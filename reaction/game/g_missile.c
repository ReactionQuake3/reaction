//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.33  2003/03/22 20:29:26  jbravo
// wrapping linkent and unlinkent calls
//
// Revision 1.32  2003/03/09 21:30:38  jbravo
// Adding unlagged.   Still needs work.
//
// Revision 1.31  2002/09/29 16:06:45  jbravo
// Work done at the HPWorld expo
//
// Revision 1.30  2002/08/28 23:10:06  jbravo
// Added cg_RQ3_SuicideLikeARealMan, timestamping to server logs and
// fixed stats for non-TP modes.
//
// Revision 1.29  2002/06/16 20:06:14  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.28  2002/06/16 17:38:00  jbravo
// Removed the MISSIONPACK ifdefs and missionpack only code.
//
// Revision 1.27  2002/06/11 15:52:21  makro
// Fixed knife + unbreakable breakables/breakables with high health bug
//
// Revision 1.26  2002/04/29 06:16:27  niceass
// small change to pressure system
//
// Revision 1.25  2002/04/06 21:42:20  makro
// Changes to bot code. New surfaceparm system.
//
// Revision 1.24  2002/04/05 18:53:26  jbravo
// Warning fixes
//
// Revision 1.23  2002/03/18 19:18:39  slicer
// Fixed bandage bugs ( i hope )
//
// Revision 1.22  2002/03/12 04:55:31  blaze
// stats should only be recored when the round is in progress
//
// Revision 1.21  2002/01/14 01:20:45  niceass
// No more default 800 gravity on items
// Thrown knife+Glass fix - NiceAss
//
// Revision 1.20  2002/01/11 19:48:30  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.19  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
#include "g_local.h"
//Makro - to get the new surfaceparm system to work :/
#include "surfaceflags.h"

int GetMaterialFromFlag(int flag);
qboolean IsMetalMat(int Material);
qboolean IsMetalFlag(int flag);

#define	MISSILE_PRESTEP_TIME	50

/*
================
G_BounceMissile

================
*/
void G_BounceMissile(gentity_t * ent, trace_t * trace)
{
	vec3_t velocity;
	float dot;
	int hitTime;

	// reflect the velocity on the trace plane
	hitTime = level.previousTime + (level.time - level.previousTime) * trace->fraction;
	G_EvaluateTrajectoryDelta(&ent->s.pos, hitTime, velocity);
	dot = DotProduct(velocity, trace->plane.normal);
	VectorMA(velocity, -2 * dot, trace->plane.normal, ent->s.pos.trDelta);

	if (ent->s.eFlags & EF_BOUNCE_HALF) {
		VectorScale(ent->s.pos.trDelta, 0.65, ent->s.pos.trDelta);
		// check for stop
		if (trace->plane.normal[2] > 0.2 && VectorLength(ent->s.pos.trDelta) < 40) {
			G_SetOrigin(ent, trace->endpos);
			return;
		}
	}

	VectorAdd(ent->r.currentOrigin, trace->plane.normal, ent->r.currentOrigin);
	VectorCopy(ent->r.currentOrigin, ent->s.pos.trBase);
	ent->s.pos.trTime = level.time;
}

/*
================
G_ExplodeMissile

Explode a missile without an impact
================
*/
void G_ExplodeMissile(gentity_t * ent)
{
	vec3_t dir;
	vec3_t origin;

	G_EvaluateTrajectory(&ent->s.pos, level.time, origin);
	SnapVector(origin);
	G_SetOrigin(ent, origin);

	// we don't have a valid direction, so just point straight up
	dir[0] = dir[1] = 0;
	dir[2] = 1;

	ent->s.eType = ET_GENERAL;
	G_AddEvent(ent, EV_MISSILE_MISS, DirToByte(dir));

	ent->freeAfterEvent = qtrue;

	// splash damage
	if (ent->splashDamage) {
		if (G_RadiusDamage
		    (ent->r.currentOrigin, ent->parent, ent->splashDamage, ent->splashRadius, ent,
		     ent->splashMethodOfDeath)) {
			g_entities[ent->r.ownerNum].client->accuracy_hits++;
			// Elder: Statistics tracking
			if (ent->s.weapon == WP_KNIFE && 
					((g_gametype.integer == GT_TEAMPLAY && level.team_round_going) || g_gametype.integer != GT_TEAMPLAY))
				g_entities[ent->r.ownerNum].client->pers.records[REC_KNIFETHROWHITS]++;
			if (ent->s.weapon == WP_GRENADE &&
					((g_gametype.integer == GT_TEAMPLAY && level.team_round_going) || g_gametype.integer != GT_TEAMPLAY))
				g_entities[ent->r.ownerNum].client->pers.records[REC_GRENADEHITS]++;
		}
	}
	//Elder: huhh?
	//G_Printf("exploding knife\n");
	trap_RQ3LinkEntity(ent, __LINE__, __FILE__);
}

/*
================
G_MissileImpact
================
*/
void G_MissileImpact(gentity_t * ent, trace_t * trace)
{
	gentity_t *other;
	qboolean hitClient = qfalse;
	vec3_t velocity;

	//Elder: added for thrown knife condition
	gitem_t *xr_item;
	gentity_t *xr_drop;

	other = &g_entities[trace->entityNum];

	//Elder: no grenade explosion on impact
	if (ent->s.weapon == WP_GRENADE && (ent->s.eFlags & (EF_BOUNCE | EF_BOUNCE_HALF))) {
		G_BounceMissile(ent, trace);
		G_AddEvent(ent, EV_GRENADE_BOUNCE, 0);
		return;
	}

	// impact damage
	if (other->takedamage) {
		// FIXME: wrong damage direction?
		if (ent->damage) {
			if (LogAccuracyHit(other, &g_entities[ent->r.ownerNum])) {
				g_entities[ent->r.ownerNum].client->accuracy_hits++;
				// Elder: Statistics tracking
				if (ent->s.weapon == WP_KNIFE &&
						((g_gametype.integer == GT_TEAMPLAY && level.team_round_going) || g_gametype.integer != GT_TEAMPLAY))
					g_entities[ent->r.ownerNum].client->pers.records[REC_KNIFETHROWHITS]++;
				//g_entities[ent->r.ownerNum].client->knifeHits++;
				if (ent->s.weapon == WP_GRENADE &&
						((g_gametype.integer == GT_TEAMPLAY && level.team_round_going) || g_gametype.integer != GT_TEAMPLAY))
					g_entities[ent->r.ownerNum].client->pers.records[REC_GRENADEHITS]++;
				//g_entities[ent->r.ownerNum].client->grenHits++;
				hitClient = qtrue;
			}
			G_EvaluateTrajectoryDelta(&ent->s.pos, level.time, velocity);
			if (VectorLength(velocity) == 0) {
				velocity[2] = 1;	// stepped on a grenade
			}
		}
	}

	if (!strcmp(ent->classname, "hook")) {
		gentity_t *nent;
		vec3_t v;

		nent = G_Spawn();
		if (other->takedamage && other->client) {

			G_AddEvent(nent, EV_MISSILE_HIT, DirToByte(trace->plane.normal));
			nent->s.otherEntityNum = other->s.number;

			ent->enemy = other;

			v[0] = other->r.currentOrigin[0] + (other->r.mins[0] + other->r.maxs[0]) * 0.5;
			v[1] = other->r.currentOrigin[1] + (other->r.mins[1] + other->r.maxs[1]) * 0.5;
			v[2] = other->r.currentOrigin[2] + (other->r.mins[2] + other->r.maxs[2]) * 0.5;

			SnapVectorTowards(v, ent->s.pos.trBase);	// save net bandwidth
		} else {
			VectorCopy(trace->endpos, v);
			G_AddEvent(nent, EV_MISSILE_MISS, DirToByte(trace->plane.normal));
			ent->enemy = NULL;
		}

		SnapVectorTowards(v, ent->s.pos.trBase);	// save net bandwidth

		nent->freeAfterEvent = qtrue;
		// change over to a normal entity right at the point of impact
		nent->s.eType = ET_GENERAL;
		ent->s.eType = ET_GRAPPLE;

		G_SetOrigin(ent, v);
		G_SetOrigin(nent, v);

		//Blaze: Hook dosent exist any more
		//ent->think = Weapon_HookThink;
		ent->nextthink = level.time + FRAMETIME;

		ent->parent->client->ps.pm_flags |= PMF_GRAPPLE_PULL;
		VectorCopy(ent->r.currentOrigin, ent->parent->client->ps.grapplePoint);

		trap_RQ3LinkEntity(ent, __LINE__, __FILE__);
		trap_RQ3LinkEntity(nent, __LINE__, __FILE__);

		return;
	}
	// is it cheaper in bandwidth to just remove this ent and create a new
	// one, rather than changing the missile into the explosion?

	//Elder: I don't know but that's what we did for the knife
	if (other->takedamage && other->client) {
		G_AddEvent(ent, EV_MISSILE_HIT, DirToByte(trace->plane.normal));
		ent->s.otherEntityNum = other->s.number;
		//Makro - new surfaceparm system
		//} else if( trace->surfaceFlags & SURF_METALSTEPS ) {
	} else if (IsMetalFlag(trace->surfaceFlags)) {
		G_AddEvent(ent, EV_MISSILE_MISS_METAL, DirToByte(trace->plane.normal));
	} else {
		G_AddEvent(ent, EV_MISSILE_MISS, DirToByte(trace->plane.normal));
	}

	//Elder: knife handling routines go HERE, not in g_main.c !!!
	if (ent->s.weapon == WP_KNIFE) {
		if (other->takedamage && other->client) {
			// Elder: must add it in here if we remove it from above
			// NiceAss: Fixed knife-leg damage bug here. Passed it the wrong vector I guess...
			G_Damage(other, ent, &g_entities[ent->r.ownerNum], velocity, ent->r.currentOrigin, THROW_DAMAGE,
				 0, MOD_KNIFE_THROWN);
			//hit a player - send the gurgle or embedding sound event
		} else {
			vec3_t temp;
			vec3_t knifeOffset;
			vec3_t knifeVelocity;
			vec3_t origin;

			//missed throw or hit func_breakable;
			//spawn a knife at its trajectory end-point
			xr_item = BG_FindItemForWeapon(WP_KNIFE);

			G_EvaluateTrajectoryDelta(&ent->s.pos, level.time, knifeVelocity);

			//Makro - added check for unbreakable breakables/breakables with high health
			if (other->s.eType == ET_BREAKABLE && !other->unbreakable && other->health <= THROW_DAMAGE) {
				VectorCopy(trace->endpos, origin);
				G_Damage(other, ent, &g_entities[ent->r.ownerNum], velocity, origin, THROW_DAMAGE, 0,
					 MOD_KNIFE_THROWN);

				// NiceAss: Find current position and set it. 
				VectorCopy(trace->endpos, ent->s.pos.trBase);
				ent->s.pos.trTime = level.time;
				// And cut the velocity down.
				VectorScale(ent->s.pos.trDelta, .2, ent->s.pos.trDelta);
				return;
			} else {
				//leave embedded in the wall
				xr_drop = LaunchItem(xr_item, trace->endpos, 0, FL_THROWN_KNIFE | FL_DROPPED_ITEM);
				VectorClear(xr_drop->s.pos.trDelta);

				//Elder: make the knife stick out a bit more
				//and transfer into shared entityState
				VectorCopy(knifeVelocity, temp);
				VectorNormalize(temp);
				VectorScale(temp, -4, temp);
				VectorAdd(trace->endpos, temp, knifeOffset);

				//VectorCopy(xr_drop->s.origin, temp);
				VectorAdd(xr_drop->s.origin, knifeOffset, xr_drop->s.origin);

				//Makro - "hurt" the breakable if needed
				if (other->s.eType == ET_BREAKABLE) {
					VectorCopy(trace->endpos, origin);
					G_Damage(other, ent, &g_entities[ent->r.ownerNum], velocity, origin,
						 THROW_DAMAGE, 0, MOD_KNIFE_THROWN);
				}

				if (other->s.eType == ET_PRESSURE)
					G_CreatePressure(xr_drop->s.origin, trace->plane.normal,
							 &g_entities[trace->entityNum]);
			}

			//Elder: transfer entity data into the shared entityState
			//They are rotated on the client side in cg_ents.c

			//G_Printf("movedir: %s\n", vtos(ent->s.pos.trDelta));
			xr_drop->s.eFlags = xr_drop->flags;

			//vectoangles( trace->plane.normal, xr_drop->s.angles );

			vectoangles(knifeVelocity, xr_drop->s.angles);
			xr_drop->s.angles[0] += 90;
		}
	}

	ent->freeAfterEvent = qtrue;

	// change over to a normal entity right at the point of impact
	ent->s.eType = ET_GENERAL;

	SnapVectorTowards(trace->endpos, ent->s.pos.trBase);	// save net bandwidth

	G_SetOrigin(ent, trace->endpos);

	// splash damage (doesn't apply to person directly hit)
	if (ent->splashDamage) {
		if (G_RadiusDamage(trace->endpos, ent->parent, ent->splashDamage, ent->splashRadius,
				   other, ent->splashMethodOfDeath)) {
			if (!hitClient) {
				g_entities[ent->r.ownerNum].client->accuracy_hits++;
				// Elder: Statistics tracking
				if (ent->s.weapon == WP_KNIFE &&
						((g_gametype.integer == GT_TEAMPLAY && level.team_round_going) || g_gametype.integer != GT_TEAMPLAY))
					g_entities[ent->r.ownerNum].client->pers.records[REC_KNIFETHROWHITS]++;
				//g_entities[ent->r.ownerNum].client->knifeHits++;
				if (ent->s.weapon == WP_GRENADE &&
						((g_gametype.integer == GT_TEAMPLAY && level.team_round_going) || g_gametype.integer != GT_TEAMPLAY))
					g_entities[ent->r.ownerNum].client->pers.records[REC_GRENADEHITS]++;
				//g_entities[ent->r.ownerNum].client->grenHits++;
			}
		}
	}

	trap_RQ3LinkEntity(ent, __LINE__, __FILE__);
}

/*
================
G_RunMissile
================
*/
void G_RunMissile(gentity_t * ent)
{
	vec3_t origin;
	trace_t tr;
	int passent;

	// get current position
	G_EvaluateTrajectory(&ent->s.pos, level.time, origin);

	// if this missile bounced off an invulnerability sphere
	if (ent->target_ent) {
		passent = ent->target_ent->s.number;
	} else {
		// ignore interactions with the missile owner
		passent = ent->r.ownerNum;
	}
	// trace a line from the previous position to the current position
	trap_Trace(&tr, ent->r.currentOrigin, ent->r.mins, ent->r.maxs, origin, passent, ent->clipmask);

	if (tr.startsolid || tr.allsolid) {
		// make sure the tr.entityNum is set to the entity we're stuck in
		trap_Trace(&tr, ent->r.currentOrigin, ent->r.mins, ent->r.maxs, ent->r.currentOrigin, passent,
			   ent->clipmask);
		tr.fraction = 0;
	} else {
		VectorCopy(tr.endpos, ent->r.currentOrigin);
	}

	trap_RQ3LinkEntity(ent, __LINE__, __FILE__);

	if (tr.fraction != 1) {
		// never explode or bounce on sky
		if (tr.surfaceFlags & SURF_NOIMPACT) {
			// If grapple, reset owner
			if (ent->parent && ent->parent->client && ent->parent->client->hook == ent) {
				ent->parent->client->hook = NULL;
			}
			G_FreeEntity(ent);
			return;
		}
		G_MissileImpact(ent, &tr);
		if (ent->s.eType != ET_MISSILE) {
			return;	// exploded
		}
	}

	// check think function after bouncing
	G_RunThink(ent);
}

//=============================================================================

/*
=================
fire_grenade
=================
*/
gentity_t *fire_grenade(gentity_t * self, vec3_t start, vec3_t dir)
{
	gentity_t *bolt;
	int speed = 0;
	vec3_t up, right;

	if (self->client)
		AngleVectors(self->client->ps.viewangles, NULL, right, up);
	else {
		// just in case we put those shooters back
		up[0] = up[1] = up[2] = 0;
		right[0] = right[1] = right[2] = 0;
	}

	VectorNormalize(dir);

	bolt = G_Spawn();
	bolt->classname = "grenade";
	bolt->nextthink = level.time + 2000;	// Action had 2 seconds
	bolt->think = G_ExplodeMissile;
	bolt->s.eType = ET_MISSILE;
	bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	bolt->s.weapon = WP_GRENADE;
	bolt->s.eFlags = EF_BOUNCE_HALF;
	bolt->r.ownerNum = self->s.number;
	bolt->s.otherEntityNum = self->s.number;
	bolt->parent = self;
	bolt->damage = GRENADE_DAMAGE;	//probably only used on a direct hit
	bolt->splashDamage = GRENADE_SPLASH_DAMAGE;	//Blaze: Reaction Grenade Damage
	bolt->splashRadius = GRENADE_SPLASH_RADIUS;	//Blaze: changed from 150 was 170, but I uped it some more
	bolt->methodOfDeath = MOD_GRENADE;
	bolt->splashMethodOfDeath = MOD_GRENADE_SPLASH;
	bolt->clipmask = MASK_SHOT;
	bolt->target_ent = NULL;

	bolt->s.pos.trType = TR_GRAVITY;
	bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;	// move a bit on the very first frame
	VectorCopy(start, bolt->s.pos.trBase);

	//Elder: grenade toggle distances/speeds
	if (self->client) {
		// Elder: Statistics tracking
		if ((g_gametype.integer == GT_TEAMPLAY && level.team_round_going) || g_gametype.integer != GT_TEAMPLAY)
			self->client->pers.records[REC_GRENADESHOTS]++;
		if (self->client->ps.stats[STAT_HEALTH] <= 0 ||
		    self->client->ps.weaponstate == WEAPON_BANDAGING ||
		    // NiceAss: Should catch any case of switching weapons with a grenade "cocked"
		    self->client->ps.weaponstate == WEAPON_DROPPING) {
			//Always drop close range if dead or about to bandage
			speed = GRENADE_SHORT_SPEED / 2;
		} else if ((self->client->ps.persistant[PERS_WEAPONMODES] & RQ3_GRENSHORT) == RQ3_GRENSHORT &&
			   (self->client->ps.persistant[PERS_WEAPONMODES] & RQ3_GRENMED) == RQ3_GRENMED) {
			//Long range throw
			speed = GRENADE_LONG_SPEED;
		} else if ((self->client->ps.persistant[PERS_WEAPONMODES] & RQ3_GRENSHORT) == RQ3_GRENSHORT) {
			//Short range throw
			speed = GRENADE_SHORT_SPEED;
		} else if ((self->client->ps.persistant[PERS_WEAPONMODES] & RQ3_GRENMED) == RQ3_GRENMED) {
			//Medium range throw
			speed = GRENADE_MEDIUM_SPEED;
		} else {
			//Elder: shouldn't be here
			G_Printf("fire_grenade: Did not receive a grenade parm\n");
			speed = GRENADE_MEDIUM_SPEED;
		}
	}

	VectorScale(dir, speed, bolt->s.pos.trDelta);
	VectorMA(bolt->s.pos.trDelta, 200 + crandom() * 10.0f, up, bolt->s.pos.trDelta);
	VectorMA(bolt->s.pos.trDelta, crandom() * 10.0f, right, bolt->s.pos.trDelta);
	SnapVector(bolt->s.pos.trDelta);	// save net bandwidth

	VectorCopy(start, bolt->r.currentOrigin);

	return bolt;
}

gentity_t *fire_knife(gentity_t * self, vec3_t start, vec3_t dir)
{

	gentity_t *bolt;

	VectorNormalize(dir);

	bolt = G_Spawn();
	bolt->classname = "weapon_knife";
	bolt->nextthink = level.time + 10000;
	bolt->think = G_FreeEntity;
	bolt->s.eType = ET_MISSILE;
	bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	bolt->s.weapon = WP_KNIFE;
	bolt->r.ownerNum = self->s.number;
	bolt->s.otherEntityNum = self->s.number;
	bolt->parent = self;
	bolt->damage = THROW_DAMAGE;
	bolt->splashDamage = 0;
	bolt->splashRadius = 0;
	bolt->methodOfDeath = MOD_KNIFE_THROWN;
	bolt->clipmask = MASK_SHOT;
	bolt->target_ent = NULL;
	bolt->count = 1;
	bolt->s.pos.trType = TR_GRAVITY;
	bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;	// move a bit on the very first frame
	VectorCopy(start, bolt->s.pos.trBase);
	VectorScale(dir, THROW_SPEED, bolt->s.pos.trDelta);
	SnapVector(bolt->s.pos.trDelta);	// save net bandwidth
	VectorCopy(start, bolt->r.currentOrigin);

	VectorCopy(dir, bolt->s.apos.trBase);
	VectorCopy(dir, bolt->r.currentAngles);

	if (self->client && ((g_gametype.integer == GT_TEAMPLAY && level.team_round_going) || g_gametype.integer != GT_TEAMPLAY)) {
		// Elder: Statistics tracking
		self->client->pers.records[REC_KNIFETHROWSHOTS]++;
	}

	return bolt;
}
