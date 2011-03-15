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


#ifndef GL_EXT_framebuffer_multisample
	#define GL_EXT_framebuffer_multisample 1
	#define GL_RENDERBUFFER_SAMPLES_EXT       0x8CAB
	#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
	#define GL_MAX_SAMPLES_EXT                0x8D57
	typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
#endif

#define GL_EXT_framebuffer_multisample_functions															\
	HANDLE_EXT_FUNC(PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC,		glRenderbufferStorageMultisampleEXT)	\



#ifndef GL_EXT_framebuffer_blit
	#define GL_EXT_framebuffer_blit 1
	#define GL_READ_FRAMEBUFFER_EXT           0x8CA8
	#define GL_DRAW_FRAMEBUFFER_EXT           0x8CA9
	#define GL_DRAW_FRAMEBUFFER_BINDING_EXT   GL_FRAMEBUFFER_BINDING_EXT
	#define GL_READ_FRAMEBUFFER_BINDING_EXT   0x8CAA
	typedef void (APIENTRYP PFNGLBLITFRAMEBUFFEREXTPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
#endif

#define GL_EXT_framebuffer_blit_functions																	\
	HANDLE_EXT_FUNC(PFNGLBLITFRAMEBUFFEREXTPROC,					glBlitFramebufferEXT)					\


#define ADD_ALL_EXTENSION_FUNCTIONS																			\
	GL_EXT_framebuffer_object_functions;																	\
	GL_EXT_framebuffer_multisample_functions;																\
	GL_EXT_framebuffer_blit_functions																		\


#endif
