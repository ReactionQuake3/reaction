// Copyright (C) 1999-2000 Id Software, Inc.
//
/*
=======================================================================

MAIN MENU

=======================================================================
*/


#include "ui_local.h"

#define ID_SINGLEPLAYER			10
#define ID_MULTIPLAYER			11
#define ID_SETUP				12
#define ID_DEMOS				13
#define ID_CINEMATICS			14
#define ID_TEAMARENA			15
#define ID_MODS					16
#define ID_EXIT					17

#define MAIN_BANNER_MODEL				"models/mapobjects/banner/banner5.md3"
#define MAIN_MENU_VERTICAL_SPACING		34

//Elder: Define button images
#define RQ3_START_BUTTON				"menu/art/rq3-menu-start.tga"
#define RQ3_SETUP_BUTTON				"menu/art/rq3-menu-setup.tga"
#define RQ3_DEMOS_BUTTON				"menu/art/rq3-menu-demos.tga"
#define RQ3_MODS_BUTTON					"menu/art/rq3-menu-mods.tga"
#define RQ3_EXIT_BUTTON					"menu/art/rq3-menu-exit.tga"
#define RQ3_FOCUS_BUTTON				"menu/art/rq3-menu-focus.tga"

typedef struct {
	menuframework_s	menu;
//Elder: Systematically replacing text with button pics
//Blaze: No single player, cinematics, team arena, and banner model
//	menutext_s		singleplayer;
//	menutext_s		multiplayer;
//	menutext_s		setup;
//	menutext_s		demos;
//	menutext_s		cinematics;
//	menutext_s		teamArena;
//	menutext_s		mods;
//	menutext_s		exit;
//	qhandle_t		bannerModel;

//Elder: RQ3 Button Images and status text
	menubitmap_s	rq3_startbutton;
	menubitmap_s	rq3_setupbutton;
	menubitmap_s	rq3_demosbutton;
	menubitmap_s	rq3_modsbutton;
	menubitmap_s	rq3_exitbutton;

	menutext_s		rq3_statustext;

//Niceass: Cvar Kick text
	menutext_s		rq3_kicktext;
} mainmenu_t;


static mainmenu_t s_main;

/*
=================
MainMenu_ExitAction
=================
*/
static void MainMenu_ExitAction( qboolean result ) {
	if( !result ) {
		return;
	}
	UI_PopMenu();
	UI_CreditMenu();
}


/*
=================
CheckKickCvar - Added by NiceAss to help the newbies out =)
================
*/
void UI_CheckKickCvar( void ) {
	static char Reason[256], Cvar[64];

	strcpy(Reason, "WARNING: You have been kicked because ");
	trap_Cvar_VariableStringBuffer("RQ3_CvarKickReason", Cvar, sizeof(Cvar));

	if (strlen(Cvar)) {
		Com_Printf("AHAH!: [%s]\n", Cvar);
		trap_Cvar_Set("RQ3_CvarKickReason", "");
		strcat(Reason, Cvar);
		strcat(Reason, " is out of range.");
		s_main.rq3_kicktext.string = Reason;
	}
	else {
		s_main.rq3_kicktext.string = "";
	}
}


/*
=================
Main_MenuEvent
=================
*/
void Main_MenuEvent (void* ptr, int event) {
	//Elder: Added status messages on event focus
	if ( event == QM_LOSTFOCUS ) {
		s_main.rq3_statustext.string = "";
	}
	else if( event == QM_GOTFOCUS ) {
		//get menu item id
		switch( ((menucommon_s*)ptr)->id ) {

		case ID_MULTIPLAYER:
			s_main.rq3_statustext.string = "Play Reaction Quake 3";
			break;

		case ID_SETUP:
			s_main.rq3_statustext.string = "Configure Reaction Quake 3";
			break;

		case ID_DEMOS:
			s_main.rq3_statustext.string = "Playback in-game demos";
			break;

		case ID_MODS:
			s_main.rq3_statustext.string = "Change game modification";
			break;

		case ID_EXIT:
			s_main.rq3_statustext.string = "Exit Reaction Quake 3";
			break;

		default:
			s_main.rq3_statustext.string = "";
			break;
		}
	}

	else if( event == QM_ACTIVATED ) {
		s_main.rq3_statustext.string = "";
		switch( ((menucommon_s*)ptr)->id ) {

//Blaze: This case nolonger exists
//	case ID_SINGLEPLAYER:
//		UI_SPLevelMenu();
//		break;

		case ID_MULTIPLAYER:
			UI_ArenaServersMenu();
			break;

		case ID_SETUP:
			UI_SetupMenu();
			break;

		case ID_DEMOS:
			UI_DemosMenu();
			break;

//Blaze: This case nolonger exists
//	case ID_CINEMATICS:
//		UI_CinematicsMenu();
//		break;

		case ID_MODS:
			UI_ModsMenu();
			break;

//Blaze: This case nolonger exists
//	case ID_TEAMARENA:
//		trap_Cvar_Set( "fs_game", "missionpack");
//		trap_Cmd_ExecuteText( EXEC_APPEND, "vid_restart;" );
//		break;

		case ID_EXIT:
			UI_ConfirmMenu( "EXIT REACTION?", NULL, MainMenu_ExitAction );
			break;

		}
	}
	else {
		return;
	}
}


/*
===============
MainMenu_Cache
===============
*/
void MainMenu_Cache( void ) {
	//Blaze: removed the banner
	//s_main.bannerModel = trap_R_RegisterModel( MAIN_BANNER_MODEL );

	//Elder: cache button images
	trap_R_RegisterShaderNoMip( RQ3_START_BUTTON );
	trap_R_RegisterShaderNoMip( RQ3_SETUP_BUTTON );
	trap_R_RegisterShaderNoMip( RQ3_DEMOS_BUTTON );
	trap_R_RegisterShaderNoMip( RQ3_MODS_BUTTON );
	trap_R_RegisterShaderNoMip( RQ3_EXIT_BUTTON );
	trap_R_RegisterShaderNoMip( RQ3_FOCUS_BUTTON );

}


/*
===============
Main_MenuDraw
===============
*/
static void Main_MenuDraw( void ) {
	refdef_t		refdef;
	//Blaze: this is was used for the q3 banner and is not needed anymore
	//	refEntity_t		ent;
	vec3_t			origin;
	//Blaze: this is was used for the q3 banner and is not needed anymore
	//vec3_t			angles;
	float			adjust;
	float			x, y, w, h;
	vec4_t			color = {0.5, 0, 0, 1};

	// setup the refdef

	memset( &refdef, 0, sizeof( refdef ) );

	refdef.rdflags = RDF_NOWORLDMODEL;

	AxisClear( refdef.viewaxis );

	x = 0;
	y = 0;
	w = 640;
	h = 120;
	UI_AdjustFrom640( &x, &y, &w, &h );
	refdef.x = x;
	refdef.y = y;
	refdef.width = w;
	refdef.height = h;

	adjust = 0; // JDC: Kenneth asked me to stop this 1.0 * sin( (float)uis.realtime / 1000 );
	refdef.fov_x = 60 + adjust;
	refdef.fov_y = 19.6875 + adjust;

	refdef.time = uis.realtime;

	origin[0] = 300;
	origin[1] = 0;
	origin[2] = -32;

	trap_R_ClearScene();

	// add the model
//Blaze: No more model
/*
	memset( &ent, 0, sizeof(ent) );

	adjust = 5.0 * sin( (float)uis.realtime / 5000 );
	VectorSet( angles, 0, 180 + adjust, 0 );
	AnglesToAxis( angles, ent.axis );
	ent.hModel = s_main.bannerModel;
	VectorCopy( origin, ent.origin );
	VectorCopy( origin, ent.lightingOrigin );
	ent.renderfx = RF_LIGHTING_ORIGIN | RF_NOSHADOW;
	VectorCopy( ent.origin, ent.oldorigin );

	trap_R_AddRefEntityToScene( &ent );

	trap_R_RenderScene( &refdef );
*/

	//Elder: "Letterbox" mask
	UI_FillRect( 0, 0, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 54, SCREEN_WIDTH, 2, color_red);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 2, color_red);

	// standard menu drawing
	Menu_Draw( &s_main.menu );

	if (uis.demoversion) {
		UI_DrawProportionalString( 320, 372, "DEMO      FOR MATURE AUDIENCES      DEMO", UI_CENTER|UI_SMALLFONT, color );
		UI_DrawString( 320, 400, "Quake III Arena(c) 1999-2000, Id Software, Inc.  All Rights Reserved", UI_CENTER|UI_SMALLFONT, color );
	} else {
		//Elder: Nudged slightly lower to accomodate status text
		UI_DrawString( 320, 464, "Quake III Arena(c) 1999-2000, Id Software, Inc.  All Rights Reserved", UI_CENTER|UI_SMALLFONT, color );
	}
}


/*
===============
UI_TeamArenaExists
===============
*/
static qboolean UI_TeamArenaExists( void ) {
	int		numdirs;
	char	dirlist[2048];
	char	*dirptr;
	char  *descptr;
	int		i;
	int		dirlen;

	numdirs = trap_FS_GetFileList( "$modlist", "", dirlist, sizeof(dirlist) );
	dirptr  = dirlist;
	for( i = 0; i < numdirs; i++ ) {
		dirlen = strlen( dirptr ) + 1;
    descptr = dirptr + dirlen;
		if (Q_stricmp(dirptr, "missionpack") == 0) {
			return qtrue;
		}
    dirptr += dirlen + strlen(descptr) + 1;
	}
	return qfalse;
}
qboolean trap_VerifyCDKey( const char *key, const char *chksum);


/*
===============
UI_MainMenu

The main menu only comes up when not in a game,
so make sure that the attract loop server is down
and that local cinematics are killed
===============
*/
void UI_MainMenu( void ) {
	//Elder: "auto" x-alignment based on number of buttons
	int		buttonCount = 0;
	int		y;
	qboolean teamArena = qfalse;
	int		style = UI_CENTER | UI_DROPSHADOW;
	// NiceAss: CvarKickReason stuff
	char Reason[256], Cvar[64];

	trap_Cvar_Set( "sv_killserver", "1" );

	if( !uis.demoversion && !ui_cdkeychecked.integer ) {
		char	key[17];

		trap_GetCDKey( key, sizeof(key) );
		if( trap_VerifyCDKey( key, NULL ) == qfalse ) {
			UI_CDKeyMenu();
			return;
		}
	}

	memset( &s_main, 0 ,sizeof(mainmenu_t) );

	// NiceAss: Check to see if you were kicked.
	UI_CheckKickCvar();

	MainMenu_Cache();

	s_main.menu.draw = Main_MenuDraw;
	s_main.menu.fullscreen = qtrue;
	s_main.menu.wrapAround = qtrue;
	s_main.menu.showlogo = qtrue;

	//Blaze: Reaction menu
	y = 12;

	//Elder: RQ3 Start Button
	s_main.rq3_startbutton.generic.type			= MTYPE_BITMAP;
	s_main.rq3_startbutton.generic.name			= RQ3_START_BUTTON;
	s_main.rq3_startbutton.generic.flags		= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	s_main.rq3_startbutton.generic.id			= ID_MULTIPLAYER;
	s_main.rq3_startbutton.generic.callback		= Main_MenuEvent;
	s_main.rq3_startbutton.generic.x			= (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	s_main.rq3_startbutton.generic.y			= y;
	s_main.rq3_startbutton.width				= RQ3_BUTTON_WIDTH;
	s_main.rq3_startbutton.height				= RQ3_BUTTON_HEIGHT;
	s_main.rq3_startbutton.focuspic				= RQ3_FOCUS_BUTTON;

	//Elder: RQ3 Setup Button
	s_main.rq3_setupbutton.generic.type			= MTYPE_BITMAP;
	s_main.rq3_setupbutton.generic.name			= RQ3_SETUP_BUTTON;
	s_main.rq3_setupbutton.generic.flags		= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	s_main.rq3_setupbutton.generic.id			= ID_SETUP;
	s_main.rq3_setupbutton.generic.callback		= Main_MenuEvent;
	s_main.rq3_setupbutton.generic.x			= (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	s_main.rq3_setupbutton.generic.y			= y;
	s_main.rq3_setupbutton.width				= RQ3_BUTTON_WIDTH;
	s_main.rq3_setupbutton.height				= RQ3_BUTTON_HEIGHT;
	s_main.rq3_setupbutton.focuspic				= RQ3_FOCUS_BUTTON;

	//Elder: RQ3 Demos Button
	s_main.rq3_demosbutton.generic.type			= MTYPE_BITMAP;
	s_main.rq3_demosbutton.generic.name			= RQ3_DEMOS_BUTTON;
	s_main.rq3_demosbutton.generic.flags		= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	s_main.rq3_demosbutton.generic.id			= ID_DEMOS;
	s_main.rq3_demosbutton.generic.callback		= Main_MenuEvent;
	s_main.rq3_demosbutton.generic.x			= (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	s_main.rq3_demosbutton.generic.y			= y;
	s_main.rq3_demosbutton.width				= RQ3_BUTTON_WIDTH;
	s_main.rq3_demosbutton.height				= RQ3_BUTTON_HEIGHT;
	s_main.rq3_demosbutton.focuspic				= RQ3_FOCUS_BUTTON;

	//Elder: RQ3 Mods Button
	s_main.rq3_modsbutton.generic.type			= MTYPE_BITMAP;
	s_main.rq3_modsbutton.generic.name			= RQ3_MODS_BUTTON;
	s_main.rq3_modsbutton.generic.flags			= QMF_RIGHT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	s_main.rq3_modsbutton.generic.id			= ID_MODS;
	s_main.rq3_modsbutton.generic.callback		= Main_MenuEvent;
	s_main.rq3_modsbutton.generic.x				= 640 - (RQ3_BUTTON_WIDTH + RQ3_BUTTON_PADDING);
	s_main.rq3_modsbutton.generic.y				= y;
	s_main.rq3_modsbutton.width					= RQ3_BUTTON_WIDTH;
	s_main.rq3_modsbutton.height				= RQ3_BUTTON_HEIGHT;
	s_main.rq3_modsbutton.focuspic				= RQ3_FOCUS_BUTTON;

	//Elder: RQ3 Exit Button
	s_main.rq3_exitbutton.generic.type			= MTYPE_BITMAP;
	s_main.rq3_exitbutton.generic.name			= RQ3_EXIT_BUTTON;
	s_main.rq3_exitbutton.generic.flags			= QMF_RIGHT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	s_main.rq3_exitbutton.generic.id			= ID_EXIT;
	s_main.rq3_exitbutton.generic.callback		= Main_MenuEvent;
	s_main.rq3_exitbutton.generic.x				= 640;
	s_main.rq3_exitbutton.generic.y				= y;
	s_main.rq3_exitbutton.width					= RQ3_BUTTON_WIDTH;
	s_main.rq3_exitbutton.height				= RQ3_BUTTON_HEIGHT;
	s_main.rq3_exitbutton.focuspic				= RQ3_FOCUS_BUTTON;

	//Elder: RQ3 Status Text
	s_main.rq3_statustext.generic.type 			= MTYPE_TEXT;
	s_main.rq3_statustext.generic.flags			= QMF_CENTER_JUSTIFY;
	s_main.rq3_statustext.generic.x 			= RQ3_STATUSBAR_X;
	s_main.rq3_statustext.generic.y 			= RQ3_STATUSBAR_Y;
	s_main.rq3_statustext.string 				= "";
	s_main.rq3_statustext.style 				= UI_CENTER|UI_SMALLFONT;
	s_main.rq3_statustext.color 				= color_orange;

	//NiceAss: For RQ3_CvarKickReason
	s_main.rq3_kicktext.generic.type 			= MTYPE_TEXT;
	s_main.rq3_kicktext.generic.flags			= QMF_CENTER_JUSTIFY;
	s_main.rq3_kicktext.generic.x 				= RQ3_STATUSBAR_X;
	s_main.rq3_kicktext.generic.y 				= RQ3_STATUSBAR_Y + 17;
	s_main.rq3_kicktext.style 					= UI_CENTER|UI_SMALLFONT;
	s_main.rq3_kicktext.color 					= color_yellow;

	/*Elder: Replaced by RQ3 buttons above
	//Blaze: This menu nolonger exists
	s_main.singleplayer.generic.type		= MTYPE_PTEXT;
	s_main.singleplayer.generic.flags		= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS;
	s_main.singleplayer.generic.x			= 320;
	s_main.singleplayer.generic.y			= y+150;
	s_main.singleplayer.generic.id			= ID_SINGLEPLAYER;
	s_main.singleplayer.generic.callback	= Main_MenuEvent;
	s_main.singleplayer.string				= "SINGLE PLAYER";
	s_main.singleplayer.color				= color_red;
	s_main.singleplayer.style				= style;

	//Blaze: Reaction menu
	//y += MAIN_MENU_VERTICAL_SPACING;
	y=3;
	s_main.multiplayer.generic.type			= MTYPE_PTEXT;
	s_main.multiplayer.generic.flags		= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS;
	s_main.multiplayer.generic.x			= 120;//Blaze: Menu X loc
	s_main.multiplayer.generic.y			= y;
	s_main.multiplayer.generic.id			= ID_MULTIPLAYER;
	s_main.multiplayer.generic.callback		= Main_MenuEvent;
	s_main.multiplayer.string				= "MULTIPLAYER";
	s_main.multiplayer.color				= color_red;
	s_main.multiplayer.style				= style;

	//Blaze: Reaction Menu
	//y += MAIN_MENU_VERTICAL_SPACING;
	s_main.setup.generic.type				= MTYPE_PTEXT;
	s_main.setup.generic.flags				= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS;
	s_main.setup.generic.x					= 280;//Blaze: Menu x loc
	s_main.setup.generic.y					= y;
	s_main.setup.generic.id					= ID_SETUP;
	s_main.setup.generic.callback			= Main_MenuEvent;
	s_main.setup.string						= "SETUP";
	s_main.setup.color						= color_red;
	s_main.setup.style						= style;

	//y += MAIN_MENU_VERTICAL_SPACING;
	s_main.demos.generic.type				= MTYPE_PTEXT;
	s_main.demos.generic.flags				= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS;
	s_main.demos.generic.x					= 390;//Blaze: Menu x loc
	s_main.demos.generic.y					= y;
	s_main.demos.generic.id					= ID_DEMOS;
	s_main.demos.generic.callback			= Main_MenuEvent;
	s_main.demos.string						= "DEMOS";
	s_main.demos.color						= color_red;
	s_main.demos.style						= style;

	//y += MAIN_MENU_VERTICAL_SPACING;
	//Blaze: This menu nolonger exists
	s_main.cinematics.generic.type			= MTYPE_PTEXT;
	s_main.cinematics.generic.flags			= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS;
	s_main.cinematics.generic.x				= 350;//Blaze: Menu x loc
	s_main.cinematics.generic.y				= y+150;
	s_main.cinematics.generic.id			= ID_CINEMATICS;
	s_main.cinematics.generic.callback		= Main_MenuEvent;
	s_main.cinematics.string				= "CINEMATICS";
	s_main.cinematics.color					= color_red;
	s_main.cinematics.style					= style;


	//Blaze: This menu nolonger exists
	if (UI_TeamArenaExists()) {
		teamArena = qtrue;
		y += MAIN_MENU_VERTICAL_SPACING;
		s_main.teamArena.generic.type			= MTYPE_PTEXT;
		s_main.teamArena.generic.flags			= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS;
		s_main.teamArena.generic.x				= 320;
		s_main.teamArena.generic.y				= y;
		s_main.teamArena.generic.id				= ID_TEAMARENA;
		s_main.teamArena.generic.callback		= Main_MenuEvent;
		s_main.teamArena.string					= "TEAM ARENA";
		s_main.teamArena.color					= color_red;
		s_main.teamArena.style					= style;
	}

	//y += MAIN_MENU_VERTICAL_SPACING;
	s_main.mods.generic.type			= MTYPE_PTEXT;
	s_main.mods.generic.flags			= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS;
	s_main.mods.generic.x				= 500;//Blaze: Menu x loc
	s_main.mods.generic.y				= y;
	s_main.mods.generic.id				= ID_MODS;
	s_main.mods.generic.callback		= Main_MenuEvent;
	s_main.mods.string					= "MODS";
	s_main.mods.color					= color_red;
	s_main.mods.style					= style;

	//y += MAIN_MENU_VERTICAL_SPACING;
	s_main.exit.generic.type				= MTYPE_PTEXT;
	s_main.exit.generic.flags				= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS;
	s_main.exit.generic.x					= 590;//Blaze: Menu x loc
	s_main.exit.generic.y					= y;
	s_main.exit.generic.id					= ID_EXIT;
	s_main.exit.generic.callback			= Main_MenuEvent;
	s_main.exit.string						= "EXIT";
	s_main.exit.color						= color_red;
	s_main.exit.style						= style;

	*/

	//Elder: Add RQ3 Stuff
	Menu_AddItem( &s_main.menu, ( void * )&s_main.rq3_startbutton );
	Menu_AddItem( &s_main.menu, ( void * )&s_main.rq3_setupbutton );
	Menu_AddItem( &s_main.menu, ( void * )&s_main.rq3_demosbutton );
	Menu_AddItem( &s_main.menu, ( void * )&s_main.rq3_modsbutton );
	Menu_AddItem( &s_main.menu, ( void * )&s_main.rq3_exitbutton );

	Menu_AddItem( &s_main.menu, 	&s_main.rq3_statustext );
	Menu_AddItem( &s_main.menu,		&s_main.rq3_kicktext );

	// Start music
	trap_Cmd_ExecuteText( EXEC_APPEND, "music music/rq3_title_intro music/rq3_title_loop\n" );

	//Elder: Replaced by RQ3 Buttons above
	//
	//Blaze: This menu nolonger exists
	//Menu_AddItem( &s_main.menu,	&s_main.singleplayer );
	//Menu_AddItem( &s_main.menu,	&s_main.multiplayer );
	//Menu_AddItem( &s_main.menu,	&s_main.setup );
	//Menu_AddItem( &s_main.menu,	&s_main.demos );
	//Blaze: This menu nolonger exists
	//Menu_AddItem( &s_main.menu,	&s_main.cinematics );
	//Blaze: This menu nolonger exists
	//if (teamArena) {
	//	Menu_AddItem( &s_main.menu,	&s_main.teamArena );
	//}
	//Menu_AddItem( &s_main.menu,	&s_main.mods );
	//Menu_AddItem( &s_main.menu,	&s_main.exit );

	trap_Key_SetCatcher( KEYCATCH_UI );
	uis.menusp = 0;
	UI_PushMenu ( &s_main.menu );
}
