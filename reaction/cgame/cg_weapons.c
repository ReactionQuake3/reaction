// Copyright (C) 1999-2000 Id Software, Inc.
//
// cg_weapons.c -- events and effects dealing with weapons
#include "cg_local.h"

/*
==========================
CG_MachineGunEjectBrass
==========================
*/
static void CG_MachineGunEjectBrass( centity_t *cent ) {
	localEntity_t	*le;
	refEntity_t		*re;
	vec3_t			velocity, xvelocity;
	vec3_t			offset, xoffset;
	float			waterScale = 1.0f;
	vec3_t			v[3];

	if ( cg_brassTime.integer <= 0 ) {
		return;
	}

	le = CG_AllocLocalEntity();
	re = &le->refEntity;

	velocity[0] = 0;
	velocity[1] = -50 + 40 * crandom();
	velocity[2] = 100 + 50 * crandom();

	le->leType = LE_FRAGMENT;
	le->startTime = cg.time;
	le->endTime = le->startTime + cg_brassTime.integer + ( cg_brassTime.integer / 4 ) * random();

	le->pos.trType = TR_GRAVITY;
	le->pos.trTime = cg.time - (rand()&15);

	AnglesToAxis( cent->lerpAngles, v );

	offset[0] = 8;
	offset[1] = -4;
	offset[2] = 24;

	xoffset[0] = offset[0] * v[0][0] + offset[1] * v[1][0] + offset[2] * v[2][0];
	xoffset[1] = offset[0] * v[0][1] + offset[1] * v[1][1] + offset[2] * v[2][1];
	xoffset[2] = offset[0] * v[0][2] + offset[1] * v[1][2] + offset[2] * v[2][2];
	VectorAdd( cent->lerpOrigin, xoffset, re->origin );

	VectorCopy( re->origin, le->pos.trBase );

	if ( CG_PointContents( re->origin, -1 ) & CONTENTS_WATER ) {
		waterScale = 0.10f;
	}

	xvelocity[0] = velocity[0] * v[0][0] + velocity[1] * v[1][0] + velocity[2] * v[2][0];
	xvelocity[1] = velocity[0] * v[0][1] + velocity[1] * v[1][1] + velocity[2] * v[2][1];
	xvelocity[2] = velocity[0] * v[0][2] + velocity[1] * v[1][2] + velocity[2] * v[2][2];
	VectorScale( xvelocity, waterScale, le->pos.trDelta );

	AxisCopy( axisDefault, re->axis );
	re->hModel = cgs.media.machinegunBrassModel;

	le->bounceFactor = 0.4 * waterScale;

	le->angles.trType = TR_LINEAR;
	le->angles.trTime = cg.time;
	le->angles.trBase[0] = rand()&31;
	le->angles.trBase[1] = rand()&31;
	le->angles.trBase[2] = rand()&31;
	le->angles.trDelta[0] = 2;
	le->angles.trDelta[1] = 1;
	le->angles.trDelta[2] = 0;

	le->leFlags = LEF_TUMBLE;
	le->leBounceSoundType = LEBS_BRASS;
	le->leMarkType = LEMT_NONE;
}

/*
==========================
CG_ShotgunEjectBrass
==========================
*/
static void CG_ShotgunEjectBrass( centity_t *cent ) {
	localEntity_t	*le;
	refEntity_t		*re;
	vec3_t			velocity, xvelocity;
	vec3_t			offset, xoffset;
	vec3_t			v[3];
	int				i,isHC;
	if (cent->currentState.weapon == WP_HANDCANNON) isHC=1;
	else
	{
		isHC=0;
	}

	if ( cg_brassTime.integer <= 0 ) {
		return;
	}

	for ( i = 0; i < isHC + 1; i++ ) {
		float	waterScale = 1.0f;

		le = CG_AllocLocalEntity();
		re = &le->refEntity;

		velocity[0] = 60 + 60 * crandom();
		if ( i == 0 ) {
			velocity[1] = 40 + 10 * crandom();
		} else {
			velocity[1] = -40 + 10 * crandom();
		}
		velocity[2] = 100 + 50 * crandom();

		le->leType = LE_FRAGMENT;
		le->startTime = cg.time;
		le->endTime = le->startTime + cg_brassTime.integer*3 + cg_brassTime.integer * random();

		le->pos.trType = TR_GRAVITY;
		le->pos.trTime = cg.time;

		AnglesToAxis( cent->lerpAngles, v );

		offset[0] = 8;
		offset[1] = 0;
		offset[2] = 24;

		xoffset[0] = offset[0] * v[0][0] + offset[1] * v[1][0] + offset[2] * v[2][0];
		xoffset[1] = offset[0] * v[0][1] + offset[1] * v[1][1] + offset[2] * v[2][1];
		xoffset[2] = offset[0] * v[0][2] + offset[1] * v[1][2] + offset[2] * v[2][2];
		VectorAdd( cent->lerpOrigin, xoffset, re->origin );
		VectorCopy( re->origin, le->pos.trBase );
		if ( CG_PointContents( re->origin, -1 ) & CONTENTS_WATER ) {
			waterScale = 0.10f;
		}

		xvelocity[0] = velocity[0] * v[0][0] + velocity[1] * v[1][0] + velocity[2] * v[2][0];
		xvelocity[1] = velocity[0] * v[0][1] + velocity[1] * v[1][1] + velocity[2] * v[2][1];
		xvelocity[2] = velocity[0] * v[0][2] + velocity[1] * v[1][2] + velocity[2] * v[2][2];
		VectorScale( xvelocity, waterScale, le->pos.trDelta );

		AxisCopy( axisDefault, re->axis );

		re->hModel = cgs.media.shotgunBrassModel;
		le->bounceFactor = 0.3f;

		le->angles.trType = TR_LINEAR;
		le->angles.trTime = cg.time;
		le->angles.trBase[0] = rand()&31;
		le->angles.trBase[1] = rand()&31;
		le->angles.trBase[2] = rand()&31;
		le->angles.trDelta[0] = 1;
		le->angles.trDelta[1] = 0.5;
		le->angles.trDelta[2] = 0;

		le->leFlags = LEF_TUMBLE;
		le->leBounceSoundType = LEBS_BRASS;
		le->leMarkType = LEMT_NONE;
	}
}


#ifdef MISSIONPACK
/*
==========================
CG_NailgunEjectBrass
==========================
*/
static void CG_NailgunEjectBrass( centity_t *cent ) {
	localEntity_t	*smoke;
	vec3_t			origin;
	vec3_t			v[3];
	vec3_t			offset;
	vec3_t			xoffset;
	vec3_t			up;

	AnglesToAxis( cent->lerpAngles, v );

	offset[0] = 0;
	offset[1] = -12;
	offset[2] = 24;

	xoffset[0] = offset[0] * v[0][0] + offset[1] * v[1][0] + offset[2] * v[2][0];
	xoffset[1] = offset[0] * v[0][1] + offset[1] * v[1][1] + offset[2] * v[2][1];
	xoffset[2] = offset[0] * v[0][2] + offset[1] * v[1][2] + offset[2] * v[2][2];
	VectorAdd( cent->lerpOrigin, xoffset, origin );

	VectorSet( up, 0, 0, 64 );

	smoke = CG_SmokePuff( origin, up, 32, 1, 1, 1, 0.33f, 700, cg.time, 0, 0, cgs.media.smokePuffShader );
	// use the optimized local entity add
	smoke->leType = LE_SCALE_FADE;
}
#endif


/*
==========================
CG_RailTrail
==========================
*/
void CG_RailTrail( clientInfo_t *ci, vec3_t start, vec3_t end ) {
	localEntity_t	*le;
	refEntity_t		*re;

	//
	// rings
	//
	le = CG_AllocLocalEntity();
	re = &le->refEntity;

	le->leType = LE_FADE_RGB;
	le->startTime = cg.time;
	le->endTime = cg.time + cg_railTrailTime.value;
	le->lifeRate = 1.0 / ( le->endTime - le->startTime );

	re->shaderTime = cg.time / 1000.0f;
	re->reType = RT_RAIL_RINGS;
	re->customShader = cgs.media.railRingsShader;
	
	VectorCopy( start, re->origin );
	VectorCopy( end, re->oldorigin );

	// nudge down a bit so it isn't exactly in center
	re->origin[2] -= 8;
	re->oldorigin[2] -= 8;

	le->color[0] = ci->color[0] * 0.75;
	le->color[1] = ci->color[1] * 0.75;
	le->color[2] = ci->color[2] * 0.75;
	le->color[3] = 1.0f;

	AxisClear( re->axis );

	//
	// core
	//
	le = CG_AllocLocalEntity();
	re = &le->refEntity;

	le->leType = LE_FADE_RGB;
	le->startTime = cg.time;
	le->endTime = cg.time + cg_railTrailTime.value;
	le->lifeRate = 1.0 / ( le->endTime - le->startTime );

	re->shaderTime = cg.time / 1000.0f;
	re->reType = RT_RAIL_CORE;
	re->customShader = cgs.media.railCoreShader;

	VectorCopy( start, re->origin );
	VectorCopy( end, re->oldorigin );

	// nudge down a bit so it isn't exactly in center
	re->origin[2] -= 8;
	re->oldorigin[2] -= 8;

	le->color[0] = ci->color[0] * 0.75;
	le->color[1] = ci->color[1] * 0.75;
	le->color[2] = ci->color[2] * 0.75;
	le->color[3] = 1.0f;

	AxisClear( re->axis );
}

/*
==========================
CG_RocketTrail
==========================
*/
static void CG_RocketTrail( centity_t *ent, const weaponInfo_t *wi ) {
	int		step;
	vec3_t	origin, lastPos;
	int		t;
	int		startTime, contents;
	int		lastContents;
	entityState_t	*es;
	vec3_t	up;
	localEntity_t	*smoke;

	up[0] = 0;
	up[1] = 0;
	up[2] = 0;

	step = 50;

	es = &ent->currentState;
	startTime = ent->trailTime;
	t = step * ( (startTime + step) / step );

	BG_EvaluateTrajectory( &es->pos, cg.time, origin );
	contents = CG_PointContents( origin, -1 );

	// if object (e.g. grenade) is stationary, don't toss up smoke
	if ( es->pos.trType == TR_STATIONARY ) {
		ent->trailTime = cg.time;
		return;
	}

	BG_EvaluateTrajectory( &es->pos, ent->trailTime, lastPos );
	lastContents = CG_PointContents( lastPos, -1 );

	ent->trailTime = cg.time;

	if ( contents & ( CONTENTS_WATER | CONTENTS_SLIME | CONTENTS_LAVA ) ) {
		if ( contents & lastContents & CONTENTS_WATER ) {
			CG_BubbleTrail( lastPos, origin, 8 );
		}
		return;
	}

	for ( ; t <= ent->trailTime ; t += step ) {
		BG_EvaluateTrajectory( &es->pos, t, lastPos );

		smoke = CG_SmokePuff( lastPos, up, 
					  wi->trailRadius, 
					  1, 1, 1, 0.33f,
					  wi->wiTrailTime, 
					  t,
					  0,
					  0, 
					  cgs.media.smokePuffShader );
		// use the optimized local entity add
		smoke->leType = LE_SCALE_FADE;
	}

}

#ifdef MISSIONPACK
/*
==========================
CG_NailTrail
==========================
*/
static void CG_NailTrail( centity_t *ent, const weaponInfo_t *wi ) {
	int		step;
	vec3_t	origin, lastPos;
	int		t;
	int		startTime, contents;
	int		lastContents;
	entityState_t	*es;
	vec3_t	up;
	localEntity_t	*smoke;

	up[0] = 0;
	up[1] = 0;
	up[2] = 0;

	step = 50;

	es = &ent->currentState;
	startTime = ent->trailTime;
	t = step * ( (startTime + step) / step );

	BG_EvaluateTrajectory( &es->pos, cg.time, origin );
	contents = CG_PointContents( origin, -1 );

	// if object (e.g. grenade) is stationary, don't toss up smoke
	if ( es->pos.trType == TR_STATIONARY ) {
		ent->trailTime = cg.time;
		return;
	}

	BG_EvaluateTrajectory( &es->pos, ent->trailTime, lastPos );
	lastContents = CG_PointContents( lastPos, -1 );

	ent->trailTime = cg.time;

	if ( contents & ( CONTENTS_WATER | CONTENTS_SLIME | CONTENTS_LAVA ) ) {
		if ( contents & lastContents & CONTENTS_WATER ) {
			CG_BubbleTrail( lastPos, origin, 8 );
		}
		return;
	}

	for ( ; t <= ent->trailTime ; t += step ) {
		BG_EvaluateTrajectory( &es->pos, t, lastPos );

		smoke = CG_SmokePuff( lastPos, up, 
					  wi->trailRadius, 
					  1, 1, 1, 0.33f,
					  wi->wiTrailTime, 
					  t,
					  0,
					  0, 
					  cgs.media.nailPuffShader );
		// use the optimized local entity add
		smoke->leType = LE_SCALE_FADE;
	}

}
#endif

/*
==========================
CG_GrappleTrail
==========================
*/
void CG_GrappleTrail( centity_t *ent, const weaponInfo_t *wi ) {
	vec3_t	origin;
	entityState_t	*es;
	vec3_t			forward, up;
	refEntity_t		beam;

	es = &ent->currentState;

	BG_EvaluateTrajectory( &es->pos, cg.time, origin );
	ent->trailTime = cg.time;

	memset( &beam, 0, sizeof( beam ) );
	//FIXME adjust for muzzle position
	VectorCopy ( cg_entities[ ent->currentState.otherEntityNum ].lerpOrigin, beam.origin );
	beam.origin[2] += 26;
	AngleVectors( cg_entities[ ent->currentState.otherEntityNum ].lerpAngles, forward, NULL, up );
	VectorMA( beam.origin, -6, up, beam.origin );
	VectorCopy( origin, beam.oldorigin );

	if (Distance( beam.origin, beam.oldorigin ) < 64 )
		return; // Don't draw if close

	beam.reType = RT_LIGHTNING;
	beam.customShader = cgs.media.lightningShader;

	AxisClear( beam.axis );
	beam.shaderRGBA[0] = 0xff;
	beam.shaderRGBA[1] = 0xff;
	beam.shaderRGBA[2] = 0xff;
	beam.shaderRGBA[3] = 0xff;
	trap_R_AddRefEntityToScene( &beam );
}

/*
==========================
CG_GrenadeTrail
==========================
*/
static void CG_GrenadeTrail( centity_t *ent, const weaponInfo_t *wi ) {
	//Elder: removed smoke trail
	//CG_RocketTrail( ent, wi );
}


/*
=================
CG_RegisterWeapon

The server says this item is used on this level
=================
*/
void CG_RegisterWeapon( int weaponNum ) {
	weaponInfo_t	*weaponInfo;
	gitem_t			*item, *ammo;
	char			path[MAX_QPATH];
	vec3_t			mins, maxs;
	int				i;

	weaponInfo = &cg_weapons[weaponNum];

	if ( weaponNum == 0 ) {
		return;
	}

	if ( weaponInfo->registered ) {
		return;
	}

	memset( weaponInfo, 0, sizeof( *weaponInfo ) );
	weaponInfo->registered = qtrue;
	
	for ( item = bg_itemlist + 1 ; item->classname ; item++ ) {
		if ( item->giType == IT_WEAPON && item->giTag == weaponNum ) {
			weaponInfo->item = item;
			break;
		}
	}

	if ( !item->classname ) {
		CG_Error( "Couldn't find weapon %i", weaponNum );
	}
	CG_RegisterItemVisuals( item - bg_itemlist );

	// load cmodel before model so filecache works
	weaponInfo->weaponModel = trap_R_RegisterModel( item->world_model[0] );

	// calc midpoint for rotation
	trap_R_ModelBounds( weaponInfo->weaponModel, mins, maxs );
	for ( i = 0 ; i < 3 ; i++ ) {
		weaponInfo->weaponMidpoint[i] = mins[i] + 0.5 * ( maxs[i] - mins[i] );
	}

	weaponInfo->weaponIcon = trap_R_RegisterShader( item->icon );
	weaponInfo->ammoIcon = trap_R_RegisterShader( item->icon );

	for ( ammo = bg_itemlist + 1 ; ammo->classname ; ammo++ ) {
		if ( ammo->giType == IT_AMMO && ammo->giTag == weaponNum ) {
			break;
		}
		//Elder: hack for handcannon to use M3 ammo icon
		else if (weaponNum == WP_HANDCANNON && ammo->giType == IT_AMMO && ammo->giTag == WP_M3)
		{
			break;
		}
		//Elder: hack for akimbos to use MK23 ammo icon
		else if (weaponNum == WP_AKIMBO && ammo->giType == IT_AMMO && ammo->giTag == WP_PISTOL)
		{
			break;
		}
	}
	if ( ammo->classname && ammo->world_model[0] ) {
		weaponInfo->ammoModel = trap_R_RegisterModel( ammo->world_model[0] );
		//Elder: added
		weaponInfo->ammoIcon = trap_R_RegisterShader( ammo->icon );
	}

	strcpy( path, item->world_model[0] );
	COM_StripExtension( path, path );
	strcat( path, "_flash.md3" );
	weaponInfo->flashModel = trap_R_RegisterModel( path );

	strcpy( path, item->world_model[0] );
	COM_StripExtension( path, path );
	strcat( path, "_barrel.md3" );
	weaponInfo->barrelModel = trap_R_RegisterModel( path );

	strcpy( path, item->world_model[0] );
	COM_StripExtension( path, path );
	strcat( path, "_hand.md3" );
	weaponInfo->handsModel = trap_R_RegisterModel( path );

	//Elder: added to cache 3rd-person models (hopefully)
	strcpy( path, item->world_model[0] );
	COM_StripExtension( path, path );
	//Elder: changed from _3rd to _1st
	strcat( path, "_1st.md3" );
	weaponInfo->firstModel = trap_R_RegisterModel( path );

	if ( !weaponInfo->handsModel ) {
		//Elder: WTF!?
		weaponInfo->handsModel = trap_R_RegisterModel( "models/weapons2/m3/m3_hand.md3" );
	}
	
	//Elder: if no _1st model, point to the weaponModel... this may get funky :)
	if ( !weaponInfo->firstModel ) {
		weaponInfo->firstModel = weaponInfo->weaponModel;
	}

	weaponInfo->loopFireSound = qfalse;
	switch ( weaponNum ) {
/*Blaze: Dont need this
	case WP_GAUNTLET:
		MAKERGB( weaponInfo->flashDlightColor, 0.6f, 0.6f, 1.0f );
		weaponInfo->firingSound = trap_S_RegisterSound( "sound/weapons/melee/fstrun.wav", qfalse );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/melee/fstatck.wav", qfalse );
		break;

	case WP_LIGHTNING:
		MAKERGB( weaponInfo->flashDlightColor, 0.6f, 0.6f, 1.0f );
		weaponInfo->readySound = trap_S_RegisterSound( "sound/weapons/melee/fsthum.wav", qfalse );
		weaponInfo->firingSound = trap_S_RegisterSound( "sound/weapons/lightning/lg_hum.wav", qfalse );

		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/lightning/lg_fire.wav", qfalse );
		cgs.media.lightningShader = trap_R_RegisterShader( "lightningBolt");
		cgs.media.lightningExplosionModel = trap_R_RegisterModel( "models/weaphits/crackle.md3" );
		cgs.media.sfx_lghit1 = trap_S_RegisterSound( "sound/weapons/lightning/lg_hit.wav", qfalse );
		cgs.media.sfx_lghit2 = trap_S_RegisterSound( "sound/weapons/lightning/lg_hit2.wav", qfalse );
		cgs.media.sfx_lghit3 = trap_S_RegisterSound( "sound/weapons/lightning/lg_hit3.wav", qfalse );

		break;

	case WP_GRAPPLING_HOOK:
		MAKERGB( weaponInfo->flashDlightColor, 0.6f, 0.6f, 1.0f );
		weaponInfo->missileModel = trap_R_RegisterModel( "models/ammo/rocket/rocket.md3" );
		weaponInfo->missileTrailFunc = CG_GrappleTrail;
		weaponInfo->missileDlight = 200;
		weaponInfo->wiTrailTime = 2000;
		weaponInfo->trailRadius = 64;
		MAKERGB( weaponInfo->missileDlightColor, 1, 0.75f, 0 );
		weaponInfo->readySound = trap_S_RegisterSound( "sound/weapons/melee/fsthum.wav", qfalse );
		weaponInfo->firingSound = trap_S_RegisterSound( "sound/weapons/melee/fstrun.wav", qfalse );
		break;

#ifdef MISSIONPACK
	case WP_CHAINGUN:
		weaponInfo->firingSound = trap_S_RegisterSound( "sound/weapons/vulcan/wvulfire.wav", qfalse );
		weaponInfo->loopFireSound = qtrue;
		MAKERGB( weaponInfo->flashDlightColor, 1, 1, 0 );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/vulcan/vulcanf1b.wav", qfalse );
		weaponInfo->flashSound[1] = trap_S_RegisterSound( "sound/weapons/vulcan/vulcanf2b.wav", qfalse );
		weaponInfo->flashSound[2] = trap_S_RegisterSound( "sound/weapons/vulcan/vulcanf3b.wav", qfalse );
		weaponInfo->flashSound[3] = trap_S_RegisterSound( "sound/weapons/vulcan/vulcanf4b.wav", qfalse );
		weaponInfo->ejectBrassFunc = CG_MachineGunEjectBrass;
		cgs.media.bulletExplosionShader = trap_R_RegisterShader( "bulletExplosion" );
		break;
#endif

	case WP_MACHINEGUN:
		MAKERGB( weaponInfo->flashDlightColor, 1, 1, 0 );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/machinegun/machgf1b.wav", qfalse );
		weaponInfo->flashSound[1] = trap_S_RegisterSound( "sound/weapons/machinegun/machgf2b.wav", qfalse );
		weaponInfo->flashSound[2] = trap_S_RegisterSound( "sound/weapons/machinegun/machgf3b.wav", qfalse );
		weaponInfo->flashSound[3] = trap_S_RegisterSound( "sound/weapons/machinegun/machgf4b.wav", qfalse );
		weaponInfo->ejectBrassFunc = CG_MachineGunEjectBrass;
		cgs.media.bulletExplosionShader = trap_R_RegisterShader( "bulletExplosion" );
		break;

	case WP_SHOTGUN:
		MAKERGB( weaponInfo->flashDlightColor, 1, 1, 0 );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/shotgun/sshotf1b.wav", qfalse );
		weaponInfo->ejectBrassFunc = CG_ShotgunEjectBrass;
		break;

	case WP_ROCKET_LAUNCHER:
		weaponInfo->missileModel = trap_R_RegisterModel( "models/ammo/rocket/rocket.md3" );
		weaponInfo->missileSound = trap_S_RegisterSound( "sound/weapons/rocket/rockfly.wav", qfalse );
		weaponInfo->missileTrailFunc = CG_RocketTrail;
		weaponInfo->missileDlight = 200;
		weaponInfo->wiTrailTime = 2000;
		weaponInfo->trailRadius = 64;
		
		MAKERGB( weaponInfo->missileDlightColor, 1, 0.75f, 0 );
		MAKERGB( weaponInfo->flashDlightColor, 1, 0.75f, 0 );

		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/rocket/rocklf1a.wav", qfalse );
		cgs.media.rocketExplosionShader = trap_R_RegisterShader( "rocketExplosion" );
		break;

#ifdef MISSIONPACK
	case WP_PROX_LAUNCHER:
		weaponInfo->missileModel = trap_R_RegisterModel( "models/weaphits/proxmine.md3" );
		weaponInfo->missileTrailFunc = CG_GrenadeTrail;
		weaponInfo->wiTrailTime = 700;
		weaponInfo->trailRadius = 32;
		MAKERGB( weaponInfo->flashDlightColor, 1, 0.70f, 0 );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/proxmine/wstbfire.wav", qfalse );
		cgs.media.grenadeExplosionShader = trap_R_RegisterShader( "grenadeExplosion" );
		break;
#endif

	case WP_GRENADE_LAUNCHER:
		weaponInfo->missileModel = trap_R_RegisterModel( "models/ammo/grenade1.md3" );
		weaponInfo->missileTrailFunc = CG_GrenadeTrail;
		weaponInfo->wiTrailTime = 700;
		weaponInfo->trailRadius = 32;
		MAKERGB( weaponInfo->flashDlightColor, 1, 0.70f, 0 );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/grenade/grenlf1a.wav", qfalse );
		cgs.media.grenadeExplosionShader = trap_R_RegisterShader( "grenadeExplosion" );
		break;

#ifdef MISSIONPACK
	case WP_NAILGUN:
		weaponInfo->ejectBrassFunc = CG_NailgunEjectBrass;
		weaponInfo->missileTrailFunc = CG_NailTrail;
		weaponInfo->missileSound = trap_S_RegisterSound( "sound/weapons/nailgun/wnalflit.wav", qfalse );
		weaponInfo->trailRadius = 16;
		weaponInfo->wiTrailTime = 250;
		weaponInfo->missileModel = trap_R_RegisterModel( "models/weaphits/nail.md3" );
		MAKERGB( weaponInfo->flashDlightColor, 1, 0.75f, 0 );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/nailgun/wnalfire.wav", qfalse );
		break;
#endif

	case WP_PLASMAGUN:
		weaponInfo->missileSound = trap_S_RegisterSound( "sound/weapons/plasma/lasfly.wav", qfalse );
		MAKERGB( weaponInfo->flashDlightColor, 0.6f, 0.6f, 1.0f );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/plasma/hyprbf1a.wav", qfalse );
		cgs.media.plasmaExplosionShader = trap_R_RegisterShader( "plasmaExplosion" );
		break;

	case WP_RAILGUN:
		weaponInfo->readySound = trap_S_RegisterSound( "sound/weapons/railgun/rg_hum.wav", qfalse );
		MAKERGB( weaponInfo->flashDlightColor, 1, 0.5f, 0 );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/railgun/railgf1a.wav", qfalse );
		cgs.media.railExplosionShader = trap_R_RegisterShader( "railExplosion" );
		cgs.media.railRingsShader = trap_R_RegisterShader( "railDisc" );
		cgs.media.railCoreShader = trap_R_RegisterShader( "railCore" );
		break;

	case WP_BFG:
		weaponInfo->readySound = trap_S_RegisterSound( "sound/weapons/bfg/bfg_hum.wav", qfalse );
		MAKERGB( weaponInfo->flashDlightColor, 1, 0.7f, 1 );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/bfg/bfg_fire.wav", qfalse );
		cgs.media.bfgExplosionShader = trap_R_RegisterShader( "bfgExplosion" );
		weaponInfo->missileModel = trap_R_RegisterModel( "models/weaphits/bfg.md3" );
		weaponInfo->missileSound = trap_S_RegisterSound( "sound/weapons/rocket/rockfly.wav", qfalse );
		break;
*/
//Blaze: Reaction Pistol
	case WP_PISTOL:
		MAKERGB( weaponInfo->flashDlightColor, 1, 1, 0 );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/mk23/mk23fire.wav", qfalse );
		weaponInfo->ejectBrassFunc = CG_MachineGunEjectBrass;
		cgs.media.bulletExplosionShader = trap_R_RegisterShader( "bulletExplosion" );
		break;
		
	case WP_KNIFE:
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/knife/slash.wav", qfalse );
		weaponInfo->missileModel = trap_R_RegisterModel("models/weapons2/knife/knife.md3");
		//weaponInfo->missileTrailFunc = CG_GrenadeTrail;
		MAKERGB( weaponInfo->flashDlightColor, 1, 0.70f, 0 );
		//cgs.media.grenadeExplosionShader = trap_R_RegisterShader( "grenadeExplosion" );
		weaponInfo->wiTrailTime = 700;
		weaponInfo->trailRadius = 32;
		break;
		
	case WP_M4:
		//Elder: added
		MAKERGB( weaponInfo->flashDlightColor, 1, 1, 0 );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/m4/m4fire.wav", qfalse );
		weaponInfo->ejectBrassFunc = CG_MachineGunEjectBrass;
		cgs.media.bulletExplosionShader = trap_R_RegisterShader( "bulletExplosion" );
		break;
		
	case WP_SSG3000:
		//Elder: added
		MAKERGB( weaponInfo->flashDlightColor, 1, 0.5f, 0 );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/ssg3000/ssgfire.wav", qfalse );
		weaponInfo->ejectBrassFunc = CG_MachineGunEjectBrass;
		cgs.media.bulletExplosionShader = trap_R_RegisterShader( "bulletExplosion" );
		break;
		
	case WP_MP5:
		//Elder: added
		MAKERGB( weaponInfo->flashDlightColor, 1, 0.75f, 0 );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/mp5/mp5fire.wav", qfalse );
		weaponInfo->ejectBrassFunc = CG_MachineGunEjectBrass;
		cgs.media.bulletExplosionShader = trap_R_RegisterShader( "bulletExplosion" );
		break;
		
	case WP_HANDCANNON:
		//Elder: added
		MAKERGB( weaponInfo->flashDlightColor, 1, 1, 0 );
		//Elder: changed to hcfire from cannon_fire
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/handcannon/hcfire.wav", qfalse );
		weaponInfo->ejectBrassFunc = CG_ShotgunEjectBrass;
		cgs.media.bulletExplosionShader = trap_R_RegisterShader( "bulletExplosion" );
		break;
		
	case WP_M3:
		MAKERGB( weaponInfo->flashDlightColor, 1, 1, 0 );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/m3/m3fire.wav", qfalse );
		weaponInfo->ejectBrassFunc = CG_ShotgunEjectBrass;
		break;
		
	case WP_AKIMBO:
		//Elder: added
		MAKERGB( weaponInfo->flashDlightColor, 1, 1, 0.5f );
		//Elder: changed to use pseudo-dual sound
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/akimbo/akimbofire.wav", qfalse );
		weaponInfo->flashSound[1] = trap_S_RegisterSound( "sound/weapons/akimbo/akimbofire.wav", qfalse );
		//weaponInfo->flashSound[1] = trap_S_RegisterSound( "sound/weapons/mk23/mk23fire.wav", qfalse );
		weaponInfo->ejectBrassFunc = CG_MachineGunEjectBrass;
		cgs.media.bulletExplosionShader = trap_R_RegisterShader( "bulletExplosion" );
		break;
		
	case WP_GRENADE:
		//Changed from _3rd
		weaponInfo->missileModel = trap_R_RegisterModel( "models/weapons2/grenade/grenade.md3" );
		weaponInfo->missileTrailFunc = CG_GrenadeTrail;
		weaponInfo->wiTrailTime = 700;
		weaponInfo->trailRadius = 32;
		MAKERGB( weaponInfo->flashDlightColor, 1, 0.70f, 0 );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/grenade/grenlf1a.wav", qfalse );
		cgs.media.grenadeExplosionShader = trap_R_RegisterShader( "grenadeExplosion" );
		break;

	 default:
		//MAKERGB( weaponInfo->flashDlightColor, 1, 1, 1 );
		//weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/rocket/rocklf1a.wav", qfalse );
		break;
	}
}

/*
=================
CG_RegisterItemVisuals

The server says this item is used on this level
=================
*/
void CG_RegisterItemVisuals( int itemNum ) {
	itemInfo_t		*itemInfo;
	gitem_t			*item;

	itemInfo = &cg_items[ itemNum ];
	if ( itemInfo->registered ) {
		return;
	}

	item = &bg_itemlist[ itemNum ];

	memset( itemInfo, 0, sizeof( &itemInfo ) );
	itemInfo->registered = qtrue;

	itemInfo->models[0] = trap_R_RegisterModel( item->world_model[0] );

	itemInfo->icon = trap_R_RegisterShader( item->icon );

	if ( item->giType == IT_WEAPON ) {
		CG_RegisterWeapon( item->giTag );
	}

	//
	// powerups have an accompanying ring or sphere
	//
	if ( item->giType == IT_POWERUP || item->giType == IT_HEALTH || 
		item->giType == IT_ARMOR || item->giType == IT_HOLDABLE ) {
		if ( item->world_model[1] ) {
			itemInfo->models[1] = trap_R_RegisterModel( item->world_model[1] );
		}
	}
}


/*
========================================================================================

VIEW WEAPON

========================================================================================
*/

/*
=================
CG_MapTorsoToWeaponFrame

=================
*/
static int CG_MapTorsoToWeaponFrame( clientInfo_t *ci, int frame ) {

	// change weapon
	if ( frame >= ci->animations[TORSO_DROP].firstFrame 
		&& frame < ci->animations[TORSO_DROP].firstFrame + 9 ) {
		return frame - ci->animations[TORSO_DROP].firstFrame + 6;
	}

	// stand attack
	if ( frame >= ci->animations[TORSO_ATTACK].firstFrame 
		&& frame < ci->animations[TORSO_ATTACK].firstFrame + 6 ) {
		return 1 + frame - ci->animations[TORSO_ATTACK].firstFrame;
	}

	// stand attack 2
	if ( frame >= ci->animations[TORSO_ATTACK2].firstFrame 
		&& frame < ci->animations[TORSO_ATTACK2].firstFrame + 6 ) {
		return 1 + frame - ci->animations[TORSO_ATTACK2].firstFrame;
	}
	
	return 0;
}


/*
==============
CG_CalculateWeaponPosition
==============
*/
static void CG_CalculateWeaponPosition( vec3_t origin, vec3_t angles ) {
	float	scale;
	int		delta;
	float	fracsin;

	VectorCopy( cg.refdef.vieworg, origin );
	VectorCopy( cg.refdefViewAngles, angles );

	// on odd legs, invert some angles
	if ( cg.bobcycle & 1 ) {
		scale = -cg.xyspeed;
	} else {
		scale = cg.xyspeed;
	}

	// gun angles from bobbing
	angles[ROLL] += scale * cg.bobfracsin * 0.005;
	angles[YAW] += scale * cg.bobfracsin * 0.01;
	angles[PITCH] += cg.xyspeed * cg.bobfracsin * 0.005;

	// drop the weapon when landing
	delta = cg.time - cg.landTime;
	if ( delta < LAND_DEFLECT_TIME ) {
		origin[2] += cg.landChange*0.25 * delta / LAND_DEFLECT_TIME;
	} else if ( delta < LAND_DEFLECT_TIME + LAND_RETURN_TIME ) {
		origin[2] += cg.landChange*0.25 * 
			(LAND_DEFLECT_TIME + LAND_RETURN_TIME - delta) / LAND_RETURN_TIME;
	}

#if 0
	// drop the weapon when stair climbing
	delta = cg.time - cg.stepTime;
	if ( delta < STEP_TIME/2 ) {
		origin[2] -= cg.stepChange*0.25 * delta / (STEP_TIME/2);
	} else if ( delta < STEP_TIME ) {
		origin[2] -= cg.stepChange*0.25 * (STEP_TIME - delta) / (STEP_TIME/2);
	}
#endif

	// idle drift
	scale = cg.xyspeed + 40;
	fracsin = sin( cg.time * 0.001 );
	angles[ROLL] += scale * fracsin * 0.01;
	angles[YAW] += scale * fracsin * 0.01;
	angles[PITCH] += scale * fracsin * 0.01;
}


/*
===============
CG_LightningBolt

Origin will be the exact tag point, which is slightly
different than the muzzle point used for determining hits.
The cent should be the non-predicted cent if it is from the player,
so the endpoint will reflect the simulated strike (lagging the predicted
angle)
===============
*/
static void CG_LightningBolt( centity_t *cent, vec3_t origin ) {
	trace_t		trace;
	refEntity_t		beam;
	vec3_t			forward;
	vec3_t			muzzlePoint, endPoint;
//Blaze: LG No longer exists
//	if ( cent->currentState.weapon != WP_LIGHTNING ) {
//		return;
//	}

	memset( &beam, 0, sizeof( beam ) );

	// find muzzle point for this frame
	VectorCopy( cent->lerpOrigin, muzzlePoint );
	AngleVectors( cent->lerpAngles, forward, NULL, NULL );

	// FIXME: crouch
	muzzlePoint[2] += DEFAULT_VIEWHEIGHT;

	VectorMA( muzzlePoint, 14, forward, muzzlePoint );

	// project forward by the lightning range
	VectorMA( muzzlePoint, LIGHTNING_RANGE, forward, endPoint );

	// see if it hit a wall
	CG_Trace( &trace, muzzlePoint, vec3_origin, vec3_origin, endPoint, 
		cent->currentState.number, MASK_SHOT );

	// this is the endpoint
	VectorCopy( trace.endpos, beam.oldorigin );

	// use the provided origin, even though it may be slightly
	// different than the muzzle origin
	VectorCopy( origin, beam.origin );

	beam.reType = RT_LIGHTNING;
	beam.customShader = cgs.media.lightningShader;
	trap_R_AddRefEntityToScene( &beam );

	// add the impact flare if it hit something
	if ( trace.fraction < 1.0 ) {
		vec3_t	angles;
		vec3_t	dir;

		VectorSubtract( beam.oldorigin, beam.origin, dir );
		VectorNormalize( dir );

		memset( &beam, 0, sizeof( beam ) );
		beam.hModel = cgs.media.lightningExplosionModel;

		VectorMA( trace.endpos, -16, dir, beam.origin );

		// make a random orientation
		angles[0] = rand() % 360;
		angles[1] = rand() % 360;
		angles[2] = rand() % 360;
		AnglesToAxis( angles, beam.axis );
		trap_R_AddRefEntityToScene( &beam );
	}
}


/*
===============
CG_SpawnRailTrail

Origin will be the exact tag point, which is slightly
different than the muzzle point used for determining hits.
===============
*/
static void CG_SpawnRailTrail( centity_t *cent, vec3_t origin ) {
	clientInfo_t	*ci;

	//Blaze: No more rail gun
	//if ( cent->currentState.weapon != WP_RAILGUN ) {
	//	return;
	//}
	if ( !cent->pe.railgunFlash ) {
		return;
	}
	cent->pe.railgunFlash = qtrue;
	ci = &cgs.clientinfo[ cent->currentState.clientNum ];
	//Blaze: No Rail Trail
	//CG_RailTrail( ci, origin, cent->pe.railgunImpact );
}


/*
======================
CG_MachinegunSpinAngle
======================
*/
#define		SPIN_SPEED	0.9
#define		COAST_TIME	1000
static float	CG_MachinegunSpinAngle( centity_t *cent ) {
	int		delta;
	float	angle;
	float	speed;

	delta = cg.time - cent->pe.barrelTime;
	if ( cent->pe.barrelSpinning ) {
		angle = cent->pe.barrelAngle + delta * SPIN_SPEED;
	} else {
		if ( delta > COAST_TIME ) {
			delta = COAST_TIME;
		}

		speed = 0.5 * ( SPIN_SPEED + (float)( COAST_TIME - delta ) / COAST_TIME );
		angle = cent->pe.barrelAngle + delta * speed;
	}

	if ( cent->pe.barrelSpinning == !(cent->currentState.eFlags & EF_FIRING) ) {
		cent->pe.barrelTime = cg.time;
		cent->pe.barrelAngle = AngleMod( angle );
		cent->pe.barrelSpinning = !!(cent->currentState.eFlags & EF_FIRING);
#ifdef MISSIONPACK
		if ( cent->currentState.weapon == WP_CHAINGUN && !cent->pe.barrelSpinning ) {
			trap_S_StartSound( NULL, cent->currentState.number, CHAN_WEAPON, trap_S_RegisterSound( "sound/weapons/vulcan/wvulwind.wav", qfalse ) );
		}
#endif
	}

	return angle;
}


/*
========================
CG_AddWeaponWithPowerups
========================
*/
static void CG_AddWeaponWithPowerups( refEntity_t *gun, int powerups ) {
	// add powerup effects
	if ( powerups & ( 1 << PW_INVIS ) ) {
		gun->customShader = cgs.media.invisShader;
		trap_R_AddRefEntityToScene( gun );
	} else {
		trap_R_AddRefEntityToScene( gun );

		if ( powerups & ( 1 << PW_BATTLESUIT ) ) {
			gun->customShader = cgs.media.battleWeaponShader;
			trap_R_AddRefEntityToScene( gun );
		}
		if ( powerups & ( 1 << PW_QUAD ) ) {
			gun->customShader = cgs.media.quadWeaponShader;
			trap_R_AddRefEntityToScene( gun );
		}
	}
}


/*
=============
CG_AddPlayerWeapon

Used for both the view weapon (ps is valid) and the world modelother character models (ps is NULL)
The main player will have this called for BOTH cases, so effects like light and
sound should only be done on the world model case.
=============
*/
void CG_AddPlayerWeapon( refEntity_t *parent, playerState_t *ps, centity_t *cent, int team ) {
	refEntity_t	gun;
//Blaze: Can remove this because no more spinning barrel
//	refEntity_t	barrel;
	refEntity_t	flash;
	vec3_t		angles;
	float		frac;
	weapon_t	weaponNum;
	weaponInfo_t	*weapon;
	centity_t	*nonPredictedCent;
//	int	col;

	weaponNum = cent->currentState.weapon;

	CG_RegisterWeapon( weaponNum );
	weapon = &cg_weapons[weaponNum];

	// add the weapon
	memset( &gun, 0, sizeof( gun ) );
	VectorCopy( parent->lightingOrigin, gun.lightingOrigin );
	gun.shadowPlane = parent->shadowPlane;
	gun.renderfx = parent->renderfx;

	// set custom shading for railgun refire rate
	//if ( ps ) {
		//Blaze: No Railgun
		//if ( cg.predictedPlayerState.weapon == WP_RAILGUN 
		//	&& cg.predictedPlayerState.weaponstate == WEAPON_FIRING ) {
		//	float	f;

		//	f = (float)cg.predictedPlayerState.weaponTime / 1500;
		//	gun.shaderRGBA[1] = 0;
		//	gun.shaderRGBA[0] = 
		//	gun.shaderRGBA[2] = 255 * ( 1.0 - f );
		//} else {
			gun.shaderRGBA[0] = 255;
			gun.shaderRGBA[1] = 255;
			gun.shaderRGBA[2] = 255;
			gun.shaderRGBA[3] = 255;
		//}
	//}
	if (ps == NULL)
	{
		//Elder: We are in third person, use the third-person model (DEFAULT)
		gun.hModel = weapon->weaponModel;
		
			/* Elder: use the cached model above
			switch (weaponNum)//Blaze: Used to make the third person weapon models different then 1st person
			{
			case 0:
				//gun.hModel = trap_R_RegisterModel( "models/weapons2/mk23/3rd_mk23.md3" );
				//No Case zero
				break;
			case 1:
				gun.hModel = trap_R_RegisterModel("models/weapons2/knife/3rd_knife.md3");
				break;
			case 2:
				gun.hModel = trap_R_RegisterModel("models/weapons2/mk23/3rd_mk23.md3");
				break;
			case 3:
				gun.hModel = trap_R_RegisterModel("models/weapons2/m4/3rd_m4.md3");
				break;
			case 4:
				gun.hModel = trap_R_RegisterModel("models/weapons2/ssg3000/3rd_ssg3000.md3");
				break;
			case 5:
				gun.hModel = trap_R_RegisterModel("models/weapons2/mp5/3rd_mp5.md3");
				break;
			case 6:
				gun.hModel = trap_R_RegisterModel("models/weapons2/m3/3rd_m3.md3");
				break;
			case 7:
				gun.hModel = trap_R_RegisterModel("models/weapons2/handcannon/3rd_handcannon.md3");
				break;
			case 8:
				gun.hModel = trap_R_RegisterModel("models/weapons2/mk23/3rd_mk23.md3");
				break;
			case 9:
				gun.hModel = trap_R_RegisterModel("models/weapons2/grenade/3rd_grenade.md3");
				break;
			}
			*/
	}
	else {
		//Elder: we are in first-person, use the first-person (NOT default) model
		gun.hModel = weapon->firstModel;
	}
	
	if (!gun.hModel) {
		return;
	}

	if ( !ps ) {
		// add weapon ready sound
		cent->pe.lightningFiring = qfalse;
		if ( ( cent->currentState.eFlags & EF_FIRING ) && weapon->firingSound ) {
			// lightning gun and guantlet make a different sound when fire is held down
			trap_S_AddLoopingSound( cent->currentState.number, cent->lerpOrigin, vec3_origin, weapon->firingSound );
			cent->pe.lightningFiring = qtrue;
		} else if ( weapon->readySound ) {
			trap_S_AddLoopingSound( cent->currentState.number, cent->lerpOrigin, vec3_origin, weapon->readySound );
		}
	}
	if (ps == NULL)
	{
	/*	resizing code
	msec = cg.time - cent->miscTime;
	if ( msec >= 0 && msec < ITEM_SCALEUP_TIME ) {
		frac = (float)msec / ITEM_SCALEUP_TIME;
		VectorScale( ent.axis[0], frac, ent.axis[0] );
		VectorScale( ent.axis[1], frac, ent.axis[1] );
		VectorScale( ent.axis[2], frac, ent.axis[2] );
		ent.nonNormalizedAxes = qtrue;
	} else {
		frac = 1.0;
	}
	*/
		//Elder: shouldn't have to do this anymore
		/*
		if (weaponNum == 4)//Blaze: Scale the Sniper Rifle down a bit
		{
			frac = 0.8f;
			VectorScale(parent->axis[0], frac, parent->axis[0]);
			//VectorScale(parent->axis[1], frac, parent->axis[1]);
			//VectorScale(parent->axis[2], frac, parent->axis[2]);
		}
		*/
		
	}	
	CG_PositionEntityOnTag( &gun, parent, parent->hModel, "tag_weapon");

	CG_AddWeaponWithPowerups( &gun, cent->currentState.powerups );

	// add the spinning barrel
	//Blaze: No Spinning Barrel
	/*
	if ( weapon->barrelModel ) {
		memset( &barrel, 0, sizeof( barrel ) );
		VectorCopy( parent->lightingOrigin, barrel.lightingOrigin );
		barrel.shadowPlane = parent->shadowPlane;
		barrel.renderfx = parent->renderfx;

		barrel.hModel = weapon->barrelModel;
		angles[YAW] = 0;
		angles[PITCH] = 0;
		angles[ROLL] = CG_MachinegunSpinAngle( cent );
		AnglesToAxis( angles, barrel.axis );

		CG_PositionRotatedEntityOnTag( &barrel, &gun, weapon->weaponModel, "tag_barrel" );

		CG_AddWeaponWithPowerups( &barrel, cent->currentState.powerups );
	}*/

	// make sure we aren't looking at cg.predictedPlayerEntity for LG
	nonPredictedCent = &cg_entities[cent->currentState.clientNum];

	// if the index of the nonPredictedCent is not the same as the clientNum
	// then this is a fake player (like on teh single player podiums), so
	// go ahead and use the cent
	if( ( nonPredictedCent - cg_entities ) != cent->currentState.clientNum ) {
		nonPredictedCent = cent;
	}

	// add the flash
	//Blaze: no more of these
	/*
	if ( ( weaponNum == WP_LIGHTNING || weaponNum == WP_GAUNTLET || weaponNum == WP_GRAPPLING_HOOK )
		&& ( nonPredictedCent->currentState.eFlags & EF_FIRING ) ) 
	{
		// continuous flash
	} else {
		// impulse flash
		if ( cg.time - cent->muzzleFlashTime > MUZZLE_FLASH_TIME && !cent->pe.railgunFlash ) {
			return;
		}
	}
	*/

	//Elder: re-added to fix loss of muzzle flashes!
	// impulse flash
	if ( cg.time - cent->muzzleFlashTime > MUZZLE_FLASH_TIME && !cent->pe.railgunFlash ) {
		return;
	}

	memset( &flash, 0, sizeof( flash ) );
	
	VectorCopy( parent->lightingOrigin, flash.lightingOrigin );
	flash.shadowPlane = parent->shadowPlane;
	flash.renderfx = parent->renderfx;
	
	flash.hModel = weapon->flashModel;
	if (!flash.hModel) {
		return;
	}
	
	angles[YAW] = 0;
	angles[PITCH] = 0;
	angles[ROLL] = crandom() * 10;
	AnglesToAxis( angles, flash.axis );

	// colorize the railgun blast
	//Blaze: No more railgun
	/*
	if ( weaponNum == WP_RAILGUN ) {
		clientInfo_t	*ci;

		ci = &cgs.clientinfo[ cent->currentState.clientNum ];
		flash.shaderRGBA[0] = 255 * ci->color[0];
		flash.shaderRGBA[1] = 255 * ci->color[1];
		flash.shaderRGBA[2] = 255 * ci->color[2];
	}
	*/
	//Blaze: No flash
	//Elder: Yes flash - try this
	
	//Elder: add conditional here so the dlight is still drawn when cg_RQ3_flash is 0
	if ( cg_RQ3_flash.integer ) {
		if (ps) {
			//Elder: draw flash based on first-person view
			CG_PositionRotatedEntityOnTag( &flash, &gun, weapon->firstModel, "tag_flash");
		}
		else {
			//Elder: draw flash based on 3rd-person view
			CG_PositionRotatedEntityOnTag( &flash, &gun, weapon->weaponModel, "tag_flash");
		}
		
		trap_R_AddRefEntityToScene( &flash );
	}
	else {
		//Elder: crappy way to get the dlight working w/o the flash model
		if ( ps || cg.renderingThirdPerson ||
			cent->currentState.number != cg.predictedPlayerState.clientNum ) {
			if ( weapon->flashDlightColor[0] || weapon->flashDlightColor[1] || weapon->flashDlightColor[2] ) {
				trap_R_AddLightToScene( gun.origin, 300 + (rand()&31), weapon->flashDlightColor[0],
					weapon->flashDlightColor[1], weapon->flashDlightColor[2] );
			}
		}
		return;
	}
	
	if ( ps || cg.renderingThirdPerson ||
		cent->currentState.number != cg.predictedPlayerState.clientNum ) {
		// add lightning bolt
		//Blaze: No need for this
		//CG_LightningBolt( nonPredictedCent, flash.origin );

		// add rail trail
		//Blaze: no need for this
		//CG_SpawnRailTrail( cent, flash.origin );
/*
		if ( team == TEAM_RED ) {
			col = 1;
		}
		else if ( team == TEAM_BLUE ) {
			col = 2;
		}
		else {
			col = 0;
		}

		// make a dlight for the flash
		if ( weapon->flashDlightColor[col][0] || weapon->flashDlightColor[col][1] || weapon->flashDlightColor[col][2] ) {
			trap_R_AddLightToScene( flash.origin, 300 + (rand()&31), weapon->flashDlightColor[col][0],
				weapon->flashDlightColor[col][1], weapon->flashDlightColor[col][2] );
		}
*/
		if ( weapon->flashDlightColor[0] || weapon->flashDlightColor[1] || weapon->flashDlightColor[2] ) {
			trap_R_AddLightToScene( flash.origin, 300 + (rand()&31), weapon->flashDlightColor[0],
				weapon->flashDlightColor[1], weapon->flashDlightColor[2] );
		}
	}
}

/*
==============
CG_AddViewWeapon

Add the weapon, and flash for the player's view
==============
*/
void CG_AddViewWeapon( playerState_t *ps ) {
	refEntity_t	hand;
	centity_t	*cent;
	clientInfo_t	*ci;
	float		fovOffset;
	vec3_t		angles;
	weaponInfo_t	*weapon;
	//Blaze: Reaction vars for gun positions
	float rxn_gunx, rxn_guny, rxn_gunz;



	if ( ps->persistant[PERS_TEAM] == TEAM_SPECTATOR ) {
		return;
	}

	if ( ps->pm_type == PM_INTERMISSION ) {
		return;
	}

	// no gun if in third person view
	if ( cg.renderingThirdPerson ) {
		return;
	}

	// allow the gun to be completely removed
	if ( !cg_drawGun.integer ) {
//Blaze: Removed these
//		vec3_t		origin;

//		if ( cg.predictedPlayerState.eFlags & EF_FIRING ) {
			// special hack for lightning gun...
//			VectorCopy( cg.refdef.vieworg, origin );
//			VectorMA( origin, -8, cg.refdef.viewaxis[2], origin );
//			CG_LightningBolt( &cg_entities[ps->clientNum], origin );
//		}
		return;
	}

// Hawkins- don't draw gun if zoomed
	if(cg.zoomed)
		return;


	// don't draw if testing a gun model
	if ( cg.testGun ) {
		return;
	}	
//Blaze start: Reaction gun positioning
	rxn_gunx = cg_gun_x.value; 
	rxn_guny = cg_gun_y.value;
	rxn_gunz = cg_gun_z.value;
	//Blaze: Gun xyz coords changes
	switch(ps->weapon)
	{
	case WP_PISTOL:
		rxn_gunx -= 4;
		break;
	case WP_M4:
		rxn_gunx += 10;
		break;
	case WP_SSG3000:
		rxn_gunx += 10;
		break;
	case WP_AKIMBO:
		rxn_gunx += 10;
	}

	if ((cg_RQ3_drawWeapon.integer > 1 ) && (cg_RQ3_drawWeapon.integer < 4 ))
	{
		rxn_guny = cg_gun_y.value + 4*(cg_RQ3_drawWeapon.integer-1);
	}
	//Blaze end:

	// drop gun lower at higher fov
	if ( cg_fov.integer > 90 ) {
		fovOffset = -0.2 * ( cg_fov.integer - 90 );
	} else {
		fovOffset = 0;
	}

	cent = &cg.predictedPlayerEntity;	// &cg_entities[cg.snap->ps.clientNum];
	CG_RegisterWeapon( ps->weapon );
	weapon = &cg_weapons[ ps->weapon ];

	memset (&hand, 0, sizeof(hand));

	// set up gun position
	CG_CalculateWeaponPosition( hand.origin, angles );
//Blaze start: reaction gun positioning
//	VectorMA( hand.origin, rxn_gunx, cg.refdef.viewaxis[0], hand.origin );
//	VectorMA( hand.origin, rxn_guny, cg.refdef.viewaxis[1], hand.origin );
//	VectorMA( hand.origin, (rxn_gunz + fovOffset), cg.refdef.viewaxis[2], hand.origin );
//Blaze end:

//Blaze: Use above code instead
//Elder: reused so Cloud can adjust the models manually
	VectorMA( hand.origin, cg_gun_x.value, cg.refdef.viewaxis[0], hand.origin );
	VectorMA( hand.origin, cg_gun_y.value, cg.refdef.viewaxis[1], hand.origin );
	VectorMA( hand.origin, (cg_gun_z.value+fovOffset), cg.refdef.viewaxis[2], hand.origin );

	AnglesToAxis( angles, hand.axis );

	// map torso animations to weapon animations
	if ( cg_gun_frame.integer ) {
		// development tool
		hand.frame = hand.oldframe = cg_gun_frame.integer;
		hand.backlerp = 0;
	} else {
		// get clientinfo for animation map
		ci = &cgs.clientinfo[ cent->currentState.clientNum ];
		hand.frame = CG_MapTorsoToWeaponFrame( ci, cent->pe.torso.frame );
		hand.oldframe = CG_MapTorsoToWeaponFrame( ci, cent->pe.torso.oldFrame );
		hand.backlerp = cent->pe.torso.backlerp;
	}

	hand.hModel = weapon->handsModel;
	hand.renderfx = RF_DEPTHHACK | RF_FIRST_PERSON | RF_MINLIGHT;

	// add everything onto the hand
	CG_AddPlayerWeapon( &hand, ps, &cg.predictedPlayerEntity, ps->persistant[PERS_TEAM] );
}

/*
==============================================================================

WEAPON SELECTION

==============================================================================
*/

/*
===================
CG_DrawWeaponSelect
===================
*/
void CG_DrawWeaponSelect( void ) {
	int		i;
	int		bits;
	int		count;
	int		x, y, w;
	char	*name;
	float	*color;

	// don't display if dead
	if ( cg.predictedPlayerState.stats[STAT_HEALTH] <= 0 ) {
		return;
	}

	color = CG_FadeColor( cg.weaponSelectTime, WEAPON_SELECT_TIME );
	if ( !color ) {
		return;
	}
	trap_R_SetColor( color );

	// showing weapon select clears pickup item display, but not the blend blob
	cg.itemPickupTime = 0;

	// count the number of weapons owned
	bits = cg.snap->ps.stats[ STAT_WEAPONS ];
	count = 0;
	for ( i = 1 ; i < 16 ; i++ ) {
		if ( bits & ( 1 << i ) ) {
			count++;
		}
	}

	x = 320 - count * 20;
	y = 380;

	for ( i = 1 ; i < 16 ; i++ ) {
		if ( !( bits & ( 1 << i ) ) ) {
			continue;
		}

		CG_RegisterWeapon( i );

		// draw weapon icon
		CG_DrawPic( x, y, 32, 32, cg_weapons[i].weaponIcon );

		// draw selection marker
		if ( i == cg.weaponSelect ) {
			CG_DrawPic( x-4, y-4, 40, 40, cgs.media.selectShader );
		}

		// no ammo cross on top
		if ( !cg.snap->ps.ammo[ i ] ) {
			CG_DrawPic( x, y, 32, 32, cgs.media.noammoShader );
		}

		x += 40;
	}

	// draw the selected name
	if ( cg_weapons[ cg.weaponSelect ].item ) {
		name = cg_weapons[ cg.weaponSelect ].item->pickup_name;
		if ( name ) {
			w = CG_DrawStrlen( name ) * BIGCHAR_WIDTH;
			x = ( SCREEN_WIDTH - w ) / 2;
			CG_DrawBigStringColor(x, y - 22, name, color);
		}
	}

	trap_R_SetColor( NULL );
}


/*
===============
CG_WeaponSelectable
===============
*/
static qboolean CG_WeaponSelectable( int i ) {
	//Elder: never switch to empty grenades/knives
	if ( !cg.snap->ps.ammo[i] && (i == WP_GRENADE || i == WP_KNIFE) ) {
		return qfalse;
	}
	//Blaze: Check the amount of clips too for the weapon rotate code
	//Elder: this won't work plus AQ2 lets you select empty weapons
	//if ( !cg.snap->ps.ammo[i] && !cg.snap->ps.stats[STAT_CLIPS] ) {
		//return qfalse;
	//}
	if ( ! (cg.snap->ps.stats[ STAT_WEAPONS ] & ( 1 << i ) ) ) {
		return qfalse;
	}

	return qtrue;
}

/*
===============
CG_NextWeapon_f
===============
*/
void CG_NextWeapon_f( void ) {
	int		i;
	int		original;

	if ( !cg.snap ) {
		return;
	}
	if ( cg.snap->ps.pm_flags & PMF_FOLLOW ) {
		return;
	}

	// if we are going into the intermission, don't do anything
	if ( cg.intermissionStarted ) {
		return;
	}

	//Elder: added
	if ( (cg.snap->ps.stats[STAT_RQ3] & RQ3_BANDAGE_WORK) == RQ3_BANDAGE_WORK) {
		CG_Printf("You are too busy bandaging...\n");
		return;
	}

	//Elder: don't allow weapon switching when in the middle of bursts
	if (cg.snap->ps.stats[STAT_BURST] > 0)
		return;

	//Elder: in the middle of firing, reloading or weapon-switching
	//cg.snap->ps.weaponstate == WEAPON_RELOADING when it's in
	if (cg.snap->ps.weaponstate == WEAPON_DROPPING && cg.snap->ps.weaponTime > 0) {
	//if (cg.snap->ps.weaponTime > 0) {
		return;
	}

	//Elder: added
	//cg.zoomed = qfalse;
	//cg.zoomLevel = 0;

	cg.weaponSelectTime = cg.time;
	original = cg.weaponSelect;

	for ( i = 0 ; i < 16 ; i++ ) {
		cg.weaponSelect++;
		if ( cg.weaponSelect == 16 ) {
			cg.weaponSelect = 0;
		}
		//Blaze: Allow full Cycle
		//if ( cg.weaponSelect == WP_GAUNTLET ) {
		//	continue;		// never cycle to gauntlet
		//}
		if ( CG_WeaponSelectable( cg.weaponSelect ) ) {
			break;
		}
	}
	if ( i == 16 ) {
		cg.weaponSelect = original;
	}
	else {
		CG_RQ3_Zoom1x();
		trap_SendClientCommand("unzoom");
	}
}

/*
===============
CG_PrevWeapon_f
===============
*/
void CG_PrevWeapon_f( void ) {
	int		i;
	int		original;

	if ( !cg.snap ) {
		return;
	}
	if ( cg.snap->ps.pm_flags & PMF_FOLLOW ) {
		return;
	}

// if we are going into the intermission, don't do anything
	if ( cg.intermissionStarted ) {
		return;
	}

	//Elder: added
	if ( (cg.snap->ps.stats[STAT_RQ3] & RQ3_BANDAGE_WORK) == RQ3_BANDAGE_WORK) {
		CG_Printf("You are too busy bandaging...\n");
		return;
	}

	//Elder: don't allow weapon switching when in the middle of bursts
	if (cg.snap->ps.stats[STAT_BURST] > 0)
		return;

	//Elder: in the middle of firing, reloading or weapon-switching
	//cg.snap->ps.weaponstate == WEAPON_RELOADING when it's in
	if (cg.snap->ps.weaponstate == WEAPON_DROPPING && cg.snap->ps.weaponTime > 0) {
		return;
	}

	//Elder: added
	//cg.zoomed = qfalse;
	//cg.zoomLevel = 0;

	cg.weaponSelectTime = cg.time;
	original = cg.weaponSelect;

	for ( i = 0 ; i < 16 ; i++ ) {
		cg.weaponSelect--;
		if ( cg.weaponSelect == -1 ) {
			cg.weaponSelect = 15;
		}
		//Blaze: Allow full Cycle
		//if ( cg.weaponSelect == WP_GAUNTLET ) {
		//	continue;		// never cycle to gauntlet
		//}
		if ( CG_WeaponSelectable( cg.weaponSelect ) ) {
			break;
		}
	}
	if ( i == 16 ) {
		cg.weaponSelect = original;
	}
	else {
		CG_RQ3_Zoom1x();
		trap_SendClientCommand("unzoom");
	}
}


/*
===============
Added by Elder
  
CG_SpecialWeapon_f
===============
*/
void CG_SpecialWeapon_f( void ) {
	int		i;
	int		original;

	if ( !cg.snap ) {
		//CG_Printf("No snapshot: normally exiting\n");
		return;
	}

	if ( cg.snap->ps.pm_flags & PMF_FOLLOW ) {
		return;
	}

	// if we are going into the intermission, don't do anything
	if ( cg.intermissionStarted ) {
		return;
	}

	//Elder: added
	if ( (cg.snap->ps.stats[STAT_RQ3] & RQ3_BANDAGE_WORK) == RQ3_BANDAGE_WORK) {
		CG_Printf("You are too busy bandaging...\n");
		return;
	}
	
	//Elder: don't allow weapon switching when in the middle of bursts
	if (cg.snap->ps.stats[STAT_BURST] > 0)
		return;

	//Elder: in the middle of firing, reloading or weapon-switching
	//cg.snap->ps.weaponstate == WEAPON_RELOADING when it's in
	if (cg.snap->ps.weaponstate == WEAPON_DROPPING && cg.snap->ps.weaponTime > 0) {
		return;
	}

	cg.weaponSelectTime = cg.time;
	original = cg.weaponSelect;

	for ( i = 0 ; i < 16 ; i++ ) {
		cg.weaponSelect++;
		if ( cg.weaponSelect == 16 ) {
			cg.weaponSelect = 0;
		}

		//Skip normal weapons
		switch (cg.weaponSelect) {
		case WP_PISTOL:
		case WP_AKIMBO:
		case WP_KNIFE:
		case WP_GRENADE:
			continue;
		}

		if ( CG_WeaponSelectable( cg.weaponSelect ) ) {
			break;
		}
	}
	if ( i == 16 ) {
		cg.weaponSelect = original;
	}
	else {
		CG_RQ3_Zoom1x();
		trap_SendClientCommand("unzoom");
	}
}


//Elder: for returning to the zoom state in ps stats
void CG_RQ3_SyncZoom ( void ) {
	if ( (cg.snap->ps.stats[STAT_RQ3] & RQ3_ZOOM_LOW) == RQ3_ZOOM_LOW &&
		(cg.snap->ps.stats[STAT_RQ3] & RQ3_ZOOM_MED) == RQ3_ZOOM_MED ) {
		//CG_Printf("Zoomed to 6x\n");
		cg.zoomLevel = RQ3_ZOOM_LOW|RQ3_ZOOM_MED;
	}
	else if ( (cg.snap->ps.stats[STAT_RQ3] & RQ3_ZOOM_LOW) == RQ3_ZOOM_LOW) {
		//CG_Printf("Zoomed to 2x\n");
		cg.zoomLevel = RQ3_ZOOM_LOW;
	}
	else if ( (cg.snap->ps.stats[STAT_RQ3] & RQ3_ZOOM_MED) == RQ3_ZOOM_MED) {
		//CG_Printf("Zoomed to 4x\n");
		cg.zoomLevel = RQ3_ZOOM_MED;
	}
	else {
		//CG_Printf("Zoomed out\n");
		cg.zoomLevel = 0;
	}
}

//Elder: save zoom level and do any other necessary housekeeping
void CG_RQ3_SaveZoomLevel() {
	cg.lastZoomLevel = cg.zoomLevel;
}


/*
void CG_RQ3_SyncZoom2 ( void ) {
	int statZoom;

	if ( (cg.snap->ps.stats[STAT_RQ3] & RQ3_ZOOM_LOW) == RQ3_ZOOM_LOW &&
		(cg.snap->ps.stats[STAT_RQ3] & RQ3_ZOOM_MED) == RQ3_ZOOM_MED ) {
		statZoom = RQ3_ZOOM_LOW|RQ3_ZOOM_MED;
	}
	else if ( (cg.snap->ps.stats[STAT_RQ3] & RQ3_ZOOM_LOW) == RQ3_ZOOM_LOW) {
		statZoom = RQ3_ZOOM_LOW;
	}
	else if ( (cg.snap->ps.stats[STAT_RQ3] & RQ3_ZOOM_MED) == RQ3_ZOOM_MED) {
		statZoom = RQ3_ZOOM_MED;
	}
	else {
		statZoom = 0;
	}

	if (statZoom != cg.zoomLevel)
		cg.zoomLevel = statZoom;
}*/

//Elder: This should identical to the portion inside
//the weapon function in g_cmds.c
void CG_RQ3_Zoom( void ) {
	//Elder: reworked SSG zoom
	if (cg.snap->ps.weapon == WP_SSG3000)
	{
		CG_RQ3_SaveZoomLevel();

		if ( (cg.zoomLevel & RQ3_ZOOM_LOW) == RQ3_ZOOM_LOW &&
			 (cg.zoomLevel & RQ3_ZOOM_MED) == RQ3_ZOOM_MED ) {
			//Elder: zoom 1x
			cg.zoomLevel &= ~RQ3_ZOOM_LOW;
			cg.zoomLevel &= ~RQ3_ZOOM_MED;
		}
		else if ( (cg.zoomLevel & RQ3_ZOOM_MED) == RQ3_ZOOM_MED) {
			//Elder: zoom 6x
			cg.zoomLevel |= RQ3_ZOOM_LOW;
		}	
		else if ( (cg.zoomLevel & RQ3_ZOOM_LOW) == RQ3_ZOOM_LOW) {
			//Elder: zoom 4x
			cg.zoomLevel |= RQ3_ZOOM_MED;
			cg.zoomLevel &= ~RQ3_ZOOM_LOW;
		}
		else {
			//Elder: zoom 2x
			cg.zoomLevel |= RQ3_ZOOM_LOW;
		}
		
		cg.zoomTime = cg.time;
	}

	/*
	if(cg.snap->ps.weapon==WP_SSG3000) {
		cg.zoomLevel++;
		if (cg.zoomLevel == 4) {
			cg.zoomed = qfalse;
			cg.zoomLevel = 0;
			CG_Printf("Zoomed out\n");
		}
		else {
			cg.zoomed = qtrue;
			CG_Printf("Zoomed to %dx\n", cg.zoomLevel * 2);	
		}
		cg.zoomTime = cg.time;
	}
	*/
}

//Elder: reset locally and send server message
void CG_RQ3_Zoom1x () {
	if (cg_RQ3_ssgZoomAssist.integer)
	{
		cg.lastZoomLevel = cg.zoomLevel;
		cg.zoomLevel = 0;
		cg.zoomTime = cg.time;
	}
	//trap_SendClientCommand("unzoom");
}

int CG_RQ3_GetGrenadeMode()
{
	int grenMode = 0;

	if ( (cg.snap->ps.persistant[PERS_WEAPONMODES] & RQ3_GRENSHORT) == RQ3_GRENSHORT)
		grenMode |= RQ3_GRENSHORT;
	
	if ( (cg.snap->ps.persistant[PERS_WEAPONMODES] & RQ3_GRENMED) == RQ3_GRENMED)
		grenMode |= RQ3_GRENMED;

	return grenMode;
}

//Print grenade mode message
void CG_RQ3_GrenadeMode()
{
	//Print a message for the next mode in line
	if ( (cg.snap->ps.persistant[PERS_WEAPONMODES] & RQ3_GRENSHORT) == RQ3_GRENSHORT &&
		(cg.snap->ps.persistant[PERS_WEAPONMODES] & RQ3_GRENMED) == RQ3_GRENMED ) {
		CG_Printf("Prepared to make a short range throw\n");
		//cg.grenadeMode = RQ3_GRENSHORT|RQ3_GRENMED;
	}
	else if ( (cg.snap->ps.persistant[PERS_WEAPONMODES] & RQ3_GRENSHORT) == RQ3_GRENSHORT) {
		CG_Printf("Prepared to make a medium range throw\n");
		//cg.grenadeMode = RQ3_GRENSHORT;
	}
	else if ( (cg.snap->ps.persistant[PERS_WEAPONMODES] & RQ3_GRENMED) == RQ3_GRENMED) {
		CG_Printf("Prepared to make a long range throw\n");
		//cg.grenadeMode = RQ3_GRENMED;
	}
}

/*
===============
CG_Weapon_f

Elder: does local stuff, then proceeds to server
Used with Q3's internal weapon switching "e.g. weapon 10"
===============
*/
void CG_Weapon_f( void ) {
	int num;
	
	if ( !cg.snap ) {
		//CG_Printf("No snapshot: normally exiting\n");
		return;
	}

	// if we are going into the intermission, don't do anything
	if ( cg.intermissionStarted ) {
		return;
	}

	//Elder: added to prevent weapon switching while bandaging
	if ( (cg.snap->ps.stats[STAT_RQ3] & RQ3_BANDAGE_WORK) == RQ3_BANDAGE_WORK) {
		CG_Printf("You are too busy bandaging...\n");
		return;
	}
	
	//Elder: don't allow weapon switching when in the middle of bursts
	if (cg.snap->ps.stats[STAT_BURST] > 0)
		return;

	//Elder: in the middle of firing, reloading or weapon-switching
	if (cg.snap->ps.weaponTime > 0) {
		return;
	}


	///Elder: spectator?
	if ( cg.snap->ps.pm_flags & PMF_FOLLOW ) {
		return;
	}

	// Hawkins (give 'weapon' dual meaning)
	if ( trap_Argc() == 1 ) {
		if (cg.snap->ps.weapon == WP_SSG3000) {
			//trap_S_StartSound( NULL, cg.snap->ps.clientNum, CHAN_ITEM, cgs.media.lensSound);
			trap_S_StartLocalSound( cgs.media.lensSound, CHAN_ITEM);
			if (cg_RQ3_ssgZoomAssist.integer)
				CG_RQ3_Zoom();
		}
		else if (cg.snap->ps.weapon == WP_GRENADE)
		{
			CG_RQ3_GrenadeMode();
		}
		else
		{
			//do weapon select sound
		}
		trap_SendClientCommand("weapon");
		//Elder: added to get out of function at this point
		return;
	}

	num = atoi( CG_Argv( 1 ) );

	if ( num < 1 || num > 15 ) {
		return;
	}

	//Elder: this point on is the regular Q3 weapon function - weird
	
	cg.weaponSelectTime = cg.time;

	if ( ! ( cg.snap->ps.stats[STAT_WEAPONS] & ( 1 << num ) ) ) {
		return;		// don't have the weapon
	}

	//Elder: If re-selecting SSG - leave function
	if ( (1 << num) == (1 << WP_SSG3000) && cg.snap->ps.weapon == WP_SSG3000) {
		//CG_Printf("Selecting SSG\n");
		return;
	}
	
	//cg.zoomed = qfalse;
	//cg.zoomLevel = 0;
	
	CG_RQ3_Zoom1x();
	trap_SendClientCommand("unzoom");
	cg.weaponSelect = num;
}


/*
===================
CG_OutOfAmmoChange

The current weapon has just run out of ammo
===================
*/
void CG_OutOfAmmoChange( void ) {
	int		i;


	if (!cg.snap)
		return;

	//Select the pistol when we run out of grenades or knives
	if (cg.snap->ps.weapon == WP_KNIFE || cg.snap->ps.weapon == WP_GRENADE) {
		cg.weaponSelectTime = cg.time;
		cg.weaponSelect = WP_PISTOL;
	}

	/* Elder: disable auto-switch
	cg.weaponSelectTime = cg.time;

	//Elder: we'll have to change this to
	//a) show the empty gun animation if gun's ammo = 0
	//b) NOT auto-switch to another weapon
	
	for ( i = 15 ; i > 0 ; i-- ) {
		if ( CG_WeaponSelectable( i ) ) {
			cg.weaponSelect = i;
			break;
		}
	}
	*/
}



/*
===================================================================================================

WEAPON EVENTS

===================================================================================================
*/

/*
================
CG_FireWeapon

Caused by an EV_FIRE_WEAPON event
================
*/
void CG_FireWeapon( centity_t *cent ) {
	entityState_t *ent;
	int				c;
	weaponInfo_t	*weap;

	ent = &cent->currentState;
	if ( ent->weapon == WP_NONE ) {
		return;
	}
	if ( ent->weapon >= WP_NUM_WEAPONS ) {
		CG_Error( "CG_FireWeapon: ent->weapon >= WP_NUM_WEAPONS" );
		return;
	}
	
	weap = &cg_weapons[ ent->weapon ];

	//Elder: added to supress burst mode flashes + sounds when 'predicting'
	// M4
	if ( cg.snap->ps.weapon == WP_M4 && 
		 (cg.snap->ps.persistant[PERS_WEAPONMODES] & RQ3_M4MODE) == RQ3_M4MODE &&
		 cg.snap->ps.stats[STAT_BURST] > 2 )
	{
		return;
	}
	// MP5
	if ( cg.snap->ps.weapon == WP_MP5 &&
		(cg.snap->ps.persistant[PERS_WEAPONMODES] & RQ3_MP5MODE) == RQ3_MP5MODE &&
		cg.snap->ps.stats[STAT_BURST] > 2 ) {
		return;
	}
	// MK23
	if ( cg.snap->ps.weapon == WP_PISTOL &&
		(cg.snap->ps.persistant[PERS_WEAPONMODES] & RQ3_MK23MODE) == RQ3_MK23MODE &&
		cg.snap->ps.stats[STAT_BURST] > 0 ) {
		return;
	}

	// mark the entity as muzzle flashing, so when it is added it will
	// append the flash to the weapon model
	cent->muzzleFlashTime = cg.time;
	
	// lightning gun only does this this on initial press
	//Blaze: no more Lighting gun
	/*
	if ( ent->weapon == WP_LIGHTNING ) {
		if ( cent->pe.lightningFiring ) {
			return;
		}
	}
	*/

	// play quad sound if needed
	if ( cent->currentState.powerups & ( 1 << PW_QUAD ) ) {
		trap_S_StartSound (NULL, cent->currentState.number, CHAN_ITEM, cgs.media.quadSound );
	}

	if ent->client->ps.
		// play a sound
		for ( c = 0 ; c < 4 ; c++ ) {
			if ( !weap->flashSound[c] ) {
				break;
			}
		}

		if ( c > 0 ) {
			c = rand() % c;
			if ( weap->flashSound[c] )
			{
				trap_S_StartSound( NULL, ent->number, CHAN_WEAPON, weap->flashSound[c] );
			}
		}

	// do brass ejection
	if ( weap->ejectBrassFunc && cg_brassTime.integer > 0 ) {
		weap->ejectBrassFunc( cent );
	}
}


/*
=================
CG_MissileHitWall

Caused by an EV_MISSILE_MISS event, or directly by local bullet tracing
=================
*/
void CG_MissileHitWall( int weapon, int clientNum, vec3_t origin, vec3_t dir, impactSound_t soundType ) {
	qhandle_t		mod;
	qhandle_t		mark;
	qhandle_t		shader;
	sfxHandle_t		sfx;
	float			radius;
	float			light;
	vec3_t			lightColor;
	localEntity_t	*le;
	int				r;
	qboolean		alphaFade;
	qboolean		isSprite;
	int				duration;
	
	//Elder: for impact smoke marks
	localEntity_t	*smokePuff;
	vec3_t			puffOrigin;
	vec3_t			puffOffset;
	vec3_t			puffDir;
	
	int				i;

	mark = 0;
	radius = 32;
	sfx = 0;
	mod = 0;
	shader = 0;
	light = 0;
	lightColor[0] = 1;
	lightColor[1] = 1;
	lightColor[2] = 0;

	// set defaults
	isSprite = qfalse;
	duration = 600;

	switch ( weapon ) {
	
/*
#ifdef MISSIONPACK
	case WP_NAILGUN:
		if( soundType == IMPACTSOUND_FLESH ) {
			sfx = cgs.media.sfx_nghitflesh;
		} else if( soundType == IMPACTSOUND_METAL ) {
			sfx = cgs.media.sfx_nghitmetal;
		} else {
			sfx = cgs.media.sfx_nghit;
		}
		mark = cgs.media.holeMarkShader;
		radius = 12;
		break;
#endif
	case WP_LIGHTNING:
		// no explosion at LG impact, it is added with the beam
		r = rand() & 3;
		if ( r < 2 ) {
			sfx = cgs.media.sfx_lghit2;
		} else if ( r == 2 ) {
			sfx = cgs.media.sfx_lghit1;
		} else {
			sfx = cgs.media.sfx_lghit3;
		}
		mark = cgs.media.holeMarkShader;
		radius = 12;
		break;
#ifdef MISSIONPACK
	case WP_PROX_LAUNCHER:
		mod = cgs.media.dishFlashModel;
		shader = cgs.media.grenadeExplosionShader;
		sfx = cgs.media.sfx_proxexp;
		mark = cgs.media.burnMarkShader;
		radius = 64;
		light = 300;
		isSprite = qtrue;
		break;
#endif
	case WP_GRENADE_LAUNCHER:
		mod = cgs.media.dishFlashModel;
		shader = cgs.media.grenadeExplosionShader;
		sfx = cgs.media.sfx_rockexp;
		mark = cgs.media.burnMarkShader;
		radius = 64;
		light = 300;
		isSprite = qtrue;
		break;
	case WP_ROCKET_LAUNCHER:
		mod = cgs.media.dishFlashModel;
		shader = cgs.media.rocketExplosionShader;
		sfx = cgs.media.sfx_rockexp;
		mark = cgs.media.burnMarkShader;
		radius = 64;
		light = 300;
		isSprite = qtrue;
		duration = 1000;
		lightColor[0] = 1;
		lightColor[1] = 0.75;
		lightColor[2] = 0.0;
//		CG_BigExplode( origin );
		break;
	case WP_RAILGUN:
		mod = cgs.media.ringFlashModel;
		shader = cgs.media.railExplosionShader;
		sfx = cgs.media.sfx_plasmaexp;
		mark = cgs.media.energyMarkShader;
		radius = 24;
		break;
	case WP_PLASMAGUN:
		mod = cgs.media.ringFlashModel;
		shader = cgs.media.plasmaExplosionShader;
		sfx = cgs.media.sfx_plasmaexp;
		mark = cgs.media.energyMarkShader;
		radius = 16;
		break;
	case WP_BFG:
		mod = cgs.media.dishFlashModel;
		shader = cgs.media.bfgExplosionShader;
		sfx = cgs.media.sfx_rockexp;
		mark = cgs.media.burnMarkShader;
		radius = 32;
		isSprite = qtrue;
		break;
	case WP_SHOTGUN:
		mod = cgs.media.bulletFlashModel;
		shader = cgs.media.bulletExplosionShader;
		mark = cgs.media.bulletMarkShader;
		sfx = 0;
		radius = 4;
		break;

#ifdef MISSIONPACK
	case WP_CHAINGUN:
		mod = cgs.media.bulletFlashModel;
		if( soundType == IMPACTSOUND_FLESH ) {
			sfx = cgs.media.sfx_chghitflesh;
		} else if( soundType == IMPACTSOUND_METAL ) {
			sfx = cgs.media.sfx_chghitmetal;
		} else {
			sfx = cgs.media.sfx_chghit;
		}
		mark = cgs.media.bulletMarkShader;

		r = rand() & 3;
		if ( r < 2 ) {
			sfx = cgs.media.sfx_ric1;
		} else if ( r == 2 ) {
			sfx = cgs.media.sfx_ric2;
		} else {
			sfx = cgs.media.sfx_ric3;
		}

		radius = 8;
		break;
#endif

	case WP_MACHINEGUN:
		mod = cgs.media.bulletFlashModel;
		shader = cgs.media.bulletExplosionShader;
		mark = cgs.media.bulletMarkShader;

		r = rand() & 3;
		if ( r < 2 ) {
			sfx = cgs.media.sfx_ric1;
		} else if ( r == 2 ) {
			sfx = cgs.media.sfx_ric2;
		} else {
			sfx = cgs.media.sfx_ric3;
		}

		radius = 8;
		break;
	}
*///Blaze: Reaction M4
	case WP_M4:
		mod = cgs.media.bulletFlashModel;
		shader = cgs.media.bulletExplosionShader;
		mark = cgs.media.bulletMarkShader;

		r = rand() & 3;
		if ( r < 2 ) {
			sfx = cgs.media.sfx_ric1;
		} else if ( r == 2 ) {
			sfx = cgs.media.sfx_ric2;
		} else {
			sfx = cgs.media.sfx_ric3;
		}

		radius = 8;
		break;
//Blaze: Reaction Pistol
	case WP_PISTOL:
		mod = cgs.media.bulletFlashModel;
		shader = cgs.media.bulletExplosionShader;
		mark = cgs.media.bulletMarkShader;

		r = rand() & 3;
		if ( r < 2 ) {
			sfx = cgs.media.sfx_ric1;
		} else if ( r == 2 ) {
			sfx = cgs.media.sfx_ric2;
		} else {
			sfx = cgs.media.sfx_ric3;
		}

		radius = 8;
		break;
//Blaze: Reaction MP5
	case WP_MP5:
		mod = cgs.media.bulletFlashModel;
		shader = cgs.media.bulletExplosionShader;
		mark = cgs.media.bulletMarkShader;

		r = rand() & 3;
		if ( r < 2 ) {
			sfx = cgs.media.sfx_ric1;
		} else if ( r == 2 ) {
			sfx = cgs.media.sfx_ric2;
		} else {
			sfx = cgs.media.sfx_ric3;
		}

		radius = 8;
		break;
//Blaze: Reaction Shotgun
	case WP_M3:
		mod = cgs.media.bulletFlashModel;
		shader = cgs.media.bulletExplosionShader;
		mark = cgs.media.bulletMarkShader;
		sfx = 0;
		radius = 4;
		break;
	case WP_HANDCANNON:
		mod = cgs.media.bulletFlashModel;
		shader = cgs.media.bulletExplosionShader;
		mark = cgs.media.bulletMarkShader;
		sfx = 0;
		radius = 4;
		break;
	case WP_AKIMBO:
		mod = cgs.media.bulletFlashModel;
		shader = cgs.media.bulletExplosionShader;
		mark = cgs.media.bulletMarkShader;
		sfx = 0;
		radius = 4;
		break;
	case WP_GRENADE:
		mod = cgs.media.dishFlashModel;
		shader = cgs.media.grenadeExplosionShader;
		sfx = cgs.media.sfx_rockexp;
		mark = cgs.media.burnMarkShader;
		radius = 96;	//64
		light = 450;	//300
		isSprite = qtrue;
		break;
	
	case WP_KNIFE:
		/*
		mod = cgs.media.dishFlashModel;
		//shader = cgs.media.grenadeExplosionShader;
		sfx = cgs.media.sfx_rockexp;
		mark = cgs.media.burnMarkShader;
		radius = 64;
		light = 300;
		isSprite = qtrue;
		break;
		*/
		mod = cgs.media.bulletFlashModel;
		shader = cgs.media.bulletExplosionShader;
		mark = cgs.media.bulletMarkShader;
		sfx = 0;
		radius = 4;
		
		break;
	default:
		break;
	}

	//Elder: 75% of the time render a bullet ricochet sound
	i = (int)(random() * 35) % 4;
	if ( sfx && i < 3) {
		trap_S_StartSound( origin, ENTITYNUM_WORLD, CHAN_AUTO, sfx );
	}

	//
	// create the explosion
	//
	if ( mod ) {
		le = CG_MakeExplosion( origin, dir, 
							   mod,	shader,
							   duration, isSprite );
		le->light = light;
		VectorCopy( lightColor, le->lightColor );
		//Blaze: No railgun
		/*
		if ( weapon == WP_RAILGUN ) {
			// colorize with client color
			VectorCopy( cgs.clientinfo[clientNum].color, le->color );
		}
		*/
	}

	//
	// impact mark
	//
	alphaFade = (mark == cgs.media.energyMarkShader);	// plasma fades alpha, all others fade color
	//Blaze: No more railgun
	//if ( weapon == WP_RAILGUN ) {
	//	float	*color;

		// colorize with client color
	//	color = cgs.clientinfo[clientNum].color;
	//	CG_ImpactMark( mark, origin, dir, random()*360, color[0],color[1], color[2],1, alphaFade, radius, qfalse );
	//} else {
		CG_ImpactMark( mark, origin, dir, random()*360, 1,1,1,1, alphaFade, radius, qfalse );
	//}

	
	//Elder: 75% of the time render a smoke puff
	i = (int)(random() * 100) % 4;
	if (cg_RQ3_impactEffects.integer && i < 3)
	{
		switch ( weapon ) {	
			case WP_MP5:
			case WP_M4:
			case WP_PISTOL:
				puffDir[0] = 0;
				puffDir[1] = 0;
				puffDir[2] = 16;

				VectorCopy(dir, puffOffset);
				VectorNormalize(puffOffset);
				VectorNegate(puffOffset, puffOffset);
				VectorScale(puffOffset, 13, puffOffset);
				VectorSubtract(origin, puffOffset, puffOrigin);
				smokePuff = CG_SmokePuff( puffOrigin, puffDir, 
						  (int)(random() * 100) % 4 + 13, 
						  1, 1, 1, 0.25f,
						  650, 
						  cg.time, 0,
						  LEF_PUFF_DONT_SCALE, 
						  cgs.media.smokePuffShader );
				break;
		}
	}
}


/*
=================
CG_MissileHitPlayer
=================
*/
void CG_MissileHitPlayer( int weapon, vec3_t origin, vec3_t dir, int entityNum ) {
	CG_Bleed( origin, entityNum );

	// some weapons will make an explosion with the blood, while
	// others will just make the blood
	//Blaze: None of these are valid
	/*
	switch ( weapon ) {
	case WP_GRENADE_LAUNCHER:
	case WP_ROCKET_LAUNCHER:
#ifdef MISSIONPACK
	case WP_NAILGUN:
	case WP_CHAINGUN:
	case WP_PROX_LAUNCHER:
#endif
		CG_MissileHitWall( weapon, 0, origin, dir, IMPACTSOUND_FLESH );
		break;
	default:
		break;
	}
	*/
}



/*
============================================================================

SHOTGUN TRACING

============================================================================
*/

/*
================
CG_ShotgunPellet

Elder: added shellWeapon param
We are not going to show every HC impact
================
*/
static void CG_ShotgunPellet( vec3_t start, vec3_t end, int skipNum, int shellWeapon ) {
	trace_t		tr;
	int sourceContentType, destContentType;

	CG_Trace( &tr, start, NULL, NULL, end, skipNum, MASK_SHOT );

	sourceContentType = trap_CM_PointContents( start, 0 );
	destContentType = trap_CM_PointContents( tr.endpos, 0 );

	// FIXME: should probably move this cruft into CG_BubbleTrail
	if ( sourceContentType == destContentType ) {
		if ( sourceContentType & CONTENTS_WATER ) {
			CG_BubbleTrail( start, tr.endpos, 32 );
		}
	} else if ( sourceContentType & CONTENTS_WATER ) {
		trace_t trace;

		trap_CM_BoxTrace( &trace, end, start, NULL, NULL, 0, CONTENTS_WATER );
		CG_BubbleTrail( start, trace.endpos, 32 );
	} else if ( destContentType & CONTENTS_WATER ) {
		trace_t trace;

		trap_CM_BoxTrace( &trace, start, end, NULL, NULL, 0, CONTENTS_WATER );
		CG_BubbleTrail( tr.endpos, trace.endpos, 32 );
	}

	if (  tr.surfaceFlags & SURF_NOIMPACT ) {
		return;
	}

	if ( cg_entities[tr.entityNum].currentState.eType == ET_PLAYER ) {
		//Blaze: Changed WP_SHOTGUN to WP_M3
		CG_MissileHitPlayer( WP_M3, tr.endpos, tr.plane.normal, tr.entityNum );
	} else {
		if ( tr.surfaceFlags & SURF_NOIMPACT ) {
			// SURF_NOIMPACT will not make a flame puff or a mark
			return;
		}
		if ( tr.surfaceFlags & SURF_METALSTEPS ) {
			//Blaze: Changed WP_SHOTGUN to WP_M3
			if (shellWeapon == WP_M3)
				CG_MissileHitWall( WP_M3, 0, tr.endpos, tr.plane.normal, IMPACTSOUND_METAL );
			else if (shellWeapon == WP_HANDCANNON && crandom() > 0.5) {
				//Elder: show only approximately every other impact mark
				CG_MissileHitWall( WP_HANDCANNON, 0, tr.endpos, tr.plane.normal, IMPACTSOUND_METAL );
			}				
		} else {
			//Blaze: Changed WP_SHOTGUN to WP_M3
			if (shellWeapon == WP_M3)
				CG_MissileHitWall( WP_M3, 0, tr.endpos, tr.plane.normal, IMPACTSOUND_DEFAULT );
			else if (shellWeapon == WP_HANDCANNON && crandom() > 0.5) {
				//Elder: show only approximately every other impact mark
				CG_MissileHitWall( WP_HANDCANNON, 0, tr.endpos, tr.plane.normal, IMPACTSOUND_DEFAULT );
			}
			//CG_MissileHitWall( WP_M3, 0, tr.endpos, tr.plane.normal, IMPACTSOUND_DEFAULT );
		}
	}
}

/*
================
CG_ShotgunPattern

Perform the same traces the server did to locate the
hit splashes (FIXME: random seed isn't synce anymore)
Elder: hopefully fixed the seed problem
================
*/
static void CG_ShotgunPattern( vec3_t origin, vec3_t origin2, int otherEntNum, int shotType, int seed ) {
	int			i;
	float		r, u;
	vec3_t		end;
	vec3_t		forward, right, up;

	int			count;
	int			hc_multipler;

	// derive the right and up vectors from the forward vector, because
	// the client won't have any other information
	VectorNormalize2( origin2, forward );
	PerpendicularVector( right, forward );
	CrossProduct( forward, right, up );

	// generate the "random" spread pattern

	//Elder: added
	if (shotType == WP_M3)
		count = DEFAULT_M3_COUNT;
	else if (shotType == WP_HANDCANNON) {
		count = DEFAULT_HANDCANNON_COUNT;
		hc_multipler = 4;
	}
	else {
		count = DEFAULT_HANDCANNON_COUNT;
		hc_multipler = 5;
	}


	for ( i = 0 ; i < count ; i++ ) {
		if (shotType == WP_M3)
		{
			r = Q_crandom(&seed) * DEFAULT_M3_HSPREAD * 16;
			u = Q_crandom(&seed) * DEFAULT_M3_VSPREAD * 16;
			//r = crandom() * DEFAULT_M3_HSPREAD * 16;
			//u = crandom() * DEFAULT_M3_VSPREAD * 16;
			//r = crandom() * DEFAULT_SHOTGUN_SPREAD * 16;
			//u = crandom() * DEFAULT_SHOTGUN_SPREAD * 16;
		}
		else
		{
			//Elder: fill in shotType
			shotType = WP_HANDCANNON;
			r = Q_crandom(&seed) * DEFAULT_SHOTGUN_HSPREAD * 16 * 4;
			u = Q_crandom(&seed) * DEFAULT_SHOTGUN_VSPREAD * 16 * hc_multipler;
//			r = crandom() * DEFAULT_HANDCANNON_SPREAD * 16 * 4;
//			u = crandom() * DEFAULT_HANDCANNON_SPREAD * 16 * 4;
		}
		VectorMA( origin, 8192 * 16, forward, end);
		VectorMA (end, r, right, end);
		VectorMA (end, u, up, end);

		CG_ShotgunPellet( origin, end, otherEntNum, shotType );
	}
}

/*
==============
CG_ShotgunFire
==============
*/
void CG_ShotgunFire( entityState_t *es, qboolean ism3) {
	vec3_t	v;
	int		contents;

	VectorSubtract( es->origin2, es->pos.trBase, v );
	VectorNormalize( v );
	VectorScale( v, 32, v );
	VectorAdd( es->pos.trBase, v, v );
	if ( cgs.glconfig.hardwareType != GLHW_RAGEPRO ) {
		// ragepro can't alpha fade, so don't even bother with smoke
		vec3_t			up;

		contents = trap_CM_PointContents( es->pos.trBase, 0 );
		if ( !( contents & CONTENTS_WATER ) ) {
			VectorSet( up, 0, 0, 8 );
			CG_SmokePuff( v, up, 32, 1, 1, 1, 0.33f, 900, cg.time, 0, LEF_PUFF_DONT_SCALE, cgs.media.shotgunSmokePuffShader );
		}
	}
	//Elder: note param changes
	if (ism3)	
	{
		CG_ShotgunPattern( es->pos.trBase, es->origin2, es->otherEntityNum, WP_M3, es->eventParm);
	}
	else
	{
		CG_ShotgunPattern( es->pos.trBase, es->origin2, es->otherEntityNum, WP_HANDCANNON, es->eventParm);
		es->angles2[1] += 20;
		//es->origin2[1] += 5;
		CG_ShotgunPattern( es->pos.trBase, es->origin2, es->otherEntityNum, -1, es->eventParm);
	}
}

/*
============================================================================

BULLETS

============================================================================
*/


/*
===============
CG_Tracer
===============
*/
void CG_Tracer( vec3_t source, vec3_t dest ) {
	vec3_t		forward, right;
	polyVert_t	verts[4];
	vec3_t		line;
	float		len, begin, end;
	vec3_t		start, finish;
	vec3_t		midpoint;

	// tracer
	VectorSubtract( dest, source, forward );
	len = VectorNormalize( forward );

	// start at least a little ways from the muzzle
	if ( len < 100 ) {
		return;
	}
	begin = 50 + random() * (len - 60);
	end = begin + cg_tracerLength.value;
	if ( end > len ) {
		end = len;
	}
	VectorMA( source, begin, forward, start );
	VectorMA( source, end, forward, finish );

	line[0] = DotProduct( forward, cg.refdef.viewaxis[1] );
	line[1] = DotProduct( forward, cg.refdef.viewaxis[2] );

	VectorScale( cg.refdef.viewaxis[1], line[1], right );
	VectorMA( right, -line[0], cg.refdef.viewaxis[2], right );
	VectorNormalize( right );

	VectorMA( finish, cg_tracerWidth.value, right, verts[0].xyz );
	verts[0].st[0] = 0;
	verts[0].st[1] = 1;
	verts[0].modulate[0] = 255;
	verts[0].modulate[1] = 255;
	verts[0].modulate[2] = 255;
	verts[0].modulate[3] = 255;

	VectorMA( finish, -cg_tracerWidth.value, right, verts[1].xyz );
	verts[1].st[0] = 1;
	verts[1].st[1] = 0;
	verts[1].modulate[0] = 255;
	verts[1].modulate[1] = 255;
	verts[1].modulate[2] = 255;
	verts[1].modulate[3] = 255;

	VectorMA( start, -cg_tracerWidth.value, right, verts[2].xyz );
	verts[2].st[0] = 1;
	verts[2].st[1] = 1;
	verts[2].modulate[0] = 255;
	verts[2].modulate[1] = 255;
	verts[2].modulate[2] = 255;
	verts[2].modulate[3] = 255;

	VectorMA( start, cg_tracerWidth.value, right, verts[3].xyz );
	verts[3].st[0] = 0;
	verts[3].st[1] = 0;
	verts[3].modulate[0] = 255;
	verts[3].modulate[1] = 255;
	verts[3].modulate[2] = 255;
	verts[3].modulate[3] = 255;

	trap_R_AddPolyToScene( cgs.media.tracerShader, 4, verts );

	midpoint[0] = ( start[0] + finish[0] ) * 0.5;
	midpoint[1] = ( start[1] + finish[1] ) * 0.5;
	midpoint[2] = ( start[2] + finish[2] ) * 0.5;

	// add the tracer sound
	trap_S_StartSound( midpoint, ENTITYNUM_WORLD, CHAN_AUTO, cgs.media.tracerSound );

}


/*
======================
CG_CalcMuzzlePoint
======================
*/
static qboolean	CG_CalcMuzzlePoint( int entityNum, vec3_t muzzle ) {
	vec3_t		forward;
	centity_t	*cent;
	int			anim;

	if ( entityNum == cg.snap->ps.clientNum ) {
		VectorCopy( cg.snap->ps.origin, muzzle );
		muzzle[2] += cg.snap->ps.viewheight;
		AngleVectors( cg.snap->ps.viewangles, forward, NULL, NULL );
		VectorMA( muzzle, 14, forward, muzzle );
		return qtrue;
	}

	cent = &cg_entities[entityNum];
	if ( !cent->currentValid ) {
		return qfalse;
	}

	VectorCopy( cent->currentState.pos.trBase, muzzle );

	AngleVectors( cent->currentState.apos.trBase, forward, NULL, NULL );
	anim = cent->currentState.legsAnim & ~ANIM_TOGGLEBIT;
	if ( anim == LEGS_WALKCR || anim == LEGS_IDLECR ) {
		muzzle[2] += CROUCH_VIEWHEIGHT;
	} else {
		muzzle[2] += DEFAULT_VIEWHEIGHT;
	}

	VectorMA( muzzle, 14, forward, muzzle );

	return qtrue;

}

/*
======================
CG_Bullet

Renders bullet effects.
======================
*/
void CG_Bullet( vec3_t end, int sourceEntityNum, vec3_t normal, qboolean flesh, int fleshEntityNum ) {
	trace_t trace;
	int sourceContentType, destContentType;
	vec3_t		start;

	// if the shooter is currently valid, calc a source point and possibly
	// do trail effects
	if ( sourceEntityNum >= 0 && cg_tracerChance.value > 0 ) {
		if ( CG_CalcMuzzlePoint( sourceEntityNum, start ) ) {
			sourceContentType = trap_CM_PointContents( start, 0 );
			destContentType = trap_CM_PointContents( end, 0 );

			// do a complete bubble trail if necessary
			if ( ( sourceContentType == destContentType ) && ( sourceContentType & CONTENTS_WATER ) ) {
				CG_BubbleTrail( start, end, 32 );
			}
			// bubble trail from water into air
			else if ( ( sourceContentType & CONTENTS_WATER ) ) {
				trap_CM_BoxTrace( &trace, end, start, NULL, NULL, 0, CONTENTS_WATER );
				CG_BubbleTrail( start, trace.endpos, 32 );
			}
			// bubble trail from air into water
			else if ( ( destContentType & CONTENTS_WATER ) ) {
				trap_CM_BoxTrace( &trace, start, end, NULL, NULL, 0, CONTENTS_WATER );
				CG_BubbleTrail( trace.endpos, end, 32 );
			}

			// draw a tracer
			if ( random() < cg_tracerChance.value ) {
				CG_Tracer( start, end );
			}
		}
	}

	// impact splash and mark
	if ( flesh ) {
		CG_Bleed( end, fleshEntityNum );
	} else {
		//Blaze: Changed WP_MACHINEGUN to WP_PISTOL
		CG_MissileHitWall( WP_PISTOL, 0, end, normal, IMPACTSOUND_DEFAULT );
	}

}
