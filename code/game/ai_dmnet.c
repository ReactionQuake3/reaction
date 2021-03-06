//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.31  2002/07/02 20:22:35  jbravo
// Changed the files to use the right ui.
//
// Revision 1.30  2002/06/16 20:06:13  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.29  2002/06/16 17:37:59  jbravo
// Removed the MISSIONPACK ifdefs and missionpack only code.
//
// Revision 1.28  2002/06/05 19:16:22  makro
// Made bots choose the ssg in teamplay
//
// Revision 1.27  2002/06/01 13:37:02  makro
// Tweaked bandaging code
//
// Revision 1.26  2002/05/30 21:18:28  makro
// Bots should reload/bandage when roaming around
// Added "pathtarget" key to all the entities
//
// Revision 1.25  2002/05/11 14:22:06  makro
// Func_statics now reset at the beginning of each round
//
// Revision 1.24  2002/05/10 13:21:53  makro
// Mainly bot stuff. Also fixed a couple of crash bugs
//
// Revision 1.23  2002/05/05 15:18:02  makro
// Fixed some crash bugs. Bot stuff. Triggerable func_statics.
// Made flags only spawn in CTF mode
//
// Revision 1.22  2002/05/04 16:13:04  makro
// Bots
//
// Revision 1.21  2002/05/03 18:09:19  makro
// Bot stuff. Jump kicks
//
// Revision 1.20  2002/05/02 23:05:25  makro
// Loading screen. Jump kicks. Bot stuff
//
// Revision 1.19  2002/05/02 12:44:58  makro
// Customizable color for the loading screen text. Bot stuff
//
// Revision 1.18  2002/05/02 00:12:22  makro
// Improved reloading and ammo handling for akimbo/hc
//
// Revision 1.17  2002/05/01 05:32:45  makro
// Bots reload akimbos/handcannons. Also, they can decide whether
// or not an item on the ground is better than theirs
//
// Revision 1.16  2002/04/30 11:54:37  makro
// Bots rule ! Also, added clips to give all. Maybe some other things
//
// Revision 1.15  2002/04/14 21:49:52  makro
// Stuff
//
// Revision 1.14  2002/04/06 21:42:19  makro
// Changes to bot code. New surfaceparm system.
//
// Revision 1.13  2002/04/05 18:52:26  makro
// Cleaned things up a bit
//
// Revision 1.12  2002/04/04 18:06:44  makro
// Improved door code. Bots reply to radio treport from teammates.
// Improved reloading code.
//
// Revision 1.11  2002/04/03 17:39:36  makro
// Made bots handle incoming radio spam better
//
// Revision 1.10  2002/04/03 16:33:20  makro
// Bots now respond to radio commands
//
// Revision 1.9  2002/04/01 12:45:54  makro
// Changed some weapon names
//
// Revision 1.7  2002/03/31 19:16:56  makro
// Bandaging, reloading, opening rotating doors (still needs a lot of work),
// shooting breakables
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
 * name:		ai_dmnet.c
 *
 * desc:		Quake3 bot AI
 *
 * $Archive: /MissionPack/code/game/ai_dmnet.c $
 * $Author$ 
 * $Revision$
 * $Modtime: 11/14/00 2:42p $
 * $Date$
 *
 *****************************************************************************/

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
//data file headers
#include "chars.h"		//characteristics
#include "inv.h"		//indexes into the inventory
#include "syn.h"		//synonyms
#include "match.h"		//string matching types and vars

// for the voice chats

//Blaze: was there a extra ../ here?
#include "../ui/menudef.h"

//Makro - to get rid of the warnings
void Cmd_Bandage(gentity_t * ent);
void Cmd_DropItem_f(gentity_t * ent);
void Cmd_DropWeapon_f(gentity_t * ent);

//goal flag, see ../botlib/be_ai_goal.h for the other GFL_*
#define GFL_AIR			128

int numnodeswitches;
char nodeswitch[MAX_NODESWITCHES + 1][144];

#define LOOKAHEAD_DISTANCE		300

/*
==================
BotResetNodeSwitches
==================
*/
void BotResetNodeSwitches(void)
{
	numnodeswitches = 0;
}

/*
==================
BotDumpNodeSwitches
==================
*/
void BotDumpNodeSwitches(bot_state_t * bs)
{
	int i;
	char netname[MAX_NETNAME];

	ClientName(bs->client, netname, sizeof(netname));
	BotAI_Print(PRT_MESSAGE, "%s at %1.1f switched more than %d AI nodes\n", netname, FloatTime(),
		    MAX_NODESWITCHES);
	for (i = 0; i < numnodeswitches; i++) {
		BotAI_Print(PRT_MESSAGE, "%s", nodeswitch[i]);
	}
	BotAI_Print(PRT_FATAL, "");
}

/*
==================
BotRecordNodeSwitch
==================
*/
void BotRecordNodeSwitch(bot_state_t * bs, char *node, char *str, char *s)
{
	char netname[MAX_NETNAME];

	ClientName(bs->client, netname, sizeof(netname));
	Com_sprintf(nodeswitch[numnodeswitches], 144, "%s at %2.1f entered %s: %s from %s\n", netname, FloatTime(),
		    node, str, s);
#ifdef DEBUG
	if (0) {
		BotAI_Print(PRT_MESSAGE, "%s", nodeswitch[numnodeswitches]);
	}
#endif				//DEBUG
	numnodeswitches++;
}

/*
==================
BotGetAirGoal
==================
*/
int BotGetAirGoal(bot_state_t * bs, bot_goal_t * goal)
{
	bsp_trace_t bsptrace;
	vec3_t end, mins = { -15, -15, -2 }, maxs = {
	15, 15, 2};
	int areanum;

	//trace up until we hit solid
	VectorCopy(bs->origin, end);
	end[2] += 1000;
	BotAI_Trace(&bsptrace, bs->origin, mins, maxs, end, bs->entitynum, CONTENTS_SOLID | CONTENTS_PLAYERCLIP);
	//trace down until we hit water
	VectorCopy(bsptrace.endpos, end);
	BotAI_Trace(&bsptrace, end, mins, maxs, bs->origin, bs->entitynum,
		    CONTENTS_WATER | CONTENTS_SLIME | CONTENTS_LAVA);
	//if we found the water surface
	if (bsptrace.fraction > 0) {
		areanum = BotPointAreaNum(bsptrace.endpos);
		if (areanum) {
			VectorCopy(bsptrace.endpos, goal->origin);
			goal->origin[2] -= 2;
			goal->areanum = areanum;
			goal->mins[0] = -15;
			goal->mins[1] = -15;
			goal->mins[2] = -1;
			goal->maxs[0] = 15;
			goal->maxs[1] = 15;
			goal->maxs[2] = 1;
			goal->flags = GFL_AIR;
			goal->number = 0;
			goal->iteminfo = 0;
			goal->entitynum = 0;
			return qtrue;
		}
	}
	return qfalse;
}

/*
==================
BotGoForAir
==================
*/
int BotGoForAir(bot_state_t * bs, int tfl, bot_goal_t * ltg, float range)
{
	bot_goal_t goal;

	//if the bot needs air
	if (bs->lastair_time < FloatTime() - 6) {
		//
#ifdef DEBUG
		//BotAI_Print(PRT_MESSAGE, "going for air\n");
#endif				//DEBUG
		//if we can find an air goal
		if (BotGetAirGoal(bs, &goal)) {
			trap_BotPushGoal(bs->gs, &goal);
			return qtrue;
		} else {
			//get a nearby goal outside the water
			while (trap_BotChooseNBGItem(bs->gs, bs->origin, bs->inventory, tfl, ltg, range)) {
				trap_BotGetTopGoal(bs->gs, &goal);
				//if the goal is not in water
				if (!
				    (trap_AAS_PointContents(goal.origin) &
				     (CONTENTS_WATER | CONTENTS_SLIME | CONTENTS_LAVA))) {
					return qtrue;
				}
				trap_BotPopGoal(bs->gs);
			}
			trap_BotResetAvoidGoals(bs->gs);
		}
	}
	return qfalse;
}

/*
==================
BotNearbyGoal
==================
*/
int BotNearbyGoal(bot_state_t * bs, int tfl, bot_goal_t * ltg, float range)
{
	int ret;

	//check if the bot should go for air
	if (BotGoForAir(bs, tfl, ltg, range))
		return qtrue;
	//if the bot is carrying the enemy flag
	if (BotCTFCarryingFlag(bs)) {
		//if the bot is just a few secs away from the base 
		if (trap_AAS_AreaTravelTimeToGoalArea(bs->areanum, bs->origin, bs->teamgoal.areanum, TFL_DEFAULT) < 300) {
			//make the range really small
			range = 50;
		}
	}
	//
	ret = trap_BotChooseNBGItem(bs->gs, bs->origin, bs->inventory, tfl, ltg, range);
	/*
	   if (ret)
	   {
	   char buf[128];
	   //get the goal at the top of the stack
	   trap_BotGetTopGoal(bs->gs, &goal);
	   trap_BotGoalName(goal.number, buf, sizeof(buf));
	   BotAI_Print(PRT_MESSAGE, "%1.1f: new nearby goal %s\n", FloatTime(), buf);
	   }
	 */
	return ret;
}

/*
==================
RQ3_Bot_WeaponToDrop

Added by Makro
==================
*/
int RQ3_Bot_WeaponToDrop(bot_state_t * bs)
{
	if (bs->cur_ps.weapon <= WP_NONE || bs->cur_ps.weapon >= WP_NUM_WEAPONS)
		return WP_NONE;
	if (bs->cur_ps.weapon == WP_PISTOL || bs->cur_ps.weapon == WP_KNIFE ||
	    bs->cur_ps.weapon == WP_AKIMBO || bs->cur_ps.weapon == WP_GRENADE) {
		//no special weapon selected
		if (bs->inventory[INVENTORY_M4])
			return WP_M4;
		else if (bs->inventory[INVENTORY_M3])
			return WP_M3;
		else if (bs->inventory[INVENTORY_MP5])
			return WP_MP5;
		else if (bs->inventory[INVENTORY_HANDCANNON])
			return WP_HANDCANNON;
		else if (bs->inventory[INVENTORY_SSG3000])
			return WP_SSG3000;
	} else {
		return bs->cur_ps.weapon;
	}
	return WP_NONE;
}

/*
====================================
RQ3_Bot_ComboScore

Added by Makro
Note - lots of factors should be
considered here; they aren't :/
====================================
*/
int RQ3_Bot_ComboScore(int weapon, holdable_t item)
{
	if (item != HI_KEVLAR || item != HI_LASER || item != HI_BANDOLIER || item != HI_SLIPPERS || item != HI_SILENCER)
		return 0;
	switch (weapon) {
		//Shotgun
	case WP_M3:
		switch (item) {
		case HI_KEVLAR:
			return 100;
		case HI_LASER:
			return 30;
		case HI_BANDOLIER:
			return 80;
		case HI_SILENCER:
			return 30;
		case HI_SLIPPERS:
			return 80;
		default:
			return 0;
		}
		break;
		//MP5
	case WP_MP5:
		switch (item) {
		case HI_KEVLAR:
			return 90;
		case HI_LASER:
			return 100;
		case HI_BANDOLIER:
			return 70;
		case HI_SILENCER:
			return 80;
		case HI_SLIPPERS:
			return 40;
		default:
			return 0;
		}
		break;
		//HANDCANNON
	case WP_HANDCANNON:
		switch (item) {
		case HI_KEVLAR:
			return 90;
		case HI_LASER:
			return 30;
		case HI_BANDOLIER:
			return 90;
		case HI_SILENCER:
			return 30;
		case HI_SLIPPERS:
			return 90;
		default:
			return 0;
		}
		break;
		//SSG3000
	case WP_SSG3000:
		switch (item) {
		case HI_KEVLAR:
			return 100;
		case HI_LASER:
			return 40;
		case HI_BANDOLIER:
			return 80;
		case HI_SILENCER:
			return 90;
		case HI_SLIPPERS:
			return 40;
		default:
			return 0;
		}
		break;
		//M4
	case WP_M4:
		switch (item) {
		case HI_KEVLAR:
			return 100;
		case HI_LASER:
			return 90;
		case HI_BANDOLIER:
			return 80;
		case HI_SILENCER:
			return 30;
		case HI_SLIPPERS:
			return 40;
		default:
			return 0;
		}
		break;
	}
	return 0;
}

/*
==================
RQ3_Bot_NeedToDropStuff

Added by Makro
==================
*/
qboolean RQ3_Bot_NeedToDropStuff(bot_state_t * bs, bot_goal_t * goal)
{
	float attack_skill = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_ATTACK_SKILL, 0, 1);
	int itemType = IT_BAD;

	//check the bot skill
	if (random() < (1 - attack_skill))
		return qfalse;

	//if the bot doesn't have an item
	if (!g_entities[goal->entitynum].item)
		//no need to worry about dropping it
		return qfalse;

	itemType = g_entities[goal->entitynum].item->giType;
	//if the bot can pick up an item
	if (itemType == IT_HOLDABLE) {
		if (bs->cur_ps.stats[STAT_HOLDABLE_ITEM] < 1 || bs->cur_ps.stats[STAT_HOLDABLE_ITEM] >= bg_numItems)
			return qfalse;
		else {
			holdable_t oldItem = bg_itemlist[bs->cur_ps.stats[STAT_HOLDABLE_ITEM]].giTag;
			holdable_t newItem = g_entities[goal->entitynum].item->giTag;
			int i, oldScore, newScore, dropWeapon = WP_NONE;

			//if the two items are identical
			if (oldItem == newItem)
				return qfalse;
			//if the bot drops the bandolier a weapon might be dropped, too
			if (oldItem == HI_BANDOLIER
			    && g_entities[bs->entitynum].client->uniqueWeapons > g_RQ3_maxWeapons.integer)
				dropWeapon = RQ3_Bot_WeaponToDrop(bs);
			if (dropWeapon != WP_NONE) {
				//if the bot doesn't have any ammo for the dropped weapon
				if (bs->cur_ps.ammo[dropWeapon] <= 0 && !RQ3_Bot_CanReload(bs, dropWeapon)) {
					//it shouldn't care whether or not it's dropped
					dropWeapon = WP_NONE;
				}
			}

			newScore = oldScore = 0;
			//check all the weapons
			for (i = 0; i < MAX_WEAPONS; i++) {
				//if the bot has the weapon
				if (bs->cur_ps.stats[STAT_WEAPONS] & (1 << i)) {
					//get the score for it
					oldScore += RQ3_Bot_ComboScore(i, oldItem);
					//don't add the score for a weapon if it's going to be dropped
					if (i != dropWeapon)
						newScore += RQ3_Bot_ComboScore(i, newItem);
				}
			}

			//if the new item is better
			if (newScore > oldScore) {
				Cmd_DropItem_f(&g_entities[bs->entitynum]);
				return qtrue;
			}
		}
		//if the bot can pick up a weapon
	} else if (itemType == IT_WEAPON) {
		int dropWeapon = RQ3_Bot_WeaponToDrop(bs);

		if (dropWeapon == WP_NONE)
			return qfalse;
		if (bs->cur_ps.ammo[dropWeapon])
			return qfalse;
		if (RQ3_Bot_CanReload(bs, dropWeapon))
			return qfalse;
		//Makro - the current weapon is empty, drop it
		Cmd_DropWeapon_f(&g_entities[bs->entitynum]);
#ifdef DEBUG
		BotAI_Print(PRT_MESSAGE, "droppping weapon %i\n", dropWeapon);
#endif				//DEBUG

		return qtrue;
	}

	return qfalse;
}

/*
==================
BotReachedGoal
==================
*/
int BotReachedGoal(bot_state_t * bs, bot_goal_t * goal)
{
	if (goal->flags & GFL_ITEM) {
		//if touching the goal
		if (trap_BotTouchingGoal(bs->origin, goal)) {
			if (!(goal->flags & GFL_DROPPED)) {
				//Makro - check if the bot picked up a better weapon or item
				RQ3_Bot_NeedToDropStuff(bs, goal);
				//also added a TP check
				if (gametype != GT_TEAMPLAY) {
					trap_BotSetAvoidGoalTime(bs->gs, goal->number, -1);
				} else {
					trap_BotSetAvoidGoalTime(bs->gs, goal->number,
								 FloatTime() + 20.0f + random() * 20.0f);
				}
			}
			/*
			   if (g_entities[goal->entitynum].classname) {
			   G_Printf(va("^5BOT CODE: ^7Reached item of type (%s)\n", g_entities[goal->entitynum].classname));
			   }
			 */
			return qtrue;
		}
		//if the goal isn't there
		if (trap_BotItemGoalInVisButNotVisible(bs->entitynum, bs->eye, bs->viewangles, goal)) {
			/*
			   float avoidtime;
			   int t;

			   avoidtime = trap_BotAvoidGoalTime(bs->gs, goal->number);
			   if (avoidtime > 0) {
			   t = trap_AAS_AreaTravelTimeToGoalArea(bs->areanum, bs->origin, goal->areanum, bs->tfl);
			   if ((float) t * 0.009 < avoidtime)
			   return qtrue;
			   }
			 */
			return qtrue;
		}
		//if in the goal area and below or above the goal and not swimming
		if (bs->areanum == goal->areanum) {
			if (bs->origin[0] > goal->origin[0] + goal->mins[0]
			    && bs->origin[0] < goal->origin[0] + goal->maxs[0]) {
				if (bs->origin[1] > goal->origin[1] + goal->mins[1]
				    && bs->origin[1] < goal->origin[1] + goal->maxs[1]) {
					if (!trap_AAS_Swimming(bs->origin)) {
						return qtrue;
					}
				}
			}
		}
	} else if (goal->flags & GFL_AIR) {
		//if touching the goal
		if (trap_BotTouchingGoal(bs->origin, goal))
			return qtrue;
		//if the bot got air
		if (bs->lastair_time > FloatTime() - 1)
			return qtrue;
	} else {
		//if touching the goal
		if (trap_BotTouchingGoal(bs->origin, goal))
			return qtrue;
	}
	return qfalse;
}

/*
==================
BotGetItemLongTermGoal
==================
*/
int BotGetItemLongTermGoal(bot_state_t * bs, int tfl, bot_goal_t * goal)
{
	//if the bot has no goal
	if (!trap_BotGetTopGoal(bs->gs, goal)) {
		//BotAI_Print(PRT_MESSAGE, "no ltg on stack\n");
		bs->ltg_time = 0;
	}
	//if the bot touches the current goal
	else if (BotReachedGoal(bs, goal)) {
		BotChooseWeapon(bs);
		bs->ltg_time = 0;
	}
	//if it is time to find a new long term goal
	if (bs->ltg_time < FloatTime()) {
		//pop the current goal from the stack
		trap_BotPopGoal(bs->gs);
		//BotAI_Print(PRT_MESSAGE, "%s: choosing new ltg\n", ClientName(bs->client, netname, sizeof(netname)));
		//choose a new goal
		//BotAI_Print(PRT_MESSAGE, "%6.1f client %d: BotChooseLTGItem\n", FloatTime(), bs->client);
		if (trap_BotChooseLTGItem(bs->gs, bs->origin, bs->inventory, tfl)) {
			/*
			   char buf[128];
			   //get the goal at the top of the stack
			   trap_BotGetTopGoal(bs->gs, goal);
			   trap_BotGoalName(goal->number, buf, sizeof(buf));
			   BotAI_Print(PRT_MESSAGE, "%1.1f: new long term goal %s\n", FloatTime(), buf);
			 */
			bs->ltg_time = FloatTime() + 20;
		} else {	//the bot gets sorta stuck with all the avoid timings, shouldn't happen though
			//
#ifdef DEBUG
			char netname[128];

			BotAI_Print(PRT_MESSAGE, "%s: no valid ltg (probably stuck)\n",
				    ClientName(bs->client, netname, sizeof(netname)));
#endif
			//trap_BotDumpAvoidGoals(bs->gs);
			//reset the avoid goals and the avoid reach
			trap_BotResetAvoidGoals(bs->gs);
			trap_BotResetAvoidReach(bs->ms);
		}
		//get the goal at the top of the stack
		return trap_BotGetTopGoal(bs->gs, goal);
	}
	return qtrue;
}

/*
==================
BotGetLongTermGoal

we could also create a separate AI node for every long term goal type
however this saves us a lot of code
==================
*/
int BotGetLongTermGoal(bot_state_t * bs, int tfl, int retreat, bot_goal_t * goal)
{
	vec3_t target, dir, dir2;
	char netname[MAX_NETNAME];
	char buf[MAX_MESSAGE_SIZE];
	int areanum;
	float croucher;
	aas_entityinfo_t entinfo, botinfo;
	bot_waypoint_t *wp;

	if (bs->ltgtype == LTG_TEAMHELP && !retreat) {
		//check for bot typing status message
		if (bs->teammessage_time && bs->teammessage_time < FloatTime()) {
			BotAI_BotInitialChat(bs, "help_start", EasyClientName(bs->teammate, netname, sizeof(netname)),
					     NULL);
			trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
			BotVoiceChatOnly(bs, bs->decisionmaker, VOICECHAT_YES);
			//Makro - ACTION_AFFIRMATIVE = reload in RQ3
			//trap_EA_Action(bs->client, ACTION_AFFIRMATIVE);
			bs->teammessage_time = 0;
		}
		//if trying to help the team mate for more than a minute
		if (bs->teamgoal_time < FloatTime())
			bs->ltgtype = 0;
		//if the team mate IS visible for quite some time
		if (bs->teammatevisible_time < FloatTime() - 10)
			bs->ltgtype = 0;
		//get entity information of the companion
		BotEntityInfo(bs->teammate, &entinfo);
		//if the team mate is visible
		if (BotEntityVisible(bs->entitynum, bs->eye, bs->viewangles, 360, bs->teammate)) {
			//if close just stand still there
			VectorSubtract(entinfo.origin, bs->origin, dir);
			if (VectorLengthSquared(dir) < Square(100)) {
				trap_BotResetAvoidReach(bs->ms);
				return qfalse;
			}
		} else {
			//last time the bot was NOT visible
			bs->teammatevisible_time = FloatTime();
		}
		//if the entity information is valid (entity in PVS)
		if (entinfo.valid) {
			areanum = BotPointAreaNum(entinfo.origin);
			if (areanum && trap_AAS_AreaReachability(areanum)) {
				//update team goal
				bs->teamgoal.entitynum = bs->teammate;
				bs->teamgoal.areanum = areanum;
				VectorCopy(entinfo.origin, bs->teamgoal.origin);
				VectorSet(bs->teamgoal.mins, -8, -8, -8);
				VectorSet(bs->teamgoal.maxs, 8, 8, 8);
			}
		}
		memcpy(goal, &bs->teamgoal, sizeof(bot_goal_t));
		return qtrue;
	}
	//if the bot accompanies someone
	if (bs->ltgtype == LTG_TEAMACCOMPANY && !retreat) {
		//check for bot typing status message
		if (bs->teammessage_time && bs->teammessage_time < FloatTime()) {
			BotAI_BotInitialChat(bs, "accompany_start",
					     EasyClientName(bs->teammate, netname, sizeof(netname)), NULL);
			trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
			BotVoiceChatOnly(bs, bs->decisionmaker, VOICECHAT_YES);
			//Makro - ACTION_AFFIRMATIVE = reload in RQ3
			//trap_EA_Action(bs->client, ACTION_AFFIRMATIVE);
			bs->teammessage_time = 0;
		}
		//if accompanying the companion for 3 minutes
		if (bs->teamgoal_time < FloatTime()) {
			BotAI_BotInitialChat(bs, "accompany_stop",
					     EasyClientName(bs->teammate, netname, sizeof(netname)), NULL);
			trap_BotEnterChat(bs->cs, bs->teammate, CHAT_TELL);
			bs->ltgtype = 0;
		}
		//get entity information of the companion
		BotEntityInfo(bs->teammate, &entinfo);
		//if the companion is visible
		if (BotEntityVisible(bs->entitynum, bs->eye, bs->viewangles, 360, bs->teammate)) {
			//update visible time
			bs->teammatevisible_time = FloatTime();
			VectorSubtract(entinfo.origin, bs->origin, dir);
			if (VectorLengthSquared(dir) < Square(bs->formation_dist)) {
				//
				// if the client being followed bumps into this bot then
				// the bot should back up
				BotEntityInfo(bs->entitynum, &botinfo);
				// if the followed client is not standing ontop of the bot
				if (botinfo.origin[2] + botinfo.maxs[2] > entinfo.origin[2] + entinfo.mins[2]) {
					// if the bounding boxes touch each other
					if (botinfo.origin[0] + botinfo.maxs[0] >
					    entinfo.origin[0] + entinfo.mins[0] - 4
					    && botinfo.origin[0] + botinfo.mins[0] <
					    entinfo.origin[0] + entinfo.maxs[0] + 4) {
						if (botinfo.origin[1] + botinfo.maxs[1] >
						    entinfo.origin[1] + entinfo.mins[1] - 4
						    && botinfo.origin[1] + botinfo.mins[1] <
						    entinfo.origin[1] + entinfo.maxs[1] + 4) {
							if (botinfo.origin[2] + botinfo.maxs[2] >
							    entinfo.origin[2] + entinfo.mins[2] - 4
							    && botinfo.origin[2] + botinfo.mins[2] <
							    entinfo.origin[2] + entinfo.maxs[2] + 4) {
								// if the followed client looks in the direction of this bot
								AngleVectors(entinfo.angles, dir, NULL, NULL);
								dir[2] = 0;
								VectorNormalize(dir);
								//VectorSubtract(entinfo.origin, entinfo.lastvisorigin, dir);
								VectorSubtract(bs->origin, entinfo.origin, dir2);
								VectorNormalize(dir2);
								if (DotProduct(dir, dir2) > 0.7) {
									// back up
									BotSetupForMovement(bs);
									trap_BotMoveInDirection(bs->ms, dir2, 400,
												MOVE_WALK);
								}
							}
						}
					}
				}
				//check if the bot wants to crouch
				//don't crouch if crouched less than 5 seconds ago
				if (bs->attackcrouch_time < FloatTime() - 5) {
					croucher =
					    trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_CROUCHER, 0, 1);
					if (random() < bs->thinktime * croucher) {
						bs->attackcrouch_time = FloatTime() + 5 + croucher * 15;
					}
				}
				//don't crouch when swimming
				if (trap_AAS_Swimming(bs->origin))
					bs->attackcrouch_time = FloatTime() - 1;
				//if not arrived yet or arived some time ago
				if (bs->arrive_time < FloatTime() - 2) {
					//if not arrived yet
					if (!bs->arrive_time) {
						trap_EA_Gesture(bs->client);
						BotAI_BotInitialChat(bs, "accompany_arrive",
								     EasyClientName(bs->teammate, netname,
										    sizeof(netname)), NULL);
						trap_BotEnterChat(bs->cs, bs->teammate, CHAT_TELL);
						bs->arrive_time = FloatTime();
					}
					//if the bot wants to crouch
					else if (bs->attackcrouch_time > FloatTime()) {
						trap_EA_Crouch(bs->client);
					}
					//else do some model taunts
					else if (random() < bs->thinktime * 0.05) {
						//do a gesture :)
						trap_EA_Gesture(bs->client);
					}
				}
				//if just arrived look at the companion
				if (bs->arrive_time > FloatTime() - 2) {
					VectorSubtract(entinfo.origin, bs->origin, dir);
					vectoangles(dir, bs->ideal_viewangles);
					bs->ideal_viewangles[2] *= 0.5;
				}
				//else look strategically around for enemies
				else if (random() < bs->thinktime * 0.8) {
					BotRoamGoal(bs, target);
					VectorSubtract(target, bs->origin, dir);
					vectoangles(dir, bs->ideal_viewangles);
					bs->ideal_viewangles[2] *= 0.5;
				}
				//check if the bot wants to go for air
				if (BotGoForAir(bs, bs->tfl, &bs->teamgoal, 400)) {
					trap_BotResetLastAvoidReach(bs->ms);
					//get the goal at the top of the stack
					//trap_BotGetTopGoal(bs->gs, &tmpgoal);
					//trap_BotGoalName(tmpgoal.number, buf, 144);
					//BotAI_Print(PRT_MESSAGE, "new nearby goal %s\n", buf);
					//time the bot gets to pick up the nearby goal item
					bs->nbg_time = FloatTime() + 8;
					AIEnter_Seek_NBG(bs, "BotLongTermGoal: go for air");
					return qfalse;
				}
				//
				trap_BotResetAvoidReach(bs->ms);
				return qfalse;
			}
		}
		//if the entity information is valid (entity in PVS)
		if (entinfo.valid) {
			areanum = BotPointAreaNum(entinfo.origin);
			if (areanum && trap_AAS_AreaReachability(areanum)) {
				//update team goal
				bs->teamgoal.entitynum = bs->teammate;
				bs->teamgoal.areanum = areanum;
				VectorCopy(entinfo.origin, bs->teamgoal.origin);
				VectorSet(bs->teamgoal.mins, -8, -8, -8);
				VectorSet(bs->teamgoal.maxs, 8, 8, 8);
			}
		}
		//the goal the bot should go for
		memcpy(goal, &bs->teamgoal, sizeof(bot_goal_t));
		//if the companion is NOT visible for too long
		if (bs->teammatevisible_time < FloatTime() - 60) {
			BotAI_BotInitialChat(bs, "accompany_cannotfind",
					     EasyClientName(bs->teammate, netname, sizeof(netname)), NULL);
			trap_BotEnterChat(bs->cs, bs->teammate, CHAT_TELL);
			bs->ltgtype = 0;
			// just to make sure the bot won't spam this message
			bs->teammatevisible_time = FloatTime();
		}
		return qtrue;
	}
	//
	if (bs->ltgtype == LTG_DEFENDKEYAREA) {
		if (trap_AAS_AreaTravelTimeToGoalArea(bs->areanum, bs->origin,
						      bs->teamgoal.areanum, TFL_DEFAULT) > bs->defendaway_range) {
			bs->defendaway_time = 0;
		}
	}
	//if defending a key area
	if (bs->ltgtype == LTG_DEFENDKEYAREA && !retreat && bs->defendaway_time < FloatTime()) {
		//check for bot typing status message
		if (bs->teammessage_time && bs->teammessage_time < FloatTime()) {
			trap_BotGoalName(bs->teamgoal.number, buf, sizeof(buf));
			BotAI_BotInitialChat(bs, "defend_start", buf, NULL);
			trap_BotEnterChat(bs->cs, 0, CHAT_TEAM);
			BotVoiceChatOnly(bs, -1, VOICECHAT_ONDEFENSE);
			bs->teammessage_time = 0;
		}
		//set the bot goal
		memcpy(goal, &bs->teamgoal, sizeof(bot_goal_t));
		//stop after 2 minutes
		if (bs->teamgoal_time < FloatTime()) {
			trap_BotGoalName(bs->teamgoal.number, buf, sizeof(buf));
			BotAI_BotInitialChat(bs, "defend_stop", buf, NULL);
			trap_BotEnterChat(bs->cs, 0, CHAT_TEAM);
			bs->ltgtype = 0;
		}
		//if very close... go away for some time
		VectorSubtract(goal->origin, bs->origin, dir);
		if (VectorLengthSquared(dir) < Square(70)) {
			trap_BotResetAvoidReach(bs->ms);
			bs->defendaway_time = FloatTime() + 3 + 3 * random();
			if (BotHasPersistantPowerupAndWeapon(bs)) {
				bs->defendaway_range = 100;
			} else {
				bs->defendaway_range = 350;
			}
		}
		return qtrue;
	}
	//going to kill someone
	if (bs->ltgtype == LTG_KILL && !retreat) {
		//check for bot typing status message
		if (bs->teammessage_time && bs->teammessage_time < FloatTime()) {
			EasyClientName(bs->teamgoal.entitynum, buf, sizeof(buf));
			BotAI_BotInitialChat(bs, "kill_start", buf, NULL);
			trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
			bs->teammessage_time = 0;
		}
		//
		if (bs->killedenemy_time > bs->teamgoal_time - TEAM_KILL_SOMEONE && bs->lastkilledplayer == bs->teamgoal.entitynum) {
			EasyClientName(bs->teamgoal.entitynum, buf, sizeof(buf));
			BotAI_BotInitialChat(bs, "kill_done", buf, NULL);
			trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
			bs->ltgtype = 0;
		}
		//
		if (bs->teamgoal_time < FloatTime()) {
			bs->ltgtype = 0;
		}
		//just roam around
		return BotGetItemLongTermGoal(bs, tfl, goal);
	}
	//get an item
	if (bs->ltgtype == LTG_GETITEM && !retreat) {
		//check for bot typing status message
		if (bs->teammessage_time && bs->teammessage_time < FloatTime()) {
			trap_BotGoalName(bs->teamgoal.number, buf, sizeof(buf));
			BotAI_BotInitialChat(bs, "getitem_start", buf, NULL);
			trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
			BotVoiceChatOnly(bs, bs->decisionmaker, VOICECHAT_YES);
			//Makro - ACTION_AFFIRMATIVE = reload in RQ3
			//trap_EA_Action(bs->client, ACTION_AFFIRMATIVE);
			bs->teammessage_time = 0;
		}
		//set the bot goal
		memcpy(goal, &bs->teamgoal, sizeof(bot_goal_t));
		//stop after some time
		if (bs->teamgoal_time < FloatTime()) {
			bs->ltgtype = 0;
		}
		//
		if (trap_BotItemGoalInVisButNotVisible(bs->entitynum, bs->eye, bs->viewangles, goal)) {
			trap_BotGoalName(bs->teamgoal.number, buf, sizeof(buf));
			BotAI_BotInitialChat(bs, "getitem_notthere", buf, NULL);
			trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
			bs->ltgtype = 0;
		} else if (BotReachedGoal(bs, goal)) {
			trap_BotGoalName(bs->teamgoal.number, buf, sizeof(buf));
			BotAI_BotInitialChat(bs, "getitem_gotit", buf, NULL);
			trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
			bs->ltgtype = 0;
		}
		return qtrue;
	}
	//if camping somewhere
	if ((bs->ltgtype == LTG_CAMP || bs->ltgtype == LTG_CAMPORDER) && !retreat) {
		//check for bot typing status message
		if (bs->teammessage_time && bs->teammessage_time < FloatTime()) {
			if (bs->ltgtype == LTG_CAMPORDER) {
				BotAI_BotInitialChat(bs, "camp_start",
						     EasyClientName(bs->teammate, netname, sizeof(netname)), NULL);
				trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
				BotVoiceChatOnly(bs, bs->decisionmaker, VOICECHAT_YES);
				//Makro - ACTION_AFFIRMATIVE = reload in RQ3
				//trap_EA_Action(bs->client, ACTION_AFFIRMATIVE);
			}
			bs->teammessage_time = 0;
		}
		//set the bot goal
		memcpy(goal, &bs->teamgoal, sizeof(bot_goal_t));
		//
		if (bs->teamgoal_time < FloatTime()) {
			if (bs->ltgtype == LTG_CAMPORDER) {
				BotAI_BotInitialChat(bs, "camp_stop", NULL);
				trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
			}
			bs->ltgtype = 0;
		}
		//if really near the camp spot
		VectorSubtract(goal->origin, bs->origin, dir);
		if (VectorLengthSquared(dir) < Square(60)) {
			//if not arrived yet
			if (!bs->arrive_time) {
				if (bs->ltgtype == LTG_CAMPORDER) {
					BotAI_BotInitialChat(bs, "camp_arrive",
							     EasyClientName(bs->teammate, netname, sizeof(netname)),
							     NULL);
					trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
					BotVoiceChatOnly(bs, bs->decisionmaker, VOICECHAT_INPOSITION);
				}
				bs->arrive_time = FloatTime();
			}
			//look strategically around for enemies
			if (random() < bs->thinktime * 0.8) {
				BotRoamGoal(bs, target);
				VectorSubtract(target, bs->origin, dir);
				vectoangles(dir, bs->ideal_viewangles);
				bs->ideal_viewangles[2] *= 0.5;
			}
			//check if the bot wants to crouch
			//don't crouch if crouched less than 5 seconds ago
			if (bs->attackcrouch_time < FloatTime() - 5) {
				croucher = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_CROUCHER, 0, 1);
				if (random() < bs->thinktime * croucher) {
					bs->attackcrouch_time = FloatTime() + 5 + croucher * 15;
				}
			}
			//if the bot wants to crouch
			if (bs->attackcrouch_time > FloatTime()) {
				trap_EA_Crouch(bs->client);
			}
			//don't crouch when swimming
			if (trap_AAS_Swimming(bs->origin))
				bs->attackcrouch_time = FloatTime() - 1;
			//make sure the bot is not gonna drown
			if (trap_PointContents(bs->eye, bs->entitynum) &
			    (CONTENTS_WATER | CONTENTS_SLIME | CONTENTS_LAVA)) {
				if (bs->ltgtype == LTG_CAMPORDER) {
					BotAI_BotInitialChat(bs, "camp_stop", NULL);
					trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
					//
					if (bs->lastgoal_ltgtype == LTG_CAMPORDER) {
						bs->lastgoal_ltgtype = 0;
					}
				}
				bs->ltgtype = 0;
			}
			//
			//if (bs->camp_range > 0) {
				//FIXME: move around a bit
			//}
			//
			trap_BotResetAvoidReach(bs->ms);
			return qfalse;
		}
		return qtrue;
	}
	//patrolling along several waypoints
	if (bs->ltgtype == LTG_PATROL && !retreat) {
		//check for bot typing status message
		if (bs->teammessage_time && bs->teammessage_time < FloatTime()) {
			strcpy(buf, "");
			for (wp = bs->patrolpoints; wp; wp = wp->next) {
				strcat(buf, wp->name);
				if (wp->next)
					strcat(buf, " to ");
			}
			BotAI_BotInitialChat(bs, "patrol_start", buf, NULL);
			trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
			BotVoiceChatOnly(bs, bs->decisionmaker, VOICECHAT_YES);
			//Makro - ACTION_AFFIRMATIVE = reload in RQ3
			//trap_EA_Action(bs->client, ACTION_AFFIRMATIVE);
			bs->teammessage_time = 0;
		}
		//
		if (!bs->curpatrolpoint) {
			bs->ltgtype = 0;
			return qfalse;
		}
		//if the bot touches the current goal
		if (trap_BotTouchingGoal(bs->origin, &bs->curpatrolpoint->goal)) {
			if (bs->patrolflags & PATROL_BACK) {
				if (bs->curpatrolpoint->prev) {
					bs->curpatrolpoint = bs->curpatrolpoint->prev;
				} else {
					bs->curpatrolpoint = bs->curpatrolpoint->next;
					bs->patrolflags &= ~PATROL_BACK;
				}
			} else {
				if (bs->curpatrolpoint->next) {
					bs->curpatrolpoint = bs->curpatrolpoint->next;
				} else {
					bs->curpatrolpoint = bs->curpatrolpoint->prev;
					bs->patrolflags |= PATROL_BACK;
				}
			}
		}
		//stop after 5 minutes
		if (bs->teamgoal_time < FloatTime()) {
			BotAI_BotInitialChat(bs, "patrol_stop", NULL);
			trap_BotEnterChat(bs->cs, bs->decisionmaker, CHAT_TELL);
			bs->ltgtype = 0;
		}
		if (!bs->curpatrolpoint) {
			bs->ltgtype = 0;
			return qfalse;
		}
		memcpy(goal, &bs->curpatrolpoint->goal, sizeof(bot_goal_t));
		return qtrue;
	}
#ifdef CTF
	if (gametype == GT_CTF) {
		//if going for enemy flag
		if (bs->ltgtype == LTG_GETFLAG) {
			//check for bot typing status message
			if (bs->teammessage_time && bs->teammessage_time < FloatTime()) {
				BotAI_BotInitialChat(bs, "captureflag_start", NULL);
				trap_BotEnterChat(bs->cs, 0, CHAT_TEAM);
				BotVoiceChatOnly(bs, -1, VOICECHAT_ONGETFLAG);
				bs->teammessage_time = 0;
			}
			//
			switch (BotTeam(bs)) {
			case TEAM_RED:
				memcpy(goal, &ctf_blueflag, sizeof(bot_goal_t));
				break;
			case TEAM_BLUE:
				memcpy(goal, &ctf_redflag, sizeof(bot_goal_t));
				break;
			default:
				bs->ltgtype = 0;
				return qfalse;
			}
			//if touching the flag
			if (trap_BotTouchingGoal(bs->origin, goal)) {
				// make sure the bot knows the flag isn't there anymore
				switch (BotTeam(bs)) {
				case TEAM_RED:
					bs->blueflagstatus = 1;
					break;
				case TEAM_BLUE:
					bs->redflagstatus = 1;
					break;
				}
				bs->ltgtype = 0;
			}
			//stop after 3 minutes
			if (bs->teamgoal_time < FloatTime()) {
				bs->ltgtype = 0;
			}
			BotAlternateRoute(bs, goal);
			return qtrue;
		}
		//if rushing to the base
		if (bs->ltgtype == LTG_RUSHBASE && bs->rushbaseaway_time < FloatTime()) {
			switch (BotTeam(bs)) {
			case TEAM_RED:
				memcpy(goal, &ctf_redflag, sizeof(bot_goal_t));
				break;
			case TEAM_BLUE:
				memcpy(goal, &ctf_blueflag, sizeof(bot_goal_t));
				break;
			default:
				bs->ltgtype = 0;
				return qfalse;
			}
			//if not carrying the flag anymore
			if (!BotCTFCarryingFlag(bs))
				bs->ltgtype = 0;
			//quit rushing after 2 minutes
			if (bs->teamgoal_time < FloatTime())
				bs->ltgtype = 0;
			//if touching the base flag the bot should loose the enemy flag
			if (trap_BotTouchingGoal(bs->origin, goal)) {
				//if the bot is still carrying the enemy flag then the
				//base flag is gone, now just walk near the base a bit
				if (BotCTFCarryingFlag(bs)) {
					trap_BotResetAvoidReach(bs->ms);
					bs->rushbaseaway_time = FloatTime() + 5 + 10 * random();
					//FIXME: add chat to tell the others to get back the flag
				} else {
					bs->ltgtype = 0;
				}
			}
			BotAlternateRoute(bs, goal);
			return qtrue;
		}
		//returning flag
		if (bs->ltgtype == LTG_RETURNFLAG) {
			//check for bot typing status message
			if (bs->teammessage_time && bs->teammessage_time < FloatTime()) {
				BotAI_BotInitialChat(bs, "returnflag_start", NULL);
				trap_BotEnterChat(bs->cs, 0, CHAT_TEAM);
				BotVoiceChatOnly(bs, -1, VOICECHAT_ONRETURNFLAG);
				bs->teammessage_time = 0;
			}
			//
			switch (BotTeam(bs)) {
			case TEAM_RED:
				memcpy(goal, &ctf_blueflag, sizeof(bot_goal_t));
				break;
			case TEAM_BLUE:
				memcpy(goal, &ctf_redflag, sizeof(bot_goal_t));
				break;
			default:
				bs->ltgtype = 0;
				return qfalse;
			}
			//if touching the flag
			if (trap_BotTouchingGoal(bs->origin, goal))
				bs->ltgtype = 0;
			//stop after 3 minutes
			if (bs->teamgoal_time < FloatTime()) {
				bs->ltgtype = 0;
			}
			BotAlternateRoute(bs, goal);
			return qtrue;
		}
	}
#endif				//CTF
	//normal goal stuff
	return BotGetItemLongTermGoal(bs, tfl, goal);
}

/*
==================
BotLongTermGoal
==================
*/
int BotLongTermGoal(bot_state_t * bs, int tfl, int retreat, bot_goal_t * goal)
{
	aas_entityinfo_t entinfo;
	char teammate[MAX_MESSAGE_SIZE];
	float squaredist;
	int areanum;
	vec3_t dir;

	//FIXME: also have air long term goals?
	//
	//if the bot is leading someone and not retreating
	if (bs->lead_time > 0 && !retreat) {
		if (bs->lead_time < FloatTime()) {
			BotAI_BotInitialChat(bs, "lead_stop",
					     EasyClientName(bs->lead_teammate, teammate, sizeof(teammate)), NULL);
			trap_BotEnterChat(bs->cs, bs->teammate, CHAT_TELL);
			bs->lead_time = 0;
			return BotGetLongTermGoal(bs, tfl, retreat, goal);
		}
		//
		if (bs->leadmessage_time < 0 && -bs->leadmessage_time < FloatTime()) {
			BotAI_BotInitialChat(bs, "followme",
					     EasyClientName(bs->lead_teammate, teammate, sizeof(teammate)), NULL);
			trap_BotEnterChat(bs->cs, bs->teammate, CHAT_TELL);
			bs->leadmessage_time = FloatTime();
		}
		//get entity information of the companion
		BotEntityInfo(bs->lead_teammate, &entinfo);
		//
		if (entinfo.valid) {
			areanum = BotPointAreaNum(entinfo.origin);
			if (areanum && trap_AAS_AreaReachability(areanum)) {
				//update team goal
				bs->lead_teamgoal.entitynum = bs->lead_teammate;
				bs->lead_teamgoal.areanum = areanum;
				VectorCopy(entinfo.origin, bs->lead_teamgoal.origin);
				VectorSet(bs->lead_teamgoal.mins, -8, -8, -8);
				VectorSet(bs->lead_teamgoal.maxs, 8, 8, 8);
			}
		}
		//if the team mate is visible
		if (BotEntityVisible(bs->entitynum, bs->eye, bs->viewangles, 360, bs->lead_teammate)) {
			bs->leadvisible_time = FloatTime();
		}
		//if the team mate is not visible for 1 seconds
		if (bs->leadvisible_time < FloatTime() - 1) {
			bs->leadbackup_time = FloatTime() + 2;
		}
		//distance towards the team mate
		VectorSubtract(bs->origin, bs->lead_teamgoal.origin, dir);
		squaredist = VectorLengthSquared(dir);
		//if backing up towards the team mate
		if (bs->leadbackup_time > FloatTime()) {
			if (bs->leadmessage_time < FloatTime() - 20) {
				BotAI_BotInitialChat(bs, "followme",
						     EasyClientName(bs->lead_teammate, teammate, sizeof(teammate)),
						     NULL);
				trap_BotEnterChat(bs->cs, bs->teammate, CHAT_TELL);
				bs->leadmessage_time = FloatTime();
			}
			//if very close to the team mate
			if (squaredist < Square(100)) {
				bs->leadbackup_time = 0;
			}
			//the bot should go back to the team mate
			memcpy(goal, &bs->lead_teamgoal, sizeof(bot_goal_t));
			return qtrue;
		} else {
			//if quite distant from the team mate
			if (squaredist > Square(500)) {
				if (bs->leadmessage_time < FloatTime() - 20) {
					BotAI_BotInitialChat(bs, "followme",
							     EasyClientName(bs->lead_teammate, teammate,
									    sizeof(teammate)), NULL);
					trap_BotEnterChat(bs->cs, bs->teammate, CHAT_TELL);
					bs->leadmessage_time = FloatTime();
				}
				//look at the team mate
				VectorSubtract(entinfo.origin, bs->origin, dir);
				vectoangles(dir, bs->ideal_viewangles);
				bs->ideal_viewangles[2] *= 0.5;
				//just wait for the team mate
				return qfalse;
			}
		}
	}
	return BotGetLongTermGoal(bs, tfl, retreat, goal);
}

/*
==================
AIEnter_Intermission
==================
*/
void AIEnter_Intermission(bot_state_t * bs, char *s)
{
	BotRecordNodeSwitch(bs, "intermission", "", s);
	//reset the bot state
	BotResetState(bs);
	//check for end level chat
	if (BotChat_EndLevel(bs)) {
		trap_BotEnterChat(bs->cs, 0, bs->chatto);
	}
	bs->ainode = AINode_Intermission;
}

/*
==================
AINode_Intermission
==================
*/
int AINode_Intermission(bot_state_t * bs)
{
	//if the intermission ended
	if (!BotIntermission(bs)) {
		if (BotChat_StartLevel(bs)) {
			bs->stand_time = FloatTime() + BotChatTime(bs);
		} else {
			bs->stand_time = FloatTime() + 2;
		}
		AIEnter_Stand(bs, "intermission: chat");
	}
	return qtrue;
}

/*
==================
AIEnter_Observer
==================
*/
void AIEnter_Observer(bot_state_t * bs, char *s)
{
	BotRecordNodeSwitch(bs, "observer", "", s);
	//reset the bot state
	BotResetState(bs);
	bs->ainode = AINode_Observer;
}

/*
==================
AINode_Observer
==================
*/
int AINode_Observer(bot_state_t * bs)
{
	//if the bot left observer mode
	if (!BotIsObserver(bs)) {
		AIEnter_Stand(bs, "observer: left observer");
	}
	return qtrue;
}

/*
==================
AIEnter_Stand
==================
*/
void AIEnter_Stand(bot_state_t * bs, char *s)
{
	BotRecordNodeSwitch(bs, "stand", "", s);
	bs->standfindenemy_time = FloatTime() + 1;
	bs->ainode = AINode_Stand;
}

/*
==================
AINode_Stand
==================
*/
int AINode_Stand(bot_state_t * bs)
{

	//if the bot's health decreased
	if (bs->lastframe_health > bs->inventory[INVENTORY_HEALTH]) {
		if (BotChat_HitTalking(bs)) {
			bs->standfindenemy_time = FloatTime() + BotChatTime(bs) + 0.1;
			bs->stand_time = FloatTime() + BotChatTime(bs) + 0.1;
		}

		if (RQ3_Bot_CheckBandage(bs)) {
			//Makro - if not bandaging already
			if (bs->cur_ps.weaponstate != WEAPON_BANDAGING) {
				Cmd_Bandage(&g_entities[bs->entitynum]);
				//Not 100% sure this will work, but oh well...
				AIEnter_Battle_Retreat(bs, "stand: bandaging");
				return qfalse;
			}
		}
	}
	if (bs->standfindenemy_time < FloatTime()) {
		if (BotFindEnemy(bs, -1)) {
			AIEnter_Battle_Fight(bs, "stand: found enemy");
			return qfalse;
		}
		bs->standfindenemy_time = FloatTime() + 1;
	}
	// put up chat icon
	trap_EA_Talk(bs->client);
	// when done standing
	if (bs->stand_time < FloatTime()) {
		trap_BotEnterChat(bs->cs, 0, bs->chatto);
		AIEnter_Seek_LTG(bs, "stand: time out");
		return qfalse;
	}
	//
	return qtrue;
}

typedef struct {
	weapon_t weapon;
	holdable_t item;
} RQ3_TPCombo_t;

static RQ3_TPCombo_t RQ3_TPCombos[] = {
	{WP_M4, HI_LASER},
	{WP_M4, HI_KEVLAR},
	{WP_M4, HI_BANDOLIER},
	{WP_MP5, HI_LASER},
	{WP_MP5, HI_SILENCER},
	{WP_MP5, HI_KEVLAR},
	{WP_MP5, HI_BANDOLIER},
	{WP_M3, HI_KEVLAR},
	{WP_M3, HI_BANDOLIER},
	{WP_M3, HI_SLIPPERS},
	{WP_HANDCANNON, HI_KEVLAR},
	{WP_HANDCANNON, HI_BANDOLIER},
	{WP_HANDCANNON, HI_SLIPPERS},
	{WP_SSG3000, HI_SILENCER},
	{WP_SSG3000, HI_KEVLAR},
	{WP_SSG3000, HI_BANDOLIER},
	{WP_SSG3000, HI_SLIPPERS},
	{WP_AKIMBO, HI_KEVLAR},
	{WP_AKIMBO, HI_BANDOLIER}
};

static int num_RQ3_TPCombos = sizeof(RQ3_TPCombos) / sizeof(RQ3_TPCombo_t);

/*
==================
AIEnter_Respawn
==================
*/
void AIEnter_Respawn(bot_state_t * bs, char *s)
{
	BotRecordNodeSwitch(bs, "respawn", "", s);
	//reset some states
	trap_BotResetMoveState(bs->ms);
	trap_BotResetGoalState(bs->gs);
	trap_BotResetAvoidGoals(bs->gs);
	trap_BotResetAvoidReach(bs->ms);
	//if the bot wants to chat
	if (BotChat_Death(bs)) {
		bs->respawn_time = FloatTime() + BotChatTime(bs);
		bs->respawnchat_time = FloatTime();
	} else {
		bs->respawn_time = FloatTime() + 1 + random();
		bs->respawnchat_time = 0;
	}

	//Makro - the last time the bot responded to a radio message
	bs->radioresponse_time = 0;
	//Makro - how many times the bot responded to radio messages
	bs->radioresponse_count = 0;

	//set respawn state
	//Makro - special code for TP; played a little with those numbers
	if (gametype != GT_TEAMPLAY) {
		bs->standfindenemy_time = FloatTime() + 3;
		bs->stand_time = FloatTime() + 10;
		bs->check_time = FloatTime() + 4;
	} else {
		weapon_t tpW = WP_NONE + atoi(BotGetUserInfoKey(bs, "tpw"));
		holdable_t tpI = HI_NONE + atoi(BotGetUserInfoKey(bs, "tpi"));
		int index = 0;

		bs->standfindenemy_time = bs->check_time = FloatTime() + 1;
		bs->stand_time = 5;
		//don't use the same combo all the time
		if (random() > 0.2f) {
			//choose a random weapon/item
			index = (int) (random() * (num_RQ3_TPCombos - 0.1));
			tpW = RQ3_TPCombos[index].weapon;
			tpI = RQ3_TPCombos[index].item;
		}
		if (tpW <= WP_NONE || tpW >= WP_NUM_WEAPONS || tpI <= HI_NONE || tpI >= HI_NUM_HOLDABLE) {
#ifdef DEBUG
			BotAI_Print(PRT_WARNING, "Bad combo %i/%i, index is %i\n", tpW, tpI, index);
#endif
			tpW = WP_M4;
			tpI = HI_LASER;
		}
		g_entities[bs->entitynum].client->teamplayWeapon = tpW;
		g_entities[bs->entitynum].client->teamplayItem = tpI;
	}
	bs->respawn_wait = qfalse;
	bs->ainode = AINode_Respawn;
}

/*
==================
AINode_Respawn
==================
*/
int AINode_Respawn(bot_state_t * bs)
{
	// if waiting for the actual respawn
	if (bs->respawn_wait) {
		if (!BotIsDead(bs)) {
			AIEnter_Seek_LTG(bs, "respawn: respawned");
		} else {
			trap_EA_Respawn(bs->client);
		}
	} else if (bs->respawn_time < FloatTime()) {
		//wait until respawned
		bs->respawn_wait = qtrue;
		//elementary action respawn
		trap_EA_Respawn(bs->client);
		//
		if (bs->respawnchat_time) {
			trap_BotEnterChat(bs->cs, 0, bs->chatto);
			bs->enemy = -1;
		}
	}
	if (bs->respawnchat_time && bs->respawnchat_time < FloatTime() - 0.5) {
		trap_EA_Talk(bs->client);
	}
	//
	return qtrue;
}

/*
==================
BotSelectActivateWeapon
==================
*/
int BotSelectActivateWeapon(bot_state_t * bs)
{
	//
	//Makro - I'm pretty sure it should be WP_ and not WEAPONINDEX_
	if (bs->inventory[INVENTORY_PISTOL] > 0 && bs->inventory[INVENTORY_PISTOLAMMO] > 0)
//              return WEAPONINDEX_PISTOL;
		return WP_PISTOL;
	else if (bs->inventory[INVENTORY_M3] > 0 && bs->inventory[INVENTORY_M3AMMO] > 0)
//              return WEAPONINDEX_M3;
		return WP_M3;
	else if (bs->inventory[INVENTORY_M4] > 0 && bs->inventory[INVENTORY_M4AMMO] > 0)
//              return WEAPONINDEX_M4;
		return WP_M4;
	else if (bs->inventory[INVENTORY_MP5] > 0 && bs->inventory[INVENTORY_MP5AMMO] > 0)
//              return WEAPONINDEX_MP5;
		return WP_MP5;
	else if (bs->inventory[INVENTORY_SSG3000] > 0 && bs->inventory[INVENTORY_SSG3000AMMO] > 0)
//              return WEAPONINDEX_SSG3000;
		return WP_SSG3000;
	else if (bs->inventory[INVENTORY_HANDCANNON] > 0 && bs->inventory[INVENTORY_M3AMMO] > 0)
//              return WEAPONINDEX_HANDCANNON;
		return WP_HANDCANNON;
	else if (bs->inventory[INVENTORY_AKIMBO] > 0 && bs->inventory[INVENTORY_AKIMBOAMMO] > 0)
//              return WEAPONINDEX_AKIMBO;
		return WP_AKIMBO;
	else {
		return -1;
	}
}

/*
==================
BotClearPath

 try to deactivate obstacles like proximity mines on the bot's path
==================
*/
void BotClearPath(bot_state_t * bs, bot_moveresult_t * moveresult)
{
	int i, bestmine;
	float dist, bestdist;
	vec3_t target, dir;
	bsp_trace_t bsptrace;
	entityState_t state;

	// if there is a dead body wearing kamikze nearby
	if (bs->kamikazebody) {
		// if the bot's view angles and weapon are not used for movement
		if (!(moveresult->flags & (MOVERESULT_MOVEMENTVIEW | MOVERESULT_MOVEMENTWEAPON))) {
			//
			BotAI_GetEntityState(bs->kamikazebody, &state);
			VectorCopy(state.pos.trBase, target);
			target[2] += 8;
			VectorSubtract(target, bs->eye, dir);
			vectoangles(dir, moveresult->ideal_viewangles);
			//
			moveresult->weapon = BotSelectActivateWeapon(bs);
			if (moveresult->weapon == -1) {
				// FIXME: run away!
				moveresult->weapon = 0;
			}
			if (moveresult->weapon) {
				//
				moveresult->flags |= MOVERESULT_MOVEMENTWEAPON | MOVERESULT_MOVEMENTVIEW;
				// if holding the right weapon
				if (bs->cur_ps.weapon == moveresult->weapon) {
					// if the bot is pretty close with it's aim
					if (InFieldOfVision(bs->viewangles, 20, moveresult->ideal_viewangles)) {
						//
						BotAI_Trace(&bsptrace, bs->eye, NULL, NULL, target, bs->entitynum,
							    MASK_SHOT);
						// if the mine is visible from the current position
						if (bsptrace.fraction >= 1.0 || bsptrace.ent == state.number) {
							// shoot at the mine
							//Makro - using custom function to allow in-combat reloads
							//trap_EA_Attack(bs->client);
							BotAttack(bs);
						}
					}
				}
			}
		}
	}
	if (moveresult->flags & MOVERESULT_BLOCKEDBYAVOIDSPOT) {
		bs->blockedbyavoidspot_time = FloatTime() + 5;
	}
	// if blocked by an avoid spot and the view angles and weapon are used for movement
	if (bs->blockedbyavoidspot_time > FloatTime() &&
	    !(moveresult->flags & (MOVERESULT_MOVEMENTVIEW | MOVERESULT_MOVEMENTWEAPON))) {
		bestdist = 300;
		bestmine = -1;
		for (i = 0; i < bs->numproxmines; i++) {
			BotAI_GetEntityState(bs->proxmines[i], &state);
			VectorSubtract(state.pos.trBase, bs->origin, dir);
			dist = VectorLength(dir);
			if (dist < bestdist) {
				bestdist = dist;
				bestmine = i;
			}
		}
		if (bestmine != -1) {
			//
			// state->generic1 == TEAM_RED || state->generic1 == TEAM_BLUE
			//
			// deactivate prox mines in the bot's path by shooting
			// rockets or plasma cells etc. at them
			BotAI_GetEntityState(bs->proxmines[bestmine], &state);
			VectorCopy(state.pos.trBase, target);
			target[2] += 2;
			VectorSubtract(target, bs->eye, dir);
			vectoangles(dir, moveresult->ideal_viewangles);
			// if the bot has a weapon that does splash damage
			//Blaze: Just grenades
			if (bs->inventory[INVENTORY_GRENADE] > 0 && bs->inventory[INVENTORY_GRENADEAMMO] > 0)
				//Makro - changing to WP_ constants
				//moveresult->weapon = WEAPONINDEX_GRENADE;
				moveresult->weapon = WP_GRENADE;
			/*else if (bs->inventory[INVENTORY_ROCKETLAUNCHER] > 0 && bs->inventory[INVENTORY_ROCKETS] > 0)
			   moveresult->weapon = WEAPONINDEX_ROCKET_LAUNCHER;
			   else if (bs->inventory[INVENTORY_BFG10K] > 0 && bs->inventory[INVENTORY_BFGAMMO] > 0)
			   moveresult->weapon = WEAPONINDEX_BFG;
			 */
			else {
				moveresult->weapon = 0;
			}
			if (moveresult->weapon) {
				//
				moveresult->flags |= MOVERESULT_MOVEMENTWEAPON | MOVERESULT_MOVEMENTVIEW;
				// if holding the right weapon
				if (bs->cur_ps.weapon == moveresult->weapon) {
					// if the bot is pretty close with it's aim
					if (InFieldOfVision(bs->viewangles, 20, moveresult->ideal_viewangles)) {
						//
						BotAI_Trace(&bsptrace, bs->eye, NULL, NULL, target, bs->entitynum,
							    MASK_SHOT);
						// if the mine is visible from the current position
						if (bsptrace.fraction >= 1.0 || bsptrace.ent == state.number) {
							// shoot at the mine
							//Makro - using custom function to allow in-combat reloads
							//trap_EA_Attack(bs->client);
							BotAttack(bs);
						}
					}
				}
			}
		}
	}
}

/*
==================
AIEnter_Seek_ActivateEntity
==================
*/
void AIEnter_Seek_ActivateEntity(bot_state_t * bs, char *s)
{
	BotRecordNodeSwitch(bs, "activate entity", "", s);
	//Makro - check if the bot needs to reload/bandage
	RQ3_Bot_IdleActions(bs);
	bs->ainode = AINode_Seek_ActivateEntity;
}

/*
==================
AINode_Seek_Activate_Entity
==================
*/
int AINode_Seek_ActivateEntity(bot_state_t * bs)
{
	bot_goal_t *goal;
	vec3_t target, dir, ideal_viewangles;
	bot_moveresult_t moveresult;
	int targetvisible;
	bsp_trace_t bsptrace;
	aas_entityinfo_t entinfo;

	if (BotIsObserver(bs)) {
		BotClearActivateGoalStack(bs);
		AIEnter_Observer(bs, "active entity: observer");
		return qfalse;
	}
	//if in the intermission
	if (BotIntermission(bs)) {
		BotClearActivateGoalStack(bs);
		AIEnter_Intermission(bs, "activate entity: intermission");
		return qfalse;
	}
	//respawn if dead
	if (BotIsDead(bs)) {
		BotClearActivateGoalStack(bs);
		AIEnter_Respawn(bs, "activate entity: bot dead");
		return qfalse;
	}
	//
	bs->tfl = TFL_DEFAULT;
	if (bot_grapple.integer)
		bs->tfl |= TFL_GRAPPLEHOOK;
	//if in lava or slime the bot should be able to get out
	if (BotInLavaOrSlime(bs))
		bs->tfl |= TFL_LAVA | TFL_SLIME;
	//map specific code
	BotMapScripts(bs);
	//no enemy
	bs->enemy = -1;
	// if the bot has no activate goal
	if (!bs->activatestack) {
		BotClearActivateGoalStack(bs);
		AIEnter_Seek_NBG(bs, "activate entity: no goal");
		return qfalse;
	}
	//
	goal = &bs->activatestack->goal;
	// initialize target being visible to false
	targetvisible = qfalse;

	//Makro - if the bot has to open a door
	if (bs->activatestack->openDoor) {
		//int dist;
		BotEntityInfo(goal->entitynum, &entinfo);
		//dist = Distance(bs->origin, entinfo.origin);
		if (trap_BotTouchingGoal(bs->origin, goal)) {
			/*
			   if (bot_developer.integer == 2) {
			   G_Printf(va("^5BOT CODE: ^7Reached door at (%i %i %i) from (%i %i %i)\n",
			   (int) (bs->origin[0]), (int) (bs->origin[1]), (int) (bs->origin[2]),
			   (int) (entinfo.origin[0]), (int) (entinfo.origin[1]), (int) (entinfo.origin[2])));
			   }
			 */
			BotPopFromActivateGoalStack(bs);
			//bs->activatestack->time = 0;
			Cmd_OpenDoor(&g_entities[bs->entitynum]);
			BotMoveTowardsEnt(bs, entinfo.origin, -64);
			return qfalse;
		}

	}
	// if the bot has to shoot at a target to activate something
	if (bs->activatestack->shoot) {
		//
		BotAI_Trace(&bsptrace, bs->eye, NULL, NULL, bs->activatestack->target, bs->entitynum, MASK_SHOT);
		// if the shootable entity is visible from the current position
		if (bsptrace.fraction >= 1.0 || bsptrace.ent == goal->entitynum) {
			targetvisible = qtrue;
			// if holding the right weapon
			// Makro - or if no weapon is set for the goal
			if (bs->cur_ps.weapon == bs->activatestack->weapon || bs->activatestack->noWeapon) {
				VectorSubtract(bs->activatestack->target, bs->eye, dir);
				vectoangles(dir, ideal_viewangles);
				// if the bot is pretty close with it's aim
				if (InFieldOfVision(bs->viewangles, 20, ideal_viewangles)) {
					//Makro - using custom function to allow in-combat reloads
					//trap_EA_Attack(bs->client);
#ifdef DEBUG
					BotAI_Print(PRT_MESSAGE, "attacking an entity; weapon  = %i, required = %i\n",
						    bs->cur_ps.weapon, bs->activatestack->weapon);
#endif				//DEBUG
					BotAttack(bs);
				}
			}
		}
	}
	// if the shoot target is visible
	if (targetvisible) {
		// get the entity info of the entity the bot is shooting at
		BotEntityInfo(goal->entitynum, &entinfo);
		// if the entity the bot shoots at moved
		// Makro - or if the entity is no longer in use - for func_breakables
		if (!VectorCompare(bs->activatestack->origin, entinfo.origin) || !(g_entities[entinfo.number].r.linked)) {
#ifdef DEBUG
			BotAI_Print(PRT_MESSAGE, "hit shootable button or trigger\n");
#endif				//DEBUG
			bs->activatestack->time = 0;
		}
		// if the activate goal has been activated or the bot takes too long
		if (bs->activatestack->time < FloatTime()) {
			BotPopFromActivateGoalStack(bs);
			// if there are more activate goals on the stack
			if (bs->activatestack) {
				bs->activatestack->time = FloatTime() + 10;
				return qfalse;
			}
			AIEnter_Seek_NBG(bs, "activate entity: time out");
			return qfalse;
		}
		memset(&moveresult, 0, sizeof(bot_moveresult_t));
	} else {
		//if the bot has no goal
		if (!goal) {
			bs->activatestack->time = 0;
		}
		// if the bot does not have a shoot goal
		else if (!bs->activatestack->shoot) {
			//if the bot touches the current goal
			if (trap_BotTouchingGoal(bs->origin, goal)) {
#ifdef DEBUG
				BotAI_Print(PRT_MESSAGE, "touched button or trigger\n");
#endif				//DEBUG
				bs->activatestack->time = 0;
			}
		}
		// if the activate goal has been activated or the bot takes too long
		if (bs->activatestack->time < FloatTime()) {
			BotPopFromActivateGoalStack(bs);
			// if there are more activate goals on the stack
			if (bs->activatestack) {
				bs->activatestack->time = FloatTime() + 10;
				return qfalse;
			}
			AIEnter_Seek_NBG(bs, "activate entity: activated");
			return qfalse;
		}
		//predict obstacles
		if (BotAIPredictObstacles(bs, goal))
			return qfalse;
		//initialize the movement state
		BotSetupForMovement(bs);
		//move towards the goal
		trap_BotMoveToGoal(&moveresult, bs->ms, goal, bs->tfl);
		//if the movement failed
		if (moveresult.failure) {
			//reset the avoid reach, otherwise bot is stuck in current area
			trap_BotResetAvoidReach(bs->ms);
			//
			bs->activatestack->time = 0;
		}
		//check if the bot is blocked
		BotAIBlocked(bs, &moveresult, qtrue);
	}
	//
	BotClearPath(bs, &moveresult);
	// if the bot has to shoot to activate
	if (bs->activatestack->shoot) {
		// if the view angles aren't yet used for the movement
		if (!(moveresult.flags & MOVERESULT_MOVEMENTVIEW)) {
			VectorSubtract(bs->activatestack->target, bs->eye, dir);
			vectoangles(dir, moveresult.ideal_viewangles);
			moveresult.flags |= MOVERESULT_MOVEMENTVIEW;
		}
		// if there's no weapon yet used for the movement
		if (!(moveresult.flags & MOVERESULT_MOVEMENTWEAPON)) {
			moveresult.flags |= MOVERESULT_MOVEMENTWEAPON;
			//
			bs->activatestack->weapon = BotSelectActivateWeapon(bs);
			if (bs->activatestack->weapon == -1) {
				//FIXME: find a decent weapon first
				bs->activatestack->weapon = 0;
			}
			moveresult.weapon = bs->activatestack->weapon;
		}
	}
	// if the ideal view angles are set for movement
	if (moveresult.flags & (MOVERESULT_MOVEMENTVIEWSET | MOVERESULT_MOVEMENTVIEW | MOVERESULT_SWIMVIEW)) {
		VectorCopy(moveresult.ideal_viewangles, bs->ideal_viewangles);
	}
	//if waiting for something
	else if (moveresult.flags & MOVERESULT_WAITING) {
		if (random() < bs->thinktime * 0.8) {
			BotRoamGoal(bs, target);
			VectorSubtract(target, bs->origin, dir);
			vectoangles(dir, bs->ideal_viewangles);
			bs->ideal_viewangles[2] *= 0.5;
		}
	} else if (!(bs->flags & BFL_IDEALVIEWSET)) {
		if (trap_BotMovementViewTarget(bs->ms, goal, bs->tfl, 300, target)) {
			VectorSubtract(target, bs->origin, dir);
			vectoangles(dir, bs->ideal_viewangles);
		} else {
			vectoangles(moveresult.movedir, bs->ideal_viewangles);
		}
		bs->ideal_viewangles[2] *= 0.5;
	}
	//if the weapon is used for the bot movement
	if (moveresult.flags & MOVERESULT_MOVEMENTWEAPON)
		bs->weaponnum = moveresult.weapon;
	//if there is an enemy
	if (BotFindEnemy(bs, -1)) {
		if (BotWantsToRetreat(bs)) {
			//keep the current long term goal and retreat
			AIEnter_Battle_NBG(bs, "activate entity: found enemy");
		} else {
			trap_BotResetLastAvoidReach(bs->ms);
			//empty the goal stack
			trap_BotEmptyGoalStack(bs->gs);
			//go fight
			AIEnter_Battle_Fight(bs, "activate entity: found enemy");
		}
		BotClearActivateGoalStack(bs);
	}
	return qtrue;
}

/*
==================
AIEnter_Seek_NBG
==================
*/
void AIEnter_Seek_NBG(bot_state_t * bs, char *s)
{
	bot_goal_t goal;
	char buf[144];

	if (trap_BotGetTopGoal(bs->gs, &goal)) {
		trap_BotGoalName(goal.number, buf, 144);
		BotRecordNodeSwitch(bs, "seek NBG", buf, s);
	} else {
		BotRecordNodeSwitch(bs, "seek NBG", "no goal", s);
	}
	//Makro - check if the bot needs to reload/bandage
	RQ3_Bot_IdleActions(bs);
	bs->ainode = AINode_Seek_NBG;
}

/*
==================
AINode_Seek_NBG
==================
*/
int AINode_Seek_NBG(bot_state_t * bs)
{
	bot_goal_t goal;
	vec3_t target, dir;
	bot_moveresult_t moveresult;

	if (BotIsObserver(bs)) {
		AIEnter_Observer(bs, "seek nbg: observer");
		return qfalse;
	}
	//if in the intermission
	if (BotIntermission(bs)) {
		AIEnter_Intermission(bs, "seek nbg: intermision");
		return qfalse;
	}
	//respawn if dead
	if (BotIsDead(bs)) {
		AIEnter_Respawn(bs, "seek nbg: bot dead");
		return qfalse;
	}
	//
	bs->tfl = TFL_DEFAULT;
	if (bot_grapple.integer)
		bs->tfl |= TFL_GRAPPLEHOOK;
	//if in lava or slime the bot should be able to get out
	if (BotInLavaOrSlime(bs))
		bs->tfl |= TFL_LAVA | TFL_SLIME;
	//
	if (BotCanAndWantsToRocketJump(bs)) {
		bs->tfl |= TFL_ROCKETJUMP;
	}
	//map specific code
	BotMapScripts(bs);

	//Makro - check if the bot needs to reload/bandage
	RQ3_Bot_IdleActions(bs);

	//no enemy
	bs->enemy = -1;
	//if the bot has no goal
	if (!trap_BotGetTopGoal(bs->gs, &goal))
		bs->nbg_time = 0;
	//if the bot touches the current goal
	else if (BotReachedGoal(bs, &goal)) {
		BotChooseWeapon(bs);
		bs->nbg_time = 0;
	}
	//
	if (bs->nbg_time < FloatTime()) {
		//pop the current goal from the stack
		trap_BotPopGoal(bs->gs);
		//check for new nearby items right away
		//NOTE: we canNOT reset the check_time to zero because it would create an endless loop of node switches
		bs->check_time = FloatTime() + 0.05;
		//go back to seek ltg
		AIEnter_Seek_LTG(bs, "seek nbg: time out");
		return qfalse;
	}
	//predict obstacles
	if (BotAIPredictObstacles(bs, &goal))
		return qfalse;
	//initialize the movement state
	BotSetupForMovement(bs);
	//move towards the goal
	trap_BotMoveToGoal(&moveresult, bs->ms, &goal, bs->tfl);
	//if the movement failed
	if (moveresult.failure) {
		//reset the avoid reach, otherwise bot is stuck in current area
		trap_BotResetAvoidReach(bs->ms);
		bs->nbg_time = 0;
	}
	//check if the bot is blocked
	BotAIBlocked(bs, &moveresult, qtrue);
	//
	BotClearPath(bs, &moveresult);
	//if the viewangles are used for the movement
	if (moveresult.flags & (MOVERESULT_MOVEMENTVIEWSET | MOVERESULT_MOVEMENTVIEW | MOVERESULT_SWIMVIEW)) {
		VectorCopy(moveresult.ideal_viewangles, bs->ideal_viewangles);
	}
	//if waiting for something
	else if (moveresult.flags & MOVERESULT_WAITING) {
		if (random() < bs->thinktime * 0.8) {
			BotRoamGoal(bs, target);
			VectorSubtract(target, bs->origin, dir);
			vectoangles(dir, bs->ideal_viewangles);
			bs->ideal_viewangles[2] *= 0.5;
		}
	} else if (!(bs->flags & BFL_IDEALVIEWSET)) {
		if (!trap_BotGetSecondGoal(bs->gs, &goal))
			trap_BotGetTopGoal(bs->gs, &goal);
		if (trap_BotMovementViewTarget(bs->ms, &goal, bs->tfl, 300, target)) {
			VectorSubtract(target, bs->origin, dir);
			vectoangles(dir, bs->ideal_viewangles);
		}
		//FIXME: look at cluster portals?
		else
			vectoangles(moveresult.movedir, bs->ideal_viewangles);
		bs->ideal_viewangles[2] *= 0.5;
	}
	//if the weapon is used for the bot movement
	if (moveresult.flags & MOVERESULT_MOVEMENTWEAPON)
		bs->weaponnum = moveresult.weapon;
	//if there is an enemy
	if (BotFindEnemy(bs, -1)) {
		if (BotWantsToRetreat(bs)) {
			//keep the current long term goal and retreat
			AIEnter_Battle_NBG(bs, "seek nbg: found enemy");
		} else {
			trap_BotResetLastAvoidReach(bs->ms);
			//empty the goal stack
			trap_BotEmptyGoalStack(bs->gs);
			//go fight
			AIEnter_Battle_Fight(bs, "seek nbg: found enemy");
		}
	}
	return qtrue;
}

/*
==================
AIEnter_Seek_LTG
==================
*/
void AIEnter_Seek_LTG(bot_state_t * bs, char *s)
{
	bot_goal_t goal;
	char buf[144];

	if (trap_BotGetTopGoal(bs->gs, &goal)) {
		trap_BotGoalName(goal.number, buf, 144);
		BotRecordNodeSwitch(bs, "seek LTG", buf, s);
	} else {
		BotRecordNodeSwitch(bs, "seek LTG", "no goal", s);
	}
	//Makro - check if the bot needs to reload/bandage
	RQ3_Bot_IdleActions(bs);
	bs->ainode = AINode_Seek_LTG;
}

/*
==================
AINode_Seek_LTG
==================
*/
int AINode_Seek_LTG(bot_state_t * bs)
{
	bot_goal_t goal;
	vec3_t target, dir;
	bot_moveresult_t moveresult;
	int range;

	//char buf[128];
	//bot_goal_t tmpgoal;

	if (BotIsObserver(bs)) {
		AIEnter_Observer(bs, "seek ltg: observer");
		return qfalse;
	}
	//if in the intermission
	if (BotIntermission(bs)) {
		AIEnter_Intermission(bs, "seek ltg: intermission");
		return qfalse;
	}
	//respawn if dead
	if (BotIsDead(bs)) {
		AIEnter_Respawn(bs, "seek ltg: bot dead");
		return qfalse;
	}
	//
	if (BotChat_Random(bs)) {
		bs->stand_time = FloatTime() + BotChatTime(bs);
		AIEnter_Stand(bs, "seek ltg: random chat");
		return qfalse;
	}
	//
	bs->tfl = TFL_DEFAULT;
	if (bot_grapple.integer)
		bs->tfl |= TFL_GRAPPLEHOOK;
	//if in lava or slime the bot should be able to get out
	if (BotInLavaOrSlime(bs))
		bs->tfl |= TFL_LAVA | TFL_SLIME;
	//
	if (BotCanAndWantsToRocketJump(bs)) {
		bs->tfl |= TFL_ROCKETJUMP;
	}
	//map specific code
	BotMapScripts(bs);

	//Makro - check if the bot needs to reload/bandage
	RQ3_Bot_IdleActions(bs);

	//no enemy
	bs->enemy = -1;
	//
	if (bs->killedenemy_time > FloatTime() - 2) {
		if (random() < bs->thinktime * 1) {
			trap_EA_Gesture(bs->client);
		}
	}
	//if there is an enemy
	if (BotFindEnemy(bs, -1)) {
		if (BotWantsToRetreat(bs)) {
			//keep the current long term goal and retreat
			AIEnter_Battle_Retreat(bs, "seek ltg: found enemy");
			return qfalse;
		} else {
			trap_BotResetLastAvoidReach(bs->ms);
			//empty the goal stack
			trap_BotEmptyGoalStack(bs->gs);
			//go fight
			AIEnter_Battle_Fight(bs, "seek ltg: found enemy");
			return qfalse;
		}
	}
	//
	BotTeamGoals(bs, qfalse);
	//get the current long term goal
	if (!BotLongTermGoal(bs, bs->tfl, qfalse, &goal)) {
		return qtrue;
	}
	//check for nearby goals periodicly
	if (bs->check_time < FloatTime()) {
		bs->check_time = FloatTime() + 0.5;
		//check if the bot wants to camp
		BotWantsToCamp(bs);
		//
		if (bs->ltgtype == LTG_DEFENDKEYAREA)
			range = 400;
		else
			range = 150;
		//
#ifdef CTF
		if (gametype == GT_CTF) {
			//if carrying a flag the bot shouldn't be distracted too much
			if (BotCTFCarryingFlag(bs))
				range = 50;
		}
#endif				//CTF
		if (BotNearbyGoal(bs, bs->tfl, &goal, range)) {
			trap_BotResetLastAvoidReach(bs->ms);
			//get the goal at the top of the stack
			//trap_BotGetTopGoal(bs->gs, &tmpgoal);
			//trap_BotGoalName(tmpgoal.number, buf, 144);
			//BotAI_Print(PRT_MESSAGE, "new nearby goal %s\n", buf);
			//time the bot gets to pick up the nearby goal item
			bs->nbg_time = FloatTime() + 4 + range * 0.01;
			AIEnter_Seek_NBG(bs, "ltg seek: nbg");
			return qfalse;
		}
	}
	//predict obstacles
	if (BotAIPredictObstacles(bs, &goal))
		return qfalse;
	//initialize the movement state
	BotSetupForMovement(bs);
	//move towards the goal
	trap_BotMoveToGoal(&moveresult, bs->ms, &goal, bs->tfl);
	//if the movement failed
	if (moveresult.failure) {
		//reset the avoid reach, otherwise bot is stuck in current area
		trap_BotResetAvoidReach(bs->ms);
		//BotAI_Print(PRT_MESSAGE, "movement failure %d\n", moveresult.traveltype);
		bs->ltg_time = 0;
	}
	//
	BotAIBlocked(bs, &moveresult, qtrue);
	//
	BotClearPath(bs, &moveresult);
	//if the viewangles are used for the movement
	if (moveresult.flags & (MOVERESULT_MOVEMENTVIEWSET | MOVERESULT_MOVEMENTVIEW | MOVERESULT_SWIMVIEW)) {
		VectorCopy(moveresult.ideal_viewangles, bs->ideal_viewangles);
	}
	//if waiting for something
	else if (moveresult.flags & MOVERESULT_WAITING) {
		if (random() < bs->thinktime * 0.8) {
			BotRoamGoal(bs, target);
			VectorSubtract(target, bs->origin, dir);
			vectoangles(dir, bs->ideal_viewangles);
			bs->ideal_viewangles[2] *= 0.5;
		}
	} else if (!(bs->flags & BFL_IDEALVIEWSET)) {
		if (trap_BotMovementViewTarget(bs->ms, &goal, bs->tfl, 300, target)) {
			VectorSubtract(target, bs->origin, dir);
			vectoangles(dir, bs->ideal_viewangles);
		}
		//FIXME: look at cluster portals?
		else if (VectorLengthSquared(moveresult.movedir)) {
			vectoangles(moveresult.movedir, bs->ideal_viewangles);
		} else if (random() < bs->thinktime * 0.8) {
			BotRoamGoal(bs, target);
			VectorSubtract(target, bs->origin, dir);
			vectoangles(dir, bs->ideal_viewangles);
			bs->ideal_viewangles[2] *= 0.5;
		}
		bs->ideal_viewangles[2] *= 0.5;
	}
	//if the weapon is used for the bot movement
	if (moveresult.flags & MOVERESULT_MOVEMENTWEAPON)
		bs->weaponnum = moveresult.weapon;
	//
	return qtrue;
}

/*
==================
AIEnter_Battle_Fight
==================
*/
void AIEnter_Battle_Fight(bot_state_t * bs, char *s)
{
	float attack_skill = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_ATTACK_SKILL, 0, 1);

	BotRecordNodeSwitch(bs, "battle fight", "", s);
	trap_BotResetLastAvoidReach(bs->ms);
	//Makro - check if the bot has leg damage
	if (RQ3_Bot_NeedToBandage(bs) == 2) {
		if (random() > attack_skill) {
			if (bs->cur_ps.weaponstate != WEAPON_BANDAGING) {
				Cmd_Bandage(&g_entities[bs->entitynum]);
			}
		}
	}
	bs->ainode = AINode_Battle_Fight;
}

/*
==================
AIEnter_Battle_SuicidalFight
==================
*/
void AIEnter_Battle_SuicidalFight(bot_state_t * bs, char *s)
{
	BotRecordNodeSwitch(bs, "battle fight", "", s);
	trap_BotResetLastAvoidReach(bs->ms);
	bs->ainode = AINode_Battle_Fight;
	bs->flags |= BFL_FIGHTSUICIDAL;
}

/*
==================
AINode_Battle_Fight
==================
*/
int AINode_Battle_Fight(bot_state_t * bs)
{
	int areanum;
	vec3_t target;
	aas_entityinfo_t entinfo;
	bot_moveresult_t moveresult;

	if (BotIsObserver(bs)) {
		AIEnter_Observer(bs, "battle fight: observer");
		return qfalse;
	}
	//if in the intermission
	if (BotIntermission(bs)) {
		AIEnter_Intermission(bs, "battle fight: intermission");
		return qfalse;
	}
	//respawn if dead
	if (BotIsDead(bs)) {
		AIEnter_Respawn(bs, "battle fight: bot dead");
		return qfalse;
	}
	//if there is another better enemy
	if (BotFindEnemy(bs, bs->enemy)) {
#ifdef DEBUG
		BotAI_Print(PRT_MESSAGE, "found new better enemy\n");
#endif
	}
	//if no enemy
	if (bs->enemy < 0) {
		AIEnter_Seek_LTG(bs, "battle fight: no enemy");
		return qfalse;
	}
	//
	BotEntityInfo(bs->enemy, &entinfo);
	//if the enemy is dead
	if (bs->enemydeath_time) {
		if (bs->enemydeath_time < FloatTime() - 1.0) {
			bs->enemydeath_time = 0;
			if (random() > 0.3f) {
				//Makro - check if the bot needs to bandage
				if (RQ3_Bot_NeedToBandage(bs) != 0) {
					if (RQ3_Bot_CheckBandage(bs)) {
						if (bs->cur_ps.weaponstate != WEAPON_BANDAGING) {
							Cmd_Bandage(&g_entities[bs->entitynum]);
						}
					}
				}
			}	//
			if (bs->enemysuicide) {
				BotChat_EnemySuicide(bs);
			}
			if (bs->lastkilledplayer == bs->enemy && BotChat_Kill(bs)) {
				bs->stand_time = FloatTime() + BotChatTime(bs);
				AIEnter_Stand(bs, "battle fight: enemy dead");
			} else {
				bs->ltg_time = 0;
				AIEnter_Seek_LTG(bs, "battle fight: enemy dead");
			}
			return qfalse;
		}
	} else {
		if (EntityIsDead(&entinfo)) {
			bs->enemydeath_time = FloatTime();
		}
	}
	//if the enemy is invisible and not shooting the bot looses track easily
	if (EntityIsInvisible(&entinfo) && !EntityIsShooting(&entinfo)) {
		if (random() < 0.2) {
			AIEnter_Seek_LTG(bs, "battle fight: invisible");
			return qfalse;
		}
	}
	//
	VectorCopy(entinfo.origin, target);
	// if not a player enemy
	if (bs->enemy >= MAX_CLIENTS) {
	}
	//update the reachability area and origin if possible
	areanum = BotPointAreaNum(target);
	if (areanum && trap_AAS_AreaReachability(areanum)) {
		VectorCopy(target, bs->lastenemyorigin);
		bs->lastenemyareanum = areanum;
	}
	//update the attack inventory values
	BotUpdateBattleInventory(bs, bs->enemy);
	//if the bot's health decreased
	if (bs->lastframe_health > bs->inventory[INVENTORY_HEALTH]) {
		if (BotChat_HitNoDeath(bs)) {
			bs->stand_time = FloatTime() + BotChatTime(bs);
			AIEnter_Stand(bs, "battle fight: chat health decreased");
			return qfalse;
		}
	}
	//if the bot hit someone
	if (bs->cur_ps.persistant[PERS_HITS] > bs->lasthitcount) {
		if (BotChat_HitNoKill(bs)) {
			bs->stand_time = FloatTime() + BotChatTime(bs);
			AIEnter_Stand(bs, "battle fight: chat hit someone");
			return qfalse;
		}
	}
	//if the enemy is not visible
	if (!BotEntityVisible(bs->entitynum, bs->eye, bs->viewangles, 360, bs->enemy)) {
		if (BotWantsToChase(bs)) {
			AIEnter_Battle_Chase(bs, "battle fight: enemy out of sight");
			return qfalse;
		} else {
			AIEnter_Seek_LTG(bs, "battle fight: enemy out of sight");
			return qfalse;
		}
	}
	//use holdable items
	BotBattleUseItems(bs);
	//
	bs->tfl = TFL_DEFAULT;
	if (bot_grapple.integer)
		bs->tfl |= TFL_GRAPPLEHOOK;
	//if in lava or slime the bot should be able to get out
	if (BotInLavaOrSlime(bs))
		bs->tfl |= TFL_LAVA | TFL_SLIME;
	//
	if (BotCanAndWantsToRocketJump(bs)) {
		bs->tfl |= TFL_ROCKETJUMP;
	}
	//choose the best weapon to fight with
	BotChooseWeapon(bs);
	//do attack movements
	moveresult = BotAttackMove(bs, bs->tfl);
	//if the movement failed
	if (moveresult.failure) {
		//reset the avoid reach, otherwise bot is stuck in current area
		trap_BotResetAvoidReach(bs->ms);
		//BotAI_Print(PRT_MESSAGE, "movement failure %d\n", moveresult.traveltype);
		bs->ltg_time = 0;
	}
	//
	BotAIBlocked(bs, &moveresult, qfalse);
	//aim at the enemy
	BotAimAtEnemy(bs);
	//attack the enemy if possible
	BotCheckAttack(bs);
	//if the bot wants to retreat
	if (!(bs->flags & BFL_FIGHTSUICIDAL)) {
		if (BotWantsToRetreat(bs)) {
			AIEnter_Battle_Retreat(bs, "battle fight: wants to retreat");
			return qtrue;
		}
	}
	return qtrue;
}

/*
==================
AIEnter_Battle_Chase
==================
*/
void AIEnter_Battle_Chase(bot_state_t * bs, char *s)
{
	BotRecordNodeSwitch(bs, "battle chase", "", s);
	bs->chase_time = FloatTime();
	bs->ainode = AINode_Battle_Chase;
}

/*
==================
AINode_Battle_Chase
==================
*/
int AINode_Battle_Chase(bot_state_t * bs)
{
	bot_goal_t goal;
	vec3_t target, dir;
	bot_moveresult_t moveresult;
	float range;

	if (BotIsObserver(bs)) {
		AIEnter_Observer(bs, "battle chase: observer");
		return qfalse;
	}
	//if in the intermission
	if (BotIntermission(bs)) {
		AIEnter_Intermission(bs, "battle chase: intermission");
		return qfalse;
	}
	//respawn if dead
	if (BotIsDead(bs)) {
		AIEnter_Respawn(bs, "battle chase: bot dead");
		return qfalse;
	}
	//if no enemy
	if (bs->enemy < 0) {
		AIEnter_Seek_LTG(bs, "battle chase: no enemy");
		return qfalse;
	}
	//if the enemy is visible
	if (BotEntityVisible(bs->entitynum, bs->eye, bs->viewangles, 360, bs->enemy)) {
		AIEnter_Battle_Fight(bs, "battle chase");
		return qfalse;
	}
	//if there is another enemy
	if (BotFindEnemy(bs, -1)) {
		AIEnter_Battle_Fight(bs, "battle chase: better enemy");
		return qfalse;
	}
	//there is no last enemy area
	if (!bs->lastenemyareanum) {
		AIEnter_Seek_LTG(bs, "battle chase: no enemy area");
		return qfalse;
	}
	//
	bs->tfl = TFL_DEFAULT;
	if (bot_grapple.integer)
		bs->tfl |= TFL_GRAPPLEHOOK;
	//if in lava or slime the bot should be able to get out
	if (BotInLavaOrSlime(bs))
		bs->tfl |= TFL_LAVA | TFL_SLIME;
	//
	if (BotCanAndWantsToRocketJump(bs)) {
		bs->tfl |= TFL_ROCKETJUMP;
	}
	//map specific code
	BotMapScripts(bs);
	//create the chase goal
	goal.entitynum = bs->enemy;
	goal.areanum = bs->lastenemyareanum;
	VectorCopy(bs->lastenemyorigin, goal.origin);
	VectorSet(goal.mins, -8, -8, -8);
	VectorSet(goal.maxs, 8, 8, 8);
	//if the last seen enemy spot is reached the enemy could not be found
	if (trap_BotTouchingGoal(bs->origin, &goal))
		bs->chase_time = 0;
	//if there's no chase time left
	if (!bs->chase_time || bs->chase_time < FloatTime() - 10) {
		AIEnter_Seek_LTG(bs, "battle chase: time out");
		return qfalse;
	}
	//check for nearby goals periodicly
	if (bs->check_time < FloatTime()) {
		bs->check_time = FloatTime() + 1;
		range = 150;
		//
		if (BotNearbyGoal(bs, bs->tfl, &goal, range)) {
			//the bot gets 5 seconds to pick up the nearby goal item
			bs->nbg_time = FloatTime() + 0.1 * range + 1;
			trap_BotResetLastAvoidReach(bs->ms);
			AIEnter_Battle_NBG(bs, "battle chase: nbg");
			return qfalse;
		}
	}
	//
	BotUpdateBattleInventory(bs, bs->enemy);
	//initialize the movement state
	BotSetupForMovement(bs);
	//move towards the goal
	trap_BotMoveToGoal(&moveresult, bs->ms, &goal, bs->tfl);
	//if the movement failed
	if (moveresult.failure) {
		//reset the avoid reach, otherwise bot is stuck in current area
		trap_BotResetAvoidReach(bs->ms);
		//BotAI_Print(PRT_MESSAGE, "movement failure %d\n", moveresult.traveltype);
		bs->ltg_time = 0;
	}
	//
	BotAIBlocked(bs, &moveresult, qfalse);
	//
	if (moveresult.flags & (MOVERESULT_MOVEMENTVIEWSET | MOVERESULT_MOVEMENTVIEW | MOVERESULT_SWIMVIEW)) {
		VectorCopy(moveresult.ideal_viewangles, bs->ideal_viewangles);
	} else if (!(bs->flags & BFL_IDEALVIEWSET)) {
		if (bs->chase_time > FloatTime() - 2) {
			BotAimAtEnemy(bs);
		} else {
			if (trap_BotMovementViewTarget(bs->ms, &goal, bs->tfl, 300, target)) {
				VectorSubtract(target, bs->origin, dir);
				vectoangles(dir, bs->ideal_viewangles);
			} else {
				vectoangles(moveresult.movedir, bs->ideal_viewangles);
			}
		}
		bs->ideal_viewangles[2] *= 0.5;
	}
	//if the weapon is used for the bot movement
	if (moveresult.flags & MOVERESULT_MOVEMENTWEAPON)
		bs->weaponnum = moveresult.weapon;
	//if the bot is in the area the enemy was last seen in
	if (bs->areanum == bs->lastenemyareanum)
		bs->chase_time = 0;
	//if the bot wants to retreat (the bot could have been damage during the chase)
	if (BotWantsToRetreat(bs)) {
		AIEnter_Battle_Retreat(bs, "battle chase: wants to retreat");
		return qtrue;
	}
	return qtrue;
}

/*
==================
AIEnter_Battle_Retreat
==================
*/
void AIEnter_Battle_Retreat(bot_state_t * bs, char *s)
{
	BotRecordNodeSwitch(bs, "battle retreat", "", s);
	bs->ainode = AINode_Battle_Retreat;
}

/*
==================
AINode_Battle_Retreat
==================
*/
int AINode_Battle_Retreat(bot_state_t * bs)
{
	bot_goal_t goal;
	aas_entityinfo_t entinfo;
	bot_moveresult_t moveresult;
	vec3_t target, dir;
	float attack_skill, range;
	int areanum;

	if (BotIsObserver(bs)) {
		AIEnter_Observer(bs, "battle retreat: observer");
		return qfalse;
	}
	//if in the intermission
	if (BotIntermission(bs)) {
		AIEnter_Intermission(bs, "battle retreat: intermission");
		return qfalse;
	}
	//respawn if dead
	if (BotIsDead(bs)) {
		AIEnter_Respawn(bs, "battle retreat: bot dead");
		return qfalse;
	}
	//if no enemy
	if (bs->enemy < 0) {
		AIEnter_Seek_LTG(bs, "battle retreat: no enemy");
		return qfalse;
	}
	//
	BotEntityInfo(bs->enemy, &entinfo);
	if (EntityIsDead(&entinfo)) {
		AIEnter_Seek_LTG(bs, "battle retreat: enemy dead");
		return qfalse;
	}
	//if there is another better enemy
	if (BotFindEnemy(bs, bs->enemy)) {
#ifdef DEBUG
		BotAI_Print(PRT_MESSAGE, "found new better enemy\n");
#endif
	}
	//
	bs->tfl = TFL_DEFAULT;
	if (bot_grapple.integer)
		bs->tfl |= TFL_GRAPPLEHOOK;
	//if in lava or slime the bot should be able to get out
	if (BotInLavaOrSlime(bs))
		bs->tfl |= TFL_LAVA | TFL_SLIME;
	//map specific code
	BotMapScripts(bs);
	//update the attack inventory values
	BotUpdateBattleInventory(bs, bs->enemy);
	//if the bot doesn't want to retreat anymore... probably picked up some nice items
	if (BotWantsToChase(bs)) {
		//empty the goal stack, when chasing, only the enemy is the goal
		trap_BotEmptyGoalStack(bs->gs);
		//go chase the enemy
		AIEnter_Battle_Chase(bs, "battle retreat: wants to chase");
		return qfalse;
	}
	//update the last time the enemy was visible
	if (BotEntityVisible(bs->entitynum, bs->eye, bs->viewangles, 360, bs->enemy)) {
		bs->enemyvisible_time = FloatTime();
		VectorCopy(entinfo.origin, target);
		// if not a player enemy
		if (bs->enemy >= MAX_CLIENTS) {
		}
		//update the reachability area and origin if possible
		areanum = BotPointAreaNum(target);
		if (areanum && trap_AAS_AreaReachability(areanum)) {
			VectorCopy(target, bs->lastenemyorigin);
			bs->lastenemyareanum = areanum;
		}
	}
	//if the enemy is NOT visible for 4 seconds
	if (bs->enemyvisible_time < FloatTime() - 4) {
		//Makro - bot retreating, enemy not in sight - a good time to bandage
		//if (bs->lastframe_health > bs->inventory[INVENTORY_HEALTH]) {
		if (random() > 0.3f) {
			if (RQ3_Bot_NeedToBandage(bs)) {
				//If not bandaging already
				if (bs->cur_ps.weaponstate != WEAPON_BANDAGING) {
					Cmd_Bandage(&g_entities[bs->entitynum]);
				}
			}
		}
		AIEnter_Seek_LTG(bs, "battle retreat: lost enemy");
		return qfalse;
	}
	//else if the enemy is NOT visible
	else if (bs->enemyvisible_time < FloatTime()) {
		//if there is another enemy
		if (BotFindEnemy(bs, -1)) {
			if (random() < 0.5f) {
				//if the bot is hurt
				if (RQ3_Bot_NeedToBandage(bs)) {
					//If the bot wants to bandage and not bandaging already
					if (bs->cur_ps.weaponstate != WEAPON_BANDAGING && RQ3_Bot_CheckBandage(bs)) {
						Cmd_Bandage(&g_entities[bs->entitynum]);
					}
				}
			}
			AIEnter_Battle_Fight(bs, "battle retreat: another enemy");
			return qfalse;
		} else {
			if (RQ3_Bot_NeedToBandage(bs) != 0) {
				//If not bandaging already
				if (bs->cur_ps.weaponstate != WEAPON_BANDAGING) {
					Cmd_Bandage(&g_entities[bs->entitynum]);
				}
			}
		}
	}
	//
	BotTeamGoals(bs, qtrue);
	//use holdable items
	BotBattleUseItems(bs);
	//get the current long term goal while retreating
	if (!BotLongTermGoal(bs, bs->tfl, qtrue, &goal)) {
		AIEnter_Battle_SuicidalFight(bs, "battle retreat: no way out");
		return qfalse;
	}
	//check for nearby goals periodicly
	if (bs->check_time < FloatTime()) {
		bs->check_time = FloatTime() + 1;
		range = 150;
#ifdef CTF
		if (gametype == GT_CTF) {
			//if carrying a flag the bot shouldn't be distracted too much
			if (BotCTFCarryingFlag(bs))
				range = 50;
		}
#endif				//CTF
		if (BotNearbyGoal(bs, bs->tfl, &goal, range)) {
			trap_BotResetLastAvoidReach(bs->ms);
			//time the bot gets to pick up the nearby goal item
			bs->nbg_time = FloatTime() + range / 100 + 1;
			AIEnter_Battle_NBG(bs, "battle retreat: nbg");
			return qfalse;
		}
	}
	//initialize the movement state
	BotSetupForMovement(bs);
	//move towards the goal
	trap_BotMoveToGoal(&moveresult, bs->ms, &goal, bs->tfl);
	//if the movement failed
	if (moveresult.failure) {
		//reset the avoid reach, otherwise bot is stuck in current area
		trap_BotResetAvoidReach(bs->ms);
		//BotAI_Print(PRT_MESSAGE, "movement failure %d\n", moveresult.traveltype);
		bs->ltg_time = 0;
	}
	//
	BotAIBlocked(bs, &moveresult, qfalse);
	//choose the best weapon to fight with
	BotChooseWeapon(bs);
	//if the view is fixed for the movement
	if (moveresult.flags & (MOVERESULT_MOVEMENTVIEW | MOVERESULT_SWIMVIEW)) {
		VectorCopy(moveresult.ideal_viewangles, bs->ideal_viewangles);
	} else if (!(moveresult.flags & MOVERESULT_MOVEMENTVIEWSET)
		   && !(bs->flags & BFL_IDEALVIEWSET)) {
		attack_skill = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_ATTACK_SKILL, 0, 1);
		//if the bot is skilled anough
		if (attack_skill > 0.3) {
			BotAimAtEnemy(bs);
		} else {
			if (trap_BotMovementViewTarget(bs->ms, &goal, bs->tfl, 300, target)) {
				VectorSubtract(target, bs->origin, dir);
				vectoangles(dir, bs->ideal_viewangles);
			} else {
				vectoangles(moveresult.movedir, bs->ideal_viewangles);
			}
			bs->ideal_viewangles[2] *= 0.5;
		}
	}
	//if the weapon is used for the bot movement
	if (moveresult.flags & MOVERESULT_MOVEMENTWEAPON)
		bs->weaponnum = moveresult.weapon;
	//attack the enemy if possible
	BotCheckAttack(bs);
	//
	return qtrue;
}

/*
==================
AIEnter_Battle_NBG
==================
*/
void AIEnter_Battle_NBG(bot_state_t * bs, char *s)
{
	BotRecordNodeSwitch(bs, "battle NBG", "", s);
	bs->ainode = AINode_Battle_NBG;
}

/*
==================
AINode_Battle_NBG
==================
*/
int AINode_Battle_NBG(bot_state_t * bs)
{
	int areanum;
	bot_goal_t goal;
	aas_entityinfo_t entinfo;
	bot_moveresult_t moveresult;
	float attack_skill;
	vec3_t target, dir;

	if (BotIsObserver(bs)) {
		AIEnter_Observer(bs, "battle nbg: observer");
		return qfalse;
	}
	//if in the intermission
	if (BotIntermission(bs)) {
		AIEnter_Intermission(bs, "battle nbg: intermission");
		return qfalse;
	}
	//respawn if dead
	if (BotIsDead(bs)) {
		AIEnter_Respawn(bs, "battle nbg: bot dead");
		return qfalse;
	}
	//if no enemy
	if (bs->enemy < 0) {
		AIEnter_Seek_NBG(bs, "battle nbg: no enemy");
		return qfalse;
	}
	//
	BotEntityInfo(bs->enemy, &entinfo);
	if (EntityIsDead(&entinfo)) {
		AIEnter_Seek_NBG(bs, "battle nbg: enemy dead");
		return qfalse;
	}
	//
	bs->tfl = TFL_DEFAULT;
	if (bot_grapple.integer)
		bs->tfl |= TFL_GRAPPLEHOOK;
	//if in lava or slime the bot should be able to get out
	if (BotInLavaOrSlime(bs))
		bs->tfl |= TFL_LAVA | TFL_SLIME;
	//
	if (BotCanAndWantsToRocketJump(bs)) {
		bs->tfl |= TFL_ROCKETJUMP;
	}
	//map specific code
	BotMapScripts(bs);
	//update the last time the enemy was visible
	if (BotEntityVisible(bs->entitynum, bs->eye, bs->viewangles, 360, bs->enemy)) {
		bs->enemyvisible_time = FloatTime();
		VectorCopy(entinfo.origin, target);
		// if not a player enemy
		if (bs->enemy >= MAX_CLIENTS) {
		}
		//update the reachability area and origin if possible
		areanum = BotPointAreaNum(target);
		if (areanum && trap_AAS_AreaReachability(areanum)) {
			VectorCopy(target, bs->lastenemyorigin);
			bs->lastenemyareanum = areanum;
		}
	}
	//if the bot has no goal or touches the current goal
	if (!trap_BotGetTopGoal(bs->gs, &goal)) {
		bs->nbg_time = 0;
	} else if (BotReachedGoal(bs, &goal)) {
		bs->nbg_time = 0;
	}
	//
	if (bs->nbg_time < FloatTime()) {
		//pop the current goal from the stack
		trap_BotPopGoal(bs->gs);
		//if the bot still has a goal
		if (trap_BotGetTopGoal(bs->gs, &goal))
			AIEnter_Battle_Retreat(bs, "battle nbg: time out");
		else
			AIEnter_Battle_Fight(bs, "battle nbg: time out");
		//
		return qfalse;
	}
	//initialize the movement state
	BotSetupForMovement(bs);
	//move towards the goal
	trap_BotMoveToGoal(&moveresult, bs->ms, &goal, bs->tfl);
	//if the movement failed
	if (moveresult.failure) {
		//reset the avoid reach, otherwise bot is stuck in current area
		trap_BotResetAvoidReach(bs->ms);
		//BotAI_Print(PRT_MESSAGE, "movement failure %d\n", moveresult.traveltype);
		bs->nbg_time = 0;
	}
	//
	BotAIBlocked(bs, &moveresult, qfalse);
	//update the attack inventory values
	BotUpdateBattleInventory(bs, bs->enemy);
	//choose the best weapon to fight with
	BotChooseWeapon(bs);
	//if the view is fixed for the movement
	if (moveresult.flags & (MOVERESULT_MOVEMENTVIEW | MOVERESULT_SWIMVIEW)) {
		VectorCopy(moveresult.ideal_viewangles, bs->ideal_viewangles);
	} else if (!(moveresult.flags & MOVERESULT_MOVEMENTVIEWSET)
		   && !(bs->flags & BFL_IDEALVIEWSET)) {
		attack_skill = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_ATTACK_SKILL, 0, 1);
		//if the bot is skilled anough and the enemy is visible
		if (attack_skill > 0.3) {
			//&& BotEntityVisible(bs->entitynum, bs->eye, bs->viewangles, 360, bs->enemy)
			BotAimAtEnemy(bs);
		} else {
			if (trap_BotMovementViewTarget(bs->ms, &goal, bs->tfl, 300, target)) {
				VectorSubtract(target, bs->origin, dir);
				vectoangles(dir, bs->ideal_viewangles);
			} else {
				vectoangles(moveresult.movedir, bs->ideal_viewangles);
			}
			bs->ideal_viewangles[2] *= 0.5;
		}
	}
	//if the weapon is used for the bot movement
	if (moveresult.flags & MOVERESULT_MOVEMENTWEAPON)
		bs->weaponnum = moveresult.weapon;
	//attack the enemy if possible
	BotCheckAttack(bs);
	//
	return qtrue;
}
