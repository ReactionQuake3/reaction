//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.64  2002/03/30 02:54:24  jbravo
// MOre spec tweaks and a scoreboard fix
//
// Revision 1.63  2002/03/30 02:29:43  jbravo
// Lots of spectator code updates. Removed debugshit, added some color.
//
// Revision 1.62  2002/03/26 11:32:04  jbravo
// Remember specstate between rounds.
//
// Revision 1.61  2002/03/23 21:29:42  jbravo
// I finally fixed snipers spawning with pistol up. g_RQ3_sniperup has been
// reinstated.
//
// Revision 1.60  2002/03/23 05:17:42  jbravo
// Major cleanup of game -> cgame communication with LCA vars.
//
// Revision 1.59  2002/03/18 19:18:39  slicer
// Fixed bandage bugs ( i hope )
//
// Revision 1.58  2002/03/02 12:24:30  jbravo
// Removed some debugging messages
//
// Revision 1.57  2002/02/27 01:54:29  jbravo
// More spectatorfixes and finally stopped all fallingdamage anims and
// sounds during LCA.
//
// Revision 1.56  2002/02/26 02:58:47  jbravo
// Fixing the spectator_free mode not being predicted in the client.
//
// Revision 1.55  2002/02/25 19:41:53  jbravo
// Fixed the use ESC and join menu to join teams when dead players are
// spectating in TP mode.
// Tuned the autorespawn system a bit.  Now dead ppl. are dead for a very
// small time before they are made into spectators.
//
// Revision 1.54  2002/02/23 16:55:09  jbravo
// Added debugging to help find what was going with can't find item for weapon
// error that crash the server.
//
// Revision 1.53  2002/02/22 02:13:13  jbravo
// Fixed a few bugs and did some cleanups
//
// Revision 1.52  2002/02/10 21:21:22  slicer
// Saving persistant and other data on some events..
//
// Revision 1.51  2002/02/10 18:38:42  jbravo
// Added new SPECTATOR_ZCAM spec mode.
//
// Revision 1.50  2002/02/10 17:20:45  jbravo
// Attempting to fix the camera freeze in the begining of the game
//
// Revision 1.49  2002/02/09 18:27:44  slicer
// Spectator code: +attack button to change view, and jump to switch player
//
// Revision 1.48  2002/02/09 00:10:12  jbravo
// Fixed spectator follow and free and updated zcam to 1.04 and added the
// missing zcam files.
//
// Revision 1.47  2002/02/08 18:59:01  slicer
// Spec code changes
//
// Revision 1.46  2002/02/06 12:06:48  slicer
// TP Scores bug fix
//
// Revision 1.45  2002/02/06 03:10:43  jbravo
// Fix the instant spectate on death and an attempt to fix the scores
//
// Revision 1.44  2002/01/29 03:13:45  jbravo
// Further fixes to antistick
//
// Revision 1.43  2002/01/27 13:33:28  jbravo
// Teamplay antistick system.
//
// Revision 1.42  2002/01/11 20:20:58  jbravo
// Adding TP to main branch
//
// Revision 1.41  2002/01/11 19:48:30  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.40  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//

#include "g_local.h"
// JBravo: need TP functions
#include "g_teamplay.h"

#ifdef  __ZCAM__
#include "zcam.h"
#endif /* __ZCAM__ */


//Elder: got rid of these
//extern float	s_quadFactor;
//extern vec3_t	forward, right, up;
//extern vec3_t	muzzle;
//extern void Cmd_OpenDoor( gentity_t * );

//Elder: moved kick to g_weapon.c where it belongs


/*
===============
G_DamageFeedback

Called just before a snapshot is sent to the given player.
Totals up all damage and generates both the player_state_t
damage values to that client for pain blends and kicks, and
global pain sound events for all clients.
===============
*/
void P_DamageFeedback( gentity_t *player ) {
//	gentity_t	*tent;
	gclient_t	*client;
	float	count, side;
	vec3_t	angles, v;
	vec3_t	forward, right, up;

	client = player->client;
	if ( client->ps.pm_type == PM_DEAD ) {
		return;
	}

	// total points of damage shot at the player this frame
	//if (client->damage_blood > 0)
		//G_Printf("(%i) Damage_blood: %i\n", player->s.clientNum, client->damage_blood);

	//if (client->damage_knockback > 0)
		//G_Printf("(%i) Damage_knockback: %i\n", player->s.clientNum, client->damage_knockback);

	count = client->damage_blood + client->damage_armor;
	if ( count == 0 ) {
		return;		// didn't take any damage
	}

	if ( count > 255 ) {
		count = 255;
	}

	// send the information to the client

	// world damage (falling, slime, etc) uses a special code
	// to make the blend blob centered instead of positional
	if ( client->damage_fromWorld ) {
		client->ps.damagePitch = 255;
		client->ps.damageYaw = 255;

		client->damage_fromWorld = qfalse;
	} else {
		vectoangles( client->damage_from, angles );
// Q3 Code
/*		client->ps.damagePitch = angles[PITCH]/360.0 * 256;
		client->ps.damageYaw = angles[YAW]/360.0 * 256;*/


		// new RQ3 view-kick code, needs more tweaking (the 50 needs to be replaces with that below calcuation
		// from the AQ2 code.

		// set aiming directions
		AngleVectors (client->ps.viewangles, forward, right, up);

		VectorSubtract(client->damage_from, player->s.origin , v);
		VectorNormalize(v);

		side = -DotProduct(v,forward);
		client->ps.damagePitch = 50*side*0.3;

		side = - DotProduct(v,right);
		client->ps.damageYaw = 50*side*0.3;

	}

	/*	AQ2 code pasted here for reference

   kick = abs(client->damage_knockback);
  if (kick && player->health > 0) // kick of 0 means no view adjust at all
  {
    kick = kick * 100 / player->health;

    if (kick < count*0.5)
      kick = count*0.5;
    if (kick > 50)
      kick = 50;

    VectorSubtract (client->damage_from, player->s.origin, v);
    VectorNormalize (v);

    side = DotProduct (v, right);
    client->v_dmg_roll = kick*side*0.3;

    side = -DotProduct (v, forward);
    client->v_dmg_pitch = kick*side*0.3;

    client->v_dmg_time = level.time + DAMAGE_TIME;




  */

	/*
	G_Printf("Lasthurt: %d, Head: %d, Face: %d, And-Op: %d\n",
			client->lasthurt_location,
			LOCATION_HEAD, LOCATION_FACE,
			client->lasthurt_location & ~(LOCATION_BACK | LOCATION_LEFT | LOCATION_RIGHT | LOCATION_FRONT) );
	*/

	// play an appropriate pain sound
	if ( (level.time > player->pain_debounce_time) && !(player->flags & FL_GODMODE) ) {
		//player->pain_debounce_time = level.time + 700;
		//Elder: reduced pain debounce time so we can have a few more sounds :)
		player->pain_debounce_time = level.time + 250;

		switch ( client->lasthurt_location &
             ~(LOCATION_BACK | LOCATION_LEFT | LOCATION_RIGHT | LOCATION_FRONT) ) {
		//Elder: headshot sound
        case LOCATION_HEAD:
        case LOCATION_FACE:
			if (client->lasthurt_mod == MOD_KNIFE || client->lasthurt_mod == MOD_KNIFE_THROWN)
				G_AddEvent( player, EV_RQ3_SOUND, RQ3_SOUND_KNIFEDEATH);
			//Elder: do nothing -- sound is handled in g_combat.c again
			//tent = G_TempEntity2(client->ps.origin, EV_RQ3_SOUND, RQ3_SOUND_HEADSHOT);
			//Elder: takes more bandwidth but guarantees a headshot sound
			//G_Sound(player, CHAN_AUTO, G_SoundIndex("sound/misc/headshot.wav"));
			//G_AddEvent ( player, EV_RQ3_SOUND, RQ3_SOUND_HEADSHOT);
			break;
		/*
		case LOCATION_CHEST:
		case LOCATION_SHOULDER:
			G_AddEvent( player, EV_PAIN, player->health );
			break;
		*/
		default:
			G_AddEvent( player, EV_PAIN, player->health );
			break;
		}

		client->ps.damageEvent++;
	}

	client->ps.damageCount = count;

	// Elder: HC Smoke
	/*
	if (client->lasthurt_mod == MOD_HANDCANNON)
	{
		G_Printf("Feedback: damage_blood: %i, damage_knockback: %i\n",
			client->damage_blood, client->damage_knockback);
	}
	*/
	if (client->lasthurt_mod == MOD_HANDCANNON &&
		client->damage_blood >= 120 &&
		client->damage_knockback >= RQ3_HANDCANNON_KICK * 6)
	{
		client->ps.eFlags |= EF_HANDCANNON_SMOKED;
	}

	//
	// clear totals
	//
	client->damage_blood = 0;
	client->damage_armor = 0;
	client->damage_knockback = 0;
}



/*
=============
P_WorldEffects

Check for lava / slime contents and drowning
=============
*/
void P_WorldEffects( gentity_t *ent ) {
	qboolean	envirosuit;
	int			waterlevel;

	if ( ent->client->noclip ) {
		ent->client->airOutTime = level.time + 12000;	// don't need air
		return;
	}

	waterlevel = ent->waterlevel;

	envirosuit = ent->client->ps.powerups[PW_BATTLESUIT] > level.time;

	//
	// check for drowning
	//
	if ( waterlevel == 3 ) {
		// envirosuit give air
		if ( envirosuit ) {
			ent->client->airOutTime = level.time + 10000;
		}

		// if out of air, start drowning
		if ( ent->client->airOutTime < level.time) {
			// drown!
			ent->client->airOutTime += 1000;
			if ( ent->health > 0 ) {
				// take more damage the longer underwater
				ent->damage += 2;
				if (ent->damage > 15)
					ent->damage = 15;

				// play a gurp sound instead of a normal pain sound
				if (ent->health <= ent->damage) {
					G_Sound(ent, CHAN_VOICE, G_SoundIndex("*drown.wav"));
				} else if (rand()&1) {
					G_Sound(ent, CHAN_VOICE, G_SoundIndex("sound/player/gurp1.wav"));
				} else {
					G_Sound(ent, CHAN_VOICE, G_SoundIndex("sound/player/gurp2.wav"));
				}

				// don't play a normal pain sound
				ent->pain_debounce_time = level.time + 200;

				G_Damage (ent, NULL, NULL, NULL, NULL,
					ent->damage, DAMAGE_NO_ARMOR, MOD_WATER);
			}
		}
	} else {
		ent->client->airOutTime = level.time + 12000;
		ent->damage = 2;
	}

	//
	// check for sizzle damage (move to pmove?)
	//
	if (waterlevel &&
		(ent->watertype&(CONTENTS_LAVA|CONTENTS_SLIME)) ) {
		/*
		if (ent->health > 0
			&& ent->pain_debounce_time <= level.time	) {
		*/
		// Elder: changed around a bit -- using timestamp variable
		if ( ent->health > 0 && level.time > ent->timestamp)
		{
			if ( envirosuit ) {
				G_AddEvent( ent, EV_POWERUP_BATTLESUIT, 0 );
			} else {
				if (ent->watertype & CONTENTS_LAVA) {
					//G_Damage (ent, NULL, NULL, NULL, NULL,
						//30*waterlevel, 0, MOD_LAVA);
					G_Damage (ent, NULL, NULL, NULL, NULL,
						3*waterlevel, 0, MOD_LAVA);
				}

				if (ent->watertype & CONTENTS_SLIME) {
					//G_Damage (ent, NULL, NULL, NULL, NULL,
						//10*waterlevel, 0, MOD_SLIME);
					G_Damage (ent, NULL, NULL, NULL, NULL,
						waterlevel, 0, MOD_SLIME);
				}
				// Elder: added
				ent->timestamp = level.time + FRAMETIME;
			}
		}
	}
}



/*
===============
G_SetClientSound
===============
*/
void G_SetClientSound( gentity_t *ent ) {
#ifdef MISSIONPACK
	if( ent->s.eFlags & EF_TICKING ) {
		//Elder: removed
		//ent->client->ps.loopSound = G_SoundIndex( "sound/weapons/proxmine/wstbtick.wav");
	}
	else
#endif
	if (ent->waterlevel && (ent->watertype&(CONTENTS_LAVA|CONTENTS_SLIME)) ) {
		ent->client->ps.loopSound = level.snd_fry;
	} else {
		ent->client->ps.loopSound = 0;
	}
}



//==============================================================

/*
==============
ClientImpacts
==============
*/
void ClientImpacts( gentity_t *ent, pmove_t *pm ) {
	int		i, j;
	trace_t	trace;
	gentity_t	*other;

	memset( &trace, 0, sizeof( trace ) );
	for (i=0 ; i<pm->numtouch ; i++) {
		for (j=0 ; j<i ; j++) {
			if (pm->touchents[j] == pm->touchents[i] ) {
				break;
			}
		}
		if (j != i) {
			continue;	// duplicated
		}
		other = &g_entities[ pm->touchents[i] ];

		if ( ( ent->r.svFlags & SVF_BOT ) && ( ent->touch ) ) {
			ent->touch( ent, other, &trace );
		}

		if ( !other->touch ) {
			continue;
		}

		other->touch( other, ent, &trace );
	}

}

/*
============
G_TouchTriggers

Find all trigger entities that ent's current position touches.
Spectators will only interact with teleporters (and door triggers for spectators)
============
*/
void	G_TouchTriggers( gentity_t *ent ) {
	int			i, num;
	int			touch[MAX_GENTITIES];
	gentity_t	*hit;
	trace_t		trace;
	vec3_t		mins, maxs;
	static vec3_t	range = { 40, 40, 52 };

	if ( !ent->client ) {
		return;
	}

	// dead clients don't activate triggers!
	if ( ent->client->ps.stats[STAT_HEALTH] <= 0 ) {
		return;
	}

	VectorSubtract( ent->client->ps.origin, range, mins );
	VectorAdd( ent->client->ps.origin, range, maxs );

	num = trap_EntitiesInBox( mins, maxs, touch, MAX_GENTITIES );

	// can't use ent->absmin, because that has a one unit pad
	VectorAdd( ent->client->ps.origin, ent->r.mins, mins );
	VectorAdd( ent->client->ps.origin, ent->r.maxs, maxs );

	for ( i=0 ; i<num ; i++ ) {
		hit = &g_entities[touch[i]];

		if ( !hit->touch && !ent->touch ) {
			continue;
		}
		if ( !( hit->r.contents & CONTENTS_TRIGGER ) ) {
			continue;
		}

		// ignore most entities if a spectator
		if ( ent->client->sess.sessionTeam == TEAM_SPECTATOR ) {
			if ( hit->s.eType != ET_TELEPORT_TRIGGER &&
				// this is ugly but adding a new ET_? type will
				// most likely cause network incompatibilities
				// NiceAss: changed Touch_DoorTrigger to Touch_DoorTriggerSpectator
				hit->touch != Touch_DoorTriggerSpectator) {
				continue;
			}
		}

		// use seperate code for determining if an item is picked up
		// so you don't have to actually contact its bounding box
		if ( hit->s.eType == ET_ITEM ) {
			if ( !BG_PlayerTouchesItem( &ent->client->ps, &hit->s, level.time ) ) {
				continue;
			}
		} else {
			if ( !trap_EntityContact( mins, maxs, hit ) ) {
				continue;
			}
		}

		memset( &trace, 0, sizeof(trace) );

		if ( hit->touch ) {
			hit->touch (hit, ent, &trace);
		}

		if ( ( ent->r.svFlags & SVF_BOT ) && ( ent->touch ) ) {
			ent->touch( ent, hit, &trace );
		}
	}

	// if we didn't touch a jump pad this pmove frame
	if ( ent->client->ps.jumppad_frame != ent->client->ps.pmove_framecount ) {
		ent->client->ps.jumppad_frame = 0;
		ent->client->ps.jumppad_ent = 0;
	}

	if (ent->client->openDoor == 2) {
		ent->client->openDoor = qfalse;
		ent->client->openDoorTime = 0;
	}
}

/*
=================
SpectatorThink
NiceAss: Heavy modifications will be here for AQ2-like spectator mode and zcam!?
=================
*/
void SpectatorThink( gentity_t *ent, usercmd_t *ucmd ) {
	pmove_t	pm;
	gclient_t	*client;
	int		clientNum;

	client = ent->client;
	clientNum = client - level.clients;

	if (client->sess.spectatorState == SPECTATOR_ZCAM) {
		client->ps.commandTime = ucmd->serverTime;
		camera_think(ent);
	}

	if (client->sess.spectatorState == SPECTATOR_FREE) {
		client->ps.pm_type = PM_SPECTATOR;
		client->ps.speed = 400;	// faster than normal

		// set up for pmove
		memset (&pm, 0, sizeof(pm));
		pm.ps = &client->ps;
		pm.cmd = *ucmd;
		pm.tracemask = MASK_PLAYERSOLID & ~CONTENTS_BODY;	// spectators can fly through bodies
		pm.trace = trap_Trace;
		pm.pointcontents = trap_PointContents;

		// perform a pmove
		Pmove (&pm);
		// save results of pmove
		VectorCopy( client->ps.origin, ent->s.origin );

		G_TouchTriggers( ent );
		trap_UnlinkEntity( ent );
	}

	//Slicer - Changing this for aq2 way
	// Jump button cycles throught spectators
	if(client->sess.spectatorState == SPECTATOR_FOLLOW || client->sess.spectatorState == SPECTATOR_ZCAM) {
		if(ucmd->upmove >=10 ) {
			if (!(client->ps.pm_flags & PMF_JUMP_HELD)) {
				client->ps.pm_flags |= PMF_JUMP_HELD;
				if (client->sess.spectatorState == SPECTATOR_ZCAM)
					CameraSwingCycle(ent, 1);
				else
					Cmd_FollowCycle_f(ent, 1);
			}
		}
		else
			client->ps.pm_flags &= ~PMF_JUMP_HELD;
	}

	client->oldbuttons = client->buttons;
	client->buttons = ucmd->buttons;

	// Attack Button cycles throught free view, follow or zcam
	if((ucmd->buttons & BUTTON_ATTACK) && !(client->oldbuttons & BUTTON_ATTACK)) {
		if (client->sess.spectatorState == SPECTATOR_FREE && OKtoFollow(clientNum)) {
			client->sess.spectatorState = SPECTATOR_ZCAM;
			client->specMode = SPECTATOR_ZCAM;
			client->ps.stats[STAT_RQ3] |= RQ3_ZCAM;
			client->ps.pm_flags &= ~PMF_FOLLOW;
			CameraSwingCycle(ent, 1);
			RQ3_SpectatorMode(ent);
		} else if (client->sess.spectatorState == SPECTATOR_ZCAM && OKtoFollow(clientNum)) {
			client->sess.spectatorState = SPECTATOR_FOLLOW;
			client->specMode = SPECTATOR_FOLLOW;
			client->ps.pm_flags |= PMF_FOLLOW;
			client->ps.stats[STAT_RQ3] &= ~RQ3_ZCAM;
			Cmd_FollowCycle_f(ent, 1);
			RQ3_SpectatorMode(ent);
		} else if (client->sess.spectatorState == SPECTATOR_FOLLOW) {
			client->sess.spectatorState = SPECTATOR_FREE;
			client->specMode = SPECTATOR_FREE;
			client->ps.pm_flags &= ~PMF_FOLLOW;
			client->ps.stats[STAT_RQ3] &= ~RQ3_ZCAM;
			StopFollowing(ent);
			RQ3_SpectatorMode(ent);
		}
	}
}


/*
=================
ClientInactivityTimer

Returns qfalse if the client is dropped
=================
*/
qboolean ClientInactivityTimer( gclient_t *client ) {
	if ( ! g_inactivity.integer ) {
		// give everyone some time, so if the operator sets g_inactivity during
		// gameplay, everyone isn't kicked
		client->inactivityTime = level.time + 60 * 1000;
		client->inactivityWarning = qfalse;
	} else if ( client->pers.cmd.forwardmove ||
		client->pers.cmd.rightmove ||
		client->pers.cmd.upmove ||
		(client->pers.cmd.buttons & BUTTON_ATTACK) ) {
		client->inactivityTime = level.time + g_inactivity.integer * 1000;
		client->inactivityWarning = qfalse;
	} else if ( !client->pers.localClient ) {
		if ( level.time > client->inactivityTime ) {
			trap_DropClient( client - level.clients, "Dropped due to inactivity" );
			return qfalse;
		}
		if ( level.time > client->inactivityTime - 10000 && !client->inactivityWarning ) {
			client->inactivityWarning = qtrue;
			trap_SendServerCommand( client - level.clients, "cp \"Ten seconds until inactivity drop!\n\"" );
		}
	}
	return qtrue;
}

/*
==================
ClientTimerActions

Actions that happen once a second
==================
*/
void ClientTimerActions( gentity_t *ent, int msec ) {
	gclient_t *client;
#ifdef MISSIONPACK
	int			maxHealth;
#endif

	client = ent->client;
	client->timeResidual += msec;

	while ( client->timeResidual >= 1000 ) {
		client->timeResidual -= 1000;

//		else if(ent->client->isbleeding)
//			ent->client->isbleeding = qfalse;

		// regenerate
#ifdef MISSIONPACK
		if( bg_itemlist[client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_GUARD ) {
			maxHealth = client->ps.stats[STAT_MAX_HEALTH] / 2;
		}
		else if ( client->ps.powerups[PW_REGEN] ) {
			maxHealth = client->ps.stats[STAT_MAX_HEALTH];
		}
		else {
			maxHealth = 0;
		}
		if( maxHealth ) {
			if ( ent->health < maxHealth ) {
				ent->health += 15;
				if ( ent->health > maxHealth * 1.1 ) {
					ent->health = maxHealth * 1.1;
				}
				G_AddEvent( ent, EV_POWERUP_REGEN, 0 );
			} else if ( ent->health < maxHealth * 2) {
				ent->health += 5;
				if ( ent->health > maxHealth * 2 ) {
					ent->health = maxHealth * 2;
				}
				G_AddEvent( ent, EV_POWERUP_REGEN, 0 );
			}
#else
		if ( client->ps.powerups[PW_REGEN] ) {
			if ( ent->health < 100) { //max health 100 client->ps.stats[STAT_MAX_HEALTH]) {
				ent->health += 15;
				if ( ent->health > 110) { //max health is 100x1.1   client->ps.stats[STAT_MAX_HEALTH] * 1.1 ) {
					ent->health = 110; //max health is 100x1.1 client->ps.stats[STAT_MAX_HEALTH] * 1.1;
				}
				G_AddEvent( ent, EV_POWERUP_REGEN, 0 );
			} else if ( ent->health < 200 ) { //max health is 200 in this case client->ps.stats[STAT_MAX_HEALTH] * 2) {
				ent->health += 5;
				if ( ent->health > 200) { // max health is 200 client->ps.stats[STAT_MAX_HEALTH] * 2 ) {
					ent->health = 200; //max health is 200 client->ps.stats[STAT_MAX_HEALTH] * 2;
				}
				G_AddEvent( ent, EV_POWERUP_REGEN, 0 );
			}
#endif
		} else {
			// count down health when over max
			if ( ent->health > 100 ) { //max is 100 client->ps.stats[STAT_MAX_HEALTH] ) {
				ent->health--;
			}
		}

		// count down armor when over max
		if ( client->ps.stats[STAT_ARMOR] > 100) {// max is 100 client->ps.stats[STAT_MAX_HEALTH] ) {
			client->ps.stats[STAT_ARMOR]--;
		}

		//Blaze: Do bandaging stuff
		if (ent->client->bleedtick > 1)
		{
			//G_Printf("Bleedtick (%d) getting lowered by one (%d)\n", ent->client->bleedtick, client->timeResidual);
			ent->client->bleedtick--;
		}
		else if (ent->client->bleedtick == 1)
		{
			ent->client->bleed_remain = 0;
			ent->client->bleeding = 0;
			ent->client->bleedtick = 0;
			ent->client->bleedBandageCount = 0;
			//Elder: remove bandage work
		//	ent->client->ps.stats[STAT_RQ3] &= ~RQ3_BANDAGE_WORK;
			//Elder: moved from somewhere - err, g_cmds.c I think
			ent->client->ps.stats[STAT_RQ3] &= ~RQ3_LEGDAMAGE;
//			ent->client->ps.weaponstate = WEAPON_RAISING;
//			ent->client->ps.torsoAnim = ( ( ent->client->ps.torsoAnim & ANIM_TOGGLEBIT ) ^ ANIM_TOGGLEBIT )      | TORSO_RAISE;
			// NiceAss: clear last player to hit you.
			ent->client->lasthurt_mod = 0;
		}

	}


#ifdef MISSIONPACK
	if( bg_itemlist[client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_AMMOREGEN ) {
		int w, max, inc, t, i;
    int weapList[]={WP_MACHINEGUN,WP_SHOTGUN,WP_GRENADE_LAUNCHER,WP_ROCKET_LAUNCHER,WP_LIGHTNING,WP_RAILGUN,WP_PLASMAGUN,WP_BFG,WP_NAILGUN,WP_PROX_LAUNCHER,WP_CHAINGUN};
    int weapCount = sizeof(weapList) / sizeof(int);
		//
    for (i = 0; i < weapCount; i++) {
		  w = weapList[i];

		  switch(w) {
			  case WP_MACHINEGUN: max = 50; inc = 4; t = 1000; break;
			  case WP_SHOTGUN: max = 10; inc = 1; t = 1500; break;
			  case WP_GRENADE_LAUNCHER: max = 10; inc = 1; t = 2000; break;
			  case WP_ROCKET_LAUNCHER: max = 10; inc = 1; t = 1750; break;
			  case WP_LIGHTNING: max = 50; inc = 5; t = 1500; break;
			  case WP_RAILGUN: max = 10; inc = 1; t = 1750; break;
			  case WP_PLASMAGUN: max = 50; inc = 5; t = 1500; break;
			  case WP_BFG: max = 10; inc = 1; t = 4000; break;
			  case WP_NAILGUN: max = 10; inc = 1; t = 1250; break;
			  case WP_PROX_LAUNCHER: max = 5; inc = 1; t = 2000; break;
			  case WP_CHAINGUN: max = 100; inc = 5; t = 1000; break;
			  default: max = 0; inc = 0; t = 1000; break;
	}
		  client->ammoTimes[w] += msec;
		  if ( client->ps.ammo[w] >= max ) {
			  client->ammoTimes[w] = 0;
		  }
		  if ( client->ammoTimes[w] >= t ) {
			  while ( client->ammoTimes[w] >= t )
				  client->ammoTimes[w] -= t;
			  client->ps.ammo[w] += inc;
			  if ( client->ps.ammo[w] > max ) {
				  client->ps.ammo[w] = max;
			  }
		  }
    }
	}
#endif
}

/*
====================
ClientIntermissionThink
====================
*/
void ClientIntermissionThink( gclient_t *client ) {
	client->ps.eFlags &= ~EF_TALK;
	client->ps.eFlags &= ~EF_FIRING;

	// the level will exit when everyone wants to or after timeouts

	// swap and latch button actions
	client->oldbuttons = client->buttons;
	client->buttons = client->pers.cmd.buttons;
	if ( client->buttons & ( BUTTON_ATTACK | BUTTON_USE_HOLDABLE ) & ( client->oldbuttons ^ client->buttons ) ) {
		// this used to be an ^1 but once a player says ready, it should stick
		client->readyToExit = 1;
	}
}


/*
================
ClientEvents

Events will be passed on to the clients for presentation,
but any server game effects are handled here
================
*/
void ClientEvents( gentity_t *ent, int oldEventSequence ) {
	int		i, j;
	int		event;
	gclient_t *client;
	int		damage;
	vec3_t	dir;
	vec3_t	origin, angles;
//	qboolean	fired;
	gitem_t *item;
	gentity_t *drop;

	client = ent->client;

	if ( oldEventSequence < client->ps.eventSequence - MAX_PS_EVENTS ) {
		oldEventSequence = client->ps.eventSequence - MAX_PS_EVENTS;
	}
	for ( i = oldEventSequence ; i < client->ps.eventSequence ; i++ ) {
		event = client->ps.events[ i & (MAX_PS_EVENTS-1) ];

		switch ( event ) {
		case EV_FALL_MEDIUM:
		case EV_FALL_FAR:

			if ( ent->s.eType != ET_PLAYER ) {
				break;		// not in the player model
			}
			if ( g_dmflags.integer & DF_NO_FALLING ) {
				break;
			}
// JBravo: fix falling pain during lca
			if (g_gametype.integer == GT_TEAMPLAY && level.lights_camera_action) {
				break;
			}

			damage = ent->client->ps.stats[STAT_FALLDAMAGE];
			VectorSet (dir, 0, 0, 1);
			ent->pain_debounce_time = level.time + 200;	// no normal pain sound
			//Elder: added so we can trigger AQ2 pain blends
			ent->client->ps.damageEvent++;
			ent->client->ps.damageCount += damage;
			if (ent->client->lasthurt_mod != 0)
			{
				G_Damage (ent, &g_entities[ent->client->lasthurt_client], &g_entities[ent->client->lasthurt_client], NULL, NULL, damage, 0, MOD_FALLING);
			}
			else
			{
				G_Damage (ent, NULL, NULL, NULL, NULL, damage, 0, MOD_FALLING);
			}

			break;

		case EV_FALL_FAR_NOSOUND:

			if ( ent->s.eType != ET_PLAYER ) {
				break;		// not in the player model
			}
			if ( g_dmflags.integer & DF_NO_FALLING ) {
				break;
			}
// JBravo: fix falling pain during lca again
			if (g_gametype.integer == GT_TEAMPLAY && level.lights_camera_action) {
				break;
			}

			damage = ent->client->ps.stats[STAT_FALLDAMAGE];
			VectorSet (dir, 0, 0, 1);
			ent->pain_debounce_time = level.time + 200;	// no normal pain sound
			//Elder: added so we can trigger AQ2 pain blends
			ent->client->ps.damageEvent++;
			ent->client->ps.damageCount += damage;
			if (ent->client->lasthurt_mod != 0)
			{
				G_Damage (ent, &g_entities[ent->client->lasthurt_client], &g_entities[ent->client->lasthurt_client], NULL, NULL, damage, 0, MOD_FALLING);
			}
			else
			{
				G_Damage (ent, NULL, NULL, NULL, NULL, damage, 0, MOD_FALLING);
			}

			break;

		case EV_FIRE_WEAPON:
			FireWeapon( ent );
			break;
	/*
		case EV_RELOAD_WEAPON0:
			ReloadWeapon ( ent, 0 );
			break;
	*/
		case EV_RELOAD_WEAPON1:
			ReloadWeapon ( ent, 1 );
			break;
		case EV_RELOAD_WEAPON2:
			ReloadWeapon ( ent, 2 );
			break;

		case EV_CHANGE_WEAPON:
			//Elder: not a good place to put stuff
			//ent->client->zoomed=0;
			break;

		case EV_USE_ITEM1:		// teleporter
			// drop flags in CTF
			item = NULL;
			j = 0;

			if ( ent->client->ps.powerups[ PW_REDFLAG ] ) {
				item = BG_FindItemForPowerup( PW_REDFLAG );
				j = PW_REDFLAG;
			} else if ( ent->client->ps.powerups[ PW_BLUEFLAG ] ) {
				item = BG_FindItemForPowerup( PW_BLUEFLAG );
				j = PW_BLUEFLAG;
			} else if ( ent->client->ps.powerups[ PW_NEUTRALFLAG ] ) {
				item = BG_FindItemForPowerup( PW_NEUTRALFLAG );
				j = PW_NEUTRALFLAG;
			}

			if ( item ) {
				drop = Drop_Item( ent, item, 0 );
				// decide how many seconds it has left
				drop->count = ( ent->client->ps.powerups[ j ] - level.time ) / 1000;
				if ( drop->count < 1 ) {
					drop->count = 1;
				}

				ent->client->ps.powerups[ j ] = 0;
			}

#ifdef MISSIONPACK
			if ( g_gametype.integer == GT_HARVESTER ) {
				if ( ent->client->ps.generic1 > 0 ) {
					if ( ent->client->sess.sessionTeam == TEAM_RED ) {
						item = BG_FindItem( "Blue Cube" );
					} else {
						item = BG_FindItem( "Red Cube" );
					}
					if ( item ) {
						for ( j = 0; j < ent->client->ps.generic1; j++ ) {
							drop = Drop_Item( ent, item, 0 );
							if ( ent->client->sess.sessionTeam == TEAM_RED ) {
								drop->spawnflags = TEAM_BLUE;
							} else {
								drop->spawnflags = TEAM_RED;
							}
						}
					}
					ent->client->ps.generic1 = 0;
				}
			}
#endif
			SelectSpawnPoint( ent->client->ps.origin, origin, angles );
			TeleportPlayer( ent, origin, angles );
			break;

		case EV_USE_ITEM2:		// medkit
			ent->health = 125; //ent->client->ps.stats[STAT_MAX_HEALTH] + 25;

			break;

#ifdef MISSIONPACK
		case EV_USE_ITEM3:		// kamikaze
			// make sure the invulnerability is off
			ent->client->invulnerabilityTime = 0;
			// start the kamikze
			G_StartKamikaze( ent );
			break;

		case EV_USE_ITEM4:		// portal
			if( ent->client->portalID ) {
				DropPortalSource( ent );
			}
			else {
				DropPortalDestination( ent );
			}
			break;
		case EV_USE_ITEM5:		// invulnerability
			ent->client->invulnerabilityTime = level.time + 10000;
			break;
#endif

		default:
			break;
		}
	}

}

#ifdef MISSIONPACK
/*
==============
StuckInOtherClient
==============
*/
static int StuckInOtherClient(gentity_t *ent) {
	int i;
	gentity_t	*ent2;

	ent2 = &g_entities[0];
	for ( i = 0; i < MAX_CLIENTS; i++, ent2++ ) {
		if ( ent2 == ent ) {
			continue;
		}
		if ( !ent2->inuse ) {
			continue;
		}
		if ( !ent2->client ) {
			continue;
		}
		if ( ent2->health <= 0 ) {
			continue;
		}
		//
		if (ent2->r.absmin[0] > ent->r.absmax[0])
			continue;
		if (ent2->r.absmin[1] > ent->r.absmax[1])
			continue;
		if (ent2->r.absmin[2] > ent->r.absmax[2])
			continue;
		if (ent2->r.absmax[0] < ent->r.absmin[0])
			continue;
		if (ent2->r.absmax[1] < ent->r.absmin[1])
			continue;
		if (ent2->r.absmax[2] < ent->r.absmin[2])
			continue;
		return qtrue;
	}
	return qfalse;
}
#endif

void BotTestSolid(vec3_t origin);
/*
=============
ThrowWeapon

XRAY FMJ
Returns the number of the weapon thrown
=============
*/

int ThrowWeapon( gentity_t *ent, qboolean forceThrow )
{
	gclient_t	*client;
	usercmd_t	*ucmd;
	gitem_t		*xr_item;
	gentity_t	*xr_drop;
	int weap;

	client = ent->client;
	ucmd = &ent->client->pers.cmd;

	if (!forceThrow)
		if ((ucmd->buttons & BUTTON_ATTACK) || client->ps.weaponTime > 0)
			return 0;

	//Elder: remove zoom bits
	Cmd_Unzoom(ent);

	weap = 0;
	if (client->uniqueWeapons > 0)
	{
		if (client->ps.weapon == WP_AKIMBO ||
			client->ps.weapon == WP_PISTOL ||
			client->ps.weapon == WP_GRENADE ||
			client->ps.weapon == WP_KNIFE ||
			client->ps.weapon == WP_NONE)	// shouldn't have to worry about NONE, but just in case
		{
			weap = client->ps.stats[STAT_WEAPONS];
			if ((client->ps.stats[STAT_WEAPONS] & (1 << WP_M4) ) == (1 << WP_M4))
				weap = WP_M4;
			if ((client->ps.stats[STAT_WEAPONS] & (1 << WP_M3) ) == (1 << WP_M3))
				weap = WP_M3;
			if ((client->ps.stats[STAT_WEAPONS] & (1 << WP_MP5) ) == (1 << WP_MP5))
				weap = WP_MP5;
			if ((client->ps.stats[STAT_WEAPONS] & (1 << WP_HANDCANNON) ) == (1 << WP_HANDCANNON))
				weap = WP_HANDCANNON;
			if ((client->ps.stats[STAT_WEAPONS] & (1 << WP_SSG3000) ) == (1 << WP_SSG3000))
				weap = WP_SSG3000;
			if (weap == 0 )
				return 0;
		} else {
			weap = client->ps.weapon;
		}

		xr_item = BG_FindItemForWeapon( weap );

		client->pers.hadUniqueWeapon[weap] = qtrue;


		//Elder: for immediate weapon drops
		if (client->ps.weapon == weap)
		{
			client->ps.stats[STAT_RQ3] |= RQ3_THROWWEAPON;
			trap_SendServerCommand( ent-g_entities, va("selectpistol"));
		}

		client->weaponCount[weap]--;
		if (client->weaponCount[weap] == 0)
			client->ps.stats[STAT_WEAPONS] &= ~( 1 << weap);

		xr_drop= dropWeapon( ent, xr_item, 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
		xr_drop->count= -1; // XRAY FMJ 0 is already taken, -1 means no ammo
		// remember who dropped you, child!
		xr_drop->s.otherEntityNum = client->ps.clientNum;
		client->uniqueWeapons--;
	}

	return weap;
}

/*
==============
ThrowItem

Used to toss an item much like weapons except a bit leaner
You can throw items ANY time (firing, bandaging, etc.)
=============
*/

void ThrowItem( gentity_t *ent )
{
	gclient_t	*client;
	gitem_t		*xr_item;
	gentity_t	*xr_drop;
	int item;

	client = ent->client;

	//itemonTime > 0 or itemonState == itemon_dropping?  Or both?
	//item = 0;

	if (client->uniqueItems > 0)
	{
		item = bg_itemlist[client->ps.stats[STAT_HOLDABLE_ITEM]].giTag;
		xr_item = BG_FindItemForHoldable( item );
		client->ps.stats[STAT_HOLDABLE_ITEM] = 0;
		//Elder: Just going to re-use the dropWeapon function
		xr_drop= dropWeapon( ent, xr_item, 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
		xr_drop->count= -1; // XRAY FMJ 0 is already taken, -1 means no ammo
		client->uniqueItems--;
	}
}

/*
==============
SendPendingPredictableEvents
==============
*/
void SendPendingPredictableEvents( playerState_t *ps ) {
	gentity_t *t;
	int event, seq;
	int extEvent, number;

	// if there are still events pending
	if ( ps->entityEventSequence < ps->eventSequence ) {
		// create a temporary entity for this event which is sent to everyone
		// except the client who generated the event
		seq = ps->entityEventSequence & (MAX_PS_EVENTS-1);
		event = ps->events[ seq ] | ( ( ps->entityEventSequence & 3 ) << 8 );
		// set external event to zero before calling BG_PlayerStateToEntityState
		extEvent = ps->externalEvent;
		ps->externalEvent = 0;
		// create temporary entity for event
		t = G_TempEntity( ps->origin, event );
		number = t->s.number;
		BG_PlayerStateToEntityState( ps, &t->s, qtrue );
		t->s.number = number;
		t->s.eType = ET_EVENTS + event;
		t->s.eFlags |= EF_PLAYER_EVENT;
		t->s.otherEntityNum = ps->clientNum;
		// send to everyone except the client who generated the event
		t->r.svFlags |= SVF_NOTSINGLECLIENT;
		t->r.singleClient = ps->clientNum;
		// set back external event
		ps->externalEvent = extEvent;
	}
}

/*
==============
ClientThink

This will be called once for each client frame, which will
usually be a couple times for each server frame on fast clients.

If "g_synchronousClients 1" is set, this will be called exactly
once for each server frame, which makes for smooth demo recording.
==============
*/
void ClientThink_real( gentity_t *ent ) {
	gclient_t	*client;
	pmove_t		pm;
	int			oldEventSequence;
	int			msec;
	usercmd_t	*ucmd;
	int bJumping = 0;

	client = ent->client;

	// don't think if the client is not yet connected (and thus not yet spawned in)
	if (client->pers.connected != CON_CONNECTED) {
		return;
	}
	// mark the time, so the connection sprite can be removed
	ucmd = &ent->client->pers.cmd;

	// sanity check the command time to prevent speedup cheating
	if ( ucmd->serverTime > level.time + 200 ) {
		ucmd->serverTime = level.time + 200;
	}
	if ( ucmd->serverTime < level.time - 1000 ) {
		ucmd->serverTime = level.time - 1000;
	}

	msec = ucmd->serverTime - client->ps.commandTime;
	// following others may result in bad times, but we still want
	// to check for follow toggles
	if ( msec < 1 && client->sess.spectatorState != SPECTATOR_FOLLOW ) {
		return;
	}
	if ( msec > 200 ) {
		msec = 200;
	}

	if ( pmove_msec.integer < 8 ) {
		trap_Cvar_Set("pmove_msec", "8");
	}
	else if (pmove_msec.integer > 33) {
		trap_Cvar_Set("pmove_msec", "33");
	}

	if ( pmove_fixed.integer || client->pers.pmoveFixed ) {
		ucmd->serverTime = ((ucmd->serverTime + pmove_msec.integer-1) / pmove_msec.integer) * pmove_msec.integer;
		//if (ucmd->serverTime - client->ps.commandTime <= 0)
		//	return;
	}

	//
	// check for exiting intermission
	//
	if ( level.intermissiontime ) {
		ClientIntermissionThink( client );
		return;
	}

	// spectators don't do much
	if ( client->sess.sessionTeam == TEAM_SPECTATOR ) {
		if ( client->sess.spectatorState == SPECTATOR_SCOREBOARD ) {
			return;
		}
		SpectatorThink( ent, ucmd );
		return;
	}

	// check for inactivity timer, but never drop the local client of a non-dedicated server
	if ( !ClientInactivityTimer( client ) ) {
		return;
	}

	// clear the rewards if time
	if ( level.time > client->rewardTime ) {
		client->ps.eFlags &= ~(EF_AWARD_IMPRESSIVE | EF_AWARD_EXCELLENT | EF_AWARD_GAUNTLET | EF_AWARD_ASSIST | EF_AWARD_DEFEND | EF_AWARD_CAP );
	}

	if ( client->noclip ) {
		client->ps.pm_type = PM_NOCLIP;
	} else if ( client->ps.stats[STAT_HEALTH] <= 0 ) {
		client->ps.pm_type = PM_DEAD;
	} else {
		client->ps.pm_type = PM_NORMAL;
	}

	client->ps.gravity = g_gravity.value;

	// set speed
	client->ps.speed = g_speed.value;

#ifdef MISSIONPACK
	if( bg_itemlist[client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_SCOUT ) {
		client->ps.speed *= 1.5;
	}
	else
#endif
	if ( client->ps.powerups[PW_HASTE] ) {
		client->ps.speed *= 1.3;
	}

	// set up for pmove
	oldEventSequence = client->ps.eventSequence;

	memset (&pm, 0, sizeof(pm));

	if ( ent->flags & FL_FORCE_GESTURE ) {
		ent->flags &= ~FL_FORCE_GESTURE;
		ent->client->pers.cmd.buttons |= BUTTON_GESTURE;
	}

	//Elder: 3rb Code moved to bg_pmove.c (resides in PM_Weapon)

#ifdef MISSIONPACK
	// check for invulnerability expansion before doing the Pmove
	if (client->ps.powerups[PW_INVULNERABILITY] ) {
		if ( !(client->ps.pm_flags & PMF_INVULEXPAND) ) {
			vec3_t mins = { -42, -42, -42 };
			vec3_t maxs = { 42, 42, 42 };
			vec3_t oldmins, oldmaxs;

			VectorCopy (ent->r.mins, oldmins);
			VectorCopy (ent->r.maxs, oldmaxs);
			// expand
			VectorCopy (mins, ent->r.mins);
			VectorCopy (maxs, ent->r.maxs);
			trap_LinkEntity(ent);
			// check if this would get anyone stuck in this player
			if ( !StuckInOtherClient(ent) ) {
				// set flag so the expanded size will be set in PM_CheckDuck
				client->ps.pm_flags |= PMF_INVULEXPAND;
			}
			// set back
			VectorCopy (oldmins, ent->r.mins);
			VectorCopy (oldmaxs, ent->r.maxs);
			trap_LinkEntity(ent);
		}
	}
#endif

	pm.ps = &client->ps;
	pm.cmd = *ucmd;

	if ( pm.ps->pm_type == PM_DEAD ) {
		pm.tracemask = MASK_PLAYERSOLID & ~CONTENTS_BODY;
	}
	else if ( ent->r.svFlags & SVF_BOT ) {
		pm.tracemask = MASK_PLAYERSOLID | CONTENTS_BOTCLIP;
	}
	else {
		pm.tracemask = MASK_PLAYERSOLID;
	}

// JBravo: fixing telefragging and shit during spawnig.  (Thanks NiceAss! :)
	if (g_gametype.integer == GT_TEAMPLAY &&
		((ent->client->ps.stats[STAT_RQ3] & RQ3_PLAYERSOLID) != RQ3_PLAYERSOLID) &&
		!level.lights_camera_action) {
		UnstickPlayer (ent);
	}
	if (g_gametype.integer == GT_TEAMPLAY &&
		((ent->client->ps.stats[STAT_RQ3] & RQ3_PLAYERSOLID) != RQ3_PLAYERSOLID)) {
		pm.tracemask = MASK_PLAYERSOLID & ~CONTENTS_BODY;
	}

	pm.trace = trap_Trace;
	pm.pointcontents = trap_PointContents;
	pm.debugLevel = g_debugMove.integer;
	pm.noFootsteps = ( g_dmflags.integer & DF_NO_FOOTSTEPS ) > 0;

	pm.pmove_fixed = pmove_fixed.integer | client->pers.pmoveFixed;
	pm.pmove_msec = pmove_msec.integer;

	VectorCopy( client->ps.origin, client->oldOrigin );

#ifdef MISSIONPACK
		if (level.intermissionQueued != 0 && g_singlePlayer.integer) {
			if ( level.time - level.intermissionQueued >= 1000  ) {
				pm.cmd.buttons = 0;
				pm.cmd.forwardmove = 0;
				pm.cmd.rightmove = 0;
				pm.cmd.upmove = 0;
				if ( level.time - level.intermissionQueued >= 2000 && level.time - level.intermissionQueued <= 2500 ) {
					trap_SendConsoleCommand( EXEC_APPEND, "centerview\n");
				}
				ent->client->ps.pm_type = PM_SPINTERMISSION;
			}
		}
	Pmove (&pm);
#else
// JBravo: setting lca in pm if appropriate
		if(g_RQ3_lca.integer == 1)
			pm.lca = qtrue;
		else
			pm.lca = qfalse;
		Pmove (&pm);
#endif

	if ( (pm.cmd.upmove > 10 ) &&
		 (pm.waterlevel == 0) &&
		 ent->s.groundEntityNum != ENTITYNUM_NONE &&
		 pm.ps->groundEntityNum == ENTITYNUM_NONE )
		 bJumping = 1;

	// save results of pmove
	if ( ent->client->ps.eventSequence != oldEventSequence ) {
		ent->eventTime = level.time;
	}
	if (g_smoothClients.integer) {
		BG_PlayerStateToEntityStateExtraPolate( &ent->client->ps, &ent->s, ent->client->ps.commandTime, qtrue );
	}
	else {
		BG_PlayerStateToEntityState( &ent->client->ps, &ent->s, qtrue );
	}
	SendPendingPredictableEvents( &ent->client->ps );

	if ( !( ent->client->ps.eFlags & EF_FIRING ) ) {
		client->fireHeld = qfalse;		// for grapple
	}

	// use the snapped origin for linking so it matches client predicted versions
	VectorCopy( ent->s.pos.trBase, ent->r.currentOrigin );

	VectorCopy (pm.mins, ent->r.mins);
	VectorCopy (pm.maxs, ent->r.maxs);

	ent->waterlevel = pm.waterlevel;
	ent->watertype = pm.watertype;

	// execute client events
	ClientEvents( ent, oldEventSequence );

	// link entity now, after any personal teleporters have been used
	trap_LinkEntity (ent);
	if ( !ent->client->noclip ) {
		G_TouchTriggers( ent );
	}

	// NOTE: now copy the exact origin over otherwise clients can be snapped into solid
	VectorCopy( ent->client->ps.origin, ent->r.currentOrigin );

	//test for solid areas in the AAS file
	BotTestAAS(ent->r.currentOrigin);

	// touch other objects
	ClientImpacts( ent, &pm );

	//Elder: someone added
	if ( bJumping )	JumpKick( ent );

	//Elder: added for akimbos and 3rb and sniper zoom
	switch( ent->client->ps.weapon ) {
	case WP_AKIMBO:
		/*
		if ( ent->client->weaponfireNextTime != 0 &&
			level.time >= ent->client->weaponfireNextTime) {
			FireWeapon( ent );
		}
		*/
		break;
	case WP_M3:
		//Elder: try to do a fast reload if it's queued
		if ( ent->client->ps.weaponTime < RQ3_M3_FAST_RELOAD_DELAY &&
			 ent->client->fastReloads &&
			 ent->client->reloadAttempts > 0)
		{
			//G_Printf("(%i) ClientThink: attempting M3 fast-reload...\n", ent->s.clientNum);
			Cmd_Reload( ent );
		}
		break;
	case WP_SSG3000:
		//Elder: try to do a fast reload if it's queued
		if ( ent->client->ps.weaponTime < RQ3_SSG3000_FAST_RELOAD_DELAY &&
			 ent->client->fastReloads &&
			 ent->client->reloadAttempts > 0)
		{
			//G_Printf("(%i) ClientThink: attempting SSG fast-reload...\n", ent->s.clientNum);
			Cmd_Reload( ent );
		}
		break;
	default:
		break;
	}

	// save results of triggers and client events
	if (ent->client->ps.eventSequence != oldEventSequence) {
		ent->eventTime = level.time;
	}

	// swap and latch button actions
	client->oldbuttons = client->buttons;
	client->buttons = ucmd->buttons;
	client->latched_buttons |= client->buttons & ~client->oldbuttons;

	// check for respawning
	// JBravo: Lets make dead players into spectators.
	if (client->ps.stats[STAT_HEALTH] <= 0) {
		// wait for the attack button to be pressed
		if (level.time > client->respawnTime) {
			// forcerespawn is to prevent users from waiting out powerups
			if (g_forcerespawn.integer > 0 &&
				(level.time - client->respawnTime ) > g_forcerespawn.integer * 1000 &&
				g_gametype.integer != GT_TEAMPLAY) {
					respawn( ent );
					return;
			}
			if (g_gametype.integer == GT_TEAMPLAY && level.time > client->respawnTime) {
				MakeSpectator(ent);
			}

			// pressing attack or use is the normal respawn method
			// JBravo: make'em spactate
			if (ucmd->buttons & ( BUTTON_ATTACK | BUTTON_USE_HOLDABLE)) {
				if (g_gametype.integer == GT_TEAMPLAY) {
					MakeSpectator(ent);
				} else {
					respawn( ent );
				}
			}
		}
		return;
	}

	// perform once-a-second actions
	ClientTimerActions( ent, msec );
}

/*
==================
ClientThink

A new command has arrived from the client
==================
*/
void ClientThink( int clientNum ) {
	gentity_t *ent;

	ent = g_entities + clientNum;
	trap_GetUsercmd( clientNum, &ent->client->pers.cmd );

	// mark the time we got info, so we can display the
	// phone jack if they don't get any for a while
	ent->client->lastCmdTime = level.time;

	     /* camera jitter fix (server side) */
// JBravo: Take SPECTATOR_ZCAM into account
	if ( !(ent->r.svFlags & SVF_BOT) && !g_synchronousClients.integer &&
		(ent->client->sess.sessionTeam != TEAM_SPECTATOR ||
		(ent->client->sess.sessionTeam == TEAM_SPECTATOR &&
		 ent->client->sess.spectatorState != SPECTATOR_ZCAM))) {
			ClientThink_real( ent );
	}
}


void G_RunClient( gentity_t *ent ) {
	     /* camera jitter fix (server side) */
// JBravo: Take SPECTATOR_ZCAM into account
	if ( !(ent->r.svFlags & SVF_BOT) && !g_synchronousClients.integer &&
		(ent->client->sess.sessionTeam != TEAM_SPECTATOR ||
		(ent->client->sess.sessionTeam == TEAM_SPECTATOR &&
		 ent->client->sess.spectatorState != SPECTATOR_ZCAM))) {
		return;
	}
	ent->client->pers.cmd.serverTime = level.time;
	ClientThink_real( ent );
}


/*
==================
SpectatorClientEndFrame

==================
*/
void SpectatorClientEndFrame( gentity_t *ent ) {
	gclient_t	*cl;
	int		savedPing, savedFlags,i;
	int savedPers[MAX_PERSISTANT];

	// if we are doing a chase cam or a remote view, grab the latest info
	if ( ent->client->sess.spectatorState == SPECTATOR_FOLLOW ) {
		int		clientNum, flags;

		clientNum = ent->client->sess.spectatorClient;

		// team follow1 and team follow2 go to whatever clients are playing
		if ( clientNum == -1 ) {
			clientNum = level.follow1;
		} else if ( clientNum == -2 ) {
			clientNum = level.follow2;
		}
		if ( clientNum >= 0 ) {
			cl = &level.clients[ clientNum ];
			if ( cl->pers.connected == CON_CONNECTED && cl->sess.sessionTeam != TEAM_SPECTATOR ) {
				flags = (cl->ps.eFlags & ~(EF_VOTED | EF_TEAMVOTED)) | (ent->client->ps.eFlags & (EF_VOTED | EF_TEAMVOTED));
			// JBravo: saving score and ping to fix the scoreboard
				savedPing = ent->client->ps.ping;
				//Slicer saving pm_flags & pers
				savedFlags = ent->client->ps.pm_flags;
				for (i = 0 ; i < MAX_PERSISTANT ; i++)
					savedPers[i] = ent->client->ps.persistant[i];
				//This will make the spectator get the client's stuff
				ent->client->ps = cl->ps;
				//Reposting score and ping.. 
				if(g_gametype.integer == GT_TEAMPLAY) {
					for (i = 0 ; i < MAX_PERSISTANT ; i++)
						ent->client->ps.persistant[i] = savedPers[i];
										
					ent->client->ps.ping = savedPing;
					//Slicer reposting pmflags
					ent->client->ps.pm_flags = savedFlags;
				}
				ent->client->ps.pm_flags |= PMF_FOLLOW;
				ent->client->ps.eFlags = flags;
				return;
			} else {
				// drop them to free spectators unless they are dedicated camera followers
				if ( ent->client->sess.spectatorClient >= 0 ) {
					ent->client->sess.spectatorState = SPECTATOR_FREE;
// JBravo: saving spectatorState
					ent->client->specMode = SPECTATOR_FREE;
					ClientBegin( ent->client - level.clients );
				}
			}
		}
	}

	if ( ent->client->sess.spectatorState == SPECTATOR_SCOREBOARD ) {
		ent->client->ps.pm_flags |= PMF_SCOREBOARD;
	} else {
		ent->client->ps.pm_flags &= ~PMF_SCOREBOARD;
	}
}


/*
==============
RQ3_ClientReloadStages

Added by Elder

Check to see if any reload events need
to occur and dispatch if necessary
This would be completely client-side
except other players need to hear the reloading
==============
*/
/* // Elder -- bad code -- and should go in pmove anyways
static void RQ3_ClientReloadStages ( gentity_t *ent )
{
	gentity_t	*tent;

	// no events for dead people
	if (ent->client->ps.pm_type == PM_DEAD)
	{
		ent->client->reloadStage = -1;
		return;
	}

	if ( ent->client->ps.weaponstate == WEAPON_RELOADING &&
		 ent->client->ps.weaponTime > 0)
	{
		switch (ent->client->ps.weapon)
		{
			//Elder: hardcoded timing values :p
			case WP_PISTOL:
				if (ent->client->ps.weaponTime < RQ3_PISTOL_RELOAD_DELAY - 1900 &&
					ent->client->reloadStage == 1)
				{
					tent = G_TempEntity2(ent->client->ps.origin, EV_RELOAD_WEAPON, 2);
					ent->client->reloadStage = 2;
				}
				else if (ent->client->ps.weaponTime < RQ3_PISTOL_RELOAD_DELAY - 1500 &&
						ent->client->reloadStage == 0)
				{
					tent = G_TempEntity2(ent->client->ps.origin, EV_RELOAD_WEAPON, 1);
					ent->client->reloadStage = 1;
				}
				else if (ent->client->ps.weaponTime < RQ3_PISTOL_RELOAD_DELAY - 100 &&
						ent->client->reloadStage == -1)
				{
					tent = G_TempEntity2(ent->client->ps.origin, EV_RELOAD_WEAPON, 0);
					ent->client->reloadStage = 0;
				}
				break;

			case WP_M3:
				if ( ent->client->ps.weaponTime % RQ3_M3_RELOAD_DELAY < RQ3_M3_RELOAD_DELAY - 500 &&
					ent->client->reloadStage == -1)
				{
					tent = G_TempEntity2(ent->client->ps.origin, EV_RELOAD_WEAPON, 0);
					ent->client->reloadStage = 0;
				}
				break;
			case WP_M4:
				if (ent->client->ps.weaponTime < RQ3_M4_RELOAD_DELAY - 1600 &&
						ent->client->reloadStage == 0)
				{
					tent = G_TempEntity2(ent->client->ps.origin, EV_RELOAD_WEAPON, 1);
					ent->client->reloadStage = 1;
				}
				else if (ent->client->ps.weaponTime < RQ3_M4_RELOAD_DELAY - 300 &&
						ent->client->reloadStage == -1)
				{
					tent = G_TempEntity2(ent->client->ps.origin, EV_RELOAD_WEAPON, 0);
					ent->client->reloadStage = 0;
				}
				break;
		}

		if (tent)
		{
			tent->s.weapon = ent->client->ps.weapon;
			tent->s.clientNum = ent->client->ps.clientNum;
		}

	}
	else if (ent->client->reloadStage != -1)
	{
		// Reset reload stage
		ent->client->reloadStage = -1;
	}

}
*/

/*
==============
ClientEndFrame

Called at the end of each server frame for each connected client
A fast client will have multiple ClientThink for each ClientEdFrame,
while a slow client may have multiple ClientEndFrame between ClientThink.
==============
*/
void ClientEndFrame( gentity_t *ent ) {
	int			i;
	clientPersistant_t	*pers;

	if ( ent->client->sess.sessionTeam == TEAM_SPECTATOR ) {
		SpectatorClientEndFrame( ent );
		return;
	}

	pers = &ent->client->pers;

	// turn off any expired powerups
	for ( i = 0 ; i < MAX_POWERUPS ; i++ ) {
		if ( ent->client->ps.powerups[ i ] < level.time ) {
			ent->client->ps.powerups[ i ] = 0;
		}
	}

#ifdef MISSIONPACK
	// set powerup for player animation
	if( bg_itemlist[ent->client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_GUARD ) {
		ent->client->ps.powerups[PW_GUARD] = level.time;
	}
	if( bg_itemlist[ent->client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_SCOUT ) {
		ent->client->ps.powerups[PW_SCOUT] = level.time;
	}
	if( bg_itemlist[ent->client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_DOUBLER ) {
		ent->client->ps.powerups[PW_DOUBLER] = level.time;
	}
	if( bg_itemlist[ent->client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_AMMOREGEN ) {
		ent->client->ps.powerups[PW_AMMOREGEN] = level.time;
	}
	if ( ent->client->invulnerabilityTime > level.time ) {
		ent->client->ps.powerups[PW_INVULNERABILITY] = level.time;
	}
#endif

	// save network bandwidth
#if 0
	if ( !g_synchronousClients->integer && ent->client->ps.pm_type == PM_NORMAL ) {
		// FIXME: this must change eventually for non-sync demo recording
		VectorClear( ent->client->ps.viewangles );
	}
#endif

	//
	// If the end of unit layout is displayed, don't give
	// the player any normal movement attributes
	//
	if ( level.intermissiontime ) {
		return;
	}

	if(ent->client->bleeding)
		CheckBleeding(ent);	// perform once-a-second actions

	// burn from lava, etc
	P_WorldEffects (ent);

	// apply all the damage taken this frame
	P_DamageFeedback (ent);

	// add the EF_CONNECTION flag if we haven't gotten commands recently
	if ( level.time - ent->client->lastCmdTime > 1000 ) {
		ent->s.eFlags |= EF_CONNECTION;
	} else {
		ent->s.eFlags &= ~EF_CONNECTION;
	}


// Begin Duffman
	// Update the clips Amount in weapon for the client
    ent->client->ps.stats[STAT_CLIPS] = ent->client->numClips[ent->client->ps.weapon];

// End Duffman
	ent->client->ps.stats[STAT_HEALTH] = ent->health;	// FIXME: get rid of ent->health...

	//Elder: bleeding notification
	if (ent->client->bleeding ||
		(ent->client->ps.stats[STAT_RQ3] & RQ3_LEGDAMAGE) == RQ3_LEGDAMAGE) {
		ent->client->ps.stats[STAT_RQ3] |= RQ3_BANDAGE_NEED;
	}
	else {
		ent->client->ps.stats[STAT_RQ3] &= ~RQ3_BANDAGE_NEED;
//		ent->client->ps.stats[STAT_RQ3] &= ~RQ3_BANDAGE_WORK;
	}


	//Moved to pmove.c
	//Elder: M4 ride-up/kick -- condition for non-burst and ammo only

	if (ent->client->consecutiveShots &&
		(ent->client->ps.ammo[WP_M4] <= 0 || ent->client->ps.weaponstate != WEAPON_FIRING))
	{
		//Restore view after shots if not firing
		ent->client->ps.delta_angles[0] = ANGLE2SHORT(SHORT2ANGLE(ent->client->ps.delta_angles[0]) - ent->client->consecutiveShots * -0.7f);
		ent->client->consecutiveShots = 0;
	}

	// Check to reset our openDoor boolean
	if ( ent->client->openDoorTime &&
		 level.time - ent->client->openDoorTime > MAXDOORTIME )
	{
		ent->client->openDoor = qfalse;
		ent->client->openDoorTime = 0;
	}

	if ( bg_itemlist[ent->client->ps.stats[STAT_HOLDABLE_ITEM]].giTag == HI_LASER )
	{
		//Try to turn the laser on if it's off
		if (ent->client->lasersight == NULL)
			Laser_Gen(ent, qtrue);
	}

	//RQ3_ClientReloadStages(ent);

	G_SetClientSound (ent);

	// set the latest infor
	if (g_smoothClients.integer) {
		BG_PlayerStateToEntityStateExtraPolate( &ent->client->ps, &ent->s, ent->client->ps.commandTime, qtrue );
	}
	else {
	BG_PlayerStateToEntityState( &ent->client->ps, &ent->s, qtrue );
	}
	SendPendingPredictableEvents( &ent->client->ps );

	// set the bit for the reachability area the client is currently in
//	i = trap_AAS_PointReachabilityAreaIndex( ent->client->ps.origin );
//	ent->client->areabits[i >> 3] |= 1 << (i & 7);
}


