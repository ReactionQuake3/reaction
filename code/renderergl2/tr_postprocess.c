/*
===========================================================================
Copyright (C) 2011 Andrei Drexler, Richard Allen, James Canete

This file is part of Reaction source code.

Reaction source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Reaction source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Reaction source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/

#include "tr_local.h"

// REACTION: auto exposure blends once per 8 ms, the frame time of 125 frames a second, which 1.0's default.cfg set
#define AUTO_EXPOSURE_BLEND_MSEC 8

void RB_ToneMap(FBO_t *hdrFbo, ivec4_t hdrBox, FBO_t *ldrFbo, ivec4_t ldrBox, int autoExposure)
{
	ivec4_t srcBox, dstBox;
	vec4_t color;
	static int lastFrameCount = 0;

	if (autoExposure)
	{
		if (lastFrameCount == 0 || tr.frameCount < lastFrameCount || tr.frameCount - lastFrameCount > 5)
		{
			// determine average log luminance
			FBO_t *srcFbo, *dstFbo, *tmp;
			int size = 256;

			lastFrameCount = tr.frameCount;

			VectorSet4(dstBox, 0, 0, size, size);

			FBO_Blit(hdrFbo, hdrBox, NULL, tr.textureScratchFbo[0], dstBox, &tr.calclevels4xShader[0], NULL, 0);

			srcFbo = tr.textureScratchFbo[0];
			dstFbo = tr.textureScratchFbo[1];

			// downscale to 1x1 texture
			while (size > 1)
			{
				VectorSet4(srcBox, 0, 0, size, size);
				//size >>= 2;
				size >>= 1;
				VectorSet4(dstBox, 0, 0, size, size);

				if (size == 1)
					dstFbo = tr.targetLevelsFbo;

				//FBO_Blit(targetFbo, srcBox, NULL, tr.textureScratchFbo[nextScratch], dstBox, &tr.calclevels4xShader[1], NULL, 0);
				FBO_FastBlit(srcFbo, srcBox, dstFbo, dstBox, GL_COLOR_BUFFER_BIT, GL_LINEAR);

				tmp = srcFbo;
				srcFbo = dstFbo;
				dstFbo = tmp;
			}
		}

		// blend with old log luminance for gradual change
		VectorSet4(srcBox, 0, 0, 0, 0);

		color[0] = 
		color[1] =
		color[2] = 1.0f;
		// REACTION: once per step of time, as the blend per frame did at 125 frames a second; per frame, the exposure
		// adapted 2.6 times as fast once the client drew 330 a second (drawing between movement ticks). Frames between
		// steps do not blend: a smaller share per frame rounds away in the levels texture and stalls short of the scene.
		{
			static int lastBlendTime;
			int now = ri.Milliseconds();
			int steps;

			// the first blend, or after the clock went back, is one step
			if (!lastBlendTime || now < lastBlendTime)
				lastBlendTime = now - AUTO_EXPOSURE_BLEND_MSEC;
			steps = (now - lastBlendTime) / AUTO_EXPOSURE_BLEND_MSEC;
			if (steps > 0)
			{
				float share = glRefConfig.textureFloat ? 0.03f : 0.1f;

				lastBlendTime += steps * AUTO_EXPOSURE_BLEND_MSEC;
				color[3] = 1.0f - pow(1.0f - share, steps);
				FBO_Blit(tr.targetLevelsFbo, srcBox, NULL, tr.calcLevelsFbo, NULL,  NULL, color, GLS_SRCBLEND_SRC_ALPHA | GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA);
			}
		}
	}

	// tonemap
	color[0] =
	color[1] =
	color[2] = pow(2, r_cameraExposure->value - autoExposure); //exp2(r_cameraExposure->value);
	color[3] = 1.0f;

	if (autoExposure)
		GL_BindToTMU(tr.calcLevelsImage,  TB_LEVELSMAP);
	else
		GL_BindToTMU(tr.fixedLevelsImage, TB_LEVELSMAP);

	FBO_Blit(hdrFbo, hdrBox, NULL, ldrFbo, ldrBox, &tr.tonemapShader, color, 0);
}

/*
=============
RB_BokehBlur


Blurs a part of one framebuffer to another.

Framebuffers can be identical. 
=============
*/
void RB_BokehBlur(FBO_t *src, ivec4_t srcBox, FBO_t *dst, ivec4_t dstBox, float blur)
{
//	ivec4_t srcBox, dstBox;
	vec4_t color;
	
	blur *= 10.0f;

	if (blur < 0.004f)
		return;

	if (glRefConfig.framebufferObject)
	{
		// bokeh blur
		if (blur > 0.0f)
		{
			ivec4_t quarterBox;

			quarterBox[0] = 0;
			quarterBox[1] = tr.quarterFbo[0]->height;
			quarterBox[2] = tr.quarterFbo[0]->width;
			quarterBox[3] = -tr.quarterFbo[0]->height;

			// create a quarter texture
			//FBO_Blit(NULL, NULL, NULL, tr.quarterFbo[0], NULL, NULL, NULL, 0);
			FBO_FastBlit(src, srcBox, tr.quarterFbo[0], quarterBox, GL_COLOR_BUFFER_BIT, GL_LINEAR);
		}

#ifndef HQ_BLUR
		if (blur > 1.0f)
		{
			// create a 1/16th texture
			//FBO_Blit(tr.quarterFbo[0], NULL, NULL, tr.textureScratchFbo[0], NULL, NULL, NULL, 0);
			FBO_FastBlit(tr.quarterFbo[0], NULL, tr.textureScratchFbo[0], NULL, GL_COLOR_BUFFER_BIT, GL_LINEAR);
		}
#endif

		if (blur > 0.0f && blur <= 1.0f)
		{
			// Crossfade original with quarter texture
			VectorSet4(color, 1, 1, 1, blur);

			FBO_Blit(tr.quarterFbo[0], NULL, NULL, dst, dstBox, NULL, color, GLS_SRCBLEND_SRC_ALPHA | GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA);
		}
#ifndef HQ_BLUR
		// ok blur, but can see some pixelization
		else if (blur > 1.0f && blur <= 2.0f)
		{
			// crossfade quarter texture with 1/16th texture
			FBO_Blit(tr.quarterFbo[0], NULL, NULL, dst, dstBox, NULL, NULL, 0);

			VectorSet4(color, 1, 1, 1, blur - 1.0f);

			FBO_Blit(tr.textureScratchFbo[0], NULL, NULL, dst, dstBox, NULL, color, GLS_SRCBLEND_SRC_ALPHA | GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA);
		}
		else if (blur > 2.0f)
		{
			// blur 1/16th texture then replace
			int i;

			for (i = 0; i < 2; i++)
			{
				vec2_t blurTexScale;
				float subblur;

				subblur = ((blur - 2.0f) / 2.0f) / 3.0f * (float)(i + 1);

				blurTexScale[0] =
				blurTexScale[1] = subblur;

				color[0] =
				color[1] =
				color[2] = 0.5f;
				color[3] = 1.0f;

				if (i != 0)
					FBO_Blit(tr.textureScratchFbo[0], NULL, blurTexScale, tr.textureScratchFbo[1], NULL, &tr.bokehShader, color, GLS_SRCBLEND_ONE | GLS_DSTBLEND_ONE);
				else
					FBO_Blit(tr.textureScratchFbo[0], NULL, blurTexScale, tr.textureScratchFbo[1], NULL, &tr.bokehShader, color, 0);
			}

			FBO_Blit(tr.textureScratchFbo[1], NULL, NULL, dst, dstBox, NULL, NULL, 0);
		}
#else // higher quality blur, but slower
		else if (blur > 1.0f)
		{
			// blur quarter texture then replace
			int i;

			src = tr.quarterFbo[0];
			dst = tr.quarterFbo[1];

			VectorSet4(color, 0.5f, 0.5f, 0.5f, 1);

			for (i = 0; i < 2; i++)
			{
				vec2_t blurTexScale;
				float subblur;

				subblur = (blur - 1.0f) / 2.0f * (float)(i + 1);

				blurTexScale[0] =
				blurTexScale[1] = subblur;

				color[0] =
				color[1] =
				color[2] = 1.0f;
				if (i != 0)
					color[3] = 1.0f;
				else
					color[3] = 0.5f;

				FBO_Blit(tr.quarterFbo[0], NULL, blurTexScale, tr.quarterFbo[1], NULL, &tr.bokehShader, color, GLS_SRCBLEND_SRC_ALPHA | GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA);
			}

			FBO_Blit(tr.quarterFbo[1], NULL, NULL, dst, dstBox, NULL, NULL, 0);
		}
#endif
	}
}


static void RB_RadialBlur(FBO_t *srcFbo, FBO_t *dstFbo, int passes, float stretch, float x, float y, float w, float h, float xcenter, float ycenter, float alpha)
{
	ivec4_t srcBox, dstBox;
	int srcWidth, srcHeight;
	vec4_t color;
	const float inc = 1.f / passes;
	const float mul = powf(stretch, inc);
	float scale;

	alpha *= inc;
	VectorSet4(color, alpha, alpha, alpha, 1.0f);

	srcWidth  = srcFbo ? srcFbo->width  : glConfig.vidWidth;
	srcHeight = srcFbo ? srcFbo->height : glConfig.vidHeight;

	VectorSet4(srcBox, 0, 0, srcWidth, srcHeight);

	VectorSet4(dstBox, x, y, w, h);
	FBO_Blit(srcFbo, srcBox, NULL, dstFbo, dstBox, NULL, color, 0);

	--passes;
	scale = mul;
	while (passes > 0)
	{
		float iscale = 1.f / scale;
		float s0 = xcenter * (1.f - iscale);
		float t0 = (1.0f - ycenter) * (1.f - iscale);

		srcBox[0] = s0 * srcWidth;
		srcBox[1] = t0 * srcHeight;
		srcBox[2] = iscale * srcWidth;
		srcBox[3] = iscale * srcHeight;
			
		FBO_Blit(srcFbo, srcBox, NULL, dstFbo, dstBox, NULL, color, GLS_SRCBLEND_ONE | GLS_DSTBLEND_ONE );

		scale *= mul;
		--passes;
	}
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
			qglGetQueryObjectiv(tr.sunFlareQuery[tr.sunFlareQueryIndex], GL_QUERY_RESULT_AVAILABLE, &available);
			if (available)
				break;
		}

		ri.Printf(PRINT_DEVELOPER, "Waited %d iterations\n", iter);
	}
	
	// Note: On desktop OpenGL this is a sample count (glRefConfig.occlusionQueryTarget == GL_SAMPLES_PASSED)
	// but on OpenGL ES this is a boolean (glRefConfig.occlusionQueryTarget == GL_ANY_SAMPLES_PASSED)
	qglGetQueryObjectuiv(tr.sunFlareQuery[tr.sunFlareQueryIndex], GL_QUERY_RESULT, &sampleCount);
	return sampleCount > 0;
}

void RB_SunRays(FBO_t *srcFbo, ivec4_t srcBox, FBO_t *dstFbo, ivec4_t dstBox)
{
	vec4_t color;
	float dot;
	const float cutoff = 0.25f;
	qboolean colorize = qtrue;

//	float w, h, w2, h2;
	mat4_t mvp;
	vec4_t pos, hpos;

	dot = DotProduct(tr.sunDirection, backEnd.viewParms.or.axis[0]);
	if (dot < cutoff)
		return;

	if (!RB_UpdateSunFlareVis())
		return;

	// From RB_DrawSun()
	{
		float dist;
		mat4_t trans, model;

		Mat4Translation( backEnd.viewParms.or.origin, trans );
		Mat4Multiply( backEnd.viewParms.world.modelMatrix, trans, model );
		Mat4Multiply(backEnd.viewParms.projectionMatrix, model, mvp);

		dist = backEnd.viewParms.zFar / 1.75;		// div sqrt(3)

		VectorScale( tr.sunDirection, dist, pos );
	}

	// project sun point
	//Mat4Multiply(backEnd.viewParms.projectionMatrix, backEnd.viewParms.world.modelMatrix, mvp);
	Mat4Transform(mvp, pos, hpos);

	// transform to UV coords
	hpos[3] = 0.5f / hpos[3];

	pos[0] = 0.5f + hpos[0] * hpos[3];
	pos[1] = 0.5f + hpos[1] * hpos[3];

	// initialize quarter buffers
	{
		float mul = 1.f;
		ivec4_t rayBox, quarterBox;
		int srcWidth  = srcFbo ? srcFbo->width  : glConfig.vidWidth;
		int srcHeight = srcFbo ? srcFbo->height : glConfig.vidHeight;

		VectorSet4(color, mul, mul, mul, 1);

		rayBox[0] = srcBox[0] * tr.sunRaysFbo->width  / srcWidth;
		rayBox[1] = srcBox[1] * tr.sunRaysFbo->height / srcHeight;
		rayBox[2] = srcBox[2] * tr.sunRaysFbo->width  / srcWidth;
		rayBox[3] = srcBox[3] * tr.sunRaysFbo->height / srcHeight;

		quarterBox[0] = 0;
		quarterBox[1] = tr.quarterFbo[0]->height;
		quarterBox[2] = tr.quarterFbo[0]->width;
		quarterBox[3] = -tr.quarterFbo[0]->height;

		// first, downsample the framebuffer
		if (colorize)
		{
			FBO_FastBlit(srcFbo, srcBox, tr.quarterFbo[0], quarterBox, GL_COLOR_BUFFER_BIT, GL_LINEAR);
			FBO_Blit(tr.sunRaysFbo, rayBox, NULL, tr.quarterFbo[0], quarterBox, NULL, color, GLS_SRCBLEND_DST_COLOR | GLS_DSTBLEND_ZERO);
		}
		else
		{
			FBO_FastBlit(tr.sunRaysFbo, rayBox, tr.quarterFbo[0], quarterBox, GL_COLOR_BUFFER_BIT, GL_LINEAR);
		}
	}

	// radial blur passes, ping-ponging between the two quarter-size buffers
	{
		const float stretch_add = 2.f/3.f;
		float stretch = 1.f + stretch_add;
		int i;
		for (i=0; i<2; ++i)
		{
			RB_RadialBlur(tr.quarterFbo[i&1], tr.quarterFbo[(~i) & 1], 5, stretch, 0.f, 0.f, tr.quarterFbo[0]->width, tr.quarterFbo[0]->height, pos[0], pos[1], 1.125f);
			stretch += stretch_add;
		}
	}
	
	// add result back on top of the main buffer
	{
		float mul = 1.f;

		VectorSet4(color, mul, mul, mul, 1);

		FBO_Blit(tr.quarterFbo[0], NULL, NULL, dstFbo, dstBox, NULL, color, GLS_SRCBLEND_ONE | GLS_DSTBLEND_ONE);
	}
}

static void RB_BlurAxis(FBO_t *srcFbo, FBO_t *dstFbo, float strength, qboolean horizontal)
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

	xmul *= strength;
	ymul *= strength;

	{
		ivec4_t srcBox, dstBox;
		vec4_t color;

		VectorSet4(color, weights[0], weights[0], weights[0], 1.0f);
		VectorSet4(srcBox, 0, 0, srcFbo->width, srcFbo->height);
		VectorSet4(dstBox, 0, 0, dstFbo->width, dstFbo->height);
		FBO_Blit(srcFbo, srcBox, NULL, dstFbo, dstBox, NULL, color, 0);

		VectorSet4(color, weights[1], weights[1], weights[1], 1.0f);
		dx = offsets[1] * xmul;
		dy = offsets[1] * ymul;
		VectorSet4(srcBox, dx, dy, srcFbo->width, srcFbo->height);
		FBO_Blit(srcFbo, srcBox, NULL, dstFbo, dstBox, NULL, color, GLS_SRCBLEND_ONE | GLS_DSTBLEND_ONE);
		VectorSet4(srcBox, -dx, -dy, srcFbo->width, srcFbo->height);
		FBO_Blit(srcFbo, srcBox, NULL, dstFbo, dstBox, NULL, color, GLS_SRCBLEND_ONE | GLS_DSTBLEND_ONE);

		VectorSet4(color, weights[2], weights[2], weights[2], 1.0f);
		dx = offsets[2] * xmul;
		dy = offsets[2] * ymul;
		VectorSet4(srcBox, dx, dy, srcFbo->width, srcFbo->height);
		FBO_Blit(srcFbo, srcBox, NULL, dstFbo, dstBox, NULL, color, GLS_SRCBLEND_ONE | GLS_DSTBLEND_ONE);
		VectorSet4(srcBox, -dx, -dy, srcFbo->width, srcFbo->height);
		FBO_Blit(srcFbo, srcBox, NULL, dstFbo, dstBox, NULL, color, GLS_SRCBLEND_ONE | GLS_DSTBLEND_ONE);
	}
}

static void RB_HBlur(FBO_t *srcFbo, FBO_t *dstFbo, float strength)
{
	RB_BlurAxis(srcFbo, dstFbo, strength, qtrue);
}

static void RB_VBlur(FBO_t *srcFbo, FBO_t *dstFbo, float strength)
{
	RB_BlurAxis(srcFbo, dstFbo, strength, qfalse);
}

void RB_GaussianBlur(FBO_t *srcFbo, FBO_t *dstFbo, float blur)
{
	//float mul = 1.f;
	float factor = Com_Clamp(0.f, 1.f, blur);

	if (factor <= 0.f)
		return;

	{
		ivec4_t srcBox, dstBox;
		vec4_t color;

		VectorSet4(color, 1, 1, 1, 1);

		// first, downsample the framebuffer
		FBO_FastBlit(srcFbo, NULL, tr.quarterFbo[0], NULL, GL_COLOR_BUFFER_BIT, GL_LINEAR);
		FBO_FastBlit(tr.quarterFbo[0], NULL, tr.textureScratchFbo[0], NULL, GL_COLOR_BUFFER_BIT, GL_LINEAR);

		// set the alpha channel
		qglColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_TRUE);
		FBO_BlitFromTexture(tr.whiteImage, NULL, NULL, tr.textureScratchFbo[0], NULL, NULL, color, GLS_DEPTHTEST_DISABLE);
		qglColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

		// blur the tiny buffer horizontally and vertically
		RB_HBlur(tr.textureScratchFbo[0], tr.textureScratchFbo[1], factor);
		RB_VBlur(tr.textureScratchFbo[1], tr.textureScratchFbo[0], factor);

		// finally, merge back to framebuffer
		VectorSet4(srcBox, 0, 0, tr.textureScratchFbo[0]->width, tr.textureScratchFbo[0]->height);
		VectorSet4(dstBox, 0, 0, glConfig.vidWidth,              glConfig.vidHeight);
		color[3] = factor;
		FBO_Blit(tr.textureScratchFbo[0], srcBox, NULL, dstFbo, dstBox, NULL, color, GLS_SRCBLEND_SRC_ALPHA | GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA);
	}
}

/*
=============
RB_TemporalAA

REACTION: temporal anti-aliasing (r_temporalAA). The static world's geometry was drawn a
fraction of a pixel off (VPF_TEMPORALJITTER); at its edges this blends the picture, in src,
with the frames before it, moved to where this frame sees them by its depth
(temporalaa_fp.glsl). A ledge thinner than a pixel is then averaged over many offsets instead
of showing or vanishing with every small move. Anything else stays as with the setting off.
=============
*/

// this frame's share of the blend on an edge, so about the last ten frames are seen
#define TEMPORAL_BLEND 0.1f
// a move longer than this in one frame (a teleport, a respawn) starts the blend over
#define TEMPORAL_RESET_DISTANCE 64.0f
// around a model's bounds, as they are its first frame's and an animated model leaves them: map units, then pixels
#define TEMPORAL_ENTITY_MARGIN 16.0f
#define TEMPORAL_ENTITY_MARGIN_PIXELS 2

// Writes this frame into the new history over a model entity on the screen (temporalkeep_fp.glsl), with no memory of edges
// there: what moves is not blended, so a player far away looks the same with the setting on as off, and leaves no trail.
// Its box and depths come from its bounds, so a model hidden behind a wall touches none of the wall in front of it.
static void RB_TemporalKeepEntity(const trRefEntity_t *ent, const mat4_t viewProjection, FBO_t *src, FBO_t *dst)
{
	vec3_t bounds[2];
	vec2_t depthRange;
	ivec4_t box;
	float left = 1.0f, right = -1.0f, bottom = 1.0f, top = -1.0f, nearest = 1.0f, farthest = 0.0f;
	int i, behind = 0;

	// the view weapon is told by its depth (temporalaa_fp.glsl); the player's own body is not drawn through the eyes
	if (ent->e.reType != RT_MODEL || (ent->e.renderfx & (RF_FIRST_PERSON | RF_THIRD_PERSON | RF_DEPTHHACK)))
		return;

	R_ModelBounds(ent->e.hModel, bounds[0], bounds[1]);

	for (i = 0; i < 8; i++)
	{
		vec4_t corner, clip;
		vec3_t local;
		int j;

		for (j = 0; j < 3; j++)
			local[j] = (i & (1 << j)) ? bounds[1][j] + TEMPORAL_ENTITY_MARGIN : bounds[0][j] - TEMPORAL_ENTITY_MARGIN;

		for (j = 0; j < 3; j++)
			corner[j] = ent->e.origin[j] + local[0] * ent->e.axis[0][j] + local[1] * ent->e.axis[1][j] + local[2] * ent->e.axis[2][j];
		corner[3] = 1.0f;

		Mat4Transform(viewProjection, corner, clip);
		if (clip[3] <= 0.0f)
		{
			behind++;
			continue;
		}

		left = MIN(left, clip[0] / clip[3]);
		right = MAX(right, clip[0] / clip[3]);
		bottom = MIN(bottom, clip[1] / clip[3]);
		top = MAX(top, clip[1] / clip[3]);
		nearest = MIN(nearest, clip[2] / clip[3] * 0.5f + 0.5f);
		farthest = MAX(farthest, clip[2] / clip[3] * 0.5f + 0.5f);
	}

	// wholly behind the eye it is not seen; partly, it may reach across the whole picture
	if (behind == 8)
		return;

	if (behind)
	{
		left = bottom = -1.0f;
		right = top = 1.0f;
		nearest = 0.0f;
	}

	left = Com_Clamp(-1.0f, 1.0f, left);
	right = Com_Clamp(-1.0f, 1.0f, right);
	bottom = Com_Clamp(-1.0f, 1.0f, bottom);
	top = Com_Clamp(-1.0f, 1.0f, top);

	box[0] = MAX(0, (int)floor((left * 0.5f + 0.5f) * dst->width) - TEMPORAL_ENTITY_MARGIN_PIXELS);
	box[1] = MAX(0, (int)floor((bottom * 0.5f + 0.5f) * dst->height) - TEMPORAL_ENTITY_MARGIN_PIXELS);
	box[2] = MIN(dst->width, (int)ceil((right * 0.5f + 0.5f) * dst->width) + TEMPORAL_ENTITY_MARGIN_PIXELS) - box[0];
	box[3] = MIN(dst->height, (int)ceil((top * 0.5f + 0.5f) * dst->height) + TEMPORAL_ENTITY_MARGIN_PIXELS) - box[1];

	if (box[2] <= 0 || box[3] <= 0)
		return;

	VectorSet2(depthRange, nearest, farthest);
	GLSL_SetUniformVec2(&tr.temporalKeepShader, UNIFORM_TEMPORALDEPTHRANGE, depthRange);
	FBO_Blit(src, box, NULL, dst, box, &tr.temporalKeepShader, NULL, 0);
}

void RB_TemporalAA(FBO_t *src)
{
	// the frame before: which history image it wrote, when, from where, and its view without the offset
	static int lastWritten;
	static image_t *lastImage;
	static int lastFrame;
	static vec3_t lastOrigin;
	static mat4_t lastViewProjection;
	mat4_t projection, viewProjection, inverse, reprojection;
	vec3_t moved;
	float blend = TEMPORAL_BLEND;
	int read = lastWritten, write = !lastWritten;
	FBO_t *dst = tr.temporalHistoryFbo[write];
	int i;

	// both frames' views without their sub-pixel offsets: a standing camera then reads the history at the very pixel
	// it writes, while the offsets alone move the samples that are averaged
	R_ProjectionWithoutJitter(&backEnd.viewParms, projection);
	Mat4Multiply(projection, backEnd.viewParms.world.modelMatrix, viewProjection);

	// start over without a frame just before this one from the same images (vid_restart), after a jump, or if the
	// view cannot be inverted
	VectorSubtract(backEnd.viewParms.or.origin, lastOrigin, moved);
	if (lastImage != tr.temporalHistoryImage[read] || backEnd.viewParms.frameCount != lastFrame + 1
		|| VectorLength(moved) > TEMPORAL_RESET_DISTANCE || !Mat4Inverse(viewProjection, inverse))
	{
		blend = 1.0f;
		Mat4Identity(reprojection);
	}
	else
	{
		Mat4Multiply(lastViewProjection, inverse, reprojection);
	}

	GL_BindToTMU(tr.temporalHistoryImage[read], TB_LIGHTMAP);
	GL_BindToTMU(tr.renderDepthImage, TB_NORMALMAP);
	GLSL_SetUniformMat4(&tr.temporalAAShader, UNIFORM_REPROJECTIONMATRIX, reprojection);
	GLSL_SetUniformFloat(&tr.temporalAAShader, UNIFORM_TEMPORALBLEND, blend);
	FBO_Blit(src, NULL, NULL, dst, NULL, &tr.temporalAAShader, NULL, 0);

	for (i = 0; i < backEnd.refdef.num_entities; i++)
		RB_TemporalKeepEntity(&backEnd.refdef.entities[i], viewProjection, src, dst);

	// the shown picture; its alpha stays, as shaders of the 2D drawn later blend by it
	qglColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE);
	FBO_Blit(dst, NULL, NULL, src, NULL, NULL, NULL, 0);
	qglColorMask(!backEnd.colorMask[0], !backEnd.colorMask[1], !backEnd.colorMask[2], !backEnd.colorMask[3]);

	lastWritten = write;
	lastImage = tr.temporalHistoryImage[write];
	lastFrame = backEnd.viewParms.frameCount;
	VectorCopy(backEnd.viewParms.or.origin, lastOrigin);
	Mat4Copy(viewProjection, lastViewProjection);
}
