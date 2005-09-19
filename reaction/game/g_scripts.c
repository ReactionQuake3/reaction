#include "g_parser.h"

#define BUFFER_SIZE		(32 * 1024)
static char scriptBuffer[BUFFER_SIZE];

// Parser states //////////////////////////////////////////////

TParseState STATE_Base;
TParseState STATE_Main;
TParseState STATE_Restrictions;
TParseState STATE_Rotation;
TParseState STATE_Rotation_Map;
TParseState STATE_Team;



///////////////////////////////////////////////////////////////
// BASE STATE /////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// Functions //////////////////////////////////////////////////

SCRIPT_FUNC(Base_To_Main)
{
	SCRIPT_PUSH_STATE(STATE_Main);
	return 0;
}
END_SCRIPT_FUNC()

SCRIPT_FUNC(Base_To_Restrictions)
{
	SCRIPT_PUSH_STATE(STATE_Restrictions);
	return 0;
}
END_SCRIPT_FUNC()

SCRIPT_FUNC(Base_To_Rotation)
{
	SCRIPT_PUSH_STATE(STATE_Rotation);
	return 0;
}
END_SCRIPT_FUNC()

SCRIPT_FUNC(Base_To_Team)
{
	SCRIPT_PUSH_STATE(STATE_Rotation);
	return 0;
}
END_SCRIPT_FUNC()

// State definition ///////////////////////////////////////////

SCRIPT_STATE(STATE_Base, NO_DATA)
{
	ADD_RULE("[main]",				Base_To_Main)
	ADD_RULE("[restrictions]",		Base_To_Restrictions)
	ADD_RULE("[rotation]",			Base_To_Rotation)
	ADD_RULE("/*",					SFN_SkipComment)
	ADD_RULE("//",					SFN_SkipLineComment)
	END_STATE_MARKER
};
// END BASE STATE /////////////////////////////////////////////



///////////////////////////////////////////////////////////////
// MAIN STATE /////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// Functions //////////////////////////////////////////////////

SCRIPT_FUNC(Main_Cvar)
{
	NEEDS_TOKENS(2, tokens);
	G_Printf("Cvar: %s = %s\n", tokens[0], tokens[1]);
	return 0;
}
END_SCRIPT_FUNC()

// State definition ///////////////////////////////////////////

SCRIPT_STATE(STATE_Main, NO_DATA)
{
	ADD_RULE("[/main]",				SFN_PopState)
	ADD_RULE("cvar",				Main_Cvar)
	ADD_RULE("/*",					SFN_SkipComment)
	ADD_RULE("//",					SFN_SkipLineComment)
	END_STATE_MARKER
};
// END MAIN STATE /////////////////////////////////////////////




///////////////////////////////////////////////////////////////
// TEAM STATE /////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// Functions //////////////////////////////////////////////////

SCRIPT_FUNC(Team_Name)
{
	NEEDS_TOKENS(1, token);
	G_Printf("Team name: %s\n", token[0]);
	return 0;
}
END_SCRIPT_FUNC()

SCRIPT_FUNC(Team_Outfit)
{
	NEEDS_TOKENS(1, token);
	G_Printf("Team skin: %s\n", token[0]);
	return 0;
}
END_SCRIPT_FUNC()

// State definition ///////////////////////////////////////////

SCRIPT_STATE(STATE_Team, NO_DATA)
{
	ADD_RULE("[/team]",				SFN_PopState)
	ADD_RULE("name",				Team_Name)
	ADD_RULE("outfit",				Team_Outfit)
	ADD_RULE("/*",					SFN_SkipComment)
	ADD_RULE("//",					SFN_SkipLineComment)
	END_STATE_MARKER
};
// END TEAM STATE /////////////////////////////////////////////




///////////////////////////////////////////////////////////////
// ROTATION STATE /////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// Functions //////////////////////////////////////////////////

SCRIPT_FUNC(Rotation_To_Map)
{
	SCRIPT_PUSH_STATE(STATE_Rotation_Map);
	return 0;
}
END_SCRIPT_FUNC()

// State definition ///////////////////////////////////////////

SCRIPT_STATE(STATE_Rotation, NO_DATA)
{
	ADD_RULE("[/rotation]",			SFN_PopState)
	ADD_RULE("[map]",				Rotation_To_Map)
	ADD_RULE("/*",					SFN_SkipComment)
	ADD_RULE("//",					SFN_SkipLineComment)
	END_STATE_MARKER
};
// END ROTATION STATE /////////////////////////////////////////




///////////////////////////////////////////////////////////////
// MAP STATE //////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// Functions //////////////////////////////////////////////////

SCRIPT_FUNC(Map_Name)
{
	NEEDS_TOKENS(1, token);
	G_Printf("Map: %s\n", token[0]);
	return 0;
}
END_SCRIPT_FUNC()

SCRIPT_FUNC(Map_Cvar)
{
	NEEDS_TOKENS(2, tokens);
	G_Printf("Cvar: %s = %s\n", tokens[0], tokens[1]);
	return 0;
}
END_SCRIPT_FUNC()

// State definition ///////////////////////////////////////////

SCRIPT_STATE(STATE_Rotation_Map, NO_DATA)
{
	ADD_RULE("[/map]",				SFN_PopState)
	ADD_RULE("map",					Map_Name)
	ADD_RULE("cvar",				Map_Cvar)
	ADD_RULE("/*",					SFN_SkipComment)
	ADD_RULE("//",					SFN_SkipLineComment)
	END_STATE_MARKER
};
// END MAP STATE //////////////////////////////////////////////



///////////////////////////////////////////////////////////////
// RESTRICTIONS STATE /////////////////////////////////////////
///////////////////////////////////////////////////////////////
// Functions //////////////////////////////////////////////////

SCRIPT_FUNC(Restrictions_Cvar)
{
	NEEDS_TOKENS(2, tokens);
	G_Printf("Cvar: %s = %s\n", tokens[0], tokens[1]);
	return 0;
}
END_SCRIPT_FUNC()

// State definition ///////////////////////////////////////////

SCRIPT_STATE(STATE_Restrictions, NO_DATA)
{
	ADD_RULE("[/restrictions]",		SFN_PopState)
	ADD_RULE("cvar",				Restrictions_Cvar)
	ADD_RULE("/*",					SFN_SkipComment)
	ADD_RULE("//",					SFN_SkipLineComment)
	END_STATE_MARKER
};
// END RESTRICTIONS STATE /////////////////////////////////////


///////////////////////////////////////////////////////////////

void G_ParseScript(const char *fname)
{
	fileHandle_t file;
	int len = trap_FS_FOpenFile(fname, &file, FS_READ);

	if (!file)
	{
		G_Printf(S_COLOR_RED " Cannot open file '%s'.\n", fname);
		return;
	}

	trap_FS_Read(scriptBuffer, len, file);
	scriptBuffer[len] = 0;

	trap_FS_FCloseFile(file);

	Script_ParseString(scriptBuffer, &STATE_Base);
}

