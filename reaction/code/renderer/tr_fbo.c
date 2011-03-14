#include "tr_local.h"

#ifndef ARRAY_SIZE
#	define ARRAY_SIZE(arr)				(sizeof(arr) / sizeof(arr[0]))
#endif

typedef struct fboRenderBuffer_s {
	GLuint			id;
	int				internalFormat;

	int				width;
	int				height;
} fboRenderBuffer_t;

#define MAX_FBO_COLOR_BUFFERS		8

typedef struct fbo_s {
	GLuint				id;
	
	int					numColorBufs;

	image_t*			color[MAX_FBO_COLOR_BUFFERS];
	fboZBuffer_t*		depth;
	fboStencilBuffer_t*	stencil;

	char				name[MAX_QPATH];
} fbo_t;


void R_FBO_InitRenderBuffer(fboRenderBuffer_t* buf)
{
	buf->id = 0;
	qglGenRenderbuffersEXT(1, &buf->id);
	qglBindRenderbufferEXT(GL_RENDERBUFFER_EXT, buf->id);
	qglRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, buf->internalFormat, buf->width, buf->height);
	qglBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
}

void R_FBO_ReleaseRenderBuffer(fboRenderBuffer_t* buf)
{
	if (buf->id == 0)
		return;

	qglDeleteRenderbuffersEXT(1, &buf->id);
	buf->id = 0;
}

fboRenderBuffer_t* R_FBO_CreateRenderBuffer(int width, int height, int pixelformat)
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
	
	R_FBO_InitRenderBuffer(ret);

	tr.fbo.renderBuffers[tr.fbo.numRenderBuffers++] = ret;
	
	return ret;
}

fboZBuffer_t* R_FBO_CreateZBuffer(int width, int height)
{
	return R_FBO_CreateRenderBuffer(width, height, GL_DEPTH_COMPONENT24);
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

void R_FBO_AddColorBuffer(fbo_t* fbo, image_t* image)
{
	if (fbo->numColorBufs >= ARRAY_SIZE(fbo->color))
	{
		ri.Error(ERR_FATAL, "Max FBO color buffers exceeded.\n");
		return;
	}
	fbo->color[fbo->numColorBufs++] = image;
	qglBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo->id);
	qglFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, (GLenum)(GL_COLOR_ATTACHMENT0_EXT + fbo->numColorBufs - 1), GL_TEXTURE_2D, image->texnum, 0);
}

qboolean R_FBO_Check()
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
	
	case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
		msg = "unsupported";
		break;

	default:
		msg = va("unknown error (0x%x)", status);
		break;
	}

	ri.Error(ERR_FATAL, "Bad framebuffer setup for '%s': %s\n", glState.currentFBO->name, msg);
	
	return qfalse;
}

fbo_t* R_FBO_Bind(fbo_t* fbo)
{
	fbo_t* old = glState.currentFBO;
	GLuint id = 0;
	if (!glRefConfig.framebufferObject)
		return NULL;
	
	if (glState.currentFBO == fbo)
		return old;

	glState.currentFBO = fbo;
	if (fbo)
		id = fbo->id;

	qglBindFramebufferEXT(GL_FRAMEBUFFER_EXT, id);

	if (fbo)
	{
		if (1)
			R_FBO_Check();
	}

	return old;
}

void R_FBO_BindColorBuffer(fbo_t* fbo, int index)
{
	GL_Bind(fbo->color[index]);
}

fbo_t* R_FBO_CreateEx(const char* name, int numColorBuffers, image_t** colorBuffers, fboZBuffer_t* depth, fboStencilBuffer_t* stencil)
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

fbo_t* R_FBO_CreateSimple(const char* name, image_t* color, fboZBuffer_t* depth, fboStencilBuffer_t* stencil)
{
	return R_FBO_CreateEx(name, color != NULL, &color, depth, stencil);
}

void R_InitFBOs(void)
{
	if (!glRefConfig.framebufferObject)
		return;

	ri.Printf(PRINT_ALL, "------- R_InitFBOs -------\n");

	tr.fbo.full[0] = R_FBO_CreateSimple(
		"main",
		R_CreateImage("*framebuffer", NULL, glConfig.vidWidth, glConfig.vidHeight, qfalse, qfalse, GL_CLAMP_TO_EDGE),
		R_FBO_CreateZBuffer(glConfig.vidWidth, glConfig.vidHeight),
		NULL);

	tr.fbo.full[1] = R_FBO_CreateSimple(
		"postprocess",
		R_CreateImage("*framebuffer", NULL, glConfig.vidWidth, glConfig.vidHeight, qfalse, qfalse, GL_CLAMP_TO_EDGE),
		tr.fbo.full[0]->depth,
		NULL);

	tr.fbo.quarter[0] = R_FBO_CreateSimple(
		"quarter0",
		R_CreateImage("*quarterBuffer0", NULL, glConfig.vidWidth/2, glConfig.vidHeight/2, qfalse, qfalse, GL_CLAMP_TO_EDGE),
		NULL,
		NULL);
	
	tr.fbo.quarter[1] = R_FBO_CreateSimple(
		"quarter1",
		R_CreateImage("*quarterBuffer1", NULL, glConfig.vidWidth/2, glConfig.vidHeight/2, qfalse, qfalse, GL_CLAMP_TO_EDGE),
		NULL,
		NULL);
	
	ri.Printf(PRINT_DEVELOPER, "Created %d FBOs\n", tr.fbo.numFBOs);
}

void R_ShutDownFBOs(void)
{
	if (!glRefConfig.framebufferObject)
		return;

	ri.Printf(PRINT_ALL, "------- R_ShutdownFBOs -------\n");

	R_FBO_Bind(NULL);

	while (tr.fbo.numRenderBuffers>0)
		R_FBO_ReleaseRenderBuffer(tr.fbo.renderBuffers[--tr.fbo.numRenderBuffers]);

	while (tr.fbo.numFBOs>0)
		R_FBO_Release(tr.fbo.fbos[--tr.fbo.numFBOs]);
}

