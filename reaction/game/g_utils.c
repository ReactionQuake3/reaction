//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
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
	0.17700769, 0.16554844, 0.15324301, 0.13986823, 0.12508152, 0.10830610, 0.08841715, 0.06251018, };

//Makro - added missing ";"
double G_acos(double x) {
	int index;

	if (x < -1)
		x = -1;
	if (x > 1)
		x = 1;
	index = (float) (1.0 + x) * 511.9;
	return G_acostable[index];
}
