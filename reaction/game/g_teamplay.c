//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.61  2002/04/07 12:49:10  slicer
// Added 'teamname' command for MM, and tweaked the cvar system.
//
// Revision 1.60  2002/04/07 03:22:48  jbravo
// Tweaks and crashbug fixes
//
// Revision 1.59  2002/04/06 21:42:20  makro
// Changes to bot code. New surfaceparm system.
//
// Revision 1.58  2002/04/05 06:50:25  blaze
// breakables should now respawn when the round restarts( when g_teamplay:SpawnPlayers() is called to be exact)
//
// Revision 1.57  2002/04/03 15:51:01  jbravo
// Small warning fixes
//
// Revision 1.56  2002/04/03 09:26:47  jbravo
// New FF system. Warns and then finally kickbans teamwounders and
// teamkillers
//
// Revision 1.55  2002/04/02 21:45:15  jbravo
// change for makro
//
// Revision 1.54  2002/04/02 21:41:03  jbravo
// But in new bot radio code.
//
// Revision 1.53  2002/04/02 20:23:12  jbravo
// Bots dont get to use any specmode other than FREE and the recive radio cmds
// as text and not sounds.
//
// Revision 1.52  2002/04/02 04:18:58  jbravo
// Made the TP scoreboard go down at round beginig (not for spectators) and
// pop up at intermission.  Also added special to the use command
//
// Revision 1.51  2002/03/31 23:41:45  jbravo
// Added the use command
//
// Revision 1.50  2002/03/31 18:36:27  jbravo
// Added $T (Near by teammates)
//
// Revision 1.49  2002/03/31 03:31:24  jbravo
// Compiler warning cleanups
//
// Revision 1.48  2002/03/30 17:37:49  jbravo
// Added damage tracking to the server. Added zcam flic mode. cleaned up g_damage.
//
// Revision 1.47  2002/03/30 02:29:43  jbravo
// Lots of spectator code updates. Removed debugshit, added some color.
//
// Revision 1.46  2002/03/26 11:32:05  jbravo
// Remember specstate between rounds.
//
// Revision 1.45  2002/03/26 10:32:52  jbravo
// Bye bye LCA lag
//
// Revision 1.44  2002/03/25 14:55:01  jbravo
// teamCount cvars for Makro
//
// Revision 1.43  2002/03/24 06:06:53  jbravo
// Some tweaks and cleanups
//
// Revision 1.42  2002/03/23 21:29:42  jbravo
// I finally fixed snipers spawning with pistol up. g_RQ3_sniperup has been
// reinstated.
//
// Revision 1.41  2002/03/23 05:17:43  jbravo
// Major cleanup of game -> cgame communication with LCA vars.
//
// Revision 1.40  2002/03/21 19:22:12  jbravo
// Bando now adds extra ammo to the special weaps, and when its dropped it goes
// away again.
//
// Revision 1.39  2002/03/21 15:02:05  jbravo
// More teamname cleanups and fix for fraglines.
//
// Revision 1.38  2002/03/18 12:25:10  jbravo
// Live players dont get fraglines, except their own. Cleanups and some
// hacks to get bots to stop using knives only.
//
// Revision 1.37  2002/03/17 16:38:57  jbravo
// Colored nicks fucked up the string in $K messages.
//
// Revision 1.36  2002/03/17 03:35:29  jbravo
// More radio tewaks and cleanups.
//
// Revision 1.35  2002/03/17 01:55:43  jbravo
// Fixed a small bug in radio enemyd that made it say "one enemu down"
//
// Revision 1.34  2002/03/17 00:40:23  jbravo
// Adding variable team names. g_RQ3_team1name and g_RQ3_team2name. Fixed
// Slicers fraglimit check.
//
// Revision 1.33  2002/03/14 23:54:12  jbravo
// Added a variable system from AQ. Works the same except it uses $ for %
//
// Revision 1.32  2002/03/14 02:24:39  jbravo
// Adding radio :)
//
// Revision 1.31  2002/03/11 18:02:33  slicer
// Fixed team changes and scoreboard bugs
//
// Revision 1.30  2002/03/07 14:29:12  slicer
// Intermission ala aq2, when timelimit/roundlimit hits.
//
// Revision 1.29  2002/03/05 02:08:16  jbravo
// Fixed Unknown client command: Roundlimit bug
//
// Revision 1.28  2002/03/03 23:51:45  jbravo
// Final fixes for anims at spawn and a knife bug.
//
// Revision 1.27  2002/03/03 18:00:26  jbravo
// More Anim fixes.  Knives still broken
//
// Revision 1.26  2002/03/03 03:11:37  jbravo
// Use propper weapon anims on TP spawns
//
// Revision 1.25  2002/03/02 16:16:54  jbravo
// Fixed the uneven team calculations
//
// Revision 1.24  2002/03/01 20:02:34  jbravo
// Added ui_RQ3_teamCount1, ui_RQ3_teamCount2 and ui_RQ3_numSpectators for
// makro
//
// Revision 1.23  2002/03/01 18:21:26  jbravo
// Cleanups and removal of g_RQ3_sniperup
//
// Revision 1.22  2002/02/27 01:54:29  jbravo
// More spectatorfixes and finally stopped all fallingdamage anims and
// sounds during LCA.
//
// Revision 1.21  2002/02/25 19:51:26  jbravo
// Fixed a bug that made it impossible to pick up special weapons when player
// had selected akimbos or knives
//
// Revision 1.20  2002/02/25 19:41:53  jbravo
// Fixed the use ESC and join menu to join teams when dead players are
// spectating in TP mode.
// Tuned the autorespawn system a bit.  Now dead ppl. are dead for a very
// small time before they are made into spectators.
//
// Revision 1.19  2002/02/24 18:12:19  jbravo
// Added a cvar to control sniper behavior g_RQ3_sniperup. Def 0. if set yo 1
// it makes players spawn with the sniper up.
//
// Revision 1.18  2002/02/24 17:56:44  jbravo
// Cleaned up EquipPlayer() and made snipers spawn with pistol in hand
//
// Revision 1.17  2002/02/24 16:40:35  jbravo
// Fixed a bug where the mode of knifes and grenades where reset to slashing
// and short throw.
//
// Revision 1.16  2002/02/22 02:13:13  jbravo
// Fixed a few bugs and did some cleanups
//
// Revision 1.15  2002/02/11 00:30:23  niceass
// LCA fix
//
// Revision 1.14  2002/02/10 04:55:28  jbravo
// Fix #1 to zcam jitter.   More is probably needed.
//
// Revision 1.13  2002/02/09 00:10:12  jbravo
// Fixed spectator follow and free and updated zcam to 1.04 and added the
// missing zcam files.
//
// Revision 1.12  2002/02/06 03:10:43  jbravo
// Fix the instant spectate on death and an attempt to fix the scores
//
// Revision 1.11  2002/02/05 23:41:27  slicer
// More on matchmode..
//
// Revision 1.10  2002/02/05 10:04:41  jbravo
// Debugging message gone and cleanup of Antistick routinr
//
// Revision 1.9  2002/02/04 05:44:00  jbravo
// Fixed a typo in knives name
//
// Revision 1.8  2002/02/03 21:23:51  slicer
// More Matchmode code and fixed 2 bugs in TP
//
// Revision 1.7  2002/01/29 03:13:45  jbravo
// Further fixes to antistick
//
// Revision 1.6  2002/01/27 13:42:19  jbravo
// temp hack removed
//
// Revision 1.5  2002/01/27 13:33:28  jbravo
// Teamplay antistick system.
//
// Revision 1.4  2002/01/23 15:59:43  jbravo
// Make use of NiceAsses ClearBodyQue() between rounds
//
// Revision 1.3  2002/01/21 20:03:15  jbravo
// Changed the knifes fix a bit
//
// Revision 1.2  2002/01/21 19:52:31  jbravo
// Fixed a bug that didnt allow knifes to be selected as primary weapon
//
// Revision 1.1  2002/01/11 20:23:41  jbravo
// Added the two new files for TP I forgot during the main TP commit
//
//
//-----------------------------------------------------------------------------

#include "g_local.h"
#include "zcam.h"

gitem_t	*BG_FindItemForHoldable( holdable_t pw );
char	*ConcatArgs( int start );
int	touch[MAX_GENTITIES];
void	ResetKills(gentity_t *ent);
void	ClearBodyQue (void);
void	Cmd_DropItem_f(gentity_t *ent);
void	Cmd_DropWeapon_f(gentity_t *ent);
void	AddIP(char *str);

void CheckTeamRules()
{
	int winner, i;
	int checked_tie = 0;
	gentity_t *player;

	//Slicer
	if(level.intermissiontime)
		return;

	level.fps = trap_Cvar_VariableIntegerValue("sv_fps");

	if (level.lights_camera_action) {
		ContinueLCA();
		return;
	}

	if (level.team_round_going)
		level.current_round_length++;

	if (level.holding_on_tie_check) {
		level.holding_on_tie_check--;
		if (level.holding_on_tie_check > 0)
			return;
		level.holding_on_tie_check = 0;
		checked_tie = 1;
	}

	if (level.team_round_countdown == 1) {
		level.team_round_countdown = 0;
		if (BothTeamsHavePlayers()) {
			level.team_game_going = 1;
			level.inGame = qtrue;
			StartLCA();
		} else {
			//Slicer: Adding Matchmode
			if(g_RQ3_matchmode.integer) {
				if(g_RQ3_team1ready.integer && g_RQ3_team2ready.integer)
					trap_SendServerCommand( -1, "cp \"Not enough players to play!\n\"");
				else
					trap_SendServerCommand( -1, "cp \"Both Teams Must Be Ready!\n\"");
			}
			else
				trap_SendServerCommand( -1, "cp \"Not enough players to play!\n\"");

			MakeAllLivePlayersObservers();
			level.inGame = qfalse;
		}
	} else {
		if (level.team_round_countdown)
			level.team_round_countdown--;
		if (level.team_round_countdown == (101*level.fps)/10) {
			for (i = 0; i < level.maxclients; i++) {
				player = &g_entities[i];
				if (!player->inuse)
					continue;
				G_AddEvent ( player, EV_RQ3_SOUND, RQ3_SOUND_COUNTDOWN);
			}
		}
	}

	level.rulecheckfrequency++;
	if (level.rulecheckfrequency % 30 && !checked_tie)
		return;

	if (!level.team_round_going) {
		if (g_timelimit.integer) {
			//Slicer : Matchmode
			if(g_RQ3_matchmode.integer) {
				if(level.matchTime >= g_timelimit.integer * 60) {
					level.inGame = level.team_round_going = level.team_round_countdown = 
					level.team_game_going = level.matchTime = 0;
					trap_SendServerCommand( -1, "roundend");
					trap_Cvar_Set("g_RQ3_team1ready", "0");
					trap_Cvar_Set("g_RQ3_team2ready", "0");
					MakeAllLivePlayersObservers ();
					trap_SendServerCommand( -1, "cp \"Match is OVER !!!.\n\"");
					return;
				}
			}
			else {
				if (level.time - level.startTime >= g_timelimit.integer*60000) {
					//Slicer : Let's do a normal console print instead..
					trap_SendServerCommand( -1, "print \"Timelimit hit.\n\"" );
					//trap_SendServerCommand( -1, va("cp \"Timelimit hit.\n\""));
					level.team_round_going = level.team_round_countdown = level.team_game_going = 0;
					trap_SendServerCommand( -1, "roundend");
					//Slicer: Start Intermission
					BeginIntermission();
					return;
				}
			}
		}
		if (!level.team_round_countdown) {
			if (BothTeamsHavePlayers()) {
				//Slicer let's print to the console too
				trap_SendServerCommand( -1, "print \"The round will begin in 20 seconds!\n\"" );
				trap_SendServerCommand( -1, va("cp \"The round will begin in 20 seconds!\n\""));
				level.team_round_countdown = (201*level.fps)/10;
			}
		}
	} else {
		if ((winner = CheckForWinner()) != WINNER_NONE) {
			if (!checked_tie) {
				level.holding_on_tie_check = (50*level.fps)/10;
				return;
			}
			if (WonGame(winner))
				return;
			level.team_round_going = 0;
			trap_SendServerCommand( -1, "roundend");
			level.lights_camera_action = 0;
			level.holding_on_tie_check = 0;
			level.team_round_countdown = (71*level.fps)/10;
//			trap_SendConsoleCommand( EXEC_APPEND, "map_restart 0\n" );
			return;
		}

		if (g_RQ3_roundtimelimit.integer && (level.current_round_length > g_RQ3_roundtimelimit.integer * 600)) {
			trap_SendServerCommand( -1, va("cp \"Round timelimit hit.\n\""));
			winner = CheckForForcedWinner();
			if (WonGame(winner))
				return;
			level.team_round_going = 0;
			trap_SendServerCommand( -1, "roundend");
			level.lights_camera_action = 0;
			level.holding_on_tie_check = 0;
			level.team_round_countdown = (71*level.fps)/10;
//			trap_SendConsoleCommand( EXEC_APPEND, "map_restart 0\n" );
			return;
		}
	}
}

void StartLCA()
{
	CleanLevel();
	trap_Cvar_Set("g_RQ3_lca", "1");
	level.lights_camera_action = (41*level.fps)/10;
	SpawnPlayers();

	trap_SendServerCommand( -1, "lights");
}

void ContinueLCA()
{
	if (level.lights_camera_action == (21*level.fps)/10) {
		trap_SendServerCommand( -1, "camera");
	}
	else if (level.lights_camera_action == 1) {
		trap_SendServerCommand( -1, "action");
		trap_Cvar_Set("g_RQ3_lca", "0");
		level.team_round_going = 1;
		trap_SendServerCommand( -1, "roundbegin");
		level.current_round_length = 0;
	}
	level.lights_camera_action--;
}

qboolean BothTeamsHavePlayers()
{
	int onteam1 = 0, onteam2 = 0;

	//Slicer: Matchmode
	if(g_RQ3_matchmode.integer && (!g_RQ3_team1ready.integer || !g_RQ3_team2ready.integer))
		return 0;
	

	onteam1 = RQ3TeamCount( -1, TEAM_RED );
	onteam2 = RQ3TeamCount( -1, TEAM_BLUE );

	return (onteam1 > 0 && onteam2 > 0);
}

void MakeAllLivePlayersObservers()
{
	gentity_t	*player;
	int		i;

	for (i = 0; i < level.maxclients; i++) {
		player = &g_entities[i];
		//Slicer: Need to check if they are solid or not.
		if (!player->inuse || player->client->ps.pm_type != PM_NORMAL)
			continue;
		level.clients[i].sess.savedTeam = level.clients[i].sess.sessionTeam;
		level.clients[i].ps.persistant[PERS_SAVEDTEAM] = level.clients[i].sess.sessionTeam;
		level.clients[i].sess.sessionTeam = TEAM_SPECTATOR;
		level.clients[i].sess.spectatorState = SPECTATOR_FREE;
	}
}

void CleanLevel()
{
	gentity_t	*ent;
	int		i;

	ClearBodyQue();
	ent = &g_entities[MAX_CLIENTS];
	for ( i = MAX_CLIENTS ; i<level.num_entities ; i++, ent++)
	{
		if (!ent->inuse)
			continue;
		if(!ent->item)
			continue;
		if (ent->item->giType == IT_WEAPON) {
			switch (ent->item->giTag) {
			case WP_MP5:
			case WP_M4:
			case WP_M3:
			case WP_HANDCANNON:
			case WP_SSG3000:
			case WP_PISTOL:
			case WP_KNIFE:
			case WP_GRENADE:
				G_FreeEntity(ent);
				break;
			default:
				break;
			}
		} else if (ent->item->giType == IT_HOLDABLE) {
			switch (ent->item->giTag) {
			case HI_KEVLAR:
			case HI_LASER:
			case HI_SILENCER:
			case HI_BANDOLIER:
			case HI_SLIPPERS:
				G_FreeEntity(ent);
				break;
			default:
				break;
			}
		} else if (ent->item->giType == IT_AMMO) {
		}
	}

}

int CheckForWinner()
{
	int onteam1 = 0, onteam2 = 0, i;
	gentity_t *player;

	for (i = 0; i < level.maxclients; i++) {
		player = &g_entities[i];
		if (!player->inuse)
			continue;
		if (level.clients[i].sess.sessionTeam == TEAM_RED && player->client->ps.stats[STAT_HEALTH] > 0)
			onteam1++;
		else if (level.clients[i].sess.sessionTeam == TEAM_BLUE && player->client->ps.stats[STAT_HEALTH] > 0)
			onteam2++;
	}

	if (onteam1 > 0 && onteam2 > 0)
		return WINNER_NONE;
	else if (onteam1 == 0 && onteam2 == 0)
		return WINNER_TIE;
	else if (onteam1 > 0 && onteam2 == 0)
		return WINNER_TEAM1;
	else
		return WINNER_TEAM2;
}

int CheckForForcedWinner()
{
	int onteam1 = 0, onteam2 = 0, i;
	int health1 = 0, health2 = 0;
	gentity_t *player;

	for (i = 0; i < level.maxclients; i++) {
		player = &g_entities[i];
		if (!player->inuse)
			continue;
		if (level.clients[i].sess.savedTeam == TEAM_RED && player->client->ps.stats[STAT_HEALTH] > 0) {
			onteam1++;
			health1 += player->client->ps.stats[STAT_HEALTH];
		} else if (level.clients[i].sess.savedTeam == TEAM_BLUE && player->client->ps.stats[STAT_HEALTH] > 0) {
			onteam2++;
			health2 += player->client->ps.stats[STAT_HEALTH];
		}
	}

	if (onteam1 > onteam2) {
		return WINNER_TEAM1;
	} else if (onteam2 > onteam1) {
		return WINNER_TEAM2;
	} else {
		if (health1 > health2)
			return WINNER_TEAM1;
		else if (health2 > health1)
			return WINNER_TEAM2;
		else
			return WINNER_TIE;
	}
}

int WonGame(int winner)
{
	trap_SendServerCommand( -1, "print \"The round is over:\n\"" );

	if (winner == WINNER_TIE) {
		trap_SendServerCommand( -1, "print \"It was a tie, no points awarded!\n\"" );
	} else {
		if (winner == WINNER_TEAM1) {
			trap_SendServerCommand( -1, va("print \"%s won!\n\"", g_RQ3_team1name.string));
			level.teamScores[TEAM_RED]++;
		} else {
			trap_SendServerCommand( -1, va("print \"%s won!\n\"", g_RQ3_team2name.string));
			level.teamScores[TEAM_BLUE]++;
		}
	}

	if (g_timelimit.integer) {
		//Slicer : Matchmode
		if(g_RQ3_matchmode.integer) {
			if(level.matchTime >= g_timelimit.integer * 60) {
			level.inGame = level.team_round_going = level.team_round_countdown = 
			level.team_game_going = level.matchTime = 0;
			trap_SendServerCommand( -1, "roundend");
			trap_Cvar_Set("g_RQ3_team1ready", "0");
			trap_Cvar_Set("g_RQ3_team2ready", "0");
			MakeAllLivePlayersObservers ();
			trap_SendServerCommand( -1, "cp \"Match is OVER !!!.\n\"");
			return 1;
			}
		}
		else {
			if(level.time - level.startTime >= g_timelimit.integer*60000) {
				trap_SendServerCommand( -1, "print \"Timelimit hit.\n\"" );
				level.team_round_going = level.team_round_countdown = level.team_game_going = 0;
				trap_SendServerCommand( -1, "roundend");
				//Slicer: Start Intermission
				BeginIntermission();
				return 1;
			}
		}
	}

	if (g_RQ3_roundlimit.integer) {
		if (level.teamScores[TEAM_RED] >= g_RQ3_roundlimit.integer || level.teamScores[TEAM_BLUE] >= g_RQ3_roundlimit.integer) {
				//Slicer : Matchmode
			if(g_RQ3_matchmode.integer) {
				level.inGame = level.team_round_going = level.team_round_countdown = 
				level.team_game_going = level.matchTime = 0;
				trap_SendServerCommand( -1, "roundend");
				trap_Cvar_Set("g_RQ3_team1ready", "0");
				trap_Cvar_Set("g_RQ3_team2ready", "0");
				MakeAllLivePlayersObservers ();
				trap_SendServerCommand( -1, "cp \"Match is OVER !!!.\n\"");
				return 1;
			}
			else {
			//Slicer: Adding a normal console print..
			trap_SendServerCommand( -1, "print \"Roundlimit hit.\n\"" );
			trap_SendServerCommand( -1, va("cp \"Roundlimit hit.\n\""));
			level.team_round_going = level.team_round_countdown = level.team_game_going = 0;
			trap_SendServerCommand( -1, "roundend");
			//Slicer: Start Intermission
			BeginIntermission();
			return 1;
			}
		}
	}

	return 0;
}

team_t RQ3TeamCount( int ignoreClientNum, int team )
{
	int	i;
	int	count = 0;
	char	buf[20];

	for ( i = 0 ; i < level.maxclients ; i++ ) {
		if ( i == ignoreClientNum ) {
			continue;
		}
		if ( level.clients[i].pers.connected == CON_DISCONNECTED ) {
			continue;
		}
		//Slicer: Matchmode - Subs don't count
		if(g_RQ3_matchmode.integer && level.clients[i].pers.sub != TEAM_FREE)
			continue;
		if ( level.clients[i].sess.savedTeam == team ) {
			count++;
		}
	}

	Com_sprintf (buf, sizeof(buf), "%i", count);
	if (team == TEAM_RED)
		trap_Cvar_Set("g_RQ3_teamCount1", buf);
	else if (team == TEAM_BLUE)
		trap_Cvar_Set("g_RQ3_teamCount2", buf);
	else if (team == TEAM_SPECTATOR || team == TEAM_FREE)	
		trap_Cvar_Set("g_RQ3_numSpectators", buf);

	return count;
}

void CheckForUnevenTeams(gentity_t *player)
{
	int		i, onteam1 = 0, onteam2 = 0;
	gentity_t	*ent;

	for (i = 0; i < level.maxclients; i++) {
		ent = &g_entities[i];
		if (ent->inuse) {
			if (ent->client->sess.savedTeam == TEAM_RED)
				onteam1++;
			else if (ent->client->sess.savedTeam == TEAM_BLUE)
				onteam2++;
		}
	}

	if (player->client->sess.savedTeam == TEAM_RED) {
		if (onteam1 > onteam2)
			trap_SendServerCommand(player-g_entities, va("print \"Your team now has %d more player%s than %s\n\"",
				onteam1 - onteam2, onteam1 - onteam2 == 1 ? "" : "s", g_RQ3_team2name.string));
	} else if (player->client->sess.savedTeam == TEAM_BLUE) {
		if (onteam2 > onteam1)
			trap_SendServerCommand(player-g_entities, va("print \"Your team now has %d more player%s than %s\n\"",
				onteam2 - onteam1, onteam2 - onteam1 == 1 ? "" : "s", g_RQ3_team1name.string));
	}
}

void SpawnPlayers()
{
	gentity_t	*player, *ent;
	gclient_t	*client;
	int		clientNum, i;

	level.spawnPointsLocated = qfalse;
	for (i = 0; i < level.maxclients; i++) {
		player = &g_entities[i];

		if (!player->inuse)
			continue;
		//Slicer: Matchmode - Subs don't spawn

		if(g_RQ3_matchmode.integer && player->client->pers.sub != TEAM_FREE)
			continue;
// JBravo: lets not respawn spectators in free floating mode
		if(player->client->sess.savedTeam == TEAM_SPECTATOR &&
				player->client->specMode == SPECTATOR_FREE)
			continue;

		client = player->client;
		clientNum = client - level.clients;

		client->sess.teamSpawn = qtrue;
		if (client->sess.savedTeam == TEAM_RED) {
			client->sess.sessionTeam = TEAM_RED;
			client->ps.persistant[PERS_TEAM] = TEAM_RED;
		} else if (client->sess.savedTeam == TEAM_BLUE) {
			client->sess.sessionTeam = TEAM_BLUE;
			client->ps.persistant[PERS_TEAM] = TEAM_BLUE;
		}
		client->ps.stats[STAT_RQ3] &= ~RQ3_PLAYERSOLID;
		client->sess.spectatorState = SPECTATOR_NOT;
		ClientSpawn(player);
		ClientUserinfoChanged(clientNum);
		client->sess.teamSpawn = qfalse;
	}
  //Blaze: May aswell respawn breakables here
  for (i=0;i<level.num_entities; i++)
  {
    ent = &g_entities[i];
    if (ent->classname != NULL && !strcmp(ent->classname, "func_breakable")) 
    {
      //re-link all unlinked breakables
      trap_LinkEntity(ent);
      
    }
  }
}

/* Let the player Choose the weapon and/or item he wants */
void RQ3_Cmd_Choose_f( gentity_t *ent )
{
	char	*cmd;

	if ( !ent->client ) {
		return;		// not fully in game yet
	}

	cmd = ConcatArgs( 1 );

	if (Q_stricmp (cmd, RQ3_MP5_NAME) == 0 || Q_stricmp (cmd, "mp5") == 0) {
		ent->client->teamplayWeapon = WP_MP5;
		trap_SendServerCommand(ent-g_entities, va("print \"Weapon selected: %s\n\"", RQ3_MP5_NAME));
	} else if (Q_stricmp (cmd, RQ3_M3_NAME) == 0 || Q_stricmp (cmd, "m3") == 0) {
		ent->client->teamplayWeapon = WP_M3;
		trap_SendServerCommand(ent-g_entities, va("print \"Weapon selected: %s\n\"", RQ3_M3_NAME));
	} else if (Q_stricmp (cmd, RQ3_M4_NAME) == 0 || Q_stricmp (cmd, "m4") == 0) {
		ent->client->teamplayWeapon = WP_M4;
		trap_SendServerCommand(ent-g_entities, va("print \"Weapon selected: %s\n\"", RQ3_M4_NAME));
	} else if (Q_stricmp (cmd, RQ3_HANDCANNON_NAME) == 0 || Q_stricmp (cmd, "hc") == 0) {
		ent->client->teamplayWeapon = WP_HANDCANNON;
		trap_SendServerCommand(ent-g_entities, va("print \"Weapon selected: %s\n\"", RQ3_HANDCANNON_NAME));
	} else if (Q_stricmp (cmd, RQ3_SSG3000_NAME) == 0 || Q_stricmp (cmd, "sniper") == 0) {
		ent->client->teamplayWeapon = WP_SSG3000;
		trap_SendServerCommand(ent-g_entities, va("print \"Weapon selected: %s\n\"", RQ3_SSG3000_NAME));
	} else if (Q_stricmp (cmd, RQ3_KNIFE_NAME) == 0 || Q_stricmp (cmd, "knives") == 0) {
		ent->client->teamplayWeapon = WP_KNIFE;
		trap_SendServerCommand(ent-g_entities, va("print \"Weapon selected: %s\n\"", RQ3_KNIFE_NAME));
	} else if (Q_stricmp (cmd, RQ3_AKIMBO_NAME) == 0 || Q_stricmp (cmd, "akimbo") == 0) {
		ent->client->teamplayWeapon = WP_AKIMBO;
		trap_SendServerCommand(ent-g_entities, va("print \"Weapon selected: %s\n\"", RQ3_AKIMBO_NAME));
	} else if (Q_stricmp (cmd, RQ3_KEVLAR_NAME) == 0 || Q_stricmp (cmd, "kevlar") == 0) {
		ent->client->teamplayItem = HI_KEVLAR;
		trap_SendServerCommand(ent-g_entities, va("print \"Item selected: %s\n\"", RQ3_KEVLAR_NAME));
	} else if (Q_stricmp (cmd, RQ3_LASER_NAME) == 0 || Q_stricmp (cmd, "laser") == 0) {
		ent->client->teamplayItem = HI_LASER;
		trap_SendServerCommand(ent-g_entities, va("print \"Item selected: %s\n\"", RQ3_LASER_NAME));
	} else if (Q_stricmp (cmd, RQ3_SLIPPERS_NAME) == 0 || Q_stricmp (cmd, "slippers") == 0) {
		ent->client->teamplayItem = HI_SLIPPERS;
		trap_SendServerCommand(ent-g_entities, va("print \"Item selected: %s\n\"", RQ3_SLIPPERS_NAME));
	} else if (Q_stricmp (cmd, RQ3_SILENCER_NAME) == 0 || Q_stricmp (cmd, "silencer") == 0) {
		ent->client->teamplayItem = HI_SILENCER;
		trap_SendServerCommand(ent-g_entities, va("print \"Item selected: %s\n\"", RQ3_SILENCER_NAME));
	} else if (Q_stricmp (cmd, RQ3_BANDOLIER_NAME) == 0 || Q_stricmp (cmd, "bandolier") == 0) {
		ent->client->teamplayItem = HI_BANDOLIER;
		trap_SendServerCommand(ent-g_entities, va("print \"Item selected: %s\n\"", RQ3_BANDOLIER_NAME));
	} else {
		trap_SendServerCommand(ent-g_entities, va("print \"Invalid weapon or item choice.\n\""));
		return;
	}
}

/* Drop weapon or Item ala. AQ */
void RQ3_Cmd_Drop_f( gentity_t *ent )
{
	char	cmd[MAX_TOKEN_CHARS];

	if ( !ent->client ) {
		return;			// not fully in game yet
	}

	trap_Argv( 1, cmd, sizeof( cmd ) );

	if (Q_stricmp (cmd, "item") == 0) {
		Cmd_DropItem_f ( ent );
	} else if (Q_stricmp (cmd, "weapon") == 0) {
		Cmd_DropWeapon_f ( ent );
	} else {
		trap_SendServerCommand(ent-g_entities, va("print \"unknown item: %s\n\"", cmd));
	}
}

/* Equip the player with the weapons and items he needs for the round. */
void EquipPlayer (gentity_t *ent)
{
	int	bandolierFactor, grenades;

	if (!ent->client || ent->client->sess.sessionTeam == TEAM_SPECTATOR)
		return;

	bandolierFactor = grenades = 0;

	ent->client->numClips[ WP_PISTOL ] = 1;			// extra clip of ammo for pistol
	ent->client->ps.ammo[ WP_PISTOL] = RQ3_PISTOL_AMMO;
	
	if (ent->client->teamplayItem == HI_BANDOLIER) {
		bandolierFactor = 2;
		grenades = trap_Cvar_VariableIntegerValue( "g_RQ3_tgren" );
	} else {
		bandolierFactor = 1;
	}

	switch(ent->client->teamplayWeapon) {
	case WP_SSG3000:
		ent->client->ps.stats[STAT_WEAPONS] = ( 1 << WP_PISTOL );
		ent->client->ps.stats[STAT_WEAPONS] |= ( 1 << WP_SSG3000 );
		ent->client->ps.stats[STAT_WEAPONS] |= ( 1 << WP_KNIFE );
		ent->client->numClips[WP_SSG3000] = RQ3_SSG3000_EXTRA_AMMO * bandolierFactor;
		ent->client->ps.ammo[WP_SSG3000] = RQ3_SSG3000_AMMO;
		if (g_RQ3_sniperup.integer == 1) {
			ent->client->ps.weapon = WP_SSG3000;
			ent->client->ps.weaponTime = RQ3_SSG3000_ACTIVATE_DELAY;
		} else {
			ent->client->ps.weapon = WP_PISTOL;
			ent->client->ps.weaponTime = RQ3_PISTOL_ACTIVATE_DELAY;
		}
		ent->client->weaponCount[WP_SSG3000] = 1;
		ent->client->uniqueWeapons = 1;
		break;
	case WP_MP5:
		ent->client->ps.stats[STAT_WEAPONS] = ( 1 << WP_MP5 );
		ent->client->ps.stats[STAT_WEAPONS] |= ( 1 << WP_PISTOL );
		ent->client->ps.stats[STAT_WEAPONS] |= ( 1 << WP_KNIFE );
		ent->client->numClips[WP_MP5] = RQ3_MP5_EXTRA_AMMO * bandolierFactor;
		ent->client->ps.ammo[WP_MP5] = RQ3_MP5_AMMO;
		ent->client->ps.weapon = WP_MP5;
		ent->client->ps.weaponTime = RQ3_MP5_ACTIVATE_DELAY;
		ent->client->weaponCount[WP_MP5] = 1;
		ent->client->uniqueWeapons = 1;
		break;
	case WP_M3:
		ent->client->ps.stats[STAT_WEAPONS] = ( 1 << WP_M3 );
		ent->client->ps.stats[STAT_WEAPONS] |= ( 1 << WP_PISTOL );
		ent->client->ps.stats[STAT_WEAPONS] |= ( 1 << WP_KNIFE );
		ent->client->numClips[WP_M3] = RQ3_M3_EXTRA_AMMO * bandolierFactor;
		ent->client->ps.ammo[WP_M3] = RQ3_M3_AMMO;
		ent->client->ps.weapon = WP_M3;
		ent->client->ps.weaponTime = RQ3_M3_ACTIVATE_DELAY;
		ent->client->weaponCount[WP_M3] = 1;
		ent->client->uniqueWeapons = 1;
		break;
	case WP_M4:
		ent->client->ps.stats[STAT_WEAPONS] = ( 1 << WP_M4 );
		ent->client->ps.stats[STAT_WEAPONS] |= ( 1 << WP_PISTOL );
		ent->client->ps.stats[STAT_WEAPONS] |= ( 1 << WP_KNIFE );
		ent->client->numClips[WP_M4] = RQ3_M4_EXTRA_AMMO * bandolierFactor;
		ent->client->ps.ammo[WP_M4] = RQ3_M4_AMMO;
		ent->client->ps.weapon = WP_M4;
		ent->client->ps.weaponTime = RQ3_M4_ACTIVATE_DELAY;
		ent->client->weaponCount[WP_M4] = 1;
		ent->client->uniqueWeapons = 1;
		break;
	case WP_AKIMBO:
		ent->client->ps.stats[STAT_WEAPONS] = ( 1 << WP_AKIMBO );
		ent->client->ps.stats[STAT_WEAPONS] |= ( 1 << WP_PISTOL );
		ent->client->ps.stats[STAT_WEAPONS] |= ( 1 << WP_KNIFE );
		ent->client->numClips[WP_AKIMBO] = RQ3_AKIMBO_EXTRA_AMMO * bandolierFactor;
		ent->client->ps.ammo[WP_AKIMBO] = RQ3_AKIMBO_AMMO;
		ent->client->ps.weapon = WP_AKIMBO;
		ent->client->ps.weaponTime = RQ3_AKIMBO_ACTIVATE_DELAY;
		ent->client->weaponCount[WP_AKIMBO] = 1;
		ent->client->uniqueWeapons = 0;
		break;
	case WP_HANDCANNON:
		ent->client->ps.stats[STAT_WEAPONS] = ( 1 << WP_HANDCANNON );
		ent->client->ps.stats[STAT_WEAPONS] |= ( 1 << WP_PISTOL );
		ent->client->ps.stats[STAT_WEAPONS] |= ( 1 << WP_KNIFE );
		ent->client->numClips[WP_HANDCANNON] = RQ3_HANDCANNON_EXTRA_AMMO * bandolierFactor;
		ent->client->ps.ammo[WP_HANDCANNON] = RQ3_HANDCANNON_AMMO;
		ent->client->ps.weapon = WP_HANDCANNON;
		ent->client->ps.weaponTime = RQ3_HANDCANNON_ACTIVATE_DELAY;
		ent->client->weaponCount[WP_HANDCANNON] = 1;
		ent->client->uniqueWeapons = 1;
		break;
	case WP_KNIFE:
		ent->client->ps.stats[STAT_WEAPONS] = ( 1 << WP_KNIFE );
		ent->client->ps.stats[STAT_WEAPONS] |= ( 1 << WP_PISTOL );
		ent->client->ps.ammo[WP_KNIFE] = RQ3_KNIVES_EXTRA_AMMO * bandolierFactor;
		ent->client->ps.weapon = WP_KNIFE;
		ent->client->ps.weaponTime = RQ3_KNIFE_ACTIVATE_DELAY;
		ent->client->weaponCount[WP_KNIFE] = 1;
		ent->client->uniqueWeapons = 0;
		break;
	default:
		break;
	}

	if (grenades > 0) {
		ent->client->ps.stats[STAT_WEAPONS] |= ( 1 << WP_GRENADE );
		ent->client->ps.ammo[WP_GRENADE] = grenades;
	}
	if (ent->client->teamplayWeapon == WP_KNIFE && !(ent->client->ps.persistant[PERS_WEAPONMODES] & RQ3_KNIFEMODE)) {
		ent->client->ps.generic1 = ((ent->client->ps.generic1 & ANIM_TOGGLEBIT) ^
			ANIM_TOGGLEBIT) | WP_ANIM_THROWACTIVATE;
	} else {
		ent->client->ps.generic1 = ((ent->client->ps.generic1 & ANIM_TOGGLEBIT) ^
			ANIM_TOGGLEBIT) | WP_ANIM_ACTIVATE;
	}
	if (ent->r.svFlags & SVF_BOT) {
		ent->client->ps.stats[STAT_WEAPONS] = ( 1 << WP_PISTOL );
		ent->client->ps.stats[STAT_WEAPONS] |= ( 1 << WP_KNIFE );
		ent->client->uniqueWeapons = 0;
	}
	ent->client->ps.weaponstate = WEAPON_RAISING;

	ent->client->ps.stats[STAT_HOLDABLE_ITEM] = BG_FindItemForHoldable( ent->client->teamplayItem ) - bg_itemlist;
	ent->client->uniqueItems = 1;
}

void UnstickPlayer( gentity_t *ent )
{
	int		i, num, count;
	gentity_t	*hit;
	vec3_t		mins, maxs;

	count = 0;

	VectorAdd( ent->client->ps.origin, ent->r.mins, mins );
	VectorAdd( ent->client->ps.origin, ent->r.maxs, maxs );

	num = trap_EntitiesInBox( mins, maxs, touch, MAX_GENTITIES );

	for (i=0 ; i<num ; i++) {
		hit = &g_entities[touch[i]];
		if ( hit->client && hit != ent ) {
			count++;
		}
	}

	if (count == 0) {
		ent->client->ps.stats[STAT_RQ3] |= RQ3_PLAYERSOLID;
	}
}

void MakeSpectator(gentity_t *ent)
{
	gclient_t	*client;

	client = ent->client;
	CopyToBodyQue (ent);

	client->weaponCount[ent->client->ps.weapon] = 0;
	client->ps.stats[STAT_WEAPONS] = 0;
	client->sess.sessionTeam = TEAM_SPECTATOR;
	client->ps.persistant[PERS_TEAM] = TEAM_SPECTATOR;
	if (ent->r.svFlags & SVF_BOT)
		client->sess.spectatorState = SPECTATOR_FREE;
	else
		client->sess.spectatorState = client->specMode;
	ClientSpawn(ent);
}

qboolean OKtoFollow( int clientnum )
{
	int i, x;

	x = 0;

	for (i = 0; i < level.maxclients ; i++) {
		if (i == clientnum) {
			continue;
		}
		if (level.clients[i].pers.connected != CON_CONNECTED) {
			continue;
		}
		if (level.clients[i].sess.sessionTeam == TEAM_SPECTATOR) {
			continue;
		}
		x++;
	};
	if (x > 0) {
		return qtrue;
	}
	return qfalse;
}

void RQ3_Cmd_Radio_power_f(gentity_t *ent)
{
	if (ent->client->radioOff == qfalse) {
		ent->client->radioOff = qtrue;
		trap_SendServerCommand(ent-g_entities, "cp \"Radio switched off\n\"");
		trap_SendServerCommand(ent-g_entities, "playradiosound 25 0\n\"");
	} else {
		ent->client->radioOff = qfalse;
		trap_SendServerCommand(ent-g_entities, "cp \"Radio switched on\n\"");
		trap_SendServerCommand(ent-g_entities, "playradiosound 25 0\n\"");
	}
}

void RQ3_Cmd_Radiogender_f(gentity_t *ent)
{
	char	arg[MAX_TOKEN_CHARS];

	if (trap_Argc() == 1) {
		if (ent->client->radioGender == 0) {
			trap_SendServerCommand(ent-g_entities, "print \"Radio gender currently set to male\n\"");
			return;
		} else {
			trap_SendServerCommand(ent-g_entities, "print \"Radio gender currently set to female\n\"");
			return;
		}
	}

	trap_Argv(1, arg, sizeof(arg));
	if (Q_stricmp (arg, "male") == 0) {
		trap_SendServerCommand(ent-g_entities, "print \"Radio gender set to male\n\"");
		ent->client->radioGender = 0;
	} else if (Q_stricmp (arg, "female") == 0) {
		trap_SendServerCommand(ent-g_entities, "print \"Radio gender set to female\n\"");
		ent->client->radioGender = 1;
	} else {
		trap_SendServerCommand(ent-g_entities, "print \"Invalid gender selection, try 'male' or 'female'\n\"");
	}
}

radio_msg_t male_radio_msgs[] = {
	{ "1", 6 },
	{ "2", 6 },
	{ "3", 8 },
	{ "4", 7 },
	{ "5", 8 },
	{ "6", 9 },
	{ "7", 8 },
	{ "8", 7 },
	{ "9", 7 },
	{ "10", 6 },
	{ "back", 6 },
	{ "cover", 7 },
	{ "down", 13 },
	{ "enemyd", 10 },
	{ "enemys", 9 },
	{ "forward", 6 },
	{ "go", 6 },
	{ "im_hit", 7 },
	{ "left", 7 },
	{ "reportin", 9 },
	{ "right", 6 },
	{ "taking_f", 22 },
	{ "teamdown", 13 },
	{ "treport", 12 },
	{ "up", 4 },
	{ "click", 4 },
	{ "END", 0 }, // end of list delimiter
};

radio_msg_t female_radio_msgs[] = {
	{ "1", 5 },
	{ "2", 5 },
	{ "3", 5 },
	{ "4", 5 },
	{ "5", 5 },
	{ "6", 8 },
	{ "7", 7 },
	{ "8", 5 },
	{ "9", 5 },
	{ "10", 5 },
	{ "back", 6 },
	{ "cover", 5 },
	{ "down", 6 },
	{ "enemyd", 9 },
	{ "enemys", 9 },
	{ "forward", 8 },
	{ "go", 6 },
	{ "im_hit", 7 },
	{ "left", 8 },
	{ "reportin", 9 },
	{ "right", 5 },
	{ "taking_f", 22 },
	{ "teamdown", 10 },
	{ "treport", 12 },
	{ "up", 6 },
	{ "click", 6 },
	{ "END", 0 }, // end of list delimiter
};

void RQ3_Cmd_Radio_f(gentity_t *ent)
{
	char		msg[MAX_TOKEN_CHARS];
	radio_msg_t	*radio_msgs;
	gentity_t	*player;
	int		i, x, kills;

	if (ent->client->sess.sessionTeam == TEAM_SPECTATOR)
		return;
	if (trap_Argc () < 2)
		return;
	if (ent->client->radioOff == qtrue) {
		trap_SendServerCommand(ent-g_entities, "print \"Your radio is off!\n\"");
		return;
	}
	if (ent->client->radioGender == 0)
		radio_msgs = male_radio_msgs;
	else
		radio_msgs = female_radio_msgs;

	x = 0;

	trap_Argv(1, msg, sizeof(msg));

	while (Q_stricmp(radio_msgs[x].msg, "END")) {
		if (!Q_stricmp(radio_msgs[x].msg, msg)) {
			if (!Q_stricmp(radio_msgs[x].msg, "enemyd")) {
				kills = ent->client->killStreak;
				ent->client->killStreak = 0;
				if (kills >1 && kills <10) {
					for (i = 0; i < level.maxclients; i++) {
						player = &g_entities[i];
						if (!player->inuse)
							continue;
						if (player->client->sess.savedTeam == ent->client->sess.savedTeam)
							trap_SendServerCommand(player-g_entities, va("playradiosound %i %i\n\"",
								kills-1, ent->client->radioGender));
					}
				}
			}
			for (i = 0; i < level.maxclients; i++) {
				player = &g_entities[i];
				if (!player->inuse)
					continue;
				if (player->client->sess.savedTeam == ent->client->sess.savedTeam) {
					if (player->r.svFlags & SVF_BOT)
						trap_SendServerCommand(player-g_entities, va("print \"radio %s %s\n\"",
							ent->client->pers.netname, radio_msgs[x].msg));
					else
						trap_SendServerCommand(player-g_entities, va("playradiosound %i %i\n\"", x,
							ent->client->radioGender));
				}
			}
		}
		x++;
	}
}

char *SeekBufEnd (char *buf)
{
	while (*buf != 0)
		buf++;
	return buf;
}

void GetWeaponName (gentity_t * ent, char *buf)
{
	if (ent->client->ps.weapon == WP_AKIMBO) {
		strcpy (buf, RQ3_AKIMBO_NAME);
		return;
	} else if (ent->client->ps.weapon == WP_PISTOL) {
		strcpy (buf, RQ3_PISTOL_NAME);
		return;
	} else if (ent->client->ps.weapon == WP_MP5) {
		strcpy (buf, RQ3_MP5_NAME);
		return;
	} else if (ent->client->ps.weapon == WP_M4) {
		strcpy (buf, RQ3_M4_NAME);
		return;
	} else if (ent->client->ps.weapon == WP_M3) {
		strcpy (buf, RQ3_M3_NAME);
		return;
	} else if (ent->client->ps.weapon == WP_HANDCANNON) {
		strcpy (buf, RQ3_HANDCANNON_NAME);
		return;
	} else if (ent->client->ps.weapon == WP_SSG3000) {
		strcpy (buf, RQ3_SSG3000_NAME);
		return;
	} else if (ent->client->ps.weapon == WP_KNIFE) {
		strcpy (buf, RQ3_KNIFE_NAME);
		return;
	} else if (ent->client->ps.weapon == WP_GRENADE) {
		strcpy (buf, RQ3_GRENADE_NAME);
		return;
	} else {
		strcpy (buf, "No Weapon");
	}
}

void GetItemName (gentity_t * ent, char *buf)
{
	if (bg_itemlist[ent->client->ps.stats[STAT_HOLDABLE_ITEM]].giTag == HI_KEVLAR) {
		strcpy (buf, RQ3_KEVLAR_NAME);
		return;
	} else if (bg_itemlist[ent->client->ps.stats[STAT_HOLDABLE_ITEM]].giTag == HI_SILENCER) {
		strcpy (buf, RQ3_SILENCER_NAME);
		return;
	} else if (bg_itemlist[ent->client->ps.stats[STAT_HOLDABLE_ITEM]].giTag == HI_SLIPPERS) {
		strcpy (buf, RQ3_SLIPPERS_NAME);
		return;
	} else if (bg_itemlist[ent->client->ps.stats[STAT_HOLDABLE_ITEM]].giTag == HI_BANDOLIER) {
		strcpy (buf, RQ3_BANDOLIER_NAME);
		return;
	} else if (bg_itemlist[ent->client->ps.stats[STAT_HOLDABLE_ITEM]].giTag == HI_LASER) {
		strcpy (buf, RQ3_LASER_NAME);
		return;
	} else {
		strcpy (buf, "No Item");
	}
}

void GetAmmo (gentity_t * ent, char *buf)
{
	int ammo;
	char temp[1024];

	switch (ent->client->ps.weapon) {
	case WP_PISTOL:
		Com_sprintf (temp, sizeof(temp), "%d rounds (%d extra clips)",
			ent->client->ps.ammo[WP_PISTOL],
			ent->client->numClips[WP_PISTOL]);
		strcpy (buf, temp);
		return;
	case WP_SSG3000:
		Com_sprintf (temp, sizeof(temp), "%d rounds (%d extra rounds)",
			ent->client->ps.ammo[WP_SSG3000],
			ent->client->numClips[WP_SSG3000]);
		strcpy (buf, temp);
		return;
	case WP_MP5:
		Com_sprintf (temp, sizeof(temp), "%i rounds (%i extra clips)",
			ent->client->ps.ammo[WP_MP5],
			ent->client->numClips[WP_MP5]);
		strcpy (buf, temp);
		return;
	case WP_M4:
		Com_sprintf (temp, sizeof(temp), "%d rounds (%d extra clips)",
			ent->client->ps.ammo[WP_M4],
			ent->client->numClips[WP_M4]);
		strcpy (buf, temp);
		return;
	case WP_M3:
		Com_sprintf (temp, sizeof(temp), "%d rounds (%d extra shells)",
			ent->client->ps.ammo[WP_M3],
			ent->client->numClips[WP_M3]);
		strcpy (buf, temp);
		return;
	case WP_HANDCANNON:
		Com_sprintf (temp, sizeof(temp), "%d rounds (%d extra shells)",
			ent->client->ps.ammo[WP_HANDCANNON],
			ent->client->numClips[WP_HANDCANNON]);
		strcpy (buf, temp);
		return;
	case WP_AKIMBO:
		Com_sprintf (temp, sizeof(temp), "%d rounds (%d extra clips)",
			ent->client->ps.ammo[WP_AKIMBO],
			ent->client->numClips[WP_AKIMBO]);
		strcpy (buf, temp);
		return;
	case WP_KNIFE:
		ammo = ent->client->ps.ammo[WP_KNIFE];
		Com_sprintf (temp, sizeof(temp), "%d kni%s", ammo, (ammo == 1) ? "fe" : "ves");
		strcpy (buf, temp);
		return;
	case WP_GRENADE:
		ammo = ent->client->ps.ammo[WP_GRENADE];
		Com_sprintf (temp, sizeof(temp), "%d grenade%s", ammo, (ammo == 1) ? "" : "s");
		strcpy (buf, temp);
		return;
	}
}

void ResetKills (gentity_t * ent)
{
	int	i;

	for (i = 0; i < RQ3_MAXKILLS; i++) {
		ent->client->lastkilled_client[i] = NULL;
	}
}

int ReadKilledPlayers (gentity_t * ent)
{
	int	results, i;

	results = -1;
	if (ent->client->lastkilled_client[0] != NULL) {
		for (i = 0; i < RQ3_MAXKILLS; i++) {
			if (ent->client->lastkilled_client[i] != NULL) {
				results++;
			}
		}
		return results;
	} else
		return -1;
}

void AddKilledPlayer (gentity_t * self, gentity_t * ent)
{
	int	kills;

	kills = ReadKilledPlayers (self);
	if (kills == RQ3_MAXKILLS || kills == -1) {
		self->client->lastkilled_client[0] = ent;
	} else {
		self->client->lastkilled_client[kills + 1] = ent;
	}
}

void GetLastKilledTarget (gentity_t * self, char * buf)
{
	int	kills, i;

	kills = ReadKilledPlayers (self);

	if (kills >= 0) {
		strcpy (buf, self->client->lastkilled_client[0]->client->pers.netname);
		if (kills > 0) {
			for (i = 1; i < kills + 1; i++) {
				if (i == kills) {
					strcat (buf, "^5 and ");
					strcat (buf, self->client->lastkilled_client[i]->client->pers.netname);
					strcat (buf, "^5");
				} else {
					strcat (buf, "^5, ");
					strcat (buf, self->client->lastkilled_client[i]->client->pers.netname);
				}
			}
		}
		ResetKills (self);
	} else {
		strcpy (buf, "nobody");
	}
}

void GetLastDamagedPart (gentity_t * self, char * buf)
{
	switch (self->client->lasthurt_location &
		~(LOCATION_BACK | LOCATION_LEFT | LOCATION_RIGHT | LOCATION_FRONT)) {
	case LOCATION_HEAD:
	case LOCATION_FACE:
		strcpy (buf, "head");
		self->client->lasthurt_location = 0;
		return;
	case LOCATION_SHOULDER:
	case LOCATION_CHEST:
		strcpy (buf, "chest");
		self->client->lasthurt_location = 0;
		return;
	case LOCATION_STOMACH:
	case LOCATION_GROIN:
		strcpy (buf, "stomach");
		self->client->lasthurt_location = 0;
		return;
	case LOCATION_LEG:
	case LOCATION_FOOT:
		strcpy (buf, "legs");
		self->client->lasthurt_location = 0;
		return;
	case LOCATION_NONE:
	default:
		strcpy (buf, "nothing");
	}
}

#define MAXNEAR 10
void GetNearbyTeammates (gentity_t *self, char *buf)
{
	char		nearby_teammates[MAXNEAR][MAX_NAME_LENGTH];
	int		nearby_teammates_num, l;
	gentity_t	*ent = NULL;

	nearby_teammates_num = 0;

	while ((ent = findradius (ent, self->s.origin, 1500)) != NULL) {
		if (ent == self || !ent->client || !CanDamage (self, ent->r.currentOrigin) ||
				(ent->client->sess.sessionTeam != self->client->sess.sessionTeam))
			continue;
		strncpy (nearby_teammates[nearby_teammates_num],
				ent->client->pers.netname, MAX_NAME_LENGTH - 1);
		nearby_teammates[nearby_teammates_num][MAX_NAME_LENGTH - 1] = 0;
		nearby_teammates_num++;
		if (nearby_teammates_num >= MAXNEAR)
			break;
	}
	if (nearby_teammates_num == 0) {
		strcpy (buf, "nobody");
		return;
	}
	for (l = 0; l < nearby_teammates_num; l++) {
		if (l == 0) {
			strcpy (buf, nearby_teammates[l]);
		} else {
			if (nearby_teammates_num == 2) {
				strcat (buf, "^5 and ");
				strcat (buf, nearby_teammates[l]);
			} else {
				if (l == (nearby_teammates_num - 1)) {
					strcat (buf, "^5, and ");
					strcat (buf, nearby_teammates[l]);
				} else {
					strcat (buf, "^5, ");
					strcat (buf, nearby_teammates[l]);
				}
			}
		}
	}
}

void ParseSayText (gentity_t *ent, char *text)
{
	static char buf[1024], infobuf[1024];
	char *p, *pbuf;

	p = text;
	pbuf = buf;
	*pbuf = 0;

	while (*p != 0) {
		if ((pbuf - buf) > 225) {
			break;
		}
		if (*p == '$') {
			switch (*(p + 1)) {
			case 'H':
				Com_sprintf (infobuf, sizeof(infobuf), "%d", ent->health);
				strcpy (pbuf, infobuf);
				pbuf = SeekBufEnd (pbuf);
				p += 2;
				continue;
			case 'A':
				GetAmmo (ent, infobuf);
				strcpy (pbuf, infobuf);
				pbuf = SeekBufEnd (pbuf);
				p += 2;
				continue;
			case 'W':
				GetWeaponName (ent, infobuf);
				strcpy (pbuf, infobuf);
				pbuf = SeekBufEnd (pbuf);
				p += 2;
				continue;
			case 'I':
				GetItemName (ent, infobuf);
				strcpy (pbuf, infobuf);
				pbuf = SeekBufEnd (pbuf);
				p += 2;
				continue;
			case 'K':
				GetLastKilledTarget (ent, infobuf);
				strcpy (pbuf, infobuf);
				pbuf = SeekBufEnd (pbuf);
				p += 2;
				continue;
			case 'D':
				GetLastDamagedPart (ent, infobuf);
				strcpy (pbuf, infobuf);
				pbuf = SeekBufEnd (pbuf);
				p += 2;
				continue;
			case 'T':
				GetNearbyTeammates (ent, infobuf);
				strcpy (pbuf, infobuf);
				pbuf = SeekBufEnd (pbuf);
				p += 2;
				continue;
/*			case 'S':
				GetSightedLocation (ent, infobuf);
				strcpy (pbuf, infobuf);
				pbuf = SeekBufEnd (pbuf);
				p += 2;
				continue;
			case 'P':
				GetLastDamagedPlayers (ent, infobuf);
				strcpy (pbuf, infobuf);
				pbuf = SeekBufEnd (pbuf);
				p += 2;
				continue; */
			}
		}
		*pbuf++ = *p++;
	}

	*pbuf = 0;

	strncpy (text, buf, 225);
	text[225] = 0;
}

void RQ3_SpectatorMode(gentity_t *ent)
{
	if (ent->r.svFlags & SVF_BOT)
		return;

	if (ent->client->sess.spectatorState == SPECTATOR_ZCAM)
		trap_SendServerCommand(ent->client->ps.clientNum,
			va("print \"\n" S_COLOR_MAGENTA "Spectator Mode-" S_COLOR_YELLOW"ZCAM-%s\n",
			(ent->client->camera->mode == CAMERA_MODE_SWING)? "SWING":"FLIC"));
	else
	trap_SendServerCommand(ent->client->ps.clientNum,
			va("print \"\n" S_COLOR_MAGENTA "Spectator Mode-" S_COLOR_YELLOW"%s\n",
			(ent->client->sess.spectatorState == SPECTATOR_FREE)? "FREE":"FOLLOW"));
}

void RQ3_Cmd_Use_f(gentity_t *ent)
{
	char	*cmd, buf[128];
	int	weapon, i;

	if (!ent->client) {
		return;		// not fully in game yet
	}

	cmd = ConcatArgs(1);
	weapon = WP_NONE;

	if (Q_stricmp (cmd, RQ3_MP5_NAME) == 0 || Q_stricmp (cmd, "mp5") == 0) {
		if ((ent->client->ps.stats[STAT_WEAPONS] & (1 << WP_MP5) ) == (1 << WP_MP5)) {
			weapon = WP_MP5;
		} else {
			trap_SendServerCommand(ent-g_entities, va("print \"Out of item: %s\n\"", RQ3_MP5_NAME));
			return;
		}
	} else if (Q_stricmp (cmd, RQ3_M3_NAME) == 0 || Q_stricmp (cmd, "m3") == 0) {
		if ((ent->client->ps.stats[STAT_WEAPONS] & (1 << WP_M3) ) == (1 << WP_M3)) {
			weapon = WP_M3;
		} else {
			trap_SendServerCommand(ent-g_entities, va("print \"Out of item: %s\n\"", RQ3_M3_NAME));
			return;
		}
	} else if (Q_stricmp (cmd, RQ3_M4_NAME) == 0 || Q_stricmp (cmd, "m4") == 0) {
		if ((ent->client->ps.stats[STAT_WEAPONS] & (1 << WP_M4) ) == (1 << WP_M4)) {
			weapon = WP_M4;
		} else {
			trap_SendServerCommand(ent-g_entities, va("print \"Out of item: %s\n\"", RQ3_M4_NAME));
			return;
		}
	} else if (Q_stricmp (cmd, RQ3_HANDCANNON_NAME) == 0 || Q_stricmp (cmd, "hc") == 0) {
		if ((ent->client->ps.stats[STAT_WEAPONS] & (1 << WP_HANDCANNON) ) == (1 << WP_HANDCANNON)) {
			weapon = WP_HANDCANNON;
		} else {
			trap_SendServerCommand(ent-g_entities, va("print \"Out of item: %s\n\"", RQ3_HANDCANNON_NAME));
			return;
		}
	} else if (Q_stricmp (cmd, RQ3_SSG3000_NAME) == 0 || Q_stricmp (cmd, "sniper") == 0) {
		if ((ent->client->ps.stats[STAT_WEAPONS] & (1 << WP_SSG3000) ) == (1 << WP_SSG3000)) {
			weapon = WP_SSG3000;
		} else {
			trap_SendServerCommand(ent-g_entities, va("print \"Out of item: %s\n\"", RQ3_SSG3000_NAME));
			return;
		}
	} else if (Q_stricmp (cmd, RQ3_AKIMBO_NAME) == 0 || Q_stricmp (cmd, "akimbo") == 0) {
		if ((ent->client->ps.stats[STAT_WEAPONS] & (1 << WP_AKIMBO) ) == (1 << WP_AKIMBO)) {
			weapon = WP_AKIMBO;
		} else {
			trap_SendServerCommand(ent-g_entities, va("print \"Out of item: %s\n\"", RQ3_AKIMBO_NAME));
			return;
		}
	} else if (Q_stricmp (cmd, RQ3_PISTOL_NAME) == 0 || Q_stricmp (cmd, "pistol") == 0) {
		if ((ent->client->ps.stats[STAT_WEAPONS] & (1 << WP_PISTOL) ) == (1 << WP_PISTOL)) {
			weapon = WP_PISTOL;
		} else {
			trap_SendServerCommand(ent-g_entities, va("print \"Out of item: %s\n\"", RQ3_AKIMBO_NAME));
			return;
		}
	} else if (Q_stricmp (cmd, RQ3_GRENADE_NAME) == 0 || Q_stricmp (cmd, "grenade") == 0) {
		if ((ent->client->ps.stats[STAT_WEAPONS] & (1 << WP_GRENADE) ) == (1 << WP_GRENADE)) {
			weapon = WP_GRENADE;
		} else {
			trap_SendServerCommand(ent-g_entities, va("print \"Out of item: %s\n\"", RQ3_GRENADE_NAME));
			return;
		}
	} else if (Q_stricmp (cmd, "throwing combat knife") == 0) {
		if ((ent->client->ps.stats[STAT_WEAPONS] & (1 << WP_KNIFE) ) == (1 << WP_KNIFE)) {
			weapon = WP_KNIFE;
			ent->client->ps.persistant[PERS_WEAPONMODES] &= ~RQ3_KNIFEMODE;
		} else {
			trap_SendServerCommand(ent-g_entities, va("print \"Out of item: %s\n\"", RQ3_KNIFE_NAME));
			return;
		}
	} else if (Q_stricmp (cmd, "slashing combat knife") == 0) {
		if ((ent->client->ps.stats[STAT_WEAPONS] & (1 << WP_KNIFE) ) == (1 << WP_KNIFE)) {
			weapon = WP_KNIFE;
			ent->client->ps.persistant[PERS_WEAPONMODES] |= RQ3_KNIFEMODE;
		} else {
			trap_SendServerCommand(ent-g_entities, va("print \"Out of item: %s\n\"", RQ3_KNIFE_NAME));
			return;
		}
	} else if (Q_stricmp (cmd, "special") == 0) {
		for (i = WP_NUM_WEAPONS - 1; i > 0; i--) {
			if (i == WP_KNIFE || i == WP_PISTOL || i == WP_AKIMBO || i == WP_GRENADE)
				continue;
			if (ent->client->ps.stats[STAT_WEAPONS] & (1 << i)) {
				weapon = i;
				break;
			}
		}
		if (weapon == WP_NONE) {
			trap_SendServerCommand(ent-g_entities, va("print \"You dont have a special weapon!\n\""));
			return;
		}
	}
	if (weapon == WP_NONE) {
		trap_SendServerCommand(ent-g_entities, va("print \"Unknown item: %s\n\"", cmd));
		return;
	}
	if (weapon == ent->client->ps.weapon)
		return;
	Com_sprintf (buf, sizeof(buf), "weapon %d\n", weapon);
	trap_SendConsoleCommand(EXEC_APPEND, buf);
}

void Add_TeamWound(gentity_t *attacker, gentity_t *victim, int mod)
{
	char	userinfo[MAX_INFO_STRING];
	char	*value;

	if (g_gametype.integer != GT_TEAMPLAY || !attacker->client || !victim->client)
		return;

	attacker->client->team_wounds++;

	if (attacker->client->ff_warning == 0) {
		attacker->client->ff_warning++;
		trap_SendServerCommand(victim-g_entities, va("print \"You were hit by %s, your TEAMMATE!\n\"",
				attacker->client->pers.netname));
		trap_SendServerCommand(attacker-g_entities, va("print \"You hit your TEAMMATE %s!\n\"",
				victim->client->pers.netname));
	}
	attacker->client->team_wounds = (attacker->client->team_wounds_before + 1);

	if (g_RQ3_maxteamkills.integer < 1)
		return;
	if (attacker->client->team_wounds < (g_RQ3_maxteamkills.integer * 3)) {
		return;
	} else if (attacker->client->team_wounds < (g_RQ3_maxteamkills.integer * 4)) {
		trap_SendServerCommand(-1, va("print \"%s is in danger of being banned for wounding teammates\n\"",
			attacker->client->pers.netname));
		trap_SendServerCommand(attacker-g_entities, va("print \"WARNING: You'll be temporarily banned if you continue wounding teammates!\n\""));
		return;
	} else {
		trap_SendServerCommand(-1, va("print \"Banning %s for team wounding\n\"", attacker->client->pers.netname));
		trap_SendServerCommand(attacker-g_entities, va("print \"You've wounded teammates too many times, and are banned for %d %s.\n\"",
				g_RQ3_twbanrounds.integer, ((g_RQ3_twbanrounds.integer > 1) ? "games" : "game")));
		trap_GetUserinfo(attacker-g_entities, userinfo, sizeof(userinfo));
		value = Info_ValueForKey (userinfo, "ip");
		AddIP(value);
		trap_DropClient(attacker-g_entities, "Dropped due to team wounding");
	}
}

void Add_TeamKill(gentity_t *attacker)
{
	char	userinfo[MAX_INFO_STRING];
	char	*value;

	if (g_gametype.integer != GT_TEAMPLAY || !attacker->client)
		return;

	attacker->client->team_kills++;

	if (attacker->client->team_wounds > attacker->client->team_wounds_before)
		attacker->client->team_wounds = attacker->client->team_wounds_before;

	if ((g_RQ3_maxteamkills.integer < 1) ||
			(attacker->client->team_kills < ((g_RQ3_maxteamkills.integer % 2) + g_RQ3_maxteamkills.integer / 2))) {
		trap_SendServerCommand(attacker-g_entities, va("print \"You killed your TEAMMATE!\n\""));
		return;
	} else if (attacker->client->team_kills < g_RQ3_maxteamkills.integer) {
		trap_SendServerCommand(-1, va("print \"%s is in danger of being banned for killing teammates\n\"",
			attacker->client->pers.netname));
		trap_SendServerCommand(attacker-g_entities, va("print \"WARNING: You'll be temporarily banned if you continue killing teammates!\n\""));
		return;
	} else {
		trap_SendServerCommand(-1, va("print \"Banning %s for team killing\n\"", attacker->client->pers.netname));
		trap_SendServerCommand(attacker-g_entities, va("print \"You've killed too many teammates, and are banned for %d %s.\n", g_RQ3_tkbanrounds.integer,
			((g_RQ3_tkbanrounds.integer > 1) ? "games" : "game")));
		trap_GetUserinfo(attacker-g_entities, userinfo, sizeof(userinfo));
		value = Info_ValueForKey (userinfo, "ip");
		AddIP(value);
		trap_DropClient(attacker-g_entities, "Dropped due to team killing");
	}
}

void setFFState(gentity_t *ent)
{
	if (ent && ent->client) {
		ent->client->team_wounds_before = ent->client->team_wounds;
		ent->client->ff_warning = 0;
	}
}
