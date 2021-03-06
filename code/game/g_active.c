//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.99  2003/04/19 15:27:30  jbravo
// Backing out of most of unlagged.  Only optimized prediction and smooth clients
// remains.
//
// Revision 1.98  2003/03/22 20:29:26  jbravo
// wrapping linkent and unlinkent calls
//
// Revision 1.97  2003/03/10 07:07:58  jbravo
// Small unlagged fixes and voting delay added.
//
// Revision 1.96  2003/03/09 21:30:38  jbravo
// Adding unlagged.   Still needs work.
//
// Revision 1.95  2002/11/13 00:50:38  jbravo
// Fixed item dropping, specmode selection on death and helmet probs.
//
// Revision 1.94  2002/10/30 21:24:47  jbravo
// Minor helmet tweaking
//
// Revision 1.93  2002/10/30 20:04:34  jbravo
// Adding helmet
//
// Revision 1.92  2002/10/26 22:03:43  jbravo
// Made TeamDM work RQ3 style.
//
// Revision 1.91  2002/10/26 00:37:18  jbravo
// New multiple item code and added PB support to the UI
//
// Revision 1.90  2002/09/29 16:06:44  jbravo
// Work done at the HPWorld expo
//
// Revision 1.89  2002/09/24 05:06:16  blaze
// fixed spectating so ref\'s can now use all the chasecam modes.
//
// Revision 1.88  2002/08/30 01:09:06  jbravo
// Semi fixed the bodies thing in CTB
//
// Revision 1.87  2002/08/21 07:00:07  jbravo
// Added CTB respawn queue and fixed game <-> cgame synch problem in CTB
//
// Revision 1.86  2002/07/24 02:17:38  jbravo
// Added a respawn delay for CTB
//
// Revision 1.85  2002/07/22 06:33:04  niceass
// cleaned up the powerup code
//
// Revision 1.84  2002/07/21 18:48:06  niceass
// weapon prediction stuff
//
// Revision 1.83  2002/07/07 18:36:13  jbravo
// Added an AntiIdle system. Can play insane sounds for idle players, drop them
// from teams or kick them.   Upped version to Beta 2.1
//
// Revision 1.82  2002/07/02 19:15:17  jbravo
// Drop weapon with akimbos now behaves like AQ, plus no suicides during LCA
//
// Revision 1.81  2002/06/23 19:27:52  niceass
// bandage bug fix
//
// Revision 1.80  2002/06/19 18:13:57  jbravo
// New TNG spawning system :)
//
// Revision 1.79  2002/06/18 06:15:30  niceass
// m4 kick now smooth
//
// Revision 1.78  2002/06/17 00:27:29  jbravo
// Cleanup
//
// Revision 1.77  2002/06/16 20:06:14  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.76  2002/06/16 17:38:00  jbravo
// Removed the MISSIONPACK ifdefs and missionpack only code.
//
// Revision 1.75  2002/06/05 15:17:51  jbravo
// Gibbed players now vanish (gibs with them tho :() and suicide is no
// longer -2 frags.  Added Obit handling for telefrags and better handling
// for unhandled mod's
//
// Revision 1.74  2002/06/03 05:25:37  niceass
// spectator changes
//
// Revision 1.73  2002/05/21 04:58:27  blaze
// kicked the reload bugs ass!
//
// Revision 1.72  2002/05/06 21:41:01  slicer
// Added rq3_cmd
//
// Revision 1.71  2002/04/13 15:37:53  jbravo
// limchasecam has been redone with new spec system
//
// Revision 1.70  2002/04/03 15:29:24  jbravo
// Those __ZCAM__ ifdefs keep creaping back in :)
//
// Revision 1.69  2002/04/03 03:13:16  blaze
// NEW BREAKABLE CODE - will break all old breakables(wont appear in maps)
//
// Revision 1.68  2002/04/02 20:23:12  jbravo
// Bots dont get to use any specmode other than FREE and the recive radio cmds
// as text and not sounds.
//
// Revision 1.67  2002/04/01 22:23:14  slicer
// Added "weapon" command buffering | Solved Gren Mode Bug
//
// Revision 1.66  2002/03/30 21:51:42  jbravo
// Removed all those ifdefs for zcam.
//
// Revision 1.65  2002/03/30 17:37:48  jbravo
// Added damage tracking to the server. Added zcam flic mode. cleaned up g_damage.
//
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
#include "zcam.h"

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
void P_DamageFeedback(gentity_t * player)
{
	gclient_t *client;
	float count, side;
	vec3_t angles, v;
	vec3_t forward, right, up;

	client = player->client;
	if (client->ps.pm_type == PM_DEAD) {
		return;
	}

	// total points of damage shot at the player this frame
	count = client->damage_blood + client->damage_armor;
	if (count == 0) {
		return;		// didn't take any damage
	}

	if (count > 255) {
		count = 255;
	}
	// send the information to the client

	// world damage (falling, slime, etc) uses a special code
	// to make the blend blob centered instead of positional
	if (client->damage_fromWorld) {
		client->ps.damagePitch = 255;
		client->ps.damageYaw = 255;

		client->damage_fromWorld = qfalse;
	} else {
		vectoangles(client->damage_from, angles);

		// new RQ3 view-kick code, needs more tweaking (the 50 needs to be replaces with that below calcuation
		// from the AQ2 code.

		// set aiming directions
		AngleVectors(client->ps.viewangles, forward, right, up);

		VectorSubtract(client->damage_from, player->s.origin, v);
		VectorNormalize(v);

		side = -DotProduct(v, forward);
		client->ps.damagePitch = 50 * side * 0.3;

		side = -DotProduct(v, right);
		client->ps.damageYaw = 50 * side * 0.3;

	}

	// play an appropriate pain sound
	if ((level.time > player->pain_debounce_time) && !(player->flags & FL_GODMODE)) {
		//Elder: reduced pain debounce time so we can have a few more sounds :)
		player->pain_debounce_time = level.time + 250;

		switch (client->lasthurt_location & ~(LOCATION_BACK | LOCATION_LEFT | LOCATION_RIGHT | LOCATION_FRONT)) {
			//Elder: headshot sound
		case LOCATION_HEAD:
		case LOCATION_FACE:
			if (client->lasthurt_mod == MOD_KNIFE || client->lasthurt_mod == MOD_KNIFE_THROWN)
				G_AddEvent(player, EV_RQ3_SOUND, RQ3_SOUND_KNIFEDEATH);
			break;
		default:
			G_AddEvent(player, EV_PAIN, player->health);
			break;
		}

		client->ps.damageEvent++;
	}

	client->ps.damageCount = count;

	// Elder: HC Smoke
	if (client->lasthurt_mod == MOD_HANDCANNON &&
	    client->damage_blood >= 120 && client->damage_knockback >= RQ3_HANDCANNON_KICK * 6) {
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
void P_WorldEffects(gentity_t * ent)
{
	int waterlevel;

	if (ent->client->noclip) {
		ent->client->airOutTime = level.time + 12000;	// don't need air
		return;
	}

	waterlevel = ent->waterlevel;

	//
	// check for drowning
	//
	if (waterlevel == 3) {

		// if out of air, start drowning
		if (ent->client->airOutTime < level.time) {
			// drown!
			ent->client->airOutTime += 1000;
			if (ent->health > 0) {
				// take more damage the longer underwater
				ent->damage += 2;
				if (ent->damage > 15)
					ent->damage = 15;

				// play a gurp sound instead of a normal pain sound
				if (ent->health <= ent->damage) {
					G_Sound(ent, CHAN_VOICE, G_SoundIndex("*drown.wav"));
				} else if (rand() & 1) {
					G_Sound(ent, CHAN_VOICE, G_SoundIndex("sound/player/gurp1.wav"));
				} else {
					G_Sound(ent, CHAN_VOICE, G_SoundIndex("sound/player/gurp2.wav"));
				}

				// don't play a normal pain sound
				ent->pain_debounce_time = level.time + 200;

				G_Damage(ent, NULL, NULL, NULL, NULL, ent->damage, DAMAGE_NO_ARMOR, MOD_WATER);
			}
		}
	} else {
		ent->client->airOutTime = level.time + 12000;
		ent->damage = 2;
	}

	//
	// check for sizzle damage (move to pmove?)
	//
	if (waterlevel && (ent->watertype & (CONTENTS_LAVA | CONTENTS_SLIME))) {
		// Elder: changed around a bit -- using timestamp variable
		if (ent->health > 0 && level.time > ent->timestamp) {
			if (ent->watertype & CONTENTS_LAVA) {
				G_Damage(ent, NULL, NULL, NULL, NULL, 3 * waterlevel, 0, MOD_LAVA);
			}

			if (ent->watertype & CONTENTS_SLIME) {
				G_Damage(ent, NULL, NULL, NULL, NULL, waterlevel, 0, MOD_SLIME);
			}
			// Elder: added
			ent->timestamp = level.time + FRAMETIME;
		}
	}
}

/*
===============
G_SetClientSound
===============
*/
void G_SetClientSound(gentity_t * ent)
{
	if (ent->waterlevel && (ent->watertype & (CONTENTS_LAVA | CONTENTS_SLIME))) {
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
void ClientImpacts(gentity_t * ent, pmove_t * pm)
{
	int i, j;
	trace_t trace;
	gentity_t *other;

	memset(&trace, 0, sizeof(trace));
	for (i = 0; i < pm->numtouch; i++) {
		for (j = 0; j < i; j++) {
			if (pm->touchents[j] == pm->touchents[i]) {
				break;
			}
		}
		if (j != i) {
			continue;	// duplicated
		}
		//Blaze: Print out some debug info
		if (&g_entities[pm->touchents[i]] == NULL) G_Printf("Ln 0377\n");
		other = &g_entities[pm->touchents[i]];

		if ((ent->r.svFlags & SVF_BOT) && (ent->touch)) {
			ent->touch(ent, other, &trace);
		}

		if (!other->touch) {
			continue;
		}

		other->touch(other, ent, &trace);
	}

}

/*
============
G_TouchTriggers

Find all trigger entities that ent's current position touches.
Spectators will only interact with teleporters (and door triggers for spectators)
============
*/
void G_TouchTriggers(gentity_t * ent)
{
	int i, num;
	int touch[MAX_GENTITIES];
	gentity_t *hit;
	trace_t trace;
	vec3_t mins, maxs;
	static vec3_t range = { 40, 40, 52 };

	if (!ent->client) {
		return;
	}
	// dead clients don't activate triggers!
	if (ent->client->ps.stats[STAT_HEALTH] <= 0) {
		return;
	}

	VectorSubtract(ent->client->ps.origin, range, mins);
	VectorAdd(ent->client->ps.origin, range, maxs);

	num = trap_EntitiesInBox(mins, maxs, touch, MAX_GENTITIES);

	// can't use ent->absmin, because that has a one unit pad
	VectorAdd(ent->client->ps.origin, ent->r.mins, mins);
	VectorAdd(ent->client->ps.origin, ent->r.maxs, maxs);

	for (i = 0; i < num; i++) {
		//Blaze: Print out some debug info
		if (&g_entities[touch[i]] == NULL) G_Printf("Ln 0429\n");

		hit = &g_entities[touch[i]];

		if (!hit->touch && !ent->touch) {
			continue;
		}
		if (!(hit->r.contents & CONTENTS_TRIGGER)) {
			continue;
		}
		// ignore most entities if a spectator
		if (ent->client->sess.sessionTeam == TEAM_SPECTATOR) {
			if (hit->s.eType != ET_TELEPORT_TRIGGER) {	//&&
				// this is ugly but adding a new ET_? type will
				// most likely cause network incompatibilities
				// NiceAss: changed Touch_DoorTrigger to Touch_DoorTriggerSpectator
				// hit->touch != Touch_DoorTriggerSpectator) {
				continue;
			}
		}
		// use separate code for determining if an item is picked up
		// so you don't have to actually contact its bounding box
		if (hit->s.eType == ET_ITEM) {
			if (!BG_PlayerTouchesItem(&ent->client->ps, &hit->s, level.time)) {
				continue;
			}
		} else {
			if (!trap_EntityContact(mins, maxs, hit)) {
				continue;
			}
		}

		memset(&trace, 0, sizeof(trace));

		if (hit->touch) {
			hit->touch(hit, ent, &trace);
		}

		if ((ent->r.svFlags & SVF_BOT) && (ent->touch)) {
			ent->touch(ent, hit, &trace);
		}
	}

	// if we didn't touch a jump pad this pmove frame
	if (ent->client->ps.jumppad_frame != ent->client->ps.pmove_framecount) {
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
void SpectatorThink(gentity_t * ent, usercmd_t * ucmd)
{
	pmove_t pm;
	gclient_t *client;
	int clientNum;

	client = ent->client;
	clientNum = client - level.clients;

	if (client->sess.spectatorState == SPECTATOR_ZCAM) {
		client->ps.commandTime = ucmd->serverTime;
		camera_think(ent);
	}

	if (client->sess.spectatorState == SPECTATOR_FREE) {
		if (g_gametype.integer == GT_CTF && level.team_round_going &&
			(client->sess.savedTeam == TEAM_RED || client->sess.savedTeam == TEAM_BLUE))
			client->ps.pm_type = PM_FREEZE;
		else
			client->ps.pm_type = PM_SPECTATOR;
		client->ps.speed = 400;	// faster than normal

		// set up for pmove
		memset(&pm, 0, sizeof(pm));
		pm.ps = &client->ps;
		pm.cmd = *ucmd;
		pm.tracemask = 0;	// spectators can fly through bodies
		pm.trace = trap_Trace;
		pm.pointcontents = trap_PointContents;
		pm.predict = qtrue;
		// perform a pmove
		Pmove(&pm);
		// save results of pmove
		VectorCopy(client->ps.origin, ent->s.origin);

		G_TouchTriggers(ent);
		trap_UnlinkEntity(ent);
	}
// JBravo: Lets not allow bots to use any specmode other than FREE
	if (ent->r.svFlags & SVF_BOT)
		return;

	//Slicer - Changing this for aq2 way
	// Jump button cycles throught spectators
	if (client->sess.spectatorState == SPECTATOR_FOLLOW || client->sess.spectatorState == SPECTATOR_ZCAM) {
		if (ucmd->upmove >= 10) {
			if (!(client->ps.pm_flags & PMF_JUMP_HELD)) {
				client->ps.pm_flags |= PMF_JUMP_HELD;
				if (client->sess.spectatorState == SPECTATOR_ZCAM) {
					if (client->camera->mode == CAMERA_MODE_SWING)
						CameraSwingCycle(ent, 1);
				} else
					Cmd_FollowCycle_f(ent, 1);
			}
		} else
			client->ps.pm_flags &= ~PMF_JUMP_HELD;
	}

	client->oldbuttons = client->buttons;
	client->buttons = ucmd->buttons;

	if (g_gametype.integer == GT_CTF && client->sess.spectatorState == SPECTATOR_FREE &&
		(client->sess.savedTeam == TEAM_RED || client->sess.savedTeam == TEAM_BLUE))
		return;

	// Attack Button cycles throught free view, follow or zcam
	if ((ucmd->buttons & BUTTON_ATTACK) && !(client->oldbuttons & BUTTON_ATTACK)) {
		if (g_gametype.integer == GT_TEAMPLAY && g_RQ3_limchasecam.integer != 0 && client->sess.referee == 0 ) {
			if (!OKtoFollow(clientNum))
				return;
			if (client->sess.spectatorState != SPECTATOR_FOLLOW) {
				client->sess.spectatorState = SPECTATOR_FOLLOW;
				client->specMode = SPECTATOR_FOLLOW;
				client->ps.pm_flags |= PMF_FOLLOW;
				client->ps.stats[STAT_RQ3] &= ~RQ3_ZCAM;
			}
			return;
		} else if (client->sess.spectatorState == SPECTATOR_FREE && OKtoFollow(clientNum)) {
			client->sess.spectatorState = SPECTATOR_ZCAM;
			client->specMode = SPECTATOR_ZCAM;
			client->camera->mode = CAMERA_MODE_SWING;
			client->ps.stats[STAT_RQ3] |= RQ3_ZCAM;
			client->ps.pm_flags &= ~PMF_FOLLOW;
			CameraSwingCycle(ent, 1);
			RQ3_SpectatorMode(ent);
		} else if (client->sess.spectatorState == SPECTATOR_ZCAM && client->camera->mode == CAMERA_MODE_SWING
			   && OKtoFollow(clientNum)) {
			client->sess.spectatorState = SPECTATOR_ZCAM;
			client->specMode = SPECTATOR_ZCAM;
			client->camera->mode = CAMERA_MODE_FLIC;
			client->ps.stats[STAT_RQ3] |= RQ3_ZCAM;
			client->ps.pm_flags &= ~PMF_FOLLOW;
			CameraFlicBegin(ent);
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
qboolean ClientInactivityTimer(gclient_t * client)
{
	if (!g_inactivity.integer) {
		// give everyone some time, so if the operator sets g_inactivity during
		// gameplay, everyone isn't kicked
		client->inactivityTime = level.time + 60 * 1000;
		client->inactivityWarning = qfalse;
	} else if (client->pers.cmd.forwardmove ||
		   client->pers.cmd.rightmove ||
		   client->pers.cmd.upmove || (client->pers.cmd.buttons & BUTTON_ATTACK)) {
		client->inactivityTime = level.time + g_inactivity.integer * 1000;
		client->inactivityWarning = qfalse;
	} else if (!client->pers.localClient) {
		if (level.time > client->inactivityTime) {
			trap_DropClient(client - level.clients, "Dropped due to inactivity");
			return qfalse;
		}
		if (level.time > client->inactivityTime - 10000 && !client->inactivityWarning) {
			client->inactivityWarning = qtrue;
			trap_SendServerCommand(client - level.clients, "cp \"Ten seconds until inactivity drop!\n\"");
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
void ClientTimerActions(gentity_t * ent, int msec)
{
	gclient_t *client;

	client = ent->client;
	client->timeResidual += msec;

	while (client->timeResidual >= 1000) {
		client->timeResidual -= 1000;

		// count down health when over max
		if (ent->health > 100) {	//max is 100 client->ps.stats[STAT_MAX_HEALTH] ) {
			ent->health--;
		}

		// count down armor when over max
		if (client->ps.stats[STAT_ARMOR] > 100) {	// max is 100 client->ps.stats[STAT_MAX_HEALTH] ) {
			client->ps.stats[STAT_ARMOR]--;
		}
		//Blaze: Do bandaging stuff
		if (ent->client->bleedtick > 1) {
			//G_Printf("Bleedtick (%d) getting lowered by one (%d)\n", ent->client->bleedtick, client->timeResidual);
			ent->client->bleedtick--;
		} else if (ent->client->bleedtick == 1) {
			ent->client->bleed_remain = 0;
			ent->client->bleeding = 0;
			ent->client->bleedtick = 0;
			//Elder: moved from somewhere - err, g_cmds.c I think
			ent->client->ps.stats[STAT_RQ3] &= ~RQ3_LEGDAMAGE;
			// NiceAss: clear last player to hit you.
			ent->client->lasthurt_mod = 0;
		}

	}
}

/*
====================
ClientIntermissionThink
====================
*/
void ClientIntermissionThink(gclient_t * client)
{
	client->ps.eFlags &= ~EF_TALK;
	client->ps.eFlags &= ~EF_FIRING;

	// the level will exit when everyone wants to or after timeouts

	// swap and latch button actions
	client->oldbuttons = client->buttons;
	client->buttons = client->pers.cmd.buttons;
	if (client->buttons & (BUTTON_ATTACK | BUTTON_USE_HOLDABLE) & (client->oldbuttons ^ client->buttons)) {
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
void ClientEvents(gentity_t * ent, int oldEventSequence)
{
	int i, j;
	int event;
	gclient_t *client;
	int damage;
//	vec3_t dir;
	vec3_t origin, angles;
	gitem_t *item;
	gentity_t *drop;

	client = ent->client;

	if (oldEventSequence < client->ps.eventSequence - MAX_PS_EVENTS) {
		oldEventSequence = client->ps.eventSequence - MAX_PS_EVENTS;
	}
	for (i = oldEventSequence; i < client->ps.eventSequence; i++) {
		event = client->ps.events[i & (MAX_PS_EVENTS - 1)];

		switch (event) {
		case EV_FALL_MEDIUM:
		case EV_FALL_FAR:

			if (ent->s.eType != ET_PLAYER) {
				break;	// not in the player model
			}
			if (g_dmflags.integer & DF_NO_FALLING) {
				break;
			}
// JBravo: fix falling pain during lca
			if (g_gametype.integer >= GT_TEAM && level.lights_camera_action) {
				break;
			}

			damage = ent->client->ps.stats[STAT_FALLDAMAGE];
//			VectorSet(dir, 0, 0, 1);
			ent->pain_debounce_time = level.time + 200;	// no normal pain sound
			//Elder: added so we can trigger AQ2 pain blends
			ent->client->ps.damageEvent++;
			ent->client->ps.damageCount += damage;
			if (ent->client->lasthurt_mod != 0) {
					//Blaze: Print out some debug info
					if (&g_entities[ent->client->lasthurt_client] == NULL) G_Printf("Ln 0748\n");

					G_Damage(ent, &g_entities[ent->client->lasthurt_client],
					 &g_entities[ent->client->lasthurt_client], NULL, NULL, damage, 0, MOD_FALLING);
			} else {
				G_Damage(ent, NULL, NULL, NULL, NULL, damage, 0, MOD_FALLING);
			}

			break;

		case EV_FALL_FAR_NOSOUND:

			if (ent->s.eType != ET_PLAYER) {
				break;	// not in the player model
			}
			if (g_dmflags.integer & DF_NO_FALLING) {
				break;
			}
// JBravo: fix falling pain during lca again
			if (g_gametype.integer >= GT_TEAM && level.lights_camera_action) {
				break;
			}

			damage = ent->client->ps.stats[STAT_FALLDAMAGE];
//			VectorSet(dir, 0, 0, 1);
			ent->pain_debounce_time = level.time + 200;	// no normal pain sound
			//Elder: added so we can trigger AQ2 pain blends
			ent->client->ps.damageEvent++;
			ent->client->ps.damageCount += damage;
			if (ent->client->lasthurt_mod != 0) {
				//Blaze: Print out some debug info
				if (&g_entities[ent->client->lasthurt_client] == NULL) G_Printf("Ln 0779\n");

				G_Damage(ent, &g_entities[ent->client->lasthurt_client],
					 &g_entities[ent->client->lasthurt_client], NULL, NULL, damage, 0, MOD_FALLING);
			} else {
				G_Damage(ent, NULL, NULL, NULL, NULL, damage, 0, MOD_FALLING);
			}

			break;

		case EV_FIRE_WEAPON:
			FireWeapon(ent);
			break;
		case EV_RELOAD_WEAPON1:
			ReloadWeapon(ent, 1);
			break;
		case EV_RELOAD_WEAPON2:
			ReloadWeapon(ent, 2);
			break;

		case EV_CHANGE_WEAPON:
			//Elder: not a good place to put stuff
			break;

		case EV_USE_ITEM1:	// teleporter
			// drop flags in CTF
			item = NULL;
			j = 0;

			if (ent->client->ps.powerups[PW_REDFLAG]) {
				item = BG_FindItemForPowerup(PW_REDFLAG);
				j = PW_REDFLAG;
			} else if (ent->client->ps.powerups[PW_BLUEFLAG]) {
				item = BG_FindItemForPowerup(PW_BLUEFLAG);
				j = PW_BLUEFLAG;
			} else if (ent->client->ps.powerups[PW_NEUTRALFLAG]) {
				item = BG_FindItemForPowerup(PW_NEUTRALFLAG);
				j = PW_NEUTRALFLAG;
			}

			if (item) {
				drop = Drop_Item(ent, item, 0);
				// decide how many seconds it has left
				drop->count = (ent->client->ps.powerups[j] - level.time) / 1000;
				if (drop->count < 1) {
					drop->count = 1;
				}

				ent->client->ps.powerups[j] = 0;
			}

			SelectSpawnPoint(ent->client->ps.origin, origin, angles);
			TeleportPlayer(ent, origin, angles);
			break;

		case EV_USE_ITEM2:	// medkit
			ent->health = 125;	//ent->client->ps.stats[STAT_MAX_HEALTH] + 25;

			break;

		default:
			break;
		}
	}

}

void BotTestSolid(vec3_t origin);

/*
=============
ThrowWeapon

XRAY FMJ
Returns the number of the weapon thrown
=============
*/

int ThrowWeapon(gentity_t * ent, qboolean forceThrow)
{
	gclient_t *client;
	usercmd_t *ucmd;
	gitem_t *xr_item;
	gentity_t *xr_drop;
	int weap;

	client = ent->client;
	ucmd = &ent->client->pers.cmd;

	if (!forceThrow)
		if ((ucmd->buttons & BUTTON_ATTACK) || client->ps.weaponTime > 0)
			return 0;

	//Elder: remove zoom bits
	Cmd_Unzoom(ent);

// JBravo: simulate AQ drop weapon for akimbo with no special weap
	if (client->ps.weapon == WP_AKIMBO && client->uniqueWeapons == 0) {
		trap_SendServerCommand(ent - g_entities, va("stuff weapon %i\n", WP_PISTOL));
		return 0;
	}

	weap = 0;
	if (client->uniqueWeapons > 0) {
		if (client->ps.weapon == WP_AKIMBO || client->ps.weapon == WP_PISTOL || client->ps.weapon == WP_GRENADE || client->ps.weapon == WP_KNIFE || client->ps.weapon == WP_NONE)	// shouldn't have to worry about NONE, but just in case
		{
			weap = client->ps.stats[STAT_WEAPONS];
			if ((client->ps.stats[STAT_WEAPONS] & (1 << WP_M4)) == (1 << WP_M4))
				weap = WP_M4;
			if ((client->ps.stats[STAT_WEAPONS] & (1 << WP_M3)) == (1 << WP_M3))
				weap = WP_M3;
			if ((client->ps.stats[STAT_WEAPONS] & (1 << WP_MP5)) == (1 << WP_MP5))
				weap = WP_MP5;
			if ((client->ps.stats[STAT_WEAPONS] & (1 << WP_HANDCANNON)) == (1 << WP_HANDCANNON))
				weap = WP_HANDCANNON;
			if ((client->ps.stats[STAT_WEAPONS] & (1 << WP_SSG3000)) == (1 << WP_SSG3000))
				weap = WP_SSG3000;
			if (weap == 0)
				return 0;
		} else {
			weap = client->ps.weapon;
		}

		xr_item = BG_FindItemForWeapon(weap);

		client->pers.hadUniqueWeapon[weap] = qtrue;

		//Elder: for immediate weapon drops
		if (client->ps.weapon == weap) {
			client->ps.stats[STAT_RQ3] |= RQ3_THROWWEAPON;
			trap_SendServerCommand(ent - g_entities, va("rq3_cmd %i", SELECTPISTOL));
		}

		client->weaponCount[weap]--;
		if (client->weaponCount[weap] == 0)
			client->ps.stats[STAT_WEAPONS] &= ~(1 << weap);

		xr_drop = dropWeapon(ent, xr_item, 0, FL_DROPPED_ITEM | FL_THROWN_ITEM);
		xr_drop->count = -1;	// XRAY FMJ 0 is already taken, -1 means no ammo
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

void ThrowItem(gentity_t * ent)
{
	gclient_t *client;
	gitem_t *xr_item;
	gentity_t *xr_drop;
//	int item;

	client = ent->client;

	//itemonTime > 0 or itemonState == itemon_dropping?  Or both?
	//item = 0;

	// JBravo: New drop item code for multiple items.
	if (client->uniqueItems > 0) {
		if (g_gametype.integer >= GT_TEAM) {
			if (client->ps.stats[STAT_HOLDABLE_ITEM] & (1 << client->teamplayItem)) {
				xr_item = BG_FindItemForHoldable(client->teamplayItem);
				xr_drop = dropWeapon(ent, xr_item, 0, FL_DROPPED_ITEM | FL_THROWN_ITEM);
				xr_drop->count = -1;
				client->ps.stats[STAT_HOLDABLE_ITEM] &= ~(1 << client->teamplayItem);
				client->uniqueItems--;
				return;
			}
		}
		if (client->ps.stats[STAT_HOLDABLE_ITEM] & (1 << HI_BANDOLIER)) {
			xr_item = BG_FindItemForHoldable(HI_BANDOLIER);
			xr_drop = dropWeapon(ent, xr_item, 0, FL_DROPPED_ITEM | FL_THROWN_ITEM);
			xr_drop->count = -1;
			client->ps.stats[STAT_HOLDABLE_ITEM] &= ~(1 << HI_BANDOLIER);
			client->uniqueItems--;
			return;
		} else if (client->ps.stats[STAT_HOLDABLE_ITEM] & (1 << HI_SLIPPERS)) {
			xr_item = BG_FindItemForHoldable(HI_SLIPPERS);
			xr_drop = dropWeapon(ent, xr_item, 0, FL_DROPPED_ITEM | FL_THROWN_ITEM);
			xr_drop->count = -1;
			client->ps.stats[STAT_HOLDABLE_ITEM] &= ~(1 << HI_SLIPPERS);
			client->uniqueItems--;
			return;
		} else if (client->ps.stats[STAT_HOLDABLE_ITEM] & (1 << HI_SILENCER)) {
			xr_item = BG_FindItemForHoldable(HI_SILENCER);
			xr_drop = dropWeapon(ent, xr_item, 0, FL_DROPPED_ITEM | FL_THROWN_ITEM);
			xr_drop->count = -1;
			client->ps.stats[STAT_HOLDABLE_ITEM] &= ~(1 << HI_SILENCER);
			client->uniqueItems--;
			return;
		// JBravo: adding the helmet :)
		} else if (client->ps.stats[STAT_HOLDABLE_ITEM] & (1 << HI_HELMET)) {
			xr_item = BG_FindItemForHoldable(HI_HELMET);
			xr_drop = dropWeapon(ent, xr_item, 0, FL_DROPPED_ITEM | FL_THROWN_ITEM);
			xr_drop->count = -1;
			client->ps.stats[STAT_HOLDABLE_ITEM] &= ~(1 << HI_HELMET);
			client->uniqueItems--;
			return;
		} else if (client->ps.stats[STAT_HOLDABLE_ITEM] & (1 << HI_LASER)) {
			xr_item = BG_FindItemForHoldable(HI_LASER);
			xr_drop = dropWeapon(ent, xr_item, 0, FL_DROPPED_ITEM | FL_THROWN_ITEM);
			xr_drop->count = -1;
			client->ps.stats[STAT_HOLDABLE_ITEM] &= ~(1 << HI_LASER);
			client->uniqueItems--;
			return;
		} else if (client->ps.stats[STAT_HOLDABLE_ITEM] & (1 << HI_KEVLAR)) {
			xr_item = BG_FindItemForHoldable(HI_KEVLAR);
			xr_drop = dropWeapon(ent, xr_item, 0, FL_DROPPED_ITEM | FL_THROWN_ITEM);
			xr_drop->count = -1;
			client->ps.stats[STAT_HOLDABLE_ITEM] &= ~(1 << HI_KEVLAR);
			client->uniqueItems--;
			return;
		}
	}
}

/*
==============
SendPendingPredictableEvents
==============
*/
void SendPendingPredictableEvents(playerState_t * ps)
{
	gentity_t *t;
	int event, seq;
	int extEvent, number;

	// if there are still events pending
	if (ps->entityEventSequence < ps->eventSequence) {
		// create a temporary entity for this event which is sent to everyone
		// except the client who generated the event
		seq = ps->entityEventSequence & (MAX_PS_EVENTS - 1);
		event = ps->events[seq] | ((ps->entityEventSequence & 3) << 8);
		// set external event to zero before calling BG_PlayerStateToEntityState
		extEvent = ps->externalEvent;
		ps->externalEvent = 0;
		// create temporary entity for event
		t = G_TempEntity(ps->origin, event);
		number = t->s.number;
		BG_PlayerStateToEntityState(ps, &t->s, qtrue);
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
void ClientThink_real(gentity_t * ent)
{
	gclient_t *client;
	pmove_t pm;
	int oldEventSequence;
	int msec;
	usercmd_t *ucmd;
	int bJumping = 0;

	client = ent->client;

	// don't think if the client is not yet connected (and thus not yet spawned in)
	if (client->pers.connected != CON_CONNECTED) {
		return;
	}
	// mark the time, so the connection sprite can be removed
	ucmd = &ent->client->pers.cmd;

	// sanity check the command time to prevent speedup cheating
	if (ucmd->serverTime > level.time + 200) {
		ucmd->serverTime = level.time + 200;
	}
	if (ucmd->serverTime < level.time - 1000) {
		ucmd->serverTime = level.time - 1000;
	}

	client->lastUpdateFrame = level.framenum;

	msec = ucmd->serverTime - client->ps.commandTime;
	// following others may result in bad times, but we still want
	// to check for follow toggles
	if (msec < 1 && client->sess.spectatorState != SPECTATOR_FOLLOW) {
		return;
	}
	if (msec > 200) {
		msec = 200;
	}

	if (pmove_msec.integer < 8) {
		trap_Cvar_Set("pmove_msec", "8");
		trap_Cvar_Update(&pmove_msec);
	} else if (pmove_msec.integer > 33) {
		trap_Cvar_Set("pmove_msec", "33");
		trap_Cvar_Update(&pmove_msec);
	}

	if (pmove_fixed.integer || client->pers.pmoveFixed) {
		ucmd->serverTime =
		    ((ucmd->serverTime + pmove_msec.integer - 1) / pmove_msec.integer) * pmove_msec.integer;
	}
	//
	// check for exiting intermission
	//
	if (level.intermissiontime) {
		ClientIntermissionThink(client);
		return;
	}
	// spectators don't do much
	if (client->sess.sessionTeam == TEAM_SPECTATOR) {
		if (client->sess.spectatorState == SPECTATOR_SCOREBOARD) {
			return;
		}
		SpectatorThink(ent, ucmd);
		return;
	}
	// check for inactivity timer, but never drop the local client of a non-dedicated server
	if (!ClientInactivityTimer(client)) {
		return;
	}
	// clear the rewards if time
	if (level.time > client->rewardTime) {
		client->ps.eFlags &=
		    ~(EF_AWARD_IMPRESSIVE | EF_AWARD_EXCELLENT | EF_AWARD_GAUNTLET | EF_AWARD_ASSIST | EF_AWARD_DEFEND |
		      EF_AWARD_CAP);
	}

	if (client->noclip) {
		client->ps.pm_type = PM_NOCLIP;
	} else if (client->ps.stats[STAT_HEALTH] <= 0) {
		client->ps.pm_type = PM_DEAD;
	} else {
		client->ps.pm_type = PM_NORMAL;
	}

	client->ps.gravity = g_gravity.value;

	// set speed
	client->ps.speed = g_speed.value;

	// set up for pmove
	oldEventSequence = client->ps.eventSequence;

	memset(&pm, 0, sizeof(pm));

	if (ent->flags & FL_FORCE_GESTURE) {
		ent->flags &= ~FL_FORCE_GESTURE;
		ent->client->pers.cmd.buttons |= BUTTON_GESTURE;
	}
	//Elder: 3rb Code moved to bg_pmove.c (resides in PM_Weapon)

	pm.ps = &client->ps;
	pm.cmd = *ucmd;

	if (pm.ps->pm_type == PM_DEAD) {
		pm.tracemask = MASK_PLAYERSOLID & ~CONTENTS_BODY;
	} else if (ent->r.svFlags & SVF_BOT) {
		pm.tracemask = MASK_PLAYERSOLID | CONTENTS_BOTCLIP;
	} else {
		pm.tracemask = MASK_PLAYERSOLID;
	}

// JBravo: fixing telefragging and shit during spawnig.  (Thanks NiceAss! :)
	if ((g_gametype.integer == GT_TEAMPLAY || g_gametype.integer == GT_TEAM) &&
	    ((ent->client->ps.stats[STAT_RQ3] & RQ3_PLAYERSOLID) != RQ3_PLAYERSOLID) && !level.lights_camera_action) {
		UnstickPlayer(ent);
	}
	if ((g_gametype.integer == GT_TEAMPLAY || g_gametype.integer == GT_TEAM) &&
	    ((ent->client->ps.stats[STAT_RQ3] & RQ3_PLAYERSOLID) != RQ3_PLAYERSOLID)) {
		pm.tracemask = MASK_PLAYERSOLID & ~CONTENTS_BODY;
	}

	pm.trace = trap_Trace;
	pm.pointcontents = trap_PointContents;
	pm.debugLevel = g_debugMove.integer;
	pm.noFootsteps = (g_dmflags.integer & DF_NO_FOOTSTEPS) > 0;

	pm.pmove_fixed = pmove_fixed.integer | client->pers.pmoveFixed;
	pm.pmove_msec = pmove_msec.integer;

	VectorCopy(client->ps.origin, client->oldOrigin);

// JBravo: setting lca in pm if appropriate
	if (g_RQ3_lca.integer == 1)
		pm.lca = qtrue;
	else
		pm.lca = qfalse;

	pm.predict = qtrue;

	Pmove(&pm);

	if ((pm.cmd.upmove > 10) &&
	    (pm.waterlevel == 0) &&
	    ent->s.groundEntityNum != ENTITYNUM_NONE && pm.ps->groundEntityNum == ENTITYNUM_NONE)
		bJumping = 1;

	// save results of pmove
	if (ent->client->ps.eventSequence != oldEventSequence) {
		ent->eventTime = level.time;
	}

	BG_PlayerStateToEntityState(&ent->client->ps, &ent->s, qtrue);
	SendPendingPredictableEvents(&ent->client->ps);

	if (!(ent->client->ps.eFlags & EF_FIRING)) {
		client->fireHeld = qfalse;	// for grapple
	}
	// use the snapped origin for linking so it matches client predicted versions
	VectorCopy(ent->s.pos.trBase, ent->r.currentOrigin);

	VectorCopy(pm.mins, ent->r.mins);
	VectorCopy(pm.maxs, ent->r.maxs);

	ent->waterlevel = pm.waterlevel;
	ent->watertype = pm.watertype;

	// execute client events
	ClientEvents(ent, oldEventSequence);

	// link entity now, after any personal teleporters have been used
	// JBravo: this call reactivates gibbed players.
	if (!ent->client->gibbed)
		trap_LinkEntity(ent);
	if (!ent->client->noclip) {
		G_TouchTriggers(ent);
	}
	// NOTE: now copy the exact origin over otherwise clients can be snapped into solid
	VectorCopy(ent->client->ps.origin, ent->r.currentOrigin);

	//test for solid areas in the AAS file
	BotTestAAS(ent->r.currentOrigin);

	// touch other objects
	ClientImpacts(ent, &pm);

	//Elder: someone added
	if (bJumping)
		JumpKick(ent);

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
			    (level.time - client->respawnTime) > g_forcerespawn.integer * 1000 &&
			    g_gametype.integer != GT_TEAMPLAY && g_gametype.integer != GT_CTF) {
				respawn(ent);
				return;
			}
			if ((g_gametype.integer == GT_TEAMPLAY || g_gametype.integer == GT_CTF) && level.time > client->respawnTime) {
				MakeSpectator(ent);
			}
			// pressing attack or use is the normal respawn method
			// JBravo: make'em spactate
			if (ucmd->buttons & (BUTTON_ATTACK | BUTTON_USE_HOLDABLE)) {
				if (g_gametype.integer == GT_TEAMPLAY || g_gametype.integer == GT_CTF) {
					MakeSpectator(ent);
				} else {
					respawn(ent);
				}
			}
		}
		return;
	}
// JBravo: Idle sounds
	if (g_RQ3_ppl_idletime.integer) {
		if (ucmd->forwardmove == 0 && ucmd->rightmove == 0) {
			if (client->idletime) {
				if (level.time >= client->idletime + (g_RQ3_ppl_idletime.integer * 1000)) {
					if (g_gametype.integer >= GT_TEAM && g_RQ3_idleaction.integer == 1 &&
						(ent->client->sess.sessionTeam == TEAM_RED || ent->client->sess.sessionTeam == TEAM_BLUE)) {
						trap_SendServerCommand( -1, va("print \"Removing %s^7 from his team for excessive Idling\n\"", 
								ent->client->pers.netname));
						trap_SendServerCommand(ent - g_entities, "stuff team none\n");
					} else if (g_gametype.integer >= GT_TEAM && g_RQ3_idleaction.integer == 2 &&
						(ent->client->sess.sessionTeam == TEAM_RED || ent->client->sess.sessionTeam == TEAM_BLUE)) {
						trap_SendServerCommand( -1, va("print \"Kicking %s^7 for excessive Idling\n\"", 
								ent->client->pers.netname));
						trap_DropClient(ent - g_entities, "Dropped due to excessive Idling");
					} else
						G_TempEntity(ent->r.currentOrigin, EV_INSANESOUND);
					client->idletime = 0;
				}
			} else {
				client->idletime = level.time;
			}
		} else {
			client->idletime = 0;
		}
	}
	// perform once-a-second actions
	ClientTimerActions(ent, msec);
}

/*
==================
ClientThink

A new command has arrived from the client
==================
*/
void ClientThink(int clientNum)
{
	gentity_t *ent;

	ent = g_entities + clientNum;
	trap_GetUsercmd(clientNum, &ent->client->pers.cmd);

	// mark the time we got info, so we can display the
	// phone jack if they don't get any for a while
	// ent->client->lastCmdTime = level.time;

	/* camera jitter fix (server side) */
// JBravo: Take SPECTATOR_ZCAM into account
	if (!(ent->r.svFlags & SVF_BOT) && !g_synchronousClients.integer &&
	    (ent->client->sess.sessionTeam != TEAM_SPECTATOR ||
	     (ent->client->sess.sessionTeam == TEAM_SPECTATOR && ent->client->sess.spectatorState != SPECTATOR_ZCAM))) {
		ClientThink_real(ent);
	}
}

void G_RunClient(gentity_t * ent)
{
	/* camera jitter fix (server side) */
// JBravo: Take SPECTATOR_ZCAM into account
	if (!(ent->r.svFlags & SVF_BOT) && !g_synchronousClients.integer &&
	    (ent->client->sess.sessionTeam != TEAM_SPECTATOR ||
	     (ent->client->sess.sessionTeam == TEAM_SPECTATOR && ent->client->sess.spectatorState != SPECTATOR_ZCAM))) {
		return;
	}
	ent->client->pers.cmd.serverTime = level.time;
	ClientThink_real(ent);
}

/*
==================
SpectatorClientEndFrame

==================
*/
void SpectatorClientEndFrame(gentity_t * ent)
{
	gclient_t *cl;
	int savedPing, savedFlags, i;
	int savedPers[MAX_PERSISTANT];

	// if we are doing a chase cam or a remote view, grab the latest info
	if (ent->client->sess.spectatorState == SPECTATOR_FOLLOW) {
		int clientNum, flags;

		clientNum = ent->client->sess.spectatorClient;

		// team follow1 and team follow2 go to whatever clients are playing
		if (clientNum == -1) {
			clientNum = level.follow1;
		} else if (clientNum == -2) {
			clientNum = level.follow2;
		}
		if (clientNum >= 0) {
			cl = &level.clients[clientNum];
			if (cl->pers.connected == CON_CONNECTED && cl->sess.sessionTeam != TEAM_SPECTATOR) {
				flags =
				    (cl->ps.eFlags & ~(EF_VOTED | EF_TEAMVOTED)) | (ent->client->ps.
										    eFlags & (EF_VOTED | EF_TEAMVOTED));
				// JBravo: saving score and ping to fix the scoreboard
				savedPing = ent->client->ps.ping;
				//Slicer saving pm_flags & pers
				savedFlags = ent->client->ps.pm_flags;
				for (i = 0; i < MAX_PERSISTANT; i++)
					savedPers[i] = ent->client->ps.persistant[i];
				//This will make the spectator get the client's stuff
				ent->client->ps = cl->ps;
				//Reposting score and ping.. 
				if (g_gametype.integer >= GT_TEAM) {
					for (i = 0; i < MAX_PERSISTANT; i++)
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
				if (ent->client->sess.spectatorClient >= 0) {
					ent->client->sess.spectatorState = SPECTATOR_FREE;
// JBravo: saving spectatorState
					ent->client->specMode = SPECTATOR_FREE;
					ClientBegin(ent->client - level.clients);
				}
			}
		}
	}

	if (ent->client->sess.spectatorState == SPECTATOR_SCOREBOARD) {
		ent->client->ps.pm_flags |= PMF_SCOREBOARD;
	} else {
		ent->client->ps.pm_flags &= ~PMF_SCOREBOARD;
	}
}

/*
==============
ClientEndFrame

Called at the end of each server frame for each connected client
A fast client will have multiple ClientThink for each ClientEdFrame,
while a slow client may have multiple ClientEndFrame between ClientThink.
==============
*/
void ClientEndFrame(gentity_t * ent)
{
	int i, frames;
//	clientPersistant_t *pers;

	if (ent->client->sess.sessionTeam == TEAM_SPECTATOR) {
		SpectatorClientEndFrame(ent);
		return;
	}

//	pers = &ent->client->pers;

	// turn off any expired powerups
	for (i = 0; i < MAX_POWERUPS; i++) {
		if (ent->client->ps.powerups[i] < level.time) {
			ent->client->ps.powerups[i] = 0;
		}
	}

	// save network bandwidth
#if 0
	if (!g_synchronousClients->integer && ent->client->ps.pm_type == PM_NORMAL) {
		// FIXME: this must change eventually for non-sync demo recording
		VectorClear(ent->client->ps.viewangles);
	}
#endif

	//
	// If the end of unit layout is displayed, don't give
	// the player any normal movement attributes
	//
	if (level.intermissiontime) {
		return;
	}

	if (ent->client->bleeding)
		CheckBleeding(ent);	// perform once-a-second actions

	// burn from lava, etc
	P_WorldEffects(ent);

	// apply all the damage taken this frame
	P_DamageFeedback(ent);

	// Update the clips Amount in weapon for the client
	ent->client->ps.stats[STAT_CLIPS] = ent->client->numClips[ent->client->ps.weapon];
	ent->client->ps.stats[STAT_HEALTH] = ent->health;	// FIXME: get rid of ent->health...

	//Elder: bleeding notification
	if (ent->client->bleeding || (ent->client->ps.stats[STAT_RQ3] & RQ3_LEGDAMAGE) == RQ3_LEGDAMAGE) {
		ent->client->ps.stats[STAT_RQ3] |= RQ3_BANDAGE_NEED;
	} else {
		ent->client->ps.stats[STAT_RQ3] &= ~RQ3_BANDAGE_NEED;
	}

	//Moved to pmove.c
	//Elder: M4 ride-up/kick -- condition for non-burst and ammo only

	if (ent->client->consecutiveShots &&
	    (ent->client->ps.ammo[WP_M4] <= 0 || ent->client->ps.weaponstate != WEAPON_FIRING)) {
		//Restore view after shots if not firing
		ent->client->ps.delta_angles[0] =
		    ANGLE2SHORT(SHORT2ANGLE(ent->client->ps.delta_angles[0]) - ent->client->consecutiveShots * -0.8);//-0.7f);
		ent->client->consecutiveShots = 0;
	}
	// Check to reset our openDoor boolean
	if (ent->client->openDoorTime && level.time - ent->client->openDoorTime > MAXDOORTIME) {
		ent->client->openDoor = qfalse;
		ent->client->openDoorTime = 0;
	}

	// JBravo: multiple items
	if (ent->client->ps.stats[STAT_HOLDABLE_ITEM] & (1 << HI_LASER)) {
		//Try to turn the laser on if it's off
		if (ent->client->lasersight == NULL)
			Laser_Gen(ent, qtrue);
	}
	//Slicer
	if (ent->client->weapon_attempts > 0)
		Cmd_Weapon(ent);

	G_SetClientSound(ent);
	BG_PlayerStateToEntityState(&ent->client->ps, &ent->s, qtrue);
	SendPendingPredictableEvents(&ent->client->ps);

	// JBravo: unlagged
	ent->client->ps.eFlags &= ~EF_CONNECTION;
	frames = level.framenum - ent->client->lastUpdateFrame - 1;
	if (frames > 2) {
		frames = 2;
		ent->client->ps.eFlags |= EF_CONNECTION;
		ent->s.eFlags |= EF_CONNECTION;
	}
	if (frames > 0 && g_smoothClients.integer) {
		G_PredictPlayerMove(ent, (float)frames / sv_fps.integer);
		SnapVector(ent->s.pos.trBase);
	}
}
