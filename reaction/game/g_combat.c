//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.126  2002/09/24 05:06:17  blaze
// fixed spectating so ref\'s can now use all the chasecam modes.
//
// Revision 1.125  2002/09/02 02:21:13  niceass
// removed spherical head detection
//
// Revision 1.124  2002/08/28 23:10:06  jbravo
// Added cg_RQ3_SuicideLikeARealMan, timestamping to server logs and
// fixed stats for non-TP modes.
//
// Revision 1.123  2002/08/27 11:28:43  jbravo
// Kevlar hits didnt tell the target who was shooting or of the kevlar got hit
//
// Revision 1.122  2002/08/27 07:50:55  jbravo
// Players can now use the kill cmd, plummet and kill teammates after rounds in
// tp without loosing frags.
//
// Revision 1.121  2002/08/27 01:25:22  jbravo
// Fixed scoring in TOURNAMENT mode and made it a legit gametype.
//
// Revision 1.120  2002/08/23 23:07:01  blaze
// Should have fixed the unkickable thing breaking explosive breakables.
//
// Revision 1.119  2002/08/22 05:00:01  blaze
// Allow func_buttons to be unkickable too (set spawnflags to 8)
//
// Revision 1.118  2002/08/21 03:35:16  niceass
// only get damage points if attacking a client
//
// Revision 1.117  2002/08/21 02:56:08  blaze
// added spawnflags 8 for breakables, lets mappers turn off kicking
//
// Revision 1.116  2002/08/18 20:26:35  jbravo
// New hitboxes.  Fixed CTB awards (flags)
//
// Revision 1.115  2002/08/07 16:13:33  jbravo
// Case carrier glowing removed. Ignorenum bug fixed
//
// Revision 1.114  2002/08/03 06:52:35  jbravo
// Fixed the plost3 sound in all radiopaks and now damage is only tracked for
// players you hit that are not on your team
//
// Revision 1.113  2002/07/31 19:56:32  makro
// Fixed the code for doors with health and the wait key set to a negative value
//
// Revision 1.112  2002/07/24 02:17:38  jbravo
// Added a respawn delay for CTB
//
// Revision 1.111  2002/07/20 18:26:25  jbravo
// FF 2 fix for CTB
//
// Revision 1.110  2002/07/20 02:25:53  jbravo
// Added the AQDT CTB sounds to the base radio paks
//
// Revision 1.109  2002/07/07 18:36:13  jbravo
// Added an AntiIdle system. Can play insane sounds for idle players, drop them
// from teams or kick them.   Upped version to Beta 2.1
//
// Revision 1.108  2002/07/04 04:20:41  jbravo
// Fixed my weaponchange cancel in the Use cmd, and fixed the bug where players
// that where in eye spectating someone moved on to another player instantly on death.
//
// Revision 1.107  2002/07/02 03:41:59  jbravo
// Fixed a 2 frags pr kill bug, the use cmd now cancels weaponchanges in progress
// and fixed the captain status lingering on people after switching from MM
//
// Revision 1.106  2002/06/30 17:33:01  jbravo
// New radio sounds and the 0wned sound was added.
//
// Revision 1.105  2002/06/29 20:57:25  niceass
// small change to kevlar detection
//
// Revision 1.104  2002/06/24 05:51:51  jbravo
// CTF mode is now semi working
//
// Revision 1.103  2002/06/23 18:29:21  jbravo
// Suicides now always gib.
//
// Revision 1.102  2002/06/22 00:12:53  jbravo
// Cleanup
//
// Revision 1.101  2002/06/21 16:54:15  makro
// Crash bug fix
//
// Revision 1.100  2002/06/21 15:04:55  makro
// Health functionality for movers should be complete now
//
// Revision 1.99  2002/06/20 22:32:43  jbravo
// Added last damaged player and fixed a test2 model problem (atrimum my ass :)
// Changed g_RQ3_printOwnObits to g_RQ3_showOwnKills and it also controls $K
//
// Revision 1.98  2002/06/16 20:09:42  niceass
// knockback fix
//
// Revision 1.97  2002/06/16 20:06:14  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.96  2002/06/16 17:38:00  jbravo
// Removed the MISSIONPACK ifdefs and missionpack only code.
//
// Revision 1.95  2002/06/13 21:03:31  jbravo
// MOre gibfixes
//
// Revision 1.94  2002/06/13 19:38:43  jbravo
// Small gib fix
//
// Revision 1.93  2002/06/11 23:40:18  jbravo
// Made the head sphere larger
//
// Revision 1.92  2002/06/05 21:54:38  jbravo
// Never say 100% done again ;)
//
// Revision 1.91  2002/06/05 20:52:47  jbravo
// Fixed sniper explode gib and sniper stomach gib. Gibs are now 100% :)
//
// Revision 1.90  2002/06/05 19:53:10  niceass
// gib fix
//
// Revision 1.89  2002/06/05 15:17:51  jbravo
// Gibbed players now vanish (gibs with them tho :() and suicide is no
// longer -2 frags.  Added Obit handling for telefrags and better handling
// for unhandled mod's
//
// Revision 1.88  2002/06/03 05:31:31  niceass
// kill message fixed
//
// Revision 1.87  2002/06/03 00:40:25  blaze
// some more breakables fixes(ssg chips)
//
// Revision 1.86  2002/05/31 17:32:11  jbravo
// HC gibs almost working :)
//
// Revision 1.85  2002/05/30 18:22:20  jbravo
// Misc fixes
//
// Revision 1.84  2002/05/28 01:46:58  jbravo
// Added stomach gibbing
//
// Revision 1.83  2002/05/28 01:17:01  jbravo
// More gib fixes.  g_RQ3_gib added
//
// Revision 1.82  2002/05/27 06:50:37  niceass
// headless code
//
// Revision 1.81  2002/05/21 17:55:26  jbravo
// Telefrags gave attacker 100000 dmg.
//
// Revision 1.80  2002/05/20 04:59:33  jbravo
// Lots of small fixes.
//
// Revision 1.79  2002/05/19 21:04:37  jbravo
// Tkok popup system
//
// Revision 1.78  2002/05/19 04:48:50  jbravo
// Added sniper headshot and hc really hard hit gibbing.  HC event gets lost
// between game and cgame
//
// Revision 1.77  2002/05/18 14:52:16  makro
// Bot stuff. Other stuff. Just... stuff :p
//
// Revision 1.76  2002/05/16 06:57:54  makro
// Doors with health (again !), bot-only trigger_pushes
//
// Revision 1.75  2002/05/15 17:13:22  makro
// Restored Q3A code for movers with health
//
// Revision 1.74  2002/05/15 13:58:35  makro
// Health for movers
//
// Revision 1.73  2002/05/15 05:38:36  niceass
// Knife fix and disabled new headshot code
//
// Revision 1.72  2002/05/12 18:07:08  jbravo
// Yet another obit fix
//
// Revision 1.71  2002/05/11 15:00:04  jbravo
// Fix for autojoin and a very minir for for Obits
//
// Revision 1.70  2002/05/10 08:10:18  jbravo
// Fixed a bug in the Obit system and a give (weapons or all) bug
//
// Revision 1.69  2002/05/10 07:47:23  jbravo
// Forgot grenade obits
//
// Revision 1.68  2002/05/10 04:06:27  jbravo
// Added Ignore
//
// Revision 1.67  2002/05/09 20:58:30  jbravo
// New Obit system and a warning cleanup in zcam
//
// Revision 1.66  2002/05/06 00:35:49  jbravo
// Small fixes to misc stuff
//
// Revision 1.65  2002/05/04 16:13:04  makro
// Bots
//
// Revision 1.64  2002/04/26 04:09:11  jbravo
// Got rid of the grey excelent icon over players heads.
//
// Revision 1.63  2002/04/26 03:39:34  jbravo
// added tkok, fixed players always leaving zcam modes when player thats
// beeing tracked dies
//
// Revision 1.62  2002/04/24 04:25:14  jbravo
// No rewards (humiliation on dead player or Icon on attacker) for knife kills
//
// Revision 1.61  2002/04/22 16:43:34  blaze
// Hey look, breakables explode now!  :)
//
// Revision 1.60  2002/04/20 23:54:55  blaze
// opps, breabable fix
//
// Revision 1.59  2002/04/07 03:22:48  jbravo
// Tweaks and crashbug fixes
//
// Revision 1.58  2002/04/06 20:47:24  niceass
// fall damage bug fix
//
// Revision 1.57  2002/04/03 09:26:47  jbravo
// New FF system. Warns and then finally kickbans teamwounders and
// teamkillers
//
// Revision 1.56  2002/04/03 03:13:16  blaze
// NEW BREAKABLE CODE - will break all old breakables(wont appear in maps)
//
// Revision 1.55  2002/03/31 03:31:24  jbravo
// Compiler warning cleanups
//
// Revision 1.54  2002/03/30 17:37:48  jbravo
// Added damage tracking to the server. Added zcam flic mode. cleaned up g_damage.
//
// Revision 1.53  2002/03/18 19:18:39  slicer
// Fixed bandage bugs ( i hope )
//
// Revision 1.52  2002/03/18 12:25:10  jbravo
// Live players dont get fraglines, except their own. Cleanups and some
// hacks to get bots to stop using knives only.
//
// Revision 1.51  2002/03/17 03:35:29  jbravo
// More radio tewaks and cleanups.
//
// Revision 1.50  2002/03/14 23:54:12  jbravo
// Added a variable system from AQ. Works the same except it uses $ for %
//
// Revision 1.49  2002/03/12 04:55:31  blaze
// stats should only be recored when the round is in progress
//
// Revision 1.48  2002/03/04 21:28:57  jbravo
// Make spectators that are following someone who dies stop at the time of
// death and not respawn somewhere else.
//
// Revision 1.47  2002/03/03 21:46:26  blaze
// weapon stats, done, beta test for bugs
//
// Revision 1.46  2002/03/01 18:21:26  jbravo
// Cleanups and removal of g_RQ3_sniperup
//
// Revision 1.45  2002/02/25 19:41:53  jbravo
// Fixed the use ESC and join menu to join teams when dead players are
// spectating in TP mode.
// Tuned the autorespawn system a bit.  Now dead ppl. are dead for a very
// small time before they are made into spectators.
//
// Revision 1.44  2002/02/24 18:49:21  jbravo
// Make it OK to frag teammates after rounds are over (no -1)
//
// Revision 1.43  2002/02/22 02:13:13  jbravo
// Fixed a few bugs and did some cleanups
//
// Revision 1.42  2002/02/10 21:21:23  slicer
// Saving persistant and other data on some events..
//
// Revision 1.41  2002/02/07 23:31:22  niceass
// fixed a bug in G_Combat that assumed pointers waren't NULL (only in DLLs was it a problem)
//
// Revision 1.40  2002/02/07 21:01:48  niceass
// AddScore bug fixed. I thought I put this in already!
//
// Revision 1.39  2002/02/06 03:10:43  jbravo
// Fix the instant spectate on death and an attempt to fix the scores
//
// Revision 1.38  2002/02/05 10:45:31  jbravo
// Cleaning up player_die and possibly fixing the scores
//
// Revision 1.37  2002/01/31 01:53:30  jbravo
// FF/no-FF fixes. g_friendlyFire 0 = no FF, 1 = FF, 2 = no FF + knockback
//
// Revision 1.36  2002/01/12 20:02:16  hal9000
// Verify we have a valid client pointer before using its members
//
// Revision 1.35  2002/01/11 20:20:58  jbravo
// Adding TP to main branch
//
// Revision 1.34  2002/01/11 19:48:30  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.33  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
// g_combat.c

#include "g_local.h"

/*
============
ScorePlum
============
*/
void ScorePlum(gentity_t * ent, vec3_t origin, int score)
{
	gentity_t *plum;

	plum = G_TempEntity(origin, EV_SCOREPLUM);
	// only send this temp entity to a single client
	plum->r.svFlags |= SVF_SINGLECLIENT;

	plum->r.singleClient = ent->s.number;
	//
	plum->s.otherEntityNum = ent->s.number;
	plum->s.time = score;
}

/*
============
AddScore

Adds score to both the client and his team
============
*/
void AddScore(gentity_t * ent, vec3_t origin, int score)
{
	if (!ent->client) {
		return;
	}
	// no scoring during pre-match warmup
	//if ( level.warmupTime ) {
	//      return;
	//}

	// show score plum
	// JBravo: not in TP
	if (g_gametype.integer != GT_TEAMPLAY)
		ScorePlum(ent, origin, score);
	//
	ent->client->ps.persistant[PERS_SCORE] += score;
	if (g_gametype.integer == GT_TEAM)
		level.teamScores[ent->client->ps.persistant[PERS_TEAM]] += score;
	CalculateRanks();
}

/*
=================
TossClientItems

Toss the weapon and powerups for the killed player
=================
*/
void TossClientItems(gentity_t * self)
{
	gitem_t *item;
	int weapon;
	float angle;
	int i;
	gentity_t *drop;

	//Elder: added
	int weaponInventory;

	// drop the weapon if not a gauntlet or machinegun
	weapon = self->s.weapon;

	//Elder: run through player STAT_WEAPONS and drop any unique weapons
	//That way, we can also account for servers with extra weapons
	//BTW, that means no cheating to get all weapons or it'll spawn mad!!
	weaponInventory = self->client->ps.stats[STAT_WEAPONS];

	//Elder: throw items in a "circle" starting at a random angle
	i = level.time;
	angle = Q_random(&i) * 30;
	//angle = 0;

	//Elder: added hadUniqueWeapons check - returns to qfalse if died with the gun
	//as opposed to dropping it, then died

	if ((weaponInventory & (1 << WP_M3)) == (1 << WP_M3)) {
		while (self->client->weaponCount[WP_M3]) {
			item = BG_FindItemForWeapon(WP_M3);
			Drop_Item(self, item, angle);
			self->client->pers.hadUniqueWeapon[WP_M3] = qfalse;
			self->client->uniqueWeapons--;
			angle += 30;
			self->client->weaponCount[WP_M3]--;
		}
	}

	if ((weaponInventory & (1 << WP_M4)) == (1 << WP_M4)) {
		while (self->client->weaponCount[WP_M4]) {
			item = BG_FindItemForWeapon(WP_M4);
			Drop_Item(self, item, angle);
			self->client->pers.hadUniqueWeapon[WP_M4] = qfalse;
			self->client->uniqueWeapons--;
			angle += 30;
			self->client->weaponCount[WP_M4]--;
		}
	}

	if ((weaponInventory & (1 << WP_MP5)) == (1 << WP_MP5)) {
		while (self->client->weaponCount[WP_MP5]) {
			item = BG_FindItemForWeapon(WP_MP5);
			Drop_Item(self, item, angle);
			self->client->pers.hadUniqueWeapon[WP_MP5] = qfalse;
			self->client->uniqueWeapons--;
			angle += 30;
			self->client->weaponCount[WP_MP5]--;
		}
	}

	if ((weaponInventory & (1 << WP_HANDCANNON)) == (1 << WP_HANDCANNON)) {
		while (self->client->weaponCount[WP_HANDCANNON]) {
			item = BG_FindItemForWeapon(WP_HANDCANNON);
			Drop_Item(self, item, angle);
			self->client->pers.hadUniqueWeapon[WP_HANDCANNON] = qfalse;
			self->client->uniqueWeapons--;
			angle += 30;
			self->client->weaponCount[WP_HANDCANNON]--;
		}
	}

	if ((weaponInventory & (1 << WP_SSG3000)) == (1 << WP_SSG3000)) {
		while (self->client->weaponCount[WP_SSG3000]) {
			item = BG_FindItemForWeapon(WP_SSG3000);
			Drop_Item(self, item, angle);
			self->client->pers.hadUniqueWeapon[WP_SSG3000] = qfalse;
			self->client->uniqueWeapons--;
			angle += 30;
			self->client->weaponCount[WP_SSG3000]--;
		}
	}
	//Elder: Always drop the pistol
	item = BG_FindItemForWeapon(WP_PISTOL);
	Drop_Item(self, item, angle);
	angle += 30;

	//Elder: drop a knife if player has at least one
	if (self->client->ps.ammo[WP_KNIFE] > 0) {
		item = BG_FindItemForWeapon(WP_KNIFE);
		Drop_Item(self, item, angle);
		angle += 30;
	}

	if (self->client->ps.stats[STAT_HOLDABLE_ITEM]) {
		Drop_Item(self, &bg_itemlist[self->client->ps.stats[STAT_HOLDABLE_ITEM]], angle);
		angle += 30;
	}
	// drop all the powerups if not in teamplay
	if (g_gametype.integer != GT_TEAM) {
		angle = 45;
		for (i = 1; i < PW_NUM_POWERUPS; i++) {
			if (self->client->ps.powerups[i] > level.time) {
				item = BG_FindItemForPowerup(i);
				if (!item) {
					continue;
				}
				drop = Drop_Item(self, item, angle);
				// decide how many seconds it has left
				drop->count = (self->client->ps.powerups[i] - level.time) / 1000;
				if (drop->count < 1) {
					drop->count = 1;
				}
				angle += 45;
			}
		}
	}
}

/*
==================
LookAtKiller
==================
*/
void LookAtKiller(gentity_t * self, gentity_t * inflictor, gentity_t * attacker)
{
	vec3_t dir;
	vec3_t angles;

	if (attacker && attacker != self) {
		VectorSubtract(attacker->s.pos.trBase, self->s.pos.trBase, dir);
	} else if (inflictor && inflictor != self) {
		VectorSubtract(inflictor->s.pos.trBase, self->s.pos.trBase, dir);
	} else {
		self->client->ps.stats[STAT_DEAD_YAW] = self->s.angles[YAW];
		return;
	}

	self->client->ps.stats[STAT_DEAD_YAW] = vectoyaw(dir);

	angles[YAW] = vectoyaw(dir);
	angles[PITCH] = 0;
	angles[ROLL] = 0;
}

/*
==================
GibEntity
==================
*/
void GibEntity(gentity_t * self, int killer)
{
	if (g_RQ3_gib.integer < 3)
		return;
	G_AddEvent(self, EV_GIB_PLAYER, killer);
	self->takedamage = qfalse;
	self->s.eType = ET_INVISIBLE;
	self->r.contents = 0;
}

// JBravo: head gibbing
void GibEntity_Headshot(gentity_t * self, int killer)
{
	G_AddEvent(self, EV_GIB_PLAYER_HEADSHOT, 0);
	self->client->noHead = qtrue;
}

// JBravo: stomach gibbing
void GibEntity_Stomach(gentity_t * self, int killer)
{
	G_TempEntity(self->r.currentOrigin, EV_GIB_PLAYER_STOMACH);
}

/*
==================
body_die
==================
*/
void body_die(gentity_t * self, gentity_t * inflictor, gentity_t * attacker, int damage, int meansOfDeath)
{
	if (self->health > GIB_HEALTH) {
		return;
	}
// JBravo: Gib control
	if (g_RQ3_gib.integer == 0) {
		return;
	}
	if (!g_blood.integer) {
		self->health = GIB_HEALTH + 1;
		return;
	}

	if (attacker->client
	    && ((g_gametype.integer == GT_TEAMPLAY && level.team_round_going) || g_gametype.integer != GT_TEAMPLAY))
		attacker->client->pers.records[REC_GIBSHOTS]++;

	GibEntity(self, 0);
}

// these are just for logging, the client prints its own messages
char *modNames[] = {
	"MOD_UNKNOWN",
	"MOD_SHOTGUN",
	"MOD_GAUNTLET",
	"MOD_MACHINEGUN",
	"MOD_GRENADE",
	"MOD_GRENADE_SPLASH",
	"MOD_ROCKET",
	"MOD_ROCKET_SPLASH",
	"MOD_PLASMA",
	"MOD_PLASMA_SPLASH",
	"MOD_RAILGUN",
	"MOD_LIGHTNING",
	"MOD_BFG",
	"MOD_BFG_SPLASH",
	"MOD_WATER",
	"MOD_SLIME",
	"MOD_LAVA",
	"MOD_CRUSH",
	"MOD_TELEFRAG",
	"MOD_FALLING",
	"MOD_SUICIDE",
	"MOD_TARGET_LASER",
	"MOD_TRIGGER_HURT",
	"MOD_GRAPPLE",
	//Blaze: Reaction MOD's
	"MOD_KNIFE",
	"MOD_KNIFE_THROWN",
	"MOD_PISTOL",
	"MOD_M4",
	"MOD_SNIPER",
	"MOD_MP5",
	"MOD_AKIMBO",
	"MOD_M3",
	"MOD_HANDCANNON",
	"MOD_KICK",
	"MOD_BLEEDING"
};

/*
==================
CheckAlmostCapture
==================
*/
void CheckAlmostCapture(gentity_t * self, gentity_t * attacker)
{
	gentity_t *ent;
	vec3_t dir;
	char *classname;

	// if this player was carrying a flag
	if (self->client->ps.powerups[PW_REDFLAG] ||
	    self->client->ps.powerups[PW_BLUEFLAG] || self->client->ps.powerups[PW_NEUTRALFLAG]) {
		// get the goal flag this player should have been going for
		if (g_gametype.integer == GT_CTF) {
			if (self->client->sess.sessionTeam == TEAM_BLUE) {
				classname = "team_CTF_blueflag";
			} else {
				classname = "team_CTF_redflag";
			}
		} else {
			if (self->client->sess.sessionTeam == TEAM_BLUE) {
				classname = "team_CTF_redflag";
			} else {
				classname = "team_CTF_blueflag";
			}
		}
		ent = NULL;
		do {
			ent = G_Find(ent, FOFS(classname), classname);
		} while (ent && (ent->flags & FL_DROPPED_ITEM));
		// if we found the destination flag and it's not picked up
		if (ent && !(ent->r.svFlags & SVF_NOCLIENT)) {
			// if the player was *very* close
			VectorSubtract(self->client->ps.origin, ent->s.origin, dir);
			if (VectorLength(dir) < 200) {
				self->client->ps.persistant[PERS_PLAYEREVENTS] ^= PLAYEREVENT_HOLYSHIT;
				if (attacker->client) {
					attacker->client->ps.persistant[PERS_PLAYEREVENTS] ^= PLAYEREVENT_HOLYSHIT;
				}
			}
		}
	}
}

/*
==================
CheckAlmostScored
==================
*/
void CheckAlmostScored(gentity_t * self, gentity_t * attacker)
{
	gentity_t *ent;
	vec3_t dir;
	char *classname;

	// if the player was carrying cubes
	if (self->client->ps.generic1) {
		if (self->client->sess.sessionTeam == TEAM_BLUE) {
			classname = "team_redobelisk";
		} else {
			classname = "team_blueobelisk";
		}
		ent = G_Find(NULL, FOFS(classname), classname);
		// if we found the destination obelisk
		if (ent) {
			// if the player was *very* close
			VectorSubtract(self->client->ps.origin, ent->s.origin, dir);
			if (VectorLength(dir) < 200) {
				self->client->ps.persistant[PERS_PLAYEREVENTS] ^= PLAYEREVENT_HOLYSHIT;
				if (attacker->client) {
					attacker->client->ps.persistant[PERS_PLAYEREVENTS] ^= PLAYEREVENT_HOLYSHIT;
				}
			}
		}
	}
}

/*
==================
SendObit
JBravo: actually send the messages
==================
*/
void SendObit(char *msg, gentity_t * deadguy, gentity_t * attacker)
{
	int i;
	gentity_t *other;

	if (g_gametype.integer != GT_TEAMPLAY) {
		trap_SendServerCommand(-1, va("print \"%s\"", msg));
	} else {
		if (g_RQ3_showOwnKills.integer == 0) {
			for (i = 0; i < level.maxclients; i++) {
				//Blaze: Prit out some Debug info
				if (&g_entities[i] == NULL) G_Printf("Ln 0693\n");
				
				other = &g_entities[i];
				if (!other->inuse || !other->client)
					continue;
				if (deadguy != other && level.team_round_going
				    && other->client->sess.sessionTeam != TEAM_SPECTATOR)
					continue;
				trap_SendServerCommand(other - g_entities, va("print \"%s\"", msg));
			}
		} else {
			for (i = 0; i < level.maxclients; i++) {
				//Blaze: Prit out some Debug info
				if (&g_entities[i] == NULL) G_Printf("Ln 1399\n");
				
				other = &g_entities[i];
				if (!other->inuse || !other->client)
					continue;
				if (deadguy != other && other != attacker &&
				    level.team_round_going && other->client->sess.sessionTeam != TEAM_SPECTATOR)
					continue;
				trap_SendServerCommand(other - g_entities, va("print \"%s\"", msg));
			}
		}
	}
}

/*
==================
PrintDeathMessage
JBravo: new Obit system
==================
*/
void PrintDeathMessage(gentity_t * target, gentity_t * attacker, int location, int meansOfDeath)
{
	int n, gender;
	char message[128], message2[128], death_msg[512];

	gender = target->client->radioGender;
	message[0] = message2[0] = '\0';

	switch (meansOfDeath) {
	case MOD_SUICIDE:
		Q_strncpyz(message, "suicides", sizeof(message));
		break;
	case MOD_FALLING:
		if (gender == GENDER_FEMALE)
			Q_strncpyz(message, "plummets to her death", sizeof(message));
		else if (gender == GENDER_NEUTER)
			Q_strncpyz(message, "plummets to its death", sizeof(message));
		else
			Q_strncpyz(message, "plummets to his death", sizeof(message));
		break;
	case MOD_CRUSH:
		Q_strncpyz(message, "was flattened", sizeof(message));
		break;
	case MOD_WATER:
		Q_strncpyz(message, "sank like a rock", sizeof(message));
		break;
	case MOD_SLIME:
		Q_strncpyz(message, "melted", sizeof(message));
		break;
	case MOD_LAVA:
		Q_strncpyz(message, "does a back flip into the lava", sizeof(message));
		break;
	case MOD_TARGET_LASER:
		Q_strncpyz(message, "saw the light", sizeof(message));
		break;
	case MOD_TRIGGER_HURT:
		Q_strncpyz(message, "was in the wrong place", sizeof(message));
		break;
	case MOD_BLEEDING:
		Q_strncpyz(message, "bleeds to death", sizeof(message));
		break;
	default:
		message[0] = '\0';
		break;
	}
	if (attacker == target) {
		switch (meansOfDeath) {
		case MOD_GRENADE_SPLASH:
			if (gender == GENDER_FEMALE)
				Q_strncpyz(message, "didn't throw her grenade far enough", sizeof(message));
			else if (gender == GENDER_NEUTER)
				Q_strncpyz(message, "didn't throw its grenade far enough", sizeof(message));
			else
				Q_strncpyz(message, "didn't throw his grenade far enough", sizeof(message));
			break;
		case MOD_ROCKET_SPLASH:
			if (gender == GENDER_FEMALE)
				Q_strncpyz(message, "blew herself up", sizeof(message));
			else if (gender == GENDER_NEUTER)
				Q_strncpyz(message, "blew itself up", sizeof(message));
			else
				Q_strncpyz(message, "blew himself up", sizeof(message));
			break;
		case MOD_PLASMA_SPLASH:
			if (gender == GENDER_FEMALE)
				Q_strncpyz(message, "melted herself", sizeof(message));
			else if (gender == GENDER_NEUTER)
				Q_strncpyz(message, "melted itself", sizeof(message));
			else
				Q_strncpyz(message, "melted himself", sizeof(message));
			break;
		case MOD_BFG_SPLASH:
			Q_strncpyz(message, "should have used a smaller gun", sizeof(message));
			break;
		default:
			if (gender == GENDER_FEMALE)
				Q_strncpyz(message, "killed herself", sizeof(message));
			else if (gender == GENDER_NEUTER)
				Q_strncpyz(message, "killed itself", sizeof(message));
			else
				Q_strncpyz(message, "killed himself", sizeof(message));
			break;
		}
	}
	if (attacker->client && attacker != target)
		message[0] = '\0';
	if (message[0] != '\0') {
		Com_sprintf(death_msg, sizeof(death_msg), "%s^7 %s\n", target->client->pers.netname, message);
		SendObit(death_msg, target, attacker);
		return;
	}

	if (attacker->client) {
		switch (meansOfDeath) {
		case MOD_FALLING:
			Q_strncpyz(message, " was taught how to fly by", sizeof(message));
			break;
		case MOD_PISTOL:
			switch (location) {
			case LOC_HDAM:
				if (gender == GENDER_NEUTER)
					Q_strncpyz(message, " has a hole in its head from", sizeof(message));
				else if (gender == GENDER_FEMALE)
					Q_strncpyz(message, " has a hole in her head from", sizeof(message));
				else
					Q_strncpyz(message, " has a hole in his head from", sizeof(message));
				Q_strncpyz(message2, "'s Mark 23 pistol", sizeof(message2));
				break;
			case LOC_CDAM:
				Q_strncpyz(message, " loses a vital chest organ thanks to", sizeof(message));
				Q_strncpyz(message2, "'s Mark 23 pistol", sizeof(message2));
				break;
			case LOC_SDAM:
				if (gender == GENDER_NEUTER)
					Q_strncpyz(message, " loses its lunch to", sizeof(message));
				else if (gender == GENDER_FEMALE)
					Q_strncpyz(message, " loses her lunch to", sizeof(message));
				else
					Q_strncpyz(message, " loses his lunch to", sizeof(message));
				Q_strncpyz(message2, "'s .45 caliber pistol round", sizeof(message));
				break;
			case LOC_LDAM:
				Q_strncpyz(message, " is legless because of", sizeof(message));
				Q_strncpyz(message2, "'s Mark 23 pistol", sizeof(message2));
				break;
			default:
				Q_strncpyz(message, "was shot by", sizeof(message));
				Q_strncpyz(message2, "'s Mark 23 Pistol", sizeof(message2));
			}
			break;
		case MOD_MP5:
			switch (location) {
			case LOC_HDAM:
				Q_strncpyz(message, "'s brains are on the wall thanks to", sizeof(message));
				Q_strncpyz(message2, "'s 10mm MP5/10 round", sizeof(message));
				break;
			case LOC_CDAM:
				Q_strncpyz(message, " feels some chest pain via", sizeof(message));
				Q_strncpyz(message2, "'s MP5/10 Submachinegun", sizeof(message));
				break;
			case LOC_SDAM:
				Q_strncpyz(message, " needs some Pepto Bismol after", sizeof(message));
				Q_strncpyz(message2, "'s 10mm MP5 round", sizeof(message2));
				break;
			case LOC_LDAM:
				if (gender == GENDER_NEUTER)
					Q_strncpyz(message, " had its legs blown off thanks to", sizeof(message));
				else if (gender == GENDER_FEMALE)
					Q_strncpyz(message, " had her legs blown off thanks to", sizeof(message));
				else
					Q_strncpyz(message, " had his legs blown off thanks to", sizeof(message));
				Q_strncpyz(message2, "'s MP5/10 Submachinegun", sizeof(message2));
				break;
			default:
				Q_strncpyz(message, " was shot by", sizeof(message));
				Q_strncpyz(message2, "'s MP5/10 Submachinegun", sizeof(message2));
			}
			break;
		case MOD_M4:
			switch (location) {
			case LOC_HDAM:
				Q_strncpyz(message, " had a makeover by", sizeof(message));
				Q_strncpyz(message2, "'s M4 Assault Rifle", sizeof(message2));
				break;
			case LOC_CDAM:
				Q_strncpyz(message, " feels some heart burn thanks to", sizeof(message));
				Q_strncpyz(message2, "'s M4 Assault Rifle", sizeof(message2));
				break;
			case LOC_SDAM:
				Q_strncpyz(message, " has an upset stomach thanks to", sizeof(message));
				Q_strncpyz(message2, "'s M4 Assault Rifle", sizeof(message2));
				break;
			case LOC_LDAM:
				Q_strncpyz(message, " is now shorter thanks to", sizeof(message));
				Q_strncpyz(message2, "'s M4 Assault Rifle", sizeof(message2));
				break;
			default:
				Q_strncpyz(message, " was shot by", sizeof(message));
				Q_strncpyz(message2, "'s M4 Assault Rifle", sizeof(message2));
			}
			break;
		case MOD_M3:
			n = rand() % 2 + 1;
			if (n == 1) {
				Q_strncpyz(message, " accepts", sizeof(message));
				Q_strncpyz(message2, "'s M3 Super 90 Assault Shotgun in hole-y matrimony",
					   sizeof(message2));
			} else {
				Q_strncpyz(message, " is full of buckshot from", sizeof(message));
				Q_strncpyz(message2, "'s M3 Super 90 Assault Shotgun", sizeof(message2));
			}
			break;
		case MOD_HANDCANNON:
			n = rand() % 2 + 1;
			if (n == 1) {
				Q_strncpyz(message, " ate", sizeof(message));
				Q_strncpyz(message2, "'s sawed-off 12 gauge", sizeof(message2));
			} else {
				Q_strncpyz(message, " is full of buckshot from", sizeof(message));
				Q_strncpyz(message2, "'s sawed off shotgun", sizeof(message2));
			}
			break;
		case MOD_GRENADE:
			Q_strncpyz(message, " ate", sizeof(message));
			Q_strncpyz(message2, "'s grenade", sizeof(message2));
			break;
		case MOD_GRENADE_SPLASH:
			Q_strncpyz(message, " was shredded by", sizeof(message));
			Q_strncpyz(message2, "'s shrapnel", sizeof(message2));
			break;
		case MOD_SNIPER:
			switch (location) {
			case LOC_HDAM:
				if (RQ3_isZoomed(target)) {
					if (gender == GENDER_NEUTER)
						Q_strncpyz(message,
							   " saw the sniper bullet go through its scope thanks to",
							   sizeof(message));
					else if (gender == GENDER_FEMALE)
						Q_strncpyz(message,
							   " saw the sniper bullet go through her scope thanks to",
							   sizeof(message));
					else
						Q_strncpyz(message,
							   " saw the sniper bullet go through his scope thanks to",
							   sizeof(message));
				} else {
					Q_strncpyz(message, " caught a sniper bullet between the eyes from",
						   sizeof(message));
				}
				break;
			case LOC_CDAM:
				Q_strncpyz(message, " was picked off by", sizeof(message));
				break;
			case LOC_SDAM:
				Q_strncpyz(message, " was sniped in the stomach by", sizeof(message));
				break;
			case LOC_LDAM:
				Q_strncpyz(message, " was shot in the legs by", sizeof(message));
				break;
			default:
				Q_strncpyz(message, " was sniped by", sizeof(message));
			}
			break;
		case MOD_AKIMBO:
			switch (location) {
			case LOC_HDAM:
				Q_strncpyz(message, " was trepanned by", sizeof(message));
				Q_strncpyz(message2, "'s akimbo Mark 23 pistols", sizeof(message2));
				break;
			case LOC_CDAM:
				Q_strncpyz(message, " was John Woo'd by", sizeof(message));
				break;
			case LOC_SDAM:
				Q_strncpyz(message, " needs some new kidneys thanks to", sizeof(message));
				Q_strncpyz(message2, "'s akimbo Mark 23 pistols", sizeof(message2));
				break;
			case LOC_LDAM:
				Q_strncpyz(message, " was shot in the legs by", sizeof(message));
				Q_strncpyz(message2, "'s akimbo Mark 23 pistols", sizeof(message2));
				break;
			default:
				Q_strncpyz(message, " was shot by", sizeof(message));
				Q_strncpyz(message2, "'s pair of Mark 23 Pistols", sizeof(message2));
			}
			break;
		case MOD_KNIFE:
			switch (location) {
			case LOC_HDAM:
				if (gender == GENDER_NEUTER)
					Q_strncpyz(message, " had its throat slit by", sizeof(message));
				else if (gender == GENDER_FEMALE)
					Q_strncpyz(message, " had her throat slit by", sizeof(message));
				else
					Q_strncpyz(message, " had his throat slit by", sizeof(message));
				break;
			case LOC_CDAM:
				Q_strncpyz(message, " had open heart surgery, compliments of", sizeof(message));
				break;
			case LOC_SDAM:
				Q_strncpyz(message, " was gutted by", sizeof(message));
				break;
			case LOC_LDAM:
				Q_strncpyz(message, " was stabbed repeatedly in the legs by", sizeof(message));
				break;
			default:
				Q_strncpyz(message, " was slashed apart by", sizeof(message));
				Q_strncpyz(message2, "'s Combat Knife", sizeof(message2));
			}
			break;
		case MOD_KNIFE_THROWN:
			switch (location) {
			case LOC_HDAM:
				Q_strncpyz(message, " caught", sizeof(message));
				if (gender == GENDER_NEUTER)
					Q_strncpyz(message2, "'s flying knife with its forehead", sizeof(message2));
				else if (gender == GENDER_FEMALE)
					Q_strncpyz(message2, "'s flying knife with her forehead", sizeof(message2));
				else
					Q_strncpyz(message2, "'s flying knife with his forehead", sizeof(message2));
				break;
			case LOC_CDAM:
				Q_strncpyz(message, "'s ribs don't help against", sizeof(message));
				Q_strncpyz(message2, "'s flying knife", sizeof(message2));
				break;
			case LOC_SDAM:
				if (gender == GENDER_NEUTER)
					Q_strncpyz(message, " sees the contents of its own stomach thanks to",
						   sizeof(message));
				else if (gender == GENDER_FEMALE)
					Q_strncpyz(message, " sees the contents of her own stomach thanks to",
						   sizeof(message));
				else
					Q_strncpyz(message, " sees the contents of his own stomach thanks to",
						   sizeof(message));
				Q_strncpyz(message2, "'s flying knife", sizeof(message2));
				break;
			case LOC_LDAM:
				if (gender == GENDER_NEUTER)
					Q_strncpyz(message, " had its legs cut off thanks to", sizeof(message));
				else if (gender == GENDER_FEMALE)
					Q_strncpyz(message, " had her legs cut off thanks to", sizeof(message));
				else
					Q_strncpyz(message, " had his legs cut off thanks to", sizeof(message));
				Q_strncpyz(message2, "'s flying knife", sizeof(message2));
				break;
			default:
				Q_strncpyz(message, " was hit by", sizeof(message));
				Q_strncpyz(message2, "'s flying Combat Knife", sizeof(message2));
			}
			break;
		case MOD_KICK:
			n = rand() % 3 + 1;
			if (n == 1) {
				if (gender == GENDER_NEUTER)
					Q_strncpyz(message, " got its ass kicked by", sizeof(message));
				else if (gender == GENDER_FEMALE)
					Q_strncpyz(message, " got her ass kicked by", sizeof(message));
				else
					Q_strncpyz(message, " got his ass kicked by", sizeof(message));
			} else if (n == 2) {
				Q_strncpyz(message, " couldn't remove", sizeof(message));
				if (gender == GENDER_NEUTER)
					Q_strncpyz(message2, "'s boot from its ass", sizeof(message2));
				else if (gender == GENDER_FEMALE)
					Q_strncpyz(message2, "'s boot from her ass", sizeof(message2));
				else
					Q_strncpyz(message2, "'s boot from his ass", sizeof(message2));
			} else {
				if (gender == GENDER_NEUTER)
					Q_strncpyz(message, " had a Bruce Lee put on it by", sizeof(message));
				else if (gender == GENDER_FEMALE)
					Q_strncpyz(message, " had a Bruce Lee put on her by", sizeof(message));
				else
					Q_strncpyz(message, " had a Bruce Lee put on him by", sizeof(message));
				Q_strncpyz(message2, ", with a quickness", sizeof(message2));
			}
			break;
		case MOD_TELEFRAG:
			Q_strncpyz(message, " tried to invade", sizeof(message));
			Q_strncpyz(message2, "'s personal space", sizeof(message2));
			break;
		default:
			Q_strncpyz(message, " died.", sizeof(message));
			break;
//                              Com_sprintf (message, sizeof(message), "died via unhandled MOD %i. Report this to JBravo", meansOfDeath);
		}
		Com_sprintf(death_msg, sizeof(death_msg), "%s^7%s %s^7%s\n", target->client->pers.netname, message,
			    attacker->client->pers.netname, message2);
		SendObit(death_msg, target, attacker);
	}
}

/*
==================
player_die
==================
*/
void player_die(gentity_t * self, gentity_t * inflictor, gentity_t * attacker, int damage, int meansOfDeath)
{
	gentity_t *DMReward;
	int anim, contents, killer, i, hurt;
	char *killerName, *obit;

	hurt = 0;
	//Blaze: Stop bleeding when dead
	if (self->client) {
		//Elder: drop the primed grenade
		if (self->client->ps.weapon == WP_GRENADE && self->client->ps.weaponstate == WEAPON_COCKED) {
			FireWeapon(self);
		}
		// Hawkins put spread back and zoom out
		//Elder: remove zoom bits
// JBravo: moving this down below the Obit printout
//              Cmd_Unzoom(self);
		self->client->bleeding = 0;
		self->client->bleed_remain = 0;
		//Elder: added;
//              self->client->ps.stats[STAT_RQ3] &= ~RQ3_BANDAGE_WORK;
		self->client->ps.stats[STAT_RQ3] &= ~RQ3_BANDAGE_NEED;
		self->client->killStreak = 0;

		//Elder: stop reload attempts
		self->client->reloadAttempts = 0;

		//JBravo: switch off the lasersight
		if (self->client->lasersight) {
			G_FreeEntity(self->client->lasersight);
			self->client->lasersight = NULL;
		}
		// JBravo: clear the gib flag
		self->client->gibbed = qfalse;
	}
	if (self->client->ps.pm_type == PM_DEAD) {
		return;
	}

	if (level.intermissiontime) {
		return;
	}
// JBravo: lets not bother with those CTF functions in Teamplay
	if (g_gametype.integer != GT_TEAMPLAY) {
		// check for an almost capture
		CheckAlmostCapture(self, attacker);
		// check for a player that almost brought in cubes
		CheckAlmostScored(self, attacker);
	}

	self->client->ps.pm_type = PM_DEAD;

	if (attacker) {
		killer = attacker->s.number;
		if (attacker->client) {
			killerName = attacker->client->pers.netname;
		} else {
			killerName = "<non-client>";
		}
	} else {
		killer = ENTITYNUM_WORLD;
		killerName = "<world>";
	}

	if (killer < 0 || killer >= MAX_CLIENTS) {
		killer = ENTITYNUM_WORLD;
		killerName = "<world>";
		// Elder: Statistics tracking
		if ((g_gametype.integer == GT_TEAMPLAY && level.team_round_going) || g_gametype.integer != GT_TEAMPLAY)
			self->client->pers.records[REC_WORLDDEATHS]++;
	}

	if (meansOfDeath < 0 || meansOfDeath >= sizeof(modNames) / sizeof(modNames[0])) {
		obit = "<bad obituary>";
	} else {
		obit = modNames[meansOfDeath];
	}

	G_LogPrintf("Kill: %i %i %i: %s killed %s by %s\n",
		    killer, self->s.number, meansOfDeath, killerName, self->client->pers.netname, obit);

	// broadcast the death event to everyone
	// Elder: use appropriate obit event and update statistics tracking
	// JBravo: Im redoing the Obits.

	if ((self->client->lasthurt_location & LOCATION_HEAD) == LOCATION_HEAD ||
	    (self->client->lasthurt_location & LOCATION_FACE) == LOCATION_FACE) {
		// head kill
		if ((g_gametype.integer == GT_TEAMPLAY && level.team_round_going) || g_gametype.integer != GT_TEAMPLAY) {
			self->client->pers.records[REC_HEADDEATHS]++;
			if (attacker && attacker->client)
				attacker->client->pers.records[REC_HEADKILLS]++;
		}
		PrintDeathMessage(self, attacker, LOC_HDAM, meansOfDeath);
		hurt = LOC_HDAM;
	} else if ((self->client->lasthurt_location & LOCATION_CHEST) == LOCATION_CHEST ||
		   (self->client->lasthurt_location & LOCATION_SHOULDER) == LOCATION_SHOULDER) {
		// chest kill
		if ((g_gametype.integer == GT_TEAMPLAY && level.team_round_going) || g_gametype.integer != GT_TEAMPLAY) {
			self->client->pers.records[REC_CHESTDEATHS]++;
			if (attacker && attacker->client)
				attacker->client->pers.records[REC_CHESTKILLS]++;
		}
		PrintDeathMessage(self, attacker, LOC_CDAM, meansOfDeath);
		hurt = LOC_CDAM;
	} else if ((self->client->lasthurt_location & LOCATION_STOMACH) == LOCATION_STOMACH ||
		   (self->client->lasthurt_location & LOCATION_GROIN) == LOCATION_GROIN) {
		// stomach kill
		if ((g_gametype.integer == GT_TEAMPLAY && level.team_round_going) || g_gametype.integer != GT_TEAMPLAY) {
			self->client->pers.records[REC_STOMACHDEATHS]++;
			if (attacker && attacker->client)
				attacker->client->pers.records[REC_STOMACHKILLS]++;
		}
		PrintDeathMessage(self, attacker, LOC_SDAM, meansOfDeath);
		hurt = LOC_SDAM;
	} else if ((self->client->lasthurt_location & LOCATION_LEG) == LOCATION_LEG ||
		   (self->client->lasthurt_location & LOCATION_FOOT) == LOCATION_FOOT) {
		// leg kill
		if ((g_gametype.integer == GT_TEAMPLAY && level.team_round_going) || g_gametype.integer != GT_TEAMPLAY) {
			self->client->pers.records[REC_LEGDEATHS]++;
			if (attacker && attacker->client)
				attacker->client->pers.records[REC_LEGKILLS]++;
		}
		PrintDeathMessage(self, attacker, LOC_LDAM, meansOfDeath);
		hurt = LOC_LDAM;
	} else {
		// non-location/world kill
		PrintDeathMessage(self, attacker, LOC_NOLOC, meansOfDeath);
		hurt = 0;
	}

	Cmd_Unzoom(self);

	// Elder: Statistics tracking
	//Blaze: make sure the game is in progress before recording stats
	if ((g_gametype.integer == GT_TEAMPLAY && level.team_round_going) || g_gametype.integer != GT_TEAMPLAY) {
		switch (meansOfDeath) {
		case MOD_KNIFE:
			if (attacker && attacker->client)
				attacker->client->pers.records[REC_KNIFESLASHKILLS]++;
			self->client->pers.records[REC_KNIFESLASHDEATHS]++;
			break;
		case MOD_KNIFE_THROWN:
			if (attacker && attacker->client)
				attacker->client->pers.records[REC_KNIFETHROWKILLS]++;
			self->client->pers.records[REC_KNIFETHROWDEATHS]++;
			break;
		case MOD_PISTOL:
			if (attacker && attacker->client)
				attacker->client->pers.records[REC_MK23KILLS]++;
			self->client->pers.records[REC_MK23DEATHS]++;
			break;
		case MOD_M3:
			if (attacker && attacker->client)
				attacker->client->pers.records[REC_M3KILLS]++;
			self->client->pers.records[REC_M3DEATHS]++;
			break;
		case MOD_M4:
			if (attacker && attacker->client)
				attacker->client->pers.records[REC_M4KILLS]++;
			self->client->pers.records[REC_M4DEATHS]++;
			break;
		case MOD_MP5:
			if (attacker && attacker->client)
				attacker->client->pers.records[REC_MP5KILLS]++;
			self->client->pers.records[REC_MP5DEATHS]++;
			break;
		case MOD_SNIPER:
			if (attacker && attacker->client)
				attacker->client->pers.records[REC_SSG3000KILLS]++;
			self->client->pers.records[REC_SSG3000DEATHS]++;
			break;
		case MOD_HANDCANNON:
			if (attacker && attacker->client)
				attacker->client->pers.records[REC_HANDCANNONKILLS]++;
			self->client->pers.records[REC_HANDCANNONDEATHS]++;
			break;
		case MOD_AKIMBO:
			if (attacker && attacker->client)
				attacker->client->pers.records[REC_AKIMBOKILLS]++;
			self->client->pers.records[REC_AKIMBODEATHS]++;
			break;
		case MOD_GRENADE:
		case MOD_GRENADE_SPLASH:
			if (attacker && attacker->client)
				attacker->client->pers.records[REC_GRENADEKILLS]++;
			self->client->pers.records[REC_GRENADEDEATHS]++;
			break;
		case MOD_KICK:
			if (attacker && attacker->client)
				attacker->client->pers.records[REC_KICKKILLS]++;
			self->client->pers.records[REC_KICKDEATHS]++;
			break;
			// JBravo: adding a default here to catch potential bugs
		default:
			break;
		}
	}
	self->enemy = attacker;
	if ((g_gametype.integer == GT_TEAMPLAY && level.team_round_going) || g_gametype.integer != GT_TEAMPLAY) {
		//Makro - crash bug fix
		if ((self->client != NULL) && (attacker->client != NULL)) {
			self->client->ps.persistant[PERS_KILLED]++;
			//Blaze: Give the attacker 1 kill
			attacker->client->pers.records[REC_KILLS]++;
		}
	}

	if (attacker && attacker->client) {
// JBravo: Add multiple last killed system.
		AddKilledPlayer(attacker, self);
		ResetKills(self);
// JBravo: make it OK to frag teammates after rounds are over.
		if (attacker == self) {
			if (g_gametype.integer == GT_TEAMPLAY && !level.team_round_going && !self->client->SuicideLikeARealMan) {
			} else
				AddScore(attacker, self->r.currentOrigin, -1);
		} else if (OnSameTeam(self, attacker)) {
			if (g_gametype.integer == GT_TEAMPLAY && level.team_round_going) {
				AddScore(attacker, self->r.currentOrigin, -1);
				//If the kill was a TK, remove 1 from REC_KILLS to negate the one given earlyier
				attacker->client->pers.records[REC_KILLS]--;
				//Also, increment the TK's record
				attacker->client->pers.records[REC_TEAMKILLS]++;
				Add_TeamKill(attacker);
				trap_SendServerCommand(self - g_entities,
						       va("rq3_cmd %i %s", TKOK, attacker->client->pers.netname));
			} else if (g_gametype.integer == GT_CTF) {
				AddScore(attacker, self->r.currentOrigin, -1);
				attacker->client->pers.records[REC_KILLS]--;
				attacker->client->pers.records[REC_TEAMKILLS]++;
				Add_TeamKill(attacker);
				trap_SendServerCommand(self - g_entities,
						       va("rq3_cmd %i %s", TKOK, attacker->client->pers.netname));
			}
		} else {
			// Increase number of kills this life for attacker
			// JBravo: unless we are in teamplay
			if (g_gametype.integer == GT_TEAMPLAY) {
				attacker->client->killStreak++;
				AddScore(attacker, self->r.currentOrigin, 1);
			} else if (g_gametype.integer == GT_CTF || g_gametype.integer == GT_TOURNAMENT) {
				attacker->client->killStreak = 0;
				AddScore(attacker, self->r.currentOrigin, 1);
			} else {
				attacker->client->killStreak++;
			}
			// DM reward scoring, should add an if statement to get around this when
			// we add teamplay.
			// JBravo: Done ;)
			if (g_gametype.integer == GT_FFA) {
				if (attacker->client->killStreak < 4)
					AddScore(attacker, self->r.currentOrigin, 1);
				else if (attacker->client->killStreak < 8) {
					AddScore(attacker, self->r.currentOrigin, 2);
					DMReward = G_TempEntity(self->r.currentOrigin, EV_DMREWARD);
					DMReward->s.otherEntityNum2 = killer;
					DMReward->s.eventParm = attacker->client->killStreak;
					DMReward->r.svFlags = SVF_BROADCAST;
				} else if (attacker->client->killStreak < 16) {
					AddScore(attacker, self->r.currentOrigin, 4);
					DMReward = G_TempEntity(self->r.currentOrigin, EV_DMREWARD);
					DMReward->s.otherEntityNum2 = killer;
					DMReward->s.eventParm = attacker->client->killStreak;
					DMReward->r.svFlags = SVF_BROADCAST;
				} else if (attacker->client->killStreak < 32) {
					AddScore(attacker, self->r.currentOrigin, 8);
					DMReward = G_TempEntity(self->r.currentOrigin, EV_DMREWARD);
					DMReward->s.otherEntityNum2 = killer;
					DMReward->s.eventParm = attacker->client->killStreak;
					DMReward->r.svFlags = SVF_BROADCAST;
				} else {
					AddScore(attacker, self->r.currentOrigin, 16);
					DMReward = G_TempEntity(self->r.currentOrigin, EV_DMREWARD);
					DMReward->s.otherEntityNum2 = killer;
					DMReward->s.eventParm = attacker->client->killStreak;
					DMReward->r.svFlags = SVF_BROADCAST;
				}
			}
// JBravo: adding the 0wned sound
			if (meansOfDeath == MOD_KNIFE) {
				trap_SendServerCommand(-1, va("rq3_cmd %i", OWNED));
			}
			attacker->client->lastKillTime = level.time;
		}
	} else {
		if (g_gametype.integer == GT_TEAMPLAY && !level.team_round_going && !self->client->SuicideLikeARealMan) {
		} else
			AddScore(self, self->r.currentOrigin, -1);
	}

	// Add team bonuses
	// JBravo: unless we are in teamplay
	if (g_gametype.integer != GT_TEAMPLAY) {
		Team_FragBonuses(self, inflictor, attacker);
	}
	// if I committed suicide, the flag does not fall, it returns.
	// Unless we are in teamplay
	if (meansOfDeath == MOD_SUICIDE) {
		// Elder: Statistics tracking
		if ((g_gametype.integer == GT_TEAMPLAY && level.team_round_going) || g_gametype.integer != GT_TEAMPLAY) {
			self->client->pers.records[REC_SUICIDES]++;
			self->client->pers.records[REC_KILLS]--;
		}
		if (g_gametype.integer != GT_TEAMPLAY) {
			if (self->client->ps.powerups[PW_NEUTRALFLAG]) {	// only happens in One Flag CTF
				Team_ReturnFlag(TEAM_FREE);
				self->client->ps.powerups[PW_NEUTRALFLAG] = 0;
			} else if (self->client->ps.powerups[PW_REDFLAG]) {	// only happens in standard CTF
				Team_ReturnFlag(TEAM_RED);
				self->client->ps.powerups[PW_REDFLAG] = 0;
			} else if (self->client->ps.powerups[PW_BLUEFLAG]) {	// only happens in standard CTF
				Team_ReturnFlag(TEAM_BLUE);
				self->client->ps.powerups[PW_BLUEFLAG] = 0;
			}
		}
	}
	// if client is in a nodrop area, don't drop anything (but return CTF flags!)
	contents = trap_PointContents(self->r.currentOrigin, -1);
	if (!(contents & CONTENTS_NODROP)) {
		TossClientItems(self);
	} else {
		if (g_gametype.integer != GT_TEAMPLAY) {
			if (self->client->ps.powerups[PW_NEUTRALFLAG]) {	// only happens in One Flag CTF
				Team_ReturnFlag(TEAM_FREE);
			} else if (self->client->ps.powerups[PW_REDFLAG]) {	// only happens in standard CTF
				Team_ReturnFlag(TEAM_RED);
			} else if (self->client->ps.powerups[PW_BLUEFLAG]) {	// only happens in standard CTF
				Team_ReturnFlag(TEAM_BLUE);
			}
		}
	}

// JBravo: no need for automatic scoreboard on deaths.
	if (g_gametype.integer != GT_TEAMPLAY) {
		Cmd_Score_f(self);	// show scores
	}
	// send updated scores to any clients that are following this one,
	// or they would get stale scoreboards
	for (i = 0; i < level.maxclients; i++) {
		gclient_t *client;

		client = &level.clients[i];

		if (client->pers.connected != CON_CONNECTED) {
			continue;
		}
		if (client->sess.sessionTeam != TEAM_SPECTATOR) {
			continue;
		}
// JBravo: make clients that are following this one stop following.
// JBravo: Moved the code to move followers over to MakeSpectator.
		if (g_gametype.integer != GT_TEAMPLAY) {
			Cmd_Score_f(g_entities + i);
		}
	}

	self->takedamage = qtrue;	// can still be gibbed
	self->s.weapon = WP_NONE;
	self->s.powerups = 0;

	// Elder: HC smoke
	if (meansOfDeath == MOD_HANDCANNON && self->client->damage_knockback > RQ3_HANDCANNON_KICK * 4) {
		self->client->ps.eFlags |= EF_HANDCANNON_SMOKED;
	}

	self->r.contents = CONTENTS_CORPSE;
	self->s.angles[0] = 0;
	self->s.angles[2] = 0;

	LookAtKiller(self, inflictor, attacker);
	VectorCopy(self->s.angles, self->client->ps.viewangles);

	self->s.loopSound = 0;
	self->r.maxs[2] = -8;

	// don't allow respawn until the death anim is done
	// g_forcerespawn may force spawning at some later time
	// JBravo: we dont want automatic respawning of players in teamplay
	if (g_gametype.integer == GT_TEAMPLAY) {
		self->client->respawnTime = level.time + 1000;
	} else {
		self->client->respawnTime = level.time + 1700;
	}
	// JBravo: set the time of death for CTB
	if (g_gametype.integer == GT_CTF) {
		self->client->time_of_death = level.time;
	}
	// remove powerups
	memset(self->client->ps.powerups, 0, sizeof(self->client->ps.powerups));

	// JBravo: AQ style Sniper and HC gibbing
	if (g_RQ3_gib.integer > 0) {
		if (meansOfDeath == MOD_SNIPER && hurt == LOC_HDAM) {
			if (g_RQ3_gib.integer < 3) {
				// NiceAss: beheading =D
				self->client->ps.eFlags |= EF_HEADLESS;
				GibEntity_Headshot(self, killer);
			} else {
				//GibEntity (self, killer);
				G_TempEntity(self->r.currentOrigin, EV_GIB_PLAYER);
				self->client->gibbed = qtrue;
				trap_UnlinkEntity(self);
			}
		} else if (meansOfDeath == MOD_HANDCANNON && g_RQ3_gib.integer > 1 && self->health <= -15) {
			self->client->noHead = qfalse;
			//GibEntity (self, killer);
			G_TempEntity(self->r.currentOrigin, EV_GIB_PLAYER);
			self->client->gibbed = qtrue;
			trap_UnlinkEntity(self);
		}
	}
	// never gib in a nodrop
	if (g_RQ3_gib.integer > 3 && !self->client->gibbed
	    && (self->health <= GIB_HEALTH && !(contents & CONTENTS_NODROP) && g_blood.integer)) {
		// gib death
		GibEntity(self, killer);
	} else if (meansOfDeath == MOD_SUICIDE) {
		G_AddEvent(self, EV_GIB_PLAYER, killer);
		self->takedamage = qfalse;
		self->s.eType = ET_INVISIBLE;
		self->r.contents = 0;
	} else if (self->client->gibbed) {
		self->client->gibbed = qtrue;	// JBravo:  Basicly do nothing
	} else {
		// normal death
		static int i;

		switch (i) {
		case 0:
			anim = BOTH_DEATH1;
			break;
		case 1:
			anim = BOTH_DEATH2;
			break;
		case 2:
		default:
			anim = BOTH_DEATH3;
			break;
		}

		// for the no-blood option, we need to prevent the health
		// from going to gib level
		if (self->health <= GIB_HEALTH) {
			self->health = GIB_HEALTH + 1;
		}

		self->client->ps.legsAnim = ((self->client->ps.legsAnim & ANIM_TOGGLEBIT) ^ ANIM_TOGGLEBIT) | anim;
		self->client->ps.torsoAnim = ((self->client->ps.torsoAnim & ANIM_TOGGLEBIT) ^ ANIM_TOGGLEBIT) | anim;

		// Elder: only do death sounds if not hit in the head
		if ((level.time - self->client->headShotTime > 400) && !self->client->gibbed)
			G_AddEvent(self, EV_DEATH1 + i, killer);

		// the body can still be gibbed
		self->die = body_die;

		// globally cycle through the different death animations
		i = (i + 1) % 3;
	}

	// JBravo: lets not relink players that have been gibbed here.
	if (!self->client->gibbed)
		trap_LinkEntity(self);
}

/*
================
CheckArmor
================
*/
int CheckArmor(gentity_t * ent, int damage, int dflags)
{
	gclient_t *client;
	int save;
	int count;

	if (!damage)
		return 0;

	client = ent->client;

	if (!client)
		return 0;

	if (dflags & DAMAGE_NO_ARMOR)
		return 0;

	// armor
	count = client->ps.stats[STAT_ARMOR];
	save = ceil(damage * ARMOR_PROTECTION);
	if (save >= count)
		save = count;

	if (!save)
		return 0;

	client->ps.stats[STAT_ARMOR] -= save;

	return save;
}

/*

============

G_LocationDamage
Added by Duffman
============

*/
/*Blaze: incorporated into the G_Damage function
int G_LocationDamage(vec3_t point, gentity_t* targ, gentity_t* attacker, int take) {

       vec3_t bulletPath;

       vec3_t bulletAngle;

       int clientHeight;
       int clientFeetZ;
       int clientRotation;
       int bulletHeight;
       int bulletRotation;     // Degrees rotation around client.

                               // used to check Back of head vs. Face

       int impactRotation;

       // First things first.  If we're not damaging them, why are we here?

       if (!take)
               return 0;

       // Point[2] is the REAL world Z. We want Z relative to the clients feet

       // Where the feet are at [real Z]
       clientFeetZ  = targ->r.currentOrigin[2] + targ->r.mins[2];
       // How tall the client is [Relative Z]
       clientHeight = targ->r.maxs[2] - targ->r.mins[2];
       // Where the bullet struck [Relative Z]
       bulletHeight = point[2] - clientFeetZ;

       // Get a vector aiming from the client to the bullet hit
       VectorSubtract(targ->r.currentOrigin, point, bulletPath);
       // Convert it into PITCH, ROLL, YAW
       vectoangles(bulletPath, bulletAngle);

       clientRotation = targ->client->ps.viewangles[YAW];
       bulletRotation = bulletAngle[YAW];

       impactRotation = abs(clientRotation-bulletRotation);

       impactRotation += 45; // just to make it easier to work with
       impactRotation = impactRotation % 360; // Keep it in the 0-359 range

       if (impactRotation < 90)
               targ->client->lasthurt_location = LOCATION_BACK;
       else if (impactRotation < 180)
               targ->client->lasthurt_location = LOCATION_RIGHT;
       else if (impactRotation < 270)
               targ->client->lasthurt_location = LOCATION_FRONT;
       else if (impactRotation < 360)
               targ->client->lasthurt_location = LOCATION_LEFT;
       else
               targ->client->lasthurt_location = LOCATION_NONE;

       // The upper body never changes height, just distance from the feet
               if (bulletHeight > clientHeight - 2)
                       targ->client->lasthurt_location |= LOCATION_HEAD;
               else if (bulletHeight > clientHeight - 8)
                       targ->client->lasthurt_location |= LOCATION_FACE;
               else if (bulletHeight > clientHeight - 10)
                       targ->client->lasthurt_location |= LOCATION_SHOULDER;
               else if (bulletHeight > clientHeight - 16)
                       targ->client->lasthurt_location |= LOCATION_CHEST;
               else if (bulletHeight > clientHeight - 26)
                       targ->client->lasthurt_location |= LOCATION_STOMACH;
               else if (bulletHeight > clientHeight - 29)
                       targ->client->lasthurt_location |= LOCATION_GROIN;
               //else if (bulletHeight < 4)
                //       targ->client->lasthurt_location |= LOCATION_FOOT;
               else
                       // The leg is the only thing that changes size when you duck,
                       // so we check for every other parts RELATIVE location, and
                       // whats left over must be the leg.
                       targ->client->lasthurt_location |= LOCATION_LEG;

               G_Printf("In loc damage: %d incomming\n",take);
               // Check the location ignoring the rotation info
               switch ( targ->client->lasthurt_location &
                               ~(LOCATION_BACK | LOCATION_LEFT | LOCATION_RIGHT | LOCATION_FRONT) )
               {
               case (LOCATION_HEAD):
				   {   trap_SendServerCommand( attacker-g_entities, va("print \"You hit %s^7 in the head.\n\"", targ->client->pers.netname));
					   trap_SendServerCommand( targ-g_entities, va("print \"Head Damage.\n\""));
				       take *= 1.8; //+ 1;
					   break;
				   }
			   case	(LOCATION_FACE):
				   {   trap_SendServerCommand( attacker-g_entities, va("print \"You hit %s^7 in the head.\n\"", targ->client->pers.netname));
					   trap_SendServerCommand( targ-g_entities, va("print \"Head Damage.\n\""));
				       take *= 1.8; //+ 1;
                       break;
				   }
               case (LOCATION_SHOULDER):
			       {   trap_SendServerCommand( attacker-g_entities, va("print \"You hit %s^7 in the chest.\n\"", targ->client->pers.netname));
					   trap_SendServerCommand( targ-g_entities, va("print \"Chest Damage.\n\""));
				       take *= 0.65;
                       break;
				   }
			   case (LOCATION_CHEST):
                   {   trap_SendServerCommand( attacker-g_entities, va("print \"You hit %s^7 in the chest.\n\"", targ->client->pers.netname));
					   trap_SendServerCommand( targ-g_entities, va("print \"Chest Damage.\n\""));
				       take *= 0.65;
                       break;
				   }
               case (LOCATION_STOMACH):
				   {   trap_SendServerCommand( attacker-g_entities, va("print \"You hit %s^7 in the stomac.\n\"", targ->client->pers.netname));
					   trap_SendServerCommand( targ-g_entities, va("print \"Stomach Damage.\n\""));
				       take *= 0.4;
                       break;
				   }
			   case (LOCATION_GROIN):
				   {   trap_SendServerCommand( attacker-g_entities, va("print \"You hit %s^7 in the stomac.\n\"", targ->client->pers.netname));
					   trap_SendServerCommand( targ-g_entities, va("print \"Stomach Damage.\n\""));
				       take *= 0.4;
                       break;
				   }
               case (LOCATION_LEG):
			       {   trap_SendServerCommand( attacker-g_entities, va("print \"You hit %s^7 in the leg.\n\"", targ->client->pers.netname));
					   trap_SendServerCommand( targ-g_entities, va("print \"Leg Damage.\n\""));
				       take *= 0.25;
                       break;
				   }
			   case (LOCATION_FOOT):
                   {   trap_SendServerCommand( attacker-g_entities, va("print \"You hit %s^0 in the leg.\n\"", targ->client->pers.netname));
					   trap_SendServerCommand( targ-g_entities, va("print \"Leg Damage.\n\""));
				       take *= 0.25;
                       break;
				   }

               }
		G_Printf("In loc damage: %d outgoing\n",take);
       return take;

}
*/
// End Duffman
/*
================
RaySphereIntersections
================
*/
int RaySphereIntersections(vec3_t origin, float radius, vec3_t point, vec3_t dir, vec3_t intersections[2])
{
	float b, c, d, t;

	//      | origin - (point + t * dir) | = radius
	//      a = dir[0]^2 + dir[1]^2 + dir[2]^2;
	//      b = 2 * (dir[0] * (point[0] - origin[0]) + dir[1] * (point[1] - origin[1]) + dir[2] * (point[2] - origin[2]));
	//      c = (point[0] - origin[0])^2 + (point[1] - origin[1])^2 + (point[2] - origin[2])^2 - radius^2;

	// normalize dir so a = 1
	VectorNormalize(dir);
	b = 2 * (dir[0] * (point[0] - origin[0]) + dir[1] * (point[1] - origin[1]) + dir[2] * (point[2] - origin[2]));
	c = (point[0] - origin[0]) * (point[0] - origin[0]) +
	    (point[1] - origin[1]) * (point[1] - origin[1]) +
	    (point[2] - origin[2]) * (point[2] - origin[2]) - radius * radius;

	d = b * b - 4 * c;
	if (d > 0) {
		t = (-b + sqrt(d)) / 2;
		VectorMA(point, t, dir, intersections[0]);
		t = (-b - sqrt(d)) / 2;
		VectorMA(point, t, dir, intersections[1]);
		return 2;
	} else if (d == 0) {
		t = (-b) / 2;
		VectorMA(point, t, dir, intersections[0]);
		return 1;
	}
	return 0;
}

/*
============
G_Damage

targ		entity that is being damaged
inflictor	entity that is causing the damage
attacker	entity that caused the inflictor to damage targ
	example: targ=monster, inflictor=rocket, attacker=player

dir			direction of the attack for knockback
point		point at which the damage is being inflicted, used for headshots
damage		amount of damage being inflicted
knockback	force to be applied against targ as a result of the damage

inflictor, attacker, dir, and point can be NULL for environmental effects

dflags		these flags are used to control how T_Damage works
	DAMAGE_RADIUS			damage was indirect (from a nearby explosion)
	DAMAGE_NO_ARMOR			armor does not protect from this damage
	DAMAGE_NO_KNOCKBACK		do not affect velocity, just view angles
	DAMAGE_NO_PROTECTION	kills godmode, armor, everything
============
*/

void VerifyHeadShot(vec3_t point, vec3_t dir, float height, vec3_t newpoint)
{
	vec3_t normdir, normdir2;

	VectorNormalize2(dir, normdir);
	VectorScale(normdir, height, normdir2);
	VectorAdd(point, normdir2, newpoint);
}

#define LEG_DAMAGE (height/2.2) - abs(targ->r.mins[2]) - 3  // -1.545455
#define STOMACH_DAMAGE (height/1.8) - abs(targ->r.mins[2])  // 7.111111
#define CHEST_DAMAGE (height/1.4) - abs(targ->r.mins[2])    // 16.000000
#define HEAD_HEIGHT 12.0

void G_Damage(gentity_t * targ, gentity_t * inflictor, gentity_t * attacker,
	      vec3_t dir, vec3_t point, int damage, int dflags, int mod)
{
	gclient_t *client;
	gentity_t *tent;
	int take, save, asave, knockback;
	int bleeding = 0, instant_dam = 1, height;
	float z_rel, targ_maxs2, from_top;
	vec3_t line, new_point;
	vec_t dist;

	if (!targ->takedamage) {
		return;
	}
		
	if (g_gametype.integer == GT_TEAMPLAY && level.lights_camera_action) {
		return;		// JBravo: No dmg during LCA
	}
	// NiceAss: Fixed pointer bug causing DLLs to crash
	// JBravo: FF control
	if (targ != attacker && attacker && targ && targ->client && attacker->client &&
	    targ->client->sess.sessionTeam == attacker->client->sess.sessionTeam &&
	    ((g_gametype.integer == GT_TEAMPLAY && !g_friendlyFire.integer && level.team_round_going) ||
	     (g_gametype.integer == GT_CTF && !g_friendlyFire.integer)))
		return;

	// the intermission has allready been qualified for, so don't
	// allow any extra scoring
	if (level.intermissionQueued) {
		return;
	}
	// Elder: respawn protection -- only for gunfire though!
	// No safety from falling!
	// NiceAss: Or TELEFAGS!
	if (targ->client && inflictor &&
	    level.time - targ->client->respawnTime < g_RQ3_respawnProtectTime.integer * 1000 && mod != MOD_TELEFRAG)
		return;

	if (!inflictor) {
		inflictor = &g_entities[ENTITYNUM_WORLD];
	}

	if (!attacker) {
		attacker = &g_entities[ENTITYNUM_WORLD];
	}

	/* old code
	   if (targ->s.eType == ET_MOVER && targ->health <= 0) {
	   //Makro - added
	   if (targ->use) targ->use(targ, inflictor, attacker);
	   return;
	   } */

	// Makro - we should change some more stuff in here
	// shootable doors / buttons don't actually have any health
	// Makro - they do now !
	if (targ->s.eType == ET_MOVER) {
		targ->health -= damage;
		if (targ->health <= 0) {
			if (targ->use
			    && (targ->moverState == MOVER_POS1 || targ->moverState == ROTATOR_POS1
				|| (targ->spawnflags & 8))) {
				targ->use(targ, inflictor, attacker);
			}
			if (targ->wait < 0) {
				targ->takedamage = qfalse;
			}
			targ->health = targ->health_saved;
		}
		return;
	}
	//Elder: from action source
	// damage reduction for shotgun and mk23/akimbo
	// if far away, reduce it to original action levels
	//Note: doesn't handle shots on non-clients (e.g. breakables)
	if (targ->client && inflictor->client) {
		if (mod == MOD_M3) {
			VectorSubtract(targ->client->ps.origin, inflictor->client->ps.origin, line);
			dist = VectorLength(line);
			if (dist > 450.0) {
				damage -= 2;
			}
		} else if (mod == MOD_PISTOL || mod == MOD_AKIMBO) {
			VectorSubtract(targ->client->ps.origin, inflictor->client->ps.origin, line);
			dist = VectorLength(line);
			if (dist > 600.0 && dist < 1400.0) {
				damage = (int) (damage * 2 / 3);
			}
			//Elder: added >= ... 1400.0 is a magic number for perfect shots if not in :)
			else if (dist >= 1400.0) {
				damage = (int) (damage * 1 / 2);
			}
		}
	}
	//Blaze: If we shot a breakable item subtract the damage from its health and try to break it
	if (targ->s.eType == ET_BREAKABLE) {
		if (!targ->unbreakable) {
			targ->health -= damage;
		}
		if (targ->exploded == qfalse)
			G_BreakGlass(targ, inflictor, attacker, point, mod, damage);
		return;
	}

	client = targ->client;

	if (client) {
		if (client->noclip) {
			return;
		}
	}

	if (!dir) {
		dflags |= DAMAGE_NO_KNOCKBACK;
	} else {
		VectorNormalize(dir);
	}

	if (targ->flags & FL_NO_KNOCKBACK) {
		knockback = 0;
	} else if (dflags & DAMAGE_NO_KNOCKBACK) {
		knockback = 0;
	} else {
		//Elder: select knockback
		switch (mod) {
		case MOD_HANDCANNON:
			knockback = RQ3_HANDCANNON_KICK;
			break;
		case MOD_M3:
			knockback = RQ3_M3_KICK;
			break;
		case MOD_M4:
			knockback = RQ3_M4_KICK;
			break;
		case MOD_MP5:
			knockback = RQ3_MP5_KICK;
			break;
		case MOD_SNIPER:
			knockback = RQ3_SNIPER_KICK;
			break;
		case MOD_PISTOL:
			knockback = RQ3_PISTOL_KICK;
			break;
		case MOD_AKIMBO:
			knockback = RQ3_AKIMBO_KICK;
			break;
		case MOD_GRENADE_SPLASH:
		case MOD_GRENADE:
			knockback = (int) (0.75 * damage);
			break;
		case MOD_KNIFE:
			knockback = RQ3_KNIFE_KICK;
			break;
		case MOD_KNIFE_THROWN:
			knockback = RQ3_THROW_KICK;
			break;
		case MOD_KICK:
			//Elder: do some calculation here?
			knockback = 400;
			break;
		case MOD_TRIGGER_HURT:
			knockback = (int) (0.75 * damage);
			break;
		default:
			G_Printf("G_Damage: Received unknown MOD - using default knockback\n");
			knockback = 50;
			break;
		}
	}

	// NiceAss: Make sure it hit the player before doing this stuff.
	// This was added when the possibility of missing was added from spherical head detection.
	// We don't want someone flying back from a sniper to the head when it actually missed!
	// Hal: Make sure we have valid pointers before accessing them
	if ((dir != NULL) && (point != NULL)) {
		// figure momentum add, even if the damage won't be taken
		if (knockback && targ->client) {
			vec3_t kvel, flydir;
			float mass;

			if (mod != MOD_FALLING) {
				VectorCopy(dir, flydir);
				// NiceAss: Although AQ2 has this, it was being much more
				// severe in RQ3 than AQ2. Removed!
				//flydir[2] += 0.4f;
			}

			mass = 200;

			if (targ->client && attacker == targ)
				VectorScale(flydir, 1600.0 * (float) knockback / mass, kvel);
			else
				VectorScale(flydir, 500.0 * (float) knockback / mass, kvel);
			VectorAdd(targ->client->ps.velocity, kvel, targ->client->ps.velocity);

			// set the timer so that the other client can't cancel
			// out the movement immediately
			if (!targ->client->ps.pm_time) {
				int t;

				t = knockback * 2;
				if (t < 50) {
					t = 50;
				}
				if (t > 200) {
					t = 200;
				}
				targ->client->ps.pm_time = t;
				targ->client->ps.pm_flags |= PMF_TIME_KNOCKBACK;
			}
		}
		// NiceAss: This was moved too
		// add to the attacker's hit counter (if the target isn't a general entity like a prox mine)
		//Makro - added check; q3 crashed sometimes with .dlls
		if ((attacker != NULL) && (client != NULL) && (targ != NULL)) {
			if (attacker->client && targ != attacker && targ->health > 0 &&
			    targ->s.eType != ET_MISSILE && targ->s.eType != ET_GENERAL) {
				if (OnSameTeam(targ, attacker)) {
					attacker->client->ps.persistant[PERS_HITS]--;
				} else {
					attacker->client->ps.persistant[PERS_HITS]++;
				}
				attacker->client->ps.persistant[PERS_ATTACKEE_ARMOR] =
				    (targ->health << 8) | (client->ps.stats[STAT_ARMOR]);
			}
		}
	}
	// check for completely getting out of the damage
	if (!(dflags & DAMAGE_NO_PROTECTION)) {

		// if TF_NO_FRIENDLY_FIRE is set, don't do damage to the target
		// if the attacker was on the same team
		if (targ != attacker && OnSameTeam(targ, attacker)) {
// JBravo: more FF tweaks
			if (g_gametype.integer == GT_TEAMPLAY && g_friendlyFire.integer == 2 && level.team_round_going) {
				return;
			}
			if (g_gametype.integer == GT_CTF && g_friendlyFire.integer == 2)
				return;
			if ((g_gametype.integer == GT_TEAMPLAY && level.team_round_going)
			    || g_gametype.integer == GT_CTF)
				Add_TeamWound(attacker, targ, mod);
		}
		// check for godmode
		if (targ->flags & FL_GODMODE) {
			return;
		}
	}
	//Blaze: Add falling damage for limping
	if (mod == MOD_FALLING)
		targ->client->ps.stats[STAT_RQ3] |= RQ3_LEGDAMAGE;

	if (damage < 1) {
		damage = 1;
	}
	take = damage;
	save = 0;

	// save some from armor
	asave = CheckArmor(targ, take, dflags);
	take -= asave;

	if (g_debugDamage.integer) {
		G_Printf("%i: client:%i health:%i damage:%i armor:%i\n", level.time, targ->s.number,
			 targ->health, take, asave);
	}
	// See if it's the player hurting the emeny flag carrier
	if (g_gametype.integer == GT_CTF) {
		Team_CheckHurtCarrier(targ, attacker);
	}
	// aasimon: start calculations for hit location determination
	if (targ->client) {
		// set the last client who damaged the target
		targ->client->lasthurt_client = attacker->s.number;
		targ->client->lasthurt_mod = mod;
		// Modify the damage for location damage

		if (point && targ && targ->health > 0 && attacker && take) {
			// First things first.  If we're not damaging them, why are we here?
			// Elder: removed M3, handcannon, and grenades from location damage code

			if (take && (mod == MOD_M3 || mod == MOD_HANDCANNON ||
				     mod == MOD_GRENADE || mod == MOD_GRENADE_SPLASH || mod == MOD_TRIGGER_HURT)) {
				bleeding = 1;
				instant_dam = 0;

				//No location damage
				targ->client->lasthurt_location = LOCATION_NONE | LOCATION_FRONT;
				//Elder: we'll use the shotgun damage report model from AQ2
				if (mod == MOD_HANDCANNON || mod == MOD_M3) {
					//Elder: do shotgun report like AQ2
					int playernum = targ - g_entities;

					if (playernum >= 0 && playernum < MAX_CLIENTS)
						tookShellHit[playernum] = 1;
				} else {
					// Grenade stuff - don't print if you hurt yourself
					// We could re-use the shotgun report for grenades
					if (targ != attacker)
						trap_SendServerCommand(attacker - g_entities,
								       va("print \"You hit %s^7\n\"",
									  targ->client->pers.netname));
				}
			} else if (take && (mod == MOD_PISTOL || mod == MOD_M4 ||
					    mod == MOD_SNIPER || mod == MOD_MP5 || mod == MOD_AKIMBO ||
					    mod == MOD_KNIFE || mod == MOD_KNIFE_THROWN)) {

				bleeding = 1;
				instant_dam = 0;

				// JBravo: calulate where the bullet hit
				targ->client->lasthurt_location = 0;
				targ_maxs2 = targ->r.maxs[2];
				height = abs(targ->r.mins[2]) + targ_maxs2;
				z_rel = point[2] - targ->r.currentOrigin[2];
				from_top = targ_maxs2 - z_rel;

				//G_Printf("z_rel = %f, height = %d, from_top = %f\n", z_rel, height, from_top);

				if (from_top < 2 * HEAD_HEIGHT) {
					VerifyHeadShot (point, dir, HEAD_HEIGHT, new_point);
					VectorSubtract (new_point, targ->r.currentOrigin, new_point);
					if ((targ_maxs2 - new_point[2]) < HEAD_HEIGHT
							&& (abs(new_point[1])) < HEAD_HEIGHT*.8
							&& (abs(new_point[0])) < HEAD_HEIGHT*.8) {
						targ->client->lasthurt_location = LOCATION_HEAD;
					}
				}
				if (z_rel < LEG_DAMAGE) {
					targ->client->lasthurt_location = LOCATION_LEG;
				} else if (z_rel < STOMACH_DAMAGE) {
					targ->client->lasthurt_location = LOCATION_STOMACH;
				} else if (targ->client->lasthurt_location == 0){
					targ->client->lasthurt_location = LOCATION_CHEST;
				}

				switch (targ->client->lasthurt_location) {
				case LOCATION_HEAD:
					if (attacker->client && ((g_gametype.integer == GT_TEAMPLAY && level.team_round_going) || g_gametype.integer != GT_TEAMPLAY))
						attacker->client->pers.records[REC_HEADSHOTS]++;
					//save headshot time for player_die
					targ->client->headShotTime = level.time;

					//Elder: reusing line so we don't have to declare more variables
					line[0] = line[1] = 0;
					line[2] = 20;
					trap_SendServerCommand(attacker - g_entities,
							       va("print \"You hit %s^7 in the head.\n\"",
								  targ->client->pers.netname));
					trap_SendServerCommand(targ - g_entities, va("print \"Head Damage.\n\""));

					//Setup headshot spray and sound
					//Only do if not knife or SSG -- SSG has its own trail of blood
					if (mod != MOD_SNIPER && mod != MOD_KNIFE && mod != MOD_KNIFE_THROWN) {
						VectorAdd(targ->s.pos.trBase, line, line);
						tent = G_TempEntity(line, EV_HEADSHOT);
						tent->s.eventParm = DirToByte(dir);
						tent->s.otherEntityNum = targ->s.clientNum;
					}
					take *= 1.8;	//+ 1;
					break;
				case LOCATION_CHEST:
					if (attacker->client && ((g_gametype.integer == GT_TEAMPLAY && level.team_round_going) || g_gametype.integer != GT_TEAMPLAY))
						attacker->client->pers.records[REC_CHESTSHOTS]++;
					// Vest stuff - is the knife supposed to be affected?
					// NiceAss: Added mod != MOD_KNIFE_THROWN so kevlar doesn't help against thrown knives
					// JBravo: added mod != MOD_KNIFE so kevlar doesn't help against slashing knives either
					if (bg_itemlist[targ->client->ps.stats[STAT_HOLDABLE_ITEM]].giTag == HI_KEVLAR &&
					    mod != MOD_KNIFE_THROWN && mod != MOD_KNIFE) {
						targ->client->kevlarHit = qtrue;
						if (attacker->client->ps.weapon == WP_SSG3000) {
							trap_SendServerCommand(attacker - g_entities,
									va("print \"%s^7 has a Kevlar Vest, too bad you have AP rounds...\n\"",
									targ->client->pers.netname));
							trap_SendServerCommand(targ - g_entities,
									va("print \"Kevlar Vest absorbed some of %s^7's AP sniper round\n\"",
									attacker->client->pers.netname));
							take = take * 0.325;
						} else {
							trap_SendServerCommand(attacker - g_entities,
									va("print \"%s^7 has a Kevlar Vest - AIM FOR THE HEAD!\n\"",
									targ->client->pers.netname));
							trap_SendServerCommand(targ - g_entities,
									va("print \"Kevlar Vest absorbed most of %s^7's shot\n\"",
									attacker->client->pers.netname));
							take = take / 10;
							instant_dam = 1;
							bleeding = 0;
						}
						//Kevlar sound
						tent = G_TempEntity(targ->s.pos.trBase, EV_BULLET_HIT_KEVLAR);
						tent->s.eventParm = DirToByte(dir);
					} else {
						trap_SendServerCommand(attacker - g_entities,
								       va("print \"You hit %s^7 in the chest.\n\"",
									  targ->client->pers.netname));
						trap_SendServerCommand(targ - g_entities,
								       va("print \"Chest Damage.\n\""));
						take *= 0.65;
					}
					break;
				case LOCATION_STOMACH:
					if (attacker->client && ((g_gametype.integer == GT_TEAMPLAY && level.team_round_going) || g_gametype.integer != GT_TEAMPLAY))
						attacker->client->pers.records[REC_STOMACHSHOTS]++;
					trap_SendServerCommand(attacker - g_entities,
							       va("print \"You hit %s^7 in the stomach.\n\"",
								  targ->client->pers.netname));
					trap_SendServerCommand(targ - g_entities, va("print \"Stomach Damage.\n\""));
					take *= 0.4;
					if (attacker->client && attacker->client->ps.weapon == WP_SSG3000
					    && g_RQ3_gib.integer >= 1) {
						G_TempEntity(targ->r.currentOrigin, EV_GIB_PLAYER_STOMACH);
					}
					break;
				case LOCATION_LEG:
					if (attacker->client && ((g_gametype.integer == GT_TEAMPLAY && level.team_round_going) || g_gametype.integer != GT_TEAMPLAY))
						attacker->client->pers.records[REC_LEGSHOTS]++;
					trap_SendServerCommand(attacker - g_entities,
							       va("print \"You hit %s^7 in the leg.\n\"",
								  targ->client->pers.netname));
					trap_SendServerCommand(targ - g_entities, va("print \"Leg Damage.\n\""));
					targ->client->ps.stats[STAT_RQ3] |= RQ3_LEGDAMAGE;
					take *= 0.25;
					break;
				}
			}
		} else
			targ->client->lasthurt_location = LOCATION_NONE;
	}
	// add to the damage inflicted on a player this frame
	// the total will be turned into screen blends and view angle kicks
	// at the end of the frame
	if (client) {
		if (attacker) {
			client->ps.persistant[PERS_ATTACKER] = attacker->s.number;
		} else {
			client->ps.persistant[PERS_ATTACKER] = ENTITYNUM_WORLD;
		}
		client->damage_armor += asave;
		client->damage_blood += take;
		client->damage_knockback += knockback;
		if (dir) {
			VectorCopy(dir, client->damage_from);
			client->damage_fromWorld = qfalse;
		} else {
			VectorCopy(targ->r.currentOrigin, client->damage_from);
			client->damage_fromWorld = qtrue;
		}
	}
	// do the damage
	if (take) {
		// JBravo: for Damage delt tracking
		if (attacker && attacker->client && targ->health > 0 && targ->client) {
			if (mod == MOD_TELEFRAG) {
				attacker->client->ps.persistant[PERS_DAMAGE_DELT] += 100;
			} else {
				if (g_gametype.integer >= GT_TEAM) {
					if (attacker->client->sess.sessionTeam != targ->client->sess.sessionTeam)
						attacker->client->ps.persistant[PERS_DAMAGE_DELT] += take;
				} else {
					attacker->client->ps.persistant[PERS_DAMAGE_DELT] += take;
				}
			}
			//Makro - crash bug fix
			if (targ && targ->client) {
				Com_sprintf(attacker->client->last_damaged_players,
					    sizeof(attacker->client->last_damaged_players), "%s^7",
					    targ->client->pers.netname);
			}
		}
		if (instant_dam) {
			// G_Printf("(%d) instant damage\n",take);
			targ->health = targ->health - take;
		}
		if (targ->client) {
			targ->client->ps.stats[STAT_HEALTH] = targ->health;
		}

		if (targ->health <= 0) {
			if (targ->health < -999) {
				targ->health = -999;
			}
			targ->enemy = attacker;
			//Makro - crash bug fix
			if (targ->die)
				targ->die(targ, inflictor, attacker, take, mod);
			return;
		} else if (targ->pain) {
			targ->pain(targ, attacker, take);
		}
	}

	if (client) {
		if (client->lasthurt_location && bleeding) {
			// Elder: use the server FPS
			int realBleedTime;

			realBleedTime = trap_Cvar_VariableIntegerValue("sv_fps");
			if (realBleedTime <= 0)
				realBleedTime = BLEED_TIME;

			client->bleeding += take * realBleedTime;
			// Elder: Splash damage bleeding happens from the origin
			if (dflags == DAMAGE_RADIUS)
				VectorClear(targ->client->bleedloc_offset);
			else
				VectorSubtract(point, targ->r.currentOrigin, targ->client->bleedloc_offset);
		}
	}
}

/*
============
CanDamage

Returns qtrue if the inflictor can directly damage the target.  Used for
explosions and melee attacks.
============
*/
qboolean CanDamage(gentity_t * targ, vec3_t origin)
{
	vec3_t dest;
	trace_t tr;
	vec3_t midpoint;

	// use the midpoint of the bounds instead of the origin, because
	// bmodels may have their origin is 0,0,0
	VectorAdd(targ->r.absmin, targ->r.absmax, midpoint);
	VectorScale(midpoint, 0.5, midpoint);

	VectorCopy(midpoint, dest);
	trap_Trace(&tr, origin, vec3_origin, vec3_origin, dest, ENTITYNUM_NONE, MASK_SOLID);

	if (tr.fraction == 1.0 || tr.entityNum == targ->s.number)
		return qtrue;

	// this should probably check in the plane of projection,
	// rather than in world coordinate, and also include Z
	VectorCopy(midpoint, dest);
	dest[0] += 15.0;
	dest[1] += 15.0;
	trap_Trace(&tr, origin, vec3_origin, vec3_origin, dest, ENTITYNUM_NONE, MASK_SOLID);
	if (tr.fraction == 1.0)
		return qtrue;

	VectorCopy(midpoint, dest);
	dest[0] += 15.0;
	dest[1] -= 15.0;
	trap_Trace(&tr, origin, vec3_origin, vec3_origin, dest, ENTITYNUM_NONE, MASK_SOLID);
	if (tr.fraction == 1.0)
		return qtrue;

	VectorCopy(midpoint, dest);
	dest[0] -= 15.0;
	dest[1] += 15.0;
	trap_Trace(&tr, origin, vec3_origin, vec3_origin, dest, ENTITYNUM_NONE, MASK_SOLID);
	if (tr.fraction == 1.0)
		return qtrue;

	VectorCopy(midpoint, dest);
	dest[0] -= 15.0;
	dest[1] -= 15.0;
	trap_Trace(&tr, origin, vec3_origin, vec3_origin, dest, ENTITYNUM_NONE, MASK_SOLID);
	if (tr.fraction == 1.0)
		return qtrue;

	return qfalse;
}

/*
============
G_RadiusDamage

Elder: this sucker needed a lot of minor tweaks to behave like AQ2
============
*/
qboolean G_RadiusDamage(vec3_t origin, gentity_t * attacker, float damage, float radius, gentity_t * ignore, int mod)
{
	float points, dist;
	gentity_t *ent;
	int entityList[MAX_GENTITIES];
	int numListedEntities;
	vec3_t mins, maxs;
	vec3_t v;
	vec3_t dir;
	int i, e;
	qboolean hitClient = qfalse;

	if (radius < 1) {
		radius = 1;
	}

	for (i = 0; i < 3; i++) {
		mins[i] = origin[i] - radius;
		maxs[i] = origin[i] + radius;
	}

	numListedEntities = trap_EntitiesInBox(mins, maxs, entityList, MAX_GENTITIES);

	for (e = 0; e < numListedEntities; e++) {
		//Blaze: Prit out some Debug info
		if (&g_entities[entityList[e]] == NULL) G_Printf("Ln 2499\n");

		ent = &g_entities[entityList[e]];

		if (ent == ignore)
			continue;
		if (!ent->takedamage)
			continue;

		// find the distance from the edge of the bounding box
		for (i = 0; i < 3; i++) {
			if (origin[i] < ent->r.absmin[i]) {
				v[i] = ent->r.absmin[i] - origin[i];
			} else if (origin[i] > ent->r.absmax[i]) {
				v[i] = origin[i] - ent->r.absmax[i];
			} else {
				v[i] = 0;
			}
		}

		dist = VectorLength(v);
		//if ( dist >= radius ) {
		if (dist > radius) {
			continue;
		}
		//Blaze: lets use the q3 damage because it works the same for grenades, but lets breakables work better.
		// Q2 radius damage
		//points = damage - 0.5f * dist;
		// Q3 radius damage
		points = damage * (1.0 - dist / radius);

		//Elder: reduce grenade damage if crouching
		if (ent->r.maxs[2] < 20) {
			points = points * 0.5f;	// hefty reduction in damage
		}

		if (CanDamage(ent, origin)) {
			if (LogAccuracyHit(ent, attacker)) {
				hitClient = qtrue;
			}
			VectorSubtract(ent->r.currentOrigin, origin, dir);
			// push the center of mass higher than the origin so players
			// get knocked into the air more
			// dir[2] += 24;

			G_Damage(ent, NULL, attacker, dir, origin, (int) (points * 0.75f), DAMAGE_RADIUS, mod);
		}
	}

	return hitClient;
}
