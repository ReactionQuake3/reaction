// Copyright (C) 1999-2000 Id Software, Inc.
//
/*
=======================================================================

SOUND OPTIONS MENU

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
#define ID_EFFECTSVOLUME	14
#define ID_MUSICVOLUME		15
#define ID_QUALITY			16
//#define ID_A3D				17
#define ID_BACK				18

//Elder: RQ3 stuff
#define RQ3_SYSTEM_ICON		"menu/art/rq3-setup-system.jpg"
#define RQ3_SETUP_TITLE		"menu/art/rq3-title-setup.tga"
#define RQ3_FOCUS_BUTTON	"menu/art/rq3-menu-focus.tga"
#define RQ3_GRAPHICS_BUTTON	"menu/art/rq3-system-graphics.tga"
#define RQ3_DISPLAY_BUTTON	"menu/art/rq3-system-display.tga"
#define RQ3_SOUND_BUTTON	"menu/art/rq3-system-sound.tga"
#define RQ3_NETWORK_BUTTON	"menu/art/rq3-system-network.tga"


static const char *quality_items[] = {
	"Low", "High", 0
};

typedef struct {
	menuframework_s		menu;

//	menutext_s			banner;
//	menubitmap_s		framel;
//	menubitmap_s		framer;
//Elder: not needed anymore
//	menutext_s			multim;
//	menutext_s			setupm;
//	menutext_s			demom;
//	menutext_s			modsm;
//	menutext_s			exitm;
//Elder: replaced by RQ3 buttons
//	menutext_s			graphics;
//	menutext_s			display;
//	menutext_s			sound;
//	menutext_s			network;

	menubitmap_s	rq3_setuptitle;
	menubitmap_s	rq3_systemicon;
	menubitmap_s	rq3_graphics;
	menubitmap_s	rq3_display;
	menubitmap_s	rq3_sound;
	menubitmap_s	rq3_network;
	menutext_s		rq3_statustext;

	menuslider_s		sfxvolume;
	menuslider_s		musicvolume;
	menulist_s			quality;
//	menuradiobutton_s	a3d;

	menubitmap_s		back;
} soundOptionsInfo_t;

static soundOptionsInfo_t	soundOptionsInfo;


/*
=================
UI_SoundOptionsMenu_Event
=================
*/
static void UI_SoundOptionsMenu_Event( void* ptr, int event ) {
	//Elder: for status bar
	if( event == QM_LOSTFOCUS ) {
		soundOptionsInfo.rq3_statustext.string = "";
		return;
	}
	else if ( event == QM_GOTFOCUS ) {
		switch( ((menucommon_s*)ptr)->id ) {
		case ID_GRAPHICS:
			soundOptionsInfo.rq3_statustext.string = "Change graphics settings";
			break;

		case ID_DISPLAY:
			soundOptionsInfo.rq3_statustext.string = "Change display settings";
			break;

		case ID_SOUND:
			soundOptionsInfo.rq3_statustext.string = "Change sound settings";
			break;
	
		case ID_NETWORK:
			soundOptionsInfo.rq3_statustext.string = "Change network settings";
			break;
		
		case ID_BACK:
			soundOptionsInfo.rq3_statustext.string = "Return to setup menu";
			break;
		
		case ID_QUALITY:
			//Q_strcat UI_Cvar_VariableString("s_khz")
			//Get khz value and compression value
			//Concatenate into one string with "Current settings: "
			//output to rq3_statustext.string
			//soundOptionsInfo.rq3_statustext.string =
			break;
		
		default:
			soundOptionsInfo.rq3_statustext.string = "";
			break;
		}
	}
	else if ( event == QM_ACTIVATED ) {
		switch( ((menucommon_s*)ptr)->id ) {
		case ID_GRAPHICS:
			UI_PopMenu();
			UI_GraphicsOptionsMenu();
			break;

		case ID_DISPLAY:
			UI_PopMenu();
			UI_DisplayOptionsMenu();
			break;

		case ID_SOUND:
			break;

		case ID_NETWORK:
			UI_PopMenu();
			UI_NetworkOptionsMenu();
			break;

		case ID_EFFECTSVOLUME:
			trap_Cvar_SetValue( "s_volume", soundOptionsInfo.sfxvolume.curvalue / 10 );
			break;

		case ID_MUSICVOLUME:
			trap_Cvar_SetValue( "s_musicvolume", soundOptionsInfo.musicvolume.curvalue / 10 );
			break;

		case ID_QUALITY:
			if( soundOptionsInfo.quality.curvalue ) {
				trap_Cvar_SetValue( "s_khz", 22 );
				trap_Cvar_SetValue( "s_compression", 0 );
			}
			else {
				trap_Cvar_SetValue( "s_khz", 11 );
				trap_Cvar_SetValue( "s_compression", 1 );
			}
			UI_ForceMenuOff();
			trap_Cmd_ExecuteText( EXEC_APPEND, "snd_restart\n" );
			break;
	/*
		case ID_A3D:
			if( soundOptionsInfo.a3d.curvalue ) {
				trap_Cmd_ExecuteText( EXEC_NOW, "s_enable_a3d\n" );
			}
			else {
				trap_Cmd_ExecuteText( EXEC_NOW, "s_disable_a3d\n" );
			}
			soundOptionsInfo.a3d.curvalue = (int)trap_Cvar_VariableValue( "s_usingA3D" );
			break;
	*/
		case ID_BACK:
			UI_PopMenu();
			break;
		}
	}
}
/*
===============
Added by Elder
UI_SoundOptionsMenu_Draw
===============
*/
static void UI_SoundOptionsMenu_Draw( void ) {
	//Elder: "Dim" and "Letterbox" mask
	UI_FillRect( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color_deepdim );
	UI_FillRect( 0, 0, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 54, color_black);
		
	// standard menu drawing
	Menu_Draw( &soundOptionsInfo.menu );
}


/*
===============
UI_SoundOptionsMenu_Init
===============
*/
static void UI_SoundOptionsMenu_Init( void ) {
	int		y = 12;
	int		buttonCount = 0;

	memset( &soundOptionsInfo, 0, sizeof(soundOptionsInfo) );

	UI_SoundOptionsMenu_Cache();
	//Elder: added draw function
	soundOptionsInfo.menu.draw		 = UI_SoundOptionsMenu_Draw;
	soundOptionsInfo.menu.wrapAround = qtrue;
	soundOptionsInfo.menu.fullscreen = qtrue;
	soundOptionsInfo.menu.showlogo   = qtrue;

/*	soundOptionsInfo.banner.generic.type		= MTYPE_BTEXT;
	soundOptionsInfo.banner.generic.flags		= QMF_CENTER_JUSTIFY;
	soundOptionsInfo.banner.generic.x			= 320;
	soundOptionsInfo.banner.generic.y			= 16;
	soundOptionsInfo.banner.string				= "SYSTEM SETUP";
	soundOptionsInfo.banner.color				= color_white;
	soundOptionsInfo.banner.style				= UI_CENTER;

	soundOptionsInfo.framel.generic.type		= MTYPE_BITMAP;
	soundOptionsInfo.framel.generic.name		= ART_FRAMEL;
	soundOptionsInfo.framel.generic.flags		= QMF_INACTIVE;
	soundOptionsInfo.framel.generic.x			= 0;  
	soundOptionsInfo.framel.generic.y			= 78;
	soundOptionsInfo.framel.width				= 256;
	soundOptionsInfo.framel.height				= 329;

	soundOptionsInfo.framer.generic.type		= MTYPE_BITMAP;
	soundOptionsInfo.framer.generic.name		= ART_FRAMER;
	soundOptionsInfo.framer.generic.flags		= QMF_INACTIVE;
	soundOptionsInfo.framer.generic.x			= 376;
	soundOptionsInfo.framer.generic.y			= 76;
	soundOptionsInfo.framer.width				= 256;
	soundOptionsInfo.framer.height				= 334;
*/
/* Elder: not needed anymore
	soundOptionsInfo.multim.generic.type	= MTYPE_PTEXT;
	soundOptionsInfo.multim.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	soundOptionsInfo.multim.generic.x		= 120;
	soundOptionsInfo.multim.generic.y		= 3;
	soundOptionsInfo.multim.string			= "MULTIPLAYER";
	soundOptionsInfo.multim.color			= color_red;
	soundOptionsInfo.multim.style			= UI_CENTER | UI_DROPSHADOW;

	soundOptionsInfo.setupm.generic.type	= MTYPE_PTEXT;
	soundOptionsInfo.setupm.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_INACTIVE|QMF_HIGHLIGHT;
	soundOptionsInfo.setupm.generic.x		= 280;
	soundOptionsInfo.setupm.generic.y		= 3;
	soundOptionsInfo.setupm.string			= "SETUP";
	soundOptionsInfo.setupm.color			= color_red;
	soundOptionsInfo.setupm.style			= UI_CENTER | UI_DROPSHADOW;

	soundOptionsInfo.demom.generic.type		= MTYPE_PTEXT;
	soundOptionsInfo.demom.generic.flags	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	soundOptionsInfo.demom.generic.x		= 390;
	soundOptionsInfo.demom.generic.y		= 3;
	soundOptionsInfo.demom.string			= "DEMOS";
	soundOptionsInfo.demom.color			= color_red;
	soundOptionsInfo.demom.style			= UI_CENTER | UI_DROPSHADOW;

	soundOptionsInfo.modsm.generic.type		= MTYPE_PTEXT;
	soundOptionsInfo.modsm.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	soundOptionsInfo.modsm.generic.x		= 500;
	soundOptionsInfo.modsm.generic.y		= 3;
	soundOptionsInfo.modsm.string			= "MODS";
	soundOptionsInfo.modsm.color			= color_red;
	soundOptionsInfo.modsm.style			= UI_CENTER | UI_DROPSHADOW;

	soundOptionsInfo.exitm.generic.type		= MTYPE_PTEXT;
	soundOptionsInfo.exitm.generic.flags  	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	soundOptionsInfo.exitm.generic.x		= 590;
	soundOptionsInfo.exitm.generic.y		= 3;
	soundOptionsInfo.exitm.string			= "EXIT";
	soundOptionsInfo.exitm.color			= color_red;
	soundOptionsInfo.exitm.style			= UI_CENTER | UI_DROPSHADOW;
*/

	//Elder: Info for system icon
	soundOptionsInfo.rq3_systemicon.generic.type				= MTYPE_BITMAP;
	soundOptionsInfo.rq3_systemicon.generic.name				= RQ3_SYSTEM_ICON;
	soundOptionsInfo.rq3_systemicon.generic.flags				= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	soundOptionsInfo.rq3_systemicon.generic.x					= 0;
	soundOptionsInfo.rq3_systemicon.generic.y					= 4;
	soundOptionsInfo.rq3_systemicon.width						= RQ3_ICON_WIDTH;
	soundOptionsInfo.rq3_systemicon.height						= RQ3_ICON_HEIGHT;

	//Elder: Info for setup title
	soundOptionsInfo.rq3_setuptitle.generic.type				= MTYPE_BITMAP;
	soundOptionsInfo.rq3_setuptitle.generic.name				= RQ3_SETUP_TITLE;
	soundOptionsInfo.rq3_setuptitle.generic.flags				= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	soundOptionsInfo.rq3_setuptitle.generic.x					= 64;
	soundOptionsInfo.rq3_setuptitle.generic.y					= 12;
	soundOptionsInfo.rq3_setuptitle.width						= 256;
	soundOptionsInfo.rq3_setuptitle.height						= 32;

//Elder: RQ3 Graphics Button
	soundOptionsInfo.rq3_graphics.generic.type		= MTYPE_BITMAP;
	soundOptionsInfo.rq3_graphics.generic.name		= RQ3_GRAPHICS_BUTTON;
	soundOptionsInfo.rq3_graphics.generic.flags		= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	soundOptionsInfo.rq3_graphics.generic.x			= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	soundOptionsInfo.rq3_graphics.generic.y			= y;
	soundOptionsInfo.rq3_graphics.generic.id		= ID_GRAPHICS;
	soundOptionsInfo.rq3_graphics.generic.callback	= UI_SoundOptionsMenu_Event;
	soundOptionsInfo.rq3_graphics.width				= RQ3_BUTTON_WIDTH;
	soundOptionsInfo.rq3_graphics.height			= RQ3_BUTTON_HEIGHT;
	soundOptionsInfo.rq3_graphics.focuspic			= RQ3_FOCUS_BUTTON;
	
	//Elder: RQ3 Display Button
	soundOptionsInfo.rq3_display.generic.type		= MTYPE_BITMAP;
	soundOptionsInfo.rq3_display.generic.name		= RQ3_DISPLAY_BUTTON;
	soundOptionsInfo.rq3_display.generic.flags		= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	soundOptionsInfo.rq3_display.generic.x			= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	soundOptionsInfo.rq3_display.generic.y			= y;
	soundOptionsInfo.rq3_display.generic.id			= ID_DISPLAY;
	soundOptionsInfo.rq3_display.generic.callback	= UI_SoundOptionsMenu_Event;
	soundOptionsInfo.rq3_display.width				= RQ3_BUTTON_WIDTH;
	soundOptionsInfo.rq3_display.height				= RQ3_BUTTON_HEIGHT;
	soundOptionsInfo.rq3_display.focuspic			= RQ3_FOCUS_BUTTON;

	//Elder: RQ3 Sound Button
	soundOptionsInfo.rq3_sound.generic.type			= MTYPE_BITMAP;
	soundOptionsInfo.rq3_sound.generic.name			= RQ3_SOUND_BUTTON;
	soundOptionsInfo.rq3_sound.generic.flags		= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	soundOptionsInfo.rq3_sound.generic.x			= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	soundOptionsInfo.rq3_sound.generic.y			= y;
	soundOptionsInfo.rq3_sound.generic.id			= ID_SOUND;
	soundOptionsInfo.rq3_sound.generic.callback		= UI_SoundOptionsMenu_Event;
	soundOptionsInfo.rq3_sound.width				= RQ3_BUTTON_WIDTH;
	soundOptionsInfo.rq3_sound.height				= RQ3_BUTTON_HEIGHT;
	soundOptionsInfo.rq3_sound.focuspic				= RQ3_FOCUS_BUTTON;

	//Elder: RQ3 Network Button
	soundOptionsInfo.rq3_network.generic.type		= MTYPE_BITMAP;
	soundOptionsInfo.rq3_network.generic.name		= RQ3_NETWORK_BUTTON;
	soundOptionsInfo.rq3_network.generic.flags		= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	soundOptionsInfo.rq3_network.generic.x			= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	soundOptionsInfo.rq3_network.generic.y			= y;
	soundOptionsInfo.rq3_network.generic.id			= ID_NETWORK;
	soundOptionsInfo.rq3_network.generic.callback	= UI_SoundOptionsMenu_Event;
	soundOptionsInfo.rq3_network.width				= RQ3_BUTTON_WIDTH;
	soundOptionsInfo.rq3_network.height				= RQ3_BUTTON_HEIGHT;
	soundOptionsInfo.rq3_network.focuspic			= RQ3_FOCUS_BUTTON;

	//Elder: RQ3 Status Text
	soundOptionsInfo.rq3_statustext.generic.type 	= MTYPE_TEXT;
	soundOptionsInfo.rq3_statustext.generic.flags	= QMF_CENTER_JUSTIFY;
	soundOptionsInfo.rq3_statustext.generic.x 		= RQ3_STATUSBAR_X;
	soundOptionsInfo.rq3_statustext.generic.y 		= RQ3_STATUSBAR_Y;
	soundOptionsInfo.rq3_statustext.string 			= "";
	soundOptionsInfo.rq3_statustext.style 			= UI_CENTER|UI_SMALLFONT;
	soundOptionsInfo.rq3_statustext.color 			= color_orange;

/* Elder: replaced by RQ3 buttons
	soundOptionsInfo.graphics.generic.type		= MTYPE_PTEXT;
	soundOptionsInfo.graphics.generic.flags		= QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	soundOptionsInfo.graphics.generic.id		= ID_GRAPHICS;
	soundOptionsInfo.graphics.generic.callback	= UI_SoundOptionsMenu_Event;
	soundOptionsInfo.graphics.generic.x			= 216;
	soundOptionsInfo.graphics.generic.y			= 240 - 2 * PROP_HEIGHT;
	soundOptionsInfo.graphics.string			= "GRAPHICS";
	soundOptionsInfo.graphics.style				= UI_RIGHT;
	soundOptionsInfo.graphics.color				= color_red;

	soundOptionsInfo.display.generic.type		= MTYPE_PTEXT;
	soundOptionsInfo.display.generic.flags		= QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	soundOptionsInfo.display.generic.id			= ID_DISPLAY;
	soundOptionsInfo.display.generic.callback	= UI_SoundOptionsMenu_Event;
	soundOptionsInfo.display.generic.x			= 216;
	soundOptionsInfo.display.generic.y			= 240 - PROP_HEIGHT;
	soundOptionsInfo.display.string				= "DISPLAY";
	soundOptionsInfo.display.style				= UI_RIGHT;
	soundOptionsInfo.display.color				= color_red;

	soundOptionsInfo.sound.generic.type			= MTYPE_PTEXT;
	soundOptionsInfo.sound.generic.flags		= QMF_RIGHT_JUSTIFY;
	soundOptionsInfo.sound.generic.id			= ID_SOUND;
	soundOptionsInfo.sound.generic.callback		= UI_SoundOptionsMenu_Event;
	soundOptionsInfo.sound.generic.x			= 216;
	soundOptionsInfo.sound.generic.y			= 240;
	soundOptionsInfo.sound.string				= "SOUND";
	soundOptionsInfo.sound.style				= UI_RIGHT;
	soundOptionsInfo.sound.color				= color_red;

	soundOptionsInfo.network.generic.type		= MTYPE_PTEXT;
	soundOptionsInfo.network.generic.flags		= QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	soundOptionsInfo.network.generic.id			= ID_NETWORK;
	soundOptionsInfo.network.generic.callback	= UI_SoundOptionsMenu_Event;
	soundOptionsInfo.network.generic.x			= 216;
	soundOptionsInfo.network.generic.y			= 240 + PROP_HEIGHT;
	soundOptionsInfo.network.string				= "NETWORK";
	soundOptionsInfo.network.style				= UI_RIGHT;
	soundOptionsInfo.network.color				= color_red;
*/

//	y = 240 - 1.5 * (BIGCHAR_HEIGHT + 2);
	soundOptionsInfo.sfxvolume.generic.type		= MTYPE_SLIDER;
	soundOptionsInfo.sfxvolume.generic.name		= "Effects Volume:";
	soundOptionsInfo.sfxvolume.generic.flags	= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	soundOptionsInfo.sfxvolume.generic.callback	= UI_SoundOptionsMenu_Event;
	soundOptionsInfo.sfxvolume.generic.id		= ID_EFFECTSVOLUME;
	soundOptionsInfo.sfxvolume.generic.x		= 200;
	soundOptionsInfo.sfxvolume.generic.y		= 64;
	soundOptionsInfo.sfxvolume.minvalue			= 0;
	soundOptionsInfo.sfxvolume.maxvalue			= 10;

//	y += BIGCHAR_HEIGHT+2;
	soundOptionsInfo.musicvolume.generic.type		= MTYPE_SLIDER;
	soundOptionsInfo.musicvolume.generic.name		= "Music Volume:";
	soundOptionsInfo.musicvolume.generic.flags		= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	soundOptionsInfo.musicvolume.generic.callback	= UI_SoundOptionsMenu_Event;
	soundOptionsInfo.musicvolume.generic.id			= ID_MUSICVOLUME;
	soundOptionsInfo.musicvolume.generic.x			= 200;
	soundOptionsInfo.musicvolume.generic.y			= 64 + BIGCHAR_HEIGHT + 2;
	soundOptionsInfo.musicvolume.minvalue			= 0;
	soundOptionsInfo.musicvolume.maxvalue			= 10;

//	y += BIGCHAR_HEIGHT+2;
	soundOptionsInfo.quality.generic.type		= MTYPE_SPINCONTROL;
	soundOptionsInfo.quality.generic.name		= "Sound Quality:";
	soundOptionsInfo.quality.generic.flags		= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	soundOptionsInfo.quality.generic.callback	= UI_SoundOptionsMenu_Event;
	soundOptionsInfo.quality.generic.id			= ID_QUALITY;
	soundOptionsInfo.quality.generic.x			= 200;
	soundOptionsInfo.quality.generic.y			= 64 + (BIGCHAR_HEIGHT + 2) * 2;
	soundOptionsInfo.quality.itemnames			= quality_items;
/*
	y += BIGCHAR_HEIGHT+2;
	soundOptionsInfo.a3d.generic.type			= MTYPE_RADIOBUTTON;
	soundOptionsInfo.a3d.generic.name			= "A3D:";
	soundOptionsInfo.a3d.generic.flags			= QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	soundOptionsInfo.a3d.generic.callback		= UI_SoundOptionsMenu_Event;
	soundOptionsInfo.a3d.generic.id				= ID_A3D;
	soundOptionsInfo.a3d.generic.x				= 400;
	soundOptionsInfo.a3d.generic.y				= y;
*/
	soundOptionsInfo.back.generic.type			= MTYPE_BITMAP;
	soundOptionsInfo.back.generic.name			= ART_BACK0;
	soundOptionsInfo.back.generic.flags			= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	soundOptionsInfo.back.generic.callback		= UI_SoundOptionsMenu_Event;
	soundOptionsInfo.back.generic.id			= ID_BACK;
	soundOptionsInfo.back.generic.x				= 8;
	soundOptionsInfo.back.generic.y				= 480-44;
	soundOptionsInfo.back.width					= 32;
	soundOptionsInfo.back.height				= 32;
	soundOptionsInfo.back.focuspic				= ART_BACK1;

//	Menu_AddItem( &soundOptionsInfo.menu, ( void * ) &soundOptionsInfo.banner );
//	Menu_AddItem( &soundOptionsInfo.menu, ( void * ) &soundOptionsInfo.framel );
//	Menu_AddItem( &soundOptionsInfo.menu, ( void * ) &soundOptionsInfo.framer );
//Elder: not needed anymore
//	Menu_AddItem( &soundOptionsInfo.menu, &soundOptionsInfo.multim );
//	Menu_AddItem( &soundOptionsInfo.menu, &soundOptionsInfo.setupm );
//	Menu_AddItem( &soundOptionsInfo.menu, &soundOptionsInfo.demom );
//	Menu_AddItem( &soundOptionsInfo.menu, &soundOptionsInfo.modsm );
//	Menu_AddItem( &soundOptionsInfo.menu, &soundOptionsInfo.exitm );
//	Menu_AddItem( &soundOptionsInfo.menu, ( void * ) &soundOptionsInfo.graphics );
//	Menu_AddItem( &soundOptionsInfo.menu, ( void * ) &soundOptionsInfo.display );
//	Menu_AddItem( &soundOptionsInfo.menu, ( void * ) &soundOptionsInfo.sound );
//	Menu_AddItem( &soundOptionsInfo.menu, ( void * ) &soundOptionsInfo.network );

	Menu_AddItem( &soundOptionsInfo.menu, ( void * ) &soundOptionsInfo.rq3_systemicon );
	Menu_AddItem( &soundOptionsInfo.menu, ( void * ) &soundOptionsInfo.rq3_setuptitle );
	Menu_AddItem( &soundOptionsInfo.menu, ( void * ) &soundOptionsInfo.rq3_graphics );
	Menu_AddItem( &soundOptionsInfo.menu, ( void * ) &soundOptionsInfo.rq3_display );
	Menu_AddItem( &soundOptionsInfo.menu, ( void * ) &soundOptionsInfo.rq3_sound );
	Menu_AddItem( &soundOptionsInfo.menu, ( void * ) &soundOptionsInfo.rq3_network );
	Menu_AddItem( &soundOptionsInfo.menu, ( void * ) &soundOptionsInfo.rq3_statustext );
	
	Menu_AddItem( &soundOptionsInfo.menu, ( void * ) &soundOptionsInfo.sfxvolume );
	Menu_AddItem( &soundOptionsInfo.menu, ( void * ) &soundOptionsInfo.musicvolume );
	Menu_AddItem( &soundOptionsInfo.menu, ( void * ) &soundOptionsInfo.quality );
//	Menu_AddItem( &soundOptionsInfo.menu, ( void * ) &soundOptionsInfo.a3d );
	Menu_AddItem( &soundOptionsInfo.menu, ( void * ) &soundOptionsInfo.back );

	soundOptionsInfo.sfxvolume.curvalue = trap_Cvar_VariableValue( "s_volume" ) * 10;
	soundOptionsInfo.musicvolume.curvalue = trap_Cvar_VariableValue( "s_musicvolume" ) * 10;
	soundOptionsInfo.quality.curvalue = !trap_Cvar_VariableValue( "s_compression" );
//	soundOptionsInfo.a3d.curvalue = (int)trap_Cvar_VariableValue( "s_usingA3D" );
}


/*
===============
UI_SoundOptionsMenu_Cache
===============
*/
void UI_SoundOptionsMenu_Cache( void ) {
	//trap_R_RegisterShaderNoMip( ART_FRAMEL );
	//trap_R_RegisterShaderNoMip( ART_FRAMER );
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
UI_SoundOptionsMenu
===============
*/
void UI_SoundOptionsMenu( void ) {
	UI_SoundOptionsMenu_Init();
	UI_PushMenu( &soundOptionsInfo.menu );
	//Elder: shifted to .rq3_sound instead of .sound
	Menu_SetCursorToItem( &soundOptionsInfo.menu, &soundOptionsInfo.rq3_sound );
}
