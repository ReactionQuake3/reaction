//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.9  2002/03/02 01:16:30  blaze
// weapons stats- reordered where the mp5 was to make it more consistant with the weapon selection page
//
// Revision 1.8  2002/02/28 06:09:23  blaze
// weapons stats on server side - spelling fixed, and forgot ssg3000 and kicks
//
// Revision 1.7  2002/02/28 05:41:54  blaze
// weapons stats on client side
//
// Revision 1.6  2002/02/10 08:17:08  niceass
// many changes to scoreboard (deaths/second mode)
//
// Revision 1.5  2002/02/04 00:23:05  niceass
// New TP scoreboard
//
// Revision 1.4  2002/01/11 19:48:29  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.3  2001/12/31 16:28:41  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
// cg_scoreboard -- draw the scoreboard on top of the game screen
#include "cg_local.h"


#define	SCOREBOARD_X		(0)

#define SB_HEADER			86
#define SB_TOP				(SB_HEADER+32)

// Where the status bar starts, so we don't overwrite it
#define SB_STATUSBAR		420

#define SB_NORMAL_HEIGHT	40
#define SB_INTER_HEIGHT		16 // interleaved height

#define SB_MAXCLIENTS_NORMAL  ((SB_STATUSBAR - SB_TOP) / SB_NORMAL_HEIGHT)
#define SB_MAXCLIENTS_INTER   ((SB_STATUSBAR - SB_TOP) / SB_INTER_HEIGHT - 1)

// Used when interleaved



#define SB_LEFT_BOTICON_X	(SCOREBOARD_X+0)
#define SB_LEFT_HEAD_X		(SCOREBOARD_X+32)
#define SB_RIGHT_BOTICON_X	(SCOREBOARD_X+64)
#define SB_RIGHT_HEAD_X		(SCOREBOARD_X+96)
// Normal
#define SB_BOTICON_X		(SCOREBOARD_X+32)
#define SB_HEAD_X			(SCOREBOARD_X+64)

#define SB_SCORELINE_X		112

#define SB_RATING_WIDTH	    (6 * BIGCHAR_WIDTH) // width 6
#define SB_SCORE_X			(SB_SCORELINE_X + BIGCHAR_WIDTH) // width 6
#define SB_RATING_X			(SB_SCORELINE_X + 6 * BIGCHAR_WIDTH) // width 6
#define SB_PING_X			(SB_SCORELINE_X + 12 * BIGCHAR_WIDTH + 8) // width 5
#define SB_TIME_X			(SB_SCORELINE_X + 17 * BIGCHAR_WIDTH + 8) // width 5
#define SB_NAME_X			(SB_SCORELINE_X + 22 * BIGCHAR_WIDTH) // width 15

// The new and improved score board
//
// In cases where the number of clients is high, the score board heads are interleaved
// here's the layout

//
//	0   32   80  112  144   240  320  400   <-- pixel position
//  bot head bot head score ping time name
//  
//  wins/losses are drawn on bot icon now

static qboolean localClient; // true if local client has been displayed

// NiceAss:
#define	SB_WIDTH				280  // 285
#define SB_START_HEIGHT			70
#define SB_MIDDLE				(SCREEN_WIDTH/2)
#define SB_LINE_WIDTH			1
#define SB_PADDING				(SB_LINE_WIDTH+2)

/*
=================
CG_DrawScoreboard
=================
*/
static void CG_DrawClientScore( int y, score_t *score, float *color, float fade, qboolean largeFormat ) {
	char	string[1024];
	vec3_t	headAngles;
	clientInfo_t	*ci;
	int iconx, headx;

	if ( score->client < 0 || score->client >= cgs.maxclients ) {
		Com_Printf( "Bad score->client: %i\n", score->client );
		return;
	}
	
	ci = &cgs.clientinfo[score->client];

	iconx = SB_BOTICON_X + (SB_RATING_WIDTH / 2);
	headx = SB_HEAD_X + (SB_RATING_WIDTH / 2);

	// draw the handicap or bot skill marker (unless player has flag)
	if ( ci->powerups & ( 1 << PW_NEUTRALFLAG ) ) {
		if( largeFormat ) {
			CG_DrawFlagModel( iconx, y - ( 32 - BIGCHAR_HEIGHT ) / 2, 32, 32, TEAM_FREE, qfalse );
		}
		else {
			CG_DrawFlagModel( iconx, y, 16, 16, TEAM_FREE, qfalse );
		}
	} else if ( ci->powerups & ( 1 << PW_REDFLAG ) ) {
		if( largeFormat ) {
			CG_DrawFlagModel( iconx, y - ( 32 - BIGCHAR_HEIGHT ) / 2, 32, 32, TEAM_RED, qfalse );
		}
		else {
			CG_DrawFlagModel( iconx, y, 16, 16, TEAM_RED, qfalse );
		}
	} else if ( ci->powerups & ( 1 << PW_BLUEFLAG ) ) {
		if( largeFormat ) {
			CG_DrawFlagModel( iconx, y - ( 32 - BIGCHAR_HEIGHT ) / 2, 32, 32, TEAM_BLUE, qfalse );
		}
		else {
			CG_DrawFlagModel( iconx, y, 16, 16, TEAM_BLUE, qfalse );
		}
	} else {
		if ( ci->botSkill > 0 && ci->botSkill <= 5 ) {
			if ( cg_drawIcons.integer ) {
				if( largeFormat ) {
					CG_DrawPic( iconx, y - ( 32 - BIGCHAR_HEIGHT ) / 2, 32, 32, cgs.media.botSkillShaders[ ci->botSkill - 1 ] );
				}
				else {
					CG_DrawPic( iconx, y, 16, 16, cgs.media.botSkillShaders[ ci->botSkill - 1 ] );
				}
			}
		} else if ( ci->handicap < 100 ) {
			Com_sprintf( string, sizeof( string ), "%i", ci->handicap );
			if ( cgs.gametype == GT_TOURNAMENT )
				CG_DrawSmallStringColor( iconx, y - SMALLCHAR_HEIGHT/2, string, color );
			else
				CG_DrawSmallStringColor( iconx, y, string, color );
		}

		// draw the wins / losses
		if ( cgs.gametype == GT_TOURNAMENT ) {
			Com_sprintf( string, sizeof( string ), "%i/%i", ci->wins, ci->losses );
			if( ci->handicap < 100 && !ci->botSkill ) {
				CG_DrawSmallStringColor( iconx, y + SMALLCHAR_HEIGHT/2, string, color );
			}
			else {
				CG_DrawSmallStringColor( iconx, y, string, color );
			}
		}
	}

	// draw the face
	VectorClear( headAngles );
	headAngles[YAW] = 180;
	if( largeFormat ) {
		CG_DrawHead( headx, y - ( ICON_SIZE - BIGCHAR_HEIGHT ) / 2, ICON_SIZE, ICON_SIZE, 
			score->client, headAngles );
	}
	else {
		CG_DrawHead( headx, y, 16, 16, score->client, headAngles );
	}

#ifdef MISSIONPACK
	// draw the team task
	if ( ci->teamTask != TEAMTASK_NONE ) {
		if ( ci->teamTask == TEAMTASK_OFFENSE ) {
			CG_DrawPic( headx + 48, y, 16, 16, cgs.media.assaultShader );
		}
		else if ( ci->teamTask == TEAMTASK_DEFENSE ) {
			CG_DrawPic( headx + 48, y, 16, 16, cgs.media.defendShader );
		}
	}
#endif
	// draw the score line
	if ( score->ping == -1 ) {
		Com_sprintf(string, sizeof(string),
			" connecting    %s", ci->name);
	} else if ( ci->team == TEAM_SPECTATOR ) {
		Com_sprintf(string, sizeof(string),
			" SPECT %3i %4i %s", score->ping, score->time, ci->name);
	} else {
		Com_sprintf(string, sizeof(string),
			"%5i %4i %4i %s", score->score, score->ping, score->time, ci->name);
	}

	// highlight your position
	if ( score->client == cg.snap->ps.clientNum ) {
		float	hcolor[4];
		int		rank;

		localClient = qtrue;

		if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR 
			|| cgs.gametype >= GT_TEAM ) {
			rank = -1;
		} else {
			rank = cg.snap->ps.persistant[PERS_RANK] & ~RANK_TIED_FLAG;
		}
		if ( rank == 0 ) {
			hcolor[0] = 0;
			hcolor[1] = 0;
			hcolor[2] = 0.7f;
		} else if ( rank == 1 ) {
			hcolor[0] = 0.7f;
			hcolor[1] = 0;
			hcolor[2] = 0;
		} else if ( rank == 2 ) {
			hcolor[0] = 0.7f;
			hcolor[1] = 0.7f;
			hcolor[2] = 0;
		} else {
			hcolor[0] = 0.7f;
			hcolor[1] = 0.7f;
			hcolor[2] = 0.7f;
		}

		hcolor[3] = fade * 0.7;
		CG_FillRect( SB_SCORELINE_X + BIGCHAR_WIDTH + (SB_RATING_WIDTH / 2), y, 
			640 - SB_SCORELINE_X - BIGCHAR_WIDTH, BIGCHAR_HEIGHT+1, hcolor );
	}

	CG_DrawBigString( SB_SCORELINE_X + (SB_RATING_WIDTH / 2), y, string, fade );

	// add the "ready" marker for intermission exiting
	if ( cg.snap->ps.stats[ STAT_CLIENTS_READY ] & ( 1 << score->client ) ) {
		CG_DrawBigStringColor( iconx, y, "READY", color );
	}
}

static void CG_DrawTeamplayClientScore( int y, int x, score_t *score, float fade, float *color ) {
	char	string[1024];
	vec3_t	headAngles;
	clientInfo_t	*ci;
	int iconx, headx;
	float	hcolor[4];
	int		size;

	if ( score->client < 0 || score->client >= cgs.maxclients ) {
		Com_Printf( "Bad score->client: %i\n", score->client );
		return;
	}
	
	ci = &cgs.clientinfo[score->client];
	
	// Name:
	CG_DrawStringExt( x, y, ci->name, color, qtrue, qfalse, SMALLCHAR_WIDTH, SMALLCHAR_HEIGHT, 17);

	if ( score->client == cg.snap->ps.clientNum ) {
		MAKERGBA(hcolor, 0.0f, 0.0f, 0.0f, 0.5f);
		CG_FillRect( x, y, SB_WIDTH-SB_PADDING*2, SMALLCHAR_HEIGHT, hcolor );
	}

	if (cg.scoreTPMode) {
		if (score->ping == -1)
			Com_sprintf(string, sizeof(string),
					"Connecting");
		else
			Com_sprintf(string, sizeof(string),
					"%4i  %4i", score->ping, score->time);
		size = 11;
	}
	else {
		if (score->ping == -1)
			Com_sprintf(string, sizeof(string),
					"  Connecting");
		else
			Com_sprintf(string, sizeof(string),
					"%5i  %6i", score->score, score->deaths);
		size = 14;
	}

	CG_DrawSmallString( x+SB_WIDTH-(SMALLCHAR_WIDTH*size)-6, y, string, fade );
}



/*
=================
CG_TeamScoreboard -- By NiceAss
=================
*/
static int CG_TeamplayScoreboard(int maxClients) 
{
	int		i, red, blue, spec;
	float	color[4], Alpha, Alpha2;
	score_t	*score;
	clientInfo_t	*ci;
	int		y;
	int		size, players;
	char	*String;

	if (cg.time > cg.scoreStartTime+300) {
		Alpha = (cos((cg.time-cg.scoreStartTime) / 400.0f) + 1.0f) * 0.25f + 0.5f;
		Alpha2 = (cos((cg.time-cg.scoreStartTime) / 400.0f) + 1.0f) * 0.5f;
	}
	else {
		Alpha = (float)(cg.time-cg.scoreStartTime)/(float)300;
		if (Alpha > 1.0f) Alpha = 1.0f;
	}

    red = blue = spec = 0;
	for ( i = 0 ; i < cg.numScores && red+blue+spec < maxClients ; i++ ) {
		score = &cg.scores[i];
		ci = &cgs.clientinfo[ score->client ];
		if (ci->team == TEAM_RED) red++;
		if (ci->team == TEAM_BLUE) blue++;
	}
	players = (red > blue) ? red : blue;
	if (players == 0) players = 1;
	size = (players*20)+SB_PADDING;

	// Red:
	MAKERGBA(color, 1.0f, 0.5f, 0.5f, 0.7f * Alpha);
	CG_FillRect(SB_MIDDLE - SB_WIDTH - 6, SB_START_HEIGHT, 
				SB_WIDTH, SMALLCHAR_HEIGHT+(SB_PADDING*2), color);
	MAKERGBA(color, 0.55f, 0.55f, 0.55f, 0.7f * Alpha);
	CG_FillRect(SB_MIDDLE - SB_WIDTH - 6, SB_START_HEIGHT+SMALLCHAR_HEIGHT+(SB_PADDING*2), 
				SB_WIDTH, SMALLCHAR_HEIGHT+(SB_PADDING*2), color);
	MAKERGBA(color, 0.6f, 0.5f, 0.5f, 0.5f * Alpha);
	CG_FillRect(SB_MIDDLE - SB_WIDTH - 6, SB_START_HEIGHT+(SMALLCHAR_HEIGHT+(SB_PADDING*2))*2, 
				SB_WIDTH, size, color);

	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 0.8f);
	CG_DrawCleanRect( SB_MIDDLE - SB_WIDTH - 6, SB_START_HEIGHT, 
			SB_WIDTH, (SMALLCHAR_HEIGHT+SB_PADDING*2)*2+size, SB_LINE_WIDTH, color );
	CG_DrawCleanRect( SB_MIDDLE - SB_WIDTH - 6, SB_START_HEIGHT + SMALLCHAR_HEIGHT+(SB_PADDING*2), 
			SB_WIDTH, (SMALLCHAR_HEIGHT+SB_PADDING*2), SB_LINE_WIDTH, color );

	
	MAKERGBA(color, 0.0f, 0.0f, 0.0f, 1.0f);
	CG_DrawSmallStringColor(SB_MIDDLE-SB_WIDTH+SB_PADDING-6, SB_START_HEIGHT+SB_PADDING,
							"Team 1", color);

	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 0.8f);
	CG_DrawSmallStringColor(SB_MIDDLE-SB_WIDTH+SB_PADDING-6, SB_START_HEIGHT+SMALLCHAR_HEIGHT+(SB_PADDING*3), 
							"Name", color);
	if (cg.scoreTPMode) {
		CG_DrawSmallStringColor(SB_MIDDLE-SB_PADDING-6-(SMALLCHAR_WIDTH*11), SB_START_HEIGHT+SMALLCHAR_HEIGHT+(SB_PADDING*3), 
								"Ping  Time", color);
	}
	else {
		CG_DrawSmallStringColor(SB_MIDDLE-SB_PADDING-6-(SMALLCHAR_WIDTH*14), SB_START_HEIGHT+SMALLCHAR_HEIGHT+(SB_PADDING*3), 
								"Frags  Deaths", color);
	}


	// Blue:
	MAKERGBA(color, 0.5f, 0.5f, 1.0f, 0.7f * Alpha);
	CG_FillRect(SB_MIDDLE + 6, SB_START_HEIGHT, 
				SB_WIDTH, SMALLCHAR_HEIGHT+(SB_PADDING*2), color);
	MAKERGBA(color, 0.55f, 0.55f, 0.55f, 0.7f * Alpha);
	CG_FillRect(SB_MIDDLE + 6, SB_START_HEIGHT+SMALLCHAR_HEIGHT+(SB_PADDING*2), 
				SB_WIDTH, SMALLCHAR_HEIGHT+(SB_PADDING*2), color);
	MAKERGBA(color, 0.5f, 0.5f, 0.6f, 0.5f * Alpha);
	CG_FillRect(SB_MIDDLE + 6, SB_START_HEIGHT+(SMALLCHAR_HEIGHT+(SB_PADDING*2))*2, 
				SB_WIDTH, size, color);

	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 0.8f);
	CG_DrawCleanRect( SB_MIDDLE + 6, SB_START_HEIGHT, 
		SB_WIDTH, (SMALLCHAR_HEIGHT+SB_PADDING*2)*2+size, SB_LINE_WIDTH, color );
	CG_DrawCleanRect( SB_MIDDLE + 6, SB_START_HEIGHT + SMALLCHAR_HEIGHT+(SB_PADDING*2), 
		SB_WIDTH, (SMALLCHAR_HEIGHT+SB_PADDING*2), SB_LINE_WIDTH, color );

	MAKERGBA(color, 0.0f, 0.0f, 0.0f, 1.0f);
	CG_DrawSmallStringColor(SB_MIDDLE+SB_PADDING+6, SB_START_HEIGHT+SB_PADDING,
							"Team 2", color);

	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 0.8f);
	CG_DrawSmallStringColor(SB_MIDDLE+SB_PADDING+6, SB_START_HEIGHT+SMALLCHAR_HEIGHT+(SB_PADDING*3), 
							"Name", color);
	if (cg.scoreTPMode) {
		CG_DrawSmallStringColor(SB_MIDDLE-SB_PADDING+6+SB_WIDTH-(SMALLCHAR_WIDTH*11), SB_START_HEIGHT+SMALLCHAR_HEIGHT+(SB_PADDING*3), 
								"Ping  Time", color);
	}
	else {
		CG_DrawSmallStringColor(SB_MIDDLE-SB_PADDING+6+SB_WIDTH-(SMALLCHAR_WIDTH*14), SB_START_HEIGHT+SMALLCHAR_HEIGHT+(SB_PADDING*3), 
								"Frags  Deaths", color);
	}

	String = va("Wins: %d ", cg.teamScores[0]);
	CG_DrawSmallStringColor(SB_MIDDLE-SB_PADDING-6-(SMALLCHAR_WIDTH*strlen(String)), 
							SB_START_HEIGHT+SB_PADDING, String, color);

	String = va("Wins: %d ", cg.teamScores[1]);
	CG_DrawSmallStringColor(SB_MIDDLE-SB_PADDING+6+SB_WIDTH-(SMALLCHAR_WIDTH*strlen(String)), 
							SB_START_HEIGHT+SB_PADDING, String, color);


	// Individual player info
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	y = SB_START_HEIGHT+(SMALLCHAR_HEIGHT+(SB_PADDING*2))*2 + SB_PADDING;
    red = blue = spec = 0;
	for ( i = 0 ; i < cg.numScores && red+blue+spec < maxClients ; i++ ) {
		score = &cg.scores[i];
		ci = &cgs.clientinfo[ score->client ];

		if (ci->team == TEAM_RED) {
			CG_DrawTeamplayClientScore( y + 20 * red, SB_MIDDLE-SB_WIDTH+SB_PADDING-6, score, 1.0f, color);
			red++;
		}
		else if (ci->team == TEAM_BLUE) {
			CG_DrawTeamplayClientScore( y + 20 * blue, SB_MIDDLE+SB_PADDING+6, score, 1.0f, color);
			blue++;
		}
		else if (ci->team == TEAM_SPECTATOR) {
			CG_DrawTeamplayClientScore( y + (20 * players) + (20 * spec) + SB_PADDING*2, 
				SB_MIDDLE-SB_WIDTH+SB_PADDING-6, score, 1.0f, color);
			spec++;
		}
	}

	// NiceAss: I added this so it will update while open. It normally only would update when first opened.
	if ( cg.scoresRequestTime + 3000 < cg.time ) {
		// the scores are more than two seconds out of data,
		// so request new ones
		cg.scoresRequestTime = cg.time;
		trap_SendClientCommand( "score" );
	}


	return red+blue+spec;
}

/*
=================
CG_TeamScoreboard
=================
*/
static int CG_TeamScoreboard( int y, team_t team, float fade, int maxClients, int lineHeight ) {
	int		i;
	score_t	*score;
	float	color[4];
	int		count;
	clientInfo_t	*ci;

	color[0] = color[1] = color[2] = 1.0;
	color[3] = fade;

	count = 0;
	for ( i = 0 ; i < cg.numScores && count < maxClients ; i++ ) {
		score = &cg.scores[i];
		ci = &cgs.clientinfo[ score->client ];

		if ( team != ci->team ) {
			continue;
		}

		CG_DrawClientScore( y + lineHeight * count, score, color, fade, lineHeight == SB_NORMAL_HEIGHT );

		count++;
	}

	return count;
}

/*
=================
CG_DrawScoreboard

Draw the normal in-game scoreboard
=================
*/
qboolean CG_DrawOldScoreboard( void ) {
	int		x, y, w, i, n1, n2;
	float	fade;
	float	*fadeColor;
	char	*s;
	int maxClients;
	int lineHeight;
	int topBorderSize, bottomBorderSize;

	// don't draw amuthing if the menu or console is up
	if ( cg_paused.integer ) {
		cg.deferredPlayerLoading = 0;
		return qfalse;
	}

	if ( cgs.gametype == GT_SINGLE_PLAYER && cg.predictedPlayerState.pm_type == PM_INTERMISSION ) {
		cg.deferredPlayerLoading = 0;
		return qfalse;
	}

	// don't draw scoreboard during death while warmup up
	if ( cg.warmup && !cg.showScores ) {
		return qfalse;
	}

	if ( cg.showScores || cg.predictedPlayerState.pm_type == PM_DEAD ||
		 cg.predictedPlayerState.pm_type == PM_INTERMISSION ) {
		fade = 1.0;
		fadeColor = colorWhite;
	} else {
		fadeColor = CG_FadeColor( cg.scoreFadeTime, FADE_TIME );
		
		if ( !fadeColor ) {
			// next time scoreboard comes up, don't print killer
			cg.deferredPlayerLoading = 0;
			cg.killerName[0] = 0;
			return qfalse;
		}
		fade = *fadeColor;
	}


	// fragged by ... line
	if ( cg.killerName[0] ) {
		s = va("Fragged by %s", cg.killerName );
		w = CG_DrawStrlen( s ) * BIGCHAR_WIDTH;
		x = ( SCREEN_WIDTH - w ) / 2;
		y = 40;
		CG_DrawBigString( x, y, s, fade );
	}

	// current rank
	if ( cgs.gametype < GT_TEAM) {
		if (cg.snap->ps.persistant[PERS_TEAM] != TEAM_SPECTATOR ) {
			s = va("%s place with %i",
				CG_PlaceString( cg.snap->ps.persistant[PERS_RANK] + 1 ),
				cg.snap->ps.persistant[PERS_SCORE] );
			w = CG_DrawStrlen( s ) * BIGCHAR_WIDTH;
			x = ( SCREEN_WIDTH - w ) / 2;
			y = 60;
			CG_DrawBigString( x, y, s, fade );
		}
	}
	// NiceAss: No
	/*else {
		if ( cg.teamScores[0] == cg.teamScores[1] ) {
			s = va("Teams are tied at %i", cg.teamScores[0] );
		} else if ( cg.teamScores[0] >= cg.teamScores[1] ) {
			s = va("Red leads %i to %i",cg.teamScores[0], cg.teamScores[1] );
		} else {
			s = va("Blue leads %i to %i",cg.teamScores[1], cg.teamScores[0] );
		}

		w = CG_DrawStrlen( s ) * BIGCHAR_WIDTH;
		x = ( SCREEN_WIDTH - w ) / 2;
		y = 60;
		CG_DrawBigString( x, y, s, fade );
	}
*/
	// scoreboard
	if ( cgs.gametype < GT_TEAM) {
		y = SB_HEADER;

		CG_DrawPic( SB_SCORE_X + (SB_RATING_WIDTH / 2), y, 64, 32, cgs.media.scoreboardScore );
		CG_DrawPic( SB_PING_X - (SB_RATING_WIDTH / 2), y, 64, 32, cgs.media.scoreboardPing );
		CG_DrawPic( SB_TIME_X - (SB_RATING_WIDTH / 2), y, 64, 32, cgs.media.scoreboardTime );
		CG_DrawPic( SB_NAME_X - (SB_RATING_WIDTH / 2), y, 64, 32, cgs.media.scoreboardName );
	}

	y = SB_TOP;

	// If there are more than SB_MAXCLIENTS_NORMAL, use the interleaved scores
	if ( cg.numScores > SB_MAXCLIENTS_NORMAL ) {
		maxClients = SB_MAXCLIENTS_INTER;
		lineHeight = SB_INTER_HEIGHT;
		topBorderSize = 8;
		bottomBorderSize = 16;
	} else {
		maxClients = SB_MAXCLIENTS_NORMAL;
		lineHeight = SB_NORMAL_HEIGHT;
		topBorderSize = 16;
		bottomBorderSize = 16;
	}

	localClient = qfalse;

	if ( cgs.gametype >= GT_TEAM ) {
		//
		// teamplay scoreboard
		//
		n1 = CG_TeamplayScoreboard(maxClients);
		maxClients -= n1;
	} else {
		//
		// free for all scoreboard
		//
		n1 = CG_TeamScoreboard( y, TEAM_FREE, fade, maxClients, lineHeight );
		y += (n1 * lineHeight) + BIGCHAR_HEIGHT;
		n2 = CG_TeamScoreboard( y, TEAM_SPECTATOR, fade, maxClients - n1, lineHeight );
		y += (n2 * lineHeight) + BIGCHAR_HEIGHT;
	}

	if (!localClient && cgs.gametype < GT_TEAM) {
		// draw local client at the bottom
		for ( i = 0 ; i < cg.numScores ; i++ ) {
			if ( cg.scores[i].client == cg.snap->ps.clientNum ) {
				CG_DrawClientScore( y, &cg.scores[i], fadeColor, fade, lineHeight == SB_NORMAL_HEIGHT );
				break;
			}
		}
	}

	// load any models that have been deferred
	if ( ++cg.deferredPlayerLoading > 10 ) {
		CG_LoadDeferredPlayers();
	}

	return qtrue;
}

//================================================================================

/*
================
CG_CenterGiantLine
================
*/
static void CG_CenterGiantLine( float y, const char *string ) {
	float		x;
	vec4_t		color;

	color[0] = 1;
	color[1] = 1;
	color[2] = 1;
	color[3] = 1;

	x = 0.5 * ( 640 - GIANT_WIDTH * CG_DrawStrlen( string ) );

	CG_DrawStringExt( x, y, string, color, qtrue, qtrue, GIANT_WIDTH, GIANT_HEIGHT, 0 );
}

/*
=================
CG_DrawTourneyScoreboard

Draw the oversize scoreboard for tournements
=================
*/
void CG_DrawOldTourneyScoreboard( void ) {
	const char		*s;
	vec4_t			color;
	int				min, tens, ones;
	clientInfo_t	*ci;
	int				y;
	int				i;

	// request more scores regularly
	if ( cg.scoresRequestTime + 2000 < cg.time ) {
		cg.scoresRequestTime = cg.time;
		trap_SendClientCommand( "score" );
	}

	color[0] = 1;
	color[1] = 1;
	color[2] = 1;
	color[3] = 1;

	// draw the dialog background
	color[0] = color[1] = color[2] = 0;
	color[3] = 1;
	CG_FillRect( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color );

	// print the mesage of the day
	s = CG_ConfigString( CS_MOTD );
	if ( !s[0] ) {
		s = "Scoreboard";
	}

	// print optional title
	CG_CenterGiantLine( 8, s );

	// print server time
	ones = cg.time / 1000;
	min = ones / 60;
	ones %= 60;
	tens = ones / 10;
	ones %= 10;
	s = va("%i:%i%i", min, tens, ones );

	CG_CenterGiantLine( 64, s );


	// print the two scores

	y = 160;
	if ( cgs.gametype >= GT_TEAM ) {
		//
		// teamplay scoreboard
		//
		CG_DrawStringExt( 8, y, "Red Team", color, qtrue, qtrue, GIANT_WIDTH, GIANT_HEIGHT, 0 );
		s = va("%i", cg.teamScores[0] );
		CG_DrawStringExt( 632 - GIANT_WIDTH * strlen(s), y, s, color, qtrue, qtrue, GIANT_WIDTH, GIANT_HEIGHT, 0 );
		
		y += 64;

		CG_DrawStringExt( 8, y, "Blue Team", color, qtrue, qtrue, GIANT_WIDTH, GIANT_HEIGHT, 0 );
		s = va("%i", cg.teamScores[1] );
		CG_DrawStringExt( 632 - GIANT_WIDTH * strlen(s), y, s, color, qtrue, qtrue, GIANT_WIDTH, GIANT_HEIGHT, 0 );
	} else {
		//
		// free for all scoreboard
		//
		for ( i = 0 ; i < MAX_CLIENTS ; i++ ) {
			ci = &cgs.clientinfo[i];
			if ( !ci->infoValid ) {
				continue;
			}
			if ( ci->team != TEAM_FREE ) {
				continue;
			}

			CG_DrawStringExt( 8, y, ci->name, color, qtrue, qtrue, GIANT_WIDTH, GIANT_HEIGHT, 0 );
			s = va("%i", ci->score );
			CG_DrawStringExt( 632 - GIANT_WIDTH * strlen(s), y, s, color, qtrue, qtrue, GIANT_WIDTH, GIANT_HEIGHT, 0 );
			y += 64;
		}
	}


}

//Blaze: Added the weapons stats "scoreboard" to this file because it's a scoreboard in a way.
/*
==============================
CG_DrawWeaponStats

  Draws the stats of the player
==============================
*/
#define WS_LEFTSIDE 20
#define WS_TOP 230
#define WS_WIDTH 640 - WS_LEFTSIDE * 10
#define WS_LINE_WIDTH			1
#define WS_PADDING				(WS_LINE_WIDTH+2)


void CG_DrawWeaponStats(void)
{
	int		i, red, blue, spec, score, deaths, offset;
	float	color[4], Alpha, Alpha2;
	
	clientInfo_t	*ci;
	int		y;
	int		size, players;
	char	String[80];

	if (cg.time > cg.wstatsStartTime+300) {
		Alpha = (cos((cg.time-cg.wstatsStartTime) / 400.0f) + 1.0f) * 0.25f + 0.5f;
		Alpha2 = (cos((cg.time-cg.wstatsStartTime) / 400.0f) + 1.0f) * 0.5f;
	}
	else {
		Alpha = (float)(cg.time-cg.wstatsStartTime)/(float)300;
		if (Alpha > 1.0f) Alpha = 1.0f;
	}
  //make room for 8 weapon stats
  size = (10*20)+SB_PADDING;
  score = cg.snap->ps.persistant[PERS_SCORE];
  deaths = cg.snap->ps.persistant[PERS_KILLED];
	// Score bar - Red:
	MAKERGBA(color, 1.0f, 0.5f, 0.5f, 0.7f * Alpha);
	CG_FillRect(WS_LEFTSIDE, WS_TOP, 
				WS_WIDTH, SMALLCHAR_HEIGHT+(WS_PADDING*2), color);

  //Box for scores, etc
  MAKERGBA(color, 0.55f, 0.55f, 0.55f, 0.7f * Alpha);
	CG_FillRect(WS_LEFTSIDE, WS_TOP+SMALLCHAR_HEIGHT+(SB_PADDING*2), 
				WS_WIDTH, SMALLCHAR_HEIGHT+(WS_PADDING*2), color);

  //Box for weapon stuff
	MAKERGBA(color, 0.6f, 0.5f, 0.5f, 0.5f * Alpha);
	CG_FillRect(WS_LEFTSIDE, WS_TOP + (SMALLCHAR_HEIGHT+(WS_PADDING*2))*2, 
				WS_WIDTH, size, color);
  //box for weapon stuff
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 0.8f);
	CG_DrawCleanRect( WS_LEFTSIDE, WS_TOP, 
			WS_WIDTH, (SMALLCHAR_HEIGHT+WS_PADDING*2)*2+size, WS_LINE_WIDTH, color );

  //box for score stuff
  CG_DrawCleanRect( WS_LEFTSIDE, WS_TOP + SMALLCHAR_HEIGHT+(WS_PADDING*2), 
			WS_WIDTH, (SMALLCHAR_HEIGHT+WS_PADDING*2), WS_LINE_WIDTH, color );

  //Red box for Weapon stats
	MAKERGBA(color, 1.0f, 0.5f, 0.5f, 0.7f * Alpha);
	CG_FillRect(WS_LEFTSIDE, WS_TOP+(SMALLCHAR_HEIGHT + (WS_PADDING*2))*2, 
				WS_WIDTH, SMALLCHAR_HEIGHT, color);
  //White box for the weapon names, etc
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 0.8f);
	CG_DrawCleanRect( WS_LEFTSIDE, WS_TOP -1 + (SMALLCHAR_HEIGHT + (WS_PADDING*2))*2, 
    WS_WIDTH, SMALLCHAR_HEIGHT+1, WS_LINE_WIDTH, color );

  
  //Fill in the top bar	
  offset = 7;
	MAKERGBA(color, 1.0f, 0.0f, 0.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6, WS_TOP + SB_PADDING,
							"Score", color);

	MAKERGBA(color, 0.0f, 1.0f, 0.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * 7, WS_TOP + SB_PADDING,
							"Net", color);

  MAKERGBA(color, 0.0f, 0.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * 7 * 2, WS_TOP + SB_PADDING,
							"Kills", color);

  MAKERGBA(color, 0.5f, 0.0f, 0.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * 7 * 3, WS_TOP + SB_PADDING,
							"Deaths", color);

 	MAKERGBA(color, 0.0f, 0.5f, 0.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * 7 * 4, WS_TOP + SB_PADDING,
							"Sui", color);

 	MAKERGBA(color, 0.0f, 0.0f, 0.5f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * 7 * 5, WS_TOP + SB_PADDING,
							"TK's", color);

  MAKERGBA(color, 0.0f, 0.0f, 0.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * 7 * 6, WS_TOP + SB_PADDING,
							"Efficiency", color);
               
	Com_sprintf(String, sizeof(String),	"%4i",score);

  

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + SB_PADDING * 3 + SMALLCHAR_HEIGHT,
							String, color);
  i=2;

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"Weapon Stats", color);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"Knife(slash)", color);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"Knife(throw)", color);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"MK23", color);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"MP5", color);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"M3", color);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"M4", color);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"HC", color);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"SSG3000", color);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"Akimbo", color);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"Grenade", color);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"Kicks", color);

  
  //Accuracy

  i=2;
  offset=15;
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"Accuracy", color);

  Com_sprintf(String, sizeof(String),	"%.1f%%",100 * (float)cg.records[REC_KNIFESLASHHITS]/(cg.records[REC_KNIFESLASHSHOTS] ? cg.records[REC_KNIFESLASHSHOTS] : 1));
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%.1f%%",100 * (float)cg.records[REC_KNIFETHROWHITS]/(cg.records[REC_KNIFETHROWSHOTS] ? cg.records[REC_KNIFETHROWSHOTS] : 1));
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%.1f%%",100 * (float)cg.records[REC_MK23HITS]/(cg.records[REC_MK23SHOTS] ? cg.records[REC_MK23SHOTS] : 1));
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%.1f%%",100 * (float)cg.records[REC_MP5HITS]/(cg.records[REC_MP5SHOTS] ? cg.records[REC_MP5SHOTS] : 1));
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%.1f%%",100 * (float)cg.records[REC_M3HITS]/(cg.records[REC_M3SHOTS] ? cg.records[REC_M3SHOTS] : 1));
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%.1f%%",100 * (float)cg.records[REC_M4HITS]/(cg.records[REC_M4SHOTS] ? cg.records[REC_M4SHOTS] : 1));
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%.1f%%",100 * (float)cg.records[REC_HANDCANNONHITS]/(cg.records[REC_HANDCANNONSHOTS] ? cg.records[REC_HANDCANNONSHOTS] : 1));
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%.1f%%",100 * (float)cg.records[REC_SSG3000HITS]/(cg.records[REC_SSG3000SHOTS] ? cg.records[REC_SSG3000SHOTS] : 1));
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%.1f%%",100 * (float)cg.records[REC_AKIMBOHITS]/(cg.records[REC_AKIMBOSHOTS] ? cg.records[REC_AKIMBOSHOTS] : 1));
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%.1f%%",100 * (float)cg.records[REC_GRENADEHITS]/(cg.records[REC_GRENADESHOTS] ? cg.records[REC_GRENADESHOTS] : 1));
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);



  //Hits
  i=2;
  offset=24;
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"Hits", color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_KNIFESLASHHITS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_KNIFETHROWHITS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_MK23HITS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_MP5HITS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_M3HITS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_M4HITS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_HANDCANNONHITS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_SSG3000HITS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_AKIMBOHITS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_GRENADEHITS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_KICKHITS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  //Shots
  i=2;
  offset = 30;
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"Shots", color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_KNIFESLASHSHOTS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_KNIFETHROWSHOTS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_MK23SHOTS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_MP5SHOTS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_M3SHOTS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_M4SHOTS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_HANDCANNONSHOTS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_SSG3000SHOTS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_AKIMBOSHOTS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_GRENADESHOTS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  //Kills
  i=2;
  offset = 37;
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"Kills", color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_KNIFESLASHKILLS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_KNIFETHROWKILLS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_MK23KILLS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_MP5KILLS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_M3KILLS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_M4KILLS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_HANDCANNONKILLS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_SSG3000KILLS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_AKIMBOKILLS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_GRENADEKILLS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_KICKKILLS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  //Deaths
  i=2;
  offset = 45;
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"Deaths", color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_KNIFESLASHDEATHS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_KNIFETHROWDEATHS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_MK23DEATHS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_MP5DEATHS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_M3DEATHS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_M4DEATHS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_HANDCANNONDEATHS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_SSG3000DEATHS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_AKIMBODEATHS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_GRENADEDEATHS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%d",cg.records[REC_KICKDEATHS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + SB_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  if ( cg.wstatsRequestTime + 3000 < cg.time ) {
		// the scores are more than two seconds out of data,
		// so request new ones
		cg.wstatsRequestTime = cg.time;
		trap_SendClientCommand( "wstats" );
	}

	return;
}
