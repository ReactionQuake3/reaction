//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.135  2004/01/26 21:26:08  makro
// no message
//
// Revision 1.134  2003/04/26 22:33:06  jbravo
// Wratted all calls to G_FreeEnt() to avoid crashing and provide debugging
//
// Revision 1.133  2003/04/23 17:49:11  slicer
// Fixed Crash Bug caused by merging 1.32 source code
//
// Revision 1.132  2003/04/19 17:41:26  jbravo
// Applied changes that where in 1.29h -> 1.32b gamecode.
//
// Revision 1.131  2003/04/19 15:27:30  jbravo
// Backing out of most of unlagged.  Only optimized prediction and smooth clients
// remains.
//
// Revision 1.130  2003/04/09 02:00:43  jbravo
// Fixed team none in DM and some final cleanups for the 3.0 release
//
// Revision 1.129  2003/04/02 22:23:51  jbravo
// More replacements tweaks. Added zcam_stfu
//
// Revision 1.128  2003/03/28 10:36:02  jbravo
// Tweaking the replacement system a bit.  Reactionmale now the default model
//
// Revision 1.127  2003/03/22 20:29:26  jbravo
// wrapping linkent and unlinkent calls
//
// Revision 1.126  2003/03/10 07:07:58  jbravo
// Small unlagged fixes and voting delay added.
//
// Revision 1.125  2003/03/09 21:30:38  jbravo
// Adding unlagged.   Still needs work.
//
// Revision 1.124  2003/02/27 03:58:35  jbravo
// Fixed the FF system after adding TDM broke it. Added color to error messages
//
// Revision 1.123  2002/11/17 20:14:15  jbravo
// Itembanning added
//
// Revision 1.122  2002/11/13 00:50:38  jbravo
// Fixed item dropping, specmode selection on death and helmet probs.
//
// Revision 1.121  2002/10/29 01:34:52  jbravo
// Added g_RQ3_tdmMode (0 = TP style, 1 = DM style) including UI support.
//
// Revision 1.120  2002/10/26 22:03:43  jbravo
// Made TeamDM work RQ3 style.
//
// Revision 1.119  2002/10/26 18:29:17  jbravo
// Added allweap and allitem funtionality.
//
// Revision 1.118  2002/10/21 21:00:39  slicer
// New MM features and bug fixes
//
// Revision 1.117  2002/09/29 16:06:44  jbravo
// Work done at the HPWorld expo
//
// Revision 1.116  2002/09/24 05:06:16  blaze
// fixed spectating so ref\'s can now use all the chasecam modes.
//
// Revision 1.115  2002/09/02 03:30:53  jbravo
// Hopefully fixed the skinhacking
//
// Revision 1.114  2002/08/30 01:09:06  jbravo
// Semi fixed the bodies thing in CTB
//
// Revision 1.113  2002/08/28 23:10:06  jbravo
// Added cg_RQ3_SuicideLikeARealMan, timestamping to server logs and
// fixed stats for non-TP modes.
//
// Revision 1.112  2002/08/23 14:25:05  slicer
// Added a new Referee System with multiple ref support
//
// Revision 1.111  2002/08/21 07:00:07  jbravo
// Added CTB respawn queue and fixed game <-> cgame synch problem in CTB
//
// Revision 1.110  2002/08/07 03:35:57  jbravo
// Added dynamic radio and stopped all radio usage during lca
//
// Revision 1.109  2002/07/26 22:28:38  jbravo
// Fixed the server about menu, made the UI handle illegal models and skins
// better.
//
// Revision 1.108  2002/07/26 06:21:43  jbravo
// Fixed the MM settings stuff so it works on remote servers also.
// Removed the MM_NAMES_COLOR since it broke on nicks with color in them.
//
// Revision 1.107  2002/07/16 04:09:14  niceass
// stupid team scoreboard fix
//
// Revision 1.106  2002/07/11 04:32:24  niceass
// misc CTB changes for joining a team or becoming a spectator on map load. Also team check before weapon equip
//
// Revision 1.105  2002/07/09 05:42:18  niceass
// small change to userinfo
//
// Revision 1.104  2002/07/02 03:41:59  jbravo
// Fixed a 2 frags pr kill bug, the use cmd now cancels weaponchanges in progress
// and fixed the captain status lingering on people after switching from MM
//
// Revision 1.103  2002/06/30 17:33:01  jbravo
// New radio sounds and the 0wned sound was added.
//
// Revision 1.102  2002/06/26 15:58:13  makro
// Fixed a crash bug in the spawning code
// (happenned on maps with one spawn point)
//
// Revision 1.101  2002/06/24 05:51:51  jbravo
// CTF mode is now semi working
//
// Revision 1.100  2002/06/23 23:32:29  jbravo
// Fixed logging of clients IP addresses.
//
// Revision 1.99  2002/06/21 11:55:32  freud
// Changed spawning system to move spawns up 9 pixels (q3 style)
//
// Revision 1.98  2002/06/20 22:32:43  jbravo
// Added last damaged player and fixed a test2 model problem (atrimum my ass :)
// Changed g_RQ3_printOwnObits to g_RQ3_showOwnKills and it also controls $K
//
// Revision 1.97  2002/06/19 18:18:09  jbravo
// Small cleanups for compiler warnings
//
// Revision 1.96  2002/06/19 18:13:57  jbravo
// New TNG spawning system :)
//
// Revision 1.95  2002/06/17 00:23:59  slicer
// Lasersight problem fixed
//
// Revision 1.94  2002/06/16 20:06:14  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.93  2002/06/16 17:38:00  jbravo
// Removed the MISSIONPACK ifdefs and missionpack only code.
//
// Revision 1.92  2002/06/13 20:59:35  slicer
// Setting ( for real ) gender on DM
//
// Revision 1.91  2002/06/12 22:32:24  slicer
// Even better way to improve the Cvar Anti-Cheat System
//
// Revision 1.90  2002/06/12 15:29:53  slicer
// Improved and fixed the Anti-Cheat System
//
// Revision 1.89  2002/06/12 03:37:38  blaze
// some fixes for the add bot code
//
// Revision 1.88  2002/06/11 23:37:27  blaze
// moved the cheat cvars to be sent at a different time, should work better
//
// Revision 1.87  2002/06/11 01:43:08  blaze
// g_rq3_cvarfile allows you to change which file holds the restricted cvars
//
// Revision 1.86  2002/06/07 19:07:08  slicer
// removed cvars for teamXready, replaced by level.teamXready
//
// Revision 1.85  2002/06/05 22:09:21  niceass
// bot fix. NOT MY FAULT
//
// Revision 1.84  2002/06/04 08:25:44  niceass
// cgame team fix. (when you change your name, etc)
//
// Revision 1.83  2002/06/04 07:12:32  niceass
// spectators spawn where you are rather than at a spawnpoint
//
// Revision 1.82  2002/05/31 17:32:11  jbravo
// HC gibs almost working :)
//
// Revision 1.81  2002/05/28 04:46:12  niceass
// headless fix
//
// Revision 1.80  2002/05/28 01:17:01  jbravo
// More gib fixes.  g_RQ3_gib added
//
// Revision 1.79  2002/05/27 06:50:01  niceass
// further spawning and removed kamakazi
//
// Revision 1.78  2002/05/25 16:31:18  blaze
// moved breakable stuff over to config strings
//
// Revision 1.77  2002/05/21 23:16:30  blaze
// Only send cheat vars on client connect instead of every spawn
//
// Revision 1.76  2002/05/20 04:59:33  jbravo
// Lots of small fixes.
//
// Revision 1.75  2002/05/19 21:27:28  blaze
// added force and buoyancy to breakables
//
// Revision 1.74  2002/05/13 07:29:14  jbravo
// Fixed server chrasing on incorrect models in TP and also added default skins
//
// Revision 1.73  2002/05/10 13:21:53  makro
// Mainly bot stuff. Also fixed a couple of crash bugs
//
// Revision 1.72  2002/05/05 15:51:16  slicer
// Captain and subs get saved on map_restarts ( moved to "sess" )
//
// Revision 1.71  2002/05/03 18:09:20  makro
// Bot stuff. Jump kicks
//
// Revision 1.70  2002/04/30 11:54:37  makro
// Bots rule ! Also, added clips to give all. Maybe some other things
//
// Revision 1.69  2002/04/30 01:23:05  jbravo
// Changed the server logging to be more like a normal AQ server.  Cleaned
// all colors from the logs.
//
// Revision 1.68  2002/04/23 00:21:44  jbravo
// Cleanups of the new model code.  Removed the spectator bar for zcam modes.
//
// Revision 1.67  2002/04/22 02:27:57  jbravo
// Dynamic model recognition
//
// Revision 1.66  2002/04/18 16:13:23  jbravo
// Scoreboard now shows green for live players and white for dead.
// Time should not get reset on deaths any more.
//
// Revision 1.65  2002/04/09 14:30:10  jbravo
// Made cg_thirdPerson a CVAR_ROM, Made bots understand team aliases (1 and 2) and
// made TP spawns more random.
//
// Revision 1.64  2002/04/07 17:50:54  makro
// Abbey
//
// Revision 1.63  2002/04/07 12:49:10  slicer
// Added 'teamname' command for MM, and tweaked the cvar system.
//
// Revision 1.62  2002/04/07 03:22:48  jbravo
// Tweaks and crashbug fixes
//
// Revision 1.61  2002/04/05 18:53:26  jbravo
// Warning fixes
//
// Revision 1.60  2002/04/03 03:13:16  blaze
// NEW BREAKABLE CODE - will break all old breakables(wont appear in maps)
//
// Revision 1.59  2002/04/02 20:23:12  jbravo
// Bots dont get to use any specmode other than FREE and the recive radio cmds
// as text and not sounds.
//
// Revision 1.58  2002/04/01 22:23:14  slicer
// Added "weapon" command buffering | Solved Gren Mode Bug
//
// Revision 1.57  2002/03/31 03:31:24  jbravo
// Compiler warning cleanups
//
// Revision 1.56  2002/03/30 21:51:42  jbravo
// Removed all those ifdefs for zcam.
//
// Revision 1.55  2002/03/30 02:29:43  jbravo
// Lots of spectator code updates. Removed debugshit, added some color.
//
// Revision 1.54  2002/03/26 11:32:04  jbravo
// Remember specstate between rounds.
//
// Revision 1.53  2002/03/26 10:32:52  jbravo
// Bye bye LCA lag
//
// Revision 1.52  2002/03/17 23:43:43  slicer
// Made Bots visible again at DM
//
// Revision 1.51  2002/03/17 02:03:48  jbravo
// Fixed a bug where a players laser would stay in the map after he disconnects
//
// Revision 1.50  2002/03/17 01:44:39  jbravo
// Fixed the "xxx died" fraglines, did some code cleanups andalmost fixed
// DM.  Only DM problem I can see is that bots are invisible.
//
// Revision 1.49  2002/03/14 23:54:12  jbravo
// Added a variable system from AQ. Works the same except it uses $ for %
//
// Revision 1.48  2002/03/14 02:24:39  jbravo
// Adding radio :)
//
// Revision 1.47  2002/03/11 18:02:33  slicer
// Fixed team changes and scoreboard bugs
//
// Revision 1.46  2002/03/07 01:38:36  assimon
// Changed Ref System. New cvar added - g_RQ3_RefID. Now referee is peserved even on map changes or map_restarts.
//
// Revision 1.45  2002/03/03 13:49:28  jbravo
// Initializing weapon modes on connect.
//
// Revision 1.44  2002/03/03 03:11:37  jbravo
// Use propper weapon anims on TP spawns
//
// Revision 1.43  2002/03/02 15:39:34  jbravo
// Fixed team auto (PickTeam) up for TP
//
// Revision 1.42  2002/03/02 14:54:24  jbravo
// Added the skin and model names to the name of the player thats being
// followed, as in AQ
//
// Revision 1.41  2002/03/01 18:21:26  jbravo
// Cleanups and removal of g_RQ3_sniperup
//
// Revision 1.40  2002/02/27 01:54:29  jbravo
// More spectatorfixes and finally stopped all fallingdamage anims and
// sounds during LCA.
//
// Revision 1.39  2002/02/26 21:59:10  jbravo
// Fixed death on switching teams while dead
//
// Revision 1.38  2002/02/26 02:58:47  jbravo
// Fixing the spectator_free mode not being predicted in the client.
//
// Revision 1.37  2002/02/10 21:21:22  slicer
// Saving persistant and other data on some events..
//
// Revision 1.36  2002/02/10 16:26:55  jbravo
// Attempting to intergrate zcam better into rq3 and a fix for lights.wav
//
// Revision 1.35  2002/02/07 23:01:07  slicer
// Small fix..
//
// Revision 1.34  2002/02/06 12:06:48  slicer
// TP Scores bug fix
//
// Revision 1.33  2002/02/06 03:10:43  jbravo
// Fix the instant spectate on death and an attempt to fix the scores
//
// Revision 1.32  2002/02/05 23:41:27  slicer
// More on matchmode..
//
// Revision 1.31  2002/02/04 00:10:49  slicer
// Matchmode: Teams Ready/Not Ready goes by cvar MM_team1/2
//
// Revision 1.28  2002/02/01 01:00:36  slicer
// Adding Matchmode: just a few basics and files...
//
// Revision 1.27  2002/01/27 13:33:28  jbravo
// Teamplay antistick system.
//
// Revision 1.26  2002/01/23 15:26:31  niceass
// body sinkage removed
// weapon reset fixed
//
// Revision 1.25  2002/01/11 20:20:58  jbravo
// Adding TP to main branch
//
// Revision 1.24  2002/01/11 19:48:30  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.23  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
#include "g_local.h"
#include "zcam.h"

// JBravo: fixme. Hack to use SelectInitialSpawnPoint() in ClientSpawn.
gentity_t *SelectInitialSpawnPoint(vec3_t origin, vec3_t angles);

//Blaze: for the breakables
breakable_t rq3_breakables[RQ3_MAX_BREAKABLES];

#define RQ3_NONAMEPLAYER		"Nameless"

// JBravo: for models
extern legitmodel_t legitmodels[MAXMODELS];
int RQ3_Validatemodel(char *model);

extern char *settings[];
extern char *settings2[];

// g_client.c -- client functions that don't happen every frame

static vec3_t playerMins = { -15, -15, -24 };
static vec3_t playerMaxs = { 15, 15, 32 };

/*QUAKED info_player_deathmatch (1 0 1) (-16 -16 -24) (16 16 32) initial
potential spawning position for deathmatch games.
The first time a player enters the game, they will be at an 'initial' spot.
Targets will be fired when someone spawns in on them.
"nobots" will prevent bots from using this spot.
"nohumans" will prevent non-bots from using this spot.
*/
void SP_info_player_deathmatch(gentity_t * ent)
{
	int i;

	G_SpawnInt("nobots", "0", &i);
	if (i) {
		ent->flags |= FL_NO_BOTS;
	}
	G_SpawnInt("nohumans", "0", &i);
	if (i) {
		ent->flags |= FL_NO_HUMANS;
	}
}

/*QUAKED info_player_start (1 0 0) (-16 -16 -24) (16 16 32)
equivalent to info_player_deathmatch
*/
void SP_info_player_start(gentity_t * ent)
{
	ent->classname = "info_player_deathmatch";
	SP_info_player_deathmatch(ent);
}

/*QUAKED info_player_intermission (1 0 1) (-16 -16 -24) (16 16 32)
The intermission will be viewed from this point.  Target an info_notnull for the view direction.
*/
void SP_info_player_intermission(gentity_t * ent)
{

}

/*
=======================================================================

  SelectSpawnPoint

=======================================================================
*/

/*
================
SpotWouldTelefrag

================
*/
qboolean SpotWouldTelefrag(gentity_t * spot)
{
	int i, num;
	int touch[MAX_GENTITIES];
	gentity_t *hit;
	vec3_t mins, maxs;

	VectorAdd(spot->s.origin, playerMins, mins);
	VectorAdd(spot->s.origin, playerMaxs, maxs);
	num = trap_EntitiesInBox(mins, maxs, touch, MAX_GENTITIES);

	for (i = 0; i < num; i++) {
		//Blaze: Print out some Debug info
		if (&g_entities[touch[i]] == NULL) G_Printf("Ln 0376\n");
		hit = &g_entities[touch[i]];
		if (hit->client) {
			return qtrue;
		}

	}
	return qfalse;
}

/*
================
SelectNearestDeathmatchSpawnPoint

Find the spot that we DON'T want to use
================
*/
// Moved to g_local.h
//#define       MAX_SPAWN_POINTS        128
gentity_t *SelectNearestDeathmatchSpawnPoint(vec3_t from)
{
	gentity_t *spot;
	vec3_t delta;
	float dist, nearestDist;
	gentity_t *nearestSpot;

	nearestDist = 999999;
	nearestSpot = NULL;
	spot = NULL;

	while ((spot = G_Find(spot, FOFS(classname), "info_player_deathmatch")) != NULL) {

		VectorSubtract(spot->s.origin, from, delta);
		dist = VectorLength(delta);
		if (dist < nearestDist) {
			nearestDist = dist;
			nearestSpot = spot;
		}
	}

	return nearestSpot;
}

/*
================
SelectRandomDeathmatchSpawnPoint

go to a random point that doesn't telefrag
================
*/
// Moved to g_local.h
//#define       MAX_SPAWN_POINTS        128
gentity_t *SelectRandomDeathmatchSpawnPoint(void)
{
	gentity_t *spot;
	int count;
	int selection;
	gentity_t *spots[MAX_SPAWN_POINTS];

	count = 0;
	spot = NULL;

	while ((spot = G_Find(spot, FOFS(classname), "info_player_deathmatch")) != NULL) {
		if (SpotWouldTelefrag(spot)) {
			continue;
		}
		spots[count] = spot;
		count++;
	}

	if (!count) {		// no spots that won't telefrag
		return G_Find(NULL, FOFS(classname), "info_player_deathmatch");
	}

	selection = rand() % count;
	return spots[selection];
}

/*
===========
SelectRandomFurthestSpawnPoint

Chooses a player start, deathmatch start, etc
============
*/
gentity_t *SelectRandomFurthestSpawnPoint(vec3_t avoidPoint, vec3_t origin, vec3_t angles)
{
	gentity_t *spot;
	vec3_t delta;
	float dist;
	float list_dist[64];
	gentity_t *list_spot[64];
	int numSpots, rnd, i, j;

	numSpots = 0;
	spot = NULL;

	while ((spot = G_Find(spot, FOFS(classname), "info_player_deathmatch")) != NULL) {
		if (SpotWouldTelefrag(spot)) {
			continue;
		}
		VectorSubtract(spot->s.origin, avoidPoint, delta);
		dist = VectorLength(delta);
		for (i = 0; i < numSpots; i++) {
			if (dist > list_dist[i]) {
				if (numSpots >= 64)
					numSpots = 64 - 1;
				for (j = numSpots; j > i; j--) {
					list_dist[j] = list_dist[j - 1];
					list_spot[j] = list_spot[j - 1];
				}
				list_dist[i] = dist;
				list_spot[i] = spot;
				numSpots++;
				if (numSpots > 64)
					numSpots = 64;
				break;
			}
		}
		if (i >= numSpots && numSpots < 64) {
			list_dist[numSpots] = dist;
			list_spot[numSpots] = spot;
			numSpots++;
		}
	}

	//Makro - on a map with one spawn point, if one player has to respawn and someone is
	//already near the spawnpoint, Q3 crashes; added check
	if (numSpots != 0) {
		// select a random spot from the spawn points furthest away
		rnd = random() * (numSpots / 3);	// NiceAss: divided by 2 changed to 3 to cut down on close spawns       

		VectorCopy(list_spot[rnd]->s.origin, origin);
		origin[2] += 9;
		VectorCopy(list_spot[rnd]->s.angles, angles);

		return list_spot[rnd];
	} else {
		//Makro - added; note - plenty of room for improvement here, I just wanted to get rid of the crash bug
		spot = G_Find(NULL, FOFS(classname), "info_player_deathmatch");
		if (!spot) {
			G_Error("Couldn't find a spawn point");
		}
		VectorCopy(spot->s.origin, origin);
		origin[2] += 9;
		VectorCopy(spot->s.angles, angles);

		return spot;
	}
}

/*
===========
SelectSpawnPoint

Chooses a player start, deathmatch start, etc
============
*/
gentity_t *SelectSpawnPoint(vec3_t avoidPoint, vec3_t origin, vec3_t angles)
{
	return SelectRandomFurthestSpawnPoint(avoidPoint, origin, angles);
}

/*
===========
SelectInitialSpawnPoint

Try to find a spawn point marked 'initial', otherwise
use normal spawn selection.
============
*/
gentity_t *SelectInitialSpawnPoint(vec3_t origin, vec3_t angles)
{
	gentity_t *spot;

	spot = NULL;
	while ((spot = G_Find(spot, FOFS(classname), "info_player_deathmatch")) != NULL) {
		if (spot->spawnflags & 1) {
			break;
		}
	}

	if (!spot || SpotWouldTelefrag(spot)) {
		return SelectSpawnPoint(vec3_origin, origin, angles);
	}

	VectorCopy(spot->s.origin, origin);
	origin[2] += 9;
	VectorCopy(spot->s.angles, angles);

	return spot;
}

/*
===========
SelectSpectatorSpawnPoint

============
*/
gentity_t *SelectSpectatorSpawnPoint(vec3_t origin, vec3_t angles)
{
	FindIntermissionPoint();

	VectorCopy(level.intermission_origin, origin);
	VectorCopy(level.intermission_angle, angles);

	return NULL;
}

/*
=======================================================================

BODYQUE

=======================================================================
*/

/*
===============
InitBodyQue
===============
*/
void InitBodyQue(void)
{
	int i;
	gentity_t *ent;

	level.bodyQueIndex = 0;
	for (i = 0; i < BODY_QUEUE_SIZE; i++) {
		ent = G_Spawn();
		ent->classname = "bodyque";
		ent->neverFree = qtrue;
		level.bodyQue[i] = ent;
	}
}

/*
===============
ClearBodyQue  -  By NiceAss
===============
*/
void ClearBodyQue(void)
{
	int i;
	gentity_t *ent;

	level.bodyQueIndex = 0;
	for (i = 0; i < BODY_QUEUE_SIZE; i++) {
		ent = level.bodyQue[i];
		trap_UnlinkEntity(ent);
		ent->physicsObject = qfalse;
	}
}

/*
=============
BodySink

After sitting around for five seconds, fall into the ground and disappear
=============
*/
void BodySink(gentity_t * ent)
{
	// NiceAss: Prevent body sink in TP. Bodies will be removed at before LCA
	if (g_gametype.integer == GT_TEAMPLAY)
		return;

	if (level.time - ent->timestamp > 6500) {
		// the body ques are never actually freed, they are just unlinked
		trap_UnlinkEntity(ent);
		ent->physicsObject = qfalse;
		return;
	}
	ent->nextthink = level.time + 100;
	ent->s.pos.trBase[2] -= 1;
}

/*
=============
CopyToBodyQue

A player is respawning, so make an entity that looks
just like the existing corpse to leave behind.
=============
*/
void CopyToBodyQue(gentity_t * ent)
{
	gentity_t *body;
	int contents;

	trap_UnlinkEntity(ent);

	// if client is in a nodrop area, don't leave the body
	contents = trap_PointContents(ent->s.origin, -1);
	if (contents & CONTENTS_NODROP) {
		return;
	}
	// grab a body que and cycle to the next one
	body = level.bodyQue[level.bodyQueIndex];
	level.bodyQueIndex = (level.bodyQueIndex + 1) % BODY_QUEUE_SIZE;

	trap_UnlinkEntity(body);

	body->s = ent->s;

	// clear EF_TALK, etc
	if (body->s.eFlags & EF_HEADLESS)
		body->s.eFlags = EF_DEAD | EF_HEADLESS;
	else
		body->s.eFlags = EF_DEAD;

	body->s.powerups = 0;	// clear powerups
	body->s.loopSound = 0;	// clear lava burning
	body->s.number = body - g_entities;
	body->timestamp = level.time;
	body->physicsObject = qtrue;
	body->physicsBounce = 0;	// don't bounce
	if (body->s.groundEntityNum == ENTITYNUM_NONE) {
		body->s.pos.trType = TR_GRAVITY;
		body->s.pos.trTime = level.time;
		VectorCopy(ent->client->ps.velocity, body->s.pos.trDelta);
	} else {
		body->s.pos.trType = TR_STATIONARY;
	}
	body->s.event = 0;

	// change the animation to the last-frame only, so the sequence
	// doesn't repeat anew for the body
	switch (body->s.legsAnim & ~ANIM_TOGGLEBIT) {
	case BOTH_DEATH1:
	case BOTH_DEAD1:
		body->s.torsoAnim = body->s.legsAnim = BOTH_DEAD1;
		break;
	case BOTH_DEATH2:
	case BOTH_DEAD2:
		body->s.torsoAnim = body->s.legsAnim = BOTH_DEAD2;
		break;
	case BOTH_DEATH3:
	case BOTH_DEAD3:
	default:
		body->s.torsoAnim = body->s.legsAnim = BOTH_DEAD3;
		break;
	}

	body->r.svFlags = ent->r.svFlags;
	VectorCopy(ent->r.mins, body->r.mins);
	VectorCopy(ent->r.maxs, body->r.maxs);
	VectorCopy(ent->r.absmin, body->r.absmin);
	VectorCopy(ent->r.absmax, body->r.absmax);

	body->clipmask = CONTENTS_SOLID | CONTENTS_PLAYERCLIP;
	body->r.contents = CONTENTS_CORPSE;
	body->r.ownerNum = ent->s.number;

	body->nextthink = level.time + 5000;

	// NiceAss: Prevent sinkage of the body in TP
	body->think = BodySink;

	body->die = body_die;

	// don't take more damage if already gibbed
	if (ent->health <= GIB_HEALTH) {
		body->takedamage = qfalse;
	} else {
		body->takedamage = qtrue;
	}

	VectorCopy(body->s.pos.trBase, body->r.currentOrigin);
	trap_LinkEntity(body);
}

//======================================================================

/*
==================
SetClientViewAngle

==================
*/
void SetClientViewAngle(gentity_t * ent, vec3_t angle)
{
	int i;

	// set the delta angle
	for (i = 0; i < 3; i++) {
		int cmdAngle;

		cmdAngle = ANGLE2SHORT(angle[i]);
		ent->client->ps.delta_angles[i] = cmdAngle - ent->client->pers.cmd.angles[i];
	}
	VectorCopy(angle, ent->s.angles);
	VectorCopy(ent->s.angles, ent->client->ps.viewangles);
}

/*
================
respawn
================
*/
void respawn(gentity_t * ent)
{
	CopyToBodyQue(ent);
	ClientSpawn(ent);
}

/*
================
TeamCount

Returns number of players on a team
================
*/
int TeamCount(int ignoreClientNum, int team)
{
	int i;
	int count = 0;

	for (i = 0; i < level.maxclients; i++) {
		if (i == ignoreClientNum) {
			continue;
		}
		if (level.clients[i].pers.connected == CON_DISCONNECTED) {
			continue;
		}
		if (level.clients[i].sess.sessionTeam == team) {
			count++;
		}
	}

	return count;
}

/*
================
TeamLeader

Returns the client number of the team leader
================
*/
int TeamLeader(int team)
{
	int i;

	for (i = 0; i < level.maxclients; i++) {
		if (level.clients[i].pers.connected == CON_DISCONNECTED) {
			continue;
		}
		if (level.clients[i].sess.sessionTeam == team) {
			if (level.clients[i].sess.teamLeader)
				return i;
		}
	}

	return -1;
}

/*
================
PickTeam

================
*/
team_t PickTeam(int ignoreClientNum)
{
	int counts[TEAM_NUM_TEAMS];

	if (g_gametype.integer >= GT_TEAM) {
		counts[TEAM_BLUE] = RQ3TeamCount(ignoreClientNum, TEAM_BLUE);
		counts[TEAM_RED] = RQ3TeamCount(ignoreClientNum, TEAM_RED);
	} else {
		counts[TEAM_BLUE] = TeamCount(ignoreClientNum, TEAM_BLUE);
		counts[TEAM_RED] = TeamCount(ignoreClientNum, TEAM_RED);
	}

	if (counts[TEAM_BLUE] > counts[TEAM_RED]) {
		return TEAM_RED;
	}
	if (counts[TEAM_RED] > counts[TEAM_BLUE]) {
		return TEAM_BLUE;
	}
	// equal team count, so join the team with the lowest score
	if (level.teamScores[TEAM_BLUE] > level.teamScores[TEAM_RED]) {
		return TEAM_RED;
	}
	return TEAM_BLUE;
}

/*
===========
ClientCleanName
============
*/
static void ClientCleanName(const char *in, char *out, int outSize)
{
	int outpos = 0, colorlessLen = 0, spaces = 0;

	// discard leading spaces
	for (; *in == ' '; in++);
	for (; *in && outpos < outSize - 1; in++) {
		out[outpos] = *in;

		if (*in == ' ') {
			// don't allow too many consecutive spaces
			if (spaces > 2)
				continue;
			spaces++;
		} else if (outpos > 0 && out[outpos - 1] == Q_COLOR_ESCAPE) {
			if (Q_IsColorString(&out[outpos - 1])) {
				colorlessLen--;
				if (ColorIndex(*in) == 0) {
					// Disallow color black in names to prevent players
					// from getting advantage playing in front of black backgrounds
					outpos--;
					continue;
				}
			} else {
				spaces = 0;
				colorlessLen++;
			}
		} else {
			spaces = 0;
			colorlessLen++;
		}
		outpos++;
	}

	out[outpos] = '\0';

	// don't allow empty names
	if( *out == '\0' || colorlessLen == 0)
		Q_strncpyz(out, RQ3_NONAMEPLAYER, outSize);
}

/*
===========
ClientUserInfoChanged

Called from ClientConnect when the player first connects and
directly by the server system when the player updates a userinfo variable.

The game can override any of the settings and call trap_SetUserinfo
if desired.
============
*/
void ClientUserinfoChanged(int clientNum)
{
	gentity_t *ent;
	gclient_t *client;
	int teamTask, teamLeader, health, gender;
	char *s, model[MAX_QPATH], headModel[MAX_QPATH], oldname[MAX_STRING_CHARS];
	char c1[MAX_INFO_STRING], c2[MAX_INFO_STRING], redTeam[MAX_INFO_STRING];
	char blueTeam[MAX_INFO_STRING], userinfo[MAX_INFO_STRING];
	char *skin2, model2[MAX_STRING_CHARS];

	ent = g_entities + clientNum;
	client = ent->client;

	trap_GetUserinfo(clientNum, userinfo, sizeof(userinfo));

	// check for malformed or illegal info strings
	if (!Info_Validate(userinfo)) {
		strcpy(userinfo, "\\name\\badinfo");
		// don't keep those clients and userinfo
		trap_DropClient(clientNum, "Invalid userinfo");
	}

	// check the item prediction
	s = Info_ValueForKey(userinfo, "cg_predictItems");
	if (!atoi(s)) {
		client->pers.predictItemPickup = qfalse;
	} else {
		client->pers.predictItemPickup = qtrue;
	}

	// JBravo: unlagged
	s = Info_ValueForKey(userinfo, "cg_delag");
	if (!atoi(s)) {
		client->pers.delag = 0; 
	} else { 
		client->pers.delag = atoi(s);
	}

	// set name
	Q_strncpyz(oldname, client->pers.netname, sizeof(oldname));
	s = Info_ValueForKey(userinfo, "name");
	ClientCleanName(s, client->pers.netname, sizeof(client->pers.netname));

	if (client->sess.sessionTeam == TEAM_SPECTATOR) {
		if (client->sess.spectatorState == SPECTATOR_SCOREBOARD) {
			Q_strncpyz(client->pers.netname, "scoreboard", sizeof(client->pers.netname));
		}
	}

	if (client->pers.connected == CON_CONNECTED) {
		if (strcmp(oldname, client->pers.netname)) {
			trap_SendServerCommand(-1, va("print \"%s" S_COLOR_WHITE " renamed to %s\n\"", oldname,
						      client->pers.netname));
		}
	}
	// set max health
	health = atoi(Info_ValueForKey(userinfo, "handicap"));
	client->pers.maxHealth = health;
	if (client->pers.maxHealth < 1 || client->pers.maxHealth > 100) {
		client->pers.maxHealth = 100;
	}
	// set model
	if (g_gametype.integer >= GT_TEAM) {
		Q_strncpyz(model, Info_ValueForKey(userinfo, "team_model"), sizeof(model));
		Q_strncpyz(headModel, Info_ValueForKey(userinfo, "team_headmodel"), sizeof(headModel));
	} else {
		Q_strncpyz(model, Info_ValueForKey(userinfo, "model"), sizeof(model));
		Q_strncpyz(headModel, Info_ValueForKey(userinfo, "headmodel"), sizeof(headModel));
	}
	// JBravo: set the radiosoundset
	s = Info_ValueForKey(userinfo, "cg_RQ3_radiovoice_male");
	if (!atoi(s)) {
		client->radioSetMale = 0;
	} else {
		client->radioSetMale = atoi(s);
	}
	s = Info_ValueForKey(userinfo, "cg_RQ3_radiovoice_female");
	if (!atoi(s)) {
		client->radioSetFemale = 0;
	} else {
		client->radioSetFemale = atoi(s);
	}
	// JBravo: Does the client get a frag reduced on suicides or not.
	s = Info_ValueForKey(userinfo, "cg_RQ3_SuicideLikeARealMan");
	if (!atoi(s)) {
		client->SuicideLikeARealMan = 0;
	} else {
		client->SuicideLikeARealMan = atoi(s);
	}
	// JBravo: to silence zcam messages
	s = Info_ValueForKey(userinfo, "cg_RQ3_zcam_stfu");
	if (!atoi(s)) {
		client->zcam_stfu = 0;
	} else {
		client->zcam_stfu = atoi(s);
	}

	if (g_gametype.integer >= GT_TEAM) {
		if (client->sess.savedTeam == TEAM_RED) {
			Q_strncpyz(model2, g_RQ3_team1model.string, sizeof(model));
			skin2 = strrchr(model2, '/');
			if (skin2) {
				*skin2++ = '\0';
			} else {
				skin2 = "robbers";
			}
			if (RQ3_Validatemodel(model2) != -1) {
				Com_sprintf(model, sizeof(model), "%s/%s", model2, skin2);
				Com_sprintf(headModel, sizeof(headModel), "%s/%s", model2, skin2);
			} else {
				Com_sprintf(model, sizeof(model), "reactionmale/robbers");
				Com_sprintf(headModel, sizeof(headModel), "reactionmale/robbers");
			}
		} else {
			Q_strncpyz(model2, g_RQ3_team2model.string, sizeof(model));
			skin2 = strrchr(model2, '/');
			if (skin2) {
				*skin2++ = '\0';
			} else {
				skin2 = "cops";
			}
			if (RQ3_Validatemodel(model2) != -1) {
				Com_sprintf(model, sizeof(model), "%s/%s", model2, skin2);
				Com_sprintf(headModel, sizeof(headModel), "%s/%s", model2, skin2);
			} else {
				Com_sprintf(model, sizeof(model), "reactionmale/cops");
				Com_sprintf(headModel, sizeof(headModel), "reactionmale/cops");
			}
		}
	} else {
		Q_strncpyz(model2, model, sizeof(model));
		skin2 = strrchr(model2, '/');
		if (skin2) {
			*skin2++ = '\0';
		} else {
			skin2 = "default";
		}

		// JBravo: Validating the model
		gender = RQ3_Validatemodel(model2);
		if (gender == -1) {
			trap_SendServerCommand(ent - g_entities,
					       va("print \"^1Illegal player model (%s). Forcing change on server.\n\"",
						  model2));
			Q_strncpyz(model, "reactionmale/default", sizeof("reactionmale/default"));
			Q_strncpyz(headModel, "reactionmale/default", sizeof("reactionmale/default"));
			client->radioGender = 0;	// Male
		} else if (gender != GENDER_NEUTER)
			client->radioGender = gender;
	}

	// teamInfo
	s = Info_ValueForKey(userinfo, "teamoverlay");
	if (!*s || atoi(s) != 0) {
		client->pers.teamInfo = qtrue;
	} else {
		client->pers.teamInfo = qfalse;
	}

	// team task (0 = none, 1 = offence, 2 = defence)
	teamTask = atoi(Info_ValueForKey(userinfo, "teamtask"));
	// team Leader (1 = leader, 0 is normal player)
	teamLeader = client->sess.teamLeader;

	// colors
	Q_strncpyz(c1, Info_ValueForKey(userinfo, "color1"), sizeof(c1));
	Q_strncpyz(c2, Info_ValueForKey(userinfo, "color2"), sizeof(c2));

	Q_strncpyz(redTeam, Info_ValueForKey(userinfo, "g_redteam"), sizeof(redTeam));
	Q_strncpyz(blueTeam, Info_ValueForKey(userinfo, "g_blueteam"), sizeof(blueTeam));

	// send over a subset of the userinfo keys so other clients can
	// print scoreboards, display models, and play custom sounds
	if (ent->r.svFlags & SVF_BOT) {
		//Makro - adding teamplay weapon/item info for bots
		s = va
		    ("n\\%s\\t\\%i\\model\\%s\\hmodel\\%s\\c1\\%s\\c2\\%s\\hc\\%i\\w\\%i\\l\\%i\\skill\\%s\\tt\\%d\\tl\\%d\\tpw\\%s\\tpi\\%s",
		     client->pers.netname, client->sess.sessionTeam, model, headModel, c1, c2, client->pers.maxHealth, client->sess.wins,
		     client->sess.losses,
		     //Info_ValueForKey( userinfo, "skill" ), teamTask, teamLeader );
		     Info_ValueForKey(userinfo, "skill"), teamTask, teamLeader, Info_ValueForKey(userinfo, "tpw"),
		     Info_ValueForKey(userinfo, "tpi"));
	} else {
		s = va
		    ("n\\%s\\t\\%i\\model\\%s\\hmodel\\%s\\g_redteam\\%s\\g_blueteam\\%s\\c1\\%s\\c2\\%s\\hc\\%i\\w\\%i\\l\\%i\\tt\\%d\\tl\\%d",
		     client->pers.netname, client->sess.savedTeam, model, headModel, redTeam, blueTeam, c1, c2,
		     client->pers.maxHealth, client->sess.wins, client->sess.losses, teamTask, teamLeader);
	}

	trap_SetConfigstring(CS_PLAYERS + clientNum, s);

	// this is not the userinfo, more like the configstring actually
	// JBravo: ugly in the logs.  Enable to debug if necessary
//      G_LogPrintf( "ClientUserinfoChanged: %i %s\n", clientNum, s );
}

/*
===========
G_SendCheatVars(int)

  Send which cvars are cheats, and the acceptable values
===========
*/
int G_SendCheatVars(int clientNum)
{
	char *text_p;
	int len;
	int i;
	char *token;
	char text[20000];
	fileHandle_t f;

	char cheatVar[40], cl_cheatvar[128];
	float lowval, highval;

	//NiceAss: Added so /devmap will not have the client check cvars. Lie to the server that it loaded fine =)
	if (g_cheats.integer)
		return qtrue;

	// load the file
	len = trap_FS_FOpenFile(g_RQ3_cvarfile.string, &f, FS_READ);
	if (len <= 0) {
		return qfalse;
	}
	if (len >= sizeof(text) - 1) {
		G_Printf("File %s too long\n", g_RQ3_cvarfile.string);
		return qfalse;
	}

	trap_FS_Read(text, len, f);
	text[len] = 0;
	trap_FS_FCloseFile(f);

	// parse the text
	text_p = text;

	for (i = 0; i < 30; i++) {
		token = COM_Parse(&text_p);
		if (!token)
			break;
		if (strlen(token) >= 40) {
			Com_Printf("Cheatvar %s is too long\n", token);
			return qfalse;
		}
		Q_strncpyz(cheatVar, token, sizeof(cheatVar));
// Fix from hal9000. Was NULL in that strcmp
		if (!strcmp(token, ""))
			return qtrue;
		token = COM_Parse(&text_p);
		if (!token)
			break;
		lowval = atof(token);
		token = COM_Parse(&text_p);
		if (!token)
			break;
		highval = atof(token);

		Com_sprintf(cl_cheatvar, sizeof(cl_cheatvar), "addCheatVar %s %f %f\n", cheatVar, lowval, highval);
		//Com_Printf("%s", cl_cheatvar);
		trap_SendServerCommand(clientNum, va("%s", cl_cheatvar));
	}
	return qtrue;
}

/*
===========
ClientConnect

Called when a player begins connecting to the server.
Called again for every map change or tournement restart.

The session information will be valid after exit.

Return NULL if the client should be allowed, otherwise return
a string with the reason for denial.

Otherwise, the client will be sent the current gamestate
and will eventually get to ClientBegin.

firstTime will be qtrue the very first time a client connects
to the server machine, but qfalse on map changes and tournement
restarts.
============
*/
char *ClientConnect(int clientNum, qboolean firstTime, qboolean isBot)
{
	char *value;
	gclient_t *client;
	char userinfo[MAX_INFO_STRING], ipaddr[64];
	gentity_t *ent;

	ent = &g_entities[clientNum];
	trap_GetUserinfo(clientNum, userinfo, sizeof(userinfo));

	// IP filtering
	// https://zerowing.idsoftware.com/bugzilla/show_bug.cgi?id=500
	// recommanding PB based IP / GUID banning, the builtin system is pretty limited
	// check to see if they are on the banned IP list
	value = Info_ValueForKey(userinfo, "ip");
	strncpy(ipaddr, value, sizeof(ipaddr));
	if (G_FilterPacket(value)) {
		return "You are banned from this server..";
	}
	// we don't check password for bots and local client
	// NOTE: local client <-> "ip" "localhost"
	// this means this client is not running in our current process
	if ( !isBot && (strcmp(value, "localhost") != 0)) {
		// check for a password
		value = Info_ValueForKey(userinfo, "password");
		if (g_password.string[0] && Q_stricmp(g_password.string, "none") &&
		    strcmp(g_password.string, value) != 0) {
			return "Invalid password";
		}
	}
	// if a player reconnects quickly after a disconnect, the client disconnect may never be called, thus flag can get lost in the ether
	if (ent->inuse) {
		G_LogPrintf("Forcing disconnect on active client: %i\n", clientNum);
		// so lets just fix up anything that should happen on a disconnect
		ClientDisconnect(clientNum);
	}
	// they can connect
	ent->client = level.clients + clientNum;
	client = ent->client;
	memset(client, 0, sizeof(*client));

	client->pers.connected = CON_CONNECTING;
// JBravo: Antistick
	client->ps.stats[STAT_RQ3] &= ~RQ3_PLAYERSOLID;
// JBravo: Clear zcam flag for cgame
	client->ps.stats[STAT_RQ3] &= ~RQ3_ZCAM;

	// check for local client
	value = Info_ValueForKey( userinfo, "ip" );
	if ( !strcmp( value, "localhost" ) ) {
		client->pers.localClient = qtrue;
	}

	if (isBot) {
		ent->r.svFlags |= SVF_BOT;
		ent->inuse = qtrue;
		if (!G_BotConnect(clientNum, !firstTime)) {
			return "BotConnectfailed";
		}
	}

	// read or initialize the session data
	if (firstTime || level.newSession) {
		G_InitSessionData(client, userinfo);
	}
	G_ReadSessionData(client);

// slicer : make sessionTeam = to savedTeam for scoreboard on cgame
// JBravo: only for teambased games. Could break DM
	if (g_gametype.integer >= GT_TEAM) {
		client->sess.sessionTeam = client->sess.savedTeam;
		ClientUserinfoChanged(clientNum);
	} else
		ClientUserinfoChanged(clientNum);

	// don't do the "xxx connected" messages if they were caried over from previous level
	if (firstTime) {
		trap_SendServerCommand(-1, va("print \"%s" S_COLOR_WHITE " connected\n\"", client->pers.netname));
		G_LogPrintf("%s@%s connected (clientNum %i)\n", client->pers.netname, ipaddr, clientNum);
	}

	if (g_gametype.integer >= GT_TEAM && g_gametype.integer != GT_TEAMPLAY && g_gametype.integer != GT_CTF &&
	    client->sess.sessionTeam != TEAM_SPECTATOR) {
		BroadcastTeamChange(client, -1);
	}
	// count current clients and rank for scoreboard
	CalculateRanks();

// JBravo: clients in TP begin as spectators
	if (g_gametype.integer >= GT_TEAM) {
		client->sess.sessionTeam = TEAM_SPECTATOR;
		client->ps.persistant[PERS_TEAM] = TEAM_SPECTATOR;
		client->sess.spectatorState = SPECTATOR_FREE;
		client->specMode = SPECTATOR_FREE;
		client->ps.pm_flags &= ~PMF_FOLLOW;
		client->ps.stats[STAT_RQ3] &= ~RQ3_ZCAM;
		camera_begin(ent);
		client->camera->mode = CAMERA_MODE_SWING;
	} else {
		client->ps.stats[STAT_RQ3] &= ~RQ3_ZCAM;
		camera_begin(ent);
		client->camera->mode = CAMERA_MODE_SWING;
	}
// JBravo: moved from ClientBegin
	client->pers.enterTime = level.time;
// JBravo: ditto
	if (g_gametype.integer == GT_FFA) {
		client->sess.sessionTeam = TEAM_FREE;
		client->sess.savedTeam = TEAM_FREE;
		client->ps.persistant[PERS_TEAM] = TEAM_FREE;
		client->sess.spectatorState = SPECTATOR_NOT;
		client->specMode = SPECTATOR_NOT;
	}

	return NULL;
}

/*
===========
ClientBegin

called when a client has finished connecting, and is ready
to be placed into the level.  This will happen every level load,
and on transition between teams, but doesn't happen on respawns
============
*/
void ClientBegin(int clientNum)
{
	gentity_t *ent;
	gclient_t *client;
	int flags, savedPing = 0, i;
	int savedPers[MAX_PERSISTANT];
	char str[256];

	ent = g_entities + clientNum;
	client = level.clients + clientNum;

	if (ent->r.linked) {
		trap_UnlinkEntity(ent);
	}

	G_InitGentity(ent);
	ent->touch = 0;
	ent->pain = 0;
	ent->client = client;

	//Slicer: Saving persistant and ping
	if (g_gametype.integer >= GT_TEAM) {
		savedPing = client->ps.ping;
		for (i = 0; i < MAX_PERSISTANT; i++)
			savedPers[i] = client->ps.persistant[i];
	}

	client->pers.connected = CON_CONNECTED;
	client->pers.teamState.state = TEAM_BEGIN;

	// save eflags around this, because changing teams will
	// cause this to happen with a valid entity, and we
	// want to make sure the teleport bit is set right
	// so the viewpoint doesn't interpolate through the
	// world to the new position
	flags = client->ps.eFlags;
	memset(&client->ps, 0, sizeof(client->ps));
	client->ps.eFlags = flags;

	//Slicer: Repost score and ping 
	if (g_gametype.integer >= GT_TEAM) {
		client->ps.ping = savedPing;
		for (i = 0; i < MAX_PERSISTANT; i++)
			client->ps.persistant[i] = savedPers[i];
	}
	// locate ent at a spawn point
	ClientSpawn(ent);

// JBravo: if teamplay and the client has not been on teams, make them a spectator.
	if ((g_gametype.integer >= GT_TEAM) &&
	    client->sess.sessionTeam != TEAM_RED && client->sess.sessionTeam != TEAM_BLUE) {
		client->sess.sessionTeam = TEAM_SPECTATOR;
		client->ps.persistant[PERS_SAVEDTEAM] = TEAM_SPECTATOR;
		client->ps.persistant[PERS_TEAM] = TEAM_SPECTATOR;
		client->sess.spectatorState = SPECTATOR_FREE;
		client->specMode = SPECTATOR_FREE;
		client->ps.pm_flags &= ~PMF_FOLLOW;
		client->ps.stats[STAT_RQ3] &= ~RQ3_ZCAM;
		RQ3_SpectatorMode(ent);
// JBravo: Set grenades to short, and the other weapons to full automatic on connect.
		client->ps.persistant[PERS_WEAPONMODES] |= RQ3_GRENSHORT;
		client->ps.persistant[PERS_WEAPONMODES] &= ~RQ3_GRENMED;
		client->ps.persistant[PERS_WEAPONMODES] |= RQ3_KNIFEMODE;
		client->ps.persistant[PERS_WEAPONMODES] &= ~RQ3_MP5MODE;
		client->ps.persistant[PERS_WEAPONMODES] &= ~RQ3_M4MODE;
		client->ps.persistant[PERS_WEAPONMODES] &= ~RQ3_MK23MODE;
		client->camera->mode = CAMERA_MODE_SWING;
	}

// JBravo: moved this up to clientconnect so DM players can join the spectator team.
/*	if (g_gametype.integer == GT_FFA) {
		client->sess.sessionTeam = TEAM_FREE;
		client->ps.persistant[PERS_TEAM] = TEAM_FREE;
		client->sess.spectatorState = SPECTATOR_NOT;
		client->specMode = SPECTATOR_NOT;
	} */

	if (client->sess.sessionTeam != TEAM_SPECTATOR && g_gametype.integer != GT_TEAMPLAY) {
		client->ps.persistant[PERS_WEAPONMODES] |= RQ3_GRENSHORT;	//set to short range
		client->ps.persistant[PERS_WEAPONMODES] |= RQ3_KNIFEMODE;	//set to slash attack

		if (g_gametype.integer != GT_TOURNAMENT) {
			trap_SendServerCommand(-1,
					       va("print \"%s" S_COLOR_WHITE " entered the game\n\"",
						  client->pers.netname));
		}
	}
	G_LogPrintf("ClientBegin: %i\n", clientNum);

// JBravo: synching the cvars over to clients for the MM ingame menu.
	if ((g_gametype.integer >= GT_TEAM) && g_RQ3_matchmode.integer) {
		for (i = 0; i < 9; ++i) {
			trap_SendServerCommand(ent - g_entities, va("rq3_cmd %i %s %i", CVARSET, settings2[i],
								    trap_Cvar_VariableIntegerValue(settings[i])));
		}
		trap_SendServerCommand(ent - g_entities, va("rq3_cmd %i cg_RQ3_capturelimit %i", CVARSET,
							    trap_Cvar_VariableIntegerValue("capturelimit")));
	}
// JBravo: setting cvars for the about menu
	trap_Cvar_VariableStringBuffer("sv_hostname", str, sizeof(str));
	trap_SendServerCommand(ent - g_entities, va("rq3_cmd %i cg_RQ3_hostname %s", CVARSET, str));
	trap_SendServerCommand(ent - g_entities, va("rq3_cmd %i cg_RQ3_needpass %i", CVARSET, g_needpass.integer));
	trap_SendServerCommand(ent - g_entities, va("rq3_cmd %i cg_RQ3_dmflags %i", CVARSET, g_dmflags.integer));
	trap_SendServerCommand(ent - g_entities, va("rq3_cmd %i cg_RQ3_showOwnKills %i", CVARSET, g_RQ3_showOwnKills.integer));
	trap_SendServerCommand(ent - g_entities, va("rq3_cmd %i cg_RQ3_timelimit %i", CVARSET, g_timelimit.integer));
	trap_SendServerCommand(ent - g_entities, va("rq3_cmd %i cg_RQ3_fraglimit %i", CVARSET, g_fraglimit.integer));
	trap_SendServerCommand(ent - g_entities, va("rq3_cmd %i cg_RQ3_bot_minplayers %i", CVARSET,
						    trap_Cvar_VariableIntegerValue("bot_minplayers")));

	// count current clients and rank for scoreboard
	CalculateRanks();

	// JBravo: default weapons
	if (g_gametype.integer >= GT_TEAM) {
		// NiceAss: Only set it if there is no value. Fix for going into spectator resetting values.
		if (ent->r.svFlags & SVF_BOT) {
			//Makro - changed to m4/laser from pistol/kevlar
			if (!client->teamplayWeapon) {
				if ((int) g_RQ3_weaponban.integer & WPF_M4) {
					client->teamplayWeapon = WP_M4;
				} else if ((int) g_RQ3_weaponban.integer & WPF_MK23) {
					client->teamplayWeapon = WP_PISTOL;
				} else if ((int) g_RQ3_weaponban.integer & WPF_KNIFE) {
					client->teamplayWeapon = WP_KNIFE;
				} else {
					client->teamplayWeapon = WP_PISTOL;
				}
			}
			if (!client->teamplayItem && ((int) g_RQ3_weaponban.integer & ITF_LASER))
				client->teamplayItem = HI_LASER;
		} else {
			if (!client->teamplayWeapon) {
				if ((int) g_RQ3_weaponban.integer & WPF_MP5) {
					client->teamplayWeapon = WP_MP5;
				} else if ((int) g_RQ3_weaponban.integer & WPF_MK23) {
					client->teamplayWeapon = WP_PISTOL;
				} else if ((int) g_RQ3_weaponban.integer & WPF_KNIFE) {
					client->teamplayWeapon = WP_KNIFE;
				} else {
					client->teamplayWeapon = WP_PISTOL;
				}
			}
			if (!client->teamplayItem && ((int) g_RQ3_weaponban.integer & ITF_KEVLAR))
				client->teamplayItem = HI_KEVLAR;
		}
		i = RQ3TeamCount(-1, client->sess.sessionTeam);
	}
}

/*
===========
ClientSpawn

Called every time a client is placed fresh in the world:
after the first ClientBegin, and after each respawn
Initializes all non-persistant parts of playerState
============
*/
void ClientSpawn(gentity_t * ent)
{
	int index, i, flags, savedPing;
	int persistant[MAX_PERSISTANT];
	vec3_t spawn_origin, spawn_angles;
	gclient_t *client;
	clientPersistant_t saved;
	clientSession_t savedSess;
	gentity_t *spawnPoint;
	int accuracy_hits, accuracy_shots, eventSequence;
	int savedWeapon, savedItem, savedSpec;	// JBravo: to save weapon/item info
	int savedRadiopower, savedRadiogender;	// JBravo: for radio.
	int savedMaleSet, savedFemaleSet;	// JBravo: for soundset saves.
	camera_t savedCamera;			// JBravo: to save camera stuff
	char userinfo[MAX_INFO_STRING];
	char *classname;

	//Slicer : Laser FIX

	//Try to turn the laser off if it's on
	if (ent->client->lasersight)
		Laser_Gen(ent, qfalse);

	index = ent - g_entities;
	client = ent->client;
	spawnPoint = NULL;

	// find a spawn point
	// do it before setting health back up, so farthest
	// ranging doesn't count this client

	if (client->sess.sessionTeam == TEAM_SPECTATOR) {
		if (g_gametype.integer == GT_CTF &&
		    (client->sess.savedTeam == TEAM_RED || client->sess.savedTeam == TEAM_BLUE)) {
			if (client->sess.savedTeam == TEAM_RED)
				classname = "team_CTF_redflag";
			else if (client->sess.savedTeam == TEAM_BLUE)
				classname = "team_CTF_blueflag";

			while ((spawnPoint = G_Find(spawnPoint, FOFS(classname), classname)) != NULL) {
				if (!(spawnPoint->flags & FL_DROPPED_ITEM))
					break;
			}
			if (spawnPoint) {
				VectorCopy(spawnPoint->r.currentOrigin, spawn_origin);
				VectorCopy(spawnPoint->s.angles, spawn_angles);
				spawn_origin[2] += 30;
			}
		} else if (VectorLength(ent->client->ps.origin) == 0.0f) {
			// Origin is not set yet? Use a spawn point
			spawnPoint = SelectSpectatorSpawnPoint(spawn_origin, spawn_angles);
			// Have a set origin already? Use it. (where you died or changed to spectator)
		} else {
			spawnPoint = NULL;
			VectorCopy(ent->client->ps.origin, spawn_origin);
			VectorCopy(ent->client->ps.viewangles, spawn_angles);
		}
	} else if (g_gametype.integer >= GT_CTF) {
		// all base oriented team games use the CTF spawn points
		spawnPoint = SelectCTFSpawnPoint(client->sess.sessionTeam,
						 client->pers.teamState.state, spawn_origin, spawn_angles);
// JBravo: If we are in Teamplay mode, use the teamspawnpoints.
	} else if (g_gametype.integer == GT_TEAMPLAY || (g_gametype.integer == GT_TEAM && client->sess.teamSpawn)) {
		// Freud: Assign the spawns from the spawning system (g_teamplay.c)
		level.team1spawnpoint = level.teamplay_spawns[0];
		level.team2spawnpoint = level.teamplay_spawns[1];

		if (client->sess.sessionTeam == TEAM_RED) {
			client->sess.spawnPoint = level.team1spawnpoint;
			spawnPoint = level.team1spawnpoint;
			VectorCopy(level.team1spawnpoint->s.angles, spawn_angles);
			VectorCopy(level.team1spawnpoint->s.origin, spawn_origin);
		} else {
			client->sess.spawnPoint = level.team2spawnpoint;
			spawnPoint = level.team2spawnpoint;
			VectorCopy(level.team2spawnpoint->s.angles, spawn_angles);
			VectorCopy(level.team2spawnpoint->s.origin, spawn_origin);
		}
		// Freud: Quake3 moves spawns up 9 pixs?
		spawn_origin[2] += 9;
// End JBravo.
	} else {
		do {
			// the first spawn should be at a good looking spot
			if (!client->pers.initialSpawn && client->pers.localClient) {
				client->pers.initialSpawn = qtrue;
				spawnPoint = SelectInitialSpawnPoint(spawn_origin, spawn_angles);
			} else {
				// don't spawn near existing origin if possible
				spawnPoint = SelectSpawnPoint(client->ps.origin, spawn_origin, spawn_angles);
			}

			// Tim needs to prevent bots from spawning at the initial point
			// on q3dm0...
			if ((spawnPoint->flags & FL_NO_BOTS) && (ent->r.svFlags & SVF_BOT)) {
				continue;	// try again
			}
			// just to be symetric, we have a nohumans option...
			if ((spawnPoint->flags & FL_NO_HUMANS) && !(ent->r.svFlags & SVF_BOT)) {
				continue;	// try again
			}

			break;

		} while (1);
	}
	client->pers.teamState.state = TEAM_ACTIVE;

	// toggle the teleport bit so the client knows to not lerp
	// and never clear the voted flag
	flags = ent->client->ps.eFlags & (EF_TELEPORT_BIT | EF_VOTED | EF_TEAMVOTED);
	flags ^= EF_TELEPORT_BIT;

	// JBravo: unlagged
	//ent->client->saved.leveltime = 0;

	// clear everything but the persistant data

	saved = client->pers;
	savedSess = client->sess;
	savedPing = client->ps.ping;
	accuracy_hits = client->accuracy_hits;
	accuracy_shots = client->accuracy_shots;

	for (i = 0; i < MAX_PERSISTANT; i++) {
		persistant[i] = client->ps.persistant[i];
	}
	eventSequence = client->ps.eventSequence;

// JBravo: save weapon/item info
	savedWeapon = client->teamplayWeapon;
	savedItem = client->teamplayItem;
	savedSpec = client->specMode;
// JBravo: save radiosettings
	savedRadiopower = client->radioOff;
	savedRadiogender = client->radioGender;
	savedMaleSet = client->radioSetMale;
	savedFemaleSet = client->radioSetFemale;
	memcpy(&savedCamera, &client->camera, sizeof(camera_t));

	Com_Memset (client, 0, sizeof(*client));

// JBravo: restore weapon/item info
	client->teamplayWeapon = savedWeapon;
	client->teamplayItem = savedItem;
	client->specMode = savedSpec;
// JBravo: restore radiosettings
	client->radioOff = savedRadiopower;
	client->radioGender = savedRadiogender;
	client->radioSetMale = savedMaleSet;
	client->radioSetFemale = savedFemaleSet;
	memcpy(&client->camera, &savedCamera, sizeof(camera_t));

	client->pers = saved;
	client->sess = savedSess;
	client->ps.ping = savedPing;
	client->accuracy_hits = accuracy_hits;
	client->accuracy_shots = accuracy_shots;
	client->lastkilled_client[0] = NULL;
	//Slicer
	client->weapon_attempts = 0;
	client->weapon_after_bandage_warned = qfalse;
	client->gibbed = qfalse;

	for (i = 0; i < MAX_PERSISTANT; i++) {
		client->ps.persistant[i] = persistant[i];
	}
	client->ps.eventSequence = eventSequence;
	// increment the spawncount so the client will detect the respawn
	client->ps.persistant[PERS_SPAWN_COUNT]++;
	client->ps.persistant[PERS_TEAM] = client->sess.sessionTeam;

	client->airOutTime = level.time + 12000;

	trap_GetUserinfo(index, userinfo, sizeof(userinfo));
	// set max health
	client->pers.maxHealth = atoi(Info_ValueForKey(userinfo, "handicap"));
	if (client->pers.maxHealth < 1 || client->pers.maxHealth > 100) {
		client->pers.maxHealth = 100;
	}
	// clear entity values
	client->ps.eFlags = flags;

	ent->s.groundEntityNum = ENTITYNUM_NONE;
	ent->client = &level.clients[index];
	ent->takedamage = qtrue;
	ent->inuse = qtrue;
	ent->classname = "player";
	ent->r.contents = CONTENTS_BODY;
	ent->clipmask = MASK_PLAYERSOLID;
	ent->die = player_die;
	ent->waterlevel = 0;
	ent->watertype = 0;
	ent->flags = 0;

	VectorCopy(playerMins, ent->r.mins);
	VectorCopy(playerMaxs, ent->r.maxs);

	client->ps.clientNum = index;

	camera_begin(ent);

//Blaze: changed WP_MACHINEGUN to WP_PISTOL, makes the base weapon you start with the pistol
// JBravo: Not in TP
	if (g_gametype.integer == GT_FFA || (g_gametype.integer == GT_TEAM && g_RQ3_tdmMode.integer)) {
		if ((int) g_RQ3_weaponban.integer & WPF_MK23) {
			client->ps.stats[STAT_WEAPONS] = (1 << WP_PISTOL);
			client->numClips[WP_PISTOL] = 0;
			client->ps.ammo[WP_PISTOL] = ClipAmountForAmmo(WP_PISTOL);
		}
		if ((int) g_RQ3_weaponban.integer & WPF_KNIFE) {
			client->ps.stats[STAT_WEAPONS] |= (1 << WP_KNIFE);
			client->ps.ammo[WP_KNIFE] = 1;
		}
	}
//Blaze: Set the bandage variable to 0
	client->bleedtick = 0;
	// health will count down towards max_health
	ent->health = client->ps.stats[STAT_HEALTH] = 100;	//Blaze: removed * 1.25 becase we wanna start at 100 health
	// reset streak count
	client->killStreak = 0;

	G_SetOrigin(ent, spawn_origin);
	VectorCopy(spawn_origin, client->ps.origin);

	// the respawned flag will be cleared after the attack and jump keys come up
	client->ps.pm_flags |= PMF_RESPAWNED;

	trap_GetUsercmd(client - level.clients, &ent->client->pers.cmd);
	SetClientViewAngle(ent, spawn_angles);

	if (ent->client->sess.sessionTeam == TEAM_SPECTATOR) {

	} else {
		G_KillBox(ent);
		trap_LinkEntity(ent);

		// force the base weapon up
		//Blaze: Changed WP_MACHINEGUN to WP_PISTOL
		// JBravo: we dont want the endless pistol in TP
		if (g_gametype.integer < GT_TEAM || (g_gametype.integer == GT_TEAM && g_RQ3_tdmMode.integer)) {
			client->ps.weapon = WP_PISTOL;
			client->ps.weaponstate = WEAPON_READY;
		}
	}

	//Blaze: Set the opendoor flag to 0
	client->openDoor = qfalse;
	client->openDoorTime = 0;

	// don't allow full run speed for a bit
	client->ps.pm_flags |= PMF_TIME_KNOCKBACK;
	client->ps.pm_time = 100;

	client->respawnTime = level.time;
	client->inactivityTime = level.time + g_inactivity.integer * 1000;
	client->latched_buttons = 0;

	//Elder: reset all RQ3 non-persistent stats
	ent->client->ps.stats[STAT_RQ3] = 0;

// JBravo: remember saved specmodes.
	if ((g_gametype.integer >= GT_TEAM) &&
	    client->sess.sessionTeam == TEAM_SPECTATOR) {
		if (client->specMode == SPECTATOR_FOLLOW || client->specMode == SPECTATOR_FREE) {
			client->sess.spectatorState = client->specMode;
			client->ps.stats[STAT_RQ3] &= ~RQ3_ZCAM;
		}
		if (client->specMode == SPECTATOR_ZCAM && client->sess.sessionTeam == TEAM_SPECTATOR) {
			client->sess.spectatorState = client->specMode;
			client->ps.stats[STAT_RQ3] |= RQ3_ZCAM;
			client->ps.pm_flags &= ~PMF_FOLLOW;
		}
	}
	//Elder: set weaponfireNextTime amount
	client->weaponfireNextTime = 0;

	//Elder: Initialize fast reloads stuff
	client->fastReloads = 0;
	client->lastReloadTime = 0;

	//Elder: initialize consecutive shots for M4 ride-up
	client->consecutiveShots = 0;

	// set default animations
	client->ps.torsoAnim = TORSO_STAND;
	client->ps.legsAnim = LEGS_IDLE;
	// weapon animations
	if (g_gametype.integer == GT_FFA || (g_gametype.integer == GT_TEAM && g_RQ3_tdmMode.integer))
		client->ps.generic1 = ((client->ps.generic1 & ANIM_TOGGLEBIT)
				       ^ ANIM_TOGGLEBIT) | WP_ANIM_IDLE;

	if (level.intermissiontime) {
		MoveClientToIntermission(ent);
	} else {
		// fire the targets of the spawn point
		if (spawnPoint)
			G_UseTargets(spawnPoint, ent);

		// select the highest weapon number available, after any
		// spawn given items have fired
		// JBravo: Lets make sure we have the right weapons
		if (g_gametype.integer >= GT_TEAM && !(g_gametype.integer == GT_TEAM && g_RQ3_tdmMode.integer) &&
		    (client->sess.sessionTeam == TEAM_RED || client->sess.sessionTeam == TEAM_BLUE)) {
			EquipPlayer(ent);
		} else {
			client->ps.weapon = 1;
			for (i = WP_NUM_WEAPONS - 1; i > 0; i--) {
				if (i == WP_KNIFE)
					continue;
				if (client->ps.stats[STAT_WEAPONS] & (1 << i)) {
					client->ps.weapon = i;
					break;
				}
			}
		}
	}

	// run a client frame to drop exactly to the floor,
	// initialize animations and other things
	client->ps.commandTime = level.time - 100;
	ent->client->pers.cmd.serverTime = level.time;
// JBravo: We should not have to call this during TP spawns
	if (g_gametype.integer == GT_FFA || (g_gametype.integer == GT_TEAM && g_RQ3_tdmMode.integer))
		ClientThink(ent - g_entities);

	// positively link the client, even if the command times are weird
	if (ent->client->sess.sessionTeam != TEAM_SPECTATOR) {
		BG_PlayerStateToEntityState(&client->ps, &ent->s, qtrue);
		VectorCopy(ent->client->ps.origin, ent->r.currentOrigin);
		trap_LinkEntity(ent);
	}
	// run the presend to set anything else
// JBravo: We should not have to call this during TP spawns
	if (g_gametype.integer == GT_FFA || (g_gametype.integer == GT_TEAM && g_RQ3_tdmMode.integer))
		ClientEndFrame(ent);
	ent->client->noHead = qfalse;

// JBravo: adding allitems.
	if (g_RQ3_allItems.integer) {
		ent->client->ps.stats[STAT_HOLDABLE_ITEM] = (1 << HI_KEVLAR);
		ent->client->ps.stats[STAT_HOLDABLE_ITEM] |= (1 << HI_LASER);
		ent->client->ps.stats[STAT_HOLDABLE_ITEM] |= (1 << HI_SILENCER);
		ent->client->ps.stats[STAT_HOLDABLE_ITEM] |= (1 << HI_BANDOLIER);
		ent->client->ps.stats[STAT_HOLDABLE_ITEM] |= (1 << HI_SLIPPERS);
		if (g_RQ3_haveHelmet.integer) {
			ent->client->ps.stats[STAT_HOLDABLE_ITEM] |= (1 << HI_HELMET);
			ent->client->uniqueItems = 6;
		} else {
			ent->client->uniqueItems = 5;
		}
	}

// JBravo: adding allweapons.
	if (g_RQ3_allWeapons.integer) {
		ent->client->ps.stats[STAT_WEAPONS] = (1 << WP_NUM_WEAPONS) - 1 - (1 << WP_NONE);
		ent->client->weaponCount[WP_SSG3000] = 1;
		ent->client->weaponCount[WP_MP5] = 1;
		ent->client->weaponCount[WP_M3] = 1;
		ent->client->weaponCount[WP_M4] = 1;
		ent->client->weaponCount[WP_AKIMBO] = 1;
		ent->client->weaponCount[WP_HANDCANNON] = 1;
		ent->client->uniqueWeapons = 5;
		//Makro - added knives
		ent->client->weaponCount[WP_KNIFE] = 1;
		for (i = 0; i < MAX_WEAPONS; i++) {
			ent->client->ps.ammo[i] = ClipAmountForAmmo(i);
			Add_Ammo(ent, i, 100, 1);
		}
		if (ent->client->ps.stats[STAT_HOLDABLE_ITEM] & (1 << HI_BANDOLIER))
			ent->client->ps.ammo[WP_KNIFE] = 20;
		else
			ent->client->ps.ammo[WP_KNIFE] = 10;

		ent->client->ps.stats[STAT_WEAPONS] |= (1 << WP_GRENADE) | (1 << WP_KNIFE);
	}

// JBravo: lock the player down
	if (g_gametype.integer == GT_CTF && ent->client->sess.sessionTeam == TEAM_SPECTATOR &&
	    (ent->client->sess.savedTeam == TEAM_RED || ent->client->sess.savedTeam == TEAM_BLUE) &&
	    !level.lights_camera_action)
		ent->client->ps.pm_type = PM_FREEZE;

	// clear entity state values
	BG_PlayerStateToEntityState(&client->ps, &ent->s, qtrue);
}

/*
===========
ClientDisconnect

Called when a player drops from the server.
Will not be called between levels.

This should NOT be called directly by any game logic,
call trap_DropClient(), which will call this and do
server system housekeeping.
============
*/
void ClientDisconnect(int clientNum)
{
	gentity_t *ent;
	gentity_t *tent;
	int oldTeam = 0, i;

	// cleanup if we are kicking a bot that
	// hasn't spawned yet
	G_RemoveQueuedBotBegin(clientNum);

	ent = g_entities + clientNum;
	if (!ent->client || ent->client->pers.connected == CON_DISCONNECTED) {
		return;
	}
// JBravo: to keep the ui teamcount cvars right.
	if (g_gametype.integer >= GT_TEAM) {
		oldTeam = ent->client->sess.sessionTeam;
	}
	//Slicer: matchmode
	if (g_RQ3_matchmode.integer) {
		if(ent->client->sess.referee)
			--level.refAmmount;
		switch (ent->client->sess.captain) {
		case TEAM_RED:
			level.team1ready = qfalse;
			break;
		case TEAM_BLUE:
			level.team2ready = qfalse;
			break;
		default:
			break;
		}
	}
	// aasimon: Referee. If player is referee, clean ref 
	/*if (clientNum == g_RQ3_RefID.integer)
	   trap_Cvar_Set("g_RQ3_RefID", "-1"); */

// JBravo: if the client had a laser, turn it off so it doesnt stay there forever.
	if (ent->client->lasersight) {
		G_FreeEntity(ent->client->lasersight);
		ent->client->lasersight = NULL;
	}
	// stop any following clients
	for (i = 0; i < level.maxclients; i++) {
		if (level.clients[i].sess.sessionTeam == TEAM_SPECTATOR
		    && level.clients[i].sess.spectatorState == SPECTATOR_FOLLOW
		    && level.clients[i].sess.spectatorClient == clientNum) {
			//Blaze: Prit out some Debug info
			if (&g_entities[i] == NULL) G_Printf("Ln 2049\n");

			StopFollowing(&g_entities[i]);
		}
	}

	camera_disconnect(ent);

	// send effect if they were completely connected
	if (ent->client->pers.connected == CON_CONNECTED && ent->client->sess.sessionTeam != TEAM_SPECTATOR) {
		tent = G_TempEntity(ent->client->ps.origin, EV_PLAYER_TELEPORT_OUT);
		tent->s.clientNum = ent->s.clientNum;

		// They don't get to take powerups with them!
		// Especially important for stuff like CTF flags
		TossClientItems(ent);
	}
// JBravo: Make this more like AQ
//      G_LogPrintf( "ClientDisconnect: %i\n", clientNum );
	G_LogPrintf("%s disconnected (clientNum %i)\n", ent->client->pers.netname, clientNum);

	// if we are playing in tourney mode and losing, give a win to the other player
	if ((g_gametype.integer == GT_TOURNAMENT)
	    && !level.intermissiontime && !level.warmupTime && level.sortedClients[1] == clientNum) {
		level.clients[level.sortedClients[0]].sess.wins++;
		ClientUserinfoChanged(level.sortedClients[0]);
	}

	trap_UnlinkEntity(ent);
	ent->s.modelindex = 0;
	ent->inuse = qfalse;
	ent->classname = "disconnected";
	ent->client->pers.connected = CON_DISCONNECTED;
	ent->client->ps.persistant[PERS_TEAM] = TEAM_FREE;
	ent->client->sess.sessionTeam = TEAM_FREE;

	trap_SetConfigstring(CS_PLAYERS + clientNum, "");

	CalculateRanks();

// JBravo: to keep the ui teamcount cvars right.
	if (g_gametype.integer >= GT_TEAM) {
		i = RQ3TeamCount(-1, oldTeam);
	}

	if (ent->r.svFlags & SVF_BOT) {
		BotAIShutdownClient(clientNum, qfalse);
	}
}
