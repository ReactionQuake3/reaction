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

CD KEY MENU

=======================================================================
*/


#include "ui_local.h"


//#define ART_FRAME		"menu/art/cut_frame"
//#define ART_ACCEPT0		"menu/art/accept_0"
//#define ART_ACCEPT1		"menu/art/accept_1"	
#define ART_ACCEPT0			"menu/art/rq3-menu-go.tga"
#define ART_ACCEPT1			"menu/art/rq3-menu-go-focus.tga"
#define ART_BACK0		"menu/art/rq3-menu-back.tga"
#define ART_BACK1		"menu/art/rq3-menu-back-focus.tga"	

//Elder: RQ3 Stuff
#define RQ3_SETUP_ICON		"menu/art/rq3-setup-cdkey.jpg"
#define RQ3_SETUP_TITLE		"menu/art/rq3-title-setup.jpg"

#define ID_CDKEY		10
#define ID_ACCEPT		11
#define ID_BACK			12


typedef struct {
	menuframework_s	menu;

//	menutext_s		banner;
//	menubitmap_s	frame;

	menufield_s		cdkey;

	menubitmap_s	accept;
	menubitmap_s	back;
	
	//Elder: RQ3 stuff
	menubitmap_s	rq3_setupicon;
	menubitmap_s	rq3_setuptitle;
	menutext_s		rq3_statustext;
	
} cdkeyMenuInfo_t;

static cdkeyMenuInfo_t	cdkeyMenuInfo;


/*
===============
UI_CDKeyMenu_Event
===============
*/
static void UI_CDKeyMenu_Event( void *ptr, int event ) {
	//Elder: Added status messages on event focus
	if ( event == QM_LOSTFOCUS ) {
		cdkeyMenuInfo.rq3_statustext.string = "";
	}
	else if( event == QM_GOTFOCUS ) {
		//get menu item id
		switch( ((menucommon_s*)ptr)->id ) {

		case ID_ACCEPT:
			cdkeyMenuInfo.rq3_statustext.string = "Accept CD key";
			break;
		
		case ID_BACK:
			cdkeyMenuInfo.rq3_statustext.string = "Return to setup menu";
			break;
		
		default:
			cdkeyMenuInfo.rq3_statustext.string = "";
			break;
		}
	}
	else if ( event == QM_ACTIVATED ) {
    	cdkeyMenuInfo.rq3_statustext.string = "";
    	switch( ((menucommon_s*)ptr)->id ) {
    	case ID_ACCEPT:
    		if( cdkeyMenuInfo.cdkey.field.buffer[0] ) {
    			trap_SetCDKey( cdkeyMenuInfo.cdkey.field.buffer );
    		}
    		UI_PopMenu();
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
UI_Mods_MenuDraw
===============
*/
static void UI_CDKeyMenu_MenuDraw( void ) {
	//Elder: "Dim" and "Letterbox" mask
	UI_FillRect( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color_deepdim );
	UI_FillRect( 0, 0, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 54, SCREEN_WIDTH, 2, color_red);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 2, color_red);
	
	// standard menu drawing
	Menu_Draw( &cdkeyMenuInfo.menu );
}

/*
=================
UI_CDKeyMenu_PreValidateKey
=================
*/
static int UI_CDKeyMenu_PreValidateKey( const char *key ) {
	char	ch;

	if( strlen( key ) != 16 ) {
		return 1;
	}

	while( ( ch = *key++ ) ) {
		switch( ch ) {
		case '2':
		case '3':
		case '7':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'g':
		case 'h':
		case 'j':
		case 'l':
		case 'p':
		case 'r':
		case 's':
		case 't':
		case 'w':
			continue;
		default:
			return -1;
		}
	}

	return 0;
}


/*
=================
UI_CDKeyMenu_DrawKey
=================
*/
static void UI_CDKeyMenu_DrawKey( void *self ) {
	menufield_s		*f;
	qboolean		focus;
	int				style;
	char			c;
	float			*color;
	int				x, y;
	int				val;

	f = (menufield_s *)self;

	focus = (f->generic.parent->cursor == f->generic.menuPosition);

	style = UI_LEFT;
	if( focus ) {
		color = color_yellow;
	}
	else {
		color = color_orange;
	}

	x = 320 - 8 * BIGCHAR_WIDTH;
	y = 240 - BIGCHAR_HEIGHT / 2;
	UI_FillRect( x, y, 16 * BIGCHAR_WIDTH, BIGCHAR_HEIGHT, listbar_color );
	UI_DrawString( x, y, f->field.buffer, style, color );

	// draw cursor if we have focus
	if( focus ) {
		if ( trap_Key_GetOverstrikeMode() ) {
			c = 11;
		} else {
			c = 10;
		}

		style &= ~UI_PULSE;
		style |= UI_BLINK;

		UI_DrawChar( x + f->field.cursor * BIGCHAR_WIDTH, y, c, style, color_white );
	}

	val = UI_CDKeyMenu_PreValidateKey( f->field.buffer );
	if( val == 1 ) {
		UI_DrawProportionalString( 320, 376, "Please enter your CD Key", UI_CENTER|UI_SMALLFONT, color_yellow );
	}
	else if ( val == 0 ) {
		UI_DrawProportionalString( 320, 376, "The CD Key appears to be valid", UI_CENTER|UI_SMALLFONT, color_white );
		//Elder: moved around
		UI_DrawProportionalString( 320, 376 + SMALLCHAR_HEIGHT, "Thank you", UI_CENTER|UI_SMALLFONT, color_white );
	}
	else {
		UI_DrawProportionalString( 320, 376, "The CD Key is not valid", UI_CENTER|UI_SMALLFONT, color_red );
	}
}


/*
===============
UI_CDKeyMenu_Init
===============
*/
static void UI_CDKeyMenu_Init( void ) {
	trap_Cvar_Set( "ui_cdkeychecked", "1" );

	UI_CDKeyMenu_Cache();

	memset( &cdkeyMenuInfo, 0, sizeof(cdkeyMenuInfo) );
	cdkeyMenuInfo.menu.draw		  = UI_CDKeyMenu_MenuDraw;
	cdkeyMenuInfo.menu.wrapAround = qtrue;
	cdkeyMenuInfo.menu.fullscreen = qtrue;
	cdkeyMenuInfo.menu.showlogo   = qtrue;

/*	cdkeyMenuInfo.banner.generic.type				= MTYPE_BTEXT;
	cdkeyMenuInfo.banner.generic.x					= 320;
	cdkeyMenuInfo.banner.generic.y					= 16;
	cdkeyMenuInfo.banner.string						= "CD KEY";
	cdkeyMenuInfo.banner.color						= color_white;
	cdkeyMenuInfo.banner.style						= UI_CENTER;
*/
/*
	cdkeyMenuInfo.frame.generic.type				= MTYPE_BITMAP;
	cdkeyMenuInfo.frame.generic.name				= ART_FRAME;
	cdkeyMenuInfo.frame.generic.flags				= QMF_INACTIVE;
	cdkeyMenuInfo.frame.generic.x					= 142;
	cdkeyMenuInfo.frame.generic.y					= 118;
	cdkeyMenuInfo.frame.width  						= 359;
	cdkeyMenuInfo.frame.height  					= 256;
*/

	//Elder: Info for setup icon
	cdkeyMenuInfo.rq3_setupicon.generic.type				= MTYPE_BITMAP;
	cdkeyMenuInfo.rq3_setupicon.generic.name				= RQ3_SETUP_ICON;
	cdkeyMenuInfo.rq3_setupicon.generic.flags				= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	cdkeyMenuInfo.rq3_setupicon.generic.x					= 0;
	cdkeyMenuInfo.rq3_setupicon.generic.y					= 4;
	cdkeyMenuInfo.rq3_setupicon.width						= RQ3_ICON_WIDTH;
	cdkeyMenuInfo.rq3_setupicon.height						= RQ3_ICON_HEIGHT;

	//Elder: Info for setup title
	cdkeyMenuInfo.rq3_setuptitle.generic.type				= MTYPE_BITMAP;
	cdkeyMenuInfo.rq3_setuptitle.generic.name				= RQ3_SETUP_TITLE;
	cdkeyMenuInfo.rq3_setuptitle.generic.flags				= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	cdkeyMenuInfo.rq3_setuptitle.generic.x					= 64;
	cdkeyMenuInfo.rq3_setuptitle.generic.y					= 12;
	cdkeyMenuInfo.rq3_setuptitle.width						= 256;
	cdkeyMenuInfo.rq3_setuptitle.height						= 32;

	cdkeyMenuInfo.cdkey.generic.type				= MTYPE_FIELD;
	cdkeyMenuInfo.cdkey.generic.name				= "CD Key:";
	cdkeyMenuInfo.cdkey.generic.flags				= QMF_LOWERCASE;
	cdkeyMenuInfo.cdkey.generic.x					= 320 - BIGCHAR_WIDTH * 2.5;
	cdkeyMenuInfo.cdkey.generic.y					= 240 - BIGCHAR_HEIGHT / 2;
	cdkeyMenuInfo.cdkey.field.widthInChars			= 16;
	cdkeyMenuInfo.cdkey.field.maxchars				= 16;
	cdkeyMenuInfo.cdkey.generic.ownerdraw			= UI_CDKeyMenu_DrawKey;

	cdkeyMenuInfo.accept.generic.type				= MTYPE_BITMAP;
	cdkeyMenuInfo.accept.generic.name				= ART_ACCEPT0;
	cdkeyMenuInfo.accept.generic.flags				= QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	cdkeyMenuInfo.accept.generic.id					= ID_ACCEPT;
	cdkeyMenuInfo.accept.generic.callback			= UI_CDKeyMenu_Event;
	cdkeyMenuInfo.accept.generic.x					= 635;
	cdkeyMenuInfo.accept.generic.y					= 480-44;
	cdkeyMenuInfo.accept.width						= 64;
	cdkeyMenuInfo.accept.height						= 32;
	cdkeyMenuInfo.accept.focuspic					= ART_ACCEPT1;

	cdkeyMenuInfo.back.generic.type					= MTYPE_BITMAP;
	cdkeyMenuInfo.back.generic.name					= ART_BACK0;
	cdkeyMenuInfo.back.generic.flags				= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	cdkeyMenuInfo.back.generic.id					= ID_BACK;
	cdkeyMenuInfo.back.generic.callback				= UI_CDKeyMenu_Event;
	cdkeyMenuInfo.back.generic.x					= 8;
	cdkeyMenuInfo.back.generic.y					= 480-44;
	cdkeyMenuInfo.back.width						= 32;
	cdkeyMenuInfo.back.height						= 32;
	cdkeyMenuInfo.back.focuspic						= ART_BACK1;

//	Menu_AddItem( &cdkeyMenuInfo.menu, &cdkeyMenuInfo.banner );
//Elder: removed
//	Menu_AddItem( &cdkeyMenuInfo.menu, &cdkeyMenuInfo.frame );
	Menu_AddItem( &cdkeyMenuInfo.menu, &cdkeyMenuInfo.rq3_setupicon );
	Menu_AddItem( &cdkeyMenuInfo.menu, &cdkeyMenuInfo.rq3_setuptitle );
	Menu_AddItem( &cdkeyMenuInfo.menu, &cdkeyMenuInfo.cdkey );
	Menu_AddItem( &cdkeyMenuInfo.menu, &cdkeyMenuInfo.accept );
	if( uis.menusp ) {
		Menu_AddItem( &cdkeyMenuInfo.menu, &cdkeyMenuInfo.back );
	}

	trap_GetCDKey( cdkeyMenuInfo.cdkey.field.buffer, cdkeyMenuInfo.cdkey.field.maxchars + 1 );
	if( strcmp( cdkeyMenuInfo.cdkey.field.buffer, "123456789" ) == 0 ) {
		cdkeyMenuInfo.cdkey.field.buffer[0] = 0;
	}
}


/*
=================
UI_CDKeyMenu_Cache
=================
*/
void UI_CDKeyMenu_Cache( void ) {
	trap_R_RegisterShaderNoMip( ART_ACCEPT0 );
	trap_R_RegisterShaderNoMip( ART_ACCEPT1 );
	trap_R_RegisterShaderNoMip( ART_BACK0 );
	trap_R_RegisterShaderNoMip( ART_BACK1 );
	//Elder: added
	trap_R_RegisterShaderNoMip( RQ3_SETUP_ICON );
	trap_R_RegisterShaderNoMip( RQ3_SETUP_TITLE );
	//trap_R_RegisterShaderNoMip( ART_FRAME );
}


/*
===============
UI_CDKeyMenu
===============
*/
void UI_CDKeyMenu( void ) {
	UI_CDKeyMenu_Init();
	UI_PushMenu( &cdkeyMenuInfo.menu );
}


/*
===============
UI_CDKeyMenu_f
===============
*/
void UI_CDKeyMenu_f( void ) {
	UI_CDKeyMenu();
}
