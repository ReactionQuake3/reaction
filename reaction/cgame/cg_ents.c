//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.43  2003/04/19 15:27:30  jbravo
// Backing out of most of unlagged.  Only optimized prediction and smooth clients
// remains.
//
// Revision 1.42  2003/04/02 17:58:03  jbravo
// Ammo skin only replacements now work.
//
// Revision 1.41  2003/03/28 22:25:10  makro
// no message
//
// Revision 1.40  2003/03/10 07:07:58  jbravo
// Small unlagged fixes and voting delay added.
//
// Revision 1.39  2003/03/09 21:30:38  jbravo
// Adding unlagged.   Still needs work.
//
// Revision 1.38  2003/03/08 09:58:08  niceass
// Changes to make my "position on tag with offset" work correctly with orientation matrices crap for CTB tag_weapon2
//
// Revision 1.37  2003/02/27 20:51:14  makro
// no message
//
// Revision 1.36  2003/02/27 19:52:34  makro
// dlights
//
// Revision 1.35  2003/02/01 02:15:31  jbravo
// Replacement models and items
//
// Revision 1.34  2003/01/08 04:46:25  jbravo
// Wrote a new hackish model replacement system
//
// Revision 1.33  2002/09/01 21:14:36  makro
// Sky portal tweaks
//
// Revision 1.32  2002/08/29 23:58:27  makro
// Sky portals
//
// Revision 1.31  2002/08/27 05:10:42  niceass
// new ctb marker shader names
//
// Revision 1.30  2002/07/19 04:33:52  niceass
// laser fog fix and ctb markers
//
// Revision 1.29  2002/06/21 21:06:20  niceass
// laserfog stuff
//
// Revision 1.28  2002/06/21 04:11:17  niceass
// fog laser
//
// Revision 1.27  2002/06/16 20:06:13  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.26  2002/06/16 19:12:52  jbravo
// Removed the MISSIONPACK ifdefs and missionpack only code.
//
// Revision 1.25  2002/04/23 06:09:18  niceass
// pressure stuff
//
// Revision 1.24  2002/04/09 18:52:13  makro
// Target_speakers can now be toggled on/off
//
// Revision 1.23  2002/04/03 03:13:48  blaze
// NEW BREAKABLE CODE - will break all old breakables(wont appear in maps)
//
// Revision 1.22  2002/03/31 13:52:48  jbravo
// More cleanups
//
// Revision 1.21  2002/03/31 03:31:24  jbravo
// Compiler warning cleanups
//
// Revision 1.20  2002/03/31 02:03:35  niceass
// new testing tag command
//
// Revision 1.19  2002/03/16 21:50:49  niceass
// I tabbed a function properly. It was pissing me off
//
// Revision 1.18  2002/01/14 01:19:23  niceass
// No more default 800 gravity on items - NiceAss
//
// Revision 1.17  2002/01/11 19:48:29  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.16  2001/12/31 16:28:41  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
// cg_ents.c -- present snapshot entities, happens every single frame

#include "cg_local.h"

static void CG_LaserSight(centity_t * cent);
static void CG_Dlight(centity_t * cent);

extern char rq3_breakables[RQ3_MAX_BREAKABLES][80];

extern void trap_R_AddAdditiveLightToScene(const vec3_t org, float intensity, float r, float g, float b);

/*
======================
CG_PositionEntityOnTag

Modifies the entities position and axis by the given
tag location
======================
*/
void CG_PositionEntityOnTag(refEntity_t * entity, const refEntity_t * parent, qhandle_t parentModel, char *tagName)
{
	int i;
	orientation_t lerped;

	// lerp the tag
	trap_R_LerpTag(&lerped, parentModel, parent->oldframe, parent->frame, 1.0 - parent->backlerp, tagName);

	// FIXME: allow origin offsets along tag?
	VectorCopy(parent->origin, entity->origin);
	for (i = 0; i < 3; i++) {
		VectorMA(entity->origin, lerped.origin[i], parent->axis[i], entity->origin);
	}

	// had to cast away the const to avoid compiler problems...
	MatrixMultiply(lerped.axis, ((refEntity_t *) parent)->axis, entity->axis);
	entity->backlerp = parent->backlerp;
}

/* [QUARANTINE] - CG_PositionWeaponOnTag
======================
CG_PositionWeaponOnTag

Changed from CG_PositionEntityOnTag function to prevent backlerp change in animations
======================
*/
void CG_PositionWeaponOnTag(refEntity_t * entity, const refEntity_t * parent, qhandle_t parentModel, char *tagName)
{
	int i;
	orientation_t lerped;

	// lerp the tag
	trap_R_LerpTag(&lerped, parentModel, parent->oldframe, parent->frame, 1.0 - parent->backlerp, tagName);

	// FIXME: allow origin offsets along tag?
	VectorCopy(parent->origin, entity->origin);
	for (i = 0; i < 3; i++) {
		VectorMA(entity->origin, lerped.origin[i], parent->axis[i], entity->origin);
	}

	// had to cast away the const to avoid compiler problems...
	MatrixMultiply(lerped.axis, ((refEntity_t *) parent)->axis, entity->axis);
	// entity->backlerp = parent->backlerp;
}

/*
======================
CG_PositionRotatedEntityOnTag

Modifies the entities position and axis by the given
tag location
======================
*/
void CG_PositionRotatedEntityOnTag(refEntity_t * entity, const refEntity_t * parent,
				   qhandle_t parentModel, char *tagName)
{
	int i;
	orientation_t lerped;
	vec3_t tempAxis[3];

//AxisClear( entity->axis );
	// lerp the tag
	trap_R_LerpTag(&lerped, parentModel, parent->oldframe, parent->frame, 1.0 - parent->backlerp, tagName);

	// FIXME: allow origin offsets along tag?
	VectorCopy(parent->origin, entity->origin);
	for (i = 0; i < 3; i++) {
		VectorMA(entity->origin, lerped.origin[i], parent->axis[i], entity->origin);
	}

	// had to cast away the const to avoid compiler problems...
	MatrixMultiply(entity->axis, lerped.axis, tempAxis);
	MatrixMultiply(tempAxis, ((refEntity_t *) parent)->axis, entity->axis);
}

/*
======================
CG_PositionRotatedEntityOnTag

Modifies the entities position and axis by the given
tag location
======================
*/
void CG_PositionRotatedOffsetEntityOnTag(refEntity_t * entity, const refEntity_t * parent,
					 qhandle_t parentModel, char *tagName, vec3_t Offset)
{
	int i;
	orientation_t lerped;
	vec3_t tempAxis[3];	//, tmp;

	// lerp the tag
	trap_R_LerpTag(&lerped, parentModel, parent->oldframe, parent->frame, 1.0 - parent->backlerp, tagName);

	VectorCopy(parent->origin, entity->origin);
	for (i = 0; i < 3; i++)
		VectorMA(entity->origin, lerped.origin[i], parent->axis[i], entity->origin);

	// had to cast away the const to avoid compiler problems...
	MatrixMultiply(entity->axis, lerped.axis, tempAxis);
	MatrixMultiply(tempAxis, ((refEntity_t *) parent)->axis, entity->axis);

	for (i = 0; i < 3; i++)
		VectorMA(entity->origin, Offset[i], entity->axis[i], entity->origin);
}

/*
==========================================================================

FUNCTIONS CALLED EACH FRAME

==========================================================================
*/

/*
======================
CG_SetEntitySoundPosition

Also called by event processing code
======================
*/
void CG_SetEntitySoundPosition(centity_t * cent)
{
	if (cent->currentState.solid == SOLID_BMODEL) {
		vec3_t origin;
		float *v;

		v = cgs.inlineModelMidpoints[cent->currentState.modelindex];
		VectorAdd(cent->lerpOrigin, v, origin);
		trap_S_UpdateEntityPosition(cent->currentState.number, origin);
	} else {
		trap_S_UpdateEntityPosition(cent->currentState.number, cent->lerpOrigin);
	}
}

/*
==================
CG_EntityEffects

Add continuous entity effects, like local entity emission and lighting
==================
*/
static void CG_EntityEffects(centity_t * cent)
{

	// update sound origins
	CG_SetEntitySoundPosition(cent);

	// add loop sound
	if (cent->currentState.loopSound) {
		//Makro - maybe this will help with the speakers ?
		//if (cent->currentState.eType != ET_SPEAKER) {
		trap_S_AddLoopingSound(cent->currentState.number, cent->lerpOrigin, vec3_origin,
				       cgs.gameSounds[cent->currentState.loopSound]);
		//} else {
		//      trap_S_AddRealLoopingSound( cent->currentState.number, cent->lerpOrigin, vec3_origin,
		//              cgs.gameSounds[ cent->currentState.loopSound ] );
		//}
	}

	// constant light glow
	if (cent->currentState.constantLight && cent->currentState.eType != ET_DLIGHT) {
		int cl;
		int i, r, g, b;

		cl = cent->currentState.constantLight;
		r = cl & 255;
		g = (cl >> 8) & 255;
		b = (cl >> 16) & 255;
		i = ((cl >> 24) & 255) * 4;

		trap_R_AddLightToScene(cent->lerpOrigin, i, r, g, b);
	}

}

/*
==================
CG_General
==================
*/
static void CG_General(centity_t * cent)
{
	refEntity_t ent;
	entityState_t *s1;

	s1 = &cent->currentState;

	// if set to invisible, skip
	if (!s1->modelindex) {
		return;
	}

	memset(&ent, 0, sizeof(ent));

	// set frame

	ent.frame = s1->frame;
	ent.oldframe = ent.frame;
	ent.backlerp = 0;

	VectorCopy(cent->lerpOrigin, ent.origin);
	VectorCopy(cent->lerpOrigin, ent.oldorigin);

	ent.hModel = cgs.gameModels[s1->modelindex];

	// player model
	if (s1->number == cg.snap->ps.clientNum) {
		ent.renderfx |= RF_THIRD_PERSON;	// only draw from mirrors
	}
	// convert angles to axis
	AnglesToAxis(cent->lerpAngles, ent.axis);

	// add to refresh list
	trap_R_AddRefEntityToScene(&ent);
}

/*
==================
CG_Speaker

Speaker entities can automatically play sounds
==================
*/
static void CG_Speaker(centity_t * cent)
{
	if (!cent->currentState.clientNum) {	// FIXME: use something other than clientNum...
		return;		// not auto triggering
	}

	if (cg.time < cent->miscTime) {
		return;
	}

	trap_S_StartSound(NULL, cent->currentState.number, CHAN_ITEM, cgs.gameSounds[cent->currentState.eventParm]);

	//      ent->s.frame = ent->wait * 10;
	//      ent->s.clientNum = ent->random * 10;
	cent->miscTime = cg.time + cent->currentState.frame * 100 + cent->currentState.clientNum * 100 * crandom();
}

/*
==================
CG_Item
==================
*/
static void CG_Item(centity_t * cent)
{
	refEntity_t ent;
	entityState_t *es;
	gitem_t *item;
	int msec;
	float frac, scale;
	weaponInfo_t *wi;
	itemInfo_t *itemInfo;

	es = &cent->currentState;
	if (es->modelindex >= bg_numItems) {
		CG_Error("Bad item index %i on entity", es->modelindex);
	}
	// if set to invisible, skip
	if (!es->modelindex || (es->eFlags & EF_NODRAW)) {
		return;
	}

	item = &bg_itemlist[es->modelindex];
	if (cg_simpleItems.integer && item->giType != IT_TEAM) {
		memset(&ent, 0, sizeof(ent));
		ent.reType = RT_SPRITE;
		VectorCopy(cent->lerpOrigin, ent.origin);
		// Elder: lower them slightly
		ent.origin[2] -= 6;
		// Elder: make auto-sprites smaller, especially grenades and knifes
		if (item->giType == IT_WEAPON) {
			if (item->giTag == WP_GRENADE || item->giTag == WP_KNIFE)
				ent.radius = 4;
			else
				ent.radius = 14;
		} else if (item->giType == IT_HOLDABLE)
			ent.radius = 10;
		else
			ent.radius = 6;
		//ent.radius = 14;
		ent.customShader = cg_items[es->modelindex].icon;
		ent.shaderRGBA[0] = 255;
		ent.shaderRGBA[1] = 255;
		ent.shaderRGBA[2] = 255;
		ent.shaderRGBA[3] = 255;
		trap_R_AddRefEntityToScene(&ent);
		return;
	}

	memset(&ent, 0, sizeof(ent));

	//Elder: knife rotation code so it's always "in" the wall
	if (item->giTag == WP_KNIFE && ((es->eFlags & FL_THROWN_KNIFE) == FL_THROWN_KNIFE)) {
		VectorCopy(es->angles, cent->lerpAngles);
		//Elder: nudges out a bit so it's more visible
		VectorCopy(es->origin, cent->lerpOrigin);
		AnglesToAxis(cent->lerpAngles, ent.axis);
	} else {
		//Elder: default item orientation
		VectorCopy(cg.autoAngles, cent->lerpAngles);
		AxisCopy(cg.autoAxis, ent.axis);
	}

	if (item->giType == IT_WEAPON && item->giTag != WP_KNIFE &&
	    (es->pos.trDelta[0] != 0 || es->pos.trDelta[1] != 0 || es->pos.trDelta[2] != 0)) {
		vec3_t myvec;

		//Elder: old fashioned AQ2 weapon drop rotating-style code :)
		//It's out here because the wi calculations mess up the lerpOrigin
		VectorCopy(cg.autoAnglesFast, cent->lerpAngles);
		AxisCopy(cg.autoAxisFast, ent.axis);

		VectorCopy(ent.axis[1], myvec);
		VectorNegate(ent.axis[2], ent.axis[1]);
		VectorCopy(myvec, ent.axis[2]);
	} else if (item->giType == IT_HOLDABLE) {
		//Elder: rotate item if moving
		if (es->pos.trDelta[0] != 0 || es->pos.trDelta[1] != 0 || es->pos.trDelta[2] != 0) {
			VectorCopy(cg.autoAnglesFast, cent->lerpAngles);
			AxisCopy(cg.autoAxisFast, ent.axis);
		} else
			AnglesToAxis(es->angles, ent.axis);
	}

	wi = NULL;
	// the weapons have their origin where they attatch to player
	// models, so we need to offset them or they will rotate
	// eccentricly
	//Elder: added knife conditional
	if (item->giType == IT_WEAPON &&
	    !(item->giTag == WP_KNIFE && ((es->eFlags & FL_THROWN_KNIFE) == FL_THROWN_KNIFE))) {

		vec3_t myvec;

		// Elder: bad hack -- but oh well.
		if (es->pos.trDelta[0] == 0 && es->pos.trDelta[1] == 0 && es->pos.trDelta[2] == 0)
			AnglesToAxis(es->angles, ent.axis);

		//CG_Printf("Should not be in here if it's a thrown knife\n");
		wi = &cg_weapons[item->giTag];
		cent->lerpOrigin[0] -=
		    wi->weaponMidpoint[0] * ent.axis[0][0] +
		    wi->weaponMidpoint[1] * ent.axis[1][0] + wi->weaponMidpoint[2] * ent.axis[2][0];
		cent->lerpOrigin[1] -=
		    wi->weaponMidpoint[0] * ent.axis[0][1] +
		    wi->weaponMidpoint[1] * ent.axis[1][1] + wi->weaponMidpoint[2] * ent.axis[2][1];
		cent->lerpOrigin[2] -=
		    wi->weaponMidpoint[0] * ent.axis[0][2] +
		    wi->weaponMidpoint[1] * ent.axis[1][2] + wi->weaponMidpoint[2] * ent.axis[2][2];
		//Blaze: Dont raise the weapon, but lower it
		//Elder: don't lower knives by much - this is bad hardcode but oh well
		if (item->giTag == WP_KNIFE)
			cent->lerpOrigin[2] -= 10;
		else
			cent->lerpOrigin[2] -= 14;

		//      cent->lerpOrigin[2] += 8;       // an extra height boost

		if (es->pos.trDelta[0] == 0 && es->pos.trDelta[1] == 0 && es->pos.trDelta[2] == 0) {
			// Blaze: rotate the gun by 90 degrees to place it on the ground
			VectorCopy(ent.axis[1], myvec);
			VectorNegate(ent.axis[2], ent.axis[1]);
			VectorCopy(myvec, ent.axis[2]);
		}
	}
	// JBravo: world skins
	if (item->giType == IT_WEAPON) {
		wi = &cg_weapons[item->giTag];
		if (wi->customSkin)
			ent.customSkin = wi->customSkin;
	}
	if (item->giType == IT_HOLDABLE || item->giType == IT_AMMO) {
		itemInfo = &cg_items[item - bg_itemlist];
		if (itemInfo->customSkin)
			ent.customSkin = itemInfo->customSkin;
	}

	//Elder: ammo offset?
	if (item->giType == IT_AMMO)
		cent->lerpOrigin[2] -= 12;
	else if (item->giType == IT_HOLDABLE)
		cent->lerpOrigin[2] -= 12;

	ent.hModel = cg_items[es->modelindex].models[0];

	VectorCopy(cent->lerpOrigin, ent.origin);
	VectorCopy(cent->lerpOrigin, ent.oldorigin);

	ent.nonNormalizedAxes = qfalse;

	// if just respawned, slowly scale up
	msec = cg.time - cent->miscTime;
	if (msec >= 0 && msec < ITEM_SCALEUP_TIME) {
		frac = (float) msec / ITEM_SCALEUP_TIME;
		VectorScale(ent.axis[0], frac, ent.axis[0]);
		VectorScale(ent.axis[1], frac, ent.axis[1]);
		VectorScale(ent.axis[2], frac, ent.axis[2]);
		ent.nonNormalizedAxes = qtrue;
	} else {
		frac = 1.0;
	}

	// Elder: special items and ammo should have minimum light too
	// items without glow textures need to keep a minimum light value
	// so they are always visible
	if ((item->giType == IT_WEAPON) ||
	    (item->giType == IT_ARMOR) || (item->giType == IT_AMMO) || (item->giType == IT_HOLDABLE)) {
		ent.renderfx |= RF_MINLIGHT;
	}
	// increase the size of the weapons when they are presented as items

	// Elder: only for knives, which are hard to spot
	// NiceAss: Scale code modified for weapons too.
	if (item->giTag == WP_KNIFE)
		scale = WEAPON_KNIFE_SCALE;
	else if (item->giType == IT_WEAPON && item->giTag != WP_KNIFE)
		scale = (float) WEAPON_GUN_SCALE;
	else
		scale = WEAPON_OTHER_SCALE;

	VectorScale(ent.axis[0], scale, ent.axis[0]);
	VectorScale(ent.axis[1], scale, ent.axis[1]);
	VectorScale(ent.axis[2], scale, ent.axis[2]);

	// add to refresh list
	trap_R_AddRefEntityToScene(&ent);

	// add strobe effect -- should make this toggle?
	// NiceAss: Temp Cvar usage for strobe shader.
	if ((item->giType == IT_WEAPON ||
	     item->giType == IT_ARMOR ||
	     item->giType == IT_AMMO || item->giType == IT_HOLDABLE) && cg_RQ3_strobe.integer == 1) {
		ent.customShader = cgs.media.itemStrobeShader;
		trap_R_AddRefEntityToScene(&ent);
	}
	// accompanying rings / spheres for powerups
	if (!cg_simpleItems.integer) {
		vec3_t spinAngles;

		VectorClear(spinAngles);

		if (item->giType == IT_HEALTH || item->giType == IT_POWERUP) {
			if ((ent.hModel = cg_items[es->modelindex].models[1]) != 0) {
				if (item->giType == IT_POWERUP) {
					ent.origin[2] += 12;
					spinAngles[1] = (cg.time & 1023) * 360 / -1024.0f;
				}
				AnglesToAxis(spinAngles, ent.axis);

				// scale up if respawning
				if (frac != 1.0) {
					VectorScale(ent.axis[0], frac, ent.axis[0]);
					VectorScale(ent.axis[1], frac, ent.axis[1]);
					VectorScale(ent.axis[2], frac, ent.axis[2]);
					ent.nonNormalizedAxes = qtrue;
				}
				trap_R_AddRefEntityToScene(&ent);
			}
		}
	}
}

//============================================================================

/*
===============
CG_Missile
===============
*/
static void CG_Missile(centity_t * cent)
{
	refEntity_t ent;
	entityState_t *s1;
	const weaponInfo_t *weapon;

	s1 = &cent->currentState;
	if (s1->weapon > WP_NUM_WEAPONS) {
		s1->weapon = 0;
	}
	weapon = &cg_weapons[s1->weapon];

	// calculate the axis
	VectorCopy(s1->angles, cent->lerpAngles);

	// add trails
	if (weapon->missileTrailFunc) {
		weapon->missileTrailFunc(cent, weapon);
	}
	// add dynamic light
	if (weapon->missileDlight) {
		trap_R_AddLightToScene(cent->lerpOrigin, weapon->missileDlight,
				       weapon->missileDlightColor[0], weapon->missileDlightColor[1],
				       weapon->missileDlightColor[2]);
	}
	// add missile sound
	if (weapon->missileSound) {
		vec3_t velocity;

		CG_EvaluateTrajectoryDelta(&cent->currentState.pos, cg.time, velocity);

		trap_S_AddLoopingSound(cent->currentState.number, cent->lerpOrigin, velocity, weapon->missileSound);
	}
	// create the render entity
	memset(&ent, 0, sizeof(ent));
	VectorCopy(cent->lerpOrigin, ent.origin);
	VectorCopy(cent->lerpOrigin, ent.oldorigin);

	// flicker between two skins
	ent.skinNum = cg.clientFrame & 1;
	ent.hModel = weapon->missileModel;
	ent.renderfx = weapon->missileRenderfx | RF_NOSHADOW;

	// convert direction of travel into axis
	if (VectorNormalize2(s1->pos.trDelta, ent.axis[0]) == 0) {
		ent.axis[0][2] = 1;
	}
	// spin as it moves
	if (s1->pos.trType != TR_STATIONARY) {
		//Spin knife like a wheel
		if (s1->weapon == WP_KNIFE) {
			vec3_t knifeVelocity;

			CG_EvaluateTrajectoryDelta(&s1->pos, cg.time, knifeVelocity);
			vectoangles(knifeVelocity, cent->lerpAngles);
			cent->lerpAngles[0] += cg.time;	// was / 6

			AnglesToAxis(cent->lerpAngles, ent.axis);

			// NiceAss: Added for scaling of the knife in flight and not just when sticking in a wall.
			VectorScale(ent.axis[0], WEAPON_KNIFE_SCALE, ent.axis[0]);
			VectorScale(ent.axis[1], WEAPON_KNIFE_SCALE, ent.axis[1]);
			VectorScale(ent.axis[2], WEAPON_KNIFE_SCALE, ent.axis[2]);
		} else
			RotateAroundDirection(ent.axis, cg.time / 4);
	} else {
		RotateAroundDirection(ent.axis, s1->time);
	}

	// add to refresh list, possibly with quad glow
	CG_AddRefEntityWithPowerups(&ent, s1, TEAM_FREE);
}

/*
===============
CG_Grapple

This is called when the grapple is sitting up against the wall
===============
*/
static void CG_Grapple(centity_t * cent)
{
	refEntity_t ent;
	entityState_t *s1;
	const weaponInfo_t *weapon;

	s1 = &cent->currentState;
	if (s1->weapon > WP_NUM_WEAPONS) {
		s1->weapon = 0;
	}
	weapon = &cg_weapons[s1->weapon];

	// calculate the axis
	VectorCopy(s1->angles, cent->lerpAngles);

#if 0				// FIXME add grapple pull sound here..?
	// add missile sound
	if (weapon->missileSound) {
		trap_S_AddLoopingSound(cent->currentState.number, cent->lerpOrigin, vec3_origin, weapon->missileSound);
	}
#endif

	// Will draw cable if needed
//Blaze: Not needed
//      CG_GrappleTrail ( cent, weapon );

	// create the render entity
	memset(&ent, 0, sizeof(ent));
	VectorCopy(cent->lerpOrigin, ent.origin);
	VectorCopy(cent->lerpOrigin, ent.oldorigin);

	// flicker between two skins
	ent.skinNum = cg.clientFrame & 1;
	ent.hModel = weapon->missileModel;
	ent.renderfx = weapon->missileRenderfx | RF_NOSHADOW;

	// convert direction of travel into axis
	if (VectorNormalize2(s1->pos.trDelta, ent.axis[0]) == 0) {
		ent.axis[0][2] = 1;
	}

	trap_R_AddRefEntityToScene(&ent);
}

/*
===============
CG_Mover
===============
*/
static void CG_Mover(centity_t * cent)
{
	refEntity_t ent;
	entityState_t *s1;

	s1 = &cent->currentState;

	// create the render entity
	memset(&ent, 0, sizeof(ent));
	VectorCopy(cent->lerpOrigin, ent.origin);
	VectorCopy(cent->lerpOrigin, ent.oldorigin);
	AnglesToAxis(cent->lerpAngles, ent.axis);

	ent.renderfx = RF_NOSHADOW;

	// flicker between two skins (FIXME?)
	ent.skinNum = (cg.time >> 6) & 1;

	// get the model, either as a bmodel or a modelindex
	if (s1->solid == SOLID_BMODEL) {
		ent.hModel = cgs.inlineDrawModel[s1->modelindex];
	} else {
		ent.hModel = cgs.gameModels[s1->modelindex];
	}

	// add to refresh list
	trap_R_AddRefEntityToScene(&ent);

	// add the secondary model
	if (s1->modelindex2) {
		ent.skinNum = 0;
		ent.hModel = cgs.gameModels[s1->modelindex2];
		trap_R_AddRefEntityToScene(&ent);
	}

}

/*
===============
CG_Beam

Also called as an event
===============
*/
void CG_Beam(centity_t * cent)
{
	refEntity_t ent;
	entityState_t *s1;

	s1 = &cent->currentState;

	// create the render entity
	memset(&ent, 0, sizeof(ent));
	VectorCopy(s1->pos.trBase, ent.origin);
	VectorCopy(s1->origin2, ent.oldorigin);
	AxisClear(ent.axis);
	ent.reType = RT_BEAM;

	ent.renderfx = RF_NOSHADOW;

	// add to refresh list
	trap_R_AddRefEntityToScene(&ent);
}

/*
===============
CG_Portal
===============
*/
static void CG_Portal(centity_t * cent)
{
	refEntity_t ent;
	entityState_t *s1;

	s1 = &cent->currentState;

	// create the render entity
	memset(&ent, 0, sizeof(ent));
	VectorCopy(cent->lerpOrigin, ent.origin);
	VectorCopy(s1->origin2, ent.oldorigin);
	ByteToDir(s1->eventParm, ent.axis[0]);
	PerpendicularVector(ent.axis[1], ent.axis[0]);

	// negating this tends to get the directions like they want
	// we really should have a camera roll value
	VectorSubtract(vec3_origin, ent.axis[1], ent.axis[1]);

	CrossProduct(ent.axis[0], ent.axis[1], ent.axis[2]);
	ent.reType = RT_PORTALSURFACE;
	ent.oldframe = s1->powerups;
	ent.frame = s1->frame;	// rotation speed
	ent.skinNum = s1->clientNum / 256.0 * 360;	// roll offset

	// add to refresh list
	trap_R_AddRefEntityToScene(&ent);
}

/*
=========================
CG_AdjustPositionForMover

Also called by client movement prediction code
=========================
*/
void CG_AdjustPositionForMover(const vec3_t in, int moverNum, int fromTime, int toTime, vec3_t out)
{
	centity_t *cent;
	vec3_t oldOrigin, origin, deltaOrigin;
	vec3_t oldAngles, angles, deltaAngles;

	if (moverNum <= 0 || moverNum >= ENTITYNUM_MAX_NORMAL) {
		VectorCopy(in, out);
		return;
	}

	cent = &cg_entities[moverNum];
	if (cent->currentState.eType != ET_MOVER) {
		VectorCopy(in, out);
		return;
	}

	CG_EvaluateTrajectory(&cent->currentState.pos, fromTime, oldOrigin);
	CG_EvaluateTrajectory(&cent->currentState.apos, fromTime, oldAngles);

	CG_EvaluateTrajectory(&cent->currentState.pos, toTime, origin);
	CG_EvaluateTrajectory(&cent->currentState.apos, toTime, angles);

	VectorSubtract(origin, oldOrigin, deltaOrigin);
	VectorSubtract(angles, oldAngles, deltaAngles);

	VectorAdd(in, deltaOrigin, out);

	// FIXME: origin change when on a rotating object
}

/*
=============================
CG_InterpolateEntityPosition
=============================
*/
static void CG_InterpolateEntityPosition(centity_t * cent)
{
	vec3_t current, next;
	float f;

	// it would be an internal error to find an entity that interpolates without
	// a snapshot ahead of the current one
	if (cg.nextSnap == NULL) {
		CG_Error("CG_InterpolateEntityPosition: cg.nextSnap == NULL");
	}

	f = cg.frameInterpolation;

	// this will linearize a sine or parabolic curve, but it is important
	// to not extrapolate player positions if more recent data is available
	CG_EvaluateTrajectory(&cent->currentState.pos, cg.snap->serverTime, current);
	CG_EvaluateTrajectory(&cent->nextState.pos, cg.nextSnap->serverTime, next);

	cent->lerpOrigin[0] = current[0] + f * (next[0] - current[0]);
	cent->lerpOrigin[1] = current[1] + f * (next[1] - current[1]);
	cent->lerpOrigin[2] = current[2] + f * (next[2] - current[2]);

	CG_EvaluateTrajectory(&cent->currentState.apos, cg.snap->serverTime, current);
	CG_EvaluateTrajectory(&cent->nextState.apos, cg.nextSnap->serverTime, next);

	cent->lerpAngles[0] = LerpAngle(current[0], next[0], f);
	cent->lerpAngles[1] = LerpAngle(current[1], next[1], f);
	cent->lerpAngles[2] = LerpAngle(current[2], next[2], f);

}

/*
===============
CG_CalcEntityLerpPositions

===============
*/
static void CG_CalcEntityLerpPositions(centity_t * cent)
{
	// this is done server-side now - cg_smoothClients is undefined
	// players will always be TR_INTERPOLATE
	// if this player does not want to see extrapolated players
// JBravo: done serverside now via unlagged
/*	if (!cg_smoothClients.integer) {
		// make sure the clients use TR_INTERPOLATE
		if (cent->currentState.number < MAX_CLIENTS) {
			cent->currentState.pos.trType = TR_INTERPOLATE;
			cent->nextState.pos.trType = TR_INTERPOLATE;
		}
	}
*/
	if (cent->interpolate && cent->currentState.pos.trType == TR_INTERPOLATE) {
		CG_InterpolateEntityPosition(cent);
		return;
	}
	// first see if we can interpolate between two snaps for
	// linear extrapolated clients
	if (cent->interpolate && cent->currentState.pos.trType == TR_LINEAR_STOP &&
	    cent->currentState.number < MAX_CLIENTS) {
		CG_InterpolateEntityPosition(cent);
		return;
	}
// JBravo: unlagged
	if (cent->currentState.number < MAX_CLIENTS &&
			cent->currentState.clientNum != cg.predictedPlayerState.clientNum) {
		cent->currentState.pos.trType = TR_LINEAR_STOP;
		cent->currentState.pos.trTime = cg.snap->serverTime;
		cent->currentState.pos.trDuration = 1000 / sv_fps.integer;
	}

	// just use the current frame and evaluate as best we can
	CG_EvaluateTrajectory(&cent->currentState.pos, cg.time, cent->lerpOrigin);
	CG_EvaluateTrajectory(&cent->currentState.apos, cg.time, cent->lerpAngles);

	// adjust for riding a mover if it wasn't rolled into the predicted
	// player state
	if (cent != &cg.predictedPlayerEntity) {
		CG_AdjustPositionForMover(cent->lerpOrigin, cent->currentState.groundEntityNum,
					  cg.snap->serverTime, cg.time, cent->lerpOrigin);
	}
}

/*
===============
CG_TeamBase
===============
*/
static void CG_TeamBase(centity_t * cent)
{
	refEntity_t model;

	if (cgs.gametype == GT_CTF) {
		// show the flag base
		memset(&model, 0, sizeof(model));
		model.reType = RT_MODEL;
		VectorCopy(cent->lerpOrigin, model.lightingOrigin);
		VectorCopy(cent->lerpOrigin, model.origin);
		AnglesToAxis(cent->currentState.angles, model.axis);
		if (cent->currentState.modelindex == TEAM_RED) {
			model.hModel = cgs.media.redFlagBaseModel;
		} else if (cent->currentState.modelindex == TEAM_BLUE) {
			model.hModel = cgs.media.blueFlagBaseModel;
		} else {
			model.hModel = cgs.media.neutralFlagBaseModel;
		}
		trap_R_AddRefEntityToScene(&model);
	}
}

/*
===============
CG_DrawDecal	By NiceAss
===============
*/
static void CG_DrawDecal(centity_t * cent)
{
	trace_t	trace;
	vec3_t	end;
	float	alpha, radius;

	if (cgs.gametype == GT_CTF) {
		//cent->currentState.modelindex 
		
		VectorCopy(cent->lerpOrigin, end);
		end[2] -= 8192;

		alpha = sin(cg.time / 160.0f) * 0.25 + 0.75f;
		radius = 48 + (cos(cg.time / 320.0f) * 4.0f);

		// Project downward to the ground
		CG_Trace(&trace, cent->lerpOrigin, NULL, NULL, end, 0, CONTENTS_SOLID | CONTENTS_PLAYERCLIP);

		if (cent->currentState.modelindex == TEAM_RED)
			CG_ImpactMark(cgs.media.ctbXMarkSilver, trace.endpos, trace.plane.normal, 45.0f,
				      1, 1, 1, 1, qfalse, radius, qtrue);
		else
			CG_ImpactMark(cgs.media.ctbOMarkBlack, trace.endpos, trace.plane.normal, 45.0f,
				      1, 1, 1, 1, qfalse, radius, qtrue);
	}
}
/*
===============
CG_AddCEntity

===============
*/
static void CG_AddCEntity(centity_t * cent)
{
	// event-only entities will have been dealt with already
	if (cent->currentState.eType >= ET_EVENTS) {
		return;
	}
	// calculate the current origin
	CG_CalcEntityLerpPositions(cent);

	// add automatic effects
	CG_EntityEffects(cent);

	switch (cent->currentState.eType) {
	default:
		CG_Error("Bad entity type: %i\n", cent->currentState.eType);
		break;
	case ET_INVISIBLE:
	case ET_PUSH_TRIGGER:
	case ET_TELEPORT_TRIGGER:
		break;
	case ET_GENERAL:
		CG_General(cent);
		break;
	case ET_PLAYER:
		CG_Player(cent);
		break;
	case ET_ITEM:
		CG_Item(cent);
		break;
	case ET_MISSILE:
		CG_Missile(cent);
		break;
	case ET_MOVER:
		CG_Mover(cent);
		break;
	case ET_BREAKABLE:
		CG_Mover(cent);
		break;
	case ET_PRESSURE:
		CG_Mover(cent);
		break;
	case ET_BEAM:
		CG_Beam(cent);
		break;
	case ET_PORTAL:
		CG_Portal(cent);
		break;
	case ET_SPEAKER:
		CG_Speaker(cent);
		break;
	case ET_GRAPPLE:
		CG_Grapple(cent);
		break;
	case ET_TEAM:
		CG_TeamBase(cent);
		break;
	case ET_DECAL:
		CG_DrawDecal(cent);
		break;
	case ET_LASER:
		//Elder: the local laser call is checked in playerstate unless it is disabled
		//if (!cg_RQ3_laserAssist.integer || cent->currentState.clientNum != cg.snap->ps.clientNum)
		CG_LaserSight(cent);
		break;
	case ET_DLIGHT:
		CG_Dlight(cent);
		break;
	}
}

/*
===============
CG_AddPacketEntities

Makro - added skyportal param
===============
*/
void CG_AddPacketEntities(int mode)
{
	centity_t *cent;
	int num;

	//Makro - if we're rendering the entities in a sky portals, we don't need this stuff
	if (mode != 1) {
		playerState_t *ps;

		// set cg.frameInterpolation
		if (cg.nextSnap) {
			int delta;

			delta = (cg.nextSnap->serverTime - cg.snap->serverTime);
			if (delta == 0) {
				cg.frameInterpolation = 0;
			} else {
				cg.frameInterpolation = (float) (cg.time - cg.snap->serverTime) / delta;
			}
		} else {
			cg.frameInterpolation = 0;	// actually, it should never be used, because
			// no entities should be marked as interpolating
		}

		// the auto-rotating items will all have the same axis
		cg.autoAngles[0] = 0;
		cg.autoAngles[1] = 0;	//Blaze: changed this ( cg.time & 2047 ) * 360 / 2048.0; to 0;
		cg.autoAngles[2] = 0;
	
		cg.autoAnglesFast[0] = 0;
		//Elder: restored for weapon rotation
		cg.autoAnglesFast[1] = (cg.time & 1023) * 360 / 1024.0f;
		cg.autoAnglesFast[2] = 0;

		AnglesToAxis(cg.autoAngles, cg.autoAxis);
		AnglesToAxis(cg.autoAnglesFast, cg.autoAxisFast);

		// generate and add the entity from the playerstate
		ps = &cg.predictedPlayerState;
		BG_PlayerStateToEntityState(ps, &cg.predictedPlayerEntity.currentState, qfalse);
		CG_AddCEntity(&cg.predictedPlayerEntity);

		// lerp the non-predicted value for lightning gun origins
		CG_CalcEntityLerpPositions(&cg_entities[cg.snap->ps.clientNum]);
// JBravo: unlagged
		if (cg.nextSnap) {
			for (num = 0 ; num < cg.nextSnap->numEntities ; num++) {
				cent = &cg_entities[cg.nextSnap->entities[num].number];
				if (cent->nextState.eType == ET_MISSILE || cent->nextState.eType == ET_GENERAL) {
					CG_TransitionEntity(cent);
					cent->interpolate = qtrue;
					CG_AddCEntity(cent);
				}
			}
		}
	}

	if (mode != -1) {
		// add each entity sent over by the server
		for (num = 0; num < cg.snap->numEntities; num++) {
			cent = &cg_entities[cg.snap->entities[num].number];
			if (mode == 1) {
				if (cent->currentState.eFlags & EF_HEADLESS) {
					CG_AddCEntity(cent);
				}
			} else {
				if (!(cent->currentState.eFlags & EF_HEADLESS) || cent->currentState.eType == ET_PLAYER) {
					CG_AddCEntity(cent);
				}
			}
		}

	} else {
		for (num = 0; num < cg.snap->numEntities; num++) {
			cent = &cg_entities[cg.snap->entities[num].number];
			if (!cg.nextSnap || (cent->nextState.eType != ET_MISSILE && cent->nextState.eType != ET_GENERAL)) {
				CG_AddCEntity(cent);
			}
		}
	}
}

/*
==================
CG_LaserSight

Creates the laser dot
Elder's Note: Client does not use this if the dot is his/her own -- see CG_LocalLaser
NiceAss's Note: Lies?! It seems to for me =P I don't even think CG_LocalLaser gets called...
==================
*/

static void CG_LaserSight(centity_t * cent)
{
	refEntity_t ent;

	// create the reference entity
	memset(&ent, 0, sizeof(ent));

	VectorCopy(cent->lerpOrigin, ent.origin);
	VectorCopy(cent->lerpOrigin, ent.oldorigin);

	if (cent->currentState.eventParm == 1) {
		ent.reType = RT_SPRITE;
		ent.radius = 3;
		ent.rotation = 0;
		ent.customShader = cgs.media.laserShader;

		// NiceAss: If it's your laser dot, draw it
		// or if not in the fog and not your laser dot draw it
		if ( ( cent->currentState.clientNum == cg.clientNum || 
			(!(trap_CM_PointContents(cent->lerpOrigin, 0) & CONTENTS_FOG) && 
			cent->currentState.clientNum != cg.clientNum) ) &&	
			cg_enableLaserFog.integer )
			trap_R_AddRefEntityToScene(&ent);
	} else {
		trap_R_AddLightToScene(ent.origin, 200, 1, 1, 1);
	}
}

/*
=================
CG_Dlight
Added by Elder.

Use sparingly.
=================
*/
static void CG_Dlight(centity_t * cent)
{
	//Makro - kinda hackish, but oh well...
	//allows us to trigger them on off; SVF_NOCLIENT should've done this already, though
	if (!(cent->currentState.eFlags & EF_NODRAW)) {
		int cl;
		float i, r, g, b, i2;

		cl = cent->currentState.constantLight;
		r = (cl & 255) / 255.0f;
		g = ((cl >> 8) & 255) / 255.0f;
		b = ((cl >> 16) & 255) / 255.0f;
		i = ((cl >> 24) & 255) * 8;
		i2 = cent->currentState.weapon;

		if (cent->currentState.eventParm & DLIGHT_FLICKER)
			i += random() * (i2-i);

		if (cent->currentState.eventParm & DLIGHT_PULSE)
		{
			float frequency = cent->currentState.powerups / 1000.0f;
			float phase = 2 * M_PI * (frequency * cg.time / 1000.0f + cent->currentState.otherEntityNum2 / 1000.0f);
			//CG_Printf("cgame: (%f %f %f) %f -> %f = ", r, g, b, i, i2);
			i += (sin(phase) + 1) * (i2-i) / 2.0f;
			//CG_Printf("%f\n", i);
		}

		if (cent->currentState.eventParm & DLIGHT_ADDITIVE)
			trap_R_AddAdditiveLightToScene(cent->lerpOrigin, i, r, g, b);
		else
			trap_R_AddLightToScene(cent->lerpOrigin, i, r, g, b);
		//trap_R_AddLightToScene(cent->lerpOrigin, 500, 1, 1, 1);

		//CG_Printf("cgame: (%f %f %f)\n", cent->lerpOrigin[0], cent->lerpOrigin[1], cent->lerpOrigin[2]);
	}
}
