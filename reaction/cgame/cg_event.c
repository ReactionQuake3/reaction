//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.55  2002/05/11 19:13:42  makro
// Sand surfaceparm
//
// Revision 1.54  2002/05/09 20:58:30  jbravo
// New Obit system and a warning cleanup in zcam
//
// Revision 1.53  2002/05/02 23:04:59  makro
// Loading screen. Jump kicks
//
// Revision 1.52  2002/04/29 06:14:57  niceass
// pressure
//
// Revision 1.51  2002/04/23 06:08:58  niceass
// pressure stuff
//
// Revision 1.50  2002/04/20 15:05:08  makro
// More footstep sounds, a few other things
//
// Revision 1.49  2002/04/06 21:43:58  makro
// New surfaceparm system
//
// Revision 1.48  2002/04/03 03:13:48  blaze
// NEW BREAKABLE CODE - will break all old breakables(wont appear in maps)
//
// Revision 1.47  2002/03/31 03:31:24  jbravo
// Compiler warning cleanups
//
// Revision 1.46  2002/03/23 05:17:42  jbravo
// Major cleanup of game -> cgame communication with LCA vars.
//
// Revision 1.45  2002/03/21 15:02:05  jbravo
// More teamname cleanups and fix for fraglines.
//
// Revision 1.44  2002/03/18 13:32:53  jbravo
// Fixed the fraglines for sniper head kills and twekaed bandaging a bit for
// testing
//
// Revision 1.43  2002/03/18 12:25:10  jbravo
// Live players dont get fraglines, except their own. Cleanups and some
// hacks to get bots to stop using knives only.
//
// Revision 1.42  2002/03/17 01:44:39  jbravo
// Fixed the "xxx died" fraglines, did some code cleanups andalmost fixed
// DM.  Only DM problem I can see is that bots are invisible.
//
// Revision 1.41  2002/03/17 00:40:23  jbravo
// Adding variable team names. g_RQ3_team1name and g_RQ3_team2name. Fixed
// Slicers fraglimit check.
//
// Revision 1.40  2002/03/14 23:54:12  jbravo
// Added a variable system from AQ. Works the same except it uses $ for %
//
// Revision 1.39  2002/03/03 22:02:15  jbravo
// Further attempts to stop "you fragged XXX" messages for spectators
//
// Revision 1.38  2002/03/02 20:16:58  jbravo
// Stopping you fragged XXX messages for spectators in followmode.
//
// Revision 1.37  2002/02/11 00:30:02  niceass
// LCA fix
//
// Revision 1.36  2002/02/10 16:26:55  jbravo
// Attempting to intergrate zcam better into rq3 and a fix for lights.wav
//
// Revision 1.35  2002/01/24 14:20:53  jbravo
// Adding func_explosive and a few new surfaceparms
//
// Revision 1.34  2002/01/14 01:19:23  niceass
// No more default 800 gravity on items - NiceAss
//
// Revision 1.33  2002/01/11 20:20:57  jbravo
// Adding TP to main branch
//
// Revision 1.32  2002/01/11 19:48:29  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.31  2001/12/31 16:28:41  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
// cg_event.c -- handle entity events at snapshot or playerstate transitions

#include "cg_local.h"
// JBravo: warning fix
void CG_BreakBreakable(centity_t *cent, int eParam, int number);

// for the voice chats
#ifdef MISSIONPACK // bk001205
#include "../../ui/menudef.h"
#endif
//==========================================================================

/*
===================
CG_PlaceString

Also called by scoreboard drawing
===================
*/
const char	*CG_PlaceString( int rank ) {
	static char	str[64];
	char	*s, *t;

	if ( rank & RANK_TIED_FLAG ) {
		rank &= ~RANK_TIED_FLAG;
		t = "Tied for ";
	} else {
		t = "";
	}

	if ( rank == 1 ) {
		s = S_COLOR_BLUE "1st" S_COLOR_WHITE;		// draw in blue
	} else if ( rank == 2 ) {
		s = S_COLOR_RED "2nd" S_COLOR_WHITE;		// draw in red
	} else if ( rank == 3 ) {
		s = S_COLOR_YELLOW "3rd" S_COLOR_WHITE;		// draw in yellow
	} else if ( rank == 11 ) {
		s = "11th";
	} else if ( rank == 12 ) {
		s = "12th";
	} else if ( rank == 13 ) {
		s = "13th";
	} else if ( rank % 10 == 1 ) {
		s = va("%ist", rank);
	} else if ( rank % 10 == 2 ) {
		s = va("%ind", rank);
	} else if ( rank % 10 == 3 ) {
		s = va("%ird", rank);
	} else {
		s = va("%ith", rank);
	}

	Com_sprintf( str, sizeof( str ), "%s%s", t, s );
	return str;
}

/*
=============
CG_Obituary
=============
*/
// JBravo: moved to game and done right ;)
/*
static void CG_Obituary( entityState_t *ent ) {
	int		mod, target, attacker;
	int		n;		//Elder: for random messages
	char		*message, *message2;
	const char	*targetInfo;
	const char	*attackerInfo;
	char		targetName[32], attackerName[32];
	gender_t	gender;
	clientInfo_t	*ci;

	target = ent->otherEntityNum;
	attacker = ent->otherEntityNum2;
	mod = ent->eventParm;

	if (target < 0 || target >= MAX_CLIENTS) {
		CG_Error("CG_Obituary: target out of range");
	}
	ci = &cgs.clientinfo[target];

	if (attacker < 0 || attacker >= MAX_CLIENTS) {
		attacker = ENTITYNUM_WORLD;
		attackerInfo = NULL;
	} else {
		attackerInfo = CG_ConfigString( CS_PLAYERS + attacker );
	}

	targetInfo = CG_ConfigString( CS_PLAYERS + target );
	if ( !targetInfo ) {
		return;
	}
	Q_strncpyz( targetName, Info_ValueForKey( targetInfo, "n" ), sizeof(targetName) - 2);
	strcat( targetName, S_COLOR_WHITE );

	message2 = "";

	// check for single client messages
	gender = ci->gender;
	switch( mod ) {
		case MOD_SUICIDE:
			message = "suicides";
			break;
		case MOD_FALLING:
			//message = "'s thoughts weren't happy enough";
			//Elder: changed
			if ( gender == GENDER_FEMALE )
				message = "plummets to her death";
			else if ( gender == GENDER_NEUTER )
				message = "plummets to its death";
			else
				message = "plummets to his death";
			break;
		case MOD_CRUSH:
			message = "was flattened";
			break;
		case MOD_WATER:
			message = "sank like a rock";
			break;
		case MOD_SLIME:
			message = "melted";
			break;
		case MOD_LAVA:
			message = "does a back flip into the lava";
			break;
		case MOD_TARGET_LASER:
			message = "saw the light";
			break;
		case MOD_TRIGGER_HURT:
			message = "was in the wrong place";
			break;
		case MOD_BLEEDING:
			message = "bleeds to death";
			break;
		default:
			message = NULL;
			break;
	}

	if (attacker == target) {
		gender = ci->gender;
		switch (mod) {
#ifdef MISSIONPACK
		case MOD_KAMIKAZE:
			message = "goes out with a bang";
			break;
#endif
		case MOD_GRENADE_SPLASH:
			if ( gender == GENDER_FEMALE )
				message = "didn't throw her grenade far enough";
			else if (gender == GENDER_NEUTER)
				message = "didn't throw its grenade far enough";
			else
				message = "didn't throw his grenade far enough";
			break;
		case MOD_ROCKET_SPLASH:
			if ( gender == GENDER_FEMALE )
				message = "blew herself up";
			else if ( gender == GENDER_NEUTER )
				message = "blew itself up";
			else
				message = "blew himself up";
			break;
		case MOD_PLASMA_SPLASH:
			if ( gender == GENDER_FEMALE )
				message = "melted herself";
			else if ( gender == GENDER_NEUTER )
				message = "melted itself";
			else
				message = "melted himself";
			break;
		case MOD_BFG_SPLASH:
			message = "should have used a smaller gun";
			break;
#ifdef MISSIONPACK
		case MOD_PROXIMITY_MINE:
			if( gender == GENDER_FEMALE ) {
				message = "found her prox mine";
			} else if ( gender == GENDER_NEUTER ) {
				message = "found it's prox mine";
			} else {
				message = "found his prox mine";
			}
			break;
#endif
		default:
			if ( gender == GENDER_FEMALE )
				message = "killed herself";
			else if ( gender == GENDER_NEUTER )
				message = "killed itself";
			else
				message = "killed himself";
			break;
		}
	}

	//Blaze: This allows for the falling damage message to pass through if someone attacked them
	if (!(attacker == ENTITYNUM_WORLD || attacker == target)) message = NULL;
	if (message) {
		CG_Printf("%s %s.\n", targetName, message);
		return;
	}

	// check for kill messages from the current clientNum
	if ( attacker == cg.snap->ps.clientNum ) {
		char	*s;

		if ( cgs.gametype < GT_TEAM ) {
			s = va("You fragged %s\n%s place with %i", targetName,
				CG_PlaceString( cg.snap->ps.persistant[PERS_RANK] + 1 ),
				cg.snap->ps.persistant[PERS_SCORE] );
		} else {
			s = va("You fragged %s", targetName );
		}
#ifdef MISSIONPACK
		if (!(cg_singlePlayerActive.integer && cg_cameraOrbit.integer)) {
			CG_CenterPrint( s, SCREEN_HEIGHT * 0.30, BIGCHAR_WIDTH );
		}
#else
// JBravo: attempting to stop these messages for spectators
		if (cg.snap->ps.persistant[PERS_TEAM] != TEAM_SPECTATOR)
			CG_CenterPrint( s, SCREEN_HEIGHT * 0.25, (BIGCHAR_WIDTH+SMALLCHAR_WIDTH)*.5 );
#endif

		// print the text message as well
	}

	// check for double client messages
	if ( !attackerInfo ) {
		attacker = ENTITYNUM_WORLD;
		strcpy( attackerName, "noname" );
	} else {
		Q_strncpyz( attackerName, Info_ValueForKey( attackerInfo, "n" ), sizeof(attackerName) - 2);
		strcat( attackerName, S_COLOR_WHITE );
		// check for kill messages about the current clientNum
		if ( target == cg.snap->ps.clientNum ) {
			Q_strncpyz( cg.killerName, attackerName, sizeof( cg.killerName ) );
		}
	}
	if ( attacker != ENTITYNUM_WORLD ) {
		switch (mod) {
		case MOD_GRAPPLE:
			message = "was caught by";
			break;
		case MOD_GAUNTLET:
			message = "was pummeled by";
			break;
		case MOD_MACHINEGUN:
			message = "was machinegunned by";
			break;
		case MOD_SHOTGUN:
			message = "was gunned down by";
			break;
		case MOD_GRENADE:
			message = "ate";
			message2 = "'s grenade";
			break;
		case MOD_GRENADE_SPLASH:
			message = "was shredded by";
			message2 = "'s shrapnel";
			break;
		case MOD_ROCKET:
			message = "ate";
			message2 = "'s rocket";
			break;
		case MOD_ROCKET_SPLASH:
			message = "almost dodged";
			message2 = "'s rocket";
			break;
		case MOD_PLASMA:
			message = "was melted by";
			message2 = "'s plasmagun";
			break;
		case MOD_PLASMA_SPLASH:
			message = "was melted by";
			message2 = "'s plasmagun";
			break;
		case MOD_RAILGUN:
			message = "was railed by";
			break;
		case MOD_LIGHTNING:
			message = "was electrocuted by";
			break;
		case MOD_BFG:
		case MOD_BFG_SPLASH:
			message = "was blasted by";
			message2 = "'s BFG";
			break;
#ifdef MISSIONPACK
		case MOD_NAIL:
			message = "was nailed by";
			break;
		case MOD_CHAINGUN:
			message = "got lead poisoning from";
			message2 = "'s Chaingun";
			break;
		case MOD_PROXIMITY_MINE:
			message = "was too close to";
			message2 = "'s Prox Mine";
			break;
		case MOD_KAMIKAZE:
			message = "falls to";
			message2 = "'s Kamikaze blast";
			break;
		case MOD_JUICED:
			message = "was juiced by";
			break;
#endif
		//Elder: added
		case MOD_FALLING:
			message = "was taught how to fly by";
			break;
		case MOD_PISTOL:
			message = "was shot by";
			message2 = "'s Mark 23 Pistol";
			break;
		case MOD_M4:
			message = "was shot by";
			message2 = "'s M4 Assault Rifle";
			break;
		case MOD_MP5:
			message = "was shot by";
			message2 = "'s MP5/10 Submachinegun";
			break;
		case MOD_AKIMBO:
			message = "was shot by";
			message2 = "'s pair of Mark 23 Pistols";
			break;
		case MOD_M3:
			n = rand() % 2 + 1;
			if (n == 1) {
				message = "accepts";
				message2 = "'s M3 Super 90 Assault Shotgun in hole-y matrimony";
			} else {
				message = "is full of buckshot from";
				message2 = "'s M3 Super 90 Assault Shotgun";
			}
			break;
		case MOD_HANDCANNON:
			n = rand() % 2 + 1;
			if (n == 1) {
				message = "ate";
				message2 = "'s sawed-off 12 gauge";
			} else {
				message = "is full of buckshot from";
				message2 = "'s sawed off shotgun";
			}
			break;
		case MOD_SNIPER:
			message = "was sniped by";
			break;
		case MOD_KICK:
			n = rand() % 3 + 1;
			if (n == 1) {
				if (gender == GENDER_NEUTER)
					message = "got its ass kicked by";
				else if (gender == GENDER_FEMALE)
					message = "got her ass kicked by";
				else
					message = "got his ass kicked by";
			} else if (n == 2) {
				message = "couldn't remove";
				if (gender == GENDER_NEUTER)
					message2 = "'s boot from its ass";
				else if (gender == GENDER_FEMALE)
					message2 = "'s boot from her ass";
				else
					message2 = "'s boot from his ass";
			} else {
				if (gender == GENDER_NEUTER)
					message = "had a Bruce Lee put on it by";
				else if (gender == GENDER_FEMALE)
					message = "had a Bruce Lee put on her by";
				else
					message = "had a Bruce Lee put on him by";
				message2 = ", with a quickness";
			}
			break;
		case MOD_KNIFE:
			message = "was slashed apart by";
			message2 = "'s Combat Knife";
			break;
		case MOD_KNIFE_THROWN:
			message = " was hit by";
			message2 = "'s flying Combat Knife";
			break;
		case MOD_TELEFRAG:
			message = "tried to invade";
			message2 = "'s personal space";
			break;
		default:
			message = "was killed by";
			break;
		}

// JBravo: live players dont get fraglines.
		if (message) {
			if (cg.snap->ps.clientNum == target || cg.snap->ps.clientNum == attacker ||
				cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR ||
				cg_RQ3_team_round_going.integer == 0)
				CG_Printf( "%s %s %s%s\n",
					targetName, message, attackerName, message2);
			return;
		}
	}

	// we don't know what it was
	CG_Printf( "(CG_Obituary)%s died and the mod is %i. Tell this to JB\n", targetName, mod );
}
*/

/*
=============
Added by Elder
Slim version of main obit

CG_Obituary_Head
=============
*/
/*
static void CG_Obituary_Head( entityState_t *ent ) {
	int		mod, target, attacker;
	char		*message, *message2;
	const char	*targetInfo, *attackerInfo;
	char		targetName[32], attackerName[32];
	gender_t	gender = GENDER_MALE;
	clientInfo_t	*ci;

	target = ent->otherEntityNum;
	attacker = ent->otherEntityNum2;
	mod = ent->eventParm;

	if (target < 0 || target >= MAX_CLIENTS) {
		CG_Error("CG_Obituary: target out of range");
	}
	ci = &cgs.clientinfo[target];

	if (attacker < 0 || attacker >= MAX_CLIENTS) {
		attacker = ENTITYNUM_WORLD;
		attackerInfo = NULL;
	} else {
		attackerInfo = CG_ConfigString(CS_PLAYERS + attacker);
	}

	targetInfo = CG_ConfigString(CS_PLAYERS + target);
	if (!targetInfo) {
		return;
	}
	Q_strncpyz(targetName, Info_ValueForKey(targetInfo, "n"), sizeof(targetName) - 2);
	strcat(targetName, S_COLOR_WHITE);

	message2 = "";

	// check for single client messages

	switch(mod) {
	case MOD_SUICIDE:
		message = "suicides";
		break;
	case MOD_FALLING:
		message = "'s thoughts weren't happy enough";
		break;
	case MOD_CRUSH:
		message = "was squished";
		break;
	case MOD_WATER:
		message = "sank like a rock";
		break;
	case MOD_SLIME:
		message = "melted";
		break;
	case MOD_LAVA:
		message = "does a back flip into the lava";
		break;
	case MOD_TARGET_LASER:
		message = "saw the light";
		break;
	case MOD_TRIGGER_HURT:
		message = "was in the wrong place";
		break;
	case MOD_BLEEDING:
		message = "bled to death";
		break;
	default:
		message = NULL;
		break;
	}

	if (attacker == target) {
		gender = ci->gender;
		switch (mod) {
		case MOD_GRENADE_SPLASH:
			break;
		default:
			//Elder: shouldn't be here
			break;
		}
	}

	if (!(attacker == ENTITYNUM_WORLD || attacker == target)) message = NULL;
	if (message) {
		CG_Printf( "%s %s.\n", targetName, message);
		return;
	}

	// check for kill messages from the current clientNum
	if (attacker == cg.snap->ps.clientNum) {
		char	*s;

		if (cgs.gametype < GT_TEAM) {
			s = va("You fragged %s\n%s place with %i", targetName,
				CG_PlaceString( cg.snap->ps.persistant[PERS_RANK] + 1 ),
				cg.snap->ps.persistant[PERS_SCORE] );
		} else {
			s = va("You fragged %s", targetName );
		}
		// print the text message as well
// JBravo: attempting to stop these messages for spectators
		if (cg.snap->ps.persistant[PERS_TEAM] != TEAM_SPECTATOR)
			CG_CenterPrint( s, SCREEN_HEIGHT * 0.25, (BIGCHAR_WIDTH+SMALLCHAR_WIDTH)*.5 );
	}

	// check for double client messages
	if ( !attackerInfo ) {
		attacker = ENTITYNUM_WORLD;
		strcpy( attackerName, "noname" );
	} else {
		Q_strncpyz( attackerName, Info_ValueForKey( attackerInfo, "n" ), sizeof(attackerName) - 2);
		strcat( attackerName, S_COLOR_WHITE );
		// check for kill messages about the current clientNum
		if ( target == cg.snap->ps.clientNum ) {
			Q_strncpyz( cg.killerName, attackerName, sizeof( cg.killerName ) );
		}
	}

	if (attacker != ENTITYNUM_WORLD) {
		switch (mod) {
		case MOD_PISTOL:
			if (gender == GENDER_FEMALE)
				message = "has a hole in her head from";
			else if (gender == GENDER_NEUTER)
				message = "has a hole in its head from";
			else
				message = "has a hole in his head from";
			message2 = "'s Mark23 Pistol";
			break;
		case MOD_M4:
			message = "had a makeover by";
			message2 = "'s M4 Assault rifle";
			break;
		case MOD_MP5:
			message = "'s brains are on the wall thanks to";
			message2 = "'s 10mm MP5/10 round";
			break;
		case MOD_AKIMBO:
			message = "was trepanned by";
			message2 = "'s akimbo Mark 23 pistols";
			break;
		case MOD_SNIPER:
// JBravo: fixing these fraglines for players that dont have a sniper
//			if (cg.refdef.fov_x < 90) {
			if (cgs.clientinfo[target].curWeapon == WP_SSG3000) {
				if (gender == GENDER_NEUTER)
					message = "saw the sniper bullet go through its scope thanks to";
				else if (gender == GENDER_FEMALE)
					message = "saw the sniper bullet go through her scope thanks to";
				else
					message = "saw the sniper bullet go through his scope thanks to";
			} else {
				message = "caught a sniper bullet between the eyes from";
			}
			break;
		case MOD_KNIFE:
			if (gender == GENDER_NEUTER)
				message = "had its throat slit by";
			else if (gender == GENDER_FEMALE)
				message = "had her throat slit by";
			else
				message = "had his throat slit by";
			break;
		case MOD_KNIFE_THROWN:
			message = "caught";
			if (gender == GENDER_NEUTER)
				message2 = "'s flying knife with its forehead";
			else if (gender == GENDER_FEMALE)
				message2 = "'s flying knife with her forehead";
			else
				message2 = "'s flying knife with his forehead";
			break;
		case MOD_HANDCANNON:
		case MOD_M3:
		case MOD_KICK:
		case MOD_GRENADE:
		case MOD_GRENADE_SPLASH:
			//Elder: shouldn't be here
			break;
		case MOD_TELEFRAG:
			message = "tried to invade";
			message2 = "'s personal space";
			break;
		case MOD_FALLING:
			message = "was taught how to fly by";
			break;
		default:
			message = "was killed by";
			break;
		}

// JBravo: live players dont get fraglines.
		if (message) {
			if (cg.snap->ps.clientNum == target || cg.snap->ps.clientNum == attacker ||
				cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR ||
				cg_RQ3_team_round_going.integer == 0)
				CG_Printf( "%s %s %s%s\n",
					targetName, message, attackerName, message2);
			return;
		}
	}

	// we don't know what it was
	CG_Printf( "(CG_Obituary_Head)%s died and the mod is %i. Tell this to JB\n", targetName, mod );
}
*/

/*
=============
Added by Elder
Slim version of main obit

CG_Obituary_Chest
=============
*/
/*
static void CG_Obituary_Chest( entityState_t *ent ) {
	int		mod, target, attacker;
	char		*message, *message2;
	const char	*targetInfo, *attackerInfo;
	char		targetName[32], attackerName[32];
	gender_t	gender;
	clientInfo_t	*ci;

	target = ent->otherEntityNum;
	attacker = ent->otherEntityNum2;
	mod = ent->eventParm;

	if ( target < 0 || target >= MAX_CLIENTS ) {
		CG_Error( "CG_Obituary: target out of range" );
	}
	ci = &cgs.clientinfo[target];

	if ( attacker < 0 || attacker >= MAX_CLIENTS ) {
		attacker = ENTITYNUM_WORLD;
		attackerInfo = NULL;
	} else {
		attackerInfo = CG_ConfigString( CS_PLAYERS + attacker );
	}

	targetInfo = CG_ConfigString( CS_PLAYERS + target );
	if ( !targetInfo ) {
		return;
	}
	Q_strncpyz( targetName, Info_ValueForKey( targetInfo, "n" ), sizeof(targetName) - 2);
	strcat( targetName, S_COLOR_WHITE );

	message2 = "";

	// check for single client messages

	switch( mod ) {
	case MOD_SUICIDE:
		message = "suicides";
		break;
	case MOD_FALLING:
		message = "'s thoughts weren't happy enough";
		break;
	case MOD_CRUSH:
		message = "was squished";
		break;
	case MOD_WATER:
		message = "sank like a rock";
		break;
	case MOD_SLIME:
		message = "melted";
		break;
	case MOD_LAVA:
		message = "does a back flip into the lava";
		break;
	case MOD_TARGET_LASER:
		message = "saw the light";
		break;
	case MOD_TRIGGER_HURT:
		message = "was in the wrong place";
		break;
	case MOD_BLEEDING:
		message = "bled to death";
		break;
	default:
		message = NULL;
		break;
	}

	if (attacker == target) {
		gender = ci->gender;
		switch (mod) {
		case MOD_GRENADE_SPLASH:
		default:
			//Elder: shouldn't be here
			break;
		}
	}

	if (!(attacker == ENTITYNUM_WORLD || attacker ==target)) message = NULL;
	if (message) {
		CG_Printf( "%s %s.\n", targetName, message);
		return;
	}

	// check for kill messages from the current clientNum
	if ( attacker == cg.snap->ps.clientNum ) {
		char	*s;

		if ( cgs.gametype < GT_TEAM ) {
			s = va("You fragged %s\n%s place with %i", targetName,
				CG_PlaceString( cg.snap->ps.persistant[PERS_RANK] + 1 ),
				cg.snap->ps.persistant[PERS_SCORE] );
		} else {
			s = va("You fragged %s", targetName );
		}
		// print the text message as well
// JBravo: attempting to stop these messages for spectators
		if (cg.snap->ps.persistant[PERS_TEAM] != TEAM_SPECTATOR)
			CG_CenterPrint( s, SCREEN_HEIGHT * 0.25, (BIGCHAR_WIDTH+SMALLCHAR_WIDTH)*.5 );
	}

	// check for double client messages
	if ( !attackerInfo ) {
		attacker = ENTITYNUM_WORLD;
		strcpy( attackerName, "noname" );
	} else {
		Q_strncpyz( attackerName, Info_ValueForKey( attackerInfo, "n" ), sizeof(attackerName) - 2);
		strcat( attackerName, S_COLOR_WHITE );
		// check for kill messages about the current clientNum
		if ( target == cg.snap->ps.clientNum ) {
			Q_strncpyz( cg.killerName, attackerName, sizeof( cg.killerName ) );
		}
	}

	if ( attacker != ENTITYNUM_WORLD ) {
		switch (mod) {
		case MOD_PISTOL:
			message = "loses a vital chest organ thanks to";
			message2 = "'s Mark 23 pistol";
			break;
		case MOD_M4:
			message = "feels some heart burn thanks to";
			message2 = "'s M4 Assault Rifle";
			break;
		case MOD_MP5:
			message = "feels some chest pain via";
			message2 = "'s MP5/10 Submachinegun";
			break;
		case MOD_AKIMBO:
			message = "was John Woo'd by";
			break;
		case MOD_SNIPER:
			message = "was picked off by";
			break;
		case MOD_KNIFE:
			message = "had open heart surgery, compliments of";
			break;
		case MOD_KNIFE_THROWN:
			message = "'s ribs don't help against";
			message2 = "'s flying knife";
			break;
		case MOD_HANDCANNON:
		case MOD_M3:
		case MOD_KICK:
		case MOD_GRENADE:
		case MOD_GRENADE_SPLASH:
			//Elder: shouldn't be here
			break;
		case MOD_TELEFRAG:
			message = "tried to invade";
			message2 = "'s personal space";
			break;
		case MOD_FALLING:
			message = "was taught how to fly by";
			break;
		default:
			message = "was killed by";
			break;
		}

// JBravo: live players dont get fraglines.
		if (message) {
			if (cg.snap->ps.clientNum == target || cg.snap->ps.clientNum == attacker ||
				cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR ||
				cg_RQ3_team_round_going.integer == 0)
				CG_Printf( "%s %s %s%s\n",
					targetName, message, attackerName, message2);
			return;
		}
	}

	// we don't know what it was
	CG_Printf( "(CG_Obituary_Chest)%s died and the mod is %i. Tell this to JB\n", targetName, mod );
}
*/
/*
=============
Added by Elder
Slim version of main obit

CG_Obituary_Stomach
=============
*/
/*
static void CG_Obituary_Stomach( entityState_t *ent ) {
	int		mod, target, attacker;
	char		*message, *message2;
	const char	*targetInfo, *attackerInfo;
	char		targetName[32], attackerName[32];
	//Makro - wasn't initialized, caused a warning in MSVC
	gender_t	gender = GENDER_MALE;
	clientInfo_t	*ci;

	target = ent->otherEntityNum;
	attacker = ent->otherEntityNum2;
	mod = ent->eventParm;

	if ( target < 0 || target >= MAX_CLIENTS ) {
		CG_Error( "CG_Obituary: target out of range" );
	}
	ci = &cgs.clientinfo[target];

	if ( attacker < 0 || attacker >= MAX_CLIENTS ) {
		attacker = ENTITYNUM_WORLD;
		attackerInfo = NULL;
	} else {
		attackerInfo = CG_ConfigString( CS_PLAYERS + attacker );
	}

	targetInfo = CG_ConfigString( CS_PLAYERS + target );
	if ( !targetInfo ) {
		return;
	}
	Q_strncpyz( targetName, Info_ValueForKey( targetInfo, "n" ), sizeof(targetName) - 2);
	strcat( targetName, S_COLOR_WHITE );

	message2 = "";

	// check for single client messages

	switch( mod ) {
	case MOD_SUICIDE:
		message = "suicides";
		break;
	case MOD_FALLING:
		message = "'s thoughts weren't happy enough";
		break;
	case MOD_CRUSH:
		message = "was squished";
		break;
	case MOD_WATER:
		message = "sank like a rock";
		break;
	case MOD_SLIME:
		message = "melted";
		break;
	case MOD_LAVA:
		message = "does a back flip into the lava";
		break;
	case MOD_TARGET_LASER:
		message = "saw the light";
		break;
	case MOD_TRIGGER_HURT:
		message = "was in the wrong place";
		break;
	case MOD_BLEEDING:
		message = "bled to death";
		break;
	default:
		message = NULL;
		break;
	}

	if (attacker == target) {
		gender = ci->gender;
		switch (mod) {
		case MOD_GRENADE_SPLASH:
		default:
			//Elder: shouldn't be here
			break;
		}
	}
	if (!(attacker == ENTITYNUM_WORLD || attacker ==target)) message = NULL;
	if (message) {
		CG_Printf( "%s %s.\n", targetName, message);
		return;
	}

	// check for kill messages from the current clientNum
	if ( attacker == cg.snap->ps.clientNum ) {
		char	*s;

		if ( cgs.gametype < GT_TEAM ) {
			s = va("You fragged %s\n%s place with %i", targetName,
				CG_PlaceString( cg.snap->ps.persistant[PERS_RANK] + 1 ),
				cg.snap->ps.persistant[PERS_SCORE] );
		} else {
			s = va("You fragged %s", targetName );
		}
		// print the text message as well
// JBravo: attempting to stop these messages for spectators
		if (cg.snap->ps.persistant[PERS_TEAM] != TEAM_SPECTATOR)
			CG_CenterPrint( s, SCREEN_HEIGHT * 0.25, (BIGCHAR_WIDTH+SMALLCHAR_WIDTH)*.5 );
	}

	// check for double client messages
	if ( !attackerInfo ) {
		attacker = ENTITYNUM_WORLD;
		strcpy( attackerName, "noname" );
	} else {
		Q_strncpyz( attackerName, Info_ValueForKey( attackerInfo, "n" ), sizeof(attackerName) - 2);
		strcat( attackerName, S_COLOR_WHITE );
		// check for kill messages about the current clientNum
		if ( target == cg.snap->ps.clientNum ) {
			Q_strncpyz( cg.killerName, attackerName, sizeof( cg.killerName ) );
		}
	}

	if ( attacker != ENTITYNUM_WORLD ) {
		switch (mod) {
		case MOD_PISTOL:
			if (gender == GENDER_NEUTER)
				message = "loses its lunch to";
			else if (gender == GENDER_FEMALE)
				message = "loses her lunch to";
			else
				message = "loses his lunch to";
			message2 = "'s .45 caliber pistol round";
			break;
		case MOD_M4:
			message = "has an upset stomach thanks to";
			message2 = "'s M4 Assault Rifle";
			break;
		case MOD_MP5:
			message = "needs some Pepto Bismol after";
			message2 = "'s 10mm MP5 round";
			break;
		case MOD_AKIMBO:
			message = "needs some new kidneys thanks to";
			message2 = "'s akimbo Mark 23 pistols";
			break;
		case MOD_SNIPER:
			message = "was sniped in the stomach by";
			break;
		case MOD_KNIFE:
			message = "was gutted by";
			break;
		case MOD_KNIFE_THROWN:
			if (gender == GENDER_NEUTER)
				message = "sees the contents of its own stomach thanks to";
			else if (gender == GENDER_FEMALE)
				message = "sees the contents of her own stomach thanks to";
			else
				message = "sees the contents of his own stomach thanks to";
			message2 = "'s flying knife";
			break;
		case MOD_HANDCANNON:
		case MOD_M3:
		case MOD_KICK:
		case MOD_GRENADE:
		case MOD_GRENADE_SPLASH:
			//Elder: shouldn't be here
			break;
		case MOD_TELEFRAG:
			message = "tried to invade";
			message2 = "'s personal space";
			break;
		case MOD_FALLING:
			message = "was taught how to fly by";
			break;
		default:
			message = "was killed by";
			break;
		}

// JBravo: live players dont get fraglines.
		if (message) {
			if (cg.snap->ps.clientNum == target || cg.snap->ps.clientNum == attacker ||
				cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR ||
				cg_RQ3_team_round_going.integer == 0)
				CG_Printf( "%s %s %s%s\n",
					targetName, message, attackerName, message2);
			return;
		}
	}

	// we don't know what it was
	CG_Printf( "(CG_Obituary_Stomach)%s died and the mod is %i. Tell this to JB\n", targetName, mod );
}
*/
/*
=============
Added by Elder
Slim version of main obit

CG_Obituary_Legs
=============
*/
/*
static void CG_Obituary_Legs( entityState_t *ent ) {
	int			mod;
	int			target, attacker;
	char		*message;
	char		*message2;
	const char	*targetInfo;
	const char	*attackerInfo;
	char		targetName[32];
	char		attackerName[32];
	//Makro - wasn't initialized, caused a warning in MSVC
	gender_t	gender = GENDER_MALE;
	clientInfo_t	*ci;

	target = ent->otherEntityNum;
	attacker = ent->otherEntityNum2;
	mod = ent->eventParm;
	if ( target < 0 || target >= MAX_CLIENTS ) {
		CG_Error( "CG_Obituary: target out of range" );
	}
	ci = &cgs.clientinfo[target];

	if ( attacker < 0 || attacker >= MAX_CLIENTS ) {
		attacker = ENTITYNUM_WORLD;
		attackerInfo = NULL;
	} else {
		attackerInfo = CG_ConfigString( CS_PLAYERS + attacker );
	}

	targetInfo = CG_ConfigString( CS_PLAYERS + target );
	if ( !targetInfo ) {
		return;
	}
	Q_strncpyz( targetName, Info_ValueForKey( targetInfo, "n" ), sizeof(targetName) - 2);
	strcat( targetName, S_COLOR_WHITE );
	message2 = "";

	// check for single client messages

	switch( mod ) {
	case MOD_SUICIDE:
		message = "suicides";
		break;
	case MOD_FALLING:
		message = "'s thoughts weren't happy enough";
		break;
	case MOD_CRUSH:
		message = "was squished";
		break;
	case MOD_WATER:
		message = "sank like a rock";
		break;
	case MOD_SLIME:
		message = "melted";
		break;
	case MOD_LAVA:
		message = "does a back flip into the lava";
		break;
	case MOD_TARGET_LASER:
		message = "saw the light";
		break;
	case MOD_TRIGGER_HURT:
		message = "was in the wrong place";
		break;
	case MOD_BLEEDING:
		message = "bled to death";
		break;
	default:
		message = NULL;
		break;
	}

	if (attacker == target) {
		gender = ci->gender;
		switch (mod) {
		case MOD_GRENADE_SPLASH:
		default:
			//Elder: shouldn't be here
			break;
		}
	}

	if (!(attacker == ENTITYNUM_WORLD || attacker == target)) message = NULL;
	if (message) {
		CG_Printf( "%s %s.\n", targetName, message);
		return;
	}

	// check for kill messages from the current clientNum
	if ( attacker == cg.snap->ps.clientNum ) {
		char	*s;

		if ( cgs.gametype < GT_TEAM ) {
			s = va("You fragged %s\n%s place with %i", targetName,
				CG_PlaceString( cg.snap->ps.persistant[PERS_RANK] + 1 ),
				cg.snap->ps.persistant[PERS_SCORE] );
		} else {
			s = va("You fragged %s", targetName );
		}
		// print the text message as well
// JBravo: attempting to stop these messages for spectators
		if (cg.snap->ps.persistant[PERS_TEAM] != TEAM_SPECTATOR)
			CG_CenterPrint( s, SCREEN_HEIGHT * 0.25, (BIGCHAR_WIDTH+SMALLCHAR_WIDTH)*.5 );
	}

	// check for double client messages
	if ( !attackerInfo ) {
		attacker = ENTITYNUM_WORLD;
		strcpy( attackerName, "noname" );
	} else {
		Q_strncpyz( attackerName, Info_ValueForKey( attackerInfo, "n" ), sizeof(attackerName) - 2);
		strcat( attackerName, S_COLOR_WHITE );
		// check for kill messages about the current clientNum
		if ( target == cg.snap->ps.clientNum ) {
			Q_strncpyz( cg.killerName, attackerName, sizeof( cg.killerName ) );
		}
	}

	if ( attacker != ENTITYNUM_WORLD ) {
		switch (mod) {
		case MOD_PISTOL:
			message = "is legless because of";
			message2 = "'s .45 caliber pistol round";
			break;
		case MOD_M4:
			message = "is now shorter thanks to";
			message2 = "'s M4 Assault Rifle";
			break;
		case MOD_MP5:
			if (gender == GENDER_NEUTER)
				message = "had its legs blown off thanks to";
			else if (gender == GENDER_FEMALE)
				message = "had her legs blown off thanks to";
			else
				message = "had his legs blown off thanks to";
			message2 = "'s MP5/10 Submachinegun";
			break;
		case MOD_AKIMBO:
			message = "was shot in the legs by";
			message2 = "'s akimbo Mark 23 pistols";
			break;
		case MOD_SNIPER:
			message = "was shot in the legs by";
			break;
		case MOD_KNIFE:
			message = "was stabbed repeatedly in the legs by";
			break;
		case MOD_KNIFE_THROWN:
			if (gender == GENDER_NEUTER)
				message = "had its legs cut off thanks to";
			else if (gender == GENDER_FEMALE)
				message = "had her legs cut off thanks to";
			else
				message = "had his legs cut off thanks to";

			message2 = "'s flying knife";
			break;
		case MOD_HANDCANNON:
		case MOD_M3:
		case MOD_KICK:
		case MOD_GRENADE:
		case MOD_GRENADE_SPLASH:
			//Elder: shouldn't be here
			break;
		case MOD_TELEFRAG:
			message = "tried to invade";
			message2 = "'s personal space";
			break;
		case MOD_FALLING:
			message = "was taught how to fly by";
			break;
		default:
			message = "was killed by";
			break;
		}

// JBravo: live players dont get fraglines.
		if (message) {
			if (cg.snap->ps.clientNum == target || cg.snap->ps.clientNum == attacker ||
				cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR ||
				cg_RQ3_team_round_going.integer == 0)
				CG_Printf( "%s %s %s%s\n",
					targetName, message, attackerName, message2);
			return;
		}
	}

	// we don't know what it was
	CG_Printf( "(CG_Obituary_Legs)%s died and the mod is %i. Tell this to JB\n", targetName, mod );
}

//==========================================================================
*/
/*
===============
CG_UseItem
===============
*/
static void CG_UseItem( centity_t *cent ) {
	clientInfo_t *ci;
	int			itemNum, clientNum;
	gitem_t		*item;
	entityState_t *es;

	es = &cent->currentState;

	itemNum = (es->event & ~EV_EVENT_BITS) - EV_USE_ITEM0;
	if ( itemNum < 0 || itemNum > HI_NUM_HOLDABLE ) {
		itemNum = 0;
	}

	// print a message if the local player
	if ( es->number == cg.snap->ps.clientNum ) {
		if ( !itemNum ) {
			CG_CenterPrint( "No item to use", SCREEN_HEIGHT * 0.30, BIGCHAR_WIDTH );
		} else {
			item = BG_FindItemForHoldable( itemNum );
			CG_CenterPrint( va("Use %s", item->pickup_name), SCREEN_HEIGHT * 0.30, BIGCHAR_WIDTH );
		}
	}

	switch ( itemNum ) {
	default:
	case HI_NONE:
		trap_S_StartSound (NULL, es->number, CHAN_BODY, cgs.media.useNothingSound );
		break;

	case HI_TELEPORTER:
		break;

	case HI_MEDKIT:
		clientNum = cent->currentState.clientNum;
		if ( clientNum >= 0 && clientNum < MAX_CLIENTS ) {
			ci = &cgs.clientinfo[ clientNum ];
			ci->medkitUsageTime = cg.time;
		}
		trap_S_StartSound (NULL, es->number, CHAN_BODY, cgs.media.medkitSound );
		break;

#ifdef MISSIONPACK
	case HI_KAMIKAZE:
		break;

	case HI_PORTAL:
		break;
	case HI_INVULNERABILITY:
		trap_S_StartSound (NULL, es->number, CHAN_BODY, cgs.media.useInvulnerabilitySound );
		break;
#endif
	}

}

/*
================
CG_ItemPickup

A new item was picked up this frame
================
*/
static void CG_ItemPickup( int itemNum ) {
	cg.itemPickup = itemNum;
	cg.itemPickupTime = cg.time;
	cg.itemPickupBlendTime = cg.time;
	// see if it should be the grabbed weapon
	if ( bg_itemlist[itemNum].giType == IT_WEAPON ) {
		// select it immediately
		//Blaze: Changed WP_MACHINEGUN to WP_PISTOL
//		if ( cg_autoswitch.integer && bg_itemlist[itemNum].giTag != WP_PISTOL ) {
//			cg.weaponSelectTime = cg.time;
//			cg.weaponSelect = bg_itemlist[itemNum].giTag;
//		}
	}

}


/*
================
CG_PainEvent

Also called by playerstate transition
================
*/
void CG_PainEvent( centity_t *cent, int health ) {
	char	*snd;

	// don't do more than two pain sounds a second
	if ( cg.time - cent->pe.painTime < 500 ) {
		return;
	}

	if ( health < 25 ) {
		snd = "*pain25_1.wav";
	} else if ( health < 50 ) {
		snd = "*pain50_1.wav";
	} else if ( health < 75 ) {
		snd = "*pain75_1.wav";
	} else {
		snd = "*pain100_1.wav";
	}
	trap_S_StartSound( NULL, cent->currentState.number, CHAN_VOICE,
		CG_CustomSound( cent->currentState.number, snd ) );

	// save pain time for programitic twitch animation
	cent->pe.painTime = cg.time;
	cent->pe.painDirection ^= 1;
}


/*
=============
CG_DMRewardEvent

Used to display the frag rewards for getting many frags in a row during a DM game.

=============
*/

static void CG_DMRewardEvent( entityState_t *ent ) {

	int			mod;
	int			attacker;
	char		*message;
	const char	*attackerInfo;
	char		attackerName[32];
//	clientInfo_t	*ci;


	attacker = ent->otherEntityNum2;
	mod = ent->eventParm;

	if ( attacker < 0 || attacker >= MAX_CLIENTS ) {
		attacker = ENTITYNUM_WORLD;
		attackerInfo = NULL;
	} else {
		attackerInfo = CG_ConfigString( CS_PLAYERS + attacker );
	}

	Q_strncpyz( attackerName, Info_ValueForKey( attackerInfo, "n" ), sizeof(attackerName) - 2);
	strcat( attackerName, S_COLOR_WHITE );
	if ((mod > 3) && (mod < 8))
		message = "2";
	else if (mod < 16)
		message = "4";
	else if (mod < 32)
		message = "8";
	else
		message = "16";

	if (message) {
		CG_Printf( "%s has %d kills in a row and receives %s frags for the kill!\n",
                        attackerName, mod, message);
		return;
	}


}

/*
==============
CG_JumpKick

Added by Elder
Handles messages for client jumpkicks plus sound event
==============
*/
static void CG_JumpKick ( entityState_t *ent )
{
	int				target;
	int				attacker;
	clientInfo_t	*ci;
	char			sex[4];		// null-terminated so one-bigger than pronoun

	target = ent->otherEntityNum;
	attacker = ent->otherEntityNum2;

	if ( target < 0 || target >= MAX_CLIENTS ) {
		CG_Error( "CG_JumpKick: target out of range" );
	}
	else if ( attacker < 0 || target >= MAX_CLIENTS ) {
		CG_Error( "CG_JumpKick: attacker out of range" );
	}

	if (ent->weapon && attacker == cg.clientNum)
	{
		// this client was the kicker
		ci = &cgs.clientinfo[target];

		// get gender-appropriate pronoun
		if (ci->gender == GENDER_FEMALE)
			Q_strncpyz(sex, "her", sizeof(sex));
		else if (ci->gender == GENDER_MALE)
			Q_strncpyz(sex, "his", sizeof(sex));
		else
			Q_strncpyz(sex, "its", sizeof(sex));

		CG_Printf("You kicked %s's %s from %s hands!\n",
					ci->name, cg_weapons[ent->weapon].item->pickup_name, sex);
	}
	else if (ent->weapon && target == cg.clientNum)
	{
		// this client was the kicked
		ci = &cgs.clientinfo[attacker];
		CG_Printf("%s kicked your weapon from your hands!\n", ci->name);
	}

	// everyone hears this
	trap_S_StartSound(NULL, ent->number, CHAN_AUTO, cgs.media.kickSound);
}

/*
==============
CG_EntityEvent

An entity has an event value
also called by CG_CheckPlayerstateEvents
==============
*/
#define	DEBUGNAME(x) if(cg_debugEvents.integer){CG_Printf(x"\n");}
void CG_EntityEvent( centity_t *cent, vec3_t position ) {
	entityState_t	*es;
	int				event;
	vec3_t			dir, viewDir;
	const char		*s;
	int				clientNum;
	clientInfo_t	*ci;

	es = &cent->currentState;
	event = es->event & ~EV_EVENT_BITS;

	if ( cg_debugEvents.integer ) {
		CG_Printf( "ent:%3i  event:%3i ", es->number, event );
	}

	if ( !event ) {
		DEBUGNAME("ZEROEVENT");
		return;
	}

	clientNum = es->clientNum;
	if ( clientNum < 0 || clientNum >= MAX_CLIENTS ) {
		clientNum = 0;
	}
	ci = &cgs.clientinfo[ clientNum ];

	CG_CalcViewDir2(es->origin2, position, viewDir);

	switch ( event ) {
	//
	// movement generated events
	//
	case EV_FOOTSTEP:
		DEBUGNAME("EV_FOOTSTEP");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY,
				cgs.media.footsteps[ ci->footsteps ][rand()&3] );
		}
		break;
	case EV_FOOTSTEP_METAL:
		DEBUGNAME("EV_FOOTSTEP_METAL");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY,
				cgs.media.footsteps[ FOOTSTEP_METAL ][rand()&3] );
		}
		break;
	case EV_FOOTSTEP_GRASS:
		DEBUGNAME("EV_FOOTSTEP_GRASS");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY,
				cgs.media.footsteps[ FOOTSTEP_GRASS ][rand()&3] );
		}
		break;

	case EV_FOOTSTEP_GRAVEL:
		DEBUGNAME("EV_FOOTSTEP_GRAVEL");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY,
				cgs.media.footsteps[ FOOTSTEP_GRAVEL ][rand()&3] );
		}
		break;

	case EV_FOOTSTEP_WOOD:
		DEBUGNAME("EV_FOOTSTEP_WOOD");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY,
				cgs.media.footsteps[ FOOTSTEP_WOOD ][rand()&3] );
		}
		break;
	case EV_FOOTSTEP_CARPET:
		DEBUGNAME("EV_FOOTSTEP_CARPET");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY,
				cgs.media.footsteps[ FOOTSTEP_CARPET ][rand()&3] );
		}
		break;
// JBravo: begin new sounds
	case EV_FOOTSTEP_SNOW:
		DEBUGNAME("EV_FOOTSTEP_SNOW");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY,
				cgs.media.footsteps[ FOOTSTEP_SNOW ][rand()&3] );
		}
		break;
	case EV_FOOTSTEP_MUD:
		DEBUGNAME("EV_FOOTSTEP_MUD");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY,
				cgs.media.footsteps[ FOOTSTEP_MUD ][rand()&3] );
		}
		break;
	case EV_FOOTSTEP_WOOD2:
		DEBUGNAME("EV_FOOTSTEP_WOOD2");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY,
				cgs.media.footsteps[ FOOTSTEP_WOOD2 ][rand()&3] );
		}
		break;
	case EV_FOOTSTEP_HARDMETAL:
		DEBUGNAME("EV_FOOTSTEP_HARDMETAL");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY,
				cgs.media.footsteps[ FOOTSTEP_HARDMETAL ][rand()&3] );
		}
		break;
// JBravo: end new sounds
// Makro - more sounds
	case EV_FOOTSTEP_LEAVES:
		DEBUGNAME("EV_FOOTSTEP_LEAVES");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY,
				cgs.media.footsteps[ FOOTSTEP_LEAVES ][rand()&3] );
		}
		break;
	case EV_FOOTSTEP_CEMENT:
		DEBUGNAME("EV_FOOTSTEP_CEMENT");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY,
				cgs.media.footsteps[ FOOTSTEP_CEMENT ][rand()&3] );
		}
		break;
	case EV_FOOTSTEP_MARBLE:
		DEBUGNAME("EV_FOOTSTEP_MARBLE");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY,
				cgs.media.footsteps[ FOOTSTEP_MARBLE ][rand()&3] );
		}
		break;
	case EV_FOOTSTEP_SNOW2:
		DEBUGNAME("EV_FOOTSTEP_SNOW2");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY,
				cgs.media.footsteps[ FOOTSTEP_SNOW2 ][rand()&3] );
		}
		break;
	case EV_FOOTSTEP_HARDSTEPS:
		DEBUGNAME("EV_FOOTSTEP_HARDSTEPS");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY,
				cgs.media.footsteps[ FOOTSTEP_HARDSTEPS ][rand()&3] );
		}
		break;
	case EV_FOOTSTEP_SAND:
		DEBUGNAME("EV_FOOTSTEP_SAND");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY,
				cgs.media.footsteps[ FOOTSTEP_SAND ][rand()&3] );
		}
		break;
// Makro - end new sounds
	case EV_FOOTSTEP_METAL2:
		DEBUGNAME("EV_FOOTSTEP_METAL2");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY,
				cgs.media.footsteps[ FOOTSTEP_METAL2 ][rand()&3] );
		}
		break;
	case EV_FOOTSPLASH:
		DEBUGNAME("EV_FOOTSPLASH");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY,
				cgs.media.footsteps[ FOOTSTEP_SPLASH ][rand()&3] );
		}
		break;
	case EV_FOOTWADE:
		DEBUGNAME("EV_FOOTWADE");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY,
				cgs.media.footsteps[ FOOTSTEP_SPLASH ][rand()&3] );
		}
		break;
	case EV_SWIM:
		DEBUGNAME("EV_SWIM");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY,
				cgs.media.footsteps[ FOOTSTEP_SPLASH ][rand()&3] );
		}
		break;


	case EV_FALL_SHORT:
		DEBUGNAME("EV_FALL_SHORT");

		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.landSound );


		if ( clientNum == cg.predictedPlayerState.clientNum ) {
			// smooth landing z changes
			cg.landChange = -8;
			cg.landTime = cg.time;
		}
		break;
	case EV_FALL_SHORT_NOSOUND:
		DEBUGNAME("EV_FALL_SHORT_NOSOUND");

		if ( clientNum == cg.predictedPlayerState.clientNum ) {
			// smooth landing z changes
			cg.landChange = -8;
			cg.landTime = cg.time;
		}
		break;
	case EV_FALL_MEDIUM:
		DEBUGNAME("EV_FALL_MEDIUM");
		// use normal pain sound

		trap_S_StartSound( NULL, es->number, CHAN_VOICE, CG_CustomSound( es->number, "*pain100_1.wav" ) );


		if ( clientNum == cg.predictedPlayerState.clientNum ) {
			// smooth landing z changes
			cg.landChange = -16;
			cg.landTime = cg.time;
		}
		break;
	case EV_FALL_MEDIUM_NOSOUND:
		DEBUGNAME("EV_FALL_MEDIUM_NOSOUND");

		if ( clientNum == cg.predictedPlayerState.clientNum ) {
			// smooth landing z changes
			cg.landChange = -16;
			cg.landTime = cg.time;
		}
		break;

	case EV_FALL_FAR:
		DEBUGNAME("EV_FALL_FAR");

		trap_S_StartSound (NULL, es->number, CHAN_AUTO, CG_CustomSound( es->number, "*fall1.wav" ) );


		cent->pe.painTime = cg.time;	// don't play a pain sound right after this
		if ( clientNum == cg.predictedPlayerState.clientNum ) {
			// smooth landing z changes
			cg.landChange = -24;
			cg.landTime = cg.time;
		}
		break;
	case EV_FALL_FAR_NOSOUND:
		DEBUGNAME("EV_FALL_FAR_NOSOUND");
		if ( clientNum == cg.predictedPlayerState.clientNum ) {
			// smooth landing z changes
			cg.landChange = -24;
			cg.landTime = cg.time;
		}
		break;


	case EV_STEP_4:
	case EV_STEP_8:
	case EV_STEP_12:
	case EV_STEP_16:		// smooth out step up transitions
		DEBUGNAME("EV_STEP");
	{
		float	oldStep;
		int		delta;
		int		step;

		if ( clientNum != cg.predictedPlayerState.clientNum ) {
			break;
		}
		// if we are interpolating, we don't need to smooth steps
		if ( cg.demoPlayback || (cg.snap->ps.pm_flags & PMF_FOLLOW) ||
			cg_nopredict.integer || cg_synchronousClients.integer ) {
			break;
		}
		// check for stepping up before a previous step is completed
		delta = cg.time - cg.stepTime;
		if (delta < STEP_TIME) {
			oldStep = cg.stepChange * (STEP_TIME - delta) / STEP_TIME;
		} else {
			oldStep = 0;
		}

		// add this amount
		step = 4 * (event - EV_STEP_4 + 1 );
		cg.stepChange = oldStep + step;
		if ( cg.stepChange > MAX_STEP_CHANGE ) {
			cg.stepChange = MAX_STEP_CHANGE;
		}
		cg.stepTime = cg.time;
		break;
	}

	case EV_JUMP_PAD:
		DEBUGNAME("EV_JUMP_PAD");
//		CG_Printf( "EV_JUMP_PAD w/effect #%i\n", es->eventParm );
		{
			localEntity_t	*smoke;
			vec3_t			up = {0, 0, 1};


			smoke = CG_SmokePuff( cent->lerpOrigin, up,
						  32,
						  1, 1, 1, 0.33f,
						  1000,
						  cg.time, 0,
						  LEF_PUFF_DONT_SCALE,
						  cgs.media.smokePuffShader );
		}

		// boing sound at origin, jump sound on player
		// NiceAss: Allow for custom jump sounds. I have no clue what I am doing.
		if (es->eventParm) trap_S_StartSound ( cent->lerpOrigin, -1, CHAN_VOICE, cgs.gameSounds[ es->eventParm ]); //cgs.media.jumpPadSound );
		//Blaze: Get rid of jump noises
//		trap_S_StartSound (NULL, es->number, CHAN_VOICE, CG_CustomSound( es->number, "*jump1.wav" ) );
		break;

	case EV_JUMP:
		DEBUGNAME("EV_JUMP");
		//Blaze: Get rid of jump noises
//		trap_S_StartSound (NULL, es->number, CHAN_VOICE, CG_CustomSound( es->number, "*jump1.wav" ) );
		break;
	case EV_TAUNT:
		DEBUGNAME("EV_TAUNT");
		trap_S_StartSound (NULL, es->number, CHAN_VOICE, CG_CustomSound( es->number, "*taunt.wav" ) );
		break;
#ifdef MISSIONPACK
	case EV_TAUNT_YES:
		DEBUGNAME("EV_TAUNT_YES");
		CG_VoiceChatLocal(SAY_TEAM, qfalse, es->number, COLOR_CYAN, VOICECHAT_YES);
		break;
	case EV_TAUNT_NO:
		DEBUGNAME("EV_TAUNT_NO");
		CG_VoiceChatLocal(SAY_TEAM, qfalse, es->number, COLOR_CYAN, VOICECHAT_NO);
		break;
	case EV_TAUNT_FOLLOWME:
		DEBUGNAME("EV_TAUNT_FOLLOWME");
		CG_VoiceChatLocal(SAY_TEAM, qfalse, es->number, COLOR_CYAN, VOICECHAT_FOLLOWME);
		break;
	case EV_TAUNT_GETFLAG:
		DEBUGNAME("EV_TAUNT_GETFLAG");
		CG_VoiceChatLocal(SAY_TEAM, qfalse, es->number, COLOR_CYAN, VOICECHAT_ONGETFLAG);
		break;
	case EV_TAUNT_GUARDBASE:
		DEBUGNAME("EV_TAUNT_GUARDBASE");
		CG_VoiceChatLocal(SAY_TEAM, qfalse, es->number, COLOR_CYAN, VOICECHAT_ONDEFENSE);
		break;
	case EV_TAUNT_PATROL:
		DEBUGNAME("EV_TAUNT_PATROL");
		CG_VoiceChatLocal(SAY_TEAM, qfalse, es->number, COLOR_CYAN, VOICECHAT_ONPATROL);
		break;
#endif
	case EV_WATER_TOUCH:
		DEBUGNAME("EV_WATER_TOUCH");
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.watrInSound );
		break;
	case EV_WATER_LEAVE:
		DEBUGNAME("EV_WATER_LEAVE");
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.watrOutSound );
		break;
	case EV_WATER_UNDER:
		DEBUGNAME("EV_WATER_UNDER");
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.watrUnSound );
		break;
	case EV_WATER_CLEAR:
		DEBUGNAME("EV_WATER_CLEAR");
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, CG_CustomSound( es->number, "*gasp.wav" ) );
		break;

	case EV_ITEM_PICKUP:
		DEBUGNAME("EV_ITEM_PICKUP");
		{
			gitem_t	*item;
			int		index;

			index = es->eventParm;		// player predicted

			if ( index < 1 || index >= bg_numItems ) {
				break;
			}
			item = &bg_itemlist[ index ];

			// powerups and team items will have a separate global sound, this one
			// will be played at prediction time
			if ( item->giType == IT_POWERUP || item->giType == IT_TEAM) {
				trap_S_StartSound (NULL, es->number, CHAN_AUTO,	cgs.media.n_healthSound );
			} else if (item->giType == IT_PERSISTANT_POWERUP) {
#ifdef MISSIONPACK
				switch (item->giTag ) {
					case PW_SCOUT:
						trap_S_StartSound (NULL, es->number, CHAN_AUTO,	cgs.media.scoutSound );
					break;
					case PW_GUARD:
						trap_S_StartSound (NULL, es->number, CHAN_AUTO,	cgs.media.guardSound );
					break;
					case PW_DOUBLER:
						trap_S_StartSound (NULL, es->number, CHAN_AUTO,	cgs.media.doublerSound );
					break;
					case PW_AMMOREGEN:
						trap_S_StartSound (NULL, es->number, CHAN_AUTO,	cgs.media.ammoregenSound );
					break;
				}
#endif
			} else if (item->giType == IT_HOLDABLE) {
				// Elder: we want sounds for unique item pickup
				trap_S_StartSound (NULL, es->number, CHAN_AUTO,	trap_S_RegisterSound( item->pickup_sound, qfalse ) );
			} else {
				// Elder: no item pick-up sound
					//trap_S_StartSound (NULL, es->number, CHAN_AUTO,	trap_S_RegisterSound( item->pickup_sound, qfalse ) );
			}

			// show icon and name on status bar
			if ( es->number == cg.snap->ps.clientNum ) {
				CG_ItemPickup( index );
			}
		}
		break;

	case EV_GLOBAL_ITEM_PICKUP:
		DEBUGNAME("EV_GLOBAL_ITEM_PICKUP");
		{
			gitem_t	*item;
			int		index;

			index = es->eventParm;		// player predicted

			if ( index < 1 || index >= bg_numItems ) {
				break;
			}
			item = &bg_itemlist[ index ];
			// powerup pickups are global
			if( item->pickup_sound ) {
				trap_S_StartSound (NULL, cg.snap->ps.clientNum, CHAN_AUTO, trap_S_RegisterSound( item->pickup_sound, qfalse ) );
			}

			// show icon and name on status bar
			if ( es->number == cg.snap->ps.clientNum ) {
				CG_ItemPickup( index );
			}
		}
		break;

	//
	// weapon events
	//
	case EV_NOAMMO:
		DEBUGNAME("EV_NOAMMO");
		//Elder: Only play on non-grenade/knife
		//Todo: use "out of ammo sound" for specific gun?
		switch ( cent->currentState.weapon )
		{
			case WP_GRENADE:
			case WP_KNIFE:
				break;
			default:
				trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.noAmmoSound );
				break;
		}
		if ( es->number == cg.snap->ps.clientNum ) {
			CG_OutOfAmmoChange();
		}
		break;
	case EV_CHANGE_WEAPON:
		DEBUGNAME("EV_CHANGE_WEAPON");
		//Elder: TODO: change to appropriate weapon "in" sound
		//trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.selectSound );
		break;
	case EV_FIRE_WEAPON:
		DEBUGNAME("EV_FIRE_WEAPON");
		//Elder: modified
		CG_FireWeapon( cent, es->eventParm );
		break;
	case EV_RELOAD_WEAPON0:
		DEBUGNAME("EV_RELOAD_WEAPON0");
		CG_ReloadWeapon( cent, 0 );
		break;
	case EV_RELOAD_WEAPON1:
		DEBUGNAME("EV_RELOAD_WEAPON1");
		CG_ReloadWeapon( cent, 1 );
		break;
	case EV_RELOAD_WEAPON2:
		DEBUGNAME("EV_RELOAD_WEAPON2");
		CG_ReloadWeapon( cent, 2 );
		break;
	case EV_USE_ITEM0:
		DEBUGNAME("EV_USE_ITEM0");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM1:
		DEBUGNAME("EV_USE_ITEM1");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM2:
		DEBUGNAME("EV_USE_ITEM2");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM3:
		DEBUGNAME("EV_USE_ITEM3");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM4:
		DEBUGNAME("EV_USE_ITEM4");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM5:
		DEBUGNAME("EV_USE_ITEM5");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM6:
		DEBUGNAME("EV_USE_ITEM6");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM7:
		DEBUGNAME("EV_USE_ITEM7");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM8:
		DEBUGNAME("EV_USE_ITEM8");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM9:
		DEBUGNAME("EV_USE_ITEM9");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM10:
		DEBUGNAME("EV_USE_ITEM10");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM11:
		DEBUGNAME("EV_USE_ITEM11");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM12:
		DEBUGNAME("EV_USE_ITEM12");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM13:
		DEBUGNAME("EV_USE_ITEM13");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM14:
		DEBUGNAME("EV_USE_ITEM14");
		CG_UseItem( cent );
		break;

	//=================================================================

	//
	// other events
	//
	case EV_PLAYER_TELEPORT_IN:
		DEBUGNAME("EV_PLAYER_TELEPORT_IN");
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.teleInSound );
		CG_SpawnEffect( position);
		break;

	case EV_PLAYER_TELEPORT_OUT:
		DEBUGNAME("EV_PLAYER_TELEPORT_OUT");
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.teleOutSound );
		CG_SpawnEffect(  position);
		break;

	case EV_ITEM_POP:
		DEBUGNAME("EV_ITEM_POP");
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.respawnSound );
		break;
	case EV_ITEM_RESPAWN:
		DEBUGNAME("EV_ITEM_RESPAWN");
		cent->miscTime = cg.time;	// scale up from this
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.respawnSound );
		break;

	case EV_GRENADE_BOUNCE:
		DEBUGNAME("EV_GRENADE_BOUNCE");
		if ( rand() & 1 ) {
			trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.hgrenb1aSound );
		} else {
			trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.hgrenb2aSound );
		}
		break;

#ifdef MISSIONPACK
	case EV_PROXIMITY_MINE_STICK:
		DEBUGNAME("EV_PROXIMITY_MINE_STICK");
		//Elder: removed
		if( es->eventParm & SURF_FLESH ) {
			//trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.wstbimplSound );
		//Makro - new surfaceparm system
		//} else 	if( es->eventParm & SURF_METALSTEPS ) {
		} else 	if( IsMetalFlag(es->eventParm) ) {
			//trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.wstbimpmSound );
		} else {
			//trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.wstbimpdSound );
		}
		break;

	case EV_PROXIMITY_MINE_TRIGGER:
		DEBUGNAME("EV_PROXIMITY_MINE_TRIGGER");
		//Elder: removed
		//trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.wstbactvSound );
		break;
	case EV_KAMIKAZE:
		DEBUGNAME("EV_KAMIKAZE");
		CG_KamikazeEffect( cent->lerpOrigin );
		break;
	case EV_OBELISKEXPLODE:
		DEBUGNAME("EV_OBELISKEXPLODE");
		CG_ObeliskExplode( cent->lerpOrigin, es->eventParm );
		break;
	case EV_OBELISKPAIN:
		DEBUGNAME("EV_OBELISKPAIN");
		CG_ObeliskPain( cent->lerpOrigin );
		break;
	case EV_INVUL_IMPACT:
		DEBUGNAME("EV_INVUL_IMPACT");
		CG_InvulnerabilityImpact( cent->lerpOrigin, cent->currentState.angles );
		break;
	case EV_JUICED:
		DEBUGNAME("EV_JUICED");
		CG_InvulnerabilityJuiced( cent->lerpOrigin );
		break;
	case EV_LIGHTNINGBOLT:
		DEBUGNAME("EV_LIGHTNINGBOLT");
		CG_LightningBoltBeam(es->origin2, es->pos.trBase);
		break;
#endif
	case EV_SCOREPLUM:
		DEBUGNAME("EV_SCOREPLUM");
		CG_ScorePlum( cent->currentState.otherEntityNum, cent->lerpOrigin, cent->currentState.time );
		break;
	//
	// missile impacts
	//
	case EV_MISSILE_HIT:
		DEBUGNAME("EV_MISSILE_HIT");
		ByteToDir( es->eventParm, dir );
		CG_MissileHitPlayer( es->weapon, position, dir, es->otherEntityNum );
		break;

	case EV_MISSILE_MISS:
		DEBUGNAME("EV_MISSILE_MISS");
		ByteToDir( es->eventParm, dir );
		CG_MissileHitWall( es->weapon, 0, position, dir, viewDir, IMPACTSOUND_DEFAULT, 0 );
		break;

	case EV_MISSILE_MISS_METAL:
		DEBUGNAME("EV_MISSILE_MISS_METAL");
		ByteToDir( es->eventParm, dir );
		CG_MissileHitWall( es->weapon, 0, position, dir, viewDir, IMPACTSOUND_METAL, 0 );
		break;
	case EV_KNIFE_MISS:
		DEBUGNAME("EV_KNIFE_MISS");
		ByteToDir( es->eventParm, dir );
		CG_MissileHitWall( es->weapon, 0, position, dir, viewDir, IMPACTSOUND_METAL, RQ3_WPMOD_KNIFESLASH );
		break;

	case EV_RAILTRAIL:
		DEBUGNAME("EV_RAILTRAIL");
		//Blaze: No Railgun
		//cent->currentState.weapon = WP_RAILGUN;
		// if the end was on a nomark surface, don't make an explosion
		//CG_RailTrail( ci, es->origin2, es->pos.trBase );
		if ( es->eventParm != 255 ) {
			ByteToDir( es->eventParm, dir );
			CG_MissileHitWall( es->weapon, es->clientNum, position, dir, viewDir, IMPACTSOUND_DEFAULT, 0 );
		}
		break;

	case EV_BULLET_HIT_WALL:
		DEBUGNAME("EV_BULLET_HIT_WALL");
		ByteToDir( es->eventParm, dir );
		CG_Bullet( es->pos.trBase, es->otherEntityNum, dir, qfalse, ENTITYNUM_WORLD, IMPACTSOUND_DEFAULT);
		break;

	case EV_BULLET_HIT_METAL:
		DEBUGNAME("EV_BULLET_HIT_METAL");
		ByteToDir( es->eventParm, dir );
		CG_Bullet( es->pos.trBase, es->otherEntityNum, dir, qfalse, ENTITYNUM_WORLD, IMPACTSOUND_METAL);
		break;

	case EV_BULLET_HIT_GLASS:
		DEBUGNAME("EV_BULLET_HIT_GLASS");
		ByteToDir( es->eventParm, dir );
		CG_Bullet( es->pos.trBase, es->otherEntityNum, dir, qfalse, ENTITYNUM_WORLD, IMPACTSOUND_GLASS);
		break;


	case EV_BULLET_HIT_KEVLAR:
		DEBUGNAME("EV_BULLET_HIT_KEVLAR");
		ByteToDir( es->eventParm, dir );
		VectorScale( dir, -1, dir );
		trap_S_StartSound( NULL, es->number, CHAN_AUTO, cgs.media.kevlarHitSound);
		if (cg_RQ3_impactEffects.integer)
		{
			vec3_t velocity;
			vec3_t origin;
			int sparkCount;
			int i;

			sparkCount = 20 + rand() % 15;
			VectorCopy(es->pos.trBase, origin);
			origin[2] += 12;
			// Generate the particles
			for (i = 0; i < sparkCount; i++)
			{
				VectorScale(dir, 150 + rand() % 30, velocity);
				//random upwards sparks
				if ( rand() % 5 < 1)
					velocity[2] += 120 + rand() % 30;

				velocity[0] += rand() % 80 - 40;
				velocity[1] += rand() % 80 - 40;
				CG_ParticleSparks(origin, velocity, 150 + rand() % 120, 2, 2, -4, 1);
			}
		}
		break;

	case EV_BULLET_HIT_FLESH:
		DEBUGNAME("EV_BULLET_HIT_FLESH");
		//ByteToDir( es->eventParm, dir );
		//Elder: added additional param
		CG_Bullet( es->pos.trBase, es->otherEntityNum, dir, qtrue, es->otherEntityNum2, IMPACTSOUND_FLESH);
		break;

	case EV_SSG3000_HIT_FLESH:
		DEBUGNAME("EV_SSG3000_HIT_FLESH");
		ByteToDir( es->eventParm, dir );
		//Elder: added additional param
		CG_Bullet( es->pos.trBase, es->otherEntityNum, dir, qtrue, es->otherEntityNum2, IMPACTSOUND_FLESH);
		VectorAdd(es->pos.trBase, dir, dir);
		CG_BleedSpray(es->pos.trBase, dir, es->otherEntityNum2, 10);
		break;

	case EV_JUMPKICK:
		DEBUGNAME("EV_JUMPKICK");
		ByteToDir( es->eventParm, dir );
		// obviously not the pistol but oh well
		CG_MissileHitPlayer( WP_PISTOL, position, dir, es->otherEntityNum );
		CG_JumpKick( es );
		break;

	case EV_EJECTBLOOD:
		DEBUGNAME("EV_EJECTBLOOD");
		// Straight up
		dir[0] = 0;
		dir[1] = 0;
		dir[2] = 20;
		// Eject blood splats
		CG_EjectBloodSplat ( es->pos.trBase, dir, 1, 1500);
		//CG_BleedParticleSpray( es->pos.trBase, dir, es->otherEntityNum, 25, 1500 );
		break;

	case EV_SHOTGUN:
		DEBUGNAME("EV_SHOTGUN");
		CG_ShotgunFire( es ,qtrue);
		break;

	case EV_HANDCANNON:
		DEBUGNAME("EV_SHOTGUN");
		CG_ShotgunFire( es ,qfalse);
		break;

	case EV_GENERAL_SOUND:
		DEBUGNAME("EV_GENERAL_SOUND");
		if ( cgs.gameSounds[ es->eventParm ] ) {
			trap_S_StartSound (NULL, es->number, CHAN_VOICE, cgs.gameSounds[ es->eventParm ] );
		} else {
			s = CG_ConfigString( CS_SOUNDS + es->eventParm );
			trap_S_StartSound (NULL, es->number, CHAN_VOICE, CG_CustomSound( es->number, s ) );
		}
		break;

	case EV_GLOBAL_SOUND:	// play from the player's head so it never diminishes
		DEBUGNAME("EV_GLOBAL_SOUND");
		if ( cgs.gameSounds[ es->eventParm ] ) {
			trap_S_StartSound (NULL, cg.snap->ps.clientNum, CHAN_AUTO, cgs.gameSounds[ es->eventParm ] );
		} else {
			s = CG_ConfigString( CS_SOUNDS + es->eventParm );
			trap_S_StartSound (NULL, cg.snap->ps.clientNum, CHAN_AUTO, CG_CustomSound( es->number, s ) );
		}
		break;


	case EV_RQ3_SOUND:
		DEBUGNAME("EV_RQ3_SOUND");
		switch (es->eventParm) {
			// Elder: handled in EV_JUMPKICK now
			// But this is for non-client hits like glass
    		case RQ3_SOUND_KICK:
    			trap_S_StartSound( NULL, es->number, CHAN_AUTO, cgs.media.kickSound);
    			break;

			//Elder: handled in EV_HEADSHOT now
			/*
    		case RQ3_SOUND_HEADSHOT:
    			//CG_Printf("EV_RQ3_SOUND: Headshot\n");
    			//Elder: extra blood - synched with sound
    			//CG_Bleed( position, es->number );
    			trap_S_StartSound( NULL, es->number, CHAN_AUTO, cgs.media.headshotSound);
    			break;
			*/
    		case RQ3_SOUND_LCA:
    			//Global sound
    			//trap_S_StartSound( NULL, cg.snap->ps.clientNum, CHAN_AUTO, cgs.media.lcaSound);
    			break;
			case RQ3_SOUND_KEVLARHIT:
				//TODO: make sparks from hit position
				trap_S_StartSound( NULL, es->number, CHAN_AUTO, cgs.media.kevlarHitSound);
				break;
			case RQ3_SOUND_KNIFEHIT:
				//When a player gets slashed
				trap_S_StartSound( NULL, es->number, CHAN_AUTO, cgs.media.knifeHitSound);
				break;
			case RQ3_SOUND_KNIFEDEATH:
				trap_S_StartSound( NULL, es->number, CHAN_AUTO, cgs.media.knifeDeathSound);
				break;
			case RQ3_SOUND_COUNTDOWN:
				trap_S_StartLocalSound( cgs.media.lca10_0Sound, CHAN_ANNOUNCER );
				break;
    		default:
    			break;
		}
		break;

	case EV_DMREWARD:
		DEBUGNAME("EV_DMREWARD");
		CG_DMRewardEvent( es );
		break;

	case EV_GLOBAL_TEAM_SOUND:	// play from the player's head so it never diminishes
		{
			DEBUGNAME("EV_GLOBAL_TEAM_SOUND");
			switch( es->eventParm ) {
				case GTS_RED_CAPTURE: // CTF: red team captured the blue flag, 1FCTF: red team captured the neutral flag
					if ( cgs.clientinfo[cg.clientNum].team == TEAM_RED )
						CG_AddBufferedSound( cgs.media.captureYourTeamSound );
					else
						CG_AddBufferedSound( cgs.media.captureOpponentSound );
					break;
				case GTS_BLUE_CAPTURE: // CTF: blue team captured the red flag, 1FCTF: blue team captured the neutral flag
					if ( cgs.clientinfo[cg.clientNum].team == TEAM_BLUE )
						CG_AddBufferedSound( cgs.media.captureYourTeamSound );
					else
						CG_AddBufferedSound( cgs.media.captureOpponentSound );
					break;
				case GTS_RED_RETURN: // CTF: blue flag returned, 1FCTF: never used
					if ( cgs.clientinfo[cg.clientNum].team == TEAM_RED )
						CG_AddBufferedSound( cgs.media.returnYourTeamSound );
					else
						CG_AddBufferedSound( cgs.media.returnOpponentSound );
					//
					CG_AddBufferedSound( cgs.media.blueFlagReturnedSound );
					break;
				case GTS_BLUE_RETURN: // CTF red flag returned, 1FCTF: neutral flag returned
					if ( cgs.clientinfo[cg.clientNum].team == TEAM_BLUE )
						CG_AddBufferedSound( cgs.media.returnYourTeamSound );
					else
						CG_AddBufferedSound( cgs.media.returnOpponentSound );
					//
					CG_AddBufferedSound( cgs.media.redFlagReturnedSound );
					break;

				case GTS_RED_TAKEN: // CTF: red team took blue flag, 1FCTF: blue team took the neutral flag
					// if this player picked up the flag then a sound is played in CG_CheckLocalSounds
					if (cg.snap->ps.powerups[PW_BLUEFLAG] || cg.snap->ps.powerups[PW_NEUTRALFLAG]) {
					}
					else {
					if (cgs.clientinfo[cg.clientNum].team == TEAM_BLUE) {
#ifdef MISSIONPACK
							if (cgs.gametype == GT_1FCTF)
								CG_AddBufferedSound( cgs.media.yourTeamTookTheFlagSound );
							else
#endif
						 	CG_AddBufferedSound( cgs.media.enemyTookYourFlagSound );
						}
						else if (cgs.clientinfo[cg.clientNum].team == TEAM_RED) {
#ifdef MISSIONPACK
							if (cgs.gametype == GT_1FCTF)
								CG_AddBufferedSound( cgs.media.enemyTookTheFlagSound );
							else
#endif
 							CG_AddBufferedSound( cgs.media.yourTeamTookEnemyFlagSound );
						}
					}
					break;
				case GTS_BLUE_TAKEN: // CTF: blue team took the red flag, 1FCTF red team took the neutral flag
					// if this player picked up the flag then a sound is played in CG_CheckLocalSounds
					if (cg.snap->ps.powerups[PW_REDFLAG] || cg.snap->ps.powerups[PW_NEUTRALFLAG]) {
					}
					else {
						if (cgs.clientinfo[cg.clientNum].team == TEAM_RED) {
#ifdef MISSIONPACK
							if (cgs.gametype == GT_1FCTF)
								CG_AddBufferedSound( cgs.media.yourTeamTookTheFlagSound );
							else
#endif
							CG_AddBufferedSound( cgs.media.enemyTookYourFlagSound );
						}
						else if (cgs.clientinfo[cg.clientNum].team == TEAM_BLUE) {
#ifdef MISSIONPACK
							if (cgs.gametype == GT_1FCTF)
								CG_AddBufferedSound( cgs.media.enemyTookTheFlagSound );
							else
#endif
							CG_AddBufferedSound( cgs.media.yourTeamTookEnemyFlagSound );
						}
					}
					break;
				case GTS_REDOBELISK_ATTACKED: // Overload: red obelisk is being attacked
					if (cgs.clientinfo[cg.clientNum].team == TEAM_RED) {
						CG_AddBufferedSound( cgs.media.yourBaseIsUnderAttackSound );
					}
					break;
				case GTS_BLUEOBELISK_ATTACKED: // Overload: blue obelisk is being attacked
					if (cgs.clientinfo[cg.clientNum].team == TEAM_BLUE) {
						CG_AddBufferedSound( cgs.media.yourBaseIsUnderAttackSound );
					}
					break;

				case GTS_REDTEAM_SCORED:
					CG_AddBufferedSound(cgs.media.redScoredSound);
					break;
				case GTS_BLUETEAM_SCORED:
					CG_AddBufferedSound(cgs.media.blueScoredSound);
					break;
				case GTS_REDTEAM_TOOK_LEAD:
					if (cg_RQ3_anouncer.integer == 1) CG_AddBufferedSound(cgs.media.redLeadsSound);
					break;
				case GTS_BLUETEAM_TOOK_LEAD:
					if (cg_RQ3_anouncer.integer == 1) CG_AddBufferedSound(cgs.media.blueLeadsSound);
					break;
				case GTS_TEAMS_ARE_TIED:
					if (cg_RQ3_anouncer.integer == 1) CG_AddBufferedSound( cgs.media.teamsTiedSound );
					break;
#ifdef MISSIONPACK
				case GTS_KAMIKAZE:
					trap_S_StartLocalSound(cgs.media.kamikazeFarSound, CHAN_ANNOUNCER);
					break;
#endif
				default:
					break;
			}
			break;
		}

	case EV_HEADSHOT:
		//Elder: headshot spray + sound
		DEBUGNAME("EV_HEADSHOT");
		//trap_S_StartSound( es->pos.trBase, es->number, CHAN_AUTO, cgs.media.headshotSound);
		trap_S_StartSound( cent->lerpOrigin, es->number, CHAN_AUTO, cgs.media.headshotSound);
		ByteToDir(es->eventParm, dir);
		VectorAdd(es->pos.trBase, dir, dir);
		CG_BleedSpray(es->pos.trBase, dir, es->otherEntityNum, 6);
		break;

	case EV_PAIN:
		// local player sounds are triggered in CG_CheckLocalSounds,
		// so ignore events on the player
		DEBUGNAME("EV_PAIN");/*
		if ( es->eventParm == -99999 ) {
			CG_Printf("EV_PAIN: Headshot\n");
			trap_S_StartSound( NULL, es->number, CHAN_AUTO, cgs.media.headshotSound);
		}*/
		if ( cent->currentState.number != cg.snap->ps.clientNum ) {
			CG_PainEvent( cent, es->eventParm );
		}
		break;

	case EV_DEATH1:
	case EV_DEATH2:
	case EV_DEATH3:
		DEBUGNAME("EV_DEATHx");
		trap_S_StartSound( NULL, es->number, CHAN_VOICE,
				CG_CustomSound( es->number, va("*death%i.wav", event - EV_DEATH1 + 1) ) );
		break;


	case EV_OBITUARY:
		DEBUGNAME("EV_OBITUARY");
// JBravo: not used
//		CG_Obituary( es );
		break;
	//Elder: location events
	case EV_OBITUARY_HEAD:
		DEBUGNAME("EV_OBITUARY_HEAD");
// JBravo: the following mod's dont have locations and are not handled in the location Orbits
/*		if (es->eventParm == MOD_HANDCANNON || es->eventParm == MOD_M3 ||
		    es->eventParm == MOD_KICK || es->eventParm == MOD_GRENADE || es->eventParm == MOD_GRENADE_SPLASH) {
			CG_Obituary( es );
		} else {
			CG_Obituary_Head( es );
		} */
		break;
	case EV_OBITUARY_CHEST:
		DEBUGNAME("EV_OBITUARY_CHEST");
// JBravo: the following mod's dont have locations and are not handled in the location Orbits
/*		if (es->eventParm == MOD_HANDCANNON || es->eventParm == MOD_M3 ||
		    es->eventParm == MOD_KICK || es->eventParm == MOD_GRENADE || es->eventParm == MOD_GRENADE_SPLASH) {
			CG_Obituary( es );
		} else {
			CG_Obituary_Chest( es );
		} */
		break;
	case EV_OBITUARY_STOMACH:
		DEBUGNAME("EV_OBITUARY_STOMACH");
// JBravo: the following mod's dont have locations and are not handled in the location Orbits
/*		if (es->eventParm == MOD_HANDCANNON || es->eventParm == MOD_M3 ||
		    es->eventParm == MOD_KICK || es->eventParm == MOD_GRENADE || es->eventParm == MOD_GRENADE_SPLASH) {
			CG_Obituary( es );
		} else {
			CG_Obituary_Stomach( es );
		} */
		break;
	case EV_OBITUARY_LEGS:
		DEBUGNAME("EV_OBITUARY_LEGS");
// JBravo: the following mod's dont have locations and are not handled in the location Orbits
/*		if (es->eventParm == MOD_HANDCANNON || es->eventParm == MOD_M3 ||
		    es->eventParm == MOD_KICK || es->eventParm == MOD_GRENADE || es->eventParm == MOD_GRENADE_SPLASH) {
			CG_Obituary( es );
		} else {
			CG_Obituary_Legs( es );
		} */
		break;
	//
	// powerup events
	//
	case EV_POWERUP_QUAD:
		DEBUGNAME("EV_POWERUP_QUAD");
		if ( es->number == cg.snap->ps.clientNum ) {
			cg.powerupActive = PW_QUAD;
			cg.powerupTime = cg.time;
		}
		trap_S_StartSound (NULL, es->number, CHAN_ITEM, cgs.media.quadSound );
		break;
	case EV_POWERUP_BATTLESUIT:
		DEBUGNAME("EV_POWERUP_BATTLESUIT");
		if ( es->number == cg.snap->ps.clientNum ) {
			cg.powerupActive = PW_BATTLESUIT;
			cg.powerupTime = cg.time;
		}
		trap_S_StartSound (NULL, es->number, CHAN_ITEM, cgs.media.protectSound );
		break;
	case EV_POWERUP_REGEN:
		DEBUGNAME("EV_POWERUP_REGEN");
		if ( es->number == cg.snap->ps.clientNum ) {
			cg.powerupActive = PW_REGEN;
			cg.powerupTime = cg.time;
		}
		trap_S_StartSound (NULL, es->number, CHAN_ITEM, cgs.media.regenSound );
		break;

	case EV_GIB_PLAYER:
		DEBUGNAME("EV_GIB_PLAYER");
		// don't play gib sound when using the kamikaze because it interferes
		// with the kamikaze sound, downside is that the gib sound will also
		// not be played when someone is gibbed while just carrying the kamikaze
		if ( !(es->eFlags & EF_KAMIKAZE) ) {
			trap_S_StartSound( NULL, es->number, CHAN_BODY, cgs.media.gibSound );
		}
		CG_GibPlayer( cent->lerpOrigin );
		break;
	case EV_BREAK_GLASS1:
 		DEBUGNAME("EV_BREAK_GLASS1");
 		// Change cgs.media.gibSound to whatever sound you want it to use
 		// I think the gib sound sounds pretty good
 		//Elder: gonna move this into the function some day
 		CG_BreakGlass( cent->lerpOrigin, es->eventParm, es->number, 0, 0 );
 		break;
	case EV_BREAK_GLASS2:
 		DEBUGNAME("EV_BREAK_GLASS2");
 		CG_BreakGlass( cent->lerpOrigin, es->eventParm, es->number, 1, 0 );
 		break;
	case EV_BREAK_GLASS3:
 		DEBUGNAME("EV_BREAK_GLASS3");
 		CG_BreakGlass( cent->lerpOrigin, es->eventParm, es->number, 2, 0 );
 		break;
	case EV_CHIP_GLASS:
 		DEBUGNAME("EV_CHIP_GLASS");
 		CG_BreakGlass( cent->lerpOrigin, es->eventParm, es->number, 1, 1 );
 		break;
	case EV_PRESSURE:
 		DEBUGNAME("EV_PRESSURE");
		ByteToDir(es->eventParm, dir);
 		CG_Pressure( position, dir, cent );
		break;

  case EV_STOPLOOPINGSOUND:
		DEBUGNAME("EV_STOPLOOPINGSOUND");
		trap_S_StopLoopingSound( es->number );
		es->loopSound = 0;
		break;

	case EV_DEBUG_LINE:
		DEBUGNAME("EV_DEBUG_LINE");
		CG_Beam( cent );
		break;

// Blaze: an exploding breakable
	case EV_EXPLODE_BREAKABLE:
		DEBUGNAME("EV_EXPLODE_BREAKABLE");
		//trap_S_StartSound( NULL, es->number, CHAN_BODY, cgs.media.gibSound );
		CG_BreakBreakable( cent, es->eventParm, es->number );
		break;

	default:
		DEBUGNAME("UNKNOWN");
		CG_Error( "Unknown event: %i", event );
		break;
	}

}


/*
==============
CG_CheckEvents

==============
*/
void CG_CheckEvents( centity_t *cent ) {
	// check for event-only entities
	if ( cent->currentState.eType > ET_EVENTS ) {
		if ( cent->previousEvent ) {
			return;	// already fired
		}
		// if this is a player event set the entity number of the client entity number
		if ( cent->currentState.eFlags & EF_PLAYER_EVENT ) {
			cent->currentState.number = cent->currentState.otherEntityNum;
		}

		cent->previousEvent = 1;

		cent->currentState.event = cent->currentState.eType - ET_EVENTS;
	} else {
		// check for events riding with another entity
		if ( cent->currentState.event == cent->previousEvent ) {
			return;
		}
		cent->previousEvent = cent->currentState.event;
		if ( ( cent->currentState.event & ~EV_EVENT_BITS ) == 0 ) {
			return;
		}
	}

	// calculate the position at exactly the frame time
	CG_EvaluateTrajectory( &cent->currentState.pos, cg.snap->serverTime, cent->lerpOrigin );
	CG_SetEntitySoundPosition( cent );

	CG_EntityEvent( cent, cent->lerpOrigin );
}

