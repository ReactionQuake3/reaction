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

#ifdef USE_LOCAL_HEADERS
#	include "SDL.h"
#else
#	include <SDL.h>
#endif

#ifdef SMP
#	ifdef USE_LOCAL_HEADERS
#		include "SDL_thread.h"
#	else
#		include <SDL_thread.h>
#	endif
#endif

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../renderer/tr_local.h"
#include "../client/client.h"
#include "../sys/sys_local.h"
#include "sdl_icon.h"

/* Just hack it for now. */
#ifdef MACOS_X
#include <OpenGL/OpenGL.h>
typedef CGLContextObj QGLContext;
#define GLimp_GetCurrentContext() CGLGetCurrentContext()
#define GLimp_SetCurrentContext(ctx) CGLSetCurrentContext(ctx)
#elif defined(_WIN32)
typedef struct
{
	HDC             hDC;		// handle to device context
	HGLRC           hGLRC;		// handle to GL rendering context
} QGLContext_t;
typedef QGLContext_t QGLContext;
#else
typedef void *QGLContext;
#define GLimp_GetCurrentContext() (NULL)
#define GLimp_SetCurrentContext(ctx)
#endif

static QGLContext opengl_context;

#ifdef _WIN32
#include "SDL_syswm.h"
static QGLContext GLimp_GetCurrentContext(void)
{
	SDL_SysWMinfo   info;

	QGLContext newcontext;

	SDL_VERSION(&info.version);
	if(!SDL_GetWMInfo(&info))
	{
		ri.Printf(PRINT_WARNING, "Failed to obtain HWND from SDL (InputRegistry)");
		newcontext.hDC = 0;
		newcontext.hGLRC = 0;
		return newcontext;
	}

	newcontext.hDC = GetDC(info.window);
	newcontext.hGLRC = info.hglrc;

	return newcontext;
}

#ifdef SMP
static void GLimp_SetCurrentContext(qboolean enable)
{
	if(enable)
		wglMakeCurrent(opengl_context.hDC, opengl_context.hGLRC);
	else
		wglMakeCurrent(opengl_context.hDC, NULL);
}
#endif
#endif

typedef enum
{
	RSERR_OK,

	RSERR_INVALID_FULLSCREEN,
	RSERR_INVALID_MODE,

	RSERR_UNKNOWN
} rserr_t;

static SDL_Surface *screen = NULL;
static const SDL_VideoInfo *videoInfo = NULL;

cvar_t *r_allowSoftwareGL; // Don't abort out if a hardware visual can't be obtained
cvar_t *r_allowResize; // make window resizable
cvar_t *r_centerWindow;
cvar_t *r_sdlDriver;

void (APIENTRYP qglActiveTextureARB) (GLenum texture);
void (APIENTRYP qglClientActiveTextureARB) (GLenum texture);
void (APIENTRYP qglMultiTexCoord2fARB) (GLenum target, GLfloat s, GLfloat t);

void (APIENTRYP qglLockArraysEXT) (GLint first, GLsizei count);
void (APIENTRYP qglUnlockArraysEXT) (void);

// GL_EXT_multi_draw_arrays
void            (APIENTRY * qglMultiDrawArraysEXT) (GLenum mode, GLint *first, GLsizei *count, GLsizei primcount);
void            (APIENTRY * qglMultiDrawElementsEXT) (GLenum mode, const GLsizei *count, GLenum type, const GLvoid **indices, GLsizei primcount);

// GL_ARB_vertex_shader
void            (APIENTRY * qglBindAttribLocationARB) (GLhandleARB programObj, GLuint index, const GLcharARB * name);
void            (APIENTRY * qglGetActiveAttribARB) (GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei * length,
													GLint * size, GLenum * type, GLcharARB * name);
GLint(APIENTRY * qglGetAttribLocationARB) (GLhandleARB programObj, const GLcharARB * name);

// GL_ARB_vertex_program
void            (APIENTRY * qglVertexAttrib4fARB) (GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
void            (APIENTRY * qglVertexAttrib4fvARB) (GLuint, const GLfloat *);
void            (APIENTRY * qglVertexAttribPointerARB) (GLuint index, GLint size, GLenum type, GLboolean normalized,
														GLsizei stride, const GLvoid * pointer);
void            (APIENTRY * qglEnableVertexAttribArrayARB) (GLuint index);
void            (APIENTRY * qglDisableVertexAttribArrayARB) (GLuint index);

// GL_ARB_vertex_buffer_object
void (APIENTRY * qglBindBufferARB) (GLenum target, GLuint buffer);
void (APIENTRY * qglDeleteBuffersARB) (GLsizei n, const GLuint * buffers);
void (APIENTRY * qglGenBuffersARB) (GLsizei n, GLuint * buffers);

GLboolean(APIENTRY * qglIsBufferARB) (GLuint buffer);
void (APIENTRY * qglBufferDataARB) (GLenum target, GLsizeiptrARB size, const GLvoid * data, GLenum usage);
void (APIENTRY * qglBufferSubDataARB) (GLenum target, GLintptrARB offset, GLsizeiptrARB size, const GLvoid * data);
void (APIENTRY * qglGetBufferSubDataARB) (GLenum target, GLintptrARB offset, GLsizeiptrARB size, GLvoid * data);

void (APIENTRY * qglGetBufferParameterivARB) (GLenum target, GLenum pname, GLint * params);
void (APIENTRY * qglGetBufferPointervARB) (GLenum target, GLenum pname, GLvoid * *params);

// GL_ARB_shader_objects
void            (APIENTRY * qglDeleteObjectARB) (GLhandleARB obj);

GLhandleARB(APIENTRY * qglGetHandleARB) (GLenum pname);
void            (APIENTRY * qglDetachObjectARB) (GLhandleARB containerObj, GLhandleARB attachedObj);

GLhandleARB(APIENTRY * qglCreateShaderObjectARB) (GLenum shaderType);
void            (APIENTRY * qglShaderSourceARB) (GLhandleARB shaderObj, GLsizei count, const GLcharARB * *string,
												 const GLint * length);
void            (APIENTRY * qglCompileShaderARB) (GLhandleARB shaderObj);

GLhandleARB(APIENTRY * qglCreateProgramObjectARB) (void);
void            (APIENTRY * qglAttachObjectARB) (GLhandleARB containerObj, GLhandleARB obj);
void            (APIENTRY * qglLinkProgramARB) (GLhandleARB programObj);
void            (APIENTRY * qglUseProgramObjectARB) (GLhandleARB programObj);
void            (APIENTRY * qglValidateProgramARB) (GLhandleARB programObj);
void            (APIENTRY * qglUniform1fARB) (GLint location, GLfloat v0);
void            (APIENTRY * qglUniform2fARB) (GLint location, GLfloat v0, GLfloat v1);
void            (APIENTRY * qglUniform3fARB) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
void            (APIENTRY * qglUniform4fARB) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
void            (APIENTRY * qglUniform1iARB) (GLint location, GLint v0);
void            (APIENTRY * qglUniform2iARB) (GLint location, GLint v0, GLint v1);
void            (APIENTRY * qglUniform3iARB) (GLint location, GLint v0, GLint v1, GLint v2);
void            (APIENTRY * qglUniform4iARB) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
void            (APIENTRY * qglUniform2fvARB) (GLint location, GLsizei count, const GLfloat * value);
void            (APIENTRY * qglUniform3fvARB) (GLint location, GLsizei count, const GLfloat * value);
void            (APIENTRY * qglUniform4fvARB) (GLint location, GLsizei count, const GLfloat * value);
void            (APIENTRY * qglUniform2ivARB) (GLint location, GLsizei count, const GLint * value);
void            (APIENTRY * qglUniform3ivARB) (GLint location, GLsizei count, const GLint * value);
void            (APIENTRY * qglUniform4ivARB) (GLint location, GLsizei count, const GLint * value);
void            (APIENTRY * qglUniformMatrix2fvARB) (GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
void            (APIENTRY * qglUniformMatrix3fvARB) (GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
void            (APIENTRY * qglUniformMatrix4fvARB) (GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
void            (APIENTRY * qglGetObjectParameterfvARB) (GLhandleARB obj, GLenum pname, GLfloat * params);
void            (APIENTRY * qglGetObjectParameterivARB) (GLhandleARB obj, GLenum pname, GLint * params);
void            (APIENTRY * qglGetInfoLogARB) (GLhandleARB obj, GLsizei maxLength, GLsizei * length, GLcharARB * infoLog);
void            (APIENTRY * qglGetAttachedObjectsARB) (GLhandleARB containerObj, GLsizei maxCount, GLsizei * count,
													   GLhandleARB * obj);
GLint(APIENTRY * qglGetUniformLocationARB) (GLhandleARB programObj, const GLcharARB * name);
void            (APIENTRY * qglGetActiveUniformARB) (GLhandleARB programObj, GLuint index, GLsizei maxIndex, GLsizei * length,
													 GLint * size, GLenum * type, GLcharARB * name);
void            (APIENTRY * qglGetUniformfvARB) (GLhandleARB programObj, GLint location, GLfloat * params);
void            (APIENTRY * qglGetUniformivARB) (GLhandleARB programObj, GLint location, GLint * params);
void            (APIENTRY * qglGetShaderSourceARB) (GLhandleARB obj, GLsizei maxLength, GLsizei * length, GLcharARB * source);

#if defined(WIN32)
// WGL_ARB_create_context
HGLRC(APIENTRY * qwglCreateContextAttribsARB) (HDC hdC, HGLRC hShareContext, const int *attribList);
#endif

#if 0 //defined(__linux__)
// GLX_ARB_create_context
GLXContext      (APIENTRY * qglXCreateContextAttribsARB) (Display *dpy, GLXFBConfig config, GLXContext share_context, Bool direct, const int *attrib_list);
#endif

/*
===============
GLimp_Shutdown
===============
*/
void GLimp_Shutdown( void )
{
	IN_Shutdown();

	SDL_QuitSubSystem( SDL_INIT_VIDEO );
	screen = NULL;

	Com_Memset( &glConfig, 0, sizeof( glConfig ) );
	Com_Memset( &glRefConfig, 0, sizeof( glRefConfig ) );
	Com_Memset( &glState, 0, sizeof( glState ) );
}

/*
===============
GLimp_Minimize

Minimize the game so that user is back at the desktop
===============
*/
void GLimp_Minimize(void)
{
	SDL_WM_IconifyWindow();
}


/*
===============
GLimp_LogComment
===============
*/
void GLimp_LogComment( char *comment )
{
	//ri.Printf(PRINT_ALL, comment);
}

/*
===============
GLimp_CompareModes
===============
*/
static int GLimp_CompareModes( const void *a, const void *b )
{
	const float ASPECT_EPSILON = 0.001f;
	SDL_Rect *modeA = *(SDL_Rect **)a;
	SDL_Rect *modeB = *(SDL_Rect **)b;
	float aspectA = (float)modeA->w / (float)modeA->h;
	float aspectB = (float)modeB->w / (float)modeB->h;
	int areaA = modeA->w * modeA->h;
	int areaB = modeB->w * modeB->h;
	float aspectDiffA = fabs( aspectA - displayAspect );
	float aspectDiffB = fabs( aspectB - displayAspect );
	float aspectDiffsDiff = aspectDiffA - aspectDiffB;

	if( aspectDiffsDiff > ASPECT_EPSILON )
		return 1;
	else if( aspectDiffsDiff < -ASPECT_EPSILON )
		return -1;
	else
		return areaA - areaB;
}


/*
===============
GLimp_DetectAvailableModes
===============
*/
static void GLimp_DetectAvailableModes(void)
{
	char buf[ MAX_STRING_CHARS ] = { 0 };
	SDL_Rect **modes;
	int numModes;
	int i;

	modes = SDL_ListModes( videoInfo->vfmt, SDL_OPENGL | SDL_FULLSCREEN );

	if( !modes )
	{
		ri.Printf( PRINT_WARNING, "Can't get list of available modes\n" );
		return;
	}

	if( modes == (SDL_Rect **)-1 )
	{
		ri.Printf( PRINT_ALL, "Display supports any resolution\n" );
		return; // can set any resolution
	}

	for( numModes = 0; modes[ numModes ]; numModes++ );

	if( numModes > 1 )
		qsort( modes, numModes, sizeof( SDL_Rect* ), GLimp_CompareModes );

	for( i = 0; i < numModes; i++ )
	{
		const char *newModeString = va( "%ux%u ", modes[ i ]->w, modes[ i ]->h );

		if( strlen( newModeString ) < (int)sizeof( buf ) - strlen( buf ) )
			Q_strcat( buf, sizeof( buf ), newModeString );
		else
			ri.Printf( PRINT_WARNING, "Skipping mode %ux%x, buffer too small\n", modes[i]->w, modes[i]->h );
	}

	if( *buf )
	{
		buf[ strlen( buf ) - 1 ] = 0;
		ri.Printf( PRINT_ALL, "Available modes: '%s'\n", buf );
		ri.Cvar_Set( "r_availableModes", buf );
	}
}

/*
===============
GLimp_SetMode
===============
*/
static int GLimp_SetMode(int mode, qboolean fullscreen, qboolean noborder)
{
	const char*   glstring;
	int sdlcolorbits;
	int colorbits, depthbits, stencilbits;
	int tcolorbits, tdepthbits, tstencilbits;
	int samples;
	int i = 0;
	SDL_Surface *vidscreen = NULL;
	Uint32 flags = SDL_OPENGL;

	ri.Printf( PRINT_ALL, "Initializing OpenGL display\n");

	if ( r_allowResize->integer )
		flags |= SDL_RESIZABLE;

	if( videoInfo == NULL )
	{
		static SDL_VideoInfo sVideoInfo;
		static SDL_PixelFormat sPixelFormat;

		videoInfo = SDL_GetVideoInfo( );

		// Take a copy of the videoInfo
		Com_Memcpy( &sPixelFormat, videoInfo->vfmt, sizeof( SDL_PixelFormat ) );
		sPixelFormat.palette = NULL; // Should already be the case
		Com_Memcpy( &sVideoInfo, videoInfo, sizeof( SDL_VideoInfo ) );
		sVideoInfo.vfmt = &sPixelFormat;
		videoInfo = &sVideoInfo;

		if( videoInfo->current_h > 0 )
		{
			// Guess the display aspect ratio through the desktop resolution
			// by assuming (relatively safely) that it is set at or close to
			// the display's native aspect ratio
			displayAspect = (float)videoInfo->current_w / (float)videoInfo->current_h;

			ri.Printf( PRINT_ALL, "Estimated display aspect: %.3f\n", displayAspect );
		}
		else
		{
			ri.Printf( PRINT_ALL,
					"Cannot estimate display aspect, assuming 1.333\n" );
		}
	}

	ri.Printf (PRINT_ALL, "...setting mode %d:", mode );

	if (mode == -2)
	{
		glConfig.vidWidth = videoInfo->current_w;
		glConfig.vidHeight = videoInfo->current_h;
		glConfig.windowAspect = displayAspect;
		fullscreen = qtrue;
		noborder = qtrue;
	}
	else if ( !R_GetModeInfo( &glConfig.vidWidth, &glConfig.vidHeight, &glConfig.windowAspect, mode ) )
	{
		ri.Printf( PRINT_ALL, " invalid mode\n" );
		return RSERR_INVALID_MODE;
	}
	ri.Printf( PRINT_ALL, " %d %d\n", glConfig.vidWidth, glConfig.vidHeight);

	if (fullscreen)
	{
		flags |= SDL_FULLSCREEN;
		glConfig.isFullscreen = qtrue;
	}
	else
	{
		if (noborder)
			flags |= SDL_NOFRAME;

		glConfig.isFullscreen = qfalse;
	}

	colorbits = r_colorbits->value;
	if ((!colorbits) || (colorbits >= 32))
		colorbits = 24;

	if (!r_depthbits->value)
		depthbits = 24;
	else
		depthbits = r_depthbits->value;
	stencilbits = r_stencilbits->value;
	samples = r_ext_multisample->value;

	for (i = 0; i < 16; i++)
	{
		// 0 - default
		// 1 - minus colorbits
		// 2 - minus depthbits
		// 3 - minus stencil
		if ((i % 4) == 0 && i)
		{
			// one pass, reduce
			switch (i / 4)
			{
				case 2 :
					if (colorbits == 24)
						colorbits = 16;
					break;
				case 1 :
					if (depthbits == 24)
						depthbits = 16;
					else if (depthbits == 16)
						depthbits = 8;
				case 3 :
					if (stencilbits == 24)
						stencilbits = 16;
					else if (stencilbits == 16)
						stencilbits = 8;
			}
		}

		tcolorbits = colorbits;
		tdepthbits = depthbits;
		tstencilbits = stencilbits;

		if ((i % 4) == 3)
		{ // reduce colorbits
			if (tcolorbits == 24)
				tcolorbits = 16;
		}

		if ((i % 4) == 2)
		{ // reduce depthbits
			if (tdepthbits == 24)
				tdepthbits = 16;
			else if (tdepthbits == 16)
				tdepthbits = 8;
		}

		if ((i % 4) == 1)
		{ // reduce stencilbits
			if (tstencilbits == 24)
				tstencilbits = 16;
			else if (tstencilbits == 16)
				tstencilbits = 8;
			else
				tstencilbits = 0;
		}

		sdlcolorbits = 4;
		if (tcolorbits == 24)
			sdlcolorbits = 8;

#ifdef __sgi /* Fix for SGIs grabbing too many bits of color */
		if (sdlcolorbits == 4)
			sdlcolorbits = 0; /* Use minimum size for 16-bit color */

		/* Need alpha or else SGIs choose 36+ bit RGB mode */
		SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 1);
#endif

		SDL_GL_SetAttribute( SDL_GL_RED_SIZE, sdlcolorbits );
		SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, sdlcolorbits );
		SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, sdlcolorbits );
		SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, tdepthbits );
		SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, tstencilbits );

		SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, samples ? 1 : 0 );
		SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, samples );

		if(r_stereoEnabled->integer)
		{
			glConfig.stereoEnabled = qtrue;
			SDL_GL_SetAttribute(SDL_GL_STEREO, 1);
		}
		else
		{
			glConfig.stereoEnabled = qfalse;
			SDL_GL_SetAttribute(SDL_GL_STEREO, 0);
		}
		
		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

#if 0 // See http://bugzilla.icculus.org/show_bug.cgi?id=3526
		// If not allowing software GL, demand accelerated
		if( !r_allowSoftwareGL->integer )
		{
			if( SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 ) < 0 )
			{
				ri.Printf( PRINT_ALL, "Unable to guarantee accelerated "
						"visual with libSDL < 1.2.10\n" );
			}
		}
#endif

		if( SDL_GL_SetAttribute( SDL_GL_SWAP_CONTROL, r_swapInterval->integer ) < 0 )
			ri.Printf( PRINT_ALL, "r_swapInterval requires libSDL >= 1.2.10\n" );

#ifdef USE_ICON
		{
			SDL_Surface *icon = SDL_CreateRGBSurfaceFrom(
					(void *)CLIENT_WINDOW_ICON.pixel_data,
					CLIENT_WINDOW_ICON.width,
					CLIENT_WINDOW_ICON.height,
					CLIENT_WINDOW_ICON.bytes_per_pixel * 8,
					CLIENT_WINDOW_ICON.bytes_per_pixel * CLIENT_WINDOW_ICON.width,
#ifdef Q3_LITTLE_ENDIAN
					0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000
#else
					0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF
#endif
					);

			SDL_WM_SetIcon( icon, NULL );
			SDL_FreeSurface( icon );
		}
#endif

		SDL_WM_SetCaption(CLIENT_WINDOW_TITLE, CLIENT_WINDOW_MIN_TITLE);
		SDL_ShowCursor(0);

		if (!(vidscreen = SDL_SetVideoMode(glConfig.vidWidth, glConfig.vidHeight, colorbits, flags)))
		{
			ri.Printf( PRINT_DEVELOPER, "SDL_SetVideoMode failed: %s\n", SDL_GetError( ) );
			continue;
		}

		opengl_context = GLimp_GetCurrentContext();

		ri.Printf( PRINT_ALL, "Using %d/%d/%d Color bits, %d depth, %d stencil display.\n",
				sdlcolorbits, sdlcolorbits, sdlcolorbits, tdepthbits, tstencilbits);

		glConfig.colorBits = tcolorbits;
		glConfig.depthBits = tdepthbits;
		glConfig.stencilBits = tstencilbits;
		break;
	}

	// try to initialize an OpenGL 3.1 context
#if 0 //defined(WIN32)
	qwglCreateContextAttribsARB = SDL_GL_GetProcAddress("wglCreateContextAttribsARB");
	if(qwglCreateContextAttribsARB)
	{
		int             attribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB,
			3,
			WGL_CONTEXT_MINOR_VERSION_ARB,
			1,
			WGL_CONTEXT_FLAGS_ARB,
			0, //WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			//WGL_CONTEXT_PROFILE_MASK_ARB,
			//WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
			0
		};

		ri.Printf(PRINT_ALL, "Initializing OpenGL 3.1 context...");

		opengl_context.hGLRC = qwglCreateContextAttribsARB(opengl_context.hDC, opengl_context.hGLRC, attribs);
		if(wglMakeCurrent(opengl_context.hDC, opengl_context.hGLRC))
		{
			ri.Printf(PRINT_ALL, " done\n");
		}
		else
		{
			ri.Printf(PRINT_ALL, " failed\n");
		}
	}
#elif 0 //defined(__linux__)

	// TODO

	/*
// GLX_ARB_create_context
#ifndef GLX_ARB_create_context
#define GLX_CONTEXT_DEBUG_BIT_ARB          0x00000001
#define GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x00000002
#define GLX_CONTEXT_MAJOR_VERSION_ARB      0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB      0x2092
#define GLX_CONTEXT_FLAGS_ARB              0x2094

extern GLXContext	(APIENTRY * qglXCreateContextAttribsARB) (Display *dpy, GLXFBConfig config, GLXContext share_context, Bool direct, const int *attrib_list);
*/

	qglXCreateContextAttribsARB = SDL_GL_GetProcAddress("glXCreateContextAttribsARB");
	if(qglXCreateContextAttribsARB)
	{
		int             attribs[3];

		ri.Printf(PRINT_ALL, "Initializing OpenGL 3.0 context...");

		attribs[0] = WGL_CONTEXT_MAJOR_VERSION_ARB;
		attribs[1] = 3;
		attribs[2] = 0;			//terminate first pair

		opengl_context->hGLRC = qglXCreateContextAttribsARB(opengl_context->, attribs);
		if(wglMakeCurrent(opengl_context->hDC, opengl_context->hGLRC))
		{
			ri.Printf(PRINT_ALL, " done\n");
			glConfig.driverType = GLDRV_OPENGL3;
		}
		else
		{
			ri.Printf(PRINT_ALL, " failed\n");
		}
	}
#endif

	GLimp_DetectAvailableModes();

	if (!vidscreen)
	{
		ri.Printf( PRINT_ALL, "Couldn't get a visual\n" );
		return RSERR_INVALID_MODE;
	}

	screen = vidscreen;

	glstring = (char *) qglGetString (GL_RENDERER);
	ri.Printf( PRINT_ALL, "GL_RENDERER: %s\n", glstring );

	return RSERR_OK;
}

/*
===============
GLimp_StartDriverAndSetMode
===============
*/
static qboolean GLimp_StartDriverAndSetMode(int mode, qboolean fullscreen, qboolean noborder)
{
	rserr_t err;

	if (!SDL_WasInit(SDL_INIT_VIDEO))
	{
		char driverName[ 64 ];

		if (SDL_Init(SDL_INIT_VIDEO) == -1)
		{
			ri.Printf( PRINT_ALL, "SDL_Init( SDL_INIT_VIDEO ) FAILED (%s)\n",
					SDL_GetError());
			return qfalse;
		}

		SDL_VideoDriverName( driverName, sizeof( driverName ) - 1 );
		ri.Printf( PRINT_ALL, "SDL using driver \"%s\"\n", driverName );
		Cvar_Set( "r_sdlDriver", driverName );
	}

	if (fullscreen && Cvar_VariableIntegerValue( "in_nograb" ) )
	{
		ri.Printf( PRINT_ALL, "Fullscreen not allowed with in_nograb 1\n");
		ri.Cvar_Set( "r_fullscreen", "0" );
		r_fullscreen->modified = qfalse;
		fullscreen = qfalse;
	}
	
	if (!fullscreen && mode == -2)
	{
		ri.Printf( PRINT_ALL, "Windowed not allowed with r_mode -2\n");
		ri.Cvar_Set( "r_fullscreen", "1" );
		r_fullscreen->modified = qfalse;
		fullscreen = qtrue;
	}
	
	err = GLimp_SetMode(mode, fullscreen, noborder);

	switch ( err )
	{
		case RSERR_INVALID_FULLSCREEN:
			ri.Printf( PRINT_ALL, "...WARNING: fullscreen unavailable in this mode\n" );
			return qfalse;
		case RSERR_INVALID_MODE:
			ri.Printf( PRINT_ALL, "...WARNING: could not set the given mode (%d)\n", mode );
			return qfalse;
		default:
			break;
	}

	return qtrue;
}

static qboolean GLimp_HaveExtension(const char *ext)
{
	const char *ptr = Q_stristr( glConfig.extensions_string, ext );
	if (ptr == NULL)
		return qfalse;
	ptr += strlen(ext);
	return ((*ptr == ' ') || (*ptr == '\0'));  // verify it's complete string.
}


/*
===============
GLimp_InitExtensions
===============
*/
static void GLimp_InitExtensions( void )
{
	if ( !r_allowExtensions->integer )
	{
		ri.Printf( PRINT_ALL, "* IGNORING OPENGL EXTENSIONS *\n" );
		return;
	}

	ri.Printf( PRINT_ALL, "Initializing OpenGL extensions\n" );

	glConfig.textureCompression = TC_NONE;

	// GL_EXT_texture_compression_s3tc
	if ( GLimp_HaveExtension( "GL_ARB_texture_compression" ) &&
	     GLimp_HaveExtension( "GL_EXT_texture_compression_s3tc" ) )
	{
		if ( r_ext_compressed_textures->value )
		{
			glConfig.textureCompression = TC_S3TC_ARB;
			ri.Printf( PRINT_ALL, "...using GL_EXT_texture_compression_s3tc\n" );
		}
		else
		{
			ri.Printf( PRINT_ALL, "...ignoring GL_EXT_texture_compression_s3tc\n" );
		}
	}
	else
	{
		ri.Printf( PRINT_ALL, "...GL_EXT_texture_compression_s3tc not found\n" );
	}

	// GL_S3_s3tc ... legacy extension before GL_EXT_texture_compression_s3tc.
	if (glConfig.textureCompression == TC_NONE)
	{
		if ( GLimp_HaveExtension( "GL_S3_s3tc" ) )
		{
			if ( r_ext_compressed_textures->value )
			{
				glConfig.textureCompression = TC_S3TC;
				ri.Printf( PRINT_ALL, "...using GL_S3_s3tc\n" );
			}
			else
			{
				ri.Printf( PRINT_ALL, "...ignoring GL_S3_s3tc\n" );
			}
		}
		else
		{
			ri.Printf( PRINT_ALL, "...GL_S3_s3tc not found\n" );
		}
	}


	// GL_EXT_texture_env_add
	glConfig.textureEnvAddAvailable = qfalse;
	if ( GLimp_HaveExtension( "EXT_texture_env_add" ) )
	{
		if ( r_ext_texture_env_add->integer )
		{
			glConfig.textureEnvAddAvailable = qtrue;
			ri.Printf( PRINT_ALL, "...using GL_EXT_texture_env_add\n" );
		}
		else
		{
			glConfig.textureEnvAddAvailable = qfalse;
			ri.Printf( PRINT_ALL, "...ignoring GL_EXT_texture_env_add\n" );
		}
	}
	else
	{
		ri.Printf( PRINT_ALL, "...GL_EXT_texture_env_add not found\n" );
	}

	// GL_ARB_multitexture
	qglMultiTexCoord2fARB = NULL;
	qglActiveTextureARB = NULL;
	qglClientActiveTextureARB = NULL;
	if ( GLimp_HaveExtension( "GL_ARB_multitexture" ) )
	{
		if ( r_ext_multitexture->value )
		{
			qglMultiTexCoord2fARB = SDL_GL_GetProcAddress( "glMultiTexCoord2fARB" );
			qglActiveTextureARB = SDL_GL_GetProcAddress( "glActiveTextureARB" );
			qglClientActiveTextureARB = SDL_GL_GetProcAddress( "glClientActiveTextureARB" );

			if ( qglActiveTextureARB )
			{
				GLint glint = 0;
				qglGetIntegerv( GL_MAX_TEXTURE_UNITS_ARB, &glint );
				glConfig.numTextureUnits = (int) glint;
				if ( glConfig.numTextureUnits > 1 )
				{
					ri.Printf( PRINT_ALL, "...using GL_ARB_multitexture\n" );
				}
				else
				{
					qglMultiTexCoord2fARB = NULL;
					qglActiveTextureARB = NULL;
					qglClientActiveTextureARB = NULL;
					ri.Printf( PRINT_ALL, "...not using GL_ARB_multitexture, < 2 texture units\n" );
				}
			}
		}
		else
		{
			ri.Printf( PRINT_ALL, "...ignoring GL_ARB_multitexture\n" );
		}
	}
	else
	{
		ri.Printf( PRINT_ALL, "...GL_ARB_multitexture not found\n" );
	}

	// GL_EXT_compiled_vertex_array
	if ( GLimp_HaveExtension( "GL_EXT_compiled_vertex_array" ) )
	{
		if ( r_ext_compiled_vertex_array->value )
		{
			ri.Printf( PRINT_ALL, "...using GL_EXT_compiled_vertex_array\n" );
			qglLockArraysEXT = ( void ( APIENTRY * )( GLint, GLint ) ) SDL_GL_GetProcAddress( "glLockArraysEXT" );
			qglUnlockArraysEXT = ( void ( APIENTRY * )( void ) ) SDL_GL_GetProcAddress( "glUnlockArraysEXT" );
			if (!qglLockArraysEXT || !qglUnlockArraysEXT)
			{
				ri.Error (ERR_FATAL, "bad getprocaddress");
			}
		}
		else
		{
			ri.Printf( PRINT_ALL, "...ignoring GL_EXT_compiled_vertex_array\n" );
		}
	}
	else
	{
		ri.Printf( PRINT_ALL, "...GL_EXT_compiled_vertex_array not found\n" );
	}

	glRefConfig.textureFilterAnisotropic = qfalse;
	if ( GLimp_HaveExtension( "GL_EXT_texture_filter_anisotropic" ) )
	{
		if ( r_ext_texture_filter_anisotropic->integer ) {
			qglGetIntegerv( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, (GLint *)&glRefConfig.maxAnisotropy );
			if ( glRefConfig.maxAnisotropy <= 0 ) {
				ri.Printf( PRINT_ALL, "...GL_EXT_texture_filter_anisotropic not properly supported!\n" );
				glRefConfig.maxAnisotropy = 0;
			}
			else
			{
				ri.Printf( PRINT_ALL, "...using GL_EXT_texture_filter_anisotropic (max: %i)\n", glRefConfig.maxAnisotropy );
				glRefConfig.textureFilterAnisotropic = qtrue;
			}
		}
		else
		{
			ri.Printf( PRINT_ALL, "...ignoring GL_EXT_texture_filter_anisotropic\n" );
		}
	}
	else
	{
		ri.Printf( PRINT_ALL, "...GL_EXT_texture_filter_anisotropic not found\n" );
	}

	// GL_EXT_multi_draw_arrays
	glRefConfig.multiDrawArrays = qfalse;
	qglMultiDrawArraysEXT = NULL;
	qglMultiDrawElementsEXT = NULL;
	if( GLimp_HaveExtension( "GL_EXT_multi_draw_arrays"))
	{
		qglMultiDrawArraysEXT = (PFNGLMULTIDRAWARRAYSEXTPROC) SDL_GL_GetProcAddress("glMultiDrawArraysEXT");
		qglMultiDrawElementsEXT = (PFNGLMULTIDRAWELEMENTSEXTPROC) SDL_GL_GetProcAddress("glMultiDrawElementsEXT");
		ri.Printf(PRINT_ALL, "...using GL_EXT_multi_draw_arrays\n");
		glRefConfig.multiDrawArrays = qtrue;
	}
	else
	{
		ri.Printf(PRINT_ALL, "...GL_EXT_multi_draw_arrays not found\n");
	}
	
	// GL_ARB_vertex_program
	glRefConfig.vertexProgram = qfalse;
	qglVertexAttrib4fARB = NULL;
	qglVertexAttrib4fvARB = NULL;
	qglVertexAttribPointerARB = NULL;
	qglEnableVertexAttribArrayARB = NULL;
	qglDisableVertexAttribArrayARB = NULL;
	if( GLimp_HaveExtension( "GL_ARB_vertex_program"))
	{
		qglVertexAttrib4fARB = (PFNGLVERTEXATTRIB4FARBPROC) SDL_GL_GetProcAddress("glVertexAttrib4fARB");
		qglVertexAttrib4fvARB = (PFNGLVERTEXATTRIB4FVARBPROC) SDL_GL_GetProcAddress("glVertexAttrib4fvARB");
		qglVertexAttribPointerARB = (PFNGLVERTEXATTRIBPOINTERARBPROC) SDL_GL_GetProcAddress("glVertexAttribPointerARB");
		qglEnableVertexAttribArrayARB =
			(PFNGLENABLEVERTEXATTRIBARRAYARBPROC) SDL_GL_GetProcAddress("glEnableVertexAttribArrayARB");
		qglDisableVertexAttribArrayARB =
			(PFNGLDISABLEVERTEXATTRIBARRAYARBPROC) SDL_GL_GetProcAddress("glDisableVertexAttribArrayARB");
		ri.Printf(PRINT_ALL, "...using GL_ARB_vertex_program\n");
		glRefConfig.vertexProgram = qtrue;
	}
	else
	{
		ri.Printf(PRINT_ALL, "...GL_ARB_vertex_program not found\n");
	}
	
	// GL_ARB_vertex_buffer_object
	glRefConfig.vertexBufferObject = qfalse;
	qglBindBufferARB = NULL;
	qglDeleteBuffersARB = NULL;
	qglGenBuffersARB = NULL;
	qglIsBufferARB = NULL;
	qglBufferDataARB = NULL;
	qglBufferSubDataARB = NULL;
	qglGetBufferSubDataARB = NULL;
	qglGetBufferParameterivARB = NULL;
	qglGetBufferPointervARB = NULL;
	if( GLimp_HaveExtension( "GL_ARB_vertex_buffer_object"))
	{
		qglBindBufferARB = (PFNGLBINDBUFFERARBPROC) SDL_GL_GetProcAddress("glBindBufferARB");
		qglDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) SDL_GL_GetProcAddress("glDeleteBuffersARB");
		qglGenBuffersARB = (PFNGLGENBUFFERSARBPROC) SDL_GL_GetProcAddress("glGenBuffersARB");
		qglIsBufferARB = (PFNGLISBUFFERARBPROC) SDL_GL_GetProcAddress("glIsBufferARB");
		qglBufferDataARB = (PFNGLBUFFERDATAARBPROC) SDL_GL_GetProcAddress("glBufferDataARB");
		qglBufferSubDataARB = (PFNGLBUFFERSUBDATAARBPROC) SDL_GL_GetProcAddress("glBufferSubDataARB");
		qglGetBufferSubDataARB = (PFNGLGETBUFFERSUBDATAARBPROC) SDL_GL_GetProcAddress("glGetBufferSubDataARB");
		qglGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVARBPROC) SDL_GL_GetProcAddress("glGetBufferParameterivARB");
		qglGetBufferPointervARB = (PFNGLGETBUFFERPOINTERVARBPROC) SDL_GL_GetProcAddress("glGetBufferPointervARB");
		ri.Printf(PRINT_ALL, "...using GL_ARB_vertex_buffer_object\n");
		glRefConfig.vertexBufferObject = qtrue;
	}
	else
	{
		ri.Printf(PRINT_ALL, "...GL_ARB_vertex_buffer_object not found\n");
	}

	// GL_ARB_shader_objects
	glRefConfig.shaderObjects = qfalse;
	qglDeleteObjectARB = NULL;
	qglGetHandleARB = NULL;
	qglDetachObjectARB = NULL;
	qglCreateShaderObjectARB = NULL;
	qglShaderSourceARB = NULL;
	qglCompileShaderARB = NULL;
	qglCreateProgramObjectARB = NULL;
	qglAttachObjectARB = NULL;
	qglLinkProgramARB = NULL;
	qglUseProgramObjectARB = NULL;
	qglValidateProgramARB = NULL;
	qglUniform1fARB = NULL;
	qglUniform2fARB = NULL;
	qglUniform3fARB = NULL;
	qglUniform4fARB = NULL;
	qglUniform1iARB = NULL;
	qglUniform2iARB = NULL;
	qglUniform3iARB = NULL;
	qglUniform4iARB = NULL;
	qglUniform2fvARB = NULL;
	qglUniform3fvARB = NULL;
	qglUniform4fvARB = NULL;
	qglUniform2ivARB = NULL;
	qglUniform3ivARB = NULL;
	qglUniform4ivARB = NULL;
	qglUniformMatrix2fvARB = NULL;
	qglUniformMatrix3fvARB = NULL;
	qglUniformMatrix4fvARB = NULL;
	qglGetObjectParameterfvARB = NULL;
	qglGetObjectParameterivARB = NULL;
	qglGetInfoLogARB = NULL;
	qglGetAttachedObjectsARB = NULL;
	qglGetUniformLocationARB = NULL;
	qglGetActiveUniformARB = NULL;
	qglGetUniformfvARB = NULL;
	qglGetUniformivARB = NULL;
	qglGetShaderSourceARB = NULL;
	if( GLimp_HaveExtension( "GL_ARB_shader_objects"))
	{
		qglDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC) SDL_GL_GetProcAddress("glDeleteObjectARB");
		qglGetHandleARB = (PFNGLGETHANDLEARBPROC) SDL_GL_GetProcAddress("glGetHandleARB");
		qglDetachObjectARB = (PFNGLDETACHOBJECTARBPROC) SDL_GL_GetProcAddress("glDetachObjectARB");
		qglCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC) SDL_GL_GetProcAddress("glCreateShaderObjectARB");
		qglShaderSourceARB = (PFNGLSHADERSOURCEARBPROC) SDL_GL_GetProcAddress("glShaderSourceARB");
		qglCompileShaderARB = (PFNGLCOMPILESHADERARBPROC) SDL_GL_GetProcAddress("glCompileShaderARB");
		qglCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC) SDL_GL_GetProcAddress("glCreateProgramObjectARB");
		qglAttachObjectARB = (PFNGLATTACHOBJECTARBPROC) SDL_GL_GetProcAddress("glAttachObjectARB");
		qglLinkProgramARB = (PFNGLLINKPROGRAMARBPROC) SDL_GL_GetProcAddress("glLinkProgramARB");
		qglUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC) SDL_GL_GetProcAddress("glUseProgramObjectARB");
		qglValidateProgramARB = (PFNGLVALIDATEPROGRAMARBPROC) SDL_GL_GetProcAddress("glValidateProgramARB");
		qglUniform1fARB = (PFNGLUNIFORM1FARBPROC) SDL_GL_GetProcAddress("glUniform1fARB");
		qglUniform2fARB = (PFNGLUNIFORM2FARBPROC) SDL_GL_GetProcAddress("glUniform2fARB");
		qglUniform3fARB = (PFNGLUNIFORM3FARBPROC) SDL_GL_GetProcAddress("glUniform3fARB");
		qglUniform4fARB = (PFNGLUNIFORM4FARBPROC) SDL_GL_GetProcAddress("glUniform4fARB");
		qglUniform1iARB = (PFNGLUNIFORM1IARBPROC) SDL_GL_GetProcAddress("glUniform1iARB");
		qglUniform2iARB = (PFNGLUNIFORM2IARBPROC) SDL_GL_GetProcAddress("glUniform2iARB");
		qglUniform3iARB = (PFNGLUNIFORM3IARBPROC) SDL_GL_GetProcAddress("glUniform3iARB");
		qglUniform4iARB = (PFNGLUNIFORM4IARBPROC) SDL_GL_GetProcAddress("glUniform4iARB");
		qglUniform2fvARB = (PFNGLUNIFORM2FVARBPROC) SDL_GL_GetProcAddress("glUniform2fvARB");
		qglUniform3fvARB = (PFNGLUNIFORM3FVARBPROC) SDL_GL_GetProcAddress("glUniform3fvARB");
		qglUniform4fvARB = (PFNGLUNIFORM4FVARBPROC) SDL_GL_GetProcAddress("glUniform4fvARB");
		qglUniform2ivARB = (PFNGLUNIFORM2IVARBPROC) SDL_GL_GetProcAddress("glUniform2ivARB");
		qglUniform3ivARB = (PFNGLUNIFORM3IVARBPROC) SDL_GL_GetProcAddress("glUniform3ivARB");
		qglUniform4ivARB = (PFNGLUNIFORM4IVARBPROC) SDL_GL_GetProcAddress("glUniform4ivARB");
		qglUniformMatrix2fvARB = (PFNGLUNIFORMMATRIX2FVARBPROC) SDL_GL_GetProcAddress("glUniformMatrix2fvARB");
		qglUniformMatrix3fvARB = (PFNGLUNIFORMMATRIX3FVARBPROC) SDL_GL_GetProcAddress("glUniformMatrix3fvARB");
		qglUniformMatrix4fvARB = (PFNGLUNIFORMMATRIX4FVARBPROC) SDL_GL_GetProcAddress("glUniformMatrix4fvARB");
		qglGetObjectParameterfvARB = (PFNGLGETOBJECTPARAMETERFVARBPROC) SDL_GL_GetProcAddress("glGetObjectParameterfvARB");
		qglGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC) SDL_GL_GetProcAddress("glGetObjectParameterivARB");
		qglGetInfoLogARB = (PFNGLGETINFOLOGARBPROC) SDL_GL_GetProcAddress("glGetInfoLogARB");
		qglGetAttachedObjectsARB = (PFNGLGETATTACHEDOBJECTSARBPROC) SDL_GL_GetProcAddress("glGetAttachedObjectsARB");
		qglGetUniformLocationARB = (PFNGLGETUNIFORMLOCATIONARBPROC) SDL_GL_GetProcAddress("glGetUniformLocationARB");
		qglGetActiveUniformARB = (PFNGLGETACTIVEUNIFORMARBPROC) SDL_GL_GetProcAddress("glGetActiveUniformARB");
		qglGetUniformfvARB = (PFNGLGETUNIFORMFVARBPROC) SDL_GL_GetProcAddress("glGetUniformfvARB");
		qglGetUniformivARB = (PFNGLGETUNIFORMIVARBPROC) SDL_GL_GetProcAddress("glGetUniformivARB");
		qglGetShaderSourceARB = (PFNGLGETSHADERSOURCEARBPROC) SDL_GL_GetProcAddress("glGetShaderSourceARB");
		ri.Printf(PRINT_ALL, "...using GL_ARB_shader_objects\n");
		glRefConfig.shaderObjects = qtrue;
	}
	else
	{
		ri.Printf(PRINT_ALL, "...GL_ARB_shader_objects not found\n");
	}

	// GL_ARB_vertex_shader
	glRefConfig.vertexShader = qfalse;
	qglBindAttribLocationARB = NULL;
	qglGetActiveAttribARB = NULL;
	qglGetAttribLocationARB = NULL;
	if( GLimp_HaveExtension( "GL_ARB_vertex_shader"))
	{
		int				reservedComponents;

		//qglGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS_ARB, &glConfig.maxVertexUniforms);
		//qglGetIntegerv(GL_MAX_VARYING_FLOATS_ARB, &glConfig.maxVaryingFloats);
		//qglGetIntegerv(GL_MAX_VERTEX_ATTRIBS_ARB, &glConfig.maxVertexAttribs);

		reservedComponents = 16 * 10; // approximation how many uniforms we have besides the bone matrices

#if 0
		if(glConfig.driverType == GLDRV_MESA)
		{
			// HACK
			// restrict to number of vertex uniforms to 512 because of:
			// xreal.x86_64: nv50_program.c:4181: nv50_program_validate_data: Assertion `p->param_nr <= 512' failed

			glConfig.maxVertexUniforms = Q_bound(0, glConfig.maxVertexUniforms, 512);
		}
#endif

		//glConfig.maxVertexSkinningBones = (int) Q_bound(0.0, (Q_max(glConfig.maxVertexUniforms - reservedComponents, 0) / 16), MAX_BONES);
		//glConfig.vboVertexSkinningAvailable = r_vboVertexSkinning->integer && ((glConfig.maxVertexSkinningBones >= 12) ? qtrue : qfalse);

		qglBindAttribLocationARB = (PFNGLBINDATTRIBLOCATIONARBPROC) SDL_GL_GetProcAddress("glBindAttribLocationARB");
		qglGetActiveAttribARB = (PFNGLGETACTIVEATTRIBARBPROC) SDL_GL_GetProcAddress("glGetActiveAttribARB");
		qglGetAttribLocationARB = (PFNGLGETATTRIBLOCATIONARBPROC) SDL_GL_GetProcAddress("glGetAttribLocationARB");
		ri.Printf(PRINT_ALL, "...using GL_ARB_vertex_shader\n");
		glRefConfig.vertexShader = qtrue;
	}
	else
	{
		ri.Printf(PRINT_ALL, "...GL_ARB_vertex_shader not found\n");
	}

	glRefConfig.glsl = glRefConfig.vertexProgram && glRefConfig.shaderObjects && glRefConfig.vertexShader;

}

#define R_MODE_FALLBACK 3 // 640 * 480

/*
===============
GLimp_Init

This routine is responsible for initializing the OS specific portions
of OpenGL
===============
*/
void GLimp_Init( void )
{
	r_allowSoftwareGL = ri.Cvar_Get( "r_allowSoftwareGL", "0", CVAR_LATCH );
	r_sdlDriver = ri.Cvar_Get( "r_sdlDriver", "", CVAR_ROM );
	r_allowResize = ri.Cvar_Get( "r_allowResize", "0", CVAR_ARCHIVE );
	r_centerWindow = ri.Cvar_Get( "r_centerWindow", "0", CVAR_ARCHIVE );

	if( Cvar_VariableIntegerValue( "com_abnormalExit" ) )
	{
		ri.Cvar_Set( "r_mode", va( "%d", R_MODE_FALLBACK ) );
		ri.Cvar_Set( "r_fullscreen", "0" );
		ri.Cvar_Set( "r_centerWindow", "0" );
		ri.Cvar_Set( "com_abnormalExit", "0" );
	}

	Sys_SetEnv( "SDL_VIDEO_CENTERED", r_centerWindow->integer ? "1" : "" );

	Sys_GLimpInit( );

	// Create the window and set up the context
	if(GLimp_StartDriverAndSetMode(r_mode->integer, r_fullscreen->integer, r_noborder->integer))
		goto success;

	// Try again, this time in a platform specific "safe mode"
	Sys_GLimpSafeInit( );

	if(GLimp_StartDriverAndSetMode(r_mode->integer, r_fullscreen->integer, qfalse))
		goto success;

	// Finally, try the default screen resolution
	if( r_mode->integer != R_MODE_FALLBACK )
	{
		ri.Printf( PRINT_ALL, "Setting r_mode %d failed, falling back on r_mode %d\n",
				r_mode->integer, R_MODE_FALLBACK );

		if(GLimp_StartDriverAndSetMode(R_MODE_FALLBACK, qfalse, qfalse))
			goto success;
	}

	// Nothing worked, give up
	ri.Error( ERR_FATAL, "GLimp_Init() - could not load OpenGL subsystem\n" );

success:
	// This values force the UI to disable driver selection
	glConfig.driverType = GLDRV_ICD;
	glConfig.hardwareType = GLHW_GENERIC;
	glConfig.deviceSupportsGamma = SDL_SetGamma( 1.0f, 1.0f, 1.0f ) >= 0;

	// Mysteriously, if you use an NVidia graphics card and multiple monitors,
	// SDL_SetGamma will incorrectly return false... the first time; ask
	// again and you get the correct answer. This is a suspected driver bug, see
	// http://bugzilla.icculus.org/show_bug.cgi?id=4316
	glConfig.deviceSupportsGamma = SDL_SetGamma( 1.0f, 1.0f, 1.0f ) >= 0;

	// get our config strings
	{
		char *string;
		
		string = (char *) qglGetString (GL_VENDOR);
		if (string)
			Q_strncpyz( glConfig.vendor_string, (char *) qglGetString (GL_VENDOR), sizeof( glConfig.vendor_string ) );
		else
			glConfig.vendor_string[0] = '\0';

		string = (char *) qglGetString (GL_RENDERER);
		if (string)
			Q_strncpyz( glConfig.renderer_string, (char *) qglGetString (GL_RENDERER), sizeof( glConfig.renderer_string ) );
		else
			glConfig.renderer_string[0] = '\0';

		if (*glConfig.renderer_string && glConfig.renderer_string[strlen(glConfig.renderer_string) - 1] == '\n')
			glConfig.renderer_string[strlen(glConfig.renderer_string) - 1] = 0;

		string = (char *) qglGetString(GL_VERSION);
		if (string)
			Q_strncpyz( glConfig.version_string, (char *) qglGetString (GL_VERSION), sizeof( glConfig.version_string ) );
		else
			glConfig.version_string[0] = '\0';
	
		string = (char *) qglGetString (GL_EXTENSIONS);
		if (string)
		{
			Q_strncpyz( glConfig.extensions_string, string, sizeof( glConfig.extensions_string ) );
		}
		else
		{
			glConfig.extensions_string[0] = '\0';
		}
	}

	// initialize extensions
	GLimp_InitExtensions( );

	ri.Cvar_Get( "r_availableModes", "", CVAR_ROM );

	// This depends on SDL_INIT_VIDEO, hence having it here
	IN_Init( );
}


/*
===============
GLimp_EndFrame

Responsible for doing a swapbuffers
===============
*/
void GLimp_EndFrame( void )
{
	// don't flip if drawing to front buffer
	if ( Q_stricmp( r_drawBuffer->string, "GL_FRONT" ) != 0 )
	{
		SDL_GL_SwapBuffers();
	}

	if( r_fullscreen->modified )
	{
		qboolean    fullscreen;
		qboolean    needToToggle = qtrue;
		qboolean    sdlToggled = qfalse;
		SDL_Surface *s = SDL_GetVideoSurface( );

		if( s )
		{
			// Find out the current state
			fullscreen = !!( s->flags & SDL_FULLSCREEN );
				
			if( r_fullscreen->integer && Cvar_VariableIntegerValue( "in_nograb" ) )
			{
				ri.Printf( PRINT_ALL, "Fullscreen not allowed with in_nograb 1\n");
				ri.Cvar_Set( "r_fullscreen", "0" );
				r_fullscreen->modified = qfalse;
			}

			// Is the state we want different from the current state?
			needToToggle = !!r_fullscreen->integer != fullscreen;

			if( needToToggle )
				sdlToggled = SDL_WM_ToggleFullScreen( s );
		}

		if( needToToggle )
		{
			// SDL_WM_ToggleFullScreen didn't work, so do it the slow way
			if( !sdlToggled )
				Cbuf_AddText( "vid_restart" );

			IN_Restart( );
		}

		r_fullscreen->modified = qfalse;
	}
}



#ifdef SMP
/*
===========================================================

SMP acceleration

===========================================================
*/

/*
 * I have no idea if this will even work...most platforms don't offer
 * thread-safe OpenGL libraries, and it looks like the original Linux
 * code counted on each thread claiming the GL context with glXMakeCurrent(),
 * which you can't currently do in SDL. We'll just have to hope for the best.
 */

static SDL_mutex *smpMutex = NULL;
static SDL_cond *renderCommandsEvent = NULL;
static SDL_cond *renderCompletedEvent = NULL;
static void (*glimpRenderThread)( void ) = NULL;
static SDL_Thread *renderThread = NULL;

/*
===============
GLimp_ShutdownRenderThread
===============
*/
static void GLimp_ShutdownRenderThread(void)
{
	if (smpMutex != NULL)
	{
		SDL_DestroyMutex(smpMutex);
		smpMutex = NULL;
	}

	if (renderCommandsEvent != NULL)
	{
		SDL_DestroyCond(renderCommandsEvent);
		renderCommandsEvent = NULL;
	}

	if (renderCompletedEvent != NULL)
	{
		SDL_DestroyCond(renderCompletedEvent);
		renderCompletedEvent = NULL;
	}

	glimpRenderThread = NULL;
}

/*
===============
GLimp_RenderThreadWrapper
===============
*/
static int GLimp_RenderThreadWrapper( void *arg )
{
	Com_Printf( "Render thread starting\n" );

	glimpRenderThread();

	GLimp_SetCurrentContext(NULL);

	Com_Printf( "Render thread terminating\n" );

	return 0;
}

/*
===============
GLimp_SpawnRenderThread
===============
*/
qboolean GLimp_SpawnRenderThread( void (*function)( void ) )
{
	static qboolean warned = qfalse;
	if (!warned)
	{
		Com_Printf("WARNING: You enable r_smp at your own risk!\n");
		warned = qtrue;
	}

#ifndef MACOS_X
	return qfalse;  /* better safe than sorry for now. */
#endif

	if (renderThread != NULL)  /* hopefully just a zombie at this point... */
	{
		Com_Printf("Already a render thread? Trying to clean it up...\n");
		SDL_WaitThread(renderThread, NULL);
		renderThread = NULL;
		GLimp_ShutdownRenderThread();
	}

	smpMutex = SDL_CreateMutex();
	if (smpMutex == NULL)
	{
		Com_Printf( "smpMutex creation failed: %s\n", SDL_GetError() );
		GLimp_ShutdownRenderThread();
		return qfalse;
	}

	renderCommandsEvent = SDL_CreateCond();
	if (renderCommandsEvent == NULL)
	{
		Com_Printf( "renderCommandsEvent creation failed: %s\n", SDL_GetError() );
		GLimp_ShutdownRenderThread();
		return qfalse;
	}

	renderCompletedEvent = SDL_CreateCond();
	if (renderCompletedEvent == NULL)
	{
		Com_Printf( "renderCompletedEvent creation failed: %s\n", SDL_GetError() );
		GLimp_ShutdownRenderThread();
		return qfalse;
	}

	glimpRenderThread = function;
	renderThread = SDL_CreateThread(GLimp_RenderThreadWrapper, NULL);
	if ( renderThread == NULL )
	{
		ri.Printf( PRINT_ALL, "SDL_CreateThread() returned %s", SDL_GetError() );
		GLimp_ShutdownRenderThread();
		return qfalse;
	}
	else
	{
		// tma 01/09/07: don't think this is necessary anyway?
		//
		// !!! FIXME: No detach API available in SDL!
		//ret = pthread_detach( renderThread );
		//if ( ret ) {
		//ri.Printf( PRINT_ALL, "pthread_detach returned %d: %s", ret, strerror( ret ) );
		//}
	}

	return qtrue;
}

static volatile void    *smpData = NULL;
static volatile qboolean smpDataReady;

/*
===============
GLimp_RendererSleep
===============
*/
void *GLimp_RendererSleep( void )
{
	void  *data = NULL;

	GLimp_SetCurrentContext(NULL);

	SDL_LockMutex(smpMutex);
	{
		smpData = NULL;
		smpDataReady = qfalse;

		// after this, the front end can exit GLimp_FrontEndSleep
		SDL_CondSignal(renderCompletedEvent);

		while ( !smpDataReady )
			SDL_CondWait(renderCommandsEvent, smpMutex);

		data = (void *)smpData;
	}
	SDL_UnlockMutex(smpMutex);

	GLimp_SetCurrentContext(opengl_context);

	return data;
}

/*
===============
GLimp_FrontEndSleep
===============
*/
void GLimp_FrontEndSleep( void )
{
	SDL_LockMutex(smpMutex);
	{
		while ( smpData )
			SDL_CondWait(renderCompletedEvent, smpMutex);
	}
	SDL_UnlockMutex(smpMutex);

	GLimp_SetCurrentContext(opengl_context);
}

/*
===============
GLimp_WakeRenderer
===============
*/
void GLimp_WakeRenderer( void *data )
{
	GLimp_SetCurrentContext(NULL);

	SDL_LockMutex(smpMutex);
	{
		assert( smpData == NULL );
		smpData = data;
		smpDataReady = qtrue;

		// after this, the renderer can continue through GLimp_RendererSleep
		SDL_CondSignal(renderCommandsEvent);
	}
	SDL_UnlockMutex(smpMutex);
}

#else

// No SMP - stubs
void GLimp_RenderThreadWrapper( void *arg )
{
}

qboolean GLimp_SpawnRenderThread( void (*function)( void ) )
{
	ri.Printf( PRINT_WARNING, "ERROR: SMP support was disabled at compile time\n");
	return qfalse;
}

void *GLimp_RendererSleep( void )
{
	return NULL;
}

void GLimp_FrontEndSleep( void )
{
}

void GLimp_WakeRenderer( void *data )
{
}

#endif
