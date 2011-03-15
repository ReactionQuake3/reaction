#include "tr_local.h"

#ifndef ARRAY_SIZE
#	define ARRAY_SIZE(arr)				(sizeof(arr) / sizeof(arr[0]))
#endif

#define MAX_FBO_COLOR_BUFFERS		8

/*
===============
Render buffer
Can be either a zbuffer, a stencil buffer or a multisampled color buffer
===============
*/

struct fboRenderBuffer_s {
	GLuint			id;
	int				internalFormat;

	int				width;
	int				height;
	qboolean		msaa;
};

typedef fboRenderBuffer_t fboZBuffer_t;
typedef fboRenderBuffer_t fboStencilBuffer_t;

/*
===============
Color buffer

If anti-aliased we'll have a texture, a render buffer
and two frame buffers needed for the MSAA resolve.

Otherwise, only the texture is initialized.
===============
*/

struct fboColorBuffer_s {
	fboRenderBuffer_t	*buf;
	image_t				*tex;
	GLuint				fboResolve[2];
	qboolean			dirty;
};

/*
===============
Frame buffer

Has one or more color buffers, an optional zbuffer
and an optional stencil buffer
===============
*/

struct fbo_s {
	GLuint				id;
	
	int					numColorBufs;

	fboColorBuffer_t*	color[MAX_FBO_COLOR_BUFFERS];
	fboZBuffer_t*		depth;
	fboStencilBuffer_t*	stencil;

	char				name[MAX_QPATH];
};


qboolean R_FBO_CheckStatus(void)
{
	GLenum status = qglCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	const char* msg = "unknown error";
	
	switch (status)
	{
	case GL_FRAMEBUFFER_COMPLETE_EXT:
		return qtrue;

	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
		msg = "incomplete attachment";
		break;
	
	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
		msg = "missing attachment";
		break;
	
	//case GL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT_EXT:
	//	msg = "duplicate attachment";
	//	break;
	
	case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
		msg = "mismatched dimensions";
		break;
	
	case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
		msg = "mismatched formats";
		break;
	
	case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
		msg = "incomplete draw buffer";
		break;
	
	case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
		msg = "incomplete read buffer";
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT:
		msg = "mismatched multisample settings";
		break;
	
	case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
		msg = "unsupported";
		break;

	default:
		msg = va("0x%x", status);
		break;
	}

	ri.Error(ERR_FATAL, "Framebuffer setup error: %s\n", msg);
	
	return qfalse;
}

void R_FBO_InitRenderBuffer(fboRenderBuffer_t* buf)
{
	buf->id = 0;
	qglGenRenderbuffersEXT(1, &buf->id);
	qglBindRenderbufferEXT(GL_RENDERBUFFER_EXT, buf->id);
	if (buf->msaa)
	{
		qglRenderbufferStorageMultisampleEXT(GL_RENDERBUFFER_EXT, tr.fbo.samples, buf->internalFormat, buf->width, buf->height);
	}
	else
	{
		qglRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, buf->internalFormat, buf->width, buf->height);
	}
	qglBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
}

void R_FBO_ReleaseRenderBuffer(fboRenderBuffer_t* buf)
{
	if (buf->id == 0)
		return;

	qglDeleteRenderbuffersEXT(1, &buf->id);
	buf->id = 0;
}

fboRenderBuffer_t *R_FBO_CreateRenderBuffer(int width, int height, int pixelformat, qboolean msaa)
{
	fboRenderBuffer_t* ret = NULL;
	if (tr.fbo.numRenderBuffers >= ARRAY_SIZE(tr.fbo.renderBuffers))
	{
		ri.Error(ERR_FATAL, "Too many FBO render buffers\n");
		return NULL;
	}

	ret = ri.Hunk_Alloc(sizeof(*ret), h_low);
	memset(ret, 0, sizeof(*ret));

	ret->width = width;
	ret->height = height;
	ret->internalFormat = pixelformat;
	ret->msaa = (msaa && tr.fbo.samples > 1);
	
	R_FBO_InitRenderBuffer(ret);

	tr.fbo.renderBuffers[tr.fbo.numRenderBuffers++] = ret;
	
	return ret;
}

fboColorBuffer_t *R_FBO_CreateColorBuffer(const char* name, int width, int height, qboolean msaa, qboolean mipmap, int clamp)
{
	if (tr.fbo.numColorBuffers>= ARRAY_SIZE(tr.fbo.colorBuffers))
	{
		ri.Error(ERR_FATAL, "Too many FBO color buffers\n");
		return NULL;
	}
	else
	{
		qboolean			realmsaa	= msaa && tr.fbo.samples > 1;
		image_t				*texture	= R_CreateImage(name, NULL, width, height, mipmap, qfalse, clamp);
		fboRenderBuffer_t	*buf		= realmsaa ? R_FBO_CreateRenderBuffer(width, height, texture->internalFormat, qtrue) : NULL;
		fboColorBuffer_t	*ret		= ri.Hunk_Alloc(sizeof(*ret), h_low);

		Com_Memset(ret, 0, sizeof(*ret));

		ret->buf = buf;
		ret->tex = texture;
		ret->dirty = qfalse;

		if (realmsaa)
		{
			qglGenFramebuffersEXT(2, ret->fboResolve);
			
			qglBindFramebufferEXT(GL_FRAMEBUFFER_EXT, ret->fboResolve[0]);
			qglFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, ret->buf->id);
			R_FBO_CheckStatus();

			qglBindFramebufferEXT(GL_FRAMEBUFFER_EXT, ret->fboResolve[1]);
			qglFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, ret->tex->texnum, 0);
			R_FBO_CheckStatus();

			qglBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		}
		else
		{
			ret->fboResolve[0] = ret->fboResolve[1] = 0;
		}

		tr.fbo.colorBuffers[tr.fbo.numColorBuffers++] = ret;
		
		return ret;
	}
}

void R_FBO_ReleaseColorBuffer(fboColorBuffer_t* color)
{
	if (color->buf)
	{
		qglDeleteFramebuffersEXT(2, color->fboResolve);
	}
}

fboZBuffer_t *R_FBO_CreateZBuffer(int width, int height, qboolean msaa)
{
	return R_FBO_CreateRenderBuffer(width, height, GL_DEPTH_COMPONENT24, msaa);
}

void R_FBO_Init(fbo_t* fbo)
{
	memset(fbo, 0, sizeof(*fbo));
	qglGenFramebuffersEXT(1, &fbo->id);
}

void R_FBO_Release(fbo_t* fbo)
{
	if (fbo->id == 0)
		return;

	qglDeleteFramebuffersEXT(1, &fbo->id);
	fbo->id = 0;
}

void R_FBO_AddColorBuffer(fbo_t* fbo, fboColorBuffer_t* color)
{
	GLenum attach;
	if (fbo->numColorBufs >= ARRAY_SIZE(fbo->color))
	{
		ri.Error(ERR_FATAL, "Max FBO color buffers exceeded.\n");
		return;
	}
	fbo->color[fbo->numColorBufs++] = color;
	
	qglBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo->id);
	attach = GL_COLOR_ATTACHMENT0_EXT + fbo->numColorBufs - 1;
	if (color->buf)
	{
		qglFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, attach, GL_RENDERBUFFER_EXT, color->buf->id);
	}
	else
	{
		qglFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, attach, GL_TEXTURE_2D, color->tex->texnum, 0);
	}
}

/*
===============
R_FBO_Bind
===============
*/

fbo_t* R_FBO_Bind(fbo_t* fbo)
{
	fbo_t* old = glState.currentFBO;
	GLuint id = 0;
	if (!glRefConfig.framebufferObject)
	{
		glState.currentFBO = NULL;
		return NULL;
	}
	
	if (old == fbo)
		return old;

	glState.currentFBO = fbo;
	if (fbo)
		id = fbo->id;

	qglBindFramebufferEXT(GL_FRAMEBUFFER_EXT, id);

	if (fbo)
	{
		int i;
		for (i=0; i<fbo->numColorBufs; ++i)
		{
			fboColorBuffer_t* color = fbo->color[i];
			color->dirty = (color->buf != NULL);
		}
		
		if (1)
			R_FBO_CheckStatus();
	}

	return old;
}

/*
===============
R_FBO_BindColorBuffer
===============
*/

void R_FBO_BindColorBuffer(fbo_t* fbo, int index)
{
	fboColorBuffer_t* color = fbo->color[index];
	if (color->dirty)
	{
		color->dirty = qfalse;
		
		// resolve
		if (color->buf)
		{
			int id;
			int width = color->buf->width;
			int height = color->buf->height;
			
			qglBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, color->fboResolve[0]);
			qglBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, color->fboResolve[1]);
			qglBlitFramebufferEXT(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
			
			if (glState.currentFBO)
				id = glState.currentFBO->id;
			else
				id = 0;

			qglBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, id);
			qglBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, id);
		}
	}
	GL_Bind(color->tex);
}

/*
===============
R_FBO_CreateEx
===============
*/

fbo_t* R_FBO_CreateEx(const char* name, int numColorBuffers, fboColorBuffer_t** colorBuffers, fboZBuffer_t* depth, fboStencilBuffer_t* stencil)
{
	fbo_t* fbo = NULL;

	if (tr.fbo.numFBOs >= ARRAY_SIZE(tr.fbo.fbos))
	{
		ri.Error(ERR_FATAL, "Too many FBO's\n");
		return NULL;
	}

	ri.Printf(PRINT_DEVELOPER, "Creating FBO %s: %d color/%d depth/%d stencil\n", name, numColorBuffers, depth != NULL, stencil != NULL);

	fbo = ri.Hunk_Alloc(sizeof(*fbo), h_low);

	R_FBO_Init(fbo);

	Q_strncpyz(fbo->name, name, ARRAY_SIZE(fbo->name));

	while (numColorBuffers-- > 0)
		R_FBO_AddColorBuffer(fbo, *colorBuffers++);

	fbo->depth = depth;
	fbo->stencil = stencil;

	qglBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo->id);

	if (fbo->depth)
		qglFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, fbo->depth->id);

	if (fbo->stencil)
		qglFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, fbo->stencil->id);
	
	qglBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	tr.fbo.fbos[tr.fbo.numFBOs++] = fbo;

	return fbo;
}

fbo_t* R_FBO_CreateSimple(const char* name, fboColorBuffer_t* color, fboZBuffer_t* depth, fboStencilBuffer_t* stencil)
{
	return R_FBO_CreateEx(name, color != NULL, &color, depth, stencil);
}

/*
===============
R_FBO_CreateDefaultBuffers
===============
*/

static void R_FBO_CreateDefaultBuffers(void)
{
	qboolean msaa = tr.fbo.samples > 1;

	tr.fbo.full[0] = R_FBO_CreateSimple(
		"main",
		R_FBO_CreateColorBuffer("*framebuffer0", glConfig.vidWidth, glConfig.vidHeight, msaa, qfalse, GL_CLAMP_TO_EDGE),
		R_FBO_CreateZBuffer(glConfig.vidWidth, glConfig.vidHeight, msaa),
		NULL);

	tr.fbo.full[1] = R_FBO_CreateSimple(
		"postprocess",
		R_FBO_CreateColorBuffer("*framebuffer1", glConfig.vidWidth, glConfig.vidHeight, msaa, qfalse, GL_CLAMP_TO_EDGE),
		tr.fbo.full[0]->depth,
		NULL);

	tr.fbo.quarter[0] = R_FBO_CreateSimple(
		"quarter0",
		R_FBO_CreateColorBuffer("*quarterBuffer0", glConfig.vidWidth/2, glConfig.vidHeight/2, qfalse, qfalse, GL_CLAMP_TO_EDGE),
		NULL,
		NULL);
	
	tr.fbo.quarter[1] = R_FBO_CreateSimple(
		"quarter1",
		R_FBO_CreateColorBuffer("*quarterBuffer1", glConfig.vidWidth/2, glConfig.vidHeight/2, qfalse, qfalse, GL_CLAMP_TO_EDGE),
		NULL,
		NULL);
	
	ri.Printf(PRINT_DEVELOPER, "...created %d FBOs\n", tr.fbo.numFBOs);
}

/*
===============
R_InitFBOs
===============
*/

void R_InitFBOs(void)
{
	GLint maxSamples = 0;
	if (!glRefConfig.framebufferObject)
		return;

	ri.Printf(PRINT_ALL, "------- R_InitFBOs -------\n");

	if (glRefConfig.framebufferMultisample && glRefConfig.framebufferBlit)
	{
		qglGetIntegerv(GL_MAX_SAMPLES_EXT, &maxSamples);
		tr.fbo.samples = maxSamples < r_ext_multisample->integer ? maxSamples : r_ext_multisample->integer;
		if (tr.fbo.samples < 2)
			tr.fbo.samples = 0;
	}
	else
	{
		tr.fbo.samples = 0;
	}

	if (tr.fbo.samples > 1)
		ri.Printf(PRINT_ALL, "MSAA enabled with %d samples (max %d)\n", tr.fbo.samples, maxSamples);

	R_FBO_CreateDefaultBuffers();

	R_FBO_Bind(tr.fbo.full[0]);
}


/*
===============
R_ShutDownFBOs
===============
*/

void R_ShutDownFBOs(void)
{
	if (!glRefConfig.framebufferObject)
		return;

	ri.Printf(PRINT_ALL, "------- R_ShutdownFBOs -------\n");

	R_FBO_Bind(NULL);

	while (tr.fbo.numRenderBuffers>0)
		R_FBO_ReleaseRenderBuffer(tr.fbo.renderBuffers[--tr.fbo.numRenderBuffers]);

	while (tr.fbo.numColorBuffers>0)
		R_FBO_ReleaseColorBuffer(tr.fbo.colorBuffers[--tr.fbo.numColorBuffers]);
	
	while (tr.fbo.numFBOs>0)
		R_FBO_Release(tr.fbo.fbos[--tr.fbo.numFBOs]);
}

