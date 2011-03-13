//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.96  2007/07/31 20:02:56  makro
// Quick hack disabling footstep sounds for ladder surfaces
//
// Revision 1.95  2005/09/07 20:27:41  makro
// Entity attachment trees
//
// Revision 1.94  2005/02/15 16:33:39  makro
// Tons of updates (entity tree attachment system, UI vectors)
//
// Revision 1.93  2003/03/09 19:47:48  niceass
// Support for torso pistol animations
//
// Revision 1.92  2003/02/05 04:29:14  niceass
// added support for akimbo animations
//
// Revision 1.91  2002/10/26 00:37:18  jbravo
// New multiple item code and added PB support to the UI
//
// Revision 1.90  2002/09/08 23:25:09  niceass
// made cg_rq3_predictweapons even more like quake 2, and it's simpler
//
// Revision 1.89  2002/09/04 00:16:17  makro
// Fixed 'unselectable grenade shown in the inventory if you switch weapons
// after pulling the pin' bug
//
// Revision 1.88  2002/08/03 07:04:18  jbravo
// Fixed constant gasping sound when you die in shallow water
//
// Revision 1.87  2002/07/22 06:33:58  niceass
// cleaned up the powerup code
//
// Revision 1.86  2002/07/21 18:52:39  niceass
// weapon prediction stuff
//
// Revision 1.85  2002/07/16 04:27:19  niceass
// physics back to 2.0
//
// Revision 1.84  2002/07/08 04:34:41  niceass
// oops, small mistake
//
// Revision 1.83  2002/07/08 04:34:15  niceass
// changes to gravity and stuff
//
// Revision 1.82  2002/06/29 02:50:58  niceass
// m4 kick fix and removed ladder stuff
//
// Revision 1.81  2002/06/18 06:15:30  niceass
// m4 kick now smooth
//
// Revision 1.80  2002/06/18 05:18:55  niceass
// adjustment to leg damage
//
// Revision 1.79  2002/06/16 20:06:14  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.78  2002/06/16 17:37:59  jbravo
// Removed the MISSIONPACK ifdefs and missionpack only code.
//
// Revision 1.77  2002/06/11 03:09:28  niceass
// +attack cancels reloads
//
// Revision 1.76  2002/06/07 19:42:44  niceass
// leg damage much closer to AQ2
//
// Revision 1.75  2002/05/27 06:48:02  niceass
// new leg damage
//
// Revision 1.74  2002/05/21 04:58:27  blaze
// kicked the reload bugs ass!
//
// Revision 1.73  2002/05/11 19:18:20  makro
// Sand surfaceparm
//
// Revision 1.72  2002/05/11 18:47:09  niceass
// last fire animation fixed
//
// Revision 1.71  2002/05/08 07:24:33  niceass
// Double jumping added. Everything feels very good.
//
// Revision 1.70  2002/05/07 05:07:32  niceass
// several physics fixes
//
// Revision 1.69  2002/05/01 21:14:59  jbravo
// Misc fixes
//
// Revision 1.68  2002/04/26 05:29:38  niceass
// PHYSICS, Take 2
//
// Revision 1.67  2002/04/20 15:03:47  makro
// More footstep sounds, a few other things
//
// Revision 1.66  2002/04/06 21:42:20  makro
// Changes to bot code. New surfaceparm system.
//
// Revision 1.65  2002/03/31 03:31:24  jbravo
// Compiler warning cleanups
//
// Revision 1.64  2002/03/27 17:20:38  jbravo
// Workaround to the bandage bug :)
//
// Revision 1.63  2002/03/23 05:17:42  jbravo
// Major cleanup of game -> cgame communication with LCA vars.
//
// Revision 1.62  2002/03/18 19:18:39  slicer
// Fixed bandage bugs ( i hope )
//
// Revision 1.61  2002/03/11 01:45:46  jbravo
// Bye bye backflips! :)
//
// Revision 1.60  2002/03/11 01:29:54  slicer
// Fixed Sniper zooming during LCA
//
// Revision 1.59  2002/03/02 22:02:09  niceass
// mk23 and akimbo last fire animation fixed
//
// Revision 1.58  2002/03/02 08:03:14  niceass
// look down movement bug fixed
//
// Revision 1.57  2002/02/27 01:54:28  jbravo
// More spectatorfixes and finally stopped all fallingdamage anims and
// sounds during LCA.
//
// Revision 1.56  2002/02/04 00:30:35  niceass
// New physics
//
// Revision 1.55  2002/01/24 14:20:53  jbravo
// Adding func_explosive and a few new surfaceparms
//
// Revision 1.54  2002/01/11 20:20:58  jbravo
// Adding TP to main branch
//
// Revision 1.53  2002/01/11 19:48:29  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.52  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
// bg_pmove.c -- both games player movement code
// takes a playerstate and a usercmd as input and returns a modifed playerstate

#include "../qcommon/q_shared.h"
#include "bg_public.h"
#include "bg_local.h"

pmove_t *pm;
pml_t pml;

//Elder: reduce x-y speed on ladders by this factor so it 'feels' more like Q2
#define PM_LADDER_MOVE_REDUCTION	10

#define STOP_EPSILON 0.1f
//#define Q2PHYSICS

// movement parameters
float pm_stopspeed = 100.0f;
float pm_duckScale = 0.25f;
float pm_swimScale = 0.50f;
float pm_ladderScale = 0.75f;	// more c3a ladders
float pm_maxspeed = 300;

float pm_accelerate = 10.0f;
float pm_airaccelerate = 1.0f;
float pm_wateraccelerate = 4.0f;
float pm_flyaccelerate = 8.0f;
float pm_ladderAccelerate = 3000;	// same as ladder friction.

float pm_friction = 6.0f;
float pm_waterfriction = 1.0f;
float pm_flightfriction = 3.0f;
float pm_spectatorfriction = 5.0f;
float pm_ladderfriction = 3000;

int c_pmove = 0;

/* [QUARANTINE] - Weapon Animations
===================
PM_StartWeaponAnim, PM_ContinueWeaponAnim
===================
*/
static void PM_StartWeaponAnim(int anim)
{
	if (pm->ps->pm_type >= PM_DEAD) {
		return;
	}

	// NiceAss: Don't do client prediction of weapon animations
	/*if ( !pm->predict && (anim == WP_ANIM_FIRE || anim == WP_ANIM_IDLE || 
		anim == WP_ANIM_EXTRA1 || anim == WP_ANIM_THROWFIRE ) )
		return;*/

	pm->ps->generic1 = ((pm->ps->generic1 & ANIM_TOGGLEBIT) ^ ANIM_TOGGLEBIT) | anim;
}

static void PM_ContinueWeaponAnim(int anim)
{
	if ((pm->ps->generic1 & ~ANIM_TOGGLEBIT) == anim) {
		return;
	}

	// NiceAss: Don't do client prediction of weapon animations
	/*
	if ( !pm->predict && (anim == WP_ANIM_FIRE || anim == WP_ANIM_IDLE || 
		anim == WP_ANIM_EXTRA1 || anim == WP_ANIM_THROWFIRE ) )
		return;*/

	PM_StartWeaponAnim(anim);
}

// END

/*
===============
PM_AddEvent

===============
*/
void PM_AddEvent(int newEvent)
{
	BG_AddPredictableEventToPlayerstate(newEvent, 0, pm->ps);
}

/*
===============
PM_AddEvent

Elder: stuffs event parameters
Be careful because you are stuffing the player
===============
*/
void PM_AddEvent2(int newEvent, int eventParm)
{
	BG_AddPredictableEventToPlayerstate(newEvent, eventParm, pm->ps);
}

/*
===============
PM_AddTouchEnt
===============
*/
void PM_AddTouchEnt(int entityNum)
{
	int i;

	if (entityNum == ENTITYNUM_WORLD) {
		return;
	}
	if (pm->numtouch == MAXTOUCH) {
		return;
	}
	// see if it is already added
	for (i = 0; i < pm->numtouch; i++) {
		if (pm->touchents[i] == entityNum) {
			return;
		}
	}

	// add it
	pm->touchents[pm->numtouch] = entityNum;
	pm->numtouch++;
}

/*
===================
PM_StartTorsoAnim
===================
*/
static void PM_StartTorsoAnim(int anim)
{
	if (pm->ps->pm_type >= PM_DEAD) {
		return;
	}
	pm->ps->torsoAnim = ((pm->ps->torsoAnim & ANIM_TOGGLEBIT) ^ ANIM_TOGGLEBIT)
	    | anim;
}
static void PM_StartLegsAnim(int anim)
{
	if (pm->ps->pm_type >= PM_DEAD) {
		return;
	}
	if (pm->ps->legsTimer > 0) {
		return;		// a high priority animation is running
	}
	pm->ps->legsAnim = ((pm->ps->legsAnim & ANIM_TOGGLEBIT) ^ ANIM_TOGGLEBIT)
	    | anim;
}

static void PM_ContinueLegsAnim(int anim)
{
	if ((pm->ps->legsAnim & ~ANIM_TOGGLEBIT) == anim) {
		return;
	}
	if (pm->ps->legsTimer > 0) {
		return;		// a high priority animation is running
	}
	PM_StartLegsAnim(anim);
}

static void PM_ContinueTorsoAnim(int anim)
{
	if ((pm->ps->torsoAnim & ~ANIM_TOGGLEBIT) == anim) {
		return;
	}
	if (pm->ps->torsoTimer > 0) {
		return;		// a high priority animation is running
	}
	PM_StartTorsoAnim(anim);
}

static void PM_ForceLegsAnim(int anim)
{
	pm->ps->legsTimer = 0;
	PM_StartLegsAnim(anim);
}

/*
==================
PM_ClipVelocity

Slide off of the impacting surface
==================
*/
void PM_ClipVelocity(vec3_t in, vec3_t normal, vec3_t out, float overbounce)
{
	float backoff;
	float change;
	int i;

#ifdef Q2PHYSICS
	backoff = DotProduct(in, normal) * overbounce;

	for (i = 0; i < 3; i++) {
		change = normal[i] * backoff;
		out[i] = in[i] - change;
		if ( out[i] > -STOP_EPSILON && out[i] < STOP_EPSILON)
			out[i] = 0;
	}
#else
	backoff = DotProduct(in, normal);

	if (backoff < 0) {
		backoff *= overbounce;
	} else {
		backoff /= overbounce;
	}

	for (i = 0; i < 3; i++) {
		change = normal[i] * backoff;
		out[i] = in[i] - change;
	}
#endif
}

/*
==================
PM_Friction

Handles both ground friction and water friction
==================
*/
static void PM_Friction(void)
{
	vec3_t vec;
	float *vel;
	float speed, newspeed, control;
	float drop;

	vel = pm->ps->velocity;

	VectorCopy(vel, vec);
	/*if ( pml.walking ) {
	   vec[2] = 0;  // ignore slope movement
	   } */

	speed = VectorLength(vec);
	if (speed < 1) {
		vel[0] = 0;
		vel[1] = 0;	// allow sinking underwater
		// FIXME: still have z friction underwater?
		return;
	}

	drop = 0;

	// apply ground friction
	if (pm->waterlevel <= 1) {
		if (pml.walking && !(pml.groundTrace.surfaceFlags & SURF_SLICK) && pm->ps->groundEntityNum) {
			// if getting knocked back, no friction
			if (!(pm->ps->pm_flags & PMF_TIME_KNOCKBACK)) {
				control = speed < pm_stopspeed ? pm_stopspeed : speed;
				drop += control * pm_friction * pml.frametime;
			}
		}
	}
	// apply water friction even if just wading
	if (pm->waterlevel) {
		drop += speed * pm_waterfriction * pm->waterlevel * pml.frametime;
	}

	if (pml.ladder)		// If they're on a ladder...
	{
		drop += speed * pm_ladderfriction * pml.frametime;	// Add ladder friction!
	}

	if (pm->ps->pm_type == PM_SPECTATOR) {
		drop += speed * pm_spectatorfriction * pml.frametime;
	}
	// scale the velocity
	newspeed = speed - drop;
	if (newspeed < 0) {
		newspeed = 0;
	}
	newspeed /= speed;

	vel[0] = vel[0] * newspeed;
	vel[1] = vel[1] * newspeed;
	vel[2] = vel[2] * newspeed;
}

/*
==============
PM_Accelerate

Handles user intended acceleration
==============
*/
static void PM_Accelerate(vec3_t wishdir, float wishspeed, float accel)
{
	int i;
	float addspeed, accelspeed, currentspeed;

	currentspeed = DotProduct(pm->ps->velocity, wishdir);
	addspeed = wishspeed - currentspeed;
	if (addspeed <= 0) {
		return;
	}
	accelspeed = accel * pml.frametime * wishspeed;
	if (accelspeed > addspeed) {
		accelspeed = addspeed;
	}

	for (i = 0; i < 3; i++) {
		pm->ps->velocity[i] += accelspeed * wishdir[i];
	}
}

/*
============
PM_CmdScale

Returns the scale factor to apply to cmd movements
This allows the clients to use axial -127 to 127 values for all directions
without getting a sqrt(2) distortion in speed.
============
*/
static float PM_CmdScale(usercmd_t * cmd)
{
	int max;
	float total;
	float scale;

	max = abs(cmd->forwardmove);
	if (abs(cmd->rightmove) > max) {
		max = abs(cmd->rightmove);
	}
	if (abs(cmd->upmove) > max) {
		max = abs(cmd->upmove);
	}
	if (!max) {
		return 0;
	}

	total = sqrt(cmd->forwardmove * cmd->forwardmove + cmd->rightmove * cmd->rightmove + cmd->upmove * cmd->upmove);
	scale = (float) pm->ps->speed * max / (127.0 * total);

	return scale;
}

/*
================
PM_SetMovementDir

Determine the rotation of the legs reletive
to the facing dir
================
*/
static void PM_SetMovementDir(void)
{
	if (pm->cmd.forwardmove || pm->cmd.rightmove) {
		if (pm->cmd.rightmove == 0 && pm->cmd.forwardmove > 0) {
			pm->ps->movementDir = 0;
		} else if (pm->cmd.rightmove < 0 && pm->cmd.forwardmove > 0) {
			pm->ps->movementDir = 1;
		} else if (pm->cmd.rightmove < 0 && pm->cmd.forwardmove == 0) {
			pm->ps->movementDir = 2;
		} else if (pm->cmd.rightmove < 0 && pm->cmd.forwardmove < 0) {
			pm->ps->movementDir = 3;
		} else if (pm->cmd.rightmove == 0 && pm->cmd.forwardmove < 0) {
			pm->ps->movementDir = 4;
		} else if (pm->cmd.rightmove > 0 && pm->cmd.forwardmove < 0) {
			pm->ps->movementDir = 5;
		} else if (pm->cmd.rightmove > 0 && pm->cmd.forwardmove == 0) {
			pm->ps->movementDir = 6;
		} else if (pm->cmd.rightmove > 0 && pm->cmd.forwardmove > 0) {
			pm->ps->movementDir = 7;
		}
	} else {
		// if they aren't actively going directly sideways,
		// change the animation to the diagonal so they
		// don't stop too crooked
		if (pm->ps->movementDir == 2) {
			pm->ps->movementDir = 1;
		} else if (pm->ps->movementDir == 6) {
			pm->ps->movementDir = 7;
		}
	}
}

/*
=============
PM_CheckJump
=============
*/
static qboolean PM_CheckJump(void)
{
	if (pm->ps->pm_flags & PMF_RESPAWNED) {
		return qfalse;	// don't allow jump until all buttons are up
	}

	if (pm->cmd.upmove < 10) {
		// not holding jump
		return qfalse;
	}
	// must wait for jump to be released
	if (pm->ps->pm_flags & PMF_JUMP_HELD) {
		// clear upmove so cmdscale doesn't lower running speed
		pm->cmd.upmove = 0;
		return qfalse;
	}

	if (!pml.groundPlane && !pml.walking)
		return qfalse;

	if (pm->debugLevel) {
		Com_Printf("%i:jump\n", c_pmove);
	}

	pml.groundPlane = qfalse;	// jumping away
	pml.walking = qfalse;
	pm->ps->pm_flags |= PMF_JUMP_HELD;

	pm->ps->groundEntityNum = ENTITYNUM_NONE;
	pm->ps->velocity[2] += JUMP_VELOCITY;

	if (pm->ps->velocity[2] < JUMP_VELOCITY)
		pm->ps->velocity[2] = JUMP_VELOCITY;

	PM_AddEvent(EV_JUMP);

	PM_ForceLegsAnim(LEGS_JUMP);
	pm->ps->pm_flags &= ~PMF_BACKWARDS_JUMP;

	return qtrue;
}

/*
=============
PM_CheckWaterJump
=============
*/
static qboolean PM_CheckWaterJump(void)
{
	vec3_t spot;
	int cont;
	vec3_t flatforward;

	if (pm->ps->pm_time) {
		return qfalse;
	}
	// check for water jump
	if (pm->waterlevel != 2) {
		return qfalse;
	}

	flatforward[0] = pml.forward[0];
	flatforward[1] = pml.forward[1];
	flatforward[2] = 0;
	VectorNormalize(flatforward);

	VectorMA(pm->ps->origin, 30, flatforward, spot);
	spot[2] += 4;
	cont = pm->pointcontents(spot, pm->ps->clientNum);
	if (!(cont & CONTENTS_SOLID)) {
		return qfalse;
	}

	spot[2] += 16;
	cont = pm->pointcontents(spot, pm->ps->clientNum);
	if (cont) {
		return qfalse;
	}
	// jump out of water
	VectorScale(pml.forward, 200, pm->ps->velocity);
	pm->ps->velocity[2] = 350;

	pm->ps->pm_flags |= PMF_TIME_WATERJUMP;
	pm->ps->pm_time = 2000;

	return qtrue;
}

//============================================================================

/*
===================
PM_WaterJumpMove

Flying out of the water
===================
*/
static void PM_WaterJumpMove(void)
{
	// waterjump has no control, but falls
#ifdef Q2PHYSICS
	Q2_PM_StepSlideMove(qtrue);
#else
	PM_StepSlideMove(qtrue);
#endif

	pm->ps->velocity[2] -= pm->ps->gravity * pml.frametime;
	if (pm->ps->velocity[2] < 0) {
		// cancel as soon as we are falling down again
		pm->ps->pm_flags &= ~PMF_ALL_TIMES;
		pm->ps->pm_time = 0;
	}
}

/*
===================
PM_WaterMove

===================
*/
static void PM_WaterMove(void)
{
	int i;
	vec3_t wishvel;
	float wishspeed;
	vec3_t wishdir;
	float scale;
	float vel;

	if (PM_CheckWaterJump()) {
		PM_WaterJumpMove();
		return;
	}

	PM_Friction();

	scale = PM_CmdScale(&pm->cmd);
	//
	// user intentions
	//
	if (!scale) {
		wishvel[0] = 0;
		wishvel[1] = 0;
		wishvel[2] = -60;	// sink towards bottom
	} else {
		for (i = 0; i < 3; i++)
			wishvel[i] =
			    scale * pml.forward[i] * pm->cmd.forwardmove + scale * pml.right[i] * pm->cmd.rightmove;

		wishvel[2] += scale * pm->cmd.upmove;
	}

	VectorCopy(wishvel, wishdir);
	wishspeed = VectorNormalize(wishdir);

	if (wishspeed > pm->ps->speed * pm_swimScale) {
		wishspeed = pm->ps->speed * pm_swimScale;
	}

	PM_Accelerate(wishdir, wishspeed, pm_wateraccelerate);

	// make sure we can go up slopes easily under water
	if (pml.groundPlane && DotProduct(pm->ps->velocity, pml.groundTrace.plane.normal) < 0) {
		vel = VectorLength(pm->ps->velocity);
		// slide along the ground plane
		PM_ClipVelocity(pm->ps->velocity, pml.groundTrace.plane.normal, pm->ps->velocity, OVERCLIP);

		VectorNormalize(pm->ps->velocity);
		VectorScale(pm->ps->velocity, vel, pm->ps->velocity);
	}
#ifdef Q2PHYSICS
	Q2_PM_StepSlideMove(qfalse);
#else
	PM_StepSlideMove(qfalse);
#endif
}

/*
===================
PM_FlyMove

Only with the flight powerup
===================
*/
static void PM_FlyMove(void)
{
	int i;
	vec3_t wishvel;
	float wishspeed;
	vec3_t wishdir;
	float scale;

	// normal slowdown
	PM_Friction();

	scale = PM_CmdScale(&pm->cmd);
	//
	// user intentions
	//
	if (!scale) {
		wishvel[0] = 0;
		wishvel[1] = 0;
		wishvel[2] = 0;
	} else {
		for (i = 0; i < 3; i++) {
			wishvel[i] =
			    scale * pml.forward[i] * pm->cmd.forwardmove + scale * pml.right[i] * pm->cmd.rightmove;
		}

		wishvel[2] += scale * pm->cmd.upmove;
	}

	VectorCopy(wishvel, wishdir);
	wishspeed = VectorNormalize(wishdir);

	PM_Accelerate(wishdir, wishspeed, pm_flyaccelerate);

#ifdef Q2PHYSICS
	Q2_PM_StepSlideMove(qfalse);
#else
	PM_StepSlideMove(qfalse);
#endif
}

/*
===================
PM_AirMove

===================
*/
static void PM_AirMove(void)
{
	int i;
	vec3_t wishvel;
	float fmove, smove;
	vec3_t wishdir;
	float wishspeed;
	float scale;
	usercmd_t cmd;

	PM_CheckJump();
	PM_Friction();

	fmove = pm->cmd.forwardmove;
	smove = pm->cmd.rightmove;

	cmd = pm->cmd;
	scale = PM_CmdScale(&cmd);

	// set the movementDir so clients can rotate the legs for strafing
	PM_SetMovementDir();

	// project moves down to flat plane

	pml.forward[2] = 0;
	pml.right[2] = 0;
	VectorNormalize(pml.forward);
	VectorNormalize(pml.right);

	for (i = 0; i < 2; i++) {
		wishvel[i] = pml.forward[i] * fmove * scale + pml.right[i] * smove * scale;
	}
	wishvel[2] = 0;

	VectorCopy(wishvel, wishdir);
	wishspeed = VectorNormalize(wishdir);
	//wishspeed *= scale;

	// not on ground, so little effect on velocity
	PM_Accelerate(wishdir, wishspeed, pm_airaccelerate);

	// we may have a ground plane that is very steep, even
	// though we don't have a groundentity
	// slide along the steep plane
	/*if ( pml.groundPlane ) {
	   PM_ClipVelocity (pm->ps->velocity, pml.groundTrace.plane.normal, 
	   pm->ps->velocity, OVERCLIP );
	   }
	 */
#ifdef Q2PHYSICS
	Q2_PM_StepSlideMove(qtrue);
#else
	PM_StepSlideMove(qtrue);
#endif
}

/*
===================
PM_GrappleMove

===================
*/
static void PM_GrappleMove(void)
{
	vec3_t vel, v;
	float vlen;

	VectorScale(pml.forward, -16, v);
	VectorAdd(pm->ps->grapplePoint, v, v);
	VectorSubtract(v, pm->ps->origin, vel);
	vlen = VectorLength(vel);
	VectorNormalize(vel);

	if (vlen <= 100)
		VectorScale(vel, 10 * vlen, vel);
	else
		VectorScale(vel, 800, vel);

	VectorCopy(vel, pm->ps->velocity);

	pml.groundPlane = qfalse;
}

/*
===================
PM_WalkMove

===================
*/
static void PM_WalkMove(void)
{
	int i;
	vec3_t wishvel;
	float fmove, smove;
	vec3_t wishdir;
	float wishspeed;
	float scale;
	usercmd_t cmd;
	float accelerate;

	if (pm->waterlevel > 2 && DotProduct(pml.forward, pml.groundTrace.plane.normal) > 0) {
		// begin swimming
		PM_WaterMove();
		return;
	}
	//Blaze: Cant jump while someone has leg damage
	if (!((pm->ps->stats[STAT_RQ3] & RQ3_LEGDAMAGE) == RQ3_LEGDAMAGE) && PM_CheckJump()) {
		// jumped away
		if (pm->waterlevel > 1) {
			PM_WaterMove();
		} else {
			PM_AirMove();
		}
		return;
	}

	PM_Friction();

	fmove = pm->cmd.forwardmove;
	smove = pm->cmd.rightmove;

	cmd = pm->cmd;
	scale = PM_CmdScale(&cmd);

	// set the movementDir so clients can rotate the legs for strafing
	PM_SetMovementDir();

	// project the forward and right directions onto the ground plane
	pml.forward[2] = 0;
	pml.right[2] = 0;
	

	//Blaze - july 10, 2009
	//The following two functions will lower your X/Y velocities depending on the plane you are walking on.
	//As they are now(commented out), you will stay at the same speed walking up a ramp
	//
	//PM_ClipVelocity(pml.forward, pml.groundTrace.plane.normal, pml.forward, OVERCLIP);
	//PM_ClipVelocity(pml.right, pml.groundTrace.plane.normal, pml.right, OVERCLIP);

	VectorNormalize(pml.forward);
	VectorNormalize(pml.right);

	for (i = 0; i < 3; i++) {
		wishvel[i] = pml.forward[i] * fmove + pml.right[i] * smove;
	}
	// when going up or down slopes the wish velocity should Not be zero
	// wishvel[2] = 0;

	VectorCopy(wishvel, wishdir);
	wishspeed = VectorNormalize(wishdir);
	wishspeed *= scale;

	// clamp the speed lower if ducking
	if (pm->ps->pm_flags & PMF_DUCKED) {
		if (wishspeed > pm->ps->speed * pm_duckScale) {
			wishspeed = pm->ps->speed * pm_duckScale;
		}
	}
	// clamp the speed lower if wading or walking on the bottom
	if (pm->waterlevel) {
		float waterScale;

		waterScale = pm->waterlevel / 3.0;
		waterScale = 1.0 - (1.0 - pm_swimScale) * waterScale;
		if (wishspeed > pm->ps->speed * waterScale) {
			wishspeed = pm->ps->speed * waterScale;
		}
	}
	// when a player gets hit, they temporarily lose
	// full control, which allows them to be moved a bit
	if ((pml.groundTrace.surfaceFlags & SURF_SLICK) || pm->ps->pm_flags & PMF_TIME_KNOCKBACK) {
		accelerate = pm_airaccelerate;
	} else {
		accelerate = pm_accelerate;
	}

	PM_Accelerate(wishdir, wishspeed, accelerate);

	if (pm->ps->velocity[2] < 0)
		pm->ps->velocity[2] = 0;


	if ((pml.groundTrace.surfaceFlags & SURF_SLICK) || pm->ps->pm_flags & PMF_TIME_KNOCKBACK) {
		pm->ps->velocity[2] -= pm->ps->gravity * pml.frametime;
	}

	// don't do anything if standing still
	if (!pm->ps->velocity[0] && !pm->ps->velocity[1]) {
		return;
	}
#ifdef Q2PHYSICS
	Q2_PM_StepSlideMove(qfalse);
#else
	PM_StepSlideMove(qfalse);
#endif

}

/*
==============
PM_DeadMove
==============
*/
static void PM_DeadMove(void)
{
	float forward;

	if (!pml.walking) {
		return;
	}
	// extra friction

	forward = VectorLength(pm->ps->velocity);
	forward -= 20;
	if (forward <= 0) {
		VectorClear(pm->ps->velocity);
	} else {
		VectorNormalize(pm->ps->velocity);
		VectorScale(pm->ps->velocity, forward, pm->ps->velocity);
	}
}

/*
===============
PM_NoclipMove
===============
*/
static void PM_NoclipMove(void)
{
	float speed, drop, friction, control, newspeed;
	int i;
	vec3_t wishvel;
	float fmove, smove;
	vec3_t wishdir;
	float wishspeed;
	float scale;

	pm->ps->viewheight = DEFAULT_VIEWHEIGHT;

	// friction

	speed = VectorLength(pm->ps->velocity);
	if (speed < 1) {
		VectorCopy(vec3_origin, pm->ps->velocity);
	} else {
		drop = 0;

		friction = pm_friction * 1.5;	// extra friction
		control = speed < pm_stopspeed ? pm_stopspeed : speed;
		drop += control * friction * pml.frametime;

		// scale the velocity
		newspeed = speed - drop;
		if (newspeed < 0)
			newspeed = 0;
		newspeed /= speed;

		VectorScale(pm->ps->velocity, newspeed, pm->ps->velocity);
	}

	// accelerate
	scale = PM_CmdScale(&pm->cmd);

	fmove = pm->cmd.forwardmove;
	smove = pm->cmd.rightmove;

	for (i = 0; i < 3; i++)
		wishvel[i] = pml.forward[i] * fmove + pml.right[i] * smove;
	wishvel[2] += pm->cmd.upmove;

	VectorCopy(wishvel, wishdir);
	wishspeed = VectorNormalize(wishdir);
	wishspeed *= scale;

	PM_Accelerate(wishdir, wishspeed, pm_accelerate);

	// move
	VectorMA(pm->ps->origin, pml.frametime, pm->ps->velocity, pm->ps->origin);
}

//============================================================================

/*
================
PM_FootstepForSurface

Returns an event number apropriate for the groundsurface
Makro - changed prototype so that we can use it for other surfaces, too
(ladder footsteps)
================
*/
static int PM_FootstepForSurface(int surfaceFlags)
{
	int Material = GetMaterialFromFlag(surfaceFlags);

	//Makro: quick note: surfaceparm nosteps will cause footstep sounds
	//NOT to be played, UNLESS surfaceparm ladder is also set.
	//Pretty weird, I know, but that how they wanted it...
	
	qboolean bLadder = (pml.groundTrace.surfaceFlags & SURF_LADDER)!=0;
	qboolean bNoSteps = (pml.groundTrace.surfaceFlags & SURF_NOSTEPS)!=0;

	//2007-07-31: getting rid of ladder footsteps

	//if ((bLadder ^ bNoSteps) != 0) {
	if (bNoSteps || bLadder) {
		return 0;
	}

	//Makro - new surfaceparm system
	//if ( pml.groundTrace.surfaceFlags & SURF_METALSTEPS ) {
	if (Material == MAT_METALSTEPS) {
		return EV_FOOTSTEP_METAL;
	}
	//Elder: added for footstep support
	//if ( pml.groundTrace.surfaceFlags & SURF_GRASS ) {
	if (Material == MAT_GRASS) {
		return EV_FOOTSTEP_GRASS;
	}
// JBravo: re-enables Gravel.
	//Makro - new surfaceparm system
	//if ( pml.groundTrace.surfaceFlags & SURF_GRAVEL ) {
	if (Material == MAT_GRAVEL) {
		return EV_FOOTSTEP_GRAVEL;
	}
	//if ( pml.groundTrace.surfaceFlags & SURF_WOOD ) {
	if (Material == MAT_WOOD) {
		return EV_FOOTSTEP_WOOD;
	}
	//if ( pml.groundTrace.surfaceFlags & SURF_CARPET ) {
	if (Material == MAT_CARPET) {
		return EV_FOOTSTEP_CARPET;
	}
	//if ( pml.groundTrace.surfaceFlags & SURF_METAL2 ) {
	if (Material == MAT_METAL2) {
		return EV_FOOTSTEP_METAL2;
	}
// JBravo: Begin adding new sounds
	//Makro - new surfaceparm system
	//if ( pml.groundTrace.surfaceFlags & SURF_SNOW ) {
	if (Material == MAT_SNOW) {
		return EV_FOOTSTEP_SNOW;
	}
	//if ( pml.groundTrace.surfaceFlags & SURF_MUD ) {
	if (Material == MAT_MUD) {
		return EV_FOOTSTEP_MUD;
	}
	//if ( pml.groundTrace.surfaceFlags & SURF_WOOD2 ) {
	if (Material == MAT_WOOD2) {
		return EV_FOOTSTEP_WOOD2;
	}
	//if ( pml.groundTrace.surfaceFlags & SURF_HARDMETAL ) {
	if (Material == MAT_HARDMETAL) {
		return EV_FOOTSTEP_HARDMETAL;
	}
// JBravo: end adding new sounds
// Makro - 5 new sounds
	if (Material == MAT_LEAVES) {
		return EV_FOOTSTEP_LEAVES;
	}

	if (Material == MAT_CEMENT) {
		return EV_FOOTSTEP_CEMENT;
	}

	if (Material == MAT_MARBLE) {
		return EV_FOOTSTEP_MARBLE;
	}

	if (Material == MAT_SNOW2) {
		return EV_FOOTSTEP_SNOW2;
	}

	if (Material == MAT_HARDSTEPS) {
		return EV_FOOTSTEP_HARDSTEPS;
	}

	if (Material == MAT_SAND) {
		return EV_FOOTSTEP_SAND;
	}
// Makro - end new sounds

	return EV_FOOTSTEP;
}

/*
=================
PM_CrashLand

Check for hard landings that generate sound events
=================
*/
static void PM_CrashLand(void)
{
	float delta;

	//float         dist;
	//float         vel, acc;
	//float         t;
	//float         a, b, c, den;
	int damage;

	// JBravo: no falling at all during LCA in Teamplay
	if (pm->lca) {
		return;
	}

	PM_ForceLegsAnim(LEGS_LAND);

	// Elder: 300/320 factor included
	delta = 0.9375f * (pm->ps->velocity[2] - pml.previous_velocity[2]);
	delta = delta * delta * 0.0001;

	// never take falling damage if completely underwater
	if (pm->waterlevel == 3) {
		return;
	}
	// reduce falling damage if there is standing water
	if (pm->waterlevel == 2) {
		delta *= 0.25;
	}
	if (pm->waterlevel == 1) {
		delta *= 0.5;
	}

	if (delta < 1) {
		return;
	}

	if (delta > 30) {
		damage = (int) (((delta - 30) / 2));
		if (damage < 1)
			damage = 1;
		damage *= 10;

		if (!(pml.groundTrace.surfaceFlags & SURF_NODAMAGE)) {
			//Blaze lots of changes to make it more like aq2
			// this is a pain grunt, so don't play it if dead
			if (pm->ps->stats[STAT_HEALTH] > 0 && damage > 0) {
				// JBravo: new multiple itemcode
				if (pm->ps->stats[STAT_HOLDABLE_ITEM] & (1 << HI_SLIPPERS))
					PM_AddEvent(EV_FALL_FAR_NOSOUND);
				else
					PM_AddEvent(EV_FALL_FAR);

				pm->ps->stats[STAT_FALLDAMAGE] = damage;
			} else {
				PM_AddEvent(PM_FootstepForSurface(pml.groundTrace.surfaceFlags));
				//Elder: added? useful?
				pm->ps->stats[STAT_FALLDAMAGE] = 0;
			}
		}
	} else if (delta > 20) {
		// JBravo: new multiple itemcode
		if (pm->ps->stats[STAT_HOLDABLE_ITEM] & (1 << HI_SLIPPERS)) {
			PM_AddEvent(EV_FALL_SHORT_NOSOUND);
			//Elder: added? useful?
			pm->ps->stats[STAT_FALLDAMAGE] = 0;
		} else {
			PM_AddEvent(EV_FALL_SHORT);
			//Elder: added? useful?
			pm->ps->stats[STAT_FALLDAMAGE] = 0;
		}
		// JBravo: new multiple itemcode
	} else if (!(pm->ps->stats[STAT_HOLDABLE_ITEM] & (1 << HI_SLIPPERS))) {
		// Elder: don't spam sound events going up -- more like Q2 ladders as well
		//Makro - ladder footsteps are handled in PM_LadderMove, chaging || to &&
		if (!pml.ladder && pm->ps->velocity[2] < 0)
			PM_AddEvent(PM_FootstepForSurface(pml.groundTrace.surfaceFlags));
		//Elder: added? useful?
		pm->ps->stats[STAT_FALLDAMAGE] = 0;
	}
	// start footstep cycle over
	pm->ps->bobCycle = 0;
}

/*
=============
PM_CorrectAllSolid
=============
*/
static int PM_CorrectAllSolid(trace_t * trace)
{
	int i, j, k;
	vec3_t point;

	if (pm->debugLevel) {
		Com_Printf("%i:allsolid\n", c_pmove);
	}
	// jitter around
	for (i = -1; i <= 1; i++) {
		for (j = -1; j <= 1; j++) {
			for (k = -1; k <= 1; k++) {
				VectorCopy(pm->ps->origin, point);
				point[0] += (float) i;
				point[1] += (float) j;
				point[2] += (float) k;
				pm->trace(trace, point, pm->mins, pm->maxs, point, pm->ps->clientNum, pm->tracemask);
				if (!trace->allsolid) {
					point[0] = pm->ps->origin[0];
					point[1] = pm->ps->origin[1];
					point[2] = pm->ps->origin[2] - 0.25;

					pm->trace(trace, pm->ps->origin, pm->mins, pm->maxs, point, pm->ps->clientNum,
						  pm->tracemask);
					pml.groundTrace = *trace;
					return qtrue;
				}
			}
		}
	}

	pm->ps->groundEntityNum = ENTITYNUM_NONE;
	pml.groundPlane = qfalse;
	pml.walking = qfalse;

	return qfalse;
}

/*
=============
PM_GroundTraceMissed

The ground trace didn't hit a surface, so we are in freefall
=============
*/
static void PM_GroundTraceMissed(void)
{
	trace_t trace;
	vec3_t point;

	if (pm->ps->groundEntityNum != ENTITYNUM_NONE) {
		// we just transitioned into freefall
		if (pm->debugLevel) {
			Com_Printf("%i:lift\n", c_pmove);
		}
		// if they aren't in a jumping animation and the ground is a ways away, force into it
		// if we didn't do the trace, the player would be backflipping down staircases
		VectorCopy(pm->ps->origin, point);
		point[2] -= 64;

		pm->trace(&trace, pm->ps->origin, pm->mins, pm->maxs, point, pm->ps->clientNum, pm->tracemask);
		if (trace.fraction == 1.0) {
			PM_ForceLegsAnim(LEGS_JUMP);
			pm->ps->pm_flags &= ~PMF_BACKWARDS_JUMP;
		}
	}

	pm->ps->groundEntityNum = ENTITYNUM_NONE;
	pml.groundPlane = qfalse;
	pml.walking = qfalse;
}

/*
=============
PM_GroundTrace
=============
*/
static void PM_GroundTrace(void)
{
	vec3_t point;
	trace_t trace;

	point[0] = pm->ps->origin[0];
	point[1] = pm->ps->origin[1];
	point[2] = pm->ps->origin[2] - 0.25;

	pm->trace(&trace, pm->ps->origin, pm->mins, pm->maxs, point, pm->ps->clientNum, pm->tracemask);
	pml.groundTrace = trace;

	// do something corrective if the trace starts in a solid...
	if (trace.allsolid) {
		if (!PM_CorrectAllSolid(&trace))
			return;
	}
	// if the trace didn't hit anything and not on ladder, we are in free fall 
	if (trace.fraction == 1.0 && !pml.ladder) {
		PM_GroundTraceMissed();
		pml.groundPlane = qfalse;
		pml.walking = qfalse;
		return;
	}

	// check if getting thrown off the ground
	/*
	   // NiceAss: Comment out and you get double jumping =D
	   if ( pm->ps->velocity[2] > 0 && DotProduct( pm->ps->velocity, trace.plane.normal ) > 10 ) {
	   if ( pm->debugLevel ) {
	   Com_Printf("%i:kickoff\n", c_pmove);
	   }

	   // go into jump animation
	   PM_ForceLegsAnim( LEGS_JUMP );
	   pm->ps->pm_flags &= ~PMF_BACKWARDS_JUMP;

	   pm->ps->groundEntityNum = ENTITYNUM_NONE;
	   pml.groundPlane = qfalse;
	   pml.walking = qfalse;
	   return;
	   }
	 */

	if (pm->ps->velocity[2] > 180) {	// NiceAss: This is here for slope acceleration!
		if (pm->debugLevel) {
			Com_Printf("%i:slopeslide\n", c_pmove);
		}

		pml.groundPlane = qfalse;
		pm->ps->groundEntityNum = ENTITYNUM_NONE;
		pml.walking = qfalse;
		return;
	}
	
	// slopes that are too steep will not be considered onground
	// Elder: added ladder check
	if (trace.plane.normal[2] < MIN_WALK_NORMAL && !pml.ladder) {
		if (pm->debugLevel) {
			Com_Printf("%i:steep\n", c_pmove);
		}
		// FIXME: if they can't slide down the slope, let them
		// walk (sharp crevices)
		pm->ps->groundEntityNum = ENTITYNUM_NONE;
		pml.groundPlane = qfalse;	//qtrue;
		pml.walking = qfalse;
		return;
	}

	pml.groundPlane = qtrue;
	pml.walking = qtrue;

	// hitting solid ground will end a waterjump
	if (pm->ps->pm_flags & PMF_TIME_WATERJUMP) {
		pm->ps->pm_flags &= ~(PMF_TIME_WATERJUMP | PMF_TIME_LAND);
		pm->ps->pm_time = 0;
	}

	if (pm->ps->groundEntityNum == ENTITYNUM_NONE) {
		// just hit the ground
		if (pm->debugLevel) {
			Com_Printf("%i:Land\n", c_pmove);
		}

		PM_CrashLand();

		if (pml.ladder) {
			pml.groundPlane = qfalse;
			pml.walking = qfalse;
			return;
		}
		// don't do landing time if we were just going down a slope
		if (pml.previous_velocity[2] < -200) {
			// don't allow another jump for a little while
			pm->ps->pm_flags |= PMF_TIME_LAND;
			pm->ps->pm_time = 250;
		}
	}

	pm->ps->groundEntityNum = trace.entityNum;

	PM_AddTouchEnt(trace.entityNum);
}

/*
=============
PM_SetWaterLevel	FIXME: avoid this twice?  certainly if not moving
=============
*/
static void PM_SetWaterLevel(void)
{
	vec3_t point;
	int cont;
	int sample1;
	int sample2;

	//
	// get waterlevel, accounting for ducking
	//
	pm->waterlevel = 0;
	pm->watertype = 0;

	point[0] = pm->ps->origin[0];
	point[1] = pm->ps->origin[1];
	point[2] = pm->ps->origin[2] + MINS_Z + 1;
	cont = pm->pointcontents(point, pm->ps->clientNum);

	if (cont & MASK_WATER) {
		sample2 = pm->ps->viewheight - MINS_Z;
		sample1 = sample2 / 2;

		pm->watertype = cont;
		pm->waterlevel = 1;
		point[2] = pm->ps->origin[2] + MINS_Z + sample1;
		cont = pm->pointcontents(point, pm->ps->clientNum);
		if (cont & MASK_WATER) {
			pm->waterlevel = 2;
			point[2] = pm->ps->origin[2] + MINS_Z + sample2;
			cont = pm->pointcontents(point, pm->ps->clientNum);
			if (cont & MASK_WATER) {
				pm->waterlevel = 3;
			}
		}
	}

}

/*
==============
PM_CheckDuck

Sets mins, maxs, and pm->ps->viewheight
==============
*/
static void PM_CheckDuck(void)
{
	trace_t trace;
	vec3_t point;		// NiceAss: Added for FUNKY CODE ALERT section

	pm->mins[0] = -15;
	pm->mins[1] = -15;

	pm->maxs[0] = 15;
	pm->maxs[1] = 15;

	pm->mins[2] = MINS_Z;

	if (pm->ps->pm_type == PM_DEAD) {
		pm->maxs[2] = -8;
		pm->ps->viewheight = DEAD_VIEWHEIGHT;
		return;
	}
	// NiceAss: FUNKY CODE ALERT!
	// Check to see if there is ground below. No? then you can't duck...
	point[0] = pm->ps->origin[0];
	point[1] = pm->ps->origin[1];
	point[2] = pm->ps->origin[2] - 0.25;

	pm->trace(&trace, pm->ps->origin, pm->mins, pm->maxs, point, pm->ps->clientNum, pm->tracemask);

	if (trace.fraction == 1.0 && !pml.ladder && !(pm->ps->pm_flags & PMF_DUCKED)) {
		pm->maxs[2] = 32;
		pm->ps->viewheight = DEFAULT_VIEWHEIGHT;
		return;
	}
	// End of funky code alert

	if (pm->cmd.upmove < 0) {	// duck
		pm->ps->pm_flags |= PMF_DUCKED;
	} else {		// stand up if possible
		if (pm->ps->pm_flags & PMF_DUCKED) {
			// try to stand up
			pm->maxs[2] = 32;
			pm->trace(&trace, pm->ps->origin, pm->mins, pm->maxs, pm->ps->origin, pm->ps->clientNum,
				  pm->tracemask);
			if (!trace.allsolid)
				pm->ps->pm_flags &= ~PMF_DUCKED;
		}
	}

	if (pm->ps->pm_flags & PMF_DUCKED) {
		pm->maxs[2] = 16;
		pm->ps->viewheight = CROUCH_VIEWHEIGHT;
	} else {
		pm->maxs[2] = 32;
		pm->ps->viewheight = DEFAULT_VIEWHEIGHT;
	}

}

//===================================================================

/*
===============
PM_Footsteps
===============
*/
static void PM_Footsteps(void)
{
	float bobmove;
	int old;
	qboolean footstep;

	//
	// calculate speed and cycle to be used for
	// all cyclic walking effects
	//
	pm->xyspeed = sqrt(pm->ps->velocity[0] * pm->ps->velocity[0]
			   + pm->ps->velocity[1] * pm->ps->velocity[1]);

	if (pm->ps->groundEntityNum == ENTITYNUM_NONE) {
		// airborne leaves position in cycle intact, but doesn't advance
		if (pm->waterlevel > 1) {
			PM_ContinueLegsAnim(LEGS_SWIM);
		}
		return;
	}
	// if not trying to move
	//Makro - changed condition a bit
	//if (!pm->cmd.forwardmove && !pm->cmd.rightmove) {
	//	if (pm->xyspeed < 5) {
	if ( (!pm->cmd.forwardmove && !pm->cmd.rightmove) || pm->xyspeed < 5) {
		pm->ps->bobCycle = 0;	// start at beginning of cycle again
		if (pm->ps->pm_flags & PMF_DUCKED) {
			PM_ContinueLegsAnim(LEGS_IDLECR);
		} else {
			PM_ContinueLegsAnim(LEGS_IDLE);
		}
		return;
	}


	footstep = qfalse;

	if (pm->ps->pm_flags & PMF_DUCKED) {
		bobmove = 0.5;	// ducked characters bob much faster
		if (pm->ps->pm_flags & PMF_BACKWARDS_RUN) {
			PM_ContinueLegsAnim(LEGS_BACKCR);
		} else {
			PM_ContinueLegsAnim(LEGS_WALKCR);
		}
		// ducked characters never play footsteps
		/*
		   } else       if ( pm->ps->pm_flags & PMF_BACKWARDS_RUN ) {
		   if ( !( pm->cmd.buttons & BUTTON_WALKING ) ) {
		   bobmove = 0.4;       // faster speeds bob faster
		   footstep = qtrue;
		   } else {
		   bobmove = 0.3;
		   }
		   PM_ContinueLegsAnim( LEGS_BACK );
		 */
	} else {
		if (!(pm->cmd.buttons & BUTTON_WALKING)) {
			bobmove = 0.4f;	// faster speeds bob faster
			if (pm->ps->pm_flags & PMF_BACKWARDS_RUN) {
				PM_ContinueLegsAnim(LEGS_BACK);
			} else {
				PM_ContinueLegsAnim(LEGS_RUN);
			}
			footstep = qtrue;
		} else {
			bobmove = 0.3f;	// walking bobs slow
			if (pm->ps->pm_flags & PMF_BACKWARDS_RUN) {
				PM_ContinueLegsAnim(LEGS_BACKWALK);
			} else {
				PM_ContinueLegsAnim(LEGS_WALK);
			}
		}
	}

	// check for footstep / splash sounds
	old = pm->ps->bobCycle;
	pm->ps->bobCycle = (int) (old + bobmove * pml.msec) & 255;

	// if we just crossed a cycle boundary, play an apropriate footstep event
	if (((old + 64) ^ (pm->ps->bobCycle + 64)) & 128) {
		if (pm->waterlevel == 0) {
			//Elder: we can check for slippers here!
			// on ground will only play sounds if running
			if ((footstep && !pm->noFootsteps)
			// JBravo: new multiple itemcode
			    && !(pm->ps->stats[STAT_HOLDABLE_ITEM] & (1 << HI_SLIPPERS))) {
				PM_AddEvent(PM_FootstepForSurface(pml.groundTrace.surfaceFlags));
			}
		} else if (pm->waterlevel == 1) {
			// splashing
			PM_AddEvent(EV_FOOTSPLASH);
		} else if (pm->waterlevel == 2) {
			// wading / swimming at surface
			PM_AddEvent(EV_SWIM);
		} else if (pm->waterlevel == 3) {
			// no sound when completely underwater

		}
	}
}

/*
==============
PM_WaterEvents

Generate sound events for entering and leaving water
==============
*/
static void PM_WaterEvents(void)
{				// FIXME?
	//
	// if just entered a water volume, play a sound
	//
	if (!pml.previous_waterlevel && pm->waterlevel) {
		PM_AddEvent(EV_WATER_TOUCH);
	}
	//
	// if just completely exited a water volume, play a sound
	//
	if (pml.previous_waterlevel && !pm->waterlevel) {
		PM_AddEvent(EV_WATER_LEAVE);
	}
	//
	// check for head just going under water
	//
	if (pml.previous_waterlevel != 3 && pm->waterlevel == 3) {
		PM_AddEvent(EV_WATER_UNDER);
	}
	//
	// check for head just coming out of water
	//
	if (pml.previous_waterlevel == 3 && pm->waterlevel != 3) {
		PM_AddEvent(EV_WATER_CLEAR);
	}
}

/*
===============
PM_BeginWeaponChange
===============
*/
static void PM_BeginWeaponChange(int weapon)
{
	//G_Printf("CHANGING WEAP TO: %i\n", weapon);

	if (weapon <= WP_NONE || weapon >= WP_NUM_WEAPONS) {
		return;
	}

	if (!(pm->ps->stats[STAT_WEAPONS] & (1 << weapon))) {
		return;
	}

	if (pm->ps->weaponstate == WEAPON_DROPPING) {
		return;
	}

	PM_AddEvent(EV_CHANGE_WEAPON);

	//Elder: ignore disarm delays when throwing a weapon
	if (pm->ps->stats[STAT_RQ3] & RQ3_THROWWEAPON) {
		pm->ps->stats[STAT_RQ3] &= ~RQ3_THROWWEAPON;
		pm->ps->weaponTime = 0;
	} else {
		//pm->ps->weaponTime += 200;
		//Elder: dependent time for each weapon
		switch (pm->ps->weapon) {
		case WP_PISTOL:
			pm->ps->weaponTime += RQ3_PISTOL_DISARM_DELAY;
			break;
		case WP_M3:
			pm->ps->weaponTime += RQ3_M3_DISARM_DELAY;
			break;
		case WP_M4:
			pm->ps->weaponTime += RQ3_M4_DISARM_DELAY;
			break;
		case WP_MP5:
			pm->ps->weaponTime += RQ3_MP5_DISARM_DELAY;
			break;
		case WP_HANDCANNON:
			pm->ps->weaponTime += RQ3_HANDCANNON_DISARM_DELAY;
			break;
		case WP_SSG3000:
			pm->ps->weaponTime += RQ3_SSG3000_DISARM_DELAY;
			break;
		case WP_AKIMBO:
			pm->ps->weaponTime += RQ3_AKIMBO_DISARM_DELAY;
			break;
		case WP_KNIFE:
			pm->ps->weaponTime += RQ3_KNIFE_DISARM_DELAY;
			break;
		case WP_GRENADE:
			pm->ps->weaponTime += RQ3_GRENADE_DISARM_DELAY;
			break;
		default:
			//Elder: shouldn't be here
			//G_Printf("PM_BeginWeaponChange: received bad weapon %d\n", pm->ps->weapon);
			pm->ps->weaponTime += 600;
			break;
		}

		if (pm->ps->weapon == WP_KNIFE && !(pm->ps->persistant[PERS_WEAPONMODES] & RQ3_KNIFEMODE))
			PM_StartWeaponAnim(WP_ANIM_THROWDISARM);
		else {
			PM_StartWeaponAnim(WP_ANIM_DISARM);
		}
	}

	// Elder: cancel reload stuff here
	pm->ps->stats[STAT_RELOADTIME] = 0;
	pm->ps->stats[STAT_RELOADATTEMPTS] = 0;
	pm->ps->stats[STAT_RQ3] &= ~RQ3_FASTRELOADS;
	pm->ps->stats[STAT_RQ3] &= ~RQ3_LOCKRELOADS;
	pm->ps->stats[STAT_RQ3] &= ~RQ3_QUEUERELOAD;

	// Elder: cancel burst shots
	pm->ps->stats[STAT_BURST] = 0;

	// NiceAss: Added this as a fix for knifes and grenades when you throw the last one.
	if (((pm->ps->weapon == WP_GRENADE || pm->ps->weapon == WP_KNIFE) && pm->ps->ammo[pm->ps->weapon] == 0) &&
	    pm->ps->weaponstate != WEAPON_FIRING) {
		pm->ps->weaponstate = WEAPON_DROPPING;
		pm->ps->weaponTime = 0;
		return;
	}

	pm->ps->weaponstate = WEAPON_DROPPING;

	if (pm->ps->weapon == WP_KNIFE && !(pm->ps->persistant[PERS_WEAPONMODES] & RQ3_KNIFEMODE))
		PM_StartWeaponAnim(WP_ANIM_THROWDISARM);
	else {
		PM_StartWeaponAnim(WP_ANIM_DISARM);
	}

	if ( pm->ps->weapon == WP_AKIMBO )
		PM_StartTorsoAnim(TORSO_DROP2);
	else
		PM_StartTorsoAnim(TORSO_DROP);
}

/*
===============
PM_FinishWeaponChange
===============
*/
static void PM_FinishWeaponChange(void)
{
	int weapon, savedWeap;

	weapon = pm->cmd.weapon;

// JBravo: debug for the bandage bug
	savedWeap = pm->ps->weapon;

	if (weapon < WP_NONE || weapon >= WP_NUM_WEAPONS) {
//              Com_Printf("BANDAGEBUG: (1) weapon is %d and cmd.weapon is %d. Reverting to previous weapon\n", pm->ps->weapon,
//                              weapon);
		weapon = savedWeap;
//              weapon = WP_NONE;
	}

	if (!(pm->ps->stats[STAT_WEAPONS] & (1 << weapon))) {
//              Com_Printf("BANDAGEBUG: (2) weapon is %d and cmd.weapon is %d. Reverting to previous weapon\n", pm->ps->weapon,
//                              weapon);
		weapon = savedWeap;
//              weapon = WP_NONE;
	}
	//Remove grenade/knife if out of ammo
	if ((weapon == WP_GRENADE || weapon == WP_KNIFE) && pm->ps->ammo[weapon] == 0) {
		if (weapon == WP_GRENADE)
			pm->ps->stats[STAT_WEAPONS] &= ~(1 << WP_GRENADE);
		if (weapon == WP_KNIFE)
			pm->ps->stats[STAT_WEAPONS] &= ~(1 << WP_KNIFE);
		weapon = WP_PISTOL;
	}

	pm->ps->weapon = weapon;
	pm->ps->weaponstate = WEAPON_RAISING;
	//Elder: weapon-dependent timing
	switch (pm->ps->weapon) {
	case WP_PISTOL:
		pm->ps->weaponTime += RQ3_PISTOL_ACTIVATE_DELAY;
		break;
	case WP_M3:
		pm->ps->weaponTime += RQ3_M3_ACTIVATE_DELAY;
		break;
	case WP_M4:
		pm->ps->weaponTime += RQ3_M4_ACTIVATE_DELAY;
		break;
	case WP_MP5:
		pm->ps->weaponTime += RQ3_MP5_ACTIVATE_DELAY;
		break;
	case WP_HANDCANNON:
		pm->ps->weaponTime += RQ3_HANDCANNON_ACTIVATE_DELAY;
		break;
	case WP_SSG3000:
		pm->ps->weaponTime += RQ3_SSG3000_ACTIVATE_DELAY;
		break;
	case WP_AKIMBO:
		pm->ps->weaponTime += RQ3_AKIMBO_ACTIVATE_DELAY;
		break;
	case WP_KNIFE:
		pm->ps->weaponTime += RQ3_KNIFE_ACTIVATE_DELAY;
		break;
	case WP_GRENADE:
		pm->ps->weaponTime += RQ3_GRENADE_ACTIVATE_DELAY;
		break;
	default:
		//Elder: shouldn't be here
		//G_Printf("PM_FinishWeaponChange: received bad weapon %d\n", pm->ps->weapon);
		pm->ps->weaponTime += 750;
		break;
	}

	if (pm->ps->weapon == WP_KNIFE && !(pm->ps->persistant[PERS_WEAPONMODES] & RQ3_KNIFEMODE))
		PM_StartWeaponAnim(WP_ANIM_THROWACTIVATE);
	else
		PM_StartWeaponAnim(WP_ANIM_ACTIVATE);

	if ( pm->ps->weapon == WP_AKIMBO )
		PM_StartTorsoAnim(TORSO_RAISE2);
	else
		PM_StartTorsoAnim(TORSO_RAISE);
}

/*
==============
PM_TorsoAnimation

==============
*/
static void PM_TorsoAnimation(void)
{
	if (pm->ps->weaponstate == WEAPON_READY) {
		if (pm->ps->weapon == WP_KNIFE)
			PM_ContinueTorsoAnim(TORSO_STAND2);
		else if ( pm->ps->weapon == WP_AKIMBO)
			PM_ContinueTorsoAnim(TORSO_STAND3);
		else if ( pm->ps->weapon == WP_PISTOL)
			PM_ContinueTorsoAnim(TORSO_STAND4);
		else
			PM_ContinueTorsoAnim(TORSO_STAND);

		// QUARANTINE - Weapon Animation
		// Should always draw the weapon when it is just ready
		if (pm->ps->ammo[pm->ps->weapon] == 0)
			PM_ContinueWeaponAnim(WP_ANIM_EMPTY);
		else if (pm->ps->weapon == WP_KNIFE && !(pm->ps->persistant[PERS_WEAPONMODES] & RQ3_KNIFEMODE))
			PM_ContinueWeaponAnim(WP_ANIM_THROWIDLE);
		else
			PM_ContinueWeaponAnim(WP_ANIM_IDLE);

//              PM_ContinueWeaponAnim( WP_ANIM_READY );

		return;
	}
}

/*
==============
PM_Reload

Added by Elder
What a mess this is :/
FIXME: This is poorly implemented

Does reload stuff like fast-reloads, sound events,
some ammo synchronization, etc.
Clip management is handled on the server (ReloadWeapon)
because we can't store all the clips in a playerstate (nor should we)
It is triggered by BUTTON_AFFIRMATIVE (bind +button5)
==============
*/
static void PM_Reload(void)
{
	// int weapon = pm->ps->weapon;
	int truePress = 0;

	// only normal/noclip players can reload
	if (pm->ps->pm_type > PM_NOCLIP) {
		pm->ps->pm_flags &= ~PMF_RELOAD_HELD;
		pm->ps->stats[STAT_RELOADTIME] = 0;
		pm->ps->stats[STAT_RELOADATTEMPTS] = 0;
		pm->ps->stats[STAT_RQ3] &= ~RQ3_FASTRELOADS;
		pm->ps->stats[STAT_RQ3] &= ~RQ3_LOCKRELOADS;
		pm->ps->stats[STAT_RQ3] &= ~RQ3_QUEUERELOAD;
		return;
	}
	// try to reload since it's queued
	if (pm->ps->stats[STAT_RQ3] & RQ3_QUEUERELOAD) {
		if ((pm->cmd.buttons & BUTTON_AFFIRMATIVE) && !(pm->ps->pm_flags & PMF_RELOAD_HELD))
			truePress = 1;

		pm->ps->stats[STAT_RQ3] &= ~RQ3_QUEUERELOAD;
		pm->ps->pm_flags &= ~PMF_RELOAD_HELD;
		pm->cmd.buttons |= BUTTON_AFFIRMATIVE;
	}
	// NiceAss: +Attack cancels fast reloads
	if (pm->cmd.buttons & BUTTON_ATTACK && pm->ps->stats[STAT_RELOADATTEMPTS] > 1) {
		pm->ps->stats[STAT_RELOADATTEMPTS] = 1;
	}

	if (pm->cmd.buttons & BUTTON_AFFIRMATIVE) {
		if (!(pm->ps->pm_flags & PMF_RELOAD_HELD)) {
			// prevent throttling
			pm->ps->pm_flags |= PMF_RELOAD_HELD;

			// check for bursting or weapon delay
			if (pm->ps->stats[STAT_BURST] > 0 || pm->ps->weaponTime > 0) {
				if (truePress && (pm->ps->weapon == WP_SSG3000 || pm->ps->weapon == WP_M3)) {
					pm->ps->stats[STAT_RQ3] |= RQ3_FASTRELOADS;
					pm->ps->stats[STAT_RELOADATTEMPTS]++;
				}

				pm->ps->stats[STAT_RQ3] |= RQ3_QUEUERELOAD;
				return;
			}
			// check for bandaging
/*			if (pm->ps->stats[STAT_RQ3] & RQ3_BANDAGE_WORK)
				return;
*/
			//Slicer
			if (pm->ps->weaponstate == WEAPON_BANDAGING)
				return;

			// check for full clip or non-reloadable weapons
			if (pm->ps->ammo[pm->ps->weapon] == ClipAmountForAmmo(pm->ps->weapon) ||
			    pm->ps->weapon == WP_KNIFE || pm->ps->weapon == WP_GRENADE) {
				//Com_Printf("No need to reload.\n");
				return;
			}
			// check for insufficient ammo
			if (pm->ps->stats[STAT_CLIPS] <= 0) {
				//Com_Printf("Out of ammo.\n");
				return;
			} else if (pm->ps->weapon == WP_HANDCANNON || pm->ps->weapon == WP_AKIMBO) {
				if (pm->ps->stats[STAT_CLIPS] < 2) {
					//Com_Printf("Not enough ammo.\n");
					return;
				}
			}
			// check for fast-reload interrupt
			if (pm->ps->weapon == WP_M3 || pm->ps->weapon == WP_SSG3000) {
				if (pm->ps->stats[STAT_RELOADTIME] > 0)	// && (pm->ps->weapon == WP_M3 && pm->ps->stats[STAT_RELOADTIME] <  RQ3_M3_RELOAD_DELAY - RQ3_M3_ALLOW_FAST_RELOAD_DELAY || pm->ps->weapon == WP_SSG3000 && pm->ps->stats[STAT_RELOADTIME] < RQ3_SSG3000_RELOAD_DELAY - RQ3_SSG3000_ALLOW_FAST_RELOAD_DELAY)) 
				{
					if (pm->ps->stats[STAT_RQ3] & RQ3_LOCKRELOADS) {
						//Com_Printf("============= Locked out in fast-reload interrupt\n");
					} else {
						//if (pm->ps->ammo[pm->ps->weapon] + pm->ps->stats[STAT_RELOADATTEMPTS] < ClipAmountForAmmo(pm->ps->weapon) &&
						//pm->ps->stats[STAT_RELOADATTEMPTS] < pm->ps->stats[STAT_CLIPS])
						if (pm->ps->stats[STAT_RELOADATTEMPTS] < (ClipAmountForAmmo(pm->ps->weapon) - pm->ps->ammo[pm->ps->weapon]))	//only let them cue up enough shots to fill the gun
						{
							//Com_Printf("Hit fast-reload entrance\n");
							// add to reload queue and enable fast-reloads flag

							pm->ps->stats[STAT_RQ3] |= RQ3_FASTRELOADS;
							pm->ps->stats[STAT_RELOADATTEMPTS]++;
							//Com_Printf("======== Reload attempts: %i ========\n", pm->ps->stats[STAT_RELOADATTEMPTS]);
						}
						return;
					}
				}
			}
			// fresh reload
			if (pm->ps->stats[STAT_RELOADTIME] == 0) {
				// set reload time according to weapon
				switch (pm->ps->weapon) {
				case WP_PISTOL:
					pm->ps->stats[STAT_RELOADTIME] = RQ3_PISTOL_RELOAD_DELAY;
					break;
				case WP_AKIMBO:
					pm->ps->stats[STAT_RELOADTIME] = RQ3_AKIMBO_RELOAD_DELAY;
					break;
				case WP_M3:
					pm->ps->stats[STAT_RELOADTIME] = RQ3_M3_RELOAD_DELAY;
					pm->ps->stats[STAT_RELOADATTEMPTS]++;
					break;
				case WP_M4:
					pm->ps->stats[STAT_RELOADTIME] = RQ3_M4_RELOAD_DELAY;
					break;
				case WP_MP5:
					pm->ps->stats[STAT_RELOADTIME] = RQ3_MP5_RELOAD_DELAY;
					break;
				case WP_HANDCANNON:
					pm->ps->stats[STAT_RELOADTIME] = RQ3_HANDCANNON_RELOAD_DELAY;
					break;
				case WP_SSG3000:
					pm->ps->stats[STAT_RELOADTIME] = RQ3_SSG3000_RELOAD_DELAY;
					pm->ps->stats[STAT_RELOADATTEMPTS]++;
					break;
				}

				// start the animation off
				if (pm->ps->weaponstate != WEAPON_RELOADING)
					PM_StartWeaponAnim(WP_ANIM_RELOAD);

				pm->ps->weaponstate = WEAPON_RELOADING;

				PM_AddEvent(EV_RELOAD_WEAPON0);
				//Com_Printf("Starting reload\n");
				return;
			}
		}
	} else {
		pm->ps->pm_flags &= ~PMF_RELOAD_HELD;
	}

	// in-progress reload
	if (pm->ps->stats[STAT_RELOADTIME] > 0) {
		pm->ps->stats[STAT_RELOADTIME] -= pml.msec;

		// process any fast-reload stuff here
		if (pm->ps->weapon == WP_M3 || pm->ps->weapon == WP_SSG3000) {
			if ((pm->ps->stats[STAT_RQ3] & RQ3_FASTRELOADS) && pm->ps->stats[STAT_RELOADATTEMPTS] > 0) {
				//Com_Printf("reloadtime (%d)\n",pm->ps->stats[STAT_RELOADTIME]);
				if (pm->ps->weapon == WP_M3) {
					// knock down reload time if doing fast-reloads
					if (pm->ps->stats[STAT_RELOADTIME] < RQ3_M3_ALLOW_FAST_RELOAD_DELAY
					    && pm->ps->stats[STAT_RELOADTIME] > RQ3_M3_FAST_RELOAD_DELAY) {
						//Com_Printf("Reducing reload time\n");
						pm->ps->stats[STAT_RELOADTIME] = RQ3_M3_FAST_RELOAD_DELAY;
					}
				} else {
					// knock down reload time if doing fast-reloads
					if (pm->ps->stats[STAT_RELOADTIME] < RQ3_SSG3000_ALLOW_FAST_RELOAD_DELAY
					    && pm->ps->stats[STAT_RELOADTIME] > RQ3_SSG3000_FAST_RELOAD_DELAY) {
						//Com_Printf("Reducing reload time\n");
						pm->ps->stats[STAT_RELOADTIME] = RQ3_SSG3000_FAST_RELOAD_DELAY;
					}
				}
			}
		}
		// insert stage 1 sound events here; check against the reload time

		// Special handcannon shell ejection hack
		if (pm->ps->weapon == WP_HANDCANNON &&
		    !(pm->ps->stats[STAT_RQ3] & RQ3_RELOADWEAPON1) && pm->ps->stats[STAT_RELOADTIME] < 1400) {
			pm->ps->stats[STAT_RQ3] |= RQ3_RELOADWEAPON1;
			PM_AddEvent(EV_RELOAD_WEAPON1);
		}
		// finished reload
		if (pm->ps->stats[STAT_RELOADTIME] <= 0) {
			int ammotoadd;

			ammotoadd = ClipAmountForReload(pm->ps->weapon);
			if (pm->ps->weapon == WP_M3 || pm->ps->weapon == WP_SSG3000) {
				// need to also check here because of fast-reloads
				if (ammotoadd + pm->ps->ammo[pm->ps->weapon] > ClipAmountForAmmo(pm->ps->weapon) ||
				    pm->ps->stats[STAT_CLIPS] <= 0) {
					ammotoadd = pm->ps->ammo[pm->ps->weapon];
					pm->ps->stats[STAT_RELOADATTEMPTS] = 0;
				} else
					ammotoadd += pm->ps->ammo[pm->ps->weapon];
			}
			// akimbo and MK23 synchronization
			if (pm->ps->weapon == WP_AKIMBO) {
				pm->ps->ammo[WP_PISTOL] = RQ3_PISTOL_AMMO;
			} else if (pm->ps->weapon == WP_PISTOL && (pm->ps->stats[STAT_WEAPONS] & (1 << WP_AKIMBO))) {
				// weird?  That's because we gave one pistol a full clip
				pm->ps->ammo[WP_AKIMBO] = pm->ps->ammo[WP_AKIMBO] - pm->ps->ammo[WP_PISTOL] + ammotoadd;
				if (pm->ps->ammo[WP_AKIMBO] > RQ3_AKIMBO_AMMO)
					pm->ps->ammo[WP_AKIMBO] = RQ3_AKIMBO_AMMO;
			}

			if (!(pm->ps->stats[STAT_RQ3] & RQ3_LOCKRELOADS)) {
				pm->ps->ammo[pm->ps->weapon] = ammotoadd;
			}
			// handle continuous fast-reloads
			if ((pm->ps->weapon == WP_M3 || pm->ps->weapon == WP_SSG3000) && (pm->ps->stats[STAT_RQ3] & RQ3_FASTRELOADS))	//&&
				//pm->ps->stats[STAT_RELOADATTEMPTS] > 0)
			{
				if (!(pm->ps->stats[STAT_RQ3] & RQ3_LOCKRELOADS) &&
				    pm->ps->stats[STAT_RELOADATTEMPTS] > 0) {
					//Com_Printf("Fast-reload cycle repeating\n");
					if (pm->ps->weapon == WP_M3)
						pm->ps->stats[STAT_RELOADTIME] += RQ3_M3_FAST_RELOAD_DELAY;
					else
						pm->ps->stats[STAT_RELOADTIME] += RQ3_SSG3000_FAST_RELOAD_DELAY;

					pm->ps->stats[STAT_RELOADATTEMPTS]--;

					if (pm->ps->stats[STAT_RELOADATTEMPTS] > 0) {
						PM_StartWeaponAnim(WP_ANIM_EXTRA1);
						//PM_StartWeaponAnim(WP_ANIM_RELOAD);
					}

					if (pm->ps->stats[STAT_CLIPS] > 0) {
						//Com_Printf("Sending event from continuous fast-reloads\n");
						PM_AddEvent(EV_RELOAD_WEAPON1);
						//PM_AddEvent(EV_RELOAD_WEAPON0);
					} else {
						//Com_Printf("Negative event prevented\n");
						pm->ps->stats[STAT_RELOADATTEMPTS] = 0;
					}

				} else {
					//Com_Printf("============= Locked out in continuous fast-reloads\n");
				}

				// finishing up fast reloads
				if ((pm->ps->stats[STAT_RQ3] & RQ3_FASTRELOADS) &&
				    pm->ps->stats[STAT_RELOADATTEMPTS] == 0) {
					//Com_Printf("Fast-reload cycle ending\n");
					if (pm->ps->weapon == WP_M3)
						pm->ps->stats[STAT_RELOADTIME] += RQ3_M3_FINISH_RELOAD_DELAY;
					else
						pm->ps->stats[STAT_RELOADTIME] += RQ3_SSG3000_FINISH_RELOAD_DELAY;

					pm->ps->stats[STAT_RQ3] &= ~RQ3_FASTRELOADS;
					// lock fast-reloads during finish delay
					pm->ps->stats[STAT_RQ3] |= RQ3_LOCKRELOADS;
					//Com_Printf("<<<<<<<<<<<<< Locking\n");
					PM_StartWeaponAnim(WP_ANIM_EXTRA2);
				}

				return;
			}
			// normal reload case
			//else
			//{
			// unlock
			if (pm->ps->stats[STAT_RQ3] & RQ3_LOCKRELOADS) {
				//Com_Printf(">>>>>>>>>>>>> Unlocking\n");
				pm->ps->stats[STAT_RQ3] &= ~RQ3_LOCKRELOADS;
			} else {
				//Com_Printf("Sending event from normal reload\n");
				PM_AddEvent(EV_RELOAD_WEAPON2);
			}

			//Com_Printf("Finished reload\n");
			pm->ps->stats[STAT_RELOADTIME] = 0;
			pm->ps->stats[STAT_RELOADATTEMPTS] = 0;
			pm->ps->stats[STAT_RQ3] &= ~RQ3_RELOADWEAPON1;
			pm->ps->weaponstate = WEAPON_READY;
			//}

		}		// end finish reload

	}			// end in-progress reload

}

/*
==============
PM_Weapon

Generates weapon events and modifes the weapon counter
==============
*/
static void PM_Weapon(void)
{
	int addTime;

	//Elder: PISTOL always gets set to 12 if akimbos have >11 based on AQ2 observation
	if (pm->ps->weapon == WP_AKIMBO && pm->ps->ammo[WP_AKIMBO] > 11) {
		pm->ps->ammo[WP_PISTOL] = 12;
	}
	// don't allow attack until all buttons are up
	if (pm->ps->pm_flags & PMF_RESPAWNED) {
		return;
	}
	// ignore if spectator
	if (pm->ps->persistant[PERS_TEAM] == TEAM_SPECTATOR) {
		return;
	}
	// check for dead player
	if (pm->ps->stats[STAT_HEALTH] <= 0) {
		pm->ps->weapon = WP_NONE;
		return;
	}
	//Elder: New 3rb Code
	//force fire button down if STAT_BURST is < proper amount
	//Otherwise release the button
	if ((pm->ps->weapon == WP_M4 &&
	     (pm->ps->persistant[PERS_WEAPONMODES] & RQ3_M4MODE) == RQ3_M4MODE) ||
	    (pm->ps->weapon == WP_MP5 && (pm->ps->persistant[PERS_WEAPONMODES] & RQ3_MP5MODE) == RQ3_MP5MODE)) {
		int weaponNum = pm->ps->weapon;

		if (pm->ps->ammo[weaponNum] == 0) {
			pm->ps->stats[STAT_BURST] = 0;
		} else if (pm->cmd.buttons & BUTTON_ATTACK)	// && client->ps.stats[STAT_BURST] > 0)
		{
			if (pm->ps->stats[STAT_BURST] >= 0 && pm->ps->stats[STAT_BURST] < 3)
				pm->cmd.buttons |= BUTTON_ATTACK;
			else
				pm->cmd.buttons &= ~BUTTON_ATTACK;
		} else if (pm->ps->stats[STAT_BURST] > 2) {
			pm->ps->stats[STAT_BURST] = 0;
			pm->ps->weaponTime += 300;
		}
		//Don't need?
		else if (pm->ps->stats[STAT_BURST] > 0)
			pm->cmd.buttons |= BUTTON_ATTACK;
	}
	//agt: Knife stupidity
	//I'll hijack STAT_BURST for this one
	if (pm->ps->weapon == WP_KNIFE && (pm->ps->persistant[PERS_WEAPONMODES] & RQ3_KNIFEMODE)) {
		if (pm->cmd.buttons & BUTTON_ATTACK && pm->ps->stats[STAT_BURST] >= 0 && pm->ps->stats[STAT_BURST] < 5) {
			pm->cmd.buttons |= BUTTON_ATTACK;
		} else if (pm->ps->stats[STAT_BURST] > 4) {
			pm->ps->stats[STAT_BURST] = 0;
			pm->ps->weaponTime += 650;	// NiceAss note: 30ms * 5 attacks = 150 ms + 650ms = 800ms.
		} else if (pm->ps->stats[STAT_BURST] > 0) {
			pm->cmd.buttons |= BUTTON_ATTACK;
		}
	}
	//Elder: New semi-auto code
	if (pm->ps->weapon == WP_PISTOL && (pm->ps->persistant[PERS_WEAPONMODES] & RQ3_MK23MODE) == RQ3_MK23MODE) {
		if (pm->ps->ammo[WP_PISTOL] == 0) {
			pm->ps->stats[STAT_BURST] = 0;
		} else if ((pm->cmd.buttons & BUTTON_ATTACK) && pm->ps->stats[STAT_BURST]) {
			pm->cmd.buttons &= ~BUTTON_ATTACK;
		} else if (pm->ps->stats[STAT_BURST]) {
			pm->ps->weaponTime += 100;	// lowered again to 100 from 150 from 200
			pm->ps->stats[STAT_BURST] = 0;
		}
	}
	// Elder: new akimbo code
	if (pm->ps->weapon == WP_AKIMBO) {
		if (pm->ps->ammo[WP_AKIMBO] == 0 && pm->ps->stats[STAT_BURST]) {
			pm->ps->stats[STAT_BURST] = 0;
			pm->cmd.buttons &= ~BUTTON_ATTACK;
		} else if (pm->ps->stats[STAT_BURST]) {
			pm->cmd.buttons |= BUTTON_ATTACK;
		}
	}

	//NiceAss: I added this for smooth M4 rise
	if (pm->ps->weaponstate == WEAPON_FIRING && pm->ps->ammo[pm->ps->weapon] &&
		pm->ps->weapon == WP_M4 && !pm->ps->stats[STAT_BURST] && 
		!(pm->ps->persistant[PERS_WEAPONMODES] & RQ3_M4MODE) /*&&
		pm->predict*/ ) {
			pm->ps->delta_angles[0] -= ANGLE2SHORT(0.13);
	}


	// make weapon function
	if (pm->ps->weaponTime > 0) {
		pm->ps->weaponTime -= pml.msec;
	}
	// Elder: make stall decrease
	if (pm->ps->stats[STAT_WEAPONSTALLTIME] > 0) {
		pm->ps->stats[STAT_WEAPONSTALLTIME] -= pml.msec;
	}
	// check for weapon change
	// can't change if weapon is firing, but can change
	// again if lowering or raising

	// Elder: modified so that a dropweapon command is high precedence

	//if ( pm->ps->weaponTime <= 0 || pm->ps->weaponstate != WEAPON_FIRING) {
	if ((pm->ps->stats[STAT_RQ3] & RQ3_THROWWEAPON) || (pm->ps->weaponTime <= 0 &&
							    !(pm->ps->weaponstate == WEAPON_FIRING
							      || pm->ps->weaponstate == WEAPON_STALL))) {
		if (pm->ps->weapon != pm->cmd.weapon) {
			//Elder: if switching weapons, fire off the grenade "instantly"
			if (pm->ps->weapon == WP_GRENADE && pm->ps->weaponstate == WEAPON_COCKED) {
				pm->ps->weaponstate = WEAPON_FIRING;
				pm->cmd.buttons &= ~BUTTON_ATTACK;
				//if (pm->predict)
					PM_AddEvent2(EV_FIRE_WEAPON, RQ3_WPMOD_GRENADEDROP);
				pm->ps->ammo[WP_GRENADE]--;
				//Makro - if this is the last grenade, remove the weapon from the inventory
				if (pm->ps->ammo[WP_GRENADE] <= 0) {
					pm->ps->stats[STAT_WEAPONS] &= ~(1 << WP_GRENADE);
				}
			}
			PM_BeginWeaponChange(pm->cmd.weapon);
		} else {
			//Elder: temp hack
			if (pm->ps->weaponstate == WEAPON_READY) {
				if (pm->ps->ammo[pm->ps->weapon] == 0) {
					PM_ContinueWeaponAnim(WP_ANIM_EMPTY);
				} else if (pm->ps->weapon == WP_KNIFE &&
					   !(pm->ps->persistant[PERS_WEAPONMODES] & RQ3_KNIFEMODE)) {
					PM_ContinueWeaponAnim(WP_ANIM_THROWIDLE);
				} else
					PM_ContinueWeaponAnim(WP_ANIM_IDLE);
			}
		}
	}
	// Elder: added STAT_RELOADTIME and STAT_WEAPONSTALLTIME check
	if (pm->ps->weaponTime > 0 || pm->ps->stats[STAT_RELOADTIME] > 0 || pm->ps->stats[STAT_WEAPONSTALLTIME] > 0) {
		return;
	}
	// change weapon if time
	if (pm->ps->weaponstate == WEAPON_DROPPING || pm->ps->weaponstate == WEAPON_BANDAGING) {
		PM_FinishWeaponChange();
		return;
	}
	//NiceAss: Attempt to have the knife/grenade "activate" after a throw if you have another one of them
	if (pm->ps->weaponstate == WEAPON_FIRING && pm->ps->ammo[pm->ps->weapon] > 0 &&
	    (pm->ps->weapon == WP_KNIFE || pm->ps->weapon == WP_GRENADE)) {

		if (pm->ps->weapon == WP_KNIFE && !(pm->ps->persistant[PERS_WEAPONMODES] & RQ3_KNIFEMODE)) {
			pm->ps->weaponTime = RQ3_KNIFE_ACTIVATE_DELAY;
			PM_StartWeaponAnim(WP_ANIM_THROWACTIVATE);
			pm->ps->weaponstate = WEAPON_RAISING;
			PM_StartTorsoAnim(TORSO_RAISE);
			return;
		}
		if (pm->ps->weapon == WP_GRENADE) {
			pm->ps->weaponTime = RQ3_GRENADE_DELAY;
			PM_StartWeaponAnim(WP_ANIM_ACTIVATE);
			pm->ps->weaponstate = WEAPON_RAISING;
			PM_StartTorsoAnim(TORSO_RAISE);
			return;
		}
	}

	if (pm->ps->weaponstate == WEAPON_RAISING &&
	    !((pm->ps->persistant[PERS_WEAPONMODES] & RQ3_KNIFEMODE) && pm->ps->stats[STAT_BURST])) {
		pm->ps->weaponstate = WEAPON_READY;
		if (pm->ps->weapon == WP_KNIFE)
			PM_StartTorsoAnim(TORSO_STAND2);
		else if ( pm->ps->weapon == WP_AKIMBO )
			PM_StartTorsoAnim(TORSO_STAND3);
		else if ( pm->ps->weapon == WP_PISTOL )
			PM_StartTorsoAnim(TORSO_STAND4);
		else
			PM_StartTorsoAnim(TORSO_STAND);
		// temp hack
		if (pm->ps->ammo[pm->ps->weapon] == 0) {
			PM_ContinueWeaponAnim(WP_ANIM_EMPTY);
		}

		else if (pm->ps->weapon == WP_KNIFE && !(pm->ps->persistant[PERS_WEAPONMODES] & RQ3_KNIFEMODE))
			PM_StartWeaponAnim(WP_ANIM_THROWIDLE);
		else
			PM_StartWeaponAnim(WP_ANIM_IDLE);

		return;
	}

	// NiceAss: Added for knife animation switch.
	// At the moment, this is only used for changing knife-throw modes.
	if (pm->ps->weaponstate == WEAPON_MODECHANGE) {
		if (pm->ps->weapon == WP_KNIFE)
			pm->ps->weaponstate = WEAPON_READY;
	}
	// JBravo: no shooting during LCA
	if (pm->lca) {
		return;
	}
	// Elder: fire on release - based on code from inolen
	// check for fire
	// if they are pressing attack and their current weapon is the grenade
	if (pm->cmd.buttons & 1) {
		if (pm->ps->weapon == WP_GRENADE) {
			if (pm->ps->weaponstate == WEAPON_READY) {
				// NiceAss: Add a delay so the pin-pull animation can complete.
				pm->ps->weaponTime = 800;
				// put it in the "cocked" position and play the pin-pull animation
				pm->ps->weaponstate = WEAPON_COCKED;
				PM_ContinueWeaponAnim(WP_ANIM_EXTRA1);
				return;
			} else if (pm->ps->weaponstate == WEAPON_COCKED)
				return;
		}
		// Elder: stall the thrown knife action

		else if (pm->ps->weapon == WP_KNIFE && pm->ps->weaponstate != WEAPON_STALL &&
			 pm->ps->stats[STAT_WEAPONSTALLTIME] <= 0 &&
			 !(pm->ps->persistant[PERS_WEAPONMODES] & RQ3_KNIFEMODE) && pm->ps->ammo[pm->ps->weapon]) {
			pm->ps->weaponstate = WEAPON_STALL;
			pm->ps->stats[STAT_WEAPONSTALLTIME] = 200;
			PM_StartWeaponAnim(WP_ANIM_THROWFIRE);
			return;
		}
	}
	// check for fireA release
	// if they aren't pressing attack
	if (!(pm->cmd.buttons & 1)) {
		// if we had them cocked and then they aren't pressing it then
		// that means they released it
		if (pm->ps->weapon == WP_GRENADE) {
			if (pm->ps->weaponstate == WEAPON_COCKED) {
				// Stall for the toss motion
				pm->ps->weaponstate = WEAPON_STALL;
				pm->ps->stats[STAT_WEAPONSTALLTIME] = 300;
				PM_StartWeaponAnim(WP_ANIM_FIRE);
				return;
			} else if (pm->ps->weaponstate == WEAPON_STALL) {
				// set to be able to fire
				pm->ps->weaponstate = WEAPON_READY;
			} else {
				// else if they arn't pressing attack, then they just are running around
				pm->ps->weaponTime = 0;
				pm->ps->weaponstate = WEAPON_READY;
				return;
			}
		}

		else if (pm->ps->weapon == WP_KNIFE && !(pm->ps->persistant[PERS_WEAPONMODES] & RQ3_KNIFEMODE)) {
			if (pm->ps->weaponstate == WEAPON_STALL) {
				pm->ps->stats[STAT_WEAPONSTALLTIME] = 0;
				pm->ps->weaponstate = WEAPON_READY;
			} else {
				// else if they arn't pressing attack, then they just are running around
				pm->ps->weaponTime = 0;
				pm->ps->weaponstate = WEAPON_READY;
				return;
			}
		}

		else {
			// else if they arn't pressing attack, then they just are running around
			pm->ps->weaponTime = 0;
			pm->ps->weaponstate = WEAPON_READY;
			return;
		}
	}
	// check for out of ammo
	if (!pm->ps->ammo[pm->ps->weapon]) {
		PM_AddEvent(EV_NOAMMO);
		//NiceAss: Dirty hack:
		if (pm->ps->weapon == WP_KNIFE || pm->ps->weapon == WP_GRENADE)
			//PM_FinishWeaponChange();
			pm->ps->weaponstate = WEAPON_DROPPING;
		else
			pm->ps->weaponTime += 500;

		return;
	}
	//Elder: custom player model fire animations go here
	// start the animation even if out of ammo -- Elder: NO WAY
	if (pm->ps->weapon == WP_KNIFE || pm->ps->weapon == WP_GRENADE) {
		if (pm->ps->weapon == WP_KNIFE && (pm->ps->persistant[PERS_WEAPONMODES] & RQ3_KNIFEMODE))
			// Modified by agt for slash "bursting"
			if (!pm->ps->stats[STAT_BURST])
				PM_StartWeaponAnim(WP_ANIM_FIRE);

		PM_StartTorsoAnim(TORSO_ATTACK2);
	} else {
		// Elder: don't repeat if semi-auto
		if (!(pm->ps->weapon == WP_PISTOL && pm->ps->stats[STAT_BURST]) ||
		    !(pm->ps->weapon == WP_M4 && pm->ps->stats[STAT_BURST] > 2) ||
		    !(pm->ps->weapon == WP_MP5 && pm->ps->stats[STAT_BURST] > 2)) {

			// NiceAss: Support for akimbo torso attack animations
			if ( pm->ps->weapon == WP_AKIMBO )
				PM_StartTorsoAnim(TORSO_ATTACK3);
			else if ( pm->ps->weapon == WP_PISTOL )
				PM_StartTorsoAnim(TORSO_ATTACK4);
			else
				PM_StartTorsoAnim(TORSO_ATTACK);

			// QUARANTINE - Weapon animations
			// This should change pm->ps->generic1 so we can animate
			// Elder: don't repeat if on semi-auto
			// temp hack

			if (pm->ps->weapon == WP_AKIMBO) {
				// don't repeat animation if on second akimbo shot
				if (!pm->ps->stats[STAT_BURST]) {
					if (pm->ps->ammo[pm->ps->weapon] > 2)
						PM_StartWeaponAnim(WP_ANIM_FIRE);
					else
						PM_StartWeaponAnim(WP_ANIM_EXTRA1);
				}
			} else {
				if (pm->ps->ammo[pm->ps->weapon] > 1 || pm->ps->weapon != WP_PISTOL)
					PM_StartWeaponAnim(WP_ANIM_FIRE);
				else
					PM_StartWeaponAnim(WP_ANIM_EXTRA1);	// Fix for last round fired
			}
		}
	}

	//NiceAss: Hack of the week!!!!
	if (pm->ps->weaponstate == WEAPON_FIRING && pm->ps->weapon == WP_GRENADE)
		return;

	pm->ps->weaponstate = WEAPON_FIRING;

	// Elder: increment stat if alt-fire mode --needs to be predicted as well
	if ((pm->ps->weapon == WP_M4 &&
	     (pm->ps->persistant[PERS_WEAPONMODES] & RQ3_M4MODE) == RQ3_M4MODE) ||
	    (pm->ps->weapon == WP_MP5 &&
	     (pm->ps->persistant[PERS_WEAPONMODES] & RQ3_MP5MODE) == RQ3_MP5MODE) ||
	    (pm->ps->weapon == WP_PISTOL &&
	     (pm->ps->persistant[PERS_WEAPONMODES] & RQ3_MK23MODE) == RQ3_MK23MODE) ||
	    (pm->ps->weapon == WP_KNIFE && (pm->ps->persistant[PERS_WEAPONMODES] & RQ3_KNIFEMODE) == RQ3_KNIFEMODE)) {
		pm->ps->stats[STAT_BURST]++;
	}

	//Elder: M4 kick code
	/*
	if (pm->ps->weapon == WP_M4 && ((pm->ps->persistant[PERS_WEAPONMODES] & RQ3_M4MODE) != RQ3_M4MODE)) {
		pm->ps->delta_angles[0] = ANGLE2SHORT(SHORT2ANGLE(pm->ps->delta_angles[0]) - 0.7);
	}
	*/

	// take an ammo away if not infinite
	if (pm->ps->ammo[pm->ps->weapon] != -1) {
		//Elder: don't remove ammo if slashing knife
		if (!
		    (pm->ps->weapon == WP_KNIFE
		     && (pm->ps->persistant[PERS_WEAPONMODES] & RQ3_KNIFEMODE) == RQ3_KNIFEMODE)) {
			pm->ps->ammo[pm->ps->weapon]--;
		}
		//Elder: special weapon case handling

		//Elder: remove knives from inventory if out of ammo
		if (pm->ps->weapon == WP_KNIFE && pm->ps->ammo[WP_KNIFE] == 0) {
			pm->ps->stats[STAT_WEAPONS] &= ~(1 << WP_KNIFE);
		}
		//Elder: remove grenade from inventory if out of ammo
		else if (pm->ps->weapon == WP_GRENADE && pm->ps->ammo[WP_GRENADE] == 0) {
			pm->ps->stats[STAT_WEAPONS] &= ~(1 << WP_GRENADE);
		}
		//Elder: remove one more bullet/shell if handcannon
		else if (pm->ps->weapon == WP_HANDCANNON) {
			pm->ps->ammo[WP_HANDCANNON]--;
		}

		//Elder: sync bullets a la AQ2 style
		if (pm->ps->weapon == WP_AKIMBO && pm->ps->ammo[WP_AKIMBO] < 12) {
			pm->ps->ammo[WP_PISTOL] = pm->ps->ammo[WP_AKIMBO];
		} else if (pm->ps->weapon == WP_PISTOL && pm->ps->ammo[WP_AKIMBO] > 0) {
			pm->ps->ammo[WP_AKIMBO]--;
		}
	}

	// fire weapon
	// NiceAss: Check to see if this is game or cgame
	//if (pm->predict) {
		//Elder: check for silencer
		// JBravo: new multiple itemcode
		if ((pm->ps->stats[STAT_HOLDABLE_ITEM] & (1 << HI_SILENCER)) &&
			(pm->ps->weapon == WP_PISTOL || pm->ps->weapon == WP_MP5 || pm->ps->weapon == WP_SSG3000)) {
			PM_AddEvent2(EV_FIRE_WEAPON, RQ3_WPMOD_SILENCER);
		} else if (pm->ps->stats[STAT_BURST] > 1 && pm->ps->weapon == WP_KNIFE &&
			   (pm->ps->persistant[PERS_WEAPONMODES] & RQ3_KNIFEMODE) == RQ3_KNIFEMODE) {
			// NiceAss: Prevent the client from doing stuff after the first "slash".
			PM_AddEvent2(EV_FIRE_WEAPON, RQ3_WPMOD_KNIFENOMARK);
		} else
			PM_AddEvent(EV_FIRE_WEAPON);
	//}

	switch (pm->ps->weapon) {
	default:
		//Elder: weapon delay times using constants
	case WP_SSG3000:
		addTime = RQ3_SSG3000_DELAY;
		break;
	case WP_PISTOL:
		addTime = RQ3_PISTOL_DELAY;
		break;
	case WP_M4:
		addTime = RQ3_M4_DELAY;
		break;
	case WP_MP5:
		addTime = RQ3_MP5_DELAY;
		break;
	case WP_KNIFE:
		if ((pm->ps->persistant[PERS_WEAPONMODES] & RQ3_KNIFEMODE) == RQ3_KNIFEMODE) {
			//knife slash
			//agt: hacking it up a little.  The alternate time value should be
			//a constant, but I have a headache and I'm tired of screwing around
			//with the knives. [NiceAss: I'll do it for you!]
			if (pm->ps->stats[STAT_BURST]) {
				addTime = RQ3_KNIFE_SLASH_BURST;	//NiceAss: Not really a burst, but it fits with everything else =D
			} else {
				addTime = RQ3_KNIFE_DELAY;
			}
		} else {
			//knife throw
			addTime = RQ3_THROW_DELAY;
		}
		break;
	case WP_HANDCANNON:
		addTime = RQ3_HANDCANNON_DELAY;
		break;
	case WP_M3:
		addTime = RQ3_M3_DELAY;
		break;
	case WP_AKIMBO:
		if (pm->ps->stats[STAT_BURST]) {
			addTime = RQ3_AKIMBO_DELAY2;
			pm->ps->stats[STAT_BURST] = 0;
		} else {
			pm->ps->stats[STAT_BURST] = 1;
			addTime = RQ3_AKIMBO_DELAY;
		}
		break;
	case WP_GRENADE:
		addTime = RQ3_GRENADE_DELAY;
		break;
	}

	pm->ps->weaponTime += addTime;

	//Auto-switch when out of ammo with grenade or knife
	if ((pm->ps->weapon == WP_KNIFE || pm->ps->weapon == WP_GRENADE) && !pm->ps->ammo[pm->ps->weapon]) {
		PM_AddEvent(EV_NOAMMO);
		pm->ps->weaponTime += 150;
	}
}

/*
================
PM_Animate
================
*/

static void PM_Animate(void)
{
	if (pm->cmd.buttons & BUTTON_GESTURE) {
		if (pm->ps->torsoTimer == 0) {
			PM_StartTorsoAnim(TORSO_GESTURE);
			pm->ps->torsoTimer = TIMER_GESTURE;
			PM_AddEvent(EV_TAUNT);
		}
	}
}

/*
================
PM_DropTimers
================
*/
static void PM_DropTimers(void)
{
	// drop misc timing counter
	if (pm->ps->pm_time) {
		if (pml.msec >= pm->ps->pm_time) {
			pm->ps->pm_flags &= ~PMF_ALL_TIMES;
			pm->ps->pm_time = 0;
		} else {
			pm->ps->pm_time -= pml.msec;
		}
	}
	// drop animation counter
	if (pm->ps->legsTimer > 0) {
		pm->ps->legsTimer -= pml.msec;
		if (pm->ps->legsTimer < 0) {
			pm->ps->legsTimer = 0;
		}
	}

	if (pm->ps->torsoTimer > 0) {
		pm->ps->torsoTimer -= pml.msec;
		if (pm->ps->torsoTimer < 0) {
			pm->ps->torsoTimer = 0;
		}
	}
}

/*
================
PM_UpdateViewAngles

This can be used as another entry point when only the viewangles
are being updated isntead of a full move
================
*/
void PM_UpdateViewAngles(playerState_t * ps, const usercmd_t * cmd)
{
	short temp;
	int i;

	if (ps->pm_type == PM_INTERMISSION || ps->pm_type == PM_SPINTERMISSION) {
		return;		// no view changes at all
	}

	if (ps->pm_type != PM_SPECTATOR && ps->stats[STAT_HEALTH] <= 0) {
		return;		// no view changes at all
	}
	// circularly clamp the angles with deltas
	for (i = 0; i < 3; i++) {
		temp = cmd->angles[i] + ps->delta_angles[i];
		if (i == PITCH) {
			// don't let the player look up or down more than 90 degrees
			if (temp > 16000) {
				ps->delta_angles[i] = 16000 - cmd->angles[i];
				temp = 16000;
			} else if (temp < -16000) {
				ps->delta_angles[i] = -16000 - cmd->angles[i];
				temp = -16000;
			}
		}
		ps->viewangles[i] = SHORT2ANGLE(temp);
	}

}

/*
===================
PM_LadderMove()
by: Calrathan [Arthur Tomlin]

Right now all I know is that this works for VERTICAL ladders.
Ladders with angles on them (urban2 for AQ2) haven't been tested.
===================
*/
static void PM_LadderMove(void)
{
	int i, old;
	vec3_t wishvel;
	float wishspeed;
	vec3_t wishdir;
	float scale;
	float vel;

	// Elder: ladder jump crap
	trace_t tr;
	vec3_t lookAhead;
	vec3_t trEndTest;

// New experimental jump code -- not too good
#if 0
	// Elder: ladder jump crap
	lookAhead[0] = pml.forward[0];
	lookAhead[1] = pml.forward[1];
	lookAhead[2] = 0;
	VectorNormalize(lookAhead);
	// Calculate end point
	VectorMA(pm->ps->origin, 1, lookAhead, trEndTest);
	//trEndTest[2] += 20;
	trEndTest[2] += 6;
	// Calculate start point
	VectorCopy(pm->ps->origin, lookAhead);
	//lookAhead[2] += 16;
	lookAhead[2] += 2;

	pm->trace(&tr, lookAhead, pm->mins, pm->maxs, trEndTest, pm->ps->clientNum, MASK_PLAYERSOLID);

	if (tr.fraction == 1 || !(tr.surfaceFlags & SURF_LADDER)) {
		// good conditions -- now we can set up a double jump on the ladder
		if (pm->debugLevel)
			Com_Printf("Ladder jump conditions met...\n");
		if (pm->ps->stats[STAT_JUMPTIME] > 0 && PM_CheckJump()) {
			if (pm->debugLevel)
				Com_Printf("Trying ladder jump...\n");
			pml.ladder = qfalse;
		}
	}
	// End ladder jump crap
#endif

	PM_Friction();
	//pml.ladder = qtrue;

	scale = PM_CmdScale(&pm->cmd);

	// user intentions [what the user is attempting to do]
	if (!scale) {
		wishvel[0] = 0;
		wishvel[1] = 0;
		wishvel[2] = 0;
	} else {		// if they're trying to move... lets calculate it
		for (i = 0; i < 3; i++)
			wishvel[i] = scale * pml.forward[i] * pm->cmd.forwardmove +
			    scale * pml.right[i] * pm->cmd.rightmove;
		//Elder: changed from a factor of 2 to 10
		wishvel[0] /= PM_LADDER_MOVE_REDUCTION;
		wishvel[1] /= PM_LADDER_MOVE_REDUCTION;
		wishvel[2] += scale * pm->cmd.upmove;
	}

	VectorCopy(wishvel, wishdir);
	wishspeed = VectorNormalize(wishdir);

	if (wishspeed > pm->ps->speed * pm_ladderScale) {
		wishspeed = pm->ps->speed * pm_ladderScale;
	}
// Old ladder jump code -- right now it works better
#if 1
	// Elder: ladder jump crap
	lookAhead[0] = pml.forward[0];
	lookAhead[1] = pml.forward[1];
	lookAhead[2] = 0;
	VectorNormalize(lookAhead);
	// Calculate end point
	VectorMA(pm->ps->origin, 1, lookAhead, trEndTest);
	trEndTest[2] += 20;
	// Calculate start point
	VectorCopy(pm->ps->origin, lookAhead);
	lookAhead[2] += 16;

	pm->trace(&tr, lookAhead, pm->mins, pm->maxs, trEndTest, pm->ps->clientNum, MASK_PLAYERSOLID);

	if (tr.fraction == 1 || !(tr.surfaceFlags & SURF_LADDER)) {
		// good conditions -- now we can set up a double jump on the ladder
		if (pm->debugLevel)
			Com_Printf("Ladder jump conditions met...\n");
		if (PM_CheckJump()) {
			if (pm->debugLevel)
				Com_Printf("Trying ladder jump...\n");
		}
	}
	// End ladder jump crap
#endif

	PM_Accelerate(wishdir, wishspeed, pm_ladderAccelerate);

	// This SHOULD help us with sloped ladders, but it remains untested.
	if (pml.groundPlane && DotProduct(pm->ps->velocity, pml.groundTrace.plane.normal) < 0) {
		vel = VectorLength(pm->ps->velocity);
		// slide along the ground plane [the ladder section under our feet]
		PM_ClipVelocity(pm->ps->velocity, pml.groundTrace.plane.normal, pm->ps->velocity, OVERCLIP);

		VectorNormalize(pm->ps->velocity);
		VectorScale(pm->ps->velocity, vel, pm->ps->velocity);
	}

	PM_StepSlideMove(qfalse);	// move without gravity
	// Elder: stop legs from animating
	//PM_ForceLegsAnim(LEGS_JUMP);
	//Makro - changed to LEGS_IDLE
	PM_ForceLegsAnim(LEGS_IDLE);

	
	//Makro - play footstep sound
	//...only if we don't have slippers!
	if (pm->ps->velocity[2] && !(pm->ps->stats[STAT_HOLDABLE_ITEM] && (1 << HI_SLIPPERS)) )
	{
		old = pm->ps->bobCycle;
		//the faster we move, the more frequent the footsteps
		pm->ps->bobCycle = (int) (old + 0.45 * fabs(pm->ps->velocity[2]) / 225.0f * pml.msec) & 255;
		// if we just crossed a cycle boundary, play an apropriate footstep event
		if (((old + 64) ^ (pm->ps->bobCycle + 64)) & 128)
		{
			//PM_AddEvent(PM_FootstepForSurface(pml.ladderSurface));
		}
	} else {
		pm->ps->bobCycle = 0;
	}
}

/*
=============
CheckLadder [ ARTHUR TOMLIN ]
=============
*/
void CheckLadder(void)
{
	vec3_t flatforward, spot;
	trace_t trace;

	pml.ladder = qfalse;

	// check for ladder
	flatforward[0] = pml.forward[0];
	flatforward[1] = pml.forward[1];
	flatforward[2] = 0;
	VectorNormalize(flatforward);

	VectorMA(pm->ps->origin, 1, flatforward, spot);
	pm->trace(&trace, pm->ps->origin, pm->mins, pm->maxs, spot, pm->ps->clientNum, MASK_PLAYERSOLID);

	//Makro - save the surface flags so we can play the appropriate sound
	pml.ladderSurface = trace.surfaceFlags;

	if ((trace.fraction < 1) && (trace.surfaceFlags & SURF_LADDER))
		pml.ladder = qtrue;

	// Elder: does this work?
	/*
	   if (pml.ladder && pml.previous_ladder == qfalse)
	   {
	   if (pm->debugLevel)
	   Com_Printf("Hit ladder hard\n");
	   PM_CrashLand();
	   }
	 */
}

/*
================
PmoveSingle

================
*/
void trap_SnapVector(float *v);

void PmoveSingle(pmove_t * pmove)
{
	pm = pmove;

	// this counter lets us debug movement problems with a journal
	// by setting a conditional breakpoint fot the previous frame
	c_pmove++;

	// clear results
	pm->numtouch = 0;
	pm->watertype = 0;
	pm->waterlevel = 0;

	if (pm->ps->stats[STAT_HEALTH] <= 0) {
		pm->tracemask &= ~CONTENTS_BODY;	// corpses can fly through bodies
	}
	// make sure walking button is clear if they are running, to avoid
	// proxy no-footsteps cheats
	if (abs(pm->cmd.forwardmove) > 64 || abs(pm->cmd.rightmove) > 64) {
		pm->cmd.buttons &= ~BUTTON_WALKING;
	}
	// set the talk balloon flag
	if (pm->cmd.buttons & BUTTON_TALK) {
		pm->ps->eFlags |= EF_TALK;
	} else {
		pm->ps->eFlags &= ~EF_TALK;
	}

	// set the firing flag for continuous beam weapons
	if (!(pm->ps->pm_flags & PMF_RESPAWNED) && pm->ps->pm_type != PM_INTERMISSION
	    && (pm->cmd.buttons & BUTTON_ATTACK) && pm->ps->ammo[pm->ps->weapon]) {
		pm->ps->eFlags |= EF_FIRING;
	} else {
		pm->ps->eFlags &= ~EF_FIRING;
	}

	// clear the respawned flag if attack and use are cleared
	if (pm->ps->stats[STAT_HEALTH] > 0 && !(pm->cmd.buttons & (BUTTON_ATTACK | BUTTON_USE_HOLDABLE))) {
		pm->ps->pm_flags &= ~PMF_RESPAWNED;
	}
	// if talk button is down, dissallow all other input
	// this is to prevent any possible intercept proxy from
	// adding fake talk balloons
	if (pmove->cmd.buttons & BUTTON_TALK) {
		// keep the talk button set tho for when the cmd.serverTime > 66 msec
		// and the same cmd is used multiple times in Pmove
		pmove->cmd.buttons = BUTTON_TALK;
		pmove->cmd.forwardmove = 0;
		pmove->cmd.rightmove = 0;
		pmove->cmd.upmove = 0;
	}
	// clear all pmove local vars
	memset(&pml, 0, sizeof(pml));

	// determine the time
	pml.msec = pmove->cmd.serverTime - pm->ps->commandTime;
	if (pml.msec < 1) {
		pml.msec = 1;
	} else if (pml.msec > 200) {
		pml.msec = 200;
	}
	pm->ps->commandTime = pmove->cmd.serverTime;

	// save old org in case we get stuck
	VectorCopy(pm->ps->origin, pml.previous_origin);

	// save old velocity for crashlanding
	VectorCopy(pm->ps->velocity, pml.previous_velocity);

	pml.frametime = pml.msec * 0.001;

	// update the viewangles

	PM_UpdateViewAngles(pm->ps, &pm->cmd);

	AngleVectors(pm->ps->viewangles, pml.forward, pml.right, pml.up);

	if (pm->cmd.upmove < 10) {
		// not holding jump
		pm->ps->pm_flags &= ~PMF_JUMP_HELD;
	}
	// decide if backpedaling animations should be used
	if (pm->cmd.forwardmove < 0) {
		pm->ps->pm_flags |= PMF_BACKWARDS_RUN;
	} else if (pm->cmd.forwardmove > 0 || (pm->cmd.forwardmove == 0 && pm->cmd.rightmove)) {
		pm->ps->pm_flags &= ~PMF_BACKWARDS_RUN;
	}

	if (pm->ps->pm_type >= PM_DEAD) {
		pm->cmd.forwardmove = 0;
		pm->cmd.rightmove = 0;
		pm->cmd.upmove = 0;
	}

	if (pm->ps->pm_type == PM_SPECTATOR) {
		PM_CheckDuck();
		PM_FlyMove();
		PM_DropTimers();
		return;
	}

	if (pm->ps->pm_type == PM_NOCLIP) {
		PM_NoclipMove();
		PM_DropTimers();
		return;
	}

	if (pm->ps->pm_type == PM_FREEZE) {
		return;		// no movement at all
	}

	if (pm->ps->pm_type == PM_INTERMISSION || pm->ps->pm_type == PM_SPINTERMISSION) {
		return;		// no movement at all
	}
	// set watertype, and waterlevel
	PM_SetWaterLevel();
	pml.previous_waterlevel = pmove->waterlevel;

	// set mins, maxs, and viewheight
	PM_CheckDuck();

	// set groundentity
	PM_GroundTrace();

	if (pm->ps->pm_type == PM_DEAD) {
		PM_DeadMove();
	}

	PM_DropTimers();
	CheckLadder();		// ARTHUR TOMLIN check and see if they're on a ladder

	if (pm->ps->pm_flags & PMF_GRAPPLE_PULL) {
		PM_GrappleMove();
		// We can wiggle a bit
		PM_AirMove();
	} else if (pm->ps->pm_flags & PMF_TIME_WATERJUMP) {
		PM_WaterJumpMove();
	} else if (pm->waterlevel > 1 && !pml.ladder) {	//Blaze: wtf, need to add a comment to make it a big enough change for cvs to notice
		// swimming
		PM_WaterMove();
		// Elder: Added !(...) check below to prevent crouch spasms at bottom of ladders
	} else if (pml.ladder
		   && !(pm->ps->viewheight == CROUCH_VIEWHEIGHT && pm->ps->groundEntityNum != ENTITYNUM_NONE)) {
		PM_LadderMove();
	} else if (pml.walking) {
		// walking on ground
		PM_WalkMove();

		// NiceAss: New leg damage, based on the AQ2 leg damage code.
		if (pm->ps->stats[STAT_RQ3] & RQ3_LEGDAMAGE && pm->ps->groundEntityNum != ENTITYNUM_NONE) {
			int i;
			
			if ( (pm->cmd.serverTime % 600) < 250 ) {
				for (i = 0; i < 3; i++) {
					if ( i < 2 || pm->ps->velocity[2] > 0 )
						pm->ps->velocity[i] /= 4;
				}
			}
		}
	} else {
		// airborne
		PM_AirMove();
	}

	PM_Animate();

	// set groundentity, watertype, and waterlevel
	PM_GroundTrace();
	PM_SetWaterLevel();

	// weapons
	if (pm->predict) {
		PM_Reload();
		PM_Weapon();
	}

	// torso animation
	PM_TorsoAnimation();

	// footstep events / legs animations
	//Makro - ladder footsteps already handled in PM_LadderMove
	if (!pml.ladder)
		PM_Footsteps();

	// entering / leaving water splashes
	// JBravo: only if you are alive
	if (pm->ps->stats[STAT_HEALTH] > 0)
		PM_WaterEvents();

	// snap some parts of playerstate to save network bandwidth
	trap_SnapVector(pm->ps->velocity);
}

/*
================
Pmove

Can be called by either the server or the client
================
*/
void Pmove(pmove_t * pmove)
{
	int finalTime;

	finalTime = pmove->cmd.serverTime;

	if (finalTime < pmove->ps->commandTime) {
		return;		// should not happen
	}

	if (finalTime > pmove->ps->commandTime + 1000) {
		pmove->ps->commandTime = finalTime - 1000;
	}

	pmove->ps->pmove_framecount = (pmove->ps->pmove_framecount + 1) & ((1 << PS_PMOVEFRAMECOUNTBITS) - 1);

	// chop the move up if it is too long, to prevent framerate
	// dependent behavior
	while (pmove->ps->commandTime != finalTime) {
		int msec;

		msec = finalTime - pmove->ps->commandTime;

		if (pmove->pmove_fixed) {
			if (msec > pmove->pmove_msec) {
				msec = pmove->pmove_msec;
			}
		} else {
			if (msec > 66) {
				msec = 66;
			}
		}
		pmove->cmd.serverTime = pmove->ps->commandTime + msec;
		PmoveSingle(pmove);

		if (pmove->ps->pm_flags & PMF_JUMP_HELD) {
			pmove->cmd.upmove = 20;
		}
	}

	//PM_CheckStuck();

}
