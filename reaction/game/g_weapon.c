// Copyright (C) 1999-2000 Id Software, Inc.
//
// g_weapon.c 
// perform the server side effects of a weapon firing

#include "g_local.h"

static	float	s_quadFactor;
static	vec3_t	forward, right, up;
static	vec3_t	muzzle;

//Elder: used for shell damage - we have no more malloc function so make it static?
int tookShellHit[MAX_CLIENTS];

#define NUM_NAILSHOTS 15

/*
================
G_BounceProjectile
================
*/
void G_BounceProjectile( vec3_t start, vec3_t impact, vec3_t dir, vec3_t endout ) {
	vec3_t v, newv;
	float dot;

	VectorSubtract( impact, start, v );
	dot = DotProduct( v, dir );
	VectorMA( v, -2*dot, dir, newv );

	VectorNormalize(newv);
	VectorMA(impact, 8192, newv, endout);
}


/*
======================================================================

RQ3_JumpKick
Moved from g_active.c to g_weapon.c
Because it is a weapon!

======================================================================
*/

qboolean JumpKick( gentity_t *ent )
{
	trace_t		tr;
	vec3_t		end;
	gentity_t	*tent;
	gentity_t	*traceEnt;
	int			damage;
	//Elder: for kick sound
	qboolean	kickSuccess;
	
	// set aiming directions
	AngleVectors (ent->client->ps.viewangles, forward, right, up);
	CalcMuzzlePoint ( ent, forward, right, up, muzzle );
	// Elder: AQ2 offset
	muzzle[2] -= (ent->client->ps.viewheight - 20);
	VectorMA (muzzle, 25, forward, end);
	//VectorMA (muzzle, 32, forward, end);
	
	//VectorCopy( ent->s.origin, muzzle );
	//muzzle[2] += 32;
	// the muzzle really isn't the right point to test the jumpkick from
	
	trap_Trace (&tr, muzzle, NULL, NULL, end, ent->s.number, MASK_SHOT);
	//trap_Trace (&tr, ent->s.origin, NULL, NULL, end, ent->s.number, MASK_SHOT);

	if ( tr.surfaceFlags & SURF_NOIMPACT ) {
		return qfalse;
	}

	kickSuccess = DoorKick( &tr, ent, muzzle, forward );
	traceEnt = &g_entities[ tr.entityNum ];

	if ( !traceEnt->takedamage) {
		return qfalse;
	}

	if (ent->client->ps.powerups[PW_QUAD] ) {
		G_AddEvent( ent, EV_POWERUP_QUAD, 0 );
		s_quadFactor = g_quadfactor.value;
	} else {
		s_quadFactor = 1;
	}

	damage = 20;

	if ( traceEnt->s.eType == ET_BREAKABLE || traceEnt->client)
		kickSuccess = qtrue;

	//Elder: can't hit if crouching but can still hit "dead" bodies :)
	if (traceEnt->client && traceEnt->health > 0 && traceEnt->r.maxs[2] < 20)
    {
		return qfalse;
    }
	else {
		G_Damage( traceEnt, ent, ent, forward, tr.endpos,
			damage, DAMAGE_NO_LOCATIONAL, MOD_KICK );
	}

	// send blood impact + event stuff
	/*
	if ( traceEnt->takedamage && traceEnt->client ) {
		//tent = G_TempEntity( tr.endpos, EV_MISSILE_HIT );
		tent = G_TempEntity( tr.endpos, EV_JUMPKICK );
		tent->s.otherEntityNum = traceEnt->s.number;
		tent->s.eventParm = DirToByte( tr.plane.normal );
		tent->s.weapon = ent->s.weapon;
	}
	*/

	if (traceEnt->client && traceEnt->takedamage)
	{
		tent = G_TempEntity( tr.endpos, EV_JUMPKICK );
		tent->s.otherEntityNum = traceEnt->s.number;
		tent->s.otherEntityNum2 = ent->s.number;
		tent->s.eventParm = DirToByte( tr.plane.normal );
		tent->s.weapon = 0;

		if (traceEnt->client->uniqueWeapons > 0)
		{
			//Elder: toss a unique weapon if kicked
			//Need to make sure to cancel any reload attempts - test this
			Cmd_Unzoom(traceEnt);
			traceEnt->client->fastReloads = 0;
			traceEnt->client->reloadAttempts = 0;
			traceEnt->client->ps.weaponTime = 0;

			//Set the entity's weapon to the target's weapon before he/she throws it
			tent->s.weapon = ThrowWeapon(traceEnt, qtrue);
		}
		
		// Don't need other sound event
		kickSuccess = qfalse;
	}



	//Elder: for the kick
	// do our special form of knockback here
	/*
        VectorMA (self->enemy->absmin, 0.5, self->enemy->size, v);
        VectorSubtract (v, point, v);
        VectorNormalize (v);
        VectorMA (self->enemy->velocity, kick, v, self->enemy->velocity);
        if (self->enemy->velocity[2] > 0)
                self->enemy->groundentity = NULL;
	*/
	//Elder: kick knockback for AQ2 -- recall variable kick = 400
	//if (traceEnt->client)
	//{
		//Elder: for kick knockback
		//vec3_t		size, vTemp;

		//Make the "size" vector - hopefully this is right
		//VectorSubtract(traceEnt->r.maxs, traceEnt->r.mins, size);
		//G_Printf("Size: %s\n", vtos(size));
		
		//VectorMA(traceEnt->r.absmin, 0.5, size, vTemp);
		//VectorSubtract(vTemp, tr.endpos, vTemp);
		//VectorNormalize(vTemp);
		//VectorMA(traceEnt->client->ps.velocity, 400, vTemp, traceEnt->client->ps.velocity);
		//if (traceEnt->client->ps.velocity[2] > 0)
			//traceEnt->s.groundEntityNum = ENTITYNUM_NONE;
	//}


	//Elder: Our set of locally called sounds
	if (kickSuccess)
	{
		G_AddEvent ( ent, EV_RQ3_SOUND, RQ3_SOUND_KICK);
	}

	return qtrue;
}

qboolean DoorKick( trace_t *trIn, gentity_t *ent, vec3_t origin, vec3_t forward )
{
	gentity_t *traceEnt;
	trace_t tr;

	traceEnt = &g_entities[ trIn->entityNum ];
	if ( Q_stricmp (traceEnt->classname, "func_door_rotating") == 0 )
	{
		vec3_t d_right, d_forward;
		float crossProduct;
		vec3_t end;

		// Find the hit point and the muzzle point with respect
		// to the door's origin, then project down to the XY plane
		// and take the cross product
		VectorSubtract( trIn->endpos, traceEnt->s.origin, d_right );
		VectorSubtract( origin, traceEnt->s.origin, d_forward );
		crossProduct = d_forward[0]*d_right[1]-d_right[0]*d_forward[1];

		// See if we are on the proper side to do it
		if ( ((traceEnt->pos2[1] > traceEnt->pos1[1]) && crossProduct > 0) || 
			 ((traceEnt->pos2[1] < traceEnt->pos1[1]) && crossProduct < 0))
		{
			Cmd_OpenDoor( ent );
			VectorMA( trIn->endpos, 25, forward, end );
			trap_Trace (&tr, trIn->endpos, NULL, NULL, end, trIn->entityNum, MASK_SHOT);
			if ( !(tr.surfaceFlags & SURF_NOIMPACT) )
			{
				traceEnt = &g_entities[ tr.entityNum ];
				if ( traceEnt->client )
				{
					*trIn = tr;
				}
			}
		}
		return qtrue;
	}
	else
		return qfalse;

}


/*
======================================================================

GAUNTLET

======================================================================
*/
/*
void Weapon_Gauntlet( gentity_t *ent ) {

}
*/
/*
===============
CheckGauntletAttack
===============
*/
qboolean CheckGauntletAttack( gentity_t *ent ) {
	trace_t		tr;
	vec3_t		end;
	gentity_t	*tent;
	gentity_t	*traceEnt;
	int			damage;

	// set aiming directions
	AngleVectors (ent->client->ps.viewangles, forward, right, up);

	CalcMuzzlePoint ( ent, forward, right, up, muzzle );

	VectorMA (muzzle, 32, forward, end);

	trap_Trace (&tr, muzzle, NULL, NULL, end, ent->s.number, MASK_SHOT);
	if ( tr.surfaceFlags & SURF_NOIMPACT ) {
		return qfalse;
	}

	traceEnt = &g_entities[ tr.entityNum ];

	// send blood impact
	if ( traceEnt->takedamage && traceEnt->client ) {
		tent = G_TempEntity( tr.endpos, EV_MISSILE_HIT );
		tent->s.otherEntityNum = traceEnt->s.number;
		tent->s.eventParm = DirToByte( tr.plane.normal );
		tent->s.weapon = ent->s.weapon;
	}

	if ( !traceEnt->takedamage) {
		return qfalse;
	}

	if (ent->client->ps.powerups[PW_QUAD] ) {
		G_AddEvent( ent, EV_POWERUP_QUAD, 0 );
		s_quadFactor = g_quadfactor.value;
	} else {
		s_quadFactor = 1;
	}
#ifdef MISSIONPACK
	if( ent->client->persistantPowerup && ent->client->persistantPowerup->item && ent->client->persistantPowerup->item->giTag == PW_DOUBLER ) {
		s_quadFactor *= 2;
	}
#endif

	damage = 50 * s_quadFactor;
	G_Damage( traceEnt, ent, ent, forward, tr.endpos,
		damage, 0, MOD_GAUNTLET );

	return qtrue;
}


/*
======================================================================

MACHINEGUN

======================================================================
*/

/*
======================
SnapVectorTowards

Round a vector to integers for more efficient network
transmission, but make sure that it rounds towards a given point
rather than blindly truncating.  This prevents it from truncating 
into a wall.
======================
*/
void SnapVectorTowards( vec3_t v, vec3_t to ) {
	int		i;

	for ( i = 0 ; i < 3 ; i++ ) {
		if ( to[i] <= v[i] ) {
			v[i] = (int)v[i];
		} else {
			v[i] = (int)v[i] + 1;
		}
	}
}

#ifdef MISSIONPACK
#define CHAINGUN_SPREAD		600
#endif
#define MACHINEGUN_SPREAD	200
#define	MACHINEGUN_DAMAGE	7
#define	MACHINEGUN_TEAM_DAMAGE	5		// wimpier MG in teamplay


void Bullet_Fire (gentity_t *ent, float spread, int damage, int MOD ) {
	trace_t		tr;
	vec3_t		end;
#ifdef MISSIONPACK
	vec3_t		impactpoint, bouncedir;
#endif
	float		r;
	float		u;
	gentity_t		*tent;
	gentity_t		*traceEnt;
	int			i, passent;

	//Elder: removed - for some reason it's set to 0
	//damage *= s_quadFactor;

	/* Original AQ2 code
    vectoangles (aimdir, dir);
    AngleVectors (dir, forward, right, up);

    r = crandom()*hspread;
    u = crandom()*vspread;
    VectorMA (start, 8192, forward, end);
    VectorMA (end, r, right, end);
    VectorMA (end, u, up, end);
	*/

	/* More AQ2 code to implement
    // change bullet's course when it enters water
    VectorSubtract (end, start, dir);
    vectoangles (dir, dir);
    AngleVectors (dir, forward, right, up);
    r = crandom()*hspread*2;
    u = crandom()*vspread*2;
    VectorMA (water_start, 8192, forward, end);
    VectorMA (end, r, right, end);
    VectorMA (end, u, up, end);
	*/

	//Elder: original Q3 code -- note the first line and its use to reduce spread
	//r = random() * M_PI * 2.0f;
	//u = sin(r) * crandom() * spread * 16;
	//r = cos(r) * crandom() * spread * 16;

	//FYI: multiply by 16 so we can reach the furthest ends of a "TA" sized map
	u = crandom() * spread * 16;
	r = crandom() * spread * 16;
	VectorMA (muzzle, 8192*16, forward, end);
	VectorMA (end, r, right, end);
	VectorMA (end, u, up, end);

	passent = ent->s.number;
	for (i = 0; i < 10; i++) {

		trap_Trace (&tr, muzzle, NULL, NULL, end, passent, MASK_SHOT);
	if ( tr.surfaceFlags & SURF_NOIMPACT ) {
		return;
	}

	traceEnt = &g_entities[ tr.entityNum ];

	// snap the endpos to integers, but nudged towards the line
	SnapVectorTowards( tr.endpos, muzzle );

	// send bullet impact
	if ( traceEnt->takedamage && traceEnt->client ) {
		tent = G_TempEntity( tr.endpos, EV_BULLET_HIT_FLESH );
		tent->s.eventParm = traceEnt->s.number;
		if( LogAccuracyHit( traceEnt, ent ) ) {
				ent->client->accuracy_hits++;
				switch (MOD)
				{
				case MOD_PISTOL:
					ent->client->mk23Hits++;
					break;
				case MOD_M4:
					ent->client->m4Hits++;
					break;
				case MOD_MP5:
					ent->client->mp5Hits++;
					break;
				case MOD_AKIMBO:
					ent->client->akimboHits++;
					break;
				}
				

		}
	//Elder: *******************TEST CODE *****************
	//} else if ( tr.surfaceFlags & SURF_GRASS ) {
		//tent = G_TempEntity( tr.endpos, EV_BULLET_HIT_FLESH);
		//tent->s.eventParm = DirToByte( tr.plane.normal );
	} else {
		tent = G_TempEntity( tr.endpos, EV_BULLET_HIT_WALL );
		tent->s.eventParm = DirToByte( tr.plane.normal );
	}
	tent->s.otherEntityNum = ent->s.number;
	//G_Printf("Surfaceflags: %d\n", tr.surfaceFlags);

	if ( traceEnt->takedamage) {
#ifdef MISSIONPACK
			if ( traceEnt->client && traceEnt->client->invulnerabilityTime > level.time ) {
				if (G_InvulnerabilityEffect( traceEnt, forward, tr.endpos, impactpoint, bouncedir )) {
					G_BounceProjectile( muzzle, impactpoint, bouncedir, end );
					VectorCopy( impactpoint, muzzle );
					// the player can hit him/herself with the bounced rail
					passent = ENTITYNUM_NONE;
				}
				else {
					VectorCopy( tr.endpos, muzzle );
					passent = traceEnt->s.number;
				}
				continue;
			}
			else {
#endif
		G_Damage( traceEnt, ent, ent, forward, tr.endpos,
			damage, 0, MOD);
#ifdef MISSIONPACK
			}
#endif
		}
		break;
	}
}


/*
======================================================================

BFG

======================================================================
*/
//Blaze: No more BFG
/*
void BFG_Fire ( gentity_t *ent ) {
	gentity_t	*m;

	m = fire_bfg (ent, muzzle, forward);
	m->damage *= s_quadFactor;
	m->splashDamage *= s_quadFactor;

//	VectorAdd( m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta );	// "real" physics
}
*/

/*
======================================================================

SHOTGUN

======================================================================
*/

// DEFAULT_SHOTGUN_SPREAD and DEFAULT_SHOTGUN_COUNT	are in bg_public.h, because
// client predicts same spreads
#define	DEFAULT_SHOTGUN_DAMAGE	10

qboolean ShotgunPellet( vec3_t start, vec3_t end, gentity_t *ent ) {
	trace_t		tr;
	int			damage, i, passent;
	gentity_t		*traceEnt;
#ifdef MISSIONPACK
	vec3_t		impactpoint, bouncedir;
#endif
	vec3_t		tr_start, tr_end;

	passent = ent->s.number;
	VectorCopy( start, tr_start );
	VectorCopy( end, tr_end );
	for (i = 0; i < 10; i++) {
		trap_Trace (&tr, tr_start, NULL, NULL, tr_end, passent, MASK_SHOT);
	traceEnt = &g_entities[ tr.entityNum ];

	// send bullet impact
	if (  tr.surfaceFlags & SURF_NOIMPACT ) {
		return qfalse;
	}

	if ( traceEnt->takedamage) {
		//Elder: added to discern handcannon and m3 damage
		if (ent->client && ent->client->ps.weapon == WP_HANDCANNON ) {
			//G_Printf("Firing handcannon\n");
			damage = HANDCANNON_DAMAGE;
			G_Damage( traceEnt, ent, ent, forward, tr.endpos, damage, 0, MOD_HANDCANNON);
		}
		else {
			//G_Printf("Firing M3\n");
			damage = M3_DAMAGE;
			G_Damage( traceEnt, ent, ent, forward, tr.endpos, damage, 0, MOD_M3);
		}
		//damage = DEFAULT_SHOTGUN_DAMAGE; // * s_quadFactor;
#ifdef MISSIONPACK
			if ( traceEnt->client && traceEnt->client->invulnerabilityTime > level.time ) {
				if (G_InvulnerabilityEffect( traceEnt, forward, tr.endpos, impactpoint, bouncedir )) {
					G_BounceProjectile( tr_start, impactpoint, bouncedir, tr_end );
					VectorCopy( impactpoint, tr_start );
					// the player can hit him/herself with the bounced rail
					passent = ENTITYNUM_NONE;
				}
				else {
					VectorCopy( tr.endpos, tr_start );
					passent = traceEnt->s.number;
				}
				continue;
			}
			else {
		G_Damage( traceEnt, ent, ent, forward, tr.endpos,
			damage, 0, MOD_SHOTGUN);
		if( LogAccuracyHit( traceEnt, ent ) ) {
			return qtrue;
		}
	}
#else
			//Elder: moved into if conditional above
			//G_Damage( traceEnt, ent, ent, forward, tr.endpos,	damage, 0, MOD_SHOTGUN);
				if( LogAccuracyHit( traceEnt, ent ) ) {
					return qtrue;
				}
#endif
		}
		return qfalse;
	}
	return qfalse;
}

// this should match CG_ShotgunPattern
void ShotgunPattern( vec3_t origin, vec3_t origin2, int seed, gentity_t *ent, int shotType ) {
	int			i;
	float		r, u;
	vec3_t		end;
	vec3_t		forward, right, up;
	int			oldScore;
	qboolean	hitClient = qfalse;

	//Elder: added
	int			count;
	int			hc_multipler;

	// derive the right and up vectors from the forward vector, because
	// the client won't have any other information
	VectorNormalize2( origin2, forward );
	PerpendicularVector( right, forward );
	CrossProduct( forward, right, up );

	oldScore = ent->client->ps.persistant[PERS_SCORE];

	//Elder: added
	if (shotType == WP_M3)
		count = DEFAULT_M3_COUNT;
	else if (shotType == WP_HANDCANNON) {
		count = DEFAULT_HANDCANNON_COUNT;
		hc_multipler = 4;
	}
	else {
		count = DEFAULT_HANDCANNON_COUNT;
		hc_multipler = 5;
	}


	// generate the "random" spread pattern
	for ( i = 0 ; i < count ; i++ ) {
		if (shotType == WP_M3)
		{
			r = Q_crandom( &seed ) * DEFAULT_M3_HSPREAD * 16;
			u = Q_crandom( &seed ) * DEFAULT_M3_VSPREAD * 16;
			//r = Q_crandom( &seed ) * DEFAULT_SHOTGUN_SPREAD * 16;
			//u = Q_crandom( &seed ) * DEFAULT_SHOTGUN_SPREAD * 16;
		}
		else
		{
			r = Q_crandom( &seed ) * DEFAULT_SHOTGUN_HSPREAD * 16 * 4;
			u = Q_crandom( &seed ) * DEFAULT_SHOTGUN_VSPREAD * 16 * hc_multipler;
			//r = Q_crandom( &seed ) * DEFAULT_HANDCANNON_SPREAD * 16 * 4;
			//u = Q_crandom( &seed ) * DEFAULT_HANDCANNON_SPREAD * 16 * 4;
		}

		VectorMA( origin, 8192 * 16, forward, end);
		VectorMA (end, r, right, end);
		VectorMA (end, u, up, end);
		if( ShotgunPellet( origin, end, ent ) && !hitClient ) {
			hitClient = qtrue;
			ent->client->accuracy_hits++;
			switch (shotType)
				{
				case WP_M3:
					ent->client->m3Hits++;
					break;
				case WP_HANDCANNON:
					ent->client->hcHits++;
					break;
				}
		}
	}
}


void weapon_supershotgun_fire (gentity_t *ent) {
	gentity_t		*tent;

	// send shotgun blast
	tent = G_TempEntity( muzzle, EV_SHOTGUN );
	VectorScale( forward, 4096, tent->s.origin2 );
	SnapVector( tent->s.origin2 );
	tent->s.eventParm = rand() & 255;		// seed for spread pattern
	tent->s.otherEntityNum = ent->s.number;

	//Elder: removed for now
	//ShotgunPattern( tent->s.pos.trBase, tent->s.origin2, tent->s.eventParm, ent, qtrue );
}


/*
======================================================================

GRENADE LAUNCHER

======================================================================
*/
//Blaze: No more grenade launcher, no need for fire function
/*
void weapon_grenadelauncher_fire (gentity_t *ent) {
	gentity_t	*m;

	// extra vertical velocity
	forward[2] += 0.2f;
	VectorNormalize( forward );

	m = fire_grenade (ent, muzzle, forward);
	m->damage *= s_quadFactor;
	m->splashDamage *= s_quadFactor;

//	VectorAdd( m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta );	// "real" physics
}
*/
/*
======================================================================

ROCKET

======================================================================
*/
//Blaze: No more rocket launcher, no need for this function
/*
void Weapon_RocketLauncher_Fire (gentity_t *ent) {
	gentity_t	*m;

	m = fire_rocket (ent, muzzle, forward);
	m->damage *= s_quadFactor;
	m->splashDamage *= s_quadFactor;

//	VectorAdd( m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta );	// "real" physics
}
*/

/*
======================================================================

PLASMA GUN

======================================================================
*/
//Blaze: No plasma gun, no need for this function
/*
void Weapon_Plasmagun_Fire (gentity_t *ent) {
	gentity_t	*m;

	m = fire_plasma (ent, muzzle, forward);
	m->damage *= s_quadFactor;
	m->splashDamage *= s_quadFactor;

//	VectorAdd( m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta );	// "real" physics
}
*/
/*
======================================================================

RAILGUN

======================================================================
*/


/*
=================
weapon_railgun_fire
=================
*/
#define	MAX_RAIL_HITS	4
void weapon_railgun_fire (gentity_t *ent) {
	vec3_t		end;
#ifdef MISSIONPACK
	vec3_t impactpoint, bouncedir;
#endif
	trace_t		trace;
	gentity_t	*tent;
	gentity_t	*traceEnt;
	int			damage;
	int			i;
	int			hits;
	int			unlinked;
	int			passent;
	gentity_t	*unlinkedEntities[MAX_RAIL_HITS];

	damage = 100 * s_quadFactor;

	VectorMA (muzzle, 8192, forward, end);

	// trace only against the solids, so the railgun will go through people
	unlinked = 0;
	hits = 0;
	passent = ent->s.number;
	do {
		trap_Trace (&trace, muzzle, NULL, NULL, end, passent, MASK_SHOT );
		if ( trace.entityNum >= ENTITYNUM_MAX_NORMAL ) {
			break;
		}
		traceEnt = &g_entities[ trace.entityNum ];
		if ( traceEnt->takedamage ) {
#ifdef MISSIONPACK
			if ( traceEnt->client && traceEnt->client->invulnerabilityTime > level.time ) {
				if ( G_InvulnerabilityEffect( traceEnt, forward, trace.endpos, impactpoint, bouncedir ) ) {
					G_BounceProjectile( muzzle, impactpoint, bouncedir, end );
					// snap the endpos to integers to save net bandwidth, but nudged towards the line
					SnapVectorTowards( trace.endpos, muzzle );
					// send railgun beam effect
					tent = G_TempEntity( trace.endpos, EV_RAILTRAIL );
					// set player number for custom colors on the railtrail
					tent->s.clientNum = ent->s.clientNum;
					VectorCopy( muzzle, tent->s.origin2 );
					// move origin a bit to come closer to the drawn gun muzzle
					VectorMA( tent->s.origin2, 4, right, tent->s.origin2 );
					VectorMA( tent->s.origin2, -1, up, tent->s.origin2 );
					tent->s.eventParm = 255;	// don't make the explosion at the end
					//
					VectorCopy( impactpoint, muzzle );
					// the player can hit him/herself with the bounced rail
					passent = ENTITYNUM_NONE;
				}
			}
			else {
				if( LogAccuracyHit( traceEnt, ent ) ) {
					hits++;
				}
				G_Damage (traceEnt, ent, ent, forward, trace.endpos, damage, 0, MOD_RAILGUN);
			}
#else
			if( LogAccuracyHit( traceEnt, ent ) ) {
				hits++;
			}
			G_Damage (traceEnt, ent, ent, forward, trace.endpos, damage, 0, MOD_RAILGUN);
#endif
		}
		if ( trace.contents & CONTENTS_SOLID ) {
			break;		// we hit something solid enough to stop the beam
		}
		// unlink this entity, so the next trace will go past it
		trap_UnlinkEntity( traceEnt );
		unlinkedEntities[unlinked] = traceEnt;
		unlinked++;
	} while ( unlinked < MAX_RAIL_HITS );

	// link back in any entities we unlinked
	for ( i = 0 ; i < unlinked ; i++ ) {
		trap_LinkEntity( unlinkedEntities[i] );
	}

	// the final trace endpos will be the terminal point of the rail trail

	// snap the endpos to integers to save net bandwidth, but nudged towards the line
	SnapVectorTowards( trace.endpos, muzzle );

	// send railgun beam effect
	tent = G_TempEntity( trace.endpos, EV_RAILTRAIL );

	// set player number for custom colors on the railtrail
	tent->s.clientNum = ent->s.clientNum;

	VectorCopy( muzzle, tent->s.origin2 );
	// move origin a bit to come closer to the drawn gun muzzle
	VectorMA( tent->s.origin2, 4, right, tent->s.origin2 );
	VectorMA( tent->s.origin2, -1, up, tent->s.origin2 );

	// no explosion at end if SURF_NOIMPACT, but still make the trail
	if ( trace.surfaceFlags & SURF_NOIMPACT ) {
		tent->s.eventParm = 255;	// don't make the explosion at the end
	} else {
		tent->s.eventParm = DirToByte( trace.plane.normal );
	}
	tent->s.clientNum = ent->s.clientNum;

	// give the shooter a reward sound if they have made two railgun hits in a row
	if ( hits == 0 ) {
		// complete miss
		ent->client->accurateCount = 0;
	} else {
		// check for "impressive" reward sound
		ent->client->accurateCount += hits;
		if ( ent->client->accurateCount >= 2 ) {
			ent->client->accurateCount -= 2;

			//Blaze: Removed because it uses the persistant stats stuff
			//ent->client->ps.persistant[PERS_IMPRESSIVE_COUNT]++;
			// add the sprite over the player's head
			ent->client->ps.eFlags &= ~(EF_AWARD_IMPRESSIVE | EF_AWARD_EXCELLENT | EF_AWARD_GAUNTLET | EF_AWARD_ASSIST | EF_AWARD_DEFEND | EF_AWARD_CAP );
			ent->client->ps.eFlags |= EF_AWARD_IMPRESSIVE;
			ent->client->rewardTime = level.time + REWARD_SPRITE_TIME;
		}
		ent->client->accuracy_hits++;
	}

}


/*
======================================================================

GRAPPLING HOOK

======================================================================
*/
//Blaze: No need for grappling hook
/*
void Weapon_GrapplingHook_Fire (gentity_t *ent)
{
	if (!ent->client->fireHeld && !ent->client->hook)
		fire_grapple (ent, muzzle, forward);

	ent->client->fireHeld = qtrue;
}

void Weapon_HookFree (gentity_t *ent)
{
	ent->parent->client->hook = NULL;
	ent->parent->client->ps.pm_flags &= ~PMF_GRAPPLE_PULL;
	G_FreeEntity( ent );
}

void Weapon_HookThink (gentity_t *ent)
{
	if (ent->enemy) {
		vec3_t v, oldorigin;

		VectorCopy(ent->r.currentOrigin, oldorigin);
		v[0] = ent->enemy->r.currentOrigin[0] + (ent->enemy->r.mins[0] + ent->enemy->r.maxs[0]) * 0.5;
		v[1] = ent->enemy->r.currentOrigin[1] + (ent->enemy->r.mins[1] + ent->enemy->r.maxs[1]) * 0.5;
		v[2] = ent->enemy->r.currentOrigin[2] + (ent->enemy->r.mins[2] + ent->enemy->r.maxs[2]) * 0.5;
		SnapVectorTowards( v, oldorigin );	// save net bandwidth

		G_SetOrigin( ent, v );
	}

	VectorCopy( ent->r.currentOrigin, ent->parent->client->ps.grapplePoint);
}
*/
 
/*
======================================================================

LIGHTNING GUN

======================================================================
*/

void Weapon_LightningFire( gentity_t *ent ) {
	trace_t		tr;
	vec3_t		end;
#ifdef MISSIONPACK
	vec3_t impactpoint, bouncedir;
#endif
	gentity_t	*traceEnt, *tent;
	int			damage, i, passent;

	damage = 8 * s_quadFactor;

	passent = ent->s.number;
	for (i = 0; i < 10; i++) {
	VectorMA( muzzle, LIGHTNING_RANGE, forward, end );

		trap_Trace( &tr, muzzle, NULL, NULL, end, passent, MASK_SHOT );

#ifdef MISSIONPACK
		// if not the first trace (the lightning bounced of an invulnerability sphere)
		if (i) {
			// add bounced off lightning bolt temp entity
			// the first lightning bolt is a cgame only visual
			//
			tent = G_TempEntity( muzzle, EV_LIGHTNINGBOLT );
			VectorCopy( tr.endpos, end );
			SnapVector( end );
			VectorCopy( end, tent->s.origin2 );
		}
#endif
	if ( tr.entityNum == ENTITYNUM_NONE ) {
		return;
	}

	traceEnt = &g_entities[ tr.entityNum ];

		if ( traceEnt->takedamage) {
#ifdef MISSIONPACK
			if ( traceEnt->client && traceEnt->client->invulnerabilityTime > level.time ) {
				if (G_InvulnerabilityEffect( traceEnt, forward, tr.endpos, impactpoint, bouncedir )) {
					G_BounceProjectile( muzzle, impactpoint, bouncedir, end );
					VectorCopy( impactpoint, muzzle );
					VectorSubtract( end, impactpoint, forward );
					VectorNormalize(forward);
					// the player can hit him/herself with the bounced lightning
					passent = ENTITYNUM_NONE;
				}
				else {
					VectorCopy( tr.endpos, muzzle );
					passent = traceEnt->s.number;
				}
				continue;
			}
			else {
				G_Damage( traceEnt, ent, ent, forward, tr.endpos,
					damage, 0, MOD_LIGHTNING);
			}
#else
				G_Damage( traceEnt, ent, ent, forward, tr.endpos,
					damage, 0, MOD_LIGHTNING);
#endif
		}

	if ( traceEnt->takedamage && traceEnt->client ) {
		tent = G_TempEntity( tr.endpos, EV_MISSILE_HIT );
		tent->s.otherEntityNum = traceEnt->s.number;
		tent->s.eventParm = DirToByte( tr.plane.normal );
		tent->s.weapon = ent->s.weapon;
		if( LogAccuracyHit( traceEnt, ent ) ) {
				ent->client->accuracy_hits++;
		}
	} else if ( !( tr.surfaceFlags & SURF_NOIMPACT ) ) {
		tent = G_TempEntity( tr.endpos, EV_MISSILE_MISS );
		tent->s.eventParm = DirToByte( tr.plane.normal );
	}

		break;
	}
}

#ifdef MISSIONPACK
/*
======================================================================

NAILGUN

======================================================================
*/

void Weapon_Nailgun_Fire (gentity_t *ent) {
	gentity_t	*m;
	int			count;

	for( count = 0; count < NUM_NAILSHOTS; count++ ) {
		m = fire_nail (ent, muzzle, forward, right, up );
		m->damage *= s_quadFactor;
		m->splashDamage *= s_quadFactor;
	}

//	VectorAdd( m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta );	// "real" physics
}


/*
======================================================================

PROXIMITY MINE LAUNCHER

======================================================================
*/

void weapon_proxlauncher_fire (gentity_t *ent) {
	gentity_t	*m;

	// extra vertical velocity
	forward[2] += 0.2f;
	VectorNormalize( forward );

	m = fire_prox (ent, muzzle, forward);
	m->damage *= s_quadFactor;
	m->splashDamage *= s_quadFactor;

//	VectorAdd( m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta );	// "real" physics
}

#endif

/*
========================================================================

KNIFE ATTACKS

========================================================================
*/

//Elder: changed to void function
void Knife_Attack ( gentity_t *self, int damage)
{    
    trace_t tr; 
    vec3_t end;
	gentity_t *hitent;
	gentity_t *tent;
	
	VectorMA( muzzle, KNIFE_RANGE, forward, end );
    trap_Trace (&tr, muzzle, NULL, NULL, end, self->s.number, MASK_SHOT);
    hitent = &g_entities[ tr.entityNum ];    
	
    // don't need to check for water
    //if (!((tr.surfaceFlags) && (tr.surfaceFlags & SURF_SKY)))    
	if (!(tr.surfaceFlags & SURF_SKY))    
    {
        if (tr.fraction < 1.0)        
        {            
            if (hitent->takedamage)            
            {
				//Elder: no knock-back on knife slashes
				G_Damage (hitent, self, self, forward, tr.endpos, damage, DAMAGE_NO_KNOCKBACK, MOD_KNIFE );
				if (hitent->client)
				{
					tent = G_TempEntity(tr.endpos, EV_RQ3_SOUND);
					tent->s.eventParm = RQ3_SOUND_KNIFEHIT;
				}
            }
			else
			{
				//Elder TODO: take into account surface flags for clank
				tent = G_TempEntity(tr.endpos, EV_KNIFE_MISS);
				tent->s.eventParm = DirToByte(tr.plane.normal);
				tent->s.weapon = WP_KNIFE;
			}
        }
    }
} 

//static int knives = 0;


//Elder: this function does not appear to be in use
void Knife_Touch (gentity_t *ent, gentity_t *other,trace_t *trace)
{
    vec3_t          origin;
	gitem_t		*xr_item;
	gentity_t	*xr_drop;

	G_Printf("Knife Touched Something\n");

        
    if (other == ent->parent)
		return;
        
	if (trace && (trace->surfaceFlags & SURF_SKY)) {
	//Blaze: Get rid of the knife if it hits the sky
//                G_FreeEdict (ent);
		//Elder: I think you want this
		G_FreeEntity(ent);
		return;
    }
        
	if (ent->parent->client) {
		//Blaze: Play the clank hit noise
//      gi.sound(ent, CHAN_WEAPON, gi.soundindex("weapons/clank.wav"), 1, ATTN_NORM, 0);
//      PlayerNoise(ent->owner, ent->s.origin, PNOISE_IMPACT);
	}
        
    // calculate position for the explosion entity

	VectorMA (ent->s.origin, -0.02, ent->s.origin2, origin);
        
//glass fx
    if (0 == Q_stricmp(other->classname, "func_explosive")) {
        // ignore it, so it can bounce
        return;
    }
	else
// ---
    if (other->takedamage) {
		G_Damage (other, ent, ent, ent->s.origin2, ent->s.origin, THROW_DAMAGE, 0, MOD_KNIFE_THROWN);
    }
    else {
            
                // code to manage excess knives in the game, guarantees that
                // no more than knifelimit knives will be stuck in walls.  
                // if knifelimit == 0 then it won't be in effect and it can
                // start removing knives even when less than the limit are
                // out there.
            /*    if ( g_rxn_knifelimit.value != 0 )
                {
                        knives++;
                        
                        if (knives > g_rxn_knifelimit.value)
                                knives = 1;
                        
                        knife = FindEdictByClassnum ("weapon_Knife", knives);
                        
                        if (knife)
                        {               
                                knife->nextthink = level.time + .1;
                        }
                        
                }   */  
		
	//spawn a knife in the object
	//Elder: todo - rotate the knife model so it's collinear with trajectory
	//and eliminate the jittering
	xr_item = BG_FindItemForWeapon( WP_KNIFE );
	//xr_drop = dropWeapon( ent, xr_item, 0, FL_DROPPED_ITEM);
	xr_drop = LaunchItem(xr_item, ent->s.pos.trBase, 0, FL_THROWN_KNIFE);
	xr_drop->count = 1;
	}

    G_FreeEntity (ent);
}


//gentity_t *Knife_Throw (gentity_t *self,vec3_t start, vec3_t dir, int damage, int speed )
//Elder: moved knife_throw to g_missile.c where it belongs



//======================================================================
//Elder: can probably be static
int RQ3_Spread (gentity_t *ent, int spread)
{
	int runspeed = 225;
	int walkspeed = 10;
	int stage = 0;
	float factor[] = {0.7f, 1.0f, 2.0f, 6.0f};
	float xyspeed = (ent->client->ps.velocity[0]*ent->client->ps.velocity[0] + ent->client->ps.velocity[1]*ent->client->ps.velocity[1]);

	//crouching
	if (ent->client->ps.pm_flags & PMF_DUCKED)
		return (spread * 0.65);

	//running
	if (xyspeed > runspeed * runspeed)
		stage = 3;
	//walking
	else if (xyspeed >= walkspeed*walkspeed)
		stage = 2;
	//standing
	else
		stage = 1;

	//added laser advantage
	if (bg_itemlist[ent->client->ps.stats[STAT_HOLDABLE_ITEM]].giTag == HI_LASER &&
		(ent->client->ps.weapon == WP_PISTOL ||
		 ent->client->ps.weapon == WP_MP5 ||
		 ent->client->ps.weapon == WP_M4))
	{
		//G_Printf("Using laser advantage\n");
		if (stage == 1)
			stage = 0;
		else
			stage = 1;
	}


	return (int)(spread * factor[stage]);

	/*
	//Elder: original AQ2 code
	int running = 225; // minimum speed for running
    int walking = 10; // minimum speed for walking
    int laser = 0;
    float factor[] = {.7, 1, 2, 6};
    int stage = 0;

    // 225 is running
    // < 10 will be standing
    float xyspeed = (ent->velocity[0]*ent->velocity[0] + ent->velocity[1]*ent->velocity[1]);
        
        if (ent->client->ps.pmove.pm_flags & PMF_DUCKED) // crouching
                return( spread * .65);

        if ( (ent->client->pers.inventory[ITEM_INDEX(FindItem(LASER_NAME))]) 
                        && (ent->client->curr_weap == MK23_NUM
                        || ent->client->curr_weap == MP5_NUM
                        || ent->client->curr_weap == M4_NUM ) )
                laser = 1;


        // running
        if ( xyspeed > running*running )
                stage = 3;
        // walking
        else if ( xyspeed >= walking*walking )
                stage = 2;
        // standing
        else
                stage = 1;
        
        // laser advantage
        if (laser)
        {
                        if (stage == 1)
                                stage = 0;
                        else
                                stage = 1;
        }
                
        return (int)(spread * factor[stage]);
	*/


}
/*
============
Knife Attack
============
*/
void Weapon_Knife_Fire(gentity_t *ent)
{
//	Knife_Attack(ent,THROW_DAMAGE);
	gentity_t	*m;

// Homer: if client is supposed to be slashing, go to that function instead
	if ( (ent->client->ps.persistant[PERS_WEAPONMODES] & RQ3_KNIFEMODE) == RQ3_KNIFEMODE ) {
		//Elder: added
		Knife_Attack(ent,SLASH_DAMAGE);
		return;
	}

	// extra vertical velocity
	forward[2] += 0.2f;
	
	//Elder: already done in  Knife_Throw
	//VectorNormalize( forward );

	//m = Knife_Throw(ent, muzzle, forward, THROW_DAMAGE, 1200);
	m = fire_knife(ent, muzzle, forward);
//	m->damage *= s_quadFactor;
//	m->splashDamage *= s_quadFactor;
// ^^^^ Homer: got quad?

}

/*
============
M4 Attack
============
*/
void Weapon_M4_Fire(gentity_t *ent)
{
	float spread;
	// Homer: increment burst if needed
	if ( (ent->client->ps.persistant[PERS_WEAPONMODES] & RQ3_M4MODE) == RQ3_M4MODE )
	{
		//ent->client->ps.stats[STAT_BURST]++;
		spread = M4_SPREAD * 0.7;
	}
	else
	{
		spread = M4_SPREAD;
		//M4-kick stuff
		ent->client->consecutiveShots++;
		if (ent->client->consecutiveShots > 23)
			ent->client->consecutiveShots = 23;

	}

	Bullet_Fire( ent, RQ3_Spread(ent, M4_SPREAD), M4_DAMAGE, MOD_M4);

	/*	
	if ( (ent->client->ps.persistant[PERS_WEAPONMODES] & RQ3_M4MODE) == RQ3_M4MODE) {
		//Elder: burst three shots
		if (ent->client->weaponfireNextTime > 0 && ent->client->ps.stats[STAT_BURST] > 2) {
			ent->client->weaponfireNextTime = 0;
		}
		else {
			ent->client->weaponfireNextTime = level.time + RQ3_M4_DELAY;
		}
	}*/

}

/*
============
MK23 Attack
============
*/
void Weapon_MK23_Fire(gentity_t *ent)
{
	float spread;
	// Homer: increment burst if needed
	if ( (ent->client->ps.persistant[PERS_WEAPONMODES] & RQ3_MK23MODE) == RQ3_MK23MODE )
	{
		spread = PISTOL_SPREAD * 0.7;
		//ent->client->ps.stats[STAT_BURST]++;
	}
	else
	{
		spread = PISTOL_SPREAD;
	}
	Bullet_Fire( ent, RQ3_Spread(ent, spread), PISTOL_DAMAGE, MOD_PISTOL);

}

/*
============
SSG3000 Attack
============
*/
void Weapon_SSG3000_FireOld(gentity_t *ent)
{
	float spread;
	//Elder: changed to use RQ3_Spread as well
	if (RQ3_isZoomed(ent))
	{
		spread = 0;
	}
	else
	{
		spread = RQ3_Spread(ent, SNIPER_SPREAD);
	}
	Bullet_Fire( ent, spread, SNIPER_DAMAGE, MOD_SNIPER);

	//Elder: bolt action plus save last zoom
	ent->client->weaponfireNextTime = level.time + RQ3_SSG3000_BOLT_DELAY;
	RQ3_SaveZoomLevel(ent);
}

/*
=================
Elder:
This is a triple-hybrid bastard child of
railgun_fire, old SSG, and bullet_fire code

weapon_ssg3000_fire
=================
*/
#define	MAX_SSG3000_HITS	8
void Weapon_SSG3000_Fire (gentity_t *ent) {
	vec3_t		end;
	trace_t		trace;
	gentity_t	*tent[MAX_SSG3000_HITS];
	gentity_t	*tentWall;
	gentity_t	*traceEnt;
	int			damage;
	int			i;
	int			hits;
	int			unlinked;
	int			passent;
	gentity_t	*unlinkedEntities[MAX_SSG3000_HITS];

	qboolean	hitBreakable;
	qboolean	hitKevlar;
	float		r;
	float		u;
	float		spread;


	VectorMA (muzzle, 8192*16, forward, end);

	//Elder: added to assist in zoom crap
	if (RQ3_isZoomed(ent))
	{
		spread = 0;
	}
	else
	{
		/*
		r = random() * M_PI * 2.0f;
		u = sin(r) * crandom() * spread * 16;
		r = cos(r) * crandom() * spread * 16;
		VectorMA (end, r, right, end);
		VectorMA (end, u, up, end);
		*/
		spread = RQ3_Spread(ent, SNIPER_SPREAD);
		u = crandom() * spread * 16;
		r = crandom() * spread * 16;
		VectorMA (end, r, right, end);
		VectorMA (end, u, up, end);
	}


	//damage = 100 * s_quadFactor;
	damage = SNIPER_DAMAGE;

	//VectorMA (muzzle, 8192*16, forward, end);

	// trace only against the solids, so the SSG3000 will go through people
	unlinked = 0;
	hits = 0;
	passent = ent->s.number;
	//G_Printf("(%d) SSG: Begin loop\n", level.time);
	do {
		//Elder: need to store this flag because
		//the entity may get wiped out in G_Damage
		hitBreakable = qfalse;
		hitKevlar = qfalse;

		//G_Printf("(%d) SSG: Trapping trace\n", level.time);

		trap_Trace (&trace, muzzle, NULL, NULL, end, passent, MASK_SHOT );
		if ( trace.entityNum >= ENTITYNUM_MAX_NORMAL ) {
			//G_Printf("(%d) SSG: OOB Entity: exiting loop\n", level.time);
			break;
		}
		
		traceEnt = &g_entities[ trace.entityNum ];
		
		if ( traceEnt->takedamage ) {
			//G_Printf("(%d) SSG: hit damagable entity\n", level.time);
			
			//flag hitBreakable - bullets go through even
			//if it doesn't "shatter" - but that's usually
			//not the case
			if ( traceEnt->s.eType == ET_BREAKABLE ) {
				//G_Printf("(%d) SSG: Hit a breakable\n", level.time);
				hitBreakable = qtrue;
			}

			// send impacts
			if ( traceEnt->client )
			{
				tent[unlinked] = G_TempEntity( trace.endpos, EV_SSG3000_HIT_FLESH );
				//tent[unlinked]->s.eventParm = DirToByte( trace.plane.normal );
				tent[unlinked]->s.eventParm = traceEnt->s.number;
				//Check to see if we've hit kevlar
				if (bg_itemlist[traceEnt->client->ps.stats[STAT_HOLDABLE_ITEM]].giTag == HI_KEVLAR)
					hitKevlar = qtrue;

			}
			else
			{
				tent[unlinked] = G_TempEntity( trace.endpos, EV_BULLET_HIT_WALL );
				tent[unlinked]->s.eventParm = DirToByte( trace.plane.normal );
			}
			tent[unlinked]->s.otherEntityNum = ent->s.number;

			if( LogAccuracyHit( traceEnt, ent ) ) {
				hits++;
			}

			//G_Printf("(%d) SSG: Doing damage to target\n", level.time);
			G_Damage (traceEnt, ent, ent, forward, trace.endpos, damage, 0, MOD_SNIPER);
		}

		//Elder: go through non-solids and breakables
		//If we ever wanted to "shoot through walls" we'd do stuff here
		if ( hitKevlar || (hitBreakable == qfalse && (trace.contents & CONTENTS_SOLID))) {
			//G_Printf("(%d) SSG: did not hit breakable and hit solid, exiting loop\n", level.time);
			break;		// we hit something solid enough to stop the beam
		}

		//G_Printf("(%d) SSG: Unlinking trace entity\n", level.time);
		// unlink this entity, so the next trace will go past it
		trap_UnlinkEntity( traceEnt );
		unlinkedEntities[unlinked] = traceEnt;
		unlinked++;
		//G_Printf("(%d) SSG: Unlinked count: %d\n", level.time, unlinked);
	} while ( unlinked < MAX_SSG3000_HITS );

	//G_Printf("(%d) SSG: Relinking unlinked entities\n", level.time);
	// link back in any entities we unlinked
	for ( i = 0 ; i < unlinked ; i++ ) {
		trap_LinkEntity( unlinkedEntities[i] );
	}

	// the final trace endpos will be the terminal point of the rail trail

	// snap the endpos to integers to save net bandwidth, but nudged towards the line
	SnapVectorTowards( trace.endpos, muzzle );

	//G_Printf("(%d) SSG: Sending bullet impact event\n", level.time);

	// send wall bullet impact
	// no explosion at end if SURF_NOIMPACT
	if ( !(trace.surfaceFlags & SURF_NOIMPACT) )
	{
		tentWall = G_TempEntity( trace.endpos, EV_BULLET_HIT_WALL );
		tentWall->s.eventParm = DirToByte( trace.plane.normal );
		tentWall->s.otherEntityNum = ent->s.number;
	}

	// send railgun beam effect
	//tent = G_TempEntity( trace.endpos, EV_RAILTRAIL );

	// set player number for custom colors on the railtrail
	//tent->s.clientNum = ent->s.clientNum;

	//VectorCopy( muzzle, tent->s.origin2 );
	// move origin a bit to come closer to the drawn gun muzzle
	//VectorMA( tent->s.origin2, 4, right, tent->s.origin2 );
	//VectorMA( tent->s.origin2, -1, up, tent->s.origin2 );

	// no explosion at end if SURF_NOIMPACT, but still make the trail
	//if ( trace.surfaceFlags & SURF_NOIMPACT ) {
		//tent->s.eventParm = 255;	// don't make the explosion at the end
	//} else {
		//tent->s.eventParm = DirToByte( trace.plane.normal );
	//}
	//tent->s.clientNum = ent->s.clientNum;

	//G_Printf("(%d) SSG: Shooter reward\n", level.time);

	// give the shooter a reward sound if they have made two railgun hits in a row
	if ( hits == 0 ) {
		// complete miss
		ent->client->accurateCount = 0;
	} else {
		// check for "impressive" reward sound
		ent->client->accurateCount += hits;
		if ( ent->client->accurateCount >= 3 ) {
			ent->client->accurateCount -= 3;

			//Blaze: Removed because it uses the persistant stats stuff
			//ent->client->ps.persistant[PERS_IMPRESSIVE_COUNT]++;
			// add the sprite over the player's head
			ent->client->ps.eFlags &= ~(EF_AWARD_IMPRESSIVE | EF_AWARD_EXCELLENT | EF_AWARD_GAUNTLET | EF_AWARD_ASSIST | EF_AWARD_DEFEND | EF_AWARD_CAP );
			ent->client->ps.eFlags |= EF_AWARD_IMPRESSIVE;
			ent->client->rewardTime = level.time + REWARD_SPRITE_TIME;
		}
		ent->client->accuracy_hits++;
		ent->client->ssgHits++;
	}

	//Elder: bolt action plus save last zoom
	//ent->client->weaponfireNextTime = level.time + RQ3_SSG3000_BOLT_DELAY;
	RQ3_SaveZoomLevel(ent);
}


/*
============
MP5 Attack
============
*/
void Weapon_MP5_Fire(gentity_t *ent)
{
	float spread;
	// Homer: increment burst if needed
	if ( (ent->client->ps.persistant[PERS_WEAPONMODES] & RQ3_MP5MODE) == RQ3_MP5MODE )
	{
		spread = MP5_SPREAD * 0.7;
		//ent->client->ps.stats[STAT_BURST]++;
	}
	else
	{
		spread = MP5_SPREAD;
	}
	
	Bullet_Fire( ent, RQ3_Spread(ent, MP5_SPREAD), MP5_DAMAGE, MOD_MP5);

}
/*
============
Handcannon Attack
============
*/
void Weapon_HandCannon_Fire(gentity_t *ent)
{
	gentity_t		*tent, *tent2;

	//Elder: added for damage report
	RQ3_InitShotgunDamageReport();

	// send shotgun blast
	tent = G_TempEntity( muzzle, EV_HANDCANNON );
	VectorScale( forward, 4096, tent->s.origin2 );
	SnapVector( tent->s.origin2 );
	tent->s.eventParm = rand() & 255;		// seed for spread pattern
	tent->s.otherEntityNum = ent->s.number;
	ShotgunPattern(tent->s.pos.trBase, tent->s.origin2, tent->s.eventParm, ent, WP_HANDCANNON );

	// send shotgun blast
	tent2 = G_TempEntity( muzzle, EV_HANDCANNON );
	VectorScale( forward, 4096, tent2->s.origin2 );
	SnapVector( tent2->s.origin2 );
	tent2->s.eventParm = rand() & 255;		// seed for spread pattern
	tent2->s.otherEntityNum = ent->s.number;
	tent2->s.angles2[1] += 20;
	//Elder: note negative one
	ShotgunPattern(tent2->s.pos.trBase, tent2->s.origin2, tent2->s.eventParm, ent, -1 );

	//Elder: added for damage report
	RQ3_ProduceShotgunDamageReport(ent);
}
/*
============
Shotgun Attack
============
*/
void Weapon_M3_Fire(gentity_t *ent)
{
	//Blaze: call to shotgun fire function here
	gentity_t		*tent;

	//Elder: added for damage report
	RQ3_InitShotgunDamageReport();

	// send shotgun blast
	tent = G_TempEntity( muzzle, EV_SHOTGUN );
	VectorScale( forward, 4096, tent->s.origin2 );
	SnapVector( tent->s.origin2 );
	tent->s.eventParm = rand() & 255;		// seed for spread pattern
	tent->s.otherEntityNum = ent->s.number;

	ShotgunPattern( tent->s.pos.trBase, tent->s.origin2, tent->s.eventParm, ent, WP_M3 );
	
	//Elder: added for damage report
	RQ3_ProduceShotgunDamageReport(ent);
}

/*
==============
RQ3_ShotgunDamageReport

Added by Elder
Used to determine hits from a shotgun source
Modelled after the one done for AQ2
==============
*/

void RQ3_InitShotgunDamageReport( void )
{
	//Elder: Reset all tookShellHit 'slots' to zero
	memset(tookShellHit, 0, MAX_CLIENTS * sizeof(int));	
}

//Elder: similar to AQ2 source
#define MAX_NAME_REPORTS	8
void RQ3_ProduceShotgunDamageReport(gentity_t *self)
{
	int		i;
    int		totalNames = 0;
	int		printed = 0;
    char	textbuf[1024];
	gclient_t	*hitClient;

    //for (l = 1; l <= g_maxclients.integer; l++)
	
	// Run through array to see if anyone was hit
	for (i = 0; i < MAX_CLIENTS; i++)
    {
		if (tookShellHit[i])
			totalNames++;
	}

    if (totalNames)
    {
		// Clamp number of names to report
		if (totalNames > MAX_NAME_REPORTS)
			totalNames = MAX_NAME_REPORTS;

		//Q_strncpyz(textbuf, "You hit", sizeof(textbuf));
		strcpy(textbuf, "You hit ");
        for (i = 0; i < MAX_CLIENTS; i++)
        {
			if (tookShellHit[i])
            {
				//grammar set
				if (printed == (totalNames - 1))
                {		
					if (totalNames == 2)
						Q_strcat(textbuf, sizeof(textbuf), "^7 and ");
                    else if (totalNames != 1)
                        Q_strcat(textbuf, sizeof(textbuf), "^7, and ");
                }
                else if (printed)
					Q_strcat(textbuf, sizeof(textbuf), "^7, ");
				
				//add to text buffer
				hitClient = g_entities[i].client;
				Q_strcat(textbuf, sizeof(textbuf), hitClient->pers.netname);
                printed++;
            }

            if (printed == totalNames)
				break;
        }
		trap_SendServerCommand( self-g_entities, va("print \"%s^7.\n\"", textbuf));
		//gi.cprintf(self, PRINT_HIGH, "%s\n", textbuf);
    }
}

/*
============
Akimbo Attack
============
*/
void Weapon_Akimbo_Fire(gentity_t *ent)
{
	float spread;
	//Blaze: Will need 2 of these
	spread = AKIMBO_SPREAD;
	Bullet_Fire( ent, RQ3_Spread(ent, spread), AKIMBO_DAMAGE, MOD_AKIMBO);

	//Elder: reset plus added 1 bullet check
	if (ent->client->weaponfireNextTime > 0 || ent->client->ps.ammo[WP_AKIMBO] < 2)
		ent->client->weaponfireNextTime = 0;
	else
		ent->client->weaponfireNextTime = level.time + RQ3_AKIMBO_DELAY2;

	//Bullet_Fire( ent, RQ3_Spread(ent, spread), AKIMBO_DAMAGE, MOD_AKIMBO);
}

/*
============
Grenade Attack
============
*/
void Weapon_Grenade_Fire(gentity_t *ent)
{
	gentity_t	*m;

	// extra vertical velocity
	forward[2] += 0.5f;
	VectorNormalize( forward );

	m = fire_grenade (ent, muzzle, forward);
	//Elder: removed
	//m->damage *= s_quadFactor;
	//m->splashDamage *= s_quadFactor;

//	VectorAdd( m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta );	// "real" physics

}

/*
===============
LogAccuracyHit
===============
*/
qboolean LogAccuracyHit( gentity_t *target, gentity_t *attacker ) {
	if( !target->takedamage ) {
		return qfalse;
	}

	if ( target == attacker ) {
		return qfalse;
	}

	if( !target->client ) {
		return qfalse;
	}

	if( !attacker->client ) {
		return qfalse;
	}

	if( target->client->ps.stats[STAT_HEALTH] <= 0 ) {
		return qfalse;
	}

	if ( OnSameTeam( target, attacker ) ) {
		return qfalse;
	}

	return qtrue;
}


/*
===============
CalcMuzzlePoint

set muzzle location relative to pivoting eye
===============
*/
void CalcMuzzlePoint ( gentity_t *ent, vec3_t forward, vec3_t right, vec3_t up, vec3_t muzzlePoint ) {
	VectorCopy( ent->s.pos.trBase, muzzlePoint );
	muzzlePoint[2] += ent->client->ps.viewheight;
	VectorMA( muzzlePoint, 14, forward, muzzlePoint );
	// snap to integer coordinates for more efficient network bandwidth usage
	SnapVector( muzzlePoint );
}

/*
===============
CalcMuzzlePointOrigin

set muzzle location relative to pivoting eye
===============
*/
void CalcMuzzlePointOrigin ( gentity_t *ent, vec3_t origin, vec3_t forward, vec3_t right, vec3_t up, vec3_t muzzlePoint ) {
	VectorCopy( ent->s.pos.trBase, muzzlePoint );
	muzzlePoint[2] += ent->client->ps.viewheight;
	VectorMA( muzzlePoint, 14, forward, muzzlePoint );
	// snap to integer coordinates for more efficient network bandwidth usage
	SnapVector( muzzlePoint );
}



/*
===============
FireWeapon
===============
*/
void FireWeapon( gentity_t *ent ) {
	/* Homer: got quad?
	if (ent->client->ps.powerups[PW_QUAD] ) {
		s_quadFactor = g_quadfactor.value;
	} else {*/
	//Elder: uncommented so it won't be zero!
	s_quadFactor = 1;
	//} 
#ifdef MISSIONPACK
	if( ent->client->persistantPowerup && ent->client->persistantPowerup->item && ent->client->persistantPowerup->item->giTag == PW_DOUBLER ) {
		s_quadFactor *= 2;
	}
#endif

	// track shots taken for accuracy tracking.  Grapple is not a weapon and gauntet is just not tracked
	//Blaze: dont record accuracy for knife
//	if( ent->s.weapon != WP_KNIFE) {
#ifdef MISSIONPACK
		if( ent->s.weapon == WP_NAILGUN ) {
			ent->client->accuracy_shots += NUM_NAILSHOTS;
		} else {
			ent->client->accuracy_shots++;
		}
#else
		ent->client->accuracy_shots++;
#endif
//	}

	// set aiming directions
	AngleVectors (ent->client->ps.viewangles, forward, right, up);

	CalcMuzzlePointOrigin ( ent, ent->client->oldOrigin, forward, right, up, muzzle );

	// fire the specific weapon
	switch( ent->s.weapon ) {
//Blaze: The functions get called when you shoot your gun
	case WP_KNIFE:
		Weapon_Knife_Fire (ent);
		ent->client->knifeShots++;
		break;
	case WP_GRENADE:
		Weapon_Grenade_Fire ( ent );
		ent->client->grenShots++;
		break;
	case WP_PISTOL:
		Weapon_MK23_Fire ( ent );
		ent->client->mk23Shots++;
		break;
	case WP_M4:
		Weapon_M4_Fire ( ent );
		ent->client->m4Shots++;
		break;
	case WP_SSG3000:
		//Weapon_SSG3000_FireOld( ent );
		Weapon_SSG3000_Fire ( ent );
		ent->client->ssgShots++;
		break;
	case WP_MP5:
		Weapon_MP5_Fire ( ent );
		ent->client->mp5Shots++;
		break;
	case WP_HANDCANNON:
		Weapon_HandCannon_Fire ( ent );
		ent->client->hcShots++;
		break;
	case WP_M3:
		Weapon_M3_Fire ( ent );
		ent->client->m3Shots++;
		break;
	case WP_AKIMBO:
		Weapon_Akimbo_Fire ( ent );
		ent->client->akimboShots++;
		break;
#ifdef MISSIONPACK
	case WP_NAILGUN:
		Weapon_Nailgun_Fire( ent );
		break;
	case WP_PROX_LAUNCHER:
		weapon_proxlauncher_fire( ent );
		break;
	case WP_CHAINGUN:
		Bullet_Fire( ent, CHAINGUN_SPREAD, MACHINEGUN_DAMAGE );
		break;
#endif
	default:
// FIXME		G_Error( "Bad ent->s.weapon" );
		break;
	}
}


#ifdef MISSIONPACK

/*
===============
KamikazeRadiusDamage
===============
*/
static void KamikazeRadiusDamage( vec3_t origin, gentity_t *attacker, float damage, float radius ) {
	float		dist;
	gentity_t	*ent;
	int			entityList[MAX_GENTITIES];
	int			numListedEntities;
	vec3_t		mins, maxs;
	vec3_t		v;
	vec3_t		dir;
	int			i, e;

	if ( radius < 1 ) {
		radius = 1;
	}

	for ( i = 0 ; i < 3 ; i++ ) {
		mins[i] = origin[i] - radius;
		maxs[i] = origin[i] + radius;
	}

	numListedEntities = trap_EntitiesInBox( mins, maxs, entityList, MAX_GENTITIES );

	for ( e = 0 ; e < numListedEntities ; e++ ) {
		ent = &g_entities[entityList[ e ]];

		if (!ent->takedamage) {
			continue;
		}

		// dont hit things we have already hit
		if( ent->kamikazeTime > level.time ) {
			continue;
		}

		// find the distance from the edge of the bounding box
		for ( i = 0 ; i < 3 ; i++ ) {
			if ( origin[i] < ent->r.absmin[i] ) {
				v[i] = ent->r.absmin[i] - origin[i];
			} else if ( origin[i] > ent->r.absmax[i] ) {
				v[i] = origin[i] - ent->r.absmax[i];
			} else {
				v[i] = 0;
			}
		}

		dist = VectorLength( v );
		if ( dist >= radius ) {
			continue;
		}

//		if( CanDamage (ent, origin) ) {
			VectorSubtract (ent->r.currentOrigin, origin, dir);
			// push the center of mass higher than the origin so players
			// get knocked into the air more
			dir[2] += 24;
			G_Damage( ent, NULL, attacker, dir, origin, damage, DAMAGE_RADIUS|DAMAGE_NO_TEAM_PROTECTION, MOD_KAMIKAZE );
			ent->kamikazeTime = level.time + 3000;
//		}
	}
}

/*
===============
KamikazeShockWave
===============
*/
static void KamikazeShockWave( vec3_t origin, gentity_t *attacker, float damage, float push, float radius ) {
	float		dist;
	gentity_t	*ent;
	int			entityList[MAX_GENTITIES];
	int			numListedEntities;
	vec3_t		mins, maxs;
	vec3_t		v;
	vec3_t		dir;
	int			i, e;

	if ( radius < 1 )
		radius = 1;

	for ( i = 0 ; i < 3 ; i++ ) {
		mins[i] = origin[i] - radius;
		maxs[i] = origin[i] + radius;
	}

	numListedEntities = trap_EntitiesInBox( mins, maxs, entityList, MAX_GENTITIES );

	for ( e = 0 ; e < numListedEntities ; e++ ) {
		ent = &g_entities[entityList[ e ]];

		// dont hit things we have already hit
		if( ent->kamikazeShockTime > level.time ) {
			continue;
		}

		// find the distance from the edge of the bounding box
		for ( i = 0 ; i < 3 ; i++ ) {
			if ( origin[i] < ent->r.absmin[i] ) {
				v[i] = ent->r.absmin[i] - origin[i];
			} else if ( origin[i] > ent->r.absmax[i] ) {
				v[i] = origin[i] - ent->r.absmax[i];
			} else {
				v[i] = 0;
			}
		}

		dist = VectorLength( v );
		if ( dist >= radius ) {
			continue;
		}

//		if( CanDamage (ent, origin) ) {
			VectorSubtract (ent->r.currentOrigin, origin, dir);
			dir[2] += 24;
			G_Damage( ent, NULL, attacker, dir, origin, damage, DAMAGE_RADIUS|DAMAGE_NO_TEAM_PROTECTION, MOD_KAMIKAZE );
			//
			dir[2] = 0;
			VectorNormalize(dir);
			if ( ent->client ) {
				ent->client->ps.velocity[0] = dir[0] * push;
				ent->client->ps.velocity[1] = dir[1] * push;
				ent->client->ps.velocity[2] = 100;
			}
			ent->kamikazeShockTime = level.time + 3000;
//		}
	}
}

/*
===============
KamikazeDamage
===============
*/
static void KamikazeDamage( gentity_t *self ) {
	int i;
	float t;
	gentity_t *ent;
	vec3_t newangles;

	self->count += 100;

	if (self->count >= KAMI_SHOCKWAVE_STARTTIME) {
		// shockwave push back
		t = self->count - KAMI_SHOCKWAVE_STARTTIME;
		KamikazeShockWave(self->s.pos.trBase, self->activator, 25, 400,	(int) (float) t * KAMI_SHOCKWAVE_MAXRADIUS / (KAMI_SHOCKWAVE_ENDTIME - KAMI_SHOCKWAVE_STARTTIME) );
	}
	//
	if (self->count >= KAMI_EXPLODE_STARTTIME) {
		// do our damage
		t = self->count - KAMI_EXPLODE_STARTTIME;
		KamikazeRadiusDamage( self->s.pos.trBase, self->activator, 400,	(int) (float) t * KAMI_BOOMSPHERE_MAXRADIUS / (KAMI_IMPLODE_STARTTIME - KAMI_EXPLODE_STARTTIME) );
	}

	// either cycle or kill self
	if( self->count >= KAMI_SHOCKWAVE_ENDTIME ) {
		G_FreeEntity( self );
		return;
	}
	self->nextthink = level.time + 100;

	// add earth quake effect
	newangles[0] = crandom() * 2;
	newangles[1] = crandom() * 2;
	newangles[2] = 0;
	for (i = 0; i < MAX_CLIENTS; i++)
	{
		ent = &g_entities[i];
		if (!ent->inuse)
			continue;
		if (!ent->client)
			continue;

		if (ent->client->ps.groundEntityNum != ENTITYNUM_NONE) {
			ent->client->ps.velocity[0] += crandom() * 120;
			ent->client->ps.velocity[1] += crandom() * 120;
			ent->client->ps.velocity[2] = 30 + random() * 25;
		}

		ent->client->ps.delta_angles[0] += ANGLE2SHORT(newangles[0] - self->movedir[0]);
		ent->client->ps.delta_angles[1] += ANGLE2SHORT(newangles[1] - self->movedir[1]);
		ent->client->ps.delta_angles[2] += ANGLE2SHORT(newangles[2] - self->movedir[2]);
	}
	VectorCopy(newangles, self->movedir);
}

/*
===============
G_StartKamikaze
===============
*/
void G_StartKamikaze( gentity_t *ent ) {
	gentity_t	*explosion;
	gentity_t	*te;
	vec3_t		snapped;

	// start up the explosion logic
	explosion = G_Spawn();

	explosion->s.eType = ET_EVENTS + EV_KAMIKAZE;
	explosion->eventTime = level.time;

	if ( ent->client ) {
		VectorCopy( ent->s.pos.trBase, snapped );
	}
	else {
		VectorCopy( ent->activator->s.pos.trBase, snapped );
	}
	SnapVector( snapped );		// save network bandwidth
	G_SetOrigin( explosion, snapped );

	explosion->classname = "kamikaze";
	explosion->s.pos.trType = TR_STATIONARY;

	explosion->kamikazeTime = level.time;

	explosion->think = KamikazeDamage;
	explosion->nextthink = level.time + 100;
	explosion->count = 0;
	VectorClear(explosion->movedir);

	trap_LinkEntity( explosion );

	if (ent->client) {
		//
		explosion->activator = ent;
		//
		ent->s.eFlags &= ~EF_KAMIKAZE;
		// nuke the guy that used it
		G_Damage( ent, ent, ent, NULL, NULL, 100000, DAMAGE_NO_PROTECTION, MOD_KAMIKAZE );
	}
	else {
		if ( !strcmp(ent->activator->classname, "bodyque") ) {
			explosion->activator = &g_entities[ent->activator->r.ownerNum];
		}
		else {
			explosion->activator = ent->activator;
		}
	}

	// play global sound at all clients
	te = G_TempEntity(snapped, EV_GLOBAL_TEAM_SOUND );
	te->r.svFlags |= SVF_BROADCAST;
	te->s.eventParm = GTS_KAMIKAZE;
}
#endif


/*
============
Laser Sight Stuff

Laser Sight / Flash Light Functions
============
*/

void Laser_Gen( gentity_t *ent, qboolean enabled )	{
	gentity_t	*las;
	//Elder: force it to laser
	int type = 1;

	// First, if it's not the right weapon, leave
	if ( ent->client->ps.weapon != WP_PISTOL && 
		 ent->client->ps.weapon != WP_MP5 &&
		 ent->client->ps.weapon != WP_M4 )
	{
		//Kill laser if it exists
		if (ent->client->lasersight)
		{
			G_FreeEntity( ent->client->lasersight );
			ent->client->lasersight = NULL;
		}
		return;
	}

	//Get rid of you?
	if ( ent->client->lasersight || enabled == qfalse)
	{
		G_FreeEntity( ent->client->lasersight );
		ent->client->lasersight = NULL;
		return;
	}

	las = G_Spawn();

	las->nextthink = level.time + 10;
	las->think = Laser_Think;

	las->s.clientNum = ent->s.number;
	las->r.ownerNum = ent->s.number;
	las->parent = ent;
	las->s.eType = ET_LASER;
	//Elder: added to enable lerping in cgame
	las->s.pos.trType = TR_INTERPOLATE;

	//Lets tell it if flashlight or laser
	if (type == 2)	{
		las->s.eventParm = 2; //tells CG that it is a flashlight
		las->classname = "flashlight";
	}
	else {
		las->s.eventParm = 1; //tells CG that it is a laser sight
		las->classname = "lasersight";
	}

	ent->client->lasersight = las;
}


void Laser_Think( gentity_t *self )
{
	vec3_t		end, start, forward, up;
	trace_t		tr;

	//If the player dies, is spectator, or wrong weapon, kill the dot
	if (self->parent->client->ps.pm_type == PM_DEAD ||
		self->parent->client->ps.pm_type == PM_SPECTATOR ||
		(self->parent->client->ps.weapon != WP_PISTOL &&
		self->parent->client->ps.weapon != WP_MP5 &&
		self->parent->client->ps.weapon != WP_M4))
	{
		//Make sure you kill the reference before freeing the entity
		self->parent->client->lasersight = NULL;
		G_FreeEntity(self);
		return;
	}

	//Set Aiming Directions
	AngleVectors(self->parent->client->ps.viewangles, forward, right, up);
	CalcMuzzlePoint(self->parent, forward, right, up, start);
	VectorMA (start, 8192 * 16, forward, end);

	//Trace Position
	trap_Trace (&tr, start, NULL, NULL, end, self->parent->s.number, MASK_SHOT );

	//Did you not hit anything?
	if (tr.surfaceFlags & SURF_NOIMPACT || tr.surfaceFlags & SURF_SKY)	{
		self->nextthink = level.time + 10;
		trap_UnlinkEntity(self);
		return;
	}

	//Move you forward to keep you visible
	if (tr.fraction != 1)
		VectorMA(tr.endpos,-4,forward,tr.endpos); 

	//Set Your position
	VectorCopy( tr.endpos, self->r.currentOrigin );
	VectorCopy( tr.endpos, self->s.pos.trBase );

	vectoangles(tr.plane.normal, self->s.angles);

	trap_LinkEntity(self);

	//Prep next move
	self->nextthink = level.time + 10;
}

