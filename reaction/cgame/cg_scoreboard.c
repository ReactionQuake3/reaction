//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.50  2002/10/21 21:17:16  niceass
// bleh
//
// Revision 1.49  2002/10/21 21:04:33  niceass
// ref fix
//
// Revision 1.48  2002/10/21 21:01:49  niceass
// ref ready code
//
// Revision 1.47  2002/08/29 04:45:25  niceass
// color changes for new outlined font
//
// Revision 1.46  2002/08/27 05:08:22  niceass
// fix for ref
//
// Revision 1.45  2002/08/24 07:59:48  niceass
// new ref system
//
// Revision 1.44  2002/08/07 04:44:23  niceass
// ctb changes
//
// Revision 1.43  2002/07/22 01:27:38  niceass
// spectator coloring fix
//
// Revision 1.42  2002/07/19 04:40:56  jbravo
// Added 2 new radio sets and ctb radio sound support
//
// Revision 1.41  2002/07/09 05:42:51  niceass
// flag scoreboard changes
//
// Revision 1.40  2002/07/08 04:27:32  niceass
// moved some code to game. Changed from head models to icons
//
// Revision 1.39  2002/07/02 07:38:55  niceass
// Added total players/subs & fixed ping bug
//
// Revision 1.38  2002/07/02 07:21:41  niceass
// untested matchmode ping determination
//
// Revision 1.37  2002/06/21 21:05:00  niceass
// tinkering
//
// Revision 1.36  2002/06/20 02:27:30  jbravo
// Now the scoreboard doesnt show whos alive and whos not when you are alive
//
// Revision 1.35  2002/06/19 05:21:20  niceass
// scoreboard stuff
//
// Revision 1.34  2002/06/16 20:06:13  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.33  2002/06/10 13:20:03  slicer
// RefID is now passed trought scoreboard, no more lca cvar, only cg.lca
//
// Revision 1.32  2002/06/05 23:39:23  niceass
// small change in wording
//
// Revision 1.31  2002/06/05 04:58:43  niceass
// Scoreboard changes
//
// Revision 1.30  2002/06/03 19:20:18  niceass
// referee change
//
// Revision 1.29  2002/06/03 00:47:18  niceass
// match scoreboard changes
//
// Revision 1.28  2002/05/27 17:47:19  jbravo
// Fixes and cleanups
//
// Revision 1.27  2002/05/27 07:00:09  niceass
// misc changes
//
// Revision 1.26  2002/05/12 02:21:06  niceass
// Matchmode scoreboard features
//
// Revision 1.25  2002/05/07 13:35:45  jbravo
// Fixed the double lights for spectators and made the use cmd use rq3_cmd
// and made scoreboard not revieal whos alive or dead to live players.
//
// Revision 1.24  2002/04/29 06:15:30  niceass
// ref shown as green. more mm stuff soon to come
//
// Revision 1.23  2002/04/23 06:05:52  niceass
// scoreboard stuff (btw, green is ugly)
//
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

void CG_DrawScoreBoardHead(float x, float y, float w, float h, 
						   qhandle_t headModel, qhandle_t headSkin, vec3_t headAngles);
void CG_ScoreBoardHead(team_t team, float x, float y, float w, float h);



#define SB_WIDTH		330
#define SB_FONTSIZEW	7
#define SB_FONTSIZEH	(SB_FONTSIZEW * 2)
#define SB_PADDING		1

int TeamAveragePing(team_t team) 
{
	int i;
	int Players = 0, AvgPing = 0;
	int MaxPing1 = -1;								// Ping value
	int MaxPing1I = -1, MaxPing2I = -1;				// Index value

	score_t *Score;
	clientInfo_t *ci;

	// Find out how many are on the team
	// and the two highest pingers
	for (i = 0; i < cg.numScores; i++) {
		Score = &cg.scores[i];
		ci = &cgs.clientinfo[Score->client];

		if (Score->sub == TEAM_RED || Score->sub == TEAM_BLUE)
			continue;

		if (ci->team != team)
			continue;

		Players++;

		if (Score->ping >= MaxPing1) {
			MaxPing2I = MaxPing1I;
			MaxPing1 = Score->ping;
			MaxPing1I = i;
		}
	}

	if (!Players)
		return 0;

	for (i = 0; i < cg.numScores; i++) {
		Score = &cg.scores[i];
		ci = &cgs.clientinfo[Score->client];

		if (Score->sub == TEAM_RED || Score->sub == TEAM_BLUE)
			continue;

		if (ci->team != team)
			continue;

		// 4+ players, ignore highest pinger on team
		if (Players > 3 && i == MaxPing1I)
			continue;

		// 7+ players, ignore second highest pinger on team also
		if (Players > 6 && i == MaxPing2I)
			continue;

		AvgPing += Score->ping;
	}


	// One player ignored
	if (Players > 3) 
		Players--;

	// A Second player ignored
	if (Players > 6)
		Players--;

	return AvgPing / Players;
}

void DrawStrip(int y, int Height, qboolean Fill, qboolean Top, qboolean Bottom, float *FillC, float *BoarderC)
{

	if (Fill) {
		CG_FillRect((SCREEN_WIDTH - SB_WIDTH) / 2, y, SB_WIDTH, Height + SB_PADDING * 2, FillC);
	}

	if (Top)
		CG_DrawCleanLine((SCREEN_WIDTH - SB_WIDTH) / 2, y, SB_WIDTH, 1, BoarderC);

	if (Bottom)
		CG_DrawCleanLine((SCREEN_WIDTH - SB_WIDTH) / 2, y + Height + SB_PADDING * 2, SB_WIDTH, 1, BoarderC);

	CG_DrawCleanSides((SCREEN_WIDTH - SB_WIDTH) / 2, y, SB_WIDTH, Height + SB_PADDING * 2, 1, BoarderC);

}

void DrawLeftStripText(int y, int Height, char *Text, int maxChars, float *Color)
{
	CG_DrawStringExt((SCREEN_WIDTH - SB_WIDTH) / 2 + 2, y + (Height + SB_PADDING * 2 - SB_FONTSIZEH) / 2, Text, Color, qtrue,
			 qfalse,	// Shadow?
			 SB_FONTSIZEW,	// charWidth
			 SB_FONTSIZEH,	// charHeight
			 maxChars);	// MaxChars
}

void DrawStripText(int y, int x, int Height, char *Text, int maxChars, float *Color)
{
	CG_DrawStringExt((SCREEN_WIDTH - SB_WIDTH) / 2 + x, y + (Height + SB_PADDING * 2 - SB_FONTSIZEH) / 2, Text, Color, qfalse,
			 qfalse,	// Shadow?
			 SB_FONTSIZEW,	// charWidth
			 SB_FONTSIZEH,	// charHeight
			 maxChars);	// MaxChars
}

void DrawRightStripText(int y, int Height, char *Text, int maxChars, float *Color)
{
	int Len;

	Len = CG_DrawStrlen(Text);
	CG_DrawStringExt(((SCREEN_WIDTH + SB_WIDTH) / 2) - (Len * SB_FONTSIZEW) - 2, y + (Height + SB_PADDING * 2 - SB_FONTSIZEH) / 2, Text, Color, qtrue,
			 qfalse,	// Shadow?
			 SB_FONTSIZEW,	// charWidth
			 SB_FONTSIZEH,	// charHeight
			 maxChars);	// MaxChars
}

void DrawCenterStripText(int y, int Height, char *Text, int maxChars, float *Color)
{
	int Len;

	Len = CG_DrawStrlen(Text);
	CG_DrawStringExt((SCREEN_WIDTH - Len * SB_FONTSIZEW) / 2, y + (Height + SB_PADDING * 2 - SB_FONTSIZEH) / 2, Text, Color, qtrue,	// Force color?
			 qfalse,	// Shadow?
			 SB_FONTSIZEW,	// charWidth
			 SB_FONTSIZEH,	// charHeight
			 maxChars);	// MaxChars
}

static void CG_DrawTeamplayClientScore(int y, score_t * score, float *Fill, float *Boarder, float *Color)
{
	char Tmp[128], MMstr[128];
	clientInfo_t *ci;
	float FillColor[4], TextColor[4];
	int l;

	if (score->client < 0 || score->client >= cgs.maxclients) {
		Com_Printf("Bad score->client: %i\n", score->client);
		return;
	}

	ci = &cgs.clientinfo[score->client];

	for (l = 0; l < 4; l++) {
		FillColor[l] = Fill[l];
		TextColor[l] = Color[l];
	}

	if (score->client == cg.clientNum)
		FillColor[3] += 0.2f;

	if (FillColor[3] > 1)
		FillColor[3] = 1;

	// Dead?
	if (!score->alive) {
		TextColor[0] *= 0.5f;
		TextColor[1] *= 0.5f;
		TextColor[2] *= 0.5f;
	}

	DrawStrip(y, SB_FONTSIZEH, qtrue, qfalse, qfalse, FillColor, Boarder);

	Com_sprintf(Tmp, 128, "%5i  %s", score->score, ci->name);
	DrawLeftStripText(y, SB_FONTSIZEH, Tmp, 27, TextColor);
	if (score->ping != -1) {
		Com_sprintf(Tmp, 128, "%4i  %4i  %6i", score->time, score->ping, score->damage);
		DrawRightStripText(y, SB_FONTSIZEH, Tmp, 100, TextColor);
	} else {
		DrawRightStripText(y, SB_FONTSIZEH, "CONNECTING     ", 100, TextColor);
	}


	memset(MMstr, 0, sizeof(MMstr));

	if (score->referee)
		strcat(MMstr, "^3[REF]^7");
	if (score->captain)
		strcat(MMstr, "[CAPTAIN]");
	if (score->sub)
		strcat(MMstr, "[SUB]");

	if ( CG_DrawStrlen(MMstr) )
		DrawStripText(y, -(SB_FONTSIZEW * ((signed)CG_DrawStrlen(MMstr) + 1)), SB_FONTSIZEH, MMstr, 100, colorWhite);

	if (ci->powerups & ( 1 << PW_REDFLAG ) )
		CG_DrawFlagModel( (SCREEN_WIDTH + SB_WIDTH) / 2 + 2, y, SB_FONTSIZEH + SB_PADDING * 2, 
			SB_FONTSIZEH + SB_PADDING * 2, TEAM_RED, qfalse );
	else if (ci->powerups & ( 1 << PW_BLUEFLAG ) )
		CG_DrawFlagModel( (SCREEN_WIDTH + SB_WIDTH) / 2 + 2, y, SB_FONTSIZEH + SB_PADDING * 2,
			SB_FONTSIZEH + SB_PADDING * 2, TEAM_BLUE, qfalse );
}

/*
=================
CG_TeamScoreboard 
	- By NiceAss
=================
*/
static int CG_TeamplayScoreboard(void)
{
	clientInfo_t *ci;
	int i;

	int Reds, Blues, Spectators;
	int RedSubs, BlueSubs;

	float Alpha;
	score_t *Score;
	int y;
	int Alternate, First;
	int Ping, Frags, Damage;	// Averages and totals
	char Tmp[128];

	// Colors
	vec4_t RedL, BlueL, GreyL, BlackL;
	vec4_t RedD, BlueD, GreyD;

	// Sine wave fading
	if (cg.time > cg.scoreStartTime + 300) {
		Alpha = cos((cg.time - cg.scoreStartTime) / 400.0f) * 0.15f + 0.85f;
	} else {
		// Fade in
		Alpha = (float) (cg.time - cg.scoreStartTime) / (float) 300;
		if (Alpha > 1.0f)
			Alpha = 1.0f;
	}

	// NiceAss: Update scoreboard while open every 2 seconds
	if (cg.scoresRequestTime + 2000 < cg.time) {
		cg.scoresRequestTime = cg.time;
		trap_SendClientCommand("score");
	}

	MAKERGBA(BlackL, 0.0f, 0.0f, 0.0f, 0.8f * Alpha);

	CG_TeamColor(TEAM_RED, RedD);
	RedD[0] *= 0.8f;
	RedD[1] *= 0.8f;
	RedD[2] *= 0.8f;
	RedD[3] *= (0.8f * Alpha);
	CG_TeamColor(TEAM_BLUE, BlueD);
	BlueD[0] *= 0.8f;
	BlueD[1] *= 0.8f;
	BlueD[2] *= 0.8f;
	BlueD[3] *= (0.8f * Alpha);
	MAKERGBA(GreyD, 0.3f, 0.3f, 0.3f, 0.84f * Alpha);
	CG_TeamColor(TEAM_RED, RedL);
	RedL[0] *= 0.8f;
	RedL[1] *= 0.8f;
	RedL[2] *= 0.8f;
	RedL[3] *= (0.8f * Alpha);
	CG_TeamColor(TEAM_BLUE, BlueL);
	BlueL[0] *= 0.8f;
	BlueL[1] *= 0.8f;
	BlueL[2] *= 0.8f;
	BlueL[3] *= (0.8f * Alpha);
	MAKERGBA(GreyL, 0.3f, 0.3f, 0.3f, 0.4f * Alpha);

	Reds = Blues = Spectators = RedSubs = BlueSubs = 0;

	// Get totals for red/blue/spectators and subs
	for (i = 0; i < cg.numScores; i++) {
		Score = &cg.scores[i];
		ci = &cgs.clientinfo[Score->client];

		if (Score->sub == TEAM_RED)
			RedSubs++;
		else if (Score->sub == TEAM_BLUE)
			BlueSubs++;
		else if (ci->team == TEAM_RED)
			Reds++;
		else if (ci->team == TEAM_BLUE)
			Blues++;
		else if (ci->team == TEAM_SPECTATOR)
			Spectators++;
	}

	y = 20;			// Starting height.

	// NiceAss: The matchmode match time
	if (cg_RQ3_matchmode.integer) {
		int mins, secs;
		char Time[16];
		char *pingFair;

		mins = (int) floor(cg.matchTime / 60.0f);
		secs = cg.matchTime - (mins * 60);
		Com_sprintf(Time, 16, "%d:%02d", mins, secs);

		if (abs(TeamAveragePing(TEAM_RED) - TeamAveragePing(TEAM_BLUE)) <= 40)
			pingFair = "PINGS FAIR";
		else
			pingFair = "PINGS UNFAIR";

		DrawRightStripText(y, SB_FONTSIZEH, va("%s - Matchtime: %s", pingFair, Time), 100, colorWhite);
		y += SB_FONTSIZEH + SB_PADDING * 2 + 2;
	}

	// NiceAss: Deathmatch scoreboard:
	if (cg.scoreTPMode == 1 || cgs.gametype < GT_TEAM) {
		vec3_t	headAngles;
		DrawStrip(y, SB_FONTSIZEH, qtrue, qtrue, qtrue, BlackL, colorWhite);
		DrawLeftStripText(y, SB_FONTSIZEH, "Frags  Name", 100, colorWhite);
		DrawRightStripText(y, SB_FONTSIZEH, "Time  Ping  Damage", 100, colorWhite);
		y += SB_FONTSIZEH + SB_PADDING * 2 + 2;

		VectorSet(headAngles, 0, sin(cg.time * 0.002f) * 20.0f + 180.0f, 0);

		First = 0;
		for (i = 0; i < cg.numScores; i++) {
			Score = &cg.scores[i];
			ci = &cgs.clientinfo[Score->client];
			CG_DrawTeamplayClientScore(y, Score, GreyL, colorWhite, colorWhite);

			if (First == 0)
				DrawStrip(y, SB_FONTSIZEH, qfalse, qtrue, qfalse, GreyL, colorWhite);

			y += SB_FONTSIZEH + SB_PADDING * 2;
			First = 1;
		}
		DrawStrip(y - (SB_FONTSIZEH + SB_PADDING * 2), SB_FONTSIZEH, qfalse, qfalse, qtrue, GreyL, colorWhite);

		return Reds + Blues + ceil(Spectators / 2);
	}

	// *************** RED TEAM ***************
	DrawStrip(y, SB_FONTSIZEH, qtrue, qtrue, qtrue, RedD, colorBlack);
	DrawLeftStripText(y, SB_FONTSIZEH, cg_RQ3_team1name.string, 100, colorWhite);

	if (cg_RQ3_matchmode.integer)
		DrawRightStripText(y, SB_FONTSIZEH, va("%d/%d - %s - Wins: %d", Reds, RedSubs,
						     cg.team1ready ? "Ready" : "Not Ready", cg.teamScores[0]), 
							 100, colorWhite);
	else
		DrawRightStripText(y, SB_FONTSIZEH, va("%d/%d - Wins: %d", Reds, RedSubs, cg.teamScores[0]), 100, colorWhite);


	CG_ScoreBoardHead (TEAM_RED, (SCREEN_WIDTH - SB_WIDTH) / 2 - 36, y, 34, 34);


	y += SB_FONTSIZEH + SB_PADDING * 2 + 2;

	DrawStrip(y, SB_FONTSIZEH, qtrue, qtrue, qtrue, GreyL, colorBlack);
	DrawLeftStripText(y, SB_FONTSIZEH, "Frags  Name", 100, colorWhite);
	DrawRightStripText(y, SB_FONTSIZEH, "Time  Ping  Damage", 100, colorWhite);
	y += SB_FONTSIZEH + SB_PADDING * 2;

	Ping = Frags = Damage = 0;
	if (Reds || RedSubs) {
		if (Reds) {
			y += 2;
			First = 0;
			for (i = 0; i < cg.numScores; i++) {
				Score = &cg.scores[i];
				ci = &cgs.clientinfo[Score->client];

				if (ci->team == TEAM_RED && Score->sub == 0) {
					CG_DrawTeamplayClientScore(y, Score, RedL, colorBlack, colorWhite);
					if (First == 0)
						DrawStrip(y, SB_FONTSIZEH, qfalse, qtrue, qfalse, RedL, colorBlack);
					y += SB_FONTSIZEH + SB_PADDING * 2;
					Ping += Score->ping;
					Frags += Score->score;
					Damage += Score->damage;
					First = 1;

				}
			}
			Ping /= Reds;
			DrawStrip(y - (SB_FONTSIZEH + SB_PADDING * 2), SB_FONTSIZEH, qfalse, qfalse, qtrue, RedL,
				  colorBlack);
		}
		// SUBS
		if (RedSubs) {
			y += 2;
			First = 0;
			for (i = 0; i < cg.numScores; i++) {
				Score = &cg.scores[i];
				ci = &cgs.clientinfo[Score->client];

				if (ci->team == TEAM_RED && Score->sub) {
					CG_DrawTeamplayClientScore(y, Score, RedL, colorBlack, colorWhite);
					if (First == 0)
						DrawStrip(y, SB_FONTSIZEH, qfalse, qtrue, qfalse, RedL, colorBlack);
					y += SB_FONTSIZEH + SB_PADDING * 2;
					Ping += Score->ping;
					Frags += Score->score;
					Damage += Score->damage;
					First = 1;

				}
			}
			DrawStrip(y - (SB_FONTSIZEH + SB_PADDING * 2), SB_FONTSIZEH, qfalse, qfalse, qtrue, RedL,
				  colorBlack);
		}

		y += 2;

		if (cg_RQ3_matchmode.integer)
			Ping = TeamAveragePing(TEAM_RED);

		Com_sprintf(Tmp, 128, "%5d", Frags);
		DrawStrip(y, SB_FONTSIZEH, qtrue, qtrue, qtrue, GreyL, colorBlack);
		DrawLeftStripText(y, SB_FONTSIZEH, Tmp, 100, colorWhite);
		Com_sprintf(Tmp, 128, "%4d  %6d", Ping, Damage);
		DrawRightStripText(y, SB_FONTSIZEH, Tmp, 100, colorWhite);
		DrawCenterStripText(y, SB_FONTSIZEH, "Totals", 20, colorWhite);
	} else {
		y += 2;
		DrawStrip(y, SB_FONTSIZEH, qtrue, qtrue, qtrue, RedL, colorBlack);
		DrawCenterStripText(y, SB_FONTSIZEH, "No team members", 100, colorWhite);
	}

	// *************** BLUE TEAM ************
	y += SB_FONTSIZEH * 2;
	DrawStrip(y, SB_FONTSIZEH, qtrue, qtrue, qtrue, BlueD, colorBlack);
	DrawLeftStripText(y, SB_FONTSIZEH, cg_RQ3_team2name.string, 100, colorWhite);

	if (cg_RQ3_matchmode.integer)
		DrawRightStripText(y, SB_FONTSIZEH, va("%d/%d - %s - Wins: %d", Blues, BlueSubs,
						       cg.team2ready ? "Ready" : "Not Ready", cg.teamScores[1]), 
							   100, colorWhite);
	else
		DrawRightStripText(y, SB_FONTSIZEH, va("%d/%d - Wins: %d", Blues, BlueSubs, cg.teamScores[1]), 100, colorWhite);
	
	CG_ScoreBoardHead (TEAM_BLUE, (SCREEN_WIDTH - SB_WIDTH) / 2 - 36, y, 34, 34);

	y += SB_FONTSIZEH + SB_PADDING * 2 + 2;

	DrawStrip(y, SB_FONTSIZEH, qtrue, qtrue, qtrue, GreyL, colorBlack);
	DrawLeftStripText(y, SB_FONTSIZEH, "Frags  Name", 100, colorWhite);
	DrawRightStripText(y, SB_FONTSIZEH, "Time  Ping  Damage", 100, colorWhite);
	y += SB_FONTSIZEH + SB_PADDING * 2;

	Ping = Frags = Damage = 0;
	if (Blues || BlueSubs) {
		if (Blues) {
			y += 2;
			First = 0;
			for (i = 0; i < cg.numScores; i++) {
				Score = &cg.scores[i];
				ci = &cgs.clientinfo[Score->client];

				if (ci->team == TEAM_BLUE && Score->sub == 0) {
					CG_DrawTeamplayClientScore(y, Score, BlueL, colorBlack, colorWhite);
					if (First == 0)
						DrawStrip(y, SB_FONTSIZEH, qfalse, qtrue, qfalse, BlueL, colorBlack);
					y += SB_FONTSIZEH + SB_PADDING * 2;
					Ping += Score->ping;
					Frags += Score->score;
					Damage += Score->damage;
					First = 1;
				}
			}
			Ping /= Blues;
			DrawStrip(y - (SB_FONTSIZEH + SB_PADDING * 2), SB_FONTSIZEH, qfalse, qfalse, qtrue, BlueL,
				  colorBlack);
		}
		// SUBS:
		if (BlueSubs) {
			y += 2;
			First = 0;
			for (i = 0; i < cg.numScores; i++) {
				Score = &cg.scores[i];
				ci = &cgs.clientinfo[Score->client];

				if (ci->team == TEAM_BLUE && Score->sub) {
					CG_DrawTeamplayClientScore(y, Score, BlueL, colorBlack, colorWhite);
					if (First == 0)
						DrawStrip(y, SB_FONTSIZEH, qfalse, qtrue, qfalse, BlueL, colorBlack);
					y += SB_FONTSIZEH + SB_PADDING * 2;
					Ping += Score->ping;
					Frags += Score->score;
					Damage += Score->damage;
					First = 1;
				}
			}
			DrawStrip(y - (SB_FONTSIZEH + SB_PADDING * 2), SB_FONTSIZEH, qfalse, qfalse, qtrue, BlueL,
				  colorBlack);
		}
		y += 2;

		if (cg_RQ3_matchmode.integer)
			Ping = TeamAveragePing(TEAM_BLUE);

		Com_sprintf(Tmp, 128, "%5d", Frags);
		DrawStrip(y, SB_FONTSIZEH, qtrue, qtrue, qtrue, GreyL, colorBlack);
		DrawLeftStripText(y, SB_FONTSIZEH, Tmp, 100, colorWhite);
		Com_sprintf(Tmp, 128, "%4d  %6d", Ping, Damage);
		DrawRightStripText(y, SB_FONTSIZEH, Tmp, 100, colorWhite);
		DrawCenterStripText(y, SB_FONTSIZEH, "Totals", 20, colorWhite);
	} else {
		y += 2;
		DrawStrip(y, SB_FONTSIZEH, qtrue, qtrue, qtrue, BlueL, colorBlack);
		DrawCenterStripText(y, SB_FONTSIZEH, "No team members", 100, colorWhite);
	}

	if ( cg_RQ3_matchmode.integer && cg.refready != -1 ) {
		y += SB_FONTSIZEH * 2;
		DrawStrip(y, SB_FONTSIZEH, qtrue, qtrue, qtrue, BlackL, colorWhite);
		DrawRightStripText(y, SB_FONTSIZEH, 
			cg.refready ? "Referee Ready" : "Referee Not Ready", 100, colorWhite);
	}

	// *************** SPECTATORS ************
	if (Spectators) {
		Alternate = 1;
		First = 0;

		y += SB_FONTSIZEH * 2;
		DrawStrip(y, SB_FONTSIZEH, qtrue, qtrue, qtrue, GreyD, colorBlack);
		DrawLeftStripText(y, SB_FONTSIZEH, "Spectators", 100, colorWhite);
		y += SB_FONTSIZEH + SB_PADDING * 2 + 2;

		for (i = 0; i < cg.numScores; i++) {
			Score = &cg.scores[i];
			ci = &cgs.clientinfo[Score->client];

			if (ci->team != TEAM_SPECTATOR)
				continue;

			if (First == 0)
				DrawStrip(y, SB_FONTSIZEH, qfalse, qtrue, qfalse, GreyL, colorBlack);
			else
				DrawStrip(y, SB_FONTSIZEH, qtrue, qfalse, qfalse, GreyL, colorBlack);

			if (Score->referee) {
				if (Alternate == 1)
					DrawStripText(y, -(SB_FONTSIZEW * 6), SB_FONTSIZEH, "^3[REF]^7", 100, colorWhite);
				else
					DrawStripText(y, SB_WIDTH + SB_FONTSIZEW, SB_FONTSIZEH, "^3[REF]^7", 100, colorWhite);
			}
			
			
			if (Alternate == 1) {
				DrawLeftStripText(y, SB_FONTSIZEH, ci->name, 20, colorWhite);
			} else {
				DrawRightStripText(y, SB_FONTSIZEH, ci->name, 20, colorWhite);
				y += SB_FONTSIZEH + SB_PADDING * 2;
			}
			Alternate = -Alternate;
			First = 1;
		}

		if (Alternate == 1)
			DrawStrip(y - (SB_FONTSIZEH + SB_PADDING * 2), SB_FONTSIZEH, qfalse, qfalse, qtrue, GreyL,
				  colorBlack);
		else
			DrawStrip(y, SB_FONTSIZEH, qfalse, qfalse, qtrue, GreyL, colorBlack);
	}

	return Reds + Blues + ceil(Spectators / 2);
}

/*
=================
CG_DrawScoreboard

Draw the normal in-game scoreboard
=================
*/
qboolean CG_DrawOldScoreboard(void)
{

	// don't draw amuthing if the menu or console is up
	if (cg_paused.integer) {
		cg.deferredPlayerLoading = 0;
		return qfalse;
	}

	if (cgs.gametype == GT_SINGLE_PLAYER && cg.predictedPlayerState.pm_type == PM_INTERMISSION) {
		cg.deferredPlayerLoading = 0;
		return qfalse;
	}

	if (!cg.showScores)
		return qfalse;

	// don't draw scoreboard during death while warmup up
	if (cg.warmup) {
		return qfalse;
	}

	CG_TeamplayScoreboard();

	// load any models that have been deferred
	if (++cg.deferredPlayerLoading > 10) {
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

static void CG_CenterGiantLine(float y, const char *string)
{
	float x;
	vec4_t color;

	color[0] = 1;
	color[1] = 1;
	color[2] = 1;
	color[3] = 1;

	x = 0.5 * (640 - GIANT_WIDTH * CG_DrawStrlen(string));

	CG_DrawStringExt(x, y, string, color, qtrue, qtrue, GIANT_WIDTH, GIANT_HEIGHT, 0);
}

/*
=================
CG_DrawTourneyScoreboard

Draw the oversize scoreboard for tournements
=================
*/

void CG_DrawOldTourneyScoreboard(void)
{
	const char *s;
	vec4_t color;
	int min, tens, ones;
	clientInfo_t *ci;
	int y;
	int i;

	// request more scores regularly
	if (cg.scoresRequestTime + 2000 < cg.time) {
		cg.scoresRequestTime = cg.time;
		trap_SendClientCommand("score");
	}

	color[0] = 1;
	color[1] = 1;
	color[2] = 1;
	color[3] = 1;

	// draw the dialog background
	color[0] = color[1] = color[2] = 0;
	color[3] = 1;
	CG_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color);

	// print the mesage of the day
	s = CG_ConfigString(CS_MOTD);
	if (!s[0]) {
		s = "Scoreboard";
	}
	// print optional title
	CG_CenterGiantLine(8, s);

	// print server time
	ones = cg.time / 1000;
	min = ones / 60;
	ones %= 60;
	tens = ones / 10;
	ones %= 10;
	s = va("%i:%i%i", min, tens, ones);

	CG_CenterGiantLine(64, s);

	// print the two scores

	y = 160;
	if (cgs.gametype >= GT_TEAM) {
		//
		// teamplay scoreboard
		//
		CG_DrawStringExt(8, y, "Red Team", color, qtrue, qtrue, GIANT_WIDTH, GIANT_HEIGHT, 0);
		s = va("%i", cg.teamScores[0]);
		CG_DrawStringExt(632 - GIANT_WIDTH * strlen(s), y, s, color, qtrue, qtrue, GIANT_WIDTH, GIANT_HEIGHT,
				 0);

		y += 64;

		CG_DrawStringExt(8, y, "Blue Team", color, qtrue, qtrue, GIANT_WIDTH, GIANT_HEIGHT, 0);
		s = va("%i", cg.teamScores[1]);
		CG_DrawStringExt(632 - GIANT_WIDTH * strlen(s), y, s, color, qtrue, qtrue, GIANT_WIDTH, GIANT_HEIGHT,
				 0);
	} else {
		//
		// free for all scoreboard
		//
		for (i = 0; i < MAX_CLIENTS; i++) {
			ci = &cgs.clientinfo[i];
			if (!ci->infoValid) {
				continue;
			}
			if (ci->team != TEAM_FREE) {
				continue;
			}

			CG_DrawStringExt(8, y, ci->name, color, qtrue, qtrue, GIANT_WIDTH, GIANT_HEIGHT, 0);
			s = va("%i", ci->score);
			CG_DrawStringExt(632 - GIANT_WIDTH * strlen(s), y, s, color, qtrue, qtrue, GIANT_WIDTH,
					 GIANT_HEIGHT, 0);
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
	int i, offset;
	float color[4], Alpha, Alpha2;
	int size;
	char String[80];

	if (cg.time > cg.wstatsStartTime + 300) {
		Alpha = (cos((cg.time - cg.wstatsStartTime) / 400.0f) + 1.0f) * 0.25f + 0.5f;
		Alpha2 = (cos((cg.time - cg.wstatsStartTime) / 400.0f) + 1.0f) * 0.5f;
	} else {
		Alpha = (float) (cg.time - cg.wstatsStartTime) / (float) 300;
		if (Alpha > 1.0f)
			Alpha = 1.0f;
	}
	//make room for 8 weapon stats
	size = (10 * 20) + WS_PADDING;

	// Score bar - Red:
	MAKERGBA(color, 1.0f, 0.5f, 0.5f, 0.7f * Alpha);
	CG_FillRect(WS_LEFTSIDE, WS_TOP, WS_WIDTH, SMALLCHAR_HEIGHT + (WS_PADDING * 2), color);

	//Box for scores, etc
	MAKERGBA(color, 0.55f, 0.55f, 0.55f, 0.7f * Alpha);
	CG_FillRect(WS_LEFTSIDE, WS_TOP + SMALLCHAR_HEIGHT + (WS_PADDING * 2),
		    WS_WIDTH, SMALLCHAR_HEIGHT + (WS_PADDING * 2), color);

	//Box for weapon stuff
	MAKERGBA(color, 0.6f, 0.5f, 0.5f, 0.5f * Alpha);
	CG_FillRect(WS_LEFTSIDE, WS_TOP + (SMALLCHAR_HEIGHT + (WS_PADDING * 2)) * 2, WS_WIDTH, size, color);
	//box for weapon stuff
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 0.8f);
	CG_DrawCleanRect(WS_LEFTSIDE, WS_TOP,
			 WS_WIDTH, (SMALLCHAR_HEIGHT + WS_PADDING * 2) * 2 + size, WS_LINE_WIDTH, color);

	//box for score stuff
	CG_DrawCleanRect(WS_LEFTSIDE, WS_TOP + SMALLCHAR_HEIGHT + (WS_PADDING * 2),
			 WS_WIDTH, (SMALLCHAR_HEIGHT + WS_PADDING * 2), WS_LINE_WIDTH, color);

	//Red box for Weapon stats
	MAKERGBA(color, 1.0f, 0.5f, 0.5f, 0.7f * Alpha);
	CG_FillRect(WS_LEFTSIDE, WS_TOP + (SMALLCHAR_HEIGHT + (WS_PADDING * 2)) * 2, WS_WIDTH, SMALLCHAR_HEIGHT, color);
	//White box for the weapon names, etc
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 0.8f);
	CG_DrawCleanRect(WS_LEFTSIDE, WS_TOP - 1 + (SMALLCHAR_HEIGHT + (WS_PADDING * 2)) * 2,
			 WS_WIDTH, SMALLCHAR_HEIGHT + 1, WS_LINE_WIDTH, color);

	//Fill in the top bar 
	offset = 7;
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6, WS_TOP + WS_PADDING, "Score", color);

	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * 7, WS_TOP + WS_PADDING, "Net", color);

	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * 7 * 2, WS_TOP + WS_PADDING, "K/D/S", color);

	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * 7 * 3, WS_TOP + WS_PADDING, "TK's", color);

//  MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
//      CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * 7 * 4, WS_TOP + WS_PADDING,
//                                                      "Efficiency", color);

	Com_sprintf(String, sizeof(String), "%4i", cg.snap->ps.persistant[PERS_SCORE]);

	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH, WS_TOP + WS_PADDING * 3 + SMALLCHAR_HEIGHT,
				String, color);

	Com_sprintf(String, sizeof(String), "%3i",
		    cg.snap->ps.persistant[PERS_SCORE] - cg.snap->ps.persistant[PERS_KILLED]);

	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * 7 - 1, WS_TOP + WS_PADDING * 3 + SMALLCHAR_HEIGHT,
				String, color);

	Com_sprintf(String, sizeof(String), "%i/%i/%i", cg.records[REC_KILLS], cg.snap->ps.persistant[PERS_KILLED],
		    cg.records[REC_SUICIDES]);

	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * 7 * 2, WS_TOP + WS_PADDING * 3 + SMALLCHAR_HEIGHT,
				String, color);

	Com_sprintf(String, sizeof(String), "%4i", cg.records[REC_TEAMKILLS]);

	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * 7 * 3, WS_TOP + WS_PADDING * 3 + SMALLCHAR_HEIGHT,
				String, color);

	i = 2;

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

	i = 2;
	offset = 15;
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, "Accuracy", color);

	Com_sprintf(String, sizeof(String), "%.1f%%",
		    100 * (float) cg.records[REC_KNIFESLASHHITS] /
		    (cg.records[REC_KNIFESLASHSHOTS] ? cg.records[REC_KNIFESLASHSHOTS] : 1));
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%.1f%%",
		    100 * (float) cg.records[REC_KNIFETHROWHITS] /
		    (cg.records[REC_KNIFETHROWSHOTS] ? cg.records[REC_KNIFETHROWSHOTS] : 1));
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%.1f%%",
		    100 * (float) cg.records[REC_MK23HITS] /
		    (cg.records[REC_MK23SHOTS] ? cg.records[REC_MK23SHOTS] : 1));
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%.1f%%",
		    100 * (float) cg.records[REC_MP5HITS] / (cg.records[REC_MP5SHOTS] ? cg.records[REC_MP5SHOTS] : 1));
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%.1f%%",
		    100 * (float) cg.records[REC_M3HITS] / (cg.records[REC_M3SHOTS] ? cg.records[REC_M3SHOTS] : 1));
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%.1f%%",
		    100 * (float) cg.records[REC_M4HITS] / (cg.records[REC_M4SHOTS] ? cg.records[REC_M4SHOTS] : 1));
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%.1f%%",
		    100 * (float) cg.records[REC_HANDCANNONHITS] /
		    (cg.records[REC_HANDCANNONSHOTS] ? cg.records[REC_HANDCANNONSHOTS] : 1));
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%.1f%%",
		    100 * (float) cg.records[REC_SSG3000HITS] /
		    (cg.records[REC_SSG3000SHOTS] ? cg.records[REC_SSG3000SHOTS] : 1));
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%.1f%%",
		    100 * (float) cg.records[REC_AKIMBOHITS] /
		    (cg.records[REC_AKIMBOSHOTS] ? cg.records[REC_AKIMBOSHOTS] : 1));
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%.1f%%",
		    100 * (float) cg.records[REC_GRENADEHITS] /
		    (cg.records[REC_GRENADESHOTS] ? cg.records[REC_GRENADESHOTS] : 1));
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	//Hits
	i = 2;
	offset = 25;
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, "Hits", color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_KNIFESLASHHITS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_KNIFETHROWHITS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_MK23HITS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_MP5HITS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_M3HITS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_M4HITS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_HANDCANNONHITS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_SSG3000HITS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_AKIMBOHITS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_GRENADEHITS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_KICKHITS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	//Shots
	i = 2;
	offset = 32;
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * (offset - 1),
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, "Shots", color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_KNIFESLASHSHOTS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_KNIFETHROWSHOTS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_MK23SHOTS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_MP5SHOTS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_M3SHOTS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_M4SHOTS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_HANDCANNONSHOTS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_SSG3000SHOTS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_AKIMBOSHOTS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_GRENADESHOTS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	//Kills
	i = 2;
	offset = 39;
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * (offset - 1),
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, "Kills", color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_KNIFESLASHKILLS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_KNIFETHROWKILLS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_MK23KILLS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_MP5KILLS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_M3KILLS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_M4KILLS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_HANDCANNONKILLS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_SSG3000KILLS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_AKIMBOKILLS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_GRENADEKILLS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_KICKKILLS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	//Deaths
	i = 2;
	offset = 47;
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * (offset - 2),
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, "Deaths", color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_KNIFESLASHDEATHS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_KNIFETHROWDEATHS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_MK23DEATHS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_MP5DEATHS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_M3DEATHS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_M4DEATHS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_HANDCANNONDEATHS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_SSG3000DEATHS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_AKIMBODEATHS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_GRENADEDEATHS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	Com_sprintf(String, sizeof(String), "%4d", cg.records[REC_KICKDEATHS]);
	MAKERGBA(color, 1.0f, 1.0f, 1.0f, 1.0f);
	CG_DrawSmallStringColor(WS_LEFTSIDE + 6 + SMALLCHAR_WIDTH * offset,
				WS_TOP + WS_PADDING * 4 + SMALLCHAR_HEIGHT * i++, String, color);

	if (cg.wstatsRequestTime + 3000 < cg.time) {
		// the scores are more than two seconds out of data,
		// so request new ones
		cg.wstatsRequestTime = cg.time;
		trap_SendClientCommand("wstats");
	}

	return;
}

/*
	CG_FindHead			By NiceAss

	Used to parse the model cvars and register the model and skin. It
	then displays it.
*/

void CG_ScoreBoardHead(team_t team, float x, float y, float w, float h) {
	char		modelskin[128], filename[128];
	char		*model = NULL, *skin = NULL;
	qhandle_t	headIcon; //headModel, headSkin;

	//vec3_t		Angles;

	if (team == TEAM_RED) 
		strcpy(modelskin, cg_RQ3_team1model.string);
	else
		strcpy(modelskin, cg_RQ3_team2model.string);

	skin = strchr(modelskin, '/');

	if (!skin)
		return;

	*skin = '\0';
	skin++;
	model = modelskin;

	//********************** LOAD HEAD ***************************
	/*
	Com_sprintf(filename, 128, "models/players/%s/head.md3", model);
	headModel = trap_R_RegisterModel( filename );

	if (!headModel)
		return;

	Com_sprintf(filename, 128, "models/players/%s/head_%s.skin", model, skin);
	headSkin = trap_R_RegisterSkin( filename );

	if (!headSkin)
		return;

	VectorClear( Angles );
	Angles[1] = sin(cg.time * 0.0025f) * 20.0f + 180.0f;
	Angles[0] = cos(cg.time * 0.002f) * 8.0f;

	CG_DrawScoreBoardHead(x, y, w, h, headModel, headSkin, Angles);
	*/
	Com_sprintf(filename, 128, "models/players/%s/icon_%s.md3", model, skin);
	headIcon = trap_R_RegisterShaderNoMip( filename );

	if (!headIcon)
		return;

	CG_DrawPic(x, y, w, h, headIcon);
}


/*
	CG_DrawScoreBoardHead			By NiceAss

	Displays the player model. This is just an altered CG_DrawHead.
*/
/*
void CG_DrawScoreBoardHead(float x, float y, float w, float h, 
						   qhandle_t headModel, qhandle_t headSkin, 
						   vec3_t headAngles)
{
	float len;
	vec3_t origin;
	vec3_t mins, maxs;

	if (!headModel)
		return;

	// offset the origin y and z to center the head
	trap_R_ModelBounds(headModel, mins, maxs);

	origin[2] = -0.5 * (mins[2] + maxs[2]);
	origin[1] = 0.5 * (mins[1] + maxs[1]);

	// calculate distance so the head nearly fills the box
	// assume heads are taller than wide
	len = 0.7 * (maxs[2] - mins[2]);
	origin[0] = len / 0.268;	// len / tan( fov/2 )

	CG_Draw3DModel(x, y, w, h, headModel, headSkin, origin, headAngles);


}
*/
