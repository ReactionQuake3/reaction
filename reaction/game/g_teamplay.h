//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.2  2002/01/27 13:33:28  jbravo
// Teamplay antistick system.
//
// Revision 1.1  2002/01/11 20:23:41  jbravo
// Added the two new files for TP I forgot during the main TP commit
//
//
//-----------------------------------------------------------------------------

#define WINNER_NONE	0
#define WINNER_TEAM1	1
#define WINNER_TEAM2	2
#define WINNER_TIE	3

void CheckTeamRules();
void StartLCA();
void ContinueLCA();
qboolean BothTeamsHavePlayers();
void MakeAllLivePlayersObservers();
int CheckForWinner();
int CheckForForcedWinner();
int WonGame(int winner);
team_t RQ3TeamCount(int ignoreClientNum, int team);
void SpawnPlayers();
void CleanLevel();
void CheckForUnevenTeams(gentity_t *player);
void EquipPlayer (gentity_t *ent);
void RQ3_Cmd_Choose_f(gentity_t *ent);
void RQ3_Cmd_Drop_f( gentity_t *ent );
void UnstickPlayer( gentity_t *ent );
