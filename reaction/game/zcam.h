//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.7  2002/03/30 17:59:27  jbravo
// Forgot a * on *ent
//
// Revision 1.6  2002/03/30 17:57:48  jbravo
// Two functions added to zcam.h for g_active.c
//
// Revision 1.5  2002/02/10 16:26:55  jbravo
// Attempting to intergrate zcam better into rq3 and a fix for lights.wav
//
// Revision 1.4  2002/02/09 01:07:14  jbravo
// Added zcam files
//
//
//-----------------------------------------------------------------------------

/* 
 *  ZCam v1.0.4
 *  Spectator Camera for Quake III Arena
 *  Copyright (C), 2001 by Avi "Zung!" Rozen
 *	
 *  http://www.telefragged.com/zungbang/zcam
 *
 *  Credits:
 *  FLIC  camera mode is based on code  taken from q2cam by Paul Jordan
 *  SWING camera mode is based on ideas taken from CreepCam for Quake I 
 *
 */ 

#ifndef __ZCAM_H__
#define __ZCAM_H__

#define MAX_VISIBLE_RANGE		1000

void camera_init (void);
void camera_shutdown (void);
void camera_state_save (gclient_t *client);
void camera_state_load (gclient_t *client);
void camera_begin (gentity_t *ent);
void camera_disconnect (gentity_t *ent);
void camera_think (gentity_t *ent);
void camera_cmd (gentity_t *ent);
void CameraFlicBegin (gentity_t *ent);
void CameraSwingCycle (gentity_t *ent, int dir);

// JBravo: moved from zcam.c to here:
/* camera mode */
typedef enum camera_mode_e {
	CAMERA_MODE_FLIC,
	CAMERA_MODE_SWING
} camera_mode_t;

/* camera data */
typedef struct camera_s
{
	camera_mode_t mode;	// camera mode

	// swing mode
	float		swing_distance;		// distance behind player
	float		swing_height;		// height of camera
	float		swing_angle;		// angle of camera
	float		swing_yaw;		// yaw of camera
	float		swing_pitch;		// pitch of camera
	gentity_t	*swing_target;
	gentity_t	*swing_secondry_target;
	vec3_t		swing_last_viewangles;
	float		swing_msg_time;

	// flic mode
	gentity_t	*flic_target;
	qboolean	flic_watching_the_dead;
	qboolean	flic_watching_the_wall;
	vec3_t		flic_dead_origin;
	float		flic_xy_lag;
	float		flic_z_lag;
	float		flic_angle_lag;
	float		flic_last_move_time;
	float		flic_last_switch_time;
	qboolean	flic_override;		// signal that player must be followed
} camera_t;

#endif /* __ZCAM_H__ */

