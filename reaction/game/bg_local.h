//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.9  2002/08/21 03:43:23  niceass
// allow clipvelocity outside of the bg_'s
//
// Revision 1.8  2002/06/29 02:51:16  niceass
// removed ladder stuff
//
// Revision 1.7  2002/06/16 20:06:14  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.6  2002/01/11 19:48:29  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.5  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
// bg_local.h -- local definitions for the bg (both games) files

#define	MIN_WALK_NORMAL	0.7f	// can't walk on very steep slopes

#define	STEPSIZE		18

#define	JUMP_VELOCITY	270

#define	TIMER_LAND		130
#define	TIMER_GESTURE	(34*66+50)

#define	OVERCLIP		1.001f

// all of the locals will be zeroed before each
// pmove, just to make damn sure we don't have
// any differences when running on client or server
typedef struct {
	vec3_t forward, right, up;
	float frametime;

	int msec;

	qboolean walking;
	qboolean groundPlane;
	trace_t groundTrace;
	qboolean ladder;	// We'll use this to tell when the player is on a ladder  (c3a tut)
	//qboolean previous_ladder;	// Elder: need this to see if player was on ladder
	qboolean opendoor;

	float impactSpeed;

	vec3_t previous_origin;
	vec3_t previous_velocity;
	int previous_waterlevel;
} pml_t;

extern pmove_t *pm;
extern pml_t pml;

// movement parameters
extern float pm_stopspeed;
extern float pm_duckScale;
extern float pm_swimScale;
extern float pm_wadeScale;

extern float pm_accelerate;
extern float pm_airaccelerate;
extern float pm_wateraccelerate;
extern float pm_flyaccelerate;

extern float pm_friction;
extern float pm_waterfriction;
extern float pm_flightfriction;

extern int c_pmove;

void PM_AddTouchEnt(int entityNum);
void PM_AddEvent(int newEvent);

//Elder: added
void PM_AddEvent2(int newEvent, int eventParm);

qboolean PM_SlideMove(qboolean gravity);
void PM_StepSlideMove(qboolean gravity);
