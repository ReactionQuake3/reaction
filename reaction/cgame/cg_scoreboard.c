//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.22  2002/04/18 16:13:23  jbravo
// Scoreboard now shows green for live players and white for dead.
// Time should not get reset on deaths any more.
//
// Revision 1.21  2002/03/31 03:31:24  jbravo
// Compiler warning cleanups
//
// Revision 1.20  2002/03/31 02:01:32  niceass
// fixes and changes
//
// Revision 1.19  2002/03/30 23:20:10  jbravo
// Added damage in scoreboard.
//
// Revision 1.18  2002/03/30 02:54:24  jbravo
// MOre spec tweaks and a scoreboard fix
//
// Revision 1.17  2002/03/24 22:57:27  niceass
// VERY big scoreboard changes
//
// Revision 1.14  2002/03/17 21:32:23  jbravo
// Fixed the dynamic teamnames system up a bit to reduce traffic
//
// Revision 1.13  2002/03/17 00:40:23  jbravo
// Adding variable team names. g_RQ3_team1name and g_RQ3_team2name. Fixed
// Slicers fraglimit check.
//
// Revision 1.12  2002/03/10 23:27:26  blaze
// fixed net for the wstats
//
// Revision 1.11  2002/03/03 23:12:18  blaze
// weapon stats - fixed a formating bug.
//
// Revision 1.10  2002/03/03 21:44:01  blaze
// weapon stats, done, beta test for bugs
//
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

//static qboolean localClient; // true if local client has been displayed

#define SB_WIDTH		330
#define SB_FONTSIZEW	7
#define SB_FONTSIZEH	14
#define SB_PADDING		1

void DrawStrip(int y, int Height, qboolean Fill, qboolean Top, qboolean Bottom, float *FillC, float *BoarderC) {

	if (Fill) {
		CG_FillRect( (SCREEN_WIDTH - SB_WIDTH) / 2, y, SB_WIDTH, Height+SB_PADDING*2, FillC );
	}

	if (Top)
		CG_DrawCleanLine( (SCREEN_WIDTH - SB_WIDTH) / 2, y, SB_WIDTH, 1, BoarderC );

	if (Bottom)
		CG_DrawCleanLine( (SCREEN_WIDTH - SB_WIDTH) / 2, y+Height+SB_PADDING*2, SB_WIDTH, 1, BoarderC );

	CG_DrawCleanSides( (SCREEN_WIDTH - SB_WIDTH) / 2, y, SB_WIDTH, Height+SB_PADDING*2, 1, BoarderC );

}

 void DrawLeftStripText(int y, int Height, char *Text, int maxChars, float *Color) {
	CG_DrawStringExt( 
				(SCREEN_WIDTH - SB_WIDTH) / 2 + 2, 
				y + (Height+SB_PADDING*2-SB_FONTSIZEH) / 2, 
				Text, 
				Color, 
				qtrue,				// Force color?
				qfalse,				// Shadow?
				SB_FONTSIZEW,		// charWidth
				SB_FONTSIZEH,		// charHeight
				maxChars);			// MaxChars
}

void DrawStripText(int y, int x, int Height, char *Text, int maxChars, float *Color) {
	CG_DrawStringExt( 
				(SCREEN_WIDTH - SB_WIDTH) / 2 + x, 
				y + (Height+SB_PADDING*2-SB_FONTSIZEH) / 2, 
				Text, 
				Color, 
				qtrue,				// Force color?
				qfalse,				// Shadow?
				SB_FONTSIZEW,		// charWidth
				SB_FONTSIZEH,		// charHeight
				maxChars);			// MaxChars
}

void DrawRightStripText(int y, int Height, char *Text, int maxChars, float *Color) {
	int		Len;

	Len = CG_DrawStrlen( Text );
	CG_DrawStringExt( 
				((SCREEN_WIDTH + SB_WIDTH) / 2) - (Len * SB_FONTSIZEW) - 2,
				y + (Height+SB_PADDING*2-SB_FONTSIZEH) / 2, 
				Text, 
				Color, 
				qtrue,				// Force color?
				qfalse,				// Shadow?
				SB_FONTSIZEW,		// charWidth
				SB_FONTSIZEH,		// charHeight
				maxChars);			// MaxChars
}

void DrawCenterStripText(int y, int Height, char *Text, int maxChars, float *Color) {
	int		Len;

	Len = CG_DrawStrlen( Text );
	CG_DrawStringExt( 
				(SCREEN_WIDTH - Len * SB_FONTSIZEW) / 2,
				y + (Height+SB_PADDING*2-SB_FONTSIZEH) / 2, 
				Text, 
				Color, 
				qtrue,				// Force color?
				qfalse,				// Shadow?
				SB_FONTSIZEW,		// charWidth
				SB_FONTSIZEH,		// charHeight
				maxChars);			// MaxChars
}

static void CG_DrawTeamplayClientScore( int y, score_t *score, float *Fill, float *Boarder, float *Color ) {
	char	Tmp[128];
	clientInfo_t	*ci;
	float	FillColor[4];

	if ( score->client < 0 || score->client >= cgs.maxclients ) {
		Com_Printf( "Bad score->client: %i\n", score->client );
		return;
	}

	ci = &cgs.clientinfo[score->client];

	FillColor[0] = Fill[0];
	FillColor[1] = Fill[1];
	FillColor[2] = Fill[2];
	FillColor[3] = Fill[3];

	if (score->client == cg.clientNum) FillColor[3] += 0.4f;
	if (FillColor[3] > 1) FillColor[3] = 1;
	
	DrawStrip(y, SB_FONTSIZEH, qtrue, qfalse, qfalse, FillColor, Boarder);

	DrawLeftStripText(y, SB_FONTSIZEH, ci->name, 20, Color);
	Com_sprintf(Tmp, 128, "%4i  %4i  %5i  %6i", score->time, score->ping, score->score, score->damage);
	DrawRightStripText(y, SB_FONTSIZEH, Tmp, 100, Color);
}

/*
=================
CG_TeamScoreboard 
	- By NiceAss
=================
*/
static int CG_TeamplayScoreboard(void) 
{
	clientInfo_t	*ci;
	int		i;
	int		Reds, Blues, Spectators, Refs;
	float	Alpha;
	score_t	*Score;
	int		y;
	int		Alternate, First;
	char	teamname[128];
	int		Ping, Frags, Damage; // Averages
	char	Tmp[128];

	vec4_t	White, Black, RedL, BlueL, GreyL, BlackL;
	vec4_t	RedD, BlueD, GreyD, Green;

	if (cg.time > cg.scoreStartTime+300) {
		Alpha = cos((cg.time-cg.scoreStartTime) / 400.0f) * 0.15f + 0.85f;
	}
	else {
		// Fade in
		Alpha = (float)(cg.time-cg.scoreStartTime)/(float)300;
		if (Alpha > 1.0f) Alpha = 1.0f;
	}

	MAKERGBA(White, 1.0f, 1.0f, 1.0f, 1.0f);
	MAKERGBA(Black, 0.0f, 0.0f, 0.0f, 1.0f);
	MAKERGBA(Green, 0.0f, 1.0f, 0.0f, 1.0f);
	MAKERGBA(BlackL, 0.0f, 0.0f, 0.0f, 0.8f * Alpha);
	MAKERGBA(RedD, 0.8f, 0.0f,0.0f, 0.8f * Alpha);
	MAKERGBA(BlueD, 0.0f, 0.0f, 0.8f, 0.8f * Alpha);
	MAKERGBA(GreyD, 0.3f, 0.3f, 0.3f, 0.84f * Alpha);
	MAKERGBA(RedL, 0.8f, 0.0f,0.0f, 0.4f * Alpha);
	MAKERGBA(BlueL, 0.0f, 0.0f, 0.8f, 0.4f * Alpha);
	MAKERGBA(GreyL, 0.3f, 0.3f, 0.3f, 0.4f * Alpha);

	Reds = Blues = Spectators = Refs = 0;

	for ( i = 0 ; i < cg.numScores ; i++ ) {
		Score = &cg.scores[i];
		ci = &cgs.clientinfo[ Score->client ];
		if (ci->team == TEAM_RED) Reds++;
		if (ci->team == TEAM_BLUE) Blues++;
		if (ci->team == TEAM_SPECTATOR) Spectators++;
	}

	y = 20;		// Starting height.

	if (cg.scoreTPMode == 1 || cgs.gametype < GT_TEAM) {
		DrawStrip(y, SB_FONTSIZEH, qtrue, qtrue, qtrue, BlackL, White);
		DrawLeftStripText(y, SB_FONTSIZEH, "Name", 100, White);
		DrawRightStripText(y, SB_FONTSIZEH, "Time  Ping  Frags  Damage", 100, White);
		y += SB_FONTSIZEH+SB_PADDING*2+2;

		First = 0;
		for ( i = 0 ; i < cg.numScores; i++ ) {
			Score = &cg.scores[i];
			ci = &cgs.clientinfo[ Score->client ];

			CG_DrawTeamplayClientScore(y, Score, GreyL, White, White);
			if (First == 0) DrawStrip(y, SB_FONTSIZEH, qfalse, qtrue, qfalse, GreyL, White);
			y += SB_FONTSIZEH+SB_PADDING*2;
			First = 1;
		}
		DrawStrip(y - (SB_FONTSIZEH+SB_PADDING*2), SB_FONTSIZEH, qfalse, qfalse, qtrue, GreyL, White);

		return Reds+Blues+ceil(Spectators/2)+Refs;
	}


	// *************** RED TEAM ***************
	DrawStrip(y, SB_FONTSIZEH, qtrue, qtrue, qtrue, RedD, Black);
	trap_Cvar_VariableStringBuffer("g_RQ3_team1name", teamname, sizeof(teamname));
	DrawStripText(y, 50, SB_FONTSIZEH, teamname, 100, Black);
	DrawRightStripText(y, SB_FONTSIZEH, va("Wins: %d", cg.teamScores[0]), 100, White);
	y += SB_FONTSIZEH+SB_PADDING*2+2;

	DrawStrip(y, SB_FONTSIZEH, qtrue, qtrue, qtrue, GreyL, Black);
	DrawLeftStripText(y, SB_FONTSIZEH, "Name", 100, White);
	DrawRightStripText(y, SB_FONTSIZEH, "Time  Ping  Frags  Damage", 100, White);
	y += SB_FONTSIZEH+SB_PADDING*2+2;

	Ping = Frags = Damage = 0;
	if (Reds) {
		First = 0;

		for ( i = 0 ; i < cg.numScores; i++ ) {
			Score = &cg.scores[i];
			ci = &cgs.clientinfo[ Score->client ];

			if (ci->team == TEAM_RED) {
				if(Score->alive)
					CG_DrawTeamplayClientScore(y, Score, RedL, Black, Green);
				else
					CG_DrawTeamplayClientScore(y, Score, RedL, Black, White);
				if (First == 0) DrawStrip(y, SB_FONTSIZEH, qfalse, qtrue, qfalse, RedL, Black);
				y += SB_FONTSIZEH+SB_PADDING*2;
				Ping += Score->ping;
				Frags += Score->score;
				Damage += Score->damage;
				First = 1;

			}
		}
		DrawStrip(y - (SB_FONTSIZEH+SB_PADDING*2), SB_FONTSIZEH, qfalse, qfalse, qtrue, RedL, Black);
		
		y += 2;
		Com_sprintf(Tmp, 128, "%4d  %5d  %6d", (int)((float)Ping / (float)Reds), Frags, Damage);
		DrawStrip(y, SB_FONTSIZEH, qtrue, qtrue, qtrue, GreyL, Black);
		DrawLeftStripText(y, SB_FONTSIZEH, "Averages/Totals:", 100, White);
		DrawRightStripText(y, SB_FONTSIZEH, Tmp, 100, White);
	}
	else {
		DrawStrip(y, SB_FONTSIZEH, qtrue, qtrue, qtrue, RedL, Black);
		DrawCenterStripText(y, SB_FONTSIZEH, "No team members", 100, White);
	}

	// *************** BLUE TEAM ************
	y += SB_FONTSIZEH*2;
	DrawStrip(y, SB_FONTSIZEH, qtrue, qtrue, qtrue, BlueD, Black);
	trap_Cvar_VariableStringBuffer("g_RQ3_team2name", teamname, sizeof(teamname));
	DrawStripText(y, 50, SB_FONTSIZEH, teamname, 100, Black);
	DrawRightStripText(y, SB_FONTSIZEH, va("Wins: %d", cg.teamScores[1]), 100, White);
	y += SB_FONTSIZEH+SB_PADDING*2+2;

	DrawStrip(y, SB_FONTSIZEH, qtrue, qtrue, qtrue, GreyL, Black);
	DrawLeftStripText(y, SB_FONTSIZEH, "Name", 100, White);
	DrawRightStripText(y, SB_FONTSIZEH, "Time  Ping  Frags  Damage", 100, White);
	y += SB_FONTSIZEH+SB_PADDING*2+2;

	Ping = Frags = Damage = 0;
	if (Blues) {
		First = 0;
		
		for ( i = 0 ; i < cg.numScores; i++ ) {
			Score = &cg.scores[i];
			ci = &cgs.clientinfo[ Score->client ];

			if (ci->team == TEAM_BLUE) {
				if(Score->alive)
					CG_DrawTeamplayClientScore(y, Score, BlueL, Black, Green);
				else
					CG_DrawTeamplayClientScore(y, Score, BlueL, Black, White);
				if (First == 0) DrawStrip(y, SB_FONTSIZEH, qfalse, qtrue, qfalse, BlueL, Black);
				y += SB_FONTSIZEH+SB_PADDING*2;
				Ping += Score->ping;
				Frags += Score->score;
				Damage += Score->damage;
				First = 1;
			}
		}
		DrawStrip(y - (SB_FONTSIZEH+SB_PADDING*2), SB_FONTSIZEH, qfalse, qfalse, qtrue, BlueL, Black);

		y += 2;
		Com_sprintf(Tmp, 128, "%4d  %5d  %6d", (int)((float)Ping / (float)Blues), Frags, Damage );
		DrawStrip(y, SB_FONTSIZEH, qtrue, qtrue, qtrue, GreyL, Black);
		DrawLeftStripText(y, SB_FONTSIZEH, "Averages/Totals:", 100, White);
		DrawRightStripText(y, SB_FONTSIZEH, Tmp, 100, White);
	}
	else {
		DrawStrip(y, SB_FONTSIZEH, qtrue, qtrue, qtrue, BlueL, Black);
		DrawCenterStripText(y, SB_FONTSIZEH, "No team members", 100, White);
	}

	// *************** SPECTATORS ************
	if (Spectators) {
		Alternate = 1;
		First = 0;

		y += SB_FONTSIZEH*2;
		DrawStrip(y, SB_FONTSIZEH, qtrue, qtrue, qtrue, GreyD, Black);
		DrawLeftStripText(y, SB_FONTSIZEH, "Spectators", 100, Black);
		y += SB_FONTSIZEH+SB_PADDING*2+2;

		for ( i = 0 ; i < cg.numScores; i++ ) {
			Score = &cg.scores[i];
			ci = &cgs.clientinfo[ Score->client ];

			if (ci->team == TEAM_SPECTATOR) {
				DrawStrip(y, SB_FONTSIZEH, qtrue, qfalse, qfalse, GreyL, Black);
				if (First == 0) DrawStrip(y, SB_FONTSIZEH, qfalse, qtrue, qfalse, GreyL, Black);

				if (Alternate == 1) {
					DrawLeftStripText(y, SB_FONTSIZEH, ci->name, 20, White);
				}
				else {
					DrawRightStripText(y, SB_FONTSIZEH, ci->name, 20, White);
					y += SB_FONTSIZEH+SB_PADDING*2;
				}
				Alternate = -Alternate;
				First = 1;
			}
		}

		if (Alternate == 1) 
			DrawStrip(y - (SB_FONTSIZEH+SB_PADDING*2), SB_FONTSIZEH, qfalse, qfalse, qtrue, GreyL, Black);
		else
			DrawStrip(y, SB_FONTSIZEH, qfalse, qfalse, qtrue, GreyL, Black);
	}

	// NiceAss: I added this so it will update while open. It normally only would update when first opened.
	if ( cg.scoresRequestTime + 2000 < cg.time ) {
		cg.scoresRequestTime = cg.time;
		trap_SendClientCommand( "score" );
	}

	return Reds+Blues+ceil(Spectators/2)+Refs;
}


/*
=================
CG_DrawScoreboard

Draw the normal in-game scoreboard
=================
*/
qboolean CG_DrawOldScoreboard( void ) {

	// don't draw amuthing if the menu or console is up
	if ( cg_paused.integer ) {
		cg.deferredPlayerLoading = 0;
		return qfalse;
	}

	if ( cgs.gametype == GT_SINGLE_PLAYER && cg.predictedPlayerState.pm_type == PM_INTERMISSION ) {
		cg.deferredPlayerLoading = 0;
		return qfalse;
	}

	if (!cg.showScores) return qfalse;

	// don't draw scoreboard during death while warmup up
	if ( cg.warmup ) {
		return qfalse;
	}

	CG_TeamplayScoreboard();

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
#define WS_TOP 200
#define WS_WIDTH 640 - WS_LEFTSIDE * 10
#define WS_LINE_WIDTH			1
#define WS_PADDING				(WS_LINE_WIDTH+2)


void CG_DrawWeaponStats(void)
{
	int		i, offset;
	float	color[4], Alpha, Alpha2;
	int		size;
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
  size = (10*20)+WS_PADDING;
  
  

	// Score bar - Red:
	MAKERGBA(color, 1.0f, 0.5f, 0.5f, 0.7f * Alpha);
	CG_FillRect(WS_LEFTSIDE, WS_TOP, 
				WS_WIDTH, SMALLCHAR_HEIGHT+(WS_PADDING*2), color);

  //Box for scores, etc
  MAKERGBA(color, 0.55f, 0.55f, 0.55f, 0.7f * Alpha);
	CG_FillRect(WS_LEFTSIDE, WS_TOP+SMALLCHAR_HEIGHT+(WS_PADDING*2), 
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
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6, WS_TOP + WS_PADDING,
							"Score", color);

	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * 7, WS_TOP + WS_PADDING,
							"Net", color);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * 7 * 2, WS_TOP + WS_PADDING,
							"K/D/S", color);

 	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * 7 * 3, WS_TOP + WS_PADDING,
							"TK's", color);

//  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
//	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * 7 * 4, WS_TOP + WS_PADDING,
//							"Efficiency", color);
               
	Com_sprintf(String, sizeof(String),	"%4i",cg.snap->ps.persistant[PERS_SCORE]);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + WS_PADDING * 3 + SMALLCHAR_HEIGHT,
							String, color);

  Com_sprintf(String, sizeof(String),	"%3i",cg.snap->ps.persistant[PERS_SCORE] - cg.snap->ps.persistant[PERS_KILLED]);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * 7 - 1, WS_TOP + WS_PADDING * 3 + SMALLCHAR_HEIGHT,
							String, color);


  Com_sprintf(String, sizeof(String),	"%i/%i/%i",cg.records[REC_KILLS],cg.snap->ps.persistant[PERS_KILLED],cg.records[REC_SUICIDES]);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * 7 * 2, WS_TOP + WS_PADDING * 3 + SMALLCHAR_HEIGHT,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4i",cg.records[REC_TEAMKILLS]);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * 7 * 3, WS_TOP + WS_PADDING * 3 + SMALLCHAR_HEIGHT,
							String, color);

  
  i=2;

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"Weapon Stats", color);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"Knife(slash)", color);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"Knife(throw)", color);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"MK23", color);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"MP5", color);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"M3", color);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"M4", color);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"HC", color);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"SSG3000", color);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"Akimbo", color);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"Grenade", color);

  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"Kicks", color);

  
  //Accuracy

  i=2;
  offset=15;
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"Accuracy", color);

  Com_sprintf(String, sizeof(String),	"%.1f%%",100 * (float)cg.records[REC_KNIFESLASHHITS]/(cg.records[REC_KNIFESLASHSHOTS] ? cg.records[REC_KNIFESLASHSHOTS] : 1));
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%.1f%%",100 * (float)cg.records[REC_KNIFETHROWHITS]/(cg.records[REC_KNIFETHROWSHOTS] ? cg.records[REC_KNIFETHROWSHOTS] : 1));
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%.1f%%",100 * (float)cg.records[REC_MK23HITS]/(cg.records[REC_MK23SHOTS] ? cg.records[REC_MK23SHOTS] : 1));
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%.1f%%",100 * (float)cg.records[REC_MP5HITS]/(cg.records[REC_MP5SHOTS] ? cg.records[REC_MP5SHOTS] : 1));
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%.1f%%",100 * (float)cg.records[REC_M3HITS]/(cg.records[REC_M3SHOTS] ? cg.records[REC_M3SHOTS] : 1));
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%.1f%%",100 * (float)cg.records[REC_M4HITS]/(cg.records[REC_M4SHOTS] ? cg.records[REC_M4SHOTS] : 1));
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%.1f%%",100 * (float)cg.records[REC_HANDCANNONHITS]/(cg.records[REC_HANDCANNONSHOTS] ? cg.records[REC_HANDCANNONSHOTS] : 1));
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%.1f%%",100 * (float)cg.records[REC_SSG3000HITS]/(cg.records[REC_SSG3000SHOTS] ? cg.records[REC_SSG3000SHOTS] : 1));
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%.1f%%",100 * (float)cg.records[REC_AKIMBOHITS]/(cg.records[REC_AKIMBOSHOTS] ? cg.records[REC_AKIMBOSHOTS] : 1));
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%.1f%%",100 * (float)cg.records[REC_GRENADEHITS]/(cg.records[REC_GRENADESHOTS] ? cg.records[REC_GRENADESHOTS] : 1));
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);



  //Hits
  i=2;
  offset=25;
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"Hits", color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_KNIFESLASHHITS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_KNIFETHROWHITS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_MK23HITS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_MP5HITS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_M3HITS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_M4HITS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_HANDCANNONHITS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_SSG3000HITS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_AKIMBOHITS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_GRENADEHITS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_KICKHITS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  //Shots
  i=2;
  offset = 32;
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * (offset - 1), WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"Shots", color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_KNIFESLASHSHOTS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_KNIFETHROWSHOTS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_MK23SHOTS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_MP5SHOTS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_M3SHOTS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_M4SHOTS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_HANDCANNONSHOTS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_SSG3000SHOTS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_AKIMBOSHOTS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_GRENADESHOTS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  //Kills
  i=2;
  offset = 39;
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * (offset - 1), WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"Kills", color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_KNIFESLASHKILLS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_KNIFETHROWKILLS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_MK23KILLS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_MP5KILLS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_M3KILLS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_M4KILLS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_HANDCANNONKILLS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_SSG3000KILLS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_AKIMBOKILLS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_GRENADEKILLS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_KICKKILLS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  //Deaths
  i=2;
  offset = 47;
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * (offset -2), WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							"Deaths", color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_KNIFESLASHDEATHS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_KNIFETHROWDEATHS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_MK23DEATHS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_MP5DEATHS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_M3DEATHS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_M4DEATHS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_HANDCANNONDEATHS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_SSG3000DEATHS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_AKIMBODEATHS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_GRENADEDEATHS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  Com_sprintf(String, sizeof(String),	"%4d",cg.records[REC_KICKDEATHS]);
  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset, WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++,
							String, color);

  if ( cg.wstatsRequestTime + 3000 < cg.time ) {
		// the scores are more than two seconds out of data,
		// so request new ones
		cg.wstatsRequestTime = cg.time;
		trap_SendClientCommand( "wstats" );
	}

	return;
}
