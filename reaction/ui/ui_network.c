//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log: &
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
/*
=======================================================================

NETWORK OPTIONS MENU

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
#define ID_RATE				14
#define ID_BACK				15
#define ID_RATE2			16

//Elder: RQ3 stuff
#define RQ3_SYSTEM_ICON		"menu/art/rq3-setup-system.jpg"
#define RQ3_SETUP_TITLE		"menu/art/rq3-title-setup.tga"
#define RQ3_FOCUS_BUTTON	"menu/art/rq3-menu-focus.tga"
#define RQ3_GRAPHICS_BUTTON	"menu/art/rq3-system-graphics.tga"
#define RQ3_DISPLAY_BUTTON	"menu/art/rq3-system-display.tga"
#define RQ3_SOUND_BUTTON	"menu/art/rq3-system-sound.tga"
#define RQ3_NETWORK_BUTTON	"menu/art/rq3-system-network.tga"
//Elder: Number of digits in rate field
#define MAX_RATE_INPUT		6

/* Elder: added a few more options - but not used anymore;
static const char *rate_items[] = {
	"2500  - 28.8K",
	"3000  - 33.6K",
	"4000  - 56K",
	"5000  - ISDN",
	"8000  - Low-bandwidth Cable/DSL",
	"10000 - High-bandwidth Cable/DSL",
	"25000 - LAN/T1 or better",
	0
};
*/

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
//	menutext_s		graphics;
//	menutext_s		display;
//	menutext_s		sound;
//	menutext_s		network;
//	menulist_s		rate;

	menubitmap_s	back;

//Elder: RQ3 stuff	
	menubitmap_s	rq3_setuptitle;
	menubitmap_s	rq3_systemicon;
	menubitmap_s	rq3_graphics;
	menubitmap_s	rq3_display;
	menubitmap_s	rq3_sound;
	menubitmap_s	rq3_network;
	menufield_s		rate_input;
	menutext_s		rq3_statustext;
	
	int 			rate_counter;
	
} networkOptionsInfo_t;

static networkOptionsInfo_t	networkOptionsInfo;
	
//Elder: prototypes
static void Network_SaveChanges( void );
static sfxHandle_t Network_MenuKey( int key );


/*
=================
UI_NetworkOptionsMenu_Event
=================
*/
static void UI_NetworkOptionsMenu_Event( void* ptr, int event ) {
	//Elder: for status bar
	if( event == QM_LOSTFOCUS ) {
		networkOptionsInfo.rq3_statustext.string = "";
		return;
	}
	else if ( event == QM_GOTFOCUS ) {
		switch( ((menucommon_s*)ptr)->id ) {
		case ID_GRAPHICS:
			networkOptionsInfo.rq3_statustext.string = "Change graphics settings";
			break;

		case ID_DISPLAY:
			networkOptionsInfo.rq3_statustext.string = "Change display settings";
			break;

		case ID_SOUND:
			networkOptionsInfo.rq3_statustext.string = "Change sound settings";
			break;
	
		case ID_NETWORK:
			networkOptionsInfo.rq3_statustext.string = "Change network settings";
			break;
		
		case ID_BACK:
			networkOptionsInfo.rq3_statustext.string = "Return to setup menu";
			break;
		
		case ID_RATE2:
			networkOptionsInfo.rq3_statustext.string = "Set rate: click to choose or type in manually";
			break;
		
		default:
			networkOptionsInfo.rq3_statustext.string = "";
			break;
		}
	}
	else if( event == QM_ACTIVATED ) {
	
		switch( ((menucommon_s*)ptr)->id ) {
		case ID_GRAPHICS:
			Network_SaveChanges();
			UI_PopMenu();
			UI_GraphicsOptionsMenu();
			break;

		case ID_DISPLAY:
			Network_SaveChanges();
			UI_PopMenu();
			UI_DisplayOptionsMenu();
			break;

		case ID_SOUND:
			Network_SaveChanges();
			UI_PopMenu();
			UI_SoundOptionsMenu();
			break;
	
		case ID_NETWORK:
			break;
	
		case ID_RATE2:
			//Elder: click to toggle
			if( networkOptionsInfo.rate_counter == 0 ) {
				Q_strncpyz( networkOptionsInfo.rate_input.field.buffer, "2500", sizeof(networkOptionsInfo.rate_input.field.buffer) );	
				//trap_Cvar_SetValue( "rate", 2500 );
			}
			else if( networkOptionsInfo.rate_counter == 1 ) {
				Q_strncpyz( networkOptionsInfo.rate_input.field.buffer, "3000", sizeof(networkOptionsInfo.rate_input.field.buffer) );	
				//trap_Cvar_SetValue( "rate", 3000 );
			}
			else if( networkOptionsInfo.rate_counter == 2 ) {
				Q_strncpyz( networkOptionsInfo.rate_input.field.buffer, "4000", sizeof(networkOptionsInfo.rate_input.field.buffer) );	
				//trap_Cvar_SetValue( "rate", 4000 );
			}
			else if( networkOptionsInfo.rate_counter == 3 ) {
				Q_strncpyz( networkOptionsInfo.rate_input.field.buffer, "5000", sizeof(networkOptionsInfo.rate_input.field.buffer) );	
				//trap_Cvar_SetValue( "rate", 5000 );
			}
			//Elder: added
			else if( networkOptionsInfo.rate_counter == 4 ) {
				Q_strncpyz( networkOptionsInfo.rate_input.field.buffer, "8000", sizeof(networkOptionsInfo.rate_input.field.buffer) );	
				//trap_Cvar_SetValue( "rate", 8000 );
			}
			else if( networkOptionsInfo.rate_counter == 5 ) {
				Q_strncpyz( networkOptionsInfo.rate_input.field.buffer, "10000", sizeof(networkOptionsInfo.rate_input.field.buffer) );	
				//trap_Cvar_SetValue( "rate", 10000 );
			}
			else if( networkOptionsInfo.rate_counter == 6 ) {
				Q_strncpyz( networkOptionsInfo.rate_input.field.buffer, "25000", sizeof(networkOptionsInfo.rate_input.field.buffer) );	
				//trap_Cvar_SetValue( "rate", 25000 );
			}
			if (networkOptionsInfo.rate_counter >= 6) {
				networkOptionsInfo.rate_counter = 0;
			}
			else {
				networkOptionsInfo.rate_counter++;
			}
			break;
		//case ID_RATE2:
			//Elder: not used anymore - unreliable
			//	trap_Cvar_SetValue( "rate", atoi(networkOptionsInfo.rate_input.field.buffer));
			//break;
	
		case ID_BACK:
			//Elder: added
			Network_SaveChanges();
			UI_PopMenu();
			break;
		}
	}
}	

/*
=================
Added by Elder
Network_SaveChanges
Borrowed concept from ui_playersettings.c
=================
*/
static void Network_SaveChanges( void ) {
	//Elder: Who's going to have rates >999999, let alone 99999?
	char s_rate[6];

	Q_strncpyz( s_rate, networkOptionsInfo.rate_input.field.buffer, sizeof(s_rate) );	
	if (strlen(s_rate) > 0) {
		// save rate cvar
		trap_Cvar_SetValue( "rate", atoi(networkOptionsInfo.rate_input.field.buffer));
	}

}


/*
=================
Added by Elder
Network_MenuKey
Borrowed concept from ui_playersettings.c
=================
*/
static sfxHandle_t Network_MenuKey( int key ) {
	//commit changes if leaving menus
	if( key == K_MOUSE2 || key == K_ESCAPE ) {
		Network_SaveChanges();
	}
	return Menu_DefaultKey( &networkOptionsInfo.menu, key );
}

/*
===============
Added by Elder
UI_NetworkOptionsMenu_Draw
===============
*/
static void UI_NetworkOptionsMenu_Draw( void ) {
	//Elder: "Dim" and "Letterbox" mask
	UI_FillRect( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color_deepdim );
	UI_FillRect( 0, 0, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 54, SCREEN_WIDTH, 2, color_red);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 2, color_red);

	// standard menu drawing
	Menu_Draw( &networkOptionsInfo.menu );
}

/*
===============
UI_NetworkOptionsMenu_Init
===============
*/
static void UI_NetworkOptionsMenu_Init( void ) {
	int		y = 12;
	//Elder: not needed anymore
	//int		rate;
	int		buttonCount = 0;

	memset( &networkOptionsInfo, 0, sizeof(networkOptionsInfo) );
	UI_NetworkOptionsMenu_Cache();
	
	networkOptionsInfo.rate_counter = 0;
	
	//Elder: added draw function
	networkOptionsInfo.menu.draw		= UI_NetworkOptionsMenu_Draw;
	//Elder: added to trap rate setting on exit (see Network_MenuKey())
	networkOptionsInfo.menu.key         = Network_MenuKey;
	networkOptionsInfo.menu.wrapAround  = qtrue;
	networkOptionsInfo.menu.fullscreen  = qtrue;
	networkOptionsInfo.menu.showlogo    = qtrue;

/*	networkOptionsInfo.banner.generic.type		= MTYPE_BTEXT;
	networkOptionsInfo.banner.generic.flags		= QMF_CENTER_JUSTIFY;
	networkOptionsInfo.banner.generic.x			= 320;
	networkOptionsInfo.banner.generic.y			= 16;
	networkOptionsInfo.banner.string			= "SYSTEM SETUP";
	networkOptionsInfo.banner.color				= color_white;
	networkOptionsInfo.banner.style				= UI_CENTER;

	networkOptionsInfo.framel.generic.type		= MTYPE_BITMAP;
	networkOptionsInfo.framel.generic.name		= ART_FRAMEL;
	networkOptionsInfo.framel.generic.flags		= QMF_INACTIVE;
	networkOptionsInfo.framel.generic.x			= 0;  
	networkOptionsInfo.framel.generic.y			= 78;
	networkOptionsInfo.framel.width				= 256;
	networkOptionsInfo.framel.height			= 329;

	networkOptionsInfo.framer.generic.type		= MTYPE_BITMAP;
	networkOptionsInfo.framer.generic.name		= ART_FRAMER;
	networkOptionsInfo.framer.generic.flags		= QMF_INACTIVE;
	networkOptionsInfo.framer.generic.x			= 376;
	networkOptionsInfo.framer.generic.y			= 76;
	networkOptionsInfo.framer.width				= 256;
	networkOptionsInfo.framer.height			= 334;
*/
/*Elder: removed
	networkOptionsInfo.multim.generic.type		= MTYPE_PTEXT;
	networkOptionsInfo.multim.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	networkOptionsInfo.multim.generic.x			= 120;
	networkOptionsInfo.multim.generic.y			= 3;
	networkOptionsInfo.multim.string			= "MULTIPLAYER";
	networkOptionsInfo.multim.color				= color_red;
	networkOptionsInfo.multim.style				= UI_CENTER | UI_DROPSHADOW;

	networkOptionsInfo.setupm.generic.type		= MTYPE_PTEXT;
	networkOptionsInfo.setupm.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_INACTIVE|QMF_HIGHLIGHT;
	networkOptionsInfo.setupm.generic.x			= 280;
	networkOptionsInfo.setupm.generic.y			= 3;
	networkOptionsInfo.setupm.string			= "SETUP";
	networkOptionsInfo.setupm.color				= color_red;
	networkOptionsInfo.setupm.style				= UI_CENTER | UI_DROPSHADOW;

	networkOptionsInfo.demom.generic.type		= MTYPE_PTEXT;
	networkOptionsInfo.demom.generic.flags		= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	networkOptionsInfo.demom.generic.x			= 390;
	networkOptionsInfo.demom.generic.y			= 3;
	networkOptionsInfo.demom.string				= "DEMOS";
	networkOptionsInfo.demom.color				= color_red;
	networkOptionsInfo.demom.style				= UI_CENTER | UI_DROPSHADOW;

	networkOptionsInfo.modsm.generic.type		= MTYPE_PTEXT;
	networkOptionsInfo.modsm.generic.flags 		= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	networkOptionsInfo.modsm.generic.x			= 500;
	networkOptionsInfo.modsm.generic.y			= 3;
	networkOptionsInfo.modsm.string				= "MODS";
	networkOptionsInfo.modsm.color				= color_red;
	networkOptionsInfo.modsm.style				= UI_CENTER | UI_DROPSHADOW;

	networkOptionsInfo.exitm.generic.type		= MTYPE_PTEXT;
	networkOptionsInfo.exitm.generic.flags  	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	networkOptionsInfo.exitm.generic.x			= 590;
	networkOptionsInfo.exitm.generic.y			= 3;
	networkOptionsInfo.exitm.string				= "EXIT";
	networkOptionsInfo.exitm.color				= color_red;
	networkOptionsInfo.exitm.style				= UI_CENTER | UI_DROPSHADOW;
*/
	//Elder: Info for system icon
	networkOptionsInfo.rq3_systemicon.generic.type				= MTYPE_BITMAP;
	networkOptionsInfo.rq3_systemicon.generic.name				= RQ3_SYSTEM_ICON;
	networkOptionsInfo.rq3_systemicon.generic.flags				= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	networkOptionsInfo.rq3_systemicon.generic.x					= 0;
	networkOptionsInfo.rq3_systemicon.generic.y					= 4;
	networkOptionsInfo.rq3_systemicon.width						= RQ3_ICON_WIDTH;
	networkOptionsInfo.rq3_systemicon.height					= RQ3_ICON_HEIGHT;

	//Elder: Info for setup title
	networkOptionsInfo.rq3_setuptitle.generic.type				= MTYPE_BITMAP;
	networkOptionsInfo.rq3_setuptitle.generic.name				= RQ3_SETUP_TITLE;
	networkOptionsInfo.rq3_setuptitle.generic.flags				= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	networkOptionsInfo.rq3_setuptitle.generic.x					= 64;
	networkOptionsInfo.rq3_setuptitle.generic.y					= 12;
	networkOptionsInfo.rq3_setuptitle.width						= 256;
	networkOptionsInfo.rq3_setuptitle.height					= 32;

	//Elder: Info for rate_input text field
	networkOptionsInfo.rate_input.generic.type			= MTYPE_FIELD;
	networkOptionsInfo.rate_input.generic.name			= "Data Rate (BPS):";
	networkOptionsInfo.rate_input.generic.flags			= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_NUMBERSONLY|QMF_SMALLFONT;
	networkOptionsInfo.rate_input.field.widthInChars	= MAX_RATE_INPUT;
	networkOptionsInfo.rate_input.field.maxchars		= MAX_RATE_INPUT;
	networkOptionsInfo.rate_input.generic.x				= 200;
	networkOptionsInfo.rate_input.generic.y				= 64;
	networkOptionsInfo.rate_input.generic.callback		= UI_NetworkOptionsMenu_Event;
	networkOptionsInfo.rate_input.generic.id			= ID_RATE2;

	// Elder: removed for type-in
	//y = 240 - 1 * (BIGCHAR_HEIGHT+2);
	/*
	networkOptionsInfo.rate.generic.type		= MTYPE_SPINCONTROL;
	networkOptionsInfo.rate.generic.name		= "Data Rate (BPS):";
	networkOptionsInfo.rate.generic.flags		= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	networkOptionsInfo.rate.generic.callback	= UI_NetworkOptionsMenu_Event;
	networkOptionsInfo.rate.generic.id			= ID_RATE;
	networkOptionsInfo.rate.generic.x			= 200; //Elder: hmm- doesn't correspond to virtual coordinates?
	networkOptionsInfo.rate.generic.y			= 64;
	networkOptionsInfo.rate.itemnames			= rate_items;
	*/

	//Elder: RQ3 Graphics Button
	networkOptionsInfo.rq3_graphics.generic.type		= MTYPE_BITMAP;
	networkOptionsInfo.rq3_graphics.generic.name		= RQ3_GRAPHICS_BUTTON;
	networkOptionsInfo.rq3_graphics.generic.flags		= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	networkOptionsInfo.rq3_graphics.generic.x			= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	networkOptionsInfo.rq3_graphics.generic.y			= y;
	networkOptionsInfo.rq3_graphics.generic.id			= ID_GRAPHICS;
	networkOptionsInfo.rq3_graphics.generic.callback	= UI_NetworkOptionsMenu_Event;
	networkOptionsInfo.rq3_graphics.width				= RQ3_BUTTON_WIDTH;
	networkOptionsInfo.rq3_graphics.height				= RQ3_BUTTON_HEIGHT;
	networkOptionsInfo.rq3_graphics.focuspic			= RQ3_FOCUS_BUTTON;
	
	//Elder: RQ3 Display Button
	networkOptionsInfo.rq3_display.generic.type			= MTYPE_BITMAP;
	networkOptionsInfo.rq3_display.generic.name			= RQ3_DISPLAY_BUTTON;
	networkOptionsInfo.rq3_display.generic.flags		= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	networkOptionsInfo.rq3_display.generic.x			= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	networkOptionsInfo.rq3_display.generic.y			= y;
	networkOptionsInfo.rq3_display.generic.id			= ID_DISPLAY;
	networkOptionsInfo.rq3_display.generic.callback		= UI_NetworkOptionsMenu_Event;
	networkOptionsInfo.rq3_display.width				= RQ3_BUTTON_WIDTH;
	networkOptionsInfo.rq3_display.height				= RQ3_BUTTON_HEIGHT;
	networkOptionsInfo.rq3_display.focuspic				= RQ3_FOCUS_BUTTON;

	//Elder: RQ3 Sound Button
	networkOptionsInfo.rq3_sound.generic.type			= MTYPE_BITMAP;
	networkOptionsInfo.rq3_sound.generic.name			= RQ3_SOUND_BUTTON;
	networkOptionsInfo.rq3_sound.generic.flags			= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	networkOptionsInfo.rq3_sound.generic.x				= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	networkOptionsInfo.rq3_sound.generic.y				= y;
	networkOptionsInfo.rq3_sound.generic.id				= ID_SOUND;
	networkOptionsInfo.rq3_sound.generic.callback		= UI_NetworkOptionsMenu_Event;
	networkOptionsInfo.rq3_sound.width					= RQ3_BUTTON_WIDTH;
	networkOptionsInfo.rq3_sound.height					= RQ3_BUTTON_HEIGHT;
	networkOptionsInfo.rq3_sound.focuspic				= RQ3_FOCUS_BUTTON;

	//Elder: RQ3 Network Button
	networkOptionsInfo.rq3_network.generic.type			= MTYPE_BITMAP;
	networkOptionsInfo.rq3_network.generic.name			= RQ3_NETWORK_BUTTON;
	networkOptionsInfo.rq3_network.generic.flags		= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	networkOptionsInfo.rq3_network.generic.x			= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	networkOptionsInfo.rq3_network.generic.y			= y;
	networkOptionsInfo.rq3_network.generic.id			= ID_NETWORK;
	networkOptionsInfo.rq3_network.generic.callback		= UI_NetworkOptionsMenu_Event;
	networkOptionsInfo.rq3_network.width				= RQ3_BUTTON_WIDTH;
	networkOptionsInfo.rq3_network.height				= RQ3_BUTTON_HEIGHT;
	networkOptionsInfo.rq3_network.focuspic				= RQ3_FOCUS_BUTTON;

	//Elder: RQ3 Status Text
	networkOptionsInfo.rq3_statustext.generic.type 		= MTYPE_TEXT;
	networkOptionsInfo.rq3_statustext.generic.flags		= QMF_CENTER_JUSTIFY;
	networkOptionsInfo.rq3_statustext.generic.x 		= RQ3_STATUSBAR_X;
	networkOptionsInfo.rq3_statustext.generic.y 		= RQ3_STATUSBAR_Y;
	networkOptionsInfo.rq3_statustext.string 			= "";
	networkOptionsInfo.rq3_statustext.style 			= UI_CENTER|UI_SMALLFONT;
	networkOptionsInfo.rq3_statustext.color 			= color_orange;

	/* Elder: replaced by RQ3 buttons
	networkOptionsInfo.graphics.generic.type		= MTYPE_PTEXT;
	networkOptionsInfo.graphics.generic.flags		= QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	networkOptionsInfo.graphics.generic.id			= ID_GRAPHICS;
	networkOptionsInfo.graphics.generic.callback	= UI_NetworkOptionsMenu_Event;
	networkOptionsInfo.graphics.generic.x			= 216;
	networkOptionsInfo.graphics.generic.y			= 240 - 2 * PROP_HEIGHT;
	networkOptionsInfo.graphics.string				= "GRAPHICS";
	networkOptionsInfo.graphics.style				= UI_RIGHT;
	networkOptionsInfo.graphics.color				= color_red;
	

	networkOptionsInfo.display.generic.type			= MTYPE_PTEXT;
	networkOptionsInfo.display.generic.flags		= QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	networkOptionsInfo.display.generic.id			= ID_DISPLAY;
	networkOptionsInfo.display.generic.callback		= UI_NetworkOptionsMenu_Event;
	networkOptionsInfo.display.generic.x			= 216;
	networkOptionsInfo.display.generic.y			= 240 - PROP_HEIGHT;
	networkOptionsInfo.display.string				= "DISPLAY";
	networkOptionsInfo.display.style				= UI_RIGHT;
	networkOptionsInfo.display.color				= color_red;

	networkOptionsInfo.sound.generic.type			= MTYPE_PTEXT;
	networkOptionsInfo.sound.generic.flags			= QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	networkOptionsInfo.sound.generic.id				= ID_SOUND;
	networkOptionsInfo.sound.generic.callback		= UI_NetworkOptionsMenu_Event;
	networkOptionsInfo.sound.generic.x				= 216;
	networkOptionsInfo.sound.generic.y				= 240;
	networkOptionsInfo.sound.string					= "SOUND";
	networkOptionsInfo.sound.style					= UI_RIGHT;
	networkOptionsInfo.sound.color					= color_red;

	networkOptionsInfo.network.generic.type			= MTYPE_PTEXT;
	networkOptionsInfo.network.generic.flags		= QMF_RIGHT_JUSTIFY;
	networkOptionsInfo.network.generic.id			= ID_NETWORK;
	networkOptionsInfo.network.generic.callback		= UI_NetworkOptionsMenu_Event;
	networkOptionsInfo.network.generic.x			= 216;
	networkOptionsInfo.network.generic.y			= 240 + PROP_HEIGHT;
	networkOptionsInfo.network.string				= "NETWORK";
	networkOptionsInfo.network.style				= UI_RIGHT;
	networkOptionsInfo.network.color				= color_red;
	*/
	
	networkOptionsInfo.back.generic.type		= MTYPE_BITMAP;
	networkOptionsInfo.back.generic.name		= ART_BACK0;
	networkOptionsInfo.back.generic.flags		= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	networkOptionsInfo.back.generic.callback	= UI_NetworkOptionsMenu_Event;
	networkOptionsInfo.back.generic.id			= ID_BACK;
	networkOptionsInfo.back.generic.x			= 8;
	networkOptionsInfo.back.generic.y			= 480-44;
	networkOptionsInfo.back.width				= 32;
	networkOptionsInfo.back.height				= 32;
	networkOptionsInfo.back.focuspic			= ART_BACK1;

//Elder: removed
//	Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.banner );
//	Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.framel );
//	Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.framer );
//	Menu_AddItem( &networkOptionsInfo.menu, &networkOptionsInfo.multim );
//	Menu_AddItem( &networkOptionsInfo.menu, &networkOptionsInfo.setupm );
//	Menu_AddItem( &networkOptionsInfo.menu, &networkOptionsInfo.demom );
//	Menu_AddItem( &networkOptionsInfo.menu, &networkOptionsInfo.modsm );
//	Menu_AddItem( &networkOptionsInfo.menu, &networkOptionsInfo.exitm );

	//Elder: added
	Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.rq3_systemicon );
	Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.rq3_setuptitle );
	Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.rq3_graphics );
	Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.rq3_display );
	Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.rq3_sound );
	Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.rq3_network );
	Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.rate_input );
	Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.rq3_statustext );
	//Elder: Removed for RQ3 stuff
	//Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.graphics );
	//Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.display );
	//Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.sound );
	//Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.network );
	//Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.rate );
	Menu_AddItem( &networkOptionsInfo.menu, ( void * ) &networkOptionsInfo.back );

	//Elder: copy cvar value into field buffer
	Q_strncpyz( networkOptionsInfo.rate_input.field.buffer, UI_Cvar_VariableString("rate"), sizeof(networkOptionsInfo.rate_input.field.buffer) );
	
	/*Elder: not needed anymore
	if( rate <= 2500 ) {
		networkOptionsInfo.rate.curvalue = 0;
	}
	else if( rate <= 3000 ) {
		networkOptionsInfo.rate.curvalue = 1;
	}
	else if( rate <= 4000 ) {
		networkOptionsInfo.rate.curvalue = 2;
	}
	else if( rate <= 5000 ) {
		networkOptionsInfo.rate.curvalue = 3;
	}
	else if( rate <= 8000 ) {
		networkOptionsInfo.rate.curvalue = 4;
	}
	else if( rate <= 10000 ) {
		networkOptionsInfo.rate.curvalue = 5;
	}
	else {
		networkOptionsInfo.rate.curvalue = 6;
	}
	*/
}


/*
===============
UI_NetworkOptionsMenu_Cache
===============
*/
void UI_NetworkOptionsMenu_Cache( void ) {
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

// name
//static void Network_SetMenuItems( void ) {
//Q_strncpyz( s_playersettings.name.field.buffer, UI_Cvar_VariableString("name"), sizeof(s_playersettings.name.field.buffer) );

/*
===============
UI_NetworkOptionsMenu
===============
*/
void UI_NetworkOptionsMenu( void ) {
	UI_NetworkOptionsMenu_Init();
	UI_PushMenu( &networkOptionsInfo.menu );
	//Elder: shifted to .rq3_network instead of .network
	Menu_SetCursorToItem( &networkOptionsInfo.menu, &networkOptionsInfo.rq3_network );
}
