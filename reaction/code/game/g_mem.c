//-----------------------------------------------------------------------------
//
// $Id$
//
//-----------------------------------------------------------------------------
//
// $Log$
// Revision 1.6  2002/06/16 20:06:14  jbravo
// Reindented all the source files with "indent -kr -ut -i8 -l120 -lc120 -sob -bad -bap"
//
// Revision 1.5  2002/01/11 19:48:30  jbravo
// Formatted the source in non DOS format.
//
// Revision 1.4  2001/12/31 16:28:42  jbravo
// I made a Booboo with the Log tag.
//
//
//-----------------------------------------------------------------------------
// Copyright (C) 1999-2000 Id Software, Inc.
//
//
// g_mem.c
//

#include "g_local.h"

#define POOLSIZE	(256 * 1024)

static char memoryPool[POOLSIZE];
static int allocPoint;

void *G_Alloc(int size)
{
	char *p;

	if (g_debugAlloc.integer) {
		G_Printf("G_Alloc of %i bytes (%i left)\n", size, POOLSIZE - allocPoint - ((size + 31) & ~31));
	}

	if (allocPoint + size > POOLSIZE) {
		G_Error("G_Alloc: failed on allocation of %i bytes\n", size);	// bk010103 - was %u, but is signed
		return NULL;
	}

	p = &memoryPool[allocPoint];

	allocPoint += (size + 31) & ~31;

	return p;
}

void G_InitMemory(void)
{
	allocPoint = 0;
}

void Svcmd_GameMem_f(void)
{
	G_Printf("Game memory status: %i out of %i bytes allocated\n", allocPoint, POOLSIZE);
}
