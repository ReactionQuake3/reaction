//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.24  2003/09/19 21:25:10  makro
// Flares (again!). Doors that open away from players.
//
// Revision 1.23  2003/09/18 23:28:44  jbravo
// Adding G_acos()
//
// Revision 1.22  2003/09/07 20:02:51  makro
// no message
//
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
//Makro - added
void G_UseEntities(gentity_t * ent, char *target, gentity_t * activator)
{
	gentity_t *t;

	if (!ent || !target) {
		return;
	}

	if (ent->targetShaderName && ent->targetShaderNewName) {
		float f = level.time * 0.001;

		AddRemap(ent->targetShaderName, ent->targetShaderNewName, f);
		trap_SetConfigstring(CS_SHADERSTATE, BuildShaderStateConfig());
	}

	t = NULL;
	while ((t = G_Find(t, FOFS(targetname), target)) != NULL) {
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

void G_UseTargets(gentity_t * ent, gentity_t * activator)
{
	//Makro - moved the code to the function above
	G_UseEntities(ent, ent->target, activator);
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

//Makro - old table
/*
float G_acostable[] = {
	3.14159265, 3.07908248, 3.05317551, 3.03328655, 3.01651113, 3.00172442, 2.98834964, 2.97604422,
	2.96458497, 2.95381690, 2.94362719, 2.93393068, 2.92466119, 2.91576615, 2.90720289, 2.89893629,
	2.89093699, 2.88318015, 2.87564455, 2.86831188, 2.86116621, 2.85419358, 2.84738169, 2.84071962,
	2.83419760, 2.82780691, 2.82153967, 2.81538876, 2.80934770, 2.80341062, 2.79757211, 2.79182724,
	2.78617145, 2.78060056, 2.77511069, 2.76969824, 2.76435988, 2.75909250, 2.75389319, 2.74875926,
	2.74368816, 2.73867752, 2.73372510, 2.72882880, 2.72398665, 2.71919677, 2.71445741, 2.70976688,
	2.70512362, 2.70052613, 2.69597298, 2.69146283, 2.68699438, 2.68256642, 2.67817778, 2.67382735,
	2.66951407, 2.66523692, 2.66099493, 2.65678719, 2.65261279, 2.64847088, 2.64436066, 2.64028133,
	2.63623214, 2.63221238, 2.62822133, 2.62425835, 2.62032277, 2.61641398, 2.61253138, 2.60867440,
	2.60484248, 2.60103507, 2.59725167, 2.59349176, 2.58975488, 2.58604053, 2.58234828, 2.57867769,
	2.57502832, 2.57139977, 2.56779164, 2.56420354, 2.56063509, 2.55708594, 2.55355572, 2.55004409,
	2.54655073, 2.54307530, 2.53961750, 2.53617701, 2.53275354, 2.52934680, 2.52595650, 2.52258238,
	2.51922417, 2.51588159, 2.51255441, 2.50924238, 2.50594525, 2.50266278, 2.49939476, 2.49614096,
	2.49290115, 2.48967513, 2.48646269, 2.48326362, 2.48007773, 2.47690482, 2.47374472, 2.47059722,
	2.46746215, 2.46433933, 2.46122860, 2.45812977, 2.45504269, 2.45196720, 2.44890314, 2.44585034,
	2.44280867, 2.43977797, 2.43675809, 2.43374890, 2.43075025, 2.42776201, 2.42478404, 2.42181622,
	2.41885841, 2.41591048, 2.41297232, 2.41004380, 2.40712480, 2.40421521, 2.40131491, 2.39842379,
	2.39554173, 2.39266863, 2.38980439, 2.38694889, 2.38410204, 2.38126374, 2.37843388, 2.37561237,
	2.37279910, 2.36999400, 2.36719697, 2.36440790, 2.36162673, 2.35885335, 2.35608768, 2.35332964,
	2.35057914, 2.34783610, 2.34510044, 2.34237208, 2.33965094, 2.33693695, 2.33423003, 2.33153010,
	2.32883709, 2.32615093, 2.32347155, 2.32079888, 2.31813284, 2.31547337, 2.31282041, 2.31017388,
	2.30753373, 2.30489988, 2.30227228, 2.29965086, 2.29703556, 2.29442632, 2.29182309, 2.28922580,
	2.28663439, 2.28404881, 2.28146900, 2.27889490, 2.27632647, 2.27376364, 2.27120637, 2.26865460,
	2.26610827, 2.26356735, 2.26103177, 2.25850149, 2.25597646, 2.25345663, 2.25094195, 2.24843238,
	2.24592786, 2.24342836, 2.24093382, 2.23844420, 2.23595946, 2.23347956, 2.23100444, 2.22853408,
	2.22606842, 2.22360742, 2.22115104, 2.21869925, 2.21625199, 2.21380924, 2.21137096, 2.20893709,
	2.20650761, 2.20408248, 2.20166166, 2.19924511, 2.19683280, 2.19442469, 2.19202074, 2.18962092,
	2.18722520, 2.18483354, 2.18244590, 2.18006225, 2.17768257, 2.17530680, 2.17293493, 2.17056692,
	2.16820274, 2.16584236, 2.16348574, 2.16113285, 2.15878367, 2.15643816, 2.15409630, 2.15175805,
	2.14942338, 2.14709226, 2.14476468, 2.14244059, 2.14011997, 2.13780279, 2.13548903, 2.13317865,
	2.13087163, 2.12856795, 2.12626757, 2.12397047, 2.12167662, 2.11938600, 2.11709859, 2.11481435,
	2.11253326, 2.11025530, 2.10798044, 2.10570867, 2.10343994, 2.10117424, 2.09891156, 2.09665185,
	2.09439510, 2.09214129, 2.08989040, 2.08764239, 2.08539725, 2.08315496, 2.08091550, 2.07867884,
	2.07644495, 2.07421383, 2.07198545, 2.06975978, 2.06753681, 2.06531651, 2.06309887, 2.06088387,
	2.05867147, 2.05646168, 2.05425445, 2.05204979, 2.04984765, 2.04764804, 2.04545092, 2.04325628,
	2.04106409, 2.03887435, 2.03668703, 2.03450211, 2.03231957, 2.03013941, 2.02796159, 2.02578610,
	2.02361292, 2.02144204, 2.01927344, 2.01710710, 2.01494300, 2.01278113, 2.01062146, 2.00846399,
	2.00630870, 2.00415556, 2.00200457, 1.99985570, 1.99770895, 1.99556429, 1.99342171, 1.99128119,
	1.98914271, 1.98700627, 1.98487185, 1.98273942, 1.98060898, 1.97848051, 1.97635399, 1.97422942,
	1.97210676, 1.96998602, 1.96786718, 1.96575021, 1.96363511, 1.96152187, 1.95941046, 1.95730088,
	1.95519310, 1.95308712, 1.95098292, 1.94888050, 1.94677982, 1.94468089, 1.94258368, 1.94048818,
	1.93839439, 1.93630228, 1.93421185, 1.93212308, 1.93003595, 1.92795046, 1.92586659, 1.92378433,
	1.92170367, 1.91962459, 1.91754708, 1.91547113, 1.91339673, 1.91132385, 1.90925250, 1.90718266,
	1.90511432, 1.90304746, 1.90098208, 1.89891815, 1.89685568, 1.89479464, 1.89273503, 1.89067683,
	1.88862003, 1.88656463, 1.88451060, 1.88245794, 1.88040664, 1.87835668, 1.87630806, 1.87426076,
	1.87221477, 1.87017008, 1.86812668, 1.86608457, 1.86404371, 1.86200412, 1.85996577, 1.85792866,
	1.85589277, 1.85385809, 1.85182462, 1.84979234, 1.84776125, 1.84573132, 1.84370256, 1.84167495,
	1.83964848, 1.83762314, 1.83559892, 1.83357582, 1.83155381, 1.82953289, 1.82751305, 1.82549429,
	1.82347658, 1.82145993, 1.81944431, 1.81742973, 1.81541617, 1.81340362, 1.81139207, 1.80938151,
	1.80737194, 1.80536334, 1.80335570, 1.80134902, 1.79934328, 1.79733848, 1.79533460, 1.79333164,
	1.79132959, 1.78932843, 1.78732817, 1.78532878, 1.78333027, 1.78133261, 1.77933581, 1.77733985,
	1.77534473, 1.77335043, 1.77135695, 1.76936428, 1.76737240, 1.76538132, 1.76339101, 1.76140148,
	1.75941271, 1.75742470, 1.75543743, 1.75345090, 1.75146510, 1.74948002, 1.74749565, 1.74551198,
	1.74352900, 1.74154672, 1.73956511, 1.73758417, 1.73560389, 1.73362426, 1.73164527, 1.72966692,
	1.72768920, 1.72571209, 1.72373560, 1.72175971, 1.71978441, 1.71780969, 1.71583556, 1.71386199,
	1.71188899, 1.70991653, 1.70794462, 1.70597325, 1.70400241, 1.70203209, 1.70006228, 1.69809297,
	1.69612416, 1.69415584, 1.69218799, 1.69022062, 1.68825372, 1.68628727, 1.68432127, 1.68235571,
	1.68039058, 1.67842588, 1.67646160, 1.67449772, 1.67253424, 1.67057116, 1.66860847, 1.66664615,
	1.66468420, 1.66272262, 1.66076139, 1.65880050, 1.65683996, 1.65487975, 1.65291986, 1.65096028,
	1.64900102, 1.64704205, 1.64508338, 1.64312500, 1.64116689, 1.63920905, 1.63725148, 1.63529416,
	1.63333709, 1.63138026, 1.62942366, 1.62746728, 1.62551112, 1.62355517, 1.62159943, 1.61964388,
	1.61768851, 1.61573332, 1.61377831, 1.61182346, 1.60986877, 1.60791422, 1.60595982, 1.60400556,
	1.60205142, 1.60009739, 1.59814349, 1.59618968, 1.59423597, 1.59228235, 1.59032882, 1.58837536,
	1.58642196, 1.58446863, 1.58251535, 1.58056211, 1.57860891, 1.57665574, 1.57470259, 1.57274945,
	1.57079633, 1.56884320, 1.56689007, 1.56493692, 1.56298375, 1.56103055, 1.55907731, 1.55712403,
	1.55517069, 1.55321730, 1.55126383, 1.54931030, 1.54735668, 1.54540297, 1.54344917, 1.54149526,
	1.53954124, 1.53758710, 1.53563283, 1.53367843, 1.53172389, 1.52976919, 1.52781434, 1.52585933,
	1.52390414, 1.52194878, 1.51999323, 1.51803748, 1.51608153, 1.51412537, 1.51216900, 1.51021240,
	1.50825556, 1.50629849, 1.50434117, 1.50238360, 1.50042576, 1.49846765, 1.49650927, 1.49455060,
	1.49259163, 1.49063237, 1.48867280, 1.48671291, 1.48475270, 1.48279215, 1.48083127, 1.47887004,
	1.47690845, 1.47494650, 1.47298419, 1.47102149, 1.46905841, 1.46709493, 1.46513106, 1.46316677,
	1.46120207, 1.45923694, 1.45727138, 1.45530538, 1.45333893, 1.45137203, 1.44940466, 1.44743682,
	1.44546850, 1.44349969, 1.44153038, 1.43956057, 1.43759024, 1.43561940, 1.43364803, 1.43167612,
	1.42970367, 1.42773066, 1.42575709, 1.42378296, 1.42180825, 1.41983295, 1.41785705, 1.41588056,
	1.41390346, 1.41192573, 1.40994738, 1.40796840, 1.40598877, 1.40400849, 1.40202755, 1.40004594,
	1.39806365, 1.39608068, 1.39409701, 1.39211264, 1.39012756, 1.38814175, 1.38615522, 1.38416795,
	1.38217994, 1.38019117, 1.37820164, 1.37621134, 1.37422025, 1.37222837, 1.37023570, 1.36824222,
	1.36624792, 1.36425280, 1.36225684, 1.36026004, 1.35826239, 1.35626387, 1.35426449, 1.35226422,
	1.35026307, 1.34826101, 1.34625805, 1.34425418, 1.34224937, 1.34024364, 1.33823695, 1.33622932,
	1.33422072, 1.33221114, 1.33020059, 1.32818904, 1.32617649, 1.32416292, 1.32214834, 1.32013273,
	1.31811607, 1.31609837, 1.31407960, 1.31205976, 1.31003885, 1.30801684, 1.30599373, 1.30396951,
	1.30194417, 1.29991770, 1.29789009, 1.29586133, 1.29383141, 1.29180031, 1.28976803, 1.28773456,
	1.28569989, 1.28366400, 1.28162688, 1.27958854, 1.27754894, 1.27550809, 1.27346597, 1.27142257,
	1.26937788, 1.26733189, 1.26528459, 1.26323597, 1.26118602, 1.25913471, 1.25708205, 1.25502803,
	1.25297262, 1.25091583, 1.24885763, 1.24679802, 1.24473698, 1.24267450, 1.24061058, 1.23854519,
	1.23647833, 1.23440999, 1.23234015, 1.23026880, 1.22819593, 1.22612152, 1.22404557, 1.22196806,
	1.21988898, 1.21780832, 1.21572606, 1.21364219, 1.21155670, 1.20946958, 1.20738080, 1.20529037,
	1.20319826, 1.20110447, 1.19900898, 1.19691177, 1.19481283, 1.19271216, 1.19060973, 1.18850553,
	1.18639955, 1.18429178, 1.18218219, 1.18007079, 1.17795754, 1.17584244, 1.17372548, 1.17160663,
	1.16948589, 1.16736324, 1.16523866, 1.16311215, 1.16098368, 1.15885323, 1.15672081, 1.15458638,
	1.15244994, 1.15031147, 1.14817095, 1.14602836, 1.14388370, 1.14173695, 1.13958808, 1.13743709,
	1.13528396, 1.13312866, 1.13097119, 1.12881153, 1.12664966, 1.12448556, 1.12231921, 1.12015061,
	1.11797973, 1.11580656, 1.11363107, 1.11145325, 1.10927308, 1.10709055, 1.10490563, 1.10271831,
	1.10052856, 1.09833638, 1.09614174, 1.09394462, 1.09174500, 1.08954287, 1.08733820, 1.08513098,
	1.08292118, 1.08070879, 1.07849378, 1.07627614, 1.07405585, 1.07183287, 1.06960721, 1.06737882,
	1.06514770, 1.06291382, 1.06067715, 1.05843769, 1.05619540, 1.05395026, 1.05170226, 1.04945136,
	1.04719755, 1.04494080, 1.04268110, 1.04041841, 1.03815271, 1.03588399, 1.03361221, 1.03133735,
	1.02905939, 1.02677830, 1.02449407, 1.02220665, 1.01991603, 1.01762219, 1.01532509, 1.01302471,
	1.01072102, 1.00841400, 1.00610363, 1.00378986, 1.00147268, 0.99915206, 0.99682798, 0.99450039,
	0.99216928, 0.98983461, 0.98749636, 0.98515449, 0.98280898, 0.98045980, 0.97810691, 0.97575030,
	0.97338991, 0.97102573, 0.96865772, 0.96628585, 0.96391009, 0.96153040, 0.95914675, 0.95675912,
	0.95436745, 0.95197173, 0.94957191, 0.94716796, 0.94475985, 0.94234754, 0.93993099, 0.93751017,
	0.93508504, 0.93265556, 0.93022170, 0.92778341, 0.92534066, 0.92289341, 0.92044161, 0.91798524,
	0.91552424, 0.91305858, 0.91058821, 0.90811309, 0.90563319, 0.90314845, 0.90065884, 0.89816430,
	0.89566479, 0.89316028, 0.89065070, 0.88813602, 0.88561619, 0.88309116, 0.88056088, 0.87802531,
	0.87548438, 0.87293806, 0.87038629, 0.86782901, 0.86526619, 0.86269775, 0.86012366, 0.85754385,
	0.85495827, 0.85236686, 0.84976956, 0.84716633, 0.84455709, 0.84194179, 0.83932037, 0.83669277,
	0.83405893, 0.83141877, 0.82877225, 0.82611928, 0.82345981, 0.82079378, 0.81812110, 0.81544172,
	0.81275556, 0.81006255, 0.80736262, 0.80465570, 0.80194171, 0.79922057, 0.79649221, 0.79375655,
	0.79101352, 0.78826302, 0.78550497, 0.78273931, 0.77996593, 0.77718475, 0.77439569, 0.77159865,
	0.76879355, 0.76598029, 0.76315878, 0.76032891, 0.75749061, 0.75464376, 0.75178826, 0.74892402,
	0.74605092, 0.74316887, 0.74027775, 0.73737744, 0.73446785, 0.73154885, 0.72862033, 0.72568217,
	0.72273425, 0.71977644, 0.71680861, 0.71383064, 0.71084240, 0.70784376, 0.70483456, 0.70181469,
	0.69878398, 0.69574231, 0.69268952, 0.68962545, 0.68654996, 0.68346288, 0.68036406, 0.67725332,
	0.67413051, 0.67099544, 0.66784794, 0.66468783, 0.66151492, 0.65832903, 0.65512997, 0.65191753,
	0.64869151, 0.64545170, 0.64219789, 0.63892987, 0.63564741, 0.63235028, 0.62903824, 0.62571106,
	0.62236849, 0.61901027, 0.61563615, 0.61224585, 0.60883911, 0.60541564, 0.60197515, 0.59851735,
	0.59504192, 0.59154856, 0.58803694, 0.58450672, 0.58095756, 0.57738911, 0.57380101, 0.57019288,
	0.56656433, 0.56291496, 0.55924437, 0.55555212, 0.55183778, 0.54810089, 0.54434099, 0.54055758,
	0.53675018, 0.53291825, 0.52906127, 0.52517867, 0.52126988, 0.51733431, 0.51337132, 0.50938028,
	0.50536051, 0.50131132, 0.49723200, 0.49312177, 0.48897987, 0.48480547, 0.48059772, 0.47635573,
	0.47207859, 0.46776530, 0.46341487, 0.45902623, 0.45459827, 0.45012983, 0.44561967, 0.44106652,
	0.43646903, 0.43182577, 0.42713525, 0.42239588, 0.41760600, 0.41276385, 0.40786755, 0.40291513,
	0.39790449, 0.39283339, 0.38769946, 0.38250016, 0.37723277, 0.37189441, 0.36648196, 0.36099209,
	0.35542120, 0.34976542, 0.34402054, 0.33818204, 0.33224495, 0.32620390, 0.32005298, 0.31378574,
	0.30739505, 0.30087304, 0.29421096, 0.28739907, 0.28042645, 0.27328078, 0.26594810, 0.25841250,
	0.25065566, 0.24265636, 0.23438976, 0.22582651, 0.21693146, 0.20766198, 0.19796546, 0.18777575,
	0.17700769, 0.16554844, 0.15324301, 0.13986823, 0.12508152, 0.10830610, 0.08841715, 0.06251018,
};
*/
float G_acostable[] =
{
	3.1415927410125732f, 3.0790824890136719f, 3.0531754493713379f, 3.0332865715026855f,
	3.0165112018585205f, 3.0017244815826416f, 2.9883496761322021f, 2.9760441780090332f,
	2.9645850658416748f, 2.9538168907165527f, 2.9436271190643311f, 2.9339306354522705f,
	2.9246611595153809f, 2.9157662391662598f, 2.9072029590606689f, 2.8989362716674805f,
	2.8909370899200439f, 2.8831801414489746f, 2.8756444454193115f, 2.8683118820190430f,
	2.8611662387847900f, 2.8541936874389648f, 2.8473815917968750f, 2.8407196998596191f,
	2.8341975212097168f, 2.8278069496154785f, 2.8215396404266357f, 2.8153886795043945f,
	2.8093476295471191f, 2.8034105300903320f, 2.7975721359252930f, 2.7918272018432617f,
	2.7861714363098145f, 2.7806005477905273f, 2.7751107215881348f, 2.7696981430053711f,
	2.7643599510192871f, 2.7590925693511963f, 2.7538931369781494f, 2.7487592697143555f,
	2.7436881065368652f, 2.7386775016784668f, 2.7337250709533691f, 2.7288289070129395f,
	2.7239866256713867f, 2.7191967964172363f, 2.7144575119018555f, 2.7097668647766113f,
	2.7051236629486084f, 2.7005262374877930f, 2.6959729194641113f, 2.6914627552032471f,
	2.6869943141937256f, 2.6825664043426514f, 2.6781778335571289f, 2.6738274097442627f,
	2.6695141792297363f, 2.6652369499206543f, 2.6609950065612793f, 2.6567871570587158f,
	2.6526126861572266f, 2.6484708786010742f, 2.6443605422973633f, 2.6402814388275146f,
	2.6362321376800537f, 2.6322124004364014f, 2.6282212734222412f, 2.6242582798004150f,
	2.6203227043151855f, 2.6164140701293945f, 2.6125314235687256f, 2.6086742877960205f,
	2.6048424243927002f, 2.6010351181030273f, 2.5972516536712646f, 2.5934917926788330f,
	2.5897548198699951f, 2.5860404968261719f, 2.5823483467102051f, 2.5786776542663574f,
	2.5750284194946289f, 2.5713996887207031f, 2.5677917003631592f, 2.5642035007476807f,
	2.5606350898742676f, 2.5570859909057617f, 2.5535557270050049f, 2.5500440597534180f,
	2.5465507507324219f, 2.5430753231048584f, 2.5396175384521484f, 2.5361769199371338f,
	2.5327534675598145f, 2.5293467044830322f, 2.5259563922882080f, 2.5225822925567627f,
	2.5192241668701172f, 2.5158815383911133f, 2.5125544071197510f, 2.5092422962188721f,
	2.5059452056884766f, 2.5026628971099854f, 2.4993946552276611f, 2.4961409568786621f,
	2.4929010868072510f, 2.4896750450134277f, 2.4864625930786133f, 2.4832637310028076f,
	2.4800777435302734f, 2.4769048690795898f, 2.4737446308135986f, 2.4705972671508789f,
	2.4674620628356934f, 2.4643392562866211f, 2.4612286090850830f, 2.4581298828125000f,
	2.4550426006317139f, 2.4519672393798828f, 2.4489030838012695f, 2.4458503723144531f,
	2.4428086280822754f, 2.4397778511047363f, 2.4367580413818359f, 2.4337489604949951f,
	2.4307501316070557f, 2.4277620315551758f, 2.4247839450836182f, 2.4218161106109619f,
	2.4188582897186279f, 2.4159104824066162f, 2.4129722118377686f, 2.4100437164306641f,
	2.4071247577667236f, 2.4042150974273682f, 2.4013149738311768f, 2.3984236717224121f,
	2.3955416679382324f, 2.3926687240600586f, 2.3898043632507324f, 2.3869488239288330f,
	2.3841021060943604f, 2.3812637329101562f, 2.3784339427947998f, 2.3756122589111328f,
	2.3727991580963135f, 2.3699939250946045f, 2.3671970367431641f, 2.3644080162048340f,
	2.3616266250610352f, 2.3588533401489258f, 2.3560876846313477f, 2.3533296585083008f,
	2.3505790233612061f, 2.3478360176086426f, 2.3451004028320312f, 2.3423721790313721f,
	2.3396508693695068f, 2.3369369506835937f, 2.3342299461364746f, 2.3315300941467285f,
	2.3288371562957764f, 2.3261508941650391f, 2.3234715461730957f, 2.3207988739013672f,
	2.3181328773498535f, 2.3154733180999756f, 2.3128204345703125f, 2.3101739883422852f,
	2.3075337409973145f, 2.3048999309539795f, 2.3022723197937012f, 2.2996509075164795f,
	2.2970354557037354f, 2.2944264411926270f, 2.2918231487274170f, 2.2892258167266846f,
	2.2866344451904297f, 2.2840487957000732f, 2.2814691066741943f, 2.2788949012756348f,
	2.2763264179229736f, 2.2737636566162109f, 2.2712063789367676f, 2.2686545848846436f,
	2.2661082744598389f, 2.2635674476623535f, 2.2610318660736084f, 2.2585015296936035f,
	2.2559764385223389f, 2.2534565925598145f, 2.2509419918060303f, 2.2484323978424072f,
	2.2459278106689453f, 2.2434284687042236f, 2.2409338951110840f, 2.2384440898895264f,
	2.2359595298767090f, 2.2334794998168945f, 2.2310044765472412f, 2.2285339832305908f,
	2.2260684967041016f, 2.2236073017120361f, 2.2211511135101318f, 2.2186992168426514f,
	2.2162520885467529f, 2.2138092517852783f, 2.2113709449768066f, 2.2089371681213379f,
	2.2065076828002930f, 2.2040824890136719f, 2.2016615867614746f, 2.1992452144622803f,
	2.1968328952789307f, 2.1944246292114258f, 2.1920206546783447f, 2.1896209716796875f,
	2.1872251033782959f, 2.1848335266113281f, 2.1824460029602051f, 2.1800622940063477f,
	2.1776826381683350f, 2.1753067970275879f, 2.1729350090026855f, 2.1705670356750488f,
	2.1682026386260986f, 2.1658422946929932f, 2.1634857654571533f, 2.1611328125000000f,
	2.1587836742401123f, 2.1564381122589111f, 2.1540963649749756f, 2.1517579555511475f,
	2.1494233608245850f, 2.1470923423767090f, 2.1447646617889404f, 2.1424405574798584f,
	2.1401200294494629f, 2.1378028392791748f, 2.1354889869689941f, 2.1331787109375000f,
	2.1308715343475342f, 2.1285679340362549f, 2.1262676715850830f, 2.1239705085754395f,
	2.1216766834259033f, 2.1193859577178955f, 2.1170985698699951f, 2.1148142814636230f,
	2.1125333309173584f, 2.1102552413940430f, 2.1079804897308350f, 2.1057085990905762f,
	2.1034400463104248f, 2.1011743545532227f, 2.0989115238189697f, 2.0966517925262451f,
	2.0943951606750488f, 2.0921413898468018f, 2.0898904800415039f, 2.0876424312591553f,
	2.0853972434997559f, 2.0831549167633057f, 2.0809154510498047f, 2.0786788463592529f,
	2.0764448642730713f, 2.0742137432098389f, 2.0719854831695557f, 2.0697598457336426f,
	2.0675368309020996f, 2.0653164386749268f, 2.0630989074707031f, 2.0608837604522705f,
	2.0586714744567871f, 2.0564615726470947f, 2.0542545318603516f, 2.0520498752593994f,
	2.0498476028442383f, 2.0476479530334473f, 2.0454509258270264f, 2.0432562828063965f,
	2.0410640239715576f, 2.0388743877410889f, 2.0366871356964111f, 2.0345020294189453f,
	2.0323195457458496f, 2.0301394462585449f, 2.0279614925384521f, 2.0257861614227295f,
	2.0236129760742187f, 2.0214419364929199f, 2.0192735195159912f, 2.0171070098876953f,
	2.0149428844451904f, 2.0127811431884766f, 2.0106215476989746f, 2.0084640979766846f,
	2.0063087940216064f, 2.0041556358337402f, 2.0020046234130859f, 1.9998557567596436f,
	1.9977089166641235f, 1.9955643415451050f, 1.9934216737747192f, 1.9912811517715454f,
	1.9891426563262939f, 1.9870063066482544f, 1.9848718643188477f, 1.9827394485473633f,
	1.9806089401245117f, 1.9784804582595825f, 1.9763540029525757f, 1.9742294549942017f,
	1.9721068143844604f, 1.9699860811233521f, 1.9678671360015869f, 1.9657502174377441f,
	1.9636350870132446f, 1.9615218639373779f, 1.9594104290008545f, 1.9573009014129639f,
	1.9551930427551270f, 1.9530870914459229f, 1.9509829282760620f, 1.9488805532455444f,
	1.9467798471450806f, 1.9446809291839600f, 1.9425836801528931f, 1.9404882192611694f,
	1.9383944272994995f, 1.9363023042678833f, 1.9342118501663208f, 1.9321230649948120f,
	1.9300359487533569f, 1.9279505014419556f, 1.9258666038513184f, 1.9237843751907349f,
	1.9217036962509155f, 1.9196245670318604f, 1.9175471067428589f, 1.9154710769653320f,
	1.9133967161178589f, 1.9113239049911499f, 1.9092525243759155f, 1.9071826934814453f,
	1.9051142930984497f, 1.9030474424362183f, 1.9009820222854614f, 1.8989181518554688f,
	1.8968557119369507f, 1.8947945833206177f, 1.8927350044250488f, 1.8906768560409546f,
	1.8886200189590454f, 1.8865646123886108f, 1.8845106363296509f, 1.8824579715728760f,
	1.8804066181182861f, 1.8783566951751709f, 1.8763080835342407f, 1.8742607831954956f,
	1.8722147941589355f, 1.8701701164245605f, 1.8681266307830811f, 1.8660845756530762f,
	1.8640437126159668f, 1.8620041608810425f, 1.8599658012390137f, 1.8579286336898804f,
	1.8558927774429321f, 1.8538581132888794f, 1.8518246412277222f, 1.8497923612594604f,
	1.8477612733840942f, 1.8457313776016235f, 1.8437025547027588f, 1.8416749238967896f,
	1.8396484851837158f, 1.8376231193542480f, 1.8355989456176758f, 1.8335758447647095f,
	1.8315538167953491f, 1.8295328617095947f, 1.8275130987167358f, 1.8254942893981934f,
	1.8234765529632568f, 1.8214598894119263f, 1.8194442987442017f, 1.8174297809600830f,
	1.8154162168502808f, 1.8134036064147949f, 1.8113920688629150f, 1.8093814849853516f,
	1.8073719739913940f, 1.8053632974624634f, 1.8033556938171387f, 1.8013490438461304f,
	1.7993432283401489f, 1.7973384857177734f, 1.7953345775604248f, 1.7933316230773926f,
	1.7913296222686768f, 1.7893284559249878f, 1.7873281240463257f, 1.7853287458419800f,
	1.7833303213119507f, 1.7813326120376587f, 1.7793358564376831f, 1.7773398160934448f,
	1.7753447294235229f, 1.7733504772186279f, 1.7713569402694702f, 1.7693642377853394f,
	1.7673723697662354f, 1.7653813362121582f, 1.7633910179138184f, 1.7614015340805054f,
	1.7594127655029297f, 1.7574247121810913f, 1.7554373741149902f, 1.7534508705139160f,
	1.7514650821685791f, 1.7494800090789795f, 1.7474956512451172f, 1.7455120086669922f,
	1.7435289621353149f, 1.7415467500686646f, 1.7395651340484619f, 1.7375841140747070f,
	1.7356039285659790f, 1.7336242198944092f, 1.7316452264785767f, 1.7296669483184814f,
	1.7276891469955444f, 1.7257120609283447f, 1.7237355709075928f, 1.7217596769332886f,
	1.7197843790054321f, 1.7178096771240234f, 1.7158355712890625f, 1.7138619422912598f,
	1.7118890285491943f, 1.7099165916442871f, 1.7079446315765381f, 1.7059732675552368f,
	1.7040023803710937f, 1.7020320892333984f, 1.7000622749328613f, 1.6980929374694824f,
	1.6961241960525513f, 1.6941558122634888f, 1.6921880245208740f, 1.6902205944061279f,
	1.6882537603378296f, 1.6862872838973999f, 1.6843212842941284f, 1.6823557615280151f,
	1.6803905963897705f, 1.6784259080886841f, 1.6764615774154663f, 1.6744977235794067f,
	1.6725342273712158f, 1.6705712080001831f, 1.6686084270477295f, 1.6666461229324341f,
	1.6646841764450073f, 1.6627225875854492f, 1.6607613563537598f, 1.6588004827499390f,
	1.6568399667739868f, 1.6548796892166138f, 1.6529198884963989f, 1.6509603261947632f,
	1.6490010023117065f, 1.6470420360565186f, 1.6450834274291992f, 1.6431250572204590f,
	1.6411669254302979f, 1.6392090320587158f, 1.6372514963150024f, 1.6352941989898682f,
	1.6333371400833130f, 1.6313802003860474f, 1.6294236183166504f, 1.6274672746658325f,
	1.6255111694335937f, 1.6235551834106445f, 1.6215994358062744f, 1.6196439266204834f,
	1.6176885366439819f, 1.6157332658767700f, 1.6137783527374268f, 1.6118234395980835f,
	1.6098687648773193f, 1.6079142093658447f, 1.6059597730636597f, 1.6040055751800537f,
	1.6020513772964478f, 1.6000974178314209f, 1.5981434583663940f, 1.5961897373199463f,
	1.5942360162734985f, 1.5922824144363403f, 1.5903288125991821f, 1.5883753299713135f,
	1.5864219665527344f, 1.5844686031341553f, 1.5825153589248657f, 1.5805621147155762f,
	1.5786088705062866f, 1.5766557455062866f, 1.5747026205062866f, 1.5727494955062866f,
	1.5707963705062866f, 1.5688432455062866f, 1.5668901205062866f, 1.5649368762969971f,
	1.5629837512969971f, 1.5610305070877075f, 1.5590772628784180f, 1.5571240186691284f,
	1.5551706552505493f, 1.5532172918319702f, 1.5512638092041016f, 1.5493103265762329f,
	1.5473567247390747f, 1.5454030036926270f, 1.5434491634368896f, 1.5414952039718628f,
	1.5395412445068359f, 1.5375870466232300f, 1.5356328487396240f, 1.5336784124374390f,
	1.5317238569259644f, 1.5297691822052002f, 1.5278143882751465f, 1.5258593559265137f,
	1.5239040851593018f, 1.5219488143920898f, 1.5199931859970093f, 1.5180374383926392f,
	1.5160815715789795f, 1.5141253471374512f, 1.5121690034866333f, 1.5102124214172363f,
	1.5082556009292603f, 1.5062985420227051f, 1.5043411254882812f, 1.5023835897445679f,
	1.5004258155822754f, 1.4984676837921143f, 1.4965093135833740f, 1.4945505857467651f,
	1.4925916194915771f, 1.4906324148178101f, 1.4886728525161743f, 1.4867129325866699f,
	1.4847526550292969f, 1.4827921390533447f, 1.4808312654495239f, 1.4788700342178345f,
	1.4769084453582764f, 1.4749464988708496f, 1.4729841947555542f, 1.4710215330123901f,
	1.4690583944320679f, 1.4670948982238770f, 1.4651310443878174f, 1.4631667137145996f,
	1.4612020254135132f, 1.4592369794845581f, 1.4572713375091553f, 1.4553053379058838f,
	1.4533389806747437f, 1.4513720273971558f, 1.4494047164916992f, 1.4474368095397949f,
	1.4454685449600220f, 1.4434996843338013f, 1.4415303468704224f, 1.4395605325698853f,
	1.4375902414321899f, 1.4356193542480469f, 1.4336479902267456f, 1.4316761493682861f,
	1.4297037124633789f, 1.4277306795120239f, 1.4257570505142212f, 1.4237829446792603f,
	1.4218082427978516f, 1.4198329448699951f, 1.4178570508956909f, 1.4158805608749390f,
	1.4139034748077393f, 1.4119256734848022f, 1.4099473953247070f, 1.4079684019088745f,
	1.4059888124465942f, 1.4040085077285767f, 1.4020274877548218f, 1.4000459909439087f,
	1.3980636596679687f, 1.3960807323455811f, 1.3940969705581665f, 1.3921126127243042f,
	1.3901275396347046f, 1.3881417512893677f, 1.3861552476882935f, 1.3841679096221924f,
	1.3821799755096436f, 1.3801912069320679f, 1.3782016038894653f, 1.3762112855911255f,
	1.3742202520370483f, 1.3722283840179443f, 1.3702356815338135f, 1.3682422637939453f,
	1.3662478923797607f, 1.3642528057098389f, 1.3622568845748901f, 1.3602600097656250f,
	1.3582624197006226f, 1.3562638759613037f, 1.3542644977569580f, 1.3522641658782959f,
	1.3502631187438965f, 1.3482609987258911f, 1.3462580442428589f, 1.3442541360855103f,
	1.3422493934631348f, 1.3402435779571533f, 1.3382369279861450f, 1.3362293243408203f,
	1.3342207670211792f, 1.3322111368179321f, 1.3302005529403687f, 1.3281890153884888f,
	1.3261765241622925f, 1.3241629600524902f, 1.3221483230590820f, 1.3201327323913574f,
	1.3181160688400269f, 1.3160983324050903f, 1.3140796422958374f, 1.3120597600936890f,
	1.3100388050079346f, 1.3080168962478638f, 1.3059936761856079f, 1.3039695024490356f,
	1.3019441366195679f, 1.2999176979064941f, 1.2978900671005249f, 1.2958613634109497f,
	1.2938313484191895f, 1.2918002605438232f, 1.2897679805755615f, 1.2877345085144043f,
	1.2856998443603516f, 1.2836639881134033f, 1.2816269397735596f, 1.2795885801315308f,
	1.2775489091873169f, 1.2755080461502075f, 1.2734659910202026f, 1.2714226245880127f,
	1.2693778276443481f, 1.2673318386077881f, 1.2652845382690430f, 1.2632359266281128f,
	1.2611860036849976f, 1.2591347694396973f, 1.2570821046829224f, 1.2550280094146729f,
	1.2529726028442383f, 1.2509158849716187f, 1.2488576173782349f, 1.2467980384826660f,
	1.2447370290756226f, 1.2426744699478149f, 1.2406105995178223f, 1.2385451793670654f,
	1.2364783287048340f, 1.2344100475311279f, 1.2323400974273682f, 1.2302688360214233f,
	1.2281959056854248f, 1.2261215448379517f, 1.2240455150604248f, 1.2219680547714233f,
	1.2198889255523682f, 1.2178083658218384f, 1.2157260179519653f, 1.2136422395706177f,
	1.2115566730499268f, 1.2094695568084717f, 1.2073807716369629f, 1.2052903175354004f,
	1.2031983137130737f, 1.2011045217514038f, 1.1990089416503906f, 1.1969118118286133f,
	1.1948127746582031f, 1.1927121877670288f, 1.1906096935272217f, 1.1885055303573608f,
	1.1863995790481567f, 1.1842917203903198f, 1.1821821928024292f, 1.1800707578659058f,
	1.1779575347900391f, 1.1758424043655396f, 1.1737254858016968f, 1.1716066598892212f,
	1.1694859266281128f, 1.1673632860183716f, 1.1652386188507080f, 1.1631121635437012f,
	1.1609836816787720f, 1.1588532924652100f, 1.1567207574844360f, 1.1545864343643188f,
	1.1524499654769897f, 1.1503114700317383f, 1.1481709480285645f, 1.1460283994674683f,
	1.1438837051391602f, 1.1417369842529297f, 1.1395881175994873f, 1.1374371051788330f,
	1.1352839469909668f, 1.1331286430358887f, 1.1309711933135986f, 1.1288114786148071f,
	1.1266496181488037f, 1.1244856119155884f, 1.1223192214965820f, 1.1201505661010742f,
	1.1179797649383545f, 1.1158065795898437f, 1.1136310100555420f, 1.1114532947540283f,
	1.1092730760574341f, 1.1070905923843384f, 1.1049056053161621f, 1.1027183532714844f,
	1.1005285978317261f, 1.0983363389968872f, 1.0961416959762573f, 1.0939446687698364f,
	1.0917450189590454f, 1.0895428657531738f, 1.0873382091522217f, 1.0851309299468994f,
	1.0829211473464966f, 1.0807087421417236f, 1.0784938335418701f, 1.0762761831283569f,
	1.0740557909011841f, 1.0718328952789307f, 1.0696072578430176f, 1.0673788785934448f,
	1.0651477575302124f, 1.0629137754440308f, 1.0606771707534790f, 1.0584377050399780f,
	1.0561953783035278f, 1.0539503097534180f, 1.0517022609710693f, 1.0494513511657715f,
	1.0471975803375244f, 1.0449408292770386f, 1.0426810979843140f, 1.0404183864593506f,
	1.0381526947021484f, 1.0358840227127075f, 1.0336122512817383f, 1.0313373804092407f,
	1.0290594100952148f, 1.0267783403396606f, 1.0244940519332886f, 1.0222066640853882f,
	1.0199160575866699f, 1.0176222324371338f, 1.0153250694274902f, 1.0130246877670288f,
	1.0107209682464600f, 1.0084140300750732f, 1.0061036348342896f, 1.0037899017333984f,
	1.0014727115631104f, 0.9991520643234253f, 0.9968279600143433f, 0.9945003986358643f,
	0.9921692609786987f, 0.9898346066474915f, 0.9874963760375977f, 0.9851545095443726f,
	0.9828090071678162f, 0.9804598093032837f, 0.9781069159507752f, 0.9757502675056458f,
	0.9733899235725403f, 0.9710257053375244f, 0.9686577320098877f, 0.9662858247756958f,
	0.9639101028442383f, 0.9615303874015808f, 0.9591467380523682f, 0.9567590951919556f,
	0.9543674588203430f, 0.9519717097282410f, 0.9495719075202942f, 0.9471679925918579f,
	0.9447598457336426f, 0.9423475265502930f, 0.9399309754371643f, 0.9375101923942566f,
	0.9350850582122803f, 0.9326555728912354f, 0.9302216768264771f, 0.9277834296226502f,
	0.9253406524658203f, 0.9228934049606323f, 0.9204416275024414f, 0.9179852604866028f,
	0.9155242443084717f, 0.9130585789680481f, 0.9105882048606873f, 0.9081131219863892f,
	0.9056332111358643f, 0.9031484723091126f, 0.9006588459014893f, 0.8981642723083496f,
	0.8956648111343384f, 0.8931602835655212f, 0.8906506896018982f, 0.8881360292434692f,
	0.8856161832809448f, 0.8830911517143250f, 0.8805608749389648f, 0.8780252933502197f,
	0.8754844069480896f, 0.8729380369186401f, 0.8703863024711609f, 0.8678290247917175f,
	0.8652662038803101f, 0.8626977801322937f, 0.8601236343383789f, 0.8575438261032105f,
	0.8549582958221436f, 0.8523668646812439f, 0.8497695922851563f, 0.8471662998199463f,
	0.8445571064949036f, 0.8419417738914490f, 0.8393203616142273f, 0.8366927504539490f,
	0.8340589404106140f, 0.8314187526702881f, 0.8287722468376160f, 0.8261193037033081f,
	0.8234598040580750f, 0.8207938075065613f, 0.8181210756301880f, 0.8154417276382446f,
	0.8127555847167969f, 0.8100625276565552f, 0.8073626160621643f, 0.8046557307243347f,
	0.8019416928291321f, 0.7992205619812012f, 0.7964922189712524f, 0.7937565445899963f,
	0.7910135388374329f, 0.7882630228996277f, 0.7855049967765808f, 0.7827392816543579f,
	0.7799659371376038f, 0.7771847248077393f, 0.7743957042694092f, 0.7715986371040344f,
	0.7687935233116150f, 0.7659803032875061f, 0.7631587982177734f, 0.7603288888931274f,
	0.7574906349182129f, 0.7546437382698059f, 0.7517882585525513f, 0.7489240169525147f,
	0.7460508942604065f, 0.7431688904762268f, 0.7402777671813965f, 0.7373774647712708f,
	0.7344678640365601f, 0.7315488457679749f, 0.7286203503608704f, 0.7256821990013123f,
	0.7227342724800110f, 0.7197764515876770f, 0.7168086171150208f, 0.7138306498527527f,
	0.7108424305915833f, 0.7078437805175781f, 0.7048345804214478f, 0.7018147110939026f,
	0.6987839937210083f, 0.6957423090934753f, 0.6926895380020142f, 0.6896254420280457f,
	0.6865499615669251f, 0.6834628582000732f, 0.6803640723228455f, 0.6772533059120178f,
	0.6741304993629456f, 0.6709954142570496f, 0.6678479313850403f, 0.6646878123283386f,
	0.6615149378776550f, 0.6583290100097656f, 0.6551299691200256f, 0.6519175171852112f,
	0.6486915349960327f, 0.6454517245292664f, 0.6421979069709778f, 0.6389298439025879f,
	0.6356474161148071f, 0.6323502659797669f, 0.6290382146835327f, 0.6257110834121704f,
	0.6223685145378113f, 0.6190102696418762f, 0.6156361699104309f, 0.6122458577156067f,
	0.6088390946388245f, 0.6054156422615051f, 0.6019751429557800f, 0.5985173583030701f,
	0.5950419306755066f, 0.5915485620498657f, 0.5880369544029236f, 0.5845066905021668f,
	0.5809575319290161f, 0.5773891210556030f, 0.5738010406494141f, 0.5701928734779358f,
	0.5665643215179443f, 0.5629149675369263f, 0.5592443943023682f, 0.5555521249771118f,
	0.5518378019332886f, 0.5481008887290955f, 0.5443409681320190f, 0.5405575633049011f,
	0.5367501974105835f, 0.5329182744026184f, 0.5290612578392029f, 0.5251786708831787f,
	0.5212698578834534f, 0.5173342823982239f, 0.5133713483810425f, 0.5093802809715271f,
	0.5053604841232300f, 0.5013113021850586f, 0.4972319900989533f, 0.4931217730045319f,
	0.4889798760414124f, 0.4848054647445679f, 0.4805977046489716f, 0.4763557314872742f,
	0.4720785915851593f, 0.4677653014659882f, 0.4634148776531220f, 0.4590262174606323f,
	0.4545982778072357f, 0.4501298367977142f, 0.4456196725368500f, 0.4410665333271027f,
	0.4364690184593201f, 0.4318257570266724f, 0.4271352589130402f, 0.4223958849906921f,
	0.4176059961318970f, 0.4127638638019562f, 0.4078675508499146f, 0.4029151201248169f,
	0.3979044854640961f, 0.3928333818912506f, 0.3876994550228119f, 0.3825001418590546f,
	0.3772327601909638f, 0.3718944191932678f, 0.3664819598197937f, 0.3609921038150787f,
	0.3554212152957916f, 0.3497654199600220f, 0.3440205454826355f, 0.3381820321083069f,
	0.3322449624538422f, 0.3262038826942444f, 0.3200529813766480f, 0.3137857317924500f,
	0.3073950409889221f, 0.3008730411529541f, 0.2942109704017639f, 0.2873990833759308f,
	0.2804264426231384f, 0.2732807695865631f, 0.2659481167793274f, 0.2584125101566315f,
	0.2506556510925293f, 0.2426563650369644f, 0.2343897670507431f, 0.2258265018463135f,
	0.2169314622879028f, 0.2076619714498520f, 0.1979654580354691f, 0.1877757459878922f,
	0.1770076900720596f, 0.1655484437942505f, 0.1532430052757263f, 0.1398682296276093f,
	0.1250815242528915f, 0.1083061024546623f, 0.0884171426296234f, 0.0625101774930954f
};

double G_acos(double x) {
	int index;

	if (x < -1)
		x = -1;
	if (x > 1)
		x = 1;
	index = (float) (1.0 + x) * 511.9;
	return G_acostable[index];
}
