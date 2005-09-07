//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.64  2005/09/07 20:29:05  makro
// Stuff I can't remember
//
// Revision 1.63  2003/09/10 21:40:35  makro
// Cooler breath puffs. Locked r_fastSky on maps with global fog.
// Some other things I can't remember.
//
// Revision 1.62  2003/09/01 15:09:48  jbravo
// Cleanups, crashbug fix and version bumped to 3.2
//
// Revision 1.61  2003/07/30 16:05:46  makro
// no message
//
// Revision 1.60  2003/04/07 18:21:34  niceass
// teamplay irvision
//
// Revision 1.59  2003/04/07 11:30:10  jbravo
// Forgot a skin change for reactionmale
//
// Revision 1.58  2003/03/29 18:53:41  jbravo
// Fixed ammo bug when dropping bandolier. Added color to more errormessages
//
// Revision 1.57  2003/03/09 21:30:38  jbravo
// Adding unlagged.   Still needs work.
//
// Revision 1.56  2003/03/08 10:02:23  niceass
// CTB briefcases in 3rd person now utilize tag_weapon2
//
// Revision 1.55  2002/10/26 22:03:42  jbravo
// Made TeamDM work RQ3 style.
//
// Revision 1.54  2002/10/26 00:37:18  jbravo
// New multiple item code and added PB support to the UI
//
// Revision 1.53  2002/09/29 16:06:44  jbravo
// Work done at the HPWorld expo
//
// Revision 1.52  2002/08/29 14:45:17  niceass
// disabled wallhack
//
// Revision 1.51  2002/08/27 07:29:31  niceass
// tralalaanasdfadf
//
// Revision 1.50  2002/08/27 07:28:11  niceass
// shuttup
//
// Revision 1.49  2002/08/27 07:02:09  niceass
// terrain fix?
//
// Revision 1.48  2002/08/27 06:57:24  niceass
// gooddamnit =(
//
// Revision 1.47  2002/08/27 06:56:15  niceass
// BETA testing idea for wallhack code
//
// Revision 1.46  2002/08/27 05:46:58  niceass
// change to anti-wallhack code
//
// Revision 1.45  2002/08/24 08:00:41  niceass
// fix to anti-wallhack system for portals (cameras and mirrors)
//
// Revision 1.44  2002/08/22 07:06:14  niceass
// basic wallhack protection in, ala ncserver
//
// Revision 1.43  2002/08/18 20:26:35  jbravo
// New hitboxes.  Fixed CTB awards (flags)
//
// Revision 1.42  2002/08/07 16:13:33  jbravo
// Case carrier glowing removed. Ignorenum bug fixed
//
// Revision 1.41  2002/07/22 06:30:52  niceass
// cleaned up the powerup code
//
// Revision 1.40  2002/07/11 16:29:16  makro
// Dust has a different color for snow surfaces now
//
// Revision 1.39  2002/07/09 06:08:09  niceass
// fixes and changes to ctb
//
// Revision 1.38  2002/06/29 21:58:14  niceass
// no more enemy bubbles
//
// Revision 1.37  2002/06/25 06:11:36  niceass
// flag positioning enhancement! (F.P.E.)
//
// Revision 1.36  2002/06/25 00:11:26  jbravo
// Damn triangles be gone
//
// Revision 1.35  2002/06/24 05:51:51  jbravo
// CTF mode is now semi working
//
// Revision 1.34  2002/06/23 15:51:59  slicer
// Fixed the UI team count cvars when someone disconnects.
//
// Revision 1.33  2002/06/16 20:06:13  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.32  2002/06/16 19:12:52  jbravo
// Removed the MISSIONPACK ifdefs and missionpack only code.
//
// Revision 1.31  2002/06/13 19:03:22  niceass
// cg_forceModel teamplay fix.
//
// Revision 1.30  2002/06/09 18:58:40  makro
// no message
//
// Revision 1.29  2002/06/01 04:20:09  niceass
// knife throw active animation bug fixed
//
// Revision 1.28  2002/05/27 07:01:02  niceass
// headless code
//
// Revision 1.27  2002/05/13 07:29:14  jbravo
// Fixed server chrasing on incorrect models in TP and also added default skins
//
// Revision 1.26  2002/05/11 15:40:41  slicer
// Changed cg_RQ3_<team count> cvars to ui_RQ3_ and added a synch system for these
//
// Revision 1.25  2002/05/01 18:56:02  makro
// Small fix
//
// Revision 1.24  2002/05/01 18:09:55  makro
// Disabled footsteps from animation.cfg files
//
// Revision 1.23  2002/04/23 11:24:06  jbravo
// Removed a debug message and did some cleanups
//
// Revision 1.22  2002/04/22 02:27:57  jbravo
// Dynamic model recognition
//
// Revision 1.21  2002/03/31 03:31:24  jbravo
// Compiler warning cleanups
//
// Revision 1.20  2002/03/23 05:50:47  jbravo
// Moved enableDust out of the missionpack
//
// Revision 1.19  2002/03/04 20:50:59  jbravo
// No floating scores over dead bodies, triangles disabled, and no viewing
// names of enemys just of teammates.
//
// Revision 1.18  2002/03/02 15:37:55  makro
// Changed the 'breath' effect a bit (alpha+size).
//
// Revision 1.17  2002/02/26 20:55:00  jbravo
// No more bubbles over dead players corpses
//
// Revision 1.16  2002/01/30 07:37:25  niceass
// EnableBreath added for mappers (TA thing)
//
// Revision 1.15  2002/01/14 01:19:23  niceass
// No more default 800 gravity on items - NiceAss
//
// Revision 1.14  2002/01/11 19:48:29  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.13  2001/12/31 16:28:41  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
// cg_players.c -- handle the media and animation for player entities
#include "cg_local.h"

char *cg_customSoundNames[MAX_CUSTOM_SOUNDS] = {
	"*death1.wav",
	"*death2.wav",
	"*death3.wav",
	"*jump1.wav",
	"*pain25_1.wav",
	"*pain50_1.wav",
	"*pain75_1.wav",
	"*pain100_1.wav",
	"*falling1.wav",
	"*gasp.wav",
	"*drown.wav",
	"*fall1.wav",
	"*taunt.wav"
};

/*
================
CG_CustomSound

================
*/
sfxHandle_t CG_CustomSound(int clientNum, const char *soundName)
{
	clientInfo_t *ci;
	int i;

	if (soundName[0] != '*') {
		return trap_S_RegisterSound(soundName, qfalse);
	}

	if (clientNum < 0 || clientNum >= MAX_CLIENTS) {
		clientNum = 0;
	}
	ci = &cgs.clientinfo[clientNum];

	for (i = 0; i < MAX_CUSTOM_SOUNDS && cg_customSoundNames[i]; i++) {
		if (!strcmp(soundName, cg_customSoundNames[i])) {
			return ci->sounds[i];
		}
	}

	CG_Error("Unknown custom sound: %s", soundName);
	return 0;
}

/*
=============================================================================

CLIENT INFO

=============================================================================
*/

/*
======================
CG_ParseAnimationFile

Read a configuration file containing animation coutns and rates
models/players/visor/animation.cfg, etc
======================
*/
static qboolean CG_ParseAnimationFile(const char *filename, clientInfo_t * ci)
{
	char *text_p, *prev;
	int len;
	int i;
	char *token;
	float fps;
	int skip;
	char text[20000];
	char var[MAX_TOKEN_CHARS];

	fileHandle_t f;
	animation_t *animations;

	animations = ci->animations;
//Com_Printf("Got This far");
	// load the file
	len = trap_FS_FOpenFile(filename, &f, FS_READ);
	if (len <= 0) {
		return qfalse;
	}
	if (len >= sizeof(text) - 1) {
		CG_Printf("^1File %s too long\n", filename);
		return qfalse;
	}
	trap_FS_Read(text, len, f);
	text[len] = 0;
	trap_FS_FCloseFile(f);

	// parse the text
	text_p = text;
	skip = 0;		// quite the compiler warning

	ci->footsteps = FOOTSTEP_NORMAL;
	VectorClear(ci->headOffset);
	ci->gender = GENDER_MALE;
	ci->fixedlegs = qfalse;
	ci->fixedtorso = qfalse;

	// read optional parameters
	while (1) {
		prev = text_p;	// so we can unget
		token = COM_Parse(&text_p);
		if (!token) {
			break;
		}
		if (!Q_stricmp(token, "footsteps")) {
			token = COM_Parse(&text_p);
			if (!token) {
				break;
			}
			if (!Q_stricmp(token, "default") || !Q_stricmp(token, "normal")) {
				ci->footsteps = FOOTSTEP_NORMAL;
			} else if (!Q_stricmp(token, "boot")) {
				ci->footsteps = FOOTSTEP_BOOT;
				//Makro - no need for these footsteps
				/*
				   } else if ( !Q_stricmp( token, "flesh" ) ) {
				   ci->footsteps = FOOTSTEP_FLESH;
				   } else if ( !Q_stricmp( token, "mech" ) ) {
				   ci->footsteps = FOOTSTEP_MECH;
				   } else if ( !Q_stricmp( token, "energy" ) ) {
				   ci->footsteps = FOOTSTEP_ENERGY; */
			} else {
				//Makro - added developer 1 check
				trap_Cvar_VariableStringBuffer("developer", var, sizeof(var));
				if (atoi(var))
					CG_Printf("^1Bad footsteps parm in %s: %s\n", filename, token);
			}
			continue;
		} else if (!Q_stricmp(token, "headoffset")) {
			for (i = 0; i < 3; i++) {
				token = COM_Parse(&text_p);
				if (!token) {
					break;
				}
				ci->headOffset[i] = atof(token);
			}
			continue;
		} else if (!Q_stricmp(token, "sex")) {
			token = COM_Parse(&text_p);
			if (!token) {
				break;
			}
			if (token[0] == 'f' || token[0] == 'F') {
				ci->gender = GENDER_FEMALE;
			} else if (token[0] == 'n' || token[0] == 'N') {
				ci->gender = GENDER_NEUTER;
			} else {
				ci->gender = GENDER_MALE;
			}
			continue;
		} else if (!Q_stricmp(token, "fixedlegs")) {
			ci->fixedlegs = qtrue;
			continue;
		} else if (!Q_stricmp(token, "fixedtorso")) {
			ci->fixedtorso = qtrue;
			continue;
		}
		// if it is a number, start parsing animations
		if (token[0] >= '0' && token[0] <= '9') {
			text_p = prev;	// unget the token
			break;
		}
		Com_Printf("^1unknown token '%s' is %s\n", token, filename);
	}

	// read information for each frame
	for (i = 0; i < MAX_ANIMATIONS; i++) {

		token = COM_Parse(&text_p);
		if (!*token) {
			if (i >= TORSO_GETFLAG && i <= TORSO_NEGATIVE) {
				animations[i].firstFrame = animations[TORSO_GESTURE].firstFrame;
				animations[i].frameLerp = animations[TORSO_GESTURE].frameLerp;
				animations[i].initialLerp = animations[TORSO_GESTURE].initialLerp;
				animations[i].loopFrames = animations[TORSO_GESTURE].loopFrames;
				animations[i].numFrames = animations[TORSO_GESTURE].numFrames;
				animations[i].reversed = qfalse;
				animations[i].flipflop = qfalse;
				continue;
			}
			break;
		}
		animations[i].firstFrame = atoi(token);
		// leg only frames are adjusted to not count the upper body only frames
		if (i == LEGS_WALKCR) {
			skip = animations[LEGS_WALKCR].firstFrame - animations[TORSO_GESTURE].firstFrame;
		}
		if (i >= LEGS_WALKCR && i < TORSO_GETFLAG) {
			animations[i].firstFrame -= skip;
		}

		token = COM_Parse(&text_p);
		if (!*token) {
			break;
		}
		animations[i].numFrames = atoi(token);

		animations[i].reversed = qfalse;
		animations[i].flipflop = qfalse;
		// if numFrames is negative the animation is reversed
		if (animations[i].numFrames < 0) {
			animations[i].numFrames = -animations[i].numFrames;
			animations[i].reversed = qtrue;
		}

		token = COM_Parse(&text_p);
		if (!*token) {
			break;
		}
		animations[i].loopFrames = atoi(token);

		token = COM_Parse(&text_p);
		if (!*token) {
			break;
		}
		fps = atof(token);
		if (fps == 0) {
			fps = 1;
		}
		animations[i].frameLerp = 1000 / fps;
		animations[i].initialLerp = 1000 / fps;
	}

	if (i != MAX_ANIMATIONS) {
		CG_Printf("^1Error parsing animation file: %s", filename);
		return qfalse;
	}
	// crouch backward animation
	memcpy(&animations[LEGS_BACKCR], &animations[LEGS_WALKCR], sizeof(animation_t));
	animations[LEGS_BACKCR].reversed = qtrue;
	// walk backward animation
	memcpy(&animations[LEGS_BACKWALK], &animations[LEGS_WALK], sizeof(animation_t));
	animations[LEGS_BACKWALK].reversed = qtrue;
	// flag moving fast
	animations[FLAG_RUN].firstFrame = 0;
	animations[FLAG_RUN].numFrames = 16;
	animations[FLAG_RUN].loopFrames = 16;
	animations[FLAG_RUN].frameLerp = 1000 / 15;
	animations[FLAG_RUN].initialLerp = 1000 / 15;
	animations[FLAG_RUN].reversed = qfalse;
	// flag not moving or moving slowly
	animations[FLAG_STAND].firstFrame = 16;
	animations[FLAG_STAND].numFrames = 5;
	animations[FLAG_STAND].loopFrames = 0;
	animations[FLAG_STAND].frameLerp = 1000 / 20;
	animations[FLAG_STAND].initialLerp = 1000 / 20;
	animations[FLAG_STAND].reversed = qfalse;
	// flag speeding up
	animations[FLAG_STAND2RUN].firstFrame = 16;
	animations[FLAG_STAND2RUN].numFrames = 5;
	animations[FLAG_STAND2RUN].loopFrames = 1;
	animations[FLAG_STAND2RUN].frameLerp = 1000 / 15;
	animations[FLAG_STAND2RUN].initialLerp = 1000 / 15;
	animations[FLAG_STAND2RUN].reversed = qtrue;
	//
	// new anims changes
	//
//      animations[TORSO_GETFLAG].flipflop = qtrue;
//      animations[TORSO_GUARDBASE].flipflop = qtrue;
//      animations[TORSO_PATROL].flipflop = qtrue;
//      animations[TORSO_AFFIRMATIVE].flipflop = qtrue;
//      animations[TORSO_NEGATIVE].flipflop = qtrue;
	//
	return qtrue;
}

/*
==========================
CG_FileExists
==========================
*/
static qboolean CG_FileExists(const char *filename)
{
	int len;

	len = trap_FS_FOpenFile(filename, 0, FS_READ);
	if (len > 0) {
		return qtrue;
	}
	return qfalse;
}

/*
==========================
CG_FindClientModelFile
==========================
*/
static qboolean CG_FindClientModelFile(char *filename, int length, clientInfo_t * ci, const char *teamName,
				       const char *modelName, const char *skinName, const char *base, const char *ext)
{
	char *team, *charactersFolder;
	int i;

	if (cgs.gametype >= GT_TEAM) {
		switch (ci->team) {
		case TEAM_BLUE:{
				team = "blue";
				break;
			}
		default:{
				team = "red";
				break;
			}
		}
	} else {
		team = "default";
	}
	charactersFolder = "";
	while (1) {
		for (i = 0; i < 2; i++) {
			if (i == 0 && teamName && *teamName) {
				//                                                              "models/players/characters/james/stroggs/lower_lily_red.skin"
				Com_sprintf(filename, length, "models/players/%s%s/%s%s_%s_%s.%s", charactersFolder,
					    modelName, teamName, base, skinName, team, ext);
			} else {
				//                                                              "models/players/characters/james/lower_lily_red.skin"
				Com_sprintf(filename, length, "models/players/%s%s/%s_%s_%s.%s", charactersFolder,
					    modelName, base, skinName, team, ext);
			}
			if (CG_FileExists(filename)) {
				return qtrue;
			}
			if (cgs.gametype >= GT_TEAM) {
				Com_sprintf(filename, length, "models/players/%s/%s_%s.%s", modelName, base, skinName,
					    ext);
			} else if (cgs.gametype >= GT_TEAM) {
				if (i == 0 && teamName && *teamName) {
					//                                                              "models/players/characters/james/stroggs/lower_red.skin"
					Com_sprintf(filename, length, "models/players/%s%s/%s%s_%s.%s",
						    charactersFolder, modelName, teamName, base, team, ext);
				} else {
					//                                                              "models/players/characters/james/lower_red.skin"
					Com_sprintf(filename, length, "models/players/%s%s/%s_%s.%s", charactersFolder,
						    modelName, base, team, ext);
				}
			} else {
				if (i == 0 && teamName && *teamName) {
					//                                                              "models/players/characters/james/stroggs/lower_lily.skin"
					Com_sprintf(filename, length, "models/players/%s%s/%s%s_%s.%s",
						    charactersFolder, modelName, teamName, base, skinName, ext);
				} else {
					//                                                              "models/players/characters/james/lower_lily.skin"
					Com_sprintf(filename, length, "models/players/%s%s/%s_%s.%s", charactersFolder,
						    modelName, base, skinName, ext);
				}
			}
			if (CG_FileExists(filename)) {
				return qtrue;
			}
			if (!teamName || !*teamName) {
				break;
			}
		}
		// if tried the heads folder first
		if (charactersFolder[0]) {
			break;
		}
		charactersFolder = "characters/";
	}

	return qfalse;
}

/*
==========================
CG_FindClientHeadFile
==========================
*/
static qboolean CG_FindClientHeadFile(char *filename, int length, clientInfo_t * ci, const char *teamName,
				      const char *headModelName, const char *headSkinName, const char *base,
				      const char *ext)
{
	char *team, *headsFolder;
	int i;

	if (cgs.gametype >= GT_TEAM) {
		switch (ci->team) {
		case TEAM_BLUE:{
				team = "blue";
				break;
			}
		default:{
				team = "red";
				break;
			}
		}
	} else {
		team = "default";
	}

	if (headModelName[0] == '*') {
		headsFolder = "heads/";
		headModelName++;
	} else {
		headsFolder = "";
	}
	while (1) {
		for (i = 0; i < 2; i++) {
			if (i == 0 && teamName && *teamName) {
				Com_sprintf(filename, length, "models/players/%s%s/%s/%s%s_%s.%s", headsFolder,
					    headModelName, headSkinName, teamName, base, team, ext);
			} else {
				Com_sprintf(filename, length, "models/players/%s%s/%s/%s_%s.%s", headsFolder,
					    headModelName, headSkinName, base, team, ext);
			}
			if (CG_FileExists(filename)) {
				return qtrue;
			}
			if (cgs.gametype >= GT_TEAM) {
				Com_sprintf(filename, length, "models/players/%s/%s_%s.%s", headModelName, base,
					    headSkinName, ext);
			} else if (cgs.gametype >= GT_TEAM) {
				if (i == 0 && teamName && *teamName) {
					Com_sprintf(filename, length, "models/players/%s%s/%s%s_%s.%s", headsFolder,
						    headModelName, teamName, base, team, ext);
				} else {
					Com_sprintf(filename, length, "models/players/%s%s/%s_%s.%s", headsFolder,
						    headModelName, base, team, ext);
				}
			} else {
				if (i == 0 && teamName && *teamName) {
					Com_sprintf(filename, length, "models/players/%s%s/%s%s_%s.%s", headsFolder,
						    headModelName, teamName, base, headSkinName, ext);
				} else {
					Com_sprintf(filename, length, "models/players/%s%s/%s_%s.%s", headsFolder,
						    headModelName, base, headSkinName, ext);
				}
			}
			if (CG_FileExists(filename)) {
				return qtrue;
			}
			if (!teamName || !*teamName) {
				break;
			}
		}
		// if tried the heads folder first
		if (headsFolder[0]) {
			break;
		}
		headsFolder = "heads/";
	}

	return qfalse;
}

/*
==========================
CG_RegisterClientSkin
==========================
*/
static qboolean CG_RegisterClientSkin(clientInfo_t * ci, const char *teamName, const char *modelName,
				      const char *skinName, const char *headModelName, const char *headSkinName)
{
	char filename[MAX_QPATH];

	/*
	   Com_sprintf( filename, sizeof( filename ), "models/players/%s/%slower_%s.skin", modelName, teamName, skinName );
	   ci->legsSkin = trap_R_RegisterSkin( filename );
	   if (!ci->legsSkin) {
	   Com_sprintf( filename, sizeof( filename ), "models/players/characters/%s/%slower_%s.skin", modelName, teamName, skinName );
	   ci->legsSkin = trap_R_RegisterSkin( filename );
	   if (!ci->legsSkin) {
	   Com_Printf( "Leg skin load failure: %s\n", filename );
	   }
	   }

	   Com_sprintf( filename, sizeof( filename ), "models/players/%s/%supper_%s.skin", modelName, teamName, skinName );
	   ci->torsoSkin = trap_R_RegisterSkin( filename );
	   if (!ci->torsoSkin) {
	   Com_sprintf( filename, sizeof( filename ), "models/players/characters/%s/%supper_%s.skin", modelName, teamName, skinName );
	   ci->torsoSkin = trap_R_RegisterSkin( filename );
	   if (!ci->torsoSkin) {
	   Com_Printf( "Torso skin load failure: %s\n", filename );
	   }
	   }
	 */
	if (CG_FindClientModelFile(filename, sizeof(filename), ci, teamName, modelName, skinName, "lower", "skin")) {
		ci->legsSkin = trap_R_RegisterSkin(filename);
	}
	if (!ci->legsSkin) {
		Com_Printf("^1Leg skin load failure: %s\n", filename);
	}

	if (CG_FindClientModelFile(filename, sizeof(filename), ci, teamName, modelName, skinName, "upper", "skin")) {
		ci->torsoSkin = trap_R_RegisterSkin(filename);
	}
	if (!ci->torsoSkin) {
		Com_Printf("^1Torso skin load failure: %s\n", filename);
	}

	if (CG_FindClientHeadFile
	    (filename, sizeof(filename), ci, teamName, headModelName, headSkinName, "head", "skin")) {
		ci->headSkin = trap_R_RegisterSkin(filename);
	}
	if (!ci->headSkin) {
		Com_Printf("^1Head skin load failure: %s\n", filename);
	}
	// if any skins failed to load
	if (!ci->legsSkin || !ci->torsoSkin || !ci->headSkin) {
		return qfalse;
	}
	return qtrue;
}

/*
==========================
CG_RegisterClientModelname
==========================
*/
static qboolean CG_RegisterClientModelname(clientInfo_t * ci, const char *modelName, const char *skinName,
					   const char *headModelName, const char *headSkinName, const char *teamName)
{
	char filename[MAX_QPATH * 2];
	const char *headName;
	char newTeamName[MAX_QPATH * 2];

	if (headModelName[0] == '\0') {
		headName = modelName;
	} else {
		headName = headModelName;
	}
	Com_sprintf(filename, sizeof(filename), "models/players/%s/lower.md3", modelName);
	ci->legsModel = trap_R_RegisterModel(filename);
	if (!ci->legsModel) {
		Com_sprintf(filename, sizeof(filename), "models/players/characters/%s/lower.md3", modelName);
		ci->legsModel = trap_R_RegisterModel(filename);
		if (!ci->legsModel) {
			Com_Printf("^1Failed to load model file %s\n", filename);
			return qfalse;
		}
	}

	Com_sprintf(filename, sizeof(filename), "models/players/%s/upper.md3", modelName);
	ci->torsoModel = trap_R_RegisterModel(filename);
	if (!ci->torsoModel) {
		Com_sprintf(filename, sizeof(filename), "models/players/characters/%s/upper.md3", modelName);
		ci->torsoModel = trap_R_RegisterModel(filename);
		if (!ci->torsoModel) {
			Com_Printf("^1Failed to load model file %s\n", filename);
			return qfalse;
		}
	}

	if (headName[0] == '*') {
		Com_sprintf(filename, sizeof(filename), "models/players/heads/%s/%s.md3", &headModelName[1],
			    &headModelName[1]);
	} else {
		Com_sprintf(filename, sizeof(filename), "models/players/%s/head.md3", headName);
	}
	ci->headModel = trap_R_RegisterModel(filename);
	// if the head model could not be found and we didn't load from the heads folder try to load from there
	if (!ci->headModel && headName[0] != '*') {
		Com_sprintf(filename, sizeof(filename), "models/players/heads/%s/%s.md3", headModelName, headModelName);
		ci->headModel = trap_R_RegisterModel(filename);
	}
	if (!ci->headModel) {
		Com_Printf("^1Failed to load model file %s\n", filename);
		return qfalse;
	}
	// if any skins failed to load, return failure
	if (!CG_RegisterClientSkin(ci, teamName, modelName, skinName, headName, headSkinName)) {
		if (teamName && *teamName) {
			Com_Printf("^1Failed to load skin file: %s : %s : %s, %s : %s\n", teamName, modelName, skinName,
				   headName, headSkinName);
			if (ci->team == TEAM_BLUE) {
				Com_sprintf(newTeamName, sizeof(newTeamName), "%s/", DEFAULT_BLUETEAM_NAME);
			} else {
				Com_sprintf(newTeamName, sizeof(newTeamName), "%s/", DEFAULT_REDTEAM_NAME);
			}
			if (!CG_RegisterClientSkin(ci, newTeamName, modelName, skinName, headName, headSkinName)) {
				Com_Printf("^1Failed to load skin file: %s : %s : %s, %s : %s\n", newTeamName, modelName,
					   skinName, headName, headSkinName);
				return qfalse;
			}
		} else {
			Com_Printf("^1Failed to load skin file: %s : %s, %s : %s\n", modelName, skinName, headName,
				   headSkinName);
			return qfalse;
		}
	}
	// load the animations
	Com_sprintf(filename, sizeof(filename), "models/players/%s/animation.cfg", modelName);
	if (!CG_ParseAnimationFile(filename, ci)) {
		Com_sprintf(filename, sizeof(filename), "models/players/characters/%s/animation.cfg", modelName);
		if (!CG_ParseAnimationFile(filename, ci)) {
			Com_Printf("^1Failed to load animation file %s\n", filename);
			return qfalse;
		}
	}

	if (CG_FindClientHeadFile(filename, sizeof(filename), ci, teamName, headName, headSkinName, "icon", "skin")) {
		ci->modelIcon = trap_R_RegisterShaderNoMip(filename);
	} else
	    if (CG_FindClientHeadFile(filename, sizeof(filename), ci, teamName, headName, headSkinName, "icon", "tga"))
	{
		ci->modelIcon = trap_R_RegisterShaderNoMip(filename);
	}

	if (!ci->modelIcon) {
		return qfalse;
	}

	return qtrue;
}

/*
====================
CG_ColorFromString
====================
*/
static void CG_ColorFromString(const char *v, vec3_t color)
{
	int val;

	VectorClear(color);

	val = atoi(v);

	if (val < 1 || val > 7) {
		VectorSet(color, 1, 1, 1);
		return;
	}

	if (val & 1) {
		color[2] = 1.0f;
	}
	if (val & 2) {
		color[1] = 1.0f;
	}
	if (val & 4) {
		color[0] = 1.0f;
	}
}

/*
===================
CG_LoadClientInfo

Load it now, taking the disk hits.
This will usually be deferred to a safe time
===================
*/
static void CG_LoadClientInfo(clientInfo_t * ci)
{
	const char *dir, *fallback;
	int i, modelloaded;
	const char *s;
	int clientNum;
	char teamname[MAX_QPATH];

	teamname[0] = 0;
	modelloaded = qtrue;
	if (!CG_RegisterClientModelname(ci, ci->modelName, ci->skinName, ci->headModelName, ci->headSkinName, teamname)) {
		if (cg_buildScript.integer) {
			CG_Error("CG_RegisterClientModelname( %s, %s, %s, %s %s ) failed", ci->modelName, ci->skinName,
				 ci->headModelName, ci->headSkinName, teamname);
		}
		// fall back to default team name
		if (cgs.gametype >= GT_TEAM) {
			// keep skin name
			if (ci->team == TEAM_BLUE) {
				Q_strncpyz(teamname, DEFAULT_BLUETEAM_NAME, sizeof(teamname));
			} else {
				Q_strncpyz(teamname, DEFAULT_REDTEAM_NAME, sizeof(teamname));
			}
			if (!CG_RegisterClientModelname
			    (ci, DEFAULT_TEAM_MODEL, ci->skinName, DEFAULT_TEAM_HEAD, ci->skinName, teamname)) {
				if (ci->team == TEAM_BLUE)
					Q_strncpyz(ci->skinName, "robber", sizeof(ci->skinName));
				else
					Q_strncpyz(ci->skinName, "default", sizeof(ci->skinName));
				if (!CG_RegisterClientModelname
				    (ci, DEFAULT_TEAM_MODEL, ci->skinName, DEFAULT_TEAM_HEAD, ci->skinName, teamname))
					CG_Error("DEFAULT_TEAM_MODEL / skin (%s/%s) failed to register",
						 DEFAULT_TEAM_MODEL, ci->skinName);
			}
		} else {
			if (!CG_RegisterClientModelname
			    (ci, DEFAULT_MODEL, DEFAULT_SKIN, DEFAULT_MODEL, DEFAULT_SKIN, teamname)) {
				//if ( !CG_RegisterClientModelname( ci, DEFAULT_MODEL, "default", DEFAULT_MODEL, "default", teamname ) ) {
				CG_Error("DEFAULT_MODEL (%s) failed to register", DEFAULT_MODEL);
			}
		}
		modelloaded = qfalse;
	}

	ci->newAnims = qfalse;
	if (ci->torsoModel) {
		orientation_t tag;

		// NiceAss: if the torso model has the "tag_weapon2" (akimbo & briefcase)
		if (trap_R_LerpTag(&tag, ci->torsoModel, 0, 0, 1, "tag_weapon2")) {
			ci->newAnims = qtrue;
		}
	}
	// sounds
	dir = ci->modelName;
	fallback = (cgs.gametype >= GT_TEAM) ? DEFAULT_TEAM_MODEL : DEFAULT_MODEL;

	for (i = 0; i < MAX_CUSTOM_SOUNDS; i++) {
		s = cg_customSoundNames[i];
		if (!s) {
			break;
		}
		ci->sounds[i] = 0;
		// if the model didn't load use the sounds of the default model
		if (modelloaded) {
			ci->sounds[i] = trap_S_RegisterSound(va("sound/player/%s/%s", dir, s + 1), qfalse);
		}
		if (!ci->sounds[i]) {
			ci->sounds[i] = trap_S_RegisterSound(va("sound/player/%s/%s", fallback, s + 1), qfalse);
		}
	}

	ci->deferred = qfalse;

	// reset any existing players and bodies, because they might be in bad
	// frames for this new model
	clientNum = ci - cgs.clientinfo;
	for (i = 0; i < MAX_GENTITIES; i++) {
		if (cg_entities[i].currentState.clientNum == clientNum
		    && cg_entities[i].currentState.eType == ET_PLAYER) {
			CG_ResetPlayerEntity(&cg_entities[i]);
		}
	}
}

/*
======================
CG_CopyClientInfoModel
======================
*/
static void CG_CopyClientInfoModel(clientInfo_t * from, clientInfo_t * to)
{
	VectorCopy(from->headOffset, to->headOffset);
	to->footsteps = from->footsteps;
	to->gender = from->gender;

	to->legsModel = from->legsModel;
	to->legsSkin = from->legsSkin;
	to->torsoModel = from->torsoModel;
	to->torsoSkin = from->torsoSkin;
	to->headModel = from->headModel;
	to->headSkin = from->headSkin;
	to->modelIcon = from->modelIcon;

	to->newAnims = from->newAnims;

	memcpy(to->animations, from->animations, sizeof(to->animations));
	memcpy(to->sounds, from->sounds, sizeof(to->sounds));
}

/*
======================
CG_ScanForExistingClientInfo
======================
*/
static qboolean CG_ScanForExistingClientInfo(clientInfo_t * ci)
{
	int i;
	clientInfo_t *match;

	for (i = 0; i < cgs.maxclients; i++) {
		match = &cgs.clientinfo[i];
		if (!match->infoValid) {
			continue;
		}
		if (match->deferred) {
			continue;
		}
		if (!Q_stricmp(ci->modelName, match->modelName)
		    && !Q_stricmp(ci->skinName, match->skinName)
		    && !Q_stricmp(ci->headModelName, match->headModelName)
		    && !Q_stricmp(ci->headSkinName, match->headSkinName)
		    && !Q_stricmp(ci->blueTeam, match->blueTeam)
		    && !Q_stricmp(ci->redTeam, match->redTeam)
		    && (cgs.gametype < GT_TEAM || ci->team == match->team)) {
			// this clientinfo is identical, so use it's handles

			ci->deferred = qfalse;

			CG_CopyClientInfoModel(match, ci);

			return qtrue;
		}
	}

	// nothing matches, so defer the load
	return qfalse;
}

/*
======================
CG_SetDeferredClientInfo

We aren't going to load it now, so grab some other
client's info to use until we have some spare time.
======================
*/
static void CG_SetDeferredClientInfo(clientInfo_t * ci)
{
	int i;
	clientInfo_t *match;

	// if someone else is already the same models and skins we
	// can just load the client info
	for (i = 0; i < cgs.maxclients; i++) {
		match = &cgs.clientinfo[i];
		if (!match->infoValid || match->deferred) {
			continue;
		}
		if (Q_stricmp(ci->skinName, match->skinName) || Q_stricmp(ci->modelName, match->modelName) ||
//                       Q_stricmp( ci->headModelName, match->headModelName ) ||
//                       Q_stricmp( ci->headSkinName, match->headSkinName ) ||
		    (cgs.gametype >= GT_TEAM && ci->team != match->team)) {
			continue;
		}
		// just load the real info cause it uses the same models and skins
		CG_LoadClientInfo(ci);
		return;
	}

	// if we are in teamplay, only grab a model if the skin is correct
	if (cgs.gametype >= GT_TEAM) {
		for (i = 0; i < cgs.maxclients; i++) {
			match = &cgs.clientinfo[i];
			if (!match->infoValid || match->deferred) {
				continue;
			}
			if (Q_stricmp(ci->skinName, match->skinName) ||
			    (cgs.gametype >= GT_TEAM && ci->team != match->team)) {
				continue;
			}
			ci->deferred = qtrue;
			CG_CopyClientInfoModel(match, ci);
			return;
		}
		// load the full model, because we don't ever want to show
		// an improper team skin.  This will cause a hitch for the first
		// player, when the second enters.  Combat shouldn't be going on
		// yet, so it shouldn't matter
		CG_LoadClientInfo(ci);
		return;
	}
	// find the first valid clientinfo and grab its stuff
	for (i = 0; i < cgs.maxclients; i++) {
		match = &cgs.clientinfo[i];
		if (!match->infoValid) {
			continue;
		}

		ci->deferred = qtrue;
		CG_CopyClientInfoModel(match, ci);
		return;
	}

	// we should never get here...
	CG_Printf("^1CG_SetDeferredClientInfo: no valid clients!\n");

	CG_LoadClientInfo(ci);
}

/* CG_UpdateTeamVars() by Slicer

This is one attempt to update the team count cvars for the UI, each time
a player changes it's userinfo ( team, name, etc )

*/
void CG_UpdateTeamVars()
{
	clientInfo_t *ci;
	int i;
	int Reds, Blues, Spectators, Dmers;

	//Makro - changed from 2 to 4; not really needed, but it's safer
	char v[4];

	Reds = Blues = Spectators = Dmers = 0;

	for (i = 0, ci = cgs.clientinfo; i < cgs.maxclients; i++, ci++) {
		if (!ci->infoValid)
			continue;
		if (ci->team == TEAM_RED)
			Reds++;
		if (ci->team == TEAM_BLUE)
			Blues++;

		if (cgs.gametype >= GT_TEAM) {
			if (ci->team == TEAM_SPECTATOR || ci->team == TEAM_FREE)
				Spectators++;
		} else {
			if (ci->team == TEAM_FREE)
				Dmers++;
			if (ci->team == TEAM_SPECTATOR)
				Spectators++;
		}
	}
	//CG_Printf("Reds: %i, Blues: %i, Spectators: %i\n",Reds, Blues, Spectators);
// JBravo: We count the "teams" differently in DM
	if (cgs.gametype >= GT_TEAM) {
		Com_sprintf(v, sizeof(v), "%i", Reds);
		trap_Cvar_Set("ui_RQ3_teamCount1", v);
		Com_sprintf(v, sizeof(v), "%i", Blues);
		trap_Cvar_Set("ui_RQ3_teamCount2", v);
		Com_sprintf(v, sizeof(v), "%i", Spectators);
		trap_Cvar_Set("ui_RQ3_numSpectators", v);
	} else {
		Com_sprintf(v, sizeof(v), "%i", Dmers);
		trap_Cvar_Set("ui_RQ3_teamCount1", v);
		Com_sprintf(v, sizeof(v), "%i", Spectators);
		trap_Cvar_Set("ui_RQ3_numSpectators", v);
	}
}

/*
======================
CG_NewClientInfo
======================
*/
void CG_NewClientInfo(int clientNum)
{
	clientInfo_t *ci;
	clientInfo_t newInfo;
	const char *configstring;
	const char *v;
	char *slash;

	ci = &cgs.clientinfo[clientNum];

	configstring = CG_ConfigString(clientNum + CS_PLAYERS);
	if (!configstring[0]) {
		memset(ci, 0, sizeof(*ci));
		//Slicer: Recalculate team count cvars
		CG_UpdateTeamVars();
		return;		// player just left
	}
	// build into a temp buffer so the defer checks can use
	// the old value
	memset(&newInfo, 0, sizeof(newInfo));

	// isolate the player's name
	v = Info_ValueForKey(configstring, "n");
	Q_strncpyz(newInfo.name, v, sizeof(newInfo.name));

	// colors
	v = Info_ValueForKey(configstring, "c1");
	CG_ColorFromString(v, newInfo.color1);

	v = Info_ValueForKey(configstring, "c2");
	CG_ColorFromString(v, newInfo.color2);

	// bot skill
	v = Info_ValueForKey(configstring, "skill");
	newInfo.botSkill = atoi(v);

	// handicap
	v = Info_ValueForKey(configstring, "hc");
	newInfo.handicap = atoi(v);

	// wins
	v = Info_ValueForKey(configstring, "w");
	newInfo.wins = atoi(v);

	// losses
	v = Info_ValueForKey(configstring, "l");
	newInfo.losses = atoi(v);

	// team
	v = Info_ValueForKey(configstring, "t");
	newInfo.team = atoi(v);

	// team task
	v = Info_ValueForKey(configstring, "tt");
	newInfo.teamTask = atoi(v);

	// team leader
	v = Info_ValueForKey(configstring, "tl");
	newInfo.teamLeader = atoi(v);

	v = Info_ValueForKey(configstring, "g_redteam");
	Q_strncpyz(newInfo.redTeam, v, MAX_TEAMNAME);

	v = Info_ValueForKey(configstring, "g_blueteam");
	Q_strncpyz(newInfo.blueTeam, v, MAX_TEAMNAME);

	// model
	v = Info_ValueForKey(configstring, "model");
	if (cg_forceModel.integer && cgs.gametype < GT_TEAM) {
		// forcemodel makes everyone use a single model
		// to prevent load hitches
		char modelStr[MAX_QPATH];
		char *skin;

		if (cgs.gametype >= GT_TEAM) {
			Q_strncpyz(newInfo.modelName, DEFAULT_TEAM_MODEL, sizeof(newInfo.modelName));
			Q_strncpyz(newInfo.skinName, "default", sizeof(newInfo.skinName));
		} else {
			trap_Cvar_VariableStringBuffer("model", modelStr, sizeof(modelStr));
			if ((skin = strchr(modelStr, '/')) == NULL) {
				skin = "default";
			} else {
				*skin++ = 0;
			}

			Q_strncpyz(newInfo.skinName, skin, sizeof(newInfo.skinName));
			Q_strncpyz(newInfo.modelName, modelStr, sizeof(newInfo.modelName));
		}

		if (cgs.gametype >= GT_TEAM) {
			// keep skin name
			slash = strchr(v, '/');
			if (slash) {
				Q_strncpyz(newInfo.skinName, slash + 1, sizeof(newInfo.skinName));
			}
		}
	} else {
		Q_strncpyz(newInfo.modelName, v, sizeof(newInfo.modelName));

		slash = strchr(newInfo.modelName, '/');
		if (!slash) {
			// modelName didn not include a skin name
			Q_strncpyz(newInfo.skinName, "default", sizeof(newInfo.skinName));
		} else {
			Q_strncpyz(newInfo.skinName, slash + 1, sizeof(newInfo.skinName));
			// truncate modelName
			*slash = 0;
		}
	}

	// head model
	v = Info_ValueForKey(configstring, "hmodel");
	if (cg_forceModel.integer && cgs.gametype < GT_TEAM) {
		// forcemodel makes everyone use a single model
		// to prevent load hitches
		char modelStr[MAX_QPATH];
		char *skin;

		if (cgs.gametype >= GT_TEAM) {
			Q_strncpyz(newInfo.headModelName, DEFAULT_TEAM_MODEL, sizeof(newInfo.headModelName));
			Q_strncpyz(newInfo.headSkinName, "default", sizeof(newInfo.headSkinName));
		} else {
			trap_Cvar_VariableStringBuffer("headmodel", modelStr, sizeof(modelStr));
			if ((skin = strchr(modelStr, '/')) == NULL) {
				skin = "default";
			} else {
				*skin++ = 0;
			}

			Q_strncpyz(newInfo.headSkinName, skin, sizeof(newInfo.headSkinName));
			Q_strncpyz(newInfo.headModelName, modelStr, sizeof(newInfo.headModelName));
		}

		if (cgs.gametype >= GT_TEAM) {
			// keep skin name
			slash = strchr(v, '/');
			if (slash) {
				Q_strncpyz(newInfo.headSkinName, slash + 1, sizeof(newInfo.headSkinName));
			}
		}
	} else {
		Q_strncpyz(newInfo.headModelName, v, sizeof(newInfo.headModelName));

		slash = strchr(newInfo.headModelName, '/');
		if (!slash) {
			// modelName didn not include a skin name
			Q_strncpyz(newInfo.headSkinName, "default", sizeof(newInfo.headSkinName));
		} else {
			Q_strncpyz(newInfo.headSkinName, slash + 1, sizeof(newInfo.headSkinName));
			// truncate modelName
			*slash = 0;
		}
	}

	// scan for an existing clientinfo that matches this modelname
	// so we can avoid loading checks if possible
	if (!CG_ScanForExistingClientInfo(&newInfo)) {
		qboolean forceDefer;

		forceDefer = trap_MemoryRemaining() < 4000000;

		// if we are defering loads, just have it pick the first valid
		if (forceDefer || (cg_deferPlayers.integer && !cg_buildScript.integer && !cg.loading)) {
			// keep whatever they had if it won't violate team skins
			CG_SetDeferredClientInfo(&newInfo);
			// if we are low on memory, leave them with this model
			if (forceDefer) {
				CG_Printf("^1Memory is low.  Using deferred model.\n");
				newInfo.deferred = qfalse;
			}
		} else {
			CG_LoadClientInfo(&newInfo);
		}
	}
	// replace whatever was there with the new one
	newInfo.infoValid = qtrue;
	*ci = newInfo;
	CG_UpdateTeamVars();
}

/*
======================
CG_LoadDeferredPlayers

Called each frame when a player is dead
and the scoreboard is up
so deferred players can be loaded
======================
*/
void CG_LoadDeferredPlayers(void)
{
	int i;
	clientInfo_t *ci;

	// scan for a deferred player to load
	for (i = 0, ci = cgs.clientinfo; i < cgs.maxclients; i++, ci++) {
		if (ci->infoValid && ci->deferred) {
			// if we are low on memory, leave it deferred
			if (trap_MemoryRemaining() < 4000000) {
				CG_Printf("^1Memory is low.  Using deferred model.\n");
				ci->deferred = qfalse;
				continue;
			}
			CG_LoadClientInfo(ci);
//                      break;
		}
	}
}

/*
=============================================================================

PLAYER ANIMATION

=============================================================================
*/
/* [QUARANTINE] - Weapon Animations
===============
CG_SetWeaponLerpFrame

may include ANIM_TOGGLEBIT
===============
*/
static void CG_SetWeaponLerpFrame(clientInfo_t * ci, lerpFrame_t * lf, int newAnimation)
{
	animation_t *anim;

	lf->animationNumber = newAnimation;
	newAnimation &= ~ANIM_TOGGLEBIT;

	if (newAnimation < 0 || newAnimation >= MAX_WEAPON_ANIMATIONS) {
		CG_Error("Bad weapon animation number: %i", newAnimation);
	}
	// Elder: selecting the right weapon animation
	if (newAnimation == WP_ANIM_ACTIVATE || newAnimation == WP_ANIM_THROWACTIVATE)
		anim = &cg_weapons[cg.weaponSelect].animations[newAnimation];
	else
		anim = &cg_weapons[cg.snap->ps.weapon].animations[newAnimation];

	lf->animation = anim;
	lf->animationTime = lf->frameTime + anim->initialLerp;

	if (cg_debugAnim.integer) {
		CG_Printf("Weapon Anim: %i\n", newAnimation);
		// Elder: more info
		//CG_Printf( "Snap Weapon: %i\n", cg.snap->ps.weapon);
		//CG_Printf( "Desired Weapon: %i\n", cg.weaponSelect);
	}
	//Elder: reset frame so there is no lerping between new animations
	lf->oldFrame = lf->frame = lf->animation->firstFrame;

}

/*
===============
CG_SetLerpFrameAnimation

may include ANIM_TOGGLEBIT
===============
*/
static void CG_SetLerpFrameAnimation(clientInfo_t * ci, lerpFrame_t * lf, int newAnimation)
{
	animation_t *anim;

	lf->animationNumber = newAnimation;
	newAnimation &= ~ANIM_TOGGLEBIT;

	if (newAnimation < 0 || newAnimation >= MAX_TOTALANIMATIONS) {
		CG_Error("Bad animation number: %i", newAnimation);
	}

	anim = &ci->animations[newAnimation];

	lf->animation = anim;
	lf->animationTime = lf->frameTime + anim->initialLerp;

	if (cg_debugAnim.integer) {
		CG_Printf("Anim: %i\n", newAnimation);
	}
}

/*
===============
CG_RunLerpFrame

Sets cg.snap, cg.oldFrame, and cg.backlerp
cg.time should be between oldFrameTime and frameTime after exit
===============
*/
static void CG_RunLerpFrame(clientInfo_t * ci, lerpFrame_t * lf, int newAnimation, float speedScale,
			    qboolean weaponAnim)
{
	int f, numFrames;
	animation_t *anim;

//      qboolean        resetAnim = qfalse;

	// debugging tool to get no animations
	if (cg_animSpeed.integer == 0) {
		lf->oldFrame = lf->frame = lf->backlerp = 0;
		return;
	}
	// see if the animation sequence is switching
	if (newAnimation != lf->animationNumber || !lf->animation) {
		if (weaponAnim) {
			lf->frameTime = lf->oldFrameTime = cg.time;
			CG_SetWeaponLerpFrame(ci, lf, newAnimation);
			//resetAnim = qtrue;
		} else {
			CG_SetLerpFrameAnimation(ci, lf, newAnimation);
		}
	}
	// Elder's chunk of debug code
	/*
	   if (weaponAnim && cg_debugAnim.integer)
	   {
	   CG_Printf("(%d)==================\n", cg.time);
	   CG_Printf("lf->frame (%d), lf->frameTime (%d),\n", lf->frame, lf->frameTime);
	   CG_Printf("lf->oldFrame (%d), lf->oldFrameTime (%d),\n", lf->oldFrame, lf->oldFrameTime);
	   } */

	// if we have passed the current frame, move it to
	// oldFrame and calculate a new frame
	if (cg.time >= lf->frameTime) {
		lf->oldFrame = lf->frame;
		lf->oldFrameTime = lf->frameTime;

		// get the next frame based on the animation
		anim = lf->animation;
		if (!anim->frameLerp) {
			return;	// shouldn't happen
		}
		if (cg.time < lf->animationTime) {
			lf->frameTime = lf->animationTime;	// initial lerp
		} else {
			lf->frameTime = lf->oldFrameTime + anim->frameLerp;
		}
		f = (lf->frameTime - lf->animationTime) / anim->frameLerp;
		f *= speedScale;	// adjust for haste, etc

		numFrames = anim->numFrames;
		if (anim->flipflop) {
			numFrames *= 2;
		}

		if (f >= numFrames) {
			f -= numFrames;
			if (anim->loopFrames) {
				f %= anim->loopFrames;
				f += anim->numFrames - anim->loopFrames;
			} else {
				f = numFrames - 1;
				// the animation is stuck at the end, so it
				// can immediately transition to another sequence
				lf->frameTime = cg.time;
			}
		}
		if (anim->reversed) {
			lf->frame = anim->firstFrame + anim->numFrames - 1 - f;
		} else if (anim->flipflop && f >= anim->numFrames) {
			lf->frame = anim->firstFrame + anim->numFrames - 1 - (f % anim->numFrames);
		} else {
			//Elder's stuff
			//if (resetAnim)
			//lf->frame = anim->firstFrame;
			//else
			lf->frame = anim->firstFrame + f;
		}
		if (cg.time > lf->frameTime) {
			lf->frameTime = cg.time;
			if (cg_debugAnim.integer) {
				CG_Printf("Clamp lf->frameTime\n");
			}
		}
	}

	if (lf->frameTime > cg.time + 200) {
		lf->frameTime = cg.time;
	}

	if (lf->oldFrameTime > cg.time) {
		lf->oldFrameTime = cg.time;
	}
	// calculate current lerp value
	if (lf->frameTime == lf->oldFrameTime) {
		lf->backlerp = 0;
	} else {
		lf->backlerp = 1.0 - (float) (cg.time - lf->oldFrameTime) / (lf->frameTime - lf->oldFrameTime);
	}

}

/*
===============
CG_ClearLerpFrame
===============
*/
static void CG_ClearLerpFrame(clientInfo_t * ci, lerpFrame_t * lf, int animationNumber)
{
	lf->frameTime = lf->oldFrameTime = cg.time;
	CG_SetLerpFrameAnimation(ci, lf, animationNumber);
	lf->oldFrame = lf->frame = lf->animation->firstFrame;
}

/* [QUARANTINE] - Weapon Animations
===============
CG_WeaponAnimation

This is called from cg_weapons.c
===============
*/
void CG_WeaponAnimation(centity_t * cent, int *weaponOld, int *weapon, float *weaponBackLerp)
{
	clientInfo_t *ci;
	int clientNum;
	int stateAnimNum;
	int weapAnimNum;

	clientNum = cent->currentState.clientNum;

	if (cg_noPlayerAnims.integer) {
		*weaponOld = *weapon = 0;
		return;
	}

	ci = &cgs.clientinfo[clientNum];

	// Elder: FIXME? - hack hehe
	// Compare master copy with existing animation frames
	// The only time when they are supposed to be mismatched is when
	// switching to a new animation (handled in first condition)
	// Even if they are wrong, yet identical, you can still work with it
	// TODO: Should also check loop and flipflop but should suffice for 99% of the cases
	stateAnimNum = cent->currentState.generic1 & ~ANIM_TOGGLEBIT;
	weapAnimNum = cent->pe.weapon.animationNumber & ~ANIM_TOGGLEBIT;
	if (stateAnimNum == weapAnimNum) {
		if (cg_weapons[cent->currentState.weapon].animations[stateAnimNum].firstFrame ==
		    cent->pe.weapon.animation->firstFrame
		    && cg_weapons[cent->currentState.weapon].animations[stateAnimNum].numFrames ==
		    cent->pe.weapon.animation->numFrames) {	//Makro - possible bug?
			// don't compile my test spam
#if 0
			CG_Printf("Animation info okay: (%i versus %i) and (%i versus %i)\n",
				  cg_weapons[cent->currentState.weapon].animations[stateAnimNum].firstFrame,
				  cent->pe.weapon.animation->firstFrame,
				  cg_weapons[cent->currentState.weapon].animations[stateAnimNum].numFrames,
				  cent->pe.weapon.animation->numFrames);
#endif
		} else {
			// don't compile my test spam
#if 0
			CG_Printf("Mismatch of animation info (%i versus %i) and (%i versus %i)\n",
				  cg_weapons[cent->currentState.weapon].animations[stateAnimNum].firstFrame,
				  cent->pe.weapon.animation->firstFrame,
				  cg_weapons[cent->currentState.weapon].animations[stateAnimNum].numFrames,
				  cent->pe.weapon.animation->numFrames);
			CG_Printf("Compensating...\n");
#endif
			cent->pe.weapon.animation = &cg_weapons[cent->currentState.weapon].animations[stateAnimNum];
		}
	} else {
		//CG_Printf("Mismatch of animation number (%i versus %i)\n", stateAnimNum, weapAnimNum);
	}

	CG_RunLerpFrame(ci, &cent->pe.weapon, cent->currentState.generic1, 1, qtrue);

	// QUARANTINE - Debug - Animations
#if 0
	if (cg_debugAnim.integer)
		if (cent->pe.weapon.oldFrame || cent->pe.weapon.frame || cent->pe.weapon.backlerp) {
			CG_Printf("weaponOld: %i weaponFrame: %i weaponBack: %i\n",
				  cent->pe.weapon.oldFrame, cent->pe.weapon.frame, cent->pe.weapon.backlerp);
		}
#endif

	*weaponOld = cent->pe.weapon.oldFrame;
	*weapon = cent->pe.weapon.frame;
	*weaponBackLerp = cent->pe.weapon.backlerp;

}

// END

/*
===============
CG_PlayerAnimation
===============
*/
static void CG_PlayerAnimation(centity_t * cent, int *legsOld, int *legs, float *legsBackLerp,
			       int *torsoOld, int *torso, float *torsoBackLerp)
{
	clientInfo_t *ci;
	int clientNum;
	float speedScale;

	clientNum = cent->currentState.clientNum;

	if (cg_noPlayerAnims.integer) {
		*legsOld = *legs = *torsoOld = *torso = 0;
		return;
	}

	speedScale = 1;

	ci = &cgs.clientinfo[clientNum];

	// do the shuffle turn frames locally
	if (cent->pe.legs.yawing && (cent->currentState.legsAnim & ~ANIM_TOGGLEBIT) == LEGS_IDLE) {
		CG_RunLerpFrame(ci, &cent->pe.legs, LEGS_TURN, speedScale, qfalse);
	} else {
		CG_RunLerpFrame(ci, &cent->pe.legs, cent->currentState.legsAnim, speedScale, qfalse);
	}

	*legsOld = cent->pe.legs.oldFrame;
	*legs = cent->pe.legs.frame;
	*legsBackLerp = cent->pe.legs.backlerp;

	CG_RunLerpFrame(ci, &cent->pe.torso, cent->currentState.torsoAnim, speedScale, qfalse);

	*torsoOld = cent->pe.torso.oldFrame;
	*torso = cent->pe.torso.frame;
	*torsoBackLerp = cent->pe.torso.backlerp;
}

/*
=============================================================================

PLAYER ANGLES

=============================================================================
*/

/*
==================
CG_SwingAngles
==================
*/
static void CG_SwingAngles(float destination, float swingTolerance, float clampTolerance,
			   float speed, float *angle, qboolean * swinging)
{
	float swing;
	float move;
	float scale;

	if (!*swinging) {
		// see if a swing should be started
		swing = AngleSubtract(*angle, destination);
		if (swing > swingTolerance || swing < -swingTolerance) {
			*swinging = qtrue;
		}
	}

	if (!*swinging) {
		return;
	}
	// modify the speed depending on the delta
	// so it doesn't seem so linear
	swing = AngleSubtract(destination, *angle);
	scale = fabs(swing);
	if (scale < swingTolerance * 0.5) {
		scale = 0.5;
	} else if (scale < swingTolerance) {
		scale = 1.0;
	} else {
		scale = 2.0;
	}

	// swing towards the destination angle
	if (swing >= 0) {
		move = cg.frametime * scale * speed;
		if (move >= swing) {
			move = swing;
			*swinging = qfalse;
		}
		*angle = AngleMod(*angle + move);
	} else if (swing < 0) {
		move = cg.frametime * scale * -speed;
		if (move <= swing) {
			move = swing;
			*swinging = qfalse;
		}
		*angle = AngleMod(*angle + move);
	}
	// clamp to no more than tolerance
	swing = AngleSubtract(destination, *angle);
	if (swing > clampTolerance) {
		*angle = AngleMod(destination - (clampTolerance - 1));
	} else if (swing < -clampTolerance) {
		*angle = AngleMod(destination + (clampTolerance - 1));
	}
}

/*
=================
CG_AddPainTwitch
=================
*/
static void CG_AddPainTwitch(centity_t * cent, vec3_t torsoAngles)
{
	int t;
	float f;

	t = cg.time - cent->pe.painTime;
	if (t >= PAIN_TWITCH_TIME) {
		return;
	}

	f = 1.0 - (float) t / PAIN_TWITCH_TIME;

	if (cent->pe.painDirection) {
		torsoAngles[ROLL] += 20 * f;
	} else {
		torsoAngles[ROLL] -= 20 * f;
	}
}

/*
===============
CG_PlayerAngles

Handles seperate torso motion

  legs pivot based on direction of movement

  head always looks exactly at cent->lerpAngles

  if motion < 20 degrees, show in head only
  if < 45 degrees, also show in torso
===============
*/
static void CG_PlayerAngles(centity_t * cent, vec3_t legs[3], vec3_t torso[3], vec3_t head[3])
{
	vec3_t legsAngles, torsoAngles, headAngles;
	float dest;
	static int movementOffsets[8] = { 0, 22, 45, -22, 0, 22, -45, -22 };
	vec3_t velocity;
	float speed;
	int dir, clientNum;
	clientInfo_t *ci;

	VectorCopy(cent->lerpAngles, headAngles);
	headAngles[YAW] = AngleMod(headAngles[YAW]);
	VectorClear(legsAngles);
	VectorClear(torsoAngles);

	// --------- yaw -------------

	// allow yaw to drift a bit
	if ((cent->currentState.legsAnim & ~ANIM_TOGGLEBIT) != LEGS_IDLE
	    || (cent->currentState.torsoAnim & ~ANIM_TOGGLEBIT) != TORSO_STAND) {
		// if not standing still, always point all in the same direction
		cent->pe.torso.yawing = qtrue;	// always center
		cent->pe.torso.pitching = qtrue;	// always center
		cent->pe.legs.yawing = qtrue;	// always center
	}
	// adjust legs for movement dir
	if (cent->currentState.eFlags & EF_DEAD) {
		// don't let dead bodies twitch
		dir = 0;
	} else {
		dir = cent->currentState.angles2[YAW];
		if (dir < 0 || dir > 7) {
			CG_Error("Bad player movement angle");
		}
	}
	legsAngles[YAW] = headAngles[YAW] + movementOffsets[dir];
	torsoAngles[YAW] = headAngles[YAW] + 0.25 * movementOffsets[dir];

	// torso
	CG_SwingAngles(torsoAngles[YAW], 25, 90, cg_swingSpeed.value, &cent->pe.torso.yawAngle, &cent->pe.torso.yawing);
	CG_SwingAngles(legsAngles[YAW], 40, 90, cg_swingSpeed.value, &cent->pe.legs.yawAngle, &cent->pe.legs.yawing);

	torsoAngles[YAW] = cent->pe.torso.yawAngle;
	legsAngles[YAW] = cent->pe.legs.yawAngle;

	// --------- pitch -------------

	// only show a fraction of the pitch angle in the torso
	if (headAngles[PITCH] > 180) {
		dest = (-360 + headAngles[PITCH]) * 0.75f;
	} else {
		dest = headAngles[PITCH] * 0.75f;
	}
	CG_SwingAngles(dest, 15, 30, 0.1f, &cent->pe.torso.pitchAngle, &cent->pe.torso.pitching);
	torsoAngles[PITCH] = cent->pe.torso.pitchAngle;

	//
	clientNum = cent->currentState.clientNum;
	if (clientNum >= 0 && clientNum < MAX_CLIENTS) {
		ci = &cgs.clientinfo[clientNum];
		if (ci->fixedtorso) {
			torsoAngles[PITCH] = 0.0f;
		}
	}
	// --------- roll -------------

	// lean towards the direction of travel
	VectorCopy(cent->currentState.pos.trDelta, velocity);
	speed = VectorNormalize(velocity);
	if (speed) {
		vec3_t axis[3];
		float side;

		speed *= 0.05f;

		AnglesToAxis(legsAngles, axis);
		side = speed * DotProduct(velocity, axis[1]);
		legsAngles[ROLL] -= side;

		side = speed * DotProduct(velocity, axis[0]);
		legsAngles[PITCH] += side;
	}
	//
	clientNum = cent->currentState.clientNum;
	if (clientNum >= 0 && clientNum < MAX_CLIENTS) {
		ci = &cgs.clientinfo[clientNum];
		if (ci->fixedlegs) {
			legsAngles[YAW] = torsoAngles[YAW];
			legsAngles[PITCH] = 0.0f;
			legsAngles[ROLL] = 0.0f;
		}
	}
	// pain twitch
	CG_AddPainTwitch(cent, torsoAngles);

	// pull the angles back out of the hierarchial chain
	AnglesSubtract(headAngles, torsoAngles, headAngles);
	AnglesSubtract(torsoAngles, legsAngles, torsoAngles);
	AnglesToAxis(legsAngles, legs);
	AnglesToAxis(torsoAngles, torso);
	AnglesToAxis(headAngles, head);
}

//==========================================================================

/*
===============
CG_HCSmokeTrail

Added by Elder
===============
*/
static void CG_HCSmokeTrail(centity_t * cent)
{
	localEntity_t *smoke;
	vec3_t origin;
	vec3_t velocity;
	int anim;
	int smokeTime;

	if (cg_noProjectileTrail.integer || cent->trailTime > cg.time) {
		return;
	}

	anim = cent->pe.legs.animationNumber & ~ANIM_TOGGLEBIT;
	if (anim != BOTH_DEATH1 && anim != BOTH_DEAD1 &&
	    anim != BOTH_DEATH2 && anim != BOTH_DEAD2 && anim != BOTH_DEATH3 && anim != BOTH_DEAD3) {
		return;
	}
	// setup smoke depending on state
	if (anim == BOTH_DEAD1 || anim == BOTH_DEAD2 || anim == BOTH_DEAD3) {
		velocity[0] = rand() % 10 - 5;
		velocity[1] = rand() % 8 - 4;
		velocity[2] = 24 + rand() % 40;
		cent->trailTime += 350;
		smokeTime = 2250 + rand() % 250;
	} else {
		velocity[0] = 0;
		velocity[1] = 0;
		velocity[2] = 10 + rand() % 16;
		cent->trailTime += 150;
		smokeTime = 1400 + rand() % 200;
	}

	if (cent->trailTime < cg.time) {
		cent->trailTime = cg.time;
	}

	VectorCopy(cent->lerpOrigin, origin);
	origin[2] -= 6;

	smoke = CG_SmokePuff(origin, velocity,
			     20 + rand() % 4, 1, 1, 1, 0.33f, smokeTime, cg.time, 0, 0, cgs.media.smokePuffShader);

	// use the optimized local entity add
	smoke->leType = LE_SCALE_FADE;
}

/*
===============
CG_BreathPuffs
// NiceAss: Used now. No londer MISSIONPACK
===============
*/
#define NUM_BREATH_PUFFS		4
#define BREATH_PUFF_LIFE		1100
#define BREATH_PUFF_LIFE_EXTRA	400
#define BREATH_PUFF_ALPHA		0.4
#define BREATH_PUFF_SIZE		8
#define BREATH_PUFF

static void CG_BreathPuffs(centity_t * cent, refEntity_t * head)
{
	clientInfo_t *ci;
	vec3_t dir, origin;
	int contents, i;
	localEntity_t *puff[NUM_BREATH_PUFFS];

	ci = &cgs.clientinfo[cent->currentState.number];

	if (!cg_enableBreath.integer) {
		return;
	}
	if (cent->currentState.number == cg.snap->ps.clientNum && !cg.renderingThirdPerson) {
		return;
	}
	if (cent->currentState.eFlags & EF_DEAD) {
		return;
	}
	contents = trap_CM_PointContents(head->origin, 0);
	if (contents & (CONTENTS_WATER | CONTENTS_SLIME | CONTENTS_LAVA)) {
		return;
	}
	if (ci->breathPuffTime > cg.time) {
		return;
	}

	//VectorSet(up, 0, 0, 8);
	VectorMA(head->origin, 6, head->axis[0], origin);
	VectorMA(origin, -2, head->axis[2], origin);
	//Makro - the damn thing was too big !
	//Changed 'radius' from 16 to 8 and alpha from 1 to 0.4
	//CG_SmokePuff(origin, up, 8, 1, 1, 1, 0.4f, 1500, cg.time, cg.time + 400, LEF_PUFF_DONT_SCALE,
	//	     cgs.media.shotgunSmokePuffShader);

	//cool new code
	for (i=0; i<NUM_BREATH_PUFFS; i++)
	{
		VectorCopy(head->axis[0], dir);
		//forward
		VectorMA(dir, crandom() * 0.3f, head->axis[0], dir);
		//left-right
		VectorMA(dir, crandom() * 0.3f, head->axis[1], dir);
		//up-down
		VectorMA(dir, -0.3f + crandom() * 0.3f, head->axis[2], dir);
		VectorScale(dir, 3+random()*3, dir);
		puff[i] = CG_SmokePuff(origin, dir, 3.5f+crandom()*0.5f, 1, 1, 1, 0.15f+crandom()*0.05f, 1000+random()*500, cg.time, 0,
			LEF_PUFF_DONT_SCALE, cgs.media.shotgunSmokePuffShader);
	}
	
	ci->breathPuffTime = cg.time + 2000;
}

/*
===============
CG_DustTrail
===============
*/
// JBravo: no longer in MISSIONPACK.
static void CG_DustTrail(centity_t * cent)
{
	int anim;
	localEntity_t *dust;
	vec3_t end, vel;
	trace_t tr;
	//Makro - added
	vec4_t color = {.8f, .8f, 0.7f, 0.33f};
	int Material;

	if (!cg_enableDust.integer)
		return;

	if (cent->dustTrailTime > cg.time) {
		return;
	}

	anim = cent->pe.legs.animationNumber & ~ANIM_TOGGLEBIT;
	if (anim != LEGS_LANDB && anim != LEGS_LAND) {
		return;
	}

	cent->dustTrailTime += 40;
	if (cent->dustTrailTime < cg.time) {
		cent->dustTrailTime = cg.time;
	}

	VectorCopy(cent->currentState.pos.trBase, end);
	end[2] -= 64;
	CG_Trace(&tr, cent->currentState.pos.trBase, NULL, NULL, end, cent->currentState.number, MASK_PLAYERSOLID);

	if (!(tr.surfaceFlags & SURF_DUST))
		return;
	//Makro - if the surface has a snow texture, use a different color for the dust puff
	Material = GetMaterialFromFlag(tr.surfaceFlags);
	if (IsSnowMat(Material)) {
		color[0] = color[1] = color[2] = 1.0f;
	}

	VectorCopy(cent->currentState.pos.trBase, end);
	end[2] -= 16;

	VectorSet(vel, 0, 0, -30);
	dust = CG_SmokePuff(end, vel, 24, color[0], color[1], color[2], color[3], 500, cg.time, 0, 0, cgs.media.dustPuffShader);
}

/*
===============
CG_TrailItem
===============
*/
static void CG_TrailItem(centity_t * cent, qhandle_t hModel, refEntity_t *torso)
{
	// NiceAss: This stuff sux!
	/*
	refEntity_t ent;
	vec3_t angles;
	vec3_t axis[3];

	VectorCopy(cent->lerpAngles, angles);
	angles[PITCH] = 0;
	angles[ROLL] = 0;
	AnglesToAxis(angles, axis);

	memset(&ent, 0, sizeof(ent));
	VectorMA(cent->lerpOrigin, -16, axis[0], ent.origin);
	ent.origin[2] += 16;
	angles[YAW] += 90;
	AnglesToAxis(angles, ent.axis);

	ent.hModel = hModel;
	trap_R_AddRefEntityToScene(&ent);
	*/

	// NiceAss: This way kicks more ass
	refEntity_t	flag;
	vec3_t		angles;

	// show the flag pole model
	memset(&flag, 0, sizeof(flag));

	flag.hModel = hModel;

	VectorCopy(torso->lightingOrigin, flag.lightingOrigin);
	flag.shadowPlane = torso->shadowPlane;
	flag.renderfx = torso->renderfx;
	
	angles[YAW] = 140;
	AnglesToAxis(angles, flag.axis);

	// THE hack. Position the flag where the head is
	CG_PositionRotatedEntityOnTag(&flag, torso, torso->hModel, "tag_head");

	// Move the flag forward a little
	VectorMA(flag.origin, -17, flag.axis[0], flag.origin);
	// Move the flag down  a little
	VectorMA(flag.origin, -14, flag.axis[2], flag.origin);

	VectorScale(flag.axis[0], 0.8f, flag.axis[0]);
	VectorScale(flag.axis[1], 0.8f, flag.axis[1]);
	VectorScale(flag.axis[2], 0.8f, flag.axis[2]);

	trap_R_AddRefEntityToScene(&flag);
}

/*
===============
CG_PlayerFlag
100% recoded by the one and only NiceAss
===============
*/
static void CG_PlayerFlag(centity_t * cent, qhandle_t hModel, refEntity_t * torso)
{
	vec3_t angles, offset;
	refEntity_t	flag;

	// show the flag pole model
	memset(&flag, 0, sizeof(flag));

	flag.hModel = hModel;

	VectorCopy(torso->lightingOrigin, flag.lightingOrigin);
	flag.shadowPlane = torso->shadowPlane;
	flag.renderfx = torso->renderfx;
	flag.nonNormalizedAxes = qtrue;

	angles[YAW] = 0;
	angles[PITCH] = 0;
	angles[ROLL] = 90;
	AnglesToAxis(angles, flag.axis);

	// Evil hardcoded offsets!
	VectorSet( offset, -4, 0, -7 );
	CG_PositionRotatedOffsetEntityOnTag( &flag, torso, torso->hModel, "tag_weapon2", offset );

	trap_R_AddRefEntityToScene(&flag);
}

/*
===============
CG_PlayerPowerups
===============
*/
static void CG_PlayerPowerups(centity_t * cent, refEntity_t * torso)
{
	int powerups;
	clientInfo_t *ci;

	powerups = cent->currentState.powerups;
	if (!powerups) {
		return;
	}
	ci = &cgs.clientinfo[cent->currentState.clientNum];
	// redflag
	if (powerups & (1 << PW_REDFLAG)) {
		if (ci->newAnims) {
			CG_PlayerFlag(cent, cgs.media.redFlagModel, torso);
		} else {
			CG_TrailItem(cent, cgs.media.redFlagModel, torso);
		}
// JBravo: no glowing in RQ3
//		trap_R_AddLightToScene(cent->lerpOrigin, 200 + (rand() & 31), 1.0, 0.2f, 0.2f);
	}
	// blueflag
	if (powerups & (1 << PW_BLUEFLAG)) {
		if (ci->newAnims) {
			CG_PlayerFlag(cent, cgs.media.blueFlagModel, torso);
		} else {
			CG_TrailItem(cent, cgs.media.blueFlagModel, torso);
		}
// JBravo: no glowing in RQ3
//		trap_R_AddLightToScene(cent->lerpOrigin, 200 + (rand() & 31), 0.2f, 0.2f, 1.0);
	}
	// neutralflag
	if (powerups & (1 << PW_NEUTRALFLAG)) {
		if (ci->newAnims) {
			CG_PlayerFlag(cent, cgs.media.neutralFlagModel, torso);
		} else {
			CG_TrailItem(cent, cgs.media.neutralFlagModel, torso);
		}
// JBravo: no glowing in RQ3
//		trap_R_AddLightToScene(cent->lerpOrigin, 200 + (rand() & 31), 1.0, 1.0, 1.0);
	}
}

/*
===============
CG_PlayerFloatSprite

Float a sprite over the player's head
===============
*/
static void CG_PlayerFloatSprite(centity_t * cent, qhandle_t shader)
{
	int rf;
	refEntity_t ent;

	// NiceAss: Don't draw floating sprites for enemies in TP
	if ( cgs.gametype >= GT_TEAM && 
		 cgs.clientinfo[cent->currentState.clientNum].team != cg.snap->ps.persistant[PERS_SAVEDTEAM] &&
		 ( cg.snap->ps.persistant[PERS_SAVEDTEAM] == TEAM_RED || 
		 cg.snap->ps.persistant[PERS_SAVEDTEAM] == TEAM_BLUE ) )
		 return;

	if (cent->currentState.number == cg.snap->ps.clientNum && !cg.renderingThirdPerson) {
		rf = RF_THIRD_PERSON;	// only show in mirrors
	} else {
		rf = 0;
	}

	memset(&ent, 0, sizeof(ent));
	VectorCopy(cent->lerpOrigin, ent.origin);
	ent.origin[2] += 48;
	ent.reType = RT_SPRITE;
	ent.customShader = shader;
	ent.radius = 10;
	ent.renderfx = rf;
	ent.shaderRGBA[0] = 255;
	ent.shaderRGBA[1] = 255;
	ent.shaderRGBA[2] = 255;
	ent.shaderRGBA[3] = 255;
	trap_R_AddRefEntityToScene(&ent);
}

/*
===============
CG_PlayerSprites

Float sprites over the player's head
===============
*/
static void CG_PlayerSprites(centity_t * cent)
{
	int team;

	if (cent->currentState.eFlags & EF_CONNECTION) {
		CG_PlayerFloatSprite(cent, cgs.media.connectionShader);
		return;
	}
// JBravo: stopping talk bubbles appearing over dead peoples heads
	if ((cent->currentState.eFlags & EF_TALK) && !(cent->currentState.eFlags & EF_DEAD)) {
		CG_PlayerFloatSprite(cent, cgs.media.balloonShader);
		return;
	}
// JBravo: we dont want the Q3 awards
/*	if (cent->currentState.eFlags & EF_AWARD_IMPRESSIVE) {
		CG_PlayerFloatSprite(cent, cgs.media.medalImpressive);
		return;
	}

	if (cent->currentState.eFlags & EF_AWARD_EXCELLENT) {
		CG_PlayerFloatSprite(cent, cgs.media.medalExcellent);
		return;
	} */

	if (cent->currentState.eFlags & EF_AWARD_GAUNTLET) {
		CG_PlayerFloatSprite(cent, cgs.media.medalGauntlet);
		return;
	}

/*	if (cent->currentState.eFlags & EF_AWARD_DEFEND) {
		CG_PlayerFloatSprite(cent, cgs.media.medalDefend);
		return;
	}

	if (cent->currentState.eFlags & EF_AWARD_ASSIST) {
		CG_PlayerFloatSprite(cent, cgs.media.medalAssist);
		return;
	}

	if (cent->currentState.eFlags & EF_AWARD_CAP) {
		CG_PlayerFloatSprite(cent, cgs.media.medalCapture);
		return;
	}
*/
// JBravo: no triangles over teammates.
	if (cgs.gametype >= GT_TEAM) {
		return;
	}

	team = cgs.clientinfo[cent->currentState.clientNum].team;
	if (!(cent->currentState.eFlags & EF_DEAD) &&
	    cg.snap->ps.persistant[PERS_TEAM] == team && cgs.gametype >= GT_TEAM) {
		if (cg_drawFriend.integer) {
			CG_PlayerFloatSprite(cent, cgs.media.friendShader);
		}
		return;
	}
}

/*
===============
CG_PlayerShadow

Returns the Z component of the surface being shadowed

  should it return a full plane instead of a Z?
===============
*/
#define	SHADOW_DISTANCE		128
static qboolean CG_PlayerShadow(centity_t * cent, float *shadowPlane)
{
	vec3_t end, mins = { -15, -15, 0 }, maxs = {
	15, 15, 2};
	trace_t trace;
	float alpha;

	*shadowPlane = 0;

	if (cg_shadows.integer == 0) {
		return qfalse;
	}

	// send a trace down from the player to the ground
	VectorCopy(cent->lerpOrigin, end);
	end[2] -= SHADOW_DISTANCE;

	trap_CM_BoxTrace(&trace, cent->lerpOrigin, end, mins, maxs, 0, MASK_PLAYERSOLID);

	// no shadow if too high
	if (trace.fraction == 1.0 || trace.startsolid || trace.allsolid) {
		return qfalse;
	}

	*shadowPlane = trace.endpos[2] + 1;

	if (cg_shadows.integer != 1) {	// no mark for stencil or projection shadows
		return qtrue;
	}
	// fade the shadow out with height
	alpha = 1.0 - trace.fraction;

	// bk0101022 - hack / FPE - bogus planes?
	//assert( DotProduct( trace.plane.normal, trace.plane.normal ) != 0.0f )

	// add the mark as a temporary, so it goes directly to the renderer
	// without taking a spot in the cg_marks array
	//Makro - 24 is too big, changing to 20
	CG_ImpactMark(cgs.media.shadowMarkShader, trace.endpos, trace.plane.normal,
		      cent->pe.legs.yawAngle, alpha, alpha, alpha, 1, qfalse, 20, qtrue);

	return qtrue;
}

/*
===============
CG_PlayerSplash

Draw a mark at the water surface
===============
*/
static void CG_PlayerSplash(centity_t * cent)
{
	vec3_t start, end;
	trace_t trace;
	int contents;
	polyVert_t verts[4];

	if (!cg_shadows.integer) {
		return;
	}

	VectorCopy(cent->lerpOrigin, end);
	end[2] -= 24;

	// if the feet aren't in liquid, don't make a mark
	// this won't handle moving water brushes, but they wouldn't draw right anyway...
	contents = trap_CM_PointContents(end, 0);
	if (!(contents & (CONTENTS_WATER | CONTENTS_SLIME | CONTENTS_LAVA))) {
		return;
	}

	VectorCopy(cent->lerpOrigin, start);
	start[2] += 32;

	// if the head isn't out of liquid, don't make a mark
	contents = trap_CM_PointContents(start, 0);
	if (contents & (CONTENTS_SOLID | CONTENTS_WATER | CONTENTS_SLIME | CONTENTS_LAVA)) {
		return;
	}
	// trace down to find the surface
	trap_CM_BoxTrace(&trace, start, end, NULL, NULL, 0, (CONTENTS_WATER | CONTENTS_SLIME | CONTENTS_LAVA));

	if (trace.fraction == 1.0) {
		return;
	}
	// create a mark polygon
	VectorCopy(trace.endpos, verts[0].xyz);
	verts[0].xyz[0] -= 32;
	verts[0].xyz[1] -= 32;
	verts[0].st[0] = 0;
	verts[0].st[1] = 0;
	verts[0].modulate[0] = 255;
	verts[0].modulate[1] = 255;
	verts[0].modulate[2] = 255;
	verts[0].modulate[3] = 255;

	VectorCopy(trace.endpos, verts[1].xyz);
	verts[1].xyz[0] -= 32;
	verts[1].xyz[1] += 32;
	verts[1].st[0] = 0;
	verts[1].st[1] = 1;
	verts[1].modulate[0] = 255;
	verts[1].modulate[1] = 255;
	verts[1].modulate[2] = 255;
	verts[1].modulate[3] = 255;

	VectorCopy(trace.endpos, verts[2].xyz);
	verts[2].xyz[0] += 32;
	verts[2].xyz[1] += 32;
	verts[2].st[0] = 1;
	verts[2].st[1] = 1;
	verts[2].modulate[0] = 255;
	verts[2].modulate[1] = 255;
	verts[2].modulate[2] = 255;
	verts[2].modulate[3] = 255;

	VectorCopy(trace.endpos, verts[3].xyz);
	verts[3].xyz[0] += 32;
	verts[3].xyz[1] -= 32;
	verts[3].st[0] = 1;
	verts[3].st[1] = 0;
	verts[3].modulate[0] = 255;
	verts[3].modulate[1] = 255;
	verts[3].modulate[2] = 255;
	verts[3].modulate[3] = 255;

	trap_R_AddPolyToScene(cgs.media.wakeMarkShader, 4, verts);
}

/*
===============
CG_AddRefEntityWithPowerups

Adds a piece with modifications or duplications for powerups
Also called by CG_Missile for quad rockets, but nobody can tell...
===============
*/
void CG_AddRefEntityWithPowerups(refEntity_t * ent, entityState_t * state, int team)
{

	/*
	   if ( state->eFlags & EF_KAMIKAZE ) {
	   if (team == TEAM_BLUE)
	   ent->customShader = cgs.media.blueKamikazeShader;
	   else
	   ent->customShader = cgs.media.redKamikazeShader;
	   trap_R_AddRefEntityToScene( ent );
	   }
	   else { */
	trap_R_AddRefEntityToScene(ent);
	//}

	//Elder: IR Vision -- only on players that are alive
	if (state->eType == ET_PLAYER) {
		if ((cg.snap->ps.stats[STAT_HOLDABLE_ITEM] & (1 << HI_BANDOLIER)) &&
			cg.rq3_irvision && !(state->eFlags & EF_DEAD)) {

			// NiceAss: On your team
			if (cgs.gametype >= GT_TEAM && cg.snap->ps.persistant[PERS_TEAM] == cgs.clientinfo[state->clientNum].team )
				ent->customShader = cgs.media.irPlayerShaderFriendly;
			// Not on your team
			else
				ent->customShader = cgs.media.irPlayerShader;

			trap_R_AddRefEntityToScene(ent);
		}
	}
}

/*
=================
CG_LightVerts
=================
*/
int CG_LightVerts(vec3_t normal, int numVerts, polyVert_t * verts)
{
	int i, j;
	float incoming;
	vec3_t ambientLight;
	vec3_t lightDir;
	vec3_t directedLight;

	trap_R_LightForPoint(verts[0].xyz, ambientLight, directedLight, lightDir);

	for (i = 0; i < numVerts; i++) {
		incoming = DotProduct(normal, lightDir);
		if (incoming <= 0) {
			verts[i].modulate[0] = ambientLight[0];
			verts[i].modulate[1] = ambientLight[1];
			verts[i].modulate[2] = ambientLight[2];
			verts[i].modulate[3] = 255;
			continue;
		}
		j = (ambientLight[0] + incoming * directedLight[0]);
		if (j > 255) {
			j = 255;
		}
		verts[i].modulate[0] = j;

		j = (ambientLight[1] + incoming * directedLight[1]);
		if (j > 255) {
			j = 255;
		}
		verts[i].modulate[1] = j;

		j = (ambientLight[2] + incoming * directedLight[2]);
		if (j > 255) {
			j = 255;
		}
		verts[i].modulate[2] = j;

		verts[i].modulate[3] = 255;
	}
	return qtrue;
}

//*********** NiceAss Start ************
static vec3_t playerMins = { -15, -15, -24 };
static vec3_t playerMaxs = { 15, 15, 32 };

qboolean CG_CheckPlayerVisible(vec3_t start, centity_t *cent) {
	int i;
	vec3_t	ends[9];
	trace_t	trace;
//	vec3_t forward, up, right;

	for (i = 0; i < 9; i++)
		VectorCopy(cent->lerpOrigin, ends[i]);

	ends[1][0] += playerMins[0];
	ends[2][0] += playerMins[0];
	ends[3][0] += playerMins[0];
	ends[4][0] += playerMins[0];
	ends[1][1] += playerMaxs[1];
	ends[2][1] += playerMaxs[1];
	ends[3][1] += playerMins[1];
	ends[4][1] += playerMins[1];
	ends[1][2] += playerMaxs[2];
	ends[2][2] += playerMins[2];
	ends[3][2] += playerMaxs[2];
	ends[4][2] += playerMins[2];

	ends[5][0] += playerMaxs[0];
	ends[6][0] += playerMaxs[0];
	ends[7][0] += playerMaxs[0];
	ends[8][0] += playerMaxs[0];
	ends[5][1] += playerMaxs[1];
	ends[6][1] += playerMaxs[1];
	ends[7][1] += playerMins[1];
	ends[8][1] += playerMins[1];
	ends[5][2] += playerMaxs[2];
	ends[6][2] += playerMins[2];
	ends[7][2] += playerMaxs[2];
	ends[8][2] += playerMins[2];

	//cg.refdefViewAngles
	//AngleVectors(cg.refdefViewAngles, forward, right, up);
	//VectorMA(start, 8192, forward, ends[0]);

	for (i = 0; i < 9; i++) {
		CG_Trace(&trace, start, NULL, NULL, ends[i], -1, CONTENTS_SOLID);
		CG_Printf("surface-- nodraw: %d  glass: %d  ", trace.surfaceFlags & SURF_NODRAW, trace.surfaceFlags & SURF_GLASS);
		CG_Printf("contents-- trans: %d  detail: %d\n", trace.contents & CONTENTS_TRANSLUCENT, trace.contents & CONTENTS_DETAIL);
		/*
		if ( trace.fraction == 1 || (trace.contents & ( CONTENTS_TRANSLUCENT | CONTENTS_DETAIL )) || (trace.surfaceFlags & ( SURF_NODRAW | SURF_GLASS )) )
			// Terrain has all 3 of these set. Assume it's terrain if all 3 are this way
			if ( !(trace.surfaceFlags & SURF_NOLIGHTMAP) &&
				 !(trace.surfaceFlags & SURF_NOMARKS) &&
				 !(trace.surfaceFlags & SURF_NODRAW) )
				return qtrue;
		*/
	}

	return qfalse;
}

/*
===============
CG_Player
===============
*/
void CG_Player(centity_t * cent)
{
	clientInfo_t *ci;
	refEntity_t legs;
	refEntity_t torso;
	refEntity_t head;
	int clientNum;
	int renderfx;
	qboolean shadow;
	float shadowPlane;

	// the client number is stored in clientNum.  It can't be derived
	// from the entity number, because a single client may have
	// multiple corpses on the level using the same clientinfo
	clientNum = cent->currentState.clientNum;
	if (clientNum < 0 || clientNum >= MAX_CLIENTS) {
		CG_Error("Bad clientNum on player entity");
	}
	ci = &cgs.clientinfo[clientNum];

	// it is possible to see corpses from disconnected players that may
	// not have valid clientinfo
	if (!ci->infoValid) {
		return;
	}
	// get the player model information
	renderfx = 0;
	if (cent->currentState.number == cg.snap->ps.clientNum) {
		if (!cg.renderingThirdPerson) {
			renderfx = RF_THIRD_PERSON;	// only draw in mirrors
		} else {
			if (cg_cameraMode.integer) {
				return;
			}
		}
	}

	// NiceAss: Render players through walls (for testing): renderfx |= RF_DEPTHHACK;
	// NiceAss: Check for visibility here
	// NiceAss: Disabled for now.
	/*
	if (cent->currentState.number != cg.snap->ps.clientNum && !CG_CheckPlayerVisible(cg.refdef.vieworg, cent) ) {
		int num;
		centity_t *cent;

		// Look to see if any portals are around. If so, ignore that the player isn't visible.
		// This could be done better and more secure.
		for (num = 0; num < cg.snap->numEntities; num++) {
			cent = &cg_entities[cg.snap->entities[num].number];
			if (cent->currentState.eType == ET_PORTAL)
				break;
		}

		// No portals
		if (num == cg.snap->numEntities)
			return;
	}
	*/

	memset(&legs, 0, sizeof(legs));
	memset(&torso, 0, sizeof(torso));
	memset(&head, 0, sizeof(head));

	// get the rotation information
	CG_PlayerAngles(cent, legs.axis, torso.axis, head.axis);

	// get the animation state (after rotation, to allow feet shuffle)
	CG_PlayerAnimation(cent, &legs.oldframe, &legs.frame, &legs.backlerp,
			   &torso.oldframe, &torso.frame, &torso.backlerp);

	// add the talk baloon or disconnect icon
	CG_PlayerSprites(cent);

	// add the shadow
	shadow = CG_PlayerShadow(cent, &shadowPlane);

	// add a water splash if partially in and out of water
	CG_PlayerSplash(cent);

	if (cg_shadows.integer == 3 && shadow) {
		renderfx |= RF_SHADOW_PLANE;
	}
	renderfx |= RF_LIGHTING_ORIGIN;	// use the same origin for all
	//
	// add the legs
	//
	legs.hModel = ci->legsModel;
	legs.customSkin = ci->legsSkin;

	VectorCopy(cent->lerpOrigin, legs.origin);

	VectorCopy(cent->lerpOrigin, legs.lightingOrigin);
	legs.shadowPlane = shadowPlane;
	legs.renderfx = renderfx;
	VectorCopy(legs.origin, legs.oldorigin);	// don't positionally lerp at all

	CG_AddRefEntityWithPowerups(&legs, &cent->currentState, ci->team);

	// if the model failed, allow the default nullmodel to be displayed
	if (!legs.hModel) {
		return;
	}
	//
	// add the torso
	//
	torso.hModel = ci->torsoModel;
	if (!torso.hModel) {
		return;
	}

	torso.customSkin = ci->torsoSkin;

	VectorCopy(cent->lerpOrigin, torso.lightingOrigin);

	CG_PositionRotatedEntityOnTag(&torso, &legs, ci->legsModel, "tag_torso");

	torso.shadowPlane = shadowPlane;
	torso.renderfx = renderfx;

	CG_AddRefEntityWithPowerups(&torso, &cent->currentState, ci->team);
	//
	// add the head
	//
	head.hModel = ci->headModel;
	if (!head.hModel) {
		return;
	}
	head.customSkin = ci->headSkin;

	VectorCopy(cent->lerpOrigin, head.lightingOrigin);

	CG_PositionRotatedEntityOnTag(&head, &torso, ci->torsoModel, "tag_head");
	//Makro - save the head pos and orientation if this is the curremt client
	if (cent->currentState.number == cg.clientNum)
	{
		memcpy(cg.headAxis, head.axis, sizeof(head.axis));
		memcpy(cg.headPos, head.origin, sizeof(head.origin));
	}

	head.shadowPlane = shadowPlane;
	head.renderfx = renderfx;

	// NiceAss will have fun here: Big head mode!
	//VectorScale( head.axis[0], 4.0f, head.axis[0] );
	//VectorScale( head.axis[1], 4.0f, head.axis[1] );
	//VectorScale( head.axis[2], 4.0f, head.axis[2] );
	// End of fun

	// NiceAss: Headless player.
	if (!(cent->currentState.eFlags & EF_HEADLESS))
		CG_AddRefEntityWithPowerups(&head, &cent->currentState, ci->team);

	// NiceAss: Outside the MISSIONPACK
	CG_BreathPuffs(cent, &head);

	// JBravo: ditto
	CG_DustTrail(cent);

	//
	// add the gun / barrel / flash
	//
	CG_AddPlayerWeapon(&torso, NULL, cent, ci->team);

	// add powerups floating behind the player
	CG_PlayerPowerups(cent, &torso);

	// Elder: HC Smoke
	if (cent->currentState.eFlags & EF_HANDCANNON_SMOKED) {
		CG_HCSmokeTrail(cent);
	}
// JBravo: unlagged
	CG_AddBoundingBox(cent);
}

//=====================================================================

/*
===============
CG_ResetPlayerEntity

A player just came into view or teleported, so reset all animation info
===============
*/
void CG_ResetPlayerEntity(centity_t * cent)
{
	cent->errorTime = -99999;	// guarantee no error decay added
	cent->extrapolated = qfalse;

	CG_ClearLerpFrame(&cgs.clientinfo[cent->currentState.clientNum], &cent->pe.legs, cent->currentState.legsAnim);
	CG_ClearLerpFrame(&cgs.clientinfo[cent->currentState.clientNum], &cent->pe.torso, cent->currentState.torsoAnim);

	CG_EvaluateTrajectory(&cent->currentState.pos, cg.time, cent->lerpOrigin);
	CG_EvaluateTrajectory(&cent->currentState.apos, cg.time, cent->lerpAngles);

	VectorCopy(cent->lerpOrigin, cent->rawOrigin);
	VectorCopy(cent->lerpAngles, cent->rawAngles);

	memset(&cent->pe.legs, 0, sizeof(cent->pe.legs));
	cent->pe.legs.yawAngle = cent->rawAngles[YAW];
	cent->pe.legs.yawing = qfalse;
	cent->pe.legs.pitchAngle = 0;
	cent->pe.legs.pitching = qfalse;

	memset(&cent->pe.torso, 0, sizeof(cent->pe.legs));
	cent->pe.torso.yawAngle = cent->rawAngles[YAW];
	cent->pe.torso.yawing = qfalse;
	cent->pe.torso.pitchAngle = cent->rawAngles[PITCH];
	cent->pe.torso.pitching = qfalse;

	if (cg_debugPosition.integer) {
		CG_Printf("%i ResetPlayerEntity yaw=%i\n", cent->currentState.number, cent->pe.torso.yawAngle);
	}
}
