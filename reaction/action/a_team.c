/*
 * Teamplay-related code for Action (formerly Axshun).  
 * Some of this is borrowed from Zoid's CTF (thanks Zoid)
 * -Fireblade
 */

#include "g_local.h"
#include "cgf_sfx_glass.h"

qboolean team_game_going = 0;   // is a team game going right now?
qboolean team_round_going = 0;  // is an actual round of a team game going right now?
int team_round_countdown = 0;   // countdown variable for start of a round
int rulecheckfrequency = 0;     // accumulator variable for checking rules every 1.5 secs
int lights_camera_action = 0;   // countdown variable for "lights...camera...action!" 
int holding_on_tie_check = 0;   // when a team "wins", countdown for a bit and wait...
int current_round_length = 0;   // frames that the current team round has lasted

int team1_score = 0;
int team2_score = 0;
int team1_total = 0;
int team2_total = 0;

#define MAX_SPAWNS 1000 // max DM spawn points supported

edict_t *potential_spawns[MAX_SPAWNS];  
int num_potential_spawns;
edict_t *teamplay_spawns[MAX_TEAMS];
trace_t trace_t_temp;  // used by our trace replace macro in ax_team.h

int num_teams = 2;              // teams in current game, fixed at 2 for now...

transparent_list_t *transparent_list = NULL;


void CreditsMenu(edict_t *ent, pmenu_t *p);


void InitTransparentList()
{
        if (transparent_list != NULL)
        {
                transparent_list_t *p, *q;

                p = transparent_list;
                while (p != NULL)
                {
                        q = p->next;
                        gi.TagFree(p);
                        p = q;
                }

                transparent_list = NULL;
        }
}

void AddToTransparentList(edict_t *ent)
{
        transparent_list_t *p, *n;

        n = (transparent_list_t *)gi.TagMalloc(sizeof(transparent_list_t), TAG_GAME);
        if (n == NULL)
        {
                gi.dprintf("Out of memory\n");
                exit(1);
        }
        n->ent = ent;
        n->next = NULL;

        if (transparent_list == NULL)
        {
                transparent_list = n;
        }
                else
        {
                p = transparent_list;
                while (p->next != NULL)
                {
                        p = p->next;
                }
                p->next = n;
        }
}

void RemoveFromTransparentList(edict_t *ent)
{
        transparent_list_t *p, *q, *r;

        if (transparent_list != NULL)
        {
                if (transparent_list->ent == ent)
                {
                        q = transparent_list->next;
                        gi.TagFree(transparent_list);
                        transparent_list = q;
                        return;
                }
                        else
                {
                        p = transparent_list;
                        q = p->next;
                        while (q != NULL)
                        {
                                if (q->ent == ent)
                                {
                                        r = q->next;
                                        gi.TagFree(q);
                                        p->next = r;
                                        return;
                                }
                                p = p->next;
                                q = p->next;
                        }
                }
        }

        gi.dprintf("Warning: attempt to RemoveFromTransparentList when not in it\n");
}               

void TransparentListSet(solid_t solid_type)
{
        transparent_list_t *p = transparent_list;

        while (p != NULL)
        {
                p->ent->solid = solid_type;
                gi.linkentity(p->ent);
                p = p->next;
        }
}

void ReprintMOTD(edict_t *ent, pmenu_t *p)
{
        PMenu_Close(ent);
        PrintMOTD(ent);
}

void JoinTeam1(edict_t *ent, pmenu_t *p)
{
        JoinTeam(ent, TEAM1, 0);
}

void JoinTeam2(edict_t *ent, pmenu_t *p)
{
        JoinTeam(ent, TEAM2, 0);
}

void SelectWeapon2(edict_t *ent, pmenu_t *p)
{
        ent->client->resp.weapon = FindItem(MP5_NAME);
        PMenu_Close(ent);
        OpenItemMenu(ent);
}

void SelectWeapon3(edict_t *ent, pmenu_t *p)
{
        ent->client->resp.weapon = FindItem(M3_NAME);
        PMenu_Close(ent);
        OpenItemMenu(ent);
}

void SelectWeapon4(edict_t *ent, pmenu_t *p)
{
        ent->client->resp.weapon = FindItem(HC_NAME);
        PMenu_Close(ent);
        OpenItemMenu(ent);
}

void SelectWeapon5(edict_t *ent, pmenu_t *p)
{
        ent->client->resp.weapon = FindItem(SNIPER_NAME);
        PMenu_Close(ent);
        OpenItemMenu(ent);
}

void SelectWeapon6(edict_t *ent, pmenu_t *p)
{
        ent->client->resp.weapon = FindItem(M4_NAME);
        PMenu_Close(ent);
        OpenItemMenu(ent);
}

void SelectWeapon0(edict_t *ent, pmenu_t *p)
{
        ent->client->resp.weapon = FindItem(KNIFE_NAME);
        PMenu_Close(ent);
        OpenItemMenu(ent);
}

void SelectWeapon9(edict_t *ent, pmenu_t *p)
{
        ent->client->resp.weapon = FindItem(DUAL_NAME);
        PMenu_Close(ent);
        OpenItemMenu(ent);
}

void SelectItem1(edict_t *ent, pmenu_t *p)
{
        ent->client->resp.item = FindItem(KEV_NAME);
        PMenu_Close(ent);
}

void SelectItem2(edict_t *ent, pmenu_t *p)
{
        ent->client->resp.item = FindItem(LASER_NAME);
        PMenu_Close(ent);
}

void SelectItem3(edict_t *ent, pmenu_t *p)
{
        ent->client->resp.item = FindItem(SLIP_NAME);
        PMenu_Close(ent);
}

void SelectItem4(edict_t *ent, pmenu_t *p)
{
        ent->client->resp.item = FindItem(SIL_NAME);
        PMenu_Close(ent);
}

void SelectItem5(edict_t *ent, pmenu_t *p)
{
        ent->client->resp.item = FindItem(BAND_NAME);
        PMenu_Close(ent);
}

void CreditsReturnToMain(edict_t *ent, pmenu_t *p)
{
        PMenu_Close(ent);
        OpenJoinMenu(ent);
}

pmenu_t creditsmenu[] = {
  { "*Action Quake 2",                      PMENU_ALIGN_CENTER, NULL, NULL },
  { "--------------",                       PMENU_ALIGN_CENTER, NULL, NULL },
  { "*Head Design, Original Programming",   PMENU_ALIGN_CENTER, NULL, NULL },
  { "Sam 'Cail' Thompson",                PMENU_ALIGN_CENTER, NULL, NULL },
  { "*Sounds, Second-In-Command",           PMENU_ALIGN_CENTER, NULL, NULL },
  { "Patrick 'Bartender' Mills",          PMENU_ALIGN_CENTER, NULL, NULL },
  { "*Original Programming",                PMENU_ALIGN_CENTER, NULL, NULL },
  { "Nathan 'Pietro' Kovner",             PMENU_ALIGN_CENTER, NULL, NULL },
  { "Michael 'Siris' Taylor",             PMENU_ALIGN_CENTER, NULL, NULL },
  { "*Skins, Etc",                          PMENU_ALIGN_CENTER, NULL, NULL },
  { "Jon 'Vain' Delee",                   PMENU_ALIGN_CENTER, NULL, NULL },
  { "*Levels",                              PMENU_ALIGN_CENTER, NULL, NULL },
  { "Evan 'Ace12GA' Prentice",            PMENU_ALIGN_CENTER, NULL, NULL },
  { "*Models, Skins, Etc",                  PMENU_ALIGN_CENTER, NULL, NULL },
  { "Minh 'Gooseman' Le",                 PMENU_ALIGN_CENTER, NULL, NULL },
  { "Dallas 'Suislide' Frank",            PMENU_ALIGN_CENTER, NULL, NULL },
  { "*Action 1.5 ('Axshun') Programming", PMENU_ALIGN_CENTER, NULL, NULL },
  { "Carl 'Zucchini' Schedvin",                PMENU_ALIGN_CENTER, NULL, NULL },
  { "Bob 'Fireblade' Farmer",             PMENU_ALIGN_CENTER, NULL, NULL },


  { NULL,                               PMENU_ALIGN_LEFT, NULL, NULL },
  { "Return to main menu",              PMENU_ALIGN_LEFT, NULL, CreditsReturnToMain },
  { NULL,                               PMENU_ALIGN_LEFT, NULL, NULL },
  { "TAB to exit menu",    PMENU_ALIGN_LEFT, NULL, NULL },
  { NULL,                                 PMENU_ALIGN_LEFT, NULL, NULL },
  { "v" ACTION_VERSION,       PMENU_ALIGN_RIGHT, NULL, NULL },
};

pmenu_t weapmenu[] = {
  { "*Action Quake 2",                 PMENU_ALIGN_CENTER, NULL, NULL },
  { "--------------",                   PMENU_ALIGN_CENTER, NULL, NULL },
  { "Select your weapon",               PMENU_ALIGN_CENTER, NULL, NULL },
  { NULL,                               PMENU_ALIGN_LEFT, NULL, NULL },
  { "MP5/10 Submachinegun",             PMENU_ALIGN_LEFT, NULL, SelectWeapon2 },
  { "M3 Super90 Assault Shotgun",       PMENU_ALIGN_LEFT, NULL, SelectWeapon3 },
  { "Handcannon",                       PMENU_ALIGN_LEFT, NULL, SelectWeapon4 },
  { "SSG 3000 Sniper Rifle",              PMENU_ALIGN_LEFT, NULL, SelectWeapon5 },
  { "M4 Assault Rifle",                   PMENU_ALIGN_LEFT, NULL, SelectWeapon6 },
  { "Combat Knives",                      PMENU_ALIGN_LEFT, NULL, SelectWeapon0 },
  { "Akimbo Pistols",                     PMENU_ALIGN_LEFT, NULL, SelectWeapon9 },
  { NULL,                               PMENU_ALIGN_LEFT, NULL, NULL },
  { "Use [ and ] to move cursor", PMENU_ALIGN_LEFT, NULL, NULL },
  { "ENTER to select",    PMENU_ALIGN_LEFT, NULL, NULL },
  { "TAB to exit menu",    PMENU_ALIGN_LEFT, NULL, NULL },
  { NULL,                                 PMENU_ALIGN_LEFT, NULL, NULL },
  { "v" ACTION_VERSION,       PMENU_ALIGN_RIGHT, NULL, NULL },
};

pmenu_t itemmenu[] = {
  { "*Action Quake 2",                 PMENU_ALIGN_CENTER, NULL, NULL },
  { "--------------",                   PMENU_ALIGN_CENTER, NULL, NULL },
  { "Select your item",               PMENU_ALIGN_CENTER, NULL, NULL },
  { NULL,                               PMENU_ALIGN_LEFT, NULL, NULL },
  { "Kevlar Vest",             PMENU_ALIGN_LEFT, NULL, SelectItem1 },
  { "Laser Sight",       PMENU_ALIGN_LEFT, NULL, SelectItem2 },
  { "Stealth Slippers",                       PMENU_ALIGN_LEFT, NULL, SelectItem3 },
  { "Silencer",              PMENU_ALIGN_LEFT, NULL, SelectItem4 },
  { "Bandolier",                   PMENU_ALIGN_LEFT, NULL, SelectItem5 },
  { NULL,                               PMENU_ALIGN_LEFT, NULL, NULL },
  { "Use [ and ] to move cursor", PMENU_ALIGN_LEFT, NULL, NULL },
  { "ENTER to select",    PMENU_ALIGN_LEFT, NULL, NULL },
  { "TAB to exit menu",    PMENU_ALIGN_LEFT, NULL, NULL },
  { NULL,                                 PMENU_ALIGN_LEFT, NULL, NULL },
  { "v" ACTION_VERSION,       PMENU_ALIGN_RIGHT, NULL, NULL },
};

pmenu_t joinmenu[] = {
  { "*Action Quake 2",                 PMENU_ALIGN_CENTER, NULL, NULL },
  { NULL /* lvl name */,                PMENU_ALIGN_CENTER, NULL, NULL },
  { NULL,                               PMENU_ALIGN_CENTER, NULL, NULL },
  { NULL /* team 1 */,                  PMENU_ALIGN_LEFT, NULL, JoinTeam1 },
  { NULL,                               PMENU_ALIGN_LEFT, NULL, NULL },
  { NULL /* team 2 */,                  PMENU_ALIGN_LEFT, NULL, JoinTeam2 },
  { NULL,                               PMENU_ALIGN_LEFT, NULL, NULL },
  { NULL,                                 PMENU_ALIGN_LEFT, NULL, NULL },
  { "MOTD",                               PMENU_ALIGN_LEFT, NULL, ReprintMOTD },
  { "Credits",                            PMENU_ALIGN_LEFT, NULL, CreditsMenu },
  { NULL,                                 PMENU_ALIGN_LEFT, NULL, NULL },
  { "Use [ and ] to move cursor", PMENU_ALIGN_LEFT, NULL, NULL },
  { "ENTER to select",    PMENU_ALIGN_LEFT, NULL, NULL },
  { "TAB to exit menu",   PMENU_ALIGN_LEFT, NULL, NULL },
  { NULL,                                 PMENU_ALIGN_LEFT, NULL, NULL },
  { "v" ACTION_VERSION,       PMENU_ALIGN_RIGHT, NULL, NULL },
};

void CreditsMenu(edict_t *ent, pmenu_t *p)
{
        PMenu_Close(ent);
        PMenu_Open(ent, creditsmenu, 4, sizeof(creditsmenu) / sizeof(pmenu_t));
}

char *TeamName(int team)
{
        if (team == TEAM1)
                return team1_name;
                else if (team == TEAM2)
                return team2_name;
                else
                return "None";
}

void AssignSkin(edict_t *ent, char *s)
{
        int playernum = ent-g_edicts-1;

        switch (ent->client->resp.team)
        {
                case TEAM1:
                        gi.configstring (CS_PLAYERSKINS+playernum, va("%s\\%s", 
                                ent->client->pers.netname, team1_skin) );
                        break;
                case TEAM2:
                        gi.configstring (CS_PLAYERSKINS+playernum,
                                va("%s\\%s", ent->client->pers.netname, team2_skin) );
                        break;
                default:
                        gi.configstring (CS_PLAYERSKINS+playernum, 
                                va("%s\\%s", ent->client->pers.netname, s) );
                        break;
        }
}

void Team_f(edict_t *ent)
{
        char *t;
        int desired_team;

        t = gi.args();
        if (!*t)
        {
                gi.cprintf(ent, PRINT_HIGH, "You are on %s.\n",
                                TeamName(ent->client->resp.team));
                return;
        }

        if (level.framenum < (ent->client->resp.joined_team + 50))
        {
                gi.cprintf(ent, PRINT_HIGH, "You must wait 5 seconds before changing teams again.\n");
                return;
        }

        if (Q_stricmp(t, "none") == 0)
        {
                if (ent->client->resp.team == NOTEAM)
                {
                        gi.cprintf(ent, PRINT_HIGH, "You're not on a team.\n");
                }
                        else
                {
                        LeaveTeam(ent);
                }
                return;
        }

        if (Q_stricmp(t, "1") == 0)
                desired_team = TEAM1;
                else if (Q_stricmp(t, "2") == 0)
                desired_team = TEAM2;
                else if (Q_stricmp(t, team1_name) == 0)
                desired_team = TEAM1;
                else if (Q_stricmp(t, team2_name) == 0)
                desired_team = TEAM2;
                else
        {
                gi.cprintf(ent, PRINT_HIGH, "Unknown team %s.\n", t);
                return;
        }

        if (ent->client->resp.team == desired_team)
        {
                gi.cprintf(ent, PRINT_HIGH, "You are already on %s.\n",
                              TeamName(ent->client->resp.team));
                return;
        }

        JoinTeam(ent, desired_team, 1);
}

void UnevenTeamsMsg(int whichteam, int uneven_amount, char *opponent)
{
        int i;
        edict_t *e;

        for (i = 1; i <= maxclients->value; i++)
        {
                e = g_edicts + i;
                if (e->inuse)
                {
                        if (e->client->resp.team == whichteam)
                        {
                                gi.cprintf(e, PRINT_HIGH, "Your team now has %d more player%s than %s.\n", 
                                              uneven_amount, uneven_amount == 1 ? "" : "s", opponent);
                                stuffcmd(e, "play misc/comp_up.wav");
                        }
                }  
        }
}

void CheckForUnevenTeams()
{
        int i, onteam1 = 0, onteam2 = 0;
        edict_t *e;

        // only use these messages during 2-team games...
        if (num_teams > 2)
                return;

        for (i = 1; i <= maxclients->value; i++)
        {
                e = g_edicts + i;
                if (e->inuse)
                {
                        if (e->client->resp.team == TEAM1)
                                onteam1++;
                                else if (e->client->resp.team == TEAM2)
                                onteam2++;
                }  
        }
        if (onteam1 > onteam2)
                UnevenTeamsMsg(TEAM1, onteam1 - onteam2, team2_name);
                else if (onteam2 > onteam1)
                UnevenTeamsMsg(TEAM2, onteam2 - onteam1, team1_name);
}

void JoinTeam(edict_t *ent, int desired_team, int skip_menuclose)
{
        char *s, *a;
  
        if (!skip_menuclose)
        {
                PMenu_Close(ent);
        }

        if (ent->client->resp.team == desired_team)
                return;

        a = (ent->client->resp.team == NOTEAM) ? "joined" : "changed to";

        ent->client->resp.team = desired_team;
        s = Info_ValueForKey (ent->client->pers.userinfo, "skin");
        AssignSkin(ent, s);

        if (ent->solid != SOLID_NOT)  // alive, in game
        {
                ent->health = 0;
                player_die (ent, ent, ent, 100000, vec3_origin);
                ent->deadflag = DEAD_DEAD;
        }

        gi.bprintf(PRINT_HIGH, "%s %s %s.\n",
                        ent->client->pers.netname, a, TeamName(desired_team));

        ent->client->resp.joined_team = level.framenum;

        CheckForUnevenTeams();

        if (!skip_menuclose)
                OpenWeaponMenu(ent);
}

void LeaveTeam(edict_t *ent)
{
        char *g;
  
        if (ent->client->resp.team == NOTEAM)
                return;

        if (ent->solid != SOLID_NOT)  // alive, in game
        {
                ent->health = 0;
                player_die (ent, ent, ent, 100000, vec3_origin);
                ent->deadflag = DEAD_DEAD;
        }

        if (IsNeutral(ent))
                g = "its";
                else if (IsFemale(ent))
                g = "her";
                else
                g = "his";
        gi.bprintf(PRINT_HIGH, "%s left %s team.\n", ent->client->pers.netname, g);

        ent->client->resp.joined_team = 0;
        ent->client->resp.team = NOTEAM;

        CheckForUnevenTeams();
}

void ReturnToMain(edict_t *ent, pmenu_t *p)
{
        PMenu_Close(ent);
        OpenJoinMenu(ent);
}

void OpenItemMenu(edict_t *ent)
{
        PMenu_Open(ent, itemmenu, 4, sizeof(itemmenu) / sizeof(pmenu_t));
}

void OpenWeaponMenu(edict_t *ent)
{
        PMenu_Open(ent, weapmenu, 4, sizeof(weapmenu) / sizeof(pmenu_t));
}

int UpdateJoinMenu(edict_t *ent)
{
        static char levelname[32];
        static char team1players[32];
        static char team2players[32];
        int num1, num2, i;

        joinmenu[3].text = team1_name;
        joinmenu[3].SelectFunc = JoinTeam1;
        joinmenu[5].text = team2_name;
        joinmenu[5].SelectFunc = JoinTeam2;

        levelname[0] = '*';
        if (g_edicts[0].message)
                strncpy(levelname+1, g_edicts[0].message, sizeof(levelname) - 2);
                else
                strncpy(levelname+1, level.mapname, sizeof(levelname) - 2);
        levelname[sizeof(levelname) - 1] = 0;

        num1 = num2 = 0;
        for (i = 0; i < maxclients->value; i++)
        {
                if (!g_edicts[i+1].inuse)
                        continue;
                if (game.clients[i].resp.team == TEAM1)
                        num1++;
                        else if (game.clients[i].resp.team == TEAM2)
                        num2++;
        }

        sprintf(team1players, "  (%d players)", num1);
        sprintf(team2players, "  (%d players)", num2);

        joinmenu[1].text = levelname;
        if (joinmenu[3].text)
                joinmenu[4].text = team1players;
                else
                joinmenu[4].text = NULL;
        if (joinmenu[5].text)
                joinmenu[6].text = team2players;
                else
                joinmenu[6].text = NULL;

        if (num1 > num2)
                return TEAM2;
                else if (num2 > num1)
                return TEAM1;
                else if (team1_score > team2_score)
                return TEAM2;
                else if (team2_score > team1_score)
                return TEAM1;
                else
                return TEAM1;
}

void OpenJoinMenu(edict_t *ent)
{
        int team;

        team = UpdateJoinMenu(ent);
        if (team == TEAM1)
                team = 3;
                else
                team = 5;
        PMenu_Open(ent, joinmenu, team, sizeof(joinmenu) / sizeof(pmenu_t));
}

int member_array(char *str, char *arr[], int num_elems)
{
        int l;
        for (l = 0; l < num_elems; l++)
        {
                if (!strcmp(str, arr[l]))
                        return l;
        }
        return -1;
}

void CleanLevel()
{
        char *remove_classnames[] = 
        {
                "weapon_Mk23",
                "weapon_MP5",
                "weapon_M4",
                "weapon_M3",
                "weapon_HC",
                "weapon_Sniper",
                "weapon_Dual",
                "weapon_Knife",
                "weapon_Grenade",
                "ammo_sniper",
                "ammo_clip",
                "ammo_mag",
                "ammo_m4",
                "ammo_m3",
                "item_quiet",
                "item_slippers",
                "item_band",
                "item_lasersight",
                "item_vest",
                                "thrown_knife",
                                "hgrenade",

        };
        int i;
        int base;
        edict_t *ent;
 
        base = 1 + maxclients->value + BODY_QUEUE_SIZE;
        ent = g_edicts + base;
        for (i = 1 + maxclients->value + BODY_QUEUE_SIZE; 
                        i < globals.num_edicts; 
                        i++, ent++)
        {
                if (!ent->classname)
                        continue;
                if (member_array(ent->classname, remove_classnames, 
                                        sizeof(remove_classnames) / sizeof(char *)) > -1)
                {
                        G_FreeEdict(ent);
                }
        }

        CleanBodies();

        // fix glass
        CGF_SFX_RebuildAllBrokenGlass();
}

qboolean StartClient(edict_t *ent)
{
        if (ent->client->resp.team != NOTEAM)
                return false;

        // start as 'observer'
        ent->movetype = MOVETYPE_NOCLIP;
        ent->solid = SOLID_NOT;
        ent->svflags |= SVF_NOCLIENT;
        ent->client->resp.team = NOTEAM;
        ent->client->ps.gunindex = 0; 
        gi.linkentity (ent);

        return true;
}

void CenterPrintAll(char *msg)
{
        int i;
        edict_t *ent;

        gi.cprintf(NULL, PRINT_HIGH, msg); // so it goes to the server console...

        for (i = 0; i < game.maxclients; i++)
        {
                ent = &g_edicts[1+i];
                if (!ent->inuse)
                        continue;
                gi.centerprintf(ent, "%s", msg);
        }               
}

qboolean BothTeamsHavePlayers()
{
        int onteam1 = 0, onteam2 = 0, i;
        edict_t *ent;

        for (i = 0; i < game.maxclients; i++)
        {
                ent = &g_edicts[1+i];
                if (!ent->inuse)
                        continue;
                if (game.clients[i].resp.team == TEAM1)
                        onteam1++;
                        else if (game.clients[i].resp.team == TEAM2)
                        onteam2++;
        }

        return (onteam1 > 0 && onteam2 > 0);
}

// CheckForWinner: Checks for a winner (or not).
int CheckForWinner()
{
        int onteam1 = 0, onteam2 = 0, i;
        edict_t *ent;

        for (i = 0; i < game.maxclients; i++)
        {
                ent = &g_edicts[1+i];
                if (!ent->inuse)
                        continue;
                if (game.clients[i].resp.team == TEAM1 && 
                                ent->solid != SOLID_NOT)
                        onteam1++;
                        else if (game.clients[i].resp.team == TEAM2 && 
                                        ent->solid != SOLID_NOT)
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

// CheckForForcedWinner: A winner is being forced, find who it is.
int CheckForForcedWinner()
{
        int onteam1 = 0, onteam2 = 0, i;
        int health1 = 0, health2 = 0;
        edict_t *ent;

        for (i = 0; i < game.maxclients; i++)
        {
                ent = &g_edicts[1+i];
                if (!ent->inuse)
                        continue;
                if (game.clients[i].resp.team == TEAM1 && ent->solid != SOLID_NOT)
                {
                        onteam1++;
                        health1 += ent->health;
                }
                        else if (game.clients[i].resp.team == TEAM2 && ent->solid != SOLID_NOT)
                {
                        onteam2++;
                        health2 += ent->health;
                }
        }
  
        if (onteam1 > onteam2)
        {
                return WINNER_TEAM1;
        }
                else if (onteam2 > onteam1)
        {
                return WINNER_TEAM2;
        }
                else
        {
                if (health1 > health2)
                        return WINNER_TEAM1;
                        else if (health2 > health1)
                        return WINNER_TEAM2;
                        else
                        return WINNER_TIE;
        }
}

void SpawnPlayers()
{
        int i;
        edict_t *ent;
        
        GetSpawnPoints();
        SetupTeamSpawnPoints();
        InitTransparentList();
        for (i = 0; i < game.maxclients; i++)
        {
                ent = &g_edicts[1+i];
                if (ent->inuse && ent->client->resp.team != NOTEAM)
                {
                        PutClientInServer(ent);
                        AddToTransparentList(ent);
                }
        }
}

void StartRound()
{
        team_round_going = 1;
        current_round_length = 0;
}

void StartLCA()
{
        CleanLevel();
   
        CenterPrintAll("LIGHTS...\n");
        gi.sound(&g_edicts[0], CHAN_VOICE | CHAN_NO_PHS_ADD, 
                gi.soundindex("atl/lights.wav"), 1.0, ATTN_NONE, 0.0);
        lights_camera_action = 41;
        SpawnPlayers();
}

// FindOverlap: Find the first (or next) overlapping player for ent.
edict_t *FindOverlap(edict_t *ent, edict_t *last_overlap)
{
        int i;
        edict_t *other;
        vec3_t diff;

        for (i = last_overlap ? last_overlap - g_edicts : 0; i < game.maxclients; i++)
        {
                other = &g_edicts[i+1];

                if (!other->inuse || other->client->resp.team == NOTEAM
                                || other == ent 
                                || other->solid == SOLID_NOT
                                || other->deadflag == DEAD_DEAD)
                        continue;

                VectorSubtract(ent->s.origin, other->s.origin, diff);

                if (diff[0] >= -33 && diff[0] <= 33 &&
                                diff[1] >= -33 && diff[1] <= 33 &&
                                diff[2] >= -65 && diff[2] <= 65)
                        return other;
        }

        return NULL;
}

void ContinueLCA()
{
        if (lights_camera_action == 21)
        {
                CenterPrintAll("CAMERA...\n");
                gi.sound(&g_edicts[0], CHAN_VOICE | CHAN_NO_PHS_ADD, 
                gi.soundindex("atl/camera.wav"), 1.0, ATTN_NONE, 0.0);
        }
                else if (lights_camera_action == 1)
        { 
                CenterPrintAll("ACTION!\n");
                gi.sound(&g_edicts[0], CHAN_VOICE | CHAN_NO_PHS_ADD, 
                gi.soundindex("atl/action.wav"), 1.0, ATTN_NONE, 0.0);
                StartRound();
        }
        lights_camera_action--;
}

void MakeAllLivePlayersObservers()
{
        edict_t *ent;
        int saveteam, i;

        for (i = 0; i < game.maxclients; i++)
        {
                ent = &g_edicts[1+i];
                if (!ent->inuse || ent->solid == SOLID_NOT)
                        continue;
                saveteam = ent->client->resp.team;
                ent->client->resp.team = NOTEAM;
                PutClientInServer(ent);
                ent->client->resp.team = saveteam;
        }
}

// WonGame: returns true if we're exiting the level.
int WonGame(int winner)
{
        gi.bprintf(PRINT_HIGH, "The round is over:\n");

        if (winner == WINNER_TIE)
        {
                gi.bprintf(PRINT_HIGH, "It was a tie, no points awarded!\n");
        }
                else        
        {
                if (winner == WINNER_TEAM1)
                {
                        gi.bprintf(PRINT_HIGH, "%s won!\n", TeamName(TEAM1));
                        team1_score++;
                }
                        else
                {
                        gi.bprintf(PRINT_HIGH, "%s won!\n", TeamName(TEAM2));
                        team2_score++;
                }
        }

        if (timelimit->value)
        {
                if (level.time >= timelimit->value*60)
                {
                        gi.bprintf(PRINT_HIGH, "Timelimit hit.\n");
                        EndDMLevel();
                        team_round_going = team_round_countdown = team_game_going = 0;
                        return 1;
                }
        }

        if (roundlimit->value)
        {
                if (team1_score >= roundlimit->value || team2_score >= roundlimit->value)
                {
                        gi.bprintf(PRINT_HIGH, "Roundlimit hit.\n");
                        EndDMLevel();
                        team_round_going = team_round_countdown = team_game_going = 0;
                        return 1;
                }
        }

        return 0;
}


void CheckTeamRules()
{
        int winner;
        int checked_tie = 0;

        if (lights_camera_action)
        {
                ContinueLCA();
                return;
        }

        if (team_round_going)
                current_round_length++;

        if (holding_on_tie_check)
        {
                holding_on_tie_check--;
                if (holding_on_tie_check > 0)
                        return;
                holding_on_tie_check = 0;
                checked_tie = 1;
        }

        if (team_round_countdown == 1)
        {
                team_round_countdown = 0;
                if (BothTeamsHavePlayers())
                {
                        team_game_going = 1;
                        StartLCA();
                }
                        else
                {
                        CenterPrintAll("Not enough players to play!\n");
                        MakeAllLivePlayersObservers();
                }
        }
                else
        {
                if (team_round_countdown)
                        team_round_countdown--;
        }

        // check these rules every 1.5 seconds...
        rulecheckfrequency++;
        if (rulecheckfrequency % 15 && !checked_tie)  
                return;

        if (!team_round_going)
        {
                if (timelimit->value)
                {
                        if (level.time >= timelimit->value*60)
                        {
                                gi.bprintf (PRINT_HIGH, "Timelimit hit.\n");
                                EndDMLevel();
                                team_round_going = team_round_countdown = team_game_going = 0;
                                return;
                        }
                }

                if (!team_round_countdown)
                {
                        if (BothTeamsHavePlayers())
                        {
                                CenterPrintAll("The round will begin in 20 seconds!\n");
                                team_round_countdown = 201;
                        }
                }
        }
                else /* team_round_going */
        {
                if ((winner = CheckForWinner()) != WINNER_NONE)
                {
                        if (!checked_tie)
                        {
                                holding_on_tie_check = 50;
                                return;
                        }
                        if (WonGame(winner))
                                return;
                        team_round_going = 0;
                        lights_camera_action = 0;
                        holding_on_tie_check = 0;
                        team_round_countdown = 71;
                        return;
                }

                if (roundtimelimit->value &&
                        (current_round_length > roundtimelimit->value * 600))
                {
                        gi.bprintf(PRINT_HIGH, "Round timelimit hit.\n");
                        winner = CheckForForcedWinner();
                        if (WonGame(winner))
                                return;
                        team_round_going = 0;
                        lights_camera_action = 0;
                        holding_on_tie_check = 0;
                        team_round_countdown = 71;
                        return;
                }
        }
}


void A_Scoreboard(edict_t *ent)
{
        if (ent->client->showscores && ent->client->scoreboardnum == 1)
        {
                // blink header of the winning team during intermission
                if (level.intermissiontime && (level.framenum & 8)) { // blink 1/8th second
                        if (team1_score > team2_score)
                                ent->client->ps.stats[STAT_TEAM1_PIC] = 0;
                        else if (team2_score > team1_score)
                                ent->client->ps.stats[STAT_TEAM2_PIC] = 0;
                        else if (team1_total > team2_total) // frag tie breaker
                                ent->client->ps.stats[STAT_TEAM1_PIC] = 0;
                        else if (team2_total > team1_total) 
                                ent->client->ps.stats[STAT_TEAM2_PIC] = 0;
                        else { // tie game!
                                ent->client->ps.stats[STAT_TEAM1_PIC] = 0;
                                ent->client->ps.stats[STAT_TEAM2_PIC] = 0;
                        }
                }
                        else
                {
                        ent->client->ps.stats[STAT_TEAM1_PIC] = gi.imageindex(team1_skin_index);
                        ent->client->ps.stats[STAT_TEAM2_PIC] = gi.imageindex(team2_skin_index);
                }

                ent->client->ps.stats[STAT_TEAM1_SCORE] = team1_score;
                ent->client->ps.stats[STAT_TEAM2_SCORE] = team2_score;
        }
}

// Maximum number of lines of scores to put under each team's header.
#define MAX_SCORES_PER_TEAM 9
        
void A_ScoreboardMessage (edict_t *ent, edict_t *killer)
{
        char        string[1400], damage[50];
        gclient_t   *cl;
        edict_t     *cl_ent;
        int         maxsize = 1000, i, j, k;

        if (ent->client->scoreboardnum == 1)
        {
                int team, len, deadview;
                int sorted[TEAM_TOP][MAX_CLIENTS];
                int sortedscores[TEAM_TOP][MAX_CLIENTS];
                int score, total[TEAM_TOP], totalscore[TEAM_TOP];
                int totalalive[TEAM_TOP], totalaliveprinted[TEAM_TOP];
                int stoppedat[TEAM_TOP];
                int name_pos[TEAM_TOP];

                deadview = (ent->solid == SOLID_NOT ||
                        ent->deadflag == DEAD_DEAD ||
                        !team_round_going);

                ent->client->ps.stats[STAT_TEAM_HEADER] = gi.imageindex ("tag3");

                total[TEAM1] = total[TEAM2] = totalalive[TEAM1] = totalalive[TEAM2] = 
                        totalscore[TEAM1] = totalscore[TEAM2] = 0;

                for (i=0 ; i<game.maxclients ; i++)
                {
                        cl_ent = g_edicts + 1 + i;
                        if (!cl_ent->inuse)
                                continue;
        
                        if (game.clients[i].resp.team == NOTEAM)
                                continue;
                                else
                                team = game.clients[i].resp.team;
        
                        score = game.clients[i].resp.score;
                        if (noscore->value)
                        {
                                j = total[team];
                        }
                                else
                        {
                                for (j = 0; j < total[team]; j++)
                                {
                                        if (score > sortedscores[team][j])
                                                break;
                                }
                                for (k=total[team] ; k>j ; k--)
                                {
                                        sorted[team][k] = sorted[team][k-1];
                                        sortedscores[team][k] = sortedscores[team][k-1];
                                }
                        }
                        sorted[team][j] = i;
                        sortedscores[team][j] = score;
                        totalscore[team] += score;
                        total[team]++;
                        if (cl_ent->solid != SOLID_NOT &&
                                cl_ent->deadflag != DEAD_DEAD)
                                totalalive[team]++;
                }
        
                // I've shifted the scoreboard position 8 pixels to the left in Axshun so it works
                // correctly in 320x240 (Action's does not)--any problems with this?  -FB
                // Also going to center the team names.

                name_pos[TEAM1] = ((20 - strlen(team1_name)) / 2) * 8;
                if (name_pos[TEAM1] < 0)
                        name_pos[TEAM1] = 0;
                name_pos[TEAM2] = ((20 - strlen(team2_name)) / 2) * 8;
                if (name_pos[TEAM2] < 0)
                        name_pos[TEAM2] = 0;

                sprintf(string, 
                        // TEAM1
                        "if 24 xv 0 yv 8 pic 24 endif "  
                        "if 22 xv 32 yv 8 pic 22 endif "
                        "xv 32 yv 28 string \"%4d/%-3d\" "
                        "xv 90 yv 12 num 2 26 "
                        "xv %d yv 0 string \"%s\" "
                        // TEAM2
                        "if 25 xv 160 yv 8 pic 25 endif "  
                        "if 22 xv 192 yv 8 pic 22 endif "
                        "xv 192 yv 28 string \"%4d/%-3d\" "
                        "xv 248 yv 12 num 2 27 "
                        "xv %d yv 0 string \"%s\" ",
                        totalscore[TEAM1], total[TEAM1], name_pos[TEAM1], team1_name,
                        totalscore[TEAM2], total[TEAM2], name_pos[TEAM2] + 160, team2_name);
        
                len = strlen(string);

                totalaliveprinted[TEAM1] = totalaliveprinted[TEAM2] = 0;
                stoppedat[TEAM1] = stoppedat[TEAM2] = -1;
        
                for (i=0 ; i < (MAX_SCORES_PER_TEAM + 1) ; i++)
                {
                        if (i >= total[TEAM1] && i >= total[TEAM2])
                                break; 
        
                        // ok, if we're approaching the "maxsize", then let's stop printing members of each
                        // teams (if there's more than one member left to print in that team...)
                        if (len > (maxsize - 100))
                        {
                                if (i < (total[TEAM1] - 1))
                                        stoppedat[TEAM1] = i;
                                if (i < (total[TEAM2] - 1))
                                        stoppedat[TEAM2] = i;
                        }
                        if (i == MAX_SCORES_PER_TEAM-1) 
                        {
                                if (total[TEAM1] > MAX_SCORES_PER_TEAM)
                                        stoppedat[TEAM1] = i;
                                if (total[TEAM2] > MAX_SCORES_PER_TEAM)
                                        stoppedat[TEAM2] = i;
                        }
        
                        if (i < total[TEAM1] && stoppedat[TEAM1] == -1)  // print next team 1 member...
                        {
                                cl = &game.clients[sorted[TEAM1][i]];
                                cl_ent = g_edicts + 1 + sorted[TEAM1][i];
                                if (cl_ent->solid != SOLID_NOT &&
                                        cl_ent->deadflag != DEAD_DEAD)
                                        totalaliveprinted[TEAM1]++;
        
                                // AQ truncates names at 12, not sure why, except maybe to conserve scoreboard 
                                // string space?  skipping that "feature".  -FB
        
                                sprintf(string+strlen(string), 
                                        "xv 0 yv %d string%s \"%s\" ",  
                                        42 + i * 8,
                                        deadview ? (cl_ent->solid == SOLID_NOT ? "" : "2") : "",
                                        game.clients[sorted[TEAM1][i]].pers.netname);
                        }
        
                        if (i < total[TEAM2] && stoppedat[TEAM2] == -1)  // print next team 2 member...
                        {
                                cl = &game.clients[sorted[TEAM2][i]];
                                cl_ent = g_edicts + 1 + sorted[TEAM2][i];
                                if (cl_ent->solid != SOLID_NOT &&
                                        cl_ent->deadflag != DEAD_DEAD)
                                        totalaliveprinted[TEAM2]++;
        
                                // AQ truncates names at 12, not sure why, except maybe to conserve scoreboard 
                                // string space?  skipping that "feature".  -FB
        
                                sprintf(string+strlen(string), 
                                        "xv 160 yv %d string%s \"%s\" ",  
                                        42 + i * 8,
                                        deadview ? (cl_ent->solid == SOLID_NOT ? "" : "2") : "",
                                        game.clients[sorted[TEAM2][i]].pers.netname);
                        }
        
                        len = strlen(string);
                }
        
                // Print remaining players if we ran out of room...
                if (!deadview) // live player viewing scoreboard...
                {
                        if (stoppedat[TEAM1] > -1)
                        {
                                sprintf(string + strlen(string), "xv 0 yv %d string \"..and %d more\" ",
                                        42 + (stoppedat[TEAM1] * 8), total[TEAM1] - stoppedat[TEAM1]);
                        }
                        if (stoppedat[TEAM2] > -1)
                        {
                                sprintf(string + strlen(string), "xv 160 yv %d string \"..and %d more\" ",
                                        42 + (stoppedat[TEAM2] * 8), total[TEAM2] - stoppedat[TEAM2]);
                        }
                }
                        else // dead player viewing scoreboard...
                {
                        if (stoppedat[TEAM1] > -1)
                        {
                                sprintf(string + strlen(string), "xv 0 yv %d string%s \"..and %d/%d more\" ",
                                        42 + (stoppedat[TEAM1] * 8), 
                                        (totalalive[TEAM1] - totalaliveprinted[TEAM1]) ? "2" : "",
                                        totalalive[TEAM1] - totalaliveprinted[TEAM1],
                                        total[TEAM1] - stoppedat[TEAM1]);
                        }
                        if (stoppedat[TEAM2] > -1)
                        {
                                sprintf(string + strlen(string), "xv 160 yv %d string%s \"..and %d/%d more\" ",
                                        42 + (stoppedat[TEAM2] * 8), 
                                        (totalalive[TEAM2] - totalaliveprinted[TEAM2]) ? "2" : "",
                                        totalalive[TEAM2] - totalaliveprinted[TEAM2],
                                        total[TEAM2] - stoppedat[TEAM2]);
                        }
                }
        }

                else if (ent->client->scoreboardnum == 2)

        {
                int total, score, ping;
                int sortedscores[MAX_CLIENTS], sorted[MAX_CLIENTS];

                total = score = 0;

                for (i = 0; i < game.maxclients; i++)
                {
                        cl_ent = g_edicts + 1 + i;
                        if (!cl_ent->inuse)
                                continue;
        
                        score = game.clients[i].resp.score;
                        if (noscore->value)
                        {
                                j = total;
                        }
                        else
                        {
                                for (j = 0; j < total; j++)
                                {
                                        if (score > sortedscores[j])
                                                break;
                                }
                                for (k = total ; k > j ; k--)
                                {
                                        sorted[k] = sorted[k-1];
                                        sortedscores[k] = sortedscores[k-1];
                                }
                        }
                        sorted[j] = i;
                        sortedscores[j] = score;
                        total++;
                }

                if (noscore->value)
                {
                        strcpy(string,  "xv 0 yv 32 string2 \"Player          Time Ping\" "
                                        "xv 0 yv 40 string2 \"--------------- ---- ----\" ");
                }
                        else
                {
                        strcpy(string,  "xv 0 yv 32 string2 \"Frags Player          Time Ping Damage\" "
                                        "xv 0 yv 40 string2 \"----- --------------- ---- ---- ------\" ");
                }

                for (i = 0; i < total; i++)
                {
                        ping = game.clients[sorted[i]].ping;
                        if (ping > 999)
                                ping = 999;
                        if (noscore->value)
                        {
                                sprintf(string + strlen(string), 
                                        "xv 0 yv %d string \"%-15s %4d %4d\" ",
                                        48 + i * 8, 
                                        game.clients[sorted[i]].pers.netname,
                                        (level.framenum - game.clients[sorted[i]].resp.enterframe)/600,
                                        ping);                  
                        }       
                        else
                        {
				if (game.clients[sorted[i]].resp.damage_dealt < 1000000)
					sprintf(damage, "%d", game.clients[sorted[i]].resp.damage_dealt);
					else
					strcpy(damage, "******");
                                sprintf(string + strlen(string), 
                                        "xv 0 yv %d string \"%5d %-15s %4d %4d %6s\" ",
                                        48 + i * 8, 
                                        sortedscores[i],
                                        game.clients[sorted[i]].pers.netname,
                                        (level.framenum - game.clients[sorted[i]].resp.enterframe)/600,
                                        ping, damage);                  
                        }

                        if (strlen(string) > (maxsize - 100) &&
                                i < (total - 2))
                        {
                                sprintf(string + strlen(string),
                                        "xv 0 yv %d string \"..and %d more\" ",
                                        48 + (i + 1) * 8,
                                        (total - i - 1));
                                break;
                        }
                }
        }


        if (strlen(string) > 1300)  // for debugging...
                gi.dprintf("Warning: scoreboard string neared or exceeded max length\nDump:\n%s\n---\n", 
                                string);

        gi.WriteByte (svc_layout);
        gi.WriteString (string);
}

// called when we enter the intermission
void TallyEndOfLevelTeamScores(void)
{
        int i;

        team1_total = team2_total = 0;
        for (i = 0; i < maxclients->value; i++)
        {
                if (!g_edicts[i+1].inuse)
                        continue;
                if (game.clients[i].resp.team == TEAM1)
                        team1_total += game.clients[i].resp.score;
                else if (game.clients[i].resp.team == TEAM2)
                        team2_total += game.clients[i].resp.score;
        }
}


/*
 * Teamplay spawning functions...
 */

edict_t *SelectTeamplaySpawnPoint(edict_t *ent)
{
        return teamplay_spawns[ent->client->resp.team - 1];
}

// SpawnPointDistance: 
// Returns the distance between two spawn points (or any entities, actually...)
float SpawnPointDistance(edict_t *spot1, edict_t *spot2)
{
        vec3_t v;
        VectorSubtract (spot1->s.origin, spot2->s.origin, v);
        return VectorLength(v);
}

// GetSpawnPoints:
// Put the spawn points into our potential_spawns array so we can work with them easily.
void GetSpawnPoints()
{
        edict_t *spot;

        spot = NULL;
        num_potential_spawns = 0;
        while ((spot = G_Find (spot, FOFS(classname), "info_player_deathmatch")) != NULL)
        {
                potential_spawns[num_potential_spawns] = spot;
                num_potential_spawns++;
                if (num_potential_spawns >= MAX_SPAWNS)
                {
                        gi.dprintf("Warning: MAX_SPAWNS exceeded\n");
                        return;
                }
        }
}

// newrand returns n, where 0 >= n < top
int newrand(int top)
{
        return (int)(random() * top);
}

// compare_spawn_distances is used by the qsort() call
int compare_spawn_distances(const void *sd1, const void *sd2)
{
        if (((spawn_distances_t *)sd1)->distance < 
                ((spawn_distances_t *)sd2)->distance)
                return -1;
                else if (((spawn_distances_t *)sd1)->distance >
                        ((spawn_distances_t *)sd2)->distance)
                return 1;
                else
                return 0;
}

void SelectRandomTeamplaySpawnPoint(int team, qboolean teams_assigned[])
{
        int spawn_point;
        spawn_point = newrand(num_potential_spawns);
        teamplay_spawns[team] = potential_spawns[spawn_point];
        teams_assigned[team] = true;
}

void SelectFarTeamplaySpawnPoint(int team, qboolean teams_assigned[])
{
        int x, y, spawn_to_use, preferred_spawn_points, num_already_used,
                total_good_spawn_points;
        float closest_spawn_distance, distance;
        spawn_distances_t *spawn_distances;

        spawn_distances = (spawn_distances_t *)gi.TagMalloc(num_potential_spawns * sizeof(spawn_distances_t), TAG_GAME);

        num_already_used = 0;
        for (x = 0; x < num_potential_spawns; x++)
        {
                closest_spawn_distance = 2000000000;

                for (y = 0; y < num_teams; y++)
                {
                        if (teams_assigned[y])
                        {
                                distance = SpawnPointDistance(potential_spawns[x], teamplay_spawns[y]);
                                if (distance < closest_spawn_distance)
                                {
                                        closest_spawn_distance = distance;
                                }
                        }
                }

                if (closest_spawn_distance == 0)
                        num_already_used++;

                spawn_distances[x].s = potential_spawns[x];
                spawn_distances[x].distance = closest_spawn_distance;
        }

        qsort(spawn_distances, num_potential_spawns, 
                sizeof(spawn_distances_t), compare_spawn_distances);

        total_good_spawn_points = num_potential_spawns - num_already_used;

        if (total_good_spawn_points <= 4)
                preferred_spawn_points = 1;
                else
                if (total_good_spawn_points <= 10)
                preferred_spawn_points = 2;
                else
                preferred_spawn_points = 3;

//FB 6/1/99 - make DF_SPAWN_FARTHEST force far spawn points in TP
        if ((int)dmflags->value & DF_SPAWN_FARTHEST)
                preferred_spawn_points = 1;
//FB 6/1/99

        spawn_to_use = newrand(preferred_spawn_points);

	if (team < 0 || team >= MAX_TEAMS)
	{
		gi.dprintf("Out-of-range teams value in SelectFarTeamplaySpawnPoint, skipping...\n");
	}
		else
	{
	        teams_assigned[team] = true;
	        teamplay_spawns[team] = spawn_distances[num_potential_spawns - spawn_to_use - 1].s;
	}

        gi.TagFree(spawn_distances);
}

// SetupTeamSpawnPoints:
//
// Setup the points at which the teams will spawn.
//
void SetupTeamSpawnPoints()
{
        qboolean teams_assigned[MAX_TEAMS];
        int started_at, l, firstassignment;

        for (l = 0; l < num_teams; l++)
        {
                teamplay_spawns[l] = NULL;
                teams_assigned[l] = false;
        }

        started_at = l = newrand(num_teams);
        firstassignment = 1;
        do
        {
                if (l < 0 || l >= MAX_TEAMS)
                {
                        gi.dprintf("Warning: attempt to setup spawns for out-of-range team (%d)\n", l);
                }

                if (firstassignment)
                {
                        SelectRandomTeamplaySpawnPoint(l, teams_assigned);
                        firstassignment = 0;
                }
                        else
                {
                        SelectFarTeamplaySpawnPoint(l, teams_assigned);
                }
                l++;
                if (l == num_teams)
                        l = 0;
        } while (l != started_at);
}
