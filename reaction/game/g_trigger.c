//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.27  2003/07/30 16:05:46  makro
// no message
//
// Revision 1.26  2003/04/26 22:33:07  jbravo
// Wratted all calls to G_FreeEnt() to avoid crashing and provide debugging
//
// Revision 1.25  2003/03/22 20:29:26  jbravo
// wrapping linkent and unlinkent calls
//
// Revision 1.24  2002/07/22 06:32:27  niceass
// cleaned up the powerup code
//
// Revision 1.23  2002/06/16 20:06:14  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.22  2002/06/06 18:08:01  makro
// Removed pathtarget code for trigger_pushes for now
//
// Revision 1.21  2002/06/04 21:35:40  makro
// Updated trigger_push code
//
// Revision 1.20  2002/06/04 20:53:19  makro
// Trigger_pushes can now be teamed up
//
// Revision 1.19  2002/05/30 21:18:28  makro
// Bots should reload/bandage when roaming around
// Added "pathtarget" key to all the entities
//
// Revision 1.18  2002/05/29 13:49:26  makro
// Elevators/doors
//
// Revision 1.17  2002/05/23 18:37:50  makro
// Bots should crouch more often when they attack with a SSG
// Made this depend on skill. Also, elevator stuff
//
// Revision 1.16  2002/05/23 15:55:25  makro
// Elevators
//
// Revision 1.15  2002/05/22 04:19:45  blaze
// Sound entity changes as per Sze
//
// Revision 1.14  2002/05/18 14:52:16  makro
// Bot stuff. Other stuff. Just... stuff :p
//
// Revision 1.13  2002/05/16 06:57:54  makro
// Doors with health (again !), bot-only trigger_pushes
//
// Revision 1.12  2002/05/11 22:01:41  makro
// Trigger_hurt
//
// Revision 1.11  2002/05/11 17:59:49  makro
// Trigger_hurt update
//
// Revision 1.10  2002/05/11 00:38:47  blaze
// trigger_push and target_push default to no noise when the noise flag is not set.
//
// Revision 1.9  2002/05/05 15:18:03  makro
// Fixed some crash bugs. Bot stuff. Triggerable func_statics.
// Made flags only spawn in CTF mode
//
// Revision 1.8  2002/03/18 06:20:39  blaze
// noise tag will play sounds for trigger_push and target_push
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
#include "g_local.h"

void InitTrigger(gentity_t * self)
{
	if (!VectorCompare(self->s.angles, vec3_origin))
		G_SetMovedir(self->s.angles, self->movedir);

	trap_SetBrushModel(self, self->model);
	self->r.contents = CONTENTS_TRIGGER;	// replaces the -1 from trap_SetBrushModel
	self->r.svFlags = SVF_NOCLIENT;
}

// the wait time has passed, so set back up for another activation
void multi_wait(gentity_t * ent)
{
	ent->nextthink = 0;
}

// the trigger was just activated
// ent->activator should be set to the activator so it can be held through a delay
// so wait for the delay time before firing
void multi_trigger(gentity_t * ent, gentity_t * activator)
{
	ent->activator = activator;
	if (ent->nextthink) {
		return;		// can't retrigger until the wait is over
	}
	//Makro - inactive trigger ?
	if (ent->inactive) {
		return;
	}
	//Makro - added check; Q3 crashed in archives when playing
	//with .dll's and shooting one of the barrels
	if (activator != NULL) {
		if (activator->client) {
			if ((ent->spawnflags & 1) && activator->client->sess.sessionTeam != TEAM_RED) {
				return;
			}
			if ((ent->spawnflags & 2) && activator->client->sess.sessionTeam != TEAM_BLUE) {
				return;
			}
		}
	}

	G_UseTargets(ent, ent->activator);

	if (ent->wait > 0) {
		ent->think = multi_wait;
		ent->nextthink = level.time + (ent->wait + ent->random * crandom()) * 1000;
	} else {
		// we can't just remove (self) here, because this is a touch function
		// called while looping through area links...
		ent->touch = 0;
		ent->nextthink = level.time + FRAMETIME;
		ent->think = G_RealFreeEntity;
	}
}

void Use_Multi(gentity_t * ent, gentity_t * other, gentity_t * activator)
{
	multi_trigger(ent, activator);
}

void Touch_Multi(gentity_t * self, gentity_t * other, trace_t * trace)
{
	if (!other->client) {
		return;
	}
	multi_trigger(self, other);
}

/*QUAKED trigger_multiple (.5 .5 .5) ?
"wait" : Seconds between triggerings, 0.5 default, -1 = one time only.
"random"	wait variance, default is 0
Variable sized repeatable trigger.  Must be targeted at one or more entities.
so, the basic time between firing is a random time between
(wait - random) and (wait + random)
*/
void SP_trigger_multiple(gentity_t * ent)
{
	G_SpawnFloat("wait", "0.5", &ent->wait);
	G_SpawnFloat("random", "0", &ent->random);

	if (ent->random >= ent->wait && ent->wait >= 0) {
		ent->random = ent->wait - FRAMETIME;
		G_Printf("trigger_multiple has random >= wait\n");
	}

	ent->touch = Touch_Multi;
	ent->use = Use_Multi;

	InitTrigger(ent);
	trap_RQ3LinkEntity(ent, __LINE__, __FILE__);
}

/*
==============================================================================

trigger_always

==============================================================================
*/

void trigger_always_think(gentity_t * ent)
{
	G_UseTargets(ent, ent);
	G_FreeEntity(ent, __LINE__, __FILE__);
}

/*QUAKED trigger_always (.5 .5 .5) (-8 -8 -8) (8 8 8)
This trigger will always fire.  It is activated by the world.
*/
void SP_trigger_always(gentity_t * ent)
{
	// we must have some delay to make sure our use targets are present
	ent->nextthink = level.time + 300;
	ent->think = trigger_always_think;
}

/*
==============================================================================

trigger_push

==============================================================================
*/

void trigger_push_touch(gentity_t * self, gentity_t * other, trace_t * trace)
{

	if (!other || !self)
		return;

	if (!other->client) {
		return;
	}
	//Makro - too soon to activate ?
	/*if (level.time < self->s.legsAnim) {
	   return;
	   } */

	//Makro - bot only triggers
	if (self->spawnflags & 1) {
		if (!(other->r.svFlags & SVF_BOT)) {
			return;
		}
	}

	BG_TouchJumpPad(&other->client->ps, &self->s);
	//Makro - "team up" trigger_pushes
	//something is broken here :/
	/*
	   if (self->pathtarget) {
	   if (self->pathtarget[0]) {
	   gentity_t    *loop = NULL;
	   for (loop = G_Find2(NULL, FOFS(classname), self->classname, FOFS(pathtarget), self->pathtarget); loop; G_Find2(loop, FOFS(classname), self->classname, FOFS(pathtarget), self->pathtarget)) {
	   //Makro - delay 5 seconds before triggering another trigger_push from the same "team"
	   if (self->distance) {
	   loop->s.legsAnim = level.time + self->distance * 1000;
	   } else {
	   loop->s.legsAnim = level.time + 5 * 1000;
	   }
	   }
	   }
	   } */

}

/*
=================
AimAtTarget

Calculate origin2 so the target apogee will be hit
=================
*/
void AimAtTarget(gentity_t * self)
{
	gentity_t *ent;
	vec3_t origin;
	float height, gravity, time, forward;
	float dist;

	VectorAdd(self->r.absmin, self->r.absmax, origin);
	VectorScale(origin, 0.5, origin);

	ent = G_PickTarget(self->target);
	if (!ent) {
		G_FreeEntity(self, __LINE__, __FILE__);
		return;
	}

	height = ent->s.origin[2] - origin[2];
	gravity = g_gravity.value;
	time = sqrt(height / (.5 * gravity));
	if (!time) {
		G_FreeEntity(self, __LINE__, __FILE__);
		return;
	}
	// set s.origin2 to the push velocity
	VectorSubtract(ent->s.origin, origin, self->s.origin2);
	self->s.origin2[2] = 0;
	dist = VectorNormalize(self->s.origin2);

	forward = dist / time;
	VectorScale(self->s.origin2, forward, self->s.origin2);

	self->s.origin2[2] = time * gravity;
}

/*QUAKED trigger_push (.5 .5 .5) ? BOT_ONLY
Must point at a target_position, which will be the apex of the leap.
This will be client side predicted, unlike target_push
*/
void SP_trigger_push(gentity_t * self)
{
	char *sound;

	InitTrigger(self);

	// unlike other triggers, we need to send this one to the client
	// NiceAss: Added for custom push sounds. Default is none. Q3 is "sounds/world/bouncepad.wav"
	//Changed from noise to sound as per Sze
	if (G_SpawnString("sound", "sound/misc/silence.wav", &sound)) {
		self->s.generic1 = G_SoundIndex(sound);
	}
	//Makro - for bot-only triggers
	if (!(self->spawnflags & 1)) {
		self->r.svFlags &= ~SVF_NOCLIENT;
	}
	self->s.powerups = (self->spawnflags & 1);
	self->s.eType = ET_PUSH_TRIGGER;
	self->touch = trigger_push_touch;
	self->think = AimAtTarget;
	self->nextthink = level.time + FRAMETIME;
	trap_RQ3LinkEntity(self, __LINE__, __FILE__);
}

void Use_target_push(gentity_t * self, gentity_t * other, gentity_t * activator)
{
	if (!activator->client) {
		return;
	}

	if (activator->client->ps.pm_type != PM_NORMAL) {
		return;
	}

	VectorCopy(self->s.origin2, activator->client->ps.velocity);

	// play fly sound every 1.5 seconds
	if (activator->fly_sound_debounce_time < level.time) {
		activator->fly_sound_debounce_time = level.time + 1500;
		//Elder: added to check noise_index
		if (self->noise_index)
			G_Sound(activator, CHAN_AUTO, self->noise_index);
	}
}

/*QUAKED target_push (.5 .5 .5) (-8 -8 -8) (8 8 8) bouncepad
Pushes the activator in the direction.of angle, or towards a target apex.
"speed"		defaults to 1000
if "bouncepad", play bounce noise instead of windfly
*/
void SP_target_push(gentity_t * self)
{
	char *sound;

	if (!self->speed) {
		self->speed = 1000;
	}
	G_SetMovedir(self->s.angles, self->s.origin2);
	VectorScale(self->s.origin2, self->speed, self->s.origin2);
	//Changed from noise to sound as per Sze
	if (G_SpawnString("sound", "sound/misc/silence.wav", &sound)) {
		//Makro - debug message, no longer needed
		//G_Printf("^2Sound was %s\n",sound);
		self->noise_index = G_SoundIndex(sound);
	}

	if (self->spawnflags & 1) {
		//Elder: edited for now TODO: let mappers use a key pair
		//self->noise_index = G_SoundIndex("sound/world/jumppad.wav");
	} else {
		//Elder: edited for now TODO: let mappers use a key pair
		//self->noise_index = G_SoundIndex("sound/misc/windfly.wav");
	}
	if (self->target) {
		VectorCopy(self->s.origin, self->r.absmin);
		VectorCopy(self->s.origin, self->r.absmax);
		self->think = AimAtTarget;
		self->nextthink = level.time + FRAMETIME;
	}
	self->use = Use_target_push;
}

/*
==============================================================================

trigger_teleport

==============================================================================
*/

void trigger_teleporter_touch(gentity_t * self, gentity_t * other, trace_t * trace)
{
	gentity_t *dest;

	if (!other->client) {
		return;
	}
	if (other->client->ps.pm_type == PM_DEAD) {
		return;
	}
	// Spectators only?
	if ((self->spawnflags & 1) && other->client->sess.sessionTeam != TEAM_SPECTATOR) {
		return;
	}

	dest = G_PickTarget(self->target);
	if (!dest) {
		G_Printf("Couldn't find teleporter destination\n");
		return;
	}

	TeleportPlayer(other, dest->s.origin, dest->s.angles);
}

/*QUAKED trigger_teleport (.5 .5 .5) ? SPECTATOR
Allows client side prediction of teleportation events.
Must point at a target_position, which will be the teleport destination.

If spectator is set, only spectators can use this teleport
Spectator teleporters are not normally placed in the editor, but are created
automatically near doors to allow spectators to move through them
*/
void SP_trigger_teleport(gentity_t * self)
{
	InitTrigger(self);

	// unlike other triggers, we need to send this one to the client
	// unless is a spectator trigger
	if (self->spawnflags & 1) {
		self->r.svFlags |= SVF_NOCLIENT;
	} else {
		self->r.svFlags &= ~SVF_NOCLIENT;
	}

	// make sure the client precaches this sound
	G_SoundIndex("sound/world/jumppad.wav");

	self->s.eType = ET_TELEPORT_TRIGGER;
	self->touch = trigger_teleporter_touch;

	trap_RQ3LinkEntity(self, __LINE__, __FILE__);
}

/*
==============================================================================

trigger_hurt

==============================================================================
*/

/*QUAKED trigger_hurt (.5 .5 .5) ? START_OFF - SILENT NO_PROTECTION SLOW
Any entity that touches this will be hurt.
It does dmg points of damage each server frame
Targeting the trigger will toggle its on / off state.

SILENT			supresses playing the sound
SLOW			changes the damage rate to once per second
NO_PROTECTION	*nothing* stops the damage

"dmg"			default 5 (whole numbers only)

*/
void hurt_use(gentity_t * self, gentity_t * other, gentity_t * activator)
{
	if (self->r.linked) {
		trap_RQ3UnlinkEntity(self, __LINE__, __FILE__);
	} else {
		trap_RQ3LinkEntity(self, __LINE__, __FILE__);
	}
}

void hurt_touch(gentity_t * self, gentity_t * other, trace_t * trace)
{
	int dflags;

	if (!other->takedamage) {
		return;
	}

	if (self->timestamp > level.time) {
		return;
	}

	if (self->spawnflags & 16) {
		self->timestamp = level.time + 1000;
	} else {
		self->timestamp = level.time + FRAMETIME;
	}

	// play sound
	if (!(self->spawnflags & 4)) {
		G_Sound(other, CHAN_AUTO, self->noise_index);
	}

	if (self->spawnflags & 8)
		dflags = DAMAGE_NO_PROTECTION;
	else
		dflags = 0;
	G_Damage(other, self, self, NULL, NULL, self->damage, dflags, MOD_TRIGGER_HURT);
}

void SP_trigger_hurt(gentity_t * self)
{
	InitTrigger(self);

	self->noise_index = G_SoundIndex("sound/world/electro.wav");
	self->touch = hurt_touch;

	if (!self->damage) {
		self->damage = 5;
	}

	self->r.contents = CONTENTS_TRIGGER;

	//Makro - removed this check
	//if ( self->spawnflags & 2 ) {
	self->use = hurt_use;
	//}

	// link in to the world if starting active
	if (!(self->spawnflags & 1)) {
		trap_RQ3LinkEntity(self, __LINE__, __FILE__);
	} else {
		//Makro - added
		trap_RQ3UnlinkEntity(self, __LINE__, __FILE__);
	}
}

/*
==============================================================================

timer

==============================================================================
*/

/*QUAKED func_timer (0.3 0.1 0.6) (-8 -8 -8) (8 8 8) START_ON
This should be renamed trigger_timer...
Repeatedly fires its targets.
Can be turned on or off by using.

"wait"			base time between triggering all targets, default is 1
"random"		wait variance, default is 0
so, the basic time between firing is a random time between
(wait - random) and (wait + random)

*/
void func_timer_think(gentity_t * self)
{
	G_UseTargets(self, self->activator);
	// set time before next firing
	self->nextthink = level.time + 1000 * (self->wait + crandom() * self->random);
}

void func_timer_use(gentity_t * self, gentity_t * other, gentity_t * activator)
{
	self->activator = activator;

	// if on, turn it off
	if (self->nextthink) {
		self->nextthink = 0;
		return;
	}
	// turn it on
	func_timer_think(self);
}

void SP_func_timer(gentity_t * self)
{
	G_SpawnFloat("random", "1", &self->random);
	G_SpawnFloat("wait", "1", &self->wait);

	self->use = func_timer_use;
	self->think = func_timer_think;

	if (self->random >= self->wait) {
		self->random = self->wait - FRAMETIME;
		G_Printf("func_timer at %s has random >= wait\n", vtos(self->s.origin));
	}

	if (self->spawnflags & 1) {
		self->nextthink = level.time + FRAMETIME;
		self->activator = self;
	}

	self->r.svFlags = SVF_NOCLIENT;
}
