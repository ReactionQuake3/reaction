//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.5  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.//
/*
=======================================================================

SETUP MENU

=======================================================================
*/


#include "ui_local.h"


#define SETUP_MENU_VERTICAL_SPACING		20//Changed to 20

#define ART_BACK0		"menu/art/rq3-menu-back.tga"
#define ART_BACK1		"menu/art/rq3-menu-back-focus.tga"	
//Elder: Don't need these either
//#define ART_FRAMEL		"menu/art/frame2_l"
//#define ART_FRAMER		"menu/art/frame1_r"

#define ID_CUSTOMIZEPLAYER		10
#define ID_CUSTOMIZECONTROLS	11
#define ID_SYSTEMCONFIG			12
#define ID_GAME					13
#define ID_CDKEY				14
#define ID_LOAD					15
#define ID_SAVE					16
#define ID_DEFAULTS				17
#define ID_BACK					18

//Elder: RQ3 Setup assets
#define RQ3_SETUP_ICON		"menu/art/rq3-menu-setup.tga"
#define RQ3_SETUP_TITLE		"menu/art/rq3-title-setup.jpg"
#define RQ3_SETUP_DEFAULTS	"menu/art/rq3-setup-defaults.jpg"
#define RQ3_SETUP_PLAYER	"menu/art/rq3-setup-player.jpg"
#define RQ3_SETUP_CONTROLS	"menu/art/rq3-setup-controls.jpg"
#define RQ3_SETUP_CDKEY		"menu/art/rq3-setup-cdkey.jpg"
#define RQ3_SETUP_SYSTEM	"menu/art/rq3-setup-system.jpg"
#define RQ3_SETUP_OPTIONS	"menu/art/rq3-setup-options.jpg"
#define RQ3_FOCUS_BUTTON	"menu/art/rq3-menu-focus.tga"

typedef struct {
	menuframework_s	menu;

//Blaze: Dont need this
//	menutext_s		banner;
//	menubitmap_s	framel;
//	menubitmap_s	framer;
//Elder: Don't need these anymore either
//	menutext_s		multim;
//	menutext_s		setupm;
//	menutext_s		demom;
//	menutext_s		modsm;
//	menutext_s		exitm;

//	menutext_s		setupplayer;
//	menutext_s		setupcontrols;
//	menutext_s		setupsystem;
//	menutext_s		game;
//	menutext_s		cdkey;
//	menutext_s		load;
//	menutext_s		save;
//	menutext_s		defaults;
	menubitmap_s	back;
	
	//Elder: RQ3 Menu buttons
	menubitmap_s	rq3_setupicon;
	menubitmap_s	rq3_setuptitle;
	
	menubitmap_s	rq3_setupcdkey;
	menubitmap_s	rq3_setupdefaults;
	menubitmap_s	rq3_setupcontrols;
	menubitmap_s	rq3_setupplayer;
	menubitmap_s	rq3_setupoptions;
	menubitmap_s	rq3_setupsystem;
	
	menutext_s		rq3_statustext;
	
} setupMenuInfo_t;

static setupMenuInfo_t	setupMenuInfo;


/*
=================
Setup_ResetDefaults_Action
=================
*/
static void Setup_ResetDefaults_Action( qboolean result ) {
	if( !result ) {
		return;
	}
	trap_Cmd_ExecuteText( EXEC_APPEND, "exec default.cfg\n");
	trap_Cmd_ExecuteText( EXEC_APPEND, "cvar_restart\n");
	trap_Cmd_ExecuteText( EXEC_APPEND, "vid_restart\n" );
}


/*
=================
Setup_ResetDefaults_Draw
=================
*/
static void Setup_ResetDefaults_Draw( void ) {
	UI_DrawProportionalString( SCREEN_WIDTH/2, 356 + PROP_HEIGHT * 0, "WARNING: This will reset *ALL*", UI_CENTER|UI_SMALLFONT, color_yellow );
	UI_DrawProportionalString( SCREEN_WIDTH/2, 356 + PROP_HEIGHT * 1, "options to their default values.", UI_CENTER|UI_SMALLFONT, color_yellow );
}

/*
===============
Added by Elder
Setup_MenuDraw
===============
*/
static void Setup_MenuDraw( void ) {
	//Elder: "Dim" and "Letterbox" mask
	UI_FillRect( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color_deepdim );
	UI_FillRect( 0, 0, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 54, SCREEN_WIDTH, 2, color_red);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 2, color_red);
	
	// standard menu drawing
	Menu_Draw( &setupMenuInfo.menu );
}

/*
===============
UI_SetupMenu_Event
===============
*/
static void UI_SetupMenu_Event( void *ptr, int event ) {
	//Elder: Added status messages on event focus
	if ( event == QM_LOSTFOCUS ) {
		setupMenuInfo.rq3_statustext.string = "";
	}
	else if( event == QM_GOTFOCUS ) {
		//get menu item id
		switch( ((menucommon_s*)ptr)->id ) {
		
		case ID_CUSTOMIZEPLAYER:
			setupMenuInfo.rq3_statustext.string = "Change player settings";
			break;
			
		case ID_CUSTOMIZECONTROLS:
			setupMenuInfo.rq3_statustext.string = "Change Reaction controls";
			break;	
		
		case ID_SYSTEMCONFIG:
			setupMenuInfo.rq3_statustext.string = "Change system settings";
			break;
		
		case ID_GAME:
			setupMenuInfo.rq3_statustext.string = "Change game options";
			break;
		
		case ID_CDKEY:
			setupMenuInfo.rq3_statustext.string = "Set the Quake 3 CD-key";
			break;
		case ID_DEFAULTS:
			setupMenuInfo.rq3_statustext.string = "Reset all settings back to default";
			break;

		case ID_BACK:
			setupMenuInfo.rq3_statustext.string = "Return to main menu";
			break;
			
		default:
			setupMenuInfo.rq3_statustext.string = "";
			break;
		}
	}	
	else if( event == QM_ACTIVATED ) {
		setupMenuInfo.rq3_statustext.string = "";
		switch( ((menucommon_s*)ptr)->id ) {
		case ID_CUSTOMIZEPLAYER:
			UI_PlayerSettingsMenu();
			break;

		case ID_CUSTOMIZECONTROLS:
			UI_ControlsMenu();
			break;

		case ID_SYSTEMCONFIG:
			UI_GraphicsOptionsMenu();
			break;

		case ID_GAME:
			UI_PreferencesMenu();
			break;

		case ID_CDKEY:
			UI_CDKeyMenu();
			break;

//	case ID_LOAD:
//		UI_LoadConfigMenu();
//		break;

//	case ID_SAVE:
//		UI_SaveConfigMenu();
//		break;

		case ID_DEFAULTS:
			UI_ConfirmMenu( "SET TO DEFAULTS?", Setup_ResetDefaults_Draw, Setup_ResetDefaults_Action );
			break;

		case ID_BACK:
			UI_PopMenu();
			break;
		}
	}
}


/*
===============
UI_SetupMenu_Init
===============
*/
static void UI_SetupMenu_Init( void ) {
	int		y, buttonCount;
	y = 12;
	buttonCount = 0;

	UI_SetupMenu_Cache();

	memset( &setupMenuInfo, 0, sizeof(setupMenuInfo) );
	//Elder: added draw function
	setupMenuInfo.menu.draw = Setup_MenuDraw;
	setupMenuInfo.menu.wrapAround = qtrue;
	setupMenuInfo.menu.fullscreen = qtrue;
	setupMenuInfo.menu.showlogo = qtrue;//Blaze: Show Background logo

//Blaze: Dont need this
/*	setupMenuInfo.banner.generic.type				= MTYPE_BTEXT;
	setupMenuInfo.banner.generic.x					= 320;
	setupMenuInfo.banner.generic.y					= 16;
	setupMenuInfo.banner.string						= "SETUP";
	setupMenuInfo.banner.color						= color_white;
	setupMenuInfo.banner.style						= UI_CENTER;

	setupMenuInfo.framel.generic.type				= MTYPE_BITMAP;
	setupMenuInfo.framel.generic.name				= ART_FRAMEL;
	setupMenuInfo.framel.generic.flags				= QMF_INACTIVE;
	setupMenuInfo.framel.generic.x					= 0;  
	setupMenuInfo.framel.generic.y					= 78;
	setupMenuInfo.framel.width  					= 256;
	setupMenuInfo.framel.height  					= 329;

	setupMenuInfo.framer.generic.type				= MTYPE_BITMAP;
	setupMenuInfo.framer.generic.name				= ART_FRAMER;
	setupMenuInfo.framer.generic.flags				= QMF_INACTIVE;
	setupMenuInfo.framer.generic.x					= 376;
	setupMenuInfo.framer.generic.y					= 76;
	setupMenuInfo.framer.width  					= 256;
	setupMenuInfo.framer.height  					= 334;
*/
/*Elder: Removed
	setupMenuInfo.multim.generic.type	= MTYPE_PTEXT;
	setupMenuInfo.multim.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	setupMenuInfo.multim.generic.x		= 120;
	setupMenuInfo.multim.generic.y		= 3;
	setupMenuInfo.multim.string			= "MULTIPLAYER";
	setupMenuInfo.multim.color			= color_red;
	setupMenuInfo.multim.style			= UI_CENTER | UI_DROPSHADOW;

	setupMenuInfo.setupm.generic.type	= MTYPE_PTEXT;
	setupMenuInfo.setupm.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_INACTIVE|QMF_HIGHLIGHT;
	setupMenuInfo.setupm.generic.x		= 280;
	setupMenuInfo.setupm.generic.y		= 3;
	setupMenuInfo.setupm.string			= "SETUP";
	setupMenuInfo.setupm.color			= color_red;
	setupMenuInfo.setupm.style			= UI_CENTER | UI_DROPSHADOW;

	setupMenuInfo.demom.generic.type	= MTYPE_PTEXT;
	setupMenuInfo.demom.generic.flags	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	setupMenuInfo.demom.generic.x		= 390;
	setupMenuInfo.demom.generic.y		= 3;
	setupMenuInfo.demom.string			= "DEMOS";
	setupMenuInfo.demom.color			= color_red;
	setupMenuInfo.demom.style			= UI_CENTER | UI_DROPSHADOW;

	setupMenuInfo.modsm.generic.type	= MTYPE_PTEXT;
//Note the following line, this makes it highlight
	setupMenuInfo.modsm.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	setupMenuInfo.modsm.generic.x		= 500;
	setupMenuInfo.modsm.generic.y		= 3;
	setupMenuInfo.modsm.string			= "MODS";
	setupMenuInfo.modsm.color			= color_red;
	setupMenuInfo.modsm.style			= UI_CENTER | UI_DROPSHADOW;

	setupMenuInfo.exitm.generic.type	= MTYPE_PTEXT;
	setupMenuInfo.exitm.generic.flags  	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	setupMenuInfo.exitm.generic.x		= 590;
	setupMenuInfo.exitm.generic.y		= 3;
	setupMenuInfo.exitm.string			= "EXIT";
	setupMenuInfo.exitm.color			= color_red;
	setupMenuInfo.exitm.style			= UI_CENTER | UI_DROPSHADOW;
*/
	//y = 64;//Blaze: Changed from 134
	//x = 64;
	/* Elder Replaced by RQ3 Buttons
	setupMenuInfo.setupplayer.generic.type			= MTYPE_PTEXT;
	setupMenuInfo.setupplayer.generic.flags			= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	setupMenuInfo.setupplayer.generic.x				= x;
	setupMenuInfo.setupplayer.generic.y				= y;
	setupMenuInfo.setupplayer.generic.id			= ID_CUSTOMIZEPLAYER;
	setupMenuInfo.setupplayer.generic.callback		= UI_SetupMenu_Event; 
	setupMenuInfo.setupplayer.string				= "PLAYER";
	setupMenuInfo.setupplayer.color					= color_red;
	setupMenuInfo.setupplayer.style					= UI_SMALLFONT;

	y += SETUP_MENU_VERTICAL_SPACING;
	setupMenuInfo.setupcontrols.generic.type		= MTYPE_PTEXT;
	setupMenuInfo.setupcontrols.generic.flags		= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	setupMenuInfo.setupcontrols.generic.x			= x;
	setupMenuInfo.setupcontrols.generic.y			= y;
	setupMenuInfo.setupcontrols.generic.id			= ID_CUSTOMIZECONTROLS;
	setupMenuInfo.setupcontrols.generic.callback	= UI_SetupMenu_Event; 
	setupMenuInfo.setupcontrols.string				= "CONTROLS";
	setupMenuInfo.setupcontrols.color				= color_red;
	setupMenuInfo.setupcontrols.style				= UI_SMALLFONT;
	*/
	/*
	//y += SETUP_MENU_VERTICAL_SPACING;
	setupMenuInfo.setupsystem.generic.type			= MTYPE_PTEXT;
	setupMenuInfo.setupsystem.generic.flags			= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	setupMenuInfo.setupsystem.generic.x				= x;
	setupMenuInfo.setupsystem.generic.y				= y;
	setupMenuInfo.setupsystem.generic.id			= ID_SYSTEMCONFIG;
	setupMenuInfo.setupsystem.generic.callback		= UI_SetupMenu_Event; 
	setupMenuInfo.setupsystem.string				= "SYSTEM";
	setupMenuInfo.setupsystem.color					= color_red;
	setupMenuInfo.setupsystem.style					= UI_SMALLFONT;

	//y += SETUP_MENU_VERTICAL_SPACING;
	setupMenuInfo.game.generic.type					= MTYPE_PTEXT;
	setupMenuInfo.game.generic.flags				= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	setupMenuInfo.game.generic.x					= x;
	setupMenuInfo.game.generic.y					= y;
	setupMenuInfo.game.generic.id					= ID_GAME;
	setupMenuInfo.game.generic.callback				= UI_SetupMenu_Event; 
	setupMenuInfo.game.string						= "OPTIONS";
	setupMenuInfo.game.color						= color_red;
	setupMenuInfo.game.style						= UI_SMALLFONT;
	*/
	/*Elder: replaced by RQ3 buttons	
	y += SETUP_MENU_VERTICAL_SPACING;
	setupMenuInfo.cdkey.generic.type				= MTYPE_PTEXT;
	setupMenuInfo.cdkey.generic.flags				= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	setupMenuInfo.cdkey.generic.x					= x;
	setupMenuInfo.cdkey.generic.y					= y;
	setupMenuInfo.cdkey.generic.id					= ID_CDKEY;
	setupMenuInfo.cdkey.generic.callback			= UI_SetupMenu_Event; 
	setupMenuInfo.cdkey.string						= "CD Key";
	setupMenuInfo.cdkey.color						= color_red;
	setupMenuInfo.cdkey.style						= UI_SMALLFONT;

	if( !trap_Cvar_VariableValue( "cl_paused" ) ) {
#if 0
		y += SETUP_MENU_VERTICAL_SPACING;
		setupMenuInfo.load.generic.type					= MTYPE_PTEXT;
		setupMenuInfo.load.generic.flags				= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
		setupMenuInfo.load.generic.x					= x;
		setupMenuInfo.load.generic.y					= y;
		setupMenuInfo.load.generic.id					= ID_LOAD;
		setupMenuInfo.load.generic.callback				= UI_SetupMenu_Event; 
		setupMenuInfo.load.string						= "LOAD";
		setupMenuInfo.load.color						= color_red;
		setupMenuInfo.load.style						= UI_SMALLFONT;

		y += SETUP_MENU_VERTICAL_SPACING;
		setupMenuInfo.save.generic.type					= MTYPE_PTEXT;
		setupMenuInfo.save.generic.flags				= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
		setupMenuInfo.save.generic.x					= x;
		setupMenuInfo.save.generic.y					= y;
		setupMenuInfo.save.generic.id					= ID_SAVE;
		setupMenuInfo.save.generic.callback				= UI_SetupMenu_Event; 
		setupMenuInfo.save.string						= "SAVE";
		setupMenuInfo.save.color						= color_red;
		setupMenuInfo.save.style						= UI_SMALLFONT;
#endif

		y += SETUP_MENU_VERTICAL_SPACING;
		setupMenuInfo.defaults.generic.type				= MTYPE_PTEXT;
		setupMenuInfo.defaults.generic.flags			= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
		setupMenuInfo.defaults.generic.x				= x;
		setupMenuInfo.defaults.generic.y				= y;
		setupMenuInfo.defaults.generic.id				= ID_DEFAULTS;
		setupMenuInfo.defaults.generic.callback			= UI_SetupMenu_Event; 
		setupMenuInfo.defaults.string					= "DEFAULTS";
		setupMenuInfo.defaults.color					= color_red;
		setupMenuInfo.defaults.style					= UI_SMALLFONT;
	}
	*/

	//Elder: Info for setup icon
	setupMenuInfo.rq3_setupicon.generic.type				= MTYPE_BITMAP;
	setupMenuInfo.rq3_setupicon.generic.name				= RQ3_SETUP_ICON;
	setupMenuInfo.rq3_setupicon.generic.flags				= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	setupMenuInfo.rq3_setupicon.generic.x					= 0;
	setupMenuInfo.rq3_setupicon.generic.y					= 4;
	setupMenuInfo.rq3_setupicon.width						= RQ3_ICON_WIDTH;
	setupMenuInfo.rq3_setupicon.height						= RQ3_ICON_HEIGHT;

	//Elder: Info for setup title
	setupMenuInfo.rq3_setuptitle.generic.type				= MTYPE_BITMAP;
	setupMenuInfo.rq3_setuptitle.generic.name				= RQ3_SETUP_TITLE;
	setupMenuInfo.rq3_setuptitle.generic.flags				= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	setupMenuInfo.rq3_setuptitle.generic.x					= 64;
	setupMenuInfo.rq3_setuptitle.generic.y					= 12;
	setupMenuInfo.rq3_setuptitle.width						= 256;
	setupMenuInfo.rq3_setuptitle.height						= 32;

	//Elder: RQ3 Player Button
	setupMenuInfo.rq3_setupplayer.generic.type			= MTYPE_BITMAP;
	setupMenuInfo.rq3_setupplayer.generic.name			= RQ3_SETUP_PLAYER;
	setupMenuInfo.rq3_setupplayer.generic.flags			= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	setupMenuInfo.rq3_setupplayer.generic.x				= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	setupMenuInfo.rq3_setupplayer.generic.y				= y;
	setupMenuInfo.rq3_setupplayer.generic.id			= ID_CUSTOMIZEPLAYER;
	setupMenuInfo.rq3_setupplayer.generic.callback		= UI_SetupMenu_Event; 
	setupMenuInfo.rq3_setupplayer.width					= RQ3_BUTTON_WIDTH;
	setupMenuInfo.rq3_setupplayer.height				= RQ3_BUTTON_HEIGHT;
	setupMenuInfo.rq3_setupplayer.focuspic				= RQ3_FOCUS_BUTTON;

	//Elder: RQ3 Controls Button
	setupMenuInfo.rq3_setupcontrols.generic.type		= MTYPE_BITMAP;
	setupMenuInfo.rq3_setupcontrols.generic.name		= RQ3_SETUP_CONTROLS;
	setupMenuInfo.rq3_setupcontrols.generic.flags		= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	setupMenuInfo.rq3_setupcontrols.generic.x			= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	setupMenuInfo.rq3_setupcontrols.generic.y			= y;
	setupMenuInfo.rq3_setupcontrols.generic.id			= ID_CUSTOMIZECONTROLS;
	setupMenuInfo.rq3_setupcontrols.generic.callback	= UI_SetupMenu_Event; 
	setupMenuInfo.rq3_setupcontrols.width				= RQ3_BUTTON_WIDTH;
	setupMenuInfo.rq3_setupcontrols.height				= RQ3_BUTTON_HEIGHT;
	setupMenuInfo.rq3_setupcontrols.focuspic			= RQ3_FOCUS_BUTTON;

	//Elder: RQ3 System Button
	setupMenuInfo.rq3_setupsystem.generic.type			= MTYPE_BITMAP;
	setupMenuInfo.rq3_setupsystem.generic.name			= RQ3_SETUP_SYSTEM;
	setupMenuInfo.rq3_setupsystem.generic.flags			= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	setupMenuInfo.rq3_setupsystem.generic.x				= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	setupMenuInfo.rq3_setupsystem.generic.y				= y;
	setupMenuInfo.rq3_setupsystem.generic.id			= ID_SYSTEMCONFIG;
	setupMenuInfo.rq3_setupsystem.generic.callback		= UI_SetupMenu_Event;
	setupMenuInfo.rq3_setupsystem.width					= RQ3_BUTTON_WIDTH;
	setupMenuInfo.rq3_setupsystem.height				= RQ3_BUTTON_HEIGHT;
	setupMenuInfo.rq3_setupsystem.focuspic				= RQ3_FOCUS_BUTTON;

	//Elder: RQ3 Options Button
	setupMenuInfo.rq3_setupoptions.generic.type			= MTYPE_BITMAP;
	setupMenuInfo.rq3_setupoptions.generic.name			= RQ3_SETUP_OPTIONS;
	setupMenuInfo.rq3_setupoptions.generic.flags		= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	setupMenuInfo.rq3_setupoptions.generic.x			= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	setupMenuInfo.rq3_setupoptions.generic.y			= y;
	setupMenuInfo.rq3_setupoptions.generic.id			= ID_GAME;
	setupMenuInfo.rq3_setupoptions.generic.callback		= UI_SetupMenu_Event; 
	setupMenuInfo.rq3_setupoptions.width				= RQ3_BUTTON_WIDTH;
	setupMenuInfo.rq3_setupoptions.height				= RQ3_BUTTON_HEIGHT;
	setupMenuInfo.rq3_setupoptions.focuspic				= RQ3_FOCUS_BUTTON;

	//Elder: RQ3 CDKEY Button
	setupMenuInfo.rq3_setupcdkey.generic.type			= MTYPE_BITMAP;
	setupMenuInfo.rq3_setupcdkey.generic.name			= RQ3_SETUP_CDKEY;
	setupMenuInfo.rq3_setupcdkey.generic.flags			= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	setupMenuInfo.rq3_setupcdkey.generic.x				= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	setupMenuInfo.rq3_setupcdkey.generic.y				= y;
	setupMenuInfo.rq3_setupcdkey.generic.id				= ID_CDKEY;
	setupMenuInfo.rq3_setupcdkey.generic.callback		= UI_SetupMenu_Event; 
	setupMenuInfo.rq3_setupcdkey.width					= RQ3_BUTTON_WIDTH;
	setupMenuInfo.rq3_setupcdkey.height					= RQ3_BUTTON_HEIGHT;
	setupMenuInfo.rq3_setupcdkey.focuspic				= RQ3_FOCUS_BUTTON;

	//Elder: RQ3 Defaults Button
	setupMenuInfo.rq3_setupdefaults.generic.type		= MTYPE_BITMAP;
	setupMenuInfo.rq3_setupdefaults.generic.name		= RQ3_SETUP_DEFAULTS;
	setupMenuInfo.rq3_setupdefaults.generic.flags		= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	setupMenuInfo.rq3_setupdefaults.generic.x			= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	setupMenuInfo.rq3_setupdefaults.generic.y			= y;
	setupMenuInfo.rq3_setupdefaults.generic.id			= ID_DEFAULTS;
	setupMenuInfo.rq3_setupdefaults.generic.callback	= UI_SetupMenu_Event; 
	setupMenuInfo.rq3_setupdefaults.width				= RQ3_BUTTON_WIDTH;
	setupMenuInfo.rq3_setupdefaults.height				= RQ3_BUTTON_HEIGHT;
	setupMenuInfo.rq3_setupdefaults.focuspic			= RQ3_FOCUS_BUTTON;


	//Back button
	setupMenuInfo.back.generic.type					= MTYPE_BITMAP;
	setupMenuInfo.back.generic.name					= ART_BACK0;
	setupMenuInfo.back.generic.flags				= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	setupMenuInfo.back.generic.id					= ID_BACK;
	setupMenuInfo.back.generic.callback				= UI_SetupMenu_Event;
	setupMenuInfo.back.generic.x					= 8;
	setupMenuInfo.back.generic.y					= 480-44;
	setupMenuInfo.back.width						= 32;
	setupMenuInfo.back.height						= 32;
	setupMenuInfo.back.focuspic						= ART_BACK1;

	//Elder: RQ3 Status Text
	setupMenuInfo.rq3_statustext.generic.type 		= MTYPE_TEXT;
	setupMenuInfo.rq3_statustext.generic.flags		= QMF_CENTER_JUSTIFY;
	setupMenuInfo.rq3_statustext.generic.x 			= RQ3_STATUSBAR_X;
	setupMenuInfo.rq3_statustext.generic.y 			= RQ3_STATUSBAR_Y;
	setupMenuInfo.rq3_statustext.string 			= "";
	setupMenuInfo.rq3_statustext.style 				= UI_CENTER|UI_SMALLFONT;
	setupMenuInfo.rq3_statustext.color 				= color_orange;

//Blaze: Dont need this
//	Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.banner );
//	Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.framel );
//	Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.framer );
//Elder: Or this
//	Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.multim );
//	Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.setupm );
//	Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.demom );
//	Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.modsm );
//	Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.exitm );

//	Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.setupplayer );
//	Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.setupcontrols );
//	Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.setupsystem );
//	Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.game );
//	Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.cdkey );
//	Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.load );
//	Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.save );
	Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.back );
	Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.rq3_setupicon );
	Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.rq3_setuptitle );
	Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.rq3_setupplayer );
	Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.rq3_setupcontrols );
	Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.rq3_setupsystem );
	Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.rq3_setupoptions );
	Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.rq3_setupcdkey );
	
	if( !trap_Cvar_VariableValue( "cl_paused" ) ) {
		//Elder: Changed
		//Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.defaults );
		Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.rq3_setupdefaults );
	}
	
	Menu_AddItem( &setupMenuInfo.menu, &setupMenuInfo.rq3_statustext );
}


/*
=================
UI_SetupMenu_Cache
=================
*/
void UI_SetupMenu_Cache( void ) {
	trap_R_RegisterShaderNoMip( ART_BACK0 );
	trap_R_RegisterShaderNoMip( ART_BACK1 );
	//Elder: Removed
	//trap_R_RegisterShaderNoMip( ART_FRAMEL );
	//trap_R_RegisterShaderNoMip( ART_FRAMER );
	//Elder: Added
	trap_R_RegisterShaderNoMip( RQ3_SETUP_ICON );
	trap_R_RegisterShaderNoMip( RQ3_SETUP_TITLE );
	trap_R_RegisterShaderNoMip( RQ3_SETUP_CDKEY );
	trap_R_RegisterShaderNoMip( RQ3_SETUP_DEFAULTS );
	trap_R_RegisterShaderNoMip( RQ3_SETUP_PLAYER );
	trap_R_RegisterShaderNoMip( RQ3_SETUP_CONTROLS );
	trap_R_RegisterShaderNoMip( RQ3_SETUP_SYSTEM );
	trap_R_RegisterShaderNoMip( RQ3_SETUP_OPTIONS );
	trap_R_RegisterShaderNoMip( RQ3_FOCUS_BUTTON );
	
}


/*
===============
UI_SetupMenu
===============
*/
void UI_SetupMenu( void ) {
	UI_SetupMenu_Init();
	UI_PushMenu( &setupMenuInfo.menu );
}
