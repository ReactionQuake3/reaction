//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.40  2002/08/21 07:09:54  jbravo
// Removed an extra definition of the vtos call
//
// Revision 1.39  2002/07/22 07:27:21  niceass
// better fog laser support
//
// Revision 1.38  2002/06/23 04:36:27  niceass
// change to foglaser
//
// Revision 1.37  2002/06/21 21:06:56  niceass
// laserfog stuff
//
// Revision 1.36  2002/06/21 04:11:34  niceass
// fog laser
//
// Revision 1.35  2002/06/16 20:06:13  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.34  2002/06/16 19:12:52  jbravo
// Removed the MISSIONPACK ifdefs and missionpack only code.
//
// Revision 1.33  2002/06/09 05:16:33  niceass
// pressure change
//
// Revision 1.32  2002/06/03 00:39:29  blaze
// dont make a sound when bouncing on the ground
//
// Revision 1.31  2002/05/26 05:16:12  niceass
// pressure
//
// Revision 1.30  2002/05/19 21:27:51  blaze
// added force and buoyancy to breakables
//
// Revision 1.29  2002/04/29 06:14:10  niceass
// pressure
//
// Revision 1.28  2002/04/26 03:39:34  jbravo
// added tkok, fixed players always leaving zcam modes when player thats
// beeing tracked dies
//
// Revision 1.27  2002/04/23 06:10:10  niceass
// some good tabbing
//
// Revision 1.26  2002/04/06 21:43:58  makro
// New surfaceparm system
//
// Revision 1.25  2002/04/03 15:51:01  jbravo
// Small warning fixes
//
// Revision 1.24  2002/04/03 03:13:48  blaze
// NEW BREAKABLE CODE - will break all old breakables(wont appear in maps)
//
// Revision 1.23  2002/03/31 03:31:24  jbravo
// Compiler warning cleanups
//
// Revision 1.22  2002/03/21 02:17:39  blaze
// more func_explosive goodness
//
// Revision 1.21  2002/03/21 00:26:46  blaze
// some fixing of func_explosive
//
// Revision 1.20  2002/03/04 20:50:59  jbravo
// No floating scores over dead bodies, triangles disabled, and no viewing
// names of enemys just of teammates.
//
// Revision 1.19  2002/01/24 14:20:53  jbravo
// Adding func_explosive and a few new surfaceparms
//
// Revision 1.18  2002/01/11 19:48:29  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.17  2001/12/31 16:28:41  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
// cg_effects.c -- these functions generate localentities, usually as a result
// of event processing

#include "cg_local.h"

extern void CG_Particle_Bleed(qhandle_t pshader, vec3_t start, vec3_t dir, int fleshEntityNum, int duration);

/*
===============
CG_ShrapnelSpark

Moved from cg_weapons
Added by Elder
Modified tracer code
I really don't know what's going on half the time here :)
===============
*/
void CG_ShrapnelSpark(vec3_t source, vec3_t dest, float width, float length)
{
	vec3_t forward, right;
	polyVert_t verts[4];
	vec3_t line;
	float len, begin, end;
	vec3_t start, finish;

	//vec3_t                midpoint;

	// tracer
	VectorSubtract(dest, source, forward);
	len = VectorNormalize(forward);

	// start at least a little ways from the muzzle
	//if ( len < 10 ) {
	//return;
	//}

	begin = crandom() * 8;
	end = begin + length;
	if (end > len) {
		end = len;
	}
	VectorMA(source, begin, forward, start);
	VectorMA(source, end, forward, finish);

	line[0] = DotProduct(forward, cg.refdef.viewaxis[1]);
	line[1] = DotProduct(forward, cg.refdef.viewaxis[2]);

	VectorScale(cg.refdef.viewaxis[1], line[1], right);
	VectorMA(right, -line[0], cg.refdef.viewaxis[2], right);
	VectorNormalize(right);

	VectorMA(finish, width, right, verts[0].xyz);
	verts[0].st[0] = 0;
	verts[0].st[1] = 1;
	verts[0].modulate[0] = 255;
	verts[0].modulate[1] = 255;
	verts[0].modulate[2] = 255;
	verts[0].modulate[3] = 255;

	VectorMA(finish, -width, right, verts[1].xyz);
	verts[1].st[0] = 1;
	verts[1].st[1] = 0;
	verts[1].modulate[0] = 255;
	verts[1].modulate[1] = 255;
	verts[1].modulate[2] = 255;
	verts[1].modulate[3] = 255;

	VectorMA(start, -width, right, verts[2].xyz);
	verts[2].st[0] = 1;
	verts[2].st[1] = 1;
	verts[2].modulate[0] = 255;
	verts[2].modulate[1] = 255;
	verts[2].modulate[2] = 255;
	verts[2].modulate[3] = 255;

	VectorMA(start, width, right, verts[3].xyz);
	verts[3].st[0] = 0;
	verts[3].st[1] = 0;
	verts[3].modulate[0] = 255;
	verts[3].modulate[1] = 255;
	verts[3].modulate[2] = 255;
	verts[3].modulate[3] = 255;

	trap_R_AddPolyToScene(cgs.media.tracerShader, 4, verts);

	//midpoint[0] = ( start[0] + finish[0] ) * 0.5;
	//midpoint[1] = ( start[1] + finish[1] ) * 0.5;
	//midpoint[2] = ( start[2] + finish[2] ) * 0.5;

	// add the tracer sound
	//trap_S_StartSound( midpoint, ENTITYNUM_WORLD, CHAN_AUTO, cgs.media.tracerSound );

}

/*
==================
CG_BubbleTrail

Bullets shot underwater
==================
*/
void CG_BubbleTrail(vec3_t start, vec3_t end, float spacing)
{
	vec3_t move;
	vec3_t vec;
	float len;
	int i;

	if (cg_noProjectileTrail.integer) {
		return;
	}

	VectorCopy(start, move);
	VectorSubtract(end, start, vec);
	len = VectorNormalize(vec);

	// advance a random amount first
	i = rand() % (int) spacing;
	VectorMA(move, i, vec, move);

	VectorScale(vec, spacing, vec);

	for (; i < len; i += spacing) {
		localEntity_t *le;
		refEntity_t *re;

		le = CG_AllocLocalEntity();
		le->leFlags = LEF_PUFF_DONT_SCALE;
		le->leType = LE_MOVE_SCALE_FADE;
		le->startTime = cg.time;
		le->endTime = cg.time + 1000 + random() * 250;
		le->lifeRate = 1.0 / (le->endTime - le->startTime);

		re = &le->refEntity;
		re->shaderTime = cg.time / 1000.0f;

		re->reType = RT_SPRITE;
		re->rotation = 0;
		re->radius = 3;
		re->customShader = cgs.media.waterBubbleShader;
		re->shaderRGBA[0] = 0xff;
		re->shaderRGBA[1] = 0xff;
		re->shaderRGBA[2] = 0xff;
		re->shaderRGBA[3] = 0xff;

		le->color[3] = 1.0;

		le->pos.trType = TR_LINEAR;
		le->pos.trTime = cg.time;
		VectorCopy(move, le->pos.trBase);
		le->pos.trDelta[0] = crandom() * 5;
		le->pos.trDelta[1] = crandom() * 5;
		le->pos.trDelta[2] = crandom() * 5 + 6;

		VectorAdd(move, vec, move);
	}
}

/*
=====================
CG_SmokePuff

Adds a smoke puff or blood trail localEntity.
=====================
*/
localEntity_t *CG_SmokePuff(const vec3_t p, const vec3_t vel,
			    float radius,
			    float r, float g, float b, float a,
			    float duration, int startTime, int fadeInTime, int leFlags, qhandle_t hShader)
{
	static int seed = 0x92;
	localEntity_t *le;
	refEntity_t *re;

//      int fadeInTime = startTime + duration / 2;

	le = CG_AllocLocalEntity();
	le->leFlags = leFlags;
	le->radius = radius;

	re = &le->refEntity;
	re->rotation = Q_random(&seed) * 360;
	re->radius = radius;
	re->shaderTime = startTime / 1000.0f;

	le->leType = LE_MOVE_SCALE_FADE;
	le->startTime = startTime;
	le->fadeInTime = fadeInTime;
	le->endTime = startTime + duration;
	if (fadeInTime > startTime) {
		le->lifeRate = 1.0 / (le->endTime - le->fadeInTime);
	} else {
		le->lifeRate = 1.0 / (le->endTime - le->startTime);
	}
	le->color[0] = r;
	le->color[1] = g;
	le->color[2] = b;
	le->color[3] = a;

	le->pos.trType = TR_LINEAR;
	le->pos.trTime = startTime;
	VectorCopy(vel, le->pos.trDelta);
	VectorCopy(p, le->pos.trBase);

	VectorCopy(p, re->origin);
	re->customShader = hShader;

	// rage pro can't alpha fade, so use a different shader
	if (cgs.glconfig.hardwareType == GLHW_RAGEPRO) {
		re->customShader = cgs.media.smokePuffRageProShader;
		re->shaderRGBA[0] = 0xff;
		re->shaderRGBA[1] = 0xff;
		re->shaderRGBA[2] = 0xff;
		re->shaderRGBA[3] = 0xff;
	} else {
		re->shaderRGBA[0] = le->color[0] * 0xff;
		re->shaderRGBA[1] = le->color[1] * 0xff;
		re->shaderRGBA[2] = le->color[2] * 0xff;
		re->shaderRGBA[3] = 0xff;
	}

	re->reType = RT_SPRITE;
	re->radius = le->radius;

	return le;
}

/*
==================
CG_SpawnEffect

Player teleporting in or out
==================
*/
void CG_SpawnEffect(vec3_t org)
{
	localEntity_t *le;
	refEntity_t *re;

	le = CG_AllocLocalEntity();
	le->leFlags = 0;
	le->leType = LE_FADE_RGB;
	le->startTime = cg.time;
	le->endTime = cg.time + 500;
	le->lifeRate = 1.0 / (le->endTime - le->startTime);

	le->color[0] = le->color[1] = le->color[2] = le->color[3] = 1.0;

	re = &le->refEntity;

	re->reType = RT_MODEL;
	re->shaderTime = cg.time / 1000.0f;

	re->customShader = cgs.media.teleportEffectShader;
	re->hModel = cgs.media.teleportEffectModel;
	AxisClear(re->axis);

	VectorCopy(org, re->origin);
	re->origin[2] -= 24;
}

/*
==================
CG_ScorePlum
==================
*/
void CG_ScorePlum(int client, vec3_t org, int score)
{
	localEntity_t *le;
	refEntity_t *re;
	vec3_t angles;
	static vec3_t lastPos;

	// only visualize for the client that scored
	if (client != cg.predictedPlayerState.clientNum || cg_scorePlum.integer == 0) {
		return;
	}
// JBravo: and not in team based games
	if (cgs.gametype >= GT_TEAM) {
		return;
	}

	le = CG_AllocLocalEntity();
	le->leFlags = 0;
	le->leType = LE_SCOREPLUM;
	le->startTime = cg.time;
	le->endTime = cg.time + 4000;
	le->lifeRate = 1.0 / (le->endTime - le->startTime);

	le->color[0] = le->color[1] = le->color[2] = le->color[3] = 1.0;
	le->radius = score;

	VectorCopy(org, le->pos.trBase);
	if (org[2] >= lastPos[2] - 20 && org[2] <= lastPos[2] + 20) {
		le->pos.trBase[2] -= 20;
	}
	//CG_Printf( "Plum origin %i %i %i -- %i\n", (int)org[0], (int)org[1], (int)org[2], (int)Distance(org, lastPos));
	VectorCopy(org, lastPos);

	re = &le->refEntity;

	re->reType = RT_SPRITE;
	re->radius = 16;

	VectorClear(angles);
	AnglesToAxis(angles, re->axis);
}

/*
====================
CG_MakeExplosion
====================
*/
localEntity_t *CG_MakeExplosion(vec3_t origin, vec3_t dir,
				qhandle_t hModel, qhandle_t shader, int msec, qboolean isSprite)
{
	float ang;
	localEntity_t *ex;
	int offset;
	vec3_t tmpVec, newOrigin;

	if (msec <= 0) {
		CG_Error("CG_MakeExplosion: msec = %i", msec);
	}
	// skew the time a bit so they aren't all in sync
	offset = rand() & 63;

	ex = CG_AllocLocalEntity();
	if (isSprite) {
		ex->leType = LE_SPRITE_EXPLOSION;

		// randomly rotate sprite orientation
		ex->refEntity.rotation = rand() % 360;
		VectorScale(dir, 16, tmpVec);
		VectorAdd(tmpVec, origin, newOrigin);
	} else {
		ex->leType = LE_EXPLOSION;
		VectorCopy(origin, newOrigin);

		// set axis with random rotate
		if (!dir) {
			AxisClear(ex->refEntity.axis);
		} else {
			ang = rand() % 360;
			VectorCopy(dir, ex->refEntity.axis[0]);
			RotateAroundDirection(ex->refEntity.axis, ang);
		}
	}

	ex->startTime = cg.time - offset;
	ex->endTime = ex->startTime + msec;

	// bias the time so all shader effects start correctly
	ex->refEntity.shaderTime = ex->startTime / 1000.0f;

	ex->refEntity.hModel = hModel;
	ex->refEntity.customShader = shader;

	// set origin
	VectorCopy(newOrigin, ex->refEntity.origin);
	VectorCopy(newOrigin, ex->refEntity.oldorigin);

	ex->color[0] = ex->color[1] = ex->color[2] = 1.0;

	return ex;
}

/*
=================
CG_BleedSpray

Elder: This is a super blood spray for SSG hits
Based on bubble trail code + other stuff
=================
*/
#define MAX_SPRAY_BURSTS	16
void CG_BleedSpray(vec3_t start, vec3_t end, int entityNum, int numBursts)
{
	//vec3_t                dir;
	vec3_t trueEnd;
	vec3_t move;
	vec3_t vec;
	vec3_t velocity;

	localEntity_t *blood;
	float len;
	int i;
	int spacing = 30;
	int bloodCount = 0;
	trace_t tr;

	if (!cg_blood.integer || cg_RQ3_bloodStyle.integer == 0) {
		return;
	}
	//Clamp number so we don't generate too many blood entities
	if (numBursts > MAX_SPRAY_BURSTS)
		numBursts = MAX_SPRAY_BURSTS;

	VectorCopy(end, move);
	VectorSubtract(end, start, vec);

	//Calculate true length via start/end points
	VectorCopy(vec, trueEnd);
	VectorNormalize(trueEnd);

	//VectorScale (trueEnd, 300 + rand() % 100, trueEnd); 
	//VectorAdd (end, trueEnd, trueEnd);
	VectorMA(end, 300 + rand() % 100, trueEnd, trueEnd);

	// Check end point validity so it doesn't go through walls
	// If it does go through wall, take the trace's endpoint
	CG_Trace(&tr, start, NULL, NULL, trueEnd, entityNum, CONTENTS_SOLID);
	if (tr.fraction != 1.0)
		VectorCopy(tr.endpos, trueEnd);

	VectorSubtract(trueEnd, start, vec);

	len = VectorNormalize(vec);

	//Set velocity
	VectorScale(vec, 10, velocity);
	if (cg_RQ3_bloodStyle.integer == 1)
		velocity[2] += 30;
	else
		velocity[2] -= 10;

	// advance a random amount first
	i = rand() % (int) spacing;
	VectorMA(move, i, vec, move);
	VectorScale(vec, spacing, vec);

	for (; i < len; i += spacing) {
		//restrict amount of spurts
		if (bloodCount++ > numBursts)
			break;

		blood = CG_SmokePuff(move, velocity, 8,
				     1, 1, 1, 1,
				     1500 + rand() % 250,
				     cg.time, 0, LEF_TUMBLE | LEF_PUFF_DONT_SCALE, cgs.media.bloodTrailShader);

		blood->refEntity.rotation = rand() % 360;
		//Check blood style
		if (cg_RQ3_bloodStyle.integer == 1) {
			blood->leType = LE_FRAGMENT;
			blood->leMarkType = LEMT_BLOOD;
			blood->pos.trType = TR_GRAVITY;
			blood->bounceFactor = 0.4f;
		}

		VectorAdd(move, vec, move);
	}
}

/*
=================
CG_EjectBloodSplat

Drop a splat
=================
*/

void CG_EjectBloodSplat(vec3_t origin, vec3_t velocity, int amount, int duration)
{
	int i;
	localEntity_t *blood;
	vec3_t bOrigin;
	vec3_t bVelocity;

	if (!cg_blood.integer)
		return;

	for (i = 0; i < amount; i++) {
		VectorCopy(origin, bOrigin);
		VectorCopy(velocity, bVelocity);
		bOrigin[0] += rand() % 6 - 3;
		bOrigin[1] += rand() % 6 - 3;
		bVelocity[0] += rand() % 6 - 3;
		bVelocity[1] += rand() % 6 - 3;

		blood = CG_SmokePuff(bOrigin, bVelocity, 4,
				     1, 1, 1, 0.6f,
				     duration + rand() % 250, cg.time, 0,
				     LEF_TUMBLE | LEF_PUFF_DONT_SCALE, cgs.media.bloodTrailShader);
		blood->refEntity.rotation = rand() % 360;
		blood->leType = LE_FRAGMENT;
		blood->leType = LE_FRAGMENT;
		blood->leMarkType = LEMT_BLOOD;
		blood->pos.trType = TR_GRAVITY;
		blood->bounceFactor = 0.4f;
	}
}

/*
=================
CG_BleedParticleSpray

This is a particle blood spray not unlike Quake 2's
Err, it's not working well right now :/
=================
*/

void CG_BleedParticleSpray(vec3_t start, vec3_t dir, int fleshEntityNum, int amount, int duration)
{
	int i;

	if (!cg_RQ3_bloodStyle.integer || !cg_blood.integer)
		return;

	for (i = 0; i < amount; i++) {
		CG_Particle_Bleed(cgs.media.bloodExplosionShader, start, dir, fleshEntityNum, duration + rand() % 250);
	}

}

/*
=================
CG_Bleed

This is the spurt of blood when a character gets hit
=================
*/
void CG_Bleed(vec3_t origin, int entityNum)
{
	localEntity_t *ex;

	if (!cg_blood.integer) {
		return;
	}

	ex = CG_AllocLocalEntity();
	ex->leType = LE_EXPLOSION;

	ex->startTime = cg.time;
	ex->endTime = ex->startTime + 500;

	VectorCopy(origin, ex->refEntity.origin);
	ex->refEntity.reType = RT_SPRITE;
	ex->refEntity.rotation = rand() % 360;
	ex->refEntity.radius = 24;

	ex->refEntity.customShader = cgs.media.bloodExplosionShader;

	// don't show player's own blood in view
	if (entityNum == cg.snap->ps.clientNum) {
		ex->refEntity.renderfx |= RF_THIRD_PERSON;
	}
}

/*
==================
CG_LaunchGib
==================
*/
void CG_LaunchGib(vec3_t origin, vec3_t velocity, qhandle_t hModel)
{
	localEntity_t *le;
	refEntity_t *re;

	le = CG_AllocLocalEntity();
	re = &le->refEntity;

	le->leType = LE_FRAGMENT;
	le->startTime = cg.time;
	le->endTime = le->startTime + 5000 + random() * 3000;

	VectorCopy(origin, re->origin);
	AxisCopy(axisDefault, re->axis);
	re->hModel = hModel;

	le->pos.trType = TR_GRAVITY;
	VectorCopy(origin, le->pos.trBase);
	VectorCopy(velocity, le->pos.trDelta);
	le->pos.trTime = cg.time;

	le->bounceFactor = 0.6f;

	le->leBounceSoundType = LEBS_BLOOD;
	le->leMarkType = LEMT_BLOOD;
}

/*
===================
CG_GibPlayer

Generated a bunch of gibs launching out from the bodies location
===================
*/
#define	GIB_VELOCITY	250
#define	GIB_JUMP		250
void CG_GibPlayer(vec3_t playerOrigin)
{
	vec3_t origin, velocity;

	if (!cg_blood.integer) {
		return;
	}

	VectorCopy(playerOrigin, origin);
	velocity[0] = crandom() * GIB_VELOCITY;
	velocity[1] = crandom() * GIB_VELOCITY;
	velocity[2] = GIB_JUMP + crandom() * GIB_VELOCITY;
	if (rand() & 1) {
		CG_LaunchGib(origin, velocity, cgs.media.gibSkull);
	} else {
		CG_LaunchGib(origin, velocity, cgs.media.gibBrain);
	}

	// allow gibs to be turned off for speed
	if (!cg_gibs.integer) {
		return;
	}

	VectorCopy(playerOrigin, origin);
	velocity[0] = crandom() * GIB_VELOCITY;
	velocity[1] = crandom() * GIB_VELOCITY;
	velocity[2] = GIB_JUMP + crandom() * GIB_VELOCITY;
	CG_LaunchGib(origin, velocity, cgs.media.gibAbdomen);

	VectorCopy(playerOrigin, origin);
	velocity[0] = crandom() * GIB_VELOCITY;
	velocity[1] = crandom() * GIB_VELOCITY;
	velocity[2] = GIB_JUMP + crandom() * GIB_VELOCITY;
	CG_LaunchGib(origin, velocity, cgs.media.gibArm);

	VectorCopy(playerOrigin, origin);
	velocity[0] = crandom() * GIB_VELOCITY;
	velocity[1] = crandom() * GIB_VELOCITY;
	velocity[2] = GIB_JUMP + crandom() * GIB_VELOCITY;
	CG_LaunchGib(origin, velocity, cgs.media.gibChest);

	VectorCopy(playerOrigin, origin);
	velocity[0] = crandom() * GIB_VELOCITY;
	velocity[1] = crandom() * GIB_VELOCITY;
	velocity[2] = GIB_JUMP + crandom() * GIB_VELOCITY;
	CG_LaunchGib(origin, velocity, cgs.media.gibFist);

	VectorCopy(playerOrigin, origin);
	velocity[0] = crandom() * GIB_VELOCITY;
	velocity[1] = crandom() * GIB_VELOCITY;
	velocity[2] = GIB_JUMP + crandom() * GIB_VELOCITY;
	CG_LaunchGib(origin, velocity, cgs.media.gibFoot);

	VectorCopy(playerOrigin, origin);
	velocity[0] = crandom() * GIB_VELOCITY;
	velocity[1] = crandom() * GIB_VELOCITY;
	velocity[2] = GIB_JUMP + crandom() * GIB_VELOCITY;
	CG_LaunchGib(origin, velocity, cgs.media.gibForearm);

	VectorCopy(playerOrigin, origin);
	velocity[0] = crandom() * GIB_VELOCITY;
	velocity[1] = crandom() * GIB_VELOCITY;
	velocity[2] = GIB_JUMP + crandom() * GIB_VELOCITY;
	CG_LaunchGib(origin, velocity, cgs.media.gibIntestine);

	VectorCopy(playerOrigin, origin);
	velocity[0] = crandom() * GIB_VELOCITY;
	velocity[1] = crandom() * GIB_VELOCITY;
	velocity[2] = GIB_JUMP + crandom() * GIB_VELOCITY;
	CG_LaunchGib(origin, velocity, cgs.media.gibLeg);

	VectorCopy(playerOrigin, origin);
	velocity[0] = crandom() * GIB_VELOCITY;
	velocity[1] = crandom() * GIB_VELOCITY;
	velocity[2] = GIB_JUMP + crandom() * GIB_VELOCITY;
	CG_LaunchGib(origin, velocity, cgs.media.gibLeg);
}

/*
==================
CG_LaunchGib
==================
*/
void CG_LaunchExplode(vec3_t origin, vec3_t velocity, qhandle_t hModel)
{
	localEntity_t *le;
	refEntity_t *re;

	le = CG_AllocLocalEntity();
	re = &le->refEntity;

	le->leType = LE_FRAGMENT;
	le->startTime = cg.time;
	le->endTime = le->startTime + 10000 + random() * 6000;

	VectorCopy(origin, re->origin);
	AxisCopy(axisDefault, re->axis);
	re->hModel = hModel;

	le->pos.trType = TR_GRAVITY;
	VectorCopy(origin, le->pos.trBase);
	VectorCopy(velocity, le->pos.trDelta);
	le->pos.trTime = cg.time;

	le->bounceFactor = 0.1f;

	le->leBounceSoundType = LEBS_BRASS;
	le->leMarkType = LEMT_NONE;
}

#define	EXP_VELOCITY	100
#define	EXP_JUMP		150
/*
===================
CG_GibPlayer

Generated a bunch of gibs launching out from the bodies location
===================
*/
void CG_BigExplode(vec3_t playerOrigin)
{
	vec3_t origin, velocity;

	if (!cg_blood.integer) {
		return;
	}

	VectorCopy(playerOrigin, origin);
	velocity[0] = crandom() * EXP_VELOCITY;
	velocity[1] = crandom() * EXP_VELOCITY;
	velocity[2] = EXP_JUMP + crandom() * EXP_VELOCITY;
	CG_LaunchExplode(origin, velocity, cgs.media.smoke2);

	VectorCopy(playerOrigin, origin);
	velocity[0] = crandom() * EXP_VELOCITY;
	velocity[1] = crandom() * EXP_VELOCITY;
	velocity[2] = EXP_JUMP + crandom() * EXP_VELOCITY;
	CG_LaunchExplode(origin, velocity, cgs.media.smoke2);

	VectorCopy(playerOrigin, origin);
	velocity[0] = crandom() * EXP_VELOCITY * 1.5;
	velocity[1] = crandom() * EXP_VELOCITY * 1.5;
	velocity[2] = EXP_JUMP + crandom() * EXP_VELOCITY;
	CG_LaunchExplode(origin, velocity, cgs.media.smoke2);

	VectorCopy(playerOrigin, origin);
	velocity[0] = crandom() * EXP_VELOCITY * 2.0;
	velocity[1] = crandom() * EXP_VELOCITY * 2.0;
	velocity[2] = EXP_JUMP + crandom() * EXP_VELOCITY;
	CG_LaunchExplode(origin, velocity, cgs.media.smoke2);

	VectorCopy(playerOrigin, origin);
	velocity[0] = crandom() * EXP_VELOCITY * 2.5;
	velocity[1] = crandom() * EXP_VELOCITY * 2.5;
	velocity[2] = EXP_JUMP + crandom() * EXP_VELOCITY;
	CG_LaunchExplode(origin, velocity, cgs.media.smoke2);
}

#define	GLASS_VELOCITY	175
#define	GLASS_JUMP		125
/*
==================
CG_LaunchGlass
==================
*/
void CG_LaunchGlass(vec3_t origin, vec3_t velocity, vec3_t rotation, float bounce, qhandle_t hModel)	//, qhandle_t altSkin )
{
	localEntity_t *le;
	refEntity_t *re;

	le = CG_AllocLocalEntity();
	re = &le->refEntity;

	le->leType = LE_FRAGMENT;
	le->startTime = cg.time;
	le->endTime = le->startTime + (random() * 3000) + cg_RQ3_glasstime.integer;	// + 30000;

	VectorCopy(origin, re->origin);
	AxisCopy(axisDefault, re->axis);
	re->hModel = hModel;

	//Elder: custom shaders for debris?
	//if (altSkin)
	//re->customSkin = altSkin;

	le->pos.trType = TR_GRAVITY;
	VectorCopy(origin, le->pos.trBase);
	VectorCopy(velocity, le->pos.trDelta);
	le->pos.trTime = cg.time;

	//Elder: added
	//VectorCopy( origin, le->angles.trBase );
	VectorCopy(velocity, le->angles.trBase);
	le->angles.trBase[2] = le->angles.trBase[2] - GLASS_JUMP;
	VectorCopy(rotation, le->angles.trDelta);
	le->angles.trTime = cg.time;

	le->bounceFactor = bounce;

	le->leFlags = LEF_TUMBLE;
	le->leBounceSoundType = LEBS_NONE;
	le->leMarkType = LEMT_NONE;
}

/*
===================
CG_BreakGlass

Generated a bunch of glass shards launching out from the glass location
Elder: don't be mislead by the name - this breaks more than glass
===================
*/

void CG_BreakGlass(vec3_t playerOrigin, int glassParm, int number, int type, int isChip)
{
	vec3_t origin, velocity, rotation;
	int value;
	int count;
	int states[] = { 1, 2, 3 };	// Select model variations

	// Get the size of the array
	int numstates = sizeof(states) / sizeof(states[0]);

	// Elder: debris model handles
	qhandle_t debris1;
	qhandle_t debris2;
	qhandle_t debris3;
	float bounceFactor;
	int newParm;
	int id;
	qhandle_t sound;

	id = (glassParm & 63);
	//  Com_Printf("ID is %d\n",id);
	glassParm = glassParm >> 6;
	sound = cgs.media.breakables[id].sound[rand() % 3];
	trap_S_StartSound(NULL, number, CHAN_BODY, sound);
	bounceFactor = (float) 0.3;

	if ((glassParm & RQ3_DEBRIS_MEDIUM) == RQ3_DEBRIS_MEDIUM && (glassParm & RQ3_DEBRIS_HIGH) == RQ3_DEBRIS_HIGH) {
		//Tons
		count = 65 + rand() % 16;
	} else if ((glassParm & RQ3_DEBRIS_HIGH) == RQ3_DEBRIS_HIGH) {
		//Large
		count = 40 + rand() % 11;
	} else if ((glassParm & RQ3_DEBRIS_MEDIUM) == RQ3_DEBRIS_MEDIUM) {
		//Medium
		count = 20 + rand() % 6;
	} else {
		//Small
		count = 8 + rand() % 6;
	}
	//If it's just a chip, dont make so many
	if (isChip == 1) {
		count /= 8;
	}
	//Strip off amount info and revert eParm back to server-side size
	newParm = glassParm & 15;
	glassParm &= ~newParm;
	glassParm = glassParm << (type * 4);

	debris1 = cgs.media.breakables[id].model[0];
	debris2 = cgs.media.breakables[id].model[1];
	debris3 = cgs.media.breakables[id].model[2];

	//launch loop
	while (count--) {
		// Generate the random number every count so every shard is a
		// of the three. If this is placed above it only gets a random
		// number every time a piece of glass is broken.
		value = states[rand() % numstates];

		VectorCopy(playerOrigin, origin);
		velocity[0] = crandom() * 25 * cgs.media.breakables[id].velocity;
		velocity[1] = crandom() * 25 * cgs.media.breakables[id].velocity;
		velocity[2] = 25 * cgs.media.breakables[id].jump + crandom() * 25 * cgs.media.breakables[id].velocity;
		//Elder: added
		rotation[0] = crandom() * GLASS_VELOCITY;
		rotation[1] = crandom() * GLASS_VELOCITY;
		rotation[2] = crandom() * GLASS_VELOCITY;

		switch (value) {
		case 1:
			CG_LaunchGlass(origin, velocity, rotation, bounceFactor, debris1);
			break;
		case 2:
			CG_LaunchGlass(origin, velocity, rotation, bounceFactor, debris2);
			break;
		case 3:
			CG_LaunchGlass(origin, velocity, rotation, bounceFactor, debris3);
			break;
		}
	}
}

// JBravo: For func_explosive
void CG_LaunchBreakableFrag(vec3_t origin, vec3_t velocity, qhandle_t hModel, float bouncyness, float size)
{
	localEntity_t *le;
	refEntity_t *re;

	le = CG_AllocLocalEntity();
	re = &le->refEntity;

	le->leType = LE_FRAGMENT;
	le->startTime = cg.time - (rand() & 63);
	le->endTime = le->startTime + 5000 + random() * 3000;

	VectorCopy(origin, re->origin);
	AxisCopy(axisDefault, re->axis);
	re->hModel = hModel;
//      re->customShader = hShader;

	le->pos.trType = TR_GRAVITY;
	VectorCopy(origin, le->pos.trBase);
	VectorCopy(velocity, le->pos.trDelta);
	le->pos.trTime = cg.time;

	le->size = size;
	VectorScale(re->axis[0], size, re->axis[0]);
	VectorScale(re->axis[1], size, re->axis[1]);
	VectorScale(re->axis[2], size, re->axis[2]);
	re->nonNormalizedAxes = qtrue;

	le->angles.trType = TR_LINEAR;
	le->angles.trTime = cg.time;
	le->angles.trBase[0] = rand() & 63;
	le->angles.trBase[1] = rand() & 63;
	le->angles.trBase[2] = rand() & 63;
	le->angles.trDelta[0] = rand() & 127;
	le->angles.trDelta[1] = rand() & 127;
	le->angles.trDelta[2] = rand() & 127;
	le->leFlags = LEF_TUMBLE;

	le->bounceFactor = bouncyness;

	le->leBounceSoundType = LEBS_NONE;
	le->leMarkType = LEMT_NONE;
}

/*
=============
VectorToString

This is just a convenience function
for printing vectors
=============
*/
/*
 * JBravo: this is unneccesary and causes compiler warnings for two definitions
char *vtos(const vec3_t v)
{
	static int index;
	static char str[8][32];
	char *s;

	// use an array so that multiple vtos won't collide
	s = str[index];
	index = (index + 1) & 7;

	Com_sprintf(s, 32, "(%i %i %i)", (int) v[0], (int) v[1], (int) v[2]);

	return s;
}
*/
// JBravo: also for func_explosive
/*
===================
CG_BreakBreakable

Generated a bunch of gibs launching out from the breakables location
===================
*/
#define BREAK_VELOCITY  550
#define BREAK_JUMP      1500

void CG_BreakBreakable(centity_t * cent, int eParam, int number)
{
	localEntity_t *le;
	vec3_t origin, velocity;
	qhandle_t mod;
	qhandle_t shader;
	vec3_t shrapnelDest;
	localEntity_t *smokePuff;
	vec3_t puffDir;

	float light;
	vec3_t lightColor;
	int duration;
	int sparkCount;

	int i;

	// JBravo: Unused variable
	//      int             modelbias[10] = { 0, 0, 0, 0, 1, 1, 1, 2, 2 };
	int id;
	int count;

	id = (eParam & 63);
	eParam = eParam >> 6;

	trap_S_StartSound(NULL, number, CHAN_BODY, cgs.media.breakables[id].exp_sound);

	if ((eParam & RQ3_DEBRIS_MEDIUM) == RQ3_DEBRIS_MEDIUM && (eParam & RQ3_DEBRIS_HIGH) == RQ3_DEBRIS_HIGH) {
		//Tons
		count = 65 + rand() % 16;
	} else if ((eParam & RQ3_DEBRIS_HIGH) == RQ3_DEBRIS_HIGH) {
		//Large
		count = 40 + rand() % 11;
	} else if ((eParam & RQ3_DEBRIS_MEDIUM) == RQ3_DEBRIS_MEDIUM) {
		//Medium
		count = 20 + rand() % 6;
	} else {
		//Small
		count = 8 + rand() % 6;
	}
	//if (material) material--;
	VectorCopy(cent->lerpOrigin, origin);
	/*
	   sound = cgs.media.breakables[id].sound;
	   trap_S_StartSound( origin, cent->currentState.number, CHAN_BODY, sound ); */

	// create an explosion
	mod = cgs.media.dishFlashModel;
	shader = cgs.media.breakables[id].shader;

	//Com_Printf("Explosion, %d, breakableshader %d at %s ep %d\n",shader,cgs.media.breakables[id].shader, vtos(origin), eParam);
	light = 550;
	lightColor[0] = 1;
	lightColor[1] = 1;
	lightColor[2] = 0;
	duration = 1000;

	velocity[0] = 1;
	velocity[1] = 1;
	velocity[2] = 1;

	le = CG_MakeExplosion(origin, velocity, mod, shader, duration, qtrue);
	le->light = light;
	VectorCopy(lightColor, le->lightColor);

	sparkCount = 60 + rand() % 10;
	origin[2] += 32;

	for (i = 0; i < sparkCount; i++) {
		VectorScale(velocity, rand() % 200, velocity);
		velocity[0] += rand() % 200 - 100;
		velocity[1] += rand() % 200 - 100;
		if (i % 8 == 7) {
			// Add shrapnel trace effect
			VectorMA(origin, 0.7f, velocity, shrapnelDest);
			CG_ShrapnelSpark(origin, shrapnelDest, 10, 280);
		}
		// Add sparks
		CG_ParticleSparks(origin, velocity, 900 + rand() % 200, 5, 5, -2.5f, 3.5f);
	}

	// Add smoke puff
	puffDir[0] = 0;
	puffDir[1] = 0;
	puffDir[2] = 20;
	origin[2] -= 16;
	smokePuff = CG_SmokePuff(origin, puffDir,
				 rand() % 12 + 100, 1, 1, 1, 0.6f, 3000, cg.time, 0, 0, cgs.media.smokePuffShader);

}

void CG_Pressure(vec3_t origin, vec3_t dir, int type, int speed)
{
	localEntity_t *le;
	refEntity_t *re;

	le = CG_AllocLocalEntity();
	re = &le->refEntity;
	le->leType = LE_PRESSURE;

	if (type == 1)
		le->leFlags = LEF_AIR;
	else if (type == 2)
		le->leFlags = LEF_FLAME;
	else if (type == 3)
		le->leFlags = LEF_WATER;
	else
		le->leFlags = LEF_STEAM;

	le->size = (float) speed;	// Size holds the speed.... yes...

	VectorCopy(origin, le->pos.trBase);
	VectorCopy(dir, le->pos.trDelta);
	le->startTime = cg.time;
	le->endTime = le->startTime + 10000;
}

static void CG_VisibleLaser( vec3_t start, vec3_t finish ) {
	refEntity_t re;

//	re.shaderTime = cg.time / 1000.0f;
	re.reType = RT_RAIL_CORE;
	re.customShader = cgs.media.railCoreShader;

	VectorCopy( start, re.origin );
	VectorCopy( finish, re.oldorigin );
	
	re.shaderRGBA[0] = 255;
	re.shaderRGBA[1] = 0;
	re.shaderRGBA[2] = 0;
	re.shaderRGBA[3] = 128;

	AxisClear( re.axis );
	
	trap_R_AddRefEntityToScene( &re );
}


void CG_DrawVisibleLaser( vec3_t origin, int clientNum, vec3_t dir) {
	int			sourceContentType, destContentType;
	vec3_t		start, end;
	trace_t		trace;

	if ( !cg_enableLaserFog.integer )
		return;

	// NiceAss: This user does not have a lasersight
	if (!( cg_entities[clientNum].currentState.powerups & (1 << PW_LASERSIGHT) ))
		return;

	VectorCopy(origin, start);

	VectorMA(origin, 8192 * 16, dir, end);
	//trap_CM_BoxTrace(&trace, start, end, NULL, NULL, clientNum, MASK_ALL); //MASK_SHOT);
	CG_Trace(&trace, start, NULL, NULL, end, clientNum, MASK_ALL);
	VectorCopy(trace.endpos, end);

	sourceContentType = trap_CM_PointContents(start, 0);
	destContentType = trap_CM_PointContents(end, 0);

	// do a complete laser if necessary
	if ((sourceContentType == destContentType) && (sourceContentType & CONTENTS_FOG)) {
		CG_VisibleLaser(start, end);
	}
	// laser from fog into air
	else if ((sourceContentType & CONTENTS_FOG)) {
		trap_CM_BoxTrace(&trace, end, start, NULL, NULL, 0, CONTENTS_FOG);
		CG_VisibleLaser(start, trace.endpos);
	}
	// laser from air into fog
	else if ((destContentType & CONTENTS_FOG)) {
		trap_CM_BoxTrace(&trace, start, end, NULL, NULL, 0, CONTENTS_FOG);
		CG_VisibleLaser(trace.endpos, end);
	}
}
