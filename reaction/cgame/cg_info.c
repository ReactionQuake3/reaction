//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
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
#define LOADING_SCREEN_TOPMARGIN		64
#define LOADING_SCREEN_BOTTOMMARGIN		32

void CG_DrawInformation( void ) {
	const char	*s;
	const char	*info;
	const char	*sysInfo;
	const char	*line;
	int			x = 8;
	int			y;
	int			value;
	qhandle_t	levelshot, shadow;
	qhandle_t	detail;
	char		buf[1024];
	qboolean	skipdetail;
	vec4_t		color1 = {.75, .75, .75, 1}, color2 = {1, 1, 1, 1};

	skipdetail = qfalse;

	info = CG_ConfigString( CS_SERVERINFO );
	sysInfo = CG_ConfigString( CS_SYSTEMINFO );

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

	s = Info_ValueForKey( info, "mapname" );
	shadow = trap_R_RegisterShaderNoMip("ui/assets/rq3-main-shadow-1.tga");
	levelshot = trap_R_RegisterShaderNoMip( va( "levelshots/%s.tga", s ) );
	if ( !levelshot ) {
		//Elder: changed
		levelshot = trap_R_RegisterShaderNoMip( "levelshots/rq3-unknownmap.tga" );
		skipdetail = qtrue;
	}
	trap_R_SetColor( NULL );
	CG_DrawPic( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, levelshot );

	// blend a detail texture over it
	//Elder: changed to RQ3 detail overlay
	if (!skipdetail) {
		detail = trap_R_RegisterShader( "rq3-levelShotDetail" );
		trap_R_DrawStretchPic( 0, 0, cgs.glconfig.vidWidth, cgs.glconfig.vidHeight, 0, 0, 2.5, 2, detail );
	}

	//Elder: "Letterbox" mask
	//Makro - changed it a bit
	CG_FillRect( 0, 0, SCREEN_WIDTH, LOADING_SCREEN_TOPMARGIN, colorBlack);
	CG_FillRect( 0, LOADING_SCREEN_TOPMARGIN, SCREEN_WIDTH, 2, colorMdGrey);
	CG_FillRect( 0, SCREEN_HEIGHT - LOADING_SCREEN_BOTTOMMARGIN, SCREEN_WIDTH, LOADING_SCREEN_BOTTOMMARGIN, colorBlack);
	CG_FillRect( 0, SCREEN_HEIGHT - LOADING_SCREEN_BOTTOMMARGIN - 2, SCREEN_WIDTH, 2, colorMdGrey);
	//Makro - shadow
	CG_DrawPic( 0, LOADING_SCREEN_TOPMARGIN + 2, 640, 12, shadow );

	//Elder: mapname
	//Makro - removed
	//UI_DrawProportionalString(x, 26, s, UI_LEFT|UI_DROPSHADOW, colorDkGrey);
	//CG_DrawBigStringColor(4, 24, s, color_red);

	//Elder: removed
	// draw the icons of things as they are loaded
	//CG_DrawLoadingIcons();

	// the first 150 rows are reserved for the client connection
	// screen to write into
	y = SCREEN_HEIGHT - (int) (0.5 * (LOADING_SCREEN_BOTTOMMARGIN + SMALLCHAR_HEIGHT));
	if ( cg.infoScreenText[0] ) {
		CG_DrawSmallStringColor(x, y, va("LOADING... %s", Q_strupr(cg.infoScreenText)), colorWhite);
	} else {
		CG_DrawSmallStringColor( x, y, "AWAITING SNAPSHOT...", colorWhite);
	}

	// draw info string information

	//Elder: Initial y-position
	y = 8;

	// map-specific message (long map name)
	s = CG_ConfigString( CS_MESSAGE );
	if ( s[0] ) {
		//Makro - allow color-coded texts; also changed to use custom color instead of colorLtGrey
		//CG_DrawSmallStringColor(x, y, s, colorMdGrey);
		CG_DrawStringExt(x, y, s, color1, qfalse, qfalse, SMALLCHAR_WIDTH, SMALLCHAR_HEIGHT, 0);
		//CG_DrawStringExt(x, y, s, colorWhite, qtrue, qfalse, SMALLCHAR_WIDTH, SMALLCHAR_HEIGHT, 0);

		y += SMALLCHAR_HEIGHT;
	}

	// don't print server lines if playing a local game
	trap_Cvar_VariableStringBuffer( "sv_running", buf, sizeof( buf ) );
	if ( !atoi( buf ) ) {
	
		// server hostname
		Q_strncpyz(buf, Info_ValueForKey( info, "sv_hostname" ), 1024);
		Q_CleanStr(buf);
		//Makro - custom color; changed from colorWhite
		CG_DrawSmallStringColor(x, y, buf, color2);
		y += SMALLCHAR_HEIGHT;

		// pure server
		s = Info_ValueForKey( sysInfo, "sv_pure" );
		if ( s[0] == '1' ) {
			//Makro - custom color; changed from colorWhite
			CG_DrawSmallStringColor(x, y, "PURE SERVER", color2);
			y += SMALLCHAR_HEIGHT;
		}

		// server-specific message of the day
		s = CG_ConfigString( CS_MOTD );
		if ( s[0] ) {
			//Makro - custom color; changed from colorWhite
			UI_DrawProportionalString( x, 360, s, UI_LEFT|UI_SMALLFONT, color2 );
			y += PROP_HEIGHT;
		}

	}

	//y += SMALLCHAR_HEIGHT;
	// game type
	switch ( cgs.gametype ) {
	case GT_FFA:
		line = "CLASSIC ACTION DEATHMATCH";
		break;
	case GT_SINGLE_PLAYER:
		line = "Single Player";
		break;
	case GT_TOURNAMENT:
		line = "Tournament";
		break;
	case GT_TEAM:
		line = "Team Deathmatch";
		break;
// JBravo: teamplay stuff.
	case GT_TEAMPLAY:
		//Makro - changed from RQ3 Teamplay
		line = "CLASSIC ACTION TEAMPLAY";
		break;
	case GT_CTF:
		line = "Capture The Flag";
		break;
#ifdef MISSIONPACK
	case GT_1FCTF:
		line = "One Flag CTF";
		break;
	case GT_OBELISK:
		line = "Overload";
		break;
	case GT_HARVESTER:
		line = "Harvester";
		break;
#endif
	default:
		line = "Unknown Gametype";
		break;
	}
	// cheats warning
	s = Info_ValueForKey( sysInfo, "sv_cheats" );
	if ( s[0] == '1' ) {
		line = va("%s / CHEATS ARE ENABLED", line);
	}
		
	//Makro - custom color; changed from colorWhite
	CG_DrawSmallStringColor(x, y, line, color2);
	y += SMALLCHAR_HEIGHT;

	line = "";
	value = atoi( Info_ValueForKey( info, "timelimit" ) );
	if ( value ) {
		line = va("TIMELIMIT %i", value);
	}

	if (cgs.gametype < GT_CTF ) {
		value = atoi( Info_ValueForKey( info, "fraglimit" ) );
		if ( value ) {
			if (line[0] != '\0') line = va("%s /", line);
			line = va("%s FRAGLIMIT %i", line, value);
		}
	}

	if (cgs.gametype >= GT_CTF) {
		value = atoi( Info_ValueForKey( info, "capturelimit" ) );
		if ( value ) {
			if (line[0] != '\0') line = va("%s /", line);
			line = va("%s CAPTURELIMIT %i", line, value);
		}
	}

	//Makro - custom color; changed from colorWhite
	CG_DrawSmallStringColor(x, y, line, color2);
	y += SMALLCHAR_HEIGHT;

}

