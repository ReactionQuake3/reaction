// Copyright (C) 1999-2000 Id Software, Inc.
//
/*
=======================================================================

DEMOS MENU

=======================================================================
*/


#include "ui_local.h"

//Elder: changed to RQ3 graphics
#define ART_BACK0			"menu/art/rq3-menu-back.tga"
#define ART_BACK1			"menu/art/rq3-menu-back-focus.tga"	
#define ART_GO0				"menu/art/rq3-menu-play.tga"
#define ART_GO1				"menu/art/rq3-menu-play-focus.tga"
//Elder: removed
//#define ART_FRAMEL			"menu/art/frame2_l"
//#define ART_FRAMER			"menu/art/frame1_r"
#define ART_ARROWS			"menu/art/arrows_horz_0"
#define ART_ARROWLEFT		"menu/art/arrows_horz_left"
#define ART_ARROWRIGHT		"menu/art/arrows_horz_right"

#define MAX_DEMOS			128
#define NAMEBUFSIZE			( MAX_DEMOS * 16 )

#define ID_BACK				10
#define ID_GO				11
#define ID_LIST				12
#define ID_RIGHT			13
#define ID_LEFT				14

#define ARROWS_WIDTH		128
#define ARROWS_HEIGHT		48

//Elder: RQ3 stuff
#define RQ3_DEMOS_ICON		"menu/art/rq3-menu-demos.tga"
#define RQ3_DEMOS_TITLE		"menu/art/rq3-title-demos.tga"

typedef struct {
	menuframework_s	menu;

//Blaze: Dont need this
//	menutext_s		banner;
//	menubitmap_s	framel;
//	menubitmap_s	framer;
//Elder: Removed for new interface
//	menutext_s		multim;
//	menutext_s		setupm;
//	menutext_s		demom;
//	menutext_s		modsm;
//	menutext_s		exitm;

	menulist_s		list;

	menubitmap_s	arrows;
	menubitmap_s	left;
	menubitmap_s	right;
	menubitmap_s	back;
	menubitmap_s	go;

	menubitmap_s	rq3_demosicon;
	menubitmap_s	rq3_demostitle;

	int				numDemos;
	char			names[NAMEBUFSIZE];
	char			*demolist[MAX_DEMOS];
} demos_t;

static demos_t	s_demos;


/*
===============
Demos_MenuEvent
===============
*/
static void Demos_MenuEvent( void *ptr, int event ) {
	if( event != QM_ACTIVATED ) {
		return;
	}

	switch( ((menucommon_s*)ptr)->id ) {
	case ID_GO:
		UI_ForceMenuOff ();
		trap_Cmd_ExecuteText( EXEC_APPEND, va( "demo %s\n",
								s_demos.list.itemnames[s_demos.list.curvalue]) );
		break;

	case ID_BACK:
		UI_PopMenu();
		break;

	case ID_LEFT:
		ScrollList_Key( &s_demos.list, K_LEFTARROW );
		break;

	case ID_RIGHT:
		ScrollList_Key( &s_demos.list, K_RIGHTARROW );
		break;
	}
}


/*
=================
UI_DemosMenu_Key
=================
*/
static sfxHandle_t UI_DemosMenu_Key( int key ) {
	menucommon_s	*item;

	item = Menu_ItemAtCursor( &s_demos.menu );

	return Menu_DefaultKey( &s_demos.menu, key );
}

/*
===============
Added by Elder
Demos_MenuDraw
===============
*/
static void Demos_MenuDraw( void ) {
	//Elder: "Dim" and "Letterbox" mask
	UI_FillRect( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color_deepdim );
	UI_FillRect( 0, 0, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 54, color_black);
	UI_FillRect( 0, 54, SCREEN_WIDTH, 2, color_red);
	UI_FillRect( 0, 426, SCREEN_WIDTH, 2, color_red);
	
	// standard menu drawing
	Menu_Draw( &s_demos.menu );
}


/*
===============
Demos_MenuInit
===============
*/
static void Demos_MenuInit( void ) {
	int		i;
	int		len;
	char	*demoname, extension[32];

	memset( &s_demos, 0 ,sizeof(demos_t) );
	s_demos.menu.key = UI_DemosMenu_Key;

	Demos_Cache();
	s_demos.menu.draw = Demos_MenuDraw;
	s_demos.menu.fullscreen = qtrue;
	s_demos.menu.wrapAround = qtrue;
	s_demos.menu.showlogo = qtrue;//Blaze: Show Background logo

//Blaze: dont need this
/*
	s_demos.banner.generic.type		= MTYPE_BTEXT;
	s_demos.banner.generic.x		= 320;
	s_demos.banner.generic.y		= 16;
	s_demos.banner.string			= "DEMOS";
	s_demos.banner.color			= color_white;
	s_demos.banner.style			= UI_CENTER;

	s_demos.framel.generic.type		= MTYPE_BITMAP;
	s_demos.framel.generic.name		= ART_FRAMEL;
	s_demos.framel.generic.flags	= QMF_INACTIVE;
	s_demos.framel.generic.x		= 0;  
	s_demos.framel.generic.y		= 78;
	s_demos.framel.width			= 256;
	s_demos.framel.height			= 329;

	s_demos.framer.generic.type		= MTYPE_BITMAP;
	s_demos.framer.generic.name		= ART_FRAMER;
	s_demos.framer.generic.flags	= QMF_INACTIVE;
	s_demos.framer.generic.x		= 376;
	s_demos.framer.generic.y		= 76;
	s_demos.framer.width			= 256;
	s_demos.framer.height			= 334;
*/
/*Elder: Removed for new interface
	s_demos.multim.generic.type		= MTYPE_PTEXT;
	s_demos.multim.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_demos.multim.generic.x		= 120;
	s_demos.multim.generic.y		= 3;
	s_demos.multim.string			= "MULTIPLAYER";
	s_demos.multim.color			= color_red;
	s_demos.multim.style			= UI_CENTER | UI_DROPSHADOW;

	s_demos.setupm.generic.type		= MTYPE_PTEXT;
	s_demos.setupm.generic.flags 	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_demos.setupm.generic.x		= 280;
	s_demos.setupm.generic.y		= 3;
	s_demos.setupm.string			= "SETUP";
	s_demos.setupm.color			= color_red;
	s_demos.setupm.style			= UI_CENTER | UI_DROPSHADOW;

	s_demos.demom.generic.type		= MTYPE_PTEXT;
	s_demos.demom.generic.flags		= QMF_CENTER_JUSTIFY|QMF_INACTIVE|QMF_HIGHLIGHT;
	s_demos.demom.generic.x			= 390;
	s_demos.demom.generic.y			= 3;
	s_demos.demom.string			= "DEMOS";
	s_demos.demom.color				= color_red;
	s_demos.demom.style				= UI_CENTER | UI_DROPSHADOW;

	s_demos.modsm.generic.type		= MTYPE_PTEXT;
	s_demos.modsm.generic.flags		= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_demos.modsm.generic.x			= 500;
	s_demos.modsm.generic.y			= 3;
	s_demos.modsm.string			= "MODS";
	s_demos.modsm.color				= color_red;
	s_demos.modsm.style				= UI_CENTER | UI_DROPSHADOW;

	s_demos.exitm.generic.type		= MTYPE_PTEXT;
	s_demos.exitm.generic.flags  	= QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS|QMF_INACTIVE;
	s_demos.exitm.generic.x			= 590;
	s_demos.exitm.generic.y			= 3;
	s_demos.exitm.string			= "EXIT";
	s_demos.exitm.color				= color_red;
	s_demos.exitm.style				= UI_CENTER | UI_DROPSHADOW;
*/

	//Elder: Info for demos icon
	s_demos.rq3_demosicon.generic.type				= MTYPE_BITMAP;
	s_demos.rq3_demosicon.generic.name				= RQ3_DEMOS_ICON;
	s_demos.rq3_demosicon.generic.flags				= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	s_demos.rq3_demosicon.generic.x					= 0;
	s_demos.rq3_demosicon.generic.y					= 4;
	s_demos.rq3_demosicon.width						= RQ3_ICON_WIDTH;
	s_demos.rq3_demosicon.height					= RQ3_ICON_HEIGHT;

	//Elder: Info for demos title
	s_demos.rq3_demostitle.generic.type				= MTYPE_BITMAP;
	s_demos.rq3_demostitle.generic.name				= RQ3_DEMOS_TITLE;
	s_demos.rq3_demostitle.generic.flags			= QMF_LEFT_JUSTIFY|QMF_INACTIVE;
	s_demos.rq3_demostitle.generic.x				= 64;
	s_demos.rq3_demostitle.generic.y				= 12;
	s_demos.rq3_demostitle.width					= 256;
	s_demos.rq3_demostitle.height					= 32;

	s_demos.arrows.generic.type		= MTYPE_BITMAP;
	s_demos.arrows.generic.name		= ART_ARROWS;
	s_demos.arrows.generic.flags	= QMF_INACTIVE;
	s_demos.arrows.generic.x		= 320-ARROWS_WIDTH/2;
	s_demos.arrows.generic.y		= 430;
	s_demos.arrows.width			= ARROWS_WIDTH;
	s_demos.arrows.height			= ARROWS_HEIGHT;

	s_demos.left.generic.type		= MTYPE_BITMAP;
	s_demos.left.generic.flags		= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_MOUSEONLY;
	s_demos.left.generic.x			= 320-ARROWS_WIDTH/2;
	s_demos.left.generic.y			= 430;
	s_demos.left.generic.id			= ID_LEFT;
	s_demos.left.generic.callback	= Demos_MenuEvent;
	s_demos.left.width				= ARROWS_WIDTH/2;
	s_demos.left.height				= ARROWS_HEIGHT;
	s_demos.left.focuspic			= ART_ARROWLEFT;

	s_demos.right.generic.type		= MTYPE_BITMAP;
	s_demos.right.generic.flags		= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS|QMF_MOUSEONLY;
	s_demos.right.generic.x			= 320;
	s_demos.right.generic.y			= 430;
	s_demos.right.generic.id		= ID_RIGHT;
	s_demos.right.generic.callback	= Demos_MenuEvent;
	s_demos.right.width				= ARROWS_WIDTH/2;
	s_demos.right.height			= ARROWS_HEIGHT;
	s_demos.right.focuspic			= ART_ARROWRIGHT;

	s_demos.back.generic.type		= MTYPE_BITMAP;
	s_demos.back.generic.name		= ART_BACK0;
	s_demos.back.generic.flags		= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	s_demos.back.generic.id			= ID_BACK;
	s_demos.back.generic.callback	= Demos_MenuEvent;
	s_demos.back.generic.x			= 8;
	s_demos.back.generic.y			= 480-44;
	s_demos.back.width				= 32;
	s_demos.back.height				= 32;
	s_demos.back.focuspic			= ART_BACK1;

	s_demos.go.generic.type			= MTYPE_BITMAP;
	s_demos.go.generic.name			= ART_GO0;
	s_demos.go.generic.flags		= QMF_RIGHT_JUSTIFY|QMF_PULSEIFFOCUS;
	s_demos.go.generic.id			= ID_GO;
	s_demos.go.generic.callback		= Demos_MenuEvent;
	s_demos.go.generic.x			= 635;
	s_demos.go.generic.y			= 480-44;
	s_demos.go.width				= 32;
	s_demos.go.height				= 32;
	s_demos.go.focuspic				= ART_GO1;

	s_demos.list.generic.type		= MTYPE_SCROLLLIST;
	s_demos.list.generic.flags		= QMF_PULSEIFFOCUS;
	s_demos.list.generic.callback	= Demos_MenuEvent;
	s_demos.list.generic.id			= ID_LIST;
	s_demos.list.generic.x			= 100;
	s_demos.list.generic.y			= 64;
	s_demos.list.width				= 16;
	s_demos.list.height				= 14;
	Com_sprintf(extension, sizeof(extension), "dm_%d", (int)trap_Cvar_VariableValue( "protocol" ) );
	s_demos.list.numitems			= trap_FS_GetFileList( "demos", extension, s_demos.names, NAMEBUFSIZE );
	s_demos.list.itemnames			= (const char **)s_demos.demolist;
	s_demos.list.columns			= 3;

	if (!s_demos.list.numitems) {
		strcpy( s_demos.names, "No Demos Found." );
		s_demos.list.numitems = 1;

		//degenerate case, not selectable
		s_demos.go.generic.flags |= (QMF_INACTIVE|QMF_HIDDEN);
	}
	else if (s_demos.list.numitems > MAX_DEMOS)
		s_demos.list.numitems = MAX_DEMOS;

	demoname = s_demos.names;
	for ( i = 0; i < s_demos.list.numitems; i++ ) {
		s_demos.list.itemnames[i] = demoname;
		
		// strip extension
		len = strlen( demoname );
		if (!Q_stricmp(demoname +  len - 4,".dm3"))
			demoname[len-4] = '\0';

		Q_strupr(demoname);

		demoname += len + 1;
	}
//Blaze: dont need this
//	Menu_AddItem( &s_demos.menu, &s_demos.banner );
//	Menu_AddItem( &s_demos.menu, &s_demos.framel );
//	Menu_AddItem( &s_demos.menu, &s_demos.framer );
//Elder: removed for new interface
//	Menu_AddItem( &s_demos.menu, &s_demos.multim );
//	Menu_AddItem( &s_demos.menu, &s_demos.setupm );
//	Menu_AddItem( &s_demos.menu, &s_demos.demom );
//	Menu_AddItem( &s_demos.menu, &s_demos.modsm );
//	Menu_AddItem( &s_demos.menu, &s_demos.exitm );
//Elder: new UI stuff
	Menu_AddItem( &s_demos.menu, &s_demos.rq3_demosicon );
	Menu_AddItem( &s_demos.menu, &s_demos.rq3_demostitle );

	Menu_AddItem( &s_demos.menu, &s_demos.list );
	Menu_AddItem( &s_demos.menu, &s_demos.arrows );
	Menu_AddItem( &s_demos.menu, &s_demos.left );
	Menu_AddItem( &s_demos.menu, &s_demos.right );
	Menu_AddItem( &s_demos.menu, &s_demos.back );
	Menu_AddItem( &s_demos.menu, &s_demos.go );
}

/*
=================
Demos_Cache
=================
*/
void Demos_Cache( void ) {
	trap_R_RegisterShaderNoMip( ART_BACK0 );
	trap_R_RegisterShaderNoMip( ART_BACK1 );
	trap_R_RegisterShaderNoMip( ART_GO0 );
	trap_R_RegisterShaderNoMip( ART_GO1 );
	//Elder: removed
	//trap_R_RegisterShaderNoMip( ART_FRAMEL );
	//trap_R_RegisterShaderNoMip( ART_FRAMER );
	trap_R_RegisterShaderNoMip( ART_ARROWS );
	trap_R_RegisterShaderNoMip( ART_ARROWLEFT );
	trap_R_RegisterShaderNoMip( ART_ARROWRIGHT );
	//Elder: RQ3 stuff
	trap_R_RegisterShaderNoMip( RQ3_DEMOS_ICON );
	trap_R_RegisterShaderNoMip( RQ3_DEMOS_TITLE );
}

/*
===============
UI_DemosMenu
===============
*/
void UI_DemosMenu( void ) {
	Demos_MenuInit();
	UI_PushMenu( &s_demos.menu );
}
