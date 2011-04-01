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
// tr_shade.c

#include "tr_local.h" 
#if idppc_altivec && !defined(MACOS_X)
#include <altivec.h>
#endif

/*

  THIS ENTIRE FILE IS BACK END

  This file deals with applying shaders to surface data in the tess struct.
*/

/*
================
R_ArrayElementDiscrete

This is just for OpenGL conformance testing, it should never be the fastest
================
*/
static void APIENTRY R_ArrayElementDiscrete( GLint index ) {
	qglColor4ubv( tess.svars.colors[ index ] );
	if ( glState.currenttmu ) {
		qglMultiTexCoord2fARB( 0, tess.svars.texcoords[ 0 ][ index ][0], tess.svars.texcoords[ 0 ][ index ][1] );
		qglMultiTexCoord2fARB( 1, tess.svars.texcoords[ 1 ][ index ][0], tess.svars.texcoords[ 1 ][ index ][1] );
	} else {
		qglTexCoord2fv( tess.svars.texcoords[ 0 ][ index ] );
	}
	qglVertex3fv( tess.xyz[ index ] );
}

/*
===================
R_DrawStripElements

===================
*/
static int		c_vertexes;		// for seeing how long our average strips are
static int		c_begins;
static void R_DrawStripElements( int numIndexes, const glIndex_t *indexes, void ( APIENTRY *element )(GLint) ) {
	int i;
	int last[3] = { -1, -1, -1 };
	qboolean even;

	c_begins++;

	if ( numIndexes <= 0 ) {
		return;
	}

	qglBegin( GL_TRIANGLE_STRIP );

	// prime the strip
	element( indexes[0] );
	element( indexes[1] );
	element( indexes[2] );
	c_vertexes += 3;

	last[0] = indexes[0];
	last[1] = indexes[1];
	last[2] = indexes[2];

	even = qfalse;

	for ( i = 3; i < numIndexes; i += 3 )
	{
		// odd numbered triangle in potential strip
		if ( !even )
		{
			// check previous triangle to see if we're continuing a strip
			if ( ( indexes[i+0] == last[2] ) && ( indexes[i+1] == last[1] ) )
			{
				element( indexes[i+2] );
				c_vertexes++;
				assert( indexes[i+2] < tess.numVertexes );
				even = qtrue;
			}
			// otherwise we're done with this strip so finish it and start
			// a new one
			else
			{
				qglEnd();

				qglBegin( GL_TRIANGLE_STRIP );
				c_begins++;

				element( indexes[i+0] );
				element( indexes[i+1] );
				element( indexes[i+2] );

				c_vertexes += 3;

				even = qfalse;
			}
		}
		else
		{
			// check previous triangle to see if we're continuing a strip
			if ( ( last[2] == indexes[i+1] ) && ( last[0] == indexes[i+0] ) )
			{
				element( indexes[i+2] );
				c_vertexes++;

				even = qfalse;
			}
			// otherwise we're done with this strip so finish it and start
			// a new one
			else
			{
				qglEnd();

				qglBegin( GL_TRIANGLE_STRIP );
				c_begins++;

				element( indexes[i+0] );
				element( indexes[i+1] );
				element( indexes[i+2] );
				c_vertexes += 3;

				even = qfalse;
			}
		}

		// cache the last three vertices
		last[0] = indexes[i+0];
		last[1] = indexes[i+1];
		last[2] = indexes[i+2];
	}

	qglEnd();
}



/*
==================
R_DrawElements

Optionally performs our own glDrawElements that looks for strip conditions
instead of using the single glDrawElements call that may be inefficient
without compiled vertex arrays.
==================
*/
static void R_DrawElements( int numIndexes, const glIndex_t *indexes ) {
	int		primitives;

	primitives = r_primitives->integer;

	// default is to use triangles if compiled vertex arrays are present
	if ( primitives == 0 ) {
		if ( qglLockArraysEXT ) {
			primitives = 2;
		} else {
			primitives = 1;
		}
	}


	if ( primitives == 2 ) {
		qglDrawElements( GL_TRIANGLES, 
						numIndexes,
						GL_INDEX_TYPE,
						indexes );
		return;
	}

	if ( primitives == 1 ) {
		R_DrawStripElements( numIndexes,  indexes, qglArrayElement );
		return;
	}
	
	if ( primitives == 3 ) {
		R_DrawStripElements( numIndexes,  indexes, R_ArrayElementDiscrete );
		return;
	}

	// anything else will cause no drawing
}


static void R_DrawElementsVBO( int numIndexes, int firstIndex )
{
	qglDrawElements(GL_TRIANGLES, numIndexes, GL_INDEX_TYPE, BUFFER_OFFSET(firstIndex * sizeof(GL_INDEX_TYPE)));
}


static void R_DrawMultiElementsVBO( int multiDrawPrimitives, const GLvoid **multiDrawFirstIndex, GLsizei *multiDrawNumIndexes)
{
	if (glRefConfig.multiDrawArrays && r_ext_multi_draw_arrays->integer)
	{
		qglMultiDrawElementsEXT(GL_TRIANGLES, multiDrawNumIndexes, GL_INDEX_TYPE, multiDrawFirstIndex, multiDrawPrimitives);
	}
	else
	{
		int i;

		for (i = 0; i < multiDrawPrimitives; i++)
		{
			qglDrawElements(GL_TRIANGLES, multiDrawNumIndexes[i], GL_INDEX_TYPE, multiDrawFirstIndex[i]);
		}
	}
}



/*
=============================================================

SURFACE SHADERS

=============================================================
*/

shaderCommands_t	tess;
static qboolean	setArraysOnce;

/*
=================
R_BindAnimatedImageToTMU

=================
*/
static void R_BindAnimatedImageToTMU( textureBundle_t *bundle, int tmu ) {
	int		index;

	if ( bundle->isVideoMap ) {
		int oldtmu = glState.currenttmu;
		GL_SelectTexture(tmu);
		ri.CIN_RunCinematic(bundle->videoMapHandle);
		ri.CIN_UploadCinematic(bundle->videoMapHandle);
		GL_SelectTexture(oldtmu);
		return;
	}

	if ( bundle->numImageAnimations <= 1 ) {
		GL_BindToTMU( bundle->image[0], tmu);
		return;
	}

	// it is necessary to do this messy calc to make sure animations line up
	// exactly with waveforms of the same frequency
	index = myftol( tess.shaderTime * bundle->imageAnimationSpeed * FUNCTABLE_SIZE );
	index >>= FUNCTABLE_SIZE2;

	if ( index < 0 ) {
		index = 0;	// may happen with shader time offsets
	}
	index %= bundle->numImageAnimations;

	GL_BindToTMU( bundle->image[ index ], tmu );
}

/*
=================
R_BindAnimatedImage

=================
*/
static void R_BindAnimatedImage( textureBundle_t *bundle ) {
	R_BindAnimatedImageToTMU( bundle, glState.currenttmu );
}


/*
================
DrawTris

Draws triangle outlines for debugging
================
*/
static void DrawTris (shaderCommands_t *input) {
	GL_Bind( tr.whiteImage );

	GL_State( GLS_POLYMODE_LINE | GLS_DEPTHMASK_TRUE );
	qglDepthRange( 0, 0 );

	if (glRefConfig.vertexBufferObject && r_arb_vertex_buffer_object->integer)
	{
		if (glRefConfig.glsl && r_arb_shader_objects->integer)
		{
			shaderProgram_t *sp = &tr.textureOnlyShader;

			GLSL_VertexAttribsState(ATTR_POSITION);
			GLSL_BindProgram(sp);
			
			GLSL_SetUniformMatrix16(sp, TEXTUREONLY_UNIFORM_MODELVIEWPROJECTIONMATRIX, glState.modelviewProjection);
			
			if (input->multiDrawPrimitives)
			{
				R_DrawMultiElementsVBO(input->multiDrawPrimitives, (const GLvoid **)input->multiDrawFirstIndex, input->multiDrawNumIndexes);
			}
			else
			{
				R_DrawElementsVBO(input->numIndexes, input->firstIndex);
			}
		}
		else
		{
			// FIXME: implement this
		}
	}
	else
	{
		qglColor3f (1,1,1);

		qglDisableClientState (GL_COLOR_ARRAY);
		qglDisableClientState (GL_TEXTURE_COORD_ARRAY);

		qglVertexPointer (3, GL_FLOAT, 16, input->xyz);	// padded for SIMD

		if (qglLockArraysEXT) {
			qglLockArraysEXT(0, input->numVertexes);
			GLimp_LogComment( "glLockArraysEXT\n" );
		}

		R_DrawElements( input->numIndexes, input->indexes );

		if (qglUnlockArraysEXT) {
			qglUnlockArraysEXT();
			GLimp_LogComment( "glUnlockArraysEXT\n" );
		}
	}
	qglDepthRange( 0, 1 );
}


/*
================
DrawNormals

Draws vertex normals for debugging
================
*/
static void DrawNormals (shaderCommands_t *input) {
	//FIXME: implement this
#if 0
	int		i;
	vec3_t	temp;

	GL_Bind( tr.whiteImage );
	qglColor3f (1,1,1);
	qglDepthRange( 0, 0 );	// never occluded
	GL_State( GLS_POLYMODE_LINE | GLS_DEPTHMASK_TRUE );

	qglBegin (GL_LINES);
	for (i = 0 ; i < input->numVertexes ; i++) {
		qglVertex3fv (input->xyz[i]);
		VectorMA (input->xyz[i], 2, input->normal[i], temp);
		qglVertex3fv (temp);
	}
	qglEnd ();

	qglDepthRange( 0, 1 );
#endif
}

/*
==============
RB_BeginSurface

We must set some things up before beginning any tesselation,
because a surface may be forced to perform a RB_End due
to overflow.
==============
*/
void RB_BeginSurface( shader_t *shader, int fogNum ) {

	shader_t *state = (shader->remappedShader) ? shader->remappedShader : shader;

	tess.numIndexes = 0;
	tess.firstIndex = 0;
	tess.numVertexes = 0;
	tess.multiDrawPrimitives = 0;
	tess.shader = state;
	tess.fogNum = fogNum;
	tess.dlightBits = 0;		// will be OR'd in by surface functions
	tess.xstages = state->stages;
	tess.numPasses = state->numUnfoggedPasses;
	tess.currentStageIteratorFunc = state->optimalStageIteratorFunc;
	tess.useInternalVBO = qtrue;

	tess.shaderTime = backEnd.refdef.floatTime - tess.shader->timeOffset;
	if (tess.shader->clampTime && tess.shaderTime >= tess.shader->clampTime) {
		tess.shaderTime = tess.shader->clampTime;
	}
}



extern float EvalWaveForm( const waveForm_t *wf );
extern float EvalWaveFormClamped( const waveForm_t *wf );


static void GenerateGLTexCoords( shaderStage_t *pStage, int bundleNum)
{
	vec4_t vec;

	switch(pStage->bundle[bundleNum].tcGen)
	{
		case TCGEN_IDENTITY:
			qglDisableClientState ( GL_TEXTURE_COORD_ARRAY );
			qglEnable(GL_TEXTURE_GEN_S);
			qglEnable(GL_TEXTURE_GEN_T);

			vec[0] = 0.0f;
			vec[1] = 0.0f;
			vec[2] = 0.0f;
			vec[3] = 0.0f;

			glTexGenfv(GL_S, GL_OBJECT_PLANE, vec);
			glTexGenfv(GL_T, GL_OBJECT_PLANE, vec);
			break;

		case TCGEN_TEXTURE:
			qglTexCoordPointer( 2, GL_FLOAT, glState.currentVBO->stride_st, BUFFER_OFFSET(glState.currentVBO->ofs_st) );
			qglEnableClientState ( GL_TEXTURE_COORD_ARRAY );
			break;

		case TCGEN_LIGHTMAP:
			qglTexCoordPointer( 2, GL_FLOAT, glState.currentVBO->stride_lightmap, BUFFER_OFFSET(glState.currentVBO->ofs_lightmap) );
			qglEnableClientState ( GL_TEXTURE_COORD_ARRAY );
			break;

		case TCGEN_ENVIRONMENT_MAPPED:
			//FIXME: This doesn't look anything like the original
			qglDisableClientState ( GL_TEXTURE_COORD_ARRAY );
			qglEnable(GL_TEXTURE_GEN_S);
			qglEnable(GL_TEXTURE_GEN_T);
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
			break;

		case TCGEN_VECTOR:
			qglDisableClientState ( GL_TEXTURE_COORD_ARRAY );
			qglEnable(GL_TEXTURE_GEN_S);
			qglEnable(GL_TEXTURE_GEN_T);

			vec[0] = pStage->bundle[0].tcGenVectors[0][0];
			vec[1] = pStage->bundle[0].tcGenVectors[0][1];
			vec[2] = pStage->bundle[0].tcGenVectors[0][2];
			vec[3] = 0.0f;
			
			glTexGenfv(GL_S, GL_OBJECT_PLANE, vec);
			
			vec[0] = pStage->bundle[0].tcGenVectors[1][0];
			vec[1] = pStage->bundle[0].tcGenVectors[2][1];
			vec[2] = pStage->bundle[0].tcGenVectors[3][2];
			vec[3] = 0.0f;
			
			glTexGenfv(GL_T, GL_OBJECT_PLANE, vec);
			break;
		case TCGEN_FOG:
			// FIXME: This doesn't look anything like the original
			{
				vec4_t vec;

				vec[0] = 0.0f;
				vec[1] = 0.0f;
				vec[2] = 1.0f;
				vec[3] = 0.0f;

				qglDisableClientState ( GL_TEXTURE_COORD_ARRAY );
				qglEnable(GL_TEXTURE_GEN_S);
				qglEnable(GL_TEXTURE_GEN_T);
				glTexGenfv(GL_S, GL_EYE_PLANE, vec);
				glTexGenfv(GL_T, GL_EYE_PLANE, vec);
			}
			break;
		default:
			// nothing else is supported, bail out
			break;
	}
}


static void UndoGLTexCoords( shaderStage_t *pStage, int bundleNum)
{
	switch(pStage->bundle[bundleNum].tcGen)
	{
		case TCGEN_IDENTITY:
		case TCGEN_ENVIRONMENT_MAPPED:
		case TCGEN_VECTOR:
		case TCGEN_FOG:
			qglEnableClientState ( GL_TEXTURE_COORD_ARRAY );
			qglDisable(GL_TEXTURE_GEN_S);
			qglDisable(GL_TEXTURE_GEN_T);
			break;

		case TCGEN_TEXTURE:
		case TCGEN_LIGHTMAP:
		default:
			break;
	}
}


static void ComputeTexMatrix( shaderStage_t *pStage, int bundleNum, float *outmatrix)
{
	int tm;
	float matrix[16], currentmatrix[16];
	textureBundle_t *bundle = &pStage->bundle[bundleNum];

/*
	if (pStage->bundle[bundleNum].tcGen == TCGEN_ENVIRONMENT_MAPPED)
	{
		Matrix16Identity(currentmatrix);
		currentmatrix[0] = 1.0f;
		currentmatrix[5] = -1.0f;
		//currentmatrix[10] = 1.0f;
		Matrix16Copy(currentmatrix, outmatrix);
	}
	else*/
	{
		Matrix16Identity(outmatrix);
		Matrix16Identity(currentmatrix);
	}

	for ( tm = 0; tm < bundle->numTexMods ; tm++ ) {
		switch ( bundle->texMods[tm].type )
		{
			
		case TMOD_NONE:
			tm = TR_MAX_TEXMODS;		// break out of for loop
			break;

		case TMOD_TURBULENT:
			RB_CalcTurbulentTexMatrix( &bundle->texMods[tm].wave, 
									 matrix );
			currentmatrix[12] = matrix[12];
			currentmatrix[13] = matrix[13];
			break;

		case TMOD_ENTITY_TRANSLATE:
			RB_CalcScrollTexMatrix( backEnd.currentEntity->e.shaderTexCoord,
								 matrix );
			//Matrix16Multiply(currentmatrix, matrix, outmatrix);
			Matrix16Multiply(matrix, currentmatrix, outmatrix);
			Matrix16Copy(outmatrix, currentmatrix);
			break;

		case TMOD_SCROLL:
			RB_CalcScrollTexMatrix( bundle->texMods[tm].scroll,
									 matrix );
			//Matrix16Multiply(currentmatrix, matrix, outmatrix);
			Matrix16Multiply(matrix, currentmatrix, outmatrix);
			Matrix16Copy(outmatrix, currentmatrix);
			break;

		case TMOD_SCALE:
			RB_CalcScaleTexMatrix( bundle->texMods[tm].scale,
								  matrix );
			//Matrix16Multiply(currentmatrix, matrix, outmatrix);
			Matrix16Multiply(matrix, currentmatrix, outmatrix);
			Matrix16Copy(outmatrix, currentmatrix);
			break;
		
		case TMOD_STRETCH:
			RB_CalcStretchTexMatrix( &bundle->texMods[tm].wave, 
								   matrix );
			//Matrix16Multiply(currentmatrix, matrix, outmatrix);
			Matrix16Multiply(matrix, currentmatrix, outmatrix);
			Matrix16Copy(outmatrix, currentmatrix);
			break;

		case TMOD_TRANSFORM:
			RB_CalcTransformTexMatrix( &bundle->texMods[tm],
									 matrix );
			//Matrix16Multiply(currentmatrix, matrix, outmatrix);
			Matrix16Multiply(matrix, currentmatrix, outmatrix);
			Matrix16Copy(outmatrix, currentmatrix);
			break;

		case TMOD_ROTATE:
			RB_CalcRotateTexMatrix( bundle->texMods[tm].rotateSpeed,
									matrix );
			//Matrix16Multiply(currentmatrix, matrix, outmatrix);
			Matrix16Multiply(matrix, currentmatrix, outmatrix);
			Matrix16Copy(outmatrix, currentmatrix);
			break;

		default:
			ri.Error( ERR_DROP, "ERROR: unknown texmod '%d' in shader '%s'\n", bundle->texMods[tm].type, tess.shader->name );
			break;
		}
	}
}


/*
===================
DrawMultitextured

output = t0 * t1 or t0 + t1

t0 = most upstream according to spec
t1 = most downstream according to spec
===================
*/
static void DrawMultitextured( shaderCommands_t *input, int stage ) {
	shaderStage_t	*pStage;

	pStage = tess.xstages[stage];

	GL_State( pStage->stateBits );

	// this is an ugly hack to work around a GeForce driver
	// bug with multitexture and clip planes
	if ( backEnd.viewParms.isPortal ) {
		qglPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}

	//
	// base
	//
	GL_SelectTexture( 0 );
	qglTexCoordPointer( 2, GL_FLOAT, 0, input->svars.texcoords[0] );
	R_BindAnimatedImage( &pStage->bundle[0] );

	//
	// lightmap/secondary pass
	//
	GL_SelectTexture( 1 );
	qglEnable( GL_TEXTURE_2D );
	qglEnableClientState( GL_TEXTURE_COORD_ARRAY );

	if ( r_lightmap->integer ) {
		GL_TexEnv( GL_REPLACE );
	} else {
		GL_TexEnv( tess.shader->multitextureEnv );
	}

	qglTexCoordPointer( 2, GL_FLOAT, 0, input->svars.texcoords[1] );

	R_BindAnimatedImage( &pStage->bundle[1] );

	R_DrawElements( input->numIndexes, input->indexes );

	//
	// disable texturing on TEXTURE1, then select TEXTURE0
	//
	//qglDisableClientState( GL_TEXTURE_COORD_ARRAY );
	qglDisable( GL_TEXTURE_2D );

	GL_SelectTexture( 0 );
}


/*
===================
DrawMultitexturedVBO

output = t0 * t1 or t0 + t1

t0 = most upstream according to spec
t1 = most downstream according to spec
===================
*/
static void DrawMultitexturedVBO( shaderCommands_t *input, int stage ) {
	shaderStage_t	*pStage;
	float matrix[16];

	pStage = tess.xstages[stage];

	GL_State( pStage->stateBits );

	// this is an ugly hack to work around a GeForce driver
	// bug with multitexture and clip planes
	if ( backEnd.viewParms.isPortal ) {
		qglPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}

	//
	// base
	//
	GL_SelectTexture( 0 );
	GenerateGLTexCoords( pStage, 0 );
	ComputeTexMatrix( pStage, 0, matrix );
	qglMatrixMode(GL_TEXTURE);
	qglLoadMatrixf(matrix);
	qglMatrixMode(GL_MODELVIEW);
	R_BindAnimatedImage( &pStage->bundle[0] );

	//
	// lightmap/secondary pass
	//
	GL_SelectTexture( 1 );
	qglEnable( GL_TEXTURE_2D );
	GenerateGLTexCoords( pStage, 1 );
	ComputeTexMatrix( pStage, 1, matrix );
	qglMatrixMode(GL_TEXTURE);
	qglLoadMatrixf(matrix);
	qglMatrixMode(GL_MODELVIEW);

	if ( r_lightmap->integer ) {
		GL_TexEnv( GL_REPLACE );
	} else {
		GL_TexEnv( tess.shader->multitextureEnv );
	}

	R_BindAnimatedImage( &pStage->bundle[1] );

	if (input->multiDrawPrimitives)
	{
		R_DrawMultiElementsVBO(input->multiDrawPrimitives, (const GLvoid **)input->multiDrawFirstIndex, input->multiDrawNumIndexes);
	}
	else
	{
		R_DrawElementsVBO(input->numIndexes, input->firstIndex);
	}

	qglDisable( GL_TEXTURE_2D );
	UndoGLTexCoords( pStage, 1 );
	qglMatrixMode(GL_TEXTURE);
	qglLoadIdentity();
	qglMatrixMode(GL_MODELVIEW);

	GL_SelectTexture( 0 );
	UndoGLTexCoords( pStage, 0 );
	qglMatrixMode(GL_TEXTURE);
	qglLoadIdentity();
	qglMatrixMode(GL_MODELVIEW);
}


/*
===================
ProjectDlightTexture

Perform dynamic lighting with another rendering pass
===================
*/
#if idppc_altivec
static void ProjectDlightTexture_altivec( void ) {
	int		i, l;
	vec_t	origin0, origin1, origin2;
	float   texCoords0, texCoords1;
	vector float floatColorVec0, floatColorVec1;
	vector float modulateVec, colorVec, zero;
	vector short colorShort;
	vector signed int colorInt;
	vector unsigned char floatColorVecPerm, modulatePerm, colorChar;
	vector unsigned char vSel = VECCONST_UINT8(0x00, 0x00, 0x00, 0xff,
                                               0x00, 0x00, 0x00, 0xff,
                                               0x00, 0x00, 0x00, 0xff,
                                               0x00, 0x00, 0x00, 0xff);
	float	*texCoords;
	byte	*colors;
	byte	clipBits[SHADER_MAX_VERTEXES];
	float	texCoordsArray[SHADER_MAX_VERTEXES][2];
	byte	colorArray[SHADER_MAX_VERTEXES][4];
	unsigned	hitIndexes[SHADER_MAX_INDEXES];
	int		numIndexes;
	float	scale;
	float	radius;
	vec3_t	floatColor;
	float	modulate = 0.0f;

	if ( !backEnd.refdef.num_dlights ) {
		return;
	}

	// There has to be a better way to do this so that floatColor
	// and/or modulate are already 16-byte aligned.
	floatColorVecPerm = vec_lvsl(0,(float *)floatColor);
	modulatePerm = vec_lvsl(0,(float *)&modulate);
	modulatePerm = (vector unsigned char)vec_splat((vector unsigned int)modulatePerm,0);
	zero = (vector float)vec_splat_s8(0);

	for ( l = 0 ; l < backEnd.refdef.num_dlights ; l++ ) {
		dlight_t	*dl;

		if ( !( tess.dlightBits & ( 1 << l ) ) ) {
			continue;	// this surface definately doesn't have any of this light
		}
		texCoords = texCoordsArray[0];
		colors = colorArray[0];

		dl = &backEnd.refdef.dlights[l];
		origin0 = dl->transformed[0];
		origin1 = dl->transformed[1];
		origin2 = dl->transformed[2];
		radius = dl->radius;
		scale = 1.0f / radius;

		if(r_greyscale->integer)
		{
			float luminance;
			
			luminance = LUMA(dl->color[0], dl->color[1], dl->color[2]) * 255.0f;
			floatColor[0] = floatColor[1] = floatColor[2] = luminance;
		}
		else if(r_greyscale->value)
		{
			float luminance;
			
			luminance = LUMA(dl->color[0], dl->color[1], dl->color[2]) * 255.0f;
			floatColor[0] = LERP(dl->color[0] * 255.0f, luminance, r_greyscale->value);
			floatColor[1] = LERP(dl->color[1] * 255.0f, luminance, r_greyscale->value);
			floatColor[2] = LERP(dl->color[2] * 255.0f, luminance, r_greyscale->value);
		}
		else
		{
			floatColor[0] = dl->color[0] * 255.0f;
			floatColor[1] = dl->color[1] * 255.0f;
			floatColor[2] = dl->color[2] * 255.0f;
		}
		floatColorVec0 = vec_ld(0, floatColor);
		floatColorVec1 = vec_ld(11, floatColor);
		floatColorVec0 = vec_perm(floatColorVec0,floatColorVec0,floatColorVecPerm);
		for ( i = 0 ; i < tess.numVertexes ; i++, texCoords += 2, colors += 4 ) {
			int		clip = 0;
			vec_t dist0, dist1, dist2;
			
			dist0 = origin0 - tess.xyz[i][0];
			dist1 = origin1 - tess.xyz[i][1];
			dist2 = origin2 - tess.xyz[i][2];

			backEnd.pc.c_dlightVertexes++;

			texCoords0 = 0.5f + dist0 * scale;
			texCoords1 = 0.5f + dist1 * scale;

			if( !r_dlightBacks->integer &&
					// dist . tess.normal[i]
					( dist0 * tess.normal[i][0] +
					dist1 * tess.normal[i][1] +
					dist2 * tess.normal[i][2] ) < 0.0f ) {
				clip = 63;
			} else {
				if ( texCoords0 < 0.0f ) {
					clip |= 1;
				} else if ( texCoords0 > 1.0f ) {
					clip |= 2;
				}
				if ( texCoords1 < 0.0f ) {
					clip |= 4;
				} else if ( texCoords1 > 1.0f ) {
					clip |= 8;
				}
				texCoords[0] = texCoords0;
				texCoords[1] = texCoords1;

				// modulate the strength based on the height and color
				if ( dist2 > radius ) {
					clip |= 16;
					modulate = 0.0f;
				} else if ( dist2 < -radius ) {
					clip |= 32;
					modulate = 0.0f;
				} else {
					dist2 = Q_fabs(dist2);
					if ( dist2 < radius * 0.5f ) {
						modulate = 1.0f;
					} else {
						modulate = 2.0f * (radius - dist2) * scale;
					}
				}
			}
			clipBits[i] = clip;

			modulateVec = vec_ld(0,(float *)&modulate);
			modulateVec = vec_perm(modulateVec,modulateVec,modulatePerm);
			colorVec = vec_madd(floatColorVec0,modulateVec,zero);
			colorInt = vec_cts(colorVec,0);	// RGBx
			colorShort = vec_pack(colorInt,colorInt);		// RGBxRGBx
			colorChar = vec_packsu(colorShort,colorShort);	// RGBxRGBxRGBxRGBx
			colorChar = vec_sel(colorChar,vSel,vSel);		// RGBARGBARGBARGBA replace alpha with 255
			vec_ste((vector unsigned int)colorChar,0,(unsigned int *)colors);	// store color
		}

		// build a list of triangles that need light
		numIndexes = 0;
		for ( i = 0 ; i < tess.numIndexes ; i += 3 ) {
			int		a, b, c;

			a = tess.indexes[i];
			b = tess.indexes[i+1];
			c = tess.indexes[i+2];
			if ( clipBits[a] & clipBits[b] & clipBits[c] ) {
				continue;	// not lighted
			}
			hitIndexes[numIndexes] = a;
			hitIndexes[numIndexes+1] = b;
			hitIndexes[numIndexes+2] = c;
			numIndexes += 3;
		}

		if ( !numIndexes ) {
			continue;
		}

		qglEnableClientState( GL_TEXTURE_COORD_ARRAY );
		qglTexCoordPointer( 2, GL_FLOAT, 0, texCoordsArray[0] );

		qglEnableClientState( GL_COLOR_ARRAY );
		qglColorPointer( 4, GL_UNSIGNED_BYTE, 0, colorArray );

		GL_Bind( tr.dlightImage );
		// include GLS_DEPTHFUNC_EQUAL so alpha tested surfaces don't add light
		// where they aren't rendered
		if ( dl->additive ) {
			GL_State( GLS_SRCBLEND_ONE | GLS_DSTBLEND_ONE | GLS_DEPTHFUNC_EQUAL );
		}
		else {
			GL_State( GLS_SRCBLEND_DST_COLOR | GLS_DSTBLEND_ONE | GLS_DEPTHFUNC_EQUAL );
		}
		R_DrawElements( numIndexes, hitIndexes );
		backEnd.pc.c_totalIndexes += numIndexes;
		backEnd.pc.c_dlightIndexes += numIndexes;
	}
}
#endif


static void ProjectDlightTexture_scalar( void ) {
	int		i, l;
	vec3_t	origin;
	float	*texCoords;
	byte	*colors;
	byte	clipBits[SHADER_MAX_VERTEXES];
	float	texCoordsArray[SHADER_MAX_VERTEXES][2];
	byte	colorArray[SHADER_MAX_VERTEXES][4];
	unsigned	hitIndexes[SHADER_MAX_INDEXES];
	int		numIndexes;
	float	scale;
	float	radius;
	vec3_t	floatColor;
	float	modulate = 0.0f;

	if ( !backEnd.refdef.num_dlights ) {
		return;
	}

	for ( l = 0 ; l < backEnd.refdef.num_dlights ; l++ ) {
		dlight_t	*dl;

		if ( !( tess.dlightBits & ( 1 << l ) ) ) {
			continue;	// this surface definately doesn't have any of this light
		}
		texCoords = texCoordsArray[0];
		colors = colorArray[0];

		dl = &backEnd.refdef.dlights[l];
		VectorCopy( dl->transformed, origin );
		radius = dl->radius;
		scale = 1.0f / radius;

		if(r_greyscale->integer)
		{
			float luminance;

			luminance = LUMA(dl->color[0], dl->color[1], dl->color[2]) * 255.0f;
			floatColor[0] = floatColor[1] = floatColor[2] = luminance;
		}
		else if(r_greyscale->value)
		{
			float luminance;
			
			luminance = LUMA(dl->color[0], dl->color[1], dl->color[2]) * 255.0f;
			floatColor[0] = LERP(dl->color[0] * 255.0f, luminance, r_greyscale->value);
			floatColor[1] = LERP(dl->color[1] * 255.0f, luminance, r_greyscale->value);
			floatColor[2] = LERP(dl->color[2] * 255.0f, luminance, r_greyscale->value);
		}
		else
		{
			floatColor[0] = dl->color[0] * 255.0f;
			floatColor[1] = dl->color[1] * 255.0f;
			floatColor[2] = dl->color[2] * 255.0f;
		}

		for ( i = 0 ; i < tess.numVertexes ; i++, texCoords += 2, colors += 4 ) {
			int		clip = 0;
			vec3_t	dist;
			
			VectorSubtract( origin, tess.xyz[i], dist );

			backEnd.pc.c_dlightVertexes++;

			texCoords[0] = 0.5f + dist[0] * scale;
			texCoords[1] = 0.5f + dist[1] * scale;

			if( !r_dlightBacks->integer &&
					// dist . tess.normal[i]
					( dist[0] * tess.normal[i][0] +
					dist[1] * tess.normal[i][1] +
					dist[2] * tess.normal[i][2] ) < 0.0f ) {
				clip = 63;
			} else {
				if ( texCoords[0] < 0.0f ) {
					clip |= 1;
				} else if ( texCoords[0] > 1.0f ) {
					clip |= 2;
				}
				if ( texCoords[1] < 0.0f ) {
					clip |= 4;
				} else if ( texCoords[1] > 1.0f ) {
					clip |= 8;
				}
				texCoords[0] = texCoords[0];
				texCoords[1] = texCoords[1];

				// modulate the strength based on the height and color
				if ( dist[2] > radius ) {
					clip |= 16;
					modulate = 0.0f;
				} else if ( dist[2] < -radius ) {
					clip |= 32;
					modulate = 0.0f;
				} else {
					dist[2] = Q_fabs(dist[2]);
					if ( dist[2] < radius * 0.5f ) {
						modulate = 1.0f;
					} else {
						modulate = 2.0f * (radius - dist[2]) * scale;
					}
				}
			}
			clipBits[i] = clip;
			colors[0] = myftol(floatColor[0] * modulate);
			colors[1] = myftol(floatColor[1] * modulate);
			colors[2] = myftol(floatColor[2] * modulate);
			colors[3] = 255;
		}

		// build a list of triangles that need light
		numIndexes = 0;
		for ( i = 0 ; i < tess.numIndexes ; i += 3 ) {
			int		a, b, c;

			a = tess.indexes[i];
			b = tess.indexes[i+1];
			c = tess.indexes[i+2];
			if ( clipBits[a] & clipBits[b] & clipBits[c] ) {
				continue;	// not lighted
			}
			hitIndexes[numIndexes] = a;
			hitIndexes[numIndexes+1] = b;
			hitIndexes[numIndexes+2] = c;
			numIndexes += 3;
		}

		if ( !numIndexes ) {
			continue;
		}

		qglEnableClientState( GL_TEXTURE_COORD_ARRAY );
		qglTexCoordPointer( 2, GL_FLOAT, 0, texCoordsArray[0] );

		qglEnableClientState( GL_COLOR_ARRAY );
		qglColorPointer( 4, GL_UNSIGNED_BYTE, 0, colorArray );

		GL_Bind( tr.dlightImage );
		// include GLS_DEPTHFUNC_EQUAL so alpha tested surfaces don't add light
		// where they aren't rendered
		if ( dl->additive ) {
			GL_State( GLS_SRCBLEND_ONE | GLS_DSTBLEND_ONE | GLS_DEPTHFUNC_EQUAL );
		}
		else {
			GL_State( GLS_SRCBLEND_DST_COLOR | GLS_DSTBLEND_ONE | GLS_DEPTHFUNC_EQUAL );
		}
		R_DrawElements( numIndexes, hitIndexes );
		backEnd.pc.c_totalIndexes += numIndexes;
		backEnd.pc.c_dlightIndexes += numIndexes;
	}
}

static void ProjectDlightTexture( void ) {
#if idppc_altivec
	if (com_altivec->integer) {
		// must be in a seperate function or G3 systems will crash.
		ProjectDlightTexture_altivec();
		return;
	}
#endif
	ProjectDlightTexture_scalar();
}

static void ProjectDlightTextureVBOGLSL( void ) {
	int		l;
	vec3_t	origin;
	float	scale;
	float	radius;

	if ( !backEnd.refdef.num_dlights ) {
		return;
	}

	for ( l = 0 ; l < backEnd.refdef.num_dlights ; l++ ) {
		dlight_t	*dl;
		shaderProgram_t *sp;
		vec4_t vector;

		if ( !( tess.dlightBits & ( 1 << l ) ) ) {
			continue;	// this surface definately doesn't have any of this light
		}

		dl = &backEnd.refdef.dlights[l];
		VectorCopy( dl->transformed, origin );
		radius = dl->radius;
		scale = 1.0f / radius;

		sp = &tr.dlightShader;

		backEnd.pc.c_dlightDraws++;

		GLSL_BindProgram(sp);

		GLSL_SetUniformMatrix16(sp, DLIGHT_UNIFORM_MODELVIEWPROJECTIONMATRIX, glState.modelviewProjection);

		GLSL_SetUniformFloat(sp, DLIGHT_UNIFORM_VERTEXLERP, glState.vertexAttribsInterpolation);
		
		// u_DeformGen
		if(!ShaderRequiresCPUDeforms(tess.shader))
		{
			deformStage_t  *ds;

			// only support the first one
			ds = &tess.shader->deforms[0];

			switch (ds->deformation)
			{
				case DEFORM_WAVE:
					GLSL_SetUniformInt(sp, DLIGHT_UNIFORM_DEFORMGEN, ds->deformationWave.func);
					{
						vec4_t v;
						waveForm_t *wf = &ds->deformationWave;
						VectorSet4(v, wf->base, wf->amplitude, wf->phase, wf->frequency);
						GLSL_SetUniformVec4(sp, DLIGHT_UNIFORM_DEFORMWAVE, v);
					}
					GLSL_SetUniformFloat(sp, DLIGHT_UNIFORM_DEFORMSPREAD, ds->deformationSpread);
					GLSL_SetUniformFloat(sp, DLIGHT_UNIFORM_TIME, tess.shaderTime);
					break;

				case DEFORM_BULGE:
					GLSL_SetUniformInt(sp, DLIGHT_UNIFORM_DEFORMGEN, DGEN_BULGE);
					{
						vec3_t v;
						VectorSet(v, ds->bulgeWidth, ds->bulgeHeight, ds->bulgeSpeed);
						GLSL_SetUniformVec3(sp, DLIGHT_UNIFORM_DEFORMBULGE, v);
					}
					GLSL_SetUniformFloat(sp, DLIGHT_UNIFORM_TIME, tess.shaderTime);
					break;

				default:
					GLSL_SetUniformInt(sp, DLIGHT_UNIFORM_DEFORMGEN, DGEN_NONE);
					break;
			}
		}
		else
		{
			GLSL_SetUniformInt(sp, DLIGHT_UNIFORM_DEFORMGEN, DGEN_NONE);
		}

		vector[0] = dl->color[0];
		vector[1] = dl->color[1];
		vector[2] = dl->color[2];
		vector[3] = 1.0f;
		GLSL_SetUniformVec4(sp, DLIGHT_UNIFORM_COLOR, vector);

		vector[0] = origin[0];
		vector[1] = origin[1];
		vector[2] = origin[2];
		vector[3] = scale;
		GLSL_SetUniformVec4(sp, DLIGHT_UNIFORM_DLIGHTINFO, vector);
	  
		GL_Bind( tr.dlightImage );

		// include GLS_DEPTHFUNC_EQUAL so alpha tested surfaces don't add light
		// where they aren't rendered
		if ( dl->additive ) {
			GL_State( GLS_SRCBLEND_ONE | GLS_DSTBLEND_ONE | GLS_DEPTHFUNC_EQUAL );
		}
		else {
			GL_State( GLS_SRCBLEND_DST_COLOR | GLS_DSTBLEND_ONE | GLS_DEPTHFUNC_EQUAL );
		}

		if (tess.multiDrawPrimitives)
		{
			R_DrawMultiElementsVBO(tess.multiDrawPrimitives, (const GLvoid **)tess.multiDrawFirstIndex, tess.multiDrawNumIndexes);
		}
		else
		{
			R_DrawElementsVBO(tess.numIndexes, tess.firstIndex);
		}

		backEnd.pc.c_totalIndexes += tess.numIndexes;
		backEnd.pc.c_dlightIndexes += tess.numIndexes;
	}
}


/*
===================
RB_FogPass

Blends a fog texture on top of everything else
===================
*/
static void RB_FogPass( void ) {
	fog_t		*fog;
	int			i;

	qglEnableClientState( GL_COLOR_ARRAY );
	qglColorPointer( 4, GL_UNSIGNED_BYTE, 0, tess.svars.colors );

	qglEnableClientState( GL_TEXTURE_COORD_ARRAY);
	qglTexCoordPointer( 2, GL_FLOAT, 0, tess.svars.texcoords[0] );

	fog = tr.world->fogs + tess.fogNum;

	for ( i = 0; i < tess.numVertexes; i++ ) {
		* ( int * )&tess.svars.colors[i] = fog->colorInt;
	}

	RB_CalcFogTexCoords( ( float * ) tess.svars.texcoords[0] );

	GL_Bind( tr.fogImage );

	if ( tess.shader->fogPass == FP_EQUAL ) {
		GL_State( GLS_SRCBLEND_SRC_ALPHA | GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA | GLS_DEPTHFUNC_EQUAL );
	} else {
		GL_State( GLS_SRCBLEND_SRC_ALPHA | GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA );
	}

	R_DrawElements( tess.numIndexes, tess.indexes );
}

/*
===================
RB_FogPassVBOGLSL

Blends a fog texture on top of everything else
===================
*/
static void RB_FogPassVBOGLSL( void ) {
	fog_t		*fog;
	vec3_t  local;
	vec4_t  color;
	vec4_t	fogDistanceVector, fogDepthVector = {0, 0, 0, 0};
	float		eyeT;
	shaderProgram_t *sp = &tr.fogShader;

	backEnd.pc.c_fogDraws++;

	GLSL_BindProgram(sp);

	fog = tr.world->fogs + tess.fogNum;

	GLSL_SetUniformMatrix16(sp, FOGPASS_UNIFORM_MODELVIEWPROJECTIONMATRIX, glState.modelviewProjection);

	GLSL_SetUniformFloat(sp, FOGPASS_UNIFORM_VERTEXLERP, glState.vertexAttribsInterpolation);
	
	// u_DeformGen
	if(!ShaderRequiresCPUDeforms(tess.shader))
	{
		deformStage_t  *ds;

		// only support the first one
		ds = &tess.shader->deforms[0];

		switch (ds->deformation)
		{
			case DEFORM_WAVE:
				GLSL_SetUniformInt(sp, FOGPASS_UNIFORM_DEFORMGEN, ds->deformationWave.func);
				{
					vec4_t v;
					waveForm_t *wf = &ds->deformationWave;
					VectorSet4(v, wf->base, wf->amplitude, wf->phase, wf->frequency);
					GLSL_SetUniformVec4(sp, FOGPASS_UNIFORM_DEFORMWAVE, v);
				}
				GLSL_SetUniformFloat(sp, FOGPASS_UNIFORM_DEFORMSPREAD, ds->deformationSpread);
				GLSL_SetUniformFloat(sp, FOGPASS_UNIFORM_TIME, tess.shaderTime);
				break;

			case DEFORM_BULGE:
				GLSL_SetUniformInt(sp, FOGPASS_UNIFORM_DEFORMGEN, DGEN_BULGE);
				{
					vec3_t v;
					VectorSet(v, ds->bulgeWidth, ds->bulgeHeight, ds->bulgeSpeed);
					GLSL_SetUniformVec3(sp, FOGPASS_UNIFORM_DEFORMBULGE, v);
				}
				GLSL_SetUniformFloat(sp, FOGPASS_UNIFORM_TIME, tess.shaderTime);
				break;

			default:
				GLSL_SetUniformInt(sp, FOGPASS_UNIFORM_DEFORMGEN, DGEN_NONE);
				break;
		}
	}
	else
	{
		GLSL_SetUniformInt(sp, FOGPASS_UNIFORM_DEFORMGEN, DGEN_NONE);
	}

	color[0] = ((unsigned char *)(&fog->colorInt))[0] / 255.0f;
	color[1] = ((unsigned char *)(&fog->colorInt))[1] / 255.0f;
	color[2] = ((unsigned char *)(&fog->colorInt))[2] / 255.0f;
	color[3] = ((unsigned char *)(&fog->colorInt))[3] / 255.0f;
	GLSL_SetUniformVec4(sp, FOGPASS_UNIFORM_COLOR, color);

	// from RB_CalcFogTexCoords()
	VectorSubtract( backEnd.or.origin, backEnd.viewParms.or.origin, local );
	fogDistanceVector[0] = -backEnd.or.modelMatrix[2];
	fogDistanceVector[1] = -backEnd.or.modelMatrix[6];
	fogDistanceVector[2] = -backEnd.or.modelMatrix[10];
	fogDistanceVector[3] = DotProduct( local, backEnd.viewParms.or.axis[0] );

	// scale the fog vectors based on the fog's thickness
	fogDistanceVector[0] *= fog->tcScale;
	fogDistanceVector[1] *= fog->tcScale;
	fogDistanceVector[2] *= fog->tcScale;
	fogDistanceVector[3] *= fog->tcScale;

	// rotate the gradient vector for this orientation
	if ( fog->hasSurface ) {
		fogDepthVector[0] = fog->surface[0] * backEnd.or.axis[0][0] + 
			fog->surface[1] * backEnd.or.axis[0][1] + fog->surface[2] * backEnd.or.axis[0][2];
		fogDepthVector[1] = fog->surface[0] * backEnd.or.axis[1][0] + 
			fog->surface[1] * backEnd.or.axis[1][1] + fog->surface[2] * backEnd.or.axis[1][2];
		fogDepthVector[2] = fog->surface[0] * backEnd.or.axis[2][0] + 
			fog->surface[1] * backEnd.or.axis[2][1] + fog->surface[2] * backEnd.or.axis[2][2];
		fogDepthVector[3] = -fog->surface[3] + DotProduct( backEnd.or.origin, fog->surface );

		eyeT = DotProduct( backEnd.or.viewOrigin, fogDepthVector ) + fogDepthVector[3];
	} else {
		eyeT = 1;	// non-surface fog always has eye inside
	}

	fogDistanceVector[3] += 1.0/512;

	GLSL_SetUniformVec4(sp, FOGPASS_UNIFORM_FOGDISTANCE, fogDistanceVector);
	GLSL_SetUniformVec4(sp, FOGPASS_UNIFORM_FOGDEPTH, fogDepthVector);
	GLSL_SetUniformFloat(sp, FOGPASS_UNIFORM_FOGEYET, eyeT);

	if ( tess.shader->fogPass == FP_EQUAL ) {
		GL_State( GLS_SRCBLEND_SRC_ALPHA | GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA | GLS_DEPTHFUNC_EQUAL );
	} else {
		GL_State( GLS_SRCBLEND_SRC_ALPHA | GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA );
	}

	if (tess.multiDrawPrimitives)
	{
		R_DrawMultiElementsVBO(tess.multiDrawPrimitives, (const GLvoid **)tess.multiDrawFirstIndex, tess.multiDrawNumIndexes);
	}
	else
	{
		R_DrawElementsVBO(tess.numIndexes, tess.firstIndex);
	}
}


/*
===============
ComputeColors
===============
*/
static void ComputeColors( shaderStage_t *pStage )
{
	int		i;

	//
	// rgbGen
	//
	switch ( pStage->rgbGen )
	{
		case CGEN_IDENTITY:
			Com_Memset( tess.svars.colors, 0xff, tess.numVertexes * 4 );
			break;
		default:
		case CGEN_IDENTITY_LIGHTING:
			Com_Memset( tess.svars.colors, tr.identityLightByte, tess.numVertexes * 4 );
			break;
		case CGEN_LIGHTING_DIFFUSE:
			RB_CalcDiffuseColor( ( unsigned char * ) tess.svars.colors );
			break;
		case CGEN_EXACT_VERTEX:
			Com_Memcpy( tess.svars.colors, tess.vertexColors, tess.numVertexes * sizeof( tess.vertexColors[0] ) );
			break;
		case CGEN_CONST:
			for ( i = 0; i < tess.numVertexes; i++ ) {
				*(int *)tess.svars.colors[i] = *(int *)pStage->constantColor;
			}
			break;
		case CGEN_VERTEX:
			if ( tr.identityLight == 1 )
			{
				Com_Memcpy( tess.svars.colors, tess.vertexColors, tess.numVertexes * sizeof( tess.vertexColors[0] ) );
			}
			else
			{
				for ( i = 0; i < tess.numVertexes; i++ )
				{
					tess.svars.colors[i][0] = tess.vertexColors[i][0] * tr.identityLight;
					tess.svars.colors[i][1] = tess.vertexColors[i][1] * tr.identityLight;
					tess.svars.colors[i][2] = tess.vertexColors[i][2] * tr.identityLight;
					tess.svars.colors[i][3] = tess.vertexColors[i][3];
				}
			}
			break;
		case CGEN_ONE_MINUS_VERTEX:
			if ( tr.identityLight == 1 )
			{
				for ( i = 0; i < tess.numVertexes; i++ )
				{
					tess.svars.colors[i][0] = 255 - tess.vertexColors[i][0];
					tess.svars.colors[i][1] = 255 - tess.vertexColors[i][1];
					tess.svars.colors[i][2] = 255 - tess.vertexColors[i][2];
				}
			}
			else
			{
				for ( i = 0; i < tess.numVertexes; i++ )
				{
					tess.svars.colors[i][0] = ( 255 - tess.vertexColors[i][0] ) * tr.identityLight;
					tess.svars.colors[i][1] = ( 255 - tess.vertexColors[i][1] ) * tr.identityLight;
					tess.svars.colors[i][2] = ( 255 - tess.vertexColors[i][2] ) * tr.identityLight;
				}
			}
			break;
		case CGEN_FOG:
			{
				fog_t		*fog;

				fog = tr.world->fogs + tess.fogNum;

				for ( i = 0; i < tess.numVertexes; i++ ) {
					* ( int * )&tess.svars.colors[i] = fog->colorInt;
				}
			}
			break;
		case CGEN_WAVEFORM:
			RB_CalcWaveColor( &pStage->rgbWave, ( unsigned char * ) tess.svars.colors );
			break;
		case CGEN_ENTITY:
			RB_CalcColorFromEntity( ( unsigned char * ) tess.svars.colors );
			break;
		case CGEN_ONE_MINUS_ENTITY:
			RB_CalcColorFromOneMinusEntity( ( unsigned char * ) tess.svars.colors );
			break;
	}

	//
	// alphaGen
	//
	switch ( pStage->alphaGen )
	{
	case AGEN_SKIP:
		break;
	case AGEN_IDENTITY:
		if ( pStage->rgbGen != CGEN_IDENTITY ) {
			if ( ( pStage->rgbGen == CGEN_VERTEX && tr.identityLight != 1 ) ||
				 pStage->rgbGen != CGEN_VERTEX ) {
				for ( i = 0; i < tess.numVertexes; i++ ) {
					tess.svars.colors[i][3] = 0xff;
				}
			}
		}
		break;
	case AGEN_CONST:
		if ( pStage->rgbGen != CGEN_CONST ) {
			for ( i = 0; i < tess.numVertexes; i++ ) {
				tess.svars.colors[i][3] = pStage->constantColor[3];
			}
		}
		break;
	case AGEN_WAVEFORM:
		RB_CalcWaveAlpha( &pStage->alphaWave, ( unsigned char * ) tess.svars.colors );
		break;
	case AGEN_LIGHTING_SPECULAR:
		RB_CalcSpecularAlpha( ( unsigned char * ) tess.svars.colors );
		break;
	case AGEN_ENTITY:
		RB_CalcAlphaFromEntity( ( unsigned char * ) tess.svars.colors );
		break;
	case AGEN_ONE_MINUS_ENTITY:
		RB_CalcAlphaFromOneMinusEntity( ( unsigned char * ) tess.svars.colors );
		break;
    case AGEN_VERTEX:
		if ( pStage->rgbGen != CGEN_VERTEX ) {
			for ( i = 0; i < tess.numVertexes; i++ ) {
				tess.svars.colors[i][3] = tess.vertexColors[i][3];
			}
		}
        break;
    case AGEN_ONE_MINUS_VERTEX:
        for ( i = 0; i < tess.numVertexes; i++ )
        {
			tess.svars.colors[i][3] = 255 - tess.vertexColors[i][3];
        }
        break;
	case AGEN_PORTAL:
		{
			unsigned char alpha;

			for ( i = 0; i < tess.numVertexes; i++ )
			{
				float len;
				vec3_t v;

				VectorSubtract( tess.xyz[i], backEnd.viewParms.or.origin, v );
				len = VectorLength( v );

				len /= tess.shader->portalRange;

				if ( len < 0 )
				{
					alpha = 0;
				}
				else if ( len > 1 )
				{
					alpha = 0xff;
				}
				else
				{
					alpha = len * 0xff;
				}

				tess.svars.colors[i][3] = alpha;
			}
		}
		break;
	}

	//
	// fog adjustment for colors to fade out as fog increases
	//
	if ( tess.fogNum )
	{
		switch ( pStage->adjustColorsForFog )
		{
		case ACFF_MODULATE_RGB:
			RB_CalcModulateColorsByFog( ( unsigned char * ) tess.svars.colors );
			break;
		case ACFF_MODULATE_ALPHA:
			RB_CalcModulateAlphasByFog( ( unsigned char * ) tess.svars.colors );
			break;
		case ACFF_MODULATE_RGBA:
			RB_CalcModulateRGBAsByFog( ( unsigned char * ) tess.svars.colors );
			break;
		case ACFF_NONE:
			break;
		}
	}
	
	// if in greyscale rendering mode turn all color values into greyscale.
	if(r_greyscale->integer)
	{
		int scale;
		for(i = 0; i < tess.numVertexes; i++)
		{
			scale = LUMA(tess.svars.colors[i][0], tess.svars.colors[i][1], tess.svars.colors[i][2]);
 			tess.svars.colors[i][0] = tess.svars.colors[i][1] = tess.svars.colors[i][2] = scale;
		}
	}
	else if(r_greyscale->value)
	{
		float scale;
		
		for(i = 0; i < tess.numVertexes; i++)
		{
			scale = LUMA(tess.svars.colors[i][0], tess.svars.colors[i][1], tess.svars.colors[i][2]);
			tess.svars.colors[i][0] = LERP(tess.svars.colors[i][0], scale, r_greyscale->value);
			tess.svars.colors[i][1] = LERP(tess.svars.colors[i][1], scale, r_greyscale->value);
			tess.svars.colors[i][2] = LERP(tess.svars.colors[i][2], scale, r_greyscale->value);
		}
	}
}

static void ComputeHelperColor( shaderStage_t *pStage, vec4_t color)
{
	//
	// rgbGen
	//
	switch ( pStage->rgbGen )
	{
		case CGEN_IDENTITY:
			color[0] = 1.0f;
			color[1] = 1.0f;
			color[2] = 1.0f;
			color[3] = 1.0f;
			break;
		case CGEN_IDENTITY_LIGHTING:
			color[0] = tr.identityLight;
			color[1] = tr.identityLight;
			color[2] = tr.identityLight;
			color[3] = tr.identityLight; // FIXME: Code was like this in quake 3, is this a bug?
			break;
		case CGEN_LIGHTING_DIFFUSE:
			// Done entirely in vertex program
			break;
		case CGEN_EXACT_VERTEX:
			// Done entirely in vertex program
			break;
		case CGEN_CONST:
			color[0] = pStage->constantColor[0] / 255.0f;
			color[1] = pStage->constantColor[1] / 255.0f;
			color[2] = pStage->constantColor[2] / 255.0f;
			color[3] = pStage->constantColor[3] / 255.0f;
			break;
		case CGEN_VERTEX:
		case CGEN_ONE_MINUS_VERTEX:
			color[0] = tr.identityLight;
			color[1] = tr.identityLight;
			color[2] = tr.identityLight;
			color[3] = 1.0f;
			break;
		case CGEN_FOG:
			{
				fog_t		*fog;

				fog = tr.world->fogs + tess.fogNum;

				color[0] = ((unsigned char *)(&fog->colorInt))[0] / 255.0f;
				color[1] = ((unsigned char *)(&fog->colorInt))[1] / 255.0f;
				color[2] = ((unsigned char *)(&fog->colorInt))[2] / 255.0f;
				color[3] = ((unsigned char *)(&fog->colorInt))[3] / 255.0f;
			}
			break;
		case CGEN_WAVEFORM:
			{
				// from RB_CalcWaveColor
				float glow;
				waveForm_t *wf = &pStage->rgbWave;

				if ( wf->func == GF_NOISE ) {
					glow = wf->base + R_NoiseGet4f( 0, 0, 0, ( tess.shaderTime + wf->phase ) * wf->frequency ) * wf->amplitude;
				} else {
					glow = EvalWaveForm( wf ) * tr.identityLight;
				}
				
				if ( glow < 0 ) {
					glow = 0;
				}
				else if ( glow > 1 ) {
					glow = 1;
				}

				color[0] = glow;
				color[1] = glow;
				color[2] = glow;
				color[3] = 1.0f;
			}
			break;
		case CGEN_ENTITY:
			if (backEnd.currentEntity)
			{
				color[0] = ((unsigned char *)backEnd.currentEntity->e.shaderRGBA)[0] / 255.0f;
				color[1] = ((unsigned char *)backEnd.currentEntity->e.shaderRGBA)[1] / 255.0f;
				color[2] = ((unsigned char *)backEnd.currentEntity->e.shaderRGBA)[2] / 255.0f;
				color[3] = ((unsigned char *)backEnd.currentEntity->e.shaderRGBA)[3] / 255.0f;
			}
			else // FIXME: does original quake3 black out vertex colors like this?
			{
				color[0] = 0.0f;
				color[1] = 0.0f;
				color[2] = 0.0f;
				color[3] = 0.0f;
			}
			break;
		case CGEN_ONE_MINUS_ENTITY:
			if (backEnd.currentEntity)
			{
				color[0] = 1.0f - ((unsigned char *)backEnd.currentEntity->e.shaderRGBA)[0] / 255.0f;
				color[1] = 1.0f - ((unsigned char *)backEnd.currentEntity->e.shaderRGBA)[1] / 255.0f;
				color[2] = 1.0f - ((unsigned char *)backEnd.currentEntity->e.shaderRGBA)[2] / 255.0f;
				color[3] = 1.0f - ((unsigned char *)backEnd.currentEntity->e.shaderRGBA)[3] / 255.0f;
			}
			else // FIXME: does original quake3 black out vertex colors like this?
			{
				color[0] = 0.0f;
				color[1] = 0.0f;
				color[2] = 0.0f;
				color[3] = 0.0f;
			}
			break;
		default:
			break;
	}

	//
	// alphaGen
	//
	switch ( pStage->alphaGen )
	{
	case AGEN_SKIP:
		break;
	case AGEN_IDENTITY:
		if ( pStage->rgbGen != CGEN_IDENTITY ) {
			if ( ( pStage->rgbGen == CGEN_VERTEX && tr.identityLight != 1 ) ||
				 pStage->rgbGen != CGEN_VERTEX ) {
				color[3] = 1.0f;
			}
		}
		break;
	case AGEN_CONST:
		if ( pStage->rgbGen != CGEN_CONST ) {
			color[3] = pStage->constantColor[3] / 255.0f;
		}
		break;
	case AGEN_WAVEFORM:
		// From RB_CalcWaveAlpha
		{
			float glow;
			waveForm_t *wf = &pStage->alphaWave;
			glow = EvalWaveFormClamped( wf );
			color[3] = glow;
		}
		break;
	case AGEN_LIGHTING_SPECULAR:
		// Done entirely in vertex program
		// RB_CalcSpecularAlpha( ( unsigned char * ) tess.svars.colors );
		break;
	case AGEN_ENTITY:
		//RB_CalcAlphaFromEntity( ( unsigned char * ) tess.svars.colors );
		if (backEnd.currentEntity)
		{
			color[3] = ((unsigned char *)backEnd.currentEntity->e.shaderRGBA)[3] / 255.0f;
		}
		break;
	case AGEN_ONE_MINUS_ENTITY:
		//RB_CalcAlphaFromOneMinusEntity( ( unsigned char * ) tess.svars.colors );
		if (backEnd.currentEntity)
		{
			color[3] = 1.0f - ((unsigned char *)backEnd.currentEntity->e.shaderRGBA)[3] / 255.0f;
		}
		break;
    case AGEN_VERTEX:
		// Done entirely in vertex program
        break;
    case AGEN_ONE_MINUS_VERTEX:
		// Done entirely in vertex program
        break;
	case AGEN_PORTAL:
		// Done entirely in vertex program
		break;
	}

	//
	// pStage->adjustColorsForFog is done in the vertex program now
	//

	// FIXME: find some way to implement this.
#if 0
	// if in greyscale rendering mode turn all color values into greyscale.
	if(r_greyscale->integer)
	{
		int scale;
		
		for(i = 0; i < tess.numVertexes; i++)
		{
			scale = (tess.svars.colors[i][0] + tess.svars.colors[i][1] + tess.svars.colors[i][2]) / 3;
			tess.svars.colors[i][0] = tess.svars.colors[i][1] = tess.svars.colors[i][2] = scale;
		}
	}
#endif

}

/*
===============
ComputeColorMatrix

if disableVertexColors is true, outmatrix[12-15] contains a color that should be used.
===============
*/

static void ComputeColorMatrix( shaderStage_t *pStage, float *outmatrix, qboolean *disableVertexColors)
{
	*disableVertexColors = qfalse;

	//
	// rgbGen
	//
	switch ( pStage->rgbGen )
	{
		case CGEN_IDENTITY:
			*disableVertexColors = qtrue;
			Matrix16Zero(outmatrix);
			outmatrix[12] = 1.0f;
			outmatrix[13] = 1.0f;
			outmatrix[14] = 1.0f;
			outmatrix[15] = 1.0f;
			break;
		default:
		case CGEN_IDENTITY_LIGHTING:
			*disableVertexColors = qtrue;
			Matrix16Zero(outmatrix);
			outmatrix[12] = tr.identityLight;
			outmatrix[13] = tr.identityLight;
			outmatrix[14] = tr.identityLight;
			outmatrix[15] = 1.0f;  // FIXME: used to just be straight tr.identityLight, is this a bug?
			break;
		case CGEN_LIGHTING_DIFFUSE:
			// FIXME: Can't do this with just a matrix
			//RB_CalcDiffuseColor( ( unsigned char * ) tess.svars.colors );
			*disableVertexColors = qtrue;
			Matrix16Zero(outmatrix);
			outmatrix[12] = 1.0f;
			outmatrix[13] = 1.0f;
			outmatrix[14] = 1.0f;
			outmatrix[15] = 1.0f;
			break;
		case CGEN_EXACT_VERTEX:
			Matrix16Identity(outmatrix);
			break;
		case CGEN_CONST:
			*disableVertexColors = qtrue;
			Matrix16Zero(outmatrix);
			outmatrix[12] = pStage->constantColor[0] / 255.0f;
			outmatrix[13] = pStage->constantColor[1] / 255.0f;
			outmatrix[14] = pStage->constantColor[2] / 255.0f;
			outmatrix[15] = pStage->constantColor[3] / 255.0f;
			break;
		case CGEN_VERTEX:
			Matrix16Identity(outmatrix);
			outmatrix[ 0] = tr.identityLight;
			outmatrix[ 5] = tr.identityLight;
			outmatrix[10] = tr.identityLight;
			outmatrix[15] = 1.0f;
			break;
		case CGEN_ONE_MINUS_VERTEX:
			// FIXME: Not a perfect fit, if alpha is less than 1.0f or identitylight isn't 1 then this doesn't work
#if 0
			if ( tr.identityLight == 1 )
			{
				for ( i = 0; i < tess.numVertexes; i++ )
				{
					tess.svars.colors[i][0] = 255 - tess.vertexColors[i][0];
					tess.svars.colors[i][1] = 255 - tess.vertexColors[i][1];
					tess.svars.colors[i][2] = 255 - tess.vertexColors[i][2];
				}
			}
			else
			{
				for ( i = 0; i < tess.numVertexes; i++ )
				{
					tess.svars.colors[i][0] = ( 255 - tess.vertexColors[i][0] ) * tr.identityLight;
					tess.svars.colors[i][1] = ( 255 - tess.vertexColors[i][1] ) * tr.identityLight;
					tess.svars.colors[i][2] = ( 255 - tess.vertexColors[i][2] ) * tr.identityLight;
				}
			}
#endif
			Matrix16Zero(outmatrix);
			outmatrix[0] = -1.0f;
			outmatrix[5] = -1.0f;
			outmatrix[10] = -1.0f;

			outmatrix[12] = 1.0f;
			outmatrix[13] = 1.0f;
			outmatrix[14] = 1.0f;
			outmatrix[15] = 1.0f;
			break;
		case CGEN_FOG:
			*disableVertexColors = qtrue;
			{
				fog_t		*fog;

				fog = tr.world->fogs + tess.fogNum;

				outmatrix[12] = ((unsigned char *)(&fog->colorInt))[0] / 255.0f;
				outmatrix[13] = ((unsigned char *)(&fog->colorInt))[1] / 255.0f;
				outmatrix[14] = ((unsigned char *)(&fog->colorInt))[2] / 255.0f;
				outmatrix[15] = ((unsigned char *)(&fog->colorInt))[3] / 255.0f;

			}
			break;
		case CGEN_WAVEFORM:
			*disableVertexColors = qtrue;
			{
				// from RB_CalcWaveColor
				float glow;
				waveForm_t *wf = &pStage->rgbWave;

				if ( wf->func == GF_NOISE ) {
					glow = wf->base + R_NoiseGet4f( 0, 0, 0, ( tess.shaderTime + wf->phase ) * wf->frequency ) * wf->amplitude;
				} else {
					glow = EvalWaveForm( wf ) * tr.identityLight;
				}
				
				if ( glow < 0 ) {
					glow = 0;
				}
				else if ( glow > 1 ) {
					glow = 1;
				}

				outmatrix[12] = glow;
				outmatrix[13] = glow;
				outmatrix[14] = glow;
				outmatrix[15] = 1.0f;
			}
			break;
		case CGEN_ENTITY:
			*disableVertexColors = qtrue;
			if (backEnd.currentEntity)
			{
				outmatrix[12] = ((unsigned char *)backEnd.currentEntity->e.shaderRGBA)[0] / 255.0f;
				outmatrix[13] = ((unsigned char *)backEnd.currentEntity->e.shaderRGBA)[1] / 255.0f;
				outmatrix[14] = ((unsigned char *)backEnd.currentEntity->e.shaderRGBA)[2] / 255.0f;
				outmatrix[15] = ((unsigned char *)backEnd.currentEntity->e.shaderRGBA)[3] / 255.0f;
			}
			else // FIXME: does original quake3 black out vertex colors like this?
			{
				outmatrix[12] = 0.0f;
				outmatrix[13] = 0.0f;
				outmatrix[14] = 0.0f;
				outmatrix[15] = 0.0f;
			}
			break;
		case CGEN_ONE_MINUS_ENTITY:
			*disableVertexColors = qtrue;
			if (backEnd.currentEntity)
			{
				outmatrix[12] = 1.0f - ((unsigned char *)backEnd.currentEntity->e.shaderRGBA)[0] / 255.0f;
				outmatrix[13] = 1.0f - ((unsigned char *)backEnd.currentEntity->e.shaderRGBA)[1] / 255.0f;
				outmatrix[14] = 1.0f - ((unsigned char *)backEnd.currentEntity->e.shaderRGBA)[2] / 255.0f;
				outmatrix[15] = 1.0f - ((unsigned char *)backEnd.currentEntity->e.shaderRGBA)[3] / 255.0f;
			}
			else // FIXME: does original quake3 black out vertex colors like this?
			{
				outmatrix[12] = 0.0f;
				outmatrix[13] = 0.0f;
				outmatrix[14] = 0.0f;
				outmatrix[15] = 0.0f;
			}
			break;
	}

	//
	// alphaGen
	//
	switch ( pStage->alphaGen )
	{
	case AGEN_SKIP:
		break;
	case AGEN_IDENTITY:
		if ( pStage->rgbGen != CGEN_IDENTITY ) {
			if ( ( pStage->rgbGen == CGEN_VERTEX && tr.identityLight != 1 ) ||
				 pStage->rgbGen != CGEN_VERTEX ) {
				// FIXME: Not a perfect fit, if alpha is less than 1.0f and vertex colors are enabled then this doesn't work
				outmatrix[15] = 1.0f;
#if 0
				for ( i = 0; i < tess.numVertexes; i++ ) {
					tess.svars.colors[i][3] = 0xff;
				}
#endif
			}
		}
		break;
	case AGEN_CONST:
		if ( pStage->rgbGen != CGEN_CONST ) {
			// FIXME: Not a perfect fit, if alpha is less than 1.0f and vertex colors are enabled then this doesn't work
#if 0
			for ( i = 0; i < tess.numVertexes; i++ ) {
				tess.svars.colors[i][3] = pStage->constantColor[3];
			}
#endif
			outmatrix[15] = pStage->constantColor[3] / 255.0f;
		}
		break;
	case AGEN_WAVEFORM:
		// From RB_CalcWaveAlpha
		// FIXME: Not a perfect fit, if alpha is less than 1.0f and vertex colors are enabled then this doesn't work
		{
			float glow;
			waveForm_t *wf = &pStage->alphaWave;
			glow = EvalWaveFormClamped( wf );
			outmatrix[15] = glow;
		}
		break;
	case AGEN_LIGHTING_SPECULAR:
		// FIXME: Can't do this with just a matrix
		// RB_CalcSpecularAlpha( ( unsigned char * ) tess.svars.colors );
		break;
	case AGEN_ENTITY:
		// FIXME: Doesn't work if alpha is less than 1.0f and vertex colors are enabled
		//RB_CalcAlphaFromEntity( ( unsigned char * ) tess.svars.colors );
		if (backEnd.currentEntity)
		{
			outmatrix[15] = ((unsigned char *)backEnd.currentEntity->e.shaderRGBA)[3] / 255.0f;
		}
		break;
	case AGEN_ONE_MINUS_ENTITY:
		// FIXME: Doesn't work if alpha is less than 1.0f and vertex colors are enabled
		//RB_CalcAlphaFromOneMinusEntity( ( unsigned char * ) tess.svars.colors );
		if (backEnd.currentEntity)
		{
			outmatrix[15] = 1.0f - ((unsigned char *)backEnd.currentEntity->e.shaderRGBA)[3] / 255.0f;
		}
		break;
    case AGEN_VERTEX:
		// FIXME: Doesn't work if vertex colors are disabled
#if 0
		if ( pStage->rgbGen != CGEN_VERTEX ) {
			for ( i = 0; i < tess.numVertexes; i++ ) {
				tess.svars.colors[i][3] = tess.vertexColors[i][3];
			}
		}
#endif
		outmatrix[15] = 1.0f;
        break;
    case AGEN_ONE_MINUS_VERTEX:
		// FIXME: Doesn't work at all
		outmatrix[15] = 1.0f;
#if 0
        for ( i = 0; i < tess.numVertexes; i++ )
        {
			tess.svars.colors[i][3] = 255 - tess.vertexColors[i][3];
        }
#endif
        break;
	case AGEN_PORTAL:
		// FIXME: This very doesn't work.
#if 0
		{
			unsigned char alpha;

			for ( i = 0; i < tess.numVertexes; i++ )
			{
				float len;
				vec3_t v;

				VectorSubtract( tess.xyz[i], backEnd.viewParms.or.origin, v );
				len = VectorLength( v );

				len /= tess.shader->portalRange;

				if ( len < 0 )
				{
					alpha = 0;
				}
				else if ( len > 1 )
				{
					alpha = 0xff;
				}
				else
				{
					alpha = len * 0xff;
				}

				tess.svars.colors[i][3] = alpha;
			}
		}
#endif
		break;
	}

	// FIXME: find some way to implement this stuff.
#if 0
	//
	// fog adjustment for colors to fade out as fog increases
	//
	if ( tess.fogNum )
	{
		switch ( pStage->adjustColorsForFog )
		{
		case ACFF_MODULATE_RGB:
			RB_CalcModulateColorsByFog( ( unsigned char * ) tess.svars.colors );
			break;
		case ACFF_MODULATE_ALPHA:
			RB_CalcModulateAlphasByFog( ( unsigned char * ) tess.svars.colors );
			break;
		case ACFF_MODULATE_RGBA:
			RB_CalcModulateRGBAsByFog( ( unsigned char * ) tess.svars.colors );
			break;
		case ACFF_NONE:
			break;
		}
	}
	
	// if in greyscale rendering mode turn all color values into greyscale.
	if(r_greyscale->integer)
	{
		int scale;
		
		for(i = 0; i < tess.numVertexes; i++)
		{
			scale = (tess.svars.colors[i][0] + tess.svars.colors[i][1] + tess.svars.colors[i][2]) / 3;
			tess.svars.colors[i][0] = tess.svars.colors[i][1] = tess.svars.colors[i][2] = scale;
		}
	}
#endif
}


/*
===============
ComputeTexCoords
===============
*/
static void ComputeTexCoords( shaderStage_t *pStage ) {
	int		i;
	int		b;

	for ( b = 0; b < NUM_TEXTURE_BUNDLES; b++ ) {
		int tm;

		//
		// generate the texture coordinates
		//
		switch ( pStage->bundle[b].tcGen )
		{
		case TCGEN_IDENTITY:
			Com_Memset( tess.svars.texcoords[b], 0, sizeof( float ) * 2 * tess.numVertexes );
			break;
		case TCGEN_TEXTURE:
			for ( i = 0 ; i < tess.numVertexes ; i++ ) {
				tess.svars.texcoords[b][i][0] = tess.texCoords[i][0][0];
				tess.svars.texcoords[b][i][1] = tess.texCoords[i][0][1];
			}
			break;
		case TCGEN_LIGHTMAP:
			for ( i = 0 ; i < tess.numVertexes ; i++ ) {
				tess.svars.texcoords[b][i][0] = tess.texCoords[i][1][0];
				tess.svars.texcoords[b][i][1] = tess.texCoords[i][1][1];
			}
			break;
		case TCGEN_VECTOR:
			for ( i = 0 ; i < tess.numVertexes ; i++ ) {
				tess.svars.texcoords[b][i][0] = DotProduct( tess.xyz[i], pStage->bundle[b].tcGenVectors[0] );
				tess.svars.texcoords[b][i][1] = DotProduct( tess.xyz[i], pStage->bundle[b].tcGenVectors[1] );
			}
			break;
		case TCGEN_FOG:
			RB_CalcFogTexCoords( ( float * ) tess.svars.texcoords[b] );
			break;
		case TCGEN_ENVIRONMENT_MAPPED:
			RB_CalcEnvironmentTexCoords( ( float * ) tess.svars.texcoords[b] );
			break;
		case TCGEN_BAD:
			return;
		default:
			break;
		}

		//
		// alter texture coordinates
		//
		for ( tm = 0; tm < pStage->bundle[b].numTexMods ; tm++ ) {
			switch ( pStage->bundle[b].texMods[tm].type )
			{
			case TMOD_NONE:
				tm = TR_MAX_TEXMODS;		// break out of for loop
				break;

			case TMOD_TURBULENT:
				RB_CalcTurbulentTexCoords( &pStage->bundle[b].texMods[tm].wave, 
						                 ( float * ) tess.svars.texcoords[b] );
				break;

			case TMOD_ENTITY_TRANSLATE:
				RB_CalcScrollTexCoords( backEnd.currentEntity->e.shaderTexCoord,
									 ( float * ) tess.svars.texcoords[b] );
				break;

			case TMOD_SCROLL:
				RB_CalcScrollTexCoords( pStage->bundle[b].texMods[tm].scroll,
										 ( float * ) tess.svars.texcoords[b] );
				break;

			case TMOD_SCALE:
				RB_CalcScaleTexCoords( pStage->bundle[b].texMods[tm].scale,
									 ( float * ) tess.svars.texcoords[b] );
				break;
			
			case TMOD_STRETCH:
				RB_CalcStretchTexCoords( &pStage->bundle[b].texMods[tm].wave, 
						               ( float * ) tess.svars.texcoords[b] );
				break;

			case TMOD_TRANSFORM:
				RB_CalcTransformTexCoords( &pStage->bundle[b].texMods[tm],
						                 ( float * ) tess.svars.texcoords[b] );
				break;

			case TMOD_ROTATE:
				RB_CalcRotateTexCoords( pStage->bundle[b].texMods[tm].rotateSpeed,
										( float * ) tess.svars.texcoords[b] );
				break;

			default:
				ri.Error( ERR_DROP, "ERROR: unknown texmod '%d' in shader '%s'\n", pStage->bundle[b].texMods[tm].type, tess.shader->name );
				break;
			}
		}
	}
}

/*
** RB_IterateStagesGeneric
*/
static void RB_IterateStagesGeneric( shaderCommands_t *input )
{
	int stage;

	for ( stage = 0; stage < MAX_SHADER_STAGES; stage++ )
	{
		shaderStage_t *pStage = tess.xstages[stage];

		if ( !pStage )
		{
			break;
		}

		ComputeColors( pStage );
		ComputeTexCoords( pStage );

		if ( !setArraysOnce )
		{
			qglEnableClientState( GL_COLOR_ARRAY );
			qglColorPointer( 4, GL_UNSIGNED_BYTE, 0, input->svars.colors );
		}

		//
		// do multitexture
		//
		if ( pStage->bundle[1].image[0] != 0 )
		{
			DrawMultitextured( input, stage );
		}
		else
		{
			if ( !setArraysOnce )
			{
				qglTexCoordPointer( 2, GL_FLOAT, 0, input->svars.texcoords[0] );
			}

			//
			// set state
			//
			if ( pStage->bundle[0].vertexLightmap && ( (r_vertexLight->integer && !r_uiFullScreen->integer) || glConfig.hardwareType == GLHW_PERMEDIA2 ) && r_lightmap->integer )
			{
				GL_Bind( tr.whiteImage );
			}
			else 
				R_BindAnimatedImage( &pStage->bundle[0] );

			GL_State( pStage->stateBits );

			//
			// draw
			//
			R_DrawElements( input->numIndexes, input->indexes );
		}
		// allow skipping out to show just lightmaps during development
		if ( r_lightmap->integer && ( pStage->bundle[0].isLightmap || pStage->bundle[1].isLightmap || pStage->bundle[0].vertexLightmap ) )
		{
			break;
		}
	}
}


/*
** RB_IterateStagesGenericVBO
*/
static void RB_IterateStagesGenericVBO( shaderCommands_t *input )
{
	int stage;

	qglEnableClientState( GL_VERTEX_ARRAY );
	qglVertexPointer(3, GL_FLOAT, glState.currentVBO->stride_xyz, BUFFER_OFFSET(glState.currentVBO->ofs_xyz));
	qglEnableClientState( GL_NORMAL_ARRAY );
	qglNormalPointer(GL_FLOAT, glState.currentVBO->stride_normal, BUFFER_OFFSET(glState.currentVBO->ofs_normal));

	for ( stage = 0; stage < MAX_SHADER_STAGES; stage++ )
	{
		shaderStage_t *pStage = tess.xstages[stage];
		qboolean disableVertexColors = qfalse;
		float matrix[16];

		if ( !pStage )
		{
			break;
		}

		ComputeColorMatrix( pStage, matrix, &disableVertexColors);

		if (!disableVertexColors)
		{
			qglMatrixMode(GL_COLOR);
			qglLoadMatrixf(matrix);
		}
		else
		{
			qglColor4fv(&matrix[12]);
		}

		qglMatrixMode(GL_MODELVIEW);

		if (!disableVertexColors)
		{
			qglEnableClientState( GL_COLOR_ARRAY );
			qglColorPointer(4, GL_UNSIGNED_BYTE, glState.currentVBO->stride_vertexcolor, BUFFER_OFFSET(glState.currentVBO->ofs_vertexcolor));
		}
		else
		{
			qglDisableClientState( GL_COLOR_ARRAY );
		}

		//
		// do multitexture
		//
		if ( pStage->bundle[1].image[0] != 0 )
		{
			DrawMultitexturedVBO( input, stage );
		}
		else
		{
			float matrix[16];

			GenerateGLTexCoords( pStage, 0 );
				
			ComputeTexMatrix( pStage, 0, matrix );
			qglMatrixMode(GL_TEXTURE);
			qglLoadMatrixf(matrix);
			qglMatrixMode(GL_MODELVIEW);

			//
			// set state
			//
			if ( pStage->bundle[0].vertexLightmap && ( (r_vertexLight->integer && !r_uiFullScreen->integer) || glConfig.hardwareType == GLHW_PERMEDIA2 ) && r_lightmap->integer )
			{
				GL_Bind( tr.whiteImage );
			}
			else 
				R_BindAnimatedImage( &pStage->bundle[0] );

			GL_State( pStage->stateBits );

			//
			// draw
			//

			if (input->multiDrawPrimitives)
			{
				R_DrawMultiElementsVBO(input->multiDrawPrimitives, (const GLvoid **)input->multiDrawFirstIndex, input->multiDrawNumIndexes);
			}
			else
			{
				R_DrawElementsVBO(input->numIndexes, input->firstIndex);
			}

			UndoGLTexCoords( pStage, 0 );
			qglEnableClientState ( GL_COLOR_ARRAY );
			qglMatrixMode(GL_COLOR);
			qglLoadIdentity();
			qglMatrixMode(GL_TEXTURE);
			qglLoadIdentity();
			qglMatrixMode(GL_MODELVIEW);

		}
		// allow skipping out to show just lightmaps during development
		if ( r_lightmap->integer && ( pStage->bundle[0].isLightmap || pStage->bundle[1].isLightmap || pStage->bundle[0].vertexLightmap ) )
		{
			break;
		}
	}
}


static void DrawMultitexturedVBOGLSL( shaderProgram_t *sp, shaderCommands_t *input, int stage ) {
	shaderStage_t	*pStage;
	matrix_t matrix;
	vec4_t vector;

	pStage = tess.xstages[stage];

	//
	// base
	//
	GLSL_SetUniformInt(sp, GENERIC_UNIFORM_TCGEN0, pStage->bundle[0].tcGen);
	if (pStage->bundle[0].tcGen == TCGEN_VECTOR)
	{
		vector[3] = 0.0f;
		VectorCopy(pStage->bundle[0].tcGenVectors[0], vector);
		GLSL_SetUniformVec4(sp, GENERIC_UNIFORM_TCGEN0VECTOR0, vector);
		VectorCopy(pStage->bundle[0].tcGenVectors[1], vector);
		GLSL_SetUniformVec4(sp, GENERIC_UNIFORM_TCGEN0VECTOR1, vector);
	}

	ComputeTexMatrix( pStage, 0, matrix );
	GLSL_SetUniformMatrix16(sp, GENERIC_UNIFORM_TEXTURE0MATRIX, matrix);
	
	R_BindAnimatedImageToTMU( &pStage->bundle[0], 0 );

	//
	// lightmap/secondary pass
	//
	if ( r_lightmap->integer ) {
		GLSL_SetUniformInt(sp, GENERIC_UNIFORM_TEXTURE1ENV, GL_REPLACE);
	} else {
		GLSL_SetUniformInt(sp, GENERIC_UNIFORM_TEXTURE1ENV, tess.shader->multitextureEnv);
	}

	R_BindAnimatedImageToTMU( &pStage->bundle[1], 1 );

	if (input->multiDrawPrimitives)
	{
		R_DrawMultiElementsVBO(input->multiDrawPrimitives, (const GLvoid **)input->multiDrawFirstIndex, input->multiDrawNumIndexes);
	}
	else
	{
		R_DrawElementsVBO(input->numIndexes, input->firstIndex);
	}
}

static unsigned int RB_CalcShaderVertexAttribs( shaderCommands_t *input )
{
	unsigned int vertexAttribs = input->shader->vertexAttribs;

	if(glState.vertexAttribsInterpolation > 0.0f)
	{
		vertexAttribs |= ATTR_POSITION2;
		if (vertexAttribs & ATTR_NORMAL)
		{
			vertexAttribs |= ATTR_NORMAL2;
		}
	}

	return vertexAttribs;
}


static void RB_IterateStagesGenericVBOGLSL( shaderCommands_t *input )
{
	int stage;
	matrix_t matrix;
	shaderProgram_t *sp = GLSL_GetGenericShaderProgram();

	GLSL_BindProgram(sp);

	GLSL_SetUniformMatrix16(sp, GENERIC_UNIFORM_MODELVIEWPROJECTIONMATRIX, glState.modelviewProjection);
	GLSL_SetUniformVec3(sp, GENERIC_UNIFORM_VIEWORIGIN, backEnd.or.viewOrigin);

	GLSL_SetUniformFloat(sp, GENERIC_UNIFORM_VERTEXLERP, glState.vertexAttribsInterpolation);
	
	// u_DeformGen
	if(!ShaderRequiresCPUDeforms(input->shader))
	{
		deformStage_t  *ds;

		// only support the first one
		ds = &input->shader->deforms[0];

		switch (ds->deformation)
		{
			case DEFORM_WAVE:
				GLSL_SetUniformInt(sp, GENERIC_UNIFORM_DEFORMGEN, ds->deformationWave.func);
				{
					vec4_t v;
					waveForm_t *wf = &ds->deformationWave;

					VectorSet4(v, wf->base, wf->amplitude, wf->phase, wf->frequency);

					GLSL_SetUniformVec4(sp, GENERIC_UNIFORM_DEFORMWAVE, v);
				}
				GLSL_SetUniformFloat(sp, GENERIC_UNIFORM_DEFORMSPREAD, ds->deformationSpread);
				GLSL_SetUniformFloat(sp, GENERIC_UNIFORM_TIME, tess.shaderTime);
				break;

			case DEFORM_BULGE:
				GLSL_SetUniformInt(sp, GENERIC_UNIFORM_DEFORMGEN, DGEN_BULGE);
				{
					vec3_t v;

					VectorSet(v, ds->bulgeWidth, ds->bulgeHeight, ds->bulgeSpeed);

					GLSL_SetUniformVec3(sp, GENERIC_UNIFORM_DEFORMBULGE, v);
				}
				GLSL_SetUniformFloat(sp, GENERIC_UNIFORM_TIME, tess.shaderTime);
				break;

			default:
				GLSL_SetUniformInt(sp, GENERIC_UNIFORM_DEFORMGEN, DGEN_NONE);
				break;
		}
	}
	else
	{
		GLSL_SetUniformInt(sp, GENERIC_UNIFORM_DEFORMGEN, DGEN_NONE);
	}

	if ( input->fogNum ) {
		fog_t		*fog;
		vec3_t	local;
		vec4_t	fogDistanceVector, fogDepthVector = {0, 0, 0, 0};
		float		eyeT;

		fog = tr.world->fogs + tess.fogNum;

		VectorSubtract( backEnd.or.origin, backEnd.viewParms.or.origin, local );
		fogDistanceVector[0] = -backEnd.or.modelMatrix[2];
		fogDistanceVector[1] = -backEnd.or.modelMatrix[6];
		fogDistanceVector[2] = -backEnd.or.modelMatrix[10];
		fogDistanceVector[3] = DotProduct( local, backEnd.viewParms.or.axis[0] );

		// scale the fog vectors based on the fog's thickness
		VectorScale4(fogDistanceVector, fog->tcScale, fogDistanceVector);

		// rotate the gradient vector for this orientation
		if ( fog->hasSurface ) {
			fogDepthVector[0] = fog->surface[0] * backEnd.or.axis[0][0] + 
				fog->surface[1] * backEnd.or.axis[0][1] + fog->surface[2] * backEnd.or.axis[0][2];
			fogDepthVector[1] = fog->surface[0] * backEnd.or.axis[1][0] + 
				fog->surface[1] * backEnd.or.axis[1][1] + fog->surface[2] * backEnd.or.axis[1][2];
			fogDepthVector[2] = fog->surface[0] * backEnd.or.axis[2][0] + 
				fog->surface[1] * backEnd.or.axis[2][1] + fog->surface[2] * backEnd.or.axis[2][2];
			fogDepthVector[3] = -fog->surface[3] + DotProduct( backEnd.or.origin, fog->surface );

			eyeT = DotProduct( backEnd.or.viewOrigin, fogDepthVector ) + fogDepthVector[3];
		} else {
			eyeT = 1;	// non-surface fog always has eye inside
		}

		GLSL_SetUniformVec4(sp, GENERIC_UNIFORM_FOGDISTANCE, fogDistanceVector);
		GLSL_SetUniformVec4(sp, GENERIC_UNIFORM_FOGDEPTH, fogDepthVector);
		GLSL_SetUniformFloat(sp, GENERIC_UNIFORM_FOGEYET, eyeT);
	}

	for ( stage = 0; stage < MAX_SHADER_STAGES; stage++ )
	{
		shaderStage_t *pStage = input->xstages[stage];
		qboolean setcolor = qfalse;

		if ( !pStage )
		{
			break;
		}

		GL_State( pStage->stateBits );

		switch (pStage->rgbGen)
		{
			case CGEN_IDENTITY:
			case CGEN_EXACT_VERTEX:
			case CGEN_LIGHTING_DIFFUSE:
				break;
			default:
				setcolor = qtrue;
		}

		switch (pStage->alphaGen)
		{
			case AGEN_IDENTITY:
			case AGEN_LIGHTING_SPECULAR:
			case AGEN_VERTEX:
			case AGEN_ONE_MINUS_VERTEX:
			case AGEN_PORTAL:
				break;
			default:
				setcolor = qtrue;
		}

		if (setcolor)
		{
			vec4_t color;

			VectorSet4(color, 1.0f, 1.0f, 1.0f, 1.0f);

			ComputeHelperColor (pStage, color);
			GLSL_SetUniformVec4(sp, GENERIC_UNIFORM_COLOR, color);
		}

		if (pStage->rgbGen == CGEN_LIGHTING_DIFFUSE)
		{
			vec3_t vec;

			VectorScale(backEnd.currentEntity->ambientLight, 1.0f / 255.0f, vec);
			GLSL_SetUniformVec3(sp, GENERIC_UNIFORM_AMBIENTLIGHT, vec);

			VectorScale(backEnd.currentEntity->directedLight, 1.0f / 255.0f, vec);
			GLSL_SetUniformVec3(sp, GENERIC_UNIFORM_DIRECTEDLIGHT, vec);
			
			GLSL_SetUniformVec3(sp, GENERIC_UNIFORM_LIGHTDIR, backEnd.currentEntity->lightDir);
		}

		if (pStage->alphaGen == AGEN_PORTAL)
		{
			GLSL_SetUniformFloat(sp, GENERIC_UNIFORM_PORTALRANGE, tess.shader->portalRange);
		}

		GLSL_SetUniformInt(sp, GENERIC_UNIFORM_COLORGEN, pStage->rgbGen);
		GLSL_SetUniformInt(sp, GENERIC_UNIFORM_ALPHAGEN, pStage->alphaGen);

		if ( input->fogNum )
		{
			GLSL_SetUniformInt(sp, GENERIC_UNIFORM_FOGADJUSTCOLORS, pStage->adjustColorsForFog);
		}
		else
		{
			GLSL_SetUniformInt(sp, GENERIC_UNIFORM_FOGADJUSTCOLORS, 0);
		}

		//
		// do multitexture
		//
		if ( pStage->bundle[1].image[0] != 0 )
		{
			DrawMultitexturedVBOGLSL( sp, input, stage );
		}
		else 
		{
			GLSL_SetUniformInt(sp, GENERIC_UNIFORM_TCGEN0, pStage->bundle[0].tcGen);
			if (pStage->bundle[0].tcGen == TCGEN_VECTOR)
			{
				vec4_t vector;

				VectorCopy(pStage->bundle[0].tcGenVectors[0], vector);
				vector[3] = 0.0f;
				GLSL_SetUniformVec4(sp, GENERIC_UNIFORM_TCGEN0VECTOR0, vector);
				VectorCopy(pStage->bundle[0].tcGenVectors[1], vector);
				GLSL_SetUniformVec4(sp, GENERIC_UNIFORM_TCGEN0VECTOR1, vector);
			}

			ComputeTexMatrix( pStage, 0, matrix );
			GLSL_SetUniformMatrix16(sp, GENERIC_UNIFORM_TEXTURE0MATRIX, matrix);

			//
			// set state
			//
			if ( pStage->bundle[0].vertexLightmap && ( (r_vertexLight->integer && !r_uiFullScreen->integer) || glConfig.hardwareType == GLHW_PERMEDIA2 ) && r_lightmap->integer )
			{
				GL_Bind( tr.whiteImage );
			}
			else 
				R_BindAnimatedImage( &pStage->bundle[0] );

			GLSL_SetUniformInt(sp, GENERIC_UNIFORM_TEXTURE1ENV, 0);

			//
			// draw
			//

			if (input->multiDrawPrimitives)
			{
				R_DrawMultiElementsVBO(input->multiDrawPrimitives, (const GLvoid **)input->multiDrawFirstIndex, input->multiDrawNumIndexes);
			}
			else
			{
				R_DrawElementsVBO(input->numIndexes, input->firstIndex);
			}
		}
	
		// allow skipping out to show just lightmaps during development
		if ( r_lightmap->integer && ( pStage->bundle[0].isLightmap || pStage->bundle[1].isLightmap || pStage->bundle[0].vertexLightmap ) )
		{
			break;
		}
	}
}


/*
** RB_StageIteratorGeneric
*/
void RB_StageIteratorGeneric( void )
{
	shaderCommands_t *input;

	input = &tess;
	
	if (!input->numVertexes || !input->numIndexes)
	{
		return;
	}

	RB_DeformTessGeometry();

	//
	// log this call
	//
	if ( r_logFile->integer ) 
	{
		// don't just call LogComment, or we will get
		// a call to va() every frame!
		GLimp_LogComment( va("--- RB_StageIteratorGeneric( %s ) ---\n", tess.shader->name) );
	}

	//
	// set face culling appropriately
	//
	GL_Cull( input->shader->cullType );

	// set polygon offset if necessary
	if ( input->shader->polygonOffset )
	{
		qglEnable( GL_POLYGON_OFFSET_FILL );
		qglPolygonOffset( r_offsetFactor->value, r_offsetUnits->value );
	}

	//
	// if there is only a single pass then we can enable color
	// and texture arrays before we compile, otherwise we need
	// to avoid compiling those arrays since they will change
	// during multipass rendering
	//
	if ( tess.numPasses > 1 || input->shader->multitextureEnv )
	{
		setArraysOnce = qfalse;
		qglDisableClientState (GL_COLOR_ARRAY);
		qglDisableClientState (GL_TEXTURE_COORD_ARRAY);
	}
	else
	{
		setArraysOnce = qtrue;

		qglEnableClientState( GL_COLOR_ARRAY);
		qglColorPointer( 4, GL_UNSIGNED_BYTE, 0, tess.svars.colors );

		qglEnableClientState( GL_TEXTURE_COORD_ARRAY);
		qglTexCoordPointer( 2, GL_FLOAT, 0, tess.svars.texcoords[0] );
	}

	//
	// lock XYZ
	//
	qglVertexPointer (3, GL_FLOAT, 16, input->xyz);	// padded for SIMD
	if (qglLockArraysEXT)
	{
		qglLockArraysEXT(0, input->numVertexes);
		GLimp_LogComment( "glLockArraysEXT\n" );
	}

	//
	// enable color and texcoord arrays after the lock if necessary
	//
	if ( !setArraysOnce )
	{
		qglEnableClientState( GL_TEXTURE_COORD_ARRAY );
		qglEnableClientState( GL_COLOR_ARRAY );
	}

	//
	// call shader function
	//
	RB_IterateStagesGeneric( input );

	// 
	// now do any dynamic lighting needed
	//
	if ( tess.dlightBits && tess.shader->sort <= SS_OPAQUE
		&& !(tess.shader->surfaceFlags & (SURF_NODLIGHT | SURF_SKY) ) ) {
		ProjectDlightTexture();
	}

	//
	// now do fog
	//
	if ( tess.fogNum && tess.shader->fogPass ) {
		RB_FogPass();
	}

	// 
	// unlock arrays
	//
	if (qglUnlockArraysEXT) 
	{
		qglUnlockArraysEXT();
		GLimp_LogComment( "glUnlockArraysEXT\n" );
	}

	//
	// reset polygon offset
	//
	if ( input->shader->polygonOffset )
	{
		qglDisable( GL_POLYGON_OFFSET_FILL );
	}
}


/*
** RB_StageIteratorGenericVBO
*/
void RB_StageIteratorGenericVBO( void )
{
	shaderCommands_t *input;
	unsigned int vertexAttribs = 0;

	input = &tess;
	
	if (!input->numVertexes || !input->numIndexes)
	{
		return;
	}

	backEnd.pc.c_genericDraws++;

	if (tess.useInternalVBO)
	{
		RB_DeformTessGeometry();
	}

	vertexAttribs = RB_CalcShaderVertexAttribs( input );

	if (tess.useInternalVBO)
	{
		RB_UpdateVBOs(vertexAttribs);
	}
	else
	{
		backEnd.pc.c_staticVboDraws++;
	}

	//
	// log this call
	//
	if ( r_logFile->integer ) 
	{
		// don't just call LogComment, or we will get
		// a call to va() every frame!
		GLimp_LogComment( va("--- RB_StageIteratorGenericVBO( %s ) ---\n", tess.shader->name) );
	}

	//
	// set face culling appropriately
	//
	GL_Cull( input->shader->cullType );

	// set polygon offset if necessary
	if ( input->shader->polygonOffset )
	{
		qglEnable( GL_POLYGON_OFFSET_FILL );
		qglPolygonOffset( r_offsetFactor->value, r_offsetUnits->value );
	}

	//
	// Set vertex attribs and pointers
	//
	if (glRefConfig.glsl && r_arb_shader_objects->integer)
	{
		GLSL_VertexAttribsState(vertexAttribs);
	}


	//
	// call shader function
	//
	if (glRefConfig.glsl && r_arb_shader_objects->integer)
	{
		RB_IterateStagesGenericVBOGLSL( input );
	}
	else
	{
		RB_IterateStagesGenericVBO( input );
	}

	// 
	// now do any dynamic lighting needed
	//
	if ( tess.dlightBits && tess.shader->sort <= SS_OPAQUE
		&& !(tess.shader->surfaceFlags & (SURF_NODLIGHT | SURF_SKY) ) ) {
		if (glRefConfig.glsl && r_arb_shader_objects->integer)
		{
			ProjectDlightTextureVBOGLSL();
		}
		else
		{
			// FIXME
		}
	}

	//
	// now do fog
	//
	if ( tess.fogNum && tess.shader->fogPass ) {
		if (glRefConfig.glsl && r_arb_shader_objects->integer)
		{
			RB_FogPassVBOGLSL();
		}
		else
		{
			// FIXME: figure out a way to do fog without GLSL
		}
	}

	//
	// reset polygon offset
	//
	if ( input->shader->polygonOffset )
	{
		qglDisable( GL_POLYGON_OFFSET_FILL );
	}
}


/*
** RB_StageIteratorVertexLitTexture
*/
void RB_StageIteratorVertexLitTexture( void )
{
	shaderCommands_t *input;
	shader_t		*shader;

	if(glRefConfig.vertexBufferObject && r_arb_vertex_buffer_object->integer)
	{
		//R_BindNullVBO();
		//R_BindNullIBO();
		return;
	}

	input = &tess;

	shader = input->shader;

	//
	// compute colors
	//
	RB_CalcDiffuseColor( ( unsigned char * ) tess.svars.colors );

	//
	// log this call
	//
	if ( r_logFile->integer ) 
	{
		// don't just call LogComment, or we will get
		// a call to va() every frame!
		GLimp_LogComment( va("--- RB_StageIteratorVertexLitTexturedUnfogged( %s ) ---\n", tess.shader->name) );
	}

	//
	// set face culling appropriately
	//
	GL_Cull( input->shader->cullType );

	//
	// set arrays and lock
	//
	qglEnableClientState( GL_COLOR_ARRAY);
	qglEnableClientState( GL_TEXTURE_COORD_ARRAY);

	qglColorPointer( 4, GL_UNSIGNED_BYTE, 0, tess.svars.colors );
	qglTexCoordPointer( 2, GL_FLOAT, 16, tess.texCoords[0][0] );
	qglVertexPointer (3, GL_FLOAT, 16, input->xyz);

	if ( qglLockArraysEXT )
	{
		qglLockArraysEXT(0, input->numVertexes);
		GLimp_LogComment( "glLockArraysEXT\n" );
	}

	//
	// call special shade routine
	//
	R_BindAnimatedImage( &tess.xstages[0]->bundle[0] );
	GL_State( tess.xstages[0]->stateBits );
	R_DrawElements( input->numIndexes, input->indexes );

	// 
	// now do any dynamic lighting needed
	//
	if ( tess.dlightBits && tess.shader->sort <= SS_OPAQUE ) {
		ProjectDlightTexture();
	}

	//
	// now do fog
	//
	if ( tess.fogNum && tess.shader->fogPass ) {
		RB_FogPass();
	}

	// 
	// unlock arrays
	//
	if (qglUnlockArraysEXT) 
	{
		qglUnlockArraysEXT();
		GLimp_LogComment( "glUnlockArraysEXT\n" );
	}
}

//define	REPLACE_MODE

void RB_StageIteratorLightmappedMultitextureVBOGLSL( void )
{
	shaderCommands_t *input;
	unsigned int vertexAttribs = 0;
	shaderProgram_t *sp;
	shaderStage_t *pStage;
	matrix_t matrix;

	input = &tess;
	
	if (!input->numVertexes || !input->numIndexes)
	{
		return;
	}

	backEnd.pc.c_lightmappedDraws++;

	vertexAttribs = ATTR_POSITION | ATTR_TEXCOORD | ATTR_LIGHTCOORD; //RB_CalcShaderVertexAttribs( input );

	if (tess.useInternalVBO)
	{
		RB_UpdateVBOs(vertexAttribs);
	}
	else
	{
		backEnd.pc.c_staticVboDraws++;
	}

	//
	// log this call
	//
	if ( r_logFile->integer ) 
	{
		// don't just call LogComment, or we will get
		// a call to va() every frame!
		GLimp_LogComment( va("--- RB_StageIteratorLightmappedMultitextureVBOGLSL( %s ) ---\n", tess.shader->name) );
	}

	//
	// set face culling appropriately
	//
	GL_Cull( input->shader->cullType );

	//
	// Set vertex attribs and pointers
	//
	if (glRefConfig.glsl && r_arb_shader_objects->integer)
	{
		GLSL_VertexAttribsState(vertexAttribs);
	}

	//
	// Bind lightmapped shader
	//
	sp = &tr.lightmappedShader;
	GLSL_BindProgram(sp);
	GLSL_SetUniformMatrix16(sp, LIGHTMAPPED_UNIFORM_MODELVIEWPROJECTIONMATRIX, glState.modelviewProjection);

	pStage = input->xstages[0];
	GL_State( pStage->stateBits );

	//
	// base
	//
	ComputeTexMatrix( pStage, 0, matrix );
	GLSL_SetUniformMatrix16(sp, LIGHTMAPPED_UNIFORM_TEXTURE0MATRIX, matrix);
	
	R_BindAnimatedImageToTMU( &pStage->bundle[0], 0 );

	//
	// lightmap/secondary pass
	//
#if 0
	if ( r_lightmap->integer ) {
		GLSL_SetUniformInt(sp, LIGHTMAPPED_UNIFORM_TEXTURE1ENV, GL_REPLACE);
	} else {
		GLSL_SetUniformInt(sp, LIGHTMAPPED_UNIFORM_TEXTURE1ENV, tess.shader->multitextureEnv);
	}
#endif

	R_BindAnimatedImageToTMU( &pStage->bundle[1], 1 );

	//
	// draw
	//
	if (input->multiDrawPrimitives)
	{
		R_DrawMultiElementsVBO(input->multiDrawPrimitives, (const GLvoid **)input->multiDrawFirstIndex, input->multiDrawNumIndexes);
	}
	else
	{
		R_DrawElementsVBO(input->numIndexes, input->firstIndex);
	}

	// 
	// now do any dynamic lighting needed
	//
	if ( tess.dlightBits && tess.shader->sort <= SS_OPAQUE
		&& !(tess.shader->surfaceFlags & (SURF_NODLIGHT | SURF_SKY) ) ) {
		ProjectDlightTextureVBOGLSL();
	}

	//
	// now do fog
	//
	if ( tess.fogNum && tess.shader->fogPass ) {
		RB_FogPassVBOGLSL();
	}
}

void RB_StageIteratorLightmappedMultitexture( void ) {
	shaderCommands_t *input;

	if(glRefConfig.vertexBufferObject && r_arb_vertex_buffer_object->integer)
	{
		//R_BindNullVBO();
		//R_BindNullIBO();
		return;
	}

	input = &tess;

	//
	// log this call
	//
	if ( r_logFile->integer ) {
		// don't just call LogComment, or we will get
		// a call to va() every frame!
		GLimp_LogComment( va("--- RB_StageIteratorLightmappedMultitexture( %s ) ---\n", tess.shader->name) );
	}

	//
	// set face culling appropriately
	//
	GL_Cull( input->shader->cullType );

	//
	// set color, pointers, and lock
	//
	GL_State( GLS_DEFAULT );
	qglVertexPointer( 3, GL_FLOAT, 16, input->xyz );

#ifdef REPLACE_MODE
	qglDisableClientState( GL_COLOR_ARRAY );
	qglColor3f( 1, 1, 1 );
	qglShadeModel( GL_FLAT );
#else
	qglEnableClientState( GL_COLOR_ARRAY );
	qglColorPointer( 4, GL_UNSIGNED_BYTE, 0, tess.constantColor255 );
#endif

	//
	// select base stage
	//
	GL_SelectTexture( 0 );

	qglEnableClientState( GL_TEXTURE_COORD_ARRAY );
	R_BindAnimatedImage( &tess.xstages[0]->bundle[0] );
	qglTexCoordPointer( 2, GL_FLOAT, 16, tess.texCoords[0][0] );

	//
	// configure second stage
	//
	GL_SelectTexture( 1 );
	qglEnable( GL_TEXTURE_2D );
	if ( r_lightmap->integer ) {
		GL_TexEnv( GL_REPLACE );
	} else {
		GL_TexEnv( GL_MODULATE );
	}
	R_BindAnimatedImage( &tess.xstages[0]->bundle[1] );
	qglEnableClientState( GL_TEXTURE_COORD_ARRAY );
	qglTexCoordPointer( 2, GL_FLOAT, 16, tess.texCoords[0][1] );

	//
	// lock arrays
	//
	if ( qglLockArraysEXT ) {
		qglLockArraysEXT(0, input->numVertexes);
		GLimp_LogComment( "glLockArraysEXT\n" );
	}

	R_DrawElements( input->numIndexes, input->indexes );

	//
	// disable texturing on TEXTURE1, then select TEXTURE0
	//
	qglDisable( GL_TEXTURE_2D );
	qglDisableClientState( GL_TEXTURE_COORD_ARRAY );

	GL_SelectTexture( 0 );
#ifdef REPLACE_MODE
	GL_TexEnv( GL_MODULATE );
	qglShadeModel( GL_SMOOTH );
#endif

	// 
	// now do any dynamic lighting needed
	//
	if ( tess.dlightBits && tess.shader->sort <= SS_OPAQUE ) {
		ProjectDlightTexture();
	}

	//
	// now do fog
	//
	if ( tess.fogNum && tess.shader->fogPass ) {
		RB_FogPass();
	}

	//
	// unlock arrays
	//
	if ( qglUnlockArraysEXT ) {
		qglUnlockArraysEXT();
		GLimp_LogComment( "glUnlockArraysEXT\n" );
	}
}

/*
** RB_EndSurface
*/
void RB_EndSurface( void ) {
	shaderCommands_t *input;

	input = &tess;

	if (input->numIndexes == 0 || input->numVertexes == 0) {
		return;
	}

	if (input->indexes[SHADER_MAX_INDEXES-1] != 0) {
		ri.Error (ERR_DROP, "RB_EndSurface() - SHADER_MAX_INDEXES hit");
	}	
	if (input->xyz[SHADER_MAX_VERTEXES-1][0] != 0) {
		ri.Error (ERR_DROP, "RB_EndSurface() - SHADER_MAX_VERTEXES hit");
	}

	if ( tess.shader == tr.shadowShader ) {
		RB_ShadowTessEnd();
		return;
	}

	// for debugging of sort order issues, stop rendering after a given sort value
	if ( r_debugSort->integer && r_debugSort->integer < tess.shader->sort ) {
		return;
	}

	//
	// update performance counters
	//
	backEnd.pc.c_shaders++;
	backEnd.pc.c_vertexes += tess.numVertexes;
	backEnd.pc.c_indexes += tess.numIndexes;
	backEnd.pc.c_totalIndexes += tess.numIndexes * tess.numPasses;

	//
	// call off to shader specific tess end function
	//
	tess.currentStageIteratorFunc();

	//
	// draw debugging stuff
	//
	if ( r_showtris->integer ) {
		DrawTris (input);
	}
	if ( r_shownormals->integer ) {
		DrawNormals (input);
	}

	if (glRefConfig.vertexBufferObject)
	{
		//R_BindNullVBO();
		//R_BindNullIBO();
	}

	// clear shader so we can tell we don't have any unclosed surfaces
	tess.numIndexes = 0;
	tess.numVertexes = 0;
	tess.firstIndex = 0;
	tess.multiDrawPrimitives = 0;

	GLimp_LogComment( "----------\n" );
}

