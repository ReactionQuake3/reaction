//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.81  2003/09/19 21:25:10  makro
// Flares (again!). Doors that open away from players.
//
// Revision 1.80  2003/09/19 00:53:14  makro
// Flares again
//
// Revision 1.79  2003/09/18 19:08:40  makro
// Lens flares
//
// Revision 1.78  2003/09/18 00:05:05  makro
// Lens flares. Opendoor trigger_multiple fixes
//
// Revision 1.77  2003/09/10 22:46:05  makro
// Cooler breath puffs. Locked r_fastSky on maps with global fog.
// Some other things I can't remember.
//
// Revision 1.76  2003/09/08 19:19:19  makro
// New code for respawning entities in TP
//
// Revision 1.75  2003/09/07 20:02:51  makro
// no message
//
// Revision 1.74  2003/08/31 14:48:33  jbravo
// Code not compiling under linux fixed and a warning silenced.
//
// Revision 1.73  2003/08/10 20:13:26  makro
// no message
//
// Revision 1.72  2003/07/30 16:05:46  makro
// no message
//
// Revision 1.71  2003/04/26 22:33:06  jbravo
// Wratted all calls to G_FreeEnt() to avoid crashing and provide debugging
//
// Revision 1.70  2003/04/19 15:27:31  jbravo
// Backing out of most of unlagged.  Only optimized prediction and smooth clients
// remains.
//
// Revision 1.69  2003/04/03 17:18:25  makro
// dlights
//
// Revision 1.68  2003/03/29 16:01:36  jbravo
// _skin cvars now fully removed. dlight code from Makro added. cvar
// defaults fixed.
//
// Revision 1.67  2003/03/22 20:29:26  jbravo
// wrapping linkent and unlinkent calls
//
// Revision 1.66  2003/03/09 21:30:38  jbravo
// Adding unlagged.   Still needs work.
//
// Revision 1.65  2003/02/27 19:52:34  makro
// dlights
//
// Revision 1.64  2003/02/13 21:19:50  makro
// no message
//
// Revision 1.63  2003/01/11 17:42:18  makro
// Fixed a bug in the sky portal code
//
// Revision 1.62  2002/08/30 00:00:16  makro
// Sky portals
//
// Revision 1.61  2002/08/25 07:07:42  niceass
// added "life" setting to func_pressure
//
// Revision 1.60  2002/08/21 02:56:08  blaze
// added spawnflags 8 for breakables, lets mappers turn off kicking
//
// Revision 1.59  2002/07/13 22:43:59  makro
// Semi-working fog hull, semi-working sky portals (cgame code commented out)
// Basically, semi-working stuff :P
//
// Revision 1.58  2002/06/18 09:21:11  niceass
// file exist function
//
// Revision 1.57  2002/06/16 20:06:14  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.56  2002/06/16 17:38:00  jbravo
// Removed the MISSIONPACK ifdefs and missionpack only code.
//
// Revision 1.55  2002/06/09 05:16:58  niceass
// pressure change
//
// Revision 1.54  2002/06/05 23:39:40  blaze
// unbreakables work properly.  Though I already commited this.
//
// Revision 1.53  2002/06/03 00:40:25  blaze
// some more breakables fixes(ssg chips)
//
// Revision 1.52  2002/06/02 22:04:38  blaze
// breakables act proper when triggered(explode if explosive, etc)  also, spawnflags 8 will make the breakable so you cant kick it
//
// Revision 1.51  2002/06/02 19:22:12  blaze
// my bad, breakables unlink when triggered now
//
// Revision 1.50  2002/05/30 21:18:28  makro
// Bots should reload/bandage when roaming around
// Added "pathtarget" key to all the entities
//
// Revision 1.49  2002/05/29 13:49:25  makro
// Elevators/doors
//
// Revision 1.48  2002/05/27 06:51:20  niceass
// pressure support for targets
//
// Revision 1.47  2002/05/26 05:16:56  niceass
// pressure
//
// Revision 1.46  2002/05/25 16:31:18  blaze
// moved breakable stuff over to config strings
//
// Revision 1.45  2002/05/23 18:37:50  makro
// Bots should crouch more often when they attack with a SSG
// Made this depend on skill. Also, elevator stuff
//
// Revision 1.44  2002/05/23 15:55:25  makro
// Elevators
//
// Revision 1.43  2002/05/23 04:53:41  blaze
// some func_breakable fixes.  Explosives respawn on new rounds now .
//
// Revision 1.42  2002/05/21 14:19:26  makro
// Printf's for misc_portal_surface setup errors
//
// Revision 1.41  2002/05/21 04:21:48  blaze
// changed buoyancy to lift as per Sze
//
// Revision 1.40  2002/05/20 16:25:48  makro
// Triggerable cameras
//
// Revision 1.39  2002/05/19 21:27:29  blaze
// added force and buoyancy to breakables
//
// Revision 1.38  2002/05/12 13:37:25  makro
// Bugs with entities
//
// Revision 1.37  2002/05/11 12:45:25  makro
// Spectators can go through breakables and doors with
// a targetname or health. Bots should crouch more/jump less
// often when attacking at long range
//
// Revision 1.36  2002/05/11 00:38:47  blaze
// trigger_push and target_push default to no noise when the noise flag is not set.
//
// Revision 1.35  2002/05/02 03:06:09  blaze
// Fixed breakables crashing on vashes
//
// Revision 1.34  2002/05/02 02:28:36  blaze
// Triggerable and targetable breakables
//
// Revision 1.33  2002/04/29 06:16:58  niceass
// small change to pressure system
//
// Revision 1.32  2002/04/23 06:01:58  niceass
// pressure stuff
//
// Revision 1.31  2002/04/22 16:43:34  blaze
// Hey look, breakables explode now!  :)
//
// Revision 1.30  2002/04/20 23:54:55  blaze
// opps, breabable fix
//
// Revision 1.29  2002/04/08 20:14:34  blaze
// func_breakable explode fix
//
// Revision 1.28  2002/04/05 06:50:25  blaze
// breakables should now respawn when the round restarts( when g_teamplay:SpawnPlayers() is called to be exact)
//
// Revision 1.27  2002/04/03 04:41:33  blaze
// woops, forgot one change in the breakable code
//
// Revision 1.26  2002/04/03 03:13:16  blaze
// NEW BREAKABLE CODE - will break all old breakables(wont appear in maps)
//
// Revision 1.25  2002/03/31 03:31:24  jbravo
// Compiler warning cleanups
//
// Revision 1.24  2002/03/20 22:58:54  blaze
// changed dlight to light_d
//
// Revision 1.23  2002/03/16 08:46:32  niceass
// spectator going through doors no longer reset viewangle
//
// Revision 1.22  2002/03/02 12:24:30  jbravo
// Removed some debugging messages
//
// Revision 1.21  2002/02/23 16:55:09  jbravo
// Added debugging to help find what was going with can't find item for weapon
// error that crash the server.
//
// Revision 1.20  2002/02/08 18:00:34  jbravo
// Fixing "No newline at end of file" Warnings Linux keeps giving me
//
// Revision 1.19  2002/01/14 01:20:45  niceass
// No more default 800 gravity on items
// Thrown knife+Glass fix - NiceAss
//
// Revision 1.18  2002/01/11 19:48:30  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.17  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
// g_misc.c

#include "g_local.h"

void G_ExplodeMissile(gentity_t * ent);

//Makro - added
void Think_SpawnNewDoorTrigger(gentity_t * ent);
void InitMover(gentity_t * ent);
void Use_Func_Train(gentity_t * ent, gentity_t * other, gentity_t * activator);
void Think_BeginMoving(gentity_t * ent);
void Reached_Train(gentity_t * ent);
void Think_SetupTrainTargets(gentity_t * ent);


/*QUAKED func_group (0 0 0) ?
Used to group brushes together just for editor convenience.  They are turned into normal brushes by the utilities.
*/

/*QUAKED info_camp (0 0.5 0) (-4 -4 -4) (4 4 4)
Used as a positional target for calculations in the utilities (spotlights, etc), but removed during gameplay.
*/
void SP_info_camp(gentity_t * self)
{
	G_SetOrigin(self, self->s.origin);
}

/*QUAKED info_null (0 0.5 0) (-4 -4 -4) (4 4 4)
Used as a positional target for calculations in the utilities (spotlights, etc), but removed during gameplay.
*/
void SP_info_null(gentity_t * self)
{
	G_FreeEntity(self, __LINE__, __FILE__);
}

/*QUAKED info_notnull (0 0.5 0) (-4 -4 -4) (4 4 4)
Used as a positional target for in-game calculation, like jumppad targets.
target_position does the same thing
*/
void SP_info_notnull(gentity_t * self)
{
	G_SetOrigin(self, self->s.origin);
}

/*QUAKED light (0 1 0) (-8 -8 -8) (8 8 8) linear
Non-displayed light.
"light" overrides the default 300 intensity.
Linear checbox gives linear falloff instead of inverse square
Lights pointed at a target will be spotlights.
"radius" overrides the default 64 unit radius of a spotlight at the target point.
*/
void SP_light(gentity_t * self)
{
	G_FreeEntity(self, __LINE__, __FILE__);
}

/*QUAKED light_d (0 1 0) (-8 -8 -8) (8 8 8) ADDITIVE FLICKER PULSE STROBE START_OFF
Dynamic light entity.  Use sparingly.
Q3 does not allow for manual light radius setup.
Set the color key for the intended color
"light" overrides the default 100 intensity.
*/
void use_dlight(gentity_t * ent, gentity_t * other, gentity_t * activator)
{
	//if train
	if (ent->count == 2) {
		if (other->pathtarget && other->pathtarget[0]) {
			Use_Func_Train(ent, other, activator);
			return;
		}
	}
	ent->unbreakable ^= 1;
	if (other)
		if (other->pathtarget)
			if (!Q_stricmp(other->pathtarget, "off"))
				ent->unbreakable = 0;
			else if (!Q_stricmp(other->pathtarget, "on"))
				ent->unbreakable = 1;

	if (ent->unbreakable) {
		ent->r.svFlags |= SVF_NOCLIENT;
		ent->s.eFlags |= EF_NODRAW;
	} else {
		ent->r.svFlags &= ~SVF_NOCLIENT;
		ent->s.eFlags &= ~EF_NODRAW;
	}
	//G_Printf("\nUsing dlight: %d\n\n", ent->unbreakable);
}

void reset_dlight(gentity_t *ent)
{
	ent->unbreakable = 0;
	if (ent->spawnflags & 8) {
		ent->unbreakable = 1;
		ent->use(ent, NULL, NULL);
	}
}

void SP_dlight(gentity_t * ent)
{
	vec3_t color;
	char *s;
	float light;
	int r, g, b, i;

	G_SpawnFloat("light", "300", &light);
	G_SpawnVector("_color", "1 1 1", color);

	// - set style bits in eventParm
	if (ent->spawnflags & 1)
		ent->s.eventParm |= DLIGHT_ADDITIVE;
	if (ent->spawnflags & 2)
		ent->s.eventParm |= DLIGHT_FLICKER;
	if (ent->spawnflags & 4)
		ent->s.eventParm |= DLIGHT_PULSE;

	r = color[0] * 255;
	if (r > 255) {
		r = 255;
	}
	g = color[1] * 255;
	if (g > 255) {
		g = 255;
	}
	b = color[2] * 255;
	if (b > 255) {
		b = 255;
	}
	i = light / 8;
	if (i > 255) {
		i = 255;
	}

	ent->s.constantLight = r | (g << 8) | (b << 16) | (i << 24);

	//Makro - added frequency, phase and light2
	G_SpawnFloat("frequency", "2", &light);
	ent->s.powerups = light * 1000;
	G_SpawnFloat("phase", "0", &light);
	ent->s.otherEntityNum2 = light * 1000;
	G_SpawnFloat("light2", "0", &light);
	ent->s.weapon = light;

	ent->s.pos.trType = TR_STATIONARY;
	VectorCopy(ent->s.origin, ent->r.currentOrigin);

	//Makro - added mover info
	if (G_SpawnString("movertype", "none", &s)) {
		if (!Q_stricmp(s, "bobbing")) {
			float height, heights[3];
			float phase2;
			int axis;

			//bobbing
			ent->count = 1;
			G_SpawnFloat("speed", "4", &ent->speed);
			G_SpawnFloat("height", "32", &height);
			G_SpawnFloat("moverphase", "0", &phase2);
			G_SpawnInt("axis", "2", &axis);
			InitMover(ent);
			VectorCopy(ent->s.origin, ent->s.pos.trBase);
			VectorCopy(ent->s.origin, ent->r.currentOrigin);
			ent->s.pos.trDuration = ent->speed * 1000;
			ent->s.pos.trTime = ent->s.pos.trDuration * phase2;
			ent->s.pos.trType = TR_SINE;
			// set the axis of bobbing
			if (G_SpawnVector("heights", "0 0 32", heights)) {
				VectorCopy(heights, ent->s.pos.trDelta);
			} else {
				ent->s.pos.trDelta[axis%3] = height;
			}
		} else if (!Q_stricmp(s, "train")) {
			//train
			ent->count = 2;
			VectorClear(ent->s.angles);
			if (!ent->speed) {
				ent->speed = 100;
			}
			if (!ent->target) {
				G_Printf("%s without a target at %s\n", ent->classname, vtos(ent->r.absmin));
				G_FreeEntity(ent, __LINE__, __FILE__);
				return;
			}
			InitMover(ent);
			ent->reached = Reached_Train;
			// start trains on the second frame, to make sure their targets have had
			// a chance to spawn
			ent->nextthink = level.time + FRAMETIME;
			ent->think = Think_SetupTrainTargets;
		}
	}
	ent->use = use_dlight;
	ent->reset = reset_dlight;
	//Makro - added START_OFF flag
	ent->unbreakable = 0;
	if (ent->spawnflags & 8) {
		ent->unbreakable = 1;
		ent->use(ent, NULL, NULL);
	}

	ent->s.eType = ET_DLIGHT;
	trap_RQ3LinkEntity(ent, __LINE__, __FILE__);
}

/*
// Nothing significant to do
void G_RunDlight(gentity_t * ent)
{
	trap_RQ3LinkEntity(ent, __LINE__, __FILE__);
}
*/


/*QUAKED misc_lens_flare (0 1 0) (-8 -8 -8) (8 8 8) ?
*/

void Think_SetupFlare(gentity_t *ent)
{
	char  info[MAX_INFO_STRING]={0};
	vec3_t dir;

	ent->think = 0;
	ent->nextthink = 0;
	if (ent->target) {
		ent->target_ent = G_PickTarget(ent->target);
		if (!ent->target_ent) {
			G_Printf(S_COLOR_YELLOW"Warning: misc_lens_flare with bad target at %s\n", vtos(ent->s.origin));
		} else {
			VectorSubtract(ent->s.origin, ent->target_ent->s.origin, dir);
		}
	} else {
		VectorCopy(ent->s.origin2, dir);
	}
	VectorNormalize(dir);
	trap_GetConfigstring(CS_SKYPORTAL, info, sizeof(info));

	Info_SetValueForKey(info, "ln", va("%d", ent->count));
	Info_SetValueForKey(info, "lx", va("%f", dir[0]));
	Info_SetValueForKey(info, "ly", va("%f", dir[1]));
	Info_SetValueForKey(info, "lz", va("%f", dir[2]));
	Info_SetValueForKey(info, "lamin", va("%f", ent->health/1000.0f));
	Info_SetValueForKey(info, "lamax", va("%f", ent->health_saved/1000.0f));
	Info_SetValueForKey(info, "lsmin", va("%d", ent->damage));
	Info_SetValueForKey(info, "lsmax", va("%d", ent->damage_radius));
	Info_SetValueForKey(info, "lsun", va("%d", ent->mass));
	Info_SetValueForKey(info, "lsa", va("%f", ent->speed));
	trap_SetConfigstring(CS_SKYPORTAL, info);
	
	G_FreeEntity(ent, __LINE__, __FILE__);
}

void SP_misc_lens_flare(gentity_t *ent)
{
	float f;
	if (ent->count < 0) {
		G_Printf(S_COLOR_YELLOW"Warning: misc_lens_flare with count <0 at %s\n", vtos(ent->s.origin));
		ent->count = 4;
	}
	G_SpawnInt("minsize", "16", &ent->damage);
	G_SpawnInt("maxsize", "128", &ent->damage_radius);

	G_SpawnFloat("alphamin", "0.5", &f);
	if (f > 1)
		f = 1;
	else if (f < 0)
		f = 0;
	ent->health = f * 1000;
	
	G_SpawnFloat("alphamax", "1", &f);
	if (f > 1)
		f = 1;
	else if (f < 0)
		f = 0;
	ent->health_saved = f * 1000;
	if (ent->health_saved < ent->health) {
		int tmp = ent->health_saved;
		ent->health_saved = ent->health;
		ent->health = tmp;
	}

	G_SpawnInt("sunsize", "0", &ent->mass);
	G_SpawnFloat("sunalpha", "0.5", &ent->speed);

	//this is so we can use the same values from
	if (!ent->target) {
		if (!G_SpawnVector("direction", "0 0 1", ent->s.origin2)) {
			AngleVectors(ent->s.angles, ent->s.origin2, NULL, NULL);
		}
	}

	ent->think = Think_SetupFlare;
	ent->nextthink = level.time + FRAMETIME;
}


/*QUAKED func_shadow (0 1 0) (-8 -8 -8) (8 8 8) ?
*/

void SP_func_shadow(gentity_t *ent)
{
	char info[MAX_INFO_STRING];
	//copied from InitTrigger	
	if (!VectorCompare(ent->s.angles, vec3_origin))
		G_SetMovedir(ent->s.angles, ent->movedir);

	trap_SetBrushModel(ent, ent->model);
	ent->r.contents = CONTENTS_TRIGGER;	// replaces the -1 from trap_SetBrushModel
	//ent->r.svFlags = SVF_NOCLIENT;
	ent->s.eFlags |= EF_NODRAW;

	Info_SetValueForKey(info, "num", "1");
	Info_SetValueForKey(info, "1", ent->pathtarget);
	trap_SetConfigstring(CS_SHADOWS, info);

	ent->s.eType = ET_SHADOW;
	trap_RQ3LinkEntity(ent, __LINE__, __FILE__);
}


/*
=================================================================================

TELEPORTERS

=================================================================================
*/

void TeleportPlayer(gentity_t * player, vec3_t origin, vec3_t angles)
{
	gentity_t *tent;

	// use temp events at source and destination to prevent the effect
	// from getting dropped by a second player event
	if (player->client->sess.sessionTeam != TEAM_SPECTATOR) {
		tent = G_TempEntity(player->client->ps.origin, EV_PLAYER_TELEPORT_OUT);
		tent->s.clientNum = player->s.clientNum;

		tent = G_TempEntity(origin, EV_PLAYER_TELEPORT_IN);
		tent->s.clientNum = player->s.clientNum;
	}
	// unlink to make sure it can't possibly interfere with G_KillBox
	trap_RQ3UnlinkEntity(player, __LINE__, __FILE__);

	VectorCopy(origin, player->client->ps.origin);
	player->client->ps.origin[2] += 1;

	// spit the player out
	// AngleVectors( angles, player->client->ps.velocity, NULL, NULL );
	// VectorScale( player->client->ps.velocity, 400, player->client->ps.velocity );
	player->client->ps.pm_time = 160;	// hold time
	player->client->ps.pm_flags |= PMF_TIME_KNOCKBACK;

	// toggle the teleport bit so the client knows to not lerp
	player->client->ps.eFlags ^= EF_TELEPORT_BIT;

	// JBravo: unlagged
	// G_ResetHistory(player);

	// set angles
	// SetClientViewAngle( player, angles );

	// kill anything at the destination
	if (player->client->sess.sessionTeam != TEAM_SPECTATOR) {
		G_KillBox(player);
	}
	// save results of pmove
	BG_PlayerStateToEntityState(&player->client->ps, &player->s, qtrue);

	// use the precise origin for linking
	VectorCopy(player->client->ps.origin, player->r.currentOrigin);

	if (player->client->sess.sessionTeam != TEAM_SPECTATOR) {
		trap_RQ3LinkEntity(player, __LINE__, __FILE__);
	}
}

/*QUAKED misc_teleporter_dest (1 0 0) (-32 -32 -24) (32 32 -16)
Point teleporters at these.
Now that we don't have teleport destination pads, this is just
an info_notnull
*/
void SP_misc_teleporter_dest(gentity_t * ent)
{
}

//===========================================================

/*QUAKED misc_model (1 0 0) (-16 -16 -16) (16 16 16)
"model"		arbitrary .md3 file to display
*/
void SP_misc_model(gentity_t * ent)
{

#if 0
	ent->s.modelindex = G_ModelIndex(ent->model);
	VectorSet(ent->mins, -16, -16, -16);
	VectorSet(ent->maxs, 16, 16, 16);
	trap_RQ3LinkEntity(ent, __LINE__, __FILE__);

	G_SetOrigin(ent, ent->s.origin);
	VectorCopy(ent->s.angles, ent->s.apos.trBase);
#else
	G_FreeEntity(ent, __LINE__, __FILE__);
#endif
}

//===========================================================

void locateCamera(gentity_t * ent)
{
	vec3_t dir;
	gentity_t *target;
	gentity_t *owner;

	if (ent->spawnflags & 1) {
		owner = G_Find(NULL, FOFS(targetname), va("%s%i", ent->target, ent->size + 1));
		ent->size = (ent->size + 1) % ent->count;
	} else {
		owner = G_PickTarget(ent->target);
	}
	if (!owner) {
		//Makro - fixed typo (misc_partal_surface)
		G_Printf("Couldn't find target for misc_portal_surface\n");
		G_FreeEntity(ent, __LINE__, __FILE__);
		return;
	}
	ent->r.ownerNum = owner->s.number;

	// frame holds the rotate speed
	if (owner->spawnflags & 1) {
		ent->s.frame = 25;
	} else if (owner->spawnflags & 2) {
		ent->s.frame = 75;
	}
	// swing camera ?
	if (owner->spawnflags & 4) {
		// set to 0 for no rotation at all
		ent->s.powerups = 0;
	} else {
		ent->s.powerups = 1;
	}

	// clientNum holds the rotate offset
	ent->s.clientNum = owner->s.clientNum;

	VectorCopy(owner->s.origin, ent->s.origin2);

	// see if the portal_camera has a target
	target = G_PickTarget(owner->target);
	if (target) {
		VectorSubtract(target->s.origin, owner->s.origin, dir);
		VectorNormalize(dir);
	} else {
		G_SetMovedir(owner->s.angles, dir);
	}

	ent->s.eventParm = DirToByte(dir);
}

void use_misc_portal_surface(gentity_t * ent, gentity_t * other, gentity_t * activator)
{
	locateCamera(ent);
}

/*QUAKED misc_portal_surface (0 0 1) (-8 -8 -8) (8 8 8) CYCLE
The portal surface nearest this entity will show a view from the targeted misc_portal_camera, or a mirror view if untargeted.
This must be within 64 world units of the surface!
*/
void SP_misc_portal_surface(gentity_t * ent)
{
	VectorClear(ent->r.mins);
	VectorClear(ent->r.maxs);
	trap_RQ3LinkEntity(ent, __LINE__, __FILE__);

	ent->r.svFlags = SVF_PORTAL;
	ent->s.eType = ET_PORTAL;

	//Makro - option to cycle through targets
	//size - current pos
	//count - max pos
	if (ent->spawnflags & 1) {
		if (!G_SpawnInt("count", "0", &ent->count)) {
			G_Printf("Cycling misc_portal_surface with no count at %s\n", vtos(ent->s.origin));
			ent->spawnflags--;
		} else {
			if (ent->count < 2) {
				G_Printf("Cycling misc_portal_surface with count < 2 at %s\n", vtos(ent->s.origin));
				ent->spawnflags--;
			} else {
				ent->size = 0;
				ent->use = use_misc_portal_surface;
			}
		}
	}

	if (!ent->target) {
		VectorCopy(ent->s.origin, ent->s.origin2);
	} else {
		ent->think = locateCamera;
		ent->nextthink = level.time + 100;
	}
}

/*QUAKED misc_portal_camera (0 0 1) (-8 -8 -8) (8 8 8) slowrotate fastrotate noswing
The target for a misc_portal_director.  You can set either angles or target another entity to determine the direction of view.
"roll" an angle modifier to orient the camera around the target vector;
*/
void SP_misc_portal_camera(gentity_t * ent)
{
	float roll;

	VectorClear(ent->r.mins);
	VectorClear(ent->r.maxs);
	trap_RQ3LinkEntity(ent, __LINE__, __FILE__);

	G_SpawnFloat("roll", "0", &roll);

	ent->s.clientNum = roll / 360.0 * 256;
}

//Makro - sky portals
void Think_SetupSkyPortal(gentity_t *ent)
{
	char  info[MAX_INFO_STRING]={0};
	qboolean isSet = qfalse;
	int n = 0;
	
	trap_GetConfigstring(CS_SKYPORTAL, info, sizeof(info));
	if (info[0]) {
		n = atoi(Info_ValueForKey(info, "n"));
		if (n)
			isSet = qtrue;
	}
	if (!isSet) {
		gentity_t *skyportal = G_Find(NULL, FOFS(targetname), ent->target);
	
		//G_Printf("^1 SKY PORTAL !!!\n");
		
		if (skyportal) {
			Info_SetValueForKey(info, "x", va("%f", skyportal->s.origin[0]));
			Info_SetValueForKey(info, "y", va("%f", skyportal->s.origin[1]));
			Info_SetValueForKey(info, "z", va("%f", skyportal->s.origin[2]));
			Info_SetValueForKey(info, "n", va("%i", skyportal->s.number));
			//G_Printf("Sky portal origin: %s\n", vtos(skyportal->s.origin));
			trap_SetConfigstring(CS_SKYPORTAL, info);
			VectorCopy(skyportal->s.origin, ent->s.origin2);
			ent->r.ownerNum = skyportal->s.number;
			//ent->s.eType = ET_PORTAL;
			//ent->r.svFlags |= SVF_BROADCAST;
		} else {
			G_Printf(S_COLOR_YELLOW "WARNING: misc_sky_portal entity with bad target at %s\n", vtos(ent->s.origin));
			G_FreeEntity(ent, __LINE__, __FILE__);
		}
	} else {
		ent->s.origin2[0] = atof(Info_ValueForKey(info, "x"));
		ent->s.origin2[1] = atof(Info_ValueForKey(info, "y"));
		ent->s.origin2[2] = atof(Info_ValueForKey(info, "z"));
		ent->r.ownerNum = n;
	}
	
	ent->nextthink = 0;
	ent->think = 0;
}

void SP_misc_sky_portal(gentity_t * ent)
{
	ent->r.svFlags |= SVF_PORTAL;
	VectorClear(ent->r.mins);
	VectorClear(ent->r.maxs);
	ent->think = Think_SetupSkyPortal;
	ent->nextthink = level.time + FRAMETIME;

	trap_RQ3LinkEntity(ent, __LINE__, __FILE__);
}

/*
======================================================================

  SHOOTERS

======================================================================
*/

void Use_Shooter(gentity_t * ent, gentity_t * other, gentity_t * activator)
{
	vec3_t dir;
	float deg;
	vec3_t up, right;

	// see if we have a target
	if (ent->enemy) {
		VectorSubtract(ent->enemy->r.currentOrigin, ent->s.origin, dir);
		VectorNormalize(dir);
	} else {
		VectorCopy(ent->movedir, dir);
	}

	// randomize a bit
	PerpendicularVector(up, dir);
	CrossProduct(up, dir, right);

	deg = crandom() * ent->random;
	VectorMA(dir, deg, up, dir);

	deg = crandom() * ent->random;
	VectorMA(dir, deg, right, dir);

	VectorNormalize(dir);
//Blaze: Use_Shooter does the code for the projectile weapons, and we dont have any of those
/*	switch ( ent->s.weapon ) {
	case WP_GRENADE_LAUNCHER:
		fire_grenade( ent, ent->s.origin, dir );
		break;
	case WP_ROCKET_LAUNCHER:
		fire_rocket( ent, ent->s.origin, dir );
		break;
	case WP_PLASMAGUN:
		fire_plasma( ent, ent->s.origin, dir );
		break;
	}
*/
	G_AddEvent(ent, EV_FIRE_WEAPON, 0);
}

static void InitShooter_Finish(gentity_t * ent)
{
	ent->enemy = G_PickTarget(ent->target);
	ent->think = 0;
	ent->nextthink = 0;
}

void InitShooter(gentity_t * ent, int weapon)
{
	ent->use = Use_Shooter;
	ent->s.weapon = weapon;

	RegisterItem(BG_FindItemForWeapon(weapon));

	G_SetMovedir(ent->s.angles, ent->movedir);

	if (!ent->random) {
		ent->random = 1.0;
	}
	ent->random = sin(M_PI * ent->random / 180);
	// target might be a moving object, so we can't set movedir for it
	if (ent->target) {
		ent->think = InitShooter_Finish;
		ent->nextthink = level.time + 500;
	}
	trap_RQ3LinkEntity(ent, __LINE__, __FILE__);
}

/*QUAKED shooter_rocket (1 0 0) (-16 -16 -16) (16 16 16)
Fires at either the target or the current direction.
"random" the number of degrees of deviance from the taget. (1.0 default)
*/
//Blaze: No need for this because no rocketlauncher
//void SP_shooter_rocket( gentity_t *ent ) {
//      InitShooter( ent, WP_ROCKET_LAUNCHER );
//}

/*QUAKED shooter_plasma (1 0 0) (-16 -16 -16) (16 16 16)
Fires at either the target or the current direction.
"random" is the number of degrees of deviance from the taget. (1.0 default)
*/
//Blaze: No need for this because no plasma gun
//void SP_shooter_plasma( gentity_t *ent ) {
//      InitShooter( ent, WP_PLASMAGUN);
//}

/*QUAKED shooter_grenade (1 0 0) (-16 -16 -16) (16 16 16)
Fires at either the target or the current direction.
"random" is the number of degrees of deviance from the taget. (1.0 default)
*/
//Blaze: No need for this because no grenade Launcher
//void SP_shooter_grenade( gentity_t *ent ) {
//      InitShooter( ent, WP_GRENADE_LAUNCHER);
//}
// Blaze: adding for func_breakable explosions
void func_breakable_explode(gentity_t * self, vec3_t pos)
{
	int eParam;
	gentity_t *tent;

//      GibEntity( self, 0 );
	eParam = self->s.eventParm;

	tent = G_TempEntity2(pos, EV_EXPLODE_BREAKABLE, eParam);

//      self->takedamage = qfalse;
//      self->s.eType = ET_INVISIBLE;
	self->exploded = qtrue;
}

// Blaze: adding for func_breakable explosions

void func_breakable_die(gentity_t * self, gentity_t * inflictor, gentity_t * attacker, int damage, int meansOfDeath)
{
	func_breakable_explode(self, self->s.origin);
//      G_ExplodeMissile(self);
	//Makro - added check
	if (self->damage > 0 && self->damage_radius > 0)
		G_RadiusDamage(self->s.origin, attacker, self->damage, self->damage_radius, self, meansOfDeath);
	//    radius damage
	trap_RQ3UnlinkEntity(self, __LINE__, __FILE__);

}

void Use_Breakable(gentity_t * self, gentity_t * other, gentity_t * activator)
{
	//G_UseTargets (self, activator);  
//  if (self->explosive)
//  {
	//func_breakable_die( self,activator,activator,self->damage,MOD_TRIGGER_HURT);
	//}
	//else
	//{
	//make sure it breaks
	//Makro - added check
	if (!self->exploded && self->health>0)
	{
		self->health = 0;
		G_BreakGlass(self, activator, activator, self->s.origin, MOD_TRIGGER_HURT, self->health);
	}
//  }
}

//Elder: Breakable anything!* -- we define, that is
/*QUAKED func_breakable (0 .5 .8) ? CHIPPABLE UNBREAKABLE EXPLOSIVE 
Breakable object entity that breaks, chips or explodes when damaged. 
-------- KEYS -------- 
health : determines the strength of the glass (default 5). 
id : a unique identification. Each type of breakable in a given map needs to have a separate id. Valid values are 0 through 63. 
type : type of breakable. See notes below. 
amount : sets the number of fragments to generate when the entity breaks. 0 ~ 10 pieces; 1 ~ 25 pieces; 2 ~ 50 pieces; 3 ~ lots of pieces (default 0). 
damage : sets the amount of damage dealt to nearbly players if the entity is made to be explosive (default 100). 
damage_radius : sets the maximum distance from the explosion players will take damage (default 128). 
-------- SPAWNFLAGS -------- 
CHIPPABLE : little pieces will spawn when the entity is shot. 
UNBREAKABLE : entity will never break. To make the entity chip, but never break, check the first two spawnflags. To make the entity chip and eventually break, only set the first spawnflag. 
EXPLOSIVE : entity will explode. 
-------- NOTES -------- 
Breakables are defined in sets by the 'type' key (e.g. type : glass, type : wood). Each type used in a map must be given a unique id number. Each entity of a particular type must have the same id number (i.e. if your first glass breakable has id : 1, then every glass breakable must have id : 1). To add custom breakables, use this format: 
 
Models: breakables/type/models/break1.md3, breakables/type/models/break2.md3, breakables/type/models/break3.md3 
Type is the value set in the type key. No more, no less than three models are required. The names must be break#. Texture/shader information is contained in the .md3 file just like regular mapobjects. 
 
Sounds: breakables/type/sounds/break1.wav, breakables/type/sounds/break2.wav, breakables/type/sounds/break3.wav, breakables/type/sounds/explosion.wav 
Type is the value set in the type key. No more, no less than three break sounds are required. The names must be break#. If the entity will be exploding (explosive : 1), then the explosion.wav sound must be included as well. 
 
Explosion graphic: breakables/type/explosion/texture 
Type is the value set in the type key. Texture is any texture(s) referenced by the explosion shader. The shader script should be added to yourmap.shader.  
 
If you wish to add a custom breakable to your map, please include your mapname (or perhaps 3 letters of it) in the type name to prevent conflicts (i.e. don't use 'brick', use 'tequila_brick' or just 'teq_brick'). See the breakables folder included in Reaction Quake 3 for the proper format.
*/

void reset_breakable(gentity_t *ent)
{
	trap_RQ3LinkEntity(ent, __LINE__, __FILE__);
	
	ent->exploded = qfalse;
	ent->takedamage = qtrue;
	ent->s.eType = ET_BREAKABLE;
	ent->health = ent->health_saved;
}

static void InitBreakable_Finish(gentity_t * ent)
{
	char info[MAX_INFO_STRING];

	ent->think = 0;
	ent->nextthink = 0;
	if (ent->s.weapon < 0 || ent->s.weapon >= RQ3_MAX_BREAKABLES) {
		G_Printf(S_COLOR_RED, "ERROR: Invalid func_breakable id (%d)\n", ent->s.weapon);
		G_FreeEntity(ent, __LINE__, __FILE__);
	}
	trap_GetConfigstring(CS_BREAKABLES + ent->s.weapon, info, sizeof(info));
	if (strlen(Info_ValueForKey(info, "type")) == 0) {
		G_Printf(S_COLOR_RED, "ERROR: Invalid func_breakable id (%d)\n", ent->s.weapon);
		G_FreeEntity(ent, __LINE__, __FILE__);
	}
	ent->s.eventParm |= (ent->s.weapon & 0x0FFF);
	ent->s.weapon = 0;
}

void SP_func_breakable(gentity_t * ent)
{
	int health;
	int amount;
	int temp;
	int damage;
	int damage_radius;

	char *id;
	char *velocity;
	char *jump;
	char *name;
	char breakinfo[MAX_INFO_STRING];

	// Make it appear as the brush
	trap_SetBrushModel(ent, ent->model);

	// Setup health of breakable
	G_SpawnInt("health", "0", &health);
	if (health <= 0) {
		health = 5;
	}
	//G_Printf("Setting health to %d\n",health);
	G_SpawnInt("damage", "170", &damage);

	ent->damage = damage;

	G_SpawnInt("damage_radius", "340", &damage_radius);

	ent->damage_radius = damage_radius;

	ent->exploded = qfalse;
	// Setup amount type
	G_SpawnInt("amount", "0", &temp);
	//Com_Printf("Amount %d ", temp);
	switch (temp) {
	case 0:
		amount = 0;
		break;
	case 1:
		amount = RQ3_DEBRIS_MEDIUM;
		break;
	case 2:
		amount = RQ3_DEBRIS_HIGH;
		break;
	case 3:
		amount = RQ3_DEBRIS_MEDIUM | RQ3_DEBRIS_HIGH;
		break;
	default:
		amount = RQ3_DEBRIS_MEDIUM;
		break;
	}
	if (ent->spawnflags & 1) {
		ent->chippable = qtrue;
		//Com_Printf("Chippable ");
	} else {
		ent->chippable = qfalse;
	}

	if (ent->spawnflags & 2) {
		ent->unbreakable = qtrue;
		//Com_Printf("Unbreakable ");
	} else {
		ent->unbreakable = qfalse;
	}

	if (ent->spawnflags & 4) {
		ent->explosive = qtrue;
	} else {
		ent->explosive = qfalse;
	}

	if (ent->spawnflags & 8) {
		ent->unkickable = qtrue;
	} else {
		ent->unkickable = qfalse;
	}
	
	if (!ent->damage_radius) {
		ent->damage_radius = GRENADE_SPLASH_RADIUS;
	}
	ent->use = Use_Breakable;
	ent->s.eventParm = amount << 6;

	//Makro - new code
	if (G_SpawnInt("type_id", "0", &ent->s.weapon)) {
		ent->think = InitBreakable_Finish;
		ent->nextthink = level.time + FRAMETIME;
	} else {
		G_SpawnString("id", "0", &id);
		if (atoi(id) < 0 || atoi(id) >= RQ3_MAX_BREAKABLES) {
			G_Printf("^2ERROR: ID too high\n");
			G_FreeEntity(ent, __LINE__, __FILE__);
			return;
		}
		//Com_Printf("ID (%d) ", id);
		if (!G_SpawnString("type", "", &name)) {
			G_Printf("^2ERROR: broken breakable name (%s)\n", name);
			G_FreeEntity(ent, __LINE__, __FILE__);
			return;
		}
		//Com_Printf("type (%s)\n",name);
		G_SpawnString("force", "7", &velocity);
		
		G_SpawnString("lift", "5", &jump);
		//Elder: merge the bits
		ent->s.eventParm |= (atoi(id) & 0x0FFF);

		Info_SetValueForKey(breakinfo, "type", name);
		Info_SetValueForKey(breakinfo, "velocity", velocity);
		Info_SetValueForKey(breakinfo, "jump", jump);
		//Makro - not needed
		//Info_SetValueForKey(breakinfo, "id", id);
		trap_SetConfigstring(CS_BREAKABLES + atoi(id), breakinfo);
	}

	ent->health = health;
	ent->health_saved = health;
	ent->takedamage = qtrue;

	ent->s.origin[0] = ent->r.mins[0] + (0.5 * (ent->r.maxs[0] - ent->r.mins[0]));
	ent->s.origin[1] = ent->r.mins[1] + (0.5 * (ent->r.maxs[1] - ent->r.mins[1]));
	ent->s.origin[2] = ent->r.mins[2] + (0.5 * (ent->r.maxs[2] - ent->r.mins[2]));

	// Let it know it is a breakable object
	ent->s.eType = ET_BREAKABLE;

	//Makro - reset function
	ent->reset = reset_breakable;

	// If the mapper gave it a model, use it
	if (ent->model2) {
		ent->s.modelindex2 = G_ModelIndex(ent->model2);
	}
	//Makro - added this so spectators can go through breakables
	//ent->nextthink = level.time + FRAMETIME;
	//ent->think = Think_SpawnNewDoorTrigger;

	trap_RQ3LinkEntity(ent, __LINE__, __FILE__);

}

/*
=================
G_BreakGlass

Create/process a breakable event entity
Original by inolen, heavy modifications by Elder
=================
*/
void G_BreakGlass(gentity_t * ent, gentity_t * inflictor, gentity_t * attacker, vec3_t point, int mod, int damage)
{
	gentity_t *tent;
	vec3_t size;
	vec3_t impactPoint;

	//Elder: for the bit-shifting
	int eParm;
	int shiftCount = 0;

	//Elder:
	//eventParm can only transmit as a byte (8-bits/255)
	//So if we receive a huge one, we can knock it down (shift-op)
	//and count the number of times
	//Once it's below 255, we can send a more appropriate event
	//This way, the mappers can use a single func_breakable
	//while we process it on the server-side.
	//Places to stuff: eventParm
	eParm = ent->s.eventParm;

	if (ent->health <= 0) {
		//G_Printf("Original eParm: %i \n", ent->s.eventParm);
		//Copy the first four bits and strip them out of the original
		/*      eParm = ent->s.eventParm & 15;
		   ent->s.eventParm &= ~eParm;

		   //Shift-op loop
		   while (ent->s.eventParm > 255)
		   {
		   shiftCount++;
		   ent->s.eventParm = ent->s.eventParm >> 4;
		   }

		   eParm |= ent->s.eventParm;
		 */
		//eParm should now be under 1 byte and shiftCount >= 0
		//G_Printf("New eParm: %i Shifts: %i\n", eParm, shiftCount);

		// Tell the program based on the gun if it was caused by splash damage
		switch (mod) {
			//Elder: added + compacted
		case MOD_KNIFE:
		case MOD_KNIFE_THROWN:
		case MOD_MP5:
		case MOD_M4:
		case MOD_M3:
		case MOD_PISTOL:
		case MOD_HANDCANNON:
		case MOD_AKIMBO:
		case MOD_SNIPER:
		case MOD_GAUNTLET:
		case MOD_KICK:
			//Use actual impact point
			VectorCopy(point, impactPoint);
			break;
		default:
			//Splash damage weapons: use center of the glass
			VectorSubtract(ent->r.maxs, ent->r.mins, size);
			VectorScale(size, 0.5, size);
			VectorAdd(ent->r.mins, size, impactPoint);
			break;

		}

		if (ent->explosive) {
			mod = MOD_TRIGGER_HURT;
			func_breakable_die(ent, inflictor, attacker, damage, mod);
		}
		G_UseTargets(ent, ent->activator);
		//G_FreeEntity( ent, __LINE__, __FILE__ );
		//G_Printf("%s shift: %i\n", vtos(impactPoint), shiftCount);
		switch (shiftCount) {
		case 0:
			tent = G_TempEntity2(impactPoint, EV_BREAK_GLASS1, eParm);
			break;
		case 1:
			tent = G_TempEntity2(impactPoint, EV_BREAK_GLASS2, eParm);
			break;
		case 2:
			tent = G_TempEntity2(impactPoint, EV_BREAK_GLASS3, eParm);
			break;
		default:
			G_Error("G_BreakGlass: shiftCount > 2\n");
			break;
		}

		//G_Printf("eType: %i\n", tent->s.event & ~EV_EVENT_BITS);
		//Elder: use TempEntity2 to stuff params
		//tent = G_TempEntity( center, EV_BREAK_GLASS );
		//tent->s.eventParm = eParm;
		//unlink it instead of freeing
		trap_RQ3UnlinkEntity(ent, __LINE__, __FILE__);

	} else if (ent->chippable) {
		//Stil has some life left, so chip it
		//Copy the first four bits and strip them out of the original
		/*eParm = ent->s.eventParm & 15;
		   ent->s.eventParm &= ~eParm;

		   //Shift-op loop
		   while (ent->s.eventParm > 255)
		   {
		   shiftCount++;
		   ent->s.eventParm = ent->s.eventParm >> 4;
		   }

		   eParm |= ent->s.eventParm;
		 */
		//eParm should now be under 1 byte and shiftCount >= 0
		//G_Printf("New eParm: %i Shifts: %i\n", eParm, shiftCount);

		// Tell the program based on the gun if it was caused by splash damage
		switch (mod) {
			//Elder: added + compacted
		case MOD_KNIFE:
		case MOD_KNIFE_THROWN:
		case MOD_MP5:
		case MOD_M4:
		case MOD_M3:
		case MOD_PISTOL:
		case MOD_HANDCANNON:
		case MOD_AKIMBO:
		case MOD_SNIPER:
		case MOD_GAUNTLET:
		case MOD_KICK:
			//Use actual impact point
			VectorCopy(point, impactPoint);
			break;
		default:
			//Splash damage weapons: use center of the glass
			VectorSubtract(ent->r.maxs, ent->r.mins, size);
			VectorScale(size, 0.5, size);
			VectorAdd(ent->r.mins, size, impactPoint);
			break;

		}
		//G_FreeEntity( ent, __LINE__, __FILE__ );
		//G_Printf("%s shift: %i\n", vtos(impactPoint), shiftCount);
		tent = G_TempEntity2(impactPoint, EV_CHIP_GLASS, eParm);

	}
}

void SP_func_pressure(gentity_t * ent)
{
	char *type;

	// Make it appear as the brush
	trap_SetBrushModel(ent, ent->model);
	trap_RQ3LinkEntity(ent, __LINE__, __FILE__);

	VectorCopy(ent->s.origin, ent->s.pos.trBase);
	VectorCopy(ent->s.origin, ent->r.currentOrigin);
	ent->s.eType = ET_PRESSURE;

	G_SpawnInt("speed", "200", &ent->mass);	// mass will hold speed... yeah...
	G_SpawnInt("life", "200", &ent->tension);  // hmm..
	G_SpawnString("type", "steam", &type);

	if (!Q_stricmp(type, "air"))	// bounce will hold pressure type... yeah...
		ent->bounce = 1;
	else if (!Q_stricmp(type, "flame") || !Q_stricmp(type, "fire"))
		ent->bounce = 2;
	else if (!Q_stricmp(type, "water"))
		ent->bounce = 3;
	else			// steam is default
		ent->bounce = 0;

	// ent->s.frame holds type
	// ent->s.powerups holds speed

}

void G_CreatePressure(vec3_t origin, vec3_t normal, gentity_t * ent)
{
	gentity_t *tent;

	G_UseTargets(ent, ent->activator);

	tent = G_TempEntity(origin, EV_PRESSURE);
	tent->s.eventParm = DirToByte(normal);

	tent->s.frame = ent->bounce;	// 1 = air, 2 = flame, 0 = steam
	tent->s.powerups = ent->mass;	// speed of pressure
	//Makro - changed from constantLight to generic1
	tent->s.generic1 = ent->tension; // 200 default. Life of steam
}

/*
	G_FileExists		by NiceAss

	Created for vote map to make sure it exists before voting. 
	I'm sure there are plenty of more uses.
*/
qboolean G_FileExists(char *filename) {
	fileHandle_t f;

	trap_FS_FOpenFile(filename, &f, FS_READ);
	if (!f) return qfalse;
	trap_FS_FCloseFile(f);
	return qtrue;
}


/*
================
G_EvaluateTrajectory

================
*/
void G_EvaluateTrajectory(const trajectory_t * tr, int atTime, vec3_t result)
{
	float deltaTime;
	float phase;

	switch (tr->trType) {
	case TR_STATIONARY:
	case TR_INTERPOLATE:
		VectorCopy(tr->trBase, result);
		break;
	case TR_LINEAR:
		deltaTime = (atTime - tr->trTime) * 0.001;	// milliseconds to seconds
		VectorMA(tr->trBase, deltaTime, tr->trDelta, result);
		break;
	case TR_SINE:
		deltaTime = (atTime - tr->trTime) / (float) tr->trDuration;
		phase = sin(deltaTime * M_PI * 2);
		VectorMA(tr->trBase, phase, tr->trDelta, result);
		break;
	case TR_LINEAR_STOP:
		if (atTime > tr->trTime + tr->trDuration) {
			atTime = tr->trTime + tr->trDuration;
		}
		deltaTime = (atTime - tr->trTime) * 0.001;	// milliseconds to seconds
		if (deltaTime < 0) {
			deltaTime = 0;
		}
		VectorMA(tr->trBase, deltaTime, tr->trDelta, result);
		break;
	case TR_GRAVITY:
		deltaTime = (atTime - tr->trTime) * 0.001;	// milliseconds to seconds
		VectorMA(tr->trBase, deltaTime, tr->trDelta, result);
		result[2] -= 0.5 * (float) g_gravity.integer * deltaTime * deltaTime;
		break;
	default:
		Com_Error(ERR_DROP, "G_EvaluateTrajectory: unknown trType: %i", tr->trTime);
		break;
	}
}

/*
================
G_EvaluateTrajectoryDelta

For determining velocity at a given time
================
*/
void G_EvaluateTrajectoryDelta(const trajectory_t * tr, int atTime, vec3_t result)
{
	float deltaTime;
	float phase;

	switch (tr->trType) {
	case TR_STATIONARY:
	case TR_INTERPOLATE:
		VectorClear(result);
		break;
	case TR_LINEAR:
		VectorCopy(tr->trDelta, result);
		break;
	case TR_SINE:
		deltaTime = (atTime - tr->trTime) / (float) tr->trDuration;
		phase = cos(deltaTime * M_PI * 2);	// derivative of sin = cos
		phase *= 0.5;
		VectorScale(tr->trDelta, phase, result);
		break;
	case TR_LINEAR_STOP:
		if (atTime > tr->trTime + tr->trDuration) {
			VectorClear(result);
			return;
		}
		VectorCopy(tr->trDelta, result);
		break;
	case TR_GRAVITY:
		deltaTime = (atTime - tr->trTime) * 0.001;	// milliseconds to seconds
		VectorCopy(tr->trDelta, result);
		result[2] -= (float) g_gravity.integer * deltaTime;
		break;
	default:
		Com_Error(ERR_DROP, "G_EvaluateTrajectoryDelta: unknown trType: %i", tr->trTime);
		break;
	}
}

/* 
================
G_EvaluateTrajectoryDelta  - By NiceAss

Will update all ET_MISSILE entities with TR_GRAVITY on a g_gravity change.
================*/
void G_GravityChange(void)
{
	int i;
	gentity_t *ent;

	ent = &g_entities[0];
	for (i = 0; i < level.num_entities; i++, ent++) {
		if (ent->s.pos.trType == TR_GRAVITY && ent->s.eType == ET_MISSILE) {
			G_EvaluateTrajectoryDelta(&ent->s.pos, level.time, ent->s.pos.trDelta);
			VectorCopy(ent->r.currentOrigin, ent->s.pos.trBase);
			ent->s.pos.trTime = level.time;
		}
	}
}
