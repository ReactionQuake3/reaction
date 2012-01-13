//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.153  2005/09/13 02:33:17  jbravo
// Adding new callvote gametype:map
//
// Revision 1.152  2005/09/07 20:27:41  makro
// Entity attachment trees
//
// Revision 1.151  2005/02/15 16:33:39  makro
// Tons of updates (entity tree attachment system, UI vectors)
//
// Revision 1.150  2004/01/26 21:26:08  makro
// no message
//
// Revision 1.149  2003/09/19 21:25:10  makro
// Flares (again!). Doors that open away from players.
//
// Revision 1.148  2003/09/18 23:28:44  jbravo
// Adding G_acos()
//
// Revision 1.147  2003/09/16 23:25:32  makro
// trigger_multiple - new spawnflag, 3 new keys
//
// Revision 1.146  2003/09/08 19:19:19  makro
// New code for respawning entities in TP
//
// Revision 1.145  2003/09/07 20:02:51  makro
// no message
//
// Revision 1.144  2003/08/24 22:45:17  makro
// Rotating func_trains
//
// Revision 1.143  2003/08/10 20:13:26  makro
// no message
//
// Revision 1.142  2003/07/30 16:05:46  makro
// no message
//
// Revision 1.141  2003/04/26 22:33:06  jbravo
// Wratted all calls to G_FreeEnt() to avoid crashing and provide debugging
//
// Revision 1.140  2003/04/19 17:41:26  jbravo
// Applied changes that where in 1.29h -> 1.32b gamecode.
//
// Revision 1.139  2003/04/19 15:27:31  jbravo
// Backing out of most of unlagged.  Only optimized prediction and smooth clients
// remains.
//
// Revision 1.138  2003/04/02 22:23:51  jbravo
// More replacements tweaks. Added zcam_stfu
//
// Revision 1.137  2003/03/22 20:29:26  jbravo
// wrapping linkent and unlinkent calls
//
// Revision 1.136  2003/03/10 07:07:58  jbravo
// Small unlagged fixes and voting delay added.
//
// Revision 1.135  2003/03/09 21:30:38  jbravo
// Adding unlagged.   Still needs work.
//
// Revision 1.134  2003/01/06 00:23:29  makro
// no message
//
// Revision 1.133  2003/01/05 22:36:50  makro
// Added "inactive" field for entities
// New "target_activate" entity
//
// Revision 1.132  2002/12/09 00:58:49  makro
// Items are now disabled from the weapon/item menus in teamplay
// games if they are banned from the server
//
// Revision 1.131  2002/11/17 20:14:15  jbravo
// Itembanning added
//
// Revision 1.130  2002/10/30 20:04:34  jbravo
// Adding helmet
//
// Revision 1.129  2002/10/29 01:34:52  jbravo
// Added g_RQ3_tdmMode (0 = TP style, 1 = DM style) including UI support.
//
// Revision 1.128  2002/10/26 18:29:17  jbravo
// Added allweap and allitem funtionality.
//
// Revision 1.127  2002/10/26 00:37:18  jbravo
// New multiple item code and added PB support to the UI
//
// Revision 1.126  2002/10/21 21:00:39  slicer
// New MM features and bug fixes
//
// Revision 1.125  2002/09/29 16:06:44  jbravo
// Work done at the HPWorld expo
//
// Revision 1.124  2002/09/08 19:47:03  niceass
// newb ctb message added
//
// Revision 1.123  2002/09/07 22:40:01  jbravo
// Added a scaling ctb respawn system.  Fixed a bug that allowed players to
// spawn before their team respawn with the team command.
//
// Revision 1.122  2002/09/02 02:21:41  niceass
// removed spherical head detection
//
// Revision 1.121  2002/08/30 00:00:16  makro
// Sky portals
//
// Revision 1.120  2002/08/28 23:10:06  jbravo
// Added cg_RQ3_SuicideLikeARealMan, timestamping to server logs and
// fixed stats for non-TP modes.
//
// Revision 1.119  2002/08/27 04:47:48  niceass
// ref say added
//
// Revision 1.118  2002/08/24 07:58:37  niceass
// moved sanitizestring to g_util
//
// Revision 1.117  2002/08/23 14:25:05  slicer
// Added a new Referee System with multiple ref support
//
// Revision 1.116  2002/08/21 07:00:07  jbravo
// Added CTB respawn queue and fixed game <-> cgame synch problem in CTB
//
// Revision 1.115  2002/08/21 03:36:04  niceass
// move of some vector functions outside of just game
//
// Revision 1.114  2002/08/21 02:56:08  blaze
// added spawnflags 8 for breakables, lets mappers turn off kicking
//
// Revision 1.113  2002/08/13 16:59:16  makro
// Fixed per-client callvote limit; added a new cvar - g_RQ3_maxClientVotes
//
// Revision 1.112  2002/08/07 03:35:57  jbravo
// Added dynamic radio and stopped all radio usage during lca
//
// Revision 1.111  2002/07/24 02:17:38  jbravo
// Added a respawn delay for CTB
//
// Revision 1.110  2002/07/16 04:07:53  niceass
// temporary hack solution for map rotation and ctb
//
// Revision 1.109  2002/07/11 04:30:01  niceass
// new func
//
// Revision 1.108  2002/07/09 03:24:30  niceass
// added alive function
//
// Revision 1.107  2002/07/07 18:36:13  jbravo
// Added an AntiIdle system. Can play insane sounds for idle players, drop them
// from teams or kick them.   Upped version to Beta 2.1
//
// Revision 1.106  2002/07/02 09:16:12  makro
// Added g_RQ3_version cvar for server browsers
//
// Revision 1.105  2002/06/24 05:51:51  jbravo
// CTF mode is now semi working
//
// Revision 1.104  2002/06/23 19:25:11  niceass
// bandage bug fix
//
// Revision 1.103  2002/06/23 19:12:17  slicer
// More Matchmode work
//
// Revision 1.102  2002/06/23 15:22:53  slicer
// Future 2.1 Matchmode Features - PART II
//
// Revision 1.101  2002/06/23 03:04:09  assimon
// Added suport for callvote map <map> and ref map <map>.
//
// Revision 1.100  2002/06/21 21:02:49  niceass
// worldspawn laserfog check
//
// Revision 1.99  2002/06/20 22:32:43  jbravo
// Added last damaged player and fixed a test2 model problem (atrimum my ass :)
// Changed g_RQ3_printOwnObits to g_RQ3_showOwnKills and it also controls $K
//
// Revision 1.98  2002/06/20 18:40:17  slicer
// Future 2.1 Matchmode Features - PART I
//
// Revision 1.97  2002/06/19 18:13:57  jbravo
// New TNG spawning system :)
//
// Revision 1.96  2002/06/18 09:22:16  niceass
// file exist function
//
// Revision 1.95  2002/06/16 20:11:41  niceass
// unused cvar removed
//
// Revision 1.94  2002/06/16 20:06:14  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.93  2002/06/16 17:38:00  jbravo
// Removed the MISSIONPACK ifdefs and missionpack only code.
//
// Revision 1.92  2002/06/13 17:01:30  slicer
// Radio Gender changes according to model gender
//
// Revision 1.91  2002/06/11 01:43:08  blaze
// g_rq3_cvarfile allows you to change which file holds the restricted cvars
//
// Revision 1.90  2002/06/09 23:18:49  assimon
// Add coments to the init parser. Added Message before intermition telling next map. New cvar: g_RQ3_NextMap
//
// Revision 1.89  2002/06/07 19:07:08  slicer
// removed cvars for teamXready, replaced by level.teamXready
//
// Revision 1.88  2002/06/05 23:39:40  blaze
// unbreakables work properly.  Though I already commited this.
//
// Revision 1.87  2002/06/03 05:24:31  niceass
// spectator changes
//
// Revision 1.86  2002/05/31 18:17:10  makro
// Bot stuff. Added a server command that prints a line to a client
// and everyone who is spectating him
//
// Revision 1.85  2002/05/31 17:32:11  jbravo
// HC gibs almost working :)
//
// Revision 1.84  2002/05/30 21:18:28  makro
// Bots should reload/bandage when roaming around
// Added "pathtarget" key to all the entities
//
// Revision 1.83  2002/05/28 01:17:01  jbravo
// More gib fixes.  g_RQ3_gib added
//
// Revision 1.82  2002/05/23 15:55:25  makro
// Elevators
//
// Revision 1.81  2002/05/19 21:27:28  blaze
// added force and buoyancy to breakables
//
// Revision 1.80  2002/05/12 00:07:47  slicer
// Added Normal Radio Flood Protection
//
// Revision 1.79  2002/05/11 16:22:38  slicer
// Added a Repeat Flood Protection to Radio
//
// Revision 1.78  2002/05/10 04:06:27  jbravo
// Added Ignore
//
// Revision 1.77  2002/05/09 20:58:30  jbravo
// New Obit system and a warning cleanup in zcam
//
// Revision 1.76  2002/05/05 15:51:16  slicer
// Captain and subs get saved on map_restarts ( moved to "sess" )
//
// Revision 1.75  2002/05/05 04:23:00  jbravo
// Some MM fixes and cleanups
//
// Revision 1.74  2002/05/05 01:20:50  jbravo
// Delay the lights sound 5 server frames.
//
// Revision 1.73  2002/04/30 11:20:12  jbravo
// Redid the teamcount cvars.
//
// Revision 1.72  2002/04/29 06:17:20  niceass
// small change to pressure system
//
// Revision 1.71  2002/04/28 11:03:46  slicer
// Added "teammodel" for Matchmode, Referee "pause" command
//
// Revision 1.70  2002/04/23 00:21:44  jbravo
// Cleanups of the new model code.  Removed the spectator bar for zcam modes.
//
// Revision 1.69  2002/04/22 16:43:34  blaze
// Hey look, breakables explode now!  :)
//
// Revision 1.68  2002/04/22 02:27:57  jbravo
// Dynamic model recognition
//
// Revision 1.67  2002/04/15 00:54:26  assimon
// Simple ini file parser that reads a ini configuration file and suports rotations.
//
// Revision 1.66  2002/04/07 12:49:10  slicer
// Added 'teamname' command for MM, and tweaked the cvar system.
//
// Revision 1.65  2002/04/03 09:26:47  jbravo
// New FF system. Warns and then finally kickbans teamwounders and
// teamkillers
//
// Revision 1.64  2002/04/03 03:13:16  blaze
// NEW BREAKABLE CODE - will break all old breakables(wont appear in maps)
//
// Revision 1.63  2002/04/02 00:56:18  jbravo
// Removed the zcam defines again and did some cleanups
//
// Revision 1.62  2002/04/01 22:23:14  slicer
// Added "weapon" command buffering | Solved Gren Mode Bug
//
// Revision 1.59  2002/03/26 11:32:05  jbravo
// Remember specstate between rounds.
//
// Revision 1.58  2002/03/26 10:32:52  jbravo
// Bye bye LCA lag
//
// Revision 1.57  2002/03/25 14:55:00  jbravo
// teamCount cvars for Makro
//
// Revision 1.56  2002/03/23 05:17:42  jbravo
// Major cleanup of game -> cgame communication with LCA vars.
//
// Revision 1.55  2002/03/18 13:32:53  jbravo
// Fixed the fraglines for sniper head kills and twekaed bandaging a bit for
// testing
//
// Revision 1.54  2002/03/17 03:35:29  jbravo
// More radio tewaks and cleanups.
//
// Revision 1.53  2002/03/17 00:40:23  jbravo
// Adding variable team names. g_RQ3_team1name and g_RQ3_team2name. Fixed
// Slicers fraglimit check.
//
// Revision 1.52  2002/03/14 23:54:12  jbravo
// Added a variable system from AQ. Works the same except it uses $ for %
//
// Revision 1.51  2002/03/14 02:24:39  jbravo
// Adding radio :)
//
// Revision 1.50  2002/03/07 01:38:36  assimon
// Changed Ref System. New cvar added - g_RQ3_RefID. Now referee is peserved even on map changes or map_restarts.
//
// Revision 1.49  2002/03/07 00:00:54  assimon
// Added a skeleton referee suport, with some functional commands (map_restart and kick)
//
// Revision 1.48  2002/02/24 18:12:19  jbravo
// Added a cvar to control sniper behavior g_RQ3_sniperup. Def 0. if set yo 1
// it makes players spawn with the sniper up.
//
// Revision 1.47  2002/02/10 21:21:23  slicer
// Saving persistant and other data on some events..
//
// Revision 1.46  2002/02/10 18:38:42  jbravo
// Added new SPECTATOR_ZCAM spec mode.
//
// Revision 1.45  2002/02/10 02:49:28  niceass
// re-added zcam #define
//
// Revision 1.44  2002/02/06 03:10:43  jbravo
// Fix the instant spectate on death and an attempt to fix the scores
//
// Revision 1.43  2002/02/05 23:41:27  slicer
// More on matchmode..
//
// Revision 1.42  2002/02/04 00:10:49  slicer
// Matchmode: Teams Ready/Not Ready goes by cvar MM_team1/2
//
// Revision 1.40  2002/02/01 01:00:36  slicer
// Adding Matchmode: just a few basics and files...
//
// Revision 1.38  2002/01/31 02:55:58  blaze
// some basic work with the trains/elevators
//
// Revision 1.37  2002/01/31 02:25:31  jbravo
// Adding limchasecam.
//
// Revision 1.36  2002/01/24 14:20:53  jbravo
// Adding func_explosive and a few new surfaceparms
//
// Revision 1.35  2002/01/14 01:20:45  niceass
// No more default 800 gravity on items
// Thrown knife+Glass fix - NiceAss
//
// Revision 1.34  2002/01/11 20:20:58  jbravo
// Adding TP to main branch
//
// Revision 1.33  2002/01/11 19:48:30  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.32  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
// g_local.h -- local definitions for game module

#include "../qcommon/q_shared.h"
#include "bg_public.h"
#include "g_public.h"

//==================================================================

// the "gameversion" client command will print this plus compile date
#define	GAMEVERSION		BASEGAME
#define BODY_QUEUE_SIZE		8

// JBravo: Max number of killed enemys to track
#define RQ3_MAXKILLS		5
#define MAX_TEAMS		2
#define MAX_SPAWN_POINTS	128

// Blaze: How long someone bleeds for
// Elder: This doesn't work the same as Q2 because clients and servers can
// run independent "clocks."  Normal servers send snapshots every 50ms
// (20 snapshots per second) so we double it from 10.
// Ideally, this number should match the server's sv_fps cvar value for those
// that run non-standard server frame rates.
#define BLEED_TIME			20
// Elder: Everyone knows you lose 6 health from the moment you start bandaging
// Let's enforce that in-code because it's sometimes 7 or even 8
// Elder: LOL it's 3, dumb Elder!
#define BLEED_BANDAGE			3
#define BLEED_BANDAGE_TIME		5400	// 27 x 2

// types of locations that can be hit
#define LOC_NOLOC			0	// non-location/world kill
#define LOC_HDAM			1	// head
#define LOC_CDAM			2	// chest
#define LOC_SDAM			3	// stomach
#define LOC_LDAM			4	// legs

#define INFINITE			1000000

#define	FRAMETIME			100	// msec
#define	CARNAGE_REWARD_TIME		3000
#define REWARD_SPRITE_TIME		2000

#define	INTERMISSION_DELAY_TIME		1000
#define	SP_INTERMISSION_DELAY_TIME	5000

// gentity->flags
#define	FL_GODMODE			0x00000010
#define	FL_NOTARGET			0x00000020
#define	FL_TEAMSLAVE			0x00000400	// not the first on the team
#define FL_NO_KNOCKBACK			0x00000800
#define FL_DROPPED_ITEM			0x00001000
#define FL_NO_BOTS			0x00002000	// spawn point not for bot use
#define FL_NO_HUMANS			0x00004000	// spawn point just for bots
#define FL_FORCE_GESTURE		0x00008000	// force gesture on client
//Elder: err - this looks funny... should it be 0x00010000 ?
//#define FL_THROWN_ITEM                0x00016000      // XRAY FMJ weapon throwing
#define FL_THROWN_ITEM			0x00010000	// XRAY FMJ weapon throwing
#define FL_RQ3_JUNKITEM			0x00020000	// Elder: the item we want to remove
//Elder: moved to bg_public.h
//#define FL_THROWN_KNIFE               0x00040000      // Elder: thrown knife special case

// movers are things like doors, plats, buttons, etc
typedef enum {
	MOVER_POS1,
	MOVER_POS2,
	MOVER_1TO2,
	MOVER_2TO1,
	// VALKYRIE: angle movements
	ROTATOR_POS1,
	ROTATOR_POS2,
	ROTATOR_1TO2,
	ROTATOR_2TO1
} moverState_t;

#define SP_PODIUM_MODEL			"models/mapobjects/podium/podium4.md3"
#define RQ3_RESPAWNTIME_DEFAULT		60000	// Elder: time for weapons to respawn - up to 60s
#define RQ3_CTF_RESPAWNTIME_DEFAULT	10000	// JBravo: time for weapons to respawn - up to 10s
#define SP_AUTOOPEN			4	// Elder: revert to Q3 behaviour
#define SP_DOORTOGGLE			8	// Elder: added to enable mover toggling
#define SP_LOOKATME			64		//Makro - door will only open if you look at it when
#define SP_OPENAWAY			128		//Makro - door will always open away from the player
									//pressing opendoor
#define MAXDOORTIME			100	// Elder: max time the opendoor key can stay open

//Makro - moved weapon/item banning flags to bg_public.h so that the UI
//		  can use them, too

//============================================================================

typedef struct gentity_s gentity_t;
typedef struct gclient_s gclient_t;

struct gentity_s {
	entityState_t s;	// communicated by server to clients
	entityShared_t r;	// shared by both the server system and game

	// DO NOT MODIFY ANYTHING ABOVE THIS, THE SERVER
	// EXPECTS THE FIELDS IN THAT ORDER!
	//================================

	struct gclient_s *client;	// NULL if not a client
	qboolean inuse;
	char *classname;	// set in QuakeEd
	int spawnflags;		// set in QuakeEd
	qboolean neverFree;	// if true, FreeEntity will only unlink
	// bodyque uses this
// JBravo: adding func_explosive
	int damage_radius;
	int mass;
	int tension;
	int bounce;
	int material;
	int size;
	int flags;		// FL_* variables
	char *model;
	char *model2;
	int freetime;		// level.time when the object was freed
	int eventTime;		// events will be cleared EVENT_VALID_MSEC after set
	qboolean freeAfterEvent;
	qboolean unlinkAfterEvent;
	qboolean physicsObject;	// if true, it can be pushed by movers and fall off edges
	// all game items are physicsObjects,
	float physicsBounce;	// 1.0 = continuous bounce, 0.0 = no bounce
	int clipmask;		// brushes with this content value will be collided against
	// when moving.  items and corpses do not collide against
	// players, for instance
	// movers
	moverState_t moverState;
	int soundPos1;
	int sound1to2;
	int sound2to1;
	int soundPos2;
	int soundLoop;
	//Makro - added
	int soundInactive;
	gentity_t *parent;
	gentity_t *nextTrain;
	gentity_t *prevTrain;
	vec3_t pos1, pos2;
	char *message;
	int timestamp;		// body queue sinking, etc
	float angle;		// set in editor, -1 = up, -2 = down
	char *target;
	char *targetname;
	char *team;
	char *targetShaderName;
	char *targetShaderNewName;
	gentity_t *target_ent;

	float speed;
	vec3_t movedir;

	int nextthink;
	void (*think) (gentity_t * self);
	void (*reached) (gentity_t * self);	// movers call this when hitting endpoint
	void (*blocked) (gentity_t * self, gentity_t * other);
	void (*touch) (gentity_t * self, gentity_t * other, trace_t * trace);
	void (*use) (gentity_t * self, gentity_t * other, gentity_t * activator);
	void (*pain) (gentity_t * self, gentity_t * attacker, int damage);
	void (*die) (gentity_t * self, gentity_t * inflictor, gentity_t * attacker, int damage, int mod);
	//Makro - called at the begining of the round in TP
	void (*reset) (gentity_t *self);
	qboolean noreset;	//Makro - if set to 1, this entity will not respawn in TP
	void (*onAttach) (gentity_t *self);
	void (*onDetach) (gentity_t *self);

	int pain_debounce_time;
	int fly_sound_debounce_time;	// wind tunnel
	int last_move_time;

	int health;
	//Blaze: hold the health so when we respawn it, the health is set properly
	int health_saved;
	//Blaze: holds if we can "chip" off peices
	qboolean chippable;
	//true if we cant break it
	qboolean unbreakable;
	//true if it's explosive
	qboolean explosive;
	//True if it's already been exploded
	qboolean exploded;
	//Bkaze: allow some entities to be shootable, but not kickable.
	qboolean unkickable;

	qboolean takedamage;
	int damage;
	int splashDamage;	// quad will increase this without increasing radius
	int splashRadius;
	int methodOfDeath;
	int splashMethodOfDeath;
	int count;
	gentity_t *chain;
	gentity_t *enemy;
	gentity_t *activator;
	gentity_t *teamchain;	// next entity in team
	gentity_t *teammaster;	// master of the team

	int watertype;
	int waterlevel;
	int noise_index;
	// timing variables
	float wait;
	float random;

	gitem_t *item;		// for bonus items
	float distance;		// VALKYRIE: for rotating door
	//Blaze: Holds the target set by a button
	char *pathtarget;
	//Makro - inactive entities
	char *activatename, *targetInactive;
	int inactive;
	//Makro - entity id strings
	char *alias;
	//Makro - moveparent
	char *moveParent;
	gentity_t *moveParent_ent;
	int moveParent_rank;
};

typedef enum {
	CON_DISCONNECTED,
	CON_CONNECTING,
	CON_CONNECTED
} clientConnected_t;

typedef enum {
	SPECTATOR_NOT,
	SPECTATOR_FREE,
	SPECTATOR_FOLLOW,
	SPECTATOR_ZCAM,
	SPECTATOR_CAMERA_FLIC,
	SPECTATOR_CAMERA_SWING,
	SPECTATOR_SCOREBOARD
} spectatorState_t;

typedef enum {
	TEAM_BEGIN,		// Beginning a team game, spawn at base
	TEAM_ACTIVE		// Now actively playing
} playerTeamStateState_t;

typedef struct {
	playerTeamStateState_t state;
	int location;
	int captures;
	int basedefense;
	int carrierdefense;
	int flagrecovery;
	int fragcarrier;
	int assists;
	float lasthurtcarrier;
	float lastreturnedflag;
	float flagsince;
	float lastfraggedcarrier;
} playerTeamState_t;

// the auto following clients don't follow a specific client
// number, but instead follow the first two active players
#define	FOLLOW_ACTIVE1	-1
#define	FOLLOW_ACTIVE2	-2

// JBravo: for ignore
#define MAXIGNORE	11
typedef gentity_t *ignorelist_t[MAXIGNORE];

// client data that stays across multiple levels or tournament restarts
// this is achieved by writing all the data to cvar strings at game shutdown
// time and reading them back at connection time.  Anything added here
// MUST be dealt with in G_InitSessionData() / G_ReadSessionData() / G_WriteSessionData()
typedef struct {
	//Slicer Matchmode
	qboolean refHear;
	int refReady;
	int referee;
	team_t captain;
	team_t sub;
	team_t sessionTeam;
	team_t savedTeam;	// JBravo: Used to hold the real team status of a player.
	int spectatorTime;	// for determining next-in-line to play
	spectatorState_t spectatorState;
	int spectatorClient;	// for chasecam and follow mode
	int wins, losses;	// tournament stats
	qboolean teamLeader;	// true when this client is a team leader
	gentity_t *spawnPoint;	// JBravo: This players spawnpoint
	qboolean teamSpawn;	// JBravo: This player is being spawned with his team.
	int ignore_time;	// JBravo: to avoid ignore flooding
	ignorelist_t ignorelist;	// JBravo: This players ignore list.
} clientSession_t;

//
#define MAX_NETNAME		36
#define	MAX_VOTE_COUNT		3

// client data that stays across multiple respawns, but is cleared
// on each level change or team change at ClientBegin()
typedef struct {
	clientConnected_t connected;
	// aasimon: No Need for this here, using a cvar to record the clientnumber of referee, so that map_restarts dont change 
	// the referee
	// qboolean     referee;

	usercmd_t cmd;		// we would lose angles if not persistant
	qboolean localClient;	// true if "ip" info key is "localhost"
	qboolean initialSpawn;	// the first spawn should be at a cool location
	qboolean predictItemPickup;	// based on cg_predictItems userinfo
	qboolean pmoveFixed;	//
	char netname[MAX_NETNAME];
	int maxHealth;		// for handicapping
	int enterTime;		// level.time the client entered the game
	playerTeamState_t teamState;	// status in teamplay games
	int voteCount;		// to prevent people from constantly calling votes
	int teamVoteCount;	// to prevent people from constantly calling votes
	qboolean teamInfo;	// send team overlay updates?
	qboolean hadUniqueWeapon[MAX_WEAPONS];	//Elder: for "ammo" in last gun

	int sayTime;		// Elder: say validation stuff
	int sayCount;
	int sayWarnings;
	int sayBans;
	int sayMuteTime;
	qboolean sayModerated;	// so warnings are not repeated for multi-line, same-frame messages
	int records[REC_NUM_RECORDS];	// Elder: for our statistics tracking
// JBravo: unlagged
	int delag;
} clientPersistant_t;

struct camera_s;

// Elder: spam prevention defaults
/*
#define SAY_MAX_NUMBER		6
#define SAY_MAX_WARNINGS	3
#define SAY_PERIOD_TIME		3			// Elder: in seconds
#define SAY_WARNING_TIME	15
#define SAY_BAN_TIME		60			// Technically should drop client
*/
#define SAY_MAX_NUMBER		"6"
#define SAY_MAX_WARNINGS	"3"
#define SAY_PERIOD_TIME		"3"	// Elder: in seconds
#define SAY_WARNING_TIME	"15"
#define SAY_BAN_TIME		"60"	// Technically should drop client
typedef enum {
	SAY_BAN,
	SAY_WARNING,
	SAY_OK,

	SAY_TOTAL
} sayValidations_t;

// this structure is cleared on each ClientSpawn(),
// except for 'client->pers' and 'client->sess'
struct gclient_s {
	// ps MUST be the first element, because the server expects it
	playerState_t ps;	// communicated by server to clients
	// the rest of the structure is private to game
	clientPersistant_t pers;
	clientSession_t sess;
	qboolean readyToExit;	// wishes to leave the intermission
	qboolean noclip;
//	int lastCmdTime;	// level.time of last usercmd_t, for EF_CONNECTION
	// we can't just use pers.lastCommand.time, because
	// of the g_sycronousclients case
	int buttons;
	int oldbuttons;
	int latched_buttons;
	vec3_t oldOrigin;
	// sum up damage over an entire frame, so
	// shotgun blasts give a single big kick
	int damage_armor;	// damage absorbed by armor
	int damage_blood;	// damage taken out of health
	int damage_knockback;	// impact damage
	vec3_t damage_from;	// origin for vector calculation
	qboolean damage_fromWorld;	// if true, don't use the damage_from vector
	//qboolean              damage_vest;            // Elder: if true, play the vest-hit sound
	int accurateCount;	// for "impressive" reward sound
	int accuracy_shots;	// total number of shots
	int accuracy_hits;	// total number of hits
	gentity_t *lastkilled_client[5];	// JBravo: last 5 clients that this client killed
	char last_damaged_players[MAX_STRING_CHARS];	// JBravo: last client this one damaged.
	int num_kills;		// JBravo: Number of killed players in TP.
	int lasthurt_client;	// last client that damaged this client
	int lasthurt_mod;	// type of damage the client did
	//Slicer
	int weapon_attempts;
	qboolean weapon_after_bandage_warned;
// Begin Duffman
	int lasthurt_location;	// Where the client was hit.
// End Duffman
	// timers
	int respawnTime;	// can respawn when time > this, force after g_forcerespwan
	int inactivityTime;	// kick players when time > this
	qboolean inactivityWarning;	// qtrue if the five seoond warning has been given
	int rewardTime;		// clear the EF_AWARD_IMPRESSIVE, etc when time > this
	int airOutTime;
	int lastKillTime;	// for multiple kill rewards
	qboolean fireHeld;	// used for hook
	gentity_t *hook;	// grapple hook if out
	int switchTeamTime;	// time the player switched teams
// Begin Duffman
	int numClips[MAX_WEAPONS];	// Number of clips each weapon has
// End Duffman
	int weaponCount[WP_NUM_WEAPONS];	// Elder: for duplicate unique weapon tracking
	int openDoor;		//Blaze: used to hold if someone has hit opendoor key
	int openDoorTime;
	// timeResidual is used to handle events that happen every second
	// like health / armor countdowns and regeneration
	int timeResidual;
	//Elder: C3A laser tutorial
	gentity_t *lasersight;	// lasersight OR flashlight if in use
	// JBravo: sniperheadshots
	qboolean noHead;
	// Bleeding server-only cvars
	int bleeding;		// Blaze: remaining points to bleed away
	int bleed_remain;	// Blaze: How much left to bleed
	int bleedloc;		// Blaze: Where are we bleeding
	vec3_t bleedloc_offset;	// Blaze: location of bleeding (from origin)
	int bleed_delay;	// Elder: time for next spurt of blood
	vec3_t bleednorm;
	//qboolean              isBleeding;             // Blaze: is client bleeding
//      int                     legDamage;              // Blaze: Client has leg damage - holds number of hits too
	int bleedtick;		// Blaze: Holds # of seconds till bleeding stops.
	int headShotTime;	// Elder: got headshot?
	//Elder: server only needs to know for sniper spread - ARGH
//      int                     zoomed;                 // Hawkins (SSG zoom)
	//qboolean              semi;                   // hawkins (semiauto mode for m4, mp5, pistol)
	int shots;		// Blaze: Number of shots fired so far with this weapon
	int weaponfireNextTime;	// for akimbos
	int lastzoom;		// Elder: save last zoom state when firing
	// These are now obsolete with the new reload code
	int fastReloads;	// Elder: for queuing M3/SSG reloads
	int lastReloadTime;	// Elder: for queuing M3/SSG reloads
	int reloadAttempts;	// Elder: for queuing M3/SSG reloads
	int reloadStage;	// Elder: 0, 1, 2 for sound queuing - move to stats?
	int consecutiveShots;	// Elder: for M4 ride-up/kick
	int uniqueWeapons;	// Elder: formerly a stat, now just a server var
	int uniqueItems;
	int killStreak;		// Elder: replaces the old STAT_STREAK
	qboolean kevlarHit;	// Elder: kevlar hit -- FIXME: poor implementation
	int knife_sound;	// NiceAss: What did the player hit while slashing?

	char *areabits;
	struct camera_s *camera;
// JBravo adding TP stuff
	int specMode;
	int teamplayWeapon;
	int teamplayItem;
	int radioGender;
	int radioSetMale;
	int radioSetFemale;
	int SuicideLikeARealMan;
	int zcam_stfu;
	qboolean radioOff;
	int team_wounds;
	int team_wounds_before;
	int ff_warning;
	int team_kills;
	int idletime;
	int savedPSweapon;
	int savedSTAT;
	qboolean gibbed;

	//Slicer Flood protect:

	float rd_mute;		//Time to be muted
	int rd_Count;		//Counter for the last msgs in "xx" secs allowed
	float rd_time;		//Time for the first radio message of the ones to follow

	int rd_lastRadio;	//Code of the last radio used
	int rd_repCount;	//Counter for the number of repeated radio msgs
	float rd_repTime;	//The time for the last repeated radio msg
// JBravo: time of death for delayed CTB respawns
	int time_of_death;
	int flagMessageTime;// NiceAss: Newb message for pistol/knife w/ enemy case
	int lastUpdateFrame;
};

// JBravo: for model loading
#define MAXMODELS	64
#define MAXMODELLEN	100

typedef struct legitmodel {
	char name[MAXMODELLEN];
	vec3_t team1color;
	vec3_t team2color;
	int gender;
} legitmodel_t;

// Begin Duffman
int G_LocationDamage(vec3_t point, gentity_t * targ, gentity_t * attacker, int take);
void Cmd_Reload(gentity_t * ent);	// reloads the current weapon

// Elder: removed - prototype in bg_public.h
//   int ClipAmountForWeapon( int w );  // returns the maximum ammo for the current weapon
// End Duffman

//
// this structure is cleared as each map is entered
//
#define	MAX_SPAWN_VARS		64
#define	MAX_SPAWN_VARS_CHARS	4096

typedef struct {
	struct gclient_s *clients;	// [maxclients]
	struct gentity_s *gentities;
	int gentitySize;
	int num_entities;	// current number, <= MAX_GENTITIES
	int warmupTime;		// restart match at this time
	fileHandle_t logFile;
	// store latched cvars here that we want to get at often
	int maxclients;
	int framenum;
	int time;		// in msec
	int previousTime;	// so movers can back up when blocked
	int startTime;		// level.time the map was started
	int teamScores[TEAM_NUM_TEAMS];
	int lastTeamLocationTime;	// last time of client team location update
	qboolean newSession;	// don't use any old session data, because
	// we changed gametype
	qboolean restarted;	// waiting for a map_restart to fire
	int numConnectedClients;
	int numNonSpectatorClients;	// includes connecting clients
	int numPlayingClients;	// connected, non-spectators
	int sortedClients[MAX_CLIENTS];	// sorted by score
	int follow1, follow2;	// clientNums for auto-follow spectators
	int snd_fry;		// sound index for standing in lava
	int warmupModificationCount;	// for detecting if g_warmup is changed
	// voting state	
	char voteString[MAX_STRING_CHARS];
	char voteDisplayString[MAX_STRING_CHARS];
	// vote extras
	char voteMap[MAX_STRING_CHARS];
	int voteGametype;	// JBravo: For callvote game
	int voteTime;		// level.time vote was called
	int voteExecuteTime;	// time the vote is executed
	int voteYes;
	int voteNo;
	int numVotingClients;	// set by CalculateRanks

	// team voting state
	char teamVoteString[2][MAX_STRING_CHARS];
	int teamVoteTime[2];	// level.time vote was called
	int teamVoteYes[2];
	int teamVoteNo[2];
	int numteamVotingClients[2];	// set by CalculateRanks

	// spawn variables
	qboolean spawning;	// the G_Spawn*() functions are valid
	int numSpawnVars;
	char *spawnVars[MAX_SPAWN_VARS][2];	// key / value pairs
	int numSpawnVarChars;
	char spawnVarChars[MAX_SPAWN_VARS_CHARS];

	// intermission state
	int intermissionQueued;	// intermission was qualified, but
	// wait INTERMISSION_DELAY_TIME before
	// actually going there so the last
	// frag can be watched.  Disable future
	// kills during this delay
	int intermissiontime;	// time the intermission was started
	char *changemap;
	qboolean readyToExit;	// at least one client wants to exit
	int exitTime;
	vec3_t intermission_origin;	// also used for spectator spawns
	vec3_t intermission_angle;

	qboolean locationLinked;	// target_locations get linked
	gentity_t *locationHead;	// head of the location list
	int bodyQueIndex;	// dead bodies
	gentity_t *bodyQue[BODY_QUEUE_SIZE];
//      Slicer: Matchmode
	float matchTime;
	int refStatus;
	int refAmmount;
	qboolean team1ready;
	qboolean team2ready;
	qboolean inGame;
	qboolean paused;
	qboolean settingsLocked;
// JBravo adding TP
	int lights_camera_action;
	qboolean team_round_going;
	int holding_on_tie_check;
	int team_round_countdown;
	qboolean team_game_going;
	int rulecheckfrequency;
	int current_round_length;
	qboolean spawnPointsLocated;
	gentity_t *team1spawnpoint;
	gentity_t *team2spawnpoint;
	vec3_t team1spawn_origin;
	vec3_t team1spawn_angles;
	vec3_t team2spawn_origin;
	vec3_t team2spawn_angles;
	int fps;
	int lights_delay;
// JBravo: for CTB
	int team1respawn;
	int team2respawn;
	int ctb_respawndelay;
	//Slicer: 
	int team1gender;
	int team2gender;

	// Freud: spawning system
	int randteam;
	int num_used_farteamplay_spawns[MAX_TEAMS];
	int num_potential_spawns[MAX_TEAMS];
	gentity_t *teamplay_spawns[MAX_TEAMS];
	qboolean teams_assigned[MAX_TEAMS];
	gentity_t *potential_spawns[MAX_TEAMS][MAX_SPAWN_POINTS];
	gentity_t *used_farteamplay_spawns[MAX_TEAMS][MAX_SPAWN_POINTS];
	//Makro - moveParent stuff
	int num_moveParents;
	int num_attachedEnts;
	//Makro - custom death messages for trigger_hurt entities
	int numCustomDeathMsg;
	char *customDeathMsg[MAX_CUSTOM_DEATH_MSG];
} level_locals_t;

//
// rxn_game.c
//

void CheckBleeding(gentity_t * targ);
void StartBandage(gentity_t * ent);

int ThrowWeapon(gentity_t * ent, qboolean forceThrow);
void ThrowItem(gentity_t * ent);
gentity_t *dropWeapon(gentity_t * ent, gitem_t * item, float angle, int xr_flags);	// XRAY FMJ

//Blaze Reaction knife stuff
//Elder: commented out - unused?
//void Rxn_SpawnKnife( gentity_t *e);
//
// g_spawn.c
//
qboolean G_SpawnString(const char *key, const char *defaultString, char **out);

// spawn string returns a temporary reference, you must CopyString() if you want to keep it
qboolean G_SpawnFloat(const char *key, const char *defaultString, float *out);
qboolean G_SpawnInt(const char *key, const char *defaultString, int *out);
qboolean G_SpawnVector(const char *key, const char *defaultString, float *out);
void G_SpawnEntitiesFromString(void);
char *G_NewString(const char *string);
//Makro - bot hack
void G_BotOnlyItem(gentity_t *ent);

//
// g_cmds.c
//
char *ConcatArgs(int start);
void Cmd_Score_f(gentity_t * ent);
void StopFollowing(gentity_t * ent);
void BroadcastTeamChange(gclient_t * client, int oldTeam);
void SetTeam(gentity_t * ent, char *s);
void Cmd_FollowCycle_f(gentity_t * ent, int dir);
void Cmd_Unzoom(gentity_t * ent);
void Cmd_OpenDoor(gentity_t * ent);
void Cmd_Weapon(gentity_t * ent);
void G_Say(gentity_t * ent, gentity_t * target, int mode, const char *chatText);

//Elder: C3A laser tutorial
void Laser_Gen(gentity_t * ent, qboolean enabled);
void Laser_Think(gentity_t * self);

//Elder: anti-spam stuff
int RQ3_ValidateSay(gentity_t * ent);

//Elder: commented out for Homer
//void toggleSemi(gentity_t *ent);
//Makro - sends a command to a client and all the ones spectating him
void G_SendClientSpec(gentity_t * ent, const char *msg);

//
// g_items.c
//
void G_CheckTeamItems(void);
void G_RunItem(gentity_t * ent);
void RespawnItem(gentity_t * ent);

void UseHoldableItem(gentity_t * ent);
void PrecacheItem(gitem_t * it);
gentity_t *Drop_Item(gentity_t * ent, gitem_t * item, float angle);
gentity_t *LaunchItem(gitem_t * item, vec3_t origin, vec3_t velocity, int xrflags);
void SetRespawn(gentity_t * ent, float delay);
void G_SpawnItem(gentity_t * ent, gitem_t * item);
void FinishSpawningItem(gentity_t * ent);
void Think_Weapon(gentity_t * ent);
int ArmorIndex(gentity_t * ent);

//Elder: added bandolier factor
void Add_Ammo(gentity_t * ent, int weapon, int count, int bandolierfactor);
void Touch_Item(gentity_t * ent, gentity_t * other, trace_t * trace);
//Makro - added
void G_ResetItem(gentity_t *ent);

void ClearRegisteredItems(void);
void RegisterItem(gitem_t * item);
void SaveRegisteredItems(void);

//Elder: added
void RQ3_DroppedItemThink(gentity_t * ent);
void RQ3_DroppedWeaponThink(gentity_t * ent);
void RQ3_ResetWeapon(int weapon);
void RQ3_ResetItem(int itemTag);

//
// g_utils.c
//
int G_ModelIndex(char *name);
int G_SoundIndex(char *name);
void G_TeamCommand(team_t team, char *cmd);
void G_KillBox(gentity_t * ent);
gentity_t *G_Find(gentity_t * from, int fieldofs, const char *match);
int G_PlayerAlive(gentity_t *ent);
void G_DebugSaveData(char *Data);
qboolean G_FileSearch(char *Filename, char *Text);
void SanitizeString(char *in, char *out);
double G_acos(double x);

//Makro - added
gentity_t *G_Find2(gentity_t * from, int fieldofs, const char *match, int fieldofs2, const char *match2);
qboolean MatchesId(gentity_t *ent, const char *ids);

gentity_t *G_PickTarget(char *targetname);
void G_UseEntities(gentity_t * ent, char *target, gentity_t * activator);
void G_UseTargets(gentity_t * ent, gentity_t * activator);
void G_SetMovedir(vec3_t angles, vec3_t movedir);

void G_InitGentity(gentity_t * e);
gentity_t *G_Spawn(void);
gentity_t *G_TempEntity(vec3_t origin, int event);

//Elder: added
gentity_t *G_TempEntity2(vec3_t origin, int event, int eParm);
void G_Sound(gentity_t * ent, int channel, int soundIndex);
void G_FreeEntity(gentity_t * e);

//Elder: added
void RQ3_SaveZoomLevel(gentity_t * ent);
int RQ3_isZoomed(gentity_t * ent);

qboolean G_EntitiesFree(void);

void G_TouchTriggers(gentity_t * ent);
void G_TouchSolids(gentity_t * ent);

//float *tv(float x, float y, float z);
char *vtos(const vec3_t v);

float vectoyaw(const vec3_t vec);

void G_AddPredictableEvent(gentity_t * ent, int event, int eventParm);
void G_AddEvent(gentity_t * ent, int event, int eventParm);
void G_SetOrigin(gentity_t * ent, vec3_t origin);
void AddRemap(const char *oldShader, const char *newShader, float timeOffset);
const char *BuildShaderStateConfig( void );

//
// g_combat.c
//
qboolean CanDamage(gentity_t * targ, vec3_t origin);
void G_Damage(gentity_t * targ, gentity_t * inflictor, gentity_t * attacker, vec3_t dir, vec3_t point, int damage,
	      int dflags, int mod);
qboolean G_RadiusDamage(vec3_t origin, gentity_t * attacker, float damage, float radius, gentity_t * ignore, int mod);
int G_InvulnerabilityEffect(gentity_t * targ, vec3_t dir, vec3_t point, vec3_t impactpoint, vec3_t bouncedir);
void body_die(gentity_t * self, gentity_t * inflictor, gentity_t * attacker, int damage, int meansOfDeath);
void TossClientItems(gentity_t * self);
void TossClientCubes(gentity_t * self);

// damage flags
#define DAMAGE_RADIUS			0x00000001	// damage was indirect
#define DAMAGE_NO_ARMOR			0x00000002	// armour does not protect from this damage
#define DAMAGE_NO_KNOCKBACK			0x00000004	// do not affect velocity, just view angles
#define DAMAGE_NO_PROTECTION		0x00000008	// armor, shields, invulnerability, and godmode have no effect
//Elder: Changed from 0x00000016 to 0x00000020
#define DAMAGE_NO_LOCATIONAL		0x00000020	// Generic damage (shotguns, grenades, kicks)

//
// g_missile.c
//
void G_RunMissile(gentity_t * ent);

gentity_t *fire_knife(gentity_t * self, vec3_t start, vec3_t aimdir);

//Blaze: Dont need these functions
//gentity_t *fire_plasma (gentity_t *self, vec3_t start, vec3_t aimdir);
gentity_t *fire_grenade(gentity_t * self, vec3_t start, vec3_t aimdir);

//gentity_t *fire_rocket (gentity_t *self, vec3_t start, vec3_t dir);
//gentity_t *fire_bfg (gentity_t *self, vec3_t start, vec3_t dir);
//gentity_t *fire_grapple (gentity_t *self, vec3_t start, vec3_t dir);

//
// g_mover.c
//
void G_RunMover(gentity_t * ent);
void Touch_DoorTrigger(gentity_t * ent, gentity_t * other, trace_t * trace);

//void Touch_DoorTriggerSpectator( gentity_t *ent, gentity_t *other, trace_t *trace ); // NiceAss: Added

//
// g_trigger.c
//
void trigger_teleporter_touch(gentity_t * self, gentity_t * other, trace_t * trace);

//
// g_misc.c
//
void TeleportPlayer(gentity_t * player, vec3_t origin, vec3_t angles);
void G_BreakGlass(gentity_t * ent, gentity_t * inflictor, gentity_t * attacker, vec3_t point, int mod, int damage);	//Blaze: Breakable glass
//Makro - not needed
//void G_RunDlight(gentity_t * ent);	// Elder: dlight running
void G_EvaluateTrajectory(const trajectory_t * tr, int atTime, vec3_t result);
void G_EvaluateTrajectoryDelta(const trajectory_t * tr, int atTime, vec3_t result);
void G_EvaluateTrajectoryEx(gentity_t *ent, int atTime, vec3_t origin, vec3_t angles);
void G_GravityChange(void);
void G_CreatePressure(vec3_t origin, vec3_t normal, gentity_t * ent);
qboolean G_FileExists(char *filename);

//
// g_weapon.c
//
qboolean LogAccuracyHit(gentity_t * target, gentity_t * attacker);
void CalcMuzzlePoint(gentity_t * ent, vec3_t forward, vec3_t right, vec3_t up, vec3_t muzzlePoint);
void SnapVectorTowards(vec3_t v, vec3_t to);
qboolean CheckGauntletAttack(gentity_t * ent);

// JBravo: unlagged - g_unlagged.c
/*void G_ResetHistory(gentity_t *ent);
void G_StoreHistory(gentity_t *ent);
void G_TimeShiftAllClients(int time, gentity_t *skip);
void G_UnTimeShiftAllClients(gentity_t *skip);
void G_DoTimeShiftFor(gentity_t *ent);
void G_UndoTimeShiftFor(gentity_t *ent);
void G_UnTimeShiftClient(gentity_t *client); */
void G_PredictPlayerMove(gentity_t *ent, float frametime);

//void Knife_Touch (gentity_t *ent, gentity_t *other,trace_t *trace);
//Blaze: No need for these because no gauntlet
//void Weapon_HookFree (gentity_t *ent);
//void Weapon_HookThink (gentity_t *ent);
//Elder: for shotgun damage reports
void RQ3_InitShotgunDamageReport(void);
void RQ3_ProduceShotgunDamageReport(gentity_t * self);
qboolean JumpKick(gentity_t * ent);
qboolean DoorKick(trace_t * trIn, gentity_t * ent, vec3_t origin, vec3_t forward);
extern int tookShellHit[MAX_CLIENTS];

//
// g_client.c
//
team_t TeamCount(int ignoreClientNum, int team);
int TeamLeader(int team);
team_t PickTeam(int ignoreClientNum);
void SetClientViewAngle(gentity_t * ent, vec3_t angle);
gentity_t *SelectSpawnPoint(vec3_t avoidPoint, vec3_t origin, vec3_t angles);

//Elder: added because I use it in g_main.c and g_items.c for item spawning
gentity_t *SelectRandomDeathmatchSpawnPoint(void);

// JBravo: need this for teamspawning
gentity_t *SelectRandomFurthestSpawnPoint(vec3_t avoidPoint, vec3_t origin, vec3_t angles);
gentity_t *SelectInitialSpawnPoint(vec3_t origin, vec3_t angles);
void CopyToBodyQue(gentity_t * ent);
void respawn(gentity_t * ent);
void BeginIntermission(void);
void InitClientPersistant(gclient_t * client);
void InitClientResp(gclient_t * client);
void InitBodyQue(void);
void ClientSpawn(gentity_t * ent);

//Blaze: for the cheat vars stuff
int G_SendCheatVars(int);

//Blaze: for the breakable stuff
int G_SendBreakableInfo(int);
void player_die(gentity_t * self, gentity_t * inflictor, gentity_t * attacker, int damage, int mod);
void AddScore(gentity_t * ent, vec3_t origin, int score);
void CalculateRanks(void);
qboolean SpotWouldTelefrag(gentity_t * spot);

//
// g_svcmds.c
//
qboolean ConsoleCommand(void);
void G_ProcessIPBans(void);
qboolean G_FilterPacket(char *from);

//
// g_weapon.c
//
void FireWeapon(gentity_t * ent);
void ReloadWeapon(gentity_t * ent, int stage);	// Elder: added

//
// p_hud.c
//
void MoveClientToIntermission(gentity_t * client);
void G_SetStats(gentity_t * ent);
void DeathmatchScoreboardMessage(gentity_t * client);

//
// g_cmds.c
//

//
// g_pweapon.c
//

//
// g_main.c
//
void FindIntermissionPoint(void);
void SetLeader(int team, int client);
void CheckTeamLeader(int team);
void G_RunThink(gentity_t * ent);
void QDECL G_LogPrintf( const char *fmt, ... ) __attribute__ ((format (printf, 1, 2)));
void SendScoreboardMessageToAllClients(void);
void QDECL G_Printf( const char *fmt, ... ) __attribute__ ((format (printf, 1, 2)));
void QDECL G_Error( const char *fmt, ... ) __attribute__ ((noreturn, format (printf, 1, 2)));
//void QDECL G_Error( const char *fmt, ... ) __attribute__ ((noreturn, format (printf, 1, 2)));
//void QDECL G_Error( const char *fmt, ... ) __attribute__ ((format (printf, 1, 2)));

//Elder: added
void RQ3_StartUniqueItems(void);

// aasimon: init stuff
void RQ3_ReadInitFile(void);
void RQ3_ParseBuffer(char *buf, int len);
int RQ3_GetTag(char *buf, int *cur_pos, char *tag, int len);
int RQ3_CheckTag(char *tag);
int RQ3_ParseBlock(int tag_type, char *tag, int *cur_pos, char *buf, int len);
int RQ3_GetCommand(char *buf, int *cur_pos, char *cvar, char *value, int len);
int RQ3_GetWord(char *buf, int *cur_pos, char *word, int len);
int RQ3_CheckClosingTag(char *buf, int *cur_pos, int tag_type, int len);
void RQ3_SkipLineComment(char *buf, int *cur_pos);

//
// g_client.c
//
char *ClientConnect(int clientNum, qboolean firstTime, qboolean isBot);
void ClientUserinfoChanged(int clientNum);
void ClientDisconnect(int clientNum);
void ClientBegin(int clientNum);
void ClientCommand(int clientNum);
typedef struct {
	char name[80];
	int jump;
	int velocity;
} breakable_t;
extern breakable_t rq3_breakables[RQ3_MAX_BREAKABLES];

//
// g_active.c
//
void ClientThink(int clientNum);
void ClientEndFrame(gentity_t * ent);
void G_RunClient(gentity_t * ent);

//
// g_team.c
//
qboolean OnSameTeam(gentity_t * ent1, gentity_t * ent2);
void Team_CheckDroppedItem(gentity_t * dropped);
qboolean CheckObeliskAttack(gentity_t * obelisk, gentity_t * attacker);

//
// g_mem.c
//
void *G_Alloc(int size);
void G_InitMemory(void);
void Svcmd_GameMem_f(void);

//
// g_session.c
//
void G_ReadSessionData(gclient_t * client);
void G_InitSessionData(gclient_t * client, char *userinfo);

void G_InitWorldSession(void);
void G_WriteSessionData(void);

//
// g_arenas.c
//
void UpdateTournamentInfo(void);
void SpawnModelsOnVictoryPads(void);
void Svcmd_AbortPodium_f(void);

//
// g_bot.c
//
void G_InitBots(qboolean restart);
char *G_GetBotInfoByNumber(int num);
char *G_GetBotInfoByName(const char *name);
void G_CheckBotSpawn(void);
void G_RemoveQueuedBotBegin(int clientNum);
qboolean G_BotConnect(int clientNum, qboolean restart);
void Svcmd_AddBot_f(void);
void Svcmd_BotList_f(void);
void BotInterbreedEndMatch(void);

// ai_main.c
#define MAX_FILEPATH			144

//bot settings
typedef struct bot_settings_s {
	char characterfile[MAX_FILEPATH];
	float skill;
	char team[MAX_FILEPATH];
} bot_settings_t;

int BotAISetup(int restart);
int BotAIShutdown(int restart);
int BotAILoadMap(int restart);
int BotAISetupClient(int client, struct bot_settings_s *settings, qboolean restart);
int BotAIShutdownClient(int client, qboolean restart);
int BotAIStartFrame(int time);
void BotTestAAS(vec3_t origin);

#include "g_team.h"		// teamplay specific stuff

// JBravo: Functions from g_teamplay.c
#include "g_teamplay.h"

extern level_locals_t level;
extern gentity_t g_entities[MAX_GENTITIES];
//Makro - moveparent tree
extern gentity_t *g_parentOrder[MAX_GENTITIES];

#define FOFS(x) ((size_t)&(((gentity_t *)0)->x))

extern vmCvar_t g_gametype;
extern vmCvar_t g_dedicated;
extern vmCvar_t g_cheats;
extern vmCvar_t g_maxclients;	// allow this many total, including spectators
extern vmCvar_t g_maxGameClients;	// allow this many active
extern vmCvar_t g_restarted;

extern vmCvar_t g_dmflags;
extern vmCvar_t g_fraglimit;
extern vmCvar_t g_timelimit;
extern vmCvar_t g_capturelimit;
extern vmCvar_t g_friendlyFire;
extern vmCvar_t g_password;
extern vmCvar_t g_needpass;
extern vmCvar_t g_gravity;
extern vmCvar_t g_speed;
extern vmCvar_t g_quadfactor;
extern vmCvar_t g_forcerespawn;
extern vmCvar_t g_inactivity;
extern vmCvar_t g_debugMove;
extern vmCvar_t g_debugAlloc;
extern vmCvar_t g_debugDamage;
extern vmCvar_t g_weaponRespawn;
extern vmCvar_t g_weaponTeamRespawn;
extern vmCvar_t g_synchronousClients;
extern vmCvar_t g_motd;
extern vmCvar_t g_warmup;
extern vmCvar_t g_doWarmup;
extern vmCvar_t g_blood;
extern vmCvar_t g_allowVote;
extern vmCvar_t g_teamAutoJoin;
extern vmCvar_t g_teamForceBalance;
extern vmCvar_t g_banIPs;
extern vmCvar_t g_filterBan;
extern vmCvar_t g_obeliskHealth;
extern vmCvar_t g_obeliskRegenPeriod;
extern vmCvar_t g_obeliskRegenAmount;
extern vmCvar_t g_obeliskRespawnDelay;
extern vmCvar_t g_cubeTimeout;
extern vmCvar_t g_redteam;
extern vmCvar_t g_blueteam;
extern vmCvar_t g_smoothClients;
extern vmCvar_t pmove_fixed;
extern vmCvar_t pmove_msec;
extern vmCvar_t g_rankings;
extern vmCvar_t g_enableDust;
extern vmCvar_t g_enableBreath;
extern vmCvar_t g_enableFogLaser;
extern vmCvar_t g_singlePlayer;
extern vmCvar_t g_proxMineTimeout;

// JBravo: unlagged
extern vmCvar_t g_delagHitscan;
extern vmCvar_t g_unlaggedVersion;
extern vmCvar_t sv_fps;

//Slicer: Matchmode
extern vmCvar_t g_RQ3_matchmode;
extern vmCvar_t g_RQ3_forceteamtalk;
extern vmCvar_t g_RQ3_maxplayers;
extern vmCvar_t g_RQ3_mmflags;

//Blaze: Reaction cvars
extern vmCvar_t g_rxn_knifelimit;
extern vmCvar_t g_RQ3_maxWeapons;
extern vmCvar_t g_RQ3_maxItems;
extern vmCvar_t g_RQ3_statLog;
extern vmCvar_t g_RQ3_ejectBlood;
extern vmCvar_t g_RQ3_respawnProtectTime;
extern vmCvar_t g_RQ3_cvarfile;

//Elder: spam protection cvars
extern vmCvar_t g_RQ3_messageMaxCount;	// Max messages in interval
extern vmCvar_t g_RQ3_messageInterval;	// Time interval for spam check
extern vmCvar_t g_RQ3_messageMaxWarnings;	// Max warning count
extern vmCvar_t g_RQ3_messageWarnTime;	// Time for warning; 0 for no-penalty warning
extern vmCvar_t g_RQ3_messageBanTime;	// Time for ban; 0 to kick
extern vmCvar_t g_RQ3_messageProtect;	// Elder: 0 disable, non-zero enable

// JBravo
extern vmCvar_t g_RQ3_roundlimit;	// JBravo: No. of rounds pr. map
extern vmCvar_t g_RQ3_roundtimelimit;	// JBravo: Time pr. round
extern vmCvar_t g_RQ3_tgren;		// JBravo: no. of team grenades
extern vmCvar_t g_RQ3_limchasecam;	// JBravo: 0 = no chasecam limit, 1 = limited to same team.
extern vmCvar_t g_RQ3_sniperup;		// JBravo: 0 = snipers begin with pistol, 1 = begin with sniper
extern vmCvar_t g_RQ3_team1name;	// JBravo: cvar for the name of team 1
extern vmCvar_t g_RQ3_team2name;	// JBravo: cvar for the name of team 2
extern vmCvar_t g_RQ3_team1model;	// JBravo: team 1 model and skin
extern vmCvar_t g_RQ3_team2model;	// JBravo: team 2 model and skin
extern vmCvar_t g_RQ3_tpcountdown;	// JBravo: to disable the pregame countdown
extern vmCvar_t g_RQ3_lca;		// JBravo: cvar to signal cgame that LCA is in progress
extern vmCvar_t g_RQ3_showOwnKills;	// JBravo: cvar to control if attaker sees his own obits and $K behavior
extern vmCvar_t g_RQ3_gib;		// JBravo: cvar for gib control
extern vmCvar_t g_RQ3_maxteamkills;	// JBravo: Max teamkills
extern vmCvar_t g_RQ3_twbanrounds;	// JBravo: no. of games team wounders are banned
extern vmCvar_t g_RQ3_tkbanrounds;	// JBravo: no. of games team killers are banned
extern vmCvar_t g_RQ3_ppl_idletime;	// JBravo: Seconds Idle before playing an insane sound
extern vmCvar_t g_RQ3_idleaction;	// JBravo: what to do with Idlers. 0 = sound, 1 = team none, 2 = kick
extern vmCvar_t g_RQ3_weaponban;	// JBravo: Bitmapped cvar for weaponbanning
extern vmCvar_t g_RQ3_itemban;		// JBravo: Bitmapped cvar for itembanning
extern vmCvar_t g_RQ3_ctb_respawndelay;	// JBravo: delay in seconds for ctb respawns
extern vmCvar_t g_RQ3_allWeapons;	// JBravo: if set, TP/DM players get all the weapons
extern vmCvar_t g_RQ3_allItems;		// JBravo: if set, TP/DM players get all the items
extern vmCvar_t g_RQ3_tdmMode;		// JBravo: Which TDM mode do we want?
extern vmCvar_t g_RQ3_haveHelmet;	// JBravo: Is the helmet active on the server ?
extern vmCvar_t g_RQ3_vote_waittime;	// JBravo: delay after mapchanges untill voting is allowed.

//Slicer: Team Status Cvars for MM
//extern vmCvar_t       g_RQ3_team1ready;
//extern vmCvar_t       g_RQ3_team2ready;
//aasimon: Ref System for MM
extern vmCvar_t g_RQ3_AllowRef;
extern vmCvar_t g_RQ3_RefPassword;
//extern vmCvar_t g_RQ3_RefID;
extern vmCvar_t g_RQ3_maxRefs;

// aasimon: ini stuff
extern vmCvar_t g_RQ3_IniFile;
extern vmCvar_t g_RQ3_ValidIniFile;
extern vmCvar_t g_RQ3_NextMapID;
extern vmCvar_t g_RQ3_NextMap;

//Slicer: Radio flood protect
extern vmCvar_t g_RQ3_radioRepeat;
extern vmCvar_t g_RQ3_radioRepeatTime;
extern vmCvar_t g_RQ3_radioBan;
extern vmCvar_t g_RQ3_radioFlood;
extern vmCvar_t g_RQ3_radioFloodTime;

//Makro - for server browsers
extern vmCvar_t g_RQ3_version;
//Makro - max votes per client;
extern vmCvar_t g_RQ3_maxClientVotes;
//Makro - no lame suicides
extern vmCvar_t g_RQ3_giveMeWhatsMine;

void trap_Printf(const char *fmt);
void trap_Error(const char *fmt) __attribute__((noreturn));
int trap_Milliseconds(void);
// JBravo: adding missing trap
int trap_RealTime(qtime_t *qtime);
int trap_Argc(void);
void trap_Argv(int n, char *buffer, int bufferLength);
void trap_Args(char *buffer, int bufferLength);
int trap_FS_FOpenFile(const char *qpath, fileHandle_t * f, fsMode_t mode);
void trap_FS_Read(void *buffer, int len, fileHandle_t f);
void trap_FS_Write(const void *buffer, int len, fileHandle_t f);
void trap_FS_FCloseFile(fileHandle_t f);
int trap_FS_GetFileList(const char *path, const char *extension, char *listbuf, int bufsize);
int trap_FS_Seek(fileHandle_t f, long offset, int origin);	// fsOrigin_t
void trap_SendConsoleCommand(int exec_when, const char *text);
void trap_Cvar_Register(vmCvar_t * cvar, const char *var_name, const char *value, int flags);
void trap_Cvar_Update(vmCvar_t * cvar);
void trap_Cvar_Set(const char *var_name, const char *value);
int trap_Cvar_VariableIntegerValue(const char *var_name);
float trap_Cvar_VariableValue(const char *var_name);
void trap_Cvar_VariableStringBuffer(const char *var_name, char *buffer, int bufsize);
void trap_LocateGameData(gentity_t * gEnts, int numGEntities, int sizeofGEntity_t, playerState_t * gameClients,
			 int sizeofGameClient);
void trap_DropClient(int clientNum, const char *reason);
void trap_SendServerCommand(int clientNum, const char *text);
void trap_SetConfigstring(int num, const char *string);
void trap_GetConfigstring(int num, char *buffer, int bufferSize);
void trap_GetUserinfo(int num, char *buffer, int bufferSize);
void trap_SetUserinfo(int num, const char *buffer);
void trap_GetServerinfo(char *buffer, int bufferSize);
void trap_SetBrushModel(gentity_t * ent, const char *name);
void trap_Trace(trace_t * results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end,
		int passEntityNum, int contentmask);
int trap_PointContents(const vec3_t point, int passEntityNum);
qboolean trap_InPVS(const vec3_t p1, const vec3_t p2);
qboolean trap_InPVSIgnorePortals(const vec3_t p1, const vec3_t p2);
void trap_AdjustAreaPortalState(gentity_t * ent, qboolean open);
qboolean trap_AreasConnected(int area1, int area2);
void trap_LinkEntity(gentity_t * ent);
void trap_UnlinkEntity(gentity_t * ent);
int trap_EntitiesInBox(const vec3_t mins, const vec3_t maxs, int *entityList, int maxcount);
qboolean trap_EntityContact(const vec3_t mins, const vec3_t maxs, const gentity_t * ent);
int trap_BotAllocateClient(void);
void trap_BotFreeClient(int clientNum);
void trap_GetUsercmd(int clientNum, usercmd_t * cmd);
qboolean trap_GetEntityToken(char *buffer, int bufferSize);

int trap_DebugPolygonCreate(int color, int numPoints, vec3_t * points);
void trap_DebugPolygonDelete(int id);

int trap_BotLibSetup(void);
int trap_BotLibShutdown(void);
int trap_BotLibVarSet(char *var_name, char *value);
int trap_BotLibVarGet(char *var_name, char *value, int size);
int trap_BotLibDefine(char *string);
int trap_BotLibStartFrame(float time);
int trap_BotLibLoadMap(const char *mapname);
int trap_BotLibUpdateEntity(int ent, void /* struct bot_updateentity_s */ *bue);
int trap_BotLibTest(int parm0, char *parm1, vec3_t parm2, vec3_t parm3);

int trap_BotGetSnapshotEntity(int clientNum, int sequence);
int trap_BotGetServerCommand(int clientNum, char *message, int size);
void trap_BotUserCommand(int client, usercmd_t * ucmd);

int trap_AAS_BBoxAreas(vec3_t absmins, vec3_t absmaxs, int *areas, int maxareas);
int trap_AAS_AreaInfo(int areanum, void /* struct aas_areainfo_s */ *info);
void trap_AAS_EntityInfo(int entnum, void /* struct aas_entityinfo_s */ *info);

int trap_AAS_Initialized(void);
void trap_AAS_PresenceTypeBoundingBox(int presencetype, vec3_t mins, vec3_t maxs);
float trap_AAS_Time(void);

int trap_AAS_PointAreaNum(vec3_t point);
int trap_AAS_PointReachabilityAreaIndex(vec3_t point);
int trap_AAS_TraceAreas(vec3_t start, vec3_t end, int *areas, vec3_t * points, int maxareas);

int trap_AAS_PointContents(vec3_t point);
int trap_AAS_NextBSPEntity(int ent);
int trap_AAS_ValueForBSPEpairKey(int ent, char *key, char *value, int size);
int trap_AAS_VectorForBSPEpairKey(int ent, char *key, vec3_t v);
int trap_AAS_FloatForBSPEpairKey(int ent, char *key, float *value);
int trap_AAS_IntForBSPEpairKey(int ent, char *key, int *value);

int trap_AAS_AreaReachability(int areanum);

int trap_AAS_AreaTravelTimeToGoalArea(int areanum, vec3_t origin, int goalareanum, int travelflags);
int trap_AAS_EnableRoutingArea(int areanum, int enable);
int trap_AAS_PredictRoute(void /*struct aas_predictroute_s */ *route, int areanum, vec3_t origin,
			  int goalareanum, int travelflags, int maxareas, int maxtime,
			  int stopevent, int stopcontents, int stoptfl, int stopareanum);

int trap_AAS_AlternativeRouteGoals(vec3_t start, int startareanum, vec3_t goal, int goalareanum, int travelflags,
				   void /*struct aas_altroutegoal_s */ *altroutegoals, int maxaltroutegoals,
				   int type);
int trap_AAS_Swimming(vec3_t origin);
int trap_AAS_PredictClientMovement(void /* aas_clientmove_s */ *move, int entnum, vec3_t origin, int presencetype,
				   int onground, vec3_t velocity, vec3_t cmdmove, int cmdframes, int maxframes,
				   float frametime, int stopevent, int stopareanum, int visualize);

void trap_EA_Say(int client, char *str);
void trap_EA_SayTeam(int client, char *str);
void trap_EA_Command(int client, char *command);

void trap_EA_Action(int client, int action);
void trap_EA_Gesture(int client);
void trap_EA_Talk(int client);
void trap_EA_Attack(int client);
void trap_EA_Use(int client);
void trap_EA_Respawn(int client);
void trap_EA_Crouch(int client);
void trap_EA_MoveUp(int client);
void trap_EA_MoveDown(int client);
void trap_EA_MoveForward(int client);
void trap_EA_MoveBack(int client);
void trap_EA_MoveLeft(int client);
void trap_EA_MoveRight(int client);
void trap_EA_SelectWeapon(int client, int weapon);
void trap_EA_Jump(int client);
void trap_EA_DelayedJump(int client);
void trap_EA_Move(int client, vec3_t dir, float speed);
void trap_EA_View(int client, vec3_t viewangles);

void trap_EA_EndRegular(int client, float thinktime);
void trap_EA_GetInput(int client, float thinktime, void /* struct bot_input_s */ *input);
void trap_EA_ResetInput(int client);

int trap_BotLoadCharacter(char *charfile, float skill);
void trap_BotFreeCharacter(int character);
float trap_Characteristic_Float(int character, int index);
float trap_Characteristic_BFloat(int character, int index, float min, float max);
int trap_Characteristic_Integer(int character, int index);
int trap_Characteristic_BInteger(int character, int index, int min, int max);
void trap_Characteristic_String(int character, int index, char *buf, int size);

int trap_BotAllocChatState(void);
void trap_BotFreeChatState(int handle);
void trap_BotQueueConsoleMessage(int chatstate, int type, char *message);
void trap_BotRemoveConsoleMessage(int chatstate, int handle);
int trap_BotNextConsoleMessage(int chatstate, void /* struct bot_consolemessage_s */ *cm);
int trap_BotNumConsoleMessages(int chatstate);
void trap_BotInitialChat(int chatstate, char *type, int mcontext, char *var0, char *var1, char *var2, char *var3,
			 char *var4, char *var5, char *var6, char *var7);
int trap_BotNumInitialChats(int chatstate, char *type);
int trap_BotReplyChat(int chatstate, char *message, int mcontext, int vcontext, char *var0, char *var1, char *var2,
		      char *var3, char *var4, char *var5, char *var6, char *var7);
int trap_BotChatLength(int chatstate);
void trap_BotEnterChat(int chatstate, int client, int sendto);
void trap_BotGetChatMessage(int chatstate, char *buf, int size);
int trap_StringContains(char *str1, char *str2, int casesensitive);
int trap_BotFindMatch(char *str, void /* struct bot_match_s */ *match, unsigned long int context);
void trap_BotMatchVariable(void /* struct bot_match_s */ *match, int variable, char *buf, int size);
void trap_UnifyWhiteSpaces(char *string);
void trap_BotReplaceSynonyms(char *string, unsigned long int context);
int trap_BotLoadChatFile(int chatstate, char *chatfile, char *chatname);
void trap_BotSetChatGender(int chatstate, int gender);
void trap_BotSetChatName(int chatstate, char *name, int client);
void trap_BotResetGoalState(int goalstate);
void trap_BotRemoveFromAvoidGoals(int goalstate, int number);
void trap_BotResetAvoidGoals(int goalstate);
void trap_BotPushGoal(int goalstate, void /* struct bot_goal_s */ *goal);
void trap_BotPopGoal(int goalstate);
void trap_BotEmptyGoalStack(int goalstate);
void trap_BotDumpAvoidGoals(int goalstate);
void trap_BotDumpGoalStack(int goalstate);
void trap_BotGoalName(int number, char *name, int size);
int trap_BotGetTopGoal(int goalstate, void /* struct bot_goal_s */ *goal);
int trap_BotGetSecondGoal(int goalstate, void /* struct bot_goal_s */ *goal);
int trap_BotChooseLTGItem(int goalstate, vec3_t origin, int *inventory, int travelflags);
int trap_BotChooseNBGItem(int goalstate, vec3_t origin, int *inventory, int travelflags,
			  void /* struct bot_goal_s */ *ltg, float maxtime);
int trap_BotTouchingGoal(vec3_t origin, void /* struct bot_goal_s */ *goal);
int trap_BotItemGoalInVisButNotVisible(int viewer, vec3_t eye, vec3_t viewangles, void /* struct bot_goal_s */ *goal);
int trap_BotGetNextCampSpotGoal(int num, void /* struct bot_goal_s */ *goal);
int trap_BotGetMapLocationGoal(char *name, void /* struct bot_goal_s */ *goal);
int trap_BotGetLevelItemGoal(int index, char *classname, void /* struct bot_goal_s */ *goal);
float trap_BotAvoidGoalTime(int goalstate, int number);
void trap_BotSetAvoidGoalTime(int goalstate, int number, float avoidtime);
void trap_BotInitLevelItems(void);
void trap_BotUpdateEntityItems(void);
int trap_BotLoadItemWeights(int goalstate, char *filename);
void trap_BotFreeItemWeights(int goalstate);
void trap_BotInterbreedGoalFuzzyLogic(int parent1, int parent2, int child);
void trap_BotSaveGoalFuzzyLogic(int goalstate, char *filename);
void trap_BotMutateGoalFuzzyLogic(int goalstate, float range);
int trap_BotAllocGoalState(int state);
void trap_BotFreeGoalState(int handle);

void trap_BotResetMoveState(int movestate);
void trap_BotMoveToGoal(void /* struct bot_moveresult_s */ *result, int movestate, void /* struct bot_goal_s */ *goal,
			int travelflags);
int trap_BotMoveInDirection(int movestate, vec3_t dir, float speed, int type);
void trap_BotResetAvoidReach(int movestate);
void trap_BotResetLastAvoidReach(int movestate);
int trap_BotReachabilityArea(vec3_t origin, int testground);
int trap_BotMovementViewTarget(int movestate, void /* struct bot_goal_s */ *goal, int travelflags, float lookahead,
			       vec3_t target);
int trap_BotPredictVisiblePosition(vec3_t origin, int areanum, void /* struct bot_goal_s */ *goal, int travelflags,
				   vec3_t target);
int trap_BotAllocMoveState(void);
void trap_BotFreeMoveState(int handle);
void trap_BotInitMoveState(int handle, void /* struct bot_initmove_s */ *initmove);
void trap_BotAddAvoidSpot(int movestate, vec3_t origin, float radius, int type);

int trap_BotChooseBestFightWeapon(int weaponstate, int *inventory);
void trap_BotGetWeaponInfo(int weaponstate, int weapon, void /* struct weaponinfo_s */ *weaponinfo);
int trap_BotLoadWeaponWeights(int weaponstate, char *filename);
int trap_BotAllocWeaponState(void);
void trap_BotFreeWeaponState(int weaponstate);
void trap_BotResetWeaponState(int weaponstate);

int trap_GeneticParentsAndChildSelection(int numranks, float *ranks, int *parent1, int *parent2, int *child);

void trap_SnapVector(float *v);

gentity_t *findradius(gentity_t * from, vec3_t org, float rad);	// Blaze: Find someone in a radius around you

//Makro - saves a custom death message index in "field"
void G_InitCustomDeathMessage(gentity_t *ent, int *field);

//Slicer: MatchMode
#include "g_matchmode.h"
