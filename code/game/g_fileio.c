//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.5  2002/06/16 20:06:14  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.4  2002/01/11 19:48:30  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.3  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
#include "../qcommon/q_shared.h"
#include "g_local.h"
#define	MAX_ARENAS_TEXT		8192
//Ok, here is how it works, you feed it a buffer in the form
//char buffer[MAX_ARENAS_TEXT];
//and a file name in the form "test.cfg" or how ever you want
//so you would call it like this
//Cmd_ReadFile_f(mybuf,"motd.txt")
//it would then return a -1 if there is an error that I trapped, otherwise a 0
//also, you will need to parse the file after you get it out!
int Cmd_ReadFile_f(char *buffer, char *fname)
{
	fileHandle_t f;
	char tbuffer[MAX_ARENAS_TEXT];	//max text per line
	int length;		//The int for length of buffer

	length = trap_FS_FOpenFile(fname, &f, FS_READ);	//Checks the file length
	tbuffer[length] = 0;
	if (length < 0) {
		return -1;
	}			//If Length less than zero
	if (length >= MAX_ARENAS_TEXT) {
		return -1;
	}
	trap_FS_Read(tbuffer, length, f);
	trap_FS_FCloseFile(f);
	strcpy(buffer, tbuffer);
	return 0;
}
