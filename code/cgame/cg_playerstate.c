//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.28  2003/09/01 15:09:48  jbravo
// Cleanups, crashbug fix and version bumped to 3.2
//
// Revision 1.27  2003/07/30 16:05:46  makro
// no message
//
// Revision 1.26  2002/06/17 15:27:41  slicer
// Added the fix for the FOV bug when selecting the ssg at spawn
//
// Revision 1.25  2002/06/16 20:06:13  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.24  2002/06/16 19:12:52  jbravo
// Removed the MISSIONPACK ifdefs and missionpack only code.
//
// Revision 1.23  2002/06/12 19:59:39  jbravo
// Removed unused variables
//
// Revision 1.22  2002/06/05 20:09:17  jbravo
// Never commit uncompiled code! :)
//
// Revision 1.21  2002/06/05 20:06:07  jbravo
// no more Q3 X minutes left or X frags left sounds
//
// Revision 1.20  2002/05/31 00:17:06  jbravo
// Slicers fix for the weaponswitching issue
//
// Revision 1.19  2002/03/31 03:31:24  jbravo
// Compiler warning cleanups
//
// Revision 1.18  2002/03/26 10:32:52  jbravo
// Bye bye LCA lag
//
// Revision 1.17  2002/03/13 18:41:18  slicer
// Adjusted some of elder's unzoom code for the new sniper system ( server side )
//
// Revision 1.16  2002/01/11 19:48:29  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.15  2001/12/31 16:28:41  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
// cg_playerstate.c -- this file acts on changes in a new playerState_t
// With normal play, this will be done after local prediction, but when
// following another player or playing back a demo, it will be checked
// when the snapshot transitions like all the other entities

#include "cg_local.h"

/*
==============
CG_CheckAmmo

If the ammo has gone low enough to generate the warning, play a sound
Elder: changed the purpose of the function
It now generates a warning ONLY if the *current* weapon is low on/out of ammo
==============
*/
void CG_CheckAmmo(void)
{
	//int           i;
	int total;
//	int previous;

	//int           weapons;

	// see about how many seconds of ammo we have remaining
	//weapons = cg.snap->ps.stats[ STAT_WEAPONS ];
	total = 0;
	//Blaze: ammo check
	//for ( i = WP_KNIFE ; i < WP_NUM_WEAPONS ; i++ ) {
	//if ( ! ( weapons & ( 1 << i ) ) ) {
	//continue;
	//}
	//if ( cg.snap->ps.ammo[i] < 0 ) {
	//continue;
	//}
//Blaze: Dont need this
/*
		switch ( i ) {
		case WP_ROCKET_LAUNCHER:
		case WP_GRENADE_LAUNCHER:
		case WP_RAILGUN:
		case WP_SHOTGUN:
			total += cg.snap->ps.ammo[i] * 1000;
			break;
		default:
			total += cg.snap->ps.ammo[i] * 200;
			break;
		}
*/
	//Elder: how it should be handled - but we're not using it
	//for this purpose
	/*
	   switch (i) {
	   case WP_PISTOL:
	   total += cg.snap->ps.ammo[i] * RQ3_PISTOL_DELAY;
	   break;
	   case WP_M3:
	   total += cg.snap->ps.ammo[i] * RQ3_M3_DELAY;
	   break;
	   case WP_M4:
	   total += cg.snap->ps.ammo[i] * RQ3_M4_DELAY;
	   break;
	   case WP_MP5:
	   total += cg.snap->ps.ammo[i] * RQ3_MP5_DELAY;
	   break;
	   case WP_M3:
	   total += cg.snap->ps.ammo[i] * RQ3_M3_DELAY;
	   break;
	   case WP_SSG3000:
	   total += cg.snap->ps.ammo[i] * RQ3_SSG3000_DELAY;
	   break;
	   case WP_GRENADE:
	   total += cg.snap->ps.ammo[i] * RQ3_GRENADE_DELAY;
	   break;
	   case WP_KNIFE:
	   total += cg.snap->ps.ammo[i] * RQ3_KNIFE_DELAY;
	   break;
	   default:
	   total += cg.snap->ps.ammo[i] * 2000;
	   break;
	   }
	 */

	//total += cg.snap->ps.ammo[i] * 2000;//Blaze: Make this big so you dont his the amo check off the bat
	/*
	   if ( total >= 5000 ) {
	   cg.lowAmmoWarning = 0;
	   return;
	   }
	   } */

	total = cg.snap->ps.ammo[cg.snap->ps.weapon];

	if (total > 0) {
		cg.lowAmmoWarning = 0;
		if (cg.snap->ps.weapon == WP_SSG3000 && cg.zoomFirstReturn == -1)
			cg.zoomFirstReturn = 0;
		return;
	}

//	previous = cg.lowAmmoWarning;

	if (total == 0) {
		cg.lowAmmoWarning = 2;
	}
	//else {
	//Elder: only allow completely empty ammo warning sounds
	//cg.lowAmmoWarning = 1;
	//}

	// play a sound on transitions
	//if ( cg.lowAmmoWarning != previous ) {
	//trap_S_StartLocalSound( cgs.media.noAmmoSound, CHAN_LOCAL_SOUND );
	//}
}

/*
==============
CG_DamageFeedback
==============
*/
void CG_DamageFeedback(int yawByte, int pitchByte, int damage)
{
	float left, front, up;
	float kick;
	int health;
	float scale;
	vec3_t dir;
	vec3_t angles;
	float dist;
	float yaw, pitch;

	//Elder: removed
	// show the attacking player's head and name in corner
	//cg.attackerTime = cg.time;

	//Elder: added
	cg.rq3_trueDamage = damage;
	//Elder: memset in cg_main.c should let us increment safely
	if (damage * 10 < 100)
		cg.rq3_blendTime += 100;
	else
		cg.rq3_blendTime += damage * 10;

	// the lower on health you are, the greater the view kick will be
	health = cg.snap->ps.stats[STAT_HEALTH];
	if (health < 40) {
		scale = 1;
	} else {
		scale = 40.0 / health;
	}
	kick = damage * scale;

	if (kick < 5)
		kick = 5;
	if (kick > 10)
		kick = 10;

	// if yaw and pitch are both 255, make the damage always centered (falling, etc)
	if (yawByte == 255 && pitchByte == 255) {
		cg.damageX = 0;
		cg.damageY = 0;
		cg.v_dmg_roll = 0;
		cg.v_dmg_pitch = -kick;
	} else {
		// positional
		pitch = pitchByte / 255.0 * 360;
		yaw = yawByte / 255.0 * 360;

		angles[PITCH] = pitch;
		angles[YAW] = yaw;
		angles[ROLL] = 0;

		AngleVectors(angles, dir, NULL, NULL);
		VectorSubtract(vec3_origin, dir, dir);

		front = DotProduct(dir, cg.refdef.viewaxis[0]);
		left = DotProduct(dir, cg.refdef.viewaxis[1]);
		up = DotProduct(dir, cg.refdef.viewaxis[2]);

		dir[0] = front;
		dir[1] = left;
		dir[2] = 0;
		dist = VectorLength(dir);
		if (dist < 0.1) {
			dist = 0.1f;
		}

		cg.v_dmg_roll = kick * left;

		cg.v_dmg_pitch = -kick * front;

		if (front <= 0.1) {
			front = 0.1f;
		}
		cg.damageX = -left / front;
		cg.damageY = up / dist;
	}

	// clamp the position
	if (cg.damageX > 1.0) {
		cg.damageX = 1.0;
	}
	if (cg.damageX < -1.0) {
		cg.damageX = -1.0;
	}

	if (cg.damageY > 1.0) {
		cg.damageY = 1.0;
	}
	if (cg.damageY < -1.0) {
		cg.damageY = -1.0;
	}
	// don't let the screen flashes vary as much
	if (kick > 10) {
		kick = 10;
	}
	cg.damageValue = kick;
	cg.v_dmg_time = cg.time + DAMAGE_TIME;
	cg.damageTime = cg.snap->serverTime;
}

/*
================
CG_Respawn

A respawn happened this snapshot
================
*/
void CG_Respawn(void)
{

	//Slicer: Force Reset the FOV to 90

	cg.zoomLevel = 0;
	cg.lastZoomLevel = 0;

	//int i=0;
	//float cvar_val;
	// no error decay on player movement
	cg.thisFrameTeleport = qtrue;

	// display weapons available
	cg.weaponSelectTime = cg.time;

	// select the weapon the server says we are using
	cg.weaponSelect = cg.snap->ps.weapon;

//Slicer: Done Server Side
	//Elder: added to reset zoom stuff LOCALLY
	//CG_RQ3_Zoom1x();

}

extern char *eventnames[];

/*
==============
CG_CheckPlayerstateEvents
==============
*/
void CG_CheckPlayerstateEvents(playerState_t * ps, playerState_t * ops)
{
	int i;
	int event;
	centity_t *cent;

	if (ps->externalEvent && ps->externalEvent != ops->externalEvent) {
		cent = &cg_entities[ps->clientNum];
		cent->currentState.event = ps->externalEvent;
		cent->currentState.eventParm = ps->externalEventParm;
		CG_EntityEvent(cent, cent->lerpOrigin);
	}

	cent = &cg.predictedPlayerEntity;	// cg_entities[ ps->clientNum ];
	// go through the predictable events buffer
	for (i = ps->eventSequence - MAX_PS_EVENTS; i < ps->eventSequence; i++) {
		// if we have a new predictable event
		if (i >= ops->eventSequence
		    // or the server told us to play another event instead of a predicted event we already issued
		    // or something the server told us changed our prediction causing a different event
		    || (i > ops->eventSequence - MAX_PS_EVENTS
			&& ps->events[i & (MAX_PS_EVENTS - 1)] != ops->events[i & (MAX_PS_EVENTS - 1)])) {

			event = ps->events[i & (MAX_PS_EVENTS - 1)];
			cent->currentState.event = event;
			cent->currentState.eventParm = ps->eventParms[i & (MAX_PS_EVENTS - 1)];
			CG_EntityEvent(cent, cent->lerpOrigin);

			cg.predictableEvents[i & (MAX_PREDICTED_EVENTS - 1)] = event;

			cg.eventSequence++;
		}
	}
}

/*
==================
CG_CheckChangedPredictableEvents
==================
*/
void CG_CheckChangedPredictableEvents(playerState_t * ps)
{
	int i;
	int event;
	centity_t *cent;

	cent = &cg.predictedPlayerEntity;
	for (i = ps->eventSequence - MAX_PS_EVENTS; i < ps->eventSequence; i++) {
		//
		if (i >= cg.eventSequence) {
			continue;
		}
		// if this event is not further back in than the maximum predictable events we remember
		if (i > cg.eventSequence - MAX_PREDICTED_EVENTS) {
			// if the new playerstate event is different from a previously predicted one
			if (ps->events[i & (MAX_PS_EVENTS - 1)] != cg.predictableEvents[i & (MAX_PREDICTED_EVENTS - 1)]) {

				event = ps->events[i & (MAX_PS_EVENTS - 1)];
				cent->currentState.event = event;
				cent->currentState.eventParm = ps->eventParms[i & (MAX_PS_EVENTS - 1)];
				CG_EntityEvent(cent, cent->lerpOrigin);

				cg.predictableEvents[i & (MAX_PREDICTED_EVENTS - 1)] = event;

				if (cg_showmiss.integer) {
					CG_Printf("WARNING: changed predicted event\n");
				}
			}
		}
	}
}

/*
==================
pushReward
==================
// JBravo: apparently not used.
*/
/*
static void pushReward(sfxHandle_t sfx, qhandle_t shader, int rewardCount) {
	if (cg.rewardStack < (MAX_REWARDSTACK-1)) {
		cg.rewardStack++;
		cg.rewardSound[cg.rewardStack] = sfx;
		cg.rewardShader[cg.rewardStack] = shader;
		cg.rewardCount[cg.rewardStack] = rewardCount;
	}
}
*/

/*
==================
CG_CheckLocalSounds
==================
*/
void CG_CheckLocalSounds(playerState_t * ps, playerState_t * ops)
{
	//int health, armor, reward;
	int reward;

	// don't play the sounds if the player just changed teams
	if (ps->persistant[PERS_TEAM] != ops->persistant[PERS_TEAM]) {
		return;
	}
	// hit changes
	if (ps->persistant[PERS_HITS] > ops->persistant[PERS_HITS]) {
//		armor = ps->persistant[PERS_ATTACKEE_ARMOR] & 0xff;
//		health = ps->persistant[PERS_ATTACKEE_ARMOR] >> 8;
	} else if (ps->persistant[PERS_HITS] < ops->persistant[PERS_HITS]) {
		if (cg_RQ3_anouncer.integer == 1)
			trap_S_StartLocalSound(cgs.media.hitTeamSound, CHAN_LOCAL_SOUND);
	}
	// health changes of more than -1 should make pain sounds
	if (ps->stats[STAT_HEALTH] < ops->stats[STAT_HEALTH] - 1) {
		if (ps->stats[STAT_HEALTH] > 0) {
			CG_PainEvent(&cg.predictedPlayerEntity, ps->stats[STAT_HEALTH]);
		}
	}

	// if we are going into the intermission, don't start any voices
	if (cg.intermissionStarted) {
		return;
	}
	// reward sounds
	reward = qfalse;

	// if any of the player event bits changed
	if (ps->persistant[PERS_PLAYEREVENTS] != ops->persistant[PERS_PLAYEREVENTS]) {
		if ((ps->persistant[PERS_PLAYEREVENTS] & PLAYEREVENT_DENIEDREWARD) !=
		    (ops->persistant[PERS_PLAYEREVENTS] & PLAYEREVENT_DENIEDREWARD)) {
			if (cg_RQ3_anouncer.integer == 1)
				trap_S_StartLocalSound(cgs.media.deniedSound, CHAN_ANNOUNCER);
		} else if ((ps->persistant[PERS_PLAYEREVENTS] & PLAYEREVENT_GAUNTLETREWARD) !=
			   (ops->persistant[PERS_PLAYEREVENTS] & PLAYEREVENT_GAUNTLETREWARD)) {
			if (cg_RQ3_anouncer.integer == 1)
				trap_S_StartLocalSound(cgs.media.humiliationSound, CHAN_ANNOUNCER);
		} else if ((ps->persistant[PERS_PLAYEREVENTS] & PLAYEREVENT_HOLYSHIT) !=
			   (ops->persistant[PERS_PLAYEREVENTS] & PLAYEREVENT_HOLYSHIT)) {
			if (cg_RQ3_anouncer.integer == 1)
				trap_S_StartLocalSound(cgs.media.holyShitSound, CHAN_ANNOUNCER);
		}
		reward = qtrue;
	}
	// check for flag pickup
	if (cgs.gametype > GT_TEAMPLAY) {
		if ((ps->powerups[PW_REDFLAG] != ops->powerups[PW_REDFLAG] && ps->powerups[PW_REDFLAG]) ||
		    (ps->powerups[PW_BLUEFLAG] != ops->powerups[PW_BLUEFLAG] && ps->powerups[PW_BLUEFLAG]) ||
		    (ps->powerups[PW_NEUTRALFLAG] != ops->powerups[PW_NEUTRALFLAG] && ps->powerups[PW_NEUTRALFLAG])) {
			trap_S_StartLocalSound(cgs.media.youHaveFlagSound, CHAN_ANNOUNCER);
		}
	}
	// lead changes
	if (!reward) {
		//
		if (!cg.warmup) {
			// never play lead changes during warmup
			if (ps->persistant[PERS_RANK] != ops->persistant[PERS_RANK]) {
				if (cgs.gametype < GT_TEAM) {
					if (ps->persistant[PERS_RANK] == 0) {
						if (cg_RQ3_anouncer.integer == 1)
							CG_AddBufferedSound(cgs.media.takenLeadSound);
					} else if (ps->persistant[PERS_RANK] == RANK_TIED_FLAG) {
						if (cg_RQ3_anouncer.integer == 1)
							CG_AddBufferedSound(cgs.media.tiedLeadSound);
					} else if ((ops->persistant[PERS_RANK] & ~RANK_TIED_FLAG) == 0) {
						if (cg_RQ3_anouncer.integer == 1)
							CG_AddBufferedSound(cgs.media.lostLeadSound);
					}
				}
			}
		}
	}
	// timelimit warnings
	// JBravo: this does nothing
/*
	if (cgs.timelimit > 0) {
		int msec;
		msec = cg.time - cgs.levelStartTime;
	}
*/
}

/*
===============
CG_TransitionPlayerState

===============
*/
void CG_TransitionPlayerState(playerState_t * ps, playerState_t * ops)
{
	// check for changing follow mode
	if (ps->clientNum != ops->clientNum) {
		cg.thisFrameTeleport = qtrue;
		// Slicer
		if (cgs.gametype == GT_TEAMPLAY) {
			if (ps->persistant[PERS_SPAWN_COUNT] != ops->persistant[PERS_SPAWN_COUNT])
				CG_Respawn();
		}
		// make sure we don't get any unwanted transition effects
		*ops = *ps;
	}
	// damage events (player is getting wounded)
	//Makro - not if wearing kevlar
	if (ps->damageEvent != ops->damageEvent && ps->damageCount && !(cg.snap->ps.stats[STAT_HOLDABLE_ITEM] & (1 << HI_KEVLAR))) {
		CG_DamageFeedback(ps->damageYaw, ps->damagePitch, ps->damageCount);
	}
	// respawning
	if (ps->persistant[PERS_SPAWN_COUNT] != ops->persistant[PERS_SPAWN_COUNT]) {
		CG_Respawn();
	}

	if (cg.mapRestart) {
		CG_Respawn();
		cg.mapRestart = qfalse;
	}

	if (cg.snap->ps.pm_type != PM_INTERMISSION && ps->persistant[PERS_TEAM] != TEAM_SPECTATOR) {
		CG_CheckLocalSounds(ps, ops);
	}
	// check for going low on ammo
	CG_CheckAmmo();

	// run events
	CG_CheckPlayerstateEvents(ps, ops);

	// smooth the ducking viewheight change
	if (ps->viewheight != ops->viewheight) {
		cg.duckChange = ps->viewheight - ops->viewheight;
		cg.duckTime = cg.time;
	}
	// Elder: reset sync sounds
	/*
	   if ( ps->weaponstate != ops->weaponstate )
	   {
	   cg.curSyncSound = 0;
	   }
	 */

	//Elder: grenade message
	if (ps->weapon == WP_GRENADE && ps->weaponstate == WEAPON_COCKED && ops->weaponstate != WEAPON_COCKED) {
		switch (CG_RQ3_GetGrenadeMode()) {
		case RQ3_GRENSHORT | RQ3_GRENMED:
			CG_AddMessage("Pin pulled. Ready to make a long range throw.\n");
			break;
		case RQ3_GRENMED:
			CG_AddMessage("Pin pulled. Ready to make a medium range throw.\n");
			break;
		case RQ3_GRENSHORT:
			CG_AddMessage("Pin pulled. Ready to make a short range throw.\n");
			break;
		}
	}
}
