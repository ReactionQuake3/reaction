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
// Copyright (C) 1999-2000 Id Software, Inc.
//
#include "ui_local.h"

void GraphicsOptions_MenuInit( void );

/*
=======================================================================

DRIVER INFORMATION MENU

=======================================================================
*/

//Elder: remove
//#define DRIVERINFO_FRAMEL	"menu/art/frame2_l"
//#define DRIVERINFO_FRAMER	"menu/art/frame1_r"
#define DRIVERINFO_BACK0	"menu/art/rq3-menu-back.tga"
#define DRIVERINFO_BACK1	"menu/art/rq3-menu-back-focus.tga"
#define RQ3_SYSTEM_ICON		"menu/art/rq3-setup-system.jpg"
#define RQ3_SETUP_TITLE		"menu/art/rq3-title-setup.tga"


static char* driverinfo_artlist[] = 
{
//Elder: removed
//	DRIVERINFO_FRAMEL,
//	DRIVERINFO_FRAMER,
	RQ3_SYSTEM_ICON,
	RQ3_SETUP_TITLE,
	DRIVERINFO_BACK0,
	DRIVERINFO_BACK1,
	NULL,
};

#define ID_DRIVERINFOBACK	100

typedef struct
{
	menuframework_s	menu;
//	menutext_s		banner;
//Elder: removed
//	menutext_s		multim;
//	menutext_s		setupm;
//	menutext_s		demom;
//	menutext_s		modsm;
//	menutext_s		exitm;

//Elder: RQ3 stuff	
	menubitmap_s	rq3_setuptitle;
	menubitmap_s	rq3_systemicon;
	
	menubitmap_s	back;
//	menubitmap_s	framel;
//	menubitmap_s	framer;
	char			stringbuff[1024];
	char*			strings[64];
	int				numstrings;
} driverinfo_t;

static driverinfo_t	s_driverinfo;

/*
=================
DriverInfo_Event
=================
*/
static void DriverInfo_Event( void* ptr, int event )
{
	if (event != QM_ACTIVATED)
		return;

	switch (((menucommon_s*)ptr)->id)
	{
		case ID_DRIVERINFOBACK:
			UI_PopMenu();
			break;
	}
}

/*
=================
DriverInfo_MenuDraw
=================
*/
static void DriverInfo_MenuDraw( void )
{
	int	i;
	int	x, y;
	//Elder: added
	char sVendor[256];

	//Elder: "Dim" mask
	UI_FillRect( 0, 0, 640, 480, color_deepdim );
	
	UI_DrawString( 100, 64, "VENDOR", UI_RIGHT|UI_SMALLFONT, color_red );
	UI_DrawString( 100, 96, "PIXELFORMAT", UI_RIGHT|UI_SMALLFONT, color_red );
	UI_DrawString( 100, 112, "EXTENSIONS", UI_RIGHT|UI_SMALLFONT, color_red );

	//Elder: consolidated into one string - bad coding? :(
	Q_strncpyz(sVendor, uis.glconfig.vendor_string, sizeof(sVendor));
	Q_strcat(sVendor, sizeof(sVendor), " (");
	Q_strcat(sVendor, sizeof(sVendor), uis.glconfig.version_string);
	Q_strcat(sVendor, sizeof(sVendor), ")");

	UI_DrawString( 110, 64, sVendor, UI_LEFT|UI_SMALLFONT, text_color_normal );
	//Elder: removed
	//UI_DrawString( 110, 64, uis.glconfig.vendor_string, UI_LEFT|UI_SMALLFONT, text_color_normal );
	//UI_DrawString( 110, 80, uis.glconfig.version_string, UI_LEFT|UI_SMALLFONT, text_color_normal );
	UI_DrawString( 110, 80, uis.glconfig.renderer_string, UI_LEFT|UI_SMALLFONT, text_color_normal );
	UI_DrawString( 110, 96, va ("color(%d-bits) Z(%d-bits) stencil(%d-bits)", uis.glconfig.colorBits, uis.glconfig.depthBits, uis.glconfig.stencilBits), UI_LEFT|UI_SMALLFONT, text_color_normal );

	// double column
	x = 110;
	y = 112;
	
	//Elder: strings[0] has some weird shit in it after going through the players menu so don't print it
	//I don't know why baseq3 doesn't have this problem, but just that it's the cause of a mucky
	//GL extension string formation
	/* Old code:
	y = 192+16;
	for (i=0; i<s_driverinfo.numstrings/2; i++) {
		UI_DrawString( 320-4, y, s_driverinfo.strings[i*2], UI_RIGHT|UI_SMALLFONT, text_color_normal );
		UI_DrawString( 320+4, y, s_driverinfo.strings[i*2+1], UI_LEFT|UI_SMALLFONT, text_color_normal );
		y += SMALLCHAR_HEIGHT;
	}

	if (s_driverinfo.numstrings & 1)
		UI_DrawString( 320, y, s_driverinfo.strings[s_driverinfo.numstrings-1], UI_CENTER|UI_SMALLFONT, text_color_normal );
	*/
	
	//Elder: new GL extension drawing code
	for (i=1; i<s_driverinfo.numstrings; i++) {
		UI_DrawString( x, y, s_driverinfo.strings[i], UI_LEFT|UI_SMALLFONT, text_color_normal );
		y += SMALLCHAR_HEIGHT;
		
		//one line before letterbox
		if ( y > (426 - SMALLCHAR_HEIGHT * 2) ) {
			//end of the line
			if (x == 370) {
				break;
			}
			//switch columns and reset y
			else {
				y = 112;
				x = 370;
			}
		}
	}
	
	//Indicates number of extensions not shown
	if (i < s_driverinfo.numstrings) {
		UI_DrawString( 320, y, va ("Extensions not listed: %i", s_driverinfo.numstrings - i - 1), UI_CENTER|UI_SMALLFONT|UI_PULSE, color_yellow );
	}
	
	//Elder: "Letterbox" mask
	UI_FillRect( 0, 0, 640, 54, color_black);
	UI_FillRect( 0, 426, 640, 54, color_black);
	UI_FillRect( 0, 54, SCREEN_WIDTH, 2, color_red);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 2, color_red);

	//Elder: moved outside the mask scope
	Menu_Draw( &s_driverinfo.menu );

}

/*
=================
DriverInfo_Cache
=================
*/
void DriverInfo_Cache( void )
{

	int	i;

	// touch all our pics
	for (i=0; ;i++)
	{
		if (!driverinfo_artlist[i])
			break;
		trap_R_RegisterShaderNoMip(driverinfo_artlist[i]);
	}

	
}

/*
=================
UI_DriverInfo_Menu
=================
*/
static void UI_DriverInfo_Menu( void )
{
	char*	eptr;
	int		i;
	int		len;

	// zero set all our globals
	memset( &s_driverinfo, 0 ,sizeof(driverinfo_t) );

	DriverInfo_Cache();

	s_driverinfo.menu.fullscreen = qtrue;
	s_driverinfo.menu.showlogo	 = qtrue;
	s_driverinfo.menu.draw       = DriverInfo_MenuDraw;

/*	s_driverinfo.banner.generic.type  = MTYPE_BTEXT;
	s_driverinfo.banner.generic.x	  = 320;
	s_driverinfo.banner.generic.y	  = 16;
	s_driverinfo.banner.string		  = "DRIVER INFO";
	s_driverinfo.banner.color	      = color_white;
	s_driverinfo.banner.style	      = UI_CENTER;

	s_driverinfo.framel.generic.type  = MTYPE_BITMAP;
	s_driverinfo.framel.generic.name  = DRIVERINFO_FRAMEL;
	s_driverinfo.framel.generic.flags = QMF_INACTIVE;
	s_driverinfo.framel.generic.x	  = 0;
	s_driverinfo.framel.generic.y	  = 78;
	s_driverinfo.framel.width  	      = 256;
	s_driverinfo.framel.height  	  = 329;

	s_driverinfo.framer.generic.type  = MTYPE_BITMAP;
	s_driverinfo.framer.generic.name  = DRIVERINFO_FRAMER;
	s_driverinfo.framer.generic.flags = QMF_INACTIVE;
	s_driverinfo.framer.generic.x	  = 376;
	s_driverinfo.framer.generic.y	  = 76;
	s_driverinfo.framer.width  	      = 256;
	s_driverinfo.framer.height  	  = 334;
*/
/* Elder: removed
	s_driverinfo.multim.generic.type	= MTYPE_PTEXT;
	s_driverinfo.multim.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_driverinfo.multim.generic.x		= 120;
	s_driverinfo.multim.generic.y		= 3;
	s_driverinfo.multim.string			= "MULTIPLAYER";
	s_driverinfo.multim.color			= color_red;
	s_driverinfo.multim.style			= UI_CENTER | UI_DROPSHADOW;

	s_driverinfo.setupm.generic.type	= MTYPE_PTEXT;
	s_driverinfo.setupm.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_INACTIVE|QMF_HIGHLIGHT;
	s_driverinfo.setupm.generic.x		= 280;
	s_driverinfo.setupm.generic.y		= 3;
	s_driverinfo.setupm.string			= "SETUP";
	s_driverinfo.setupm.color			= color_red;
	s_driverinfo.setupm.style			= UI_CENTER | UI_DROPSHADOW;

	s_driverinfo.demom.generic.type		= MTYPE_PTEXT;
	s_driverinfo.demom.generic.flags	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_driverinfo.demom.generic.x		= 390;
	s_driverinfo.demom.generic.y		= 3;
	s_driverinfo.demom.string			= "DEMOS";
	s_driverinfo.demom.color			= color_red;
	s_driverinfo.demom.style			= UI_CENTER | UI_DROPSHADOW;

	s_driverinfo.modsm.generic.type		= MTYPE_PTEXT;
//Note the following line, this makes it highlight
	s_driverinfo.modsm.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_driverinfo.modsm.generic.x		= 500;
	s_driverinfo.modsm.generic.y		= 3;
	s_driverinfo.modsm.string			= "MODS";
	s_driverinfo.modsm.color			= color_red;
	s_driverinfo.modsm.style			= UI_CENTER | UI_DROPSHADOW;

	s_driverinfo.exitm.generic.type		= MTYPE_PTEXT;
	s_driverinfo.exitm.generic.flags  	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_driverinfo.exitm.generic.x		= 590;
	s_driverinfo.exitm.generic.y		= 3;
	s_driverinfo.exitm.string			= "EXIT";
	s_driverinfo.exitm.color			= color_red;
	s_driverinfo.exitm.style			= UI_CENTER | UI_DROPSHADOW;
*/

	//Elder: Info for system icon
	s_driverinfo.rq3_systemicon.generic.type			= MTYPE_BITMAP;
	s_driverinfo.rq3_systemicon.generic.name			= RQ3_SYSTEM_ICON;
	s_driverinfo.rq3_systemicon.generic.flags			= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	s_driverinfo.rq3_systemicon.generic.x				= 0;
	s_driverinfo.rq3_systemicon.generic.y				= 4;
	s_driverinfo.rq3_systemicon.width					= RQ3_ICON_WIDTH;
	s_driverinfo.rq3_systemicon.height					= RQ3_ICON_HEIGHT;

	//Elder: Info for setup title
	s_driverinfo.rq3_setuptitle.generic.type			= MTYPE_BITMAP;
	s_driverinfo.rq3_setuptitle.generic.name			= RQ3_SETUP_TITLE;
	s_driverinfo.rq3_setuptitle.generic.flags			= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	s_driverinfo.rq3_setuptitle.generic.x				= 64;
	s_driverinfo.rq3_setuptitle.generic.y				= 12;
	s_driverinfo.rq3_setuptitle.width					= 256;
	s_driverinfo.rq3_setuptitle.height					= 32;

	s_driverinfo.back.generic.type	   = MTYPE_BITMAP;
	s_driverinfo.back.generic.name     = DRIVERINFO_BACK0;
	s_driverinfo.back.generic.flags    = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	s_driverinfo.back.generic.callback = DriverInfo_Event;
	s_driverinfo.back.generic.id	   = ID_DRIVERINFOBACK;
	s_driverinfo.back.generic.x		   = 8;
	s_driverinfo.back.generic.y		   = 480-44;
	s_driverinfo.back.width  		   = 32;
	s_driverinfo.back.height  		   = 32;
	s_driverinfo.back.focuspic         = DRIVERINFO_BACK1;

	strcpy( s_driverinfo.stringbuff, uis.glconfig.extensions_string );

	// build null terminated extension strings
	eptr = s_driverinfo.stringbuff;
	while ( s_driverinfo.numstrings<40 && *eptr )
	{
		while ( *eptr && *eptr == ' ' )
			*eptr++ = '\0';

		// track start of valid string
		if (*eptr && *eptr != ' ')
			s_driverinfo.strings[s_driverinfo.numstrings++] = eptr;

		while ( *eptr && *eptr != ' ' )
			eptr++;
	}

	// safety length strings for display
	for (i=0; i<s_driverinfo.numstrings; i++) {
		len = strlen(s_driverinfo.strings[i]);
		if (len > 32) {
			s_driverinfo.strings[i][len-1] = '>';
			s_driverinfo.strings[i][len]   = '\0';
		}
	}

//	Menu_AddItem( &s_driverinfo.menu, &s_driverinfo.banner );
//	Menu_AddItem( &s_driverinfo.menu, &s_driverinfo.framel );
//	Menu_AddItem( &s_driverinfo.menu, &s_driverinfo.framer );
//Elder: removed
//	Menu_AddItem( &s_driverinfo.menu, &s_driverinfo.multim );
//	Menu_AddItem( &s_driverinfo.menu, &s_driverinfo.setupm );
//	Menu_AddItem( &s_driverinfo.menu, &s_driverinfo.demom );
//	Menu_AddItem( &s_driverinfo.menu, &s_driverinfo.modsm );
//	Menu_AddItem( &s_driverinfo.menu, &s_driverinfo.exitm );

	Menu_AddItem( &s_driverinfo.menu, ( void * ) &s_driverinfo.rq3_systemicon );
	Menu_AddItem( &s_driverinfo.menu, ( void * ) &s_driverinfo.rq3_setuptitle );
	Menu_AddItem( &s_driverinfo.menu, &s_driverinfo.back );

	UI_PushMenu( &s_driverinfo.menu );
}

/*
=======================================================================

GRAPHICS OPTIONS MENU

=======================================================================
*/

//#define GRAPHICSOPTIONS_FRAMEL	"menu/art/frame2_l"
//#define GRAPHICSOPTIONS_FRAMER	"menu/art/frame1_r"
#define GRAPHICSOPTIONS_BACK0	"menu/art/rq3-menu-back.tga"
#define GRAPHICSOPTIONS_BACK1	"menu/art/rq3-menu-back-focus.tga"
#define GRAPHICSOPTIONS_ACCEPT0	"menu/art/rq3-menu-go.tga"
#define GRAPHICSOPTIONS_ACCEPT1	"menu/art/rq3-menu-go-focus.tga"

static const char *s_drivers[] =
{
	OPENGL_DRIVER_NAME,
	_3DFX_DRIVER_NAME,
	0
};

#define ID_BACK2		101
#define ID_FULLSCREEN	102
#define ID_LIST			103
#define ID_MODE			104
#define ID_DRIVERINFO	105
#define ID_GRAPHICS		106
#define ID_DISPLAY		107
#define ID_SOUND		108
#define ID_NETWORK		109

//Elder: RQ3 stuff - first two defined at top of file
//#define RQ3_SYSTEM_ICON		"menu/art/rq3-setup-system.jpg"
//#define RQ3_SETUP_TITLE		"menu/art/rq3-title-setup.tga"
#define RQ3_FOCUS_BUTTON	"menu/art/rq3-menu-focus.tga"
#define RQ3_GRAPHICS_BUTTON	"menu/art/rq3-system-graphics.tga"
#define RQ3_DISPLAY_BUTTON	"menu/art/rq3-system-display.tga"
#define RQ3_SOUND_BUTTON	"menu/art/rq3-system-sound.tga"
#define RQ3_NETWORK_BUTTON	"menu/art/rq3-system-network.tga"
#define RQ3_DRIVERINFO_BUTTON	"menu/art/rq3-system-driverinfo.jpg"

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

//Elder: RQ3 stuff	
	menubitmap_s	rq3_setuptitle;
	menubitmap_s	rq3_systemicon;
	menubitmap_s	rq3_graphics;
	menubitmap_s	rq3_display;
	menubitmap_s	rq3_sound;
	menubitmap_s	rq3_network;
	menubitmap_s	rq3_driverinfo;
	menutext_s		rq3_statustext;

	menulist_s		list;
	menulist_s		mode;
	menulist_s		driver;
	menuslider_s	tq;
	menulist_s  	fs;
	menulist_s  	lighting;
	menulist_s  	allow_extensions;
	menulist_s  	texturebits;
	menulist_s  	colordepth;
	menulist_s  	geometry;
	menulist_s  	filter;
	//Elder: removed
	//menutext_s		driverinfo;

	menubitmap_s	apply;
	menubitmap_s	back;
} graphicsoptions_t;

typedef struct
{
	int mode;
	qboolean fullscreen;
	int tq;
	int lighting;
	int colordepth;
	int texturebits;
	int geometry;
	int filter;
	int driver;
	qboolean extensions;
} InitialVideoOptions_s;

static InitialVideoOptions_s	s_ivo;
static graphicsoptions_t		s_graphicsoptions;	

static InitialVideoOptions_s s_ivo_templates[] =
{
	{
		4, qtrue, 2, 0, 2, 2, 1, 1, 0, qtrue	// JDC: this was tq 3
	},
	{
		3, qtrue, 2, 0, 0, 0, 1, 0, 0, qtrue
	},
	{
		2, qtrue, 1, 0, 1, 0, 0, 0, 0, qtrue
	},
	{
		2, qtrue, 1, 1, 1, 0, 0, 0, 0, qtrue
	},
	{
		3, qtrue, 1, 0, 0, 0, 1, 0, 0, qtrue
	}
};

#define NUM_IVO_TEMPLATES ( sizeof( s_ivo_templates ) / sizeof( s_ivo_templates[0] ) )

/*
=================
GraphicsOptions_GetInitialVideo
=================
*/
static void GraphicsOptions_GetInitialVideo( void )
{
	s_ivo.colordepth  = s_graphicsoptions.colordepth.curvalue;
	s_ivo.driver      = s_graphicsoptions.driver.curvalue;
	s_ivo.mode        = s_graphicsoptions.mode.curvalue;
	s_ivo.fullscreen  = s_graphicsoptions.fs.curvalue;
	s_ivo.extensions  = s_graphicsoptions.allow_extensions.curvalue;
	s_ivo.tq          = s_graphicsoptions.tq.curvalue;
	s_ivo.lighting    = s_graphicsoptions.lighting.curvalue;
	s_ivo.geometry    = s_graphicsoptions.geometry.curvalue;
	s_ivo.filter      = s_graphicsoptions.filter.curvalue;
	s_ivo.texturebits = s_graphicsoptions.texturebits.curvalue;
}

/*
=================
GraphicsOptions_CheckConfig
=================
*/
static void GraphicsOptions_CheckConfig( void )
{
	int i;

	for ( i = 0; i < NUM_IVO_TEMPLATES; i++ )
	{
		if ( s_ivo_templates[i].colordepth != s_graphicsoptions.colordepth.curvalue )
			continue;
		if ( s_ivo_templates[i].driver != s_graphicsoptions.driver.curvalue )
			continue;
		if ( s_ivo_templates[i].mode != s_graphicsoptions.mode.curvalue )
			continue;
		if ( s_ivo_templates[i].fullscreen != s_graphicsoptions.fs.curvalue )
			continue;
		if ( s_ivo_templates[i].tq != s_graphicsoptions.tq.curvalue )
			continue;
		if ( s_ivo_templates[i].lighting != s_graphicsoptions.lighting.curvalue )
			continue;
		if ( s_ivo_templates[i].geometry != s_graphicsoptions.geometry.curvalue )
			continue;
		if ( s_ivo_templates[i].filter != s_graphicsoptions.filter.curvalue )
			continue;
//		if ( s_ivo_templates[i].texturebits != s_graphicsoptions.texturebits.curvalue )
//			continue;
		s_graphicsoptions.list.curvalue = i;
		return;
	}
	s_graphicsoptions.list.curvalue = 4;
}

/*
=================
GraphicsOptions_UpdateMenuItems
=================
*/
static void GraphicsOptions_UpdateMenuItems( void )
{
	if ( s_graphicsoptions.driver.curvalue == 1 )
	{
		s_graphicsoptions.fs.curvalue = 1;
		s_graphicsoptions.fs.generic.flags |= QMF_GRAYED;
		s_graphicsoptions.colordepth.curvalue = 1;
	}
	else
	{
		s_graphicsoptions.fs.generic.flags &= ~QMF_GRAYED;
	}

	if ( s_graphicsoptions.fs.curvalue == 0 || s_graphicsoptions.driver.curvalue == 1 )
	{
		s_graphicsoptions.colordepth.curvalue = 0;
		s_graphicsoptions.colordepth.generic.flags |= QMF_GRAYED;
	}
	else
	{
		s_graphicsoptions.colordepth.generic.flags &= ~QMF_GRAYED;
	}

	if ( s_graphicsoptions.allow_extensions.curvalue == 0 )
	{
		if ( s_graphicsoptions.texturebits.curvalue == 0 )
		{
			s_graphicsoptions.texturebits.curvalue = 1;
		}
	}

	s_graphicsoptions.apply.generic.flags |= QMF_HIDDEN|QMF_INACTIVE;

	if ( s_ivo.mode != s_graphicsoptions.mode.curvalue )
	{
		s_graphicsoptions.apply.generic.flags &= ~(QMF_HIDDEN|QMF_INACTIVE);
	}
	if ( s_ivo.fullscreen != s_graphicsoptions.fs.curvalue )
	{
		s_graphicsoptions.apply.generic.flags &= ~(QMF_HIDDEN|QMF_INACTIVE);
	}
	if ( s_ivo.extensions != s_graphicsoptions.allow_extensions.curvalue )
	{
		s_graphicsoptions.apply.generic.flags &= ~(QMF_HIDDEN|QMF_INACTIVE);
	}
	if ( s_ivo.tq != s_graphicsoptions.tq.curvalue )
	{
		s_graphicsoptions.apply.generic.flags &= ~(QMF_HIDDEN|QMF_INACTIVE);
	}
	if ( s_ivo.lighting != s_graphicsoptions.lighting.curvalue )
	{
		s_graphicsoptions.apply.generic.flags &= ~(QMF_HIDDEN|QMF_INACTIVE);
	}
	if ( s_ivo.colordepth != s_graphicsoptions.colordepth.curvalue )
	{
		s_graphicsoptions.apply.generic.flags &= ~(QMF_HIDDEN|QMF_INACTIVE);
	}
	if ( s_ivo.driver != s_graphicsoptions.driver.curvalue )
	{
		s_graphicsoptions.apply.generic.flags &= ~(QMF_HIDDEN|QMF_INACTIVE);
	}
	if ( s_ivo.texturebits != s_graphicsoptions.texturebits.curvalue )
	{
		s_graphicsoptions.apply.generic.flags &= ~(QMF_HIDDEN|QMF_INACTIVE);
	}
	if ( s_ivo.geometry != s_graphicsoptions.geometry.curvalue )
	{
		s_graphicsoptions.apply.generic.flags &= ~(QMF_HIDDEN|QMF_INACTIVE);
	}
	if ( s_ivo.filter != s_graphicsoptions.filter.curvalue )
	{
		s_graphicsoptions.apply.generic.flags &= ~(QMF_HIDDEN|QMF_INACTIVE);
	}

	GraphicsOptions_CheckConfig();
}	

/*
=================
GraphicsOptions_ApplyChanges
=================
*/
static void GraphicsOptions_ApplyChanges( void *unused, int notification )
{
	//Elder: some quick modifications
	if (notification == QM_GOTFOCUS) {
		s_graphicsoptions.rq3_statustext.string = "Apply changes";
		return;
	}
	else if (notification == QM_LOSTFOCUS) {
		s_graphicsoptions.rq3_statustext.string = "";
		return;
	}
	else if (notification == QM_ACTIVATED) {
    	switch ( s_graphicsoptions.texturebits.curvalue  )
    	{
    	case 0:
    		trap_Cvar_SetValue( "r_texturebits", 0 );
    		break;
    	case 1:
    		trap_Cvar_SetValue( "r_texturebits", 16 );
    		break;
    	case 2:
    		trap_Cvar_SetValue( "r_texturebits", 32 );
    		break;
    	}
    	trap_Cvar_SetValue( "r_picmip", 3 - s_graphicsoptions.tq.curvalue );
    	trap_Cvar_SetValue( "r_allowExtensions", s_graphicsoptions.allow_extensions.curvalue );
    	trap_Cvar_SetValue( "r_mode", s_graphicsoptions.mode.curvalue );
    	trap_Cvar_SetValue( "r_fullscreen", s_graphicsoptions.fs.curvalue );
    	trap_Cvar_Set( "r_glDriver", ( char * ) s_drivers[s_graphicsoptions.driver.curvalue] );
    	switch ( s_graphicsoptions.colordepth.curvalue )
    	{
    	case 0:
    		trap_Cvar_SetValue( "r_colorbits", 0 );
    		trap_Cvar_SetValue( "r_depthbits", 0 );
    		trap_Cvar_SetValue( "r_stencilbits", 0 );
    		break;
    	case 1:
    		trap_Cvar_SetValue( "r_colorbits", 16 );
    		trap_Cvar_SetValue( "r_depthbits", 16 );
    		trap_Cvar_SetValue( "r_stencilbits", 0 );
    		break;
    	case 2:
    		trap_Cvar_SetValue( "r_colorbits", 32 );
    		trap_Cvar_SetValue( "r_depthbits", 24 );
    		break;
    	}
    	trap_Cvar_SetValue( "r_vertexLight", s_graphicsoptions.lighting.curvalue );
    
    	if ( s_graphicsoptions.geometry.curvalue == 2 )
    	{
    		trap_Cvar_SetValue( "r_lodBias", 0 );
    		trap_Cvar_SetValue( "r_subdivisions", 4 );
    	}
    	else if ( s_graphicsoptions.geometry.curvalue == 1 )
    	{
    		trap_Cvar_SetValue( "r_lodBias", 1 );
    		trap_Cvar_SetValue( "r_subdivisions", 12 );
    	}
    	else
    	{
    		trap_Cvar_SetValue( "r_lodBias", 1 );
    		trap_Cvar_SetValue( "r_subdivisions", 20 );
    	}
    
    	if ( s_graphicsoptions.filter.curvalue )
    	{
    		trap_Cvar_Set( "r_textureMode", "GL_LINEAR_MIPMAP_LINEAR" );
    	}
    	else
    	{
    		trap_Cvar_Set( "r_textureMode", "GL_LINEAR_MIPMAP_NEAREST" );
    	}
    
    	trap_Cmd_ExecuteText( EXEC_APPEND, "vid_restart\n" );
    }
}

/*
=================
GraphicsOptions_Event
=================
*/
static void GraphicsOptions_Event( void* ptr, int event ) {
	InitialVideoOptions_s *ivo;

	//Elder: for status bar
	if( event == QM_LOSTFOCUS ) {
		s_graphicsoptions.rq3_statustext.string = "";
		return;
	}
	else if ( event == QM_GOTFOCUS ) {
		switch( ((menucommon_s*)ptr)->id ) {
		case ID_GRAPHICS:
			s_graphicsoptions.rq3_statustext.string = "Change graphics settings";
			break;

		case ID_DISPLAY:
			s_graphicsoptions.rq3_statustext.string = "Change display settings";
			break;

		case ID_SOUND:
			s_graphicsoptions.rq3_statustext.string = "Change sound settings";
			break;
	
		case ID_NETWORK:
			s_graphicsoptions.rq3_statustext.string = "Change network settings";
			break;
		
		case ID_BACK2:
			s_graphicsoptions.rq3_statustext.string = "Return to setup menu";
			break;
		
		case ID_MODE:
			s_graphicsoptions.rq3_statustext.string = "Change video resolution";
			break;
		
		case ID_DRIVERINFO:
			s_graphicsoptions.rq3_statustext.string = "View driver info and GL extensions";
			break;
		
		default:
			s_graphicsoptions.rq3_statustext.string = "";
			break;
		}
	}
	else if ( event == QM_ACTIVATED ) {
    	switch( ((menucommon_s*)ptr)->id ) {
    	
    	case ID_MODE:
    		// clamp 3dfx video modes
    		if ( s_graphicsoptions.driver.curvalue == 1 )
    		{
    			if ( s_graphicsoptions.mode.curvalue < 2 )
    				s_graphicsoptions.mode.curvalue = 2;
    			else if ( s_graphicsoptions.mode.curvalue > 6 )
    				s_graphicsoptions.mode.curvalue = 6;
    		}
    		break;
    
    	case ID_LIST:
    		ivo = &s_ivo_templates[s_graphicsoptions.list.curvalue];
    
    		s_graphicsoptions.mode.curvalue        = ivo->mode;
    		s_graphicsoptions.tq.curvalue          = ivo->tq;
    		s_graphicsoptions.lighting.curvalue    = ivo->lighting;
    		s_graphicsoptions.colordepth.curvalue  = ivo->colordepth;
    		s_graphicsoptions.texturebits.curvalue = ivo->texturebits;
    		s_graphicsoptions.geometry.curvalue    = ivo->geometry;
    		s_graphicsoptions.filter.curvalue      = ivo->filter;
    		s_graphicsoptions.fs.curvalue          = ivo->fullscreen;
    		break;
    
    	case ID_DRIVERINFO:
    		UI_DriverInfo_Menu();
    		break;
    
    	case ID_BACK2:
    		UI_PopMenu();
    		break;
    
    	case ID_GRAPHICS:
    		break;
    
    	case ID_DISPLAY:
    		UI_PopMenu();
    		UI_DisplayOptionsMenu();
    		break;
    
    	case ID_SOUND:
    		UI_PopMenu();
    		UI_SoundOptionsMenu();
    		break;
    
    	case ID_NETWORK:
    		UI_PopMenu();
    		UI_NetworkOptionsMenu();
    		break;
    	}
	}
}


/*
================
GraphicsOptions_TQEvent
================
*/
static void GraphicsOptions_TQEvent( void *ptr, int event ) {
	if( event != QM_ACTIVATED ) {
	 	return;
	}
	s_graphicsoptions.tq.curvalue = (int)(s_graphicsoptions.tq.curvalue + 0.5);
}


/*
================
GraphicsOptions_MenuDraw
================
*/
void GraphicsOptions_MenuDraw (void)
{
//APSFIX - rework this
	GraphicsOptions_UpdateMenuItems();

	//Elder: "Dim" and "Letterbox" mask
	UI_FillRect( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color_deepdim );
	UI_FillRect( 0, 0, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 54, SCREEN_WIDTH, 2, color_red);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 2, color_red);
	
	Menu_Draw( &s_graphicsoptions.menu );
}

/*
=================
GraphicsOptions_SetMenuItems
=================
*/
static void GraphicsOptions_SetMenuItems( void )
{
	s_graphicsoptions.mode.curvalue = trap_Cvar_VariableValue( "r_mode" );
	if ( s_graphicsoptions.mode.curvalue < 0 )
	{
		s_graphicsoptions.mode.curvalue = 3;
	}
	s_graphicsoptions.fs.curvalue = trap_Cvar_VariableValue("r_fullscreen");
	s_graphicsoptions.allow_extensions.curvalue = trap_Cvar_VariableValue("r_allowExtensions");
	s_graphicsoptions.tq.curvalue = 3-trap_Cvar_VariableValue( "r_picmip");
	if ( s_graphicsoptions.tq.curvalue < 0 )
	{
		s_graphicsoptions.tq.curvalue = 0;
	}
	else if ( s_graphicsoptions.tq.curvalue > 3 )
	{
		s_graphicsoptions.tq.curvalue = 3;
	}

	s_graphicsoptions.lighting.curvalue = trap_Cvar_VariableValue( "r_vertexLight" ) != 0;
	switch ( ( int ) trap_Cvar_VariableValue( "r_texturebits" ) )
	{
	default:
	case 0:
		s_graphicsoptions.texturebits.curvalue = 0;
		break;
	case 16:
		s_graphicsoptions.texturebits.curvalue = 1;
		break;
	case 32:
		s_graphicsoptions.texturebits.curvalue = 2;
		break;
	}

	if ( !Q_stricmp( UI_Cvar_VariableString( "r_textureMode" ), "GL_LINEAR_MIPMAP_NEAREST" ) )
	{
		s_graphicsoptions.filter.curvalue = 0;
	}
	else
	{
		s_graphicsoptions.filter.curvalue = 1;
	}

	if ( trap_Cvar_VariableValue( "r_lodBias" ) > 0 )
	{
		if ( trap_Cvar_VariableValue( "r_subdivisions" ) >= 20 )
		{
			s_graphicsoptions.geometry.curvalue = 0;
		}
		else
		{
			s_graphicsoptions.geometry.curvalue = 1;
		}
	}
	else
	{
		s_graphicsoptions.geometry.curvalue = 2;
	}

	switch ( ( int ) trap_Cvar_VariableValue( "r_colorbits" ) )
	{
	default:
	case 0:
		s_graphicsoptions.colordepth.curvalue = 0;
		break;
	case 16:
		s_graphicsoptions.colordepth.curvalue = 1;
		break;
	case 32:
		s_graphicsoptions.colordepth.curvalue = 2;
		break;
	}

	if ( s_graphicsoptions.fs.curvalue == 0 )
	{
		s_graphicsoptions.colordepth.curvalue = 0;
	}
	if ( s_graphicsoptions.driver.curvalue == 1 )
	{
		s_graphicsoptions.colordepth.curvalue = 1;
	}
}

/*
================
GraphicsOptions_MenuInit
================
*/
void GraphicsOptions_MenuInit( void )
{
	static const char *s_driver_names[] =
	{
		"Default",
		"Voodoo",
		0
	};

	static const char *tq_names[] =
	{
		"Default",
		"16 bit",
		"32 bit",
		0
	};

	static const char *s_graphics_options_names[] =
	{
		"High Quality",
		"Normal",
		"Fast",
		"Fastest",
		"Custom",
		0
	};

	static const char *lighting_names[] =
	{
		"Lightmap",
		"Vertex",
		0
	};

	static const char *colordepth_names[] =
	{
		"Default",
		"16 bit",
		"32 bit",
		0
	};

	static const char *resolutions[] = 
	{
		"320x240",
		"400x300",
		"512x384",
		"640x480",
		"800x600",
		"960x720",
		"1024x768",
		"1152x864",
		"1280x1024",
		"1600x1200",
		"2048x1536",
		"856x480 wide screen",
		0
	};
	static const char *filter_names[] =
	{
		"Bilinear",
		"Trilinear",
		0
	};
	static const char *quality_names[] =
	{
		"Low",
		"Medium",
		"High",
		0
	};
	static const char *enabled_names[] =
	{
		"Off",
		"On",
		0
	};

	int y = 12;
	int buttonCount = 0;

	// zero set all our globals
	memset( &s_graphicsoptions, 0 ,sizeof(graphicsoptions_t) );

	GraphicsOptions_Cache();

	s_graphicsoptions.menu.draw       = GraphicsOptions_MenuDraw;
	s_graphicsoptions.menu.wrapAround = qtrue;
	s_graphicsoptions.menu.fullscreen = qtrue;
	s_graphicsoptions.menu.showlogo	  = qtrue;

/*	s_graphicsoptions.banner.generic.type  = MTYPE_BTEXT;
	s_graphicsoptions.banner.generic.x	   = 320;
	s_graphicsoptions.banner.generic.y	   = 16;
	s_graphicsoptions.banner.string  	   = "SYSTEM SETUP";
	s_graphicsoptions.banner.color         = color_white;
	s_graphicsoptions.banner.style         = UI_CENTER;

	s_graphicsoptions.framel.generic.type  = MTYPE_BITMAP;
	s_graphicsoptions.framel.generic.name  = GRAPHICSOPTIONS_FRAMEL;
	s_graphicsoptions.framel.generic.flags = QMF_INACTIVE;
	s_graphicsoptions.framel.generic.x	   = 0;
	s_graphicsoptions.framel.generic.y	   = 78;
	s_graphicsoptions.framel.width  	   = 256;
	s_graphicsoptions.framel.height  	   = 329;

	s_graphicsoptions.framer.generic.type  = MTYPE_BITMAP;
	s_graphicsoptions.framer.generic.name  = GRAPHICSOPTIONS_FRAMER;
	s_graphicsoptions.framer.generic.flags = QMF_INACTIVE;
	s_graphicsoptions.framer.generic.x	   = 376;
	s_graphicsoptions.framer.generic.y	   = 76;
	s_graphicsoptions.framer.width  	   = 256;
	s_graphicsoptions.framer.height  	   = 334;
*/
/* Elder: removed
	s_graphicsoptions.multim.generic.type	= MTYPE_PTEXT;
	s_graphicsoptions.multim.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_graphicsoptions.multim.generic.x		= 120;
	s_graphicsoptions.multim.generic.y		= 3;
	s_graphicsoptions.multim.string			= "MULTIPLAYER";
	s_graphicsoptions.multim.color			= color_red;
	s_graphicsoptions.multim.style			= UI_CENTER | UI_DROPSHADOW;

	s_graphicsoptions.setupm.generic.type	= MTYPE_PTEXT;
	s_graphicsoptions.setupm.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_INACTIVE|QMF_HIGHLIGHT;
	s_graphicsoptions.setupm.generic.x		= 280;
	s_graphicsoptions.setupm.generic.y		= 3;
	s_graphicsoptions.setupm.string			= "SETUP";
	s_graphicsoptions.setupm.color			= color_red;
	s_graphicsoptions.setupm.style			= UI_CENTER | UI_DROPSHADOW;

	s_graphicsoptions.demom.generic.type		= MTYPE_PTEXT;
	s_graphicsoptions.demom.generic.flags	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_graphicsoptions.demom.generic.x		= 390;
	s_graphicsoptions.demom.generic.y		= 3;
	s_graphicsoptions.demom.string			= "DEMOS";
	s_graphicsoptions.demom.color			= color_red;
	s_graphicsoptions.demom.style			= UI_CENTER | UI_DROPSHADOW;

	s_graphicsoptions.modsm.generic.type		= MTYPE_PTEXT;
	s_graphicsoptions.modsm.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_graphicsoptions.modsm.generic.x		= 500;
	s_graphicsoptions.modsm.generic.y		= 3;
	s_graphicsoptions.modsm.string			= "MODS";
	s_graphicsoptions.modsm.color			= color_red;
	s_graphicsoptions.modsm.style			= UI_CENTER | UI_DROPSHADOW;

	s_graphicsoptions.exitm.generic.type		= MTYPE_PTEXT;
	s_graphicsoptions.exitm.generic.flags  	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_graphicsoptions.exitm.generic.x		= 590;
	s_graphicsoptions.exitm.generic.y		= 3;
	s_graphicsoptions.exitm.string			= "EXIT";
	s_graphicsoptions.exitm.color			= color_red;
	s_graphicsoptions.exitm.style			= UI_CENTER | UI_DROPSHADOW;
*/

//Elder: Info for system icon
	s_graphicsoptions.rq3_systemicon.generic.type			= MTYPE_BITMAP;
	s_graphicsoptions.rq3_systemicon.generic.name			= RQ3_SYSTEM_ICON;
	s_graphicsoptions.rq3_systemicon.generic.flags			= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	s_graphicsoptions.rq3_systemicon.generic.x				= 0;
	s_graphicsoptions.rq3_systemicon.generic.y				= 4;
	s_graphicsoptions.rq3_systemicon.width					= RQ3_ICON_WIDTH;
	s_graphicsoptions.rq3_systemicon.height					= RQ3_ICON_HEIGHT;

	//Elder: Info for setup title
	s_graphicsoptions.rq3_setuptitle.generic.type			= MTYPE_BITMAP;
	s_graphicsoptions.rq3_setuptitle.generic.name			= RQ3_SETUP_TITLE;
	s_graphicsoptions.rq3_setuptitle.generic.flags			= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	s_graphicsoptions.rq3_setuptitle.generic.x				= 64;
	s_graphicsoptions.rq3_setuptitle.generic.y				= 12;
	s_graphicsoptions.rq3_setuptitle.width					= 256;
	s_graphicsoptions.rq3_setuptitle.height					= 32;

	//Elder: RQ3 Graphics Button
	s_graphicsoptions.rq3_graphics.generic.type		= MTYPE_BITMAP;
	s_graphicsoptions.rq3_graphics.generic.name		= RQ3_GRAPHICS_BUTTON;
	s_graphicsoptions.rq3_graphics.generic.flags	= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	s_graphicsoptions.rq3_graphics.generic.x		= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	s_graphicsoptions.rq3_graphics.generic.y		= y;
	s_graphicsoptions.rq3_graphics.generic.id		= ID_GRAPHICS;
	s_graphicsoptions.rq3_graphics.generic.callback	= GraphicsOptions_Event;
	s_graphicsoptions.rq3_graphics.width			= RQ3_BUTTON_WIDTH;
	s_graphicsoptions.rq3_graphics.height			= RQ3_BUTTON_HEIGHT;
	s_graphicsoptions.rq3_graphics.focuspic			= RQ3_FOCUS_BUTTON;
	
	//Elder: RQ3 Display Button
	s_graphicsoptions.rq3_display.generic.type		= MTYPE_BITMAP;
	s_graphicsoptions.rq3_display.generic.name		= RQ3_DISPLAY_BUTTON;
	s_graphicsoptions.rq3_display.generic.flags		= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	s_graphicsoptions.rq3_display.generic.x			= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	s_graphicsoptions.rq3_display.generic.y			= y;
	s_graphicsoptions.rq3_display.generic.id		= ID_DISPLAY;
	s_graphicsoptions.rq3_display.generic.callback	= GraphicsOptions_Event;
	s_graphicsoptions.rq3_display.width				= RQ3_BUTTON_WIDTH;
	s_graphicsoptions.rq3_display.height			= RQ3_BUTTON_HEIGHT;
	s_graphicsoptions.rq3_display.focuspic			= RQ3_FOCUS_BUTTON;

	//Elder: RQ3 Sound Button
	s_graphicsoptions.rq3_sound.generic.type		= MTYPE_BITMAP;
	s_graphicsoptions.rq3_sound.generic.name		= RQ3_SOUND_BUTTON;
	s_graphicsoptions.rq3_sound.generic.flags		= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	s_graphicsoptions.rq3_sound.generic.x			= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	s_graphicsoptions.rq3_sound.generic.y			= y;
	s_graphicsoptions.rq3_sound.generic.id			= ID_SOUND;
	s_graphicsoptions.rq3_sound.generic.callback	= GraphicsOptions_Event;
	s_graphicsoptions.rq3_sound.width				= RQ3_BUTTON_WIDTH;
	s_graphicsoptions.rq3_sound.height				= RQ3_BUTTON_HEIGHT;
	s_graphicsoptions.rq3_sound.focuspic			= RQ3_FOCUS_BUTTON;

	//Elder: RQ3 Network Button
	s_graphicsoptions.rq3_network.generic.type		= MTYPE_BITMAP;
	s_graphicsoptions.rq3_network.generic.name		= RQ3_NETWORK_BUTTON;
	s_graphicsoptions.rq3_network.generic.flags		= QMF_LEFT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	s_graphicsoptions.rq3_network.generic.x			= 320 + (RQ3_BUTTON_PADDING + RQ3_BUTTON_WIDTH) * buttonCount++;
	s_graphicsoptions.rq3_network.generic.y			= y;
	s_graphicsoptions.rq3_network.generic.id		= ID_NETWORK;
	s_graphicsoptions.rq3_network.generic.callback	= GraphicsOptions_Event;
	s_graphicsoptions.rq3_network.width				= RQ3_BUTTON_WIDTH;
	s_graphicsoptions.rq3_network.height			= RQ3_BUTTON_HEIGHT;
	s_graphicsoptions.rq3_network.focuspic			= RQ3_FOCUS_BUTTON;

	//Elder: RQ3 Status Text
	s_graphicsoptions.rq3_statustext.generic.type 	= MTYPE_TEXT;
	s_graphicsoptions.rq3_statustext.generic.flags	= QMF_CENTER_JUSTIFY;
	s_graphicsoptions.rq3_statustext.generic.x 		= RQ3_STATUSBAR_X;
	s_graphicsoptions.rq3_statustext.generic.y 		= RQ3_STATUSBAR_Y;
	s_graphicsoptions.rq3_statustext.string 		= "";
	s_graphicsoptions.rq3_statustext.style 			= UI_CENTER|UI_SMALLFONT;
	s_graphicsoptions.rq3_statustext.color 			= color_orange;

	/* Elder: removed for RQ3 stuff
	s_graphicsoptions.graphics.generic.type		= MTYPE_PTEXT;
	s_graphicsoptions.graphics.generic.flags	= QMF_RIGHT_JUSTIFY;
	s_graphicsoptions.graphics.generic.id		= ID_GRAPHICS;
	s_graphicsoptions.graphics.generic.callback	= GraphicsOptions_Event;
	s_graphicsoptions.graphics.generic.x		= 216;
	s_graphicsoptions.graphics.generic.y		= 240 - 2 * PROP_HEIGHT;
	s_graphicsoptions.graphics.string			= "GRAPHICS";
	s_graphicsoptions.graphics.style			= UI_RIGHT;
	s_graphicsoptions.graphics.color			= color_red;

	s_graphicsoptions.display.generic.type		= MTYPE_PTEXT;
	s_graphicsoptions.display.generic.flags		= QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	s_graphicsoptions.display.generic.id		= ID_DISPLAY;
	s_graphicsoptions.display.generic.callback	= GraphicsOptions_Event;
	s_graphicsoptions.display.generic.x			= 216;
	s_graphicsoptions.display.generic.y			= 240 - PROP_HEIGHT;
	s_graphicsoptions.display.string			= "DISPLAY";
	s_graphicsoptions.display.style				= UI_RIGHT;
	s_graphicsoptions.display.color				= color_red;

	s_graphicsoptions.sound.generic.type		= MTYPE_PTEXT;
	s_graphicsoptions.sound.generic.flags		= QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	s_graphicsoptions.sound.generic.id			= ID_SOUND;
	s_graphicsoptions.sound.generic.callback	= GraphicsOptions_Event;
	s_graphicsoptions.sound.generic.x			= 216;
	s_graphicsoptions.sound.generic.y			= 240;
	s_graphicsoptions.sound.string				= "SOUND";
	s_graphicsoptions.sound.style				= UI_RIGHT;
	s_graphicsoptions.sound.color				= color_red;

	s_graphicsoptions.network.generic.type		= MTYPE_PTEXT;
	s_graphicsoptions.network.generic.flags		= QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	s_graphicsoptions.network.generic.id		= ID_NETWORK;
	s_graphicsoptions.network.generic.callback	= GraphicsOptions_Event;
	s_graphicsoptions.network.generic.x			= 216;
	s_graphicsoptions.network.generic.y			= 240 + PROP_HEIGHT;
	s_graphicsoptions.network.string			= "NETWORK";
	s_graphicsoptions.network.style				= UI_RIGHT;
	s_graphicsoptions.network.color				= color_red;
	*/
	
	y = 64;
	s_graphicsoptions.list.generic.type     = MTYPE_SPINCONTROL;
	s_graphicsoptions.list.generic.name     = "Graphics Settings:";
	s_graphicsoptions.list.generic.flags    = QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_graphicsoptions.list.generic.x        = 200;
	s_graphicsoptions.list.generic.y        = y;
	s_graphicsoptions.list.generic.callback = GraphicsOptions_Event;
	s_graphicsoptions.list.generic.id       = ID_LIST;
	s_graphicsoptions.list.itemnames        = s_graphics_options_names;
	y += 2 * ( BIGCHAR_HEIGHT + 2 );

	s_graphicsoptions.driver.generic.type  = MTYPE_SPINCONTROL;
	s_graphicsoptions.driver.generic.name  = "GL Driver:";
	s_graphicsoptions.driver.generic.flags = QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_graphicsoptions.driver.generic.x     = 200;
	s_graphicsoptions.driver.generic.y     = y;
	s_graphicsoptions.driver.itemnames     = s_driver_names;
	s_graphicsoptions.driver.curvalue      = (uis.glconfig.driverType == GLDRV_VOODOO);
	y += BIGCHAR_HEIGHT+2;

	// references/modifies "r_allowExtensions"
	s_graphicsoptions.allow_extensions.generic.type     = MTYPE_SPINCONTROL;
	s_graphicsoptions.allow_extensions.generic.name	    = "GL Extensions:";
	s_graphicsoptions.allow_extensions.generic.flags	= QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_graphicsoptions.allow_extensions.generic.x	    = 200;
	s_graphicsoptions.allow_extensions.generic.y	    = y;
	s_graphicsoptions.allow_extensions.itemnames        = enabled_names;
	y += BIGCHAR_HEIGHT+2;

	// references/modifies "r_mode"
	s_graphicsoptions.mode.generic.type     = MTYPE_SPINCONTROL;
	s_graphicsoptions.mode.generic.name     = "Video Mode:";
	s_graphicsoptions.mode.generic.flags    = QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_graphicsoptions.mode.generic.x        = 200;
	s_graphicsoptions.mode.generic.y        = y;
	s_graphicsoptions.mode.itemnames        = resolutions;
	s_graphicsoptions.mode.generic.callback = GraphicsOptions_Event;
	s_graphicsoptions.mode.generic.id       = ID_MODE;
	y += BIGCHAR_HEIGHT+2;

	// references "r_colorbits"
	s_graphicsoptions.colordepth.generic.type     = MTYPE_SPINCONTROL;
	s_graphicsoptions.colordepth.generic.name     = "Color Depth:";
	s_graphicsoptions.colordepth.generic.flags    = QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_graphicsoptions.colordepth.generic.x        = 200;
	s_graphicsoptions.colordepth.generic.y        = y;
	s_graphicsoptions.colordepth.itemnames        = colordepth_names;
	y += BIGCHAR_HEIGHT+2;

	// references/modifies "r_fullscreen"
	s_graphicsoptions.fs.generic.type     = MTYPE_SPINCONTROL;
	s_graphicsoptions.fs.generic.name	  = "Fullscreen:";
	s_graphicsoptions.fs.generic.flags	  = QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_graphicsoptions.fs.generic.x	      = 200;
	s_graphicsoptions.fs.generic.y	      = y;
	s_graphicsoptions.fs.itemnames	      = enabled_names;
	y += BIGCHAR_HEIGHT+2;

	// references/modifies "r_vertexLight"
	s_graphicsoptions.lighting.generic.type  = MTYPE_SPINCONTROL;
	s_graphicsoptions.lighting.generic.name	 = "Lighting:";
	s_graphicsoptions.lighting.generic.flags = QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_graphicsoptions.lighting.generic.x	 = 200;
	s_graphicsoptions.lighting.generic.y	 = y;
	s_graphicsoptions.lighting.itemnames     = lighting_names;
	y += BIGCHAR_HEIGHT+2;

	// references/modifies "r_lodBias" & "subdivisions"
	s_graphicsoptions.geometry.generic.type  = MTYPE_SPINCONTROL;
	s_graphicsoptions.geometry.generic.name	 = "Geometric Detail:";
	s_graphicsoptions.geometry.generic.flags = QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_graphicsoptions.geometry.generic.x	 = 200;
	s_graphicsoptions.geometry.generic.y	 = y;
	s_graphicsoptions.geometry.itemnames     = quality_names;
	y += BIGCHAR_HEIGHT+2;

	// references/modifies "r_picmip"
	s_graphicsoptions.tq.generic.type	= MTYPE_SLIDER;
	s_graphicsoptions.tq.generic.name	= "Texture Detail:";
	s_graphicsoptions.tq.generic.flags	= QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_graphicsoptions.tq.generic.x		= 200;
	s_graphicsoptions.tq.generic.y		= y;
	s_graphicsoptions.tq.minvalue       = 0;
	s_graphicsoptions.tq.maxvalue       = 3;
	s_graphicsoptions.tq.generic.callback = GraphicsOptions_TQEvent;
	y += BIGCHAR_HEIGHT+2;

	// references/modifies "r_textureBits"
	s_graphicsoptions.texturebits.generic.type  = MTYPE_SPINCONTROL;
	s_graphicsoptions.texturebits.generic.name	= "Texture Quality:";
	s_graphicsoptions.texturebits.generic.flags	= QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_graphicsoptions.texturebits.generic.x	    = 200;
	s_graphicsoptions.texturebits.generic.y	    = y;
	s_graphicsoptions.texturebits.itemnames     = tq_names;
	y += BIGCHAR_HEIGHT+2;

	// references/modifies "r_textureMode"
	s_graphicsoptions.filter.generic.type   = MTYPE_SPINCONTROL;
	s_graphicsoptions.filter.generic.name	= "Texture Filter:";
	s_graphicsoptions.filter.generic.flags	= QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_graphicsoptions.filter.generic.x	    = 200;
	s_graphicsoptions.filter.generic.y	    = y;
	s_graphicsoptions.filter.itemnames      = filter_names;
	y += 2*BIGCHAR_HEIGHT;

	/* Elder: replaced by RQ3 button
	s_graphicsoptions.driverinfo.generic.type     = MTYPE_PTEXT;
	s_graphicsoptions.driverinfo.generic.flags    = QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS;
	s_graphicsoptions.driverinfo.generic.callback = GraphicsOptions_Event;
	s_graphicsoptions.driverinfo.generic.id       = ID_DRIVERINFO;
	s_graphicsoptions.driverinfo.generic.x        = 320;
	s_graphicsoptions.driverinfo.generic.y        = y;
	s_graphicsoptions.driverinfo.string           = "Driver Info";
	s_graphicsoptions.driverinfo.style            = UI_CENTER|UI_SMALLFONT;
	s_graphicsoptions.driverinfo.color            = color_red;
	y += BIGCHAR_HEIGHT+2;
	*/

	s_graphicsoptions.rq3_driverinfo.generic.type		= MTYPE_BITMAP;
	s_graphicsoptions.rq3_driverinfo.generic.name    	= RQ3_DRIVERINFO_BUTTON;
	s_graphicsoptions.rq3_driverinfo.generic.flags    	= QMF_RIGHT_JUSTIFY|QMF_HIGHLIGHT_IF_FOCUS;
	s_graphicsoptions.rq3_driverinfo.generic.callback 	= GraphicsOptions_Event;
	s_graphicsoptions.rq3_driverinfo.generic.id	    	= ID_DRIVERINFO;
	s_graphicsoptions.rq3_driverinfo.generic.x			= 640;
	s_graphicsoptions.rq3_driverinfo.generic.y			= 12;
	s_graphicsoptions.rq3_driverinfo.width  		  	= RQ3_BUTTON_WIDTH;
	s_graphicsoptions.rq3_driverinfo.height  		    = RQ3_BUTTON_HEIGHT;
	s_graphicsoptions.rq3_driverinfo.focuspic         	= RQ3_FOCUS_BUTTON;

	s_graphicsoptions.back.generic.type	    = MTYPE_BITMAP;
	s_graphicsoptions.back.generic.name     = GRAPHICSOPTIONS_BACK0;
	s_graphicsoptions.back.generic.flags    = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	s_graphicsoptions.back.generic.callback = GraphicsOptions_Event;
	s_graphicsoptions.back.generic.id	    = ID_BACK2;
	s_graphicsoptions.back.generic.x		= 8;
	s_graphicsoptions.back.generic.y		= 480-44;
	s_graphicsoptions.back.width  		    = 32;
	s_graphicsoptions.back.height  		    = 32;
	s_graphicsoptions.back.focuspic         = GRAPHICSOPTIONS_BACK1;

	s_graphicsoptions.apply.generic.type     = MTYPE_BITMAP;
	s_graphicsoptions.apply.generic.name     = GRAPHICSOPTIONS_ACCEPT0;
	s_graphicsoptions.apply.generic.flags    = QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_HIDDEN|QMF_INACTIVE;
	s_graphicsoptions.apply.generic.callback = GraphicsOptions_ApplyChanges;
	s_graphicsoptions.apply.generic.x        = 632 ;
	s_graphicsoptions.apply.generic.y        = 480-44;
	s_graphicsoptions.apply.width  		     = 64;
	s_graphicsoptions.apply.height  		 = 32;
	s_graphicsoptions.apply.focuspic         = GRAPHICSOPTIONS_ACCEPT1;

//	Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.banner );
//	Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.framel );
//	Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.framer );
//	Menu_AddItem( &s_graphicsoptions.menu, &s_graphicsoptions.multim );
//	Menu_AddItem( &s_graphicsoptions.menu, &s_graphicsoptions.setupm );
//	Menu_AddItem( &s_graphicsoptions.menu, &s_graphicsoptions.demom );
//	Menu_AddItem( &s_graphicsoptions.menu, &s_graphicsoptions.modsm );
//	Menu_AddItem( &s_graphicsoptions.menu, &s_graphicsoptions.exitm );

	//Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.graphics );
	//Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.display );
	//Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.sound );
	//Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.network );

	//Elder: added
	Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.rq3_systemicon );
	Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.rq3_setuptitle );
	Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.rq3_graphics );
	Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.rq3_display );
	Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.rq3_sound );
	Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.rq3_network );
	Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.rq3_statustext );
	Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.rq3_driverinfo );

	Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.list );
	Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.driver );
	Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.allow_extensions );
	Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.mode );
	Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.colordepth );
	Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.fs );
	Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.lighting );
	Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.geometry );
	Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.tq );
	Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.texturebits );
	Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.filter );
	//Elder: removed
	//Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.driverinfo );

	Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.back );
	Menu_AddItem( &s_graphicsoptions.menu, ( void * ) &s_graphicsoptions.apply );

	GraphicsOptions_SetMenuItems();
	GraphicsOptions_GetInitialVideo();

	if ( uis.glconfig.driverType == GLDRV_ICD &&
		 uis.glconfig.hardwareType == GLHW_3DFX_2D3D )
	{
		s_graphicsoptions.driver.generic.flags |= QMF_HIDDEN|QMF_INACTIVE;
	}
}


/*
=================
GraphicsOptions_Cache
=================
*/
void GraphicsOptions_Cache( void ) {
	//trap_R_RegisterShaderNoMip( GRAPHICSOPTIONS_FRAMEL );
	//trap_R_RegisterShaderNoMip( GRAPHICSOPTIONS_FRAMER );
	trap_R_RegisterShaderNoMip( GRAPHICSOPTIONS_BACK0 );
	trap_R_RegisterShaderNoMip( GRAPHICSOPTIONS_BACK1 );
	trap_R_RegisterShaderNoMip( GRAPHICSOPTIONS_ACCEPT0 );
	trap_R_RegisterShaderNoMip( GRAPHICSOPTIONS_ACCEPT1 );

	//Elder: added
	trap_R_RegisterShaderNoMip( RQ3_SYSTEM_ICON );
	trap_R_RegisterShaderNoMip( RQ3_SETUP_TITLE );
	trap_R_RegisterShaderNoMip( RQ3_GRAPHICS_BUTTON );	
	trap_R_RegisterShaderNoMip( RQ3_DISPLAY_BUTTON );
	trap_R_RegisterShaderNoMip( RQ3_SOUND_BUTTON );	
	trap_R_RegisterShaderNoMip( RQ3_NETWORK_BUTTON );
	trap_R_RegisterShaderNoMip( RQ3_DRIVERINFO_BUTTON );
	trap_R_RegisterShaderNoMip( RQ3_FOCUS_BUTTON );
}


/*
=================
UI_GraphicsOptionsMenu
=================
*/
void UI_GraphicsOptionsMenu( void ) {
	GraphicsOptions_MenuInit();
	UI_PushMenu( &s_graphicsoptions.menu );
	Menu_SetCursorToItem( &s_graphicsoptions.menu, &s_graphicsoptions.rq3_graphics );
}

