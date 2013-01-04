/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.

This file is part of Quake III Arena source code.

Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Quake III Arena source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/
//
// This file must be identical in the quake and utils directories

// contents flags are seperate bits
// a given brush can contribute multiple content bits

// these definitions also need to be in q_shared.h!

#define	CONTENTS_SOLID			0x00000001		// an eye is never valid in a solid

#define CONTENTS_ENVBIT_0		0x00000002
#define CONTENTS_ENVBIT_1		0x00000004

#define	CONTENTS_LAVA			0x00000008
#define	CONTENTS_SLIME			0x00000010
#define	CONTENTS_WATER			0x00000020
#define	CONTENTS_FOG			0x00000040

#define CONTENTS_NOTTEAM1		0x00000080
#define CONTENTS_NOTTEAM2		0x00000100
#define CONTENTS_NOBOTCLIP		0x00000200

#define CONTENTS_ENVBIT_2		0x00000400
#define CONTENTS_ENVBIT_3		0x00000800
#define CONTENTS_ENVBIT_4		0x00001000
#define CONTENTS_ENVBIT_5		0x00002000
#define CONTENTS_ENVBIT_6		0x00004000

#define CONTENTS_ENVIRONMENT_MASK	(CONTENTS_ENVBIT_0|CONTENTS_ENVBIT_1|CONTENTS_ENVBIT_2|CONTENTS_ENVBIT_3|CONTENTS_ENVBIT_4|CONTENTS_ENVBIT_5|CONTENTS_ENVBIT_6)
#define CONTENTS_LIQUID_MASK		(CONTENTS_LAVA|CONTENTS_SLIME|CONTENTS_WATER)

#define	CONTENTS_AREAPORTAL		0x00008000

#define	CONTENTS_PLAYERCLIP		0x00010000
#define	CONTENTS_MONSTERCLIP	0x00020000
//bot specific contents types
#define	CONTENTS_TELEPORTER		0x00040000
#define	CONTENTS_JUMPPAD		0x00080000
#define CONTENTS_CLUSTERPORTAL	0x00100000
#define CONTENTS_DONOTENTER		0x00200000
#define CONTENTS_BOTCLIP		0x00400000
#define CONTENTS_MOVER			0x00800000

#define	CONTENTS_ORIGIN			0x01000000	// removed before bsping an entity

#define	CONTENTS_BODY			0x02000000	// should never be on a brush, only in game
#define	CONTENTS_CORPSE			0x04000000
#define	CONTENTS_DETAIL			0x08000000	// brushes not used for the bsp
#define	CONTENTS_STRUCTURAL		0x10000000	// brushes used for the bsp
#define	CONTENTS_TRANSLUCENT	0x20000000	// don't consume surface fragments inside
#define	CONTENTS_TRIGGER		0x40000000
#define	CONTENTS_NODROP			0x80000000	// don't leave bodies or items (death fog, lava)

#define	SURF_NODAMAGE			0x1		// never give falling damage
#define	SURF_SLICK				0x2		// effects game physics
#define	SURF_SKY				0x4		// lighting from environment map
#define	SURF_LADDER				0x8
#define	SURF_NOIMPACT			0x10	// don't make missile explosions
#define	SURF_NOMARKS			0x20	// don't leave missile marks
#define	SURF_FLESH				0x40	// make flesh sounds and effects
#define	SURF_NODRAW				0x80	// don't generate a drawsurface at all
#define	SURF_HINT				0x100	// make a primary bsp splitter
#define	SURF_SKIP				0x200	// completely ignore, allowing non-closed brushes
#define	SURF_NOLIGHTMAP			0x400	// surface doesn't need a lightmap
#define	SURF_POINTLIGHT			0x800	// generate lighting info at vertexes
#define	SURF_METALSTEPS			0x1000	// clanking footsteps
#define	SURF_NOSTEPS			0x2000	// no footstep sounds
#define	SURF_NONSOLID			0x4000	// don't collide against curves with this set
#define	SURF_LIGHTFILTER		0x8000	// act as a light filter during q3map -light
#define	SURF_ALPHASHADOW		0x10000	// do per-pixel light shadow casting in q3map
#define	SURF_NODLIGHT			0x20000	// don't dlight even if solid (solid lava, skies)
#define SURF_DUST				0x40000 // leave a dust trail when walking on this surface

//Elder: new surfaces
#define SURF_GRAVEL                    0x80000
#define SURF_WOOD                      0x100000
#define SURF_CARPET                    0x200000
#define SURF_METAL2                    0x400000
#define SURF_GLASS                     0x800000
#define SURF_GRASS                     0x1000000
// JBravo: new sounds
#define SURF_SNOW                      0x2000000
#define SURF_MUD                       0x4000000
#define SURF_WOOD2                     0x8000000
#define SURF_HARDMETAL                 0x10000000

