// Copyright (C) 1999-2000 Id Software, Inc.
//
// g_misc.c

#include "g_local.h"


/*QUAKED func_group (0 0 0) ?
Used to group brushes together just for editor convenience.  They are turned into normal brushes by the utilities.
*/


/*QUAKED info_camp (0 0.5 0) (-4 -4 -4) (4 4 4)
Used as a positional target for calculations in the utilities (spotlights, etc), but removed during gameplay.
*/
void SP_info_camp( gentity_t *self ) {
	G_SetOrigin( self, self->s.origin );
}


/*QUAKED info_null (0 0.5 0) (-4 -4 -4) (4 4 4)
Used as a positional target for calculations in the utilities (spotlights, etc), but removed during gameplay.
*/
void SP_info_null( gentity_t *self ) {
	G_FreeEntity( self );
}


/*QUAKED info_notnull (0 0.5 0) (-4 -4 -4) (4 4 4)
Used as a positional target for in-game calculation, like jumppad targets.
target_position does the same thing
*/
void SP_info_notnull( gentity_t *self ){
	G_SetOrigin( self, self->s.origin );
}


/*QUAKED light (0 1 0) (-8 -8 -8) (8 8 8) linear
Non-displayed light.
"light" overrides the default 300 intensity.
Linear checbox gives linear falloff instead of inverse square
Lights pointed at a target will be spotlights.
"radius" overrides the default 64 unit radius of a spotlight at the target point.
*/
void SP_light( gentity_t *self ) {
	G_FreeEntity( self );
}



/*
=================================================================================

TELEPORTERS

=================================================================================
*/

void TeleportPlayer( gentity_t *player, vec3_t origin, vec3_t angles ) {
	gentity_t	*tent;

	// use temp events at source and destination to prevent the effect
	// from getting dropped by a second player event
	if ( player->client->sess.sessionTeam != TEAM_SPECTATOR ) {
		tent = G_TempEntity( player->client->ps.origin, EV_PLAYER_TELEPORT_OUT );
		tent->s.clientNum = player->s.clientNum;

		tent = G_TempEntity( origin, EV_PLAYER_TELEPORT_IN );
		tent->s.clientNum = player->s.clientNum;
	}

	// unlink to make sure it can't possibly interfere with G_KillBox
	trap_UnlinkEntity (player);

	VectorCopy ( origin, player->client->ps.origin );
	player->client->ps.origin[2] += 1;

	// spit the player out
	AngleVectors( angles, player->client->ps.velocity, NULL, NULL );
	VectorScale( player->client->ps.velocity, 400, player->client->ps.velocity );
	player->client->ps.pm_time = 160;		// hold time
	player->client->ps.pm_flags |= PMF_TIME_KNOCKBACK;

	// toggle the teleport bit so the client knows to not lerp
	player->client->ps.eFlags ^= EF_TELEPORT_BIT;

	// set angles
	SetClientViewAngle( player, angles );

	// kill anything at the destination
	if ( player->client->sess.sessionTeam != TEAM_SPECTATOR ) {
		G_KillBox (player);
	}

	// save results of pmove
	BG_PlayerStateToEntityState( &player->client->ps, &player->s, qtrue );

	// use the precise origin for linking
	VectorCopy( player->client->ps.origin, player->r.currentOrigin );

	if ( player->client->sess.sessionTeam != TEAM_SPECTATOR ) {
		trap_LinkEntity (player);
	}
}


/*QUAKED misc_teleporter_dest (1 0 0) (-32 -32 -24) (32 32 -16)
Point teleporters at these.
Now that we don't have teleport destination pads, this is just
an info_notnull
*/
void SP_misc_teleporter_dest( gentity_t *ent ) {
}


//===========================================================

/*QUAKED misc_model (1 0 0) (-16 -16 -16) (16 16 16)
"model"		arbitrary .md3 file to display
*/
void SP_misc_model( gentity_t *ent ) {

#if 0
	ent->s.modelindex = G_ModelIndex( ent->model );
	VectorSet (ent->mins, -16, -16, -16);
	VectorSet (ent->maxs, 16, 16, 16);
	trap_LinkEntity (ent);

	G_SetOrigin( ent, ent->s.origin );
	VectorCopy( ent->s.angles, ent->s.apos.trBase );
#else
	G_FreeEntity( ent );
#endif
}

//===========================================================

void locateCamera( gentity_t *ent ) {
	vec3_t		dir;
	gentity_t	*target;
	gentity_t	*owner;

	owner = G_PickTarget( ent->target );
	if ( !owner ) {
		G_Printf( "Couldn't find target for misc_partal_surface\n" );
		G_FreeEntity( ent );
		return;
	}
	ent->r.ownerNum = owner->s.number;

	// frame holds the rotate speed
	if ( owner->spawnflags & 1 ) {
		ent->s.frame = 25;
	} else if ( owner->spawnflags & 2 ) {
		ent->s.frame = 75;
	}

	// swing camera ?
	if ( owner->spawnflags & 4 ) {
		// set to 0 for no rotation at all
		ent->s.powerups = 0;
	}
	else {
		ent->s.powerups = 1;
	}

	// clientNum holds the rotate offset
	ent->s.clientNum = owner->s.clientNum;

	VectorCopy( owner->s.origin, ent->s.origin2 );

	// see if the portal_camera has a target
	target = G_PickTarget( owner->target );
	if ( target ) {
		VectorSubtract( target->s.origin, owner->s.origin, dir );
		VectorNormalize( dir );
	} else {
		G_SetMovedir( owner->s.angles, dir );
	}

	ent->s.eventParm = DirToByte( dir );
}

/*QUAKED misc_portal_surface (0 0 1) (-8 -8 -8) (8 8 8)
The portal surface nearest this entity will show a view from the targeted misc_portal_camera, or a mirror view if untargeted.
This must be within 64 world units of the surface!
*/
void SP_misc_portal_surface(gentity_t *ent) {
	VectorClear( ent->r.mins );
	VectorClear( ent->r.maxs );
	trap_LinkEntity (ent);

	ent->r.svFlags = SVF_PORTAL;
	ent->s.eType = ET_PORTAL;

	if ( !ent->target ) {
		VectorCopy( ent->s.origin, ent->s.origin2 );
	} else {
		ent->think = locateCamera;
		ent->nextthink = level.time + 100;
	}
}

/*QUAKED misc_portal_camera (0 0 1) (-8 -8 -8) (8 8 8) slowrotate fastrotate noswing
The target for a misc_portal_director.  You can set either angles or target another entity to determine the direction of view.
"roll" an angle modifier to orient the camera around the target vector;
*/
void SP_misc_portal_camera(gentity_t *ent) {
	float	roll;

	VectorClear( ent->r.mins );
	VectorClear( ent->r.maxs );
	trap_LinkEntity (ent);

	G_SpawnFloat( "roll", "0", &roll );

	ent->s.clientNum = roll/360.0 * 256;
}

/*
======================================================================

  SHOOTERS

======================================================================
*/

void Use_Shooter( gentity_t *ent, gentity_t *other, gentity_t *activator ) {
	vec3_t		dir;
	float		deg;
	vec3_t		up, right;

	// see if we have a target
	if ( ent->enemy ) {
		VectorSubtract( ent->enemy->r.currentOrigin, ent->s.origin, dir );
		VectorNormalize( dir );
	} else {
		VectorCopy( ent->movedir, dir );
	}

	// randomize a bit
	PerpendicularVector( up, dir );
	CrossProduct( up, dir, right );

	deg = crandom() * ent->random;
	VectorMA( dir, deg, up, dir );

	deg = crandom() * ent->random;
	VectorMA( dir, deg, right, dir );

	VectorNormalize( dir );
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
	G_AddEvent( ent, EV_FIRE_WEAPON, 0 );
}


static void InitShooter_Finish( gentity_t *ent ) {
	ent->enemy = G_PickTarget( ent->target );
	ent->think = 0;
	ent->nextthink = 0;
}

void InitShooter( gentity_t *ent, int weapon ) {
	ent->use = Use_Shooter;
	ent->s.weapon = weapon;

	RegisterItem( BG_FindItemForWeapon( weapon ) );

	G_SetMovedir( ent->s.angles, ent->movedir );

	if ( !ent->random ) {
		ent->random = 1.0;
	}
	ent->random = sin( M_PI * ent->random / 180 );
	// target might be a moving object, so we can't set movedir for it
	if ( ent->target ) {
		ent->think = InitShooter_Finish;
		ent->nextthink = level.time + 500;
	}
	trap_LinkEntity( ent );
}

/*QUAKED shooter_rocket (1 0 0) (-16 -16 -16) (16 16 16)
Fires at either the target or the current direction.
"random" the number of degrees of deviance from the taget. (1.0 default)
*/
//Blaze: No need for this because no rocketlauncher
//void SP_shooter_rocket( gentity_t *ent ) {
//	InitShooter( ent, WP_ROCKET_LAUNCHER );
//}

/*QUAKED shooter_plasma (1 0 0) (-16 -16 -16) (16 16 16)
Fires at either the target or the current direction.
"random" is the number of degrees of deviance from the taget. (1.0 default)
*/
//Blaze: No need for this because no plasma gun
//void SP_shooter_plasma( gentity_t *ent ) {
//	InitShooter( ent, WP_PLASMAGUN);
//}

/*QUAKED shooter_grenade (1 0 0) (-16 -16 -16) (16 16 16)
Fires at either the target or the current direction.
"random" is the number of degrees of deviance from the taget. (1.0 default)
*/
//Blaze: No need for this because no grenade Launcher
//void SP_shooter_grenade( gentity_t *ent ) {
//	InitShooter( ent, WP_GRENADE_LAUNCHER);
//}

//Blaze: Breakable glasss
//Elder: Breakable anything!* -- we define, that is
/*QUAKED func_breakable (1 0 0) (-16 -16 -16) (16 16 16)
 Explodes any defined type of debris
 "health" overrides the default health value of 5
 "debris" overrides the default glass shards
   0 - glass
   1 - wood
   2 - metal
   3 - ceramics
   4 - paper
   5 - brick
   6 - concrete
 "amount" overrides the default quantity
   0 - small: about 10 pieces
   1 - medium: about 25 pieces
   2 - large: about 50 pieces
   3 - tons (watch out when using this)
 "variation" (0 to 3) allows you to pick one of 4 variations
   
 */
void SP_func_breakable( gentity_t *ent ) {
	int health;
	int amount;
	int variation;
	int debris;
	int temp;
  
    // Make it appear as the brush
    trap_SetBrushModel( ent, ent->model );
    
	// Setup health of breakable
    G_SpawnInt( "health", "0", &health );
    if( health <= 0 )
  		health = 5;

	// Setup debris type
	G_SpawnInt( "debris", "0", &temp );
	switch (temp)
	{
		case 0:
			debris = RQ3_DEBRIS_GLASS;
			break;
		case 1:
			debris = RQ3_DEBRIS_WOOD;
			break;
		case 2:
			debris = RQ3_DEBRIS_METAL;
			break;
		case 3:
			debris = RQ3_DEBRIS_CERAMIC;
			break;
		case 4:
			debris = RQ3_DEBRIS_PAPER;
			break;
		case 5:
			debris = RQ3_DEBRIS_BRICK;
			break;
		case 6:
			debris = RQ3_DEBRIS_CONCRETE;
			break;
		default:
			debris = RQ3_DEBRIS_GLASS;
			break;
	}
   
	// Setup amount type
	G_SpawnInt( "amount", "0", &temp );   
	switch (temp)
	{
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
			amount = RQ3_DEBRIS_MEDIUM|RQ3_DEBRIS_HIGH;
			break;
		default:
			amount = RQ3_DEBRIS_MEDIUM;
			break;
	}
	
	// Setup variation type
	G_SpawnInt( "variation", "0", &temp);
	switch (temp)
	{
		case 0:
			variation = 0;
			break;
		case 1:
			variation = RQ3_DEBRIS_VAR1;
			break;
		case 2:
			variation = RQ3_DEBRIS_VAR2;
			break;
		case 3:
			variation = RQ3_DEBRIS_VAR1|RQ3_DEBRIS_VAR2;
			break;
		default:
			variation = 0;
			break;
	}

	//Elder: merge the bits
	ent->s.eventParm = amount|variation|debris;
	
    ent->health = health;
    ent->takedamage = qtrue;

    // Let it know it is a breakable object
    ent->s.eType = ET_BREAKABLE;

    // If the mapper gave it a model, use it
    if ( ent->model2 ) {
        ent->s.modelindex2 = G_ModelIndex( ent->model2 );
    }

    trap_LinkEntity (ent);
}

/*
=================
G_BreakGlass

Create/process a breakable event entity
Original by inolen, heavy modifications by Elder
=================
*/
void G_BreakGlass( gentity_t *ent, vec3_t point, int mod )
{
	gentity_t   *tent;
 	vec3_t      size;
    vec3_t      impactPoint;
 	//Elder: for the bit-shifting
	int			eParm;
	int			shiftCount = 0;
 	
	//Elder:
	//eventParm can only transmit as a byte (8-bits/255)
	//So if we receive a huge one, we can knock it down (shift-op)
	//and count the number of times
	//Once it's below 255, we can send a more appropriate event
	//This way, the mappers can use a single func_breakable
	//while we process it on the server-side.
	//Places to stuff: eventParm

 	if( ent->health <= 0 ) {
		//G_Printf("Original eParm: %i \n", ent->s.eventParm);
		//Copy the first four bits and strip them out of the original
		eParm = ent->s.eventParm & 15;
		ent->s.eventParm &= ~eParm;
		
		//Shift-op loop
		while (ent->s.eventParm > 255)
		{
			shiftCount++;
			ent->s.eventParm = ent->s.eventParm >> 4;
		}
		
		eParm |= ent->s.eventParm;

		//eParm should now be under 1 byte and shiftCount >= 0
		//G_Printf("New eParm: %i Shifts: %i\n", eParm, shiftCount);
		
        // Tell the program based on the gun if it was caused by splash damage
     	switch( mod ) {
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
		G_Printf("(%d) (%d) (%d)\n", impactPoint[0], impactPoint[1], impactPoint[2]);
		G_FreeEntity( ent );
		switch ( shiftCount )
		{
			case 0:
				tent = G_TempEntity2( impactPoint, EV_BREAK_GLASS1, eParm);
				break;
			case 1:
				tent = G_TempEntity2( impactPoint, EV_BREAK_GLASS2, eParm);
				break;
			case 2:
				tent = G_TempEntity2( impactPoint, EV_BREAK_GLASS3, eParm);
				break;
			default:
				G_Error("G_BreakGlass: shiftCount > 2\n");
				break;
		}

     	//Elder: use TempEntity2 to stuff params
        //tent = G_TempEntity( center, EV_BREAK_GLASS );
 	tent->s.eventParm = eParm;
 	}
}


#ifdef MISSIONPACK
static void PortalDie (gentity_t *self, gentity_t *inflictor, gentity_t *attacker, int damage, int mod) {
	G_FreeEntity( self );
	//FIXME do something more interesting
}


void DropPortalDestination( gentity_t *player ) {
	gentity_t	*ent;
	vec3_t		snapped;

	// create the portal destination
	ent = G_Spawn();
	ent->s.modelindex = G_ModelIndex( "models/powerups/teleporter/tele_exit.md3" );

	VectorCopy( player->s.pos.trBase, snapped );
	SnapVector( snapped );
	G_SetOrigin( ent, snapped );
	VectorCopy( player->r.mins, ent->r.mins );
	VectorCopy( player->r.maxs, ent->r.maxs );

	ent->classname = "hi_portal destination";
	ent->s.pos.trType = TR_STATIONARY;

	ent->r.contents = CONTENTS_CORPSE;
	ent->takedamage = qtrue;
	ent->health = 200;
	ent->die = PortalDie;

	VectorCopy( player->s.apos.trBase, ent->s.angles );

	ent->think = G_FreeEntity;
	ent->nextthink = level.time + 2 * 60 * 1000;

	trap_LinkEntity( ent );

	player->client->portalID = ++level.portalSequence;
	ent->count = player->client->portalID;

	// give the item back so they can drop the source now
	player->client->ps.stats[STAT_HOLDABLE_ITEM] = BG_FindItem( "Portal" ) - bg_itemlist;
}


static void PortalTouch( gentity_t *self, gentity_t *other, trace_t *trace) {
	gentity_t	*destination;

	// see if we will even let other try to use it
	if( other->health <= 0 ) {
		return;
	}
	if( !other->client ) {
		return;
	}
//	if( other->client->ps.persistant[PERS_TEAM] != self->spawnflags ) {
//		return;
//	}

	if ( other->client->ps.powerups[PW_NEUTRALFLAG] ) {		// only happens in One Flag CTF
		Drop_Item( other, BG_FindItemForPowerup( PW_NEUTRALFLAG ), 0 );
		other->client->ps.powerups[PW_NEUTRALFLAG] = 0;
	}
	else if ( other->client->ps.powerups[PW_REDFLAG] ) {		// only happens in standard CTF
		Drop_Item( other, BG_FindItemForPowerup( PW_REDFLAG ), 0 );
		other->client->ps.powerups[PW_REDFLAG] = 0;
	}
	else if ( other->client->ps.powerups[PW_BLUEFLAG] ) {	// only happens in standard CTF
		Drop_Item( other, BG_FindItemForPowerup( PW_BLUEFLAG ), 0 );
		other->client->ps.powerups[PW_BLUEFLAG] = 0;
	}

	// find the destination
	destination = NULL;
	while( (destination = G_Find(destination, FOFS(classname), "hi_portal destination")) != NULL ) {
		if( destination->count == self->count ) {
			break;
		}
	}

	// if there is not one, die!
	if( !destination ) {
		if( self->pos1[0] || self->pos1[1] || self->pos1[2] ) {
			TeleportPlayer( other, self->pos1, self->s.angles );
		}
		G_Damage( other, other, other, NULL, NULL, 100000, DAMAGE_NO_PROTECTION, MOD_TELEFRAG );
		return;
	}

	TeleportPlayer( other, destination->s.pos.trBase, destination->s.angles );
}


static void PortalEnable( gentity_t *self ) {
	self->touch = PortalTouch;
	self->think = G_FreeEntity;
	self->nextthink = level.time + 2 * 60 * 1000;
}


void DropPortalSource( gentity_t *player ) {
	gentity_t	*ent;
	gentity_t	*destination;
	vec3_t		snapped;

	// create the portal source
	ent = G_Spawn();
	ent->s.modelindex = G_ModelIndex( "models/powerups/teleporter/tele_enter.md3" );

	VectorCopy( player->s.pos.trBase, snapped );
	SnapVector( snapped );
	G_SetOrigin( ent, snapped );
	VectorCopy( player->r.mins, ent->r.mins );
	VectorCopy( player->r.maxs, ent->r.maxs );

	ent->classname = "hi_portal source";
	ent->s.pos.trType = TR_STATIONARY;

	ent->r.contents = CONTENTS_CORPSE | CONTENTS_TRIGGER;
	ent->takedamage = qtrue;
	ent->health = 200;
	ent->die = PortalDie;

	trap_LinkEntity( ent );

	ent->count = player->client->portalID;
	player->client->portalID = 0;

//	ent->spawnflags = player->client->ps.persistant[PERS_TEAM];

	ent->nextthink = level.time + 1000;
	ent->think = PortalEnable;

	// find the destination
	destination = NULL;
	while( (destination = G_Find(destination, FOFS(classname), "hi_portal destination")) != NULL ) {
		if( destination->count == ent->count ) {
			VectorCopy( destination->s.pos.trBase, ent->pos1 );
			break;
		}
	}

}
#endif
