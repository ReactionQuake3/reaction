//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.6  2002/01/11 19:48:30  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.5  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
/*
=======================================================================

DISPLAY OPTIONS MENU

=======================================================================
*/

#include "ui_local.h"

//Elder: removed
//#define ART_FRAMEL			"menu/art/frame2_l"
//#define ART_FRAMER			"menu/art/frame1_r"
#define ART_BACK0			"menu/art/rq3-menu-back.tga"
#define ART_BACK1			"menu/art/rq3-menu-back-focus.tga"

#define ID_GRAPHICS			10
#define ID_DISPLAY			11
#define ID_SOUND			12
#define ID_NETWORK			13
#define ID_BRIGHTNESS		14
#define ID_SCREENSIZE		15
#define ID_BACK				16
//Elder: new options
#define ID_OVERBRIGHT		17

//Elder: RQ3 stuff
#define RQ3_SYSTEM_ICON		"menu/art/rq3-setup-system.jpg"
#define RQ3_SETUP_TITLE		"menu/art/rq3-title-setup.tga"
#define RQ3_FOCUS_BUTTON	"menu/art/rq3-menu-focus.tga"
#define RQ3_GRAPHICS_BUTTON	"menu/art/rq3-system-graphics.tga"
#define RQ3_DISPLAY_BUTTON	"menu/art/rq3-system-display.tga"
#define RQ3_SOUND_BUTTON	"menu/art/rq3-system-sound.tga"
#define RQ3_NETWORK_BUTTON	"menu/art/rq3-system-network.tga"

typedef struct {
	menuframework_s	menu;
//Blaze: Dont need this
//	menutext_s		banner;
//	menubitmap_s	framel;
//	menubitmap_s	framer;
//Elder: removed
//	menutext_s		multim;
//	menutext_s		setupm;
//	menutext_s		demom;
//	menutext_s		modsm;
//	menutext_s		exitm;

//Elder: RQ3 stuff	
	menubitmap_s	rq3_setuptitle;
	menubitmap_s	rq3_systemicon;
	menubitmap_s	rq3_graphics;
	menubitmap_s	rq3_display;
	menubitmap_s	rq3_sound;
	menubitmap_s	rq3_network;
	menutext_s		rq3_statustext;

	menuradiobutton_s	rq3_overbright;

//Elder: removed
//	menutext_s		graphics;
//	menutext_s		display;
//	menutext_s		sound;
//	menutext_s		network;

	menuslider_s	brightness;
	menuslider_s	screensize;

	menubitmap_s	back;
} displayOptionsInfo_t;

static displayOptionsInfo_t	displayOptionsInfo;


/*
=================
UI_DisplayOptionsMenu_Event
=================
*/
static void UI_DisplayOptionsMenu_Event( void* ptr, int event ) {
	//Elder: for status bar
	if( event == QM_LOSTFOCUS ) {
		displayOptionsInfo.rq3_statustext.string = "";
		return;
	}
	else if ( event == QM_GOTFOCUS ) {
		switch( ((menucommon_s*)ptr)->id ) {
		case ID_GRAPHICS:
			displayOptionsInfo.rq3_statustext.string = "Change graphics settings";
			break;

		case ID_DISPLAY:
			displayOptionsInfo.rq3_statustext.string = "Change display settings";
			break;

		case ID_SOUND:
			displayOptionsInfo.rq3_statustext.string = "Change sound settings";
			break;
	
		case ID_NETWORK:
			displayOptionsInfo.rq3_statustext.string = "Change network settings";
			break;

		case ID_BRIGHTNESS:
			displayOptionsInfo.rq3_statustext.string = "Adjust gamma correction";
			break;
		
		case ID_SCREENSIZE:
			displayOptionsInfo.rq3_statustext.string = "Adjust in-game screen size";
			break;
		
		case ID_BACK:
			displayOptionsInfo.rq3_statustext.string = "Return to setup menu";
			break;

		//Elder: added
		case ID_OVERBRIGHT:
			displayOptionsInfo.rq3_statustext.string = "Toggle over-bright bits (recommended: off)";
			break;
		
		default:
			displayOptionsInfo.rq3_statustext.string = "";
			break;
		}
	}
	else if( event == QM_ACTIVATED ) {
		switch( ((menucommon_s*)ptr)->id ) {
		
		case ID_GRAPHICS:
			UI_PopMenu();
			UI_GraphicsOptionsMenu();
			break;

		case ID_DISPLAY:
			break;

		case ID_SOUND:
			UI_PopMenu();
			UI_SoundOptionsMenu();
			break;

		case ID_NETWORK:
			UI_PopMenu();
			UI_NetworkOptionsMenu();
			break;

		case ID_BRIGHTNESS:
			trap_Cvar_SetValue( "r_gamma", displayOptionsInfo.brightness.curvalue / 10.0f );
			break;
	
		case ID_SCREENSIZE:
			trap_Cvar_SetValue( "cg_viewsize", displayOptionsInfo.screensize.curvalue * 10 );
			break;
		
		//Elder: added
		case ID_OVERBRIGHT:
			trap_Cvar_SetValue( "r_overBrightBits", displayOptionsInfo.rq3_overbright.curvalue);
			break;
		
		case ID_BACK:
			UI_PopMenu();
			break;
		}
	}
}

/*
===============
Added by Elder
UI_NetworkOptionsMenu_Draw
===============
*/
static void UI_DisplayOptionsMenu_Draw( void ) {
	//Elder: "Dim" and "Letterbox" mask
	UI_FillRect( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color_deepdim );
	UI_FillRect( 0, 0, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 54, SCREEN_WIDTH, 2, color_red);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 2, color_red);
	
	// standard menu drawing
	Menu_Draw( &displayOptionsInfo.menu );
}

/*
===============
UI_DisplayOptionsMenu_Init
===============
*/
static void UI_DisplayOptionsMenu_Init( void ) {
	int		y = 12;
	int		buttonCount = 0;

	memset( &displayOptionsInfo, 0, sizeof(displayOptionsInfo) );

	UI_DisplayOptionsMenu_Cache();
	displayOptionsInfo.menu.draw	   = UI_DisplayOptionsMenu_Draw;
	displayOptionsInfo.menu.wrapAround = qtrue;
	displayOptionsInfo.menu.fullscreen = qtrue;
	displayOptionsInfo.menu.showlogo   = qtrue;

/*	displayOptionsInfo.banner.generic.type		= MTYPE_BTEXT;
	displayOptionsInfo.banner.generic.flags		= QMF_CENTER_JUSTIFY;
	displayOptionsInfo.banner.generic.x			= 320;
	displayOptionsInfo.banner.generic.y			= 16;
	displayOptionsInfo.banner.string			= "SYSTEM SETUP";
	displayOptionsInfo.banner.color				= color_white;
	displayOptionsInfo.banner.style				= UI_CENTER;

	displayOptionsInfo.framel.generic.type		= MTYPE_BITMAP;
	displayOptionsInfo.framel.generic.name		= ART_FRAMEL;
	displayOptionsInfo.framel.generic.flags		= QMF_INACTIVE;
	displayOptionsInfo.framel.generic.x			= 0;  
	displayOptionsInfo.framel.generic.y			= 78;
	displayOptionsInfo.framel.width				= 256;
	displayOptionsInfo.framel.height			= 329;

	displayOptionsInfo.framer.generic.type		= MTYPE_BITMAP;
	displayOptionsInfo.framer.generic.name		= ART_FRAMER;
	displayOptionsInfo.framer.generic.flags		= QMF_INACTIVE;
	displayOptionsInfo.framer.generic.x			= 376;
	displayOptionsInfo.framer.generic.y			= 76;
	displayOptionsInfo.framer.width				= 256;
	displayOptionsInfo.framer.height			= 334;
*/
/* Elder: not needed anymore
	displayOptionsInfo.multim.generic.type	= MTYPE_PTEXT;
	displayOptionsInfo.multim.generic.flags = QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	displayOptionsInfo.multim.generic.x		= 120;
	displayOptionsInfo.multim.generic.y		= 3;
	displayOptionsInfo.multim.string		= "MULTIPLAYER";
	displayOptionsInfo.multim.color			= color_red;
	displayOptionsInfo.multim.style			= UI_CENTER | UI_DROPSHADOW;

	displayOptionsInfo.setupm.generic.type	= MTYPE_PTEXT;
	displayOptionsInfo.setupm.generic.flags = QMF_CENTER_JUSTIFY|QMF_INACTIVE|QMF_HIGHLIGHT;
	displayOptionsInfo.setupm.generic.x		= 280;
	displayOptionsInfo.setupm.generic.y		= 3;
	displayOptionsInfo.setupm.string		= "SETUP";
	displayOptionsInfo.setupm.color			= color_red;
	displayOptionsInfo.setupm.style			= UI_CENTER | UI_DROPSHADOW;

	displayOptionsInfo.demom.generic.type	= MTYPE_PTEXT;
	displayOptionsInfo.demom.generic.flags	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	displayOptionsInfo.demom.generic.x		= 390;
	displayOptionsInfo.demom.generic.y		= 3;
	displayOptionsInfo.demom.string			= "DEMOS";
	displayOptionsInfo.demom.color			= color_red;
	displayOptionsInfo.demom.style			= UI_CENTER | UI_DROPSHADOW;

	displayOptionsInfo.modsm.generic.type	= MTYPE_PTEXT;
	displayOptionsInfo.modsm.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	displayOptionsInfo.modsm.generic.x		= 500;
	displayOptionsInfo.modsm.generic.y		= 3;
	displayOptionsInfo.modsm.string			= "MODS";
	displayOptionsInfo.modsm.color			= color_red;
	displayOptionsInfo.modsm.style			= UI_CENTER | UI_DROPSHADOW;

	displayOptionsInfo.exitm.generic.type	= MTYPE_PTEXT;
	displayOptionsInfo.exitm.generic.flags  = QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	displayOptionsInfo.exitm.generic.x		= 590;
	displayOptionsInfo.exitm.generic.y		= 3;
	displayOptionsInfo.exitm.string			= "EXIT";
	displayOptionsInfo.exitm.color			= color_red;
	displayOptionsInfo.exitm.style			= UI_CENTER | UI_DROPSHADOW;
*/

	//Elder: Info for system icon
	displayOptionsInfo.rq3_systemicon.generic.type				= MTYPE_BITMAP;
	displayOptionsInfo.rq3_systemicon.generic.name				= RQ3_SYSTEM_ICON;
	displayOptionsInfo.rq3_systemicon.generic.flags				= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	displayOptionsInfo.rq3_systemicon.generic.x					= 0;
	displayOptionsInfo.rq3_systemicon.generic.y					= 4;
	displayOptionsInfo.rq3_systemicon.width						= RQ3_ICON_WIDTH;
	displayOptionsInfo.rq3_systemicon.height					= RQ3_ICON_HEIGHT;

	//Elder: Info for setup title
	displayOptionsInfo.rq3_setuptitle.generic.type				= MTYPE_BITMAP;
	displayOptionsInfo.rq3_setuptitle.generic.name				= RQ3_SETUP_TITLE;
	displayOptionsInfo.rq3_setuptitle.generic.flags				= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	displayOptionsInfo.rq3_setuptitle.generic.x					= 64;
	displayOptionsInfo.rq3_setuptitle.generic.y					= 12;
	displayOptionsInfo.rq3_setuptitle.width						= 256;
	displayOptionsInfo.rq3_setuptitle.height					= 32;

	//Elder: RQ3 Graphics Button
	displayOptionsInfo.rq3_graphics.generic.type		= MTYPE_BITMAP;
	displayOptionsInfo.rq3_graphics.generic.name		= RQ3_GRAPHICS_BUTTON;
	displayOptionsInfo.rq3_graphics.generic.flags		= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	displayOptionsInfo.rq3_graphics.generic.x			= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	displayOptionsInfo.rq3_graphics.generic.y			= y;
	displayOptionsInfo.rq3_graphics.generic.id			= ID_GRAPHICS;
	displayOptionsInfo.rq3_graphics.generic.callback	= UI_DisplayOptionsMenu_Event;
	displayOptionsInfo.rq3_graphics.width				= RQ3_BUTTON_WIDTH;
	displayOptionsInfo.rq3_graphics.height				= RQ3_BUTTON_HEIGHT;
	displayOptionsInfo.rq3_graphics.focuspic			= RQ3_FOCUS_BUTTON;
	
	//Elder: RQ3 Display Button
	displayOptionsInfo.rq3_display.generic.type			= MTYPE_BITMAP;
	displayOptionsInfo.rq3_display.generic.name			= RQ3_DISPLAY_BUTTON;
	displayOptionsInfo.rq3_display.generic.flags		= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	displayOptionsInfo.rq3_display.generic.x			= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	displayOptionsInfo.rq3_display.generic.y			= y;
	displayOptionsInfo.rq3_display.generic.id			= ID_DISPLAY;
	displayOptionsInfo.rq3_display.generic.callback		= UI_DisplayOptionsMenu_Event;
	displayOptionsInfo.rq3_display.width				= RQ3_BUTTON_WIDTH;
	displayOptionsInfo.rq3_display.height				= RQ3_BUTTON_HEIGHT;
	displayOptionsInfo.rq3_display.focuspic				= RQ3_FOCUS_BUTTON;

	//Elder: RQ3 Sound Button
	displayOptionsInfo.rq3_sound.generic.type			= MTYPE_BITMAP;
	displayOptionsInfo.rq3_sound.generic.name			= RQ3_SOUND_BUTTON;
	displayOptionsInfo.rq3_sound.generic.flags			= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	displayOptionsInfo.rq3_sound.generic.x				= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	displayOptionsInfo.rq3_sound.generic.y				= y;
	displayOptionsInfo.rq3_sound.generic.id				= ID_SOUND;
	displayOptionsInfo.rq3_sound.generic.callback		= UI_DisplayOptionsMenu_Event;
	displayOptionsInfo.rq3_sound.width					= RQ3_BUTTON_WIDTH;
	displayOptionsInfo.rq3_sound.height					= RQ3_BUTTON_HEIGHT;
	displayOptionsInfo.rq3_sound.focuspic				= RQ3_FOCUS_BUTTON;

	//Elder: RQ3 Network Button
	displayOptionsInfo.rq3_network.generic.type			= MTYPE_BITMAP;
	displayOptionsInfo.rq3_network.generic.name			= RQ3_NETWORK_BUTTON;
	displayOptionsInfo.rq3_network.generic.flags		= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	displayOptionsInfo.rq3_network.generic.x			= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	displayOptionsInfo.rq3_network.generic.y			= y;
	displayOptionsInfo.rq3_network.generic.id			= ID_NETWORK;
	displayOptionsInfo.rq3_network.generic.callback		= UI_DisplayOptionsMenu_Event;
	displayOptionsInfo.rq3_network.width				= RQ3_BUTTON_WIDTH;
	displayOptionsInfo.rq3_network.height				= RQ3_BUTTON_HEIGHT;
	displayOptionsInfo.rq3_network.focuspic				= RQ3_FOCUS_BUTTON;

	//Elder: RQ3 Status Text
	displayOptionsInfo.rq3_statustext.generic.type 		= MTYPE_TEXT;
	displayOptionsInfo.rq3_statustext.generic.flags		= QMF_CENTER_JUSTIFY;
	displayOptionsInfo.rq3_statustext.generic.x 		= RQ3_STATUSBAR_X;
	displayOptionsInfo.rq3_statustext.generic.y 		= RQ3_STATUSBAR_Y;
	displayOptionsInfo.rq3_statustext.string 			= "";
	displayOptionsInfo.rq3_statustext.style 			= UI_CENTER|UI_SMALLFONT;
	displayOptionsInfo.rq3_statustext.color 			= color_orange;

	/*
	displayOptionsInfo.graphics.generic.type		= MTYPE_PTEXT;
	displayOptionsInfo.graphics.generic.flags		= QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	displayOptionsInfo.graphics.generic.id			= ID_GRAPHICS;
	displayOptionsInfo.graphics.generic.callback	= UI_DisplayOptionsMenu_Event;
	displayOptionsInfo.graphics.generic.x			= 216;
	displayOptionsInfo.graphics.generic.y			= 240 - 2 * PROP_HEIGHT;
	displayOptionsInfo.graphics.string				= "GRAPHICS";
	displayOptionsInfo.graphics.style				= UI_RIGHT;
	displayOptionsInfo.graphics.color				= color_red;

	displayOptionsInfo.display.generic.type			= MTYPE_PTEXT;
	displayOptionsInfo.display.generic.flags		= QMF_RIGHT_JUSTIFY;
	displayOptionsInfo.display.generic.id			= ID_DISPLAY;
	displayOptionsInfo.display.generic.callback		= UI_DisplayOptionsMenu_Event;
	displayOptionsInfo.display.generic.x			= 216;
	displayOptionsInfo.display.generic.y			= 240 - PROP_HEIGHT;
	displayOptionsInfo.display.string				= "DISPLAY";
	displayOptionsInfo.display.style				= UI_RIGHT;
	displayOptionsInfo.display.color				= color_red;

	displayOptionsInfo.sound.generic.type			= MTYPE_PTEXT;
	displayOptionsInfo.sound.generic.flags			= QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	displayOptionsInfo.sound.generic.id				= ID_SOUND;
	displayOptionsInfo.sound.generic.callback		= UI_DisplayOptionsMenu_Event;
	displayOptionsInfo.sound.generic.x				= 216;
	displayOptionsInfo.sound.generic.y				= 240;
	displayOptionsInfo.sound.string					= "SOUND";
	displayOptionsInfo.sound.style					= UI_RIGHT;
	displayOptionsInfo.sound.color					= color_red;

	displayOptionsInfo.network.generic.type			= MTYPE_PTEXT;
	displayOptionsInfo.network.generic.flags		= QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	displayOptionsInfo.network.generic.id			= ID_NETWORK;
	displayOptionsInfo.network.generic.callback		= UI_DisplayOptionsMenu_Event;
	displayOptionsInfo.network.generic.x			= 216;
	displayOptionsInfo.network.generic.y			= 240 + PROP_HEIGHT;
	displayOptionsInfo.network.string				= "NETWORK";
	displayOptionsInfo.network.style				= UI_RIGHT;
	displayOptionsInfo.network.color				= color_red;
	*/
	
	//y = 240 - 1 * (BIGCHAR_HEIGHT+2);
	displayOptionsInfo.brightness.generic.type		= MTYPE_SLIDER;
	displayOptionsInfo.brightness.generic.name		= "Brightness:";
	displayOptionsInfo.brightness.generic.flags		= QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	displayOptionsInfo.brightness.generic.callback	= UI_DisplayOptionsMenu_Event;
	displayOptionsInfo.brightness.generic.id		= ID_BRIGHTNESS;
	displayOptionsInfo.brightness.generic.x			= 200;
	displayOptionsInfo.brightness.generic.y			= 64;
	displayOptionsInfo.brightness.minvalue			= 5;
	displayOptionsInfo.brightness.maxvalue			= 20;
	if( !uis.glconfig.deviceSupportsGamma ) {
		displayOptionsInfo.brightness.generic.flags |= QMF_GRAYED;
	}

	//y += BIGCHAR_HEIGHT+2;
	displayOptionsInfo.screensize.generic.type		= MTYPE_SLIDER;
	displayOptionsInfo.screensize.generic.name		= "Screen Size:";
	displayOptionsInfo.screensize.generic.flags		= QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	displayOptionsInfo.screensize.generic.callback	= UI_DisplayOptionsMenu_Event;
	displayOptionsInfo.screensize.generic.id		= ID_SCREENSIZE;
	displayOptionsInfo.screensize.generic.x			= 200;
	displayOptionsInfo.screensize.generic.y			= 64 + BIGCHAR_HEIGHT + 2;;
	displayOptionsInfo.screensize.minvalue			= 3;
    displayOptionsInfo.screensize.maxvalue			= 10;

	//Elder: added
	displayOptionsInfo.rq3_overbright.generic.type		= MTYPE_RADIOBUTTON;
	displayOptionsInfo.rq3_overbright.generic.name		= "Overbright Bits:";
	displayOptionsInfo.rq3_overbright.generic.flags		= QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	displayOptionsInfo.rq3_overbright.generic.callback	= UI_DisplayOptionsMenu_Event;
	displayOptionsInfo.rq3_overbright.generic.id		= ID_OVERBRIGHT;
	displayOptionsInfo.rq3_overbright.generic.x			= 200;
	displayOptionsInfo.rq3_overbright.generic.y			= 64 + 2 * (BIGCHAR_HEIGHT + 2);
	
	displayOptionsInfo.back.generic.type		= MTYPE_BITMAP;
	displayOptionsInfo.back.generic.name		= ART_BACK0;
	displayOptionsInfo.back.generic.flags		= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	displayOptionsInfo.back.generic.callback	= UI_DisplayOptionsMenu_Event;
	displayOptionsInfo.back.generic.id			= ID_BACK;
	displayOptionsInfo.back.generic.x			= 8;
	displayOptionsInfo.back.generic.y			= 480-44;
	displayOptionsInfo.back.width				= 32;
	displayOptionsInfo.back.height				= 32;
	displayOptionsInfo.back.focuspic			= ART_BACK1;

//	Menu_AddItem( &displayOptionsInfo.menu, ( void * ) &displayOptionsInfo.banner );
//	Menu_AddItem( &displayOptionsInfo.menu, ( void * ) &displayOptionsInfo.framel );
//	Menu_AddItem( &displayOptionsInfo.menu, ( void * ) &displayOptionsInfo.framer );
/* Elder: removed	
	Menu_AddItem( &displayOptionsInfo.menu, &displayOptionsInfo.multim );
	Menu_AddItem( &displayOptionsInfo.menu, &displayOptionsInfo.setupm );
	Menu_AddItem( &displayOptionsInfo.menu, &displayOptionsInfo.demom );
	Menu_AddItem( &displayOptionsInfo.menu, &displayOptionsInfo.modsm );
	Menu_AddItem( &displayOptionsInfo.menu, &displayOptionsInfo.exitm );
	Menu_AddItem( &displayOptionsInfo.menu, ( void * ) &displayOptionsInfo.graphics );
	Menu_AddItem( &displayOptionsInfo.menu, ( void * ) &displayOptionsInfo.display );
	Menu_AddItem( &displayOptionsInfo.menu, ( void * ) &displayOptionsInfo.sound );
	Menu_AddItem( &displayOptionsInfo.menu, ( void * ) &displayOptionsInfo.network );
*/
	
	//Elder: added
	Menu_AddItem( &displayOptionsInfo.menu, ( void * ) &displayOptionsInfo.rq3_systemicon );
	Menu_AddItem( &displayOptionsInfo.menu, ( void * ) &displayOptionsInfo.rq3_setuptitle );
	Menu_AddItem( &displayOptionsInfo.menu, ( void * ) &displayOptionsInfo.rq3_graphics );
	Menu_AddItem( &displayOptionsInfo.menu, ( void * ) &displayOptionsInfo.rq3_display );
	Menu_AddItem( &displayOptionsInfo.menu, ( void * ) &displayOptionsInfo.rq3_sound );
	Menu_AddItem( &displayOptionsInfo.menu, ( void * ) &displayOptionsInfo.rq3_network );
	Menu_AddItem( &displayOptionsInfo.menu, ( void * ) &displayOptionsInfo.rq3_statustext );
	
	Menu_AddItem( &displayOptionsInfo.menu, ( void * ) &displayOptionsInfo.brightness );
	Menu_AddItem( &displayOptionsInfo.menu, ( void * ) &displayOptionsInfo.screensize );
	Menu_AddItem( &displayOptionsInfo.menu, ( void * ) &displayOptionsInfo.rq3_overbright );
	
	Menu_AddItem( &displayOptionsInfo.menu, ( void * ) &displayOptionsInfo.back );

	displayOptionsInfo.brightness.curvalue  = trap_Cvar_VariableValue("r_gamma") * 10;
	displayOptionsInfo.screensize.curvalue  = trap_Cvar_VariableValue( "cg_viewsize")/10;
	//Elder: added
	displayOptionsInfo.rq3_overbright.curvalue = trap_Cvar_VariableValue( "r_overbrightbits" ) != 0;
}


/*
===============
UI_DisplayOptionsMenu_Cache
===============
*/
void UI_DisplayOptionsMenu_Cache( void ) {
//Elder: removed
//	trap_R_RegisterShaderNoMip( ART_FRAMEL );
//	trap_R_RegisterShaderNoMip( ART_FRAMER );
	trap_R_RegisterShaderNoMip( ART_BACK0 );
	trap_R_RegisterShaderNoMip( ART_BACK1 );
//Elder: added
	trap_R_RegisterShaderNoMip( RQ3_SYSTEM_ICON );
	trap_R_RegisterShaderNoMip( RQ3_SETUP_TITLE );
	trap_R_RegisterShaderNoMip( RQ3_GRAPHICS_BUTTON );	
	trap_R_RegisterShaderNoMip( RQ3_DISPLAY_BUTTON );
	trap_R_RegisterShaderNoMip( RQ3_SOUND_BUTTON );	
	trap_R_RegisterShaderNoMip( RQ3_NETWORK_BUTTON );
	trap_R_RegisterShaderNoMip( RQ3_FOCUS_BUTTON );
}


/*
===============
UI_DisplayOptionsMenu
===============
*/
void UI_DisplayOptionsMenu( void ) {
	UI_DisplayOptionsMenu_Init();
	UI_PushMenu( &displayOptionsInfo.menu );
	//Elder: shifted to .rq3_display
	Menu_SetCursorToItem( &displayOptionsInfo.menu, &displayOptionsInfo.rq3_display );
}
