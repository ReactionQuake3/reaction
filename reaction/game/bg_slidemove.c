//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.10  2002/02/04 02:05:28  jbravo
// removed an extraneous return value from a void routine
//
// Revision 1.9  2002/02/04 00:31:40  niceass
// oops =D
//
// Revision 1.8  2002/02/04 00:30:35  niceass
// New physics
//
// Revision 1.7  2002/01/11 19:48:30  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.6  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
// bg_slidemove.c -- part of bg_pmove functionality

#include "q_shared.h"
#include "bg_public.h"
#include "bg_local.h"

/*

input: origin, velocity, bounds, groundPlane, trace function

output: origin, velocity, impacts, stairup boolean

*/

#define	MIN_STEP_NORMAL	0.7		// can't step up onto very steep slopes
#define	MAX_CLIP_PLANES	5

void PM_StepSlideMove_ ( void ) {
	int			bumpcount, numbumps;
	vec3_t		dir;
	float		d;
	int			numplanes;
	vec3_t		planes[MAX_CLIP_PLANES];
	vec3_t		primal_velocity;
	int			i, j;
	trace_t		trace;
	vec3_t		end;
	float		time_left;

	numbumps = 4;
	numplanes = 0;
	time_left = pml.frametime;
	
	VectorCopy(pm->ps->velocity, primal_velocity);

	for (bumpcount=0 ; bumpcount<numbumps ; bumpcount++) {
		VectorMA(pm->ps->origin, time_left, pm->ps->velocity, end);

		pm->trace (&trace, pm->ps->origin, pm->mins, pm->maxs, end, pm->ps->clientNum, pm->tracemask);

		if (trace.allsolid) {
			// entity is completely trapped in another solid
			pm->ps->velocity[2] = 0;	// don't build up falling damage, but allow sideways acceleration
			return; // qtrue;
		}

		if (trace.fraction > 0) {
			// actually covered some distance
			VectorCopy (trace.endpos, pm->ps->origin);
			numplanes = 0;
		}

		if (trace.fraction == 1) {
			 break;		// moved the entire distance
		}

		// save entity for contact
		PM_AddTouchEnt( trace.entityNum );

		time_left -= time_left * trace.fraction;

		if (numplanes >= MAX_CLIP_PLANES) {
			// this shouldn't really happen
			VectorClear( pm->ps->velocity );
			break;
		}

		VectorCopy (trace.plane.normal, planes[numplanes]);
		numplanes++;
		
		for (i=0 ; i < numplanes ; i++)
		{
			PM_ClipVelocity(pm->ps->velocity, planes[i], pm->ps->velocity, OVERCLIP);  //1.01);
			for (j = 0; j < numplanes; j++)
				if (DotProduct (pm->ps->velocity, planes[j]) < 0 && j != i) break;

			// Get through all planes okay? Then stop clipping the velocity.
			if (j == numplanes) break;
		}

		// Clipped velocity against all planes
		if (i == numplanes) {
			if (numplanes != 2) {
				VectorClear(pm->ps->velocity);
				break;
			}
			else {
				CrossProduct (planes[0], planes[1], dir);
				d = DotProduct (dir, pm->ps->velocity);
				VectorScale (dir, d, pm->ps->velocity);
			}
		}

		if (DotProduct (pm->ps->velocity, primal_velocity) <= 0) {
			VectorClear(pm->ps->velocity);
			break;
		}
	}

	if (pm->ps->pm_time) {
		VectorCopy (primal_velocity, pm->ps->velocity);
	}
}

/*
==================
PM_StepSlideMove

==================
*/

void PM_StepSlideMove ( qboolean gravity )
{
	vec3_t		start_o, start_v;
	vec3_t		down_o, down_v;
	trace_t		trace;
	float		DistanceDown, DistanceUp;
	vec3_t		up, down;

	// use the step move
	vec3_t		old_normal;
	float		delta0;
	float		delta1;
	float		delta2;
	vec3_t		tmp_o;

	VectorCopy (pm->ps->origin, start_o);
	VectorCopy (pm->ps->velocity, start_v);

	PM_StepSlideMove_ ();

	VectorCopy (pm->ps->origin, down_o);
	VectorCopy (pm->ps->velocity, down_v);

	VectorCopy (start_o, up);
	up[2] += STEPSIZE;

	pm->trace (&trace, up, pm->mins, pm->maxs, up, pm->ps->clientNum, pm->tracemask);
	if (trace.allsolid) {
		return;		// can't step up
	}

	// try sliding above
	VectorCopy (up, pm->ps->origin);
	VectorCopy (start_v, pm->ps->velocity);

	PM_StepSlideMove_ ();

	// push down the final amount
	VectorCopy (pm->ps->origin, down);
	down[2] -= STEPSIZE;
	pm->trace (&trace, pm->ps->origin, pm->mins, pm->maxs, down, pm->ps->clientNum, pm->tracemask);
	if (!trace.allsolid)
	{
		VectorCopy (trace.endpos, pm->ps->origin);
	}

	VectorCopy(pm->ps->origin, up);

	VectorSubtract(down_o, start_o, tmp_o);
    DistanceDown = tmp_o[0]*tmp_o[0] + tmp_o[1]*tmp_o[1];
	VectorSubtract(up, start_o, tmp_o);
    DistanceUp = tmp_o[0]*tmp_o[0] + tmp_o[1]*tmp_o[1];

	//Com_Printf("%f ", trace.plane.normal[2]);
	if (DistanceDown > DistanceUp || trace.plane.normal[2] < MIN_STEP_NORMAL) {
		VectorCopy (down_o, pm->ps->origin);
		VectorCopy (down_v, pm->ps->velocity);
		return;
	}
	// Flat/walking up:
	else {
		//!! Special case
		// if we were walking along a plane, then we need to copy the Z over
		pm->ps->velocity[2] = down_v[2];
	}
	
	// NiceAss Move the origin up a little... Seems hackish but needed.
	VectorCopy(pm->ps->origin, tmp_o);
	tmp_o[2] += 0.01f;
	start_o[2] += 0.01f;

	// if the trace can trace back to the original position directly, don't step
	pm->trace ( &trace, tmp_o, pm->mins, pm->maxs, start_o, pm->ps->clientNum, pm->tracemask);
	// If it didn't make it all the way..

	if ( trace.fraction != 1.0 ) {
		// use the step move
		float	delta;

		delta = tmp_o[2] - start_o[2];
		if ( delta > 2 ) {
			if ( delta < 7 ) {
				PM_AddEvent( EV_STEP_4 );
			} else if ( delta < 11 ) {
				PM_AddEvent( EV_STEP_8 );
			} else if ( delta < 15 ) {
				PM_AddEvent( EV_STEP_12 );
			} else {
				PM_AddEvent( EV_STEP_16 );
			}
		}
		if ( pm->debugLevel ) {
			Com_Printf("%d:stepped\n", c_pmove);
		}
	}
}
