//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.27  2002/05/31 19:01:33  makro
// Unfixed something
//
// Revision 1.26  2002/05/31 00:17:06  jbravo
// Slicers fix for the weaponswitching issue
//
// Revision 1.25  2002/05/28 21:06:37  jbravo
// I broke the progressbar.  Final fix for that
//
// Revision 1.24  2002/05/28 03:10:50  jbravo
// My fixups broke stuff
//
// Revision 1.23  2002/05/27 17:47:19  jbravo
// Fixes and cleanups
//
// Revision 1.22  2002/05/26 06:17:27  makro
// Loading screen again
//
// Revision 1.21  2002/05/26 05:15:16  niceass
// pregress bar
//
// Revision 1.20  2002/05/26 05:00:19  makro
// Loading screen
//
// Revision 1.19  2002/05/25 16:39:16  makro
// Loading screen
//
// Revision 1.18  2002/05/25 10:40:31  makro
// Loading screen
//
// Revision 1.17  2002/05/24 18:41:34  makro
// Loading screen
//
// Revision 1.16  2002/05/02 23:04:59  makro
// Loading screen. Jump kicks
//
// Revision 1.15  2002/05/02 12:44:07  makro
// Customizable color for the loading screen text
//
// Revision 1.14  2002/03/31 03:31:24  jbravo
// Compiler warning cleanups
//
// Revision 1.13  2002/03/24 21:24:51  makro
// Added a drop-shadow effect to the loading screen
//
// Revision 1.12  2002/03/03 18:10:20  makro
// Changed the colors for the 'loading map' screen a bit
//
// Revision 1.11  2002/01/11 20:20:57  jbravo
// Adding TP to main branch
//
// Revision 1.10  2002/01/11 19:48:29  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.9  2001/12/31 16:28:41  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
// cg_info.c -- display information while data is being loading

#include "cg_local.h"

#define MAX_LOADING_PLAYER_ICONS	16
#define MAX_LOADING_ITEM_ICONS		26

static int			loadingPlayerIconCount;
static int			loadingItemIconCount;
static qhandle_t	loadingPlayerIcons[MAX_LOADING_PLAYER_ICONS];
static qhandle_t	loadingItemIcons[MAX_LOADING_ITEM_ICONS];


/*
===================
CG_DrawLoadingIcons
===================
// JBravo: apparently not used.
*/
/*
static void CG_DrawLoadingIcons( void ) {
	int		n;
	int		x, y;

	for( n = 0; n < loadingPlayerIconCount; n++ ) {
		x = 16 + n * 78;
		y = 324-40;
		CG_DrawPic( x, y, 64, 64, loadingPlayerIcons[n] );
	}

	for( n = 0; n < loadingItemIconCount; n++ ) {
		y = 400-40;
		if( n >= 13 ) {
			y += 40;
		}
		x = 16 + n % 13 * 48;
		CG_DrawPic( x, y, 32, 32, loadingItemIcons[n] );
	}
}
*/

/*
======================
CG_LoadingString

======================
*/
void CG_LoadingString( const char *s ) {
	Q_strncpyz( cg.infoScreenText, s, sizeof( cg.infoScreenText ) );

	trap_UpdateScreen();
}

/*
===================
CG_LoadingItem
===================
*/
void CG_LoadingItem( int itemNum ) {
	gitem_t		*item;

	item = &bg_itemlist[itemNum];
	
	if ( item->icon && loadingItemIconCount < MAX_LOADING_ITEM_ICONS ) {
		loadingItemIcons[loadingItemIconCount++] = trap_R_RegisterShaderNoMip( item->icon );
	}

	CG_LoadingString( item->pickup_name );
}

/*
===================
CG_LoadingClient
===================
*/
void CG_LoadingClient( int clientNum ) {
	const char		*info;
	char			*skin;
	char			personality[MAX_QPATH];
	char			model[MAX_QPATH];
	char			iconName[MAX_QPATH];

	info = CG_ConfigString( CS_PLAYERS + clientNum );

	if ( loadingPlayerIconCount < MAX_LOADING_PLAYER_ICONS ) {
		Q_strncpyz( model, Info_ValueForKey( info, "model" ), sizeof( model ) );
		skin = Q_strrchr( model, '/' );
		if ( skin ) {
			*skin++ = '\0';
		} else {
			skin = "default";
		}

		Com_sprintf( iconName, MAX_QPATH, "models/players/%s/icon_%s.tga", model, skin );
		
		loadingPlayerIcons[loadingPlayerIconCount] = trap_R_RegisterShaderNoMip( iconName );
		if ( !loadingPlayerIcons[loadingPlayerIconCount] ) {
			Com_sprintf( iconName, MAX_QPATH, "models/players/characters/%s/icon_%s.tga", model, skin );
			loadingPlayerIcons[loadingPlayerIconCount] = trap_R_RegisterShaderNoMip( iconName );
		}
		if ( !loadingPlayerIcons[loadingPlayerIconCount] ) {
			// Elder: changed
			Com_sprintf( iconName, MAX_QPATH, "models/players/%s/icon_%s.tga", DEFAULT_MODEL, DEFAULT_SKIN );
			//Com_sprintf( iconName, MAX_QPATH, "models/players/%s/icon_%s.tga", DEFAULT_MODEL, "default" );
			loadingPlayerIcons[loadingPlayerIconCount] = trap_R_RegisterShaderNoMip( iconName );
		}
		if ( loadingPlayerIcons[loadingPlayerIconCount] ) {
			loadingPlayerIconCount++;
		}
	}

	Q_strncpyz( personality, Info_ValueForKey( info, "n" ), sizeof(personality) );
	Q_CleanStr( personality );

	if( cgs.gametype == GT_SINGLE_PLAYER ) {
		trap_S_RegisterSound( va( "sound/player/announce/%s.wav", personality ), qtrue );
	}

	CG_LoadingString( personality );
}


/*
====================
CG_DrawInformation

Draw all the status / pacifier stuff during level loading
====================
*/
#define LS_TOPMARGIN			72
#define LS_BOTTOMMARGIN			48
#define LS_CHAR_WIDTH			8
#define LS_CHAR_HEIGHT			12

void CG_DrawInformation( void ) {
	const char	*s;
	const char	*info;
	const char	*sysInfo;
	char		*line;
	int			x = 8, y, value, bar = 0;
	qhandle_t	levelshot, shadow;
	//qhandle_t	detail;
	qhandle_t	percentBox;
	char		buf[1024];
	qboolean	skipdetail;
	vec4_t		color1 = {.75, .75, .75, 1}, color2 = {1, 1, 1, 1};

	skipdetail = qfalse;

	info = CG_ConfigString( CS_SERVERINFO );
	sysInfo = CG_ConfigString( CS_SYSTEMINFO );

	/* Makro - no longer used
	//Makro - settings read from the worldspawn entity
	s = CG_ConfigString( CS_LOADINGSCREEN );
	color1[0] = atof(Info_ValueForKey(s, "r1"));
	color1[1] = atof(Info_ValueForKey(s, "g1"));
	color1[2] = atof(Info_ValueForKey(s, "b1"));
	color2[0] = atof(Info_ValueForKey(s, "r2"));
	color2[1] = atof(Info_ValueForKey(s, "g2"));
	color2[2] = atof(Info_ValueForKey(s, "b2"));
	color1[3] = color2[3] = 1;
	skipdetail = ( atoi(Info_ValueForKey(s, "nodetail")) != 0 ); 
	*/

	s = Info_ValueForKey( info, "mapname" );
	shadow = trap_R_RegisterShaderNoMip("ui/assets/rq3-main-shadow-1.tga");
	levelshot = trap_R_RegisterShaderNoMip( va( "levelshots/%s.tga", s ) );
	percentBox = trap_R_RegisterShaderNoMip("gfx/percent.tga");
	if ( !levelshot ) {
		//Elder: changed
		levelshot = trap_R_RegisterShaderNoMip( "levelshots/rq3-unknownmap.tga" );
		skipdetail = qtrue;
	}
	trap_R_SetColor( NULL );
	CG_DrawPic( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, levelshot );

	/* Makro - removed
	// blend a detail texture over it
	//Elder: changed to RQ3 detail overlay
	if (!skipdetail) {
		detail = trap_R_RegisterShader( "rq3-levelShotDetail" );
		trap_R_DrawStretchPic( 0, 0, cgs.glconfig.vidWidth, cgs.glconfig.vidHeight, 0, 0, 2.5, 2, detail );
	}
	*/

	//Elder: "Letterbox" mask
	//Makro - changed it a bit
	CG_FillRect( 0, 0, SCREEN_WIDTH, LS_TOPMARGIN, colorBlack);
	CG_FillRect( 0, LS_TOPMARGIN, SCREEN_WIDTH, 2, colorMdGrey);
	CG_FillRect( 0, SCREEN_HEIGHT - LS_BOTTOMMARGIN, SCREEN_WIDTH, LS_BOTTOMMARGIN, colorBlack);
	CG_FillRect( 0, SCREEN_HEIGHT - LS_BOTTOMMARGIN - 2, SCREEN_WIDTH, 2, colorMdGrey);
	//Makro - shadow
	CG_DrawPic( 0, LS_TOPMARGIN + 2, 640, 12, shadow );

	//Elder: mapname
	//Makro - removed
	//UI_DrawProportionalString(x, 26, s, UI_LEFT|UI_DROPSHADOW, colorDkGrey);
	//CG_DrawBigStringColor(4, 24, s, color_red);

	//Elder: removed
	// draw the icons of things as they are loaded
	//CG_DrawLoadingIcons();

	// draw info string information

	//Elder: Initial y-position
	y = LS_TOPMARGIN - 8 - LS_CHAR_HEIGHT;

	// map-specific message (long map name)
	s = CG_ConfigString( CS_MESSAGE );
	if ( s[0] ) {
		//Makro - allow color-coded text; also changed to use custom color instead of colorLtGrey
		//CG_DrawSmallStringColor(x, y, s, colorMdGrey);
		//CG_DrawStringExt(x, y, s, colorWhite, qtrue, qfalse, LS_CHAR_WIDTH, LS_CHAR_HEIGHT, 0);
		CG_DrawStringExt(x, y, s, color1, qtrue, qfalse, LS_CHAR_WIDTH, LS_CHAR_HEIGHT, 0);

		y -= (2 * LS_CHAR_HEIGHT);
	}

	//y += LS_CHAR_HEIGHT;
	// game type
	switch ( cgs.gametype ) {
	case GT_FFA:
		line = "CLASSIC ACTION DEATHMATCH";
		break;
	case GT_SINGLE_PLAYER:
		line = "SINGLE PLAYER";
		break;
	case GT_TOURNAMENT:
		line = "TOURNAMENT";
		break;
	case GT_TEAM:
		line = "TEAM DEATHMATCH";
		break;
// JBravo: teamplay stuff.
	case GT_TEAMPLAY:
		//Makro - changed from RQ3 Teamplay
		line = "CLASSIC ACTION TEAMPLAY";
		break;
	case GT_CTF:
		line = "CAPTURE THE FLAG";
		break;
#ifdef MISSIONPACK
	case GT_1FCTF:
		line = "ONE FLAG CTF";
		break;
	case GT_OBELISK:
		line = "OVERLOAD";
		break;
	case GT_HARVESTER:
		line = "HARVESTER";
		break;
#endif
	default:
		line = "UNKNOWN GAMETYPE";
		break;
	}

// JBravo: the call to Q_strupr seems to crash Q3 when running as dll or .so. Attempting a fix
// Makro: the fix crashes Q3 with .dll's, unfixing ;P
	//strcat (line, '\0');
	//line = Q_strupr(line);

	// cheats warning
	s = Info_ValueForKey( sysInfo, "sv_cheats" );
	//Makro - didn't like this
	//if ( s[0] == '1' ) {
	if ( atoi(s) ) {
		line = va("%s / CHEATS ARE ENABLED", line);
	}
		
	//Makro - custom color; changed from colorWhite
	//CG_DrawSmallStringColor(x, y, line, color2);
	CG_DrawStringExt(x, y, line, color2, qfalse, qfalse, LS_CHAR_WIDTH, LS_CHAR_HEIGHT, 0);
	y -= LS_CHAR_HEIGHT;

	line = "";
	// pure server
	s = Info_ValueForKey( sysInfo, "sv_pure" );
	if ( atoi(s) ) {
		if (line[0]) line = va("%s / ", line);
		line = va("%sPURE SERVER", line);
	}

	value = atoi( Info_ValueForKey( info, "timelimit" ) );
	if ( value ) {
		line = va("TIMELIMIT %i", value);
	}

	if (cgs.gametype <= GT_TEAM ) {
		value = atoi( Info_ValueForKey( info, "fraglimit" ) );
		if ( value ) {
			if (line[0]) line = va("%s / ", line);
			line = va("%sFRAGLIMIT %i", line, value);
		}
	} else if (cgs.gametype == GT_TEAMPLAY) {
		value = atoi( Info_ValueForKey( info, "g_RQ3_roundlimit" ) );
		if ( value ) {
			if (line[0]) line = va("%s / ", line);
			line = va("%sROUNDLIMIT %i", line, value);
		}
	} else {
		value = atoi( Info_ValueForKey( info, "capturelimit" ) );
		if ( value ) {
			if (line[0]) line = va("%s / ", line);
			line = va("%sCAPTURELIMIT %i", line, value);
		}
	}

	//Makro - don't write unless there's something to write
	if ( line[0] ) {
		CG_DrawStringExt(x, y, line, color2, qfalse, qfalse, LS_CHAR_WIDTH, LS_CHAR_HEIGHT, 0);
		y -= LS_CHAR_HEIGHT;
	}

	line = "";
	// don't print server lines if playing a local game
	trap_Cvar_VariableStringBuffer( "sv_running", buf, sizeof( buf ) );
	if ( !atoi( buf ) ) {
	
		// server hostname
		Q_strncpyz(buf, Info_ValueForKey( info, "sv_hostname" ), 1024);
		Q_CleanStr(buf);
		if (buf[0] && Q_stricmp(buf, "noname")) {
			line = va("%s", buf);
		}

		// server-specific message of the day
		s = CG_ConfigString( CS_MOTD );
		if ( s[0] ) {
			if (line[0]) line = va("%s / ", line);
			line = va("%s%s", line, s);
		}

		//Makro - don't write unless there's something to write
		if ( line[0] ) {
			CG_DrawStringExt(x, y, line, color2, qfalse, qfalse, LS_CHAR_WIDTH, LS_CHAR_HEIGHT, 0);
			y -= LS_CHAR_HEIGHT;
		}
	}

	// BOTTOM //

	// the first 150 rows are reserved for the client connection
	// screen to write into
	//y = SCREEN_HEIGHT - (int) (0.5 * (LS_BOTTOMMARGIN + LS_CHAR_HEIGHT));
	y = SCREEN_HEIGHT - LS_BOTTOMMARGIN + 8;
	if ( cg.infoScreenText[0] ) {
		CG_DrawStringExt(x, y, va("LOADING... %s", Q_strupr(cg.infoScreenText)), color2, qfalse, qfalse, LS_CHAR_WIDTH, LS_CHAR_HEIGHT, 0);
		//UI_DrawProportionalString(SCREEN_WIDTH - 8, y, va("LOADING... %s", Q_strupr(cg.infoScreenText)), UI_RIGHT, colorWhite);
	} else {
		CG_DrawStringExt(x, y, "AWAITING SNAPSHOT...", color2, qfalse, qfalse, LS_CHAR_WIDTH, LS_CHAR_HEIGHT, 0);
		//UI_DrawProportionalString(SCREEN_WIDTH - 8, y, "AWAITING SNAPSHOT...", UI_RIGHT, colorWhite);
	}

	//y += 24;

	if (percentBox) {
		trap_R_SetColor(colorWhite);
		for (bar = 0; bar < ceil(cg.loadingMapPercent * 10) && bar < 10; bar++) {
			CG_DrawPic(SCREEN_WIDTH - (11 - bar) * 10, y, 8, 8, percentBox);
		}

		trap_R_SetColor(colorDkGrey);
		for (; bar < 10; bar++) {
			CG_DrawPic(SCREEN_WIDTH - (11 - bar) * 10, y, 8, 8, percentBox);
		}
	} else {
		for (bar = 0; bar < ceil(cg.loadingMapPercent * 10) && bar < 10; bar++) {
			CG_FillRect( SCREEN_WIDTH - (11 - bar) * 10, y, 8, 8, colorWhite);
		}

		for (; bar < 10; bar++) {
			CG_FillRect( SCREEN_WIDTH - (11 - bar) * 10, y, 8, 8, colorDkGrey);
		}
	}

}
