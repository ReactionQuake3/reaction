//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.49  2003/02/05 20:21:38  jbravo
// Fixed the model replacement system.  Its no longer an ugly hack.
//
// Revision 1.48  2003/02/01 02:15:31  jbravo
// Replacement models and items
//
// Revision 1.47  2003/01/08 04:46:26  jbravo
// Wrote a new hackish model replacement system
//
// Revision 1.46  2002/10/30 20:04:34  jbravo
// Adding helmet
//
// Revision 1.45  2002/10/26 00:37:18  jbravo
// New multiple item code and added PB support to the UI
//
// Revision 1.44  2002/07/22 06:34:13  niceass
// cleaned up the powerup code
//
// Revision 1.43  2002/07/01 02:18:42  jbravo
// Small fixes to CTB and possible fix for subs and limchasecam
//
// Revision 1.42  2002/06/29 04:15:15  jbravo
// CTF is now CTB.  no weapons while the case is in hand other than pistol or knife
//
// Revision 1.41  2002/06/16 20:06:14  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.40  2002/06/16 17:37:59  jbravo
// Removed the MISSIONPACK ifdefs and missionpack only code.
//
// Revision 1.39  2002/05/29 13:49:25  makro
// Elevators/doors
//
// Revision 1.38  2002/05/12 22:14:13  makro
// Impact sounds
//
// Revision 1.37  2002/05/11 19:18:20  makro
// Sand surfaceparm
//
// Revision 1.36  2002/05/11 14:22:06  makro
// Func_statics now reset at the beginning of each round
//
// Revision 1.35  2002/04/30 11:54:37  makro
// Bots rule ! Also, added clips to give all. Maybe some other things
//
// Revision 1.34  2002/04/23 06:03:39  niceass
// pressure stuff
//
// Revision 1.33  2002/04/20 15:03:47  makro
// More footstep sounds, a few other things
//
// Revision 1.32  2002/04/03 03:13:16  blaze
// NEW BREAKABLE CODE - will break all old breakables(wont appear in maps)
//
// Revision 1.31  2002/03/31 03:31:24  jbravo
// Compiler warning cleanups
//
// Revision 1.30  2002/03/02 12:24:30  jbravo
// Removed some debugging messages
//
// Revision 1.29  2002/02/23 16:55:09  jbravo
// Added debugging to help find what was going with can't find item for weapon
// error that crash the server.
//
// Revision 1.28  2002/01/24 14:20:53  jbravo
// Adding func_explosive and a few new surfaceparms
//
// Revision 1.27  2002/01/14 07:31:33  jbravo
// Added a small workaround for the HoldableItem not found crash during
// mapchanges.
//
// Revision 1.26  2002/01/11 19:48:29  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.25  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
// bg_misc.c -- both games misc functions, all completely stateless

#include "q_shared.h"
#include "bg_public.h"

/*QUAKED item_***** ( 0 0 0 ) (-16 -16 -16) (16 16 16) suspended
DO NOT USE THIS CLASS, IT JUST HOLDS GENERAL INFORMATION.
The suspended flag will allow items to hang in the air, otherwise they are dropped to the next surface.

If an item is the target of another entity, it will not spawn in until fired.

An item fires all of its targets when it is picked up.  If the toucher can't carry it, the targets won't be fired.

"notfree" if set to 1, don't spawn in free for all games
"notteam" if set to 1, don't spawn in team games
"notsingle" if set to 1, don't spawn in single player games
"wait"	override the default wait before respawning.  -1 = never respawn automatically, which can be used with targeted spawning.
"random" random number of plus or minus seconds varied from the respawn time
"count" override quantity or duration on most items.
*/

gitem_t bg_itemlist[] = {
	{
	 NULL,
	 NULL,
	 {NULL,
	  NULL,
	  0, 0}
	 ,
/* icon */ NULL,
/* pickup */ NULL,
	 0,
	 0,
	 0,
/* precache */ "",
/* sounds */ ""
	 }
	,			// leave index 0 alone

	//
	// ARMOR
	//

	//
	// WEAPONS
	//

//Blaze: Reaction weapons
//Knife
	{
	 "weapon_knife",
	 "sound/misc/am_pkup.wav",
	 {"models/weapons2/knife/knife.md3",
	  0, 0, 0}
	 ,
	 "icons/iconw_knife",
	 RQ3_KNIFE_NAME,
	 1,
	 IT_WEAPON,
	 WP_KNIFE,
	 "",
	 ""}
	,

//Pistol
	{
	 "weapon_pistol",
	 "sound/weapons/mk23/mk23slide.wav",
	 {"models/weapons2/mk23/mk23.md3",
	  0, 0, 0}
	 ,
/* icon */ "icons/iconw_mk23",
/* pickup */ RQ3_PISTOL_NAME,
	 12,
	 IT_WEAPON,
	 WP_PISTOL,
/* precache */ "",
/* sounds */ ""
	 }
	,

//M4
	{
	 "weapon_m4",
	 "sound/weapons/m4/m4slide.wav",
	 {"models/weapons2/m4/m4.md3",
	  0, 0, 0}
	 ,
/* icon */ "icons/iconw_m4",
/* pickup */ RQ3_M4_NAME,
	 24,
	 IT_WEAPON,
	 WP_M4,
/* precache */ "",
/* sounds */ ""
	 }
	,

//SSG3000
	{
	 "weapon_ssg3000",
	 "sound/weapons/ssg3000/ssgin.wav",
	 {"models/weapons2/ssg3000/ssg3000.md3",
	  0, 0, 0}
	 ,
/* icon */ "icons/iconw_ssg",
/* pickup */ RQ3_SSG3000_NAME,
	 6,
	 IT_WEAPON,
	 WP_SSG3000,
/* precache */ "",
/* sounds */ ""
	 }
	,

//MP5
	{
	 "weapon_mp5",
	 "sound/weapons/mp5/mp5slide.wav",
	 {"models/weapons2/mp5/mp5.md3",
	  0, 0, 0}
	 ,
/* icon */ "icons/iconw_mp5",
/* pickup */ RQ3_MP5_NAME,
	 30,
	 IT_WEAPON,
	 WP_MP5,
/* precache */ "",
/* sounds */ ""
	 }
	,

//Handcannon
	{
	 "weapon_handcannon",
	 "sound/weapons/handcannon/hcopen.wav",
	 {"models/weapons2/handcannon/handcannon.md3",
	  0, 0, 0}
	 ,
/* icon */ "icons/iconw_handcannon",
/* pickup */ RQ3_HANDCANNON_NAME,
	 2,
	 IT_WEAPON,
	 WP_HANDCANNON,
/* precache */ "",
/* sounds */ ""
	 }
	,

//Shotgun
	{
	 "weapon_m3",
	 "sound/weapons/m3/m3in.wav",
	 {"models/weapons2/m3/m3.md3",
	  0, 0, 0}
	 ,
/* icon */ "icons/iconw_m3",
/* pickup */ RQ3_M3_NAME,
	 7,
	 IT_WEAPON,
	 WP_M3,
/* precache */ "",
/* sounds */ ""
	 }
	,

//Akimbo Placeholder
	{
	 "weapon_akimbo",
	 "sound/weapons/mk23/mk23slide.wav",
	 {"models/weapons2/akimbo/akimbo.md3",
	  0, 0, 0}
	 ,
/* icon */ "icons/iconw_akimbo",
/* pickup */ RQ3_AKIMBO_NAME,
	 24,
	 IT_WEAPON,
	 WP_AKIMBO,
/* precache */ "",
/* sounds */ ""
	 }
	,

//Grenade
	{
	 "weapon_grenade",
	 //"sound/grenade/tink2.wav",
	 "sound/misc/am_pkup.wav",
	 {"models/weapons2/grenade/grenade.md3",
	  0, 0, 0}
	 ,
/* icon */ "icons/iconw_grenade",
/* pickup */ RQ3_GRENADE_NAME,
	 1,
	 IT_WEAPON,
	 WP_GRENADE,
/* precache */ "",
/* sounds */ ""
	 }
	,

//Blaze: 3rd Person Models
//Elder: 07/06/2001: Now known as 1st-person models!
//Knife

	{
	 "knife_1st",
	 NULL,
	 {"models/weapons2/knife/knife_1st.md3", 0, 0, 0}
	 ,
	 "icons/iconw_knife",
	 RQ3_KNIFE_NAME,
	 1,
	 IT_WEAPON,
	 WP_KNIFE,
	 "",
	 ""}
	,

//Pistol
	{
	 "pistol_1st",
	 NULL,
	 {"models/weapons2/mk23/mk23_1st.md3",
	  0, 0, 0}
	 ,
	 "icons/iconw_mk23",
	 RQ3_PISTOL_NAME,
	 12,
	 IT_WEAPON,
	 WP_PISTOL,
	 "",
	 ""}
	,

//M4
	{
	 "m4_1st",
	 NULL,
	 {"models/weapons2/m4/m4_1st.md3",
	  0, 0, 0}
	 ,
	 "icons/iconw_m4",
	 RQ3_M4_NAME,
	 24,
	 IT_WEAPON,
	 WP_M4,
	 "",
	 ""}
	,

//SSG3000
	{
	 "ssg3000_1st",
	 NULL,
	 {"models/weapons2/ssg3000/ssg3000_1st.md3",
	  0, 0, 0}
	 ,
	 "icons/iconw_ssg",
	 RQ3_SSG3000_NAME,
	 6,
	 IT_WEAPON,
	 WP_SSG3000,
	 "",
	 ""}
	,

//MP5
	{
	 "mp5_1st",
	 NULL,
	 {"models/weapons2/mp5/mp5_1st.md3",
	  0, 0, 0}
	 ,
	 "icons/iconw_mp5",
	 RQ3_MP5_NAME,
	 30,
	 IT_WEAPON,
	 WP_MP5,
	 "",
	 ""}
	,

//Handcannon
	{
	 "handcannon_1st",
	 NULL,
	 {"models/weapons2/handcannon/handcannon_1st.md3",
	  0, 0, 0}
	 ,
	 "icons/iconw_sawedoff",
	 RQ3_HANDCANNON_NAME,
	 2,
	 IT_WEAPON,
	 WP_HANDCANNON,
	 "",
	 ""}
	,

//Shotgun
	{
	 "m3_1st",
	 NULL,
	 {"models/weapons2/m3/m3_1st.md3",
	  0, 0, 0}
	 ,
	 "icons/iconw_m3",
	 RQ3_M3_NAME,
	 7,
	 IT_WEAPON,
	 WP_M3,
	 "",
	 ""}
	,

//Akimbo Placeholder
	{
	 "akimbo_1st",
	 NULL,
	 {"models/weapons2/akimbo/akimbo_1st.md3",
	  0, 0, 0}
	 ,
	 "icons/iconw_akimbo",
	 RQ3_AKIMBO_NAME,
	 24,
	 IT_WEAPON,
	 WP_AKIMBO,
	 "",
	 ""}
	,

//Grenade
	{
	 "grenade_1st",
	 NULL,
	 {"models/weapons2/grenade/grenade_1st.md3",
	  0, 0, 0}
	 ,
	 "icons/iconw_gren",
	 RQ3_GRENADE_NAME,
	 1,
	 IT_WEAPON,
	 WP_GRENADE,
	 "",
	 ""}
	,

	//
	// AMMO ITEMS
	//
/*QUAKED ammo_mk23 (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
	 "ammo_mk23",
	 "sound/misc/am_pkup.wav",
	 {"models/ammo/mk23.md3",
	  0, 0, 0}
	 ,
/* icon */ "icons/icona_mk23clip",
/* pickup */ "MK23 Clip",
	 1,
	 IT_AMMO,
	 //Blaze: Changed from WP_MACHINEGUN to WP_PISTOL
	 WP_PISTOL,
/* precache */ "",
/* sounds */ ""
	 }
	,

/*QUAKED ammo_shells (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
	 "ammo_shells",
	 "sound/misc/am_pkup.wav",
	 {"models/ammo/m3.md3",
	  0, 0, 0}
	 ,
/* icon */ "icons/icona_shells",
/* pickup */ "Shotgun Shells",
	 7,
	 IT_AMMO,
	 //Blaze: Changed from WP_ROCKET_LAUNCHER to WP_SHOTGUN
	 WP_M3,
/* precache */ "",
/* sounds */ ""
	 }
	,

/*QUAKED ammo_ssg3000 (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
	 "ammo_ssg3000",
	 "sound/misc/am_pkup.wav",
	 {"models/ammo/ssg3000.md3",
	  0, 0, 0}
	 ,
/* icon */ "icons/icona_ssgammo",
/* pickup */ "AP Sniper Ammo",
	 10,
	 IT_AMMO,
	 //Blaze: Changed from WP_RAILGUN to WP_GRENADE
	 WP_SSG3000,
/* precache */ "",
/* sounds */ ""
	 }
	,

/*QUAKED ammo_mp5 (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
	 "ammo_mp5",
	 "sound/misc/am_pkup.wav",
	 {"models/ammo/mp5.md3",
	  0, 0, 0}
	 ,
/* icon */ "icons/icona_mp5clip",
/* pickup */ "MP5 Clip",
	 1,
	 IT_AMMO,
	 //Blaze: Changed from WP_PLASMAGUN to WP_MP5
	 WP_MP5,
/* precache */ "",
/* sounds */ ""
	 }
	,

/*QUAKED ammo_lightning (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
//Blaze: HC and M3 use same ammo
//      {
//              "ammo_lightning",
//              "sound/misc/am_pkup.wav",
//      { "models/powerups/ammo/lightningam.md3",
//          0, 0, 0},
/* icon *///            "icons/icona_lightning",
/* pickup *///  "Shotgun Shells",
	//7,
	//IT_AMMO,
	//Blaze: Changed from WP_LIGHTNING to WP_HANDCANNON
	//WP_HANDCANNON,
/* precache */// "",
/* sounds *///""
//      },

/*QUAKED ammo_m4 (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
	 "ammo_m4",
	 "sound/misc/am_pkup.wav",
	 {"models/ammo/m4.md3",
	  0, 0, 0}
	 ,
/* icon */ "icons/icona_m4clip",
/* pickup */ "M4 Clip",
	 1,
	 IT_AMMO,
	 //Blaze: changed from WP_SHOTGUN to WP_M4
	 WP_M4,
/* precache */ "",
/* sounds */ ""
	 }
	,

/*QUAKED team_CTF_redflag (1 0 0) (-16 -16 -16) (16 16 16)
Only in CTF games
*/
	{
	 "team_CTF_redflag",
	 NULL,
//	 {"models/flags/r_flag.md3",
	 {"models/cases/s_case.md3",
	  0, 0, 0}
	 ,
/* icon */ "icons/iconc_silver",
/* pickup */ "Silver Case",
	 0,
	 IT_TEAM,
	 PW_REDFLAG,
/* precache */ "",
/* sounds */ ""
	 }
	,

/*QUAKED team_CTF_blueflag (0 0 1) (-16 -16 -16) (16 16 16)
Only in CTF games
*/
	{
	 "team_CTF_blueflag",
	 NULL,
//	 {"models/flags/b_flag.md3",
	 {"models/cases/b_case.md3",
	  0, 0, 0}
	 ,
/* icon */ "icons/iconc_black",
/* pickup */ "Black Case",
	 0,
	 IT_TEAM,
	 PW_BLUEFLAG,
/* precache */ "",
/* sounds */ ""
	 }
	,

	//Elder: RQ3 Items
	{
	 "item_kevlar",
	 "sound/items/kevlar.wav",
	 {"models/items/kevlar.md3",
	  0, 0, 0}
	 ,
	 "icons/iconi_kevlar",
	 RQ3_KEVLAR_NAME,
	 0,
	 IT_HOLDABLE,
	 HI_KEVLAR,
	 "",
	 ""}
	,

	{
	 "item_silencer",
	 "sound/items/silencer.wav",
	 {"models/items/silencer.md3",
	  0, 0, 0}
	 ,
	 "icons/iconi_silencer",
	 RQ3_SILENCER_NAME,
	 0,
	 IT_HOLDABLE,
	 HI_SILENCER,
	 "",
	 ""}
	,

	{
	 "item_laser",
	 "sound/items/laser.wav",
	 {"models/items/laser.md3",
	  0, 0, 0}
	 ,
	 "icons/iconi_laser",
	 RQ3_LASER_NAME,
	 0,
	 IT_HOLDABLE,
	 HI_LASER,
	 "",
	 ""}
	,

	{
	 "item_bandolier",
	 "sound/items/bandolier.wav",
	 {"models/items/bandolier.md3",
	  0, 0, 0}
	 ,
	 "icons/iconi_bandolier",
	 RQ3_BANDOLIER_NAME,
	 0,
	 IT_HOLDABLE,
	 HI_BANDOLIER,
	 "",
	 ""}
	,

	{
	 "item_slippers",
	 "sound/items/slippers.wav",
	 {"models/items/slippers.md3",
	  0, 0, 0}
	 ,
	 "icons/iconi_slippers",
	 RQ3_SLIPPERS_NAME,
	 0,
	 IT_HOLDABLE,
	 HI_SLIPPERS,
	 "",
	 ""}
	,
// JBravo: adding Helmet
	{
	 "item_helmet",
	 "sound/items/slippers.wav",
	 {"models/items/helmet.md3",
	  0, 0, 0}
	 ,
	 "icons/iconi_helmet",
	 RQ3_HELMET_NAME,
	 0,
	 IT_HOLDABLE,
	 HI_HELMET,
	 "",
	 ""}
	,
	// end of list marker
	{NULL}
};

int bg_numItems = sizeof(bg_itemlist) / sizeof(bg_itemlist[0]) - 1;

/*
==============
BG_FindItemForPowerup
==============
*/
gitem_t *BG_FindItemForPowerup(powerup_t pw)
{
	int i;

	for (i = 0; i < bg_numItems; i++) {
		if ((bg_itemlist[i].giType == IT_POWERUP ||
		     bg_itemlist[i].giType == IT_TEAM ||
		     bg_itemlist[i].giType == IT_PERSISTANT_POWERUP) && bg_itemlist[i].giTag == pw) {
			return &bg_itemlist[i];
		}
	}

	return NULL;
}

/*
==============
BG_FindItemForHoldable
==============
*/
gitem_t *BG_FindItemForHoldable(holdable_t pw)
{
	int i;

// JBravo: fix for HoldableItem not found error during mapchanges.
// I dont understand why this gets called with pw == 0 during map changes.
	if (pw == 0)
		return NULL;

	for (i = 0; i < bg_numItems; i++) {
		if (bg_itemlist[i].giType == IT_HOLDABLE && bg_itemlist[i].giTag == pw) {
			return &bg_itemlist[i];
		}
	}

	Com_Error(ERR_DROP, "HoldableItem not found");

	return NULL;
}

/*
===============
BG_FindItemForWeapon

===============
*/
gitem_t *BG_FindItemForWeapon(weapon_t weapon)
{
	gitem_t *it;

	for (it = bg_itemlist + 1; it->classname; it++) {
		if (it->giType == IT_WEAPON && it->giTag == weapon) {
			return it;
		}
	}

	Com_Error(ERR_DROP, "Couldn't find item for weapon %i", weapon);
	return NULL;
}

/*
===============
BG_FindItem

===============
*/
gitem_t *BG_FindItem(const char *pickupName)
{
	gitem_t *it;

	for (it = bg_itemlist + 1; it->classname; it++) {
		if (!Q_stricmp(it->pickup_name, pickupName))
			return it;
	}

	return NULL;
}

/*
============
BG_PlayerTouchesItem

Items can be picked up without actually touching their physical bounds to make
grabbing them easier
============
*/
qboolean BG_PlayerTouchesItem(playerState_t * ps, entityState_t * item, int atTime)
{
	vec3_t origin;

	BG_EvaluateTrajectory(&item->pos, atTime, origin);

	// we are ignoring ducked differences here
	if (ps->origin[0] - origin[0] > 44
	    || ps->origin[0] - origin[0] < -50
	    || ps->origin[1] - origin[1] > 36
	    || ps->origin[1] - origin[1] < -36 || ps->origin[2] - origin[2] > 36 || ps->origin[2] - origin[2] < -36) {
		return qfalse;
	}

	return qtrue;
}

/*
==================
 Elder: changed from ClipAmountForWeapon - which was an ambiguous name
 ClipAmountForReload for Cmd_Reload
 Added by Duffman
 Returns the amount of ammo a weapon reloads by
 ==================
*/

int ClipAmountForReload(int w)
{
	//How much each clip holds
	//Elder: this function is very misleading.
	//It returns the amount to add when reloading,
	//Not the actual amount in a weapon clip!!
	//For that, you should check ClipAmountForAmmo below
	//Changed to use constants defined in bg_public.h
	switch (w) {
	case WP_PISTOL:
		return RQ3_PISTOL_RELOAD;
	case WP_KNIFE:
		return RQ3_KNIFE_RELOAD;
	case WP_M4:
		return RQ3_M4_RELOAD;
	case WP_SSG3000:
		return RQ3_SSG3000_RELOAD;
	case WP_MP5:
		return RQ3_MP5_RELOAD;
	case WP_HANDCANNON:
		return RQ3_HANDCANNON_RELOAD;
	case WP_M3:
		return RQ3_M3_RELOAD;
	case WP_AKIMBO:
		return RQ3_AKIMBO_RELOAD;
	case WP_GRENADE:
		return RQ3_GRENADE_RELOAD;
	default:
		return RQ3_PISTOL_RELOAD;
	}
//       return 12; //this wont happen unless you copy-and-paste too much
}

/*
==================
 ClipAmountForAmmo
 Added by Elder
 Returns the amount of ammo a weapon can hold
 ==================
*/

int ClipAmountForAmmo(int w)
{
	//How much each GUN holds!
	//Elder: don't confuse with the reload one
	switch (w) {
	case WP_PISTOL:
		return RQ3_PISTOL_AMMO;
	case WP_KNIFE:
		return RQ3_KNIFE_AMMO;
	case WP_M4:
		return RQ3_M4_AMMO;
	case WP_SSG3000:
		return RQ3_SSG3000_AMMO;
	case WP_MP5:
		return RQ3_MP5_AMMO;
	case WP_HANDCANNON:
		return RQ3_HANDCANNON_AMMO;
	case WP_M3:
		return RQ3_M3_AMMO;
	case WP_AKIMBO:
		return RQ3_AKIMBO_AMMO;
	case WP_GRENADE:
		return RQ3_GRENADE_AMMO;
	default:
		return RQ3_PISTOL_AMMO;
	}
}

/*
================
BG_CanItemBeGrabbed

Returns false if the item should not be picked up.
This needs to be the same for client side prediction and server use.
================
*/

qboolean BG_CanItemBeGrabbed(int gametype, const entityState_t * ent, const playerState_t * ps)
{
	gitem_t *item;

	if (ent->modelindex < 1 || ent->modelindex >= bg_numItems) {
		Com_Error(ERR_DROP, "BG_CanItemBeGrabbed: index out of range");
	}

	item = &bg_itemlist[ent->modelindex];

	switch (item->giType) {
	case IT_WEAPON:
		//Elder: gotta check before we can pick it up
		//if (item->giTag == WP_KNIFE && ps->ammo[WP_KNIFE] >= RQ3_KNIFE_MAXCLIP)
		//return qfalse;
		//else
		//if (item->giTag != WP_KNIFE && ent->pos.trDelta && ent->pos.trDelta[2] != 0)
		//return qfalse;
		//else
		return qtrue;	// weapons are always picked up

	case IT_AMMO:

		//Blaze: pick up all ammo
		//Blaze: make sure you dont go over max amount of clips
		//if ( ps->stats[STAT_CLIPS] >= 2)
		//if ( ps->ammo[ item->giTag ] >= ClipAmountForWeapon(item->giTag )) {
		//{
		//      return qfalse;          // can't hold any more
		//}
		return qtrue;

	case IT_ARMOR:
		if (ps->stats[STAT_ARMOR] >= 200) {	//2 times max healthps->stats[STAT_MAX_HEALTH] * 2 ) {
			return qfalse;
		}
		return qtrue;

	case IT_HEALTH:
		// small and mega healths will go over the max, otherwise
		// don't pick up if already at max
		if (item->quantity == 5 || item->quantity == 100) {
			if (ps->stats[STAT_HEALTH] >= 200) {	//200 is max health x 2 ps->stats[STAT_MAX_HEALTH] * 2 ) {
				return qfalse;
			}
			return qtrue;
		}

		if (ps->stats[STAT_HEALTH] >= 100) {	//100 is the max health ps->stats[STAT_MAX_HEALTH] ) {
			return qfalse;
		}
		return qtrue;

	case IT_POWERUP:
		return qtrue;	// powerups are always picked up

	case IT_TEAM:		// team items, such as flags
		if (gametype == GT_CTF) {
			// ent->modelindex2 is non-zero on items if they are dropped
			// we need to know this because we can pick up our dropped flag (and return it)
			// but we can't pick up our flag at base
			if (ps->persistant[PERS_TEAM] == TEAM_RED) {
				if (item->giTag == PW_BLUEFLAG ||
				    (item->giTag == PW_REDFLAG && ent->modelindex2) ||
				    (item->giTag == PW_REDFLAG && ps->powerups[PW_BLUEFLAG]))
					return qtrue;
			} else if (ps->persistant[PERS_TEAM] == TEAM_BLUE) {
				if (item->giTag == PW_REDFLAG ||
				    (item->giTag == PW_BLUEFLAG && ent->modelindex2) ||
				    (item->giTag == PW_BLUEFLAG && ps->powerups[PW_REDFLAG]))
					return qtrue;
			}
		}

		return qfalse;

	case IT_HOLDABLE:
		// can only hold one item at a time
		// JBravo: I beg to differ
/*		if (ps->stats[STAT_HOLDABLE_ITEM]) {
			return qfalse;
		} */
		return qtrue;

	case IT_BAD:
		Com_Error(ERR_DROP, "BG_CanItemBeGrabbed: IT_BAD");
	default:
#ifndef Q3_VM
#ifndef NDEBUG			// bk0001204
		Com_Printf("BG_CanItemBeGrabbed: unknown enum %d\n", item->giType);
#endif
#endif
		break;
	}

	return qfalse;
}

//======================================================================

/*
================
BG_EvaluateTrajectory

================
*/
void BG_EvaluateTrajectory(const trajectory_t * tr, int atTime, vec3_t result)
{
	float deltaTime;
	float phase;

	switch (tr->trType) {
	case TR_STATIONARY:
	case TR_INTERPOLATE:
		VectorCopy(tr->trBase, result);
		break;
	case TR_LINEAR:
		deltaTime = (atTime - tr->trTime) * 0.001;	// milliseconds to seconds
		VectorMA(tr->trBase, deltaTime, tr->trDelta, result);
		break;
	case TR_SINE:
		deltaTime = (atTime - tr->trTime) / (float) tr->trDuration;
		phase = sin(deltaTime * M_PI * 2);
		VectorMA(tr->trBase, phase, tr->trDelta, result);
		break;
	case TR_LINEAR_STOP:
		if (atTime > tr->trTime + tr->trDuration) {
			atTime = tr->trTime + tr->trDuration;
		}
		deltaTime = (atTime - tr->trTime) * 0.001;	// milliseconds to seconds
		if (deltaTime < 0) {
			deltaTime = 0;
		}
		VectorMA(tr->trBase, deltaTime, tr->trDelta, result);
		break;
	case TR_GRAVITY:
		deltaTime = (atTime - tr->trTime) * 0.001;	// milliseconds to seconds
		VectorMA(tr->trBase, deltaTime, tr->trDelta, result);
		result[2] -= 0.5 * DEFAULT_GRAVITY * deltaTime * deltaTime;	// FIXME: local gravity...
		break;
	default:
		Com_Error(ERR_DROP, "BG_EvaluateTrajectory: unknown trType: %i", tr->trTime);
		break;
	}
}

/*
================
BG_EvaluateTrajectoryDelta

For determining velocity at a given time
================
*/
void BG_EvaluateTrajectoryDelta(const trajectory_t * tr, int atTime, vec3_t result)
{
	float deltaTime;
	float phase;

	switch (tr->trType) {
	case TR_STATIONARY:
	case TR_INTERPOLATE:
		VectorClear(result);
		break;
	case TR_LINEAR:
		VectorCopy(tr->trDelta, result);
		break;
	case TR_SINE:
		deltaTime = (atTime - tr->trTime) / (float) tr->trDuration;
		phase = cos(deltaTime * M_PI * 2);	// derivative of sin = cos
		phase *= 0.5;
		VectorScale(tr->trDelta, phase, result);
		break;
	case TR_LINEAR_STOP:
		if (atTime > tr->trTime + tr->trDuration) {
			VectorClear(result);
			return;
		}
		VectorCopy(tr->trDelta, result);
		break;
	case TR_GRAVITY:
		deltaTime = (atTime - tr->trTime) * 0.001;	// milliseconds to seconds
		VectorCopy(tr->trDelta, result);
		result[2] -= DEFAULT_GRAVITY * deltaTime;	// FIXME: local gravity...
		break;
	default:
		Com_Error(ERR_DROP, "BG_EvaluateTrajectoryDelta: unknown trType: %i", tr->trTime);
		break;
	}
}

char *eventnames[] = {
	"EV_NONE",

	"EV_FOOTSTEP",
	"EV_FOOTSTEP_METAL",
	"EV_FOOTSTEP_GRAVEL",
	"EV_FOOTSTEP_WOOD",
	"EV_FOOTSTEP_CARPET",
	"EV_FOOTSTEP_METAL2",
	"EV_FOOTSTEP_GLASS",
	"EV_FOOTSTEP_GRASS",
	"EV_FOOTSTEP_SNOW",	// JBravo: adding new sounds
	"EV_FOOTSTEP_MUD",
	"EV_FOOTSTEP_WOOD2",
	"EV_FOOTSTEP_HARDMETAL",
	//Makro - new sounds
	"EV_FOOTSTEP_LEAVES",
	"EV_FOOTSTEP_CEMENT",
	"EV_FOOTSTEP_MARBLE",
	"EV_FOOTSTEP_SNOW2",
	"EV_FOOTSTEP_HARDSTEPS",
	"EV_FOOTSTEP_SAND",

	"EV_FOOTSPLASH",
	"EV_FOOTWADE",
	"EV_SWIM",

	"EV_STEP_4",
	"EV_STEP_8",
	"EV_STEP_12",
	"EV_STEP_16",

	"EV_FALL_SHORT",
	"EV_FALL_SHORT_NOSOUND",
	"EV_FALL_MEDIUM",
	"EV_FALL_MEDIUM_NOSOUND",
	"EV_FALL_FAR",
	"EV_FALL_FAR_NOSOUND",

	"EV_JUMP_PAD",		// boing sound at origin", jump sound on player

	"EV_JUMP",
	"EV_WATER_TOUCH",	// foot touches
	"EV_WATER_LEAVE",	// foot leaves
	"EV_WATER_UNDER",	// head touches
	"EV_WATER_CLEAR",	// head leaves

	"EV_ITEM_PICKUP",	// normal item pickups are predictable
	"EV_GLOBAL_ITEM_PICKUP",	// powerup / team sounds are broadcast to everyone

	"EV_NOAMMO",
	"EV_CHANGE_WEAPON",
	"EV_FIRE_WEAPON",
	"EV_RELOAD_WEAPON0",	// Elder: reload weapon sounds
	"EV_RELOAD_WEAPON1",	// Elder: reload weapon sounds
	"EV_RELOAD_WEAPON2",	// Elder: reload weapon sounds

	"EV_USE_ITEM0",
	"EV_USE_ITEM1",
	"EV_USE_ITEM2",
	"EV_USE_ITEM3",
	"EV_USE_ITEM4",
	"EV_USE_ITEM5",
	"EV_USE_ITEM6",
	"EV_USE_ITEM7",
	"EV_USE_ITEM8",
	"EV_USE_ITEM9",
	"EV_USE_ITEM10",
	"EV_USE_ITEM11",
	"EV_USE_ITEM12",
	"EV_USE_ITEM13",
	"EV_USE_ITEM14",
	"EV_USE_ITEM15",

	"EV_ITEM_RESPAWN",
	"EV_ITEM_POP",
	"EV_PLAYER_TELEPORT_IN",
	"EV_PLAYER_TELEPORT_OUT",

	"EV_GRENADE_BOUNCE",	// eventParm will be the soundindex

	"EV_GENERAL_SOUND",
	"EV_GLOBAL_SOUND",	// no attenuation
	"EV_GLOBAL_TEAM_SOUND",
	"EV_RQ3_SOUND",		// Elder: play local sounds - primarily for kick

	"EV_DMREWARD",		// Duffman: To display exponential reward messages.

	"EV_BULLET_HIT_FLESH",
	"EV_BULLET_HIT_WALL",
	"EV_BULLET_HIT_METAL",	// Elder: sparks
	"EV_BULLET_HIT_KEVLAR",	// Elder: sparks
	"EV_BULLET_HIT_GLASS",	// Elder: glass mark
	"EV_BULLET_HIT_WOOD",	// Makro: new sound
	"EV_BULLET_HIT_BRICK",	// Makro: new sound
	"EV_BULLET_HIT_CERAMIC",	// Makro: new sound
	"EV_SSG3000_HIT_FLESH",	// Elder: SSG3000 blood spray
	"EV_JUMPKICK",		// Elder: sound + jumpkick message
	"EV_EJECTBLOOD",	// Elder: when bleeding, every 2s release blood

	"EV_MISSILE_HIT",
	"EV_MISSILE_MISS",
	"EV_MISSILE_MISS_METAL",
	"EV_KNIFE_MISS",	// Elder: knife slash stuff
	"EV_RAILTRAIL",
	"EV_SHOTGUN",
	"EV_HANDCANNON",
	"EV_BULLET",		// otherEntity is the shooter

	"EV_HEADSHOT",		// Elder: spray like SSG shot
	"EV_PAIN",
	"EV_DEATH1",
	"EV_DEATH2",
	"EV_DEATH3",
	"EV_OBITUARY",
	//Elder:
	//Location-specific obits- need separate events b/c you can't stuff >8bits in eventParm
	"EV_OBITUARY_HEAD",
	"EV_OBITUARY_CHEST",
	"EV_OBITUARY_STOMACH",
	"EV_OBITUARY_LEGS",

	"EV_GIB_PLAYER",	// gib a previously living player
	"EV_BREAK_GLASS1",	// Blaze: Breakable glass
	"EV_BREAK_GLASS2",
	"EV_BREAK_GLASS3",
	"EV_CHIP_GLASS",	// Blaze: this even just breaks it a little bit.
	"EV_PRESSURE_WATER",	// NiceAss: Shot an ent under pressure with water
	"EV_SCOREPLUM",		// score plum
	"EV_PROXIMITY_MINE_STICK",
	"EV_PROXIMITY_MINE_TRIGGER",
	"EV_KAMIKAZE",		// kamikaze explodes
	"EV_OBELISKEXPLODE",	// obelisk explodes
	"EV_INVUL_IMPACT",	// invulnerability sphere impact
	"EV_JUICED",		// invulnerability juiced effect
	"EV_LIGHTNINGBOLT",	// lightning bolt bounced of invulnerability sphere
	"EV_DEBUG_LINE",
	"EV_STOPLOOPINGSOUND",
	"EV_TAUNT"
};

/*
===============
BG_AddPredictableEventToPlayerstate

Handles the sequence numbers
===============
*/

void trap_Cvar_VariableStringBuffer(const char *var_name, char *buffer, int bufsize);

void BG_AddPredictableEventToPlayerstate(int newEvent, int eventParm, playerState_t * ps)
{

#ifdef _DEBUG
	{
		char buf[256];

		trap_Cvar_VariableStringBuffer("showevents", buf, sizeof(buf));
		if (atof(buf) != 0) {
#ifdef QAGAME
			Com_Printf(" game event svt %5d -> %5d: num = %20s parm %d\n",
				   ps->pmove_framecount /*ps->commandTime */ , ps->eventSequence, eventnames[newEvent],
				   eventParm);
#else
			Com_Printf("Cgame event svt %5d -> %5d: num = %20s parm %d\n",
				   ps->pmove_framecount /*ps->commandTime */ , ps->eventSequence, eventnames[newEvent],
				   eventParm);
#endif
		}
	}
#endif
	ps->events[ps->eventSequence & (MAX_PS_EVENTS - 1)] = newEvent;
	ps->eventParms[ps->eventSequence & (MAX_PS_EVENTS - 1)] = eventParm;
	ps->eventSequence++;
}

/*
========================
BG_TouchJumpPad
========================
*/
void BG_TouchJumpPad(playerState_t * ps, entityState_t * jumppad)
{
	int effectNum;

	// spectators don't use jump pads
	if (ps->pm_type != PM_NORMAL) {
		return;
	}

	//Makro - disable all this for bot only triggers
	if (!jumppad->powerups) {
		// if we didn't hit this same jumppad the previous frame
		// then don't play the event sound again if we are in a fat trigger
		if (ps->jumppad_ent != jumppad->number) {

			/*
			   vectoangles( jumppad->origin2, angles);
			   p = fabs( AngleNormalize180( angles[PITCH] ) );
			   if( p < 45 ) {
			   effectNum = 0;
			   } else {
			   effectNum = 1;
			   }
			 */
			// NiceAss: For cutsom sounds...
			effectNum = jumppad->generic1;
			BG_AddPredictableEventToPlayerstate(EV_JUMP_PAD, effectNum, ps);
		}
	}
	// remember hitting this jumppad this frame
	ps->jumppad_ent = jumppad->number;
	ps->jumppad_frame = ps->pmove_framecount;
	// give the player the velocity from the jumppad
	VectorCopy(jumppad->origin2, ps->velocity);
}

/*
========================
BG_PlayerStateToEntityState

This is done after each set of usercmd_t on the server,
and after local prediction on the client
========================
*/
void BG_PlayerStateToEntityState(playerState_t * ps, entityState_t * s, qboolean snap)
{
	int i;

	if (ps->pm_type == PM_INTERMISSION || ps->pm_type == PM_SPECTATOR) {
		s->eType = ET_INVISIBLE;
	} else if (ps->stats[STAT_HEALTH] <= GIB_HEALTH) {
		s->eType = ET_INVISIBLE;
	} else {
		s->eType = ET_PLAYER;
	}

	s->number = ps->clientNum;

	s->pos.trType = TR_INTERPOLATE;
	VectorCopy(ps->origin, s->pos.trBase);
	if (snap) {
		SnapVector(s->pos.trBase);
	}
	// set the trDelta for flag direction
	VectorCopy(ps->velocity, s->pos.trDelta);

	s->apos.trType = TR_INTERPOLATE;
	VectorCopy(ps->viewangles, s->apos.trBase);
	if (snap) {
		SnapVector(s->apos.trBase);
	}

	s->angles2[YAW] = ps->movementDir;
	s->legsAnim = ps->legsAnim;
	s->torsoAnim = ps->torsoAnim;
	s->clientNum = ps->clientNum;	// ET_PLAYER looks here instead of at number
	// so corpses can also reference the proper config
	s->eFlags = ps->eFlags;
	if (ps->stats[STAT_HEALTH] <= 0) {
		s->eFlags |= EF_DEAD;
	} else {
		s->eFlags &= ~EF_DEAD;
	}

	if (ps->externalEvent) {
		s->event = ps->externalEvent;
		s->eventParm = ps->externalEventParm;
	} else if (ps->entityEventSequence < ps->eventSequence) {
		int seq;

		if (ps->entityEventSequence < ps->eventSequence - MAX_PS_EVENTS) {
			ps->entityEventSequence = ps->eventSequence - MAX_PS_EVENTS;
		}
		seq = ps->entityEventSequence & (MAX_PS_EVENTS - 1);
		s->event = ps->events[seq] | ((ps->entityEventSequence & 3) << 8);
		s->eventParm = ps->eventParms[seq];
		ps->entityEventSequence++;
	}

	s->weapon = ps->weapon;
	s->groundEntityNum = ps->groundEntityNum;

	s->powerups = 0;
	for (i = 0; i < MAX_POWERUPS; i++) {
		if (ps->powerups[i]) {
			s->powerups |= 1 << i;
		}
	}

	s->loopSound = ps->loopSound;
	s->generic1 = ps->generic1;
}

/*
========================
BG_PlayerStateToEntityStateExtraPolate

This is done after each set of usercmd_t on the server,
and after local prediction on the client
========================
*/
void BG_PlayerStateToEntityStateExtraPolate(playerState_t * ps, entityState_t * s, int time, qboolean snap)
{
	int i;

	if (ps->pm_type == PM_INTERMISSION || ps->pm_type == PM_SPECTATOR) {
		s->eType = ET_INVISIBLE;
	} else if (ps->stats[STAT_HEALTH] <= GIB_HEALTH) {
		s->eType = ET_INVISIBLE;
	} else {
		s->eType = ET_PLAYER;
	}

	s->number = ps->clientNum;

	s->pos.trType = TR_LINEAR_STOP;
	VectorCopy(ps->origin, s->pos.trBase);
	if (snap) {
		SnapVector(s->pos.trBase);
	}
	// set the trDelta for flag direction and linear prediction
	VectorCopy(ps->velocity, s->pos.trDelta);
	// set the time for linear prediction
	s->pos.trTime = time;
	// set maximum extra polation time
	s->pos.trDuration = 50;	// 1000 / sv_fps (default = 20)

	s->apos.trType = TR_INTERPOLATE;
	VectorCopy(ps->viewangles, s->apos.trBase);
	if (snap) {
		SnapVector(s->apos.trBase);
	}

	s->angles2[YAW] = ps->movementDir;
	s->legsAnim = ps->legsAnim;
	s->torsoAnim = ps->torsoAnim;
	s->clientNum = ps->clientNum;	// ET_PLAYER looks here instead of at number
	// so corpses can also reference the proper config
	s->eFlags = ps->eFlags;
	if (ps->stats[STAT_HEALTH] <= 0) {
		s->eFlags |= EF_DEAD;
	} else {
		s->eFlags &= ~EF_DEAD;
	}

	if (ps->externalEvent) {
		s->event = ps->externalEvent;
		s->eventParm = ps->externalEventParm;
	} else if (ps->entityEventSequence < ps->eventSequence) {
		int seq;

		if (ps->entityEventSequence < ps->eventSequence - MAX_PS_EVENTS) {
			ps->entityEventSequence = ps->eventSequence - MAX_PS_EVENTS;
		}
		seq = ps->entityEventSequence & (MAX_PS_EVENTS - 1);
		s->event = ps->events[seq] | ((ps->entityEventSequence & 3) << 8);
		s->eventParm = ps->eventParms[seq];
		ps->entityEventSequence++;
	}

	s->weapon = ps->weapon;
	s->groundEntityNum = ps->groundEntityNum;

	s->powerups = 0;
	for (i = 0; i < MAX_POWERUPS; i++) {
		if (ps->powerups[i]) {
			s->powerups |= 1 << i;
		}
	}

	s->loopSound = ps->loopSound;
	s->generic1 = ps->generic1;
}

//Makro - weapon string aliases

typedef struct {
	const char *name;
	weapon_t weapon;
} weaponAlias_t;

weaponAlias_t weaponAliases[] = {
	{RQ3_PISTOL_NAME, WP_PISTOL},
	{"pistol", WP_PISTOL},
	{"mk23", WP_PISTOL},
	{RQ3_M3_NAME, WP_M3},
	{"m3", WP_M3},
	{"shotgun", WP_M3},
	{RQ3_HANDCANNON_NAME, WP_HANDCANNON},
	{"hc", WP_HANDCANNON},
	{RQ3_M4_NAME, WP_M4},
	{"m4", WP_M4},
	{RQ3_MP5_NAME, WP_MP5},
	{"mp5", WP_MP5},
	{"mp5/10", WP_MP5},
	{RQ3_SSG3000_NAME, WP_SSG3000},
	{"sniper", WP_SSG3000},
	{"ssg3000", WP_SSG3000},
	{"ssg 3000", WP_SSG3000},
	{"ssg", WP_SSG3000},
	{RQ3_AKIMBO_NAME, WP_AKIMBO},
	{"akimbo", WP_AKIMBO},
	{RQ3_KNIFE_NAME, WP_KNIFE},
	{"knife", WP_KNIFE},
	{"knives", WP_KNIFE},
	{RQ3_GRENADE_NAME, WP_GRENADE},
	{"grenade", WP_GRENADE},
	{"grenades", WP_GRENADE},
	{NULL, WP_PISTOL}
};

#define num_weapon_aliases	25

weapon_t CharToWeapon(char *name, weapon_t defweapon)
{
	int i;

	if (!name)
		return defweapon;

	for (i = 0; weaponAliases[i].name != NULL; i++) {
		if (!Q_stricmp(name, weaponAliases[i].name))
			return weaponAliases[i].weapon;
	}

	return defweapon;
}

//Makro - item string aliases

typedef struct {
	const char *name;
	holdable_t item;
} itemAlias_t;

itemAlias_t itemAliases[] = {
	{RQ3_SLIPPERS_NAME, HI_SLIPPERS},
	{"slippers", HI_SLIPPERS},
	{RQ3_KEVLAR_NAME, HI_KEVLAR},
	{"vest", HI_KEVLAR},
	{"kevlar", HI_KEVLAR},
	{RQ3_BANDOLIER_NAME, HI_BANDOLIER},
	{RQ3_LASER_NAME, HI_LASER},
	{"laser", HI_LASER},
	{RQ3_SILENCER_NAME, HI_SILENCER},
	{RQ3_HELMET_NAME, HI_HELMET},
	{"helmet", HI_HELMET},
	{NULL, HI_KEVLAR}
};

#define num_item_aliases	9

holdable_t CharToItem(char *name, holdable_t defitem)
{
	int i;

	if (!name)
		return defitem;

	for (i = 0; itemAliases[i].name != NULL; i++) {
		if (!Q_stricmp(name, itemAliases[i].name))
			return itemAliases[i].item;
	}

	return defitem;
}

/*
=====================
Surfaceparm stuff
=====================
*/

int MatFlags[] = {
	SURF_METALSTEPS,
	SURF_GRAVEL,
	SURF_WOOD,
	SURF_CARPET,
	SURF_METAL2,
	SURF_GLASS,
	SURF_GRASS,
	SURF_SNOW,
	SURF_MUD,
	SURF_WOOD2,
	SURF_HARDMETAL
};

#define MatFlagCount			5

int GetMaterialFromFlag(int flag)
{
	int Material = 0;
	int i = 0;

	for (i = 0; i < MatFlagCount; i++) {
		if ((flag & MatFlags[i])) {
			Material += (1 << i);
		}
	}

	return Material;
}

//metal
qboolean IsMetalMat(int Material)
{
	if (Material == MAT_METALSTEPS || Material == MAT_METAL2 || Material == MAT_HARDMETAL) {
		return qtrue;
	}
	return qfalse;
}

qboolean IsMetalFlag(int flag)
{
	return IsMetalMat(GetMaterialFromFlag(flag));
}

//wood
qboolean IsWoodMat(int Material)
{
	if (Material == MAT_WOOD || Material == MAT_WOOD2) {
		return qtrue;
	}
	return qfalse;
}

qboolean IsWoodFlag(int flag)
{
	return IsWoodMat(GetMaterialFromFlag(flag));
}
