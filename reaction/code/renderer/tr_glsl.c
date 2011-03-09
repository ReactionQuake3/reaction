/*
===========================================================================
Copyright (C) 2006-2009 Robert Beckebans <trebor_7@users.sourceforge.net>

This file is part of XreaL source code.

XreaL source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

XreaL source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with XreaL source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/
// tr_glsl.c
#include "tr_local.h"

void GLSL_BindNullProgram(void);

// FIXME: Do something that isn't this messy
static const char *fallbackGenericShader_vp = 
"attribute vec4  attr_Position;\r\nattribute vec4  attr_TexCoord0;\r\nattrib"
"ute vec4  attr_TexCoord1;\r\nattribute vec3  attr_Normal;\r\nattribute vec4"
"  attr_Color;\r\n\r\n#if defined(USE_VERTEX_ANIMATION)\r\nattribute vec4  a"
"ttr_Position2;\r\nattribute vec3  attr_Normal2;\r\n#endif\r\n\r\nuniform ma"
"t4    u_Texture0Matrix;\r\nuniform vec3    u_ViewOrigin;\r\n\r\n#if defined"
"(USE_TCGEN)\r\nuniform int     u_TCGen0;\r\nuniform vec4    u_TCGen0Vector0"
";\r\nuniform vec4    u_TCGen0Vector1;\r\n#endif\r\n\r\n#if defined(USE_FOG)"
"\r\nuniform vec4    u_FogDistance;\r\nuniform vec4    u_FogDepth;\r\nunifor"
"m float   u_FogEyeT;\r\nuniform int     u_FogAdjustColors;\r\n#endif\r\n\r"
"\n#if defined(USE_DEFORM_VERTEXES)\r\nuniform int     u_DeformGen;\r\nunifo"
"rm vec4    u_DeformWave;\r\nuniform vec3    u_DeformBulge;\r\nuniform float"
"   u_DeformSpread;\r\n#endif\r\n\r\nuniform float   u_Time;\r\nuniform int "
"    u_ColorGen;\r\nuniform int     u_AlphaGen;\r\nuniform vec4    u_Color;"
"\r\nuniform mat4    u_ModelViewProjectionMatrix;\r\nuniform vec3    u_Ambie"
"ntLight;\r\nuniform vec3    u_DirectedLight;\r\nuniform vec3    u_LightDir;"
"\r\n\r\nuniform float   u_PortalRange;\r\n\r\n#if defined(USE_VERTEX_ANIMAT"
"ION)\r\nuniform float   u_VertexLerp;\r\n#endif\r\n\r\nvarying vec2    var_"
"Tex1;\r\nvarying vec2    var_Tex2;\r\nvarying vec4    var_Color;\r\nvarying"
" float   var_DlightMod;\r\n\r\n#if defined(USE_DEFORM_VERTEXES)\r\nfloat tr"
"iangle(float x)\r\n{\r\n\treturn max(1.0 - abs(x), 0);\r\n}\r\n\r\nfloat sa"
"wtooth(float x)\r\n{\r\n\treturn x - floor(x);\r\n}\r\n\r\nvec4 DeformPosit"
"ion(const vec4 pos, const vec3 normal, const vec2 st)\r\n{\r\n\tvec4 deform"
"ed = pos;\r\n\r\n\tif (u_DeformGen == DGEN_WAVE_SIN)\r\n\t{\r\n\t\tfloat of"
"f = (pos.x + pos.y + pos.z) * u_DeformSpread;\r\n\t\tfloat scale = u_Deform"
"Wave.x  + sin((off + u_DeformWave.z + (u_Time * u_DeformWave.w)) * 2.0 * M_"
"PI) * u_DeformWave.y;\r\n\t\tvec3 offset = normal * scale;\r\n\r\n\t\tdefor"
"med.xyz += offset;\r\n\t}\r\n  else if (u_DeformGen == DGEN_WAVE_SQUARE)\r"
"\n\t{\r\n\t\tfloat off = (pos.x + pos.y + pos.z) * u_DeformSpread;\r\n\t\tf"
"loat scale = u_DeformWave.x  + sign(sin((off + u_DeformWave.z + (u_Time * u"
"_DeformWave.w)) * 2.0 * M_PI)) * u_DeformWave.y;\r\n\t\tvec3 offset = norma"
"l * scale;\r\n\r\n\t\tdeformed.xyz += offset;\r\n\t}\r\n  else if (u_Deform"
"Gen == DGEN_WAVE_TRIANGLE)\r\n\t{\r\n\t\tfloat off = (pos.x + pos.y + pos.z"
") * u_DeformSpread;\r\n\t\tfloat scale = u_DeformWave.x  + triangle(off + u"
"_DeformWave.z + (u_Time * u_DeformWave.w)) * u_DeformWave.y;\r\n\t\tvec3 of"
"fset = normal * scale;\r\n\r\n\t\tdeformed.xyz += offset;\r\n\t}\r\n  else "
"if (u_DeformGen == DGEN_WAVE_SAWTOOTH)\r\n\t{\r\n\t\tfloat off = (pos.x + p"
"os.y + pos.z) * u_DeformSpread;\r\n\t\tfloat scale = u_DeformWave.x  + sawt"
"ooth(off + u_DeformWave.z + (u_Time * u_DeformWave.w)) * u_DeformWave.y;\r"
"\n\t\tvec3 offset = normal * scale;\r\n\r\n\t\tdeformed.xyz += offset;\r\n"
"\t}\r\n  else if (u_DeformGen == DGEN_WAVE_INVERSE_SAWTOOTH)\r\n\t{\r\n\t\t"
"float off = (pos.x + pos.y + pos.z) * u_DeformSpread;\r\n\t\tfloat scale = "
"u_DeformWave.x + (1.0 - sawtooth(off + u_DeformWave.z + (u_Time * u_DeformW"
"ave.w))) * u_DeformWave.y;\r\n\t\tvec3 offset = normal * scale;\r\n\r\n\t\t"
"deformed.xyz += offset;\r\n\t}\r\n  else if (u_DeformGen == DGEN_BULGE)\r\n"
"\t{\r\n\t\tfloat bulgeWidth = u_DeformBulge.x;\r\n\t\tfloat bulgeHeight = u"
"_DeformBulge.y;\r\n\t\tfloat bulgeSpeed = u_DeformBulge.z;\r\n\r\n\t\tfloat"
" now = u_Time * bulgeSpeed;\r\n\r\n\t\tfloat off = (M_PI * 0.25) * st.x * b"
"ulgeWidth + now;\r\n\t\tfloat scale = sin(off) * bulgeHeight;\r\n\t\tvec3 o"
"ffset = normal * scale;\r\n\r\n\t\tdeformed.xyz += offset;\r\n\t}\r\n\r\n\t"
"return deformed;\r\n}\r\n#endif\r\n\r\n#if defined(USE_TCGEN)\r\nvec2 GenTe"
"xCoords(int TCGen, vec4 position, vec3 normal, mat4 texMatrix, vec4 TCGenVe"
"ctor0, vec4 TCGenVector1)\r\n{\r\n\tvec2 tex = vec2(0.0);\r\n\r\n\tif (TCGe"
"n == TCGEN_LIGHTMAP)\r\n\t{\r\n\t\ttex = attr_TexCoord1.st;\r\n\t}\r\n\tels"
"e if (TCGen == TCGEN_TEXTURE)\r\n\t{\r\n\t\ttex = attr_TexCoord0.st;\r\n\t}"
"\r\n\telse if (TCGen == TCGEN_ENVIRONMENT_MAPPED)\r\n\t{\r\n\t\tvec3 viewer"
" = normalize(u_ViewOrigin - position.xyz);\r\n\r\n\t\tfloat d = dot(normal,"
" viewer);\r\n\r\n\t\tvec3 reflected = normal * 2.0 * d - viewer;\r\n\r\n\t"
"\ttex.s = 0.5 + reflected.y * 0.5;\r\n\t\ttex.t = 0.5 - reflected.z * 0.5;"
"\r\n\t}\r\n\telse if (TCGen == TCGEN_VECTOR)\r\n\t{\r\n\t\ttex.s = dot(posi"
"tion.xyz, TCGenVector0.xyz);\r\n\t\ttex.t = dot(position.xyz, TCGenVector1."
"xyz);\r\n\t}\r\n\telse if (TCGen == TCGEN_DLIGHT)\r\n\t{\r\n\t  vec3 dist ="
" TCGenVector0.xyz - position.xyz;\r\n\t  \r\n\t  if (dot(dist, normal) < 0)"
"\r\n\t  {\r\n\t    var_DlightMod = 0;\r\n\t  }\r\n\t  else\r\n\t  {\r\n\t  "
"  float diffz = abs(dist.z);\r\n      float radius = 1.0 / TCGenVector0.a;"
"\r\n\t    \r\n\t    if (diffz > radius)\r\n      {\r\n        var_DlightMod"
" = 0;\r\n      }\r\n      else\r\n      {\r\n        tex = vec2(0.5) + dist"
".xy * TCGenVector0.a;\r\n\r\n        if (diffz < radius * 0.5)\r\n        {"
"\r\n          var_DlightMod = 1.0;\r\n        }\r\n        else\r\n        "
"{\r\n          var_DlightMod = 2.0 * (radius - diffz) * TCGenVector0.a;\r\n"
"        }\r\n      }\r\n\t  }\r\n\t}\r\n\t\r\n\treturn tex;\r\n}\r\n#endif"
"\r\n\r\nvoid\tmain()\r\n{\r\n\tvec4 position;\r\n\tvec3 normal;\r\n\r\n#if "
"defined(USE_VERTEX_ANIMATION)\r\n  if (u_VertexLerp > 0.0)\r\n  {\r\n    po"
"sition = mix(attr_Position, attr_Position2, u_VertexLerp);\r\n    normal = "
"mix(attr_Normal, attr_Normal2, u_VertexLerp);\r\n    normal = normalize(nor"
"mal);\r\n  }\r\n  else\r\n#endif\r\n  {\r\n    position = attr_Position;\r"
"\n    normal = attr_Normal;\r\n  }\r\n\r\n#if defined(USE_DEFORM_VERTEXES)"
"\r\n  position = DeformPosition(position, normal, attr_TexCoord0.st);\r\n#e"
"ndif\r\n\r\n\tgl_Position = u_ModelViewProjectionMatrix * position;\r\n\r\n"
"  {\r\n    vec4 tex = vec4(1.0, 1.0, 1.0, 0.0);\r\n\r\n#if defined(USE_TCGE"
"N)\r\n    tex.st = GenTexCoords(u_TCGen0, position, normal, u_Texture0Matri"
"x, u_TCGen0Vector0, u_TCGen0Vector1);\r\n#else\r\n    tex.st = attr_TexCoor"
"d0.st;\r\n#endif\r\n    \r\n    var_Tex1 = (u_Texture0Matrix * tex).st;\r\n"
"\r\n    if (u_Texture0Matrix[3][0] != 0)\r\n    {\r\n      var_Tex1.s += si"
"n(((position.x + position.z) * 1.0 / 128.0 * 0.125 + u_Texture0Matrix[3][1]"
") * 2.0 * M_PI) * u_Texture0Matrix[3][0];\r\n      var_Tex1.t += sin((posit"
"ion.y * 1.0 / 128.0 * 0.125 + u_Texture0Matrix[3][1]) * 2.0 * M_PI) * u_Tex"
"ture0Matrix[3][0];\r\n    }\r\n  }\r\n\r\n  var_Tex2 = attr_TexCoord1.st;\r"
"\n\r\n  if (u_ColorGen == CGEN_IDENTITY)\r\n  {\r\n    var_Color.rgb = vec3"
"(1.0);\r\n  }\r\n\telse if (u_ColorGen == CGEN_LIGHTING_DIFFUSE)\r\n\t{\r\n"
"\t\tfloat incoming = dot(attr_Normal, u_LightDir);\r\n\r\n\t\tif (incoming "
"<= 0)\r\n\t\t{\r\n\t\t\tvar_Color.rgb = u_AmbientLight;\r\n\t\t}\r\n\t\tels"
"e\r\n\t\t{\r\n\t\t  var_Color.rgb = min(u_AmbientLight + u_DirectedLight * "
"incoming, vec3(1));\r\n\t\t}\r\n\t}\r\n\telse if (u_ColorGen == CGEN_EXACT_"
"VERTEX)\r\n\t{\r\n\t\tvar_Color.rgb = attr_Color.rgb;\r\n\t}\r\n\telse if ("
"u_ColorGen == CGEN_VERTEX)\r\n\t{\r\n\t\tvar_Color.rgb = attr_Color.rgb * u"
"_Color.rgb;\r\n\t}\r\n\telse if (u_ColorGen == CGEN_ONE_MINUS_VERTEX)\r\n\t"
"{\r\n\t\tvar_Color.rgb = (vec3(1.0) - attr_Color.rgb) * u_Color.rgb;\r\n\t}"
"\r\n\telse if (u_ColorGen == CGEN_DLIGHT)\r\n\t{\r\n\t  var_Color.rgb = u_C"
"olor.rgb * var_DlightMod;\r\n\t}\r\n\telse\r\n\t{\r\n\t\tvar_Color.rgb = u_"
"Color.rgb;\r\n\t}\r\n\r\n  if (u_AlphaGen == AGEN_IDENTITY)\r\n  {\r\n    v"
"ar_Color.a = 1.0;\r\n  }\r\n\telse if (u_AlphaGen == AGEN_LIGHTING_SPECULAR"
")\r\n\t{\r\n\t\tvec3 lightDir = vec3(-960.0, -1980.0, 96.0) - position.xyz;"
"\r\n\t\tlightDir = normalize(lightDir);\r\n\r\n\t\tfloat d = dot(attr_Norma"
"l, lightDir);\r\n\t\tvec3 reflected = attr_Normal * 2.0 * d - lightDir;\r\n"
"\r\n\t\tvec3 viewer = u_ViewOrigin - position.xyz;\r\n\t\tfloat ilength = 1"
".0 / length(viewer);\r\n\r\n\t\tfloat l = dot(reflected, viewer);\r\n\t\tl "
"*= ilength;\r\n\r\n\t\tif (l < 0.0)\r\n\t\t{\r\n\t\t\tvar_Color.a = 0.0;\r"
"\n\t\t}\r\n\t\telse\r\n\t\t{\r\n\t\t\tl = l*l;\r\n\t\t\tl = l*l;\r\n\t\t\tv"
"ar_Color.a = min(l, 1.0);\r\n\t\t}\r\n\t}\r\n\telse if (u_AlphaGen == AGEN_"
"VERTEX)\r\n\t{\r\n\t\tvar_Color.a = attr_Color.a;\r\n\t}\r\n\telse if (u_Al"
"phaGen == AGEN_ONE_MINUS_VERTEX)\r\n\t{\r\n\t\tvar_Color.a = 1.0 - attr_Col"
"or.a;\r\n\t}\r\n\telse if (u_AlphaGen == AGEN_PORTAL)\r\n\t{\r\n\t\tfloat l"
"en;\r\n\t\tvec3 v;\r\n\r\n\t\tv = position.xyz - u_ViewOrigin;\r\n\t\tlen ="
" length(v);\r\n\r\n\t\tlen /= u_PortalRange;\r\n\r\n\t\tvar_Color.a = clamp"
"(len, 0.0, 1.0);\r\n\t}\r\n\telse\r\n\t{\r\n\t\tvar_Color.a = u_Color.a;\r"
"\n\t}\r\n\r\n#if defined (USE_FOG)\r\n  if (u_FogAdjustColors != 0) \r\n\t{"
"\r\n\t\tfloat s = dot(position.xyz, u_FogDistance.xyz) + u_FogDistance.a;\r"
"\n\t\tfloat t = dot(position.xyz, u_FogDepth.xyz) + u_FogDepth.a;\r\n\t\t\r"
"\n\t\tif (s < 0.0 || t < 0.0 || (u_FogEyeT < 0.0 && t < 1.0) )\r\n\t\t{\r\n"
"\t\t  s = 0.0;\r\n\t\t}\r\n\t\telse\r\n\t\t{\r\n\t\t  if (u_FogEyeT < 0.0)"
"\r\n\t\t  {\r\n\t\t      s *= t / (t - u_FogEyeT);\r\n\t\t  }\r\n\r\n\t\t  "
"s *= 8.0;\r\n\t\t  \t\t  \r\n\t\t  s = clamp(s, 0.0, 1.0);\r\n\t\t  \r\n\t"
"\t  s = sqrt(s);\r\n\t\t}\r\n\t\t\r\n\t\tif (u_FogAdjustColors == 1)\r\n   "
" {\r\n      var_Color.xyz *= (1.0 - s);\r\n    }\r\n    else if (u_FogAdjus"
"tColors == 2)\r\n    {\r\n      var_Color.a *= (1.0 - s);\r\n    }\r\n    e"
"lse if (u_FogAdjustColors == 3)\r\n    {\r\n      var_Color *= (1.0 - s);\r"
"\n    }\r\n    else if (u_FogAdjustColors == 4)\r\n    {\r\n      var_Color"
".xyz = u_Color.xyz;\r\n      var_Color.a = u_Color.a * s;\r\n    }\r\n  }\r"
"\n#endif\r\n}\r\n";

static const char *fallbackGenericShader_fp = 
"uniform sampler2D    u_Texture0Map;\r\nuniform sampler2D    u_Texture1Map;"
"\r\nuniform int          u_Texture1Env;\r\n\r\n#if defined(USE_FOG)\r\nunif"
"orm int          u_FogAdjustColors;\r\n#endif\r\n\r\nvarying vec2         v"
"ar_Tex1;\r\nvarying vec2         var_Tex2;\r\nvarying vec4         var_Colo"
"r;\r\n\r\n\r\nvoid\tmain()\r\n{\r\n\tvec4 color;\r\n\r\n#if defined(USE_FOG"
")\r\n  if (u_FogAdjustColors == 4)\r\n  {\r\n    color = var_Color;\r\n  }"
"\r\n  else\r\n#endif\r\n  {\r\n    if (u_Texture1Env != 2)\r\n    {\r\n    "
"   color = texture2D(u_Texture0Map, var_Tex1);\r\n    }\r\n    \r\n    if ("
"u_Texture1Env != 0)\r\n    {\r\n      vec4 color2 = texture2D(u_Texture1Map"
", var_Tex2);\r\n\r\n      if (u_Texture1Env == 1) // GL_MODULATE\r\n      {"
"\r\n        color *= color2;\r\n      }\r\n      else if (u_Texture1Env == "
"4) // GL_ADD\r\n      {\r\n        color += color2;\r\n      }\r\n      els"
"e // if (u_Texture1Env == 2) GL_REPLACE\r\n      {\r\n        color = color"
"2;\r\n      }\r\n    }\r\n\r\n    color *= var_Color;\r\n  }\r\n\r\n\tgl_Fr"
"agColor = color;\r\n}\r\n";


static void GLSL_PrintInfoLog(GLhandleARB object, qboolean developerOnly)
{
	char           *msg;
	static char     msgPart[1024];
	int             maxLength = 0;
	int             i;

	qglGetObjectParameterivARB(object, GL_OBJECT_INFO_LOG_LENGTH_ARB, &maxLength);

	msg = ri.Malloc(maxLength);

	qglGetInfoLogARB(object, maxLength, &maxLength, msg);

	if(developerOnly)
	{
		ri.Printf(PRINT_DEVELOPER, "compile log:\n");
	}
	else
	{
		ri.Printf(PRINT_ALL, "compile log:\n");
	}

	for(i = 0; i < maxLength; i += 1024)
	{
		Q_strncpyz(msgPart, msg + i, sizeof(msgPart));

		if(developerOnly)
			ri.Printf(PRINT_DEVELOPER, "%s\n", msgPart);
		else
			ri.Printf(PRINT_ALL, "%s\n", msgPart);
	}

	ri.Free(msg);
}

static void GLSL_PrintShaderSource(GLhandleARB object)
{
	char           *msg;
	static char     msgPart[1024];
	int             maxLength = 0;
	int             i;

	qglGetObjectParameterivARB(object, GL_OBJECT_SHADER_SOURCE_LENGTH_ARB, &maxLength);

	msg = ri.Malloc(maxLength);

	qglGetShaderSourceARB(object, maxLength, &maxLength, msg);

	for(i = 0; i < maxLength; i += 1024)
	{
		Q_strncpyz(msgPart, msg + i, sizeof(msgPart));
		ri.Printf(PRINT_ALL, "%s\n", msgPart);
	}

	ri.Free(msg);
}

static int GLSL_CompileGPUShader(GLhandleARB program, GLhandleARB *prevShader, const GLcharARB *buffer, int size, GLenum shaderType, const GLcharARB *extra)
{
	GLint           compiled;
	GLhandleARB     shader;

	shader = qglCreateShaderObjectARB(shaderType);

	{
		static char     bufferExtra[32000];
		int             sizeExtra;

		char           *bufferFinal = NULL;
		int             sizeFinal;

		float           fbufWidthScale, fbufHeightScale;

		Com_Memset(bufferExtra, 0, sizeof(bufferExtra));

		// HACK: abuse the GLSL preprocessor to turn GLSL 1.20 shaders into 1.30 ones
		if(0) //(glConfig.driverType == GLDRV_OPENGL3)
		{
			Q_strcat(bufferExtra, sizeof(bufferExtra), "#version 130\n");

			if(shaderType == GL_VERTEX_SHADER_ARB)
			{
				Q_strcat(bufferExtra, sizeof(bufferExtra), "#define attribute in\n");
				Q_strcat(bufferExtra, sizeof(bufferExtra), "#define varying out\n");
			}
			else
			{
				Q_strcat(bufferExtra, sizeof(bufferExtra), "#define varying in\n");

				Q_strcat(bufferExtra, sizeof(bufferExtra), "out vec4 out_Color;\n");
				Q_strcat(bufferExtra, sizeof(bufferExtra), "#define gl_FragColor out_Color\n");
			}
		}
		else
		{
			Q_strcat(bufferExtra, sizeof(bufferExtra), "#version 120\n");
		}

		// HACK: add some macros to avoid extra uniforms and save speed and code maintenance
		//Q_strcat(bufferExtra, sizeof(bufferExtra),
		//		 va("#ifndef r_SpecularExponent\n#define r_SpecularExponent %f\n#endif\n", r_specularExponent->value));
		//Q_strcat(bufferExtra, sizeof(bufferExtra),
		//		 va("#ifndef r_SpecularScale\n#define r_SpecularScale %f\n#endif\n", r_specularScale->value));
		//Q_strcat(bufferExtra, sizeof(bufferExtra),
		//       va("#ifndef r_NormalScale\n#define r_NormalScale %f\n#endif\n", r_normalScale->value));


		Q_strcat(bufferExtra, sizeof(bufferExtra), "#ifndef M_PI\n#define M_PI 3.14159265358979323846f\n#endif\n");

		//Q_strcat(bufferExtra, sizeof(bufferExtra), va("#ifndef MAX_SHADOWMAPS\n#define MAX_SHADOWMAPS %i\n#endif\n", MAX_SHADOWMAPS));

		Q_strcat(bufferExtra, sizeof(bufferExtra),
						 va("#ifndef deformGen_t\n"
							"#define deformGen_t\n"
							"#define DGEN_WAVE_SIN %i\n"
							"#define DGEN_WAVE_SQUARE %i\n"
							"#define DGEN_WAVE_TRIANGLE %i\n"
							"#define DGEN_WAVE_SAWTOOTH %i\n"
							"#define DGEN_WAVE_INVERSE_SAWTOOTH %i\n"
							"#define DGEN_BULGE %i\n"
							"#define DGEN_MOVE %i\n"
							"#endif\n",
							DGEN_WAVE_SIN,
							DGEN_WAVE_SQUARE,
							DGEN_WAVE_TRIANGLE,
							DGEN_WAVE_SAWTOOTH,
							DGEN_WAVE_INVERSE_SAWTOOTH,
							DGEN_BULGE,
							DGEN_MOVE));

		Q_strcat(bufferExtra, sizeof(bufferExtra),
						 va("#ifndef tcGen_t\n"
							"#define tcGen_t\n"
							"#define TCGEN_LIGHTMAP %i\n"
							"#define TCGEN_TEXTURE %i\n"
							"#define TCGEN_ENVIRONMENT_MAPPED %i\n"
							"#define TCGEN_FOG %i\n"
							"#define TCGEN_VECTOR %i\n"
							"#define TCGEN_DLIGHT %i\n"
							"#endif\n",
							TCGEN_LIGHTMAP,
							TCGEN_TEXTURE,
							TCGEN_ENVIRONMENT_MAPPED,
							TCGEN_FOG,
							TCGEN_VECTOR,
							TCGEN_DLIGHT));

		Q_strcat(bufferExtra, sizeof(bufferExtra),
						 va("#ifndef colorGen_t\n"
							"#define colorGen_t\n"
							"#define CGEN_IDENTITY %i\n"
							"#define CGEN_VERTEX %i\n"
							"#define CGEN_ONE_MINUS_VERTEX %i\n"
							"#define CGEN_EXACT_VERTEX %i\n"
							"#define CGEN_LIGHTING_DIFFUSE %i\n"
							"#define CGEN_DLIGHT %i\n"
							"#endif\n",
							CGEN_IDENTITY,
							CGEN_VERTEX,
							CGEN_ONE_MINUS_VERTEX,
							CGEN_EXACT_VERTEX,
							CGEN_LIGHTING_DIFFUSE,
							CGEN_DLIGHT));

		Q_strcat(bufferExtra, sizeof(bufferExtra),
								 va("#ifndef alphaGen_t\n"
									"#define alphaGen_t\n"
									"#define AGEN_IDENTITY %i\n"
									"#define AGEN_VERTEX %i\n"
									"#define AGEN_ONE_MINUS_VERTEX %i\n"
									"#define AGEN_LIGHTING_SPECULAR %i\n"
									"#define AGEN_PORTAL %i\n"
									"#endif\n",
									AGEN_IDENTITY,
									AGEN_VERTEX,
									AGEN_ONE_MINUS_VERTEX,
									AGEN_LIGHTING_SPECULAR,
									AGEN_PORTAL));

		Q_strcat(bufferExtra, sizeof(bufferExtra),
								 va("#ifndef alphaTest_t\n"
									"#define alphaTest_t\n"
									"#define ATEST_GT_0 %i\n"
									"#define ATEST_LT_128 %i\n"
									"#define ATEST_GE_128 %i\n"
									"#endif\n",
									ATEST_GT_0,
									ATEST_LT_128,
									ATEST_GE_128));

		fbufWidthScale = 1.0f / ((float)glConfig.vidWidth);
		fbufHeightScale = 1.0f / ((float)glConfig.vidHeight);
		Q_strcat(bufferExtra, sizeof(bufferExtra),
				 va("#ifndef r_FBufScale\n#define r_FBufScale vec2(%f, %f)\n#endif\n", fbufWidthScale, fbufHeightScale));


		if (extra)
		{
			Q_strcat(bufferExtra, sizeof(bufferExtra), extra);
		}

		// OK we added a lot of stuff but if we do something bad in the GLSL shaders then we want the proper line
		// so we have to reset the line counting
		Q_strcat(bufferExtra, sizeof(bufferExtra), "#line 0\n");

		sizeExtra = strlen(bufferExtra);
		sizeFinal = sizeExtra + size;

		//ri.Printf(PRINT_ALL, "GLSL extra: %s\n", bufferExtra);

		bufferFinal = ri.Hunk_AllocateTempMemory(size + sizeExtra);

		strcpy(bufferFinal, bufferExtra);
		Q_strcat(bufferFinal, sizeFinal, buffer);

		qglShaderSourceARB(shader, 1, (const GLcharARB **)&bufferFinal, &sizeFinal);

		ri.Hunk_FreeTempMemory(bufferFinal);
	}

	// compile shader
	qglCompileShaderARB(shader);

	// check if shader compiled
	qglGetObjectParameterivARB(shader, GL_OBJECT_COMPILE_STATUS_ARB, &compiled);
	if(!compiled)
	{
		GLSL_PrintShaderSource(shader);
		GLSL_PrintInfoLog(shader, qfalse);
		ri.Error(ERR_DROP, "Couldn't compile shader");
		return 0;
	}

	GLSL_PrintInfoLog(shader, qtrue);
	//ri.Printf(PRINT_ALL, "%s\n", GLSL_PrintShaderSource(shader));

	if (*prevShader)
	{
		qglDetachObjectARB(program, *prevShader);
		qglDeleteObjectARB(*prevShader);
	}

	// attach shader to program
	qglAttachObjectARB(program, shader);

	*prevShader = shader;

	return 1;
}


static int GLSL_LoadGPUShader(GLhandleARB program, GLhandleARB *prevShader, const char *name, GLenum shaderType, const GLcharARB *extra)
{
	char            filename[MAX_QPATH];
	GLcharARB      *buffer = NULL;
	int             size;
	int				result;

	if(shaderType == GL_VERTEX_SHADER_ARB)
	{
		Com_sprintf(filename, sizeof(filename), "glsl/%s_vp.glsl", name);
	}
	else
	{
		Com_sprintf(filename, sizeof(filename), "glsl/%s_fp.glsl", name);
	}

	ri.Printf(PRINT_ALL, "...loading '%s'\n", filename);
	size = ri.FS_ReadFile(filename, (void **)&buffer);
	if(!buffer)
	{
		//ri.Error(ERR_DROP, "Couldn't load %s", filename);
		ri.Printf(PRINT_ALL, "Couldn't load %s, size %d\n", filename, size);
		return 0;
	}

#if 0 // for dumping
	{
		int i, l, inc;

		ri.Printf(PRINT_ALL, "%s:\n\"", filename);
		l = 0;

		for (i = 0; i < size; i++)
		{
			switch (buffer[i])
			{
				case '\a':
				case '\b':
				case '\f':
				case '\n':
				case '\r':
				case '\t':
				case '\v':
				case '"':
				case '\\':
					inc = 2;
					break;
				default:
					inc = 1;
					break;
			}

			l += inc;

			if (l >= 76)
			{
				ri.Printf(PRINT_ALL, "\"\n\"");
				l = inc;
			}

			switch (buffer[i])
			{
				case '\a':
					ri.Printf(PRINT_ALL, "\\a");
					break;
				case '\b':
					ri.Printf(PRINT_ALL, "\\b");
					break;
				case '\f':
					ri.Printf(PRINT_ALL, "\\f");
					break;
				case '\n':
					ri.Printf(PRINT_ALL, "\\n");
					break;
				case '\r':
					ri.Printf(PRINT_ALL, "\\r");
					break;
				case '\t':
					ri.Printf(PRINT_ALL, "\\t");
					break;
				case '\v':
					ri.Printf(PRINT_ALL, "\\v");
					break;
				case '"':
					ri.Printf(PRINT_ALL, "\\\"");
					break;
				case '\\':
					ri.Printf(PRINT_ALL, "\\\\");
					break;
				default:
					ri.Printf(PRINT_ALL, "%c", buffer[i]);
					break;
			}
		}
		ri.Printf(PRINT_ALL, "\"\n");
	}
#endif

	result = GLSL_CompileGPUShader(program, prevShader, buffer, size, shaderType, extra);

	ri.FS_FreeFile(buffer);
	
	return result;
}

static void GLSL_LinkProgram(GLhandleARB program)
{
	GLint           linked;

	qglLinkProgramARB(program);

	qglGetObjectParameterivARB(program, GL_OBJECT_LINK_STATUS_ARB, &linked);
	if(!linked)
	{
		GLSL_PrintInfoLog(program, qfalse);
		ri.Error(ERR_DROP, "\nshaders failed to link");
	}
}

static void GLSL_ValidateProgram(GLhandleARB program)
{
	GLint           validated;

	qglValidateProgramARB(program);

	qglGetObjectParameterivARB(program, GL_OBJECT_VALIDATE_STATUS_ARB, &validated);
	if(!validated)
	{
		GLSL_PrintInfoLog(program, qfalse);
		ri.Error(ERR_DROP, "\nshaders failed to validate");
	}
}

static void GLSL_ShowProgramUniforms(GLhandleARB program)
{
	int             i, count, size;
	GLenum			type;
	char            uniformName[1000];

	// install the executables in the program object as part of current state.
	qglUseProgramObjectARB(program);

	// check for GL Errors

	// query the number of active uniforms
	qglGetObjectParameterivARB(program, GL_OBJECT_ACTIVE_UNIFORMS_ARB, &count);

	// Loop over each of the active uniforms, and set their value
	for(i = 0; i < count; i++)
	{
		qglGetActiveUniformARB(program, i, sizeof(uniformName), NULL, &size, &type, uniformName);

		ri.Printf(PRINT_DEVELOPER, "active uniform: '%s'\n", uniformName);
	}

	qglUseProgramObjectARB(0);
}

static int GLSL_InitGPUShader(shaderProgram_t * program, const char *name, int attribs, qboolean fragmentShader, const GLcharARB *extra)
{
	ri.Printf(PRINT_DEVELOPER, "------- GPU shader -------\n");

	if(strlen(name) >= MAX_QPATH)
	{
		ri.Error(ERR_DROP, "GLSL_InitGPUShader: \"%s\" is too long\n", name);
	}

	Q_strncpyz(program->name, name, sizeof(program->name));

	program->program = qglCreateProgramObjectARB();
	program->attribs = attribs;

	if (!(GLSL_LoadGPUShader(program->program, &program->vertexShader, name, GL_VERTEX_SHADER_ARB, extra)))
	{
		ri.Printf(PRINT_ALL, "GLSL_InitGPUShader: Unable to load \"%s\" as GL_VERTEX_SHADER_ARB\n", name);
		qglDeleteObjectARB(program->program);
		return 0;
	}

	if(fragmentShader)
		GLSL_LoadGPUShader(program->program, &program->fragmentShader, name, GL_FRAGMENT_SHADER_ARB, extra);

	if(attribs & ATTR_POSITION)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_POSITION, "attr_Position");

	if(attribs & ATTR_TEXCOORD)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_TEXCOORD0, "attr_TexCoord0");

	if(attribs & ATTR_LIGHTCOORD)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_TEXCOORD1, "attr_TexCoord1");

//  if(attribs & ATTR_TEXCOORD2)
//      qglBindAttribLocationARB(program->program, ATTR_INDEX_TEXCOORD2, "attr_TexCoord2");

//  if(attribs & ATTR_TEXCOORD3)
//      qglBindAttribLocationARB(program->program, ATTR_INDEX_TEXCOORD3, "attr_TexCoord3");

	if(attribs & ATTR_TANGENT)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_TANGENT, "attr_Tangent");

	if(attribs & ATTR_BINORMAL)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_BINORMAL, "attr_Binormal");

	if(attribs & ATTR_NORMAL)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_NORMAL, "attr_Normal");

	if(attribs & ATTR_COLOR)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_COLOR, "attr_Color");

	if(attribs & ATTR_PAINTCOLOR)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_PAINTCOLOR, "attr_PaintColor");

	if(attribs & ATTR_LIGHTDIRECTION)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_LIGHTDIRECTION, "attr_LightDirection");

	if(attribs & ATTR_POSITION2)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_POSITION2, "attr_Position2");

	if(attribs & ATTR_NORMAL2)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_NORMAL2, "attr_Normal2");

	GLSL_LinkProgram(program->program);

	return 1;
}


static int GLSL_InitFallbackGenericShader(shaderProgram_t * program, const char *name, int attribs, qboolean fragmentShader, const GLcharARB *extra)
{
	ri.Printf(PRINT_DEVELOPER, "------- GPU shader -------\n");

	if(strlen(name) >= MAX_QPATH)
	{
		ri.Error(ERR_DROP, "GLSL_InitGPUShader: \"%s\" is too long\n", name);
	}

	Q_strncpyz(program->name, name, sizeof(program->name));

	program->program = qglCreateProgramObjectARB();
	program->attribs = attribs;

	if (!(GLSL_CompileGPUShader(program->program, &program->vertexShader, fallbackGenericShader_vp, strlen(fallbackGenericShader_vp), GL_VERTEX_SHADER_ARB, extra)))
	{
		ri.Printf(PRINT_ALL, "GLSL_InitFallbackGenericShader: Unable to load \"%s\" as GL_VERTEX_SHADER_ARB\n", name);
		qglDeleteObjectARB(program->program);
		return 0;
	}

	if(fragmentShader)
		GLSL_CompileGPUShader(program->program, &program->fragmentShader, fallbackGenericShader_fp, strlen(fallbackGenericShader_fp), GL_FRAGMENT_SHADER_ARB, extra);

	if(attribs & ATTR_POSITION)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_POSITION, "attr_Position");

	if(attribs & ATTR_TEXCOORD)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_TEXCOORD0, "attr_TexCoord0");

	if(attribs & ATTR_LIGHTCOORD)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_TEXCOORD1, "attr_TexCoord1");

//  if(attribs & ATTR_TEXCOORD2)
//      qglBindAttribLocationARB(program->program, ATTR_INDEX_TEXCOORD2, "attr_TexCoord2");

//  if(attribs & ATTR_TEXCOORD3)
//      qglBindAttribLocationARB(program->program, ATTR_INDEX_TEXCOORD3, "attr_TexCoord3");

	if(attribs & ATTR_TANGENT)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_TANGENT, "attr_Tangent");

	if(attribs & ATTR_BINORMAL)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_BINORMAL, "attr_Binormal");

	if(attribs & ATTR_NORMAL)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_NORMAL, "attr_Normal");

	if(attribs & ATTR_COLOR)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_COLOR, "attr_Color");

	if(attribs & ATTR_PAINTCOLOR)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_PAINTCOLOR, "attr_PaintColor");

	if(attribs & ATTR_LIGHTDIRECTION)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_LIGHTDIRECTION, "attr_LightDirection");

	if(attribs & ATTR_POSITION2)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_POSITION2, "attr_Position2");

	if(attribs & ATTR_NORMAL2)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_NORMAL2, "attr_Normal2");

	GLSL_LinkProgram(program->program);

	return 1;
}


void GLSL_InitGPUShaders(void)
{
	int             startTime, endTime;
	int i;
	char extradefines[1024];

	ri.Printf(PRINT_ALL, "------- GLSL_InitGPUShaders -------\n");

	// make sure the render thread is stopped
	R_SyncRenderThread();

	startTime = ri.Milliseconds();

	for (i = 0; i < GLSLDEF_COUNT; i++)
	{
		int attribs = ATTR_POSITION | ATTR_TEXCOORD | ATTR_LIGHTCOORD | ATTR_NORMAL | ATTR_COLOR;
		extradefines[0] = '\0';

		if (i & GLSLDEF_USE_DEFORM_VERTEXES)
			Q_strcat(extradefines, 1024, "#define USE_DEFORM_VERTEXES\n");

		if (i & GLSLDEF_USE_TCGEN)
			Q_strcat(extradefines, 1024, "#define USE_TCGEN\n");

		if (i & GLSLDEF_USE_VERTEX_ANIMATION)
		{
			Q_strcat(extradefines, 1024, "#define USE_VERTEX_ANIMATION\n");
			attribs |= ATTR_POSITION2 | ATTR_NORMAL2;
		}

		if (i & GLSLDEF_USE_FOG)
		{
			Q_strcat(extradefines, 1024, "#define USE_FOG\n");
		}

		if (!GLSL_InitGPUShader(&tr.genericShader[i], "generic", attribs, qtrue, extradefines))
		{
			// Failed to load, init the fallback one
			GLSL_InitFallbackGenericShader(&tr.genericShader[i], "generic", attribs, qtrue, extradefines);
		}

		tr.genericShader[i].u_ModelViewProjectionMatrix =
			qglGetUniformLocationARB(tr.genericShader[i].program, "u_ModelViewProjectionMatrix");

		tr.genericShader[i].u_AlphaTest      = -1; //qglGetUniformLocationARB(tr.genericShader[i].program, "u_AlphaTest");
		tr.genericShader[i].u_ColorGen       = qglGetUniformLocationARB(tr.genericShader[i].program, "u_ColorGen");
		tr.genericShader[i].u_AlphaGen       = qglGetUniformLocationARB(tr.genericShader[i].program, "u_AlphaGen");

		if (i & GLSLDEF_USE_TCGEN)
		{
			tr.genericShader[i].u_TCGen0         = qglGetUniformLocationARB(tr.genericShader[i].program, "u_TCGen0");
			tr.genericShader[i].u_TCGen1         = -1; //qglGetUniformLocationARB(tr.genericShader[i].program, "u_TCGen1");
			tr.genericShader[i].u_TCGen0Vector0  = qglGetUniformLocationARB(tr.genericShader[i].program, "u_TCGen0Vector0");
			tr.genericShader[i].u_TCGen0Vector1  = qglGetUniformLocationARB(tr.genericShader[i].program, "u_TCGen0Vector1");
			tr.genericShader[i].u_TCGen1Vector0  = -1; //qglGetUniformLocationARB(tr.genericShader[i].program, "u_TCGen1Vector0");
			tr.genericShader[i].u_TCGen1Vector1  = -1; //qglGetUniformLocationARB(tr.genericShader[i].program, "u_TCGen1Vector1");
		}
		else
		{
			tr.genericShader[i].u_TCGen0         = -1;
			tr.genericShader[i].u_TCGen1         = -1;
			tr.genericShader[i].u_TCGen0Vector0  = -1;
			tr.genericShader[i].u_TCGen0Vector1  = -1;
			tr.genericShader[i].u_TCGen1Vector0  = -1;
			tr.genericShader[i].u_TCGen1Vector1  = -1;
		}

		if (i & GLSLDEF_USE_FOG)
		{
			tr.genericShader[i].u_FogAdjustColors = qglGetUniformLocationARB(tr.genericShader[i].program, "u_FogAdjustColors");
			tr.genericShader[i].u_FogDistance     = qglGetUniformLocationARB(tr.genericShader[i].program, "u_FogDistance");
			tr.genericShader[i].u_FogDepth        = qglGetUniformLocationARB(tr.genericShader[i].program, "u_FogDepth");
			tr.genericShader[i].u_FogEyeT         = qglGetUniformLocationARB(tr.genericShader[i].program, "u_FogEyeT");
		}
		else
		{
			tr.genericShader[i].u_FogAdjustColors = -1;
			tr.genericShader[i].u_FogDistance     = -1;
			tr.genericShader[i].u_FogDepth        = -1;
			tr.genericShader[i].u_FogEyeT         = -1;
		}

		if (i & GLSLDEF_USE_DEFORM_VERTEXES)
		{
			tr.genericShader[i].u_DeformGen      = qglGetUniformLocationARB(tr.genericShader[i].program, "u_DeformGen");
			tr.genericShader[i].u_DeformWave     = qglGetUniformLocationARB(tr.genericShader[i].program, "u_DeformWave");
			tr.genericShader[i].u_DeformBulge    = qglGetUniformLocationARB(tr.genericShader[i].program, "u_DeformBulge");
			tr.genericShader[i].u_DeformSpread   = qglGetUniformLocationARB(tr.genericShader[i].program, "u_DeformSpread");
		}
		else
		{
			tr.genericShader[i].u_DeformGen      = -1;
			tr.genericShader[i].u_DeformWave     = -1;
			tr.genericShader[i].u_DeformBulge    = -1;
			tr.genericShader[i].u_DeformSpread   = -1;
		}

		tr.genericShader[i].u_Time           = qglGetUniformLocationARB(tr.genericShader[i].program, "u_Time");
		tr.genericShader[i].u_Color          = qglGetUniformLocationARB(tr.genericShader[i].program, "u_Color");
		tr.genericShader[i].u_AmbientLight   = qglGetUniformLocationARB(tr.genericShader[i].program, "u_AmbientLight");
		tr.genericShader[i].u_DirectedLight  = qglGetUniformLocationARB(tr.genericShader[i].program, "u_DirectedLight");
		tr.genericShader[i].u_LightDir       = qglGetUniformLocationARB(tr.genericShader[i].program, "u_LightDir");
		tr.genericShader[i].u_ViewOrigin     = qglGetUniformLocationARB(tr.genericShader[i].program, "u_ViewOrigin");
		tr.genericShader[i].u_Texture0Matrix = qglGetUniformLocationARB(tr.genericShader[i].program, "u_Texture0Matrix");
		tr.genericShader[i].u_Texture1Matrix = -1; //qglGetUniformLocationARB(tr.genericShader[i].program, "u_Texture1Matrix");
		tr.genericShader[i].u_Texture1Env    = qglGetUniformLocationARB(tr.genericShader[i].program, "u_Texture1Env");

		tr.genericShader[i].u_Texture0Map    = qglGetUniformLocationARB(tr.genericShader[i].program, "u_Texture0Map");
		tr.genericShader[i].u_Texture1Map    = qglGetUniformLocationARB(tr.genericShader[i].program, "u_Texture1Map");

		tr.genericShader[i].u_PortalRange    = qglGetUniformLocationARB(tr.genericShader[i].program, "u_PortalRange");
		tr.genericShader[i].u_ModelMatrix    = -1; //qglGetUniformLocationARB(tr.genericShader[i].program, "u_ModelMatrix");

		if (i & GLSLDEF_USE_VERTEX_ANIMATION)
		{
			tr.genericShader[i].u_VertexLerp     = qglGetUniformLocationARB(tr.genericShader[i].program, "u_VertexLerp");
		}
		else
		{
			tr.genericShader[i].u_VertexLerp     = -1;
		}

		qglUseProgramObjectARB(tr.genericShader[i].program);
		qglUniform1iARB(tr.genericShader[i].u_Texture0Map, 0);
		qglUniform1iARB(tr.genericShader[i].u_Texture1Map, 1);
		qglUseProgramObjectARB(0);

		GLSL_ValidateProgram(tr.genericShader[i].program);
		GLSL_ShowProgramUniforms(tr.genericShader[i].program);
		GL_CheckErrors();
	}

	endTime = ri.Milliseconds();

	ri.Printf(PRINT_ALL, "GLSL shaders load time = %5.2f seconds\n", (endTime - startTime) / 1000.0);
}

void GLSL_ShutdownGPUShaders(void)
{
	int i;

	ri.Printf(PRINT_ALL, "------- GLSL_ShutdownGPUShaders -------\n");

	qglDisableVertexAttribArrayARB(ATTR_INDEX_TEXCOORD0);
	qglDisableVertexAttribArrayARB(ATTR_INDEX_TEXCOORD1);
	qglDisableVertexAttribArrayARB(ATTR_INDEX_POSITION);
	qglDisableVertexAttribArrayARB(ATTR_INDEX_NORMAL);
	qglDisableVertexAttribArrayARB(ATTR_INDEX_COLOR);
	GLSL_BindNullProgram();

	for ( i = 0; i < GLSLDEF_COUNT; i++)
	{
		if(tr.genericShader[i].program)
		{
			if (tr.genericShader[i].vertexShader)
			{
				qglDetachObjectARB(tr.genericShader[i].program, tr.genericShader[i].vertexShader);
				qglDeleteObjectARB(tr.genericShader[i].vertexShader);
			}

			if (tr.genericShader[i].fragmentShader)
			{
				qglDetachObjectARB(tr.genericShader[i].program, tr.genericShader[i].fragmentShader);
				qglDeleteObjectARB(tr.genericShader[i].fragmentShader);
			}

			qglDeleteObjectARB(tr.genericShader[i].program);
			Com_Memset(&tr.genericShader[i], 0, sizeof(shaderProgram_t));
		}
	}

	glState.currentProgram = 0;
	qglUseProgramObjectARB(0);
}


void GLSL_BindProgram(shaderProgram_t * program)
{
	if(!program)
	{
		GLSL_BindNullProgram();
		return;
	}

	if(r_logFile->integer)
	{
		// don't just call LogComment, or we will get a call to va() every frame!
		GLimp_LogComment(va("--- GL_BindProgram( %s ) ---\n", program->name));
	}

	if(glState.currentProgram != program)
	{
		qglUseProgramObjectARB(program->program);
		glState.currentProgram = program;
	}
}

void GLSL_BindNullProgram(void)
{
	if(r_logFile->integer)
	{
		GLimp_LogComment("--- GL_BindNullProgram ---\n");
	}

	if(glState.currentProgram)
	{
		qglUseProgramObjectARB(0);
		glState.currentProgram = NULL;
	}
}


void GLSL_VertexAttribsState(uint32_t stateBits)
{
	uint32_t		diff;

	GLSL_VertexAttribPointers(stateBits);

	diff = stateBits ^ glState.vertexAttribsState;
	if(!diff)
	{
		return;
	}

	if(diff & ATTR_POSITION)
	{
		if(stateBits & ATTR_POSITION)
		{
			GLimp_LogComment("qglEnableVertexAttribArrayARB( ATTR_INDEX_POSITION )\n");
			qglEnableVertexAttribArrayARB(ATTR_INDEX_POSITION);
		}
		else
		{
			GLimp_LogComment("qglDisableVertexAttribArrayARB( ATTR_INDEX_POSITION )\n");
			qglDisableVertexAttribArrayARB(ATTR_INDEX_POSITION);
		}
	}

	if(diff & ATTR_TEXCOORD)
	{
		if(stateBits & ATTR_TEXCOORD)
		{
			GLimp_LogComment("qglEnableVertexAttribArrayARB( ATTR_INDEX_TEXCOORD )\n");
			qglEnableVertexAttribArrayARB(ATTR_INDEX_TEXCOORD0);
		}
		else
		{
			GLimp_LogComment("qglDisableVertexAttribArrayARB( ATTR_INDEX_TEXCOORD )\n");
			qglDisableVertexAttribArrayARB(ATTR_INDEX_TEXCOORD0);
		}
	}

	if(diff & ATTR_LIGHTCOORD)
	{
		if(stateBits & ATTR_LIGHTCOORD)
		{
			GLimp_LogComment("qglEnableVertexAttribArrayARB( ATTR_INDEX_LIGHTCOORD )\n");
			qglEnableVertexAttribArrayARB(ATTR_INDEX_TEXCOORD1);
		}
		else
		{
			GLimp_LogComment("qglDisableVertexAttribArrayARB( ATTR_INDEX_LIGHTCOORD )\n");
			qglDisableVertexAttribArrayARB(ATTR_INDEX_TEXCOORD1);
		}
	}

	if(diff & ATTR_NORMAL)
	{
		if(stateBits & ATTR_NORMAL)
		{
			GLimp_LogComment("qglEnableVertexAttribArrayARB( ATTR_INDEX_NORMAL )\n");
			qglEnableVertexAttribArrayARB(ATTR_INDEX_NORMAL);
		}
		else
		{
			GLimp_LogComment("qglDisableVertexAttribArrayARB( ATTR_INDEX_NORMAL )\n");
			qglDisableVertexAttribArrayARB(ATTR_INDEX_NORMAL);
		}
	}

	if(diff & ATTR_COLOR)
	{
		if(stateBits & ATTR_COLOR)
		{
			GLimp_LogComment("qglEnableVertexAttribArrayARB( ATTR_INDEX_COLOR )\n");
			qglEnableVertexAttribArrayARB(ATTR_INDEX_COLOR);
		}
		else
		{
			GLimp_LogComment("qglDisableVertexAttribArrayARB( ATTR_INDEX_COLOR )\n");
			qglDisableVertexAttribArrayARB(ATTR_INDEX_COLOR);
		}
	}

	if(diff & ATTR_POSITION2)
	{
		if(stateBits & ATTR_POSITION2)
		{
			GLimp_LogComment("qglEnableVertexAttribArrayARB( ATTR_INDEX_POSITION2 )\n");
			qglEnableVertexAttribArrayARB(ATTR_INDEX_POSITION2);
		}
		else
		{
			GLimp_LogComment("qglDisableVertexAttribArrayARB( ATTR_INDEX_POSITION2 )\n");
			qglDisableVertexAttribArrayARB(ATTR_INDEX_POSITION2);
		}
	}

	if(diff & ATTR_NORMAL2)
	{
		if(stateBits & ATTR_NORMAL2)
		{
			GLimp_LogComment("qglEnableVertexAttribArrayARB( ATTR_INDEX_NORMAL2 )\n");
			qglEnableVertexAttribArrayARB(ATTR_INDEX_NORMAL2);
		}
		else
		{
			GLimp_LogComment("qglDisableVertexAttribArrayARB( ATTR_INDEX_NORMAL2 )\n");
			qglDisableVertexAttribArrayARB(ATTR_INDEX_NORMAL2);
		}
	}

	glState.vertexAttribsState = stateBits;
}

void GLSL_VertexAttribPointers(uint32_t attribBits)
{
	if(!glState.currentVBO)
	{
		ri.Error(ERR_FATAL, "GL_VertexAttribPointers: no VBO bound");
		return;
	}

	// don't just call LogComment, or we will get a call to va() every frame!
	GLimp_LogComment(va("--- GL_VertexAttribPointers( %s ) ---\n", glState.currentVBO->name));

	if((attribBits & ATTR_POSITION) && !(glState.vertexAttribPointersSet & ATTR_POSITION))
	{
		GLimp_LogComment("qglVertexAttribPointerARB( ATTR_INDEX_POSITION )\n");

		qglVertexAttribPointerARB(ATTR_INDEX_POSITION, 3, GL_FLOAT, 0, glState.currentVBO->stride_xyz, BUFFER_OFFSET(glState.currentVBO->ofs_xyz + glState.vertexAttribsNewFrame * glState.currentVBO->size_xyz));
		glState.vertexAttribPointersSet |= ATTR_POSITION;
	}

	if((attribBits & ATTR_TEXCOORD) && !(glState.vertexAttribPointersSet & ATTR_TEXCOORD))
	{
		GLimp_LogComment("qglVertexAttribPointerARB( ATTR_INDEX_TEXCOORD )\n");

		qglVertexAttribPointerARB(ATTR_INDEX_TEXCOORD0, 2, GL_FLOAT, 0, glState.currentVBO->stride_st, BUFFER_OFFSET(glState.currentVBO->ofs_st));
		glState.vertexAttribPointersSet |= ATTR_TEXCOORD;
	}

	if((attribBits & ATTR_LIGHTCOORD) && !(glState.vertexAttribPointersSet & ATTR_LIGHTCOORD))
	{
		GLimp_LogComment("qglVertexAttribPointerARB( ATTR_INDEX_LIGHTCOORD )\n");

		qglVertexAttribPointerARB(ATTR_INDEX_TEXCOORD1, 2, GL_FLOAT, 0, glState.currentVBO->stride_lightmap, BUFFER_OFFSET(glState.currentVBO->ofs_lightmap));
		glState.vertexAttribPointersSet |= ATTR_LIGHTCOORD;
	}

	if((attribBits & ATTR_NORMAL) && !(glState.vertexAttribPointersSet & ATTR_NORMAL))
	{
		GLimp_LogComment("qglVertexAttribPointerARB( ATTR_INDEX_NORMAL )\n");

		qglVertexAttribPointerARB(ATTR_INDEX_NORMAL, 3, GL_FLOAT, 0, glState.currentVBO->stride_normal, BUFFER_OFFSET(glState.currentVBO->ofs_normal + glState.vertexAttribsNewFrame * glState.currentVBO->size_normal));
		glState.vertexAttribPointersSet |= ATTR_NORMAL;
	}

	if((attribBits & ATTR_COLOR) && !(glState.vertexAttribPointersSet & ATTR_COLOR))
	{
		GLimp_LogComment("qglVertexAttribPointerARB( ATTR_INDEX_COLOR )\n");

		qglVertexAttribPointerARB(ATTR_INDEX_COLOR, 4, GL_UNSIGNED_BYTE, 1, glState.currentVBO->stride_vertexcolor, BUFFER_OFFSET(glState.currentVBO->ofs_vertexcolor));
		glState.vertexAttribPointersSet |= ATTR_COLOR;
	}

	if((attribBits & ATTR_POSITION2) && !(glState.vertexAttribPointersSet & ATTR_POSITION2))
	{
		GLimp_LogComment("qglVertexAttribPointerARB( ATTR_INDEX_POSITION2 )\n");

		qglVertexAttribPointerARB(ATTR_INDEX_POSITION2, 3, GL_FLOAT, 0, glState.currentVBO->stride_xyz, BUFFER_OFFSET(glState.currentVBO->ofs_xyz + glState.vertexAttribsOldFrame * glState.currentVBO->size_xyz));
		glState.vertexAttribPointersSet |= ATTR_POSITION2;
	}

	if((attribBits & ATTR_NORMAL2) && !(glState.vertexAttribPointersSet & ATTR_NORMAL2))
	{
		GLimp_LogComment("qglVertexAttribPointerARB( ATTR_INDEX_NORMAL2 )\n");

		qglVertexAttribPointerARB(ATTR_INDEX_NORMAL2, 3, GL_FLOAT, 0, glState.currentVBO->stride_normal, BUFFER_OFFSET(glState.currentVBO->ofs_normal + glState.vertexAttribsOldFrame * glState.currentVBO->size_normal));
		glState.vertexAttribPointersSet |= ATTR_NORMAL2;
	}

}

shaderProgram_t *GLSL_GetGenericShaderProgram()
{
	int shaderAttribs = 0;

	if (tess.fogNum)
	{
		shaderAttribs |= GLSLDEF_USE_FOG;
	}

	// swapping these two out causes the worse case frame time to increase due to too many context switches
	// think about doing actual checks if the sort is changed
	shaderAttribs |= GLSLDEF_USE_DEFORM_VERTEXES;
	shaderAttribs |= GLSLDEF_USE_TCGEN;

	if (backEnd.currentEntity && backEnd.currentEntity != &tr.worldEntity)
	{
		shaderAttribs |= GLSLDEF_USE_VERTEX_ANIMATION;
	}

	return &tr.genericShader[shaderAttribs];
}