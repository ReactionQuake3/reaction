//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.1  2002/01/11 20:23:41  jbravo
// Added the two new files for TP I forgot during the main TP commit
//
//
//-----------------------------------------------------------------------------

#include "g_local.h"
gitem_t	*BG_FindItemForHoldable( holdable_t pw );
char	*ConcatArgs( int start );

void CheckTeamRules()
{
	int winner, i;
	int checked_tie = 0;
	gentity_t *player;

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
			StartLCA();
		} else {
			trap_SendServerCommand( -1, va("cp \"Not enough players to play!\n\""));
			MakeAllLivePlayersObservers();
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
			if (level.time - level.startTime >= g_timelimit.integer*60000) {
				trap_SendServerCommand( -1, va("cp \"Timelimit hit.\n\""));
				level.team_round_going = level.team_round_countdown = level.team_game_going = 0;
				return;
			}
		}
		if (!level.team_round_countdown) {
			if (BothTeamsHavePlayers()) {
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
	int i;
	gentity_t *player;

	CleanLevel();
	trap_Cvar_Set("RQ3_lca", "1");
	level.lights_camera_action = (41*level.fps)/10;
	SpawnPlayers();

	trap_SendServerCommand( -1, va("cp \"LIGHTS...\n\""));
	for (i = 0; i < level.maxclients; i++) {
		player = &g_entities[i];
		if (!player->inuse)
			continue;
		G_AddEvent ( player, EV_RQ3_SOUND, RQ3_SOUND_LIGHTS);
//		break;
	}
}

void ContinueLCA()
{
	int i;
	gentity_t *player;

	if (level.lights_camera_action == (21*level.fps)/10) {
		trap_SendServerCommand( -1, va("cp \"CAMERA...\n\""));
		for (i = 0; i < level.maxclients; i++) {
			player = &g_entities[i];
			if (!player->inuse)
				continue;
			G_AddEvent ( player, EV_RQ3_SOUND, RQ3_SOUND_CAMERA);
//			break;
		}
	}
	else if (level.lights_camera_action == 1) {
		trap_SendServerCommand( -1, va("cp \"ACTION!\n\""));
		trap_Cvar_Set("RQ3_lca", "0");
		for (i = 0; i < level.maxclients; i++) {
			player = &g_entities[i];
			if (!player->inuse)
				continue;
			G_AddEvent ( player, EV_RQ3_SOUND, RQ3_SOUND_ACTION);
//			break;
		}
		level.team_round_going = 1;
		level.current_round_length = 0;
	}
	level.lights_camera_action--;
}

qboolean BothTeamsHavePlayers()
{
	int onteam1 = 0, onteam2 = 0;

	onteam1 = RQ3TeamCount( -1, TEAM_RED );
	onteam2 = RQ3TeamCount( -1, TEAM_BLUE );

	return (onteam1 > 0 && onteam2 > 0);
}

void MakeAllLivePlayersObservers()
{
	gentity_t	*player;
	int		saveteam, i;

	for (i = 0; i < level.maxclients; i++) {
		player = &g_entities[i];
		if (!player->inuse)
			continue;
		level.clients[i].sess.savedTeam = level.clients[i].sess.sessionTeam;
		level.clients[i].sess.sessionTeam = TEAM_SPECTATOR;
		level.clients[i].sess.spectatorState = SPECTATOR_FOLLOW;
	}
}

void CleanLevel()
{
	gentity_t	*ent;
	int		i;

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
			trap_SendServerCommand( -1, "print \"Team 1 won!\n\"" );
			level.teamScores[TEAM_RED]++;
		} else {
			trap_SendServerCommand( -1, "print \"Team 2 won!\n\"" );
			level.teamScores[TEAM_BLUE]++;
		}
	}

	if (g_timelimit.integer) {
		if (level.time - level.startTime >= g_timelimit.integer*60000) {
			trap_SendServerCommand( -1, "print \"Timelimit hit.\n\"" );
			level.team_round_going = level.team_round_countdown = level.team_game_going = 0;
			return 1;
		}
	}

	if (g_RQ3_roundlimit.integer) {
		if (level.teamScores[TEAM_RED] >= g_RQ3_roundlimit.integer || level.teamScores[TEAM_BLUE] >= g_RQ3_roundlimit.integer) {
			trap_SendServerCommand( -1, "Roundlimit hit.\n\"" );
			level.team_round_going = level.team_round_countdown = level.team_game_going = 0;
			return 1;
		}
	}

	return 0;
}

team_t RQ3TeamCount( int ignoreClientNum, int team )
{
	int	i;
	int	count = 0;

	for ( i = 0 ; i < level.maxclients ; i++ ) {
		if ( i == ignoreClientNum ) {
			continue;
		}
		if ( level.clients[i].pers.connected == CON_DISCONNECTED ) {
			continue;
		}
		if ( level.clients[i].sess.savedTeam == team ) {
			count++;
		}
	}

	return count;
}

void CheckForUnevenTeams(gentity_t *player)
{
	int		i, onteam1 = 0, onteam2 = 0;
	gentity_t	*ent;
	char		buffer[1024];

	for (i = 0; i < level.maxclients; i++) {
		ent = &g_entities[i];
		if (ent->inuse) {
			if (ent->client->sess.savedTeam == TEAM_RED)
				onteam1++;
			else if (ent->client->sess.savedTeam == TEAM_BLUE)
				onteam2++;
		}
	}
	if (onteam1 > onteam2)
		trap_SendServerCommand(player-g_entities, va("print \"Your team now has %d more player%s than team 2\n\"",
			onteam1 - onteam2, onteam1 - onteam2 == 1 ? "" : "s"));
	else if (onteam2 > onteam1)
		trap_SendServerCommand(player-g_entities, va("print \"Your team now has %d more player%s than team 1\n\"",
			onteam2 - onteam1, onteam2 - onteam1 == 1 ? "" : "s"));
}

void SpawnPlayers()
{
	gentity_t	*player;
	gclient_t	*client;
	int		clientNum, i;

	client->sess.teamSpawn = qtrue;
	level.spawnPointsLocated = qfalse;
	for (i = 0; i < level.maxclients; i++) {
		player = &g_entities[i];

		if (!player->inuse)
			continue;

		client = player->client;
		clientNum = client - level.clients;
		if (client->sess.savedTeam == TEAM_RED) {
			client->sess.sessionTeam = TEAM_RED;
		} else if (client->sess.savedTeam == TEAM_BLUE) {
			client->sess.sessionTeam = TEAM_BLUE;
		}
		ClientSpawn(player);
		ClientUserinfoChanged(clientNum);
	}
	client->sess.teamSpawn = qfalse;
}

/* Let the player Choose the weapon and/or item he wants */
void RQ3_Cmd_Choose_f( gentity_t *ent )
{
//	char	cmd[MAX_STRING_CHARS];
	char	*cmd;
	int	len, c;

	if ( !ent->client ) {
		return;		// not fully in game yet
	}

//	trap_Argv( 1, cmd, sizeof( cmd ) );

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
	} else if (Q_stricmp (cmd, RQ3_KNIFE_NAME) == 0 || Q_stricmp (cmd, "knifes") == 0) {
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

	ent->client->ps.weapon = ent->client->teamplayWeapon;
	ent->client->numClips[ WP_PISTOL ] = 1;			// extra clip of ammo for pistol
	ent->client->ps.ammo[ WP_PISTOL] = RQ3_PISTOL_AMMO;
	ent->client->ps.persistant[PERS_WEAPONMODES] |= RQ3_KNIFEMODE;
	
	if (ent->client->teamplayItem == HI_BANDOLIER) {
		bandolierFactor = 2;
		grenades = trap_Cvar_VariableIntegerValue( "g_RQ3_tgren" );
		if (grenades > 0)
			ent->client->ps.ammo[WP_GRENADE] = grenades;
			ent->client->ps.persistant[PERS_WEAPONMODES] |= RQ3_GRENSHORT;
	} else {
		bandolierFactor = 1;
	}

	switch(ent->client->ps.weapon) {
	case WP_SSG3000:
		ent->client->numClips[ WP_SSG3000 ] = RQ3_SSG3000_EXTRA_AMMO;
		ent->client->ps.ammo[ WP_SSG3000 ] = RQ3_SSG3000_AMMO;
		break;
	case WP_MP5:
		ent->client->numClips[ WP_MP5 ] = RQ3_MP5_EXTRA_AMMO;
		ent->client->ps.ammo[ WP_MP5 ] = RQ3_MP5_AMMO;
		break;
	case WP_M3:
		ent->client->numClips[ WP_M3 ] = RQ3_M3_EXTRA_AMMO;
		ent->client->ps.ammo[ WP_M3 ] = RQ3_M3_AMMO;
		break;
	case WP_M4:
		ent->client->numClips[ WP_M4 ] = RQ3_M4_EXTRA_AMMO;
		ent->client->ps.ammo[ WP_M4 ] = RQ3_M4_AMMO;
		break;
	case WP_AKIMBO:
		ent->client->numClips[ WP_AKIMBO ] = RQ3_AKIMBO_EXTRA_AMMO;
		ent->client->ps.ammo[ WP_AKIMBO ] = RQ3_AKIMBO_AMMO;
		break;
	case WP_HANDCANNON:
		ent->client->numClips[ WP_HANDCANNON ] = RQ3_HANDCANNON_EXTRA_AMMO;
		ent->client->ps.ammo[ WP_HANDCANNON ] = RQ3_HANDCANNON_AMMO;
		break;
	default:
		break;
	}
	ent->client->weaponCount[ent->client->ps.weapon] = 1;
	ent->client->uniqueWeapons = 1;
	ent->client->ps.stats[STAT_WEAPONS] = ( 1 << ent->client->ps.weapon );
	ent->client->ps.stats[STAT_WEAPONS] |= ( 1 << WP_PISTOL );
	ent->client->ps.stats[STAT_WEAPONS] |= ( 1 << WP_KNIFE );
	if(grenades > 0) {
		ent->client->ps.stats[STAT_WEAPONS] |= ( 1 << WP_GRENADE );
		ent->client->uniqueWeapons++;
	}
	ent->client->ps.weaponstate = WEAPON_READY;

	ent->client->ps.stats[STAT_HOLDABLE_ITEM] = BG_FindItemForHoldable( ent->client->teamplayItem ) - bg_itemlist;
	ent->client->uniqueItems = 1;
}
