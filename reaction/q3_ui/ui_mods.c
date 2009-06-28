//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.7  2002/01/11 19:48:30  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.6  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
#include "ui_local.h"

//Elder: changed filenames
#define ART_BACK0			"menu/art/rq3-menu-back.tga"
#define ART_BACK1			"menu/art/rq3-menu-back-focus.tga"	
#define ART_FIGHT0			"menu/art/rq3-menu-go.tga"
#define ART_FIGHT1			"menu/art/rq3-menu-go-focus.tga"
//Elder: removed
//#define ART_FRAMEL			"menu/art/frame2_l"
//#define ART_FRAMER			"menu/art/frame1_r"

#define MAX_MODS			64
#define NAMEBUFSIZE			( MAX_MODS * 48 )
#define GAMEBUFSIZE			( MAX_MODS * 16 )

#define ID_BACK				10
#define ID_GO				11
#define ID_LIST				12

//Elder: RQ3 assets
#define RQ3_MODS_ICON		"menu/art/rq3-menu-mods.tga"
#define RQ3_MODS_TITLE		"menu/art/rq3-title-mods.jpg"

typedef struct {
	menuframework_s	menu;

//Blaze: Dont need this
//	menutext_s		banner;
//	menubitmap_s	framel;
//	menubitmap_s	framer;
//Elder: Don't need these anymore
//	menutext_s      multim;
//	menutext_s		setupm;
//	menutext_s		demom;
//	menutext_s		modsm;
//	menutext_s		exitm;

	menulist_s		list;

	menubitmap_s	back;
	menubitmap_s	go;

	char			description[NAMEBUFSIZE];
	char			fs_game[GAMEBUFSIZE];

	char			*descriptionPtr;
	char			*fs_gamePtr;

	char			*descriptionList[MAX_MODS];
	char			*fs_gameList[MAX_MODS];
	
	menubitmap_s	rq3_modsicon;
	menubitmap_s	rq3_modstitle;
} mods_t;

static mods_t	s_mods;


/*
===============
UI_Mods_MenuEvent
===============
*/
static void UI_Mods_MenuEvent( void *ptr, int event ) {
	if( event != QM_ACTIVATED ) {
		return;
	}

	switch ( ((menucommon_s*)ptr)->id ) {
	case ID_GO:
		trap_Cvar_Set( "fs_game", s_mods.fs_gameList[s_mods.list.curvalue] );
		trap_Cmd_ExecuteText( EXEC_APPEND, "vid_restart;" );
		UI_PopMenu();
		break;

	case ID_BACK:
		UI_PopMenu();
		break;
	}
}


/*
===============
UI_Mods_ParseInfos
===============
*/
static void UI_Mods_ParseInfos( char *modDir, char *modDesc ) {
	s_mods.fs_gameList[s_mods.list.numitems] = s_mods.fs_gamePtr;
	Q_strncpyz( s_mods.fs_gamePtr, modDir, 16 );

	s_mods.descriptionList[s_mods.list.numitems] = s_mods.descriptionPtr;
	Q_strncpyz( s_mods.descriptionPtr, modDesc, 48 );

	s_mods.list.itemnames[s_mods.list.numitems] = s_mods.descriptionPtr;
	s_mods.descriptionPtr += strlen( s_mods.descriptionPtr ) + 1;
	s_mods.fs_gamePtr += strlen( s_mods.fs_gamePtr ) + 1;
	s_mods.list.numitems++;
}


#if 0 // bk001204 - unused
/*
===============
UI_Mods_LoadModsFromFile
===============
*/
static void UI_Mods_LoadModsFromFile( char *filename ) {
	int				len;
	fileHandle_t	f;
	char			buf[1024];

	len = trap_FS_FOpenFile( filename, &f, FS_READ );
	if ( !f ) {
		trap_Print( va( S_COLOR_RED "file not found: %s\n", filename ) );
		return;
	}
	if ( len >= sizeof(buf) ) {
		trap_Print( va( S_COLOR_RED "file too large: %s is %i, max allowed is %i", filename, len, sizeof(buf) ) );
		trap_FS_FCloseFile( f );
		return;
	}

	trap_FS_Read( buf, len, f );
	buf[len] = 0;
	trap_FS_FCloseFile( f );

	len = strlen( filename );
	if( !Q_stricmp(filename +  len - 4,".mod") ) {
		filename[len-4] = '\0';
	}

	UI_Mods_ParseInfos( filename, buf );
}
#endif


/*
===============
UI_Mods_LoadMods
===============
*/
static void UI_Mods_LoadMods( void ) {
	int		numdirs;
	char	dirlist[2048];
	char	*dirptr;
  char  *descptr;
	int		i;
	int		dirlen;

	s_mods.list.itemnames = (const char **)s_mods.descriptionList;
	s_mods.descriptionPtr = s_mods.description;
	s_mods.fs_gamePtr = s_mods.fs_game;

	// always start off with baseq3
	s_mods.list.numitems = 1;
	s_mods.list.itemnames[0] = s_mods.descriptionList[0] = "Quake III Arena";
	s_mods.fs_gameList[0] = "";

	numdirs = trap_FS_GetFileList( "$modlist", "", dirlist, sizeof(dirlist) );
	dirptr  = dirlist;
	for( i = 0; i < numdirs; i++ ) {
		dirlen = strlen( dirptr ) + 1;
    descptr = dirptr + dirlen;
  	UI_Mods_ParseInfos( dirptr, descptr);
    dirptr += dirlen + strlen(descptr) + 1;
	}

	trap_Print( va( "%i mods parsed\n", s_mods.list.numitems ) );
	if (s_mods.list.numitems > MAX_MODS) {
		s_mods.list.numitems = MAX_MODS;
	}
}

/*
===============
Added by Elder
UI_Mods_MenuDraw
===============
*/
static void UI_Mods_MenuDraw( void ) {
	//Elder: "Dim" and "Letterbox" mask
	UI_FillRect( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color_deepdim );
	UI_FillRect( 0, 0, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 54, SCREEN_WIDTH, 2, color_red);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 2, color_red);
	
	// standard menu drawing
	Menu_Draw( &s_mods.menu );
}

/*
===============
UI_Mods_MenuInit
===============
*/
static void UI_Mods_MenuInit( void ) {
	

	memset( &s_mods, 0 ,sizeof(mods_t) );
	UI_ModsMenu_Cache();//Blaze: Moved below the memset
	s_mods.menu.draw = UI_Mods_MenuDraw;
	s_mods.menu.wrapAround = qtrue;
	s_mods.menu.fullscreen = qtrue;//Blaze: full screen
	s_mods.menu.showlogo = qtrue;//Blaze: Show background logo

//Blaze: Dont need this
/*	s_mods.banner.generic.type		= MTYPE_BTEXT;
	s_mods.banner.generic.x			= 320;
	s_mods.banner.generic.y			= 16;
	s_mods.banner.string			= "MODS";
	s_mods.banner.color				= color_white;
	s_mods.banner.style				= UI_CENTER;

	s_mods.framel.generic.type		= MTYPE_BITMAP;
	s_mods.framel.generic.name		= ART_FRAMEL;
	s_mods.framel.generic.flags		= QMF_INACTIVE;
	s_mods.framel.generic.x			= 0;  
	s_mods.framel.generic.y			= 78;
	s_mods.framel.width				= 256;
	s_mods.framel.height			= 329;

	s_mods.framer.generic.type		= MTYPE_BITMAP;
	s_mods.framer.generic.name		= ART_FRAMER;
	s_mods.framer.generic.flags		= QMF_INACTIVE;
	s_mods.framer.generic.x			= 376;
	s_mods.framer.generic.y			= 76;
	s_mods.framer.width				= 256;
	s_mods.framer.height			= 334;
*/

/* Elder: Don't need these either
	s_mods.multim.generic.type	= MTYPE_PTEXT;
	s_mods.multim.generic.flags = QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_mods.multim.generic.x		= 120;
	s_mods.multim.generic.y		= 3;
	s_mods.multim.string		= "MULTIPLAYER";
	s_mods.multim.color			= color_red;
	s_mods.multim.style			= UI_CENTER | UI_DROPSHADOW;

	s_mods.setupm.generic.type	= MTYPE_PTEXT;
	s_mods.setupm.generic.flags = QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_mods.setupm.generic.x		= 280;
	s_mods.setupm.generic.y		= 3;
	s_mods.setupm.string		= "SETUP";
	s_mods.setupm.color			= color_red;
	s_mods.setupm.style			= UI_CENTER | UI_DROPSHADOW;

	s_mods.demom.generic.type	= MTYPE_PTEXT;
	s_mods.demom.generic.flags	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_mods.demom.generic.x		= 390;
	s_mods.demom.generic.y		= 3;
	s_mods.demom.string			= "DEMOS";
	s_mods.demom.color			= color_red;
	s_mods.demom.style			= UI_CENTER | UI_DROPSHADOW;

	s_mods.modsm.generic.type	= MTYPE_PTEXT;
	s_mods.modsm.generic.flags  = QMF_CENTER_JUSTIFY|QMF_INACTIVE|QMF_HIGHLIGHT;
	s_mods.modsm.generic.x		= 500;
	s_mods.modsm.generic.y		= 3;
	s_mods.modsm.string			= "MODS";
	s_mods.modsm.color			= color_red;
	s_mods.modsm.style			= UI_CENTER | UI_DROPSHADOW;

	s_mods.exitm.generic.type	= MTYPE_PTEXT;
	s_mods.exitm.generic.flags  = QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_mods.exitm.generic.x		= 590;
	s_mods.exitm.generic.y		= 3;
	s_mods.exitm.string			= "EXIT";
	s_mods.exitm.color			= color_red;
	s_mods.exitm.style			= UI_CENTER | UI_DROPSHADOW;
*/

	//Elder: Info for mods icon
	s_mods.rq3_modsicon.generic.type				= MTYPE_BITMAP;
	s_mods.rq3_modsicon.generic.name				= RQ3_MODS_ICON;
	s_mods.rq3_modsicon.generic.flags				= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	s_mods.rq3_modsicon.generic.x					= 0;
	s_mods.rq3_modsicon.generic.y					= 4;
	s_mods.rq3_modsicon.width						= RQ3_ICON_WIDTH;
	s_mods.rq3_modsicon.height						= RQ3_ICON_HEIGHT;

	//Elder: Info for mods title
	s_mods.rq3_modstitle.generic.type				= MTYPE_BITMAP;
	s_mods.rq3_modstitle.generic.name				= RQ3_MODS_TITLE;
	s_mods.rq3_modstitle.generic.flags				= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	s_mods.rq3_modstitle.generic.x					= 64;
	s_mods.rq3_modstitle.generic.y					= 12;
	s_mods.rq3_modstitle.width						= 256;
	s_mods.rq3_modstitle.height						= 32;

	
	//Back button
	s_mods.back.generic.type				= MTYPE_BITMAP;
	s_mods.back.generic.name				= ART_BACK0;
	s_mods.back.generic.flags				= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	s_mods.back.generic.id					= ID_BACK;
	s_mods.back.generic.callback			= UI_Mods_MenuEvent;
	s_mods.back.generic.x					= 8;
	s_mods.back.generic.y					= 480-44;
	s_mods.back.width						= 32;
	s_mods.back.height						= 32;
	s_mods.back.focuspic					= ART_BACK1;
	
	//Elder: some metric changes
	s_mods.go.generic.type			= MTYPE_BITMAP;
	s_mods.go.generic.name			= ART_FIGHT0;
	s_mods.go.generic.flags			= QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	s_mods.go.generic.id			= ID_GO;
	s_mods.go.generic.callback		= UI_Mods_MenuEvent;
	s_mods.go.generic.x				= 632;
	s_mods.go.generic.y				= 480-44;
	s_mods.go.width					= 64;
	s_mods.go.height				= 32;
	s_mods.go.focuspic				= ART_FIGHT1;

	// scan for mods
	s_mods.list.generic.type		= MTYPE_SCROLLLIST;
	s_mods.list.generic.flags		= QMF_PULSEIFFOCUS|QMF_CENTER_JUSTIFY;
	s_mods.list.generic.callback	= UI_Mods_MenuEvent;
	s_mods.list.generic.id			= ID_LIST;
	s_mods.list.generic.x			= 320;
	//Elder: Readjusted height
	s_mods.list.generic.y			= 64;
	s_mods.list.width				= 48;
	s_mods.list.height				= 14;

	UI_Mods_LoadMods();

//Blaze: Dont need this
//	Menu_AddItem( &s_mods.menu, &s_mods.banner );
//	Menu_AddItem( &s_mods.menu, &s_mods.framel );
//	Menu_AddItem( &s_mods.menu, &s_mods.framer );
//Elder: Don't need these
//	Menu_AddItem( &s_mods.menu, &s_mods.multim );
//	Menu_AddItem( &s_mods.menu, &s_mods.setupm );
//	Menu_AddItem( &s_mods.menu, &s_mods.demom );
//	Menu_AddItem( &s_mods.menu, &s_mods.modsm );
//	Menu_AddItem( &s_mods.menu, &s_mods.exitm );

	//Elder: Added
	Menu_AddItem( &s_mods.menu, &s_mods.rq3_modsicon );
	Menu_AddItem( &s_mods.menu, &s_mods.rq3_modstitle );

	Menu_AddItem( &s_mods.menu, &s_mods.list );
	Menu_AddItem( &s_mods.menu, &s_mods.back );
	Menu_AddItem( &s_mods.menu, &s_mods.go );
}

/*
=================
UI_Mods_Cache
=================
*/
void UI_ModsMenu_Cache( void ) {
	trap_R_RegisterShaderNoMip( ART_BACK0 );
	trap_R_RegisterShaderNoMip( ART_BACK1 );
	trap_R_RegisterShaderNoMip( ART_FIGHT0 );
	trap_R_RegisterShaderNoMip( ART_FIGHT1 );
	//Elder: Removed
	//trap_R_RegisterShaderNoMip( ART_FRAMEL );
	//trap_R_RegisterShaderNoMip( ART_FRAMER );
	//Elder: Added
	trap_R_RegisterShaderNoMip( RQ3_MODS_ICON );
	trap_R_RegisterShaderNoMip( RQ3_MODS_TITLE );
}


/*
===============
UI_ModsMenu
===============
*/
void UI_ModsMenu( void ) {

	UI_Mods_MenuInit();

	UI_PushMenu( &s_mods.menu );
}
