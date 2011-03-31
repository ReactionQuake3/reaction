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
"attribute vec4 attr_Position;\r\nattribute vec4 attr_TexCoord0;\r\nattribut"
"e vec4 attr_TexCoord1;\r\nattribute vec3 attr_Normal;\r\nattribute vec4 att"
"r_Color;\r\n\r\n#if defined(USE_VERTEX_ANIMATION)\r\nattribute vec4 attr_Po"
"sition2;\r\nattribute vec3 attr_Normal2;\r\n#endif\r\n\r\nuniform mat4   u_"
"Texture0Matrix;\r\nuniform vec3   u_ViewOrigin;\r\n\r\n#if defined(USE_TCGE"
"N)\r\nuniform int    u_TCGen0;\r\nuniform vec4   u_TCGen0Vector0;\r\nunifor"
"m vec4   u_TCGen0Vector1;\r\n#endif\r\n\r\n#if defined(USE_FOG)\r\nuniform "
"vec4   u_FogDistance;\r\nuniform vec4   u_FogDepth;\r\nuniform float  u_Fog"
"EyeT;\r\nuniform int    u_FogAdjustColors;\r\n#endif\r\n\r\n#if defined(USE"
"_DEFORM_VERTEXES)\r\nuniform int    u_DeformGen;\r\nuniform vec4   u_Deform"
"Wave;\r\nuniform vec3   u_DeformBulge;\r\nuniform float  u_DeformSpread;\r"
"\n#endif\r\n\r\nuniform float  u_Time;\r\nuniform int    u_ColorGen;\r\nuni"
"form int    u_AlphaGen;\r\nuniform vec4   u_Color;\r\nuniform mat4   u_Mode"
"lViewProjectionMatrix;\r\nuniform vec3   u_AmbientLight;\r\nuniform vec3   "
"u_DirectedLight;\r\nuniform vec3   u_LightDir;\r\n\r\nuniform float  u_Port"
"alRange;\r\n\r\n#if defined(USE_VERTEX_ANIMATION)\r\nuniform float  u_Verte"
"xLerp;\r\n#endif\r\n\r\nvarying vec2   var_Tex1;\r\nvarying vec2   var_Tex2"
";\r\nvarying vec4   var_Color;\r\n\r\n#if defined(USE_DEFORM_VERTEXES)\r\nf"
"loat triangle(float x)\r\n{\r\n\treturn max(1.0 - abs(x), 0);\r\n}\r\n\r\nf"
"loat sawtooth(float x)\r\n{\r\n\treturn x - floor(x);\r\n}\r\n\r\nvec4 Defo"
"rmPosition(const vec4 pos, const vec3 normal, const vec2 st)\r\n{\r\n\tvec4"
" deformed = pos;\r\n\r\n\tif (u_DeformGen == DGEN_WAVE_SIN)\r\n\t{\r\n\t\tf"
"loat off = (pos.x + pos.y + pos.z) * u_DeformSpread;\r\n\t\tfloat scale = u"
"_DeformWave.x  + sin((off + u_DeformWave.z + (u_Time * u_DeformWave.w)) * 2"
".0 * M_PI) * u_DeformWave.y;\r\n\t\tvec3 offset = normal * scale;\r\n\r\n\t"
"\tdeformed.xyz += offset;\r\n\t}\r\n\telse if (u_DeformGen == DGEN_WAVE_SQU"
"ARE)\r\n\t{\r\n\t\tfloat off = (pos.x + pos.y + pos.z) * u_DeformSpread;\r"
"\n\t\tfloat scale = u_DeformWave.x  + sign(sin((off + u_DeformWave.z + (u_T"
"ime * u_DeformWave.w)) * 2.0 * M_PI)) * u_DeformWave.y;\r\n\t\tvec3 offset "
"= normal * scale;\r\n\r\n\t\tdeformed.xyz += offset;\r\n\t}\r\n\telse if (u"
"_DeformGen == DGEN_WAVE_TRIANGLE)\r\n\t{\r\n\t\tfloat off = (pos.x + pos.y "
"+ pos.z) * u_DeformSpread;\r\n\t\tfloat scale = u_DeformWave.x  + triangle("
"off + u_DeformWave.z + (u_Time * u_DeformWave.w)) * u_DeformWave.y;\r\n\t\t"
"vec3 offset = normal * scale;\r\n\r\n\t\tdeformed.xyz += offset;\r\n\t}\r\n"
"\telse if (u_DeformGen == DGEN_WAVE_SAWTOOTH)\r\n\t{\r\n\t\tfloat off = (po"
"s.x + pos.y + pos.z) * u_DeformSpread;\r\n\t\tfloat scale = u_DeformWave.x "
" + sawtooth(off + u_DeformWave.z + (u_Time * u_DeformWave.w)) * u_DeformWav"
"e.y;\r\n\t\tvec3 offset = normal * scale;\r\n\r\n\t\tdeformed.xyz += offset"
";\r\n\t}\r\n\telse if (u_DeformGen == DGEN_WAVE_INVERSE_SAWTOOTH)\r\n\t{\r"
"\n\t\tfloat off = (pos.x + pos.y + pos.z) * u_DeformSpread;\r\n\t\tfloat sc"
"ale = u_DeformWave.x + (1.0 - sawtooth(off + u_DeformWave.z + (u_Time * u_D"
"eformWave.w))) * u_DeformWave.y;\r\n\t\tvec3 offset = normal * scale;\r\n\r"
"\n\t\tdeformed.xyz += offset;\r\n\t}\r\n\telse if (u_DeformGen == DGEN_BULG"
"E)\r\n\t{\r\n\t\tfloat bulgeWidth = u_DeformBulge.x;\r\n\t\tfloat bulgeHeig"
"ht = u_DeformBulge.y;\r\n\t\tfloat bulgeSpeed = u_DeformBulge.z;\r\n\r\n\t"
"\tfloat now = u_Time * bulgeSpeed;\r\n\r\n\t\tfloat off = (M_PI * 0.25) * s"
"t.x * bulgeWidth + now;\r\n\t\tfloat scale = sin(off) * bulgeHeight;\r\n\t"
"\tvec3 offset = normal * scale;\r\n\r\n\t\tdeformed.xyz += offset;\r\n\t}\r"
"\n\r\n\treturn deformed;\r\n}\r\n#endif\r\n\r\n#if defined(USE_TCGEN)\r\nve"
"c2 GenTexCoords(int TCGen, vec4 position, vec3 normal, mat4 texMatrix, vec4"
" TCGenVector0, vec4 TCGenVector1)\r\n{\r\n\tvec2 tex = vec2(0.0);\r\n\r\n\t"
"if (TCGen == TCGEN_LIGHTMAP)\r\n\t{\r\n\t\ttex = attr_TexCoord1.st;\r\n\t}"
"\r\n\telse if (TCGen == TCGEN_TEXTURE)\r\n\t{\r\n\t\ttex = attr_TexCoord0.s"
"t;\r\n\t}\r\n\telse if (TCGen == TCGEN_ENVIRONMENT_MAPPED)\r\n\t{\r\n\t\tve"
"c3 viewer = normalize(u_ViewOrigin - position.xyz);\r\n\r\n\t\tfloat d = do"
"t(normal, viewer);\r\n\r\n\t\tvec3 reflected = normal * 2.0 * d - viewer;\r"
"\n\r\n\t\ttex.s = 0.5 + reflected.y * 0.5;\r\n\t\ttex.t = 0.5 - reflected.z"
" * 0.5;\r\n\t}\r\n\telse if (TCGen == TCGEN_VECTOR)\r\n\t{\r\n\t\ttex.s = d"
"ot(position.xyz, TCGenVector0.xyz);\r\n\t\ttex.t = dot(position.xyz, TCGenV"
"ector1.xyz);\r\n\t}\r\n\t\r\n\treturn tex;\r\n}\r\n#endif\r\n\r\nvoid main("
")\r\n{\r\n\tvec4 position;\r\n\tvec3 normal;\r\n\tvec4 tex;\r\n\r\n#if defi"
"ned(USE_VERTEX_ANIMATION)\r\n\tif (u_VertexLerp > 0.0)\r\n\t{\r\n\t\tpositi"
"on = mix(attr_Position, attr_Position2, u_VertexLerp);\r\n\t\tnormal = mix("
"attr_Normal, attr_Normal2, u_VertexLerp);\r\n\t\tnormal = normalize(normal)"
";\r\n\t}\r\n\telse\r\n#endif\r\n\t{\r\n\t\tposition = attr_Position;\r\n\t"
"\tnormal = attr_Normal;\r\n\t}\r\n\r\n#if defined(USE_DEFORM_VERTEXES)\r\n"
"\tposition = DeformPosition(position, normal, attr_TexCoord0.st);\r\n#endif"
"\r\n\r\n\tgl_Position = u_ModelViewProjectionMatrix * position;\r\n\r\n\r\n"
"\ttex = vec4(1.0, 1.0, 1.0, 0.0);\r\n\r\n#if defined(USE_TCGEN)\r\n\ttex.st"
" = GenTexCoords(u_TCGen0, position, normal, u_Texture0Matrix, u_TCGen0Vecto"
"r0, u_TCGen0Vector1);\r\n#else\r\n\ttex.st = attr_TexCoord0.st;\r\n#endif\r"
"\n    \r\n\tvar_Tex1 = (u_Texture0Matrix * tex).st;\r\n\r\n\tif (u_Texture0"
"Matrix[3][0] != 0)\r\n\t{\r\n\t\tvar_Tex1.s += sin(((position.x + position."
"z) * 1.0 / 128.0 * 0.125 + u_Texture0Matrix[3][1]) * 2.0 * M_PI) * u_Textur"
"e0Matrix[3][0];\r\n\t\tvar_Tex1.t += sin((position.y * 1.0 / 128.0 * 0.125 "
"+ u_Texture0Matrix[3][1]) * 2.0 * M_PI) * u_Texture0Matrix[3][0];\r\n\t}\r"
"\n\r\n\tvar_Tex2 = attr_TexCoord1.st;\r\n\r\n\tif (u_ColorGen == CGEN_IDENT"
"ITY)\r\n\t{\r\n\t\tvar_Color.rgb = vec3(1.0);\r\n\t}\r\n\telse if (u_ColorG"
"en == CGEN_LIGHTING_DIFFUSE)\r\n\t{\r\n\t\tfloat incoming = dot(attr_Normal"
", u_LightDir);\r\n\r\n\t\tif (incoming <= 0)\r\n\t\t{\r\n\t\t\tvar_Color.rg"
"b = u_AmbientLight;\r\n\t\t}\r\n\t\telse\r\n\t\t{\r\n\t\t\tvar_Color.rgb = "
"min(u_AmbientLight + u_DirectedLight * incoming, vec3(1));\r\n\t\t}\r\n\t}"
"\r\n\telse if (u_ColorGen == CGEN_EXACT_VERTEX)\r\n\t{\r\n\t\tvar_Color.rgb"
" = attr_Color.rgb;\r\n\t}\r\n\telse if (u_ColorGen == CGEN_VERTEX)\r\n\t{\r"
"\n\t\tvar_Color.rgb = attr_Color.rgb * u_Color.rgb;\r\n\t}\r\n\telse if (u_"
"ColorGen == CGEN_ONE_MINUS_VERTEX)\r\n\t{\r\n\t\tvar_Color.rgb = (vec3(1.0)"
" - attr_Color.rgb) * u_Color.rgb;\r\n\t}\r\n\telse\r\n\t{\r\n\t\tvar_Color."
"rgb = u_Color.rgb;\r\n\t}\r\n\r\n\tif (u_AlphaGen == AGEN_IDENTITY)\r\n\t{"
"\r\n\t\tvar_Color.a = 1.0;\r\n\t}\r\n\telse if (u_AlphaGen == AGEN_LIGHTING"
"_SPECULAR)\r\n\t{\r\n\t\tvec3 lightDir = vec3(-960.0, -1980.0, 96.0) - posi"
"tion.xyz;\r\n\t\tlightDir = normalize(lightDir);\r\n\r\n\t\tfloat d = dot(a"
"ttr_Normal, lightDir);\r\n\t\tvec3 reflected = attr_Normal * 2.0 * d - ligh"
"tDir;\r\n\r\n\t\tvec3 viewer = u_ViewOrigin - position.xyz;\r\n\t\tfloat il"
"ength = 1.0 / length(viewer);\r\n\r\n\t\tfloat l = dot(reflected, viewer);"
"\r\n\t\tl *= ilength;\r\n\r\n\t\tif (l < 0.0)\r\n\t\t{\r\n\t\t\tvar_Color.a"
" = 0.0;\r\n\t\t}\r\n\t\telse\r\n\t\t{\r\n\t\t\tl = l*l;\r\n\t\t\tl = l*l;\r"
"\n\t\t\tvar_Color.a = min(l, 1.0);\r\n\t\t}\r\n\t}\r\n\telse if (u_AlphaGen"
" == AGEN_VERTEX)\r\n\t{\r\n\t\tvar_Color.a = attr_Color.a;\r\n\t}\r\n\telse"
" if (u_AlphaGen == AGEN_ONE_MINUS_VERTEX)\r\n\t{\r\n\t\tvar_Color.a = 1.0 -"
" attr_Color.a;\r\n\t}\r\n\telse if (u_AlphaGen == AGEN_PORTAL)\r\n\t{\r\n\t"
"\tfloat len;\r\n\t\tvec3 v;\r\n\r\n\t\tv = position.xyz - u_ViewOrigin;\r\n"
"\t\tlen = length(v);\r\n\r\n\t\tlen /= u_PortalRange;\r\n\r\n\t\tvar_Color."
"a = clamp(len, 0.0, 1.0);\r\n\t}\r\n\telse\r\n\t{\r\n\t\tvar_Color.a = u_Co"
"lor.a;\r\n\t}\r\n\r\n#if defined (USE_FOG)\r\n\tif (u_FogAdjustColors != AC"
"FF_NONE) \r\n\t{\r\n\t\tfloat s = dot(position.xyz, u_FogDistance.xyz) + u_"
"FogDistance.a;\r\n\t\tfloat t = dot(position.xyz, u_FogDepth.xyz) + u_FogDe"
"pth.a;\r\n\t\t\r\n\t\tif (s < 0.0 || t < 0.0 || (u_FogEyeT < 0.0 && t < 1.0"
") )\r\n\t\t{\r\n\t\t\ts = 0.0;\r\n\t\t}\r\n\t\telse\r\n\t\t{\r\n\t\t\tif (u"
"_FogEyeT < 0.0)\r\n\t\t\t{\r\n\t\t\t\ts *= t / (t - u_FogEyeT);\r\n\t\t\t}"
"\r\n\r\n\t\t\ts *= 8.0;\r\n\t\t\t\t  \r\n\t\t\ts = clamp(s, 0.0, 1.0);\r\n"
"\r\n\t\t\ts = 1.0 - sqrt(s);\r\n\t\t}\r\n\t\t\r\n\t\tif (u_FogAdjustColors "
"== ACFF_MODULATE_RGB)\r\n\t\t{\r\n\t\t\tvar_Color.xyz *= s;\r\n\t\t}\r\n\t"
"\telse if (u_FogAdjustColors == ACFF_MODULATE_ALPHA)\r\n\t\t{\r\n\t\t\tvar_"
"Color.a *= s;\r\n\t\t}\r\n\t\telse if (u_FogAdjustColors == ACFF_MODULATE_R"
"GBA)\r\n\t\t{\r\n\t\t\tvar_Color *= s;\r\n\t\t}\r\n\t}\r\n#endif\r\n}\r\n";

static const char *fallbackGenericShader_fp = 
"uniform sampler2D u_Texture0Map;\r\nuniform sampler2D u_Texture1Map;\r\nuni"
"form int       u_Texture1Env;\r\n\r\nvarying vec2      var_Tex1;\r\nvarying"
" vec2      var_Tex2;\r\nvarying vec4      var_Color;\r\n\r\n\r\nvoid main()"
"\r\n{\r\n\tvec4 color;\r\n\r\n\tif (u_Texture1Env != 2)\r\n\t{\r\n\t\tcolor"
" = texture2D(u_Texture0Map, var_Tex1);\r\n\t}\r\n\r\n\tif (u_Texture1Env !="
" 0)\r\n\t{\r\n\t\tvec4 color2 = texture2D(u_Texture1Map, var_Tex2);\r\n\r\n"
"\t\tif (u_Texture1Env == GL_MODULATE)\r\n\t\t{\r\n\t\t\tcolor *= color2;\r"
"\n\t\t}\r\n\t\t\telse if (u_Texture1Env == GL_ADD)\r\n\t\t{\r\n\t\t\tcolor "
"+= color2;\r\n\t\t}\r\n\t\t\telse // if (u_Texture1Env == GL_REPLACE)\r\n\t"
"\t{\r\n\t\t\tcolor = color2;\r\n\t\t}\r\n\t}\r\n\r\n\tcolor *= var_Color;\r"
"\n\r\n\tgl_FragColor = color;\r\n}\r\n";

static const char *fallbackLightmappedShader_vp = 
"#version 120\r\n\r\n#ifndef M_PI\r\n#define M_PI 3.14159265358979323846f\r"
"\n#endif\r\n\r\nattribute vec4 attr_Position;\r\nattribute vec4 attr_TexCoo"
"rd0;\r\nattribute vec4 attr_TexCoord1;\r\n\r\nuniform mat4   u_Texture0Matr"
"ix;\r\nuniform mat4   u_ModelViewProjectionMatrix;\r\n\r\nvarying vec2   va"
"r_Tex1;\r\nvarying vec2   var_Tex2;\r\n\r\nvoid main()\r\n{\r\n\tvec4 tex ="
" vec4(1, 1, 1, 0);\r\n\r\n\tgl_Position = u_ModelViewProjectionMatrix * att"
"r_Position;\r\n\r\n\ttex.st = attr_TexCoord0.st;\r\n    \r\n\tvar_Tex1 = (u"
"_Texture0Matrix * tex).st;\r\n\r\n\tif (u_Texture0Matrix[3][0] != 0)\r\n\t{"
"\r\n\t\tvar_Tex1.s += sin(((attr_Position.x + attr_Position.z) * 1.0 / 128."
"0 * 0.125 + u_Texture0Matrix[3][1]) * 2.0 * M_PI) * u_Texture0Matrix[3][0];"
"\r\n\t\tvar_Tex1.t += sin((attr_Position.y * 1.0 / 128.0 * 0.125 + u_Textur"
"e0Matrix[3][1]) * 2.0 * M_PI) * u_Texture0Matrix[3][0];\r\n\t}\r\n\r\n\tvar"
"_Tex2 = attr_TexCoord1.st;\r\n}\r\n";

static const char *fallbackLightmappedShader_fp =
"#version 120\r\n\r\nuniform sampler2D    u_Texture0Map;\r\nuniform sampler2"
"D    u_Texture1Map;\r\n\r\nvarying vec2         var_Tex1;\r\nvarying vec2  "
"       var_Tex2;\r\n\r\n\r\nvoid\tmain()\r\n{\r\n\tvec4 color, light;\r\n\r"
"\n\tcolor = texture2D(u_Texture0Map, var_Tex1);\r\n\tlight = texture2D(u_Te"
"xture1Map, var_Tex2);\r\n\r\n\tgl_FragColor = color * light;\r\n}\r\n";

static const char *fallbackTextureOnlyShader_vp =
"#version 120\r\n\r\nattribute vec4 attr_Position;\r\nattribute vec4 attr_Te"
"xCoord0;\r\n\r\nuniform mat4   u_ModelViewProjectionMatrix;\r\n\r\nvarying "
"vec2   var_Tex1;\r\n\r\n\r\nvoid main()\r\n{\r\n\tgl_Position = u_ModelView"
"ProjectionMatrix * attr_Position;\r\n\tvar_Tex1 = attr_TexCoord0.st;\r\n}\r"
"\n";

static const char *fallbackTextureOnlyShader_fp =
"#version 120\r\n\r\nuniform sampler2D    u_Texture0Map;\r\n\r\nvarying vec2"
"         var_Tex1;\r\n\r\n\r\nvoid main()\r\n{\r\n\tgl_FragColor = texture2"
"D(u_Texture0Map, var_Tex1);\r\n}\r\n";

static const char *fallbackFogPassShader_vp =
"attribute vec4  attr_Position;\r\nattribute vec3  attr_Normal;\r\nattribute"
" vec4  attr_TexCoord0;\r\n\r\n//#if defined(USE_VERTEX_ANIMATION)\r\nattrib"
"ute vec4  attr_Position2;\r\nattribute vec3  attr_Normal2;\r\n//#endif\r\n"
"\r\nuniform vec4    u_FogDistance;\r\nuniform vec4    u_FogDepth;\r\nunifor"
"m float   u_FogEyeT;\r\n\r\n//#if defined(USE_DEFORM_VERTEXES)\r\nuniform i"
"nt     u_DeformGen;\r\nuniform vec4    u_DeformWave;\r\nuniform vec3    u_D"
"eformBulge;\r\nuniform float   u_DeformSpread;\r\n//#endif\r\n\r\nuniform f"
"loat   u_Time;\r\nuniform vec4    u_Color;\r\nuniform mat4    u_ModelViewPr"
"ojectionMatrix;\r\n\r\n//#if defined(USE_VERTEX_ANIMATION)\r\nuniform float"
"   u_VertexLerp;\r\n//#endif\r\n\r\nvarying vec4    var_Color;\r\n\r\n//#if"
" defined(USE_DEFORM_VERTEXES)\r\nfloat triangle(float x)\r\n{\r\n\treturn m"
"ax(1.0 - abs(x), 0);\r\n}\r\n\r\nfloat sawtooth(float x)\r\n{\r\n\treturn x"
" - floor(x);\r\n}\r\n\r\nvec4 DeformPosition(const vec4 pos, const vec3 nor"
"mal, const vec2 st)\r\n{\r\n\tvec4 deformed = pos;\r\n\r\n\tif (u_DeformGen"
" == DGEN_WAVE_SIN)\r\n\t{\r\n\t\tfloat off = (pos.x + pos.y + pos.z) * u_De"
"formSpread;\r\n\t\tfloat scale = u_DeformWave.x  + sin((off + u_DeformWave."
"z + (u_Time * u_DeformWave.w)) * 2.0 * M_PI) * u_DeformWave.y;\r\n\t\tvec3 "
"offset = normal * scale;\r\n\r\n\t\tdeformed.xyz += offset;\r\n\t}\r\n\tels"
"e if (u_DeformGen == DGEN_WAVE_SQUARE)\r\n\t{\r\n\t\tfloat off = (pos.x + p"
"os.y + pos.z) * u_DeformSpread;\r\n\t\tfloat scale = u_DeformWave.x  + sign"
"(sin((off + u_DeformWave.z + (u_Time * u_DeformWave.w)) * 2.0 * M_PI)) * u_"
"DeformWave.y;\r\n\t\tvec3 offset = normal * scale;\r\n\r\n\t\tdeformed.xyz "
"+= offset;\r\n\t}\r\n\telse if (u_DeformGen == DGEN_WAVE_TRIANGLE)\r\n\t{\r"
"\n\t\tfloat off = (pos.x + pos.y + pos.z) * u_DeformSpread;\r\n\t\tfloat sc"
"ale = u_DeformWave.x  + triangle(off + u_DeformWave.z + (u_Time * u_DeformW"
"ave.w)) * u_DeformWave.y;\r\n\t\tvec3 offset = normal * scale;\r\n\r\n\t\td"
"eformed.xyz += offset;\r\n\t}\r\n\telse if (u_DeformGen == DGEN_WAVE_SAWTOO"
"TH)\r\n\t{\r\n\t\tfloat off = (pos.x + pos.y + pos.z) * u_DeformSpread;\r\n"
"\t\tfloat scale = u_DeformWave.x  + sawtooth(off + u_DeformWave.z + (u_Time"
" * u_DeformWave.w)) * u_DeformWave.y;\r\n\t\tvec3 offset = normal * scale;"
"\r\n\r\n\t\tdeformed.xyz += offset;\r\n\t}\r\n\telse if (u_DeformGen == DGE"
"N_WAVE_INVERSE_SAWTOOTH)\r\n\t{\r\n\t\tfloat off = (pos.x + pos.y + pos.z) "
"* u_DeformSpread;\r\n\t\tfloat scale = u_DeformWave.x + (1.0 - sawtooth(off"
" + u_DeformWave.z + (u_Time * u_DeformWave.w))) * u_DeformWave.y;\r\n\t\tve"
"c3 offset = normal * scale;\r\n\r\n\t\tdeformed.xyz += offset;\r\n\t}\r\n\t"
"else if (u_DeformGen == DGEN_BULGE)\r\n\t{\r\n\t\tfloat bulgeWidth = u_Defo"
"rmBulge.x;\r\n\t\tfloat bulgeHeight = u_DeformBulge.y;\r\n\t\tfloat bulgeSp"
"eed = u_DeformBulge.z;\r\n\r\n\t\tfloat now = u_Time * bulgeSpeed;\r\n\r\n"
"\t\tfloat off = (M_PI * 0.25) * st.x * bulgeWidth + now;\r\n\t\tfloat scale"
" = sin(off) * bulgeHeight;\r\n\t\tvec3 offset = normal * scale;\r\n\r\n\t\t"
"deformed.xyz += offset;\r\n\t}\r\n\r\n\treturn deformed;\r\n}\r\n//#endif\r"
"\n\r\n\r\nvoid\tmain()\r\n{\r\n\tvec4 position;\r\n\tvec3 normal;\r\n\r\n//"
"#if defined(USE_VERTEX_ANIMATION)\r\n\tif (u_VertexLerp > 0.0)\r\n\t{\r\n\t"
"\tposition = mix(attr_Position, attr_Position2, u_VertexLerp);\r\n\t\tnorma"
"l = mix(attr_Normal, attr_Normal2, u_VertexLerp);\r\n\t\tnormal = normalize"
"(normal);\r\n\t}\r\n\telse\r\n//#endif\r\n\t{\r\n\t\tposition = attr_Positi"
"on;\r\n\t\tnormal = attr_Normal;\r\n\t}\r\n\r\n//#if defined(USE_DEFORM_VER"
"TEXES)\r\n\tposition = DeformPosition(position, normal, attr_TexCoord0.st);"
"\r\n//#endif\r\n\r\n\tgl_Position = u_ModelViewProjectionMatrix * position;"
"\r\n\r\n\t{\r\n\t\tfloat s = dot(position.xyz, u_FogDistance.xyz) + u_FogDi"
"stance.a;\r\n\t\tfloat t = dot(position.xyz, u_FogDepth.xyz) + u_FogDepth.a"
";\r\n\r\n\t\tif (s < 0.0 || t < 0.0 || (u_FogEyeT < 0.0 && t < 1.0) )\r\n\t"
"\t{\r\n\t\t\ts = 0.0;\r\n\t\t}\r\n\t\telse\r\n\t\t{\r\n\t\t\tif (u_FogEyeT "
"< 0.0)\r\n\t\t\t{\r\n\t\t\t\ts *= t / (t - u_FogEyeT);\r\n\t\t\t}\r\n\r\n\t"
"\t\ts *= 8.0;\r\n\t\t  \r\n\t\t\ts = clamp(s, 0.0, 1.0);\r\n\r\n\t\t\ts = s"
"qrt(s);\r\n\t\t}\r\n\r\n\t\tvar_Color.xyz = u_Color.xyz;\r\n\t\tvar_Color.a"
" = u_Color.a * s;\r\n\t}\r\n}\r\n";

static const char *fallbackFogPassShader_fp =
"varying vec4         var_Color;\r\n\r\n\r\nvoid\tmain()\r\n{\r\n\tgl_FragCo"
"lor = var_Color;\r\n}\r\n";

static const char *fallbackDlightShader_vp =
"attribute vec4 attr_Position;\r\nattribute vec4 attr_TexCoord0;\r\nattribut"
"e vec3 attr_Normal;\r\n\r\nattribute vec4 attr_Position2;\r\nattribute vec3"
" attr_Normal2;\r\n\r\nuniform vec4   u_DlightInfo;\r\n\r\nuniform int    u_"
"DeformGen;\r\nuniform vec4   u_DeformWave;\r\nuniform vec3   u_DeformBulge;"
"\r\nuniform float  u_DeformSpread;\r\n\r\nuniform float  u_Time;\r\nuniform"
" vec4   u_Color;\r\nuniform mat4   u_ModelViewProjectionMatrix;\r\n\r\nunif"
"orm float  u_VertexLerp;\r\n\r\nvarying vec2   var_Tex1;\r\nvarying vec4   "
"var_Color;\r\n\r\nfloat triangle(float x)\r\n{\r\n\treturn max(1.0 - abs(x)"
", 0);\r\n}\r\n\r\nfloat sawtooth(float x)\r\n{\r\n\treturn x - floor(x);\r"
"\n}\r\n\r\nvec4 DeformPosition(const vec4 pos, const vec3 normal, const vec"
"2 st)\r\n{\r\n\tvec4 deformed = pos;\r\n\r\n\tif (u_DeformGen == DGEN_WAVE_"
"SIN)\r\n\t{\r\n\t\tfloat off = (pos.x + pos.y + pos.z) * u_DeformSpread;\r"
"\n\t\tfloat scale = u_DeformWave.x  + sin((off + u_DeformWave.z + (u_Time *"
" u_DeformWave.w)) * 2.0 * M_PI) * u_DeformWave.y;\r\n\t\tvec3 offset = norm"
"al * scale;\r\n\r\n\t\tdeformed.xyz += offset;\r\n\t}\r\n\telse if (u_Defor"
"mGen == DGEN_WAVE_SQUARE)\r\n\t{\r\n\t\tfloat off = (pos.x + pos.y + pos.z)"
" * u_DeformSpread;\r\n\t\tfloat scale = u_DeformWave.x  + sign(sin((off + u"
"_DeformWave.z + (u_Time * u_DeformWave.w)) * 2.0 * M_PI)) * u_DeformWave.y;"
"\r\n\t\tvec3 offset = normal * scale;\r\n\r\n\t\tdeformed.xyz += offset;\r"
"\n\t}\r\n\telse if (u_DeformGen == DGEN_WAVE_TRIANGLE)\r\n\t{\r\n\t\tfloat "
"off = (pos.x + pos.y + pos.z) * u_DeformSpread;\r\n\t\tfloat scale = u_Defo"
"rmWave.x  + triangle(off + u_DeformWave.z + (u_Time * u_DeformWave.w)) * u_"
"DeformWave.y;\r\n\t\tvec3 offset = normal * scale;\r\n\r\n\t\tdeformed.xyz "
"+= offset;\r\n\t}\r\n\telse if (u_DeformGen == DGEN_WAVE_SAWTOOTH)\r\n\t{\r"
"\n\t\tfloat off = (pos.x + pos.y + pos.z) * u_DeformSpread;\r\n\t\tfloat sc"
"ale = u_DeformWave.x  + sawtooth(off + u_DeformWave.z + (u_Time * u_DeformW"
"ave.w)) * u_DeformWave.y;\r\n\t\tvec3 offset = normal * scale;\r\n\r\n\t\td"
"eformed.xyz += offset;\r\n\t}\r\n\telse if (u_DeformGen == DGEN_WAVE_INVERS"
"E_SAWTOOTH)\r\n\t{\r\n\t\tfloat off = (pos.x + pos.y + pos.z) * u_DeformSpr"
"ead;\r\n\t\tfloat scale = u_DeformWave.x + (1.0 - sawtooth(off + u_DeformWa"
"ve.z + (u_Time * u_DeformWave.w))) * u_DeformWave.y;\r\n\t\tvec3 offset = n"
"ormal * scale;\r\n\r\n\t\tdeformed.xyz += offset;\r\n\t}\r\n\telse if (u_De"
"formGen == DGEN_BULGE)\r\n\t{\r\n\t\tfloat bulgeWidth = u_DeformBulge.x;\r"
"\n\t\tfloat bulgeHeight = u_DeformBulge.y;\r\n\t\tfloat bulgeSpeed = u_Defo"
"rmBulge.z;\r\n\r\n\t\tfloat now = u_Time * bulgeSpeed;\r\n\r\n\t\tfloat off"
" = (M_PI * 0.25) * st.x * bulgeWidth + now;\r\n\t\tfloat scale = sin(off) *"
" bulgeHeight;\r\n\t\tvec3 offset = normal * scale;\r\n\r\n\t\tdeformed.xyz "
"+= offset;\r\n\t}\r\n\r\n\treturn deformed;\r\n}\r\n\r\n\r\nvoid main()\r\n"
"{\r\n\tvec4 position;\r\n\tvec3 normal;\r\n\tvec3 dist;\r\n\tvec2 tex;\r\n"
"\tfloat dlightmod;\r\n\r\n\tif (u_VertexLerp > 0.0)\r\n\t{\r\n\t\tposition "
"= mix(attr_Position, attr_Position2, u_VertexLerp);\r\n\t\tnormal = mix(att"
"r_Normal, attr_Normal2, u_VertexLerp);\r\n\t\tnormal = normalize(normal);\r"
"\n\t}\r\n\telse\r\n\t{\r\n\t\tposition = attr_Position;\r\n\t\tnormal = att"
"r_Normal;\r\n\t}\r\n\r\n\tposition = DeformPosition(position, normal, attr_"
"TexCoord0.st);\r\n\r\n\tgl_Position = u_ModelViewProjectionMatrix * positio"
"n;\r\n\t\r\n\t\r\n\ttex = vec2(0);\r\n\t\r\n\tdist = u_DlightInfo.xyz - pos"
"ition.xyz;\t\r\n\tdlightmod = 0;\r\n\r\n\tif (!(dot(dist, normal) < 0))\r\n"
"\t{\r\n\t\tfloat diffz = abs(dist.z);\r\n\t\tfloat radius = 1.0 / u_DlightI"
"nfo.a;\r\n    \r\n\t\tif (diffz <= radius)\r\n\t\t{\r\n\t\t\ttex = vec2(0.5"
") + dist.xy * u_DlightInfo.a;\r\n\r\n\t\t\tif (diffz < radius * 0.5)\r\n\t"
"\t\t{\r\n\t\t\t\tdlightmod = 1.0;\r\n\t\t\t}\r\n\t\t\telse\r\n\t\t\t{\r\n\t"
"\t\t\tdlightmod = 2.0 * (radius - diffz) * u_DlightInfo.a;\r\n\t\t\t}\r\n\t"
"\t}\r\n\t}\r\n\r\n\tvar_Tex1 = tex;\r\n\tvar_Color.rgb = u_Color.rgb * dlig"
"htmod;\r\n\tvar_Color.a = u_Color.a;\r\n}\r\n";

static const char *fallbackDlightShader_fp =
"uniform sampler2D u_Texture0Map;\r\n\r\nvarying vec2      var_Tex1;\r\nvary"
"ing vec4      var_Color;\r\n\r\n\r\nvoid main()\r\n{\r\n\tvec4 color;\r\n\r"
"\n\tcolor = texture2D(u_Texture0Map, var_Tex1);\r\n\r\n\tcolor *= var_Color"
";\r\n\r\n\tgl_FragColor = color;\r\n}\r\n";


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

static int GLSL_CompileGPUShader(GLhandleARB program, GLhandleARB *prevShader, const GLcharARB *buffer, int size, GLenum shaderType, const GLcharARB *extra, qboolean addHeader)
{
	GLint           compiled;
	GLhandleARB     shader;

	shader = qglCreateShaderObjectARB(shaderType);

	if (addHeader)
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

		Q_strcat(bufferExtra, sizeof(bufferExtra),
								 va("#ifndef acff_t\n"
									"#define acff_t\n"
									"#define ACFF_NONE %i\n"
									"#define ACFF_MODULATE_RGB %i\n"
									"#define ACFF_MODULATE_RGBA %i\n"
									"#define ACFF_MODULATE_ALPHA %i\n"
									"#endif\n",
									ACFF_NONE,
									ACFF_MODULATE_RGB,
									ACFF_MODULATE_RGBA,
									ACFF_MODULATE_ALPHA));

		Q_strcat(bufferExtra, sizeof(bufferExtra),
								 va("#ifndef texenv_t\n"
									"#define texenv_t\n"
									"#define GL_MODULATE %i\n"
									"#define GL_ADD %i\n"
									"#define GL_REPLACE %i\n"
									"#endif\n",
									GL_MODULATE,
									GL_ADD,
									GL_REPLACE));

	

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

		bufferFinal = ri.Hunk_AllocateTempMemory(size + sizeExtra);

		strcpy(bufferFinal, bufferExtra);
		Q_strcat(bufferFinal, sizeFinal, buffer);

		qglShaderSourceARB(shader, 1, (const GLcharARB **)&bufferFinal, &sizeFinal);

		ri.Hunk_FreeTempMemory(bufferFinal);
	}
	else
	{
		int sizeFinal = size;
		qglShaderSourceARB(shader, 1, (const GLcharARB **)&buffer, &sizeFinal);
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


static int GLSL_LoadGPUShader(GLhandleARB program, GLhandleARB *prevShader, const char *name, GLenum shaderType, const GLcharARB *extra, qboolean addHeader)
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

	result = GLSL_CompileGPUShader(program, prevShader, buffer, size, shaderType, extra, addHeader);

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

static int GLSL_InitGPUShader(shaderProgram_t * program, const char *name, int attribs, qboolean fragmentShader, const GLcharARB *extra, qboolean addHeader,
							  const char *fallback_vp, const char *fallback_fp, int numUniforms)
{
	ri.Printf(PRINT_DEVELOPER, "------- GPU shader -------\n");

	if(strlen(name) >= MAX_QPATH)
	{
		ri.Error(ERR_DROP, "GLSL_InitGPUShader: \"%s\" is too long\n", name);
	}

	Q_strncpyz(program->name, name, sizeof(program->name));

	program->program = qglCreateProgramObjectARB();
	program->attribs = attribs;

	if (!(GLSL_LoadGPUShader(program->program, &program->vertexShader, name, GL_VERTEX_SHADER_ARB, extra, addHeader)))
	{
		ri.Printf(PRINT_ALL, "GLSL_InitGPUShader: Unable to load \"%s\" as GL_VERTEX_SHADER_ARB\n", name);
		if (fallback_vp)
		{
			ri.Printf(PRINT_ALL, "compiling fallback...\n");
			if (!GLSL_CompileGPUShader(program->program, &program->vertexShader, fallback_vp, strlen(fallback_vp), GL_VERTEX_SHADER_ARB, extra, addHeader))
			{
				ri.Printf(PRINT_ALL, "Fallback failed!\n");
				qglDeleteObjectARB(program->program);
				return 0;
			}
		}
		else
		{
			qglDeleteObjectARB(program->program);
			return 0;
		}
	}

	if(fragmentShader)
	{
		if(!(GLSL_LoadGPUShader(program->program, &program->fragmentShader, name, GL_FRAGMENT_SHADER_ARB, extra, addHeader)))
		{
			ri.Printf(PRINT_ALL, "GLSL_InitGPUShader: Unable to load \"%s\" as GL_FRAGMENT_SHADER_ARB\n", name);
			if (fallback_fp)
			{
				ri.Printf(PRINT_ALL, "compiling fallback...\n");
				if (!GLSL_CompileGPUShader(program->program, &program->fragmentShader, fallback_fp, strlen(fallback_fp), GL_FRAGMENT_SHADER_ARB, extra, addHeader))
				{
					ri.Printf(PRINT_ALL, "Fallback failed!\n");
					qglDeleteObjectARB(program->program);
					return 0;
				}
			}
			else
			{
				qglDeleteObjectARB(program->program);
				return 0;
			}
		}
	}

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

	program->numUniforms = numUniforms;

	{
		int i, size;

		size = sizeof(*program->uniforms) * numUniforms;
		program->uniforms = ri.Malloc(size);
		for (i = 0; i < numUniforms; i++)
		{
			program->uniforms[i] = -1;
		}

		size = sizeof(*program->uniformTypes) * numUniforms;
		program->uniformTypes = ri.Malloc(size);
		memset(program->uniformTypes, 0, size);

		size = sizeof(*program->uniformBufferOffsets) * numUniforms;
		program->uniformBufferOffsets = ri.Malloc(size);
		memset(program->uniformBufferOffsets, 0, size);
	}

	return 1;
}

// intentionally deceiving the user here, not actually setting the names but getting their indexes.
void GLSL_AddUniform(shaderProgram_t *program, int uniformNum, const char *name, int type)
{
	GLint *uniforms = program->uniforms;

	uniforms[uniformNum] = qglGetUniformLocationARB(program->program, name);
	program->uniformTypes[uniformNum] = type;
}

void GLSL_FinishGPUShader(shaderProgram_t *program)
{
	if (program->numUniforms)
	{
		int i, size;
		 
		size = 0;
		for (i = 0; i < program->numUniforms; i++)
		{
			if (program->uniforms[i] != -1)
			{
				program->uniformBufferOffsets[i] = size;

				switch(program->uniformTypes[i])
				{
					case GLSL_INT:
						size += sizeof(GLint);
						break;
					case GLSL_FLOAT:
						size += sizeof(GLfloat);
						break;
					case GLSL_VEC2:
						size += sizeof(vec_t) * 2;
						break;
					case GLSL_VEC3:
						size += sizeof(vec_t) * 3;
						break;
					case GLSL_VEC4:
						size += sizeof(vec_t) * 4;
						break;
					case GLSL_MAT16:
						size += sizeof(vec_t) * 16;
						break;
					default:
						break;
				}
			}
		}

		ri.Printf(PRINT_ALL, "size %d\n", size);

		program->uniformBuffer = ri.Malloc(size);

	}

	GLSL_ValidateProgram(program->program);
	GLSL_ShowProgramUniforms(program->program);
	GL_CheckErrors();
}

void GLSL_SetUniformInt(shaderProgram_t *program, int uniformNum, GLint value)
{
	GLint *uniforms = program->uniforms;
	GLint *compare = (GLint *)(program->uniformBuffer + program->uniformBufferOffsets[uniformNum]);

	if (uniforms[uniformNum] == -1)
		return;

	if (program->uniformTypes[uniformNum] != GLSL_INT)
	{
		ri.Printf( PRINT_WARNING, "GLSL_SetUniformInt: wrong type for uniform %i in program %s\n", uniformNum, program->name);
		return;
	}

	if (value == *compare)
	{
		return;
	}

	qglUniform1iARB(uniforms[uniformNum], value);
}

void GLSL_SetUniformFloat(shaderProgram_t *program, int uniformNum, GLfloat value)
{
	GLint *uniforms = program->uniforms;
	GLfloat *compare = (GLfloat *)(program->uniformBuffer + program->uniformBufferOffsets[uniformNum]);

	if (uniforms[uniformNum] == -1)
		return;

	if (program->uniformTypes[uniformNum] != GLSL_FLOAT)
	{
		ri.Printf( PRINT_WARNING, "GLSL_SetUniformFloat: wrong type for uniform %i in program %s\n", uniformNum, program->name);
		return;
	}

	if (value == *compare)
	{
		return;
	}
	
	qglUniform1fARB(uniforms[uniformNum], value);
}

void GLSL_SetUniformVec2(shaderProgram_t *program, int uniformNum, const vec2_t v)
{
	GLint *uniforms = program->uniforms;
	vec_t *compare = (float *)(program->uniformBuffer + program->uniformBufferOffsets[uniformNum]);

	if (uniforms[uniformNum] == -1)
		return;

	if (program->uniformTypes[uniformNum] != GLSL_VEC2)
	{
		ri.Printf( PRINT_WARNING, "GLSL_SetUniformVec2: wrong type for uniform %i in program %s\n", uniformNum, program->name);
		return;
	}

	if (v[0] == compare[0] && v[1] == compare[1])
	{
		return;
	}

	qglUniform2fARB(uniforms[uniformNum], v[0], v[1]);
}

void GLSL_SetUniformVec3(shaderProgram_t *program, int uniformNum, const vec3_t v)
{
	GLint *uniforms = program->uniforms;
	vec_t *compare = (float *)(program->uniformBuffer + program->uniformBufferOffsets[uniformNum]);

	if (uniforms[uniformNum] == -1)
		return;

	if (program->uniformTypes[uniformNum] != GLSL_VEC3)
	{
		ri.Printf( PRINT_WARNING, "GLSL_SetUniformVec3: wrong type for uniform %i in program %s\n", uniformNum, program->name);
		return;
	}

	if (VectorCompare(v, compare))
	{
		return;
	}

	qglUniform3fARB(uniforms[uniformNum], v[0], v[1], v[2]);
}

void GLSL_SetUniformVec4(shaderProgram_t *program, int uniformNum, const vec4_t v)
{
	GLint *uniforms = program->uniforms;
	vec_t *compare = (float *)(program->uniformBuffer + program->uniformBufferOffsets[uniformNum]);

	if (uniforms[uniformNum] == -1)
		return;

	if (program->uniformTypes[uniformNum] != GLSL_VEC4)
	{
		ri.Printf( PRINT_WARNING, "GLSL_SetUniformVec4: wrong type for uniform %i in program %s\n", uniformNum, program->name);
		return;
	}

	if (VectorCompare4(v, compare))
	{
		return;
	}

	qglUniform4fARB(uniforms[uniformNum], v[0], v[1], v[2], v[3]);
}

void GLSL_SetUniformMatrix16(shaderProgram_t *program, int uniformNum, const matrix_t matrix)
{
	GLint *uniforms = program->uniforms;
	vec_t *compare = (float *)(program->uniformBuffer + program->uniformBufferOffsets[uniformNum]);

	if (uniforms[uniformNum] == -1)
		return;

	if (program->uniformTypes[uniformNum] != GLSL_MAT16)
	{
		ri.Printf( PRINT_WARNING, "GLSL_SetUniformMatrix16: wrong type for uniform %i in program %s\n", uniformNum, program->name);
		return;
	}

	if (Matrix16Compare(matrix, compare))
	{
		return;
	}

	qglUniformMatrix4fvARB(uniforms[uniformNum], 1, GL_FALSE, matrix);
}

void GLSL_DeleteGPUShader(shaderProgram_t *program)
{
	if(program->program)
	{
		if (program->vertexShader)
		{
			qglDetachObjectARB(program->program, program->vertexShader);
			qglDeleteObjectARB(program->vertexShader);
		}

		if (program->fragmentShader)
		{
			qglDetachObjectARB(program->program, program->fragmentShader);
			qglDeleteObjectARB(program->fragmentShader);
		}

		qglDeleteObjectARB(program->program);

		if (program->uniforms)
		{
			ri.Free(program->uniforms);
		}

		if (program->uniformTypes)
		{
			ri.Free(program->uniformTypes);
		}
				
		if (program->uniformBuffer)
		{
			ri.Free(program->uniformBuffer);
		}

		if (program->uniformBufferOffsets)
		{
			ri.Free(program->uniformBufferOffsets);
		}

		Com_Memset(program, 0, sizeof(*program));
	}
}

void GLSL_InitGPUShaders(void)
{
	int             startTime, endTime;
	int i;
	char extradefines[1024];
	int attribs;

	ri.Printf(PRINT_ALL, "------- GLSL_InitGPUShaders -------\n");

	// make sure the render thread is stopped
	R_SyncRenderThread();

	startTime = ri.Milliseconds();

	for (i = 0; i < GLSLDEF_COUNT; i++)
	{	
		attribs = ATTR_POSITION | ATTR_TEXCOORD | ATTR_LIGHTCOORD | ATTR_NORMAL | ATTR_COLOR;
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

		if (!GLSL_InitGPUShader(&tr.genericShader[i], "generic", attribs, qtrue, extradefines, qtrue, fallbackGenericShader_vp, fallbackGenericShader_fp, GENERIC_UNIFORM_COUNT))
		{
			ri.Error(ERR_FATAL, "Could not load generic shader!\n");
		}

		// There's actually no need to filter these out, since they'll
		// redirect to -1 if nonexistent, but it's more understandable this way.
		
		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_MODELVIEWPROJECTIONMATRIX, "u_ModelViewProjectionMatrix", GLSL_MAT16);

		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_COLORGEN, "u_ColorGen", GLSL_INT);
		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_ALPHAGEN, "u_AlphaGen", GLSL_INT);

		if (i & GLSLDEF_USE_TCGEN)
		{
			GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_TCGEN0,        "u_TCGen0",        GLSL_INT);
			GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_TCGEN0VECTOR0, "u_TCGen0Vector0", GLSL_VEC4);
			GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_TCGEN0VECTOR1, "u_TCGen0Vector1", GLSL_VEC4);
		}

		if (i & GLSLDEF_USE_FOG)
		{
			GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_FOGADJUSTCOLORS, "u_FogAdjustColors", GLSL_INT);
			GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_FOGDISTANCE,     "u_FogDistance",     GLSL_VEC4);
			GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_FOGDEPTH,        "u_FogDepth",        GLSL_VEC4);
			GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_FOGEYET,         "u_FogEyeT",         GLSL_FLOAT);
		}

		if (i & GLSLDEF_USE_DEFORM_VERTEXES)
		{
			GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_DEFORMGEN,    "u_DeformGen",    GLSL_INT);
			GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_DEFORMWAVE,   "u_DeformWave",   GLSL_VEC4);
			GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_DEFORMBULGE,  "u_DeformBulge",  GLSL_VEC3);
			GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_DEFORMSPREAD, "u_DeformSpread", GLSL_FLOAT);
		}

		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_TIME,           "u_Time",           GLSL_FLOAT);
		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_COLOR,          "u_Color",          GLSL_VEC4);
		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_AMBIENTLIGHT,   "u_AmbientLight",   GLSL_VEC3);
		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_DIRECTEDLIGHT,  "u_DirectedLight",  GLSL_VEC3);
		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_LIGHTDIR,       "u_LightDir",       GLSL_VEC3);
		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_VIEWORIGIN,     "u_ViewOrigin",     GLSL_VEC3);
		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_TEXTURE0MATRIX, "u_Texture0Matrix", GLSL_MAT16);
		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_TEXTURE1ENV,    "u_Texture1Env",    GLSL_INT);

		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_TEXTURE0MAP,    "u_Texture0Map",    GLSL_INT);
		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_TEXTURE1MAP,    "u_Texture1Map",    GLSL_INT);

		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_PORTALRANGE,    "u_PortalRange",    GLSL_FLOAT);

		if (i & GLSLDEF_USE_VERTEX_ANIMATION)
		{
			GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_VERTEXLERP, "u_VertexLerp", GLSL_FLOAT);
		}

		GLSL_FinishGPUShader(&tr.genericShader[i]);

		qglUseProgramObjectARB(tr.genericShader[i].program);
		GLSL_SetUniformInt(&tr.genericShader[i], GENERIC_UNIFORM_TEXTURE0MAP, 0);
		GLSL_SetUniformInt(&tr.genericShader[i], GENERIC_UNIFORM_TEXTURE1MAP, 1);
		qglUseProgramObjectARB(0);
	}


	attribs = ATTR_POSITION | ATTR_TEXCOORD | ATTR_LIGHTCOORD;

	if (!GLSL_InitGPUShader(&tr.lightmappedShader, "lightmapped", attribs, qtrue, NULL, qfalse, fallbackLightmappedShader_vp, fallbackLightmappedShader_fp, LIGHTMAPPED_UNIFORM_COUNT))
	{
		ri.Error(ERR_FATAL, "Could not load lightmapped shader!\n");
	}

	GLSL_AddUniform(&tr.lightmappedShader, LIGHTMAPPED_UNIFORM_MODELVIEWPROJECTIONMATRIX, "u_ModelViewProjectionMatrix", GLSL_MAT16);
	GLSL_AddUniform(&tr.lightmappedShader, LIGHTMAPPED_UNIFORM_TEXTURE0MATRIX,            "u_Texture0Matrix",            GLSL_MAT16);
	GLSL_AddUniform(&tr.lightmappedShader, LIGHTMAPPED_UNIFORM_TEXTURE1ENV,               "u_Texture1Env",               GLSL_INT);
	GLSL_AddUniform(&tr.lightmappedShader, LIGHTMAPPED_UNIFORM_TEXTURE0MAP,               "u_Texture0Map",               GLSL_INT);
	GLSL_AddUniform(&tr.lightmappedShader, LIGHTMAPPED_UNIFORM_TEXTURE1MAP,               "u_Texture1Map",               GLSL_INT);

	GLSL_FinishGPUShader(&tr.lightmappedShader);

	qglUseProgramObjectARB(tr.lightmappedShader.program);
	GLSL_SetUniformInt(&tr.lightmappedShader, LIGHTMAPPED_UNIFORM_TEXTURE0MAP, 0);
	GLSL_SetUniformInt(&tr.lightmappedShader, LIGHTMAPPED_UNIFORM_TEXTURE1MAP, 1);
	qglUseProgramObjectARB(0);


	attribs = ATTR_POSITION | ATTR_TEXCOORD;

	if (!GLSL_InitGPUShader(&tr.textureOnlyShader, "textureonly", attribs, qtrue, NULL, qfalse, fallbackTextureOnlyShader_vp, fallbackTextureOnlyShader_fp, TEXTUREONLY_UNIFORM_COUNT))
	{
		ri.Error(ERR_FATAL, "Could not load textureonly shader!\n");
	}
	
	GLSL_AddUniform(&tr.textureOnlyShader, TEXTUREONLY_UNIFORM_MODELVIEWPROJECTIONMATRIX, "u_ModelViewProjectionMatrix", GLSL_MAT16);
	GLSL_AddUniform(&tr.textureOnlyShader, TEXTUREONLY_UNIFORM_TEXTURE0MAP,               "u_Texture0Map",               GLSL_INT);

	GLSL_FinishGPUShader(&tr.textureOnlyShader);

	qglUseProgramObjectARB(tr.textureOnlyShader.program);
	GLSL_SetUniformInt(&tr.textureOnlyShader, TEXTUREONLY_UNIFORM_TEXTURE0MAP, 0);
	qglUseProgramObjectARB(0);


	attribs = ATTR_POSITION | ATTR_POSITION2 | ATTR_NORMAL | ATTR_NORMAL2 | ATTR_TEXCOORD;

	if (!GLSL_InitGPUShader(&tr.fogShader, "fogpass", attribs, qtrue, NULL, qtrue, fallbackFogPassShader_vp, fallbackFogPassShader_fp, FOGPASS_UNIFORM_COUNT))
	{
		ri.Error(ERR_FATAL, "Could not load fogpass shader!\n");
	}

	GLSL_AddUniform(&tr.fogShader, FOGPASS_UNIFORM_FOGDISTANCE,               "u_FogDistance",               GLSL_VEC4);
	GLSL_AddUniform(&tr.fogShader, FOGPASS_UNIFORM_FOGDEPTH,                  "u_FogDepth",                  GLSL_VEC4);
	GLSL_AddUniform(&tr.fogShader, FOGPASS_UNIFORM_FOGEYET,                   "u_FogEyeT",                   GLSL_FLOAT);
	GLSL_AddUniform(&tr.fogShader, FOGPASS_UNIFORM_DEFORMGEN,                 "u_DeformGen",                 GLSL_INT);
	GLSL_AddUniform(&tr.fogShader, FOGPASS_UNIFORM_DEFORMWAVE,                "u_DeformWave",                GLSL_VEC4);
	GLSL_AddUniform(&tr.fogShader, FOGPASS_UNIFORM_DEFORMBULGE,               "u_DeformBulge",               GLSL_VEC3);
	GLSL_AddUniform(&tr.fogShader, FOGPASS_UNIFORM_DEFORMSPREAD,              "u_DeformSpread",              GLSL_FLOAT);
	GLSL_AddUniform(&tr.fogShader, FOGPASS_UNIFORM_TIME,                      "u_Time",                      GLSL_FLOAT);
	GLSL_AddUniform(&tr.fogShader, FOGPASS_UNIFORM_COLOR,                     "u_Color",                     GLSL_VEC4);
	GLSL_AddUniform(&tr.fogShader, FOGPASS_UNIFORM_MODELVIEWPROJECTIONMATRIX, "u_ModelViewProjectionMatrix", GLSL_MAT16);
	GLSL_AddUniform(&tr.fogShader, FOGPASS_UNIFORM_VERTEXLERP,                "u_VertexLerp",                GLSL_FLOAT);
	
	GLSL_FinishGPUShader(&tr.fogShader);


	attribs = ATTR_POSITION | ATTR_POSITION2 | ATTR_NORMAL | ATTR_NORMAL2 | ATTR_TEXCOORD;

	if (!GLSL_InitGPUShader(&tr.dlightShader, "dlight", attribs, qtrue, NULL, qtrue, fallbackDlightShader_vp, fallbackDlightShader_fp, DLIGHT_UNIFORM_COUNT))
	{
		ri.Error(ERR_FATAL, "Could not load dlight shader!\n");
	}

	GLSL_AddUniform(&tr.dlightShader, DLIGHT_UNIFORM_DLIGHTINFO,                "u_DlightInfo",                GLSL_VEC4);
	GLSL_AddUniform(&tr.dlightShader, DLIGHT_UNIFORM_DEFORMGEN,                 "u_DeformGen",                 GLSL_INT);
	GLSL_AddUniform(&tr.dlightShader, DLIGHT_UNIFORM_DEFORMWAVE,                "u_DeformWave",                GLSL_VEC4);
	GLSL_AddUniform(&tr.dlightShader, DLIGHT_UNIFORM_DEFORMBULGE,               "u_DeformBulge",               GLSL_VEC3);
	GLSL_AddUniform(&tr.dlightShader, DLIGHT_UNIFORM_DEFORMSPREAD,              "u_DeformSpread",              GLSL_FLOAT);
	GLSL_AddUniform(&tr.dlightShader, DLIGHT_UNIFORM_TIME,                      "u_Time",                      GLSL_FLOAT);
	GLSL_AddUniform(&tr.dlightShader, DLIGHT_UNIFORM_COLOR,                     "u_Color",                     GLSL_VEC4);
	GLSL_AddUniform(&tr.dlightShader, DLIGHT_UNIFORM_MODELVIEWPROJECTIONMATRIX, "u_ModelViewProjectionMatrix", GLSL_MAT16);
	GLSL_AddUniform(&tr.dlightShader, DLIGHT_UNIFORM_VERTEXLERP,                "u_VertexLerp",                GLSL_FLOAT);
	
	GLSL_FinishGPUShader(&tr.dlightShader);
	
	
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
	qglDisableVertexAttribArrayARB(ATTR_INDEX_POSITION2);
	qglDisableVertexAttribArrayARB(ATTR_INDEX_NORMAL);
	qglDisableVertexAttribArrayARB(ATTR_INDEX_NORMAL2);
	qglDisableVertexAttribArrayARB(ATTR_INDEX_COLOR);
	GLSL_BindNullProgram();

	for ( i = 0; i < GLSLDEF_COUNT; i++)
	{
		GLSL_DeleteGPUShader(&tr.genericShader[i]);
	}

	GLSL_DeleteGPUShader(&tr.textureOnlyShader);
	GLSL_DeleteGPUShader(&tr.lightmappedShader);
	GLSL_DeleteGPUShader(&tr.fogShader);
	GLSL_DeleteGPUShader(&tr.dlightShader);
	
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
		backEnd.pc.c_glslShaderBinds++;
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

