//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
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

int GetMaterialFromFlag( int flag );
qboolean IsMetalMat( int Material );
qboolean IsMetalFlag( int flag );

#define	MISSILE_PRESTEP_TIME	50

/*
================
G_BounceMissile

================
*/
void G_BounceMissile( gentity_t *ent, trace_t *trace ) {
	vec3_t	velocity;
	float	dot;
	int		hitTime;

	// reflect the velocity on the trace plane
	hitTime = level.previousTime + ( level.time - level.previousTime ) * trace->fraction;
	G_EvaluateTrajectoryDelta( &ent->s.pos, hitTime, velocity );
	dot = DotProduct( velocity, trace->plane.normal );
	VectorMA( velocity, -2*dot, trace->plane.normal, ent->s.pos.trDelta );

	if ( ent->s.eFlags & EF_BOUNCE_HALF ) {
		VectorScale( ent->s.pos.trDelta, 0.65, ent->s.pos.trDelta );
		// check for stop
		if ( trace->plane.normal[2] > 0.2 && VectorLength( ent->s.pos.trDelta ) < 40 ) {
			G_SetOrigin( ent, trace->endpos );
			return;
		}
	}

	VectorAdd( ent->r.currentOrigin, trace->plane.normal, ent->r.currentOrigin);
	VectorCopy( ent->r.currentOrigin, ent->s.pos.trBase );
	ent->s.pos.trTime = level.time;
}


/*
================
G_ExplodeMissile

Explode a missile without an impact
================
*/
void G_ExplodeMissile( gentity_t *ent ) {
	vec3_t		dir;
	vec3_t		origin;

	G_EvaluateTrajectory( &ent->s.pos, level.time, origin );
	SnapVector( origin );
	G_SetOrigin( ent, origin );

	// we don't have a valid direction, so just point straight up
	dir[0] = dir[1] = 0;
	dir[2] = 1;

	ent->s.eType = ET_GENERAL;
	G_AddEvent( ent, EV_MISSILE_MISS, DirToByte( dir ) );

	ent->freeAfterEvent = qtrue;

	// splash damage
	if ( ent->splashDamage ) {
		if( G_RadiusDamage( ent->r.currentOrigin, ent->parent, ent->splashDamage, ent->splashRadius, ent
			, ent->splashMethodOfDeath ) ) {
			g_entities[ent->r.ownerNum].client->accuracy_hits++;
			// Elder: Statistics tracking
			if (ent->s.weapon == WP_KNIFE && level.team_round_going)
				g_entities[ent->r.ownerNum].client->pers.records[REC_KNIFETHROWHITS]++;
				//g_entities[ent->r.ownerNum].client->knifeHits++;
			if (ent->s.weapon == WP_GRENADE && level.team_round_going)
				g_entities[ent->r.ownerNum].client->pers.records[REC_GRENADEHITS]++;
				//g_entities[ent->r.ownerNum].client->grenHits++;
		}
	}
	//Elder: huhh?
	//G_Printf("exploding knife\n");
	trap_LinkEntity( ent );
}


#ifdef MISSIONPACK
/*
================
ProximityMine_Explode
================
*/
static void ProximityMine_Explode( gentity_t *mine ) {
	G_ExplodeMissile( mine );
	// if the prox mine has a trigger free it
	if (mine->activator) {
		G_FreeEntity(mine->activator);
		mine->activator = NULL;
	}
}

/*
================
ProximityMine_Die
================
*/
static void ProximityMine_Die( gentity_t *ent, gentity_t *inflictor, gentity_t *attacker, int damage, int mod ) {
	ent->think = ProximityMine_Explode;
	ent->nextthink = level.time + 1;
}

/*
================
ProximityMine_Trigger
================
*/
void ProximityMine_Trigger( gentity_t *trigger, gentity_t *other, trace_t *trace ) {
	vec3_t		v;
	gentity_t	*mine;

	if( !other->client ) {
		return;
	}

	// trigger is a cube, do a distance test now to act as if it's a sphere
	VectorSubtract( trigger->s.pos.trBase, other->s.pos.trBase, v );
	if( VectorLength( v ) > trigger->parent->splashRadius ) {
		return;
	}


	if ( g_gametype.integer >= GT_TEAM ) {
		// don't trigger same team mines
		if (trigger->parent->s.generic1 == other->client->sess.sessionTeam) {
			return;
		}
	}

	// ok, now check for ability to damage so we don't get triggered thru walls, closed doors, etc...
	if( !CanDamage( other, trigger->s.pos.trBase ) ) {
		return;
	}

	// trigger the mine!
	mine = trigger->parent;
	mine->s.loopSound = 0;
	G_AddEvent( mine, EV_PROXIMITY_MINE_TRIGGER, 0 );
	mine->nextthink = level.time + 500;

	G_FreeEntity( trigger );
}

/*
================
ProximityMine_Activate
================
*/
static void ProximityMine_Activate( gentity_t *ent ) {
	gentity_t	*trigger;
	float		r;

	ent->think = ProximityMine_Explode;
	ent->nextthink = level.time + g_proxMineTimeout.integer;

	ent->takedamage = qtrue;
	ent->health = 1;
	ent->die = ProximityMine_Die;

	//Elder: removed
	//ent->s.loopSound = G_SoundIndex( "sound/weapons/proxmine/wstbtick.wav" );

	// build the proximity trigger
	trigger = G_Spawn ();

	trigger->classname = "proxmine_trigger";

	r = ent->splashRadius;
	VectorSet( trigger->r.mins, -r, -r, -r );
	VectorSet( trigger->r.maxs, r, r, r );

	G_SetOrigin( trigger, ent->s.pos.trBase );

	trigger->parent = ent;
	trigger->r.contents = CONTENTS_TRIGGER;
	trigger->touch = ProximityMine_Trigger;

	trap_LinkEntity (trigger);

	// set pointer to trigger so the entity can be freed when the mine explodes
	ent->activator = trigger;
}

/*
================
ProximityMine_ExplodeOnPlayer
================
*/
static void ProximityMine_ExplodeOnPlayer( gentity_t *mine ) {
	gentity_t	*player;

	player = mine->enemy;
	player->client->ps.eFlags &= ~EF_TICKING;

	if ( player->client->invulnerabilityTime > level.time ) {
		G_Damage( player, mine->parent, mine->parent, vec3_origin, mine->s.origin, 1000, DAMAGE_NO_KNOCKBACK, MOD_JUICED );
		player->client->invulnerabilityTime = 0;
		G_TempEntity( player->client->ps.origin, EV_JUICED );
	}
	else {
		G_SetOrigin( mine, player->s.pos.trBase );
		// make sure the explosion gets to the client
		mine->r.svFlags &= ~SVF_NOCLIENT;
		mine->splashMethodOfDeath = MOD_PROXIMITY_MINE;
		G_ExplodeMissile( mine );
	}
}

/*
================
ProximityMine_Player
================
*/
static void ProximityMine_Player( gentity_t *mine, gentity_t *player ) {
	if( mine->s.eFlags & EF_NODRAW ) {
		return;
	}

	G_AddEvent( mine, EV_PROXIMITY_MINE_STICK, 0 );

	if( player->s.eFlags & EF_TICKING ) {
		player->activator->splashDamage += mine->splashDamage;
		player->activator->splashRadius *= 1.50;
		mine->think = G_FreeEntity;
		mine->nextthink = level.time;
		return;
	}

	player->client->ps.eFlags |= EF_TICKING;
	player->activator = mine;

	mine->s.eFlags |= EF_NODRAW;
	mine->r.svFlags |= SVF_NOCLIENT;
	mine->s.pos.trType = TR_LINEAR;
	VectorClear( mine->s.pos.trDelta );

	mine->enemy = player;
	mine->think = ProximityMine_ExplodeOnPlayer;
	if ( player->client->invulnerabilityTime > level.time ) {
		mine->nextthink = level.time + 2 * 1000;
	}
	else {
		mine->nextthink = level.time + 10 * 1000;
	}
}
#endif

/*
================
G_MissileImpact
================
*/
void G_MissileImpact( gentity_t *ent, trace_t *trace ) {
	gentity_t		*other;
	qboolean		hitClient = qfalse;
	vec3_t			velocity;
#ifdef MISSIONPACK
	vec3_t			forward, impactpoint, bouncedir;
	int				eFlags;
#endif
	//Elder: added for thrown knife condition
	gitem_t		*xr_item;
	gentity_t	*xr_drop;

	other = &g_entities[trace->entityNum];

	//Elder: no grenade explosion on impact
	if ( ent->s.weapon == WP_GRENADE &&
		( ent->s.eFlags & ( EF_BOUNCE | EF_BOUNCE_HALF ) ) ) {
		G_BounceMissile( ent, trace );
		G_AddEvent( ent, EV_GRENADE_BOUNCE, 0 );
		return;
	}

	//Elder: regular Q3 grenades
	// check for bounce
	/*
	if ( !other->takedamage &&
		( ent->s.eFlags & ( EF_BOUNCE | EF_BOUNCE_HALF ) ) ) {
		G_BounceMissile( ent, trace );
		G_AddEvent( ent, EV_GRENADE_BOUNCE, 0 );
		return;
	}
	*/

#ifdef MISSIONPACK
	if ( other->takedamage ) {
		if ( ent->s.weapon != WP_PROX_LAUNCHER ) {
			if ( other->client && other->client->invulnerabilityTime > level.time ) {
				//
				VectorCopy( ent->s.pos.trDelta, forward );
				VectorNormalize( forward );
				if (G_InvulnerabilityEffect( other, forward, ent->s.pos.trBase, impactpoint, bouncedir )) {
					VectorCopy( bouncedir, trace->plane.normal );
					eFlags = ent->s.eFlags & EF_BOUNCE_HALF;
					ent->s.eFlags &= ~EF_BOUNCE_HALF;
					G_BounceMissile( ent, trace );
					ent->s.eFlags |= eFlags;
				}
				ent->target_ent = other;
				return;
			}
		}
	}
#endif
	// impact damage
	if (other->takedamage) {
		// FIXME: wrong damage direction?
		if ( ent->damage ) {
			if( LogAccuracyHit( other, &g_entities[ent->r.ownerNum] ) ) {
				g_entities[ent->r.ownerNum].client->accuracy_hits++;
				// Elder: Statistics tracking
				if (ent->s.weapon == WP_KNIFE && level.team_round_going)
					g_entities[ent->r.ownerNum].client->pers.records[REC_KNIFETHROWHITS]++;
					//g_entities[ent->r.ownerNum].client->knifeHits++;
				if (ent->s.weapon == WP_GRENADE && level.team_round_going)
					g_entities[ent->r.ownerNum].client->pers.records[REC_GRENADEHITS]++;
					//g_entities[ent->r.ownerNum].client->grenHits++;
				hitClient = qtrue;
			}
			G_EvaluateTrajectoryDelta( &ent->s.pos, level.time, velocity );
			if ( VectorLength( velocity ) == 0 ) {
				velocity[2] = 1;	// stepped on a grenade
			}

			//Elder: added
			//Blaze: Moved down into the section where it actually hits the glass, otherwise the breakable entity is gone when it checks for it
			/*if ( ent->s.weapon == WP_KNIFE && other->s.eType == ET_BREAKABLE ) {
				G_Damage (other, ent, &g_entities[ent->r.ownerNum], velocity,
							ent->s.origin, ent->damage, 0, ent->methodOfDeath);
			}*/
		}
	}

#ifdef MISSIONPACK
	if( ent->s.weapon == WP_PROX_LAUNCHER ) {
		if( ent->s.pos.trType != TR_GRAVITY ) {
			return;
		}

		// if it's a player, stick it on to them (flag them and remove this entity)
		if( other->s.eType == ET_PLAYER && other->health > 0 ) {
			ProximityMine_Player( ent, other );
			return;
		}

		SnapVectorTowards( trace->endpos, ent->s.pos.trBase );
		G_SetOrigin( ent, trace->endpos );
		ent->s.pos.trType = TR_STATIONARY;
		VectorClear( ent->s.pos.trDelta );

		G_AddEvent( ent, EV_PROXIMITY_MINE_STICK, trace->surfaceFlags );

		ent->think = ProximityMine_Activate;
		ent->nextthink = level.time + 2000;

		vectoangles( trace->plane.normal, ent->s.angles );
		ent->s.angles[0] += 90;

		// link the prox mine to the other entity
		ent->enemy = other;
		ent->die = ProximityMine_Die;
		VectorCopy(trace->plane.normal, ent->movedir);
		VectorSet(ent->r.mins, -4, -4, -4);
		VectorSet(ent->r.maxs, 4, 4, 4);
		trap_LinkEntity(ent);

		return;
	}
#endif

	if (!strcmp(ent->classname, "hook")) {
		gentity_t *nent;
		vec3_t v;

		nent = G_Spawn();
		if ( other->takedamage && other->client ) {

			G_AddEvent( nent, EV_MISSILE_HIT, DirToByte( trace->plane.normal ) );
			nent->s.otherEntityNum = other->s.number;

			ent->enemy = other;

			v[0] = other->r.currentOrigin[0] + (other->r.mins[0] + other->r.maxs[0]) * 0.5;
			v[1] = other->r.currentOrigin[1] + (other->r.mins[1] + other->r.maxs[1]) * 0.5;
			v[2] = other->r.currentOrigin[2] + (other->r.mins[2] + other->r.maxs[2]) * 0.5;

			SnapVectorTowards( v, ent->s.pos.trBase );	// save net bandwidth
		} else {
			VectorCopy(trace->endpos, v);
			G_AddEvent( nent, EV_MISSILE_MISS, DirToByte( trace->plane.normal ) );
			ent->enemy = NULL;
		}

		SnapVectorTowards( v, ent->s.pos.trBase );	// save net bandwidth

		nent->freeAfterEvent = qtrue;
		// change over to a normal entity right at the point of impact
		nent->s.eType = ET_GENERAL;
		ent->s.eType = ET_GRAPPLE;

		G_SetOrigin( ent, v );
		G_SetOrigin( nent, v );

		//Blaze: Hook dosent exist any more
		//ent->think = Weapon_HookThink;
		ent->nextthink = level.time + FRAMETIME;

		ent->parent->client->ps.pm_flags |= PMF_GRAPPLE_PULL;
		VectorCopy( ent->r.currentOrigin, ent->parent->client->ps.grapplePoint);

		trap_LinkEntity( ent );
		trap_LinkEntity( nent );

		return;
	}

	// is it cheaper in bandwidth to just remove this ent and create a new
	// one, rather than changing the missile into the explosion?

	//Elder: I don't know but that's what we did for the knife
	if ( other->takedamage && other->client ) {
		G_AddEvent( ent, EV_MISSILE_HIT, DirToByte( trace->plane.normal ) );
		ent->s.otherEntityNum = other->s.number;
	//Makro - new surfaceparm system
	//} else if( trace->surfaceFlags & SURF_METALSTEPS ) {
	} else if( IsMetalFlag(trace->surfaceFlags) ) {
		G_AddEvent( ent, EV_MISSILE_MISS_METAL, DirToByte( trace->plane.normal ) );
	} else {
		G_AddEvent( ent, EV_MISSILE_MISS, DirToByte( trace->plane.normal ) );
	}

	//Elder: knife handling routines go HERE, not in g_main.c !!!
	if (ent->s.weapon == WP_KNIFE) {
		if ( other->takedamage && other->client) {
			// Elder: must add it in here if we remove it from above
			// NiceAss: Fixed knife-leg damage bug here. Passed it the wrong vector I guess...
			G_Damage (other, ent, &g_entities[ent->r.ownerNum], velocity, ent->r.currentOrigin, THROW_DAMAGE, 0, MOD_KNIFE_THROWN);
			//hit a player - send the gurgle or embedding sound event
		}
		else {
			vec3_t temp;
			vec3_t knifeOffset;
			vec3_t knifeVelocity;
			vec3_t origin;
			//missed throw or hit func_breakable;
			//spawn a knife at its trajectory end-point
			xr_item = BG_FindItemForWeapon( WP_KNIFE );

			G_EvaluateTrajectoryDelta(&ent->s.pos, level.time, knifeVelocity);

			if (other->s.eType == ET_BREAKABLE) {
				VectorCopy(trace->endpos, origin);
				G_Damage (other, ent, &g_entities[ent->r.ownerNum], velocity, origin, THROW_DAMAGE, 0, MOD_KNIFE_THROWN);

				// NiceAss: Find current position and set it. 
				VectorCopy(trace->endpos, ent->s.pos.trBase);
				ent->s.pos.trTime = level.time;
				// And cut the velocity down.
				VectorScale(ent->s.pos.trDelta, .2, ent->s.pos.trDelta);
				return;
				/*  OLD METHOD
				//breakable "hit"; make it fall to the ground
				xr_drop = LaunchItem(xr_item, trace->endpos, velocity, FL_DROPPED_ITEM);

				//but still set it as a thrown knife
				//xr_drop->flags |= FL_THROWN_KNIFE;

				//Elder: move the knife back a bit more
				//and transfer into shared entityState
				VectorScale(trace->plane.normal, 16, temp);
				VectorAdd(trace->endpos, temp, knifeOffset);

				//VectorCopy(xr_drop->s.origin, temp);
				VectorAdd(xr_drop->s.origin, knifeOffset, xr_drop->s.origin);

				VectorCopy(xr_drop->s.origin, xr_drop->r.currentOrigin);
				*/
			}
			else {
				//leave embedded in the wall
				xr_drop = LaunchItem(xr_item, trace->endpos, 0, FL_THROWN_KNIFE|FL_DROPPED_ITEM);
				VectorClear( xr_drop->s.pos.trDelta );

				//Elder: make the knife stick out a bit more
				//and transfer into shared entityState
				VectorCopy(knifeVelocity, temp);
				VectorNormalize(temp);
				VectorScale(temp, -4, temp);
				VectorAdd(trace->endpos, temp, knifeOffset);

				//VectorCopy(xr_drop->s.origin, temp);
				VectorAdd(xr_drop->s.origin, knifeOffset, xr_drop->s.origin);

				if ( other->s.eType == ET_PRESSURE )
					G_CreatePressure(xr_drop->s.origin, trace->plane.normal, &g_entities[trace->entityNum]);
			}

			//Elder: transfer entity data into the shared entityState
			//They are rotated on the client side in cg_ents.c

			//G_Printf("movedir: %s\n", vtos(ent->s.pos.trDelta));
			xr_drop->s.eFlags = xr_drop->flags;

			//vectoangles( trace->plane.normal, xr_drop->s.angles );

			vectoangles( knifeVelocity, xr_drop->s.angles);
			xr_drop->s.angles[0] += 90;
		}
	}

	ent->freeAfterEvent = qtrue;

	// change over to a normal entity right at the point of impact
	ent->s.eType = ET_GENERAL;

	SnapVectorTowards( trace->endpos, ent->s.pos.trBase );	// save net bandwidth

	G_SetOrigin( ent, trace->endpos );

	// splash damage (doesn't apply to person directly hit)
	if ( ent->splashDamage ) {
		if( G_RadiusDamage( trace->endpos, ent->parent, ent->splashDamage, ent->splashRadius,
			other, ent->splashMethodOfDeath ) ) {
			if( !hitClient ) {
				g_entities[ent->r.ownerNum].client->accuracy_hits++;
				// Elder: Statistics tracking
				if (ent->s.weapon == WP_KNIFE && level.team_round_going)
					g_entities[ent->r.ownerNum].client->pers.records[REC_KNIFETHROWHITS]++;
					//g_entities[ent->r.ownerNum].client->knifeHits++;
				if (ent->s.weapon == WP_GRENADE && level.team_round_going)
					g_entities[ent->r.ownerNum].client->pers.records[REC_GRENADEHITS]++;
					//g_entities[ent->r.ownerNum].client->grenHits++;
			}
		}
	}

	trap_LinkEntity( ent );
}

/*
================
G_ExplodeMissile

Explode a missile without an impact
================
*/
/*
void G_ExplodeMissile( gentity_t *ent ) {
	vec3_t		dir;
	vec3_t		origin;

	G_EvaluateTrajectory( &ent->s.pos, level.time, origin );
	SnapVector( origin );
	G_SetOrigin( ent, origin );

	// we don't have a valid direction, so just point straight up
	dir[0] = dir[1] = 0;
	dir[2] = 1;

	ent->s.eType = ET_GENERAL;
	G_AddEvent( ent, EV_MISSILE_MISS, DirToByte( dir ) );

	ent->freeAfterEvent = qtrue;

	// splash damage
	if ( ent->splashDamage ) {
		if( G_RadiusDamage( ent->r.currentOrigin, ent->parent, ent->splashDamage, ent->splashRadius, NULL
			, ent->splashMethodOfDeath ) ) {
			g_entities[ent->r.ownerNum].client->ps.persistant[PERS_ACCURACY_HITS]++;
		}
	}

	trap_LinkEntity( ent );
}
*/

/*
================
G_RunMissile
================
*/
void G_RunMissile( gentity_t *ent ) {
	vec3_t		origin;
	trace_t		tr;
	int			passent;

	// get current position
	G_EvaluateTrajectory( &ent->s.pos, level.time, origin );

	// if this missile bounced off an invulnerability sphere
	if ( ent->target_ent ) {
		passent = ent->target_ent->s.number;
	}
#ifdef MISSIONPACK
	// prox mines that left the owner bbox will attach to anything, even the owner
	else if (ent->s.weapon == WP_PROX_LAUNCHER && ent->count) {
		passent = ENTITYNUM_NONE;
	}
#endif
	else {
		// ignore interactions with the missile owner
		passent = ent->r.ownerNum;
	}
	// trace a line from the previous position to the current position
	trap_Trace( &tr, ent->r.currentOrigin, ent->r.mins, ent->r.maxs, origin, passent, ent->clipmask );

	if ( tr.startsolid || tr.allsolid ) {
		// make sure the tr.entityNum is set to the entity we're stuck in
		trap_Trace( &tr, ent->r.currentOrigin, ent->r.mins, ent->r.maxs, ent->r.currentOrigin, passent, ent->clipmask );
		tr.fraction = 0;
	}
	else {
		VectorCopy( tr.endpos, ent->r.currentOrigin );
	}

	trap_LinkEntity( ent );

	if ( tr.fraction != 1 ) {
		// never explode or bounce on sky
		if ( tr.surfaceFlags & SURF_NOIMPACT ) {
			// If grapple, reset owner
			if (ent->parent && ent->parent->client && ent->parent->client->hook == ent) {
				ent->parent->client->hook = NULL;
			}
			G_FreeEntity( ent );
			return;
		}
		G_MissileImpact( ent, &tr );
		if ( ent->s.eType != ET_MISSILE ) {
			return;		// exploded
		}
	}

	//Elder: make knife follow the trajectory - not real but oh well...
	/* Done in CG_Missile locally to save bandwidth
	if (ent->classname == "weapon_knife")
	{
		vec3_t knifeVelocity;

		G_EvaluateTrajectoryDelta(&ent->s.pos, level.time, knifeVelocity);
		vectoangles(knifeVelocity, ent->s.angles);
		ent->s.angles[0] += level.time % 360;
	}
	*/

#ifdef MISSIONPACK
	// if the prox mine wasn't yet outside the player body
	if (ent->s.weapon == WP_PROX_LAUNCHER && !ent->count) {
		// check if the prox mine is outside the owner bbox
		trap_Trace( &tr, ent->r.currentOrigin, ent->r.mins, ent->r.maxs, ent->r.currentOrigin, ENTITYNUM_NONE, ent->clipmask );
		if (!tr.startsolid || tr.entityNum != ent->r.ownerNum) {
			ent->count = 1;
		}
	}
#endif
	// check think function after bouncing
		G_RunThink( ent );
}


//=============================================================================

/*
=================
fire_plasma

=================
*/
//Blaze: No plasma gun so no need for this function
/*
gentity_t *fire_plasma (gentity_t *self, vec3_t start, vec3_t dir) {
	gentity_t	*bolt;

	VectorNormalize (dir);

	bolt = G_Spawn();
	bolt->classname = "plasma";
	bolt->nextthink = level.time + 10000;
	bolt->think = G_ExplodeMissile;
	bolt->s.eType = ET_MISSILE;
	bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	bolt->s.weapon = WP_PLASMAGUN;
	bolt->r.ownerNum = self->s.number;
	bolt->parent = self;
	bolt->damage = 20;
	bolt->splashDamage = 15;
	bolt->splashRadius = 20;
	bolt->methodOfDeath = MOD_PLASMA;
	bolt->splashMethodOfDeath = MOD_PLASMA_SPLASH;
	bolt->clipmask = MASK_SHOT;
	bolt->target_ent = NULL;

	bolt->s.pos.trType = TR_LINEAR;
	bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;		// move a bit on the very first frame
	VectorCopy( start, bolt->s.pos.trBase );
	VectorScale( dir, 2000, bolt->s.pos.trDelta );
	SnapVector( bolt->s.pos.trDelta );			// save net bandwidth

	VectorCopy (start, bolt->r.currentOrigin);

	return bolt;
}
*/
//=============================================================================


/*
=================
fire_grenade
=================
*/
gentity_t *fire_grenade (gentity_t *self, vec3_t start, vec3_t dir) {
	gentity_t	*bolt;
	int speed = 0;
	vec3_t up, right;

	if (self->client)
		AngleVectors( self->client->ps.viewangles, NULL, right, up);
	else
	{
		// just in case we put those shooters back
		up[0] = up[1] = up[2] = 0;
		right[0] = right[1] = right[2] = 0;
	}

	VectorNormalize (dir);

	bolt = G_Spawn();
	bolt->classname = "grenade";
	bolt->nextthink = level.time + 2000; // Action had 2 seconds
	bolt->think = G_ExplodeMissile;
	bolt->s.eType = ET_MISSILE;
	bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	bolt->s.weapon = WP_GRENADE;
	bolt->s.eFlags = EF_BOUNCE_HALF;
	bolt->r.ownerNum = self->s.number;
	bolt->parent = self;
	bolt->damage = GRENADE_DAMAGE;	//probably only used on a direct hit
	bolt->splashDamage = GRENADE_SPLASH_DAMAGE;	//Blaze: Reaction Grenade Damage
	bolt->splashRadius = GRENADE_SPLASH_RADIUS; //Blaze: changed from 150 was 170, but I uped it some more
	bolt->methodOfDeath = MOD_GRENADE;
	bolt->splashMethodOfDeath = MOD_GRENADE_SPLASH;
	bolt->clipmask = MASK_SHOT;
	bolt->target_ent = NULL;

	bolt->s.pos.trType = TR_GRAVITY;
	bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;		// move a bit on the very first frame
	VectorCopy( start, bolt->s.pos.trBase );

	//Elder: grenade toggle distances/speeds
	if ( self->client) {
		// Elder: Statistics tracking
		if (level.team_round_going) self->client->pers.records[REC_GRENADESHOTS]++;
		if ( self->client->ps.stats[STAT_HEALTH] <= 0 ||
	//		(self->client->ps.stats[STAT_RQ3] & RQ3_BANDAGE_WORK) == RQ3_BANDAGE_WORK ||
			self->client->ps.weaponstate == WEAPON_BANDAGING ||
			// NiceAss: Should catch any case of switching weapons with a grenade "cocked"
			self->client->ps.weaponstate == WEAPON_DROPPING ) {
			//Always drop close range if dead or about to bandage
			speed = GRENADE_SHORT_SPEED / 2;
		}
		else if ( (self->client->ps.persistant[PERS_WEAPONMODES] & RQ3_GRENSHORT) == RQ3_GRENSHORT &&
			(self->client->ps.persistant[PERS_WEAPONMODES] & RQ3_GRENMED) == RQ3_GRENMED) {
			//Long range throw
			speed = GRENADE_LONG_SPEED;
		}
		else if ( (self->client->ps.persistant[PERS_WEAPONMODES] & RQ3_GRENSHORT) == RQ3_GRENSHORT) {
			//Short range throw
			speed = GRENADE_SHORT_SPEED;
		}
		else if ( (self->client->ps.persistant[PERS_WEAPONMODES] & RQ3_GRENMED) == RQ3_GRENMED) {
			//Medium range throw
			speed = GRENADE_MEDIUM_SPEED;
		}
		else {
			//Elder: shouldn't be here
			G_Printf("fire_grenade: Did not receive a grenade parm\n");
			speed = GRENADE_MEDIUM_SPEED;
		}
	}

	VectorScale( dir, speed, bolt->s.pos.trDelta );
	VectorMA (bolt->s.pos.trDelta, 200 + crandom() * 10.0f, up, bolt->s.pos.trDelta);
    VectorMA (bolt->s.pos.trDelta, crandom() * 10.0f, right, bolt->s.pos.trDelta);
	SnapVector( bolt->s.pos.trDelta );			// save net bandwidth


	VectorCopy (start, bolt->r.currentOrigin);

	return bolt;
}

gentity_t *fire_knife (gentity_t *self, vec3_t start, vec3_t dir)
{

    gentity_t   *bolt;

    VectorNormalize (dir);

    bolt = G_Spawn();
    bolt->classname = "weapon_knife";
    bolt->nextthink = level.time + 10000;
    bolt->think = G_FreeEntity;
    bolt->s.eType = ET_MISSILE;
	bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
    bolt->s.weapon = WP_KNIFE;
    bolt->r.ownerNum = self->s.number;
    bolt->parent = self;
	bolt->damage = THROW_DAMAGE;
	bolt->splashDamage = 0;
	bolt->splashRadius = 0;
    bolt->methodOfDeath = MOD_KNIFE_THROWN;
    bolt->clipmask = MASK_SHOT;
	bolt->target_ent = NULL;
	bolt->count = 1;
    bolt->s.pos.trType = TR_GRAVITY;
    bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;     // move a bit on the very first frame
    VectorCopy( start, bolt->s.pos.trBase );
    VectorScale( dir, THROW_SPEED, bolt->s.pos.trDelta );
    SnapVector( bolt->s.pos.trDelta );          // save net bandwidth
    VectorCopy (start, bolt->r.currentOrigin);

	VectorCopy (dir, bolt->s.apos.trBase);
	VectorCopy (dir, bolt->r.currentAngles);

	if (self->client && level.team_round_going)
	{
		// Elder: Statistics tracking
		self->client->pers.records[REC_KNIFETHROWSHOTS]++;
	}

	// bolt->s.pos.trDelta[2] *= .85;

	//Elder: not needed anymore
	//Saving stuff for Makro's knife equations
	//VectorCopy( start, bolt->s.origin2);
	//VectorCopy( dir, bolt->s.angles2);

    return bolt;
}

//=============================================================================


/*
=================
fire_bfg
=================
*/
//Blaze: no bfg
/*
gentity_t *fire_bfg (gentity_t *self, vec3_t start, vec3_t dir) {
	gentity_t	*bolt;

	VectorNormalize (dir);

	bolt = G_Spawn();
	bolt->classname = "bfg";
	bolt->nextthink = level.time + 10000;
	bolt->think = G_ExplodeMissile;
	bolt->s.eType = ET_MISSILE;
	bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	bolt->s.weapon = WP_BFG;
	bolt->r.ownerNum = self->s.number;
	bolt->parent = self;
	bolt->damage = 100;
	bolt->splashDamage = 100;
	bolt->splashRadius = 120;
	bolt->methodOfDeath = MOD_BFG;
	bolt->splashMethodOfDeath = MOD_BFG_SPLASH;
	bolt->clipmask = MASK_SHOT;
	bolt->target_ent = NULL;

	bolt->s.pos.trType = TR_LINEAR;
	bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;		// move a bit on the very first frame
	VectorCopy( start, bolt->s.pos.trBase );
	VectorScale( dir, 2000, bolt->s.pos.trDelta );
	SnapVector( bolt->s.pos.trDelta );			// save net bandwidth
	VectorCopy (start, bolt->r.currentOrigin);

	return bolt;
}
*/
//=============================================================================


/*
=================
fire_rocket
=================
*/
//Blaze: No need for this since there are no rockets
/*
gentity_t *fire_rocket (gentity_t *self, vec3_t start, vec3_t dir) {
	gentity_t	*bolt;

	VectorNormalize (dir);

	bolt = G_Spawn();
	bolt->classname = "rocket";
	bolt->nextthink = level.time + 15000;
	bolt->think = G_ExplodeMissile;
	bolt->s.eType = ET_MISSILE;
	bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	bolt->s.weapon = WP_ROCKET_LAUNCHER;
	bolt->r.ownerNum = self->s.number;
	bolt->parent = self;
	bolt->damage = 100;
	bolt->splashDamage = 100;
	bolt->splashRadius = 120;
	bolt->methodOfDeath = MOD_ROCKET;
	bolt->splashMethodOfDeath = MOD_ROCKET_SPLASH;
	bolt->clipmask = MASK_SHOT;
	bolt->target_ent = NULL;

	bolt->s.pos.trType = TR_LINEAR;
	bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;		// move a bit on the very first frame
	VectorCopy( start, bolt->s.pos.trBase );
	VectorScale( dir, 900, bolt->s.pos.trDelta );
	SnapVector( bolt->s.pos.trDelta );			// save net bandwidth
	VectorCopy (start, bolt->r.currentOrigin);

	return bolt;
}
*/
/*
=================
fire_grapple
=================
*/
//Blaze: no need for this since no grapple
/*
gentity_t *fire_grapple (gentity_t *self, vec3_t start, vec3_t dir) {
	gentity_t	*hook;

	VectorNormalize (dir);

	hook = G_Spawn();
	hook->classname = "hook";
	hook->nextthink = level.time + 10000;
	hook->think = Weapon_HookFree;
	hook->s.eType = ET_MISSILE;
	hook->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	hook->s.weapon = WP_GRAPPLING_HOOK;
	hook->r.ownerNum = self->s.number;
	hook->methodOfDeath = MOD_GRAPPLE;
	hook->clipmask = MASK_SHOT;
	hook->parent = self;
	hook->target_ent = NULL;

	hook->s.pos.trType = TR_LINEAR;
	hook->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;		// move a bit on the very first frame
	hook->s.otherEntityNum = self->s.number; // use to match beam in client
	VectorCopy( start, hook->s.pos.trBase );
	VectorScale( dir, 800, hook->s.pos.trDelta );
	SnapVector( hook->s.pos.trDelta );			// save net bandwidth
	VectorCopy (start, hook->r.currentOrigin);

	self->client->hook = hook;

	return hook;
}
*/


#ifdef MISSIONPACK
/*
=================
fire_nail
=================
*/
#define NAILGUN_SPREAD	500

gentity_t *fire_nail( gentity_t *self, vec3_t start, vec3_t forward, vec3_t right, vec3_t up ) {
	gentity_t	*bolt;
	vec3_t		dir;
	vec3_t		end;
	float		r, u, scale;

	bolt = G_Spawn();
	bolt->classname = "nail";
	bolt->nextthink = level.time + 10000;
	bolt->think = G_ExplodeMissile;
	bolt->s.eType = ET_MISSILE;
	bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	bolt->s.weapon = WP_NAILGUN;
	bolt->r.ownerNum = self->s.number;
	bolt->parent = self;
	bolt->damage = 20;
	bolt->methodOfDeath = MOD_NAIL;
	bolt->clipmask = MASK_SHOT;
	bolt->target_ent = NULL;

	bolt->s.pos.trType = TR_LINEAR;
	bolt->s.pos.trTime = level.time;
	VectorCopy( start, bolt->s.pos.trBase );

	r = random() * M_PI * 2.0f;
	u = sin(r) * crandom() * NAILGUN_SPREAD * 16;
	r = cos(r) * crandom() * NAILGUN_SPREAD * 16;
	VectorMA( start, 8192 * 16, forward, end);
	VectorMA (end, r, right, end);
	VectorMA (end, u, up, end);
	VectorSubtract( end, start, dir );
	VectorNormalize( dir );

	scale = 555 + random() * 1800;
	VectorScale( dir, scale, bolt->s.pos.trDelta );
	SnapVector( bolt->s.pos.trDelta );

	VectorCopy( start, bolt->r.currentOrigin );

	return bolt;
}


/*
=================
fire_prox
=================
*/
gentity_t *fire_prox( gentity_t *self, vec3_t start, vec3_t dir ) {
	gentity_t	*bolt;

	VectorNormalize (dir);

	bolt = G_Spawn();
	bolt->classname = "prox mine";
	bolt->nextthink = level.time + 3000;
	bolt->think = G_ExplodeMissile;
	bolt->s.eType = ET_MISSILE;
	bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	bolt->s.weapon = WP_PROX_LAUNCHER;
	bolt->s.eFlags = 0;
	bolt->r.ownerNum = self->s.number;
	bolt->parent = self;
	bolt->damage = 0;
	bolt->splashDamage = 100;
	bolt->splashRadius = 150;
	bolt->methodOfDeath = MOD_PROXIMITY_MINE;
	bolt->splashMethodOfDeath = MOD_PROXIMITY_MINE;
	bolt->clipmask = MASK_SHOT;
	bolt->target_ent = NULL;
	// count is used to check if the prox mine left the player bbox
	// if count == 1 then the prox mine left the player bbox and can attack to it
	bolt->count = 0;

	//FIXME: we prolly wanna abuse another field
	bolt->s.generic1 = self->client->sess.sessionTeam;

	bolt->s.pos.trType = TR_GRAVITY;
	bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;		// move a bit on the very first frame
	VectorCopy( start, bolt->s.pos.trBase );
	VectorScale( dir, 700, bolt->s.pos.trDelta );
	SnapVector( bolt->s.pos.trDelta );			// save net bandwidth

	VectorCopy (start, bolt->r.currentOrigin);

	return bolt;
}
#endif
