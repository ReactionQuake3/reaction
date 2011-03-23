//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.29  2005/09/08 03:47:35  jbravo
// Fixing 'No newline at end of file' warnings
//
// Revision 1.28  2005/02/15 16:33:38  makro
// Tons of updates (entity tree attachment system, UI vectors)
//
// Revision 1.27  2003/03/10 07:07:58  jbravo
// Small unlagged fixes and voting delay added.
//
// Revision 1.26  2003/03/09 21:30:38  jbravo
// Adding unlagged.   Still needs work.
//
// Revision 1.25  2002/07/21 18:47:27  niceass
// weaponprediction cvar added
//
// Revision 1.24  2002/06/16 20:06:13  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.23  2002/06/16 19:12:52  jbravo
// Removed the MISSIONPACK ifdefs and missionpack only code.
//
// Revision 1.22  2002/06/11 23:38:43  niceass
// spectator fix
//
// Revision 1.21  2002/06/10 13:20:03  slicer
// RefID is now passed trought scoreboard, no more lca cvar, only cg.lca
//
// Revision 1.20  2002/06/03 05:23:22  niceass
// spectator changes
//
// Revision 1.19  2002/03/31 03:31:24  jbravo
// Compiler warning cleanups
//
// Revision 1.18  2002/03/30 02:29:43  jbravo
// Lots of spectator code updates. Removed debugshit, added some color.
//
// Revision 1.17  2002/03/23 05:17:42  jbravo
// Major cleanup of game -> cgame communication with LCA vars.
//
// Revision 1.16  2002/03/11 02:23:06  niceass
// client gravity fix
//
// Revision 1.15  2002/02/26 02:58:47  jbravo
// Fixing the spectator_free mode not being predicted in the client.
//
// Revision 1.14  2002/01/27 13:33:28  jbravo
// Teamplay antistick system.
//
// Revision 1.13  2002/01/14 01:19:23  niceass
// No more default 800 gravity on items - NiceAss
//
// Revision 1.12  2002/01/11 20:20:57  jbravo
// Adding TP to main branch
//
// Revision 1.11  2002/01/11 19:48:29  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.10  2001/12/31 16:28:41  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
// cg_predict.c -- this file generates cg.predictedPlayerState by either
// interpolating between snapshots from the server or locally predicting
// ahead the client's movement.
// It also handles local physics interaction, like fragments bouncing off walls

#include "cg_local.h"

static pmove_t cg_pmove;

static int cg_numSolidEntities;
static centity_t *cg_solidEntities[MAX_ENTITIES_IN_SNAPSHOT];
static int cg_numTriggerEntities;
static centity_t *cg_triggerEntities[MAX_ENTITIES_IN_SNAPSHOT];

/*
====================
CG_BuildSolidList

When a new cg.snap has been set, this function builds a sublist
of the entities that are actually solid, to make for more
efficient collision detection
====================
*/
void CG_BuildSolidList(void)
{
	int i;
	centity_t *cent;
	snapshot_t *snap;
	entityState_t *ent;

	cg_numSolidEntities = 0;
	cg_numTriggerEntities = 0;

	if (cg.nextSnap && !cg.nextFrameTeleport && !cg.thisFrameTeleport) {
		snap = cg.nextSnap;
	} else {
		snap = cg.snap;
	}

	for (i = 0; i < snap->numEntities; i++) {
		cent = &cg_entities[snap->entities[i].number];
		ent = &cent->currentState;

		if (ent->eType == ET_ITEM || ent->eType == ET_PUSH_TRIGGER || ent->eType == ET_TELEPORT_TRIGGER) {
			cg_triggerEntities[cg_numTriggerEntities] = cent;
			cg_numTriggerEntities++;
			continue;
		}

		if (cent->nextState.solid) {
			cg_solidEntities[cg_numSolidEntities] = cent;
			cg_numSolidEntities++;
			continue;
		}
	}
}

/*
====================
CG_ClipMoveToEntities

====================
*/
static void CG_ClipMoveToEntities(const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end,
				  int skipNumber, int mask, trace_t * tr)
{
	int i, x, zd, zu;
	trace_t trace;
	entityState_t *ent;
	clipHandle_t cmodel;
	vec3_t bmins, bmaxs;
	vec3_t origin, angles;
	centity_t *cent;

	for (i = 0; i < cg_numSolidEntities; i++) {
		cent = cg_solidEntities[i];
		ent = &cent->currentState;

		if (ent->number == skipNumber) {
			continue;
		}

		if (ent->solid == SOLID_BMODEL) {
			// special value for bmodel
			cmodel = trap_CM_InlineModel(ent->modelindex);
			//VectorCopy(cent->lerpAngles, angles);
			//CG_EvaluateTrajectory(&cent->currentState.pos, cg.physicsTime, origin);
			CG_EvaluateTrajectoryEx(cent, cg.physicsTime, origin, angles);
		} else {
			// encoded bbox
			x = (ent->solid & 255);
			zd = ((ent->solid >> 8) & 255);
			zu = ((ent->solid >> 16) & 255) - 32;

			bmins[0] = bmins[1] = -x;
			bmaxs[0] = bmaxs[1] = x;
			bmins[2] = -zd;
			bmaxs[2] = zu;

			cmodel = trap_CM_TempBoxModel(bmins, bmaxs);
			VectorCopy(vec3_origin, angles);
			VectorCopy(cent->lerpOrigin, origin);
		}

		trap_CM_TransformedBoxTrace(&trace, start, end, mins, maxs, cmodel, mask, origin, angles);

		if (trace.allsolid || trace.fraction < tr->fraction) {
			trace.entityNum = ent->number;
			*tr = trace;
		} else if (trace.startsolid) {
			tr->startsolid = qtrue;
		}
		if (tr->allsolid) {
			return;
		}
	}
}

/*
================
CG_Trace

Elder: changed header - added 'const' to mins and maxs so VMs can compile
Also check cg_syscalls.c and cg_local.h
================
*/
void CG_Trace(trace_t * result, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end,
	      int skipNumber, int mask)
{
	trace_t t;

	trap_CM_BoxTrace(&t, start, end, mins, maxs, 0, mask);
	t.entityNum = t.fraction != 1.0 ? ENTITYNUM_WORLD : ENTITYNUM_NONE;
	// check all other solid models
	CG_ClipMoveToEntities(start, mins, maxs, end, skipNumber, mask, &t);

	*result = t;
}

/*
================
CG_PointContents
================
*/
int CG_PointContents(const vec3_t point, int passEntityNum)
{
	int i;
	entityState_t *ent;
	centity_t *cent;
	clipHandle_t cmodel;
	int contents;

	contents = trap_CM_PointContents(point, 0);

	for (i = 0; i < cg_numSolidEntities; i++) {
		cent = cg_solidEntities[i];

		ent = &cent->currentState;

		if (ent->number == passEntityNum) {
			continue;
		}

		if (ent->solid != SOLID_BMODEL) {	// special value for bmodel
			continue;
		}

		cmodel = trap_CM_InlineModel(ent->modelindex);
		if (!cmodel) {
			continue;
		}

		contents |= trap_CM_TransformedPointContents(point, cmodel, ent->origin, ent->angles);
	}

	return contents;
}

/*
========================
CG_InterpolatePlayerState

Generates cg.predictedPlayerState by interpolating between
cg.snap->player_state and cg.nextFrame->player_state
========================
*/
static void CG_InterpolatePlayerState(qboolean grabAngles)
{
	float f;
	int i;
	playerState_t *out;
	snapshot_t *prev, *next;

	out = &cg.predictedPlayerState;
	prev = cg.snap;
	next = cg.nextSnap;

	*out = cg.snap->ps;

	// if we are still allowing local input, short circuit the view angles
	if (grabAngles) {
		usercmd_t cmd;
		int cmdNum;

		cmdNum = trap_GetCurrentCmdNumber();
		trap_GetUserCmd(cmdNum, &cmd);

		PM_UpdateViewAngles(out, &cmd);
	}
	// if the next frame is a teleport, we can't lerp to it
	if (cg.nextFrameTeleport) {
		return;
	}

	if (!next || next->serverTime <= prev->serverTime) {
		return;
	}

	f = (float) (cg.time - prev->serverTime) / (next->serverTime - prev->serverTime);

	i = next->ps.bobCycle;
	if (i < prev->ps.bobCycle) {
		i += 256;	// handle wraparound
	}
	out->bobCycle = prev->ps.bobCycle + f * (i - prev->ps.bobCycle);

	for (i = 0; i < 3; i++) {
		out->origin[i] = prev->ps.origin[i] + f * (next->ps.origin[i] - prev->ps.origin[i]);
		if (!grabAngles) {
			out->viewangles[i] = LerpAngle(prev->ps.viewangles[i], next->ps.viewangles[i], f);
		}
		out->velocity[i] = prev->ps.velocity[i] + f * (next->ps.velocity[i] - prev->ps.velocity[i]);
	}

}

/*
===================
CG_TouchItem
===================
*/
static void CG_TouchItem(centity_t * cent)
{
//      gitem_t         *item;
//Blaze: No item prediction
	return;
// JBravo - Compiler warnings over unreached code.
/*
	if ( !cg_predictItems.integer ) {
		return;
	}
	if ( !BG_PlayerTouchesItem( &cg.predictedPlayerState, &cent->currentState, cg.time ) ) {
		return;
	}

	// never pick an item up twice in a prediction
	if ( cent->miscTime == cg.time ) {
		return;
	}
	item = &bg_itemlist[ cent->currentState.modelindex ];
	if ( !BG_CanItemBeGrabbed( cgs.gametype, &cent->currentState, &cg.predictedPlayerState ) ) {
		return;		// can't hold it
	}

	// Special case for flags.
	// We don't predict touching our own flag
	if( cgs.gametype == GT_CTF ) {
		if (cg.predictedPlayerState.persistant[PERS_TEAM] == TEAM_RED &&
			item->giTag == PW_REDFLAG)
			return;
		if (cg.predictedPlayerState.persistant[PERS_TEAM] == TEAM_BLUE &&
			item->giTag == PW_BLUEFLAG)
			return;
	}

	// grab it
	BG_AddPredictableEventToPlayerstate( EV_ITEM_PICKUP, cent->currentState.modelindex , &cg.predictedPlayerState);

	// remove it from the frame so it won't be drawn
	cent->currentState.eFlags |= EF_NODRAW;

	// don't touch it again this prediction
	cent->miscTime = cg.time;

	// if its a weapon, give them some predicted ammo so the autoswitch will work
	if ( item->giType == IT_WEAPON ) {
		cg.predictedPlayerState.stats[ STAT_WEAPONS ] |= 1 << item->giTag;
		if ( !cg.predictedPlayerState.ammo[ item->giTag ] ) {
			cg.predictedPlayerState.ammo[ item->giTag ] = 1;
		}
	}  */
}

/*
=========================
CG_TouchTriggerPrediction

Predict push triggers and items
=========================
*/
static void CG_TouchTriggerPrediction(void)
{
	int i;
	trace_t trace;
	entityState_t *ent;
	clipHandle_t cmodel;
	centity_t *cent;
	qboolean spectator;

	// dead clients don't activate triggers
	if (cg.predictedPlayerState.stats[STAT_HEALTH] <= 0) {
		return;
	}

	spectator = (cg.predictedPlayerState.pm_type == PM_SPECTATOR);

	if (cg.predictedPlayerState.pm_type != PM_NORMAL && !spectator) {
		return;
	}

	for (i = 0; i < cg_numTriggerEntities; i++) {
		cent = cg_triggerEntities[i];
		ent = &cent->currentState;

		if (ent->eType == ET_ITEM && !spectator) {
			CG_TouchItem(cent);
			continue;
		}

		if (ent->solid != SOLID_BMODEL) {
			continue;
		}

		cmodel = trap_CM_InlineModel(ent->modelindex);
		if (!cmodel) {
			continue;
		}

		trap_CM_BoxTrace(&trace, cg.predictedPlayerState.origin, cg.predictedPlayerState.origin,
				 cg_pmove.mins, cg_pmove.maxs, cmodel, -1);

		if (!trace.startsolid) {
			continue;
		}

		if (ent->eType == ET_TELEPORT_TRIGGER) {
			cg.hyperspace = qtrue;
		} else if (ent->eType == ET_PUSH_TRIGGER) {
			BG_TouchJumpPad(&cg.predictedPlayerState, ent);
		}
	}

	// if we didn't touch a jump pad this pmove frame
	if (cg.predictedPlayerState.jumppad_frame != cg.predictedPlayerState.pmove_framecount) {
		cg.predictedPlayerState.jumppad_frame = 0;
		cg.predictedPlayerState.jumppad_ent = 0;
	}
}

// JBravo: unlagged - optimized prediction
#define ABS(x) ((x) < 0 ? (-(x)) : (x))

static int IsUnacceptableError (playerState_t *ps, playerState_t *pps) {
	vec3_t delta;
	int i;

	if (pps->pm_type != ps->pm_type ||
			pps->pm_flags != ps->pm_flags ||
			pps->pm_time != ps->pm_time) {
		return 1;
	}

	VectorSubtract(pps->origin, ps->origin, delta);
	if (VectorLengthSquared( delta ) > 0.1f * 0.1f) {
		if (cg_showmiss.integer) {
			CG_Printf("delta: %.2f  ", VectorLength(delta));
		}
		return 2;
	}

	VectorSubtract(pps->velocity, ps->velocity, delta);
	if (VectorLengthSquared( delta ) > 0.1f * 0.1f) {
		if (cg_showmiss.integer) {
			CG_Printf("delta: %.2f  ", VectorLength(delta));
		}
		return 3;
	}

	if (pps->weaponTime != ps->weaponTime ||
			pps->gravity != ps->gravity ||
			pps->speed != ps->speed ||
			pps->delta_angles[0] != ps->delta_angles[0] ||
			pps->delta_angles[1] != ps->delta_angles[1] ||
			pps->delta_angles[2] != ps->delta_angles[2] ||
			pps->groundEntityNum != ps->groundEntityNum) {
		return 4;
	}

	if (pps->legsTimer != ps->legsTimer ||
			pps->legsAnim != ps->legsAnim ||
			pps->torsoTimer != ps->torsoTimer ||
			pps->torsoAnim != ps->torsoAnim ||
			pps->movementDir != ps->movementDir) {
		return 5;
	}

	VectorSubtract(pps->grapplePoint, ps->grapplePoint, delta);
	if (VectorLengthSquared(delta) > 0.1f * 0.1f) {
		return 6;
	}

	if (pps->eFlags != ps->eFlags) {
		return 7;
	}

	if (pps->eventSequence != ps->eventSequence) {
		return 8;
	}

	for (i = 0; i < MAX_PS_EVENTS; i++) {
		if (pps->events[i] != ps->events[i] ||
				pps->eventParms[i] != ps->eventParms[i]) {
			return 9;
		}
	}

	if (pps->externalEvent != ps->externalEvent ||
			pps->externalEventParm != ps->externalEventParm ||
			pps->externalEventTime != ps->externalEventTime) {
		return 10;
	}

	if (pps->clientNum != ps->clientNum ||
			pps->weapon != ps->weapon ||
			pps->weaponstate != ps->weaponstate) {
		return 11;
	}

	if (ABS(pps->viewangles[0] - ps->viewangles[0]) > 1.0f ||
			ABS(pps->viewangles[1] - ps->viewangles[1]) > 1.0f ||
			ABS(pps->viewangles[2] - ps->viewangles[2]) > 1.0f) {
		return 12;
	}

	if (pps->viewheight != ps->viewheight) {
		return 13;
	}

	if (pps->damageEvent != ps->damageEvent ||
			pps->damageYaw != ps->damageYaw ||
			pps->damagePitch != ps->damagePitch ||
			pps->damageCount != ps->damageCount) {
		return 14;
	}

	for (i = 0; i < MAX_STATS; i++) {
		if (pps->stats[i] != ps->stats[i]) {
			return 15;
		}
	}

	for (i = 0; i < MAX_PERSISTANT; i++) {
		if (pps->persistant[i] != ps->persistant[i]) {
			return 16;
		}
	}

	for (i = 0; i < MAX_POWERUPS; i++) {
		if (pps->powerups[i] != ps->powerups[i]) {
			return 17;
		}
	}

	for (i = 0; i < MAX_WEAPONS; i++) {
		if (pps->ammo[i] != ps->ammo[i]) {
			return 18;
		}
	}

	if (pps->generic1 != ps->generic1 ||
			pps->loopSound != ps->loopSound ||
			pps->jumppad_ent != ps->jumppad_ent) {
		return 19;
	}

	return 0;
}

/*
=================
CG_PredictPlayerState

Generates cg.predictedPlayerState for the current cg.time
cg.predictedPlayerState is guaranteed to be valid after exiting.

For demo playback, this will be an interpolation between two valid
playerState_t.

For normal gameplay, it will be the result of predicted usercmd_t on
top of the most recent playerState_t received from the server.

Each new snapshot will usually have one or more new usercmd over the last,
but we simulate all unacknowledged commands each time, not just the new ones.
This means that on an internet connection, quite a few pmoves may be issued
each frame.

OPTIMIZE: don't re-simulate unless the newly arrived snapshot playerState_t
differs from the predicted one.  Would require saving all intermediate
playerState_t during prediction.

We detect prediction errors and allow them to be decayed off over several frames
to ease the jerk.
=================
*/
void CG_PredictPlayerState(void)
{
	int cmdNum, current;
	playerState_t oldPlayerState;
	qboolean moved;
	usercmd_t oldestCmd;
	usercmd_t latestCmd;
// JBravo: unlagged
	int stateIndex = 0, predictCmd = 0;
	int numPredicted = 0, numPlayedBack = 0;

	cg.hyperspace = qfalse;	// will be set if touching a trigger_teleport

	// if this is the first frame we must guarantee
	// predictedPlayerState is valid even if there is some
	// other error condition
	if (!cg.validPPS) {
		cg.validPPS = qtrue;
		cg.predictedPlayerState = cg.snap->ps;
	}

	// demo playback just copies the moves
	// JBravo: Zcam fix
	/* camera jitter fix (client side) */
	if (cg.demoPlayback || (cg.snap->ps.pm_flags & PMF_FOLLOW) ||
	    ((cg.snap->ps.stats[STAT_RQ3] & RQ3_ZCAM) == RQ3_ZCAM)
		|| (cg_pmove.ps && cg_pmove.ps->pm_type == PM_DEAD) ) {
		CG_InterpolatePlayerState(qfalse);
		return;
	}
	// non-predicting local movement will grab the latest angles
	if (cg_nopredict.integer || cg_synchronousClients.integer) {
		CG_InterpolatePlayerState(qtrue);
		return;
	}
	// prepare for pmove
	cg_pmove.ps = &cg.predictedPlayerState;
	cg_pmove.trace = CG_Trace;
	cg_pmove.pointcontents = CG_PointContents;
	if (cg_pmove.ps->pm_type == PM_DEAD || cg_pmove.ps->pm_type == PM_SPECTATOR) {
		cg_pmove.tracemask = 0;	//NiceAss: User can go through anything. Before it was: MASK_PLAYERSOLID & ~CONTENTS_BODY;
	} else {
		cg_pmove.tracemask = MASK_PLAYERSOLID;
	}

	// JBravo: fixing telefragging and shit during spawing (Thanks NiceAss! :)
	if ((cg.snap->ps.stats[STAT_RQ3] & RQ3_PLAYERSOLID) != RQ3_PLAYERSOLID) {
		cg_pmove.tracemask &= ~CONTENTS_BODY;
	}

	cg_pmove.noFootsteps = (cgs.dmflags & DF_NO_FOOTSTEPS) > 0;

	// save the state before the pmove so we can detect transitions
	oldPlayerState = cg.predictedPlayerState;

	current = trap_GetCurrentCmdNumber();

	// if we don't have the commands right after the snapshot, we
	// can't accurately predict a current position, so just freeze at
	// the last good position we had
	cmdNum = current - CMD_BACKUP + 1;
	trap_GetUserCmd(cmdNum, &oldestCmd);
	if (oldestCmd.serverTime > cg.snap->ps.commandTime && oldestCmd.serverTime < cg.time) {	// special check for map_restart
		if (cg_showmiss.integer) {
			CG_Printf("exceeded PACKET_BACKUP on commands\n");
		}
		return;
	}
	// get the latest command so we can know which commands are from previous map_restarts
	trap_GetUserCmd(current, &latestCmd);

	// get the most recent information we have, even if
	// the server time is beyond our current cg.time,
	// because predicted player positions are going to
	// be ahead of everything else anyway
	if (cg.nextSnap && !cg.nextFrameTeleport && !cg.thisFrameTeleport) {
		cg.predictedPlayerState = cg.nextSnap->ps;
		cg.physicsTime = cg.nextSnap->serverTime;
	} else {
		cg.predictedPlayerState = cg.snap->ps;
		cg.physicsTime = cg.snap->serverTime;
	}

	if (pmove_msec.integer < 8) {
		trap_Cvar_Set("pmove_msec", "8");
	} else if (pmove_msec.integer > 33) {
		trap_Cvar_Set("pmove_msec", "33");
	}

	cg_pmove.pmove_fixed = pmove_fixed.integer;	// | cg_pmove_fixed.integer;
	cg_pmove.pmove_msec = pmove_msec.integer;

// JBravo: unlagged
	if (cg_optimizePrediction.integer && !cg_latentCmds.integer) {
		if (cg.nextFrameTeleport || cg.thisFrameTeleport) {
			cg.lastPredictedCommand = 0;
			cg.stateTail = cg.stateHead;
			predictCmd = current - CMD_BACKUP + 1;
		} else if (cg.physicsTime == cg.lastServerTime) {
			predictCmd = cg.lastPredictedCommand + 1;
		} else {
			int i;
			qboolean error = qtrue;

			for (i = cg.stateHead; i != cg.stateTail; i = (i + 1) % NUM_SAVED_STATES) {
				if (cg.savedPmoveStates[i].commandTime == cg.predictedPlayerState.commandTime) {
					int errorcode = IsUnacceptableError(&cg.predictedPlayerState, &cg.savedPmoveStates[i]);
					if (errorcode) {
						if (cg_showmiss.integer) {
							CG_Printf("errorcode %d at %d\n", errorcode, cg.time);
						}
						break;
					}
					*cg_pmove.ps = cg.savedPmoveStates[i];
					cg.stateHead = (i + 1) % NUM_SAVED_STATES;
					predictCmd = cg.lastPredictedCommand + 1;
					error = qfalse;
					break;
				}
			}
			if (error) {
				cg.lastPredictedCommand = 0;
				cg.stateTail = cg.stateHead;
				predictCmd = current - CMD_BACKUP + 1;
			}
		}
		cg.lastServerTime = cg.physicsTime;
		stateIndex = cg.stateHead;
	}

	// run cmds
	moved = qfalse;
	for (cmdNum = current - CMD_BACKUP + 1; cmdNum <= current; cmdNum++) {
		// get the command
		trap_GetUserCmd(cmdNum, &cg_pmove.cmd);

		if (cg_pmove.pmove_fixed) {
			PM_UpdateViewAngles(cg_pmove.ps, &cg_pmove.cmd);
		}
		// don't do anything if the time is before the snapshot player time
		if (cg_pmove.cmd.serverTime <= cg.predictedPlayerState.commandTime) {
			continue;
		}
		// don't do anything if the command was from a previous map_restart
		if (cg_pmove.cmd.serverTime > latestCmd.serverTime) {
			continue;
		}
		// check for a prediction error from last frame
		// on a lan, this will often be the exact value
		// from the snapshot, but on a wan we will have
		// to predict several commands to get to the point
		// we want to compare
		if (cg.predictedPlayerState.commandTime == oldPlayerState.commandTime) {
			vec3_t delta;
			float len;

			if (cg.thisFrameTeleport) {
				// a teleport will not cause an error decay
				VectorClear(cg.predictedError);
				if (cg_showmiss.integer) {
					CG_Printf("PredictionTeleport\n");
				}
				cg.thisFrameTeleport = qfalse;
			} else {
				vec3_t adjusted;

				//Makro - made it so that angles get adjusted, too
				{
					vec3_t angles;
					VectorCopy(cg.predictedPlayerState.viewangles, angles);
					CG_AdjustPositionForMover(cg.predictedPlayerState.origin,
								  cg.predictedPlayerState.groundEntityNum, cg.physicsTime,
								  cg.oldTime, adjusted, angles);
					// only YAW for players, though
					cg.predictedPlayerState.viewangles[YAW] = angles[YAW];
				}

				if (cg_showmiss.integer) {
					if (!VectorCompare(oldPlayerState.origin, adjusted)) {
						CG_Printf("prediction error\n");
					}
				}
				VectorSubtract(oldPlayerState.origin, adjusted, delta);
				len = VectorLength(delta);
				if (len > 0.1) {
					if (cg_showmiss.integer) {
						CG_Printf("Prediction miss: %f\n", len);
					}
					if (cg_errorDecay.integer) {
						int t;
						float f;

						t = cg.time - cg.predictedErrorTime;
						f = (cg_errorDecay.value - t) / cg_errorDecay.value;
						if (f < 0) {
							f = 0;
						}
						if (f > 0 && cg_showmiss.integer) {
							CG_Printf("Double prediction decay: %f\n", f);
						}
						VectorScale(cg.predictedError, f, cg.predictedError);
					} else {
						VectorClear(cg.predictedError);
					}
					VectorAdd(delta, cg.predictedError, cg.predictedError);
					cg.predictedErrorTime = cg.oldTime;
				}
			}
		}
		// don't predict gauntlet firing, which is only supposed to happen
		// when it actually inflicts damage
		cg_pmove.gauntletHit = qfalse;

		if (cg_pmove.pmove_fixed) {
			cg_pmove.cmd.serverTime =
			    ((cg_pmove.cmd.serverTime + pmove_msec.integer -
			      1) / pmove_msec.integer) * pmove_msec.integer;
		}

// JBravo: setting lca in pm if needed
		//if (cg_RQ3_lca.integer == 1)
		if (cg.lca)
			cg_pmove.lca = qtrue;
		else
			cg_pmove.lca = qfalse;
		
		
		if (cg_RQ3_predictWeapons.integer)
			cg_pmove.predict = qtrue;
		else
			cg_pmove.predict = qfalse;

// JBravo: unlagged
		if (cg_optimizePrediction.integer && !cg_latentCmds.integer) {
			if (cmdNum >= predictCmd || (stateIndex + 1) % NUM_SAVED_STATES == cg.stateHead) {
				Pmove (&cg_pmove);
				numPredicted++;
				cg.lastPredictedCommand = cmdNum;
				if ((stateIndex + 1) % NUM_SAVED_STATES != cg.stateHead) {
					cg.savedPmoveStates[stateIndex] = *cg_pmove.ps;
					stateIndex = (stateIndex + 1) % NUM_SAVED_STATES;
					cg.stateTail = stateIndex;
				}
			} else {
				numPlayedBack++;
				if (cg_showmiss.integer &&
						cg.savedPmoveStates[stateIndex].commandTime != cg_pmove.cmd.serverTime) {
					CG_Printf("saved state miss\n");
				}
				*cg_pmove.ps = cg.savedPmoveStates[stateIndex];
				stateIndex = (stateIndex + 1) % NUM_SAVED_STATES;
			}
		} else {
			Pmove (&cg_pmove);
			numPredicted++;
		}

		moved = qtrue;

		// add push trigger movement effects
		CG_TouchTriggerPrediction();

		// check for predictable events that changed from previous predictions
		//CG_CheckChangedPredictableEvents(&cg.predictedPlayerState);
	}

	if (cg_showmiss.integer > 1) {
		CG_Printf("[%i : %i] ", cg_pmove.cmd.serverTime, cg.time);
	}

	if (!moved) {
		if (cg_showmiss.integer) {
			CG_Printf("not moved\n");
		}
		return;
	}
	// adjust for the movement of the groundentity
	//Makro - made it so that angles get adjusted, too
	{
		vec3_t angles;
		VectorCopy(cg.predictedPlayerState.viewangles, angles);
		CG_AdjustPositionForMover(cg.predictedPlayerState.origin,
					  cg.predictedPlayerState.groundEntityNum,
					  cg.physicsTime, cg.time, cg.predictedPlayerState.origin, angles);
		// only YAW for players, though
		cg.predictedPlayerState.viewangles[YAW] = angles[YAW];
	}

	if (cg_showmiss.integer) {
		if (cg.predictedPlayerState.eventSequence > oldPlayerState.eventSequence + MAX_PS_EVENTS) {
			CG_Printf("WARNING: dropped event\n");
		}
	}
	// fire events and other transition triggered things
	CG_TransitionPlayerState(&cg.predictedPlayerState, &oldPlayerState);

	if (cg_showmiss.integer) {
		if (cg.eventSequence > cg.predictedPlayerState.eventSequence) {
			CG_Printf("WARNING: double event\n");
			cg.eventSequence = cg.predictedPlayerState.eventSequence;
		}
	}
}

/*
================
CG_EvaluateTrajectory

================
*/
void CG_EvaluateTrajectory(const trajectory_t * tr, int atTime, vec3_t result)
{
	float deltaTime;
	float phase;

	switch (tr->trType) {
	case TR_STATIONARY:
	case TR_INTERPOLATE:
		VectorCopy(tr->trBase, result);
		break;
	case TR_LINEAR:
		deltaTime = (atTime - tr->trTime) * 0.001;	// milliseconds to seconds
		VectorMA(tr->trBase, deltaTime, tr->trDelta, result);
		break;
	case TR_SINE:
		deltaTime = (atTime - tr->trTime) / (float) tr->trDuration;
		phase = sin(deltaTime * M_PI * 2);
		VectorMA(tr->trBase, phase, tr->trDelta, result);
		break;
	case TR_LINEAR_STOP:
		if (atTime > tr->trTime + tr->trDuration) {
			atTime = tr->trTime + tr->trDuration;
		}
		deltaTime = (atTime - tr->trTime) * 0.001;	// milliseconds to seconds
		if (deltaTime < 0) {
			deltaTime = 0;
		}
		VectorMA(tr->trBase, deltaTime, tr->trDelta, result);
		break;
	case TR_GRAVITY:
		deltaTime = (atTime - tr->trTime) * 0.001;	// milliseconds to seconds
		VectorMA(tr->trBase, deltaTime, tr->trDelta, result);
		result[2] -= 0.5 * cg_gravity.value * deltaTime * deltaTime;	// FIXME: local gravity...
		break;
	default:
		Com_Error(ERR_DROP, "CG_EvaluateTrajectory: unknown trType: %i", tr->trTime);
		break;
	}
}

/*
================
CG_EvaluateTrajectoryDelta

For determining velocity at a given time
================
*/
void CG_EvaluateTrajectoryDelta(const trajectory_t * tr, int atTime, vec3_t result)
{
	float deltaTime;
	float phase;

	switch (tr->trType) {
	case TR_STATIONARY:
	case TR_INTERPOLATE:
		VectorClear(result);
		break;
	case TR_LINEAR:
		VectorCopy(tr->trDelta, result);
		break;
	case TR_SINE:
		deltaTime = (atTime - tr->trTime) / (float) tr->trDuration;
		phase = cos(deltaTime * M_PI * 2);	// derivative of sin = cos
		phase *= 0.5;
		VectorScale(tr->trDelta, phase, result);
		break;
	case TR_LINEAR_STOP:
		if (atTime > tr->trTime + tr->trDuration) {
			VectorClear(result);
			return;
		}
		VectorCopy(tr->trDelta, result);
		break;
	case TR_GRAVITY:
		deltaTime = (atTime - tr->trTime) * 0.001;	// milliseconds to seconds
		VectorCopy(tr->trDelta, result);
		result[2] -= cg_gravity.value * deltaTime;	// FIXME: local gravity...
		break;
	default:
		Com_Error(ERR_DROP, "CG_EvaluateTrajectoryDelta: unknown trType: %i", tr->trTime);
		break;
	}
}

void CG_EvaluateTrajectoryEx(centity_t *cent, int time, vec3_t origin, vec3_t angles)
{

	if (origin) CG_EvaluateTrajectory(&cent->currentState.pos, time, origin);
	if (angles) CG_EvaluateTrajectory(&cent->currentState.apos, time, angles);

	if (cent->currentState.eType != ET_PLAYER && cent->currentState.eFlags & EF_ATTACHED)
	{
		vec3_t org, axis[3], parent_angles;
		centity_t *parent = cg_entities+cent->currentState.time2;
		
		VectorCopy(parent->lerpAngles, parent_angles);
		if (origin)
		{
			if (parent->lerpAngles[YAW] || parent->lerpAngles[PITCH] || parent->lerpAngles[ROLL])
			{
				VectorCopy(cent->currentState.angles2, org);
				VectorAdd(org, origin, org);
				AnglesToAxis(parent_angles, axis);
				ChangeRefSystem(org, NULL, axis, org);
				VectorAdd(org, parent->lerpOrigin, origin);
			} else {
				VectorAdd(origin, cent->currentState.angles2, origin);
				VectorAdd(origin, parent->lerpOrigin, origin);
			}
		}
		if (angles)
		{
			VectorAdd(angles, parent_angles, angles);
		}
	}
}
