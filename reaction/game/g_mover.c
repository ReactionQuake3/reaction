//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.44  2002/06/09 06:30:59  blaze
// some changes to the default sounds on doors.
//
// Revision 1.43  2002/05/30 21:18:28  makro
// Bots should reload/bandage when roaming around
// Added "pathtarget" key to all the entities
//
// Revision 1.42  2002/05/29 19:49:21  makro
// Option to disable spectator triggers for doors
//
// Revision 1.41  2002/05/29 13:49:25  makro
// Elevators/doors
//
// Revision 1.40  2002/05/27 06:51:54  niceass
// FIXED SPELLING MISTACK
//
// Revision 1.39  2002/05/24 18:42:35  makro
// Elevator stuff
//
// Revision 1.38  2002/05/23 18:37:50  makro
// Bots should crouch more often when they attack with a SSG
// Made this depend on skill. Also, elevator stuff
//
// Revision 1.37  2002/05/23 15:55:25  makro
// Elevators
//
// Revision 1.36  2002/05/23 05:13:44  blaze
// More sound changes as per Sze, please dont kill me Cent
//
// Revision 1.35  2002/05/23 04:58:05  blaze
// More sound changes as per Sze, please dont kill me Cent
//
// Revision 1.34  2002/05/22 04:20:37  blaze
// Sound entity changes as per Sze - teach me to comit when Sze is still talking
//
// Revision 1.33  2002/05/22 04:19:22  blaze
// Sound entity changes as per Sze - more
//
// Revision 1.32  2002/05/22 04:17:18  blaze
// Sound entity changes as per Sze
//
// Revision 1.31  2002/05/16 06:57:54  makro
// Doors with health (again !), bot-only trigger_pushes
//
// Revision 1.30  2002/05/15 12:46:32  makro
// Small func_static change.Give ammo should now give grenades/knives
//
// Revision 1.29  2002/05/13 04:41:26  makro
// Bug with doors (mine !)
//
// Revision 1.28  2002/05/11 12:45:25  makro
// Spectators can go through breakables and doors with
// a targetname or health. Bots should crouch more/jump less
// often when attacking at long range
//
// Revision 1.27  2002/05/11 00:38:47  blaze
// trigger_push and target_push default to no noise when the noise flag is not set.
//
// Revision 1.26  2002/05/05 15:18:02  makro
// Fixed some crash bugs. Bot stuff. Triggerable func_statics.
// Made flags only spawn in CTF mode
//
// Revision 1.25  2002/04/03 15:51:01  jbravo
// Small warning fixes
//
// Revision 1.24  2002/04/03 03:13:16  blaze
// NEW BREAKABLE CODE - will break all old breakables(wont appear in maps)
//
// Revision 1.23  2002/03/31 03:31:24  jbravo
// Compiler warning cleanups
//
// Revision 1.22  2002/03/21 04:27:53  blaze
// more func_explosive goodness
//
// Revision 1.21  2002/01/31 02:50:18  blaze
// some basic work on the trains/elevators
//
// Revision 1.20  2002/01/24 14:20:53  jbravo
// Adding func_explosive and a few new surfaceparms
//
// Revision 1.19  2002/01/14 01:20:44  niceass
// No more default 800 gravity on items
// Thrown knife+Glass fix - NiceAss
//
// Revision 1.18  2002/01/11 19:48:30  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.17  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//

#include "g_local.h"
void InitRotator( gentity_t *ent );


/*
===============================================================================

PUSHMOVE

===============================================================================
*/

void MatchTeam( gentity_t *teamLeader, int moverState, int time );

typedef struct {
	gentity_t	*ent;
	vec3_t	origin;
	vec3_t	angles;
	float	deltayaw;
} pushed_t;
pushed_t	pushed[MAX_GENTITIES], *pushed_p;


/*
============
G_TestEntityPosition

============
*/
gentity_t	*G_TestEntityPosition( gentity_t *ent ) {
	trace_t	tr;
	int		mask;
//	vec3_t		origin2;

	if ( ent->clipmask ) {
		mask = ent->clipmask;
	} else {
		mask = MASK_SOLID;
	}
	if ( ent->client ) {
		//VectorCopy(ent->client->ps.origin,origin2);
		//origin2[2] +=200;
		trap_Trace( &tr, ent->client->ps.origin, ent->r.mins, ent->r.maxs, ent->client->ps.origin, ent->s.number, mask );
	} else {
		trap_Trace( &tr, ent->s.pos.trBase, ent->r.mins, ent->r.maxs, ent->s.pos.trBase, ent->s.number, mask );
	}

	if (tr.startsolid)
	{
		//Com_Printf("startsolid\n");
		return &g_entities[ tr.entityNum ];
	}
	return NULL;
}

/*
================
G_CreateRotationMatrix
================
*/
void G_CreateRotationMatrix(vec3_t angles, vec3_t matrix[3]) {
	AngleVectors(angles, matrix[0], matrix[1], matrix[2]);
	VectorInverse(matrix[1]);
}

/*
================
G_TransposeMatrix
================
*/
void G_TransposeMatrix(vec3_t matrix[3], vec3_t transpose[3]) {
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			transpose[i][j] = matrix[j][i];
		}
	}
}

/*
================
G_RotatePoint
================
*/
void G_RotatePoint(vec3_t point, vec3_t matrix[3]) {
	vec3_t tvec;

	VectorCopy(point, tvec);
	point[0] = DotProduct(matrix[0], tvec);
	point[1] = DotProduct(matrix[1], tvec);
	point[2] = DotProduct(matrix[2], tvec);
}

/*
==================
G_TryPushingEntity

Returns qfalse if the move is blocked
==================
*/
qboolean	G_TryPushingEntity( gentity_t *check, gentity_t *pusher, vec3_t move, vec3_t amove ) {
	vec3_t		matrix[3], transpose[3];
	vec3_t		org, org2, move2;
	gentity_t	*block;

	// EF_MOVER_STOP will just stop when contacting another entity
	// instead of pushing it, but entities can still ride on top of it
	if ( ( pusher->s.eFlags & EF_MOVER_STOP ) &&
		check->s.groundEntityNum != pusher->s.number ) {
		return qfalse;
	}

	// save off the old position
	if (pushed_p > &pushed[MAX_GENTITIES]) {
		G_Error( "pushed_p > &pushed[MAX_GENTITIES]" );
	}
	pushed_p->ent = check;
	VectorCopy (check->s.pos.trBase, pushed_p->origin);
	VectorCopy (check->s.apos.trBase, pushed_p->angles);
	if ( check->client ) {
		pushed_p->deltayaw = check->client->ps.delta_angles[YAW];
		VectorCopy (check->client->ps.origin, pushed_p->origin);
	}
	pushed_p++;

	// try moving the contacted entity
	// figure movement due to the pusher's amove
	G_CreateRotationMatrix( amove, transpose );
	G_TransposeMatrix( transpose, matrix );
	if (check->client) {
		VectorSubtract (check->client->ps.origin, pusher->r.currentOrigin, org);
	}
	else {
		VectorSubtract (check->s.pos.trBase, pusher->r.currentOrigin, org);
	}
	VectorCopy( org, org2 );
	G_RotatePoint( org2, matrix );
	VectorSubtract (org2, org, move2);
	// add movement
	VectorAdd (check->s.pos.trBase, move, check->s.pos.trBase);
	VectorAdd (check->s.pos.trBase, move2, check->s.pos.trBase);
	if ( check->client ) {
		VectorAdd (check->client->ps.origin, move, check->client->ps.origin);
		VectorAdd (check->client->ps.origin, move2, check->client->ps.origin);
		// make sure the client's view rotates when on a rotating mover
		check->client->ps.delta_angles[YAW] += ANGLE2SHORT(amove[YAW]);
	}

	// may have pushed them off an edge
	if ( check->s.groundEntityNum != pusher->s.number ) {
		check->s.groundEntityNum = -1;
	}

	block = G_TestEntityPosition( check );
	if (!block) {
		// pushed ok

		if ( check->client ) {
			VectorCopy( check->client->ps.origin, check->r.currentOrigin );
		} else {
			VectorCopy( check->s.pos.trBase, check->r.currentOrigin );
		}
		trap_LinkEntity (check);
		return qtrue;
	}

	// if it is ok to leave in the old position, do it
	// this is only relevent for riding entities, not pushed
	// Sliding trapdoors can cause this.
	VectorCopy( (pushed_p-1)->origin, check->s.pos.trBase);
	if ( check->client ) {
		VectorCopy( (pushed_p-1)->origin, check->client->ps.origin);
	}
	VectorCopy( (pushed_p-1)->angles, check->s.apos.trBase );
	block = G_TestEntityPosition (check);
	if ( !block ) {
		check->s.groundEntityNum = -1;
		pushed_p--;
		return qtrue;
	}

	// blocked
	return qfalse;
}

/*
==================
G_CheckProxMinePosition
==================
*/
qboolean G_CheckProxMinePosition( gentity_t *check ) {
	vec3_t		start, end;
	trace_t	tr;

	VectorMA(check->s.pos.trBase, 0.125, check->movedir, start);
	VectorMA(check->s.pos.trBase, 2, check->movedir, end);
	trap_Trace( &tr, start, NULL, NULL, end, check->s.number, MASK_SOLID );

	if (tr.startsolid || tr.fraction < 1)
		return qfalse;

	return qtrue;
}

/*
==================
G_TryPushingProxMine
==================
*/
qboolean G_TryPushingProxMine( gentity_t *check, gentity_t *pusher, vec3_t move, vec3_t amove ) {
	vec3_t		forward, right, up;
	vec3_t		org, org2, move2;
	int ret;

	// we need this for pushing things later
	VectorSubtract (vec3_origin, amove, org);
	AngleVectors (org, forward, right, up);

	// try moving the contacted entity
	VectorAdd (check->s.pos.trBase, move, check->s.pos.trBase);

	// figure movement due to the pusher's amove
	VectorSubtract (check->s.pos.trBase, pusher->r.currentOrigin, org);
	org2[0] = DotProduct (org, forward);
	org2[1] = -DotProduct (org, right);
	org2[2] = DotProduct (org, up);
	VectorSubtract (org2, org, move2);
	VectorAdd (check->s.pos.trBase, move2, check->s.pos.trBase);

	ret = G_CheckProxMinePosition( check );
	if (ret) {
		VectorCopy( check->s.pos.trBase, check->r.currentOrigin );
		trap_LinkEntity (check);
	}
	return ret;
}

void G_ExplodeMissile( gentity_t *ent );

/*
============
G_MoverPush

Objects need to be moved back on a failed push,
otherwise riders would continue to slide.
If qfalse is returned, *obstacle will be the blocking entity
============
*/
qboolean G_MoverPush( gentity_t *pusher, vec3_t move, vec3_t amove, gentity_t **obstacle ) {
	int			i, e;
	gentity_t	*check;
	vec3_t		mins, maxs;
	pushed_t	*p;
	int			entityList[MAX_GENTITIES];
	int			listedEntities;
	float			deltaTime;
	float		phase;
	vec3_t		totalMins, totalMaxs;

	*obstacle = NULL;


	// mins/maxs are the bounds at the destination
	// totalMins / totalMaxs are the bounds for the entire move
	if ( pusher->r.currentAngles[0] || pusher->r.currentAngles[1] || pusher->r.currentAngles[2]
		|| amove[0] || amove[1] || amove[2] ) {
		float		radius;

		radius = RadiusFromBounds( pusher->r.mins, pusher->r.maxs );
		for ( i = 0 ; i < 3 ; i++ ) {
			mins[i] = pusher->r.currentOrigin[i] + move[i] - radius;
			maxs[i] = pusher->r.currentOrigin[i] + move[i] + radius;
			totalMins[i] = mins[i] - move[i];
			totalMaxs[i] = maxs[i] - move[i];
		}
	} else {
		for (i=0 ; i<3 ; i++) {
			mins[i] = pusher->r.absmin[i] + move[i];
			maxs[i] = pusher->r.absmax[i] + move[i];
		}

		VectorCopy( pusher->r.absmin, totalMins );
		VectorCopy( pusher->r.absmax, totalMaxs );
		for (i=0 ; i<3 ; i++) {
			if ( move[i] > 0 ) {
				totalMaxs[i] += move[i];
			} else {
				totalMins[i] += move[i];
			}
		}
	}

	// unlink the pusher so we don't get it in the entityList
	trap_UnlinkEntity( pusher );

	listedEntities = trap_EntitiesInBox( totalMins, totalMaxs, entityList, MAX_GENTITIES );

	// move the pusher to it's final position
	VectorAdd( pusher->r.currentOrigin, move, pusher->r.currentOrigin );
	VectorAdd( pusher->r.currentAngles, amove, pusher->r.currentAngles );
	trap_LinkEntity( pusher );

	// see if any solid entities are inside the final position
	for ( e = 0 ; e < listedEntities ; e++ ) {
		check = &g_entities[ entityList[ e ] ];

#ifdef MISSIONPACK
		if ( check->s.eType == ET_MISSILE ) {
			// if it is a prox mine
			if ( !strcmp(check->classname, "prox mine") ) {
				// if this prox mine is attached to this mover try to move it with the pusher
				if ( check->enemy == pusher ) {
					if (!G_TryPushingProxMine( check, pusher, move, amove )) {
						//explode
						check->s.loopSound = 0;
						G_AddEvent( check, EV_PROXIMITY_MINE_TRIGGER, 0 );
						G_ExplodeMissile(check);
						if (check->activator) {
							G_FreeEntity(check->activator);
							check->activator = NULL;
						}
						//G_Printf("prox mine explodes\n");
					}
				}
				else {
					//check if the prox mine is crushed by the mover
					if (!G_CheckProxMinePosition( check )) {
						//explode
						check->s.loopSound = 0;
						G_AddEvent( check, EV_PROXIMITY_MINE_TRIGGER, 0 );
						G_ExplodeMissile(check);
						if (check->activator) {
							G_FreeEntity(check->activator);
							check->activator = NULL;
						}
						//G_Printf("prox mine explodes\n");
					}
				}
				continue;
			}
		}
#endif
		// only push items and players
		if ( check->s.eType != ET_ITEM && check->s.eType != ET_PLAYER && !check->physicsObject ) {
			continue;
		}

		// if the entity is standing on the pusher, it will definitely be moved
		if ( check->s.groundEntityNum != pusher->s.number ) {
			// see if the ent needs to be tested
			if ( check->r.absmin[0] >= maxs[0]
			|| check->r.absmin[1] >= maxs[1]
			|| check->r.absmin[2] >= maxs[2]
			|| check->r.absmax[0] <= mins[0]
			|| check->r.absmax[1] <= mins[1]
			|| check->r.absmax[2] <= mins[2]) {
			//	Com_Printf("No Test\n");
				continue;
			}
			// see if the ent's bbox is inside the pusher's final position
			// this does allow a fast moving object to pass through a thin entity...

			if (!G_TestEntityPosition (check)) {
				continue;
			}



		}

		// the entity needs to be pushed
		if ( G_TryPushingEntity( check, pusher, move, amove ) ) {
			continue;
		}

		// the move was blocked an entity

		// bobbing entities are instant-kill and never get blocked
		//Elder: Pendulum killer code - commented out for now
		//But it has to PUSH the client off... I don't know how just yet :(
		if ( pusher->s.pos.trType == TR_SINE || pusher->s.apos.trType == TR_SINE ) {
			//Elder: debug code
			//G_Printf("RQ3: TR_SINE crusher code removed\n");
			for ( p=pushed_p-1 ; p>=pushed ; p-- ) {
				VectorCopy (p->origin, p->ent->s.pos.trBase);
				VectorCopy (p->angles, p->ent->s.apos.trBase);
				if ( p->ent->client ) {
					//trBase[1] = angle it swings at, delta[2] = speed
					//Com_Printf("(%d)(%f)(%f)\n",pusher->s.apos.trDuration[0],pusher->s.apos.trDuration[1],pusher->s.apos.trDuration[2]);
					deltaTime = (level.time - pusher->s.apos.trTime ) / (float) pusher->s.apos.trDuration;
					phase = sin( deltaTime * M_PI * 2 );
					if (phase <0)
					{
						p->ent->client->ps.origin[1]+=abs((int)(10*cos(pusher->s.apos.trBase[1])));
						p->ent->client->ps.origin[0]+=abs((int)(10*sin(pusher->s.apos.trBase[1])));
					}
					if (phase >=0)
					{
						p->ent->client->ps.origin[1]-=abs((int)(10*cos(pusher->s.apos.trBase[1])));
						p->ent->client->ps.origin[0]-=abs((int)(10*sin(pusher->s.apos.trBase[1])));
					}
					p->ent->client->ps.delta_angles[YAW] = p->deltayaw;
					//VectorCopy (p->origin, p->ent->client->ps.origin);
				}
//				trap_LinkEntity (p->ent);
			}
		//	return qfalse;
		continue;
			//Elder: temp - player will stop the pendulum from going
			//Elder: removed qfalse and continue
			//return qfalse;
			//G_Damage( check, pusher, pusher, NULL, NULL, 99999, 0, MOD_CRUSH );
			//continue;
		}


		// save off the obstacle so we can call the block function (crush, etc)
		*obstacle = check;

		// move back any entities we already moved
		// go backwards, so if the same entity was pushed
		// twice, it goes back to the original position
		for ( p=pushed_p-1 ; p>=pushed ; p-- ) {
			VectorCopy (p->origin, p->ent->s.pos.trBase);
			VectorCopy (p->angles, p->ent->s.apos.trBase);
			if ( p->ent->client ) {
				p->ent->client->ps.delta_angles[YAW] = p->deltayaw;
				VectorCopy (p->origin, p->ent->client->ps.origin);
			}
			trap_LinkEntity (p->ent);
		}
		return qfalse;
	}

	return qtrue;
}


/*
=================
G_MoverTeam
=================
*/
void G_MoverTeam( gentity_t *ent ) {
	vec3_t		move, amove;
	gentity_t	*part, *obstacle;
	vec3_t		origin, angles;

	obstacle = NULL;

	// make sure all team slaves can move before commiting
	// any moves or calling any think functions
	// if the move is blocked, all moved objects will be backed out
	pushed_p = pushed;
	for (part = ent ; part ; part=part->teamchain) {
		// get current position
		G_EvaluateTrajectory( &part->s.pos, level.time, origin );
		G_EvaluateTrajectory( &part->s.apos, level.time, angles );
		VectorSubtract( origin, part->r.currentOrigin, move );
		VectorSubtract( angles, part->r.currentAngles, amove );
		if ( !G_MoverPush( part, move, amove, &obstacle ) ) {
			break;	// move was blocked
		}
	}

	if (part) {
		// go back to the previous position
		for ( part = ent ; part ; part = part->teamchain ) {
			part->s.pos.trTime += level.time - level.previousTime;
			part->s.apos.trTime += level.time - level.previousTime;
			G_EvaluateTrajectory( &part->s.pos, level.time, part->r.currentOrigin );
			G_EvaluateTrajectory( &part->s.apos, level.time, part->r.currentAngles );
			trap_LinkEntity( part );
		}

		// if the pusher has a "blocked" function, call it
		if (ent->blocked) {
			ent->blocked( ent, obstacle );
		}
		return;
	}

	// the move succeeded
	for ( part = ent ; part ; part = part->teamchain ) {
		// call the reached function if time is at or past end point
		if ( part->s.pos.trType == TR_LINEAR_STOP ) {
			if ( level.time >= part->s.pos.trTime + part->s.pos.trDuration ) {
				if ( part->reached ) {
					part->reached( part );
				}
			}
		}
		if ( part->s.apos.trType == TR_LINEAR_STOP ) {
			if ( level.time >= part->s.apos.trTime + part->s.apos.trDuration ) {
				if ( part->reached ) {
					part->reached( part );
				}
			}
		}

	}
}

/*
================
G_RunMover

================
*/
void G_RunMover( gentity_t *ent ) {
	// if not a team captain, don't do anything, because
	// the captain will handle everything
	if ( ent->flags & FL_TEAMSLAVE ) {
		return;
	}

	// if stationary at one of the positions, don't move anything
	if ( ent->s.pos.trType != TR_STATIONARY || ent->s.apos.trType != TR_STATIONARY ) {
		G_MoverTeam( ent );
	}

	// check think function
	G_RunThink( ent );
}

/*
============================================================================

GENERAL MOVERS

Doors, plats, and buttons are all binary (two position) movers
Pos1 is "at rest", pos2 is "activated"
============================================================================
*/

/*
===============
SetMoverState
===============
*/
void SetMoverState( gentity_t *ent, moverState_t moverState, int time ) {
	vec3_t			delta;
	float			f;

	ent->moverState = moverState;

	ent->s.pos.trTime = time;
	ent->s.apos.trTime = time;					// Reaction	rotating doors

	switch( moverState ) {
	case MOVER_POS1:
		VectorCopy( ent->pos1, ent->s.pos.trBase );
		ent->s.pos.trType = TR_STATIONARY;
		break;
	case MOVER_POS2:
		VectorCopy( ent->pos2, ent->s.pos.trBase );
		ent->s.pos.trType = TR_STATIONARY;
		break;
	case MOVER_1TO2:
		VectorCopy( ent->pos1, ent->s.pos.trBase );
		VectorSubtract( ent->pos2, ent->pos1, delta );
		f = 1000.0 / ent->s.pos.trDuration;
		VectorScale( delta, f, ent->s.pos.trDelta );
		ent->s.pos.trType = TR_LINEAR_STOP;
		break;
	case MOVER_2TO1:
		VectorCopy( ent->pos2, ent->s.pos.trBase );
		VectorSubtract( ent->pos1, ent->pos2, delta );
		f = 1000.0 / ent->s.pos.trDuration;
		VectorScale( delta, f, ent->s.pos.trDelta );
		ent->s.pos.trType = TR_LINEAR_STOP;
		break;
	case ROTATOR_POS1:
		VectorCopy( ent->pos1, ent->s.apos.trBase );
		ent->s.apos.trType = TR_STATIONARY;
		break;
	case ROTATOR_POS2:
		VectorCopy( ent->pos2, ent->s.apos.trBase );
		ent->s.apos.trType = TR_STATIONARY;
		break;
	case ROTATOR_1TO2:
		VectorCopy( ent->pos1, ent->s.apos.trBase );
		VectorSubtract( ent->pos2, ent->pos1, delta );
		f = 1000.0 / ent->s.apos.trDuration;
		VectorScale( delta, f, ent->s.apos.trDelta );
		ent->s.apos.trType = TR_LINEAR_STOP;
		break;
	case ROTATOR_2TO1:
		VectorCopy( ent->pos2, ent->s.apos.trBase );
		VectorSubtract( ent->pos1, ent->pos2, delta );
		f = 1000.0 / ent->s.apos.trDuration;
		VectorScale( delta, f, ent->s.apos.trDelta );
		ent->s.apos.trType = TR_LINEAR_STOP;
		break;
	}
	G_EvaluateTrajectory( &ent->s.pos, level.time, ent->r.currentOrigin );
	G_EvaluateTrajectory( &ent->s.apos, level.time, ent->r.currentAngles );

	trap_LinkEntity( ent );
}

/*
================
MatchTeam

All entities in a mover team will move from pos1 to pos2
in the same amount of time
================
*/
void MatchTeam( gentity_t *teamLeader, int moverState, int time ) {
	gentity_t		*slave;

	for ( slave = teamLeader ; slave ; slave = slave->teamchain ) {
		SetMoverState( slave, moverState, time );
	}
}



/*
================
ReturnToPos1
================
*/
void ReturnToPos1( gentity_t *ent ) {
	MatchTeam( ent, MOVER_2TO1, level.time );

	// looping sound
	ent->s.loopSound = ent->soundLoop;

	// starting sound
	if ( ent->sound2to1 ) {
		G_AddEvent( ent, EV_GENERAL_SOUND, ent->sound2to1 );
	}
}


// Reaction
/*
================
ReturnToApos1
================
*/
void ReturnToApos1( gentity_t *ent ) {
	MatchTeam( ent, ROTATOR_2TO1, level.time );

	// looping sound
	ent->s.loopSound = ent->soundLoop;

	// starting sound
	if ( ent->sound2to1 ) {
		G_AddEvent( ent, EV_GENERAL_SOUND, ent->sound2to1 );
	}
}


/*
================
Reached_BinaryMover
================
*/
void Reached_BinaryMover( gentity_t *ent ) {

	// stop the looping sound
	ent->s.loopSound = ent->soundLoop;

	if ( ent->moverState == MOVER_1TO2 ) {
		// reached pos2
		SetMoverState( ent, MOVER_POS2, level.time );

		// play sound
		if ( ent->soundPos2 ) {
			G_AddEvent( ent, EV_GENERAL_SOUND, ent->soundPos2 );
		}

		//Elder: added toggle bit
		//Also added "touch" and "takedamage" check so we are only abusing doors
		if ( (ent->spawnflags & SP_DOORTOGGLE) == SP_DOORTOGGLE ) { //||
			//ent->touch || (ent->takedamage == qtrue) ) {
			//G_Printf("Sliding Toggle Door used\n");
		}
		else {
			// return to pos1 after a delay
			ent->think = ReturnToPos1;
			ent->nextthink = level.time + ent->wait;
		}

		// fire targets
		if ( !ent->activator ) {
			ent->activator = ent;
		}
		G_UseTargets( ent, ent->activator );

	} else if ( ent->moverState == MOVER_2TO1 ) {
		// reached pos1
		SetMoverState( ent, MOVER_POS1, level.time );

		// play sound
		if ( ent->soundPos1 ) {
			G_AddEvent( ent, EV_GENERAL_SOUND, ent->soundPos1 );
		}

		// close areaportals
		if ( ent->teammaster == ent || !ent->teammaster) {
			trap_AdjustAreaPortalState( ent, qfalse );
		}

	} else if ( ent->moverState == ROTATOR_1TO2 ) {			// Reaction
		// reached pos2
		SetMoverState( ent, ROTATOR_POS2, level.time );

		// play sound
		if ( ent->soundPos2 ) {
			G_AddEvent( ent, EV_GENERAL_SOUND, ent->soundPos2 );
		}

		//Elder: added toggle bit
		//Also added "touch" and "takedamage" check so we are only abusing doors
		//if ( ( (ent->spawnflags & SP_NODOORTOGGLE) == SP_NODOORTOGGLE ) ||
		if ( (ent->spawnflags & SP_DOORTOGGLE) == SP_DOORTOGGLE ) { //||
			//ent->touch || (ent->takedamage == qtrue) ) {
			//G_Printf("Rotating Toggle Door used\n");
		}
		else {
			// return to apos1 after a delay
			ent->think = ReturnToApos1;
			ent->nextthink = level.time + ent->wait;
		}

		// fire targets
		if ( !ent->activator ) {
			ent->activator = ent;
		}
		G_UseTargets( ent, ent->activator );
	} else if ( ent->moverState == ROTATOR_2TO1 ) {
		// reached pos1
		SetMoverState( ent, ROTATOR_POS1, level.time );

		// play sound
		if ( ent->soundPos1 ) {
			G_AddEvent( ent, EV_GENERAL_SOUND, ent->soundPos1 );
		}

		// close areaportals
		if ( ent->teammaster == ent || !ent->teammaster ) {
			trap_AdjustAreaPortalState( ent, qfalse );
		}
	} else {
		G_Error( "Reached_BinaryMover: bad moverState" );
	}
}


/*
================
Use_BinaryMover
================
*/
void Use_BinaryMover( gentity_t *ent, gentity_t *other, gentity_t *activator ) {
	int		total;
	int		partial;
	/* Makro - trains have a custom use function now
	//Blaze: Holds the train entity
	gentity_t *temp;
	if ( ent->pathtarget != NULL )
	{
		//G_Printf("The pathtarget is %s\n",ent->pathtarget);
		temp = NULL;
		temp = G_Find(temp,FOFS(targetname),ent->target);
		if ( !temp )
		{
			G_Printf("Could not find the train %s that button points to\n", ent->target);
		}
		else
		{
			temp->nextTrain = G_Find(NULL, FOFS(targetname),ent->pathtarget);
			//Blaze
			//G_Printf("^2pathtarget: %s target: %s targetname: %s\n",ent->pathtarget, ent->target, ent->targetname);
			//G_Printf("^2%s\n", ent->nextTrain->targetname);
		}
	}
	*/

	// only the master should be used
	if ( ent->flags & FL_TEAMSLAVE ) {
		Use_BinaryMover( ent->teammaster, other, activator );
		return;
	}

	ent->activator = activator;

	if ( ent->moverState == MOVER_POS1 ) {
		// start moving 50 msec later, becase if this was player
		// triggered, level.time hasn't been advanced yet
		MatchTeam( ent, MOVER_1TO2, level.time + 50 );

		// starting sound
		if ( ent->sound1to2 ) {
			G_AddEvent( ent, EV_GENERAL_SOUND, ent->sound1to2 );
		}

		// looping sound
		ent->s.loopSound = ent->soundLoop;

		// open areaportal
		if ( ent->teammaster == ent || !ent->teammaster ) {
			trap_AdjustAreaPortalState( ent, qtrue );
		}
		return;
	}

	// if all the way up, just delay before coming down
	if ( ent->moverState == MOVER_POS2 ) {
		//Elder: added two additional checks
		if ( (ent->spawnflags & SP_DOORTOGGLE) == SP_DOORTOGGLE ) {
		//if ( ( (ent->spawnflags & SP_NODOORTOGGLE) == SP_NODOORTOGGLE ) ||
			//ent->touch || ent->takedamage) {
		//Elder: Move back "immediately"
			MatchTeam( ent, MOVER_2TO1, level.time + 50);
			if ( ent->sound1to2 ) {
				G_AddEvent( ent, EV_GENERAL_SOUND, ent->sound1to2 );
			}
		}
		else {
			//Elder: normal Q3 door
			ent->nextthink = level.time + ent->wait;
		}
		return;
	}

	// only partway down before reversing
	if ( ent->moverState == MOVER_2TO1 ) {
		//Elder: don't interrupt if auto-opening
		if ( (ent->spawnflags & SP_AUTOOPEN) == SP_AUTOOPEN)
			return;

		total = ent->s.pos.trDuration;
		partial = level.time - ent->s.pos.trTime;
		if ( partial > total ) {
			partial = total;
		}
		//if ( (ent->spawnflags & SP_NODOORTOGGLE) == SP_NODOORTOGGLE) {
			//Elder: normal Q3 door and Toggle Door work identically
			MatchTeam( ent, MOVER_1TO2, level.time - ( total - partial ) );
			if ( ent->sound1to2 ) {
				G_AddEvent( ent, EV_GENERAL_SOUND, ent->sound1to2 );
			}
		//}
		return;
	}

	// only partway up before reversing
	if ( ent->moverState == MOVER_1TO2 ) {
		//Elder: don't interrupt if auto-opening
		if ( (ent->spawnflags & SP_AUTOOPEN) == SP_AUTOOPEN)
			return;

		total = ent->s.pos.trDuration;
		partial = level.time - ent->s.pos.trTime;
		if ( partial > total ) {
			partial = total;
		}
		//if ( (ent->spawnflags & SP_NODOORTOGGLE) == SP_NODOORTOGGLE) {
			//Elder: normal Q3 door and Toggle Door work identically
			MatchTeam( ent, MOVER_2TO1, level.time - ( total - partial ) );
			if ( ent->sound2to1 ) {
				G_AddEvent( ent, EV_GENERAL_SOUND, ent->sound2to1 );
			}
		//}
		return;
	}

	if ( ent->moverState == ROTATOR_POS1 ) {			// Reaction
		// start moving 50 msec later, becase if this was player
		// triggered, level.time hasn't been advanced yet
		MatchTeam( ent, ROTATOR_1TO2, level.time + 50 );

		// starting sound
		if ( ent->sound1to2 ) {
			G_AddEvent( ent, EV_GENERAL_SOUND, ent->sound1to2 );
		}

		// looping sound
		ent->s.loopSound = ent->soundLoop;

		// open areaportal
		if ( ent->teammaster == ent || !ent->teammaster ) {
			trap_AdjustAreaPortalState( ent, qtrue );
		}
		return;
	}

	// if all the way up, just delay before coming down
	if ( ent->moverState == ROTATOR_POS2 ) {
		//if ( ( (ent->spawnflags & SP_NODOORTOGGLE) == SP_NODOORTOGGLE ) ||
			//ent->touch || ent->takedamage) {
		if ( (ent->spawnflags & SP_DOORTOGGLE) == SP_DOORTOGGLE ) {
			//Elder: Move back "immediately"
			MatchTeam( ent, ROTATOR_2TO1, level.time + 50);
			if ( ent->sound1to2 ) {
				G_AddEvent( ent, EV_GENERAL_SOUND, ent->sound1to2 );
			}
		}
		else {
			//Elder: normal rotating door
			ent->nextthink = level.time + ent->wait;
		}
		return;
	}

	// only partway down before reversing
	if ( ent->moverState == ROTATOR_2TO1 ) {
		//Elder: don't interrupt if auto-opening
		if ( (ent->spawnflags & SP_AUTOOPEN) == SP_AUTOOPEN)
			return;

		total = ent->s.apos.trDuration;
		partial = level.time - ent->s.apos.trTime;
		if ( partial > total ) {
			partial = total;
		}
		//if ( (ent->spawnflags & SP_NODOORTOGGLE) == SP_NODOORTOGGLE) {
			//Elder: normal and toggle rotator act identically
			MatchTeam( ent, ROTATOR_1TO2, level.time - ( total - partial ) );
			if ( ent->sound1to2 ) {
				G_AddEvent( ent, EV_GENERAL_SOUND, ent->sound1to2 );
			}
		//}
		return;
	}

	// only partway up before reversing
	if ( ent->moverState == ROTATOR_1TO2 ) {
		//Elder: don't interrupt if auto-opening
		if ( (ent->spawnflags & SP_AUTOOPEN) == SP_AUTOOPEN)
			return;

		total = ent->s.apos.trDuration;
		partial = level.time - ent->s.apos.trTime;
		if ( partial > total ) {
			partial = total;
		}
		//Elder: Identical code -- err, maybe we can merge it
		//if ( (ent->spawnflags & SP_NODOORTOGGLE) == SP_NODOORTOGGLE) {
			//Elder: normal and toggle rotator act identically
			MatchTeam( ent, ROTATOR_2TO1, level.time - ( total - partial ) );
			if ( ent->sound2to1 ) {
				G_AddEvent( ent, EV_GENERAL_SOUND, ent->sound2to1 );
			}
		//}
		return;
	}
}



/*
================
InitMover

"pos1", "pos2", and "speed" should be set before calling,
so the movement delta can be calculated
================
*/
void InitMover( gentity_t *ent ) {
	vec3_t		move;
	float		distance;
	float		light;
	vec3_t		color;
	qboolean	lightSet, colorSet;
	char		*sound;

	// if the "model2" key is set, use a seperate model
	// for drawing, but clip against the brushes
	if ( ent->model2 ) {
		ent->s.modelindex2 = G_ModelIndex( ent->model2 );
	}

	// if the "loopsound" key is set, use a constant looping sound when moving
	if ( G_SpawnString( "noise", "100", &sound ) ) {
		ent->s.loopSound = G_SoundIndex( sound );
	}

	// if the "color" or "light" keys are set, setup constantLight
	lightSet = G_SpawnFloat( "light", "100", &light );
	colorSet = G_SpawnVector( "color", "1 1 1", color );
	if ( lightSet || colorSet ) {
		int		r, g, b, i;

		r = color[0] * 255;
		if ( r > 255 ) {
			r = 255;
		}
		g = color[1] * 255;
		if ( g > 255 ) {
			g = 255;
		}
		b = color[2] * 255;
		if ( b > 255 ) {
			b = 255;
		}
		i = light / 4;
		if ( i > 255 ) {
			i = 255;
		}
		ent->s.constantLight = r | ( g << 8 ) | ( b << 16 ) | ( i << 24 );
	}


	ent->use = Use_BinaryMover;
	ent->reached = Reached_BinaryMover;

	ent->moverState = MOVER_POS1;
	ent->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	ent->s.eType = ET_MOVER;
	VectorCopy (ent->pos1, ent->r.currentOrigin);
	trap_LinkEntity (ent);

	ent->s.pos.trType = TR_STATIONARY;
	VectorCopy( ent->pos1, ent->s.pos.trBase );

	// calculate time to reach second position from speed
	VectorSubtract( ent->pos2, ent->pos1, move );
	distance = VectorLength( move );
	if ( ! ent->speed ) {
		ent->speed = 100;
	}
	VectorScale( move, ent->speed, ent->s.pos.trDelta );
	ent->s.pos.trDuration = distance * 1000 / ent->speed;
	if ( ent->s.pos.trDuration <= 0 ) {
		ent->s.pos.trDuration = 1;
	}
}


/*
===============================================================================

DOOR

A use can be triggered either by a touch function, by being shot, or by being
targeted by another entity.

===============================================================================
*/

/*
================
Blocked_Door
================
*/
void Blocked_Door( gentity_t *ent, gentity_t *other ) {
	// remove anything other than a client
	if ( !other->client ) {
		// except CTF flags!!!!
		if ( other->s.eType == ET_ITEM && other->item->giType == IT_TEAM ) {
			Team_DroppedFlagThink( other );
			return;
		}
		// Elder: added to handle items and weapons in door paths
		if ( other->s.eType == ET_ITEM && other->item->giType == IT_WEAPON)
		{
			switch ( other->item->giTag )
			{
				case WP_MP5:
				case WP_M4:
				case WP_M3:
				case WP_HANDCANNON:
				case WP_SSG3000:
					RQ3_DroppedWeaponThink( other );
					return;
					break;
				case WP_GRENADE:
				case WP_PISTOL:
				case WP_KNIFE:
				case WP_AKIMBO:
				default:
					break;
			}
		}
		if ( other->s.eType == ET_ITEM && other->item->giType == IT_HOLDABLE) {
			switch ( other->item->giTag )
			{
				case HI_LASER:
				case HI_BANDOLIER:
				case HI_KEVLAR:
				case HI_SILENCER:
				case HI_SLIPPERS:
					RQ3_DroppedItemThink( other );
					return;
					break;
				default:
					break;
			}
		}
		G_TempEntity( other->s.origin, EV_ITEM_POP );
		G_FreeEntity( other );
		return;
	}

	if ( ent->damage ) {
		G_Damage( other, ent, ent, NULL, NULL, ent->damage, 0, MOD_CRUSH );
	}
	//if ( ent->spawnflags & 4 ) {
	//Elder: new crusher flag
	if ( ent->spawnflags & 2 ) {
		return;		// crushers don't reverse
	}

	// reverse direction
	// Makro - not for func_trains
	if (Q_stricmp(ent->classname, "func_train")) {
		Use_BinaryMover( ent, ent, other );
	}
}

/*
================
Touch_DoorTriggerSpectator
================
*/
void Touch_DoorTriggerSpectator( gentity_t *ent, gentity_t *other, trace_t *trace ) {
	int i, axis;
	vec3_t origin, dir, angles;

	// NiceAss: Only let spectators teleport through a door.
	if (other->client->sess.sessionTeam == TEAM_SPECTATOR) {
		axis = ent->count;
		VectorClear(dir);
		if (fabs(other->s.origin[axis] - ent->r.absmax[axis]) <
			fabs(other->s.origin[axis] - ent->r.absmin[axis])) {
			// NiceAss: "- 10" changed to "- 15" to prevent jumping back and forth occasionally when moving slowly
			origin[axis] = ent->r.absmin[axis] - 15;
			dir[axis] = -1;
		}
		else {
			// NiceAss: "- 10" changed to "- 15" to prevent jumping back and forth occasionally when moving slowly
			origin[axis] = ent->r.absmax[axis] + 15;
			dir[axis] = 1;
		}
		for (i = 0; i < 3; i++) {
			if (i == axis) continue;
			origin[i] = (ent->r.absmin[i] + ent->r.absmax[i]) * 0.5;
		}
		vectoangles(dir, angles);
		TeleportPlayer(other, origin, angles );
	}
}

/*
================
Touch_DoorTrigger
================
*/
void Touch_DoorTrigger( gentity_t *ent, gentity_t *other, trace_t *trace ) {
	// NiceAss: Not needed now that door's have their own spectator trigger
	/*
	if ( other->client && other->client->sess.sessionTeam == TEAM_SPECTATOR ) {
		// if the door is not open and not opening
		if ( ent->parent->moverState != MOVER_1TO2 &&
			ent->parent->moverState != MOVER_POS2 &&
			ent->parent->moverState != ROTATOR_1TO2 &&            // reaction
			ent->parent->moverState != ROTATOR_POS2 ) {
			Touch_DoorTriggerSpectator( ent, other, trace );
		}
	}
	*/
	//else if ( ent->parent->moverState != MOVER_1TO2 &&
			//ent->parent->moverState != ROTATOR_1TO2 ) {
	//Elder: we want to handle MOVER_1TO2 and ROTATOR_1TO2 now
	//else {
		//Blaze's broken open door code
		//Elder: not as broken as you think	:)
		if (other->client->openDoor ||
			(ent->parent->spawnflags & SP_AUTOOPEN) == SP_AUTOOPEN) {
			//G_Printf("Using a door\n");
			Use_BinaryMover( ent->parent, ent, other );
			// NiceAss: Hackish, but oh well. Done so you can trigger multiple doors in an area.
			other->client->openDoor = 2;  
		}
	//}
}


/*
======================
Think_SpawnNewDoorTrigger

All of the parts of a door have been spawned, so create
a trigger that encloses all of them
======================
*/
void Think_SpawnNewDoorTrigger( gentity_t *ent ) {
	gentity_t		*other;
	vec3_t		mins, maxs;
	int			i, best;

	// set all of the slaves as shootable
	// Makro - why ?
	for ( other = ent ; other ; other = other->teamchain ) {
		//other->takedamage = qtrue;
		other->takedamage = ent->takedamage;
	}

	// find the bounds of everything on the team
	VectorCopy (ent->r.absmin, mins);
	VectorCopy (ent->r.absmax, maxs);

	for (other = ent->teamchain ; other ; other=other->teamchain) {
		AddPointToBounds (other->r.absmin, mins, maxs);
		AddPointToBounds (other->r.absmax, mins, maxs);
	}

	// find the thinnest axis, which will be the one we expand
	best = 0;
	for ( i = 1 ; i < 3 ; i++ ) {
		if ( maxs[i] - mins[i] < maxs[best] - mins[best] ) {
			best = i;
		}
	}
	// expand
	maxs[best] += 60;
	mins[best] -= 60;
	// NiceAss: AQ2 Style. Above is Q3 style.
	if (best != 0) {
		maxs[0] += 60;
		mins[0] -= 60;
	}
	if (best != 1) {
		maxs[1] += 60;
		mins[1] -= 60;
	}

	// NiceAss: This trigger will be for players
	// create a trigger with this size
	// Makro - we only want these for doors without health & targetname
	if (!(ent->targetname) && !ent->health) {
		other = G_Spawn ();
		other->classname = "door_trigger";
		VectorCopy (mins, other->r.mins);
		VectorCopy (maxs, other->r.maxs);
		other->parent = ent;
		other->r.contents = CONTENTS_TRIGGER;
		other->touch = Touch_DoorTrigger;
		// remember the thinnest axis
		other->count = best;
		trap_LinkEntity (other);
	}

	//Makro - some doors shouldn't have triggers for spectators
	if (!ent->unbreakable) {
		// NiceAss: This trigger will be for spectators
		// NiceAss: Undo the stretched box size
		// expand
		maxs[best] -= 60;
		mins[best] += 60;
		// NiceAss: AQ2 Style. Above is Q3 style.
		if (best != 0) {
			maxs[0] -= 60;
			mins[0] += 60;
		}
		if (best != 1) {
			maxs[1] -= 60;
			mins[1] += 60;
		}


		other = G_Spawn ();
		other->classname = "door_trigger_spectator";
		VectorCopy (mins, other->r.mins);
		VectorCopy (maxs, other->r.maxs);
		other->parent = ent;
		other->r.contents = CONTENTS_TRIGGER;
		other->touch = Touch_DoorTriggerSpectator;
		// remember the thinnest axis
		other->count = best;
		trap_LinkEntity (other);
	}

	MatchTeam( ent, ent->moverState, level.time );
}

void Think_MatchTeam( gentity_t *ent ) {
	MatchTeam( ent, ent->moverState, level.time );
}

//Elder: old func_door Radiant comment
/*QUAKED func_door (0 .5 .8) ? START_OPEN x CRUSHER
TOGGLE		wait in both the start and end states for a trigger event.
START_OPEN	the door to moves to its destination when spawned, and operate in reverse.  It is used to temporarily or permanently close off an area when triggered (not useful for touch or takedamage doors).
NOMONSTER	monsters will not trigger this door

"model2"	.md3 model to also draw
"angle"		determines the opening direction
"targetname" if set, no touch field will be spawned and a remote button or trigger field activates the door.
"speed"		movement speed (100 default)
"wait"		wait before returning (3 default, -1 = never return)
"lip"		lip remaining at end of move (8 default)
"dmg"		damage to inflict when blocked (2 default)
"color"		constantLight color
"light"		constantLight radius
"health"	if set, the door must be shot open
*/

//Elder: new one from GTKRadiant's entity.def plus Reaction stuff

/*QUAKED func_door (0 .5 .8) ? START_OPEN CRUSHER AUTO_OPEN TOGGLE
Normal sliding door entity. By default, the door will activate when player walks close to it or when damage is inflicted to it.
-------- KEYS --------
angle : determines the opening direction of door (up = -1, down = -2).
speed : determines how fast the door moves (default 100).
wait : number of seconds before door returns (default 2, -1 = return immediately)
lip : lip remaining at end of move (default 8)
targetname : if set, a func_button or trigger is required to activate the door.
health : if set to a non-zero value, the door must be damaged by "health" amount of points to activate (default 0).
dmg : damage to inflict on player when he blocks operation of door (default 4). Door will reverse direction when blocked unless CRUSHER spawnflag is set.
team: assign the same team name to multiple doors that should operate together (see Notes).
light : constantLight radius of .md3 model included with entity. Has no effect on the entity's brushes (default 0).
color : constantLight color of .md3 model included with entity. Has no effect on the entity's brushes (default 1 1 1).
model2 : path/name of model to include (eg: models/mapobjects/pipe/pipe02.md3).
origin : alternate method of setting XYZ origin of .md3 model included with entity (See Notes).
notfree : when set to 1, entity will not spawn in "Free for all" and "Tournament" modes.
notteam : when set to 1, entity will not spawn in "Teamplay" and "CTF" modes.
notsingle : when set to 1, entity will not spawn in Single Player mode (bot play mode).
soundstart : path to sound file to play when door starts to open
soundstop : path to sound file to play when door comes to a stop
soundmove : path to sound file to play when door is moving
-------- SPAWNFLAGS --------
START_OPEN : the door will spawn in the open state and operate in reverse.
CRUSHER : door will not reverse direction when blocked and will keep damaging player until he dies or gets out of the way.
TOGGLE : door requires an opendoor toggle to open or close
AUTOOPEN : door will open like traditional Q3 doors (like a motion sensor)
-------- NOTES --------
Unlike in Quake 2, doors that touch are NOT automatically teamed. If you want doors to operate together, you have to team them manually by assigning the same team name to all of them. Setting the origin key is simply an alternate method to using an origin brush. When using the model2 key, the origin point of the model will correspond to the origin point defined by either the origin brush or the origin coordinate value.*/
void SP_func_door (gentity_t *ent) {
	vec3_t	abs_movedir;
	float	distance;
	vec3_t	size;
	float	lip;
	//Elder: added
	char	*sSndMove;
	char	*sSndStop;
	char	*sSndStart;

	//Elder: can set sounds from here
  //Blaze: changed default path as per Sze
	G_SpawnString( "soundstart", "sound/misc/silence.wav", &sSndStart );
	G_SpawnString( "soundstop", "sound/movers/rdoor_stop.wav", &sSndStop );
	G_SpawnString( "soundmove", "sound/movers/rdoor_move.wav", &sSndMove );

	ent->sound1to2 = ent->sound2to1 = G_SoundIndex(sSndMove);
	ent->soundPos1 = G_SoundIndex(sSndStart);
	ent->soundPos2 = G_SoundIndex(sSndStop);

	//ent->sound1to2 = ent->sound2to1 = G_SoundIndex("sound/movers/doors/dr1_strt.wav");
	//ent->soundPos1 = ent->soundPos2 = G_SoundIndex("sound/movers/doors/dr1_end.wav");

	ent->blocked = Blocked_Door;

	//Elder: added for debugging purposes but doesn't show up (DOH)
/*
	if ( (ent->spawnflags & 1) == 1)
		G_Printf("func_door Starting Open\n");
	if ( (ent->spawnflags & 2) == 2)
		G_Printf("func_door CRUSHER\n");
	if ( (ent->spawnflags & SP_DOORTOGGLE) == SP_DOORTOGGLE)
		G_Printf("func_door is a Toggle\n");
	if ( (ent->spawnflags & SP_AUTOOPEN) == SP_AUTOOPEN)
		G_Printf("func_door is an auto-open\n");
*/

	// default speed of 400
	if (!ent->speed)
		ent->speed = 400;

	// default wait of 2 seconds
	if (!ent->wait)
		ent->wait = 2;
	ent->wait *= 1000;

	// default lip of 8 units
	G_SpawnFloat( "lip", "8", &lip );

	// default damage of 2 points
	G_SpawnInt( "dmg", "2", &ent->damage );

	// first position at start
	VectorCopy( ent->s.origin, ent->pos1 );

	// calculate second position
	trap_SetBrushModel( ent, ent->model );
	G_SetMovedir (ent->s.angles, ent->movedir);
	abs_movedir[0] = fabs(ent->movedir[0]);
	abs_movedir[1] = fabs(ent->movedir[1]);
	abs_movedir[2] = fabs(ent->movedir[2]);
	VectorSubtract( ent->r.maxs, ent->r.mins, size );
	distance = DotProduct( abs_movedir, size ) - lip;
	VectorMA( ent->pos1, distance, ent->movedir, ent->pos2 );

	// if "start_open", reverse position 1 and 2
	if ( ent->spawnflags & 1 ) {
		vec3_t	temp;

		VectorCopy( ent->pos2, temp );
		VectorCopy( ent->s.origin, ent->pos2 );
		VectorCopy( temp, ent->pos1 );
	}

	InitMover( ent );

	if ( ! (ent->flags & FL_TEAMSLAVE ) ) {
		int health;
		int noSpecs = 0;

		G_SpawnInt( "health", "0", &health );
		if ( health ) {
			ent->takedamage = qtrue;
		}

		//Makro - some doors don't need spectator triggers
		G_SpawnInt( "nospectators", "0", &noSpecs );
		//hijacking unbreakable field
		ent->unbreakable = noSpecs;
		ent->think = Think_SpawnNewDoorTrigger;
		ent->nextthink = level.time + FRAMETIME;
	}

	//Elder: open areaportals for start_open doors
	if ( (ent->spawnflags & 1) == 1 && (ent->teammaster == ent || !ent->teammaster) ) {
		trap_AdjustAreaPortalState( ent, qtrue );
	}

}

// REACTION

/*QUAKED func_door_rotating (0 .5 .8) START_OPEN CRUSHER AUTO_OPEN TOGGLE X_AXIS Y_AXIS
This is the rotating door... just as the name suggests it's a door that rotates
START_OPEN	the door to moves to its destination when spawned, and operate in reverse.
REVERSE		if you want the door to open in the other direction, use this switch.
TOGGLE		wait in both the start and end states for a trigger event.
X_AXIS		open on the X-axis instead of the Z-axis
Y_AXIS		open on the Y-axis instead of the Z-axis

You need to have an origin brush as part of this entity.  The center of that brush will be
the point around which it is rotated. It will rotate around the Z axis by default.  You can
check either the X_AXIS or Y_AXIS box to change that.

"model2"	.md3 model to also draw
"distance"	how many degrees the door will open
"speed"	 	how fast the door will open (degrees/second)
"color"		constantLight color
"light"		constantLight radius
soundstart : path to sound file to play when door starts to open
soundstop : path to sound file to play when door comes to a stop
soundmove : path to sound file to play when door is moving
*/

void SP_func_door_rotating ( gentity_t *ent ) {
	//Elder: added
	char	*sSndMove;
	char	*sSndStop;
	char	*sSndStart;

	//Elder: can set sounds from here
	G_SpawnString( "soundstart", "sound/movers/rdoor_stop.wav", &sSndStart );
	G_SpawnString( "soundstop", "sound/misc/silence.wav", &sSndStop );
	G_SpawnString( "soundmove", "sound/movers/rdoor_move.wav", &sSndMove );

	ent->sound1to2 = ent->sound2to1 = G_SoundIndex(sSndMove);
	ent->soundPos1 = G_SoundIndex(sSndStart);
	ent->soundPos2 = G_SoundIndex(sSndStop);

	//ent->sound1to2 = ent->sound2to1 = G_SoundIndex("sound/movers/doors/dr1_strt.wav");
	//ent->soundPos1 = ent->soundPos2 = G_SoundIndex("sound/movers/doors/dr1_end.wav");

	ent->blocked = Blocked_Door;

	// default speed of 120
	if (!ent->speed)
		ent->speed = 120;

/*
	if ( ent->spawnflags & 1)
		G_Printf("rotating door Starting Open\n");
	if ( ent->spawnflags & 2)
		G_Printf("rotating door in REVERSE\n");
	if ( ent->spawnflags & 4)
		G_Printf("rotating door Toggleable\n");
	if ( ent->spawnflags & 8)
		G_Printf("rotating door on X_AXIS\n");
	if ( ent->spawnflags & 16)
		G_Printf("rotating door on Y_AXIS\n");
*/

	// if speed is negative, positize it and add reverse flag
	// Elder: handled below in reverse direction
	/*
	if ( ent->speed < 0 ) {
		ent->speed *= -1;
		ent->spawnflags |= 2;
	}*/

	// default of 2 seconds
	if (!ent->wait)
		ent->wait = 2;
	ent->wait *= 1000;

	// set the axis of rotation
	VectorClear( ent->movedir );
	VectorClear( ent->s.angles );

	//Elder: changed from 8 - 16 and 16 - 32 respectively
	if ( ent->spawnflags & 16 ) {
		ent->movedir[2] = 1.0;
	} else if ( ent->spawnflags & 32 ) {
		ent->movedir[0] = 1.0;
	} else {
		ent->movedir[1] = 1.0;
	}

	// reverse direction if necessary
	//if ( ent->spawnflags & 2 )
	if (ent->speed < 0) {
		ent->speed *= -1;
		VectorNegate ( ent->movedir, ent->movedir );
	}

	// default distance of 90 degrees. This is something the mapper should not
	// leave out, so we'll tell him if he does.
	if ( !ent->distance ) {
		G_Printf("%s at %s with no distance set.\n",
		ent->classname, vtos(ent->s.origin));
		ent->distance = 90.0;
	}

	VectorCopy( ent->s.angles, ent->pos1 );
	trap_SetBrushModel( ent, ent->model );
	VectorMA ( ent->pos1, ent->distance, ent->movedir, ent->pos2 );

	// if "start_open", reverse position 1 and 2
	if ( ent->spawnflags & 1 ) {
		vec3_t	temp;

		VectorCopy( ent->pos2, temp );
		VectorCopy( ent->s.angles, ent->pos2 );
		VectorCopy( temp, ent->pos1 );
		VectorNegate ( ent->movedir, ent->movedir );
	}

	// set origin
	VectorCopy( ent->s.origin, ent->s.pos.trBase );
	VectorCopy( ent->s.pos.trBase, ent->r.currentOrigin );

	InitRotator( ent );

	if ( ! (ent->flags & FL_TEAMSLAVE ) ) {
		int health;
		int noSpecs = 0;

		G_SpawnInt( "health", "0", &health );
		if ( health ) {
			ent->takedamage = qtrue;
		}

		//Makro - some doors don't need spectator triggers
		G_SpawnInt( "nospectators", "0", &noSpecs );
		//hijacking unbreakable field
		ent->unbreakable = noSpecs;
		ent->think = Think_SpawnNewDoorTrigger;
		ent->nextthink = level.time + FRAMETIME;
	}

	//Makro - copied from func_door
	//Elder: open areaportals for start_open doors
	if ( (ent->spawnflags & 1) == 1 && (ent->teammaster == ent || !ent->teammaster) ) {
		trap_AdjustAreaPortalState( ent, qtrue );
	}

}

/*
================
InitRotator

"pos1", "pos2", and "speed" should be set before calling,
so the movement delta can be calculated
================
*/
void InitRotator( gentity_t *ent ) {
	vec3_t		move;
	float		angle;
	float		light;
	vec3_t		color;
	qboolean	lightSet, colorSet;
	char		*sound;

	// if the "model2" key is set, use a seperate model
	// for drawing, but clip against the brushes
	if ( ent->model2 ) {
		ent->s.modelindex2 = G_ModelIndex( ent->model2 );
	}

	// if the "loopsound" key is set, use a constant looping sound when moving
	if ( G_SpawnString( "noise", "100", &sound ) ) {
		ent->s.loopSound = G_SoundIndex( sound );
	}

	// if the "color" or "light" keys are set, setup constantLight
	lightSet = G_SpawnFloat( "light", "100", &light );
	colorSet = G_SpawnVector( "color", "1 1 1", color );
	if ( lightSet || colorSet ) {
		int		r, g, b, i;

		r = color[0] * 255;
		if ( r > 255 ) {
			r = 255;
		}
		g = color[1] * 255;
		if ( g > 255 ) {
			g = 255;
		}
		b = color[2] * 255;
		if ( b > 255 ) {
			b = 255;
		}
		i = light / 4;
		if ( i > 255 ) {
			i = 255;
		}
		ent->s.constantLight = r | ( g << 8 ) | ( b << 16 ) | ( i << 24 );
	}


	ent->use = Use_BinaryMover;
	ent->reached = Reached_BinaryMover;

	ent->moverState = ROTATOR_POS1;
	ent->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	ent->s.eType = ET_MOVER;
	VectorCopy( ent->pos1, ent->r.currentAngles );
	trap_LinkEntity (ent);

	ent->s.apos.trType = TR_STATIONARY;
	VectorCopy( ent->pos1, ent->s.apos.trBase );

	// calculate time to reach second position from speed
	VectorSubtract( ent->pos2, ent->pos1, move );
	angle = VectorLength( move );
	if ( ! ent->speed ) {
		ent->speed = 120;
	}
	VectorScale( move, ent->speed, ent->s.apos.trDelta );
	ent->s.apos.trDuration = angle * 1000 / ent->speed;
	if ( ent->s.apos.trDuration <= 0 ) {
		ent->s.apos.trDuration = 1;
	}
}






/*
===============================================================================

PLAT

===============================================================================
*/

/*
==============
Touch_Plat

Don't allow decent if a living player is on it
===============
*/
void Touch_Plat( gentity_t *ent, gentity_t *other, trace_t *trace ) {
	if ( !other->client || other->client->ps.stats[STAT_HEALTH] <= 0 ) {
		return;
	}

	// delay return-to-pos1 by one second
	if ( ent->moverState == MOVER_POS2 ) {
		ent->nextthink = level.time + 1000;
	}
}

/*
==============
Touch_PlatCenterTrigger

If the plat is at the bottom position, start it going up
===============
*/
void Touch_PlatCenterTrigger(gentity_t *ent, gentity_t *other, trace_t *trace ) {
	if ( !other->client ) {
		return;
	}

	if ( ent->parent->moverState == MOVER_POS1 ) {
		Use_BinaryMover( ent->parent, ent, other );
	}
}


/*
================
SpawnPlatTrigger

Spawn a trigger in the middle of the plat's low position
Elevator cars require that the trigger extend through the entire low position,
not just sit on top of it.
================
*/
void SpawnPlatTrigger( gentity_t *ent ) {
	gentity_t	*trigger;
	vec3_t	tmin, tmax;

	// the middle trigger will be a thin trigger just
	// above the starting position
	trigger = G_Spawn();
	trigger->classname = "plat_trigger";
	trigger->touch = Touch_PlatCenterTrigger;
	trigger->r.contents = CONTENTS_TRIGGER;
	trigger->parent = ent;

	tmin[0] = ent->pos1[0] + ent->r.mins[0] + 33;
	tmin[1] = ent->pos1[1] + ent->r.mins[1] + 33;
	tmin[2] = ent->pos1[2] + ent->r.mins[2];

	tmax[0] = ent->pos1[0] + ent->r.maxs[0] - 33;
	tmax[1] = ent->pos1[1] + ent->r.maxs[1] - 33;
	tmax[2] = ent->pos1[2] + ent->r.maxs[2] + 8;

	if ( tmax[0] <= tmin[0] ) {
		tmin[0] = ent->pos1[0] + (ent->r.mins[0] + ent->r.maxs[0]) *0.5;
		tmax[0] = tmin[0] + 1;
	}
	if ( tmax[1] <= tmin[1] ) {
		tmin[1] = ent->pos1[1] + (ent->r.mins[1] + ent->r.maxs[1]) *0.5;
		tmax[1] = tmin[1] + 1;
	}

	VectorCopy (tmin, trigger->r.mins);
	VectorCopy (tmax, trigger->r.maxs);

	trap_LinkEntity (trigger);
}


/*QUAKED func_plat (0 .5 .8) ?
Plats are always drawn in the extended position so they will light correctly.

"lip"		default 8, protrusion above rest position
"height"	total height of movement, defaults to model height
"speed"		overrides default 200.
"dmg"		overrides default 2
"model2"	.md3 model to also draw
"color"		constantLight color
"light"		constantLight radius
*/
void SP_func_plat (gentity_t *ent) {
	float		lip, height;

	//Blaze: added
	char	*sSndMove;
	char	*sSndStop;
	char	*sSndStart;

	G_SpawnString( "soundstart", "sound/movers/plat_start.wav", &sSndStart );
	G_SpawnString( "soundstop", "sound/movers/plat_stop.wav", &sSndStop );
	G_SpawnString( "soundmove", "sound/movers/plat_move.wav", &sSndMove );

	ent->sound1to2 = ent->sound2to1 = G_SoundIndex(sSndMove);
	ent->soundPos1 = G_SoundIndex(sSndStart);
	ent->soundPos2 = G_SoundIndex(sSndStop);


	VectorClear (ent->s.angles);

	G_SpawnFloat( "speed", "200", &ent->speed );
	G_SpawnInt( "dmg", "2", &ent->damage );
	G_SpawnFloat( "wait", "1", &ent->wait );
	G_SpawnFloat( "lip", "8", &lip );

	ent->wait = 1000;

	// create second position
	trap_SetBrushModel( ent, ent->model );

	if ( !G_SpawnFloat( "height", "0", &height ) ) {
		height = (ent->r.maxs[2] - ent->r.mins[2]) - lip;
	}

	// pos1 is the rest (bottom) position, pos2 is the top
	VectorCopy( ent->s.origin, ent->pos2 );
	VectorCopy( ent->pos2, ent->pos1 );
	ent->pos1[2] -= height;

	InitMover( ent );

	// touch function keeps the plat from returning while
	// a live player is standing on it
	ent->touch = Touch_Plat;

	ent->blocked = Blocked_Door;

	ent->parent = ent;	// so it can be treated as a door

	// spawn the trigger if one hasn't been custom made
	if ( !ent->targetname ) {
		SpawnPlatTrigger(ent);
	}
}


/*
===============================================================================

BUTTON

===============================================================================
*/

/*
==============
Touch_Button

===============
*/
void Touch_Button(gentity_t *ent, gentity_t *other, trace_t *trace ) {
	if ( !other->client ) {
		return;
	}

	if ( ent->moverState == MOVER_POS1 ) {
		Use_BinaryMover( ent, other, other );
	}
}


/*QUAKED func_button (0 .5 .8) ?
When a button is touched, it moves some distance in the direction of it's angle, triggers all of it's targets, waits some time, then returns to it's original position where it can be triggered again.

"model2"	.md3 model to also draw
"angle"		determines the opening direction
"target"	all entities with a matching targetname will be used
"speed"		override the default 40 speed
"wait"		override the default 1 second wait (-1 = never return)
"lip"		override the default 4 pixel lip remaining at end of move
"health"	if set, the button must be killed instead of touched
"color"		constantLight color
"light"		constantLight radius
"pathtarget" stores the target for a train
*/

void SP_func_button( gentity_t *ent ) {
	vec3_t		abs_movedir;
	float		distance;
	vec3_t		size;
	float		lip;
	char *noise;
  
  //changed to sound to stop it from conflicting with the looping noise
  //Changed from noise to sound as per Sze
  G_SpawnString( "sound", "sound/movers/button.wav", &noise );
  ent->sound1to2 = G_SoundIndex(noise);

	if ( !ent->speed ) {
		ent->speed = 40;
	}

	if ( !ent->wait ) {
		ent->wait = 1;
	}
	ent->wait *= 1000;

	// first position
	VectorCopy( ent->s.origin, ent->pos1 );

	// calculate second position
	trap_SetBrushModel( ent, ent->model );

	G_SpawnFloat( "lip", "4", &lip );

	G_SetMovedir( ent->s.angles, ent->movedir );
	abs_movedir[0] = fabs(ent->movedir[0]);
	abs_movedir[1] = fabs(ent->movedir[1]);
	abs_movedir[2] = fabs(ent->movedir[2]);
	VectorSubtract( ent->r.maxs, ent->r.mins, size );
	distance = abs_movedir[0] * size[0] + abs_movedir[1] * size[1] + abs_movedir[2] * size[2] - lip;
	VectorMA (ent->pos1, distance, ent->movedir, ent->pos2);

	if (ent->health) {
		// shootable button
		ent->takedamage = qtrue;
	} else {
		// touchable button
		ent->touch = Touch_Button;
	}

	InitMover( ent );
	//if ( G_SpawnString( "pathtarget","", &s) ) {
	//	strcpy(ent->pathtarget, s);
	//}

}



/*
===============================================================================

TRAIN

===============================================================================
*/


#define TRAIN_START_ON		1
#define TRAIN_TOGGLE		2
#define TRAIN_BLOCK_STOPS	4

/*
===============
Think_BeginMoving

The wait time at a corner has completed, so start moving again
===============
*/
void Think_BeginMoving( gentity_t *ent ) {
	ent->s.pos.trTime = level.time;
	ent->s.pos.trType = TR_LINEAR_STOP;
}

/*
===============
Reached_Train
===============
*/
void Reached_Train( gentity_t *ent ) {
	gentity_t		*next;
	float			speed;
	vec3_t			move;
	float			length;

	// copy the apropriate values
	next = ent->nextTrain;
	if ( !next || !next->nextTrain ) {
		return;		// just stop
	}

	// fire all other targets
	// Makro - set activator to ent; was NULL before
	G_UseTargets( next, ent );

	// set the new trajectory
	ent->nextTrain = next->nextTrain;
	//Blaze: Spam out some info about where the train is
	//G_Printf("^1Reached Reached_Train %s %s\n", next->targetname, next->target);
	//G_Printf("^3Train is at (%f %f %f) or (%f %f %f)\n",ent->s.origin[0],ent->s.origin[1],ent->s.origin[2], ent->pos1[0], ent->pos1[1], ent->pos1[2]);
	//G_Printf("^2NextTrain  Origin(%f, %f, %f) Next Origin (%f, %f, %f)\n", next->nextTrain->s.origin[0], next->nextTrain->s.origin[1], next->nextTrain->s.origin[2], next->s.origin[0], next->s.origin[1], next->s.origin[2]);
	
	VectorCopy( next->s.origin, ent->pos1 );
	VectorCopy( next->nextTrain->s.origin, ent->pos2 );

	// if the path_corner has a speed, use that
	if ( next->speed ) {
		speed = next->speed;
	} else {
		// otherwise use the train's speed
		speed = ent->speed;
	}
	if ( speed < 1 ) {
		speed = 1;
	}

	// calculate duration
	VectorSubtract( ent->pos2, ent->pos1, move );
	length = VectorLength( move );

	ent->s.pos.trDuration = length * 1000 / speed;

	// looping sound
	ent->s.loopSound = next->soundLoop;

	// start it going
	SetMoverState( ent, MOVER_1TO2, level.time );

	// if there is a "wait" value on the target, don't start moving yet
	if ( next->wait ) {
		ent->nextthink = level.time + next->wait * 1000;
		ent->think = Think_BeginMoving;
		ent->s.pos.trType = TR_STATIONARY;
	}
	//Blaze: If the wait is less then 0, dont nextthing
	if (next->wait < 0)
	{
		ent->nextthink = 0;
		ent->think = Think_BeginMoving;
		ent->s.pos.trType = TR_STATIONARY;
	}
}


/*
===============
Think_SetupTrainTargets

Link all the corners together
===============
*/
void Think_SetupTrainTargets( gentity_t *ent ) {
	gentity_t		*path, *next, *start;

	ent->nextTrain = G_Find( NULL, FOFS(targetname), ent->target );
	if ( !ent->nextTrain ) {
		G_Printf( "func_train at %s with an unfound target\n",
			vtos(ent->r.absmin) );
		return;
	}

	start = NULL;
	for ( path = ent->nextTrain ; path != start ; path = next ) {
		if ( !start ) {
			start = path;
		}

		if ( !path->target ) {
			G_Printf( "Train corner at %s without a target\n",
				vtos(path->s.origin) );
			return;
		}

		// find a path_corner among the targets
		// there may also be other targets that get fired when the corner
		// is reached
		next = NULL;
		do {
			next = G_Find( next, FOFS(targetname), path->target );
			if ( !next ) {
				G_Printf( "Train corner at %s without a target path_corner\n",
					vtos(path->s.origin) );
				return;
			}
		} while ( strcmp( next->classname, "path_corner" ) );

		path->nextTrain = next;
	}

	// start the train moving from the first corner
	Reached_Train( ent );
}



/*QUAKED path_corner (.5 .3 0) (-8 -8 -8) (8 8 8)
Train path corners.
Target: next path corner and other targets to fire
"speed" speed to move to the next corner
"wait" seconds to wait before behining move to next corner
*/
void SP_path_corner( gentity_t *self ) {

	//Blaze Print out some info for the path corners
	//G_Printf("^1Ent Wait = %f %s %s\n", self->wait, self->targetname, self->target);

	//G_Printf("^2path_corner Origin(%f, %f, %f)", self->s.origin[0], self->s.origin[1], self->s.origin[2]);

	if ( !self->targetname ) {
		G_Printf ("path_corner with no targetname at %s\n", vtos(self->s.origin));
		G_FreeEntity( self );
		return;
	}
	// path corners don't need to be linked in
}

/*
===============
Use_Func_Train

Added by Makro
===============
*/
void Use_Func_Train( gentity_t *ent, gentity_t *other, gentity_t *activator ) {
	gentity_t		*next;
	float			speed;
	vec3_t			move;
	float			length;

	// copy the apropriate values
	if (!other->pathtarget)
		return;
	//G_Printf("pathtarget to look for: %s\n\n", other->pathtarget);
	next = G_Find2(NULL, FOFS(targetname), other->pathtarget, FOFS(classname), "path_corner");
	
	if ( !next || !next->nextTrain ) {
		return;		// just stop
	}

	// set the new trajectory
	VectorCopy( ent->r.currentOrigin, ent->pos1 );
	VectorCopy( next->s.origin, ent->pos2 );
	ent->nextTrain = next;

	//the train is already there
	if (VectorCompare(ent->pos1, ent->pos2)) {
		Reached_Train(ent);
		return;
	}
	//Blaze: Spam out some info about where the train is
	//G_Printf("^1Reached Reached_Train %s %s\n", next->targetname, next->target);
	//G_Printf("^3Train is at (%f %f %f) or (%f %f %f)\n",ent->s.origin[0],ent->s.origin[1],ent->s.origin[2], ent->pos1[0], ent->pos1[1], ent->pos1[2]);
	//G_Printf("^2NextTrain  Origin(%f, %f, %f) Next Origin (%f, %f, %f)\n", next->nextTrain->s.origin[0], next->nextTrain->s.origin[1], next->nextTrain->s.origin[2], next->s.origin[0], next->s.origin[1], next->s.origin[2]);
	
	speed = ent->speed;

	// calculate duration
	VectorSubtract( ent->pos2, ent->pos1, move );
	length = VectorLength( move );

	ent->s.pos.trDuration = length * 1000 / speed;

	// looping sound
	ent->s.loopSound = next->soundLoop;

	// start it going
	SetMoverState( ent, MOVER_1TO2, level.time );

	// if there is a "wait" value on the target, don't start moving yet
	if ( next->wait ) {
		ent->nextthink = level.time + next->wait * 1000;
		ent->think = Think_BeginMoving;
		ent->s.pos.trType = TR_STATIONARY;
	}
	//Blaze: If the wait is less than 0, dont nextthing
	/*
	if (next->wait < 0)
	{
		ent->nextthink = 0;
		ent->think = Think_BeginMoving;
		ent->s.pos.trType = TR_STATIONARY;
	}
	*/
}



/*QUAKED func_train (0 .5 .8) ? START_ON TOGGLE BLOCK_STOPS
A train is a mover that moves between path_corner target points.
Trains MUST HAVE AN ORIGIN BRUSH.
The train spawns at the first target it is pointing at.
"model2"	.md3 model to also draw
"speed"		default 100
"dmg"		default	2
"noise"		looping sound to play when the train is in motion
"target"	next path corner
"color"		constantLight color
"light"		constantLight radius
*/
void SP_func_train (gentity_t *self) {
	VectorClear (self->s.angles);

	/* Makro - more power to the mappa' !
	if (self->spawnflags & TRAIN_BLOCK_STOPS) {
		self->damage = 0;
	} else {
		if (!self->damage) {
			self->damage = 2;
		}
	}
	*/

	if ( !self->speed ) {
		self->speed = 100;
	}

	if ( !self->target ) {
		G_Printf ("func_train without a target at %s\n", vtos(self->r.absmin));
		G_FreeEntity( self );
		return;
	}

	trap_SetBrushModel( self, self->model );
	InitMover( self );

	self->reached = Reached_Train;

	// start trains on the second frame, to make sure their targets have had
	// a chance to spawn
	self->nextthink = level.time + FRAMETIME;
	self->think = Think_SetupTrainTargets;

	//Makro - added
	self->use = Use_Func_Train;
	self->blocked = Blocked_Door;
}

/*
===============================================================================

STATIC

===============================================================================
*/


/*QUAKED func_static (0 .5 .8) ? START_OFF
A bmodel that just sits there, doing nothing.  Can be used for conditional walls and models.
"model2"	.md3 model to also draw
"color"		constantLight color
"light"		constantLight radius
*/
//Makro - added for triggerable func_statics
void use_func_static( gentity_t *ent, gentity_t *other, gentity_t *activator ) {
	ent->count ^= 1;
	if ( ent->count ) {
		ent->s.eFlags &= ~EF_NODRAW;
		ent->r.contents = CONTENTS_SOLID;
		ent->r.svFlags &= ~SVF_NOCLIENT;
	} else {
		ent->s.eFlags |= EF_NODRAW;
		ent->r.contents = CONTENTS_TRIGGER;
		ent->r.svFlags |= SVF_NOCLIENT;
	}
}

void SP_func_static( gentity_t *ent ) {
	trap_SetBrushModel( ent, ent->model );
	InitMover( ent );
	VectorCopy( ent->s.origin, ent->s.pos.trBase );
	VectorCopy( ent->s.origin, ent->r.currentOrigin );
	//Makro - added
	ent->count = (ent->spawnflags & 1);
	ent->use = use_func_static;
	ent->use(ent, NULL, NULL);
	//end Makro
}


/*
===============================================================================

ROTATING

===============================================================================
*/


/*QUAKED func_rotating (0 .5 .8) ? START_ON - X_AXIS Y_AXIS
You need to have an origin brush as part of this entity.  The center of that brush will be
the point around which it is rotated. It will rotate around the Z axis by default.  You can
check either the X_AXIS or Y_AXIS box to change that.

"model2"	.md3 model to also draw
"speed"		determines how fast it moves; default value is 100.
"dmg"		damage to inflict when blocked (2 default)
"color"		constantLight color
"light"		constantLight radius
*/
void SP_func_rotating (gentity_t *ent) {
	if ( !ent->speed ) {
		ent->speed = 100;
	}

	// set the axis of rotation
	ent->s.apos.trType = TR_LINEAR;
	if ( ent->spawnflags & 4 ) {
		ent->s.apos.trDelta[2] = ent->speed;
	} else if ( ent->spawnflags & 8 ) {
		ent->s.apos.trDelta[0] = ent->speed;
	} else {
		ent->s.apos.trDelta[1] = ent->speed;
	}

	if (!ent->damage) {
		ent->damage = 2;
	}

	trap_SetBrushModel( ent, ent->model );
	InitMover( ent );

	VectorCopy( ent->s.origin, ent->s.pos.trBase );
	VectorCopy( ent->s.pos.trBase, ent->r.currentOrigin );
	VectorCopy( ent->s.apos.trBase, ent->r.currentAngles );

	trap_LinkEntity( ent );
}


/*
===============================================================================

BOBBING

===============================================================================
*/


/*QUAKED func_bobbing (0 .5 .8) ? X_AXIS Y_AXIS
Normally bobs on the Z axis
"model2"	.md3 model to also draw
"height"	amplitude of bob (32 default)
"speed"		seconds to complete a bob cycle (4 default)
"phase"		the 0.0 to 1.0 offset in the cycle to start at
"dmg"		damage to inflict when blocked (2 default)
"color"		constantLight color
"light"		constantLight radius
*/
void SP_func_bobbing (gentity_t *ent) {
	float		height;
	float		phase;

	G_SpawnFloat( "speed", "4", &ent->speed );
	G_SpawnFloat( "height", "32", &height );
	G_SpawnInt( "dmg", "2", &ent->damage );
	G_SpawnFloat( "phase", "0", &phase );

	trap_SetBrushModel( ent, ent->model );
	InitMover( ent );

	VectorCopy( ent->s.origin, ent->s.pos.trBase );
	VectorCopy( ent->s.origin, ent->r.currentOrigin );

	ent->s.pos.trDuration = ent->speed * 1000;
	ent->s.pos.trTime = ent->s.pos.trDuration * phase;
	ent->s.pos.trType = TR_SINE;

	// set the axis of bobbing
	if ( ent->spawnflags & 1 ) {
		ent->s.pos.trDelta[0] = height;
	} else if ( ent->spawnflags & 2 ) {
		ent->s.pos.trDelta[1] = height;
	} else {
		ent->s.pos.trDelta[2] = height;
	}
}

/*
===============================================================================

PENDULUM

===============================================================================
*/


/*QUAKED func_pendulum (0 .5 .8) ?
You need to have an origin brush as part of this entity.
Pendulums always swing north / south on unrotated models.  Add an angles field to the model to allow rotation in other directions.
Pendulum frequency is a physical constant based on the length of the beam and gravity.
"model2"	.md3 model to also draw
"speed"		the number of degrees each way the pendulum swings, (30 default)
"phase"		the 0.0 to 1.0 offset in the cycle to start at
"dmg"		damage to inflict when blocked (2 default)
"color"		constantLight color
"light"		constantLight radius
*/
void SP_func_pendulum(gentity_t *ent) {
	float		freq;
	float		length;
	float		phase;
	float		speed;

	G_SpawnFloat( "speed", "30", &speed );
	G_SpawnInt( "dmg", "2", &ent->damage );
	G_SpawnFloat( "phase", "0", &phase );

	trap_SetBrushModel( ent, ent->model );

	// find pendulum length
	length = fabs( ent->r.mins[2] );
	if ( length < 8 ) {
		length = 8;
	}

	freq = 1 / ( M_PI * 2 ) * sqrt( g_gravity.value / ( 3 * length ) );

	ent->s.pos.trDuration = ( 1000 / freq );

	InitMover( ent );

	VectorCopy( ent->s.origin, ent->s.pos.trBase );
	VectorCopy( ent->s.origin, ent->r.currentOrigin );

	VectorCopy( ent->s.angles, ent->s.apos.trBase );

	ent->s.apos.trDuration = 1000 / freq;
	ent->s.apos.trTime = ent->s.apos.trDuration * phase;
	ent->s.apos.trType = TR_SINE;
	ent->s.apos.trDelta[2] = speed;
}

//Blaze: Merged into func_breakable in g_misc.c

/*
// JBravo: adding for func_explosive
void SP_func_explosive (gentity_t *ent)
{
	G_SpawnInt( "material", "1", &ent->material );
	G_SpawnInt( "tension", "100", &ent->tension );
	G_SpawnInt( "bounce", "5", &ent->bounce );
	G_SpawnInt( "health", "100", &ent->health );
	G_SpawnInt( "size", "10", &ent->size );
	G_SpawnInt( "mass", "100", &ent->mass );

	ent->takedamage = qtrue;
	ent->die = func_explosive_die;
	if (!ent->health) {
		ent->health = 2;
	}

	if (!ent->damage) {
		ent->damage = 2;
	}
	VectorCopy( ent->s.origin, ent->pos1 );

	trap_SetBrushModel( ent, ent->model );
	InitMover( ent );

//	VectorSubtract( ent->r.maxs, ent->r.mins, ent->s.origin );
	VectorCopy( ent->s.pos.trBase, ent->s.origin );*/
/*	VectorCopy( ent->s.origin, ent->s.pos.trBase );
	VectorCopy( ent->s.pos.trBase, ent->r.currentOrigin );
	VectorCopy( ent->s.apos.trBase, ent->r.currentAngles );
	VectorCopy( ent->s.origin, ent->r.currentOrigin );		*/
/*
	ent->s.origin[0] = ent->r.mins[0] + (0.5 * (ent->r.maxs[0] - ent->r.mins[0]));
	ent->s.origin[1] = ent->r.mins[1] + (0.5 * (ent->r.maxs[1] - ent->r.mins[1]));
	ent->s.origin[2] = ent->r.mins[2] + (0.5 * (ent->r.maxs[2] - ent->r.mins[2]));

	ent->s.powerups = ((ent->material << 12) & 0xF000) |
			((ent->tension << 8) & 0x0F00) |
			((ent->bounce << 4) & 0x00F0) |
			((ent->size) & 0x000F);

	trap_LinkEntity( ent );
	G_Printf("at : %s %s Material (%d)\n", vtos(ent->r.currentAngles), vtos(ent->r.currentOrigin ), ent->material );
}
*/

