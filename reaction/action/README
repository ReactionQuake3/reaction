SERVER/PLAYER DOCUMENTATION FOR ACTION 1.52


ACTION-SPECIFIC SERVER VARIABLES

actionmaps: set to 1 if you wish to use the map rotation as defined in your
"action.ini" file (default = 1).

teamplay: whether the game is teamplay (1) or regular DM (0) (default = 0).

roundlimit: the number of wins by one team before the map is ended
(default = 0 [no limit]).

roundtimelimit: the number of minutes a round can go on before a winner is
declared (default = 0 [no limit]).

motd_time: the number of seconds that the initial MOTD should remain on the
player's screen.  This number is rounded up to the nearest 2-second interval
(default = 2).

skipmotd: allows you to skip all but the top two lines of the normal
Action MOTD, for server operators who want large motd.txt files
(default = 0 [don't skip]).

weapons: the maximum number of "unique weapons" a player can carry (the 
bandolier adds 1 to a player's max carry) (default = 1).

items: the number of "special items" a player can carry (default = 1).

ir: whether or not IR vision goggles are enabled for use with the
bandolier (default = 1 [on]). 

radiolog: whether or not all radio messages sent are printed to the
console (default = 0 [no]). 

bholelimit: the number of bulletholes in walls/etc that should be allowed to be
in the game at one time (default = 0 [don't use bulletholes, for a faster
Internet game]).

splatlimit: the number of bloodsplats on the ground/etc that should be allowed
to be in the game at one time (default = 0 [don't use bloodsplats, for a faster
Internet game]).

shelloff: turns off the dropping of expended shells from your gun
(default = 1 [turn off shells, for a faster Internet game]).

knifelimit: the number of throwing knives that can be lying around on the map
at any given time (default = 40).

allweapon: gives all the weapons to each player in teamplay/DM
(default = 0).

allitem: gives all the items to each player in teamplay/DM
(default = 0).

tgren: sets the number of grenades that come with the bandolier in
teamplay (default = 0). 

noscore: if set to 1, individual scores (and damage stats) are not in
effect for teamplay, the only scores visible will be team wins and total
frags (default = 0).

nohud: if set to 1, the standard HUD (health, ammo, etc) is disabled for
all players.  This can allow you to record better-looking demos of staged
scenes (default = 0). 

ininame: if set, changes the name of the Action INI file from "action.ini"
to whatever you specify.  The file must always be located in your Action
game directory.  This should be used on the Quake2 commandline, ie:
  quake2 +set game action +set ininame alternate.ini +set dedicated 1 ...
(default = "action.ini").  

limchasecam: if set to 1, will prevent all players on teams from free
floating, or chase-camming enemy players.  If set to 2, will prevent all
players on teams from using the normal chase cam as well (only the
through-eyes cam on teammates will be allowed).  This variable should be
set to 2 for clan matches, etc (default = 0).

shelloff: turns off the dropping of expended shells from your gun
(default = 1 [turn off shells, for a faster Internet game]).

breakableglass: turns on breakable glass.  Not recommended for Internet
games (default = 0).

glassfragmentlimit: controls the maximum number of glass fragments present
on the map at any time (default = 30).

maxteamkills: the maximum number of teammates a player can kill in one map
before he is temporarily banned from the server.  Only applies during
friendly-fire enabled teamplay games.  Players will also be banned for
wounding teammates, if they wound 4*maxteamkills teammates.  Setting this
to zero disables the feature (default = 0).

tkbanrounds: the number of maps a player will be banned for when he is
banned for killing teammates (default = 2).

twbanrounds: the number of maps a player will be banned for when he is
banned for wounding teammates (default = 2).


ACTION-SPECIFIC PLAYER COMMANDS

reload: reloads current weapon, if applicable to the weapon you're currently
using.  Can be repeated quickly for "fast reload" on shotgun and sniper rifle.

weapon: toggles mode on current weapon.  For single pistol, MP5, and M4, this
toggles between semi-auto/burst and auto mode.  For the sniper rifle, this
changes the lens.  For knives, this changes between slashing and throwing.  For
the grenade, this changes how far you are going to throw.  Not applicable to
any other weapon.

opendoor: opens a door in front of you.

bandage: applies bandages to stop bleeding and cure any limb damage.

team: displays the team you're on, or changes teams (if used with the team
number to switch to as an argument, or "none" to leave your current team and
become a spectator)

id: toggles identification of players on or off (default is on).  only works on
teammates, or when you're an observer, but this can be used to turn it off if
you don't want it.

irvision: toggles IR vision goggles w/ the bandolier (assuming IR vision
is enabled on the server).

motd: brings up the MOTD (message of the day) again.

spectator: can be set to 0 or 1 ("spectator 0", "spectator 1") to toggle being
a spectator in DM games.

hand: in addition to the normal Q2 modes (0 = right-handed, 1 =
left-handed, 2 = "center"-handed), you can select "classic" style shooting
(where shots end up left/right and below the crosshair), or "classic high"
style shooting (where shots end up left/right of the crosshair).  The
proper commands to select those modes are: hand "0 classic" (right-handed
classic), hand "0 classic high" (right-handed classic high), etc.  Note
that the double-quotes are required.

choose: chooses a particular item or weapon as your item or weapon, without
going through the menus, in teamplay (ie: "choose mp5/10 submachinegun" or
"choose lasersight").

(The remaining commands are all radio/partner-related...)

radio: sends a message on the radio, in whatever your default mode is (set with
the "channel" command, defaults to team).  Useable in teamplay, teams-by-skin
DM, or teams-by-model DM.  Valid messages are: 1 ("one"), 2 ("two"), 3
("three"), 4 ("four"), 5 ("five"), 6 ("six"), 7 ("seven"), 8 ("eight"), 9
("nine"), 10 ("ten"), back ("back"), cover ("cover"), down ("down"), enemyd
("enemy down"), enemys ("enemy spotted"), forward ("forward"), go ("go"),
im_hit ("I'm hit"), left ("left"), reportin ("reporting in"), right ("right"),
taking_f ("taking fire, requesting assistance"), teamdown ("teammate down"),
treport ("team, report in"), up ("up").

radiogender: used without an argument, displays your current radio gender.  If
used with "male" or "female", sets your radio gender to that gender.  This
changes the voice on your radio messages.  Default is male.

radio_power: toggles your radio power on or off (default is on).  If your radio
power is off, you won't receive any radio messages, but also can't send any.

radiopartner: sends a radio message to your partner, see the "radio" command
for the valid messages.

radioteam: sends a radio message to your team, see the "radio" command for the
valid messages.

channel: toggles your default radio destination (see the "radio" command)
between team and partner.  Default is team.

say_partner: sends a message to your partner, in much the same way as
"say_team" sends a message to your team.

partner: attempts to establish a partnership.  You must have the person you
want to partner with's name displayed on your HUD, then use the "partner"
command to send a partnership request to him.  The other player will have the
chance to accept (by doing the same thing to you), or denying by ignoring you
or using the "deny" command (see below).

deny: deny a partnership request (see "partner" command above).

unpartner: breaks your current partnership.


WEAPON/ITEM NAMES

These are the exact names of all the weapons/items in the game, for use with
commands like "use", "drop", "choose", "give", etc:

MK23 Pistol
M3 Super 90 Assault Shotgun
MP5/10 Submachinegun
Handcannon
Sniper Rifle
M4 Assault Rifle
Dual MK23 Pistols
Combat Knife (also aliases "throwing combat knife" and 
              "slashing combat knife" for the "use" command)

Pistol Clip
12 Gauge Shells
Machinegun Magazine
M4 Clip
AP Sniper Ammo

M26 Fragmentation Grenade

Kevlar Vest
Lasersight
Stealth Slippers
Silencer
Bandolier


SUBSTITUTIONS IN SAY COMMANDS

The following substitution variables can be used with say, say_team, or
say_partner messages, and they will be replaced with the specified text:

%W = your current weapon
%I = your current item (a random one, if you have more than one)
%H = your current health
%A = your current ammo for your current weapon (in-gun and in-inventory)
%T = names of teammates that are near you and in your line of sight


OTHER CONFIGURATION

IP banning is supported in the standard Q2 3.20 form.  See below for full
details from id's documentation.

Flood protection is supported using the standard Q2 3.20 variables,
"flood_msgs" (default 4), "flood_persecond" (default 4), and "flood_waitdelay"
(default 10).

DM teams-by-model, teams-by-skin, friendly fire, etc are supported using
the standard Q2 "dmflags" values.  A server should use dmflags 256 for
"normal" play (including no friendly fire), 0 for friendly fire.  Some of
the other regular dmflags are also available, such as "spawn farthest"
(512).

action/action.ini is the configuration file for map rotation and teamplay team
name/model/skin setup.  See the example for information on the format.

action/motd.txt, if present, will be appended to the server MOTD.  The
server command "sv reloadmotd" can be used to reload it from disk at any
time, and it is also reloaded at the end of each level automatically.


IP BANNING

Commands: sv addip, sv removeip, sv listip, sv writeip
Server variables: filterban

You can add or remove addresses from the IP filter list with the commands
"sv addip <ip>" and "sv removeip <ip>".  The IP address is specified in
numeric dot format, and any unspecified digits will match any value, so
you can specify an entire class C network with "addip 240.200.100", for
example. "sv removeip" will only remove an address specified in the exact
same way.  The "sv listip" command will print the current list of filters.  
The "sv writeip" command will dump the current filters to a config file,
"listip.cfg" in your Action directory.  You should add a line in your
normal server.cfg that does an "exec listip.cfg" to load this file by
default.  IP addresses in the filter list will only be prohibited from
connecting if the "filterban" variable is set to 1 (this is the default).


OTHER SERVER COMMANDS

sv reloadmotd: reloads the MOTD file from disk.

sv nextmap: immediately skips to the next map in the rotation.


REPORTING BUGS OR MAKING COMMENTS

The maintainers of the Action server code, Zucchini and Fireblade, can be
contacted at spikard@u.washington.edu and ucs_brf@shsu.edu, respectively.  
The Action Quake 2 website is at http://aq2.action-web.net/ and has a
message board where discussions about Action Quake 2 take place.
