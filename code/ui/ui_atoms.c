//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.22  2005/09/07 20:24:33  makro
// Vector support for most item types
//
// Revision 1.21  2005/02/15 16:33:39  makro
// Tons of updates (entity tree attachment system, UI vectors)
//
// Revision 1.20  2003/03/31 00:23:18  makro
// Replacements and stuff
//
// Revision 1.19  2002/12/09 00:58:49  makro
// Items are now disabled from the weapon/item menus in teamplay
// games if they are banned from the server
//
// Revision 1.18  2002/11/09 14:17:51  makro
// Cleaned up about menu code
// Made the weapon menu unavailable in TDM if g_RQ3_tdmMode is not 0
//
// Revision 1.17  2002/10/29 01:34:52  jbravo
// Added g_RQ3_tdmMode (0 = TP style, 1 = DM style) including UI support.
//
// Revision 1.16  2002/09/01 21:15:47  makro
// no message
//
// Revision 1.15  2002/08/26 00:41:52  makro
// Presets menu + editor
//
// Revision 1.14  2002/07/02 09:51:29  makro
// In-game server info code
//
// Revision 1.13  2002/06/24 12:29:43  makro
// Enabled weapon/item menus in CTF
//
// Revision 1.12  2002/06/16 20:06:14  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.11  2002/05/29 13:30:19  makro
// Weapon/join menu tweaks
//
// Revision 1.10  2002/04/30 11:56:54  makro
// Stuff
//
// Revision 1.9  2002/04/07 17:51:49  makro
// Abbey
//
// Revision 1.8  2002/03/31 13:23:26  makro
// Cleaned things up a little
//
// Revision 1.7  2002/03/24 21:26:15  makro
// no message
//
// Revision 1.6  2002/03/14 21:52:08  makro
// no message
//
// Revision 1.5  2002/03/10 22:10:10  makro
// no message
//
// Revision 1.4  2002/03/03 21:22:58  makro
// no message
//
// Revision 1.3  2002/02/21 20:10:16  jbravo
// Converted files back from M$ format and added cvs headers again.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
/**********************************************************************
	UI_ATOMS.C

	User interface building blocks and support functions.
**********************************************************************/
#include "ui_local.h"

qboolean m_entersound;		// after a frame, so caching won't disrupt the sound

// these are here so the functions in q_shared.c can link
#ifndef UI_HARD_LINKED

void QDECL Com_Error(int level, const char *error, ...)
{
	va_list argptr;
	char text[1024];

	va_start(argptr, error);
	Q_vsnprintf(text, sizeof(text), error, argptr);
	va_end(argptr);

	trap_Error(va("%s", text));
}

void QDECL Com_Printf(const char *msg, ...)
{
	va_list argptr;
	char text[1024];

	va_start(argptr, msg);
	Q_vsnprintf(text, sizeof(text), msg, argptr);
	va_end(argptr);

	trap_Print(va("%s", text));
}

#endif

qboolean newUI = qfalse;

/*
=================
UI_ClampCvar
=================
*/
float UI_ClampCvar(float min, float max, float value)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

/*
=================
UI_StartDemoLoop
=================
*/
void UI_StartDemoLoop(void)
{
	trap_Cmd_ExecuteText(EXEC_APPEND, "d1\n");
}

//Makro - not used anywhere
/*
#ifndef MISSIONPACK // bk001206
static void NeedCDAction( qboolean result ) {
	if ( !result ) {
		trap_Cmd_ExecuteText( EXEC_APPEND, "quit\n" );
	}
}
#endif // MISSIONPACK

#ifndef MISSIONPACK // bk001206
static void NeedCDKeyAction( qboolean result ) {
	if ( !result ) {
		trap_Cmd_ExecuteText( EXEC_APPEND, "quit\n" );
	}
}
#endif // MISSIONPACK
*/

char *UI_Argv(int arg)
{
	static char buffer[MAX_STRING_CHARS];

	trap_Argv(arg, buffer, sizeof(buffer));

	return buffer;
}

char *UI_Cvar_VariableString(const char *var_name)
{
	static char buffer[MAX_STRING_CHARS];

	trap_Cvar_VariableStringBuffer(var_name, buffer, sizeof(buffer));

	return buffer;
}

void UI_SetBestScores(postGameInfo_t * newInfo, qboolean postGame)
{
	trap_Cvar_Set("ui_scoreAccuracy", va("%i%%", newInfo->accuracy));
	trap_Cvar_Set("ui_scoreImpressives", va("%i", newInfo->impressives));
	trap_Cvar_Set("ui_scoreExcellents", va("%i", newInfo->excellents));
	trap_Cvar_Set("ui_scoreDefends", va("%i", newInfo->defends));
	trap_Cvar_Set("ui_scoreAssists", va("%i", newInfo->assists));
	trap_Cvar_Set("ui_scoreGauntlets", va("%i", newInfo->gauntlets));
	trap_Cvar_Set("ui_scoreScore", va("%i", newInfo->score));
	trap_Cvar_Set("ui_scorePerfect", va("%i", newInfo->perfects));
	trap_Cvar_Set("ui_scoreTeam", va("%i to %i", newInfo->redScore, newInfo->blueScore));
	trap_Cvar_Set("ui_scoreBase", va("%i", newInfo->baseScore));
	trap_Cvar_Set("ui_scoreTimeBonus", va("%i", newInfo->timeBonus));
	trap_Cvar_Set("ui_scoreSkillBonus", va("%i", newInfo->skillBonus));
	trap_Cvar_Set("ui_scoreShutoutBonus", va("%i", newInfo->shutoutBonus));
	trap_Cvar_Set("ui_scoreTime", va("%02i:%02i", newInfo->time / 60, newInfo->time % 60));
	trap_Cvar_Set("ui_scoreCaptures", va("%i", newInfo->captures));
	if (postGame) {
		trap_Cvar_Set("ui_scoreAccuracy2", va("%i%%", newInfo->accuracy));
		trap_Cvar_Set("ui_scoreImpressives2", va("%i", newInfo->impressives));
		trap_Cvar_Set("ui_scoreExcellents2", va("%i", newInfo->excellents));
		trap_Cvar_Set("ui_scoreDefends2", va("%i", newInfo->defends));
		trap_Cvar_Set("ui_scoreAssists2", va("%i", newInfo->assists));
		trap_Cvar_Set("ui_scoreGauntlets2", va("%i", newInfo->gauntlets));
		trap_Cvar_Set("ui_scoreScore2", va("%i", newInfo->score));
		trap_Cvar_Set("ui_scorePerfect2", va("%i", newInfo->perfects));
		trap_Cvar_Set("ui_scoreTeam2", va("%i to %i", newInfo->redScore, newInfo->blueScore));
		trap_Cvar_Set("ui_scoreBase2", va("%i", newInfo->baseScore));
		trap_Cvar_Set("ui_scoreTimeBonus2", va("%i", newInfo->timeBonus));
		trap_Cvar_Set("ui_scoreSkillBonus2", va("%i", newInfo->skillBonus));
		trap_Cvar_Set("ui_scoreShutoutBonus2", va("%i", newInfo->shutoutBonus));
		trap_Cvar_Set("ui_scoreTime2", va("%02i:%02i", newInfo->time / 60, newInfo->time % 60));
		trap_Cvar_Set("ui_scoreCaptures2", va("%i", newInfo->captures));
	}
}

void UI_LoadBestScores(const char *map, int game)
{
	char fileName[MAX_QPATH];
	fileHandle_t f;
	postGameInfo_t newInfo;
	int protocol, protocolLegacy;

	memset(&newInfo, 0, sizeof(postGameInfo_t));
	Com_sprintf(fileName, MAX_QPATH, "games/%s_%i.game", map, game);
	if (trap_FS_FOpenFile(fileName, &f, FS_READ) >= 0) {
		int size = 0;
		trap_FS_Read(&size, sizeof(int), f);
		if (size == sizeof(postGameInfo_t)) {
			trap_FS_Read(&newInfo, sizeof(postGameInfo_t), f);
		}
		trap_FS_FCloseFile(f);
	}
	UI_SetBestScores(&newInfo, qfalse);

	uiInfo.demoAvailable = qfalse;

	protocolLegacy = trap_Cvar_VariableValue("com_legacyprotocol");
	protocol = trap_Cvar_VariableValue("com_protocol");

	if(!protocol)
		protocol = trap_Cvar_VariableValue("protocol");
	if(protocolLegacy == protocol)
		protocolLegacy = 0;

	Com_sprintf(fileName, MAX_QPATH, "demos/%s_%d.%s%d", map, game, DEMOEXT, protocol);
	if(trap_FS_FOpenFile(fileName, &f, FS_READ) >= 0)
	{
		uiInfo.demoAvailable = qtrue;
		trap_FS_FCloseFile(f);
	}
	else if(protocolLegacy > 0)
	{
		Com_sprintf(fileName, MAX_QPATH, "demos/%s_%d.%s%d", map, game, DEMOEXT, protocolLegacy);
		if (trap_FS_FOpenFile(fileName, &f, FS_READ) >= 0)
		{
			uiInfo.demoAvailable = qtrue;
			trap_FS_FCloseFile(f);
		}
	}
}

/*
===============
UI_ClearScores
===============
*/
void UI_ClearScores()
{
	char gameList[4096];
	char *gameFile;
	int i, len, count, size;
	fileHandle_t f;
	postGameInfo_t newInfo;

	count = trap_FS_GetFileList("games", "game", gameList, sizeof(gameList));

	size = sizeof(postGameInfo_t);
	memset(&newInfo, 0, size);

	if (count > 0) {
		gameFile = gameList;
		for (i = 0; i < count; i++) {
			len = strlen(gameFile);
			if (trap_FS_FOpenFile(va("games/%s", gameFile), &f, FS_WRITE) >= 0) {
				trap_FS_Write(&size, sizeof(int), f);
				trap_FS_Write(&newInfo, size, f);
				trap_FS_FCloseFile(f);
			}
			gameFile += len + 1;
		}
	}

	UI_SetBestScores(&newInfo, qfalse);

}

static void UI_Cache_f( void )
{
	Display_CacheAll();
}

/*
=======================
UI_CalcPostGameStats
=======================
*/
static void UI_CalcPostGameStats( void )
{
	char map[MAX_QPATH];
	char fileName[MAX_QPATH];
	char info[MAX_INFO_STRING];
	fileHandle_t f;
	int size, game, time, adjustedTime;
	postGameInfo_t oldInfo;
	postGameInfo_t newInfo;
	qboolean newHigh = qfalse;

	trap_GetConfigString(CS_SERVERINFO, info, sizeof(info));
	Q_strncpyz(map, Info_ValueForKey(info, "mapname"), sizeof(map));
	game = atoi(Info_ValueForKey(info, "g_gametype"));

	// compose file name
	Com_sprintf(fileName, MAX_QPATH, "games/%s_%i.game", map, game);
	// see if we have one already
	memset(&oldInfo, 0, sizeof(postGameInfo_t));
	if (trap_FS_FOpenFile(fileName, &f, FS_READ) >= 0) {
		// if so load it
		size = 0;
		trap_FS_Read(&size, sizeof(int), f);
		if (size == sizeof(postGameInfo_t)) {
			trap_FS_Read(&oldInfo, sizeof(postGameInfo_t), f);
		}
		trap_FS_FCloseFile(f);
	}

	newInfo.accuracy = atoi(UI_Argv(3));
	newInfo.impressives = atoi(UI_Argv(4));
	newInfo.excellents = atoi(UI_Argv(5));
	newInfo.defends = atoi(UI_Argv(6));
	newInfo.assists = atoi(UI_Argv(7));
	newInfo.gauntlets = atoi(UI_Argv(8));
	newInfo.baseScore = atoi(UI_Argv(9));
	newInfo.perfects = atoi(UI_Argv(10));
	newInfo.redScore = atoi(UI_Argv(11));
	newInfo.blueScore = atoi(UI_Argv(12));
	time = atoi(UI_Argv(13));
	newInfo.captures = atoi(UI_Argv(14));

	newInfo.time = (time - trap_Cvar_VariableValue("ui_matchStartTime")) / 1000;
	adjustedTime = uiInfo.mapList[ui_currentMap.integer].timeToBeat[game];
	if (newInfo.time < adjustedTime) {
		newInfo.timeBonus = (adjustedTime - newInfo.time) * 10;
	} else {
		newInfo.timeBonus = 0;
	}

	if (newInfo.redScore > newInfo.blueScore && newInfo.blueScore <= 0) {
		newInfo.shutoutBonus = 100;
	} else {
		newInfo.shutoutBonus = 0;
	}

	newInfo.skillBonus = trap_Cvar_VariableValue("g_spSkill");
	if (newInfo.skillBonus <= 0) {
		newInfo.skillBonus = 1;
	}
	newInfo.score = newInfo.baseScore + newInfo.shutoutBonus + newInfo.timeBonus;
	newInfo.score *= newInfo.skillBonus;

	// see if the score is higher for this one
	newHigh = (newInfo.redScore > newInfo.blueScore && newInfo.score > oldInfo.score);

	if (newHigh) {
		// if so write out the new one
		uiInfo.newHighScoreTime = uiInfo.uiDC.realTime + 20000;
		if (trap_FS_FOpenFile(fileName, &f, FS_WRITE) >= 0) {
			size = sizeof(postGameInfo_t);
			trap_FS_Write(&size, sizeof(int), f);
			trap_FS_Write(&newInfo, sizeof(postGameInfo_t), f);
			trap_FS_FCloseFile(f);
		}
	}

	if (newInfo.time < oldInfo.time) {
		uiInfo.newBestTime = uiInfo.uiDC.realTime + 20000;
	}
	// put back all the ui overrides
	trap_Cvar_Set("capturelimit", UI_Cvar_VariableString("ui_saveCaptureLimit"));
	trap_Cvar_Set("fraglimit", UI_Cvar_VariableString("ui_saveFragLimit"));
	trap_Cvar_Set("cg_drawTimer", UI_Cvar_VariableString("ui_drawTimer"));
	trap_Cvar_Set("g_doWarmup", UI_Cvar_VariableString("ui_doWarmup"));
	trap_Cvar_Set("g_Warmup", UI_Cvar_VariableString("ui_Warmup"));
	trap_Cvar_Set("sv_pure", UI_Cvar_VariableString("ui_pure"));
	trap_Cvar_Set("g_friendlyFire", UI_Cvar_VariableString("ui_friendlyFire"));

	UI_SetBestScores(&newInfo, qtrue);
	UI_ShowPostGame(newHigh);

}

//Makro - returns qtrue if the player can access the weapon/item menus
qboolean UI_RQ3_WeaponMenuAccess()
{
	char info[MAX_INFO_STRING];
	int game, tdmMode;

	trap_GetConfigString(CS_SERVERINFO, info, sizeof(info));
	game = atoi(Info_ValueForKey(info, "g_gametype"));
	tdmMode = atoi(Info_ValueForKey(info, "g_RQ3_tdmMode"));

	if (game == GT_TEAMPLAY || game == GT_CTF || (game == GT_TEAM && !tdmMode))
	   return qtrue;
	else
		return qfalse;
}

/*
=================
UI_ConsoleCommand
=================
*/

qboolean UI_ConsoleCommand(int realTime)
{
	char *cmd;

	uiInfo.uiDC.frameTime = realTime - uiInfo.uiDC.realTime;
	uiInfo.uiDC.realTime = realTime;

	cmd = UI_Argv(0);

	// ensure minimum menu data is available
	//Menu_Cache();

	if (Q_stricmp(cmd, "ui_test") == 0) {
		UI_ShowPostGame(qtrue);
		return qtrue;
	}

	if (Q_stricmp(cmd, "ui_report") == 0) {
		UI_Report();
		return qtrue;
	}

	if (Q_stricmp(cmd, "ui_load") == 0) {
		UI_Load();
		return qtrue;
	}

	if (Q_stricmp(cmd, "remapShader") == 0) {
		//Makro - disabling shader remapping when cheats are off
		if (trap_Cvar_VariableValue("sv_cheats") == 1) {
			if (trap_Argc() >= 4) {
				char shader1[MAX_QPATH];
				char shader2[MAX_QPATH];

				Q_strncpyz(shader1, UI_Argv(1), sizeof(shader1));
				Q_strncpyz(shader2, UI_Argv(2), sizeof(shader2));
				trap_R_RemapShader(shader1, shader2, UI_Argv(3));
			} else
				//Makro - if no offset is specified, use 0
			if (trap_Argc() == 3) {
				char shader1[MAX_QPATH];
				char shader2[MAX_QPATH];

				Q_strncpyz(shader1, UI_Argv(1), sizeof(shader1));
				Q_strncpyz(shader2, UI_Argv(2), sizeof(shader2));
				trap_R_RemapShader(shader1, shader2, 0);
			} else
				Com_Printf("Usage: remapShader <oldShader> <newShader> [timeOffset]\n");
		} else
			Com_Printf("Shader remapping is cheat-protected\n");
		return qtrue;
	}

	if (Q_stricmp(cmd, "postgame") == 0) {
		UI_CalcPostGameStats();
		return qtrue;
	}

	if (Q_stricmp(cmd, "ui_cache") == 0) {
		UI_Cache_f();
		return qtrue;
	}

	if (Q_stricmp(cmd, "ui_teamOrders") == 0) {
		//UI_TeamOrdersMenu_f();
		return qtrue;
	}

	if (Q_stricmp(cmd, "ui_cdkey") == 0) {
		//UI_CDKeyMenu_f();
		return qtrue;
	}
	//Makro - adding popup for choose commands
	if (Q_stricmp(cmd, "ui_RQ3_loadout") == 0) {
		if (UI_RQ3_WeaponMenuAccess())
			_UI_SetActiveMenu(UIMENU_RQ3_WEAPON);
		else
			Com_Printf("Weapon/item menus are not available in this gametype.\n");
		return qtrue;
	}
	//Makro - join menu
	if (Q_stricmp(cmd, "ui_RQ3_joinTeam") == 0) {
		_UI_SetActiveMenu(UIMENU_RQ3_JOIN);
		return qtrue;
	}
	//Makro - tkok menu
	if (Q_stricmp(cmd, "ui_RQ3_tkok") == 0) {
		if (trap_Cvar_VariableValue("g_gametype") >= GT_TEAM)
			_UI_SetActiveMenu(UIMENU_RQ3_TKOK);
		else
			Com_Printf("Not playing a team-based game.\n");
		return qtrue;
	}
	//Makro - presets menu
	if (Q_stricmp(cmd, "ui_RQ3_presets") == 0) {
		_UI_SetActiveMenu(UIMENU_RQ3_PRESETS);
		return qtrue;
	}
	//Makro - I've always wanted a command to inc/dec a cvar :)
	if (Q_stricmp(cmd, "inc") == 0) {
		if (trap_Argc() >= 2) {
			char cvar[MAX_CVAR_VALUE_STRING];
			float amount = 1;
			float val;
			int max = 0;

			Q_strncpyz(cvar, UI_Argv(1), sizeof(cvar));
			val = trap_Cvar_VariableValue(cvar);

			if (trap_Argc() >= 3) {
				amount = atof(UI_Argv(2));
				if (trap_Argc() >= 4) {
					max = atoi(UI_Argv(3));
				}
			}
			if (max != 0) {
				trap_Cvar_SetValue(cvar, (float) (((int) (val + amount)) % max));
			} else {
				trap_Cvar_SetValue(cvar, val + amount);
			}
		} else {
			Com_Printf("Usage: inc <cvarName> [amount] [max]\n");
		}
		return qtrue;
	}
/*
	if ( Q_stricmp (cmd, "ifCvars") == 0) {
		if (trap_Argc() >= 4) {
			char cvar[MAX_CVAR_VALUE_STRING], cvarValue[MAX_CVAR_VALUE_STRING];
			char *val = "";
			char command[256];
			char script[1024];
			qboolean doScript = qfalse;
			int i;
			
			Q_strncpyz(cvar, UI_Argv(1), sizeof(cvar));
			Q_strncpyz(cvarValue, UI_Argv(2), sizeof(cvarValue));
			memset(script, 0, sizeof(script));
			
			for (i=3; i<trap_Argc(); i++) {
				Q_strncpyz(command, UI_Argv(i), sizeof(command));
				Q_strcat(script, sizeof(script), command);
				if (trap_Argc()-i > 1) {
					Q_strcat(script, sizeof(script), " ");
				}
			}
			val = UI_Cvar_VariableString(cvar);

			if (Q_stricmp(val, cvarValue) == 0) {
				doScript = qtrue;
				Com_Printf(va("^3%s = %s^7\n", val, cvarValue));
			}

			if (doScript) {
				trap_Cmd_ExecuteText(EXEC_APPEND, va("%s\n", script));
			}

		} else {
			Com_Printf(va("Usage: %s <cvarName> <cvarValue> <script>\n", cmd));
		}
		return qtrue;
	}
*/

	/*
	if (Q_stricmp(cmd, "error") == 0) {
		if (trap_Cvar_VariableValue("developer") == 1) {
			char text[MAX_CVAR_VALUE_STRING];

			memset(text, 0, sizeof(text));

			if (trap_Argc() == 1) {
				//Q_strcat(text, sizeof(text), "INFO: Testing error menu. Type 'error [msg]' in the console to see this screen. This command is only available when developer is set to 1");
				Q_strcat(text, sizeof(text),
					 "Could not download \"maps/longmapname.pk3\" because autodownloading is disabled on the server\n\nThe server you are connecting to is not a pure server, set autodownload to No in your settings and you might be able to join the game anyway.\n");
			} else {
				Q_strncpyz(text, ConcatArgs(1), sizeof(text));
			}

			Com_Error(ERR_DROP, text);
			return qtrue;
		}
	}
	*/

	if (Q_stricmp(cmd, "ui_RQ3_postVidRestart") == 0) {
		_UI_SetActiveMenu(UIMENU_RQ3_POST_VID_RESTART);
		return qtrue;
	}

	return qfalse;
}

/*
=================
UI_Shutdown
=================
*/
void UI_Shutdown(void)
{
}

/*
================
UI_AdjustFrom640

Adjusted for resolution and screen aspect ratio

Makro - converted to macro, see ui_local.h
================
*/
void _UI_AdjustFrom640(float *x, float *y, float *w, float *h)
{
	// expect valid pointers
#if 0
	*x = *x * uiInfo.uiDC.scale + uiInfo.uiDC.bias;
	*y *= uiInfo.uiDC.scale;
	*w *= uiInfo.uiDC.scale;
	*h *= uiInfo.uiDC.scale;
#endif

	*x *= uiInfo.uiDC.xscale;
	*y *= uiInfo.uiDC.yscale;
	*w *= uiInfo.uiDC.xscale;
	*h *= uiInfo.uiDC.yscale;

}

void UI_DrawNamedPic(float x, float y, float width, float height, const char *picname)
{
	qhandle_t hShader;

	hShader = trap_R_RegisterShaderNoMip(picname);
	UI_AdjustFrom640(&x, &y, &width, &height);
	//trap_R_DrawStretchPic(x, y, width, height, 0, 0, 1, 1, hShader);
	uiInfo.uiDC.drawStretchPic(x, y, width, height, 0, 0, 1, 1, hShader, qfalse);
}

void UI_DrawHandlePic(float x, float y, float w, float h, qhandle_t hShader)
{
	float s0;
	float s1;
	float t0;
	float t1;

	if (w < 0) {		// flip about vertical
		w = -w;
		s0 = 1;
		s1 = 0;
	} else {
		s0 = 0;
		s1 = 1;
	}

	if (h < 0) {		// flip about horizontal
		h = -h;
		t0 = 1;
		t1 = 0;
	} else {
		t0 = 0;
		t1 = 1;
	}

	UI_AdjustFrom640(&x, &y, &w, &h);
	//trap_R_DrawStretchPic(x, y, w, h, s0, t0, s1, t1, hShader);
	uiInfo.uiDC.drawStretchPic(x, y, w, h, s0, t0, s1, t1, hShader, qfalse);
}

/*
================
UI_FillRect

Coordinates are 640*480 virtual values
=================
*/
void UI_FillRect(float x, float y, float width, float height, const float *color)
{
	trap_R_SetColor(color);

	UI_AdjustFrom640(&x, &y, &width, &height);
	//trap_R_DrawStretchPic(x, y, width, height, 0, 0, 0, 0, uiInfo.uiDC.whiteShader);
	uiInfo.uiDC.drawStretchPic(x, y, width, height, 0, 0, 0, 0, uiInfo.uiDC.whiteShader, qfalse);

	trap_R_SetColor(NULL);
}

//Makro - added shader parm
void UI_DrawSides(float x, float y, float w, float h, qhandle_t shader)
{
	UI_AdjustFrom640(&x, &y, &w, &h);
	//trap_R_DrawStretchPic(x, y, 1, h, 0, 0, 0, 0, uiInfo.uiDC.whiteShader);
	//trap_R_DrawStretchPic(x + w - 1, y, 1, h, 0, 0, 0, 0, uiInfo.uiDC.whiteShader);
	uiInfo.uiDC.drawStretchPic(x, y, 1, h, 0, 0, 0, 0, shader, qfalse);
	uiInfo.uiDC.drawStretchPic(x + w - 1, y, 1, h, 0, 0, 0, 0, shader, qfalse);
}

//Makro - added shader parm
void UI_DrawTopBottom(float x, float y, float w, float h, qhandle_t shader)
{
	UI_AdjustFrom640(&x, &y, &w, &h);
	//trap_R_DrawStretchPic(x, y, w, 1, 0, 0, 0, 0, uiInfo.uiDC.whiteShader);
	//trap_R_DrawStretchPic(x, y + h - 1, w, 1, 0, 0, 0, 0, uiInfo.uiDC.whiteShader);
	uiInfo.uiDC.drawStretchPic(x, y, w, 1, 0, 0, 0, 0, shader, qfalse);
	uiInfo.uiDC.drawStretchPic(x, y + h - 1, w, 1, 0, 0, 0, 0, shader, qfalse);
}

/*
================
UI_DrawRect

Coordinates are 640*480 virtual values
=================
*/
//Makro - added shader
void UI_DrawRect(float x, float y, float width, float height, const float *color, qhandle_t shader)
{
	trap_R_SetColor(color);

	UI_DrawTopBottom(x, y, width, height, shader);
	UI_DrawSides(x, y, width, height, shader);

	trap_R_SetColor(NULL);
}

void UI_SetColor(const float *rgba)
{
	trap_R_SetColor(rgba);
}

void UI_UpdateScreen(void)
{
	trap_UpdateScreen();
}

void UI_DrawTextBox(int x, int y, int width, int lines)
{
	UI_FillRect(x + BIGCHAR_WIDTH / 2, y + BIGCHAR_HEIGHT / 2, (width + 1) * BIGCHAR_WIDTH,
		    (lines + 1) * BIGCHAR_HEIGHT, colorBlack);
	UI_DrawRect(x + BIGCHAR_WIDTH / 2, y + BIGCHAR_HEIGHT / 2, (width + 1) * BIGCHAR_WIDTH,
		    (lines + 1) * BIGCHAR_HEIGHT, colorWhite, uiInfo.uiDC.whiteShader);
}

qboolean UI_CursorInRect(int x, int y, int width, int height)
{
	if (uiInfo.uiDC.cursorx < x ||
	    uiInfo.uiDC.cursory < y || uiInfo.uiDC.cursorx > x + width || uiInfo.uiDC.cursory > y + height)
		return qfalse;

	return qtrue;
}
