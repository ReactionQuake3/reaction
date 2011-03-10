//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.80  2005/09/07 20:29:05  makro
// Stuff I can't remember
//
// Revision 1.79  2005/02/15 16:33:38  makro
// Tons of updates (entity tree attachment system, UI vectors)
//
// Revision 1.78  2003/09/19 21:22:52  makro
// Flares
//
// Revision 1.77  2003/09/19 00:54:23  makro
// Flares again
//
// Revision 1.76  2003/09/18 19:05:10  makro
// Lens flares
//
// Revision 1.75  2003/09/17 23:49:29  makro
// Lens flares. Opendoor trigger_multiple fixes
//
// Revision 1.74  2003/09/10 21:40:35  makro
// Cooler breath puffs. Locked r_fastSky on maps with global fog.
// Some other things I can't remember.
//
// Revision 1.73  2003/08/10 20:13:26  makro
// no message
//
// Revision 1.72  2003/04/19 17:41:26  jbravo
// Applied changes that where in 1.29h -> 1.32b gamecode.
//
// Revision 1.71  2003/03/09 21:30:38  jbravo
// Adding unlagged.   Still needs work.
//
// Revision 1.70  2002/10/26 22:03:43  jbravo
// Made TeamDM work RQ3 style.
//
// Revision 1.69  2002/10/21 21:03:32  niceass
// ref ready code
//
// Revision 1.68  2002/10/21 21:01:49  niceass
// ref ready code
//
// Revision 1.67  2002/09/29 16:06:44  jbravo
// Work done at the HPWorld expo
//
// Revision 1.66  2002/09/17 20:17:12  blaze
// Fixed up the cg_rq3_autoaction to include the map name, and removed the player name since it was broken anyways
//
// Revision 1.65  2002/08/28 18:52:09  jbravo
// Added the Keanu male radio sound set.
//
// Revision 1.64  2002/08/25 00:45:04  niceass
// q3f atmosphere
//
// Revision 1.63  2002/08/24 07:59:23  niceass
// new scoreboard info for refs
//
// Revision 1.62  2002/08/22 03:29:36  niceass
// countdown code added
//
// Revision 1.61  2002/08/21 07:00:07  jbravo
// Added CTB respawn queue and fixed game <-> cgame synch problem in CTB
//
// Revision 1.60  2002/08/07 03:35:57  jbravo
// Added dynamic radio and stopped all radio usage during lca
//
// Revision 1.59  2002/07/26 06:21:43  jbravo
// Fixed the MM settings stuff so it works on remote servers also.
// Removed the MM_NAMES_COLOR since it broke on nicks with color in them.
//
// Revision 1.58  2002/07/20 02:25:53  jbravo
// Added the AQDT CTB sounds to the base radio paks
//
// Revision 1.57  2002/07/19 04:40:56  jbravo
// Added 2 new radio sets and ctb radio sound support
//
// Revision 1.56  2002/07/08 04:28:55  niceass
// removed deaths
//
// Revision 1.55  2002/07/02 20:22:35  jbravo
// Changed the files to use the right ui.
//
// Revision 1.54  2002/07/01 02:55:13  blaze
// change the format of the autorecorded demo name
//
// Revision 1.53  2002/06/30 17:33:01  jbravo
// New radio sounds and the 0wned sound was added.
//
// Revision 1.52  2002/06/16 20:06:13  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.51  2002/06/16 19:12:52  jbravo
// Removed the MISSIONPACK ifdefs and missionpack only code.
//
// Revision 1.50  2002/06/12 22:31:59  slicer
// Even better way to improve the Cvar Anti-Cheat System
//
// Revision 1.49  2002/06/12 15:30:24  slicer
// Improved and fixed the Anti-Cheat System
//
// Revision 1.48  2002/06/10 20:56:38  niceass
// scoreboard fix
//
// Revision 1.47  2002/06/10 14:02:31  slicer
// Removed rq3_cmd : ROUND , associated to cg_RQ3_team_round_going that wasn't being used
//
// Revision 1.46  2002/06/10 13:20:03  slicer
// RefID is now passed trought scoreboard, no more lca cvar, only cg.lca
//
// Revision 1.45  2002/06/03 00:47:06  niceass
// match scoreboard changes
//
// Revision 1.44  2002/06/02 22:23:57  makro
// no message
//
// Revision 1.43  2002/05/25 07:12:34  blaze
// moved breakables into a configstring so they work in demos
//
// Revision 1.42  2002/05/23 03:06:56  blaze
// Some changes to autoaction, still need to fix up a little bit more stuff relating to getting sent 2 screenshot requests
//
// Revision 1.41  2002/05/20 16:23:44  jbravo
// Fixed spec problem when noone is alive. Fixed kicking teammates bug
//
// Revision 1.40  2002/05/20 04:59:33  jbravo
// Lots of small fixes.
//
// Revision 1.39  2002/05/19 21:27:51  blaze
// added force and buoyancy to breakables
//
// Revision 1.38  2002/05/19 21:04:37  jbravo
// Tkok popup system
//
// Revision 1.37  2002/05/18 21:58:53  blaze
// cg_rq3_autoaction support
//
// Revision 1.36  2002/05/11 19:55:20  slicer
// Added sub and captain to the scoreboard parser
//
// Revision 1.35  2002/05/11 15:40:41  slicer
// Changed cg_RQ3_<team count> cvars to ui_RQ3_ and added a synch system for these
//
// Revision 1.34  2002/05/09 02:43:12  jbravo
// Fixing stuff and use cmd's
//
// Revision 1.33  2002/05/07 15:04:56  slicer
// Removed a debug message left behind..
//
// Revision 1.32  2002/05/06 21:40:37  slicer
// Added rq3_cmd
//
// Revision 1.31  2002/05/02 00:02:19  jbravo
// Added a fix for the incorrect weapon at spawns
//
// Revision 1.30  2002/05/01 18:44:36  jbravo
// Added a stuff command.  Needed for misc things.  See bottum of cmd_use in
// g_teamplay.c
//
// Revision 1.29  2002/04/30 11:20:12  jbravo
// Redid the teamcount cvars.
//
// Revision 1.28  2002/04/18 16:13:23  jbravo
// Scoreboard now shows green for live players and white for dead.
// Time should not get reset on deaths any more.
//
// Revision 1.27  2002/04/03 03:13:49  blaze
// NEW BREAKABLE CODE - will break all old breakables(wont appear in maps)
//
// Revision 1.26  2002/04/02 04:18:58  jbravo
// Made the TP scoreboard go down at round beginig (not for spectators) and
// pop up at intermission.  Also added special to the use command
//
// Revision 1.25  2002/03/30 23:20:10  jbravo
// Added damage in scoreboard.
//
// Revision 1.24  2002/03/26 10:32:52  jbravo
// Bye bye LCA lag
//
// Revision 1.23  2002/03/17 03:35:29  jbravo
// More radio tewaks and cleanups.
//
// Revision 1.22  2002/03/14 16:04:26  slicer
// Optimization on radio parsing
//
// Revision 1.21  2002/03/14 02:24:39  jbravo
// Adding radio :)
//
// Revision 1.20  2002/03/13 18:41:18  slicer
// Adjusted some of elder's unzoom code for the new sniper system ( server side )
//
// Revision 1.19  2002/03/03 21:44:01  blaze
// weapon stats, done, beta test for bugs
//
// Revision 1.18  2002/02/28 05:41:54  blaze
// weapons stats on client side
//
// Revision 1.17  2002/02/11 00:30:02  niceass
// LCA fix
//
// Revision 1.16  2002/02/10 08:17:08  niceass
// many changes to scoreboard (deaths/second mode)
//
// Revision 1.15  2002/01/12 20:00:49  hal9000
// Fixed a few more instances of strcmp(blah,NULL)
//
// Revision 1.14  2002/01/11 20:20:58  jbravo
// Adding TP to main branch
//
// Revision 1.13  2002/01/11 19:48:29  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.12  2001/12/31 16:28:41  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
// cg_servercmds.c -- reliably sequenced text commands sent by the server
// these are processed at snapshot transition time, so there will definately
// be a valid snapshot this frame

#include "cg_local.h"
#include "../ui/menudef.h"	// bk001205 - for Q3_ui as well

//Blaze: holds the id to name mapping of the breakables
extern char rq3_breakables[RQ3_MAX_BREAKABLES][80];
extern int trap_RealTime(qtime_t * qtime);
typedef struct {
	const char *order;
	int taskNum;
} orderTask_t;

static const orderTask_t validOrders[] = {
	{VOICECHAT_GETFLAG, TEAMTASK_OFFENSE},
	{VOICECHAT_OFFENSE, TEAMTASK_OFFENSE},
	{VOICECHAT_DEFEND, TEAMTASK_DEFENSE},
	{VOICECHAT_DEFENDFLAG, TEAMTASK_DEFENSE},
	{VOICECHAT_PATROL, TEAMTASK_PATROL},
	{VOICECHAT_CAMP, TEAMTASK_CAMP},
	{VOICECHAT_FOLLOWME, TEAMTASK_FOLLOW},
	{VOICECHAT_RETURNFLAG, TEAMTASK_RETRIEVE},
	{VOICECHAT_FOLLOWFLAGCARRIER, TEAMTASK_ESCORT}
};

static const int numValidOrders = ARRAY_LEN(validOrders);

/*
=================
CG_ParseScores

=================
*/
static void CG_ParseScores(void)
{
	int i, powerups;

	cg.numScores = atoi(CG_Argv(1));
	if (cg.numScores > MAX_CLIENTS) {
		cg.numScores = MAX_CLIENTS;
	}

	cg.teamScores[0] = atoi(CG_Argv(2));
	cg.teamScores[1] = atoi(CG_Argv(3));
	cg.team1ready = atoi(CG_Argv(4));
	cg.team2ready = atoi(CG_Argv(5));
	cg.matchTime = atoi(CG_Argv(6));
	cg.refready = atoi(CG_Argv(7));

	memset(cg.scores, 0, sizeof(cg.scores));
	for (i = 0; i < cg.numScores; i++) {
		//Elder: Leave as-is ... sent zeros by server
		cg.scores[i].client = atoi(CG_Argv(i * 12 + 8));
		cg.scores[i].score = atoi(CG_Argv(i * 12 + 9));
		cg.scores[i].ping = atoi(CG_Argv(i * 12 + 10));
		cg.scores[i].time = atoi(CG_Argv(i * 12 + 11));
		cg.scores[i].scoreFlags = atoi(CG_Argv(i * 12 + 12));
		powerups = atoi(CG_Argv(i * 12 + 13));
		cg.scores[i].accuracy = atoi(CG_Argv(i * 12 + 14));
		cg.scores[i].damage = atoi(CG_Argv(i * 12 + 15));
		cg.scores[i].alive = atoi(CG_Argv(i * 12 + 16));
		cg.scores[i].captain = atoi(CG_Argv(i * 12 + 17));
		cg.scores[i].sub = atoi(CG_Argv(i * 12 + 18));
		cg.scores[i].referee = atoi(CG_Argv(i * 12 + 19));

		if (cg.scores[i].client < 0 || cg.scores[i].client >= MAX_CLIENTS) {
			cg.scores[i].client = 0;
		}
		cgs.clientinfo[cg.scores[i].client].score = cg.scores[i].score;
		cgs.clientinfo[cg.scores[i].client].powerups = powerups;

		cg.scores[i].team = cgs.clientinfo[cg.scores[i].client].team;
	}
}

/*
=================
CG_ParseWeaponStats

=================
*/
static void CG_ParseWeaponStats(void)
{
	int i;

	i = 1;
	//Blaze: oi, damn fugly code
	cg.records[REC_KNIFETHROWSHOTS] = atoi(CG_Argv(i++));
	cg.records[REC_KNIFETHROWHITS] = atoi(CG_Argv(i++));
	cg.records[REC_KNIFESLASHSHOTS] = atoi(CG_Argv(i++));
	cg.records[REC_KNIFESLASHHITS] = atoi(CG_Argv(i++));
	cg.records[REC_MK23SHOTS] = atoi(CG_Argv(i++));
	cg.records[REC_MK23HITS] = atoi(CG_Argv(i++));
	cg.records[REC_M3SHOTS] = atoi(CG_Argv(i++));
	cg.records[REC_M3HITS] = atoi(CG_Argv(i++));
	cg.records[REC_MP5SHOTS] = atoi(CG_Argv(i++));
	cg.records[REC_MP5HITS] = atoi(CG_Argv(i++));
	cg.records[REC_M4SHOTS] = atoi(CG_Argv(i++));
	cg.records[REC_M4HITS] = atoi(CG_Argv(i++));
	cg.records[REC_SSG3000SHOTS] = atoi(CG_Argv(i++));
	cg.records[REC_SSG3000HITS] = atoi(CG_Argv(i++));
	cg.records[REC_HANDCANNONSHOTS] = atoi(CG_Argv(i++));
	cg.records[REC_HANDCANNONHITS] = atoi(CG_Argv(i++));
	cg.records[REC_AKIMBOSHOTS] = atoi(CG_Argv(i++));
	cg.records[REC_AKIMBOHITS] = atoi(CG_Argv(i++));
	cg.records[REC_GRENADESHOTS] = atoi(CG_Argv(i++));
	cg.records[REC_GRENADEHITS] = atoi(CG_Argv(i++));
	cg.records[REC_KICKHITS] = atoi(CG_Argv(i++));
	cg.records[REC_KILLS] = atoi(CG_Argv(i++));
	cg.records[REC_TEAMKILLS] = atoi(CG_Argv(i++));
	cg.records[REC_SUICIDES] = atoi(CG_Argv(i++));

}

/*
=================
CG_ParseWeaponStats2
I send 2 server config strings, I was not 
sure if there was a max length, so may aswell avoid it
=================
*/
static void CG_ParseWeaponStats2(void)
{
	int i;

	i = 1;
	//Blaze: oi, damn fugly code
	cg.records[REC_KNIFETHROWDEATHS] = atoi(CG_Argv(i++));
	cg.records[REC_KNIFETHROWKILLS] = atoi(CG_Argv(i++));
	cg.records[REC_KNIFESLASHDEATHS] = atoi(CG_Argv(i++));
	cg.records[REC_KNIFESLASHKILLS] = atoi(CG_Argv(i++));
	cg.records[REC_MK23DEATHS] = atoi(CG_Argv(i++));
	cg.records[REC_MK23KILLS] = atoi(CG_Argv(i++));
	cg.records[REC_M3DEATHS] = atoi(CG_Argv(i++));
	cg.records[REC_M3KILLS] = atoi(CG_Argv(i++));
	cg.records[REC_MP5DEATHS] = atoi(CG_Argv(i++));
	cg.records[REC_MP5KILLS] = atoi(CG_Argv(i++));
	cg.records[REC_M4DEATHS] = atoi(CG_Argv(i++));
	cg.records[REC_M4KILLS] = atoi(CG_Argv(i++));
	cg.records[REC_SSG3000DEATHS] = atoi(CG_Argv(i++));
	cg.records[REC_SSG3000KILLS] = atoi(CG_Argv(i++));
	cg.records[REC_HANDCANNONDEATHS] = atoi(CG_Argv(i++));
	cg.records[REC_HANDCANNONKILLS] = atoi(CG_Argv(i++));
	cg.records[REC_AKIMBODEATHS] = atoi(CG_Argv(i++));
	cg.records[REC_AKIMBOKILLS] = atoi(CG_Argv(i++));
	cg.records[REC_GRENADEDEATHS] = atoi(CG_Argv(i++));
	cg.records[REC_GRENADEKILLS] = atoi(CG_Argv(i++));
	cg.records[REC_KICKDEATHS] = atoi(CG_Argv(i++));
	cg.records[REC_KICKKILLS] = atoi(CG_Argv(i++));
}

/*
=================
CG_ParseTeamInfo

=================
*/
static void CG_ParseTeamInfo(void)
{
	int i;
	int client;

	numSortedTeamPlayers = atoi(CG_Argv(1));

	if (numSortedTeamPlayers < 0 || numSortedTeamPlayers > TEAM_MAXOVERLAY) {
		CG_Error("CG_ParseTeamInfo: numSortedTeamPlayers out of range (%d)",
			numSortedTeamPlayers);
		return;
	}
	for (i = 0; i < numSortedTeamPlayers; i++) {
		client = atoi(CG_Argv(i * 6 + 2));
		if (client < 0 || client >= MAX_CLIENTS) {
			CG_Error("CG_ParseTeamInfo: bad client number: %d", client);
			return;
		}
		sortedTeamPlayers[i] = client;

		cgs.clientinfo[client].location = atoi(CG_Argv(i * 6 + 3));
		cgs.clientinfo[client].health = atoi(CG_Argv(i * 6 + 4));
		cgs.clientinfo[client].armor = atoi(CG_Argv(i * 6 + 5));
		cgs.clientinfo[client].curWeapon = atoi(CG_Argv(i * 6 + 6));
		cgs.clientinfo[client].powerups = atoi(CG_Argv(i * 6 + 7));
	}
}

/*
================
CG_ParseServerinfo

This is called explicitly when the gamestate is first received,
and whenever the server updates any serverinfo flagged cvars
================
*/
void CG_ParseServerinfo(void)
{
	const char *info;
	char *mapname;

	info = CG_ConfigString(CS_SERVERINFO);
	cgs.gametype = atoi(Info_ValueForKey(info, "g_gametype"));
	trap_Cvar_Set("g_gametype", va("%i", cgs.gametype));
	cgs.dmflags = atoi(Info_ValueForKey(info, "dmflags"));
	cgs.teamflags = atoi(Info_ValueForKey(info, "teamflags"));
	cgs.fraglimit = atoi(Info_ValueForKey(info, "fraglimit"));
	cgs.capturelimit = atoi(Info_ValueForKey(info, "capturelimit"));
	cgs.timelimit = atoi(Info_ValueForKey(info, "timelimit"));
	cgs.maxclients = atoi(Info_ValueForKey(info, "sv_maxclients"));
	mapname = Info_ValueForKey(info, "mapname");
	Com_sprintf(cgs.mapname, sizeof(cgs.mapname), "maps/%s.bsp", mapname);
	Q_strncpyz(cgs.redTeam, Info_ValueForKey(info, "g_redTeam"), sizeof(cgs.redTeam));
	trap_Cvar_Set("g_redTeam", cgs.redTeam);
	Q_strncpyz(cgs.blueTeam, Info_ValueForKey(info, "g_blueTeam"), sizeof(cgs.blueTeam));
	trap_Cvar_Set("g_blueTeam", cgs.blueTeam);
// JBravo: unlagged
	cgs.delagHitscan = atoi(Info_ValueForKey(info, "g_delagHitscan"));
	trap_Cvar_Set("g_delagHitscan", va("%i", cgs.delagHitscan));
}

/*
==================
CG_ParseWarmup
==================
*/
static void CG_ParseWarmup(void)
{
	const char *info;
	int warmup;

	info = CG_ConfigString(CS_WARMUP);

	warmup = atoi(info);
	cg.warmupCount = -1;

	if (warmup == 0 && cg.warmup) {

	} else if (warmup > 0 && cg.warmup <= 0) {
		if (cg_RQ3_anouncer.integer == 1)
			trap_S_StartLocalSound(cgs.media.countPrepareSound, CHAN_ANNOUNCER);
	}

	cg.warmup = warmup;
}

//Makro - sky portal and lens flare
void CG_ParseSkyPortal(const char *str)
{
	//sky portal
	if (str && str[0] && Q_stricmp(str, "none") && atoi(Info_ValueForKey(str, "n"))) {
		cgs.skyPortalOrigin[0] = atof(Info_ValueForKey(str, "x"));
		cgs.skyPortalOrigin[1] = atof(Info_ValueForKey(str, "y"));
		cgs.skyPortalOrigin[2] = atof(Info_ValueForKey(str, "z"));
		cgs.skyPortalMoveFactor[0] = atof(Info_ValueForKey(str, "mx"));
		cgs.skyPortalMoveFactor[1] = atof(Info_ValueForKey(str, "my"));
		cgs.skyPortalMoveFactor[2] = atof(Info_ValueForKey(str, "mz"));
		cgs.skyPortalSet = qtrue;
	} else {
		cgs.skyPortalSet = qfalse;
	}
	//lens flare
	cgs.sunFlareSize = atoi(Info_ValueForKey(str, "lsun"));
	cgs.numFlares = atoi(Info_ValueForKey(str, "ln"));
	cgs.numFlares = 0;
	if (cgs.sunFlareSize > 0 || cgs.numFlares > 0) {
		float alphamin, alphamax, sizemin, sizemax, dfactor = 0.75f;
		int i;
		
		cgs.sunDir[0] = atof(Info_ValueForKey(str, "lx"));
		cgs.sunDir[1] = atof(Info_ValueForKey(str, "ly"));
		cgs.sunDir[2] = atof(Info_ValueForKey(str, "lz"));
		alphamin = Com_Clamp(0.0f, 1.0f, atof(Info_ValueForKey(str, "lamin")));
		alphamax = Com_Clamp(0.0f, 1.0f, atof(Info_ValueForKey(str, "lamax")));
		sizemin = atof(Info_ValueForKey(str, "lsmin"));
		sizemax = atof(Info_ValueForKey(str, "lsmax"));
		cgs.sunAlpha = Com_Clamp(0.0f, 1.0f, atof(Info_ValueForKey(str, "lsa")));

		//generate flare parms
		for (i=0; i<MAX_VISIBLE_FLARES; i++) {
			cg.flareShaderNum[i] = rand() % NUM_FLARE_SHADERS;
			//looks yucky, but oh well...
			cg.flareShaderSize[i] = sizemin + random() * (sizemax - sizemin) *
				(1.0f - dfactor * (1.0f - (i+1) / (float)MAX_VISIBLE_FLARES));
			cg.flareColor[i][0] = 0.25f + random() * 0.75f;
			cg.flareColor[i][1] = 0.25f + random() * 0.75f;
			cg.flareColor[i][2] = 0.25f + random() * 0.75f;
			cg.flareColor[i][3] = alphamin + random() * (alphamin - alphamax);
		}
	} else {
		cgs.numFlares = 0;
	}
}

//Makro - added
void CG_ParseFogHull(const char *str)
{
	if (str && str[0]) {
		cgs.clearColor[0] = atof(Info_ValueForKey(str, "r"));
		cgs.clearColor[1] = atof(Info_ValueForKey(str, "g"));
		cgs.clearColor[2] = atof(Info_ValueForKey(str, "b"));
		cgs.clearColorSet = qtrue;
	} else {
		cgs.clearColorSet = qfalse;
	}
}

void CG_ParseDlightStyles(const char *str)
{
	int i;
	memset(dlightStyles, 0, sizeof(dlightStyles));
	dlightStyleCount = atoi(Info_ValueForKey(str, "n"));
	for (i=0; i<dlightStyleCount; i++)
	{
		Q_strncpyz(dlightStyles[i], Info_ValueForKey(str, va("%i", i)), sizeof(dlightStyles[0]));
	}
}

void CG_ParseMoveParents(const char *str)
{
	int i, num;
	char tmp[4];	//3 digits and trailing zero

	memset(cg_moveParentRanks, 0, sizeof(cg_moveParentRanks));
	Q_strncpyz(tmp, str, 4);
	str += 3;
	num = atoi(tmp);
	//num = GetIntBytes(str, 2) >> 1;
	//str += 2;
	for (i=0; i<num; i++)
	{
		int entnum;
		Q_strncpyz(tmp, str, 4);
		entnum = atoi(tmp);
		str += 3;
		//entnum = GetIntBytes(str, 2) >> 1;
		//str += 2;
		Q_strncpyz(tmp, str, 4);
		str += 3;
		cg_moveParentRanks[entnum] = atoi(tmp);
		//cg_moveParentRanks[entnum] = GetIntBytes(str, 2);
		//str += 2;
	}
}

/*
================
CG_SetConfigValues

Called on load to set the initial values from configure strings
================
*/
void CG_SetConfigValues(void)
{
	const char *s;

	cgs.scores1 = atoi(CG_ConfigString(CS_SCORES1));
	cgs.scores2 = atoi(CG_ConfigString(CS_SCORES2));
	cgs.levelStartTime = atoi(CG_ConfigString(CS_LEVEL_START_TIME));
	if (cgs.gametype == GT_CTF) {
		s = CG_ConfigString(CS_FLAGSTATUS);
		cgs.redflag = s[0] - '0';
		cgs.blueflag = s[1] - '0';
	}
	cg.warmup = atoi(CG_ConfigString(CS_WARMUP));
	// q3f atmospheric stuff:
	if ( cg_atmosphericEffects.integer )
		CG_EffectParse( CG_ConfigString( CS_ATMOSEFFECT ) );
	//Makro - "clear" color
	CG_ParseFogHull( CG_ConfigString(CS_FOGHULL) );
	//Makro - sky portal
	CG_ParseSkyPortal( CG_ConfigString(CS_SKYPORTAL) );
	//Makro - fake shadows (not implemented yet!)
	s = Info_ValueForKey(CG_ConfigString(CS_SHADOWS), "1");
	if (s && *s)
		trap_R_RegisterShaderNoMip(s);
	//Makro - dlight styles
	CG_ParseDlightStyles(CG_ConfigString(CS_DLIGHT_STYLES));
	//Makro - moveparent order
	CG_ParseMoveParents(CG_ConfigString(CS_MOVEPARENTS));
}

/*
=====================
CG_ShaderStateChanged
=====================
*/
void CG_ShaderStateChanged(void)
{
	char originalShader[MAX_QPATH];
	char newShader[MAX_QPATH];
	char timeOffset[16];
	const char *o;
	char *n, *t;

	o = CG_ConfigString(CS_SHADERSTATE);
	while (o && *o) {
		n = strstr(o, "=");
		if (n && *n) {
			strncpy(originalShader, o, n - o);
			originalShader[n - o] = 0;
			n++;
			t = strstr(n, ":");
			if (t && *t) {
				strncpy(newShader, n, t - n);
				newShader[t - n] = 0;
			} else {
				break;
			}
			t++;
			o = strstr(t, "@");
			if (o) {
				strncpy(timeOffset, t, o - t);
				timeOffset[o - t] = 0;
				o++;
				trap_R_RemapShader(originalShader, newShader, timeOffset);
			}
		} else {
			break;
		}
	}
}

/*
================
CG_ConfigStringModified

================
*/
static void CG_ConfigStringModified(void)
{
	const char *str;
	int num;

	num = atoi(CG_Argv(1));

	// get the gamestate from the client system, which will have the
	// new configstring already integrated
	trap_GetGameState(&cgs.gameState);

	// look up the individual string that was modified
	str = CG_ConfigString(num);

	// do something with it if necessary
	if (num == CS_MUSIC) {
		CG_StartMusic();
	} else if (num == CS_SERVERINFO) {
		CG_ParseServerinfo();
	} else if (num == CS_WARMUP) {
		CG_ParseWarmup();
	} else if (num == CS_SCORES1) {
		cgs.scores1 = atoi(str);
	} else if (num == CS_SCORES2) {
		cgs.scores2 = atoi(str);
	} else if (num == CS_LEVEL_START_TIME) {
		cgs.levelStartTime = atoi(str);
	} else if (num == CS_VOTE_TIME) {
		cgs.voteTime = atoi(str);
		cgs.voteModified = qtrue;
	} else if (num == CS_VOTE_YES) {
		cgs.voteYes = atoi(str);
		cgs.voteModified = qtrue;
	} else if (num == CS_VOTE_NO) {
		cgs.voteNo = atoi(str);
		cgs.voteModified = qtrue;
	} else if (num == CS_VOTE_STRING) {
		Q_strncpyz(cgs.voteString, str, sizeof(cgs.voteString));
	} else if (num >= CS_TEAMVOTE_TIME && num <= CS_TEAMVOTE_TIME + 1) {
		cgs.teamVoteTime[num - CS_TEAMVOTE_TIME] = atoi(str);
		cgs.teamVoteModified[num - CS_TEAMVOTE_TIME] = qtrue;
	} else if (num >= CS_TEAMVOTE_YES && num <= CS_TEAMVOTE_YES + 1) {
		cgs.teamVoteYes[num - CS_TEAMVOTE_YES] = atoi(str);
		cgs.teamVoteModified[num - CS_TEAMVOTE_YES] = qtrue;
	} else if (num >= CS_TEAMVOTE_NO && num <= CS_TEAMVOTE_NO + 1) {
		cgs.teamVoteNo[num - CS_TEAMVOTE_NO] = atoi(str);
		cgs.teamVoteModified[num - CS_TEAMVOTE_NO] = qtrue;
	} else if (num >= CS_TEAMVOTE_STRING && num <= CS_TEAMVOTE_STRING + 1) {
		Q_strncpyz(cgs.teamVoteString[num - CS_TEAMVOTE_STRING], str, sizeof(cgs.teamVoteString));
	} else if (num == CS_INTERMISSION) {
		cg.intermissionStarted = atoi(str);
	} else if (num >= CS_MODELS && num < CS_MODELS + MAX_MODELS) {
		cgs.gameModels[num - CS_MODELS] = trap_R_RegisterModel(str);
	} else if (num >= CS_SOUNDS && num < CS_SOUNDS + MAX_SOUNDS) {
		if (str[0] != '*') {	// player specific sounds don't register here
			cgs.gameSounds[num - CS_SOUNDS] = trap_S_RegisterSound(str, qfalse);
		}
	} else if (num >= CS_PLAYERS && num < CS_PLAYERS + MAX_CLIENTS) {
		CG_NewClientInfo(num - CS_PLAYERS);
		CG_BuildSpectatorString();
	} else if (num == CS_FLAGSTATUS) {
		if (cgs.gametype == GT_CTF) {
			// format is rb where its red/blue, 0 is at base, 1 is taken, 2 is dropped
			cgs.redflag = str[0] - '0';
			cgs.blueflag = str[1] - '0';
		}
	} else if (num == CS_SHADERSTATE) {
		CG_ShaderStateChanged();
  	} else if( num == CS_ATMOSEFFECT ) {
  	  	CG_EffectParse( str );
   	//Makro - sky portals
	} else if (num == CS_SKYPORTAL) {
		CG_ParseSkyPortal(str);
	//Makro - "clear" color
	} else if (num == CS_FOGHULL) {
		CG_ParseFogHull(str);
	//Makro - dlight styles
	} else if (num == CS_DLIGHT_STYLES) {
		CG_ParseDlightStyles(str);
	//Makro - moveparent order
	} else if (num == CS_MOVEPARENTS) {
		CG_ParseMoveParents(str);
	}

}

/*
=======================
CG_AddToTeamChat

=======================
*/
static void CG_AddToTeamChat(const char *str)
{
	int len;
	char *p, *ls;
	int lastcolor;
	int chatHeight;

	if (cg_teamChatHeight.integer < TEAMCHAT_HEIGHT) {
		chatHeight = cg_teamChatHeight.integer;
	} else {
		chatHeight = TEAMCHAT_HEIGHT;
	}

	if (chatHeight <= 0 || cg_teamChatTime.integer <= 0) {
		// team chat disabled, dump into normal chat
		cgs.teamChatPos = cgs.teamLastChatPos = 0;
		return;
	}

	len = 0;

	p = cgs.teamChatMsgs[cgs.teamChatPos % chatHeight];
	*p = 0;

	lastcolor = '7';

	ls = NULL;
	while (*str) {
		if (len > TEAMCHAT_WIDTH - 1) {
			if (ls) {
				str -= (p - ls);
				str++;
				p -= (p - ls);
			}
			*p = 0;

			cgs.teamChatMsgTimes[cgs.teamChatPos % chatHeight] = cg.time;

			cgs.teamChatPos++;
			p = cgs.teamChatMsgs[cgs.teamChatPos % chatHeight];
			*p = 0;
			*p++ = Q_COLOR_ESCAPE;
			*p++ = lastcolor;
			len = 0;
			ls = NULL;
		}

		if (Q_IsColorString(str)) {
			*p++ = *str++;
			lastcolor = *str;
			*p++ = *str++;
			continue;
		}
		if (*str == ' ') {
			ls = p;
		}
		*p++ = *str++;
		len++;
	}
	*p = 0;

	cgs.teamChatMsgTimes[cgs.teamChatPos % chatHeight] = cg.time;
	cgs.teamChatPos++;

	if (cgs.teamChatPos - cgs.teamLastChatPos > chatHeight)
		cgs.teamLastChatPos = cgs.teamChatPos - chatHeight;
}

/*
===============
CG_MapRestart

The server has issued a map_restart, so the next snapshot
is completely new and should not be interpolated to.

A tournement restart will clear everything, but doesn't
require a reload of all the media
===============
*/
static void CG_MapRestart(void)
{
	if (cg_showmiss.integer) {
		CG_Printf("CG_MapRestart\n");
	}

	CG_InitLocalEntities();
	CG_InitMarkPolys();
	CG_ClearParticles();

	// make sure the "3 frags left" warnings play again
	cg.fraglimitWarnings = 0;

	cg.timelimitWarnings = 0;

	cg.intermissionStarted = qfalse;
	cg.levelShot = qfalse;

	cgs.voteTime = 0;

	cg.mapRestart = qtrue;

	CG_StartMusic();

	trap_S_ClearLoopingSounds(qtrue);

	// we really should clear more parts of cg here and stop sounds

	// play the "fight" sound if this is a restart without warmup
	// JBravo: unless we are in teamplay mode.
	if (cgs.gametype >= GT_TEAM)
		return;
	if (cg.warmup == 0 /* && cgs.gametype == GT_TOURNAMENT */ ) {
		trap_S_StartLocalSound(cgs.media.countFightSound, CHAN_ANNOUNCER);
		CG_CenterPrint("FIGHT!", 120, GIANTCHAR_WIDTH * 2);
	}
	trap_Cvar_Set("cg_thirdPerson", "0");
}

#define MAX_VOICEFILESIZE	16384
#define MAX_VOICEFILES		8
#define MAX_VOICECHATS		64
#define MAX_VOICESOUNDS		64
#define MAX_CHATSIZE		64
#define MAX_HEADMODELS		64

typedef struct voiceChat_s {
	char id[64];
	int numSounds;
	sfxHandle_t sounds[MAX_VOICESOUNDS];
	char chats[MAX_VOICESOUNDS][MAX_CHATSIZE];
} voiceChat_t;

typedef struct voiceChatList_s {
	char name[64];
	int gender;
	int numVoiceChats;
	voiceChat_t voiceChats[MAX_VOICECHATS];
} voiceChatList_t;

typedef struct headModelVoiceChat_s {
	char headmodel[64];
	int voiceChatNum;
} headModelVoiceChat_t;

voiceChatList_t voiceChatLists[MAX_VOICEFILES];
headModelVoiceChat_t headModelVoiceChat[MAX_HEADMODELS];

/*
=================
CG_ParseVoiceChats
=================
*/
int CG_ParseVoiceChats(const char *filename, voiceChatList_t * voiceChatList, int maxVoiceChats)
{
	int len, i;
	fileHandle_t f;
	char buf[MAX_VOICEFILESIZE];
	char **p, *ptr;
	char *token;
	voiceChat_t *voiceChats;
	qboolean compress;
	sfxHandle_t sound;

	compress = qtrue;
	if (cg_buildScript.integer) {
		compress = qfalse;
	}

	len = trap_FS_FOpenFile(filename, &f, FS_READ);
	if (!f) {
		trap_Print(va(S_COLOR_RED "voice chat file not found: %s\n", filename));
		return qfalse;
	}
	if (len >= MAX_VOICEFILESIZE) {
		trap_Print(va
			   (S_COLOR_RED "voice chat file too large: %s is %i, max allowed is %i", filename, len,
			    MAX_VOICEFILESIZE));
		trap_FS_FCloseFile(f);
		return qfalse;
	}

	trap_FS_Read(buf, len, f);
	buf[len] = 0;
	trap_FS_FCloseFile(f);

	ptr = buf;
	p = &ptr;

	Com_sprintf(voiceChatList->name, sizeof(voiceChatList->name), "%s", filename);
	voiceChats = voiceChatList->voiceChats;
	for (i = 0; i < maxVoiceChats; i++) {
		voiceChats[i].id[0] = 0;
	}
	token = COM_ParseExt(p, qtrue);
	if (!token || token[0] == 0) {
		return qtrue;
	}
	if (!Q_stricmp(token, "female")) {
		voiceChatList->gender = GENDER_FEMALE;
	} else if (!Q_stricmp(token, "male")) {
		voiceChatList->gender = GENDER_MALE;
	} else if (!Q_stricmp(token, "neuter")) {
		voiceChatList->gender = GENDER_NEUTER;
	} else {
		trap_Print(va(S_COLOR_RED "expected gender not found in voice chat file: %s\n", filename));
		return qfalse;
	}

	voiceChatList->numVoiceChats = 0;
	while (1) {
		token = COM_ParseExt(p, qtrue);
		if (!token || token[0] == 0) {
			return qtrue;
		}
		Com_sprintf(voiceChats[voiceChatList->numVoiceChats].id,
			    sizeof(voiceChats[voiceChatList->numVoiceChats].id), "%s", token);
		token = COM_ParseExt(p, qtrue);
		if (Q_stricmp(token, "{")) {
			trap_Print(va(S_COLOR_RED "expected { found %s in voice chat file: %s\n", token, filename));
			return qfalse;
		}
		voiceChats[voiceChatList->numVoiceChats].numSounds = 0;
		while (1) {
			token = COM_ParseExt(p, qtrue);
			if (!token || token[0] == 0) {
				return qtrue;
			}
			if (!Q_stricmp(token, "}"))
				break;
			sound = trap_S_RegisterSound(token, compress);
			voiceChats[voiceChatList->numVoiceChats].sounds[voiceChats[voiceChatList->numVoiceChats].
					numSounds] = sound;
			token = COM_ParseExt(p, qtrue);
			if (!token || token[0] == 0) {
				return qtrue;
			}
			Com_sprintf(voiceChats[voiceChatList->numVoiceChats].
				    chats[voiceChats[voiceChatList->numVoiceChats].numSounds], MAX_CHATSIZE, "%s",
				    token);
			if (sound)
				voiceChats[voiceChatList->numVoiceChats].numSounds++;
			if (voiceChats[voiceChatList->numVoiceChats].numSounds >= MAX_VOICESOUNDS)
				break;
		}
		voiceChatList->numVoiceChats++;
		if (voiceChatList->numVoiceChats >= maxVoiceChats)
			return qtrue;
	}
	return qtrue;
}

/*
=================
CG_LoadVoiceChats
=================
*/
void CG_LoadVoiceChats(void)
{
	int size;

	size = trap_MemoryRemaining();
	CG_ParseVoiceChats("scripts/female1.voice", &voiceChatLists[0], MAX_VOICECHATS);
	CG_ParseVoiceChats("scripts/female2.voice", &voiceChatLists[1], MAX_VOICECHATS);
	CG_ParseVoiceChats("scripts/female3.voice", &voiceChatLists[2], MAX_VOICECHATS);
	CG_ParseVoiceChats("scripts/male1.voice", &voiceChatLists[3], MAX_VOICECHATS);
	CG_ParseVoiceChats("scripts/male2.voice", &voiceChatLists[4], MAX_VOICECHATS);
	CG_ParseVoiceChats("scripts/male3.voice", &voiceChatLists[5], MAX_VOICECHATS);
	CG_ParseVoiceChats("scripts/male4.voice", &voiceChatLists[6], MAX_VOICECHATS);
	CG_ParseVoiceChats("scripts/male5.voice", &voiceChatLists[7], MAX_VOICECHATS);
	CG_Printf("voice chat memory size = %d\n", size - trap_MemoryRemaining());
}

/*
=================
CG_HeadModelVoiceChats
=================
*/
int CG_HeadModelVoiceChats(char *filename)
{
	int len, i;
	fileHandle_t f;
	char buf[MAX_VOICEFILESIZE];
	char **p, *ptr;
	char *token;

	len = trap_FS_FOpenFile(filename, &f, FS_READ);
	if (!f) {
		//trap_Print( va( "voice chat file not found: %s\n", filename ) );
		return -1;
	}
	if (len >= MAX_VOICEFILESIZE) {
		trap_Print(va
			   (S_COLOR_RED "voice chat file too large: %s is %i, max allowed is %i", filename, len,
			    MAX_VOICEFILESIZE));
		trap_FS_FCloseFile(f);
		return -1;
	}

	trap_FS_Read(buf, len, f);
	buf[len] = 0;
	trap_FS_FCloseFile(f);

	ptr = buf;
	p = &ptr;

	token = COM_ParseExt(p, qtrue);
	if (!token || token[0] == 0) {
		return -1;
	}

	for (i = 0; i < MAX_VOICEFILES; i++) {
		if (!Q_stricmp(token, voiceChatLists[i].name)) {
			return i;
		}
	}

	//FIXME: maybe try to load the .voice file which name is stored in token?

	return -1;
}

/*
=================
CG_GetVoiceChat
=================
*/
int CG_GetVoiceChat(voiceChatList_t * voiceChatList, const char *id, sfxHandle_t * snd, char **chat)
{
	int i, rnd;

	for (i = 0; i < voiceChatList->numVoiceChats; i++) {
		if (!Q_stricmp(id, voiceChatList->voiceChats[i].id)) {
			rnd = random() * voiceChatList->voiceChats[i].numSounds;
			*snd = voiceChatList->voiceChats[i].sounds[rnd];
			*chat = voiceChatList->voiceChats[i].chats[rnd];
			return qtrue;
		}
	}
	return qfalse;
}

/*
=================
CG_VoiceChatListForClient
=================
*/
voiceChatList_t *CG_VoiceChatListForClient(int clientNum)
{
	clientInfo_t *ci;
	int voiceChatNum, i, j, k, gender;
	char filename[MAX_QPATH], headModelName[MAX_QPATH];

	if (clientNum < 0 || clientNum >= MAX_CLIENTS) {
		clientNum = 0;
	}
	ci = &cgs.clientinfo[clientNum];

	for (k = 0; k < 2; k++) {
		if (k == 0) {
			if (ci->headModelName[0] == '*') {
				Com_sprintf(headModelName, sizeof(headModelName), "%s/%s", ci->headModelName + 1,
					    ci->headSkinName);
			} else {
				Com_sprintf(headModelName, sizeof(headModelName), "%s/%s", ci->headModelName,
					    ci->headSkinName);
			}
		} else {
			if (ci->headModelName[0] == '*') {
				Com_sprintf(headModelName, sizeof(headModelName), "%s", ci->headModelName + 1);
			} else {
				Com_sprintf(headModelName, sizeof(headModelName), "%s", ci->headModelName);
			}
		}
		// find the voice file for the head model the client uses
		for (i = 0; i < MAX_HEADMODELS; i++) {
			if (!Q_stricmp(headModelVoiceChat[i].headmodel, headModelName)) {
				break;
			}
		}
		if (i < MAX_HEADMODELS) {
			return &voiceChatLists[headModelVoiceChat[i].voiceChatNum];
		}
		// find a <headmodelname>.vc file
		for (i = 0; i < MAX_HEADMODELS; i++) {
			if (!strlen(headModelVoiceChat[i].headmodel)) {
				Com_sprintf(filename, sizeof(filename), "scripts/%s.vc", headModelName);
				voiceChatNum = CG_HeadModelVoiceChats(filename);
				if (voiceChatNum == -1)
					break;
				Com_sprintf(headModelVoiceChat[i].headmodel, sizeof(headModelVoiceChat[i].headmodel),
					    "%s", headModelName);
				headModelVoiceChat[i].voiceChatNum = voiceChatNum;
				return &voiceChatLists[headModelVoiceChat[i].voiceChatNum];
			}
		}
	}
	gender = ci->gender;
	for (k = 0; k < 2; k++) {
		// just pick the first with the right gender
		for (i = 0; i < MAX_VOICEFILES; i++) {
			if (strlen(voiceChatLists[i].name)) {
				if (voiceChatLists[i].gender == gender) {
					// store this head model with voice chat for future reference
					for (j = 0; j < MAX_HEADMODELS; j++) {
						if (!strlen(headModelVoiceChat[j].headmodel)) {
							Com_sprintf(headModelVoiceChat[j].headmodel,
								    sizeof(headModelVoiceChat[j].headmodel), "%s",
								    headModelName);
							headModelVoiceChat[j].voiceChatNum = i;
							break;
						}
					}
					return &voiceChatLists[i];
				}
			}
		}
		// fall back to male gender because we don't have neuter in the mission pack
		if (gender == GENDER_MALE)
			break;
		gender = GENDER_MALE;
	}
	// store this head model with voice chat for future reference
	for (j = 0; j < MAX_HEADMODELS; j++) {
		if (!strlen(headModelVoiceChat[j].headmodel)) {
			Com_sprintf(headModelVoiceChat[j].headmodel, sizeof(headModelVoiceChat[j].headmodel),
				    "%s", headModelName);
			headModelVoiceChat[j].voiceChatNum = 0;
			break;
		}
	}
	// just return the first voice chat list
	return &voiceChatLists[0];
}

#define MAX_VOICECHATBUFFER		32

typedef struct bufferedVoiceChat_s {
	int clientNum;
	sfxHandle_t snd;
	int voiceOnly;
	char cmd[MAX_SAY_TEXT];
	char message[MAX_SAY_TEXT];
} bufferedVoiceChat_t;

bufferedVoiceChat_t voiceChatBuffer[MAX_VOICECHATBUFFER];

/*
=================
CG_PlayVoiceChat
=================
*/
void CG_PlayVoiceChat(bufferedVoiceChat_t * vchat)
{
}

/*
=====================
CG_PlayBufferedVoieChats
=====================
*/
void CG_PlayBufferedVoiceChats(void)
{
}

/*
=====================
CG_AddBufferedVoiceChat
=====================
*/
void CG_AddBufferedVoiceChat(bufferedVoiceChat_t * vchat)
{
}

/*
=================
CG_VoiceChatLocal
=================
*/
void CG_VoiceChatLocal(int mode, qboolean voiceOnly, int clientNum, int color, const char *cmd)
{
}

/*
=================
CG_VoiceChat
=================
*/
void CG_VoiceChat(int mode)
{
}

/*
=================
CG_RemoveChatEscapeChar
=================
*/
static void CG_RemoveChatEscapeChar(char *text)
{
	int i, l;

	l = 0;
	for (i = 0; text[i]; i++) {
		if (text[i] == '\x19')
			continue;
		text[l++] = text[i];
	}
	text[l] = '\0';
}

/*
=================
CG_ConcatArgs

Recontruct arguments into a whole string
=================
*/
char *CG_ConcatArgs(int start)
{
	int i, c, tlen, len;
	static char line[MAX_STRING_CHARS];
	char arg[MAX_STRING_CHARS];

	len = 0;
	c = trap_Argc();
	for (i = start; i < c; i++) {
		trap_Argv(i, arg, sizeof(arg));
		tlen = strlen(arg);
		if (len + tlen >= MAX_STRING_CHARS - 1) {
			break;
		}
		memcpy(line + len, arg, tlen);
		len += tlen;
		if (i != c - 1) {
			line[len] = ' ';
			len++;
		}
	}

	line[len] = 0;
	return line;
}
void CG_Stuffcmd(void)
{
	char *cmd;

	cmd = CG_ConcatArgs(1);
	trap_SendConsoleCommand(cmd);
}

// JBravo: generic cvar setting command.  Used from game
void CG_CvarSet(void)
{
	char cvar[128], value[128];

	Q_strncpyz(cvar, CG_Argv(2), 128);
	Q_strncpyz(value, CG_Argv(3), 128);

	trap_Cvar_Set(cvar, value);
}

/*void CG_SetTeamPlayers(void) {
		int	team, number;
			char	teamz[64];

		team = atoi(CG_Argv(1));
		number = atoi(CG_Argv(2));
		Com_sprintf (teamz, sizeof(teamz), "%i", number);

		if (team == TEAM_RED)
			trap_Cvar_Set("ui_RQ3_teamCount1", teamz);
		else if (team == TEAM_BLUE)
			trap_Cvar_Set("ui_RQ3_teamCount2", teamz);
		else if (team == TEAM_SPECTATOR || team == TEAM_FREE)
			trap_Cvar_Set("ui_RQ3_numSpectators", teamz);
		return;
}*/

void CG_Radio(void)
{
	int sound, gender, set;

	sound = atoi(CG_Argv(2));
	gender = atoi(CG_Argv(3));
	set = atoi(CG_Argv(4));

	//Slicer optimization
	if (cg_RQ3_dynamicRadio.integer) {
		if (!gender) {
			if (set == 0) {
				CG_AddBufferedSound(cgs.media.male_sounds[sound]);
			} else if (set == 1) {
				CG_AddBufferedSound(cgs.media.new_male_sounds[sound]);
			} else if (set == 2) {
				CG_AddBufferedSound(cgs.media.pikey_male_sounds[sound]);
			} else if (set == 3) {
				CG_AddBufferedSound(cgs.media.pirate_male_sounds[sound]);
			} else if (set > 3)
				CG_AddBufferedSound(cgs.media.keanu_male_sounds[sound]);
		} else
			CG_AddBufferedSound(cgs.media.female_sounds[sound]);
	} else if (!gender) {
		if (cg_RQ3_radiovoice_male.integer == 0) {
			CG_AddBufferedSound(cgs.media.male_sounds[sound]);
		} else if (cg_RQ3_radiovoice_male.integer == 1) {
			CG_AddBufferedSound(cgs.media.new_male_sounds[sound]);
		} else if (cg_RQ3_radiovoice_male.integer == 2) {
			CG_AddBufferedSound(cgs.media.pikey_male_sounds[sound]);
		} else if (cg_RQ3_radiovoice_male.integer == 3) {
			CG_AddBufferedSound(cgs.media.pirate_male_sounds[sound]);
		} else if (cg_RQ3_radiovoice_male.integer > 3)
			CG_AddBufferedSound(cgs.media.pirate_male_sounds[sound]);
	} else {
		CG_AddBufferedSound(cgs.media.female_sounds[sound]);
	}
	return;
}

/*
==============
RemoveColorEscapeSequences
==============
*/
void RemoveColorEscapeSequences(char *text)
{
	int i, l;

	l = 0;
	for (i = 0; text[i]; i++) {
		if (Q_IsColorString(&text[i])) {
			i++;
			continue;
		}
		if (text[i] > 0x7E)
			continue;
		text[l++] = text[i];
	}
	text[l] = '\0';
}

void CG_CtbCountDown(int delay) 
{
	cg.CTBcountdowntime = cg.time + delay * 1000;
}

/*
=================
CG_RQ3_Cmd by sLiCeR
This function will parse and handle several cmds in one ( rq3_cmd)
=================
*/
void CG_RQ3_Cmd( void )
{
	int cmd, i;
	char scrnshotName[MAX_QPATH], playerName[MAX_NAME_LENGTH];
	qtime_t qtime;

	cmd = atoi(CG_Argv(1));

	switch (cmd) {
	case LIGHTS:
		cg.lca = 1;
		//trap_Cvar_Set("cg_RQ3_lca", "1");
		cg.showScores = qfalse;
		cg.scoreTPMode = 0;
		CG_CenterPrint("LIGHTS...", SCREEN_HEIGHT * 0.30, BIGCHAR_WIDTH);
		CG_Printf("\nLIGHTS...\n");
		CG_AddBufferedSound(cgs.media.lightsSound);
		break;
	case CAMERA:
		CG_CenterPrint("CAMERA...", SCREEN_HEIGHT * 0.30, BIGCHAR_WIDTH);
		CG_Printf("\nCAMERA...\n");
		CG_AddBufferedSound(cgs.media.cameraSound);
		break;
	case TPCOUNTDOWN:
		CG_AddBufferedSound(cgs.media.lca10_0Sound);
		break;
	case ACTION:
		CG_CenterPrint("ACTION!", SCREEN_HEIGHT * 0.30, BIGCHAR_WIDTH);
		CG_Printf("\nACTION!\n");
		cg.lca = 0;
		//      trap_Cvar_Set("cg_RQ3_lca", "0");
		CG_AddBufferedSound(cgs.media.actionSound);
		break;
		/*case SETTEAMPLAYERS:
		   CG_SetTeamPlayers();
		   break; */
		//Slicer: for the anti-cheat system
		//      case AUTH:
		//              trap_Cvar_Set("cg_RQ3_auth","1");
	case SELECTPISTOL:
		if (cg.snap) {
			switch (cg.snap->ps.weapon) {
			case WP_PISTOL:
			case WP_KNIFE:
			case WP_AKIMBO:
				break;
				//case WP_GRENADE:
			default:
				cg.weaponSelectTime = cg.time;
				cg.weaponSelect = WP_PISTOL;
				//Slicer: Done Server Side
				//CG_RQ3_Zoom1x();
				break;
			}
		}
		break;
		//Slicer: apparently not being used
		/*      case ROUND:
		   trap_Cvar_Set("cg_RQ3_team_round_going", CG_Argv(1));
		   break; */
	case MAPSTART:
		break;
	case STARTDEMO:
		switch (cg_RQ3_autoAction.integer) {
		case 1:
		case 3:
			trap_RealTime(&qtime);
			Com_sprintf(scrnshotName, sizeof(scrnshotName), "record %d-%d-%d_%d-%d-%d%s\n",
				    qtime.tm_year + 1900, qtime.tm_mon + 1, qtime.tm_mday, qtime.tm_hour, qtime.tm_min, qtime.tm_sec,strstr(cgs.mapname,"/"));
			for (i = 0; i < MAX_QPATH; i++) {
				switch (scrnshotName[i]) {
				case '>':
				case '<':
				case '"':
				case '?':
				case '*':
				case ':':
				case '\\':
				case '/':
				case '|':
					scrnshotName[i] = '_';
					break;
				}
			}
			trap_SendConsoleCommand("g_synchronousClients 1\n");
			trap_SendConsoleCommand(scrnshotName);
			trap_SendConsoleCommand("g_synchronousClients 0\n");
			break;
		}
		break;
	case MAPEND:
		cg.showScores = qtrue;
		cg.scoreTPMode = 0;
		break;
	case STOPDEMO:
		switch (cg_RQ3_autoAction.integer) {
		case 1:
		case 3:
			trap_SendConsoleCommand("stoprecord\n");
			break;
		}
	case SCREENSHOT:
		switch (cg_RQ3_autoAction.integer) {
		case 3:
		case 2:
			trap_RealTime(&qtime);
			Com_sprintf(playerName, sizeof(playerName), "%s", cgs.clientinfo->name);
			RemoveColorEscapeSequences(playerName);
			Com_sprintf(scrnshotName, sizeof(scrnshotName), "screenshotjpeg %d-%d-%d_%d-%d-%d%s\n",
				    qtime.tm_year + 1900, qtime.tm_mon + 1, qtime.tm_mday, qtime.tm_hour, qtime.tm_min,
				    qtime.tm_sec, strstr(cgs.mapname,"/"));
			for (i = 0; i < MAX_QPATH; i++) {
				switch (scrnshotName[i]) {
				case '>':
				case '<':
				case '"':
				case '?':
				case '*':
				case ':':
				case '\\':
				case '/':
				case '&':
				case '|':
					scrnshotName[i] = '_';
					break;
				}
			}
			trap_SendConsoleCommand(scrnshotName);
			break;
		case 1:
			trap_SendConsoleCommand("stoprecord\n");
			break;
		}
		break;
	case SETWEAPON:
		i = atoi(CG_Argv(2));
		cg.weaponSelect = i;
		cg.weaponSelectTime = cg.time;
		break;
	case STUFF:
		CG_Stuffcmd();
		break;
	case RADIO:
		CG_Radio();
		break;
	case TKOK:
		if (cg_RQ3_tkokAutoPopup.integer)
			trap_SendConsoleCommand("ui_RQ3_tkok\n");
		break;
	case OWNED:
		if (cg_RQ3_anouncer.integer == 1)
			CG_AddBufferedSound(cgs.media.humiliationSound);
		break;
	case CVARSET:
		CG_CvarSet();
		break;
	case CTBCOUNTDOWN:
		i = atoi(CG_Argv(2));
		CG_CtbCountDown(i);
		break;
	//Makro - added
	case ZCAMTEXT:
		strcpy(cg.zcamLine[1], CG_Argv(2));
		break;
	default:
		break;
	}
}

/*
=================
CG_ServerCommand

The string has been tokenized and can be retrieved with
Cmd_Argc() / Cmd_Argv()
=================
*/
static void CG_ServerCommand(void)
{
	const char *cmd;
	char text[MAX_SAY_TEXT];

	cmd = CG_Argv(0);

	if (!cmd[0]) {
		// server claimed the command
		return;
	}

	if (!strcmp(cmd, "cp")) {
		CG_CenterPrint(CG_Argv(1), SCREEN_HEIGHT * 0.30, BIGCHAR_WIDTH);
		return;
	}

	if (!strcmp(cmd, "cs")) {
		CG_ConfigStringModified();
		return;
	}

	if (!strcmp(cmd, "print")) {
		CG_Printf("%s", CG_Argv(1));
		return;
	}

	if (!strcmp(cmd, "chat")) {
		if (!cg_teamChatsOnly.integer) {
			trap_S_StartLocalSound(cgs.media.talkSound, CHAN_LOCAL_SOUND);
			Q_strncpyz(text, CG_Argv(1), MAX_SAY_TEXT);
			CG_RemoveChatEscapeChar(text);
			CG_Printf("%s\n", text);
		}
		return;
	}

	if (!strcmp(cmd, "tchat")) {
		trap_S_StartLocalSound(cgs.media.talkSound, CHAN_LOCAL_SOUND);
		Q_strncpyz(text, CG_Argv(1), MAX_SAY_TEXT);
		CG_RemoveChatEscapeChar(text);
		CG_AddToTeamChat(text);
		CG_Printf("%s\n", text);
		return;
	}
	if (!strcmp(cmd, "vchat")) {
		CG_VoiceChat(SAY_ALL);
		return;
	}

	if (!strcmp(cmd, "vtchat")) {
		CG_VoiceChat(SAY_TEAM);
		return;
	}

	if (!strcmp(cmd, "vtell")) {
		CG_VoiceChat(SAY_TELL);
		return;
	}

	if (!strcmp(cmd, "scores")) {
		CG_ParseScores();
		return;
	}

	if (!strcmp(cmd, "wstats")) {
		CG_ParseWeaponStats();
		return;
	}

	if (!strcmp(cmd, "wstats2")) {
		CG_ParseWeaponStats2();
		return;
	}

	if (!strcmp(cmd, "tinfo")) {
		CG_ParseTeamInfo();
		return;
	}

	if (!strcmp(cmd, "map_restart")) {
		CG_MapRestart();
		return;
	}

	 if ( Q_stricmp (cmd, "remapShader") == 0 ) {
		if (trap_Argc() == 4) {
			char shader1[MAX_QPATH];
			char shader2[MAX_QPATH];
			char shader3[MAX_QPATH];

			Q_strncpyz(shader1, CG_Argv(1), sizeof(shader1));
			Q_strncpyz(shader2, CG_Argv(2), sizeof(shader2));
			Q_strncpyz(shader3, CG_Argv(3), sizeof(shader3));

			trap_R_RemapShader(shader1, shader2, shader3);
		}
		return;
	}
/*	if (Q_stricmp(cmd, "remapShader") == 0) {
		if (trap_Argc() == 4) {
			trap_R_RemapShader(CG_Argv(1), CG_Argv(2), CG_Argv(3));
		}
	}
*/
	// loaddeferred can be both a servercmd and a consolecmd
	//Makro - fixed spelling
	//if ( !strcmp( cmd, "loaddefered" ) ) {        // FIXME: spelled wrong, but not changing for demo
	if (!strcmp(cmd, "loaddeferred")) {
		CG_LoadDeferredPlayers();
		return;
	}
	// clientLevelShot is sent before taking a special screenshot for
	// the menu system during development
	if (!strcmp(cmd, "clientLevelShot")) {
		cg.levelShot = qtrue;
		return;
	}
	//Blaze: Dont think q3 can d
	/*if ( !strcmp( cmd, "numCheatVars" ) )
	   {//set and clear the cheatvar structure
	   int          numCheats;
	   numCheats = atoi(CG_Argv(1));

	   return;
	   } */

	if (!strcmp(cmd, "delCheatVar")) {
		//remove a cvar from the list of cheat variables
		//not needed now, mabey later?
		return;
	}

	if (!strcmp(cmd, "addCheatVar")) {
		//add a cvar from the list of cheat variables
		char param[128];
		int i;
		float lowend, highend;

		Q_strncpyz(param, CG_Argv(1), 128);
		lowend = atof(CG_Argv(2));
		highend = atof(CG_Argv(3));
		//CG_Printf("1) %s %f %f\n", param, lowend, highend);
		for (i = 0; i < 30; i++) {
			if (!strcmp(cheats[i].cvar, "")) {
				Q_strncpyz(cheats[i].cvar, param, 40);
				cheats[i].high = highend;
				cheats[i].low = lowend;
				//CG_Printf("2) %s %f %f\n", cheats[i].cvar, cheats[i].low, cheats[i].high);
				return;
			}
		}
		return;
	}
//Blaze: Moved to a config string to allow breakables to work in a demo
/*	if (!strcmp(cmd, "breakable")) {
		int id;
		id = atoi(CG_Argv(1));
		if (id >= 0 && id < RQ3_MAX_BREAKABLES) {
			Com_Printf("Registering breakable %s ID=%d\n",CG_Argv(2), id);
			//Blaze: Breakable stuff - register the models, sounds, and explosion shader
			cgs.media.breakables[id].model[0] = trap_R_RegisterModel( va("breakables/%s/models/break1.md3",CG_Argv(2)));
 			cgs.media.breakables[id].model[1] = trap_R_RegisterModel( va("breakables/%s/models/break2.md3",CG_Argv(2)));
 			cgs.media.breakables[id].model[2] = trap_R_RegisterModel( va("breakables/%s/models/break3.md3",CG_Argv(2)));
			cgs.media.breakables[id].shader = trap_R_RegisterShader( va("breakable_%s_explosion",CG_Argv(2)));
			cgs.media.breakables[id].sound[0] = trap_S_RegisterSound( va("breakables/%s/sounds/break1.wav", CG_Argv(2)), qfalse);
			cgs.media.breakables[id].sound[1] = trap_S_RegisterSound( va("breakables/%s/sounds/break2.wav", CG_Argv(2)), qfalse);
			cgs.media.breakables[id].sound[2] = trap_S_RegisterSound( va("breakables/%s/sounds/break3.wav", CG_Argv(2)), qfalse);
			cgs.media.breakables[id].exp_sound = trap_S_RegisterSound( va("breakables/%s/sounds/explosion.wav", CG_Argv(2)), qfalse);
      cgs.media.breakables[id].velocity = atoi(CG_Argv(3));
      cgs.media.breakables[id].jump = atoi(CG_Argv(4));
			return;
		} else {
			CG_Printf("ID was %d\n",id);
		}
		return;
	}
*/
	if (!strcmp(cmd, "rq3_cmd")) {
		CG_RQ3_Cmd();
		return;
	}

	if (!strcmp(cmd, "stuff")) {
		char *cmd;

		cmd = CG_ConcatArgs(1);
		trap_SendConsoleCommand(cmd);
		return;
	}

	CG_Printf("Unknown client game command: %s\n", cmd);
}

/*
====================
CG_ExecuteNewServerCommands

Execute all of the server commands that were received along
with this this snapshot.
====================
*/
void CG_ExecuteNewServerCommands(int latestSequence)
{
	while (cgs.serverCommandSequence < latestSequence) {
		if (trap_GetServerCommand(++cgs.serverCommandSequence)) {
			CG_ServerCommand();
		}
	}
}
