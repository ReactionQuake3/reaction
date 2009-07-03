//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.5  2002/06/16 20:06:13  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
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
 * name:		be_ai_char.h
 *
 * desc:		bot characters
 *
 * $Archive: /source/code/botlib/be_ai_char.h $
 * $Author$ 
 * $Revision$
 * $Modtime: 10/05/99 3:32p $
 * $Date$
 *
 *****************************************************************************/

//loads a bot character from a file
int BotLoadCharacter(char *charfile, float skill);

//frees a bot character
void BotFreeCharacter(int character);

//returns a float characteristic
float Characteristic_Float(int character, int index);

//returns a bounded float characteristic
float Characteristic_BFloat(int character, int index, float min, float max);

//returns an integer characteristic
int Characteristic_Integer(int character, int index);

//returns a bounded integer characteristic
int Characteristic_BInteger(int character, int index, int min, int max);

//returns a string characteristic
void Characteristic_String(int character, int index, char *buf, int size);

//free cached bot characters
void BotShutdownCharacters(void);
