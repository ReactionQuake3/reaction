//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.12  2002/01/11 19:48:30  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.11  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
/*
=======================================================================

CONTROLS MENU

=======================================================================
*/


#include "ui_local.h"

#define ART_BACK0		"menu/art/rq3-menu-back.tga"
#define ART_BACK1		"menu/art/rq3-menu-back-focus.tga"
//#define ART_BACK0			"menu/art/back_0"
//#define ART_BACK1			"menu/art/back_1"
//#define ART_FRAMEL			"menu/art/frame2_l"
//#define ART_FRAMER			"menu/art/frame1_r"

//Elder: RQ3 Setup assets
#define RQ3_SETUP_ICON		"menu/art/rq3-setup-controls.jpg"
#define RQ3_SETUP_TITLE		"menu/art/rq3-title-setup.jpg"
#define RQ3_FOCUS_BUTTON	"menu/art/rq3-menu-focus.tga"
#define RQ3_LOOKING_BUTTON	"menu/art/rq3-controls-looking.jpg"
#define RQ3_MOVEMENT_BUTTON	"menu/art/rq3-controls-movement.jpg"
#define RQ3_WEAPONS_BUTTON	"menu/art/rq3-controls-weapons.jpg"
#define RQ3_MISC_BUTTON		"menu/art/rq3-controls-misc.jpg"
#define RQ3_REACTION_BUTTON	"menu/art/rq3-controls-reaction.jpg"


typedef struct {
	char	*command;
	char	*label;
	int		id;
	int		anim;
	int		defaultbind1;
	int		defaultbind2;
	int		bind1;
	int		bind2;
} bind_t;

typedef struct
{
	char*	name;
	float	defaultvalue;
	float	value;
} configcvar_t;

#define SAVE_NOOP		0
#define SAVE_YES		1
#define SAVE_NO			2
#define SAVE_CANCEL		3

// control sections
#define C_MOVEMENT		0
#define C_LOOKING		1
#define C_WEAPONS		2
#define C_MISC			3
//Blaze: Reaction control section
#define C_REACTION		4
#define C_MAX			5

#define ID_MOVEMENT		100
#define ID_LOOKING		101
#define ID_WEAPONS		102
#define ID_MISC			103
#define ID_DEFAULTS		104
#define ID_BACK			105
#define ID_SAVEANDEXIT	106
#define ID_EXIT			107
//Blaze: Reaction menu
#define ID_REACTION     108


// bindable actions
#define ID_SHOWSCORES	0
#define ID_USEITEM		1
#define ID_SPEED		2
#define ID_FORWARD		3
#define ID_BACKPEDAL	4
#define ID_MOVELEFT		5
#define ID_MOVERIGHT	6
#define ID_MOVEUP		7
#define ID_MOVEDOWN		8
#define ID_LEFT			9
#define ID_RIGHT		10
#define ID_STRAFE		11
#define ID_LOOKUP		12
#define ID_LOOKDOWN		13
#define ID_MOUSELOOK	14
#define ID_CENTERVIEW	15
#define ID_ZOOMVIEW		16
// Elder: WEAPON1 is now pistol
#define ID_WEAPON1		17
#define ID_WEAPON2		18
#define ID_WEAPON3		19
#define ID_WEAPON4		20
#define ID_WEAPON5		21
#define ID_WEAPON6		22
#define ID_WEAPON7		23
#define ID_WEAPON8		24
#define ID_WEAPON9		25
#define ID_ATTACK		26
#define ID_WEAPPREV		27
#define ID_WEAPNEXT		28
#define ID_GESTURE		29
#define ID_CHAT			30
#define ID_CHAT2		31
#define ID_CHAT3		32
#define ID_CHAT4		33
//Blaze: Reaction binds
#define ID_BANDAGE		34
#define ID_RELOAD		35
#define ID_WEAPON		36
#define ID_OPENDOOR		37
#define ID_DROPWEAP		38
#define ID_DROPITEM		39
#define ID_IRVISION		40

// all others
#define ID_FREELOOK		40
#define ID_INVERTMOUSE	41
#define ID_ALWAYSRUN	42
#define ID_AUTOSWITCH	43
#define ID_MOUSESPEED	44
#define ID_JOYENABLE	45
#define ID_JOYTHRESHOLD	46
#define ID_SMOOTHMOUSE	47

#define ANIM_IDLE		0
#define ANIM_RUN		1
#define ANIM_WALK		2
#define ANIM_BACK		3
#define ANIM_JUMP		4
#define ANIM_CROUCH		5
#define ANIM_STEPLEFT	6
#define ANIM_STEPRIGHT	7
#define ANIM_TURNLEFT	8
#define ANIM_TURNRIGHT	9
#define ANIM_LOOKUP		10
#define ANIM_LOOKDOWN	11
#define ANIM_WEAPON1	12
#define ANIM_WEAPON2	13
#define ANIM_WEAPON3	14
#define ANIM_WEAPON4	15
#define ANIM_WEAPON5	16
#define ANIM_WEAPON6	17
#define ANIM_WEAPON7	18
#define ANIM_WEAPON8	19
#define ANIM_WEAPON9	20
#define ANIM_WEAPON10	21
#define ANIM_ATTACK		22
#define ANIM_GESTURE	23
#define ANIM_DIE		24
#define ANIM_CHAT		25
#define ANIM_RELOAD		26


typedef struct
{
	menuframework_s		menu;

//Blaze: Dont need this
//	menutext_s			banner;
//	menubitmap_s		framel;
//	menubitmap_s		framer;
/*
	menutext_s		multim;
	menutext_s		setupm;
	menutext_s		demom;
	menutext_s		modsm;
	menutext_s		exitm;
*/
//	menutext_s		load;
//	menutext_s		save;
	menutext_s		defaults;

	//Elder: RQ3 Stuff
	menubitmap_s	rq3_setupicon;
	menubitmap_s	rq3_setuptitle;
	menutext_s		rq3_statustext;

	menubitmap_s		player;

	/*
	menutext_s			movement;
	menutext_s			looking;
	menutext_s			weapons;
	menutext_s			misc;
	*/
	menubitmap_s		movement;
	menubitmap_s		looking;
	menubitmap_s		weapons;
	menubitmap_s		misc;

	//Blaze: Reaction Menu
	menubitmap_s		reaction;

	menuaction_s		walkforward;
	menuaction_s		backpedal;
	menuaction_s		stepleft;
	menuaction_s		stepright;
	menuaction_s		moveup;
	menuaction_s		movedown;
	menuaction_s		turnleft;
	menuaction_s		turnright;
	menuaction_s		sidestep;
	menuaction_s		run;

//Blaze: Dont need these
	//menuaction_s		chainsaw;
	//menuaction_s		machinegun;
//Blaze: Reaction weapons binds
	menuaction_s		mk23;
	menuaction_s		m3;
	menuaction_s		mp5;
	menuaction_s		handcannon;
	menuaction_s		ssg3000;
	menuaction_s		m4;
	menuaction_s		akimbos;
	menuaction_s		knife;
	menuaction_s		grenade;
	menuaction_s		attack;
	menuaction_s		prevweapon;
	menuaction_s		nextweapon;
	menuaction_s		lookup;
	menuaction_s		lookdown;
	menuaction_s		mouselook;
	menuradiobutton_s	freelook;
	menuaction_s		centerview;
	menuaction_s		zoomview;
	menuaction_s		gesture;
	menuradiobutton_s	invertmouse;
	menuslider_s		sensitivity;
	menuradiobutton_s	smoothmouse;
	menuradiobutton_s	alwaysrun;
	menuaction_s		showscores;
	menuradiobutton_s	autoswitch;
	menuaction_s		useitem;
	playerInfo_t		playerinfo;
	qboolean			changesmade;
	menuaction_s		chat;
	menuaction_s		chat2;
	menuaction_s		chat3;
	menuaction_s		chat4;
	//Blaze: Reaction binds
	menuaction_s		bandage;
	menuaction_s		reload;
	menuaction_s		weapon;
	menuaction_s		opendoor;
	menuaction_s		dropweap;
	menuaction_s		dropitem;
	menuaction_s		irvision;

	menuradiobutton_s	joyenable;
	menuslider_s		joythreshold;
	int					section;
	qboolean			waitingforkey;
	char				playerModel[64];
	vec3_t				playerViewangles;
	vec3_t				playerMoveangles;
	int					playerLegs;
	int					playerTorso;
	int					playerWeapon;
	qboolean			playerChat;

	menubitmap_s		back;
	menutext_s			name;
} controls_t;

static controls_t s_controls;

static vec4_t controls_binding_color  = {1.00f, 0.43f, 0.00f, 1.00f}; // bk: Win32 C4305

static bind_t g_bindings[] =
{
	{"+scores",			"show scores",		ID_SHOWSCORES,	ANIM_IDLE,		K_TAB,			-1,		-1, -1},
	{"+button2",		"use item",			ID_USEITEM,		ANIM_IDLE,		K_ENTER,		-1,		-1, -1},
	{"+speed", 			"run / walk",		ID_SPEED,		ANIM_RUN,		K_SHIFT,		-1,		-1,	-1},
	{"+forward", 		"walk forward",		ID_FORWARD,		ANIM_WALK,		K_UPARROW,		-1,		-1, -1},
	{"+back", 			"backpedal",		ID_BACKPEDAL,	ANIM_BACK,		K_DOWNARROW,	-1,		-1, -1},
	{"+moveleft", 		"step left",		ID_MOVELEFT,	ANIM_STEPLEFT,	',',			-1,		-1, -1},
	{"+moveright", 		"step right",		ID_MOVERIGHT,	ANIM_STEPRIGHT,	'.',			-1,		-1, -1},
	{"+moveup",			"up / jump",		ID_MOVEUP,		ANIM_JUMP,		K_SPACE,		-1,		-1, -1},
	{"+movedown",		"down / crouch",	ID_MOVEDOWN,	ANIM_CROUCH,	'c',			-1,		-1, -1},
	{"+left", 			"turn left",		ID_LEFT,		ANIM_TURNLEFT,	K_LEFTARROW,	-1,		-1, -1},
	{"+right", 			"turn right",		ID_RIGHT,		ANIM_TURNRIGHT,	K_RIGHTARROW,	-1,		-1, -1},
	{"+strafe", 		"sidestep / turn",	ID_STRAFE,		ANIM_IDLE,		K_ALT,			-1,		-1, -1},
	{"+lookup", 		"look up",			ID_LOOKUP,		ANIM_LOOKUP,	K_PGDN,			-1,		-1, -1},
	{"+lookdown", 		"look down",		ID_LOOKDOWN,	ANIM_LOOKDOWN,	K_DEL,			-1,		-1, -1},
	{"+mlook", 			"mouse look",		ID_MOUSELOOK,	ANIM_IDLE,		'/',			-1,		-1, -1},
	{"centerview", 		"center view",		ID_CENTERVIEW,	ANIM_IDLE,		K_END,			-1,		-1, -1},
	{"+zoom", 			"zoom view",		ID_ZOOMVIEW,	ANIM_IDLE,		-1,				-1,		-1, -1},
//Blaze: Reaction Weapon binds
//Jbravo: order is important.
	{"weapon 1",		"MK23 Pistol",				ID_WEAPON1,	ANIM_WEAPON1,	'1',	-1,	-1, -1},
	{"weapon 2",		"M3 Assault Shotgun",		ID_WEAPON2,	ANIM_WEAPON2,	'2',	-1,	-1, -1},
	{"weapon 3",		"MP5/10 Submachinegun",		ID_WEAPON3,	ANIM_WEAPON3,	'3',	-1,	-1, -1},
	{"weapon 4",		"Handcannon",				ID_WEAPON4,	ANIM_WEAPON4,	'4',	-1,	-1, -1},
	{"weapon 5",		"Sniper Rifle",				ID_WEAPON5,	ANIM_WEAPON5,	'5',	-1,	-1, -1},
	{"weapon 6",		"M4 Assault Rifle",			ID_WEAPON6,	ANIM_WEAPON6,	'6',	-1,	-1, -1},
	{"weapon 7",		"Dual MK23 Pistols",		ID_WEAPON7,	ANIM_WEAPON7,	'7',	-1,	-1, -1},
	{"weapon 8",		"Combat Knife",				ID_WEAPON8,	ANIM_WEAPON8,	'8',	-1,	-1, -1},
	{"weapon 9",		"M26 Frag Grenade",			ID_WEAPON9,	ANIM_WEAPON9,	'9',	-1,	-1, -1},
	{"+attack", 		"attack",			ID_ATTACK,		ANIM_ATTACK,	K_CTRL,			-1,		-1, -1},
	{"weapprev",		"prev weapon",		ID_WEAPPREV,	ANIM_IDLE,		'[',			-1,		-1, -1},
	{"weapnext", 		"next weapon",		ID_WEAPNEXT,	ANIM_IDLE,		']',			-1,		-1, -1},
	{"+button3", 		"gesture",			ID_GESTURE,		ANIM_GESTURE,	K_MOUSE3,		-1,		-1, -1},
	{"messagemode", 	"chat",				ID_CHAT,		ANIM_CHAT,		't',			-1,		-1, -1},
	{"messagemode2", 	"chat - team",		ID_CHAT2,		ANIM_CHAT,		-1,				-1,		-1, -1},
	{"messagemode3", 	"chat - target",	ID_CHAT3,		ANIM_CHAT,		-1,				-1,		-1, -1},
	{"messagemode4", 	"chat - attacker",	ID_CHAT4,		ANIM_CHAT,		-1,				-1,		-1, -1},
	{"bandage",	 		"Bandage",			ID_BANDAGE,		ANIM_IDLE,		-1,				-1,		-1, -1},
	{"+button5",		"Reload",			ID_RELOAD,		ANIM_RELOAD,	-1,				-1,		-1, -1},
	{"weapon",			"Weapon Mode",		ID_WEAPON,		ANIM_IDLE,		-1,				-1,		-1, -1},
	{"opendoor",	 	"Open Door",		ID_OPENDOOR,	ANIM_IDLE,		-1,				-1,		-1, -1},
	{"dropweapon",	 	"Drop Weapon",		ID_DROPWEAP,	ANIM_IDLE,		-1,				-1,		-1, -1},
	{"dropitem",	 	"Drop Item",		ID_DROPITEM,	ANIM_IDLE,		-1,				-1,		-1, -1},
	{"irvision",	 	"IR Vision",		ID_IRVISION,	ANIM_IDLE,		-1,				-1,		-1, -1},
	{(char*)NULL,		(char*)NULL,		0,				0,				-1,				-1,		-1,	-1},
};

static configcvar_t g_configcvars[] =
{
	{"cl_run",			0,					0},
	{"m_pitch",			0,					0},
	{"cg_autoswitch",	0,					0},
	{"sensitivity",		0,					0},
	{"in_joystick",		0,					0},
	{"joy_threshold",	0,					0},
	{"m_filter",		0,					0},
	{"cl_freelook",		0,					0},
	{NULL,				0,					0}
};

static menucommon_s *g_movement_controls[] =
{
	(menucommon_s *)&s_controls.alwaysrun,
	(menucommon_s *)&s_controls.run,
	(menucommon_s *)&s_controls.walkforward,
	(menucommon_s *)&s_controls.backpedal,
	(menucommon_s *)&s_controls.stepleft,
	(menucommon_s *)&s_controls.stepright,
	(menucommon_s *)&s_controls.moveup,
	(menucommon_s *)&s_controls.movedown,
	(menucommon_s *)&s_controls.turnleft,
	(menucommon_s *)&s_controls.turnright,
	(menucommon_s *)&s_controls.sidestep,
	NULL
};

static menucommon_s *g_weapons_controls[] = {
	(menucommon_s *)&s_controls.attack,
	(menucommon_s *)&s_controls.nextweapon,
	(menucommon_s *)&s_controls.prevweapon,
	(menucommon_s *)&s_controls.autoswitch,
//Blaze: No need for the chainsaw/gauntlet or machinegun
/*
	(menucommon_s *)&s_controls.chainsaw,
	(menucommon_s *)&s_controls.machinegun,
*/
	(menucommon_s *)&s_controls.mk23,
	(menucommon_s *)&s_controls.m3,
	(menucommon_s *)&s_controls.mp5,
	(menucommon_s *)&s_controls.handcannon,
	(menucommon_s *)&s_controls.ssg3000,
	(menucommon_s *)&s_controls.m4,
	(menucommon_s *)&s_controls.akimbos,
	(menucommon_s *)&s_controls.knife,
	(menucommon_s *)&s_controls.grenade,
	NULL,
};

static menucommon_s *g_looking_controls[] = {
	(menucommon_s *)&s_controls.sensitivity,
	(menucommon_s *)&s_controls.smoothmouse,
	(menucommon_s *)&s_controls.invertmouse,
	(menucommon_s *)&s_controls.lookup,
	(menucommon_s *)&s_controls.lookdown,
	(menucommon_s *)&s_controls.mouselook,
	(menucommon_s *)&s_controls.freelook,
	(menucommon_s *)&s_controls.centerview,
	(menucommon_s *)&s_controls.zoomview,
	(menucommon_s *)&s_controls.joyenable,
	(menucommon_s *)&s_controls.joythreshold,
	NULL,
};

static menucommon_s *g_misc_controls[] = {
	(menucommon_s *)&s_controls.showscores,
	(menucommon_s *)&s_controls.useitem,
	(menucommon_s *)&s_controls.gesture,
	(menucommon_s *)&s_controls.chat,
	(menucommon_s *)&s_controls.chat2,
	(menucommon_s *)&s_controls.chat3,
	(menucommon_s *)&s_controls.chat4,
	NULL,
};
//Blaze: Reaction Menu stuff
static menucommon_s *g_reaction_controls[] = {

	(menucommon_s *)&s_controls.bandage,
	(menucommon_s *)&s_controls.reload,
	(menucommon_s *)&s_controls.weapon,
	(menucommon_s *)&s_controls.opendoor,
	(menucommon_s *)&s_controls.dropweap,
	(menucommon_s *)&s_controls.dropitem,
	(menucommon_s *)&s_controls.irvision,
	NULL,

};



static menucommon_s **g_controls[] = {
	g_movement_controls,
	g_looking_controls,
	g_weapons_controls,
	g_misc_controls,
	//Blaze: Reaction menu
	g_reaction_controls,
};

/*
=================
Controls_InitCvars
=================
*/
static void Controls_InitCvars( void )
{
	int				i;
	configcvar_t*	cvarptr;

	cvarptr = g_configcvars;
	for (i=0; ;i++,cvarptr++)
	{
		if (!cvarptr->name)
			break;

		// get current value
		cvarptr->value = trap_Cvar_VariableValue( cvarptr->name );

		// get default value
		trap_Cvar_Reset( cvarptr->name );
		cvarptr->defaultvalue = trap_Cvar_VariableValue( cvarptr->name );

		// restore current value
		trap_Cvar_SetValue( cvarptr->name, cvarptr->value );
	}
}

/*
=================
Controls_GetCvarDefault
=================
*/
static float Controls_GetCvarDefault( char* name )
{
	configcvar_t*	cvarptr;
	int				i;

	cvarptr = g_configcvars;
	for (i=0; ;i++,cvarptr++)
	{
		if (!cvarptr->name)
			return (0);

		if (!strcmp(cvarptr->name,name))
			break;
	}

	return (cvarptr->defaultvalue);
}

/*
=================
Controls_GetCvarValue
=================
*/
static float Controls_GetCvarValue( char* name )
{
	configcvar_t*	cvarptr;
	int				i;

	cvarptr = g_configcvars;
	for (i=0; ;i++,cvarptr++)
	{
		if (!cvarptr->name)
			return (0);

		if (!strcmp(cvarptr->name,name))
			break;
	}

	return (cvarptr->value);
}


/*
=================
Controls_UpdateModel
=================
*/
static void Controls_UpdateModel( int anim ) {
	VectorClear( s_controls.playerViewangles );
	VectorClear( s_controls.playerMoveangles );
	s_controls.playerViewangles[YAW] = 180 - 30;
	s_controls.playerMoveangles[YAW] = s_controls.playerViewangles[YAW];
	s_controls.playerLegs		     = LEGS_IDLE;
	s_controls.playerTorso			 = TORSO_STAND;
	s_controls.playerWeapon			 = -1;
	s_controls.playerChat			 = qfalse;

	switch( anim ) {
	case ANIM_RUN:
		s_controls.playerLegs = LEGS_RUN;
		break;

	case ANIM_WALK:
		s_controls.playerLegs = LEGS_WALK;
		break;

	case ANIM_BACK:
		s_controls.playerLegs = LEGS_BACK;
		break;

	case ANIM_JUMP:
		s_controls.playerLegs = LEGS_JUMP;
		break;

	case ANIM_CROUCH:
		s_controls.playerLegs = LEGS_IDLECR;
		break;

	case ANIM_TURNLEFT:
		s_controls.playerViewangles[YAW] += 90;
		break;

	case ANIM_TURNRIGHT:
		s_controls.playerViewangles[YAW] -= 90;
		break;

	case ANIM_STEPLEFT:
		s_controls.playerLegs = LEGS_WALK;
		s_controls.playerMoveangles[YAW] = s_controls.playerViewangles[YAW] + 90;
		break;

	case ANIM_STEPRIGHT:
		s_controls.playerLegs = LEGS_WALK;
		s_controls.playerMoveangles[YAW] = s_controls.playerViewangles[YAW] - 90;
		break;

	case ANIM_LOOKUP:
		s_controls.playerViewangles[PITCH] = -45;
		break;

	case ANIM_LOOKDOWN:
		s_controls.playerViewangles[PITCH] = 45;
		break;
//Blaze: Dont need gauntlet animation
//	case ANIM_WEAPON1:
//		s_controls.playerWeapon = WP_GAUNTLET;
//		break;
//Blaze: Dont need this
/*	case ANIM_WEAPON2:
		s_controls.playerWeapon = WP_MACHINEGUN;
		break;
*/
//Blaze: Reaction weapons
	case ANIM_WEAPON1:
		s_controls.playerTorso = TORSO_STAND;
		s_controls.playerWeapon = WP_PISTOL;
		break;

	case ANIM_WEAPON2:
		s_controls.playerTorso = TORSO_STAND;
		s_controls.playerWeapon = WP_M3;
		break;

	case ANIM_WEAPON3:
		s_controls.playerTorso = TORSO_STAND;
		s_controls.playerWeapon = WP_MP5;
		break;

	case ANIM_WEAPON4:
		s_controls.playerTorso = TORSO_STAND;
		s_controls.playerWeapon = WP_HANDCANNON;
		break;

	case ANIM_WEAPON5:
		s_controls.playerTorso = TORSO_STAND;
		s_controls.playerWeapon = WP_SSG3000;
		break;

	case ANIM_WEAPON6:
		s_controls.playerTorso = TORSO_STAND;
		s_controls.playerWeapon = WP_M4;
		break;

	case ANIM_WEAPON7:
		s_controls.playerTorso = TORSO_STAND;
		s_controls.playerWeapon = WP_AKIMBO;
		break;

	case ANIM_WEAPON8:
		s_controls.playerTorso = TORSO_STAND2;
		s_controls.playerWeapon = WP_KNIFE;
		break;

	case ANIM_WEAPON9:
		s_controls.playerTorso = TORSO_STAND2;
		s_controls.playerWeapon = WP_GRENADE;
		break;

	case ANIM_ATTACK:
		if ( s_controls.playerWeapon == WP_GRENADE ||
			s_controls.playerWeapon == WP_KNIFE )
			s_controls.playerTorso = TORSO_ATTACK2;
		else
			s_controls.playerTorso = TORSO_ATTACK;
		break;

	case ANIM_GESTURE:
		s_controls.playerTorso = TORSO_GESTURE;
		break;

	case ANIM_DIE:
		s_controls.playerLegs = BOTH_DEATH1;
		s_controls.playerTorso = BOTH_DEATH1;
		s_controls.playerWeapon = WP_NONE;
		break;

	case ANIM_CHAT:
		s_controls.playerChat = qtrue;
		break;
	case ANIM_RELOAD:
		//Com_Printf("At Reload");
		//s_controls.weapon.generic.
		break;

	default:
		break;
	}

	UI_PlayerInfo_SetInfo( &s_controls.playerinfo, s_controls.playerLegs, s_controls.playerTorso, s_controls.playerViewangles, s_controls.playerMoveangles, s_controls.playerWeapon, s_controls.playerChat );
}


/*
=================
Controls_Update
=================
*/
static void Controls_Update( void ) {
	int		i;
	int		j;
	int		y;
	menucommon_s	**controls;
	menucommon_s	*control;

	// disable all controls in all groups
	for( i = 0; i < C_MAX; i++ ) {
		controls = g_controls[i];
		// bk001204 - parentheses
		for( j = 0;  (control = controls[j]) ; j++ ) {
			control->flags |= (QMF_HIDDEN|QMF_INACTIVE);
		}
	}

	controls = g_controls[s_controls.section];

	// enable controls in active group (and count number of items for vertical centering)
	// bk001204 - parentheses
	for( j = 0;  (control = controls[j]) ; j++ ) {
		control->flags &= ~(QMF_GRAYED|QMF_HIDDEN|QMF_INACTIVE);
	}

	// position controls
	y = ( SCREEN_HEIGHT - j * SMALLCHAR_HEIGHT ) / 2;
	// bk001204 - parentheses
	for( j = 0;	(control = controls[j]) ; j++, y += SMALLCHAR_HEIGHT ) {
		//Elder: changed from 320
		control->x      = 200;
		control->y      = y;
		control->left   = 200 - 19*SMALLCHAR_WIDTH;
		control->right  = 200 + 21*SMALLCHAR_WIDTH;
		control->top    = y;
		control->bottom = y + SMALLCHAR_HEIGHT;
	}

	if( s_controls.waitingforkey ) {
		// disable everybody
		for( i = 0; i < s_controls.menu.nitems; i++ ) {
			((menucommon_s*)(s_controls.menu.items[i]))->flags |= QMF_GRAYED;
		}

		// enable action item
		((menucommon_s*)(s_controls.menu.items[s_controls.menu.cursor]))->flags &= ~QMF_GRAYED;

		// don't gray out player's name
		//s_controls.name.generic.flags &= ~QMF_GRAYED;

		return;
	}

	// enable everybody
	for( i = 0; i < s_controls.menu.nitems; i++ ) {
		((menucommon_s*)(s_controls.menu.items[i]))->flags &= ~QMF_GRAYED;
	}

	// makes sure flags are right on the group selection controls
	s_controls.looking.generic.flags  &= ~(QMF_GRAYED|QMF_HIGHLIGHT|QMF_PULSEIFFOCUS);
	s_controls.movement.generic.flags &= ~(QMF_GRAYED|QMF_HIGHLIGHT|QMF_PULSEIFFOCUS);
	s_controls.weapons.generic.flags  &= ~(QMF_GRAYED|QMF_HIGHLIGHT|QMF_PULSEIFFOCUS);
	s_controls.misc.generic.flags     &= ~(QMF_GRAYED|QMF_HIGHLIGHT|QMF_PULSEIFFOCUS);
	s_controls.reaction.generic.flags &= ~(QMF_GRAYED|QMF_HIGHLIGHT|QMF_PULSEIFFOCUS);

	s_controls.looking.generic.flags  |= QMF_HIGHLIGHT_IF_FOCUS;
	s_controls.movement.generic.flags |= QMF_HIGHLIGHT_IF_FOCUS;
	s_controls.weapons.generic.flags  |= QMF_HIGHLIGHT_IF_FOCUS;
	s_controls.misc.generic.flags     |= QMF_HIGHLIGHT_IF_FOCUS;
	s_controls.reaction.generic.flags |= QMF_HIGHLIGHT_IF_FOCUS;

	// set buttons
	switch( s_controls.section ) {
	case C_MOVEMENT:
		s_controls.movement.generic.flags &= ~QMF_PULSEIFFOCUS;
		s_controls.movement.generic.flags |= (QMF_HIGHLIGHT|QMF_HIGHLIGHT_IF_FOCUS);
		break;

	case C_LOOKING:
		s_controls.looking.generic.flags &= ~QMF_PULSEIFFOCUS;
		s_controls.looking.generic.flags |= (QMF_HIGHLIGHT|QMF_HIGHLIGHT_IF_FOCUS);
		break;

	case C_WEAPONS:
		s_controls.weapons.generic.flags &= ~QMF_PULSEIFFOCUS;
		s_controls.weapons.generic.flags |= (QMF_HIGHLIGHT|QMF_HIGHLIGHT_IF_FOCUS);
		break;

	case C_MISC:
		s_controls.misc.generic.flags &= ~QMF_PULSEIFFOCUS;
		s_controls.misc.generic.flags |= (QMF_HIGHLIGHT|QMF_HIGHLIGHT_IF_FOCUS);
		break;
		//Blaze: Reaction case
	case C_REACTION:
		s_controls.reaction.generic.flags &= ~QMF_PULSEIFFOCUS;
		s_controls.reaction.generic.flags |= (QMF_HIGHLIGHT|QMF_HIGHLIGHT_IF_FOCUS);
		break;
	}
}


/*
=================
Controls_DrawKeyBinding
=================
*/
static void Controls_DrawKeyBinding( void *self )
{
	menuaction_s*	a;
	int				x;
	int				y;
	int				b1;
	int				b2;
	qboolean		c;
	char			name[32];
	char			name2[32];

	a = (menuaction_s*) self;

	x =	a->generic.x;
	y = a->generic.y;

	c = (Menu_ItemAtCursor( a->generic.parent ) == a);

	b1 = g_bindings[a->generic.id].bind1;
	if (b1 == -1)
		strcpy(name,"???");
	else
	{
		trap_Key_KeynumToStringBuf( b1, name, 32 );
		Q_strupr(name);

		b2 = g_bindings[a->generic.id].bind2;
		if (b2 != -1)
		{
			trap_Key_KeynumToStringBuf( b2, name2, 32 );
			Q_strupr(name2);

			strcat( name, " or " );
			strcat( name, name2 );
		}
	}

	if (c)
	{
		UI_FillRect( a->generic.left, a->generic.top, a->generic.right-a->generic.left+1, a->generic.bottom-a->generic.top+1, listbar_color );

		UI_DrawString( x - SMALLCHAR_WIDTH, y, g_bindings[a->generic.id].label, UI_RIGHT|UI_SMALLFONT, text_color_highlight );
		UI_DrawString( x + SMALLCHAR_WIDTH, y, name, UI_LEFT|UI_SMALLFONT|UI_PULSE, text_color_highlight );

		if (s_controls.waitingforkey)
		{
			UI_DrawChar( x, y, '=', UI_CENTER|UI_BLINK|UI_SMALLFONT, text_color_highlight);
			UI_DrawString(SCREEN_WIDTH * 0.50, SCREEN_HEIGHT * 0.80, "Waiting for new key ... ESCAPE to cancel", UI_SMALLFONT|UI_CENTER|UI_PULSE, colorWhite );
		}
		else
		{
			UI_DrawChar( x, y, 13, UI_CENTER|UI_BLINK|UI_SMALLFONT, text_color_highlight);
			UI_DrawString(SCREEN_WIDTH * 0.50, SCREEN_HEIGHT * 0.78, "Press ENTER or CLICK to change", UI_SMALLFONT|UI_CENTER, colorWhite );
			UI_DrawString(SCREEN_WIDTH * 0.50, SCREEN_HEIGHT * 0.82, "Press BACKSPACE to clear", UI_SMALLFONT|UI_CENTER, colorWhite );
		}
	}
	else
	{
		if (a->generic.flags & QMF_GRAYED)
		{
			UI_DrawString( x - SMALLCHAR_WIDTH, y, g_bindings[a->generic.id].label, UI_RIGHT|UI_SMALLFONT, text_color_disabled );
			UI_DrawString( x + SMALLCHAR_WIDTH, y, name, UI_LEFT|UI_SMALLFONT, text_color_disabled );
		}
		else
		{
			UI_DrawString( x - SMALLCHAR_WIDTH, y, g_bindings[a->generic.id].label, UI_RIGHT|UI_SMALLFONT, controls_binding_color );
			UI_DrawString( x + SMALLCHAR_WIDTH, y, name, UI_LEFT|UI_SMALLFONT, controls_binding_color );
		}
	}
}

/*
=================
Controls_StatusBar
=================
*/
static void Controls_StatusBar( void *self )
{
	UI_DrawString(SCREEN_WIDTH * 0.50, SCREEN_HEIGHT * 0.80, "Use Arrow Keys or CLICK to change", UI_SMALLFONT|UI_CENTER, colorWhite );
}


/*
=================
Controls_DrawPlayer
=================
*/
static void Controls_DrawPlayer( void *self ) {
	menubitmap_s	*b;
	char			buf[MAX_QPATH];

	trap_Cvar_VariableStringBuffer( "model", buf, sizeof( buf ) );
	if ( strcmp( buf, s_controls.playerModel ) != 0 ) {
		UI_PlayerInfo_SetModel( &s_controls.playerinfo, buf );
		strcpy( s_controls.playerModel, buf );
		Controls_UpdateModel( ANIM_IDLE );
	}

	b = (menubitmap_s*) self;
	UI_DrawPlayer( b->generic.x, b->generic.y, b->width, b->height, &s_controls.playerinfo, uis.realtime/2 );
}


/*
=================
Controls_GetKeyAssignment
=================
*/
static void Controls_GetKeyAssignment (char *command, int *twokeys)
{
	int		count;
	int		j;
	char	b[256];

	twokeys[0] = twokeys[1] = -1;
	count = 0;

	for ( j = 0; j < 256; j++ )
	{
		trap_Key_GetBindingBuf( j, b, 256 );
		if ( *b == 0 ) {
			continue;
		}
		if ( !Q_stricmp( b, command ) ) {
			twokeys[count] = j;
			count++;
			if (count == 2)
				break;
		}
	}
}

/*
=================
Controls_GetConfig
=================
*/
static void Controls_GetConfig( void )
{
	int		i;
	int		twokeys[2];
	bind_t*	bindptr;

	// put the bindings into a local store
	bindptr = g_bindings;

	// iterate each command, get its numeric binding
	for (i=0; ;i++,bindptr++)
	{
		if (!bindptr->label)
			break;

		Controls_GetKeyAssignment(bindptr->command, twokeys);

		bindptr->bind1 = twokeys[0];
		bindptr->bind2 = twokeys[1];
	}

	s_controls.invertmouse.curvalue  = Controls_GetCvarValue( "m_pitch" ) < 0;
	s_controls.smoothmouse.curvalue  = UI_ClampCvar( 0, 1, Controls_GetCvarValue( "m_filter" ) );
	s_controls.alwaysrun.curvalue    = UI_ClampCvar( 0, 1, Controls_GetCvarValue( "cl_run" ) );
	s_controls.autoswitch.curvalue   = UI_ClampCvar( 0, 1, Controls_GetCvarValue( "cg_autoswitch" ) );
	s_controls.sensitivity.curvalue  = UI_ClampCvar( 2, 30, Controls_GetCvarValue( "sensitivity" ) );
	s_controls.joyenable.curvalue    = UI_ClampCvar( 0, 1, Controls_GetCvarValue( "in_joystick" ) );
	s_controls.joythreshold.curvalue = UI_ClampCvar( 0.05f, 0.75f, Controls_GetCvarValue( "joy_threshold" ) );
	s_controls.freelook.curvalue     = UI_ClampCvar( 0, 1, Controls_GetCvarValue( "cl_freelook" ) );
}

/*
=================
Controls_SetConfig
=================
*/
static void Controls_SetConfig( void )
{
	int		i;
	bind_t*	bindptr;

	// set the bindings from the local store
	bindptr = g_bindings;

	// iterate each command, get its numeric binding
	for (i=0; ;i++,bindptr++)
	{
		if (!bindptr->label)
			break;

		if (bindptr->bind1 != -1)
		{
			trap_Key_SetBinding( bindptr->bind1, bindptr->command );

			if (bindptr->bind2 != -1)
				trap_Key_SetBinding( bindptr->bind2, bindptr->command );
		}
	}

	if ( s_controls.invertmouse.curvalue )
		trap_Cvar_SetValue( "m_pitch", -fabs( trap_Cvar_VariableValue( "m_pitch" ) ) );
	else
		trap_Cvar_SetValue( "m_pitch", fabs( trap_Cvar_VariableValue( "m_pitch" ) ) );

	trap_Cvar_SetValue( "m_filter", s_controls.smoothmouse.curvalue );
	trap_Cvar_SetValue( "cl_run", s_controls.alwaysrun.curvalue );
	trap_Cvar_SetValue( "cg_autoswitch", s_controls.autoswitch.curvalue );
	trap_Cvar_SetValue( "sensitivity", s_controls.sensitivity.curvalue );
	trap_Cvar_SetValue( "in_joystick", s_controls.joyenable.curvalue );
	trap_Cvar_SetValue( "joy_threshold", s_controls.joythreshold.curvalue );
	trap_Cvar_SetValue( "cl_freelook", s_controls.freelook.curvalue );
	trap_Cmd_ExecuteText( EXEC_APPEND, "in_restart\n" );
}

/*
=================
Controls_SetDefaults
=================
*/
static void Controls_SetDefaults( void )
{
	int	i;
	bind_t*	bindptr;

	// set the bindings from the local store
	bindptr = g_bindings;

	// iterate each command, set its default binding
	for (i=0; ;i++,bindptr++)
	{
		if (!bindptr->label)
			break;

		bindptr->bind1 = bindptr->defaultbind1;
		bindptr->bind2 = bindptr->defaultbind2;
	}

	s_controls.invertmouse.curvalue  = Controls_GetCvarDefault( "m_pitch" ) < 0;
	s_controls.smoothmouse.curvalue  = Controls_GetCvarDefault( "m_filter" );
	s_controls.alwaysrun.curvalue    = Controls_GetCvarDefault( "cl_run" );
	s_controls.autoswitch.curvalue   = Controls_GetCvarDefault( "cg_autoswitch" );
	s_controls.sensitivity.curvalue  = Controls_GetCvarDefault( "sensitivity" );
	s_controls.joyenable.curvalue    = Controls_GetCvarDefault( "in_joystick" );
	s_controls.joythreshold.curvalue = Controls_GetCvarDefault( "joy_threshold" );
	s_controls.freelook.curvalue     = Controls_GetCvarDefault( "cl_freelook" );
}

/*
=================
Controls_MenuKey
=================
*/
static sfxHandle_t Controls_MenuKey( int key )
{
	int			id;
	int			i;
	qboolean	found;
	bind_t*		bindptr;
	found = qfalse;

	if (!s_controls.waitingforkey)
	{
		switch (key)
		{
			case K_BACKSPACE:
			case K_DEL:
			case K_KP_DEL:
				key = -1;
				break;

			case K_MOUSE2:
			case K_ESCAPE:
				if (s_controls.changesmade)
					Controls_SetConfig();
				goto ignorekey;

			default:
				goto ignorekey;
		}
	}
	else
	{
		if (key & K_CHAR_FLAG)
			goto ignorekey;

		switch (key)
		{
			case K_ESCAPE:
				s_controls.waitingforkey = qfalse;
				Controls_Update();
				return (menu_out_sound);

			case '`':
				goto ignorekey;
		}
	}

	s_controls.changesmade = qtrue;

	if (key != -1)
	{
		// remove from any other bind
		bindptr = g_bindings;
		for (i=0; ;i++,bindptr++)
		{
			if (!bindptr->label)
				break;

			if (bindptr->bind2 == key)
				bindptr->bind2 = -1;

			if (bindptr->bind1 == key)
			{
				bindptr->bind1 = bindptr->bind2;
				bindptr->bind2 = -1;
			}
		}
	}

	// assign key to local store
	id      = ((menucommon_s*)(s_controls.menu.items[s_controls.menu.cursor]))->id;
	bindptr = g_bindings;
	for (i=0; ;i++,bindptr++)
	{
		if (!bindptr->label)
			break;

		if (bindptr->id == id)
		{
			found = qtrue;
			if (key == -1)
			{
				if( bindptr->bind1 != -1 ) {
					trap_Key_SetBinding( bindptr->bind1, "" );
					bindptr->bind1 = -1;
				}
				if( bindptr->bind2 != -1 ) {
					trap_Key_SetBinding( bindptr->bind2, "" );
					bindptr->bind2 = -1;
				}
			}
			else if (bindptr->bind1 == -1) {
				bindptr->bind1 = key;
			}
			else if (bindptr->bind1 != key && bindptr->bind2 == -1) {
				bindptr->bind2 = key;
			}
			else
			{
				trap_Key_SetBinding( bindptr->bind1, "" );
				trap_Key_SetBinding( bindptr->bind2, "" );
				bindptr->bind1 = key;
				bindptr->bind2 = -1;
			}
			break;
		}
	}

	s_controls.waitingforkey = qfalse;

	if (found)
	{
		Controls_Update();
		return (menu_out_sound);
	}

ignorekey:
	return Menu_DefaultKey( &s_controls.menu, key );
}

/*
=================
Controls_ResetDefaults_Action
=================
*/
static void Controls_ResetDefaults_Action( qboolean result ) {
	if( !result ) {
		return;
	}

	s_controls.changesmade = qtrue;
	Controls_SetDefaults();
	Controls_Update();
}

/*
=================
Controls_ResetDefaults_Draw
=================
*/
static void Controls_ResetDefaults_Draw( void ) {
	UI_DrawProportionalString( SCREEN_WIDTH/2, 356 + PROP_HEIGHT * 0, "WARNING: This will reset all", UI_CENTER|UI_SMALLFONT, color_yellow );
	UI_DrawProportionalString( SCREEN_WIDTH/2, 356 + PROP_HEIGHT * 1, "controls to their default values.", UI_CENTER|UI_SMALLFONT, color_yellow );
}

/*
=================
Controls_MenuEvent
=================
*/
static void Controls_MenuEvent( void* ptr, int event )
{
	//Elder: for status bar
	if( event == QM_LOSTFOCUS ) {
		s_controls.rq3_statustext.string = "";
		return;
	}
	else if ( event == QM_GOTFOCUS )
	{
		switch( ((menucommon_s*)ptr)->id )
		{
			case ID_MOVEMENT:
				s_controls.rq3_statustext.string = "Change movement keys";
				break;
			case ID_LOOKING:
				s_controls.rq3_statustext.string = "Change view keys";
				break;
			case ID_WEAPONS:
				s_controls.rq3_statustext.string = "Change weapon keys";
				break;
			case ID_MISC:
				s_controls.rq3_statustext.string = "Change miscellaneous keys";
				break;
			case ID_REACTION:
				s_controls.rq3_statustext.string = "Change Reaction-specific keys";
				break;
			case ID_BACK:
				s_controls.rq3_statustext.string = "Return to setup menu";
				break;
			default:
				s_controls.rq3_statustext.string = "";
				break;
		}
	}
	else if ( event == QM_ACTIVATED )
	{
		switch (((menucommon_s*)ptr)->id)
		{
			case ID_MOVEMENT:
				//if (event == QM_ACTIVATED)
				//{
					s_controls.section = C_MOVEMENT;
					Controls_Update();
				//}
				break;

			case ID_LOOKING:
				//if (event == QM_ACTIVATED)
				//{
					s_controls.section = C_LOOKING;
					Controls_Update();
				//}
				break;

			case ID_WEAPONS:
				//if (event == QM_ACTIVATED)
				//{
					s_controls.section = C_WEAPONS;
					Controls_Update();
				//}
				break;

			case ID_MISC:
				//if (event == QM_ACTIVATED)
				//{
					s_controls.section = C_MISC;
					Controls_Update();
				//}
				break;
	//Blaze: Reaction Menu
			case ID_REACTION:
				//if (event == QM_ACTIVATED)
				//{
					s_controls.section = C_REACTION;
					Controls_Update();
				//}
				break;
			case ID_DEFAULTS:
				//if (event == QM_ACTIVATED)
				//{
					UI_ConfirmMenu( "SET TO DEFAULTS?", Controls_ResetDefaults_Draw, Controls_ResetDefaults_Action );
				//}
				break;

			case ID_BACK:
				//if (event == QM_ACTIVATED)
				//{
					if (s_controls.changesmade)
						Controls_SetConfig();
					UI_PopMenu();
				//}
				break;

			case ID_SAVEANDEXIT:
				//if (event == QM_ACTIVATED)
				//{
					Controls_SetConfig();
					UI_PopMenu();
				//}
				break;

			case ID_EXIT:
				//if (event == QM_ACTIVATED)
				//{
					UI_PopMenu();
				//}
				break;

			case ID_FREELOOK:
			case ID_MOUSESPEED:
			case ID_INVERTMOUSE:
			case ID_SMOOTHMOUSE:
			case ID_ALWAYSRUN:
			case ID_AUTOSWITCH:
			case ID_JOYENABLE:
			case ID_JOYTHRESHOLD:
				//if (event == QM_ACTIVATED)
				//{
					s_controls.changesmade = qtrue;
				//}
				break;
		}
	}
}

/*
=================
Controls_ActionEvent
=================
*/
static void Controls_ActionEvent( void* ptr, int event )
{
	if (event == QM_LOSTFOCUS)
	{
		Controls_UpdateModel( ANIM_IDLE );
	}
	else if (event == QM_GOTFOCUS)
	{
		Controls_UpdateModel( g_bindings[((menucommon_s*)ptr)->id].anim );
	}
	else if ((event == QM_ACTIVATED) && !s_controls.waitingforkey)
	{
		s_controls.waitingforkey = 1;
		Controls_Update();
	}
}

/*
=================
Controls_InitModel
=================
*/
static void Controls_InitModel( void )
{
	memset( &s_controls.playerinfo, 0, sizeof(playerInfo_t) );

	UI_PlayerInfo_SetModel( &s_controls.playerinfo, UI_Cvar_VariableString( "model" ) );

	Controls_UpdateModel( ANIM_IDLE );
}

/*
=================
Controls_InitWeapons
=================
*/
static void Controls_InitWeapons( void ) {
	gitem_t *	item;

	for ( item = bg_itemlist + 1 ; item->classname ; item++ ) {
		if ( item->giType != IT_WEAPON ) {
			continue;
		}
		trap_R_RegisterModel( item->world_model[0] );
	}
}

/*
===============
Added by Elder
Controls_MenuDraw
===============
*/
static void Controls_MenuDraw( void ) {
	//Elder: "Dim" and "Letterbox" mask
	UI_FillRect( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color_deepdim );
	UI_FillRect( 0, 0, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 54, SCREEN_WIDTH, 2, color_red);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 2, color_red);

	// standard menu drawing
	Menu_Draw( &s_controls.menu );
}

/*
=================
Controls_MenuInit
=================
*/
static void Controls_MenuInit( void )
{
	static char playername[32];
	// Elder: added
	int		buttonCount = 0;
	int		y = 12;

	// zero set all our globals
	memset( &s_controls, 0 ,sizeof(controls_t) );

	Controls_Cache();

	s_controls.menu.draw = Controls_MenuDraw;
	s_controls.menu.key        = Controls_MenuKey;
	s_controls.menu.wrapAround = qtrue;
	s_controls.menu.fullscreen = qtrue;
	s_controls.menu.showlogo = qtrue;//Blaze: Show Background logo

/*	s_controls.banner.generic.type	= MTYPE_BTEXT;
	s_controls.banner.generic.flags	= QMF_CENTER_JUSTIFY;
	s_controls.banner.generic.x		= 320;
	s_controls.banner.generic.y		= 16;
	s_controls.banner.string		= "CONTROLS";
	s_controls.banner.color			= color_white;
	s_controls.banner.style			= UI_CENTER;

	s_controls.framel.generic.type  = MTYPE_BITMAP;
	s_controls.framel.generic.name  = ART_FRAMEL;
	s_controls.framel.generic.flags = QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	s_controls.framel.generic.x     = 0;
	s_controls.framel.generic.y     = 78;
	s_controls.framel.width  	    = 256;
	s_controls.framel.height  	    = 329;

	s_controls.framer.generic.type  = MTYPE_BITMAP;
	s_controls.framer.generic.name  = ART_FRAMER;
	s_controls.framer.generic.flags = QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	s_controls.framer.generic.x     = 376;
	s_controls.framer.generic.y     = 76;
	s_controls.framer.width  	    = 256;
	s_controls.framer.height  	    = 334;
*/
/*
	s_controls.multim.generic.type		= MTYPE_PTEXT;
	s_controls.multim.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_controls.multim.generic.x			= 120;
	s_controls.multim.generic.y			= 3;
	s_controls.multim.string			= "MULTIPLAYER";
	s_controls.multim.color				= color_red;
	s_controls.multim.style				= UI_CENTER | UI_DROPSHADOW;

	s_controls.setupm.generic.type		= MTYPE_PTEXT;
	s_controls.setupm.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_INACTIVE|QMF_HIGHLIGHT;
	s_controls.setupm.generic.x			= 280;
	s_controls.setupm.generic.y			= 3;
	s_controls.setupm.string			= "SETUP";
	s_controls.setupm.color				= color_red;
	s_controls.setupm.style				= UI_CENTER | UI_DROPSHADOW;

	s_controls.demom.generic.type		= MTYPE_PTEXT;
	s_controls.demom.generic.flags		= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_controls.demom.generic.x			= 390;
	s_controls.demom.generic.y			= 3;
	s_controls.demom.string				= "DEMOS";
	s_controls.demom.color				= color_red;
	s_controls.demom.style				= UI_CENTER | UI_DROPSHADOW;

	s_controls.modsm.generic.type		= MTYPE_PTEXT;
	s_controls.modsm.generic.flags 		= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_controls.modsm.generic.x			= 500;
	s_controls.modsm.generic.y			= 3;
	s_controls.modsm.string				= "MODS";
	s_controls.modsm.color				= color_red;
	s_controls.modsm.style				= UI_CENTER | UI_DROPSHADOW;

	s_controls.exitm.generic.type		= MTYPE_PTEXT;
	s_controls.exitm.generic.flags  	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_controls.exitm.generic.x			= 590;
	s_controls.exitm.generic.y			= 3;
	s_controls.exitm.string				= "EXIT";
	s_controls.exitm.color				= color_red;
	s_controls.exitm.style				= UI_CENTER | UI_DROPSHADOW;
*/

	//Elder: Info for setup icon
	s_controls.rq3_setupicon.generic.type				= MTYPE_BITMAP;
	s_controls.rq3_setupicon.generic.name				= RQ3_SETUP_ICON;
	s_controls.rq3_setupicon.generic.flags				= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	s_controls.rq3_setupicon.generic.x					= 0;
	s_controls.rq3_setupicon.generic.y					= 4;
	s_controls.rq3_setupicon.width						= RQ3_ICON_WIDTH;
	s_controls.rq3_setupicon.height						= RQ3_ICON_HEIGHT;

	//Elder: Info for setup title
	s_controls.rq3_setuptitle.generic.type				= MTYPE_BITMAP;
	s_controls.rq3_setuptitle.generic.name				= RQ3_SETUP_TITLE;
	s_controls.rq3_setuptitle.generic.flags				= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	s_controls.rq3_setuptitle.generic.x					= 64;
	s_controls.rq3_setuptitle.generic.y					= 12;
	s_controls.rq3_setuptitle.width						= 256;
	s_controls.rq3_setuptitle.height						= 32;

	//Elder: RQ3 Status Text
	s_controls.rq3_statustext.generic.type 		= MTYPE_TEXT;
	s_controls.rq3_statustext.generic.flags		= QMF_CENTER_JUSTIFY;
	s_controls.rq3_statustext.generic.x 		= RQ3_STATUSBAR_X;
	s_controls.rq3_statustext.generic.y 		= RQ3_STATUSBAR_Y;
	s_controls.rq3_statustext.string 			= "";
	s_controls.rq3_statustext.style 			= UI_CENTER|UI_SMALLFONT;
	s_controls.rq3_statustext.color 			= color_orange;


	/*
	s_controls.looking.generic.type     = MTYPE_PTEXT;
	s_controls.looking.generic.flags    = QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	s_controls.looking.generic.id	    = ID_LOOKING;
	s_controls.looking.generic.callback	= Controls_MenuEvent;
	s_controls.looking.generic.x	    = 152;
	s_controls.looking.generic.y	    = 240 - 2 * PROP_HEIGHT;
	s_controls.looking.string			= "LOOK";
	s_controls.looking.style			= UI_RIGHT;
	s_controls.looking.color			= color_red;
	*/

	//Elder: RQ3 Looking Button
	s_controls.looking.generic.type		= MTYPE_BITMAP;
	s_controls.looking.generic.name		= RQ3_LOOKING_BUTTON;
	s_controls.looking.generic.flags	= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	s_controls.looking.generic.x		= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	s_controls.looking.generic.y		= y;
	s_controls.looking.generic.id		= ID_LOOKING;
	s_controls.looking.generic.callback	= Controls_MenuEvent;
	s_controls.looking.width			= RQ3_BUTTON_WIDTH;
	s_controls.looking.height			= RQ3_BUTTON_HEIGHT;
	s_controls.looking.focuspic			= RQ3_FOCUS_BUTTON;

	/*
	s_controls.movement.generic.type     = MTYPE_PTEXT;
	s_controls.movement.generic.flags    = QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	s_controls.movement.generic.id	     = ID_MOVEMENT;
	s_controls.movement.generic.callback = Controls_MenuEvent;
	s_controls.movement.generic.x	     = 152;
	s_controls.movement.generic.y	     = 240 - PROP_HEIGHT;
	s_controls.movement.string			= "MOVE";
	s_controls.movement.style			= UI_RIGHT;
	s_controls.movement.color			= color_red;
	*/

	//Elder: RQ3 Movement Button
	s_controls.movement.generic.type		= MTYPE_BITMAP;
	s_controls.movement.generic.name		= RQ3_MOVEMENT_BUTTON;
	s_controls.movement.generic.flags		= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	s_controls.movement.generic.x			= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	s_controls.movement.generic.y			= y;
	s_controls.movement.generic.id			= ID_MOVEMENT;
	s_controls.movement.generic.callback	= Controls_MenuEvent;
	s_controls.movement.width				= RQ3_BUTTON_WIDTH;
	s_controls.movement.height				= RQ3_BUTTON_HEIGHT;
	s_controls.movement.focuspic			= RQ3_FOCUS_BUTTON;

	/*
	s_controls.weapons.generic.type	    = MTYPE_PTEXT;
	s_controls.weapons.generic.flags    = QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	s_controls.weapons.generic.id	    = ID_WEAPONS;
	s_controls.weapons.generic.callback	= Controls_MenuEvent;
	s_controls.weapons.generic.x	    = 152;
	s_controls.weapons.generic.y	    = 240;
	s_controls.weapons.string			= "SHOOT";
	s_controls.weapons.style			= UI_RIGHT;
	s_controls.weapons.color			= color_red;
	*/

	//Elder: RQ3 Weapons Button
	s_controls.weapons.generic.type		= MTYPE_BITMAP;
	s_controls.weapons.generic.name		= RQ3_WEAPONS_BUTTON;
	s_controls.weapons.generic.flags	= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	s_controls.weapons.generic.x		= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	s_controls.weapons.generic.y		= y;
	s_controls.weapons.generic.id		= ID_WEAPONS;
	s_controls.weapons.generic.callback	= Controls_MenuEvent;
	s_controls.weapons.width			= RQ3_BUTTON_WIDTH;
	s_controls.weapons.height			= RQ3_BUTTON_HEIGHT;
	s_controls.weapons.focuspic			= RQ3_FOCUS_BUTTON;

	/*
	s_controls.misc.generic.type	 = MTYPE_PTEXT;
	s_controls.misc.generic.flags    = QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	s_controls.misc.generic.id	     = ID_MISC;
	s_controls.misc.generic.callback = Controls_MenuEvent;
	s_controls.misc.generic.x		 = 152;
	s_controls.misc.generic.y		 = 240 + PROP_HEIGHT;
	s_controls.misc.string			= "MISC";
	s_controls.misc.style			= UI_RIGHT;
	s_controls.misc.color			= color_red;
	*/

	//Elder: RQ3 Misc Button
	s_controls.misc.generic.type		= MTYPE_BITMAP;
	s_controls.misc.generic.name		= RQ3_MISC_BUTTON;
	s_controls.misc.generic.flags		= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	s_controls.misc.generic.x			= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	s_controls.misc.generic.y			= y;
	s_controls.misc.generic.id			= ID_MISC;
	s_controls.misc.generic.callback	= Controls_MenuEvent;
	s_controls.misc.width				= RQ3_BUTTON_WIDTH;
	s_controls.misc.height				= RQ3_BUTTON_HEIGHT;
	s_controls.misc.focuspic			= RQ3_FOCUS_BUTTON;

	//Blaze: Reaction section
	/*
	s_controls.reaction.generic.type	 = MTYPE_PTEXT;
	s_controls.reaction.generic.flags    = QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	s_controls.reaction.generic.id	     = ID_REACTION;
	s_controls.reaction.generic.callback = Controls_MenuEvent;
	s_controls.reaction.generic.x		 = 152;
	s_controls.reaction.generic.y		 = 240 + 2 * PROP_HEIGHT;
	s_controls.reaction.string			= "REACTION";
	s_controls.reaction.style			= UI_RIGHT;
	s_controls.reaction.color			= color_red;
	*/

	//Elder: RQ3 Reaction Button
	s_controls.reaction.generic.type		= MTYPE_BITMAP;
	s_controls.reaction.generic.name		= RQ3_REACTION_BUTTON;
	s_controls.reaction.generic.flags		= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	s_controls.reaction.generic.x			= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	s_controls.reaction.generic.y			= y;
	s_controls.reaction.generic.id			= ID_REACTION;
	s_controls.reaction.generic.callback	= Controls_MenuEvent;
	s_controls.reaction.width				= RQ3_BUTTON_WIDTH;
	s_controls.reaction.height				= RQ3_BUTTON_HEIGHT;
	s_controls.reaction.focuspic			= RQ3_FOCUS_BUTTON;

	s_controls.back.generic.type	 = MTYPE_BITMAP;
	s_controls.back.generic.name     = ART_BACK0;
	s_controls.back.generic.flags    = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	s_controls.back.generic.x		 = 8;
	s_controls.back.generic.y		 = 480-44;
	s_controls.back.generic.id	     = ID_BACK;
	s_controls.back.generic.callback = Controls_MenuEvent;
	s_controls.back.width  		     = 32;
	s_controls.back.height  		 = 32;
	s_controls.back.focuspic         = ART_BACK1;

	s_controls.player.generic.type      = MTYPE_BITMAP;
	s_controls.player.generic.flags     = QMF_INACTIVE;
	s_controls.player.generic.ownerdraw = Controls_DrawPlayer;
	s_controls.player.generic.x	        = 400;
	s_controls.player.generic.y	        = -40;
	s_controls.player.width	            = 32*10;
	s_controls.player.height            = 56*10;

	s_controls.walkforward.generic.type	     = MTYPE_ACTION;
	s_controls.walkforward.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.walkforward.generic.callback  = Controls_ActionEvent;
	s_controls.walkforward.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.walkforward.generic.id 	     = ID_FORWARD;

	s_controls.backpedal.generic.type	   = MTYPE_ACTION;
	s_controls.backpedal.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.backpedal.generic.callback  = Controls_ActionEvent;
	s_controls.backpedal.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.backpedal.generic.id 	   = ID_BACKPEDAL;

	s_controls.stepleft.generic.type	  = MTYPE_ACTION;
	s_controls.stepleft.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.stepleft.generic.callback  = Controls_ActionEvent;
	s_controls.stepleft.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.stepleft.generic.id 		  = ID_MOVELEFT;

	s_controls.stepright.generic.type	   = MTYPE_ACTION;
	s_controls.stepright.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.stepright.generic.callback  = Controls_ActionEvent;
	s_controls.stepright.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.stepright.generic.id        = ID_MOVERIGHT;

	s_controls.moveup.generic.type	    = MTYPE_ACTION;
	s_controls.moveup.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.moveup.generic.callback  = Controls_ActionEvent;
	s_controls.moveup.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.moveup.generic.id        = ID_MOVEUP;

	s_controls.movedown.generic.type	  = MTYPE_ACTION;
	s_controls.movedown.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.movedown.generic.callback  = Controls_ActionEvent;
	s_controls.movedown.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.movedown.generic.id        = ID_MOVEDOWN;

	s_controls.turnleft.generic.type	  = MTYPE_ACTION;
	s_controls.turnleft.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.turnleft.generic.callback  = Controls_ActionEvent;
	s_controls.turnleft.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.turnleft.generic.id        = ID_LEFT;

	s_controls.turnright.generic.type	   = MTYPE_ACTION;
	s_controls.turnright.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.turnright.generic.callback  = Controls_ActionEvent;
	s_controls.turnright.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.turnright.generic.id        = ID_RIGHT;

	s_controls.sidestep.generic.type	  = MTYPE_ACTION;
	s_controls.sidestep.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.sidestep.generic.callback  = Controls_ActionEvent;
	s_controls.sidestep.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.sidestep.generic.id        = ID_STRAFE;

	s_controls.run.generic.type	     = MTYPE_ACTION;
	s_controls.run.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.run.generic.callback  = Controls_ActionEvent;
	s_controls.run.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.run.generic.id        = ID_SPEED;

//Blaze: Dont need chainsaw <-gauntlet
/*	s_controls.chainsaw.generic.type	  = MTYPE_ACTION;
	s_controls.chainsaw.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.chainsaw.generic.callback  = Controls_ActionEvent;
	s_controls.chainsaw.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.chainsaw.generic.id        = ID_WEAPON1;
*/

//Blaze: dont need this anymore
/*	s_controls.machinegun.generic.type	    = MTYPE_ACTION;
	s_controls.machinegun.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.machinegun.generic.callback  = Controls_ActionEvent;
	s_controls.machinegun.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.machinegun.generic.id        = ID_WEAPON2;
*/
	s_controls.mk23.generic.type	     = MTYPE_ACTION;
	s_controls.mk23.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.mk23.generic.callback  = Controls_ActionEvent;
	s_controls.mk23.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.mk23.generic.id        = ID_WEAPON1;

	s_controls.m3.generic.type	     = MTYPE_ACTION;
	s_controls.m3.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.m3.generic.callback  = Controls_ActionEvent;
	s_controls.m3.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.m3.generic.id        = ID_WEAPON2;

	s_controls.mp5.generic.type	     = MTYPE_ACTION;
	s_controls.mp5.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.mp5.generic.callback  = Controls_ActionEvent;
	s_controls.mp5.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.mp5.generic.id        = ID_WEAPON3;

	s_controls.handcannon.generic.type	     = MTYPE_ACTION;
	s_controls.handcannon.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.handcannon.generic.callback  = Controls_ActionEvent;
	s_controls.handcannon.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.handcannon.generic.id        = ID_WEAPON4;

	s_controls.ssg3000.generic.type	    = MTYPE_ACTION;
	s_controls.ssg3000.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.ssg3000.generic.callback  = Controls_ActionEvent;
	s_controls.ssg3000.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.ssg3000.generic.id        = ID_WEAPON5;

	s_controls.m4.generic.type	    = MTYPE_ACTION;
	s_controls.m4.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.m4.generic.callback  = Controls_ActionEvent;
	s_controls.m4.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.m4.generic.id        = ID_WEAPON6;

	s_controls.akimbos.generic.type	   = MTYPE_ACTION;
	s_controls.akimbos.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.akimbos.generic.callback  = Controls_ActionEvent;
	s_controls.akimbos.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.akimbos.generic.id        = ID_WEAPON7;

	s_controls.knife.generic.type	     = MTYPE_ACTION;
	s_controls.knife.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.knife.generic.callback  = Controls_ActionEvent;
	s_controls.knife.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.knife.generic.id        = ID_WEAPON8;

	s_controls.grenade.generic.type	     = MTYPE_ACTION;
	s_controls.grenade.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.grenade.generic.callback  = Controls_ActionEvent;
	s_controls.grenade.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.grenade.generic.id        = ID_WEAPON9;


	s_controls.attack.generic.type	    = MTYPE_ACTION;
	s_controls.attack.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.attack.generic.callback  = Controls_ActionEvent;
	s_controls.attack.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.attack.generic.id        = ID_ATTACK;

	s_controls.prevweapon.generic.type	    = MTYPE_ACTION;
	s_controls.prevweapon.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.prevweapon.generic.callback  = Controls_ActionEvent;
	s_controls.prevweapon.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.prevweapon.generic.id        = ID_WEAPPREV;

	s_controls.nextweapon.generic.type	    = MTYPE_ACTION;
	s_controls.nextweapon.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.nextweapon.generic.callback  = Controls_ActionEvent;
	s_controls.nextweapon.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.nextweapon.generic.id        = ID_WEAPNEXT;

	s_controls.lookup.generic.type	    = MTYPE_ACTION;
	s_controls.lookup.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.lookup.generic.callback  = Controls_ActionEvent;
	s_controls.lookup.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.lookup.generic.id        = ID_LOOKUP;

	s_controls.lookdown.generic.type	  = MTYPE_ACTION;
	s_controls.lookdown.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.lookdown.generic.callback  = Controls_ActionEvent;
	s_controls.lookdown.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.lookdown.generic.id        = ID_LOOKDOWN;

	s_controls.mouselook.generic.type	   = MTYPE_ACTION;
	s_controls.mouselook.generic.flags     = QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.mouselook.generic.callback  = Controls_ActionEvent;
	s_controls.mouselook.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.mouselook.generic.id        = ID_MOUSELOOK;

	s_controls.freelook.generic.type		= MTYPE_RADIOBUTTON;
	s_controls.freelook.generic.flags		= QMF_SMALLFONT;
	s_controls.freelook.generic.x			= SCREEN_WIDTH/2;
	s_controls.freelook.generic.name		= "free look";
	s_controls.freelook.generic.id			= ID_FREELOOK;
	s_controls.freelook.generic.callback	= Controls_MenuEvent;
	s_controls.freelook.generic.statusbar	= Controls_StatusBar;

	s_controls.centerview.generic.type	    = MTYPE_ACTION;
	s_controls.centerview.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.centerview.generic.callback  = Controls_ActionEvent;
	s_controls.centerview.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.centerview.generic.id        = ID_CENTERVIEW;

	s_controls.zoomview.generic.type	  = MTYPE_ACTION;
	s_controls.zoomview.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.zoomview.generic.callback  = Controls_ActionEvent;
	s_controls.zoomview.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.zoomview.generic.id        = ID_ZOOMVIEW;

	s_controls.useitem.generic.type	     = MTYPE_ACTION;
	s_controls.useitem.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.useitem.generic.callback  = Controls_ActionEvent;
	s_controls.useitem.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.useitem.generic.id        = ID_USEITEM;

	s_controls.showscores.generic.type	    = MTYPE_ACTION;
	s_controls.showscores.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.showscores.generic.callback  = Controls_ActionEvent;
	s_controls.showscores.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.showscores.generic.id        = ID_SHOWSCORES;

	s_controls.invertmouse.generic.type      = MTYPE_RADIOBUTTON;
	s_controls.invertmouse.generic.flags	 = QMF_SMALLFONT;
	s_controls.invertmouse.generic.x	     = SCREEN_WIDTH/2;
	s_controls.invertmouse.generic.name	     = "invert mouse";
	s_controls.invertmouse.generic.id        = ID_INVERTMOUSE;
	s_controls.invertmouse.generic.callback  = Controls_MenuEvent;
	s_controls.invertmouse.generic.statusbar = Controls_StatusBar;

	s_controls.smoothmouse.generic.type      = MTYPE_RADIOBUTTON;
	s_controls.smoothmouse.generic.flags	 = QMF_SMALLFONT;
	s_controls.smoothmouse.generic.x	     = SCREEN_WIDTH/2;
	s_controls.smoothmouse.generic.name	     = "smooth mouse";
	s_controls.smoothmouse.generic.id        = ID_SMOOTHMOUSE;
	s_controls.smoothmouse.generic.callback  = Controls_MenuEvent;
	s_controls.smoothmouse.generic.statusbar = Controls_StatusBar;

	s_controls.alwaysrun.generic.type      = MTYPE_RADIOBUTTON;
	s_controls.alwaysrun.generic.flags	   = QMF_SMALLFONT;
	s_controls.alwaysrun.generic.x	       = SCREEN_WIDTH/2;
	s_controls.alwaysrun.generic.name	   = "always run";
	s_controls.alwaysrun.generic.id        = ID_ALWAYSRUN;
	s_controls.alwaysrun.generic.callback  = Controls_MenuEvent;
	s_controls.alwaysrun.generic.statusbar = Controls_StatusBar;

	s_controls.autoswitch.generic.type      = MTYPE_RADIOBUTTON;
	s_controls.autoswitch.generic.flags	    = QMF_SMALLFONT;
	s_controls.autoswitch.generic.x	        = SCREEN_WIDTH/2;
	s_controls.autoswitch.generic.name	    = "autoswitch weapons";
	s_controls.autoswitch.generic.id        = ID_AUTOSWITCH;
	s_controls.autoswitch.generic.callback  = Controls_MenuEvent;
	s_controls.autoswitch.generic.statusbar = Controls_StatusBar;

	s_controls.sensitivity.generic.type	     = MTYPE_SLIDER;
	s_controls.sensitivity.generic.x		 = SCREEN_WIDTH/2;
	s_controls.sensitivity.generic.flags	 = QMF_SMALLFONT;
	s_controls.sensitivity.generic.name	     = "mouse speed";
	s_controls.sensitivity.generic.id 	     = ID_MOUSESPEED;
	s_controls.sensitivity.generic.callback  = Controls_MenuEvent;
	s_controls.sensitivity.minvalue		     = 2;
	s_controls.sensitivity.maxvalue		     = 30;
	s_controls.sensitivity.generic.statusbar = Controls_StatusBar;

	s_controls.gesture.generic.type	     = MTYPE_ACTION;
	s_controls.gesture.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.gesture.generic.callback  = Controls_ActionEvent;
	s_controls.gesture.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.gesture.generic.id        = ID_GESTURE;

	s_controls.chat.generic.type	  = MTYPE_ACTION;
	s_controls.chat.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.chat.generic.callback  = Controls_ActionEvent;
	s_controls.chat.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.chat.generic.id        = ID_CHAT;

	s_controls.chat2.generic.type	   = MTYPE_ACTION;
	s_controls.chat2.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.chat2.generic.callback  = Controls_ActionEvent;
	s_controls.chat2.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.chat2.generic.id        = ID_CHAT2;

	s_controls.chat3.generic.type	   = MTYPE_ACTION;
	s_controls.chat3.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.chat3.generic.callback  = Controls_ActionEvent;
	s_controls.chat3.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.chat3.generic.id        = ID_CHAT3;

	s_controls.chat4.generic.type	   = MTYPE_ACTION;
	s_controls.chat4.generic.flags     = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.chat4.generic.callback  = Controls_ActionEvent;
	s_controls.chat4.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.chat4.generic.id        = ID_CHAT4;

	//Blaze: Reaction stuff

	s_controls.bandage.generic.type		= MTYPE_ACTION;
	s_controls.bandage.generic.flags	= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.bandage.generic.callback = Controls_ActionEvent;
	s_controls.bandage.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.bandage.generic.id		= ID_BANDAGE;

	s_controls.reload.generic.type		= MTYPE_ACTION;
	s_controls.reload.generic.flags		= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.reload.generic.callback	= Controls_ActionEvent;
	s_controls.reload.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.reload.generic.id		= ID_RELOAD;

	s_controls.weapon.generic.type		= MTYPE_ACTION;
	s_controls.weapon.generic.flags		= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.weapon.generic.callback = Controls_ActionEvent;
	s_controls.weapon.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.weapon.generic.id		= ID_WEAPON;

	s_controls.opendoor.generic.type	= MTYPE_ACTION;
	s_controls.opendoor.generic.flags	= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.opendoor.generic.callback = Controls_ActionEvent;
	s_controls.opendoor.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.opendoor.generic.id		= ID_OPENDOOR;

	s_controls.dropweap.generic.type		= MTYPE_ACTION;
	s_controls.dropweap.generic.flags	= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.dropweap.generic.callback = Controls_ActionEvent;
	s_controls.dropweap.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.dropweap.generic.id		= ID_DROPWEAP;

	s_controls.dropitem.generic.type		= MTYPE_ACTION;
	s_controls.dropitem.generic.flags	= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.dropitem.generic.callback = Controls_ActionEvent;
	s_controls.dropitem.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.dropitem.generic.id		= ID_DROPITEM;

	s_controls.irvision.generic.type	= MTYPE_ACTION;
	s_controls.irvision.generic.flags	= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_GRAYED|QMF_HIDDEN;
	s_controls.irvision.generic.callback = Controls_ActionEvent;
	s_controls.irvision.generic.ownerdraw = Controls_DrawKeyBinding;
	s_controls.irvision.generic.id		= ID_IRVISION;

	s_controls.joyenable.generic.type      = MTYPE_RADIOBUTTON;
	s_controls.joyenable.generic.flags	   = QMF_SMALLFONT;
	s_controls.joyenable.generic.x	       = SCREEN_WIDTH/2;
	s_controls.joyenable.generic.name	   = "joystick";
	s_controls.joyenable.generic.id        = ID_JOYENABLE;
	s_controls.joyenable.generic.callback  = Controls_MenuEvent;
	s_controls.joyenable.generic.statusbar = Controls_StatusBar;

	s_controls.joythreshold.generic.type	  = MTYPE_SLIDER;
	s_controls.joythreshold.generic.x		  = SCREEN_WIDTH/2;
	s_controls.joythreshold.generic.flags	  = QMF_SMALLFONT;
	s_controls.joythreshold.generic.name	  = "joystick threshold";
	s_controls.joythreshold.generic.id 	      = ID_JOYTHRESHOLD;
	s_controls.joythreshold.generic.callback  = Controls_MenuEvent;
	s_controls.joythreshold.minvalue		  = 0.05f;
	s_controls.joythreshold.maxvalue		  = 0.75f;
	s_controls.joythreshold.generic.statusbar = Controls_StatusBar;

	/*
	s_controls.name.generic.type	= MTYPE_PTEXT;
	s_controls.name.generic.flags	= QMF_CENTER_JUSTIFY|QMF_INACTIVE;
	s_controls.name.generic.x		= 320;
	s_controls.name.generic.y		= 440;
	s_controls.name.string			= playername;
	s_controls.name.style			= UI_CENTER;
	s_controls.name.color			= text_color_normal;
	*/
//	Menu_AddItem( &s_controls.menu, &s_controls.banner );
//	Menu_AddItem( &s_controls.menu, &s_controls.framel );
//	Menu_AddItem( &s_controls.menu, &s_controls.framer );
/*
	Menu_AddItem( &s_controls.menu, &s_controls.multim );
	Menu_AddItem( &s_controls.menu, &s_controls.setupm );
	Menu_AddItem( &s_controls.menu, &s_controls.demom );
	Menu_AddItem( &s_controls.menu, &s_controls.modsm );
	Menu_AddItem( &s_controls.menu, &s_controls.exitm );
*/
	Menu_AddItem( &s_controls.menu, &s_controls.rq3_setupicon );
	Menu_AddItem( &s_controls.menu, &s_controls.rq3_setuptitle );
	Menu_AddItem( &s_controls.menu, &s_controls.rq3_statustext);

	Menu_AddItem( &s_controls.menu, &s_controls.player );
	//Menu_AddItem( &s_controls.menu, &s_controls.name );

	Menu_AddItem( &s_controls.menu, &s_controls.looking );
	Menu_AddItem( &s_controls.menu, &s_controls.movement );
	Menu_AddItem( &s_controls.menu, &s_controls.weapons );
	Menu_AddItem( &s_controls.menu, &s_controls.misc );
	//Blaze: Reaction Addition
	Menu_AddItem( &s_controls.menu, &s_controls.reaction );

	Menu_AddItem( &s_controls.menu, &s_controls.sensitivity );
	Menu_AddItem( &s_controls.menu, &s_controls.smoothmouse );
	Menu_AddItem( &s_controls.menu, &s_controls.invertmouse );
	Menu_AddItem( &s_controls.menu, &s_controls.lookup );
	Menu_AddItem( &s_controls.menu, &s_controls.lookdown );
	Menu_AddItem( &s_controls.menu, &s_controls.mouselook );
	Menu_AddItem( &s_controls.menu, &s_controls.freelook );
	Menu_AddItem( &s_controls.menu, &s_controls.centerview );
	Menu_AddItem( &s_controls.menu, &s_controls.zoomview );
	Menu_AddItem( &s_controls.menu, &s_controls.joyenable );
	Menu_AddItem( &s_controls.menu, &s_controls.joythreshold );

	Menu_AddItem( &s_controls.menu, &s_controls.alwaysrun );
	Menu_AddItem( &s_controls.menu, &s_controls.run );
	Menu_AddItem( &s_controls.menu, &s_controls.walkforward );
	Menu_AddItem( &s_controls.menu, &s_controls.backpedal );
	Menu_AddItem( &s_controls.menu, &s_controls.stepleft );
	Menu_AddItem( &s_controls.menu, &s_controls.stepright );
	Menu_AddItem( &s_controls.menu, &s_controls.moveup );
	Menu_AddItem( &s_controls.menu, &s_controls.movedown );
	Menu_AddItem( &s_controls.menu, &s_controls.turnleft );
	Menu_AddItem( &s_controls.menu, &s_controls.turnright );
	Menu_AddItem( &s_controls.menu, &s_controls.sidestep );

	Menu_AddItem( &s_controls.menu, &s_controls.attack );
	Menu_AddItem( &s_controls.menu, &s_controls.nextweapon );
	Menu_AddItem( &s_controls.menu, &s_controls.prevweapon );
	Menu_AddItem( &s_controls.menu, &s_controls.autoswitch );
//	Menu_AddItem( &s_controls.menu, &s_controls.chainsaw );
//	Menu_AddItem( &s_controls.menu, &s_controls.machinegun );
//Blaze: Reaction weapon additions Pistol replaces machinegun

	Menu_AddItem( &s_controls.menu, &s_controls.mk23);
	Menu_AddItem( &s_controls.menu, &s_controls.m3);
	Menu_AddItem( &s_controls.menu, &s_controls.mp5 );
	Menu_AddItem( &s_controls.menu, &s_controls.handcannon );
	Menu_AddItem( &s_controls.menu, &s_controls.ssg3000 );
	Menu_AddItem( &s_controls.menu, &s_controls.m4 );
	Menu_AddItem( &s_controls.menu, &s_controls.akimbos );
	Menu_AddItem( &s_controls.menu, &s_controls.knife );
	Menu_AddItem( &s_controls.menu, &s_controls.grenade );

	Menu_AddItem( &s_controls.menu, &s_controls.showscores );
	Menu_AddItem( &s_controls.menu, &s_controls.useitem );
	Menu_AddItem( &s_controls.menu, &s_controls.gesture );
	Menu_AddItem( &s_controls.menu, &s_controls.chat );
	Menu_AddItem( &s_controls.menu, &s_controls.chat2 );
	Menu_AddItem( &s_controls.menu, &s_controls.chat3 );
	Menu_AddItem( &s_controls.menu, &s_controls.chat4 );

	//Blaze: Reaction binds
	Menu_AddItem( &s_controls.menu, &s_controls.bandage );
	Menu_AddItem( &s_controls.menu, &s_controls.reload );
	Menu_AddItem( &s_controls.menu, &s_controls.weapon );
	Menu_AddItem( &s_controls.menu, &s_controls.opendoor );
	Menu_AddItem( &s_controls.menu, &s_controls.dropweap );
	Menu_AddItem( &s_controls.menu, &s_controls.dropitem );
	Menu_AddItem( &s_controls.menu, &s_controls.irvision );

	Menu_AddItem( &s_controls.menu, &s_controls.back );

	//trap_Cvar_VariableStringBuffer( "name", s_controls.name.string, 16 );
	//Q_CleanStr( s_controls.name.string );

	// initialize the configurable cvars
	Controls_InitCvars();

	// initialize the current config
	Controls_GetConfig();

	// intialize the model
	Controls_InitModel();

	// intialize the weapons
	Controls_InitWeapons ();

	// initial default section
	s_controls.section = C_LOOKING;

	// update the ui
	Controls_Update();
}


/*
=================
Controls_Cache
=================
*/
void Controls_Cache( void ) {
	trap_R_RegisterShaderNoMip( ART_BACK0 );
	trap_R_RegisterShaderNoMip( ART_BACK1 );
	trap_R_RegisterShaderNoMip( RQ3_SETUP_ICON );
	trap_R_RegisterShaderNoMip( RQ3_SETUP_TITLE );
	trap_R_RegisterShaderNoMip( RQ3_LOOKING_BUTTON );
	trap_R_RegisterShaderNoMip( RQ3_MOVEMENT_BUTTON );
	trap_R_RegisterShaderNoMip( RQ3_WEAPONS_BUTTON );
	trap_R_RegisterShaderNoMip( RQ3_MISC_BUTTON );
	trap_R_RegisterShaderNoMip( RQ3_REACTION_BUTTON );
	trap_R_RegisterShaderNoMip( RQ3_FOCUS_BUTTON );
	//trap_R_RegisterShaderNoMip( ART_FRAMEL );
	//trap_R_RegisterShaderNoMip( ART_FRAMER );
}


/*
=================
UI_ControlsMenu
=================
*/
void UI_ControlsMenu( void ) {
	Controls_MenuInit();
	UI_PushMenu( &s_controls.menu );
}
