// Copyright (C) 1999-2000 Id Software, Inc.
//
#include "g_local.h"

/*

  Items are any object that a player can touch to gain some effect.

  Pickup will return the number of seconds until they should respawn.

  all items should pop when dropped in lava or slime

  Respawnable items don't actually go away when picked up, they are
  just made invisible and untouchable.  This allows them to ride
  movers and respawn apropriately.
*/


#define	RESPAWN_ARMOR		25
#define	RESPAWN_HEALTH		35
#define	RESPAWN_AMMO		40
#define	RESPAWN_HOLDABLE	60
#define	RESPAWN_MEGAHEALTH	35//120
#define	RESPAWN_POWERUP		120

//Blaze: used for setting amount of ammo a gun has when picked up around line 249
//Elder: Def'd in bg_public.h which g_local.h looks up
//extern int ClipAmountForWeapon(int);
//======================================================================

int Pickup_Powerup( gentity_t *ent, gentity_t *other ) {
	int			quantity;
	int			i;
	gclient_t	*client;

	if ( !other->client->ps.powerups[ent->item->giTag] ) {
		// round timing to seconds to make multiple powerup timers
		// count in sync
		other->client->ps.powerups[ent->item->giTag] = 
			level.time - ( level.time % 1000 );
	}

	if ( ent->count ) {
		quantity = ent->count;
	} else {
		quantity = ent->item->quantity;
	}

	other->client->ps.powerups[ent->item->giTag] += quantity * 1000;

	// give any nearby players a "denied" anti-reward
	for ( i = 0 ; i < level.maxclients ; i++ ) {
		vec3_t		delta;
		float		len;
		vec3_t		forward;
		trace_t		tr;

		client = &level.clients[i];
		if ( client == other->client ) {
			continue;
		}
		if ( client->pers.connected == CON_DISCONNECTED ) {
			continue;
		}
		if ( client->ps.stats[STAT_HEALTH] <= 0 ) {
			continue;
		}

    // if same team in team game, no sound
    // cannot use OnSameTeam as it expects to g_entities, not clients
  	if ( g_gametype.integer >= GT_TEAM && other->client->sess.sessionTeam == client->sess.sessionTeam  ) {
      continue;
    }

		// if too far away, no sound
		VectorSubtract( ent->s.pos.trBase, client->ps.origin, delta );
		len = VectorNormalize( delta );
		if ( len > 192 ) {
			continue;
		}

		// if not facing, no sound
		AngleVectors( client->ps.viewangles, forward, NULL, NULL );
		if ( DotProduct( delta, forward ) < 0.4 ) {
			continue;
		}

		// if not line of sight, no sound
		trap_Trace( &tr, client->ps.origin, NULL, NULL, ent->s.pos.trBase, ENTITYNUM_NONE, CONTENTS_SOLID );
		if ( tr.fraction != 1.0 ) {
			continue;
		}

		// anti-reward
		client->ps.persistant[PERS_PLAYEREVENTS] ^= PLAYEREVENT_DENIEDREWARD;
	}
	return RESPAWN_POWERUP;
}

//======================================================================

#ifdef MISSIONPACK
int Pickup_PersistantPowerup( gentity_t *ent, gentity_t *other ) {
	int		clientNum;
	char	userinfo[MAX_INFO_STRING];
	float	handicap;
	int		max;

	other->client->ps.stats[STAT_PERSISTANT_POWERUP] = ent->item - bg_itemlist;
	other->client->persistantPowerup = ent;

	switch( ent->item->giTag ) {
	case PW_GUARD:
		clientNum = other->client->ps.clientNum;
		trap_GetUserinfo( clientNum, userinfo, sizeof(userinfo) );
		handicap = atof( Info_ValueForKey( userinfo, "handicap" ) );
		if( !handicap ) {
			handicap = 100.0f;
		}
		max = (int)(2 *  handicap);

		other->health = max;
		other->client->ps.stats[STAT_HEALTH] = max;
		other->client->ps.stats[STAT_MAX_HEALTH] = max;
		other->client->ps.stats[STAT_ARMOR] = max;
		other->client->pers.maxHealth = max;

		break;

	case PW_SCOUT:
		clientNum = other->client->ps.clientNum;
		trap_GetUserinfo( clientNum, userinfo, sizeof(userinfo) );
		handicap = atof( Info_ValueForKey( userinfo, "handicap" ) );
		if( !handicap ) {
			handicap = 100.0f;
		}
		other->client->pers.maxHealth = handicap;
		other->client->ps.stats[STAT_ARMOR] = 0;
		break;

	case PW_DOUBLER:
		clientNum = other->client->ps.clientNum;
		trap_GetUserinfo( clientNum, userinfo, sizeof(userinfo) );
		handicap = atof( Info_ValueForKey( userinfo, "handicap" ) );
		if( !handicap ) {
			handicap = 100.0f;
		}
		other->client->pers.maxHealth = handicap;
		break;
	case PW_AMMOREGEN:
		clientNum = other->client->ps.clientNum;
		trap_GetUserinfo( clientNum, userinfo, sizeof(userinfo) );
		handicap = atof( Info_ValueForKey( userinfo, "handicap" ) );
		if( !handicap ) {
			handicap = 100.0f;
		}
		other->client->pers.maxHealth = handicap;
		memset(other->client->ammoTimes, 0, sizeof(other->client->ammoTimes));
		break;
	default:
		clientNum = other->client->ps.clientNum;
		trap_GetUserinfo( clientNum, userinfo, sizeof(userinfo) );
		handicap = atof( Info_ValueForKey( userinfo, "handicap" ) );
		if( !handicap ) {
			handicap = 100.0f;
		}
		other->client->pers.maxHealth = handicap;
		break;
	}

	return -1;
}

//======================================================================
#endif

int Pickup_Holdable( gentity_t *ent, gentity_t *other ) {

	other->client->ps.stats[STAT_HOLDABLE_ITEM] = ent->item - bg_itemlist;

	if( ent->item->giTag == HI_KAMIKAZE ) {
		other->client->ps.eFlags |= EF_KAMIKAZE;
	}

	return RESPAWN_HOLDABLE;
}


//======================================================================

void Add_Ammo (gentity_t *ent, int weapon, int count)
{
	//Blaze: Reaction stuff, add to clip when picking up ammo packs
	//Elder: Modified to use constants def'd in bg_public.h
	ent->client->numClips[weapon] += count;
	
	switch (weapon)
	{
	case WP_KNIFE:
		//Blaze: you get more knifes by picking up the "gun" as opposed to ammo
		break;
	case WP_PISTOL:
		if (ent->client->numClips[weapon] > RQ3_PISTOL_MAXCLIP)
			ent->client->numClips[weapon] = RQ3_PISTOL_MAXCLIP;
		break;
	case WP_AKIMBO:
		if (ent->client->numClips[weapon] > RQ3_AKIMBO_MAXCLIP)
			ent->client->numClips[weapon] = RQ3_AKIMBO_MAXCLIP;
		break;
	case WP_MP5:
		if (ent->client->numClips[weapon] > RQ3_MP5_MAXCLIP)
			ent->client->numClips[weapon] = RQ3_MP5_MAXCLIP;
		break;
	case WP_M4:
		if (ent->client->numClips[weapon] > RQ3_M4_MAXCLIP)
			ent->client->numClips[weapon] = RQ3_M4_MAXCLIP;
		break;
	case WP_M3:
		if (ent->client->numClips[weapon] > RQ3_M3_MAXCLIP)
			ent->client->numClips[weapon] = RQ3_M3_MAXCLIP;
		break;
	case WP_HANDCANNON:
		if (ent->client->numClips[weapon] > RQ3_HANDCANNON_MAXCLIP)
			ent->client->numClips[weapon] = RQ3_HANDCANNON_MAXCLIP;
		break;
	case WP_SSG3000:
		if (ent->client->numClips[weapon] > RQ3_SSG3000_MAXCLIP)
			ent->client->numClips[weapon] = RQ3_SSG3000_MAXCLIP;
		break;
	case WP_GRENADE:
		//Blaze: you get more knifes by picking up the "gun" as opposed to ammo
		break;
	default:
		//Blaze: Should never hit here
		if (ent->client->numClips[weapon] > 20) ent->client->numClips[weapon] = 20;
		break;
	}

	//Elder: sync HC and M3 ammo
	if(weapon == WP_M3) {
		ent->client->numClips[WP_HANDCANNON] = ent->client->numClips[WP_M3]; 
	}
	else if (weapon == WP_HANDCANNON){ 
		ent->client->numClips[WP_M3] = ent->client->numClips[WP_HANDCANNON];
	}
	//Elder: sync Akimbo and MK23 ammo
	else if(weapon == WP_PISTOL) {
		ent->client->numClips[WP_AKIMBO] = ent->client->numClips[WP_PISTOL]; 
	}
	else if (weapon == WP_AKIMBO){ 
		ent->client->numClips[WP_PISTOL] = ent->client->numClips[WP_AKIMBO];
	}
	
	//ent->client->ps.ammo[weapon] += count;
	//if ( ent->client->ps.ammo[weapon] > 200 ) {
	//	ent->client->ps.ammo[weapon] = 200;
	//}
}

int Pickup_Ammo (gentity_t *ent, gentity_t *other)
{
	int		quantity;

	if ( ent->count ) {
		quantity = ent->count;
	} else {
		quantity = ent->item->quantity;
	}
	Add_Ammo (other, ent->item->giTag, quantity);

	return RESPAWN_AMMO;
}

//======================================================================


int Pickup_Weapon (gentity_t *ent, gentity_t *other) {
	int		quantity,ammotoadd;

	if ( ent->count < 0 ) {
		quantity = 0; // None for you, sir!
	} else {
		if ( ent->count ) {
			quantity = ent->count;
		} else {
			quantity = ent->item->quantity;
		}
		/* Elder: commented out
		// dropped items and teamplay weapons always have full ammo
		if ( ! (ent->flags & FL_DROPPED_ITEM) && g_gametype.integer != GT_TEAM ) {
			// respawning rules
			// drop the quantity if the already have over the minimum
			if ( other->client->ps.ammo[ ent->item->giTag ] < quantity ) {
				quantity = quantity - other->client->ps.ammo[ ent->item->giTag ];
			} else {
				quantity = 1;		// only add a single shot
			}
		} */
	}

	// add the weapon if not knife or pistol
	if (ent->item->giTag != WP_KNIFE || ent->item->giTag != WP_PISTOL)
		other->client->ps.stats[STAT_WEAPONS] |= ( 1 << ent->item->giTag );

// Begin Duffman - Adds a clip for each weapon picked up, will want to edit this later
	/*Add_Ammo( other, ent->item->giTag, quantity );*/
	switch (ent->item->giTag)
	{
	case WP_KNIFE:
		if (other->client->ps.ammo[WP_KNIFE] < RQ3_KNIFE_MAXCLIP) 
		{
			//G_Printf("(%d)\n",other->client->ps.ammo[ent->item->giTag]);
			ammotoadd = other->client->ps.ammo[WP_KNIFE] + 1;
		}
		else
		{
			ammotoadd = RQ3_KNIFE_MAXCLIP;
		}
		break;
	case WP_PISTOL:
		//Elder: special case
		//Someone can optimize this code later, but for now, it works.
		if ( !(other->client->ps.stats[STAT_WEAPONS] & (1 << WP_AKIMBO) ) ) {
			//give akimbo
			//G_Printf("Dual MK23 pistols\n");
			trap_SendServerCommand( other-g_entities, va("print \"%s^7\n\"", RQ3_AKIMBO_NAME) );
			other->client->ps.stats[STAT_WEAPONS] |= ( 1 << WP_AKIMBO );
			other->client->ps.ammo[WP_AKIMBO] = other->client->ps.ammo[WP_PISTOL] + RQ3_PISTOL_AMMO;
			ammotoadd = other->client->ps.ammo[WP_PISTOL];
		}
		//Elder: Already have akimbo - technically should have pistol
		else if (other->client->numClips[ WP_PISTOL ] < 2) {
			//give an extra clip - make < 2 + 2 * hasBandolier(0/1) or something for bando when it's in
			//G_Printf("Picked up an extra clip\n");
			trap_SendServerCommand( other-g_entities, va("print \"Picked up an extra clip^7\n\"" ) );
			other->client->numClips[ WP_PISTOL ]++;
			other->client->numClips[ WP_AKIMBO ]++;
			ammotoadd = other->client->ps.ammo[WP_PISTOL];
		}
		else {
			//Elder: maxed out on clips, have akimbo - can't take more!
			ammotoadd = other->client->ps.ammo[WP_PISTOL];
		}
		break;
	case WP_AKIMBO:
		//Elder: Should not need to come here
		ammotoadd= RQ3_AKIMBO_AMMO;
		break;
	case WP_MP5:
		ammotoadd= RQ3_MP5_AMMO;
		other->client->ps.stats[STAT_UNIQUEWEAPONS]++;
		break;
	case WP_M4:
		ammotoadd= RQ3_M4_AMMO;
		other->client->ps.stats[STAT_UNIQUEWEAPONS]++;
		break;
	case WP_M3:
		ammotoadd= RQ3_M3_AMMO;
		other->client->ps.stats[STAT_UNIQUEWEAPONS]++;
		break;
	case WP_HANDCANNON:
		ammotoadd= RQ3_HANDCANNON_AMMO;
		//Elder: HC gets 2 in chamber and 5 in reserve
		//Also sync with M3
		//Removed until we can store the amount of ammo in the gun
		//When it's dropped
		//other->client->numClips[ WP_HANDCANNON ] += 5;
		//other->client->numClips[ WP_M3 ] += 5;
		other->client->ps.stats[STAT_UNIQUEWEAPONS]++;
		break;
	case WP_SSG3000:
		ammotoadd= RQ3_SSG3000_AMMO;
		other->client->ps.stats[STAT_UNIQUEWEAPONS]++;
		break;
	case WP_GRENADE:
		if (other->client->ps.ammo[ent->item->giTag] < RQ3_GRENADE_MAXCLIP) 
		{
			ammotoadd=other->client->ps.ammo[ent->item->giTag]+1;
		}
		else
		{
			ammotoadd= RQ3_GRENADE_MAXCLIP;
		}
		break;
	default:
		//Blaze: Should never hit here
		G_Printf("Pickup_Weapon: Given bad giTag: %d\n", ent->item->giTag);
		ammotoadd=0;
		break;
	}
	//Elder: conditional added to "restore" weapons
	if ( other->client->hadUniqueWeapon[ent->item->giTag] == qfalse ||
		 !((ent->flags & FL_THROWN_ITEM) == FL_THROWN_ITEM) ) {
		other->client->ps.ammo[ent->item->giTag]= ammotoadd;
		//Elder: add extra handcannon clips if it's "fresh"
		if (ent->item->giTag == WP_HANDCANNON) {
			other->client->numClips[ WP_HANDCANNON ] += 5;
			other->client->numClips[ WP_M3 ] += 5;
		}
	}

// End Duffman



//Blaze: No hook
/*
	if (ent->item->giTag == WP_GRAPPLING_HOOK)
		other->client->ps.ammo[ent->item->giTag] = -1; // unlimited ammo
*/

	// team deathmatch has slow weapon respawns
	if ( g_gametype.integer == GT_TEAM ) {
		return g_weaponTeamRespawn.integer;
	}

	return g_weaponRespawn.integer;
}


//======================================================================

int Pickup_Health (gentity_t *ent, gentity_t *other) {
	int			max;
	int			quantity;

	// small and mega healths will go over the max
#ifdef MISSIONPACK
	if( other->client && bg_itemlist[other->client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_GUARD ) {
		max = other->client->ps.stats[STAT_MAX_HEALTH];
	}
	else
#endif
	if ( ent->item->quantity != 5 && ent->item->quantity != 100  ) {
		max = 100;// max health is 100 other->client->ps.stats[STAT_MAX_HEALTH];
	} else {
		max = 100;// max health is 100 other->client->ps.stats[STAT_MAX_HEALTH] * 2;
	}

	if ( ent->count ) {
		quantity = ent->count;
	} else {
		quantity = ent->item->quantity;
	}

	other->health += quantity;

	if (other->health > max ) {
		other->health = max;
	}
	other->client->ps.stats[STAT_HEALTH] = other->health;

	if ( ent->item->quantity == 100 ) {		// mega health respawns slow
		return RESPAWN_MEGAHEALTH;
	}

	return RESPAWN_HEALTH;
}

//======================================================================

int Pickup_Armor( gentity_t *ent, gentity_t *other ) {
#ifdef MISSIONPACK
	int		upperBound;

	other->client->ps.stats[STAT_ARMOR] += ent->item->quantity;

	if( other->client && bg_itemlist[other->client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_GUARD ) {
		upperBound = other->client->ps.stats[STAT_MAX_HEALTH];
	}
	else {
		upperBound = other->client->ps.stats[STAT_MAX_HEALTH] * 2;
	}

	if ( other->client->ps.stats[STAT_ARMOR] > upperBound ) {
		other->client->ps.stats[STAT_ARMOR] = upperBound;
	}
#else
	other->client->ps.stats[STAT_ARMOR] += ent->item->quantity;
	if ( other->client->ps.stats[STAT_ARMOR] > 200) {//max health in this case is 200 other->client->ps.stats[STAT_MAX_HEALTH] * 2 ) {
		other->client->ps.stats[STAT_ARMOR] = 200; //max health is 200 in this case other->client->ps.stats[STAT_MAX_HEALTH] * 2;
	}
#endif

	return RESPAWN_ARMOR;
}

//======================================================================

/*
===============
RespawnItem
===============
*/
void RespawnItem( gentity_t *ent ) {
	// randomly select from teamed entities
	if (ent->team) {
		gentity_t	*master;
		int	count;
		int choice;

		if ( !ent->teammaster ) {
			G_Error( "RespawnItem: bad teammaster");
		}
		master = ent->teammaster;

		for (count = 0, ent = master; ent; ent = ent->teamchain, count++)
			;

		choice = rand() % count;

		for (count = 0, ent = master; count < choice; ent = ent->teamchain, count++)
			;
	}

	ent->r.contents = CONTENTS_TRIGGER;
	ent->s.eFlags &= ~EF_NODRAW;
	ent->r.svFlags &= ~SVF_NOCLIENT;
	trap_LinkEntity (ent);

	if ( ent->item->giType == IT_POWERUP ) {
		// play powerup spawn sound to all clients
		gentity_t	*te;

		// if the powerup respawn sound should Not be global
		if (ent->speed) {
			te = G_TempEntity( ent->s.pos.trBase, EV_GENERAL_SOUND );
		}
		else {
		te = G_TempEntity( ent->s.pos.trBase, EV_GLOBAL_SOUND );
		}
		te->s.eventParm = G_SoundIndex( "sound/items/poweruprespawn.wav" );
		te->r.svFlags |= SVF_BROADCAST;
	}

	if ( ent->item->giType == IT_HOLDABLE && ent->item->giTag == HI_KAMIKAZE ) {
		// play powerup spawn sound to all clients
		gentity_t	*te;

		// if the powerup respawn sound should Not be global
		if (ent->speed) {
			te = G_TempEntity( ent->s.pos.trBase, EV_GENERAL_SOUND );
		}
		else {
			te = G_TempEntity( ent->s.pos.trBase, EV_GLOBAL_SOUND );
		}
		te->s.eventParm = G_SoundIndex( "sound/items/kamikazerespawn.wav" );
		te->r.svFlags |= SVF_BROADCAST;
	}

	// play the normal respawn sound only to nearby clients
	G_AddEvent( ent, EV_ITEM_RESPAWN, 0 );

	ent->nextthink = 0;
}


/*
===============
Touch_Item
===============
*/
void Touch_Item (gentity_t *ent, gentity_t *other, trace_t *trace) {

	int			respawn;
	qboolean	predict;

	if (!other->client)
		return;
	if (other->health < 1)
		return;		// dead people can't pickup

	// the same pickup rules are used for client side and server side
	if ( !BG_CanItemBeGrabbed( g_gametype.integer, &ent->s, &other->client->ps ) ) return;


	G_LogPrintf( "Item: %i %s\n", other->s.number, ent->item->classname );

	predict = other->client->pers.predictItemPickup;

	//Elder: should check if the item was recently thrown ... if it was, then
	//don't allow it to be picked up ... or something like that

	// call the item-specific pickup function
	switch( ent->item->giType ) {
	case IT_WEAPON:
		switch(ent->item->giTag)
		{
		//Blaze: Check to see if we already have the weapon,
		//If not so check and see if we have less then full ammo, if so pick up gun
		//Elder's version:
		//Accumulators (e.g. knife, grenade): if you have the weap AND the max limit, leave
		//Pistols: if you have akimbos AND max clips, leave
		//Akimbos: shouldn't pick them up b/c they shouldn't be dropped
		//Specials: if you have more than/equal to limit (remember bando later), leave
		case WP_KNIFE:
			if ( ( (other->client->ps.stats[STAT_WEAPONS] & (1 << WP_KNIFE) ) == (1 << WP_KNIFE) ) &&
				(other->client->ps.ammo[ent->item->giTag] >= RQ3_KNIFE_MAXCLIP) )
				return;
			break;
		case WP_GRENADE:
			if ( (other->client->ps.stats[STAT_WEAPONS] & (1 << WP_GRENADE) == (1 << WP_GRENADE) ) &&
				(other->client->ps.ammo[ent->item->giTag] >= RQ3_GRENADE_MAXCLIP) )
				return;
			break;
		case WP_PISTOL:
			//Elder: always have pistol - but extra ones give akimbo or clips
			if ( ( (other->client->ps.stats[STAT_WEAPONS] & (1 << WP_AKIMBO) ) == (1 << WP_AKIMBO) ) &&
				other->client->numClips[WP_PISTOL] >= RQ3_PISTOL_MAXCLIP ) {
				//leave if we have max clips and akimbos
				return;
			}
			break;
		case WP_M3:
		case WP_HANDCANNON:
		case WP_MP5:
		case WP_M4:
		case WP_SSG3000:
			if (other->client->ps.stats[STAT_UNIQUEWEAPONS] >= g_rxn_maxweapons.integer)
				return;
			break;
		case WP_AKIMBO:
		default:
			//Elder: shouldn't be here
			G_Printf("Touch_Item received invalid IT_WEAPON giTag: %d\n", ent->item->giTag);
			return;
			break;
		}
		/*
		case WP_KNIFE:
			if (!other->client->ps.stats[STAT_WEAPONS] & WP_KNIFE == WP_KNIFE &&
				(other->client->ps.ammo[ent->item->giTag] >= RQ3_KNIFE_MAXCLIP) )
				return;
			break;
		case WP_PISTOL:
			if (!(other->client->ps.stats[STAT_WEAPONS] & WP_PISTOL == WP_PISTOL) &&
				(other->client->ps.stats[STAT_CLIPS] >= RQ3_PISTOL_MAXCLIP) )
				//Elder: why are we checking clips here but ammo in the others and what-not??
				return;
			break;
		case WP_M3:
			if (!(other->client->ps.stats[STAT_WEAPONS] & WP_M3 == WP_M3) &&
				(other->client->ps.ammo[ent->item->giTag] >= RQ3_M3_AMMO) )
				return;
			break;
		case WP_HANDCANNON:
			if (!(other->client->ps.stats[STAT_WEAPONS] & WP_HANDCANNON == WP_HANDCANNON) &&
				(other->client->ps.ammo[ent->item->giTag] >= RQ3_HANDCANNON_AMMO) )
				return;
			break;
		case WP_MP5:
			if (!(other->client->ps.stats[STAT_WEAPONS] & WP_MP5 == WP_MP5) &&
				(other->client->ps.stats[STAT_CLIPS] >= RQ3_MP5_MAXCLIP) )
				return;
			break;
		case WP_M4:
			if (!(other->client->ps.stats[STAT_WEAPONS] & WP_M4 == WP_M4) &&
				(other->client->ps.stats[STAT_CLIPS] >= RQ3_M4_MAXCLIP) )
				return;
			break;
		case WP_SSG3000:
			if (!(other->client->ps.stats[STAT_WEAPONS] & WP_SSG3000 == WP_SSG3000) &&
				(other->client->ps.ammo[ent->item->giTag] >= RQ3_SSG3000_AMMO ) )
				return;
			break;
		case WP_AKIMBO:
			//Elder: uhh- 24 clips?
			//if (!(other->client->ps.stats[STAT_WEAPONS] & WP_AKIMBO == WP_AKIMBO) &&
				//(other->client->ps.stats[STAT_CLIPS] >= 24) ) return;
			if (!(other->client->ps.stats[STAT_WEAPONS] & WP_AKIMBO == WP_AKIMBO) &&
				(other->client->ps.stats[STAT_CLIPS] >= RQ3_AKIMBO_MAXCLIP) )
				return;
			break;
		case WP_GRENADE:
			if (!other->client->ps.stats[STAT_WEAPONS] & WP_GRENADE == WP_GRENADE &&
				(other->client->ps.ammo[ent->item->giTag] >= RQ3_GRENADE_MAXCLIP))
				return;
			break;
		
		//Blaze: Check and see if it's a unique weapon, and if so make sure they dont have too many already
		if (ent->item->giTag == WP_MP5 || ent->item->giTag == WP_M4 ||
			ent->item->giTag == WP_M3 || ent->item->giTag == WP_HANDCANNON ||
			ent->item->giTag == WP_SSG3000) {
			if (other->client->ps.stats[STAT_UNIQUEWEAPONS] >= g_rxn_maxweapons.integer) {
				return;
			}
		}
		*/
		
		respawn = Pickup_Weapon(ent, other);
		
		
		//Elder: added pistol and knife condition
		if (ent->item->giTag == WP_GRENADE || ent->item->giTag == WP_PISTOL ||
			ent->item->giTag == WP_KNIFE) {
//			G_Printf("Grenade Picked up (%d)\n",respawn);	
			respawn = 30;
		}
		else {
			//Elder: moved here
			respawn = -1; //Dont respawn weapons
		}
		
//		predict = qfalse;
		break;
	case IT_AMMO:
		switch(ent->item->giTag)
		{
			//Blaze: dont pick up the clip if we already have all the clips we can have
		case WP_KNIFE:
			if (other->client->numClips[ent->item->giTag] >= 0) return;//No clips for knifes
			break;
		case WP_PISTOL:
			if (other->client->numClips[ent->item->giTag] >= RQ3_PISTOL_MAXCLIP ) return;
			break;
		case WP_M3:
			if (other->client->numClips[ent->item->giTag] >= RQ3_M3_MAXCLIP) return;
			break;
		case WP_HANDCANNON:
			if (other->client->numClips[ent->item->giTag] >= RQ3_HANDCANNON_MAXCLIP) return;
			break;
		case WP_MP5:
			if (other->client->numClips[ent->item->giTag] >= RQ3_MP5_MAXCLIP ) return;
			break;
		case WP_M4:
			if (other->client->numClips[ent->item->giTag] >= RQ3_M4_MAXCLIP ) return;
			break;
		case WP_SSG3000:
			if (other->client->numClips[ent->item->giTag] >= RQ3_SSG3000_MAXCLIP ) return;
			break;
		case WP_AKIMBO:
			if (other->client->numClips[ent->item->giTag] >= RQ3_AKIMBO_MAXCLIP ) return;
			break;
		case WP_GRENADE:
			if (other->client->numClips[ent->item->giTag] >= 0 ) return;//no clips for grenades
			break;
		}
		respawn = Pickup_Ammo(ent, other);
//		predict = qfalse;
		break;
	case IT_ARMOR:
		respawn = Pickup_Armor(ent, other);
		break;
	case IT_HEALTH:
		respawn = Pickup_Health(ent, other);
		break;
	case IT_POWERUP:
		respawn = Pickup_Powerup(ent, other);
		predict = qfalse;
		break;
#ifdef MISSIONPACK
	case IT_PERSISTANT_POWERUP:
		respawn = Pickup_PersistantPowerup(ent, other);
		break;
#endif
	case IT_TEAM:
		respawn = Pickup_Team(ent, other);
		break;
	case IT_HOLDABLE:
		respawn = Pickup_Holdable(ent, other);
		break;
	default:
		return;
	}

	if ( !respawn ) {
		return;
	}

	// play the normal pickup sound
	if (predict) {
		G_AddPredictableEvent( other, EV_ITEM_PICKUP, ent->s.modelindex );
	} else {
		G_AddEvent( other, EV_ITEM_PICKUP, ent->s.modelindex );
	}

	// powerup pickups are global broadcasts
	if ( ent->item->giType == IT_POWERUP || ent->item->giType == IT_TEAM) {
		// if we want the global sound to play
		if (!ent->speed) {
		gentity_t	*te;

		te = G_TempEntity( ent->s.pos.trBase, EV_GLOBAL_ITEM_PICKUP );
		te->s.eventParm = ent->s.modelindex;
		te->r.svFlags |= SVF_BROADCAST;
		} else {
			gentity_t	*te;

			te = G_TempEntity( ent->s.pos.trBase, EV_GLOBAL_ITEM_PICKUP );
			te->s.eventParm = ent->s.modelindex;
			// only send this temp entity to a single client
			te->r.svFlags |= SVF_SINGLECLIENT;
			te->r.singleClient = other->s.number;
		}
	}

	// fire item targets
	G_UseTargets (ent, other);

	// wait of -1 will not respawn
	if ( ent->wait == -1 ) {
		ent->r.svFlags |= SVF_NOCLIENT;
		ent->s.eFlags |= EF_NODRAW;
		ent->r.contents = 0;
		ent->unlinkAfterEvent = qtrue;
		return;
	}

	// non zero wait overrides respawn time
	if ( ent->wait ) {
		respawn = ent->wait;
	}

	// random can be used to vary the respawn time
	if ( ent->random ) {
		respawn += crandom() * ent->random;
		if ( respawn < 1 ) {
			respawn = 1;
		}
	}

	// dropped items will not respawn
	if ( ent->flags & FL_DROPPED_ITEM ) {
		ent->freeAfterEvent = qtrue;
	}

	// picked up items still stay around, they just don't
	// draw anything.  This allows respawnable items
	// to be placed on movers.
	ent->r.svFlags |= SVF_NOCLIENT;
	ent->s.eFlags |= EF_NODRAW;
	ent->r.contents = 0;

	// ZOID
	// A negative respawn times means to never respawn this item (but don't 
	// delete it).  This is used by items that are respawned by third party 
	// events such as ctf flags
	if ( respawn <= 0 ) {
		ent->nextthink = 0;
		ent->think = 0;
	} else {
		ent->nextthink = level.time + respawn * 1000;
		ent->think = RespawnItem;
	}
	trap_LinkEntity( ent );
}


//======================================================================

/*
================
LaunchItem

Spawns an item and tosses it forward
================
*/
gentity_t *LaunchItem( gitem_t *item, vec3_t origin, vec3_t velocity, int xr_flags ) {
	gentity_t	*dropped;

	dropped = G_Spawn();

	dropped->s.eType = ET_ITEM;
	dropped->s.modelindex = item - bg_itemlist;	// store item number in modelindex
	dropped->s.modelindex2 = 1; // This is non-zero is it's a dropped item

	dropped->classname = item->classname;
	dropped->item = item;
	VectorSet (dropped->r.mins, -ITEM_RADIUS, -ITEM_RADIUS, -ITEM_RADIUS);
	VectorSet (dropped->r.maxs, ITEM_RADIUS, ITEM_RADIUS, ITEM_RADIUS);
	dropped->r.contents = CONTENTS_TRIGGER;

	dropped->touch = Touch_Item;

	//Elder: suspend thrown knives so they don't jitter
	G_Printf("xr_flags: %d, condition: %d\n", xr_flags, (xr_flags & FL_THROWN_KNIFE) == FL_THROWN_KNIFE);
	if (item->giTag == WP_KNIFE && ( (xr_flags & FL_THROWN_KNIFE) == FL_THROWN_KNIFE) ) {
		G_SetOrigin( dropped, origin );

		//reset back the dropped item case
		dropped->flags = FL_DROPPED_ITEM;
		//dropped->s.eFlags |= EF_BOUNCE_HALF;
	}
	else {
		G_SetOrigin( dropped, origin );
		dropped->s.pos.trType = TR_GRAVITY;
		dropped->s.pos.trTime = level.time;
		//Elder: should change to a constant velocity for weapons
		VectorCopy( velocity, dropped->s.pos.trDelta );
		
		//Elder: moved from outside else statement
		dropped->s.eFlags |= EF_BOUNCE_HALF;
	}

	
#ifdef MISSIONPACK
	if ((g_gametype.integer == GT_CTF || g_gametype.integer == GT_1FCTF)			&& item->giType == IT_TEAM) { // Special case for CTF flags
#else
	if (g_gametype.integer == GT_CTF && item->giType == IT_TEAM) { // Special case for CTF flags
#endif
		dropped->think = Team_DroppedFlagThink;
		dropped->nextthink = level.time + 30000;
		Team_CheckDroppedItem( dropped );
	}

	//Elder: Reaction Unique Weapons in deathmatch - respawn in ~60 seconds
	//Don't forget to condition it when we get teamplay in
	else if ( item->giType == IT_WEAPON &&
		item->giTag != WP_GRENADE && item->giTag != WP_PISTOL && 
		item->giTag != WP_AKIMBO && item->giTag != WP_KNIFE ) {
		dropped->think = RQ3_DroppedWeaponThink;
		//Elder: don't want to wait forever while testing :)
		dropped->nextthink = level.time + RQ3_RESPAWNTIME_DEFAULT;
	}

	else { // auto-remove after 30 seconds
		dropped->think = G_FreeEntity;
		dropped->nextthink = level.time + 30000;
	}

	dropped->flags = xr_flags;//FL_DROPPED_ITEM;
	if( xr_flags & FL_THROWN_ITEM) {
		dropped->clipmask = MASK_SHOT; // XRAY FMJ
		dropped->s.pos.trTime = level.time - 50;	// move a bit on the very first frame
		VectorScale( velocity, 200, dropped->s.pos.trDelta ); // 700 500 400
		SnapVector( dropped->s.pos.trDelta );		// save net bandwidth
		dropped->physicsBounce= 0;
	}

	trap_LinkEntity (dropped);

	return dropped;
}

/*
================
dropWeapon XRAY FMJ
================
*/
gentity_t *dropWeapon( gentity_t *ent, gitem_t *item, float angle, int xr_flags ) { // XRAY FMJ
	vec3_t	velocity;
	vec3_t  angles;
	vec3_t	origin;

	VectorCopy( ent->s.pos.trBase, origin );
	VectorCopy( ent->s.apos.trBase, angles );
	angles[YAW] += angle;
	angles[PITCH] = 0; // always forward

	AngleVectors( angles, velocity, NULL, NULL);
	//VectorScale( velocity, 150, velocity);

	// set aiming directions
	//AngleVectors (ent->client->ps.viewangles, velocity, NULL, NULL);

	origin[2] += ent->client->ps.viewheight;
	VectorMA( origin, 10, velocity, origin ); // 14 34
	// snap to integer coordinates for more efficient network bandwidth usage
	SnapVector( origin);

	// less vertical velocity
	//velocity[2] += 0.2f;
	//velocity[2] = 20;
	//G_Printf("Velocity: %s\n", vtos(velocity));
	VectorNormalize( velocity );
	VectorScale( velocity, 5, velocity);
	return LaunchItem( item, origin, velocity, xr_flags );
	//return LaunchItem( item, ent->s.pos.trBase, velocity, xr_flags );
}

/*
================
Drop_Item

Spawns an item and tosses it forward
================
*/
gentity_t *Drop_Item( gentity_t *ent, gitem_t *item, float angle ) {
	vec3_t	velocity;
	vec3_t	angles;

	VectorCopy( ent->s.apos.trBase, angles );
	angles[YAW] += angle;
	angles[PITCH] = 0;	// always forward

	AngleVectors( angles, velocity, NULL, NULL );
	VectorScale( velocity, 150, velocity );
	velocity[2] += 200 + crandom() * 50;
	
	return LaunchItem( item, ent->s.pos.trBase, velocity, FL_DROPPED_ITEM );
}


/*
================
Use_Item

Respawn the item
================
*/
void Use_Item( gentity_t *ent, gentity_t *other, gentity_t *activator ) {
	RespawnItem( ent );
}

//======================================================================

/*
================
FinishSpawningItem

Traces down to find where an item should rest, instead of letting them
free fall from their spawn points
================
*/
void FinishSpawningItem( gentity_t *ent ) {
	trace_t		tr;
	vec3_t		dest;

	VectorSet( ent->r.mins, -ITEM_RADIUS, -ITEM_RADIUS, -ITEM_RADIUS );
	VectorSet( ent->r.maxs, ITEM_RADIUS, ITEM_RADIUS, ITEM_RADIUS );

	ent->s.eType = ET_ITEM;
	ent->s.modelindex = ent->item - bg_itemlist;		// store item number in modelindex
	ent->s.modelindex2 = 0; // zero indicates this isn't a dropped item

	ent->r.contents = CONTENTS_TRIGGER;
	ent->touch = Touch_Item;
	// useing an item causes it to respawn
	ent->use = Use_Item;
	
	if ( ent->spawnflags & 1 ) {
		// suspended
		G_SetOrigin( ent, ent->s.origin );
	} else {
		// drop to floor
		VectorSet( dest, ent->s.origin[0], ent->s.origin[1], ent->s.origin[2] - 4096 );
		trap_Trace( &tr, ent->s.origin, ent->r.mins, ent->r.maxs, dest, ent->s.number, MASK_SOLID );
		if ( tr.startsolid ) {
			G_Printf ("FinishSpawningItem: %s startsolid at %s\n", ent->classname, vtos(ent->s.origin));
			G_FreeEntity( ent );
			return;
		}

		// allow to ride movers
		ent->s.groundEntityNum = tr.entityNum;

		G_SetOrigin( ent, tr.endpos );
	}

	// team slaves and targeted items aren't present at start
	if ( ( ent->flags & FL_TEAMSLAVE ) || ent->targetname ) {
		ent->s.eFlags |= EF_NODRAW;
		ent->r.contents = 0;
		return;
	}

	// powerups don't spawn in for a while
	if ( ent->item->giType == IT_POWERUP ) {
		float	respawn;

		respawn = 45 + crandom() * 15;
		ent->s.eFlags |= EF_NODRAW;
		ent->r.contents = 0;
		ent->nextthink = level.time + respawn * 1000;
		ent->think = RespawnItem;
		return;
	}


	trap_LinkEntity (ent);
}


qboolean	itemRegistered[MAX_ITEMS];

/*
==================
G_CheckTeamItems
==================
*/
void G_CheckTeamItems( void ) {

	// Set up team stuff
	Team_InitGame();

	if ( g_gametype.integer == GT_CTF ) {
		gitem_t	*item;

		// check for the two flags
		item = BG_FindItem( "Red Flag" );
		if ( !item || !itemRegistered[ item - bg_itemlist ] ) {
			G_Printf( S_COLOR_YELLOW "WARNING: No team_CTF_redflag in map" );
		}
		item = BG_FindItem( "Blue Flag" );
		if ( !item || !itemRegistered[ item - bg_itemlist ] ) {
			G_Printf( S_COLOR_YELLOW "WARNING: No team_CTF_blueflag in map" );
		}
	}
#ifdef MISSIONPACK
	if( g_gametype.integer == GT_1FCTF ) {
		gitem_t	*item;

		// check for all three flags
		item = BG_FindItem( "Red Flag" );
		if ( !item || !itemRegistered[ item - bg_itemlist ] ) {
			G_Printf( S_COLOR_YELLOW "WARNING: No team_CTF_redflag in map" );
		}
		item = BG_FindItem( "Blue Flag" );
		if ( !item || !itemRegistered[ item - bg_itemlist ] ) {
			G_Printf( S_COLOR_YELLOW "WARNING: No team_CTF_blueflag in map" );
		}
		item = BG_FindItem( "Neutral Flag" );
		if ( !item || !itemRegistered[ item - bg_itemlist ] ) {
			G_Printf( S_COLOR_YELLOW "WARNING: No team_CTF_neutralflag in map" );
		}
	}

	if( g_gametype.integer == GT_OBELISK ) {
		gentity_t	*ent;

		// check for the two obelisks
		ent = NULL;
		ent = G_Find( ent, FOFS(classname), "team_redobelisk" );
		if( !ent ) {
			G_Printf( S_COLOR_YELLOW "WARNING: No team_redobelisk in map" );
		}

		ent = NULL;
		ent = G_Find( ent, FOFS(classname), "team_blueobelisk" );
		if( !ent ) {
			G_Printf( S_COLOR_YELLOW "WARNING: No team_blueobelisk in map" );
		}
	}

	if( g_gametype.integer == GT_HARVESTER ) {
		gentity_t	*ent;

		// check for all three obelisks
		ent = NULL;
		ent = G_Find( ent, FOFS(classname), "team_redobelisk" );
		if( !ent ) {
			G_Printf( S_COLOR_YELLOW "WARNING: No team_redobelisk in map" );
		}

		ent = NULL;
		ent = G_Find( ent, FOFS(classname), "team_blueobelisk" );
		if( !ent ) {
			G_Printf( S_COLOR_YELLOW "WARNING: No team_blueobelisk in map" );
		}

		ent = NULL;
		ent = G_Find( ent, FOFS(classname), "team_neutralobelisk" );
		if( !ent ) {
			G_Printf( S_COLOR_YELLOW "WARNING: No team_neutralobelisk in map" );
		}
	}
#endif
}

/*
==============
ClearRegisteredItems
==============
*/
void ClearRegisteredItems( void ) {
	memset( itemRegistered, 0, sizeof( itemRegistered ) );

	// players always start with the base weapon
	//Blaze: Changed WP_MACHINEGUN to WP_PISTOL and WP_GAUNTLET to WP_KNIFE
	RegisterItem( BG_FindItemForWeapon( WP_PISTOL ) );
	RegisterItem( BG_FindItemForWeapon( WP_KNIFE ) );
#ifdef MISSIONPACK
	if( g_gametype.integer == GT_HARVESTER ) {
		RegisterItem( BG_FindItem( "Red Cube" ) );
		RegisterItem( BG_FindItem( "Blue Cube" ) );
	}
#endif
}

/*
===============
RegisterItem

The item will be added to the precache list
===============
*/
void RegisterItem( gitem_t *item ) {
	if ( !item ) {
		G_Error( "RegisterItem: NULL" );
	}
	itemRegistered[ item - bg_itemlist ] = qtrue;
}


/*
===============
SaveRegisteredItems

Write the needed items to a config string
so the client will know which ones to precache
===============
*/
void SaveRegisteredItems( void ) {
	char	string[MAX_ITEMS+1];
	int		i;
	int		count;

	count = 0;
	for ( i = 0 ; i < bg_numItems ; i++ ) {
		if ( itemRegistered[i] ) {
			count++;
			string[i] = '1';
		} else {
			string[i] = '0';
		}
	}
	string[ bg_numItems ] = 0;

	G_Printf( "%i items registered\n", count );
	trap_SetConfigstring(CS_ITEMS, string);
}

/*
============
G_ItemDisabled
============
*/
int G_ItemDisabled( gitem_t *item ) {

	char name[128];

	Com_sprintf(name, sizeof(name), "disable_%s", item->classname);
	return trap_Cvar_VariableIntegerValue( name );
}

/*
============
G_SpawnItem

Sets the clipping size and plants the object on the floor.

Items can't be immediately dropped to floor, because they might
be on an entity that hasn't spawned yet.
============
*/
void G_SpawnItem (gentity_t *ent, gitem_t *item) {
	G_SpawnFloat( "random", "0", &ent->random );
	G_SpawnFloat( "wait", "0", &ent->wait );

	RegisterItem( item );
	if ( G_ItemDisabled(item) )
		return;

	ent->item = item;
	// some movers spawn on the second frame, so delay item
	// spawns until the third frame so they can ride trains
	ent->nextthink = level.time + FRAMETIME * 2;
	ent->think = FinishSpawningItem;

	ent->physicsBounce = 0.50;		// items are bouncy

	if ( item->giType == IT_POWERUP ) {
		G_SoundIndex( "sound/items/poweruprespawn.wav" );
		G_SpawnFloat( "noglobalsound", "0", &ent->speed);
	}

#ifdef MISSIONPACK
	if ( item->giType == IT_PERSISTANT_POWERUP ) {
		ent->s.generic1 = ent->spawnflags;
	}
#endif
}


/*
================
G_BounceItem

================
*/
void G_BounceItem( gentity_t *ent, trace_t *trace ) {
	vec3_t	velocity;
	float	dot;
	int		hitTime;

	// reflect the velocity on the trace plane
	hitTime = level.previousTime + ( level.time - level.previousTime ) * trace->fraction;
	BG_EvaluateTrajectoryDelta( &ent->s.pos, hitTime, velocity );
	dot = DotProduct( velocity, trace->plane.normal );
	VectorMA( velocity, -2*dot, trace->plane.normal, ent->s.pos.trDelta );

	// cut the velocity to keep from bouncing forever
	VectorScale( ent->s.pos.trDelta, ent->physicsBounce, ent->s.pos.trDelta );

	// check for stop
	if ( trace->plane.normal[2] > 0 && ent->s.pos.trDelta[2] < 40 ) {
		trace->endpos[2] += 1.0;	// make sure it is off ground
		SnapVector( trace->endpos );
		G_SetOrigin( ent, trace->endpos );
		ent->s.groundEntityNum = trace->entityNum;
		return;
	}

	VectorAdd( ent->r.currentOrigin, trace->plane.normal, ent->r.currentOrigin);
	VectorCopy( ent->r.currentOrigin, ent->s.pos.trBase );
	ent->s.pos.trTime = level.time;
}


/*
================
G_RunItem

================
*/
void G_RunItem( gentity_t *ent ) {
	vec3_t		origin;
	trace_t		tr;
	int			contents;
	int			mask;

	// if groundentity has been set to -1, it may have been pushed off an edge
	if ( ent->s.groundEntityNum == -1 ) {
		if ( ent->s.pos.trType != TR_GRAVITY ) {
			ent->s.pos.trType = TR_GRAVITY;
			ent->s.pos.trTime = level.time;
		}
	}

	if ( ent->s.pos.trType == TR_STATIONARY ) {
		// check think function
		G_RunThink( ent );
		return;
	}

	// get current position
	BG_EvaluateTrajectory( &ent->s.pos, level.time, origin );

	// trace a line from the previous position to the current position
	if ( ent->clipmask ) {
		mask = ent->clipmask;
	} else {
		mask = MASK_PLAYERSOLID & ~CONTENTS_BODY;//MASK_SOLID;
	}
	trap_Trace( &tr, ent->r.currentOrigin, ent->r.mins, ent->r.maxs, origin, 
		ent->r.ownerNum, mask );

	VectorCopy( tr.endpos, ent->r.currentOrigin );

	if ( tr.startsolid ) {
		tr.fraction = 0;
	}

	trap_LinkEntity( ent );	// FIXME: avoid this for stationary?

	// check think function
	G_RunThink( ent );

	if ( tr.fraction == 1 ) {
		return;
	}

	// if it is in a nodrop volume, remove it
	contents = trap_PointContents( ent->r.currentOrigin, -1 );
	if ( contents & CONTENTS_NODROP ) {
		if (ent->item && ent->item->giType == IT_TEAM) {
			Team_FreeEntity(ent);
		} else {
			G_FreeEntity( ent );
		}
		return;
	}

	G_BounceItem( ent, &tr );
}

/*
==============
Added by Elder

RQ3_DroppedWeaponThink
Get the item name from the entity and forward
it to RQ3_ResetWeapon to find and respawn

This is like respawning CTF flags in baseq3
==============
*/
void RQ3_DroppedWeaponThink(gentity_t *ent) {
	int	weaponNum = WP_NONE;

	switch (ent->item->giTag) {
    	case WP_MP5:
    	case WP_M4:
    	case WP_M3:
    	case WP_HANDCANNON:
    	case WP_SSG3000:
    		weaponNum = ent->item->giTag;
    		break;
    		
    	case WP_PISTOL:
    	case WP_KNIFE:
    	case WP_AKIMBO:
    	case WP_GRENADE:
    	default:
    		//Elder: shouldn't have to come here
    		G_Printf("DroppedWeaponThink: Out of range weapon %d\n", ent->item->giTag);
    		return;
    		break;
	}
	//Elder: flag the item we want to remove
	ent->flags |= FL_RQ3_JUNKITEM;
	RQ3_ResetWeapon( weaponNum );
	// Reset Weapon will delete this entity
}

/*
==============
Added by Elder

RQ3_ResetWeapon
Respawn a unique weapon

Similar to CTF Flag reset
A little quirky - maybe someone can fine-tune this!
Bugs:
The weapon may not return to its original location if there is
more than one of the type.  It just finds the closest empty spot
and respawns it.
==============
*/
void RQ3_ResetWeapon( int weapon ) {
	char *c;
	gentity_t *ent; //, *rent = NULL;
	int numRespawned = 0;
	int numRemoved = 0;
	
	switch (weapon) {
	case WP_M3:
		c = "weapon_m3";
		break;
	case WP_M4:
		c = "weapon_m4";
		break;	
	case WP_MP5:
		c = "weapon_mp5";
		break;
	case WP_SSG3000:
		c = "weapon_ssg3000";
		break;
	case WP_HANDCANNON:
		c = "weapon_handcannon";
		break;
	default:
		//Elder: shouldn't be here
		G_Printf("RQ3_ResetWeapon: Received bad weapon: %d\n", weapon);
		break;
	}

	ent = NULL;
	//Elder: here's the solution and another problem to RQ3 weapon respawns
	while ((ent = G_Find (ent, FOFS(classname), c)) != NULL) {
		//if it's a dropped copy, free it
		//if (ent->flags & FL_DROPPED_ITEM) {
		//Elder: only release if it's past the
		//default respawn time and is flagged
		if (numRemoved < 1 &&
			(ent->flags & FL_DROPPED_ITEM) == FL_DROPPED_ITEM &&
			(ent->flags & FL_RQ3_JUNKITEM) == FL_RQ3_JUNKITEM ) {
			//Elder: removed because of possible door collision removal
			//level.time - ent->timestamp >= RQ3_RESPAWNTIME_DEFAULT) {
			G_FreeEntity(ent);
			numRemoved++;
		}
		else {
			//rent = ent;
			//Elder: only respawn if it's a "taken" item
			//It won't necessarily respawn the gun in its original spot if there's
			//more than one, but it will put it in an empty location... good enough?
			if ( (ent->r.svFlags & SVF_NOCLIENT) == SVF_NOCLIENT &&
				 (ent->s.eFlags & EF_NODRAW) == EF_NODRAW &&
				ent->r.contents == 0 && numRespawned < 1) {
				RespawnItem(ent);
				numRespawned++;
				}
		}
	}
	
	//return rent;
}
