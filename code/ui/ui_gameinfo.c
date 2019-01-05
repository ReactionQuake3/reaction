//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.12  2006/04/14 18:02:06  makro
// no message
//
// Revision 1.11  2003/03/31 01:23:54  jbravo
// Fixing 2 compiler warnings
//
// Revision 1.10  2002/09/08 13:14:47  makro
// New code added for the callvote menu map list
//
// Revision 1.9  2002/07/24 05:28:44  jbravo
// Changed rq3ctf to rq3ctb in the .arena parsing code.
//
// Revision 1.8  2002/06/16 20:06:14  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.7  2002/06/13 15:50:24  makro
// Bot list is now sorted alphabetically
//
// Revision 1.6  2002/05/26 14:37:21  makro
// Map list is now sorted alphabetically
//
// Revision 1.5  2002/03/31 13:23:26  makro
// Cleaned things up a little
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
//
// gameinfo.c
//

#include "ui_local.h"

//
// arena and bot info
//

int ui_numBots;
static char *ui_botInfos[MAX_BOTS];

static int ui_numArenas;
static char *ui_arenaInfos[MAX_ARENAS];

//Makro - not used anywhere
/*
#ifndef MISSIONPACK // bk001206
static int		ui_numSinglePlayerArenas;
static int		ui_numSpecialSinglePlayerArenas;
#endif
*/

//Makro - grouping the gametypes parsed in .arena files
typedef struct {
	char *Name;
	int Value;
} RQ3_GameType_t;

static RQ3_GameType_t RQ3_GameTypes[] = {
/*	{"ffa",				1 << GT_FFA},
	{"tourney",			1 << GT_TOURNAMENT},
	{"team",			1 << GT_TEAM},
	{"rq3tp",			1 << GT_TEAMPLAY},
	{"ctf",				1 << GT_CTF},
	{"1fctf",			1 << GT_1FCTF},
	{"obelisk",			1 << GT_OBELISK},
	{"harvester",		1 << GT_HARVESTER},
*/
	{"rq3dm", 1 << GT_FFA},
	{"rq3tdm", 1 << GT_TEAM},
	{"rq3tp", 1 << GT_TEAMPLAY},
	{"rq3ctb", 1 << GT_CTF},
	{"none", 0}
};

// static int UI_RQ3_DefaultArenaGameType = 1 << GT_FFA;

//end Makro

/*
===============
UI_ParseInfos
===============
*/
int UI_ParseInfos(char *buf, int max, char *infos[])
{
	char *token;
	int count;
	char key[MAX_TOKEN_CHARS];
	char info[MAX_INFO_STRING];

	count = 0;

	INFINITE_LOOP {
		token = COM_Parse(&buf);
		if (!token[0]) {
			break;
		}
		if (strcmp(token, "{")) {
			Com_Printf("Missing { in info file\n");
			break;
		}

		if (count == max) {
			Com_Printf("Max infos exceeded\n");
			break;
		}

		info[0] = '\0';
		INFINITE_LOOP {
			token = COM_ParseExt(&buf, qtrue);
			if (!token[0]) {
				Com_Printf("Unexpected end of info file\n");
				break;
			}
			if (!strcmp(token, "}")) {
				break;
			}
			Q_strncpyz(key, token, sizeof(key));

			token = COM_ParseExt(&buf, qfalse);
			if (!token[0]) {
				strcpy(token, "<NULL>");
			}
			Info_SetValueForKey(info, key, token);
		}
		//NOTE: extra space for arena number
		infos[count] = UI_Alloc(strlen(info) + strlen("\\num\\") + strlen(va("%d", MAX_ARENAS)) + 1);
		if (infos[count]) {
			strcpy(infos[count], info);
			count++;
		}
	}
	return count;
}

/*
===============
UI_LoadArenasFromFile
===============
*/
static void UI_LoadArenasFromFile(char *filename)
{
	int len;
	fileHandle_t f;
	char buf[MAX_ARENAS_TEXT];

	len = trap_FS_FOpenFile(filename, &f, FS_READ);
	if (!f) {
		trap_Print(va(S_COLOR_RED "file not found: %s\n", filename));
		return;
	}
	if (len >= MAX_ARENAS_TEXT) {
		trap_Print(va
			   (S_COLOR_RED "file too large: %s is %i, max allowed is %i", filename, len, MAX_ARENAS_TEXT));
		trap_FS_FCloseFile(f);
		return;
	}

	trap_FS_Read(buf, len, f);
	buf[len] = 0;
	trap_FS_FCloseFile(f);

	ui_numArenas += UI_ParseInfos(buf, MAX_ARENAS - ui_numArenas, &ui_arenaInfos[ui_numArenas]);
}

/*
===============
UI_LoadArenas
===============
*/
void UI_LoadArenas(void)
{
	int numdirs;
	vmCvar_t arenasFile;
	char filename[128];
	char dirlist[1024];
	char *dirptr;
	int i;
	int dirlen;

	ui_numArenas = 0;

	trap_Cvar_Register(&arenasFile, "g_arenasFile", "", CVAR_INIT | CVAR_ROM);
	if (*arenasFile.string) {
		UI_LoadArenasFromFile(arenasFile.string);
	} else {
		UI_LoadArenasFromFile("scripts/arenas.txt");
	}

	// get all arenas from .arena files
	numdirs = trap_FS_GetFileList("scripts", ".arena", dirlist, 1024);
	dirptr = dirlist;
	for (i = 0; i < numdirs; i++, dirptr += dirlen + 1) {
		dirlen = strlen(dirptr);
		strcpy(filename, "scripts/");
		strcat(filename, dirptr);
		UI_LoadArenasFromFile(filename);
	}
	trap_Print(va("%i arenas parsed\n", ui_numArenas));
	if (UI_OutOfMemory()) {
		trap_Print(S_COLOR_YELLOW "WARNING: not anough memory in pool to load all arenas\n");
	}
}

/*
===============
UI_LoadArenasIntoMapList
===============
*/
void UI_LoadArenasIntoMapList(void)
{
	int i, n;
	char *type;

	uiInfo.mapCount = 0;

	for (n = 0; n < ui_numArenas; n++) {
		// determine type

		uiInfo.mapList[uiInfo.mapCount].cinematic = -1;
		uiInfo.mapList[uiInfo.mapCount].mapLoadName = String_Alloc(Info_ValueForKey(ui_arenaInfos[n], "map"));
		uiInfo.mapList[uiInfo.mapCount].mapName = String_Alloc(Info_ValueForKey(ui_arenaInfos[n], "longname"));
		uiInfo.mapList[uiInfo.mapCount].levelShot = -1;
		uiInfo.mapList[uiInfo.mapCount].imageName =
		    String_Alloc(va("levelshots/%s", uiInfo.mapList[uiInfo.mapCount].mapLoadName));
		uiInfo.mapList[uiInfo.mapCount].typeBits = 0;

		type = Info_ValueForKey(ui_arenaInfos[n], "type");
		// if no type specified, it will be treated as "ffa"
		// Makro - I didn't like the old code, hehe
/*
		if( *type ) {
			if( strstr( type, "ffa" ) ) {
				uiInfo.mapList[uiInfo.mapCount].typeBits |= (1 << GT_FFA);
			}
			if( strstr( type, "tourney" ) ) {
				uiInfo.mapList[uiInfo.mapCount].typeBits |= (1 << GT_TOURNAMENT);
			}
			if( strstr( type, "ctf" ) ) {
				uiInfo.mapList[uiInfo.mapCount].typeBits |= (1 << GT_CTF);
			}
			if( strstr( type, "oneflag" ) ) {
				uiInfo.mapList[uiInfo.mapCount].typeBits |= (1 << GT_1FCTF);
			}
			if( strstr( type, "overload" ) ) {
				uiInfo.mapList[uiInfo.mapCount].typeBits |= (1 << GT_OBELISK);
			}
			if( strstr( type, "harvester" ) ) {
				uiInfo.mapList[uiInfo.mapCount].typeBits |= (1 << GT_HARVESTER);
			}
		} else {
			uiInfo.mapList[uiInfo.mapCount].typeBits |= (1 << GT_FFA);
		}
*/
		// Makro - new code
		if (*type) {
			for (i = 0; RQ3_GameTypes[i].Value != 0; i++) {
				if (strstr(type, RQ3_GameTypes[i].Name)) {
					uiInfo.mapList[uiInfo.mapCount].typeBits |= RQ3_GameTypes[i].Value;
				}
			}
		}// else {
		//	uiInfo.mapList[uiInfo.mapCount].typeBits |= UI_RQ3_DefaultArenaGameType;
		//}

		uiInfo.mapCount++;
		if (uiInfo.mapCount >= MAX_MAPS) {
			break;
		}
	}

	//Makro - sorting list
	for (i = 0; i < uiInfo.mapCount - 1; i++) {
		for (n = i + 1; n < uiInfo.mapCount; n++) {
			if (Q_stricmp(uiInfo.mapList[i].mapName, uiInfo.mapList[n].mapName) > 0) {
				mapInfo temp = uiInfo.mapList[i];

				uiInfo.mapList[i] = uiInfo.mapList[n];
				uiInfo.mapList[n] = temp;
			}
		}
	}
}

/*
===============
UI_LoadBotsFromFile
===============
*/
static void UI_LoadBotsFromFile(char *filename)
{
	int len;
	fileHandle_t f;
	char buf[MAX_BOTS_TEXT];

	len = trap_FS_FOpenFile(filename, &f, FS_READ);
	if (!f) {
		trap_Print(va(S_COLOR_RED "file not found: %s\n", filename));
		return;
	}
	if (len >= MAX_BOTS_TEXT) {
		trap_Print(va(S_COLOR_RED "file too large: %s is %i, max allowed is %i\n", filename, len, MAX_BOTS_TEXT));
		trap_FS_FCloseFile(f);
		return;
	}

	trap_FS_Read(buf, len, f);
	buf[len] = 0;
	trap_FS_FCloseFile(f);

	COM_Compress(buf);

	ui_numBots += UI_ParseInfos(buf, MAX_BOTS - ui_numBots, &ui_botInfos[ui_numBots]);
}

/*
===============
UI_LoadBots
===============
*/
void UI_LoadBots(void)
{
	vmCvar_t botsFile;
	int numdirs;
	char filename[128];
	char dirlist[1024];
	char *dirptr;
	int i;
	int dirlen;

	ui_numBots = 0;

	trap_Cvar_Register(&botsFile, "g_botsFile", "", CVAR_INIT | CVAR_ROM);
	if (*botsFile.string) {
		UI_LoadBotsFromFile(botsFile.string);
	} else {
		UI_LoadBotsFromFile("scripts/bots.txt");
	}

	// get all bots from .bot files
	numdirs = trap_FS_GetFileList("scripts", ".bot", dirlist, 1024);
	dirptr = dirlist;
	for (i = 0; i < numdirs; i++, dirptr += dirlen + 1) {
		dirlen = strlen(dirptr);
		strcpy(filename, "scripts/");
		strcat(filename, dirptr);
		UI_LoadBotsFromFile(filename);
	}

	//Makro - sort bot list
	for (i = 0; i < ui_numBots - 1; i++) {
		for (dirlen = i + 1; dirlen < ui_numBots; dirlen++) {
			char *n1 = Info_ValueForKey(ui_botInfos[i], "name");
			char *n2 = Info_ValueForKey(ui_botInfos[dirlen], "name");

			if (!n1)
				n1 = "Abbey";
			if (!n2)
				n2 = "Abbey";
			if (Q_stricmp(n1, n2) > 0) {
				dirptr = ui_botInfos[i];
				ui_botInfos[i] = ui_botInfos[dirlen];
				ui_botInfos[dirlen] = dirptr;
			}
		}
	}

	trap_Print(va("%i bots parsed\n", ui_numBots));
}

/*
===============
UI_GetBotInfoByNumber
===============
*/
char *UI_GetBotInfoByNumber(int num)
{
	if (num < 0 || num >= ui_numBots) {
		trap_Print(va(S_COLOR_RED "Invalid bot number: %i\n", num));
		return NULL;
	}
	return ui_botInfos[num];
}

/*
===============
UI_GetBotInfoByName
===============
*/
char *UI_GetBotInfoByName(const char *name)
{
	int n;
	char *value;

	for (n = 0; n < ui_numBots; n++) {
		value = Info_ValueForKey(ui_botInfos[n], "name");
		if (!Q_stricmp(value, name)) {
			return ui_botInfos[n];
		}
	}

	return NULL;
}

int UI_GetNumBots()
{
	return ui_numBots;
}

char *UI_GetBotNameByNumber(int num)
{
	char *info = UI_GetBotInfoByNumber(num);

	if (info) {
		return Info_ValueForKey(info, "name");
	}
	//Makro - changed from Sarge
	return "Raver";
}
