//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.4  2002/01/11 19:48:29  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.3  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//

/*****************************************************************************
 * name:		ai_vcmd.h
 *
 * desc:		Quake3 bot AI
 *
 * $Archive: /source/code/botai/ai_vcmd.c $
 * $Author$ 
 * $Revision$
 * $Modtime: 11/10/99 3:30p $
 * $Date$
 *
 *****************************************************************************/

int BotVoiceChatCommand(bot_state_t *bs, int mode, char *voicechat);
void BotVoiceChat_Defend(bot_state_t *bs, int client, int mode);


