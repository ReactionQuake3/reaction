/*
===========================================================================
Copyright (C) 2010 James Canete (use.less01@gmail.com)

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
// tr_extramath.h

#ifndef __TR_EXTRAMATH_H__
#define __TR_EXTRAMATH_H__

typedef vec_t matrix_t[16];

void Matrix16Zero( matrix_t out );
void Matrix16Identity( matrix_t out );
void Matrix16Copy( const matrix_t in, matrix_t out );
void Matrix16Multiply( const matrix_t in1, const matrix_t in2, matrix_t out );
void Matrix16Transform( const matrix_t in1, const vec4_t in2, vec4_t out );
qboolean Matrix16Compare(const matrix_t a, const matrix_t b);
void Matrix16Dump( const matrix_t in );
void Matrix16Translation( vec3_t vec, matrix_t out );
void Matrix16Ortho( float left, float right, float bottom, float top, float znear, float zfar, matrix_t out );

#define VectorCopy4(a,b)		((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2],(b)[3]=(a)[3])
#define VectorSet4(v,x,y,z,w)	((v)[0]=(x),(v)[1]=(y),(v)[2]=(z),(v)[3]=(w))
#define DotProduct4(a,b)        ((a)[0]*(b)[0] + (a)[1]*(b)[1] + (a)[2]*(b)[2] + (a)[3]*(b)[3])
#define VectorScale4(a,b,c)     ((c)[0]=(a)[0]*(b),(c)[1]=(a)[1]*(b),(c)[2]=(a)[2]*(b),(c)[3]=(a)[3]*(b))

static ID_INLINE int VectorCompare4(const vec4_t v1, const vec4_t v2)
{
	if(v1[0] != v2[0] || v1[1] != v2[1] || v1[2] != v2[2] || v1[3] != v2[3])
	{
		return 0;
	}
	return 1;
}

void VectorLerp( vec3_t a, vec3_t b, float lerp, vec3_t c);

#define SGN(x) (((x) >= 0) ? !!(x) : -1)

#endif