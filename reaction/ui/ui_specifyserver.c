// Copyright (C) 1999-2000 Id Software, Inc.
//
#include "ui_local.h"

/*********************************************************************************
	SPECIFY SERVER
*********************************************************************************/

//#define SPECIFYSERVER_FRAMEL	"menu/art/frame2_l"
//#define SPECIFYSERVER_FRAMER	"menu/art/frame1_r"

//#define SPECIFYSERVER_BACK0		"menu/art/back_0"
//#define SPECIFYSERVER_BACK1		"menu/art/back_1"
#define SPECIFYSERVER_BACK0		"menu/art/rq3-menu-back.tga"
#define SPECIFYSERVER_BACK1		"menu/art/rq3-menu-back-focus.tga"	
#define SPECIFYSERVER_FIGHT0	"menu/art/fight_0"
#define SPECIFYSERVER_FIGHT1	"menu/art/fight_1"

//Elder: RQ3 Setup assets
#define RQ3_START_ICON		"menu/art/rq3-menu-start.jpg"
#define RQ3_START_TITLE		"menu/art/rq3-title-start.jpg"

#define ID_SPECIFYSERVERBACK	102
#define ID_SPECIFYSERVERGO		103

static char* specifyserver_artlist[] =
{
	//SPECIFYSERVER_FRAMEL,
	//SPECIFYSERVER_FRAMER,
	SPECIFYSERVER_BACK0,	
	SPECIFYSERVER_BACK1,	
	SPECIFYSERVER_FIGHT0,
	SPECIFYSERVER_FIGHT1,
	NULL
};

typedef struct
{
	menuframework_s	menu;
//Blaze: Dont need this banner
//	menutext_s		banner;
//	menubitmap_s	framel;
//	menubitmap_s	framer;
	/*
	menutext_s		multim;
	menutext_s		setupm;
	menutext_s		demom;
	menutext_s		modsm;
	menutext_s		exitm;
	*/

	
	//Elder: RQ3 Stuff
	menubitmap_s		rq3_starticon;
	menubitmap_s		rq3_starttitle;

	menufield_s		domain;
	menufield_s		port;
	menubitmap_s	go;
	menubitmap_s	back;
} specifyserver_t;

static specifyserver_t	s_specifyserver;


/*
===============
Added by Elder
Preferences_MenuDraw
===============
*/
static void SpecifyServer_MenuDraw( void ) {
	//Elder: "Dim" and "Letterbox" mask
	UI_FillRect( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color_deepdim );
	UI_FillRect( 0, 0, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 54, SCREEN_WIDTH, 2, color_red);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 2, color_red);
	
	// standard menu drawing
	Menu_Draw( &s_specifyserver.menu );
}


/*
=================
SpecifyServer_Event
=================
*/
static void SpecifyServer_Event( void* ptr, int event )
{
	char	buff[256];

	switch (((menucommon_s*)ptr)->id)
	{
		case ID_SPECIFYSERVERGO:
			if (event != QM_ACTIVATED)
				break;

			if (s_specifyserver.domain.field.buffer[0])
			{
				strcpy(buff,s_specifyserver.domain.field.buffer);
				if (s_specifyserver.port.field.buffer[0])
					Com_sprintf( buff+strlen(buff), 128, ":%s", s_specifyserver.port.field.buffer );

				trap_Cmd_ExecuteText( EXEC_APPEND, va( "connect %s\n", buff ) );
			}
			break;

		case ID_SPECIFYSERVERBACK:
			if (event != QM_ACTIVATED)
				break;

			UI_PopMenu();
			break;
	}
}

/*
=================
SpecifyServer_MenuInit
=================
*/
void SpecifyServer_MenuInit( void )
{
	// zero set all our globals
	memset( &s_specifyserver, 0 ,sizeof(specifyserver_t) );

	SpecifyServer_Cache();

	s_specifyserver.menu.draw = SpecifyServer_MenuDraw;
	s_specifyserver.menu.wrapAround = qtrue;
	s_specifyserver.menu.fullscreen = qtrue;
	s_specifyserver.menu.showlogo	= qtrue;

//Blaze: This banner is not needed
/*	s_specifyserver.banner.generic.type	 = MTYPE_BTEXT;
	s_specifyserver.banner.generic.x     = 320;
	s_specifyserver.banner.generic.y     = 16;
	s_specifyserver.banner.string		 = "SPECIFY SERVER";
	s_specifyserver.banner.color  		 = color_white;
	s_specifyserver.banner.style  		 = UI_CENTER;
*/

	//Blaze: This is not needed
/*	s_specifyserver.framel.generic.type  = MTYPE_BITMAP;
	s_specifyserver.framel.generic.name  = SPECIFYSERVER_FRAMEL;
	s_specifyserver.framel.generic.flags = QMF_INACTIVE;
	s_specifyserver.framel.generic.x	 = 0;  
	s_specifyserver.framel.generic.y	 = 78;
	s_specifyserver.framel.width  	     = 256;
	s_specifyserver.framel.height  	     = 329;

	s_specifyserver.framer.generic.type  = MTYPE_BITMAP;
	s_specifyserver.framer.generic.name  = SPECIFYSERVER_FRAMER;
	s_specifyserver.framer.generic.flags = QMF_INACTIVE;
	s_specifyserver.framer.generic.x	 = 376;
	s_specifyserver.framer.generic.y	 = 76;
	s_specifyserver.framer.width  	     = 256;
	s_specifyserver.framer.height  	     = 334;
*/
	/*
	s_specifyserver.multim.generic.type		= MTYPE_PTEXT;
	s_specifyserver.multim.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_INACTIVE|QMF_HIGHLIGHT;
	s_specifyserver.multim.generic.x		= 120;
	s_specifyserver.multim.generic.y		= 3;
	s_specifyserver.multim.string			= "MULTIPLAYER";
	s_specifyserver.multim.color			= color_red;
	s_specifyserver.multim.style			= UI_CENTER | UI_DROPSHADOW;

	s_specifyserver.setupm.generic.type		= MTYPE_PTEXT;
	s_specifyserver.setupm.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_specifyserver.setupm.generic.x		= 280;
	s_specifyserver.setupm.generic.y		= 3;
	s_specifyserver.setupm.string			= "SETUP";
	s_specifyserver.setupm.color			= color_red;
	s_specifyserver.setupm.style			= UI_CENTER | UI_DROPSHADOW;

	s_specifyserver.demom.generic.type		= MTYPE_PTEXT;
	s_specifyserver.demom.generic.flags		= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_specifyserver.demom.generic.x			= 390;
	s_specifyserver.demom.generic.y			= 3;
	s_specifyserver.demom.string			= "DEMOS";
	s_specifyserver.demom.color				= color_red;
	s_specifyserver.demom.style				= UI_CENTER | UI_DROPSHADOW;

	s_specifyserver.modsm.generic.type		= MTYPE_PTEXT;
//Note the following line, this makes it highlight
	s_specifyserver.modsm.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_specifyserver.modsm.generic.x			= 500;
	s_specifyserver.modsm.generic.y			= 3;
	s_specifyserver.modsm.string			= "MODS";
	s_specifyserver.modsm.color				= color_red;
	s_specifyserver.modsm.style				= UI_CENTER | UI_DROPSHADOW;

	s_specifyserver.exitm.generic.type		= MTYPE_PTEXT;
	s_specifyserver.exitm.generic.flags  	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_specifyserver.exitm.generic.x			= 590;
	s_specifyserver.exitm.generic.y			= 3;
	s_specifyserver.exitm.string			= "EXIT";
	s_specifyserver.exitm.color				= color_red;
	s_specifyserver.exitm.style				= UI_CENTER | UI_DROPSHADOW;
	*/

	//Elder: Info for setup icon
	s_specifyserver.rq3_starticon.generic.type				= MTYPE_BITMAP;
	s_specifyserver.rq3_starticon.generic.name				= RQ3_START_ICON;
	s_specifyserver.rq3_starticon.generic.flags				= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	s_specifyserver.rq3_starticon.generic.x					= 0;
	s_specifyserver.rq3_starticon.generic.y					= 4;
	s_specifyserver.rq3_starticon.width						= RQ3_ICON_WIDTH;
	s_specifyserver.rq3_starticon.height						= RQ3_ICON_HEIGHT;

	//Elder: Info for setup title
	s_specifyserver.rq3_starttitle.generic.type				= MTYPE_BITMAP;
	s_specifyserver.rq3_starttitle.generic.name				= RQ3_START_TITLE;
	s_specifyserver.rq3_starttitle.generic.flags				= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	s_specifyserver.rq3_starttitle.generic.x					= 64;
	s_specifyserver.rq3_starttitle.generic.y					= 12;
	s_specifyserver.rq3_starttitle.width						= 256;
	s_specifyserver.rq3_starttitle.height					= 32;


	s_specifyserver.domain.generic.type       = MTYPE_FIELD;
	s_specifyserver.domain.generic.name       = "Address:";
	s_specifyserver.domain.generic.flags      = QMF_PULSEIFFOCUS|QMF_SMALLFONT;
	s_specifyserver.domain.generic.x	      = 206;
	s_specifyserver.domain.generic.y	      = 220;
	s_specifyserver.domain.field.widthInChars = 38;
	s_specifyserver.domain.field.maxchars     = 80;

	s_specifyserver.port.generic.type       = MTYPE_FIELD;
	s_specifyserver.port.generic.name	    = "Port:";
	s_specifyserver.port.generic.flags	    = QMF_PULSEIFFOCUS|QMF_SMALLFONT|QMF_NUMBERSONLY;
	s_specifyserver.port.generic.x	        = 206;
	s_specifyserver.port.generic.y	        = 250;
	s_specifyserver.port.field.widthInChars = 6;
	s_specifyserver.port.field.maxchars     = 5;

	s_specifyserver.go.generic.type	    = MTYPE_BITMAP;
	s_specifyserver.go.generic.name     = SPECIFYSERVER_FIGHT0;
	s_specifyserver.go.generic.flags    = QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	s_specifyserver.go.generic.callback = SpecifyServer_Event;
	s_specifyserver.go.generic.id	    = ID_SPECIFYSERVERGO;
	s_specifyserver.go.generic.x		= 640-8;
	s_specifyserver.go.generic.y		= 480-44;
	s_specifyserver.go.width  		    = 64;
	s_specifyserver.go.height  		    = 32;
	s_specifyserver.go.focuspic         = SPECIFYSERVER_FIGHT1;

	s_specifyserver.back.generic.type	  = MTYPE_BITMAP;
	s_specifyserver.back.generic.name     = SPECIFYSERVER_BACK0;
	s_specifyserver.back.generic.flags    = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	s_specifyserver.back.generic.callback = SpecifyServer_Event;
	s_specifyserver.back.generic.id	      = ID_SPECIFYSERVERBACK;
	s_specifyserver.back.generic.x		  = 8;
	s_specifyserver.back.generic.y		  = 480-44;
	s_specifyserver.back.width  		  = 32;
	s_specifyserver.back.height  		  = 32;
	s_specifyserver.back.focuspic         = SPECIFYSERVER_BACK1;

	//Blaze: This banner is not needed
	//Menu_AddItem( &s_specifyserver.menu, &s_specifyserver.banner );
	//Menu_AddItem( &s_specifyserver.menu, &s_specifyserver.framel );
	//Menu_AddItem( &s_specifyserver.menu, &s_specifyserver.framer );
	/*
	Menu_AddItem( &s_specifyserver.menu, &s_specifyserver.multim );
	Menu_AddItem( &s_specifyserver.menu, &s_specifyserver.setupm );
	Menu_AddItem( &s_specifyserver.menu, &s_specifyserver.demom );
	Menu_AddItem( &s_specifyserver.menu, &s_specifyserver.modsm );
	Menu_AddItem( &s_specifyserver.menu, &s_specifyserver.exitm );
	*/

	Menu_AddItem( &s_specifyserver.menu, &s_specifyserver.rq3_starticon );
	Menu_AddItem( &s_specifyserver.menu, &s_specifyserver.rq3_starttitle );
	Menu_AddItem( &s_specifyserver.menu, &s_specifyserver.domain );
	Menu_AddItem( &s_specifyserver.menu, &s_specifyserver.port );
	Menu_AddItem( &s_specifyserver.menu, &s_specifyserver.go );
	Menu_AddItem( &s_specifyserver.menu, &s_specifyserver.back );

	Com_sprintf( s_specifyserver.port.field.buffer, 6, "%i", 27960 );
}

/*
=================
SpecifyServer_Cache
=================
*/
void SpecifyServer_Cache( void )
{
	int	i;

	// touch all our pics
	for (i=0; ;i++)
	{
		if (!specifyserver_artlist[i])
			break;
		trap_R_RegisterShaderNoMip(specifyserver_artlist[i]);
	}
}

/*
=================
UI_SpecifyServerMenu
=================
*/
void UI_SpecifyServerMenu( void )
{
	SpecifyServer_MenuInit();
	UI_PushMenu( &s_specifyserver.menu );
}

