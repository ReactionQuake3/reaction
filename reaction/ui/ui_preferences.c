//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.7  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
/*
=======================================================================

GAME OPTIONS MENU

=======================================================================
*/


#include "ui_local.h"

//Elder: removed
//#define ART_FRAMEL				"menu/art/frame2_l"
//#define ART_FRAMER				"menu/art/frame1_r"
#define ART_BACK0		"menu/art/rq3-menu-back.tga"
#define ART_BACK1		"menu/art/rq3-menu-back-focus.tga"	

//Elder: RQ3 Setup assets
#define RQ3_SETUP_ICON		"menu/art/rq3-setup-options.jpg"
#define RQ3_SETUP_TITLE		"menu/art/rq3-title-setup.jpg"

#define PREFERENCES_X_POS		200

#define ID_CROSSHAIR			127
#define ID_SIMPLEITEMS			128
#define ID_HIGHQUALITYSKY		129
#define ID_EJECTINGBRASS		130
#define ID_WALLMARKS			131
#define ID_DYNAMICLIGHTS		132
#define ID_IDENTIFYTARGET		133
#define ID_SYNCEVERYFRAME		134
#define ID_FORCEMODEL			135
#define ID_DRAWTEAMOVERLAY		136
#define ID_ALLOWDOWNLOAD			137
#define ID_BACK					138

#define	NUM_CROSSHAIRS			10

//Elder: RQ3 stuff
#define ID_MUZZLEFLASH			139
#define ID_PAINBLEND			140
#define ID_ANNOUNCER			141
#define ID_IMPACTEFFECTS		142

//#define 

typedef struct {
	menuframework_s		menu;

//	menutext_s			banner;
//	menubitmap_s		framel;
//	menubitmap_s		framer;
//Elder: removed
//	menutext_s			multim;
//	menutext_s			setupm;
//	menutext_s			demom;
//	menutext_s			modsm;
//	menutext_s			exitm;

	//Elder: RQ3 Stuff
	menubitmap_s	rq3_setupicon;
	menubitmap_s	rq3_setuptitle;
	menutext_s		rq3_statustext;

	menuradiobutton_s	rq3_muzzleflash;
	menuradiobutton_s	rq3_painblend;
	menuradiobutton_s	rq3_announcer;
	menuradiobutton_s	rq3_impacteffects;

	menulist_s			crosshair;
	menuradiobutton_s	simpleitems;
	menuradiobutton_s	brass;
	menuradiobutton_s	wallmarks;
	menuradiobutton_s	dynamiclights;
	menuradiobutton_s	identifytarget;
	menuradiobutton_s	highqualitysky;
	menuradiobutton_s	synceveryframe;
	menuradiobutton_s	forcemodel;
	menulist_s			drawteamoverlay;
	menuradiobutton_s	allowdownload;
	menubitmap_s		back;

	qhandle_t			crosshairShader[NUM_CROSSHAIRS];
} preferences_t;

static preferences_t s_preferences;

static const char *teamoverlay_names[] =
{
	"off",
	"upper right",
	"lower right",
	"lower left",
	0
};

/*
===============
Added by Elder
Preferences_MenuDraw
===============
*/
static void Preferences_MenuDraw( void ) {
	//Elder: "Dim" and "Letterbox" mask
	UI_FillRect( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color_deepdim );
	UI_FillRect( 0, 0, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 54, SCREEN_WIDTH, 2, color_red);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 2, color_red);
	
	// standard menu drawing
	Menu_Draw( &s_preferences.menu );
}

static void Preferences_SetMenuItems( void ) {
	s_preferences.crosshair.curvalue		= (int)trap_Cvar_VariableValue( "cg_drawCrosshair" ) % NUM_CROSSHAIRS;
	s_preferences.simpleitems.curvalue		= trap_Cvar_VariableValue( "cg_simpleItems" ) != 0;
	s_preferences.brass.curvalue			= trap_Cvar_VariableValue( "cg_brassTime" ) != 0;
	s_preferences.wallmarks.curvalue		= trap_Cvar_VariableValue( "cg_marks" ) != 0;
	s_preferences.identifytarget.curvalue	= trap_Cvar_VariableValue( "cg_drawCrosshairNames" ) != 0;
	s_preferences.dynamiclights.curvalue	= trap_Cvar_VariableValue( "r_dynamiclight" ) != 0;
	s_preferences.highqualitysky.curvalue	= trap_Cvar_VariableValue ( "r_fastsky" ) == 0;
	s_preferences.synceveryframe.curvalue	= trap_Cvar_VariableValue( "r_finish" ) != 0;
	s_preferences.forcemodel.curvalue		= trap_Cvar_VariableValue( "cg_forcemodel" ) != 0;
	s_preferences.drawteamoverlay.curvalue	= Com_Clamp( 0, 3, trap_Cvar_VariableValue( "cg_drawTeamOverlay" ) );
	s_preferences.allowdownload.curvalue	= trap_Cvar_VariableValue( "cl_allowDownload" ) != 0;
	//Elder: added
	s_preferences.rq3_muzzleflash.curvalue	= trap_Cvar_VariableValue( "cg_RQ3_flash" ) != 0;
	s_preferences.rq3_painblend.curvalue	= trap_Cvar_VariableValue( "cg_RQ3_painBlend" ) != 0;
	s_preferences.rq3_impacteffects.curvalue	= trap_Cvar_VariableValue( "cg_RQ3_impactEffects" ) != 0;
	s_preferences.rq3_announcer.curvalue	= trap_Cvar_VariableValue( "cg_RQ3_announcer" ) != 0;
}


static void Preferences_Event( void* ptr, int event ) {
	//Elder: Added status messages on event focus
	if ( event == QM_LOSTFOCUS ) {
		s_preferences.rq3_statustext.string = "";
	}
	else if ( event == QM_GOTFOCUS ) {
		//get menu item id
		switch( ((menucommon_s*)ptr)->id ) {

		case ID_CROSSHAIR:
			s_preferences.rq3_statustext.string = "Change regular crosshair style";
			break;

		case ID_SIMPLEITEMS:
			s_preferences.rq3_statustext.string = "Enable 2D sprite items";
			break;

		case ID_HIGHQUALITYSKY:
			s_preferences.rq3_statustext.string = "Enable high quality sky";
			break;

		case ID_EJECTINGBRASS:
			s_preferences.rq3_statustext.string = "Enable shell ejections";
			break;

		case ID_WALLMARKS:
			s_preferences.rq3_statustext.string = "Enable wall marks";
			break;

		case ID_DYNAMICLIGHTS:
			s_preferences.rq3_statustext.string = "Enable dynamic lighting";
			break;

		case ID_IDENTIFYTARGET:
			s_preferences.rq3_statustext.string = "Enable crosshair target identification";
			break;

		case ID_SYNCEVERYFRAME:
			s_preferences.rq3_statustext.string = "Enable V-SYNC (recommended off)";
			break;
		
		case ID_FORCEMODEL:
			s_preferences.rq3_statustext.string = "Force player models to your own";
			break;			

		case ID_DRAWTEAMOVERLAY:
			s_preferences.rq3_statustext.string = "Choose team overlay position";
			break;

		case ID_ALLOWDOWNLOAD:
			s_preferences.rq3_statustext.string = "Allow automatic downloads from server";
			break;

		case ID_MUZZLEFLASH:
			s_preferences.rq3_statustext.string = "Enable weapon muzzle flashes";
			break;

		case ID_PAINBLEND:
			s_preferences.rq3_statustext.string = "Enable screen pain blends";
			break;

		case ID_ANNOUNCER:
			s_preferences.rq3_statustext.string = "Enable Quake 3 announcer";
			break;

		case ID_IMPACTEFFECTS:
			s_preferences.rq3_statustext.string = "Enable visual projectile impact effects";
			break;

		case ID_BACK:
			s_preferences.rq3_statustext.string = "Return to setup menu";
			break;
			
		default:
			s_preferences.rq3_statustext.string = "";
			break;
		}
	}

	else if ( event == QM_ACTIVATED ) {
    	switch( ((menucommon_s*)ptr)->id ) {
    	case ID_CROSSHAIR:
    		s_preferences.crosshair.curvalue++;
    		if( s_preferences.crosshair.curvalue == NUM_CROSSHAIRS ) {
    			s_preferences.crosshair.curvalue = 0;
    		}
    		trap_Cvar_SetValue( "cg_drawCrosshair", s_preferences.crosshair.curvalue );
    		break;
    
    	case ID_SIMPLEITEMS:
    		trap_Cvar_SetValue( "cg_simpleItems", s_preferences.simpleitems.curvalue );
    		break;
    
    	case ID_HIGHQUALITYSKY:
    		trap_Cvar_SetValue( "r_fastsky", !s_preferences.highqualitysky.curvalue );
    		break;
    
    	case ID_EJECTINGBRASS:
    		if ( s_preferences.brass.curvalue )
    			trap_Cvar_Reset( "cg_brassTime" );
    		else
    			trap_Cvar_SetValue( "cg_brassTime", 0 );
    		break;
    
    	case ID_WALLMARKS:
    		trap_Cvar_SetValue( "cg_marks", s_preferences.wallmarks.curvalue );
    		break;
    
    	case ID_DYNAMICLIGHTS:
    		trap_Cvar_SetValue( "r_dynamiclight", s_preferences.dynamiclights.curvalue );
    		break;		
    
    	case ID_IDENTIFYTARGET:
    		trap_Cvar_SetValue( "cg_drawCrosshairNames", s_preferences.identifytarget.curvalue );
    		break;
    
    	case ID_SYNCEVERYFRAME:
    		trap_Cvar_SetValue( "r_finish", s_preferences.synceveryframe.curvalue );
    		break;
    
    	case ID_FORCEMODEL:
    		trap_Cvar_SetValue( "cg_forcemodel", s_preferences.forcemodel.curvalue );
    		break;
    
    	case ID_DRAWTEAMOVERLAY:
    		trap_Cvar_SetValue( "cg_drawTeamOverlay", s_preferences.drawteamoverlay.curvalue );
    		break;
    
    	case ID_ALLOWDOWNLOAD:
    		trap_Cvar_SetValue( "cl_allowDownload", s_preferences.allowdownload.curvalue );
    		break;
    
        case ID_MUZZLEFLASH:
    		trap_Cvar_SetValue( "cg_RQ3_flash", s_preferences.allowdownload.curvalue );
    		break;
		
		case ID_PAINBLEND:
    		trap_Cvar_SetValue( "cg_RQ3_painBlend", s_preferences.allowdownload.curvalue );
    		break;
    
    	case ID_BACK:
    		UI_PopMenu();
    		break;
    	}
	}
}


/*
=================
Crosshair_Draw
=================
*/
static void Crosshair_Draw( void *self ) {
	menulist_s	*s;
	float		*color;
	int			x, y;
	int			style;
	qboolean	focus;

	s = (menulist_s *)self;
	x = s->generic.x;
	y =	s->generic.y;

	style = UI_SMALLFONT;
	focus = (s->generic.parent->cursor == s->generic.menuPosition);

	if ( s->generic.flags & QMF_GRAYED )
		color = text_color_disabled;
	else if ( focus )
	{
		color = text_color_highlight;
		style |= UI_PULSE;
	}
	else if ( s->generic.flags & QMF_BLINK )
	{
		color = text_color_highlight;
		style |= UI_BLINK;
	}
	else
		color = text_color_normal;

	if ( focus )
	{
		// draw cursor
		UI_FillRect( s->generic.left, s->generic.top, s->generic.right-s->generic.left+1, s->generic.bottom-s->generic.top+1, listbar_color ); 
		UI_DrawChar( x, y, 13, UI_CENTER|UI_BLINK|UI_SMALLFONT, color);
	}

	UI_DrawString( x - SMALLCHAR_WIDTH, y, s->generic.name, style|UI_RIGHT, color );
	if( !s->curvalue ) {
		return;
	}
	UI_DrawHandlePic( x + SMALLCHAR_WIDTH, y - 4, 24, 24, s_preferences.crosshairShader[s->curvalue] );
}


static void Preferences_MenuInit( void ) {
	int				y;

	memset( &s_preferences, 0 ,sizeof(preferences_t) );

	Preferences_Cache();
	//Elder: added draw function
	s_preferences.menu.draw = Preferences_MenuDraw;
	s_preferences.menu.wrapAround = qtrue;
	s_preferences.menu.fullscreen = qtrue;
	s_preferences.menu.showlogo   = qtrue;

/*	s_preferences.banner.generic.type  = MTYPE_BTEXT;
	s_preferences.banner.generic.x	   = 320;
	s_preferences.banner.generic.y	   = 16;
	s_preferences.banner.string		   = "GAME OPTIONS";
	s_preferences.banner.color         = color_white;
	s_preferences.banner.style         = UI_CENTER;

	s_preferences.framel.generic.type  = MTYPE_BITMAP;
	s_preferences.framel.generic.name  = ART_FRAMEL;
	s_preferences.framel.generic.flags = QMF_INACTIVE;
	s_preferences.framel.generic.x	   = 0;
	s_preferences.framel.generic.y	   = 78;
	s_preferences.framel.width  	   = 256;
	s_preferences.framel.height  	   = 329;

	s_preferences.framer.generic.type  = MTYPE_BITMAP;
	s_preferences.framer.generic.name  = ART_FRAMER;
	s_preferences.framer.generic.flags = QMF_INACTIVE;
	s_preferences.framer.generic.x	   = 376;
	s_preferences.framer.generic.y	   = 76;
	s_preferences.framer.width  	   = 256;
	s_preferences.framer.height  	   = 334;
*/
/* Elder: removed
	s_preferences.multim.generic.type	= MTYPE_PTEXT;
	s_preferences.multim.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_preferences.multim.generic.x		= 120;
	s_preferences.multim.generic.y		= 3;
	s_preferences.multim.string			= "MULTIPLAYER";
	s_preferences.multim.color			= color_red;
	s_preferences.multim.style			= UI_CENTER | UI_DROPSHADOW;

	s_preferences.setupm.generic.type	= MTYPE_PTEXT;
	s_preferences.setupm.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_INACTIVE|QMF_HIGHLIGHT;
	s_preferences.setupm.generic.x		= 280;
	s_preferences.setupm.generic.y		= 3;
	s_preferences.setupm.string			= "SETUP";
	s_preferences.setupm.color			= color_red;
	s_preferences.setupm.style			= UI_CENTER | UI_DROPSHADOW;

	s_preferences.demom.generic.type	= MTYPE_PTEXT;
	s_preferences.demom.generic.flags	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_preferences.demom.generic.x		= 390;
	s_preferences.demom.generic.y		= 3;
	s_preferences.demom.string			= "DEMOS";
	s_preferences.demom.color			= color_red;
	s_preferences.demom.style			= UI_CENTER | UI_DROPSHADOW;

	s_preferences.modsm.generic.type	= MTYPE_PTEXT;
	s_preferences.modsm.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_preferences.modsm.generic.x		= 500;
	s_preferences.modsm.generic.y		= 3;
	s_preferences.modsm.string			= "MODS";
	s_preferences.modsm.color			= color_red;
	s_preferences.modsm.style			= UI_CENTER | UI_DROPSHADOW;

	s_preferences.exitm.generic.type	= MTYPE_PTEXT;
	s_preferences.exitm.generic.flags  	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_preferences.exitm.generic.x		= 590;
	s_preferences.exitm.generic.y		= 3;
	s_preferences.exitm.string			= "EXIT";
	s_preferences.exitm.color			= color_red;
	s_preferences.exitm.style			= UI_CENTER | UI_DROPSHADOW;
*/

	//Elder: Info for setup icon
	s_preferences.rq3_setupicon.generic.type				= MTYPE_BITMAP;
	s_preferences.rq3_setupicon.generic.name				= RQ3_SETUP_ICON;
	s_preferences.rq3_setupicon.generic.flags				= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	s_preferences.rq3_setupicon.generic.x					= 0;
	s_preferences.rq3_setupicon.generic.y					= 4;
	s_preferences.rq3_setupicon.width						= RQ3_ICON_WIDTH;
	s_preferences.rq3_setupicon.height						= RQ3_ICON_HEIGHT;

	//Elder: Info for setup title
	s_preferences.rq3_setuptitle.generic.type				= MTYPE_BITMAP;
	s_preferences.rq3_setuptitle.generic.name				= RQ3_SETUP_TITLE;
	s_preferences.rq3_setuptitle.generic.flags				= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	s_preferences.rq3_setuptitle.generic.x					= 64;
	s_preferences.rq3_setuptitle.generic.y					= 12;
	s_preferences.rq3_setuptitle.width						= 256;
	s_preferences.rq3_setuptitle.height						= 32;

	y = 64;
	s_preferences.crosshair.generic.type		= MTYPE_TEXT;
	s_preferences.crosshair.generic.flags		= QMF_PULSEIFFOCUS|QMF_SMALLFONT|QMF_NODEFAULTINIT|QMF_OWNERDRAW;
	s_preferences.crosshair.generic.x			= PREFERENCES_X_POS;
	s_preferences.crosshair.generic.y			= y;
	s_preferences.crosshair.generic.name		= "Crosshair:";
	s_preferences.crosshair.generic.callback	= Preferences_Event;
	s_preferences.crosshair.generic.ownerdraw	= Crosshair_Draw;
	s_preferences.crosshair.generic.id			= ID_CROSSHAIR;
	s_preferences.crosshair.generic.top			= y - 4;
	s_preferences.crosshair.generic.bottom		= y + 20;
	s_preferences.crosshair.generic.left		= PREFERENCES_X_POS - ( ( strlen(s_preferences.crosshair.generic.name) + 1 ) * SMALLCHAR_WIDTH );
	s_preferences.crosshair.generic.right		= PREFERENCES_X_POS + 48;

	y += BIGCHAR_HEIGHT+2+4;
	s_preferences.simpleitems.generic.type        = MTYPE_RADIOBUTTON;
	s_preferences.simpleitems.generic.name	      = "Simple Items:";
	s_preferences.simpleitems.generic.flags	      = QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_preferences.simpleitems.generic.callback    = Preferences_Event;
	s_preferences.simpleitems.generic.id          = ID_SIMPLEITEMS;
	s_preferences.simpleitems.generic.x	          = PREFERENCES_X_POS;
	s_preferences.simpleitems.generic.y	          = y;

	y += BIGCHAR_HEIGHT;
	s_preferences.wallmarks.generic.type          = MTYPE_RADIOBUTTON;
	s_preferences.wallmarks.generic.name	      = "Marks on Walls:";
	s_preferences.wallmarks.generic.flags	      = QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_preferences.wallmarks.generic.callback      = Preferences_Event;
	s_preferences.wallmarks.generic.id            = ID_WALLMARKS;
	s_preferences.wallmarks.generic.x	          = PREFERENCES_X_POS;
	s_preferences.wallmarks.generic.y	          = y;

	y += BIGCHAR_HEIGHT+2;
	s_preferences.rq3_impacteffects.generic.type            = MTYPE_RADIOBUTTON;
	s_preferences.rq3_impacteffects.generic.name	          = "Impact Effects:";
	s_preferences.rq3_impacteffects.generic.flags	          = QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_preferences.rq3_impacteffects.generic.callback        = Preferences_Event;
	s_preferences.rq3_impacteffects.generic.id              = ID_IMPACTEFFECTS;
	s_preferences.rq3_impacteffects.generic.x	              = PREFERENCES_X_POS;
	s_preferences.rq3_impacteffects.generic.y	              = y;

	y += BIGCHAR_HEIGHT+2;
	s_preferences.brass.generic.type              = MTYPE_RADIOBUTTON;
	s_preferences.brass.generic.name	          = "Ejecting Brass:";
	s_preferences.brass.generic.flags	          = QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_preferences.brass.generic.callback          = Preferences_Event;
	s_preferences.brass.generic.id                = ID_EJECTINGBRASS;
	s_preferences.brass.generic.x	              = PREFERENCES_X_POS;
	s_preferences.brass.generic.y	              = y;

	y += BIGCHAR_HEIGHT+2;
	s_preferences.dynamiclights.generic.type      = MTYPE_RADIOBUTTON;
	s_preferences.dynamiclights.generic.name	  = "Dynamic Lights:";
	s_preferences.dynamiclights.generic.flags     = QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_preferences.dynamiclights.generic.callback  = Preferences_Event;
	s_preferences.dynamiclights.generic.id        = ID_DYNAMICLIGHTS;
	s_preferences.dynamiclights.generic.x	      = PREFERENCES_X_POS;
	s_preferences.dynamiclights.generic.y	      = y;

	y += BIGCHAR_HEIGHT+2;
	s_preferences.rq3_muzzleflash.generic.type            = MTYPE_RADIOBUTTON;
	s_preferences.rq3_muzzleflash.generic.name	          = "Muzzle Flash:";
	s_preferences.rq3_muzzleflash.generic.flags	          = QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_preferences.rq3_muzzleflash.generic.callback        = Preferences_Event;
	s_preferences.rq3_muzzleflash.generic.id              = ID_MUZZLEFLASH;
	s_preferences.rq3_muzzleflash.generic.x	              = PREFERENCES_X_POS;
	s_preferences.rq3_muzzleflash.generic.y	              = y;

	y += BIGCHAR_HEIGHT+2;
	s_preferences.rq3_painblend.generic.type				= MTYPE_RADIOBUTTON;
	s_preferences.rq3_painblend.generic.name				= "Pain Blends:";
	s_preferences.rq3_painblend.generic.flags				= QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_preferences.rq3_painblend.generic.callback			= Preferences_Event;
	s_preferences.rq3_painblend.generic.id					= ID_PAINBLEND;
	s_preferences.rq3_painblend.generic.x					= PREFERENCES_X_POS;
	s_preferences.rq3_painblend.generic.y					= y;

	y += BIGCHAR_HEIGHT+2;
	s_preferences.rq3_announcer.generic.type            = MTYPE_RADIOBUTTON;
	s_preferences.rq3_announcer.generic.name	          = "Announcer:";
	s_preferences.rq3_announcer.generic.flags	          = QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_preferences.rq3_announcer.generic.callback        = Preferences_Event;
	s_preferences.rq3_announcer.generic.id              = ID_ANNOUNCER;
	s_preferences.rq3_announcer.generic.x	              = PREFERENCES_X_POS;
	s_preferences.rq3_announcer.generic.y	              = y;

	y += BIGCHAR_HEIGHT+2;
	s_preferences.identifytarget.generic.type     = MTYPE_RADIOBUTTON;
	s_preferences.identifytarget.generic.name	  = "Identify Target:";
	s_preferences.identifytarget.generic.flags    = QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_preferences.identifytarget.generic.callback = Preferences_Event;
	s_preferences.identifytarget.generic.id       = ID_IDENTIFYTARGET;
	s_preferences.identifytarget.generic.x	      = PREFERENCES_X_POS;
	s_preferences.identifytarget.generic.y	      = y;

	y += BIGCHAR_HEIGHT+2;
	s_preferences.highqualitysky.generic.type     = MTYPE_RADIOBUTTON;
	s_preferences.highqualitysky.generic.name	  = "High Quality Sky:";
	s_preferences.highqualitysky.generic.flags	  = QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_preferences.highqualitysky.generic.callback = Preferences_Event;
	s_preferences.highqualitysky.generic.id       = ID_HIGHQUALITYSKY;
	s_preferences.highqualitysky.generic.x	      = PREFERENCES_X_POS;
	s_preferences.highqualitysky.generic.y	      = y;

	y += BIGCHAR_HEIGHT+2;
	s_preferences.synceveryframe.generic.type     = MTYPE_RADIOBUTTON;
	s_preferences.synceveryframe.generic.name	  = "Sync Every Frame:";
	s_preferences.synceveryframe.generic.flags	  = QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_preferences.synceveryframe.generic.callback = Preferences_Event;
	s_preferences.synceveryframe.generic.id       = ID_SYNCEVERYFRAME;
	s_preferences.synceveryframe.generic.x	      = PREFERENCES_X_POS;
	s_preferences.synceveryframe.generic.y	      = y;

	y += BIGCHAR_HEIGHT+2;
	s_preferences.forcemodel.generic.type     = MTYPE_RADIOBUTTON;
	s_preferences.forcemodel.generic.name	  = "Force Player Models:";
	s_preferences.forcemodel.generic.flags	  = QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_preferences.forcemodel.generic.callback = Preferences_Event;
	s_preferences.forcemodel.generic.id       = ID_FORCEMODEL;
	s_preferences.forcemodel.generic.x	      = PREFERENCES_X_POS;
	s_preferences.forcemodel.generic.y	      = y;

	y += BIGCHAR_HEIGHT+2;
	s_preferences.drawteamoverlay.generic.type     = MTYPE_SPINCONTROL;
	s_preferences.drawteamoverlay.generic.name	   = "Draw Team Overlay:";
	s_preferences.drawteamoverlay.generic.flags	   = QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_preferences.drawteamoverlay.generic.callback = Preferences_Event;
	s_preferences.drawteamoverlay.generic.id       = ID_DRAWTEAMOVERLAY;
	s_preferences.drawteamoverlay.generic.x	       = PREFERENCES_X_POS;
	s_preferences.drawteamoverlay.generic.y	       = y;
	s_preferences.drawteamoverlay.itemnames			= teamoverlay_names;

	y += BIGCHAR_HEIGHT+2;
	s_preferences.allowdownload.generic.type     = MTYPE_RADIOBUTTON;
	s_preferences.allowdownload.generic.name	   = "Automatic Downloading:";
	s_preferences.allowdownload.generic.flags	   = QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_preferences.allowdownload.generic.callback = Preferences_Event;
	s_preferences.allowdownload.generic.id       = ID_ALLOWDOWNLOAD;
	s_preferences.allowdownload.generic.x	       = PREFERENCES_X_POS;
	s_preferences.allowdownload.generic.y	       = y;

	//Elder: RQ3 Status Text
	s_preferences.rq3_statustext.generic.type 		= MTYPE_TEXT;
	s_preferences.rq3_statustext.generic.flags		= QMF_CENTER_JUSTIFY;
	s_preferences.rq3_statustext.generic.x 			= RQ3_STATUSBAR_X;
	s_preferences.rq3_statustext.generic.y 			= RQ3_STATUSBAR_Y;
	s_preferences.rq3_statustext.string 			= "";
	s_preferences.rq3_statustext.style 				= UI_CENTER|UI_SMALLFONT;
	s_preferences.rq3_statustext.color 				= color_orange;

	y += BIGCHAR_HEIGHT+2;
	s_preferences.back.generic.type	    = MTYPE_BITMAP;
	s_preferences.back.generic.name     = ART_BACK0;
	s_preferences.back.generic.flags    = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	s_preferences.back.generic.callback = Preferences_Event;
	s_preferences.back.generic.id	    = ID_BACK;
	s_preferences.back.generic.x		= 8;
	s_preferences.back.generic.y		= 480-44;
	s_preferences.back.width  		    = 32;
	s_preferences.back.height  		    = 32;
	s_preferences.back.focuspic         = ART_BACK1;

//	Menu_AddItem( &s_preferences.menu, &s_preferences.banner );
//	Menu_AddItem( &s_preferences.menu, &s_preferences.framel );
//	Menu_AddItem( &s_preferences.menu, &s_preferences.framer );
//Elder: removed
//	Menu_AddItem( &s_preferences.menu, &s_preferences.multim );
//	Menu_AddItem( &s_preferences.menu, &s_preferences.setupm );
//	Menu_AddItem( &s_preferences.menu, &s_preferences.demom );
//	Menu_AddItem( &s_preferences.menu, &s_preferences.modsm );
//	Menu_AddItem( &s_preferences.menu, &s_preferences.exitm );

	//Elder: added
	Menu_AddItem( &s_preferences.menu, &s_preferences.rq3_setupicon );
	Menu_AddItem( &s_preferences.menu, &s_preferences.rq3_setuptitle );

	Menu_AddItem( &s_preferences.menu, &s_preferences.crosshair );
	Menu_AddItem( &s_preferences.menu, &s_preferences.simpleitems );
	Menu_AddItem( &s_preferences.menu, &s_preferences.wallmarks );
	Menu_AddItem( &s_preferences.menu, &s_preferences.rq3_impacteffects );
	Menu_AddItem( &s_preferences.menu, &s_preferences.brass );
	Menu_AddItem( &s_preferences.menu, &s_preferences.dynamiclights );
	Menu_AddItem( &s_preferences.menu, &s_preferences.rq3_muzzleflash );
	Menu_AddItem( &s_preferences.menu, &s_preferences.rq3_painblend );
	Menu_AddItem( &s_preferences.menu, &s_preferences.rq3_announcer );
	Menu_AddItem( &s_preferences.menu, &s_preferences.identifytarget );
	Menu_AddItem( &s_preferences.menu, &s_preferences.highqualitysky );
	Menu_AddItem( &s_preferences.menu, &s_preferences.synceveryframe );
	Menu_AddItem( &s_preferences.menu, &s_preferences.forcemodel );
	Menu_AddItem( &s_preferences.menu, &s_preferences.drawteamoverlay );
	Menu_AddItem( &s_preferences.menu, &s_preferences.allowdownload );

	Menu_AddItem( &s_preferences.menu, &s_preferences.back );

	Menu_AddItem( &s_preferences.menu, &s_preferences.rq3_statustext );

	Preferences_SetMenuItems();
}


/*
===============
Preferences_Cache
===============
*/
void Preferences_Cache( void ) {
	int		n;

	//Elder: removed
	//trap_R_RegisterShaderNoMip( ART_FRAMEL );
	//trap_R_RegisterShaderNoMip( ART_FRAMER );
	trap_R_RegisterShaderNoMip( ART_BACK0 );
	trap_R_RegisterShaderNoMip( ART_BACK1 );
	trap_R_RegisterShaderNoMip( RQ3_SETUP_ICON );
	trap_R_RegisterShaderNoMip( RQ3_SETUP_TITLE );
	for( n = 0; n < NUM_CROSSHAIRS; n++ ) {
		s_preferences.crosshairShader[n] = trap_R_RegisterShaderNoMip( va("gfx/2d/crosshair%c", 'a' + n ) );
	}
}


/*
===============
UI_PreferencesMenu
===============
*/
void UI_PreferencesMenu( void ) {
	Preferences_MenuInit();
	UI_PushMenu( &s_preferences.menu );
}
