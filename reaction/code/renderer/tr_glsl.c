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
"DiffuseTexMatrix;\r\nuniform vec3   u_ViewOrigin;\r\n\r\n#if defined(USE_TC"
"GEN)\r\nuniform int    u_TCGen0;\r\nuniform vec4   u_TCGen0Vector0;\r\nunif"
"orm vec4   u_TCGen0Vector1;\r\n#endif\r\n\r\n#if defined(USE_FOG)\r\nunifor"
"m vec4   u_FogDistance;\r\nuniform vec4   u_FogDepth;\r\nuniform float  u_F"
"ogEyeT;\r\nuniform int    u_FogAdjustColors;\r\n#endif\r\n\r\n#if defined(U"
"SE_DEFORM_VERTEXES)\r\nuniform int    u_DeformGen;\r\nuniform vec4   u_Defo"
"rmWave;\r\nuniform vec3   u_DeformBulge;\r\nuniform float  u_DeformSpread;"
"\r\n#endif\r\n\r\nuniform float  u_Time;\r\n\r\nuniform mat4   u_ModelViewP"
"rojectionMatrix;\r\nuniform vec4   u_Color;\r\n\r\n#if defined(USE_RGBAGEN)"
"\r\nuniform int    u_ColorGen;\r\nuniform int    u_AlphaGen;\r\nuniform vec"
"3   u_AmbientLight;\r\nuniform vec3   u_DirectedLight;\r\nuniform vec4   u_"
"LightOrigin;\r\nuniform float  u_PortalRange;\r\n#endif\r\n\r\n#if defined("
"USE_VERTEX_ANIMATION)\r\nuniform float  u_VertexLerp;\r\n#endif\r\n\r\nvary"
"ing vec2   var_DiffuseTex;\r\nvarying vec2   var_LightTex;\r\nvarying vec4 "
"  var_Color;\r\n\r\n#if defined(USE_DEFORM_VERTEXES)\r\nfloat triangle(floa"
"t x)\r\n{\r\n\treturn max(1.0 - abs(x), 0);\r\n}\r\n\r\nfloat sawtooth(floa"
"t x)\r\n{\r\n\treturn x - floor(x);\r\n}\r\n\r\nvec4 DeformPosition(const v"
"ec4 pos, const vec3 normal, const vec2 st)\r\n{\r\n\tvec4 deformed = pos;\r"
"\n\r\n\tif (u_DeformGen == DGEN_WAVE_SIN)\r\n\t{\r\n\t\tfloat off = (pos.x "
"+ pos.y + pos.z) * u_DeformSpread;\r\n\t\tfloat scale = u_DeformWave.x  + s"
"in((off + u_DeformWave.z + (u_Time * u_DeformWave.w)) * 2.0 * M_PI) * u_Def"
"ormWave.y;\r\n\t\tvec3 offset = normal * scale;\r\n\r\n\t\tdeformed.xyz += "
"offset;\r\n\t}\r\n\telse if (u_DeformGen == DGEN_WAVE_SQUARE)\r\n\t{\r\n\t"
"\tfloat off = (pos.x + pos.y + pos.z) * u_DeformSpread;\r\n\t\tfloat scale "
"= u_DeformWave.x  + sign(sin((off + u_DeformWave.z + (u_Time * u_DeformWave"
".w)) * 2.0 * M_PI)) * u_DeformWave.y;\r\n\t\tvec3 offset = normal * scale;"
"\r\n\r\n\t\tdeformed.xyz += offset;\r\n\t}\r\n\telse if (u_DeformGen == DGE"
"N_WAVE_TRIANGLE)\r\n\t{\r\n\t\tfloat off = (pos.x + pos.y + pos.z) * u_Defo"
"rmSpread;\r\n\t\tfloat scale = u_DeformWave.x  + triangle(off + u_DeformWav"
"e.z + (u_Time * u_DeformWave.w)) * u_DeformWave.y;\r\n\t\tvec3 offset = nor"
"mal * scale;\r\n\r\n\t\tdeformed.xyz += offset;\r\n\t}\r\n\telse if (u_Defo"
"rmGen == DGEN_WAVE_SAWTOOTH)\r\n\t{\r\n\t\tfloat off = (pos.x + pos.y + pos"
".z) * u_DeformSpread;\r\n\t\tfloat scale = u_DeformWave.x  + sawtooth(off +"
" u_DeformWave.z + (u_Time * u_DeformWave.w)) * u_DeformWave.y;\r\n\t\tvec3 "
"offset = normal * scale;\r\n\r\n\t\tdeformed.xyz += offset;\r\n\t}\r\n\tels"
"e if (u_DeformGen == DGEN_WAVE_INVERSE_SAWTOOTH)\r\n\t{\r\n\t\tfloat off = "
"(pos.x + pos.y + pos.z) * u_DeformSpread;\r\n\t\tfloat scale = u_DeformWave"
".x + (1.0 - sawtooth(off + u_DeformWave.z + (u_Time * u_DeformWave.w))) * u"
"_DeformWave.y;\r\n\t\tvec3 offset = normal * scale;\r\n\r\n\t\tdeformed.xyz"
" += offset;\r\n\t}\r\n\telse if (u_DeformGen == DGEN_BULGE)\r\n\t{\r\n\t\tf"
"loat bulgeWidth = u_DeformBulge.x;\r\n\t\tfloat bulgeHeight = u_DeformBulge"
".y;\r\n\t\tfloat bulgeSpeed = u_DeformBulge.z;\r\n\r\n\t\tfloat now = u_Tim"
"e * bulgeSpeed;\r\n\r\n\t\tfloat off = (M_PI * 0.25) * st.x * bulgeWidth + "
"now;\r\n\t\tfloat scale = sin(off) * bulgeHeight;\r\n\t\tvec3 offset = norm"
"al * scale;\r\n\r\n\t\tdeformed.xyz += offset;\r\n\t}\r\n\r\n\treturn defor"
"med;\r\n}\r\n#endif\r\n\r\n#if defined(USE_TCGEN)\r\nvec2 GenTexCoords(int "
"TCGen, vec4 position, vec3 normal, vec4 TCGenVector0, vec4 TCGenVector1)\r"
"\n{\r\n\tvec2 tex = vec2(0.0);\r\n\r\n\tif (TCGen == TCGEN_LIGHTMAP)\r\n\t{"
"\r\n\t\ttex = attr_TexCoord1.st;\r\n\t}\r\n\telse if (TCGen == TCGEN_TEXTUR"
"E)\r\n\t{\r\n\t\ttex = attr_TexCoord0.st;\r\n\t}\r\n\telse if (TCGen == TCG"
"EN_ENVIRONMENT_MAPPED)\r\n\t{\r\n\t\tvec3 viewer = normalize(u_ViewOrigin -"
" position.xyz);\r\n\r\n\t\tfloat d = dot(normal, viewer);\r\n\r\n\t\tvec3 r"
"eflected = normal * 2.0 * d - viewer;\r\n\r\n\t\ttex.s = 0.5 + reflected.y "
"* 0.5;\r\n\t\ttex.t = 0.5 - reflected.z * 0.5;\r\n\t}\r\n\telse if (TCGen ="
"= TCGEN_VECTOR)\r\n\t{\r\n\t\ttex.s = dot(position.xyz, TCGenVector0.xyz);"
"\r\n\t\ttex.t = dot(position.xyz, TCGenVector1.xyz);\r\n\t}\r\n\t\r\n\tretu"
"rn tex;\r\n}\r\n#endif\r\n\r\nvoid main()\r\n{\r\n#if defined(USE_VERTEX_AN"
"IMATION)\r\n\tvec4 position = mix(attr_Position, attr_Position2, u_VertexLe"
"rp);\r\n\tvec3 normal = normalize(mix(attr_Normal, attr_Normal2, u_VertexLe"
"rp));\r\n#else\r\n\tvec4 position = attr_Position;\r\n\tvec3 normal = attr_"
"Normal;\r\n#endif\r\n\r\n#if defined(USE_DEFORM_VERTEXES)\r\n\tposition = D"
"eformPosition(position, normal, attr_TexCoord0.st);\r\n#endif\r\n\r\n\tgl_P"
"osition = u_ModelViewProjectionMatrix * position;\r\n\r\n\r\n\tvec4 tex = v"
"ec4(1.0, 1.0, 1.0, 0.0);\r\n\r\n#if defined(USE_TCGEN)\r\n\ttex.st = GenTex"
"Coords(u_TCGen0, position, normal, u_TCGen0Vector0, u_TCGen0Vector1);\r\n#e"
"lse\r\n\ttex.st = attr_TexCoord0.st;\r\n#endif\r\n    \r\n\tvar_DiffuseTex "
"= (u_DiffuseTexMatrix * tex).st;\r\n\r\n\tvar_DiffuseTex.s += sin(((positio"
"n.x + position.z) * 1.0 / 128.0 * 0.125 + u_DiffuseTexMatrix[3][1]) * 2.0 *"
" M_PI) * u_DiffuseTexMatrix[3][0];\r\n\tvar_DiffuseTex.t += sin((position.y"
" * 1.0 / 128.0 * 0.125 + u_DiffuseTexMatrix[3][1]) * 2.0 * M_PI) * u_Diffus"
"eTexMatrix[3][0];\r\n\r\n\tvar_LightTex = attr_TexCoord1.st;\r\n\t\r\n\tvar"
"_Color = u_Color;\r\n\r\n#if defined(USE_RGBAGEN)\r\n\tif (u_ColorGen == CG"
"EN_LIGHTING_DIFFUSE)\r\n\t{\r\n\t\t// when CGEN_LIGHTING_DIFFUSE, u_LightOr"
"igin is always at infinity, ie directional\r\n\t\tfloat incoming = max(dot("
"normal, u_LightOrigin.xyz), 0.0);\r\n\r\n\t\tvar_Color.rgb = min(u_Directed"
"Light * incoming + u_AmbientLight, 1.0);\r\n\t}\r\n\telse if (u_ColorGen =="
" CGEN_EXACT_VERTEX)\r\n\t{\r\n\t\tvar_Color.rgb = attr_Color.rgb;\r\n\t}\r"
"\n\telse if (u_ColorGen == CGEN_VERTEX)\r\n\t{\r\n\t\tvar_Color.rgb *= attr"
"_Color.rgb;\r\n\t}\r\n\telse if (u_ColorGen == CGEN_ONE_MINUS_VERTEX)\r\n\t"
"{\r\n\t\tvar_Color.rgb *= (vec3(1.0) - attr_Color.rgb);\r\n\t}\r\n\r\n\tif "
"(u_AlphaGen == AGEN_LIGHTING_SPECULAR)\r\n\t{\r\n\t\tvec3 lightDir = normal"
"ize(vec3(-960.0, -1980.0, 96.0) - position.xyz);\r\n\t\tvec3 viewer = norma"
"lize(u_ViewOrigin - position.xyz);\r\n\t\tvec3 halfangle = normalize(lightD"
"ir + viewer);\r\n\t\t\r\n\t\tvar_Color.a = pow(max(dot(normal, halfangle), "
"0.0), 8.0);\r\n\t}\r\n\telse if (u_AlphaGen == AGEN_VERTEX)\r\n\t{\r\n\t\tv"
"ar_Color.a = attr_Color.a;\r\n\t}\r\n\telse if (u_AlphaGen == AGEN_ONE_MINU"
"S_VERTEX)\r\n\t{\r\n\t\tvar_Color.a = 1.0 - attr_Color.a;\r\n\t}\r\n\telse "
"if (u_AlphaGen == AGEN_PORTAL)\r\n\t{\r\n\t\tfloat alpha = length(position."
"xyz - u_ViewOrigin) / u_PortalRange;\r\n\r\n\t\tvar_Color.a = min(alpha, 1."
"0);\r\n\t}\r\n\telse if (u_AlphaGen == AGEN_FRESNEL)\r\n\t{\r\n\t\tvec3 vie"
"wer = normalize(u_ViewOrigin - position.xyz);\r\n\t\t\r\n\t\tvar_Color.a = "
"dot(viewer, normal);\r\n\t}\r\n#endif\r\n\r\n#if defined (USE_FOG)\r\n\tif "
"(u_FogAdjustColors != ACFF_NONE) \r\n\t{\r\n\t\tfloat s = max(dot(position."
"xyz, u_FogDistance.xyz) + u_FogDistance.a, 0.0);\r\n\t\tfloat t = max(dot(p"
"osition.xyz, u_FogDepth.xyz) + u_FogDepth.a, 0.0);\r\n\t\t\r\n\t\tif (t >= "
"1.0)\r\n\t\t{\r\n\t\t\ts *= t / (t - min(u_FogEyeT, 0.0));\r\n\t\t}\r\n\t\t"
"\r\n\t\ts = 1.0 - sqrt(min(s * 8.0, 1.0));\r\n\t\r\n\t\tif (u_FogAdjustColo"
"rs == ACFF_MODULATE_RGB)\r\n\t\t{\r\n\t\t\tvar_Color.xyz *= s;\r\n\t\t}\r\n"
"\t\telse if (u_FogAdjustColors == ACFF_MODULATE_ALPHA)\r\n\t\t{\r\n\t\t\tva"
"r_Color.a *= s;\r\n\t\t}\r\n\t\telse if (u_FogAdjustColors == ACFF_MODULATE"
"_RGBA)\r\n\t\t{\r\n\t\t\tvar_Color *= s;\r\n\t\t}\r\n\t}\r\n#endif\r\n}\r\n";

static const char *fallbackGenericShader_fp = 
"uniform sampler2D u_DiffuseMap;\r\nuniform sampler2D u_LightMap;\r\nuniform"
" int       u_Texture1Env;\r\n\r\nvarying vec2      var_DiffuseTex;\r\nvaryi"
"ng vec2      var_LightTex;\r\nvarying vec4      var_Color;\r\n\r\n\r\nvoid "
"main()\r\n{\r\n\tvec4 color;\r\n\r\n\tif (u_Texture1Env != 2)\r\n\t{\r\n\t"
"\tcolor = texture2D(u_DiffuseMap, var_DiffuseTex);\r\n\t}\r\n\r\n\tif (u_Te"
"xture1Env != 0)\r\n\t{\r\n\t\tvec4 color2 = texture2D(u_LightMap, var_Light"
"Tex);\r\n\r\n\t\tif (u_Texture1Env == GL_MODULATE)\r\n\t\t{\r\n\t\t\tcolor "
"*= color2;\r\n\t\t}\r\n\t\t\telse if (u_Texture1Env == GL_ADD)\r\n\t\t{\r\n"
"\t\t\tcolor += color2;\r\n\t\t}\r\n\t\t\telse // if (u_Texture1Env == GL_RE"
"PLACE)\r\n\t\t{\r\n\t\t\tcolor = color2;\r\n\t\t}\r\n\t}\r\n\r\n\tcolor *= "
"var_Color;\r\n\r\n\tgl_FragColor = color;\r\n}\r\n";

static const char *fallbackTextureColorShader_vp =
"#version 120\r\n\r\nattribute vec4 attr_Position;\r\nattribute vec4 attr_Te"
"xCoord0;\r\n\r\nuniform mat4   u_ModelViewProjectionMatrix;\r\n\r\nvarying "
"vec2   var_Tex1;\r\n\r\n\r\nvoid main()\r\n{\r\n\tgl_Position = u_ModelView"
"ProjectionMatrix * attr_Position;\r\n\tvar_Tex1 = attr_TexCoord0.st;\r\n}\r"
"\n";

static const char *fallbackTextureColorShader_fp =
"#version 120\r\n\r\nuniform sampler2D u_DiffuseMap;\r\nuniform vec4      u_"
"Color;\r\n\r\nvarying vec2         var_Tex1;\r\n\r\n\r\nvoid main()\r\n{\r"
"\n\tgl_FragColor = texture2D(u_DiffuseMap, var_Tex1) * u_Color;\r\n}\r\n";

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
"l = normalize(mix(attr_Normal, attr_Normal2, u_VertexLerp));\r\n\t}\r\n\tel"
"se\r\n//#endif\r\n\t{\r\n\t\tposition = attr_Position;\r\n\t\tnormal = attr"
"_Normal;\r\n\t}\r\n\r\n//#if defined(USE_DEFORM_VERTEXES)\r\n\tposition = D"
"eformPosition(position, normal, attr_TexCoord0.st);\r\n//#endif\r\n\r\n\tgl"
"_Position = u_ModelViewProjectionMatrix * position;\r\n\r\n\tfloat s = max("
"dot(position.xyz, u_FogDistance.xyz) + u_FogDistance.a, 0.0);\r\n\tfloat t "
"= max(dot(position.xyz, u_FogDepth.xyz) + u_FogDepth.a, 0.0);\r\n\t\r\n\tif"
" (t >= 1.0)\r\n\t{\r\n\t\ts *= t / (t - min(u_FogEyeT, 0.0));\r\n\t}\r\n\t"
"\r\n\ts = sqrt(min(s * 8.0, 1.0));\r\n\t\r\n\tvar_Color.xyz = u_Color.xyz;"
"\r\n\tvar_Color.a = u_Color.a * s;\r\n}\r\n";

static const char *fallbackFogPassShader_fp =
"varying vec4 var_Color;\r\n\r\n\r\nvoid main()\r\n{\r\n\tgl_FragColor = var"
"_Color;\r\n}\r\n";

static const char *fallbackDlightallShader_vp =
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
"{\r\n\tvec4 position = mix(attr_Position, attr_Position2, u_VertexLerp);\r"
"\n\tvec3 normal = normalize(mix(attr_Normal, attr_Normal2, u_VertexLerp));"
"\r\n\r\n\tposition = DeformPosition(position, normal, attr_TexCoord0.st);\r"
"\n\r\n\tgl_Position = u_ModelViewProjectionMatrix * position;\r\n\t\r\n\tve"
"c2 tex = vec2(0);\r\n\t\r\n\tvec3 dist = u_DlightInfo.xyz - position.xyz;\t"
"\r\n\tfloat dlightmod = 0;\r\n\r\n\tif (dot(dist, normal) > 0)\r\n\t{\r\n\t"
"\tfloat diffz = abs(dist.z);\r\n\t\tfloat radius = 1.0 / u_DlightInfo.a;\r"
"\n    \r\n\t\tif (diffz <= radius)\r\n\t\t{\r\n\t\t\ttex = vec2(0.5) + dist"
".xy * u_DlightInfo.a;\r\n\r\n\t\t\tif (diffz < radius * 0.5)\r\n\t\t\t{\r\n"
"\t\t\t\tdlightmod = 1.0;\r\n\t\t\t}\r\n\t\t\telse\r\n\t\t\t{\r\n\t\t\t\tdli"
"ghtmod = 2.0 * (radius - diffz) * u_DlightInfo.a;\r\n\t\t\t}\r\n\t\t}\r\n\t"
"}\r\n\r\n\tvar_Tex1 = tex;\r\n\tvar_Color.rgb = u_Color.rgb * dlightmod;\r"
"\n\tvar_Color.a = u_Color.a;\r\n}\r\n";

static const char *fallbackDlightallShader_fp =
"uniform sampler2D u_DiffuseMap;\r\n\r\nvarying vec2      var_Tex1;\r\nvaryi"
"ng vec4      var_Color;\r\n\r\n\r\nvoid main()\r\n{\r\n\tvec4 color = textu"
"re2D(u_DiffuseMap, var_Tex1);\r\n\r\n\tgl_FragColor = color * var_Color;\r"
"\n}\r\n";

static const char *fallbackLightallShader_vp =
"attribute vec4 attr_TexCoord0;\r\nattribute vec4 attr_TexCoord1;\r\n\r\natt"
"ribute vec4 attr_Position;\r\nattribute vec3 attr_Normal;\r\n\r\n#if define"
"d(USE_NORMALMAP)\r\nattribute vec3 attr_Tangent;\r\nattribute vec3 attr_Bit"
"angent;\r\n#endif\r\n\r\n#if defined(USE_VERTEX_ANIMATION)\r\nattribute vec"
"4 attr_Position2;\r\nattribute vec3 attr_Normal2;\r\n  #if defined(USE_NORM"
"ALMAP)\r\nattribute vec3 attr_Tangent2;\r\nattribute vec3 attr_Bitangent2;"
"\r\n  #endif\r\n#endif\r\n\r\nuniform mat4   u_DiffuseTexMatrix;\r\nuniform"
" vec3   u_ViewOrigin;\r\nuniform mat4   u_ModelViewProjectionMatrix;\r\n\r"
"\n#if defined(USE_MODELMATRIX)\r\nuniform mat4   u_ModelMatrix;\r\n#endif\r"
"\n\r\n#if defined(USE_VERTEX_ANIMATION)\r\nuniform float  u_VertexLerp;\r\n"
"#endif\r\n\r\nvarying vec2   var_DiffuseTex;\r\nvarying vec2   var_LightTex"
";\r\n\r\nvarying vec3   var_Position;\r\nvarying vec3   var_Normal;\r\n\r\n"
"#if defined(USE_NORMALMAP)\r\nvarying vec3   var_Tangent;\r\nvarying vec3  "
" var_Bitangent;\r\n#endif\r\n\r\nvec2 DoTexMatrix(vec2 st, vec3 position, m"
"at4 texMatrix)\r\n{\r\n\tvec4 st2 = vec4(st, 1, 0);\r\n\t\r\n\tst2.st = (te"
"xMatrix * st2).st;\r\n\r\n\tvec2 texOffset;\r\n\tvec3 offsetPos = position."
"xyz / 1024.0;\r\n\toffsetPos.x += offsetPos.z;\r\n\r\n\ttexOffset = sin((of"
"fsetPos.xy + vec2(texMatrix[3][1])) * 2.0 * M_PI);\r\n\t\r\n\treturn st2.st"
" + texOffset * texMatrix[3][0];\r\n}\r\n\r\nvoid main()\r\n{\r\n#if defined"
"(USE_VERTEX_ANIMATION)\r\n\tvec4 position  = mix(attr_Position, attr_Positi"
"on2, u_VertexLerp);\r\n\tvec3 normal    = normalize(mix(attr_Normal,    att"
"r_Normal2,    u_VertexLerp));\r\n  #if defined(USE_NORMALMAP)\r\n\tvec3 tan"
"gent   = normalize(mix(attr_Tangent,   attr_Tangent2,   u_VertexLerp));\r\n"
"\tvec3 bitangent = normalize(mix(attr_Bitangent, attr_Bitangent2, u_VertexL"
"erp));\r\n  #endif\r\n#else\r\n\tvec4 position  = attr_Position;\r\n\tvec3 "
"normal    = attr_Normal;\r\n  #if defined(USE_NORMALMAP)\r\n        vec3 ta"
"ngent   = attr_Tangent;\r\n        vec3 bitangent = attr_Bitangent;\r\n  #e"
"ndif\r\n#endif\r\n\r\n\tgl_Position = u_ModelViewProjectionMatrix * positio"
"n;\r\n\r\n#if defined(TCGEN_ENVIRONMENT)\r\n\t{\r\n\t\tvec2 tex;\r\n\t\tvec"
"3 viewer = normalize(u_ViewOrigin - position.xyz);\r\n\r\n\t\tfloat d = dot"
"(normal, viewer);\r\n\r\n\t\tvec3 reflected = normal * 2.0 * d - viewer;\r"
"\n\r\n\t\ttex.s = 0.5 + reflected.y * 0.5;\r\n\t\ttex.t = 0.5 - reflected.z"
" * 0.5;\r\n\t\t\r\n\t\tvar_DiffuseTex = DoTexMatrix(tex, position.xyz, u_Di"
"ffuseTexMatrix);\r\n\t}\r\n#else\r\n\tvar_DiffuseTex = DoTexMatrix(attr_Tex"
"Coord0.st, position.xyz, u_DiffuseTexMatrix);\r\n#endif\r\n\r\n\r\n\tvar_Li"
"ghtTex = attr_TexCoord1.st;\r\n\r\n#if defined(USE_MODELMATRIX)\r\n\tvar_Po"
"sition  = (u_ModelMatrix * position).xyz;\r\n\tvar_Normal    = (u_ModelMatr"
"ix * vec4(normal, 0.0)).xyz;\r\n\r\n  #if defined(USE_NORMALMAP)\r\n\tvar_T"
"angent   = (u_ModelMatrix * vec4(tangent, 0.0)).xyz;\r\n\tvar_Bitangent = ("
"u_ModelMatrix * vec4(bitangent, 0.0)).xyz;\r\n  #endif\r\n#else\r\n\tvar_Po"
"sition  = position.xyz;\r\n\tvar_Normal    = normal;\r\n\r\n  #if defined(U"
"SE_NORMALMAP)\r\n\tvar_Tangent   = tangent;\r\n\tvar_Bitangent = bitangent;"
"\r\n  #endif\r\n#endif\r\n}\r\n";

static const char *fallbackLightallShader_fp =
"uniform sampler2D u_DiffuseMap;\r\n\r\n#if defined(USE_LIGHTMAP)\r\nuniform"
" sampler2D u_LightMap;\r\n#endif\r\n\r\n#if defined(USE_NORMALMAP)\r\nunifo"
"rm sampler2D u_NormalMap;\r\n#endif\r\n\r\n#if defined(USE_DELUXEMAP)\r\nun"
"iform sampler2D u_DeluxeMap;\r\n#endif\r\n\r\n#if defined(USE_SPECULARMAP)"
"\r\nuniform sampler2D u_SpecularMap;\r\n#endif\r\n\r\nuniform vec3      u_V"
"iewOrigin;\r\nuniform vec4      u_Color;\r\n\r\n#if !defined(USE_LIGHTMAP)"
"\r\nuniform vec3      u_DirectedLight;\r\nuniform vec3      u_AmbientLight;"
"\r\nuniform vec4      u_LightOrigin;\r\nuniform float     u_LightScaleSqr;"
"\r\n#endif\r\n\r\nvarying vec2      var_DiffuseTex;\r\nvarying vec2      va"
"r_LightTex;\r\n\r\nvarying vec3      var_Position;\r\n\r\n#if defined(USE_N"
"ORMALMAP)\r\nvarying vec3      var_Tangent;\r\nvarying vec3      var_Bitang"
"ent;\r\n#endif\r\n\r\nvarying vec3      var_Normal;\r\n\r\n\r\nfloat RayInt"
"ersectDisplaceMap(vec2 dp, vec2 ds, sampler2D normalMap)\r\n{\r\n\tconst in"
"t linearSearchSteps = 5;\r\n\tconst int binarySearchSteps = 5;\r\n\r\n\tflo"
"at depthStep = 1.0 / float(linearSearchSteps);\r\n\r\n\t// current size of "
"search window\r\n\tfloat size = depthStep;\r\n\r\n\t// current depth positi"
"on\r\n\tfloat depth = 0.0;\r\n\r\n\t// best match found (starts with last p"
"osition 1.0)\r\n\tfloat bestDepth = 1.0;\r\n\r\n\t// search front to back f"
"or first point inside object\r\n\tfor(int i = 0; i < linearSearchSteps - 1;"
" ++i)\r\n\t{\r\n\t\tdepth += size;\r\n\t\t\r\n\t\tvec4 t = texture2D(normal"
"Map, dp + ds * depth);\r\n\r\n\t\tif(bestDepth > 0.996)\t\t// if no depth f"
"ound yet\r\n\t\t\tif(depth >= t.w)\r\n\t\t\t\tbestDepth = depth;\t// store "
"best depth\r\n\t}\r\n\r\n\tdepth = bestDepth;\r\n\t\r\n\t// recurse around "
"first point (depth) for closest match\r\n\tfor(int i = 0; i < binarySearchS"
"teps; ++i)\r\n\t{\r\n\t\tsize *= 0.5;\r\n\r\n\t\tvec4 t = texture2D(normalM"
"ap, dp + ds * depth);\r\n\t\t\r\n\t\tif(depth >= t.w)\r\n\t\t{\r\n\t\t\tbes"
"tDepth = depth;\r\n\t\t\tdepth -= 2.0 * size;\r\n\t\t}\r\n\r\n\t\tdepth += "
"size;\r\n\t}\r\n\r\n\treturn bestDepth;\r\n}\r\n\r\nvoid main()\r\n{\r\n#if"
" defined(USE_LIGHTMAP)\r\n\tvec4 light = texture2D(u_LightMap, var_LightTex"
");\r\n  #if defined(USE_DELUXEMAP)\r\n\tvec4 deluxe = texture2D(u_DeluxeMap"
", var_LightTex);\r\n\tvec3 worldLight = normalize(2.0 * deluxe.xyz - vec3(1"
".0));\r\n  #else\r\n\tvec3 worldLight = normalize(var_Normal);\r\n  #endif"
"\r\n#else\r\n\tvec3 worldLight = u_LightOrigin.xyz - (var_Position * u_Ligh"
"tOrigin.w);\r\n  #if defined(USE_INVSQRLIGHT)\r\n\tfloat intensity = 1.0f /"
" dot(worldLight, worldLight);\r\n  #else\r\n\tfloat intensity = clamp((1.0 "
"- dot(worldLight, worldLight) * u_LightScaleSqr) * 1.07, 0.0, 1.0);\r\n  #e"
"ndif\t\r\n\tworldLight = normalize(worldLight);\r\n\tvec3 directedLight = u"
"_DirectedLight * intensity;\r\n\tvec3 ambientLight  = u_AmbientLight;  \r\n"
"#endif\r\n\r\n\tvec3 SampleToView = normalize(u_ViewOrigin - var_Position);"
"\r\n\tvec2 texOffset = vec2(0.0);\r\n\r\n#if defined(USE_NORMALMAP)\r\n\tma"
"t3 tangentToWorld = mat3(var_Tangent.xyz, var_Bitangent.xyz, var_Normal.xyz"
");\r\n\r\n  #if defined(USE_PARALLAXMAP)\r\n\tvec3 offsetDir = normalize(Sa"
"mpleToView * tangentToWorld);\r\n    #if 0\r\n\tfloat dist = 0.02 * texture"
"2D(u_NormalMap, var_DiffuseTex).w - (0.02 / 2.0);\r\n    #else\r\n\toffsetD"
"ir.xy *= 0.02 / offsetDir.z;\r\n\tfloat dist = RayIntersectDisplaceMap(var_"
"NormalTex, offsetDir.xy, u_NormalMap);\r\n    #endif\t\r\n\ttexOffset = off"
"setDir.xy * dist;\r\n  #endif\r\n  \r\n\tvec3 normal = texture2D(u_NormalMa"
"p, var_DiffuseTex + texOffset).xyz;\r\n\tvec3 worldNormal = normalize(tange"
"ntToWorld * (2.0 * normal.xyz - vec3(1.0)));\r\n#else\r\n\tvec3 worldNormal"
" = normalize(var_Normal);\r\n#endif\r\n\r\n\tvec4 diffuse = texture2D(u_Dif"
"fuseMap, var_DiffuseTex + texOffset) * u_Color;\r\n\r\n#if defined(USE_LIGH"
"TMAP)\r\n\tdiffuse.rgb *= light.rgb;\r\n  #if defined(USE_DELUXEMAP)\r\n   "
" #if defined(USE_NORMALMAP)\r\n      #if defined(r_normalAmbient)\r\n      "
"  diffuse.rgb *= mix(max(dot(worldNormal, worldLight), 0.0), normal.z, r_no"
"rmalAmbient);\r\n      #else\r\n        diffuse.rgb *= max(dot(worldNormal,"
" worldLight), 0.0);\r\n      #endif\r\n    #endif\r\n  #else\r\n    #if def"
"ined(USE_NORMALMAP)\r\n      #if defined(r_normalAmbient)\r\n        diffus"
"e.rgb *= mix(1.0, normal.z, r_normalAmbient);\r\n      #endif\r\n    #endif"
"\r\n  #endif\r\n#else\r\n  #if defined(USE_NORMALMAP) && defined(r_normalAm"
"bient)\r\n        ambientLight *= normal.z;\r\n  #endif\r\n\tdiffuse.rgb *="
" min(directedLight * max(dot(worldNormal, worldLight), 0.0) + ambientLight,"
" 1.0);\r\n#endif\r\n\r\n\tgl_FragColor = diffuse;\r\n\r\n#if defined(USE_SP"
"ECULARMAP)\r\n\tvec4 specular = texture2D(u_SpecularMap, var_DiffuseTex + t"
"exOffset);\r\n\tvec3 halfAngle = normalize(worldLight + SampleToView);\r\n"
"\r\n  #if defined(USE_LIGHTMAP)\r\n\tspecular.rgb *= light.rgb;\r\n  #else"
"\r\n\tspecular.rgb *= directedLight;\r\n  #endif\r\n\r\n\tspecular.rgb *= p"
"ow(max(dot(worldNormal, halfAngle), 0.0), 255 * specular.a);\r\n\r\n\tgl_Fr"
"agColor.rgb += specular.rgb;\r\n#endif\r\n}\r\n";


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
							"#endif\n",
							CGEN_IDENTITY,
							CGEN_VERTEX,
							CGEN_ONE_MINUS_VERTEX,
							CGEN_EXACT_VERTEX,
							CGEN_LIGHTING_DIFFUSE));

		Q_strcat(bufferExtra, sizeof(bufferExtra),
								 va("#ifndef alphaGen_t\n"
									"#define alphaGen_t\n"
									"#define AGEN_IDENTITY %i\n"
									"#define AGEN_VERTEX %i\n"
									"#define AGEN_ONE_MINUS_VERTEX %i\n"
									"#define AGEN_LIGHTING_SPECULAR %i\n"
									"#define AGEN_PORTAL %i\n"
									"#define AGEN_FRESNEL %i\n"
									"#endif\n",
									AGEN_IDENTITY,
									AGEN_VERTEX,
									AGEN_ONE_MINUS_VERTEX,
									AGEN_LIGHTING_SPECULAR,
									AGEN_PORTAL,
									AGEN_FRESNEL));

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

	ri.Printf(PRINT_DEVELOPER, "...loading '%s'\n", filename);
	size = ri.FS_ReadFile(filename, (void **)&buffer);
	if(!buffer)
	{
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
		if (fallback_vp)
		{
			ri.Printf(PRINT_DEVELOPER, "compiling fallback...\n");
			if (!GLSL_CompileGPUShader(program->program, &program->vertexShader, fallback_vp, strlen(fallback_vp), GL_VERTEX_SHADER_ARB, extra, addHeader))
			{
				ri.Printf(PRINT_ALL, "GLSL_InitGPUShader: Unable to load \"%s\" as GL_VERTEX_SHADER_ARB\n", name);
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
			if (fallback_fp)
			{
				ri.Printf(PRINT_DEVELOPER, "compiling fallback...\n");
				if (!GLSL_CompileGPUShader(program->program, &program->fragmentShader, fallback_fp, strlen(fallback_fp), GL_FRAGMENT_SHADER_ARB, extra, addHeader))
				{
					ri.Printf(PRINT_ALL, "GLSL_InitGPUShader: Unable to load \"%s\" as GL_FRAGMENT_SHADER_ARB\n", name);
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

	if(attribs & ATTR_BITANGENT)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_BITANGENT, "attr_Bitangent");

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

	if(attribs & ATTR_TANGENT2)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_TANGENT2, "attr_Tangent2");

	if(attribs & ATTR_BITANGENT2)
		qglBindAttribLocationARB(program->program, ATTR_INDEX_BITANGENT2, "attr_Bitangent2");

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

	*compare = value;

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

	*compare = value;
	
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

	compare[0] = v[0];
	compare[1] = v[1];

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

	VectorCopy(v, compare);

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

	VectorCopy4(v, compare);

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

	Matrix16Copy(matrix, compare);

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

	for (i = 0; i < GENERICDEF_COUNT; i++)
	{	
		attribs = ATTR_POSITION | ATTR_TEXCOORD | ATTR_LIGHTCOORD | ATTR_NORMAL | ATTR_COLOR;
		extradefines[0] = '\0';

		if (i & GENERICDEF_USE_DEFORM_VERTEXES)
			Q_strcat(extradefines, 1024, "#define USE_DEFORM_VERTEXES\n");

		if (i & GENERICDEF_USE_TCGEN)
			Q_strcat(extradefines, 1024, "#define USE_TCGEN\n");

		if (i & GENERICDEF_USE_VERTEX_ANIMATION)
		{
			Q_strcat(extradefines, 1024, "#define USE_VERTEX_ANIMATION\n");
			attribs |= ATTR_POSITION2 | ATTR_NORMAL2;
		}

		if (i & GENERICDEF_USE_FOG)
		{
			Q_strcat(extradefines, 1024, "#define USE_FOG\n");
		}

		if (i & GENERICDEF_USE_RGBAGEN)
		{
			Q_strcat(extradefines, 1024, "#define USE_RGBAGEN\n");
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

		if (i & GENERICDEF_USE_TCGEN)
		{
			GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_TCGEN0,        "u_TCGen0",        GLSL_INT);
			GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_TCGEN0VECTOR0, "u_TCGen0Vector0", GLSL_VEC4);
			GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_TCGEN0VECTOR1, "u_TCGen0Vector1", GLSL_VEC4);
		}

		if (i & GENERICDEF_USE_FOG)
		{
			GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_FOGADJUSTCOLORS, "u_FogAdjustColors", GLSL_INT);
			GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_FOGDISTANCE,     "u_FogDistance",     GLSL_VEC4);
			GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_FOGDEPTH,        "u_FogDepth",        GLSL_VEC4);
			GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_FOGEYET,         "u_FogEyeT",         GLSL_FLOAT);
		}

		if (i & GENERICDEF_USE_DEFORM_VERTEXES)
		{
			GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_DEFORMGEN,    "u_DeformGen",    GLSL_INT);
			GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_DEFORMWAVE,   "u_DeformWave",   GLSL_VEC4);
			GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_DEFORMBULGE,  "u_DeformBulge",  GLSL_VEC3);
			GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_DEFORMSPREAD, "u_DeformSpread", GLSL_FLOAT);
		}

		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_TIME,             "u_Time",           GLSL_FLOAT);
		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_COLOR,            "u_Color",          GLSL_VEC4);
		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_AMBIENTLIGHT,     "u_AmbientLight",   GLSL_VEC3);
		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_DIRECTEDLIGHT,    "u_DirectedLight",  GLSL_VEC3);
		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_LIGHTORIGIN,      "u_LightOrigin",    GLSL_VEC4);
		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_VIEWORIGIN,       "u_ViewOrigin",     GLSL_VEC3);
		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_DIFFUSETEXMATRIX, "u_DiffuseTexMatrix", GLSL_MAT16);
		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_TEXTURE1ENV,      "u_Texture1Env",    GLSL_INT);

		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_DIFFUSEMAP,     "u_DiffuseMap",     GLSL_INT);
		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_LIGHTMAP,       "u_LightMap",       GLSL_INT);

		GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_PORTALRANGE,    "u_PortalRange",    GLSL_FLOAT);

		if (i & GENERICDEF_USE_VERTEX_ANIMATION)
		{
			GLSL_AddUniform(&tr.genericShader[i], GENERIC_UNIFORM_VERTEXLERP, "u_VertexLerp", GLSL_FLOAT);
		}

		GLSL_FinishGPUShader(&tr.genericShader[i]);

		qglUseProgramObjectARB(tr.genericShader[i].program);
		GLSL_SetUniformInt(&tr.genericShader[i], GENERIC_UNIFORM_DIFFUSEMAP, TB_DIFFUSEMAP);
		GLSL_SetUniformInt(&tr.genericShader[i], GENERIC_UNIFORM_LIGHTMAP,   TB_LIGHTMAP);
		qglUseProgramObjectARB(0);
	}


	attribs = ATTR_POSITION | ATTR_TEXCOORD;

	if (!GLSL_InitGPUShader(&tr.textureColorShader, "texturecolor", attribs, qtrue, NULL, qfalse, fallbackTextureColorShader_vp, fallbackTextureColorShader_fp, TEXTURECOLOR_UNIFORM_COUNT))
	{
		ri.Error(ERR_FATAL, "Could not load texturecolor shader!\n");
	}
	
	GLSL_AddUniform(&tr.textureColorShader, TEXTURECOLOR_UNIFORM_MODELVIEWPROJECTIONMATRIX, "u_ModelViewProjectionMatrix", GLSL_MAT16);
	GLSL_AddUniform(&tr.textureColorShader, TEXTURECOLOR_UNIFORM_COLOR,                     "u_Color",                     GLSL_VEC4);
	GLSL_AddUniform(&tr.textureColorShader, TEXTURECOLOR_UNIFORM_DIFFUSEMAP,                "u_DiffuseMap",                GLSL_INT);

	GLSL_FinishGPUShader(&tr.textureColorShader);

	qglUseProgramObjectARB(tr.textureColorShader.program);
	GLSL_SetUniformInt(&tr.textureColorShader, TEXTURECOLOR_UNIFORM_DIFFUSEMAP, TB_DIFFUSEMAP);
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

	if (!GLSL_InitGPUShader(&tr.dlightallShader, "dlight", attribs, qtrue, NULL, qtrue, fallbackDlightallShader_vp, fallbackDlightallShader_fp, DLIGHT_UNIFORM_COUNT))
	{
		ri.Error(ERR_FATAL, "Could not load dlight shader!\n");
	}

	GLSL_AddUniform(&tr.dlightallShader, DLIGHT_UNIFORM_DLIGHTINFO,                "u_DlightInfo",                GLSL_VEC4);
	GLSL_AddUniform(&tr.dlightallShader, DLIGHT_UNIFORM_DEFORMGEN,                 "u_DeformGen",                 GLSL_INT);
	GLSL_AddUniform(&tr.dlightallShader, DLIGHT_UNIFORM_DEFORMWAVE,                "u_DeformWave",                GLSL_VEC4);
	GLSL_AddUniform(&tr.dlightallShader, DLIGHT_UNIFORM_DEFORMBULGE,               "u_DeformBulge",               GLSL_VEC3);
	GLSL_AddUniform(&tr.dlightallShader, DLIGHT_UNIFORM_DEFORMSPREAD,              "u_DeformSpread",              GLSL_FLOAT);
	GLSL_AddUniform(&tr.dlightallShader, DLIGHT_UNIFORM_TIME,                      "u_Time",                      GLSL_FLOAT);
	GLSL_AddUniform(&tr.dlightallShader, DLIGHT_UNIFORM_COLOR,                     "u_Color",                     GLSL_VEC4);
	GLSL_AddUniform(&tr.dlightallShader, DLIGHT_UNIFORM_MODELVIEWPROJECTIONMATRIX, "u_ModelViewProjectionMatrix", GLSL_MAT16);
	GLSL_AddUniform(&tr.dlightallShader, DLIGHT_UNIFORM_VERTEXLERP,                "u_VertexLerp",                GLSL_FLOAT);
	
	GLSL_FinishGPUShader(&tr.dlightallShader);
	
	qglUseProgramObjectARB(tr.dlightallShader.program);
	GLSL_SetUniformInt(&tr.dlightallShader, DLIGHT_UNIFORM_DIFFUSEMAP, TB_DIFFUSEMAP);
	qglUseProgramObjectARB(0);

	for (i = 0; i < LIGHTDEF_COUNT; i++)
	{
		// skip impossible combos
		if (!(i & LIGHTDEF_USE_LIGHTMAP) && (i & LIGHTDEF_USE_DELUXEMAP))
			continue;

		if (!(i & LIGHTDEF_USE_NORMALMAP) && (i & LIGHTDEF_USE_PARALLAXMAP))
			continue;

		if ((i & LIGHTDEF_USE_LIGHTMAP) && (i & LIGHTDEF_ENTITY))
			continue;

		attribs = ATTR_POSITION | ATTR_TEXCOORD | ATTR_NORMAL;
		extradefines[0] = '\0';

		if (r_normalAmbient->value > 0.003f)
			Q_strcat(extradefines, 1024, va("#define r_normalAmbient %f\n", r_normalAmbient->value));

		if (i & LIGHTDEF_USE_LIGHTMAP)
		{
			Q_strcat(extradefines, 1024, "#define USE_LIGHTMAP\n");
			attribs |= ATTR_LIGHTCOORD;
		}

		if (i & LIGHTDEF_USE_NORMALMAP && r_normalMapping->integer)
		{
			Q_strcat(extradefines, 1024, "#define USE_NORMALMAP\n");
			attribs |= ATTR_TANGENT | ATTR_BITANGENT;
		}

		if (i & LIGHTDEF_USE_SPECULARMAP && r_specularMapping->integer)
			Q_strcat(extradefines, 1024, "#define USE_SPECULARMAP\n");

		if (i & LIGHTDEF_USE_DELUXEMAP && r_deluxeMapping->integer)
			Q_strcat(extradefines, 1024, "#define USE_DELUXEMAP\n");

		if (i & LIGHTDEF_USE_PARALLAXMAP && !(i & LIGHTDEF_ENTITY) && r_parallaxMapping->integer)
			Q_strcat(extradefines, 1024, "#define USE_PARALLAXMAP\n");

		if (i & LIGHTDEF_TCGEN_ENVIRONMENT)
			Q_strcat(extradefines, 1024, "#define TCGEN_ENVIRONMENT\n");

		if (i & LIGHTDEF_ENTITY)
		{
			Q_strcat(extradefines, 1024, "#define USE_VERTEX_ANIMATION\n#define USE_MODELMATRIX\n");
			attribs |= ATTR_POSITION2 | ATTR_NORMAL2;

			if (i & LIGHTDEF_USE_NORMALMAP && r_normalMapping->integer)
			{
				attribs |= ATTR_TANGENT2 | ATTR_BITANGENT2;
			}
		}
	
		if (!GLSL_InitGPUShader(&tr.lightallShader[i], "lightall", attribs, qtrue, extradefines, qtrue, fallbackLightallShader_vp, fallbackLightallShader_fp, GENERIC_UNIFORM_COUNT))
		{
			ri.Error(ERR_FATAL, "Could not load lightall shader!\n");
		}

		GLSL_AddUniform(&tr.lightallShader[i], GENERIC_UNIFORM_MODELVIEWPROJECTIONMATRIX, "u_ModelViewProjectionMatrix", GLSL_MAT16);
		GLSL_AddUniform(&tr.lightallShader[i], GENERIC_UNIFORM_MODELMATRIX,               "u_ModelMatrix",               GLSL_MAT16);
		GLSL_AddUniform(&tr.lightallShader[i], GENERIC_UNIFORM_DIFFUSETEXMATRIX,          "u_DiffuseTexMatrix",          GLSL_MAT16);
		//GLSL_AddUniform(&tr.lightallShader[i], GENERIC_UNIFORM_NORMALTEXMATRIX,           "u_NormalTexMatrix",           GLSL_MAT16);
		//GLSL_AddUniform(&tr.lightallShader[i], GENERIC_UNIFORM_SPECULARTEXMATRIX,         "u_SpecularTexMatrix",         GLSL_MAT16);
		GLSL_AddUniform(&tr.lightallShader[i], GENERIC_UNIFORM_VIEWORIGIN,                "u_ViewOrigin",                GLSL_VEC3);

		GLSL_AddUniform(&tr.lightallShader[i], GENERIC_UNIFORM_DIFFUSEMAP,                "u_DiffuseMap",                GLSL_INT);
		GLSL_AddUniform(&tr.lightallShader[i], GENERIC_UNIFORM_LIGHTMAP,                  "u_LightMap",                  GLSL_INT);
		GLSL_AddUniform(&tr.lightallShader[i], GENERIC_UNIFORM_NORMALMAP,                 "u_NormalMap",                 GLSL_INT);
		GLSL_AddUniform(&tr.lightallShader[i], GENERIC_UNIFORM_DELUXEMAP,                 "u_DeluxeMap",                 GLSL_INT);
		GLSL_AddUniform(&tr.lightallShader[i], GENERIC_UNIFORM_SPECULARMAP,               "u_SpecularMap",               GLSL_INT);

		GLSL_AddUniform(&tr.lightallShader[i], GENERIC_UNIFORM_AMBIENTLIGHT,              "u_AmbientLight",              GLSL_VEC3);
		GLSL_AddUniform(&tr.lightallShader[i], GENERIC_UNIFORM_DIRECTEDLIGHT,             "u_DirectedLight",             GLSL_VEC3);
		GLSL_AddUniform(&tr.lightallShader[i], GENERIC_UNIFORM_LIGHTORIGIN,               "u_LightOrigin",               GLSL_VEC4);
		GLSL_AddUniform(&tr.lightallShader[i], GENERIC_UNIFORM_LIGHTSCALESQR,             "u_LightScaleSqr",             GLSL_FLOAT);

		GLSL_AddUniform(&tr.lightallShader[i], GENERIC_UNIFORM_COLOR,                     "u_Color",                     GLSL_VEC4);
		GLSL_AddUniform(&tr.lightallShader[i], GENERIC_UNIFORM_VERTEXLERP,                "u_VertexLerp",                GLSL_FLOAT);

		GLSL_FinishGPUShader(&tr.lightallShader[i]);

		qglUseProgramObjectARB(tr.lightallShader[i].program);
		GLSL_SetUniformInt(&tr.lightallShader[i], GENERIC_UNIFORM_DIFFUSEMAP,  TB_DIFFUSEMAP);
		GLSL_SetUniformInt(&tr.lightallShader[i], GENERIC_UNIFORM_LIGHTMAP,    TB_LIGHTMAP);
		GLSL_SetUniformInt(&tr.lightallShader[i], GENERIC_UNIFORM_NORMALMAP,   TB_NORMALMAP);
		GLSL_SetUniformInt(&tr.lightallShader[i], GENERIC_UNIFORM_DELUXEMAP,   TB_DELUXEMAP);
		GLSL_SetUniformInt(&tr.lightallShader[i], GENERIC_UNIFORM_SPECULARMAP, TB_SPECULARMAP);
		qglUseProgramObjectARB(0);
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
	qglDisableVertexAttribArrayARB(ATTR_INDEX_POSITION2);
	qglDisableVertexAttribArrayARB(ATTR_INDEX_NORMAL);
	qglDisableVertexAttribArrayARB(ATTR_INDEX_TANGENT);
	qglDisableVertexAttribArrayARB(ATTR_INDEX_BITANGENT);
	qglDisableVertexAttribArrayARB(ATTR_INDEX_NORMAL2);
	qglDisableVertexAttribArrayARB(ATTR_INDEX_TANGENT2);
	qglDisableVertexAttribArrayARB(ATTR_INDEX_BITANGENT2);
	qglDisableVertexAttribArrayARB(ATTR_INDEX_COLOR);
	GLSL_BindNullProgram();

	for ( i = 0; i < GENERICDEF_COUNT; i++)
	{
		GLSL_DeleteGPUShader(&tr.genericShader[i]);
	}

	GLSL_DeleteGPUShader(&tr.textureColorShader);
	GLSL_DeleteGPUShader(&tr.fogShader);
	GLSL_DeleteGPUShader(&tr.dlightallShader);

	for ( i = 0; i < LIGHTDEF_COUNT; i++)
	{
		GLSL_DeleteGPUShader(&tr.lightallShader[i]);
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

	if(diff & ATTR_TANGENT)
	{
		if(stateBits & ATTR_TANGENT)
		{
			GLimp_LogComment("qglEnableVertexAttribArrayARB( ATTR_INDEX_TANGENT )\n");
			qglEnableVertexAttribArrayARB(ATTR_INDEX_TANGENT);
		}
		else
		{
			GLimp_LogComment("qglDisableVertexAttribArrayARB( ATTR_INDEX_TANGENT )\n");
			qglDisableVertexAttribArrayARB(ATTR_INDEX_TANGENT);
		}
	}

	if(diff & ATTR_BITANGENT)
	{
		if(stateBits & ATTR_BITANGENT)
		{
			GLimp_LogComment("qglEnableVertexAttribArrayARB( ATTR_INDEX_BITANGENT )\n");
			qglEnableVertexAttribArrayARB(ATTR_INDEX_BITANGENT);
		}
		else
		{
			GLimp_LogComment("qglDisableVertexAttribArrayARB( ATTR_INDEX_BITANGENT )\n");
			qglDisableVertexAttribArrayARB(ATTR_INDEX_BITANGENT);
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

	if(diff & ATTR_TANGENT2)
	{
		if(stateBits & ATTR_TANGENT2)
		{
			GLimp_LogComment("qglEnableVertexAttribArrayARB( ATTR_INDEX_TANGENT2 )\n");
			qglEnableVertexAttribArrayARB(ATTR_INDEX_TANGENT2);
		}
		else
		{
			GLimp_LogComment("qglDisableVertexAttribArrayARB( ATTR_INDEX_TANGENT2 )\n");
			qglDisableVertexAttribArrayARB(ATTR_INDEX_TANGENT2);
		}
	}

	if(diff & ATTR_BITANGENT2)
	{
		if(stateBits & ATTR_BITANGENT2)
		{
			GLimp_LogComment("qglEnableVertexAttribArrayARB( ATTR_INDEX_BITANGENT2 )\n");
			qglEnableVertexAttribArrayARB(ATTR_INDEX_BITANGENT2);
		}
		else
		{
			GLimp_LogComment("qglDisableVertexAttribArrayARB( ATTR_INDEX_BITANGENT2 )\n");
			qglDisableVertexAttribArrayARB(ATTR_INDEX_BITANGENT2);
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

	if((attribBits & ATTR_TANGENT) && !(glState.vertexAttribPointersSet & ATTR_TANGENT))
	{
		GLimp_LogComment("qglVertexAttribPointerARB( ATTR_INDEX_TANGENT )\n");

		qglVertexAttribPointerARB(ATTR_INDEX_TANGENT, 3, GL_FLOAT, 0, glState.currentVBO->stride_tangent, BUFFER_OFFSET(glState.currentVBO->ofs_tangent + glState.vertexAttribsNewFrame * glState.currentVBO->size_normal)); // FIXME
		glState.vertexAttribPointersSet |= ATTR_TANGENT;
	}

	if((attribBits & ATTR_BITANGENT) && !(glState.vertexAttribPointersSet & ATTR_BITANGENT))
	{
		GLimp_LogComment("qglVertexAttribPointerARB( ATTR_INDEX_BITANGENT )\n");

		qglVertexAttribPointerARB(ATTR_INDEX_BITANGENT, 3, GL_FLOAT, 0, glState.currentVBO->stride_bitangent, BUFFER_OFFSET(glState.currentVBO->ofs_bitangent + glState.vertexAttribsNewFrame * glState.currentVBO->size_normal)); // FIXME
		glState.vertexAttribPointersSet |= ATTR_BITANGENT;
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

	if((attribBits & ATTR_TANGENT2) && !(glState.vertexAttribPointersSet & ATTR_TANGENT2))
	{
		GLimp_LogComment("qglVertexAttribPointerARB( ATTR_INDEX_TANGENT2 )\n");

		qglVertexAttribPointerARB(ATTR_INDEX_TANGENT2, 3, GL_FLOAT, 0, glState.currentVBO->stride_tangent, BUFFER_OFFSET(glState.currentVBO->ofs_tangent + glState.vertexAttribsOldFrame * glState.currentVBO->size_normal)); // FIXME
		glState.vertexAttribPointersSet |= ATTR_TANGENT2;
	}

	if((attribBits & ATTR_BITANGENT2) && !(glState.vertexAttribPointersSet & ATTR_BITANGENT2))
	{
		GLimp_LogComment("qglVertexAttribPointerARB( ATTR_INDEX_BITANGENT2 )\n");

		qglVertexAttribPointerARB(ATTR_INDEX_BITANGENT2, 3, GL_FLOAT, 0, glState.currentVBO->stride_bitangent, BUFFER_OFFSET(glState.currentVBO->ofs_bitangent + glState.vertexAttribsOldFrame * glState.currentVBO->size_normal)); // FIXME
		glState.vertexAttribPointersSet |= ATTR_BITANGENT2;
	}
}

shaderProgram_t *GLSL_GetGenericShaderProgram(int stage)
{
	shaderStage_t *pStage = tess.xstages[stage];
	int shaderAttribs = 0;

	if ( tess.fogNum && pStage->adjustColorsForFog)
	{
		shaderAttribs |= GENERICDEF_USE_FOG;
	}

	switch (pStage->rgbGen)
	{
		case CGEN_EXACT_VERTEX:
		case CGEN_LIGHTING_DIFFUSE:
		case CGEN_VERTEX:
		case CGEN_ONE_MINUS_VERTEX:
			shaderAttribs |= GENERICDEF_USE_RGBAGEN;
			break;
		default:
			break;
	}

	switch (pStage->alphaGen)
	{
		case AGEN_LIGHTING_SPECULAR:
		case AGEN_VERTEX:
		case AGEN_ONE_MINUS_VERTEX:
		case AGEN_PORTAL:
		case AGEN_FRESNEL:
			shaderAttribs |= GENERICDEF_USE_RGBAGEN;
			break;
		default:
			break;
	}

	if (pStage->bundle[0].tcGen != TCGEN_TEXTURE)
	{
		shaderAttribs |= GENERICDEF_USE_TCGEN;
	}

	if (!ShaderRequiresCPUDeforms(tess.shader))
	{
		shaderAttribs |= GENERICDEF_USE_DEFORM_VERTEXES;
	}

	if (glState.vertexAttribsInterpolation > 0.0f && backEnd.currentEntity && backEnd.currentEntity != &tr.worldEntity)
	{
		shaderAttribs |= GENERICDEF_USE_VERTEX_ANIMATION;
	}

	return &tr.genericShader[shaderAttribs];
}

