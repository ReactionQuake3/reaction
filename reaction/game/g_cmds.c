//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.178  2003/03/09 21:30:38  jbravo
// Adding unlagged.   Still needs work.
//
// Revision 1.177  2003/02/27 03:58:35  jbravo
// Fixed the FF system after adding TDM broke it. Added color to error messages
//
// Revision 1.176  2002/11/13 00:50:38  jbravo
// Fixed item dropping, specmode selection on death and helmet probs.
//
// Revision 1.175  2002/10/30 20:04:34  jbravo
// Adding helmet
//
// Revision 1.174  2002/10/26 22:03:43  jbravo
// Made TeamDM work RQ3 style.
//
// Revision 1.173  2002/10/26 18:29:17  jbravo
// Added allweap and allitem funtionality.
//
// Revision 1.172  2002/10/26 00:37:18  jbravo
// New multiple item code and added PB support to the UI
//
// Revision 1.171  2002/10/21 21:00:39  slicer
// New MM features and bug fixes
//
// Revision 1.170  2002/09/30 01:32:30  jbravo
// Fixing the vote and callvote cmd's so dead players in CTB can use them.
//
// Revision 1.169  2002/09/29 16:06:44  jbravo
// Work done at the HPWorld expo
//
// Revision 1.168  2002/09/24 05:06:17  blaze
// fixed spectating so ref\'s can now use all the chasecam modes.
//
// Revision 1.167  2002/09/07 22:40:01  jbravo
// Added a scaling ctb respawn system.  Fixed a bug that allowed players to
// spawn before their team respawn with the team command.
//
// Revision 1.166  2002/09/04 00:16:17  makro
// Fixed 'unselectable grenade shown in the inventory if you switch weapons
// after pulling the pin' bug
//
// Revision 1.165  2002/08/27 04:53:46  niceass
// one more woops
//
// Revision 1.164  2002/08/27 04:50:54  niceass
// woops
//
// Revision 1.163  2002/08/27 04:48:13  niceass
// ref say added
//
// Revision 1.162  2002/08/24 07:58:49  niceass
// moved sanitizestring to g_util
//
// Revision 1.161  2002/08/23 14:25:05  slicer
// Added a new Referee System with multiple ref support
//
// Revision 1.160  2002/08/21 07:00:07  jbravo
// Added CTB respawn queue and fixed game <-> cgame synch problem in CTB
//
// Revision 1.159  2002/08/17 01:56:31  jbravo
// % vars now only work in say_team mode.
//
// Revision 1.158  2002/08/13 16:59:16  makro
// Fixed per-client callvote limit; added a new cvar - g_RQ3_maxClientVotes
//
// Revision 1.157  2002/08/07 20:49:21  slicer
// Adapted Vote system to Matchmode
//
// Revision 1.156  2002/07/16 04:08:28  niceass
// temporary hack solution for map rotation and ctb
//
// Revision 1.155  2002/07/11 04:31:07  niceass
// removed team leaders in all gametypes and changed some text from centerprint to console print
//
// Revision 1.154  2002/07/09 05:41:48  niceass
// scoreboard fix
//
// Revision 1.153  2002/07/09 03:24:00  niceass
// fixed team talk
//
// Revision 1.152  2002/07/08 04:25:02  niceass
// changes to who can be seen dead. removed deaths
//
// Revision 1.151  2002/07/07 23:54:57  jbravo
// Say and Say_team now resets the idle timer
//
// Revision 1.150  2002/07/04 04:20:41  jbravo
// Fixed my weaponchange cancel in the Use cmd, and fixed the bug where players
// that where in eye spectating someone moved on to another player instantly on death.
//
// Revision 1.149  2002/07/02 20:22:35  jbravo
// Changed the files to use the right ui.
//
// Revision 1.148  2002/07/02 19:15:17  jbravo
// Drop weapon with akimbos now behaves like AQ, plus no suicides during LCA
//
// Revision 1.147  2002/06/29 04:15:15  jbravo
// CTF is now CTB.  no weapons while the case is in hand other than pistol or knife
//
// Revision 1.146  2002/06/28 21:41:12  jbravo
// Gawd damn buglet
//
// Revision 1.145  2002/06/24 05:51:51  jbravo
// CTF mode is now semi working
//
// Revision 1.144  2002/06/23 23:32:29  jbravo
// Fixed logging of clients IP addresses.
//
// Revision 1.143  2002/06/23 21:44:08  jbravo
// Fixed shots fired stats for non TP modes and some cleanups
//
// Revision 1.142  2002/06/23 19:27:18  niceass
// bandage bug fix
//
// Revision 1.141  2002/06/23 15:22:53  slicer
// Future 2.1 Matchmode Features - PART II
//
// Revision 1.140  2002/06/23 03:04:09  assimon
// Added suport for callvote map <map> and ref map <map>.
//
// Revision 1.139  2002/06/21 00:05:55  slicer
// Spectators can now use say_team to communicate among each others, DM and TP
//
// Revision 1.138  2002/06/20 22:32:43  jbravo
// Added last damaged player and fixed a test2 model problem (atrimum my ass :)
// Changed g_RQ3_printOwnObits to g_RQ3_showOwnKills and it also controls $K
//
// Revision 1.137  2002/06/20 21:06:07  freud
// Added playing of lens.wav when using the unzoom command
//
// Revision 1.136  2002/06/20 18:40:17  slicer
// Future 2.1 Matchmode Features - PART I
//
// Revision 1.135  2002/06/20 02:27:30  jbravo
// Now the scoreboard doesnt show whos alive and whos not when you are alive
//
// Revision 1.134  2002/06/19 18:18:09  jbravo
// Small cleanups for compiler warnings
//
// Revision 1.133  2002/06/18 09:23:23  niceass
// small callvote upgrade
//
// Revision 1.132  2002/06/18 03:57:38  jbravo
// Committing for aasimon.  Callvote nextmap removed and replaced with cyclemap for .ini
//
// Revision 1.131  2002/06/17 16:57:39  jbravo
// Items can now be dropped during bandaging
//
// Revision 1.130  2002/06/17 03:22:58  jbravo
// Base voting system is now fixed.
//
// Revision 1.129  2002/06/16 20:06:14  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.128  2002/06/13 17:01:30  slicer
// Radio Gender changes according to model gender
//
// Revision 1.127  2002/06/12 22:32:24  slicer
// Even better way to improve the Cvar Anti-Cheat System
//
// Revision 1.126  2002/06/10 23:32:03  slicer
// Tweaked the weapon queuing
//
// Revision 1.125  2002/06/10 19:10:59  jbravo
// Voting system fixed for TP
//
// Revision 1.124  2002/06/10 19:04:21  slicer
// Passing RefID trought scoreboard, forgot to add
//
// Revision 1.123  2002/06/10 03:26:04  jbravo
// Fixed two small errors
//
// Revision 1.122  2002/06/09 18:58:00  makro
// no message
//
// Revision 1.121  2002/06/07 19:07:08  slicer
// removed cvars for teamXready, replaced by level.teamXready
//
// Revision 1.120  2002/06/05 23:53:05  jbravo
// Color fixes for player names
//
// Revision 1.119  2002/06/05 04:57:50  niceass
// "team" command fix
//
// Revision 1.118  2002/06/03 19:21:16  niceass
// matchmode scoreboard changes. untested
//
// Revision 1.117  2002/06/03 05:56:04  jbravo
// server used say for cmds issued during intermission
//
// Revision 1.116  2002/06/03 00:46:08  niceass
// match scoreboard changes
//
// Revision 1.115  2002/06/02 00:13:39  makro
// Spectators can vote in TP, not just call a vote
//
// Revision 1.114  2002/05/31 18:17:10  makro
// Bot stuff. Added a server command that prints a line to a client
// and everyone who is spectating him
//
// Revision 1.113  2002/05/21 04:58:28  blaze
// kicked the reload bugs ass!
//
// Revision 1.112  2002/05/19 17:50:33  jbravo
// Team fixes for DM
//
// Revision 1.111  2002/05/15 12:46:32  makro
// Small func_static change.Give ammo should now give grenades/knives
//
// Revision 1.110  2002/05/12 19:15:47  jbravo
// Added playerlist, did some cleanup on votes.
//
// Revision 1.109  2002/05/12 16:10:19  jbravo
// Added unignore
//
// Revision 1.108  2002/05/12 12:15:05  slicer
// Added Referee command for captains
//
// Revision 1.107  2002/05/11 19:52:09  slicer
// Added sub and captain to the scoreboard function
//
// Revision 1.106  2002/05/10 08:10:18  jbravo
// Fixed a bug in the Obit system and a give (weapons or all) bug
//
// Revision 1.105  2002/05/10 04:06:27  jbravo
// Added Ignore
//
// Revision 1.104  2002/05/06 00:35:49  jbravo
// Small fixes to misc stuff
//
// Revision 1.103  2002/05/05 15:51:16  slicer
// Captain and subs get saved on map_restarts ( moved to "sess" )
//
// Revision 1.102  2002/05/04 16:19:02  jbravo
// Fixing the stuff cmd to work on dedicated servers.
//
// Revision 1.101  2002/05/01 18:44:36  jbravo
// Added a stuff command.  Needed for misc things.  See bottum of cmd_use in
// g_teamplay.c
//
// Revision 1.100  2002/04/30 11:54:37  makro
// Bots rule ! Also, added clips to give all. Maybe some other things
//
// Revision 1.99  2002/04/30 01:23:05  jbravo
// Changed the server logging to be more like a normal AQ server.  Cleaned
// all colors from the logs.
//
// Revision 1.98  2002/04/28 11:03:46  slicer
// Added "teammodel" for Matchmode, Referee "pause" command
//
// Revision 1.97  2002/04/26 03:39:34  jbravo
// added tkok, fixed players always leaving zcam modes when player thats
// beeing tracked dies
//
// Revision 1.96  2002/04/23 06:03:05  niceass
// scoreboard stuff
//
// Revision 1.95  2002/04/18 16:13:23  jbravo
// Scoreboard now shows green for live players and white for dead.
// Time should not get reset on deaths any more.
//
// Revision 1.94  2002/04/14 12:55:03  jbravo
// Cleaned up cmd_reload while hunting for the m3 reload bug
//
// Revision 1.93  2002/04/13 15:37:53  jbravo
// limchasecam has been redone with new spec system
//
// Revision 1.92  2002/04/07 12:57:36  slicer
// Small fix on Matchmode Captain system
//
// Revision 1.90  2002/04/07 03:22:48  jbravo
// Tweaks and crashbug fixes
//
// Revision 1.89  2002/04/05 18:53:26  jbravo
// Warning fixes
//
// Revision 1.88  2002/04/01 22:23:14  slicer
// Added "weapon" command buffering | Solved Gren Mode Bug
//
// Revision 1.87  2002/03/31 23:41:45  jbravo
// Added the use command
//
// Revision 1.86  2002/03/31 03:31:24  jbravo
// Compiler warning cleanups
//
// Revision 1.85  2002/03/30 23:20:10  jbravo
// Added damage in scoreboard.
//
// Revision 1.84  2002/03/30 21:51:42  jbravo
// Removed all those ifdefs for zcam.
//
// Revision 1.83  2002/03/30 02:29:43  jbravo
// Lots of spectator code updates. Removed debugshit, added some color.
//
// Revision 1.82  2002/03/26 11:32:05  jbravo
// Remember specstate between rounds.
//
// Revision 1.81  2002/03/23 05:17:42  jbravo
// Major cleanup of game -> cgame communication with LCA vars.
//
// Revision 1.80  2002/03/21 19:22:12  jbravo
// Bando now adds extra ammo to the special weaps, and when its dropped it goes
// away again.
//
// Revision 1.79  2002/03/18 19:18:39  slicer
// Fixed bandage bugs ( i hope )
//
// Revision 1.78  2002/03/18 13:39:24  jbravo
// Spectators in TP can now use callvote
//
// Revision 1.77  2002/03/18 13:32:53  jbravo
// Fixed the fraglines for sniper head kills and twekaed bandaging a bit for
// testing
//
// Revision 1.76  2002/03/18 04:37:10  jbravo
// Removing locations from teamtalk on dead players.
//
// Revision 1.75  2002/03/18 01:22:35  slicer
// bandage bleedtick back to original
//
// Revision 1.74  2002/03/17 15:18:55  jbravo
// Added 2 checks to debugshit
//
// Revision 1.73  2002/03/17 13:41:28  jbravo
// Added a debug cmd to print out stuff when bugs occor
//
// Revision 1.72  2002/03/17 00:40:23  jbravo
// Adding variable team names. g_RQ3_team1name and g_RQ3_team2name. Fixed
// Slicers fraglimit check.
//
// Revision 1.71  2002/03/14 23:54:12  jbravo
// Added a variable system from AQ. Works the same except it uses $ for %
//
// Revision 1.70  2002/03/14 02:24:39  jbravo
// Adding radio :)
//
// Revision 1.69  2002/03/13 18:40:52  slicer
// Adjusted some of elder's unzoom code for the new sniper system ( server side )
//
// Revision 1.68  2002/03/07 19:46:47  jbravo
// No dropping weapons or items if bandaging
//
// Revision 1.67  2002/03/07 00:00:54  assimon
// Added a skeleton referee suport, with some functional commands (map_restart and kick)
//
// Revision 1.66  2002/03/03 21:46:26  blaze
// weapon stats, done, beta test for bugs
//
// Revision 1.65  2002/03/03 02:04:14  jbravo
// Zcam tewaking
//
// Revision 1.64  2002/03/02 14:54:24  jbravo
// Added the skin and model names to the name of the player thats being
// followed, as in AQ
//
// Revision 1.63  2002/03/01 20:22:31  jbravo
// Fixed a small booboo with the teamcounts
//
// Revision 1.62  2002/03/01 20:02:34  jbravo
// Added ui_RQ3_teamCount1, ui_RQ3_teamCount2 and ui_RQ3_numSpectators for
// makro
//
// Revision 1.61  2002/02/28 05:42:31  blaze
// weapons stats on server side
//
// Revision 1.60  2002/02/27 01:54:29  jbravo
// More spectatorfixes and finally stopped all fallingdamage anims and
// sounds during LCA.
//
// Revision 1.59  2002/02/26 21:59:10  jbravo
// Fixed death on switching teams while dead
//
// Revision 1.58  2002/02/26 04:59:10  jbravo
// Fixed teamswitching and team broadcasting
//
// Revision 1.57  2002/02/26 03:46:53  jbravo
// Range can now be set on grenades.
//
// Revision 1.56  2002/02/26 01:10:19  jbravo
// Dead people cant speak to the living any more.
//
// Revision 1.55  2002/02/25 19:41:53  jbravo
// Fixed the use ESC and join menu to join teams when dead players are
// spectating in TP mode.
// Tuned the autorespawn system a bit.  Now dead ppl. are dead for a very
// small time before they are made into spectators.
//
// Revision 1.54  2002/02/25 17:54:57  jbravo
// Added [DEAD] tags infront of players names where appropriate and made
// the server log conversation like AQ does.
//
// Revision 1.53  2002/02/23 18:07:18  slicer
// Changed Sniper code and Cam code
//
// Revision 1.52  2002/02/22 02:13:13  jbravo
// Fixed a few bugs and did some cleanups
//
// Revision 1.51  2002/02/10 22:02:06  niceass
// took some debug info out
//
// Revision 1.50  2002/02/10 08:16:12  niceass
// added deaths to the scoreboard
//
// Revision 1.49  2002/02/09 00:10:12  jbravo
// Fixed spectator follow and free and updated zcam to 1.04 and added the
// missing zcam files.
//
// Revision 1.48  2002/02/05 23:41:27  slicer
// More on matchmode..
//
// Revision 1.47  2002/02/04 00:10:49  slicer
// Matchmode: Teams Ready/Not Ready goes by cvar MM_team1/2
//
// Revision 1.43  2002/02/02 16:34:02  slicer
// Matchmode..
//
// Revision 1.42  2002/01/31 02:53:28  blaze
// err, make that playerstats command
//
// Revision 1.41  2002/01/31 02:52:49  blaze
// some basic work on the trains/elevators
//
// Revision 1.40  2002/01/31 02:25:31  jbravo
// Adding limchasecam.
//
// Revision 1.39  2002/01/11 20:20:58  jbravo
// Adding TP to main branch
//
// Revision 1.38  2002/01/11 19:48:30  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.37  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
#include "g_local.h"
#include "zcam.h"

//Blaze: was there a extra ../ here?
#include "../ta_ui/menudef.h"	// for the voice chats
//Blaze for door code
void Use_BinaryMover(gentity_t * ent, gentity_t * other, gentity_t * activator);

/*
==================
DeathmatchScoreboardMessage

==================
*/
void DeathmatchScoreboardMessage(gentity_t * ent)
{
	char entry[1024], string[1400];
	int stringlength, i, j;
	gclient_t *cl;
	int numSorted, scoreFlags, accuracy;
	int alive;

	// send the latest information on all clients
	string[0] = 0;
	stringlength = 0;
	scoreFlags = 0;

	numSorted = level.numConnectedClients;

	for (i = 0; i < numSorted; i++) {
		int ping;

		cl = &level.clients[level.sortedClients[i]];

		if (cl->pers.connected == CON_CONNECTING) {
			ping = -1;
		} else {
			//ping = cl->ps.ping < 999 ? cl->ps.ping : 999;
			ping = cl->pers.realPing < 999 ? cl->pers.realPing : 999;
		}

		if (cl->accuracy_shots) {
			accuracy = cl->accuracy_hits * 100 / cl->accuracy_shots;
		} else {
			accuracy = 0;
		}

		// NiceAss: No one can see who is dead or alive in matchmode when alive.
		// But if you are dead, you can see who is dead/alive on your team.
		alive = cl->sess.sessionTeam != TEAM_SPECTATOR;
		
		if (g_gametype.integer >= GT_TEAM && level.team_round_going) {
			if (ent->client->sess.sessionTeam != TEAM_SPECTATOR)
				alive = qtrue;

			if (g_RQ3_matchmode.integer && ent->client->sess.sessionTeam == TEAM_SPECTATOR &&
				ent->client->sess.savedTeam != cl->sess.savedTeam)
				alive = qtrue;
		}
		//Blaze: Prit out some Debug info
		if (&g_entities[level.sortedClients[i]] == NULL) G_Printf("Ln 1399\n");

		Com_sprintf(entry, sizeof(entry), " %i %i %i %i %i %i %i %i %i %i %i %i", 
			level.sortedClients[i], 
			cl->ps.persistant[PERS_SCORE], 
			ping, 
			(level.time - cl->pers.enterTime) / 60000, 
			scoreFlags, 
			g_entities[level.sortedClients[i]].s.powerups, 
			accuracy, 
			cl->ps.persistant[PERS_DAMAGE_DELT],	// JBravo: Added for scoreboard
			alive,					// JBravo: Added for TP scoreboard
			cl->sess.captain,				// Slicer: Added for Matchmode Scoreboard
			cl->sess.sub,				// Slicer: Added for Matchmode Scoreboard
			cl->sess.referee
			);

		j = strlen(entry);
		if (stringlength + j > 1024)
			break;
		strcpy(string + stringlength, entry);
		stringlength += j;
	}

	trap_SendServerCommand(ent - g_entities, va("scores %i %i %i %i %i %i %i%s", i,
						    level.teamScores[TEAM_RED], level.teamScores[TEAM_BLUE],
						    level.team1ready, level.team2ready,
							(int) level.matchTime, level.refAmmount ? level.refStatus : -1,string));
}

/*
==================
Cmd_Score_f

Request current scoreboard information
==================
*/
void Cmd_Score_f(gentity_t * ent)
{
	DeathmatchScoreboardMessage(ent);
}

/*
==================
Cmd_WeaponStats_f

Request current weaponstats information
==================
*/
void Cmd_WeaponStats_f(gentity_t * ent)
{

	trap_SendServerCommand(ent - g_entities,
			       va("wstats %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i",
				  ent->client->pers.records[REC_KNIFETHROWSHOTS],
				  ent->client->pers.records[REC_KNIFETHROWHITS],
				  ent->client->pers.records[REC_KNIFESLASHSHOTS],
				  ent->client->pers.records[REC_KNIFESLASHHITS],
				  ent->client->pers.records[REC_MK23SHOTS], ent->client->pers.records[REC_MK23HITS],
				  ent->client->pers.records[REC_M3SHOTS], ent->client->pers.records[REC_M3HITS],
				  ent->client->pers.records[REC_MP5SHOTS], ent->client->pers.records[REC_MP5HITS],
				  ent->client->pers.records[REC_M4SHOTS], ent->client->pers.records[REC_M4HITS],
				  ent->client->pers.records[REC_SSG3000SHOTS],
				  ent->client->pers.records[REC_SSG3000HITS],
				  ent->client->pers.records[REC_HANDCANNONSHOTS],
				  ent->client->pers.records[REC_HANDCANNONHITS],
				  ent->client->pers.records[REC_AKIMBOSHOTS], ent->client->pers.records[REC_AKIMBOHITS],
				  ent->client->pers.records[REC_GRENADESHOTS],
				  ent->client->pers.records[REC_GRENADEHITS], ent->client->pers.records[REC_KICKHITS],
				  ent->client->pers.records[REC_KILLS], ent->client->pers.records[REC_TEAMKILLS],
				  ent->client->pers.records[REC_SUICIDES]));

	trap_SendServerCommand(ent - g_entities,
			       va("wstats2 %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i",
				  ent->client->pers.records[REC_KNIFETHROWDEATHS],
				  ent->client->pers.records[REC_KNIFETHROWKILLS],
				  ent->client->pers.records[REC_KNIFESLASHDEATHS],
				  ent->client->pers.records[REC_KNIFESLASHKILLS],
				  ent->client->pers.records[REC_MK23DEATHS], ent->client->pers.records[REC_MK23KILLS],
				  ent->client->pers.records[REC_M3DEATHS], ent->client->pers.records[REC_M3KILLS],
				  ent->client->pers.records[REC_MP5DEATHS], ent->client->pers.records[REC_MP5KILLS],
				  ent->client->pers.records[REC_M4DEATHS], ent->client->pers.records[REC_M4KILLS],
				  ent->client->pers.records[REC_SSG3000DEATHS],
				  ent->client->pers.records[REC_SSG3000KILLS],
				  ent->client->pers.records[REC_HANDCANNONDEATHS],
				  ent->client->pers.records[REC_HANDCANNONKILLS],
				  ent->client->pers.records[REC_AKIMBODEATHS],
				  ent->client->pers.records[REC_AKIMBOKILLS],
				  ent->client->pers.records[REC_GRENADEDEATHS],
				  ent->client->pers.records[REC_GRENADEKILLS],
				  ent->client->pers.records[REC_KICKDEATHS], ent->client->pers.records[REC_KICKKILLS]));

}

/*
==================
CheatsOk
==================
*/
qboolean CheatsOk(gentity_t * ent)
{
	if (!g_cheats.integer) {
		trap_SendServerCommand(ent - g_entities, va("print \"^1Cheats are not enabled on this server.\n\""));
		return qfalse;
	}
	if (ent->health <= 0) {
		trap_SendServerCommand(ent - g_entities, va("print \"^1You must be alive to use this command.\n\""));
		return qfalse;
	}
	return qtrue;
}

/*
==================
ConcatArgs
==================
*/
char *ConcatArgs(int start)
{
	int i, c, tlen;
	static char line[MAX_STRING_CHARS];
	int len;
	char arg[MAX_STRING_CHARS];

	len = 0;
	c = trap_Argc();
	for (i = start; i < c; i++) {
		trap_Argv(i, arg, sizeof(arg));
		tlen = strlen(arg);
		if (len + tlen >= MAX_STRING_CHARS - 1) {
			break;
		}
		memcpy(line + len, arg, tlen);
		len += tlen;
		if (i != c - 1) {
			line[len] = ' ';
			len++;
		}
	}

	line[len] = 0;

	return line;
}

/*
==================
ClientNumberFromString

Returns a player number for either a number or name string
Returns -1 if invalid
==================
*/
int ClientNumberFromString(gentity_t * to, char *s)
{
	gclient_t *cl;
	int idnum;
	char s2[MAX_STRING_CHARS];
	char n2[MAX_STRING_CHARS];

	// numeric values are just slot numbers
	if (s[0] >= '0' && s[0] <= '9') {
		idnum = atoi(s);
		if (idnum < 0 || idnum >= level.maxclients) {
			trap_SendServerCommand(to - g_entities, va("print \"^1Bad client slot: %i\n\"", idnum));
			return -1;
		}

		cl = &level.clients[idnum];
		if (cl->pers.connected != CON_CONNECTED) {
			trap_SendServerCommand(to - g_entities, va("print \"^1Client %i is not active\n\"", idnum));
			return -1;
		}
		return idnum;
	}
	// check for a name match
	SanitizeString(s, s2);
	for (idnum = 0, cl = level.clients; idnum < level.maxclients; idnum++, cl++) {
		if (cl->pers.connected != CON_CONNECTED) {
			continue;
		}
		SanitizeString(cl->pers.netname, n2);
		if (!strcmp(n2, s2)) {
			return idnum;
		}
	}

	trap_SendServerCommand(to - g_entities, va("print \"^1User %s is not on the server\n\"", s));
	return -1;
}

/*
==================
Cmd_Give_f

Give items to a client
==================
*/
void Cmd_Give_f(gentity_t * ent)
{
	char *name;
	gitem_t *it;
	int i;
	qboolean give_all;
	gentity_t *it_ent;
	trace_t trace;

	if (!CheatsOk(ent)) {
		return;
	}

	name = ConcatArgs(1);

	if (Q_stricmp(name, "all") == 0)
		give_all = qtrue;
	else
		give_all = qfalse;

	if (give_all || Q_stricmp(name, "health") == 0) {
		ent->health = 100;	// 100 max health ent->client->ps.stats[STAT_MAX_HEALTH];
		if (!give_all)
			return;
	}

	if (give_all || Q_stricmp(name, "weapons") == 0) {
		//Elder: basically it sets all the STAT_WEAPONS bits to 1 EXCEPT for WP_NONE and
		//the initial bit (I don't know what that is)
		//http://www.iota-six.freeserve.co.uk/c/bitwise.htm
		ent->client->ps.stats[STAT_WEAPONS] = (1 << WP_NUM_WEAPONS) - 1 - (1 << WP_NONE);
		// JBravo: so we can drop any of these weapons
		ent->client->uniqueWeapons = 5;
		ent->client->weaponCount[WP_SSG3000] = 1;
		ent->client->weaponCount[WP_MP5] = 1;
		ent->client->weaponCount[WP_M3] = 1;
		ent->client->weaponCount[WP_M4] = 1;
		ent->client->weaponCount[WP_AKIMBO] = 1;
		ent->client->weaponCount[WP_HANDCANNON] = 1;
		if (!give_all)
			return;
	}

	if (give_all || Q_stricmp(name, "items") == 0) {
		// JBravo: for the new items system
		ent->client->ps.stats[STAT_HOLDABLE_ITEM] = (1 << HI_KEVLAR);
		ent->client->ps.stats[STAT_HOLDABLE_ITEM] |= (1 << HI_LASER);
		ent->client->ps.stats[STAT_HOLDABLE_ITEM] |= (1 << HI_SILENCER);
		ent->client->ps.stats[STAT_HOLDABLE_ITEM] |= (1 << HI_BANDOLIER);
		ent->client->ps.stats[STAT_HOLDABLE_ITEM] |= (1 << HI_SLIPPERS);
		if (g_RQ3_haveHelmet.integer) {
			ent->client->ps.stats[STAT_HOLDABLE_ITEM] |= (1 << HI_HELMET);
			ent->client->uniqueItems = 6;
		} else {
			ent->client->uniqueItems = 5;
		}
	}
		
	if (give_all || Q_stricmp(name, "ammo") == 0) {
		for (i = 0; i < MAX_WEAPONS; i++) {
			//Blaze: Give right amount of shots to each gun
			ent->client->ps.ammo[i] = ClipAmountForAmmo(i);
			//Makro - I want clips, dammit !
			Add_Ammo(ent, i, 100, 1);
		}
		//Makro - added grenade + knife
		ent->client->ps.stats[STAT_WEAPONS] |= (1 << WP_GRENADE) | (1 << WP_KNIFE);
		if (!give_all)
			return;
	}
	// spawn a specific item right on the player
	if (!give_all) {
		it = BG_FindItem(name);
		if (!it) {
			return;
		}

		it_ent = G_Spawn();
		VectorCopy(ent->r.currentOrigin, it_ent->s.origin);
		it_ent->classname = it->classname;
		G_SpawnItem(it_ent, it);
		FinishSpawningItem(it_ent);
		memset(&trace, 0, sizeof(trace));
		Touch_Item(it_ent, ent, &trace);
		if (it_ent->inuse) {
			G_FreeEntity(it_ent);
		}
	}
}

void RQ3_Cmd_debugshit (gentity_t * ent)
{
	G_Printf("STAT_HOLDABLE_ITEM is %d, uniqueItems is %d\n", ent->client->ps.stats[STAT_HOLDABLE_ITEM], ent->client->uniqueItems);
}
/*
==================
Cmd_God_f

Sets client to godmode

argv(0) god
==================
*/
void Cmd_God_f(gentity_t * ent)
{
	char *msg;

	if (!CheatsOk(ent)) {
		return;
	}

	ent->flags ^= FL_GODMODE;
	if (!(ent->flags & FL_GODMODE))
		msg = "godmode OFF\n";
	else
		msg = "godmode ON\n";

	trap_SendServerCommand(ent - g_entities, va("print \"%s\"", msg));
}

/*
==================
Cmd_Notarget_f

Sets client to notarget

argv(0) notarget
==================
*/
void Cmd_Notarget_f(gentity_t * ent)
{
	char *msg;

	if (!CheatsOk(ent)) {
		return;
	}

	ent->flags ^= FL_NOTARGET;
	if (!(ent->flags & FL_NOTARGET))
		msg = "notarget OFF\n";
	else
		msg = "notarget ON\n";

	trap_SendServerCommand(ent - g_entities, va("print \"%s\"", msg));
}

/*
==================
Cmd_Noclip_f

argv(0) noclip
==================
*/
void Cmd_Noclip_f(gentity_t * ent)
{
	char *msg;

	if (!CheatsOk(ent)) {
		return;
	}

	if (ent->client->noclip) {
		msg = "noclip OFF\n";
	} else {
		msg = "noclip ON\n";
	}
	ent->client->noclip = !ent->client->noclip;

	trap_SendServerCommand(ent - g_entities, va("print \"%s\"", msg));
}

/*
==================
Cmd_LevelShot_f

This is just to help generate the level pictures
for the menus.  It goes to the intermission immediately
and sends over a command to the client to resize the view,
hide the scoreboard, and take a special screenshot
==================
*/
void Cmd_LevelShot_f(gentity_t * ent)
{
	if (!CheatsOk(ent)) {
		return;
	}
	// doesn't work in single player
	if (g_gametype.integer != 0) {
		trap_SendServerCommand(ent - g_entities, "print \"^1Must be in g_gametype 0 for levelshot\n\"");
		return;
	}

	BeginIntermission();
	trap_SendServerCommand(ent - g_entities, "clientLevelShot");
}

/*
==================
Elder: WTF... this is the wrong description, but it was
like this in the 1.29h source

Cmd_LevelShot_f

This is just to help generate the level pictures
for the menus.  It goes to the intermission immediately
and sends over a command to the client to resize the view,
hide the scoreboard, and take a special screenshot
==================
*/
void Cmd_TeamTask_f(gentity_t * ent)
{
	char userinfo[MAX_INFO_STRING];
	char arg[MAX_TOKEN_CHARS];
	int task;
	int client = ent->client - level.clients;

	if (trap_Argc() != 2) {
		return;
	}
	trap_Argv(1, arg, sizeof(arg));
	task = atoi(arg);

	trap_GetUserinfo(client, userinfo, sizeof(userinfo));
	Info_SetValueForKey(userinfo, "teamtask", va("%d", task));
	trap_SetUserinfo(client, userinfo);
	ClientUserinfoChanged(client);
}

/*
=================
Cmd_Kill_f
=================
*/
void Cmd_Kill_f(gentity_t * ent)
{
	if (ent->client->sess.sessionTeam == TEAM_SPECTATOR) {
		return;
	}
	if (ent->health <= 0) {
		return;
	}
	if (g_gametype.integer == GT_TEAMPLAY && level.lights_camera_action) {
		return;
	}
	ent->flags &= ~FL_GODMODE;
	ent->client->ps.stats[STAT_HEALTH] = ent->health = -999;
	player_die(ent, ent, ent, 100000, MOD_SUICIDE);
}

/*
=================
BroadCastTeamChange

Let everyone know about a team change
=================
*/
void BroadcastTeamChange(gclient_t * client, int oldTeam)
{
// JBravo: change team names if teamplay

	if (g_gametype.integer >= GT_TEAM) {
		if (client->sess.savedTeam == TEAM_RED) {
			trap_SendServerCommand(-1, va("print \"%s" S_COLOR_WHITE " joined %s.\n\"",
						      client->pers.netname, g_RQ3_team1name.string));
		} else if (client->sess.savedTeam == TEAM_BLUE) {
			trap_SendServerCommand(-1, va("print \"%s" S_COLOR_WHITE " joined %s.\n\"",
						      client->pers.netname, g_RQ3_team2name.string));
		} else if (client->sess.savedTeam == TEAM_SPECTATOR && oldTeam != TEAM_SPECTATOR) {
			trap_SendServerCommand(-1, va("print \"%s" S_COLOR_WHITE " left his team.\n\"",
						      client->pers.netname));
		}
	} else {
		if (client->sess.sessionTeam == TEAM_RED) {
			trap_SendServerCommand(-1, va("print \"%s" S_COLOR_WHITE " joined the red team.\n\"",
						      client->pers.netname));
		} else if (client->sess.sessionTeam == TEAM_BLUE) {
			trap_SendServerCommand(-1, va("print \"%s" S_COLOR_WHITE " joined the blue team.\n\"",
						      client->pers.netname));
		} else if (client->sess.sessionTeam == TEAM_SPECTATOR && oldTeam != TEAM_SPECTATOR) {
			trap_SendServerCommand(-1, va("print \"%s" S_COLOR_WHITE " joined the spectators.\n\"",
						      client->pers.netname));
		} else if (client->sess.sessionTeam == TEAM_FREE) {
			trap_SendServerCommand(-1, va("print \"%s" S_COLOR_WHITE " joined the battle.\n\"",
						      client->pers.netname));
		}
	}
}

/*
=================
SetTeam
=================
*/
void SetTeam(gentity_t * ent, char *s)
{
	int team, oldTeam, clientNum;
	gclient_t *client;
	spectatorState_t specState = 0;
	int specClient = 0, teamsave;
	//int teamLeader;

	//
	// see what change is requested
	//
	client = ent->client;
	clientNum = client - level.clients;

	if (g_gametype.integer < GT_TEAM) {
		specClient = 0;
		specState = SPECTATOR_NOT;
	}

	if (!Q_stricmp(s, "scoreboard") || !Q_stricmp(s, "score")) {
		team = TEAM_SPECTATOR;
		specState = SPECTATOR_SCOREBOARD;
	} else if (!Q_stricmp(s, "follow1")) {
		team = TEAM_SPECTATOR;
		specState = SPECTATOR_FOLLOW;
		specClient = -1;
	} else if (!Q_stricmp(s, "follow2")) {
		team = TEAM_SPECTATOR;
		specState = SPECTATOR_FOLLOW;
		specClient = -2;
// JBravo: adding aliases none for spectator, 1 for team red and 2 for team blue.
	} else if (!Q_stricmp(s, "spectator") || !Q_stricmp(s, "s") || !Q_stricmp(s, "none")) {
		team = TEAM_SPECTATOR;
		specState = SPECTATOR_FREE;
	} else if (g_gametype.integer >= GT_TEAM) {
		// if running a team game, assign player to one of the teams
		if (g_gametype.integer < GT_TEAM) {
			specState = SPECTATOR_NOT;
		}
		if (!Q_stricmp(s, "red") || !Q_stricmp(s, "r") || !Q_stricmp(s, "1")) {
			team = TEAM_RED;
		} else if (!Q_stricmp(s, "blue") || !Q_stricmp(s, "b") || !Q_stricmp(s, "2")) {
			team = TEAM_BLUE;
		} else {
			// pick the team with the least number of players
			trap_SendServerCommand(ent->client->ps.clientNum,
				va("print \"^1%s is an illegal team. Putting you on the team with the least number of players.\n\"", s));
			team = PickTeam(clientNum);
		}

		if (g_teamForceBalance.integer) {
			int counts[TEAM_NUM_TEAMS];

			counts[TEAM_BLUE] = TeamCount(ent->client->ps.clientNum, TEAM_BLUE);
			counts[TEAM_RED] = TeamCount(ent->client->ps.clientNum, TEAM_RED);

			// We allow a spread of two
			if (team == TEAM_RED && counts[TEAM_RED] - counts[TEAM_BLUE] > 1) {
				trap_SendServerCommand(ent->client->ps.clientNum,
						       "cp \"Red team has too many players.\n\"");
				return;	// ignore the request
			}
			if (team == TEAM_BLUE && counts[TEAM_BLUE] - counts[TEAM_RED] > 1) {
				trap_SendServerCommand(ent->client->ps.clientNum,
						       "cp \"Blue team has too many players.\n\"");
				return;	// ignore the request
			}
			// It's ok, the team we are switching to has less or same number of players
		}
	} else {
		// force them to spectators if there aren't any spots free
		team = TEAM_FREE;
	}

	// override decision if limiting the players
	if ((g_gametype.integer == GT_TOURNAMENT)
	    && level.numNonSpectatorClients >= 2) {
		team = TEAM_SPECTATOR;
	} else if (g_maxGameClients.integer > 0 && level.numNonSpectatorClients >= g_maxGameClients.integer) {
		team = TEAM_SPECTATOR;
	}
	//
	// decide if we will allow the change
	//
// JBravo: we use the savedTeam var because the player meight be dead.
	if (g_gametype.integer >= GT_TEAM) {
		oldTeam = client->sess.savedTeam;
	} else {
		oldTeam = client->sess.sessionTeam;
	}
	if (team == oldTeam) {
		return;
	}
// JBravo: we want it to be OK to change from FREE to SPECTATOR without dieing.
	if (g_gametype.integer == GT_TEAMPLAY && oldTeam == TEAM_FREE && team == TEAM_SPECTATOR) {
		return;
	}
	//
	// execute the team change
	//
	//sLiCeR: Matchmode referee hear all protection
	if(g_gametype.integer >= GT_TEAM && (oldTeam == TEAM_FREE || oldTeam == TEAM_SPECTATOR) && (team == TEAM_RED || team == TEAM_BLUE))
		ent->client->sess.refHear = qfalse;

	// if the player was dead leave the body
	if (client->ps.stats[STAT_HEALTH] <= 0) {
		CopyToBodyQue(ent);
	}
	// he starts at 'base'
	client->pers.teamState.state = TEAM_BEGIN;

// JBravo: if player is changing from FREE or SPECT. there is no need for violence.
	if (client->sess.sessionTeam != TEAM_SPECTATOR && client->sess.sessionTeam != TEAM_FREE &&
	    client->ps.pm_type == PM_NORMAL) {
		// Kill him (makes sure he loses flags, etc)
		ent->flags &= ~FL_GODMODE;
		ent->client->ps.stats[STAT_HEALTH] = ent->health = 0;
		player_die(ent, ent, ent, 100000, MOD_SUICIDE);
	}

// JBravo: lets set the correct var here.
	if (g_gametype.integer >= GT_TEAM) {
		client->sess.savedTeam = team;
		client->ps.persistant[PERS_SAVEDTEAM] = team;
	} else {
		client->sess.sessionTeam = team;
	}

	//Slicer : Matchmode - If a captain changes team , that team is no longer ready
	if (g_RQ3_matchmode.integer) {
		switch (ent->client->sess.captain) {
		case TEAM_RED:
			level.team1ready = qfalse;
			break;
		case TEAM_BLUE:
			level.team2ready = qfalse;
			break;
		default:
			break;
		}
		ent->client->sess.captain = TEAM_FREE;
		ent->client->sess.sub = TEAM_FREE;
	}
	// they go to the end of the line for tournements
	if (team == TEAM_SPECTATOR) {
		client->sess.spectatorTime = level.time;
	}
// JBravo: not messing with spec system in TP during teamswitches
	if (g_gametype.integer < GT_TEAM) {
		client->sess.spectatorState = specState;
		client->sess.spectatorClient = specClient;
	}

	client->sess.teamLeader = qfalse;
	BroadcastTeamChange(client, oldTeam);

	// get and distribute relevent paramters

// JBravo: save sessionTeam and then set it correctly for the call to ClientUserinfoChanged
//         so the scoreboard will be correct.  Also check for uneven teams.
	if (g_gametype.integer >= GT_TEAM) {
		if (g_RQ3_matchmode.integer && g_RQ3_maxplayers.integer > 0) {
			if (RQ3TeamCount(-1, client->sess.savedTeam) > g_RQ3_maxplayers.integer) // If it overflows max players
				//Make him a sub immeadiatly.
				ent->client->sess.sub = client->sess.savedTeam; 
		}
		CheckForUnevenTeams(ent);
		teamsave = client->sess.sessionTeam;
		client->sess.sessionTeam = client->sess.savedTeam;
		ClientUserinfoChanged(clientNum);
		CalculateRanks();
		client->sess.sessionTeam = teamsave;
		ResetKills(ent);
		client->last_damaged_players[0] = '\0';
		//Slicer: Changing radio gender according to models
		if (client->sess.savedTeam == TEAM_RED)
			client->radioGender = level.team1gender;
		else if (client->sess.savedTeam == TEAM_BLUE)
			client->radioGender = level.team2gender;
	} else {
		ClientUserinfoChanged(clientNum);
		ClientBegin(clientNum);
	}
	if (g_gametype.integer == GT_CTF || (g_gametype.integer == GT_TEAM && client->sess.savedTeam == TEAM_SPECTATOR))
		MakeSpectator (ent);
// JBravo: If the game is in progress, lets spawn players joining.
	if (g_gametype.integer == GT_TEAM && level.team_round_going &&
			(client->sess.savedTeam == TEAM_RED || client->sess.savedTeam == TEAM_BLUE)) {
		client->ps.persistant[PERS_SAVEDTEAM] = client->sess.savedTeam;
		client->ps.persistant[PERS_TEAM] = client->sess.savedTeam;
		client->sess.sessionTeam = client->sess.savedTeam;
		respawn (ent);
	}
}

/*
=================
StopFollowing

If the client being followed leaves the game, or you just want to drop
to free floating spectator mode
=================
*/
void StopFollowing(gentity_t * ent)
{
	vec3_t angle;

	ent->client->ps.persistant[PERS_TEAM] = TEAM_SPECTATOR;
	ent->client->sess.sessionTeam = TEAM_SPECTATOR;
	ent->client->sess.spectatorState = SPECTATOR_FREE;
	ent->client->specMode = SPECTATOR_FREE;
// JBravo: clear zcam also
	ent->client->ps.stats[STAT_RQ3] &= ~RQ3_ZCAM;
	//Slicer - Removing any zoom bits he might have gainned
	Cmd_Unzoom(ent);
	ent->client->ps.pm_flags &= ~PMF_FOLLOW;
	ent->r.svFlags &= ~SVF_BOT;
	ent->client->ps.clientNum = ent - g_entities;
	angle[0] = angle[1] = angle[2] = 0.0;
	SetClientViewAngle(ent, angle);
}

/*
=================
Cmd_Team_f
=================
*/
void Cmd_Team_f(gentity_t * ent)
{
	int oldTeam;
	char s[MAX_TOKEN_CHARS];

	//Makro - moved here
	if (g_gametype.integer >= GT_TEAM) {
		oldTeam = ent->client->sess.savedTeam;
	} else {
		oldTeam = ent->client->sess.sessionTeam;
	}

	if (trap_Argc() != 2) {
// JBravo: lets keep the teamnames right.
		if (g_gametype.integer == GT_TEAMPLAY || g_gametype.integer == GT_TEAM) {
			//oldTeam = ent->client->sess.savedTeam;
			switch (oldTeam) {
			case TEAM_RED:
				trap_SendServerCommand(ent - g_entities,
						       va("print \"You are a member of %s\n\"",
							  g_RQ3_team1name.string));
				break;
			case TEAM_BLUE:
				trap_SendServerCommand(ent - g_entities,
						       va("print \"You are a member of %s\n\"",
							  g_RQ3_team2name.string));
				break;
			case TEAM_SPECTATOR:
			case TEAM_FREE:
				trap_SendServerCommand(ent - g_entities, "print \"You have not joined a team.\n\"");
				break;
			}
		} else if (g_gametype.integer == GT_CTF) {
			switch (oldTeam) {
			case TEAM_RED:
				trap_SendServerCommand(ent - g_entities,
						       va("print \"You are a member of the SILVER team.\n\""));
				break;
			case TEAM_BLUE:
				trap_SendServerCommand(ent - g_entities,
						       va("print \"You are a member of the BLACK team.\n\""));
				break;
			case TEAM_SPECTATOR:
			case TEAM_FREE:
				trap_SendServerCommand(ent - g_entities, "print \"You have not joined a team.\n\"");
				break;
			}
		} else {
			//oldTeam = ent->client->sess.sessionTeam;
			switch (oldTeam) {
			case TEAM_BLUE:
				trap_SendServerCommand(ent - g_entities, "print \"Blue team\n\"");
				break;
			case TEAM_RED:
				trap_SendServerCommand(ent - g_entities, "print \"Red team\n\"");
				break;
			case TEAM_FREE:
				trap_SendServerCommand(ent - g_entities, "print \"Free team\n\"");
				break;
			case TEAM_SPECTATOR:
				trap_SendServerCommand(ent - g_entities, "print \"Spectator team\n\"");
				break;
			}
		}
		return;
	}

	if (ent->client->switchTeamTime > level.time) {
		trap_SendServerCommand(ent - g_entities,
				       "print \"^1May not switch teams more than once per 5 seconds.\n\"");
		return;
	}
	// if they are playing a tournement game, count as a loss
	if ((g_gametype.integer == GT_TOURNAMENT)
	    && ent->client->sess.sessionTeam == TEAM_FREE) {
		ent->client->sess.losses++;
	}

	trap_Argv(1, s, sizeof(s));

	SetTeam(ent, s);

	ent->client->switchTeamTime = level.time + 5000;
}

/*
=================
Cmd_Follow_f
=================
*/
void Cmd_Follow_f(gentity_t * ent)
{
	int i;
	char arg[MAX_TOKEN_CHARS];

	if (trap_Argc() != 2) {
		if (ent->client->sess.spectatorState == SPECTATOR_FOLLOW) {
			StopFollowing(ent);
		}
		return;
	}

	trap_Argv(1, arg, sizeof(arg));
	i = ClientNumberFromString(ent, arg);
	if (i == -1) {
		return;
	}
	// can't follow self
	if (&level.clients[i] == ent->client) {
		return;
	}
	// can't follow another spectator
	if (level.clients[i].sess.sessionTeam == TEAM_SPECTATOR) {
		return;
	}
	// if they are playing a tournement game, count as a loss
	if ((g_gametype.integer == GT_TOURNAMENT)
	    && ent->client->sess.sessionTeam == TEAM_FREE) {
		ent->client->sess.losses++;
	}
	// first set them to spectator
	if (ent->client->sess.sessionTeam != TEAM_SPECTATOR) {
		SetTeam(ent, "spectator");
	}

	ent->client->sess.spectatorState = SPECTATOR_FOLLOW;
	ent->client->specMode = SPECTATOR_FOLLOW;
	ent->client->sess.spectatorClient = i;
}

/*
=================
Cmd_FollowCycle_f
=================
*/
void Cmd_FollowCycle_f(gentity_t * ent, int dir)
{
	int clientnum;
	int original;

	// if they are playing a tournement game, count as a loss
	if ((g_gametype.integer == GT_TOURNAMENT)
	    && ent->client->sess.sessionTeam == TEAM_FREE) {
		ent->client->sess.losses++;
	}
	// first set them to spectator
	// JBravo: Unless we are in teamplay. No need to mess with teams.
	if (ent->client->sess.spectatorState == SPECTATOR_NOT && g_gametype.integer < GT_TEAM) {
		SetTeam(ent, "spectator");
	}

	if (dir != 1 && dir != -1) {
		G_Error("Cmd_FollowCycle_f: bad dir %i", dir);
	}

	clientnum = ent->client->sess.spectatorClient;
	original = clientnum;
	do {
		clientnum += dir;
		if (clientnum >= level.maxclients) {
			clientnum = 0;
		}
		if (clientnum < 0) {
			clientnum = level.maxclients - 1;
		}
		// can only follow connected clients
		if (level.clients[clientnum].pers.connected != CON_CONNECTED) {
			continue;
		}
		// can't follow another spectator
		if (level.clients[clientnum].sess.sessionTeam == TEAM_SPECTATOR) {
			continue;
		}
// JBravo: limchasecam
		if (g_gametype.integer >= GT_TEAM && g_RQ3_limchasecam.integer != 0 &&
		    ent->client->sess.savedTeam != level.clients[clientnum].sess.sessionTeam && ent->client->sess.referee == 0) {
			G_Printf("SavedTeam = (%d)\n",ent->client->sess.savedTeam);
			continue;
		}
		// this is good, we can use it
		ent->client->sess.spectatorClient = clientnum;
		ent->client->sess.spectatorState = SPECTATOR_FOLLOW;
		ent->client->specMode = SPECTATOR_FOLLOW;
		return;
	} while (clientnum != original);

	// leave it where it was
}

/*
==================
G_Say
==================
*/

static void G_SayTo(gentity_t * ent, gentity_t * other, int mode, int color, const char *name, const char *message)
{
	if (!other) {
		return;
	}
	if (!other->inuse) {
		return;
	}
	if (!other->client) {
		return;
	}
	if (other->client->pers.connected != CON_CONNECTED) {
		return;
	}
	if (mode == SAY_TEAM && !OnSameTeam(ent, other) && !ent->client->sess.refHear) { //Slicer: This makes referees read say_team stuff if Hear all
		return;
	}
	// no chatting to players in tournements
	if ((g_gametype.integer == GT_TOURNAMENT)
	    && other->client->sess.sessionTeam == TEAM_FREE && ent->client->sess.sessionTeam != TEAM_FREE &&
		mode != SAY_REF) {
		return;
	}
// JBravo: is the guy ignored ?
	if (IsInIgnoreList(other, ent) && mode != SAY_REF)
		return;
	
	// JBravo: Dead people dont speak to the living...  or so Im told.
	if (!G_PlayerAlive(ent) && G_PlayerAlive(other) &&
		g_gametype.integer == GT_TEAMPLAY && level.team_round_going && mode != SAY_REF)
		return;

	trap_SendServerCommand(other - g_entities, va("%s \"%s%c%c%s\"",
						      mode == SAY_TEAM ? "tchat" : "chat",
						      name, Q_COLOR_ESCAPE, color, message));
}

#define EC		"\x19"

void G_Say(gentity_t * ent, gentity_t * target, int mode, const char *chatText)
{
	int j;
	gentity_t *other;
	int color;
	char name[64];

	// don't let text be too long for malicious reasons
	char text[MAX_SAY_TEXT];
	char location[64];
	int validation;

	// Elder: validate the client
	validation = RQ3_ValidateSay(ent);
	ent->client->idletime = 0;

	if (validation != SAY_OK) {
		// Only send one message for the initial offense
		if (ent->client->pers.sayMuteTime == level.time && ent->client->pers.sayModerated == qfalse) {
			ent->client->pers.sayModerated = qtrue;
			if (validation == SAY_WARNING) {
				trap_SendServerCommand(ent - g_entities,
						       va
						       ("print \"Exceeded message limit - ^3WARNING ^7(%i seconds).\n\"",
							g_RQ3_messageWarnTime.integer));
				G_LogPrintf("Server: %s received a message protect warning (offense %i)\n",
					    ent->client->pers.netname, ent->client->pers.sayWarnings);
			} else if (validation == SAY_BAN) {
				// Don't bother printing if kicked
				if (g_RQ3_messageBanTime.integer > 0)
					trap_SendServerCommand(ent - g_entities,
							       va
							       ("print \"Exceeded message limit - ^1BAN ^7(%i seconds).\n\"",
								g_RQ3_messageBanTime.integer));
				G_LogPrintf("Server: %s received a message protect ban (offense %i)\n",
					    ent->client->pers.netname, ent->client->pers.sayBans);
			}
		}

		return;
	}

// Slicer: DM now has [SPECTATOR]
// JBravo: adding below the [DEAD] tag infront of dead players names.
	switch (mode) {
	default:
	case SAY_ALL:
		if (ent->client->sess.sessionTeam == TEAM_SPECTATOR) {
			if (g_gametype.integer < GT_TEAM)	// DM, SPECTATOR
				Com_sprintf(name, sizeof(name), "[SPECTATOR] %s%c%c" EC ": ", ent->client->pers.netname,
				    Q_COLOR_ESCAPE, COLOR_WHITE);
			else {
				if (ent->client->sess.savedTeam == TEAM_SPECTATOR)
					Com_sprintf(name, sizeof(name), "%s %s%c%c" EC ": ",ent->client->sess.referee ? "[REFEREE]":"[SPECTATOR]", ent->client->pers.netname,
						  Q_COLOR_ESCAPE, COLOR_WHITE);			
				else
					Com_sprintf(name, sizeof(name), "%s %s%c%c" EC ": ",ent->client->sess.referee ? "[REFEREE]":"[DEAD]", ent->client->pers.netname,
						  Q_COLOR_ESCAPE, COLOR_WHITE);
			}
		} else {
			Com_sprintf(name, sizeof(name), "%s%c%c" EC ": ", ent->client->pers.netname, Q_COLOR_ESCAPE,
				    COLOR_WHITE);
		}
		color = COLOR_GREEN;
		break;
	case SAY_TEAM:
		if (ent->client->sess.sessionTeam == TEAM_SPECTATOR) {
			if(g_gametype.integer < GT_TEAM) // DM, SPECTATOR
			Com_sprintf(name, sizeof(name), EC "[SPECTATOR] (%s%c%c" EC ")" EC ": ",
				    ent->client->pers.netname, Q_COLOR_ESCAPE, COLOR_WHITE);
			else {
				if (ent->client->sess.savedTeam == TEAM_SPECTATOR)
					Com_sprintf(name, sizeof(name), EC "%s (%s%c%c" EC ")" EC ": ",ent->client->sess.referee ? "[REFEREE]":"[SPECTATOR]",
						 ent->client->pers.netname, Q_COLOR_ESCAPE, COLOR_WHITE);
				else
					Com_sprintf(name, sizeof(name), EC "[DEAD] (%s%c%c" EC ")" EC ": ",
						 ent->client->pers.netname, Q_COLOR_ESCAPE, COLOR_WHITE);
			}
		} else {
			if (Team_GetLocationMsg(ent, location, sizeof(location)))
				Com_sprintf(name, sizeof(name), EC "(%s%c%c" EC ") (%s)" EC ": ",
					    ent->client->pers.netname, Q_COLOR_ESCAPE, COLOR_WHITE, location);
			else
				Com_sprintf(name, sizeof(name), EC "(%s%c%c" EC ")" EC ": ",
					    ent->client->pers.netname, Q_COLOR_ESCAPE, COLOR_WHITE);
		}
		color = COLOR_CYAN;
		break;
	case SAY_TELL:
		if (target && g_gametype.integer == GT_TEAMPLAY &&
		    target->client->sess.savedTeam == ent->client->sess.savedTeam &&
		    Team_GetLocationMsg(ent, location, sizeof(location)))
			Com_sprintf(name, sizeof(name), EC "[%s%c%c" EC "] (%s)" EC ": ", ent->client->pers.netname,
				    Q_COLOR_ESCAPE, COLOR_WHITE, location);
		else if (target && g_gametype.integer >= GT_TEAM
			 && target->client->sess.sessionTeam == ent->client->sess.sessionTeam
			 && Team_GetLocationMsg(ent, location, sizeof(location)))
			Com_sprintf(name, sizeof(name), EC "[%s%c%c" EC "] (%s)" EC ": ", ent->client->pers.netname,
				    Q_COLOR_ESCAPE, COLOR_WHITE, location);
		else
			Com_sprintf(name, sizeof(name), EC "[%s%c%c" EC "]" EC ": ", ent->client->pers.netname,
				    Q_COLOR_ESCAPE, COLOR_WHITE);
		color = COLOR_MAGENTA;
		break;
	case SAY_REF:
		Com_sprintf(name, sizeof(name), "[REFEREE] %s%c%c" EC ": ", ent->client->pers.netname,
		    Q_COLOR_ESCAPE, COLOR_WHITE);
		color = COLOR_WHITE;
		break;
	}

// JBravo: Parsing % vars here
	if (ent->client->sess.sessionTeam != TEAM_SPECTATOR && mode == SAY_TEAM) {
		ParseSayText(ent, (char *) chatText);
	}

	Q_strncpyz(text, chatText, sizeof(text));

	if (target) {
		G_SayTo(ent, target, mode, color, name, text);
		return;
	}
	// echo the text to the console
	if (g_dedicated.integer) {
		G_Printf("%s%s\n", name, text);
	}
// JBravo: Log it like AQ does
	G_LogPrintf("%s%s\n", name, text);

	// send it to all the apropriate clients
	for (j = 0; j < level.maxclients; j++) {
		//Blaze: Prit out some Debug info
		if (&g_entities[j] == NULL) G_Printf("Ln 1532\n");
		
		other = &g_entities[j];
		G_SayTo(ent, other, mode, color, name, text);
	}
}

/*
==================
Cmd_ay_f
==================
*/
static void Cmd_Say_f(gentity_t * ent, int mode, qboolean arg0)
{
	char *p;
	qboolean normaluser;

	if (trap_Argc() < 2 && !arg0) {
		return;
	}

	if (arg0) {
		p = ConcatArgs(0);
	} else {
		p = ConcatArgs(1);
	}

	//Slicer Matchmode
	if (g_RQ3_matchmode.integer) {
		normaluser = (ent->client->sess.captain == TEAM_FREE && !ent->client->sess.referee);
		switch (g_RQ3_forceteamtalk.integer) {
		case 1: //Only allow say_team when the game hasn't started
			if (level.inGame && normaluser)
				mode = SAY_TEAM;
			break;
		case 2:
			if (normaluser)
				mode = SAY_TEAM;
			break;
		default:
			break;
		}
	}

	G_Say(ent, NULL, mode, p);
}

/*
==================
Cmd_Tell_f
==================
*/
static void Cmd_Tell_f(gentity_t * ent)
{
	int targetNum;
	gentity_t *target;
	char *p;
	char arg[MAX_TOKEN_CHARS];

	if (trap_Argc() < 2) {
		return;
	}

	//Slicer : no TELL FOR TP
	if (!g_gametype.integer < GT_TEAM)
		return;

	trap_Argv(1, arg, sizeof(arg));
	targetNum = atoi(arg);
	if (targetNum < 0 || targetNum >= level.maxclients) {
		return;
	}
	//Blaze: Prit out some Debug info
	if (&g_entities[targetNum] == NULL) G_Printf("Ln 1608\n");

	target = &g_entities[targetNum];
	if (!target || !target->inuse || !target->client) {
		return;
	}

	p = ConcatArgs(2);

	G_LogPrintf("tell: %s to %s: %s\n", ent->client->pers.netname, target->client->pers.netname, p);
	G_Say(ent, target, SAY_TELL, p);
	// don't tell to the player self if it was already directed to this player
	// also don't send the chat back to a bot
	if (ent != target && !(ent->r.svFlags & SVF_BOT)) {
		G_Say(ent, ent, SAY_TELL, p);
	}
}

static void G_VoiceTo(gentity_t * ent, gentity_t * other, int mode, const char *id, qboolean voiceonly)
{
	int color;
	char *cmd;

	if (!other) {
		return;
	}
	if (!other->inuse) {
		return;
	}
	if (!other->client) {
		return;
	}
	if (mode == SAY_TEAM && !OnSameTeam(ent, other)) {
		return;
	}
	// no chatting to players in tournements
	if ((g_gametype.integer == GT_TOURNAMENT)) {
		return;
	}

	if (mode == SAY_TEAM) {
		color = COLOR_CYAN;
		cmd = "vtchat";
	} else if (mode == SAY_TELL) {
		color = COLOR_MAGENTA;
		cmd = "vtell";
	} else {
		color = COLOR_GREEN;
		cmd = "vchat";
	}

	trap_SendServerCommand(other - g_entities, va("%s %d %d %d %s", cmd, voiceonly, ent->s.number, color, id));
}

void G_Voice(gentity_t * ent, gentity_t * target, int mode, const char *id, qboolean voiceonly)
{
	int j;
	gentity_t *other;

	if (g_gametype.integer < GT_TEAM && mode == SAY_TEAM) {
		mode = SAY_ALL;
	}

	if (target) {
		G_VoiceTo(ent, target, mode, id, voiceonly);
		return;
	}
	// echo the text to the console
	if (g_dedicated.integer) {
		G_Printf("voice: %s %s\n", ent->client->pers.netname, id);
	}
	// send it to all the apropriate clients
	for (j = 0; j < level.maxclients; j++) {
		//Blaze: Prit out some Debug info
		if (&g_entities[j] == NULL) G_Printf("Ln 1682\n");

		other = &g_entities[j];
		G_VoiceTo(ent, other, mode, id, voiceonly);
	}
}

/*
==================
Cmd_Voice_f
==================
*/
static void Cmd_Voice_f(gentity_t * ent, int mode, qboolean arg0, qboolean voiceonly)
{
	char *p;

	if (trap_Argc() < 2 && !arg0) {
		return;
	}

	if (arg0) {
		p = ConcatArgs(0);
	} else {
		p = ConcatArgs(1);
	}

	G_Voice(ent, NULL, mode, p, voiceonly);
}

/*
==================
Cmd_VoiceTell_f
==================
*/
static void Cmd_VoiceTell_f(gentity_t * ent, qboolean voiceonly)
{
	int targetNum;
	gentity_t *target;
	char *id;
	char arg[MAX_TOKEN_CHARS];

	if (trap_Argc() < 2) {
		return;
	}

	trap_Argv(1, arg, sizeof(arg));
	targetNum = atoi(arg);
	if (targetNum < 0 || targetNum >= level.maxclients) {
		return;
	}
	//Blaze: Prit out some Debug info
	if (&g_entities[targetNum] == NULL) G_Printf("Ln 1733\n");

	target = &g_entities[targetNum];
	if (!target || !target->inuse || !target->client) {
		return;
	}

	id = ConcatArgs(2);

	G_LogPrintf("vtell: %s to %s: %s\n", ent->client->pers.netname, target->client->pers.netname, id);
	G_Voice(ent, target, SAY_TELL, id, voiceonly);
	// don't tell to the player self if it was already directed to this player
	// also don't send the chat back to a bot
	if (ent != target && !(ent->r.svFlags & SVF_BOT)) {
		G_Voice(ent, ent, SAY_TELL, id, voiceonly);
	}
}

/*
==================
Cmd_VoiceTaunt_f
==================
*/
static void Cmd_VoiceTaunt_f(gentity_t * ent)
{
	gentity_t *who;
	int i;

	if (!ent->client) {
		return;
	}
	// insult someone who just killed you
// JBravo: adding the multiple killed system.
	if (ent->enemy && ent->enemy->client && ent->enemy->client->lastkilled_client[0] == ent) {
		// i am a dead corpse
		if (!(ent->enemy->r.svFlags & SVF_BOT)) {
			G_Voice(ent, ent->enemy, SAY_TELL, VOICECHAT_DEATHINSULT, qfalse);
		}
		if (!(ent->r.svFlags & SVF_BOT)) {
			G_Voice(ent, ent, SAY_TELL, VOICECHAT_DEATHINSULT, qfalse);
		}
		ent->enemy = NULL;
		return;
	}
	// insult someone you just killed
// JBravo: adding the multiple killed system.
	if (ent->client->lastkilled_client[0] != NULL && ent->client->lastkilled_client[0]->s.number >= 0 &&
	    ent->client->lastkilled_client[0]->s.number != ent->s.number) {
		who = ent->client->lastkilled_client[0];
		if (who->client) {
			// who is the person I just killed
			if (who->client->lasthurt_mod == MOD_GAUNTLET) {
				if (!(who->r.svFlags & SVF_BOT)) {
					G_Voice(ent, who, SAY_TELL, VOICECHAT_KILLGAUNTLET, qfalse);	// and I killed them with a gauntlet
				}
				if (!(ent->r.svFlags & SVF_BOT)) {
					G_Voice(ent, ent, SAY_TELL, VOICECHAT_KILLGAUNTLET, qfalse);
				}
			} else {
				if (!(who->r.svFlags & SVF_BOT)) {
					G_Voice(ent, who, SAY_TELL, VOICECHAT_KILLINSULT, qfalse);	// and I killed them with something else
				}
				if (!(ent->r.svFlags & SVF_BOT)) {
					G_Voice(ent, ent, SAY_TELL, VOICECHAT_KILLINSULT, qfalse);
				}
			}
// JBravo: adding the multiple killed system.
			ent->client->lastkilled_client[0] = NULL;
			return;
		}
	}

	if (g_gametype.integer >= GT_TEAM) {
		// praise a team mate who just got a reward
		for (i = 0; i < MAX_CLIENTS; i++) {
			who = g_entities + i;
			if (who->client && who != ent && who->client->sess.sessionTeam == ent->client->sess.sessionTeam) {
				if (who->client->rewardTime > level.time) {
					if (!(who->r.svFlags & SVF_BOT)) {
						G_Voice(ent, who, SAY_TELL, VOICECHAT_PRAISE, qfalse);
					}
					if (!(ent->r.svFlags & SVF_BOT)) {
						G_Voice(ent, ent, SAY_TELL, VOICECHAT_PRAISE, qfalse);
					}
					return;
				}
			}
		}
	}
	// just say something
	G_Voice(ent, NULL, SAY_ALL, VOICECHAT_TAUNT, qfalse);
}

static char *gc_orders[] = {
	"hold your position",
	"hold this position",
	"come here",
	"cover me",
	"guard location",
	"search and destroy",
	"report"
};

void Cmd_GameCommand_f(gentity_t * ent)
{
	int player;
	int order;
	char str[MAX_TOKEN_CHARS];

	trap_Argv(1, str, sizeof(str));
	player = atoi(str);
	trap_Argv(2, str, sizeof(str));
	order = atoi(str);

	if (player < 0 || player >= MAX_CLIENTS) {
		return;
	}
	if (order < 0 || order > sizeof(gc_orders) / sizeof(char *)) {
		return;
	}
	//Blaze: Prit out some Debug info
	if (&g_entities[player] == NULL) G_Printf("Ln 1854\n");

	G_Say(ent, &g_entities[player], SAY_TELL, gc_orders[order]);
	G_Say(ent, ent, SAY_TELL, gc_orders[order]);
}

/*
==================
Cmd_Where_f
==================
*/
void Cmd_Where_f(gentity_t * ent)
{
	trap_SendServerCommand(ent - g_entities, va("print \"%s\n\"", vtos(ent->s.origin)));
}

static const char *gameNames[] = {
	"Free For All",
	"Tournament",
	"Single Player",
	"Team Deathmatch",

// JBravo: duh ;)
	"RQ3 teamplay",
	"Capture the Briefcase",
	"One Flag CTF",
	"Overload",
	"Harvester"
};

/*
==================
Cmd_CallVote_f
==================
*/
void Cmd_CallVote_f(gentity_t * ent)
{
	int i;
	char arg1[MAX_STRING_TOKENS];
	char arg2[MAX_STRING_TOKENS];

	if (!g_allowVote.integer) {
		trap_SendServerCommand(ent - g_entities, "print \"^1Voting not allowed here.\n\"");
		return;
	}
	if (level.voteTime) {
		trap_SendServerCommand(ent - g_entities, "print \"^1A vote is already in progress.\n\"");
		return;
	}
	//Makro - replaced the constant with a cvar
	if (ent->client->pers.voteCount >= g_RQ3_maxClientVotes.integer) {
		//Makro - added cvar info
		trap_SendServerCommand(ent - g_entities, va("print \"^1You have called the maximum number of votes (%i).\n\"", g_RQ3_maxClientVotes.integer));
		return;
	}
// JBravo: Lets allow spectators to vote in TP
	if (ent->client->sess.sessionTeam == TEAM_SPECTATOR && g_gametype.integer < GT_TEAM) {
		trap_SendServerCommand(ent - g_entities, "print \"^1Not allowed to call a vote as spectator.\n\"");
		return;
	}
		//Slicer Matchmode
	if(g_RQ3_matchmode.integer && ent->client->sess.captain == TEAM_FREE) {
		trap_SendServerCommand(ent - g_entities, "print \"^1Only team Captains can start a vote.\n\"");	
		return;
	}
	// make sure it is a valid command to vote on
	trap_Argv(1, arg1, sizeof(arg1));
	trap_Argv(2, arg2, sizeof(arg2));

	if (strchr(arg1, ';') || strchr(arg2, ';')) {
		trap_SendServerCommand(ent - g_entities, "print \"^1Invalid vote string.\n\"");
		return;
	}
	
	if (!Q_stricmp(arg1, "cyclemap")) {	
	} else if (!Q_stricmp(arg1, "map")) {
	} else if (!Q_stricmp(arg1, "g_gametype")) {
	} else if (!Q_stricmp(arg1, "kick")) {
	} else if (!Q_stricmp(arg1, "clientkick")) {
	} else {
		if(g_RQ3_matchmode.integer) {
			if (!Q_stricmp(arg1, "resetmatch")) {
			} else if (!Q_stricmp(arg1, "clearscores")) {
			} else {
					trap_SendServerCommand(ent - g_entities, "print \"^1Invalid vote command.\n\"");
					trap_SendServerCommand(ent - g_entities,"print \"Valid vote commands are: cyclemap, map <mapname>, g_gametype <n>, kick <player>, clientkick <clientnum>,clearscores,resetmatch.\n\"");
					return;
			}
		}
		else {
			trap_SendServerCommand(ent - g_entities, "print \"^1Invalid vote command.\n\"");
			trap_SendServerCommand(ent - g_entities, 
				"print \"Valid vote commands are: cyclemap, map <mapname>, g_gametype <n>, kick <player>, and clientkick <clientnum>.\n\"");
		return;
		}
	}

	// if there is still a vote to be executed
	if (level.voteExecuteTime) {
		level.voteExecuteTime = 0;
		trap_SendConsoleCommand(EXEC_APPEND, va("%s\n", level.voteString));
	}
	// special case for g_gametype, check for bad values
	if (!Q_stricmp(arg1, "g_gametype")) {
		i = atoi(arg2);
		if (i != GT_FFA && i != GT_TEAMPLAY && i != GT_CTF && i != GT_TEAM) {
			trap_SendServerCommand(ent - g_entities, "print \"^1Invalid gametype. Valid gametypes are 0, 3, 4 and 5.\n\"");
			return;
		}

		Com_sprintf(level.voteString, sizeof(level.voteString), "%s %d", arg1, i);
		Com_sprintf(level.voteDisplayString, sizeof(level.voteDisplayString), "%s %s", arg1, gameNames[i]);
	} else if (!Q_stricmp(arg1, "map")) {
		// special case for map changes, we want to reset the nextmap setting
		// this allows a player to change maps, but not upset the map rotation

		if ( !G_FileExists(va("maps/%s.bsp", arg2)) ) {
			trap_SendServerCommand(ent - g_entities, va("print \"^1The map %s does not exist.\n\"", arg2));
			return;
		}

		// NiceAss: Talk to NiceAss before you fix this crappy hack =)
		if ( !G_FileSearch( va("scripts/%s.arena", arg2), "rq3ctb" ) && g_gametype.integer == GT_CTF ) {
			trap_SendServerCommand(ent - g_entities, va("print \"^1The map %s does not support CTB.\n\"", arg2));
			return;
		}

		Com_sprintf(level.voteString, sizeof(level.voteString), "%s", arg1);
		Com_sprintf(level.voteMap, sizeof(level.voteMap), "%s", arg2);
		Com_sprintf(level.voteDisplayString, sizeof(level.voteDisplayString), "%s %s", level.voteString, level.voteMap);

	} else if (!Q_stricmp(arg1, "cyclemap")) {
		Com_sprintf(level.voteString, sizeof(level.voteString), "cyclemap");
		Com_sprintf(level.voteDisplayString, sizeof(level.voteDisplayString), "%s", level.voteString);
	} else {
		Com_sprintf(level.voteString, sizeof(level.voteString), "%s \"%s\"", arg1, arg2);
		Com_sprintf(level.voteDisplayString, sizeof(level.voteDisplayString), "%s", level.voteString);
	}

	trap_SendServerCommand(-1, va("print \"%s^7 called a vote.\n\"", ent->client->pers.netname));

	// start the voting, the caller autoamtically votes yes
	level.voteTime = level.time;
	level.voteYes = 1;
	level.voteNo = 0;

	for (i = 0; i < level.maxclients; i++) {
		level.clients[i].ps.eFlags &= ~EF_VOTED;
	}
	ent->client->ps.eFlags |= EF_VOTED;
	//Makro - added
	ent->client->pers.voteCount++;

	trap_SetConfigstring(CS_VOTE_TIME, va("%i", level.voteTime));
	trap_SetConfigstring(CS_VOTE_STRING, level.voteDisplayString);
	trap_SetConfigstring(CS_VOTE_YES, va("%i", level.voteYes));
	trap_SetConfigstring(CS_VOTE_NO, va("%i", level.voteNo));
}

/*
==================
Cmd_Vote_f
==================
*/
void Cmd_Vote_f(gentity_t * ent)
{
	char msg[64];

	if (!level.voteTime) {
		trap_SendServerCommand(ent - g_entities, "print \"No vote in progress.\n\"");
		return;
	}
	if (ent->client->ps.eFlags & EF_VOTED) {
		trap_SendServerCommand(ent - g_entities, "print \"^1Vote already cast.\n\"");
		return;
	}
	//Makro - allow spectators to vote in TP
	if (ent->client->sess.sessionTeam == TEAM_SPECTATOR && g_gametype.integer < GT_TEAM) {
		trap_SendServerCommand(ent - g_entities, "print \"^1Not allowed to vote as spectator.\n\"");
		return;
	}
		//Slicer Matchmode
	if(g_RQ3_matchmode.integer && ent->client->sess.captain == TEAM_FREE) {
		trap_SendServerCommand(ent - g_entities, "print \"^1Only team Captains vote.\n\"");	
		return;
	}
	trap_SendServerCommand(ent - g_entities, "print \"Vote cast.\n\"");

	ent->client->ps.eFlags |= EF_VOTED;

	trap_Argv(1, msg, sizeof(msg));

	if (msg[0] == 'y' || msg[1] == 'Y' || msg[1] == '1') {
		level.voteYes++;
		trap_SetConfigstring(CS_VOTE_YES, va("%i", level.voteYes));
	} else {
		level.voteNo++;
		trap_SetConfigstring(CS_VOTE_NO, va("%i", level.voteNo));
	}

	// a majority will be determined in CheckVote, which will also account
	// for players entering or leaving
}

/*
==================
Cmd_CallTeamVote_f
==================
*/
void Cmd_CallTeamVote_f(gentity_t * ent)
{
	int i, team, cs_offset;
	char arg1[MAX_STRING_TOKENS];
	char arg2[MAX_STRING_TOKENS];

// JBravo: not wanted for TP
	if (g_gametype.integer >= GT_TEAM)
		return;

	team = ent->client->sess.sessionTeam;
	if (team == TEAM_RED)
		cs_offset = 0;
	else if (team == TEAM_BLUE)
		cs_offset = 1;
	else
		return;

	if (!g_allowVote.integer) {
		trap_SendServerCommand(ent - g_entities, "print \"^1Voting not allowed here.\n\"");
		return;
	}

	if (level.teamVoteTime[cs_offset]) {
		trap_SendServerCommand(ent - g_entities, "print \"^1A team vote is already in progress.\n\"");
		return;
	}
	//Makro - replaced the constant with a cvar
	if (ent->client->pers.teamVoteCount >= g_RQ3_maxClientVotes.integer) {
		//Makro - added cvar info
		trap_SendServerCommand(ent - g_entities,
				       va("print \"^1You have called the maximum number of team votes (%i).\n\"", g_RQ3_maxClientVotes.integer));
		return;
	}
	if (ent->client->sess.sessionTeam == TEAM_SPECTATOR) {
		trap_SendServerCommand(ent - g_entities, "print \"^1Not allowed to call a vote as spectator.\n\"");
		return;
	}
	// make sure it is a valid command to vote on
	trap_Argv(1, arg1, sizeof(arg1));
	arg2[0] = '\0';
	for (i = 2; i < trap_Argc(); i++) {
		if (i > 2)
			strcat(arg2, " ");
		trap_Argv(i, &arg2[strlen(arg2)], sizeof(arg2) - strlen(arg2));
	}

	if (strchr(arg1, ';') || strchr(arg2, ';')) {
		trap_SendServerCommand(ent - g_entities, "print \"^1Invalid vote string.\n\"");
		return;
	}

	if (!Q_stricmp(arg1, "leader")) {
		char netname[MAX_NETNAME], leader[MAX_NETNAME];

		if (!arg2[0]) {
			i = ent->client->ps.clientNum;
		} else {
			// numeric values are just slot numbers
			for (i = 0; i < 3; i++) {
				if (!arg2[i] || arg2[i] < '0' || arg2[i] > '9')
					break;
			}
			if (i >= 3 || !arg2[i]) {
				i = atoi(arg2);
				if (i < 0 || i >= level.maxclients) {
					trap_SendServerCommand(ent - g_entities,
							       va("print \"^1Bad client slot: %i\n\"", i));
					return;
				}

				if (!g_entities[i].inuse) {
					trap_SendServerCommand(ent - g_entities,
							       va("print \"^1Client %i is not active\n\"", i));
					return;
				}
			} else {
				Q_strncpyz(leader, arg2, sizeof(leader));
				Q_CleanStr(leader);
				for (i = 0; i < level.maxclients; i++) {
					if (level.clients[i].pers.connected == CON_DISCONNECTED)
						continue;
					if (level.clients[i].sess.sessionTeam != team)
						continue;
					Q_strncpyz(netname, level.clients[i].pers.netname, sizeof(netname));
					Q_CleanStr(netname);
					if (!Q_stricmp(netname, leader)) {
						break;
					}
				}
				if (i >= level.maxclients) {
					trap_SendServerCommand(ent - g_entities,
							       va("print \"^1%s is not a valid player on your team.\n\"",
								  arg2));
					return;
				}
			}
		}
		Com_sprintf(arg2, sizeof(arg2), "%d", i);
	} else {
		trap_SendServerCommand(ent - g_entities, "print \"^1Invalid vote string.\n\"");
		trap_SendServerCommand(ent - g_entities, "print \"Team vote commands are: leader <player>.\n\"");
		return;
	}

	Com_sprintf(level.teamVoteString[cs_offset], sizeof(level.teamVoteString[cs_offset]), "%s %s", arg1, arg2);

	for (i = 0; i < level.maxclients; i++) {
		if (level.clients[i].pers.connected == CON_DISCONNECTED)
			continue;
		if (level.clients[i].sess.sessionTeam == team)
			trap_SendServerCommand(i,
					       va("print \"%s^7 called a team vote.\n\"", ent->client->pers.netname));
	}

	// start the voting, the caller autoamtically votes yes
	level.teamVoteTime[cs_offset] = level.time;
	level.teamVoteYes[cs_offset] = 1;
	level.teamVoteNo[cs_offset] = 0;

	for (i = 0; i < level.maxclients; i++) {
		if (level.clients[i].sess.sessionTeam == team)
			level.clients[i].ps.eFlags &= ~EF_TEAMVOTED;
	}
	ent->client->ps.eFlags |= EF_TEAMVOTED;
	//Makro - added
	ent->client->pers.teamVoteCount++;


	trap_SetConfigstring(CS_TEAMVOTE_TIME + cs_offset, va("%i", level.teamVoteTime[cs_offset]));
	trap_SetConfigstring(CS_TEAMVOTE_STRING + cs_offset, level.teamVoteString[cs_offset]);
	trap_SetConfigstring(CS_TEAMVOTE_YES + cs_offset, va("%i", level.teamVoteYes[cs_offset]));
	trap_SetConfigstring(CS_TEAMVOTE_NO + cs_offset, va("%i", level.teamVoteNo[cs_offset]));
}

/*
==================
Cmd_TeamVote_f
==================
*/
void Cmd_TeamVote_f(gentity_t * ent)
{
	int team, cs_offset;
	char msg[64];

	team = ent->client->sess.sessionTeam;
	if (team == TEAM_RED)
		cs_offset = 0;
	else if (team == TEAM_BLUE)
		cs_offset = 1;
	else
		return;

	if (!level.teamVoteTime[cs_offset]) {
		trap_SendServerCommand(ent - g_entities, "print \"No team vote in progress.\n\"");
		return;
	}
	if (ent->client->ps.eFlags & EF_TEAMVOTED) {
		trap_SendServerCommand(ent - g_entities, "print \"Team vote already cast.\n\"");
		return;
	}
	if (ent->client->sess.sessionTeam == TEAM_SPECTATOR) {
		trap_SendServerCommand(ent - g_entities, "print \"Not allowed to vote as spectator.\n\"");
		return;
	}

	trap_SendServerCommand(ent - g_entities, "print \"Team vote cast.\n\"");

	ent->client->ps.eFlags |= EF_TEAMVOTED;

	trap_Argv(1, msg, sizeof(msg));

	if (msg[0] == 'y' || msg[1] == 'Y' || msg[1] == '1') {
		level.teamVoteYes[cs_offset]++;
		trap_SetConfigstring(CS_TEAMVOTE_YES + cs_offset, va("%i", level.teamVoteYes[cs_offset]));
	} else {
		level.teamVoteNo[cs_offset]++;
		trap_SetConfigstring(CS_TEAMVOTE_NO + cs_offset, va("%i", level.teamVoteNo[cs_offset]));
	}

	// a majority will be determined in TeamCheckVote, which will also account
	// for players entering or leaving
}

/*
=================
Cmd_SetViewpos_f
=================
*/
void Cmd_SetViewpos_f(gentity_t * ent)
{
	vec3_t origin, angles;
	char buffer[MAX_TOKEN_CHARS];
	int i;

	if (!g_cheats.integer) {
		trap_SendServerCommand(ent - g_entities, va("print \"^1Cheats are not enabled on this server.\n\""));
		return;
	}
	if (trap_Argc() != 5) {
		trap_SendServerCommand(ent - g_entities, va("print \"usage: setviewpos x y z yaw\n\""));
		return;
	}

	VectorClear(angles);
	for (i = 0; i < 3; i++) {
		trap_Argv(i + 1, buffer, sizeof(buffer));
		origin[i] = atof(buffer);
	}

	trap_Argv(4, buffer, sizeof(buffer));
	angles[YAW] = atof(buffer);

	TeleportPlayer(ent, origin, angles);
}

/*
=================
Cmd_Stats_f
=================
*/
void Cmd_Stats_f(gentity_t * ent)
{
}

/*
=================
 Cmd_Bandage
 Added by Blaze
=================
*/
void Cmd_Bandage(gentity_t * ent)
{
	if (ent->client->ps.pm_type == PM_SPECTATOR)
		return;

	//Elder: added so you can't "rebandage"
	if (ent->client->ps.weaponstate == WEAPON_BANDAGING) {
		trap_SendServerCommand(ent - g_entities, va("print \"You are already bandaging!\n\""));
		return;
	}

	if ((ent->client->ps.stats[STAT_RQ3] & RQ3_BANDAGE_NEED) == RQ3_BANDAGE_NEED ||
	    (ent->client->ps.stats[STAT_RQ3] & RQ3_LEGDAMAGE) == RQ3_LEGDAMAGE) {
		//Elder: remove zoom bits
		Cmd_Unzoom(ent);

		//Elder: drop the primed grenade
		//Moved weapon switch to bg_pmove.c
		if (ent->client->ps.weapon == WP_GRENADE && ent->client->ps.weaponstate == WEAPON_COCKED) {
			FireWeapon(ent);
			ent->client->ps.ammo[WP_GRENADE]--;
			//Makro - if this is the last grenade, remove the weapon from the inventory
			if (ent->client->ps.ammo[WP_GRENADE] <= 0) {
				ent->client->ps.stats[STAT_WEAPONS] &= ~(1 << WP_GRENADE);
			}
		}
//slicer
		ent->client->ps.weaponstate = WEAPON_BANDAGING;

		if (ent->client->ps.weapon == WP_KNIFE
		    && !(ent->client->ps.persistant[PERS_WEAPONMODES] & RQ3_KNIFEMODE)) {
			ent->client->ps.generic1 = ((ent->client->ps.generic1 & ANIM_TOGGLEBIT)
						    ^ ANIM_TOGGLEBIT) | WP_ANIM_THROWDISARM;
		} else {
			ent->client->ps.generic1 = ((ent->client->ps.generic1 & ANIM_TOGGLEBIT)
						    ^ ANIM_TOGGLEBIT) | WP_ANIM_DISARM;
		}

		ent->client->ps.weaponTime += BLEED_BANDAGE_TIME;
		ent->client->bleedtick = 4;
	} else {
		trap_SendServerCommand(ent - g_entities, va("print \"No need to bandage.\n\""));
	}
}

/*
==================
 Opendoor Function
 Added by Blaze
 Checks to see if they are near a door, if so open it
==================
*/
void Cmd_OpenDoor(gentity_t * ent)
{
	//Use_BinaryMover( ent->parent, ent, other );
	gentity_t *door = NULL;

	//Don't open doors if dead or spectating
	if (ent->client->ps.stats[STAT_HEALTH] <= 0 || ent->client->ps.pm_type == PM_SPECTATOR)
		return;

	while ((door = findradius(door, ent->r.currentOrigin, 100)) != NULL) {
		if (Q_stricmp(door->classname, "func_door_rotating") == 0) {
			ent->client->openDoor = qtrue;
			ent->client->openDoorTime = level.time;
		} else if (Q_stricmp(door->classname, "func_door") == 0) {
			ent->client->openDoor = qtrue;
			ent->client->openDoorTime = level.time;
		}
	}
}

/* Hawkins. Reaction weapon command */
void Cmd_Weapon(gentity_t * ent)
{

	ent->client->weapon_attempts--;
	if (ent->client->weapon_attempts < 0)
		ent->client->weapon_attempts = 0;

	if (ent->client->ps.pm_type == PM_SPECTATOR)
		return;

	if (ent->client->ps.weaponstate == WEAPON_BANDAGING) {
		if (!ent->client->weapon_after_bandage_warned) {
			ent->client->weapon_after_bandage_warned = qtrue;
			G_SendClientSpec(ent,
					 va("print \"You'll get to your weapon when you are finished bandaging!\n\""));
		}
		ent->client->weapon_attempts++;
		return;
	}
	ent->client->weapon_after_bandage_warned = qfalse;

	if (ent->client->ps.weaponstate == WEAPON_RELOADING ||
	    ent->client->ps.weaponstate == WEAPON_FIRING ||
	    ent->client->ps.weaponstate == WEAPON_DROPPING || ent->client->ps.weaponstate == WEAPON_RAISING) {
		ent->client->weapon_attempts++;
		return;
	}
	//Elder: added brackets, and-ops and not-ops instead of logical ops
	switch (ent->s.weapon) {
	case WP_SSG3000:
		if ((ent->client->ps.stats[STAT_RQ3] & RQ3_ZOOM_LOW) == RQ3_ZOOM_LOW &&
		    (ent->client->ps.stats[STAT_RQ3] & RQ3_ZOOM_MED) == RQ3_ZOOM_MED) {
			//Elder: zoom 1x
			ent->client->ps.stats[STAT_RQ3] &= ~RQ3_ZOOM_LOW;
			ent->client->ps.stats[STAT_RQ3] &= ~RQ3_ZOOM_MED;
		} else if ((ent->client->ps.stats[STAT_RQ3] & RQ3_ZOOM_MED) == RQ3_ZOOM_MED) {
			//Elder: zoom 6x
			ent->client->ps.stats[STAT_RQ3] |= RQ3_ZOOM_LOW;
		} else if ((ent->client->ps.stats[STAT_RQ3] & RQ3_ZOOM_LOW) == RQ3_ZOOM_LOW) {
			//Elder: zoom 4x
			ent->client->ps.stats[STAT_RQ3] |= RQ3_ZOOM_MED;
			ent->client->ps.stats[STAT_RQ3] &= ~RQ3_ZOOM_LOW;
		} else {
			//Elder: zoom 2x
			ent->client->ps.stats[STAT_RQ3] |= RQ3_ZOOM_LOW;
		}

		G_Sound(ent, CHAN_ITEM, G_SoundIndex("sound/misc/lens.wav"));
		break;
	case WP_PISTOL:
		// semiauto toggle (increase accuracy)
		if ((ent->client->ps.persistant[PERS_WEAPONMODES] & RQ3_MK23MODE) == RQ3_MK23MODE) {
			ent->client->ps.persistant[PERS_WEAPONMODES] &= ~RQ3_MK23MODE;
			G_SendClientSpec(ent, va("print \"Switched to full automatic.\n\""));
		} else {
			ent->client->ps.persistant[PERS_WEAPONMODES] |= RQ3_MK23MODE;
			G_SendClientSpec(ent, va("print \"Switched to semi-automatic.\n\""));
		}
		G_Sound(ent, CHAN_ITEM, G_SoundIndex("sound/misc/click.wav"));
		break;
	case WP_M4:
		// 3rb/full auto toggle
		if ((ent->client->ps.persistant[PERS_WEAPONMODES] & RQ3_M4MODE) == RQ3_M4MODE) {
			ent->client->ps.persistant[PERS_WEAPONMODES] &= ~RQ3_M4MODE;
			G_SendClientSpec(ent, va("print \"Switched to full automatic.\n\""));
		} else {
			ent->client->ps.persistant[PERS_WEAPONMODES] |= RQ3_M4MODE;
			G_SendClientSpec(ent, va("print \"Switched to 3 round burst.\n\""));
		}
		G_Sound(ent, CHAN_ITEM, G_SoundIndex("sound/misc/click.wav"));
		break;
	case WP_MP5:
		// 3rb/full auto toggle
		if ((ent->client->ps.persistant[PERS_WEAPONMODES] & RQ3_MP5MODE) == RQ3_MP5MODE) {
			ent->client->ps.persistant[PERS_WEAPONMODES] &= ~RQ3_MP5MODE;
			G_SendClientSpec(ent, va("print \"Switched to full automatic.\n\""));
		} else {
			ent->client->ps.persistant[PERS_WEAPONMODES] |= RQ3_MP5MODE;
			G_SendClientSpec(ent, va("print \"Switched to 3 round burst.\n\""));
		}
		G_Sound(ent, CHAN_ITEM, G_SoundIndex("sound/misc/click.wav"));
		break;
	case WP_KNIFE:
		// NiceAss: weapon animation/state check before the mode switch.
		if (ent->client->ps.weaponstate != WEAPON_READY)
			break;

		// toggle throwing/slashing
		if ((ent->client->ps.persistant[PERS_WEAPONMODES] & RQ3_KNIFEMODE) == RQ3_KNIFEMODE) {
			//Elder: added
			ent->client->ps.persistant[PERS_WEAPONMODES] &= ~RQ3_KNIFEMODE;
			G_SendClientSpec(ent, va("print \"Switched to throwing.\n\""));
			// Niceass: Animations added
			ent->client->ps.weaponstate = WEAPON_MODECHANGE;
			ent->client->ps.weaponTime = 550;
			ent->client->ps.generic1 =
			    ((ent->client->ps.generic1 & ANIM_TOGGLEBIT) ^ ANIM_TOGGLEBIT) | WP_ANIM_EXTRA1;
		} else {
			//Elder: we're gonna use this to flag throw or slash with the knife
			ent->client->ps.persistant[PERS_WEAPONMODES] |= RQ3_KNIFEMODE;
			G_SendClientSpec(ent, va("print \"Switched to slashing.\n\""));
			// Niceass: Animations added
			ent->client->ps.weaponstate = WEAPON_MODECHANGE;
			ent->client->ps.weaponTime = 550;
			ent->client->ps.generic1 =
			    ((ent->client->ps.generic1 & ANIM_TOGGLEBIT) ^ ANIM_TOGGLEBIT) | WP_ANIM_EXTRA2;
		}
		break;
	case WP_HANDCANNON:
		// nothing
		break;
	case WP_M3:
		// nothing
		break;
	case WP_AKIMBO:
		// nothing
		break;
	case WP_GRENADE:
// JBravo: Fix for uninitialized grenade mode
		if ((ent->client->ps.persistant[PERS_WEAPONMODES] & RQ3_GRENSHORT) == 0 &&
		    (ent->client->ps.persistant[PERS_WEAPONMODES] & RQ3_GRENMED) == 0) {
			ent->client->ps.persistant[PERS_WEAPONMODES] |= RQ3_GRENSHORT;
			ent->client->ps.persistant[PERS_WEAPONMODES] &= ~RQ3_GRENMED;
		}
		// short, medium, long throws
		if ((ent->client->ps.persistant[PERS_WEAPONMODES] & RQ3_GRENSHORT) == RQ3_GRENSHORT && (ent->client->ps.persistant[PERS_WEAPONMODES] & RQ3_GRENMED) == RQ3_GRENMED) {	//Going into Short
			ent->client->ps.persistant[PERS_WEAPONMODES] |= RQ3_GRENSHORT;	//Set the short flag
			ent->client->ps.persistant[PERS_WEAPONMODES] &= ~RQ3_GRENMED;	//unset the med flag
			G_SendClientSpec(ent, va("print \"Grenade set for short range throw.\n\""));
		} else if ((ent->client->ps.persistant[PERS_WEAPONMODES] & RQ3_GRENSHORT) == RQ3_GRENSHORT) {	//Going into Med
			ent->client->ps.persistant[PERS_WEAPONMODES] &= ~RQ3_GRENSHORT;	//unset the short flag
			ent->client->ps.persistant[PERS_WEAPONMODES] |= RQ3_GRENMED;	//Set the med flag
			G_SendClientSpec(ent, va("print \"Grenade set for medium range throw.\n\""));
		} else if ((ent->client->ps.persistant[PERS_WEAPONMODES] & RQ3_GRENMED) == RQ3_GRENMED) {	//Going into Long
			ent->client->ps.persistant[PERS_WEAPONMODES] |= RQ3_GRENSHORT;	//Set the short flag
			ent->client->ps.persistant[PERS_WEAPONMODES] |= RQ3_GRENMED;	//Set the med flag
			G_SendClientSpec(ent, va("print \"Grenade set for long range throw.\n\""));
		}
		//Elder: added
		else {
			G_Printf("Cmd_Weapon_f: Received bad grenade toggle\n");
		}
		break;
	default:
		break;
	}
//Makro - changed all the trap_SendServerCommand prints to G_SendClientSpec prints
//so that players spectating this client get his messages, too
}

//Slicer
void Cmd_New_Weapon(gentity_t * ent)
{

	ent->client->weapon_attempts++;
	if (ent->client->weapon_attempts == 1)
		Cmd_Weapon(ent);
}

// Hawkins make sure spread comes back
void Cmd_Unzoom(gentity_t * ent)
{
	// Freud, play zooming sounds for unzoom
	if (ent->client->ps.stats[STAT_RQ3] & RQ3_ZOOM_LOW ||
			ent->client->ps.stats[STAT_RQ3] & RQ3_ZOOM_MED)
		G_Sound(ent, CHAN_ITEM, G_SoundIndex("sound/misc/lens.wav"));

	ent->client->ps.stats[STAT_RQ3] &= ~RQ3_ZOOM_LOW;
	ent->client->ps.stats[STAT_RQ3] &= ~RQ3_ZOOM_MED;
}

/*
=================
Cmd_DropWeapon_f XRAY FMJ
=================
*/
void Cmd_DropWeapon_f(gentity_t * ent)
{

	if (ent->client->ps.pm_type == PM_SPECTATOR)
		return;
// JBravo: no dropping stuff while bandaging. Fix dedicated to GoKu and JesterRace :)
	if (ent->client->ps.weaponstate == WEAPON_BANDAGING) {
		trap_SendServerCommand(ent - g_entities, va("print \"You are too busy bandaging...\n\""));
		return;
	}
	//Elder: remove zoom bits
	Cmd_Unzoom(ent);
	//Throwing away return value here; high precedence weapon drop
	ThrowWeapon(ent, qtrue);
}

/*
=================
Cmd_DropItem_f
=================
*/
void Cmd_DropItem_f(gentity_t * ent)
{
	if (ent->client->ps.pm_type == PM_SPECTATOR)
		return;

// JBravo: no dropping stuff while bandaging. Fix dedicated to GoKu and JesterRace :)
// Turns out they are full of shit... :)
/*	if (ent->client->ps.weaponstate == WEAPON_BANDAGING) {
		trap_SendServerCommand(ent - g_entities, va("print \"You are too busy bandaging...\n\""));
		return;
	} */

	if (ent->client->ps.stats[STAT_HOLDABLE_ITEM]) {
		//Elder: reset item totals if using bandolier
		//JBravo: New multiple items code.
		if (ent->client->ps.stats[STAT_HOLDABLE_ITEM] & (1 << HI_BANDOLIER)) {
			if (ent->client->numClips[WP_SSG3000] > RQ3_SSG3000_EXTRA_AMMO)
				ent->client->numClips[WP_SSG3000] = RQ3_SSG3000_EXTRA_AMMO;
			if (ent->client->numClips[WP_M3] > RQ3_M3_EXTRA_AMMO)
				ent->client->numClips[WP_M3] = RQ3_M3_EXTRA_AMMO;
			if (ent->client->numClips[WP_M4] > RQ3_M4_EXTRA_AMMO)
				ent->client->numClips[WP_M4] = RQ3_M4_EXTRA_AMMO;
			if (ent->client->numClips[WP_MP5] > RQ3_MP5_EXTRA_AMMO)
				ent->client->numClips[WP_MP5] = RQ3_MP5_EXTRA_AMMO;
			if (ent->client->numClips[WP_KNIFE] > RQ3_KNIVES_EXTRA_AMMO)
				ent->client->numClips[WP_KNIFE] = RQ3_KNIVES_EXTRA_AMMO;
			if (ent->client->numClips[WP_AKIMBO] > RQ3_AKIMBO_EXTRA_AMMO)
				ent->client->numClips[WP_AKIMBO] = RQ3_AKIMBO_EXTRA_AMMO;
			if (ent->client->ps.ammo[WP_GRENADE] > 0)
				ent->client->ps.ammo[WP_GRENADE] = 0;
			if (ent->client->numClips[WP_PISTOL] > 1)
				ent->client->numClips[WP_PISTOL] = 1;
			if (ent->client->uniqueWeapons > g_RQ3_maxWeapons.integer) {
				Cmd_Unzoom(ent);
				ThrowWeapon(ent, qtrue);
			}
		}
		//Force laser off
		else if (ent->client->ps.stats[STAT_HOLDABLE_ITEM] & (1 << HI_LASER))
			Laser_Gen(ent, qfalse);
		ThrowItem(ent);
	}
}

/*
=================
PlayerStats
=================
*/
void Cmd_PlayerStats_f(gentity_t * ent)
{
	trap_SendServerCommand(ent - g_entities, va("print \"%s^7:\n\"", ent->client->pers.netname));
	trap_SendServerCommand(ent - g_entities, va("print \"----------------------------------\n\""));
	trap_SendServerCommand(ent - g_entities, va("print \"| Weapon  | Accuracy | Hits/Shots |\n\""));
	trap_SendServerCommand(ent - g_entities, va("print \"----------------------------------\n\""));
	trap_SendServerCommand(ent - g_entities,
			       va("print \"| Knife(T)|      %.0f   |  %.0f/%.0f \n\"",
				  (100 * (float) ent->client->pers.records[REC_KNIFETHROWHITS] /
				   (ent->client->pers.records[REC_KNIFETHROWSHOTS] ? ent->client->pers.
				    records[REC_KNIFETHROWSHOTS] : 1)),
				  (float) ent->client->pers.records[REC_KNIFETHROWHITS],
				  (float) ent->client->pers.records[REC_KNIFETHROWSHOTS]));
	trap_SendServerCommand(ent - g_entities,
			       va("print \"| MK23    |      %.0f   |  %.0f/%.0f \n\"",
				  (100 * (float) ent->client->pers.records[REC_MK23HITS] /
				   (ent->client->pers.records[REC_MK23SHOTS] ? ent->client->pers.
				    records[REC_MK23SHOTS] : 1)), (float) ent->client->pers.records[REC_MK23HITS],
				  (float) ent->client->pers.records[REC_MK23SHOTS]));
	trap_SendServerCommand(ent - g_entities,
			       va("print \"| Akimbo  |      %.0f   |  %.0f/%.0f \n\"",
				  (100 * (float) ent->client->pers.records[REC_AKIMBOHITS] /
				   (ent->client->pers.records[REC_AKIMBOSHOTS] ? ent->client->pers.
				    records[REC_AKIMBOSHOTS] : 1)), (float) ent->client->pers.records[REC_AKIMBOHITS],
				  (float) ent->client->pers.records[REC_AKIMBOSHOTS]));
	trap_SendServerCommand(ent - g_entities,
			       va("print \"| M4      |      %.0f   |  %.0f/%.0f \n\"",
				  (100 * (float) ent->client->pers.records[REC_M4HITS] /
				   (ent->client->pers.records[REC_M4SHOTS] ? ent->client->pers.
				    records[REC_M4SHOTS] : 1)), (float) ent->client->pers.records[REC_M4HITS],
				  (float) ent->client->pers.records[REC_M4SHOTS]));
	trap_SendServerCommand(ent - g_entities,
			       va("print \"| MP5     |      %.0f   |  %.0f/%.0f \n\"",
				  (100 * (float) ent->client->pers.records[REC_MP5HITS] /
				   (ent->client->pers.records[REC_MP5SHOTS] ? ent->client->pers.
				    records[REC_MP5SHOTS] : 1)), (float) ent->client->pers.records[REC_MP5HITS],
				  (float) ent->client->pers.records[REC_MP5SHOTS]));
	trap_SendServerCommand(ent - g_entities,
			       va("print \"| M3      |      %.0f   |  %.0f/%.0f \n\"",
				  (100 * (float) ent->client->pers.records[REC_M3HITS] /
				   (ent->client->pers.records[REC_M3SHOTS] ? ent->client->pers.
				    records[REC_M3SHOTS] : 1)), (float) ent->client->pers.records[REC_M3HITS],
				  (float) ent->client->pers.records[REC_M3SHOTS]));
	trap_SendServerCommand(ent - g_entities,
			       va("print \"| HC      |      %.0f   |  %.0f/%.0f \n\"",
				  (100 * (float) ent->client->pers.records[REC_HANDCANNONHITS] /
				   (ent->client->pers.records[REC_HANDCANNONSHOTS] ? ent->client->pers.
				    records[REC_HANDCANNONSHOTS] : 1)),
				  (float) ent->client->pers.records[REC_HANDCANNONHITS],
				  (float) ent->client->pers.records[REC_HANDCANNONSHOTS]));
	trap_SendServerCommand(ent - g_entities,
			       va("print \"| SSG     |      %.0f   |  %.0f/%.0f \n\"",
				  (100 * (float) ent->client->pers.records[REC_SSG3000HITS] /
				   (ent->client->pers.records[REC_SSG3000SHOTS] ? ent->client->pers.
				    records[REC_SSG3000SHOTS] : 1)), (float) ent->client->pers.records[REC_SSG3000HITS],
				  (float) ent->client->pers.records[REC_SSG3000SHOTS]));
	trap_SendServerCommand(ent - g_entities, va("print \"----------------------------------\n\""));
}

/*
=================
ClientCommand
=================
*/

void ClientCommand(int clientNum)
{
	gentity_t *ent;
	char cmd[MAX_TOKEN_CHARS];

	ent = g_entities + clientNum;
	if (!ent->client) {
		return;		// not fully in game yet
	}

	trap_Argv(0, cmd, sizeof(cmd));

	if (Q_stricmp(cmd, "say") == 0) {
		Cmd_Say_f(ent, SAY_ALL, qfalse);
		return;
	}
	if (Q_stricmp(cmd, "say_team") == 0) {
		Cmd_Say_f(ent, SAY_TEAM, qfalse);
		return;
	}
	if (Q_stricmp(cmd, "tell") == 0) {
		Cmd_Tell_f(ent);
		return;
	}
	if (Q_stricmp(cmd, "vsay") == 0) {
		Cmd_Voice_f(ent, SAY_ALL, qfalse, qfalse);
		return;
	}
	if (Q_stricmp(cmd, "vsay_team") == 0) {
		Cmd_Voice_f(ent, SAY_TEAM, qfalse, qfalse);
		return;
	}
	if (Q_stricmp(cmd, "vtell") == 0) {
		Cmd_VoiceTell_f(ent, qfalse);
		return;
	}
	if (Q_stricmp(cmd, "vosay") == 0) {
		Cmd_Voice_f(ent, SAY_ALL, qfalse, qtrue);
		return;
	}
	if (Q_stricmp(cmd, "vosay_team") == 0) {
		Cmd_Voice_f(ent, SAY_TEAM, qfalse, qtrue);
		return;
	}
	if (Q_stricmp(cmd, "votell") == 0) {
		Cmd_VoiceTell_f(ent, qtrue);
		return;
	}
	if (Q_stricmp(cmd, "vtaunt") == 0) {
		Cmd_VoiceTaunt_f(ent);
		return;
	}
	if (Q_stricmp(cmd, "score") == 0) {
		Cmd_Score_f(ent);
		return;
	}

	if (Q_stricmp(cmd, "wstats") == 0) {
		Cmd_WeaponStats_f(ent);
		return;
	}
	// ignore all other commands when at intermission
	if (level.intermissiontime) {
// JBravo: this is just simply way out there.
//              Cmd_Say_f (ent, qfalse, qtrue);
		return;
	}

	if (Q_stricmp(cmd, "give") == 0)
		Cmd_Give_f(ent);
	else if (Q_stricmp(cmd, "god") == 0)
		Cmd_God_f(ent);
	else if (Q_stricmp(cmd, "notarget") == 0)
		Cmd_Notarget_f(ent);
	else if (Q_stricmp(cmd, "noclip") == 0)
		Cmd_Noclip_f(ent);
	else if (Q_stricmp(cmd, "kill") == 0)
		Cmd_Kill_f(ent);
	else if (Q_stricmp(cmd, "teamtask") == 0)
		Cmd_TeamTask_f(ent);
	else if (Q_stricmp(cmd, "levelshot") == 0)
		Cmd_LevelShot_f(ent);
	else if (Q_stricmp(cmd, "follow") == 0)
		Cmd_Follow_f(ent);
	else if (Q_stricmp(cmd, "follownext") == 0)
		Cmd_FollowCycle_f(ent, 1);
	else if (Q_stricmp(cmd, "followprev") == 0)
		Cmd_FollowCycle_f(ent, -1);
	else if (Q_stricmp(cmd, "team") == 0)
		Cmd_Team_f(ent);
	else if (Q_stricmp(cmd, "where") == 0)
		Cmd_Where_f(ent);
	else if (Q_stricmp(cmd, "callvote") == 0)
		Cmd_CallVote_f(ent);
	else if (Q_stricmp(cmd, "vote") == 0)
		Cmd_Vote_f(ent);
	else if (Q_stricmp(cmd, "callteamvote") == 0)
		Cmd_CallTeamVote_f(ent);
	else if (Q_stricmp(cmd, "teamvote") == 0)
		Cmd_TeamVote_f(ent);
	else if (Q_stricmp(cmd, "gc") == 0)
		Cmd_GameCommand_f(ent);
	else if (Q_stricmp(cmd, "setviewpos") == 0)
		Cmd_SetViewpos_f(ent);
	else if (Q_stricmp(cmd, "stats") == 0)
		Cmd_Stats_f(ent);
	else if (Q_stricmp(cmd, "playerlist") == 0)
		Cmd_Playerlist_f(ent);
//Slicer: matchmode
	else if (Q_stricmp(cmd, "captain") == 0)
		MM_Captain_f(ent);
	else if (Q_stricmp(cmd, "ready") == 0)
		MM_Ready_f(ent);
	else if (Q_stricmp(cmd, "sub") == 0)
		MM_Sub_f(ent);
	else if (Q_stricmp(cmd, "teamname") == 0)
		MM_TeamName_f(ent);
	else if (Q_stricmp(cmd, "teammodel") == 0)
		MM_TeamModel_f(ent);
	else if (Q_stricmp(cmd, "referee") == 0)
		MM_Referee_f(ent);
	else if (Q_stricmp(cmd, "settings") == 0)
		MM_Settings_f(ent);
// aasimon: referee for MM
	else if (Q_stricmp(cmd, "reflogin") == 0)
		Ref_Auth(ent);
	else if (Q_stricmp(cmd, "ref") == 0)
		Ref_Command(ent);
	else if (Q_stricmp(cmd, "refresign") == 0)
		Ref_Resign(ent);
// Begin Duffman
	else if (Q_stricmp(cmd, "reload") == 0) {
		//Cmd_Reload( ent );
// End Duffman
	//Blaze's Open door command
	} else if (Q_stricmp(cmd, "opendoor") == 0)
		Cmd_OpenDoor(ent);
	//Blaze: Bandage code
	else if (Q_stricmp(cmd, "bandage") == 0)
		Cmd_Bandage(ent);
	//End Blaze
	// Hawkins
	else if (Q_stricmp(cmd, "weapon") == 0)
		Cmd_New_Weapon(ent);
	else if (Q_stricmp(cmd, "unzoom") == 0)
		Cmd_Unzoom(ent);
	// end hawkins
// JBravo: adding the choose and drop commands.
	else if (Q_stricmp(cmd, "choose") == 0)
		RQ3_Cmd_Choose_f(ent);
	else if (Q_stricmp(cmd, "drop") == 0)
		RQ3_Cmd_Drop_f(ent);
	else if (Q_stricmp(cmd, "use") == 0)
		RQ3_Cmd_Use_f(ent);
// JBravo: adding radio
	else if (Q_stricmp(cmd, "radiogender") == 0)
		RQ3_Cmd_Radiogender_f(ent);
	else if (Q_stricmp(cmd, "radio_power") == 0)
		RQ3_Cmd_Radio_power_f(ent);
	else if (Q_stricmp(cmd, "radio") == 0)
		RQ3_Cmd_Radio_f(ent);
	else if (Q_stricmp(cmd, "dropweapon") == 0)	// XRAY FMJ
		Cmd_DropWeapon_f(ent);
// JBravo: adding ignore
	else if (Q_stricmp(cmd, "ignorenum") == 0)
		Cmd_Ignorenum_f(ent);
	else if (Q_stricmp(cmd, "unignorenum") == 0)
		Cmd_Ignorenum_f(ent);
	else if (Q_stricmp(cmd, "ignore") == 0)
		Cmd_Ignore_f(ent);
	else if (Q_stricmp(cmd, "unignore") == 0)
		Cmd_Unignore_f(ent);
	else if (Q_stricmp(cmd, "clearignorelist") == 0)
		Cmd_Ignoreclear_f(ent);
// JBravo: adding tkok
	else if (Q_stricmp(cmd, "tkok") == 0)
		RQ3_Cmd_TKOk(ent);
	else if (Q_stricmp(cmd, "debugshit") == 0)
		RQ3_Cmd_debugshit(ent);
	//Elder: stuff for dropping items
	else if (Q_stricmp(cmd, "dropitem") == 0)
		Cmd_DropItem_f(ent);
	else if (Q_stricmp(cmd, "camera") == 0)
		camera_cmd(ent);
	else if (Q_stricmp(cmd, "playerstats") == 0)
		Cmd_PlayerStats_f(ent);
	else if (Q_stricmp(cmd, "SendCheatCvars") == 0) {
		if (!G_SendCheatVars(clientNum))
			Com_Printf("Error loading cvar cfg\n");
	} else
		trap_SendServerCommand(clientNum, va("print \"^1unknown cmd ^7%s\n\"", cmd));
}

/*
===============
RQ3_ValidateSay

Added by Elder
Ensure that the client is not spamming because we need
sv_floodProtect off for fast reloads and what-not.
It's not perfect (ideally we'd cut them off in cgame
but messagemodes by-pass it), but at least it prevents
spam from reaching other clients.
===============
*/

int RQ3_ValidateSay(gentity_t * ent)
{
	int timeCheck, warnTime, banTime;
	int intervalTime, maxWarnings, maxMessages;

	if (g_RQ3_messageProtect.integer == 0)
		return SAY_OK;

	// Check for good cvar values and set them to defaults if bad
	// We use local vars because the cvars may not update in time for use

	// message count
	if (g_RQ3_messageMaxCount.integer < 0) {
		maxMessages = atoi(SAY_MAX_NUMBER);
		trap_Cvar_Set("sv_RQ3_messageMaxCount", SAY_MAX_NUMBER);
	} else
		maxMessages = g_RQ3_messageMaxCount.integer;

	// warning time
	if (g_RQ3_messageWarnTime.integer < 0) {
		warnTime = atoi(SAY_WARNING_TIME);
		trap_Cvar_Set("sv_RQ3_messageWarnTime", SAY_WARNING_TIME);
	} else
		warnTime = g_RQ3_messageWarnTime.integer;

	// max warnings
	if (g_RQ3_messageMaxWarnings.integer < 0) {
		maxWarnings = atoi(SAY_MAX_WARNINGS);
		trap_Cvar_Set("sv_RQ3_messageMaxWarnings", SAY_MAX_WARNINGS);
	} else
		maxWarnings = g_RQ3_messageMaxWarnings.integer;

	// ban time
	if (g_RQ3_messageBanTime.integer < 0) {
		banTime = atoi(SAY_BAN_TIME);
		trap_Cvar_Set("sv_RQ3_messageBanTime", SAY_BAN_TIME);
	} else
		banTime = g_RQ3_messageBanTime.integer;

	// interval time
	if (g_RQ3_messageInterval.integer < 0) {
		intervalTime = atoi(SAY_PERIOD_TIME);
		trap_Cvar_Set("sv_RQ3_messageInterval", SAY_PERIOD_TIME);
	} else
		intervalTime = g_RQ3_messageInterval.integer;

	// seconds to milliseconds
	if (ent->client->pers.sayWarnings) {
		timeCheck = warnTime * 1000;
	} else {
		timeCheck = banTime * 1000;
	}

	// check if already warned/banned
	if (ent->client->pers.sayMuteTime && level.time - ent->client->pers.sayMuteTime < timeCheck) {
		if (ent->client->pers.sayWarnings)
			return SAY_WARNING;
		else
			return SAY_BAN;
	}
	// check if a flooder
	if (ent->client->pers.sayCount >= maxMessages && level.time - ent->client->pers.sayTime < intervalTime * 1000) {
		ent->client->pers.sayMuteTime = level.time;

		// determine penalty level
		if (ent->client->pers.sayWarnings >= maxWarnings) {
			// bans never reset, but warnings do
			ent->client->pers.sayBans++;
			ent->client->pers.sayWarnings = 0;

			// kick if no ban time is set
			if (banTime == 0)
				trap_DropClient(ent->s.clientNum, "Dropped due to chat abuse");

			return SAY_BAN;
		} else {
			ent->client->pers.sayWarnings++;
			return SAY_WARNING;
		}
	}
	// regular say check
	if (level.time - ent->client->pers.sayTime > intervalTime * 1000) {
		ent->client->pers.sayCount = 0;
		ent->client->pers.sayTime = level.time;
		ent->client->pers.sayMuteTime = 0;
		ent->client->pers.sayModerated = qfalse;
	}

	ent->client->pers.sayCount++;

	return SAY_OK;
}

//Makro - this function sends print commands to the client and the ones spectating him
void G_SendClientSpec(gentity_t * ent, const char *msg)
{
	int i;

	if (!ent)
		return;
	if (!ent->client)
		return;

	trap_SendServerCommand(ent - g_entities, msg);

	for (i = 0; i < level.maxclients; i++) {
		gclient_t *follower = &level.clients[i];

		//no need to send the message twice
		if (i == ent - g_entities)
			continue;
		if (follower->pers.connected != CON_CONNECTED)
			continue;
		if (follower->sess.sessionTeam != TEAM_SPECTATOR)
			continue;
		if (follower->sess.spectatorState != SPECTATOR_FOLLOW)
			continue;
		//gotcha !
		if (follower->sess.spectatorClient == ent - g_entities)
			trap_SendServerCommand(i, msg);
	}
}
