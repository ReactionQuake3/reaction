//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.21  2003/04/26 22:33:07  jbravo
// Wratted all calls to G_FreeEnt() to avoid crashing and provide debugging
//
// Revision 1.20  2003/03/22 20:29:26  jbravo
// wrapping linkent and unlinkent calls
//
// Revision 1.19  2002/08/24 07:58:15  niceass
// moved sanitizestring to g_util
//
// Revision 1.18  2002/08/21 03:42:04  niceass
// move of some vector functions outside of just game
//
// Revision 1.17  2002/07/19 04:28:39  niceass
// no end line fix
//
// Revision 1.16  2002/07/16 04:06:21  niceass
// temporary hack solution for map rotation and ctb
//
// Revision 1.15  2002/07/11 04:26:46  niceass
// new debug function to save a string to a file
//
// Revision 1.14  2002/07/09 03:31:25  niceass
// oops
//
// Revision 1.13  2002/07/09 03:23:14  niceass
// added a alive function
//
// Revision 1.12  2002/06/16 20:06:14  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.11  2002/06/06 18:08:01  makro
// Removed pathtarget code for trigger_pushes for now
//
// Revision 1.10  2002/05/23 15:55:25  makro
// Elevators
//
// Revision 1.9  2002/05/20 16:25:48  makro
// Triggerable cameras
//
// Revision 1.8  2002/01/11 20:20:58  jbravo
// Adding TP to main branch
//
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
// g_utils.c -- misc utility functions for game module

#include "g_local.h"

typedef struct {
	char oldShader[MAX_QPATH];
	char newShader[MAX_QPATH];
	float timeOffset;
} shaderRemap_t;

#define MAX_SHADER_REMAPS 128

int remapCount = 0;
shaderRemap_t remappedShaders[MAX_SHADER_REMAPS];

void AddRemap(const char *oldShader, const char *newShader, float timeOffset)
{
	int i;

	for (i = 0; i < remapCount; i++) {
		if (Q_stricmp(oldShader, remappedShaders[i].oldShader) == 0) {
			// found it, just update this one
			strcpy(remappedShaders[i].newShader, newShader);
			remappedShaders[i].timeOffset = timeOffset;
			return;
		}
	}
	if (remapCount < MAX_SHADER_REMAPS) {
		strcpy(remappedShaders[remapCount].newShader, newShader);
		strcpy(remappedShaders[remapCount].oldShader, oldShader);
		remappedShaders[remapCount].timeOffset = timeOffset;
		remapCount++;
	}
}

const char *BuildShaderStateConfig()
{
	static char buff[MAX_STRING_CHARS * 4];
	char out[(MAX_QPATH * 2) + 5];
	int i;

	memset(buff, 0, MAX_STRING_CHARS);
	for (i = 0; i < remapCount; i++) {
		Com_sprintf(out, (MAX_QPATH * 2) + 5, "%s=%s:%5.2f@", remappedShaders[i].oldShader,
			    remappedShaders[i].newShader, remappedShaders[i].timeOffset);
		Q_strcat(buff, sizeof(buff), out);
	}
	return buff;
}

/*
=========================================================================

model / sound configstring indexes

=========================================================================
*/

/*
================
G_FindConfigstringIndex

================
*/
int G_FindConfigstringIndex(char *name, int start, int max, qboolean create)
{
	int i;
	char s[MAX_STRING_CHARS];

	if (!name || !name[0]) {
		return 0;
	}

	for (i = 1; i < max; i++) {
		trap_GetConfigstring(start + i, s, sizeof(s));
		if (!s[0]) {
			break;
		}
		if (!strcmp(s, name)) {
			return i;
		}
	}

	if (!create) {
		return 0;
	}

	if (i == max) {
		G_Error("G_FindConfigstringIndex: overflow");
	}

	trap_SetConfigstring(start + i, name);

	return i;
}

int G_ModelIndex(char *name)
{
	return G_FindConfigstringIndex(name, CS_MODELS, MAX_MODELS, qtrue);
}

int G_SoundIndex(char *name)
{
	return G_FindConfigstringIndex(name, CS_SOUNDS, MAX_SOUNDS, qtrue);
}

//=====================================================================

/*
================
G_TeamCommand

Broadcasts a command to only a specific team
================
*/
void G_TeamCommand(team_t team, char *cmd)
{
	int i;

	for (i = 0; i < level.maxclients; i++) {
		if (level.clients[i].pers.connected == CON_CONNECTED) {
			if (level.clients[i].sess.sessionTeam == team) {
				trap_SendServerCommand(i, va("%s", cmd));
			}
		}
	}
}

/*
=============
G_Find

Searches all active entities for the next one that holds
the matching string at fieldofs (use the FOFS() macro) in the structure.

Searches beginning at the entity after from, or the beginning if NULL
NULL will be returned if the end of the list is reached.

=============
*/
gentity_t *G_Find(gentity_t * from, int fieldofs, const char *match)
{
	char *s;

	if (!from)
		from = g_entities;
	else
		from++;

	for (; from < &g_entities[level.num_entities]; from++) {
		if (!from->inuse)
			continue;
		s = *(char **) ((byte *) from + fieldofs);
		if (!s)
			continue;
		if (!Q_stricmp(s, match))
			return from;
	}

	return NULL;
}

//Makro - returns the first entity that matches both fieldofs
gentity_t *G_Find2(gentity_t * from, int fieldofs, const char *match, int fieldofs2, const char *match2)
{
	gentity_t *ent;

	for (ent = G_Find(from, fieldofs, match); ent; ent = G_Find(ent, fieldofs, match)) {
		char *s = *(char **) ((byte *) ent + fieldofs2);

		if (!s)
			continue;
		if (!Q_stricmp(s, match2))
			return ent;
	}

	return NULL;
}

/*
=============
G_PickTarget

Selects a random entity from among the targets
=============
*/
#define MAXCHOICES	32

gentity_t *G_PickTarget(char *targetname)
{
	gentity_t *ent = NULL;
	int num_choices = 0;
	gentity_t *choice[MAXCHOICES];

	if (!targetname) {
		G_Printf("G_PickTarget called with NULL targetname\n");
		return NULL;
	}

	while (1) {
		ent = G_Find(ent, FOFS(targetname), targetname);
		if (!ent)
			break;
		choice[num_choices++] = ent;
		if (num_choices == MAXCHOICES)
			break;
	}

	if (!num_choices) {
		G_Printf("G_PickTarget: target %s not found\n", targetname);
		return NULL;
	}

	return choice[rand() % num_choices];
}

/*
==============================
G_UseTargets

"activator" should be set to the entity that initiated the firing.

Search for (string)targetname in all entities that
match (string)self.target and call their .use function

==============================
*/
void G_UseTargets(gentity_t * ent, gentity_t * activator)
{
	gentity_t *t;

	if (!ent) {
		return;
	}

	if (ent->targetShaderName && ent->targetShaderNewName) {
		float f = level.time * 0.001;

		AddRemap(ent->targetShaderName, ent->targetShaderNewName, f);
		trap_SetConfigstring(CS_SHADERSTATE, BuildShaderStateConfig());
	}

	if (!ent->target) {
		return;
	}

	t = NULL;
	while ((t = G_Find(t, FOFS(targetname), ent->target)) != NULL) {
		if (t == ent) {
			G_Printf("WARNING: Entity used itself.\n");
		} else {
			if (t->use) {
				t->use(t, ent, activator);
			}
		}
		if (!ent->inuse) {
			G_Printf("entity was removed while using targets\n");
			return;
		}
	}
}


/*
===============
G_SetMovedir

The editor only specifies a single value for angles (yaw),
but we have special constants to generate an up or down direction.
Angles will be cleared, because it is being used to represent a direction
instead of an orientation.
===============
*/
void G_SetMovedir(vec3_t angles, vec3_t movedir)
{
	static vec3_t VEC_UP = { 0, -1, 0 };
	static vec3_t MOVEDIR_UP = { 0, 0, 1 };
	static vec3_t VEC_DOWN = { 0, -2, 0 };
	static vec3_t MOVEDIR_DOWN = { 0, 0, -1 };

	if (VectorCompare(angles, VEC_UP)) {
		VectorCopy(MOVEDIR_UP, movedir);
	} else if (VectorCompare(angles, VEC_DOWN)) {
		VectorCopy(MOVEDIR_DOWN, movedir);
	} else {
		AngleVectors(angles, movedir, NULL, NULL);
	}
	VectorClear(angles);
}

float vectoyaw(const vec3_t vec)
{
	float yaw;

	if (vec[YAW] == 0 && vec[PITCH] == 0) {
		yaw = 0;
	} else {
		if (vec[PITCH]) {
			yaw = (atan2(vec[YAW], vec[PITCH]) * 180 / M_PI);
		} else if (vec[YAW] > 0) {
			yaw = 90;
		} else {
			yaw = 270;
		}
		if (yaw < 0) {
			yaw += 360;
		}
	}

	return yaw;
}

void G_InitGentity(gentity_t * e)
{
	e->inuse = qtrue;
	e->classname = "noclass";
	e->s.number = e - g_entities;
	e->r.ownerNum = ENTITYNUM_NONE;
}

/*
=================
G_Spawn

Either finds a free entity, or allocates a new one.

  The slots from 0 to MAX_CLIENTS-1 are always reserved for clients, and will
never be used by anything else.

Try to avoid reusing an entity that was recently freed, because it
can cause the client to think the entity morphed into something else
instead of being removed and recreated, which can cause interpolated
angles and bad trails.
=================
*/
gentity_t *G_Spawn(void)
{
	int i, force;
	gentity_t *e;

	e = NULL;		// shut up warning
	i = 0;			// shut up warning
	for (force = 0; force < 2; force++) {
		// if we go through all entities and can't find one to free,
		// override the normal minimum times before use
		e = &g_entities[MAX_CLIENTS];
		for (i = MAX_CLIENTS; i < level.num_entities; i++, e++) {
			if (e->inuse) {
				continue;
			}
			// the first couple seconds of server time can involve a lot of
			// freeing and allocating, so relax the replacement policy
			if (!force && e->freetime > level.startTime + 2000 && level.time - e->freetime < 1000) {
				continue;
			}
			// reuse this slot
			G_InitGentity(e);
			return e;
		}
		if (i != MAX_GENTITIES) {
			break;
		}
	}
	if (i == ENTITYNUM_MAX_NORMAL) {
		for (i = 0; i < MAX_GENTITIES; i++) {
			G_Printf("%4i: %s\n", i, g_entities[i].classname);
		}
		G_Error("G_Spawn: no free entities");
	}
	// open up a new slot
	level.num_entities++;

	// let the server system know that there are more entities
	trap_LocateGameData(level.gentities, level.num_entities, sizeof(gentity_t),
			    &level.clients[0].ps, sizeof(level.clients[0]));

	G_InitGentity(e);
	return e;
}

/*
=================
G_EntitiesFree
=================
*/
qboolean G_EntitiesFree(void)
{
	int i;
	gentity_t *e;

	e = &g_entities[MAX_CLIENTS];
	for (i = MAX_CLIENTS; i < level.num_entities; i++, e++) {
		if (e->inuse) {
			continue;
		}
		// slot available
		return qtrue;
	}
	return qfalse;
}

/*
=================
G_FreeEntity

Marks the entity as free
=================
*/
void G_FreeEntity(gentity_t * ed, int line, char *file)
{
	if (ed == NULL || ed-g_entities < 0 || ed-g_entities > level.num_entities || ed->s.number <0 || ed->s.number > level.num_entities) {
		trap_SendServerCommand(-1, va("print \"^1G_FreeEntity got called with a bad ent from line %d of file %s. PLEASE report this to the RQ3 team\"", line, file));
		G_LogPrintf("G_FreeEntity got called with a bad ent from line %d of file %s. PLEASE report this to the RQ3 team", line, file);
		return;
	}

	trap_RQ3UnlinkEntity(ed, __LINE__, __FILE__);	// unlink from world

	if (ed->neverFree) {
		return;
	}

	memset(ed, 0, sizeof(*ed));
	ed->classname = "freed";
	ed->freetime = level.time;
	ed->inuse = qfalse;
}

void G_RealFreeEntity(gentity_t * ed)
{
	if (ed == NULL || ed-g_entities < 0 || ed-g_entities > level.num_entities || ed->s.number <0 || ed->s.number > level.num_entities) {
		trap_SendServerCommand(-1, va("print \"^1G_FreeEntity got called with a bad ent with no tracing. PLEASE report this to the RQ3 team\""));
		G_LogPrintf("G_FreeEntity got called with a bad ent with no tracing. PLEASE report this to the RQ3 team");
		return;
	}

	trap_RQ3UnlinkEntity(ed, __LINE__, __FILE__);	// unlink from world

	if (ed->neverFree) {
		return;
	}

	memset(ed, 0, sizeof(*ed));
	ed->classname = "freed";
	ed->freetime = level.time;
	ed->inuse = qfalse;
}

/*
=================
G_TempEntity

Spawns an event entity that will be auto-removed
The origin will be snapped to save net bandwidth, so care
must be taken if the origin is right on a surface (snap towards start vector first)
=================
*/
gentity_t *G_TempEntity(vec3_t origin, int event)
{
	gentity_t *e;
	vec3_t snapped;

	e = G_Spawn();
	e->s.eType = ET_EVENTS + event;

	e->classname = "tempEntity";
	e->eventTime = level.time;
	e->freeAfterEvent = qtrue;

	VectorCopy(origin, snapped);
	SnapVector(snapped);	// save network bandwidth
	G_SetOrigin(e, snapped);

	// find cluster for PVS
	trap_RQ3LinkEntity(e, __LINE__, __FILE__);

	return e;
}

/*
=================
G_TempEntity2
Elder: Like above, except can sneak in event parameters
=================
*/
gentity_t *G_TempEntity2(vec3_t origin, int event, int eParm)
{
	gentity_t *e;
	vec3_t snapped;

	e = G_Spawn();
	e->s.eType = ET_EVENTS + event;
	e->s.eventParm = eParm;

	e->classname = "tempEntity";
	e->eventTime = level.time;
	e->freeAfterEvent = qtrue;

	VectorCopy(origin, snapped);
	SnapVector(snapped);	// save network bandwidth
	G_SetOrigin(e, snapped);

	// find cluster for PVS
	trap_RQ3LinkEntity(e, __LINE__, __FILE__);

	return e;
}

/*
==============================================================================

Kill box

==============================================================================
*/

/*
=================
G_KillBox

Kills all entities that would touch the proposed new positioning
of ent.  Ent should be unlinked before calling this!
=================
*/
void G_KillBox(gentity_t * ent)
{
	int i, num;
	int touch[MAX_GENTITIES];
	gentity_t *hit;
	vec3_t mins, maxs;

// JBravo attempting to stop telefrags
	if (g_gametype.integer == GT_TEAMPLAY) {	// && level.lights_camera_action) {
		return;
	}

	VectorAdd(ent->client->ps.origin, ent->r.mins, mins);
	VectorAdd(ent->client->ps.origin, ent->r.maxs, maxs);
	num = trap_EntitiesInBox(mins, maxs, touch, MAX_GENTITIES);

	for (i = 0; i < num; i++) {
		hit = &g_entities[touch[i]];
		if (!hit->client) {
			continue;
		}
		// nail it
		G_Damage(hit, ent, ent, NULL, NULL, 100000, DAMAGE_NO_PROTECTION, MOD_TELEFRAG);
	}

}

//==============================================================================

/*
===============
G_AddPredictableEvent

Use for non-pmove events that would also be predicted on the
client side: jumppads and item pickups
Adds an event+parm and twiddles the event counter
===============
*/
void G_AddPredictableEvent(gentity_t * ent, int event, int eventParm)
{
	if (!ent->client) {
		return;
	}
	BG_AddPredictableEventToPlayerstate(event, eventParm, &ent->client->ps);
}

/*
===============
G_AddEvent

Adds an event+parm and twiddles the event counter
===============
*/
void G_AddEvent(gentity_t * ent, int event, int eventParm)
{
	int bits;

	if (!event) {
		G_Printf("G_AddEvent: zero event added for entity %i\n", ent->s.number);
		return;
	}
	// clients need to add the event in playerState_t instead of entityState_t
	if (ent->client) {
		bits = ent->client->ps.externalEvent & EV_EVENT_BITS;
		bits = (bits + EV_EVENT_BIT1) & EV_EVENT_BITS;
		ent->client->ps.externalEvent = event | bits;
		ent->client->ps.externalEventParm = eventParm;
		ent->client->ps.externalEventTime = level.time;
	} else {
		bits = ent->s.event & EV_EVENT_BITS;
		bits = (bits + EV_EVENT_BIT1) & EV_EVENT_BITS;
		ent->s.event = event | bits;
		ent->s.eventParm = eventParm;
	}
	ent->eventTime = level.time;
}

/*
=============
G_Sound
=============
*/
void G_Sound(gentity_t * ent, int channel, int soundIndex)
{
	gentity_t *te;

	te = G_TempEntity(ent->r.currentOrigin, EV_GENERAL_SOUND);
	te->s.eventParm = soundIndex;
}

//==============================================================================

/*
================
G_SetOrigin

Sets the pos trajectory for a fixed position
================
*/
void G_SetOrigin(gentity_t * ent, vec3_t origin)
{
	VectorCopy(origin, ent->s.pos.trBase);
	ent->s.pos.trType = TR_STATIONARY;
	ent->s.pos.trTime = 0;
	ent->s.pos.trDuration = 0;
	VectorClear(ent->s.pos.trDelta);

	VectorCopy(origin, ent->r.currentOrigin);
}

/*
================
DebugLine

  debug polygons only work when running a local game
  with r_debugSurface set to 2
================
*/
int DebugLine(vec3_t start, vec3_t end, int color)
{
	vec3_t points[4], dir, cross, up = { 0, 0, 1 };
	float dot;

	VectorCopy(start, points[0]);
	VectorCopy(start, points[1]);
	//points[1][2] -= 2;
	VectorCopy(end, points[2]);
	//points[2][2] -= 2;
	VectorCopy(end, points[3]);

	VectorSubtract(end, start, dir);
	VectorNormalize(dir);
	dot = DotProduct(dir, up);
	if (dot > 0.99 || dot < -0.99)
		VectorSet(cross, 1, 0, 0);
	else
		CrossProduct(dir, up, cross);

	VectorNormalize(cross);

	VectorMA(points[0], 2, cross, points[0]);
	VectorMA(points[1], -2, cross, points[1]);
	VectorMA(points[2], -2, cross, points[2]);
	VectorMA(points[3], 2, cross, points[3]);

	return trap_DebugPolygonCreate(color, 4, points);
}

// Blaze: Find radius
//
gentity_t *findradius(gentity_t * from, vec3_t org, float rad)
{
	vec3_t eorg;
	int j;

	if (!from)
		from = g_entities;
	else
		from++;

	for (; from < &g_entities[level.num_entities]; from++) {
		if (!from->inuse)
			continue;
		for (j = 0; j < 3; j++)
			eorg[j] = org[j] - (from->r.currentOrigin[j] + (from->r.mins[j] + from->r.maxs[j]) * 0.5);
		if (VectorLength(eorg) > rad)
			continue;
		return from;
	}

	return NULL;
}

/*
================
Added by Elder

RQ3_SaveZoomLevel

Quick function to save the last zoom setting
================
*/
void RQ3_SaveZoomLevel(gentity_t * ent)
{
	if (ent->client) {
		if ((ent->client->ps.stats[STAT_RQ3] & RQ3_ZOOM_LOW) == RQ3_ZOOM_LOW)
			ent->client->lastzoom |= RQ3_ZOOM_LOW;
		if ((ent->client->ps.stats[STAT_RQ3] & RQ3_ZOOM_MED) == RQ3_ZOOM_MED)
			ent->client->lastzoom |= RQ3_ZOOM_MED;
	}
}

/*
================
Added by Elder

RQ3_isZoomed

Quick function to determine if player is zoomed in
================
*/
int RQ3_isZoomed(gentity_t * ent)
{
	if (!ent->client) {
		G_Error("RQ3_isZoomed: passed non-client entity");
		return -1;
	} else {
		return ((ent->client->ps.stats[STAT_RQ3] & RQ3_ZOOM_LOW) == RQ3_ZOOM_LOW ||
			(ent->client->ps.stats[STAT_RQ3] & RQ3_ZOOM_MED) == RQ3_ZOOM_MED);
	}
}

/*
	G_PlayerAlive			by NiceAss

	Created to fix complications when inbetween death and being a spectator in TP
*/
int G_PlayerAlive(gentity_t *ent)
{
	if (g_gametype.integer < GT_TEAM) 
	{
		if ( ent->health > 0 )
			return qtrue;
		else
			return qfalse;
	}
	else
	{
		if ( ent->health > 0 && ( ent->client->sess.sessionTeam == TEAM_RED || ent->client->sess.sessionTeam == TEAM_BLUE ) )
			return qtrue;
		else
			return qfalse;
	}
}

/*
	Want to save data right before RQ3 crashes? Ues this =D
*/
void G_DebugSaveData(char *Data) {
	fileHandle_t f;

	if (trap_FS_FOpenFile("debugout.txt", &f, FS_WRITE) >= 0) {
		trap_FS_Write(Data, strlen(Data), f);
		trap_FS_FCloseFile(f);
	}
}

qboolean G_FileSearch(char *Filename, char *Text) {
	fileHandle_t file;
	char *buf;
	int len;

	len = trap_FS_FOpenFile(Filename, &file, FS_READ);

	if (!file)
		return qfalse;

	buf = G_Alloc(len);
	trap_FS_Read(buf, len, file);

	trap_FS_FCloseFile(file);

	return ( strstr(buf, Text) != NULL );
}

/*
==================
SanitizeString

Remove case and control characters
==================
*/
void SanitizeString(char *in, char *out)
{
	while (*in) {
		if (*in == 27) {
			in += 2;	// skip color code
			continue;
		}
		if (*in < 32) {
			in++;
			continue;
		}
		*out++ = tolower(*in++);
	}

	*out = 0;
}
