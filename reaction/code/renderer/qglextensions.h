#ifndef __QGLEXTENSIONS_H__
#define __QGLEXTENSIONS_H__

#define GL_EXT_framebuffer_object_functions																	\
	HANDLE_EXT_FUNC(PFNGLGENFRAMEBUFFERSEXTPROC,					glGenFramebuffersEXT);					\
	HANDLE_EXT_FUNC(PFNGLBINDFRAMEBUFFEREXTPROC,					glBindFramebufferEXT);					\
	HANDLE_EXT_FUNC(PFNGLFRAMEBUFFERTEXTURE2DEXTPROC,				glFramebufferTexture2DEXT);				\
	HANDLE_EXT_FUNC(PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC,			glFramebufferRenderbufferEXT);			\
	HANDLE_EXT_FUNC(PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC,				glCheckFramebufferStatusEXT);			\
	HANDLE_EXT_FUNC(PFNGLDELETEFRAMEBUFFERSEXTPROC,					glDeleteFramebuffersEXT);				\
	HANDLE_EXT_FUNC(PFNGLGENERATEMIPMAPEXTPROC,						glGenerateMipmapEXT);					\
	HANDLE_EXT_FUNC(PFNGLDELETERENDERBUFFERSEXTPROC,				glDeleteRenderbuffersEXT);				\
	HANDLE_EXT_FUNC(PFNGLGENRENDERBUFFERSEXTPROC,					glGenRenderbuffersEXT);					\
	HANDLE_EXT_FUNC(PFNGLRENDERBUFFERSTORAGEEXTPROC,				glRenderbufferStorageEXT);				\
	HANDLE_EXT_FUNC(PFNGLBINDRENDERBUFFEREXTPROC,					glBindRenderbufferEXT)					\

#if !defined(GL_EXT_framebuffer_multisample) || !defined(GL_EXT_framebuffer_blit)
#	error "You need to update glext.h / SDL_opengl.h"
#endif


#define GL_EXT_framebuffer_multisample_functions															\
	HANDLE_EXT_FUNC(PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC,		glRenderbufferStorageMultisampleEXT)	\


#define GL_EXT_framebuffer_blit_functions																	\
	HANDLE_EXT_FUNC(PFNGLBLITFRAMEBUFFEREXTPROC,					glBlitFramebufferEXT)					\


#define ADD_ALL_EXTENSION_FUNCTIONS																			\
	GL_EXT_framebuffer_object_functions;																	\
	GL_EXT_framebuffer_multisample_functions;																\
	GL_EXT_framebuffer_blit_functions																		\


#endif
