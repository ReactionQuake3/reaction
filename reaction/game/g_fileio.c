#include "q_shared.h"
#include "g_local.h"
#define	MAX_ARENAS_TEXT		8192
//Ok, here is how it works, you feed it a buffer in the form
//char buffer[MAX_ARENAS_TEXT];
//and a file name in the form "test.cfg" or how ever you want
//so you would call it like this
//Cmd_ReadFile_f(mybuf,"motd.txt")
//it would then return a -1 if there is an error that I trapped, otherwise a 0
//also, you will need to parse the file after you get it out!
int Cmd_ReadFile_f( char *buffer, char *fname) 
{
	fileHandle_t f;
	char tbuffer[MAX_ARENAS_TEXT]; //max text per line
    int length; //The int for length of buffer

	length = trap_FS_FOpenFile( fname, &f,FS_READ ); //Checks the file length
	tbuffer[length] = 0;
	if (length < 0) {return -1;} //If Length less than zero
    if (length >= MAX_ARENAS_TEXT) {return -1;}
	trap_FS_Read(tbuffer,length,f); 
	trap_FS_FCloseFile( f ); 
    strcpy (buffer,tbuffer);
	return 0;
}
