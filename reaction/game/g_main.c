//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.73  2002/06/12 03:37:38  blaze
// some fixes for the add bot code
//
// Revision 1.72  2002/06/11 01:43:08  blaze
// g_rq3_cvarfile allows you to change which file holds the restricted cvars
//
// Revision 1.71  2002/06/10 23:53:32  assimon
// Fixed buffer overflow. (commented the printing of the ini file contents)
//
// Revision 1.70  2002/06/10 19:10:59  jbravo
// Voting system fixed for TP
//
// Revision 1.69  2002/06/10 18:38:40  makro
// Changed default value for g_allowvote to 0
//
// Revision 1.68  2002/06/10 03:26:04  jbravo
// Fixed two small errors
//
// Revision 1.67  2002/06/09 23:18:49  assimon
// Add coments to the init parser. Added Message before intermition telling next map. New cvar: g_RQ3_NextMap
//
// Revision 1.66  2002/06/07 19:07:08  slicer
// removed cvars for teamXready, replaced by level.teamXready
//
// Revision 1.65  2002/06/07 13:06:34  jbravo
// Disabled all gametypes except FFA and TP
//
// Revision 1.64  2002/06/07 03:03:02  jbravo
// More colorfixes
//
// Revision 1.63  2002/06/05 23:36:39  niceass
// "ready" command lag fix
//
// Revision 1.62  2002/06/03 00:49:07  niceass
// match scoreboard changes
//
// Revision 1.61  2002/05/31 05:12:50  niceass
// tpcountdown default 0!1@$@#%$
//
// Revision 1.60  2002/05/28 01:17:01  jbravo
// More gib fixes.  g_RQ3_gib added
//
// Revision 1.59  2002/05/23 03:07:10  blaze
// Some changes to autoaction, still need to fix up a little bit more stuff relating to getting sent 2 screenshot requests
//
// Revision 1.58  2002/05/12 12:15:05  slicer
// Added Referee command for captains
//
// Revision 1.57  2002/05/12 00:07:47  slicer
// Added Normal Radio Flood Protection
//
// Revision 1.56  2002/05/11 16:22:38  slicer
// Added a Repeat Flood Protection to Radio
//
// Revision 1.55  2002/05/09 20:58:30  jbravo
// New Obit system and a warning cleanup in zcam
//
// Revision 1.54  2002/05/06 21:41:01  slicer
// Added rq3_cmd
//
// Revision 1.53  2002/05/05 15:51:16  slicer
// Captain and subs get saved on map_restarts ( moved to "sess" )
//
// Revision 1.52  2002/05/05 04:23:00  jbravo
// Some MM fixes and cleanups
//
// Revision 1.51  2002/05/04 23:17:26  jbravo
// Fixed the model checking code a bit. It now works with the .ini file
//
// Revision 1.50  2002/04/30 11:20:12  jbravo
// Redid the teamcount cvars.
//
// Revision 1.49  2002/04/30 01:23:05  jbravo
// Changed the server logging to be more like a normal AQ server.  Cleaned
// all colors from the logs.
//
// Revision 1.48  2002/04/28 23:13:08  jbravo
// Clean up the server logs
//
// Revision 1.47  2002/04/23 00:21:44  jbravo
// Cleanups of the new model code.  Removed the spectator bar for zcam modes.
//
// Revision 1.46  2002/04/22 02:27:57  jbravo
// Dynamic model recognition
//
// Revision 1.45  2002/04/15 00:54:26  assimon
// Simple ini file parser that reads a ini configuration file and suports rotations.
//
// Revision 1.44  2002/04/12 18:34:31  jbravo
// Bye bye lag when somebody joins a team.
//
// Revision 1.43  2002/04/07 12:49:10  slicer
// Added 'teamname' command for MM, and tweaked the cvar system.
//
// Revision 1.42  2002/04/03 09:26:47  jbravo
// New FF system. Warns and then finally kickbans teamwounders and
// teamkillers
//
// Revision 1.41  2002/04/02 04:18:58  jbravo
// Made the TP scoreboard go down at round beginig (not for spectators) and
// pop up at intermission.  Also added special to the use command
//
// Revision 1.40  2002/03/30 21:51:42  jbravo
// Removed all those ifdefs for zcam.
//
// Revision 1.39  2002/03/26 10:32:52  jbravo
// Bye bye LCA lag
//
// Revision 1.38  2002/03/25 14:55:00  jbravo
// teamCount cvars for Makro
//
// Revision 1.37  2002/03/24 06:06:53  jbravo
// Some tweaks and cleanups
//
// Revision 1.36  2002/03/23 05:50:47  jbravo
// Moved enableDust out of the missionpack
//
// Revision 1.35  2002/03/23 05:17:43  jbravo
// Major cleanup of game -> cgame communication with LCA vars.
//
// Revision 1.34  2002/03/21 15:02:05  jbravo
// More teamname cleanups and fix for fraglines.
//
// Revision 1.33  2002/03/17 20:53:44  slicer
// Small fix on CheckExitRules
//
// Revision 1.32  2002/03/17 01:44:39  jbravo
// Fixed the "xxx died" fraglines, did some code cleanups andalmost fixed
// DM.  Only DM problem I can see is that bots are invisible.
//
// Revision 1.31  2002/03/17 00:40:23  jbravo
// Adding variable team names. g_RQ3_team1name and g_RQ3_team2name. Fixed
// Slicers fraglimit check.
//
// Revision 1.30  2002/03/14 23:14:19  slicer
// Added Fraglimit checks on TP ( !!! )
//
// Revision 1.29  2002/03/11 02:21:13  niceass
// client gravity fix
//
// Revision 1.28  2002/03/07 14:29:12  slicer
// Intermission ala aq2, when timelimit/roundlimit hits.
//
// Revision 1.27  2002/03/07 01:38:36  assimon
// Changed Ref System. New cvar added - g_RQ3_RefID. Now referee is peserved even on map changes or map_restarts.
//
// Revision 1.26  2002/03/07 00:00:54  assimon
// Added a skeleton referee suport, with some functional commands (map_restart and kick)
//
// Revision 1.25  2002/03/01 18:50:26  makro
// Added CVAR_ARCHIVE flag to some g_RQ3 cvars
//
// Revision 1.24  2002/02/24 18:12:19  jbravo
// Added a cvar to control sniper behavior g_RQ3_sniperup. Def 0. if set yo 1
// it makes players spawn with the sniper up.
//
// Revision 1.23  2002/02/10 04:55:28  jbravo
// Fix #1 to zcam jitter.   More is probably needed.
//
// Revision 1.22  2002/02/07 23:47:06  niceass
// Score sorting for >= GT_TEAM fixed
//
// Revision 1.21  2002/02/05 23:41:27  slicer
// More on matchmode..
//
// Revision 1.20  2002/02/04 00:10:49  slicer
// Matchmode: Teams Ready/Not Ready goes by cvar MM_team1/2
//
// Revision 1.19  2002/01/31 23:51:18  slicer
// Adding Matchmode: just a few basics and files...
//
// Revision 1.18  2002/01/31 02:25:31  jbravo
// Adding limchasecam.
//
// Revision 1.17  2002/01/14 01:20:45  niceass
// No more default 800 gravity on items
// Thrown knife+Glass fix - NiceAss
//
// Revision 1.16  2002/01/11 20:20:58  jbravo
// Adding TP to main branch
//
// Revision 1.15  2002/01/11 19:48:30  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.14  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//

#include "g_local.h"
#include "zcam.h"

level_locals_t	level;

typedef struct {
	vmCvar_t	*vmCvar;
	char		*cvarName;
	char		*defaultString;
	int			cvarFlags;
	int			modificationCount;  // for tracking changes
	qboolean	trackChange;	// track this variable, and announce if changed
  qboolean teamShader;        // track and if changed, update shader state
} cvarTable_t;

gentity_t		g_entities[MAX_GENTITIES];
gclient_t		g_clients[MAX_CLIENTS];

vmCvar_t	g_gametype;
vmCvar_t	g_dmflags;
vmCvar_t	g_fraglimit;
vmCvar_t	g_timelimit;
vmCvar_t	g_capturelimit;
vmCvar_t	g_friendlyFire;
vmCvar_t	g_password;
vmCvar_t	g_needpass;
vmCvar_t	g_maxclients;
vmCvar_t	g_maxGameClients;
vmCvar_t	g_dedicated;
vmCvar_t	g_speed;
vmCvar_t	g_gravity;
vmCvar_t	g_cheats;
vmCvar_t	g_knockback;
vmCvar_t	g_quadfactor;
vmCvar_t	g_forcerespawn;
vmCvar_t	g_inactivity;
vmCvar_t	g_debugMove;
vmCvar_t	g_debugDamage;
vmCvar_t	g_debugAlloc;
vmCvar_t	g_weaponRespawn;
vmCvar_t	g_weaponTeamRespawn;
vmCvar_t	g_motd;
vmCvar_t	g_synchronousClients;
vmCvar_t	g_warmup;
vmCvar_t	g_doWarmup;
vmCvar_t	g_restarted;
vmCvar_t	g_log;
vmCvar_t	g_logSync;
vmCvar_t	g_blood;
vmCvar_t	g_podiumDist;
vmCvar_t	g_podiumDrop;
vmCvar_t	g_allowVote;
vmCvar_t	g_teamAutoJoin;
vmCvar_t	g_teamForceBalance;
vmCvar_t	g_banIPs;
vmCvar_t	g_filterBan;
vmCvar_t	g_smoothClients;
vmCvar_t	pmove_fixed;
vmCvar_t	pmove_msec;
vmCvar_t	g_rankings;
vmCvar_t	g_listEntity;
//Slicer: Matchmode
vmCvar_t	g_RQ3_matchmode;
//Blaze: Reaction cvars
vmCvar_t	g_rxn_knifelimit;
vmCvar_t	g_RQ3_maxWeapons;
vmCvar_t	g_RQ3_statLog;
vmCvar_t	g_RQ3_ejectBlood;
vmCvar_t	g_RQ3_respawnProtectTime;
//Elder: spam protection cvars
vmCvar_t	g_RQ3_messageMaxCount;
vmCvar_t	g_RQ3_messageInterval;
vmCvar_t	g_RQ3_messageMaxWarnings;
vmCvar_t	g_RQ3_messageWarnTime;
vmCvar_t	g_RQ3_messageBanTime;
vmCvar_t	g_RQ3_messageProtect;
// JBravo: adding TP cvars
vmCvar_t	g_RQ3_roundlimit;
vmCvar_t	g_RQ3_roundtimelimit;
vmCvar_t	g_RQ3_tgren;
vmCvar_t	g_RQ3_limchasecam;
vmCvar_t	g_RQ3_sniperup;
vmCvar_t	g_RQ3_lca;
vmCvar_t	g_RQ3_team1name;
vmCvar_t	g_RQ3_team2name;
vmCvar_t	g_RQ3_team1model;
vmCvar_t	g_RQ3_team2model;
vmCvar_t	g_RQ3_tpcountdown;
vmCvar_t	g_RQ3_printOwnObits;
vmCvar_t	g_RQ3_gib;
vmCvar_t	g_RQ3_maxteamkills;
vmCvar_t	g_RQ3_twbanrounds;
vmCvar_t	g_RQ3_tkbanrounds;
//Slicer: Team Status Cvars for MM
//vmCvar_t	g_RQ3_team1ready;
//vmCvar_t	g_RQ3_team2ready;
// aasimon: Ref System for MM
vmCvar_t	g_RQ3_AllowRef;
vmCvar_t	g_RQ3_RefPass;
vmCvar_t	g_RQ3_RefID;
// aasimon: ini stuff
vmCvar_t	g_RQ3_IniFile;
vmCvar_t	g_RQ3_ValidIniFile;
vmCvar_t	g_RQ3_NextMapID;
vmCvar_t	g_RQ3_NextMap;

//Slicer Radio radio flood protect
vmCvar_t		g_RQ3_radioRepeat;
vmCvar_t		g_RQ3_radioRepeatTime;
vmCvar_t		g_RQ3_radioBan;
vmCvar_t		g_RQ3_radioFlood;
vmCvar_t		g_RQ3_radioFloodTime;

 
#ifdef MISSIONPACK
vmCvar_t	g_obeliskHealth;
vmCvar_t	g_obeliskRegenPeriod;
vmCvar_t	g_obeliskRegenAmount;
vmCvar_t	g_obeliskRespawnDelay;
vmCvar_t	g_cubeTimeout;
vmCvar_t	g_redteam;
vmCvar_t	g_blueteam;
vmCvar_t	g_singlePlayer;
vmCvar_t	g_proxMineTimeout;
#endif
// NiceAss: Taken out of the missionpack
vmCvar_t	g_enableBreath;
// JBravo: ditto
vmCvar_t	g_enableDust;
//Blaze let cvar.cfg be set by server admins
vmCvar_t  g_RQ3_cvarfile;

// bk001129 - made static to avoid aliasing
static cvarTable_t		gameCvarTable[] = {
	// don't override the cheat state set by the system
	{ &g_cheats, "sv_cheats", "", 0, 0, qfalse },

	// noset vars
	{ NULL, "gamename", GAMEVERSION , CVAR_SERVERINFO | CVAR_ROM, 0, qfalse  },
	{ NULL, "gamedate", __DATE__ , CVAR_ROM, 0, qfalse  },
	{ &g_restarted, "g_restarted", "0", CVAR_ROM, 0, qfalse  },
	{ NULL, "sv_mapname", "", CVAR_SERVERINFO | CVAR_ROM, 0, qfalse  },

	// latched vars
	{ &g_gametype, "g_gametype", "0", CVAR_SERVERINFO | CVAR_USERINFO | CVAR_LATCH, 0, qfalse  },

	{ &g_maxclients, "sv_maxclients", "8", CVAR_SERVERINFO | CVAR_LATCH | CVAR_ARCHIVE, 0, qfalse  },
	{ &g_maxGameClients, "g_maxGameClients", "0", CVAR_SERVERINFO | CVAR_LATCH | CVAR_ARCHIVE, 0, qfalse  },

	// change anytime vars
	{ &g_dmflags, "dmflags", "0", CVAR_SERVERINFO | CVAR_ARCHIVE, 0, qtrue  },
	{ &g_fraglimit, "fraglimit", "20", CVAR_SERVERINFO | CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue },
	{ &g_timelimit, "timelimit", "0", CVAR_SERVERINFO | CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue },
	{ &g_capturelimit, "capturelimit", "8", CVAR_SERVERINFO | CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue },

	{ &g_synchronousClients, "g_synchronousClients", "0", CVAR_SYSTEMINFO, 0, qfalse  },

	{ &g_friendlyFire, "g_friendlyFire", "0", CVAR_ARCHIVE, 0, qtrue  },

	{ &g_teamAutoJoin, "g_teamAutoJoin", "0", CVAR_ARCHIVE  },
	{ &g_teamForceBalance, "g_teamForceBalance", "0", CVAR_ARCHIVE  },

	{ &g_warmup, "g_warmup", "20", CVAR_ARCHIVE, 0, qtrue  },
	{ &g_doWarmup, "g_doWarmup", "0", 0, 0, qtrue  },
	{ &g_log, "g_log", "reaction.log", CVAR_ARCHIVE, 0, qfalse  },
	{ &g_logSync, "g_logSync", "0", CVAR_ARCHIVE, 0, qfalse  },

	{ &g_password, "g_password", "", CVAR_USERINFO, 0, qfalse  },

	{ &g_banIPs, "g_banIPs", "", CVAR_ARCHIVE, 0, qfalse  },
	{ &g_filterBan, "g_filterBan", "1", CVAR_ARCHIVE, 0, qfalse  },

	{ &g_needpass, "g_needpass", "0", CVAR_SERVERINFO | CVAR_ROM, 0, qfalse },

	{ &g_dedicated, "dedicated", "0", 0, 0, qfalse  },

	// Elder: slow down to 300?
	{ &g_speed, "g_speed", "300", 0, 0, qtrue  },	// was 320
	{ &g_gravity, "g_gravity", "800", CVAR_SYSTEMINFO, 0, qtrue  },		// shared with client (cg_gravity)
	{ &g_knockback, "g_knockback", "1000", 0, 0, qtrue  },
	{ &g_quadfactor, "g_quadfactor", "3", 0, 0, qtrue  },
	{ &g_weaponRespawn, "g_weaponrespawn", "5", 0, 0, qtrue  },
	{ &g_weaponTeamRespawn, "g_weaponTeamRespawn", "30", 0, 0, qtrue },
	{ &g_forcerespawn, "g_forcerespawn", "20", 0, 0, qtrue },
	{ &g_inactivity, "g_inactivity", "0", 0, 0, qtrue },
	{ &g_debugMove, "g_debugMove", "0", 0, 0, qfalse },
	{ &g_debugDamage, "g_debugDamage", "0", 0, 0, qfalse },
	{ &g_debugAlloc, "g_debugAlloc", "0", 0, 0, qfalse },
	{ &g_motd, "g_motd", "", 0, 0, qfalse },
	{ &g_blood, "com_blood", "1", 0, 0, qfalse },

	{ &g_podiumDist, "g_podiumDist", "80", 0, 0, qfalse },
	{ &g_podiumDrop, "g_podiumDrop", "70", 0, 0, qfalse },

	//Makro - changed default to 0
	{ &g_allowVote, "g_allowVote", "0", CVAR_ARCHIVE, 0, qfalse },
	{ &g_listEntity, "g_listEntity", "0", 0, 0, qfalse },

#ifdef MISSIONPACK
	{ &g_obeliskHealth, "g_obeliskHealth", "2500", 0, 0, qfalse },
	{ &g_obeliskRegenPeriod, "g_obeliskRegenPeriod", "1", 0, 0, qfalse },
	{ &g_obeliskRegenAmount, "g_obeliskRegenAmount", "15", 0, 0, qfalse },
	{ &g_obeliskRespawnDelay, "g_obeliskRespawnDelay", "10", CVAR_SERVERINFO, 0, qfalse },

	{ &g_cubeTimeout, "g_cubeTimeout", "30", 0, 0, qfalse },
	{ &g_redteam, "g_redteam", "Stroggs", CVAR_ARCHIVE | CVAR_SERVERINFO | CVAR_USERINFO , 0, qtrue, qtrue },
	{ &g_blueteam, "g_blueteam", "Pagans", CVAR_ARCHIVE | CVAR_SERVERINFO | CVAR_USERINFO , 0, qtrue, qtrue  },
	{ &g_singlePlayer, "ui_singlePlayerActive", "", 0, 0, qfalse, qfalse  },

	{ &g_proxMineTimeout, "g_proxMineTimeout", "20000", 0, 0, qfalse },
#endif
	// NiceAss: Taken out of the missionpack
	{ &g_enableBreath, "g_enableBreath", "0", CVAR_SERVERINFO, 0, qfalse },
	// JBravo: ditto
	{ &g_enableDust, "g_enableDust", "0", CVAR_SERVERINFO, 0, qfalse },
	{ &g_smoothClients, "g_smoothClients", "1", 0, 0, qfalse},
	{ &pmove_fixed, "pmove_fixed", "0", CVAR_SYSTEMINFO, 0, qfalse},
	{ &pmove_msec, "pmove_msec", "8", CVAR_SYSTEMINFO, 0, qfalse},

	{ &g_rankings, "g_rankings", "0", 0, 0, qfalse},
	//Slicer: Matchmode
	{ &g_RQ3_matchmode, "g_RQ3_matchmode", "0", CVAR_SERVERINFO | CVAR_USERINFO | CVAR_LATCH | CVAR_SYSTEMINFO, 0, qfalse  },
	//Slicer: radio protect
	{ &g_RQ3_radioFlood, "g_RQ3_radioFlood", "3", 0 , 0, qfalse  },
	{ &g_RQ3_radioFloodTime, "g_RQ3_radioFloodTime", "2", 0 , 0, qfalse  },
	{ &g_RQ3_radioRepeat, "g_RQ3_radioRepeat", "2", 0 , 0, qfalse  },
	{ &g_RQ3_radioRepeatTime, "g_RQ3_radioRepeat", "1", 0 , 0, qfalse  },
	{ &g_RQ3_radioBan, "g_RQ3_radioBan", "10", 0 , 0, qfalse  },
	//Blaze: Reaction stuff
	// Elder: these are explicit values set every time the game initializes
	{ &g_RQ3_ejectBlood, "g_RQ3_ejectBlood", "0", CVAR_ARCHIVE | CVAR_NORESTART,0, qfalse},
	{ &g_RQ3_maxWeapons, "g_RQ3_maxWeapons", "1",0,0, qtrue},
	{ &g_RQ3_respawnProtectTime, "g_RQ3_respawnProtectTime", "2", CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue},
	{ &g_RQ3_statLog, "sv_RQ3_statLog", "1", CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse},
	{ &g_RQ3_messageMaxCount, "sv_RQ3_messageMaxCount", SAY_MAX_NUMBER, 0, 0, qfalse },
	{ &g_RQ3_messageInterval, "sv_RQ3_messageInterval", SAY_PERIOD_TIME, 0, 0, qfalse },
	{ &g_RQ3_messageMaxWarnings, "sv_RQ3_messageMaxWarnings", SAY_MAX_WARNINGS, 0, 0, qfalse },
	{ &g_RQ3_messageWarnTime, "sv_RQ3_messageWarnTime", SAY_WARNING_TIME, 0, 0, qfalse },
	{ &g_RQ3_messageBanTime, "sv_RQ3_messageBanTime", SAY_BAN_TIME, 0, 0, qfalse },
	{ &g_RQ3_messageProtect, "sv_RQ3_messageProtect", "1", CVAR_SERVERINFO, 0, qtrue},
// JBravo: still with the TP cvars
// Makro - adding CVAR_ARCHIVE so these settings work when starting up the UI
	{ &g_RQ3_roundlimit, "g_RQ3_roundlimit", "0", CVAR_ARCHIVE, 0, qtrue},
	{ &g_RQ3_roundtimelimit, "g_RQ3_roundtimelimit", "2", CVAR_ARCHIVE, 0, qtrue},
	{ &g_RQ3_tgren, "g_RQ3_tgren", "0", CVAR_ARCHIVE, 0, qtrue},
	{ &g_RQ3_limchasecam, "g_RQ3_limchasecam", "0", CVAR_ARCHIVE, 0, qtrue},
	{ &g_RQ3_sniperup, "g_RQ3_sniperup", "0", CVAR_ARCHIVE, 0, qtrue},
	{ &g_RQ3_team1name, "g_RQ3_team1name", "Robbers", CVAR_SYSTEMINFO | CVAR_SERVERINFO , 0, qfalse },
	{ &g_RQ3_team2name, "g_RQ3_team2name", "Swat", CVAR_SYSTEMINFO | CVAR_SERVERINFO , 0, qfalse },
	{ &g_RQ3_team1model, "g_RQ3_team1model", "grunt/robber", CVAR_SERVERINFO, 0, qfalse },
	{ &g_RQ3_team2model, "g_RQ3_team2model", "grunt/police", CVAR_SERVERINFO, 0, qfalse },
	{ &g_RQ3_tpcountdown, "g_RQ3_tpcountdown", "0", CVAR_ARCHIVE, 0, qfalse },
	{ &g_RQ3_printOwnObits, "g_RQ3_printOwnObits", "0", CVAR_ARCHIVE, 0, qfalse },
	{ &g_RQ3_gib, "g_RQ3_gib", "1", CVAR_ARCHIVE, 0, qtrue },
	{ &g_RQ3_lca, "g_RQ3_lca", "0", CVAR_ROM, 0, qfalse},
	{ &g_RQ3_maxteamkills, "g_RQ3_maxteamkills", "0", CVAR_ARCHIVE, 0, qtrue},
	{ &g_RQ3_twbanrounds, "g_RQ3_twbanrounds", "2", CVAR_ARCHIVE, 0, qtrue},
	{ &g_RQ3_tkbanrounds, "g_RQ3_tkbanrounds", "2", CVAR_ARCHIVE, 0, qtrue},
  //Blaze: let cvar.cfg be set by the server admins
  { &g_RQ3_cvarfile, "g_RQ3_cvarfile", "cvar.cfg", CVAR_ARCHIVE, 0, qtrue},
	//Slicer: Team Status Cvars for MM
	//{ &g_RQ3_team1ready, "g_RQ3_team1ready", "0", 0, 0, qfalse},
	//{ &g_RQ3_team2ready, "g_RQ3_team2ready", "0", 0, 0, qfalse},
	// aasimon: Ref system for MM,added infor for referee id (clientnumber)
	{ &g_RQ3_AllowRef, "g_RQ3_AllowRef", "0", CVAR_SERVERINFO, 0, qtrue},
	{ &g_RQ3_RefPass, "g_RQ3_RefPassword", "", CVAR_USERINFO, 0, qfalse},
	{ &g_RQ3_RefID, "g_RQ3_RefID", "-1", CVAR_SYSTEMINFO | CVAR_ROM, 0, qfalse},
	// aasimon: stuff for da ini file
	{ &g_RQ3_IniFile, "g_RQ3_IniFile", "rq3.ini", CVAR_SERVERINFO, 0, qtrue},
	{ &g_RQ3_ValidIniFile, "g_RQ3_ValidIniFile", "1", CVAR_SYSTEMINFO | CVAR_ROM, 0, qfalse},
	{ &g_RQ3_NextMapID, "g_RQ3_NextMapID", "-1", CVAR_SYSTEMINFO, 0, qfalse}, 
	{ &g_RQ3_NextMap, "g_RQ3_NextMap", "", CVAR_SYSTEMINFO, 0, qfalse}
};

// bk001129 - made static to avoid aliasing
static int gameCvarTableSize = sizeof( gameCvarTable ) / sizeof( gameCvarTable[0] );


void G_InitGame( int levelTime, int randomSeed, int restart );
void G_RunFrame( int levelTime );
void G_ShutdownGame( int restart );
void CheckExitRules( void );


/*
================
vmMain

This is the only way control passes into the module.
This must be the very first function compiled into the .q3vm file
================
*/
int vmMain( int command, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11  ) {
	switch ( command ) {
	case GAME_INIT:
		G_InitGame( arg0, arg1, arg2 );
		return 0;
	case GAME_SHUTDOWN:
		G_ShutdownGame( arg0 );
		return 0;
	case GAME_CLIENT_CONNECT:
		return (int)ClientConnect( arg0, arg1, arg2 );
	case GAME_CLIENT_THINK:
		ClientThink( arg0 );
		return 0;
	case GAME_CLIENT_USERINFO_CHANGED:
		ClientUserinfoChanged( arg0 );
		return 0;
	case GAME_CLIENT_DISCONNECT:
		ClientDisconnect( arg0 );
		return 0;
	case GAME_CLIENT_BEGIN:
		ClientBegin( arg0 );
		return 0;
	case GAME_CLIENT_COMMAND:
		ClientCommand( arg0 );
		return 0;
	case GAME_RUN_FRAME:
		G_RunFrame( arg0 );
		return 0;
	case GAME_CONSOLE_COMMAND:
		return ConsoleCommand();
	case BOTAI_START_FRAME:
		return BotAIStartFrame( arg0 );
	}

	return -1;
}


void QDECL G_Printf( const char *fmt, ... ) {
	va_list		argptr;
	char		text[1024];

	va_start (argptr, fmt);
	vsprintf (text, fmt, argptr);
	va_end (argptr);

	trap_Printf( text );
}

void QDECL G_Error( const char *fmt, ... ) {
	va_list		argptr;
	char		text[1024];

	va_start (argptr, fmt);
	vsprintf (text, fmt, argptr);
	va_end (argptr);

	trap_Error( text );
}

/*
================
G_FindTeams

Chain together all entities with a matching team field.
Entity teams are used for item groups and multi-entity mover groups.

All but the first will have the FL_TEAMSLAVE flag set and teammaster field set
All but the last will have the teamchain field set to the next one
================
*/
void G_FindTeams( void ) {
	gentity_t	*e, *e2;
	int		i, j;
	int		c, c2;

	c = 0;
	c2 = 0;
	for ( i=1, e=g_entities+i ; i < level.num_entities ; i++,e++ ){
		if (!e->inuse)
			continue;
		if (!e->team)
			continue;
		if (e->flags & FL_TEAMSLAVE)
			continue;
		e->teammaster = e;
		c++;
		c2++;
		for (j=i+1, e2=e+1 ; j < level.num_entities ; j++,e2++)
		{
			if (!e2->inuse)
				continue;
			if (!e2->team)
				continue;
			if (e2->flags & FL_TEAMSLAVE)
				continue;
			if (!strcmp(e->team, e2->team))
			{
				c2++;
				e2->teamchain = e->teamchain;
				e->teamchain = e2;
				e2->teammaster = e;
				e2->flags |= FL_TEAMSLAVE;

				// make sure that targets only point at the master
				if ( e2->targetname ) {
					e->targetname = e2->targetname;
					e2->targetname = NULL;
				}
			}
		}
	}

	G_Printf ("%i teams with %i entities\n", c, c2);
}

void G_RemapTeamShaders() {
#ifdef MISSIONPACK
	char string[1024];
	float f = level.time * 0.001;
	Com_sprintf( string, sizeof(string), "team_icon/%s_red", g_redteam.string );
	AddRemap("textures/ctf2/redteam01", string, f);
	AddRemap("textures/ctf2/redteam02", string, f);
	Com_sprintf( string, sizeof(string), "team_icon/%s_blue", g_blueteam.string );
	AddRemap("textures/ctf2/blueteam01", string, f);
	AddRemap("textures/ctf2/blueteam02", string, f);
	trap_SetConfigstring(CS_SHADERSTATE, BuildShaderStateConfig());
#endif
}


/*
=================
G_RegisterCvars
=================
*/
void G_RegisterCvars( void ) {
	int			i;
	cvarTable_t	*cv;
	qboolean remapped = qfalse;

	for ( i = 0, cv = gameCvarTable ; i < gameCvarTableSize ; i++, cv++ ) {
		trap_Cvar_Register( cv->vmCvar, cv->cvarName,
			cv->defaultString, cv->cvarFlags );
		if ( cv->vmCvar )
			cv->modificationCount = cv->vmCvar->modificationCount;

		if (cv->teamShader) {
			remapped = qtrue;
		}
	}

	if (remapped) {
		G_RemapTeamShaders();
	}
	// check some things
	if ( g_gametype.integer < 0 || g_gametype.integer >= GT_MAX_GAME_TYPE ) {
		G_Printf( "g_gametype %i is out of range, defaulting to 0\n", g_gametype.integer );
		trap_Cvar_Set( "g_gametype", "0" );
	}
// JBravo: lets disable the untested modes.
	if (g_gametype.integer != GT_FFA && g_gametype.integer != GT_TEAMPLAY) {
		G_Printf ("g_gametype %i is currently not supported by ReactionQuake3. Defaulting to 0\n", g_gametype.integer);
		trap_Cvar_Set ("g_gametype", "0");
	}

	level.warmupModificationCount = g_warmup.modificationCount;
}

/*
=================
G_UpdateCvars
=================
*/
void G_UpdateCvars( void ) {
	int			i;
	cvarTable_t	*cv;
	qboolean remapped = qfalse;

	for ( i = 0, cv = gameCvarTable ; i < gameCvarTableSize ; i++, cv++ ) {
		if ( cv->vmCvar ) {
			trap_Cvar_Update( cv->vmCvar );

			if ( cv->modificationCount != cv->vmCvar->modificationCount ) {
				cv->modificationCount = cv->vmCvar->modificationCount;
				if (Q_stricmp (cv->cvarName, "g_gravity") == 0) G_GravityChange();
				if ( cv->trackChange ) {
					trap_SendServerCommand( -1, va("print \"Server: %s changed to %s\n\"",
						cv->cvarName, cv->vmCvar->string ) );
				}

				if (cv->teamShader) {
					remapped = qtrue;
			}
		}
	}
}

	if (remapped) {
		G_RemapTeamShaders();
	}
}

/*
============
RQ3_Validatemodel
JBravo: Makes sure we have a legit RQ3 model
============
*/

legitmodel_t	legitmodels[MAXMODELS];

qboolean RQ3_Validatemodel (char *model) {
	qboolean	valid;
	int		i;

	valid = qfalse;

	for (i=0; i <MAXMODELS; i++) {
		if (*legitmodels[i].name == 0)
			break;
		if (!Q_stricmp (legitmodels[i].name, model)) {
			valid = qtrue;
			break;
		}
	}
	return valid;
}

/*
============
RQ3_loadmodels
JBravo: load modelinfo from all RQ3 models
============
*/
void RQ3_loadmodels (void)
{
	int		i, j, len, numdirs, modelcount, dirlen;
	char		*dirptr, *text_p, *token, dirlist[2048], buf[2048];
	fileHandle_t	file;

	for (i=0; i < MAXMODELS; i++) {
		memset (&legitmodels[i], 0, sizeof (legitmodels[i]));
	}
	numdirs = trap_FS_GetFileList("models/players", "/", dirlist, sizeof(dirlist));
	dirptr  = dirlist;
	modelcount = 0;
  
	for (i=0; i < numdirs; i++, dirptr += dirlen+1) {
		dirlen = strlen(dirptr);
		if (dirlen && dirptr[dirlen-1]=='/') dirptr[dirlen-1]='\0';
		if (!strcmp(dirptr, ".") || !strcmp(dirptr, ".."))
			continue;
    Com_Printf("models (%s)\n",dirptr);
		len = trap_FS_FOpenFile(va("models/players/%s/rq3model.cfg", dirptr), &file, FS_READ);
		if (file) {
			trap_FS_Read(buf, len, file);
			buf[len] = 0;
			text_p = buf;
			trap_FS_FCloseFile (file);
      Com_Printf("Adding %s as a legit model\n",dirptr);
			Com_sprintf(legitmodels[modelcount].name, sizeof(legitmodels[modelcount].name), "%s", dirptr);
			for (j=0; j < 3; j++) {
				token = COM_Parse(&text_p);
				if (!token) break;
				if (Q_stricmp (token, "team1color") == 0) {
					token = COM_Parse(&text_p);
					if (token)
						legitmodels[modelcount].team1color[0] = atof (token);
					else
						break;
					token = COM_Parse(&text_p);
					if (token)
						legitmodels[modelcount].team1color[1] = atof (token);
					else
						break;
					token = COM_Parse(&text_p);
					if (token)
						legitmodels[modelcount].team1color[2] = atof (token);
					else
						break;
				} else if (Q_stricmp (token, "team2color") == 0) {
					token = COM_Parse(&text_p);
					if (token)
						legitmodels[modelcount].team2color[0] = atof (token);
					else
						break;
					token = COM_Parse(&text_p);
					if (token)
						legitmodels[modelcount].team2color[1] = atof (token);
					else
						break;
					token = COM_Parse(&text_p);
					if (token)
						legitmodels[modelcount].team2color[2] = atof (token);
					else
						break;
				} else if (Q_stricmp (token, "gender") == 0) {
					token = COM_Parse(&text_p);
					if (token)
						if (!Q_stricmp(token, "male"))
							legitmodels[modelcount].gender = GENDER_MALE;
						else if (!Q_stricmp(token, "female"))
							legitmodels[modelcount].gender = GENDER_FEMALE;
						else if (!Q_stricmp(token, "neuter"))
							legitmodels[modelcount].gender = GENDER_NEUTER;
						else
							break;
					else
						break;
				}
			}
			modelcount++;
		}
	}
}

/*
============
G_InitGame

============
*/

void G_InitGame( int levelTime, int randomSeed, int restart ) {
	int		i;

	G_Printf ("------- Game Initialization -------\n");
	G_Printf ("gamename: %s\n", GAMEVERSION);
	G_Printf ("gamedate: %s\n", __DATE__);

	srand( randomSeed );

	G_RegisterCvars();

	G_ProcessIPBans();

	G_InitMemory();

	// JBravo: Load RQ3 models
	RQ3_loadmodels();

	// Runs the config if the file is valid. First run will allways be valid
	if( g_RQ3_ValidIniFile.integer && (g_RQ3_NextMapID.integer == -1) ){  
		g_RQ3_NextMapID.integer = 0;
		RQ3_ReadInitFile();
	}

	// set some level globals
	memset( &level, 0, sizeof( level ) );
	level.time = levelTime;
	level.startTime = levelTime;

	level.snd_fry = G_SoundIndex("sound/player/fry.wav");	// FIXME standing in lava / slime

	if ( g_gametype.integer != GT_SINGLE_PLAYER && g_log.string[0] ) {
		if ( g_logSync.integer ) {
			trap_FS_FOpenFile( g_log.string, &level.logFile, FS_APPEND_SYNC );
		} else {
			trap_FS_FOpenFile( g_log.string, &level.logFile, FS_APPEND );
		}
		if ( !level.logFile ) {
			G_Printf( "WARNING: Couldn't open logfile: %s\n", g_log.string );
		} else {
			char	serverinfo[MAX_INFO_STRING];

			trap_GetServerinfo( serverinfo, sizeof( serverinfo ) );

			G_LogPrintf("------------------------------------------------------------\n" );
			G_LogPrintf("InitGame: %s\n", serverinfo );
		}
	} else {
		G_Printf( "Not logging to disk.\n" );
	}

	G_InitWorldSession();

	// initialize all entities for this game
	memset( g_entities, 0, MAX_GENTITIES * sizeof(g_entities[0]) );
	level.gentities = g_entities;

	// initialize all clients for this game
	level.maxclients = g_maxclients.integer;
	memset( g_clients, 0, MAX_CLIENTS * sizeof(g_clients[0]) );
	level.clients = g_clients;

	// set client fields on player ents
	for ( i=0 ; i<level.maxclients ; i++ ) {
		g_entities[i].client = level.clients + i;
	}

	camera_init ();

	// always leave room for the max number of clients,
	// even if they aren't all used, so numbers inside that
	// range are NEVER anything but clients
	level.num_entities = MAX_CLIENTS;

	// let the server system know where the entites are
	trap_LocateGameData( level.gentities, level.num_entities, sizeof( gentity_t ),
		&level.clients[0].ps, sizeof( level.clients[0] ) );

	// reserve some spots for dead player bodies
	InitBodyQue();

	ClearRegisteredItems();

	// parse the key/value pairs and spawn gentities
	G_SpawnEntitiesFromString();

	// general initialization
	G_FindTeams();

	// make sure we have flags for CTF, etc
	if( g_gametype.integer >= GT_TEAM ) {
		G_CheckTeamItems();
	}

	//Elder: spawn unique items.
	// JBravo: unless we are in Teamplay
	if ( g_gametype.integer != GT_TEAMPLAY ) {
		RQ3_StartUniqueItems();
	}

	// Elder: force sv_floodprotect to 0 -- remove when we finish
	// recoding the weapon command and any other commands that may
	// need smashing :)
	if ( trap_Cvar_VariableIntegerValue( "sv_floodprotect" ) != 0 )
	{
		trap_Cvar_Set( "sv_floodprotect", "0" );
		G_Printf("sv_floodprotect shut off for RQ3 Release 1.\n");
	}

	SaveRegisteredItems();

	G_Printf ("-----------------------------------\n");

	if( g_gametype.integer == GT_SINGLE_PLAYER || trap_Cvar_VariableIntegerValue( "com_buildScript" ) ) {
		G_ModelIndex( SP_PODIUM_MODEL );
		G_SoundIndex( "sound/player/gurp1.wav" );
		G_SoundIndex( "sound/player/gurp2.wav" );
	}

// JBravo: reset teamplay stuff.
	if( g_gametype.integer == GT_TEAMPLAY ) {
		level.team_round_countdown = 0;
		level.rulecheckfrequency = 0;
		level.lights_camera_action = 0;
		level.holding_on_tie_check = 0;
		level.current_round_length = 0;
		level.team_game_going = 0;
		level.team_round_going = 0;
		level.fps = trap_Cvar_VariableIntegerValue( "sv_fps" );
	}
// Slicer: reset matchmode vars
	if(g_RQ3_matchmode.integer && g_gametype.integer == GT_TEAMPLAY) {
		level.matchTime = 0;
		level.inGame = qfalse;
		level.team1ready = qfalse;
		level.team2ready = qfalse;
		refVotes[0] = refVotes[1] = -1;
	}

	if ( trap_Cvar_VariableIntegerValue( "bot_enable" ) ) {
		BotAISetup( restart );
		BotAILoadMap( restart );
		G_InitBots( restart );
	}

	G_RemapTeamShaders();

}



/*
=================
G_ShutdownGame
=================
*/
void G_ShutdownGame( int restart ) {
	G_Printf ("==== ShutdownGame ====\n");

	if ( level.logFile ) {
		G_LogPrintf("ShutdownGame:\n" );
		G_LogPrintf("------------------------------------------------------------\n" );
		trap_FS_FCloseFile( level.logFile );
	}

	camera_shutdown ();

	// write all the client session data so we can get it back
	G_WriteSessionData();

	if ( trap_Cvar_VariableIntegerValue( "bot_enable" ) ) {
		BotAIShutdown( restart );
	}
}



//===================================================================

#ifndef GAME_HARD_LINKED
// this is only here so the functions in q_shared.c and bg_*.c can link

void QDECL Com_Error ( int level, const char *error, ... ) {
	va_list		argptr;
	char		text[1024];

	va_start (argptr, error);
	vsprintf (text, error, argptr);
	va_end (argptr);

	G_Error( "%s", text);
}

void QDECL Com_Printf( const char *msg, ... ) {
	va_list		argptr;
	char		text[1024];

	va_start (argptr, msg);
	vsprintf (text, msg, argptr);
	va_end (argptr);

	G_Printf ("%s", text);
}

#endif

/*
========================================================================

PLAYER COUNTING / SCORE SORTING

========================================================================
*/

/*
=============
AddTournamentPlayer

If there are less than two tournament players, put a
spectator in the game and restart
=============
*/
void AddTournamentPlayer( void ) {
	int			i;
	gclient_t	*client;
	gclient_t	*nextInLine;

	if ( level.numPlayingClients >= 2 ) {
		return;
	}

	// never change during intermission
	if ( level.intermissiontime ) {
		return;
	}

	nextInLine = NULL;

	for ( i = 0 ; i < level.maxclients ; i++ ) {
		client = &level.clients[i];
		if ( client->pers.connected != CON_CONNECTED ) {
			continue;
		}
		if ( client->sess.sessionTeam != TEAM_SPECTATOR ) {
			continue;
		}
		// never select the dedicated follow or scoreboard clients
		if ( client->sess.spectatorState == SPECTATOR_SCOREBOARD ||
			client->sess.spectatorClient < 0  ) {
			continue;
		}

		if ( !nextInLine || client->sess.spectatorTime < nextInLine->sess.spectatorTime ) {
			nextInLine = client;
		}
	}

	if ( !nextInLine ) {
		return;
	}

	level.warmupTime = -1;

	// set them to free-for-all team
	SetTeam( &g_entities[ nextInLine - level.clients ], "f" );
}

/*
=======================
RemoveTournamentLoser

Make the loser a spectator at the back of the line
=======================
*/
void RemoveTournamentLoser( void ) {
	int			clientNum;

	if ( level.numPlayingClients != 2 ) {
		return;
	}

	clientNum = level.sortedClients[1];

	if ( level.clients[ clientNum ].pers.connected != CON_CONNECTED ) {
		return;
	}

	// make them a spectator
	SetTeam( &g_entities[ clientNum ], "s" );
}

/*
=======================
RemoveTournamentWinner
=======================
*/
void RemoveTournamentWinner( void ) {
	int			clientNum;

	if ( level.numPlayingClients != 2 ) {
		return;
	}

	clientNum = level.sortedClients[0];

	if ( level.clients[ clientNum ].pers.connected != CON_CONNECTED ) {
		return;
	}

	// make them a spectator
	SetTeam( &g_entities[ clientNum ], "s" );
}

/*
=======================
AdjustTournamentScores
=======================
*/
void AdjustTournamentScores( void ) {
	int			clientNum;

	clientNum = level.sortedClients[0];
	if ( level.clients[ clientNum ].pers.connected == CON_CONNECTED ) {
		level.clients[ clientNum ].sess.wins++;
		ClientUserinfoChanged( clientNum );
	}

	clientNum = level.sortedClients[1];
	if ( level.clients[ clientNum ].pers.connected == CON_CONNECTED ) {
		level.clients[ clientNum ].sess.losses++;
		ClientUserinfoChanged( clientNum );
	}

}

/*
=============
SortRanks

=============
*/
int QDECL SortRanks( const void *a, const void *b ) {
	gclient_t	*ca, *cb;

	ca = &level.clients[*(int *)a];
	cb = &level.clients[*(int *)b];

	// Added so score is the only important factor in sorting
	if (g_gametype.integer < GT_TEAM) {
		// sort special clients last
		if ( ca->sess.spectatorState == SPECTATOR_SCOREBOARD || ca->sess.spectatorClient < 0 ) {
			return 1;
		}
		if ( cb->sess.spectatorState == SPECTATOR_SCOREBOARD || cb->sess.spectatorClient < 0  ) {
			return -1;
		}

		// then connecting clients
		if ( ca->pers.connected == CON_CONNECTING ) {
			return 1;
		}
		if ( cb->pers.connected == CON_CONNECTING ) {
			return -1;
		}


		// then spectators
		if ( ca->sess.sessionTeam == TEAM_SPECTATOR && cb->sess.sessionTeam == TEAM_SPECTATOR ) {
			if ( ca->sess.spectatorTime < cb->sess.spectatorTime ) {
				return -1;
			}
			if ( ca->sess.spectatorTime > cb->sess.spectatorTime ) {
				return 1;
			}
			return 0;
		}
		if ( ca->sess.sessionTeam == TEAM_SPECTATOR ) {
			return 1;
		}
		if ( cb->sess.sessionTeam == TEAM_SPECTATOR ) {
			return -1;
		}
	}

	// then sort by score
	if ( ca->ps.persistant[PERS_SCORE]
		> cb->ps.persistant[PERS_SCORE] ) {
		return -1;
	}
	if ( ca->ps.persistant[PERS_SCORE]
		< cb->ps.persistant[PERS_SCORE] ) {
		return 1;
	}
	return 0;
}

/*
============
CalculateRanks

Recalculates the score ranks of all players
This will be called on every client connect, begin, disconnect, death,
and team change.
============
*/
void CalculateRanks (void) {
	int		i, rank, score, newScore;
	gclient_t	*cl;

	level.follow1 = -1;
	level.follow2 = -1;
	level.numConnectedClients = 0;
	level.numNonSpectatorClients = 0;
	level.numPlayingClients = 0;
	level.numVotingClients = 0;		// don't count bots
	for (i = 0; i < TEAM_NUM_TEAMS; i++) {
		level.numteamVotingClients[i] = 0;
	}
	for (i = 0 ; i < level.maxclients ; i++) {
		if (level.clients[i].pers.connected != CON_DISCONNECTED) {
			level.sortedClients[level.numConnectedClients] = i;
			level.numConnectedClients++;

			if (g_gametype.integer == GT_TEAMPLAY) {
				if (level.clients[i].sess.savedTeam != TEAM_SPECTATOR) {
					level.numNonSpectatorClients++;

					// decide if this should be auto-followed
					if (level.clients[i].pers.connected == CON_CONNECTED) {
						level.numPlayingClients++;
						if (!(g_entities[i].r.svFlags & SVF_BOT)) {
							level.numVotingClients++;
							if (level.clients[i].sess.savedTeam == TEAM_RED)
								level.numteamVotingClients[0]++;
							else if (level.clients[i].sess.savedTeam == TEAM_BLUE)
								level.numteamVotingClients[1]++;
						}
						if (level.follow1 == -1) {
							level.follow1 = i;
						} else if (level.follow2 == -1) {
							level.follow2 = i;
						}
					}
				}
			} else {
				if (level.clients[i].sess.sessionTeam != TEAM_SPECTATOR) {
					level.numNonSpectatorClients++;

					// decide if this should be auto-followed
					if (level.clients[i].pers.connected == CON_CONNECTED) {
						level.numPlayingClients++;
						if (!(g_entities[i].r.svFlags & SVF_BOT)) {
							level.numVotingClients++;
							if (level.clients[i].sess.sessionTeam == TEAM_RED)
								level.numteamVotingClients[0]++;
							else if (level.clients[i].sess.sessionTeam == TEAM_BLUE)
								level.numteamVotingClients[1]++;
						}
						if (level.follow1 == -1) {
							level.follow1 = i;
						} else if (level.follow2 == -1) {
							level.follow2 = i;
						}
					}
				}
			}
		}
	}

	qsort(level.sortedClients, level.numConnectedClients,
		sizeof(level.sortedClients[0]), SortRanks);

	// set the rank value for all clients that are connected and not spectators
	if (g_gametype.integer >= GT_TEAM) {
		// in team games, rank is just the order of the teams, 0=red, 1=blue, 2=tied
		for (i = 0;  i < level.numConnectedClients; i++) {
			cl = &level.clients[level.sortedClients[i]];
			if (level.teamScores[TEAM_RED] == level.teamScores[TEAM_BLUE]) {
				cl->ps.persistant[PERS_RANK] = 2;
			} else if (level.teamScores[TEAM_RED] > level.teamScores[TEAM_BLUE]) {
				cl->ps.persistant[PERS_RANK] = 0;
			} else {
				cl->ps.persistant[PERS_RANK] = 1;
			}
		}
	} else {
		rank = -1;
		score = 0;
		for (i = 0;  i < level.numPlayingClients; i++) {
			cl = &level.clients[level.sortedClients[i]];
			newScore = cl->ps.persistant[PERS_SCORE];
			if (i == 0 || newScore != score) {
				rank = i;
				// assume we aren't tied until the next client is checked
				level.clients[level.sortedClients[i]].ps.persistant[PERS_RANK] = rank;
			} else {
				// we are tied with the previous client
				level.clients[level.sortedClients[i-1]].ps.persistant[PERS_RANK] = rank | RANK_TIED_FLAG;
				level.clients[level.sortedClients[i]].ps.persistant[PERS_RANK] = rank | RANK_TIED_FLAG;
			}
			score = newScore;
			if (g_gametype.integer == GT_SINGLE_PLAYER && level.numPlayingClients == 1) {
				level.clients[level.sortedClients[i]].ps.persistant[PERS_RANK] = rank | RANK_TIED_FLAG;
			}
		}
	}

	// set the CS_SCORES1/2 configstrings, which will be visible to everyone
	if (g_gametype.integer >= GT_TEAM) {
		trap_SetConfigstring (CS_SCORES1, va("%i", level.teamScores[TEAM_RED]));
		trap_SetConfigstring (CS_SCORES2, va("%i", level.teamScores[TEAM_BLUE]));
	} else {
		if (level.numConnectedClients == 0) {
			trap_SetConfigstring (CS_SCORES1, va("%i", SCORE_NOT_PRESENT));
			trap_SetConfigstring (CS_SCORES2, va("%i", SCORE_NOT_PRESENT));
		} else if (level.numConnectedClients == 1) {
			trap_SetConfigstring (CS_SCORES1, va("%i", level.clients[level.sortedClients[0]].ps.persistant[PERS_SCORE]));
			trap_SetConfigstring (CS_SCORES2, va("%i", SCORE_NOT_PRESENT));
		} else {
			trap_SetConfigstring (CS_SCORES1, va("%i", level.clients[level.sortedClients[0]].ps.persistant[PERS_SCORE]));
			trap_SetConfigstring (CS_SCORES2, va("%i", level.clients[level.sortedClients[1]].ps.persistant[PERS_SCORE]));
		}
	}

	// see if it is time to end the level
	CheckExitRules();

	// if we are at the intermission, send the new info to everyone
	if (level.intermissiontime) {
		SendScoreboardMessageToAllClients();
	}
}


/*
========================================================================

MAP CHANGING

========================================================================
*/

/*
========================
SendScoreboardMessageToAllClients

Do this at BeginIntermission time and whenever ranks are recalculated
due to enters/exits/forced team changes
========================
*/
void SendScoreboardMessageToAllClients( void ) {
	int		i;

	for ( i = 0 ; i < level.maxclients ; i++ ) {
		if ( level.clients[ i ].pers.connected == CON_CONNECTED ) {
			DeathmatchScoreboardMessage( g_entities + i );
		}
	}
}

/*
========================
MoveClientToIntermission

When the intermission starts, this will be called for all players.
If a new client connects, this will be called after the spawn function.
========================
*/
void MoveClientToIntermission( gentity_t *ent ) {
	// take out of follow mode if needed
	if ( ent->client->sess.spectatorState == SPECTATOR_FOLLOW ) {
		StopFollowing( ent );
	}


	// move to the spot
	VectorCopy( level.intermission_origin, ent->s.origin );
	VectorCopy( level.intermission_origin, ent->client->ps.origin );
	VectorCopy (level.intermission_angle, ent->client->ps.viewangles);
	ent->client->ps.pm_type = PM_INTERMISSION;

	// clean up powerup info
	memset( ent->client->ps.powerups, 0, sizeof(ent->client->ps.powerups) );

	ent->client->ps.eFlags = 0;
	ent->s.eFlags = 0;
	ent->s.eType = ET_GENERAL;
	ent->s.modelindex = 0;
	ent->s.loopSound = 0;
	ent->s.event = 0;
	ent->r.contents = 0;
}

/*
==================
FindIntermissionPoint

This is also used for spectator spawns
==================
*/
void FindIntermissionPoint( void ) {
	gentity_t	*ent, *target;
	vec3_t		dir;

	// find the intermission spot
	ent = G_Find (NULL, FOFS(classname), "info_player_intermission");
	if ( !ent ) {	// the map creator forgot to put in an intermission point...
		SelectSpawnPoint ( vec3_origin, level.intermission_origin, level.intermission_angle );
	} else {
		VectorCopy (ent->s.origin, level.intermission_origin);
		VectorCopy (ent->s.angles, level.intermission_angle);
		// if it has a target, look towards it
		if ( ent->target ) {
			target = G_PickTarget( ent->target );
			if ( target ) {
				VectorSubtract( target->s.origin, level.intermission_origin, dir );
				vectoangles( dir, level.intermission_angle );
			}
		}
	}

}

/*
==================
BeginIntermission
==================
*/
void BeginIntermission( void ) {
	int			i;
	gentity_t	*client;

	if ( level.intermissiontime ) {
		return;		// already active
	}

	trap_SendServerCommand( -1, va("print \"Next map in rotation is %s\n\"", g_RQ3_NextMap.string) );

	// if in tournement mode, change the wins / losses
	if ( g_gametype.integer == GT_TOURNAMENT ) {
		AdjustTournamentScores();
	}

	level.intermissiontime = level.time;
	FindIntermissionPoint();

#ifdef MISSIONPACK
	if (g_singlePlayer.integer) {
		trap_Cvar_Set("ui_singlePlayerActive", "0");
		UpdateTournamentInfo();
	}
#else
	// if single player game
	if ( g_gametype.integer == GT_SINGLE_PLAYER ) {
		UpdateTournamentInfo();
		SpawnModelsOnVictoryPads();
	}
#endif

	// move all clients to the intermission point
	for (i=0 ; i< level.maxclients ; i++) {
		client = g_entities + i;
		if (!client->inuse)
			continue;
		// respawn if dead
		if (client->health <= 0) {
			respawn(client);
		}
		MoveClientToIntermission( client );
// JBravo: send the TP scoreboard to players
		if (g_gametype.integer == GT_TEAMPLAY)
			trap_SendServerCommand (i, va("rq3_cmd %i",MAPEND));
	}

	// send the current scoring to all clients
	if (g_gametype.integer != GT_TEAMPLAY)
		SendScoreboardMessageToAllClients();

  //Stop the demos
  trap_SendServerCommand (-1, va("rq3_cmd %i",STOPDEMO));
  //Take the screen shot
  trap_SendServerCommand (-1, va("rq3_cmd %i",SCREENSHOT));

}


/*
=============
ExitLevel

When the intermission has been exited, the server is either killed
or moved to a new level based on the "nextmap" cvar

=============
*/
void ExitLevel (void) {
	int		i;
	gclient_t *cl;

	//bot interbreeding
	BotInterbreedEndMatch();

	// if we are running a tournement map, kick the loser to spectator status,
	// which will automatically grab the next spectator and restart
	if ( g_gametype.integer == GT_TOURNAMENT ) {
		if ( !level.restarted ) {
			RemoveTournamentLoser();
			trap_SendConsoleCommand( EXEC_APPEND, "map_restart 0\n" );
			level.restarted = qtrue;
			level.changemap = NULL;
			level.intermissiontime = 0;
		}
		return;
	}

	//	trap_SendConsoleCommand( EXEC_APPEND, "vstr nextmap\n" );
	//  Map ini stuff
	if( g_RQ3_ValidIniFile.integer )  
		RQ3_ReadInitFile();


	trap_SendConsoleCommand( EXEC_APPEND, "vstr nextmap\n" );
	level.changemap = NULL;
	level.intermissiontime = 0;

	// reset all the scores so we don't enter the intermission again
	level.teamScores[TEAM_RED] = 0;
	level.teamScores[TEAM_BLUE] = 0;
	for ( i=0 ; i< g_maxclients.integer ; i++ ) {
		cl = level.clients + i;
		if ( cl->pers.connected != CON_CONNECTED ) {
			continue;
		}
		cl->ps.persistant[PERS_SCORE] = 0;
	}

	// we need to do this here before chaning to CON_CONNECTING
	G_WriteSessionData();

	// change all client states to connecting, so the early players into the
	// next level will know the others aren't done reconnecting
	for (i=0 ; i< g_maxclients.integer ; i++) {
		if ( level.clients[i].pers.connected == CON_CONNECTED ) {
			level.clients[i].pers.connected = CON_CONNECTING;
		}
	}

}

/*
=================
G_LogPrintf

Print to the logfile with a time stamp if it is open
=================
*/
void QDECL G_LogPrintf( const char *fmt, ... ) {
	va_list		argptr;
	char		string[1024];
	int		min, tens, sec, i, l;

	sec = level.time / 1000;
	min = sec / 60;
	sec -= min * 60;
	tens = sec / 10;
	sec -= tens * 10;

	l = i = 0;

	Com_sprintf (string, sizeof(string), "%3i:%i%i ", min, tens, sec);

	va_start (argptr, fmt);
	vsprintf (string +7, fmt, argptr);
	va_end (argptr);

	if (g_dedicated.integer) {
		G_Printf ("%s", string + 7);
	}

	if (!level.logFile) {
		return;
	}

// JBravo: damn colors fsck up the logs and make them ugly.
	for (i = 0; string[i]; i++) {
		if (Q_IsColorString (&string[i])) {
			i++;
			continue;
		}
		if (string[i] > 0x7E)
			continue;
		if (string[i] == 0x19)
			continue;
		string[l++] = string[i];
	}
	string[l] = '\0';

	trap_FS_Write (string, strlen(string), level.logFile);
}

/*
================
LogExit

Append information about this game to the log file
================
*/
void LogExit( const char *string ) {
	int				i, numSorted;
	gclient_t		*cl;
#ifdef MISSIONPACK // bk001205
	qboolean won = qtrue;
#endif
	G_LogPrintf( "Exit: %s\n", string );

	level.intermissionQueued = level.time;

	// this will keep the clients from playing any voice sounds
	// that will get cut off when the queued intermission starts
	trap_SetConfigstring( CS_INTERMISSION, "1" );

	// don't send more than 32 scores (FIXME?)
	numSorted = level.numConnectedClients;
	if ( numSorted > 32 ) {
		numSorted = 32;
	}

	if ( g_gametype.integer >= GT_TEAM ) {
		G_LogPrintf( "red:%i  blue:%i\n",
			level.teamScores[TEAM_RED], level.teamScores[TEAM_BLUE] );
	}

	for (i=0 ; i < numSorted ; i++) {
		int		ping;

		cl = &level.clients[level.sortedClients[i]];

		if ( cl->sess.sessionTeam == TEAM_SPECTATOR ) {
			continue;
		}
		if ( cl->pers.connected == CON_CONNECTING ) {
			continue;
		}

		ping = cl->ps.ping < 999 ? cl->ps.ping : 999;

		G_LogPrintf( "score: %i  ping: %i  client: %i %s\n", cl->ps.persistant[PERS_SCORE], ping, level.sortedClients[i],	cl->pers.netname );
#ifdef MISSIONPACK
		if (g_singlePlayer.integer && g_gametype.integer == GT_TOURNAMENT) {
			if (g_entities[cl - level.clients].r.svFlags & SVF_BOT && cl->ps.persistant[PERS_RANK] == 0) {
				won = qfalse;
			}
	}
#endif

		// Don't print bot statistics
		if ( g_RQ3_statLog.integer && !(g_entities[cl - level.clients].r.svFlags & SVF_BOT) )
		{
			// Elder: Statistics tracking for server
			G_LogPrintf( "-----------------------------------\n");
			G_LogPrintf( "Reaction Quake 3 Statistics Results for client %i %s\n", level.sortedClients[i], cl->pers.netname );
			G_LogPrintf( "Kicks: %i  kills %i  deaths %i\n", cl->pers.records[REC_KICKHITS],
							cl->pers.records[REC_KICKKILLS], cl->pers.records[REC_KICKDEATHS]);
			G_LogPrintf( "Knife Throw Stats: hits/shots %i/%i  kills %i  deaths %i\n",
							cl->pers.records[REC_KNIFETHROWHITS], cl->pers.records[REC_KNIFETHROWSHOTS],
							cl->pers.records[REC_KNIFETHROWKILLS], cl->pers.records[REC_KNIFETHROWDEATHS]);
			G_LogPrintf( "Knife Slash Stats: hits/shots %i/%i  kills %i  deaths %i\n",
							cl->pers.records[REC_KNIFESLASHHITS], cl->pers.records[REC_KNIFESLASHSHOTS],
							cl->pers.records[REC_KNIFESLASHKILLS], cl->pers.records[REC_KNIFESLASHDEATHS]);
			G_LogPrintf( "MK23 Stats: hits/shots %i/%i  kills %i  deaths %i\n",
							cl->pers.records[REC_MK23HITS], cl->pers.records[REC_MK23SHOTS],
							cl->pers.records[REC_MK23KILLS], cl->pers.records[REC_MK23DEATHS]);
			G_LogPrintf( "MP5 Stats: hits/shots %i/%i  kills %i  deaths %i\n",
							cl->pers.records[REC_MP5HITS], cl->pers.records[REC_MP5SHOTS],
							cl->pers.records[REC_MP5KILLS], cl->pers.records[REC_MP5DEATHS]);
			G_LogPrintf( "M4 Stats: hits/shots %i/%i  kills %i  deaths %i\n",
							cl->pers.records[REC_M4HITS], cl->pers.records[REC_M4SHOTS],
							cl->pers.records[REC_M4KILLS], cl->pers.records[REC_M4DEATHS]);
			G_LogPrintf( "M3 Stats: hits/shots %i/%i  kills %i  deaths %i\n",
							cl->pers.records[REC_M3HITS], cl->pers.records[REC_M3SHOTS],
							cl->pers.records[REC_M3KILLS], cl->pers.records[REC_M3DEATHS]);
			G_LogPrintf( "HC Stats: hits/shots %i/%i  kills %i  deaths %i\n",
							cl->pers.records[REC_HANDCANNONHITS], cl->pers.records[REC_HANDCANNONSHOTS],
							cl->pers.records[REC_HANDCANNONKILLS], cl->pers.records[REC_HANDCANNONDEATHS]);
			G_LogPrintf( "SSG3000 Stats: hits/shots %i/%i  kills %i  deaths %i\n",
							cl->pers.records[REC_SSG3000HITS], cl->pers.records[REC_SSG3000SHOTS],
							cl->pers.records[REC_SSG3000KILLS], cl->pers.records[REC_SSG3000DEATHS]);
			G_LogPrintf( "Akimbo Stats: hits/shots %i/%i  kills %i  deaths %i\n",
							cl->pers.records[REC_AKIMBOHITS], cl->pers.records[REC_AKIMBOSHOTS],
							cl->pers.records[REC_AKIMBOKILLS], cl->pers.records[REC_AKIMBODEATHS]);
			G_LogPrintf( "Grenade Stats: hits/shots %i/%i  kills %i  deaths %i\n",
							cl->pers.records[REC_GRENADEHITS], cl->pers.records[REC_GRENADESHOTS],
							cl->pers.records[REC_GRENADEKILLS], cl->pers.records[REC_GRENADEDEATHS]);
			G_LogPrintf( "Location Shot Stats 1: head %i  chest %i  stomach %i  leg %i\n",
							cl->pers.records[REC_HEADSHOTS], cl->pers.records[REC_CHESTSHOTS],
							cl->pers.records[REC_STOMACHSHOTS], cl->pers.records[REC_LEGSHOTS]);
			G_LogPrintf( "Location Shot Stats 2: front %i  back %i  left %i  right %i\n",
							cl->pers.records[REC_FRONTSHOTS], cl->pers.records[REC_BACKSHOTS],
							cl->pers.records[REC_LEFTSHOTS], cl->pers.records[REC_RIGHTSHOTS]);
			G_LogPrintf( "Location Kill Stats: head %i  chest %i  stomach %i  leg %i\n",
							cl->pers.records[REC_HEADKILLS], cl->pers.records[REC_CHESTKILLS],
							cl->pers.records[REC_STOMACHKILLS], cl->pers.records[REC_LEGKILLS]);
			G_LogPrintf( "Location Death Stats: head %i  chest %i  stomach %i  leg %i\n",
							cl->pers.records[REC_HEADDEATHS], cl->pers.records[REC_CHESTDEATHS],
							cl->pers.records[REC_STOMACHDEATHS], cl->pers.records[REC_LEGDEATHS]);
			G_LogPrintf( "Morbid Stats: corpse shots %i  gib shots %i\n",
							cl->pers.records[REC_CORPSESHOTS], cl->pers.records[REC_GIBSHOTS]);
			G_LogPrintf( "-----------------------------------\n");
		}
	}

#ifdef MISSIONPACK
	if (g_singlePlayer.integer) {
		if (g_gametype.integer >= GT_CTF) {
			won = level.teamScores[TEAM_RED] > level.teamScores[TEAM_BLUE];
		}
		trap_SendConsoleCommand( EXEC_APPEND, (won) ? "spWin\n" : "spLose\n" );
	}
#endif


}


/*
=================
CheckIntermissionExit

The level will stay at the intermission for a minimum of 5 seconds
If all players wish to continue, the level will then exit.
If one or more players have not acknowledged the continue, the game will
wait 10 seconds before going on.

Slicer: This is changed for rq3. minimum of 5 secs showing scoreboard
and then, if a player presses BUTTON_ATTACK, change the map

=================
*/
void CheckIntermissionExit( void ) {
//	int			ready, notReady;
	int			i;
	gclient_t	*cl;
//	int			readyMask;

/*	if ( g_gametype.integer == GT_SINGLE_PLAYER ) {
		return;
	}

	// see which players are ready
	ready = 0;
	notReady = 0;
	readyMask = 0;
	for (i=0 ; i< g_maxclients.integer ; i++) {
		cl = level.clients + i;
		if ( cl->pers.connected != CON_CONNECTED ) {
			continue;
		}
		if ( g_entities[cl->ps.clientNum].r.svFlags & SVF_BOT ) {
			continue;
		}

		if ( cl->readyToExit ) {
			ready++;
			if ( i < 16 ) {
				readyMask |= 1 << i;
			}
		} else {
			notReady++;
		}
	}

	// copy the readyMask to each player's stats so
	// it can be displayed on the scoreboard
	for (i=0 ; i< g_maxclients.integer ; i++) {
		cl = level.clients + i;
		if ( cl->pers.connected != CON_CONNECTED ) {
			continue;
		}
		cl->ps.stats[STAT_CLIENTS_READY] = readyMask;
	}
*/
	// never exit in less than five seconds
	if ( level.time < level.intermissiontime + 5000 ) {
		return;
	}

	for (i=0 ; i< g_maxclients.integer ; i++) {
		cl = level.clients + i;
		if ( cl->pers.connected != CON_CONNECTED ) {
			continue;
		}
		if ( g_entities[cl->ps.clientNum].r.svFlags & SVF_BOT ) {
			continue;
		}
		if(g_entities[cl->ps.clientNum].client->buttons & BUTTON_ATTACK)
			ExitLevel();
	}
/*
	// if nobody wants to go, clear timer
	if ( !ready ) {
		level.readyToExit = qfalse;
		return;
	}

	// if everyone wants to go, go now
	if ( !notReady ) {
		ExitLevel();
		return;
	}

	// the first person to ready starts the ten second timeout
	if ( !level.readyToExit ) {
		level.readyToExit = qtrue;
		level.exitTime = level.time;
	}

	// if we have waited ten seconds since at least one player
	// wanted to exit, go ahead
	if ( level.time < level.exitTime + 10000 ) {
		return;
	}

	ExitLevel();
	*/
}

/*
=============
ScoreIsTied
=============
*/
qboolean ScoreIsTied( void ) {
	int		a, b;

	if ( level.numPlayingClients < 2 ) {
		return qfalse;
	}

	if ( g_gametype.integer >= GT_TEAM ) {
		return level.teamScores[TEAM_RED] == level.teamScores[TEAM_BLUE];
	}

	a = level.clients[level.sortedClients[0]].ps.persistant[PERS_SCORE];
	b = level.clients[level.sortedClients[1]].ps.persistant[PERS_SCORE];

	return a == b;
}

/*
=================
CheckExitRules

There will be a delay between the time the exit is qualified for
and the time everyone is moved to the intermission spot, so you
can see the last frag.

=================
*/
void CheckExitRules( void ) {
	int			i;
	gclient_t	*cl;
	// if at the intermission, wait for all non-bots to
	// signal ready, then go to next level
	if ( level.intermissiontime ) {
		CheckIntermissionExit ();
		return;
	}
	//Slicer
	if(g_gametype.integer == GT_TEAMPLAY) {
		//Let's check fraglimit here, everything else is on teamplay.c
		if(g_fraglimit.integer > 0) {
			for ( i=0 ; i< g_maxclients.integer ; i++ ) {
				cl = level.clients + i;
				if ( cl->pers.connected != CON_CONNECTED ) {
					continue;
				}
				if ( cl->sess.savedTeam == TEAM_SPECTATOR ) {
					continue;
				}
				if ( cl->ps.persistant[PERS_SCORE] >= g_fraglimit.integer ) {
					LogExit( "Fraglimit hit." );
					trap_SendServerCommand( -1, va("print \"%s" S_COLOR_WHITE " hit the fraglimit.\n\"",
						cl->pers.netname ) );
					//Slicer: Start Intermission
					BeginIntermission();
				}
			}
		}
		//let's return if teamplay.
	return;
	}

	if ( level.intermissionQueued ) {
#ifdef MISSIONPACK
		int time = (g_singlePlayer.integer) ? SP_INTERMISSION_DELAY_TIME : INTERMISSION_DELAY_TIME;
		if ( level.time - level.intermissionQueued >= time ) {
			level.intermissionQueued = 0;
			BeginIntermission();
		}
#else
		if ( level.time - level.intermissionQueued >= INTERMISSION_DELAY_TIME ) {
			level.intermissionQueued = 0;
			BeginIntermission();
		}
#endif
		return;
	}

	// check for sudden death
	if (  ScoreIsTied() ) {
		// always wait for sudden death
				return;
			}
	if ( g_timelimit.integer && !level.warmupTime) {
		if ( level.time - level.startTime >= g_timelimit.integer*60000 ) {
			trap_SendServerCommand( -1, "print \"Timelimit hit.\n\"");
			LogExit( "Timelimit hit." );
			return;
		}
	}

	if ( level.numPlayingClients < 2 ) {
		return;
	}

	if ( g_gametype.integer < GT_CTF && g_fraglimit.integer ) {
		if ( level.teamScores[TEAM_RED] >= g_fraglimit.integer ) {
			trap_SendServerCommand( -1, "print \"Red hit the fraglimit.\n\"" );
			LogExit( "Fraglimit hit." );
			return;
		}

		if ( level.teamScores[TEAM_BLUE] >= g_fraglimit.integer ) {
			trap_SendServerCommand( -1, "print \"Blue hit the fraglimit.\n\"" );
			LogExit( "Fraglimit hit." );
			return;
		}

		for ( i=0 ; i< g_maxclients.integer ; i++ ) {
			cl = level.clients + i;
			if ( cl->pers.connected != CON_CONNECTED ) {
				continue;
			}
			if ( cl->sess.sessionTeam != TEAM_FREE ) {
				continue;
			}

			if ( cl->ps.persistant[PERS_SCORE] >= g_fraglimit.integer ) {
				LogExit( "Fraglimit hit." );
				trap_SendServerCommand( -1, va("print \"%s" S_COLOR_WHITE " hit the fraglimit.\n\"",
					cl->pers.netname ) );
				return;
			}
		}
	}

	if ( g_gametype.integer >= GT_CTF && g_capturelimit.integer ) {

		if ( level.teamScores[TEAM_RED] >= g_capturelimit.integer ) {
			trap_SendServerCommand( -1, "print \"Red hit the capturelimit.\n\"" );
			LogExit( "Capturelimit hit." );
			return;
		}

		if ( level.teamScores[TEAM_BLUE] >= g_capturelimit.integer ) {
			trap_SendServerCommand( -1, "print \"Blue hit the capturelimit.\n\"" );
			LogExit( "Capturelimit hit." );
			return;
		}
	}
	
}



/*
========================================================================

FUNCTIONS CALLED EVERY FRAME

========================================================================
*/


/*
=============
CheckTournament

Once a frame, check for changes in tournement player state
=============
*/
void CheckTournament( void ) {
	// check because we run 3 game frames before calling Connect and/or ClientBegin
	// for clients on a map_restart
	if ( level.numPlayingClients == 0 ) {
		return;
	}

	if ( g_gametype.integer == GT_TOURNAMENT ) {

		// pull in a spectator if needed
		if ( level.numPlayingClients < 2 ) {
			AddTournamentPlayer();
		}

		// if we don't have two players, go back to "waiting for players"
		if ( level.numPlayingClients != 2 ) {
			if ( level.warmupTime != -1 ) {
				level.warmupTime = -1;
				trap_SetConfigstring( CS_WARMUP, va("%i", level.warmupTime) );
				G_LogPrintf( "Warmup:\n" );
			}
			return;
		}

		if ( level.warmupTime == 0 ) {
			return;
		}

		// if the warmup is changed at the console, restart it
		if ( g_warmup.modificationCount != level.warmupModificationCount ) {
			level.warmupModificationCount = g_warmup.modificationCount;
			level.warmupTime = -1;
		}

		// if all players have arrived, start the countdown
		if ( level.warmupTime < 0 ) {
			if ( level.numPlayingClients == 2 ) {
				// fudge by -1 to account for extra delays
				level.warmupTime = level.time + ( g_warmup.integer - 1 ) * 1000;
				trap_SetConfigstring( CS_WARMUP, va("%i", level.warmupTime) );
			}
			return;
		}

		// if the warmup time has counted down, restart
		if ( level.time > level.warmupTime ) {
			level.warmupTime += 10000;
			trap_Cvar_Set( "g_restarted", "1" );
			trap_SendConsoleCommand( EXEC_APPEND, "map_restart 0\n" );
			level.restarted = qtrue;
			return;
		}
	} else if ( g_gametype.integer != GT_SINGLE_PLAYER && level.warmupTime != 0 ) {
		int		counts[TEAM_NUM_TEAMS];
		qboolean	notEnough = qfalse;

		if ( g_gametype.integer > GT_TEAM ) {
			counts[TEAM_BLUE] = TeamCount( -1, TEAM_BLUE );
			counts[TEAM_RED] = TeamCount( -1, TEAM_RED );

			if (counts[TEAM_RED] < 1 || counts[TEAM_BLUE] < 1) {
				notEnough = qtrue;
			}
		} else if ( level.numPlayingClients < 2 ) {
			notEnough = qtrue;
		}

		if ( notEnough ) {
			if ( level.warmupTime != -1 ) {
				level.warmupTime = -1;
				trap_SetConfigstring( CS_WARMUP, va("%i", level.warmupTime) );
				G_LogPrintf( "Warmup:\n" );
			}
			return; // still waiting for team members
		}

		if ( level.warmupTime == 0 ) {
			return;
		}

		// if the warmup is changed at the console, restart it
		if ( g_warmup.modificationCount != level.warmupModificationCount ) {
			level.warmupModificationCount = g_warmup.modificationCount;
			level.warmupTime = -1;
		}

		// if all players have arrived, start the countdown
		if ( level.warmupTime < 0 ) {
			// fudge by -1 to account for extra delays
			level.warmupTime = level.time + ( g_warmup.integer - 1 ) * 1000;
			trap_SetConfigstring( CS_WARMUP, va("%i", level.warmupTime) );
			return;
		}

		// if the warmup time has counted down, restart
		if ( level.time > level.warmupTime ) {
			level.warmupTime += 10000;
			trap_Cvar_Set( "g_restarted", "1" );
			trap_SendConsoleCommand( EXEC_APPEND, "map_restart 0\n" );
			level.restarted = qtrue;
			return;
		}
	}
}


/*
==================
CheckVote
==================
*/
void CheckVote( void ) {
	if ( level.voteExecuteTime && level.voteExecuteTime < level.time ) {
		level.voteExecuteTime = 0;
		trap_SendConsoleCommand( EXEC_APPEND, va("%s\n", level.voteString ) );
	}
	if ( !level.voteTime ) {
		return;
	}
	if ( level.time - level.voteTime >= VOTE_TIME ) {
		trap_SendServerCommand( -1, "print \"Vote failed.\n\"" );
	} else {
		if ( level.voteYes > level.numVotingClients/2 ) {
			// execute the command, then remove the vote
			trap_SendServerCommand( -1, "print \"Vote passed.\n\"" );
			level.voteExecuteTime = level.time + 3000;
		} else if ( level.voteNo >= level.numVotingClients/2 ) {
			// same behavior as a timeout
			trap_SendServerCommand( -1, "print \"Vote failed.\n\"" );
		} else {
			// still waiting for a majority
			return;
		}
	}
	level.voteTime = 0;
	trap_SetConfigstring( CS_VOTE_TIME, "" );

}

/*
==================
PrintTeam
==================
*/
void PrintTeam(int team, char *message) {
	int i;

	for ( i = 0 ; i < level.maxclients ; i++ ) {
		if (level.clients[i].sess.sessionTeam != team)
			continue;
		trap_SendServerCommand( i, message );
	}
}

/*
==================
SetLeader
==================
*/
void SetLeader(int team, int client) {
	int i;

	if ( level.clients[client].pers.connected == CON_DISCONNECTED ) {
		PrintTeam(team, va("print \"%s^7 is not connected\n\"", level.clients[client].pers.netname) );
		return;
	}
	if (level.clients[client].sess.sessionTeam != team) {
		PrintTeam(team, va("print \"%s^7 is not on the team anymore\n\"", level.clients[client].pers.netname) );
		return;
	}
	for ( i = 0 ; i < level.maxclients ; i++ ) {
		if (level.clients[i].sess.sessionTeam != team)
			continue;
		if (level.clients[i].sess.teamLeader) {
			level.clients[i].sess.teamLeader = qfalse;
			ClientUserinfoChanged(i);
		}
	}
	level.clients[client].sess.teamLeader = qtrue;
	ClientUserinfoChanged( client );
	PrintTeam(team, va("print \"%s^7 is the new team leader\n\"", level.clients[client].pers.netname) );
}

/*
==================
CheckTeamLeader
==================
*/
void CheckTeamLeader( int team ) {
	int i;

	for ( i = 0 ; i < level.maxclients ; i++ ) {
		if (level.clients[i].sess.sessionTeam != team)
			continue;
		if (level.clients[i].sess.teamLeader)
			break;
	}
	if (i >= level.maxclients) {
		for ( i = 0 ; i < level.maxclients ; i++ ) {
			if (level.clients[i].sess.sessionTeam != team)
				continue;
			if (!(g_entities[i].r.svFlags & SVF_BOT)) {
				level.clients[i].sess.teamLeader = qtrue;
				break;
			}
		}
		for ( i = 0 ; i < level.maxclients ; i++ ) {
			if (level.clients[i].sess.sessionTeam != team)
				continue;
			level.clients[i].sess.teamLeader = qtrue;
			break;
		}
	}
}

/*
==================
CheckTeamVote
==================
*/
void CheckTeamVote( int team ) {
	int cs_offset;

	if ( team == TEAM_RED )
		cs_offset = 0;
	else if ( team == TEAM_BLUE )
		cs_offset = 1;
	else
		return;

	if ( !level.teamVoteTime[cs_offset] ) {
		return;
	}
	if ( level.time - level.teamVoteTime[cs_offset] >= VOTE_TIME ) {
		trap_SendServerCommand( -1, "print \"Team vote failed.\n\"" );
	} else {
		if ( level.teamVoteYes[cs_offset] > level.numteamVotingClients[cs_offset]/2 ) {
			// execute the command, then remove the vote
			trap_SendServerCommand( -1, "print \"Team vote passed.\n\"" );
			//
			if ( !Q_strncmp( "leader", level.teamVoteString[cs_offset], 6) ) {
				//set the team leader
				SetLeader(team, atoi(level.teamVoteString[cs_offset] + 7));
			}
			else {
				trap_SendConsoleCommand( EXEC_APPEND, va("%s\n", level.teamVoteString[cs_offset] ) );
			}
		} else if ( level.teamVoteNo[cs_offset] >= level.numteamVotingClients[cs_offset]/2 ) {
			// same behavior as a timeout
			trap_SendServerCommand( -1, "print \"Team vote failed.\n\"" );
		} else {
			// still waiting for a majority
			return;
		}
	}
	level.teamVoteTime[cs_offset] = 0;
	trap_SetConfigstring( CS_TEAMVOTE_TIME + cs_offset, "" );

}


/*
==================
CheckCvars
==================
*/
void CheckCvars( void ) {
	static int lastMod = -1;

	if ( g_password.modificationCount != lastMod ) {
		lastMod = g_password.modificationCount;
		if ( *g_password.string && Q_stricmp( g_password.string, "none" ) ) {
			trap_Cvar_Set( "g_needpass", "1" );
		} else {
			trap_Cvar_Set( "g_needpass", "0" );
		}
	}
}

/*
=============
G_RunThink

Runs thinking code for this frame if necessary
=============
*/
void G_RunThink (gentity_t *ent) {
	float	thinktime;

	thinktime = ent->nextthink;
	if (thinktime <= 0) {
		return;
	}
	if (thinktime > level.time) {
		return;
	}

	ent->nextthink = 0;
	if (!ent->think) {
		G_Error ( "NULL ent->think");
	}
	ent->think (ent);
}

/*
================
G_RunFrame

Advances the non-player objects in the world
================
*/
void G_RunFrame( int levelTime ) {
	int			i;
	gentity_t	*ent;
	//Blaze: Used for droping knifes
	//gitem_t		*xr_item;
	//gentity_t	*xr_drop;
	//int			temp;
	int			msec;
	int 		start, end;

	// if we are waiting for the level to restart, do nothing
	if ( level.restarted ) {
		return;
	}

	level.framenum++;
	level.previousTime = level.time;
	level.time = levelTime;
	msec = level.time - level.previousTime;

	// get any cvar changes
	G_UpdateCvars();

	//
	// go through all allocated objects
	//
	start = trap_Milliseconds();
	ent = &g_entities[0];
	for (i=0 ; i<level.num_entities ; i++, ent++) {
		if ( !ent->inuse ) {
			continue;
		}

		// clear events that are too old
		if ( level.time - ent->eventTime > EVENT_VALID_MSEC ) {
			if ( ent->s.event ) {
				//G_Printf("Discarded: %i\n", ent->s.event & ~EV_EVENT_BITS);
				ent->s.event = 0;	// &= EV_EVENT_BITS;
				if ( ent->client ) {
					ent->client->ps.externalEvent = 0;
					// predicted events should never be set to zero
					//ent->client->ps.events[0] = 0;
					//ent->client->ps.events[1] = 0;
				}
			}
			if ( ent->freeAfterEvent ) {
				//Elder: moved to g_missile.c where it belongs
				// tempEntities or dropped items completely go away after their event
				//if (!strcmp(ent->classname,"weapon_knife"))
				//{
					/*
					xr_item = BG_FindItemForWeapon( WP_KNIFE );
					//Elder: removed
					//xr_drop= dropWeapon( ent, xr_item, 0,  FL_THROWN_ITEM );//FL_DROPPED_ITEM |
					xr_drop = LaunchItem(xr_item, ent->s.pos.trBase, 0, FL_THROWN_KNIFE);


					G_FreeEntity( ent );
					*/
				//}
				//else
				//{
					G_FreeEntity( ent );
				//}
				continue;
			} else if ( ent->unlinkAfterEvent ) {
				// items that will respawn will hide themselves after their pickup event
				ent->unlinkAfterEvent = qfalse;
				trap_UnlinkEntity( ent );
			}
		}

		// temporary entities don't think
		if ( ent->freeAfterEvent ) {
			continue;
		}

		if ( !ent->r.linked && ent->neverFree ) {
			continue;
		}

		if ( ent->s.eType == ET_MISSILE ) {
			G_RunMissile( ent );
			continue;
		}

		if ( ent->s.eType == ET_ITEM || ent->physicsObject ) {
			G_RunItem( ent );
			continue;
		}

		if ( ent->s.eType == ET_MOVER ) {
			G_RunMover( ent );
			continue;
		}

		// Elder: run dynamic lights
		if ( ent->s.eType == ET_DLIGHT ) {
			G_RunDlight( ent );
			continue;
		}

		if ( i < MAX_CLIENTS ) {
			G_RunClient( ent );    // Basicly calls ClientThink_real()
			continue;
		}

		G_RunThink( ent );
	}
	end = trap_Milliseconds();

	start = trap_Milliseconds();
	// perform final fixups on the players
	ent = &g_entities[0];
	for (i=0 ; i < level.maxclients ; i++, ent++ ) {
		if ( ent->inuse ) {
			ClientEndFrame( ent );
		}
	}
	end = trap_Milliseconds();

	// see if it is time to do a tournement restart
	// JBravo: no need if teamplay
	if ( g_gametype.integer != GT_TEAMPLAY ) {
	CheckTournament();
	}

	// see if it is time to end the level
	// JBravo: no need if teamplay
	// Slicer: We will need it now for the rotation system..
//	if ( g_gametype.integer != GT_TEAMPLAY ) {
	CheckExitRules();
//	}

	// update to team status?
	// JBravo: no need if teamplay
	if ( g_gametype.integer != GT_TEAMPLAY ) {
	CheckTeamStatus();
	}

	// cancel vote if timed out
	CheckVote();

	// JBravo: this is the main function in g_teamplay that does everything
	if ( g_gametype.integer == GT_TEAMPLAY ) {
		CheckTeamRules();
	}
	// Slicer: matchmode
	if(g_RQ3_matchmode.integer )
		MM_RunFrame();

	// check team votes
	CheckTeamVote( TEAM_RED );
	CheckTeamVote( TEAM_BLUE );

	// for tracking changes
	CheckCvars();

	if (g_listEntity.integer) {
		for (i = 0; i < MAX_GENTITIES; i++) {
			G_Printf("%4i: %s\n", i, g_entities[i].classname);
		}
		trap_Cvar_Set("g_listEntity", "0");
	}
}


/*
==============
RQ3_StartUniqueItems

Added by Elder
Spawns items at the beginning of a level
==============
*/
void RQ3_StartUniqueItems ( void )
{
	gitem_t		*rq3_item;
	gentity_t	*rq3_temp;
	float		angle = 0;

	G_Printf("RQ3_StartUniqueItems: Starting unique item spawn code...\n");

	rq3_item = BG_FindItemForHoldable( HI_SLIPPERS );
	rq3_temp = (gentity_t*)SelectRandomDeathmatchSpawnPoint();
	Drop_Item (rq3_temp, rq3_item, angle);
	angle += 30;

	rq3_item = BG_FindItemForHoldable( HI_KEVLAR );
	rq3_temp = (gentity_t*)SelectRandomDeathmatchSpawnPoint();
	Drop_Item (rq3_temp, rq3_item, angle);
	angle += 30;

	rq3_item = BG_FindItemForHoldable( HI_SILENCER );
	rq3_temp = (gentity_t*)SelectRandomDeathmatchSpawnPoint();
	Drop_Item (rq3_temp, rq3_item, angle);
	angle += 30;

	rq3_item = BG_FindItemForHoldable( HI_BANDOLIER );
	rq3_temp = (gentity_t*)SelectRandomDeathmatchSpawnPoint();
	Drop_Item (rq3_temp, rq3_item, angle);
	angle += 30;

	rq3_item = BG_FindItemForHoldable( HI_LASER );
	rq3_temp = (gentity_t*)SelectRandomDeathmatchSpawnPoint();
	Drop_Item (rq3_temp, rq3_item, angle);
	angle += 30;
}


/*
================
All RQ3 ini config system starts here with several help funtions. 

We have some functions:

  loader - loads the file
  parser - parses the file and reports errors
  manage_info - manages all the information


	cvars needed: RQ3_NextMap, RQ3_ValidInit (validates ini file so that no further processing is needed)
*/

enum	RQ3_InitTag {MAIN, ROTATION, MAP, CVARS, TEAM1, TEAM2, INVALID};
enum	RQ3_Parser {ERROR, TOKEN_TAG, TOKEN_CVAR, TOKEN_WORD, PARSING_OK, PARSING_ERROR, PARSING_LENGHT_ERROR};
#define CHECK_BOUND() if ((*cur_pos) > len) return PARSING_LENGHT_ERROR;

void RQ3_ReadInitFile() {
	fileHandle_t	file;
	char		*buf;
 	int		len;

 	len = trap_FS_FOpenFile (g_RQ3_IniFile.string, &file, FS_READ);
 	if (!file) {
 		G_Printf ("Could not open INI file\n");
		trap_Cvar_Set ("g_RQ3_ValidIniFile", "0");
		return;
 	}

	G_Printf ("RQ3 config system: Lenght of file is: %i\n", len);

 	buf = G_Alloc (len); 
	trap_FS_Read (buf, len, file);
 //	G_Printf ("RQ3 config system: Ini File contains: %s\n", buf);
 	trap_FS_FCloseFile (file);

	RQ3_ParseBuffer (buf, len); 
}

void RQ3_ParseBuffer (char *buf, int len) {
	char	tag[20];
	int	cur_pos, tag_type;

	for (cur_pos = 0;  cur_pos < len; cur_pos++) {
		// chop things we dont need
		if ((*(buf + cur_pos) == ' ') || (*(buf + cur_pos) == '\n') || (*(buf + cur_pos) == '\t') || (*(buf + cur_pos) == '\r'))
			continue;
		if (*(buf + cur_pos) == '<') { // we are in a tag
			cur_pos++;
			if ((tag_type = RQ3_GetTag (buf, &cur_pos, tag, len)) == INVALID)
				return;

			// now we found a tag, so we start loading parameters for the kind of tag

			if (RQ3_ParseBlock (tag_type, tag, &cur_pos, buf, len) == PARSING_ERROR)
				return;	
		}
	}

	G_Printf ("RQ3 config system: Finished loading the ini File\n");
	return;

	// Can't go here
	//G_Printf ( "RQ3 config system: Invalid init file\n" );
} 

int RQ3_GetTag ( char *buf, int *cur_pos, char *tag, int len){
	int	counter = 0, tag_type;

	while ((*(buf + *cur_pos) == ' ') || (*(buf + *cur_pos) == '\t'))
		(*cur_pos)++;
	while (*(buf + *cur_pos) != '>') {			
		tag[counter] = *(buf + *cur_pos);
		counter++;
		(*cur_pos)++;
	}

	(*cur_pos)++;
	tag[counter] = '\0';

	if ((tag_type = RQ3_CheckTag (tag)) == INVALID) {
		G_Printf ("RQ3 config system: Invalid tag %s\n", tag);
		return tag_type;
	}

	return tag_type;
}
 

// Parser of a block
int RQ3_ParseBlock (int tag_type, char *tag, int *cur_pos, char *buf, int len) {
	int	map_number = 0;
	char	map_to_go[2], word_buff[50], buff_map[50];
	char	cvar[40], value[80], model[200], *skin;
	char	map_now[50];

	G_Printf( "RQ3 config system: Processing block: <%s>\n", tag );
	
	if (tag_type == MAIN) {
		for (;;) {
			if (RQ3_GetCommand (buf, cur_pos, cvar, value, len) == TOKEN_TAG)
				return RQ3_CheckClosingTag (buf, cur_pos, tag_type, len);
			else {
				// process the cvar here	
				G_Printf ("RQ3 config system: Found cvar: %s with value %s\n", cvar, value);
				trap_Cvar_Set(cvar, value);
			}
		}
	} else if (tag_type == TEAM1 || tag_type == TEAM2) {
		if (RQ3_GetWord (buf, cur_pos, word_buff, len) != TOKEN_TAG) {
			G_Printf("RQ3 config system: found team name: %s\n", word_buff);
			if (tag_type == TEAM1)
				trap_Cvar_Set ("g_RQ3_team1name", word_buff);
			else 
				trap_Cvar_Set ("g_RQ3_team2name", word_buff);
		} else 
			return RQ3_CheckClosingTag (buf, cur_pos, tag_type, len);

		if (RQ3_GetWord (buf, cur_pos, word_buff, len) != TOKEN_TAG) {
			G_Printf ("RQ3 config system: found model/skin name: %s\n", word_buff);
			Com_sprintf (model, sizeof (model) , "%s", word_buff);
			skin = Q_strrchr(word_buff, '/');
			if (skin) {
				*skin++ = '\0';
			} else {
				G_Printf ("RQ3 config system: Found invalid skin\n");
				return PARSING_ERROR;
			}
			if (!RQ3_Validatemodel(word_buff)) {
				G_Printf ("RQ3 config system: The model is not a valid RQ3 model\n");
				return PARSING_ERROR;
			}
			if (tag_type == TEAM1) {
				trap_Cvar_Set ("g_RQ3_team1model", model);
			} else {
				trap_Cvar_Set ("g_RQ3_team2model", model);
			}
		} 

		if (RQ3_GetWord (buf, cur_pos, word_buff, len) == TOKEN_TAG)
			return RQ3_CheckClosingTag (buf, cur_pos, tag_type, len);
		else {
			G_Printf ("RQ3 config system: Found invalid string in block team\n");
			return PARSING_ERROR;
		}

	}
	else if (tag_type == ROTATION) {
		for (;;) {
			// Find a </rotation> or a <map> entrie
				if (RQ3_GetCommand (buf, cur_pos, cvar, value, len) == TOKEN_TAG) {
						(*cur_pos)++;
						if ((*(buf + *cur_pos) == '/')) {
								(*cur_pos)++;
								if (RQ3_GetTag (buf, cur_pos, tag, len) == ROTATION) { 	
										G_Printf ("RQ3 config system: Block <rotation> is finished\n");

										// finished rotation
										map_number--;
										Com_sprintf (buff_map, sizeof(buff_map), "map %s\n", map_now);
										if (map_number != g_RQ3_NextMapID.integer) {	
											g_RQ3_NextMapID.integer++;
											Com_sprintf (map_to_go, sizeof(map_to_go), "%d", g_RQ3_NextMapID.integer);
											trap_Cvar_Set ("g_RQ3_NextMapID", map_to_go); 
											G_Printf ("RQ3 config system: finished map processing. Next Map: %s\n", buff_map);
											trap_SendConsoleCommand (EXEC_APPEND, buff_map);
											return 1;
										} else {
											G_Printf ("RQ3 config system: finished map rotation.\n");
											g_RQ3_NextMapID.integer = 0;
											Com_sprintf (map_to_go, sizeof(map_to_go), "%d", g_RQ3_NextMapID.integer);
											trap_Cvar_Set ("g_RQ3_NextMapID", map_to_go);
											trap_SendConsoleCommand (EXEC_APPEND, buff_map);
											return 1;
										}
								} else {
										G_Printf ("RQ3 config system: Invalid block closing. Needs </rotation>, found </%s>\n", tag);
										return PARSING_ERROR;
								}
						}

				if (RQ3_GetTag (buf, cur_pos, tag, len) == MAP ) {
					G_Printf ("RQ3 config system: Prossessing block <map>\n");
					// Process the map block here
					// G_Printf ("RQ3 config system: g_RQ3_NextMapID is: %d and map_number is: %d \n", g_RQ3_NextMapID.integer, map_number);
					

					
					if (RQ3_GetWord (buf, cur_pos, word_buff, len) == TOKEN_TAG) 
						if (RQ3_CheckClosingTag (buf, cur_pos, MAP, len) == PARSING_OK) {
							map_number++;
							// G_Printf ("RQ3 config system: current map number is %d.\n", map_number); // ver esta merda
						} else 
							return PARSING_ERROR;
					else
					if (map_number != g_RQ3_NextMapID.integer) {
						// skipp everything and go to the next map
						while (*(buf + *cur_pos) != '<')
							(*cur_pos)++;
						
						if (map_number == (g_RQ3_NextMapID.integer + 1) || map_number == 0)
							trap_Cvar_Set( "g_RQ3_NextMap", word_buff);
			

						if (RQ3_CheckClosingTag (buf, cur_pos, MAP, len) == PARSING_OK) {
							map_number++;
							// G_Printf ("RQ3 config system: current map count is %d.\n", map_number);
						} else 
							return PARSING_ERROR;
					} else {
						// do something with the map name
						G_Printf ("RQ3 config system: map found: %s\n", word_buff);
						Com_sprintf (map_now, sizeof(map_now), "%s", word_buff);
						for (;;)	// Here process all cvar from the map definition
							if (RQ3_GetCommand (buf, cur_pos, cvar, value, len) == TOKEN_TAG)
								if (RQ3_CheckClosingTag (buf, cur_pos, MAP, len) == PARSING_OK) {
									map_number++;
									break;
								} else 
									return PARSING_ERROR; // return apropriate error code
							else {
							// process the cvar here	
								G_Printf ("RQ3 config system: Found cvar: %s with value %s\n", cvar, value);
								trap_Cvar_Set (cvar, value);
							}
					}
				}
			} else {
				G_Printf ("RQ3 config system: Parser error. Found invalid command betwen <rotation> </rotation>\n");
				return PARSING_ERROR;
			}
		}
	} 
	return 1;
}

int RQ3_GetWord (char *buf, int *cur_pos, char *word, int len) {
	int	count;

//	for (;; (*cur_pos)++) {
	for(;;){
		if (*(buf + *cur_pos) == '"') {
			count = 0;
			(*cur_pos)++;
			while (*(buf + *cur_pos) != '"') {
				word[count] = *(buf + *cur_pos);
				count++;
				(*cur_pos)++;
			}
			word[count] = '\0';
			(*cur_pos)++;
			break;
		}
		else if (*(buf + *cur_pos) == '<') // not considered word
			return TOKEN_TAG;
		else if ((*(buf + *cur_pos) == '\r') || (*(buf + *cur_pos) == ' ') || (*(buf + *cur_pos) == '\n') || (*(buf + *cur_pos) == '\t')){
			(*cur_pos)++;
			continue;
		}
		else 
			if ( *(buf + *cur_pos) == '#' || ( *(buf + *cur_pos) == '/' &&  *(buf + *cur_pos + 1) == '/')){
				RQ3_SkipLineComment( buf, cur_pos );
				(*cur_pos)++;
			}
		else {
			count = 0;
			while ((*(buf + *cur_pos) != ' ') && (*(buf + *cur_pos) != '\n') && (*(buf + *cur_pos) != '\t') && (*(buf + *cur_pos) != '\r')) {
				word[count] = *(buf + *cur_pos);
				count++;
				(*cur_pos)++;
			}
			word[count] = '\0';
			break;
		}
	}		
//	}
	return TOKEN_WORD;
}

int RQ3_GetCommand (char *buf, int *cur_pos, char *cvar, char *value, int len) {
	enum	were_stat { NONE, CVAR, VALUE, DONE };
	int	state = NONE;
	int	count;

//	for (;; (*cur_pos)++) {
	for (;;){
		if (*(buf + *cur_pos) == '<') // closing block
			return TOKEN_TAG; 
		else if ((*(buf + *cur_pos) == '\r') || (*(buf + *cur_pos) == ' ') || (*(buf + *cur_pos) == '\n') || (*(buf + *cur_pos) == '\t')){
			(*cur_pos)++;
			continue;		
		}
		else 
			if ( *(buf + *cur_pos) == '#' || ( *(buf + *cur_pos) == '/' &&  *(buf + *cur_pos + 1) == '/')){
				RQ3_SkipLineComment( buf, cur_pos );
				(*cur_pos)++;
			}
		else	
		if (state == NONE) {
			state = CVAR;
			count = 0;
			while ((*(buf + *cur_pos) != ' ') && (*(buf + *cur_pos) != '\n') && (*(buf + *cur_pos) != '\t') && (*(buf + *cur_pos) != '\r')) {
				cvar[count] = *(buf + *cur_pos);
				count++;
				(*cur_pos)++;
			}
			cvar[count] = '\0';
			(*cur_pos)++;
		} else if ((state == CVAR) && (*(buf + *cur_pos) == '"')) {
			state = VALUE;
			(*cur_pos)++;
			count = 0;
			while (*(buf + *cur_pos) != '"') {
				value[count] = *(buf + *cur_pos);
				count++;
				(*cur_pos)++;
			} 
			value[count] = '\0';
			(*cur_pos)++;
			return TOKEN_CVAR;
		} else if (state == CVAR) {
			state = VALUE;
			count = 0;
			while ((*(buf + *cur_pos) != ' ') && (*(buf + *cur_pos) != '\n') && (*(buf + *cur_pos) != '\t') && (*(buf + *cur_pos) != '\r')) {
				value[count] = *(buf + *cur_pos);
				count++;
				(*cur_pos)++;
			}
			value[count] = '\0';
			return TOKEN_CVAR;
		}
	}

//}
}	

char *known_tags[] = { "main", "rotation", "map", "cvars", "team1", "team2"};

int RQ3_CheckTag (char *tag) {
	#define NUM_TAGS 6
	int	i;

	for (i = 0; i < NUM_TAGS; i++)
		if (Q_stricmp ( known_tags[i], tag) == 0)
			return i;
	return INVALID;
}

int RQ3_CheckClosingTag (char *buf, int *cur_pos, int tag_type, int len) {
	char	tag[20];

	(*cur_pos)++;
	if (*(buf + *cur_pos) == '/') {
	
		(*cur_pos)++;
		if (RQ3_GetTag (buf, cur_pos, tag, len) == tag_type) {
			G_Printf ("RQ3 config system: Block <%s> is finished\n", known_tags[tag_type]);
			return PARSING_OK;
		} else {
			G_Printf ("RQ3 config system: Invalid block closing. Needs </%s>, found </%s>\n", known_tags[tag_type], tag);
			return PARSING_ERROR;
		}
	} else {
		G_Printf ("RQ3 config system: Found invalid tag in block <%s>\n", known_tags[tag_type]);
		return PARSING_ERROR;
	}
}


void RQ3_SkipLineComment( char *buf, int *cur_pos ){
	if ( *(buf + *cur_pos) == '/' )
		(*cur_pos) += 2;
		
	while ((*(buf + *cur_pos) != '\n'))
		(*cur_pos)++;
}
