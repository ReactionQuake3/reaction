//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.52  2005/09/07 20:27:42  makro
// Entity attachment trees
//
// Revision 1.51  2005/02/15 16:33:39  makro
// Tons of updates (entity tree attachment system, UI vectors)
//
// Revision 1.50  2004/01/26 21:26:08  makro
// no message
//
// Revision 1.49  2003/09/18 00:05:05  makro
// Lens flares. Opendoor trigger_multiple fixes
//
// Revision 1.48  2003/09/10 22:46:05  makro
// Cooler breath puffs. Locked r_fastSky on maps with global fog.
// Some other things I can't remember.
//
// Revision 1.47  2003/09/08 19:19:20  makro
// New code for respawning entities in TP
//
// Revision 1.46  2003/09/07 20:02:51  makro
// no message
//
// Revision 1.45  2003/08/10 20:13:26  makro
// no message
//
// Revision 1.44  2003/04/26 22:33:06  jbravo
// Wratted all calls to G_FreeEnt() to avoid crashing and provide debugging
//
// Revision 1.43  2003/02/27 19:52:34  makro
// dlights
//
// Revision 1.42  2003/01/06 00:23:29  makro
// no message
//
// Revision 1.41  2003/01/05 22:36:50  makro
// Added "inactive" field for entities
// New "target_activate" entity
//
// Revision 1.40  2002/09/01 21:15:08  makro
// Sky portal tweaks
//
// Revision 1.39  2002/08/30 00:00:16  makro
// Sky portals
//
// Revision 1.38  2002/08/25 00:46:52  niceass
// q3f atmosphere
//
// Revision 1.37  2002/07/19 04:29:18  niceass
// typo fix
//
// Revision 1.36  2002/07/13 22:43:59  makro
// Semi-working fog hull, semi-working sky portals (cgame code commented out)
// Basically, semi-working stuff :P
//
// Revision 1.35  2002/06/29 04:15:15  jbravo
// CTF is now CTB.  no weapons while the case is in hand other than pistol or knife
//
// Revision 1.34  2002/06/24 05:51:51  jbravo
// CTF mode is now semi working
//
// Revision 1.33  2002/06/21 21:02:07  niceass
// worldspawn laserfog check
//
// Revision 1.32  2002/06/16 20:06:14  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.31  2002/06/16 17:38:00  jbravo
// Removed the MISSIONPACK ifdefs and missionpack only code.
//
// Revision 1.30  2002/06/12 11:14:35  makro
// Fixed knives/pistols not spawning bug
//
// Revision 1.29  2002/06/08 11:41:48  makro
// weapon_grenadelauncher = weapon_pistol
//
// Revision 1.28  2002/05/30 21:18:28  makro
// Bots should reload/bandage when roaming around
// Added "pathtarget" key to all the entities
//
// Revision 1.27  2002/05/25 10:40:31  makro
// Loading screen
//
// Revision 1.26  2002/05/23 15:55:25  makro
// Elevators
//
// Revision 1.25  2002/05/11 12:45:25  makro
// Spectators can go through breakables and doors with
// a targetname or health. Bots should crouch more/jump less
// often when attacking at long range
//
// Revision 1.24  2002/05/05 15:18:02  makro
// Fixed some crash bugs. Bot stuff. Triggerable func_statics.
// Made flags only spawn in CTF mode
//
// Revision 1.23  2002/05/04 06:28:58  makro
// no message
//
// Revision 1.22  2002/05/04 01:03:43  makro
// Bots
//
// Revision 1.21  2002/05/02 23:05:25  makro
// Loading screen. Jump kicks. Bot stuff
//
// Revision 1.20  2002/05/02 12:44:58  makro
// Customizable color for the loading screen text. Bot stuff
//
// Revision 1.19  2002/04/30 12:23:35  jbravo
// Warningfix
//
// Revision 1.18  2002/04/30 11:54:37  makro
// Bots rule ! Also, added clips to give all. Maybe some other things
//
// Revision 1.17  2002/04/23 06:01:39  niceass
// pressure stuff
//
// Revision 1.16  2002/04/20 02:34:57  jbravo
// Changed weapon and ammo classnames at Sze's request
//
// Revision 1.15  2002/04/03 15:51:01  jbravo
// Small warning fixes
//
// Revision 1.14  2002/04/03 03:13:16  blaze
// NEW BREAKABLE CODE - will break all old breakables(wont appear in maps)
//
// Revision 1.13  2002/03/31 03:31:24  jbravo
// Compiler warning cleanups
//
// Revision 1.12  2002/03/23 05:17:43  jbravo
// Major cleanup of game -> cgame communication with LCA vars.
//
// Revision 1.11  2002/03/20 22:58:27  blaze
// changed dlight to light_d
//
// Revision 1.10  2002/03/10 21:42:44  blaze
// allow RQ3_weapon_name to map to weapon_name to make radiant work better
//
// Revision 1.9  2002/01/24 14:20:53  jbravo
// Adding func_explosive and a few new surfaceparms
//
// Revision 1.8  2002/01/11 20:20:58  jbravo
// Adding TP to main branch
//
// Revision 1.7  2002/01/11 19:48:30  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.6  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//

#include "g_local.h"

qboolean G_SpawnString(const char *key, const char *defaultString, char **out)
{
	int i;

	if (!level.spawning) {
		*out = (char *) defaultString;
//              G_Error( "G_SpawnString() called while not spawning" );
	}

	for (i = 0; i < level.numSpawnVars; i++) {
		if (!Q_stricmp(key, level.spawnVars[i][0])) {
			*out = level.spawnVars[i][1];
			return qtrue;
		}
	}

	*out = (char *) defaultString;
	return qfalse;
}

qboolean G_SpawnFloat(const char *key, const char *defaultString, float *out)
{
	char *s;
	qboolean present;

	present = G_SpawnString(key, defaultString, &s);
	*out = atof(s);
	return present;
}

qboolean G_SpawnInt(const char *key, const char *defaultString, int *out)
{
	char *s;
	qboolean present;

	present = G_SpawnString(key, defaultString, &s);
	*out = atoi(s);
	return present;
}

qboolean G_SpawnVector(const char *key, const char *defaultString, float *out)
{
	char *s;
	qboolean present;

	present = G_SpawnString(key, defaultString, &s);
	sscanf(s, "%f %f %f", &out[0], &out[1], &out[2]);
	return present;
}

//
// fields are needed for spawning from the entity string
//
typedef enum {
	F_INT,
	F_FLOAT,
	F_LSTRING,		// string on disk, pointer in memory, TAG_LEVEL
	F_GSTRING,		// string on disk, pointer in memory, TAG_GAME
	F_VECTOR,
	F_ANGLEHACK,
	F_ENTITY,		// index on disk, pointer in memory
	F_ITEM,			// index on disk, pointer in memory
	F_CLIENT,		// index on disk, pointer in memory
	F_IGNORE
} fieldtype_t;

typedef struct {
	char *name;
	int ofs;
	fieldtype_t type;
//	int flags;
} field_t;

field_t fields[] = {
	{"classname", FOFS(classname), F_LSTRING},
	{"origin", FOFS(s.origin), F_VECTOR},
	{"model", FOFS(model), F_LSTRING},
	{"model2", FOFS(model2), F_LSTRING},
	{"spawnflags", FOFS(spawnflags), F_INT},
	{"speed", FOFS(speed), F_FLOAT},
	{"target", FOFS(target), F_LSTRING},
	{"targetname", FOFS(targetname), F_LSTRING},
	{"message", FOFS(message), F_LSTRING},
	{"team", FOFS(team), F_LSTRING},
	{"wait", FOFS(wait), F_FLOAT},
	{"random", FOFS(random), F_FLOAT},
	{"count", FOFS(count), F_INT},
	{"health", FOFS(health), F_INT},
	{"light", 0, F_IGNORE},
	{"dmg", FOFS(damage), F_INT},
	{"angles", FOFS(s.angles), F_VECTOR},
	//Makro - only used by the sky portal code
	{"portalspeed", FOFS(movedir), F_VECTOR},
	{"angle", FOFS(s.angles), F_ANGLEHACK},
	{"targetShaderName", FOFS(targetShaderName), F_LSTRING},
	{"targetShaderNewName", FOFS(targetShaderNewName), F_LSTRING},
	{"distance", FOFS(distance), F_FLOAT},	// VALKYRIE: for rotating doors
	{"targetinactive", FOFS(targetInactive), F_LSTRING},	// Makro - target to be fired when inactive
	{"pathtarget", FOFS(pathtarget), F_LSTRING},	// Makro - for func_trains
	{"inactive", FOFS(inactive), F_INT},	// Makro - for inactive objects
	{"activatename", FOFS(activatename), F_LSTRING},
	{"alias", FOFS(alias), F_LSTRING},		//Makro - entity id strings
	{"moveparent", FOFS(moveParent), F_LSTRING},		//Makro - entity id strings
	{"attachto", FOFS(moveParent), F_LSTRING},			//
	{"noreset", FOFS(noreset), F_INT},	//Makro - for entities that shouldn't respawn in TP
	{NULL}
};

typedef struct {
	char *name;
	void (*spawn) (gentity_t * ent);
} spawn_t;

void SP_info_player_start(gentity_t * ent);
void SP_info_player_deathmatch(gentity_t * ent);
void SP_info_player_intermission(gentity_t * ent);
void SP_info_firstplace(gentity_t * ent);
void SP_info_secondplace(gentity_t * ent);
void SP_info_thirdplace(gentity_t * ent);
void SP_info_podium(gentity_t * ent);

void SP_func_plat(gentity_t * ent);
void SP_func_static(gentity_t * ent);
void SP_func_rotating(gentity_t * ent);
void SP_func_bobbing(gentity_t * ent);
void SP_func_pendulum(gentity_t * ent);
void SP_func_button(gentity_t * ent);
void SP_func_door(gentity_t * ent);
void SP_func_train(gentity_t * ent);
void SP_func_timer(gentity_t * self);
void SP_func_breakable(gentity_t * ent);	//Blaze: Breakable glass
void SP_func_pressure(gentity_t * ent);	//NiceAss: pressure entity

void SP_trigger_always(gentity_t * ent);
void SP_trigger_multiple(gentity_t * ent);
void SP_trigger_push(gentity_t * ent);
void SP_trigger_teleport(gentity_t * ent);
void SP_trigger_hurt(gentity_t * ent);

void SP_target_remove_powerups(gentity_t * ent);
void SP_target_give(gentity_t * ent);
void SP_target_delay(gentity_t * ent);
void SP_target_speaker(gentity_t * ent);
void SP_target_print(gentity_t * ent);
void SP_target_laser(gentity_t * self);
void SP_target_character(gentity_t * ent);
void SP_target_score(gentity_t * ent);
void SP_target_teleporter(gentity_t * ent);
void SP_target_relay(gentity_t * ent);
void SP_target_kill(gentity_t * ent);
//Makro - added
void SP_target_activate(gentity_t * ent);
void SP_target_position(gentity_t * ent);
void SP_target_location(gentity_t * ent);
void SP_target_push(gentity_t * ent);

void SP_light(gentity_t * self);
void SP_dlight(gentity_t * self);	// Elder: dlight entity
void SP_misc_lens_flare(gentity_t *ent);	//Makro - lens flare
void SP_func_shadow(gentity_t *ent);	//Makro - fake shadow
void SP_misc_corona(gentity_t *ent);	//Makro - fake shadow
void SP_info_null(gentity_t * self);
void SP_info_notnull(gentity_t * self);
void SP_info_camp(gentity_t * self);
void SP_path_corner(gentity_t * self);

void SP_misc_teleporter_dest(gentity_t * self);
void SP_misc_model(gentity_t * ent);
void SP_misc_portal_camera(gentity_t * ent);
void SP_misc_portal_surface(gentity_t * ent);
//Makro - sky portals
void SP_misc_sky_portal(gentity_t * ent);

//Blaze: These functions are nolonger here
//void SP_shooter_rocket( gentity_t *ent );
//void SP_shooter_plasma( gentity_t *ent );
//void SP_shooter_grenade( gentity_t *ent );

void SP_team_CTF_redplayer(gentity_t * ent);
void SP_team_CTF_blueplayer(gentity_t * ent);

void SP_team_CTF_redspawn(gentity_t * ent);
void SP_team_CTF_bluespawn(gentity_t * ent);

void SP_func_door_rotating(gentity_t * ent);	// VALKYRIE: for rotating doors

// JBravo: SP_item_botroam doesnt really exsist.
// Makro - still, bots are supposed to use these
void SP_item_botroam(gentity_t * ent);

//Blaze: merged func_explosive into func_breakable

// JBravo: adding explosive
//void SP_func_explosive (gentity_t *self);

spawn_t spawns[] = {
	// info entities don't do anything at all, but provide positional
	// information for things controlled by other processes
	{"info_player_start", SP_info_player_start},
	{"info_player_deathmatch", SP_info_player_deathmatch},
	{"info_player_intermission", SP_info_player_intermission},
	{"info_null", SP_info_null},
	{"info_notnull", SP_info_notnull},	// use target_position instead
	{"info_camp", SP_info_camp},

	{"func_plat", SP_func_plat},
	{"func_button", SP_func_button},
	{"func_door", SP_func_door},
	{"func_static", SP_func_static},
	{"func_rotating", SP_func_rotating},
	{"func_bobbing", SP_func_bobbing},
	{"func_pendulum", SP_func_pendulum},
	{"func_train", SP_func_train},
	{"func_group", SP_info_null},
	{"func_timer", SP_func_timer},	// rename trigger_timer?
	{"func_breakable", SP_func_breakable},	// Blaze: Breakable glass
	{"func_pressure", SP_func_pressure},	// NiceAss: pressure entity

	// Triggers are brush objects that cause an effect when contacted
	// by a living player, usually involving firing targets.
	// While almost everything could be done with
	// a single trigger class and different targets, triggered effects
	// could not be client side predicted (push and teleport).
	{"trigger_always", SP_trigger_always},
	{"trigger_multiple", SP_trigger_multiple},
	{"trigger_push", SP_trigger_push},
	{"trigger_teleport", SP_trigger_teleport},
	{"trigger_hurt", SP_trigger_hurt},

	// targets perform no action by themselves, but must be triggered
	// by another entity
	{"target_give", SP_target_give},
	{"target_remove_powerups", SP_target_remove_powerups},
	{"target_delay", SP_target_delay},
	{"target_speaker", SP_target_speaker},
	{"target_print", SP_target_print},
	{"target_laser", SP_target_laser},
	{"target_score", SP_target_score},
	{"target_teleporter", SP_target_teleporter},
	{"target_relay", SP_target_relay},
	{"target_kill", SP_target_kill},
	//Makro - added
	{"target_activate", SP_target_activate},
	{"target_position", SP_target_position},
	{"target_location", SP_target_location},
	{"target_push", SP_target_push},

	{"light", SP_light},
	{"func_dlite", SP_dlight},	// Elder: dlight entity
	{"light_d", SP_dlight},	//Makro - for compatibility with older maps
	{"func_shadow", SP_func_shadow},	//Makro - fake shadow
	{"misc_corona",	SP_misc_corona},	//Makro - coronas
	{"misc_lens_flare", SP_misc_lens_flare}, //Makro - lens flare
	{"path_corner", SP_path_corner},

	{"misc_teleporter_dest", SP_misc_teleporter_dest},
	{"misc_model", SP_misc_model},
	{"misc_portal_surface", SP_misc_portal_surface},
	{"misc_portal_camera", SP_misc_portal_camera},
	//Makro - sky portal !
	{"misc_sky_portal", SP_misc_sky_portal},
//Blaze: This removes rocket traps I think
//      {"shooter_rocket", SP_shooter_rocket},
//      {"shooter_grenade", SP_shooter_grenade},
//      {"shooter_plasma", SP_shooter_plasma},

	{"team_CTF_redplayer", SP_team_CTF_redplayer},
	{"team_CTF_blueplayer", SP_team_CTF_blueplayer},

	{"team_CTF_redspawn", SP_team_CTF_redspawn},
	{"team_CTF_bluespawn", SP_team_CTF_bluespawn},

	{"func_door_rotating", SP_func_door_rotating},	// VALKYRIE: for rotating doors

//Blaze: Merged func_explosive into func_breakable
//      {"func_explosive", SP_func_explosive},  // JBravo: for explosive.
	{"item_botroam", SP_item_botroam},

	{NULL, 0}
};

// JBravo: Compiler warning shutup
void SP_item_botroam(gentity_t * ent)
{
	return;
}

/*
===============
G_CallSpawn

Finds the spawn function for the entity and calls it,
returning qfalse if not found
===============
*/
qboolean G_CallSpawn(gentity_t * ent)
{
	spawn_t *s;
	gitem_t *item;

	if (!ent->classname) {
		G_Printf("G_CallSpawn: NULL classname\n");
		return qfalse;
	}
	
	//Blaze: allow for Reaction specific spawns to be used
	//Elder: map Q3DM weapons -> RQ3 weapons
	if (!strcmp(ent->classname, "weapon_gauntlet"))
		ent->classname = "weapon_knife";
	else if (!strcmp(ent->classname, "weapon_machinegun"))
		ent->classname = "weapon_pistol";
	else if (!strcmp(ent->classname, "weapon_shotgun"))
		ent->classname = "weapon_m3";
	else if (!strcmp(ent->classname, "weapon_plasmagun"))
		ent->classname = "weapon_mp5";
	else if (!strcmp(ent->classname, "weapon_rocketlauncher"))
		ent->classname = "weapon_handcannon";
	else if (!strcmp(ent->classname, "weapon_railgun"))
		ent->classname = "weapon_ssg3000";
	else if (!strcmp(ent->classname, "weapon_bfg"))
		ent->classname = "weapon_m4";
	else if (!strcmp(ent->classname, "ammo_grenades"))
		ent->classname = "weapon_grenade";
	//Makro - this was missing
	else if (!strcmp(ent->classname, "weapon_grenadelauncher"))
		ent->classname = "weapon_pistol";

	//Elder: map Q3DM ammo -> RQ3 ammo
	if (!strcmp(ent->classname, "ammo_bullets"))
		ent->classname = "ammo_mk23";
	else if (!strcmp(ent->classname, "ammo_slugs"))
		ent->classname = "ammo_ssg3000";
	else if (!strcmp(ent->classname, "ammo_cells"))
		ent->classname = "ammo_mp5";
	else if (!strcmp(ent->classname, "ammo_bfg"))
		ent->classname = "ammo_m4";
	else if (!strcmp(ent->classname, "ammo_rockets"))
		ent->classname = "ammo_shells";

	//Blaze: let us support RQ3_weapon name so radiant works nicer
	if (!strcmp(ent->classname, "RQ3weapon_knife"))
		ent->classname = "weapon_knife";
	else if (!strcmp(ent->classname, "RQ3weapon_pistol"))
		ent->classname = "weapon_pistol";
	else if (!strcmp(ent->classname, "RQ3weapon_m3"))
		ent->classname = "weapon_m3";
	else if (!strcmp(ent->classname, "RQ3weapon_mp5"))
		ent->classname = "weapon_mp5";
	else if (!strcmp(ent->classname, "RQ3weapon_handcannon"))
		ent->classname = "weapon_handcannon";
	else if (!strcmp(ent->classname, "RQ3weapon_ssg3000"))
		ent->classname = "weapon_ssg3000";
	else if (!strcmp(ent->classname, "RQ3weapon_m4"))
		ent->classname = "weapon_m4";
	else if (!strcmp(ent->classname, "RQ3weapon_grenade"))
		ent->classname = "weapon_grenade";
	// JBravo: Briefcases
	else if (!strcmp(ent->classname, "RQ3case_black"))
		ent->classname = "team_CTF_blueflag";
	else if (!strcmp(ent->classname, "RQ3case_silver"))
		ent->classname = "team_CTF_redflag";
	//Elder: map Q3DM ammo -> RQ3 ammo
	if (!strcmp(ent->classname, "RQ3ammo_mk23"))
		ent->classname = "ammo_mk23";
	else if (!strcmp(ent->classname, "RQ3ammo_ssg3000"))
		ent->classname = "ammo_ssg3000";
	else if (!strcmp(ent->classname, "RQ3ammo_mp5"))
		ent->classname = "ammo_mp5";
	else if (!strcmp(ent->classname, "RQ3ammo_m4"))
		ent->classname = "ammo_m4";
	else if (!strcmp(ent->classname, "RQ3ammo_shells"))
		ent->classname = "ammo_shells";

	/*
	   //Elder: old stuff
	   if (!strcmp(ent->classname,"weapon_gauntlet")) ent->classname = "weapon_knife";
	   else if (!strcmp(ent->classname,"weapon_railgun")) ent->classname = "weapon_ssg3000";
	   else if (!strcmp(ent->classname,"weapon_shotgun")) ent->classname = "weapon_m3";
	   else if (!strcmp(ent->classname,"weapon_machinegun")) ent->classname = "weapon_mp5";
	   else if (!strcmp(ent->classname,"weapon_rocketlauncher")) ent->classname = "weapon_handcannon";
	   else if (!strcmp(ent->classname,"weapon_bfg")) ent->classname = "weapon_m4";
	   else if (!strcmp(ent->classname,"weapon_grenadelauncher")) ent->classname = "weapon_pistol";
	   else if (!strcmp(ent->classname,"ammo_grenades")) ent->classname = "weapon_grenade";
	 */
	// check item spawn functions

// JBravo: No weapons and items on the maps in teamplay
	/*
	   if (g_gametype.integer != GT_TEAMPLAY) {
	   for ( item=bg_itemlist+1 ; item->classname ; item++ ) {
	   if ( !strcmp(item->classname, ent->classname) ) {
	   G_SpawnItem( ent, item );
	   return qtrue;
	   }
	   }
	   } */
	//Makro - new code

	for (item = bg_itemlist + 1; item->classname; item++) {
		if (!strcmp(item->classname, ent->classname)) {
			//if it's a flag
			if (item->giType == IT_TEAM && (item->giTag == PW_REDFLAG || item->giTag == PW_BLUEFLAG)) {
				//only spawn it in CTF
				if (g_gametype.integer == GT_CTF) {
					G_SpawnItem(ent, item);
				}
				return qtrue;
			} else {
				// JBravo: no spawning in CTF
				if (g_gametype.integer != GT_CTF) {
					G_SpawnItem(ent, item);
					G_BotOnlyItem(ent);
				}
				return qtrue;
			}
		}
	}

	// check normal spawn functions
	for (s = spawns; s->name; s++) {
		if (!strcmp(s->name, ent->classname)) {
			// found it
			s->spawn(ent);
			return qtrue;
		}
	}
// JBravo: getting rid of warnings when the game starts up.
// JBravo: FIXME! This is just supressing the message, not the problem.
	if (g_gametype.integer != GT_TEAMPLAY)
		G_Printf("%s doesn't have a spawn function\n", ent->classname);
	return qfalse;
}

/*
=============
G_NewString

Builds a copy of the string, translating \n to real linefeeds
so message texts can be multi-line
=============
*/
char *G_NewString(const char *string)
{
	char *newb, *new_p;
	int i, l;

	l = strlen(string) + 1;

	newb = G_Alloc(l);

	new_p = newb;

	// turn \n into a real linefeed
	for (i = 0; i < l; i++) {
		if (string[i] == '\\' && i < l - 1) {
			i++;
			if (string[i] == 'n') {
				*new_p++ = '\n';
			} else {
				*new_p++ = '\\';
			}
		} else {
			*new_p++ = string[i];
		}
	}

	return newb;
}

/*
===============
G_ParseField

Takes a key/value pair and sets the binary values
in a gentity
===============
*/
void G_ParseField(const char *key, const char *value, gentity_t * ent)
{
	field_t *f;
	byte *b;
	float v;
	vec3_t vec;

	for (f = fields; f->name; f++) {
		if (!Q_stricmp(f->name, key)) {
			// found it
			b = (byte *) ent;

			switch (f->type) {
			case F_LSTRING:
				*(char **) (b + f->ofs) = G_NewString(value);
				break;
			case F_VECTOR:
				sscanf(value, "%f %f %f", &vec[0], &vec[1], &vec[2]);
				((float *) (b + f->ofs))[0] = vec[0];
				((float *) (b + f->ofs))[1] = vec[1];
				((float *) (b + f->ofs))[2] = vec[2];
				break;
			case F_INT:
				*(int *) (b + f->ofs) = atoi(value);
				break;
			case F_FLOAT:
				*(float *) (b + f->ofs) = atof(value);
				break;
			case F_ANGLEHACK:
				v = atof(value);
				((float *) (b + f->ofs))[0] = 0;
				((float *) (b + f->ofs))[1] = v;
				((float *) (b + f->ofs))[2] = 0;
				break;
			default:
			case F_IGNORE:
				break;
			}
			return;
		}
	}
}

/*
===================
G_SpawnGEntityFromSpawnVars

Spawn an entity and fill in all of the level fields from
level.spawnVars[], then call the class specfic spawn function
===================
*/
void G_SpawnGEntityFromSpawnVars(void)
{
	int i;
	gentity_t *ent;
	char *s, *value, *gametypeName;

// JBravo: added teamplay
	static char *gametypeNames[] =
	    { "ffa", "tournament", "single", "team", "teamplay", "ctf", "oneflag", "obelisk", "harvester",
		"teamtournament"
	};

	// get the next free entity
	ent = G_Spawn();

	for (i = 0; i < level.numSpawnVars; i++) {
		G_ParseField(level.spawnVars[i][0], level.spawnVars[i][1], ent);
	}

	// check for "notsingle" flag
	if (g_gametype.integer == GT_SINGLE_PLAYER) {
		G_SpawnInt("notsingle", "0", &i);
		if (i) {
			G_FreeEntity(ent, __LINE__, __FILE__);
			return;
		}
	}
	//Makro - check for "notgametype" key
	if (G_SpawnInt("notgametype", "0", &i)) {
		if ((i & (1 << g_gametype.integer)) != 0) {
			G_FreeEntity(ent, __LINE__, __FILE__);
			return;
		}
	// check for "notteam" flag (GT_FFA, GT_TOURNAMENT, GT_SINGLE_PLAYER)
	} else if (g_gametype.integer >= GT_TEAM) {
		G_SpawnInt("notteam", "0", &i);
		if (i) {
			G_FreeEntity(ent, __LINE__, __FILE__);
			return;
		}
	} else {
		G_SpawnInt("notfree", "0", &i);
		if (i) {
			G_FreeEntity(ent, __LINE__, __FILE__);
			return;
		}
	}

	G_SpawnInt("notq3a", "0", &i);
	if (i) {
		G_FreeEntity(ent, __LINE__, __FILE__);
		return;
	}

	if (G_SpawnString("gametype", NULL, &value)) {
		if (g_gametype.integer >= GT_FFA && g_gametype.integer < GT_MAX_GAME_TYPE) {
			gametypeName = gametypeNames[g_gametype.integer];

			s = strstr(value, gametypeName);
			if (!s) {
				G_FreeEntity(ent, __LINE__, __FILE__);
				return;
			}
		}
	}
	// move editor origin to pos
	VectorCopy(ent->s.origin, ent->s.pos.trBase);
	VectorCopy(ent->s.origin, ent->r.currentOrigin);

	// if we didn't get a classname, don't bother spawning anything
	if (!G_CallSpawn(ent)) {
		G_FreeEntity(ent, __LINE__, __FILE__);
	}

	//Makro - is the entity in a sky portal ?
	if (G_SpawnInt("skyportalent", "0", &i)) {
		if (i) {
			ent->s.eFlags |= EF_HEADLESS;
		}
	}
}

/*
====================
G_AddSpawnVarToken
====================
*/
char *G_AddSpawnVarToken(const char *string)
{
	int l;
	char *dest;

	l = strlen(string);
	if (level.numSpawnVarChars + l + 1 > MAX_SPAWN_VARS_CHARS) {
		G_Error("G_AddSpawnVarToken: MAX_SPAWN_CHARS");
	}

	dest = level.spawnVarChars + level.numSpawnVarChars;
	memcpy(dest, string, l + 1);

	level.numSpawnVarChars += l + 1;

	return dest;
}

/*
====================
G_ParseSpawnVars

Parses a brace bounded set of key / value pairs out of the
level's entity strings into level.spawnVars[]

This does not actually spawn an entity.
====================
*/
qboolean G_ParseSpawnVars(void)
{
	char keyname[MAX_TOKEN_CHARS];
	char com_token[MAX_TOKEN_CHARS];

	level.numSpawnVars = 0;
	level.numSpawnVarChars = 0;

	// parse the opening brace
	if (!trap_GetEntityToken(com_token, sizeof(com_token))) {
		// end of spawn string
		return qfalse;
	}
	if (com_token[0] != '{') {
		G_Error("G_ParseSpawnVars: found %s when expecting {", com_token);
	}
	// go through all the key / value pairs
	while (1) {
		// parse key
		if (!trap_GetEntityToken(keyname, sizeof(keyname))) {
			G_Error("G_ParseSpawnVars: EOF without closing brace");
		}

		if (keyname[0] == '}') {
			break;
		}
		// parse value  
		if (!trap_GetEntityToken(com_token, sizeof(com_token))) {
			G_Error("G_ParseSpawnVars: EOF without closing brace");
		}

		if (com_token[0] == '}') {
			G_Error("G_ParseSpawnVars: closing brace without data");
		}
		if (level.numSpawnVars == MAX_SPAWN_VARS) {
			G_Error("G_ParseSpawnVars: MAX_SPAWN_VARS");
		}
		level.spawnVars[level.numSpawnVars][0] = G_AddSpawnVarToken(keyname);
		level.spawnVars[level.numSpawnVars][1] = G_AddSpawnVarToken(com_token);
		level.numSpawnVars++;
	}

	return qtrue;
}

/*QUAKED worldspawn (0 0 0) ?

Every map should have exactly one worldspawn.
"music"		music wav file
"gravity"	800 is default gravity
"message"	Text to print during connection process
*/
void SP_worldspawn(void)
{
	char *s;

	vec3_t		color;
	//int		nodetail = 0;
	int			i;
	char		info[MAX_INFO_STRING];

	G_SpawnString("classname", "", &s);
	if (Q_stricmp(s, "worldspawn")) {
		G_Error("SP_worldspawn: The first entity isn't 'worldspawn'");
	}
	// make some data visible to connecting client
	trap_SetConfigstring(CS_GAME_VERSION, GAME_VERSION);

	trap_SetConfigstring(CS_LEVEL_START_TIME, va("%i", level.startTime));

	G_SpawnString("music", "", &s);
	trap_SetConfigstring(CS_MUSIC, s);

	G_SpawnString("message", "", &s);
	trap_SetConfigstring(CS_MESSAGE, s);	// map specific message

	/* Makro - no longer
	   //Makro - color for the loading screen text
	   G_SpawnVector( "_text_color", "0.75 0.75 0.75", color );
	   Info_SetValueForKey(info, "r1", va("%f", color[0]));
	   Info_SetValueForKey(info, "g1", va("%f", color[1]));
	   Info_SetValueForKey(info, "b1", va("%f", color[2]));
	   G_SpawnVector( "_text_color2", "1 1 1", color );
	   Info_SetValueForKey(info, "r2", va("%f", color[0]));
	   Info_SetValueForKey(info, "g2", va("%f", color[1]));
	   Info_SetValueForKey(info, "b2", va("%f", color[2]));
	   //skip detail ?
	   G_SpawnInt( "nodetail", "0", &nodetail );
	   Info_SetValueForKey(info, "nodetail", va("%i", nodetail));
	   //save settings
	   trap_SetConfigstring( CS_LOADINGSCREEN, info );
	 */
	
	//Makro - fog hull replacement
	if (G_SpawnVector("_rq3_fog_color", "0 0 0", color)) {
		memset(info, 0, sizeof(info));
		Info_SetValueForKey(info, "r", va("%f", color[0]));
		Info_SetValueForKey(info, "g", va("%f", color[1]));
		Info_SetValueForKey(info, "b", va("%f", color[2]));
		trap_SetConfigstring( CS_FOGHULL, info );
	}

	trap_SetConfigstring(CS_MOTD, g_motd.string);	// message of the day

	G_SpawnString("gravity", "800", &s);
	trap_Cvar_Set("g_gravity", s);

	G_SpawnString("enableDust", "0", &s);
	trap_Cvar_Set("g_enableDust", s);

	G_SpawnString("enableBreath", "0", &s);
	trap_Cvar_Set("g_enableBreath", s);

  	//Makro - read func_breakable types
	if (G_SpawnInt("numbreakabletypes", "0", &i)) {
		int j;
		for (j=0; j<i && j<RQ3_MAX_BREAKABLES; j++) {
			char *type, *force, *lift;
			if (!G_SpawnString(va("b%d_type", j), "", &type))
				continue;
			G_SpawnString(va("b%d_force", j), "7", &force);
			G_SpawnString(va("b%d_lift", j), "5", &lift);
			info[0] = 0;
			Info_SetValueForKey(info, "type", type);
			Info_SetValueForKey(info, "velocity", force);
			Info_SetValueForKey(info, "jump", lift);
			trap_SetConfigstring(CS_BREAKABLES + j, info);
		}
	}
	
	
	// q3f atmospheric stuff:
	G_SpawnString( "atmosphere", "", &s );
  	trap_SetConfigstring( CS_ATMOSEFFECT, s );  	  	  	// Atmospheric effect

	G_SpawnString("enableLaserFog", "1", &s);
	trap_Cvar_Set("g_enableLaserFog", s);


	g_entities[ENTITYNUM_WORLD].s.number = ENTITYNUM_WORLD;
	g_entities[ENTITYNUM_WORLD].classname = "worldspawn";

	// see if we want a warmup time
	trap_SetConfigstring(CS_WARMUP, "");
	if (g_restarted.integer) {
		trap_Cvar_Set("g_restarted", "0");
		level.warmupTime = 0;
	} else if (g_doWarmup.integer) {	// Turn it on
		level.warmupTime = -1;
		trap_SetConfigstring(CS_WARMUP, va("%i", level.warmupTime));
		G_LogPrintf("Warmup:\n");
	}

}

/*
==============
G_SpawnEntitiesFromString

Parses textual entity definitions out of an entstring and spawns gentities.
==============
*/
void G_SpawnEntitiesFromString(void)
{
	// allow calls to G_Spawn*()
	level.spawning = qtrue;
	level.numSpawnVars = 0;

	// the worldspawn is not an actual entity, but it still
	// has a "spawn" function to perform any global setup
	// needed by a level (setting configstrings or cvars, etc)
	if (!G_ParseSpawnVars()) {
		G_Error("SpawnEntities: no entities");
	}
	SP_worldspawn();

	// parse ents
	while (G_ParseSpawnVars()) {
		G_SpawnGEntityFromSpawnVars();
	}

	level.spawning = qfalse;	// any future calls to G_Spawn*() will be errors
}
