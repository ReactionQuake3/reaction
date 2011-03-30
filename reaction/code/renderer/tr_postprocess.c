#include "tr_local.h"

/* Color functions */

static void GLSL_Color4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	vec4_t clr;
	MAKERGBA(clr, r, g, b, a);
	GLSL_SetUniform_Color(glState.currentProgram, clr);
}

static void qglDefColor4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	qglColor4f(r, g, b, a);
}

/* Quad-drawing functions */

static void tessTexCoord2f(float s, float t)
{
	tess.texCoords[tess.numVertexes][0][0] = s;
	tess.texCoords[tess.numVertexes][0][1] = t;
	tess.texCoords[tess.numVertexes][0][2] = 0;
	tess.texCoords[tess.numVertexes][0][3] = 1;
}

static void tessVertex2f(float x, float y)
{
	tess.xyz[tess.numVertexes][0] = x;
	tess.xyz[tess.numVertexes][1] = y;
	tess.xyz[tess.numVertexes][2] = 0.f;
	tess.xyz[tess.numVertexes][3] = 1.f;
	++tess.numVertexes;
}

static void tessBeginQuads(void)
{
	tess.numIndexes = 0;
	tess.numVertexes = 0;
	tess.firstIndex = 0;
}

static void tessEndQuads(void)
{
	int i;

	for (i=0; i<tess.numVertexes; i+=4)
	{
		tess.indexes[tess.numIndexes++] = i+0;
		tess.indexes[tess.numIndexes++] = i+1;
		tess.indexes[tess.numIndexes++] = i+2;
		tess.indexes[tess.numIndexes++] = i+0;
		tess.indexes[tess.numIndexes++] = i+2;
		tess.indexes[tess.numIndexes++] = i+3;
	}

	// FIXME: A lot of this can probably be removed for speed, and refactored into a more convenient function
	RB_UpdateVBOs(ATTR_POSITION | ATTR_TEXCOORD);
	
	if (glRefConfig.glsl && r_arb_shader_objects->integer)
	{
		GLSL_VertexAttribsState(ATTR_POSITION | ATTR_TEXCOORD);
		GLSL_SetUniform_ModelViewProjectionMatrix(glState.currentProgram, glState.modelviewProjection);
	}
	else
	{
		qglEnableClientState( GL_VERTEX_ARRAY );
		qglEnableClientState( GL_TEXTURE_COORD_ARRAY );
		qglVertexPointer(3, GL_FLOAT, glState.currentVBO->stride_xyz, BUFFER_OFFSET(glState.currentVBO->ofs_xyz));
		qglTexCoordPointer( 2, GL_FLOAT, glState.currentVBO->stride_st, BUFFER_OFFSET(glState.currentVBO->ofs_st) );			
	}

	qglDrawElements(GL_TRIANGLES, tess.numIndexes, GL_INDEX_TYPE, BUFFER_OFFSET(0));
	
	//R_BindNullVBO();
	//R_BindNullIBO();

	tess.numIndexes = 0;
	tess.numVertexes = 0;
	tess.firstIndex = 0;
}

static void RB_DrawQuad_Imm(float x, float y, float w, float h, float s0, float t0, float s1, float t1)
{
	qglBegin (GL_QUADS);
	{
		qglTexCoord2f( s0, t1 );
		qglVertex2f( x, y );
		
		qglTexCoord2f( s1, t1 );
		qglVertex2f( x + w, y );
		
		qglTexCoord2f( s1, t0 );
		qglVertex2f( x + w, y + h );
		
		qglTexCoord2f( s0, t0 );
		qglVertex2f( x, y + h );
	}
	qglEnd();
}

static void RB_DrawQuad_Tess(float x, float y, float w, float h, float s0, float t0, float s1, float t1)
{
	tessBeginQuads();
	{
		tessTexCoord2f( s0, t1 );
		tessVertex2f( x, y );
		
		tessTexCoord2f( s1, t1 );
		tessVertex2f( x + w, y );
		
		tessTexCoord2f( s1, t0 );
		tessVertex2f( x + w, y + h );
		
		tessTexCoord2f( s0, t0 );
		tessVertex2f( x, y + h );
	}
	tessEndQuads();
}

static void (*RB_DrawQuad) (float x, float y, float w, float h, float s0, float t0, float s1, float t1) = NULL;
static void (*RB_Color4f) (GLfloat r, GLfloat g, GLfloat b, GLfloat a) = NULL;

static void RB_DrawScaledQuad(float x, float y, float w, float h, float xcenter, float ycenter, float scale)
{
	float iscale = 1.f / scale;
	float s0 = xcenter * (1.f - iscale);
	float t0 = ycenter * (1.f - iscale);
	float s1 = iscale + s0;
	float t1 = iscale + t0;

	RB_DrawQuad(x, y, w, h, s0, t0, s1, t1);
}

static void RB_RadialBlur(int passes, float stretch, float x, float y, float w, float h, float xcenter, float ycenter, float alpha)
{
	const float inc = 1.f / passes;
	const float mul = powf(stretch, inc);
	float scale;
	
	
	alpha *= inc;
	RB_Color4f(alpha, alpha, alpha, 1.f);
	
	GL_State(GLS_DEPTHTEST_DISABLE | GLS_SRCBLEND_ONE | GLS_DSTBLEND_ZERO );
	RB_DrawQuad(x, y, w, h, 0.f, 0.f, 1.f, 1.f);
	
	GL_State(GLS_DEPTHTEST_DISABLE | GLS_SRCBLEND_ONE | GLS_DSTBLEND_ONE );
	--passes;
	scale = mul;
	while (passes > 0)
	{
		RB_DrawScaledQuad(x, y, w, h, xcenter, ycenter, scale);
		scale *= mul;
		--passes;
	}
	
	RB_Color4f(1.f, 1.f, 1.f, 1.f);
}

static qboolean RB_UpdateSunFlareVis(void)
{
	GLuint sampleCount = 0;
	if (!glRefConfig.occlusionQuery)
		return qtrue;

	tr.sunFlareQueryIndex ^= 1;
	if (!tr.sunFlareQueryActive[tr.sunFlareQueryIndex])
		return qtrue;

	/* debug code */
	if (0)
	{
		int iter;
		for (iter=0 ; ; ++iter)
		{
			GLint available = 0;
			qglGetQueryObjectivARB(tr.sunFlareQuery[tr.sunFlareQueryIndex], GL_QUERY_RESULT_AVAILABLE_ARB, &available);
			if (available)
				break;
		}

		ri.Printf(PRINT_DEVELOPER, "Waited %d iterations\n", iter);
	}
	
	qglGetQueryObjectuivARB(tr.sunFlareQuery[tr.sunFlareQueryIndex], GL_QUERY_RESULT_ARB, &sampleCount);
	return sampleCount > 0;
}

/*
================
RB_GodRays

================
*/

static void RB_GodRays(void)
{
	vec3_t dir;
	float dot;
	const float cutoff = 0.25f;
	qboolean colorize = qtrue;

	float w, h, w2, h2;
	matrix_t mvp;
	vec4_t pos, hpos;

	if (!backEnd.hasSunFlare)
		return;

	VectorSubtract(backEnd.sunFlarePos, backEnd.viewParms.or.origin, dir);
	VectorNormalize(dir);

	dot = DotProduct(dir, backEnd.viewParms.or.axis[0]);
	if (dot < cutoff)
		return;

	if (!RB_UpdateSunFlareVis())
		return;

	VectorCopy(backEnd.sunFlarePos, pos);
	pos[3] = 1.f;

	// project sun point
	Matrix16Multiply(backEnd.viewParms.projectionMatrix, backEnd.viewParms.world.modelMatrix, mvp);
	Matrix16Transform(mvp, pos, hpos);
	
	// transform to UV coords
	hpos[3] = 0.5f / hpos[3];

	pos[0] = 0.5f + hpos[0] * hpos[3];
	pos[1] = 0.5f + hpos[1] * hpos[3];
	
	// viewport dimensions
	w = glConfig.vidWidth;
	h = glConfig.vidHeight;
	w2 = glConfig.vidWidth / 2;
	h2 = glConfig.vidHeight / 2;

	// initialize quarter buffers
	{
		float mul = 1.f;
		
		RB_SetGL2D_Level(1);
		
		GL_State(GLS_DEPTHTEST_DISABLE | GLS_SRCBLEND_ONE | GLS_DSTBLEND_ZERO );
		RB_Color4f(mul, mul, mul, 1.f);

		// first, downsample the main framebuffers
		R_FBO_Bind(tr.fbo.quarter[0]);
		R_FBO_BindColorBuffer(tr.fbo.full[1], 0);
		RB_DrawQuad(0.f, 0.f, w2, h2, 0.f, 0.f, 1.f, 1.f);

		if (colorize)
		{
			GL_State(GLS_DEPTHTEST_DISABLE | GLS_SRCBLEND_DST_COLOR | GLS_DSTBLEND_SRC_COLOR );
			R_FBO_BindColorBuffer(tr.fbo.full[0], 0);
			mul = 1.f;
			RB_Color4f(mul, mul, mul, 1.f);
			RB_DrawQuad(0.f, 0.f, w2, h2, 0.f, 0.f, 1.f, 1.f);
		}
	}

	// radial blur passes, ping-ponging between the two quarter-size buffers
	{
		const float stretch_add = 2.f/3.f;
		float stretch = 1.f + stretch_add;
		int i;
		for (i=0; i<2; ++i)
		{
			R_FBO_Bind(tr.fbo.quarter[(~i) & 1]);
			R_FBO_BindColorBuffer(tr.fbo.quarter[i&1], 0);
			RB_RadialBlur(5, stretch, 0.f, 0.f, w2, h2, pos[0], pos[1], 1.125f);
			stretch += stretch_add;
		}
	}
	
	// add result back on top of the main buffer
	{
		float mul = 1.f;
		R_FBO_BindColorBuffer(R_FBO_Bind(tr.fbo.full[0]), 0);
		RB_SetGL2D_Level(0);
		GL_State(GLS_DEPTHTEST_DISABLE | GLS_SRCBLEND_ONE | GLS_DSTBLEND_ONE );
		
		RB_Color4f(mul, mul, mul, 1.f);
		RB_DrawQuad(0.f, 0.f, w, h, 0.f, 0.f, 1.f, 1.f);
	}
}

static void RB_BlurAxis(float w, float h, float strength, qboolean horizontal)
{
	float dx, dy;
	float xmul, ymul;
	float weights[3] = {
		0.227027027f,
		0.316216216f,
		0.070270270f,
	};
	float offsets[3] = {
		0.f,
		1.3846153846f,
		3.2307692308f,
	};

	xmul = horizontal;
	ymul = 1.f - xmul;

	xmul /= w;
	ymul /= h;

	xmul *= strength;
	ymul *= strength;

	GL_State(GLS_DEPTHTEST_DISABLE | GLS_SRCBLEND_ONE | GLS_DSTBLEND_ZERO | GLS_ALPHAMASK_FALSE );
	
	RB_Color4f(weights[0], weights[0], weights[0], 0.f);
	RB_DrawQuad(0.f, 0.f, w, h, 0.f, 0.f, 1.f, 1.f);

	GL_State(GLS_DEPTHTEST_DISABLE | GLS_SRCBLEND_ONE | GLS_DSTBLEND_ONE | GLS_ALPHAMASK_FALSE );
	
	RB_Color4f(weights[1], weights[1], weights[1], 0.f);
	dx = offsets[1] * xmul;
	dy = offsets[1] * ymul;
	RB_DrawQuad(0.f, 0.f, w, h, dx, dy, 1.f+dx, 1.f+dy);
	RB_DrawQuad(0.f, 0.f, w, h, -dx, -dy, 1.f-dx, 1.f-dy);

	RB_Color4f(weights[2], weights[2], weights[2], 0.f);
	dx = offsets[2] * xmul;
	dy = offsets[2] * ymul;
	RB_DrawQuad(0.f, 0.f, w, h, dx, dy, 1.f+dx, 1.f+dy);
	RB_DrawQuad(0.f, 0.f, w, h, -dx, -dy, 1.f-dx, 1.f-dy);
}

static void RB_HBlur(float w, float h, float strength)
{
	RB_BlurAxis(w, h, strength, qtrue);
}

static void RB_VBlur(float w, float h, float strength)
{
	RB_BlurAxis(w, h, strength, qfalse);
}

static void RB_Blur(void)
{
	float w, h, w2, h2, w4, h4;
	float mul = 1.f;
	float factor = Com_Clamp(0.f, 1.f, backEnd.refdef.blurFactor);
	int i;

	if (factor <= 0.f)
		return;

	// viewport dimensions
	w = glConfig.vidWidth;
	h = glConfig.vidHeight;
	w2 = glConfig.vidWidth / 2;
	h2 = glConfig.vidHeight / 2;
	w4 = glConfig.vidWidth / 4;
	h4 = glConfig.vidHeight / 4;
	
	RB_SetGL2D_Level(1);
	
	GL_State(GLS_DEPTHTEST_DISABLE | GLS_SRCBLEND_ONE | GLS_DSTBLEND_ZERO );
	RB_Color4f(mul, mul, mul, 1.f);

	// first, downsample the main framebuffers
	R_FBO_Bind(tr.fbo.quarter[0]);
	R_FBO_BindColorBuffer(tr.fbo.full[0], 0);
	RB_DrawQuad(0.f, 0.f, w2, h2, 0.f, 0.f, 1.f, 1.f);

	RB_SetGL2D_Level(2);
	GL_State(GLS_DEPTHTEST_DISABLE | GLS_SRCBLEND_ONE | GLS_DSTBLEND_ZERO );
	RB_Color4f(mul, mul, mul, 1.f);
	
	R_FBO_Bind(tr.fbo.tiny[0]);
	
	R_FBO_BindColorBuffer(tr.fbo.quarter[0], 0);
	GL_State(GLS_DEPTHTEST_DISABLE | GLS_SRCBLEND_ONE | GLS_DSTBLEND_ZERO );
	mul = 1.f;
	RB_Color4f(mul, mul, mul, 1.f);
	RB_DrawQuad(0.f, 0.f, w4, h4, 0.f, 0.f, 1.f, 1.f);

	GL_State(GLS_DEPTHTEST_DISABLE | GLS_SRCBLEND_ONE | GLS_DSTBLEND_ZERO | GLS_REDMASK_FALSE | GLS_BLUEMASK_FALSE | GLS_GREENMASK_FALSE );
	GL_Bind(tr.whiteImage);
	mul = 1.f;
	RB_Color4f(mul, mul, mul, 1.f);
	RB_DrawQuad(0.f, 0.f, w4, h4, 0.f, 0.f, 1.f, 1.f);

	//for (i=0; i<2; ++i)
	{
		R_FBO_Bind(tr.fbo.tiny[1]);
		R_FBO_BindColorBuffer(tr.fbo.tiny[0], 0);
		RB_HBlur(w4, h4, factor);

		R_FBO_Bind(tr.fbo.tiny[0]);
		R_FBO_BindColorBuffer(tr.fbo.tiny[1], 0);
		RB_VBlur(w4, h4, factor);
	}

	RB_SetGL2D_Level(0);
	R_FBO_BindColorBuffer(R_FBO_Bind(tr.fbo.full[0]), 0);
	GL_State(GLS_DEPTHTEST_DISABLE | GLS_SRCBLEND_SRC_ALPHA | GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA );
	mul = 1.f;
	RB_Color4f(mul, mul, mul, factor);
	RB_DrawQuad(0.f, 0.f, w, h, 0.f, 0.f, 1.f, 1.f);

	GL_State(GLS_DEPTHTEST_DISABLE | GLS_SRCBLEND_ONE | GLS_DSTBLEND_ZERO );
}

void RB_FBO_Set2D(void)
{
	RB_DrawQuad = NULL;
	RB_Color4f = NULL;
	
	// initialize our function pointers and perform any necessary setup
	if (glRefConfig.vertexBufferObject && r_arb_vertex_buffer_object->integer)
	{
		RB_DrawQuad = &RB_DrawQuad_Tess;
		if (glRefConfig.glsl && r_arb_shader_objects->integer)
		{
			matrix_t matrix;
			shaderProgram_t *sp = &tr.genericShader[0];

			GLSL_BindProgram(sp);
			
			GLSL_SetUniform_ModelViewProjectionMatrix(sp, glState.modelviewProjection);
			
			GLSL_SetUniform_FogAdjustColors(sp, 0);
			GLSL_SetUniform_DeformGen(sp, DGEN_NONE);
			GLSL_SetUniform_TCGen0(sp, TCGEN_TEXTURE);
			Matrix16Identity(matrix);
			GLSL_SetUniform_Texture0Matrix(sp, matrix);
			GLSL_SetUniform_Texture1Env(sp, 0);
			GLSL_SetUniform_ColorGen(sp, CGEN_CONST);
			GLSL_SetUniform_AlphaGen(sp, AGEN_CONST);

			RB_Color4f = &GLSL_Color4f;
		}
		else
		{
			RB_Color4f = &qglDefColor4f;
		}
	}
	else
	{
		RB_DrawQuad = &RB_DrawQuad_Imm;
		RB_Color4f = &qglDefColor4f;
	}

	RB_SetGL2D();
	
	GL_SelectTexture(1);
	GL_Bind(tr.whiteImage);
	GL_SelectTexture(0);
	
	RB_Color4f(1.f, 1.f, 1.f, 1.f);
}


/*
================
RB_FBO_Blit
================
*/

void RB_FBO_Blit(void)
{
	fbo_t* fbo = R_FBO_Bind(NULL);
	if (!fbo)
		return;
	
	RB_FBO_Set2D();

	R_FBO_BindColorBuffer(fbo, 0);
	GL_State(GLS_DEPTHTEST_DISABLE | GLS_SRCBLEND_ONE | GLS_DSTBLEND_ZERO );

	if (glRefConfig.glslOverbright)
	{
		float mul = 1.f / tr.identityLight;
		RB_Color4f(mul, mul, mul, 1.f);
	}

	RB_DrawQuad(0.f, 0.f, glConfig.vidWidth, glConfig.vidHeight, 0.f, 0.f, 1.f, 1.f);

	R_FBO_Bind(fbo);
}

/*
================
RB_PostProcess
================
*/

void RB_PostProcess(void)
{
	if (!glState.currentFBO || backEnd.refdef.rdflags & RDF_NOWORLDMODEL)
		return;

	RB_FBO_Set2D();
	RB_GodRays();
	RB_Blur();
}
