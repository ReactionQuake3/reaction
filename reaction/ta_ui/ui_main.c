//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log: ui_main.c,v $
// Revision 1.84  2007/02/03 15:02:21  jbravo
// Renamed RQ3 to Reaction, Dropped loading of various baseq3 media, disabled the follow command, fixed grenades killing teammates and some cleanups
//
// Revision 1.83  2006/04/14 18:02:06  makro
// no message
//
// Revision 1.82  2005/09/07 20:24:33  makro
// Vector support for most item types
//
// Revision 1.81  2005/02/15 16:33:39  makro
// Tons of updates (entity tree attachment system, UI vectors)
//
// Revision 1.80  2004/03/12 11:26:05  makro
// no messaged
//
// Revision 1.79  2004/01/26 21:26:09  makro
// no message
//
// Revision 1.78  2003/09/01 15:09:49  jbravo
// Cleanups, crashbug fix and version bumped to 3.2
//
// Revision 1.77  2003/04/26 15:23:57  jbravo
// grenade replacement fix.  Version bumped to 3.1
//
// Revision 1.76  2003/04/26 10:37:02  slicer
// Small fix from "radio imhit" to "radio im_hit"
//
// Revision 1.75  2003/04/26 02:03:51  jbravo
// Helmet fixes
//
// Revision 1.74  2003/04/19 17:41:26  jbravo
// Applied changes that where in 1.29h -> 1.32b gamecode.
//
// Revision 1.73  2003/04/13 16:56:22  makro
// In-game browser was showing "reaction" servers instead of "rq3" ones
//
// Revision 1.72  2003/04/07 02:18:49  jbravo
// Removed more unlagged stuff that was messing up impact marks and fixed a
// booboo in the UI ssg xhair previews.
//
// Revision 1.71  2003/04/06 18:31:21  makro
// SSG crosshairs
//
// Revision 1.70  2003/03/31 21:02:30  makro
// no message
//
// Revision 1.69  2003/03/31 15:17:58  makro
// Replacements system tweaks.
// Fixed some other bugs.
//
// Revision 1.68  2003/03/31 05:54:20  jbravo
// More replacementhacks
//
// Revision 1.67  2003/03/31 04:55:58  jbravo
// Small UI replacements fixes.
//
// Revision 1.66  2003/03/31 01:23:54  jbravo
// Fixing 2 compiler warnings
//
// Revision 1.65  2003/03/31 00:23:18  makro
// Replacements and stuff
//
// Revision 1.64  2003/03/28 10:36:02  jbravo
// Tweaking the replacement system a bit.  Reactionmale now the default model
//
// Revision 1.63  2003/03/02 21:12:46  jbravo
// Version bumped to 3.0.  Lets try and keep it list this.
//
// Revision 1.62  2003/02/26 18:22:05  makro
// Added an option to change crosshair size in assetGlobalDef's
//
// Revision 1.61  2003/02/25 22:41:14  jbravo
// Fixed a bug in item replacements. Removed "Beta" from the version.
//
// Revision 1.60  2003/02/16 21:39:10  makro
// Fixed "timelimit is read only" on local servers error
//
// Revision 1.59  2003/02/13 21:19:51  makro
// no message
//
// Revision 1.58  2002/12/09 00:58:49  makro
// Items are now disabled from the weapon/item menus in teamplay
// games if they are banned from the server
//
// Revision 1.57  2002/11/09 14:17:51  makro
// Cleaned up about menu code
// Made the weapon menu unavailable in TDM if g_RQ3_tdmMode is not 0
//
// Revision 1.56  2002/11/09 13:05:02  makro
// g_RQ3_teamXname cvars are now used in the join menu
//
// Revision 1.55  2002/10/31 01:10:07  jbravo
// Bumped the version to 2.3
//
// Revision 1.54  2002/10/29 01:34:52  jbravo
// Added g_RQ3_tdmMode (0 = TP style, 1 = DM style) including UI support.
//
// Revision 1.53  2002/09/09 02:39:22  niceass
// updated version again from 2.21 to 2.25
//
// Revision 1.52  2002/09/08 19:46:46  makro
// Commented out the code that filters servers based on gametype
//
// Revision 1.51  2002/09/08 13:14:47  makro
// New code added for the callvote menu map list
//
// Revision 1.50  2002/09/08 00:34:26  jbravo
// Bumped version to 2.21
//
// Revision 1.49  2002/09/01 12:30:29  makro
// Small fixes
//
// Revision 1.48  2002/08/30 17:22:29  makro
// Added clientNum info to the UI; made ref kick and referee ui scripts
// use client nums instead of names
//
// Revision 1.47  2002/08/30 15:09:43  makro
// MM UI
//
// Revision 1.46  2002/08/26 00:41:52  makro
// Presets menu + editor
//
// Revision 1.45  2002/07/26 22:28:38  jbravo
// Fixed the server about menu, made the UI handle illegal models and skins
// better.
//
// Revision 1.44  2002/07/26 06:21:43  jbravo
// Fixed the MM settings stuff so it works on remote servers also.
// Removed the MM_NAMES_COLOR since it broke on nicks with color in them.
//
// Revision 1.43  2002/07/07 18:36:13  jbravo
// Added an AntiIdle system. Can play insane sounds for idle players, drop them
// from teams or kick them.   Upped version to Beta 2.1
//
// Revision 1.42  2002/07/04 16:07:54  slicer
// Small fix for the "settings" cmd
//
// Revision 1.41  2002/07/02 09:51:29  makro
// In-game server info code
//
// Revision 1.40  2002/06/29 04:15:15  jbravo 
// CTF is now CTB.  no weapons while the case is in hand other than pistol or knife 
// 
// Revision 1.39  2002/06/28 21:20:44  makro
// More MM...
//
// Revision 1.38  2002/06/28 20:30:35  makro
// MM
//
// Revision 1.37  2002/06/28 20:08:42  makro
// MM stuff
//
// Revision 1.36  2002/06/24 12:29:43  makro
// Enabled weapon/item menus in CTF
//
// Revision 1.35  2002/06/24 12:21:09  makro
// New UI sscript that uses the "settings" command
//
// Revision 1.34  2002/06/16 20:06:15  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.33  2002/06/15 13:19:17  makro
// Support for adding random bots when starting up a game from the UI
//
// Revision 1.32  2002/06/13 15:50:24  makro
// Bot list is now sorted alphabetically
//
// Revision 1.31  2002/06/12 11:15:31  makro
// Support for changing the SSG crosshair. Some other stuff
//
// Revision 1.30  2002/06/09 18:56:53  makro
// Removed teamcount cvars
//
// Revision 1.29  2002/06/09 15:35:23  makro
// "wait" command is no longer executed before adding a bot
// when starting a server from the UI
//
// Revision 1.28  2002/06/05 19:17:07  makro
// Squashed some bugs :)
//
// Revision 1.27  2002/06/04 21:19:10  makro
// Added leading zero's in the "last refresh time" text
//
// Revision 1.26  2002/06/02 22:22:04  makro
// Bug in the server browser
//
// Revision 1.25  2002/06/02 00:15:07  makro
// Small fixes
//
// Revision 1.24  2002/05/29 13:30:19  makro
// Weapon/join menu tweaks
//
// Revision 1.23  2002/05/19 21:31:22  makro
// Stuff
//
// Revision 1.22  2002/05/19 15:45:03  makro
// "Specify server" option
//
// Revision 1.21  2002/05/15 12:48:17  makro
// Fixed a bug with bots + teams
//
// Revision 1.20  2002/05/12 22:15:13  makro
// Support for ignore/unignore
//
// Revision 1.19  2002/04/30 11:56:54  makro
// Stuff
//
// Revision 1.18  2002/04/22 18:40:58  makro
// Model validation
//
// Revision 1.17  2002/04/20 15:06:28  makro
// Cool stuff :p
//
// Revision 1.16  2002/04/14 21:50:55  makro
// Stuff
//
// Revision 1.15  2002/04/07 17:51:49  makro
// Abbey
//
// Revision 1.14  2002/04/06 21:40:59  makro
// Delayed in-game bot adds. Fixed a small bug in the key
// handling code for bot names.
//
// Revision 1.13  2002/04/03 17:38:09  makro
// Commented out another unused function
//
// Revision 1.12  2002/04/03 16:34:29  makro
// Got rid of one more warning
//
// Revision 1.11  2002/03/31 14:14:42  makro
// Cleaned up a little more
//
// Revision 1.10  2002/03/31 13:23:26  makro
// Cleaned things up a little
//
// Revision 1.9  2002/03/25 13:51:14  makro
// Added teamCount cvars
//
// Revision 1.8  2002/03/24 21:26:14  makro
// no message
//
// Revision 1.7  2002/03/14 21:52:08  makro
// no message
//
// Revision 1.6  2002/03/10 22:10:10  makro
// no message
//
// Revision 1.5  2002/03/03 21:22:58  makro
// no message
//
// Revision 1.3  2002/02/21 20:10:16  jbravo
// Converted files back from M$ format and added cvs headers again.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
/*
=======================================================================

USER INTERFACE MAIN

=======================================================================
*/

// use this to get a demo build without an explicit demo build, i.e. to get the demo ui files to build
//#define PRE_RELEASE_TADEMO

#include "ui_local.h"

uiInfo_t uiInfo;

static const char *MonthAbbrev[] = {
	"Jan", "Feb", "Mar",
	"Apr", "May", "Jun",
	"Jul", "Aug", "Sep",
	"Oct", "Nov", "Dec"
};

static const char *skillLevels[] = {
	"I Can Win",
	"Bring It On",
	"Hurt Me Plenty",
	"Hardcore",
	"Nightmare"
};

//Makro - changed from macros to constants
const char *KEYBIND_STATUS1 = "ENTER or CLICK to change, BACKSPACE to clear";
const char *KEYBIND_STATUS2 = "Waiting for new key... Press ESCAPE to cancel";

static const int numSkillLevels = sizeof(skillLevels) / sizeof(const char *);

static const char *netSources[] = {
	"Local",
	"Mplayer",
	"Internet",
	"Favorites"
};
static const int numNetSources = sizeof(netSources) / sizeof(const char *);

//Makro - replacement types/subtypes
typedef struct {
	const char *displayName, *cvarName;
} replacementSubtype_t;

static replacementSubtype_t replacementTypes[] = {
	{"Weapons",		"weapons2"},
	{"Items",		"items"},
	{"Ammo",		"ammo"}
};
static const int replacementTypeCount = sizeof(replacementTypes) / sizeof(replacementSubtype_t);

// WEAPONS //
static replacementSubtype_t replacementWeapons[] =
{
	{"Mk23",		"mk23"},
	{"M3",			"m3"},
	{"MP5",			"mp5"},
	{"Handcannon",	"handcannon"},
	{"SSG3000",		"ssg3000"},
	{"M4",			"m4"},
	{"Grenade",		"grenade"},
	{"Akimbo",		"akimbo"},
	{"Knife",		"knife"}
};
static const int replacementWeapCount = sizeof(replacementWeapons) / sizeof(replacementSubtype_t);

// ITEMS //
static replacementSubtype_t replacementItems[] =
{
	{"Kevlar",		"kevlar"},
	{"Bandolier",		"bandolier"},
	{"Silencer",		"silencer"},
	{"Laser",		"laser"},
	{"Slippers",		"slippers"},
	{"Helmet",		"helmet"}
};
static const int replacementItemCount = sizeof(replacementItems) / sizeof(replacementSubtype_t);

// AMMO //
static replacementSubtype_t replacementAmmo[] =
{
	{"Mk23",		"ammo_mk23"},
	{"Shells",		"ammo_m3"},
	{"SSG3000",		"ammo_ssg3000"},
	{"MP5",			"ammo_mp5"},
	{"M4",			"ammo_m4"}
};
static const int replacementAmmoCount = sizeof(replacementAmmo) / sizeof(replacementSubtype_t);

static const serverFilter_t serverFilters[] = {
//Makro - we only want Reaction servers in the server list
/*	{"All", "" },
	{"Quake 3 Arena", "" },
	{"Team Arena", "missionpack" },
	{"Rocket Arena", "arena" },
	{"Alliance", "alliance20" },
	{"Weapons Factory Arena", "wfa" },
	{"OSP", "osp" },
	{"All", "" },*/
	//Makro - hack !!!
	{"Reaction", "rq3"}
};

static const char *teamArenaGameTypes[] = {
	"RQ3 DM",
	"TOURNAMENT",
	"SP",
	"TEAM DM",
//Makro - inserted teamplay
	"RQ3 TP",
	"CTF",
	"1FCTF",
	"OVERLOAD",
	"HARVESTER",
	"TEAMTOURNAMENT"
};

static int const numTeamArenaGameTypes = sizeof(teamArenaGameTypes) / sizeof(const char *);

static const char *teamArenaGameNames[] = {
	"Deathmatch",
	"Tournament",
	"Deathmatch (SP)",
	"Team Deathmatch",
//Makro - inserted teamplay
	"Teamplay",
	"Capture the Briefcase",
	"One Flag CTF",
	"Overload",
	"Harvester",
	"Team Tournament",
};

static int const numTeamArenaGameNames = sizeof(teamArenaGameNames) / sizeof(const char *);

static const int numServerFilters = sizeof(serverFilters) / sizeof(serverFilter_t);

static const char *sortKeys[] = {
	"Server Name",
	"Map Name",
	"Open Player Spots",
	"Game Type",
	"Ping Time"
};
static const int numSortKeys = sizeof(sortKeys) / sizeof(const char *);

//Makro - radio presets
typedef struct {
	vmCvar_t *Text, *Script;
} radioPreset_t;
radioPreset_t radioPresets[] =
{
	{&ui_RQ3_radioPreset1Desc, &ui_RQ3_radioPreset1Script},
	{&ui_RQ3_radioPreset2Desc, &ui_RQ3_radioPreset2Script},
	{&ui_RQ3_radioPreset3Desc, &ui_RQ3_radioPreset3Script},
	{&ui_RQ3_radioPreset4Desc, &ui_RQ3_radioPreset4Script},
	{&ui_RQ3_radioPreset5Desc, &ui_RQ3_radioPreset5Script},
	{&ui_RQ3_radioPreset6Desc, &ui_RQ3_radioPreset6Script},
	{&ui_RQ3_radioPreset7Desc, &ui_RQ3_radioPreset7Script},
	{&ui_RQ3_radioPreset8Desc, &ui_RQ3_radioPreset8Script},
	{&ui_RQ3_radioPreset9Desc, &ui_RQ3_radioPreset9Script},
	{&ui_RQ3_radioPreset10Desc, &ui_RQ3_radioPreset10Script}
};
static const int numRadioPresets = sizeof(radioPresets) / sizeof(radioPreset_t);



static char *netnames[] = {
	"???",
	"UDP",
	"IPX",
	NULL
};

//Makro - not used anywhere
//#ifndef MISSIONPACK // bk001206
//static char quake3worldMessage[] = "Visit www.quake3world.com - News, Community, Events, Files";
//#endif

static int gamecodetoui[] = { 4, 2, 3, 0, 5, 1, 6 };
static int uitogamecode[] = { 4, 6, 2, 3, 1, 5, 7 };

static void UI_StartServerRefresh(qboolean full);
static void UI_StopServerRefresh(void);
static void UI_DoServerRefresh(void);
static void UI_FeederSelection(float feederID, int index);
static void UI_BuildServerDisplayList(qboolean force);
static void UI_BuildServerStatus(qboolean force);
static void UI_BuildFindPlayerList(qboolean force);
static int QDECL UI_ServersQsortCompare(const void *arg1, const void *arg2);
static int UI_MapCountByGameType(qboolean singlePlayer);
static int UI_HeadCountByTeam(void);
static void UI_ParseGameInfo(const char *teamFile);
static void UI_ParseTeamInfo(const char *teamFile);
static const char *UI_SelectedMap(int index, int *actual);
static const char *UI_SelectedHead(int index, int *actual);
//Makro - added
static int UI_MapCountVote(void);

static int UI_GetIndexFromSelection(int actual);

int ProcessNewUI(int command, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);

/*
================
vmMain

This is the only way control passes into the module.
This must be the very first function compiled into the .qvm file
================
*/
vmCvar_t ui_new;
//Makro - renamed to ui_developer
//vmCvar_t ui_debug;
vmCvar_t ui_developer;
vmCvar_t ui_initialized;
vmCvar_t ui_reaction33FirstRun;

void _UI_Init(qboolean);
void _UI_Shutdown(void);
void _UI_KeyEvent(int key, qboolean down);
void _UI_MouseEvent(int dx, int dy);
void _UI_Refresh(int realtime);
qboolean _UI_IsFullscreen(void);
int vmMain(int command, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8,
	   int arg9, int arg10, int arg11)
{
	switch (command) {
	case UI_GETAPIVERSION:
		return UI_API_VERSION;

	case UI_INIT:
		_UI_Init(arg0);
		return 0;

	case UI_SHUTDOWN:
		_UI_Shutdown();
		return 0;

	case UI_KEY_EVENT:
		_UI_KeyEvent(arg0, arg1);
		return 0;

	case UI_MOUSE_EVENT:
		_UI_MouseEvent(arg0, arg1);
		return 0;

	case UI_REFRESH:
		_UI_Refresh(arg0);
		return 0;

	case UI_IS_FULLSCREEN:
		return _UI_IsFullscreen();

	case UI_SET_ACTIVE_MENU:
		_UI_SetActiveMenu(arg0);
		return 0;

	case UI_CONSOLE_COMMAND:
		return UI_ConsoleCommand(arg0);

	case UI_DRAW_CONNECT_SCREEN:
		UI_DrawConnectScreen(arg0);
		return 0;
	case UI_HASUNIQUECDKEY:	// mod authors need to observe this
		return qtrue;	// bk010117 - change this to qfalse for mods!

	}

	return -1;
}

/*
==========================
UI_FileExists

Makro - moved from ui_players.c
==========================
*/
qboolean UI_FileExists(const char *filename)
{
	int len;

	len = trap_FS_FOpenFile(filename, 0, FS_READ);
	if (len > 0) {
		return qtrue;
	}
	return qfalse;
}

//Makro - registers an asset; path is relative to the assetsPath
qhandle_t Asset_RegisterShaderNoMip(const char *path)
{
	if (!path)
		return 0;
	if (!uiInfo.uiDC.Assets.assetsPath)
		return trap_R_RegisterShaderNoMip(va("ui/assets/%s", path));
	return trap_R_RegisterShaderNoMip(va("%s/%s", uiInfo.uiDC.Assets.assetsPath, path));
}

void AssetCache()
{
	int n, ssg;

	//if (Assets.textFont == NULL) {
	//}
	//Assets.background = trap_R_RegisterShaderNoMip( ASSET_BACKGROUND );
	//Com_Printf("Menu Size: %i bytes\n", sizeof(Menus));
	uiInfo.uiDC.Assets.gradientBar = Asset_RegisterShaderNoMip(ASSET_GRADIENTBAR);
	uiInfo.uiDC.Assets.fxBasePic = trap_R_RegisterShaderNoMip(ART_FX_BASE);
	uiInfo.uiDC.Assets.fxPic[0] = trap_R_RegisterShaderNoMip(ART_FX_RED);
	uiInfo.uiDC.Assets.fxPic[1] = trap_R_RegisterShaderNoMip(ART_FX_YELLOW);
	uiInfo.uiDC.Assets.fxPic[2] = trap_R_RegisterShaderNoMip(ART_FX_GREEN);
	uiInfo.uiDC.Assets.fxPic[3] = trap_R_RegisterShaderNoMip(ART_FX_TEAL);
	uiInfo.uiDC.Assets.fxPic[4] = trap_R_RegisterShaderNoMip(ART_FX_BLUE);
	uiInfo.uiDC.Assets.fxPic[5] = trap_R_RegisterShaderNoMip(ART_FX_CYAN);
	uiInfo.uiDC.Assets.fxPic[6] = trap_R_RegisterShaderNoMip(ART_FX_WHITE);
	uiInfo.uiDC.Assets.scrollBarH = Asset_RegisterShaderNoMip(ASSET_SCROLLBAR_H);
	uiInfo.uiDC.Assets.scrollBarV = Asset_RegisterShaderNoMip(ASSET_SCROLLBAR_V);
	uiInfo.uiDC.Assets.scrollBarArrowDown = Asset_RegisterShaderNoMip(ASSET_SCROLLBAR_ARROWDOWN);
	uiInfo.uiDC.Assets.scrollBarArrowUp = Asset_RegisterShaderNoMip(ASSET_SCROLLBAR_ARROWUP);
	uiInfo.uiDC.Assets.scrollBarArrowLeft = Asset_RegisterShaderNoMip(ASSET_SCROLLBAR_ARROWLEFT);
	uiInfo.uiDC.Assets.scrollBarArrowRight = Asset_RegisterShaderNoMip(ASSET_SCROLLBAR_ARROWRIGHT);
	uiInfo.uiDC.Assets.scrollBarThumb = Asset_RegisterShaderNoMip(ASSET_SCROLL_THUMB);
	//Makro - shown when clicked
	uiInfo.uiDC.Assets.scrollBarArrowDown2 = Asset_RegisterShaderNoMip(ASSET_SCROLLBAR_ARROWDOWN2);
	uiInfo.uiDC.Assets.scrollBarArrowUp2 = Asset_RegisterShaderNoMip(ASSET_SCROLLBAR_ARROWUP2);
	uiInfo.uiDC.Assets.scrollBarArrowLeft2 = Asset_RegisterShaderNoMip(ASSET_SCROLLBAR_ARROWLEFT2);
	uiInfo.uiDC.Assets.scrollBarArrowRight2 = Asset_RegisterShaderNoMip(ASSET_SCROLLBAR_ARROWRIGHT2);
	uiInfo.uiDC.Assets.sliderBar0 = Asset_RegisterShaderNoMip(ASSET_SLIDER_BAR0);
	uiInfo.uiDC.Assets.sliderBar1 = Asset_RegisterShaderNoMip(ASSET_SLIDER_BAR1);
	uiInfo.uiDC.Assets.sliderThumb = Asset_RegisterShaderNoMip(ASSET_SLIDER_THUMB);
	
	uiInfo.uiDC.Assets.defaultLevelshot = trap_R_RegisterShaderNoMip("menu/art/unknownmap");

	for (n = 0; n < NUM_CROSSHAIRS; n++) {
		uiInfo.uiDC.Assets.crosshairShader[n] = trap_R_RegisterShaderNoMip(va("gfx/2d/crosshair%c", 'a' + n));
	}

	//Makro - for the SSG crosshair preview
	ssg = (int) trap_Cvar_VariableValue("cg_RQ3_ssgCrosshair") % NUM_SSGCROSSHAIRS;
	uiInfo.uiDC.Assets.SSGcrosshairShader = trap_R_RegisterShaderNoMip(va("gfx/rq3_hud/ssg2x-%i", ssg));

	//Makro - for drop shadows
	for (n = 0; n < 4; n++) {
		uiInfo.uiDC.Assets.dropShadowCorners[n] =
		    Asset_RegisterShaderNoMip(va("rq3-ingame-shadow-c%i", n + 1));
	}
	uiInfo.uiDC.Assets.dropShadowRight = Asset_RegisterShaderNoMip("rq3-ingame-shadow-right");
	uiInfo.uiDC.Assets.dropShadowBottom = Asset_RegisterShaderNoMip("rq3-ingame-shadow-bottom");
	
	uiInfo.newHighScoreSound = trap_S_RegisterSound("sound/feedback/voc_newhighscore.wav", qfalse);
}

//Makro - angled rectangles
void _UI_DrawAngledRect(float x, float y, float w, float h, const float *u, const float *v, float size, const float *color, unsigned char type, qhandle_t shader)
{
	float p[2], p2[2];
	
	p[0] = x;
	p[1] = y;
	Vector2MA(p, w, u, p2);
	Vector2MA(p2, h, v, p2);

	if (type & RECT_TOPBOTTOM) {
		uiInfo.uiDC.drawAngledPic(p[0], p[1], w, size, u, v, color, 0, 0, 1, 1, shader);
		uiInfo.uiDC.drawAngledPic(p2[0], p2[1], -w, -size, u, v, color, 0, 0, 1, 1, shader);
	}
	if (type & RECT_SIDES) {
		uiInfo.uiDC.drawAngledPic(p[0], p[1], size, h, u, v, color, 0, 0, 1, 1, shader);
		uiInfo.uiDC.drawAngledPic(p2[0], p2[1], -size, -h, u, v, color, 0, 0, 1, 1, shader);
	}
}

//Makro - added shader
void _UI_DrawSides(float x, float y, float w, float h, float size, qhandle_t shader)
{
	UI_AdjustFrom640(&x, &y, &w, &h);
	size *= uiInfo.uiDC.xscale;
	//trap_R_DrawStretchPic(x, y, size, h, 0, 0, 0, 0, uiInfo.uiDC.whiteShader);
	//trap_R_DrawStretchPic(x + w - size, y, size, h, 0, 0, 0, 0, uiInfo.uiDC.whiteShader);
	uiInfo.uiDC.drawStretchPic(x, y, size, h, 0, 0, 0, 0, shader, qfalse);
	uiInfo.uiDC.drawStretchPic(x + w - size, y, size, h, 0, 0, 0, 0, shader, qfalse);
}

//Makro - added shader
void _UI_DrawTopBottom(float x, float y, float w, float h, float size, qhandle_t shader)
{
	UI_AdjustFrom640(&x, &y, &w, &h);
	size *= uiInfo.uiDC.yscale;
	//trap_R_DrawStretchPic(x, y, w, size, 0, 0, 0, 0, uiInfo.uiDC.whiteShader);
	//trap_R_DrawStretchPic(x, y + h - size, w, size, 0, 0, 0, 0, uiInfo.uiDC.whiteShader);
	uiInfo.uiDC.drawStretchPic(x, y, w, size, 0, 0, 0, 0, shader, qfalse);
	uiInfo.uiDC.drawStretchPic(x, y + h - size, w, size, 0, 0, 0, 0, shader, qfalse);
}

/*
================
UI_DrawRect

Coordinates are 640*480 virtual values
=================
*/
//Makro - added shader
void _UI_DrawRect(float x, float y, float width, float height, float size, const float *color, qhandle_t shader)
{
	trap_R_SetColor(color);

	_UI_DrawTopBottom(x, y, width, height, size, shader);
	_UI_DrawSides(x, y, width, height, size, shader);

	trap_R_SetColor(NULL);
}

int Text_Width(const char *text, float scale, int limit)
{
	int count, len, maxPixels = 0;
	float out;
	glyphInfo_t *glyph;
	float useScale;

	const char *s = text;
	fontInfo_t *font = &uiInfo.uiDC.Assets.textFont;

	if (scale <= ui_smallFont.value) {
		font = &uiInfo.uiDC.Assets.smallFont;
	} else if (scale >= ui_bigFont.value) {
		font = &uiInfo.uiDC.Assets.bigFont;
	}
	useScale = scale * font->glyphScale;
	out = 0;
	if (text) {
		//Makro - strlen doesn't take into account color escape sequences
		len = Q_PrintStrlen(text);
		//Makro - new feature: negative limit = -max pixels
		if (limit < 0) {
			maxPixels = -limit;
		} else if (limit > 0 && len > limit) {
			len = limit;
		}
		count = 0;
		while (s && *s && count < len) {
			if (Q_IsColorString(s)) {
				s += 2;
				continue;
			} else {
				glyph = &font->glyphs[(int) *s];
				out += glyph->xSkip;
				//Makro - added
				if (maxPixels)
					if (out > maxPixels)
						break;
				s++;
				count++;
			}
		}
	}
	return (int) (out * useScale);
}

int Text_Height(const char *text, float scale, int limit)
{
	int len, count;
	float max;
	glyphInfo_t *glyph;
	float useScale;
	const char *s = text;	// bk001206 - unsigned
	fontInfo_t *font = &uiInfo.uiDC.Assets.textFont;

	if (scale <= ui_smallFont.value) {
		font = &uiInfo.uiDC.Assets.smallFont;
	} else if (scale >= ui_bigFont.value) {
		font = &uiInfo.uiDC.Assets.bigFont;
	}
	useScale = scale * font->glyphScale;
	max = 0;
	if (text) {
		len = strlen(text);
		if (limit > 0 && len > limit) {
			len = limit;
		}
		count = 0;
		while (s && *s && count < len) {
			if (Q_IsColorString(s)) {
				s += 2;
				continue;
			} else {
				glyph = &font->glyphs[(int) *s];	// TTimo: FIXME: getting nasty warnings without the cast, hopefully this doesn't break the VM build
				if (max < glyph->height) {
					max = glyph->height;
				}
				s++;
				count++;
			}
		}
	}
	return max * useScale;
}

//Makro - added
//FIXME: doesn't take into account color escape sequences
//also, Text_Width now supports pixel limits, not just char count limits
int Text_maxPaintChars(char *text, float scale, float width)
{
	char buf[1024];
	int l;

	if (!text)
		return 0;

	Q_strncpyz(buf, text, sizeof(buf));
	l = strlen(buf);
	while (l>=0 && Text_Width(buf, scale, 0) > width)
		buf[--l]=0;

	return l;
}

void Text_PaintChar(float x, float y, float width, float height, float scale, float s, float t, float s2, float t2,
		    qhandle_t hShader)
{
	float w, h;

	w = width * scale;
	h = height * scale;
	UI_AdjustFrom640(&x, &y, &w, &h);
	//trap_R_DrawStretchPic(x, y, w, h, s, t, s2, t2, hShader);
	uiInfo.uiDC.drawStretchPic(x, y, w, h, s, t, s2, t2, hShader, qfalse);
}



void Text_Paint(float x, float y, float scale, vec4_t color, const char *text, float adjust, int limit, float maxwidth, int style, qboolean forceColor)
{
	int len, count;
	qboolean underlined = qfalse;
	//Makro - added width
	float width;
	vec4_t newColor;
	float useScale;
	fontInfo_t *font = &uiInfo.uiDC.Assets.textFont;
	glyphInfo_t *glyph, *uglyph = &font->glyphs[(int)'_']; //Makro - added for underlined chars;

	if (scale <= ui_smallFont.value) {
		font = &uiInfo.uiDC.Assets.smallFont;
	} else if (scale >= ui_bigFont.value) {
		font = &uiInfo.uiDC.Assets.bigFont;
	}
	useScale = scale * font->glyphScale;
	if (text) {
// TTimo: FIXME         
//    const unsigned char *s = text; // bk001206 - unsigned
		const char *s = text;	// bk001206 - unsigned

		trap_R_SetColor(color);
		memcpy(&newColor[0], &color[0], sizeof(vec4_t));
		//Makro - changed
		//len = strlen(text);
		len = Q_PrintStrlen(text);
		if (limit > 0 && len > limit) {
			len = limit;
		}
		count = 0;
		width = 0;
		while (s && *s && count < len) {
			glyph = &font->glyphs[(int) *s];	// TTimo: FIXME: getting nasty warnings without the cast, hopefully this doesn't break the VM build
			//int yadj = Assets.textFont.glyphs[text[i]].bottom + Assets.textFont.glyphs[text[i]].top;
			//float yadj = scale * (Assets.textFont.glyphs[text[i]].imageHeight - Assets.textFont.glyphs[text[i]].height);
			if (Q_IsColorString(s)) {
				//Makro - new tricks
				if (*(s+1) == '*')
				{
					memcpy(newColor, color, sizeof(newColor));
					trap_R_SetColor(newColor);
				} else if (*(s+1)== '_')
				{
					underlined ^= qtrue;
				} else if (!forceColor) {
					memcpy(newColor, g_color_table[ColorIndex(*(s + 1))], sizeof(newColor));
					newColor[3] = color[3];
					trap_R_SetColor(newColor);
				}
				s += 2;
				continue;
			} else {
				float yadj = useScale * glyph->top;
				if (style == ITEM_TEXTSTYLE_SHADOWED || style == ITEM_TEXTSTYLE_SHADOWEDMORE) {
					int ofs = style == ITEM_TEXTSTYLE_SHADOWED ? 1 : 2;

					colorBlack[3] = newColor[3];
					trap_R_SetColor(colorBlack);
					Text_PaintChar(x + ofs, y - yadj + ofs,
						       glyph->imageWidth,
						       glyph->imageHeight,
						       useScale,
						       glyph->s, glyph->t, glyph->s2, glyph->t2, glyph->glyph);
					trap_R_SetColor(newColor);
					colorBlack[3] = 1.0;
				}
				Text_PaintChar(x, y - yadj,
					       glyph->imageWidth,
					       glyph->imageHeight,
					       useScale, glyph->s, glyph->t, glyph->s2, glyph->t2, glyph->glyph);
				//Makro - added
				if (underlined)
				{
					Text_PaintChar(x, y, glyph->imageWidth, uglyph->imageHeight,
						useScale, uglyph->s, uglyph->t, uglyph->s2, uglyph->t2, uglyph->glyph);
				}

				//Makro - added width
				width += (glyph->xSkip * useScale) + adjust;
				if (maxwidth > 0 && width > maxwidth)
					break;

				x += (glyph->xSkip * useScale) + adjust;
				s++;
				count++;
			}
		}
		trap_R_SetColor(NULL);
	}
}

void UI_AddQuadToScene(qhandle_t hShader, const polyVert_t *verts)
{
	polyVert_t mverts[4];

	memcpy(mverts, verts, sizeof(mverts));
	mverts[0].xyz[0] -= uiInfo.uiDC.polyZ;
	mverts[1].xyz[0] -= uiInfo.uiDC.polyZ;
	mverts[2].xyz[0] -= uiInfo.uiDC.polyZ;
	mverts[3].xyz[0] -= uiInfo.uiDC.polyZ;

	trap_R_AddPolyToScene(hShader, 4, mverts);
	uiInfo.uiDC.polyZ += UI_POLY_Z_OFFSET;
	uiInfo.uiDC.pendingPolys++;
}

/*
void _UI_DrawAngledRect(float x, float y, float w, float h, const float *u, const float *v, float size, const float *color, unsigned char type)
{
	float p[2], p2[2];
	
	p[0] = x;
	p[1] = y;
	Vector2MA(p, w, u, p2);
	Vector2MA(p2, h, v, p2);

	if (type & RECT_TOPBOTTOM) {
		uiInfo.uiDC.drawAngledPic(p[0], p[1], w, size, u, v, color, 0, 0, 1, 1, uiInfo.uiDC.whiteShader);
		uiInfo.uiDC.drawAngledPic(p2[0], p2[1], -w, -size, u, v, color, 0, 0, 1, 1, uiInfo.uiDC.whiteShader);
	}
	if (type & RECT_SIDES) {
		uiInfo.uiDC.drawAngledPic(p[0], p[1], size, h, u, v, color, 0, 0, 1, 1, uiInfo.uiDC.whiteShader);
		uiInfo.uiDC.drawAngledPic(p2[0], p2[1], -size, -h, u, v, color, 0, 0, 1, 1, uiInfo.uiDC.whiteShader);
	}
}
*/

//TODO
void UI_AddFrameToScene(float x, float y, float w, float h, const float *u, const float *v, float size, const float *color, unsigned char type)
{
	polyVert_t verts[4];

	verts[0].modulate[0]=verts[1].modulate[0]=verts[2].modulate[0]=verts[3].modulate[0]=((int)(color[0]*255))&255;
	verts[0].modulate[1]=verts[1].modulate[1]=verts[2].modulate[1]=verts[3].modulate[1]=((int)(color[1]*255))&255;
	verts[0].modulate[2]=verts[1].modulate[2]=verts[2].modulate[2]=verts[3].modulate[2]=((int)(color[2]*255))&255;
	verts[0].modulate[3]=verts[1].modulate[3]=verts[2].modulate[3]=verts[3].modulate[3]=((int)(color[3]*255))&255;
	//0
	verts[0].st[0]=0;
	verts[0].st[1]=0;
	//1
	verts[1].st[0]=1;
	verts[1].st[1]=0;
	//2
	verts[2].st[0]=1;
	verts[2].st[1]=1;
	//3
	verts[3].st[0]=0;
	verts[3].st[1]=1;
	VectorSet(verts[0].xyz, 320, 320-x, 240-y);
	VectorSet(verts[1].xyz, 320, verts[0].xyz[1]-u[0]*w, verts[0].xyz[2]-u[1]*w);
	VectorSet(verts[2].xyz, 320, verts[1].xyz[1]-v[0]*h, verts[1].xyz[2]-v[1]*h);
	VectorSet(verts[3].xyz, 320, verts[0].xyz[1]-v[0]*h, verts[0].xyz[2]-v[1]*h);
	verts[0].xyz[0] -= uiInfo.uiDC.polyZ;
	verts[1].xyz[0] -= uiInfo.uiDC.polyZ;
	verts[2].xyz[0] -= uiInfo.uiDC.polyZ;
	verts[3].xyz[0] -= uiInfo.uiDC.polyZ;

	trap_R_AddPolyToScene(uiInfo.uiDC.whiteShader, 4, verts);
	uiInfo.uiDC.polyZ += UI_POLY_Z_OFFSET;
	uiInfo.uiDC.pendingPolys++;
}

//Makro - draws a skewed textured rectangle
void UI_DrawAngledPic(float x, float y, float w, float h, const float *u, const float *v, const float *color, float s, float t, float s2, float t2, qhandle_t hShader)
{
	polyVert_t verts[4];
	//memset(verts, 0, sizeof(verts));
	
	//avoid "null poly shader" warnings
	if (!hShader)
		return;

	verts[0].modulate[0]=verts[1].modulate[0]=verts[2].modulate[0]=verts[3].modulate[0]=((int)(color[0]*255))&255;
	verts[0].modulate[1]=verts[1].modulate[1]=verts[2].modulate[1]=verts[3].modulate[1]=((int)(color[1]*255))&255;
	verts[0].modulate[2]=verts[1].modulate[2]=verts[2].modulate[2]=verts[3].modulate[2]=((int)(color[2]*255))&255;
	verts[0].modulate[3]=verts[1].modulate[3]=verts[2].modulate[3]=verts[3].modulate[3]=((int)(color[3]*255))&255;
	verts[0].st[0]=s;
	verts[0].st[1]=t;
	verts[1].st[0]=s2;
	verts[1].st[1]=t;
	verts[2].st[0]=s2;
	verts[2].st[1]=t2;
	verts[3].st[0]=s;
	verts[3].st[1]=t2;
	/*
	VectorSet(verts[0].xyz, 320, 320-x, 240-y);
	VectorSet(verts[1].xyz, 320, 320-(x+u[0]*w), 240-(y+u[1]*w));
	VectorSet(verts[2].xyz, 320, 320-(x+u[0]*w+v[0]*h), 240-(y+u[1]*w+v[1]*h));
	VectorSet(verts[3].xyz, 320, 320-(x+v[0]*h), 240-(y+v[1]*h));
	*/
	VectorSet(verts[0].xyz, 320, 320-x, 240-y);
	VectorSet(verts[1].xyz, 320, verts[0].xyz[1]-u[0]*w, verts[0].xyz[2]-u[1]*w);
	VectorSet(verts[2].xyz, 320, verts[1].xyz[1]-v[0]*h, verts[1].xyz[2]-v[1]*h);
	VectorSet(verts[3].xyz, 320, verts[0].xyz[1]-v[0]*h, verts[0].xyz[2]-v[1]*h);

	//trap_R_AddPolyToScene(hShader, 4, verts);
	//uiInfo.uiDC.polyZ += UI_POLY_Z_OFFSET;
	//uiInfo.uiDC.pendingPolys++;

	UI_AddQuadToScene(hShader, verts);
	
	//trap_R_RenderScene(&uiInfo.uiDC.scene2D);
}

//Makro - same as the old Text_Paint, this time using vectors
void Text_PaintAngled(float x, float y, const float *u, const float *v, float scale, vec4_t color, const char *text,
					float adjust, int limit, float maxwidth, int style, qboolean forceColor)
{
	int len, count;
	//Makro - added
	float width;
	qboolean underlined = qfalse;
	vec4_t newColor;
	float useScale;
	float p[2], *colorPtr;
	fontInfo_t *font = &uiInfo.uiDC.Assets.textFont;
	glyphInfo_t *glyph, *uglyph = &font->glyphs[(int)'_']; //Makro - added for underlined chars;
	
	if (scale <= ui_smallFont.value) {
		font = &uiInfo.uiDC.Assets.smallFont;
	} else if (scale >= ui_bigFont.value) {
		font = &uiInfo.uiDC.Assets.bigFont;
	}
	useScale = scale * font->glyphScale;
	
	if (text) {
		// TTimo: FIXME         
		//    const unsigned char *s = text; // bk001206 - unsigned
		const char *s = text;	// bk001206 - unsigned
		
		//trap_R_SetColor(color);
		colorPtr = color;
		memcpy(&newColor[0], &color[0], sizeof(vec4_t));
		len = strlen(text);
		if (limit > 0 && len > limit) {
			len = limit;
		}
		width = 0;
		count = 0;
		while (s && *s && count < len) {
			glyph = &font->glyphs[(int) *s];	// TTimo: FIXME: getting nasty warnings without the cast, hopefully this doesn't break the VM build
			if (Q_IsColorString(s)) {
				//Makro - new tricks
				if (*(s+1) == '*')
				{
					memcpy(newColor, color, sizeof(newColor));
					//trap_R_SetColor(newColor);
					colorPtr = color;
				} else if (*(s+1)== '_')
				{
					underlined ^= qtrue;
				} else if (!forceColor) {
					memcpy(newColor, g_color_table[ColorIndex(*(s + 1))], sizeof(newColor));
					newColor[3] = color[3];
					//trap_R_SetColor(newColor);
					colorPtr = newColor;
				}
				s += 2;
				continue;
			} else {
				float yadj = useScale * glyph->top;
				if (style == ITEM_TEXTSTYLE_SHADOWED || style == ITEM_TEXTSTYLE_SHADOWEDMORE)
				{
					int ofs = style == ITEM_TEXTSTYLE_SHADOWED ? 1 : 2;
					colorBlack[3] = newColor[3];
					
					Vector2Set(p, x, y);
					Vector2MA(p, ofs, u, p);
					Vector2MA(p, ofs-yadj, v, p);
					
					UI_DrawAngledPic(p[0], p[1],
						glyph->imageWidth * useScale,
						glyph->imageHeight * useScale,
						u,v, colorBlack,
						glyph->s, glyph->t, glyph->s2, glyph->t2, glyph->glyph);
					colorBlack[3] = 1.0;
				}
				Vector2Set(p, x, y);
				Vector2MA(p, -yadj, v, p);
				UI_DrawAngledPic(p[0], p[1],
					glyph->imageWidth * useScale,
					glyph->imageHeight * useScale,
					u,v,colorPtr,
					glyph->s, glyph->t, glyph->s2, glyph->t2, glyph->glyph);
				//Makro - added
				if (underlined)
				{
					UI_DrawAngledPic(x, y, glyph->imageWidth * useScale, uglyph->imageHeight * useScale,
						u, v, colorPtr, uglyph->s, uglyph->t, uglyph->s2, uglyph->t2, uglyph->glyph);
				}
				//Makro - added width
				width += (glyph->xSkip * useScale) + adjust;
				if (maxwidth > 0 && width > maxwidth)
					break;
				x += ((glyph->xSkip * useScale) + adjust) * u[0];
				y += ((glyph->xSkip * useScale) + adjust) * u[1];
				s++;
				count++;
			}
		}
	}
}

void Text_PaintWithCursor(float x, float y, float scale, vec4_t color, const char *text, int cursorPos, char cursor,
			  int limit, int style)
{
	int len, count;
	vec4_t newColor;
	glyphInfo_t *glyph, *glyph2;
	float yadj;
	float useScale;
	fontInfo_t *font = &uiInfo.uiDC.Assets.textFont;

	if (scale <= ui_smallFont.value) {
		font = &uiInfo.uiDC.Assets.smallFont;
	} else if (scale >= ui_bigFont.value) {
		font = &uiInfo.uiDC.Assets.bigFont;
	}
	useScale = scale * font->glyphScale;
	if (text) {
// TTimo: FIXME
//    const unsigned char *s = text; // bk001206 - unsigned
		const char *s = text;	// bk001206 - unsigned

		trap_R_SetColor(color);
		memcpy(&newColor[0], &color[0], sizeof(vec4_t));
		len = strlen(text);
		if (limit > 0 && len > limit) {
			len = limit;
		}
		count = 0;
		glyph2 = &font->glyphs[(int) cursor];	// bk001206 - possible signed char
		while (s && *s && count < len) {
			glyph = &font->glyphs[(int) *s];	// TTimo: FIXME: getting nasty warnings without the cast, hopefully this doesn't break the VM build
			//int yadj = Assets.textFont.glyphs[text[i]].bottom + Assets.textFont.glyphs[text[i]].top;
			//float yadj = scale * (Assets.textFont.glyphs[text[i]].imageHeight - Assets.textFont.glyphs[text[i]].height);
			if (Q_IsColorString(s)) {
				memcpy(newColor, g_color_table[ColorIndex(*(s + 1))], sizeof(newColor));
				newColor[3] = color[3];
				trap_R_SetColor(newColor);
				s += 2;
				continue;
			} else {
				yadj = useScale * glyph->top;
				if (style == ITEM_TEXTSTYLE_SHADOWED || style == ITEM_TEXTSTYLE_SHADOWEDMORE) {
					int ofs = style == ITEM_TEXTSTYLE_SHADOWED ? 1 : 2;

					colorBlack[3] = newColor[3];
					trap_R_SetColor(colorBlack);
					Text_PaintChar(x + ofs, y - yadj + ofs,
						       glyph->imageWidth,
						       glyph->imageHeight,
						       useScale,
						       glyph->s, glyph->t, glyph->s2, glyph->t2, glyph->glyph);
					colorBlack[3] = 1.0;
					trap_R_SetColor(newColor);
				}
				Text_PaintChar(x, y - yadj,
					       glyph->imageWidth,
					       glyph->imageHeight,
					       useScale, glyph->s, glyph->t, glyph->s2, glyph->t2, glyph->glyph);

				// CG_DrawPic(x, y - yadj, scale * uiDC.Assets.textFont.glyphs[text[i]].imageWidth, scale * uiDC.Assets.textFont.glyphs[text[i]].imageHeight, uiDC.Assets.textFont.glyphs[text[i]].glyph);
				yadj = useScale * glyph2->top;
				if (count == cursorPos && !((uiInfo.uiDC.realTime / BLINK_DIVISOR) & 1)) {
					Text_PaintChar(x, y - yadj,
						       glyph2->imageWidth,
						       glyph2->imageHeight,
						       useScale,
						       glyph2->s, glyph2->t, glyph2->s2, glyph2->t2, glyph2->glyph);
				}

				x += (glyph->xSkip * useScale);
				s++;
				count++;
			}
		}
		// need to paint cursor at end of text
		if (cursorPos == len && !((uiInfo.uiDC.realTime / BLINK_DIVISOR) & 1)) {
			yadj = useScale * glyph2->top;
			Text_PaintChar(x, y - yadj,
				       glyph2->imageWidth,
				       glyph2->imageHeight,
				       useScale, glyph2->s, glyph2->t, glyph2->s2, glyph2->t2, glyph2->glyph);

		}

		trap_R_SetColor(NULL);
	}
}

//Makro - modified version of Text_PaintAngled
void Text_PaintWithCursorAngled(float x, float y, const float *u, const float *v, float scale, vec4_t color, const char *text,
					int cursorPos, char cursor, int limit, int style)
{
	int len, count;
	//Makro - added
	float width;
	qboolean underlined = qfalse;
	vec4_t newColor;
	float useScale;
	float p[2], *colorPtr;
	fontInfo_t *font = &uiInfo.uiDC.Assets.textFont;
	glyphInfo_t *glyph, *glyph2, *uglyph = &font->glyphs[(int)'_']; //Makro - added for underlined chars;
	
	if (scale <= ui_smallFont.value) {
		font = &uiInfo.uiDC.Assets.smallFont;
	} else if (scale >= ui_bigFont.value) {
		font = &uiInfo.uiDC.Assets.bigFont;
	}
	useScale = scale * font->glyphScale;
	
	if (text) {
		// TTimo: FIXME         
		//    const unsigned char *s = text; // bk001206 - unsigned
		const char *s = text;	// bk001206 - unsigned
		
		//trap_R_SetColor(color);
		colorPtr = color;
		memcpy(&newColor[0], &color[0], sizeof(vec4_t));
		len = strlen(text);
		if (limit > 0 && len > limit) {
			len = limit;
		}
		width = 0;
		count = 0;
		glyph2 = &font->glyphs[(int) cursor];	// bk001206 - possible signed char
		while (s && *s && count < len)
		{
			glyph = &font->glyphs[(int) *s];	// TTimo: FIXME: getting nasty warnings without the cast, hopefully this doesn't break the VM build
			if (Q_IsColorString(s)) {
				//Makro - new tricks
				if (*(s+1) == '*')
				{
					memcpy(newColor, color, sizeof(newColor));
					//trap_R_SetColor(newColor);
					colorPtr = color;
				} else if (*(s+1)== '_')
				{
					underlined ^= qtrue;
				} else /* if (!forceColor) */ {
					memcpy(newColor, g_color_table[ColorIndex(*(s + 1))], sizeof(newColor));
					newColor[3] = color[3];
					//trap_R_SetColor(newColor);
					colorPtr = newColor;
				}
				s += 2;
				continue;
			} else {
				float yadj = useScale * glyph->top;
				if (style == ITEM_TEXTSTYLE_SHADOWED || style == ITEM_TEXTSTYLE_SHADOWEDMORE)
				{
					int ofs = style == ITEM_TEXTSTYLE_SHADOWED ? 1 : 2;
					colorBlack[3] = newColor[3];
					
					Vector2Set(p, x, y);
					Vector2MA(p, ofs, u, p);
					Vector2MA(p, ofs-yadj, v, p);
					
					UI_DrawAngledPic(p[0], p[1],
						glyph->imageWidth * useScale,
						glyph->imageHeight * useScale,
						u,v, colorBlack,
						glyph->s, glyph->t, glyph->s2, glyph->t2, glyph->glyph);
					colorBlack[3] = 1.0;
				}
				Vector2Set(p, x, y);
				Vector2MA(p, -yadj, v, p);
				UI_DrawAngledPic(p[0], p[1],
					glyph->imageWidth * useScale,
					glyph->imageHeight * useScale,
					u,v,colorPtr,
					glyph->s, glyph->t, glyph->s2, glyph->t2, glyph->glyph);
				//Makro - added
				if (underlined)
				{
					UI_DrawAngledPic(x, y, glyph->imageWidth * useScale, uglyph->imageHeight * useScale,
						u, v, colorPtr, uglyph->s, uglyph->t, uglyph->s2, uglyph->t2, uglyph->glyph);
				}
				//Makro - added width
				//width += (glyph->xSkip * useScale) + adjust;
				width += (glyph->xSkip * useScale);
				/*
				if (maxwidth > 0 && width > maxwidth)
					break;
				*/
				//x += ((glyph->xSkip * useScale) + adjust) * u[0];
				//y += ((glyph->xSkip * useScale) + adjust) * u[1];
				if (count == cursorPos && !((uiInfo.uiDC.realTime / BLINK_DIVISOR) & 1)) {
					float adj2 = useScale * (glyph2->top - glyph->top);
					UI_DrawAngledPic(p[0] - adj2 * v[0], p[1] - adj2 * v[1],
						       glyph2->imageWidth * useScale,
						       glyph2->imageHeight * useScale,
						       u, v, colorPtr,
						       glyph2->s, glyph2->t, glyph2->s2, glyph2->t2, glyph2->glyph);
				}
				x += (glyph->xSkip * useScale) * u[0];
				y += (glyph->xSkip * useScale) * u[1];
				s++;
				count++;
			}
		}
		// need to paint cursor at end of text
		if (cursorPos == len && !((uiInfo.uiDC.realTime / BLINK_DIVISOR) & 1)) {
			float yadj = useScale * glyph2->top;
			UI_DrawAngledPic(x - yadj * v[0], y - yadj * v[1],
				       glyph2->imageWidth * useScale,
				       glyph2->imageHeight * useScale,
				       u, v, colorPtr,
				       glyph2->s, glyph2->t, glyph2->s2, glyph2->t2, glyph2->glyph);

		}
	}
}

static void Text_Paint_Limit(float *maxX, float x, float y, float scale, vec4_t color, const char *text, float adjust,
			     int limit)
{
	int len, count;
	vec4_t newColor;
	glyphInfo_t *glyph;

	if (text) {
// TTimo: FIXME
//    const unsigned char *s = text; // bk001206 - unsigned
		const char *s = text;	// bk001206 - unsigned
		float max = *maxX;
		float useScale;
		fontInfo_t *font = &uiInfo.uiDC.Assets.textFont;

		if (scale <= ui_smallFont.value) {
			font = &uiInfo.uiDC.Assets.smallFont;
		} else if (scale > ui_bigFont.value) {
			font = &uiInfo.uiDC.Assets.bigFont;
		}
		useScale = scale * font->glyphScale;
		trap_R_SetColor(color);
		len = strlen(text);
		if (limit > 0 && len > limit) {
			len = limit;
		}
		count = 0;
		while (s && *s && count < len) {
			glyph = &font->glyphs[(int) *s];	// TTimo: FIXME: getting nasty warnings without the cast, hopefully this doesn't break the VM build
			if (Q_IsColorString(s)) {
				memcpy(newColor, g_color_table[ColorIndex(*(s + 1))], sizeof(newColor));
				newColor[3] = color[3];
				trap_R_SetColor(newColor);
				s += 2;
				continue;
			} else {
				float yadj = useScale * glyph->top;

				if (Text_Width(s, useScale, 1) + x > max) {
					*maxX = 0;
					break;
				}
				Text_PaintChar(x, y - yadj,
					       glyph->imageWidth,
					       glyph->imageHeight,
					       useScale, glyph->s, glyph->t, glyph->s2, glyph->t2, glyph->glyph);
				x += (glyph->xSkip * useScale) + adjust;
				*maxX = x;
				count++;
				s++;
			}
		}
		trap_R_SetColor(NULL);
	}

}

void UI_ShowPostGame(qboolean newHigh)
{
	trap_Cvar_Set("cg_cameraOrbit", "0");
	trap_Cvar_Set("cg_thirdPerson", "0");
	trap_Cvar_Set("sv_killserver", "1");
	uiInfo.soundHighScore = newHigh;
	_UI_SetActiveMenu(UIMENU_POSTGAME);
}


//Makro - added
int GMemory();

/*
=================
_UI_Refresh
=================
*/
//Makro - need this variable here; moved from line ~1585 
static qboolean updateModel = qtrue;
qboolean UI_NeedToUpdateModel()
{
	return updateModel;
}

void UI_DrawCenteredPic(qhandle_t image, int w, int h)
{
	int x, y;

	x = (SCREEN_WIDTH - w) / 2;
	y = (SCREEN_HEIGHT - h) / 2;
	UI_DrawHandlePic(x, y, w, h, image);
}

//int frameCount = 0;
//int startTime;

#define	UI_FPS_FRAMES	4
//Makro - mouse fading constants
#define UI_MOUSE_HIDE_TIME		3500
#define UI_MOUSE_FADE_START		3000

void _UI_Refresh(int realtime)
{
	static int index;
	static int previousTimes[UI_FPS_FRAMES];
	//Makro - smoother version
	static int FPSCheckTime = 0, frameCount = 0;
	int modelModCount;
	//Makro - added
	uiClientState_t cstate;
	int lifeTime;

	//if ( !( trap_Key_GetCatcher() & KEYCATCH_UI ) ) {
	//      return;
	//}

	uiInfo.uiDC.pendingPolys = 0;
	uiInfo.uiDC.polyZ = 0;
	uiInfo.uiDC.scene2D.time = realtime;

	uiInfo.uiDC.frameTime = realtime - uiInfo.uiDC.realTime;
	uiInfo.uiDC.realTime = realtime;

	previousTimes[index % UI_FPS_FRAMES] = uiInfo.uiDC.frameTime;
	index++;
	if (index > UI_FPS_FRAMES) {
		int i, total;

		// average multiple frames together to smooth changes out a bit
		total = 0;
		for (i = 0; i < UI_FPS_FRAMES; i++) {
			total += previousTimes[i];
		}
		if (!total) {
			total = 1;
		}
		uiInfo.uiDC.FPS = 1000 * UI_FPS_FRAMES / total;
	}
	frameCount++;
	//Makro - smooth (and inaccurate) version
	if (realtime > FPSCheckTime)
	{
		FPSCheckTime = realtime + 1000;
		uiInfo.uiDC.smoothFPS = frameCount;
		frameCount = 0;
	}

	modelModCount = ui_RQ3_model.modificationCount;
	UI_UpdateCvars();
	if (modelModCount != ui_RQ3_model.modificationCount) {
		int i;
		
		for (i=0;i<uiInfo.q3HeadCount;i++) {
			if (!Q_stricmp(uiInfo.q3HeadNames[i], ui_RQ3_model.string)) {
				UI_FeederSelection(FEEDER_Q3HEADS, i);
				break;
			}
		}
	}

	if (Menu_Count() > 0) {
		// paint all the menus
		Menu_PaintAll();
		// refresh server browser list
		UI_DoServerRefresh();
		// refresh server status
		UI_BuildServerStatus(qfalse);
		// refresh find player list
		UI_BuildFindPlayerList(qfalse);
	}
	//Makro - let's play with the mouse a bit
	if (ui_developer.integer)
	{
		if (uiInfo.uiDC.mouseDown[0] || uiInfo.uiDC.mouseDown[1] || uiInfo.uiDC.mouseDown[2])
		{
			int dif[2];
			float angle, u[2], v[2], norm;
			vec4_t linecolor = {0.8f, 0.8f, 0.8f, 0.75f};

			dif[0] = uiInfo.uiDC.cursorx;
			dif[1] = uiInfo.uiDC.cursory;
			Vector2Subtract(dif, uiInfo.uiDC.mouseDownPos, dif);
			norm = sqrt(Vector2Norm2(dif));
			angle = -RAD2DEG(atan2(dif[1], dif[0]));
			Text_Paint(20, 12, 0.225f, colorCyan, va("(%i, %i) - (%i,%i) = (%i, %i) = %.2f = %.3f deg",
				uiInfo.uiDC.mouseDownPos[0], uiInfo.uiDC.mouseDownPos[1], uiInfo.uiDC.cursorx, uiInfo.uiDC.cursory,
				dif[0], dif[1], norm, angle), 0, 0, 0, ITEM_TEXTSTYLE_SHADOWED, qfalse);
			if (norm)
			{
				Vector2Scale(dif, 1.0f/norm, u);
				//Vector2Set(v, cos(angle), sin(angle));
				Vector2Set(v, -u[1], u[0]);
				UI_DrawAngledPic(uiInfo.uiDC.mouseDownPos[0], uiInfo.uiDC.mouseDownPos[1], norm, 2, u, v, linecolor, 0, 0, norm/16, 1, uiInfo.uiDC.selectShader);
			}
			Text_Paint(uiInfo.uiDC.mouseDownPos[0]-4, uiInfo.uiDC.mouseDownPos[1]+6, 0.4f, colorYellow, "x", 0, 0, 0, ITEM_TEXTSTYLE_SHADOWED, qfalse);
		} else {
			char *s;
			menuDef_t *menu = Menu_GetFocused();
			if (menu)
			{
				s = va("Abs = (%i, %i) Rel = (%.0f, %.0f)", uiInfo.uiDC.cursorx, uiInfo.uiDC.cursory,
					uiInfo.uiDC.cursorx - menu->window.rect.x, uiInfo.uiDC.cursory - menu->window.rect.y);
			} else {
				s = va("(%i, %i)", uiInfo.uiDC.cursorx, uiInfo.uiDC.cursory);
			}
			Text_Paint(20, 12, 0.225f, colorCyan, s, 0, 0, 0, ITEM_TEXTSTYLE_SHADOWED, qfalse);
		}
		Text_Paint(20, 32, 0.225f, colorCyan, va("%i fps", uiInfo.uiDC.smoothFPS), 0, 0, 0,
			ITEM_TEXTSTYLE_SHADOWED, qfalse);
	}
	//any left-overs?
	if (uiInfo.uiDC.pendingPolys)
	{
		UI_Render2DScene();
	}

	// draw cursor
	UI_SetColor(NULL);
	trap_GetClientState(&cstate);
	//Makro - not if it hasn't moved for a while
	lifeTime = uiInfo.uiDC.realTime - uiInfo.uiDC.mouseMoveTime;

	if (Menu_Count() > 0 && (cstate.connState != CA_LOADING) && (lifeTime < UI_MOUSE_HIDE_TIME))
	{
		float ccolor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
		int size = uiInfo.uiDC.cursorSize;
		if (!size)
			size = 32;
		if (uiInfo.uiDC.mouseDown[0] || uiInfo.uiDC.mouseDown[1] || uiInfo.uiDC.mouseDown[2])
		{
			ccolor[0] = 1.00f;
			ccolor[1] = 0.50f;
			ccolor[2] = 0.25f;
		}
		if (lifeTime > UI_MOUSE_FADE_START)
		{
			ccolor[3] = 1.0f - (lifeTime - UI_MOUSE_FADE_START) / (float) (UI_MOUSE_HIDE_TIME - UI_MOUSE_FADE_START);
		}
		UI_SetColor(ccolor);
		UI_DrawHandlePic(uiInfo.uiDC.cursorx - (size>>1), uiInfo.uiDC.cursory - (size>>1), size, size, uiInfo.uiDC.Assets.cursor);
		UI_SetColor(NULL);
	}

	//Makro - draw overlay
	//is it fading ?
	if (IsBetween(realtime, uiInfo.uiDC.overlayFadeStart, uiInfo.uiDC.overlayFadeEnd)) {
		float oColor[4];
		float amt = (float) (realtime - uiInfo.uiDC.overlayFadeStart) / (uiInfo.uiDC.overlayFadeEnd - uiInfo.uiDC.overlayFadeStart);
		LerpColor(uiInfo.uiDC.overlayColor, uiInfo.uiDC.overlayColor2, oColor, amt);
		if (oColor[3] != 0.0f) {
			UI_SetColor(oColor);
			uiInfo.uiDC.drawStretchPic(0, 0, uiInfo.uiDC.glconfig.vidWidth, uiInfo.uiDC.glconfig.vidHeight, 0, 0, 1, 1, uiInfo.uiDC.whiteShader, qfalse);
			UI_SetColor(NULL);
		}
	} else {
		if (uiInfo.uiDC.overlayColor2[3] != 0.0f) {
			UI_SetColor(uiInfo.uiDC.overlayColor2);
			uiInfo.uiDC.drawStretchPic(0, 0, uiInfo.uiDC.glconfig.vidWidth, uiInfo.uiDC.glconfig.vidHeight, 0, 0, 1, 1, uiInfo.uiDC.whiteShader, qfalse);
			UI_SetColor(NULL);
		}
	}

#ifndef NDEBUG
	if (uiInfo.uiDC.debug) {
		// cursor coordinates
		//FIXME
		//UI_DrawString( 0, 0, va("(%d,%d)",uis.cursorx,uis.cursory), UI_LEFT|UI_SMALLFONT, colorRed );
	}
#endif

}

/*
=================
_UI_Shutdown
=================
*/
void _UI_Shutdown(void)
{
	trap_LAN_SaveCachedServers();
}

char *defaultMenu = NULL;

char *GetMenuBuffer(const char *filename)
{
	int len;
	fileHandle_t f;
	static char buf[MAX_MENUFILE];

	len = trap_FS_FOpenFile(filename, &f, FS_READ);
	if (!f) {
		trap_Print(va(S_COLOR_RED "menu file not found: %s, using default\n", filename));
		return defaultMenu;
	}
	if (len >= MAX_MENUFILE) {
		trap_Print(va
			   (S_COLOR_RED "menu file too large: %s is %i, max allowed is %i", filename, len,
			    MAX_MENUFILE));
		trap_FS_FCloseFile(f);
		return defaultMenu;
	}

	trap_FS_Read(buf, len, f);
	buf[len] = 0;
	trap_FS_FCloseFile(f);
	//COM_Compress(buf);
	return buf;

}

qboolean Asset_Parse(int handle)
{
	pc_token_t token;
	const char *tempStr;

	if (!trap_PC_ReadToken(handle, &token))
		return qfalse;
	if (Q_stricmp(token.string, "{") != 0) {
		return qfalse;
	}

	INFINITE_LOOP {

		memset(&token, 0, sizeof(pc_token_t));

		if (!trap_PC_ReadToken(handle, &token))
			return qfalse;

		if (Q_stricmp(token.string, "}") == 0) {
			return qtrue;
		}
		// font
		if (Q_stricmp(token.string, "font") == 0) {
			int pointSize;

			if (!PC_String_Parse(handle, &tempStr) || !PC_Int_Parse(handle, &pointSize)) {
				return qfalse;
			}
			trap_R_RegisterFont(tempStr, pointSize, &uiInfo.uiDC.Assets.textFont);
			uiInfo.uiDC.Assets.fontRegistered = qtrue;
			continue;
		}

		if (Q_stricmp(token.string, "smallFont") == 0) {
			int pointSize;

			if (!PC_String_Parse(handle, &tempStr) || !PC_Int_Parse(handle, &pointSize)) {
				return qfalse;
			}
			trap_R_RegisterFont(tempStr, pointSize, &uiInfo.uiDC.Assets.smallFont);
			continue;
		}

		if (Q_stricmp(token.string, "bigFont") == 0) {
			int pointSize;

			if (!PC_String_Parse(handle, &tempStr) || !PC_Int_Parse(handle, &pointSize)) {
				return qfalse;
			}
			trap_R_RegisterFont(tempStr, pointSize, &uiInfo.uiDC.Assets.bigFont);
			continue;
		}

		// gradientbar
		if (Q_stricmp(token.string, "gradientbar") == 0) {
			if (!PC_String_Parse(handle, &tempStr)) {
				return qfalse;
			}
			uiInfo.uiDC.Assets.gradientBar = trap_R_RegisterShaderNoMip(tempStr);
			continue;
		}
		// enterMenuSound
		if (Q_stricmp(token.string, "menuEnterSound") == 0) {
			if (!PC_String_Parse(handle, &tempStr)) {
				return qfalse;
			}
			uiInfo.uiDC.Assets.menuEnterSound = trap_S_RegisterSound(tempStr, qfalse);
			continue;
		}
		// exitMenuSound
		if (Q_stricmp(token.string, "menuExitSound") == 0) {
			if (!PC_String_Parse(handle, &tempStr)) {
				return qfalse;
			}
			uiInfo.uiDC.Assets.menuExitSound = trap_S_RegisterSound(tempStr, qfalse);
			continue;
		}
		// itemFocusSound
		if (Q_stricmp(token.string, "itemFocusSound") == 0) {
			if (!PC_String_Parse(handle, &tempStr)) {
				return qfalse;
			}
			uiInfo.uiDC.Assets.itemFocusSound = trap_S_RegisterSound(tempStr, qfalse);
			continue;
		}
		// menuBuzzSound
		if (Q_stricmp(token.string, "menuBuzzSound") == 0) {
			if (!PC_String_Parse(handle, &tempStr)) {
				return qfalse;
			}
			uiInfo.uiDC.Assets.menuBuzzSound = trap_S_RegisterSound(tempStr, qfalse);
			continue;
		}

		if (Q_stricmp(token.string, "cursor") == 0) {
			if (!PC_String_Parse(handle, &uiInfo.uiDC.Assets.cursorStr)) {
				return qfalse;
			}
			uiInfo.uiDC.Assets.cursor = trap_R_RegisterShaderNoMip(uiInfo.uiDC.Assets.cursorStr);
			continue;
		}

		//Makro - this allows us to have more than one UI
		if (Q_stricmp(token.string, "assetsPath") == 0) {
			if (!PC_String_Parse(handle, &uiInfo.uiDC.Assets.assetsPath)) {
				return qfalse;
			}
			continue;
		}

		//Makro - key bind status 1
		if (Q_stricmp(token.string, "keyBindStatus1") == 0) {
			if (!PC_String_Parse(handle, &uiInfo.keyBindStatus1)) {
				return qfalse;
			}
			continue;
		}
		
		//Makro - key bind status 2
		if (Q_stricmp(token.string, "keyBindStatus2") == 0) {
			if (!PC_String_Parse(handle, &uiInfo.keyBindStatus2)) {
				return qfalse;
			}
			continue;
		}


		//Makro - added cursor size
		if (Q_stricmp(token.string, "cursorSize") == 0) {
			if (!PC_Int_Parse(handle, &uiInfo.uiDC.cursorSize)) {
				return qfalse;
			}
			continue;
		}

		if (Q_stricmp(token.string, "fadeClamp") == 0) {
			if (!PC_Float_Parse(handle, &uiInfo.uiDC.Assets.fadeClamp)) {
				return qfalse;
			}
			continue;
		}

		if (Q_stricmp(token.string, "fadeCycle") == 0) {
			if (!PC_Int_Parse(handle, &uiInfo.uiDC.Assets.fadeCycle)) {
				return qfalse;
			}
			continue;
		}

		if (Q_stricmp(token.string, "fadeAmount") == 0) {
			if (!PC_Float_Parse(handle, &uiInfo.uiDC.Assets.fadeAmount)) {
				return qfalse;
			}
			continue;
		}

		if (Q_stricmp(token.string, "shadowX") == 0) {
			if (!PC_Float_Parse(handle, &uiInfo.uiDC.Assets.shadowX)) {
				return qfalse;
			}
			continue;
		}

		if (Q_stricmp(token.string, "shadowY") == 0) {
			if (!PC_Float_Parse(handle, &uiInfo.uiDC.Assets.shadowY)) {
				return qfalse;
			}
			continue;
		}

		if (Q_stricmp(token.string, "shadowColor") == 0) {
			if (!PC_Color_Parse(handle, &uiInfo.uiDC.Assets.shadowColor)) {
				return qfalse;
			}
			uiInfo.uiDC.Assets.shadowFadeClamp = uiInfo.uiDC.Assets.shadowColor[3];
			continue;
		}

		//Makro - for grouped checkboxes
		if (Q_stricmp(token.string, "checkBox0") == 0) {
			if (!PC_String_Parse(handle, &tempStr)) {
				return qfalse;
			}
			uiInfo.uiDC.Assets.checkBox0 = trap_R_RegisterShaderNoMip(tempStr);
			continue;
		}
		if (Q_stricmp(token.string, "checkBox1") == 0) {
			if (!PC_String_Parse(handle, &tempStr)) {
				return qfalse;
			}
			uiInfo.uiDC.Assets.checkBox1 = trap_R_RegisterShaderNoMip(tempStr);
			continue;
		}


	}
	//Makro - unreachable
	//return qfalse;
}

void Font_Report()
{
	int i;

	Com_Printf("Font Info\n");
	Com_Printf("=========\n");
	for (i = 32; i < 96; i++) {
		Com_Printf("Glyph handle %i: %i\n", i, uiInfo.uiDC.Assets.textFont.glyphs[i].glyph);
	}
}

void UI_Report()
{
	String_Report();
	//Font_Report();

}

void UI_ParseMenu(const char *menuFile)
{
	int handle;
	pc_token_t token;

	Com_Printf("Parsing menu file:%s\n", menuFile);

	handle = trap_PC_LoadSource(menuFile);
	if (!handle) {
		return;
	}
	
	INFINITE_LOOP {
		memset(&token, 0, sizeof(pc_token_t));
		if (!trap_PC_ReadToken(handle, &token)) {
			break;
		}
		//if ( Q_stricmp( token, "{" ) ) {
		//      Com_Printf( "Missing { in menu file\n" );
		//      break;
		//}

		//if ( menuCount == MAX_MENUS ) {
		//      Com_Printf( "Too many menus!\n" );
		//      break;
		//}

		if (token.string[0] == '}') {
			break;
		}

		if (Q_stricmp(token.string, "assetGlobalDef") == 0) {
			if (Asset_Parse(handle)) {
				continue;
			} else {
				break;
			}
		}

		if (Q_stricmp(token.string, "menudef") == 0) {
			// start a new menu
			Menu_New(handle);
		}
	}
	trap_PC_FreeSource(handle);
}

qboolean Load_Menu(int handle)
{
	pc_token_t token;

	if (!trap_PC_ReadToken(handle, &token))
		return qfalse;
	if (token.string[0] != '{') {
		return qfalse;
	}

	INFINITE_LOOP {

		if (!trap_PC_ReadToken(handle, &token))
			return qfalse;

		if (token.string[0] == 0) {
			return qfalse;
		}

		if (token.string[0] == '}') {
			return qtrue;
		}

		UI_ParseMenu(token.string);
	}
	//Makro - unreachable
	//return qfalse;
}

void UI_LoadMenus(const char *menuFile, qboolean reset)
{
	pc_token_t token;
	int handle;
	int start;

	start = trap_Milliseconds();

	handle = trap_PC_LoadSource(menuFile);
	if (!handle) {
		trap_Error(va(S_COLOR_YELLOW "menu file not found: %s, using default\n", menuFile));
		handle = trap_PC_LoadSource("ui/menus.txt");
		if (!handle) {
			trap_Error(va
				   (S_COLOR_RED "default menu file not found: ui/menus.txt, unable to continue!\n",
				    menuFile));
		}
	}

	ui_new.integer = 1;

	if (reset) {
		Menu_Reset();
	}

	INFINITE_LOOP {
		if (!trap_PC_ReadToken(handle, &token))
			break;
		if (token.string[0] == 0 || token.string[0] == '}') {
			break;
		}

		if (token.string[0] == '}') {
			break;
		}

		if (Q_stricmp(token.string, "loadmenu") == 0) {
			if (Load_Menu(handle)) {
				continue;
			} else {
				break;
			}
		}
	}

	Com_Printf("UI menu load time = %d milli seconds\n", trap_Milliseconds() - start);

	trap_PC_FreeSource(handle);
}

void UI_Load()
{
	char lastName[1024];
	menuDef_t *menu = Menu_GetFocused();
	char *menuSet = UI_Cvar_VariableString("ui_menuFiles");

	if (menu && menu->window.name) {
		strcpy(lastName, menu->window.name);
	}
	if (menuSet == NULL || menuSet[0] == '\0') {
		menuSet = "ui/menus.txt";
	}

	String_Init();

#ifdef PRE_RELEASE_TADEMO
	UI_ParseGameInfo("demogameinfo.txt");
#else
	UI_ParseGameInfo("gameinfo.txt");
	UI_LoadArenas();
#endif

	UI_LoadMenus(menuSet, qtrue);
	Menus_CloseAll();
	Menus_ActivateByName(lastName, qfalse);

}

static const char *handicapValues[] =
    { "None", "95", "90", "85", "80", "75", "70", "65", "60", "55", "50", "45", "40", "35", "30", "25", "20", "15",
"10", "5", NULL };
//Makro - not used anywhere
//#ifndef MISSIONPACK // bk001206
//static int numHandicaps = sizeof(handicapValues) / sizeof(const char*);
//#endif

static void UI_DrawHandicap(rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
	int i, h;

	h = Com_Clamp(5, 100, trap_Cvar_VariableValue("handicap"));
	i = 20 - h / 5;

	Text_Paint(rect->x, rect->y, scale, color, handicapValues[i], 0, 0, 0, textStyle, qfalse);
}

static void UI_DrawClanName(rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
	Text_Paint(rect->x, rect->y, scale, color, UI_Cvar_VariableString("ui_teamName"), 0, 0, 0, textStyle, qfalse);
}

static void UI_SetCapFragLimits(qboolean uiVars)
{
	int cap = 5;
	int frag = 10;

	if (uiInfo.gameTypes[ui_gameType.integer].gtEnum == GT_OBELISK) {
		cap = 4;
	} else if (uiInfo.gameTypes[ui_gameType.integer].gtEnum == GT_HARVESTER) {
		cap = 15;
	}
	if (uiVars) {
		trap_Cvar_Set("ui_captureLimit", va("%d", cap));
		trap_Cvar_Set("ui_fragLimit", va("%d", frag));
	} else {
		trap_Cvar_Set("capturelimit", va("%d", cap));
		trap_Cvar_Set("fraglimit", va("%d", frag));
	}
}

// ui_gameType assumes gametype 0 is -1 ALL and will not show
static void UI_DrawGameType(rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
	Text_Paint(rect->x, rect->y, scale, color, uiInfo.gameTypes[ui_gameType.integer].gameType, 0, 0, 0, textStyle, qfalse);
}

static void UI_DrawNetGameType(rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
	if (ui_netGameType.integer < 0 || ui_netGameType.integer > uiInfo.numGameTypes) {
		trap_Cvar_Set("ui_netGameType", "0");
		trap_Cvar_Set("ui_actualNetGameType", "0");
	}
	if (rect->hasVectors)
		Text_PaintAngled(rect->x, rect->y, rect->u, rect->v, scale, color, uiInfo.gameTypes[ui_netGameType.integer].gameType, 0, 0, 0, textStyle, qfalse);
	else
		Text_Paint(rect->x, rect->y, scale, color, uiInfo.gameTypes[ui_netGameType.integer].gameType, 0, 0, 0, textStyle, qfalse);
}

static void UI_DrawJoinGameType(rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
	if (ui_joinGameType.integer < 0 || ui_joinGameType.integer > uiInfo.numJoinGameTypes) {
		trap_Cvar_Set("ui_joinGameType", "0");
	}
	Text_Paint(rect->x, rect->y, scale, color, uiInfo.joinGameTypes[ui_joinGameType.integer].gameType, 0, 0, 0,
		   textStyle, qfalse);
}

static int UI_TeamIndexFromName(const char *name)
{
	int i;

	if (name && *name) {
		for (i = 0; i < uiInfo.teamCount; i++) {
			if (Q_stricmp(name, uiInfo.teamList[i].teamName) == 0) {
				return i;
			}
		}
	}

	return 0;

}

static void UI_DrawClanLogo(rectDef_t * rect, float scale, vec4_t color)
{
	int i;

	i = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_teamName"));
	if (i >= 0 && i < uiInfo.teamCount) {
		trap_R_SetColor(color);

		if (uiInfo.teamList[i].teamIcon == -1) {
			uiInfo.teamList[i].teamIcon = trap_R_RegisterShaderNoMip(uiInfo.teamList[i].imageName);
			uiInfo.teamList[i].teamIcon_Metal =
			    trap_R_RegisterShaderNoMip(va("%s_metal", uiInfo.teamList[i].imageName));
			uiInfo.teamList[i].teamIcon_Name =
			    trap_R_RegisterShaderNoMip(va("%s_name", uiInfo.teamList[i].imageName));
		}

		UI_DrawHandlePic(rect->x, rect->y, rect->w, rect->h, uiInfo.teamList[i].teamIcon);
		trap_R_SetColor(NULL);
	}
}

static void UI_DrawClanCinematic(rectDef_t * rect, float scale, vec4_t color)
{
	int i;

	i = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_teamName"));
	if (i >= 0 && i < uiInfo.teamCount) {

		if (uiInfo.teamList[i].cinematic >= -2) {
			if (uiInfo.teamList[i].cinematic == -1) {
				uiInfo.teamList[i].cinematic =
				    trap_CIN_PlayCinematic(va("%s.roq", uiInfo.teamList[i].imageName), 0, 0, 0, 0,
							   (CIN_loop | CIN_silent));
			}
			if (uiInfo.teamList[i].cinematic >= 0) {
				trap_CIN_RunCinematic(uiInfo.teamList[i].cinematic);
				trap_CIN_SetExtents(uiInfo.teamList[i].cinematic, rect->x, rect->y, rect->w, rect->h);
				trap_CIN_DrawCinematic(uiInfo.teamList[i].cinematic);
			} else {
				trap_R_SetColor(color);
				UI_DrawHandlePic(rect->x, rect->y, rect->w, rect->h, uiInfo.teamList[i].teamIcon_Metal);
				trap_R_SetColor(NULL);
				uiInfo.teamList[i].cinematic = -2;
			}
		} else {
			trap_R_SetColor(color);
			UI_DrawHandlePic(rect->x, rect->y, rect->w, rect->h, uiInfo.teamList[i].teamIcon);
			trap_R_SetColor(NULL);
		}
	}

}

static void UI_DrawPreviewCinematic(rectDef_t * rect, float scale, vec4_t color)
{
	if (uiInfo.previewMovie > -2) {
		uiInfo.previewMovie =
		    trap_CIN_PlayCinematic(va("%s.roq", uiInfo.movieList[uiInfo.movieIndex]), 0, 0, 0, 0,
					   (CIN_loop | CIN_silent));
		if (uiInfo.previewMovie >= 0) {
			trap_CIN_RunCinematic(uiInfo.previewMovie);
			trap_CIN_SetExtents(uiInfo.previewMovie, rect->x, rect->y, rect->w, rect->h);
			trap_CIN_DrawCinematic(uiInfo.previewMovie);
		} else {
			uiInfo.previewMovie = -2;
		}
	}

}

static void UI_DrawSkill(rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
	int i;

	i = trap_Cvar_VariableValue("g_spSkill");
	if (i < 1 || i > numSkillLevels) {
		i = 1;
	}
	Text_Paint(rect->x, rect->y, scale, color, skillLevels[i - 1], 0, 0, 0, textStyle, qfalse);
}

static void UI_DrawTeamName(rectDef_t * rect, float scale, vec4_t color, qboolean blue, int textStyle)
{
	int i;

	i = UI_TeamIndexFromName(UI_Cvar_VariableString((blue) ? "ui_blueTeam" : "ui_redTeam"));
	if (i >= 0 && i < uiInfo.teamCount) {
		Text_Paint(rect->x, rect->y, scale, color,
			   va("%s: %s", (blue) ? "Blue" : "Red", uiInfo.teamList[i].teamName), 0, 0, 0, textStyle, qfalse);
	}
}

//Makro - added for radio presets
static void UI_RQ3_DrawPreset(rectDef_t * rect, float scale, vec4_t color, int num, int textStyle)
{
	//char *text = "(empty)";
	char *text = "\0";
	if (radioPresets[num-1].Text->string[0]) {
		text = radioPresets[num-1].Text->string;
	}
	Text_Paint(rect->x, rect->y, scale, color, text, 0, 0, 0, textStyle, qfalse);
}

static char team1Name[128], team2Name[128];
//Makro - added for the join menu
static void UI_RQ3_DrawJoinTeam(rectDef_t * rect, float scale, vec4_t color, int num, int textStyle)
{
	//char *text = va("Team %i", num);
	Text_Paint(rect->x, rect->y, scale, color, (num == 1) ? team1Name : team2Name, 0, 0, 0, textStyle, qfalse);
}

static void UI_DrawTeamMember(rectDef_t * rect, float scale, vec4_t color, qboolean blue, int num, int textStyle)
{
	// 0 - None
	// 1 - Human
	// 2..NumCharacters - Bot
	int value = trap_Cvar_VariableValue(va(blue ? "ui_blueteam%i" : "ui_redteam%i", num));
	const char *text;

	if (value <= 0) {
		text = "Closed";
	} else if (value == 1) {
		text = "Human";
		//Makro - support for adding a random bot
	} else if (value == 2) {
		text = "Random";
	} else {
		//Makro - changed from 2
		value -= 3;

//Makro - using bot list instead of character list
/*
		if (ui_actualNetGameType.integer >= GT_TEAM) {
			if (value >= uiInfo.characterCount) {
				value = 0;
			}
			text = uiInfo.characterList[value].name;
		} else {
*/
		if (value >= UI_GetNumBots()) {
			value = 0;
		}
		text = UI_GetBotNameByNumber(value);
		//}
	}
	//Makro - changed
	//Text_Paint(rect->x, rect->y, scale, color, text, 0, 0, textStyle);
	if (ui_actualNetGameType.integer >= GT_TEAM) {
		Text_Paint(rect->x, rect->y, scale, color, va("%i. %s", num, text), 0, 0, 0, textStyle, qfalse);
	} else {
		Text_Paint(rect->x, rect->y, scale, color, va("%i. %s", blue ? (num + 5) : num, text), 0, 0, 0,
			textStyle, qfalse);
	}

}

static void UI_DrawEffects(rectDef_t * rect, float scale, vec4_t color)
{
	UI_DrawHandlePic(rect->x, rect->y - 14, 128, 8, uiInfo.uiDC.Assets.fxBasePic);
	UI_DrawHandlePic(rect->x + uiInfo.effectsColor * 16 + 8, rect->y - 16, 16, 12,
			 uiInfo.uiDC.Assets.fxPic[uiInfo.effectsColor]);
}

static void UI_DrawMapPreview(rectDef_t * rect, float scale, vec4_t color, qboolean net)
{
	int map = (net) ? ui_currentNetMap.integer : ui_currentMap.integer;

	if (uiInfo.mapCount == 0)
		return;

	if (map < 0 || map > uiInfo.mapCount) {
		if (net) {
			ui_currentNetMap.integer = 0;
			trap_Cvar_Set("ui_currentNetMap", "0");
		} else {
			ui_currentMap.integer = 0;
			trap_Cvar_Set("ui_currentMap", "0");
		}
		map = 0;
	}

	if (uiInfo.mapList[map].levelShot == -1) {
		return;
		// Makro - we no longer load the levelshot here because it could lead to a crash...
		//uiInfo.mapList[map].levelShot = trap_R_RegisterShaderNoMip(uiInfo.mapList[map].imageName);
	}

	if (rect->hasVectors) {
		if (uiInfo.mapList[map].levelShot > 0) {
			UI_DrawAngledPic(rect->x, rect->y, rect->w, rect->h, rect->u, rect->v, color, 0.f, 0.f, 1.f, 1.f, uiInfo.mapList[map].levelShot);
		} else {
			UI_DrawAngledPic(rect->x, rect->y, rect->w, rect->h, rect->u, rect->v, color, 0.f, 0.f, 1.f, 1.f, uiInfo.uiDC.Assets.defaultLevelshot);
		}
	} else {
		if (uiInfo.mapList[map].levelShot > 0) {
			UI_DrawHandlePic(rect->x, rect->y, rect->w, rect->h, uiInfo.mapList[map].levelShot);
		} else {
			UI_DrawHandlePic(rect->x, rect->y, rect->w, rect->h, uiInfo.uiDC.Assets.defaultLevelshot);
		}
	}
}

static void UI_DrawMapTimeToBeat(rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
	int minutes, seconds, time;

	if (ui_currentMap.integer < 0 || ui_currentMap.integer > uiInfo.mapCount) {
		ui_currentMap.integer = 0;
		trap_Cvar_Set("ui_currentMap", "0");
	}

	time = uiInfo.mapList[ui_currentMap.integer].timeToBeat[uiInfo.gameTypes[ui_gameType.integer].gtEnum];

	minutes = time / 60;
	seconds = time % 60;

	Text_Paint(rect->x, rect->y, scale, color, va("%02i:%02i", minutes, seconds), 0, 0, 0, textStyle, qfalse);
}

static void UI_DrawMapCinematic(rectDef_t * rect, float scale, vec4_t color, qboolean net)
{
	int map = (net) ? ui_currentNetMap.integer : ui_currentMap.integer;

	if (map < 0 || map > uiInfo.mapCount) {
		if (net) {
			ui_currentNetMap.integer = 0;
			trap_Cvar_Set("ui_currentNetMap", "0");
		} else {
			ui_currentMap.integer = 0;
			trap_Cvar_Set("ui_currentMap", "0");
		}
		map = 0;
	}

	if (uiInfo.mapList[map].cinematic >= -1) {
		if (uiInfo.mapList[map].cinematic == -1) {
			uiInfo.mapList[map].cinematic =
			    trap_CIN_PlayCinematic(va("%s.roq", uiInfo.mapList[map].mapLoadName), 0, 0, 0, 0,
						   (CIN_loop | CIN_silent));
		}
		if (uiInfo.mapList[map].cinematic >= 0) {
			trap_CIN_RunCinematic(uiInfo.mapList[map].cinematic);
			trap_CIN_SetExtents(uiInfo.mapList[map].cinematic, rect->x, rect->y, rect->w, rect->h);
			trap_CIN_DrawCinematic(uiInfo.mapList[map].cinematic);
		} else {
			uiInfo.mapList[map].cinematic = -2;
		}
	} else {
		UI_DrawMapPreview(rect, scale, color, net);
	}
}

//Makro - need to use this variable around line 870; moved above
//static qboolean updateModel = qtrue;
static qboolean q3Model = qfalse;
static animNumber_t RQ3_UI_legsAnim = LEGS_IDLE;
static animNumber_t RQ3_UI_torsoAnim = TORSO_STAND;
static weapon_t RQ3_UI_weapon = WP_PISTOL;

//Makro - use different animations for the player model depending on ui_RQ3_modelCommand

animNumber_t UI_RQ3_GetAnimForLegs()
{
	int cmd = (int) trap_Cvar_VariableValue("ui_RQ3_modelCommand");

	switch (cmd) {
	case 1:
		return LEGS_IDLE;
		break;
	case 2:
		return LEGS_BACK;
		break;
	case 3:
		return LEGS_RUN;
		break;
	case 4:
		return LEGS_WALK;
		break;
	case 5:
		return LEGS_JUMP;
		break;
	case 6:
		return LEGS_IDLECR;
		break;
	case 7:
		return LEGS_WALKCR;
		break;
	default:
		return RQ3_UI_legsAnim;
		break;
	}
}

//Makro - use different animations for the player model depending on ui_RQ3_modelCommand

animNumber_t UI_RQ3_GetAnimForTorso()
{
	int cmd = (int) trap_Cvar_VariableValue("ui_RQ3_modelCommand");

	switch (cmd) {
	case 8:
		return TORSO_GESTURE;
		break;
	default:
		return RQ3_UI_torsoAnim;
		break;
	}
}

//Makro - use different weapons for the player model depending on ui_RQ3_model_command

weapon_t UI_RQ3_GetWeaponForPlayer()
{
	int cmd = (int) trap_Cvar_VariableValue("ui_RQ3_modelCommand");

	switch (cmd) {
	case 101:
		return WP_PISTOL;
		break;
	case 102:
		return WP_M3;
		break;
	case 103:
		return WP_MP5;
		break;
	case 104:
		return WP_HANDCANNON;
		break;
	case 105:
		return WP_SSG3000;
		break;
	case 106:
		return WP_M4;
		break;
	case 107:
		return WP_AKIMBO;
		break;
	case 108:
		return WP_KNIFE;
		break;
	case 109:
		return WP_GRENADE;
		break;
	default:
		return RQ3_UI_weapon;
		break;
	}
}

static void UI_DrawPlayerModel(rectDef_t * rect)
{
	static playerInfo_t info;
	char model[MAX_QPATH];
	char team[256];
	char head[256];
	vec3_t viewangles;
	vec3_t moveangles;

	if (trap_Cvar_VariableValue("ui_Q3Model")) {
		strcpy(model, UI_Cvar_VariableString("model"));
		strcpy(head, UI_Cvar_VariableString("headmodel"));
		if (!q3Model) {
			q3Model = qtrue;
			updateModel = qtrue;
		}
		team[0] = '\0';
	} else {

		strcpy(team, UI_Cvar_VariableString("ui_teamName"));
		strcpy(model, UI_Cvar_VariableString("model"));
		strcpy(head, UI_Cvar_VariableString("headmodel"));
		if (q3Model) {
			q3Model = qfalse;
			updateModel = qtrue;
		}
	}

	//updateModel = updateModel || (trap_Cvar_VariableValue("ui_RQ3_modelCommand") != 0);
	if (updateModel || (trap_Cvar_VariableValue("ui_RQ3_modelCommand") != 0)) {
		if (updateModel) {
			memset(&info, 0, sizeof(playerInfo_t));
		}
		viewangles[YAW] = 180 + 40;
		viewangles[PITCH] = 0;
		viewangles[ROLL] = 0;
		VectorClear(moveangles);
		if (updateModel) {
			UI_PlayerInfo_SetModel(&info, model, head, team);
		}
		//Blaze: Changed WP_MACHINEGUN to WP_PISTOL
		//Makro: Changed from WP_PISTOL to custom function
		RQ3_UI_legsAnim = UI_RQ3_GetAnimForLegs();
		RQ3_UI_torsoAnim = UI_RQ3_GetAnimForTorso();
		RQ3_UI_weapon = UI_RQ3_GetWeaponForPlayer();
		UI_PlayerInfo_SetInfo(&info, RQ3_UI_legsAnim, RQ3_UI_torsoAnim, viewangles, vec3_origin, RQ3_UI_weapon,
				      qfalse);
//              UI_RegisterClientModelname( &info, model, head, team);
		updateModel = qfalse;
		trap_Cvar_SetValue("ui_RQ3_modelCommand", 0);
	}

	UI_DrawPlayer(rect->x, rect->y, rect->w, rect->h, &info, uiInfo.uiDC.realTime / 2);

}

static void UI_DrawNetSource(rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
	const char* msg = netSources[ui_netSource.integer];
	if (ui_netSource.integer < 0 || ui_netSource.integer > numNetSources) {
		ui_netSource.integer = 0;
	}
	if (rect->hasVectors)
		Text_PaintAngled(rect->x, rect->y, rect->u, rect->v, scale, color, msg, 0, 0, 0,
			textStyle, qfalse);
	else
		Text_Paint(rect->x, rect->y, scale, color, msg, 0, 0, 0,
			textStyle, qfalse);
}

static void UI_DrawNetMapPreview(rectDef_t * rect, float scale, vec4_t color)
{

	if (uiInfo.serverStatus.currentServerPreview > 0) {
		UI_DrawHandlePic(rect->x, rect->y, rect->w, rect->h, uiInfo.serverStatus.currentServerPreview);
	} else {
		UI_DrawHandlePic(rect->x, rect->y, rect->w, rect->h, trap_R_RegisterShaderNoMip("menu/art/unknownmap"));
	}
}

static void UI_DrawNetMapCinematic(rectDef_t * rect, float scale, vec4_t color)
{
	if (ui_currentNetMap.integer < 0 || ui_currentNetMap.integer > uiInfo.mapCount) {
		ui_currentNetMap.integer = 0;
		trap_Cvar_Set("ui_currentNetMap", "0");
	}

	if (uiInfo.serverStatus.currentServerCinematic >= 0) {
		trap_CIN_RunCinematic(uiInfo.serverStatus.currentServerCinematic);
		trap_CIN_SetExtents(uiInfo.serverStatus.currentServerCinematic, rect->x, rect->y, rect->w, rect->h);
		trap_CIN_DrawCinematic(uiInfo.serverStatus.currentServerCinematic);
	} else {
		UI_DrawNetMapPreview(rect, scale, color);
	}
}

static void UI_DrawNetFilter(rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
	if (ui_serverFilterType.integer < 0 || ui_serverFilterType.integer > numServerFilters) {
		ui_serverFilterType.integer = 0;
	}
	Text_Paint(rect->x, rect->y, scale, color,
		   va("Filter: %s", serverFilters[ui_serverFilterType.integer].description), 0, 0, 0,
		   textStyle, qfalse);
}

static void UI_DrawTier(rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
	int i;

	i = trap_Cvar_VariableValue("ui_currentTier");
	if (i < 0 || i >= uiInfo.tierCount) {
		i = 0;
	}
	Text_Paint(rect->x, rect->y, scale, color, va("Tier: %s", uiInfo.tierList[i].tierName), 0, 0, 0,
		textStyle, qfalse);
}

static void UI_DrawTierMap(rectDef_t * rect, int index)
{
	int i;

	i = trap_Cvar_VariableValue("ui_currentTier");
	if (i < 0 || i >= uiInfo.tierCount) {
		i = 0;
	}

	if (uiInfo.tierList[i].mapHandles[index] == -1) {
		uiInfo.tierList[i].mapHandles[index] =
		    trap_R_RegisterShaderNoMip(va("levelshots/%s", uiInfo.tierList[i].maps[index]));
	}

	UI_DrawHandlePic(rect->x, rect->y, rect->w, rect->h, uiInfo.tierList[i].mapHandles[index]);
}

static const char *UI_EnglishMapName(const char *map)
{
	int i;

	for (i = 0; i < uiInfo.mapCount; i++) {
		if (Q_stricmp(map, uiInfo.mapList[i].mapLoadName) == 0) {
			return uiInfo.mapList[i].mapName;
		}
	}
	return "";
}

static void UI_DrawTierMapName(rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
	int i, j;

	i = trap_Cvar_VariableValue("ui_currentTier");
	if (i < 0 || i >= uiInfo.tierCount) {
		i = 0;
	}
	j = trap_Cvar_VariableValue("ui_currentMap");
	if (j < 0 || j > MAPS_PER_TIER) {
		j = 0;
	}

	Text_Paint(rect->x, rect->y, scale, color, UI_EnglishMapName(uiInfo.tierList[i].maps[j]),
		0, 0, 0, textStyle, qfalse);
}

static void UI_DrawTierGameType(rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
	int i, j;

	i = trap_Cvar_VariableValue("ui_currentTier");
	if (i < 0 || i >= uiInfo.tierCount) {
		i = 0;
	}
	j = trap_Cvar_VariableValue("ui_currentMap");
	if (j < 0 || j > MAPS_PER_TIER) {
		j = 0;
	}

	Text_Paint(rect->x, rect->y, scale, color, uiInfo.gameTypes[uiInfo.tierList[i].gameTypes[j]].gameType,
		0, 0, 0, textStyle, qfalse);
}

//Makro - not used anywhere
/*
#ifndef MISSIONPACK // bk001206
static const char *UI_OpponentLeaderName() {
  int i = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_opponentName"));
	return uiInfo.teamList[i].teamMembers[0];
}
#endif
*/

static const char *UI_AIFromName(const char *name)
{
	int j;

	for (j = 0; j < uiInfo.aliasCount; j++) {
		if (Q_stricmp(uiInfo.aliasList[j].name, name) == 0) {
			return uiInfo.aliasList[j].ai;
		}
	}
	return "James";
}

//Makro - not used anywhere
/*
#ifndef MISSIONPACK // bk001206
static const int UI_AIIndex(const char *name) {
	int j;
	for (j = 0; j < uiInfo.characterCount; j++) {
		if (Q_stricmp(name, uiInfo.characterList[j].name) == 0) {
			return j;
		}
	}
	return 0;
}
#endif

#ifndef MISSIONPACK // bk001206
static const int UI_AIIndexFromName(const char *name) {
	int j;
	for (j = 0; j < uiInfo.aliasCount; j++) {
		if (Q_stricmp(uiInfo.aliasList[j].name, name) == 0) {
			return UI_AIIndex(uiInfo.aliasList[j].ai);
		}
	}
	return 0;
}
#endif

#ifndef MISSIONPACK // bk001206
static const char *UI_OpponentLeaderHead() {
	const char *leader = UI_OpponentLeaderName();
	return UI_AIFromName(leader);
}
#endif

#ifndef MISSIONPACK // bk001206
static const char *UI_OpponentLeaderModel() {
	int i;
	const char *head = UI_OpponentLeaderHead();
	for (i = 0; i < uiInfo.characterCount; i++) {
		if (Q_stricmp(head, uiInfo.characterList[i].name) == 0) {
			return uiInfo.characterList[i].base;
		}
	}
	return "James";
}
#endif
*/

static qboolean updateOpponentModel = qtrue;
static void UI_DrawOpponent(rectDef_t * rect)
{
	static playerInfo_t info2;
	char model[MAX_QPATH];
	char headmodel[MAX_QPATH];
	char team[256];
	vec3_t viewangles;
	vec3_t moveangles;

	updateOpponentModel = updateOpponentModel || trap_Cvar_VariableValue("ui_RQ3_modelCommand") != 0;
	if (updateOpponentModel) {

		strcpy(model, UI_Cvar_VariableString("ui_opponentModel"));
		strcpy(headmodel, UI_Cvar_VariableString("ui_opponentModel"));
		team[0] = '\0';

		memset(&info2, 0, sizeof(playerInfo_t));
		viewangles[YAW] = 180 - 10;
		viewangles[PITCH] = 0;
		viewangles[ROLL] = 0;
		VectorClear(moveangles);
		UI_PlayerInfo_SetModel(&info2, model, headmodel, "");
		//Makro - changed to custom function
		//FIXME - copy code from player model drawing function
		UI_PlayerInfo_SetInfo(&info2, UI_RQ3_GetAnimForLegs(), UI_RQ3_GetAnimForTorso(), viewangles,
				      vec3_origin, UI_RQ3_GetWeaponForPlayer(), qfalse);
		UI_RegisterClientModelname(&info2, model, headmodel, team);
		updateOpponentModel = qfalse;
		trap_Cvar_SetValue("ui_RQ3_modelCommand", 0);
	}

	UI_DrawPlayer(rect->x, rect->y, rect->w, rect->h, &info2, uiInfo.uiDC.realTime / 2);

}

static void UI_NextOpponent()
{
	int i = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_opponentName"));
	int j = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_teamName"));

	i++;
	if (i >= uiInfo.teamCount) {
		i = 0;
	}
	if (i == j) {
		i++;
		if (i >= uiInfo.teamCount) {
			i = 0;
		}
	}
	trap_Cvar_Set("ui_opponentName", uiInfo.teamList[i].teamName);
}

static void UI_PriorOpponent()
{
	int i = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_opponentName"));
	int j = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_teamName"));

	i--;
	if (i < 0) {
		i = uiInfo.teamCount - 1;
	}
	if (i == j) {
		i--;
		if (i < 0) {
			i = uiInfo.teamCount - 1;
		}
	}
	trap_Cvar_Set("ui_opponentName", uiInfo.teamList[i].teamName);
}

static void UI_DrawPlayerLogo(rectDef_t * rect, vec3_t color)
{
	int i = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_teamName"));

	if (uiInfo.teamList[i].teamIcon == -1) {
		uiInfo.teamList[i].teamIcon = trap_R_RegisterShaderNoMip(uiInfo.teamList[i].imageName);
		uiInfo.teamList[i].teamIcon_Metal =
		    trap_R_RegisterShaderNoMip(va("%s_metal", uiInfo.teamList[i].imageName));
		uiInfo.teamList[i].teamIcon_Name =
		    trap_R_RegisterShaderNoMip(va("%s_name", uiInfo.teamList[i].imageName));
	}

	trap_R_SetColor(color);
	UI_DrawHandlePic(rect->x, rect->y, rect->w, rect->h, uiInfo.teamList[i].teamIcon);
	trap_R_SetColor(NULL);
}

static void UI_DrawPlayerLogoMetal(rectDef_t * rect, vec3_t color)
{
	int i = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_teamName"));

	if (uiInfo.teamList[i].teamIcon == -1) {
		uiInfo.teamList[i].teamIcon = trap_R_RegisterShaderNoMip(uiInfo.teamList[i].imageName);
		uiInfo.teamList[i].teamIcon_Metal =
		    trap_R_RegisterShaderNoMip(va("%s_metal", uiInfo.teamList[i].imageName));
		uiInfo.teamList[i].teamIcon_Name =
		    trap_R_RegisterShaderNoMip(va("%s_name", uiInfo.teamList[i].imageName));
	}

	trap_R_SetColor(color);
	UI_DrawHandlePic(rect->x, rect->y, rect->w, rect->h, uiInfo.teamList[i].teamIcon_Metal);
	trap_R_SetColor(NULL);
}

static void UI_DrawPlayerLogoName(rectDef_t * rect, vec3_t color)
{
	int i = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_teamName"));

	if (uiInfo.teamList[i].teamIcon == -1) {
		uiInfo.teamList[i].teamIcon = trap_R_RegisterShaderNoMip(uiInfo.teamList[i].imageName);
		uiInfo.teamList[i].teamIcon_Metal =
		    trap_R_RegisterShaderNoMip(va("%s_metal", uiInfo.teamList[i].imageName));
		uiInfo.teamList[i].teamIcon_Name =
		    trap_R_RegisterShaderNoMip(va("%s_name", uiInfo.teamList[i].imageName));
	}

	trap_R_SetColor(color);
	UI_DrawHandlePic(rect->x, rect->y, rect->w, rect->h, uiInfo.teamList[i].teamIcon_Name);
	trap_R_SetColor(NULL);
}

static void UI_DrawOpponentLogo(rectDef_t * rect, vec3_t color)
{
	int i = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_opponentName"));

	if (uiInfo.teamList[i].teamIcon == -1) {
		uiInfo.teamList[i].teamIcon = trap_R_RegisterShaderNoMip(uiInfo.teamList[i].imageName);
		uiInfo.teamList[i].teamIcon_Metal =
		    trap_R_RegisterShaderNoMip(va("%s_metal", uiInfo.teamList[i].imageName));
		uiInfo.teamList[i].teamIcon_Name =
		    trap_R_RegisterShaderNoMip(va("%s_name", uiInfo.teamList[i].imageName));
	}

	trap_R_SetColor(color);
	UI_DrawHandlePic(rect->x, rect->y, rect->w, rect->h, uiInfo.teamList[i].teamIcon);
	trap_R_SetColor(NULL);
}

static void UI_DrawOpponentLogoMetal(rectDef_t * rect, vec3_t color)
{
	int i = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_opponentName"));

	if (uiInfo.teamList[i].teamIcon == -1) {
		uiInfo.teamList[i].teamIcon = trap_R_RegisterShaderNoMip(uiInfo.teamList[i].imageName);
		uiInfo.teamList[i].teamIcon_Metal =
		    trap_R_RegisterShaderNoMip(va("%s_metal", uiInfo.teamList[i].imageName));
		uiInfo.teamList[i].teamIcon_Name =
		    trap_R_RegisterShaderNoMip(va("%s_name", uiInfo.teamList[i].imageName));
	}

	trap_R_SetColor(color);
	UI_DrawHandlePic(rect->x, rect->y, rect->w, rect->h, uiInfo.teamList[i].teamIcon_Metal);
	trap_R_SetColor(NULL);
}

static void UI_DrawOpponentLogoName(rectDef_t * rect, vec3_t color)
{
	int i = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_opponentName"));

	if (uiInfo.teamList[i].teamIcon == -1) {
		uiInfo.teamList[i].teamIcon = trap_R_RegisterShaderNoMip(uiInfo.teamList[i].imageName);
		uiInfo.teamList[i].teamIcon_Metal =
		    trap_R_RegisterShaderNoMip(va("%s_metal", uiInfo.teamList[i].imageName));
		uiInfo.teamList[i].teamIcon_Name =
		    trap_R_RegisterShaderNoMip(va("%s_name", uiInfo.teamList[i].imageName));
	}

	trap_R_SetColor(color);
	UI_DrawHandlePic(rect->x, rect->y, rect->w, rect->h, uiInfo.teamList[i].teamIcon_Name);
	trap_R_SetColor(NULL);
}

static void UI_DrawAllMapsSelection(rectDef_t * rect, float scale, vec4_t color, int textStyle, qboolean net)
{
	int map = (net) ? ui_currentNetMap.integer : ui_currentMap.integer;

	if (map >= 0 && map < uiInfo.mapCount) {
		Text_Paint(rect->x, rect->y, scale, color, uiInfo.mapList[map].mapName, 0, 0, 0, textStyle, qfalse);
	}
}

static void UI_DrawOpponentName(rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
	Text_Paint(rect->x, rect->y, scale, color, UI_Cvar_VariableString("ui_opponentName"), 0, 0, 0,
		textStyle, qfalse);
}

static int UI_OwnerDrawWidth(int ownerDraw, float scale)
{
	int i, h, value;
	const char *text;
	const char *s = NULL;

	switch (ownerDraw) {
	case UI_HANDICAP:
		h = Com_Clamp(5, 100, trap_Cvar_VariableValue("handicap"));
		i = 20 - h / 5;
		s = handicapValues[i];
		break;
	case UI_CLANNAME:
		s = UI_Cvar_VariableString("ui_teamName");
		break;
	case UI_GAMETYPE:
		s = uiInfo.gameTypes[ui_gameType.integer].gameType;
		break;
	case UI_SKILL:
		i = trap_Cvar_VariableValue("g_spSkill");
		if (i < 1 || i > numSkillLevels) {
			i = 1;
		}
		s = skillLevels[i - 1];
		break;
	case UI_BLUETEAMNAME:
		i = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_blueTeam"));
		if (i >= 0 && i < uiInfo.teamCount) {
			s = va("%s: %s", "Blue", uiInfo.teamList[i].teamName);
		}
		break;
	case UI_REDTEAMNAME:
		i = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_redTeam"));
		if (i >= 0 && i < uiInfo.teamCount) {
			s = va("%s: %s", "Red", uiInfo.teamList[i].teamName);
		}
		break;
	case UI_BLUETEAM1:
	case UI_BLUETEAM2:
	case UI_BLUETEAM3:
	case UI_BLUETEAM4:
	case UI_BLUETEAM5:
		value = trap_Cvar_VariableValue(va("ui_blueteam%i", ownerDraw - UI_BLUETEAM1 + 1));
		if (value <= 0) {
			text = "Closed";
		} else if (value == 1) {
			text = "Human";
		} else {
			value -= 2;
			if (value >= uiInfo.aliasCount) {
				value = 0;
			}
			text = uiInfo.aliasList[value].name;
		}
		//Makro - changed
		//s = va("%i. %s", ownerDraw-UI_BLUETEAM1 + 1, text);
		if (ui_actualNetGameType.integer >= GT_TEAM) {
			s = va("%i. %s", ownerDraw - UI_BLUETEAM1 + 1, text);
		} else {
			s = va("%i. %s", ownerDraw - UI_BLUETEAM1 + 6, text);
		}
		break;
	case UI_REDTEAM1:
	case UI_REDTEAM2:
	case UI_REDTEAM3:
	case UI_REDTEAM4:
	case UI_REDTEAM5:
		value = trap_Cvar_VariableValue(va("ui_redteam%i", ownerDraw - UI_REDTEAM1 + 1));
		if (value <= 0) {
			text = "Closed";
		} else if (value == 1) {
			text = "Human";
		} else {
			value -= 2;
			if (value >= uiInfo.aliasCount) {
				value = 0;
			}
			text = uiInfo.aliasList[value].name;
		}
		s = va("%i. %s", ownerDraw - UI_REDTEAM1 + 1, text);
		break;
	case UI_NETSOURCE:
		if (ui_netSource.integer < 0 || ui_netSource.integer > uiInfo.numJoinGameTypes) {
			ui_netSource.integer = 0;
		}

		s = va("Source: %s", netSources[ui_netSource.integer]);
		break;
	case UI_NETFILTER:
		if (ui_serverFilterType.integer < 0 || ui_serverFilterType.integer > numServerFilters) {
			ui_serverFilterType.integer = 0;
		}
		s = va("Filter: %s", serverFilters[ui_serverFilterType.integer].description);
		break;
	case UI_TIER:
		break;
	case UI_TIER_MAPNAME:
		break;
	case UI_TIER_GAMETYPE:
		break;
	case UI_ALLMAPS_SELECTION:
		break;
	case UI_OPPONENT_NAME:
		break;
	case UI_KEYBINDSTATUS:
		if (Display_KeyBindPending()) {
			s = uiInfo.keyBindStatus2;
		} else {
			s = uiInfo.keyBindStatus1;
		}
		break;
	case UI_SERVERREFRESHDATE:
		s = UI_Cvar_VariableString(va("ui_lastServerRefresh_%i", ui_netSource.integer));
		break;
	//Makro - replacement model name
	case UI_RQ3_REPLACEMENTNAME:
		s = uiInfo.replacements.Name;
		break;
	//Makro - replacement model info
	case UI_RQ3_REPLACEMENTINFO:
		s = uiInfo.replacements.Info;
		break;
	default:
		break;
	}

	if (s) {
		return Text_Width(s, scale, 0);
	}
	return 0;
}

static void UI_DrawBotName(rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
	int value = uiInfo.botIndex;

	//int game = trap_Cvar_VariableValue("g_gametype");
	const char *text = "";

//Makro - using bot list instead of character list
/*
	if (game >= GT_TEAM) {
		if (value >= uiInfo.characterCount) {
			value = 0;
		}
		text = uiInfo.characterList[value].name;
	} else {
*/
	if (value >= UI_GetNumBots()) {
		value = 0;
	}
	text = UI_GetBotNameByNumber(value);
//      }
	Text_Paint(rect->x, rect->y, scale, color, text, 0, 0, 0, textStyle, qfalse);
}

static void UI_DrawBotSkill(rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
	if (uiInfo.skillIndex >= 0 && uiInfo.skillIndex < numSkillLevels) {
		Text_Paint(rect->x, rect->y, scale, color, skillLevels[uiInfo.skillIndex], 0, 0, 0, textStyle, qfalse);
	}
}

static void UI_DrawRedBlue(rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
	//Makro - added Team 1/2
	Text_Paint(rect->x, rect->y, scale, color, (uiInfo.redBlue == 0) ? "1 (Red)" : "2 (Blue)", 0, 0, 0, textStyle, qfalse);
}

static void UI_DrawCrosshair(rectDef_t * rect, float scale)
{
	vec4_t color;
	float size;

	color[0] = trap_Cvar_VariableValue("cg_RQ3_crosshairColorR");
	color[1] = trap_Cvar_VariableValue("cg_RQ3_crosshairColorG");
	color[2] = trap_Cvar_VariableValue("cg_RQ3_crosshairColorB");
	color[3] = trap_Cvar_VariableValue("cg_RQ3_crosshairColorA");

	size = trap_Cvar_VariableValue("cg_crosshairSize");

	trap_R_SetColor(color);

	if (uiInfo.currentCrosshair < 0 || uiInfo.currentCrosshair >= NUM_CROSSHAIRS) {
		uiInfo.currentCrosshair = 0;
	}
	//Makro - fixing bug that draws a crosshair even if cg_drawcrosshair is 0
	if (uiInfo.currentCrosshair != 0)
	{
		if (rect->hasVectors)
		{
			float pt[2];
			float mx, my;

			vec4_t black = { 0, 0, 0, 1};
			
			pt[0] = rect->x;
			pt[1] = rect->y;


			UI_DrawAngledPic(pt[0], pt[1], rect->w, rect->h, rect->u, rect->v, black,
				0.f, 0.f, 1.f, 1.f, /*uiInfo.uiDC.Assets.crosshairShader[uiInfo.currentCrosshair]*/ uiInfo.uiDC.whiteShader);

			mx = (rect->w - size) * 0.5f;
			my = (rect->h - size) * 0.5f;

			Vector2MA(pt, mx, rect->u, pt);
			Vector2MA(pt, my, rect->v, pt);

			UI_DrawAngledPic(pt[0], pt[1], size, size, rect->u, rect->v, color,
				0.f, 0.f, 1.f, 1.f, /*uiInfo.uiDC.Assets.crosshairShader[uiInfo.currentCrosshair]*/ uiInfo.uiDC.whiteShader);
		}
		else
			UI_DrawHandlePic(rect->x + (rect->w - size) * 0.5f, rect->y + (rect->h - size) * 0.5f, size, size,
					 uiInfo.uiDC.Assets.crosshairShader[uiInfo.currentCrosshair]);
	}
	trap_R_SetColor(NULL);
}

//Makro - digital clock
static void UI_DrawClock(itemDef_t *item, rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
	int time = uiInfo.uiDC.realTime;
	char *text;
	qtime_t qt;


	trap_RealTime(&qt);
	text = va("%02i:%02i", qt.tm_hour, qt.tm_min);

	if (!item->window.rectClient.hasVectors) {
		Text_Paint(rect->x, rect->y, scale, color, text, 0, 0, 0, textStyle, qfalse);
	} else {
		Text_PaintAngled(rect->x, rect->y,
			item->window.rectClient.u, item->window.rectClient.v, scale, color, text, 0, 0, 0, textStyle, qfalse);
	}
}

//Makro - for the SSG crosshair preview
static void UI_DrawSSGCrosshair(rectDef_t * rect)
{
	vec4_t color;

	color[0] = trap_Cvar_VariableValue("cg_RQ3_ssgColorR");
	color[1] = trap_Cvar_VariableValue("cg_RQ3_ssgColorG");
	color[2] = trap_Cvar_VariableValue("cg_RQ3_ssgColorB");
	color[3] = trap_Cvar_VariableValue("cg_RQ3_ssgColorA");
	trap_R_SetColor(color);

	UI_DrawHandlePic(rect->x, rect->y, rect->w, rect->h, uiInfo.uiDC.Assets.SSGcrosshairShader);
	trap_R_SetColor(NULL);
}

/*
===============
UI_BuildIngameServerInfoList
Added by Makro
===============
*/
char *GetFirstWord(char **line)
{
	char *word;

	if (!*line || !**line) {
		return "";
	} else {
		char *s = strchr(*line, '\\');
		if (!s) {
			word = *line;
			*line = 0;
		} else {
			*s = '\0';
			word = *line;
			*line = s + 1;
		}
		return word;
	}
}

void AddIngameLine(char *key, char *val)
{
	if (uiInfo.ingameServerInfoLineCount >= MAX_SERVERSTATUS_LINES) {
		return;
	} else {
		Q_strncpyz(uiInfo.ingameServerInfo[uiInfo.ingameServerInfoLineCount][0], key, sizeof(uiInfo.ingameServerInfo[uiInfo.ingameServerInfoLineCount][0]));
		Q_strncpyz(uiInfo.ingameServerInfo[uiInfo.ingameServerInfoLineCount][1], val, sizeof(uiInfo.ingameServerInfo[uiInfo.ingameServerInfoLineCount][1]));
		uiInfo.ingameServerInfoLineCount++;
	}
}

void UI_BuildIngameServerInfoList()
{
	char serverInfo[MAX_INFO_STRING], systemInfo[MAX_INFO_STRING];
	char *p, *key, *val;

	memset(uiInfo.ingameServerInfo, 0, sizeof(uiInfo.ingameServerInfo));
	uiInfo.ingameServerInfoLineCount = 0;

	trap_GetConfigString(CS_SERVERINFO, serverInfo, sizeof(serverInfo));
	trap_GetConfigString(CS_SYSTEMINFO, systemInfo, sizeof(systemInfo));
	//detailed info
	if (trap_Cvar_VariableValue("ui_RQ3_ingameDetails")) {	
		p = serverInfo;
		while (*p == '\\')
			p++;
		// get the cvars
		while (p && *p) {
			key = GetFirstWord(&p);
			val = GetFirstWord(&p);
			//Q_strncpyz(uiInfo.ingameServerInfo[uiInfo.ingameServerInfoLineCount][0], key, sizeof(uiInfo.ingameServerInfo[uiInfo.ingameServerInfoLineCount][0]));
			//Q_strncpyz(uiInfo.ingameServerInfo[uiInfo.ingameServerInfoLineCount][1], val, sizeof(uiInfo.ingameServerInfo[uiInfo.ingameServerInfoLineCount][1]));
			//uiInfo.ingameServerInfoLineCount++;
			AddIngameLine(key, val);
			if (!key && !val)
				break;
			if (!*key && !*val)
				break;
			if (uiInfo.ingameServerInfoLineCount >= MAX_SERVERSTATUS_LINES)
				break;
		}
	//basic info
	} else {
		//to avoid reading some stuff more than once
		int gametype = atoi(Info_ValueForKey(serverInfo, "g_gametype"));
		int matchmode = atoi(Info_ValueForKey(serverInfo, "g_RQ3_matchmode"));
		int limit = atoi(Info_ValueForKey(serverInfo, "timelimit"));
		
		AddIngameLine("RQ3 Version", Info_ValueForKey(serverInfo, "g_RQ3_version"));
		AddIngameLine("Host name", Info_ValueForKey(serverInfo, "sv_hostname"));
		AddIngameLine("Map name", Info_ValueForKey(serverInfo, "mapname"));
		AddIngameLine("Gametype", (char*)teamArenaGameNames[gametype]);
		AddIngameLine("Time limit", (limit !=0 ) ? va("%i", limit) : "None");
		switch (gametype) {
			case GT_TEAMPLAY:
				{
					limit = atoi(Info_ValueForKey(serverInfo, "g_RQ3_roundlimit"));
					AddIngameLine("Round limit", (limit !=0 ) ? va("%i", limit) : "None");
					limit = atoi(Info_ValueForKey(serverInfo, "g_RQ3_roundtimelimit"));
					AddIngameLine("Round time limit", (limit !=0 ) ? va("%i", limit) : "None");
					AddIngameLine("Team 1", va("%s (%s)", Info_ValueForKey(serverInfo, "g_RQ3_team1Name"), Info_ValueForKey(systemInfo, "g_RQ3_team1model")));
					AddIngameLine("Team 2", va("%s (%s)", Info_ValueForKey(serverInfo, "g_RQ3_team2Name"), Info_ValueForKey(systemInfo, "g_RQ3_team2model")));
					break;
				}
			case GT_TEAM:
				{
					AddIngameLine("Team 1", va("%s (%s)", Info_ValueForKey(serverInfo, "g_RQ3_team1Name"), Info_ValueForKey(systemInfo, "g_RQ3_team1model")));
					AddIngameLine("Team 2", va("%s (%s)", Info_ValueForKey(serverInfo, "g_RQ3_team2Name"), Info_ValueForKey(systemInfo, "g_RQ3_team2model")));
					AddIngameLine("TeamDM Mode", (atoi(Info_ValueForKey(serverInfo, "g_RQ3_tdmMode")) != 0) ? "Classic" : "TP style");
					break;
				}
			case GT_CTF:
				{
					limit = atoi(Info_ValueForKey(serverInfo, "capturelimit"));
					AddIngameLine("Capture limit", (limit !=0 ) ? va("%i", limit) : "None");
					break;
				}
			default:
				{
					limit = atoi(Info_ValueForKey(serverInfo, "fraglimit"));
					AddIngameLine("Frag limit", (limit !=0 ) ? va("%i", limit) : "None");
					break;
				}
		}
		AddIngameLine("Match mode", (matchmode != 0) ? "On" : "Off");
		if (matchmode) {
			//int refID = atoi(Info_ValueForKey(info, "g_RQ3_refID"));
			int allowRef = atoi(Info_ValueForKey(serverInfo, "g_RQ3_allowRef"));
			AddIngameLine("Allow referee", (allowRef != 0) ? va("Yes (%i max)", atoi(Info_ValueForKey(serverInfo, "g_RQ3_maxRefs"))) : "No");
			//if (allowRef && refID != -1) {
			//	char info2[MAX_INFO_STRING];
			//	trap_GetConfigString(CS_PLAYERS + refID, info2, sizeof(info2));
			//	AddIngameLine("Referee", Info_ValueForKey(info2, "name"));
			//}
		}
		AddIngameLine("Max clients", Info_ValueForKey(serverInfo, "sv_maxClients"));
		AddIngameLine("Bot/min players", Info_ValueForKey(serverInfo, "bot_minplayers"));
		AddIngameLine("Password required", (atoi(Info_ValueForKey(serverInfo, "g_needPass")) != 0) ? "Yes" : "No");
		AddIngameLine("Protocol", Info_ValueForKey(serverInfo, "protocol"));
		AddIngameLine("Q3 Version", Info_ValueForKey(serverInfo, "version"));
	}
}


/*
===============
UI_BuildReplacementList
Added by Makro
===============
*/
char *GetLine(char **buf)
{
	char *p;
	if (!buf || !*buf)
		return NULL;
	//p = strchrstr(*buf, "\n\r");
	p = strchr(*buf, '\n');
	if (!p)
	{
		p=*buf;
		*buf+=strlen(p);
	} else {
		int i = 0;
		while (*p=='\r' || *p=='\n')
		{
			i++;
			*(p--)=0;
		}
		p=*buf;
		*buf+=strlen(p)+i;
	}
	return p;
}

void UI_AddReplacement(char *filename)
{
	int len;
	fileHandle_t f;
	char buf[4096], *text;

	if (uiInfo.replacements.Count < MAX_UI_REPLACEMENTS)
	{
		len = trap_FS_FOpenFile(filename, &f, FS_READ);
		if (!f)
			return;
		if (len >= sizeof(buf))
			return;
		trap_FS_Read(buf, len, f);
		buf[len] = 0;
		trap_FS_FCloseFile(f);
		text = buf;
		Q_strncpyz(uiInfo.replacements.Files[uiInfo.replacements.Count], filename, sizeof(uiInfo.replacements.Files[uiInfo.replacements.Count]));
		/*
		//line 1 - replacement name
		Q_strncpyz(uiInfo.replacementNames[uiInfo.replacementCount], GetLine(&text), sizeof(uiInfo.replacementNames[uiInfo.replacementCount]));
		//line 2 - cvar value
		Q_strncpyz(uiInfo.replacementCvars[uiInfo.replacementCount], GetLine(&text), sizeof(uiInfo.replacementCvars[uiInfo.replacementCount]));
		*/
		//line 1 - replacement name
		GetLine(&text);

		//line 2 - cvar value
		Q_strncpyz(uiInfo.replacements.Cvars[uiInfo.replacements.Count], GetLine(&text), sizeof(uiInfo.replacements.Cvars[uiInfo.replacements.Count]));
		if (!strcmp(UI_Cvar_VariableString(va("cg_RQ3_%s", uiInfo.replacements.Type)), uiInfo.replacements.Cvars[uiInfo.replacements.Count]))
		{
			uiInfo.replacements.Index = uiInfo.replacements.Count;
		}
		uiInfo.replacements.Count++;
	}
}

void UI_SelectReplacement(void)
{
	char *currentCvar = UI_Cvar_VariableString(va("cg_RQ3_%s", uiInfo.replacements.Type));

	if (uiInfo.replacements.Count <= 0)
		return;

	uiInfo.replacements.Index %= uiInfo.replacements.Count;

	//if the model isn't already selected
	if (strcmp(currentCvar, uiInfo.replacements.Cvars[uiInfo.replacements.Index]))
	{
		trap_Cvar_Set(va("cg_RQ3_%s", uiInfo.replacements.Type), uiInfo.replacements.Cvars[uiInfo.replacements.Index]);
		//Q_strcat(uiInfo.replacements.Name, sizeof(uiInfo.replacements.Name), " (*)");
		//if we have enough free memory
		if (trap_MemoryRemaining() > 8000000)
		{
			gitem_t *item = NULL;
			int type = -1;
			switch (uiInfo.replacements.TypeIndex)
			{
				case 0:
					switch (uiInfo.replacements.SubtypeIndex)
					{
						case 0:
							type = WP_PISTOL;
							break;
						case 1:
							type = WP_M3;
							break;
						case 2:
							type = WP_MP5;
							break;
						case 3:
							type = WP_HANDCANNON;
							break;
						case 4:
							type = WP_SSG3000;
							break;
						case 5:
							type = WP_M4;
							break;
						case 6:
							type = WP_GRENADE;
							break;
						case 7:
							type = WP_AKIMBO;
							break;
						case 8:
							type = WP_KNIFE;
							break;
						default:
							break;
					}
					if (type != -1)
						item = BG_FindItemForWeapon(type);
					break;
				case 1:
				case 2:
					break;
				default:
					break;
			}
			if (item)
			{
				trap_Cmd_ExecuteText(EXEC_APPEND, va("reloadmodel 0 %i\n", type));
			}
		}
	}
}

void UI_BuildReplacementList(const char *type)
{
	int i, numfiles, filelen;
	char filelist[8192], *fileptr;
	
	if (!type || !*type)
		return;
	
	uiInfo.replacements.Count = 0;
	uiInfo.replacements.Index = 0;
	Q_strncpyz(uiInfo.replacements.Type, type, sizeof(uiInfo.replacements.Type));
	numfiles = trap_FS_GetFileList("models/replacements", "cfg", filelist, sizeof(filelist));
	fileptr = filelist;
	for (i = 0; i < numfiles && uiInfo.replacements.Count < MAX_UI_REPLACEMENTS; i++, fileptr += filelen + 1)
	{
		filelen = strlen(fileptr);
		if (Q_stricmpn(fileptr, va("%s_", type), strlen(type)+1))
			continue;
		UI_AddReplacement(va("models/replacements/%s", fileptr));
	}
	//Com_Printf("Read info for %i replacement(s) of type %s\n", uiInfo.replacementCount, uiInfo.replacementType);
}

void UI_LoadReplacement(int index)
{
	int len;
	fileHandle_t f;
	char buf[4096], *p, *text, skin[MAX_QPATH], model[MAX_QPATH];
	char *currentCvar = UI_Cvar_VariableString(va("cg_RQ3_%s", uiInfo.replacements.Type));
	const char *typeDir = replacementTypes[uiInfo.replacements.TypeIndex % replacementTypeCount].cvarName;

	uiInfo.replacements.Info[0]=0;
	uiInfo.replacements.Name[0]=0;

	//Com_Printf("UI_LoadReplacement(%i) - %s\n", index, uiInfo.replacementFiles[index]);
	if (index < 0 || index >= uiInfo.replacements.Count)
		return;

	len = trap_FS_FOpenFile(uiInfo.replacements.Files[index], &f, FS_READ);
	if (!f)
		return;
	if (len >= sizeof(buf))
		return;
	//Com_Printf("Everything's ok !\n");
	trap_FS_Read(buf, len, f);
	buf[len] = 0;
	trap_FS_FCloseFile(f);
	uiInfo.replacements.Index = index;
	text = buf;
	//line 1 - replacement name
	Q_strncpyz(uiInfo.replacements.Name, GetLine(&text), sizeof(uiInfo.replacements.Name));

	//line 2 - cvar value
	p=GetLine(&text);
	Q_strncpyz(model, modelFromStr(p), sizeof(model));
	if (!Q_stricmp(model, "default"))
		Q_strncpyz(model, uiInfo.replacements.Type, sizeof(model));
	if (!strcmp(currentCvar, p))
	{
		//Q_strcat(uiInfo.replacements.Name, sizeof(uiInfo.replacements.Name), " (*)");
	}
	
	Q_strncpyz(skin, skinFromStr(p), sizeof(skin));
	//trap_Cvar_Set(va("cg_RQ3_%s", uiInfo.replacements.Type), p);

	//line 3 - co-ordinates
	p = GetLine(&text);
	sscanf(p, "%f %f %f %f %f %f %i %i %i", &uiInfo.replacements.origin[0], &uiInfo.replacements.origin[1], &uiInfo.replacements.origin[2],
		&uiInfo.replacements.angles[0], &uiInfo.replacements.angles[1], &uiInfo.replacements.angles[2],
		&uiInfo.replacements.fovx, &uiInfo.replacements.fovy, &uiInfo.replacements.speed);
	//Com_Printf("Model: %s\n", va("models/%s/%s/%s.md3", typeDir, model, uiInfo.replacements.Type));
	//Com_Printf("Skin : %s\n", va("models/%s/%s/%s.skin", typeDir, model, skin));
	if (!Q_stricmp(typeDir, "ammo")) {
		uiInfo.replacements.Model = trap_R_RegisterModel(va("models/%s/%s.md3", typeDir, model));
		uiInfo.replacements.Skin = trap_R_RegisterSkin(va("models/%s/%s.skin", typeDir, skin));
		//Com_Printf("AmmoModel: %s\n", va("models/%s/%s.md3", typeDir, model));
		//Com_Printf("AmmoSkin : %s\n", va("models/%s/%s.skin", typeDir, skin));
	} else if (!Q_stricmp(typeDir, "items")) {
		uiInfo.replacements.Model = trap_R_RegisterModel(va("models/%s/%s.md3", typeDir, model));
		uiInfo.replacements.Skin = trap_R_RegisterSkin(va("models/%s/%s/%s.skin", typeDir, model, skin));
		//Com_Printf("ItemModel: %s\n", va("models/%s/%s.md3", typeDir, model));
		//Com_Printf("ItemSkin : %s\n", va("models/%s/%s/%s.skin", typeDir, model, skin));
	} else {
		uiInfo.replacements.Model = trap_R_RegisterModel(va("models/%s/%s/%s.md3", typeDir, model, uiInfo.replacements.Type));
		uiInfo.replacements.Skin = trap_R_RegisterSkin(va("models/%s/%s/%s.skin", typeDir, model, skin));
		//Com_Printf("WeaponModel: %s\n", va("models/%s/%s/%s.md3", typeDir, model, uiInfo.replacements.Type));
		//Com_Printf("WeaponSkin : %s\n", va("models/%s/%s/%s.skin", typeDir, model, skin));
	}
	//...replacement info
	Q_strncpyz(uiInfo.replacements.Info, text, sizeof(uiInfo.replacements.Info));
}

/*
===============
UI_BuildPlayerList
===============
*/
static void UI_BuildPlayerList()
{
	uiClientState_t cs;
	int n, count, team, team2, playerTeamNumber;
	char info[MAX_INFO_STRING];

	trap_GetClientState(&cs);
	trap_GetConfigString(CS_PLAYERS + cs.clientNum, info, MAX_INFO_STRING);
	uiInfo.playerNumber = cs.clientNum;
	uiInfo.teamLeader = atoi(Info_ValueForKey(info, "tl"));
	team = atoi(Info_ValueForKey(info, "t"));
	trap_GetConfigString(CS_SERVERINFO, info, sizeof(info));
	count = atoi(Info_ValueForKey(info, "sv_maxclients"));
	uiInfo.playerCount = 0;
	uiInfo.myTeamCount = 0;
	playerTeamNumber = 0;
	for (n = 0; n < count; n++) {
		trap_GetConfigString(CS_PLAYERS + n, info, MAX_INFO_STRING);

		if (info[0]) {
			Q_strncpyz(uiInfo.playerNames[uiInfo.playerCount], Info_ValueForKey(info, "n"),
				   MAX_NAME_LENGTH);
			Q_CleanStr(uiInfo.playerNames[uiInfo.playerCount]);
			uiInfo.clientNums[uiInfo.playerCount] = n;
			uiInfo.playerCount++;
			team2 = atoi(Info_ValueForKey(info, "t"));
			if (team2 == team) {
				Q_strncpyz(uiInfo.teamNames[uiInfo.myTeamCount], Info_ValueForKey(info, "n"),
					   MAX_NAME_LENGTH);
				Q_CleanStr(uiInfo.teamNames[uiInfo.myTeamCount]);
				uiInfo.teamClientNums[uiInfo.myTeamCount] = n;
				if (uiInfo.playerNumber == n) {
					playerTeamNumber = uiInfo.myTeamCount;
				}
				uiInfo.myTeamCount++;
			}
		}
	}

	if (!uiInfo.teamLeader) {
		trap_Cvar_Set("cg_selectedPlayer", va("%d", playerTeamNumber));
	}

	n = trap_Cvar_VariableValue("cg_selectedPlayer");
	if (n < 0 || n > uiInfo.myTeamCount) {
		n = 0;
	}
	if (n < uiInfo.myTeamCount) {
		trap_Cvar_Set("cg_selectedPlayerName", uiInfo.teamNames[n]);
	}
}

static void UI_DrawSelectedPlayer(rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
	if (uiInfo.uiDC.realTime > uiInfo.playerRefresh) {
		uiInfo.playerRefresh = uiInfo.uiDC.realTime + 3000;
		UI_BuildPlayerList();
	}
	Text_Paint(rect->x, rect->y, scale, color,
		   (uiInfo.
		    teamLeader) ? UI_Cvar_VariableString("cg_selectedPlayerName") : UI_Cvar_VariableString("name"), 0,
		   0, 0, textStyle, qfalse);
}

static void UI_DrawServerRefreshDate(rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
	if (uiInfo.serverStatus.refreshActive) {
		vec4_t lowLight, newColor;
		int count = trap_LAN_GetServerCount(ui_netSource.integer);
		const char* msg = (count > 0) ? va("Getting info for %d servers (ESC to cancel)", count) :
			"Getting server info (ESC to cancel)";

		lowLight[0] = 0.8 * color[0];
		lowLight[1] = 0.8 * color[1];
		lowLight[2] = 0.8 * color[2];
		lowLight[3] = 0.8 * color[3];
		if (count < 0) {
			count = 0;
		}
		LerpColor(color, lowLight, newColor, 0.5 + 0.5 * sin(uiInfo.uiDC.realTime / PULSE_DIVISOR));
		
		if (rect->hasVectors)
			Text_PaintAngled(rect->x, rect->y, rect->u, rect->v, scale, newColor,
			   msg, 0, 0, 0, textStyle, qfalse);
		else
			Text_Paint(rect->x, rect->y, scale, newColor,
			   msg, 0, 0, 0, textStyle, qfalse);
	} else {
		char buff[64];
		const char* msg;

		Q_strncpyz(buff, UI_Cvar_VariableString(va("ui_lastServerRefresh_%i", ui_netSource.integer)), 64);
		msg = va("Refresh Time: %s", buff);
		if (rect->hasVectors)
			Text_PaintAngled(rect->x, rect->y, rect->u, rect->v, scale, color, msg, 0, 0, 0, textStyle, qfalse);
		else
			Text_Paint(rect->x, rect->y, scale, color, msg, 0, 0, 0, textStyle, qfalse);
	}
}

static void UI_DrawServerMOTD(rectDef_t * rect, float scale, vec4_t color)
{
	if (uiInfo.serverStatus.motdLen) {
		float maxX;

		if (uiInfo.serverStatus.motdWidth == -1) {
			uiInfo.serverStatus.motdWidth = 0;
			uiInfo.serverStatus.motdPaintX = rect->x + 1;
			uiInfo.serverStatus.motdPaintX2 = -1;
		}

		if (uiInfo.serverStatus.motdOffset > uiInfo.serverStatus.motdLen) {
			uiInfo.serverStatus.motdOffset = 0;
			uiInfo.serverStatus.motdPaintX = rect->x + 1;
			uiInfo.serverStatus.motdPaintX2 = -1;
		}

		if (uiInfo.uiDC.realTime > uiInfo.serverStatus.motdTime) {
			uiInfo.serverStatus.motdTime = uiInfo.uiDC.realTime + 10;
			if (uiInfo.serverStatus.motdPaintX <= rect->x + 2) {
				if (uiInfo.serverStatus.motdOffset < uiInfo.serverStatus.motdLen) {
					uiInfo.serverStatus.motdPaintX +=
					    Text_Width(&uiInfo.serverStatus.motd[uiInfo.serverStatus.motdOffset], scale,
						       1) - 1;
					uiInfo.serverStatus.motdOffset++;
				} else {
					uiInfo.serverStatus.motdOffset = 0;
					if (uiInfo.serverStatus.motdPaintX2 >= 0) {
						uiInfo.serverStatus.motdPaintX = uiInfo.serverStatus.motdPaintX2;
					} else {
						uiInfo.serverStatus.motdPaintX = rect->x + rect->w - 2;
					}
					uiInfo.serverStatus.motdPaintX2 = -1;
				}
			} else {
				//serverStatus.motdPaintX--;
				uiInfo.serverStatus.motdPaintX -= 2;
				if (uiInfo.serverStatus.motdPaintX2 >= 0) {
					//serverStatus.motdPaintX2--;
					uiInfo.serverStatus.motdPaintX2 -= 2;
				}
			}
		}

		maxX = rect->x + rect->w - 2;
		Text_Paint_Limit(&maxX, uiInfo.serverStatus.motdPaintX, rect->y + rect->h - 3, scale, color,
				 &uiInfo.serverStatus.motd[uiInfo.serverStatus.motdOffset], 0, 0);
		if (uiInfo.serverStatus.motdPaintX2 >= 0) {
			float maxX2 = rect->x + rect->w - 2;

			Text_Paint_Limit(&maxX2, uiInfo.serverStatus.motdPaintX2, rect->y + rect->h - 3, scale, color,
					 uiInfo.serverStatus.motd, 0, uiInfo.serverStatus.motdOffset);
		}
		if (uiInfo.serverStatus.motdOffset && maxX > 0) {
			// if we have an offset ( we are skipping the first part of the string ) and we fit the string
			if (uiInfo.serverStatus.motdPaintX2 == -1) {
				uiInfo.serverStatus.motdPaintX2 = rect->x + rect->w - 2;
			}
		} else {
			uiInfo.serverStatus.motdPaintX2 = -1;
		}

	}
}

static void UI_DrawKeyBindStatus(itemDef_t *item, rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
//      int ofs = 0; TTimo: unused
	if (Display_KeyBindPending()) {
		if (item->window.rect.hasVectors)
		{
			Text_PaintAngled(rect->x, rect->y, item->window.rect.u, item->window.rect.v,
				scale, color, uiInfo.keyBindStatus2, 0, 0, 0, textStyle, qfalse);
		} else {
			Text_Paint(rect->x, rect->y, scale, color, uiInfo.keyBindStatus2, 0, 0, 0, textStyle, qfalse);
		}
	} else {
		if (item->window.rect.hasVectors)
		{
			Text_PaintAngled(rect->x, rect->y, item->window.rect.u, item->window.rect.v,
				scale, color, uiInfo.keyBindStatus1, 0, 0, 0, textStyle, qfalse);
		} else {
			Text_Paint(rect->x, rect->y, scale, color, uiInfo.keyBindStatus1, 0, 0, 0, textStyle, qfalse);
		}
	}
}

//Makro - rewrote this function - added more info and support for vectors; moved extensions to FEEDER_GLDRIVER_INFO

#define GLINFO_STRING1	va("RENDERER: %s / %s", uiInfo.uiDC.glconfig.renderer_string, uiInfo.uiDC.glconfig.vendor_string)
#define GLINFO_STRING2	va("VERSION: %s", uiInfo.uiDC.glconfig.version_string)
#define GLINFO_STRING3	va("PIXELFORMAT: color(%d) Z(%d) stencil(%d); REFRESH: %d Hz", uiInfo.uiDC.glconfig.colorBits,\
	uiInfo.uiDC.glconfig.depthBits, uiInfo.uiDC.glconfig.stencilBits, uiInfo.uiDC.glconfig.displayFrequency)
#define GLINFO_STRING4	va("TEX: %d units, %d x %d max%s%s", uiInfo.uiDC.glconfig.maxActiveTextures,\
	uiInfo.uiDC.glconfig.maxTextureSize, uiInfo.uiDC.glconfig.maxTextureSize,\
	(uiInfo.uiDC.glconfig.textureCompression == TC_NONE) ? "" : ", compressed", uiInfo.uiDC.glconfig.smpActive ? "; SMP: on" : "")

static void UI_DrawGLInfo(rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
	float p[2];
	float u[2] = {1, 0};
	float v[2] = {0, 1};

	Vector2Set(p, rect->x, rect->y);

	//Makro - vectors?
	if (rect->hasVectors)
	{
		Vector2Copy(rect->u, u);
		Vector2Copy(rect->v, v);
	}

	//Makro - rewrote this code
	if (rect->hasVectors)
	{
		#define GLINFO_OUTPUT_STRING_ANGLED(str)\
			Text_PaintAngled(p[0], p[1], u, v, scale, color, str, 0, 0, rect->w, textStyle, qfalse);\
			Vector2MA(p, 64 * scale, v, p)

		GLINFO_OUTPUT_STRING_ANGLED(GLINFO_STRING1);
		GLINFO_OUTPUT_STRING_ANGLED(GLINFO_STRING2);
		GLINFO_OUTPUT_STRING_ANGLED(GLINFO_STRING3);
		GLINFO_OUTPUT_STRING_ANGLED(GLINFO_STRING4);
	}
	else
	{
		#define GLINFO_OUTPUT_STRING(str)\
			Text_Paint(p[0], p[1], scale, color, str, 0, 0, rect->w, textStyle, qfalse);\
			Vector2MA(p, 64 * scale, v, p)

		GLINFO_OUTPUT_STRING(GLINFO_STRING1);
		GLINFO_OUTPUT_STRING(GLINFO_STRING2);
		GLINFO_OUTPUT_STRING(GLINFO_STRING3);
		GLINFO_OUTPUT_STRING(GLINFO_STRING4);
	}
}

//Makro - startup menu text
static void UI_DrawStartupText(itemDef_t *item, rectDef_t *rect, float scale, vec4_t color, int textStyle)
{
	if (!item->window.rectClient.hasVectors) {
		Text_Paint(rect->x, rect->y, scale, color, uiInfo.startupText, 0, 0, 0, textStyle, qfalse);
	} else {
		Text_PaintAngled(rect->x, rect->y,
			item->window.rectClient.u, item->window.rectClient.v, scale, color, uiInfo.startupText, 0, 0, 0, textStyle, qfalse);
	}
}

//Makro - replacement model info
static void UI_DrawReplacementInfo(rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
	int y = rect->y;
	char buf[4096], *text = buf, *p;
	
	Q_strncpyz(buf, uiInfo.replacements.Info, sizeof(buf));
	do {
		int l;
		p = GetLine(&text);
		l = strlen(p);
		while ( l>0 && Text_Width(p, scale, 0) > rect->w )
			p[l--]=0;
		Text_Paint(rect->x, y, scale, color, p, 0, 0, 0, textStyle, qfalse);
		y += Text_Height(p, scale, 0) + 4;
	} while (strlen(text)>0 /*&& y<rect->h*/);
}

static void UI_DrawReplacementName(rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
	char name[128], *curCvar = UI_Cvar_VariableString(va("cg_RQ3_%s", uiInfo.replacements.Type));
	char *newCvar;
	int l;
	
	if (uiInfo.replacements.Count <= 0)
		return;

	Q_strncpyz(name, uiInfo.replacements.Name, sizeof(name));
	newCvar = uiInfo.replacements.Cvars[uiInfo.replacements.Index % uiInfo.replacements.Count];

	if (!strcmp(newCvar, curCvar))
		Q_strins(name, "> ", sizeof(name));

	//don't go over the window borders
	l = strlen(name);
	while (l>0 && Text_Width(name, scale, 0)>rect->w)
		name[l--]=0;

	Text_Paint(rect->x, rect->y, scale, color, name, 0, 0, 0, textStyle, qfalse);
}

static void UI_DrawReplacementType(rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
	const char *p = replacementTypes[uiInfo.replacements.TypeIndex % replacementTypeCount].displayName;

	Text_Paint(rect->x, rect->y, scale, color, p, 0, 0, 0, textStyle, qfalse);
}

static void UI_DrawReplacementSubtype(rectDef_t * rect, float scale, vec4_t color, int textStyle)
{
	const char *p;

	switch (uiInfo.replacements.TypeIndex)
	{
		case 0:
			p = replacementWeapons[uiInfo.replacements.SubtypeIndex % replacementWeapCount].displayName;
			break;
		case 1:
			p = replacementItems[uiInfo.replacements.SubtypeIndex % replacementItemCount].displayName;
			break;
		case 2:
			p = replacementAmmo[uiInfo.replacements.SubtypeIndex % replacementAmmoCount].displayName;
			break;
		default:
			return;
	}
	Text_Paint(rect->x, rect->y, scale, color, p, 0, 0, 0, textStyle, qfalse);
}

static void UI_DrawReplacementModel(rectDef_t *rect)
{
	float x, y, w, h;
	refdef_t refdef;
	refEntity_t ent;
	vec3_t mins, maxs, origin;
	vec3_t angles;

	if (uiInfo.replacements.Count <= 0)
		return;

	// setup the refdef
	memset(&refdef, 0, sizeof(refdef));
	refdef.rdflags = RDF_NOWORLDMODEL;
	AxisClear(refdef.viewaxis);
	x = rect->x + 1;
	y = rect->y + 1;
	w = rect->w - 2;
	h = rect->h - 2;

	UI_AdjustFrom640(&x, &y, &w, &h);

	refdef.x = x;
	refdef.y = y;
	refdef.width = w;
	refdef.height = h;

	uiInfo.uiDC.modelBounds(uiInfo.replacements.Model, mins, maxs);

	origin[2] = -0.5 * (mins[2] + maxs[2]);
	origin[1] = 0.5 * (mins[1] + maxs[1]);

	// calculate distance so the model nearly fills the box
	if (qtrue) {
		float len = 0.5 * (maxs[2] - mins[2]);

		origin[0] = len / 0.268;	// len / tan( fov/2 )
		//origin[0] = len / tan(w/2);
	}
	refdef.fov_x = (uiInfo.replacements.fovx) ? uiInfo.replacements.fovx : 60;
	refdef.fov_y = (uiInfo.replacements.fovy) ? uiInfo.replacements.fovy : 60;

	//refdef.fov_x = (int)((float)refdef.width / 640.0f * 90.0f);
	//xx = refdef.width / tan( refdef.fov_x / 360 * M_PI );
	//refdef.fov_y = atan2( refdef.height, xx );
	//refdef.fov_y *= ( 360 / M_PI );

	uiInfo.uiDC.clearScene();

	refdef.time = uiInfo.uiDC.realTime;

	// add the model
	memset(&ent, 0, sizeof(ent));

	//adjust = 5.0 * sin( (float)uis.realtime / 500 );
	//adjust = 360 % (int)((float)uis.realtime / 1000);
	//VectorSet( angles, 0, 0, 1 );

	//changed for Birdman...
	//VectorCopy(uiInfo.replacements.angles, angles);
	angles[YAW] = uiInfo.replacements.angles[0];
	angles[PITCH] = uiInfo.replacements.angles[1];
	angles[ROLL] = uiInfo.replacements.angles[2];
	// rotation
	if (uiInfo.replacements.speed) {
		angles[YAW] += uiInfo.replacements.speed * uiInfo.uiDC.realTime / 1000.0f;
	}
	AnglesToAxis(angles, ent.axis);

	VectorAdd(origin, uiInfo.replacements.origin, origin);

	ent.hModel = uiInfo.replacements.Model;
// JBravo: Added so replacements work
	ent.customSkin = uiInfo.replacements.Skin;
	VectorCopy(origin, ent.origin);
	VectorCopy(origin, ent.lightingOrigin);
	ent.renderfx = RF_LIGHTING_ORIGIN | RF_NOSHADOW;
	VectorCopy(ent.origin, ent.oldorigin);

	uiInfo.uiDC.addRefEntityToScene(&ent);
	uiInfo.uiDC.renderScene(&refdef);
}


// FIXME: table drive
//
//Makro - going to... eventually
static void UI_OwnerDraw(itemDef_t *item, float x, float y, float w, float h, float text_x, float text_y, int ownerDraw,
			 int ownerDrawFlags, int align, float special, float scale, vec4_t color, qhandle_t shader,
			 int textStyle)
{
	rectDef_t rect;

	rect.w = w;
	rect.h = h;
	if (item->window.rectClient.hasVectors)
	{
		float p[2];

		p[0] = x;
		p[1] = y;
		Vector2Copy(item->window.rectClient.u, rect.u);
		Vector2Copy(item->window.rectClient.v, rect.v);
		Vector2MA(p, text_x, rect.u, p);
		Vector2MA(p, text_y, rect.v, p);
		rect.x = p[0];
		rect.y = p[1];
		rect.hasVectors = qtrue;
	} else {
		rect.hasVectors = qfalse;
		rect.x = x + text_x;
		rect.y = y + text_y;
	}

	switch (ownerDraw) {
	case UI_HANDICAP:
		UI_DrawHandicap(&rect, scale, color, textStyle);
		break;
	case UI_EFFECTS:
		UI_DrawEffects(&rect, scale, color);
		break;
	case UI_PLAYERMODEL:
		UI_DrawPlayerModel(&rect);
		break;
	case UI_CLANNAME:
		UI_DrawClanName(&rect, scale, color, textStyle);
		break;
	case UI_CLANLOGO:
		UI_DrawClanLogo(&rect, scale, color);
		break;
	case UI_CLANCINEMATIC:
		UI_DrawClanCinematic(&rect, scale, color);
		break;
	case UI_PREVIEWCINEMATIC:
		UI_DrawPreviewCinematic(&rect, scale, color);
		break;
	case UI_GAMETYPE:
		UI_DrawGameType(&rect, scale, color, textStyle);
		break;
	case UI_NETGAMETYPE:
		UI_DrawNetGameType(&rect, scale, color, textStyle);
		break;
	case UI_JOINGAMETYPE:
		UI_DrawJoinGameType(&rect, scale, color, textStyle);
		break;
	case UI_MAPPREVIEW:
		UI_DrawMapPreview(&rect, scale, color, qtrue);
		break;
	case UI_MAP_TIMETOBEAT:
		UI_DrawMapTimeToBeat(&rect, scale, color, textStyle);
		break;
	case UI_MAPCINEMATIC:
		UI_DrawMapCinematic(&rect, scale, color, qfalse);
		break;
	case UI_STARTMAPCINEMATIC:
		UI_DrawMapCinematic(&rect, scale, color, qtrue);
		break;
	case UI_SKILL:
		UI_DrawSkill(&rect, scale, color, textStyle);
		break;
	case UI_BLUETEAMNAME:
		UI_DrawTeamName(&rect, scale, color, qtrue, textStyle);
		break;
	case UI_REDTEAMNAME:
		UI_DrawTeamName(&rect, scale, color, qfalse, textStyle);
		break;
	case UI_BLUETEAM1:
	case UI_BLUETEAM2:
	case UI_BLUETEAM3:
	case UI_BLUETEAM4:
	case UI_BLUETEAM5:
		UI_DrawTeamMember(&rect, scale, color, qtrue, ownerDraw - UI_BLUETEAM1 + 1, textStyle);
		break;
	case UI_REDTEAM1:
	case UI_REDTEAM2:
	case UI_REDTEAM3:
	case UI_REDTEAM4:
	case UI_REDTEAM5:
		UI_DrawTeamMember(&rect, scale, color, qfalse, ownerDraw - UI_REDTEAM1 + 1, textStyle);
		break;
	case UI_NETSOURCE:
		UI_DrawNetSource(&rect, scale, color, textStyle);
		break;
	case UI_NETMAPPREVIEW:
		UI_DrawNetMapPreview(&rect, scale, color);
		break;
	case UI_NETMAPCINEMATIC:
		UI_DrawNetMapCinematic(&rect, scale, color);
		break;
	case UI_NETFILTER:
		UI_DrawNetFilter(&rect, scale, color, textStyle);
		break;
	case UI_TIER:
		UI_DrawTier(&rect, scale, color, textStyle);
		break;
	case UI_OPPONENTMODEL:
		UI_DrawOpponent(&rect);
		break;
	case UI_TIERMAP1:
		UI_DrawTierMap(&rect, 0);
		break;
	case UI_TIERMAP2:
		UI_DrawTierMap(&rect, 1);
		break;
	case UI_TIERMAP3:
		UI_DrawTierMap(&rect, 2);
		break;
	case UI_PLAYERLOGO:
		UI_DrawPlayerLogo(&rect, color);
		break;
	case UI_PLAYERLOGO_METAL:
		UI_DrawPlayerLogoMetal(&rect, color);
		break;
	case UI_PLAYERLOGO_NAME:
		UI_DrawPlayerLogoName(&rect, color);
		break;
	case UI_OPPONENTLOGO:
		UI_DrawOpponentLogo(&rect, color);
		break;
	case UI_OPPONENTLOGO_METAL:
		UI_DrawOpponentLogoMetal(&rect, color);
		break;
	case UI_OPPONENTLOGO_NAME:
		UI_DrawOpponentLogoName(&rect, color);
		break;
	case UI_TIER_MAPNAME:
		UI_DrawTierMapName(&rect, scale, color, textStyle);
		break;
	case UI_TIER_GAMETYPE:
		UI_DrawTierGameType(&rect, scale, color, textStyle);
		break;
	case UI_ALLMAPS_SELECTION:
		UI_DrawAllMapsSelection(&rect, scale, color, textStyle, qtrue);
		break;
	case UI_MAPS_SELECTION:
		UI_DrawAllMapsSelection(&rect, scale, color, textStyle, qfalse);
		break;
	case UI_OPPONENT_NAME:
		UI_DrawOpponentName(&rect, scale, color, textStyle);
		break;
	case UI_BOTNAME:
		UI_DrawBotName(&rect, scale, color, textStyle);
		break;
	case UI_BOTSKILL:
		UI_DrawBotSkill(&rect, scale, color, textStyle);
		break;
	case UI_REDBLUE:
		UI_DrawRedBlue(&rect, scale, color, textStyle);
		break;
	case UI_CROSSHAIR:
		UI_DrawCrosshair(&rect, scale);
		break;
	//Makro - adding SSG crosshair
	case UI_SSG_CROSSHAIR:
		UI_DrawSSGCrosshair(&rect);
		break;
	case UI_CLOCK:
		UI_DrawClock(item, &rect, scale, color, textStyle);
		break;
	//Makro - radio presets
	case UI_RQ3_RADIOPRESET1:
	case UI_RQ3_RADIOPRESET2:
	case UI_RQ3_RADIOPRESET3:
	case UI_RQ3_RADIOPRESET4:
	case UI_RQ3_RADIOPRESET5:
	case UI_RQ3_RADIOPRESET6:
	case UI_RQ3_RADIOPRESET7:
	case UI_RQ3_RADIOPRESET8:
	case UI_RQ3_RADIOPRESET9:
	case UI_RQ3_RADIOPRESET10:
		UI_RQ3_DrawPreset(&rect, scale, color, ownerDraw - UI_RQ3_RADIOPRESET1 + 1, textStyle);
		break;
	//Makro - join team menu items
	case UI_RQ3_JOINTEAM1:
	case UI_RQ3_JOINTEAM2:
		UI_RQ3_DrawJoinTeam(&rect, scale, color, (ownerDraw == UI_RQ3_JOINTEAM1) ? 1 : 2, textStyle);
		break;
	//Makro - replacement model info
	case UI_RQ3_REPLACEMENTINFO:
		UI_DrawReplacementInfo(&rect, scale, color, textStyle);
		break;
	//Makro - replacement model name
	case UI_RQ3_REPLACEMENTNAME:
		UI_DrawReplacementName(&rect, scale, color, textStyle);
		break;
	//Makro - replacement model
	case UI_RQ3_REPLACEMENTMODEL:
		UI_DrawReplacementModel(&rect);
		break;
	//Makro - replacement type
	case UI_RQ3_REPLACEMENTTYPE:
		UI_DrawReplacementType(&rect, scale, color, textStyle);
		break;
	//Makro - replacement subtype
	case UI_RQ3_REPLACEMENTSUBTYPE:
		UI_DrawReplacementSubtype(&rect, scale, color, textStyle);
		break;
	//Makro - startup menu text
	case UI_RQ3_STARTUP:
		UI_DrawStartupText(item, &rect, scale, color, textStyle);
		break;
	case UI_SELECTEDPLAYER:
		UI_DrawSelectedPlayer(&rect, scale, color, textStyle);
		break;
	case UI_SERVERREFRESHDATE:
		UI_DrawServerRefreshDate(&rect, scale, color, textStyle);
		break;
	case UI_SERVERMOTD:
		UI_DrawServerMOTD(&rect, scale, color);
		break;
	case UI_GLINFO:
		UI_DrawGLInfo(&rect, scale, color, textStyle);
		break;
	case UI_KEYBINDSTATUS:
		UI_DrawKeyBindStatus(item, &rect, scale, color, textStyle);
		break;
	default:
		break;
	}

}

typedef struct
{
	int banFlag, uiFlag;
} banInfo_t;

banInfo_t menuWeapBans[] =
{
	{WPF_MP5,		UI_SHOW_WEAP1},
	{WPF_M3,		UI_SHOW_WEAP2},
	{WPF_HC,		UI_SHOW_WEAP3},
	{WPF_SNIPER,		UI_SHOW_WEAP4},
	{WPF_M4,		UI_SHOW_WEAP5},
	{WPF_KNIFE,		UI_SHOW_WEAP6},
	{WPF_DUAL | WPF_MK23,	UI_SHOW_WEAP7}
};
static const int menuWeapCount = sizeof(menuWeapBans)/sizeof(banInfo_t);
banInfo_t menuItemBans[] =
{
	{ITF_KEVLAR,		UI_SHOW_ITEM1},
	{ITF_LASER,		UI_SHOW_ITEM2},
	{ITF_SLIPPERS,		UI_SHOW_ITEM3},
	{ITF_SILENCER,		UI_SHOW_ITEM4},
	{ITF_BANDOLIER,		UI_SHOW_ITEM5},
	{ITF_HELMET,		UI_SHOW_ITEM6}
};
static const int menuItemCount = sizeof(menuItemBans)/sizeof(banInfo_t);

/* Makro - this was ugly
static int menuWeapons[] = {WPF_MP5, WPF_M3, WPF_HC, WPF_SNIPER, WPF_M4, WPF_KNIFE, WPF_GRENADE};
static int menuWeapFlags[] = {UI_SHOW_WEAP1, UI_SHOW_WEAP2, UI_SHOW_WEAP3, UI_SHOW_WEAP4, UI_SHOW_WEAP5, UI_SHOW_WEAP6, UI_SHOW_WEAP7};
static const int menuWeapCount = sizeof(menuWeapons)/sizeof(int);
static int menuItems[] = {ITF_KEVLAR, ITF_LASER, ITF_SLIPPERS, ITF_SILENCER, ITF_BANDOLIER, ITF_HELMET};
static int menuItemFlags[] = {UI_SHOW_ITEM1, UI_SHOW_ITEM2, UI_SHOW_ITEM3, UI_SHOW_ITEM4, UI_SHOW_ITEM5, UI_SHOW_ITEM6};
static const int menuItemCount = sizeof(menuItems)/sizeof(int);
*/

static qboolean UI_OwnerDrawVisible(int flags)
{
	qboolean vis = qtrue;

	//Makro - was this really needed ?
	//while (flags) {
		//Makro - added
		int i;

		if (flags & UI_SHOW_FFA) {
			if (trap_Cvar_VariableValue("g_gametype") != GT_FFA) {
				vis = qfalse;
			}
			flags &= ~UI_SHOW_FFA;
		}

		if (flags & UI_SHOW_NOTFFA) {
			if (trap_Cvar_VariableValue("g_gametype") == GT_FFA) {
				vis = qfalse;
			}
			flags &= ~UI_SHOW_NOTFFA;
		}

		if (flags & UI_SHOW_LEADER) {
			// these need to show when this client can give orders to a player or a group
			if (!uiInfo.teamLeader) {
				vis = qfalse;
			} else {
				// if showing yourself
				if (ui_selectedPlayer.integer < uiInfo.myTeamCount
				    && uiInfo.teamClientNums[ui_selectedPlayer.integer] == uiInfo.playerNumber) {
					vis = qfalse;
				}
			}
			flags &= ~UI_SHOW_LEADER;
		}
		if (flags & UI_SHOW_NOTLEADER) {
			// these need to show when this client is assigning their own status or they are NOT the leader
			if (uiInfo.teamLeader) {
				// if not showing yourself
				if (!
				    (ui_selectedPlayer.integer < uiInfo.myTeamCount
				     && uiInfo.teamClientNums[ui_selectedPlayer.integer] == uiInfo.playerNumber)) {
					vis = qfalse;
				}
				// these need to show when this client can give orders to a player or a group
			}
			flags &= ~UI_SHOW_NOTLEADER;
		}
		if (flags & UI_SHOW_FAVORITESERVERS) {
			// this assumes you only put this type of display flag on something showing in the proper context
			if (ui_netSource.integer != AS_FAVORITES) {
				vis = qfalse;
			}
			flags &= ~UI_SHOW_FAVORITESERVERS;
		}
		if (flags & UI_SHOW_NOTFAVORITESERVERS) {
			// this assumes you only put this type of display flag on something showing in the proper context
			if (ui_netSource.integer == AS_FAVORITES) {
				vis = qfalse;
			}
			flags &= ~UI_SHOW_NOTFAVORITESERVERS;
		}
		if (flags & UI_SHOW_ANYTEAMGAME) {
			if (uiInfo.gameTypes[ui_gameType.integer].gtEnum <= GT_TEAM) {
				vis = qfalse;
			}
			flags &= ~UI_SHOW_ANYTEAMGAME;
		}
		if (flags & UI_SHOW_ANYNONTEAMGAME) {
			if (uiInfo.gameTypes[ui_gameType.integer].gtEnum > GT_TEAM) {
				vis = qfalse;
			}
			flags &= ~UI_SHOW_ANYNONTEAMGAME;
		}
		if (flags & UI_SHOW_NETANYTEAMGAME) {
			if (uiInfo.gameTypes[ui_netGameType.integer].gtEnum <= GT_TEAM) {
				vis = qfalse;
			}
			flags &= ~UI_SHOW_NETANYTEAMGAME;
		}
		if (flags & UI_SHOW_NETANYNONTEAMGAME) {
			if (uiInfo.gameTypes[ui_netGameType.integer].gtEnum > GT_TEAM) {
				vis = qfalse;
			}
			flags &= ~UI_SHOW_NETANYNONTEAMGAME;
		}
		if (flags & UI_SHOW_NEWHIGHSCORE) {
			if (uiInfo.newHighScoreTime < uiInfo.uiDC.realTime) {
				vis = qfalse;
			} else {
				if (uiInfo.soundHighScore) {
					if (trap_Cvar_VariableValue("sv_killserver") == 0) {
						// wait on server to go down before playing sound
						trap_S_StartLocalSound(uiInfo.newHighScoreSound, CHAN_ANNOUNCER);
						uiInfo.soundHighScore = qfalse;
					}
				}
			}
			flags &= ~UI_SHOW_NEWHIGHSCORE;
		}
		if (flags & UI_SHOW_NEWBESTTIME) {
			if (uiInfo.newBestTime < uiInfo.uiDC.realTime) {
				vis = qfalse;
			}
			flags &= ~UI_SHOW_NEWBESTTIME;
		}
		if (flags & UI_SHOW_DEMOAVAILABLE) {
			if (!uiInfo.demoAvailable) {
				vis = qfalse;
			}
			flags &= ~UI_SHOW_DEMOAVAILABLE;
		}
		//Makro - item/weapon banning
		for (i=0; i<menuWeapCount; i++)
			if (flags & menuWeapBans[i].uiFlag) {
				if (!(uiInfo.weapBan & menuWeapBans[i].banFlag))
					vis = qfalse;
				flags &= ~menuWeapBans[i].uiFlag;
			}
		for (i=0; i<menuItemCount; i++) {
			if (flags & menuItemBans[i].uiFlag) {
				//special check for the helmet
				if (menuItemBans[i].banFlag == ITF_HELMET && (trap_Cvar_VariableValue("g_RQ3_haveHelmet") == 0))
					vis = qfalse;
				else if (!(uiInfo.itemBan & menuItemBans[i].banFlag))
					vis = qfalse;
				flags &= ~menuItemBans[i].uiFlag;
			}
		}
		//Makro - added toggle flag
		if (flags & UI_SHOW_TOGGLE) {
			vis ^= 1;
		}
		flags = 0;
	return vis;
}

static qboolean UI_Handicap_HandleKey(int flags, float *special, int key)
{
	if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_ENTER || key == K_KP_ENTER) {
		int h;

		h = Com_Clamp(5, 100, trap_Cvar_VariableValue("handicap"));
		if (key == K_MOUSE2) {
			h -= 5;
		} else {
			h += 5;
		}
		if (h > 100) {
			h = 5;
		} else if (h < 0) {
			h = 100;
		}
		trap_Cvar_Set("handicap", va("%i", h));
		return qtrue;
	}
	return qfalse;
}

static qboolean UI_Effects_HandleKey(int flags, float *special, int key)
{
	//Makro - left/right support
	if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_ENTER || key == K_KP_ENTER || key == K_LEFTARROW
	    || key == K_RIGHTARROW) {

		if (key == K_MOUSE2 || key == K_LEFTARROW) {
			uiInfo.effectsColor--;
		} else {
			uiInfo.effectsColor++;
		}

		if (uiInfo.effectsColor > 6) {
			uiInfo.effectsColor = 0;
		} else if (uiInfo.effectsColor < 0) {
			uiInfo.effectsColor = 6;
		}

		trap_Cvar_SetValue("color1", uitogamecode[uiInfo.effectsColor]);
		return qtrue;
	}
	return qfalse;
}

static qboolean UI_ClanName_HandleKey(int flags, float *special, int key)
{
	//Makro - left/right support
	if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_ENTER || key == K_KP_ENTER || key == K_LEFTARROW
	    || key == K_RIGHTARROW) {
		int i;

		i = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_teamName"));
		if (uiInfo.teamList[i].cinematic >= 0) {
			trap_CIN_StopCinematic(uiInfo.teamList[i].cinematic);
			uiInfo.teamList[i].cinematic = -1;
		}
		if (key == K_MOUSE2 || key == K_LEFTARROW) {
			i--;
		} else {
			i++;
		}
		if (i >= uiInfo.teamCount) {
			i = 0;
		} else if (i < 0) {
			i = uiInfo.teamCount - 1;
		}
		trap_Cvar_Set("ui_teamName", uiInfo.teamList[i].teamName);
		UI_HeadCountByTeam();
		UI_FeederSelection(FEEDER_HEADS, 0);
		updateModel = qtrue;
		return qtrue;
	}
	return qfalse;
}

static qboolean UI_GameType_HandleKey(int flags, float *special, int key, qboolean resetMap)
{
	//Makro - left/right support
	if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_ENTER || key == K_KP_ENTER || key == K_LEFTARROW
	    || key == K_RIGHTARROW) {
		int oldCount = UI_MapCountByGameType(qtrue);

		// hard coded mess here
		if (key == K_MOUSE2 || key == K_LEFTARROW) {
			ui_gameType.integer--;
			if (ui_gameType.integer == 2) {
				ui_gameType.integer = 1;
			} else if (ui_gameType.integer < 2) {
				ui_gameType.integer = uiInfo.numGameTypes - 1;
			}
		} else {
			ui_gameType.integer++;
			if (ui_gameType.integer >= uiInfo.numGameTypes) {
				ui_gameType.integer = 1;
			} else if (ui_gameType.integer == 2) {
				ui_gameType.integer = 3;
			}
		}

		if (uiInfo.gameTypes[ui_gameType.integer].gtEnum == GT_TOURNAMENT) {
			trap_Cvar_Set("ui_Q3Model", "1");
		} else {
			trap_Cvar_Set("ui_Q3Model", "0");
		}

		trap_Cvar_Set("ui_gameType", va("%d", ui_gameType.integer));
		UI_SetCapFragLimits(qtrue);
		UI_LoadBestScores(uiInfo.mapList[ui_currentMap.integer].mapLoadName,
				  uiInfo.gameTypes[ui_gameType.integer].gtEnum);
		if (resetMap && oldCount != UI_MapCountByGameType(qtrue)) {
			trap_Cvar_Set("ui_currentMap", "0");
			Menu_SetFeederSelection(NULL, FEEDER_MAPS, 0, NULL);
		}
		return qtrue;
	}
	return qfalse;
}

static qboolean UI_NetGameType_HandleKey(int flags, float *special, int key)
{
	//Makro - left/right support
	if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_ENTER || key == K_KP_ENTER || key == K_LEFTARROW
	    || key == K_RIGHTARROW) {

		if (key == K_MOUSE2 || key == K_LEFTARROW) {
			ui_netGameType.integer--;
		} else {
			ui_netGameType.integer++;
		}

		if (ui_netGameType.integer < 0) {
			ui_netGameType.integer = uiInfo.numGameTypes - 1;
		} else if (ui_netGameType.integer >= uiInfo.numGameTypes) {
			ui_netGameType.integer = 0;
		}

		trap_Cvar_Set("ui_netGameType", va("%d", ui_netGameType.integer));
		trap_Cvar_Set("ui_actualnetGameType", va("%d", uiInfo.gameTypes[ui_netGameType.integer].gtEnum));
		trap_Cvar_Set("ui_currentNetMap", "0");

		UI_MapCountByGameType(qfalse);
		Menu_SetFeederSelection(NULL, FEEDER_ALLMAPS, 0, NULL);
		return qtrue;
	}
	return qfalse;
}

static qboolean UI_JoinGameType_HandleKey(int flags, float *special, int key)
{
	//Makro - left/right support
	if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_ENTER || key == K_KP_ENTER || key == K_LEFTARROW
	    || key == K_RIGHTARROW) {

		if (key == K_MOUSE2 || key == K_LEFTARROW) {
			ui_joinGameType.integer--;
		} else {
			ui_joinGameType.integer++;
		}

		if (ui_joinGameType.integer < 0) {
			ui_joinGameType.integer = uiInfo.numJoinGameTypes - 1;
		} else if (ui_joinGameType.integer >= uiInfo.numJoinGameTypes) {
			ui_joinGameType.integer = 0;
		}

		trap_Cvar_Set("ui_joinGameType", va("%d", ui_joinGameType.integer));
		UI_BuildServerDisplayList(qtrue);
		return qtrue;
	}
	return qfalse;
}

static qboolean UI_Skill_HandleKey(int flags, float *special, int key)
{
	//Makro - left/right support
	if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_ENTER || key == K_KP_ENTER || key == K_LEFTARROW
	    || key == K_RIGHTARROW || key == K_HOME || key == K_END) {
		int i = trap_Cvar_VariableValue("g_spSkill");

		switch (key) {
		case K_HOME:
			i = 1;
			break;
		case K_END:
			i = numSkillLevels;
			break;
		case K_MOUSE2:
		case K_LEFTARROW:
			i--;
			break;
		default:
			i++;
			break;
		}

		if (i < 1) {
			i = numSkillLevels;
		} else if (i > numSkillLevels) {
			i = 1;
		}

		trap_Cvar_Set("g_spSkill", va("%i", i));
		return qtrue;
	}
	return qfalse;
}

static qboolean UI_TeamName_HandleKey(int flags, float *special, int key, qboolean blue)
{
	//Makro - left/right support
	if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_ENTER || key == K_KP_ENTER || key == K_LEFTARROW
	    || key == K_RIGHTARROW) {
		int i;

		i = UI_TeamIndexFromName(UI_Cvar_VariableString((blue) ? "ui_blueTeam" : "ui_redTeam"));

		if (key == K_MOUSE2 || key == K_LEFTARROW) {
			i--;
		} else {
			i++;
		}

		if (i >= uiInfo.teamCount) {
			i = 0;
		} else if (i < 0) {
			i = uiInfo.teamCount - 1;
		}

		trap_Cvar_Set((blue) ? "ui_blueTeam" : "ui_redTeam", uiInfo.teamList[i].teamName);

		return qtrue;
	}
	return qfalse;
}

static qboolean UI_TeamMember_HandleKey(int flags, float *special, int key, qboolean blue, int num)
{
	//Makro - left/right support
	if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_ENTER || key == K_KP_ENTER || key == K_LEFTARROW
	    || key == K_RIGHTARROW || key == K_HOME || key == K_END) {
		// 0 - None
		// 1 - Human
		// 2..NumCharacters - Bot
		char *cvar = va(blue ? "ui_blueteam%i" : "ui_redteam%i", num);
		int value = trap_Cvar_VariableValue(cvar);

		switch (key) {
		case K_HOME:
			value = 0;
			break;
		case K_END:
			//Makro - support for adding a random bot; changed 2 to 3
			value = UI_GetNumBots() + 3 - 1;
			break;
		case K_MOUSE2:
		case K_LEFTARROW:
			value--;
			break;
		default:
			value++;
			break;
		}

//Makro - using bot list instead of character list
/*
		if (ui_actualNetGameType.integer >= GT_TEAM) {
			if (value >= uiInfo.characterCount + 2) {
				value = 0;
			} else if (value < 0) {
				value = uiInfo.characterCount + 2 - 1;
			}
		} else {
*/
		//Makro - support for adding a random bot; changed 2 to 3
		if (value >= UI_GetNumBots() + 3) {
			value = 0;
		} else if (value < 0) {
			value = UI_GetNumBots() + 3 - 1;
		}
//              }

		trap_Cvar_Set(cvar, va("%i", value));
		return qtrue;
	}
	return qfalse;
}

static qboolean UI_NetSource_HandleKey(int flags, float *special, int key)
{
	//Makro - left/right support
	if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_ENTER || key == K_KP_ENTER || key == K_LEFTARROW
	    || key == K_RIGHTARROW) {

		if (key == K_MOUSE2 || key == K_LEFTARROW) {
			ui_netSource.integer--;
			if (ui_netSource.integer == AS_MPLAYER)
				ui_netSource.integer--;
		} else {
			ui_netSource.integer++;
			if (ui_netSource.integer == AS_MPLAYER)
				ui_netSource.integer++;
		}

		if (ui_netSource.integer >= numNetSources) {
			ui_netSource.integer = 0;
		} else if (ui_netSource.integer < 0) {
			ui_netSource.integer = numNetSources - 1;
		}

		UI_BuildServerDisplayList(qtrue);
		if (ui_netSource.integer != AS_GLOBAL) {
			UI_StartServerRefresh(qtrue);
		}
		trap_Cvar_Set("ui_netSource", va("%d", ui_netSource.integer));
		return qtrue;
	}
	return qfalse;
}

static qboolean UI_NetFilter_HandleKey(int flags, float *special, int key)
{
	//Makro - left/right support
	if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_ENTER || key == K_KP_ENTER || key == K_LEFTARROW
	    || key == K_RIGHTARROW) {

		if (key == K_MOUSE2 || key == K_LEFTARROW) {
			ui_serverFilterType.integer--;
		} else {
			ui_serverFilterType.integer++;
		}

		if (ui_serverFilterType.integer >= numServerFilters) {
			ui_serverFilterType.integer = 0;
		} else if (ui_serverFilterType.integer < 0) {
			ui_serverFilterType.integer = numServerFilters - 1;
		}

		UI_BuildServerDisplayList(qtrue);
		return qtrue;
	}
	return qfalse;
}

static qboolean UI_OpponentName_HandleKey(int flags, float *special, int key)
{
	//Makro - left/right support
	if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_ENTER || key == K_KP_ENTER || key == K_LEFTARROW
	    || key == K_RIGHTARROW) {
		if (key == K_MOUSE2 || key == K_LEFTARROW) {
			UI_PriorOpponent();
		} else {
			UI_NextOpponent();
		}
		return qtrue;
	}
	return qfalse;
}

static qboolean UI_BotName_HandleKey(int flags, float *special, int key)
{
	//Makro - left/right support
	if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_ENTER || key == K_KP_ENTER || key == K_LEFTARROW
	    || key == K_RIGHTARROW) {
		//int game = trap_Cvar_VariableValue("g_gametype");
		int value = uiInfo.botIndex;

		if (key == K_MOUSE2 || key == K_LEFTARROW) {
			value--;
		} else {
			value++;
		}

//Makro - using bot list instead of character list
/*
		if (game >= GT_TEAM) {
			if (value >= uiInfo.characterCount + 2) {
				value = 0;
			} else if (value < 0) {
				value = uiInfo.characterCount + 2 - 1;
			}
		} else {
*/
		//Makro - max value isn't UI_GetNumBots() + 2, it's just UI_GetNumBots()
		if (value >= UI_GetNumBots()) {
			value = 0;
		} else if (value < 0) {
			value = UI_GetNumBots() - 1;
		}
//              }
		uiInfo.botIndex = value;
		return qtrue;
	}
	return qfalse;
}

static qboolean UI_BotSkill_HandleKey(int flags, float *special, int key)
{
	//Makro - left/right support
	if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_ENTER || key == K_KP_ENTER || key == K_LEFTARROW
	    || key == K_RIGHTARROW || key == K_HOME || key == K_END) {

		switch (key) {
		case K_HOME:
			uiInfo.skillIndex = 0;
			break;
		case K_END:
			uiInfo.skillIndex = numSkillLevels - 1;
			break;
		case K_MOUSE2:
		case K_LEFTARROW:
			uiInfo.skillIndex--;
			break;
		default:
			uiInfo.skillIndex++;
			break;
		}

		if (uiInfo.skillIndex >= numSkillLevels) {
			uiInfo.skillIndex = 0;
		} else if (uiInfo.skillIndex < 0) {
			uiInfo.skillIndex = numSkillLevels - 1;
		}
		return qtrue;
	}
	return qfalse;
}

static qboolean UI_RedBlue_HandleKey(int flags, float *special, int key)
{
	//Makro - left/right support
	if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_ENTER || key == K_KP_ENTER || key == K_LEFTARROW
	    || key == K_RIGHTARROW) {
		uiInfo.redBlue ^= 1;
		return qtrue;
	}
	return qfalse;
}

static qboolean UI_Crosshair_HandleKey(int flags, float *special, int key)
{
	//Makro - left/right support
	if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_ENTER || key == K_KP_ENTER || key == K_LEFTARROW
	    || key == K_RIGHTARROW) {
		if (key == K_MOUSE2 || key == K_LEFTARROW) {
			uiInfo.currentCrosshair--;
		} else {
			uiInfo.currentCrosshair++;
		}

		if (uiInfo.currentCrosshair >= NUM_CROSSHAIRS) {
			uiInfo.currentCrosshair = 0;
		} else if (uiInfo.currentCrosshair < 0) {
			uiInfo.currentCrosshair = NUM_CROSSHAIRS - 1;
		}

		trap_Cvar_Set("cg_drawCrosshair", va("%d", uiInfo.currentCrosshair));

		return qtrue;
	}
	return qfalse;
}

//Makro - added for the SSG crosshair
static qboolean UI_SSG_Crosshair_HandleKey(int flags, float *special, int key)
{
	//Makro - left/right support
	if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_ENTER || key == K_KP_ENTER || key == K_LEFTARROW
	    || key == K_RIGHTARROW) {
		int current = (int) trap_Cvar_VariableValue("cg_RQ3_ssgCrosshair") % NUM_SSGCROSSHAIRS, offset = 1;

		if (key == K_MOUSE2 || key == K_LEFTARROW) {
			offset = -1;
		}
		current += offset;

		if (current < 0)
			current = NUM_SSGCROSSHAIRS - 1;
		else if (current >= NUM_SSGCROSSHAIRS)
			current = 0;

		trap_Cvar_SetValue("cg_RQ3_ssgCrosshair", (float) current);

		uiInfo.uiDC.Assets.SSGcrosshairShader = trap_R_RegisterShaderNoMip(va("gfx/rq3_hud/ssg2x-%i", current));

		return qtrue;
	}
	return qfalse;
}

static qboolean UI_SelectedPlayer_HandleKey(int flags, float *special, int key)
{
	//Makro - left/right support
	if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_ENTER || key == K_KP_ENTER || key == K_LEFTARROW
	    || key == K_RIGHTARROW) {
		int selected;

		UI_BuildPlayerList();
		if (!uiInfo.teamLeader) {
			return qfalse;
		}
		selected = trap_Cvar_VariableValue("cg_selectedPlayer");

		if (key == K_MOUSE2 || key == K_LEFTARROW) {
			selected--;
		} else {
			selected++;
		}

		if (selected > uiInfo.myTeamCount) {
			selected = 0;
		} else if (selected < 0) {
			selected = uiInfo.myTeamCount;
		}

		if (selected == uiInfo.myTeamCount) {
			trap_Cvar_Set("cg_selectedPlayerName", "Everyone");
		} else {
			trap_Cvar_Set("cg_selectedPlayerName", uiInfo.teamNames[selected]);
		}
		trap_Cvar_Set("cg_selectedPlayer", va("%d", selected));
	}
	return qfalse;
}

//Makro - replacement type
static qboolean UI_ReplacementType_HandleKey(int flags, float *special, int key)
{
	if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_ENTER || key == K_KP_ENTER || key == K_LEFTARROW
	    || key == K_RIGHTARROW) {
		int index = uiInfo.replacements.TypeIndex;

		if (key == K_MOUSE2 || key == K_LEFTARROW) {
			index--;
		} else {
			index++;
		}

		if (index >= replacementTypeCount) {
			index = 0;
		} else if (index < 0) {
			index = replacementTypeCount - 1;
		}
		uiInfo.replacements.TypeIndex = index;
		uiInfo.replacements.SubtypeIndex = 0;
		switch (index)
		{
			case 0:
				UI_BuildReplacementList(replacementWeapons[0].cvarName);
				UI_LoadReplacement(uiInfo.replacements.Index);
				break;
			case 1:
				UI_BuildReplacementList(replacementItems[0].cvarName);
				UI_LoadReplacement(uiInfo.replacements.Index);
				break;
			case 2:
				UI_BuildReplacementList(replacementAmmo[0].cvarName);
				UI_LoadReplacement(uiInfo.replacements.Index);
				break;
			default:
				break;
		}
	}
	return qfalse;
}

static qboolean UI_ReplacementSubType_HandleKey(int flags, float *special, int key)
{
	if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_ENTER || key == K_KP_ENTER || key == K_LEFTARROW
	    || key == K_RIGHTARROW) {
		int index = uiInfo.replacements.SubtypeIndex, max;

		if (key == K_MOUSE2 || key == K_LEFTARROW) {
			index--;
		} else {
			index++;
		}

		switch (uiInfo.replacements.TypeIndex%replacementTypeCount)
		{
			case 0:
				max = replacementWeapCount;
				break;
			case 1:
				max = replacementItemCount;
				break;
			case 2:
				max = replacementAmmoCount;
				break;
			default:
				max = replacementWeapCount;
				break;
		}

		if (index >= max) {
			index = 0;
		} else if (index < 0) {
			index = max - 1;
		}

		uiInfo.replacements.SubtypeIndex = index;
		switch (uiInfo.replacements.TypeIndex)
		{
			case 0:
				UI_BuildReplacementList(replacementWeapons[index].cvarName);
				UI_LoadReplacement(uiInfo.replacements.Index);
				break;
			case 1:
				UI_BuildReplacementList(replacementItems[index].cvarName);
				UI_LoadReplacement(uiInfo.replacements.Index);
				break;
			case 2:
				UI_BuildReplacementList(replacementAmmo[index].cvarName);
				UI_LoadReplacement(uiInfo.replacements.Index);
				break;
			default:
				break;
		}
	}

	return qfalse;
}

static qboolean UI_OwnerDrawHandleKey(int ownerDraw, int flags, float *special, int key)
{
	switch (ownerDraw) {
	case UI_HANDICAP:
		return UI_Handicap_HandleKey(flags, special, key);
		break;
	case UI_EFFECTS:
		return UI_Effects_HandleKey(flags, special, key);
		break;
	case UI_CLANNAME:
		return UI_ClanName_HandleKey(flags, special, key);
		break;
	case UI_GAMETYPE:
		return UI_GameType_HandleKey(flags, special, key, qtrue);
		break;
	case UI_NETGAMETYPE:
		return UI_NetGameType_HandleKey(flags, special, key);
		break;
	case UI_JOINGAMETYPE:
		return UI_JoinGameType_HandleKey(flags, special, key);
		break;
	case UI_SKILL:
		return UI_Skill_HandleKey(flags, special, key);
		break;
	case UI_BLUETEAMNAME:
		return UI_TeamName_HandleKey(flags, special, key, qtrue);
		break;
	case UI_REDTEAMNAME:
		return UI_TeamName_HandleKey(flags, special, key, qfalse);
		break;
	case UI_BLUETEAM1:
	case UI_BLUETEAM2:
	case UI_BLUETEAM3:
	case UI_BLUETEAM4:
	case UI_BLUETEAM5:
		UI_TeamMember_HandleKey(flags, special, key, qtrue, ownerDraw - UI_BLUETEAM1 + 1);
		break;
	case UI_REDTEAM1:
	case UI_REDTEAM2:
	case UI_REDTEAM3:
	case UI_REDTEAM4:
	case UI_REDTEAM5:
		UI_TeamMember_HandleKey(flags, special, key, qfalse, ownerDraw - UI_REDTEAM1 + 1);
		break;
	case UI_NETSOURCE:
		UI_NetSource_HandleKey(flags, special, key);
		break;
	case UI_NETFILTER:
		UI_NetFilter_HandleKey(flags, special, key);
		break;
	case UI_OPPONENT_NAME:
		UI_OpponentName_HandleKey(flags, special, key);
		break;
	case UI_BOTNAME:
		return UI_BotName_HandleKey(flags, special, key);
		break;
	case UI_BOTSKILL:
		return UI_BotSkill_HandleKey(flags, special, key);
		break;
	case UI_REDBLUE:
		UI_RedBlue_HandleKey(flags, special, key);
		break;
	case UI_CROSSHAIR:
		UI_Crosshair_HandleKey(flags, special, key);
		break;
	//Makro - for the SSG crosshair
	case UI_SSG_CROSSHAIR:
		UI_SSG_Crosshair_HandleKey(flags, special, key);
		break;
	//Makro - replacement type
	case UI_RQ3_REPLACEMENTTYPE:
		UI_ReplacementType_HandleKey(flags, special, key);
		break;
	//Makro - replacement subtype
	case UI_RQ3_REPLACEMENTSUBTYPE:
		UI_ReplacementSubType_HandleKey(flags, special, key);
		break;
	case UI_SELECTEDPLAYER:
		UI_SelectedPlayer_HandleKey(flags, special, key);
		break;
	default:
		break;
	}

	return qfalse;
}

static float UI_GetValue(int ownerDraw)
{
	return 0;
}

/*
=================
UI_ServersQsortCompare
=================
*/
static int QDECL UI_ServersQsortCompare(const void *arg1, const void *arg2)
{
	return trap_LAN_CompareServers(ui_netSource.integer, uiInfo.serverStatus.sortKey, uiInfo.serverStatus.sortDir,
				       *(int *) arg1, *(int *) arg2);
}

/*
=================
UI_ServersSort
=================
*/
void UI_ServersSort(int column, qboolean force)
{

	if (!force) {
		if (uiInfo.serverStatus.sortKey == column) {
			return;
		}
	}

	uiInfo.serverStatus.sortKey = column;
	qsort(&uiInfo.serverStatus.displayServers[0], uiInfo.serverStatus.numDisplayServers, sizeof(int),
	      UI_ServersQsortCompare);
}

/*
static void UI_StartSinglePlayer() {
	int i,j, k, skill;
	char buff[1024];
	i = trap_Cvar_VariableValue( "ui_currentTier" );
  if (i < 0 || i >= tierCount) {
    i = 0;
  }
	j = trap_Cvar_VariableValue("ui_currentMap");
	if (j < 0 || j > MAPS_PER_TIER) {
		j = 0;
	}

 	trap_Cvar_SetValue( "singleplayer", 1 );
 	trap_Cvar_SetValue( "g_gametype", Com_Clamp( 0, 7, tierList[i].gameTypes[j] ) );
	trap_Cmd_ExecuteText( EXEC_APPEND, va( "wait ; wait ; map %s\n", tierList[i].maps[j] ) );
	skill = trap_Cvar_VariableValue( "g_spSkill" );

	if (j == MAPS_PER_TIER-1) {
		k = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_opponentName"));
		Com_sprintf( buff, sizeof(buff), "wait ; addbot %s %i %s 250 %s\n", UI_AIFromName(teamList[k].teamMembers[0]), skill, "", teamList[k].teamMembers[0]);
	} else {
		k = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_opponentName"));
		for (i = 0; i < PLAYERS_PER_TEAM; i++) {
			Com_sprintf( buff, sizeof(buff), "wait ; addbot %s %i %s 250 %s\n", UI_AIFromName(teamList[k].teamMembers[i]), skill, "Blue", teamList[k].teamMembers[i]);
			trap_Cmd_ExecuteText( EXEC_APPEND, buff );
		}

		k = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_teamName"));
		for (i = 1; i < PLAYERS_PER_TEAM; i++) {
			Com_sprintf( buff, sizeof(buff), "wait ; addbot %s %i %s 250 %s\n", UI_AIFromName(teamList[k].teamMembers[i]), skill, "Red", teamList[k].teamMembers[i]);
			trap_Cmd_ExecuteText( EXEC_APPEND, buff );
		}
		trap_Cmd_ExecuteText( EXEC_APPEND, "wait 5; team Red\n" );
	}
	

}
*/

/*
===============
UI_LoadMods
===============
*/
static void UI_LoadMods()
{
	int numdirs;
	char dirlist[2048];
	char *dirptr;
	char *descptr;
	int i;
	int dirlen;

	uiInfo.modCount = 0;
	numdirs = trap_FS_GetFileList("$modlist", "", dirlist, sizeof(dirlist));
	dirptr = dirlist;
	for (i = 0; i < numdirs; i++) {
		dirlen = strlen(dirptr) + 1;
		descptr = dirptr + dirlen;
		uiInfo.modList[uiInfo.modCount].modName = String_Alloc(dirptr);
		uiInfo.modList[uiInfo.modCount].modDescr = String_Alloc(descptr);
		dirptr += dirlen + strlen(descptr) + 1;
		uiInfo.modCount++;
		if (uiInfo.modCount >= MAX_MODS) {
			break;
		}
	}

}

/*
===============
UI_LoadTeams
===============
*/
static void UI_LoadTeams()
{
	char teamList[4096];
	char *teamName;
	int i, len, count;

	count = trap_FS_GetFileList("", "team", teamList, 4096);

	if (count) {
		teamName = teamList;
		for (i = 0; i < count; i++) {
			len = strlen(teamName);
			UI_ParseTeamInfo(teamName);
			teamName += len + 1;
		}
	}

}

/*
===============
UI_LoadMovies
===============
*/
static void UI_LoadMovies()
{
	char movielist[4096];
	char *moviename;
	int i, len;

	uiInfo.movieCount = trap_FS_GetFileList("video", "roq", movielist, 4096);

	if (uiInfo.movieCount) {
		if (uiInfo.movieCount > MAX_MOVIES) {
			uiInfo.movieCount = MAX_MOVIES;
		}
		moviename = movielist;
		for (i = 0; i < uiInfo.movieCount; i++) {
			len = strlen(moviename);
			if (!Q_stricmp(moviename + len - 4, ".roq")) {
				moviename[len - 4] = '\0';
			}
			Q_strupr(moviename);
			uiInfo.movieList[i] = String_Alloc(moviename);
			moviename += len + 1;
		}
	}

}

/*
===============
UI_LoadDemos
===============
*/
static const int q3Protocols[] = {66, 67, 68};
static const char *q3Versions[] = {"1.30", "1.31", "1.32"};
static const int q3VersionCount = sizeof(q3Protocols)/sizeof(q3Protocols[0]);

const char *q3VersionFromProtocol(int protocol)
{
	int i;

	for (i=0; i<q3VersionCount; i++)
	{
		if (protocol == q3Protocols[i])
			return q3Versions[i];
	}
	return q3Versions[q3VersionCount-1];
}

int q3ProtocolFromVersion(const char *version)
{
	int i;

	for (i=0; i<q3VersionCount; i++)
	{
		if (!Q_stricmp(version, q3Versions[i]))
			return q3Protocols[i];
	}
	return q3Protocols[q3VersionCount-1];
}

void UI_SortDemoList(int start, int end, int column)
{
	int i, j;
	for (i=start; i<end-1; i++)
	{
		for (j=i+1; j<end; j++)
		{
			qboolean swap;
			//sort list alphabetically
			if (column == 0)
				swap = (Q_stricmp(uiInfo.demoList[i], uiInfo.demoList[j]) > 0);
			//sort by q3 version
			else
				swap = (uiInfo.demoType[i] - uiInfo.demoType[j] > 0);

			if (swap)
			{
				int tmp;
				const char *tmpstr;

				tmpstr = uiInfo.demoList[i];
				tmp = uiInfo.demoType[i];
				uiInfo.demoList[i] = uiInfo.demoList[j];
				uiInfo.demoType[i] = uiInfo.demoType[j];
				uiInfo.demoList[j] = tmpstr;
				uiInfo.demoType[j] = tmp;
			}
		}
	}
}

static void UI_LoadDemos()
{
	char demolist[4096];
	char demoExt[32];
	char *demoname;
	int i, j, len, protocol = (int) trap_Cvar_VariableValue("protocol");

	uiInfo.demoCount = 0;
	//Makro - old code was using just the "protocol" cvar; replaced with a for loop
	for (j=66; j<=protocol; j++)
	{
		int count;
		//Com_sprintf(demoExt, sizeof(demoExt), "dm_%d", (int) trap_Cvar_VariableValue("protocol"));
		Com_sprintf(demoExt, sizeof(demoExt), "dm_%d", j);

		count = trap_FS_GetFileList("demos", demoExt, demolist, 4096);

		//Com_sprintf(demoExt, sizeof(demoExt), ".dm_%d", (int) trap_Cvar_VariableValue("protocol"));
		Com_sprintf(demoExt, sizeof(demoExt), ".dm_%d", j);

		if (count) {
			//int start = uiInfo.demoCount+1;
			//uiInfo.demoList[uiInfo.demoCount++] = String_Alloc(va("*** Recorded with Quake 3 %s ***", q3VersionFromProtocol(j)));
			demoname = demolist;
			for (i = 0; i < count && uiInfo.demoCount <= MAX_DEMOS; i++)
			{
				len = strlen(demoname);
				if (!Q_stricmp(demoname + len - strlen(demoExt), demoExt))
				{
					demoname[len - strlen(demoExt)] = '\0';
				}
				//Makro - bad for linux users
				//Q_strupr(demoname);
				uiInfo.demoType[uiInfo.demoCount] = j;
				//uiInfo.demoList[uiInfo.demoCount++] = String_Alloc(va("%s (%s)", demoname, q3VersionFromProtocol(j)));
				uiInfo.demoList[uiInfo.demoCount++] = String_Alloc(demoname);
				demoname += len + 1;
			}
		}
	}
	UI_SortDemoList(0, uiInfo.demoCount, 0);
}

static qboolean UI_SetNextMap(int actual, int index)
{
	int i;

	for (i = actual + 1; i < uiInfo.mapCount; i++) {
		if (uiInfo.mapList[i].active) {
			Menu_SetFeederSelection(NULL, FEEDER_MAPS, index + 1, "skirmish");
			return qtrue;
		}
	}
	return qfalse;
}

static void UI_StartSkirmish(qboolean next)
{
	int i, k, g, delay, temp;
	float skill;
	char buff[MAX_STRING_CHARS];

	if (next) {
		int actual;
		int index = trap_Cvar_VariableValue("ui_mapIndex");

		UI_MapCountByGameType(qtrue);
		UI_SelectedMap(index, &actual);
		if (UI_SetNextMap(actual, index)) {
		} else {
			UI_GameType_HandleKey(0, 0, K_MOUSE1, qfalse);
			UI_MapCountByGameType(qtrue);
			Menu_SetFeederSelection(NULL, FEEDER_MAPS, 0, "skirmish");
		}
	}

	g = uiInfo.gameTypes[ui_gameType.integer].gtEnum;
	trap_Cvar_SetValue("g_gametype", g);
	trap_Cmd_ExecuteText(EXEC_APPEND,
			     va("wait ; wait ; map %s\n", uiInfo.mapList[ui_currentMap.integer].mapLoadName));
	skill = trap_Cvar_VariableValue("g_spSkill");
	trap_Cvar_Set("ui_scoreMap", uiInfo.mapList[ui_currentMap.integer].mapName);

	k = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_opponentName"));

	trap_Cvar_Set("ui_singlePlayerActive", "1");

	// set up sp overrides, will be replaced on postgame
	temp = trap_Cvar_VariableValue("capturelimit");
	trap_Cvar_Set("ui_saveCaptureLimit", va("%i", temp));
	temp = trap_Cvar_VariableValue("fraglimit");
	trap_Cvar_Set("ui_saveFragLimit", va("%i", temp));

	UI_SetCapFragLimits(qfalse);

	temp = trap_Cvar_VariableValue("cg_drawTimer");
	trap_Cvar_Set("ui_drawTimer", va("%i", temp));
	temp = trap_Cvar_VariableValue("g_doWarmup");
	trap_Cvar_Set("ui_doWarmup", va("%i", temp));
	temp = trap_Cvar_VariableValue("g_friendlyFire");
	trap_Cvar_Set("ui_friendlyFire", va("%i", temp));
	temp = trap_Cvar_VariableValue("sv_maxClients");
	trap_Cvar_Set("ui_maxClients", va("%i", temp));
	temp = trap_Cvar_VariableValue("g_warmup");
	trap_Cvar_Set("ui_Warmup", va("%i", temp));
	temp = trap_Cvar_VariableValue("sv_pure");
	trap_Cvar_Set("ui_pure", va("%i", temp));

	trap_Cvar_Set("cg_cameraOrbit", "0");
	trap_Cvar_Set("cg_thirdPerson", "0");
	trap_Cvar_Set("cg_drawTimer", "1");
	trap_Cvar_Set("g_doWarmup", "1");
	trap_Cvar_Set("g_warmup", "15");
	trap_Cvar_Set("sv_pure", "0");
	trap_Cvar_Set("g_friendlyFire", "0");
	trap_Cvar_Set("g_redTeam", UI_Cvar_VariableString("ui_teamName"));
	trap_Cvar_Set("g_blueTeam", UI_Cvar_VariableString("ui_opponentName"));

	if (trap_Cvar_VariableValue("ui_recordSPDemo")) {
		Com_sprintf(buff, MAX_STRING_CHARS, "%s_%i", uiInfo.mapList[ui_currentMap.integer].mapLoadName, g);
		trap_Cvar_Set("ui_recordSPDemoName", buff);
	}

	delay = 500;

	if (g == GT_TOURNAMENT) {
		trap_Cvar_Set("sv_maxClients", "2");
		Com_sprintf(buff, sizeof(buff), "wait ; addbot %s %f " ", %i \n",
			    uiInfo.mapList[ui_currentMap.integer].opponentName, skill, delay);
		trap_Cmd_ExecuteText(EXEC_APPEND, buff);
	} else {
		temp = uiInfo.mapList[ui_currentMap.integer].teamMembers * 2;
		trap_Cvar_Set("sv_maxClients", va("%d", temp));
		for (i = 0; i < uiInfo.mapList[ui_currentMap.integer].teamMembers; i++) {
			Com_sprintf(buff, sizeof(buff), "addbot %s %f %s %i %s\n",
				    UI_AIFromName(uiInfo.teamList[k].teamMembers[i]), skill,
				    (g == GT_FFA) ? "" : "Blue", delay, uiInfo.teamList[k].teamMembers[i]);
			trap_Cmd_ExecuteText(EXEC_APPEND, buff);
			delay += 500;
		}
		k = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_teamName"));
		for (i = 0; i < uiInfo.mapList[ui_currentMap.integer].teamMembers - 1; i++) {
			Com_sprintf(buff, sizeof(buff), "addbot %s %f %s %i %s\n",
				    UI_AIFromName(uiInfo.teamList[k].teamMembers[i]), skill, (g == GT_FFA) ? "" : "Red",
				    delay, uiInfo.teamList[k].teamMembers[i]);
			trap_Cmd_ExecuteText(EXEC_APPEND, buff);
			delay += 500;
		}
	}
	if (g >= GT_TEAM) {
		trap_Cmd_ExecuteText(EXEC_APPEND, "wait 5; team Red\n");
	}
}

static void UI_Update(const char *name)
{
	int val = trap_Cvar_VariableValue(name);

	if (Q_stricmp(name, "ui_SetName") == 0) {
		trap_Cvar_Set("name", UI_Cvar_VariableString("ui_Name"));
	} else if (Q_stricmp(name, "ui_setRate") == 0) {
		float rate = trap_Cvar_VariableValue("rate");

		if (rate >= 5000) {
			trap_Cvar_Set("cl_maxpackets", "30");
			trap_Cvar_Set("cl_packetdup", "1");
		} else if (rate >= 4000) {
			trap_Cvar_Set("cl_maxpackets", "15");
			trap_Cvar_Set("cl_packetdup", "2");	// favor less prediction errors when there's packet loss
		} else {
			trap_Cvar_Set("cl_maxpackets", "15");
			trap_Cvar_Set("cl_packetdup", "1");	// favor lower bandwidth
		}
	} else if (Q_stricmp(name, "ui_GetName") == 0) {
		trap_Cvar_Set("ui_Name", UI_Cvar_VariableString("name"));
	} else if (Q_stricmp(name, "r_colorbits") == 0) {
		switch (val) {
		case 0:
			trap_Cvar_SetValue("r_depthbits", 0);
			trap_Cvar_SetValue("r_stencilbits", 0);
			break;
		case 16:
			trap_Cvar_SetValue("r_depthbits", 16);
			trap_Cvar_SetValue("r_stencilbits", 0);
			break;
		case 32:
			trap_Cvar_SetValue("r_depthbits", 24);
			break;
		}
	} else if (Q_stricmp(name, "r_lodbias") == 0) {
		//TTI: minor changes
		switch (val) {
		case 0:
			trap_Cvar_SetValue("r_subdivisions", 4);
			trap_Cvar_SetValue("r_lodCurveError", 250);
			break;
		case 1:
			trap_Cvar_SetValue("r_subdivisions", 8);
			trap_Cvar_SetValue("r_lodCurveError", 250);
			break;
		case 2:
			trap_Cvar_SetValue("r_subdivisions", 16);
			trap_Cvar_SetValue("r_lodCurveError", 125);
			break;
		}
	} else if (Q_stricmp(name, "ui_glCustom") == 0) {
		switch (val) {
		//TTI: new presets
		case 0:	// high quality
			trap_Cvar_SetValue("com_blood", 1);
			trap_Cvar_SetValue("cg_gibs", 1);
			trap_Cvar_SetValue("cg_simpleItems", 0);
			trap_Cvar_SetValue("cg_marks", 1);
			trap_Cvar_SetValue("cg_brassTime", 30000);
			trap_Cvar_SetValue("cg_RQ3_glasstime", 30000);
			trap_Cvar_SetValue("cg_RQ3_flash", 1);
			trap_Cvar_SetValue("cg_RQ3_impactEffects", 1);
			trap_Cvar_SetValue("cg_shadows", 1);
			trap_Cvar_SetValue("r_inGameVideo", 1);
			trap_Cvar_SetValue("r_picmip", 0);
			trap_Cvar_SetValue("r_roundImagesDown", 0);
			trap_Cvar_SetValue("r_detailtextures", 1);
			trap_Cvar_SetValue("r_lodBias", 0);
			trap_Cvar_SetValue("r_swapInterval", 0);
			trap_Cvar_SetValue("r_subdivisions", 0);
			trap_Cvar_SetValue("r_lodCurveError", 10000);
			trap_Cvar_SetValue("r_vertexlight", 0);
			trap_Cvar_SetValue("r_colorbits", 32);
			trap_Cvar_SetValue("r_texturebits", 32);
			trap_Cvar_SetValue("r_stencilbits", 8);
			trap_Cvar_SetValue("r_depthbits", 24);
			trap_Cvar_SetValue("r_dynamiclight", 1);
			trap_Cvar_SetValue("r_drawSun", 1);
			trap_Cvar_SetValue("r_fastsky", 0);
			trap_Cvar_SetValue("r_flares", 1);
			trap_Cvar_Set("r_texturemode", "GL_LINEAR_MIPMAP_LINEAR");
			trap_Cvar_SetValue("r_ext_multitexture", 1);
			trap_Cvar_SetValue("r_ext_compressed_textures", 0);
			trap_Cvar_SetValue("r_ext_texture_filter_anisotropic", 1);
			trap_Cvar_SetValue("r_ext_max_anisotropy", 16);
			break;
		case 1:	// normal 
			trap_Cvar_SetValue("com_blood", 1);
			trap_Cvar_SetValue("cg_gibs", 1);
			trap_Cvar_SetValue("cg_simpleItems", 0);
			trap_Cvar_SetValue("cg_marks", 1);
			trap_Cvar_SetValue("cg_brassTime", 10000);
			trap_Cvar_SetValue("cg_RQ3_glasstime", 10000);
			trap_Cvar_SetValue("cg_RQ3_flash", 1);
			trap_Cvar_SetValue("cg_RQ3_impactEffects", 1);
			trap_Cvar_SetValue("cg_shadows", 1);
			trap_Cvar_SetValue("r_inGameVideo", 1);
			trap_Cvar_SetValue("r_picmip", 0);
			trap_Cvar_SetValue("r_roundImagesDown", 1);
			trap_Cvar_SetValue("r_detailtextures", 1);
			trap_Cvar_SetValue("r_lodBias", 0);
			trap_Cvar_SetValue("r_swapInterval", 0);
			trap_Cvar_SetValue("r_subdivisions", 4);
			trap_Cvar_SetValue("r_lodCurveError", 250);
			trap_Cvar_SetValue("r_vertexlight", 0);
			trap_Cvar_SetValue("r_colorbits", 32);
			trap_Cvar_SetValue("r_texturebits", 32);
			trap_Cvar_SetValue("r_stencilbits", 0);
			trap_Cvar_SetValue("r_depthbits", 24);
			trap_Cvar_SetValue("r_dynamiclight", 1);
			trap_Cvar_SetValue("r_drawSun", 0);
			trap_Cvar_SetValue("r_fastsky", 0);
			trap_Cvar_SetValue("r_flares", 1);
			trap_Cvar_Set("r_texturemode", "GL_LINEAR_MIPMAP_LINEAR");
			trap_Cvar_SetValue("r_ext_multitexture", 1);
			trap_Cvar_SetValue("r_ext_compressed_textures", 0);
			trap_Cvar_SetValue("r_ext_texture_filter_anisotropic", 1);
			trap_Cvar_SetValue("r_ext_max_anisotropy", 4);
			break;
		case 2:	// fast
			trap_Cvar_SetValue("com_blood", 1);
			trap_Cvar_SetValue("cg_gibs", 1);
			trap_Cvar_SetValue("cg_simpleItems", 0);
			trap_Cvar_SetValue("cg_marks", 1);
			trap_Cvar_SetValue("cg_brassTime", 2000);
			trap_Cvar_SetValue("cg_RQ3_glasstime", 2000);
			trap_Cvar_SetValue("cg_RQ3_flash", 1);
			trap_Cvar_SetValue("cg_RQ3_impactEffects", 0);
			trap_Cvar_SetValue("cg_shadows", 0);
			trap_Cvar_SetValue("r_inGameVideo", 1);
			trap_Cvar_SetValue("r_picmip", 1);
			trap_Cvar_SetValue("r_roundImagesDown", 1);
			trap_Cvar_SetValue("r_detailtextures", 1);
			trap_Cvar_SetValue("r_lodBias", 1);
			trap_Cvar_SetValue("r_swapInterval", 0);
			trap_Cvar_SetValue("r_subdivisions", 8);
			trap_Cvar_SetValue("r_lodCurveError", 250);
			trap_Cvar_SetValue("r_vertexlight", 0);
			trap_Cvar_SetValue("r_colorbits", 32);
			trap_Cvar_SetValue("r_texturebits", 32);
			trap_Cvar_SetValue("r_stencilbits", 0);
			trap_Cvar_SetValue("r_depthbits", 16);
			trap_Cvar_SetValue("r_dynamiclight", 1);
			trap_Cvar_SetValue("r_drawSun", 0);
			trap_Cvar_SetValue("r_fastsky", 0);
			trap_Cvar_SetValue("r_flares", 0);
			trap_Cvar_Set("r_texturemode", "GL_LINEAR_MIPMAP_LINEAR");
			trap_Cvar_SetValue("r_ext_multitexture", 1);
			trap_Cvar_SetValue("r_ext_compressed_textures", 1);
			trap_Cvar_SetValue("r_ext_texture_filter_anisotropic", 0);
			trap_Cvar_SetValue("r_ext_max_anisotropy", 2);
			break;
		case 3:	// fastest
			trap_Cvar_SetValue("com_blood", 0);
			trap_Cvar_SetValue("cg_gibs", 0);
			trap_Cvar_SetValue("cg_simpleItems", 1);
			trap_Cvar_SetValue("cg_marks", 0);
			trap_Cvar_SetValue("cg_brassTime", 0);
			trap_Cvar_SetValue("cg_RQ3_glasstime", 0);
			trap_Cvar_SetValue("cg_RQ3_flash", 0);
			trap_Cvar_SetValue("cg_RQ3_impactEffects", 0);
			trap_Cvar_SetValue("cg_shadows", 0);
			trap_Cvar_SetValue("r_inGameVideo", 1);
			trap_Cvar_SetValue("r_picmip", 2);
			trap_Cvar_SetValue("r_roundImagesDown", 2);
			trap_Cvar_SetValue("r_detailtextures", 0);
			trap_Cvar_SetValue("r_lodBias", 2);
			trap_Cvar_SetValue("r_swapInterval", 0);
			trap_Cvar_SetValue("r_subdivisions", 16);
			trap_Cvar_SetValue("r_lodCurveError", 125);
			trap_Cvar_SetValue("r_vertexlight", 0);
			trap_Cvar_SetValue("r_colorbits", 16);
			trap_Cvar_SetValue("r_texturebits", 16);
			trap_Cvar_SetValue("r_stencilbits", 0);
			trap_Cvar_SetValue("r_depthbits", 16);
			trap_Cvar_SetValue("r_dynamiclight", 0);
			trap_Cvar_SetValue("r_drawSun", 0);
			trap_Cvar_SetValue("r_fastsky", 1);
			trap_Cvar_SetValue("r_flares", 0);
			trap_Cvar_Set("r_texturemode", "GL_LINEAR_MIPMAP_NEAREST");
			trap_Cvar_SetValue("r_ext_multitexture", 0);
			trap_Cvar_SetValue("r_ext_compressed_textures", 1);
			trap_Cvar_SetValue("r_ext_texture_filter_anisotropic", 0);
			trap_Cvar_SetValue("r_ext_max_anisotropy", 2);
			break;
		}
	} else if (Q_stricmp(name, "ui_mousePitch") == 0) {
		if (val == 0) {
			trap_Cvar_SetValue("m_pitch", 0.022f);
		} else {
			trap_Cvar_SetValue("m_pitch", -0.022f);
		}
	}
}

static void UI_RunMenuScript(char **args)
{
	const char *name, *name2;
	char buff[1024];

	if (String_Parse(args, &name)) {
		if (Q_stricmp(name, "StartServer") == 0) {
			int i, clients, oldclients;
			float skill;

			trap_Cvar_Set("cg_thirdPerson", "0");
			trap_Cvar_Set("cg_cameraOrbit", "0");
			trap_Cvar_Set("ui_singlePlayerActive", "0");
			trap_Cvar_SetValue("dedicated", Com_Clamp(0, 2, ui_dedicated.integer));
			trap_Cvar_SetValue("g_gametype",
					   Com_Clamp(0, 8, uiInfo.gameTypes[ui_netGameType.integer].gtEnum));
			trap_Cvar_Set("g_redTeam", UI_Cvar_VariableString("ui_teamName"));
			trap_Cvar_Set("g_blueTeam", UI_Cvar_VariableString("ui_opponentName"));
			//Makro - client password
			if ((int) trap_Cvar_VariableValue("dedicated") == 0) {
				trap_Cvar_Set("password", UI_Cvar_VariableString("g_password"));
			}
			trap_Cmd_ExecuteText(EXEC_APPEND,
					     va("wait ; wait ; map %s\n",
						uiInfo.mapList[ui_currentNetMap.integer].mapLoadName));
			skill = trap_Cvar_VariableValue("g_spSkill");
			// set max clients based on spots
			oldclients = trap_Cvar_VariableValue("sv_maxClients");
			clients = 0;
			for (i = 0; i < PLAYERS_PER_TEAM; i++) {
				int bot = trap_Cvar_VariableValue(va("ui_blueteam%i", i + 1));

				if (bot >= 0) {
					clients++;
				}
				bot = trap_Cvar_VariableValue(va("ui_redteam%i", i + 1));
				if (bot >= 0) {
					clients++;
				}
			}
			if (clients == 0) {
				clients = 8;
			}

			if (oldclients > clients) {
				clients = oldclients;
			}

			trap_Cvar_Set("sv_maxClients", va("%d", clients));

			for (i = 0; i < PLAYERS_PER_TEAM; i++) {
				int bot = trap_Cvar_VariableValue(va("ui_blueteam%i", i + 1));

				//Makro - support for adding random bots; changed from 1 to 2
				if (bot > 2) {
					//Makro - using bot list instead of character list; new code below
					//if (ui_actualNetGameType.integer >= GT_TEAM) {
					//      Com_sprintf( buff, sizeof(buff), "addbot %s %f %s\n", uiInfo.characterList[bot-2].name, skill, "Blue");
					//} else {
					//      Com_sprintf( buff, sizeof(buff), "wait; addbot %s %f \n", UI_GetBotNameByNumber(bot-2), skill);
					//}
					if (ui_actualNetGameType.integer >= GT_TEAM) {
						//Makro - support for adding random bots; changed from 2 to 3
						Com_sprintf(buff, sizeof(buff), "addbot %s %f blue\n",
							    UI_GetBotNameByNumber(bot - 3), skill);
					} else {
						//Makro - support for adding random bots; changed from 2 to 3
						Com_sprintf(buff, sizeof(buff), "addbot %s %f \n",
							    UI_GetBotNameByNumber(bot - 3), skill);
					}
					trap_Cmd_ExecuteText(EXEC_APPEND, buff);
				} else if (bot == 2) {
					//Makro - support for adding random bots
					if (ui_actualNetGameType.integer >= GT_TEAM) {
						//Makro - support for adding random bots; changed from 2 to 3
						Com_sprintf(buff, sizeof(buff), "addbot %s %f blue\n",
							    UI_GetBotNameByNumber(rand() % UI_GetNumBots()), skill);
					} else {
						//Makro - support for adding random bots; changed from 2 to 3
						Com_sprintf(buff, sizeof(buff), "addbot %s %f \n",
							    UI_GetBotNameByNumber(rand() % UI_GetNumBots()), skill);
					}
					trap_Cmd_ExecuteText(EXEC_APPEND, buff);
				}
				bot = trap_Cvar_VariableValue(va("ui_redteam%i", i + 1));
				//Makro - support for adding random bots; changed from 1 to 2
				if (bot > 2) {
					//Makro - using bot list instead of character list; new code below
					//if (ui_actualNetGameType.integer >= GT_TEAM) {
					//      Com_sprintf( buff, sizeof(buff), "addbot %s %f %s\n", uiInfo.characterList[bot-2].name, skill, "Red");
					//} else {
					//      Com_sprintf( buff, sizeof(buff), "wait; addbot %s %f \n", UI_GetBotNameByNumber(bot-2), skill);
					//}
					if (ui_actualNetGameType.integer >= GT_TEAM) {
						//Makro - support for adding random bots; changed from 2 to 3
						Com_sprintf(buff, sizeof(buff), "addbot %s %f red\n",
							    UI_GetBotNameByNumber(bot - 3), skill);
					} else {
						//Makro - support for adding random bots; changed from 2 to 3
						Com_sprintf(buff, sizeof(buff), "addbot %s %f \n",
							    UI_GetBotNameByNumber(bot - 3), skill);
					}
					trap_Cmd_ExecuteText(EXEC_APPEND, buff);
				} else if (bot == 2) {
					//Makro - support for adding random bots
					if (ui_actualNetGameType.integer >= GT_TEAM) {
						//Makro - support for adding random bots; changed from 2 to 3
						Com_sprintf(buff, sizeof(buff), "addbot %s %f red\n",
							    UI_GetBotNameByNumber(rand() % UI_GetNumBots()), skill);
					} else {
						//Makro - support for adding random bots; changed from 2 to 3
						Com_sprintf(buff, sizeof(buff), "addbot %s %f \n",
							    UI_GetBotNameByNumber(rand() % UI_GetNumBots()), skill);
					}
					trap_Cmd_ExecuteText(EXEC_APPEND, buff);
				}
			}
		} else if (Q_stricmp(name, "updateSPMenu") == 0) {
			UI_SetCapFragLimits(qtrue);
			UI_MapCountByGameType(qtrue);
			ui_mapIndex.integer = UI_GetIndexFromSelection(ui_currentMap.integer);
			trap_Cvar_Set("ui_mapIndex", va("%d", ui_mapIndex.integer));
			Menu_SetFeederSelection(NULL, FEEDER_MAPS, ui_mapIndex.integer, "skirmish");
			UI_GameType_HandleKey(0, 0, K_MOUSE1, qfalse);
			UI_GameType_HandleKey(0, 0, K_MOUSE2, qfalse);
		} else if (Q_stricmp(name, "resetDefaults") == 0) {
			trap_Cmd_ExecuteText(EXEC_APPEND, "exec default.cfg\n");
			trap_Cmd_ExecuteText(EXEC_APPEND, "cvar_restart\n");
			Controls_SetDefaults();
			trap_Cvar_Set("com_introPlayed", "1");
			trap_Cmd_ExecuteText(EXEC_APPEND, "vid_restart\n");
		} else if (Q_stricmp(name, "getCDKey") == 0) {
			char out[17];

			trap_GetCDKey(buff, 17);
			trap_Cvar_Set("cdkey1", "");
			trap_Cvar_Set("cdkey2", "");
			trap_Cvar_Set("cdkey3", "");
			trap_Cvar_Set("cdkey4", "");
			if (strlen(buff) == CDKEY_LEN) {
				Q_strncpyz(out, buff, 5);
				trap_Cvar_Set("cdkey1", out);
				Q_strncpyz(out, buff + 4, 5);
				trap_Cvar_Set("cdkey2", out);
				Q_strncpyz(out, buff + 8, 5);
				trap_Cvar_Set("cdkey3", out);
				Q_strncpyz(out, buff + 12, 5);
				trap_Cvar_Set("cdkey4", out);
			}

		} else if (Q_stricmp(name, "verifyCDKey") == 0) {
			buff[0] = '\0';
			Q_strcat(buff, 1024, UI_Cvar_VariableString("cdkey1"));
			Q_strcat(buff, 1024, UI_Cvar_VariableString("cdkey2"));
			Q_strcat(buff, 1024, UI_Cvar_VariableString("cdkey3"));
			Q_strcat(buff, 1024, UI_Cvar_VariableString("cdkey4"));
			trap_Cvar_Set("cdkey", buff);
			if (trap_VerifyCDKey(buff, UI_Cvar_VariableString("cdkeychecksum"))) {
				trap_Cvar_Set("ui_cdkeyvalid", "CD Key Appears to be valid.");
				trap_SetCDKey(buff);
			} else {
				trap_Cvar_Set("ui_cdkeyvalid", "CD Key does not appear to be valid.");
			}
		//Makro - ref command - map
		} else if (Q_stricmp(name, "refMap") == 0) {
			if (ui_currentNetMap.integer >= 0 && ui_currentNetMap.integer < uiInfo.mapCount) {
				trap_Cmd_ExecuteText(EXEC_APPEND,
						     va("ref map %s\n",
							uiInfo.mapList[ui_currentNetMap.integer].mapLoadName));
			}
		//Makro - ref command - kick
		} else if (Q_stricmp(name, "refKick") == 0) {
			if (uiInfo.playerIndex >= 0 && uiInfo.playerIndex < uiInfo.playerCount) {
				trap_Cmd_ExecuteText(EXEC_APPEND,
						     va("ref kick %i\n", uiInfo.clientNums[uiInfo.playerIndex]));
			}
		//Makro - captain command - referee
		} else if (Q_stricmp(name, "captainRef") == 0) {
			if (uiInfo.playerIndex >= 0 && uiInfo.playerIndex < uiInfo.playerCount) {
				trap_Cmd_ExecuteText(EXEC_APPEND,
						     va("referee %i\n", uiInfo.clientNums[uiInfo.playerIndex]));
			}
		//Makro - ref login
		} else if (Q_stricmp(name, "refLogin") == 0) {
			trap_Cmd_ExecuteText(EXEC_APPEND, va("reflogin %s\n", ui_RQ3_refPassword.string));
		//Makro - read MM captain team settings
		} else if (Q_stricmp(name, "readMMcaptainSettings") == 0) {
			trap_Cvar_Set("ui_RQ3_teamName", "");
		//Makro - send the matchmode settings to the server
		} else if (Q_stricmp(name, "sendMMsettings") == 0) {
			trap_Cmd_ExecuteText(EXEC_APPEND, va("settings %i %i %i %i %i %i %i %i %i\n",
			ui_RQ3_timelimit.integer,
			ui_RQ3_roundlimit.integer,
			ui_RQ3_roundtimelimit.integer,
			ui_RQ3_fraglimit.integer,
			ui_RQ3_maxplayers.integer,
			ui_RQ3_forceteamtalk.integer,
			ui_RQ3_limchasecam.integer,
			ui_RQ3_tgren.integer,
			ui_RQ3_friendlyFire.integer));
		//Makro - captain command - teamname
		} else if (Q_stricmp(name, "captainSetTeamName") == 0) {
			trap_Cmd_ExecuteText(EXEC_APPEND, va("teamname \"%s\"\n", ui_RQ3_teamName.string));
		//Makro - captain command - teammodel
		} else if (Q_stricmp(name, "captainSetTeamModel") == 0) {
			trap_Cmd_ExecuteText(EXEC_APPEND, va("teammodel \"%s\"\n", ui_RQ3_teamModel.string));
		//Makro - sync ui MM cvars with the real ones
		} else if (Q_stricmp(name, "readMMsettings") == 0) {
			trap_Cvar_SetValue("ui_RQ3_timelimit", trap_Cvar_VariableValue("timelimit"));
			trap_Cvar_SetValue("ui_RQ3_roundlimit", trap_Cvar_VariableValue("cg_RQ3_roundlimit"));
			trap_Cvar_SetValue("ui_RQ3_roundtimelimit", trap_Cvar_VariableValue("cg_RQ3_roundtimelimit"));
			trap_Cvar_SetValue("ui_RQ3_fraglimit", trap_Cvar_VariableValue("fraglimit"));
			trap_Cvar_SetValue("ui_RQ3_maxplayers", trap_Cvar_VariableValue("cg_RQ3_maxplayers"));
			trap_Cvar_SetValue("ui_RQ3_forceteamtalk", trap_Cvar_VariableValue("cg_RQ3_forceteamtalk"));
			trap_Cvar_SetValue("ui_RQ3_limchasecam", trap_Cvar_VariableValue("cg_RQ3_limchasecam"));
			trap_Cvar_SetValue("ui_RQ3_tgren", trap_Cvar_VariableValue("cg_RQ3_tgren"));
			trap_Cvar_SetValue("ui_RQ3_friendlyFire", trap_Cvar_VariableValue("cg_RQ3_friendlyFire"));
		//Makro - build server info list
		} else if (Q_stricmp(name, "refreshIngameServerInfo") == 0) {
			UI_BuildIngameServerInfoList();
		//Makro - run a preset command
		} else if (Q_stricmp(name, "runPreset") == 0) {
			int index;
			if (Int_Parse(args, &index)) {
				if (index >=1 && index <= numRadioPresets) {
					char *cmd = radioPresets[index-1].Script->string;

					if (cmd[0]) {
						trap_Cmd_ExecuteText(EXEC_APPEND, va("%s\n", radioPresets[index-1].Script->string));
					} else {
						Com_Printf("Empty slot (%i)\n", index);
					}
				} else {
					Com_Printf("Preset number out of range (%i)\n", index);
				}
			}
		//Makro - change the SSG crosshair
		} else if (Q_stricmp(name, "nextSSGCrosshair") == 0) {
			int current, offset;

			if (Int_Parse(args, &offset)) {
				if (String_Parse(args, &name2)) {
					qboolean instant = (Q_stricmp(name2, "instant") == 0);

					current = ((int) trap_Cvar_VariableValue("cg_RQ3_ssgCrosshair") + offset) % NUM_SSGCROSSHAIRS;
					if (current < 0)
						current = NUM_SSGCROSSHAIRS - 1;
					else if (current >= NUM_SSGCROSSHAIRS)
						current = 0;
					if (instant) {
/*						if (current == 0)
							uiInfo.uiDC.Assets.SSGcrosshairShader =
							    trap_R_RegisterShaderNoMip("gfx/rq3_hud/ssg2x");
						else
							uiInfo.uiDC.Assets.SSGcrosshairShader =
							    trap_R_RegisterShaderNoMip(va
										       ("gfx/rq3_hud/ssg2x-%i",
											current)); */
							uiInfo.uiDC.Assets.SSGcrosshairShader =
							    trap_R_RegisterShaderNoMip(va
										       ("gfx/rq3_hud/ssg2x-%i",
											current));
					}
					trap_Cvar_SetValue("cg_RQ3_ssgCrosshair", (float) current);
				}
			}
		} else if (Q_stricmp(name, "loadArenas") == 0) {
			//Makro - updating cvars needed here
			trap_Cvar_Set("ui_netGameType", va("%d", ui_netGameType.integer));
			trap_Cvar_Set("ui_actualnetGameType",
				      va("%d", uiInfo.gameTypes[ui_netGameType.integer].gtEnum));
			trap_Cvar_Set("ui_currentNetMap", "0");
			UI_LoadArenas();
			UI_MapCountByGameType(qfalse);
			Menu_SetFeederSelection(NULL, FEEDER_ALLMAPS, 0, "createserver");
		//Makro - new UI script that doesn't check the gametype
		} else if (Q_stricmp(name, "loadVoteArenas") == 0) {
			trap_Cvar_Set("ui_currentNetMap", "0");
			UI_LoadArenas();
			UI_MapCountVote();
			Menu_SetFeederSelection(NULL, FEEDER_ALLMAPS, 0, "ingame_callvote");
		//Makro - get the team names
		} else if (Q_stricmp(name, "updateJoinTeamNames") == 0) {
			char info[MAX_INFO_STRING];
			trap_GetConfigString(CS_SERVERINFO, info, sizeof(info));
			strncpy(team1Name, UI_Cvar_VariableString("g_RQ3_team1Name"), sizeof(team1Name));
			strncpy(team2Name, UI_Cvar_VariableString("g_RQ3_team2Name"), sizeof(team2Name));
		//Makro - update weapon/item banning info
		} else if (Q_stricmp(name, "updateItemBans") == 0) {
			char info[MAX_INFO_STRING];
			trap_GetConfigString(CS_SERVERINFO, info, sizeof(info));
			uiInfo.weapBan = atoi(Info_ValueForKey(info, "g_RQ3_weaponBan"));
			uiInfo.itemBan = atoi(Info_ValueForKey(info, "g_RQ3_itemBan"));
		} else if (Q_stricmp(name, "saveControls") == 0) {
			Controls_SetConfig(qtrue);
		} else if (Q_stricmp(name, "loadControls") == 0) {
			Controls_GetConfig();
		} else if (Q_stricmp(name, "clearError") == 0) {
			trap_Cvar_Set("com_errorMessage", "");
		} else if (Q_stricmp(name, "loadGameInfo") == 0) {
#ifdef PRE_RELEASE_TADEMO
			UI_ParseGameInfo("demogameinfo.txt");
#else
			UI_ParseGameInfo("gameinfo.txt");
#endif
			UI_LoadBestScores(uiInfo.mapList[ui_currentMap.integer].mapLoadName,
					  uiInfo.gameTypes[ui_gameType.integer].gtEnum);
		} else if (Q_stricmp(name, "resetScores") == 0) {
			UI_ClearScores();
		} else if (Q_stricmp(name, "RefreshServers") == 0) {
			UI_StartServerRefresh(qtrue);
			UI_BuildServerDisplayList(qtrue);
		} else if (Q_stricmp(name, "RefreshFilter") == 0) {
			UI_StartServerRefresh(qfalse);
			UI_BuildServerDisplayList(qtrue);
		} else if (Q_stricmp(name, "RunSPDemo") == 0) {
			if (uiInfo.demoAvailable) {
				trap_Cmd_ExecuteText(EXEC_APPEND,
						     va("demo %s_%i\n",
							uiInfo.mapList[ui_currentMap.integer].mapLoadName,
							uiInfo.gameTypes[ui_gameType.integer].gtEnum));
			}
		} else if (Q_stricmp(name, "LoadDemos") == 0) {
			UI_LoadDemos();
		} else if (Q_stricmp(name, "LoadMovies") == 0) {
			UI_LoadMovies();
		} else if (Q_stricmp(name, "LoadMods") == 0) {
			UI_LoadMods();
		} else if (Q_stricmp(name, "playMovie") == 0) {
			if (uiInfo.previewMovie >= 0) {
				trap_CIN_StopCinematic(uiInfo.previewMovie);
			}
			trap_Cmd_ExecuteText(EXEC_APPEND,
					     va("cinematic %s.roq 2\n", uiInfo.movieList[uiInfo.movieIndex]));
		} else if (Q_stricmp(name, "RunMod") == 0) {
			trap_Cvar_Set("fs_game", uiInfo.modList[uiInfo.modIndex].modName);
			trap_Cmd_ExecuteText(EXEC_APPEND, "vid_restart;");
		} else if (Q_stricmp(name, "RunDemo") == 0) {
			//Makro - missing check
			if (uiInfo.demoIndex >= 0 && uiInfo.demoIndex < uiInfo.demoCount)
			{
				//Makro - no longer needed
				//Makro - remove version info
				//char demoname[128], *p;
				//Q_strncpyz(demoname, uiInfo.demoList[uiInfo.demoIndex], sizeof(demoname));
				//p = Q_strrchr(demoname, '(');
				//if (p)
				//	*(p-1)=0;
				//trap_Cmd_ExecuteText(EXEC_APPEND, va("demo %s.dm_%d\n", demoname, uiInfo.demoType[uiInfo.demoIndex]));
				trap_Cmd_ExecuteText(EXEC_APPEND, va("demo %s.dm_%d\n", uiInfo.demoList[uiInfo.demoIndex], uiInfo.demoType[uiInfo.demoIndex]));
			}
		} else if (Q_stricmp(name, "Quake3") == 0) {
			trap_Cvar_Set("fs_game", "");
			trap_Cmd_ExecuteText(EXEC_APPEND, "vid_restart;");
		} else if (Q_stricmp(name, "closeJoin") == 0) {
			if (uiInfo.serverStatus.refreshActive) {
				UI_StopServerRefresh();
				uiInfo.serverStatus.nextDisplayRefresh = 0;
				uiInfo.nextServerStatusRefresh = 0;
				uiInfo.nextFindPlayerRefresh = 0;
				UI_BuildServerDisplayList(qtrue);
			} else {
				Menus_CloseByName("joinserver");
				Menus_OpenByName("main", qfalse);
			}
		} else if (Q_stricmp(name, "StopRefresh") == 0) {
			UI_StopServerRefresh();
			uiInfo.serverStatus.nextDisplayRefresh = 0;
			uiInfo.nextServerStatusRefresh = 0;
			uiInfo.nextFindPlayerRefresh = 0;
		} else if (Q_stricmp(name, "UpdateFilter") == 0) {
			if (ui_netSource.integer == AS_LOCAL) {
				UI_StartServerRefresh(qtrue);
			}
			UI_BuildServerDisplayList(qtrue);
			UI_FeederSelection(FEEDER_SERVERS, 0);
		} else if (Q_stricmp(name, "ServerStatus") == 0) {
			trap_LAN_GetServerAddressString(ui_netSource.integer,
							uiInfo.serverStatus.displayServers[uiInfo.serverStatus.
											   currentServer],
							uiInfo.serverStatusAddress, sizeof(uiInfo.serverStatusAddress));
			UI_BuildServerStatus(qtrue);
		} else if (Q_stricmp(name, "FoundPlayerServerStatus") == 0) {
			Q_strncpyz(uiInfo.serverStatusAddress,
				   uiInfo.foundPlayerServerAddresses[uiInfo.currentFoundPlayerServer],
				   sizeof(uiInfo.serverStatusAddress));
			UI_BuildServerStatus(qtrue);
			Menu_SetFeederSelection(NULL, FEEDER_FINDPLAYER, 0, NULL);
		} else if (Q_stricmp(name, "FindPlayer") == 0) {
			UI_BuildFindPlayerList(qtrue);
			// clear the displayed server status info
			uiInfo.serverStatusInfo.numLines = 0;
			Menu_SetFeederSelection(NULL, FEEDER_FINDPLAYER, 0, NULL);
		} else if (Q_stricmp(name, "JoinServer") == 0) {
			trap_Cvar_Set("cg_thirdPerson", "0");
			trap_Cvar_Set("cg_cameraOrbit", "0");
			trap_Cvar_Set("ui_singlePlayerActive", "0");
			if (uiInfo.serverStatus.currentServer >= 0
			    && uiInfo.serverStatus.currentServer < uiInfo.serverStatus.numDisplayServers) {
				trap_LAN_GetServerAddressString(ui_netSource.integer,
								uiInfo.serverStatus.displayServers[uiInfo.serverStatus.
												   currentServer], buff,
								1024);
				trap_Cmd_ExecuteText(EXEC_APPEND, va("connect %s\n", buff));
			}
			//Makro - specify server
		} else if (Q_stricmp(name, "JoinSpecifiedServer") == 0) {
			trap_Cvar_Set("cg_thirdPerson", "0");
			trap_Cvar_Set("cg_cameraOrbit", "0");
			trap_Cvar_Set("ui_singlePlayerActive", "0");
			if (ui_RQ3_joinPort.value) {
				trap_Cmd_ExecuteText(EXEC_APPEND,
						     va("connect %s:%i\n", ui_RQ3_joinAddress.string,
							ui_RQ3_joinPort.integer));
			} else {
				trap_Cmd_ExecuteText(EXEC_APPEND, va("connect %s\n", ui_RQ3_joinAddress.string));
			}
		} else if (Q_stricmp(name, "FoundPlayerJoinServer") == 0) {
			trap_Cvar_Set("ui_singlePlayerActive", "0");
			if (uiInfo.currentFoundPlayerServer >= 0
			    && uiInfo.currentFoundPlayerServer < uiInfo.numFoundPlayerServers) {
				trap_Cmd_ExecuteText(EXEC_APPEND,
						     va("connect %s\n",
							uiInfo.foundPlayerServerAddresses[uiInfo.
											  currentFoundPlayerServer]));
			}
		} else if (Q_stricmp(name, "Quit") == 0) {
			trap_Cvar_Set("ui_singlePlayerActive", "0");
			//Makro - see if we have to restore the music volume
			if (uiInfo.savedMusicVol) {
				trap_Cmd_ExecuteText(EXEC_APPEND, va("set s_musicvolume %f ; wait\n", uiInfo.oldMusicVol));
			}
			//trap_Cmd_ExecuteText( EXEC_NOW, "quit");
			//Makro - saved config file before exiting
			trap_Cmd_ExecuteText(EXEC_APPEND, "writeconfig rq3config.cfg ; quit\n");
			//Makro - weapon menu after joining a team
		} else if (Q_stricmp(name, "weapAfterJoin") == 0) {
			//only in teamplay
			if (UI_RQ3_WeaponMenuAccess())
			{
				if (ui_RQ3_weapAfterJoin.integer) {
					_UI_SetActiveMenu(UIMENU_RQ3_WEAPON);
				}
			}
		} else if (Q_stricmp(name, "Controls") == 0) {
			trap_Cvar_Set("cl_paused", "1");
			trap_Key_SetCatcher(KEYCATCH_UI);
			Menus_CloseAll();
			Menus_ActivateByName("setup_menu2", qfalse);
		} else if (Q_stricmp(name, "Leave") == 0) {
			trap_Cmd_ExecuteText(EXEC_APPEND, "disconnect\n");
			trap_Key_SetCatcher(KEYCATCH_UI);
			Menus_CloseAll();
			Menus_ActivateByName("main", qfalse);
		} else if (Q_stricmp(name, "ServerSort") == 0) {
			int sortColumn;

			if (Int_Parse(args, &sortColumn)) {
				// if same column we're already sorting on then flip the direction
				if (sortColumn == uiInfo.serverStatus.sortKey) {
					uiInfo.serverStatus.sortDir = !uiInfo.serverStatus.sortDir;
				}
				// make sure we sort again
				UI_ServersSort(sortColumn, qtrue);
			}
		} else if (Q_stricmp(name, "nextSkirmish") == 0) {
			UI_StartSkirmish(qtrue);
		} else if (Q_stricmp(name, "SkirmishStart") == 0) {
			UI_StartSkirmish(qfalse);
		} else if (Q_stricmp(name, "closeingame") == 0) {
			trap_Key_SetCatcher(trap_Key_GetCatcher() & ~KEYCATCH_UI);
			trap_Key_ClearStates();
			trap_Cvar_Set("cl_paused", "0");
			Menus_CloseAll();
		} else if (Q_stricmp(name, "voteMap") == 0) {
			if (ui_currentNetMap.integer >= 0 && ui_currentNetMap.integer < uiInfo.mapCount) {
				trap_Cmd_ExecuteText(EXEC_APPEND,
						     va("callvote map %s\n",
							uiInfo.mapList[ui_currentNetMap.integer].mapLoadName));
			}
		} else if (Q_stricmp(name, "voteKick") == 0) {
			if (uiInfo.playerIndex >= 0 && uiInfo.playerIndex < uiInfo.playerCount) {
				trap_Cmd_ExecuteText(EXEC_APPEND,
						     va("callvote kick %s\n", uiInfo.playerNames[uiInfo.playerIndex]));
			}
		//Makro - ignore command
		} else if (Q_stricmp(name, "ignore") == 0) {
			if (uiInfo.playerIndex >= 0 && uiInfo.playerIndex < uiInfo.playerCount) {
				trap_Cmd_ExecuteText(EXEC_APPEND,
						     va("ignore %s\n", uiInfo.playerNames[uiInfo.playerIndex]));
			}
		//...and unignore
		} else if (Q_stricmp(name, "unignore") == 0) {
			if (uiInfo.playerIndex >= 0 && uiInfo.playerIndex < uiInfo.playerCount) {
				trap_Cmd_ExecuteText(EXEC_APPEND,
						     va("unignore %s\n", uiInfo.playerNames[uiInfo.playerIndex]));
			}
		} else if (Q_stricmp(name, "voteGame") == 0) {
			if (ui_netGameType.integer >= 0 && ui_netGameType.integer < uiInfo.numGameTypes) {
				trap_Cmd_ExecuteText(EXEC_APPEND,
						     va("callvote g_gametype %i\n",
							uiInfo.gameTypes[ui_netGameType.integer].gtEnum));
			}
		} else if (Q_stricmp(name, "voteLeader") == 0) {
			if (uiInfo.teamIndex >= 0 && uiInfo.teamIndex < uiInfo.myTeamCount) {
				trap_Cmd_ExecuteText(EXEC_APPEND,
						     va("callteamvote leader %s\n",
							uiInfo.teamNames[uiInfo.teamIndex]));
			}
		} else if (Q_stricmp(name, "addBot") == 0) {
			//Makro - using bot list instead of character list
			//if (trap_Cvar_VariableValue("g_gametype") >= GT_TEAM) {
			//      trap_Cmd_ExecuteText( EXEC_APPEND, va("addbot %s %i %s\n", uiInfo.characterList[uiInfo.botIndex].name, uiInfo.skillIndex+1, (uiInfo.redBlue == 0) ? "Red" : "Blue") );
			//} else {
			//Makro - don't add the bot instantly
			trap_Cmd_ExecuteText(EXEC_APPEND, va("wait; addbot %s %i %s\n", UI_GetBotNameByNumber(uiInfo.botIndex), uiInfo.skillIndex + 1, (uiInfo.redBlue == 0) ? "Red" : "Blue"));
			//}
		//Makro - add random bot
		} else if (Q_stricmp(name, "addRandomBot") == 0) {
			//int index = (int) (random() * (float) (UI_GetNumBots() - 1));
			//Makro - don't add the bot instantly
			//trap_Cmd_ExecuteText( EXEC_APPEND, va("wait; addbot %s %i %s\n", UI_GetBotNameByNumber(index), uiInfo.skillIndex+1, (uiInfo.redBlue == 0) ? "Red" : "Blue") );
			trap_Cmd_ExecuteText(EXEC_APPEND, va("wait; addbot %s %i %s\n", UI_GetBotNameByNumber(rand() % UI_GetNumBots()), uiInfo.skillIndex + 1, (uiInfo.redBlue == 0) ? "Red" : "Blue"));
		//Makro - record a demo
		} else if (Q_stricmp(name, "recordDemo") == 0) {
			int oldSync = (int) trap_Cvar_VariableValue("g_synchronousClients");

			trap_Cmd_ExecuteText(EXEC_APPEND,
					     va
					     ("wait; wait; set g_synchronousClients 1; record %s; set g_synchronousClients %i",
					      ui_RQ3_demoName.string, oldSync));
		} else if (Q_stricmp(name, "addFavorite") == 0) {
			if (ui_netSource.integer != AS_FAVORITES) {
				char name[MAX_NAME_LENGTH];
				char addr[MAX_NAME_LENGTH];
				int res;

				trap_LAN_GetServerInfo(ui_netSource.integer,
						       uiInfo.serverStatus.displayServers[uiInfo.serverStatus.
											  currentServer], buff,
						       MAX_STRING_CHARS);
				name[0] = addr[0] = '\0';
				Q_strncpyz(name, Info_ValueForKey(buff, "hostname"), MAX_NAME_LENGTH);
				Q_strncpyz(addr, Info_ValueForKey(buff, "addr"), MAX_NAME_LENGTH);
				if (strlen(name) > 0 && strlen(addr) > 0) {
					res = trap_LAN_AddServer(AS_FAVORITES, name, addr);
					if (res == 0) {
						// server already in the list
						Com_Printf("Favorite already in list\n");
					} else if (res == -1) {
						// list full
						Com_Printf("Favorite list full\n");
					} else {
						// successfully added
						Com_Printf("Added favorite server %s\n", addr);
					}
				}
			}
		} else if (Q_stricmp(name, "deleteFavorite") == 0) {
			if (ui_netSource.integer == AS_FAVORITES) {
				char addr[MAX_NAME_LENGTH];

				trap_LAN_GetServerInfo(ui_netSource.integer,
						       uiInfo.serverStatus.displayServers[uiInfo.serverStatus.
											  currentServer], buff,
						       MAX_STRING_CHARS);
				addr[0] = '\0';
				Q_strncpyz(addr, Info_ValueForKey(buff, "addr"), MAX_NAME_LENGTH);
				if (strlen(addr) > 0) {
					trap_LAN_RemoveServer(AS_FAVORITES, addr);
				}
			}
		} else if (Q_stricmp(name, "createFavorite") == 0) {
			if (ui_netSource.integer == AS_FAVORITES) {
				char name[MAX_NAME_LENGTH];
				char addr[MAX_NAME_LENGTH];
				int res;

				name[0] = addr[0] = '\0';
				Q_strncpyz(name, UI_Cvar_VariableString("ui_favoriteName"), MAX_NAME_LENGTH);
				Q_strncpyz(addr, UI_Cvar_VariableString("ui_favoriteAddress"), MAX_NAME_LENGTH);
				if (strlen(name) > 0 && strlen(addr) > 0) {
					res = trap_LAN_AddServer(AS_FAVORITES, name, addr);
					if (res == 0) {
						// server already in the list
						Com_Printf("Favorite already in list\n");
					} else if (res == -1) {
						// list full
						Com_Printf("Favorite list full\n");
					} else {
						// successfully added
						Com_Printf("Added favorite server %s\n", addr);
					}
				}
			}
		} else if (Q_stricmp(name, "orders") == 0) {
			const char *orders;

			if (String_Parse(args, &orders)) {
				int selectedPlayer = trap_Cvar_VariableValue("cg_selectedPlayer");

				if (selectedPlayer < uiInfo.myTeamCount) {
					strcpy(buff, orders);
					trap_Cmd_ExecuteText(EXEC_APPEND,
							     va(buff, uiInfo.teamClientNums[selectedPlayer]));
					trap_Cmd_ExecuteText(EXEC_APPEND, "\n");
				} else {
					int i;

					for (i = 0; i < uiInfo.myTeamCount; i++) {
						if (Q_stricmp(UI_Cvar_VariableString("name"), uiInfo.teamNames[i]) == 0) {
							continue;
						}
						strcpy(buff, orders);
						trap_Cmd_ExecuteText(EXEC_APPEND, va(buff, uiInfo.teamNames[i]));
						trap_Cmd_ExecuteText(EXEC_APPEND, "\n");
					}
				}
				trap_Key_SetCatcher(trap_Key_GetCatcher() & ~KEYCATCH_UI);
				trap_Key_ClearStates();
				trap_Cvar_Set("cl_paused", "0");
				Menus_CloseAll();
			}
		} else if (Q_stricmp(name, "voiceOrdersTeam") == 0) {
			const char *orders;

			if (String_Parse(args, &orders)) {
				int selectedPlayer = trap_Cvar_VariableValue("cg_selectedPlayer");

				if (selectedPlayer == uiInfo.myTeamCount) {
					trap_Cmd_ExecuteText(EXEC_APPEND, orders);
					trap_Cmd_ExecuteText(EXEC_APPEND, "\n");
				}
				trap_Key_SetCatcher(trap_Key_GetCatcher() & ~KEYCATCH_UI);
				trap_Key_ClearStates();
				trap_Cvar_Set("cl_paused", "0");
				Menus_CloseAll();
			}
		} else if (Q_stricmp(name, "voiceOrders") == 0) {
			const char *orders;

			if (String_Parse(args, &orders)) {
				int selectedPlayer = trap_Cvar_VariableValue("cg_selectedPlayer");

				if (selectedPlayer < uiInfo.myTeamCount) {
					strcpy(buff, orders);
					trap_Cmd_ExecuteText(EXEC_APPEND,
							     va(buff, uiInfo.teamClientNums[selectedPlayer]));
					trap_Cmd_ExecuteText(EXEC_APPEND, "\n");
				}
				trap_Key_SetCatcher(trap_Key_GetCatcher() & ~KEYCATCH_UI);
				trap_Key_ClearStates();
				trap_Cvar_Set("cl_paused", "0");
				Menus_CloseAll();
			}
		} else if (Q_stricmp(name, "glCustom") == 0) {
			trap_Cvar_Set("ui_glCustom", "4");
			//Makro - save/load the music volume            
		} else if (Q_stricmp(name, "backupMusicVolume") == 0) {
			uiInfo.oldMusicVol = trap_Cvar_VariableValue("s_musicvolume");
			uiInfo.savedMusicVol = qtrue;
		} else if (Q_stricmp(name, "restoreMusicVolume") == 0) {
			trap_Cvar_SetValue("s_musicvolume", uiInfo.oldMusicVol);
			uiInfo.savedMusicVol = qfalse;
		//Makro - create model replacements list
		} else if (Q_stricmp(name, "buildReplacementList") == 0) {
			switch (uiInfo.replacements.TypeIndex)
			{
				case 0:
					UI_BuildReplacementList(replacementWeapons[uiInfo.replacements.SubtypeIndex % replacementWeapCount].cvarName);
					UI_LoadReplacement(uiInfo.replacements.Index);
					break;
				case 1:
					UI_BuildReplacementList(replacementItems[uiInfo.replacements.SubtypeIndex % replacementItemCount].cvarName);
					UI_LoadReplacement(uiInfo.replacements.Index);
					break;
				case 2:
					UI_BuildReplacementList(replacementAmmo[uiInfo.replacements.SubtypeIndex % replacementAmmoCount].cvarName);
					UI_LoadReplacement(uiInfo.replacements.Index);
					break;
				default:
					break;
			}
		//Makro - next/prev replacement
		} else if (Q_stricmp(name, "nextReplacement") == 0) {
			int index = uiInfo.replacements.Index, offset = 0;
			if (Int_Parse(args, &offset)) {
				index += offset;
				if (index >= uiInfo.replacements.Count)
					index = 0;
				else if (index < 0)
					index = uiInfo.replacements.Count-1;
				UI_LoadReplacement(index);
			}
		//Makro - select replacement
		} else if (Q_stricmp(name, "selectReplacement") == 0) {
			UI_SelectReplacement();
		} else if (Q_stricmp(name, "update") == 0) {
			if (String_Parse(args, &name2)) {
				UI_Update(name2);
			}
		} else if (Q_stricmp(name, "setPbClStatus") == 0) {
			int stat;

			if (Int_Parse(args, &stat))
				trap_SetPbClStatus(stat);
		} else {
			Com_Printf("unknown UI script %s\n", name);
		}
	}
}

static void UI_GetTeamColor(vec4_t * color)
{
}

/*
==================
UI_MapCountByGameType
==================
*/
static int UI_MapCountByGameType(qboolean singlePlayer)
{
	int i, c, game;

	c = 0;
	game =
	    singlePlayer ? uiInfo.gameTypes[ui_gameType.integer].gtEnum : uiInfo.gameTypes[ui_netGameType.integer].
	    gtEnum;
	if (game == GT_SINGLE_PLAYER) {
		game++;
	}
	if (game == GT_TEAM) {
		game = GT_FFA;
	}

	for (i = 0; i < uiInfo.mapCount; i++) {
		uiInfo.mapList[i].active = qfalse;
		if (uiInfo.mapList[i].typeBits & (1 << game)) {
			if (singlePlayer) {
				if (!(uiInfo.mapList[i].typeBits & (1 << GT_SINGLE_PLAYER))) {
					continue;
				}
			}
			c++;
			uiInfo.mapList[i].active = qtrue;
		}
	}
	return c;
}

/*
==================
UI_MapCountVote
Added by Makro
==================
*/
static int UI_MapCountVote(void)
{
	int i, c = 0;

	for (i=0; i < uiInfo.mapCount; i++) {
		if (uiInfo.mapList[i].typeBits != 0) {
			c++;
			uiInfo.mapList[i].active = qtrue;
		} else {
			uiInfo.mapList[i].active = qfalse;
		}
	}
	return c;
}

qboolean UI_hasSkinForBase(const char *base, const char *team)
{
	char test[1024];

	Com_sprintf(test, sizeof(test), "models/players/%s/%s/lower_default.skin", base, team);

	if (trap_FS_FOpenFile(test, 0, FS_READ)) {
		return qtrue;
	}
	Com_sprintf(test, sizeof(test), "models/players/characters/%s/%s/lower_default.skin", base, team);

	if (trap_FS_FOpenFile(test, 0, FS_READ)) {
		return qtrue;
	}
	return qfalse;
}

/*
==================
UI_MapCountByTeam
==================
*/
static int UI_HeadCountByTeam()
{
	static int init = 0;
	int i, j, k, c, tIndex;

	c = 0;
	if (!init) {
		for (i = 0; i < uiInfo.characterCount; i++) {
			uiInfo.characterList[i].reference = 0;
			for (j = 0; j < uiInfo.teamCount; j++) {
				if (UI_hasSkinForBase(uiInfo.characterList[i].base, uiInfo.teamList[j].teamName)) {
					uiInfo.characterList[i].reference |= (1 << j);
				}
			}
		}
		init = 1;
	}

	tIndex = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_teamName"));

	// do names
	for (i = 0; i < uiInfo.characterCount; i++) {
		uiInfo.characterList[i].active = qfalse;
		for (j = 0; j < TEAM_MEMBERS; j++) {
			if (uiInfo.teamList[tIndex].teamMembers[j] != NULL) {
				if (uiInfo.characterList[i].reference & (1 << tIndex)) {	// && Q_stricmp(uiInfo.teamList[tIndex].teamMembers[j], uiInfo.characterList[i].name)==0) {
					uiInfo.characterList[i].active = qtrue;
					c++;
					break;
				}
			}
		}
	}

	// and then aliases
	for (j = 0; j < TEAM_MEMBERS; j++) {
		for (k = 0; k < uiInfo.aliasCount; k++) {
			if (uiInfo.aliasList[k].name != NULL) {
				if (Q_stricmp(uiInfo.teamList[tIndex].teamMembers[j], uiInfo.aliasList[k].name) == 0) {
					for (i = 0; i < uiInfo.characterCount; i++) {
						if (uiInfo.characterList[i].headImage != -1
						    && uiInfo.characterList[i].reference & (1 << tIndex)
						    && Q_stricmp(uiInfo.aliasList[k].ai,
								 uiInfo.characterList[i].name) == 0) {
							if (uiInfo.characterList[i].active == qfalse) {
								uiInfo.characterList[i].active = qtrue;
								c++;
							}
							break;
						}
					}
				}
			}
		}
	}
	return c;
}

/*
==================
UI_InsertServerIntoDisplayList
==================
*/
static void UI_InsertServerIntoDisplayList(int num, int position)
{
	int i;

	if (position < 0 || position > uiInfo.serverStatus.numDisplayServers) {
		return;
	}
	//
	uiInfo.serverStatus.numDisplayServers++;
	for (i = uiInfo.serverStatus.numDisplayServers; i > position; i--) {
		uiInfo.serverStatus.displayServers[i] = uiInfo.serverStatus.displayServers[i - 1];
	}
	uiInfo.serverStatus.displayServers[position] = num;
}

/*
==================
UI_RemoveServerFromDisplayList
==================
*/
static void UI_RemoveServerFromDisplayList(int num)
{
	int i, j;

	for (i = 0; i < uiInfo.serverStatus.numDisplayServers; i++) {
		if (uiInfo.serverStatus.displayServers[i] == num) {
			uiInfo.serverStatus.numDisplayServers--;
			for (j = i; j < uiInfo.serverStatus.numDisplayServers; j++) {
				uiInfo.serverStatus.displayServers[j] = uiInfo.serverStatus.displayServers[j + 1];
			}
			return;
		}
	}
}

/*
==================
UI_BinaryServerInsertion
==================
*/
static void UI_BinaryServerInsertion(int num)
{
	int mid, offset, res, len;

	// use binary search to insert server
	len = uiInfo.serverStatus.numDisplayServers;
	mid = len;
	offset = 0;
	res = 0;
	while (mid > 0) {
		mid = len >> 1;
		//
		res = trap_LAN_CompareServers(ui_netSource.integer, uiInfo.serverStatus.sortKey,
					      uiInfo.serverStatus.sortDir, num,
					      uiInfo.serverStatus.displayServers[offset + mid]);
		// if equal
		if (res == 0) {
			UI_InsertServerIntoDisplayList(num, offset + mid);
			return;
		}
		// if larger
		else if (res == 1) {
			offset += mid;
			len -= mid;
		}
		// if smaller
		else {
			len -= mid;
		}
	}
	if (res == 1) {
		offset++;
	}
	UI_InsertServerIntoDisplayList(num, offset);
}

/*
==================
UI_BuildServerDisplayList
==================
*/
static void UI_BuildServerDisplayList(qboolean force)
{
	int i, count, clients, maxClients, ping, len, visible;
	char info[MAX_STRING_CHARS];

//      qboolean startRefresh = qtrue; TTimo: unused
	static int numinvisible;

	if (!(force || uiInfo.uiDC.realTime > uiInfo.serverStatus.nextDisplayRefresh)) {
		return;
	}
	// if we shouldn't reset
	if (force == 2) {
		force = 0;
	}
	// do motd updates here too
	trap_Cvar_VariableStringBuffer("cl_motdString", uiInfo.serverStatus.motd, sizeof(uiInfo.serverStatus.motd));
	len = strlen(uiInfo.serverStatus.motd);
	if (len == 0) {
		//Makro - changing from Team Arena to RQ3 beta2
		//strcpy(uiInfo.serverStatus.motd, "Welcome to Team Arena!");
		strcpy(uiInfo.serverStatus.motd, " *** Welcome to Reaction Quake 3 v3.3 *** ");
		len = strlen(uiInfo.serverStatus.motd);
	}
	if (len != uiInfo.serverStatus.motdLen) {
		uiInfo.serverStatus.motdLen = len;
		uiInfo.serverStatus.motdWidth = -1;
	}

	if (force) {
		numinvisible = 0;
		// clear number of displayed servers
		uiInfo.serverStatus.numDisplayServers = 0;
		uiInfo.serverStatus.numPlayersOnServers = 0;
		// set list box index to zero
		Menu_SetFeederSelection(NULL, FEEDER_SERVERS, 0, NULL);
		// mark all servers as visible so we store ping updates for them
		trap_LAN_MarkServerVisible(ui_netSource.integer, -1, qtrue);
	}
	// get the server count (comes from the master)
	count = trap_LAN_GetServerCount(ui_netSource.integer);
	if (count == -1 || (ui_netSource.integer == AS_LOCAL && count == 0)) {
		// still waiting on a response from the master
		uiInfo.serverStatus.numDisplayServers = 0;
		uiInfo.serverStatus.numPlayersOnServers = 0;
		uiInfo.serverStatus.nextDisplayRefresh = uiInfo.uiDC.realTime + 500;
		return;
	}

	visible = qfalse;
	for (i = 0; i < count; i++) {
		// if we already got info for this server
		if (!trap_LAN_ServerIsVisible(ui_netSource.integer, i)) {
			continue;
		}
		visible = qtrue;
		// get the ping for this server
		ping = trap_LAN_GetServerPing(ui_netSource.integer, i);
		if (ping > 0 || ui_netSource.integer == AS_FAVORITES) {

			trap_LAN_GetServerInfo(ui_netSource.integer, i, info, MAX_STRING_CHARS);

			clients = atoi(Info_ValueForKey(info, "clients"));
			uiInfo.serverStatus.numPlayersOnServers += clients;

			if (ui_browserShowEmpty.integer == 0) {
				if (clients == 0) {
					trap_LAN_MarkServerVisible(ui_netSource.integer, i, qfalse);
					continue;
				}
			}

			if (ui_browserShowFull.integer == 0) {
				maxClients = atoi(Info_ValueForKey(info, "sv_maxclients"));
				if (clients == maxClients) {
					trap_LAN_MarkServerVisible(ui_netSource.integer, i, qfalse);
					continue;
				}
			}

			//Makro - don't need filtering by gametype right now; we should re-enable this when we have more servers
			/*
			if (uiInfo.joinGameTypes[ui_joinGameType.integer].gtEnum != -1) {
				game = atoi(Info_ValueForKey(info, "gametype"));
				if (game != uiInfo.joinGameTypes[ui_joinGameType.integer].gtEnum) {
					trap_LAN_MarkServerVisible(ui_netSource.integer, i, qfalse);
					continue;
				}
			}
			*/
			//Makro - changed check
			//if (ui_serverFilterType.integer > 0) {
			if (serverFilters[ui_serverFilterType.integer].basedir[0]) {
				if (Q_stricmp
				    (Info_ValueForKey(info, "game"),
				     serverFilters[ui_serverFilterType.integer].basedir) != 0) {
					trap_LAN_MarkServerVisible(ui_netSource.integer, i, qfalse);
					continue;
				}
			}
			// make sure we never add a favorite server twice
			if (ui_netSource.integer == AS_FAVORITES) {
				UI_RemoveServerFromDisplayList(i);
			}
			// insert the server into the list
			UI_BinaryServerInsertion(i);
			// done with this server
			if (ping > 0) {
				trap_LAN_MarkServerVisible(ui_netSource.integer, i, qfalse);
				numinvisible++;
			}
		}
	}

	uiInfo.serverStatus.refreshtime = uiInfo.uiDC.realTime;

	// if there were no servers visible for ping updates
	if (!visible) {
//              UI_StopServerRefresh();
//              uiInfo.serverStatus.nextDisplayRefresh = 0;
	}
}

typedef struct {
	char *name, *altName;
} serverStatusCvar_t;

serverStatusCvar_t serverStatusCvars[] = {
	{"sv_hostname", "Name"},
	{"Address", ""},
	{"gamename", "Game name"},
	{"g_gametype", "Game type"},
	{"mapname", "Map"},
	{"version", ""},
	{"protocol", ""},
	{"timelimit", ""},
	{"fraglimit", ""},
	{NULL, NULL}
};

/*
==================
UI_SortServerStatusInfo
==================
*/
static void UI_SortServerStatusInfo(serverStatusInfo_t * info)
{
	int i, j, index;
	char *tmp1, *tmp2;

	// FIXME: if "gamename" == "baseq3" or "missionpack" then
	// replace the gametype number by FFA, CTF etc.
	//
	index = 0;
	for (i = 0; serverStatusCvars[i].name; i++) {
		for (j = 0; j < info->numLines; j++) {
			if (!info->lines[j][1] || info->lines[j][1][0]) {
				continue;
			}
			if (!Q_stricmp(serverStatusCvars[i].name, info->lines[j][0])) {
				// swap lines
				tmp1 = info->lines[index][0];
				tmp2 = info->lines[index][3];
				info->lines[index][0] = info->lines[j][0];
				info->lines[index][3] = info->lines[j][3];
				info->lines[j][0] = tmp1;
				info->lines[j][3] = tmp2;
				//
				if (strlen(serverStatusCvars[i].altName)) {
					info->lines[index][0] = serverStatusCvars[i].altName;
				}
				index++;
			}
		}
	}
}

/*
==================
UI_GetServerStatusInfo
==================
*/
static int UI_GetServerStatusInfo(const char *serverAddress, serverStatusInfo_t * info)
{
	char *p, *score, *ping, *name;
	int i, len;

	if (!info) {
		trap_LAN_ServerStatus(serverAddress, NULL, 0);
		return qfalse;
	}
	memset(info, 0, sizeof(*info));
	if (trap_LAN_ServerStatus(serverAddress, info->text, sizeof(info->text))) {
		Q_strncpyz(info->address, serverAddress, sizeof(info->address));
		p = info->text;
		info->numLines = 0;
		info->lines[info->numLines][0] = "Address";
		info->lines[info->numLines][1] = "";
		info->lines[info->numLines][2] = "";
		info->lines[info->numLines][3] = info->address;
		info->numLines++;
		// get the cvars
		while (p && *p) {
			p = strchr(p, '\\');
			if (!p)
				break;
			*p++ = '\0';
			if (*p == '\\')
				break;
			info->lines[info->numLines][0] = p;
			info->lines[info->numLines][1] = "";
			info->lines[info->numLines][2] = "";
			p = strchr(p, '\\');
			if (!p)
				break;
			*p++ = '\0';
			info->lines[info->numLines][3] = p;

			info->numLines++;
			if (info->numLines >= MAX_SERVERSTATUS_LINES)
				break;
		}
		// get the player list
		if (info->numLines < MAX_SERVERSTATUS_LINES - 3) {
			// empty line
			info->lines[info->numLines][0] = "";
			info->lines[info->numLines][1] = "";
			info->lines[info->numLines][2] = "";
			info->lines[info->numLines][3] = "";
			info->numLines++;
			// header
			info->lines[info->numLines][0] = "num";
			info->lines[info->numLines][1] = "score";
			info->lines[info->numLines][2] = "ping";
			info->lines[info->numLines][3] = "name";
			info->numLines++;
			// parse players
			i = 0;
			len = 0;
			while (p && *p) {
				if (*p == '\\')
					*p++ = '\0';
				if (!p)
					break;
				score = p;
				p = strchr(p, ' ');
				if (!p)
					break;
				*p++ = '\0';
				ping = p;
				p = strchr(p, ' ');
				if (!p)
					break;
				*p++ = '\0';
				name = p;
				Com_sprintf(&info->pings[len], sizeof(info->pings) - len, "%d", i);
				info->lines[info->numLines][0] = &info->pings[len];
				len += strlen(&info->pings[len]) + 1;
				info->lines[info->numLines][1] = score;
				info->lines[info->numLines][2] = ping;
				info->lines[info->numLines][3] = name;
				info->numLines++;
				if (info->numLines >= MAX_SERVERSTATUS_LINES)
					break;
				p = strchr(p, '\\');
				if (!p)
					break;
				*p++ = '\0';
				//
				i++;
			}
		}
		UI_SortServerStatusInfo(info);
		return qtrue;
	}
	return qfalse;
}

/*
==================
stristr
==================
*/
static char *stristr(char *str, char *charset)
{
	int i;

	while (*str) {
		for (i = 0; charset[i] && str[i]; i++) {
			if (toupper(charset[i]) != toupper(str[i]))
				break;
		}
		if (!charset[i])
			return str;
		str++;
	}
	return NULL;
}

/*
==================
UI_BuildFindPlayerList
==================
*/
static void UI_BuildFindPlayerList(qboolean force)
{
	static int numFound, numTimeOuts;
	int i, j, resend;
	serverStatusInfo_t info;
	char name[MAX_NAME_LENGTH + 2];
	char infoString[MAX_STRING_CHARS];

	if (!force) {
		if (!uiInfo.nextFindPlayerRefresh || uiInfo.nextFindPlayerRefresh > uiInfo.uiDC.realTime) {
			return;
		}
	} else {
		memset(&uiInfo.pendingServerStatus, 0, sizeof(uiInfo.pendingServerStatus));
		uiInfo.numFoundPlayerServers = 0;
		uiInfo.currentFoundPlayerServer = 0;
		trap_Cvar_VariableStringBuffer("ui_findPlayer", uiInfo.findPlayerName, sizeof(uiInfo.findPlayerName));
		Q_CleanStr(uiInfo.findPlayerName);
		// should have a string of some length
		if (!strlen(uiInfo.findPlayerName)) {
			uiInfo.nextFindPlayerRefresh = 0;
			return;
		}
		// set resend time
		resend = ui_serverStatusTimeOut.integer / 2 - 10;
		if (resend < 50) {
			resend = 50;
		}
		trap_Cvar_Set("cl_serverStatusResendTime", va("%d", resend));
		// reset all server status requests
		trap_LAN_ServerStatus(NULL, NULL, 0);
		//
		uiInfo.numFoundPlayerServers = 1;
		Com_sprintf(uiInfo.foundPlayerServerNames[uiInfo.numFoundPlayerServers - 1],
			    sizeof(uiInfo.foundPlayerServerNames[uiInfo.numFoundPlayerServers - 1]),
			    "searching %d...", uiInfo.pendingServerStatus.num);
		numFound = 0;
		numTimeOuts++;
	}
	for (i = 0; i < MAX_SERVERSTATUSREQUESTS; i++) {
		// if this pending server is valid
		if (uiInfo.pendingServerStatus.server[i].valid) {
			// try to get the server status for this server
			if (UI_GetServerStatusInfo(uiInfo.pendingServerStatus.server[i].adrstr, &info)) {
				//
				numFound++;
				// parse through the server status lines
				for (j = 0; j < info.numLines; j++) {
					// should have ping info
					if (!info.lines[j][2] || !info.lines[j][2][0]) {
						continue;
					}
					// clean string first
					Q_strncpyz(name, info.lines[j][3], sizeof(name));
					Q_CleanStr(name);
					// if the player name is a substring
					if (stristr(name, uiInfo.findPlayerName)) {
						// add to found server list if we have space (always leave space for a line with the number found)
						if (uiInfo.numFoundPlayerServers < MAX_FOUNDPLAYER_SERVERS - 1) {
							//
							Q_strncpyz(uiInfo.
								   foundPlayerServerAddresses[uiInfo.
											      numFoundPlayerServers -
											      1],
								   uiInfo.pendingServerStatus.server[i].adrstr,
								   sizeof(uiInfo.foundPlayerServerAddresses[0]));
							Q_strncpyz(uiInfo.
								   foundPlayerServerNames[uiInfo.numFoundPlayerServers -
											  1],
								   uiInfo.pendingServerStatus.server[i].name,
								   sizeof(uiInfo.foundPlayerServerNames[0]));
							uiInfo.numFoundPlayerServers++;
						} else {
							// can't add any more so we're done
							uiInfo.pendingServerStatus.num =
							    uiInfo.serverStatus.numDisplayServers;
						}
					}
				}
				Com_sprintf(uiInfo.foundPlayerServerNames[uiInfo.numFoundPlayerServers - 1],
					    sizeof(uiInfo.foundPlayerServerNames[uiInfo.numFoundPlayerServers - 1]),
					    "searching %d/%d...", uiInfo.pendingServerStatus.num, numFound);
				// retrieved the server status so reuse this spot
				uiInfo.pendingServerStatus.server[i].valid = qfalse;
			}
		}
		// if empty pending slot or timed out
		if (!uiInfo.pendingServerStatus.server[i].valid ||
		    uiInfo.pendingServerStatus.server[i].startTime <
		    uiInfo.uiDC.realTime - ui_serverStatusTimeOut.integer) {
			if (uiInfo.pendingServerStatus.server[i].valid) {
				numTimeOuts++;
			}
			// reset server status request for this address
			UI_GetServerStatusInfo(uiInfo.pendingServerStatus.server[i].adrstr, NULL);
			// reuse pending slot
			uiInfo.pendingServerStatus.server[i].valid = qfalse;
			// if we didn't try to get the status of all servers in the main browser yet
			if (uiInfo.pendingServerStatus.num < uiInfo.serverStatus.numDisplayServers) {
				uiInfo.pendingServerStatus.server[i].startTime = uiInfo.uiDC.realTime;
				trap_LAN_GetServerAddressString(ui_netSource.integer,
								uiInfo.serverStatus.displayServers[uiInfo.
												   pendingServerStatus.
												   num],
								uiInfo.pendingServerStatus.server[i].adrstr,
								sizeof(uiInfo.pendingServerStatus.server[i].adrstr));
				trap_LAN_GetServerInfo(ui_netSource.integer,
						       uiInfo.serverStatus.displayServers[uiInfo.pendingServerStatus.
											  num], infoString,
						       sizeof(infoString));
				Q_strncpyz(uiInfo.pendingServerStatus.server[i].name,
					   Info_ValueForKey(infoString, "hostname"),
					   sizeof(uiInfo.pendingServerStatus.server[0].name));
				uiInfo.pendingServerStatus.server[i].valid = qtrue;
				uiInfo.pendingServerStatus.num++;
				Com_sprintf(uiInfo.foundPlayerServerNames[uiInfo.numFoundPlayerServers - 1],
					    sizeof(uiInfo.foundPlayerServerNames[uiInfo.numFoundPlayerServers - 1]),
					    "searching %d/%d...", uiInfo.pendingServerStatus.num, numFound);
			}
		}
	}
	for (i = 0; i < MAX_SERVERSTATUSREQUESTS; i++) {
		if (uiInfo.pendingServerStatus.server[i].valid) {
			break;
		}
	}
	// if still trying to retrieve server status info
	if (i < MAX_SERVERSTATUSREQUESTS) {
		uiInfo.nextFindPlayerRefresh = uiInfo.uiDC.realTime + 25;
	} else {
		// add a line that shows the number of servers found
		if (!uiInfo.numFoundPlayerServers) {
			Com_sprintf(uiInfo.foundPlayerServerNames[uiInfo.numFoundPlayerServers - 1],
				    sizeof(uiInfo.foundPlayerServerAddresses[0]), "no servers found");
		} else {
			Com_sprintf(uiInfo.foundPlayerServerNames[uiInfo.numFoundPlayerServers - 1],
				    sizeof(uiInfo.foundPlayerServerAddresses[0]), "%d server%s found with player %s",
				    uiInfo.numFoundPlayerServers - 1, uiInfo.numFoundPlayerServers == 2 ? "" : "s",
				    uiInfo.findPlayerName);
		}
		uiInfo.nextFindPlayerRefresh = 0;
		// show the server status info for the selected server
		UI_FeederSelection(FEEDER_FINDPLAYER, uiInfo.currentFoundPlayerServer);
	}
}

/*
==================
UI_BuildServerStatus
==================
*/
static void UI_BuildServerStatus(qboolean force)
{

	if (uiInfo.nextFindPlayerRefresh) {
		return;
	}
	if (!force) {
		if (!uiInfo.nextServerStatusRefresh || uiInfo.nextServerStatusRefresh > uiInfo.uiDC.realTime) {
			return;
		}
	} else {
		Menu_SetFeederSelection(NULL, FEEDER_SERVERSTATUS, 0, NULL);
		uiInfo.serverStatusInfo.numLines = 0;
		// reset all server status requests
		trap_LAN_ServerStatus(NULL, NULL, 0);
	}
	if (uiInfo.serverStatus.currentServer < 0
	    || uiInfo.serverStatus.currentServer > uiInfo.serverStatus.numDisplayServers
	    || uiInfo.serverStatus.numDisplayServers == 0) {
		return;
	}
	if (UI_GetServerStatusInfo(uiInfo.serverStatusAddress, &uiInfo.serverStatusInfo)) {
		uiInfo.nextServerStatusRefresh = 0;
		UI_GetServerStatusInfo(uiInfo.serverStatusAddress, NULL);
	} else {
		uiInfo.nextServerStatusRefresh = uiInfo.uiDC.realTime + 500;
	}
}

/*
==================
UI_FeederCount
==================
*/
static int UI_FeederCount(float feederID)
{
	if (feederID == FEEDER_HEADS) {
		return UI_HeadCountByTeam();
	//Makro - added FEEDER_MMHEADS
	} else if (feederID == FEEDER_Q3HEADS || feederID == FEEDER_MMHEADS) {
		return uiInfo.q3HeadCount;
	} else if (feederID == FEEDER_CINEMATICS) {
		return uiInfo.movieCount;
	} else if (feederID == FEEDER_MAPS || feederID == FEEDER_ALLMAPS) {
		return UI_MapCountByGameType(feederID == FEEDER_MAPS ? qtrue : qfalse);
	} else if (feederID == FEEDER_SERVERS) {
		return uiInfo.serverStatus.numDisplayServers;
	} else if (feederID == FEEDER_SERVERSTATUS) {
		return uiInfo.serverStatusInfo.numLines;
	} else if (feederID == FEEDER_FINDPLAYER) {
		return uiInfo.numFoundPlayerServers;
	} else if (feederID == FEEDER_PLAYER_LIST) {
		if (uiInfo.uiDC.realTime > uiInfo.playerRefresh) {
			uiInfo.playerRefresh = uiInfo.uiDC.realTime + 3000;
			UI_BuildPlayerList();
		}
		return uiInfo.playerCount;
	} else if (feederID == FEEDER_TEAM_LIST) {
		if (uiInfo.uiDC.realTime > uiInfo.playerRefresh) {
			uiInfo.playerRefresh = uiInfo.uiDC.realTime + 3000;
			UI_BuildPlayerList();
		}
		return uiInfo.myTeamCount;
	} else if (feederID == FEEDER_MODS) {
		return uiInfo.modCount;
	} else if (feederID == FEEDER_DEMOS) {
		return uiInfo.demoCount;
	//Makro - improved in-game server info list
	} else if (feederID == FEEDER_INGAME_SERVERINFO) {
		return uiInfo.ingameServerInfoLineCount;
	//Makro - model replacements
	} else if (feederID == FEEDER_REPLACEMENTS) {
		return uiInfo.replacements.Count;
	//Makro - gl driver extensions
	} else if (feederID == FEEDER_GLDRIVER_INFO) {
		return uiInfo.uiDC.numGlExtensions;
	}
	return 0;
}

static const char *UI_SelectedMap(int index, int *actual)
{
	int i, c;

	c = 0;
	*actual = 0;
	for (i = 0; i < uiInfo.mapCount; i++) {
		if (uiInfo.mapList[i].active) {
			if (c == index) {
				*actual = i;
				return uiInfo.mapList[i].mapName;
			} else {
				c++;
			}
		}
	}
	return "";
}

static const char *UI_SelectedHead(int index, int *actual)
{
	int i, c;

	c = 0;
	*actual = 0;
	for (i = 0; i < uiInfo.characterCount; i++) {
		if (uiInfo.characterList[i].active) {
			if (c == index) {
				*actual = i;
				return uiInfo.characterList[i].name;
			} else {
				c++;
			}
		}
	}
	return "";
}

//Makro - added
int UI_SelectedQ3Head(qboolean doUpdate)
{
	//return uiInfo.q3SelectedHead;
	int i;
	char currentSkin[64];

	trap_Cvar_VariableStringBuffer("model", currentSkin, sizeof(currentSkin));

	updateModel |= doUpdate;

	for (i = 0; i < uiInfo.q3HeadCount; i++) {
		if (!strcmp(currentSkin, uiInfo.q3HeadNames[i])) {
			return i;
		}
	}
	return 0;
}

static int UI_GetIndexFromSelection(int actual)
{
	int i, c;

	c = 0;
	for (i = 0; i < uiInfo.mapCount; i++) {
		if (uiInfo.mapList[i].active) {
			if (i == actual) {
				return c;
			}
			c++;
		}
	}
	return 0;
}

static void UI_UpdatePendingPings()
{
	trap_LAN_ResetPings(ui_netSource.integer);
	uiInfo.serverStatus.refreshActive = qtrue;
	uiInfo.serverStatus.refreshtime = uiInfo.uiDC.realTime + 1000;

}

static const char *UI_FeederItemText(float feederID, int index, int column, qhandle_t * handle)
{
	static char info[MAX_STRING_CHARS];
	static char hostname[1024];
	static char clientBuff[32];
	static char clientIdStr[32];
	static int lastColumn = -1;
	static int lastTime = 0;

	*handle = -1;
	if (feederID == FEEDER_HEADS) {
		int actual;

		return UI_SelectedHead(index, &actual);
	//Makro - added FEEDER_MMHEADS
	} else if (feederID == FEEDER_Q3HEADS || feederID == FEEDER_MMHEADS) {
		if (index >= 0 && index < uiInfo.q3HeadCount) {
			return uiInfo.q3HeadNames[index];
		}
	} else if (feederID == FEEDER_MAPS || feederID == FEEDER_ALLMAPS) {
		int actual;

		return UI_SelectedMap(index, &actual);
	} else if (feederID == FEEDER_SERVERS) {
		if (index >= 0 && index < uiInfo.serverStatus.numDisplayServers) {
			int ping, game, punkbuster;

			if (lastColumn != column || lastTime > uiInfo.uiDC.realTime + 5000) {
				trap_LAN_GetServerInfo(ui_netSource.integer, uiInfo.serverStatus.displayServers[index],
						       info, MAX_STRING_CHARS);
				lastColumn = column;
				lastTime = uiInfo.uiDC.realTime;
			}
			ping = atoi(Info_ValueForKey(info, "ping"));
			if (ping == -1) {
				// if we ever see a ping that is out of date, do a server refresh
				// UI_UpdatePendingPings();
			}
			switch (column) {
			case SORT_HOST:
				if (ping <= 0) {
					return Info_ValueForKey(info, "addr");
				} else {
					if (ui_netSource.integer == AS_LOCAL) {
						Com_sprintf(hostname, sizeof(hostname), "%s [%s]",
							    Info_ValueForKey(info, "hostname"),
							    netnames[atoi(Info_ValueForKey(info, "nettype"))]);
						return hostname;
					} else {
						Com_sprintf(hostname, sizeof(hostname), "%s",
							Info_ValueForKey(info, "hostname"));
						return hostname;
					}
				}
			case SORT_MAP:
				return Info_ValueForKey(info, "mapname");
			case SORT_CLIENTS:
				Com_sprintf(clientBuff, sizeof(clientBuff), "%s / %s",
					    Info_ValueForKey(info, "clients"), Info_ValueForKey(info, "sv_maxclients"));
				return clientBuff;
			case SORT_GAME:
				game = atoi(Info_ValueForKey(info, "gametype"));
				if (game >= 0 && game < numTeamArenaGameTypes) {
					return teamArenaGameTypes[game];
				} else {
					return "Unknown";
				}
			case SORT_PING:
				if (ping <= 0) {
					return "...";
				} else {
					return Info_ValueForKey(info, "ping");
				}
			case SORT_PUNKBUSTER:
				punkbuster = atoi(Info_ValueForKey(info, "punkbuster"));
				if (punkbuster) {
					return "Yes";
				} else {
					return "No";
				}
			}
		}
	} else if (feederID == FEEDER_SERVERSTATUS) {
		if (index >= 0 && index < uiInfo.serverStatusInfo.numLines) {
			if (column >= 0 && column < 4) {
				return uiInfo.serverStatusInfo.lines[index][column];
			}
		}
	} else if (feederID == FEEDER_FINDPLAYER) {
		if (index >= 0 && index < uiInfo.numFoundPlayerServers) {
			//return uiInfo.foundPlayerServerAddresses[index];
			return uiInfo.foundPlayerServerNames[index];
		}
	} else if (feederID == FEEDER_PLAYER_LIST) {
		if (index >= 0 && index < uiInfo.playerCount) {
			if (column != 1)
				return uiInfo.playerNames[index];
			Com_sprintf(clientIdStr, sizeof(clientIdStr), "%d", index);
			return clientIdStr;
		}
	} else if (feederID == FEEDER_TEAM_LIST) {
		if (index >= 0 && index < uiInfo.myTeamCount) {
			if (column != 1)
				return uiInfo.teamNames[index];
			Com_sprintf(clientIdStr, sizeof(clientIdStr), "%d", index);
			return clientIdStr;
		}
	} else if (feederID == FEEDER_MODS) {
		if (index >= 0 && index < uiInfo.modCount) {
			if (uiInfo.modList[index].modDescr && *uiInfo.modList[index].modDescr && column == 0) {
				return uiInfo.modList[index].modDescr;
			} else {
				return uiInfo.modList[index].modName;
			}
		}
	} else if (feederID == FEEDER_CINEMATICS) {
		if (index >= 0 && index < uiInfo.movieCount) {
			return uiInfo.movieList[index];
		}
	} else if (feederID == FEEDER_DEMOS) {
		if (index >= 0 && index < uiInfo.demoCount) {
			if (column == 0) {
				return uiInfo.demoList[index];
			} else if (column == 1) {
				return q3VersionFromProtocol(uiInfo.demoType[index]);
			}
		}
	//Makro - improved in-game server info list
	} else if (feederID == FEEDER_INGAME_SERVERINFO) {
		if (index >= 0 && index < uiInfo.ingameServerInfoLineCount) {
			if (column >= 0 && column <= 1) {
				return uiInfo.ingameServerInfo[index][column];
			}
		}
	} else if (feederID == FEEDER_GLDRIVER_INFO) {
		if (index >= 0 && index < uiInfo.uiDC.numGlExtensions)
			return uiInfo.uiDC.glExtensions[index];
	/*
	//Makro - model replacements
	} else if (feederID == FEEDER_REPLACEMENTS) {
		if (index >= 0 && index < uiInfo.replacementCount) {
			return uiInfo.replacementNames[index];
		}
	*/
	}
	return "";
}

static qhandle_t UI_FeederItemImage(float feederID, int index)
{
	if (feederID == FEEDER_HEADS) {
		int actual;

		UI_SelectedHead(index, &actual);
		index = actual;
		if (index >= 0 && index < uiInfo.characterCount) {
			if (uiInfo.characterList[index].headImage == -1) {
				uiInfo.characterList[index].headImage =
				    trap_R_RegisterShaderNoMip(uiInfo.characterList[index].imageName);
			}
			return uiInfo.characterList[index].headImage;
		}
	//Makro - added FEEDER_MMHEADS
	} else if (feederID == FEEDER_Q3HEADS || feederID == FEEDER_MMHEADS) {
		if (index >= 0 && index < uiInfo.q3HeadCount) {
			return uiInfo.q3HeadIcons[index];
		}
	} else if (feederID == FEEDER_ALLMAPS || feederID == FEEDER_MAPS) {
		int actual;

		UI_SelectedMap(index, &actual);
		index = actual;
		if (index >= 0 && index < uiInfo.mapCount) {
			if (uiInfo.mapList[index].levelShot == -1) {
				uiInfo.mapList[index].levelShot =
				    trap_R_RegisterShaderNoMip(uiInfo.mapList[index].imageName);
			}
			return uiInfo.mapList[index].levelShot;
		}
	}
	return 0;
}

static void UI_FeederSelection(float feederID, int index)
{
	static char info[MAX_STRING_CHARS];

	if (feederID == FEEDER_HEADS) {
		int actual;

		UI_SelectedHead(index, &actual);
		index = actual;
		if (index >= 0 && index < uiInfo.characterCount) {
			trap_Cvar_Set("model", va("%s", uiInfo.characterList[index].base));
			trap_Cvar_Set("headmodel", va("*%s", uiInfo.characterList[index].name));
			updateModel = qtrue;
		}
	//Makro - added FEEDER_MMHEADS
	} else if (feederID == FEEDER_MMHEADS) {
		if (index >= 0 && index < uiInfo.q3HeadCount) {
			trap_Cvar_Set("ui_RQ3_teamModel", uiInfo.q3HeadNames[index]);
		}
	} else if (feederID == FEEDER_Q3HEADS) {
		if (index >= 0 && index < uiInfo.q3HeadCount) {
			trap_Cvar_Set("model", uiInfo.q3HeadNames[index]);
			trap_Cvar_Set("headmodel", uiInfo.q3HeadNames[index]);
			//Makro - this should be saved here
			uiInfo.q3SelectedHead = index;
			updateModel = qtrue;
		}
	} else if (feederID == FEEDER_MAPS || feederID == FEEDER_ALLMAPS) {
		int actual, map;

		map = (feederID == FEEDER_ALLMAPS) ? ui_currentNetMap.integer : ui_currentMap.integer;
		if (uiInfo.mapList[map].cinematic >= 0) {
			trap_CIN_StopCinematic(uiInfo.mapList[map].cinematic);
			uiInfo.mapList[map].cinematic = -1;
		}
		UI_SelectedMap(index, &actual);
		trap_Cvar_Set("ui_mapIndex", va("%d", index));
		ui_mapIndex.integer = index;

		if (feederID == FEEDER_MAPS) {
			ui_currentMap.integer = actual;
			trap_Cvar_Set("ui_currentMap", va("%d", actual));
			uiInfo.mapList[ui_currentMap.integer].cinematic =
			    trap_CIN_PlayCinematic(va("%s.roq", uiInfo.mapList[ui_currentMap.integer].mapLoadName), 0,
						   0, 0, 0, (CIN_loop | CIN_silent));
			UI_LoadBestScores(uiInfo.mapList[ui_currentMap.integer].mapLoadName,
					  uiInfo.gameTypes[ui_gameType.integer].gtEnum);
			trap_Cvar_Set("ui_opponentModel", uiInfo.mapList[ui_currentMap.integer].opponentName);
			updateOpponentModel = qtrue;
		} else {
			ui_currentNetMap.integer = actual;
			trap_Cvar_Set("ui_currentNetMap", va("%d", actual));
			uiInfo.mapList[ui_currentNetMap.integer].cinematic =
			    trap_CIN_PlayCinematic(va("%s.roq", uiInfo.mapList[ui_currentNetMap.integer].mapLoadName),
						   0, 0, 0, 0, (CIN_loop | CIN_silent));
		}
		
		// Makro - load the levelshot here, and not inside the drawing function
		if (actual >= 0 && actual < uiInfo.mapCount && uiInfo.mapList[actual].levelShot == -1)
			uiInfo.mapList[actual].levelShot = trap_R_RegisterShaderNoMip(uiInfo.mapList[actual].imageName);

	} else if (feederID == FEEDER_SERVERS) {
		const char *mapName = NULL;

		uiInfo.serverStatus.currentServer = index;
		trap_LAN_GetServerInfo(ui_netSource.integer, uiInfo.serverStatus.displayServers[index], info,
				       MAX_STRING_CHARS);
		uiInfo.serverStatus.currentServerPreview =
		    trap_R_RegisterShaderNoMip(va("levelshots/%s", Info_ValueForKey(info, "mapname")));
		if (uiInfo.serverStatus.currentServerCinematic >= 0) {
			trap_CIN_StopCinematic(uiInfo.serverStatus.currentServerCinematic);
			uiInfo.serverStatus.currentServerCinematic = -1;
		}
		mapName = Info_ValueForKey(info, "mapname");
		if (mapName && *mapName) {
			uiInfo.serverStatus.currentServerCinematic =
			    trap_CIN_PlayCinematic(va("%s.roq", mapName), 0, 0, 0, 0, (CIN_loop | CIN_silent));
		}
	} else if (feederID == FEEDER_SERVERSTATUS) {
		//
	} else if (feederID == FEEDER_FINDPLAYER) {
		uiInfo.currentFoundPlayerServer = index;
		//
		if (index < uiInfo.numFoundPlayerServers - 1) {
			// build a new server status for this server
			Q_strncpyz(uiInfo.serverStatusAddress,
				   uiInfo.foundPlayerServerAddresses[uiInfo.currentFoundPlayerServer],
				   sizeof(uiInfo.serverStatusAddress));
			Menu_SetFeederSelection(NULL, FEEDER_SERVERSTATUS, 0, NULL);
			UI_BuildServerStatus(qtrue);
		}
	} else if (feederID == FEEDER_PLAYER_LIST) {
		uiInfo.playerIndex = index;
	} else if (feederID == FEEDER_TEAM_LIST) {
		uiInfo.teamIndex = index;
	} else if (feederID == FEEDER_MODS) {
		uiInfo.modIndex = index;
	} else if (feederID == FEEDER_CINEMATICS) {
		uiInfo.movieIndex = index;
		if (uiInfo.previewMovie >= 0) {
			trap_CIN_StopCinematic(uiInfo.previewMovie);
		}
		uiInfo.previewMovie = -1;
	} else if (feederID == FEEDER_DEMOS) {
		uiInfo.demoIndex = index;
	//Makro - model replacements
	} else if (feederID == FEEDER_REPLACEMENTS) {
		//INSERT CODE !
	}
}

static qboolean Team_Parse(char **p)
{
	char *token;
	const char *tempStr;
	int i;

	token = COM_ParseExt(p, qtrue);

	if (token[0] != '{') {
		return qfalse;
	}

	INFINITE_LOOP {

		token = COM_ParseExt(p, qtrue);

		if (Q_stricmp(token, "}") == 0) {
			return qtrue;
		}

		if (!token || token[0] == 0) {
			return qfalse;
		}

		if (token[0] == '{') {
			// seven tokens per line, team name and icon, and 5 team member names
			if (!String_Parse(p, &uiInfo.teamList[uiInfo.teamCount].teamName) || !String_Parse(p, &tempStr)) {
				return qfalse;
			}

			uiInfo.teamList[uiInfo.teamCount].imageName = tempStr;
			uiInfo.teamList[uiInfo.teamCount].teamIcon =
			    trap_R_RegisterShaderNoMip(uiInfo.teamList[uiInfo.teamCount].imageName);
			uiInfo.teamList[uiInfo.teamCount].teamIcon_Metal =
			    trap_R_RegisterShaderNoMip(va("%s_metal", uiInfo.teamList[uiInfo.teamCount].imageName));
			uiInfo.teamList[uiInfo.teamCount].teamIcon_Name =
			    trap_R_RegisterShaderNoMip(va("%s_name", uiInfo.teamList[uiInfo.teamCount].imageName));

			uiInfo.teamList[uiInfo.teamCount].cinematic = -1;

			for (i = 0; i < TEAM_MEMBERS; i++) {
				uiInfo.teamList[uiInfo.teamCount].teamMembers[i] = NULL;
				if (!String_Parse(p, &uiInfo.teamList[uiInfo.teamCount].teamMembers[i])) {
					return qfalse;
				}
			}

			Com_Printf("Loaded team %s with team icon %s.\n", uiInfo.teamList[uiInfo.teamCount].teamName,
				   tempStr);
			if (uiInfo.teamCount < MAX_TEAMS) {
				uiInfo.teamCount++;
			} else {
				Com_Printf("Too many teams, last team replaced!\n");
			}
			token = COM_ParseExt(p, qtrue);
			if (token[0] != '}') {
				return qfalse;
			}
		}
	}

	//Makro - unreachable
	//return qfalse;
}

static qboolean Character_Parse(char **p)
{
	char *token;
	const char *tempStr;

	token = COM_ParseExt(p, qtrue);

	if (token[0] != '{') {
		return qfalse;
	}

	INFINITE_LOOP {
		token = COM_ParseExt(p, qtrue);

		if (Q_stricmp(token, "}") == 0) {
			return qtrue;
		}

		if (!token || token[0] == 0) {
			return qfalse;
		}

		if (token[0] == '{') {
			// two tokens per line, character name and sex
			if (!String_Parse(p, &uiInfo.characterList[uiInfo.characterCount].name)
			    || !String_Parse(p, &tempStr)) {
				return qfalse;
			}

			uiInfo.characterList[uiInfo.characterCount].headImage = -1;
			uiInfo.characterList[uiInfo.characterCount].imageName =
			    String_Alloc(va
					 ("models/players/heads/%s/icon_default.tga",
					  uiInfo.characterList[uiInfo.characterCount].name));

			if (tempStr && (!Q_stricmp(tempStr, "female"))) {
				uiInfo.characterList[uiInfo.characterCount].base = String_Alloc(va("Janet"));
			} else if (tempStr && (!Q_stricmp(tempStr, "male"))) {
				uiInfo.characterList[uiInfo.characterCount].base = String_Alloc(va("James"));
			} else {
				uiInfo.characterList[uiInfo.characterCount].base = String_Alloc(va("%s", tempStr));
			}

			Com_Printf("Loaded %s character %s.\n", uiInfo.characterList[uiInfo.characterCount].base,
				   uiInfo.characterList[uiInfo.characterCount].name);
			if (uiInfo.characterCount < MAX_HEADS) {
				uiInfo.characterCount++;
			} else {
				Com_Printf("Too many characters, last character replaced!\n");
			}

			token = COM_ParseExt(p, qtrue);
			if (token[0] != '}') {
				return qfalse;
			}
		}
	}

	//Makro - unreachable
	//return qfalse;
}

static qboolean Alias_Parse(char **p)
{
	char *token;

	token = COM_ParseExt(p, qtrue);

	if (token[0] != '{') {
		return qfalse;
	}

	INFINITE_LOOP {
		token = COM_ParseExt(p, qtrue);

		if (Q_stricmp(token, "}") == 0) {
			return qtrue;
		}

		if (!token || token[0] == 0) {
			return qfalse;
		}

		if (token[0] == '{') {
			// three tokens per line, character name, bot alias, and preferred action a - all purpose, d - defense, o - offense
			if (!String_Parse(p, &uiInfo.aliasList[uiInfo.aliasCount].name)
			    || !String_Parse(p, &uiInfo.aliasList[uiInfo.aliasCount].ai)
			    || !String_Parse(p, &uiInfo.aliasList[uiInfo.aliasCount].action)) {
				return qfalse;
			}

			Com_Printf("Loaded character alias %s using character ai %s.\n",
				   uiInfo.aliasList[uiInfo.aliasCount].name, uiInfo.aliasList[uiInfo.aliasCount].ai);
			if (uiInfo.aliasCount < MAX_ALIASES) {
				uiInfo.aliasCount++;
			} else {
				Com_Printf("Too many aliases, last alias replaced!\n");
			}

			token = COM_ParseExt(p, qtrue);
			if (token[0] != '}') {
				return qfalse;
			}
		}
	}

	//Makro - unreachable
	//return qfalse;
}

// mode 
// 0 - high level parsing
// 1 - team parsing
// 2 - character parsing
static void UI_ParseTeamInfo(const char *teamFile)
{
	char *token;
	char *p;
	char *buff = NULL;

	//static int mode = 0; TTimo: unused

	buff = GetMenuBuffer(teamFile);
	if (!buff) {
		return;
	}

	p = buff;

	INFINITE_LOOP {
		token = COM_ParseExt(&p, qtrue);
		if (!token || token[0] == 0 || token[0] == '}') {
			break;
		}

		if (Q_stricmp(token, "}") == 0) {
			break;
		}

		if (Q_stricmp(token, "teams") == 0) {

			if (Team_Parse(&p)) {
				continue;
			} else {
				break;
			}
		}

		if (Q_stricmp(token, "characters") == 0) {
			Character_Parse(&p);
		}

		if (Q_stricmp(token, "aliases") == 0) {
			Alias_Parse(&p);
		}

	}

}

static qboolean GameType_Parse(char **p, qboolean join)
{
/*
//Sample section

joingametypes {
  { "All" -1 }
  { "Free For All" 0 }
  { "Teamplay" 4 } 
}
*/
	char *token;

	token = COM_ParseExt(p, qtrue);

	if (token[0] != '{') {
		return qfalse;
	}

	if (join) {
		uiInfo.numJoinGameTypes = 0;
	} else {
		uiInfo.numGameTypes = 0;
	}

	INFINITE_LOOP {
		token = COM_ParseExt(p, qtrue);

		if (Q_stricmp(token, "}") == 0) {
			return qtrue;
		}

		if (!token || token[0] == 0) {
			return qfalse;
		}

		if (token[0] == '{') {
			// two tokens per line, character name and sex
			// Makro  - name and sex for gametypes ? Har har har
			//          They probably mean "name" and "value", heh
			//                      I guess copy/paste isn't a coder's best friend after all
			if (join) {
				if (!String_Parse(p, &uiInfo.joinGameTypes[uiInfo.numJoinGameTypes].gameType)
				    || !Int_Parse(p, &uiInfo.joinGameTypes[uiInfo.numJoinGameTypes].gtEnum)) {
					return qfalse;
				}
			} else {
				if (!String_Parse(p, &uiInfo.gameTypes[uiInfo.numGameTypes].gameType)
				    || !Int_Parse(p, &uiInfo.gameTypes[uiInfo.numGameTypes].gtEnum)) {
					return qfalse;
				}
			}

			if (join) {
				if (uiInfo.numJoinGameTypes < MAX_GAMETYPES) {
					uiInfo.numJoinGameTypes++;
				} else {
					Com_Printf("Too many net game types, last one replace!\n");
				}
			} else {
				if (uiInfo.numGameTypes < MAX_GAMETYPES) {
					uiInfo.numGameTypes++;
				} else {
					Com_Printf("Too many game types, last one replace!\n");
				}
			}

			token = COM_ParseExt(p, qtrue);
			if (token[0] != '}') {
				return qfalse;
			}
		}
	}
	//Makro - unreachable
	//return qfalse;
}

static qboolean MapList_Parse(char **p)
{
	char *token;

	token = COM_ParseExt(p, qtrue);

	if (token[0] != '{') {
		return qfalse;
	}

	uiInfo.mapCount = 0;

	INFINITE_LOOP {
		token = COM_ParseExt(p, qtrue);

		if (Q_stricmp(token, "}") == 0) {
			return qtrue;
		}

		if (!token || token[0] == 0) {
			return qfalse;
		}

		if (token[0] == '{') {
			if (!String_Parse(p, &uiInfo.mapList[uiInfo.mapCount].mapName)
			    || !String_Parse(p, &uiInfo.mapList[uiInfo.mapCount].mapLoadName)
			    || !Int_Parse(p, &uiInfo.mapList[uiInfo.mapCount].teamMembers)) {
				return qfalse;
			}

			if (!String_Parse(p, &uiInfo.mapList[uiInfo.mapCount].opponentName)) {
				return qfalse;
			}

			uiInfo.mapList[uiInfo.mapCount].typeBits = 0;

			INFINITE_LOOP {
				token = COM_ParseExt(p, qtrue);
				if (token[0] >= '0' && token[0] <= '9') {
					uiInfo.mapList[uiInfo.mapCount].typeBits |= (1 << (token[0] - 0x030));
					if (!Int_Parse(p, &uiInfo.mapList[uiInfo.mapCount].timeToBeat[token[0] - 0x30])) {
						return qfalse;
					}
				} else {
					break;
				}
			}

			//mapList[mapCount].imageName = String_Alloc(va("levelshots/%s", mapList[mapCount].mapLoadName));
			//if (uiInfo.mapCount == 0) {
			// only load the first cinematic, selection loads the others
			//  uiInfo.mapList[uiInfo.mapCount].cinematic = trap_CIN_PlayCinematic(va("%s.roq",uiInfo.mapList[uiInfo.mapCount].mapLoadName), qfalse, qfalse, qtrue, 0, 0, 0, 0);
			//}
			uiInfo.mapList[uiInfo.mapCount].cinematic = -1;
			uiInfo.mapList[uiInfo.mapCount].levelShot =
			    trap_R_RegisterShaderNoMip(va
						       ("levelshots/%s_small",
							uiInfo.mapList[uiInfo.mapCount].mapLoadName));

			if (uiInfo.mapCount < MAX_MAPS) {
				uiInfo.mapCount++;
			} else {
				Com_Printf("Too many maps, last one replaced!\n");
			}
		}
	}
	//Makro - unreachable
	//return qfalse;
}

static void UI_ParseGameInfo(const char *teamFile)
{
	char *token;
	char *p;
	char *buff = NULL;

	//int mode = 0; TTimo: unused

	buff = GetMenuBuffer(teamFile);
	if (!buff) {
		return;
	}

	p = buff;

	INFINITE_LOOP {
		token = COM_ParseExt(&p, qtrue);
		if (!token || token[0] == 0 || token[0] == '}') {
			break;
		}

		if (Q_stricmp(token, "}") == 0) {
			break;
		}

		if (Q_stricmp(token, "gametypes") == 0) {

			if (GameType_Parse(&p, qfalse)) {
				continue;
			} else {
				break;
			}
		}

		if (Q_stricmp(token, "joingametypes") == 0) {

			if (GameType_Parse(&p, qtrue)) {
				continue;
			} else {
				break;
			}
		}

		if (Q_stricmp(token, "maps") == 0) {
			// start a new menu
			MapList_Parse(&p);
		}

	}
}

static void UI_Pause(qboolean b)
{
	if (b) {
		// pause the game and set the ui keycatcher
		trap_Cvar_Set("cl_paused", "1");
		trap_Key_SetCatcher(KEYCATCH_UI);
	} else {
		// unpause the game and clear the ui keycatcher
		trap_Key_SetCatcher(trap_Key_GetCatcher() & ~KEYCATCH_UI);
		trap_Key_ClearStates();
		trap_Cvar_Set("cl_paused", "0");
	}
}

//Makro - not used anywhere
/*
#ifndef MISSIONPACK // bk001206
static int UI_OwnerDraw_Width(int ownerDraw) {
  // bk001205 - LCC missing return value
  return 0;
}
#endif
*/

static int UI_PlayCinematic(const char *name, float x, float y, float w, float h)
{
	return trap_CIN_PlayCinematic(name, x, y, w, h, (CIN_loop | CIN_silent));
}

static void UI_StopCinematic(int handle)
{
	if (handle >= 0) {
		trap_CIN_StopCinematic(handle);
	} else {
		handle = abs(handle);
		if (handle == UI_MAPCINEMATIC) {
			if (uiInfo.mapList[ui_currentMap.integer].cinematic >= 0) {
				trap_CIN_StopCinematic(uiInfo.mapList[ui_currentMap.integer].cinematic);
				uiInfo.mapList[ui_currentMap.integer].cinematic = -1;
			}
		} else if (handle == UI_NETMAPCINEMATIC) {
			if (uiInfo.serverStatus.currentServerCinematic >= 0) {
				trap_CIN_StopCinematic(uiInfo.serverStatus.currentServerCinematic);
				uiInfo.serverStatus.currentServerCinematic = -1;
			}
		} else if (handle == UI_CLANCINEMATIC) {
			int i = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_teamName"));

			if (i >= 0 && i < uiInfo.teamCount) {
				if (uiInfo.teamList[i].cinematic >= 0) {
					trap_CIN_StopCinematic(uiInfo.teamList[i].cinematic);
					uiInfo.teamList[i].cinematic = -1;
				}
			}
		}
	}
}

static void UI_DrawCinematic(int handle, float x, float y, float w, float h)
{
	trap_CIN_SetExtents(handle, x, y, w, h);
	trap_CIN_DrawCinematic(handle);
}

static void UI_RunCinematicFrame(int handle)
{
	trap_CIN_RunCinematic(handle);
}

/*
=================
PlayerModel_BuildList
=================
*/
static void UI_BuildQ3Model_List(void)
{
	int numdirs;
	int numfiles;
	char dirlist[2048];
	char filelist[2048];
	char skinname[64], currentSkin[64];
	char scratch[256];
	char *dirptr;
	char *fileptr;
	int i;
	int j, k, dirty;
	int dirlen;
	int filelen;

	uiInfo.q3HeadCount = 0;
	//Makro - save current model
	trap_Cvar_VariableStringBuffer("model", currentSkin, sizeof(currentSkin));

	// iterate directory of all player models
	numdirs = trap_FS_GetFileList("models/players", "/", dirlist, 2048);
	dirptr = dirlist;

	for (i = 0; i < numdirs && uiInfo.q3HeadCount < MAX_PLAYERMODELS; i++, dirptr += dirlen + 1) {
		dirlen = strlen(dirptr);

		if (dirlen && dirptr[dirlen - 1] == '/')
			dirptr[dirlen - 1] = '\0';

		if (!strcmp(dirptr, ".") || !strcmp(dirptr, ".."))
			continue;

		// NiceAss:
		// Makro - added abbey
		//if (strcmp(dirptr,"grunt") && strcmp(dirptr, "abbey"))
		//      continue;

		// Makro - new code
		if (!UI_FileExists(va("models/players/%s/rq3model.cfg", dirptr)))
			continue;

		// iterate all skin files in directory
		numfiles = trap_FS_GetFileList(va("models/players/%s", dirptr), "tga", filelist, 2048);
		fileptr = filelist;
		for (j = 0; j < numfiles && uiInfo.q3HeadCount < MAX_PLAYERMODELS; j++, fileptr += filelen + 1) {
			filelen = strlen(fileptr);

			COM_StripExtension(fileptr, skinname);

			// look for icon_????
			if (Q_stricmpn(skinname, "icon_", 5) == 0
			    && !(Q_stricmp(skinname, "icon_blue") == 0 || Q_stricmp(skinname, "icon_red") == 0)) {
				if (Q_stricmp(skinname, "icon_default") == 0) {
					Com_sprintf(scratch, sizeof(scratch), dirptr);
				} else {
					Com_sprintf(scratch, sizeof(scratch), "%s/%s", dirptr, skinname + 5);
				}
				dirty = 0;
				for (k = 0; k < uiInfo.q3HeadCount; k++) {
					//Makro - changed from uiInfo.q3HeadNames[uiInfo.q3HeadCount] !
					if (!Q_stricmp(scratch, uiInfo.q3HeadNames[k])) {
						dirty = 1;
						break;
					}
				}
				if (!dirty) {
					Com_sprintf(uiInfo.q3HeadNames[uiInfo.q3HeadCount],
						    sizeof(uiInfo.q3HeadNames[uiInfo.q3HeadCount]), scratch);
					//Makro - see if this model is the selected one
					if (!strcmp(currentSkin, scratch)) {
						uiInfo.q3SelectedHead = uiInfo.q3HeadCount;
					}
					uiInfo.q3HeadIcons[uiInfo.q3HeadCount++] =
					    trap_R_RegisterShaderNoMip(va("models/players/%s/%s", dirptr, skinname));
				}
			}

		}
	}

}

//Makro - custom functions to start/stop background music

void UI_RQ3_StopBackgroundTrack(void)
{
	trap_S_StopBackgroundTrack();
	uiInfo.playingIntro = NULL;
	uiInfo.playingLoop = NULL;
#ifdef DEBUG
	Com_Printf("Stopped music\n");
#endif
}

void UI_RQ3_StartBackgroundTrack(const char *intro, const char *loop)
{
	if (uiInfo.playingIntro != intro || uiInfo.playingLoop != loop) {
		uiInfo.playingIntro = intro;
		uiInfo.playingLoop = loop;
		trap_S_StartBackgroundTrack(intro, loop);
#ifdef DEBUG
		Com_Printf("Started music: %s %s\n", intro, loop);
#endif
	}
}

void UI_RenderScene(const refdef_t *ref)
{
	trap_R_RenderScene(ref);
	trap_R_ClearScene();
}

void UI_Render2DScene()
{
	if (uiInfo.uiDC.pendingPolys == 0)
		return;
	UI_RenderScene(&uiInfo.uiDC.scene2D);
	uiInfo.uiDC.pendingPolys = 0;
}

void UI_ClearScene()
{
	if (uiInfo.uiDC.pendingPolys)
	{
		UI_Render2DScene();
	}
	trap_R_ClearScene();
}

void UI_DrawPolyStretchPic(float x, float y, float w, float h, float s1, float t1, float s2, float t2, qhandle_t hShader, qboolean adjust)
{
	if (uiInfo.uiDC.pendingPolys)
	{
		UI_Render2DScene();
	}
	if (adjust)
	{
		UI_AdjustFrom640(&x, &y, &w, &h);
	}
	trap_R_DrawStretchPic(x, y, w, h, s1, t1, s2, t2, hShader);
}

static void UI_MakeExtensionsList()
{
	char *eptr;

	uiInfo.uiDC.numGlExtensions = 0;

	// build null terminated extension strings

	eptr = uiInfo.uiDC.glconfig.extensions_string;
	while (*eptr && uiInfo.uiDC.numGlExtensions < MAX_NUM_GL_EXTENSIONS)
	{
		// skip whitespace
		while (*eptr && *eptr == ' ')
			*eptr++ = '\0';

		// track start of valid string
		if (*eptr && *eptr != ' ')
			uiInfo.uiDC.glExtensions[uiInfo.uiDC.numGlExtensions++] = eptr;

		while (*eptr && *eptr != ' ')
			eptr++;

		// end token
		if (*eptr)
			*eptr++ = '\0';
	}
}


/*
=================
UI_Init
=================
*/
void _UI_Init(qboolean inGameLoad)
{
	const char *menuSet;
	//Makro - added
	char info[MAX_INFO_STRING];
	//
	int start;
	qboolean needRestart = qfalse;

	//uiInfo.inGameLoad = inGameLoad;

	UI_RegisterCvars();
	UI_InitMemory();

	
	// cache redundant calulations
	trap_GetGlconfig(&uiInfo.uiDC.glconfig);

	UI_MakeExtensionsList();

	//Makro - 8192 polys should be enough for the new UI...
	if (ui_maxpolys.integer < 8192)
	{
		trap_Cvar_SetValue("r_maxpolys", 8192);
		needRestart = qtrue;
	}

	//Makro - 32768 poly verts should be enough for the new UI...
	if (ui_maxpolyverts.integer < 32768)
	{
		trap_Cvar_SetValue("r_maxpolyverts", 32768);
		needRestart = qtrue;
	}
	if (needRestart)
	{
		trap_Cmd_ExecuteText(EXEC_INSERT, "vid_restart");
	}

	// for 640x480 virtualized screen
	uiInfo.uiDC.yscale = uiInfo.uiDC.glconfig.vidHeight * (1.0 / 480.0);
	uiInfo.uiDC.xscale = uiInfo.uiDC.glconfig.vidWidth * (1.0 / 640.0);
	if (uiInfo.uiDC.glconfig.vidWidth * 480 > uiInfo.uiDC.glconfig.vidHeight * 640) {
		// wide screen
		uiInfo.uiDC.bias =
		    0.5 * (uiInfo.uiDC.glconfig.vidWidth - (uiInfo.uiDC.glconfig.vidHeight * (640.0 / 480.0)));
	} else {
		// no wide screen
		uiInfo.uiDC.bias = 0;
	}

	//Makro - set up 2D scene
	memset(&uiInfo.uiDC.scene2D, 0, sizeof(&uiInfo.uiDC.scene2D));
	uiInfo.uiDC.scene2D.x = 0;
	uiInfo.uiDC.scene2D.y = 0;
	uiInfo.uiDC.scene2D.width = 640 * uiInfo.uiDC.xscale;
	uiInfo.uiDC.scene2D.height = 480 * uiInfo.uiDC.yscale ;
	uiInfo.uiDC.scene2D.fov_x = 90;
	uiInfo.uiDC.scene2D.fov_y = 73.739795291688f;
	uiInfo.uiDC.scene2D.rdflags = RDF_NOWORLDMODEL | RDF_NOFOG;
	AxisClear(uiInfo.uiDC.scene2D.viewaxis);

	
	//Makro - default values for the key bind strings
	uiInfo.keyBindStatus1 = KEYBIND_STATUS1;
	uiInfo.keyBindStatus2 = KEYBIND_STATUS2;

	//Makro - empty startup menu text
	*uiInfo.startupText = 0;

	//UI_Load();
	uiInfo.uiDC.registerShaderNoMip = &trap_R_RegisterShaderNoMip;
	uiInfo.uiDC.setColor = &UI_SetColor;
	uiInfo.uiDC.drawHandlePic = &UI_DrawHandlePic;
	//uiInfo.uiDC.drawStretchPic = &trap_R_DrawStretchPic;
	uiInfo.uiDC.drawStretchPic = &UI_DrawPolyStretchPic;
	//Makro - angled pictures
	uiInfo.uiDC.drawAngledPic = &UI_DrawAngledPic;
	uiInfo.uiDC.drawText = &Text_Paint;
	//Makro - angled text
	uiInfo.uiDC.drawAngledText = &Text_PaintAngled;
	uiInfo.uiDC.textWidth = &Text_Width;
	uiInfo.uiDC.textHeight = &Text_Height;
	uiInfo.uiDC.registerModel = &trap_R_RegisterModel;
	uiInfo.uiDC.modelBounds = &trap_R_ModelBounds;
	uiInfo.uiDC.fillRect = &UI_FillRect;
	uiInfo.uiDC.drawRect = &_UI_DrawRect;
	uiInfo.uiDC.drawSides = &_UI_DrawSides;
	uiInfo.uiDC.drawTopBottom = &_UI_DrawTopBottom;
	//Makro - angled rectangles
	uiInfo.uiDC.drawAngledRect = &_UI_DrawAngledRect;
	//Makro - changed
	//uiInfo.uiDC.clearScene = &trap_R_ClearScene;
	uiInfo.uiDC.clearScene = &UI_ClearScene;
	uiInfo.uiDC.addRefEntityToScene = &trap_R_AddRefEntityToScene;
	//uiInfo.uiDC.renderScene = &trap_R_RenderScene;
	uiInfo.uiDC.renderScene = &UI_RenderScene;
	uiInfo.uiDC.registerFont = &trap_R_RegisterFont;
	uiInfo.uiDC.ownerDrawItem = &UI_OwnerDraw;
	uiInfo.uiDC.getValue = &UI_GetValue;
	uiInfo.uiDC.ownerDrawVisible = &UI_OwnerDrawVisible;
	uiInfo.uiDC.runScript = &UI_RunMenuScript;
	uiInfo.uiDC.getTeamColor = &UI_GetTeamColor;
	uiInfo.uiDC.setCVar = trap_Cvar_Set;
	uiInfo.uiDC.getCVarString = trap_Cvar_VariableStringBuffer;
	uiInfo.uiDC.getCVarValue = trap_Cvar_VariableValue;
	uiInfo.uiDC.drawTextWithCursor = &Text_PaintWithCursor;
	//Makro - items using vectors
	uiInfo.uiDC.drawAngledTextWithCursor = &Text_PaintWithCursorAngled;
	uiInfo.uiDC.setOverstrikeMode = &trap_Key_SetOverstrikeMode;
	uiInfo.uiDC.getOverstrikeMode = &trap_Key_GetOverstrikeMode;
	uiInfo.uiDC.startLocalSound = &trap_S_StartLocalSound;
	uiInfo.uiDC.ownerDrawHandleKey = &UI_OwnerDrawHandleKey;
	uiInfo.uiDC.feederCount = &UI_FeederCount;
	uiInfo.uiDC.feederItemImage = &UI_FeederItemImage;
	uiInfo.uiDC.feederItemText = &UI_FeederItemText;
	uiInfo.uiDC.feederSelection = &UI_FeederSelection;
	uiInfo.uiDC.setBinding = &trap_Key_SetBinding;
	uiInfo.uiDC.getBindingBuf = &trap_Key_GetBindingBuf;
	uiInfo.uiDC.keynumToStringBuf = &trap_Key_KeynumToStringBuf;
	uiInfo.uiDC.executeText = &trap_Cmd_ExecuteText;
	uiInfo.uiDC.Error = &Com_Error;
	uiInfo.uiDC.Print = &Com_Printf;
	uiInfo.uiDC.Pause = &UI_Pause;
	uiInfo.uiDC.ownerDrawWidth = &UI_OwnerDrawWidth;
	uiInfo.uiDC.registerSound = &trap_S_RegisterSound;
	//Makro - custom functions
	//uiInfo.uiDC.startBackgroundTrack = &trap_S_StartBackgroundTrack;
	//uiInfo.uiDC.stopBackgroundTrack = &trap_S_StopBackgroundTrack;
	uiInfo.uiDC.startBackgroundTrack = &UI_RQ3_StartBackgroundTrack;
	uiInfo.uiDC.stopBackgroundTrack = &UI_RQ3_StopBackgroundTrack;
	uiInfo.uiDC.playCinematic = &UI_PlayCinematic;
	uiInfo.uiDC.stopCinematic = &UI_StopCinematic;
	uiInfo.uiDC.drawCinematic = &UI_DrawCinematic;
	uiInfo.uiDC.runCinematicFrame = &UI_RunCinematicFrame;

	Init_Display(&uiInfo.uiDC);

	String_Init();

	uiInfo.uiDC.cursor = trap_R_RegisterShaderNoMip("menu/art/3_cursor2");
	uiInfo.uiDC.whiteShader = trap_R_RegisterShaderNoMip("white");
	//Makro - added; almost useless
	uiInfo.uiDC.selectShader = trap_R_RegisterShaderNoMip("selectshader");

	AssetCache();

	start = trap_Milliseconds();

	uiInfo.teamCount = 0;
	uiInfo.characterCount = 0;
	uiInfo.aliasCount = 0;

#ifdef PRE_RELEASE_TADEMO
	UI_ParseTeamInfo("demoteaminfo.txt");
	UI_ParseGameInfo("demogameinfo.txt");
#else
	UI_ParseTeamInfo("teaminfo.txt");
	UI_LoadTeams();
	UI_ParseGameInfo("gameinfo.txt");
#endif

	menuSet = UI_Cvar_VariableString("ui_menuFiles");
	if (menuSet == NULL || menuSet[0] == '\0') {
		menuSet = "ui/menus.txt";
	}
#if 0
	if (uiInfo.inGameLoad) {
		UI_LoadMenus("ui/ingame.txt", qtrue);
	} else {		// bk010222: left this: UI_LoadMenus(menuSet, qtrue);
	}
#else
	UI_LoadMenus(menuSet, qtrue);
	UI_LoadMenus("ui/ingame.txt", qfalse);
#endif

	Menus_CloseAll();

	trap_LAN_LoadCachedServers();
	UI_LoadBestScores(uiInfo.mapList[ui_currentMap.integer].mapLoadName,
			  uiInfo.gameTypes[ui_gameType.integer].gtEnum);

	UI_BuildQ3Model_List();
	UI_LoadBots();

	// sets defaults for ui temp cvars
	uiInfo.effectsColor = gamecodetoui[(int) trap_Cvar_VariableValue("color1") - 1];
	uiInfo.currentCrosshair = (int) trap_Cvar_VariableValue("cg_drawCrosshair");

	trap_Cvar_Set("ui_mousePitch", (trap_Cvar_VariableValue("m_pitch") >= 0) ? "0" : "1");

	//Makro - save the music volume
	uiInfo.oldMusicVol = trap_Cvar_VariableValue("s_musicvolume");
	uiInfo.savedMusicVol = qfalse;

	//Makro - music files being played
	uiInfo.playingIntro = NULL;
	uiInfo.playingLoop = NULL;

	//Makro - set default bot skill to medium
	uiInfo.skillIndex = 2;
	//Makro - set default net filter index to 0
	trap_Cvar_Set("ui_serverFilterType", "0");

	//Makro - read item/weapon banning info
	trap_GetConfigString(CS_SERVERINFO, info, sizeof(info));
	uiInfo.weapBan = atoi(Info_ValueForKey(info, "g_RQ3_weaponBan"));
	uiInfo.itemBan = atoi(Info_ValueForKey(info, "g_RQ3_itemBan"));
	
	uiInfo.serverStatus.currentServerCinematic = -1;
	uiInfo.previewMovie = -1;

	if (trap_Cvar_VariableValue("ui_reaction33FirstRun") == 0) {
		trap_Cvar_Set("s_volume", "0.8");
		trap_Cvar_Set("s_musicvolume", "0.5");
		trap_Cvar_Set("ui_reaction33FirstRun", "1");
	}

	trap_Cvar_Register(NULL, "debug_protocol", "", 0);

	trap_Cvar_Set("ui_actualNetGameType", va("%d", ui_netGameType.integer));

	uiInfo.uiDC.cursorx = 320;
	uiInfo.uiDC.cursory = 240;

	//Makro - keep the cursor visible for 5 seconds
	uiInfo.uiDC.mouseMoveTime = trap_Milliseconds() + 5000;
}

/*
=================
UI_KeyEvent
=================
*/
void _UI_KeyEvent(int key, qboolean down)
{
	//Makro - for the cursor
	if (key == K_MOUSE1)
	{
		uiInfo.uiDC.mouseDown[0] = down;
		uiInfo.uiDC.mouseMoveTime = uiInfo.uiDC.realTime;
		Vector2Set(uiInfo.uiDC.mouseDownPos, uiInfo.uiDC.cursorx, uiInfo.uiDC.cursory);
	} else if (key == K_MOUSE2) {
		uiInfo.uiDC.mouseDown[1] = down;
		uiInfo.uiDC.mouseMoveTime = uiInfo.uiDC.realTime;
		Vector2Set(uiInfo.uiDC.mouseDownPos, uiInfo.uiDC.cursorx, uiInfo.uiDC.cursory);
	} else if (key == K_MOUSE3) {
		uiInfo.uiDC.mouseDown[2] = down;
		uiInfo.uiDC.mouseMoveTime = uiInfo.uiDC.realTime;
		Vector2Set(uiInfo.uiDC.mouseDownPos, uiInfo.uiDC.cursorx, uiInfo.uiDC.cursory);
	}

	if (Menu_Count() > 0) {
		menuDef_t *menu = Menu_GetFocused();

		if (menu) {
			if (key == K_ESCAPE && down && !Menus_AnyFullScreenVisible()) {
				Menus_CloseAll();
			} else {
				Menu_HandleKey(menu, key, down);
			}
		} else {
			trap_Key_SetCatcher(trap_Key_GetCatcher() & ~KEYCATCH_UI);
			trap_Key_ClearStates();
			trap_Cvar_Set("cl_paused", "0");
		}
	}
	//if ((s > 0) && (s != menu_null_sound)) {
	//  trap_S_StartLocalSound( s, CHAN_LOCAL_SOUND );
	//}
}

/*
=================
UI_MouseEvent
=================
*/
void _UI_MouseEvent(int dx, int dy)
{
	//Makro - added tablet code
	if (ui_RQ3_tabletMode.integer)
	{
		uiInfo.uiDC.cursorx = (int) (SCREEN_WIDTH / 2.0f +
			(float) dx * SCREEN_WIDTH / uiInfo.uiDC.glconfig.vidWidth);
		uiInfo.uiDC.cursory = (int) (SCREEN_HEIGHT / 2.0f +
			(float) dy * SCREEN_HEIGHT / uiInfo.uiDC.glconfig.vidHeight);
	} else {
		// update mouse screen position
		uiInfo.uiDC.cursorx += dx;
		uiInfo.uiDC.cursory += dy;
	}

	if (uiInfo.uiDC.cursorx < 0)
		uiInfo.uiDC.cursorx = 0;
	else if (uiInfo.uiDC.cursorx > SCREEN_WIDTH)
		uiInfo.uiDC.cursorx = SCREEN_WIDTH;

	if (uiInfo.uiDC.cursory < 0)
		uiInfo.uiDC.cursory = 0;
	else if (uiInfo.uiDC.cursory > SCREEN_HEIGHT)
		uiInfo.uiDC.cursory = SCREEN_HEIGHT;

	if (Menu_Count() > 0) {
		//menuDef_t *menu = Menu_GetFocused();
		//Menu_HandleMouseMove(menu, uiInfo.uiDC.cursorx, uiInfo.uiDC.cursory);
		Display_MouseMove(g_anchoredMenu, uiInfo.uiDC.cursorx, uiInfo.uiDC.cursory);
	}

	//Makro - update the time
	uiInfo.uiDC.mouseMoveTime = uiInfo.uiDC.realTime;
}

void UI_LoadNonIngame()
{
	const char *menuSet = UI_Cvar_VariableString("ui_menuFiles");

	if (menuSet == NULL || menuSet[0] == '\0') {
		menuSet = "ui/menus.txt";
	}
	UI_LoadMenus(menuSet, qfalse);
	uiInfo.inGameLoad = qfalse;
}

void _UI_SetActiveMenu(uiMenuCommand_t menu)
{
	char buf[256];

	// this should be the ONLY way the menu system is brought up
	// enusure minumum menu data is cached
	if (Menu_Count() > 0) {
		vec3_t v;

		v[0] = v[1] = v[2] = 0;
		switch (menu) {
		case UIMENU_NONE:
			trap_Key_SetCatcher(trap_Key_GetCatcher() & ~KEYCATCH_UI);
			trap_Key_ClearStates();
			trap_Cvar_Set("cl_paused", "0");
			Menus_CloseAll();

			return;
		case UIMENU_MAIN:
			//trap_Cvar_Set( "sv_killserver", "1" );
			trap_Key_SetCatcher(KEYCATCH_UI);
			//trap_S_StartLocalSound( trap_S_RegisterSound("sound/misc/menu_background.wav", qfalse) , CHAN_LOCAL_SOUND );
			//trap_S_StartBackgroundTrack("sound/misc/menu_background.wav", NULL);
			if (uiInfo.inGameLoad) {
				UI_LoadNonIngame();
			}
			Menus_CloseAll();
			Menus_ActivateByName("main", qfalse);
			trap_Cvar_VariableStringBuffer("com_errorMessage", buf, sizeof(buf));
			if (strlen(buf)) {
				if (!ui_singlePlayerActive.integer) {
					Menus_ActivateByName("error_popmenu", qfalse);
				} else {
					trap_Cvar_Set("com_errorMessage", "");
				}
			//Makro - check com_hunkmegs
			} else {
				if ((int)trap_Cvar_VariableValue("com_hunkMegs") < 256)
				{
					trap_Cvar_SetValue("com_hunkMegs", 256);
					Menus_ActivateByName("memory_popmenu", qfalse);
				};
			}
			return;
		case UIMENU_TEAM:
			trap_Key_SetCatcher(KEYCATCH_UI);
			Menus_ActivateByName("team", qfalse);
			return;
		case UIMENU_NEED_CD:
			// no cd check in TA
			//trap_Key_SetCatcher( KEYCATCH_UI );
			//Menus_ActivateByName("needcd");
			//UI_ConfirmMenu( "Insert the CD", NULL, NeedCDAction );
			return;
		case UIMENU_BAD_CD_KEY:
			// no cd check in TA
			//trap_Key_SetCatcher( KEYCATCH_UI );
			//Menus_ActivateByName("badcd");
			//UI_ConfirmMenu( "Bad CD Key", NULL, NeedCDKeyAction );
			return;
		case UIMENU_POSTGAME:
			//trap_Cvar_Set( "sv_killserver", "1" );
			trap_Key_SetCatcher(KEYCATCH_UI);
			if (uiInfo.inGameLoad) {
				UI_LoadNonIngame();
			}
			Menus_CloseAll();
			Menus_ActivateByName("endofgame", qfalse);
			//UI_ConfirmMenu( "Bad CD Key", NULL, NeedCDKeyAction );
			return;
		case UIMENU_INGAME:
			trap_Cvar_Set("cl_paused", "1");
			trap_Key_SetCatcher(KEYCATCH_UI);
			UI_BuildPlayerList();
			Menus_CloseAll();
			Menus_ActivateByName("ingame", qfalse);
			return;
		//Makro - RQ3 menus
		case UIMENU_RQ3_WEAPON:
			trap_Cvar_Set("cl_paused", "1");
			trap_Key_SetCatcher(KEYCATCH_UI);
			UI_BuildPlayerList();
			Menus_CloseAll();
			Menus_ActivateByName("ingame_weapon", qfalse);
			return;
		case UIMENU_RQ3_JOIN:
			trap_Cvar_Set("cl_paused", "1");
			trap_Key_SetCatcher(KEYCATCH_UI);
			UI_BuildPlayerList();
			Menus_CloseAll();
			if (trap_Cvar_VariableValue("g_gametype") >= GT_TEAM) {
				Menus_ActivateByName("ingame_join", qfalse);
			} else {
				Menus_ActivateByName("ingame_join_dm", qfalse);
			}
			return;
		case UIMENU_RQ3_TKOK:
			trap_Cvar_Set("cl_paused", "1");
			trap_Key_SetCatcher(KEYCATCH_UI);
			UI_BuildPlayerList();
			Menus_CloseAll();
			Menus_ActivateByName("ingame_tkok", qfalse);
			return;
		case UIMENU_RQ3_PRESETS:
			trap_Cvar_Set("cl_paused", "1");
			trap_Key_SetCatcher(KEYCATCH_UI);
			UI_BuildPlayerList();
			Menus_CloseAll();
			Menus_ActivateByName("ingame_presets", qfalse);
			return;
		}
	}
}

qboolean _UI_IsFullscreen(void)
{
	return Menus_AnyFullScreenVisible();
}

static connstate_t lastConnState;
static char lastLoadingText[MAX_INFO_VALUE];

static void UI_ReadableSize(char *buf, int bufsize, int value)
{
	if (value > 1024 * 1024 * 1024) {	// gigs
		Com_sprintf(buf, bufsize, "%d", value / (1024 * 1024 * 1024));
		Com_sprintf(buf + strlen(buf), bufsize - strlen(buf), ".%02d GB",
			    (value % (1024 * 1024 * 1024)) * 100 / (1024 * 1024 * 1024));
	} else if (value > 1024 * 1024) {	// megs
		Com_sprintf(buf, bufsize, "%d", value / (1024 * 1024));
		Com_sprintf(buf + strlen(buf), bufsize - strlen(buf), ".%02d MB",
			    (value % (1024 * 1024)) * 100 / (1024 * 1024));
	} else if (value > 1024) {	// kilos
		Com_sprintf(buf, bufsize, "%d KB", value / 1024);
	} else {		// bytes
		Com_sprintf(buf, bufsize, "%d bytes", value);
	}
}

// Assumes time is in msec
static void UI_PrintTime(char *buf, int bufsize, int time)
{
	time /= 1000;		// change to seconds

	if (time > 3600) {	// in the hours range
		Com_sprintf(buf, bufsize, "%d hr %d min", time / 3600, (time % 3600) / 60);
	} else if (time > 60) {	// mins
		Com_sprintf(buf, bufsize, "%d min %d sec", time / 60, time % 60);
	} else {		// secs
		Com_sprintf(buf, bufsize, "%d sec", time);
	}
}

void Text_PaintCenter(float x, float y, float scale, vec4_t color, const char *text, float adjust)
{
	int len = Text_Width(text, scale, 0);

	Text_Paint(x - len / 2, y, scale, color, text, 0, 0, 0, ITEM_TEXTSTYLE_SHADOWEDMORE, qfalse);
}

void Text_PaintCenter_AutoWrapped(float x, float y, float xmax, float ystep, float scale, vec4_t color, const char *str, float adjust)
{
	int width;
	char *s1, *s2, *s3;
	char c_bcp;
	char buf[1024];

	if (!str || str[0] == '\0')
		return;

	Q_strncpyz(buf, str, sizeof(buf));
	s1 = s2 = s3 = buf;

	INFINITE_LOOP {
		do {
			s3++;
		} while (*s3 != ' ' && *s3 != '\0');
		c_bcp = *s3;
		*s3 = '\0';
		width = Text_Width(s1, scale, 0);
		*s3 = c_bcp;
		if (width > xmax) {
			if (s1 == s2) {
				// fuck, don't have a clean cut, we'll overflow
				s2 = s3;
			}
			*s2 = '\0';
			Text_PaintCenter(x, y, scale, color, s1, adjust);
			y += ystep;
			if (c_bcp == '\0') {
				// that was the last word
				// we could start a new loop, but that wouldn't be much use
				// even if the word is too long, we would overflow it (see above)
				// so just print it now if needed
				s2++;
				if (*s2 != '\0')        // if we are printing an overflowing line we have s2 == s3
					Text_PaintCenter(x, y, scale, color, s2, adjust);
				break;
			}
			s2++;
			s1 = s2;
			s3 = s2;
		} else {
			s2 = s3;
			if (c_bcp == '\0')      // we reached the end
			{
				Text_PaintCenter(x, y, scale, color, s1, adjust);
				break;
			}
		}
	}
}

static void UI_DisplayDownloadInfo(const char *downloadName, float centerPoint, float yStart, float scale)
{
	static char dlText[] = "Downloading:";
	static char etaText[] = "Estimated time left:";
	static char xferText[] = "Transfer rate:";

	int downloadSize, downloadCount, downloadTime;
	char dlSizeBuf[64], totalSizeBuf[64], xferRateBuf[64], dlTimeBuf[64];
	int xferRate;
	int leftWidth;
	const char *s;

	downloadSize = trap_Cvar_VariableValue("cl_downloadSize");
	downloadCount = trap_Cvar_VariableValue("cl_downloadCount");
	downloadTime = trap_Cvar_VariableValue("cl_downloadTime");

	leftWidth = 320;

	UI_SetColor(colorWhite);
	Text_PaintCenter(centerPoint, yStart + 112, scale, colorWhite, dlText, 0);
	Text_PaintCenter(centerPoint, yStart + 192, scale, colorWhite, etaText, 0);
	Text_PaintCenter(centerPoint, yStart + 248, scale, colorWhite, xferText, 0);

	if (downloadSize > 0) {
		s = va("%s (%d%%)", downloadName, downloadCount * 100 / downloadSize);
	} else {
		s = downloadName;
	}

	Text_PaintCenter(centerPoint, yStart + 136, scale, colorWhite, s, 0);

	UI_ReadableSize(dlSizeBuf, sizeof dlSizeBuf, downloadCount);
	UI_ReadableSize(totalSizeBuf, sizeof totalSizeBuf, downloadSize);

	if (downloadCount < 4096 || !downloadTime) {
		Text_PaintCenter(leftWidth, yStart + 216, scale, colorWhite, "estimating", 0);
		Text_PaintCenter(leftWidth, yStart + 160, scale, colorWhite,
				 va("(%s of %s copied)", dlSizeBuf, totalSizeBuf), 0);
	} else {
		if ((uiInfo.uiDC.realTime - downloadTime) / 1000) {
			xferRate = downloadCount / ((uiInfo.uiDC.realTime - downloadTime) / 1000);
		} else {
			xferRate = 0;
		}
		UI_ReadableSize(xferRateBuf, sizeof xferRateBuf, xferRate);

		// Extrapolate estimated completion time
		if (downloadSize && xferRate) {
			int n = downloadSize / xferRate;	// estimated time for entire d/l in secs

			// We do it in K (/1024) because we'd overflow around 4MB
			UI_PrintTime(dlTimeBuf, sizeof dlTimeBuf,
				     (n - (((downloadCount / 1024) * n) / (downloadSize / 1024))) * 1000);

			Text_PaintCenter(leftWidth, yStart + 216, scale, colorWhite, dlTimeBuf, 0);
			Text_PaintCenter(leftWidth, yStart + 160, scale, colorWhite,
					 va("(%s of %s copied)", dlSizeBuf, totalSizeBuf), 0);
		} else {
			Text_PaintCenter(leftWidth, yStart + 216, scale, colorWhite, "estimating", 0);
			if (downloadSize) {
				Text_PaintCenter(leftWidth, yStart + 160, scale, colorWhite,
						 va("(%s of %s copied)", dlSizeBuf, totalSizeBuf), 0);
			} else {
				Text_PaintCenter(leftWidth, yStart + 160, scale, colorWhite,
						 va("(%s copied)", dlSizeBuf), 0);
			}
		}

		if (xferRate) {
			Text_PaintCenter(leftWidth, yStart + 272, scale, colorWhite, va("%s/Sec", xferRateBuf), 0);
		}
	}
}

/*
========================
UI_DrawConnectScreen

This will also be overlaid on the cgame info screen during loading
to prevent it from blinking away too rapidly on local or lan games.
========================
*/
void UI_DrawConnectScreen(qboolean overlay)
{
	char *s;
	uiClientState_t cstate;
	char info[MAX_INFO_VALUE];
	char text[256];
	float centerPoint, yStart, scale;

	menuDef_t *menu = Menus_FindByName("Connect");

	if (!overlay && menu) {
		Menu_Paint(menu, qtrue);
	}

	if (!overlay) {
		centerPoint = 320;
		yStart = 130;
		scale = 0.5f;
	} else {
		centerPoint = 320;
		yStart = 32;
		scale = 0.6f;
		return;
	}

	// see what information we should display
	trap_GetClientState(&cstate);

	info[0] = '\0';
	if (trap_GetConfigString(CS_SERVERINFO, info, sizeof(info))) {
		Text_PaintCenter(centerPoint, yStart, scale, colorWhite,
				 va("Loading %s", Info_ValueForKey(info, "mapname")), 0);
	}

	if (!Q_stricmp(cstate.servername, "localhost")) {
		Text_PaintCenter(centerPoint, yStart + 48, scale, colorWhite, va("Starting up..."),
				 ITEM_TEXTSTYLE_SHADOWEDMORE);
		//Q_strncpyz(uiInfo.startupText, "Starting up...", sizeof(uiInfo.startupText));
	} else {
		strcpy(text, va("Connecting to %s", cstate.servername));
		Text_PaintCenter(centerPoint, yStart + 48, scale, colorWhite, text, ITEM_TEXTSTYLE_SHADOWEDMORE);
		//Q_strncpyz(uiInfo.startupText, va("Connecting to %s", cstate.servername), sizeof(uiInfo.startupText));
	}

	// display global MOTD at bottom
	Text_PaintCenter(centerPoint, 600, scale, colorWhite, Info_ValueForKey(cstate.updateInfoString, "motd"), 0);
	// print any server info (server full, bad version, etc)
	if (cstate.connState < CA_CONNECTED) {
//		Text_PaintCenter(centerPoint, yStart + 176, scale, colorWhite, cstate.messageString, 0);
		Text_PaintCenter_AutoWrapped(centerPoint, yStart + 176, 630, 20, scale, colorWhite,
					cstate.messageString, 0);
	}

	if (lastConnState > cstate.connState) {
		lastLoadingText[0] = '\0';
	}
	lastConnState = cstate.connState;

	switch (cstate.connState) {
	case CA_CONNECTING:
		s = va("Awaiting connection...%i", cstate.connectPacketCount);
		break;
	case CA_CHALLENGING:
		s = va("Awaiting challenge...%i", cstate.connectPacketCount);
		break;
	case CA_CONNECTED:{
			char downloadName[MAX_INFO_VALUE];

			trap_Cvar_VariableStringBuffer("cl_downloadName", downloadName, sizeof(downloadName));
			if (*downloadName) {
				UI_DisplayDownloadInfo(downloadName, centerPoint, yStart, scale);
				return;
			}
		}
		s = "Awaiting gamestate...";
		break;
	case CA_LOADING:
		return;
	case CA_PRIMED:
		return;
	default:
		return;
	}

	if (Q_stricmp(cstate.servername, "localhost")) {
		Text_PaintCenter(centerPoint, yStart + 80, scale, colorWhite, s, 0);
	}

	// password required / connection rejected information goes here
}

/*
================
cvars
================
*/

typedef struct {
	vmCvar_t *vmCvar;
	char *cvarName;
	char *defaultString;
	int cvarFlags;
} cvarTable_t;

vmCvar_t ui_ffa_fraglimit;
vmCvar_t ui_ffa_timelimit;

vmCvar_t ui_tourney_fraglimit;
vmCvar_t ui_tourney_timelimit;

vmCvar_t ui_team_fraglimit;
vmCvar_t ui_team_timelimit;
vmCvar_t ui_team_friendly;

vmCvar_t ui_ctf_capturelimit;
vmCvar_t ui_ctf_timelimit;
vmCvar_t ui_ctf_friendly;

vmCvar_t ui_arenasFile;
vmCvar_t ui_botsFile;
vmCvar_t ui_spScores1;
vmCvar_t ui_spScores2;
vmCvar_t ui_spScores3;
vmCvar_t ui_spScores4;
vmCvar_t ui_spScores5;
vmCvar_t ui_spAwards;
vmCvar_t ui_spVideos;
vmCvar_t ui_spSkill;

vmCvar_t ui_spSelection;

vmCvar_t ui_browserMaster;
vmCvar_t ui_browserGameType;
vmCvar_t ui_browserSortKey;
vmCvar_t ui_browserShowFull;
vmCvar_t ui_browserShowEmpty;

vmCvar_t ui_brassTime;
vmCvar_t ui_drawCrosshair;
vmCvar_t ui_drawCrosshairNames;
vmCvar_t ui_marks;

vmCvar_t ui_server1;
vmCvar_t ui_server2;
vmCvar_t ui_server3;
vmCvar_t ui_server4;
vmCvar_t ui_server5;
vmCvar_t ui_server6;
vmCvar_t ui_server7;
vmCvar_t ui_server8;
vmCvar_t ui_server9;
vmCvar_t ui_server10;
vmCvar_t ui_server11;
vmCvar_t ui_server12;
vmCvar_t ui_server13;
vmCvar_t ui_server14;
vmCvar_t ui_server15;
vmCvar_t ui_server16;

vmCvar_t ui_cdkeychecked;

vmCvar_t ui_redteam;
vmCvar_t ui_redteam1;
vmCvar_t ui_redteam2;
vmCvar_t ui_redteam3;
vmCvar_t ui_redteam4;
vmCvar_t ui_redteam5;
vmCvar_t ui_blueteam;
vmCvar_t ui_blueteam1;
vmCvar_t ui_blueteam2;
vmCvar_t ui_blueteam3;
vmCvar_t ui_blueteam4;
vmCvar_t ui_blueteam5;
vmCvar_t ui_teamName;
vmCvar_t ui_dedicated;
vmCvar_t ui_gameType;
vmCvar_t ui_netGameType;
vmCvar_t ui_actualNetGameType;
vmCvar_t ui_joinGameType;
vmCvar_t ui_netSource;
vmCvar_t ui_serverFilterType;
vmCvar_t ui_opponentName;
vmCvar_t ui_menuFiles;
vmCvar_t ui_currentTier;
vmCvar_t ui_currentMap;
vmCvar_t ui_currentNetMap;
vmCvar_t ui_mapIndex;
vmCvar_t ui_currentOpponent;
vmCvar_t ui_selectedPlayer;
vmCvar_t ui_selectedPlayerName;
vmCvar_t ui_lastServerRefresh_0;
vmCvar_t ui_lastServerRefresh_1;
vmCvar_t ui_lastServerRefresh_2;
vmCvar_t ui_lastServerRefresh_3;
vmCvar_t ui_singlePlayerActive;
vmCvar_t ui_scoreAccuracy;
vmCvar_t ui_scoreImpressives;
vmCvar_t ui_scoreExcellents;
vmCvar_t ui_scoreCaptures;
vmCvar_t ui_scoreDefends;
vmCvar_t ui_scoreAssists;
vmCvar_t ui_scoreGauntlets;
vmCvar_t ui_scoreScore;
vmCvar_t ui_scorePerfect;
vmCvar_t ui_scoreTeam;
vmCvar_t ui_scoreBase;
vmCvar_t ui_scoreTimeBonus;
vmCvar_t ui_scoreSkillBonus;
vmCvar_t ui_scoreShutoutBonus;
vmCvar_t ui_scoreTime;
vmCvar_t ui_captureLimit;
vmCvar_t ui_fragLimit;
vmCvar_t ui_smallFont;
vmCvar_t ui_bigFont;
vmCvar_t ui_findPlayer;
vmCvar_t ui_Q3Model;
vmCvar_t ui_hudFiles;
vmCvar_t ui_recordSPDemo;
vmCvar_t ui_realCaptureLimit;
vmCvar_t ui_realWarmUp;
vmCvar_t ui_serverStatusTimeOut;

//Makro - cvar for player model display
vmCvar_t ui_RQ3_modelCommand;

//Makro - tablet support in the UI
vmCvar_t ui_RQ3_tabletMode;

//Makro - model cvar
vmCvar_t ui_RQ3_model;

//Makro - for the SSG crosshair preview
vmCvar_t ui_RQ3_ssgCrosshair;

//Makro - activate the weapon menu after a team join
vmCvar_t ui_RQ3_weapAfterJoin;
//Makro - team counts
//Handled in cgame now
//vmCvar_t      ui_RQ3_teamCount1;
//vmCvar_t      ui_RQ3_teamCount2;
//vmCvar_t      ui_RQ3_numSpectators;
//Makro - specify server option
vmCvar_t ui_RQ3_joinAddress;
vmCvar_t ui_RQ3_joinPort;
//Makro - demo name
vmCvar_t ui_RQ3_demoName;
//Makro - maxpolys hack
vmCvar_t ui_maxpolys;
vmCvar_t ui_maxpolyverts;
//Makro - matchmode settings
vmCvar_t ui_RQ3_timelimit;
vmCvar_t ui_RQ3_roundlimit;
vmCvar_t ui_RQ3_roundtimelimit;
vmCvar_t ui_RQ3_fraglimit;
vmCvar_t ui_RQ3_maxplayers;
vmCvar_t ui_RQ3_forceteamtalk;
vmCvar_t ui_RQ3_limchasecam;
vmCvar_t ui_RQ3_tgren;
vmCvar_t ui_RQ3_friendlyFire;
//Makro - in-game server info
vmCvar_t ui_RQ3_ingameDetails;
//Makro - ref pass
vmCvar_t ui_RQ3_refPassword;
//Makro - captain cvars
vmCvar_t ui_RQ3_teamName;
vmCvar_t ui_RQ3_teamModel;
//Makro - radio presets menu cvars
//1
vmCvar_t ui_RQ3_radioPreset1Desc;
vmCvar_t ui_RQ3_radioPreset1Script;
//2
vmCvar_t ui_RQ3_radioPreset2Desc;
vmCvar_t ui_RQ3_radioPreset2Script;
//3
vmCvar_t ui_RQ3_radioPreset3Desc;
vmCvar_t ui_RQ3_radioPreset3Script;
//4
vmCvar_t ui_RQ3_radioPreset4Desc;
vmCvar_t ui_RQ3_radioPreset4Script;
//5
vmCvar_t ui_RQ3_radioPreset5Desc;
vmCvar_t ui_RQ3_radioPreset5Script;
//6
vmCvar_t ui_RQ3_radioPreset6Desc;
vmCvar_t ui_RQ3_radioPreset6Script;
//7
vmCvar_t ui_RQ3_radioPreset7Desc;
vmCvar_t ui_RQ3_radioPreset7Script;
//8
vmCvar_t ui_RQ3_radioPreset8Desc;
vmCvar_t ui_RQ3_radioPreset8Script;
//9
vmCvar_t ui_RQ3_radioPreset9Desc;
vmCvar_t ui_RQ3_radioPreset9Script;
//10
vmCvar_t ui_RQ3_radioPreset10Desc;
vmCvar_t ui_RQ3_radioPreset10Script;

//Makro - player gender; irrelevant for now
vmCvar_t ui_RQ3_gender;


// bk001129 - made static to avoid aliasing
static cvarTable_t cvarTable[] = {
	{&ui_ffa_fraglimit, "ui_ffa_fraglimit", "20", CVAR_ARCHIVE},
	{&ui_ffa_timelimit, "ui_ffa_timelimit", "0", CVAR_ARCHIVE},

	{&ui_tourney_fraglimit, "ui_tourney_fraglimit", "0", CVAR_ARCHIVE},
	{&ui_tourney_timelimit, "ui_tourney_timelimit", "15", CVAR_ARCHIVE},

	{&ui_team_fraglimit, "ui_team_fraglimit", "0", CVAR_ARCHIVE},
	{&ui_team_timelimit, "ui_team_timelimit", "20", CVAR_ARCHIVE},
	{&ui_team_friendly, "ui_team_friendly", "1", CVAR_ARCHIVE},

	{&ui_ctf_capturelimit, "ui_ctf_capturelimit", "8", CVAR_ARCHIVE},
	{&ui_ctf_timelimit, "ui_ctf_timelimit", "30", CVAR_ARCHIVE},
	{&ui_ctf_friendly, "ui_ctf_friendly", "0", CVAR_ARCHIVE},

	{&ui_arenasFile, "g_arenasFile", "", CVAR_INIT | CVAR_ROM},
	{&ui_botsFile, "g_botsFile", "", CVAR_INIT | CVAR_ROM},
	{&ui_spScores1, "g_spScores1", "", CVAR_ARCHIVE | CVAR_ROM},
	{&ui_spScores2, "g_spScores2", "", CVAR_ARCHIVE | CVAR_ROM},
	{&ui_spScores3, "g_spScores3", "", CVAR_ARCHIVE | CVAR_ROM},
	{&ui_spScores4, "g_spScores4", "", CVAR_ARCHIVE | CVAR_ROM},
	{&ui_spScores5, "g_spScores5", "", CVAR_ARCHIVE | CVAR_ROM},
	{&ui_spAwards, "g_spAwards", "", CVAR_ARCHIVE | CVAR_ROM},
	{&ui_spVideos, "g_spVideos", "", CVAR_ARCHIVE | CVAR_ROM},
	{&ui_spSkill, "g_spSkill", "2", CVAR_ARCHIVE},

	{&ui_spSelection, "ui_spSelection", "", CVAR_ROM},

	{&ui_browserMaster, "ui_browserMaster", "0", CVAR_ARCHIVE},
	{&ui_browserGameType, "ui_browserGameType", "0", CVAR_ARCHIVE},
	{&ui_browserSortKey, "ui_browserSortKey", "4", CVAR_ARCHIVE},
	{&ui_browserShowFull, "ui_browserShowFull", "1", CVAR_ARCHIVE},
	{&ui_browserShowEmpty, "ui_browserShowEmpty", "1", CVAR_ARCHIVE},

	{&ui_brassTime, "cg_brassTime", "2500", CVAR_ARCHIVE},
	{&ui_drawCrosshair, "cg_drawCrosshair", "4", CVAR_ARCHIVE},
	{&ui_drawCrosshairNames, "cg_drawCrosshairNames", "1", CVAR_ARCHIVE},
	{&ui_marks, "cg_marks", "1", CVAR_ARCHIVE},

	{&ui_server1, "server1", "", CVAR_ARCHIVE},
	{&ui_server2, "server2", "", CVAR_ARCHIVE},
	{&ui_server3, "server3", "", CVAR_ARCHIVE},
	{&ui_server4, "server4", "", CVAR_ARCHIVE},
	{&ui_server5, "server5", "", CVAR_ARCHIVE},
	{&ui_server6, "server6", "", CVAR_ARCHIVE},
	{&ui_server7, "server7", "", CVAR_ARCHIVE},
	{&ui_server8, "server8", "", CVAR_ARCHIVE},
	{&ui_server9, "server9", "", CVAR_ARCHIVE},
	{&ui_server10, "server10", "", CVAR_ARCHIVE},
	{&ui_server11, "server11", "", CVAR_ARCHIVE},
	{&ui_server12, "server12", "", CVAR_ARCHIVE},
	{&ui_server13, "server13", "", CVAR_ARCHIVE},
	{&ui_server14, "server14", "", CVAR_ARCHIVE},
	{&ui_server15, "server15", "", CVAR_ARCHIVE},
	{&ui_server16, "server16", "", CVAR_ARCHIVE},
	{&ui_cdkeychecked, "ui_cdkeychecked", "0", CVAR_ROM},
	{&ui_new, "ui_new", "0", CVAR_TEMP},
	//Makro - renamed to ui_developer
	//{&ui_debug, "ui_debug", "0", CVAR_TEMP},
	{&ui_developer, "ui_developer", "0", CVAR_TEMP},
	{&ui_initialized, "ui_initialized", "0", CVAR_TEMP},
	{&ui_teamName, "ui_teamName", "Pagans", CVAR_ARCHIVE},
	{&ui_opponentName, "ui_opponentName", "Stroggs", CVAR_ARCHIVE},
	{&ui_redteam, "ui_redteam", "Pagans", CVAR_ARCHIVE},
	{&ui_blueteam, "ui_blueteam", "Stroggs", CVAR_ARCHIVE},
	{&ui_dedicated, "ui_dedicated", "0", CVAR_ARCHIVE},
	{&ui_gameType, "ui_gametype", "3", CVAR_ARCHIVE},
	{&ui_joinGameType, "ui_joinGametype", "0", CVAR_ARCHIVE},
	{&ui_netGameType, "ui_netGametype", "3", CVAR_ARCHIVE},
	{&ui_actualNetGameType, "ui_actualNetGametype", "3", CVAR_ARCHIVE},
	{&ui_redteam1, "ui_redteam1", "0", CVAR_ARCHIVE},
	{&ui_redteam2, "ui_redteam2", "0", CVAR_ARCHIVE},
	{&ui_redteam3, "ui_redteam3", "0", CVAR_ARCHIVE},
	{&ui_redteam4, "ui_redteam4", "0", CVAR_ARCHIVE},
	{&ui_redteam5, "ui_redteam5", "0", CVAR_ARCHIVE},
	{&ui_blueteam1, "ui_blueteam1", "0", CVAR_ARCHIVE},
	{&ui_blueteam2, "ui_blueteam2", "0", CVAR_ARCHIVE},
	{&ui_blueteam3, "ui_blueteam3", "0", CVAR_ARCHIVE},
	{&ui_blueteam4, "ui_blueteam4", "0", CVAR_ARCHIVE},
	{&ui_blueteam5, "ui_blueteam5", "0", CVAR_ARCHIVE},
	{&ui_netSource, "ui_netSource", "0", CVAR_ARCHIVE},
	{&ui_menuFiles, "ui_menuFiles", "ui/menus.txt", CVAR_ARCHIVE},
	{&ui_currentTier, "ui_currentTier", "0", CVAR_ARCHIVE},
	{&ui_currentMap, "ui_currentMap", "0", CVAR_ARCHIVE},
	{&ui_currentNetMap, "ui_currentNetMap", "0", CVAR_ARCHIVE},
	{&ui_mapIndex, "ui_mapIndex", "0", CVAR_ARCHIVE},
	{&ui_currentOpponent, "ui_currentOpponent", "0", CVAR_ARCHIVE},
	{&ui_selectedPlayer, "cg_selectedPlayer", "0", CVAR_ARCHIVE},
	{&ui_selectedPlayerName, "cg_selectedPlayerName", "", CVAR_ARCHIVE},
	{&ui_lastServerRefresh_0, "ui_lastServerRefresh_0", "", CVAR_ARCHIVE},
	{&ui_lastServerRefresh_1, "ui_lastServerRefresh_1", "", CVAR_ARCHIVE},
	{&ui_lastServerRefresh_2, "ui_lastServerRefresh_2", "", CVAR_ARCHIVE},
	{&ui_lastServerRefresh_3, "ui_lastServerRefresh_3", "", CVAR_ARCHIVE},
	{&ui_singlePlayerActive, "ui_singlePlayerActive", "0", 0},
	{&ui_scoreAccuracy, "ui_scoreAccuracy", "0", CVAR_ARCHIVE},
	{&ui_scoreImpressives, "ui_scoreImpressives", "0", CVAR_ARCHIVE},
	{&ui_scoreExcellents, "ui_scoreExcellents", "0", CVAR_ARCHIVE},
	{&ui_scoreCaptures, "ui_scoreCaptures", "0", CVAR_ARCHIVE},
	{&ui_scoreDefends, "ui_scoreDefends", "0", CVAR_ARCHIVE},
	{&ui_scoreAssists, "ui_scoreAssists", "0", CVAR_ARCHIVE},
	{&ui_scoreGauntlets, "ui_scoreGauntlets", "0", CVAR_ARCHIVE},
	{&ui_scoreScore, "ui_scoreScore", "0", CVAR_ARCHIVE},
	{&ui_scorePerfect, "ui_scorePerfect", "0", CVAR_ARCHIVE},
	{&ui_scoreTeam, "ui_scoreTeam", "0 to 0", CVAR_ARCHIVE},
	{&ui_scoreBase, "ui_scoreBase", "0", CVAR_ARCHIVE},
	{&ui_scoreTime, "ui_scoreTime", "00:00", CVAR_ARCHIVE},
	{&ui_scoreTimeBonus, "ui_scoreTimeBonus", "0", CVAR_ARCHIVE},
	{&ui_scoreSkillBonus, "ui_scoreSkillBonus", "0", CVAR_ARCHIVE},
	{&ui_scoreShutoutBonus, "ui_scoreShutoutBonus", "0", CVAR_ARCHIVE},
	{&ui_fragLimit, "ui_fragLimit", "10", 0},
	{&ui_captureLimit, "ui_captureLimit", "5", 0},
	{&ui_smallFont, "ui_smallFont", "0.25", CVAR_ARCHIVE},
	{&ui_bigFont, "ui_bigFont", "0.4", CVAR_ARCHIVE},
	//Makro - changed from Sarge
	{&ui_findPlayer, "ui_findPlayer", "Abbey", CVAR_ARCHIVE},
	//Makro - adding CVAR_ROM
	{&ui_Q3Model, "ui_q3model", "1", CVAR_ARCHIVE | CVAR_ROM},
	{&ui_hudFiles, "cg_hudFiles", "ui/hud.txt", CVAR_ARCHIVE},
	{&ui_recordSPDemo, "ui_recordSPDemo", "0", CVAR_ARCHIVE},
	{&ui_reaction33FirstRun, "ui_reaction33FirstRun", "0", CVAR_ARCHIVE | CVAR_ROM},
	{&ui_realWarmUp, "g_warmup", "20", CVAR_ARCHIVE},
	{&ui_realCaptureLimit, "capturelimit", "8", CVAR_SERVERINFO | CVAR_ARCHIVE | CVAR_NORESTART},
	{&ui_serverStatusTimeOut, "ui_serverStatusTimeOut", "7000", CVAR_ARCHIVE},
	//Makro - tablet support in the UI
	{&ui_RQ3_tabletMode, "ui_RQ3_tabletMode", "0", CVAR_ARCHIVE},
	//Makro - cvar for player model display
	{&ui_RQ3_modelCommand, "ui_RQ3_modelCommand", "0", 0},
	{&ui_RQ3_ssgCrosshair, "ui_RQ3_ssgCrosshair", "0", 0},
	{&ui_RQ3_weapAfterJoin, "ui_RQ3_weapAfterJoin", "1", CVAR_ARCHIVE},
	//Makro - model cvar
	{&ui_RQ3_model, "model", "reactionmale/default", 0},
	//Makro - team counts
	//Handled in cgame now
	//{ &ui_RQ3_teamCount1, "g_RQ3_teamCount1", "0", 0},
	//{ &ui_RQ3_teamCount2, "g_RQ3_teamCount2", "0", 0},
	//{ &ui_RQ3_numSpectators, "g_RQ3_numSpectators", "0", 0},
	//Makro - specify server option
	{&ui_RQ3_joinAddress, "ui_RQ3_joinAddress", "", CVAR_ARCHIVE},
	{&ui_RQ3_joinPort, "ui_RQ3_joinPort", "27960", CVAR_ARCHIVE},
	//Makro - demo name
	{&ui_RQ3_demoName, "ui_RQ3_demoName", "", 0},
	//Makro - maxpolys hack
	{&ui_maxpolys, "r_maxpolys", "4096", CVAR_ARCHIVE},
	{&ui_maxpolyverts, "r_maxpolyverts", "16384", CVAR_ARCHIVE},
	//Makro - matchmode settings
	{&ui_RQ3_timelimit,			"ui_RQ3_timelimit", "0", 0},
	{&ui_RQ3_roundlimit,		"ui_RQ3_roundlimit", "0", 0},
	{&ui_RQ3_roundtimelimit,	"ui_RQ3_roundtimelimit", "0", 0},
	{&ui_RQ3_fraglimit,			"ui_RQ3_fraglimit", "0", 0},
	{&ui_RQ3_maxplayers,		"ui_RQ3_maxplayers", "0", 0},
	{&ui_RQ3_forceteamtalk,		"ui_RQ3_forceteamtalk", "0", 0},
	{&ui_RQ3_limchasecam,		"ui_RQ3_limchasecam", "0", 0},
	{&ui_RQ3_tgren,				"ui_RQ3_tgren", "0", 0},
	{&ui_RQ3_friendlyFire,		"ui_RQ3_friendlyFire", "0", 0},
	//Makro - in-game server info
	{&ui_RQ3_ingameDetails,		"ui_RQ3_ingameDetails",	"0", CVAR_ARCHIVE},
	//Makro - ref pass
	{&ui_RQ3_refPassword,		"ui_RQ3_refPassword",	"", 0},
	//Makro - captain cvars
	{&ui_RQ3_teamName,		"ui_RQ3_teamName",	"", CVAR_ARCHIVE},
	{&ui_RQ3_teamModel,		"ui_RQ3_teamModel",	"", CVAR_ARCHIVE},
	//Makro - radio presets menu cvars
	//1
	{&ui_RQ3_radioPreset1Desc,		"ui_RQ3_radioPreset1Desc", "Enemy spotted", CVAR_ARCHIVE},
	{&ui_RQ3_radioPreset1Script,	"ui_RQ3_radioPreset1Script", "say_team Enemy spotted; radio enemys", CVAR_ARCHIVE},
	//2
	{&ui_RQ3_radioPreset2Desc,		"ui_RQ3_radioPreset2Desc", "Reporting in", CVAR_ARCHIVE},
	{&ui_RQ3_radioPreset2Script,	"ui_RQ3_radioPreset2Script", "say_team Reporting in with $W and $H health; radio reportin", CVAR_ARCHIVE},
	//3
	{&ui_RQ3_radioPreset3Desc,		"ui_RQ3_radioPreset3Desc", "Team, report in !", CVAR_ARCHIVE},
	{&ui_RQ3_radioPreset3Script,	"ui_RQ3_radioPreset3Script", "say_team Team, report in; radio treport", CVAR_ARCHIVE},
	//4
	{&ui_RQ3_radioPreset4Desc,		"ui_RQ3_radioPreset4Desc", "Go !", CVAR_ARCHIVE},
	{&ui_RQ3_radioPreset4Script,	"ui_RQ3_radioPreset4Script", "say_team Go !; radio go", CVAR_ARCHIVE},
	//5
	{&ui_RQ3_radioPreset5Desc,		"ui_RQ3_radioPreset5Desc", "I'm hit !", CVAR_ARCHIVE},
	{&ui_RQ3_radioPreset5Script,	"ui_RQ3_radioPreset5Script", "say_team I'm hit, I've got $H left !; radio im_hit", CVAR_ARCHIVE},
	//6
	{&ui_RQ3_radioPreset6Desc,		"ui_RQ3_radioPreset6Desc", "I've got your back !", CVAR_ARCHIVE},
	{&ui_RQ3_radioPreset6Script,	"ui_RQ3_radioPreset6Script", "say_team I've got your back !; radio escort2", CVAR_ARCHIVE},
	//7
	{&ui_RQ3_radioPreset7Desc,		"ui_RQ3_radioPreset7Desc", "Teammate down", CVAR_ARCHIVE},
	{&ui_RQ3_radioPreset7Script,	"ui_RQ3_radioPreset7Script", "say_team Teammate down !; radio teamdown", CVAR_ARCHIVE},
	//8
	{&ui_RQ3_radioPreset8Desc,		"ui_RQ3_radioPreset8Desc", "Enemy down", CVAR_ARCHIVE},
	{&ui_RQ3_radioPreset8Script,	"ui_RQ3_radioPreset8Script", "say_team $K eliminated; radio enemyd", CVAR_ARCHIVE},
	//9
	{&ui_RQ3_radioPreset9Desc,		"ui_RQ3_radioPreset9Desc", "Right", CVAR_ARCHIVE},
	{&ui_RQ3_radioPreset9Script,	"ui_RQ3_radioPreset9Script", "say_team Right; radio right", CVAR_ARCHIVE},
	//10
	{&ui_RQ3_radioPreset10Desc,		"ui_RQ3_radioPreset10Desc", "", CVAR_ARCHIVE},
	{&ui_RQ3_radioPreset10Script,	"ui_RQ3_radioPreset10Script", "", CVAR_ARCHIVE},
	//Makro - player gender; irrelevant for now
	{&ui_RQ3_gender,				"ui_RQ3_gender", "0",	CVAR_ARCHIVE}
};

// bk001129 - made static to avoid aliasing
static int cvarTableSize = sizeof(cvarTable) / sizeof(cvarTable[0]);

/*
=================
UI_RegisterCvars
=================
*/
void UI_RegisterCvars(void)
{
	int i;
	cvarTable_t *cv;

	for (i = 0, cv = cvarTable; i < cvarTableSize; i++, cv++) {
		trap_Cvar_Register(cv->vmCvar, cv->cvarName, cv->defaultString, cv->cvarFlags);
	}
}
/*
=================
UI_UpdateCvars
=================
*/
void UI_UpdateCvars(void)
{
	int i;
	cvarTable_t *cv;

	for (i = 0, cv = cvarTable; i < cvarTableSize; i++, cv++) {
		trap_Cvar_Update(cv->vmCvar);
	}
}

/*
=================
ArenaServers_StopRefresh
=================
*/
static void UI_StopServerRefresh(void)
{
	int count;

	if (!uiInfo.serverStatus.refreshActive) {
		// not currently refreshing
		return;
	}
	uiInfo.serverStatus.refreshActive = qfalse;
	Com_Printf("%d servers listed in browser with %d players.\n",
		   uiInfo.serverStatus.numDisplayServers, uiInfo.serverStatus.numPlayersOnServers);
	count = trap_LAN_GetServerCount(ui_netSource.integer);
	if (count - uiInfo.serverStatus.numDisplayServers > 0) {
		Com_Printf("%d servers not listed due to packet loss or pings higher than %d\n",
			   count - uiInfo.serverStatus.numDisplayServers, (int) trap_Cvar_VariableValue("cl_maxPing"));
	}

}

/*
=================
ArenaServers_MaxPing
=================
*/

//Makro - not used anywhere
/*
#ifndef MISSIONPACK // bk001206
static int ArenaServers_MaxPing( void ) {
	int		maxPing;

	maxPing = (int)trap_Cvar_VariableValue( "cl_maxPing" );
	if( maxPing < 100 ) {
		maxPing = 100;
	}
	return maxPing;
}
#endif
*/

/*
=================
UI_DoServerRefresh
=================
*/
static void UI_DoServerRefresh(void)
{
	qboolean wait = qfalse;

	if (!uiInfo.serverStatus.refreshActive) {
		return;
	}
	if (ui_netSource.integer != AS_FAVORITES) {
		if (ui_netSource.integer == AS_LOCAL) {
			if (!trap_LAN_GetServerCount(ui_netSource.integer)) {
				wait = qtrue;
			}
		} else {
			if (trap_LAN_GetServerCount(ui_netSource.integer) < 0) {
				wait = qtrue;
			}
		}
	}

	if (uiInfo.uiDC.realTime < uiInfo.serverStatus.refreshtime) {
		if (wait) {
			return;
		}
	}
	// if still trying to retrieve pings
	if (trap_LAN_UpdateVisiblePings(ui_netSource.integer)) {
		uiInfo.serverStatus.refreshtime = uiInfo.uiDC.realTime + 1000;
	} else if (!wait) {
		// get the last servers in the list
		UI_BuildServerDisplayList(2);
		// stop the refresh
		UI_StopServerRefresh();
	}
	//
	UI_BuildServerDisplayList(qfalse);
}

/*
=================
UI_StartServerRefresh
=================
*/
static void UI_StartServerRefresh(qboolean full)
{
	int i;
	char *ptr;

	qtime_t q;

	trap_RealTime(&q);
	//Makro - added leading zero's
	//trap_Cvar_Set( va("ui_lastServerRefresh_%i", ui_netSource.integer), va("%s-%i, %i at %i:%i", MonthAbbrev[q.tm_mon],q.tm_mday, 1900+q.tm_year,q.tm_hour,q.tm_min));
	trap_Cvar_Set(va("ui_lastServerRefresh_%i", ui_netSource.integer),
		      va("%s-%i, %d at %02i:%02i", MonthAbbrev[q.tm_mon], q.tm_mday, 1900 + q.tm_year, q.tm_hour,
			 q.tm_min));

	if (!full) {
		UI_UpdatePendingPings();
		return;
	}

	uiInfo.serverStatus.refreshActive = qtrue;
	uiInfo.serverStatus.nextDisplayRefresh = uiInfo.uiDC.realTime + 1000;
	// clear number of displayed servers
	uiInfo.serverStatus.numDisplayServers = 0;
	uiInfo.serverStatus.numPlayersOnServers = 0;
	// mark all servers as visible so we store ping updates for them
	trap_LAN_MarkServerVisible(ui_netSource.integer, -1, qtrue);
	// reset all the pings
	trap_LAN_ResetPings(ui_netSource.integer);
	//
	if (ui_netSource.integer == AS_LOCAL) {
		trap_Cmd_ExecuteText(EXEC_NOW, "localservers\n");
		uiInfo.serverStatus.refreshtime = uiInfo.uiDC.realTime + 1000;
		return;
	}

	uiInfo.serverStatus.refreshtime = uiInfo.uiDC.realTime + 5000;
	if (ui_netSource.integer == AS_GLOBAL || ui_netSource.integer == AS_MPLAYER) {
		if (ui_netSource.integer == AS_GLOBAL) {
			i = 0;
		} else {
			i = 1;
		}

		ptr = UI_Cvar_VariableString("debug_protocol");
		if (strlen(ptr)) {
			trap_Cmd_ExecuteText(EXEC_NOW, va("globalservers %d %s full empty\n", i, ptr));
		} else {
			trap_Cmd_ExecuteText(EXEC_NOW,
					     va("globalservers %d %d full empty\n", i,
						(int) trap_Cvar_VariableValue("protocol")));
		}
	}
}

