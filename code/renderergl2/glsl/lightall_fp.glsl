uniform sampler2D u_DiffuseMap;

#if defined(USE_LIGHTMAP)
uniform sampler2D u_LightMap;
#endif

#if defined(USE_NORMALMAP)
uniform sampler2D u_NormalMap;
#endif

#if defined(USE_DELUXEMAP)
uniform sampler2D u_DeluxeMap;
#endif

#if defined(USE_SPECULARMAP)
uniform sampler2D u_SpecularMap;
#endif

#if defined(USE_SHADOWMAP)
uniform sampler2D u_ShadowMap;
#endif

#if defined(USE_CUBEMAP)
uniform samplerCube u_CubeMap;
#endif

#if defined(USE_NORMALMAP) || defined(USE_DELUXEMAP) || defined(USE_SPECULARMAP) || defined(USE_CUBEMAP)
// y = deluxe, w = cube
uniform vec4      u_EnableTextures; 
#endif

#if defined(USE_PRIMARY_LIGHT) || defined(USE_SHADOWMAP)
uniform vec3  u_PrimaryLightColor;
uniform vec3  u_PrimaryLightAmbient;
#endif

#if defined(USE_LIGHT) && !defined(USE_FAST_LIGHT)
uniform vec4      u_NormalScale;
uniform vec4      u_SpecularScale;
#endif

#if defined(USE_LIGHT) && !defined(USE_FAST_LIGHT)
#if defined(USE_CUBEMAP)
uniform vec4      u_CubeMapInfo;
#endif
#endif

uniform int       u_AlphaTest;

#if defined(USE_SCREEN_REFLECTIONS) && defined(USE_LIGHTMAP)
// REACTION: the screen's reflections of the frame before (RB_ScreenReflections), and this place in that frame
uniform sampler2D u_ReflectMap;
varying vec4      var_ReflectPos;
#endif

#if defined(USE_ULTRA_LIGHT) && defined(USE_PRIMARY_LIGHT)
// REACTION: the share of the sun a thin surface (a leaf) lets through to the side the sun is not on; 0 for anything else
uniform float     u_ThinSurface;
#endif

#if defined(USE_ULTRA_LIGHT) && defined(USE_LIGHT_VECTOR) && !defined(USE_FAST_LIGHT)
// REACTION: the light that arrives at a model from each of six sides (trRefEntity_t's lightFrom, tr_light.c)
uniform vec3      u_LightFromPX;
uniform vec3      u_LightFromNX;
uniform vec3      u_LightFromPY;
uniform vec3      u_LightFromNY;
uniform vec3      u_LightFromPZ;
uniform vec3      u_LightFromNZ;
#endif

#if defined(USE_TEMPORAL_JITTER)
uniform vec2      u_TemporalJitter;     // REACTION: pixels the static world is drawn off (RB_SetTemporalJitter)
#endif

varying vec4      var_TexCoords;

varying vec4      var_Color;
#if (defined(USE_LIGHT) && !defined(USE_FAST_LIGHT))
varying vec4      var_ColorAmbient;
#endif

// REACTION: with anti-aliasing a pixel on a surface's edge is shaded at its centre, which can lie outside the
// surface, and there the normal and the view direction are run on past the edge. A reflection read with them pointed
// somewhere bright, and the edge of the gun showed a row of white pixels that moved with it. Centroid keeps the
// point these are taken at inside the surface. Texture coordinates stay as they are: their rate of change across
// the screen picks the mip level, and centroid makes it uneven at edges. (The same line is in lightall_vp.glsl.)
#if defined(USE_ULTRA_LIGHT)
#define LIGHTVARYING centroid varying
#else
#define LIGHTVARYING varying
#endif

#if (defined(USE_LIGHT) && !defined(USE_FAST_LIGHT))
LIGHTVARYING vec4   var_Normal;
LIGHTVARYING vec4   var_Tangent;
LIGHTVARYING vec4   var_Bitangent;
#endif

#if defined(USE_LIGHT) && !defined(USE_FAST_LIGHT)
LIGHTVARYING vec4      var_LightDir;
#endif

#if defined(USE_PRIMARY_LIGHT) || defined(USE_SHADOWMAP)
varying vec4      var_PrimaryLightDir;
#endif


#define EPSILON 0.00000001

#if defined(USE_PARALLAXMAP)
float SampleDepth(sampler2D normalMap, vec2 t)
{
  #if defined(SWIZZLE_NORMALMAP)
	return 1.0 - texture2D(normalMap, t).r;
  #else
	return 1.0 - texture2D(normalMap, t).a;
  #endif
}

float RayIntersectDisplaceMap(vec2 dp, vec2 ds, sampler2D normalMap)
{
	const int linearSearchSteps = 16;
	const int binarySearchSteps = 6;

	// current size of search window
	float size = 1.0 / float(linearSearchSteps);

	// adjust position if offset above surface
	dp -= ds * r_parallaxMapOffset;

	// current depth position
	float depth = 0.0;

	// best match found (starts with last position 1.0)
	float bestDepth = 1.0;

	// texture depth at best depth
	float texDepth = 0.0;

	float prevT = SampleDepth(normalMap, dp);
	float prevTexDepth = prevT;

	// search front to back for first point inside object
	for(int i = 0; i < linearSearchSteps - 1; ++i)
	{
		depth += size;
		
		float t = SampleDepth(normalMap, dp + ds * depth);
		
		if(bestDepth > 0.996)		// if no depth found yet
			if(depth >= t)
			{
				bestDepth = depth;	// store best depth
				texDepth = t;
				prevTexDepth = prevT;
			}
		prevT = t;
	}

	depth = bestDepth;

#if !defined (USE_RELIEFMAP)
	float div = 1.0 / (1.0 + (prevTexDepth - texDepth) * float(linearSearchSteps));
	bestDepth -= (depth - size - prevTexDepth) * div;
#else
	// recurse around first point (depth) for closest match
	for(int i = 0; i < binarySearchSteps; ++i)
	{
		size *= 0.5;

		float t = SampleDepth(normalMap, dp + ds * depth);
		
		if(depth >= t)
		{
			bestDepth = depth;
			depth -= 2.0 * size;
		}

		depth += size;
	}
#endif

	return bestDepth - r_parallaxMapOffset;
}

float LightRay(vec2 dp, vec2 ds, sampler2D normalMap)
{
	const int linearSearchSteps = 16;

	// current size of search window
	float size = 1.0 / float(linearSearchSteps);

	// current height from initial texel depth
	float height = 0.0;

	float startDepth = SampleDepth(normalMap, dp);

	// find a collision or escape
	for(int i = 0; i < linearSearchSteps - 1; ++i)
	{
		height += size;

		if (startDepth < height)
			return 1.0;
		
		float t = SampleDepth(normalMap, dp + ds * height);

		if (startDepth > t + height)
			return 0.0;
	}

	return 1.0;
}
#endif

vec3 CalcDiffuse(vec3 diffuseAlbedo, float NH, float EH, float roughness)
{
#if defined(USE_BURLEY)
	// modified from https://disney-animation.s3.amazonaws.com/library/s2012_pbs_disney_brdf_notes_v2.pdf
	float fd90 = -0.5 + EH * EH * roughness;
	float burley = 1.0 + fd90 * 0.04 / NH;
	burley *= burley;
	return diffuseAlbedo * burley;
#else
	return diffuseAlbedo;
#endif
}

vec3 EnvironmentBRDF(float roughness, float NE, vec3 specular)
{
	// from http://community.arm.com/servlet/JiveServlet/download/96891546-19496/siggraph2015-mmg-renaldas-slides.pdf
	float v = 1.0 - max(roughness, NE);
	v *= v * v;
	return vec3(v) + specular;
}

vec3 CalcSpecular(vec3 specular, float NH, float EH, float roughness)
{
	// from http://community.arm.com/servlet/JiveServlet/download/96891546-19496/siggraph2015-mmg-renaldas-slides.pdf
	float rr = roughness*roughness;
	float rrrr = rr*rr;
	float d = (NH * NH) * (rrrr - 1.0) + 1.0;
	float v = (EH * EH) * (roughness + 0.5) + EPSILON;
	return specular * (rrrr / (4.0 * d * d * v));
}


float CalcLightAttenuation(float point, float normDist)
{
	// zero light at 1.0, approximating q3 style
	// also don't attenuate directional light
	float attenuation = (0.5 * normDist - 1.5) * point + 1.0;

	// clamp attenuation
	#if defined(NO_LIGHT_CLAMP)
	attenuation = max(attenuation, 0.0);
	#else
	attenuation = clamp(attenuation, 0.0, 1.0);
	#endif

	return attenuation;
}

#if defined(USE_BOX_CUBEMAP_PARALLAX)
vec4 hitCube(vec3 ray, vec3 pos, vec3 invSize, float lod, samplerCube tex)
{
	// find any hits on cubemap faces facing the camera
	vec3 scale = (sign(ray) - pos) / ray;

	// find the nearest hit
	float minScale = min(min(scale.x, scale.y), scale.z);

	// if the nearest hit is behind the camera, ignore
	// should not be necessary as long as pos is inside the cube
	//if (minScale < 0.0)
		//return vec4(0.0);

	// calculate the hit position, that's our texture coordinates
	vec3 tc = pos + ray * minScale;

	// if the texture coordinates are outside the cube, ignore
	// necessary since we're not fading out outside the cube
	if (any(greaterThan(abs(tc), vec3(1.00001))))
		return vec4(0.0);

	// fade out when approaching the cubemap edges
	//vec3 fade3 = abs(pos);
	//float fade = max(max(fade3.x, fade3.y), fade3.z);
	//fade = clamp(1.0 - fade, 0.0, 1.0);
			
	//return vec4(textureCubeLod(tex, tc, lod).rgb * fade, fade);
	return vec4(textureCubeLod(tex, tc, lod).rgb, 1.0);
}
#endif

void main()
{
	vec3 viewDir, lightColor, ambientColor, reflectance;
	vec3 L, N, E, H;
	float NL, NH, NE, EH, attenuation;

#if defined(USE_LIGHT) && !defined(USE_FAST_LIGHT)
	vec3 surfNormal = (!gl_FrontFacing ? var_Normal : -var_Normal).xyz;
	mat3 tangentToWorld = mat3(var_Tangent.xyz, var_Bitangent.xyz, surfNormal);
	viewDir = vec3(var_Normal.w, var_Tangent.w, var_Bitangent.w);
	E = normalize(viewDir);
#endif

	lightColor = var_Color.rgb;

#if defined(USE_LIGHTMAP)
	vec4 lightmapColor = texture2D(u_LightMap, var_TexCoords.zw);
  #if defined(RGBM_LIGHTMAP)
	lightmapColor.rgb *= lightmapColor.a;
  #endif
  #if defined(USE_PBR) && !defined(USE_FAST_LIGHT)
	lightmapColor.rgb *= lightmapColor.rgb;
  #endif
	lightColor *= lightmapColor.rgb;
#endif

	vec2 texCoords = var_TexCoords.xy;

#if defined(USE_TEMPORAL_JITTER) && !defined(TEMPORAL_WHOLE_PICTURE)
	// the texture as if the view were not offset; an alpha-tested edge is geometry and keeps the offset. Lightmaps
	// keep it too: on a thin strip seen at a grazing angle this would read light from far beyond the strip.
	texCoords += (dFdx(texCoords) * u_TemporalJitter.x + dFdy(texCoords) * u_TemporalJitter.y) * ((u_AlphaTest == 0) ? 1.0 : 0.0);
#endif

#if defined(USE_PARALLAXMAP)
	vec3 offsetDir = E * tangentToWorld;

	offsetDir.xy *= -u_NormalScale.a / offsetDir.z;

	texCoords += offsetDir.xy * RayIntersectDisplaceMap(texCoords, offsetDir.xy, u_NormalMap);
#endif

	vec4 diffuse = texture2D(u_DiffuseMap, texCoords);
	
	float alpha = diffuse.a * var_Color.a;
	if (u_AlphaTest == 1)
	{
		if (alpha == 0.0)
			discard;
	}
	else if (u_AlphaTest == 2)
	{
		if (alpha >= 0.5)
			discard;
	}
	else if (u_AlphaTest == 3)
	{
		if (alpha < 0.5)
			discard;
	}

#if defined(USE_LIGHT) && !defined(USE_FAST_LIGHT)
	L = var_LightDir.xyz;
  #if defined(USE_DELUXEMAP)
	L += (texture2D(u_DeluxeMap, var_TexCoords.zw).xyz - vec3(0.5)) * u_EnableTextures.y;
  #elif defined(USE_ULTRA_LIGHT) && defined(USE_LIGHTMAP) && !defined(USE_LIGHT_VECTOR)
	// REACTION: with a real-time sun the lightmap holds only what the sky, the lamps and other surfaces give, and
	// that light has no single direction; the map's own guess (the light grid's direction at each corner of the
	// surface) still pointed at the sun, or anywhere, and changed across a wall. Most of that light comes from the
	// open side of the surface and from above, so a wall's relief is lit from in front and above, a floor's from
	// above and a ceiling's from below: bumps and mortar lines keep their shape in shade.
	#define SKY_LIFT 0.8
	L = surfNormal + vec3(0.0, 0.0, SKY_LIFT);
  #endif
	float sqrLightDist = dot(L, L);
	L /= sqrt(sqrLightDist);

  #if defined(USE_LIGHT_VECTOR)
	attenuation  = CalcLightAttenuation(float(var_LightDir.w > 0.0), var_LightDir.w / sqrLightDist);
  #else
	attenuation  = 1.0;
  #endif

  #if defined(USE_NORMALMAP)
    #if defined(USE_ULTRA_LIGHT)
	// REACTION: the relief is read one mip level coarser than the colour. Light is not a straight function of
	// the normal, so relief as fine as a pixel does not average out as colour does: under the sun each mortar line
	// and grain a pixel wide flashed as the view moved. A level coarser, no bump is thinner than two pixels; a
	// surface seen close, where one texel covers several pixels, keeps every texel of its relief.
	#define NORMALMAP_LOD_BIAS 1.0
    #else
	#define NORMALMAP_LOD_BIAS 0.0
    #endif
    #if defined(SWIZZLE_NORMALMAP)
	N.xy = texture2D(u_NormalMap, texCoords, NORMALMAP_LOD_BIAS).ag - vec2(0.5);
    #else
	N.xy = texture2D(u_NormalMap, texCoords, NORMALMAP_LOD_BIAS).rg - vec2(0.5);
    #endif
	N.xy *= u_NormalScale.xy;
	N.z = sqrt(clamp((0.25 - N.x * N.x) - N.y * N.y, 0.0, 1.0));
	N = tangentToWorld * N;
  #else
	N = surfNormal;
  #endif

	N = normalize(N);

  #if defined(USE_SHADOWMAP) 
	vec2 shadowTex = gl_FragCoord.xy * r_FBufScale;
	float shadowValue = texture2D(u_ShadowMap, shadowTex).r;

    #if defined(USE_PRIMARY_LIGHT) && defined(USE_ULTRA_LIGHT)
	// REACTION: the sun's own term below already falls off with the angle between the normal and the light (NL2).
	// The stock line also took it here, so the sun fell off with its square: a sunlit wall came out darker than in
	// the bake this light replaces, and every bump in a normal map showed with twice the contrast, which made
	// sunlit gravel and brick sparkle as the view moved. Here only the face's own side counts: a face turned from
	// the light is shadowed, whatever its normal map says (its bumps caught the sun and drew white specks).
	// A thin leaf (u_ThinSurface) seen from the side the sun is not on is not in shade either: the sun on its other
	// side comes through it, and the sun's term below gives it that share.
	{
		float sunSide = dot(surfNormal, var_PrimaryLightDir.xyz) * 6.0;

		shadowValue *= max(clamp(sunSide, 0.0, 1.0), sign(u_ThinSurface) * clamp(-sunSide, 0.0, 1.0));
	}
    #else
	// surfaces not facing the light are always shadowed
	shadowValue *= clamp(dot(N, var_PrimaryLightDir.xyz), 0.0, 1.0);
    #endif

    #if defined(SHADOWMAP_MODULATE)
	lightColor *= shadowValue * (1.0 - u_PrimaryLightAmbient.r) + u_PrimaryLightAmbient.r;
    #endif
  #endif

  #if defined(USE_PARALLAXMAP) && defined(USE_PARALLAXMAP_SHADOWS)
	offsetDir = L * tangentToWorld;
	offsetDir.xy *= u_NormalScale.a / offsetDir.z;
	lightColor *= LightRay(texCoords, offsetDir.xy, u_NormalMap);
  #endif


  #if !defined(USE_LIGHT_VECTOR)
	ambientColor = lightColor;
	float surfNL = clamp(dot(surfNormal, L), 0.0, 1.0);

	// reserve 25% ambient to avoid black areas on normalmaps
	lightColor *= 0.75;

	// Scale the incoming light to compensate for the baked-in light angle
	// attenuation.
	lightColor /= max(surfNL, 0.25);

	// Recover any unused light as ambient, in case attenuation is over 4x or
	// light is below the surface
	ambientColor = max(ambientColor - lightColor * surfNL, vec3(0.0));
  #elif defined(USE_ULTRA_LIGHT)
	// REACTION: a model's light with no single direction comes from six sides, and each point of it takes the
	// sides its normal faces, by the squares of the normal's parts (which add up to one): its top is lit as the
	// floor under it is, its flank as the wall beside it, its underside by what the ground throws back. One colour
	// for the whole model left it flat and of the same brightness all round. var_ColorAmbient holds the surface's
	// own colour times u_AmbientLight, which is 1 for a model lit this way and 0 in a dynamic light's pass.
	{
		vec3 share = N * N;

		ambientColor = var_ColorAmbient.rgb * (share.x * (N.x > 0.0 ? u_LightFromPX : u_LightFromNX)
			+ share.y * (N.y > 0.0 ? u_LightFromPY : u_LightFromNY)
			+ share.z * (N.z > 0.0 ? u_LightFromPZ : u_LightFromNZ));
	}
  #else
	ambientColor = var_ColorAmbient.rgb;
  #endif

	NL = clamp(dot(N, L), 0.0, 1.0);
	NE = clamp(dot(N, E), 0.0, 1.0);
	H = normalize(L + E);
	EH = clamp(dot(E, H), 0.0, 1.0);
	NH = clamp(dot(N, H), 0.0, 1.0);

  #if defined(USE_SPECULARMAP)
	vec4 specular = texture2D(u_SpecularMap, texCoords);
  #else
	vec4 specular = vec4(1.0);
  #endif
	specular *= u_SpecularScale;

  #if defined(USE_PBR)
	diffuse.rgb *= diffuse.rgb;
  #endif

  #if defined(USE_PBR)
	// diffuse rgb is base color
	// specular red is gloss
	// specular green is metallicness
	float gloss = specular.r;
	float metal = specular.g;
	specular.rgb = metal * diffuse.rgb + vec3(0.04 - 0.04 * metal);
	diffuse.rgb *= 1.0 - metal;
  #else
	// diffuse rgb is diffuse
	// specular rgb is specular reflectance at normal incidence
	// specular alpha is gloss
	float gloss = specular.a;

	// adjust diffuse by specular reflectance, to maintain energy conservation
	diffuse.rgb *= vec3(1.0) - specular.rgb;
  #endif

  #if defined(GLOSS_IS_GLOSS)
	float roughness = exp2(-3.0 * gloss);
  #elif defined(GLOSS_IS_SMOOTHNESS)
	float roughness = 1.0 - gloss;
  #elif defined(GLOSS_IS_ROUGHNESS)
	float roughness = gloss;
  #elif defined(GLOSS_IS_SHININESS)
	float roughness = pow(2.0 / (8190.0 * gloss + 2.0), 0.25);
  #endif

  #if defined(USE_ULTRA_LIGHT)
	// REACTION: where the normal turns within one pixel (the rim of a rounded edge, relief finer than a pixel) a
	// shine or reflection is thinner than the pixel and shows as bright dots that move with the view: the gun's far
	// edge had a dotted white rim. The surface is taken as rougher there by how much the normal varies across the
	// pixel, which spreads the shine over what the pixel really covers (Kaplanyan and Hill 2016, Tokuyoshi and
	// Kaplanyan 2019: variance 0.25 of the squared change, added twice to the squared width, at most 0.18).
	{
		vec3 turnX = dFdx(N);
		vec3 turnY = dFdy(N);
		float wider = min(0.5 * (dot(turnX, turnX) + dot(turnY, turnY)), 0.18);
		float width = roughness * roughness;

		roughness = pow(clamp(width * width + wider, 0.0, 1.0), 0.25);
	}
  #endif

	reflectance  = CalcDiffuse(diffuse.rgb, NH, EH, roughness);

  #if defined(r_deluxeSpecular)
    #if defined(USE_LIGHT_VECTOR)
	reflectance += CalcSpecular(specular.rgb, NH, EH, roughness) * r_deluxeSpecular;
    #else
	reflectance += CalcSpecular(specular.rgb, NH, EH, pow(roughness, r_deluxeSpecular));
    #endif
  #endif

	gl_FragColor.rgb  = lightColor   * reflectance * (attenuation * NL);
	gl_FragColor.rgb += ambientColor * diffuse.rgb;

  #if defined(USE_CUBEMAP)
	reflectance = EnvironmentBRDF(roughness, NE, specular.rgb);

	vec3 R = reflect(E, N);

	// parallax corrected cubemap (cheaper trick)
	// from http://seblagarde.wordpress.com/2012/09/29/image-based-lighting-approaches-and-parallax-corrected-cubemap/
	vec3 parallax = u_CubeMapInfo.xyz + u_CubeMapInfo.w * viewDir;

  #if defined(USE_BOX_CUBEMAP_PARALLAX)
	vec3 cubeLightColor = hitCube(R * u_CubeMapInfo.w, parallax, u_CubeMapInfo.www, ROUGHNESS_MIPS * roughness, u_CubeMap).rgb * u_EnableTextures.w;
  #else
	vec3 cubeLightColor = textureCubeLod(u_CubeMap, R + parallax, ROUGHNESS_MIPS * roughness).rgb * u_EnableTextures.w;
  #endif

	// normalize cubemap based on last roughness mip (~diffuse)
	// multiplying cubemap values by lighting below depends on either this or the cubemap being normalized at generation
	//vec3 cubeLightDiffuse = max(textureCubeLod(u_CubeMap, N, ROUGHNESS_MIPS).rgb, 0.5 / 255.0);
	//cubeLightColor /= dot(cubeLightDiffuse, vec3(0.2125, 0.7154, 0.0721));

    #if defined(USE_PBR)
	cubeLightColor *= cubeLightColor;
    #endif

	// multiply cubemap values by lighting
	// not technically correct, but helps make reflections look less unnatural
	//cubeLightColor *= lightColor * (attenuation * NL) + ambientColor;

    #if defined(USE_ULTRA_LIGHT)
	// REACTION: a probe holds its own spot's surroundings in that spot's light, and the nearest one may stand in
	// the sun while this surface stands in an alley: a gun carried into shade gleamed as if the sun were on it. So
	// the reflection is weighed by the light that reaches this surface against the light the probe was made in. The
	// probe's blurriest level is its surroundings' average look, and where a probe stands in the same light as the
	// surface that is PROBE_ALBEDO of the light on the surface (measured on urban: the pistol on a sunlit roof 1/6.7,
	// in an alley whose probe stands in the same shade 1/7.5). Never more than PROBE_MOST, so a dark probe cannot
	// blow a reflection up.
	#define PROBE_ALBEDO 0.14
	#define PROBE_MOST 1.25
      #if defined(USE_LIGHTMAP)
	// The sky's probe (a radius of none, tr_shade.c) is the one every surface of the map with a lightmap shows: the
	// sky and the skyline as seen from over the roofs. It is what a surface under the open sky reflects, in the picture's
	// own values, so it needs no weighing by light; what it needs is how much of the sky this spot sees, or a
	// floor indoors would gleam with a sky no ray from it can reach. The pack's light atlas holds that in its
	// alpha: the sky's light on this spot as a share of its light on open flat ground. A wall under an open sky
	// gets half of that, a slope something between (half of one plus the normal's height), so the share is taken
	// against what this surface's tilt could get at most. A face turned down gets next to nothing either way:
	// SKY_SHARE_LEAST keeps the division from blowing its little up. That share counts the sky straight in front
	// of the surface most, and in a street that is where the house across stands (urban's walls: half of them
	// under 0.07, the most open 0.5), while a reflection goes where the eye's line leaves the surface, mostly
	// along the street, where the sky is open. Which way that is the atlas cannot say, so the square root stands
	// between the two: a wall that sees a fifth of its sky shows the probe at under half, one that sees none
	// shows none.
	#define SKY_SHARE_LEAST 0.25
	if (u_CubeMapInfo.w == 0.0)
	{
		cubeLightColor *= sqrt(clamp(lightmapColor.a / max(0.5 + 0.5 * surfNormal.z, SKY_SHARE_LEAST), 0.0, 1.0));
	}
	else
      #endif
	{
		const vec3 LUMA = vec3(0.2126, 0.7152, 0.0722);
		vec3 arriving = ambientColor + lightColor * (attenuation * NL);
      #if defined(USE_PRIMARY_LIGHT)
		float sunFacing = clamp(dot(N, var_PrimaryLightDir.xyz), 0.0, 1.0);
        #if defined(USE_SHADOWMAP)
		sunFacing *= shadowValue;
        #endif
		arriving += u_PrimaryLightColor * sunFacing;
      #endif
		vec3 surroundings = textureCubeLod(u_CubeMap, N, ROUGHNESS_MIPS).rgb;

		cubeLightColor *= min(dot(arriving, LUMA) * PROBE_ALBEDO / max(dot(surroundings, LUMA), 0.004), PROBE_MOST);
	}
    #endif

    #if defined(USE_SCREEN_REFLECTIONS) && defined(USE_LIGHTMAP)
	// REACTION: what the sky's probe cannot show is what stands in the street: the house across, a lamp, a player.
	// The frame before left, for every pixel, what its surface mirrored of the picture itself and how sure that
	// is (RB_ScreenReflections, ssao_fp.glsl). It lies over the probe's reflection by that sureness: where the
	// mirrored line met something in the picture, that shows; where it met nothing, the sky's probe stays. A rough
	// surface reads a small copy of it, which is a blurred one. It is read where this place stood in that frame.
	if (var_ReflectPos.w > 0.0)
	{
		vec2 was = var_ReflectPos.xy / var_ReflectPos.w * 0.5 + 0.5;

		if (was.x > 0.0 && was.x < 1.0 && was.y > 0.0 && was.y < 1.0)
		{
			vec4 seen = texture2DLod(u_ReflectMap, was, roughness * REFLECT_MIPS);

			cubeLightColor = cubeLightColor * (1.0 - seen.a) + seen.rgb;
		}
	}
    #endif

	gl_FragColor.rgb += cubeLightColor * reflectance;
  #endif

  #if defined(USE_PRIMARY_LIGHT) || defined(SHADOWMAP_MODULATE)
	vec3 L2, H2;
	float NL2, EH2, NH2;

	L2 = var_PrimaryLightDir.xyz;

	// enable when point lights are supported as primary lights
	//sqrLightDist = dot(L2, L2);
	//L2 /= sqrt(sqrLightDist);

	NL2 = clamp(dot(N, L2), 0.0, 1.0);
	H2 = normalize(L2 + E);
	EH2 = clamp(dot(E, H2), 0.0, 1.0);
	NH2 = clamp(dot(N, H2), 0.0, 1.0);

	reflectance  = CalcSpecular(specular.rgb, NH2, EH2, roughness);

	// bit of a hack, with modulated shadowmaps, ignore diffuse
    #if !defined(SHADOWMAP_MODULATE)
	reflectance += CalcDiffuse(diffuse.rgb, NH2, EH2, roughness);
    #endif

	lightColor = u_PrimaryLightColor;

    #if defined(USE_SHADOWMAP)
	lightColor *= shadowValue;
    #endif

	// enable when point lights are supported as primary lights
	//lightColor *= CalcLightAttenuation(float(u_PrimaryLightDir.w > 0.0), u_PrimaryLightDir.w / sqrLightDist);

  #if defined(USE_PARALLAXMAP) && defined(USE_PARALLAXMAP_SHADOWS)
	offsetDir = L2 * tangentToWorld;
	offsetDir.xy *= u_NormalScale.a / offsetDir.z;
	lightColor *= LightRay(texCoords, offsetDir.xy, u_NormalMap);
  #endif

	gl_FragColor.rgb += lightColor * reflectance * NL2;
    #if defined(USE_PRIMARY_LIGHT) && defined(USE_ULTRA_LIGHT) && !defined(SHADOWMAP_MODULATE)
	// REACTION: what the sun on a thin leaf's other side sends through it, in the leaf's own colour and without a
	// highlight. u_ThinSurface is 0 for everything that is not a leaf.
	gl_FragColor.rgb += lightColor * CalcDiffuse(diffuse.rgb, NH2, EH2, roughness) * (u_ThinSurface * clamp(-dot(N, L2), 0.0, 1.0));
    #endif
  #endif

  #if defined(USE_PBR)
	gl_FragColor.rgb = sqrt(gl_FragColor.rgb);
  #endif

#else

	gl_FragColor.rgb = diffuse.rgb * lightColor;

#endif

	gl_FragColor.a = alpha;
}
