//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.138  2003/03/28 10:36:02  jbravo
// Tweaking the replacement system a bit.  Reactionmale now the default model
//
// Revision 1.137  2003/03/09 21:30:38  jbravo
// Adding unlagged.   Still needs work.
//
// Revision 1.136  2003/02/27 08:10:20  jbravo
// Added replacement model functionality for ammo
//
// Revision 1.135  2003/02/16 21:39:09  makro
// Fixed "timelimit is read only" on local servers error
//
// Revision 1.134  2003/02/05 20:21:38  jbravo
// Fixed the model replacement system.  Its no longer an ugly hack.
//
// Revision 1.133  2003/02/01 02:15:31  jbravo
// Replacement models and items
//
// Revision 1.132  2002/12/05 23:11:29  blaze
// Added item replacement code
//
// Revision 1.131  2002/12/02 19:52:05  niceass
// water pressure & shell ejection stuff
//
// Revision 1.130  2002/11/18 04:39:47  jbravo
// Cleanup of cg_weapons.c
//
// Revision 1.129  2002/10/30 20:04:34  jbravo
// Adding helmet
//
// Revision 1.128  2002/10/21 21:01:09  niceass
// no ref ready code
//
// Revision 1.127  2002/10/20 21:24:32  blaze
// Added cg_RQ3_gunname cvars.  These can be used to choose weapon replacements.  You will need 3 icons that I will upload to the ftp.  These should go in the next pk3
//
// Revision 1.126  2002/09/01 21:14:37  makro
// Sky portal tweaks
//
// Revision 1.125  2002/08/29 23:58:28  makro
// Sky portals
//
// Revision 1.124  2002/08/29 14:24:43  niceass
// new wallhack thing
//
// Revision 1.123  2002/08/29 04:42:40  blaze
// Anti OGC code
//
// Revision 1.122  2002/08/28 23:10:06  jbravo
// Added cg_RQ3_SuicideLikeARealMan, timestamping to server logs and
// fixed stats for non-TP modes.
//
// Revision 1.121  2002/08/28 18:52:09  jbravo
// Added the Keanu male radio sound set.
//
// Revision 1.120  2002/08/27 05:10:42  niceass
// new ctb marker shader names
//
// Revision 1.119  2002/08/25 07:08:41  niceass
// added "life" setting to func_pressure
//
// Revision 1.118  2002/08/25 00:45:24  niceass
// q3f atmosphere
//
// Revision 1.117  2002/08/24 08:01:11  niceass
// new ref system for scoreboard
//
// Revision 1.116  2002/08/22 03:30:20  niceass
// countdown code added
//
// Revision 1.115  2002/08/07 04:45:07  niceass
// ctb changes
//
// Revision 1.114  2002/08/07 03:35:57  jbravo
// Added dynamic radio and stopped all radio usage during lca
//
// Revision 1.113  2002/08/03 06:52:35  jbravo
// Fixed the plost3 sound in all radiopaks and now damage is only tracked for
// players you hit that are not on your team
//
// Revision 1.112  2002/07/26 22:28:38  jbravo
// Fixed the server about menu, made the UI handle illegal models and skins
// better.
//
// Revision 1.111  2002/07/26 06:21:43  jbravo
// Fixed the MM settings stuff so it works on remote servers also.
// Removed the MM_NAMES_COLOR since it broke on nicks with color in them.
//
// Revision 1.110  2002/07/21 18:46:32  niceass
// weaponprediction cvar added
//
// Revision 1.109  2002/07/20 02:25:53  jbravo
// Added the AQDT CTB sounds to the base radio paks
//
// Revision 1.108  2002/07/19 04:40:56  jbravo
// Added 2 new radio sets and ctb radio sound support
//
// Revision 1.107  2002/07/19 04:32:42  niceass
// added marker support for ctb
//
// Revision 1.106  2002/07/13 22:42:18  makro
// Semi-working fog hull, semi-working sky portals (cgame code commented out)
// Basically, semi-working stuff :P
//
// Revision 1.105  2002/07/08 04:25:29  niceass
// removed deaths
//
// Revision 1.104  2002/07/07 18:36:13  jbravo
// Added an AntiIdle system. Can play insane sounds for idle players, drop them
// from teams or kick them.   Upped version to Beta 2.1
//
// Revision 1.103  2002/06/30 17:33:01  jbravo
// New radio sounds and the 0wned sound was added.
//
// Revision 1.102  2002/06/24 05:55:24  niceass
// drawping
//
// Revision 1.101  2002/06/23 04:36:02  niceass
// change to foglaser
//
// Revision 1.100  2002/06/21 23:20:34  blaze
// cg_RQ3_overlaycrosshair when set to 1 will draw your non zoomed crosshair overtop of your ssg crosshair
//
// Revision 1.99  2002/06/21 21:05:57  niceass
// laserfog stuff & removed unused cvar
//
// Revision 1.98  2002/06/21 04:10:59  niceass
// fog laser
//
// Revision 1.97  2002/06/19 05:17:57  niceass
// scoreboard stuff
//
// Revision 1.96  2002/06/16 23:26:23  blaze
// fixed to allow > 16 breakables
//
// Revision 1.95  2002/06/16 20:06:13  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.94  2002/06/16 19:12:52  jbravo
// Removed the MISSIONPACK ifdefs and missionpack only code.
//
// Revision 1.93  2002/06/12 23:05:14  slicer
// SSG Zooming final tweak
//
// Revision 1.92  2002/06/12 22:31:59  slicer
// Even better way to improve the Cvar Anti-Cheat System
//
// Revision 1.91  2002/06/12 15:30:24  slicer
// Improved and fixed the Anti-Cheat System
//
// Revision 1.90  2002/06/11 22:49:42  niceass
// HC brass
//
// Revision 1.89  2002/06/10 14:02:31  slicer
// Removed rq3_cmd : ROUND , associated to cg_RQ3_team_round_going that wasn't being used
//
// Revision 1.88  2002/06/10 13:20:03  slicer
// RefID is now passed trought scoreboard, no more lca cvar, only cg.lca
//
// Revision 1.87  2002/06/09 05:16:17  niceass
// pressure change
//
// Revision 1.86  2002/06/06 01:54:26  niceass
// pressure change
//
// Revision 1.85  2002/06/05 23:36:07  niceass
// "ready" command lag fix
//
// Revision 1.84  2002/06/03 00:48:10  niceass
// match scoreboard changes
//
// Revision 1.83  2002/05/28 01:17:01  jbravo
// More gib fixes.  g_RQ3_gib added
//
// Revision 1.82  2002/05/27 07:02:11  niceass
// reflection changes
//
// Revision 1.81  2002/05/26 05:13:08  niceass
// pressure and progress stuff
//
// Revision 1.80  2002/05/21 14:59:11  makro
// cg_RQ3_avidemo
//
// Revision 1.79  2002/05/19 21:27:51  blaze
// added force and buoyancy to breakables
//
// Revision 1.78  2002/05/19 21:04:37  jbravo
// Tkok popup system
//
// Revision 1.77  2002/05/19 18:32:11  jbravo
// Made new cvars for regular xhair colors.
//
// Revision 1.76  2002/05/18 21:58:53  blaze
// cg_RQ3_autoaction support
//
// Revision 1.75  2002/05/18 03:55:35  niceass
// many misc. changes
//
// Revision 1.74  2002/05/12 14:39:48  makro
// Wood, brick & ceramic impact sounds
//
// Revision 1.73  2002/05/11 19:55:20  slicer
// Added sub and captain to the scoreboard parser
//
// Revision 1.72  2002/05/11 19:13:42  makro
// Sand surfaceparm
//
// Revision 1.71  2002/05/11 15:40:41  slicer
// Changed cg_RQ3_<team count> cvars to ui_RQ3_ and added a synch system for these
//
// Revision 1.70  2002/05/09 06:45:14  niceass
// New tracers
//
// Revision 1.69  2002/04/30 11:20:12  jbravo
// Redid the teamcount cvars.
//
// Revision 1.68  2002/04/29 06:11:28  niceass
// centerprint, pressure and matchmode stuff
//
// Revision 1.67  2002/04/23 06:08:24  niceass
// scoreboard stuff
//
// Revision 1.66  2002/04/20 15:05:08  makro
// More footstep sounds, a few other things
//
// Revision 1.65  2002/04/18 16:13:23  jbravo
// Scoreboard now shows green for live players and white for dead.
// Time should not get reset on deaths any more.
//
// Revision 1.64  2002/04/07 12:49:53  slicer
// Added 'teamname' command for MM, and tweaked the cvar system.
//
// Revision 1.63  2002/04/03 03:13:48  blaze
// NEW BREAKABLE CODE - will break all old breakables(wont appear in maps)
//
// Revision 1.62  2002/03/31 02:03:13  niceass
// added tag declaration
//
// Revision 1.61  2002/03/30 23:20:10  jbravo
// Added damage in scoreboard.
//
// Revision 1.60  2002/03/30 21:51:42  jbravo
// Removed all those ifdefs for zcam.
//
// Revision 1.59  2002/03/24 22:48:29  niceass
// cg_draw change for scoreboard
//
// Revision 1.58  2002/03/23 05:50:47  jbravo
// Moved enableDust out of the missionpack
//
// Revision 1.57  2002/03/23 05:17:42  jbravo
// Major cleanup of game -> cgame communication with LCA vars.
//
// Revision 1.56  2002/03/21 15:02:05  jbravo
// More teamname cleanups and fix for fraglines.
//
// Revision 1.55  2002/03/21 02:17:39  blaze
// more func_explosive goodness
//
// Revision 1.54  2002/03/17 21:32:23  jbravo
// Fixed the dynamic teamnames system up a bit to reduce traffic
//
// Revision 1.53  2002/03/16 21:50:09  niceass
// All new shell ejection code
//
// Revision 1.52  2002/03/14 16:04:26  slicer
// Optimization on radio parsing
//
// Revision 1.51  2002/03/14 02:24:39  jbravo
// Adding radio :)
//
// Revision 1.50  2002/03/11 02:25:38  niceass
// client gravity fix/tag shell ejection
//
// Revision 1.49  2002/02/28 05:41:54  blaze
// weapons stats on client side
//
// Revision 1.48  2002/02/10 08:17:08  niceass
// many changes to scoreboard (deaths/second mode)
//
// Revision 1.47  2002/02/10 02:49:13  niceass
// re-added zcam #define
//
// Revision 1.46  2002/02/08 05:52:18  niceass
// cg_drawcleanrect declaration added.
//
// Revision 1.45  2002/02/05 23:42:06  slicer
// More on matchmode..
//
// Revision 1.44  2002/02/04 02:17:39  jbravo
// scoreStartTime definition missing
//
// Revision 1.43  2002/02/04 00:11:12  slicer
// Matchmode: Teams Ready/Not Ready goes by cvar MM_team1/2
//
// Revision 1.42  2002/01/30 07:37:25  niceass
// EnableBreath added for mappers (TA thing)
//
// Revision 1.41  2002/01/24 14:20:53  jbravo
// Adding func_explosive and a few new surfaceparms
//
// Revision 1.40  2002/01/14 01:19:23  niceass
// No more default 800 gravity on items - NiceAss
//
// Revision 1.39  2002/01/11 20:20:57  jbravo
// Adding TP to main branch
//
// Revision 1.38  2002/01/11 19:48:29  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.37  2001/12/31 16:28:41  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
#include "../game/q_shared.h"
#include "tr_types.h"
#include "../game/bg_public.h"
#include "cg_public.h"

// The entire cgame module is unloaded and reloaded on each level change,
// so there is NO persistant data between levels on the client side.
// If you absolutely need something stored, it can either be kept
// by the server in the server stored userinfos, or stashed in a cvar.

#define	POWERUP_BLINKS		5

// NiceAss: Weapon scales
#define WEAPON_KNIFE_SCALE	1.5
#define WEAPON_GUN_SCALE 	1.2
#define WEAPON_OTHER_SCALE	1.0

#define	POWERUP_BLINK_TIME	1000
#define	FADE_TIME			200
#define	PULSE_TIME			200
#define	DAMAGE_DEFLECT_TIME	100
#define	DAMAGE_RETURN_TIME	400
#define DAMAGE_TIME			500
#define	LAND_DEFLECT_TIME	150
#define	LAND_RETURN_TIME	300
#define	STEP_TIME			200
#define	DUCK_TIME			100
#define	PAIN_TWITCH_TIME	200
#define	WEAPON_SELECT_TIME	1400
#define KICK_TIME			40	// Elder: default kick time, added for kick decay
// Elder: decreased from 1000
#define	ITEM_SCALEUP_TIME	250
#define	ZOOM_TIME			150
// Elder: increased from 200
#define	ITEM_BLOB_TIME		300
#define	MUZZLE_FLASH_TIME	20
#define	SINK_TIME			1000	// time for fragments to sink into ground before going away
#define	ATTACKER_HEAD_TIME	10000
#define	REWARD_TIME			3000

#define	PULSE_SCALE			1.5	// amount to scale up the icons when activating

#define	MAX_STEP_CHANGE		32

#define	MAX_VERTS_ON_POLY	10
#define	MAX_MARK_POLYS		256

#define STAT_MINUS			10	// num frame for '-' stats digit

#define	ICON_SIZE			48
//Elder: small icon size added
#define SMICON_SIZE			32
#define	CHAR_WIDTH			32
#define	CHAR_HEIGHT			48
#define	TEXT_ICON_SPACE		4

#define	TEAMCHAT_WIDTH		80
#define TEAMCHAT_HEIGHT		8

// very large characters
#define	GIANT_WIDTH			32
#define	GIANT_HEIGHT		48

#define	NUM_CROSSHAIRS		10

#define TEAM_OVERLAY_MAXNAME_WIDTH	12
#define TEAM_OVERLAY_MAXLOCATION_WIDTH	16

// JBravo: used to store replacement models
#define MAX_MODEL_LEN 128

// Elder: changed to good ol' resdog
#define	DEFAULT_MODEL			"reactionmale"
// Elder: this is added
#define	DEFAULT_SKIN			"default"

#define	DEFAULT_TEAM_MODEL		"reactionmale"
#define	DEFAULT_TEAM_HEAD		"reactionmale"

// Elder: Changed
#define DEFAULT_REDTEAM_NAME		"Reservoir Dogs"
#define DEFAULT_BLUETEAM_NAME		"Psychos"

// Elder: Some ssg stuff
#define ZOOM_LEVELS		3
#define ZOOM_PREPTIME	10	//milliseconds
// Elder: Zoom status
#define ZOOM_OUTOFAMMO	-1	// stay in current FOV even when firing
#define ZOOM_IDLE	0	// stay in current FOV if not firing or reloading
#define ZOOM_OUT	1	// switch to 90 degree FOV

// Elder: max number of "blood" marks when hitting a player w/ shell weapons
#define MAX_SHELL_HITS	6

typedef enum {
	FOOTSTEP_NORMAL,
	FOOTSTEP_BOOT,
	FOOTSTEP_FLESH,
	FOOTSTEP_MECH,
	FOOTSTEP_ENERGY,
	FOOTSTEP_METAL,
	FOOTSTEP_SPLASH,
	// Elder: new surface sounds
	FOOTSTEP_GRAVEL,
	FOOTSTEP_WOOD,
	FOOTSTEP_CARPET,
	FOOTSTEP_METAL2,
	FOOTSTEP_GLASS,
	FOOTSTEP_GRASS,
	// JBravo: new surface sounds
	FOOTSTEP_SNOW,
	FOOTSTEP_MUD,
	FOOTSTEP_WOOD2,
	FOOTSTEP_HARDMETAL,
	// Makro: more sounds
	FOOTSTEP_LEAVES,
	FOOTSTEP_CEMENT,
	FOOTSTEP_MARBLE,
	FOOTSTEP_SNOW2,
	FOOTSTEP_HARDSTEPS,
	FOOTSTEP_SAND,

	FOOTSTEP_TOTAL
} footstep_t;

typedef enum {
	IMPACTSOUND_DEFAULT,
	IMPACTSOUND_METAL,
	IMPACTSOUND_FLESH,
	// rq3 onwards
	IMPACTSOUND_GLASS,
	//Makro - added
	IMPACTSOUND_BRICK,
	IMPACTSOUND_WOOD,
	IMPACTSOUND_CERAMIC
} impactSound_t;

//Blaze: anti cheat stuff
typedef struct {
	char cvar[40];
	float low;
	float high;
} cheat_cvar;

//=================================================

// player entities need to track more information
// than any other type of entity.

// note that not every player entity is a client entity,
// because corpses after respawn are outside the normal
// client numbering range

// when changing animation, set animationTime to frameTime + lerping time
// The current lerp will finish out, then it will lerp to the new animation
typedef struct {
	int oldFrame;
	int oldFrameTime;	// time when ->oldFrame was exactly on

	int frame;
	int frameTime;		// time when ->frame will be exactly on

	float backlerp;

	float yawAngle;
	qboolean yawing;
	float pitchAngle;
	qboolean pitching;

	int animationNumber;	// may include ANIM_TOGGLEBIT
	animation_t *animation;
	int animationTime;	// time when the first frame of the animation will be exact
} lerpFrame_t;

typedef struct {
	lerpFrame_t legs, torso, flag;
	int painTime;
	int painDirection;	// flip from 0 to 1
	int lightningFiring;

	// railgun trail spawning
	vec3_t railgunImpact;
	qboolean railgunFlash;

	// machinegun spinning
	float barrelAngle;
	int barrelTime;
	qboolean barrelSpinning;
	qboolean noHead;
	//Blaze: for weapon animations
	lerpFrame_t weapon;
} playerEntity_t;

//=================================================

// centity_t have a direct corespondence with gentity_t in the game, but
// only the entityState_t is directly communicated to the cgame
typedef struct centity_s {
	entityState_t currentState;	// from cg.frame
	entityState_t nextState;	// from cg.nextFrame, if available
	qboolean interpolate;	// true if next is valid to interpolate to
	qboolean currentValid;	// true if cg.frame holds this entity

	int muzzleFlashTime;	// move to playerEntity?
	int ejectBrassTime;	// NiceAss: set when the weapon should eject a shell
	int previousEvent;
	int teleportFlag;

	int trailTime;		// so missile trails can handle dropped initial packets
	int dustTrailTime;
	int miscTime;

	int snapShotTime;	// last time this entity was found in a snapshot

	playerEntity_t pe;

	int errorTime;		// decay the error from this time
	vec3_t errorOrigin;
	vec3_t errorAngles;

	qboolean extrapolated;	// false if origin / angles is an interpolation
	vec3_t rawOrigin;
	vec3_t rawAngles;

	vec3_t beamEnd;

	// exact interpolated position of entity on this frame
	vec3_t lerpOrigin;
	vec3_t lerpAngles;
} centity_t;

//======================================================================

// local entities are created as a result of events or predicted actions,
// and live independantly from all server transmitted entities

typedef struct markPoly_s {
	struct markPoly_s *prevMark, *nextMark;
	int time;
	qhandle_t markShader;
	qboolean alphaFade;	// fade alpha instead of rgb
	float color[4];
	poly_t poly;
	polyVert_t verts[MAX_VERTS_ON_POLY];
} markPoly_t;

typedef enum {
	LE_MARK,
	LE_EXPLOSION,
	LE_SPRITE_EXPLOSION,
	LE_FRAGMENT,
	LE_MOVE_SCALE_FADE,
	LE_FALL_SCALE_FADE,
	LE_FADE_RGB,
	LE_SCALE_FADE,
	LE_SCOREPLUM,
	LE_PRESSURE,
	LE_TRACER,
} leType_t;

typedef enum {
	LEF_PUFF_DONT_SCALE = 0x0001,	// do not scale size over time
	LEF_TUMBLE = 0x0002,	// tumble over time, used for ejecting shells
	LEF_SOUND1 = 0x0004,	// sound 1 for kamikaze
	LEF_SOUND2 = 0x0008,	// sound 2 for kamikaze
	LEF_STEAM = 0x0010,	// NiceAss: For pressure entities
	LEF_FLAME = 0x0020,
	LEF_AIR = 0x0040,
	LEF_WATER = 0x0080
} leFlag_t;

typedef enum {
	LEMT_NONE,
	LEMT_BURN,
	LEMT_BLOOD
} leMarkType_t;			// fragment local entities can leave marks on walls

typedef enum {
	LEBS_NONE,
	LEBS_BLOOD,
	LEBS_BRASS
} leBounceSoundType_t;		// fragment local entities can make sounds on impacts

typedef struct localEntity_s {
	struct localEntity_s *prev, *next;
	leType_t leType;
	int leFlags;

	int startTime;
	int endTime;
	int fadeInTime;

	float lifeRate;		// 1.0 / (endTime - startTime)

	trajectory_t pos;
	trajectory_t angles;

	float bounceFactor;	// 0.0 = no bounce, 1.0 = perfect

	float color[4];

	float radius;

	float light;
	vec3_t lightColor;

	leMarkType_t leMarkType;	// mark to leave on fragment impact
	leBounceSoundType_t leBounceSoundType;

	refEntity_t refEntity;
	
	// JBravo: for func_explosive
	float size;
	// NiceAss: for func_pressure
	int life;
} localEntity_t;

//======================================================================

typedef struct {
	int client;
	int score;
	int damage;
	int alive;
	int ping;
	int time;
	int scoreFlags;
	int powerUps;
	int accuracy;
	int team;
	//Slicer Matchmode
	team_t captain;
	team_t sub;
	qboolean referee;
} score_t;

//Blaze: WeaponStats Struct

// each client has an associated clientInfo_t
// that contains media references necessary to present the
// client model and other color coded effects
// this is regenerated each time a client's configstring changes,
// usually as a result of a userinfo (name, model, etc) change
#define	MAX_CUSTOM_SOUNDS	32

typedef struct {
	qboolean infoValid;

	char name[MAX_QPATH];
	team_t team;

	int botSkill;		// 0 = not bot, 1-5 = bot

	vec3_t color1;
	vec3_t color2;

	int score;		// updated by score servercmds
	int location;		// location index for team mode
	int health;		// you only get this info about your teammates
	int armor;
	int curWeapon;

	int handicap;
	int wins, losses;	// in tourney mode

	int teamTask;		// task in teamplay (offence/defence)
	qboolean teamLeader;	// true when this is a team leader

	int powerups;		// so can display quad/flag status

	int medkitUsageTime;
	int invulnerabilityStartTime;
	int invulnerabilityStopTime;

	int breathPuffTime;

	// when clientinfo is changed, the loading of models/skins/sounds
	// can be deferred until you are dead, to prevent hitches in
	// gameplay
	char modelName[MAX_QPATH];
	char skinName[MAX_QPATH];
	char headModelName[MAX_QPATH];
	char headSkinName[MAX_QPATH];
	char redTeam[MAX_TEAMNAME];
	char blueTeam[MAX_TEAMNAME];
	qboolean deferred;

	qboolean newAnims;	// true if using the new mission pack animations
	qboolean fixedlegs;	// true if legs yaw is always the same as torso yaw
	qboolean fixedtorso;	// true if torso never changes yaw

	vec3_t headOffset;	// move head in icon views
	footstep_t footsteps;
	gender_t gender;	// from model

	qhandle_t legsModel;
	qhandle_t legsSkin;

	qhandle_t torsoModel;
	qhandle_t torsoSkin;

	qhandle_t headModel;
	qhandle_t headSkin;

	qhandle_t modelIcon;

	animation_t animations[MAX_TOTALANIMATIONS];

	sfxHandle_t sounds[MAX_CUSTOM_SOUNDS];
} clientInfo_t;

// Elder: maximum sizes
#define MAX_RELOAD_SOUNDS		5
#define MAX_OTHER_SOUNDS		5

#define MAX_ANIM_SOUNDS			16

struct sfxSyncInfo_s {
	int frame;
	sfxHandle_t sound;
	qboolean played;
};

typedef struct sfxSyncInfo_s sfxSyncInfo_t;

typedef struct {
	int numFrames;
	sfxSyncInfo_t sfxInfo[MAX_ANIM_SOUNDS];
} sfxWeapTiming_t;

// each WP_* weapon enum has an associated weaponInfo_t
// that contains media references necessary to present the
// weapon and its effects
typedef struct weaponInfo_s {
	qboolean registered;
	gitem_t *item;

	qhandle_t handsModel;	// the hands don't actually draw, they just position the weapon
	qhandle_t weaponModel;	// Third-person/world model
	qhandle_t barrelModel;
	qhandle_t flashModel;
	qhandle_t customSkin;	// JBravo: for custom skins

	qhandle_t firstModel;	//Elder: view model
	qhandle_t animHandModel;	//Blaze: for animations
	animation_t animations[MAX_WEAPON_ANIMATIONS];

	vec3_t weaponMidpoint;	// so it will rotate centered instead of by tag

	float flashDlight;
	vec3_t flashDlightColor;
	sfxHandle_t flashSound[4];	// fast firing weapons randomly choose

	qhandle_t weaponIcon;
	qhandle_t ammoIcon;

	qhandle_t ammoModel;
	qhandle_t ammocustomSkin;

	qhandle_t missileModel;
	sfxHandle_t missileSound;
	void (*missileTrailFunc) (centity_t *, const struct weaponInfo_s * wi);
	float missileDlight;
	vec3_t missileDlightColor;
	int missileRenderfx;

	//void                  (*ejectBrassFunc)( centity_t *, vec3_t, vec3_t );
	localEntity_t *(*ejectBrassFunc) (centity_t * cent);

	float trailRadius;
	float wiTrailTime;

	sfxHandle_t readySound;
	sfxHandle_t firingSound;

	// Elder: sounds to queue
	sfxWeapTiming_t animationSounds[MAX_ANIM_SOUNDS];
	sfxHandle_t worldReloadSound[3];

	qboolean loopFireSound;
} weaponInfo_t;

// each IT_* item has an associated itemInfo_t
// that constains media references necessary to present the
// item and its effects
typedef struct {
	qboolean registered;
	qhandle_t models[MAX_ITEM_MODELS];
	qhandle_t icon;
// JBravo: for customskins
	qhandle_t customSkin;
} itemInfo_t;

typedef struct {
	int itemNum;
} powerupInfo_t;

#define MAX_SKULLTRAIL		10

typedef struct {
	vec3_t positions[MAX_SKULLTRAIL];
	int numpositions;
} skulltrail_t;

#define MAX_REWARDSTACK		10
#define MAX_SOUNDBUFFER		20

//======================================================================

// all cg.stepTime, cg.duckTime, cg.landTime, etc are set to cg.time when the action
// occurs, and they will have visible effects for #define STEP_TIME or whatever msec after

#define MAX_PREDICTED_EVENTS	16

// JBravo: unlagged
#define NUM_SAVED_STATES (CMD_BACKUP + 2)

typedef struct {
	int clientFrame;	// incremented each frame

	int clientNum;

	qboolean demoPlayback;
	qboolean levelShot;	// taking a level menu screenshot
	int deferredPlayerLoading;
	qboolean loading;	// don't defer players at initial startup
	qboolean intermissionStarted;	// don't play voice rewards, because game will end shortly

	// there are only one or two snapshot_t that are relevent at a time
	int latestSnapshotNum;	// the number of snapshots the client system has received
	int latestSnapshotTime;	// the time from latestSnapshotNum, so we don't need to read the snapshot yet

	snapshot_t *snap;	// cg.snap->serverTime <= cg.time
	snapshot_t *nextSnap;	// cg.nextSnap->serverTime > cg.time, or NULL
	snapshot_t activeSnapshots[2];

	float frameInterpolation;	// (float)( cg.time - cg.frame->serverTime ) / (cg.nextFrame->serverTime - cg.frame->serverTime)

	qboolean thisFrameTeleport;
	qboolean nextFrameTeleport;

	int frametime;		// cg.time - cg.oldTime

	int time;		// this is the time value that the client
	// is rendering at.
	int oldTime;		// time at last frame, used for missile trails and prediction checking

	int cvarCheckTime;	// Elder: used for cvar cheat interval cycling

	int screenshotTime;	// Makro - avidemo with jpegs

	int physicsTime;	// either cg.snap->time or cg.nextSnap->time

	int timelimitWarnings;	// 5 min, 1 min, overtime
	int fraglimitWarnings;

	qboolean mapRestart;	// set on a map restart to set back the weapon

	qboolean renderingThirdPerson;	// during deaths, chasecams, etc

	// prediction state
	qboolean hyperspace;	// true if prediction has hit a trigger_teleport
	playerState_t predictedPlayerState;
	centity_t predictedPlayerEntity;
	qboolean validPPS;	// clear until the first call to CG_PredictPlayerState
	int predictedErrorTime;
	vec3_t predictedError;

	int eventSequence;
	int predictableEvents[MAX_PREDICTED_EVENTS];

	float stepChange;	// for stair up smoothing
	int stepTime;

	float duckChange;	// for duck viewheight smoothing
	int duckTime;

	float landChange;	// for landing hard
	int landTime;

	// input state sent to server
	int weaponSelect;

	// auto rotating items
	vec3_t autoAngles;
	vec3_t autoAxis[3];
	vec3_t autoAnglesFast;
	vec3_t autoAxisFast[3];

	// view rendering
	refdef_t refdef;
	vec3_t refdefViewAngles;	// will be converted to refdef.viewaxis

	// zoom key
	qboolean zooming;	//Slicer: flag to determine when to set zoomTime
	qboolean zoomed;	// Determines first-person weapon drawing
	int zoomLevel;		// Zoom LEVEL! -- uses zoom bits like STAT_RQ3
	int lastZoomLevel;	// Save last zoom state
	int zoomFirstReturn;	// Elder: switch for zooming in/out between shots
	int zoomTime;
	float zoomSensitivity;

	// information screen text during loading
	char infoScreenText[MAX_STRING_CHARS];

	// scoreboard
	int scoresRequestTime;
	int numScores;
	int selectedScore;
	int teamScores[2];
	score_t scores[MAX_CLIENTS];
	qboolean showScores;
	qboolean scoreBoardShowing;
	int scoreFadeTime;
	int scoreTPMode;
	//Blaze: weapon stats stuff
	qboolean showWStats;
	int wstatsStartTime;
	int wstatsRequestTime;
	//end weapon stats stuff
	char killerName[MAX_NAME_LENGTH];
	char spectatorList[MAX_STRING_CHARS];	// list of names
	int spectatorLen;	// length of list
	float spectatorWidth;	// width in device units
	int spectatorTime;	// next time to offset
	int spectatorPaintX;	// current paint x
	int spectatorPaintX2;	// current paint x
	int spectatorOffset;	// current offset from start
	int spectatorPaintLen;	// current offset from start

	// skull trails
	skulltrail_t skulltrails[MAX_CLIENTS];

	// centerprinting
	int centerPrintTime;
	int centerPrintCharWidth;
	int centerPrintY;
	char centerPrint[1024];
	int centerPrintLines;
	int centerPrintMaxLen;

	// low ammo warning state
	int lowAmmoWarning;	// 1 = low, 2 = empty

	// kill timers for carnage reward
	int lastKillTime;

	// crosshair client ID
	int crosshairClientNum;
	int crosshairClientTime;

	// powerup active flashing
	int powerupActive;
	int powerupTime;

	// attacking player
	int attackerTime;
	int voiceTime;

	// reward medals
	int rewardStack;
	int rewardTime;
	int rewardCount[MAX_REWARDSTACK];
	qhandle_t rewardShader[MAX_REWARDSTACK];
	qhandle_t rewardSound[MAX_REWARDSTACK];

	// sound buffer mainly for announcer sounds
	int soundBufferIn;
	int soundBufferOut;
	int soundTime;
	qhandle_t soundBuffer[MAX_SOUNDBUFFER];

	// for voice chat buffer
	int voiceChatTime;
	int voiceChatBufferIn;
	int voiceChatBufferOut;

	// warmup countdown
	int warmup;
	int warmupCount;

	//==========================

	int itemPickup;
	int itemPickupTime;
	int itemPickupBlendTime;	// the pulse around the crosshair is timed seperately

	int weaponSelectTime;
	int weaponAnimation;
	int weaponAnimationTime;

	// blend blobs
	float damageTime;
	float damageX, damageY, damageValue;

	//Elder: added for alpha pain blend
	int rq3_trueDamage;	//Q3 doesn't hold the actual damage amount in cg.damageValue
	float rq3_blendTime;	//How long we take to fade out

	// status bar head
	float headYaw;
	float headEndPitch;
	float headEndYaw;
	int headEndTime;
	float headStartPitch;
	float headStartYaw;
	int headStartTime;

	// view movement
	float v_dmg_time;
	float v_dmg_pitch;
	float v_dmg_roll;

	vec3_t kick_angles;	// weapon kicks
	vec3_t kick_origin;
	int kick_time;		// Elder: added to decay the kicks more smoothly
	int kick_duration;	// Elder: some need more

	// temp working variables for player view
	float bobfracsin;
	int bobcycle;
	float xyspeed;
	int nextOrbitTime;

	//qboolean cameraMode;          // if rendering from a loaded camera

	// development tool
	refEntity_t testModelEntity;
	char testModelName[MAX_QPATH];
	qboolean testGun;

	// Elder: for message flooding protection
	int sayTime;
	int sayCount;

	int shellHits;		//Count number of successful shell hits

	qboolean laserSight;	//Whether to draw local laser sight
	localEntity_t *laserEnt;	//Local model -- NULL if not in-use
	qboolean rq3_irvision;	// Elder: enabled IR vision
	int akimboFlash;	// Alternate between two tags for flash (0 or 1)

	sfxSyncInfo_t curSyncSound;	// Shifts after a sound is played

// JBravo: adding scoreStartTime for NiceAss
	int scoreStartTime;

	int records[REC_NUM_RECORDS];	// Blaze: for our statistics tracking
	float loadingMapPercent;	// NiceAss: Ranges from 0 to 1. Used on map load.

	//Slicer vars that are synched from GAME
	int lca;

	// NiceAss: Scoreboard MM stuff:
	int refID;
	int matchTime;
	int team1ready;
	int team2ready;
	int refready;

	int CTBcountdowntime;
// JBravo: unlagged
	int lastPredictedCommand;
	int lastServerTime;
	playerState_t savedPmoveStates[NUM_SAVED_STATES];
	int stateHead, stateTail;
} cg_t;

//Blaze: struct to hold the func_breakable stuff
typedef struct {
	qhandle_t model[3];
	sfxHandle_t sound[3];
	sfxHandle_t exp_sound;
	qhandle_t shader;
	int jump;
	int velocity;
} breakable_t;

// all of the model, shader, and sound references that are
// loaded at gamestate time are stored in cgMedia_t
// Other media that can be tied to clients, weapons, or items are
// stored in the clientInfo_t, itemInfo_t, weaponInfo_t, and powerupInfo_t
typedef struct {
	qhandle_t charsetShader;
	qhandle_t charsetProp;
	qhandle_t charsetPropGlow;
	qhandle_t charsetPropB;
	qhandle_t whiteShader;

	qhandle_t blackHackShader;

	qhandle_t redCubeModel;
	qhandle_t blueCubeModel;
	qhandle_t redCubeIcon;
	qhandle_t blueCubeIcon;
	qhandle_t redFlagModel;
	qhandle_t blueFlagModel;
	qhandle_t neutralFlagModel;
	qhandle_t redFlagShader[3];
	qhandle_t blueFlagShader[3];
	qhandle_t flagShader[4];

	qhandle_t flagPoleModel;
	qhandle_t flagFlapModel;

	qhandle_t redFlagFlapSkin;
	qhandle_t blueFlagFlapSkin;
	qhandle_t neutralFlagFlapSkin;

	qhandle_t redFlagBaseModel;
	qhandle_t blueFlagBaseModel;
	qhandle_t neutralFlagBaseModel;

	qhandle_t armorModel;
	qhandle_t armorIcon;

	qhandle_t teamStatusBar;

	qhandle_t deferShader;

	// gib explosions
	qhandle_t gibAbdomen;
	qhandle_t gibArm;
	qhandle_t gibChest;
	qhandle_t gibFist;
	qhandle_t gibFoot;
	qhandle_t gibForearm;
	qhandle_t gibIntestine;
	qhandle_t gibLeg;
	qhandle_t gibSkull;
	qhandle_t gibBrain;
	qhandle_t glass01;	//Blaze: Breakable glass
	qhandle_t glass02;	//Blaze: Breakable glass
	qhandle_t glass03;	//Blaze: Breakable glass
	//Elder: additional debris
	qhandle_t metal01;
	qhandle_t metal02;
	qhandle_t metal03;
	qhandle_t wood01;
	qhandle_t wood02;
	qhandle_t wood03;
	qhandle_t ceramic01;
	qhandle_t ceramic02;
	qhandle_t ceramic03;
	qhandle_t paper01;
	qhandle_t paper02;
	qhandle_t paper03;
	qhandle_t brick01;
	qhandle_t brick02;
	qhandle_t brick03;
	qhandle_t concrete01;
	qhandle_t concrete02;
	qhandle_t concrete03;
	//Elder: akimbo stuff - since it's valid every game
	qhandle_t akimboModel;
	qhandle_t akimboFlashModel;
	qhandle_t akimbo1stModel;
	qhandle_t akimboHandModel;

// Blaze: func_explosive stuff
	breakable_t breakables[RQ3_MAX_BREAKABLES];

	qhandle_t smoke2;

	qhandle_t machinegunBrassModel;
	qhandle_t largeBrassModel;
	qhandle_t shotgunBrassModel;
	qhandle_t HCBrassModel;

	qhandle_t railRingsShader;
	qhandle_t railCoreShader;

	qhandle_t lightningShader;

	qhandle_t friendShader;

	qhandle_t balloonShader;
	qhandle_t connectionShader;

	qhandle_t selectShader;
	qhandle_t viewBloodShader;
	qhandle_t tracerShader;
	qhandle_t crosshairShader[NUM_CROSSHAIRS];
	qhandle_t lagometerShader;
	qhandle_t backTileShader;
	qhandle_t noammoShader;

	//Elder: item strobe to increase brightness
	qhandle_t itemStrobeShader;

	//Elder: C3A Laser tutorial
	qhandle_t laserShader;

	//Elder: sniper crosshairs
	qhandle_t ssgCrosshair[ZOOM_LEVELS];

	//Elder: RQ3 hud-related stuff
	qhandle_t rq3_healthicon;
	qhandle_t rq3_healthicon2;

	qhandle_t smokePuffShader;
	qhandle_t smokePuffAnimShader;
	qhandle_t smokePuffRageProShader;
	qhandle_t shotgunSmokePuffShader;
	qhandle_t plasmaBallShader;
	qhandle_t waterBubbleShader;

	// Pressure:
	qhandle_t waterPressureModel;
	qhandle_t flamePressureShader;

	qhandle_t bloodTrailShader;

	qhandle_t numberShaders[11];

	qhandle_t shadowMarkShader;

	qhandle_t botSkillShaders[5];

	// wall mark shaders
	qhandle_t wakeMarkShader;
	qhandle_t bloodMarkShader;
	qhandle_t ctbXMarkSilver;
	qhandle_t ctbOMarkBlack;
	qhandle_t bulletMarkShader;
	qhandle_t burnMarkShader;
	qhandle_t holeMarkShader;
	qhandle_t energyMarkShader;

	// Elder: rq3 marks
	qhandle_t slashMarkShader;
	qhandle_t glassMarkShader;
	qhandle_t metalMarkShader;
	// Makro - new mark
	//qhandle_t tileMarkShader;

	// powerup shaders
	qhandle_t quadShader;
	qhandle_t redQuadShader;
	qhandle_t quadWeaponShader;
	qhandle_t invisShader;
	qhandle_t regenShader;
	qhandle_t battleSuitShader;
	qhandle_t battleWeaponShader;
	qhandle_t hastePuffShader;
	qhandle_t redKamikazeShader;
	qhandle_t blueKamikazeShader;

	// Elder: rq3 misc shaders
	qhandle_t irPlayerShader;

	// weapon effect models
	qhandle_t bulletFlashModel;
	qhandle_t ringFlashModel;
	qhandle_t dishFlashModel;
	qhandle_t lightningExplosionModel;

	// Elder: hit spark to replace bulletFlash
	qhandle_t hitSparkModel;
	qhandle_t hitSparkShader;

	// Elder: RQ3 item models

	qhandle_t rq3_kevlarModel;
	qhandle_t rq3_bandolierModel;
	qhandle_t rq3_silencerModel;
	qhandle_t rq3_laserModel;
	qhandle_t rq3_slippersModel;
	// JBravo: the helmet
	qhandle_t rq3_helmetModel;

	// weapon effect shaders
	qhandle_t railExplosionShader;
	qhandle_t plasmaExplosionShader;
	qhandle_t bulletExplosionShader;
	qhandle_t rocketExplosionShader;
	qhandle_t grenadeExplosionShader;
	qhandle_t bfgExplosionShader;
	qhandle_t bloodExplosionShader;

	// special effects models
	qhandle_t teleportEffectModel;
	qhandle_t teleportEffectShader;
// JBravo: moved out of MISSIONPACK
	qhandle_t dustPuffShader;

	qhandle_t invulnerabilityPowerupModel;

	// scoreboard headers
	qhandle_t scoreboardName;
	qhandle_t scoreboardPing;
	qhandle_t scoreboardScore;
	qhandle_t scoreboardTime;

	// medals shown during gameplay
	qhandle_t medalImpressive;
	qhandle_t medalExcellent;
	qhandle_t medalGauntlet;
	qhandle_t medalDefend;
	qhandle_t medalAssist;
	qhandle_t medalCapture;

	// sounds
	sfxHandle_t kickSound;	//Elder: kick sound
	sfxHandle_t headshotSound;	//Elder: splat
	//sfxHandle_t   lcaSound;               //Elder: lights, camera, action!
	sfxHandle_t lensSound;	//Elder: sniper lens zoom
	sfxHandle_t silencerSound;
	sfxHandle_t kevlarHitSound;
	sfxHandle_t weapToggleSound;
	sfxHandle_t knifeClankSound;
	sfxHandle_t knifeDeathSound;
	sfxHandle_t knifeHitSound;
	//sfxHandle_t knifeThrowSound;

	sfxHandle_t quadSound;
	sfxHandle_t tracerSound;
	sfxHandle_t selectSound;
	sfxHandle_t useNothingSound;
	sfxHandle_t wearOffSound;
	sfxHandle_t footsteps[FOOTSTEP_TOTAL][4];
	sfxHandle_t sfx_lghit1;
	sfxHandle_t sfx_lghit2;
	sfxHandle_t sfx_lghit3;
	sfxHandle_t sfx_ric1;
	sfxHandle_t sfx_ric2;
	sfxHandle_t sfx_ric3;

	// Elder: Metal ricochet sounds
	sfxHandle_t sfx_metalric1;
	sfxHandle_t sfx_metalric2;
	sfxHandle_t sfx_metalric3;
	// Elder: Glass ricochet sounds
	sfxHandle_t sfx_glassric1;
	sfxHandle_t sfx_glassric2;
	sfxHandle_t sfx_glassric3;
	// Makro: brick ricochet sounds
	sfxHandle_t sfx_brickric1;
	sfxHandle_t sfx_brickric2;
	sfxHandle_t sfx_brickric3;
	// Makro: wood ricochet sounds
	sfxHandle_t sfx_woodric1;
	sfxHandle_t sfx_woodric2;
	sfxHandle_t sfx_woodric3;
	// Makro: ceramic ricochet sounds
	sfxHandle_t sfx_ceramicric1;
	sfxHandle_t sfx_ceramicric2;
	sfxHandle_t sfx_ceramicric3;
	// Elder: Shell tumble sound
	sfxHandle_t sfx_shelltumble;

	sfxHandle_t sfx_railg;
	sfxHandle_t sfx_rockexp;
	sfxHandle_t sfx_plasmaexp;
	sfxHandle_t gibSound;
	//Blaze: Dont need this any more
//      sfxHandle_t glassSound; //Blaze: Reaction breakable glass
//      sfxHandle_t glass2Sound;
	sfxHandle_t gibBounce1Sound;
	sfxHandle_t gibBounce2Sound;
	sfxHandle_t gibBounce3Sound;
	sfxHandle_t teleInSound;
	sfxHandle_t teleOutSound;
	sfxHandle_t noAmmoSound;
	sfxHandle_t respawnSound;
	sfxHandle_t talkSound;
	sfxHandle_t landSound;
	sfxHandle_t fallSound;
	sfxHandle_t jumpPadSound;

	sfxHandle_t oneMinuteSound;
	sfxHandle_t fiveMinuteSound;
	sfxHandle_t suddenDeathSound;

	sfxHandle_t threeFragSound;
	sfxHandle_t twoFragSound;
	sfxHandle_t oneFragSound;

	sfxHandle_t hitSound;
	sfxHandle_t hitSoundHighArmor;
	sfxHandle_t hitSoundLowArmor;
	sfxHandle_t hitTeamSound;
	sfxHandle_t impressiveSound;
	sfxHandle_t excellentSound;
	sfxHandle_t deniedSound;
	sfxHandle_t humiliationSound;
	sfxHandle_t assistSound;
	sfxHandle_t defendSound;
	sfxHandle_t firstImpressiveSound;
	sfxHandle_t firstExcellentSound;
	sfxHandle_t firstHumiliationSound;

	sfxHandle_t takenLeadSound;
	sfxHandle_t tiedLeadSound;
	sfxHandle_t lostLeadSound;

	sfxHandle_t voteNow;
	sfxHandle_t votePassed;
	sfxHandle_t voteFailed;

	sfxHandle_t watrInSound;
	sfxHandle_t watrOutSound;
	sfxHandle_t watrUnSound;

	sfxHandle_t flightSound;
	sfxHandle_t medkitSound;

	sfxHandle_t weaponHoverSound;

	// teamplay sounds
	sfxHandle_t captureAwardSound;
	sfxHandle_t redScoredSound;
	sfxHandle_t blueScoredSound;
	sfxHandle_t redLeadsSound;
	sfxHandle_t blueLeadsSound;
	sfxHandle_t teamsTiedSound;

	sfxHandle_t captureYourTeamSound;
	sfxHandle_t captureOpponentSound;
	sfxHandle_t returnYourTeamSound;
	sfxHandle_t returnOpponentSound;
	sfxHandle_t takenYourTeamSound;
	sfxHandle_t takenOpponentSound;

	sfxHandle_t redFlagReturnedSound;
	sfxHandle_t blueFlagReturnedSound;
	sfxHandle_t neutralFlagReturnedSound;
	sfxHandle_t enemyTookYourFlagSound;
	sfxHandle_t enemyTookTheFlagSound;
	sfxHandle_t yourTeamTookEnemyFlagSound;
	sfxHandle_t yourTeamTookTheFlagSound;
	sfxHandle_t youHaveFlagSound;
	sfxHandle_t yourBaseIsUnderAttackSound;
	sfxHandle_t holyShitSound;

	// tournament sounds
	sfxHandle_t count3Sound;
	sfxHandle_t count2Sound;
	sfxHandle_t count1Sound;
	sfxHandle_t countFightSound;
	sfxHandle_t countPrepareSound;

	qhandle_t cursor;
	qhandle_t selectCursor;
	qhandle_t sizeCursor;

	sfxHandle_t regenSound;
	sfxHandle_t protectSound;
	sfxHandle_t n_healthSound;
	sfxHandle_t hgrenb1aSound;
	sfxHandle_t hgrenb2aSound;
	//Elder: removed
	//sfxHandle_t   wstbimplSound;
	//sfxHandle_t   wstbimpmSound;
	//sfxHandle_t   wstbimpdSound;
	//sfxHandle_t   wstbactvSound;
// JBravo: LCA sounds
	sfxHandle_t lightsSound;
	sfxHandle_t cameraSound;
	sfxHandle_t actionSound;
	sfxHandle_t lca10_0Sound;
	sfxHandle_t insanesounds[9];
// JBravo: Radio sounds

	//Slicer 
	sfxHandle_t male_sounds[56];
	sfxHandle_t new_male_sounds[56];
	sfxHandle_t pikey_male_sounds[56];
	sfxHandle_t pirate_male_sounds[56];
	sfxHandle_t keanu_male_sounds[56];
	sfxHandle_t female_sounds[56];

	sfxHandle_t steamSound;
	sfxHandle_t male_1sound;
	sfxHandle_t male_2sound;
	sfxHandle_t male_3sound;
	sfxHandle_t male_4sound;
	sfxHandle_t male_5sound;
	sfxHandle_t male_6sound;
	sfxHandle_t male_7sound;
	sfxHandle_t male_8sound;
	sfxHandle_t male_9sound;
	sfxHandle_t male_10sound;
	sfxHandle_t male_backsound;
	sfxHandle_t male_coversound;
	sfxHandle_t male_downsound;
	sfxHandle_t male_enemydsound;
	sfxHandle_t male_enemyssound;
	sfxHandle_t male_forwardsound;
	sfxHandle_t male_gosound;
	sfxHandle_t male_im_hitsound;
	sfxHandle_t male_leftsound;
	sfxHandle_t male_reportinsound;
	sfxHandle_t male_rightsound;
	sfxHandle_t male_taking_fsound;
	sfxHandle_t male_teamdownsound;
	sfxHandle_t male_treportsound;
	sfxHandle_t male_upsound;
	sfxHandle_t male_click;
	sfxHandle_t female_1sound;
	sfxHandle_t female_2sound;
	sfxHandle_t female_3sound;
	sfxHandle_t female_4sound;
	sfxHandle_t female_5sound;
	sfxHandle_t female_6sound;
	sfxHandle_t female_7sound;
	sfxHandle_t female_8sound;
	sfxHandle_t female_9sound;
	sfxHandle_t female_10sound;
	sfxHandle_t female_backsound;
	sfxHandle_t female_coversound;
	sfxHandle_t female_downsound;
	sfxHandle_t female_enemydsound;
	sfxHandle_t female_enemyssound;
	sfxHandle_t female_forwardsound;
	sfxHandle_t female_gosound;
	sfxHandle_t female_im_hitsound;
	sfxHandle_t female_leftsound;
	sfxHandle_t female_reportinsound;
	sfxHandle_t female_rightsound;
	sfxHandle_t female_taking_fsound;
	sfxHandle_t female_teamdownsound;
	sfxHandle_t female_treportsound;
	sfxHandle_t female_upsound;
	sfxHandle_t female_click;
} cgMedia_t;

// The client game static (cgs) structure hold everything
// loaded or calculated from the gamestate.  It will NOT
// be cleared when a tournement restart is done, allowing
// all clients to begin playing instantly
typedef struct {
	gameState_t gameState;	// gamestate from server
	glconfig_t glconfig;	// rendering configuration
	float screenXScale;	// derived from glconfig
	float screenYScale;
	float screenXBias;

	int serverCommandSequence;	// reliable command stream counter
	int processedSnapshotNum;	// the number of snapshots cgame has requested

	qboolean localServer;	// detected on startup by checking sv_running

	// parsed from serverinfo
	gametype_t gametype;
	int dmflags;
	int teamflags;
	int fraglimit;
	int capturelimit;
	int timelimit;
	int maxclients;
	char mapname[MAX_QPATH];
	char redTeam[MAX_QPATH];
	char blueTeam[MAX_QPATH];

	int voteTime;
	int voteYes;
	int voteNo;
	qboolean voteModified;	// beep whenever changed
	char voteString[MAX_STRING_TOKENS];

	int teamVoteTime[2];
	int teamVoteYes[2];
	int teamVoteNo[2];
	qboolean teamVoteModified[2];	// beep whenever changed
	char teamVoteString[2][MAX_STRING_TOKENS];

	int levelStartTime;

	int scores1, scores2;	// from configstrings
	int redflag, blueflag;	// flag status from configstrings
	int flagStatus;

	qboolean newHud;

	//
	// locally derived information from gamestate
	//
	qhandle_t gameModels[MAX_MODELS];
	sfxHandle_t gameSounds[MAX_SOUNDS];

	int numInlineModels;
	qhandle_t inlineDrawModel[MAX_MODELS];
	vec3_t inlineModelMidpoints[MAX_MODELS];

	clientInfo_t clientinfo[MAX_CLIENTS];

	// teamchat width is *3 because of embedded color codes
	char teamChatMsgs[TEAMCHAT_HEIGHT][TEAMCHAT_WIDTH * 3 + 1];
	int teamChatMsgTimes[TEAMCHAT_HEIGHT];
	int teamChatPos;
	int teamLastChatPos;

	int cursorX;
	int cursorY;
	qboolean eventHandling;
	qboolean mouseCaptured;
	qboolean sizingHud;
	void *capturedItem;
	qhandle_t activeCursor;

	// orders
	int currentOrder;
	qboolean orderPending;
	int orderTime;
	int currentVoiceClient;
	int acceptOrderTime;
	int acceptTask;
	int acceptLeader;
	char acceptVoice[MAX_NAME_LENGTH];

	// media
	cgMedia_t media;
// JBravo: unlagged
	int delagHitscan;
} cgs_t;

//==============================================================================

extern cgs_t cgs;
extern cg_t cg;
extern centity_t cg_entities[MAX_GENTITIES];
extern weaponInfo_t cg_weapons[MAX_WEAPONS];
extern itemInfo_t cg_items[MAX_ITEMS];
extern markPoly_t cg_markPolys[MAX_MARK_POLYS];

extern vmCvar_t cg_centertime;
extern vmCvar_t cg_runpitch;
extern vmCvar_t cg_runroll;
extern vmCvar_t cg_bobup;
extern vmCvar_t cg_bobpitch;
extern vmCvar_t cg_bobroll;
extern vmCvar_t cg_swingSpeed;
extern vmCvar_t cg_shadows;
extern vmCvar_t cg_gibs;
extern vmCvar_t cg_drawTimer;
extern vmCvar_t cg_drawFPS;
extern vmCvar_t cg_drawPing;
extern vmCvar_t cg_drawSnapshot;
extern vmCvar_t cg_draw3dIcons;
extern vmCvar_t cg_drawIcons;
extern vmCvar_t cg_drawAmmoWarning;
extern vmCvar_t cg_drawCrosshair;
extern vmCvar_t cg_drawCrosshairNames;
extern vmCvar_t cg_drawRewards;
extern vmCvar_t cg_drawTeamOverlay;
extern vmCvar_t cg_teamOverlayUserinfo;
extern vmCvar_t cg_crosshairX;
extern vmCvar_t cg_crosshairY;
extern vmCvar_t cg_crosshairSize;
extern vmCvar_t cg_crosshairHealth;
extern vmCvar_t cg_drawStatus;
extern vmCvar_t cg_draw2D;
extern vmCvar_t cg_animSpeed;
extern vmCvar_t cg_debugAnim;
extern vmCvar_t cg_debugPosition;
extern vmCvar_t cg_debugEvents;
extern vmCvar_t cg_railTrailTime;
extern vmCvar_t cg_errorDecay;
extern vmCvar_t cg_nopredict;
extern vmCvar_t cg_noPlayerAnims;
extern vmCvar_t cg_showmiss;
extern vmCvar_t cg_footsteps;
extern vmCvar_t cg_addMarks;
extern vmCvar_t cg_brassTime;
extern vmCvar_t cg_gun_frame;
extern vmCvar_t cg_gun_x;
extern vmCvar_t cg_gun_y;
extern vmCvar_t cg_gun_z;
extern vmCvar_t cg_drawGun;
extern vmCvar_t cg_viewsize;
extern vmCvar_t cg_tracerChance;
extern vmCvar_t cg_tracerWidth;
extern vmCvar_t cg_tracerLength;
extern vmCvar_t cg_autoswitch;
extern vmCvar_t cg_ignore;
extern vmCvar_t cg_simpleItems;
extern vmCvar_t cg_fov;
extern vmCvar_t cg_thirdPersonRange;
extern vmCvar_t cg_thirdPersonAngle;
extern vmCvar_t cg_thirdPerson;
extern vmCvar_t cg_stereoSeparation;
extern vmCvar_t cg_lagometer;
extern vmCvar_t cg_drawAttacker;
extern vmCvar_t cg_synchronousClients;
extern vmCvar_t cg_gravity;
extern vmCvar_t cg_teamChatTime;
extern vmCvar_t cg_teamChatHeight;
extern vmCvar_t cg_stats;
extern vmCvar_t cg_forceModel;
extern vmCvar_t cg_buildScript;
extern vmCvar_t cg_paused;
extern vmCvar_t cg_blood;
extern vmCvar_t cg_predictItems;
extern vmCvar_t cg_deferPlayers;
//Blaze: Anti OGC code
extern vmCvar_t ogc_islame;

//Blaze: replacement weapons
extern vmCvar_t cg_RQ3_knife;
extern vmCvar_t cg_RQ3_mk23;
extern vmCvar_t cg_RQ3_m4;
extern vmCvar_t cg_RQ3_ssg3000;
extern vmCvar_t cg_RQ3_mp5;
extern vmCvar_t cg_RQ3_handcannon;
extern vmCvar_t cg_RQ3_m3;
extern vmCvar_t cg_RQ3_akimbo;
extern vmCvar_t cg_RQ3_grenade;
// JBravo: replacement skins
extern vmCvar_t cg_RQ3_knife_skin;
extern vmCvar_t cg_RQ3_mk23_skin;
extern vmCvar_t cg_RQ3_m4_skin;
extern vmCvar_t cg_RQ3_ssg3000_skin;
extern vmCvar_t cg_RQ3_mp5_skin;
extern vmCvar_t cg_RQ3_handcannon_skin;
extern vmCvar_t cg_RQ3_m3_skin;
extern vmCvar_t cg_RQ3_akimbo_skin;
extern vmCvar_t cg_RQ3_grenade_skin;
//Blaze: replacement items
extern vmCvar_t cg_RQ3_bandolier;
extern vmCvar_t cg_RQ3_kevlar;
extern vmCvar_t cg_RQ3_silencer;
extern vmCvar_t cg_RQ3_laser;
extern vmCvar_t cg_RQ3_slippers;
extern vmCvar_t cg_RQ3_helmet;
// JBravo: replacement skins
extern vmCvar_t cg_RQ3_bandolier_skin;
extern vmCvar_t cg_RQ3_kevlar_skin;
extern vmCvar_t cg_RQ3_silencer_skin;
extern vmCvar_t cg_RQ3_laser_skin;
extern vmCvar_t cg_RQ3_slippers_skin;
extern vmCvar_t cg_RQ3_helmet_skin;
// JBravo: replacement ammo
extern vmCvar_t cg_RQ3_ammo_mk23;
extern vmCvar_t cg_RQ3_ammo_shells;
extern vmCvar_t cg_RQ3_ammo_ssg3000;
extern vmCvar_t cg_RQ3_ammo_mp5;
extern vmCvar_t cg_RQ3_ammo_m4;
// JBravo: replacement skins
extern vmCvar_t cg_RQ3_ammo_mk23_skin;
extern vmCvar_t cg_RQ3_ammo_shells_skin;
extern vmCvar_t cg_RQ3_ammo_ssg3000_skin;
extern vmCvar_t cg_RQ3_ammo_mp5_skin;
extern vmCvar_t cg_RQ3_ammo_m4_skin;

//Blaze: Reaction weapon positions
//extern        vmCvar_t                cg_RQ3_drawWeapon;
//Blaze: how long the glass stays around for
extern vmCvar_t cg_RQ3_glasstime;

//Elder: muzzle flash toggle
extern vmCvar_t cg_RQ3_flash;

//Elder: toggle alpha blending
extern vmCvar_t cg_RQ3_painblend;

//Elder: toggle client-side zoom assist
extern vmCvar_t cg_RQ3_ssgZoomAssist;

//Elder: crosshair colours!
extern vmCvar_t cg_RQ3_ssgColorR;
extern vmCvar_t cg_RQ3_ssgColorG;
extern vmCvar_t cg_RQ3_ssgColorB;
extern vmCvar_t cg_RQ3_ssgColorA;

// JBravo: normal crosshair colors
extern vmCvar_t cg_RQ3_crosshairColorR;
extern vmCvar_t cg_RQ3_crosshairColorG;
extern vmCvar_t cg_RQ3_crosshairColorB;
extern vmCvar_t cg_RQ3_crosshairColorA;

//Blaze: allow regular crosshair to be overlaid ontop of the ssg crosshair
extern vmCvar_t cg_RQ3_overlaycrosshair;

// JBravo: cvar for tkok popups
extern vmCvar_t cg_RQ3_tkokAutoPopup;
extern vmCvar_t cg_RQ3_radiovoice_male;
extern vmCvar_t cg_RQ3_radiovoice_female;
extern vmCvar_t cg_RQ3_SuicideLikeARealMan;
extern vmCvar_t cg_RQ3_dynamicRadio;

// Slicer: for the Anti-Cheat System
//extern  vmCvar_t      cg_RQ3_Auth;
//Elder: SSG unique sensitivities
extern vmCvar_t cg_RQ3_ssgSensitivityAuto;
extern vmCvar_t cg_RQ3_ssgSensitivity2x;
extern vmCvar_t cg_RQ3_ssgSensitivity4x;
extern vmCvar_t cg_RQ3_ssgSensitivity6x;

//Blaze: Holds which crosshair to use for the ssg
extern vmCvar_t cg_RQ3_ssgCrosshair;

//Elder: smoke puffs, sparks, etc.
extern vmCvar_t cg_RQ3_impactEffects;

//Elder: toggle client-side laser drawing
extern vmCvar_t cg_RQ3_laserAssist;

//Blaze: anouncer sounds
extern vmCvar_t cg_RQ3_anouncer;

//Elder: different blood types
extern vmCvar_t cg_RQ3_bloodStyle;

//NiceAss: strobing weapons/items like quake 2
extern vmCvar_t cg_RQ3_strobe;
extern vmCvar_t cg_RQ3_predictWeapons;

//Makro - avidemo with jpegs
extern vmCvar_t cg_RQ3_avidemo;
extern vmCvar_t cg_drawFriend;
extern vmCvar_t cg_teamChatsOnly;
extern vmCvar_t cg_noVoiceChats;
extern vmCvar_t cg_noVoiceText;
extern vmCvar_t cg_scorePlum;
//extern vmCvar_t cg_smoothClients;
extern vmCvar_t pmove_fixed;
extern vmCvar_t pmove_msec;

//extern        vmCvar_t                cg_pmove_fixed;
extern vmCvar_t cg_cameraOrbit;
extern vmCvar_t cg_cameraOrbitDelay;
extern vmCvar_t cg_timescaleFadeEnd;
extern vmCvar_t cg_timescaleFadeSpeed;
extern vmCvar_t cg_timescale;
extern vmCvar_t cg_cameraMode;
extern vmCvar_t cg_smallFont;
extern vmCvar_t cg_bigFont;
extern vmCvar_t cg_noTaunt;
extern vmCvar_t cg_noProjectileTrail;
extern vmCvar_t cg_oldRail;
extern vmCvar_t cg_oldRocket;
extern vmCvar_t cg_oldPlasma;
extern vmCvar_t cg_trueLightning;

// JBravo: unlagged
extern vmCvar_t cg_delag;
extern vmCvar_t cg_debugDelag;
extern vmCvar_t cg_drawBBox;
extern vmCvar_t cg_cmdTimeNudge;
extern vmCvar_t sv_fps;
extern vmCvar_t cg_projectileNudge;
extern vmCvar_t cg_optimizePrediction;
extern vmCvar_t cl_timeNudge;
extern vmCvar_t cg_latentSnaps;
extern vmCvar_t cg_latentCmds;
extern vmCvar_t cg_plOut;

// NiceAss: No longer part of the MissionPack
extern vmCvar_t cg_enableBreath;
extern vmCvar_t cg_enableLaserFog;

// JBravo: ditto
extern vmCvar_t cg_enableDust;

//Blaze: to handle the auto actions
extern vmCvar_t cg_RQ3_autoAction;

//Blaze: Cheat cvars
extern cheat_cvar cheats[30];

// JBravo: Teamplay cvars synched from game
//Slicer: no longer needed.
//extern        vmCvar_t                cg_RQ3_lca;

//Slicer: apparently not being used
//extern        vmCvar_t                cg_RQ3_team_round_going;
extern vmCvar_t cg_RQ3_team1name;
extern vmCvar_t cg_RQ3_team2name;
extern vmCvar_t cg_RQ3_team1model;
extern vmCvar_t cg_RQ3_team2model;


extern vmCvar_t ui_RQ3_teamCount1;
extern vmCvar_t ui_RQ3_teamCount2;
extern vmCvar_t ui_RQ3_numSpectators;

// JBravo: MM ingame menu cvars.
//Makro - removed timelimit/fraglimit cvars - they were causing problems on local servers
//extern vmCvar_t cg_RQ3_timelimit;
extern vmCvar_t cg_RQ3_roundlimit;
extern vmCvar_t cg_RQ3_roundtimelimit;
//extern vmCvar_t cg_RQ3_fraglimit;
extern vmCvar_t cg_RQ3_maxplayers;
extern vmCvar_t cg_RQ3_forceteamtalk;
extern vmCvar_t cg_RQ3_limchasecam;
extern vmCvar_t cg_RQ3_tgren;
extern vmCvar_t cg_RQ3_friendlyFire;
// JBravo: cvars for the about menu
extern vmCvar_t cg_RQ3_hostname;
extern vmCvar_t cg_RQ3_needpass;
extern vmCvar_t cg_RQ3_capturelimit;
extern vmCvar_t cg_RQ3_dmflags;
extern vmCvar_t cg_RQ3_bot_minplayers;
extern vmCvar_t cg_RQ3_showOwnKills;

//Slicer: matchmode team status cvars
//extern        vmCvar_t                cg_RQ3_RefID;
extern vmCvar_t cg_RQ3_matchmode;

// q3f atmospheric stuff:
extern  	vmCvar_t  	  	cg_atmosphericEffects;
extern  	vmCvar_t  	  	cg_lowEffects;

void CG_PredictWeaponEffects(centity_t *cent);
void CG_AddBoundingBox(centity_t *cent);
qboolean CG_Cvar_ClampInt(const char *name, vmCvar_t *vmCvar, int min, int max);

//
// cg_main.c
//
const char *CG_ConfigString(int index);
const char *CG_Argv(int arg);

void QDECL CG_Printf(const char *msg, ...);
void QDECL CG_Error(const char *msg, ...);

void CG_StartMusic(void);

void CG_UpdateCvars(void);

int CG_CrosshairPlayer(void);
int CG_LastAttacker(void);
void CG_LoadMenus(const char *menuFile);
void CG_KeyEvent(int key, qboolean down);
void CG_MouseEvent(int x, int y);
void CG_EventHandling(int type);
void CG_RankRunFrame(void);
void CG_SetScoreSelection(void *menu);
score_t *CG_GetSelectedScore();
void CG_BuildSpectatorString();

//
// cg_atmospheric.c
//
void CG_EffectParse( const char *effectstr );
void CG_AddAtmosphericEffects();
qboolean CG_AtmosphericKludge();

//
// cg_view.c
//
void CG_TestModel_f(void);
void CG_TestGun_f(void);
void CG_TestModelNextFrame_f(void);
void CG_TestModelPrevFrame_f(void);
void CG_TestModelNextSkin_f(void);
void CG_TestModelPrevSkin_f(void);
void CG_ZoomDown_f(void);
void CG_ZoomUp_f(void);
void CG_AddBufferedSound(sfxHandle_t sfx);

void CG_DrawActiveFrame(int serverTime, stereoFrame_t stereoView, qboolean demoPlayback);

//
// cg_drawtools.c
//
void CG_AdjustFrom640(float *x, float *y, float *w, float *h);
void CG_FillRect(float x, float y, float width, float height, const float *color);
void CG_DrawPic(float x, float y, float width, float height, qhandle_t hShader);
void CG_DrawString(float x, float y, const char *string, float charWidth, float charHeight, const float *modulate);

void CG_DrawStringExt(int x, int y, const char *string, const float *setColor,
		      qboolean forceColor, qboolean shadow, int charWidth, int charHeight, int maxChars);
void CG_DrawBigString(int x, int y, const char *s, float alpha);
void CG_DrawBigStringColor(int x, int y, const char *s, vec4_t color);
void CG_DrawSmallString(int x, int y, const char *s, float alpha);
void CG_DrawSmallStringColor(int x, int y, const char *s, vec4_t color);

int CG_DrawStrlen(const char *str);

float *CG_FadeColor(int startMsec, int totalMsec);
void CG_TeamColor(int team, float *color);
void CG_TileClear(void);
void CG_ColorForHealth(vec4_t hcolor);
void CG_GetColorForHealth(int health, int armor, vec4_t hcolor);

void UI_DrawProportionalString(int x, int y, const char *str, int style, vec4_t color);
void CG_DrawRect(float x, float y, float width, float height, float size, const float *color);
void CG_DrawSides(float x, float y, float w, float h, float size);
void CG_DrawTopBottom(float x, float y, float w, float h, float size);
void CG_DrawCleanSides(float x, float y, float w, float h, float size, const float *color);
void CG_DrawCleanRect(float x, float y, float width, float height, float size, const float *color);
void CG_DrawCleanLine(float x, float y, float w, float size, const float *color);

//
// cg_draw.c, cg_newDraw.c
//
extern int sortedTeamPlayers[TEAM_MAXOVERLAY];
extern int numSortedTeamPlayers;
extern int drawTeamOverlayModificationCount;
extern char systemChat[256];
extern char teamChat1[256];
extern char teamChat2[256];

void CG_AddLagometerFrameInfo(void);
void CG_AddLagometerSnapshotInfo(snapshot_t * snap);
void CG_CenterPrint(const char *str, int y, int charWidth);
void CG_DrawHead(float x, float y, float w, float h, int clientNum, vec3_t headAngles);
void CG_DrawActive(stereoFrame_t stereoView);
void CG_DrawFlagModel(float x, float y, float w, float h, int team, qboolean force2D);
void CG_DrawTeamBackground(int x, int y, int w, int h, float alpha, int team);
void CG_OwnerDraw(float x, float y, float w, float h, float text_x, float text_y, int ownerDraw, int ownerDrawFlags,
		  int align, float special, float scale, vec4_t color, qhandle_t shader, int textStyle);
void CG_Text_Paint(float x, float y, float scale, vec4_t color, const char *text, float adjust, int limit, int style);
int CG_Text_Width(const char *text, float scale, int limit);
int CG_Text_Height(const char *text, float scale, int limit);
void CG_SelectPrevPlayer();
void CG_SelectNextPlayer();
float CG_GetValue(int ownerDraw);
qboolean CG_OwnerDrawVisible(int flags);
void CG_RunMenuScript(char **args);
void CG_ShowResponseHead();
void CG_SetPrintString(int type, const char *p);
void CG_InitTeamChat();
void CG_GetTeamColor(vec4_t * color);
const char *CG_GetGameStatusText();
const char *CG_GetKillerText();
void CG_Draw3DModel(float x, float y, float w, float h, qhandle_t model, qhandle_t skin, vec3_t origin, vec3_t angles);
void CG_Text_PaintChar(float x, float y, float width, float height, float scale, float s, float t, float s2, float t2,
		       qhandle_t hShader);
void CG_CheckOrderPending();
const char *CG_GameTypeString();
qboolean CG_YourTeamHasFlag();
qboolean CG_OtherTeamHasFlag();
qhandle_t CG_StatusHandle(int task);

//
// cg_player.c
//
void CG_Player(centity_t * cent);
void CG_ResetPlayerEntity(centity_t * cent);
void CG_AddRefEntityWithPowerups(refEntity_t * ent, entityState_t * state, int team);
void CG_NewClientInfo(int clientNum);
sfxHandle_t CG_CustomSound(int clientNum, const char *soundName);

//
// cg_predict.c
//
void CG_BuildSolidList(void);
int CG_PointContents(const vec3_t point, int passEntityNum);

//Elder: try this
void CG_Trace(trace_t * result, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end,
	      int skipNumber, int mask);
//void CG_Trace( trace_t *result, const vec3_t start, vec3_t mins, vec3_t maxs, const vec3_t end,
					 //int skipNumber, int mask );
void CG_PredictPlayerState(void);
void CG_LoadDeferredPlayers(void);
void CG_EvaluateTrajectory(const trajectory_t * tr, int atTime, vec3_t result);
void CG_EvaluateTrajectoryDelta(const trajectory_t * tr, int atTime, vec3_t result);

//
// cg_events.c
//
void CG_CheckEvents(centity_t * cent);
const char *CG_PlaceString(int rank);
void CG_EntityEvent(centity_t * cent, vec3_t position);
void CG_PainEvent(centity_t * cent, int health);

//
// cg_ents.c
//
void CG_SetEntitySoundPosition(centity_t * cent);
//Makro - added skyportal param
//void CG_AddPacketEntities(void);
void CG_AddPacketEntities(int mode);
void CG_Beam(centity_t * cent);
void CG_AdjustPositionForMover(const vec3_t in, int moverNum, int fromTime, int toTime, vec3_t out);

void CG_PositionEntityOnTag(refEntity_t * entity, const refEntity_t * parent, qhandle_t parentModel, char *tagName);
void CG_PositionRotatedEntityOnTag(refEntity_t * entity, const refEntity_t * parent,
				   qhandle_t parentModel, char *tagName);
//Blaze: for weapon animations
void CG_PositionWeaponOnTag(refEntity_t * entity, const refEntity_t * parent, qhandle_t parentModel, char *tagName);
void CG_PositionRotatedOffsetEntityOnTag(refEntity_t * entity, const refEntity_t * parent, qhandle_t parentModel,
					 char *tagName, vec3_t Offset);

//
// cg_weapons.c
//
void CG_NextWeapon_f(void);

//Elder: added?
void CG_Weapon_f(void);
void CG_PrevWeapon_f(void);
void CG_SpecialWeapon_f(void);

void CG_RQ3_SyncZoom(void);
void CG_RQ3_SaveZoomLevel();
void CG_RQ3_Zoom(void);		//Elder: just threw it in
void CG_RQ3_Zoom1x();
int CG_RQ3_GetGrenadeMode();
void CG_RQ3_GrenadeMode();

void CG_RegisterWeapon(int weaponNum);
void CG_RegisterItemVisuals(int itemNum);

void CG_FireWeapon(centity_t * cent, int weapModification);
void CG_ReloadWeapon(centity_t * cent, int reloadStage);	//Elder: added
void CG_MissileHitWall(int weapon, int clientNum, vec3_t origin, vec3_t dir, impactSound_t soundType, int weapModification);	//Elder: added weapMod
void CG_MissileHitPlayer(int weapon, vec3_t origin, vec3_t dir, int entityNum);
void CG_ShotgunFire(entityState_t * es, qboolean ism3);
void CG_Bullet(vec3_t origin, int sourceEntityNum, vec3_t normal, qboolean flesh, int fleshEntityNum,
	       impactSound_t soundType);

void CG_RailTrail(clientInfo_t * ci, vec3_t start, vec3_t end);
void CG_GrappleTrail(centity_t * ent, const weaponInfo_t * wi);
void CG_AddViewWeapon(playerState_t * ps);
void CG_AddPlayerWeapon(refEntity_t * parent, playerState_t * ps, centity_t * cent, int team);
void CG_DrawWeaponSelect(void);

void CG_Tracer(vec3_t source, vec3_t dest);

void CG_OutOfAmmoChange(void);	// should this be in pmove?
void CG_CheckLaser();		//Elder: check laser to see if it's our own

//
// cg_marks.c
//
void CG_InitMarkPolys(void);
void CG_AddMarks(void);
void CG_ImpactMark(qhandle_t markShader,
		   const vec3_t origin, const vec3_t dir,
		   float orientation,
		   float r, float g, float b, float a, qboolean alphaFade, float radius, qboolean temporary);

//
// cg_localents.c
//
void CG_InitLocalEntities(void);
localEntity_t *CG_AllocLocalEntity(void);
void CG_AddLocalEntities(void);
void CG_FreeLocalEntity(localEntity_t * le);
void CG_LE_EvaluateTrajectory(const trajectory_t * tr, int atTime, vec3_t result);
void CG_LE_EvaluateTrajectoryDelta(const trajectory_t * tr, int atTime, vec3_t result);

//
// cg_effects.c
//
localEntity_t *CG_SmokePuff(const vec3_t p,
			    const vec3_t vel,
			    float radius,
			    float r, float g, float b, float a,
			    float duration, int startTime, int fadeInTime, int leFlags, qhandle_t hShader);
void CG_BubbleTrail(vec3_t start, vec3_t end, float spacing);
void CG_SpawnEffect(vec3_t org);
void CG_ScorePlum(int client, vec3_t org, int score);
void CG_DrawVisibleLaser( vec3_t origin, int clientNum, vec3_t dir);

//Blaze: for explosions
void CG_Particle_Bleed(qhandle_t pshader, vec3_t start, vec3_t dir, int fleshEntityNum, int duration);
void CG_ShrapnelSpark(vec3_t source, vec3_t dest, float width, float length);

void CG_GibPlayer(vec3_t playerOrigin);

// JBravo: Sniperheadshots
void CG_GibPlayerHeadshot(vec3_t playerOrigin);
void CG_BigExplode(vec3_t playerOrigin);

// Blaze: Breakable glass Elder: modified
void CG_BreakGlass(vec3_t playerOrigin, int glassParm, int number, int type, int isChip);
void CG_Bleed(vec3_t origin, int entityNum);

//Elder: for SSG shots
void CG_BleedSpray(vec3_t start, vec3_t end, int entityNum, int numBursts);
void CG_BleedParticleSpray(vec3_t start, vec3_t dir, int fleshEntityNum, int amount, int duration);
void CG_EjectBloodSplat(vec3_t origin, vec3_t velocity, int amount, int duration);

localEntity_t *CG_MakeExplosion(vec3_t origin, vec3_t dir,
				qhandle_t hModel, qhandle_t shader, int msec, qboolean isSprite);

void CG_Pressure(vec3_t origin, vec3_t dir, int type, int speed, int life);

//
// cg_snapshot.c
//
void CG_ProcessSnapshots(void);
void CG_TransitionEntity(centity_t *cent);

//
// cg_info.c
//
void CG_LoadingString(const char *s);
void CG_LoadingItem(int itemNum);
void CG_LoadingClient(int clientNum);
void CG_DrawInformation(void);

//
// cg_scoreboard.c
//
qboolean CG_DrawOldScoreboard(void);
void CG_DrawOldTourneyScoreboard(void);

//
// cg_players.c
//
void CG_WeaponAnimation(centity_t * cent, int *weaponOld, int *weapon, float *weaponBackLerp);

//
// cg_consolecmds.c
//
qboolean CG_ConsoleCommand(void);
void CG_InitConsoleCommands(void);

//
// cg_servercmds.c
//
void CG_ExecuteNewServerCommands(int latestSequence);
void CG_ParseServerinfo(void);
void CG_SetConfigValues(void);
void CG_LoadVoiceChats(void);
void CG_ShaderStateChanged(void);
void CG_VoiceChatLocal(int mode, qboolean voiceOnly, int clientNum, int color, const char *cmd);
void CG_PlayBufferedVoiceChats(void);

//
// cg_playerstate.c
//
void CG_Respawn(void);
void CG_TransitionPlayerState(playerState_t * ps, playerState_t * ops);
void CG_CheckChangedPredictableEvents(playerState_t * ps);

//===============================================

//
// system traps
// These functions are how the cgame communicates with the main game system
//

// print message on the local console
void trap_Print(const char *fmt);

// abort the game
void trap_Error(const char *fmt);

// milliseconds should only be used for performance tuning, never
// for anything game related.  Get time from the CG_DrawActiveFrame parameter
int trap_Milliseconds(void);

// console variable interaction
void trap_Cvar_Register(vmCvar_t * vmCvar, const char *varName, const char *defaultValue, int flags);
void trap_Cvar_Update(vmCvar_t * vmCvar);
void trap_Cvar_Set(const char *var_name, const char *value);
void trap_Cvar_VariableStringBuffer(const char *var_name, char *buffer, int bufsize);

// ServerCommand and ConsoleCommand parameter access
int trap_Argc(void);
void trap_Argv(int n, char *buffer, int bufferLength);
void trap_Args(char *buffer, int bufferLength);

// filesystem access
// returns length of file
int trap_FS_FOpenFile(const char *qpath, fileHandle_t * f, fsMode_t mode);
void trap_FS_Read(void *buffer, int len, fileHandle_t f);
void trap_FS_Write(const void *buffer, int len, fileHandle_t f);
void trap_FS_FCloseFile(fileHandle_t f);

// add commands to the local console as if they were typed in
// for map changing, etc.  The command is not executed immediately,
// but will be executed in order the next time console commands
// are processed
void trap_SendConsoleCommand(const char *text);

// register a command name so the console can perform command completion.
// FIXME: replace this with a normal console command "defineCommand"?
void trap_AddCommand(const char *cmdName);

// send a string to the server over the network
void trap_SendClientCommand(const char *s);

// force a screen update, only used during gamestate load
void trap_UpdateScreen(void);

// model collision
void trap_CM_LoadMap(const char *mapname);
int trap_CM_NumInlineModels(void);
clipHandle_t trap_CM_InlineModel(int index);	// 0 = world, 1+ = bmodels
clipHandle_t trap_CM_TempBoxModel(const vec3_t mins, const vec3_t maxs);
int trap_CM_PointContents(const vec3_t p, clipHandle_t model);
int trap_CM_TransformedPointContents(const vec3_t p, clipHandle_t model, const vec3_t origin, const vec3_t angles);
void trap_CM_BoxTrace(trace_t * results, const vec3_t start, const vec3_t end,
		      const vec3_t mins, const vec3_t maxs, clipHandle_t model, int brushmask);
void trap_CM_TransformedBoxTrace(trace_t * results, const vec3_t start, const vec3_t end,
				 const vec3_t mins, const vec3_t maxs,
				 clipHandle_t model, int brushmask, const vec3_t origin, const vec3_t angles);

// Returns the projection of a polygon onto the solid brushes in the world
int trap_CM_MarkFragments(int numPoints, const vec3_t * points,
			  const vec3_t projection,
			  int maxPoints, vec3_t pointBuffer, int maxFragments, markFragment_t * fragmentBuffer);

// normal sounds will have their volume dynamically changed as their entity
// moves and the listener moves
void trap_S_StartSound(vec3_t origin, int entityNum, int entchannel, sfxHandle_t sfx);
void trap_S_StopLoopingSound(int entnum);

// a local sound is always played full volume
void trap_S_StartLocalSound(sfxHandle_t sfx, int channelNum);
void trap_S_ClearLoopingSounds(qboolean killall);
void trap_S_AddLoopingSound(int entityNum, const vec3_t origin, const vec3_t velocity, sfxHandle_t sfx);
void trap_S_AddRealLoopingSound(int entityNum, const vec3_t origin, const vec3_t velocity, sfxHandle_t sfx);
void trap_S_UpdateEntityPosition(int entityNum, const vec3_t origin);

// repatialize recalculates the volumes of sound as they should be heard by the
// given entityNum and position
void trap_S_Respatialize(int entityNum, const vec3_t origin, vec3_t axis[3], int inwater);
sfxHandle_t trap_S_RegisterSound(const char *sample, qboolean compressed);	// returns buzz if not found
void trap_S_StartBackgroundTrack(const char *intro, const char *loop);	// empty name stops music
void trap_S_StopBackgroundTrack(void);

void trap_R_LoadWorldMap(const char *mapname);

// all media should be registered during level startup to prevent
// hitches during gameplay
qhandle_t trap_R_RegisterModel(const char *name);	// returns rgb axis if not found
qhandle_t trap_R_RegisterSkin(const char *name);	// returns all white if not found
qhandle_t trap_R_RegisterShader(const char *name);	// returns all white if not found
qhandle_t trap_R_RegisterShaderNoMip(const char *name);	// returns all white if not found

// a scene is built up by calls to R_ClearScene and the various R_Add functions.
// Nothing is drawn until R_RenderScene is called.
void trap_R_ClearScene(void);
void trap_R_AddRefEntityToScene(const refEntity_t * re);

// polys are intended for simple wall marks, not really for doing
// significant construction
void trap_R_AddPolyToScene(qhandle_t hShader, int numVerts, const polyVert_t * verts);
void trap_R_AddPolysToScene(qhandle_t hShader, int numVerts, const polyVert_t * verts, int numPolys);
void trap_R_AddLightToScene(const vec3_t org, float intensity, float r, float g, float b);
int trap_R_LightForPoint(vec3_t point, vec3_t ambientLight, vec3_t directedLight, vec3_t lightDir);
void trap_R_RenderScene(const refdef_t * fd);
void trap_R_SetColor(const float *rgba);	// NULL = 1,1,1,1
void trap_R_DrawStretchPic(float x, float y, float w, float h,
			   float s1, float t1, float s2, float t2, qhandle_t hShader);
void trap_R_ModelBounds(clipHandle_t model, vec3_t mins, vec3_t maxs);
int trap_R_LerpTag(orientation_t * tag, clipHandle_t mod, int startFrame, int endFrame,
		   float frac, const char *tagName);
void trap_R_RemapShader(const char *oldShader, const char *newShader, const char *timeOffset);

// The glconfig_t will not change during the life of a cgame.
// If it needs to change, the entire cgame will be restarted, because
// all the qhandle_t are then invalid.
void trap_GetGlconfig(glconfig_t * glconfig);

// the gamestate should be grabbed at startup, and whenever a
// configstring changes
void trap_GetGameState(gameState_t * gamestate);

// cgame will poll each frame to see if a newer snapshot has arrived
// that it is interested in.  The time is returned seperately so that
// snapshot latency can be calculated.
void trap_GetCurrentSnapshotNumber(int *snapshotNumber, int *serverTime);

// a snapshot get can fail if the snapshot (or the entties it holds) is so
// old that it has fallen out of the client system queue
qboolean trap_GetSnapshot(int snapshotNumber, snapshot_t * snapshot);

// retrieve a text command from the server stream
// the current snapshot will hold the number of the most recent command
// qfalse can be returned if the client system handled the command
// argc() / argv() can be used to examine the parameters of the command
qboolean trap_GetServerCommand(int serverCommandNumber);

// returns the most recent command number that can be passed to GetUserCmd
// this will always be at least one higher than the number in the current
// snapshot, and it may be quite a few higher if it is a fast computer on
// a lagged connection
int trap_GetCurrentCmdNumber(void);

qboolean trap_GetUserCmd(int cmdNumber, usercmd_t * ucmd);

// used for the weapon select and zoom
void trap_SetUserCmdValue(int stateValue, float sensitivityScale);

// aids for VM testing
void testPrintInt(char *string, int i);
void testPrintFloat(char *string, float f);

int trap_MemoryRemaining(void);
void trap_R_RegisterFont(const char *fontName, int pointSize, fontInfo_t * font);
qboolean trap_Key_IsDown(int keynum);
int trap_Key_GetCatcher(void);
void trap_Key_SetCatcher(int catcher);
int trap_Key_GetKey(const char *binding);

typedef enum {
	SYSTEM_PRINT,
	CHAT_PRINT,
	TEAMCHAT_PRINT
} q3print_t;			// bk001201 - warning: useless keyword or type name in empty declaration

int trap_CIN_PlayCinematic(const char *arg0, int xpos, int ypos, int width, int height, int bits);
e_status trap_CIN_StopCinematic(int handle);
e_status trap_CIN_RunCinematic(int handle);
void trap_CIN_DrawCinematic(int handle);
void trap_CIN_SetExtents(int handle, int x, int y, int w, int h);

void trap_SnapVector(float *v);

qboolean trap_loadCamera(const char *name);
void trap_startCamera(int time);
qboolean trap_getCameraInfo(int time, vec3_t * origin, vec3_t * angles);

qboolean trap_GetEntityToken(char *buffer, int bufferSize);

void CG_ClearParticles(void);
void CG_AddParticles(void);
void CG_ParticleSnow(qhandle_t pshader, vec3_t origin, vec3_t origin2, int turb, float range, int snum);
void CG_ParticleSmoke(qhandle_t pshader, centity_t * cent);
void CG_AddParticleShrapnel(localEntity_t * le);
void CG_ParticleSnowFlurry(qhandle_t pshader, centity_t * cent);
void CG_ParticleBulletDebris(vec3_t org, vec3_t vel, int duration);
void CG_ParticleSparks(vec3_t org, vec3_t vel, int duration, float x, float y, float speed, float scale);
void CG_ParticleDust(centity_t * cent, vec3_t origin, vec3_t dir);
void CG_ParticleMisc(qhandle_t pshader, vec3_t origin, int size, int duration, float alpha);
void CG_ParticleExplosion(char *animStr, vec3_t origin, vec3_t vel, int duration, int sizeStart, int sizeEnd);
void CG_ParticleAir(vec3_t org, vec3_t vel, int duration, float alpha, float speed, float scale);
void CG_ParticleSteam(vec3_t org, vec3_t vel, int duration, float alpha, float speed, float scale, int Shader);
void CG_ParticleWater(vec3_t org, vec3_t vel, int duration, float alpha, float speed, float scale);

extern qboolean initparticles;
int CG_NewParticleArea(int num);
