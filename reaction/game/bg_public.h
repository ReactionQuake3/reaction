//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.97  2002/09/29 16:06:44  jbravo
// Work done at the HPWorld expo
//
// Revision 1.96  2002/09/01 21:15:08  makro
// Sky portal tweaks
//
// Revision 1.95  2002/08/30 00:00:16  makro
// Sky portals
//
// Revision 1.94  2002/08/25 00:47:00  niceass
// q3f atmosphere
//
// Revision 1.93  2002/08/21 07:00:07  jbravo
// Added CTB respawn queue and fixed game <-> cgame synch problem in CTB
//
// Revision 1.92  2002/08/21 03:43:57  niceass
// allow clipvelocity outside of the bg_'s
//
// Revision 1.91  2002/07/26 06:21:43  jbravo
// Fixed the MM settings stuff so it works on remote servers also.
// Removed the MM_NAMES_COLOR since it broke on nicks with color in them.
//
// Revision 1.90  2002/07/22 07:26:43  niceass
// better fog laser support
//
// Revision 1.89  2002/07/22 06:33:34  niceass
// cleaned up the powerup code
//
// Revision 1.88  2002/07/21 18:48:24  niceass
// weapon prediction stuff
//
// Revision 1.87  2002/07/19 04:31:12  niceass
// changed ef_dead for bot protection
//
// Revision 1.86  2002/07/16 04:09:44  niceass
// skyportal compile fix
//
// Revision 1.85  2002/07/13 22:43:59  makro
// Semi-working fog hull, semi-working sky portals (cgame code commented out)
// Basically, semi-working stuff :P
//
// Revision 1.84  2002/07/07 18:36:13  jbravo
// Added an AntiIdle system. Can play insane sounds for idle players, drop them
// from teams or kick them.   Upped version to Beta 2.1
//
// Revision 1.83  2002/06/30 17:33:01  jbravo
// New radio sounds and the 0wned sound was added.
//
// Revision 1.82  2002/06/21 21:03:15  niceass
// quicker ssg after reload
//
// Revision 1.81  2002/06/19 18:13:57  jbravo
// New TNG spawning system :)
//
// Revision 1.80  2002/06/16 20:06:14  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.79  2002/06/16 17:37:59  jbravo
// Removed the MISSIONPACK ifdefs and missionpack only code.
//
// Revision 1.78  2002/06/12 22:32:24  slicer
// Even better way to improve the Cvar Anti-Cheat System
//
// Revision 1.77  2002/06/12 15:29:53  slicer
// Improved and fixed the Anti-Cheat System
//
// Revision 1.76  2002/06/10 14:03:47  slicer
// Removed rq3_cmd : ROUND
//
// Revision 1.75  2002/06/09 04:59:20  blaze
// RQ3_MAX_BREAKABLES upped from 16 to 64
//
// Revision 1.74  2002/05/28 01:46:58  jbravo
// Added stomach gibbing
//
// Revision 1.73  2002/05/28 01:17:01  jbravo
// More gib fixes.  g_RQ3_gib added
//
// Revision 1.72  2002/05/27 06:48:39  niceass
// headless variable
//
// Revision 1.71  2002/05/25 16:31:18  blaze
// moved breakable stuff over to config strings
//
// Revision 1.70  2002/05/25 10:40:31  makro
// Loading screen
//
// Revision 1.69  2002/05/23 03:07:10  blaze
// Some changes to autoaction, still need to fix up a little bit more stuff relating to getting sent 2 screenshot requests
//
// Revision 1.68  2002/05/21 04:58:27  blaze
// kicked the reload bugs ass!
//
// Revision 1.67  2002/05/19 21:27:28  blaze
// added force and buoyancy to breakables
//
// Revision 1.66  2002/05/19 21:04:37  jbravo
// Tkok popup system
//
// Revision 1.65  2002/05/18 21:57:54  blaze
// Transmit round start to clients
// used for cg_rq3_autoaction
//
// Revision 1.64  2002/05/15 03:43:09  niceass
// ssg disarm fix
//
// Revision 1.63  2002/05/12 14:40:28  makro
// Wood, brick & ceramic impact sounds
//
// Revision 1.62  2002/05/11 19:18:20  makro
// Sand surfaceparm
//
// Revision 1.61  2002/05/06 21:41:01  slicer
// Added rq3_cmd
//
// Revision 1.60  2002/05/02 12:44:58  makro
// Customizable color for the loading screen text. Bot stuff
//
// Revision 1.59  2002/04/30 11:54:37  makro
// Bots rule ! Also, added clips to give all. Maybe some other things
//
// Revision 1.58  2002/04/29 06:17:39  niceass
// small change to pressure system
//
// Revision 1.57  2002/04/23 06:04:12  niceass
// pressure stuff
//
// Revision 1.56  2002/04/20 15:03:48  makro
// More footstep sounds, a few other things
//
// Revision 1.55  2002/04/06 21:42:20  makro
// Changes to bot code. New surfaceparm system.
//
// Revision 1.54  2002/04/03 03:13:16  blaze
// NEW BREAKABLE CODE - will break all old breakables(wont appear in maps)
//
// Revision 1.53  2002/03/30 17:37:48  jbravo
// Added damage tracking to the server. Added zcam flic mode. cleaned up g_damage.
//
// Revision 1.52  2002/03/23 05:17:42  jbravo
// Major cleanup of game -> cgame communication with LCA vars.
//
// Revision 1.51  2002/03/21 19:22:12  jbravo
// Bando now adds extra ammo to the special weaps, and when its dropped it goes
// away again.
//
// Revision 1.50  2002/03/14 02:24:39  jbravo
// Adding radio :)
//
// Revision 1.49  2002/03/03 21:46:26  blaze
// weapon stats, done, beta test for bugs
//
// Revision 1.48  2002/02/26 02:58:47  jbravo
// Fixing the spectator_free mode not being predicted in the client.
//
// Revision 1.47  2002/02/25 19:41:53  jbravo
// Fixed the use ESC and join menu to join teams when dead players are
// spectating in TP mode.
// Tuned the autorespawn system a bit.  Now dead ppl. are dead for a very
// small time before they are made into spectators.
//
// Revision 1.46  2002/02/11 00:30:23  niceass
// LCA fix
//
// Revision 1.45  2002/01/27 13:33:28  jbravo
// Teamplay antistick system.
//
// Revision 1.44  2002/01/24 14:20:53  jbravo
// Adding func_explosive and a few new surfaceparms
//
// Revision 1.43  2002/01/11 20:20:58  jbravo
// Adding TP to main branch
//
// Revision 1.42  2002/01/11 19:48:30  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.41  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
// bg_public.h -- definitions shared by both the server game and client game modules

// because games can change separately from the main system version, we need a
// second version that must match between game and cgame

#define	GAME_VERSION		"baseq3-1"

#define	DEFAULT_GRAVITY		800
//Elder: lowered from -40 so falling deaths don't gib so easily
#define	GIB_HEALTH			-500
#define	ARMOR_PROTECTION	0.66

#define	MAX_ITEMS			256

#define	RANK_TIED_FLAG		0x4000

//Elder: Q2 shotgun spreads for handcannon
#define DEFAULT_SHOTGUN_HSPREAD 1000
#define DEFAULT_SHOTGUN_VSPREAD 500
#define DEFAULT_M3_HSPREAD	800
#define DEFAULT_M3_VSPREAD	800

//Elder: this are uncertified
//#define DEFAULT_SHOTGUN_SPREAD        700
//#define DEFAULT_HANDCANNON_SPREAD     1400
//#define DEFAULT_SHOTGUN_COUNT 11
#define DEFAULT_M3_COUNT		12
#define DEFAULT_HANDCANNON_COUNT 17	//Elder: 17 per blast = 34 per shot

//Elder: changing this will affect the cgame entity placement
#define	ITEM_RADIUS			15	// item sizes are needed for client side pickup detection

#define	LIGHTNING_RANGE		768
//Blaze: Distance the knife reaches
#define KNIFE_RANGE 45

#define	SCORE_NOT_PRESENT	-9999	// for the CS_SCORES[12] when only one player is present

#define	VOTE_TIME			30000	// 30 seconds before vote times out

#define	MINS_Z				-24
//#define DEFAULT_VIEWHEIGHT    22
#define	DEFAULT_VIEWHEIGHT	26
//Elder: changed to 8 like AQ2 source
//Elder: moved back to original viewheight
//#define CROUCH_VIEWHEIGHT     8
#define CROUCH_VIEWHEIGHT	12
#define	DEAD_VIEWHEIGHT		-16

//Elder: New breakable bit definitions
//Enum materials?
//No amount bits = Low ... both amount bits = Tons
#define RQ3_DEBRIS_MEDIUM			0x00000001
#define RQ3_DEBRIS_HIGH				0x00000002
//No variation bits = original... both variation bits = variation 3
#define RQ3_DEBRIS_VAR1				0x00000004
#define RQ3_DEBRIS_VAR2				0x00000008
//These are not "compressed"
#define RQ3_DEBRIS_GLASS			0x00000010
#define RQ3_DEBRIS_WOOD				0x00000020
#define RQ3_DEBRIS_METAL			0x00000040
#define RQ3_DEBRIS_CERAMIC			0x00000080
#define RQ3_DEBRIS_PAPER			0x00000100
#define RQ3_DEBRIS_BRICK			0x00000200
#define RQ3_DEBRIS_CONCRETE			0x00000400
#define RQ3_DEBRIS_POPCAN			0x00000800

// Elder: dynamic light switches
#define DLIGHT_ADDITIVE		1
#define DLIGHT_FLICKER		2
#define DLIGHT_PULSE		4
#define DLIGHT_STROBE		8

//Blaze: Max number of breakables
#define RQ3_MAX_BREAKABLES 64

//Old debris definitions
//Elder: debris bit parms to pass to break_glass - maybe I should enum this?
/*
#define RQ3_DEBRIS_SMALL	0x00000001
#define RQ3_DEBRIS_MEDIUM	0x00000002
#define RQ3_DEBRIS_LARGE	0x00000004
#define RQ3_DEBRIS_TONS		0x00000008
#define RQ3_DEBRIS_GLASS	0x00000010
#define RQ3_DEBRIS_WOOD		0x00000020
#define RQ3_DEBRIS_METAL	0x00000040
#define RQ3_DEBRIS_CERAMIC	0x00000080
#define RQ3_DEBRIS_PAPER	0x00000100
#define RQ3_DEBRIS_BRICK	0x00000200
#define RQ3_DEBRIS_CONCRETE	0x00000400
//#define RQ3_DEBRIS_POPCAN	0x00000800

//Elder: debris variations
#define RQ3_DEBRIS_VAR0		0x00001000
#define RQ3_DEBRIS_VAR1		0x00002000
#define RQ3_DEBRIS_VAR2		0x00004000
#define RQ3_DEBRIS_VAR3		0x00008000
*/
//Elder: to stop some of the hardcoding
//This is some ammo amounts per clip/item pick up
#define RQ3_SSG3000_CLIP		6
#define RQ3_MP5_CLIP			30
#define RQ3_M3_CLIP				7
#define RQ3_M4_CLIP				24
#define RQ3_PISTOL_CLIP			12
#define RQ3_KNIFE_CLIP			1
#define RQ3_AKIMBO_CLIP			24
#define RQ3_HANDCANNON_CLIP		7
#define RQ3_GRENADE_CLIP		1

//Elder: this is the maximum reserve hold sans bandolier
#define RQ3_SSG3000_MAXCLIP		20
#define RQ3_MP5_MAXCLIP			2
#define RQ3_M3_MAXCLIP			14
#define RQ3_M4_MAXCLIP			1
#define RQ3_PISTOL_MAXCLIP		2
#define RQ3_KNIFE_MAXCLIP		10
#define RQ3_AKIMBO_MAXCLIP		2
#define RQ3_HANDCANNON_MAXCLIP	14
#define RQ3_GRENADE_MAXCLIP		2

//Elder: this is the amount to add when reloading
#define RQ3_SSG3000_RELOAD		1	//Elder: note - one at a time
#define RQ3_MP5_RELOAD			30
#define RQ3_M3_RELOAD			1	//Elder: note - one at a time
#define RQ3_M4_RELOAD			24
#define RQ3_PISTOL_RELOAD		12
#define RQ3_KNIFE_RELOAD		1	//Elder: shouldn't need to reload
#define RQ3_AKIMBO_RELOAD		24
#define RQ3_HANDCANNON_RELOAD	2
#define RQ3_GRENADE_RELOAD		1	//Elder: shouldn't need to reload

//Elder: this is the amount for a full chamber
#define RQ3_SSG3000_AMMO		6
#define RQ3_MP5_AMMO			30
#define RQ3_M3_AMMO				7
#define RQ3_M4_AMMO				24
#define RQ3_PISTOL_AMMO			12
#define RQ3_KNIFE_AMMO			1	//Elder: shouldn't need this value
#define RQ3_AKIMBO_AMMO			24
#define RQ3_HANDCANNON_AMMO		2
#define RQ3_GRENADE_AMMO		1	//Elder: shouldn't need this value

// JBravo: extra ammo for the guns in Teamplay.
#define RQ3_SSG3000_EXTRA_AMMO		10
#define RQ3_MP5_EXTRA_AMMO		1
#define RQ3_M3_EXTRA_AMMO		7
#define RQ3_M4_EXTRA_AMMO		1
#define RQ3_AKIMBO_EXTRA_AMMO		2
#define RQ3_HANDCANNON_EXTRA_AMMO	12
#define RQ3_KNIVES_EXTRA_AMMO		10

//Elder: confused?

//Elder: from Action source, but changed defined names a bit
#define RQ3_PISTOL_NAME 		"MK23 Pistol"
#define RQ3_MP5_NAME 			"MP5/10 Submachinegun"
#define RQ3_M4_NAME 			"M4 Assault Rifle"
#define RQ3_M3_NAME 			"M3 Super 90 Assault Shotgun"
#define RQ3_HANDCANNON_NAME 	"Handcannon"
#define RQ3_SSG3000_NAME 		"Sniper Rifle"
#define RQ3_AKIMBO_NAME 		"Dual MK23 Pistols"
#define RQ3_KNIFE_NAME 			"Combat Knife"
#define RQ3_GRENADE_NAME 		"M26 Fragmentation Grenade"

#define RQ3_SILENCER_NAME 		"Silencer"
#define RQ3_SLIPPERS_NAME 		"Stealth Slippers"
#define RQ3_BANDOLIER_NAME 		"Bandolier"
#define RQ3_KEVLAR_NAME 		"Kevlar Vest"
#define RQ3_LASER_NAME			"Lasersight"

enum {
	LIGHTS,
	CAMERA,
	ACTION,
	TPCOUNTDOWN,
	SELECTPISTOL,
//Slicer: apparently not being used
//      ROUND,
	MAPEND,
	MAPSTART,
	SETWEAPON,
	STUFF,
	TKOK,
	RADIO,
	STARTDEMO,
	STOPDEMO,
	SCREENSHOT,
	OWNED,
	CVARSET,
	CTBCOUNTDOWN
};

//Elder: sound events for EV_RQ3_SOUND
typedef enum {
	RQ3_SOUND_KICK,
	RQ3_SOUND_HEADSHOT,
	RQ3_SOUND_KNIFEHIT,
	RQ3_SOUND_KNIFEDEATH,
	RQ3_SOUND_LCA,		//lights, camera, action!
	RQ3_SOUND_KEVLARHIT,
	RQ3_SOUND_COUNTDOWN,

	RQ3_SOUND_TOTAL
} rq3_sounds_t;

// JBravo: radio. This part stolen from AQ
typedef struct radio_msg_s {
	char *msg;		// the msg name
	int length;		// length in server frames (ie tenths of a second), rounded up
} radio_msg_t;

extern radio_msg_t male_radio_msgs[];
extern radio_msg_t female_radio_msgs[];

//Elder: Weapon damage and spread stats
#define PISTOL_DAMAGE 			90
#define MP5_DAMAGE 				55
#define M4_DAMAGE 				90
#define M3_DAMAGE 				17
//Elder: wrong name
//#define SHOTGUN_DAMAGE                        17
#define HANDCANNON_DAMAGE 		20
#define SNIPER_DAMAGE 			250
#define AKIMBO_DAMAGE 			90
#define SLASH_DAMAGE 			200	//Shashing knife damage
#define THROW_DAMAGE 			250	//Throwing Knife damage
#define GRENADE_DAMAGE			170
#define GRENADE_SPLASH_DAMAGE	170
#define GRENADE_SPLASH_RADIUS	340	//Damage * 2

#define PISTOL_SPREAD 			140
#define MP5_SPREAD 				250
#define M4_SPREAD 				300
#define SNIPER_SPREAD 			425
#define AKIMBO_SPREAD     		300

//Elder: weapon kicks - I think this is against whoever got hit?
#define RQ3_PISTOL_KICK			150
#define RQ3_M3_KICK				20
#define RQ3_M4_KICK				90
#define RQ3_MP5_KICK			90
#define RQ3_HANDCANNON_KICK		40
#define RQ3_SNIPER_KICK			200	// but it seems to get multiplied by zero in the source
#define RQ3_AKIMBO_KICK			90
#define RQ3_KNIFE_KICK			0
#define RQ3_THROW_KICK			50
#define RQ3_GRENADE_KICK		200	// Elder: assumed

//Elder: weaponTime constants (delay in milliseconds)
//Kinda "derived" from the AQ2 source
//Recall that Q2 animations run at 10Hz and the fire
//rate is derived from the number of animation frames
#define RQ3_PISTOL_DELAY		400
#define RQ3_M3_DELAY			900
#define RQ3_M4_DELAY			100
#define RQ3_MP5_DELAY			100
#define RQ3_HANDCANNON_DELAY	1200
#define RQ3_SSG3000_DELAY		1400
#define RQ3_SSG3000_BOLT_DELAY	1300	// Elder: delay before zooming back in
//#define RQ3_AKIMBO_DELAY              500     // Elder: two delays: one for the total delay
//#define RQ3_AKIMBO_DELAY2             200 // one for the time to start the second shot
#define RQ3_AKIMBO_DELAY		100
#define RQ3_AKIMBO_DELAY2		300
#define RQ3_KNIFE_DELAY			800
#define RQ3_THROW_DELAY			300	// NiceAss: Was 800, but much too slow.
#define RQ3_KNIFE_SLASH_BURST   30	// NiceAss: For slashing every 30 ms. (Agt's arbitrary number of the day =))
#define RQ3_GRENADE_DELAY		300	// NiceAss: Was 750, but much too slow.

//Elder: reload delays
//Also kinda "derived" from the AQ2 source
#define RQ3_PISTOL_RELOAD_DELAY			2100
#define RQ3_M4_RELOAD_DELAY				1900
#define RQ3_MP5_RELOAD_DELAY			1800
#define RQ3_HANDCANNON_RELOAD_DELAY		2100
#define RQ3_AKIMBO_RELOAD_DELAY			2500

#define RQ3_M3_RELOAD_DELAY				1100
#define RQ3_M3_ALLOW_FAST_RELOAD_DELAY	700	// 700 Time into reload to enable fast-reloads
#define RQ3_M3_FAST_RELOAD_DELAY		500	// Fast reload time
//#define RQ3_M3_START_RELOAD_DELAY             300 // Start index point of fast reload
#define RQ3_M3_FINISH_RELOAD_DELAY		300	// Amount of time after all fast reloads

#define RQ3_SSG3000_RELOAD_DELAY		3100
#define RQ3_SSG3000_ALLOW_FAST_RELOAD_DELAY	1800	//1100 Time into reload to enable fast-reloads
#define RQ3_SSG3000_FAST_RELOAD_DELAY	600	// Fast reload time
//#define RQ3_SSG3000_START_RELOAD_DELAY        1700    // Start index point of fast reload
#define RQ3_SSG3000_FINISH_RELOAD_DELAY	200	// Amount of time after all fast reloads. Was 800.

#define RQ3_KNIFE_RELOAD_DELAY			0	// Elder: shouldn't need
#define RQ3_GRENADE_RELOAD_DELAY		0	// Elder: shouldn't need

//Elder: each weapon also has a different weapon switch up delay... ugh bloody hell
#define RQ3_PISTOL_ACTIVATE_DELAY		900
#define RQ3_M3_ACTIVATE_DELAY			700
#define RQ3_M4_ACTIVATE_DELAY			700	// 1000
#define RQ3_MP5_ACTIVATE_DELAY			1000
#define RQ3_HANDCANNON_ACTIVATE_DELAY	600
#define RQ3_SSG3000_ACTIVATE_DELAY		800
#define RQ3_AKIMBO_ACTIVATE_DELAY		600
#define RQ3_KNIFE_ACTIVATE_DELAY		500
#define RQ3_THROW_ACTIVATE_DELAY		500
#define RQ3_GRENADE_ACTIVATE_DELAY		500	//300  Elder: I made this up

//Elder: each weapon also has a different weapon switch down delay and...
#define RQ3_PISTOL_DISARM_DELAY			300
#define RQ3_M3_DISARM_DELAY				600
#define RQ3_M4_DISARM_DELAY				500
#define RQ3_MP5_DISARM_DELAY			400
#define RQ3_HANDCANNON_DISARM_DELAY		400
#define RQ3_SSG3000_DISARM_DELAY		900	// For some reason it's auto-used with WEAPON_RAISING
#define RQ3_AKIMBO_DISARM_DELAY			800
#define RQ3_KNIFE_DISARM_DELAY			700
#define RQ3_THROW_DISARM_DELAY			700
#define RQ3_GRENADE_DISARM_DELAY		300	//Elder: I made this up

//Elder: special for grenade: speeds depending on distance select
#define GRENADE_SHORT_SPEED		400
#define GRENADE_MEDIUM_SPEED	720
#define GRENADE_LONG_SPEED		920

//Elder: knife throw speed - from the AQ2 source
#define THROW_SPEED                             1200	// NiceAss: Changed to 1100 (from 1200)

//Elder: special flag needed in both games
#define FL_THROWN_KNIFE			0x00040000	// Elder: thrown knife special case

//Elder: weapon modifications
#define RQ3_WPMOD_SILENCER		1
#define RQ3_WPMOD_KNIFESLASH	2
// NiceAss: Used after the first "slash" of the knife.
// A bit misleading in its name. It also means there will be no sound.
#define RQ3_WPMOD_KNIFENOMARK	3
// Niceass: If you are switching weapons, the grenade is dropped rather than thrown.
#define RQ3_WPMOD_GRENADEDROP	4

//
// config strings are a general means of communicating variable length strings
// from the server to all connected clients.
//

// CS_SERVERINFO and CS_SYSTEMINFO are defined in q_shared.h
#define	CS_MUSIC			2
#define	CS_MESSAGE			3	// from the map worldspawn's message field
#define	CS_MOTD				4	// g_motd string for server message of the day
#define	CS_WARMUP			5	// server time when the match will be restarted
#define	CS_SCORES1			6
#define	CS_SCORES2			7
#define CS_VOTE_TIME		8
#define CS_VOTE_STRING		9
#define	CS_VOTE_YES			10
#define	CS_VOTE_NO			11

#define CS_TEAMVOTE_TIME		12
#define CS_TEAMVOTE_STRING		14
#define	CS_TEAMVOTE_YES			16
#define	CS_TEAMVOTE_NO			18

#define	CS_GAME_VERSION			20
#define	CS_LEVEL_START_TIME		21	// so the timer only shows the current level
#define	CS_INTERMISSION			22	// when 1, fraglimit/timelimit has been hit and intermission will start in a second or two
#define CS_FLAGSTATUS			23	// string indicating flag status in CTF
#define CS_SHADERSTATE			24
#define CS_BOTINFO				25

#define	CS_ITEMS				27	// string of 0's and 1's that tell which items are present
#define CS_ATMOSEFFECT			28	// q3f: Atmospheric effect, if any.

//Makro - color for the loading screen text
//#define CS_LOADINGSCREEN              29
//Makro - sky portals !
#define CS_SKYPORTAL		30
//Makro - fog hull
#define CS_FOGHULL			31

#define	CS_MODELS			32
#define	CS_SOUNDS			(CS_MODELS+MAX_MODELS)
#define	CS_PLAYERS			(CS_SOUNDS+MAX_SOUNDS)
#define CS_LOCATIONS		(CS_PLAYERS+MAX_CLIENTS)
#define CS_PARTICLES			(CS_LOCATIONS+MAX_LOCATIONS)
//Blaze: Storing breakables in config strings now
#define CS_BREAKABLES (CS_PARTICLES+MAX_LOCATIONS)

#define CS_MAX					(CS_BREAKABLES+RQ3_MAX_BREAKABLES)

#if (CS_MAX) > MAX_CONFIGSTRINGS
#error overflow: (CS_MAX) > MAX_CONFIGSTRINGS
#endif

typedef enum {
	GT_FFA,			// free for all
	GT_TOURNAMENT,		// one on one tournament
	GT_SINGLE_PLAYER,	// single player ffa

	//-- team games go after this --

	GT_TEAM,		// team deathmatch
	GT_TEAMPLAY,		// JBravo: The teamplay mode itself.
	GT_CTF,			// capture the flag
	GT_1FCTF,
	GT_OBELISK,
	GT_HARVESTER,
	GT_MAX_GAME_TYPE
} gametype_t;

typedef enum { GENDER_MALE, GENDER_FEMALE, GENDER_NEUTER } gender_t;

/*
===================================================================================

PMOVE MODULE

The pmove code takes a player_state_t and a usercmd_t and generates a new player_state_t
and some other output data.  Used for local prediction on the client game and true
movement on the server game.
===================================================================================
*/

typedef enum {
	PM_NORMAL,		// can accelerate and turn
	PM_NOCLIP,		// noclip movement
	PM_SPECTATOR,		// still run into walls
	PM_DEAD,		// no acceleration or turning, but free falling
	PM_FREEZE,		// stuck in place with no control
	PM_INTERMISSION,	// no movement or status bar
	PM_SPINTERMISSION	// no movement or status bar
} pmtype_t;

typedef enum {
	WEAPON_READY,		//sync with WP_ANIM_IDLE
	WEAPON_COCKED,		//sync with WP_ANIM_EXTRA1 for grenade
	WEAPON_RAISING,		//sync with WP_ANIM_ACTIVATE
	WEAPON_DROPPING,	//sync with WP_ANIM_DISARM
	WEAPON_FIRING,		//sync with WP_ANIM_FIRE
	WEAPON_RELOADING,	//sync with WP_ANIM_RELOAD
	WEAPON_STALL,		//for delaying weapon fires (knife, grenade)
	WEAPON_MODECHANGE,	// NiceAss: sync with WP_ANIM_EXTRA1 & WP_ANIM_EXTRA2 for knife.
	WEAPON_BANDAGING	// NiceAss: Added to follow AQ2 and fix a bug.
} weaponstate_t;

//Blaze: for the weapon animation states
typedef enum {
	//WP_ANIM_READY,
	WP_ANIM_FIRE,
	WP_ANIM_RELOAD,
	WP_ANIM_IDLE,
	WP_ANIM_DISARM,
	WP_ANIM_ACTIVATE,
	WP_ANIM_EMPTY,
	WP_ANIM_EXTRA1,		// e.g. grenade pulling pin, fast-reload, knife slash to throw switch
	WP_ANIM_EXTRA2,		// knife throw to slash switch
	// Knife exclusives
	WP_ANIM_THROWFIRE,
	WP_ANIM_THROWIDLE,
	WP_ANIM_THROWDISARM,
	WP_ANIM_THROWACTIVATE,
	MAX_WEAPON_ANIMATIONS
} wpAnimNumber_t;

// pmove->pm_flags
#define	PMF_DUCKED			1
#define	PMF_JUMP_HELD		2
#define	PMF_BACKWARDS_JUMP	8	// go into backwards land
#define	PMF_BACKWARDS_RUN	16	// coast down to backwards run
#define	PMF_TIME_LAND		32	// pm_time is time before rejump
#define	PMF_TIME_KNOCKBACK	64	// pm_time is an air-accelerate only time
#define	PMF_TIME_WATERJUMP	256	// pm_time is waterjump
#define	PMF_RESPAWNED		512	// clear after attack and jump buttons come up
#define	PMF_USE_ITEM_HELD	1024
#define PMF_GRAPPLE_PULL	2048	// pull towards grapple location
#define PMF_FOLLOW			4096	// spectate following another player
#define PMF_SCOREBOARD		8192	// spectate as a scoreboard
// NiceAss: Room for something right here, value 16384
#define PMF_RELOAD_HELD		32768	// Elder: new reload code

#define	PMF_ALL_TIMES	(PMF_TIME_WATERJUMP|PMF_TIME_LAND|PMF_TIME_KNOCKBACK)

#define	MAXTOUCH	32
typedef struct {
	// state (in / out)
	playerState_t *ps;

	// command (in)
	usercmd_t cmd;
	int tracemask;		// collide against these types of surfaces
	int debugLevel;		// if set, diagnostic output will be printed
	qboolean noFootsteps;	// if the game is setup for no footsteps by the server
	qboolean gauntletHit;	// true if a gauntlet attack would actually hit something

	int framecount;

	// results (out)
	int numtouch;
	int touchents[MAXTOUCH];

	vec3_t mins, maxs;	// bounding box size

	int watertype;
	int waterlevel;

	float xyspeed;

	// for fixed msec Pmove
	int pmove_fixed;
	int pmove_msec;

	// callbacks to test the world
	// these will be different functions during game and cgame
	void (*trace) (trace_t * results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end,
		       int passEntityNum, int contentMask);

	int (*pointcontents) (const vec3_t point, int passEntityNum);
// JBravo: lca info for the pm stuff
	qboolean lca;
	qboolean predict;
} pmove_t;

// if a full pmove isn't done on the client, you can just update the angles
void PM_UpdateViewAngles(playerState_t * ps, const usercmd_t * cmd);
void Pmove(pmove_t * pmove);

//===================================================================================

// player_state->stats[] indexes
// NOTE: may not have more than 16
typedef enum {
	STAT_HEALTH,
	STAT_HOLDABLE_ITEM,	// Elder: Used to hold unique items in Reaction
	STAT_WEAPONS,		// 16 bit fields
	STAT_ARMOR,		// Elder: technically we don't need this anymore
	STAT_DEAD_YAW,		// look this direction when dead (FIXME: get rid of?)

	STAT_CLIENTS_READY,	// bit mask of clients wishing to exit the intermission (FIXME: configstring?)
	//STAT_MAX_HEALTH,                              // health / armor limit, changable by handicap

	//These are RQ3-related specific stats
	STAT_CLIPS,		// Num Clips player currently has
	STAT_BURST,		// number of shots in burst
	STAT_JUMPTIME,		// Blaze: Double jump
	STAT_RELOADTIME,	// Elder: Reload sound triggering and weapon switch override
	STAT_RELOADATTEMPTS,	// Elder: For fast-reload queuing
	STAT_WEAPONSTALLTIME,	// Elder: For delaying grenades, knife throwing, etc.
	STAT_FALLDAMAGE,
	STAT_RQ3		// Blaze: Will hold a few flags for bandage, etc info
	    //STAT_STREAK,                                  // Elder: wasteful stat -- only used on server-side ATM
} statIndex_t;

//STAT_RQ3 stat info
#define RQ3_LEGDAMAGE		1	//If this bit is set, the player has leg damage
#define RQ3_BANDAGE_NEED	2
#define RQ3_BANDAGE_WORK	4
// Elder: zoom stat - 1x = 0, 2x = zoom low, 4x = zoom_med, 6x = zoom_low + zoom_med
#define RQ3_ZOOM_LOW		8
#define RQ3_ZOOM_MED		16
#define RQ3_THROWWEAPON		32	// Present if dropping weapon via cmd or kicked away
#define RQ3_FASTRELOADS		64	// Fast-reloads flag
#define RQ3_LOCKRELOADS		128	// Lock-reloads at end of fast-reload cycle
#define RQ3_QUEUERELOAD		256	// auto-reload if set
#define RQ3_RELOADWEAPON1	512	// flag off EV_RELOAD_WEAPON1 event so no dupes occur
#define RQ3_PLAYERSOLID		1024	// JBravo: Flag set when player is solid.
#define RQ3_ZCAM		2048	// JBravo: Flag to tell cgame when zcam is on.

// player_state->persistant[] indexes
// these fields are the only part of player_state that isn't
// cleared on respawn
// NOTE: may not have more than 16
typedef enum {
	PERS_SCORE,		// !!! MUST NOT CHANGE, SERVER AND GAME BOTH REFERENCE !!!
	PERS_HITS,		// total points damage inflicted so damage beeps can sound on change
	PERS_RANK,		// player rank or team rank
	PERS_TEAM,		// player team
	PERS_SPAWN_COUNT,	// incremented every respawn
	PERS_PLAYEREVENTS,	// 16 bits that can be flipped for events
	PERS_ATTACKER,		// clientnum of last damage inflicter
	PERS_ATTACKEE_ARMOR,	// health/armor of last person we attacked
	PERS_KILLED,		// count of the number of times you died
	// player awards tracking
	/* Blaze: No need for these, may re-implement later if we want in a different form
	   PERS_IMPRESSIVE_COUNT,                       // two railgun hits in a row
	   PERS_EXCELLENT_COUNT,                        // two successive kills in a short amount of time
	   PERS_DEFEND_COUNT,                           // defend awards
	   PERS_ASSIST_COUNT,                           // assist awards
	   PERS_GAUNTLET_FRAG_COUNT,            // kills with the guantlet
	   PERS_CAPTURES                                        // captures
	 */
	PERS_SAVEDTEAM,		// JBravo: for TP
	PERS_DAMAGE_DELT,	// JBravo: Keeping track of damage.
	PERS_WEAPONMODES	// Blaze: Holds the different weapond modes for the different guns see below for the defines to use
} persEnum_t;

//RQ3 Weapon modes - If the bit is set, then the weapon is in the more restrictive mode, as in if it's set to 1 it's semi, 3rnd burst, etc
#define RQ3_MK23MODE		1	// Pistol modes
#define RQ3_MP5MODE			2	// MP5 Modes
#define RQ3_M4MODE			4	// M4 Modes
#define RQ3_KNIFEMODE		8	// Knife Modes
#define RQ3_GRENSHORT		16	// Short range grenade
#define RQ3_GRENMED			32	// Medium range grenade, if short and medium are both 1, then it is long range

// entityState_t->eFlags
// NiceAss: I swapped these two for OGC protection. I hope it helps.
#define EF_HANDCANNON_SMOKED 0x00000001	// Elder: HC Smoke
#define	EF_DEAD				0x00000002	// don't draw a foe marker over players with EF_DEAD
#define	EF_TELEPORT_BIT		0x00000004	// toggled every time the origin abruptly changes
#define	EF_AWARD_EXCELLENT	0x00000008	// draw an excellent sprite
#define EF_PLAYER_EVENT		0x00000010
#define	EF_BOUNCE			0x00000010	// for missiles
#define	EF_BOUNCE_HALF		0x00000020	// for missiles
#define	EF_AWARD_GAUNTLET	0x00000040	// draw a gauntlet sprite
#define	EF_NODRAW			0x00000080	// may have an event, but no model (unspawned items)
#define	EF_FIRING			0x00000100	// for lightning gun
#define	EF_HEADLESS			0x00000200	// NiceAss: Replaced EF_KAMAKAZI
#define	EF_MOVER_STOP		0x00000400	// will push otherwise
#define EF_AWARD_CAP		0x00000800	// draw the capture sprite
#define	EF_TALK				0x00001000	// draw a talk balloon
#define	EF_CONNECTION		0x00002000	// draw a connection trouble sprite
#define	EF_VOTED			0x00004000	// already cast a vote
#define	EF_AWARD_IMPRESSIVE	0x00008000	// draw an impressive sprite
#define	EF_AWARD_DEFEND		0x00010000	// draw a defend sprite
#define	EF_AWARD_ASSIST		0x00020000	// draw a assist sprite
#define EF_AWARD_DENIED		0x00040000	// denied
#define EF_TEAMVOTED		0x00080000	// already cast a team vote


// NOTE: may not have more than 16
typedef enum {
	PW_NONE,

	PW_LASERSIGHT,

	PW_REDFLAG,
	PW_BLUEFLAG,
	PW_NEUTRALFLAG,

	PW_NUM_POWERUPS
} powerup_t;

//Elder: swapped around + full Bando name and typo fix on "slipers"
typedef enum {
	HI_NONE,

	//TODO: remove the baseQ3 ones
	HI_TELEPORTER,
	HI_MEDKIT,
	HI_KAMIKAZE,
	HI_PORTAL,
	HI_INVULNERABILITY,
	HI_KEVLAR,
	HI_LASER,
	HI_SILENCER,
	HI_BANDOLIER,
	HI_SLIPPERS,

	HI_NUM_HOLDABLE
} holdable_t;

typedef enum {
	WP_NONE,
//Blaze: Reaction Weapons
//Remember to put them in the right spots
/*
MK23 Pistol
M3 Super 90 Assault Shotgun
MP5/10 Submachinegun
Handcannon
Sniper Rifle
M4 Assault Rifle
Dual MK23 Pistols
Combat Knife
*/
	WP_PISTOL,
	WP_M3,
	WP_MP5,
	WP_HANDCANNON,
	WP_SSG3000,
	WP_M4,
	WP_AKIMBO,
	WP_KNIFE,
	WP_GRENADE,

	WP_NUM_WEAPONS
} weapon_t;

// Elder: for our end-level awards later on
// I was just brainstorming a whole bunch of necessary records
// This should probably be defined in g_local.h because it
// will almost be exclusively for the server to utilize
// We can send config strings to the individual players
// for their own review and the global config string would
// contain the global ones with rewards
typedef enum {
	// Location-hit tally - Where this player shot at
	REC_HEADSHOTS,
	REC_CHESTSHOTS,
	REC_STOMACHSHOTS,
	REC_LEGSHOTS,
	REC_FRONTSHOTS,
	REC_BACKSHOTS,
	REC_LEFTSHOTS,
	REC_RIGHTSHOTS,
	REC_CORPSESHOTS,	// sickos - takes precedence over above records on carcasses
	REC_GIBSHOTS,		// sickos - takes precedence over above records on carcasses
	// Weapon usage tally
	REC_MP5SHOTS,
	REC_M4SHOTS,
	REC_MK23SHOTS,
	REC_SSG3000SHOTS,
	REC_HANDCANNONSHOTS,
	REC_M3SHOTS,
	REC_AKIMBOSHOTS,
	REC_GRENADESHOTS,
	REC_KNIFETHROWSHOTS,
	REC_KNIFESLASHSHOTS,
	REC_MK23HITS,
	REC_M3HITS,
	REC_MP5HITS,
	REC_M4HITS,
	REC_SSG3000HITS,
	REC_HANDCANNONHITS,
	REC_AKIMBOHITS,
	REC_GRENADEHITS,
	REC_KNIFETHROWHITS,
	REC_KNIFESLASHHITS,
	REC_KICKHITS,
	// Death tally
	REC_HEADDEATHS,
	REC_CHESTDEATHS,
	REC_STOMACHDEATHS,
	REC_LEGDEATHS,
	REC_MK23DEATHS,
	REC_M3DEATHS,
	REC_MP5DEATHS,
	REC_M4DEATHS,
	REC_SSG3000DEATHS,
	REC_HANDCANNONDEATHS,
	REC_AKIMBODEATHS,
	REC_GRENADEDEATHS,
	REC_KNIFETHROWDEATHS,
	REC_KNIFESLASHDEATHS,
	REC_KICKDEATHS,
	REC_BLEEDDEATHS,
	REC_FALLINGDEATHS,
	REC_SUICIDES,		// e.g. for MPELP award, those loonies :)
	REC_WORLDDEATHS,	// crushers, doors, etc.
	// Kill tally
	REC_HEADKILLS,
	REC_CHESTKILLS,
	REC_STOMACHKILLS,
	REC_LEGKILLS,
	REC_MK23KILLS,
	REC_M3KILLS,
	REC_MP5KILLS,
	REC_M4KILLS,
	REC_SSG3000KILLS,
	REC_HANDCANNONKILLS,
	REC_AKIMBOKILLS,
	REC_GRENADEKILLS,
	REC_KNIFETHROWKILLS,
	REC_KNIFESLASHKILLS,
	REC_KICKKILLS,
	REC_STEALTHKILLS,	// this is a derived record -- remove?
	// Movement tally - dunno about these ones since they are related to pmove
	REC_CAMPCOUNT,
	REC_CROUCHCOUNT,
	REC_JUMPCOUNT,		// e.g. rabbit or monkey award
	// Player interaction tally
	REC_FRAGSTEALS,		// this is a derived record -- remove?
	REC_CHATCOUNT,
	REC_GESTURECOUNT,
	REC_KILLS,		//How many kills - different then score
	//how many TK's
	REC_TEAMKILLS,
	REC_NUM_RECORDS
} rq3record_t;

//Elder: added
//
//bg_misc.c
//
int ClipAmountForReload(int w);
int ClipAmountForAmmo(int w);

// reward sounds (stored in ps->persistant[PERS_PLAYEREVENTS])
#define	PLAYEREVENT_DENIEDREWARD		0x0001
#define	PLAYEREVENT_GAUNTLETREWARD		0x0002
#define PLAYEREVENT_HOLYSHIT			0x0004

// entityState_t->event values
// entity events are for effects that take place reletive
// to an existing entities origin.  Very network efficient.

// two bits at the top of the entityState->event field
// will be incremented with each change in the event so
// that an identical event started twice in a row can
// be distinguished.  And off the value with ~EV_EVENT_BITS
// to retrieve the actual event number
#define	EV_EVENT_BIT1		0x00000100
#define	EV_EVENT_BIT2		0x00000200
#define	EV_EVENT_BITS		(EV_EVENT_BIT1|EV_EVENT_BIT2)

#define	EVENT_VALID_MSEC	300

typedef enum {
	EV_NONE,

	EV_FOOTSTEP,
	EV_FOOTSTEP_METAL,
	EV_FOOTSTEP_GRASS,	// Elder: new surfaces
	EV_FOOTSTEP_WOOD,
	EV_FOOTSTEP_CARPET,
	EV_FOOTSTEP_METAL2,
	EV_FOOTSTEP_GRAVEL,
	EV_FOOTSTEP_SNOW,	// JBravo: new surfaces
	EV_FOOTSTEP_MUD,
	EV_FOOTSTEP_WOOD2,
	EV_FOOTSTEP_HARDMETAL,
	EV_FOOTSTEP_LEAVES,	// Makro: new surfaces
	EV_FOOTSTEP_CEMENT,
	EV_FOOTSTEP_MARBLE,
	EV_FOOTSTEP_SNOW2,
	EV_FOOTSTEP_HARDSTEPS,
	EV_FOOTSTEP_SAND,
	EV_FOOTSPLASH,
	EV_FOOTWADE,
	EV_SWIM,

//Blaze: For exploding breakables
	EV_EXPLODE_BREAKABLE,

	EV_STEP_4,
	EV_STEP_8,
	EV_STEP_12,
	EV_STEP_16,

	EV_FALL_SHORT,
	EV_FALL_SHORT_NOSOUND,
	EV_FALL_MEDIUM,
	EV_FALL_MEDIUM_NOSOUND,
	EV_FALL_FAR,
	EV_FALL_FAR_NOSOUND,

	EV_JUMP_PAD,		// boing sound at origin, jump sound on player

	EV_JUMP,
	EV_WATER_TOUCH,		// foot touches
	EV_WATER_LEAVE,		// foot leaves
	EV_WATER_UNDER,		// head touches
	EV_WATER_CLEAR,		// head leaves

	EV_ITEM_PICKUP,		// normal item pickups are predictable
	EV_GLOBAL_ITEM_PICKUP,	// powerup / team sounds are broadcast to everyone

	EV_NOAMMO,
	EV_CHANGE_WEAPON,
	EV_FIRE_WEAPON,
	EV_RELOAD_WEAPON0,	// Elder: reload weapon sounds
	EV_RELOAD_WEAPON1,	// Elder: reload weapon sounds
	EV_RELOAD_WEAPON2,	// Elder: reload weapon sounds

	EV_USE_ITEM0,
	EV_USE_ITEM1,
	EV_USE_ITEM2,
	EV_USE_ITEM3,
	EV_USE_ITEM4,
	EV_USE_ITEM5,
	EV_USE_ITEM6,
	EV_USE_ITEM7,
	EV_USE_ITEM8,
	EV_USE_ITEM9,
	EV_USE_ITEM10,
	EV_USE_ITEM11,
	EV_USE_ITEM12,
	EV_USE_ITEM13,
	EV_USE_ITEM14,
	EV_USE_ITEM15,

	EV_ITEM_RESPAWN,
	EV_ITEM_POP,
	EV_PLAYER_TELEPORT_IN,
	EV_PLAYER_TELEPORT_OUT,

	EV_GRENADE_BOUNCE,	// eventParm will be the soundindex

	EV_GENERAL_SOUND,
	EV_GLOBAL_SOUND,	// no attenuation
	EV_GLOBAL_TEAM_SOUND,
	EV_RQ3_SOUND,		// Elder: play local sounds - intended for kick

	EV_DMREWARD,		// Duffman: To display expotional reward messages.

	EV_BULLET_HIT_FLESH,
	EV_BULLET_HIT_WALL,
	EV_BULLET_HIT_METAL,	// Elder: sparks
	EV_BULLET_HIT_KEVLAR,	// Elder: sparks
	EV_BULLET_HIT_GLASS,	// Elder: glass mark
	EV_BULLET_HIT_WOOD,	// Makro: new sound
	EV_BULLET_HIT_BRICK,	// Makro: new sound
	EV_BULLET_HIT_CERAMIC,	// Makro: new sound
	EV_SSG3000_HIT_FLESH,
	EV_JUMPKICK,		// Elder: sound + jumpkick message
	EV_EJECTBLOOD,		// Elder: when bleeding, every 2s release blood

	EV_MISSILE_HIT,
	EV_MISSILE_MISS,
	EV_MISSILE_MISS_METAL,
	EV_KNIFE_MISS,		// Elder: knife slash stuff
	EV_RAILTRAIL,
	EV_SHOTGUN,
	EV_HANDCANNON,
	EV_BULLET,		// otherEntity is the shooter

	EV_HEADSHOT,		// Elder: spray like SSG shot
	EV_PAIN,
	EV_DEATH1,
	EV_DEATH2,
	EV_DEATH3,
	EV_OBITUARY,
	EV_OBITUARY_HEAD,
	EV_OBITUARY_CHEST,
	EV_OBITUARY_STOMACH,
	EV_OBITUARY_LEGS,

	EV_GIB_PLAYER,		// gib a previously living player
	EV_GIB_PLAYER_HEADSHOT,	// JBravo: for sniper head shots
	EV_GIB_PLAYER_STOMACH,	// JBravo: for sniper stomach shots
	EV_BREAK_GLASS1,	// Blaze: Breakable glass
	EV_BREAK_GLASS2,
	EV_BREAK_GLASS3,
	EV_CHIP_GLASS,		//Blaze: this even just breaks it a little bit.
	EV_PRESSURE,		// NiceAss: an entity under pressure
	EV_SCOREPLUM,		// score plum

	EV_PROXIMITY_MINE_STICK,
	EV_PROXIMITY_MINE_TRIGGER,
	EV_KAMIKAZE,		// kamikaze explodes
	EV_OBELISKEXPLODE,	// obelisk explodes
	EV_OBELISKPAIN,		// obelisk is in pain
	EV_INVUL_IMPACT,	// invulnerability sphere impact
	EV_JUICED,		// invulnerability juiced effect
	EV_LIGHTNINGBOLT,	// lightning bolt bounced of invulnerability sphere

	EV_INSANESOUND,		// JBravo: for insanesounds
	EV_DEBUG_LINE,
	EV_STOPLOOPINGSOUND,
	EV_TAUNT,
	EV_TAUNT_YES,
	EV_TAUNT_NO,
	EV_TAUNT_FOLLOWME,
	EV_TAUNT_GETFLAG,
	EV_TAUNT_GUARDBASE,
	EV_TAUNT_PATROL
} entity_event_t;

typedef enum {
	GTS_RED_CAPTURE,
	GTS_BLUE_CAPTURE,
	GTS_RED_RETURN,
	GTS_BLUE_RETURN,
	GTS_RED_TAKEN,
	GTS_BLUE_TAKEN,
	GTS_REDOBELISK_ATTACKED,
	GTS_BLUEOBELISK_ATTACKED,
	GTS_REDTEAM_SCORED,
	GTS_BLUETEAM_SCORED,
	GTS_REDTEAM_TOOK_LEAD,
	GTS_BLUETEAM_TOOK_LEAD,
	GTS_TEAMS_ARE_TIED,
	GTS_KAMIKAZE
} global_team_sound_t;

// animations
typedef enum {
	BOTH_DEATH1,
	BOTH_DEAD1,
	BOTH_DEATH2,
	BOTH_DEAD2,
	BOTH_DEATH3,
	BOTH_DEAD3,

	TORSO_GESTURE,

	TORSO_ATTACK,
	TORSO_ATTACK2,

	TORSO_DROP,
	TORSO_RAISE,

	TORSO_STAND,
	TORSO_STAND2,

	LEGS_WALKCR,
	LEGS_WALK,
	LEGS_RUN,
	LEGS_BACK,
	LEGS_SWIM,

	LEGS_JUMP,
	LEGS_LAND,

	LEGS_JUMPB,
	LEGS_LANDB,

	LEGS_IDLE,
	LEGS_IDLECR,

	LEGS_TURN,
//Blaze: Weapon reload animation
//      WEAPON_RELOAD,

	TORSO_GETFLAG,
	TORSO_GUARDBASE,
	TORSO_PATROL,
	TORSO_FOLLOWME,
	TORSO_AFFIRMATIVE,
	TORSO_NEGATIVE,

	MAX_ANIMATIONS,

	LEGS_BACKCR,
	LEGS_BACKWALK,
	FLAG_RUN,
	FLAG_STAND,
	FLAG_STAND2RUN,

	MAX_TOTALANIMATIONS
} animNumber_t;

typedef struct animation_s {
	int firstFrame;
	int numFrames;
	int loopFrames;		// 0 to numFrames
	int frameLerp;		// msec between frames
	int initialLerp;	// msec to get to first frame
	int reversed;		// true if animation is reversed
	int flipflop;		// true if animation should flipflop back to base
} animation_t;

// flip the togglebit every time an animation
// changes so a restart of the same anim can be detected
#define	ANIM_TOGGLEBIT		128

typedef enum {
	TEAM_FREE,
	TEAM_RED,
	TEAM_BLUE,
	TEAM_SPECTATOR,

	TEAM_NUM_TEAMS
} team_t;

// Time between location updates
#define TEAM_LOCATION_UPDATE_TIME		1000

// How many players on the overlay
#define TEAM_MAXOVERLAY		32

// Begin Duffman
// Location Damage
// Height layers
#define LOCATION_NONE           0x00000000

#define LOCATION_HEAD           0x00000001	// [F,B,L,R] Top of head
#define LOCATION_FACE           0x00000002	// [F] Face [B,L,R] Head
#define LOCATION_SHOULDER       0x00000004	// [L,R] Shoulder [F] Throat, [B] Neck
#define LOCATION_CHEST          0x00000008	// [F] Chest [B] Back [L,R] Arm
#define LOCATION_STOMACH        0x00000010	// [L,R] Sides [F] Stomach [B] Lower Back
#define LOCATION_GROIN          0x00000020	// [F] Groin [B] Butt [L,R] Hip
#define LOCATION_LEG            0x00000040	// [F,B,L,R] Legs
#define LOCATION_FOOT           0x00000080	// [F,B,L,R] Bottom of Feet

// Relative direction strike came from

#define LOCATION_LEFT           0x00000100
#define LOCATION_RIGHT          0x00000200
#define LOCATION_FRONT          0x00000400
#define LOCATION_BACK           0x00000800
// End Duffman

//team task
typedef enum {
	TEAMTASK_NONE,
	TEAMTASK_OFFENSE,
	TEAMTASK_DEFENSE,
	TEAMTASK_PATROL,
	TEAMTASK_FOLLOW,
	TEAMTASK_RETRIEVE,
	TEAMTASK_ESCORT,
	TEAMTASK_CAMP
} teamtask_t;

// means of death
typedef enum {
	MOD_UNKNOWN,
	MOD_SHOTGUN,
	MOD_GAUNTLET,
	MOD_MACHINEGUN,
	MOD_GRENADE,
	MOD_GRENADE_SPLASH,
	MOD_ROCKET,
	MOD_ROCKET_SPLASH,
	MOD_PLASMA,
	MOD_PLASMA_SPLASH,
	MOD_RAILGUN,
	MOD_LIGHTNING,
	MOD_BFG,
	MOD_BFG_SPLASH,
	MOD_WATER,
	MOD_SLIME,
	MOD_LAVA,
	MOD_CRUSH,
	MOD_TELEFRAG,
	MOD_FALLING,
	MOD_SUICIDE,
	MOD_TARGET_LASER,
	MOD_TRIGGER_HURT,
	MOD_GRAPPLE,
	//Blaze: Reaction Deaths
	MOD_KNIFE,
	MOD_KNIFE_THROWN,
	MOD_PISTOL,
	MOD_M4,
	MOD_SNIPER,
	MOD_MP5,
	MOD_AKIMBO,
	MOD_M3,
	MOD_HANDCANNON,
	MOD_KICK,
	MOD_BLEEDING
} meansOfDeath_t;

//---------------------------------------------------------

// gitem_t->type
typedef enum {
	IT_BAD,
	IT_WEAPON,		// EFX: rotate + upscale + minlight
	IT_AMMO,		// EFX: rotate
	IT_ARMOR,		// EFX: rotate + minlight
	IT_HEALTH,		// EFX: static external sphere + rotating internal
	IT_POWERUP,		// instant on, timer based
	// EFX: rotate + external ring that rotates
	IT_HOLDABLE,		// single use, holdable item
	// EFX: rotate + bob
	IT_PERSISTANT_POWERUP,
	IT_TEAM
} itemType_t;

#define MAX_ITEM_MODELS 4

typedef struct gitem_s {
	char *classname;	// spawning name
	char *pickup_sound;
	char *world_model[MAX_ITEM_MODELS];

	char *icon;
	char *pickup_name;	// for printing on pickup

	int quantity;		// for ammo how much, or duration of powerup
	itemType_t giType;	// IT_* flags

	int giTag;

	char *precaches;	// string of all models and images this item will use
	char *sounds;		// string of all sounds this item will use
} gitem_t;

// included in both the game dll and the client
extern gitem_t bg_itemlist[];
extern int bg_numItems;

gitem_t *BG_FindItem(const char *pickupName);
gitem_t *BG_FindItemForWeapon(weapon_t weapon);
gitem_t *BG_FindItemForPowerup(powerup_t pw);
gitem_t *BG_FindItemForHoldable(holdable_t pw);

#define	ITEM_INDEX(x) ((x)-bg_itemlist)

qboolean BG_CanItemBeGrabbed(int gametype, const entityState_t * ent, const playerState_t * ps);

// g_dmflags->integer flags
#define	DF_NO_FALLING			8
#define DF_FIXED_FOV			16
#define	DF_NO_FOOTSTEPS			32
#define DF_SPAWN_FARTHEST		512

// content masks
#define	MASK_ALL				(-1)
#define	MASK_SOLID				(CONTENTS_SOLID)
#define	MASK_PLAYERSOLID		(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_BODY)
#define	MASK_DEADSOLID			(CONTENTS_SOLID|CONTENTS_PLAYERCLIP)
#define	MASK_WATER				(CONTENTS_WATER|CONTENTS_LAVA|CONTENTS_SLIME)
#define	MASK_OPAQUE				(CONTENTS_SOLID|CONTENTS_SLIME|CONTENTS_LAVA)
#define	MASK_SHOT				(CONTENTS_SOLID|CONTENTS_BODY|CONTENTS_CORPSE)

//
// entityState_t->eType
//
typedef enum {
	ET_GENERAL,
	ET_PLAYER,
	ET_ITEM,
	ET_MISSILE,
	ET_MOVER,
	ET_BREAKABLE,		//Blaze: Breakable glass
	ET_PRESSURE,		//NiceAss: Pressure entities
	ET_BEAM,
	ET_PORTAL,
	ET_SPEAKER,
	ET_PUSH_TRIGGER,
	ET_TELEPORT_TRIGGER,
	ET_INVISIBLE,
	ET_GRAPPLE,		// grapple hooked on wall
	ET_TEAM,
	ET_LASER,		// lasersight entity type
	ET_DLIGHT,		// Elder: dynamic light entity
	ET_DECAL,		// Stick a decal on the ground

	ET_EVENTS		// any of the EV_* events can be added freestanding
	    // by setting eType to ET_EVENTS + eventNum
	    // this avoids having to set eFlags and eventNum
} entityType_t;

void BG_EvaluateTrajectory(const trajectory_t * tr, int atTime, vec3_t result);
void BG_EvaluateTrajectoryDelta(const trajectory_t * tr, int atTime, vec3_t result);

void BG_AddPredictableEventToPlayerstate(int newEvent, int eventParm, playerState_t * ps);

void BG_TouchJumpPad(playerState_t * ps, entityState_t * jumppad);

void BG_PlayerStateToEntityState(playerState_t * ps, entityState_t * s, qboolean snap);
void BG_PlayerStateToEntityStateExtraPolate(playerState_t * ps, entityState_t * s, int time, qboolean snap);

qboolean BG_PlayerTouchesItem(playerState_t * ps, entityState_t * item, int atTime);

#define ARENAS_PER_TIER		4
#define MAX_ARENAS			1024
#define	MAX_ARENAS_TEXT		8192

#define MAX_BOTS			1024
#define MAX_BOTS_TEXT		8192

// Kamikaze

// 1st shockwave times
#define KAMI_SHOCKWAVE_STARTTIME		0
#define KAMI_SHOCKWAVEFADE_STARTTIME	1500
#define KAMI_SHOCKWAVE_ENDTIME			2000
// explosion/implosion times
#define KAMI_EXPLODE_STARTTIME			250
#define KAMI_IMPLODE_STARTTIME			2000
#define KAMI_IMPLODE_ENDTIME			2250
// 2nd shockwave times
#define KAMI_SHOCKWAVE2_STARTTIME		2000
#define KAMI_SHOCKWAVE2FADE_STARTTIME	2500
#define KAMI_SHOCKWAVE2_ENDTIME			3000
// radius of the models without scaling
#define KAMI_SHOCKWAVEMODEL_RADIUS		88
#define KAMI_BOOMSPHEREMODEL_RADIUS		72
// maximum radius of the models during the effect
#define KAMI_SHOCKWAVE_MAXRADIUS		1320
#define KAMI_BOOMSPHERE_MAXRADIUS		720
#define KAMI_SHOCKWAVE2_MAXRADIUS		704

//Makro - for the new surfaceparm system

#define MAT_DEFAULT				0
#define MAT_METALSTEPS			1
#define MAT_GRAVEL				2
#define MAT_WOOD				3
#define MAT_CARPET				4
#define MAT_METAL2				5
#define MAT_GLASS				6
#define MAT_GRASS				7
#define MAT_SNOW				8
#define MAT_MUD					9
#define MAT_WOOD2				10
#define MAT_HARDMETAL			11
//new
#define MAT_LEAVES				12
#define MAT_CEMENT				13
#define MAT_MARBLE				14
#define MAT_SNOW2				15
#define MAT_HARDSTEPS			16
#define	MAT_SAND				17
#define	MAT_BRICK				18
#define	MAT_CERAMIC				19

int GetMaterialFromFlag(int flag);
qboolean IsMetalMat(int Material);
qboolean IsMetalFlag(int flag);
qboolean IsWoodMat(int Material);
qboolean IsWoodFlag(int flag);

holdable_t CharToItem(char *name, holdable_t defitem);
weapon_t CharToWeapon(char *name, weapon_t defweapon);

void PM_ClipVelocity(vec3_t in, vec3_t normal, vec3_t out, float overbounce);
