//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log: &
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
// cg_effects.c -- these functions generate localentities, usually as a result
// of event processing

#include "cg_local.h"


/*
==================
CG_BubbleTrail

Bullets shot underwater
==================
*/
void CG_BubbleTrail( vec3_t start, vec3_t end, float spacing ) {
	vec3_t		move;
	vec3_t		vec;
	float		len;
	int			i;

	if ( cg_noProjectileTrail.integer ) {
		return;
	}

	VectorCopy (start, move);
	VectorSubtract (end, start, vec);
	len = VectorNormalize (vec);

	// advance a random amount first
	i = rand() % (int)spacing;
	VectorMA( move, i, vec, move );

	VectorScale (vec, spacing, vec);

	for ( ; i < len; i += spacing ) {
		localEntity_t	*le;
		refEntity_t		*re;

		le = CG_AllocLocalEntity();
		le->leFlags = LEF_PUFF_DONT_SCALE;
		le->leType = LE_MOVE_SCALE_FADE;
		le->startTime = cg.time;
		le->endTime = cg.time + 1000 + random() * 250;
		le->lifeRate = 1.0 / ( le->endTime - le->startTime );

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
		VectorCopy( move, le->pos.trBase );
		le->pos.trDelta[0] = crandom()*5;
		le->pos.trDelta[1] = crandom()*5;
		le->pos.trDelta[2] = crandom()*5 + 6;

		VectorAdd (move, vec, move);
	}
}

/*
=====================
CG_SmokePuff

Adds a smoke puff or blood trail localEntity.
=====================
*/
localEntity_t *CG_SmokePuff( const vec3_t p, const vec3_t vel, 
				   float radius,
				   float r, float g, float b, float a,
				   float duration,
				   int startTime,
				   int fadeInTime,
				   int leFlags,
				   qhandle_t hShader ) {
	static int	seed = 0x92;
	localEntity_t	*le;
	refEntity_t		*re;
//	int fadeInTime = startTime + duration / 2;

	le = CG_AllocLocalEntity();
	le->leFlags = leFlags;
	le->radius = radius;

	re = &le->refEntity;
	re->rotation = Q_random( &seed ) * 360;
	re->radius = radius;
	re->shaderTime = startTime / 1000.0f;

	le->leType = LE_MOVE_SCALE_FADE;
	le->startTime = startTime;
	le->fadeInTime = fadeInTime;
	le->endTime = startTime + duration;
	if ( fadeInTime > startTime ) {
		le->lifeRate = 1.0 / ( le->endTime - le->fadeInTime );
	}
	else {
		le->lifeRate = 1.0 / ( le->endTime - le->startTime );
	}
	le->color[0] = r;
	le->color[1] = g; 
	le->color[2] = b;
	le->color[3] = a;


	le->pos.trType = TR_LINEAR;
	le->pos.trTime = startTime;
	VectorCopy( vel, le->pos.trDelta );
	VectorCopy( p, le->pos.trBase );

	VectorCopy( p, re->origin );
	re->customShader = hShader;

	// rage pro can't alpha fade, so use a different shader
	if ( cgs.glconfig.hardwareType == GLHW_RAGEPRO ) {
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
void CG_SpawnEffect( vec3_t org ) {
	localEntity_t	*le;
	refEntity_t		*re;

	le = CG_AllocLocalEntity();
	le->leFlags = 0;
	le->leType = LE_FADE_RGB;
	le->startTime = cg.time;
	le->endTime = cg.time + 500;
	le->lifeRate = 1.0 / ( le->endTime - le->startTime );

	le->color[0] = le->color[1] = le->color[2] = le->color[3] = 1.0;

	re = &le->refEntity;

	re->reType = RT_MODEL;
	re->shaderTime = cg.time / 1000.0f;

#ifndef MISSIONPACK
	re->customShader = cgs.media.teleportEffectShader;
#endif
	re->hModel = cgs.media.teleportEffectModel;
	AxisClear( re->axis );

	VectorCopy( org, re->origin );
#ifdef MISSIONPACK
	re->origin[2] += 16;
#else
	re->origin[2] -= 24;
#endif
}

#ifdef MISSIONPACK

/*
===============
CG_LightningBoltBeam
===============
*/
void CG_LightningBoltBeam( vec3_t start, vec3_t end ) {
	localEntity_t	*le;
	refEntity_t		*beam;

	le = CG_AllocLocalEntity();
	le->leFlags = 0;
	le->leType = LE_SHOWREFENTITY;
	le->startTime = cg.time;
	le->endTime = cg.time + 50;

	beam = &le->refEntity;

	VectorCopy( start, beam->origin );
	// this is the end point
	VectorCopy( end, beam->oldorigin );

	beam->reType = RT_LIGHTNING;
	beam->customShader = cgs.media.lightningShader;
}

/*
==================
CG_KamikazeEffect
==================
*/
void CG_KamikazeEffect( vec3_t org ) {
	localEntity_t	*le;
	refEntity_t		*re;

	le = CG_AllocLocalEntity();
	le->leFlags = 0;
	le->leType = LE_KAMIKAZE;
	le->startTime = cg.time;
	le->endTime = cg.time + 3000;//2250;
	le->lifeRate = 1.0 / ( le->endTime - le->startTime );

	le->color[0] = le->color[1] = le->color[2] = le->color[3] = 1.0;

	VectorClear(le->angles.trBase);

	re = &le->refEntity;

	re->reType = RT_MODEL;
	re->shaderTime = cg.time / 1000.0f;

	re->hModel = cgs.media.kamikazeEffectModel;

	VectorCopy( org, re->origin );

}

/*
==================
CG_ObeliskExplode
==================
*/
void CG_ObeliskExplode( vec3_t org, int entityNum ) {
	localEntity_t	*le;
	vec3_t origin;

	// create an explosion
	VectorCopy( org, origin );
	origin[2] += 64;
	le = CG_MakeExplosion( origin, vec3_origin,
						   cgs.media.dishFlashModel,
						   cgs.media.rocketExplosionShader,
						   600, qtrue );
	le->light = 300;
	le->lightColor[0] = 1;
	le->lightColor[1] = 0.75;
	le->lightColor[2] = 0.0;
}

/*
==================
CG_ObeliskPain
==================
*/
void CG_ObeliskPain( vec3_t org ) {
	float r;
	sfxHandle_t sfx;

	// hit sound
	r = rand() & 3;
	if ( r < 2 ) {
		sfx = cgs.media.obeliskHitSound1;
	} else if ( r == 2 ) {
		sfx = cgs.media.obeliskHitSound2;
	} else {
		sfx = cgs.media.obeliskHitSound3;
	}
	trap_S_StartSound ( org, ENTITYNUM_NONE, CHAN_BODY, sfx );
}


/*
==================
CG_InvulnerabilityImpact
==================
*/
void CG_InvulnerabilityImpact( vec3_t org, vec3_t angles ) {
	localEntity_t	*le;
	refEntity_t		*re;
	int				r;
	sfxHandle_t		sfx;

	le = CG_AllocLocalEntity();
	le->leFlags = 0;
	le->leType = LE_INVULIMPACT;
	le->startTime = cg.time;
	le->endTime = cg.time + 1000;
	le->lifeRate = 1.0 / ( le->endTime - le->startTime );

	le->color[0] = le->color[1] = le->color[2] = le->color[3] = 1.0;

	re = &le->refEntity;

	re->reType = RT_MODEL;
	re->shaderTime = cg.time / 1000.0f;

	re->hModel = cgs.media.invulnerabilityImpactModel;

	VectorCopy( org, re->origin );
	AnglesToAxis( angles, re->axis );

	r = rand() & 3;
	if ( r < 2 ) {
		sfx = cgs.media.invulnerabilityImpactSound1;
	} else if ( r == 2 ) {
		sfx = cgs.media.invulnerabilityImpactSound2;
	} else {
		sfx = cgs.media.invulnerabilityImpactSound3;
	}
	trap_S_StartSound (org, ENTITYNUM_NONE, CHAN_BODY, sfx );
}

/*
==================
CG_InvulnerabilityJuiced
==================
*/
void CG_InvulnerabilityJuiced( vec3_t org ) {
	localEntity_t	*le;
	refEntity_t		*re;
	vec3_t			angles;

	le = CG_AllocLocalEntity();
	le->leFlags = 0;
	le->leType = LE_INVULJUICED;
	le->startTime = cg.time;
	le->endTime = cg.time + 10000;
	le->lifeRate = 1.0 / ( le->endTime - le->startTime );

	le->color[0] = le->color[1] = le->color[2] = le->color[3] = 1.0;

	re = &le->refEntity;

	re->reType = RT_MODEL;
	re->shaderTime = cg.time / 1000.0f;

	re->hModel = cgs.media.invulnerabilityJuicedModel;

	VectorCopy( org, re->origin );
	VectorClear(angles);
	AnglesToAxis( angles, re->axis );

	trap_S_StartSound (org, ENTITYNUM_NONE, CHAN_BODY, cgs.media.invulnerabilityJuicedSound );
}

#endif

/*
==================
CG_ScorePlum
==================
*/
void CG_ScorePlum( int client, vec3_t org, int score ) {
	localEntity_t	*le;
	refEntity_t		*re;
	vec3_t			angles;
	static vec3_t lastPos;

	// only visualize for the client that scored
	if (client != cg.predictedPlayerState.clientNum || cg_scorePlum.integer == 0) {
		return;
	}

	le = CG_AllocLocalEntity();
	le->leFlags = 0;
	le->leType = LE_SCOREPLUM;
	le->startTime = cg.time;
	le->endTime = cg.time + 4000;
	le->lifeRate = 1.0 / ( le->endTime - le->startTime );

	
	le->color[0] = le->color[1] = le->color[2] = le->color[3] = 1.0;
	le->radius = score;
	
	VectorCopy( org, le->pos.trBase );
	if (org[2] >= lastPos[2] - 20 && org[2] <= lastPos[2] + 20) {
		le->pos.trBase[2] -= 20;
	}

	//CG_Printf( "Plum origin %i %i %i -- %i\n", (int)org[0], (int)org[1], (int)org[2], (int)Distance(org, lastPos));
	VectorCopy(org, lastPos);


	re = &le->refEntity;

	re->reType = RT_SPRITE;
	re->radius = 16;

	VectorClear(angles);
	AnglesToAxis( angles, re->axis );
}


/*
====================
CG_MakeExplosion
====================
*/
localEntity_t *CG_MakeExplosion( vec3_t origin, vec3_t dir, 
								qhandle_t hModel, qhandle_t shader,
								int msec, qboolean isSprite ) {
	float			ang;
	localEntity_t	*ex;
	int				offset;
	vec3_t			tmpVec, newOrigin;

	if ( msec <= 0 ) {
		CG_Error( "CG_MakeExplosion: msec = %i", msec );
	}

	// skew the time a bit so they aren't all in sync
	offset = rand() & 63;

	ex = CG_AllocLocalEntity();
	if ( isSprite ) {
		ex->leType = LE_SPRITE_EXPLOSION;

		// randomly rotate sprite orientation
		ex->refEntity.rotation = rand() % 360;
		VectorScale( dir, 16, tmpVec );
		VectorAdd( tmpVec, origin, newOrigin );
	} else {
		ex->leType = LE_EXPLOSION;
		VectorCopy( origin, newOrigin );

		// set axis with random rotate
		if ( !dir ) {
			AxisClear( ex->refEntity.axis );
		} else {
			ang = rand() % 360;
			VectorCopy( dir, ex->refEntity.axis[0] );
			RotateAroundDirection( ex->refEntity.axis, ang );
		}
	}

	ex->startTime = cg.time - offset;
	ex->endTime = ex->startTime + msec;

	// bias the time so all shader effects start correctly
	ex->refEntity.shaderTime = ex->startTime / 1000.0f;

	ex->refEntity.hModel = hModel;
	ex->refEntity.customShader = shader;

	// set origin
	VectorCopy( newOrigin, ex->refEntity.origin );
	VectorCopy( newOrigin, ex->refEntity.oldorigin );
	
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
void CG_BleedSpray ( vec3_t start, vec3_t end, int entityNum, int numBursts )
{
	//vec3_t		dir;
	vec3_t		trueEnd;
	vec3_t		move;
	vec3_t		vec;
	vec3_t		velocity;

	localEntity_t	*blood;
	float		len;
	int			i;
	int			spacing = 30;
	int			bloodCount = 0;
	trace_t		tr;

	if ( !cg_blood.integer || cg_RQ3_bloodStyle.integer == 0) {
		return;
	}

	//Clamp number so we don't generate too many blood entities
	if (numBursts > MAX_SPRAY_BURSTS)
		numBursts = MAX_SPRAY_BURSTS;


	VectorCopy (end, move);
	VectorSubtract (end, start, vec);

	//Calculate true length via start/end points
	VectorCopy (vec, trueEnd);
	VectorNormalize (trueEnd);

	//VectorScale (trueEnd, 300 + rand() % 100, trueEnd); 
	//VectorAdd (end, trueEnd, trueEnd);
	VectorMA(end, 300 + rand() % 100, trueEnd, trueEnd);

	// Check end point validity so it doesn't go through walls
	// If it does go through wall, take the trace's endpoint
	CG_Trace(&tr, start, NULL, NULL, trueEnd, entityNum, CONTENTS_SOLID);
	if (tr.fraction != 1.0)
		VectorCopy(tr.endpos, trueEnd);

	VectorSubtract (trueEnd, start, vec);

	len = VectorNormalize (vec);
	
	//Set velocity
	VectorScale(vec, 10, velocity);
	if (cg_RQ3_bloodStyle.integer == 1)
		velocity[2] += 30;
	else
		velocity[2] -= 10;

	// advance a random amount first
	i = rand() % (int)spacing;
	VectorMA( move, i, vec, move );
	VectorScale (vec, spacing, vec);
	

	for ( ; i < len ; i += spacing )
	{
		//restrict amount of spurts
		if (bloodCount++ > numBursts)
			break;

		blood = CG_SmokePuff(move, velocity, 8,
					 1, 1, 1, 1,
					 1500 + rand() % 250,
					 cg.time, 0,
					 LEF_TUMBLE|LEF_PUFF_DONT_SCALE,
					 cgs.media.bloodTrailShader);

		blood->refEntity.rotation = rand() % 360;
		//Check blood style
		if (cg_RQ3_bloodStyle.integer == 1)
		{
			blood->leType = LE_FRAGMENT;
			blood->leMarkType = LEMT_BLOOD;
			blood->pos.trType = TR_GRAVITY;
			blood->bounceFactor = 0.4f;
		}

		VectorAdd (move, vec, move);
	}
}


/*
=================
CG_EjectBloodSplat

Drop a splat
=================
*/

void CG_EjectBloodSplat ( vec3_t origin, vec3_t velocity, int amount, int duration )
{
	int				i;
	localEntity_t	*blood;
	vec3_t			bOrigin;
	vec3_t			bVelocity;

	if ( !cg_blood.integer )
		return;	

	for (i = 0; i < amount; i++)
	{
		VectorCopy( origin, bOrigin );
		VectorCopy( velocity, bVelocity );
		bOrigin[0] += rand() % 6 - 3;
		bOrigin[1] += rand() % 6 - 3;
		bVelocity[0] += rand() % 6 - 3;
		bVelocity[1] += rand() % 6 - 3;

		blood = CG_SmokePuff( bOrigin, bVelocity, 4,
								1, 1, 1, 0.6f,
								duration + rand() % 250, cg.time, 0,
								LEF_TUMBLE|LEF_PUFF_DONT_SCALE,
								cgs.media.bloodTrailShader);
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

void CG_BleedParticleSpray ( vec3_t start, vec3_t dir, int fleshEntityNum, int amount, int duration)
{
	int i;

	if ( !cg_RQ3_bloodStyle.integer || !cg_blood.integer)
		return;

	for (i = 0; i < amount; i++)
	{
		CG_Particle_Bleed(cgs.media.bloodExplosionShader, start, dir, fleshEntityNum, duration + rand() % 250);
	}

}

/*
=================
CG_Bleed

This is the spurt of blood when a character gets hit
=================
*/
void CG_Bleed( vec3_t origin, int entityNum ) {
	localEntity_t	*ex;

	if ( !cg_blood.integer ) {
		return;
	}

	ex = CG_AllocLocalEntity();
	ex->leType = LE_EXPLOSION;

	ex->startTime = cg.time;
	ex->endTime = ex->startTime + 500;
	
	VectorCopy ( origin, ex->refEntity.origin);
	ex->refEntity.reType = RT_SPRITE;
	ex->refEntity.rotation = rand() % 360;
	ex->refEntity.radius = 24;

	ex->refEntity.customShader = cgs.media.bloodExplosionShader;

	// don't show player's own blood in view
	if ( entityNum == cg.snap->ps.clientNum ) {
		ex->refEntity.renderfx |= RF_THIRD_PERSON;
	}
}



/*
==================
CG_LaunchGib
==================
*/
void CG_LaunchGib( vec3_t origin, vec3_t velocity, qhandle_t hModel ) {
	localEntity_t	*le;
	refEntity_t		*re;

	le = CG_AllocLocalEntity();
	re = &le->refEntity;

	le->leType = LE_FRAGMENT;
	le->startTime = cg.time;
	le->endTime = le->startTime + 5000 + random() * 3000;

	VectorCopy( origin, re->origin );
	AxisCopy( axisDefault, re->axis );
	re->hModel = hModel;

	le->pos.trType = TR_GRAVITY;
	VectorCopy( origin, le->pos.trBase );
	VectorCopy( velocity, le->pos.trDelta );
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
void CG_GibPlayer( vec3_t playerOrigin ) {
	vec3_t	origin, velocity;

	if ( !cg_blood.integer ) {
		return;
	}

	VectorCopy( playerOrigin, origin );
	velocity[0] = crandom()*GIB_VELOCITY;
	velocity[1] = crandom()*GIB_VELOCITY;
	velocity[2] = GIB_JUMP + crandom()*GIB_VELOCITY;
	if ( rand() & 1 ) {
		CG_LaunchGib( origin, velocity, cgs.media.gibSkull );
	} else {
		CG_LaunchGib( origin, velocity, cgs.media.gibBrain );
	}

	// allow gibs to be turned off for speed
	if ( !cg_gibs.integer ) {
		return;
	}

	VectorCopy( playerOrigin, origin );
	velocity[0] = crandom()*GIB_VELOCITY;
	velocity[1] = crandom()*GIB_VELOCITY;
	velocity[2] = GIB_JUMP + crandom()*GIB_VELOCITY;
	CG_LaunchGib( origin, velocity, cgs.media.gibAbdomen );

	VectorCopy( playerOrigin, origin );
	velocity[0] = crandom()*GIB_VELOCITY;
	velocity[1] = crandom()*GIB_VELOCITY;
	velocity[2] = GIB_JUMP + crandom()*GIB_VELOCITY;
	CG_LaunchGib( origin, velocity, cgs.media.gibArm );

	VectorCopy( playerOrigin, origin );
	velocity[0] = crandom()*GIB_VELOCITY;
	velocity[1] = crandom()*GIB_VELOCITY;
	velocity[2] = GIB_JUMP + crandom()*GIB_VELOCITY;
	CG_LaunchGib( origin, velocity, cgs.media.gibChest );

	VectorCopy( playerOrigin, origin );
	velocity[0] = crandom()*GIB_VELOCITY;
	velocity[1] = crandom()*GIB_VELOCITY;
	velocity[2] = GIB_JUMP + crandom()*GIB_VELOCITY;
	CG_LaunchGib( origin, velocity, cgs.media.gibFist );

	VectorCopy( playerOrigin, origin );
	velocity[0] = crandom()*GIB_VELOCITY;
	velocity[1] = crandom()*GIB_VELOCITY;
	velocity[2] = GIB_JUMP + crandom()*GIB_VELOCITY;
	CG_LaunchGib( origin, velocity, cgs.media.gibFoot );

	VectorCopy( playerOrigin, origin );
	velocity[0] = crandom()*GIB_VELOCITY;
	velocity[1] = crandom()*GIB_VELOCITY;
	velocity[2] = GIB_JUMP + crandom()*GIB_VELOCITY;
	CG_LaunchGib( origin, velocity, cgs.media.gibForearm );

	VectorCopy( playerOrigin, origin );
	velocity[0] = crandom()*GIB_VELOCITY;
	velocity[1] = crandom()*GIB_VELOCITY;
	velocity[2] = GIB_JUMP + crandom()*GIB_VELOCITY;
	CG_LaunchGib( origin, velocity, cgs.media.gibIntestine );

	VectorCopy( playerOrigin, origin );
	velocity[0] = crandom()*GIB_VELOCITY;
	velocity[1] = crandom()*GIB_VELOCITY;
	velocity[2] = GIB_JUMP + crandom()*GIB_VELOCITY;
	CG_LaunchGib( origin, velocity, cgs.media.gibLeg );

	VectorCopy( playerOrigin, origin );
	velocity[0] = crandom()*GIB_VELOCITY;
	velocity[1] = crandom()*GIB_VELOCITY;
	velocity[2] = GIB_JUMP + crandom()*GIB_VELOCITY;
	CG_LaunchGib( origin, velocity, cgs.media.gibLeg );
}

/*
==================
CG_LaunchGib
==================
*/
void CG_LaunchExplode( vec3_t origin, vec3_t velocity, qhandle_t hModel ) {
	localEntity_t	*le;
	refEntity_t		*re;

	le = CG_AllocLocalEntity();
	re = &le->refEntity;

	le->leType = LE_FRAGMENT;
	le->startTime = cg.time;
	le->endTime = le->startTime + 10000 + random() * 6000;

	VectorCopy( origin, re->origin );
	AxisCopy( axisDefault, re->axis );
	re->hModel = hModel;

	le->pos.trType = TR_GRAVITY;
	VectorCopy( origin, le->pos.trBase );
	VectorCopy( velocity, le->pos.trDelta );
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
void CG_BigExplode( vec3_t playerOrigin ) {
	vec3_t	origin, velocity;

	if ( !cg_blood.integer ) {
		return;
	}

	VectorCopy( playerOrigin, origin );
	velocity[0] = crandom()*EXP_VELOCITY;
	velocity[1] = crandom()*EXP_VELOCITY;
	velocity[2] = EXP_JUMP + crandom()*EXP_VELOCITY;
	CG_LaunchExplode( origin, velocity, cgs.media.smoke2 );

	VectorCopy( playerOrigin, origin );
	velocity[0] = crandom()*EXP_VELOCITY;
	velocity[1] = crandom()*EXP_VELOCITY;
	velocity[2] = EXP_JUMP + crandom()*EXP_VELOCITY;
	CG_LaunchExplode( origin, velocity, cgs.media.smoke2 );

	VectorCopy( playerOrigin, origin );
	velocity[0] = crandom()*EXP_VELOCITY*1.5;
	velocity[1] = crandom()*EXP_VELOCITY*1.5;
	velocity[2] = EXP_JUMP + crandom()*EXP_VELOCITY;
	CG_LaunchExplode( origin, velocity, cgs.media.smoke2 );

	VectorCopy( playerOrigin, origin );
	velocity[0] = crandom()*EXP_VELOCITY*2.0;
	velocity[1] = crandom()*EXP_VELOCITY*2.0;
	velocity[2] = EXP_JUMP + crandom()*EXP_VELOCITY;
	CG_LaunchExplode( origin, velocity, cgs.media.smoke2 );

	VectorCopy( playerOrigin, origin );
	velocity[0] = crandom()*EXP_VELOCITY*2.5;
	velocity[1] = crandom()*EXP_VELOCITY*2.5;
	velocity[2] = EXP_JUMP + crandom()*EXP_VELOCITY;
	CG_LaunchExplode( origin, velocity, cgs.media.smoke2 );
}

#define	GLASS_VELOCITY	175
#define	GLASS_JUMP		125
/*
==================
CG_LaunchGlass
==================
*/
void CG_LaunchGlass( vec3_t origin, vec3_t velocity, vec3_t rotation,
					 float bounce, qhandle_t hModel )//, qhandle_t altSkin )
{
  	localEntity_t	*le;
  	refEntity_t		*re;
  
  	le = CG_AllocLocalEntity();
  	re = &le->refEntity;
  
  	le->leType = LE_FRAGMENT;
  	le->startTime = cg.time;
  	le->endTime = le->startTime + (random() * 3000)+ cg_RQ3_glasstime.integer; // + 30000;
	
  	VectorCopy( origin, re->origin );
  	AxisCopy( axisDefault, re->axis );
  	re->hModel = hModel;

	//Elder: custom shaders for debris?
	//if (altSkin)
		//re->customSkin = altSkin;


  	le->pos.trType = TR_GRAVITY;
  	VectorCopy( origin, le->pos.trBase );
  	VectorCopy( velocity, le->pos.trDelta );
  	le->pos.trTime = cg.time;
	
  	//Elder: added
  	//VectorCopy( origin, le->angles.trBase );
  	VectorCopy( velocity, le->angles.trBase );
  	le->angles.trBase[2] = le->angles.trBase[2] - GLASS_JUMP;
  	VectorCopy( rotation, le->angles.trDelta );
  	le->angles.trTime = cg.time;
  
  	le->bounceFactor = bounce;
	
  	le->leFlags = LEF_TUMBLE;
  	le->leBounceSoundType = LEBS_BRASS;
  	le->leMarkType = LEMT_NONE;
}
  
/*
===================
CG_BreakGlass

Generated a bunch of glass shards launching out from the glass location
Elder: don't be mislead by the name - this breaks more than glass
===================
*/
  
void CG_BreakGlass( vec3_t playerOrigin, int glassParm, int type ) {
  	vec3_t	origin, velocity, rotation;
    int     value;
  	int     count;
  	int     states[] = {1,2,3};			// Select model variations
  	// Get the size of the array
    int     numstates = sizeof(states)/sizeof(states[0]);
    // Elder: debris model handles
    qhandle_t	debris1;
	qhandle_t	debris2;
	qhandle_t	debris3;
	int		bounceFactor;
	int		newParm;

  	if ( (glassParm & RQ3_DEBRIS_MEDIUM) == RQ3_DEBRIS_MEDIUM &&
		 (glassParm & RQ3_DEBRIS_HIGH) == RQ3_DEBRIS_HIGH)
	{
		//Tons
  		count = 65 + rand() % 16;
  	}
 	else if ( (glassParm & RQ3_DEBRIS_HIGH) == RQ3_DEBRIS_HIGH)
	{
		//Large
  		count = 40 + rand() % 11;
  	}
  	else if ( (glassParm & RQ3_DEBRIS_MEDIUM) == RQ3_DEBRIS_MEDIUM)
	{
		//Medium
		count = 20 + rand() % 6;
  	}
  	else
	{
		//Small
  		count = 8 + rand() % 6;
	}

	/*
	===============================
	TODO: Utilize variation bits!
	==============================
	*/

	//Strip off amount info and revert eParm back to server-side size
	newParm = glassParm & 15;
	glassParm &= ~newParm;
	glassParm = glassParm << (type * 4);

	//CG_Printf("glassParm: %i\n", glassParm);

	//Elder: check debris type and assign debris models  	
	if ( (glassParm & RQ3_DEBRIS_WOOD) == RQ3_DEBRIS_WOOD)
	{
  		//CG_Printf("Launching wood\n");
  		debris1 = cgs.media.wood01;
  		debris2 = cgs.media.wood02;
  		debris3 = cgs.media.wood03;
		bounceFactor = 0.8f;
  	}
  	else if ( (glassParm & RQ3_DEBRIS_METAL) == RQ3_DEBRIS_METAL)
	{
  		//CG_Printf("Launching metal\n");
  		debris1 = cgs.media.metal01;
  		debris2 = cgs.media.metal02;
  		debris3 = cgs.media.metal03;
		bounceFactor = 0.7f;
  	}
  	else if ( (glassParm & RQ3_DEBRIS_CERAMIC) == RQ3_DEBRIS_CERAMIC)
	{ 
  		//CG_Printf("Launching ceramic\n");
  		debris1 = cgs.media.ceramic01;
  		debris2 = cgs.media.ceramic02;
  		debris3 = cgs.media.ceramic03;
		bounceFactor = 0.7f;
  	}
  	else if ( (glassParm & RQ3_DEBRIS_PAPER) == RQ3_DEBRIS_PAPER)
	{
  		//CG_Printf("Launching paper\n");
  		debris1 = cgs.media.paper01;
  		debris2 = cgs.media.paper02;
  		debris3 = cgs.media.paper03;
		bounceFactor = 0.2f;
  	}
	else if ( (glassParm & RQ3_DEBRIS_BRICK) == RQ3_DEBRIS_BRICK)
	{ 
  		//CG_Printf("Launching brick\n");
  		debris1 = cgs.media.brick01;
  		debris2 = cgs.media.brick02;
  		debris3 = cgs.media.brick03;
		bounceFactor = 0.4f;
  	}
	else if ( (glassParm & RQ3_DEBRIS_CONCRETE) == RQ3_DEBRIS_CONCRETE)
	{ 
  		//CG_Printf("Launching concrete\n");
  		debris1 = cgs.media.concrete01;
  		debris2 = cgs.media.concrete02;
  		debris3 = cgs.media.concrete03;
		bounceFactor = 0.5f;
  	}
	/*
	else if ( (glassParm & RQ3_DEBRIS_POPCAN) == RQ3_DEBRIS_POPCAN)
	{ 
  		CG_Printf("Launching pop cans\n");
  		debris1 = cgs.media.popcan01;
  		debris2 = cgs.media.popcan02;
  		debris3 = cgs.media.popcan03;
  	}
	*/
  	else
	{
  		//glass is default
  		//CG_Printf("Launching glass\n");
  		debris1 = cgs.media.glass01;
  		debris2 = cgs.media.glass02;
  		debris3 = cgs.media.glass03;
		bounceFactor = 0.7f;
  	}
  	
	//launch loop
  	while ( count-- ) {
      	// Generate the random number every count so every shard is a
      	// of the three. If this is placed above it only gets a random
      	// number every time a piece of glass is broken.
      	value = states[rand()%numstates];

		VectorCopy( playerOrigin, origin );
      	velocity[0] = crandom() * GLASS_VELOCITY;
      	velocity[1] = crandom() * GLASS_VELOCITY;
      	velocity[2] = GLASS_JUMP + crandom() * GLASS_VELOCITY;
		//Elder: added
		rotation[0] = crandom() * GLASS_VELOCITY;
		rotation[1] = crandom() * GLASS_VELOCITY;
		rotation[2] = crandom() * GLASS_VELOCITY;
      	
		switch (value)
		{
      	case 1:
          	CG_LaunchGlass( origin, velocity, rotation, bounceFactor, debris1 );
          	break;
      	case 2:
      		CG_LaunchGlass( origin, velocity, rotation, bounceFactor, debris2 );
          	break;
      	case 3:
      		CG_LaunchGlass( origin, velocity, rotation, bounceFactor, debris3 );
      		break;
      	}
  	}
}
