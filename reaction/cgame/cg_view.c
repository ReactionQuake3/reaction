//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.48  2005/02/15 16:33:38  makro
// Tons of updates (entity tree attachment system, UI vectors)
//
// Revision 1.47  2004/03/09 01:05:21  makro
// Flares
//
// Revision 1.46  2004/03/09 00:39:47  makro
// Flares
//
// Revision 1.45  2004/03/07 17:39:11  makro
// no message
//
// Revision 1.44  2004/01/28 23:26:33  makro
// Made flares additive
//
// Revision 1.43  2004/01/26 21:26:08  makro
// no message
//
// Revision 1.42  2003/09/20 19:38:16  makro
// Lens flares, what else ?
//
// Revision 1.41  2003/09/19 21:22:52  makro
// Flares
//
// Revision 1.40  2003/09/19 00:54:23  makro
// Flares again
//
// Revision 1.39  2003/09/18 19:05:10  makro
// Lens flares
//
// Revision 1.38  2003/09/17 23:49:29  makro
// Lens flares. Opendoor trigger_multiple fixes
//
// Revision 1.37  2003/09/07 22:19:27  makro
// Typo !
//
// Revision 1.36  2003/09/07 19:51:40  makro
// no message
//
// Revision 1.35  2003/08/10 20:13:26  makro
// no message
//
// Revision 1.34  2003/04/23 17:49:38  slicer
// Added new cvar cg_RQ3_ssgZoomSensLock
//
// Revision 1.33  2003/04/19 15:27:30  jbravo
// Backing out of most of unlagged.  Only optimized prediction and smooth clients
// remains.
//
// Revision 1.32  2003/04/13 21:58:00  slicer
// Added a Zoom Sensitivity Lock during fire sequence of ssg; removed unnecessary code
//
// Revision 1.31  2003/03/28 22:25:10  makro
// no message
//
// Revision 1.30  2003/03/09 21:30:38  jbravo
// Adding unlagged.   Still needs work.
//
// Revision 1.29  2002/09/01 21:14:37  makro
// Sky portal tweaks
//
// Revision 1.28  2002/08/29 23:58:28  makro
// Sky portals
//
// Revision 1.27  2002/08/29 04:42:41  blaze
// Anti OGC code
//
// Revision 1.26  2002/08/25 00:45:40  niceass
// q3f atmosphere
//
// Revision 1.25  2002/08/07 03:35:57  jbravo
// Added dynamic radio and stopped all radio usage during lca
//
// Revision 1.24  2002/07/13 22:42:18  makro
// Semi-working fog hull, semi-working sky portals (cgame code commented out)
// Basically, semi-working stuff :P
//
// Revision 1.23  2002/06/16 20:06:13  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.22  2002/06/12 23:01:06  slicer
// SSG Zooming final tweak
//
// Revision 1.21  2002/05/23 15:54:35  makro
// cg_RQ3_avidemo tweak
//
// Revision 1.20  2002/05/21 14:59:11  makro
// cg_RQ3_avidemo
//
// Revision 1.19  2002/03/07 14:51:57  makro
// no message
//
// Revision 1.18  2002/02/23 18:07:46  slicer
// Changed Sniper code and Cam code
//
// Revision 1.17  2002/01/12 20:00:49  hal9000
// Fixed a few more instances of strcmp(blah,NULL)
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
// cg_view.c -- setup all the parameters (position, angle, etc)
// for a 3D rendering
#include "cg_local.h"
//Blaze: Should come in handy for cheat detection
static float CG_Cvar_Get(const char *cvar)
{
	char buff[128];

	memset(buff, 0, sizeof(buff));
	trap_Cvar_VariableStringBuffer(cvar, buff, sizeof(buff));
	return atof(buff);
}

/*
=============================================================================

  MODEL TESTING

The viewthing and gun positioning tools from Q2 have been integrated and
enhanced into a single model testing facility.

Model viewing can begin with either "testmodel <modelname>" or "testgun <modelname>".

The names must be the full pathname after the basedir, like
"models/weapons/v_launch/tris.md3" or "players/male/tris.md3"

Testmodel will create a fake entity 100 units in front of the current view
position, directly facing the viewer.  It will remain immobile, so you can
move around it to view it from different angles.

Testgun will cause the model to follow the player around and supress the real
view weapon model.  The default frame 0 of most guns is completely off screen,
so you will probably have to cycle a couple frames to see it.

"nextframe", "prevframe", "nextskin", and "prevskin" commands will change the
frame or skin of the testmodel.  These are bound to F5, F6, F7, and F8 in
q3default.cfg.

If a gun is being tested, the "gun_x", "gun_y", and "gun_z" variables will let
you adjust the positioning.

Note that none of the model testing features update while the game is paused, so
it may be convenient to test with deathmatch set to 1 so that bringing down the
console doesn't pause the game.

=============================================================================
*/

/*
=================
CG_TestModel_f

Creates an entity in front of the current position, which
can then be moved around
=================
*/
void CG_TestModel_f(void)
{
	vec3_t angles;

	memset(&cg.testModelEntity, 0, sizeof(cg.testModelEntity));
	if (trap_Argc() < 2) {
		return;
	}

	Q_strncpyz(cg.testModelName, CG_Argv(1), MAX_QPATH);
	cg.testModelEntity.hModel = trap_R_RegisterModel(cg.testModelName);

	if (trap_Argc() == 3) {
		cg.testModelEntity.backlerp = atof(CG_Argv(2));
		cg.testModelEntity.frame = 1;
		cg.testModelEntity.oldframe = 0;
	}
	if (!cg.testModelEntity.hModel) {
		CG_Printf("Can't register model\n");
		return;
	}

	VectorMA(cg.refdef.vieworg, 100, cg.refdef.viewaxis[0], cg.testModelEntity.origin);

	angles[PITCH] = 0;
	angles[YAW] = 180 + cg.refdefViewAngles[1];
	angles[ROLL] = 0;

	AnglesToAxis(angles, cg.testModelEntity.axis);
	cg.testGun = qfalse;
}

/*
=================
CG_TestGun_f

Replaces the current view weapon with the given model
=================
*/
void CG_TestGun_f(void)
{
	CG_TestModel_f();
	cg.testGun = qtrue;
	cg.testModelEntity.renderfx = RF_MINLIGHT | RF_DEPTHHACK | RF_FIRST_PERSON;
}

void CG_TestModelNextFrame_f(void)
{
	cg.testModelEntity.frame++;
	CG_Printf("frame %i\n", cg.testModelEntity.frame);
}

void CG_TestModelPrevFrame_f(void)
{
	cg.testModelEntity.frame--;
	if (cg.testModelEntity.frame < 0) {
		cg.testModelEntity.frame = 0;
	}
	CG_Printf("frame %i\n", cg.testModelEntity.frame);
}

void CG_TestModelNextSkin_f(void)
{
	cg.testModelEntity.skinNum++;
	CG_Printf("skin %i\n", cg.testModelEntity.skinNum);
}

void CG_TestModelPrevSkin_f(void)
{
	cg.testModelEntity.skinNum--;
	if (cg.testModelEntity.skinNum < 0) {
		cg.testModelEntity.skinNum = 0;
	}
	CG_Printf("skin %i\n", cg.testModelEntity.skinNum);
}

static void CG_AddTestModel(void)
{
	int i;

	// re-register the model, because the level may have changed
	cg.testModelEntity.hModel = trap_R_RegisterModel(cg.testModelName);
	if (!cg.testModelEntity.hModel) {
		CG_Printf("Can't register model\n");
		return;
	}
	// if testing a gun, set the origin reletive to the view origin
	if (cg.testGun) {
		VectorCopy(cg.refdef.vieworg, cg.testModelEntity.origin);
		VectorCopy(cg.refdef.viewaxis[0], cg.testModelEntity.axis[0]);
		VectorCopy(cg.refdef.viewaxis[1], cg.testModelEntity.axis[1]);
		VectorCopy(cg.refdef.viewaxis[2], cg.testModelEntity.axis[2]);

		// allow the position to be adjusted
		for (i = 0; i < 3; i++) {
			cg.testModelEntity.origin[i] += cg.refdef.viewaxis[0][i] * cg_gun_x.value;
			cg.testModelEntity.origin[i] += cg.refdef.viewaxis[1][i] * cg_gun_y.value;
			cg.testModelEntity.origin[i] += cg.refdef.viewaxis[2][i] * cg_gun_z.value;
		}
	}

	trap_R_AddRefEntityToScene(&cg.testModelEntity);
}

//============================================================================

/*
=================
CG_CalcVrect

Sets the coordinates of the rendered window
=================
*/
static void CG_CalcVrect(void)
{
	int size;

	// the intermission should allways be full screen
	if (cg.snap->ps.pm_type == PM_INTERMISSION) {
		size = 100;
	} else {
		// bound normal viewsize
		if (cg_viewsize.integer < 30) {
			trap_Cvar_Set("cg_viewsize", "30");
			size = 30;
		} else if (cg_viewsize.integer > 100) {
			trap_Cvar_Set("cg_viewsize", "100");
			size = 100;
		} else {
			size = cg_viewsize.integer;
		}

	}
	cg.refdef.width = cgs.glconfig.vidWidth * size / 100;
	cg.refdef.width &= ~1;

	cg.refdef.height = cgs.glconfig.vidHeight * size / 100;
	cg.refdef.height &= ~1;

	cg.refdef.x = (cgs.glconfig.vidWidth - cg.refdef.width) / 2;
	cg.refdef.y = (cgs.glconfig.vidHeight - cg.refdef.height) / 2;
}

//==============================================================================

/*
===============
CG_OffsetThirdPersonView

===============
*/
#define	FOCUS_DISTANCE	512
static void CG_OffsetThirdPersonView(void)
{
	vec3_t forward, right, up;
	vec3_t view;
	vec3_t focusAngles;
	trace_t trace;
	static vec3_t mins = { -4, -4, -4 };
	static vec3_t maxs = { 4, 4, 4 };
	vec3_t focusPoint;
	float focusDist;
	float forwardScale, sideScale;

	cg.refdef.vieworg[2] += cg.predictedPlayerState.viewheight;

	VectorCopy(cg.refdefViewAngles, focusAngles);

	// if dead, look at killer
	if (cg.predictedPlayerState.stats[STAT_HEALTH] <= 0) {
		focusAngles[YAW] = cg.predictedPlayerState.stats[STAT_DEAD_YAW];
		cg.refdefViewAngles[YAW] = cg.predictedPlayerState.stats[STAT_DEAD_YAW];
	}

	if (focusAngles[PITCH] > 45) {
		focusAngles[PITCH] = 45;	// don't go too far overhead
	}
	AngleVectors(focusAngles, forward, NULL, NULL);

	VectorMA(cg.refdef.vieworg, FOCUS_DISTANCE, forward, focusPoint);

	VectorCopy(cg.refdef.vieworg, view);

	view[2] += 8;

	cg.refdefViewAngles[PITCH] *= 0.5;

	AngleVectors(cg.refdefViewAngles, forward, right, up);

	forwardScale = cos(cg_thirdPersonAngle.value / 180 * M_PI);
	sideScale = sin(cg_thirdPersonAngle.value / 180 * M_PI);
	VectorMA(view, -cg_thirdPersonRange.value * forwardScale, forward, view);
	VectorMA(view, -cg_thirdPersonRange.value * sideScale, right, view);

	// trace a ray from the origin to the viewpoint to make sure the view isn't
	// in a solid block.  Use an 8 by 8 block to prevent the view from near clipping anything

	if (!cg_cameraMode.integer) {
		CG_Trace(&trace, cg.refdef.vieworg, mins, maxs, view, cg.predictedPlayerState.clientNum, MASK_SOLID);

		if (trace.fraction != 1.0) {
			VectorCopy(trace.endpos, view);
			view[2] += (1.0 - trace.fraction) * 32;
			// try another trace to this position, because a tunnel may have the ceiling
			// close enogh that this is poking out

			CG_Trace(&trace, cg.refdef.vieworg, mins, maxs, view, cg.predictedPlayerState.clientNum,
				 MASK_SOLID);
			VectorCopy(trace.endpos, view);
		}
	}

	VectorCopy(view, cg.refdef.vieworg);

	// select pitch to look at focus point from vieword
	VectorSubtract(focusPoint, cg.refdef.vieworg, focusPoint);
	focusDist = sqrt(focusPoint[0] * focusPoint[0] + focusPoint[1] * focusPoint[1]);
	if (focusDist < 1) {
		focusDist = 1;	// should never happen
	}
	cg.refdefViewAngles[PITCH] = -180 / M_PI * atan2(focusPoint[2], focusDist);
	cg.refdefViewAngles[YAW] -= cg_thirdPersonAngle.value;
}

// this causes a compiler bug on mac MrC compiler
static void CG_StepOffset(void)
{
	int timeDelta;

	// smooth out stair climbing
	timeDelta = cg.time - cg.stepTime;
	if (timeDelta < STEP_TIME) {
		cg.refdef.vieworg[2] -= cg.stepChange * (STEP_TIME - timeDelta) / STEP_TIME;
	}
}

/*
===============
CG_OffsetFirstPersonView

===============
*/
static void CG_OffsetFirstPersonView(void)
{
	float *origin;
	float *angles;
	float bob;
	float ratio;
	float delta;
	float speed;
	float f;
	vec3_t predictedVelocity;
	int timeDelta;

	if (cg.snap->ps.pm_type == PM_INTERMISSION) {
		return;
	}

	origin = cg.refdef.vieworg;
	angles = cg.refdefViewAngles;

	// if dead, fix the angle and don't add any kick
	if (cg.snap->ps.stats[STAT_HEALTH] <= 0) {
		angles[ROLL] = 40;
		angles[PITCH] = -15;
		angles[YAW] = cg.snap->ps.stats[STAT_DEAD_YAW];
		origin[2] += cg.predictedPlayerState.viewheight;
		return;
	}
	// add angles based on weapon kick
	VectorAdd(angles, cg.kick_angles, angles);

	// add angles based on damage kick
	if (cg.damageTime) {
		ratio = cg.time - cg.damageTime;
		if (ratio < DAMAGE_DEFLECT_TIME) {
			ratio /= DAMAGE_DEFLECT_TIME;
			angles[PITCH] += ratio * cg.v_dmg_pitch;
			angles[ROLL] += ratio * cg.v_dmg_roll;
		} else {
			ratio = 1.0 - (ratio - DAMAGE_DEFLECT_TIME) / DAMAGE_RETURN_TIME;
			if (ratio > 0) {
				angles[PITCH] += ratio * cg.v_dmg_pitch;
				angles[ROLL] += ratio * cg.v_dmg_roll;
			}
		}
	}
	// add pitch based on fall kick
#if 0
	ratio = (cg.time - cg.landTime) / FALL_TIME;
	if (ratio < 0)
		ratio = 0;
	angles[PITCH] += ratio * cg.fall_value;
#endif

	// add angles based on velocity
	VectorCopy(cg.predictedPlayerState.velocity, predictedVelocity);

	delta = DotProduct(predictedVelocity, cg.refdef.viewaxis[0]);
	angles[PITCH] += delta * cg_runpitch.value;

	delta = DotProduct(predictedVelocity, cg.refdef.viewaxis[1]);
	angles[ROLL] -= delta * cg_runroll.value;

	// add angles based on bob

	// make sure the bob is visible even at low speeds
	speed = cg.xyspeed > 200 ? cg.xyspeed : 200;

	delta = cg.bobfracsin * cg_bobpitch.value * speed;
	if (cg.predictedPlayerState.pm_flags & PMF_DUCKED)
		delta *= 3;	// crouching
	angles[PITCH] += delta;
	delta = cg.bobfracsin * cg_bobroll.value * speed;
	if (cg.predictedPlayerState.pm_flags & PMF_DUCKED)
		delta *= 3;	// crouching accentuates roll
	if (cg.bobcycle & 1)
		delta = -delta;
	angles[ROLL] += delta;

//===================================

	// add view height
	origin[2] += cg.predictedPlayerState.viewheight;

	// smooth out duck height changes
	timeDelta = cg.time - cg.duckTime;
	if (timeDelta < DUCK_TIME) {
		cg.refdef.vieworg[2] -= cg.duckChange * (DUCK_TIME - timeDelta) / DUCK_TIME;
	}
	// add bob height
	bob = cg.bobfracsin * cg.xyspeed * cg_bobup.value;
	if (bob > 6) {
		bob = 6;
	}

	origin[2] += bob;

	// add fall height
	delta = cg.time - cg.landTime;
	if (delta < LAND_DEFLECT_TIME) {
		f = delta / LAND_DEFLECT_TIME;
		cg.refdef.vieworg[2] += cg.landChange * f;
	} else if (delta < LAND_DEFLECT_TIME + LAND_RETURN_TIME) {
		delta -= LAND_DEFLECT_TIME;
		f = 1.0 - (delta / LAND_RETURN_TIME);
		cg.refdef.vieworg[2] += cg.landChange * f;
	}
	// add step offset
	CG_StepOffset();

	// add kick offset

	VectorAdd(origin, cg.kick_origin, origin);

	// pivot the eye based on a neck length
#if 0
	{
#define	NECK_LENGTH		8
		vec3_t forward, up;

		cg.refdef.vieworg[2] -= NECK_LENGTH;
		AngleVectors(cg.refdefViewAngles, forward, NULL, up);
		VectorMA(cg.refdef.vieworg, 3, forward, cg.refdef.vieworg);
		VectorMA(cg.refdef.vieworg, NECK_LENGTH, up, cg.refdef.vieworg);
	}
#endif

	// Weapon kick management
	if (cg.kick_time) {
		int duration;

		if (cg.kick_duration)
			duration = cg.kick_duration;
		else
			duration = KICK_TIME;

		if (cg.time - cg.kick_time >= duration) {
			// Elder: clear kick origin and angles
			VectorClear(cg.kick_angles);
			VectorClear(cg.kick_origin);
			cg.kick_time = 0;
			cg.kick_duration = 0;
		} else {
			// Decay them
			cg.kick_angles[0] = cg.kick_angles[0] * (1 - (float) (cg.time - cg.kick_time) / duration);
			cg.kick_angles[1] = cg.kick_angles[1] * (1 - (float) (cg.time - cg.kick_time) / duration);
			cg.kick_angles[2] = cg.kick_angles[2] * (1 - (float) (cg.time - cg.kick_time) / duration);
			cg.kick_origin[0] = cg.kick_origin[0] * (1 - (float) (cg.time - cg.kick_time) / duration);
			cg.kick_origin[1] = cg.kick_origin[1] * (1 - (float) (cg.time - cg.kick_time) / duration);
			cg.kick_origin[2] = cg.kick_origin[2] * (1 - (float) (cg.time - cg.kick_time) / duration);
		}
		/*
		   CG_Printf("Kick Angles: (%f %f %f) Origin: (%f %f %f)\n",
		   cg.kick_angles[0], cg.kick_angles[1], cg.kick_angles[2],
		   cg.kick_origin[0], cg.kick_origin[1], cg.kick_origin[2]);
		 */
	}
}

//======================================================================

/* hawkins: not needed in rxn as is. however, useful for SSG. */
/*
void CG_ZoomDown_f( void ) {
	if ( cg.zoomed ) {
		return;
	}
	cg.zoomed = qtrue;
	cg.zoomTime = cg.time;
}

void CG_ZoomUp_f( void ) {
	if ( !cg.zoomed ) {
		return;
	}
	cg.zoomed = qfalse;
	cg.zoomTime = cg.time;
}
*/

/*
====================
CG_RQ3_GetFov

Returns a FOV based on the current zoom state
====================
*/

static int CG_RQ3_GetFov()
{
	if ((cg.zoomLevel & RQ3_ZOOM_LOW) == RQ3_ZOOM_LOW && (cg.zoomLevel & RQ3_ZOOM_MED) == RQ3_ZOOM_MED)
		return 10;
	else if ((cg.zoomLevel & RQ3_ZOOM_MED) == RQ3_ZOOM_MED)
		return 20;
	else if ((cg.zoomLevel & RQ3_ZOOM_LOW) == RQ3_ZOOM_LOW)
		return 45;

	return 90;
}

/*
====================
CG_RQ3_GetFov

Returns a FOV based on the last zoom state
====================
*/

static int CG_RQ3_GetLastFov()
{
	if ((cg.lastZoomLevel & RQ3_ZOOM_LOW) == RQ3_ZOOM_LOW && (cg.lastZoomLevel & RQ3_ZOOM_MED) == RQ3_ZOOM_MED)
		return 10;
	else if ((cg.lastZoomLevel & RQ3_ZOOM_MED) == RQ3_ZOOM_MED)
		return 20;
	else if ((cg.lastZoomLevel & RQ3_ZOOM_LOW) == RQ3_ZOOM_LOW)
		return 45;

	return 90;
}

/*
====================
CG_CalcFov

Fixed fov at intermissions, otherwise account for fov variable and zooms.
====================
*/
#define	WAVE_AMPLITUDE	1
#define	WAVE_FREQUENCY	0.4

static int CG_CalcFov(void)
{
	float x;
	float phase;
	float v;
	int contents;
	float fov_x, fov_y;	//Current zoom
	float zoomFov;		//Desired zoom
	float f;
	int inwater;

	if (cg.predictedPlayerState.pm_type == PM_INTERMISSION) {
		fov_x = 90;
	}
	// Slicer: Updates the cg.zoomLevel with the info sent by server
	CG_RQ3_SyncZoom();

	//Slicer
	cg.zoomSensLock = qfalse;
	
	if (cg.snap->ps.weapon == WP_SSG3000) {
		//switching zoom
		if (cg.zoomLevel != cg.lastZoomLevel) {
	
			//Slicer
			if (!cg.zooming) {	// If this is the first zooming attempt
				cg.zoomTime = cg.time;	// Lets set the time
				cg.zooming = qtrue;	// and disable the IF condition
			}

			fov_x = CG_RQ3_GetLastFov();
			//Get desired zoom FOV based on current FOV
			if (cg.zoomLevel == 0) {
				zoomFov = 90;
				cg.zoomed = qfalse;
			} else {
				switch ((int) fov_x) {
				case 20:
					zoomFov = 10;
					cg.zoomed = qtrue;
					break;
				case 45:
					zoomFov = 20;
					cg.zoomed = qtrue;
					break;
				case 90:
					zoomFov = 45;
					cg.zoomed = qtrue;
					break;
				case 10:
				default:
					zoomFov = 90;
					cg.zoomed = qfalse;
					break;
				}
			}

			f = (cg.time - cg.zoomTime) / (float) ZOOM_TIME;
			if (f > 1.0 || cg.zoomFirstReturn == ZOOM_OUT) {
				//finished zoom switch
				cg.lastZoomLevel = cg.zoomLevel;
				fov_x = zoomFov;
				//Slicer : zoom has finished, so the next one needs to have a new zoomTime
				cg.zooming = qfalse;
			} else
				fov_x = fov_x + f * (zoomFov - fov_x);
		}
		//Idle state
		else if (cg.snap->ps.weaponTime == 0 && cg.snap->ps.weaponstate == WEAPON_READY) {
			fov_x = CG_RQ3_GetFov();
			if (fov_x == 90) {
				cg.zoomed = qfalse;
			}
			else
				cg.zoomed = qtrue;

			if (cg.lowAmmoWarning)
				cg.zoomFirstReturn = ZOOM_OUTOFAMMO;
			else
				cg.zoomFirstReturn = ZOOM_IDLE;
		}
		//Zoom back in after a reload or fire
		else if (cg.snap->ps.weaponTime < ZOOM_TIME &&
			 !(cg.snap->ps.weaponstate == WEAPON_DROPPING ||
			   cg.snap->ps.weaponstate == WEAPON_RAISING) &&
			 cg.snap->ps.stats[STAT_RELOADTIME] < ZOOM_TIME &&
			 !(cg.snap->ps.stats[STAT_RQ3] & RQ3_FASTRELOADS)) {
			if (cg.zoomFirstReturn == ZOOM_OUT) {
				cg.zoomTime = cg.time;
				if (cg.lowAmmoWarning)
					cg.zoomFirstReturn = ZOOM_OUTOFAMMO;
				else
					cg.zoomFirstReturn = ZOOM_IDLE;
			}

			fov_x = 90;
			zoomFov = CG_RQ3_GetFov();


			if (zoomFov == 90)
				cg.zoomed = qfalse;
			else
				cg.zoomed = qtrue;

			f = (cg.time - cg.zoomTime) / (float) ZOOM_TIME;
			if (f > 1.0)	//|| cg.zoomFirstReturn == ZOOM_OUTOFAMMO)
				fov_x = zoomFov;
			else
				fov_x = fov_x + f * (zoomFov - fov_x);
			//fov_x = zoomFov + f * ( fov_x - zoomFov );
		}
		//first time after a shot, reload, or weapon switch - zoom out
		else {
			fov_x = CG_RQ3_GetFov();
			//Slicer: if the weapon is about to go to firing sequence, lock the zoomSensitivity
			if(cg.snap->ps.weaponstate == WEAPON_FIRING && cg_RQ3_ssgZoomSensLock.value)
				cg.zoomSensLock = qtrue;

			if (cg.snap->ps.weaponstate == WEAPON_RELOADING && cg.zoomFirstReturn != ZOOM_OUT) {
				cg.zoomTime = cg.time;
				cg.zoomFirstReturn = ZOOM_OUT;
			} else if (cg.zoomFirstReturn == ZOOM_IDLE &&
				   !(cg.snap->ps.weaponstate == WEAPON_DROPPING
				     || cg.snap->ps.weaponstate == WEAPON_RAISING)) {
				cg.zoomTime = cg.time;
				cg.zoomFirstReturn = ZOOM_OUT;
			}

			if (cg.zoomFirstReturn == ZOOM_OUTOFAMMO) {
				zoomFov = fov_x;
				f = 1.0f;	// don't bother zooming out
			} else {
				zoomFov = 90;
				f = (cg.time - cg.zoomTime) / (float) ZOOM_TIME;
			}

			if (f > 1.0) {
				fov_x = zoomFov;
				if (fov_x == 90)
					cg.zoomed = qfalse;
				else
					cg.zoomed = qtrue;
			} else
				fov_x = fov_x + f * (zoomFov - fov_x);
		}

	}
	//Using anything but the SSG3000
	else {
		//Always at 90 degrees
		fov_x = 90;
		cg.zoomed = qfalse;
		cg.zoomSensLock = qfalse;
	}

	x = cg.refdef.width / tan(fov_x / 360 * M_PI);
	fov_y = atan2(cg.refdef.height, x);
	fov_y = fov_y * 360 / M_PI;

	// warp if underwater
	contents = CG_PointContents(cg.refdef.vieworg, -1);
	if (contents & (CONTENTS_WATER | CONTENTS_SLIME | CONTENTS_LAVA)) {
		phase = cg.time / 1000.0 * WAVE_FREQUENCY * M_PI * 2;
		v = WAVE_AMPLITUDE * sin(phase);
		fov_x += v;
		fov_y -= v;
		inwater = qtrue;
	} else {
		inwater = qfalse;
	}

	// set it
	cg.refdef.fov_x = fov_x;
	cg.refdef.fov_y = fov_y;
	//Slicer: Don't calculate new values for the zoomSensitivity when doing the firing sequence
	if(!cg.zoomSensLock) {
		if (!cg.zoomed ) {
		cg.zoomSensitivity = 1;
		} else {
			if (cg_RQ3_ssgSensitivityAuto.integer)
				cg.zoomSensitivity = cg.refdef.fov_y / 75.0;
			else {
				// Use user-defined sensitivites
				switch ((int) fov_x) {
				case 45:
					cg.zoomSensitivity = cg_RQ3_ssgSensitivity2x.value;
					break;
				case 20:
					cg.zoomSensitivity = cg_RQ3_ssgSensitivity4x.value;
					break;
				case 10:
					cg.zoomSensitivity = cg_RQ3_ssgSensitivity6x.value;
					break;
				}
			}
		}
	}

	return inwater;
}

/*
===============
CG_DamageBlendBlob

===============
*/
static void CG_DamageBlendBlob(void)
{
	int t;
	int maxTime;
	refEntity_t ent;

	if (!cg.damageValue) {
		return;
	}
	//if (cg.cameraMode) {
	//      return;
	//}

	// ragePro systems can't fade blends, so don't obscure the screen
	if (cgs.glconfig.hardwareType == GLHW_RAGEPRO) {
		return;
	}

	maxTime = DAMAGE_TIME;
	t = cg.time - cg.damageTime;
	if (t <= 0 || t >= maxTime) {
		return;
	}

	memset(&ent, 0, sizeof(ent));
	ent.reType = RT_SPRITE;
	ent.renderfx = RF_FIRST_PERSON;

	VectorMA(cg.refdef.vieworg, 8, cg.refdef.viewaxis[0], ent.origin);
	VectorMA(ent.origin, cg.damageX * -8, cg.refdef.viewaxis[1], ent.origin);
	VectorMA(ent.origin, cg.damageY * 8, cg.refdef.viewaxis[2], ent.origin);

	ent.radius = cg.damageValue * 3;
	ent.customShader = cgs.media.viewBloodShader;
	ent.shaderRGBA[0] = 255;
	ent.shaderRGBA[1] = 255;
	ent.shaderRGBA[2] = 255;
	ent.shaderRGBA[3] = 200 * (1.0 - ((float) t / maxTime));
	trap_R_AddRefEntityToScene(&ent);
}

/*
===============
CG_CalcViewValues

Sets cg.refdef view values
===============
*/
static int CG_CalcViewValues(void)
{
	playerState_t *ps;

	memset(&cg.refdef, 0, sizeof(cg.refdef));

	// strings for in game rendering
	// Q_strncpyz( cg.refdef.text[0], "Park Ranger", sizeof(cg.refdef.text[0]) );
	// Q_strncpyz( cg.refdef.text[1], "19", sizeof(cg.refdef.text[1]) );

	// calculate size of 3D view
	CG_CalcVrect();

	ps = &cg.predictedPlayerState;
/*
	if (cg.cameraMode) {
		vec3_t origin, angles;
		if (trap_getCameraInfo(cg.time, &origin, &angles)) {
			VectorCopy(origin, cg.refdef.vieworg);
			angles[ROLL] = 0;
			VectorCopy(angles, cg.refdefViewAngles);
			AnglesToAxis( cg.refdefViewAngles, cg.refdef.viewaxis );
			return CG_CalcFov();
		} else {
			cg.cameraMode = qfalse;
		}
	}
*/
	// intermission view
	if (ps->pm_type == PM_INTERMISSION) {
		VectorCopy(ps->origin, cg.refdef.vieworg);
		VectorCopy(ps->viewangles, cg.refdefViewAngles);
		AnglesToAxis(cg.refdefViewAngles, cg.refdef.viewaxis);
		return CG_CalcFov();
	}

	cg.bobcycle = (ps->bobCycle & 128) >> 7;
	cg.bobfracsin = fabs(sin((ps->bobCycle & 127) / 127.0 * M_PI));
	cg.xyspeed = sqrt(ps->velocity[0] * ps->velocity[0] + ps->velocity[1] * ps->velocity[1]);

	VectorCopy(ps->origin, cg.refdef.vieworg);
	VectorCopy(ps->viewangles, cg.refdefViewAngles);

	if (cg_cameraOrbit.integer) {
		if (cg.time > cg.nextOrbitTime) {
			cg.nextOrbitTime = cg.time + cg_cameraOrbitDelay.integer;
			cg_thirdPersonAngle.value += cg_cameraOrbit.value;
		}
	}
	// add error decay
	if (cg_errorDecay.value > 0) {
		int t;
		float f;

		t = cg.time - cg.predictedErrorTime;
		f = (cg_errorDecay.value - t) / cg_errorDecay.value;
		if (f > 0 && f < 1) {
			VectorMA(cg.refdef.vieworg, f, cg.predictedError, cg.refdef.vieworg);
		} else {
			cg.predictedErrorTime = 0;
		}
	}

	if (cg.renderingThirdPerson) {
		// back away from character
		CG_OffsetThirdPersonView();
	} else {
		// offset for local bobbing and kicks
		CG_OffsetFirstPersonView();
	}

	// position eye reletive to origin
	AnglesToAxis(cg.refdefViewAngles, cg.refdef.viewaxis);

	if (cg.hyperspace) {
		cg.refdef.rdflags |= RDF_NOWORLDMODEL | RDF_HYPERSPACE;
	}
	// field of view
	return CG_CalcFov();
}

/*
=====================
CG_PowerupTimerSounds
=====================
*/
static void CG_PowerupTimerSounds(void)
{
	int i;
	int t;

	// powerup timers going away
	for (i = 0; i < MAX_POWERUPS; i++) {
		t = cg.snap->ps.powerups[i];
		if (t <= cg.time) {
			continue;
		}
		if (t - cg.time >= POWERUP_BLINKS * POWERUP_BLINK_TIME) {
			continue;
		}
		if ((t - cg.time) / POWERUP_BLINK_TIME != (t - cg.oldTime) / POWERUP_BLINK_TIME) {
			trap_S_StartSound(NULL, cg.snap->ps.clientNum, CHAN_ITEM, cgs.media.wearOffSound);
		}
	}
}

/*
=====================
CG_AddBufferedSound
=====================
*/
void CG_AddBufferedSound(sfxHandle_t sfx)
{
	if (!sfx)
		return;
	cg.soundBuffer[cg.soundBufferIn] = sfx;
	cg.soundBufferIn = (cg.soundBufferIn + 1) % MAX_SOUNDBUFFER;
	if (cg.soundBufferIn == cg.soundBufferOut) {
		cg.soundBufferOut++;
	}
}

/*
=====================
CG_PlayBufferedSounds
=====================
*/
static void CG_PlayBufferedSounds(void)
{
	if (cg.soundTime < cg.time) {
		if (cg.soundBufferOut != cg.soundBufferIn && cg.soundBuffer[cg.soundBufferOut]) {
			trap_S_StartLocalSound(cg.soundBuffer[cg.soundBufferOut], CHAN_ANNOUNCER);
			cg.soundBuffer[cg.soundBufferOut] = 0;
			cg.soundBufferOut = (cg.soundBufferOut + 1) % MAX_SOUNDBUFFER;
			cg.soundTime = cg.time + 1100;
		}
	}
}

//=========================================================================


#define FLARE_FADEOUT_TIME	200
#define FLARE_BLIND_ALPHA	0.25f

void CG_AddLensFlare(qboolean sun)
{
	vec3_t dir, dp;

	if (cgs.numFlares <= 0 && (cgs.sunFlareSize <= 0 || cgs.sunAlpha == 0))
		return;
 
	if (sun)
	{
		float PI180 = M_PI/180, pitch, yaw, cx, cy,
			hfovx = cg.refdef.fov_x/2, hfovy = cg.refdef.fov_y/2;
		vec3_t end;
		trace_t tr;
		int timeDelta = 0, visible = 0;

		cgs.flareFadeFactor = 0.0f;

		VectorCopy(cgs.sunDir, dir);
		dp[0] = DotProduct(dir, cg.refdef.viewaxis[0]);
		dp[1] = DotProduct(dir, cg.refdef.viewaxis[1]);
		dp[2] = DotProduct(dir, cg.refdef.viewaxis[2]);

		//do a trace in the direction of the sun
		VectorMA(cg.refdef.vieworg, 16384, dir, end);
		CG_Trace(&tr, cg.refdef.vieworg, NULL, NULL, end, 0, CONTENTS_SOLID);
		//if we hit the sky
		if (tr.surfaceFlags & SURF_SKY)
		{
			yaw = 90.0f - acos(dp[1])/PI180;
			pitch = 90.0f - acos(dp[2])/PI180;
			
			cgs.flareForwardFactor = dp[0];
			//if the sun is in fov
			if (cgs.flareForwardFactor > 0 && abs(yaw) <= hfovx && abs(pitch) <= hfovy) {
				//get the screen co-ordinates of the sun
#if 0
				cx = 320 * (1.0f - dp[1] / (cos(yaw * PI180) * tan(hfovx * PI180)));
				cy = 240 * (1.0f - dp[2] / (cos(pitch * PI180) * tan(hfovy * PI180)));
#else
				//if we really needed them to be accurate, those above would be best
				//but we actually don't !
				cx = 320 * (1.0f - dp[1]);
				cy = 240 * (1.0f - dp[2]);
#endif
				cgs.lastSunX = cx;
				cgs.lastSunY = cy;
				cgs.lastSunTime = cg.time;
				visible = qtrue;
				cgs.flareFadeFactor = 1.0f;
			}
			//Note - we could do more traces if we hit transparent objects instead
			//of the sky for example, but that would slow things down
		}
		if (!visible && cgs.lastSunTime) {
			timeDelta = cg.time - cgs.lastSunTime;
			if (timeDelta > FLARE_FADEOUT_TIME)
			{
				cgs.lastSunTime = 0;
				return;
			}
			cgs.flareFadeFactor = 1.0f - (float)timeDelta / FLARE_FADEOUT_TIME;
		}
		//global vars
		if (cg.refdef.fov_x < 90)
			cgs.flareFovFactor = 5 - 0.05f * cg.refdef.fov_x;
		else
			cgs.flareFovFactor = 1.0f;
		//finally, add the sun
		if (cgs.sunFlareSize > 0 && cgs.sunAlpha > 0 && cgs.flareFadeFactor != 0.0f) {
			refEntity_t ent;

			memset(&ent, 0, sizeof(ent));
			VectorCopy(tr.endpos, ent.origin);
			ent.reType = RT_SPRITE;
			ent.customShader = cgs.media.sunFlareShader;
			//this function wouldn't be complete without some funny math
			//this makes the sprite as big as the mapper wanted it to be
			ent.radius = cgs.sunFlareSize * tr.fraction * 25.6f;
			ent.renderfx = RF_DEPTHHACK;
			ent.shaderRGBA[0] = cgs.flareFadeFactor * cgs.sunAlpha * 255;
			ent.shaderRGBA[1] = ent.shaderRGBA[0];
			ent.shaderRGBA[2] = ent.shaderRGBA[0];
			ent.shaderRGBA[3] = ent.shaderRGBA[0];
			trap_R_AddRefEntityToScene(&ent);
		}
		//speed hack
		cgs.flareFadeFactor *= cg_RQ3_flareIntensity.value;
	} else {
		//add the reflection particles
		if (cgs.flareFadeFactor != 0.0f)
		{
			float len = 0, color[4];
			float size, hsize;
			float ffov = cos(cg.refdef.fov_y/4);
			int i;
			
			VectorSet(dir, 320-cgs.lastSunX, 240-cgs.lastSunY, 0);
			len = 2 * VectorNormalize(dir);
			for (i=0; i<cgs.numFlares; i++) {
				float alpha = cg.flareColor[i][3] * cgs.flareFadeFactor;
				size = cg.flareShaderSize[i] * cgs.flareFovFactor;
				hsize = size/2.0f;
				dp[2] = len / cgs.numFlares * (i+1);
				dp[0] = cgs.lastSunX + dp[2] * dir[0];
				dp[1] = cgs.lastSunY + dp[2] * dir[1];
				color[0] = cg.flareColor[i][0] * alpha;
				color[1] = cg.flareColor[i][1] * alpha;
				color[2] = cg.flareColor[i][2] * alpha;
				color[3] = 1.0f;
				trap_R_SetColor(color);
				CG_DrawPic(dp[0] - hsize, dp[1] - hsize, size, size,
					cgs.media.flareShader[cg.flareShaderNum[i]]);
			}
			if (cgs.flareForwardFactor > ffov)
			{
				color[0] = color[1] = color[2] = 1.0f;
				//color[3] = cgs.sunAlpha * cgs.flareForwardFactor * cgs.flareFadeFactor * FLARE_BLIND_ALPHA;
				color[3] = (cgs.flareForwardFactor - ffov) / (1 - ffov) * cgs.flareFadeFactor * FLARE_BLIND_ALPHA;
				//Makro - too expensive
				//color[3] = cgs.sunAlpha * cgs.flareFadeFactor * FLARE_BLIND_ALPHA * (1.0f - abs(320 - cgs.lastSunX) / 320.0f) * (1.0f - abs(240 - cgs.lastSunY) / 240.0f);
				CG_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color);
			}
		}
	}
}


/*
=================
CG_DrawActiveFrame

Generates and draws a game scene and status information at the given time.
=================
*/
void CG_DrawActiveFrame(int serverTime, stereoFrame_t stereoView, qboolean demoPlayback)
{
	int inwater;
	int skyPortalMode = ADDENTS_NOSKYPORTAL;
	float aviDemoFPS = 0;

	//Blaze: for cheat detection
	int i;
	float cvar_val;

	//end Blaze
	cg.time = serverTime;

	cg.demoPlayback = demoPlayback;

	// update cvars
	CG_UpdateCvars();

	// if we are only updating the screen as a loading
	// pacifier, don't even try to read snapshots
	if (cg.infoScreenText[0] != 0) {
		CG_DrawInformation();
		return;
	}
	// any looped sounds will be respecified as entities
	// are added to the render list
	trap_S_ClearLoopingSounds(qfalse);

	// clear all the render lists
	trap_R_ClearScene();

	// set up cg.snap and possibly cg.nextSnap
	CG_ProcessSnapshots();

	// if we haven't received any snapshots yet, all
	// we can draw is the information screen
	if (!cg.snap || (cg.snap->snapFlags & SNAPFLAG_NOT_ACTIVE)) {
		CG_DrawInformation();
		return;
	}
	// let the client system know what our weapon and zoom settings are
	trap_SetUserCmdValue(cg.weaponSelect, cg.zoomSensitivity);

	// this counter will be bumped for every valid scene we generate
	cg.clientFrame++;

	// update cg.predictedPlayerState
	CG_PredictPlayerState();

	// decide on third person view
	// Elder: remove third-person death rendering
	cg.renderingThirdPerson = cg_thirdPerson.integer;	//|| (cg.snap->ps.stats[STAT_HEALTH] <= 0);

	// build cg.refdef
	inwater = CG_CalcViewValues();

	// first person blend blobs, done after AnglesToAxis
	if (!cg.renderingThirdPerson) {
		CG_DamageBlendBlob();
	}

	//Makro - these were a few lines below
	cg.refdef.time = cg.time;
	memcpy(cg.refdef.areamask, cg.snap->areamask, sizeof(cg.refdef.areamask));

	//Makro - fog hull
	if (cgs.clearColorSet) {
		float fogcolor[4];
		fogcolor[0] = cgs.clearColor[0];
		fogcolor[1] = cgs.clearColor[1];
		fogcolor[2] = cgs.clearColor[2];
		fogcolor[3] = 1.0f;
		CG_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, fogcolor);
	}
	//CG_DrawBigPolygon();

	//Makro - draw sky portal first
	if (cgs.skyPortalSet) {
		vec3_t oldOrigin;
		CG_AddPacketEntities(ADDENTS_SKYPORTAL);
		skyPortalMode = ADDENTS_NORMAL;
		VectorCopy(cg.refdef.vieworg, oldOrigin);
		VectorCopy(cgs.skyPortalOrigin, cg.refdef.vieworg);
		trap_R_RenderScene(&cg.refdef);
		VectorCopy(oldOrigin, cg.refdef.vieworg);
	}

	// build the render lists
	if (!cg.hyperspace) {
		CG_AddPacketEntities(skyPortalMode);	// adter calcViewValues, so predicted player state is correct
		CG_AddMarks();
		CG_AddParticles();
		CG_AddLocalEntities();
		CG_AddAtmosphericEffects();  	  	// q3f atmospheric stuff: Add rain/snow etc.
	}
	CG_AddViewWeapon(&cg.predictedPlayerState);

	//Elder: check local laser status
	//CG_CheckLaser();

	// add buffered sounds
	CG_PlayBufferedSounds();

	// play buffered voice chats
	CG_PlayBufferedVoiceChats();

	// finish up the rest of the refdef
	if (cg.testModelEntity.hModel) {
		CG_AddTestModel();
	}

	//Makro - moved a few lines up, before the sky portal code
	//cg.refdef.time = cg.time;
	//memcpy(cg.refdef.areamask, cg.snap->areamask, sizeof(cg.refdef.areamask));

	// warning sounds when powerup is wearing off
	CG_PowerupTimerSounds();

	// update audio positions
	trap_S_Respatialize(cg.snap->ps.clientNum, cg.refdef.vieworg, cg.refdef.viewaxis, inwater);

	// make sure the lagometerSample and frame timing isn't done twice when in stereo
	if (stereoView != STEREO_RIGHT) {
		cg.frametime = cg.time - cg.oldTime;
		if (cg.frametime < 0) {
			cg.frametime = 0;
		}
		cg.oldTime = cg.time;
		CG_AddLagometerFrameInfo();
	}
	if (cg_timescale.value != cg_timescaleFadeEnd.value) {
		if (cg_timescale.value < cg_timescaleFadeEnd.value) {
			cg_timescale.value += cg_timescaleFadeSpeed.value * ((float) cg.frametime) / 1000;
			if (cg_timescale.value > cg_timescaleFadeEnd.value)
				cg_timescale.value = cg_timescaleFadeEnd.value;
		} else {
			cg_timescale.value -= cg_timescaleFadeSpeed.value * ((float) cg.frametime) / 1000;
			if (cg_timescale.value < cg_timescaleFadeEnd.value)
				cg_timescale.value = cg_timescaleFadeEnd.value;
		}
		if (cg_timescaleFadeSpeed.value) {
			trap_Cvar_Set("timescale", va("%f", cg_timescale.value));
		}
	}

	// actually issue the rendering calls
	CG_DrawActive(stereoView);

	if (cg_stats.integer) {
		CG_Printf("cg.clientFrame:%i\n", cg.clientFrame);
	}
	//if ((cg.time - cgs.levelStartTime) / 10000 == 1)
	// Elder: working timer implementation
	if (cg.time > cg.cvarCheckTime) {
		//cg.cvarCheckTime = cg.time + 5000 + rand() % 6000;
		cg.cvarCheckTime = cg.time + 10000;
		if (0 == CG_Cvar_Get("ogc_islame"))
		{
			Com_Error(ERR_DISCONNECT, "No OGC plzkthx");
		}
		//Blaze: Check for invalid video settings.
		for (i = 0; i < 30; i++) {
			if (strcmp(cheats[i].cvar, "") != 0) {
				cvar_val = CG_Cvar_Get(cheats[i].cvar);
				//CG_Printf("%s is set to %f\n",cheats[i].cvar, cvar_val);
				if ((cvar_val < cheats[i].low || cvar_val > cheats[i].high)) {
					CG_Printf("This server restricts %s to be between %1.11f and %1.11f\n",
						  cheats[i].cvar, cheats[i].low, cheats[i].high);
					//Makro - a Com_Error would be nicer
					//trap_Cvar_Set("RQ3_CvarKickReason", cheats[i].cvar );
					//trap_SendConsoleCommand(va("disconnect\n"));
					Com_Error(ERR_DISCONNECT,
						  "WARNING: You have been disconnected from the server because %s was out of range (%f - %f)",
						  cheats[i].cvar, cheats[i].low, cheats[i].high);
				}

			}

		}
	}
	//Makro - like cl_avidemo, just that it uses JPEG's
	aviDemoFPS = cg_RQ3_avidemo.value;
	if (aviDemoFPS > 0) {
		//if it's time to take a screenshot
		if (cg.time > cg.screenshotTime + (int) (1000.0f / aviDemoFPS)) {
			trap_SendConsoleCommand("screenshotJPEG silent\n");
			cg.screenshotTime = cg.time;
		}
	}
}
