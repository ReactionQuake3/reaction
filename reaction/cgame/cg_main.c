//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.109  2002/08/29 10:26:46  jbravo
// Blaze's commit nuked my keanu code and Suicide code in this file only.
// Its fixed now.
//
// Revision 1.108  2002/08/29 05:55:28  blaze
// changed ogc_islame from archive to ROM
//
// Revision 1.107  2002/08/29 04:42:41  blaze
// Anti OGC code
//
// Revision 1.104  2002/08/27 05:10:05  niceass
// new ctb marker shader names
//
// Revision 1.103  2002/08/25 00:45:24  niceass
// q3f atmosphere
//
// Revision 1.102  2002/08/07 03:35:57  jbravo
// Added dynamic radio and stopped all radio usage during lca
//
// Revision 1.101  2002/07/26 22:28:38  jbravo
// Fixed the server about menu, made the UI handle illegal models and skins
// better.
//
// Revision 1.100  2002/07/26 06:21:43  jbravo
// Fixed the MM settings stuff so it works on remote servers also.
// Removed the MM_NAMES_COLOR since it broke on nicks with color in them.
//
// Revision 1.99  2002/07/21 18:46:57  niceass
// weaponprediction cvar added
//
// Revision 1.98  2002/07/20 02:25:53  jbravo
// Added the AQDT CTB sounds to the base radio paks
//
// Revision 1.97  2002/07/19 04:40:56  jbravo
// Added 2 new radio sets and ctb radio sound support
//
// Revision 1.96  2002/07/19 04:32:09  niceass
// added marker support for ctb
//
// Revision 1.95  2002/07/13 22:42:18  makro
// Semi-working fog hull, semi-working sky portals (cgame code commented out)
// Basically, semi-working stuff :P
//
// Revision 1.94  2002/07/08 00:52:14  jbravo
// Renamed the foglaser shader at Sze's request.
//
// Revision 1.93  2002/07/07 18:36:13  jbravo
// Added an AntiIdle system. Can play insane sounds for idle players, drop them
// from teams or kick them.   Upped version to Beta 2.1
//
// Revision 1.92  2002/07/01 02:18:41  jbravo
// Small fixes to CTB and possible fix for subs and limchasecam
//
// Revision 1.91  2002/06/30 17:33:01  jbravo
// New radio sounds and the 0wned sound was added.
//
// Revision 1.90  2002/06/29 04:15:15  jbravo
// CTF is now CTB.  no weapons while the case is in hand other than pistol or knife
//
// Revision 1.89  2002/06/24 05:55:03  niceass
// drawping
//
// Revision 1.88  2002/06/21 23:20:34  blaze
// cg_rq3_overlaycrosshair when set to 1 will draw your non zoomed crosshair overtop of your ssg crosshair
//
// Revision 1.87  2002/06/21 21:05:35  niceass
// laserfog stuff & removed unused cvar
//
// Revision 1.86  2002/06/19 05:20:01  niceass
// scoreboard stuff
//
// Revision 1.85  2002/06/16 20:06:13  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.84  2002/06/16 19:12:52  jbravo
// Removed the MISSIONPACK ifdefs and missionpack only code.
//
// Revision 1.83  2002/06/13 19:03:22  niceass
// cg_forceModel teamplay fix.
//
// Revision 1.82  2002/06/12 22:31:59  slicer
// Even better way to improve the Cvar Anti-Cheat System
//
// Revision 1.81  2002/06/12 15:30:24  slicer
// Improved and fixed the Anti-Cheat System
//
// Revision 1.80  2002/06/11 22:49:22  niceass
// HC brass
//
// Revision 1.79  2002/06/10 14:02:31  slicer
// Removed rq3_cmd : ROUND , associated to cg_RQ3_team_round_going that wasn't being used
//
// Revision 1.78  2002/06/10 13:20:03  slicer
// RefID is now passed trought scoreboard, no more lca cvar, only cg.lca
//
// Revision 1.77  2002/06/09 18:58:40  makro
// no message
//
// Revision 1.76  2002/06/09 05:14:40  niceass
// pressure change
//
// Revision 1.75  2002/06/06 20:44:16  makro
// Removed cheat protection for cg_gunX, Y and Z
//
// Revision 1.74  2002/06/06 18:10:51  makro
// Loading a map with pre-2.0 breakables crashed Q3. Added temp fix
//
// Revision 1.73  2002/06/06 03:01:46  blaze
// a breakable with a underscore in it's name will now try and load files from it's parent if it cant find any itself
// ex glass_blue will load sounds from glass if there is no glass_blue/sounds/break1.wav
//
// Revision 1.72  2002/06/06 01:53:51  niceass
// pressure change
//
// Revision 1.71  2002/06/05 23:35:42  niceass
// "ready" command lag fix
//
// Revision 1.70  2002/05/26 05:12:11  niceass
// gravity fix and progress bar stuff
//
// Revision 1.69  2002/05/25 07:12:34  blaze
// moved breakables into a configstring so they work in demos
//
// Revision 1.68  2002/05/21 14:59:11  makro
// cg_RQ3_avidemo
//
// Revision 1.67  2002/05/19 21:04:37  jbravo
// Tkok popup system
//
// Revision 1.66  2002/05/19 18:32:11  jbravo
// Made new cvars for regular xhair colors.
//
// Revision 1.65  2002/05/18 03:55:35  niceass
// many misc. changes
//
// Revision 1.64  2002/05/13 05:24:54  jbravo
// the ssg color cvars now also control normal xhair color
//
// Revision 1.63  2002/05/12 14:39:48  makro
// Wood, brick & ceramic impact sounds
//
// Revision 1.62  2002/05/11 19:13:42  makro
// Sand surfaceparm
//
// Revision 1.61  2002/05/11 15:40:41  slicer
// Changed cg_RQ3_<team count> cvars to ui_RQ3_ and added a synch system for these
//
// Revision 1.60  2002/05/09 06:41:10  niceass
// New tracers
//
// Revision 1.59  2002/04/30 11:20:12  jbravo
// Redid the teamcount cvars.
//
// Revision 1.58  2002/04/29 06:12:40  niceass
// client matchmode stuff
//
// Revision 1.57  2002/04/23 06:06:57  niceass
// pressure stuff
//
// Revision 1.56  2002/04/20 15:05:08  makro
// More footstep sounds, a few other things
//
// Revision 1.55  2002/04/10 05:13:42  makro
// Changed cg_thirdPerson from CVAR_ROM to CVAR_CHEAT
//
// Revision 1.54  2002/04/09 14:30:10  jbravo
// Made cg_thirdPerson a CVAR_ROM, Made bots understand team aliases (1 and 2) and
// made TP spawns more random.
//
// Revision 1.53  2002/04/07 12:49:53  slicer
// Added 'teamname' command for MM, and tweaked the cvar system.
//
// Revision 1.52  2002/04/03 03:13:49  blaze
// NEW BREAKABLE CODE - will break all old breakables(wont appear in maps)
//
// Revision 1.51  2002/03/26 10:32:51  jbravo
// Bye bye LCA lag
//
// Revision 1.50  2002/03/23 05:50:47  jbravo
// Moved enableDust out of the missionpack
//
// Revision 1.49  2002/03/23 05:17:42  jbravo
// Major cleanup of game -> cgame communication with LCA vars.
//
// Revision 1.48  2002/03/21 15:02:05  jbravo
// More teamname cleanups and fix for fraglines.
//
// Revision 1.47  2002/03/21 00:26:20  blaze
// some fixing of func_explosive
//
// Revision 1.46  2002/03/17 21:32:23  jbravo
// Fixed the dynamic teamnames system up a bit to reduce traffic
//
// Revision 1.45  2002/03/16 21:49:08  niceass
// All new shell ejection code
//
// Revision 1.44  2002/03/14 16:04:26  slicer
// Optimization on radio parsing
//
// Revision 1.43  2002/03/14 02:24:39  jbravo
// Adding radio :)
//
// Revision 1.42  2002/03/11 02:23:52  niceass
// client gravity fix
//
// Revision 1.41  2002/03/07 19:50:48  makro
// Made cg_RQ3_ssgCrosshair latched
//
// Revision 1.40  2002/03/07 14:51:57  makro
// no message
//
// Revision 1.39  2002/02/26 04:02:53  jbravo
// Getting rid of the triangles over teammates heads by making cg_drawFriend's
// default 0
//
// Revision 1.38  2002/02/04 00:11:12  slicer
// Matchmode: Teams Ready/Not Ready goes by cvar MM_team1/2
//
// Revision 1.37  2002/01/30 07:37:25  niceass
// EnableBreath added for mappers (TA thing)
//
// Revision 1.36  2002/01/24 14:20:53  jbravo
// Adding func_explosive and a few new surfaceparms
//
// Revision 1.35  2002/01/11 20:20:57  jbravo
// Adding TP to main branch
//
// Revision 1.34  2002/01/11 19:48:29  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.33  2001/12/31 16:28:41  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
// cg_main.c -- initialization and primary entry point for cgame
#include "cg_local.h"

int forceModelModificationCount = -1;

void CG_Init(int serverMessageNum, int serverCommandSequence, int clientNum);
void CG_Shutdown(void);

//Blaze: used to access the names of the breakables
char rq3_breakables[RQ3_MAX_BREAKABLES][80];

/*
================
vmMain

This is the only way control passes into the module.
This must be the very first function compiled into the .q3vm file
================
*/
int vmMain(int command, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8,
	   int arg9, int arg10, int arg11)
{

	switch (command) {
	case CG_INIT:
		CG_Init(arg0, arg1, arg2);
		return 0;
	case CG_SHUTDOWN:
		CG_Shutdown();
		return 0;
	case CG_CONSOLE_COMMAND:
		return CG_ConsoleCommand();
	case CG_DRAW_ACTIVE_FRAME:
		CG_DrawActiveFrame(arg0, arg1, arg2);
		return 0;
	case CG_CROSSHAIR_PLAYER:
		return CG_CrosshairPlayer();
	case CG_LAST_ATTACKER:
		return CG_LastAttacker();
	case CG_KEY_EVENT:
		CG_KeyEvent(arg0, arg1);
		return 0;
	case CG_MOUSE_EVENT:
		CG_MouseEvent(arg0, arg1);
		return 0;
	case CG_EVENT_HANDLING:
		CG_EventHandling(arg0);
		return 0;
	default:
		CG_Error("vmMain: unknown command %i", command);
		break;
	}
	return -1;
}

cg_t cg;
cgs_t cgs;
centity_t cg_entities[MAX_GENTITIES];
weaponInfo_t cg_weapons[MAX_WEAPONS];
itemInfo_t cg_items[MAX_ITEMS];

vmCvar_t cg_railTrailTime;
vmCvar_t cg_centertime;
vmCvar_t cg_runpitch;
vmCvar_t cg_runroll;
vmCvar_t cg_bobup;
vmCvar_t cg_bobpitch;
vmCvar_t cg_bobroll;
vmCvar_t cg_swingSpeed;
vmCvar_t cg_shadows;
vmCvar_t cg_gibs;
vmCvar_t cg_drawTimer;
vmCvar_t cg_drawFPS;
vmCvar_t cg_drawPing;
vmCvar_t cg_drawSnapshot;
vmCvar_t cg_draw3dIcons;
vmCvar_t cg_drawIcons;
vmCvar_t cg_drawAmmoWarning;
vmCvar_t cg_drawCrosshair;
vmCvar_t cg_drawCrosshairNames;
vmCvar_t cg_drawRewards;
vmCvar_t cg_crosshairSize;
vmCvar_t cg_crosshairX;
vmCvar_t cg_crosshairY;
vmCvar_t cg_crosshairHealth;
vmCvar_t cg_draw2D;
vmCvar_t cg_drawStatus;
vmCvar_t cg_animSpeed;
vmCvar_t cg_debugAnim;
vmCvar_t cg_debugPosition;
vmCvar_t cg_debugEvents;
vmCvar_t cg_errorDecay;
vmCvar_t cg_nopredict;
vmCvar_t cg_noPlayerAnims;
vmCvar_t cg_showmiss;
vmCvar_t cg_footsteps;
vmCvar_t cg_addMarks;
vmCvar_t cg_brassTime;
vmCvar_t cg_viewsize;
vmCvar_t cg_drawGun;
vmCvar_t cg_gun_frame;
vmCvar_t cg_gun_x;
vmCvar_t cg_gun_y;
vmCvar_t cg_gun_z;
vmCvar_t cg_tracerChance;
vmCvar_t cg_tracerWidth;
vmCvar_t cg_tracerLength;
vmCvar_t cg_autoswitch;
vmCvar_t cg_ignore;
vmCvar_t cg_simpleItems;
vmCvar_t cg_fov;
vmCvar_t cg_thirdPerson;
vmCvar_t cg_thirdPersonRange;
vmCvar_t cg_thirdPersonAngle;
vmCvar_t cg_stereoSeparation;
vmCvar_t cg_lagometer;
vmCvar_t cg_drawAttacker;
vmCvar_t cg_synchronousClients;
vmCvar_t cg_teamChatTime;
vmCvar_t cg_teamChatHeight;
vmCvar_t cg_stats;
vmCvar_t cg_buildScript;
vmCvar_t cg_forceModel;
vmCvar_t cg_paused;
vmCvar_t cg_blood;
vmCvar_t cg_predictItems;
vmCvar_t cg_deferPlayers;
vmCvar_t cg_drawTeamOverlay;
vmCvar_t cg_teamOverlayUserinfo;

//Blaze: reaction weapon positioning
// Elder: removed for now
//vmCvar_t      cg_RQ3_drawWeapon;
vmCvar_t cg_RQ3_glasstime;

//Blaze: Anti OGC code
vmCvar_t ogc_islame;

//Elder: muzzle flash toggle
vmCvar_t cg_RQ3_flash;

//Elder: toggle alpha blending
vmCvar_t cg_RQ3_painblend;

//Elder: toggle client-side zoom assist
vmCvar_t cg_RQ3_ssgZoomAssist;

//Elder: crosshair colours!
vmCvar_t cg_RQ3_ssgColorR;
vmCvar_t cg_RQ3_ssgColorG;
vmCvar_t cg_RQ3_ssgColorB;
vmCvar_t cg_RQ3_ssgColorA;

// JBravo: normal crosshair colors
vmCvar_t cg_RQ3_crosshairColorR;
vmCvar_t cg_RQ3_crosshairColorG;
vmCvar_t cg_RQ3_crosshairColorB;
vmCvar_t cg_RQ3_crosshairColorA;

//Blaze: allow regular crosshair to be overlaid ontop of the ssg crosshair
vmCvar_t cg_RQ3_overlaycrosshair;

// JBravo: cvar for tkok popup
vmCvar_t cg_RQ3_tkokAutoPopup;
// JBravo: radio cvars.
vmCvar_t cg_RQ3_radiovoice_male;
vmCvar_t cg_RQ3_radiovoice_female;
vmCvar_t cg_RQ3_SuicideLikeARealMan;
vmCvar_t cg_RQ3_dynamicRadio;

// Slicer: for the Anti-Cheat System
//vmCvar_t      cg_RQ3_Auth;
//Elder: SSG unique sensitivities
vmCvar_t cg_RQ3_ssgSensitivityAuto;
vmCvar_t cg_RQ3_ssgSensitivity2x;
vmCvar_t cg_RQ3_ssgSensitivity4x;
vmCvar_t cg_RQ3_ssgSensitivity6x;

//Blaze: Which ssg crosshair to use
vmCvar_t cg_RQ3_ssgCrosshair;

//Blaze: Allow stuff to be done automatically on round start/end
vmCvar_t cg_RQ3_autoAction;

//Elder: smoke puffs, sparks, etc.
vmCvar_t cg_RQ3_impactEffects;

//Elder: toggle client-side laser drawing
vmCvar_t cg_RQ3_laserAssist;

//Blaze: anouncer sounds
vmCvar_t cg_RQ3_anouncer;

//Elder: different blood types
vmCvar_t cg_RQ3_bloodStyle;

//NiceAss: Temporary boolean strobe cvar
vmCvar_t cg_RQ3_strobe;

//NiceAss: Predict weapon animations or not. Makes it like Q2 if disabled.
vmCvar_t cg_RQ3_predictWeapons;


//Makro: avidemo with jpegs
vmCvar_t cg_RQ3_avidemo;
vmCvar_t cg_drawFriend;
vmCvar_t cg_teamChatsOnly;
vmCvar_t cg_noVoiceChats;
vmCvar_t cg_noVoiceText;
vmCvar_t cg_hudFiles;
vmCvar_t cg_scorePlum;
vmCvar_t cg_smoothClients;
vmCvar_t pmove_fixed;

//vmCvar_t      cg_pmove_fixed;
vmCvar_t pmove_msec;
vmCvar_t cg_pmove_msec;
vmCvar_t cg_cameraMode;
vmCvar_t cg_cameraOrbit;
vmCvar_t cg_cameraOrbitDelay;
vmCvar_t cg_timescaleFadeEnd;
vmCvar_t cg_timescaleFadeSpeed;
vmCvar_t cg_timescale;
vmCvar_t cg_smallFont;
vmCvar_t cg_bigFont;
vmCvar_t cg_noTaunt;
vmCvar_t cg_noProjectileTrail;
vmCvar_t cg_oldRail;
vmCvar_t cg_gravity;
vmCvar_t cg_oldRocket;
vmCvar_t cg_oldPlasma;
vmCvar_t cg_trueLightning;

//Blaze: cheat struct
cheat_cvar cheats[30];

// JBravo: Teamplay cvars synced from game
//Slicer: no longer needed.
//vmCvar_t      cg_RQ3_lca;

//Slicer: apparently not being used
//vmCvar_t      cg_RQ3_team_round_going;
vmCvar_t cg_RQ3_team1name;
vmCvar_t cg_RQ3_team2name;
vmCvar_t cg_RQ3_team1model;
vmCvar_t cg_RQ3_team2model;

vmCvar_t ui_RQ3_teamCount1;
vmCvar_t ui_RQ3_teamCount2;
vmCvar_t ui_RQ3_numSpectators;

//Slicer: matchmode team status cvars
//vmCvar_t      cg_RQ3_RefID;
vmCvar_t cg_RQ3_matchmode;

// NiceAss: Taken out of the missionpack
vmCvar_t cg_enableBreath;
vmCvar_t cg_enableLaserFog;

// JBravo: ditto
vmCvar_t cg_enableDust;

// JBravo: cvars for the MM ingame menu
vmCvar_t cg_RQ3_timelimit;
vmCvar_t cg_RQ3_roundlimit;
vmCvar_t cg_RQ3_roundtimelimit;
vmCvar_t cg_RQ3_fraglimit;
vmCvar_t cg_RQ3_maxplayers;
vmCvar_t cg_RQ3_forceteamtalk;
vmCvar_t cg_RQ3_limchasecam;
vmCvar_t cg_RQ3_tgren;
vmCvar_t cg_RQ3_friendlyFire;
vmCvar_t cg_RQ3_version;
// JBravo: cvars for the about menu
vmCvar_t cg_RQ3_hostname;
vmCvar_t cg_RQ3_needpass;
vmCvar_t cg_RQ3_capturelimit;
vmCvar_t cg_RQ3_dmflags;
vmCvar_t cg_RQ3_bot_minplayers;
vmCvar_t cg_RQ3_showOwnKills;
// q3f atmospheric stuff
vmCvar_t	cg_atmosphericEffects;
vmCvar_t	cg_lowEffects;

typedef struct {
	vmCvar_t *vmCvar;
	char *cvarName;
	char *defaultString;
	int cvarFlags;
} cvarTable_t;

static cvarTable_t cvarTable[] = {	// bk001129
	{&cg_ignore, "cg_ignore", "0", 0},	// used for debugging
	{&cg_autoswitch, "cg_autoswitch", "1", CVAR_ARCHIVE},
	{&cg_drawGun, "cg_drawGun", "1", CVAR_ARCHIVE},
	{&cg_fov, "cg_fov", "90", CVAR_ARCHIVE},
	{&cg_viewsize, "cg_viewsize", "100", CVAR_ARCHIVE},
	{&cg_stereoSeparation, "cg_stereoSeparation", "0.4", CVAR_ARCHIVE},
	{&cg_shadows, "cg_shadows", "1", CVAR_ARCHIVE},
	{&cg_gibs, "cg_gibs", "1", CVAR_ARCHIVE},
	{&cg_draw2D, "cg_draw2D", "1", CVAR_ARCHIVE},
	{&cg_drawStatus, "cg_drawStatus", "1", CVAR_ARCHIVE},
	{&cg_drawTimer, "cg_drawTimer", "0", CVAR_ARCHIVE},
	{&cg_drawFPS, "cg_drawFPS", "0", CVAR_ARCHIVE},
	{&cg_drawPing, "cg_drawPing", "0", CVAR_ARCHIVE},
	{&cg_drawSnapshot, "cg_drawSnapshot", "0", CVAR_ARCHIVE},
	{&cg_draw3dIcons, "cg_draw3dIcons", "1", CVAR_ARCHIVE},
	{&cg_drawIcons, "cg_drawIcons", "1", CVAR_ARCHIVE},
	{&cg_drawAmmoWarning, "cg_drawAmmoWarning", "1", CVAR_ARCHIVE},
	{&cg_drawAttacker, "cg_drawAttacker", "1", CVAR_ARCHIVE},
	{&cg_drawCrosshair, "cg_drawCrosshair", "4", CVAR_ARCHIVE},
	{&cg_drawCrosshairNames, "cg_drawCrosshairNames", "1", CVAR_ARCHIVE},
	{&cg_drawRewards, "cg_drawRewards", "1", CVAR_ARCHIVE},
	{&cg_crosshairSize, "cg_crosshairSize", "24", CVAR_ARCHIVE},
	{&cg_crosshairHealth, "cg_crosshairHealth", "1", CVAR_ARCHIVE},
	{&cg_crosshairX, "cg_crosshairX", "0", CVAR_ARCHIVE},
	{&cg_crosshairY, "cg_crosshairY", "0", CVAR_ARCHIVE},
	{&cg_brassTime, "cg_brassTime", "10000", CVAR_ARCHIVE},
	{&cg_simpleItems, "cg_simpleItems", "0", CVAR_ARCHIVE},
	{&cg_addMarks, "cg_marks", "1", CVAR_ARCHIVE},
	{&cg_lagometer, "cg_lagometer", "1", CVAR_ARCHIVE},
	{&cg_railTrailTime, "cg_railTrailTime", "400", CVAR_ARCHIVE},
	//Makro - changed from CVAR_CHEAT
	{&cg_gun_x, "cg_gunX", "0", CVAR_ARCHIVE},
	{&cg_gun_y, "cg_gunY", "0", CVAR_ARCHIVE},
	{&cg_gun_z, "cg_gunZ", "0", CVAR_ARCHIVE},
	//Blaze: to test the gun frames
	{&cg_gun_frame, "cg_gun_frame", "0", CVAR_CHEAT},
	{&cg_centertime, "cg_centertime", "3", CVAR_CHEAT},
	{&cg_runpitch, "cg_runpitch", "0.002", CVAR_ARCHIVE},
	{&cg_runroll, "cg_runroll", "0.005", CVAR_ARCHIVE},
	{&cg_bobup, "cg_bobup", "0.005", CVAR_ARCHIVE},
	{&cg_bobpitch, "cg_bobpitch", "0.002", CVAR_ARCHIVE},
	{&cg_bobroll, "cg_bobroll", "0.002", CVAR_ARCHIVE},
	{&cg_swingSpeed, "cg_swingSpeed", "0.3", CVAR_CHEAT},
	{&cg_animSpeed, "cg_animspeed", "1", CVAR_CHEAT},
	{&cg_debugAnim, "cg_debuganim", "0", CVAR_CHEAT},
	{&cg_debugPosition, "cg_debugposition", "0", CVAR_CHEAT},
	{&cg_debugEvents, "cg_debugevents", "0", CVAR_CHEAT},
	{&cg_errorDecay, "cg_errordecay", "100", 0},
	{&cg_nopredict, "cg_nopredict", "0", 0},
	{&cg_noPlayerAnims, "cg_noplayeranims", "0", CVAR_CHEAT},
	{&cg_showmiss, "cg_showmiss", "0", 0},
	{&cg_footsteps, "cg_footsteps", "1", CVAR_CHEAT},
	{&cg_tracerChance, "cg_tracerchance", "0.4", CVAR_CHEAT},
	{&cg_tracerWidth, "cg_tracerwidth", "1", CVAR_CHEAT},
	{&cg_tracerLength, "cg_tracerlength", "300", CVAR_CHEAT},
	{&cg_thirdPersonRange, "cg_thirdPersonRange", "40", CVAR_CHEAT},
	{&cg_thirdPersonAngle, "cg_thirdPersonAngle", "0", CVAR_CHEAT},
	//Makro - changing from CVAR_ROM (why was it like that ?) to CVAR_CHEAT
	{&cg_thirdPerson, "cg_thirdPerson", "0", CVAR_CHEAT},
	{&cg_teamChatTime, "cg_teamChatTime", "3000", CVAR_ARCHIVE},
	{&cg_teamChatHeight, "cg_teamChatHeight", "0", CVAR_ARCHIVE},
	{&cg_forceModel, "cg_forceModel", "0", CVAR_ARCHIVE},
	{&cg_predictItems, "cg_predictItems", "1", CVAR_ARCHIVE},
	{&cg_deferPlayers, "cg_deferPlayers", "1", CVAR_ARCHIVE},
	{&cg_drawTeamOverlay, "cg_drawTeamOverlay", "0", CVAR_ARCHIVE},
	{&cg_teamOverlayUserinfo, "teamoverlay", "0", CVAR_ROM | CVAR_USERINFO},
	{&cg_stats, "cg_stats", "0", 0},
	{&cg_drawFriend, "cg_drawFriend", "0", CVAR_ARCHIVE},
	{&cg_teamChatsOnly, "cg_teamChatsOnly", "0", CVAR_ARCHIVE},
	{&cg_noVoiceChats, "cg_noVoiceChats", "0", CVAR_ARCHIVE},
	{&cg_noVoiceText, "cg_noVoiceText", "0", CVAR_ARCHIVE},
	{&ogc_islame,"ogc_islame","1",CVAR_ROM},
	// the following variables are created in other parts of the system,
	// but we also reference them here
	{&cg_buildScript, "com_buildScript", "0", 0},	// force loading of all possible data amd error on failures
	{&cg_paused, "cl_paused", "0", CVAR_ROM},
	{&cg_blood, "com_blood", "1", CVAR_ARCHIVE},
	{&cg_synchronousClients, "g_synchronousClients", "0", 0},	// communicated by systeminfo
	// NiceAss: Taken out of the missionpack
	{&cg_enableBreath, "g_enableBreath", "0", CVAR_SERVERINFO},
	{&cg_enableLaserFog, "g_enableLaserFog", "1", CVAR_SERVERINFO},
	// JBravo: ditto
	{&cg_enableDust, "g_enableDust", "0", CVAR_SERVERINFO},

	{&cg_cameraOrbit, "cg_cameraOrbit", "0", CVAR_CHEAT},
	{&cg_cameraOrbitDelay, "cg_cameraOrbitDelay", "50", CVAR_ARCHIVE},
	{&cg_timescaleFadeEnd, "cg_timescaleFadeEnd", "1", 0},
	{&cg_timescaleFadeSpeed, "cg_timescaleFadeSpeed", "0", 0},
	{&cg_timescale, "timescale", "1", 0},
	{&cg_scorePlum, "cg_scorePlums", "1", CVAR_USERINFO | CVAR_ARCHIVE},
	{&cg_smoothClients, "cg_smoothClients", "0", CVAR_USERINFO | CVAR_ARCHIVE},
	{&cg_cameraMode, "com_cameraMode", "0", CVAR_CHEAT},

	{&pmove_fixed, "pmove_fixed", "0", 0},
	{&pmove_msec, "pmove_msec", "8", 0},
	{&cg_noTaunt, "cg_noTaunt", "0", CVAR_ARCHIVE},
	{&cg_noProjectileTrail, "cg_noProjectileTrail", "0", CVAR_ARCHIVE},
	{&cg_smallFont, "ui_smallFont", "0.25", CVAR_ARCHIVE},
	{&cg_bigFont, "ui_bigFont", "0.4", CVAR_ARCHIVE},
	//Blaze: Reaction hand type command
	// Elder: removed
	//{ &cg_RQ3_drawWeapon, "cg_RQ3_drawWeapon", "2", CVAR_ARCHIVE },
	{&cg_RQ3_glasstime, "cg_RQ3_glasstime", "0", CVAR_ARCHIVE},
	// Slicer: for the Anti-Cheat System
	//{ &cg_RQ3_Auth, "cg_RQ3_Auth", "0", CVAR_USERINFO | CVAR_ROM },
	// Elder: added
	{&cg_RQ3_flash, "cg_RQ3_flash", "1", CVAR_ARCHIVE},
	// NiceAss: added
	{&cg_RQ3_strobe, "cg_RQ3_strobe", "0", CVAR_ARCHIVE},
	{&cg_RQ3_painblend, "cg_RQ3_painblend", "1", CVAR_ARCHIVE},
	{&cg_RQ3_ssgZoomAssist, "cg_RQ3_ssgZoomAssist", "1", CVAR_ARCHIVE},
	{&cg_RQ3_ssgSensitivityAuto, "cg_RQ3_ssgSensitivityAuto", "1", CVAR_ARCHIVE},
	{&cg_RQ3_ssgSensitivity2x, "cg_RQ3_ssgSensitivity2x", "0.4", CVAR_ARCHIVE},
	{&cg_RQ3_ssgSensitivity4x, "cg_RQ3_ssgSensitivity4x", "0.2", CVAR_ARCHIVE},
	{&cg_RQ3_ssgSensitivity6x, "cg_RQ3_ssgSensitivity6x", "0.1", CVAR_ARCHIVE},
	//Blaze: Added to let people autop perform actions on match start/end
	{&cg_RQ3_autoAction, "cg_RQ3_autoAction", "0", CVAR_ARCHIVE},
	//Makro - this should be latched
	{&cg_RQ3_ssgCrosshair, "cg_RQ3_ssgCrosshair", "0", CVAR_ARCHIVE | CVAR_LATCH},
	{&cg_RQ3_ssgColorR, "cg_RQ3_ssgColorR", "0.0", CVAR_ARCHIVE},
	{&cg_RQ3_ssgColorG, "cg_RQ3_ssgColorG", "1.0", CVAR_ARCHIVE},
	{&cg_RQ3_ssgColorB, "cg_RQ3_ssgColorB", "0.0", CVAR_ARCHIVE},
	{&cg_RQ3_ssgColorA, "cg_RQ3_ssgColorA", "0.75", CVAR_ARCHIVE},
//Blaze: allow regular crosshair to be overlaid ontop of the ssg crosshair
	{&cg_RQ3_overlaycrosshair, "cg_RQ3_overlaycrosshair", "0", CVAR_ARCHIVE},

// JBravo: cvars for regular crosshairs and their colors
// Makro - changed default color to white; it was 0/1/0/.75 before
	{&cg_RQ3_crosshairColorR, "cg_RQ3_crosshairColorR", "1.0", CVAR_ARCHIVE},
	{&cg_RQ3_crosshairColorG, "cg_RQ3_crosshairColorG", "1.0", CVAR_ARCHIVE},
	{&cg_RQ3_crosshairColorB, "cg_RQ3_crosshairColorB", "1.0", CVAR_ARCHIVE},
	{&cg_RQ3_crosshairColorA, "cg_RQ3_crosshairColorA", "1.0", CVAR_ARCHIVE},
	{&cg_RQ3_tkokAutoPopup, "cg_RQ3_tkokAutoPopup", "0", CVAR_ARCHIVE},
	{&cg_RQ3_radiovoice_male, "cg_RQ3_radiovoice_male", "1", CVAR_USERINFO | CVAR_ARCHIVE},
	{&cg_RQ3_radiovoice_female, "cg_RQ3_radiovoice_female", "1", CVAR_USERINFO | CVAR_ARCHIVE},
	{&cg_RQ3_SuicideLikeARealMan, "cg_RQ3_SuicideLikeARealMan", "0", CVAR_USERINFO | CVAR_ARCHIVE},
	{&cg_RQ3_dynamicRadio, "cg_RQ3_dynamicRadio", "1", CVAR_ARCHIVE},
	{&cg_RQ3_impactEffects, "cg_RQ3_impactEffects", "1", CVAR_ARCHIVE},
	{&cg_RQ3_laserAssist, "cg_RQ3_laserAssist", "0", CVAR_ARCHIVE},
	{&cg_RQ3_anouncer, "cg_RQ3_announcer", "1", CVAR_ARCHIVE},
	{&cg_RQ3_bloodStyle, "cg_RQ3_bloodStyle", "0", CVAR_ARCHIVE},
	{&cg_RQ3_predictWeapons, "cg_RQ3_predictWeapons", "1", CVAR_ARCHIVE},
	{&cg_oldRail, "cg_oldRail", "1", CVAR_ARCHIVE},
	{&cg_oldRocket, "cg_oldRocket", "1", CVAR_ARCHIVE},
	{&cg_oldPlasma, "cg_oldPlasma", "1", CVAR_ARCHIVE},
	{&cg_trueLightning, "cg_trueLightning", "0.0", CVAR_ARCHIVE},
	//Makro - avidemo with jpegs
	{&cg_RQ3_avidemo, "cg_RQ3_avidemo", "0", 0},
// JBravo: added
//Slicer: no longer needed.
//      { &cg_RQ3_lca, "cg_RQ3_lca", "0", CVAR_ROM},

//Slicer: apparently not being used     
//      { &cg_RQ3_team_round_going, "cg_RQ3_team_round_going", "0", CVAR_ROM},
	{&cg_RQ3_team1name, "g_RQ3_team1name", "0", 0},
	{&cg_RQ3_team2name, "g_RQ3_team2name", "0", 0},
	{&cg_RQ3_team1model, "g_RQ3_team1model", "grunt/robber", 0},
	{&cg_RQ3_team2model, "g_RQ3_team2model", "grunt/police", 0},
	{&ui_RQ3_teamCount1, "ui_RQ3_teamCount1", "0", CVAR_ROM},
	{&ui_RQ3_teamCount2, "ui_RQ3_teamCount2", "0", CVAR_ROM},
	{&ui_RQ3_numSpectators, "ui_RQ3_numSpectators", "0", CVAR_ROM},
	{&cg_gravity, "g_gravity", "800", 0},
	//Slicer: Team Status Cvars for MM
	{&cg_RQ3_matchmode, "g_RQ3_matchmode", "0", 0},
	// JBravo: more MM ingame cvars.
	{&cg_RQ3_timelimit, "timelimit", "0", CVAR_ROM},
	{&cg_RQ3_roundlimit, "cg_RQ3_roundlimit", "0", CVAR_ROM},
	{&cg_RQ3_roundtimelimit, "cg_RQ3_roundtimelimit", "0", CVAR_ROM},
	{&cg_RQ3_fraglimit, "fraglimit", "0", CVAR_ROM},
	{&cg_RQ3_maxplayers, "cg_RQ3_maxplayers", "0", CVAR_ROM},
	{&cg_RQ3_forceteamtalk, "cg_RQ3_forceteamtalk", "0", CVAR_ROM},
	{&cg_RQ3_limchasecam, "cg_RQ3_limchasecam", "0", CVAR_ROM},
	{&cg_RQ3_tgren, "cg_RQ3_tgren", "0", CVAR_ROM},
	{&cg_RQ3_friendlyFire, "cg_RQ3_friendlyFire", "0", CVAR_ROM},
	{&cg_RQ3_version, "g_RQ3_version", "0", CVAR_ROM},
	// JBravo: cvars for the about menu.
	{&cg_RQ3_hostname, "sv_hostname", "0", CVAR_ROM},
	{&cg_RQ3_needpass, "g_needpass", "0", CVAR_ROM},
	{&cg_RQ3_capturelimit, "capturelimit", "0", CVAR_ROM},
	{&cg_RQ3_dmflags, "dmflags", "0", CVAR_ROM},
	{&cg_RQ3_bot_minplayers, "bot_minplayers", "0", CVAR_ROM},
	{&cg_RQ3_showOwnKills, "g_RQ3_showOwnKills", "0", CVAR_ROM},
	// q3f atmospheric stuff:
	{ &cg_atmosphericEffects, "cg_atmosphericEffects", "1", CVAR_ARCHIVE },
	{ &cg_lowEffects, "cg_lowEffects", "0", CVAR_ARCHIVE },

	//{ &cg_RQ3_RefID, "g_RQ3_RefID", "0", 0}
	//{ &cg_pmove_fixed, "cg_pmove_fixed", "0", CVAR_USERINFO | CVAR_ARCHIVE }
};

static int cvarTableSize = sizeof(cvarTable) / sizeof(cvarTable[0]);

/*
=================
CG_RegisterCvars
=================
*/
void CG_RegisterCvars(void)
{
	int i;
	cvarTable_t *cv;
	char var[MAX_TOKEN_CHARS];

	for (i = 0, cv = cvarTable; i < cvarTableSize; i++, cv++) {
		trap_Cvar_Register(cv->vmCvar, cv->cvarName, cv->defaultString, cv->cvarFlags);
	}

	// see if we are also running the server on this machine
	trap_Cvar_VariableStringBuffer("sv_running", var, sizeof(var));
	cgs.localServer = atoi(var);

	forceModelModificationCount = cg_forceModel.modificationCount;

	trap_Cvar_Register(NULL, "model", DEFAULT_MODEL, CVAR_USERINFO | CVAR_ARCHIVE);
	trap_Cvar_Register(NULL, "headmodel", DEFAULT_MODEL, CVAR_USERINFO | CVAR_ARCHIVE);
	trap_Cvar_Register(NULL, "team_model", DEFAULT_TEAM_MODEL, CVAR_USERINFO | CVAR_ARCHIVE);
	trap_Cvar_Register(NULL, "team_headmodel", DEFAULT_TEAM_HEAD, CVAR_USERINFO | CVAR_ARCHIVE);
}

/*
===================
CG_ForceModelChange
===================
*/
static void CG_ForceModelChange(void)
{
	int i;

	for (i = 0; i < MAX_CLIENTS; i++) {
		const char *clientInfo;

		clientInfo = CG_ConfigString(CS_PLAYERS + i);
		if (!clientInfo[0]) {
			continue;
		}
		CG_NewClientInfo(i);
	}
}

/*
=================
CG_UpdateCvars
=================
*/
void CG_UpdateCvars(void)
{
	int i;
	cvarTable_t *cv;

	for (i = 0, cv = cvarTable; i < cvarTableSize; i++, cv++) {
		trap_Cvar_Update(cv->vmCvar);
	}

	// check for modications here

	// If team overlay is on, ask for updates from the server.  If its off,
	// let the server know so we don't receive it
	if (drawTeamOverlayModificationCount != cg_drawTeamOverlay.modificationCount) {
		drawTeamOverlayModificationCount = cg_drawTeamOverlay.modificationCount;

		if (cg_drawTeamOverlay.integer > 0) {
			trap_Cvar_Set("teamoverlay", "1");
		} else {
			trap_Cvar_Set("teamoverlay", "0");
		}
		// FIXME E3 HACK
		trap_Cvar_Set("teamoverlay", "1");
	}
	// if force model changed
	if (forceModelModificationCount != cg_forceModel.modificationCount && cgs.gametype < GT_TEAM) {
		forceModelModificationCount = cg_forceModel.modificationCount;
		CG_ForceModelChange();
	}
}

int CG_CrosshairPlayer(void)
{
	if (cg.time > (cg.crosshairClientTime + 1000)) {
		return -1;
	}
	return cg.crosshairClientNum;
}

int CG_LastAttacker(void)
{
	if (!cg.attackerTime) {
		return -1;
	}
	return cg.snap->ps.persistant[PERS_ATTACKER];
}

void QDECL CG_Printf(const char *msg, ...)
{
	va_list argptr;
	char text[1024];

	va_start(argptr, msg);
	vsprintf(text, msg, argptr);
	va_end(argptr);

	trap_Print(text);
}

void QDECL CG_Error(const char *msg, ...)
{
	va_list argptr;
	char text[1024];

	va_start(argptr, msg);
	vsprintf(text, msg, argptr);
	va_end(argptr);

	trap_Error(text);
}

#ifndef CGAME_HARD_LINKED
// this is only here so the functions in q_shared.c and bg_*.c can link (FIXME)

void QDECL Com_Error(int level, const char *error, ...)
{
	va_list argptr;
	char text[1024];

	va_start(argptr, error);
	vsprintf(text, error, argptr);
	va_end(argptr);

	CG_Error("%s", text);
}

void QDECL Com_Printf(const char *msg, ...)
{
	va_list argptr;
	char text[1024];

	va_start(argptr, msg);
	vsprintf(text, msg, argptr);
	va_end(argptr);

	CG_Printf("%s", text);
}

#endif

/*
================
CG_Argv
================
*/
const char *CG_Argv(int arg)
{
	static char buffer[MAX_STRING_CHARS];

	trap_Argv(arg, buffer, sizeof(buffer));

	return buffer;
}

//========================================================================

/*
=================
CG_RegisterItemSounds

The server says this item is used on this level
=================
*/
static void CG_RegisterItemSounds(int itemNum)
{
	gitem_t *item;
	char data[MAX_QPATH];
	char *s, *start;
	int len;

	item = &bg_itemlist[itemNum];

	if (item->pickup_sound) {
		trap_S_RegisterSound(item->pickup_sound, qfalse);
	}
	// parse the space seperated precache string for other media
	s = item->sounds;
	if (!s || !s[0])
		return;

	while (*s) {
		start = s;
		while (*s && *s != ' ') {
			s++;
		}

		len = s - start;
		if (len >= MAX_QPATH || len < 5) {
			CG_Error("PrecacheItem: %s has bad precache string", item->classname);
			return;
		}
		memcpy(data, start, len);
		data[len] = 0;
		if (*s) {
			s++;
		}

		if (!strcmp(data + len - 3, "wav")) {
			trap_S_RegisterSound(data, qfalse);
		}
	}
}

/*
=================
CG_RegisterSounds

called during a precache command
=================
*/
static void CG_RegisterSounds(void)
{
	int i;
	char items[MAX_ITEMS + 1];
	char name[MAX_QPATH];
	const char *soundName;

	// NiceAss: Used for pressure entities. Not implemented yet.
	// cgs.media.steamSound = trap_S_RegisterSound( "sound/steam.wav", qtrue );
	cgs.media.oneMinuteSound = trap_S_RegisterSound("sound/feedback/1_minute.wav", qtrue);
	cgs.media.fiveMinuteSound = trap_S_RegisterSound("sound/feedback/5_minute.wav", qtrue);
	cgs.media.suddenDeathSound = trap_S_RegisterSound("sound/feedback/sudden_death.wav", qtrue);
	cgs.media.oneFragSound = trap_S_RegisterSound("sound/feedback/1_frag.wav", qtrue);
	cgs.media.twoFragSound = trap_S_RegisterSound("sound/feedback/2_frags.wav", qtrue);
	cgs.media.threeFragSound = trap_S_RegisterSound("sound/feedback/3_frags.wav", qtrue);
	cgs.media.count3Sound = trap_S_RegisterSound("sound/feedback/three.wav", qtrue);
	cgs.media.count2Sound = trap_S_RegisterSound("sound/feedback/two.wav", qtrue);
	cgs.media.count1Sound = trap_S_RegisterSound("sound/feedback/one.wav", qtrue);
	cgs.media.countFightSound = trap_S_RegisterSound("sound/feedback/fight.wav", qtrue);
	cgs.media.countPrepareSound = trap_S_RegisterSound("sound/feedback/prepare.wav", qtrue);
// JBravo: The insane sounds
	cgs.media.insanesounds[0] = trap_S_RegisterSound("sound/insane/insane1.wav", qtrue);
	cgs.media.insanesounds[1] = trap_S_RegisterSound("sound/insane/insane2.wav", qtrue);
	cgs.media.insanesounds[2] = trap_S_RegisterSound("sound/insane/insane3.wav", qtrue);
	cgs.media.insanesounds[3] = trap_S_RegisterSound("sound/insane/insane4.wav", qtrue);
	cgs.media.insanesounds[4] = trap_S_RegisterSound("sound/insane/insane5.wav", qtrue);
	cgs.media.insanesounds[5] = trap_S_RegisterSound("sound/insane/insane6.wav", qtrue);
	cgs.media.insanesounds[6] = trap_S_RegisterSound("sound/insane/insane7.wav", qtrue);
	cgs.media.insanesounds[7] = trap_S_RegisterSound("sound/insane/insane8.wav", qtrue);
	cgs.media.insanesounds[8] = trap_S_RegisterSound("sound/insane/insane9.wav", qtrue);
	if (cgs.gametype >= GT_TEAM || cg_buildScript.integer) {
// JBravo: registering the LCA sounds.
		cgs.media.lightsSound = trap_S_RegisterSound("sound/lca/lights.wav", qtrue);
		cgs.media.cameraSound = trap_S_RegisterSound("sound/lca/camera.wav", qtrue);
		cgs.media.actionSound = trap_S_RegisterSound("sound/lca/action.wav", qtrue);
		cgs.media.lca10_0Sound = trap_S_RegisterSound("sound/lca/10_0.wav", qtrue);
// JBravo: and the radio sounds
		//Slicer: optimization.
		cgs.media.male_sounds[0] = trap_S_RegisterSound("sound/radio/male/1.wav", qtrue);
		cgs.media.male_sounds[1] = trap_S_RegisterSound("sound/radio/male/2.wav", qtrue);
		cgs.media.male_sounds[2] = trap_S_RegisterSound("sound/radio/male/3.wav", qtrue);
		cgs.media.male_sounds[3] = trap_S_RegisterSound("sound/radio/male/4.wav", qtrue);
		cgs.media.male_sounds[4] = trap_S_RegisterSound("sound/radio/male/5.wav", qtrue);
		cgs.media.male_sounds[5] = trap_S_RegisterSound("sound/radio/male/6.wav", qtrue);
		cgs.media.male_sounds[6] = trap_S_RegisterSound("sound/radio/male/7.wav", qtrue);
		cgs.media.male_sounds[7] = trap_S_RegisterSound("sound/radio/male/8.wav", qtrue);
		cgs.media.male_sounds[8] = trap_S_RegisterSound("sound/radio/male/9.wav", qtrue);
		cgs.media.male_sounds[9] = trap_S_RegisterSound("sound/radio/male/10.wav", qtrue);
		cgs.media.male_sounds[10] = trap_S_RegisterSound("sound/radio/male/back.wav", qtrue);
		cgs.media.male_sounds[11] = trap_S_RegisterSound("sound/radio/male/cover.wav", qtrue);
		cgs.media.male_sounds[12] = trap_S_RegisterSound("sound/radio/male/down.wav", qtrue);
		cgs.media.male_sounds[13] = trap_S_RegisterSound("sound/radio/male/enemyd.wav", qtrue);
		cgs.media.male_sounds[14] = trap_S_RegisterSound("sound/radio/male/enemys.wav", qtrue);
		cgs.media.male_sounds[15] = trap_S_RegisterSound("sound/radio/male/forward.wav", qtrue);
		cgs.media.male_sounds[16] = trap_S_RegisterSound("sound/radio/male/go.wav", qtrue);
		cgs.media.male_sounds[17] = trap_S_RegisterSound("sound/radio/male/im_hit.wav", qtrue);
		cgs.media.male_sounds[18] = trap_S_RegisterSound("sound/radio/male/left.wav", qtrue);
		cgs.media.male_sounds[19] = trap_S_RegisterSound("sound/radio/male/reportin.wav", qtrue);
		cgs.media.male_sounds[20] = trap_S_RegisterSound("sound/radio/male/right.wav", qtrue);
		cgs.media.male_sounds[21] = trap_S_RegisterSound("sound/radio/male/taking_f.wav", qtrue);
		cgs.media.male_sounds[22] = trap_S_RegisterSound("sound/radio/male/teamdown.wav", qtrue);
		cgs.media.male_sounds[23] = trap_S_RegisterSound("sound/radio/male/treport.wav", qtrue);
		cgs.media.male_sounds[24] = trap_S_RegisterSound("sound/radio/male/up.wav", qtrue);
		cgs.media.male_sounds[25] = trap_S_RegisterSound("sound/radio/click.wav", qtrue);
		cgs.media.male_sounds[26] = trap_S_RegisterSound("sound/radio/male/backup1.wav", qtrue);
		cgs.media.male_sounds[27] = trap_S_RegisterSound("sound/radio/male/backup2.wav", qtrue);
		cgs.media.male_sounds[28] = trap_S_RegisterSound("sound/radio/male/backup3.wav", qtrue);
		cgs.media.male_sounds[29] = trap_S_RegisterSound("sound/radio/male/chit1.wav", qtrue);
		cgs.media.male_sounds[30] = trap_S_RegisterSound("sound/radio/male/chit2.wav", qtrue);
		cgs.media.male_sounds[31] = trap_S_RegisterSound("sound/radio/male/chit3.wav", qtrue);
		cgs.media.male_sounds[32] = trap_S_RegisterSound("sound/radio/male/deliv1.wav", qtrue);
		cgs.media.male_sounds[33] = trap_S_RegisterSound("sound/radio/male/deliv2.wav", qtrue);
		cgs.media.male_sounds[34] = trap_S_RegisterSound("sound/radio/male/deliv3.wav", qtrue);
		cgs.media.male_sounds[35] = trap_S_RegisterSound("sound/radio/male/ecdown1.wav", qtrue);
		cgs.media.male_sounds[36] = trap_S_RegisterSound("sound/radio/male/ecdown2.wav", qtrue);
		cgs.media.male_sounds[37] = trap_S_RegisterSound("sound/radio/male/ecdown3.wav", qtrue);
		cgs.media.male_sounds[38] = trap_S_RegisterSound("sound/radio/male/enepak1.wav", qtrue);
		cgs.media.male_sounds[39] = trap_S_RegisterSound("sound/radio/male/enepak2.wav", qtrue);
		cgs.media.male_sounds[40] = trap_S_RegisterSound("sound/radio/male/enepak3.wav", qtrue);
		cgs.media.male_sounds[41] = trap_S_RegisterSound("sound/radio/male/escort1.wav", qtrue);
		cgs.media.male_sounds[42] = trap_S_RegisterSound("sound/radio/male/escort2.wav", qtrue);
		cgs.media.male_sounds[43] = trap_S_RegisterSound("sound/radio/male/escort3.wav", qtrue);
		cgs.media.male_sounds[44] = trap_S_RegisterSound("sound/radio/male/gotpak1.wav", qtrue);
		cgs.media.male_sounds[45] = trap_S_RegisterSound("sound/radio/male/gotpak2.wav", qtrue);
		cgs.media.male_sounds[46] = trap_S_RegisterSound("sound/radio/male/gotpak3.wav", qtrue);
		cgs.media.male_sounds[47] = trap_S_RegisterSound("sound/radio/male/guard1.wav", qtrue);
		cgs.media.male_sounds[48] = trap_S_RegisterSound("sound/radio/male/guard2.wav", qtrue);
		cgs.media.male_sounds[49] = trap_S_RegisterSound("sound/radio/male/guard3.wav", qtrue);
		cgs.media.male_sounds[50] = trap_S_RegisterSound("sound/radio/male/incoming1.wav", qtrue);
		cgs.media.male_sounds[51] = trap_S_RegisterSound("sound/radio/male/incoming2.wav", qtrue);
		cgs.media.male_sounds[52] = trap_S_RegisterSound("sound/radio/male/incoming3.wav", qtrue);
		cgs.media.male_sounds[53] = trap_S_RegisterSound("sound/radio/male/plost1.wav", qtrue);
		cgs.media.male_sounds[54] = trap_S_RegisterSound("sound/radio/male/plost2.wav", qtrue);
		cgs.media.male_sounds[55] = trap_S_RegisterSound("sound/radio/male/plost3.wav", qtrue);
		cgs.media.new_male_sounds[0] = trap_S_RegisterSound("sound/newradio/male/1.wav", qtrue);
		cgs.media.new_male_sounds[1] = trap_S_RegisterSound("sound/newradio/male/2.wav", qtrue);
		cgs.media.new_male_sounds[2] = trap_S_RegisterSound("sound/newradio/male/3.wav", qtrue);
		cgs.media.new_male_sounds[3] = trap_S_RegisterSound("sound/newradio/male/4.wav", qtrue);
		cgs.media.new_male_sounds[4] = trap_S_RegisterSound("sound/newradio/male/5.wav", qtrue);
		cgs.media.new_male_sounds[5] = trap_S_RegisterSound("sound/newradio/male/6.wav", qtrue);
		cgs.media.new_male_sounds[6] = trap_S_RegisterSound("sound/newradio/male/7.wav", qtrue);
		cgs.media.new_male_sounds[7] = trap_S_RegisterSound("sound/newradio/male/8.wav", qtrue);
		cgs.media.new_male_sounds[8] = trap_S_RegisterSound("sound/newradio/male/9.wav", qtrue);
		cgs.media.new_male_sounds[9] = trap_S_RegisterSound("sound/newradio/male/10.wav", qtrue);
		cgs.media.new_male_sounds[10] = trap_S_RegisterSound("sound/newradio/male/back.wav", qtrue);
		cgs.media.new_male_sounds[11] = trap_S_RegisterSound("sound/newradio/male/cover.wav", qtrue);
		cgs.media.new_male_sounds[12] = trap_S_RegisterSound("sound/newradio/male/down.wav", qtrue);
		cgs.media.new_male_sounds[13] = trap_S_RegisterSound("sound/newradio/male/enemyd.wav", qtrue);
		cgs.media.new_male_sounds[14] = trap_S_RegisterSound("sound/newradio/male/enemys.wav", qtrue);
		cgs.media.new_male_sounds[15] = trap_S_RegisterSound("sound/newradio/male/forward.wav", qtrue);
		cgs.media.new_male_sounds[16] = trap_S_RegisterSound("sound/newradio/male/go.wav", qtrue);
		cgs.media.new_male_sounds[17] = trap_S_RegisterSound("sound/newradio/male/im_hit.wav", qtrue);
		cgs.media.new_male_sounds[18] = trap_S_RegisterSound("sound/newradio/male/left.wav", qtrue);
		cgs.media.new_male_sounds[19] = trap_S_RegisterSound("sound/newradio/male/reportin.wav", qtrue);
		cgs.media.new_male_sounds[20] = trap_S_RegisterSound("sound/newradio/male/right.wav", qtrue);
		cgs.media.new_male_sounds[21] = trap_S_RegisterSound("sound/newradio/male/taking_f.wav", qtrue);
		cgs.media.new_male_sounds[22] = trap_S_RegisterSound("sound/newradio/male/teamdown.wav", qtrue);
		cgs.media.new_male_sounds[23] = trap_S_RegisterSound("sound/newradio/male/treport.wav", qtrue);
		cgs.media.new_male_sounds[24] = trap_S_RegisterSound("sound/newradio/male/up.wav", qtrue);
		cgs.media.new_male_sounds[25] = trap_S_RegisterSound("sound/radio/click.wav", qtrue);
		cgs.media.new_male_sounds[26] = trap_S_RegisterSound("sound/newradio/male/backup1.wav", qtrue);
		cgs.media.new_male_sounds[27] = trap_S_RegisterSound("sound/newradio/male/backup2.wav", qtrue);
		cgs.media.new_male_sounds[28] = trap_S_RegisterSound("sound/newradio/male/backup3.wav", qtrue);
		cgs.media.new_male_sounds[29] = trap_S_RegisterSound("sound/newradio/male/chit1.wav", qtrue);
		cgs.media.new_male_sounds[30] = trap_S_RegisterSound("sound/newradio/male/chit2.wav", qtrue);
		cgs.media.new_male_sounds[31] = trap_S_RegisterSound("sound/newradio/male/chit3.wav", qtrue);
		cgs.media.new_male_sounds[32] = trap_S_RegisterSound("sound/newradio/male/deliv1.wav", qtrue);
		cgs.media.new_male_sounds[33] = trap_S_RegisterSound("sound/newradio/male/deliv2.wav", qtrue);
		cgs.media.new_male_sounds[34] = trap_S_RegisterSound("sound/newradio/male/deliv3.wav", qtrue);
		cgs.media.new_male_sounds[35] = trap_S_RegisterSound("sound/newradio/male/ecdown1.wav", qtrue);
		cgs.media.new_male_sounds[36] = trap_S_RegisterSound("sound/newradio/male/ecdown2.wav", qtrue);
		cgs.media.new_male_sounds[37] = trap_S_RegisterSound("sound/newradio/male/ecdown3.wav", qtrue);
		cgs.media.new_male_sounds[38] = trap_S_RegisterSound("sound/newradio/male/enepak1.wav", qtrue);
		cgs.media.new_male_sounds[39] = trap_S_RegisterSound("sound/newradio/male/enepak2.wav", qtrue);
		cgs.media.new_male_sounds[40] = trap_S_RegisterSound("sound/newradio/male/enepak3.wav", qtrue);
		cgs.media.new_male_sounds[41] = trap_S_RegisterSound("sound/newradio/male/escort1.wav", qtrue);
		cgs.media.new_male_sounds[42] = trap_S_RegisterSound("sound/newradio/male/escort2.wav", qtrue);
		cgs.media.new_male_sounds[43] = trap_S_RegisterSound("sound/newradio/male/escort3.wav", qtrue);
		cgs.media.new_male_sounds[44] = trap_S_RegisterSound("sound/newradio/male/gotpak1.wav", qtrue);
		cgs.media.new_male_sounds[45] = trap_S_RegisterSound("sound/newradio/male/gotpak2.wav", qtrue);
		cgs.media.new_male_sounds[46] = trap_S_RegisterSound("sound/newradio/male/gotpak3.wav", qtrue);
		cgs.media.new_male_sounds[47] = trap_S_RegisterSound("sound/newradio/male/guard1.wav", qtrue);
		cgs.media.new_male_sounds[48] = trap_S_RegisterSound("sound/newradio/male/guard2.wav", qtrue);
		cgs.media.new_male_sounds[49] = trap_S_RegisterSound("sound/newradio/male/guard3.wav", qtrue);
		cgs.media.new_male_sounds[50] = trap_S_RegisterSound("sound/newradio/male/incoming1.wav", qtrue);
		cgs.media.new_male_sounds[51] = trap_S_RegisterSound("sound/newradio/male/incoming2.wav", qtrue);
		cgs.media.new_male_sounds[52] = trap_S_RegisterSound("sound/newradio/male/incoming3.wav", qtrue);
		cgs.media.new_male_sounds[53] = trap_S_RegisterSound("sound/newradio/male/plost1.wav", qtrue);
		cgs.media.new_male_sounds[54] = trap_S_RegisterSound("sound/newradio/male/plost2.wav", qtrue);
		cgs.media.new_male_sounds[55] = trap_S_RegisterSound("sound/newradio/male/plost3.wav", qtrue);
		cgs.media.pikey_male_sounds[0] = trap_S_RegisterSound("sound/newradio/pikey/1.wav", qtrue);
		cgs.media.pikey_male_sounds[1] = trap_S_RegisterSound("sound/newradio/pikey/2.wav", qtrue);
		cgs.media.pikey_male_sounds[2] = trap_S_RegisterSound("sound/newradio/pikey/3.wav", qtrue);
		cgs.media.pikey_male_sounds[3] = trap_S_RegisterSound("sound/newradio/pikey/4.wav", qtrue);
		cgs.media.pikey_male_sounds[4] = trap_S_RegisterSound("sound/newradio/pikey/5.wav", qtrue);
		cgs.media.pikey_male_sounds[5] = trap_S_RegisterSound("sound/newradio/pikey/6.wav", qtrue);
		cgs.media.pikey_male_sounds[6] = trap_S_RegisterSound("sound/newradio/pikey/7.wav", qtrue);
		cgs.media.pikey_male_sounds[7] = trap_S_RegisterSound("sound/newradio/pikey/8.wav", qtrue);
		cgs.media.pikey_male_sounds[8] = trap_S_RegisterSound("sound/newradio/pikey/9.wav", qtrue);
		cgs.media.pikey_male_sounds[9] = trap_S_RegisterSound("sound/newradio/pikey/10.wav", qtrue);
		cgs.media.pikey_male_sounds[10] = trap_S_RegisterSound("sound/newradio/pikey/back.wav", qtrue);
		cgs.media.pikey_male_sounds[11] = trap_S_RegisterSound("sound/newradio/pikey/cover.wav", qtrue);
		cgs.media.pikey_male_sounds[12] = trap_S_RegisterSound("sound/newradio/pikey/down.wav", qtrue);
		cgs.media.pikey_male_sounds[13] = trap_S_RegisterSound("sound/newradio/pikey/enemyd.wav", qtrue);
		cgs.media.pikey_male_sounds[14] = trap_S_RegisterSound("sound/newradio/pikey/enemys.wav", qtrue);
		cgs.media.pikey_male_sounds[15] = trap_S_RegisterSound("sound/newradio/pikey/forward.wav", qtrue);
		cgs.media.pikey_male_sounds[16] = trap_S_RegisterSound("sound/newradio/pikey/go.wav", qtrue);
		cgs.media.pikey_male_sounds[17] = trap_S_RegisterSound("sound/newradio/pikey/im_hit.wav", qtrue);
		cgs.media.pikey_male_sounds[18] = trap_S_RegisterSound("sound/newradio/pikey/left.wav", qtrue);
		cgs.media.pikey_male_sounds[19] = trap_S_RegisterSound("sound/newradio/pikey/reportin.wav", qtrue);
		cgs.media.pikey_male_sounds[20] = trap_S_RegisterSound("sound/newradio/pikey/right.wav", qtrue);
		cgs.media.pikey_male_sounds[21] = trap_S_RegisterSound("sound/newradio/pikey/taking_f.wav", qtrue);
		cgs.media.pikey_male_sounds[22] = trap_S_RegisterSound("sound/newradio/pikey/teamdown.wav", qtrue);
		cgs.media.pikey_male_sounds[23] = trap_S_RegisterSound("sound/newradio/pikey/treport.wav", qtrue);
		cgs.media.pikey_male_sounds[24] = trap_S_RegisterSound("sound/newradio/pikey/up.wav", qtrue);
		cgs.media.pikey_male_sounds[25] = trap_S_RegisterSound("sound/radio/click.wav", qtrue);
		cgs.media.pikey_male_sounds[26] = trap_S_RegisterSound("sound/newradio/pikey/backup1.wav", qtrue);
		cgs.media.pikey_male_sounds[27] = trap_S_RegisterSound("sound/newradio/pikey/backup2.wav", qtrue);
		cgs.media.pikey_male_sounds[28] = trap_S_RegisterSound("sound/newradio/pikey/backup3.wav", qtrue);
		cgs.media.pikey_male_sounds[29] = trap_S_RegisterSound("sound/newradio/pikey/chit1.wav", qtrue);
		cgs.media.pikey_male_sounds[30] = trap_S_RegisterSound("sound/newradio/pikey/chit2.wav", qtrue);
		cgs.media.pikey_male_sounds[31] = trap_S_RegisterSound("sound/newradio/pikey/chit3.wav", qtrue);
		cgs.media.pikey_male_sounds[32] = trap_S_RegisterSound("sound/newradio/pikey/deliv1.wav", qtrue);
		cgs.media.pikey_male_sounds[33] = trap_S_RegisterSound("sound/newradio/pikey/deliv2.wav", qtrue);
		cgs.media.pikey_male_sounds[34] = trap_S_RegisterSound("sound/newradio/pikey/deliv3.wav", qtrue);
		cgs.media.pikey_male_sounds[35] = trap_S_RegisterSound("sound/newradio/pikey/ecdown1.wav", qtrue);
		cgs.media.pikey_male_sounds[36] = trap_S_RegisterSound("sound/newradio/pikey/ecdown2.wav", qtrue);
		cgs.media.pikey_male_sounds[37] = trap_S_RegisterSound("sound/newradio/pikey/ecdown3.wav", qtrue);
		cgs.media.pikey_male_sounds[38] = trap_S_RegisterSound("sound/newradio/pikey/enepak1.wav", qtrue);
		cgs.media.pikey_male_sounds[39] = trap_S_RegisterSound("sound/newradio/pikey/enepak2.wav", qtrue);
		cgs.media.pikey_male_sounds[40] = trap_S_RegisterSound("sound/newradio/pikey/enepak3.wav", qtrue);
		cgs.media.pikey_male_sounds[41] = trap_S_RegisterSound("sound/newradio/pikey/escort1.wav", qtrue);
		cgs.media.pikey_male_sounds[42] = trap_S_RegisterSound("sound/newradio/pikey/escort2.wav", qtrue);
		cgs.media.pikey_male_sounds[43] = trap_S_RegisterSound("sound/newradio/pikey/escort3.wav", qtrue);
		cgs.media.pikey_male_sounds[44] = trap_S_RegisterSound("sound/newradio/pikey/gotpak1.wav", qtrue);
		cgs.media.pikey_male_sounds[45] = trap_S_RegisterSound("sound/newradio/pikey/gotpak2.wav", qtrue);
		cgs.media.pikey_male_sounds[46] = trap_S_RegisterSound("sound/newradio/pikey/gotpak3.wav", qtrue);
		cgs.media.pikey_male_sounds[47] = trap_S_RegisterSound("sound/newradio/pikey/guard1.wav", qtrue);
		cgs.media.pikey_male_sounds[48] = trap_S_RegisterSound("sound/newradio/pikey/guard2.wav", qtrue);
		cgs.media.pikey_male_sounds[49] = trap_S_RegisterSound("sound/newradio/pikey/guard3.wav", qtrue);
		cgs.media.pikey_male_sounds[50] = trap_S_RegisterSound("sound/newradio/pikey/incoming1.wav", qtrue);
		cgs.media.pikey_male_sounds[51] = trap_S_RegisterSound("sound/newradio/pikey/incoming2.wav", qtrue);
		cgs.media.pikey_male_sounds[52] = trap_S_RegisterSound("sound/newradio/pikey/incoming3.wav", qtrue);
		cgs.media.pikey_male_sounds[53] = trap_S_RegisterSound("sound/newradio/pikey/plost1.wav", qtrue);
		cgs.media.pikey_male_sounds[54] = trap_S_RegisterSound("sound/newradio/pikey/plost2.wav", qtrue);
		cgs.media.pikey_male_sounds[55] = trap_S_RegisterSound("sound/newradio/pikey/plost3.wav", qtrue);
		cgs.media.pirate_male_sounds[0] = trap_S_RegisterSound("sound/newradio/pirate/1.wav", qtrue);
		cgs.media.pirate_male_sounds[1] = trap_S_RegisterSound("sound/newradio/pirate/2.wav", qtrue);
		cgs.media.pirate_male_sounds[2] = trap_S_RegisterSound("sound/newradio/pirate/3.wav", qtrue);
		cgs.media.pirate_male_sounds[3] = trap_S_RegisterSound("sound/newradio/pirate/4.wav", qtrue);
		cgs.media.pirate_male_sounds[4] = trap_S_RegisterSound("sound/newradio/pirate/5.wav", qtrue);
		cgs.media.pirate_male_sounds[5] = trap_S_RegisterSound("sound/newradio/pirate/6.wav", qtrue);
		cgs.media.pirate_male_sounds[6] = trap_S_RegisterSound("sound/newradio/pirate/7.wav", qtrue);
		cgs.media.pirate_male_sounds[7] = trap_S_RegisterSound("sound/newradio/pirate/8.wav", qtrue);
		cgs.media.pirate_male_sounds[8] = trap_S_RegisterSound("sound/newradio/pirate/9.wav", qtrue);
		cgs.media.pirate_male_sounds[9] = trap_S_RegisterSound("sound/newradio/pirate/10.wav", qtrue);
		cgs.media.pirate_male_sounds[10] = trap_S_RegisterSound("sound/newradio/pirate/back.wav", qtrue);
		cgs.media.pirate_male_sounds[11] = trap_S_RegisterSound("sound/newradio/pirate/cover.wav", qtrue);
		cgs.media.pirate_male_sounds[12] = trap_S_RegisterSound("sound/newradio/pirate/down.wav", qtrue);
		cgs.media.pirate_male_sounds[13] = trap_S_RegisterSound("sound/newradio/pirate/enemyd.wav", qtrue);
		cgs.media.pirate_male_sounds[14] = trap_S_RegisterSound("sound/newradio/pirate/enemys.wav", qtrue);
		cgs.media.pirate_male_sounds[15] = trap_S_RegisterSound("sound/newradio/pirate/forward.wav", qtrue);
		cgs.media.pirate_male_sounds[16] = trap_S_RegisterSound("sound/newradio/pirate/go.wav", qtrue);
		cgs.media.pirate_male_sounds[17] = trap_S_RegisterSound("sound/newradio/pirate/im_hit.wav", qtrue);
		cgs.media.pirate_male_sounds[18] = trap_S_RegisterSound("sound/newradio/pirate/left.wav", qtrue);
		cgs.media.pirate_male_sounds[19] = trap_S_RegisterSound("sound/newradio/pirate/reportin.wav", qtrue);
		cgs.media.pirate_male_sounds[20] = trap_S_RegisterSound("sound/newradio/pirate/right.wav", qtrue);
		cgs.media.pirate_male_sounds[21] = trap_S_RegisterSound("sound/newradio/pirate/taking_f.wav", qtrue);
		cgs.media.pirate_male_sounds[22] = trap_S_RegisterSound("sound/newradio/pirate/teamdown.wav", qtrue);
		cgs.media.pirate_male_sounds[23] = trap_S_RegisterSound("sound/newradio/pirate/treport.wav", qtrue);
		cgs.media.pirate_male_sounds[24] = trap_S_RegisterSound("sound/newradio/pirate/up.wav", qtrue);
		cgs.media.pirate_male_sounds[25] = trap_S_RegisterSound("sound/radio/click.wav", qtrue);
		cgs.media.pirate_male_sounds[26] = trap_S_RegisterSound("sound/newradio/pirate/backup1.wav", qtrue);
		cgs.media.pirate_male_sounds[27] = trap_S_RegisterSound("sound/newradio/pirate/backup2.wav", qtrue);
		cgs.media.pirate_male_sounds[28] = trap_S_RegisterSound("sound/newradio/pirate/backup3.wav", qtrue);
		cgs.media.pirate_male_sounds[29] = trap_S_RegisterSound("sound/newradio/pirate/chit1.wav", qtrue);
		cgs.media.pirate_male_sounds[30] = trap_S_RegisterSound("sound/newradio/pirate/chit2.wav", qtrue);
		cgs.media.pirate_male_sounds[31] = trap_S_RegisterSound("sound/newradio/pirate/chit3.wav", qtrue);
		cgs.media.pirate_male_sounds[32] = trap_S_RegisterSound("sound/newradio/pirate/deliv1.wav", qtrue);
		cgs.media.pirate_male_sounds[33] = trap_S_RegisterSound("sound/newradio/pirate/deliv2.wav", qtrue);
		cgs.media.pirate_male_sounds[34] = trap_S_RegisterSound("sound/newradio/pirate/deliv3.wav", qtrue);
		cgs.media.pirate_male_sounds[35] = trap_S_RegisterSound("sound/newradio/pirate/ecdown1.wav", qtrue);
		cgs.media.pirate_male_sounds[36] = trap_S_RegisterSound("sound/newradio/pirate/ecdown2.wav", qtrue);
		cgs.media.pirate_male_sounds[37] = trap_S_RegisterSound("sound/newradio/pirate/ecdown3.wav", qtrue);
		cgs.media.pirate_male_sounds[38] = trap_S_RegisterSound("sound/newradio/pirate/enepak1.wav", qtrue);
		cgs.media.pirate_male_sounds[39] = trap_S_RegisterSound("sound/newradio/pirate/enepak2.wav", qtrue);
		cgs.media.pirate_male_sounds[40] = trap_S_RegisterSound("sound/newradio/pirate/enepak3.wav", qtrue);
		cgs.media.pirate_male_sounds[41] = trap_S_RegisterSound("sound/newradio/pirate/escort1.wav", qtrue);
		cgs.media.pirate_male_sounds[42] = trap_S_RegisterSound("sound/newradio/pirate/escort2.wav", qtrue);
		cgs.media.pirate_male_sounds[43] = trap_S_RegisterSound("sound/newradio/pirate/escort3.wav", qtrue);
		cgs.media.pirate_male_sounds[44] = trap_S_RegisterSound("sound/newradio/pirate/gotpak1.wav", qtrue);
		cgs.media.pirate_male_sounds[45] = trap_S_RegisterSound("sound/newradio/pirate/gotpak2.wav", qtrue);
		cgs.media.pirate_male_sounds[46] = trap_S_RegisterSound("sound/newradio/pirate/gotpak3.wav", qtrue);
		cgs.media.pirate_male_sounds[47] = trap_S_RegisterSound("sound/newradio/pirate/guard1.wav", qtrue);
		cgs.media.pirate_male_sounds[48] = trap_S_RegisterSound("sound/newradio/pirate/guard2.wav", qtrue);
		cgs.media.pirate_male_sounds[49] = trap_S_RegisterSound("sound/newradio/pirate/guard3.wav", qtrue);
		cgs.media.pirate_male_sounds[50] = trap_S_RegisterSound("sound/newradio/pirate/incoming1.wav", qtrue);
		cgs.media.pirate_male_sounds[51] = trap_S_RegisterSound("sound/newradio/pirate/incoming2.wav", qtrue);
		cgs.media.pirate_male_sounds[52] = trap_S_RegisterSound("sound/newradio/pirate/incoming3.wav", qtrue);
		cgs.media.pirate_male_sounds[53] = trap_S_RegisterSound("sound/newradio/pirate/plost1.wav", qtrue);
		cgs.media.pirate_male_sounds[54] = trap_S_RegisterSound("sound/newradio/pirate/plost2.wav", qtrue);
		cgs.media.pirate_male_sounds[55] = trap_S_RegisterSound("sound/newradio/pirate/plost3.wav", qtrue);
		cgs.media.keanu_male_sounds[0] = trap_S_RegisterSound("sound/newradio/keanu/1.wav", qtrue);
		cgs.media.keanu_male_sounds[1] = trap_S_RegisterSound("sound/newradio/keanu/2.wav", qtrue);
		cgs.media.keanu_male_sounds[2] = trap_S_RegisterSound("sound/newradio/keanu/3.wav", qtrue);
		cgs.media.keanu_male_sounds[3] = trap_S_RegisterSound("sound/newradio/keanu/4.wav", qtrue);
		cgs.media.keanu_male_sounds[4] = trap_S_RegisterSound("sound/newradio/keanu/5.wav", qtrue);
		cgs.media.keanu_male_sounds[5] = trap_S_RegisterSound("sound/newradio/keanu/6.wav", qtrue);
		cgs.media.keanu_male_sounds[6] = trap_S_RegisterSound("sound/newradio/keanu/7.wav", qtrue);
		cgs.media.keanu_male_sounds[7] = trap_S_RegisterSound("sound/newradio/keanu/8.wav", qtrue);
		cgs.media.keanu_male_sounds[8] = trap_S_RegisterSound("sound/newradio/keanu/9.wav", qtrue);
		cgs.media.keanu_male_sounds[9] = trap_S_RegisterSound("sound/newradio/keanu/10.wav", qtrue);
		cgs.media.keanu_male_sounds[10] = trap_S_RegisterSound("sound/newradio/keanu/back.wav", qtrue);
		cgs.media.keanu_male_sounds[11] = trap_S_RegisterSound("sound/newradio/keanu/cover.wav", qtrue);
		cgs.media.keanu_male_sounds[12] = trap_S_RegisterSound("sound/newradio/keanu/down.wav", qtrue);
		cgs.media.keanu_male_sounds[13] = trap_S_RegisterSound("sound/newradio/keanu/enemyd.wav", qtrue);
		cgs.media.keanu_male_sounds[14] = trap_S_RegisterSound("sound/newradio/keanu/enemys.wav", qtrue);
		cgs.media.keanu_male_sounds[15] = trap_S_RegisterSound("sound/newradio/keanu/forward.wav", qtrue);
		cgs.media.keanu_male_sounds[16] = trap_S_RegisterSound("sound/newradio/keanu/go.wav", qtrue);
		cgs.media.keanu_male_sounds[17] = trap_S_RegisterSound("sound/newradio/keanu/im_hit.wav", qtrue);
		cgs.media.keanu_male_sounds[18] = trap_S_RegisterSound("sound/newradio/keanu/left.wav", qtrue);
		cgs.media.keanu_male_sounds[19] = trap_S_RegisterSound("sound/newradio/keanu/reportin.wav", qtrue);
		cgs.media.keanu_male_sounds[20] = trap_S_RegisterSound("sound/newradio/keanu/right.wav", qtrue);
		cgs.media.keanu_male_sounds[21] = trap_S_RegisterSound("sound/newradio/keanu/taking_f.wav", qtrue);
		cgs.media.keanu_male_sounds[22] = trap_S_RegisterSound("sound/newradio/keanu/teamdown.wav", qtrue);
		cgs.media.keanu_male_sounds[23] = trap_S_RegisterSound("sound/newradio/keanu/treport.wav", qtrue);
		cgs.media.keanu_male_sounds[24] = trap_S_RegisterSound("sound/newradio/keanu/up.wav", qtrue);
		cgs.media.keanu_male_sounds[25] = trap_S_RegisterSound("sound/radio/click.wav", qtrue);
		cgs.media.keanu_male_sounds[26] = trap_S_RegisterSound("sound/newradio/keanu/backup1.wav", qtrue);
		cgs.media.keanu_male_sounds[27] = trap_S_RegisterSound("sound/newradio/keanu/backup2.wav", qtrue);
		cgs.media.keanu_male_sounds[28] = trap_S_RegisterSound("sound/newradio/keanu/backup3.wav", qtrue);
		cgs.media.keanu_male_sounds[29] = trap_S_RegisterSound("sound/newradio/keanu/chit1.wav", qtrue);
		cgs.media.keanu_male_sounds[30] = trap_S_RegisterSound("sound/newradio/keanu/chit2.wav", qtrue);
		cgs.media.keanu_male_sounds[31] = trap_S_RegisterSound("sound/newradio/keanu/chit3.wav", qtrue);
		cgs.media.keanu_male_sounds[32] = trap_S_RegisterSound("sound/newradio/keanu/deliv1.wav", qtrue);
		cgs.media.keanu_male_sounds[33] = trap_S_RegisterSound("sound/newradio/keanu/deliv2.wav", qtrue);
		cgs.media.keanu_male_sounds[34] = trap_S_RegisterSound("sound/newradio/keanu/deliv3.wav", qtrue);
		cgs.media.keanu_male_sounds[35] = trap_S_RegisterSound("sound/newradio/keanu/ecdown1.wav", qtrue);
		cgs.media.keanu_male_sounds[36] = trap_S_RegisterSound("sound/newradio/keanu/ecdown2.wav", qtrue);
		cgs.media.keanu_male_sounds[37] = trap_S_RegisterSound("sound/newradio/keanu/ecdown3.wav", qtrue);
		cgs.media.keanu_male_sounds[38] = trap_S_RegisterSound("sound/newradio/keanu/enepak1.wav", qtrue);
		cgs.media.keanu_male_sounds[39] = trap_S_RegisterSound("sound/newradio/keanu/enepak2.wav", qtrue);
		cgs.media.keanu_male_sounds[40] = trap_S_RegisterSound("sound/newradio/keanu/enepak3.wav", qtrue);
		cgs.media.keanu_male_sounds[41] = trap_S_RegisterSound("sound/newradio/keanu/escort1.wav", qtrue);
		cgs.media.keanu_male_sounds[42] = trap_S_RegisterSound("sound/newradio/keanu/escort2.wav", qtrue);
		cgs.media.keanu_male_sounds[43] = trap_S_RegisterSound("sound/newradio/keanu/escort3.wav", qtrue);
		cgs.media.keanu_male_sounds[44] = trap_S_RegisterSound("sound/newradio/keanu/gotpak1.wav", qtrue);
		cgs.media.keanu_male_sounds[45] = trap_S_RegisterSound("sound/newradio/keanu/gotpak2.wav", qtrue);
		cgs.media.keanu_male_sounds[46] = trap_S_RegisterSound("sound/newradio/keanu/gotpak3.wav", qtrue);
		cgs.media.keanu_male_sounds[47] = trap_S_RegisterSound("sound/newradio/keanu/guard1.wav", qtrue);
		cgs.media.keanu_male_sounds[48] = trap_S_RegisterSound("sound/newradio/keanu/guard2.wav", qtrue);
		cgs.media.keanu_male_sounds[49] = trap_S_RegisterSound("sound/newradio/keanu/guard3.wav", qtrue);
		cgs.media.keanu_male_sounds[50] = trap_S_RegisterSound("sound/newradio/keanu/incoming1.wav", qtrue);
		cgs.media.keanu_male_sounds[51] = trap_S_RegisterSound("sound/newradio/keanu/incoming2.wav", qtrue);
		cgs.media.keanu_male_sounds[52] = trap_S_RegisterSound("sound/newradio/keanu/incoming3.wav", qtrue);
		cgs.media.keanu_male_sounds[53] = trap_S_RegisterSound("sound/newradio/keanu/plost1.wav", qtrue);
		cgs.media.keanu_male_sounds[54] = trap_S_RegisterSound("sound/newradio/keanu/plost2.wav", qtrue);
		cgs.media.keanu_male_sounds[55] = trap_S_RegisterSound("sound/newradio/keanu/plost3.wav", qtrue);

		cgs.media.female_sounds[0] = trap_S_RegisterSound("sound/radio/female/1.wav", qtrue);
		cgs.media.female_sounds[1] = trap_S_RegisterSound("sound/radio/female/2.wav", qtrue);
		cgs.media.female_sounds[2] = trap_S_RegisterSound("sound/radio/female/3.wav", qtrue);
		cgs.media.female_sounds[3] = trap_S_RegisterSound("sound/radio/female/4.wav", qtrue);
		cgs.media.female_sounds[4] = trap_S_RegisterSound("sound/radio/female/5.wav", qtrue);
		cgs.media.female_sounds[5] = trap_S_RegisterSound("sound/radio/female/6.wav", qtrue);
		cgs.media.female_sounds[6] = trap_S_RegisterSound("sound/radio/female/7.wav", qtrue);
		cgs.media.female_sounds[7] = trap_S_RegisterSound("sound/radio/female/8.wav", qtrue);
		cgs.media.female_sounds[8] = trap_S_RegisterSound("sound/radio/female/9.wav", qtrue);
		cgs.media.female_sounds[9] = trap_S_RegisterSound("sound/radio/female/10.wav", qtrue);
		cgs.media.female_sounds[10] = trap_S_RegisterSound("sound/radio/female/back.wav", qtrue);
		cgs.media.female_sounds[11] = trap_S_RegisterSound("sound/radio/female/cover.wav", qtrue);
		cgs.media.female_sounds[12] = trap_S_RegisterSound("sound/radio/female/down.wav", qtrue);
		cgs.media.female_sounds[13] = trap_S_RegisterSound("sound/radio/female/enemyd.wav", qtrue);
		cgs.media.female_sounds[14] = trap_S_RegisterSound("sound/radio/female/enemys.wav", qtrue);
		cgs.media.female_sounds[15] = trap_S_RegisterSound("sound/radio/female/forward.wav", qtrue);
		cgs.media.female_sounds[16] = trap_S_RegisterSound("sound/radio/female/go.wav", qtrue);
		cgs.media.female_sounds[17] = trap_S_RegisterSound("sound/radio/female/im_hit.wav", qtrue);
		cgs.media.female_sounds[18] = trap_S_RegisterSound("sound/radio/female/left.wav", qtrue);
		cgs.media.female_sounds[19] = trap_S_RegisterSound("sound/radio/female/reportin.wav", qtrue);
		cgs.media.female_sounds[20] = trap_S_RegisterSound("sound/radio/female/right.wav", qtrue);
		cgs.media.female_sounds[21] = trap_S_RegisterSound("sound/radio/female/taking_f.wav", qtrue);
		cgs.media.female_sounds[22] = trap_S_RegisterSound("sound/radio/female/teamdown.wav", qtrue);
		cgs.media.female_sounds[23] = trap_S_RegisterSound("sound/radio/female/treport.wav", qtrue);
		cgs.media.female_sounds[24] = trap_S_RegisterSound("sound/radio/female/up.wav", qtrue);
		cgs.media.female_sounds[25] = trap_S_RegisterSound("sound/radio/click.wav", qtrue);
		cgs.media.female_sounds[26] = trap_S_RegisterSound("sound/radio/female/backup1.wav", qtrue);
		cgs.media.female_sounds[27] = trap_S_RegisterSound("sound/radio/female/backup2.wav", qtrue);
		cgs.media.female_sounds[28] = trap_S_RegisterSound("sound/radio/female/backup3.wav", qtrue);
		cgs.media.female_sounds[29] = trap_S_RegisterSound("sound/radio/female/chit1.wav", qtrue);
		cgs.media.female_sounds[30] = trap_S_RegisterSound("sound/radio/female/chit2.wav", qtrue);
		cgs.media.female_sounds[31] = trap_S_RegisterSound("sound/radio/female/chit3.wav", qtrue);
		cgs.media.female_sounds[32] = trap_S_RegisterSound("sound/radio/female/deliv1.wav", qtrue);
		cgs.media.female_sounds[33] = trap_S_RegisterSound("sound/radio/female/deliv2.wav", qtrue);
		cgs.media.female_sounds[34] = trap_S_RegisterSound("sound/radio/female/deliv3.wav", qtrue);
		cgs.media.female_sounds[35] = trap_S_RegisterSound("sound/radio/female/ecdown1.wav", qtrue);
		cgs.media.female_sounds[36] = trap_S_RegisterSound("sound/radio/female/ecdown2.wav", qtrue);
		cgs.media.female_sounds[37] = trap_S_RegisterSound("sound/radio/female/ecdown3.wav", qtrue);
		cgs.media.female_sounds[38] = trap_S_RegisterSound("sound/radio/female/enepak1.wav", qtrue);
		cgs.media.female_sounds[39] = trap_S_RegisterSound("sound/radio/female/enepak2.wav", qtrue);
		cgs.media.female_sounds[40] = trap_S_RegisterSound("sound/radio/female/enepak3.wav", qtrue);
		cgs.media.female_sounds[41] = trap_S_RegisterSound("sound/radio/female/escort1.wav", qtrue);
		cgs.media.female_sounds[42] = trap_S_RegisterSound("sound/radio/female/escort2.wav", qtrue);
		cgs.media.female_sounds[43] = trap_S_RegisterSound("sound/radio/female/escort3.wav", qtrue);
		cgs.media.female_sounds[44] = trap_S_RegisterSound("sound/radio/female/gotpak1.wav", qtrue);
		cgs.media.female_sounds[45] = trap_S_RegisterSound("sound/radio/female/gotpak2.wav", qtrue);
		cgs.media.female_sounds[46] = trap_S_RegisterSound("sound/radio/female/gotpak3.wav", qtrue);
		cgs.media.female_sounds[47] = trap_S_RegisterSound("sound/radio/female/guard1.wav", qtrue);
		cgs.media.female_sounds[48] = trap_S_RegisterSound("sound/radio/female/guard2.wav", qtrue);
		cgs.media.female_sounds[49] = trap_S_RegisterSound("sound/radio/female/guard3.wav", qtrue);
		cgs.media.female_sounds[50] = trap_S_RegisterSound("sound/radio/female/incoming1.wav", qtrue);
		cgs.media.female_sounds[51] = trap_S_RegisterSound("sound/radio/female/incoming2.wav", qtrue);
		cgs.media.female_sounds[52] = trap_S_RegisterSound("sound/radio/female/incoming3.wav", qtrue);
		cgs.media.female_sounds[53] = trap_S_RegisterSound("sound/radio/female/plost1.wav", qtrue);
		cgs.media.female_sounds[54] = trap_S_RegisterSound("sound/radio/female/plost2.wav", qtrue);
		cgs.media.female_sounds[55] = trap_S_RegisterSound("sound/radio/female/plost3.wav", qtrue);
		cgs.media.captureAwardSound = trap_S_RegisterSound("sound/teamplay/flagcapture_yourteam.wav", qtrue);
		cgs.media.redLeadsSound = trap_S_RegisterSound("sound/feedback/redleads.wav", qtrue);
		cgs.media.blueLeadsSound = trap_S_RegisterSound("sound/feedback/blueleads.wav", qtrue);
		cgs.media.teamsTiedSound = trap_S_RegisterSound("sound/feedback/teamstied.wav", qtrue);
		cgs.media.hitTeamSound = trap_S_RegisterSound("sound/feedback/hit_teammate.wav", qtrue);

		cgs.media.redScoredSound = trap_S_RegisterSound("sound/teamplay/voc_red_scores.wav", qtrue);
		cgs.media.blueScoredSound = trap_S_RegisterSound("sound/teamplay/voc_blue_scores.wav", qtrue);

		cgs.media.captureYourTeamSound = trap_S_RegisterSound("sound/teamplay/flagcapture_yourteam.wav", qtrue);
		cgs.media.captureOpponentSound = trap_S_RegisterSound("sound/teamplay/flagcapture_opponent.wav", qtrue);

		cgs.media.returnYourTeamSound = trap_S_RegisterSound("sound/teamplay/flagreturn_yourteam.wav", qtrue);
		cgs.media.returnOpponentSound = trap_S_RegisterSound("sound/teamplay/flagreturn_opponent.wav", qtrue);

		cgs.media.takenYourTeamSound = trap_S_RegisterSound("sound/teamplay/flagtaken_yourteam.wav", qtrue);
		cgs.media.takenOpponentSound = trap_S_RegisterSound("sound/teamplay/flagtaken_opponent.wav", qtrue);

		if (cgs.gametype == GT_CTF || cg_buildScript.integer) {
			cgs.media.redFlagReturnedSound =
			    trap_S_RegisterSound("sound/teamplay/voc_red_returned.wav", qtrue);
			cgs.media.blueFlagReturnedSound =
			    trap_S_RegisterSound("sound/teamplay/voc_blue_returned.wav", qtrue);
			cgs.media.enemyTookYourFlagSound =
			    trap_S_RegisterSound("sound/teamplay/voc_enemy_flag.wav", qtrue);
			cgs.media.yourTeamTookEnemyFlagSound =
			    trap_S_RegisterSound("sound/teamplay/voc_team_flag.wav", qtrue);
		}
		cgs.media.youHaveFlagSound = trap_S_RegisterSound("sound/teamplay/voc_you_flag.wav", qtrue);
		cgs.media.holyShitSound = trap_S_RegisterSound("sound/feedback/voc_holyshit.wav", qtrue);
		cgs.media.neutralFlagReturnedSound =
		    trap_S_RegisterSound("sound/teamplay/flagreturn_opponent.wav", qtrue);
		cgs.media.yourTeamTookTheFlagSound = trap_S_RegisterSound("sound/teamplay/voc_team_1flag.wav", qtrue);
		cgs.media.enemyTookTheFlagSound = trap_S_RegisterSound("sound/teamplay/voc_enemy_1flag.wav", qtrue);
	}

	cgs.media.tracerSound = trap_S_RegisterSound("sound/weapons/machinegun/buletby1.wav", qfalse);
	cgs.media.selectSound = trap_S_RegisterSound("sound/weapons/change.wav", qfalse);
	cgs.media.wearOffSound = trap_S_RegisterSound("sound/items/wearoff.wav", qfalse);
	cgs.media.useNothingSound = trap_S_RegisterSound("sound/items/use_nothing.wav", qfalse);
	cgs.media.gibSound = trap_S_RegisterSound("sound/player/gibsplt1.wav", qfalse);
	//Blaze: Reaction breakable glass
	/*cgs.media.glassSound = trap_S_RegisterSound( "sound/world/glassbk.wav", qfalse );
	   cgs.media.glass2Sound = trap_S_RegisterSound( "sound/world/glassbk2.wav", qfalse ); */
	cgs.media.gibBounce1Sound = trap_S_RegisterSound("sound/player/gibimp1.wav", qfalse);
	cgs.media.gibBounce2Sound = trap_S_RegisterSound("sound/player/gibimp2.wav", qfalse);
	cgs.media.gibBounce3Sound = trap_S_RegisterSound("sound/player/gibimp3.wav", qfalse);

	//Elder: RQ3 sounds
	cgs.media.kickSound = trap_S_RegisterSound("sound/misc/kick.wav", qfalse);
	cgs.media.lensSound = trap_S_RegisterSound("sound/misc/lens.wav", qfalse);
	cgs.media.headshotSound = trap_S_RegisterSound("sound/misc/headshot.wav", qfalse);
	//cgs.media.lcaSound = trap_S_RegisterSound( "sound/misc/lca.wav", qfalse);
	cgs.media.silencerSound = trap_S_RegisterSound("sound/misc/silencershot.wav", qfalse);
	cgs.media.kevlarHitSound = trap_S_RegisterSound("sound/misc/kevlarhit.wav", qfalse);
	cgs.media.weapToggleSound = trap_S_RegisterSound("sound/misc/click.wav", qfalse);
	cgs.media.knifeClankSound = trap_S_RegisterSound("sound/misc/knife_clank.wav", qfalse);
	cgs.media.knifeDeathSound = trap_S_RegisterSound("sound/player/gurp2.wav", qfalse);
	cgs.media.knifeHitSound = trap_S_RegisterSound("sound/misc/knife_hit.wav", qfalse);

	cgs.media.teleInSound = trap_S_RegisterSound("sound/world/telein.wav", qfalse);
	cgs.media.teleOutSound = trap_S_RegisterSound("sound/world/teleout.wav", qfalse);
	cgs.media.respawnSound = trap_S_RegisterSound("sound/items/respawn1.wav", qfalse);

	cgs.media.noAmmoSound = trap_S_RegisterSound("sound/weapons/noammo.wav", qfalse);

	cgs.media.talkSound = trap_S_RegisterSound("sound/player/talk.wav", qfalse);
	cgs.media.landSound = trap_S_RegisterSound("sound/player/land1.wav", qfalse);

	cgs.media.hitSound = trap_S_RegisterSound("sound/feedback/hit.wav", qfalse);

	cgs.media.impressiveSound = trap_S_RegisterSound("sound/feedback/impressive.wav", qtrue);
	cgs.media.excellentSound = trap_S_RegisterSound("sound/feedback/excellent.wav", qtrue);
	cgs.media.deniedSound = trap_S_RegisterSound("sound/feedback/denied.wav", qtrue);
	cgs.media.humiliationSound = trap_S_RegisterSound("sound/feedback/humiliation.wav", qtrue);
	cgs.media.assistSound = trap_S_RegisterSound("sound/feedback/assist.wav", qtrue);
	cgs.media.defendSound = trap_S_RegisterSound("sound/feedback/defense.wav", qtrue);

	cgs.media.takenLeadSound = trap_S_RegisterSound("sound/feedback/takenlead.wav", qtrue);
	cgs.media.tiedLeadSound = trap_S_RegisterSound("sound/feedback/tiedlead.wav", qtrue);
	cgs.media.lostLeadSound = trap_S_RegisterSound("sound/feedback/lostlead.wav", qtrue);

	cgs.media.watrInSound = trap_S_RegisterSound("sound/player/watr_in.wav", qfalse);
	cgs.media.watrOutSound = trap_S_RegisterSound("sound/player/watr_out.wav", qfalse);
	cgs.media.watrUnSound = trap_S_RegisterSound("sound/player/watr_un.wav", qfalse);

	cgs.media.jumpPadSound = trap_S_RegisterSound("sound/world/jumppad.wav", qfalse);

	for (i = 0; i < 4; i++) {
		Com_sprintf(name, sizeof(name), "sound/player/footsteps/step%i.wav", i + 1);
		cgs.media.footsteps[FOOTSTEP_NORMAL][i] = trap_S_RegisterSound(name, qfalse);

		Com_sprintf(name, sizeof(name), "sound/player/footsteps/boot%i.wav", i + 1);
		cgs.media.footsteps[FOOTSTEP_BOOT][i] = trap_S_RegisterSound(name, qfalse);

		Com_sprintf(name, sizeof(name), "sound/player/footsteps/flesh%i.wav", i + 1);
		cgs.media.footsteps[FOOTSTEP_FLESH][i] = trap_S_RegisterSound(name, qfalse);

		Com_sprintf(name, sizeof(name), "sound/player/footsteps/mech%i.wav", i + 1);
		cgs.media.footsteps[FOOTSTEP_MECH][i] = trap_S_RegisterSound(name, qfalse);

		Com_sprintf(name, sizeof(name), "sound/player/footsteps/energy%i.wav", i + 1);
		cgs.media.footsteps[FOOTSTEP_ENERGY][i] = trap_S_RegisterSound(name, qfalse);

		Com_sprintf(name, sizeof(name), "sound/player/footsteps/splash%i.wav", i + 1);
		cgs.media.footsteps[FOOTSTEP_SPLASH][i] = trap_S_RegisterSound(name, qfalse);

		Com_sprintf(name, sizeof(name), "sound/player/footsteps/clank%i.wav", i + 1);
		cgs.media.footsteps[FOOTSTEP_METAL][i] = trap_S_RegisterSound(name, qfalse);

		//Elder: new footsteps
		Com_sprintf(name, sizeof(name), "sound/player/footsteps/grass%i.wav", i + 1);
		cgs.media.footsteps[FOOTSTEP_GRASS][i] = trap_S_RegisterSound(name, qfalse);

		Com_sprintf(name, sizeof(name), "sound/player/footsteps/wood%i.wav", i + 1);
		cgs.media.footsteps[FOOTSTEP_WOOD][i] = trap_S_RegisterSound(name, qfalse);

		Com_sprintf(name, sizeof(name), "sound/player/footsteps/carpet%i.wav", i + 1);
		cgs.media.footsteps[FOOTSTEP_CARPET][i] = trap_S_RegisterSound(name, qfalse);

		Com_sprintf(name, sizeof(name), "sound/player/footsteps/metal%i.wav", i + 1);
		cgs.media.footsteps[FOOTSTEP_METAL2][i] = trap_S_RegisterSound(name, qfalse);

		Com_sprintf(name, sizeof(name), "sound/player/footsteps/gravel%i.wav", i + 1);
		cgs.media.footsteps[FOOTSTEP_GRAVEL][i] = trap_S_RegisterSound(name, qfalse);

		Com_sprintf(name, sizeof(name), "sound/player/footsteps/snow%i.wav", i + 1);
		cgs.media.footsteps[FOOTSTEP_SNOW][i] = trap_S_RegisterSound(name, qfalse);

		Com_sprintf(name, sizeof(name), "sound/player/footsteps/mud%i.wav", i + 1);
		cgs.media.footsteps[FOOTSTEP_MUD][i] = trap_S_RegisterSound(name, qfalse);

		Com_sprintf(name, sizeof(name), "sound/player/footsteps/hollowwood%i.wav", i + 1);
		cgs.media.footsteps[FOOTSTEP_WOOD2][i] = trap_S_RegisterSound(name, qfalse);

		Com_sprintf(name, sizeof(name), "sound/player/footsteps/hardmetal%i.wav", i + 1);
		cgs.media.footsteps[FOOTSTEP_HARDMETAL][i] = trap_S_RegisterSound(name, qfalse);

		//Makro - new sounds
		Com_sprintf(name, sizeof(name), "sound/player/footsteps/leaves%i.wav", i + 1);
		cgs.media.footsteps[FOOTSTEP_LEAVES][i] = trap_S_RegisterSound(name, qfalse);

		Com_sprintf(name, sizeof(name), "sound/player/footsteps/cement%i.wav", i + 1);
		cgs.media.footsteps[FOOTSTEP_CEMENT][i] = trap_S_RegisterSound(name, qfalse);

		Com_sprintf(name, sizeof(name), "sound/player/footsteps/marble%i.wav", i + 1);
		cgs.media.footsteps[FOOTSTEP_MARBLE][i] = trap_S_RegisterSound(name, qfalse);

		Com_sprintf(name, sizeof(name), "sound/player/footsteps/snow2_%i.wav", i + 1);
		cgs.media.footsteps[FOOTSTEP_SNOW2][i] = trap_S_RegisterSound(name, qfalse);

		Com_sprintf(name, sizeof(name), "sound/player/footsteps/hardstep%i.wav", i + 1);
		cgs.media.footsteps[FOOTSTEP_HARDSTEPS][i] = trap_S_RegisterSound(name, qfalse);

		Com_sprintf(name, sizeof(name), "sound/player/footsteps/sand%i.wav", i + 1);
		cgs.media.footsteps[FOOTSTEP_SAND][i] = trap_S_RegisterSound(name, qfalse);

	}

	// only register the items that the server says we need
	strcpy(items, CG_ConfigString(CS_ITEMS));

	for (i = 1; i < bg_numItems; i++) {
//              if ( items[ i ] == '1' || cg_buildScript.integer ) {
		CG_RegisterItemSounds(i);
//              }
	}

	for (i = 1; i < MAX_SOUNDS; i++) {
		soundName = CG_ConfigString(CS_SOUNDS + i);
		if (!soundName[0]) {
			break;
		}
		if (soundName[0] == '*') {
			continue;	// custom sound
		}
		cgs.gameSounds[i] = trap_S_RegisterSound(soundName, qfalse);
	}

	// FIXME: only needed with item
	cgs.media.flightSound = trap_S_RegisterSound("sound/items/flight.wav", qfalse);
	cgs.media.medkitSound = trap_S_RegisterSound("sound/items/use_medkit.wav", qfalse);
	cgs.media.quadSound = trap_S_RegisterSound("sound/items/damage3.wav", qfalse);
	cgs.media.sfx_ric1 = trap_S_RegisterSound("sound/weapons/machinegun/ric1.wav", qfalse);
	cgs.media.sfx_ric2 = trap_S_RegisterSound("sound/weapons/machinegun/ric2.wav", qfalse);
	cgs.media.sfx_ric3 = trap_S_RegisterSound("sound/weapons/machinegun/ric3.wav", qfalse);
	// Elder: added
	cgs.media.sfx_metalric1 = trap_S_RegisterSound("sound/world/impactmetal01.wav", qfalse);
	cgs.media.sfx_metalric2 = trap_S_RegisterSound("sound/world/impactmetal02.wav", qfalse);
	cgs.media.sfx_metalric3 = trap_S_RegisterSound("sound/world/impactmetal03.wav", qfalse);
	cgs.media.sfx_glassric1 = trap_S_RegisterSound("sound/world/impactglass01.wav", qfalse);
	cgs.media.sfx_glassric2 = trap_S_RegisterSound("sound/world/impactglass02.wav", qfalse);
	cgs.media.sfx_glassric3 = trap_S_RegisterSound("sound/world/impactglass03.wav", qfalse);
	//Makro - added
	cgs.media.sfx_brickric1 = trap_S_RegisterSound("sound/world/impactbrick01.wav", qfalse);
	cgs.media.sfx_brickric2 = trap_S_RegisterSound("sound/world/impactbrick02.wav", qfalse);
	cgs.media.sfx_brickric3 = trap_S_RegisterSound("sound/world/impactbrick03.wav", qfalse);
	cgs.media.sfx_woodric1 = trap_S_RegisterSound("sound/world/impactwood01.wav", qfalse);
	cgs.media.sfx_woodric2 = trap_S_RegisterSound("sound/world/impactwood02.wav", qfalse);
	cgs.media.sfx_woodric3 = trap_S_RegisterSound("sound/world/impactwood03.wav", qfalse);
	cgs.media.sfx_ceramicric1 = trap_S_RegisterSound("sound/world/impactceramic01.wav", qfalse);
	cgs.media.sfx_ceramicric2 = trap_S_RegisterSound("sound/world/impactceramic02.wav", qfalse);
	cgs.media.sfx_ceramicric3 = trap_S_RegisterSound("sound/world/impactceramic03.wav", qfalse);

	cgs.media.sfx_shelltumble = trap_S_RegisterSound("sound/misc/shell.wav", qfalse);

	cgs.media.sfx_railg = trap_S_RegisterSound("sound/weapons/railgun/railgf1a.wav", qfalse);
	cgs.media.sfx_rockexp = trap_S_RegisterSound("sound/weapons/rocket/rocklx1a.wav", qfalse);
	cgs.media.sfx_plasmaexp = trap_S_RegisterSound("sound/weapons/plasma/plasmx1a.wav", qfalse);

	cgs.media.regenSound = trap_S_RegisterSound("sound/items/regen.wav", qfalse);
	cgs.media.protectSound = trap_S_RegisterSound("sound/items/protect3.wav", qfalse);
	cgs.media.n_healthSound = trap_S_RegisterSound("sound/items/n_health.wav", qfalse);
	cgs.media.hgrenb1aSound = trap_S_RegisterSound("sound/weapons/grenade/hgrenb1a.wav", qfalse);
	cgs.media.hgrenb2aSound = trap_S_RegisterSound("sound/weapons/grenade/hgrenb2a.wav", qfalse);
}

//===================================================================================
/*
=================
CG_CheckFile

  This function checks to see if a file exists
=================
*/
static qboolean CG_CheckFile(const char *fpath)
{
	fileHandle_t f;
	int len;

	len = trap_FS_FOpenFile(fpath, &f, FS_READ);
	if (len == -1) {
		trap_FS_FCloseFile(f);
		return qfalse;
	}
	trap_FS_FCloseFile(f);
	return qtrue;
}

//===================================================================================
/*
=================
CG_RegisterBreakables

  This function registers the breakables
=================
*/
static void CG_RegisterBreakables(void)
{
	int i, id;
	const char *breakInfo;
	const char *name;
	char baseName[80];

	CG_Printf("In registerbreakables\n");
	for (i = 0; i < RQ3_MAX_BREAKABLES; i++) {
		breakInfo = CG_ConfigString(CS_BREAKABLES + i);
		if (!breakInfo[0]) {
			continue;
		}

		id = atoi(Info_ValueForKey(breakInfo, "id"));
		if (id >= 0 && id < RQ3_MAX_BREAKABLES) {
			name = Info_ValueForKey(breakInfo, "type");
			Com_Printf("Registering breakable %s ID=%d\n", name, id);
			//Blaze: Breakable stuff - register the models, sounds, and explosion shader
			if (CG_CheckFile(va("breakables/%s/models/break1.md3", name)) == qtrue) {
				cgs.media.breakables[id].model[0] =
				    trap_R_RegisterModel(va("breakables/%s/models/break1.md3", name));
				cgs.media.breakables[id].model[1] =
				    trap_R_RegisterModel(va("breakables/%s/models/break2.md3", name));
				cgs.media.breakables[id].model[2] =
				    trap_R_RegisterModel(va("breakables/%s/models/break3.md3", name));
			} else {
				strncpy(baseName, name, 80);
				//Makro - crash bug fix; TODO: find a better way to handle this
				if (!strstr(name, "_"))
					return;
				baseName[strstr(name, "_") - name] = '\0';
				cgs.media.breakables[id].model[0] =
				    trap_R_RegisterModel(va("breakables/%s/models/break1.md3", baseName));
				cgs.media.breakables[id].model[1] =
				    trap_R_RegisterModel(va("breakables/%s/models/break2.md3", baseName));
				cgs.media.breakables[id].model[2] =
				    trap_R_RegisterModel(va("breakables/%s/models/break3.md3", baseName));
			}
			if (CG_CheckFile(va("breakables/%s/sounds/break1.wav", name)) == qtrue) {
				cgs.media.breakables[id].sound[0] =
				    trap_S_RegisterSound(va("breakables/%s/sounds/break1.wav", name), qfalse);
				cgs.media.breakables[id].sound[1] =
				    trap_S_RegisterSound(va("breakables/%s/sounds/break2.wav", name), qfalse);
				cgs.media.breakables[id].sound[2] =
				    trap_S_RegisterSound(va("breakables/%s/sounds/break3.wav", name), qfalse);
			} else {
				strncpy(baseName, name, 80);
				baseName[strstr(name, "_") - name] = '\0';
				cgs.media.breakables[id].sound[0] =
				    trap_S_RegisterSound(va("breakables/%s/sounds/break1.wav", baseName), qfalse);
				cgs.media.breakables[id].sound[1] =
				    trap_S_RegisterSound(va("breakables/%s/sounds/break2.wav", baseName), qfalse);
				cgs.media.breakables[id].sound[2] =
				    trap_S_RegisterSound(va("breakables/%s/sounds/break3.wav", baseName), qfalse);
			}
			if (CG_CheckFile(va("breakables/%s/sounds/explosion.wav", name)) == qtrue) {
				cgs.media.breakables[id].exp_sound =
				    trap_S_RegisterSound(va("breakables/%s/sounds/explosion.wav", name), qfalse);
			} else {
				strncpy(baseName, name, 80);
				baseName[strstr(name, "_") - name] = '\0';
				cgs.media.breakables[id].exp_sound =
				    trap_S_RegisterSound(va("breakables/%s/sounds/explosion.wav", baseName), qfalse);
			}

			cgs.media.breakables[id].shader = trap_R_RegisterShader(va("breakable_%s_explosion", name));
			cgs.media.breakables[id].velocity = atoi(Info_ValueForKey(breakInfo, "velocity"));
			cgs.media.breakables[id].jump = atoi(Info_ValueForKey(breakInfo, "jump"));
		} else {
			CG_Printf("ID was %d\n", id);
		}

	}
}

/*
=================
CG_RegisterGraphics

This function may execute for a couple of minutes with a slow disk.
=================
*/
static void CG_RegisterGraphics(void)
{
	int i, num = 0;
	char items[MAX_ITEMS + 1];

	static char *sb_nums[11] = {
		"gfx/2d/numbers/zero_32b",
		"gfx/2d/numbers/one_32b",
		"gfx/2d/numbers/two_32b",
		"gfx/2d/numbers/three_32b",
		"gfx/2d/numbers/four_32b",
		"gfx/2d/numbers/five_32b",
		"gfx/2d/numbers/six_32b",
		"gfx/2d/numbers/seven_32b",
		"gfx/2d/numbers/eight_32b",
		"gfx/2d/numbers/nine_32b",
		"gfx/2d/numbers/minus_32b",
	};

	// clear any references to old media
	memset(&cg.refdef, 0, sizeof(cg.refdef));
	trap_R_ClearScene();

	CG_LoadingString(cgs.mapname);

	trap_R_LoadWorldMap(cgs.mapname);
	cg.loadingMapPercent += 0.45f;

	// precache status bar pics
	CG_LoadingString("game media");

	for (i = 0; i < 11; i++) {
		cgs.media.numberShaders[i] = trap_R_RegisterShader(sb_nums[i]);
	}

	cgs.media.botSkillShaders[0] = trap_R_RegisterShader("menu/art/skill1.tga");
	cgs.media.botSkillShaders[1] = trap_R_RegisterShader("menu/art/skill2.tga");
	cgs.media.botSkillShaders[2] = trap_R_RegisterShader("menu/art/skill3.tga");
	cgs.media.botSkillShaders[3] = trap_R_RegisterShader("menu/art/skill4.tga");
	cgs.media.botSkillShaders[4] = trap_R_RegisterShader("menu/art/skill5.tga");

	cgs.media.viewBloodShader = trap_R_RegisterShader("viewBloodBlend");

	cgs.media.deferShader = trap_R_RegisterShaderNoMip("gfx/2d/defer.tga");

	cgs.media.scoreboardName = trap_R_RegisterShaderNoMip("menu/tab/name.tga");
	cgs.media.scoreboardPing = trap_R_RegisterShaderNoMip("menu/tab/ping.tga");
	cgs.media.scoreboardScore = trap_R_RegisterShaderNoMip("menu/tab/score.tga");
	cgs.media.scoreboardTime = trap_R_RegisterShaderNoMip("menu/tab/time.tga");

	cgs.media.smokePuffShader = trap_R_RegisterShader("smokePuff");
	// Elder: expanding animated smoke puff
	cgs.media.smokePuffAnimShader = trap_R_RegisterShader("smokePuff-rq3");
	cgs.media.smokePuffRageProShader = trap_R_RegisterShader("smokePuffRagePro");
	cgs.media.shotgunSmokePuffShader = trap_R_RegisterShader("shotgunSmokePuff");
	cgs.media.plasmaBallShader = trap_R_RegisterShader("sprites/plasma1");
	cgs.media.bloodTrailShader = trap_R_RegisterShader("bloodTrail");
	cgs.media.lagometerShader = trap_R_RegisterShader("lagometer");
	cgs.media.connectionShader = trap_R_RegisterShader("disconnected");

	cgs.media.flamePressureShader = trap_R_RegisterShader("flamepressure");	// NiceAss: Used in pressure entities
	// cgs.media.waterPressureModel = trap_R_RegisterModel("models/mapobjects/reaction/watercone/watercode.md3");

	cgs.media.waterBubbleShader = trap_R_RegisterShader("waterBubble");

	cgs.media.tracerShader = trap_R_RegisterShader("gfx/misc/tracer");
	cgs.media.selectShader = trap_R_RegisterShader("gfx/2d/select");

	for (i = 0; i < NUM_CROSSHAIRS; i++) {
//              cgs.media.crosshairShader[i] = trap_R_RegisterShader( va("gfx/2d/crosshair%c", 'a'+i) );
		cgs.media.crosshairShader[i] = trap_R_RegisterShaderNoMip(va("gfx/2d/IDcrosshair%c", 'a' + i));
	}

	cgs.media.backTileShader = trap_R_RegisterShader("gfx/2d/backtile");
	cgs.media.noammoShader = trap_R_RegisterShader("icons/noammo");

	// powerup shaders
	cgs.media.quadShader = trap_R_RegisterShader("powerups/quad");
	cgs.media.quadWeaponShader = trap_R_RegisterShader("powerups/quadWeapon");
	cgs.media.battleSuitShader = trap_R_RegisterShader("powerups/battleSuit");
	cgs.media.battleWeaponShader = trap_R_RegisterShader("powerups/battleWeapon");
	cgs.media.invisShader = trap_R_RegisterShader("powerups/invisibility");
	cgs.media.regenShader = trap_R_RegisterShader("powerups/regen");
	cgs.media.hastePuffShader = trap_R_RegisterShader("hasteSmokePuff");

	// Elder: RQ3 misc. shaders
	cgs.media.irPlayerShader = trap_R_RegisterShader("powerups/irdetail");
	cgs.media.itemStrobeShader = trap_R_RegisterShader("rq3-itemstrobe");

	if (cgs.gametype == GT_CTF || cg_buildScript.integer) {
		cgs.media.redCubeModel = trap_R_RegisterModel("models/powerups/orb/r_orb.md3");
		cgs.media.blueCubeModel = trap_R_RegisterModel("models/powerups/orb/b_orb.md3");
		cgs.media.redCubeIcon = trap_R_RegisterShader("icons/skull_red");
		cgs.media.blueCubeIcon = trap_R_RegisterShader("icons/skull_blue");
	}

	if (cgs.gametype == GT_CTF || cg_buildScript.integer) {
//		cgs.media.redFlagModel = trap_R_RegisterModel("models/flags/r_flag.md3");
//		cgs.media.blueFlagModel = trap_R_RegisterModel("models/flags/b_flag.md3");
		cgs.media.redFlagModel = trap_R_RegisterModel("models/cases/s_case.md3");
		cgs.media.blueFlagModel = trap_R_RegisterModel("models/cases/b_case.md3");
		cgs.media.redFlagShader[0] = trap_R_RegisterShaderNoMip("icons/iconc_silver1");
		cgs.media.redFlagShader[1] = trap_R_RegisterShaderNoMip("icons/iconc_silver2");
		cgs.media.redFlagShader[2] = trap_R_RegisterShaderNoMip("icons/iconc_silver3");
		cgs.media.blueFlagShader[0] = trap_R_RegisterShaderNoMip("icons/iconc_black1");
		cgs.media.blueFlagShader[1] = trap_R_RegisterShaderNoMip("icons/iconc_black2");
		cgs.media.blueFlagShader[2] = trap_R_RegisterShaderNoMip("icons/iconc_black3");
/*		cgs.media.redFlagShader[0] = trap_R_RegisterShaderNoMip("icons/iconf_red1");
		cgs.media.redFlagShader[1] = trap_R_RegisterShaderNoMip("icons/iconf_red2");
		cgs.media.redFlagShader[2] = trap_R_RegisterShaderNoMip("icons/iconf_red3");
		cgs.media.blueFlagShader[0] = trap_R_RegisterShaderNoMip("icons/iconf_blu1");
		cgs.media.blueFlagShader[1] = trap_R_RegisterShaderNoMip("icons/iconf_blu2");
		cgs.media.blueFlagShader[2] = trap_R_RegisterShaderNoMip("icons/iconf_blu3"); */
	}
// JBravo: moved outof MISSIONPACK
	cgs.media.dustPuffShader = trap_R_RegisterShader("hasteSmokePuff");

	if (cgs.gametype >= GT_TEAM || cg_buildScript.integer) {
		cgs.media.friendShader = trap_R_RegisterShader("sprites/foe");
		cgs.media.redQuadShader = trap_R_RegisterShader("powerups/blueflag");
		cgs.media.teamStatusBar = trap_R_RegisterShader("gfx/2d/colorbar.tga");
	}

	cgs.media.armorModel = trap_R_RegisterModel("models/powerups/armor/armor_yel.md3");
	cgs.media.armorIcon = trap_R_RegisterShaderNoMip("icons/iconr_yellow");

	cgs.media.machinegunBrassModel = trap_R_RegisterModel("models/weapons2/shells/m_shell.md3");
	cgs.media.largeBrassModel = trap_R_RegisterModel("models/weapons2/shells/l_shell.md3");
	cgs.media.shotgunBrassModel = trap_R_RegisterModel("models/weapons2/shells/s_shell.md3");
	cgs.media.HCBrassModel = trap_R_RegisterModel("models/weapons2/shells/hc_shell.md3");

	cgs.media.gibAbdomen = trap_R_RegisterModel("models/gibs/abdomen.md3");
	cgs.media.gibArm = trap_R_RegisterModel("models/gibs/arm.md3");
	cgs.media.gibChest = trap_R_RegisterModel("models/gibs/chest.md3");
	cgs.media.gibFist = trap_R_RegisterModel("models/gibs/fist.md3");
	cgs.media.gibFoot = trap_R_RegisterModel("models/gibs/foot.md3");
	cgs.media.gibForearm = trap_R_RegisterModel("models/gibs/forearm.md3");
	cgs.media.gibIntestine = trap_R_RegisterModel("models/gibs/intestine.md3");
	cgs.media.gibLeg = trap_R_RegisterModel("models/gibs/leg.md3");
	cgs.media.gibSkull = trap_R_RegisterModel("models/gibs/skull.md3");
	cgs.media.gibBrain = trap_R_RegisterModel("models/gibs/brain.md3");
	//Blaze: Delay loading the breakable stuff
/*
	//Elder: additional debris
	//Todo: load only if in the level
  i++;

	cgs.media.breakable_frag[i][0] = cgs.media.wood01 = trap_R_RegisterModel( "models/breakables/wood01.md3" );
 	cgs.media.breakable_frag[i][1] = cgs.media.wood02 = trap_R_RegisterModel( "models/breakables/wood02.md3" );
 	cgs.media.breakable_frag[i][2] = cgs.media.wood03 = trap_R_RegisterModel( "models/breakables/wood03.md3" );

  i++;
	cgs.media.breakable_frag[i][0] = cgs.media.metal01 = trap_R_RegisterModel( "models/breakables/metal01.md3" );
 	cgs.media.breakable_frag[i][1] = cgs.media.metal02 = trap_R_RegisterModel( "models/breakables/metal02.md3" );
 	cgs.media.breakable_frag[i][2] = cgs.media.metal03 = trap_R_RegisterModel( "models/breakables/metal03.md3" );

  i++;
 	cgs.media.breakable_frag[i][0] = cgs.media.ceramic01 = trap_R_RegisterModel( "models/breakables/ceramic01.md3" );
 	cgs.media.breakable_frag[i][1] = cgs.media.ceramic02 = trap_R_RegisterModel( "models/breakables/ceramic02.md3" );
 	cgs.media.breakable_frag[i][2] = cgs.media.ceramic03 = trap_R_RegisterModel( "models/breakables/ceramic03.md3" );

  i++;
 	cgs.media.breakable_frag[i][0] = cgs.media.paper01 = trap_R_RegisterModel( "models/breakables/paper01.md3" );
 	cgs.media.breakable_frag[i][1] = cgs.media.paper02 = trap_R_RegisterModel( "models/breakables/paper02.md3" );
 	cgs.media.breakable_frag[i][2] = cgs.media.paper03 = trap_R_RegisterModel( "models/breakables/paper03.md3" );

  i++;
	cgs.media.breakable_frag[i][0] = cgs.media.brick01 = trap_R_RegisterModel( "models/breakables/brick01.md3" );
 	cgs.media.breakable_frag[i][1] = cgs.media.brick02 = trap_R_RegisterModel( "models/breakables/brick02.md3" );
 	cgs.media.breakable_frag[i][2] = cgs.media.brick03 = trap_R_RegisterModel( "models/breakables/brick03.md3" );

  i++;
	cgs.media.breakable_frag[i][0] = cgs.media.concrete01 = trap_R_RegisterModel( "models/breakables/concrete01.md3" );
 	cgs.media.breakable_frag[i][1] = cgs.media.concrete02 = trap_R_RegisterModel( "models/breakables/concrete02.md3" );
 	cgs.media.breakable_frag[i][2] = cgs.media.concrete03 = trap_R_RegisterModel( "models/breakables/concrete03.md3" );
*/
	//Elder: akimbos - some of the stuff isn't in yet :p
	cgs.media.akimboModel = trap_R_RegisterModel("models/weapons2/akimbo/akimbo.md3");
	cgs.media.akimboFlashModel = trap_R_RegisterModel("models/weapons2/akimbo/akimbo_flash.md3");
	cgs.media.akimbo1stModel = trap_R_RegisterModel("models/weapons2/akimbo/akimbo_1st.md3");
	cgs.media.akimboHandModel = trap_R_RegisterModel("models/weapons2/akimbo/akimbo_hand.md3");

	//Elder: item cache
	cgs.media.rq3_bandolierModel = trap_R_RegisterModel("models/items/bandolier.md3");
	cgs.media.rq3_kevlarModel = trap_R_RegisterModel("models/items/kevlar.md3");
	cgs.media.rq3_silencerModel = trap_R_RegisterModel("models/items/silencer.md3");
	cgs.media.rq3_laserModel = trap_R_RegisterModel("models/items/laser.md3");
	cgs.media.rq3_slippersModel = trap_R_RegisterModel("models/items/slippers.md3");

	cgs.media.smoke2 = trap_R_RegisterModel("models/weapons2/shells/s_shell.md3");

	cgs.media.balloonShader = trap_R_RegisterShader("sprites/balloon3");

	cgs.media.bloodExplosionShader = trap_R_RegisterShader("bloodExplosion");

	cgs.media.bulletFlashModel = trap_R_RegisterModel("models/weaphits/bullet.md3");
	cgs.media.ringFlashModel = trap_R_RegisterModel("models/weaphits/ring02.md3");
	cgs.media.dishFlashModel = trap_R_RegisterModel("models/weaphits/boom01.md3");

	// Elder: added
	cgs.media.hitSparkModel = trap_R_RegisterModel("models/weaphits/tracer/tracer.md3");
	cgs.media.hitSparkShader = trap_R_RegisterShader("models/weaphits/tracer/tracer");

	cgs.media.teleportEffectModel = trap_R_RegisterModel("models/misc/telep.md3");
	cgs.media.teleportEffectShader = trap_R_RegisterShader("teleportEffect");

	cgs.media.invulnerabilityPowerupModel = trap_R_RegisterModel("models/powerups/shield/shield.md3");
	cgs.media.medalImpressive = trap_R_RegisterShaderNoMip("medal_impressive");
	cgs.media.medalExcellent = trap_R_RegisterShaderNoMip("medal_excellent");
	cgs.media.medalGauntlet = trap_R_RegisterShaderNoMip("medal_gauntlet");
	cgs.media.medalDefend = trap_R_RegisterShaderNoMip("medal_defend");
	cgs.media.medalAssist = trap_R_RegisterShaderNoMip("medal_assist");
	cgs.media.medalCapture = trap_R_RegisterShaderNoMip("medal_capture");

	//Elder: C3A laser tutorial
	cgs.media.laserShader = trap_R_RegisterShader("sprites/laser");

	//Elder: added for sniper crosshairs
	switch (cg_RQ3_ssgCrosshair.integer) {
	case 0:
		cgs.media.ssgCrosshair[0] = trap_R_RegisterShaderNoMip("gfx/rq3_hud/ssg2x");
		cgs.media.ssgCrosshair[1] = trap_R_RegisterShaderNoMip("gfx/rq3_hud/ssg4x");
		cgs.media.ssgCrosshair[2] = trap_R_RegisterShaderNoMip("gfx/rq3_hud/ssg6x");
		break;
	case 1:
		cgs.media.ssgCrosshair[0] = trap_R_RegisterShaderNoMip("gfx/rq3_hud/ssg2x-1");
		cgs.media.ssgCrosshair[1] = trap_R_RegisterShaderNoMip("gfx/rq3_hud/ssg4x-1");
		cgs.media.ssgCrosshair[2] = trap_R_RegisterShaderNoMip("gfx/rq3_hud/ssg6x-1");
		break;
	case 2:
		cgs.media.ssgCrosshair[0] = trap_R_RegisterShaderNoMip("gfx/rq3_hud/ssg2x-2");
		cgs.media.ssgCrosshair[1] = trap_R_RegisterShaderNoMip("gfx/rq3_hud/ssg4x-2");
		cgs.media.ssgCrosshair[2] = trap_R_RegisterShaderNoMip("gfx/rq3_hud/ssg6x-2");
		break;
	case 3:
		cgs.media.ssgCrosshair[0] = trap_R_RegisterShaderNoMip("gfx/rq3_hud/ssg2x-3");
		cgs.media.ssgCrosshair[1] = trap_R_RegisterShaderNoMip("gfx/rq3_hud/ssg4x-3");
		cgs.media.ssgCrosshair[2] = trap_R_RegisterShaderNoMip("gfx/rq3_hud/ssg6x-3");
		break;
	case 4:
		cgs.media.ssgCrosshair[0] = trap_R_RegisterShaderNoMip("gfx/rq3_hud/ssg2x-4");
		cgs.media.ssgCrosshair[1] = trap_R_RegisterShaderNoMip("gfx/rq3_hud/ssg4x-4");
		cgs.media.ssgCrosshair[2] = trap_R_RegisterShaderNoMip("gfx/rq3_hud/ssg6x-4");
		break;
	case 5:
		cgs.media.ssgCrosshair[0] = trap_R_RegisterShaderNoMip("gfx/rq3_hud/ssg2x-5");
		cgs.media.ssgCrosshair[1] = trap_R_RegisterShaderNoMip("gfx/rq3_hud/ssg4x-5");
		cgs.media.ssgCrosshair[2] = trap_R_RegisterShaderNoMip("gfx/rq3_hud/ssg6x-5");
		break;
	default:
		cgs.media.ssgCrosshair[0] = trap_R_RegisterShaderNoMip("gfx/rq3_hud/ssg2x");
		cgs.media.ssgCrosshair[1] = trap_R_RegisterShaderNoMip("gfx/rq3_hud/ssg4x");
		cgs.media.ssgCrosshair[2] = trap_R_RegisterShaderNoMip("gfx/rq3_hud/ssg6x");
		break;
	}
	//Elder: other hud-related elements
	cgs.media.rq3_healthicon = trap_R_RegisterShaderNoMip("gfx/rq3_hud/hud_health");
	cgs.media.rq3_healthicon2 = trap_R_RegisterShaderNoMip("gfx/rq3_hud/hud_healthwarning");

	cg.loadingMapPercent += 0.05f;

	memset(cg_items, 0, sizeof(cg_items));
	memset(cg_weapons, 0, sizeof(cg_weapons));

	// only register the items that the server says we need
	strcpy(items, CG_ConfigString(CS_ITEMS));

	for (i = 1; i < bg_numItems; i++)
		if (items[i] == '1' || cg_buildScript.integer)
			num++;

	for (i = 1; i < bg_numItems; i++) {
		if (items[i] == '1' || cg_buildScript.integer) {
			CG_LoadingItem(i);
			CG_RegisterItemVisuals(i);
			if (num)
				cg.loadingMapPercent += (0.25f / (float) num);
		}
	}
	if (!num)
		cg.loadingMapPercent += 0.25f;

	// wall marks
	cgs.media.bulletMarkShader = trap_R_RegisterShader("gfx/damage/bullet_mrk");
	cgs.media.burnMarkShader = trap_R_RegisterShader("gfx/damage/burn_med_mrk");
	cgs.media.holeMarkShader = trap_R_RegisterShader("gfx/damage/hole_lg_mrk");
	cgs.media.energyMarkShader = trap_R_RegisterShader("gfx/damage/plasma_mrk");
	cgs.media.shadowMarkShader = trap_R_RegisterShader("markShadow");
	cgs.media.wakeMarkShader = trap_R_RegisterShader("wake");
	cgs.media.bloodMarkShader = trap_R_RegisterShader("bloodMark");
	cgs.media.ctbXMarkSilver = trap_R_RegisterShader("ctbXMarkSilver");
	cgs.media.ctbOMarkBlack = trap_R_RegisterShader("ctbOMarkBlack");
	//Blaze: added for explosive boxes and grenades
	cgs.media.grenadeExplosionShader = trap_R_RegisterShader("grenadeExplosion");
	// Elder: added
	cgs.media.slashMarkShader = trap_R_RegisterShader("gfx/damage/slash_mrk");
	cgs.media.glassMarkShader = trap_R_RegisterShader("gfx/damage/glass_mrk");
	cgs.media.metalMarkShader = trap_R_RegisterShader("gfx/damage/metal_mrk");
	// Makro - added
	//cgs.media.tileMarkShader = trap_R_RegisterShader("gfx/damage/tile_mrk");

	// NiceAss: for foglaser
	cgs.media.railCoreShader = trap_R_RegisterShader("fogLaser");

	// register the inline models
	cgs.numInlineModels = trap_CM_NumInlineModels();
	for (i = 1; i < cgs.numInlineModels; i++) {
		char name[10];
		vec3_t mins, maxs;
		int j;

		Com_sprintf(name, sizeof(name), "*%i", i);
		cgs.inlineDrawModel[i] = trap_R_RegisterModel(name);
		trap_R_ModelBounds(cgs.inlineDrawModel[i], mins, maxs);
		for (j = 0; j < 3; j++) {
			cgs.inlineModelMidpoints[i][j] = mins[j] + 0.5 * (maxs[j] - mins[j]);
		}
	}

	// register all the server specified models
	for (i = 1; i < MAX_MODELS; i++) {
		const char *modelName;

		modelName = CG_ConfigString(CS_MODELS + i);
		if (!modelName[0]) {
			break;
		}
		cgs.gameModels[i] = trap_R_RegisterModel(modelName);
	}

	CG_ClearParticles();

	/*
	   for (i=1; i<MAX_PARTICLES_AREAS; i++)
	   {
	   {
	   int rval;

	   rval = CG_NewParticleArea ( CS_PARTICLES + i);
	   if (!rval)
	   break;
	   }
	   }
	 */
}

/*
=======================
CG_BuildSpectatorString

=======================
*/
void CG_BuildSpectatorString()
{
	int i;

	cg.spectatorList[0] = 0;
	for (i = 0; i < MAX_CLIENTS; i++) {
		if (cgs.clientinfo[i].infoValid && cgs.clientinfo[i].team == TEAM_SPECTATOR) {
			Q_strcat(cg.spectatorList, sizeof(cg.spectatorList), va("%s     ", cgs.clientinfo[i].name));
		}
	}
	i = strlen(cg.spectatorList);
	if (i != cg.spectatorLen) {
		cg.spectatorLen = i;
		cg.spectatorWidth = -1;
	}
}

/*
===================
CG_RegisterClients
===================
*/
static void CG_RegisterClients(void)
{
	int i, num = 0;

	CG_LoadingClient(cg.clientNum);
	CG_NewClientInfo(cg.clientNum);

	for (i = 0; i < MAX_CLIENTS; i++) {
		const char *clientInfo;

		clientInfo = CG_ConfigString(CS_PLAYERS + i);
		if (cg.clientNum != i && clientInfo[0])
			num++;
	}

	for (i = 0; i < MAX_CLIENTS; i++) {
		const char *clientInfo;

		if (cg.clientNum == i) {
			continue;
		}

		clientInfo = CG_ConfigString(CS_PLAYERS + i);
		if (!clientInfo[0]) {
			continue;
		}
		CG_LoadingClient(i);
		CG_NewClientInfo(i);
		if (num)
			cg.loadingMapPercent += (0.2f / (float) num);
	}
	if (!num)
		cg.loadingMapPercent += 0.2f;
	CG_BuildSpectatorString();
}

//===========================================================================

/*
=================
CG_ConfigString
=================
*/
const char *CG_ConfigString(int index)
{
	if (index < 0 || index >= MAX_CONFIGSTRINGS) {
		CG_Error("CG_ConfigString: bad index: %i", index);
	}
	return cgs.gameState.stringData + cgs.gameState.stringOffsets[index];
}

//==================================================================

/*
======================
CG_StartMusic

======================
*/
void CG_StartMusic(void)
{
	char *s;
	char parm1[MAX_QPATH], parm2[MAX_QPATH];

	// start the background music
	s = (char *) CG_ConfigString(CS_MUSIC);
	Q_strncpyz(parm1, COM_Parse(&s), sizeof(parm1));
	Q_strncpyz(parm2, COM_Parse(&s), sizeof(parm2));

	trap_S_StartBackgroundTrack(parm1, parm2);
}

/*
=================
CG_Init

Called after every level change or subsystem restart
Will perform callbacks to make the loading info screen update.
=================
*/
void CG_Init(int serverMessageNum, int serverCommandSequence, int clientNum)
{
	const char *s;

	// clear everything
	memset(&cgs, 0, sizeof(cgs));
	memset(&cg, 0, sizeof(cg));
	memset(cg_entities, 0, sizeof(cg_entities));
	memset(cg_weapons, 0, sizeof(cg_weapons));
	memset(cg_items, 0, sizeof(cg_items));

	cg.clientNum = clientNum;

	cgs.processedSnapshotNum = serverMessageNum;
	cgs.serverCommandSequence = serverCommandSequence;

	// load a few needed things before we do any screen updates
	cgs.media.charsetShader = trap_R_RegisterShader("gfx/2d/bigchars");
	cgs.media.whiteShader = trap_R_RegisterShader("white");
	cgs.media.charsetProp = trap_R_RegisterShaderNoMip("menu/art/font1_prop.tga");
	cgs.media.charsetPropGlow = trap_R_RegisterShaderNoMip("menu/art/font1_prop_glo.tga");
	cgs.media.charsetPropB = trap_R_RegisterShaderNoMip("menu/art/font2_prop.tga");

	CG_RegisterCvars();

	CG_InitConsoleCommands();
	//Blaze: Default weapon = Pistol
	cg.weaponSelect = WP_PISTOL;

	cgs.redflag = cgs.blueflag = -1;	// For compatibily, default to unset for
	cgs.flagStatus = -1;
	// old servers

	// get the rendering configuration from the client system
	trap_GetGlconfig(&cgs.glconfig);
	cgs.screenXScale = cgs.glconfig.vidWidth / 640.0;
	cgs.screenYScale = cgs.glconfig.vidHeight / 480.0;

	// get the gamestate from the client system
	trap_GetGameState(&cgs.gameState);

	// check version
	s = CG_ConfigString(CS_GAME_VERSION);
	if (strcmp(s, GAME_VERSION)) {
		CG_Error("Client/Server game mismatch: %s/%s", GAME_VERSION, s);
	}

	s = CG_ConfigString(CS_LEVEL_START_TIME);
	cgs.levelStartTime = atoi(s);

	CG_ParseServerinfo();

	// load the new map
	CG_LoadingString("collision map");

	trap_CM_LoadMap(cgs.mapname);

	cg.loading = qtrue;	// force players to load instead of defer

	CG_LoadingString("sounds");

	CG_RegisterSounds();
	cg.loadingMapPercent += 0.05f;

	CG_LoadingString("graphics");

	CG_RegisterGraphics();

	//Blaze: Load breakables
	CG_LoadingString("breakables");

	CG_RegisterBreakables();

	CG_LoadingString("clients");

	CG_RegisterClients();	// if low on memory, some clients will be deferred

//Makro - this should be moved out of missionpack eventually
#ifdef MAKROMISSIONPACK
	CG_LoadingString("hud menu");
	CG_AssetCache();
	CG_LoadHudMenu();	// load new hud stuff
#endif

	cg.loading = qfalse;	// future players will be deferred

	CG_InitLocalEntities();

	CG_InitMarkPolys();

	// remove the last loading update
	cg.infoScreenText[0] = 0;

	// Make sure we have update values (scores)
	CG_SetConfigValues();

	CG_StartMusic();

	CG_LoadingString("");

	CG_ShaderStateChanged();

	trap_S_ClearLoopingSounds(qtrue);

	//Slicer: For the anti-cheat system
	//trap_Cvar_Set("cg_RQ3_Auth","0");
	trap_SendClientCommand("SendCheatCvars");
}

/*
=================
CG_Shutdown

Called before every level change or subsystem restart
=================
*/
void CG_Shutdown(void)
{
	// some mods may need to do cleanup work here,
	// like closing files or archiving session data
}

/*
==================
CG_EventHandling
==================
 type 0 - no event handling
      1 - team menu
      2 - hud editor

*/
void CG_EventHandling(int type)
{
}

void CG_KeyEvent(int key, qboolean down)
{
	//Elder: Let's see what we're pressing
	//CG_Printf("Key: %i, isDown: %d\n", key, down);
}

void CG_MouseEvent(int x, int y)
{
}
