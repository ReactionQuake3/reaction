//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
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


void G_ExplodeMissile( gentity_t *ent );
//Makro - added
void Think_SpawnNewDoorTrigger( gentity_t *ent );

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

/*QUAKED light_d (0 1 0) (-8 -8 -8) (8 8 8)
Dynamic light entity.  Use sparingly.
Q3 does not allow for manual light radius setup.
Set the color key for the intended color
"light" overrides the default 100 intensity.
*/
void SP_dlight( gentity_t *ent ) {
	vec3_t	color;
	float	light;
	int		r, g, b, i;
//	int		style;

	G_SpawnFloat( "light", "300", &light );
	G_SpawnVector( "_color", "1 1 1", color );

	// - set style bits in eventParm
	if ( ent->spawnflags & 1 )
		ent->s.eventParm |= DLIGHT_ADDITIVE;
	if ( ent->spawnflags & 2 )
		ent->s.eventParm |= DLIGHT_FLICKER;
	if ( ent->spawnflags & 4 )
		ent->s.eventParm |= DLIGHT_PULSE;
	if ( ent->spawnflags & 8 )
		ent->s.eventParm |= DLIGHT_STROBE;
	
	r = color[0] * 255;
	if ( r > 255 ) {
		r = 255;
	}
	g = color[1] * 255;
	if ( g > 255 ) {
		g = 255;
	}
	b = color[2] * 255;
	if ( b > 255 ) {
		b = 255;
	}
	i = light / 4;
	if ( i > 255 ) {
		i = 255;
	}

	ent->s.constantLight = r | ( g << 8 ) | ( b << 16 ) | ( i << 24 );

	ent->s.eType = ET_DLIGHT;
	ent->classname = "light_d";
	ent->s.pos.trType = TR_STATIONARY;
	VectorCopy( ent->s.origin, ent->r.currentOrigin);

	trap_LinkEntity( ent );
}

// Nothing significant to do
void G_RunDlight ( gentity_t *ent ) {
	trap_LinkEntity( ent );
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
	// AngleVectors( angles, player->client->ps.velocity, NULL, NULL );
	// VectorScale( player->client->ps.velocity, 400, player->client->ps.velocity );
	player->client->ps.pm_time = 160;		// hold time
	player->client->ps.pm_flags |= PMF_TIME_KNOCKBACK;

	// toggle the teleport bit so the client knows to not lerp
	player->client->ps.eFlags ^= EF_TELEPORT_BIT;

	// set angles
	// SetClientViewAngle( player, angles );

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

	if (ent->spawnflags & 1) {
		owner = G_Find(NULL, FOFS(targetname), va("%s%i", ent->target, ent->size+1));
		ent->size = (ent->size + 1) % ent->count;
	} else {
		owner = G_PickTarget( ent->target );
	}
	if ( !owner ) {
		//Makro - fixed typo (misc_partal_surface)
		G_Printf( "Couldn't find target for misc_portal_surface\n" );
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

void use_misc_portal_surface( gentity_t *ent, gentity_t *other, gentity_t *activator ) {
	locateCamera(ent);
}

/*QUAKED misc_portal_surface (0 0 1) (-8 -8 -8) (8 8 8) CYCLE
The portal surface nearest this entity will show a view from the targeted misc_portal_camera, or a mirror view if untargeted.
This must be within 64 world units of the surface!
*/
void SP_misc_portal_surface(gentity_t *ent) {
	VectorClear( ent->r.mins );
	VectorClear( ent->r.maxs );
	trap_LinkEntity (ent);

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
				G_Printf("Cycling misc_portal_surface with no count at %s\n", vtos(ent->s.origin));
				ent->spawnflags--;
			} else {
				ent->size = 0;
				ent->use = use_misc_portal_surface;
			}
		}
	}

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
// Blaze: adding for func_breakable explosions
void func_breakable_explode( gentity_t *self , vec3_t pos ) {
	int eParam;
  gentity_t *tent;
//	GibEntity( self, 0 );
	eParam = self->s.eventParm;

  tent = G_TempEntity2( pos, EV_EXPLODE_BREAKABLE, eParam);

//	self->takedamage = qfalse;
//	self->s.eType = ET_INVISIBLE;
  self->exploded = qtrue;
}

// Blaze: adding for func_breakable explosions

void func_breakable_die( gentity_t *self, gentity_t *inflictor, gentity_t *attacker, int damage, int meansOfDeath )
{
  func_breakable_explode( self , self->s.origin );
//	G_ExplodeMissile(self);
	G_RadiusDamage(self->s.origin,attacker,self->damage,self->damage_radius,self, meansOfDeath);
  //	radius damage
  
}

void Use_Breakable( gentity_t *self, gentity_t *other, gentity_t *activator ) {
  G_UseTargets (self, activator);  
  func_breakable_die( self,activator,activator,self->damage,MOD_TRIGGER_HURT);
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
 


void SP_func_breakable( gentity_t *ent ) {
	int health;
	int amount;
  int temp;
  int damage;
  int damage_radius;

  char *id;
  char *velocity;
  char *jump;
  char *name, *s;
  char breakinfo[MAX_INFO_STRING];

  // Make it appear as the brush
  trap_SetBrushModel( ent, ent->model );
    
	// Setup health of breakable
  G_SpawnInt( "health", "0", &health );
  if( health <= 0 )	
  {
    health = 5;
  }
  //G_Printf("Setting health to %d\n",health);
  G_SpawnInt("damage","170", &damage);

	ent->damage = damage;

  G_SpawnInt("damage_radius","340", &damage_radius);

	ent->damage_radius = damage_radius;
  
  ent->exploded = qfalse;
	// Setup amount type
	G_SpawnInt( "amount", "0", &temp );  
  //Com_Printf("Amount %d ", temp);
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
	if ( ent->spawnflags & 1)
  {
    ent->chippable = qtrue;
    //Com_Printf("Chippable ");
  }
  else
  {
    ent->chippable = qfalse;
  }

  if ( ent->spawnflags & 2)
  {
    ent->unbreakable = qtrue;
    //Com_Printf("Unbreakable ");
  }
  else
  {
    ent->unbreakable = qfalse;
  }
	
  if ( ent->spawnflags & 4)
  {
    ent->explosive = qtrue;
  }
  else
  {
    ent->explosive = qfalse;
  }
  
  if ( !ent->damage_radius )
  {
    ent->damage_radius=GRENADE_SPLASH_RADIUS;
  }
  ent->use = Use_Breakable;

  G_SpawnString( "id","0", &id);
  if (atoi(id) < 0 || atoi(id) >= RQ3_MAX_BREAKABLES )
  {
    G_Printf("^2ERROR: ID too high\n");
    G_FreeEntity( ent );
    return;
  }
  //Com_Printf("ID (%d) ", id);
  if (!G_SpawnString( "type", "", &name) )
  {
    G_Printf("^2ERROR: broken breakable name (%s)\n", name);
    G_FreeEntity( ent );
    return;
  }
  //Com_Printf("type (%s)\n",name);
  G_SpawnString( "force", "7", &velocity);


  G_SpawnString( "lift", "5", &jump);


  amount = amount << 6;
  
	//Elder: merge the bits
 	ent->s.eventParm = amount | (atoi(id) & 0x0FFF);

  ent->health = health;
  ent->takedamage = qtrue;


  ent->s.origin[0] = ent->r.mins[0] + (0.5 * (ent->r.maxs[0] - ent->r.mins[0]));
	ent->s.origin[1] = ent->r.mins[1] + (0.5 * (ent->r.maxs[1] - ent->r.mins[1]));
	ent->s.origin[2] = ent->r.mins[2] + (0.5 * (ent->r.maxs[2] - ent->r.mins[2]));

  // Let it know it is a breakable object
  ent->s.eType = ET_BREAKABLE;

  // If the mapper gave it a model, use it
  if ( ent->model2 ) {
      ent->s.modelindex2 = G_ModelIndex( ent->model2 );
  }


  //Makro - added this so spectators can go through breakables
  //ent->nextthink = level.time + FRAMETIME;
  //ent->think = Think_SpawnNewDoorTrigger;
  Info_SetValueForKey( breakinfo, "type", name );
  Info_SetValueForKey( breakinfo, "velocity", velocity );
  Info_SetValueForKey( breakinfo, "jump", jump );
  Info_SetValueForKey( breakinfo, "id", id );
  trap_SetConfigstring( CS_BREAKABLES+atoi(id), breakinfo);
  
  trap_LinkEntity (ent);

	//Makro - added for elevators
	if (G_SpawnString( "pathtarget","", &s)) {
		Q_strncpyz(ent->pathtarget, s, sizeof(ent->pathtarget));
	}

}


/*
=================
G_BreakGlass

Create/process a breakable event entity
Original by inolen, heavy modifications by Elder
=================
*/
void G_BreakGlass( gentity_t *ent, gentity_t *inflictor, gentity_t *attacker, vec3_t point, int mod, int damage )
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
  eParm = ent->s.eventParm;
  
 	if( ent->health <= 0 ) {
		//G_Printf("Original eParm: %i \n", ent->s.eventParm);
		//Copy the first four bits and strip them out of the original
	/*	eParm = ent->s.eventParm & 15;
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
    
    if (ent->explosive)
    {
      mod = MOD_TRIGGER_HURT;
      func_breakable_die(ent, inflictor, attacker, damage, mod);
    }
    G_UseTargets (ent, ent->activator);
		//G_FreeEntity( ent );
		//G_Printf("%s shift: %i\n", vtos(impactPoint), shiftCount);
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

		//G_Printf("eType: %i\n", tent->s.event & ~EV_EVENT_BITS);
     	//Elder: use TempEntity2 to stuff params
        //tent = G_TempEntity( center, EV_BREAK_GLASS );
 	//tent->s.eventParm = eParm;
    //unlink it instead of freeing
    trap_UnlinkEntity(ent);

 	}
  else if(ent->chippable)
  {
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
		//G_FreeEntity( ent );
		//G_Printf("%s shift: %i\n", vtos(impactPoint), shiftCount);
		tent = G_TempEntity2( impactPoint, EV_CHIP_GLASS, eParm);

  }
}

void SP_func_pressure( gentity_t *ent ) {
	// Make it appear as the brush
	G_Printf("Creating Pressure entity\n");
	trap_SetBrushModel( ent, ent->model );
	trap_LinkEntity (ent);

	VectorCopy( ent->s.origin, ent->s.pos.trBase );
	VectorCopy( ent->s.origin, ent->r.currentOrigin );
	ent->s.eType = ET_PRESSURE;

	G_SpawnInt( "speed", "0", &ent->size);

	// ent->spawnflags
	// flame, steam, water

	// ent->s.frame holds type
	// ent->s.powerups holds speed
}

void G_CreatePressure(vec3_t origin, vec3_t normal, gentity_t *ent) {
	gentity_t *tent;

	tent = G_TempEntity( origin, EV_PRESSURE );
	tent->s.eventParm = DirToByte( normal );

	tent->s.frame = ent->spawnflags;	// 1 = water, 2 = steam, 4 = fire
	tent->s.powerups = ent->size;		// speed of pressure
	G_Printf("Game: %d and %d\n", tent->s.frame, tent->s.powerups);
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

/*
================
G_EvaluateTrajectory

================
*/
void G_EvaluateTrajectory( const trajectory_t *tr, int atTime, vec3_t result ) {
	float		deltaTime;
	float		phase;

	switch( tr->trType ) {
	case TR_STATIONARY:
	case TR_INTERPOLATE:
		VectorCopy( tr->trBase, result );
		break;
	case TR_LINEAR:
		deltaTime = ( atTime - tr->trTime ) * 0.001;	// milliseconds to seconds
		VectorMA( tr->trBase, deltaTime, tr->trDelta, result );
		break;
	case TR_SINE:
		deltaTime = ( atTime - tr->trTime ) / (float) tr->trDuration;
		phase = sin( deltaTime * M_PI * 2 );
		VectorMA( tr->trBase, phase, tr->trDelta, result );
		break;
	case TR_LINEAR_STOP:
		if ( atTime > tr->trTime + tr->trDuration ) {
			atTime = tr->trTime + tr->trDuration;
		}
		deltaTime = ( atTime - tr->trTime ) * 0.001;	// milliseconds to seconds
		if ( deltaTime < 0 ) {
			deltaTime = 0;
		}
		VectorMA( tr->trBase, deltaTime, tr->trDelta, result );
		break;
	case TR_GRAVITY:
		deltaTime = ( atTime - tr->trTime ) * 0.001;	// milliseconds to seconds
		VectorMA( tr->trBase, deltaTime, tr->trDelta, result );
		result[2] -= 0.5 * (float)g_gravity.integer * deltaTime * deltaTime;
		break;
	default:
		Com_Error( ERR_DROP, "G_EvaluateTrajectory: unknown trType: %i", tr->trTime );
		break;
	}
}

/*
================
G_EvaluateTrajectoryDelta

For determining velocity at a given time
================
*/
void G_EvaluateTrajectoryDelta( const trajectory_t *tr, int atTime, vec3_t result ) {
	float	deltaTime;
	float	phase;

	switch( tr->trType ) {
	case TR_STATIONARY:
	case TR_INTERPOLATE:
		VectorClear( result );
		break;
	case TR_LINEAR:
		VectorCopy( tr->trDelta, result );
		break;
	case TR_SINE:
		deltaTime = ( atTime - tr->trTime ) / (float) tr->trDuration;
		phase = cos( deltaTime * M_PI * 2 );	// derivative of sin = cos
		phase *= 0.5;
		VectorScale( tr->trDelta, phase, result );
		break;
	case TR_LINEAR_STOP:
		if ( atTime > tr->trTime + tr->trDuration ) {
			VectorClear( result );
			return;
		}
		VectorCopy( tr->trDelta, result );
		break;
	case TR_GRAVITY:
		deltaTime = ( atTime - tr->trTime ) * 0.001;	// milliseconds to seconds
		VectorCopy( tr->trDelta, result );
		result[2] -= (float)g_gravity.integer * deltaTime;
		break;
	default:
		Com_Error( ERR_DROP, "G_EvaluateTrajectoryDelta: unknown trType: %i", tr->trTime );
		break;
	}
}

/* 
================
G_EvaluateTrajectoryDelta  - By NiceAss

Will update all ET_MISSILE entities with TR_GRAVITY on a g_gravity change.
================*/
void G_GravityChange(void) {
	int			i;
	gentity_t	*ent;
	ent = &g_entities[0];
	for (i=0 ; i<level.num_entities ; i++, ent++) {
		if ( ent->s.pos.trType == TR_GRAVITY &&
			ent->s.eType == ET_MISSILE ) 
		{
			G_EvaluateTrajectoryDelta( &ent->s.pos, level.time, ent->s.pos.trDelta );
			VectorCopy( ent->r.currentOrigin, ent->s.pos.trBase );
			ent->s.pos.trTime = level.time;
		}
	}
}

