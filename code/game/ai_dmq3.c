//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.56  2005/02/15 16:33:39  makro
// Tons of updates (entity tree attachment system, UI vectors)
//
// Revision 1.55  2003/03/09 21:30:38  jbravo
// Adding unlagged.   Still needs work.
//
// Revision 1.54  2003/02/27 07:33:58  jbravo
// Bots stfy about flags.  Its cases.  Teamname fixes. TP style TP fixes.
//
// Revision 1.53  2003/01/08 04:46:26  jbravo
// Wrote a new hackish model replacement system
//
// Revision 1.52  2002/11/17 20:14:15  jbravo
// Itembanning added
//
// Revision 1.51  2002/09/29 16:06:44  jbravo
// Work done at the HPWorld expo
//
// Revision 1.50  2002/07/22 06:34:46  niceass
// cleaned up the powerup code
//
// Revision 1.49  2002/07/02 20:22:35  jbravo
// Changed the files to use the right ui.
//
// Revision 1.48  2002/07/01 19:55:50  makro
// Reorganized things a little
//
// Revision 1.47  2002/07/01 19:20:46  makro
// Bots now use semi-auto when firing the mk23 from long range
//
// Revision 1.46  2002/06/16 20:06:13  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.45  2002/06/16 17:37:59  jbravo
// Removed the MISSIONPACK ifdefs and missionpack only code.
//
// Revision 1.44  2002/06/15 15:02:05  makro
// Recoded AI for weapon mode switching. Bots can now zoom with the sg
//
// Revision 1.43  2002/06/11 14:03:04  makro
// Forgot (), heh
//
// Revision 1.42  2002/06/11 13:42:54  makro
// Added a time limit for changing weapon modes for bots
//
// Revision 1.41  2002/06/06 20:04:10  makro
// Checking teams
//
// Revision 1.40  2002/06/01 13:37:02  makro
// Tweaked bandaging code
//
// Revision 1.39  2002/05/31 18:17:10  makro
// Bot stuff. Added a server command that prints a line to a client
// and everyone who is spectating him
//
// Revision 1.38  2002/05/30 21:18:28  makro
// Bots should reload/bandage when roaming around
// Added "pathtarget" key to all the entities
//
// Revision 1.37  2002/05/27 06:47:22  niceass
// removed some kamakazi stuff
//
// Revision 1.36  2002/05/23 18:37:50  makro
// Bots should crouch more often when they attack with a SSG
// Made this depend on skill. Also, elevator stuff
//
// Revision 1.35  2002/05/19 15:43:51  makro
// Bots now know about weapon modes. Just for grenades so far.
//
// Revision 1.34  2002/05/18 14:52:16  makro
// Bot stuff. Other stuff. Just... stuff :p
//
// Revision 1.33  2002/05/11 19:18:20  makro
// Sand surfaceparm
//
// Revision 1.32  2002/05/11 14:22:06  makro
// Func_statics now reset at the beginning of each round
//
// Revision 1.31  2002/05/11 12:45:25  makro
// Spectators can go through breakables and doors with
// a targetname or health. Bots should crouch more/jump less
// often when attacking at long range
//
// Revision 1.30  2002/05/10 13:21:53  makro
// Mainly bot stuff. Also fixed a couple of crash bugs
//
// Revision 1.29  2002/05/05 15:18:02  makro
// Fixed some crash bugs. Bot stuff. Triggerable func_statics.
// Made flags only spawn in CTF mode
//
// Revision 1.28  2002/05/04 16:13:04  makro
// Bots
//
// Revision 1.27  2002/05/04 01:21:47  makro
// Crash bug :/
//
// Revision 1.26  2002/05/04 01:03:42  makro
// Bots
//
// Revision 1.25  2002/05/03 18:09:19  makro
// Bot stuff. Jump kicks
//
// Revision 1.24  2002/05/02 23:05:25  makro
// Loading screen. Jump kicks. Bot stuff
//
// Revision 1.23  2002/05/02 12:44:58  makro
// Customizable color for the loading screen text. Bot stuff
//
// Revision 1.22  2002/05/02 00:12:22  makro
// Improved reloading and ammo handling for akimbo/hc
//
// Revision 1.21  2002/05/01 05:32:45  makro
// Bots reload akimbos/handcannons. Also, they can decide whether
// or not an item on the ground is better than theirs
//
// Revision 1.20  2002/04/30 12:14:53  makro
// Fixed a small warning
//
// Revision 1.19  2002/04/30 11:54:37  makro
// Bots rule ! Also, added clips to give all. Maybe some other things
//
// Revision 1.18  2002/04/20 15:03:47  makro
// More footstep sounds, a few other things
//
// Revision 1.17  2002/04/06 21:42:19  makro
// Changes to bot code. New surfaceparm system.
//
// Revision 1.16  2002/04/05 18:52:26  makro
// Cleaned things up a bit
//
// Revision 1.15  2002/04/04 18:06:44  makro
// Improved door code. Bots reply to radio treport from teammates.
// Improved reloading code.
//
// Revision 1.14  2002/04/03 17:46:14  makro
// Fixed one more thing
//
// Revision 1.13  2002/04/03 17:39:36  makro
// Made bots handle incoming radio spam better
//
// Revision 1.12  2002/04/03 16:33:20  makro
// Bots now respond to radio commands
//
// Revision 1.11  2002/04/01 12:45:54  makro
// Changed some weapon names
//
// Revision 1.9  2002/03/31 19:16:56  makro
// Bandaging, reloading, opening rotating doors (still needs a lot of work),
// shooting breakables
//
// Revision 1.8  2002/03/18 12:25:10  jbravo
// Live players dont get fraglines, except their own. Cleanups and some
// hacks to get bots to stop using knives only.
//
// Revision 1.7  2002/01/11 20:20:58  jbravo
// Adding TP to main branch
//
// Revision 1.6  2002/01/11 19:48:29  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.5  2001/12/31 16:28:41  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//

/*****************************************************************************
 * name:		ai_dmq3.c
 *
 * desc:		Quake3 bot AI
 *
 * $Archive: /MissionPack/code/game/ai_dmq3.c $
 * $Author$ 
 * $Revision$
 * $Modtime: 11/28/00 9:12a $
 * $Date$
 *
 *****************************************************************************/

// JBravo: Here be dragons.  ioquake3's ai_dmq3.c rev 2116 meight have something for us.

#include "g_local.h"
#include "../botlib/botlib.h"
#include "../botlib/be_aas.h"
#include "../botlib/be_ea.h"
#include "../botlib/be_ai_char.h"
#include "../botlib/be_ai_chat.h"
#include "../botlib/be_ai_gen.h"
#include "../botlib/be_ai_goal.h"
#include "../botlib/be_ai_move.h"
#include "../botlib/be_ai_weap.h"
//
#include "ai_main.h"
#include "ai_dmq3.h"
#include "ai_chat.h"
#include "ai_cmd.h"
#include "ai_dmnet.h"
#include "ai_team.h"
//
#include "chars.h"		//characteristics
#include "inv.h"		//indexes into the inventory
#include "syn.h"		//synonyms
#include "match.h"		//string matching types and vars

// for the voice chats

//Blaze: was there a extra ../ here?
#include "../ui/menudef.h"

//Makro - to get rid of the warnings
void Cmd_Bandage(gentity_t * ent);
void G_Say(gentity_t * ent, gentity_t * target, int mode, const char *chatText);
gentity_t *SelectRandomDeathmatchSpawnPoint(void);
void Cmd_New_Weapon(gentity_t * ent);

// from aasfile.h
#define AREACONTENTS_MOVER				1024
#define AREACONTENTS_MODELNUMSHIFT		24
#define AREACONTENTS_MAXMODELNUM		0xFF
#define AREACONTENTS_MODELNUM			(AREACONTENTS_MAXMODELNUM << AREACONTENTS_MODELNUMSHIFT)

#define IDEAL_ATTACKDIST			140

#define MAX_WAYPOINTS		128
//
bot_waypoint_t botai_waypoints[MAX_WAYPOINTS];
bot_waypoint_t *botai_freewaypoints;

//NOTE: not using a cvars which can be updated because the game should be reloaded anyway
int gametype;			//game type

vmCvar_t bot_grapple;
vmCvar_t bot_rocketjump;
vmCvar_t bot_fastchat;
vmCvar_t bot_nochat;
vmCvar_t bot_testrchat;
vmCvar_t bot_challenge;
vmCvar_t bot_predictobstacles;
vmCvar_t g_spSkill;

extern vmCvar_t bot_developer;

vec3_t lastteleport_origin;	//last teleport event origin
float lastteleport_time;	//last teleport event time
int max_bspmodelindex;		//maximum BSP model index

//CTF flag goals
bot_goal_t ctf_redflag;
bot_goal_t ctf_blueflag;

#define MAX_ALTROUTEGOALS		32

int altroutegoals_setup;
aas_altroutegoal_t red_altroutegoals[MAX_ALTROUTEGOALS];
int red_numaltroutegoals;
aas_altroutegoal_t blue_altroutegoals[MAX_ALTROUTEGOALS];
int blue_numaltroutegoals;

//Makro - the vector located on the line from src to dest dist units away
void VectorTargetDist(vec3_t src, vec3_t dest, int dist, vec3_t final)
{
	VectorSubtract(src, dest, final);
	VectorNormalize(final);
	VectorMA(src, dist, final, final);
	//VectorScale(final, dist, final);
	//VectorAdd(final, src, final);
}

/*
==================
RQ3_Bot_ClipsForWeapon

Added by Makro
==================
*/
int RQ3_Bot_ClipsForWeapon(bot_state_t * bs, int weapon)
{
	switch (weapon) {
	case WP_PISTOL:
		return bs->inventory[INVENTORY_PISTOLCLIP];
		break;
	case WP_AKIMBO:
		return bs->inventory[INVENTORY_AKIMBOCLIP];
		break;
	case WP_M3:
		return bs->inventory[INVENTORY_M3CLIP];
		break;
	case WP_HANDCANNON:
		return bs->inventory[INVENTORY_HANDCANNONCLIP];
		break;
	case WP_MP5:
		return bs->inventory[INVENTORY_MP5CLIP];
		break;
	case WP_M4:
		return bs->inventory[INVENTORY_M4CLIP];
		break;
	case WP_SSG3000:
		return bs->inventory[INVENTORY_SSG3000CLIP];
		break;
	default:
		return 0;
		break;
	}
}

/*
==================
RQ3_Bot_CanReload

Added by Makro
==================
*/
qboolean RQ3_Bot_CanReload(bot_state_t * bs, int weapon)
{
	int clips = RQ3_Bot_ClipsForWeapon(bs, weapon);

	//If no clips or not a valid weapon
	if (!clips || !(bs->cur_ps.stats[STAT_WEAPONS] & (1 << weapon)))
		return qfalse;

	if (weapon == WP_AKIMBO || weapon == WP_HANDCANNON)
		return (clips >= 2);
	else
		return qtrue;
}

/*
==================
BotAttack

Added by Makro
==================
*/
void BotAttack(bot_state_t * bs)
{

	//Makro - if the weapon isn't ready, stop
	if (bs->cur_ps.weaponstate != WEAPON_READY) {
		return;
	}
	//If the gun is empty
	if ((bs->cur_ps.ammo[bs->cur_ps.weapon]) == 0) {
		//If the bot has extra ammo
		if (RQ3_Bot_CanReload(bs, bs->cur_ps.weapon) >= 1) {
			//Cmd_Reload( &g_entities[bs->entitynum] );
			trap_EA_Action(bs->client, ACTION_AFFIRMATIVE);
#ifdef DEBUG
			BotAI_Print(PRT_MESSAGE, "empty weapon (%i), reloading\n", bs->cur_ps.weapon);
#endif				//DEBUG
		}
	} else {
		//Gun is not empty
		//trap_EA_Attack(bs->client);
		trap_EA_Action(bs->client, ACTION_ATTACK);
	}
}

/*
==================
BotMoveTo

Added by Makro
==================
*/
bot_moveresult_t BotMoveTo(bot_state_t * bs, vec3_t dest)
{
	bot_goal_t goal;
	bot_moveresult_t moveresult;

	//create goal
	goal.entitynum = 0;
	VectorCopy(dest, goal.origin);
	VectorSet(goal.mins, -8, -8, -8);
	VectorSet(goal.maxs, 8, 8, 8);
	//VectorAdd(goal.mins, goal.origin, goal.mins);
	//VectorAdd(goal.maxs, goal.origin, goal.maxs);
	goal.areanum = trap_AAS_PointAreaNum(goal.origin);
	//initialize the movement state
	BotSetupForMovement(bs);
	//trap_BotMoveInDirection(bs->ms, dir, dist, MOVE_RUN);
	//trap_BotPushGoal(bs->gs, &goal);
	//move towards the goal
	trap_BotMoveToGoal(&moveresult, bs->ms, &goal, bs->tfl);
	//if movement failed
	if (moveresult.failure) {
		//G_Printf("BotMoveTo: moveresult.failure = 1\n");
		//G_Printf("BotMoveTo: moveresult.blocked = %i\n", moveresult.blocked);
		//G_Printf("BotMoveTo: moveresult.type = %i\n", moveresult.type);
		//reset the avoid reach, otherwise bot is stuck in current area
		trap_BotResetAvoidReach(bs->ms);
		if (bs->activatestack != NULL)
			bs->activatestack->time = 0;
	}
	//G_Printf("BotMoveTo: moveresult.flags = %i\n", moveresult.flags);
	return moveresult;
}

/*
==================
BotMoveTowardsEnt

Added by Makro
==================
*/
void BotMoveTowardsEnt(bot_state_t * bs, vec3_t dest, int dist)
{
	vec3_t dir;

/*
	VectorTargetDist(bs->origin, dest, dist, dir);
	//dir[2] = bs->origin[2];
	BotMoveTo(bs, dir);
*/
	VectorSubtract(dest, bs->origin, dir);
	VectorNormalize(dir);
	BotSetupForMovement(bs);
	trap_BotMoveInDirection(bs->ms, dir, 400, MOVE_WALK);
}

/*
==================
RQ3_Bot_GetWeaponMode

Added by Makro
==================
*/
int RQ3_Bot_GetWeaponMode(bot_state_t * bs, int weapon)
{
	switch (weapon) {
	case WP_GRENADE:
		{
			//long range
			if ((bs->cur_ps.persistant[PERS_WEAPONMODES] & RQ3_GRENMED) == RQ3_GRENMED &&
			    (bs->cur_ps.persistant[PERS_WEAPONMODES] & RQ3_GRENSHORT) == RQ3_GRENSHORT) {
				return 2;
				//medium range
			} else if ((bs->cur_ps.persistant[PERS_WEAPONMODES] & RQ3_GRENMED) == RQ3_GRENMED) {
				return 1;
				//short range
			} else {
				return 0;
			}
		}
	case WP_SSG3000:
		{
			//6x
			if ((bs->cur_ps.stats[STAT_RQ3] & RQ3_ZOOM_MED) == RQ3_ZOOM_MED &&
			    (bs->cur_ps.stats[STAT_RQ3] & RQ3_ZOOM_LOW) == RQ3_ZOOM_LOW) {
				return 3;
				//4x
			} else if ((bs->cur_ps.stats[STAT_RQ3] & RQ3_ZOOM_MED) == RQ3_ZOOM_MED) {
				return 2;
				//2x
			} else if ((bs->cur_ps.stats[STAT_RQ3] & RQ3_ZOOM_LOW) == RQ3_ZOOM_LOW) {
				return 1;
				//unzoomed
			} else {
				return 0;
			}
		}
	case WP_KNIFE:
		{
			if ((bs->cur_ps.persistant[PERS_WEAPONMODES] & RQ3_KNIFEMODE) == RQ3_KNIFEMODE) {
				//slashing
				return 0;
			} else {
				//throwing
				return 1;
			}
		}
	case WP_PISTOL:
		{
			if ((bs->cur_ps.persistant[PERS_WEAPONMODES] & RQ3_MK23MODE) == RQ3_MK23MODE) {
				//3rb
				return 1;
			} else {
				//full auto
				return 0;
			}
		}
	case WP_MP5:
		{
			if ((bs->cur_ps.persistant[PERS_WEAPONMODES] & RQ3_MP5MODE) == RQ3_MP5MODE) {
				//3rb
				return 1;
			} else {
				//normal
				return 0;
			}
		}
	case WP_M4:
		{
			if ((bs->cur_ps.persistant[PERS_WEAPONMODES] & RQ3_M4MODE) == RQ3_M4MODE) {
				//3rb
				return 1;
			} else {
				//normal
				return 0;
			}
		}
	default:
		return 0;
	}
}

/*
==================
RQ3_Bot_SetWeaponMode

Added by Makro
==================
*/
void RQ3_Bot_SetWeaponMode(bot_state_t * bs, int weapon, int mode)
{
	//int i, modeCount, oldMode, press;
	float reactionTime = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_REACTIONTIME, 0, 1);

	//invalid weapon
	if (weapon <= WP_NONE || weapon >= WP_NUM_WEAPONS)
		return;

	/* Makro - old code
	   //not holding the right weapon
	   if (weapon != bs->cur_ps.weapon)
	   return;
	 */

	//too soon ?
	//TODO: array with weapon mode change times for individual weapons ?
	if (FloatTime() < bs->weaponModeChange_time + 2 - reactionTime)
		return;

	/* Old code
	   switch (bs->cur_ps.weapon) {
	   case WP_PISTOL:
	   case WP_KNIFE:
	   modeCount = 2;
	   break;
	   case WP_MP5:
	   case WP_M4:
	   case WP_GRENADE:
	   modeCount = 3;
	   break;
	   case WP_SSG3000:
	   modeCount = 4;
	   break;
	   default:
	   modeCount = 1;
	   break;
	   }

	   //no modes available
	   if (modeCount <= 1)
	   return;

	   mode = mode % modeCount;
	   oldMode = RQ3_Bot_GetWeaponMode(bs, weapon) % modeCount;
	   press = mode - oldMode;
	   if (press < 0)
	   press += modeCount;

	   //use the weapon command "press" times
	   for (i = 0; i < press; i++) {
	   //changed it to use Slicer's new command
	   //Cmd_Weapon( &g_entities[bs->entitynum] );
	   Cmd_New_Weapon( &g_entities[bs->entitynum] );
	   }
	 */

	//new code
	bs->weapMode[weapon] = mode;

	bs->weaponModeChange_time = FloatTime();
}

/*
==================
RQ3_Bot_GetWeaponInfo

Added by Makro
==================
*/
//TODO: - set spreads here depending on what the player is doing - crouching, running etc. ?
qboolean RQ3_Bot_GetWeaponInfo(bot_state_t * bs, int weaponstate, int weapon, void *weaponinfo)
{

	//if the weapon is not valid
	if (weapon <= WP_NONE || weapon >= WP_NUM_WEAPONS) {
#ifdef DEBUG
		BotAI_Print(PRT_MESSAGE, "Bot_GetWeaponInfo: weapon number out of range (%i)\n", weapon);
#else				//DEBUG
		if (trap_Cvar_VariableIntegerValue("developer")) {
			BotAI_Print(PRT_ERROR, "Bot_GetWeaponInfo: weapon number out of range (%i)\n", weapon);
		}
		return qfalse;
#endif
	} else {
		weaponinfo_t *wi;
		int weaponMode = 0;

		trap_BotGetWeaponInfo(weaponstate, weapon, weaponinfo);
		wi = (weaponinfo_t *) weaponinfo;

		if (!wi)
			return qfalse;
		if (!wi->valid)
			return qfalse;

		weaponMode = RQ3_Bot_GetWeaponMode(bs, wi->number);
		if (wi->number == WP_GRENADE) {
			//long range
			if (weaponMode == 2) {
				wi->speed = GRENADE_LONG_SPEED;
				//medium range
			} else if (weaponMode == 1) {
				wi->speed = GRENADE_MEDIUM_SPEED;
				//short range
			} else {
				wi->speed = GRENADE_SHORT_SPEED;
			}
		}
	}
	return qtrue;
}

/*
==================
BotSetUserInfo
==================
*/
void BotSetUserInfo(bot_state_t * bs, char *key, char *value)
{
	char userinfo[MAX_INFO_STRING];

	trap_GetUserinfo(bs->client, userinfo, sizeof(userinfo));
	Info_SetValueForKey(userinfo, key, value);
	trap_SetUserinfo(bs->client, userinfo);
	ClientUserinfoChanged(bs->client);
}

/*
==================
BotGetUserInfoKey

Added by Makro
==================
*/
char *BotGetUserInfoKey(bot_state_t * bs, char *key)
{
	char userinfo[MAX_INFO_STRING];

	trap_GetUserinfo(bs->client, userinfo, sizeof(userinfo));
	return Info_ValueForKey(userinfo, key);
}

/*
==================
BotCTFCarryingFlag
==================
*/
int BotCTFCarryingFlag(bot_state_t * bs)
{
	if (gametype != GT_CTF)
		return CTF_FLAG_NONE;

	if (bs->inventory[INVENTORY_REDFLAG] > 0)
		return CTF_FLAG_RED;
	else if (bs->inventory[INVENTORY_BLUEFLAG] > 0)
		return CTF_FLAG_BLUE;
	return CTF_FLAG_NONE;
}

/*
==================
BotTeam
==================
*/
int BotTeam(bot_state_t * bs)
{
	if (bs->client < 0 || bs->client >= MAX_CLIENTS) {
		return qfalse;
	}

	if (level.clients[bs->client].sess.sessionTeam == TEAM_RED) {
		return TEAM_RED;
	} else if (level.clients[bs->client].sess.sessionTeam == TEAM_BLUE) {
		return TEAM_BLUE;
	}
	return TEAM_FREE;
}

/*
==================
BotOppositeTeam
==================
*/
int BotOppositeTeam(bot_state_t * bs)
{
	switch (BotTeam(bs)) {
	case TEAM_RED:
		return TEAM_BLUE;
	case TEAM_BLUE:
		return TEAM_RED;
	default:
		return TEAM_FREE;
	}
}

/*
==================
BotEnemyFlag
==================
*/
bot_goal_t *BotEnemyFlag(bot_state_t * bs)
{
	if (BotTeam(bs) == TEAM_RED) {
		return &ctf_blueflag;
	} else {
		return &ctf_redflag;
	}
}

/*
==================
BotTeamFlag
==================
*/
bot_goal_t *BotTeamFlag(bot_state_t * bs)
{
	if (BotTeam(bs) == TEAM_RED) {
		return &ctf_redflag;
	} else {
		return &ctf_blueflag;
	}
}

/*
==================
EntityIsDead
==================
*/
qboolean EntityIsDead(aas_entityinfo_t * entinfo)
{
	playerState_t ps;

	if (entinfo->number >= 0 && entinfo->number < MAX_CLIENTS) {
		//retrieve the current client state
		if (!BotAI_GetClientState(entinfo->number, &ps)) {
			return qfalse;
		}
		//Makro - added health check
		if (ps.pm_type != PM_NORMAL || ps.stats[STAT_HEALTH] <= 0)
			return qtrue;
	}
	return qfalse;
}

/*
==================
EntityCarriesFlag
==================
*/
qboolean EntityCarriesFlag(aas_entityinfo_t * entinfo)
{
	if (entinfo->powerups & (1 << PW_REDFLAG))
		return qtrue;
	if (entinfo->powerups & (1 << PW_BLUEFLAG))
		return qtrue;
	return qfalse;
}

/*
==================
EntityIsInvisible
==================
*/
qboolean EntityIsInvisible(aas_entityinfo_t * entinfo)
{
	// the flag is always visible
	if (EntityCarriesFlag(entinfo)) {
		return qfalse;
	}

	return qfalse;
}

/*
==================
EntityIsShooting
==================
*/
qboolean EntityIsShooting(aas_entityinfo_t * entinfo)
{
	if (entinfo->flags & EF_FIRING) {
		return qtrue;
	}
	return qfalse;
}

/*
==================
EntityIsChatting
==================
*/
qboolean EntityIsChatting(aas_entityinfo_t * entinfo)
{
	if (entinfo->flags & EF_TALK) {
		return qtrue;
	}
	return qfalse;
}

/*
==================
EntityHasQuad
==================
*/
qboolean EntityHasQuad(aas_entityinfo_t * entinfo)
{
	return qfalse;
}

/*
==================
BotRememberLastOrderedTask
==================
*/
void BotRememberLastOrderedTask(bot_state_t * bs)
{
	if (!bs->ordered) {
		return;
	}
	bs->lastgoal_decisionmaker = bs->decisionmaker;
	bs->lastgoal_ltgtype = bs->ltgtype;
	memcpy(&bs->lastgoal_teamgoal, &bs->teamgoal, sizeof(bot_goal_t));
	bs->lastgoal_teammate = bs->teammate;
}

/*
==================
BotSetTeamStatus
==================
*/
void BotSetTeamStatus(bot_state_t * bs)
{
}

/*
==================
BotSetLastOrderedTask
==================
*/
int BotSetLastOrderedTask(bot_state_t * bs)
{

	if (gametype == GT_CTF) {
		// don't go back to returning the flag if it's at the base
		if (bs->lastgoal_ltgtype == LTG_RETURNFLAG) {
			if (BotTeam(bs) == TEAM_RED) {
				if (bs->redflagstatus == 0) {
					bs->lastgoal_ltgtype = 0;
				}
			} else {
				if (bs->blueflagstatus == 0) {
					bs->lastgoal_ltgtype = 0;
				}
			}
		}
	}

	if (bs->lastgoal_ltgtype) {
		bs->decisionmaker = bs->lastgoal_decisionmaker;
		bs->ordered = qtrue;
		bs->ltgtype = bs->lastgoal_ltgtype;
		memcpy(&bs->teamgoal, &bs->lastgoal_teamgoal, sizeof(bot_goal_t));
		bs->teammate = bs->lastgoal_teammate;
		bs->teamgoal_time = FloatTime() + 300;
		BotSetTeamStatus(bs);
		//
		if (gametype == GT_CTF) {
			if (bs->ltgtype == LTG_GETFLAG) {
				bot_goal_t *tb, *eb;
				int tt, et;

				tb = BotTeamFlag(bs);
				eb = BotEnemyFlag(bs);
				tt = trap_AAS_AreaTravelTimeToGoalArea(bs->areanum, bs->origin, tb->areanum,
								       TFL_DEFAULT);
				et = trap_AAS_AreaTravelTimeToGoalArea(bs->areanum, bs->origin, eb->areanum,
								       TFL_DEFAULT);
				// if the travel time towards the enemy base is larger than towards our base
				if (et > tt) {
					//get an alternative route goal towards the enemy base
					BotGetAlternateRouteGoal(bs, BotOppositeTeam(bs));
				}
			}
		}
		return qtrue;
	}
	return qfalse;
}

/*
==================
BotRefuseOrder
==================
*/
void BotRefuseOrder(bot_state_t * bs)
{
	if (!bs->ordered)
		return;
	// if the bot was ordered to do something
	if (bs->order_time && bs->order_time > FloatTime() - 10) {
		trap_EA_Action(bs->client, ACTION_NEGATIVE);
		BotVoiceChat(bs, bs->decisionmaker, VOICECHAT_NO);
		bs->order_time = 0;
	}
}

/*
==================
BotCTFSeekGoals
==================
*/
void BotCTFSeekGoals(bot_state_t * bs)
{
	float rnd, l1, l2;
	int flagstatus, c;
	vec3_t dir;
	aas_entityinfo_t entinfo;

	//when carrying a flag in ctf the bot should rush to the base
	if (BotCTFCarryingFlag(bs)) {
		//if not already rushing to the base
		if (bs->ltgtype != LTG_RUSHBASE) {
			BotRefuseOrder(bs);
			bs->ltgtype = LTG_RUSHBASE;
			bs->teamgoal_time = FloatTime() + CTF_RUSHBASE_TIME;
			bs->rushbaseaway_time = 0;
			bs->decisionmaker = bs->client;
			bs->ordered = qfalse;
			//
			switch (BotTeam(bs)) {
			case TEAM_RED:
				VectorSubtract(bs->origin, ctf_blueflag.origin, dir);
				break;
			case TEAM_BLUE:
				VectorSubtract(bs->origin, ctf_redflag.origin, dir);
				break;
			default:
				VectorSet(dir, 999, 999, 999);
				break;
			}
			// if the bot picked up the flag very close to the enemy base
			if (VectorLength(dir) < 128) {
				// get an alternative route goal through the enemy base
				BotGetAlternateRouteGoal(bs, BotOppositeTeam(bs));
			} else {
				// don't use any alt route goal, just get the hell out of the base
				bs->altroutegoal.areanum = 0;
			}
			BotSetUserInfo(bs, "teamtask", va("%d", TEAMTASK_OFFENSE));
			BotVoiceChat(bs, -1, VOICECHAT_IHAVEFLAG);
		} else if (bs->rushbaseaway_time > FloatTime()) {
			if (BotTeam(bs) == TEAM_RED)
				flagstatus = bs->redflagstatus;
			else
				flagstatus = bs->blueflagstatus;
			//if the flag is back
			if (flagstatus == 0) {
				bs->rushbaseaway_time = 0;
			}
		}
		return;
	}
	// if the bot decided to follow someone
	if (bs->ltgtype == LTG_TEAMACCOMPANY && !bs->ordered) {
		// if the team mate being accompanied no longer carries the flag
		BotEntityInfo(bs->teammate, &entinfo);
		if (!EntityCarriesFlag(&entinfo)) {
			bs->ltgtype = 0;
		}
	}
	//
	if (BotTeam(bs) == TEAM_RED)
		flagstatus = bs->redflagstatus * 2 + bs->blueflagstatus;
	else
		flagstatus = bs->blueflagstatus * 2 + bs->redflagstatus;
	//if our team has the enemy flag and our flag is at the base
	if (flagstatus == 1) {
		//
		if (bs->owndecision_time < FloatTime()) {
			//if Not defending the base already
			if (!(bs->ltgtype == LTG_DEFENDKEYAREA &&
			      (bs->teamgoal.number == ctf_redflag.number ||
			       bs->teamgoal.number == ctf_blueflag.number))) {
				//if there is avisible team mate flag carrier
				c = BotTeamFlagCarrierVisible(bs);
				if (c >= 0 &&
				    // and not already following the team mate flag carrier
				    (bs->ltgtype != LTG_TEAMACCOMPANY || bs->teammate != c)) {
					//
					BotRefuseOrder(bs);
					//follow the flag carrier
					bs->decisionmaker = bs->client;
					bs->ordered = qfalse;
					//the team mate
					bs->teammate = c;
					//last time the team mate was visible
					bs->teammatevisible_time = FloatTime();
					//no message
					bs->teammessage_time = 0;
					//no arrive message
					bs->arrive_time = 1;
					//
					BotVoiceChat(bs, bs->teammate, VOICECHAT_ONFOLLOW);
					//get the team goal time
					bs->teamgoal_time = FloatTime() + TEAM_ACCOMPANY_TIME;
					bs->ltgtype = LTG_TEAMACCOMPANY;
					bs->formation_dist = 3.5 * 32;	//3.5 meter
					BotSetTeamStatus(bs);
					bs->owndecision_time = FloatTime() + 5;
				}
			}
		}
		return;
	}
	//if the enemy has our flag
	else if (flagstatus == 2) {
		//
		if (bs->owndecision_time < FloatTime()) {
			//if enemy flag carrier is visible
			c = BotEnemyFlagCarrierVisible(bs);
			if (c >= 0) {
				//FIXME: fight enemy flag carrier
			}
			//if not already doing something important
			if (bs->ltgtype != LTG_GETFLAG &&
			    bs->ltgtype != LTG_RETURNFLAG &&
			    bs->ltgtype != LTG_TEAMHELP &&
			    bs->ltgtype != LTG_TEAMACCOMPANY &&
			    bs->ltgtype != LTG_CAMPORDER && bs->ltgtype != LTG_PATROL && bs->ltgtype != LTG_GETITEM) {

				BotRefuseOrder(bs);
				bs->decisionmaker = bs->client;
				bs->ordered = qfalse;
				//
				if (random() < 0.5) {
					//go for the enemy flag
					bs->ltgtype = LTG_GETFLAG;
				} else {
					bs->ltgtype = LTG_RETURNFLAG;
				}
				//no team message
				bs->teammessage_time = 0;
				//set the time the bot will stop getting the flag
				bs->teamgoal_time = FloatTime() + CTF_GETFLAG_TIME;
				//get an alternative route goal towards the enemy base
				BotGetAlternateRouteGoal(bs, BotOppositeTeam(bs));
				//
				BotSetTeamStatus(bs);
				bs->owndecision_time = FloatTime() + 5;
			}
		}
		return;
	}
	//if both flags Not at their bases
	else if (flagstatus == 3) {
		//
		if (bs->owndecision_time < FloatTime()) {
			// if not trying to return the flag and not following the team flag carrier
			if (bs->ltgtype != LTG_RETURNFLAG && bs->ltgtype != LTG_TEAMACCOMPANY) {
				//
				c = BotTeamFlagCarrierVisible(bs);
				// if there is a visible team mate flag carrier
				if (c >= 0) {
					BotRefuseOrder(bs);
					//follow the flag carrier
					bs->decisionmaker = bs->client;
					bs->ordered = qfalse;
					//the team mate
					bs->teammate = c;
					//last time the team mate was visible
					bs->teammatevisible_time = FloatTime();
					//no message
					bs->teammessage_time = 0;
					//no arrive message
					bs->arrive_time = 1;
					//
					BotVoiceChat(bs, bs->teammate, VOICECHAT_ONFOLLOW);
					//get the team goal time
					bs->teamgoal_time = FloatTime() + TEAM_ACCOMPANY_TIME;
					bs->ltgtype = LTG_TEAMACCOMPANY;
					bs->formation_dist = 3.5 * 32;	//3.5 meter
					//
					BotSetTeamStatus(bs);
					bs->owndecision_time = FloatTime() + 5;
				} else {
					BotRefuseOrder(bs);
					bs->decisionmaker = bs->client;
					bs->ordered = qfalse;
					//get the enemy flag
					bs->teammessage_time = FloatTime() + 2 * random();
					//get the flag
					bs->ltgtype = LTG_RETURNFLAG;
					//set the time the bot will stop getting the flag
					bs->teamgoal_time = FloatTime() + CTF_RETURNFLAG_TIME;
					//get an alternative route goal towards the enemy base
					BotGetAlternateRouteGoal(bs, BotOppositeTeam(bs));
					//
					BotSetTeamStatus(bs);
					bs->owndecision_time = FloatTime() + 5;
				}
			}
		}
		return;
	}
	// don't just do something wait for the bot team leader to give orders
	if (BotTeamLeader(bs)) {
		return;
	}
	// if the bot is ordered to do something
	if (bs->lastgoal_ltgtype) {
		bs->teamgoal_time += 60;
	}
	// if the bot decided to do something on it's own and has a last ordered goal
	if (!bs->ordered && bs->lastgoal_ltgtype) {
		bs->ltgtype = 0;
	}
	//if already a CTF or team goal
	if (bs->ltgtype == LTG_TEAMHELP ||
	    bs->ltgtype == LTG_TEAMACCOMPANY ||
	    bs->ltgtype == LTG_DEFENDKEYAREA ||
	    bs->ltgtype == LTG_GETFLAG ||
	    bs->ltgtype == LTG_RUSHBASE ||
	    bs->ltgtype == LTG_RETURNFLAG ||
	    bs->ltgtype == LTG_CAMPORDER ||
	    bs->ltgtype == LTG_PATROL ||
	    bs->ltgtype == LTG_GETITEM || bs->ltgtype == LTG_MAKELOVE_UNDER || bs->ltgtype == LTG_MAKELOVE_ONTOP) {
		return;
	}
	//
	if (BotSetLastOrderedTask(bs))
		return;
	//
	if (bs->owndecision_time > FloatTime())
		return;;
	//if the bot is roaming
	if (bs->ctfroam_time > FloatTime())
		return;
	//if the bot has anough aggression to decide what to do
	if (BotAggression(bs) < 50)
		return;
	//set the time to send a message to the team mates
	bs->teammessage_time = FloatTime() + 2 * random();
	//
	if (bs->teamtaskpreference & (TEAMTP_ATTACKER | TEAMTP_DEFENDER)) {
		if (bs->teamtaskpreference & TEAMTP_ATTACKER) {
			l1 = 0.7f;
		} else {
			l1 = 0.2f;
		}
		l2 = 0.9f;
	} else {
		l1 = 0.4f;
		l2 = 0.7f;
	}
	//get the flag or defend the base
	rnd = random();
	if (rnd < l1 && ctf_redflag.areanum && ctf_blueflag.areanum) {
		bs->decisionmaker = bs->client;
		bs->ordered = qfalse;
		bs->ltgtype = LTG_GETFLAG;
		//set the time the bot will stop getting the flag
		bs->teamgoal_time = FloatTime() + CTF_GETFLAG_TIME;
		//get an alternative route goal towards the enemy base
		BotGetAlternateRouteGoal(bs, BotOppositeTeam(bs));
		BotSetTeamStatus(bs);
	} else if (rnd < l2 && ctf_redflag.areanum && ctf_blueflag.areanum) {
		bs->decisionmaker = bs->client;
		bs->ordered = qfalse;
		//
		if (BotTeam(bs) == TEAM_RED)
			memcpy(&bs->teamgoal, &ctf_redflag, sizeof(bot_goal_t));
		else
			memcpy(&bs->teamgoal, &ctf_blueflag, sizeof(bot_goal_t));
		//set the ltg type
		bs->ltgtype = LTG_DEFENDKEYAREA;
		//set the time the bot stops defending the base
		bs->teamgoal_time = FloatTime() + TEAM_DEFENDKEYAREA_TIME;
		bs->defendaway_time = 0;
		BotSetTeamStatus(bs);
	} else {
		bs->ltgtype = 0;
		//set the time the bot will stop roaming
		bs->ctfroam_time = FloatTime() + CTF_ROAM_TIME;
		BotSetTeamStatus(bs);
	}
	bs->owndecision_time = FloatTime() + 5;
#ifdef DEBUG
	BotPrintTeamGoal(bs);
#endif				//DEBUG
}

/*
==================
BotCTFRetreatGoals
==================
*/
void BotCTFRetreatGoals(bot_state_t * bs)
{
	//when carrying a flag in ctf the bot should rush to the base
	if (BotCTFCarryingFlag(bs)) {
		//if not already rushing to the base
		if (bs->ltgtype != LTG_RUSHBASE) {
			BotRefuseOrder(bs);
			bs->ltgtype = LTG_RUSHBASE;
			bs->teamgoal_time = FloatTime() + CTF_RUSHBASE_TIME;
			bs->rushbaseaway_time = 0;
			bs->decisionmaker = bs->client;
			bs->ordered = qfalse;
			BotSetTeamStatus(bs);
		}
	}
}

/*
==================
BotRQ3TPSeekGoals

Added by Makro  
==================
*/
void BotRQ3TPSeekGoals(bot_state_t * bs)
{
/*
	int		firstBot = -1, firstHuman = -1, leader = -1, i;
	static int maxclients;

  //if the bot already has a goal
	if (bs->ltgtype || bs->ltg_time < FloatTime())
		return;

	if (!maxclients)
		maxclients = trap_Cvar_VariableIntegerValue("sv_maxclients");
	

	//find the first human/bot teammates
	for ( i=0; i < MAX_CLIENTS && i < maxclients; i++ ) {
		if ( !(g_entities[i].inuse) || !(g_entities[i].client) )
			continue;
		if (!BotSameTeam(bs, i))
			continue;
		if (g_entities[i].r.svFlags & SVF_BOT) {
			if (i != bs->entitynum)
				firstBot = i;
		} else {
			firstHuman = i;
		}
		if (firstHuman && firstBot)
			break;
	}

	if (firstHuman != -1)
		leader = firstHuman;
	else if (firstBot != -1)
		leader = firstBot;
	else
		return;

	//the team mate
	bs->teammate = leader;
	bs->decisionmaker = bs->client;
	bs->ordered = qfalse;
	//no message
	bs->teammessage_time = 0;
	//no arrive message
	//bs->arrive_time = 0;
	//
	bs->ctfroam_time = FloatTime() + CTF_ROAM_TIME;
	BotVoiceChat(bs, bs->teammate, VOICECHAT_ONFOLLOW);
	//get the team goal time
	bs->teamgoal_time = FloatTime() + TEAM_ACCOMPANY_TIME;
	bs->ltgtype = LTG_TEAMACCOMPANY;
	bs->formation_dist = 3.5 * 32;		//3.5 meter
	BotSetTeamStatus(bs);
*/
	return;
}

/*
==================
BotTeamGoals
==================
*/
void BotTeamGoals(bot_state_t * bs, int retreat)
{
	//Makro - unused
	//bot_goal_t *goal;
	if (retreat) {
		if (gametype == GT_CTF) {
			BotCTFRetreatGoals(bs);
		}
	} else {
		if (gametype == GT_CTF) {
			//decide what to do in CTF mode
			BotCTFSeekGoals(bs);
		}
		//Makro - decide what to do in TP mode
		else if (gametype == GT_TEAMPLAY) {
			BotRQ3TPSeekGoals(bs);
		}
	}
	// reset the order time which is used to see if
	// we decided to refuse an order
	bs->order_time = 0;
}

/*
==================
BotPointAreaNum
==================
*/
int BotPointAreaNum(vec3_t origin)
{
	int areanum, numareas, areas[10];
	vec3_t end;

	areanum = trap_AAS_PointAreaNum(origin);
	if (areanum)
		return areanum;
	VectorCopy(origin, end);
	end[2] += 10;
	numareas = trap_AAS_TraceAreas(origin, end, areas, NULL, 10);
	if (numareas > 0)
		return areas[0];
	return 0;
}

/*
==================
ClientName
==================
*/
char *ClientName(int client, char *name, int size)
{
	char buf[MAX_INFO_STRING];

	if (client < 0 || client >= MAX_CLIENTS) {
		BotAI_Print(PRT_ERROR, "ClientName: client out of range\n");
		return "[client out of range]";
	}
	trap_GetConfigstring(CS_PLAYERS + client, buf, sizeof(buf));
	strncpy(name, Info_ValueForKey(buf, "n"), size - 1);
	name[size - 1] = '\0';
	Q_CleanStr(name);
	return name;
}

/*
==================
ClientSkin
==================
*/
char *ClientSkin(int client, char *skin, int size)
{
	char buf[MAX_INFO_STRING];

	if (client < 0 || client >= MAX_CLIENTS) {
		BotAI_Print(PRT_ERROR, "ClientSkin: client out of range\n");
		return "[client out of range]";
	}
	trap_GetConfigstring(CS_PLAYERS + client, buf, sizeof(buf));
	strncpy(skin, Info_ValueForKey(buf, "model"), size - 1);
	skin[size - 1] = '\0';
	return skin;
}

/*
==================
ClientFromName
==================
*/
int ClientFromName(char *name)
{
	int i;
	char buf[MAX_INFO_STRING];

	for (i = 0; i < level.maxclients; i++) {
		trap_GetConfigstring(CS_PLAYERS + i, buf, sizeof(buf));
		Q_CleanStr(buf);
		if (!Q_stricmp(Info_ValueForKey(buf, "n"), name))
			return i;
	}
	return -1;
}

/*
==================
ClientOnSameTeamFromName
==================
*/
int ClientOnSameTeamFromName(bot_state_t * bs, char *name)
{
	int i;
	char buf[MAX_INFO_STRING];

	for (i = 0; i < level.maxclients; i++) {
		if (!BotSameTeam(bs, i))
			continue;
		trap_GetConfigstring(CS_PLAYERS + i, buf, sizeof(buf));
		Q_CleanStr(buf);
		if (!Q_stricmp(Info_ValueForKey(buf, "n"), name))
			return i;
	}
	return -1;
}

/*
==================
stristr
==================
*/
char *stristr(char *str, char *charset)
{
	int i;

	while (*str) {
		for (i = 0; charset[i] && str[i]; i++) {
			if (toupper(charset[i]) != toupper(str[i]))
				break;
		}
		if (!charset[i])
			return str;
		str++;
	}
	return NULL;
}

/*
==================
EasyClientName
==================
*/
char *EasyClientName(int client, char *buf, int size)
{
	int i;
	char *str1, *str2, *ptr, c;
	char name[128] = {0};

	ClientName(client, name, sizeof(name));
	for (i = 0; name[i]; i++)
		name[i] &= 127;
	//remove all spaces
	for (ptr = strstr(name, " "); ptr; ptr = strstr(name, " ")) {
		memmove(ptr, ptr + 1, strlen(ptr + 1) + 1);
	}
	//check for [x] and ]x[ clan names
	str1 = strstr(name, "[");
	str2 = strstr(name, "]");
	if (str1 && str2) {
		if (str2 > str1)
			memmove(str1, str2 + 1, strlen(str2 + 1) + 1);
		else
			memmove(str2, str1 + 1, strlen(str1 + 1) + 1);
	}
	//remove Mr prefix
	if ((name[0] == 'm' || name[0] == 'M') && (name[1] == 'r' || name[1] == 'R')) {
		memmove(name, name + 2, strlen(name + 2) + 1);
	}
	//only allow lower case alphabet characters
	ptr = name;
	while (*ptr) {
		c = *ptr;
		if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
			ptr++;
		} else if (c >= 'A' && c <= 'Z') {
			*ptr += 'a' - 'A';
			ptr++;
		} else {
			memmove(ptr, ptr + 1, strlen(ptr + 1) + 1);
		}
	}
	strncpy(buf, name, size - 1);
	buf[size - 1] = '\0';
	return buf;
}

/*
==================
BotSynonymContext
==================
*/
int BotSynonymContext(bot_state_t * bs)
{
	int context;

	context = CONTEXT_NORMAL | CONTEXT_NEARBYITEM | CONTEXT_NAMES;
	//
	if (gametype == GT_CTF) {
		if (BotTeam(bs) == TEAM_RED)
			context |= CONTEXT_CTFREDTEAM;
		else
			context |= CONTEXT_CTFBLUETEAM;
	}
	return context;
}

/*
====================================
RQ3_Bot_WeaponFitness

Added by Makro
We have to take into account factors
that the trap calls don't seem to
====================================
*/
#define Score_M3_1		50
#define Score_M3_2		65
#define Score_M3_3		80

#define Score_HC_1		50
#define Score_HC_2		65
#define Score_HC_3		80

#define PLAYER_SIZE_X	30.0f
#define PLAYER_SIZE_Y	49.0f

float RQ3_Bot_WeaponFitness(bot_state_t * bs, int weapon)
{
	int dist = sqrt(bs->inventory[ENEMY_HORIZONTAL_DIST] * bs->inventory[ENEMY_HORIZONTAL_DIST] +
			bs->inventory[ENEMY_HEIGHT] * bs->inventory[ENEMY_HEIGHT]);
	if (dist <= 0) {
		dist = 8;
	}
	//no ammo
	if (bs->cur_ps.ammo[weapon] <= 0 && !RQ3_Bot_CanReload(bs, weapon))
		return 0;

	//psx * psy / ((hs * d / 8192) * (vs * d / 8192))
	switch (weapon) {
	case WP_PISTOL:
		return (float) PLAYER_SIZE_X *PLAYER_SIZE_Y / ((PISTOL_SPREAD * dist / 8192) *
							       (PISTOL_SPREAD * dist / 8192)) *
		    bs->inventory[INVENTORY_PISTOLAMMO] * PISTOL_DAMAGE;
	case WP_AKIMBO:
		return (float) PLAYER_SIZE_X *PLAYER_SIZE_Y / ((PISTOL_SPREAD * dist / 8192) *
							       (PISTOL_SPREAD * dist / 8192)) *
		    bs->inventory[INVENTORY_AKIMBOAMMO] * PISTOL_DAMAGE;
	case WP_M3:
		return (float) PLAYER_SIZE_X *PLAYER_SIZE_Y / ((DEFAULT_M3_HSPREAD * dist / 8192) *
							       (DEFAULT_M3_VSPREAD * dist / 8192)) *
		    bs->inventory[INVENTORY_M3AMMO] * M3_DAMAGE * 10;
	case WP_HANDCANNON:
		return (float) PLAYER_SIZE_X *PLAYER_SIZE_Y / ((DEFAULT_SHOTGUN_HSPREAD * dist / 8192) *
							       (DEFAULT_SHOTGUN_VSPREAD * dist / 8192)) *
		    bs->inventory[INVENTORY_HANDCANNONAMMO] * HANDCANNON_DAMAGE * 10;
	case WP_M4:
		return (float) PLAYER_SIZE_X *PLAYER_SIZE_Y / ((M4_SPREAD * dist / 8192) * (M4_SPREAD * dist / 8192)) *
		    bs->inventory[INVENTORY_M4AMMO] * M4_DAMAGE;
	case WP_MP5:
		return (float) PLAYER_SIZE_X *PLAYER_SIZE_Y / ((MP5_SPREAD * dist / 8192) *
							       (MP5_SPREAD * dist / 8192)) *
		    bs->inventory[INVENTORY_MP5AMMO] * MP5_DAMAGE;
	case WP_SSG3000:
		return (float) PLAYER_SIZE_X *PLAYER_SIZE_Y / ((SNIPER_SPREAD * dist / 8192) *
							       (SNIPER_SPREAD * dist / 8192)) *
		    bs->inventory[INVENTORY_SSG3000AMMO] * SNIPER_DAMAGE;
	case WP_KNIFE:
		return 0.1f;
	case WP_GRENADE:
		return 1.0f;
	default:
		return 0;
	}
}

/*
======================
RQ3_Bot_ChooseBestFightWeapon

Added by Makro
======================
*/
int RQ3_Bot_ChooseBestFightWeapon(bot_state_t * bs)
{
	/*
	   int i;

	   for (i=WP_NONE+1; i<WP_NUM_WEAPONS; i++) {
	   if ((bs->cur_ps.stats[STAT_WEAPONS] & (1 << i)) == (1 << i)) {
	   BotAI_Print(PRT_MESSAGE, "Weapon %i: %f\n", i, RQ3_Bot_WeaponFitness(bs, i));
	   }
	   }
	 */
	return trap_BotChooseBestFightWeapon(bs->ws, bs->inventory);
}

/*
==================
RQ3_Bot_ChooseWeaponMode

Added by Makro
==================
*/
void RQ3_Bot_ChooseWeaponMode(bot_state_t * bs)
{
	//distance from the enemy
	int dist;

	if (bs->enemy != -1) {
		dist = sqrt(bs->inventory[ENEMY_HORIZONTAL_DIST] * bs->inventory[ENEMY_HORIZONTAL_DIST] +
			    bs->inventory[ENEMY_HEIGHT] * bs->inventory[ENEMY_HEIGHT]);
	} else {
		dist = 8;
	}

	if (dist <= 0) {
		dist = 8;
	}

	if (bs->weaponnum == WP_GRENADE) {
		//long range
		if (dist > 800) {
			RQ3_Bot_SetWeaponMode(bs, WP_GRENADE, 2);
		//medium range
		} else if (dist > 400) {
			RQ3_Bot_SetWeaponMode(bs, WP_GRENADE, 1);
		//short range
		} else {
			RQ3_Bot_SetWeaponMode(bs, WP_GRENADE, 0);
		}
	} else if (bs->weaponnum == WP_SSG3000) {
		//2x
		if (bs->enemy != -1 && dist > 600) {
			RQ3_Bot_SetWeaponMode(bs, WP_SSG3000, 1);
		//unzoomed
		} else {
			RQ3_Bot_SetWeaponMode(bs, WP_SSG3000, 0);
		}
	} else if (bs->weaponnum == WP_PISTOL) {
		if (dist > 800) {
			//semi-auto
			RQ3_Bot_SetWeaponMode(bs, WP_PISTOL, 1);
		} else {
			//full auto
			RQ3_Bot_SetWeaponMode(bs, WP_PISTOL, 0);
		}
	}
}

/*
==================
BotChooseWeapon
==================
*/
void BotChooseWeapon(bot_state_t * bs)
{
	int newweaponnum;

	//Makro - don't change weapons while bandaging
	if (bs->cur_ps.weaponstate == WEAPON_BANDAGING) {
		return;
	}

// JBravo: Force the bot to use a pistol when he decides to go for a case.
	if (bs->ltgtype == LTG_GETFLAG) {
		bs->weaponnum = WP_PISTOL;
		RQ3_Bot_ChooseWeaponMode(bs);
	} else if (bs->cur_ps.weaponstate == WEAPON_RAISING || bs->cur_ps.weaponstate == WEAPON_DROPPING) {
		trap_EA_SelectWeapon(bs->client, bs->weaponnum);
		//Makro - choose weapon mode
		RQ3_Bot_ChooseWeaponMode(bs);
	} else {
		//Makro - new function
		//newweaponnum = trap_BotChooseBestFightWeapon(bs->ws, bs->inventory);
		newweaponnum = RQ3_Bot_ChooseBestFightWeapon(bs);
		if (bs->weaponnum != newweaponnum)
			bs->weaponchange_time = FloatTime();
// JBravo: test hack
// Makro - test unhack :P
		bs->weaponnum = newweaponnum;
		//bs->weaponnum = WP_PISTOL;
		//BotAI_Print(PRT_MESSAGE, "bs->weaponnum = %d\n", bs->weaponnum);
		trap_EA_SelectWeapon(bs->client, bs->weaponnum);
		//Makro - choose weapon mode
		RQ3_Bot_ChooseWeaponMode(bs);
	}
}

/*
==================
BotSetupForMovement
==================
*/
void BotSetupForMovement(bot_state_t * bs)
{
	bot_initmove_t initmove;

	memset(&initmove, 0, sizeof(bot_initmove_t));
	VectorCopy(bs->cur_ps.origin, initmove.origin);
	VectorCopy(bs->cur_ps.velocity, initmove.velocity);
	VectorClear(initmove.viewoffset);
	initmove.viewoffset[2] += bs->cur_ps.viewheight;
	initmove.entitynum = bs->entitynum;
	initmove.client = bs->client;
	initmove.thinktime = bs->thinktime;
	//set the onground flag
	if (bs->cur_ps.groundEntityNum != ENTITYNUM_NONE)
		initmove.or_moveflags |= MFL_ONGROUND;
	//set the teleported flag
	if ((bs->cur_ps.pm_flags & PMF_TIME_KNOCKBACK) && (bs->cur_ps.pm_time > 0)) {
		initmove.or_moveflags |= MFL_TELEPORTED;
	}
	//set the waterjump flag
	if ((bs->cur_ps.pm_flags & PMF_TIME_WATERJUMP) && (bs->cur_ps.pm_time > 0)) {
		initmove.or_moveflags |= MFL_WATERJUMP;
	}
	//set presence type
	if (bs->cur_ps.pm_flags & PMF_DUCKED)
		initmove.presencetype = PRESENCE_CROUCH;
	else
		initmove.presencetype = PRESENCE_NORMAL;
	//
	if (bs->walker > 0.5)
		initmove.or_moveflags |= MFL_WALK;
	//
	VectorCopy(bs->viewangles, initmove.viewangles);
	//
	trap_BotInitMoveState(bs->ms, &initmove);
}

/*
==================
BotCheckItemPickup
==================
*/
void BotCheckItemPickup(bot_state_t * bs, int *oldinventory)
{
}

/*
==================
BotUpdateInventory
==================
*/
void BotUpdateInventory(bot_state_t * bs)
{
	int oldinventory[MAX_ITEMS];
	gentity_t *ent = &g_entities[bs->entitynum];
	int amt = 0;

	//DEBUG STUFF
	//qboolean      showInfo = (trap_Cvar_VariableIntegerValue("bot_RQ3_report") != 0);

	memcpy(oldinventory, bs->inventory, sizeof(oldinventory));
	//armor
	bs->inventory[INVENTORY_ARMOR] = bs->cur_ps.stats[STAT_ARMOR];

	// WEAPONS //

	//Blaze: Reaction Weapons
	bs->inventory[INVENTORY_KNIFE] = (bs->cur_ps.stats[STAT_WEAPONS] & (1 << WP_KNIFE)) != 0;
	bs->inventory[INVENTORY_PISTOL] = (bs->cur_ps.stats[STAT_WEAPONS] & (1 << WP_PISTOL)) != 0;
	bs->inventory[INVENTORY_M4] = (bs->cur_ps.stats[STAT_WEAPONS] & (1 << WP_M4)) != 0;
	bs->inventory[INVENTORY_SSG3000] = (bs->cur_ps.stats[STAT_WEAPONS] & (1 << WP_SSG3000)) != 0;
	bs->inventory[INVENTORY_MP5] = (bs->cur_ps.stats[STAT_WEAPONS] & (1 << WP_MP5)) != 0;
	bs->inventory[INVENTORY_HANDCANNON] = (bs->cur_ps.stats[STAT_WEAPONS] & (1 << WP_HANDCANNON)) != 0;
	bs->inventory[INVENTORY_M3] = (bs->cur_ps.stats[STAT_WEAPONS] & (1 << WP_M3)) != 0;
	bs->inventory[INVENTORY_AKIMBO] = (bs->cur_ps.stats[STAT_WEAPONS] & (1 << WP_AKIMBO)) != 0;
	bs->inventory[INVENTORY_GRENADE] = (bs->cur_ps.stats[STAT_WEAPONS] & (1 << WP_GRENADE)) != 0;

	// CLIPS //

	//Makro - adding clip info
	//Note - this stuff is also added to the ammo info, so bots know they still have ammo for their guns
	bs->inventory[INVENTORY_KNIFECLIP] = ent->client->numClips[WP_KNIFE];
	bs->inventory[INVENTORY_PISTOLCLIP] = ent->client->numClips[WP_PISTOL];
	bs->inventory[INVENTORY_M3CLIP] = ent->client->numClips[WP_M3];
	bs->inventory[INVENTORY_SSG3000CLIP] = ent->client->numClips[WP_SSG3000];
	bs->inventory[INVENTORY_MP5CLIP] = ent->client->numClips[WP_MP5];
	bs->inventory[INVENTORY_M4CLIP] = ent->client->numClips[WP_M4];
	amt = ent->client->numClips[WP_HANDCANNON];
	if (amt < 2)
		amt = 0;
	bs->inventory[INVENTORY_HANDCANNONCLIP] = amt;
	amt = ent->client->numClips[WP_AKIMBO];
	if (amt < 2)
		amt = 0;
	bs->inventory[INVENTORY_AKIMBOCLIP] = amt;
	bs->inventory[INVENTORY_GRENADECLIP] = ent->client->numClips[WP_GRENADE];

	// AMMO //

	//Makro - clips should be taken into account
	bs->inventory[INVENTORY_PISTOLAMMO] =
	    bs->cur_ps.ammo[WP_PISTOL] + bs->inventory[INVENTORY_PISTOLCLIP] * RQ3_PISTOL_CLIP;
	bs->inventory[INVENTORY_KNIFEAMMO] = bs->cur_ps.ammo[WP_KNIFE];
	bs->inventory[INVENTORY_M4AMMO] = bs->cur_ps.ammo[WP_M4] + bs->inventory[INVENTORY_M4CLIP] * RQ3_M4_CLIP;
	bs->inventory[INVENTORY_SSG3000AMMO] = bs->cur_ps.ammo[WP_SSG3000] + bs->inventory[INVENTORY_SSG3000CLIP];
	bs->inventory[INVENTORY_MP5AMMO] = bs->cur_ps.ammo[WP_MP5] + bs->inventory[INVENTORY_MP5CLIP] * RQ3_MP5_CLIP;
	//Blaze: Same ammo for shotgun and handcannon
	//Makro - this was odd
	//bs->inventory[INVENTORY_M3AMMO] = bs->cur_ps.ammo[WP_HANDCANNON];
	//bs->inventory[INVENTORY_M3AMMO] = bs->cur_ps.ammo[WP_M3];
	bs->inventory[INVENTORY_M3AMMO] = bs->cur_ps.ammo[WP_M3] + bs->inventory[INVENTORY_M3CLIP];
	amt = bs->cur_ps.ammo[WP_HANDCANNON] + bs->inventory[INVENTORY_HANDCANNONCLIP];
	//Makro - hackish, but oh well... bots shouldn't want to use a HC when they only have one shell left
	if (amt < 2)
		amt = 0;
	bs->inventory[INVENTORY_HANDCANNONAMMO] = amt;
	//Blaze: Same ammo for Pistol and Akimbo Pistols
	//bs->inventory[INVENTORY_PISTOLAMMO] = bs->cur_ps.ammo[WP_AKIMBO];
	bs->inventory[INVENTORY_AKIMBOAMMO] =
	    bs->cur_ps.ammo[WP_AKIMBO] + bs->inventory[INVENTORY_AKIMBOCLIP] * RQ3_PISTOL_CLIP;
	bs->inventory[INVENTORY_GRENADEAMMO] = bs->cur_ps.ammo[WP_GRENADE];

//      bs->inventory[INVENTORY_BFGAMMO] = bs->cur_ps.ammo[WP_BFG];
	//powerups
	bs->inventory[INVENTORY_HEALTH] = bs->cur_ps.stats[STAT_HEALTH];
	//bs->inventory[INVENTORY_TELEPORTER] = bs->cur_ps.stats[STAT_HOLDABLE_ITEM] == MODELINDEX_TELEPORTER;
	//bs->inventory[INVENTORY_MEDKIT] = bs->cur_ps.stats[STAT_HOLDABLE_ITEM] == MODELINDEX_MEDKIT;
	bs->inventory[INVENTORY_REDFLAG] = bs->cur_ps.powerups[PW_REDFLAG] != 0;
	bs->inventory[INVENTORY_BLUEFLAG] = bs->cur_ps.powerups[PW_BLUEFLAG] != 0;

	/*
	   if (showInfo) {
	   BotAI_Print(PRT_MESSAGE, "Inventory for %s :\n-----------------\n", ent->client->pers.netname);
	   BotAI_Print(PRT_MESSAGE, "KNIFE :   %i / %i\n", bs->inventory[INVENTORY_KNIFE], bs->inventory[INVENTORY_KNIFEAMMO]);
	   BotAI_Print(PRT_MESSAGE, "PISTOL:   %i / %i\n", bs->inventory[INVENTORY_PISTOL], bs->inventory[INVENTORY_PISTOLAMMO]);
	   BotAI_Print(PRT_MESSAGE, "AKIMBO:   %i / %i\n", bs->inventory[INVENTORY_AKIMBO], bs->inventory[INVENTORY_AKIMBOAMMO]);
	   BotAI_Print(PRT_MESSAGE, "M3    :   %i / %i\n", bs->inventory[INVENTORY_M3], bs->inventory[INVENTORY_M3AMMO]);
	   BotAI_Print(PRT_MESSAGE, "HC    :   %i / %i\n", bs->inventory[INVENTORY_HANDCANNON], bs->inventory[INVENTORY_HANDCANNONAMMO]);
	   BotAI_Print(PRT_MESSAGE, "MP5   :   %i / %i\n", bs->inventory[INVENTORY_MP5], bs->inventory[INVENTORY_MP5AMMO]);
	   BotAI_Print(PRT_MESSAGE, "M4    :   %i / %i\n", bs->inventory[INVENTORY_M4], bs->inventory[INVENTORY_M4AMMO]);
	   BotAI_Print(PRT_MESSAGE, "M26 G :   %i / %i\n", bs->inventory[INVENTORY_GRENADE], bs->inventory[INVENTORY_GRENADEAMMO]);
	   trap_Cvar_Set("bot_RQ3_report", "0");
	   }
	 */
	BotCheckItemPickup(bs, oldinventory);

	//Makro - new weapon mode switching code
	if (RQ3_Bot_GetWeaponMode(bs, bs->cur_ps.weapon) != bs->weapMode[bs->cur_ps.weapon]) {
		if (bs->weaponModeClick_time + 0.1 < FloatTime()) {
			if (bs->cur_ps.weaponstate == WEAPON_READY) {
				Cmd_New_Weapon(&g_entities[bs->entitynum]);
			}
			bs->weaponModeClick_time = FloatTime();
		}
	}
}

/*
==================
BotUpdateBattleInventory
==================
*/
void BotUpdateBattleInventory(bot_state_t * bs, int enemy)
{
	vec3_t dir;
	aas_entityinfo_t entinfo;

	BotEntityInfo(enemy, &entinfo);
	VectorSubtract(entinfo.origin, bs->origin, dir);
	bs->inventory[ENEMY_HEIGHT] = (int) dir[2];
	dir[2] = 0;
	bs->inventory[ENEMY_HORIZONTAL_DIST] = (int) VectorLength(dir);
	//FIXME: add num visible enemies and num visible team mates to the inventory
}

/*
==================
RQ3_Bot_NeedToBandage

Added by Makro
==================
*/
int RQ3_Bot_NeedToBandage(bot_state_t * bs)
{
	if ((bs->cur_ps.stats[STAT_RQ3] & RQ3_LEGDAMAGE) == RQ3_LEGDAMAGE)
		return 2;
	if ((bs->cur_ps.stats[STAT_RQ3] & RQ3_BANDAGE_NEED) == RQ3_BANDAGE_NEED)
		return 1;
	return 0;
}

/*
==================
RQ3_Bot_CheckBandage

Added by Makro
==================
*/
qboolean RQ3_Bot_CheckBandage(bot_state_t * bs)
{
	qboolean doBandage = qfalse;

	if ((bs->flags & BFL_FIGHTSUICIDAL) == BFL_FIGHTSUICIDAL)
		return qfalse;

	if (bs->inventory[INVENTORY_HEALTH] > 20)
		doBandage = (random() > (float) bs->inventory[INVENTORY_HEALTH] / 100.0f);
	else
		doBandage = qtrue;

	return doBandage;
}

/*
==================
RQ3_Bot_RQ3_Bot_IdleActions

Added by Makro
==================
*/
void RQ3_Bot_IdleActions(bot_state_t * bs)
{
	int damage = RQ3_Bot_NeedToBandage(bs);
	int ammo = bs->cur_ps.ammo[bs->cur_ps.weapon];
	int weapon = bs->cur_ps.weapon;

	//float reactiontime = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_REACTIONTIME, 0, 1);

	//always unzoom SSG when idle
	if (RQ3_Bot_GetWeaponMode(bs, WP_SSG3000)) {
		RQ3_Bot_SetWeaponMode(bs, WP_SSG3000, 0);
	}
	//too soon to reload/bandage again ?
	if (bs->idleAction_time > FloatTime())
		return;

	//check if the bot needs to bandage
	if (damage && RQ3_Bot_CheckBandage(bs)) {
		if (bs->cur_ps.weaponstate != WEAPON_BANDAGING) {
			Cmd_Bandage(&g_entities[bs->entitynum]);
			bs->idleAction_time = FloatTime() + 4;
			return;
		}
	}
	//check if the bot needs to reload
	if (ammo == 0 || (weapon == WP_SSG3000 && ammo < RQ3_SSG3000_AMMO) || (weapon == WP_M3 && ammo < RQ3_M3_AMMO)) {
		if (RQ3_Bot_CanReload(bs, weapon)) {
			trap_EA_Action(bs->client, ACTION_AFFIRMATIVE);
			bs->idleAction_time = FloatTime() + 1;
			return;
		}
	}

	return;
}

/*
==================
BotBattleUseItems
==================
*/
void BotBattleUseItems(bot_state_t * bs)
{
	//Makro - bot was hit; if very low on health, bandage immediately, otherwise, bandage randomly
	/*
	   if ( bs->lastframe_health > bs->inventory[INVENTORY_HEALTH] ) {
	   if (RQ3_Bot_CheckBandage(bs))
	   //Makro - if not bandaging already
	   if (bs->cur_ps.weaponstate != WEAPON_BANDAGING) {
	   Cmd_Bandage( &g_entities[bs->entitynum] );
	   }
	   }
	 */
	//On second though, bots shouldn't bandage at all during combat

	if (bs->inventory[INVENTORY_HEALTH] < 40) {
		if (bs->inventory[INVENTORY_TELEPORTER] > 0) {
			if (!BotCTFCarryingFlag(bs)) {
				trap_EA_Use(bs->client);
			}
		}
	}
	if (bs->inventory[INVENTORY_HEALTH] < 60) {
		if (bs->inventory[INVENTORY_MEDKIT] > 0) {
			trap_EA_Use(bs->client);
		}
	}
}

/*
==================
BotSetTeleportTime
==================
*/
void BotSetTeleportTime(bot_state_t * bs)
{
	if ((bs->cur_ps.eFlags ^ bs->last_eFlags) & EF_TELEPORT_BIT) {
		bs->teleport_time = FloatTime();
	}
	bs->last_eFlags = bs->cur_ps.eFlags;
}

/*
==================
BotIsDead
==================
*/
qboolean BotIsDead(bot_state_t * bs)
{
	return (bs->cur_ps.pm_type == PM_DEAD);
}

/*
==================
BotIsObserver
==================
*/
qboolean BotIsObserver(bot_state_t * bs)
{
	char buf[MAX_INFO_STRING];

	if (bs->cur_ps.pm_type == PM_SPECTATOR)
		return qtrue;
	trap_GetConfigstring(CS_PLAYERS + bs->client, buf, sizeof(buf));
	if (atoi(Info_ValueForKey(buf, "t")) == TEAM_SPECTATOR)
		return qtrue;
	return qfalse;
}

/*
==================
BotIntermission
==================
*/
qboolean BotIntermission(bot_state_t * bs)
{
	//NOTE: we shouldn't be looking at the game code...
	if (level.intermissiontime)
		return qtrue;
	return (bs->cur_ps.pm_type == PM_FREEZE || bs->cur_ps.pm_type == PM_INTERMISSION);
}

/*
==================
BotInLavaOrSlime
==================
*/
qboolean BotInLavaOrSlime(bot_state_t * bs)
{
	vec3_t feet;

	VectorCopy(bs->origin, feet);
	feet[2] -= 23;
	return (trap_AAS_PointContents(feet) & (CONTENTS_LAVA | CONTENTS_SLIME));
}

/*
==================
BotCreateWayPoint
==================
*/
bot_waypoint_t *BotCreateWayPoint(char *name, vec3_t origin, int areanum)
{
	bot_waypoint_t *wp;
	vec3_t waypointmins = { -8, -8, -8 }, waypointmaxs = {
	8, 8, 8};

	wp = botai_freewaypoints;
	if (!wp) {
		BotAI_Print(PRT_WARNING, "BotCreateWayPoint: Out of waypoints\n");
		return NULL;
	}
	botai_freewaypoints = botai_freewaypoints->next;

	Q_strncpyz(wp->name, name, sizeof(wp->name));
	VectorCopy(origin, wp->goal.origin);
	VectorCopy(waypointmins, wp->goal.mins);
	VectorCopy(waypointmaxs, wp->goal.maxs);
	wp->goal.areanum = areanum;
	wp->next = NULL;
	wp->prev = NULL;
	return wp;
}

/*
==================
BotFindWayPoint
==================
*/
bot_waypoint_t *BotFindWayPoint(bot_waypoint_t * waypoints, char *name)
{
	bot_waypoint_t *wp;

	for (wp = waypoints; wp; wp = wp->next) {
		if (!Q_stricmp(wp->name, name))
			return wp;
	}
	return NULL;
}

/*
==================
BotFreeWaypoints
==================
*/
void BotFreeWaypoints(bot_waypoint_t * wp)
{
	bot_waypoint_t *nextwp;

	for (; wp; wp = nextwp) {
		nextwp = wp->next;
		wp->next = botai_freewaypoints;
		botai_freewaypoints = wp;
	}
}

/*
==================
BotInitWaypoints
==================
*/
void BotInitWaypoints(void)
{
	int i;

	botai_freewaypoints = NULL;
	for (i = 0; i < MAX_WAYPOINTS; i++) {
		botai_waypoints[i].next = botai_freewaypoints;
		botai_freewaypoints = &botai_waypoints[i];
	}
}

/*
==================
TeamPlayIsOn
==================
*/
int TeamPlayIsOn(void)
{
	return (gametype >= GT_TEAM);
}

/*
==================
BotAggression
==================
*/
float BotAggression(bot_state_t * bs)
{
	//if the enemy is located way higher than the bot
	if (bs->inventory[ENEMY_HEIGHT] > 200)
		return 0;
	//if the bot is very low on health
	if (bs->inventory[INVENTORY_HEALTH] < 60)
		return 0;
	//if the bot is low on health
	// Elder: ignore armor checks
	/*
	   if (bs->inventory[INVENTORY_HEALTH] < 80) {
	   //if the bot has insufficient armor
	   if (bs->inventory[INVENTORY_ARMOR] < 40) return 0;
	   }
	 */
	//if the bot can use the Handcannon
	if (bs->inventory[INVENTORY_HANDCANNON] > 0 && bs->inventory[INVENTORY_HANDCANNONAMMO] >= 2)
		return 100;
	//if the bot can use the Sniper
	if (bs->inventory[INVENTORY_SSG3000] > 0 && bs->inventory[INVENTORY_SSG3000] > 3)
		return 95;
	//if the bot can use the MP5
	if (bs->inventory[INVENTORY_MP5] > 0 && bs->inventory[INVENTORY_MP5AMMO] > 10)
		return 90;
	//if the bot can use the M4
	if (bs->inventory[INVENTORY_M4] > 0 && bs->inventory[INVENTORY_M4AMMO] > 5)
		return 90;
	//if the bot can use the plasmagun
	if (bs->inventory[INVENTORY_M3] > 0 && bs->inventory[INVENTORY_M3AMMO] > 4)
		return 85;
	//if the bot can use the grenade launcher
	if (bs->inventory[INVENTORY_GRENADE] > 0 && bs->inventory[INVENTORY_GRENADE] > 2)
		return 80;
	// if the bot can use akimbos
	if (bs->inventory[INVENTORY_AKIMBO] > 0 && bs->inventory[INVENTORY_AKIMBOAMMO] > 4)
		return 80;
	//if the bot can use the shotgun
	//if (bs->inventory[INVENTORY_SHOTGUN] > 0 &&
	//              bs->inventory[INVENTORY_SHELLS] > 10) return 50;
	//otherwise the bot is not feeling too good
	return 0;
}

/*
==================
BotFeelingBad
==================
*/
float BotFeelingBad(bot_state_t * bs)
{
	if (bs->weaponnum == WP_KNIFE) {
		return 100;
	}
	if (bs->inventory[INVENTORY_HEALTH] < 40) {
		return 100;
	}
	if (bs->weaponnum == WP_PISTOL) {
		return 90;
	}
	if (bs->inventory[INVENTORY_HEALTH] < 60) {
		return 80;
	}
	return 0;
}

/*
==================
BotWantsToRetreat
==================
*/
int BotWantsToRetreat(bot_state_t * bs)
{
	aas_entityinfo_t entinfo;

	if (gametype == GT_CTF) {
		//always retreat when carrying a CTF flag
		if (BotCTFCarryingFlag(bs))
			return qtrue;
	}
	if (bs->enemy >= 0) {
		//if the enemy is carrying a flag
		BotEntityInfo(bs->enemy, &entinfo);
		if (EntityCarriesFlag(&entinfo))
			return qfalse;
	}
	//if the bot is getting the flag
	if (bs->ltgtype == LTG_GETFLAG)
		return qtrue;
	//
	if (BotAggression(bs) < 50)
		return qtrue;
	return qfalse;
}

/*
==================
BotWantsToChase
==================
*/
int BotWantsToChase(bot_state_t * bs)
{
	aas_entityinfo_t entinfo;

	if (gametype == GT_CTF) {
		//never chase when carrying a CTF flag
		if (BotCTFCarryingFlag(bs))
			return qfalse;
		//always chase if the enemy is carrying a flag
		BotEntityInfo(bs->enemy, &entinfo);
		if (EntityCarriesFlag(&entinfo))
			return qtrue;
	}
	//if the bot is getting the flag
	if (bs->ltgtype == LTG_GETFLAG)
		return qfalse;
	//
	if (BotAggression(bs) > 50)
		return qtrue;
	return qfalse;
}

/*
==================
BotWantsToHelp
==================
*/
int BotWantsToHelp(bot_state_t * bs)
{
	return qtrue;
}

/*
==================
BotCanAndWantsToRocketJump
==================
*/
int BotCanAndWantsToRocketJump(bot_state_t * bs)
{
	return qfalse;		//No Rocketjumping
/*
	float rocketjumper;

	//if rocket jumping is disabled
	if (!bot_rocketjump.integer) return qfalse;
	//if no rocket launcher
	if (bs->inventory[INVENTORY_ROCKETLAUNCHER] <= 0) return qfalse;
	//if low on rockets
	if (bs->inventory[INVENTORY_ROCKETS] < 3) return qfalse;
	//never rocket jump with the Quad
	if (bs->inventory[INVENTORY_QUAD]) return qfalse;
	//if low on health
	if (bs->inventory[INVENTORY_HEALTH] < 60) return qfalse;
	//if not full health
	if (bs->inventory[INVENTORY_HEALTH] < 90) {
		//if the bot has insufficient armor
		if (bs->inventory[INVENTORY_ARMOR] < 40) return qfalse;
	}
	rocketjumper = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_WEAPONJUMPING, 0, 1);
	if (rocketjumper < 0.5) return qfalse;
	return qtrue;
	*/
}

/*
==================
BotHasPersistantPowerupAndWeapon
==================
*/
int BotHasPersistantPowerupAndWeapon(bot_state_t * bs)
{
	//if the bot is very low on health
	if (bs->inventory[INVENTORY_HEALTH] < 60)
		return qfalse;
	//if the bot is low on health
	if (bs->inventory[INVENTORY_HEALTH] < 80) {
		//if the bot has insufficient armor
		if (bs->inventory[INVENTORY_ARMOR] < 40)
			return qfalse;
	}
	//if the bot can use the bfg
	if (bs->inventory[INVENTORY_M4] > 0 && bs->inventory[INVENTORY_M4AMMO] > 7)
		return qtrue;
	//if the bot can use the railgun
	if (bs->inventory[INVENTORY_SSG3000] > 0 && bs->inventory[INVENTORY_SSG3000] > 5)
		return qtrue;
	//if the bot can use the lightning gun
	if (bs->inventory[INVENTORY_MP5] > 0 && bs->inventory[INVENTORY_MP5AMMO] > 50)
		return qtrue;
	//if the bot can use the rocketlauncher
	if (bs->inventory[INVENTORY_HANDCANNON] > 0 && bs->inventory[INVENTORY_M3AMMO] > 5)
		return qtrue;
	//
	/*if (bs->inventory[INVENTORY_NAILGUN] > 0 &&
	   bs->inventory[INVENTORY_NAILS] > 5) return qtrue;
	   //
	   if (bs->inventory[INVENTORY_PROXLAUNCHER] > 0 &&
	   bs->inventory[INVENTORY_MINES] > 5) return qtrue;
	   //
	   if (bs->inventory[INVENTORY_CHAINGUN] > 0 &&
	   bs->inventory[INVENTORY_BELT] > 40) return qtrue;
	   //if the bot can use the plasmagun
	   if (bs->inventory[INVENTORY_PLASMAGUN] > 0 &&
	   bs->inventory[INVENTORY_CELLS] > 20) return qtrue;
	 */
	return qfalse;
}

/*
==================
BotGoCamp
==================
*/
void BotGoCamp(bot_state_t * bs, bot_goal_t * goal)
{
	float camper;

	bs->decisionmaker = bs->client;
	//set message time to zero so bot will NOT show any message
	bs->teammessage_time = 0;
	//set the ltg type
	bs->ltgtype = LTG_CAMP;
	//set the team goal
	memcpy(&bs->teamgoal, goal, sizeof(bot_goal_t));
	//get the team goal time
	camper = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_CAMPER, 0, 1);
	if (camper > 0.99)
		bs->teamgoal_time = FloatTime() + 99999;
	else
		bs->teamgoal_time = FloatTime() + 120 + 180 * camper + random() * 15;
	//set the last time the bot started camping
	bs->camp_time = FloatTime();
	//the teammate that requested the camping
	bs->teammate = 0;
	//do NOT type arrive message
	bs->arrive_time = 1;
}

/*
==================
BotWantsToCamp
==================
*/
int BotWantsToCamp(bot_state_t * bs)
{
	float camper;
	int cs, traveltime, besttraveltime;
	bot_goal_t goal, bestgoal;

	camper = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_CAMPER, 0, 1);
	if (camper < 0.1)
		return qfalse;
	//if the bot has a team goal
	if (bs->ltgtype == LTG_TEAMHELP ||
	    bs->ltgtype == LTG_TEAMACCOMPANY ||
	    bs->ltgtype == LTG_DEFENDKEYAREA ||
	    bs->ltgtype == LTG_GETFLAG ||
	    bs->ltgtype == LTG_RUSHBASE ||
	    bs->ltgtype == LTG_CAMP || bs->ltgtype == LTG_CAMPORDER || bs->ltgtype == LTG_PATROL) {
		return qfalse;
	}
	//if camped recently
	if (bs->camp_time > FloatTime() - 60 + 300 * (1 - camper))
		return qfalse;
	//
	if (random() > camper) {
		bs->camp_time = FloatTime();
		return qfalse;
	}
	//if the bot isn't healthy anough
	if (BotAggression(bs) < 50)
		return qfalse;
	//the bot should have at least have the rocket launcher, the railgun or the bfg10k with some ammo
	// Elder: changed a few of the numbers
	//Makro - fixed a typo - bs->inventory[INVENTORY_M3AMMO < 5]
	if ((bs->inventory[INVENTORY_HANDCANNON] <= 0 || bs->inventory[INVENTORY_M3AMMO] < 5) &&
	    (bs->inventory[INVENTORY_M4] <= 0 || bs->inventory[INVENTORY_M4AMMO] < 10) &&
	    (bs->inventory[INVENTORY_SSG3000] <= 0 || bs->inventory[INVENTORY_SSG3000AMMO] < 6)) {
		return qfalse;
	}
	//find the closest camp spot
	besttraveltime = 99999;
	for (cs = trap_BotGetNextCampSpotGoal(0, &goal); cs; cs = trap_BotGetNextCampSpotGoal(cs, &goal)) {
		traveltime = trap_AAS_AreaTravelTimeToGoalArea(bs->areanum, bs->origin, goal.areanum, TFL_DEFAULT);
		if (traveltime && traveltime < besttraveltime) {
			besttraveltime = traveltime;
			memcpy(&bestgoal, &goal, sizeof(bot_goal_t));
		}
	}
	if (besttraveltime > 150)
		return qfalse;
	//ok found a camp spot, go camp there
	BotGoCamp(bs, &bestgoal);
	bs->ordered = qfalse;
	//
	return qtrue;
}

/*
==================
BotDontAvoid
==================
*/
void BotDontAvoid(bot_state_t * bs, char *itemname)
{
	bot_goal_t goal;
	int num;

	num = trap_BotGetLevelItemGoal(-1, itemname, &goal);
	while (num >= 0) {
		trap_BotRemoveFromAvoidGoals(bs->gs, goal.number);
		num = trap_BotGetLevelItemGoal(num, itemname, &goal);
	}
}

/*
==================
BotGoForPowerups
==================
*/
void BotGoForPowerups(bot_state_t * bs)
{

	//don't avoid any of the powerups anymore
	//Makro - replaced with Q3 items
	/*
	   BotDontAvoid(bs, "Quad Damage");
	   BotDontAvoid(bs, "Regeneration");
	   BotDontAvoid(bs, "Battle Suit");
	   BotDontAvoid(bs, "Speed");
	   BotDontAvoid(bs, "Invisibility");
	 */
	BotDontAvoid(bs, RQ3_KEVLAR_NAME);
	BotDontAvoid(bs, RQ3_LASER_NAME);
	BotDontAvoid(bs, RQ3_BANDOLIER_NAME);
	BotDontAvoid(bs, RQ3_SLIPPERS_NAME);
	BotDontAvoid(bs, RQ3_SILENCER_NAME);
	//BotDontAvoid(bs, "Flight");
	//reset the long term goal time so the bot will go for the powerup
	//NOTE: the long term goal type doesn't change
	bs->ltg_time = 0;
}

/*
==================
BotRoamGoal
==================
*/
void BotRoamGoal(bot_state_t * bs, vec3_t goal)
{
	int pc, i;
	float len, rnd;
	vec3_t dir, bestorg, belowbestorg;
	bsp_trace_t trace;

	for (i = 0; i < 10; i++) {
		//start at the bot origin
		VectorCopy(bs->origin, bestorg);
		rnd = random();
		if (rnd > 0.25) {
			//add a random value to the x-coordinate
			if (random() < 0.5)
				bestorg[0] -= 800 * random() + 100;
			else
				bestorg[0] += 800 * random() + 100;
		}
		if (rnd < 0.75) {
			//add a random value to the y-coordinate
			if (random() < 0.5)
				bestorg[1] -= 800 * random() + 100;
			else
				bestorg[1] += 800 * random() + 100;
		}
		//add a random value to the z-coordinate (NOTE: 48 = maxjump?)
		bestorg[2] += 2 * 48 * crandom();
		//trace a line from the origin to the roam target
		BotAI_Trace(&trace, bs->origin, NULL, NULL, bestorg, bs->entitynum, MASK_SOLID);
		//direction and length towards the roam target
		VectorSubtract(trace.endpos, bs->origin, dir);
		len = VectorNormalize(dir);
		//if the roam target is far away anough
		if (len > 200) {
			//the roam target is in the given direction before walls
			VectorScale(dir, len * trace.fraction - 40, dir);
			VectorAdd(bs->origin, dir, bestorg);
			//get the coordinates of the floor below the roam target
			belowbestorg[0] = bestorg[0];
			belowbestorg[1] = bestorg[1];
			belowbestorg[2] = bestorg[2] - 800;
			BotAI_Trace(&trace, bestorg, NULL, NULL, belowbestorg, bs->entitynum, MASK_SOLID);
			//
			if (!trace.startsolid) {
				trace.endpos[2]++;
				pc = trap_PointContents(trace.endpos, bs->entitynum);
				if (!(pc & (CONTENTS_LAVA | CONTENTS_SLIME))) {
					VectorCopy(bestorg, goal);
					return;
				}
			}
		}
	}
	VectorCopy(bestorg, goal);
}

/*
==================
BotAttackMove
==================
*/
bot_moveresult_t BotAttackMove(bot_state_t * bs, int tfl)
{
	int movetype, i, attackentity;
	float attack_skill, jumper, croucher, dist, strafechange_time;
	float attack_dist, attack_range;
	vec3_t forward, backward, sideward, hordir, up = { 0, 0, 1 };
	aas_entityinfo_t entinfo;
	bot_moveresult_t moveresult;
	bot_goal_t goal;

	attackentity = bs->enemy;
	//
	if (bs->attackchase_time > FloatTime()) {
		//create the chase goal
		goal.entitynum = attackentity;
		goal.areanum = bs->lastenemyareanum;
		VectorCopy(bs->lastenemyorigin, goal.origin);
		VectorSet(goal.mins, -8, -8, -8);
		VectorSet(goal.maxs, 8, 8, 8);
		//initialize the movement state
		BotSetupForMovement(bs);
		//move towards the goal
		trap_BotMoveToGoal(&moveresult, bs->ms, &goal, tfl);
		return moveresult;
	}
	//
	memset(&moveresult, 0, sizeof(bot_moveresult_t));
	//
	attack_skill = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_ATTACK_SKILL, 0, 1);
	jumper = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_JUMPER, 0, 1);
	croucher = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_CROUCHER, 0, 1);
	//if the bot is really stupid
	if (attack_skill < 0.2)
		return moveresult;
	//initialize the movement state
	BotSetupForMovement(bs);
	//get the enemy entity info
	BotEntityInfo(attackentity, &entinfo);
	//direction towards the enemy
	VectorSubtract(entinfo.origin, bs->origin, forward);
	//the distance towards the enemy
	dist = VectorNormalize(forward);
	//Makro - for long range attacks the bots should crouch more often
	//              same for sniper now; also added skill as a factor
	if (dist > 512 || (dist > 128 && bs->cur_ps.weapon == WP_SSG3000)) {
		croucher = Com_Clamp(0.1f, 1, croucher * (attack_skill + 1));
		jumper = Com_Clamp(0, 1, jumper / (attack_skill + 1));
	}
	VectorNegate(forward, backward);
	//walk, crouch or jump
	movetype = MOVE_WALK;
	//
	if (bs->attackcrouch_time < FloatTime() - 1) {
		if (random() < jumper) {
			movetype = MOVE_JUMP;
		}
		//wait at least one second before crouching again
		else if (bs->attackcrouch_time < FloatTime() - 1 && random() < croucher) {
			bs->attackcrouch_time = FloatTime() + croucher * 5;
		}
	}
	if (bs->attackcrouch_time > FloatTime())
		movetype = MOVE_CROUCH;
	//if the bot should jump
	if (movetype == MOVE_JUMP) {
		//if jumped last frame
		if (bs->attackjump_time > FloatTime()) {
			movetype = MOVE_WALK;
		} else {
			bs->attackjump_time = FloatTime() + 1;
		}
	}
	if (bs->cur_ps.weapon == WP_KNIFE) {
		attack_dist = 0;
		attack_range = 0;
	} else {
		attack_dist = IDEAL_ATTACKDIST;
		attack_range = 40;
	}
	//if the bot is stupid
	if (attack_skill <= 0.4) {
		//just walk to or away from the enemy
		if (dist > attack_dist + attack_range) {
			if (trap_BotMoveInDirection(bs->ms, forward, 400, movetype))
				return moveresult;
		}
		if (dist < attack_dist - attack_range) {
			if (trap_BotMoveInDirection(bs->ms, backward, 400, movetype))
				return moveresult;
		}
		return moveresult;
	}
	//increase the strafe time
	bs->attackstrafe_time += bs->thinktime;
	//get the strafe change time
	strafechange_time = 0.4 + (1 - attack_skill) * 0.2;
	if (attack_skill > 0.7)
		strafechange_time += crandom() * 0.2;
	//if the strafe direction should be changed
	if (bs->attackstrafe_time > strafechange_time) {
		//some magic number :)
		if (random() > 0.935) {
			//flip the strafe direction
			bs->flags ^= BFL_STRAFERIGHT;
			bs->attackstrafe_time = 0;
		}
	}
	//
	for (i = 0; i < 2; i++) {
		hordir[0] = forward[0];
		hordir[1] = forward[1];
		hordir[2] = 0;
		VectorNormalize(hordir);
		//get the sideward vector
		CrossProduct(hordir, up, sideward);
		//reverse the vector depending on the strafe direction
		if (bs->flags & BFL_STRAFERIGHT)
			VectorNegate(sideward, sideward);
		//randomly go back a little
		if (random() > 0.9) {
			VectorAdd(sideward, backward, sideward);
		} else {
			//walk forward or backward to get at the ideal attack distance
			if (dist > attack_dist + attack_range) {
				VectorAdd(sideward, forward, sideward);
			} else if (dist < attack_dist - attack_range) {
				VectorAdd(sideward, backward, sideward);
			}
		}
		//perform the movement
		if (trap_BotMoveInDirection(bs->ms, sideward, 400, movetype))
			return moveresult;
		//movement failed, flip the strafe direction
		bs->flags ^= BFL_STRAFERIGHT;
		bs->attackstrafe_time = 0;
	}
	//bot couldn't do any useful movement
//      bs->attackchase_time = AAS_Time() + 6;
	return moveresult;
}

/*
==================
BotSameTeam
==================
*/
int BotSameTeam(bot_state_t * bs, int entnum)
{
//	char info1[1024], info2[1024];
	int team1, team2;

	if (bs->client < 0 || bs->client >= MAX_CLIENTS) {
		return qfalse;
	}
	if (entnum < 0 || entnum >= MAX_CLIENTS) {
		return qfalse;
	}
	if (gametype >= GT_TEAM) {
		//Makro - added teamplay code; changed some stuff
		team1 = g_entities[bs->client].client->sess.savedTeam;
		team2 = g_entities[entnum].client->sess.savedTeam;
		if (team1 == TEAM_SPECTATOR || team2 == TEAM_SPECTATOR)
			return qfalse;
		if (team1 == team2)
			return qtrue;
	}
	return qfalse;
}

/*
==================
InFieldOfVision
==================
*/
qboolean InFieldOfVision(vec3_t viewangles, float fov, vec3_t angles)
{
	int i;
	float diff, angle;

	for (i = 0; i < 2; i++) {
		angle = AngleMod(viewangles[i]);
		angles[i] = AngleMod(angles[i]);
		diff = angles[i] - angle;
		if (angles[i] > angle) {
			if (diff > 180.0)
				diff -= 360.0;
		} else {
			if (diff < -180.0)
				diff += 360.0;
		}
		if (diff > 0) {
			if (diff > fov * 0.5)
				return qfalse;
		} else {
			if (diff < -fov * 0.5)
				return qfalse;
		}
	}
	return qtrue;
}

/*
==================
BotEntityVisible

returns visibility in the range [0, 1] taking fog and water surfaces into account
==================
*/
float BotEntityVisible(int viewer, vec3_t eye, vec3_t viewangles, float fov, int ent)
{
	int i, contents_mask, passent, hitent, infog, inwater, otherinfog, pc;
	float squaredfogdist, waterfactor, vis, bestvis;
	bsp_trace_t trace;
	aas_entityinfo_t entinfo;
	vec3_t dir, entangles, start, end, middle;

	BotEntityInfo(ent, &entinfo);
	if (!entinfo.valid) {
		return 0;
	}

	//calculate middle of bounding box
	VectorAdd(entinfo.mins, entinfo.maxs, middle);
	VectorScale(middle, 0.5, middle);
	VectorAdd(entinfo.origin, middle, middle);
	//check if entity is within field of vision
	VectorSubtract(middle, eye, dir);
	vectoangles(dir, entangles);
	if (!InFieldOfVision(viewangles, fov, entangles))
		return 0;
	//
	pc = trap_AAS_PointContents(eye);
	infog = (pc & CONTENTS_FOG);
	inwater = (pc & (CONTENTS_LAVA | CONTENTS_SLIME | CONTENTS_WATER));
	//
	bestvis = 0;
	for (i = 0; i < 3; i++) {
		//if the point is not in potential visible sight
		//if (!AAS_inPVS(eye, middle)) continue;
		//
		contents_mask = CONTENTS_SOLID | CONTENTS_PLAYERCLIP;
		passent = viewer;
		hitent = ent;
		VectorCopy(eye, start);
		VectorCopy(middle, end);
		//if the entity is in water, lava or slime
		if (trap_AAS_PointContents(middle) & (CONTENTS_LAVA | CONTENTS_SLIME | CONTENTS_WATER)) {
			contents_mask |= (CONTENTS_LAVA | CONTENTS_SLIME | CONTENTS_WATER);
		}
		//if eye is in water, lava or slime
		if (inwater) {
			if (!(contents_mask & (CONTENTS_LAVA | CONTENTS_SLIME | CONTENTS_WATER))) {
				passent = ent;
				hitent = viewer;
				VectorCopy(middle, start);
				VectorCopy(eye, end);
			}
			contents_mask ^= (CONTENTS_LAVA | CONTENTS_SLIME | CONTENTS_WATER);
		}
		//trace from start to end
		BotAI_Trace(&trace, start, NULL, NULL, end, passent, contents_mask);
		//if water was hit
		waterfactor = 1.0;
		//note: trace.contents is always 0, see BotAI_Trace
		if (trace.contents & (CONTENTS_LAVA | CONTENTS_SLIME | CONTENTS_WATER)) {
			//if the water surface is translucent
			if (1) {
				//trace through the water
				contents_mask &= ~(CONTENTS_LAVA | CONTENTS_SLIME | CONTENTS_WATER);
				BotAI_Trace(&trace, trace.endpos, NULL, NULL, end, passent, contents_mask);
				waterfactor = 0.5;
			}
		}
		//if a full trace or the hitent was hit
		if (trace.fraction >= 1 || trace.ent == hitent) {
			//check for fog, assuming there's only one fog brush where
			//either the viewer or the entity is in or both are in
			otherinfog = (trap_AAS_PointContents(middle) & CONTENTS_FOG);
			if (infog && otherinfog) {
				VectorSubtract(trace.endpos, eye, dir);
				squaredfogdist = VectorLengthSquared(dir);
			} else if (infog) {
				VectorCopy(trace.endpos, start);
				BotAI_Trace(&trace, start, NULL, NULL, eye, viewer, CONTENTS_FOG);
				VectorSubtract(eye, trace.endpos, dir);
				squaredfogdist = VectorLengthSquared(dir);
			} else if (otherinfog) {
				VectorCopy(trace.endpos, end);
				BotAI_Trace(&trace, eye, NULL, NULL, end, viewer, CONTENTS_FOG);
				VectorSubtract(end, trace.endpos, dir);
				squaredfogdist = VectorLengthSquared(dir);
			} else {
				//if the entity and the viewer are not in fog assume there's no fog in between
				squaredfogdist = 0;
			}
			//decrease visibility with the view distance through fog
			vis = 1 / ((squaredfogdist * 0.001) < 1 ? 1 : (squaredfogdist * 0.001));
			//if entering water visibility is reduced
			vis *= waterfactor;
			//
			if (vis > bestvis)
				bestvis = vis;
			//if pretty much no fog
			if (bestvis >= 0.95)
				return bestvis;
		}
		//check bottom and top of bounding box as well
		if (i == 0)
			middle[2] += entinfo.mins[2];
		else if (i == 1)
			middle[2] += entinfo.maxs[2] - entinfo.mins[2];
	}
	return bestvis;
}

/*
==================
BotFindEnemy
==================
*/
int BotFindEnemy(bot_state_t * bs, int curenemy)
{
	int i, healthdecrease;
	float f, alertness, easyfragger, vis;
	float squaredist, cursquaredist;
	aas_entityinfo_t entinfo, curenemyinfo;
	vec3_t dir, angles;

	alertness = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_ALERTNESS, 0, 1);
	easyfragger = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_EASY_FRAGGER, 0, 1);
	//check if the health decreased
	healthdecrease = bs->lasthealth > bs->inventory[INVENTORY_HEALTH];
	//remember the current health value
	bs->lasthealth = bs->inventory[INVENTORY_HEALTH];
	//
	if (curenemy >= 0) {
		BotEntityInfo(curenemy, &curenemyinfo);
		if (EntityCarriesFlag(&curenemyinfo))
			return qfalse;
		VectorSubtract(curenemyinfo.origin, bs->origin, dir);
		cursquaredist = VectorLengthSquared(dir);
	} else {
		cursquaredist = 0;
	}
	for (i = 0; i < level.maxclients; i++) {

		if (i == bs->client)
			continue;
		//if it's the current enemy
		if (i == curenemy)
			continue;
		//if the enemy has targeting disabled
		if (g_entities[i].flags & FL_NOTARGET) {
			continue;
		}
		//
		BotEntityInfo(i, &entinfo);
		//
		if (!entinfo.valid)
			continue;
		//if the enemy isn't dead and the enemy isn't the bot self
		if (EntityIsDead(&entinfo) || entinfo.number == bs->entitynum)
			continue;
		//if the enemy is invisible and not shooting
		if (EntityIsInvisible(&entinfo) && !EntityIsShooting(&entinfo)) {
			continue;
		}

		//if not an easy fragger don't shoot at chatting players
		if (easyfragger < 0.5 && EntityIsChatting(&entinfo))
			continue;
		//
		if (lastteleport_time > FloatTime() - 3) {
			VectorSubtract(entinfo.origin, lastteleport_origin, dir);
			if (VectorLengthSquared(dir) < Square(70))
				continue;
		}
		//calculate the distance towards the enemy
		VectorSubtract(entinfo.origin, bs->origin, dir);
		squaredist = VectorLengthSquared(dir);
		//if this entity is not carrying a flag
		if (!EntityCarriesFlag(&entinfo)) {
			//if this enemy is further away than the current one
			if (curenemy >= 0 && squaredist > cursquaredist)
				continue;
		}		//end if
		//if the bot has no
		if (squaredist > Square(900.0 + alertness * 4000.0))
			continue;
		//if on the same team
		if (BotSameTeam(bs, i))
			continue;
		//if the bot's health decreased or the enemy is shooting
		if (curenemy < 0 && (healthdecrease || EntityIsShooting(&entinfo)))
			f = 360;
		else
			f = 90 + 90 - (90 - (squaredist > Square(810) ? Square(810) : squaredist) / (810 * 9));
		//check if the enemy is visible
		vis = BotEntityVisible(bs->entitynum, bs->eye, bs->viewangles, f, i);
		if (vis <= 0)
			continue;
		//if the enemy is quite far away, not shooting and the bot is not damaged
		if (curenemy < 0 && squaredist > Square(100) && !healthdecrease && !EntityIsShooting(&entinfo)) {
			//check if we can avoid this enemy
			VectorSubtract(bs->origin, entinfo.origin, dir);
			vectoangles(dir, angles);
			//if the bot isn't in the fov of the enemy
			if (!InFieldOfVision(entinfo.angles, 90, angles)) {
				//update some stuff for this enemy
				BotUpdateBattleInventory(bs, i);
				//if the bot doesn't really want to fight
				if (BotWantsToRetreat(bs))
					continue;
			}
		}
		//found an enemy
		bs->enemy = entinfo.number;
		if (curenemy >= 0)
			bs->enemysight_time = FloatTime() - 2;
		else
			bs->enemysight_time = FloatTime();
		bs->enemysuicide = qfalse;
		bs->enemydeath_time = 0;
		bs->enemyvisible_time = FloatTime();
		return qtrue;
	}
	return qfalse;
}

/*
==================
BotTeamFlagCarrierVisible
==================
*/
int BotTeamFlagCarrierVisible(bot_state_t * bs)
{
	int i;
	float vis;
	aas_entityinfo_t entinfo;

	for (i = 0; i < level.maxclients; i++) {
		if (i == bs->client)
			continue;
		//
		BotEntityInfo(i, &entinfo);
		//if this player is active
		if (!entinfo.valid)
			continue;
		//if this player is carrying a flag
		if (!EntityCarriesFlag(&entinfo))
			continue;
		//if the flag carrier is not on the same team
		if (!BotSameTeam(bs, i))
			continue;
		//if the flag carrier is not visible
		vis = BotEntityVisible(bs->entitynum, bs->eye, bs->viewangles, 360, i);
		if (vis <= 0)
			continue;
		//
		return i;
	}
	return -1;
}

/*
==================
BotTeamFlagCarrier
==================
*/
int BotTeamFlagCarrier(bot_state_t * bs)
{
	int i;
	aas_entityinfo_t entinfo;

	for (i = 0; i < level.maxclients; i++) {
		if (i == bs->client)
			continue;
		//
		BotEntityInfo(i, &entinfo);
		//if this player is active
		if (!entinfo.valid)
			continue;
		//if this player is carrying a flag
		if (!EntityCarriesFlag(&entinfo))
			continue;
		//if the flag carrier is not on the same team
		if (!BotSameTeam(bs, i))
			continue;
		//
		return i;
	}
	return -1;
}

/*
==================
BotEnemyFlagCarrierVisible
==================
*/
int BotEnemyFlagCarrierVisible(bot_state_t * bs)
{
	int i;
	float vis;
	aas_entityinfo_t entinfo;

	for (i = 0; i < level.maxclients; i++) {
		if (i == bs->client)
			continue;
		//
		BotEntityInfo(i, &entinfo);
		//if this player is active
		if (!entinfo.valid)
			continue;
		//if this player is carrying a flag
		if (!EntityCarriesFlag(&entinfo))
			continue;
		//if the flag carrier is on the same team
		if (BotSameTeam(bs, i))
			continue;
		//if the flag carrier is not visible
		vis = BotEntityVisible(bs->entitynum, bs->eye, bs->viewangles, 360, i);
		if (vis <= 0)
			continue;
		//
		return i;
	}
	return -1;
}

/*
==================
BotVisibleTeamMatesAndEnemies
==================
*/
void BotVisibleTeamMatesAndEnemies(bot_state_t * bs, int *teammates, int *enemies, float range)
{
	int i;
	float vis;
	aas_entityinfo_t entinfo;
	vec3_t dir;

	if (teammates)
		*teammates = 0;
	if (enemies)
		*enemies = 0;
	for (i = 0; i < level.maxclients; i++) {
		if (i == bs->client)
			continue;
		//
		BotEntityInfo(i, &entinfo);
		//if this player is active
		if (!entinfo.valid)
			continue;
		//if this player is carrying a flag
		if (!EntityCarriesFlag(&entinfo))
			continue;
		//if not within range
		VectorSubtract(entinfo.origin, bs->origin, dir);
		if (VectorLengthSquared(dir) > Square(range))
			continue;
		//if the flag carrier is not visible
		vis = BotEntityVisible(bs->entitynum, bs->eye, bs->viewangles, 360, i);
		if (vis <= 0)
			continue;
		//if the flag carrier is on the same team
		if (BotSameTeam(bs, i)) {
			if (teammates)
				(*teammates)++;
		} else {
			if (enemies)
				(*enemies)++;
		}
	}
}

/*
==================
BotAimAtEnemy
==================
*/
void BotAimAtEnemy(bot_state_t * bs)
{
	int enemyvisible;
	float dist, f, aim_skill, aim_accuracy, speed, reactiontime;
	vec3_t dir, bestorigin, end, start, groundtarget, cmdmove, enemyvelocity;
	vec3_t mins = { -4, -4, -4 }, maxs = {
	4, 4, 4};
	weaponinfo_t wi;
	aas_entityinfo_t entinfo;
	bot_goal_t goal;
	bsp_trace_t trace;
	vec3_t target;

	//if the bot has no enemy
	if (bs->enemy < 0) {
		return;
	}
	//get the enemy entity information
	BotEntityInfo(bs->enemy, &entinfo);
	//if this is not a player (should be an obelisk)
	if (bs->enemy >= MAX_CLIENTS) {
		//if the obelisk is visible
		VectorCopy(entinfo.origin, target);
		//aim at the obelisk
		VectorSubtract(target, bs->eye, dir);
		vectoangles(dir, bs->ideal_viewangles);
		//set the aim target before trying to attack
		VectorCopy(target, bs->aimtarget);
		return;
	}
	//
	//BotAI_Print(PRT_MESSAGE, "client %d: aiming at client %d\n", bs->entitynum, bs->enemy);
	//
	aim_skill = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_AIM_SKILL, 0, 1);
	aim_accuracy = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_AIM_ACCURACY, 0, 1);
	//
	if (aim_skill > 0.95) {
		//don't aim too early
		reactiontime = 0.5 * trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_REACTIONTIME, 0, 1);
		if (bs->enemysight_time > FloatTime() - reactiontime)
			return;
		if (bs->teleport_time > FloatTime() - reactiontime)
			return;
	}
	//get the weapon information
	//trap_BotGetWeaponInfo(bs->ws, bs->weaponnum, &wi);
	//Makro - new function; if weapon/weapon info not ok, stop
	if (!RQ3_Bot_GetWeaponInfo(bs, bs->ws, bs->weaponnum, &wi))
		return;

	//get the weapon specific aim accuracy and or aim skill
//Blaze: just gonna set the Characteristic aim to machinegun for all of these, but I am still doing the if's so we can edit it later for bot support
//Blaze: Reaction Pistol
	if (wi.number == WP_PISTOL) {
		aim_accuracy = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_AIM_ACCURACY_MACHINEGUN, 0, 1);
	}
//Blaze: Reaction Knife
	if (wi.number == WP_KNIFE) {
		aim_accuracy = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_AIM_ACCURACY_MACHINEGUN, 0, 1);
	}
//Blaze: Reaction M4
	if (wi.number == WP_M4) {
		aim_accuracy = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_AIM_ACCURACY_MACHINEGUN, 0, 1);
	}
//Blaze: Reaction SSG3000
	if (wi.number == WP_SSG3000) {
		aim_accuracy = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_AIM_ACCURACY_MACHINEGUN, 0, 1);
	}
//Blaze: Reaction MP5
	if (wi.number == WP_MP5) {
		aim_accuracy = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_AIM_ACCURACY_MACHINEGUN, 0, 1);
	}
//Blaze: Reaction HandCannon
//Makro - using shotgun accuracy for now
	if (wi.number == WP_HANDCANNON) {
		aim_accuracy = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_AIM_ACCURACY_SHOTGUN, 0, 1);
	}
//Blaze: Reaction Shotgun
//Makro - using shotgun accuracy for now
	if (wi.number == WP_M3) {
		aim_accuracy = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_AIM_ACCURACY_SHOTGUN, 0, 1);
	}
//Blaze: Reaction Akimbo
	if (wi.number == WP_AKIMBO) {
		aim_accuracy = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_AIM_ACCURACY_MACHINEGUN, 0, 1);
	}
//Blaze: Reaction Grenade
//Makro - changed to grenade launcher accuracy
	if (wi.number == WP_GRENADE) {
		aim_accuracy =
		    trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_AIM_ACCURACY_GRENADELAUNCHER, 0, 1);
	}
	//
	if (aim_accuracy <= 0)
		aim_accuracy = 0.0001f;
	//get the enemy entity information
	BotEntityInfo(bs->enemy, &entinfo);
	//if the enemy is invisible then shoot crappy most of the time
	if (EntityIsInvisible(&entinfo)) {
		if (random() > 0.1)
			aim_accuracy *= 0.4f;
	}
	//
	VectorSubtract(entinfo.origin, entinfo.lastvisorigin, enemyvelocity);
	VectorScale(enemyvelocity, 1 / entinfo.update_time, enemyvelocity);
	//enemy origin and velocity is remembered every 0.5 seconds
	if (bs->enemyposition_time < FloatTime()) {
		//
		bs->enemyposition_time = FloatTime() + 0.5;
		VectorCopy(enemyvelocity, bs->enemyvelocity);
		VectorCopy(entinfo.origin, bs->enemyorigin);
	}
	//if not extremely skilled
	if (aim_skill < 0.9) {
		VectorSubtract(entinfo.origin, bs->enemyorigin, dir);
		//if the enemy moved a bit
		if (VectorLengthSquared(dir) > Square(48)) {
			//if the enemy changed direction
			if (DotProduct(bs->enemyvelocity, enemyvelocity) < 0) {
				//aim accuracy should be worse now
				aim_accuracy *= 0.7f;
			}
		}
	}
	//check visibility of enemy
	enemyvisible = BotEntityVisible(bs->entitynum, bs->eye, bs->viewangles, 360, bs->enemy);
	//if the enemy is visible
	if (enemyvisible) {
		//
		VectorCopy(entinfo.origin, bestorigin);
		bestorigin[2] += 8;
		//get the start point shooting from
		//NOTE: the x and y projectile start offsets are ignored
		VectorCopy(bs->origin, start);
		start[2] += bs->cur_ps.viewheight;
		start[2] += wi.offset[2];
		//
		BotAI_Trace(&trace, start, mins, maxs, bestorigin, bs->entitynum, MASK_SHOT);
		//if the enemy is NOT hit
		if (trace.fraction <= 1 && trace.ent != entinfo.number) {
			bestorigin[2] += 16;
		}
		//if it is not an instant hit weapon the bot might want to predict the enemy
		if (wi.speed) {
			//
			VectorSubtract(bestorigin, bs->origin, dir);
			dist = VectorLength(dir);
			VectorSubtract(entinfo.origin, bs->enemyorigin, dir);
			//if the enemy is NOT pretty far away and strafing just small steps left and right
			if (!(dist > 100 && VectorLengthSquared(dir) < Square(32))) {
				//if skilled anough do exact prediction
				if (aim_skill > 0.8 &&
				    //if the weapon is ready to fire
				    bs->cur_ps.weaponstate == WEAPON_READY) {
					aas_clientmove_t move;
					vec3_t origin;

					VectorSubtract(entinfo.origin, bs->origin, dir);
					//distance towards the enemy
					dist = VectorLength(dir);
					//direction the enemy is moving in
					VectorSubtract(entinfo.origin, entinfo.lastvisorigin, dir);
					//
					VectorScale(dir, 1 / entinfo.update_time, dir);
					//
					VectorCopy(entinfo.origin, origin);
					origin[2] += 1;
					//
					VectorClear(cmdmove);
					//AAS_ClearShownDebugLines();
					trap_AAS_PredictClientMovement(&move, bs->enemy, origin,
								       PRESENCE_CROUCH, qfalse,
								       dir, cmdmove, 0,
								       dist * 10 / wi.speed, 0.1f, 0, 0, qfalse);
					VectorCopy(move.endpos, bestorigin);
					//BotAI_Print(PRT_MESSAGE, "%1.1f predicted speed = %f, frames = %f\n", FloatTime(), VectorLength(dir), dist * 10 / wi.speed);
				}
				//if not that skilled do linear prediction
				else if (aim_skill > 0.4) {
					VectorSubtract(entinfo.origin, bs->origin, dir);
					//distance towards the enemy
					dist = VectorLength(dir);
					//direction the enemy is moving in
					VectorSubtract(entinfo.origin, entinfo.lastvisorigin, dir);
					dir[2] = 0;
					//
					speed = VectorNormalize(dir) / entinfo.update_time;
					//botimport.Print(PRT_MESSAGE, "speed = %f, wi->speed = %f\n", speed, wi->speed);
					//best spot to aim at
					VectorMA(entinfo.origin, (dist / wi.speed) * speed, dir, bestorigin);
				}
			}
		}
		//if the projectile does radial damage
		if (aim_skill > 0.6 && wi.proj.damagetype & DAMAGETYPE_RADIAL) {
			//if the enemy isn't standing significantly higher than the bot
			if (entinfo.origin[2] < bs->origin[2] + 16) {
				//try to aim at the ground in front of the enemy
				VectorCopy(entinfo.origin, end);
				end[2] -= 64;
				BotAI_Trace(&trace, entinfo.origin, NULL, NULL, end, entinfo.number, MASK_SHOT);
				//
				VectorCopy(bestorigin, groundtarget);
				if (trace.startsolid)
					groundtarget[2] = entinfo.origin[2] - 16;
				else
					groundtarget[2] = trace.endpos[2] - 8;
				//trace a line from projectile start to ground target
				BotAI_Trace(&trace, start, NULL, NULL, groundtarget, bs->entitynum, MASK_SHOT);
				//if hitpoint is not vertically too far from the ground target
				if (fabs(trace.endpos[2] - groundtarget[2]) < 50) {
					VectorSubtract(trace.endpos, groundtarget, dir);
					//if the hitpoint is near anough the ground target
					if (VectorLengthSquared(dir) < Square(60)) {
						VectorSubtract(trace.endpos, start, dir);
						//if the hitpoint is far anough from the bot
						if (VectorLengthSquared(dir) > Square(100)) {
							//check if the bot is visible from the ground target
							trace.endpos[2] += 1;
							BotAI_Trace(&trace, trace.endpos, NULL, NULL, entinfo.origin,
								    entinfo.number, MASK_SHOT);
							if (trace.fraction >= 1) {
								//botimport.Print(PRT_MESSAGE, "%1.1f aiming at ground\n", AAS_Time());
								VectorCopy(groundtarget, bestorigin);
							}
						}
					}
				}
			}
		}
		bestorigin[0] += 20 * crandom() * (1 - aim_accuracy);
		bestorigin[1] += 20 * crandom() * (1 - aim_accuracy);
		bestorigin[2] += 10 * crandom() * (1 - aim_accuracy);
	} else {
		//
		VectorCopy(bs->lastenemyorigin, bestorigin);
		bestorigin[2] += 8;
		//if the bot is skilled anough
		if (aim_skill > 0.5) {
			//do prediction shots around corners
			//Blaze: Knifes are the only thing bots would need to do predictions shots with, but will need lots of tweaking
			if (wi.number == WP_KNIFE) {
				//create the chase goal
				goal.entitynum = bs->client;
				goal.areanum = bs->areanum;
				VectorCopy(bs->eye, goal.origin);
				VectorSet(goal.mins, -8, -8, -8);
				VectorSet(goal.maxs, 8, 8, 8);
				//
				if (trap_BotPredictVisiblePosition
				    (bs->lastenemyorigin, bs->lastenemyareanum, &goal, TFL_DEFAULT, target)) {
					VectorSubtract(target, bs->eye, dir);
					if (VectorLengthSquared(dir) > Square(80)) {
						VectorCopy(target, bestorigin);
						bestorigin[2] -= 20;
					}
				}
				aim_accuracy = 1;
			}
		}
	}
	//
	if (enemyvisible) {
		BotAI_Trace(&trace, bs->eye, NULL, NULL, bestorigin, bs->entitynum, MASK_SHOT);
		VectorCopy(trace.endpos, bs->aimtarget);
	} else {
		VectorCopy(bestorigin, bs->aimtarget);
	}
	//get aim direction
	VectorSubtract(bestorigin, bs->eye, dir);
	//
	//Blaze: dont wanna have non hitscan weapons here I think like the knife or Grenades
	if (wi.number == WP_PISTOL ||
	    wi.number == WP_M4 ||
	    wi.number == WP_SSG3000 ||
	    wi.number == WP_MP5 || wi.number == WP_HANDCANNON || wi.number == WP_M3 || wi.number == WP_AKIMBO) {
		//distance towards the enemy
		dist = VectorLength(dir);
		if (dist > 150)
			dist = 150;
		f = 0.6 + dist / 150 * 0.4;
		aim_accuracy *= f;
	}
	//add some random stuff to the aim direction depending on the aim accuracy
	//Makro - bots look even more stupid than they are with this
	//if (aim_accuracy < 0.8) {
	//      VectorNormalize(dir);
	//      for (i = 0; i < 3; i++) dir[i] += 0.3 * crandom() * (1 - aim_accuracy);
	//}
	//set the ideal view angles
	vectoangles(dir, bs->ideal_viewangles);
	//take the weapon spread into account for lower skilled bots
	bs->ideal_viewangles[PITCH] += 6 * wi.vspread * crandom() * (1 - aim_accuracy);
	bs->ideal_viewangles[PITCH] = AngleMod(bs->ideal_viewangles[PITCH]);
	bs->ideal_viewangles[YAW] += 6 * wi.hspread * crandom() * (1 - aim_accuracy);
	bs->ideal_viewangles[YAW] = AngleMod(bs->ideal_viewangles[YAW]);
	//if the bots should be really challenging
	if (bot_challenge.integer) {
		//if the bot is really accurate and has the enemy in view for some time
		if (aim_accuracy > 0.9 && bs->enemysight_time < FloatTime() - 1) {
			//set the view angles directly
			if (bs->ideal_viewangles[PITCH] > 180)
				bs->ideal_viewangles[PITCH] -= 360;
			VectorCopy(bs->ideal_viewangles, bs->viewangles);
			trap_EA_View(bs->client, bs->viewangles);
		}
	}
}

/*
==================
BotCheckAttack
==================
*/
void BotCheckAttack(bot_state_t * bs)
{
	float points, reactiontime, fov, firethrottle;
	int attackentity;
	bsp_trace_t bsptrace;

	//float selfpreservation;
	vec3_t forward, right, start, end, dir, angles;
	weaponinfo_t wi;
	bsp_trace_t trace;
	aas_entityinfo_t entinfo;
	vec3_t mins = { -8, -8, -8 }, maxs = {
	8, 8, 8};

	attackentity = bs->enemy;
	//
	BotEntityInfo(attackentity, &entinfo);
	// if not attacking a player
	if (attackentity >= MAX_CLIENTS) {
	}
	//
	//Makro - we need the weapon info sooner
	//get the weapon info
	//trap_BotGetWeaponInfo(bs->ws, bs->weaponnum, &wi);
	//Makro - new function; if weapon/weapon info not ok, stop
	if (!RQ3_Bot_GetWeaponInfo(bs, bs->ws, bs->weaponnum, &wi))
		return;
	reactiontime = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_REACTIONTIME, 0, 1);
	if (bs->enemysight_time > FloatTime() - reactiontime)
		return;
	if (bs->teleport_time > FloatTime() - reactiontime)
		return;
	//if changing weapons
	//Makro - changed from 0.1 to an expression that takes into account weapon info
	if (bs->weaponchange_time > FloatTime() - 0.1 - wi.activate)
		return;
	//check fire throttle characteristic
	if (bs->firethrottlewait_time > FloatTime())
		return;
	firethrottle = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_FIRETHROTTLE, 0, 1);
	if (bs->firethrottleshoot_time < FloatTime()) {
		if (random() > firethrottle) {
			bs->firethrottlewait_time = FloatTime() + firethrottle;
			bs->firethrottleshoot_time = 0;
		} else {
			bs->firethrottleshoot_time = FloatTime() + 1 - firethrottle;
			bs->firethrottlewait_time = 0;
		}
	}
	//
	//
	VectorSubtract(bs->aimtarget, bs->eye, dir);
	//
	if (bs->weaponnum == WP_KNIFE) {
		if (VectorLengthSquared(dir) > Square(60)) {
			return;
		}
	}
	if (VectorLengthSquared(dir) < Square(100))
		fov = 120;
	else
		fov = 50;
	//
	vectoangles(dir, angles);
	if (!InFieldOfVision(bs->viewangles, fov, angles))
		return;
	BotAI_Trace(&bsptrace, bs->eye, NULL, NULL, bs->aimtarget, bs->client, CONTENTS_SOLID | CONTENTS_PLAYERCLIP);
	if (bsptrace.fraction < 1 && bsptrace.ent != attackentity)
		return;

	//Makro - get weapon info sooner; was here before
	//get the start point shooting from
	VectorCopy(bs->origin, start);
	start[2] += bs->cur_ps.viewheight;
	AngleVectors(bs->viewangles, forward, right, NULL);
	start[0] += forward[0] * wi.offset[0] + right[0] * wi.offset[1];
	start[1] += forward[1] * wi.offset[0] + right[1] * wi.offset[1];
	start[2] += forward[2] * wi.offset[0] + right[2] * wi.offset[1] + wi.offset[2];
	//end point aiming at
	VectorMA(start, 1000, forward, end);
	//a little back to make sure not inside a very close enemy
	VectorMA(start, -12, forward, start);
	BotAI_Trace(&trace, start, mins, maxs, end, bs->entitynum, MASK_SHOT);
	//if the entity is a client
	if (trace.ent >= 0 && trace.ent < MAX_CLIENTS) {
		if (trace.ent != attackentity) {
			//if a teammate is hit
			if (BotSameTeam(bs, trace.ent))
				return;
		}
	}
	//if won't hit the enemy or not attacking a player (obelisk)
	if (trace.ent != attackentity || attackentity >= MAX_CLIENTS) {
		//if the projectile does radial damage
		if (wi.proj.damagetype & DAMAGETYPE_RADIAL) {
			if (trace.fraction * 1000 < wi.proj.radius) {
				points = (wi.proj.damage - 0.5 * trace.fraction * 1000) * 0.5;
				if (points > 0) {
					return;
				}
			}
			//FIXME: check if a teammate gets radial damage
		}
	}
	//if fire has to be release to activate weapon
	if (wi.flags & WFL_FIRERELEASED) {
		if (bs->flags & BFL_ATTACKED) {
			//Makro - using custom function to allow in-combat reloads
			//trap_EA_Attack(bs->client);
			BotAttack(bs);
		}
	} else {
		//Makro - using custom function to allow in-combat reloads
		//trap_EA_Attack(bs->client);
		BotAttack(bs);
	}
	bs->flags ^= BFL_ATTACKED;
}

/*
==================
BotMapScripts
==================
*/
void BotMapScripts(bot_state_t * bs)
{
	char info[1024];
	char mapname[128];
	int i, shootbutton;
	float aim_accuracy;
	aas_entityinfo_t entinfo;
	vec3_t dir;

	trap_GetServerinfo(info, sizeof(info));

	strncpy(mapname, Info_ValueForKey(info, "mapname"), sizeof(mapname) - 1);
	mapname[sizeof(mapname) - 1] = '\0';

	if (!Q_stricmp(mapname, "q3tourney6") || !Q_stricmp(mapname, "q3tourney6_ctf") || !Q_stricmp(mapname, "mpq3tourney6")) {
		vec3_t mins = { 694, 200, 480 }, maxs = {
		968, 472, 680 };
		vec3_t buttonorg = { 304, 352, 920 };

		//NOTE: NEVER use the func_bobbing in q3tourney6
		bs->tfl &= ~TFL_FUNCBOB;
		//crush area is higher in mpq3tourney6
		if (!Q_stricmp(mapname, "mpq3tourney6")) {
			mins[2] += 64;
			maxs[2] += 64;
		}
		//if the bot is in the bounding box of the crush area
		if (bs->origin[0] > mins[0] && bs->origin[0] < maxs[0]) {
			if (bs->origin[1] > mins[1] && bs->origin[1] < maxs[1]) {
				if (bs->origin[2] > mins[2] && bs->origin[2] < maxs[2]) {
					return;
				}
			}
		}
		shootbutton = qfalse;
		//if an enemy is in the bounding box then shoot the button
		for (i = 0; i < level.maxclients; i++) {

			if (i == bs->client)
				continue;
			//
			BotEntityInfo(i, &entinfo);
			//
			if (!entinfo.valid)
				continue;
			//if the enemy isn't dead and the enemy isn't the bot self
			if (EntityIsDead(&entinfo) || entinfo.number == bs->entitynum)
				continue;
			//
			if (entinfo.origin[0] > mins[0] && entinfo.origin[0] < maxs[0]) {
				if (entinfo.origin[1] > mins[1] && entinfo.origin[1] < maxs[1]) {
					if (entinfo.origin[2] > mins[2] && entinfo.origin[2] < maxs[2]) {
						//if there's a team mate below the crusher
						if (BotSameTeam(bs, i)) {
							shootbutton = qfalse;
							break;
						} else if (gametype < GT_CTF || bs->enemy == i) {
							shootbutton = qtrue;
						}
					}
				}
			}
		}
		if (shootbutton) {
			bs->flags |= BFL_IDEALVIEWSET;
			VectorSubtract(buttonorg, bs->eye, dir);
			vectoangles(dir, bs->ideal_viewangles);
			aim_accuracy = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_AIM_ACCURACY, 0, 1);
			bs->ideal_viewangles[PITCH] += 8 * crandom() * (1 - aim_accuracy);
			bs->ideal_viewangles[PITCH] = AngleMod(bs->ideal_viewangles[PITCH]);
			bs->ideal_viewangles[YAW] += 8 * crandom() * (1 - aim_accuracy);
			bs->ideal_viewangles[YAW] = AngleMod(bs->ideal_viewangles[YAW]);
			//
			if (InFieldOfVision(bs->viewangles, 20, bs->ideal_viewangles)) {
				//Makro - using custom function to allow in-combat reloads
				//trap_EA_Attack(bs->client);
				BotAttack(bs);
			}
		}
	}
}

/*
==================
BotSetMovedir
==================
*/
// bk001205 - made these static
static vec3_t VEC_UP = { 0, -1, 0 };
static vec3_t MOVEDIR_UP = { 0, 0, 1 };
static vec3_t VEC_DOWN = { 0, -2, 0 };
static vec3_t MOVEDIR_DOWN = { 0, 0, -1 };

void BotSetMovedir(vec3_t angles, vec3_t movedir)
{
	if (VectorCompare(angles, VEC_UP)) {
		VectorCopy(MOVEDIR_UP, movedir);
	} else if (VectorCompare(angles, VEC_DOWN)) {
		VectorCopy(MOVEDIR_DOWN, movedir);
	} else {
		AngleVectors(angles, movedir, NULL, NULL);
	}
}

/*
==================
BotModelMinsMaxs

this is ugly
==================
*/
int BotModelMinsMaxs(int modelindex, int eType, int contents, vec3_t mins, vec3_t maxs)
{
	gentity_t *ent;
	int i;

	//Makro - started from 0
	//ent = &g_entities[0];
	ent = &g_entities[MAX_CLIENTS];
	for (i = MAX_CLIENTS; i < level.num_entities; i++, ent++) {
		if (!ent->inuse) {
			continue;
		}
		if (eType && ent->s.eType != eType) {
			continue;
		}
		if (contents && ent->r.contents != contents) {
			continue;
		}
		if (ent->s.modelindex == modelindex) {
			if (mins)
				VectorAdd(ent->r.currentOrigin, ent->r.mins, mins);
			if (maxs)
				VectorAdd(ent->r.currentOrigin, ent->r.maxs, maxs);
			return i;
		}
	}
	if (mins)
		VectorClear(mins);
	if (maxs)
		VectorClear(maxs);
	return 0;
}

/*
==================
BotFuncButtonGoal
==================
*/
int BotFuncButtonActivateGoal(bot_state_t * bs, int bspent, bot_activategoal_t * activategoal)
{
	int i, areas[10], numareas, modelindex, entitynum;
	char model[128];
	float lip, dist, health, angle;
	vec3_t size, start, end, mins, maxs, angles, points[10];
	vec3_t movedir, origin, goalorigin, bboxmins, bboxmaxs;
	vec3_t extramins = { 1, 1, 1 }, extramaxs = {
	-1, -1, -1};
	bsp_trace_t bsptrace;

	activategoal->shoot = qfalse;
	VectorClear(activategoal->target);
	//create a bot goal towards the button
	trap_AAS_ValueForBSPEpairKey(bspent, "model", model, sizeof(model));
	if (!*model)
		return qfalse;
	modelindex = atoi(model + 1);
	if (!modelindex)
		return qfalse;
	entitynum = BotModelMinsMaxs(modelindex, ET_MOVER, 0, mins, maxs);
	//get the lip of the button
	trap_AAS_FloatForBSPEpairKey(bspent, "lip", &lip);
	if (!lip)
		lip = 4;
	//get the move direction from the angle
	trap_AAS_FloatForBSPEpairKey(bspent, "angle", &angle);
	VectorSet(angles, 0, angle, 0);
	BotSetMovedir(angles, movedir);
	//button size
	VectorSubtract(maxs, mins, size);
	//button origin
	VectorAdd(mins, maxs, origin);
	VectorScale(origin, 0.5, origin);
	//touch distance of the button
	dist = fabs(movedir[0]) * size[0] + fabs(movedir[1]) * size[1] + fabs(movedir[2]) * size[2];
	dist *= 0.5;
	//
	trap_AAS_FloatForBSPEpairKey(bspent, "health", &health);
	//if the button is shootable
	if (health) {
		//calculate the shoot target
		VectorMA(origin, -dist, movedir, goalorigin);
		//
		VectorCopy(goalorigin, activategoal->target);
		activategoal->shoot = qtrue;
		//
		BotAI_Trace(&bsptrace, bs->eye, NULL, NULL, goalorigin, bs->entitynum, MASK_SHOT);
		// if the button is visible from the current position
		if (bsptrace.fraction >= 1.0 || bsptrace.ent == entitynum) {
			//
			activategoal->goal.entitynum = entitynum;	//NOTE: this is the entity number of the shootable button
			activategoal->goal.number = 0;
			activategoal->goal.flags = 0;
			VectorCopy(bs->origin, activategoal->goal.origin);
			activategoal->goal.areanum = bs->areanum;
			VectorSet(activategoal->goal.mins, -8, -8, -8);
			VectorSet(activategoal->goal.maxs, 8, 8, 8);
			//
			return qtrue;
		} else {
			//create a goal from where the button is visible and shoot at the button from there
			//add bounding box size to the dist
			trap_AAS_PresenceTypeBoundingBox(PRESENCE_CROUCH, bboxmins, bboxmaxs);
			for (i = 0; i < 3; i++) {
				if (movedir[i] < 0)
					dist += fabs(movedir[i]) * fabs(bboxmaxs[i]);
				else
					dist += fabs(movedir[i]) * fabs(bboxmins[i]);
			}
			//calculate the goal origin
			VectorMA(origin, -dist, movedir, goalorigin);
			//
			VectorCopy(goalorigin, start);
			start[2] += 24;
			VectorCopy(start, end);
			end[2] -= 512;
			numareas = trap_AAS_TraceAreas(start, end, areas, points, 10);
			//
			for (i = numareas - 1; i >= 0; i--) {
				if (trap_AAS_AreaReachability(areas[i])) {
					break;
				}
			}
			if (i < 0) {
				// FIXME: trace forward and maybe in other directions to find a valid area
			}
			if (i >= 0) {
				//
				VectorCopy(points[i], activategoal->goal.origin);
				activategoal->goal.areanum = areas[i];
				VectorSet(activategoal->goal.mins, 8, 8, 8);
				VectorSet(activategoal->goal.maxs, -8, -8, -8);
				//
				for (i = 0; i < 3; i++) {
					if (movedir[i] < 0)
						activategoal->goal.maxs[i] += fabs(movedir[i]) * fabs(extramaxs[i]);
					else
						activategoal->goal.mins[i] += fabs(movedir[i]) * fabs(extramins[i]);
				}	//end for
				//
				activategoal->goal.entitynum = entitynum;
				activategoal->goal.number = 0;
				activategoal->goal.flags = 0;
				return qtrue;
			}
		}
		return qfalse;
	} else {
		//add bounding box size to the dist
		trap_AAS_PresenceTypeBoundingBox(PRESENCE_CROUCH, bboxmins, bboxmaxs);
		for (i = 0; i < 3; i++) {
			if (movedir[i] < 0)
				dist += fabs(movedir[i]) * fabs(bboxmaxs[i]);
			else
				dist += fabs(movedir[i]) * fabs(bboxmins[i]);
		}
		//calculate the goal origin
		VectorMA(origin, -dist, movedir, goalorigin);
		//
		VectorCopy(goalorigin, start);
		start[2] += 24;
		VectorCopy(start, end);
		end[2] -= 100;
		numareas = trap_AAS_TraceAreas(start, end, areas, NULL, 10);
		//
		for (i = 0; i < numareas; i++) {
			if (trap_AAS_AreaReachability(areas[i])) {
				break;
			}
		}
		if (i < numareas) {
			//
			VectorCopy(origin, activategoal->goal.origin);
			activategoal->goal.areanum = areas[i];
			VectorSubtract(mins, origin, activategoal->goal.mins);
			VectorSubtract(maxs, origin, activategoal->goal.maxs);
			//
			for (i = 0; i < 3; i++) {
				if (movedir[i] < 0)
					activategoal->goal.maxs[i] += fabs(movedir[i]) * fabs(extramaxs[i]);
				else
					activategoal->goal.mins[i] += fabs(movedir[i]) * fabs(extramins[i]);
			}	//end for
			//
			activategoal->goal.entitynum = entitynum;
			activategoal->goal.number = 0;
			activategoal->goal.flags = 0;
			return qtrue;
		}
	}
	return qfalse;
}

/*
==================
BotFuncDoorGoal
==================
*/
int BotFuncDoorActivateGoal(bot_state_t * bs, int bspent, bot_activategoal_t * activategoal)
{
	int modelindex, entitynum;
	char model[MAX_INFO_STRING];
	vec3_t mins, maxs, origin;

	//shoot at the shootable door
	trap_AAS_ValueForBSPEpairKey(bspent, "model", model, sizeof(model));
	if (!*model)
		return qfalse;
	modelindex = atoi(model + 1);
	if (!modelindex)
		return qfalse;
	//VectorClear(angles);
	entitynum = BotModelMinsMaxs(modelindex, ET_MOVER, 0, mins, maxs);
	//door origin
	VectorAdd(mins, maxs, origin);
	VectorScale(origin, 0.5, origin);
	VectorCopy(origin, activategoal->target);
	activategoal->shoot = qtrue;
	activategoal->goal.entitynum = entitynum;	//NOTE: this is the entity number of the shootable door
	activategoal->goal.number = 0;
	activategoal->goal.flags = 0;
	VectorCopy(bs->origin, activategoal->goal.origin);
	activategoal->goal.areanum = bs->areanum;
	VectorSet(activategoal->goal.mins, -8, -8, -8);
	VectorSet(activategoal->goal.maxs, 8, 8, 8);
	return qtrue;
}

/*
====================================
BotFuncBreakableGoal

Added by Makro
Basically a rip off of the previous
function !
====================================
*/
int BotFuncBreakableGoal(bot_state_t * bs, int bspent, bot_activategoal_t * activategoal)
{
	int modelindex, entitynum;
	char model[MAX_INFO_STRING];
	vec3_t mins, maxs, origin;

	//shoot at the func_breakable
	trap_AAS_ValueForBSPEpairKey(bspent, "model", model, sizeof(model));
	if (!*model)
		return qfalse;
	modelindex = atoi(model + 1);
	if (!modelindex)
		return qfalse;
	//VectorClear(angles);
	//Makro - changing from ET_BREAKABLE to 0
	entitynum = BotModelMinsMaxs(modelindex, 0, 0, mins, maxs);
	//breakable origin
	VectorAdd(mins, maxs, origin);
	VectorScale(origin, 0.5, origin);
	VectorCopy(origin, activategoal->target);
	activategoal->shoot = qtrue;
	activategoal->goal.entitynum = entitynum;
	activategoal->goal.number = 0;
	activategoal->goal.flags = 0;
	//activategoal->weapon = WP_NUM_WEAPONS;
	activategoal->noWeapon = qtrue;
	//Makro - hmm, not quite sure this is right, but they did it for func_doors
	VectorCopy(bs->origin, activategoal->goal.origin);
	activategoal->goal.areanum = bs->areanum;
	VectorSet(activategoal->goal.mins, -8, -8, -8);
	VectorSet(activategoal->goal.maxs, 8, 8, 8);
	return qtrue;
}

/*
====================================
BotFuncDoorRotatingActivateGoal

Added by Makro
====================================
*/
int BotFuncDoorRotatingActivateGoal(bot_state_t * bs, int bspent, bot_activategoal_t * activategoal)
{
	int modelindex, entitynum;
	char model[MAX_INFO_STRING];
	vec3_t mins, maxs, origin;

	trap_AAS_ValueForBSPEpairKey(bspent, "model", model, sizeof(model));
	if (!*model)
		return qfalse;
	modelindex = atoi(model + 1);
	if (!modelindex)
		return qfalse;
	entitynum = BotModelMinsMaxs(modelindex, ET_MOVER, 0, mins, maxs);
	//door origin
	VectorAdd(mins, maxs, origin);
	VectorScale(origin, 0.5, origin);
	activategoal->goal.entitynum = entitynum;
	VectorTargetDist(bs->origin, origin, -48, activategoal->origin);
	activategoal->openDoor = qtrue;
	activategoal->goal.number = 0;
	activategoal->goal.flags = 0;
	//VectorCopy(bs->origin, activategoal->goal.origin);
	VectorCopy(activategoal->origin, activategoal->goal.origin);
	activategoal->goal.areanum = bs->areanum;
	VectorSet(activategoal->goal.mins, -8, -8, -8);
	VectorSet(activategoal->goal.maxs, 8, 8, 8);
	return qtrue;
}

/*
==================
BotTriggerMultipleGoal
==================
*/
int BotTriggerMultipleActivateGoal(bot_state_t * bs, int bspent, bot_activategoal_t * activategoal)
{
	int i, areas[10], numareas, modelindex, entitynum;
	char model[128];
	vec3_t start, end, mins, maxs;
	vec3_t origin, goalorigin;

	activategoal->shoot = qfalse;
	VectorClear(activategoal->target);
	//create a bot goal towards the trigger
	trap_AAS_ValueForBSPEpairKey(bspent, "model", model, sizeof(model));
	if (!*model)
		return qfalse;
	modelindex = atoi(model + 1);
	if (!modelindex)
		return qfalse;
	entitynum = BotModelMinsMaxs(modelindex, 0, CONTENTS_TRIGGER, mins, maxs);
	//trigger origin
	VectorAdd(mins, maxs, origin);
	VectorScale(origin, 0.5, origin);
	VectorCopy(origin, goalorigin);
	//
	VectorCopy(goalorigin, start);
	start[2] += 24;
	VectorCopy(start, end);
	end[2] -= 100;
	numareas = trap_AAS_TraceAreas(start, end, areas, NULL, 10);
	//
	for (i = 0; i < numareas; i++) {
		if (trap_AAS_AreaReachability(areas[i])) {
			break;
		}
	}
	if (i < numareas) {
		VectorCopy(origin, activategoal->goal.origin);
		activategoal->goal.areanum = areas[i];
		VectorSubtract(mins, origin, activategoal->goal.mins);
		VectorSubtract(maxs, origin, activategoal->goal.maxs);
		//
		activategoal->goal.entitynum = entitynum;
		activategoal->goal.number = 0;
		activategoal->goal.flags = 0;
		return qtrue;
	}
	return qfalse;
}

/*
==================
BotPopFromActivateGoalStack
==================
*/
int BotPopFromActivateGoalStack(bot_state_t * bs)
{
	if (!bs->activatestack)
		return qfalse;
	BotEnableActivateGoalAreas(bs->activatestack, qtrue);
	bs->activatestack->inuse = qfalse;
	bs->activatestack->justused_time = FloatTime();
	bs->activatestack = bs->activatestack->next;
	return qtrue;
}

/*
==================
BotPushOntoActivateGoalStack
==================
*/
int BotPushOntoActivateGoalStack(bot_state_t * bs, bot_activategoal_t * activategoal)
{
	int i, best;
	float besttime;

	best = -1;
	besttime = FloatTime() + 9999;
	//
	for (i = 0; i < MAX_ACTIVATESTACK; i++) {
		if (!bs->activategoalheap[i].inuse) {
			if (bs->activategoalheap[i].justused_time < besttime) {
				besttime = bs->activategoalheap[i].justused_time;
				best = i;
			}
		}
	}
	if (best != -1) {
		memcpy(&bs->activategoalheap[best], activategoal, sizeof(bot_activategoal_t));
		bs->activategoalheap[best].inuse = qtrue;
		bs->activategoalheap[best].next = bs->activatestack;
		bs->activatestack = &bs->activategoalheap[best];
		return qtrue;
	}
	return qfalse;
}

/*
==================
BotClearActivateGoalStack
==================
*/
void BotClearActivateGoalStack(bot_state_t * bs)
{
	while (bs->activatestack)
		BotPopFromActivateGoalStack(bs);
}

/*
==================
BotEnableActivateGoalAreas
==================
*/
void BotEnableActivateGoalAreas(bot_activategoal_t * activategoal, int enable)
{
	int i;

	if (activategoal->areasdisabled == !enable)
		return;
	for (i = 0; i < activategoal->numareas; i++)
		trap_AAS_EnableRoutingArea(activategoal->areas[i], enable);
	activategoal->areasdisabled = !enable;
}

/*
==================
BotIsGoingToActivateEntity
==================
*/
int BotIsGoingToActivateEntity(bot_state_t * bs, int entitynum)
{
	bot_activategoal_t *a;
	int i;

	for (a = bs->activatestack; a; a = a->next) {
		if (a->time < FloatTime())
			continue;
		if (a->goal.entitynum == entitynum)
			return qtrue;
	}
	for (i = 0; i < MAX_ACTIVATESTACK; i++) {
		if (bs->activategoalheap[i].inuse)
			continue;
		//
		if (bs->activategoalheap[i].goal.entitynum == entitynum) {
			// if the bot went for this goal less than 2 seconds ago
			if (bs->activategoalheap[i].justused_time > FloatTime() - 2)
				return qtrue;
		}
	}
	return qfalse;
}

/*
==================
BotGetActivateGoal

  returns the number of the bsp entity to activate
  goal->entitynum will be set to the game entity to activate
==================
*/
//#define OBSTACLEDEBUG

int BotGetActivateGoal(bot_state_t * bs, int entitynum, bot_activategoal_t * activategoal)
{
	int i, ent, cur_entities[10], spawnflags, modelindex, areas[MAX_ACTIVATEAREAS * 2], numareas, t;
	char model[MAX_INFO_STRING], tmpmodel[128];
	char target[128], classname[128];
	float health;
	char targetname[10][128];
	aas_entityinfo_t entinfo;
	aas_areainfo_t areainfo;
	vec3_t origin, absmins, absmaxs;

	memset(activategoal, 0, sizeof(bot_activategoal_t));
	BotEntityInfo(entitynum, &entinfo);
	Com_sprintf(model, sizeof(model), "*%d", entinfo.modelindex);
	for (ent = trap_AAS_NextBSPEntity(0); ent; ent = trap_AAS_NextBSPEntity(ent)) {
		if (!trap_AAS_ValueForBSPEpairKey(ent, "model", tmpmodel, sizeof(tmpmodel)))
			continue;
		if (!strcmp(model, tmpmodel))
			break;
	}
	if (!ent) {
		BotAI_Print(PRT_ERROR, "BotGetActivateGoal: no entity found with model %s\n", model);
		return 0;
	}
	trap_AAS_ValueForBSPEpairKey(ent, "classname", classname, sizeof(classname));
	if (!*classname) {
		BotAI_Print(PRT_ERROR, "BotGetActivateGoal: entity with model %s has no classname\n", model);
		return 0;
	}
	//if it is a door
	//Makro - or a door_rotating
	if (!strcmp(classname, "func_door") || !strcmp(classname, "func_door_rotating")) {
		qboolean rotating = (strcmp(classname, "func_door_rotating") == 0);

		if (trap_AAS_FloatForBSPEpairKey(ent, "health", &health)) {
			//if the door has health then the door must be shot to open
			if (health) {
				BotFuncDoorActivateGoal(bs, ent, activategoal);
				return ent;
			}
		}
		//
		trap_AAS_IntForBSPEpairKey(ent, "spawnflags", &spawnflags);
		// if the door starts open then just wait for the door to return
		// Makro - only if toggle is not set
		if ((spawnflags & 1) && !(spawnflags & 8))
			return 0;
		//get the door origin
		if (!trap_AAS_VectorForBSPEpairKey(ent, "origin", origin)) {
			VectorClear(origin);
		}
		//if the door is open or opening already
		//Makro - different code for rotating doors
		if (!rotating) {
			if (!VectorCompare(origin, entinfo.origin))
				return 0;
		} else {
			if (g_entities[entinfo.number].moverState == ROTATOR_1TO2
			    || g_entities[entinfo.number].moverState == ROTATOR_2TO1)
				return 0;
		}
		// store all the areas the door is in
		trap_AAS_ValueForBSPEpairKey(ent, "model", model, sizeof(model));
		if (*model) {
			modelindex = atoi(model + 1);
			if (modelindex) {
				BotModelMinsMaxs(modelindex, ET_MOVER, 0, absmins, absmaxs);
				//
				numareas = trap_AAS_BBoxAreas(absmins, absmaxs, areas, MAX_ACTIVATEAREAS * 2);
				// store the areas with reachabilities first
				for (i = 0; i < numareas; i++) {
					if (activategoal->numareas >= MAX_ACTIVATEAREAS)
						break;
					if (!trap_AAS_AreaReachability(areas[i])) {
						continue;
					}
					trap_AAS_AreaInfo(areas[i], &areainfo);
					if (areainfo.contents & AREACONTENTS_MOVER) {
						activategoal->areas[activategoal->numareas++] = areas[i];
					}
				}
				// store any remaining areas
				for (i = 0; i < numareas; i++) {
					if (activategoal->numareas >= MAX_ACTIVATEAREAS)
						break;
					if (trap_AAS_AreaReachability(areas[i])) {
						continue;
					}
					trap_AAS_AreaInfo(areas[i], &areainfo);
					if (areainfo.contents & AREACONTENTS_MOVER) {
						activategoal->areas[activategoal->numareas++] = areas[i];
					}
				}
			}
			//Makro - open the door
			if (!g_entities[entinfo.number].targetname) {
				if (!rotating) {
					Cmd_OpenDoor(&g_entities[bs->entitynum]);
					return 0;
				} else {
					BotMoveTowardsEnt(bs, entinfo.origin, -80);
					//BotMoveTowardsEnt(bs, g_entities[entinfo.number].s.origin2, -80);
					//BotFuncDoorRotatingActivateGoal(bs, ent, activategoal);
					Cmd_OpenDoor(&g_entities[bs->entitynum]);
					return 0;
				}
			}
		}
	}
	//if it is some glass
	if (!strcmp(classname, "func_breakable")) {
		//disable all areas the blocking entity is in
		BotEnableActivateGoalAreas(activategoal, qfalse);
		//nothing the bot can do to unbreakable glass
		if (g_entities[entinfo.number].unbreakable)
			return 0;
		if (!g_entities[entinfo.number].targetname) {
			BotFuncBreakableGoal(bs, ent, activategoal);
			return ent;
		}
	}
	/* Handled above now
	   //Makro - checking for rotating doors
	   if ( !strcmp(classname, "func_door_rotating") ) {
	   //if door is moving, wait till it stops
	   if ( g_entities[entitynum].moverState == ROTATOR_1TO2 || g_entities[entitynum].moverState == ROTATOR_2TO1 || (g_entities[entitynum].targetname) ) {
	   BotMoveTowardsEnt(bs, entinfo.origin, -80);
	   if ( g_entities[entitynum].targetname == NULL ) {
	   return 0;
	   }
	   } else {
	   //Cmd_OpenDoor( &g_entities[bs->entitynum] );
	   BotFuncDoorRotatingActivateGoal(bs, ent, activategoal);
	   //disable all areas the blocking entity is in
	   BotEnableActivateGoalAreas( activategoal, qfalse );
	   return ent;
	   }
	   } */
	// if the bot is blocked by or standing on top of a button
	if (!strcmp(classname, "func_button")) {
		return 0;
	}
	// get the targetname so we can find an entity with a matching target
	if (!trap_AAS_ValueForBSPEpairKey(ent, "targetname", targetname[0], sizeof(targetname[0]))) {
		if (bot_developer.integer) {
			BotAI_Print(PRT_ERROR, "BotGetActivateGoal: entity with model \"%s\" has no targetname\n",
				    model);
		}
		return 0;
	}
	// allow tree-like activation
	cur_entities[0] = trap_AAS_NextBSPEntity(0);
	for (i = 0; i >= 0 && i < 10;) {
		for (ent = cur_entities[i]; ent; ent = trap_AAS_NextBSPEntity(ent)) {
			if (!trap_AAS_ValueForBSPEpairKey(ent, "target", target, sizeof(target)))
				continue;
			if (!strcmp(targetname[i], target)) {
				cur_entities[i] = trap_AAS_NextBSPEntity(ent);
				break;
			}
		}
		if (!ent) {
			if (bot_developer.integer) {
				BotAI_Print(PRT_ERROR, "BotGetActivateGoal: no entity with target \"%s\"\n",
					    targetname[i]);
			}
			i--;
			continue;
		}
		if (!trap_AAS_ValueForBSPEpairKey(ent, "classname", classname, sizeof(classname))) {
			if (bot_developer.integer) {
				BotAI_Print(PRT_ERROR,
					    "BotGetActivateGoal: entity with target \"%s\" has no classname\n",
					    targetname[i]);
			}
			continue;
		}
		// BSP button model
		if (!strcmp(classname, "func_button")) {
			//
			if (!BotFuncButtonActivateGoal(bs, ent, activategoal))
				continue;
			// if the bot tries to activate this button already
			if (bs->activatestack && bs->activatestack->inuse &&
			    bs->activatestack->goal.entitynum == activategoal->goal.entitynum &&
			    bs->activatestack->time > FloatTime() && bs->activatestack->start_time < FloatTime() - 2)
				continue;
			// if the bot is in a reachability area
			if (trap_AAS_AreaReachability(bs->areanum)) {
				// disable all areas the blocking entity is in
				BotEnableActivateGoalAreas(activategoal, qfalse);
				//
				t = trap_AAS_AreaTravelTimeToGoalArea(bs->areanum, bs->origin,
								      activategoal->goal.areanum, bs->tfl);
				// if the button is not reachable
				if (!t) {
					continue;
				}
				activategoal->time = FloatTime() + t * 0.01 + 5;
			}
			return ent;
		}
		// invisible trigger multiple box
		else if (!strcmp(classname, "trigger_multiple")) {
			//
			if (!BotTriggerMultipleActivateGoal(bs, ent, activategoal))
				continue;
			// if the bot tries to activate this trigger already
			if (bs->activatestack && bs->activatestack->inuse &&
			    bs->activatestack->goal.entitynum == activategoal->goal.entitynum &&
			    bs->activatestack->time > FloatTime() && bs->activatestack->start_time < FloatTime() - 2)
				continue;
			// if the bot is in a reachability area
			if (trap_AAS_AreaReachability(bs->areanum)) {
				// disable all areas the blocking entity is in
				BotEnableActivateGoalAreas(activategoal, qfalse);
				//
				t = trap_AAS_AreaTravelTimeToGoalArea(bs->areanum, bs->origin,
								      activategoal->goal.areanum, bs->tfl);
				// if the trigger is not reachable
				if (!t) {
					continue;
				}
				activategoal->time = FloatTime() + t * 0.01 + 5;
			}
			return ent;
		} else if (!strcmp(classname, "func_timer")) {
			// just skip the func_timer
			continue;
		}
		// the actual button or trigger might be linked through a target_relay or target_delay
		else if (!strcmp(classname, "target_relay") || !strcmp(classname, "target_delay")) {
			if (trap_AAS_ValueForBSPEpairKey(ent, "targetname", targetname[i + 1], sizeof(targetname[0]))) {
				i++;
				cur_entities[i] = trap_AAS_NextBSPEntity(0);
			}
		}
	}
#ifdef OBSTACLEDEBUG
	BotAI_Print(PRT_ERROR, "BotGetActivateGoal: no valid activator for entity with target \"%s\"\n", targetname[0]);
#endif
	return 0;
}

/*
==================
BotGoForActivateGoal
==================
*/
int BotGoForActivateGoal(bot_state_t * bs, bot_activategoal_t * activategoal)
{
	aas_entityinfo_t activateinfo;

	activategoal->inuse = qtrue;
	if (!activategoal->time)
		activategoal->time = FloatTime() + 10;
	activategoal->start_time = FloatTime();
	BotEntityInfo(activategoal->goal.entitynum, &activateinfo);
	VectorCopy(activateinfo.origin, activategoal->origin);
	//
	if (BotPushOntoActivateGoalStack(bs, activategoal)) {
		// enter the activate entity AI node
		AIEnter_Seek_ActivateEntity(bs, "BotGoForActivateGoal");
		return qtrue;
	} else {
		// enable any routing areas that were disabled
		BotEnableActivateGoalAreas(activategoal, qtrue);
		return qfalse;
	}
}

/*
==================
BotPrintActivateGoalInfo
==================
*/
void BotPrintActivateGoalInfo(bot_state_t * bs, bot_activategoal_t * activategoal, int bspent)
{
	char netname[MAX_NETNAME];
	char classname[128];
	char buf[128];

	ClientName(bs->client, netname, sizeof(netname));
	trap_AAS_ValueForBSPEpairKey(bspent, "classname", classname, sizeof(classname));
	if (activategoal->shoot) {
		Com_sprintf(buf, sizeof(buf), "%s: I have to shoot at a %s from %1.1f %1.1f %1.1f in area %d\n",
			    netname, classname,
			    activategoal->goal.origin[0],
			    activategoal->goal.origin[1], activategoal->goal.origin[2], activategoal->goal.areanum);
	} else {
		Com_sprintf(buf, sizeof(buf), "%s: I have to activate a %s at %1.1f %1.1f %1.1f in area %d\n",
			    netname, classname,
			    activategoal->goal.origin[0],
			    activategoal->goal.origin[1], activategoal->goal.origin[2], activategoal->goal.areanum);
	}
	trap_EA_Say(bs->client, buf);
}

/*
==================
BotRandomMove
==================
*/
void BotRandomMove(bot_state_t * bs, bot_moveresult_t * moveresult)
{
	vec3_t dir, angles;

	angles[0] = 0;
	angles[1] = random() * 360;
	angles[2] = 0;
	AngleVectors(angles, dir, NULL, NULL);

	trap_BotMoveInDirection(bs->ms, dir, 400, MOVE_WALK);

	moveresult->failure = qfalse;
	VectorCopy(dir, moveresult->movedir);
}

/*
==================
BotAIBlocked

Very basic handling of bots being blocked by other entities.
Check what kind of entity is blocking the bot and try to activate
it. If that's not an option then try to walk around or over the entity.
Before the bot ends in this part of the AI it should predict which doors to
open, which buttons to activate etc.
==================
*/
void BotAIBlocked(bot_state_t * bs, bot_moveresult_t * moveresult, int activate)
{
#ifdef OBSTACLEDEBUG
	char netname[MAX_NETNAME];
#endif
	int movetype, bspent;
	vec3_t hordir, sideward, angles, up = {0, 0, 1};
	//vec3_t start, end, mins, maxs;
	aas_entityinfo_t entinfo;
	bot_activategoal_t activategoal;

	// if the bot is not blocked by anything
	if (!moveresult->blocked) {
		bs->notblocked_time = FloatTime();
		return;
	}
	// if stuck in a solid area
	if (moveresult->type == RESULTTYPE_INSOLIDAREA) {
		// move in a random direction in the hope to get out
		BotRandomMove(bs, moveresult);
		//
		return;
	}
	// get info for the entity that is blocking the bot
	BotEntityInfo(moveresult->blockentity, &entinfo);
#ifdef OBSTACLEDEBUG
	ClientName(bs->client, netname, sizeof(netname));
	BotAI_Print(PRT_MESSAGE, "%s: I'm blocked by model %d\n", netname, entinfo.modelindex);
// JBravo: silencing a compiler warning by commenting out text after endif
#endif				/* OBSTACLEDEBUG */
	// if blocked by a bsp model and the bot wants to activate it
	if (activate && entinfo.modelindex > 0 && entinfo.modelindex <= max_bspmodelindex) {
		// find the bsp entity which should be activated in order to get the blocking entity out of the way
		bspent = BotGetActivateGoal(bs, entinfo.number, &activategoal);
		if (bspent) {
			//
			if (bs->activatestack && !bs->activatestack->inuse)
				bs->activatestack = NULL;
			// if not already trying to activate this entity
			if (!BotIsGoingToActivateEntity(bs, activategoal.goal.entitynum)) {
				//
				BotGoForActivateGoal(bs, &activategoal);
			}
			// if ontop of an obstacle or
			// if the bot is not in a reachability area it'll still
			// need some dynamic obstacle avoidance, otherwise return
			if (!(moveresult->flags & MOVERESULT_ONTOPOFOBSTACLE) && trap_AAS_AreaReachability(bs->areanum))
				return;
		} else {
			// enable any routing areas that were disabled
			BotEnableActivateGoalAreas(&activategoal, qtrue);
		}
	}
	//just some basic dynamic obstacle avoidance code
	hordir[0] = moveresult->movedir[0];
	hordir[1] = moveresult->movedir[1];
	hordir[2] = 0;
	//if no direction just take a random direction
	if (VectorNormalize(hordir) < 0.1) {
		VectorSet(angles, 0, 360 * random(), 0);
		AngleVectors(angles, hordir, NULL, NULL);
	}
	//
	//if (moveresult->flags & MOVERESULT_ONTOPOFOBSTACLE) movetype = MOVE_JUMP;
	//else
	movetype = MOVE_WALK;
	//if there's an obstacle at the bot's feet and head then
	//the bot might be able to crouch through
	//VectorCopy(bs->origin, start);
	//start[2] += 18;
	//VectorMA(start, 5, hordir, end);
	//VectorSet(mins, -16, -16, -24);
	//VectorSet(maxs, 16, 16, 4);
	//
	//bsptrace = AAS_Trace(start, mins, maxs, end, bs->entitynum, MASK_PLAYERSOLID);
	//if (bsptrace.fraction >= 1) movetype = MOVE_CROUCH;
	//get the sideward vector
	CrossProduct(hordir, up, sideward);
	//
	if (bs->flags & BFL_AVOIDRIGHT)
		VectorNegate(sideward, sideward);
	//try to crouch straight forward?
	if (movetype != MOVE_CROUCH || !trap_BotMoveInDirection(bs->ms, hordir, 400, movetype)) {
		//perform the movement
		if (!trap_BotMoveInDirection(bs->ms, sideward, 400, movetype)) {
			//flip the avoid direction flag
			bs->flags ^= BFL_AVOIDRIGHT;
			//flip the direction
			// VectorNegate(sideward, sideward);
			VectorMA(sideward, -1, hordir, sideward);
			//move in the other direction
			trap_BotMoveInDirection(bs->ms, sideward, 400, movetype);
		}
	}
	//
	if (bs->notblocked_time < FloatTime() - 0.4) {
		// just reset goals and hope the bot will go into another direction?
		//is this still needed??
		if (bs->ainode == AINode_Seek_NBG)
			bs->nbg_time = 0;
		else if (bs->ainode == AINode_Seek_LTG)
			bs->ltg_time = 0;
	}
}

/*
==================
BotAIPredictObstacles

Predict the route towards the goal and check if the bot
will be blocked by certain obstacles. When the bot has obstacles
on it's path the bot should figure out if they can be removed
by activating certain entities.
==================
*/
int BotAIPredictObstacles(bot_state_t * bs, bot_goal_t * goal)
{
	int modelnum, entitynum, bspent;
	bot_activategoal_t activategoal;
	aas_predictroute_t route;

	if (!bot_predictobstacles.integer)
		return qfalse;

	// always predict when the goal change or at regular intervals
	if (bs->predictobstacles_goalareanum == goal->areanum && bs->predictobstacles_time > FloatTime() - 6) {
		return qfalse;
	}
	bs->predictobstacles_goalareanum = goal->areanum;
	bs->predictobstacles_time = FloatTime();

	// predict at most 100 areas or 1 second ahead
	trap_AAS_PredictRoute(&route, bs->areanum, bs->origin,
			      goal->areanum, bs->tfl, 100, 1000,
			      RSE_USETRAVELTYPE | RSE_ENTERCONTENTS, AREACONTENTS_MOVER, TFL_BRIDGE, 0);
	// if bot has to travel through an area with a mover
	if (route.stopevent & RSE_ENTERCONTENTS) {
		// if the bot will run into a mover
		if (route.endcontents & AREACONTENTS_MOVER) {
			//NOTE: this only works with bspc 2.1 or higher
			modelnum = (route.endcontents & AREACONTENTS_MODELNUM) >> AREACONTENTS_MODELNUMSHIFT;
			if (modelnum) {
				//
				entitynum = BotModelMinsMaxs(modelnum, ET_MOVER, 0, NULL, NULL);
				if (entitynum) {
					//NOTE: BotGetActivateGoal already checks if the door is open or not
					bspent = BotGetActivateGoal(bs, entitynum, &activategoal);
					if (bspent) {
						//
						if (bs->activatestack && !bs->activatestack->inuse)
							bs->activatestack = NULL;
						// if not already trying to activate this entity
						if (!BotIsGoingToActivateEntity(bs, activategoal.goal.entitynum)) {
							//
							//BotAI_Print(PRT_MESSAGE, "blocked by mover model %d, entity %d ?\n", modelnum, entitynum);
							//
							BotGoForActivateGoal(bs, &activategoal);
							return qtrue;
						} else {
							// enable any routing areas that were disabled
							BotEnableActivateGoalAreas(&activategoal, qtrue);
						}
					}
				}
			}
		}
	} else if (route.stopevent & RSE_USETRAVELTYPE) {
		if (route.endtravelflags & TFL_BRIDGE) {
			//FIXME: check if the bridge is available to travel over
		}
	}
	return qfalse;
}

#define BOT_RADIO_REPLY_TIME	2

/*
==================
BotReplyToRadioMessage

Added by Makro
==================
*/
void BotReplyToRadioMessage(bot_state_t * bs, char *msg, int handle)
{

	//Must be in a team-based game to reply
	if (gametype < GT_TEAM) {
		return;
	}
	//Bot must be alive to report
	if (!BotIsDead(bs)) {
		char *token;
		char *initial = msg;

		token = COM_ParseExt(&msg, qtrue);
		if (!Q_stricmp(token, "radio")) {
			qboolean willreply;

			//The bot is more likely to reply if you don't spam him with treport's
			if (bs->radioresponse_count > 15) {
				willreply = (random() < 0.3);
			} else if (bs->radioresponse_count > 10) {
				willreply = (random() < 0.5);
			} else if (bs->radioresponse_count > 5) {
				willreply = (random() < 0.7);
			} else {
				willreply = (random() < 0.9);
			}

			//Bots won't reply to ALL radio messages; they do have a life, you know
			if ((willreply)
			    && (FloatTime() >
				BOT_RADIO_REPLY_TIME +
				bs->radioresponse_time) /*&& (bs->radioresponse_count < 20) */ ) {
				char *sender = COM_ParseExt(&msg, qtrue);
				qboolean responded = qfalse;

				//Lazy bots
				if (random() < 0.5) {
					//sender = Q_strlwr(sender);
					EasyClientName(ClientFromName(sender), sender, 32);
				}

				if (strstr(msg, "treport")) {
					//Team, report in
					G_Say(&g_entities[bs->entitynum], NULL, SAY_TEAM,
					      va("%s, I have a $W with $A ammo and $H health", sender));
					responded = qtrue;
				}

				/*
				   if (strstr(msg, "im_hit")) {
				   int senderId = ClientFromName(sender);
				   if (senderId != -1) {
				   BotMoveTo(bs, g_entities[senderId].r.currentOrigin);
				   G_Printf("%s: coming over to %s\n", g_entities[bs->entitynum].client->pers.netname, g_entities[senderId].client->pers.netname);
				   responded = qtrue;
				   }
				   }
				 */

				if (responded) {
					bs->radioresponse_time = FloatTime();
					bs->radioresponse_count++;
				}
				//TODO:
				// - Add code that makes the bot move towards
				//   the player that sent the radio message
				// - Prioritize teamdown, taking_f, im_hit
				//   over enemyd and enemys
				// - Make the bot talk dirty to spammers
			}
		}
		msg = initial;
	}
}

/*
==================
BotCheckRadioMessage

Added by Makro
==================
*/
qboolean BotCheckRadioMessage(bot_state_t * bs, char *msg, int handle)
{
	char *token;
	char *initial = msg;

	//Must be in a team-based game to reply
	if (gametype < GT_TEAM) {
		return qfalse;
	}

	token = COM_ParseExt(&msg, qtrue);
	msg = initial;
	if (!Q_stricmp(token, "radio")) {
		return qtrue;
	}

	return qfalse;
}

/*
==================
BotCheckConsoleMessages
==================
*/
void BotCheckConsoleMessages(bot_state_t * bs)
{
	char botname[MAX_NETNAME], message[MAX_MESSAGE_SIZE], netname[MAX_NETNAME], *ptr;
	float chat_reply;
	int context, handle;
	bot_consolemessage_t m;
	bot_match_t match;
	qboolean radio;

	//the name of this bot
	ClientName(bs->client, botname, sizeof(botname));
	//
	while ((handle = trap_BotNextConsoleMessage(bs->cs, &m)) != 0) {
		//if the chat state is flooded with messages the bot will read them quickly
		if (trap_BotNumConsoleMessages(bs->cs) < 10) {
			//if it is a chat message the bot needs some time to read it
			if (m.type == CMS_CHAT && m.time > FloatTime() - (1 + random()))
				break;
		}
		//Makro - check for radio commands
		radio = BotCheckRadioMessage(bs, m.message, handle);
		if (radio) {
			//The bot needs at least two seconds to reply
			if (FloatTime() > (m.time + 2 + random() * 2)) {
				BotReplyToRadioMessage(bs, m.message, handle);
				//remove the console message
				trap_BotRemoveConsoleMessage(bs->cs, handle);
				continue;
			} else {
				//Too soon to reply
				break;
			}
		}
		//
		ptr = m.message;
		//if it is a chat message then don't unify white spaces and don't
		//replace synonyms in the netname
		if (m.type == CMS_CHAT) {
			//
			if (trap_BotFindMatch(m.message, &match, MTCONTEXT_REPLYCHAT)) {
				ptr = m.message + match.variables[MESSAGE].offset;
			}
		}
		//unify the white spaces in the message
		trap_UnifyWhiteSpaces(ptr);
		//replace synonyms in the right context
		context = BotSynonymContext(bs);
		trap_BotReplaceSynonyms(ptr, context);
		//if there's no match
		if (!BotMatchMessage(bs, m.message)) {
			//if it is a chat message
			if (m.type == CMS_CHAT && !bot_nochat.integer) {
				//
				if (!trap_BotFindMatch(m.message, &match, MTCONTEXT_REPLYCHAT)) {
					trap_BotRemoveConsoleMessage(bs->cs, handle);
					continue;
				}
				//don't use eliza chats with team messages
				if (match.subtype & ST_TEAM) {
					trap_BotRemoveConsoleMessage(bs->cs, handle);
					continue;
				}
				//
				trap_BotMatchVariable(&match, NETNAME, netname, sizeof(netname));
				trap_BotMatchVariable(&match, MESSAGE, message, sizeof(message));
				//if this is a message from the bot self
				if (bs->client == ClientFromName(netname)) {
					trap_BotRemoveConsoleMessage(bs->cs, handle);
					continue;
				}
				//unify the message
				trap_UnifyWhiteSpaces(message);
				//
				trap_Cvar_Update(&bot_testrchat);
				if (bot_testrchat.integer) {
					//
					trap_BotLibVarSet("bot_testrchat", "1");
					//if bot replies with a chat message
					if (trap_BotReplyChat(bs->cs, message, context, CONTEXT_REPLY,
							      NULL, NULL, NULL, NULL, NULL, NULL, botname, netname)) {
						BotAI_Print(PRT_MESSAGE, "------------------------\n");
					} else {
						BotAI_Print(PRT_MESSAGE, "**** no valid reply ****\n");
					}
				}
				//if at a valid chat position and not chatting already and not in teamplay
				else if (bs->ainode != AINode_Stand && BotValidChatPosition(bs) && !TeamPlayIsOn()) {
					chat_reply =
					    trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_CHAT_REPLY, 0, 1);
					if (random() < 1.5 / (NumBots() + 1) && random() < chat_reply) {
						//if bot replies with a chat message
						if (trap_BotReplyChat(bs->cs, message, context, CONTEXT_REPLY,
								      NULL, NULL,
								      NULL, NULL, NULL, NULL, botname, netname)) {
							//remove the console message
							trap_BotRemoveConsoleMessage(bs->cs, handle);
							bs->stand_time = FloatTime() + BotChatTime(bs);
							AIEnter_Stand(bs, "BotCheckConsoleMessages: reply chat");
							//EA_Say(bs->client, bs->cs.chatmessage);
							break;
						}
					}
				}
			}
		}
		//remove the console message
		trap_BotRemoveConsoleMessage(bs->cs, handle);
	}
}

/*
==================
BotCheckEvents
==================
*/
void BotCheckForGrenades(bot_state_t * bs, entityState_t * state)
{
	// if this is not a grenade
	if (state->eType != ET_MISSILE || state->weapon != WP_GRENADE)
		return;
	// try to avoid the grenade
	trap_BotAddAvoidSpot(bs->ms, state->pos.trBase, 160, AVOID_ALWAYS);
}

/*
==================
BotCheckEvents
==================
*/
void BotCheckEvents(bot_state_t * bs, entityState_t * state)
{
	int event;
	char buf[128];

	//NOTE: this sucks, we're accessing the gentity_t directly
	//but there's no other fast way to do it right now
	if (bs->entityeventTime[state->number] == g_entities[state->number].eventTime) {
		return;
	}
	bs->entityeventTime[state->number] = g_entities[state->number].eventTime;
	//if it's an event only entity
	if (state->eType > ET_EVENTS) {
		event = (state->eType - ET_EVENTS) & ~EV_EVENT_BITS;
	} else {
		event = state->event & ~EV_EVENT_BITS;
	}
	//
	switch (event) {
		//client obituary event
	case EV_OBITUARY:
		{
			int target, attacker, mod;

			target = state->otherEntityNum;
			attacker = state->otherEntityNum2;
			mod = state->eventParm;
			//
			if (target == bs->client) {
				bs->botdeathtype = mod;
				bs->lastkilledby = attacker;
				//
				if (target == attacker || target == ENTITYNUM_NONE || target == ENTITYNUM_WORLD)
					bs->botsuicide = qtrue;
				else
					bs->botsuicide = qfalse;
				//
				bs->num_deaths++;
			}
			//else if this client was killed by the bot
			else if (attacker == bs->client) {
				bs->enemydeathtype = mod;
				bs->lastkilledplayer = target;
				bs->killedenemy_time = FloatTime();
				//
				bs->num_kills++;
			} else if (attacker == bs->enemy && target == attacker) {
				bs->enemysuicide = qtrue;
			}
			break;
		}
	case EV_GLOBAL_SOUND:
		{
			if (state->eventParm < 0 || state->eventParm >= MAX_SOUNDS) {
				BotAI_Print(PRT_ERROR, "EV_GLOBAL_SOUND: eventParm (%d) out of range\n",
					    state->eventParm);
				break;
			}
			trap_GetConfigstring(CS_SOUNDS + state->eventParm, buf, sizeof(buf));
			/*
			   if (!strcmp(buf, "sound/teamplay/flagret_red.wav")) {
			   //red flag is returned
			   bs->redflagstatus = 0;
			   bs->flagstatuschanged = qtrue;
			   }
			   else if (!strcmp(buf, "sound/teamplay/flagret_blu.wav")) {
			   //blue flag is returned
			   bs->blueflagstatus = 0;
			   bs->flagstatuschanged = qtrue;
			   }
			   else */
			if (!strcmp(buf, "sound/items/poweruprespawn.wav")) {
				//powerup respawned... go get it
				BotGoForPowerups(bs);
			}
			break;
		}
	case EV_GLOBAL_TEAM_SOUND:
		{
			if (gametype == GT_CTF) {
				switch (state->eventParm) {
				case GTS_RED_CAPTURE:
					bs->blueflagstatus = 0;
					bs->redflagstatus = 0;
					bs->flagstatuschanged = qtrue;
					break;	//see BotMatch_CTF
				case GTS_BLUE_CAPTURE:
					bs->blueflagstatus = 0;
					bs->redflagstatus = 0;
					bs->flagstatuschanged = qtrue;
					break;	//see BotMatch_CTF
				case GTS_RED_RETURN:
					//blue flag is returned
					bs->blueflagstatus = 0;
					bs->flagstatuschanged = qtrue;
					break;
				case GTS_BLUE_RETURN:
					//red flag is returned
					bs->redflagstatus = 0;
					bs->flagstatuschanged = qtrue;
					break;
				case GTS_RED_TAKEN:
					//blue flag is taken
					bs->blueflagstatus = 1;
					bs->flagstatuschanged = qtrue;
					break;	//see BotMatch_CTF
				case GTS_BLUE_TAKEN:
					//red flag is taken
					bs->redflagstatus = 1;
					bs->flagstatuschanged = qtrue;
					break;	//see BotMatch_CTF
				}
			}
			break;
		}
	case EV_PLAYER_TELEPORT_IN:
		{
			VectorCopy(state->origin, lastteleport_origin);
			lastteleport_time = FloatTime();
			break;
		}
	case EV_GENERAL_SOUND:
		{
			//if this sound is played on the bot
			if (state->number == bs->client) {
				if (state->eventParm < 0 || state->eventParm >= MAX_SOUNDS) {
					BotAI_Print(PRT_ERROR, "EV_GENERAL_SOUND: eventParm (%d) out of range\n",
						    state->eventParm);
					break;
				}
				//check out the sound
				trap_GetConfigstring(CS_SOUNDS + state->eventParm, buf, sizeof(buf));
				//if falling into a death pit
				if (!strcmp(buf, "*falling1.wav")) {
					//if the bot has a personal teleporter
					if (bs->inventory[INVENTORY_TELEPORTER] > 0) {
						//use the holdable item
						trap_EA_Use(bs->client);
					}
				}
			}
			break;
		}
	case EV_FOOTSTEP:
	case EV_FOOTSTEP_METAL:
	case EV_FOOTSTEP_GRASS:	// Elder: new surfaces
	case EV_FOOTSTEP_WOOD:
	case EV_FOOTSTEP_CARPET:
	case EV_FOOTSTEP_METAL2:
	case EV_FOOTSTEP_GRAVEL:
	case EV_FOOTSTEP_SNOW:	// JBravo: new surfaces
	case EV_FOOTSTEP_MUD:
	case EV_FOOTSTEP_WOOD2:
	case EV_FOOTSTEP_HARDMETAL:
	case EV_FOOTSTEP_LEAVES:	// Makro: new surfaces
	case EV_FOOTSTEP_CEMENT:
	case EV_FOOTSTEP_MARBLE:
	case EV_FOOTSTEP_SNOW2:
	case EV_FOOTSTEP_HARDSTEPS:
	case EV_FOOTSTEP_SAND:
	case EV_FOOTSPLASH:
	case EV_FOOTWADE:
	case EV_SWIM:
	case EV_FALL_SHORT:
		break;
	case EV_FALL_MEDIUM:
	case EV_FALL_FAR:
	case EV_FALL_FAR_NOSOUND:	// Makro - check for falling damage
		{
			if (RQ3_Bot_NeedToBandage(bs) == 2) {
				qboolean willBandage = qfalse;

				//Makro - this is the attack skill, we should be using the overall skill
				int skill =
				    trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_ATTACK_SKILL, 0, 1);
				//if the bot isn't in the middle of a fight
				if (bs->enemy == -1) {
					if (BotFindEnemy(bs, -1)) {
						//if an enemy is nearby, a smart bot won't bandage
						willBandage = (random() > skill);
					} else {
						//but it will otherwise
						willBandage = (random() > (1.0f - skill));
					}
				} else {
					//smart bots don't bandage during a fight
					willBandage = (random() > skill);
				}
				if (willBandage) {
					Cmd_Bandage(&g_entities[bs->entitynum]);
				}
			}
		}
	case EV_STEP_4:
	case EV_STEP_8:
	case EV_STEP_12:
	case EV_STEP_16:
	case EV_JUMP_PAD:
	case EV_JUMP:
	case EV_TAUNT:
	case EV_WATER_TOUCH:
	case EV_WATER_LEAVE:
	case EV_WATER_UNDER:
	case EV_WATER_CLEAR:
	case EV_ITEM_PICKUP:
	case EV_GLOBAL_ITEM_PICKUP:
	case EV_NOAMMO:
	case EV_CHANGE_WEAPON:
	case EV_FIRE_WEAPON:
		//FIXME: either add to sound queue or mark player as someone making noise
		break;
	case EV_USE_ITEM0:
	case EV_USE_ITEM1:
	case EV_USE_ITEM2:
	case EV_USE_ITEM3:
	case EV_USE_ITEM4:
	case EV_USE_ITEM5:
	case EV_USE_ITEM6:
	case EV_USE_ITEM7:
	case EV_USE_ITEM8:
	case EV_USE_ITEM9:
	case EV_USE_ITEM10:
	case EV_USE_ITEM11:
	case EV_USE_ITEM12:
	case EV_USE_ITEM13:
	case EV_USE_ITEM14:
	case EV_USE_ITEM15:
		break;
	}
}

/*
==================
BotCheckSnapshot
==================
*/
void BotCheckSnapshot(bot_state_t * bs)
{
	int ent;
	entityState_t state;

	//remove all avoid spots
	trap_BotAddAvoidSpot(bs->ms, vec3_origin, 0, AVOID_CLEAR);
	//reset kamikaze body
	bs->kamikazebody = 0;
	//reset number of proxmines
	bs->numproxmines = 0;
	//
	ent = 0;
	while ((ent = BotAI_GetSnapshotEntity(bs->client, ent, &state)) != -1) {
		//check the entity state for events
		BotCheckEvents(bs, &state);
		//check for grenades the bot should avoid
		BotCheckForGrenades(bs, &state);
	}
	//check the player state for events
	BotAI_GetEntityState(bs->client, &state);
	//copy the player state events to the entity state
	state.event = bs->cur_ps.externalEvent;
	state.eventParm = bs->cur_ps.externalEventParm;
	//
	BotCheckEvents(bs, &state);
}

/*
==================
BotCheckAir
==================
*/
void BotCheckAir(bot_state_t * bs)
{
	bs->lastair_time = FloatTime();
}

/*
==================
BotAlternateRoute
==================
*/
bot_goal_t *BotAlternateRoute(bot_state_t * bs, bot_goal_t * goal)
{
	int t;

	// if the bot has an alternative route goal
	if (bs->altroutegoal.areanum) {
		//
		if (bs->reachedaltroutegoal_time)
			return goal;
		// travel time towards alternative route goal
		t = trap_AAS_AreaTravelTimeToGoalArea(bs->areanum, bs->origin, bs->altroutegoal.areanum, bs->tfl);
		if (t && t < 20) {
			//BotAI_Print(PRT_MESSAGE, "reached alternate route goal\n");
			bs->reachedaltroutegoal_time = FloatTime();
		}
		memcpy(goal, &bs->altroutegoal, sizeof(bot_goal_t));
		return &bs->altroutegoal;
	}
	return goal;
}

/*
==================
BotGetAlternateRouteGoal
==================
*/
int BotGetAlternateRouteGoal(bot_state_t * bs, int base)
{
	aas_altroutegoal_t *altroutegoals;
	bot_goal_t *goal;
	int numaltroutegoals, rnd;

	if (base == TEAM_RED) {
		altroutegoals = red_altroutegoals;
		numaltroutegoals = red_numaltroutegoals;
	} else {
		altroutegoals = blue_altroutegoals;
		numaltroutegoals = blue_numaltroutegoals;
	}
	if (!numaltroutegoals)
		return qfalse;
	rnd = (float) random() * numaltroutegoals;
	if (rnd >= numaltroutegoals)
		rnd = numaltroutegoals - 1;
	goal = &bs->altroutegoal;
	goal->areanum = altroutegoals[rnd].areanum;
	VectorCopy(altroutegoals[rnd].origin, goal->origin);
	VectorSet(goal->mins, -8, -8, -8);
	VectorSet(goal->maxs, 8, 8, 8);
	goal->entitynum = 0;
	goal->iteminfo = 0;
	goal->number = 0;
	goal->flags = 0;
	//
	bs->reachedaltroutegoal_time = 0;
	return qtrue;
}

/*
==================
BotSetupAlternateRouteGoals
==================
*/
void BotSetupAlternativeRouteGoals(void)
{

	if (altroutegoals_setup)
		return;
	altroutegoals_setup = qtrue;
}

/*
==================
BotDeathmatchAI
==================
*/
void BotDeathmatchAI(bot_state_t * bs, float thinktime)
{
	char gender[144], name[144];
	char userinfo[MAX_INFO_STRING];
	int i;

	//if the bot has just been setup
	if (bs->setupcount > 0) {
		bs->setupcount--;
		if (bs->setupcount > 0)
			return;
		//get the gender characteristic
		trap_Characteristic_String(bs->character, CHARACTERISTIC_GENDER, gender, sizeof(gender));
		//set the bot gender
		trap_GetUserinfo(bs->client, userinfo, sizeof(userinfo));
		Info_SetValueForKey(userinfo, "sex", gender);
		trap_SetUserinfo(bs->client, userinfo);
		//set the chat gender
		if (gender[0] == 'm')
			trap_BotSetChatGender(bs->cs, CHAT_GENDERMALE);
		else if (gender[0] == 'f')
			trap_BotSetChatGender(bs->cs, CHAT_GENDERFEMALE);
		else
			trap_BotSetChatGender(bs->cs, CHAT_GENDERLESS);
		//set the chat name
		ClientName(bs->client, name, sizeof(name));
		trap_BotSetChatName(bs->cs, name, bs->client);
		//
		bs->lastframe_health = bs->inventory[INVENTORY_HEALTH];
		bs->lasthitcount = bs->cur_ps.persistant[PERS_HITS];
		//
		bs->setupcount = 0;
		//
		BotSetupAlternativeRouteGoals();
	}
	//no ideal view set
	bs->flags &= ~BFL_IDEALVIEWSET;
	//
	if (!BotIntermission(bs)) {
		//set the teleport time
		BotSetTeleportTime(bs);
		//update some inventory values
		BotUpdateInventory(bs);
		//check out the snapshot
		BotCheckSnapshot(bs);
		//check for air
		BotCheckAir(bs);
	}
	//check the console messages
	BotCheckConsoleMessages(bs);
	//if not in the intermission and not in observer mode
	if (!BotIntermission(bs) && !BotIsObserver(bs)) {
		//do team AI
		BotTeamAI(bs);
	}
	//if the bot has no ai node
	if (!bs->ainode) {
		AIEnter_Seek_LTG(bs, "BotDeathmatchAI: no ai node");
	}
	//if the bot entered the game less than 8 seconds ago
	if (!bs->entergamechat && bs->entergame_time > FloatTime() - 8) {
		if (BotChat_EnterGame(bs)) {
			bs->stand_time = FloatTime() + BotChatTime(bs);
			AIEnter_Stand(bs, "BotDeathmatchAI: chat enter game");
		}
		bs->entergamechat = qtrue;
	}
	//reset the node switches from the previous frame
	BotResetNodeSwitches();
	//execute AI nodes
	for (i = 0; i < MAX_NODESWITCHES; i++) {
		if (bs->ainode(bs))
			break;
	}
	//if the bot removed itself :)
	if (!bs->inuse)
		return;
	//if the bot executed too many AI nodes
	if (i >= MAX_NODESWITCHES) {
		trap_BotDumpGoalStack(bs->gs);
		trap_BotDumpAvoidGoals(bs->gs);
		BotDumpNodeSwitches(bs);
		ClientName(bs->client, name, sizeof(name));
		BotAI_Print(PRT_ERROR, "%s at %1.1f switched more than %d AI nodes\n", name, FloatTime(),
			    MAX_NODESWITCHES);
	}
	//
	bs->lastframe_health = bs->inventory[INVENTORY_HEALTH];
	bs->lasthitcount = bs->cur_ps.persistant[PERS_HITS];
}

/*
==================
BotSetEntityNumForGoalWithModel
==================
*/
void BotSetEntityNumForGoalWithModel(bot_goal_t * goal, int eType, char *modelname)
{
	gentity_t *ent;
	int i, modelindex;
	vec3_t dir;

	modelindex = G_ModelIndex(modelname);
	ent = &g_entities[0];
	for (i = 0; i < level.num_entities; i++, ent++) {
		if (!ent->inuse) {
			continue;
		}
		if (eType && ent->s.eType != eType) {
			continue;
		}
		if (ent->s.modelindex != modelindex) {
			continue;
		}
		VectorSubtract(goal->origin, ent->s.origin, dir);
		if (VectorLengthSquared(dir) < Square(10)) {
			goal->entitynum = i;
			return;
		}
	}
}

/*
==================
BotSetEntityNumForGoal
==================
*/
void BotSetEntityNumForGoal(bot_goal_t * goal, char *classname)
{
	gentity_t *ent;
	int i;
	vec3_t dir;

	ent = &g_entities[0];
	for (i = 0; i < level.num_entities; i++, ent++) {
		if (!ent->inuse) {
			continue;
		}
		if (Q_stricmp(ent->classname, classname) != 0) {
			continue;
		}
		VectorSubtract(goal->origin, ent->s.origin, dir);
		if (VectorLengthSquared(dir) < Square(10)) {
			goal->entitynum = i;
			return;
		}
	}
}

/*
==================
BotSetEntityNumForGoalWithActivator
==================
*/
void BotSetEntityNumForGoalWithActivator(bot_goal_t *goal, char *classname) {
	gentity_t *ent;
	int i;
	vec3_t dir;

	ent = &g_entities[0];
	for (i = 0; i < level.num_entities; i++, ent++) {
		if (!ent->inuse || !ent->activator) {
			continue;
		}
		if (Q_stricmp(ent->activator->classname, classname) != 0) {
			continue;
		}
		VectorSubtract(goal->origin, ent->s.origin, dir);
		if (VectorLengthSquared(dir) < Square(10)) {
			goal->entitynum = i;
			return;
		}
	}
}

/*
==================
BotGoalForBSPEntity
==================
*/
int BotGoalForBSPEntity(char *classname, bot_goal_t * goal)
{
	char value[MAX_INFO_STRING];
	vec3_t origin, start, end;
	int ent, numareas, areas[10];

	memset(goal, 0, sizeof(bot_goal_t));
	for (ent = trap_AAS_NextBSPEntity(0); ent; ent = trap_AAS_NextBSPEntity(ent)) {
		if (!trap_AAS_ValueForBSPEpairKey(ent, "classname", value, sizeof(value)))
			continue;
		if (!strcmp(value, classname)) {
			if (!trap_AAS_VectorForBSPEpairKey(ent, "origin", origin))
				return qfalse;
			VectorCopy(origin, goal->origin);
			VectorCopy(origin, start);
			start[2] -= 32;
			VectorCopy(origin, end);
			end[2] += 32;
			numareas = trap_AAS_TraceAreas(start, end, areas, NULL, 10);
			if (!numareas)
				return qfalse;
			goal->areanum = areas[0];
			return qtrue;
		}
	}
	return qfalse;
}

/*
==================
BotSetupDeathmatchAI
==================
*/
void BotSetupDeathmatchAI(void)
{
	int ent, modelnum;
	char model[128];

	gametype = trap_Cvar_VariableIntegerValue("g_gametype");

	trap_Cvar_Register(&bot_rocketjump, "bot_rocketjump", "1", 0);
	trap_Cvar_Register(&bot_grapple, "bot_grapple", "0", 0);
	trap_Cvar_Register(&bot_fastchat, "bot_fastchat", "0", 0);
	trap_Cvar_Register(&bot_nochat, "bot_nochat", "0", 0);
	trap_Cvar_Register(&bot_testrchat, "bot_testrchat", "0", 0);
	trap_Cvar_Register(&bot_challenge, "bot_challenge", "0", 0);
	trap_Cvar_Register(&bot_predictobstacles, "bot_predictobstacles", "1", 0);
	trap_Cvar_Register(&g_spSkill, "g_spSkill", "2", 0);
	//
	if (gametype == GT_CTF) {
		if (trap_BotGetLevelItemGoal(-1, "Silver Case", &ctf_redflag) < 0)
			BotAI_Print(PRT_WARNING, "CTB without Silver Case\n");
		if (trap_BotGetLevelItemGoal(-1, "Black Case", &ctf_blueflag) < 0)
			BotAI_Print(PRT_WARNING, "CTB without Black Case\n");
	}
	max_bspmodelindex = 0;
	for (ent = trap_AAS_NextBSPEntity(0); ent; ent = trap_AAS_NextBSPEntity(ent)) {
		if (!trap_AAS_ValueForBSPEpairKey(ent, "model", model, sizeof(model)))
			continue;
		if (model[0] == '*') {
			modelnum = atoi(model + 1);
			if (modelnum > max_bspmodelindex)
				max_bspmodelindex = modelnum;
		}
	}
	//initialize the waypoint heap
	BotInitWaypoints();
}

/*
==================
BotShutdownDeathmatchAI
==================
*/
void BotShutdownDeathmatchAI(void)
{
	altroutegoals_setup = qfalse;
}
