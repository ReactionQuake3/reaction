uniform sampler2D u_ScreenDepthMap;

uniform sampler2DShadow u_ShadowMap;
#if defined(USE_SHADOW_CASCADE)
uniform sampler2DShadow u_ShadowMap2;
uniform sampler2DShadow u_ShadowMap3;
uniform sampler2DShadow u_ShadowMap4;
#endif

uniform mat4      u_ShadowMvp;
#if defined(USE_SHADOW_CASCADE)
uniform mat4      u_ShadowMvp2;
uniform mat4      u_ShadowMvp3;
uniform mat4      u_ShadowMvp4;
#endif

uniform vec3   u_ViewOrigin;
uniform vec4   u_ViewInfo; // zfar / znear, zfar

varying vec2   var_DepthTex;
varying vec3   var_ViewDir;

// depth is GL_DEPTH_COMPONENT24
// so the maximum error is 1.0 / 2^24
#define DEPTH_MAX_ERROR 0.000000059604644775390625

// Input: It uses texture coords as the random number seed.
// Output: Random number: [0,1), that is between 0.0 and 0.999999... inclusive.
// Author: Michael Pohoreski
// Copyright: Copyleft 2012 :-)
// Source: http://stackoverflow.com/questions/5149544/can-i-generate-a-random-number-inside-a-pixel-shader

float random( const vec2 p )
{
  // We need irrationals for pseudo randomness.
  // Most (all?) known transcendental numbers will (generally) work.
  const vec2 r = vec2(
    23.1406926327792690,  // e^pi (Gelfond's constant)
     2.6651441426902251); // 2^sqrt(2) (Gelfond-Schneider constant)
  //return fract( cos( mod( 123456789., 1e-7 + 256. * dot(p,r) ) ) );
  return mod( 123456789., 1e-7 + 256. * dot(p,r) );  
}

#if defined(USE_SHADOW_SMOOTH)
// REACTION: a shadow edge is softened over seven texels of its map by a filter that changes evenly as the point
// moves across the map. The stock filter turns its pattern by a random angle per screen pixel, and that noise
// crawled along every shadow edge; sixteen fixed reads that each said yes or no for one texel made a staircase of
// sixteen levels, which beat against the screen's pixels and crawled too.
float TexelWorld(const mat4 mvp)
{
	// the first row of an orthographic view-projection is a unit axis times 2 / width
	return 2.0 / (length(vec3(mvp[0][0], mvp[1][0], mvp[2][0])) * r_shadowMapSize);
}

vec3 TowardLight(const mat4 mvp)
{
	// its third row runs along the light
	return -normalize(vec3(mvp[0][2], mvp[1][2], mvp[2][2]));
}

// The maps are read with linear filtering (tr_image.c), so one read is the compare blended over four texels. Sixteen
// reads, placed and weighed by where the point lies inside its texel, add up to a tent seven texels wide whose
// every texel weight changes evenly with the point: no step anywhere for the screen's pixels to beat against.
// (Ignacio Castano, "Shadow Mapping Summary", 2013; the weights as in MJP's Shadows sample, MIT licence.)
#define FILTER_REACH 3.5   // texels from the point to the filter's edge

float PCF(const sampler2DShadow shadowmap, const vec2 st, const float dist)
{
	vec2 uv = st * r_shadowMapSize;
	vec2 base = floor(uv + 0.5);
	float s = uv.x + 0.5 - base.x;
	float t = uv.y + 0.5 - base.y;
	vec4 uw = vec4(5.0 * s - 6.0, 11.0 * s - 28.0, -(11.0 * s + 17.0), -(5.0 * s + 1.0));
	vec4 vw = vec4(5.0 * t - 6.0, 11.0 * t - 28.0, -(11.0 * t + 17.0), -(5.0 * t + 1.0));
	vec4 u = vec4((4.0 * s - 5.0) / uw.x - 3.0, (4.0 * s - 16.0) / uw.y - 1.0, -(7.0 * s + 5.0) / uw.z + 1.0, -s / uw.w + 3.0);
	vec4 v = vec4((4.0 * t - 5.0) / vw.x - 3.0, (4.0 * t - 16.0) / vw.y - 1.0, -(7.0 * t + 5.0) / vw.z + 1.0, -t / vw.w + 3.0);
	float sum = 0.0;

	base = (base - 0.5) / r_shadowMapSize;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			sum += uw[x] * vw[y] * shadow2D(shadowmap, vec3(base + vec2(u[x], v[y]) / r_shadowMapSize, dist));
		}
	}

	return sum / 2704.0;   // the weights of a row add up to -52
}

// How far a point lies toward the edge of a map: 0 in its middle, 1 at its edge.
float Reach(const mat4 mvp, const vec3 pos)
{
	vec4 p = mvp * vec4(pos, 1.0);
	vec3 q = abs(p.xyz / p.w);
	return max(q.x, max(q.y, q.z));
}

float Sample(const sampler2DShadow shadowmap, const mat4 mvp, const vec3 pos, const vec3 normal)
{
	float texelWorld = TexelWorld(mvp);
	vec3 toLight = TowardLight(mvp);
	// Moved off its surface by what the filter's width needs, so a lit surface does not shade itself: the filter
	// reaches FILTER_REACH texels along the surface, where a surface the light meets at an angle a from its normal
	// stands FILTER_REACH * tan(a) nearer the light; a point FILTER_REACH * sin(a) out along the normal clears that.
	// And a texel toward the light. The stock shader pulls the point toward the eye, which moves every shadow edge
	// as the eye moves.
	// TOWARD_LIGHT texels toward the light: one clears the map's own rounding; the rest is for a corner where two
	// sunlit faces meet. There the filter reaches onto the other face, which stands nearer the light than this
	// face run on, and with the solid blocks in the maps (R_LoadSunBlockers) that read as shade: a dark line a
	// pixel wide along the corner, broken into dots that flickered with every move. At three texels only the
	// filter's outermost twentieth still reaches it.
	#define TOWARD_LIGHT 3.0
	// A point seen from the side the light is not on is moved off toward the light's side. Its normal is turned to
	// the eye, so off along it the point of a leaf seen from below went behind the leaf's own sheet, which lies in
	// the map at that depth: the leaf shaded itself in specks that changed with every step (measured on
	// teamjungle: 0.37 % of a tree's pixels flipping a step, 0.09 % without sun shadows). Anything else seen from
	// its unlit side takes no sun at all, whatever this answers.
	// The side turns over gradually, while the light passes from along the face to GRAZING behind it. A face the
	// light runs along (on jericho, whose sun stands at yaw 270, every wall facing east or west) has a light term of
	// nothing but the noise of a normal taken from the depths, and an outright choice by its sign put each pixel
	// FILTER_REACH texels into the face's solid or out into the air at random: specks of shade and sun that changed
	// with every frame and every move (at the shutters there, 14 to 21 % of the picture's points changed by more than
	// a quarter in a turn of 0.25 degrees or a step of half a unit), and showed where the surface's own normal leans
	// into the sun. Such a face now reads the eye's side, which is open air.
	#define GRAZING 0.1   // a light term; the normal's noise from 24-bit depths is under 0.05 at 2000 units on a screen 3840 wide
	float lit = dot(normal, toLight);
	float side = clamp(2.0 * lit / GRAZING + 1.0, -1.0, 1.0);   // 1 down to lit 0, -1 from lit -GRAZING
	float skim = sqrt(1.0 - min(lit * lit, 1.0));
	vec4 shadowpos = mvp * vec4(pos + normal * (side * texelWorld * FILTER_REACH * skim) + toLight * (texelWorld * TOWARD_LIGHT), 1.0);

	shadowpos.xyz = shadowpos.xyz * (0.5 / shadowpos.w) + vec3(0.5);
	return PCF(shadowmap, shadowpos.xy, shadowpos.z);
}

// A point takes the first map it lies in. Toward that map's edge it fades into the next one, so no line shows on the
// ground where one map hands over to a coarser one.
#define FADE_FROM 0.82
#define MAP_EDGE  0.97

float Fade(const float here, const float reach, const sampler2DShadow next, const mat4 nextMvp, const vec3 pos, const vec3 normal)
{
	if (reach <= FADE_FROM)
		return here;
	return mix(here, Sample(next, nextMvp, pos, normal), smoothstep(FADE_FROM, MAP_EDGE, reach));
}
#else
float PCF(const sampler2DShadow shadowmap, const vec2 st, const float dist)
{
	float mult;
	float scale = 2.0 / r_shadowMapSize;

#if 0
	// from http://http.developer.nvidia.com/GPUGems/gpugems_ch11.html
	vec2 offset = vec2(greaterThan(fract(var_DepthTex.xy * r_FBufScale * 0.5), vec2(0.25)));
	offset.y += offset.x;
	if (offset.y > 1.1) offset.y = 0.0;
	
	mult = shadow2D(shadowmap, vec3(st + (offset + vec2(-1.5,  0.5)) * scale, dist))
	     + shadow2D(shadowmap, vec3(st + (offset + vec2( 0.5,  0.5)) * scale, dist))
	     + shadow2D(shadowmap, vec3(st + (offset + vec2(-1.5, -1.5)) * scale, dist))
	     + shadow2D(shadowmap, vec3(st + (offset + vec2( 0.5, -1.5)) * scale, dist));
	 
	mult *= 0.25;
#endif

#if defined(USE_SHADOW_FILTER)
	float r = random(var_DepthTex.xy);
	float sinr = sin(r) * scale;
	float cosr = cos(r) * scale;
	mat2 rmat = mat2(cosr, sinr, -sinr, cosr);

	mult =  shadow2D(shadowmap, vec3(st + rmat * vec2(-0.7055767, 0.196515), dist));
	mult += shadow2D(shadowmap, vec3(st + rmat * vec2(0.3524343, -0.7791386), dist));
	mult += shadow2D(shadowmap, vec3(st + rmat * vec2(0.2391056, 0.9189604), dist));
  #if defined(USE_SHADOW_FILTER2)
	mult += shadow2D(shadowmap, vec3(st + rmat * vec2(-0.07580382, -0.09224417), dist));
	mult += shadow2D(shadowmap, vec3(st + rmat * vec2(0.5784913, -0.002528916), dist));
	mult += shadow2D(shadowmap, vec3(st + rmat * vec2(0.192888, 0.4064181), dist));
	mult += shadow2D(shadowmap, vec3(st + rmat * vec2(-0.6335801, -0.5247476), dist));
	mult += shadow2D(shadowmap, vec3(st + rmat * vec2(-0.5579782, 0.7491854), dist));
	mult += shadow2D(shadowmap, vec3(st + rmat * vec2(0.7320465, 0.6317794), dist));

	mult *= 0.11111;
  #else
    mult *= 0.33333;
  #endif
#else
	mult = shadow2D(shadowmap, vec3(st, dist));
#endif

	return mult;
}
#endif

float getLinearDepth(sampler2D depthMap, vec2 tex, float zFarDivZNear)
{
	float sampleZDivW = texture2D(depthMap, tex).r - DEPTH_MAX_ERROR;
	return 1.0 / mix(zFarDivZNear, 1.0, sampleZDivW);
}

#if defined(USE_SHADOW_SMOOTH)
// REACTION: the surface's normal at this pixel, from the pixels beside it. The stock way for a full-screen pass,
// the change of the point across a 2 x 2 block of pixels (dFdx, dFdy), spans both faces wherever two meet, so along
// every corner and edge the normal pointed somewhere between or beyond them and the shadow there was read from the
// wrong place. Here each direction takes the side that lies on this pixel's own surface: a plane's window depth
// changes evenly across the screen, so that is the side whose two depths run on evenly through this pixel.
vec3 SurfaceNormal(const vec3 pos)
{
	vec2 px = vec2(dFdx(var_DepthTex.x), 0.0);
	vec2 py = vec2(0.0, dFdy(var_DepthTex.y));
	vec3 dirX = dFdx(var_ViewDir);   // the view direction changes evenly across the screen, so these are exact
	vec3 dirY = dFdy(var_ViewDir);
	float here = texture2D(u_ScreenDepthMap, var_DepthTex).r;
	float left = texture2D(u_ScreenDepthMap, var_DepthTex - px).r;
	float right = texture2D(u_ScreenDepthMap, var_DepthTex + px).r;
	float down = texture2D(u_ScreenDepthMap, var_DepthTex - py).r;
	float up = texture2D(u_ScreenDepthMap, var_DepthTex + py).r;
	vec3 across, along;

	if (abs(texture2D(u_ScreenDepthMap, var_DepthTex - 2.0 * px).r - 2.0 * left + here)
		< abs(texture2D(u_ScreenDepthMap, var_DepthTex + 2.0 * px).r - 2.0 * right + here))
		across = pos - (u_ViewOrigin + (var_ViewDir - dirX) * getLinearDepth(u_ScreenDepthMap, var_DepthTex - px, u_ViewInfo.x));
	else
		across = (u_ViewOrigin + (var_ViewDir + dirX) * getLinearDepth(u_ScreenDepthMap, var_DepthTex + px, u_ViewInfo.x)) - pos;

	if (abs(texture2D(u_ScreenDepthMap, var_DepthTex - 2.0 * py).r - 2.0 * down + here)
		< abs(texture2D(u_ScreenDepthMap, var_DepthTex + 2.0 * py).r - 2.0 * up + here))
		along = pos - (u_ViewOrigin + (var_ViewDir - dirY) * getLinearDepth(u_ScreenDepthMap, var_DepthTex - py, u_ViewInfo.x));
	else
		along = (u_ViewOrigin + (var_ViewDir + dirY) * getLinearDepth(u_ScreenDepthMap, var_DepthTex + py, u_ViewInfo.x)) - pos;

	return normalize(cross(across, along));
}
#endif

void main()
{
	float result;

	float depth = getLinearDepth(u_ScreenDepthMap, var_DepthTex, u_ViewInfo.x);
	vec4 biasPos = vec4(u_ViewOrigin + var_ViewDir * (depth - 0.5 / u_ViewInfo.x), 1.0);

#if defined(USE_SHADOW_SMOOTH)
	// the point itself, and its surface's normal, turned to face the eye (taken before any branch, since it reads
	// how values change across the screen)
	vec3 pos = u_ViewOrigin + var_ViewDir * depth;
	vec3 normal = SurfaceNormal(pos);

	if (dot(normal, var_ViewDir) > 0.0)
		normal = -normal;

	if ( depth >= 0.999 )
	{
		result = 1.0;
	}
	else if (texture2D(u_ScreenDepthMap, var_DepthTex).r < WEAPON_DEPTH)
	{
		// The gun in the hand (WEAPON_DEPTH comes from the renderer: the view weapon is drawn in depths from 0 to
		// it). Its depths are squeezed into that range, so a point worked out from them lies a few units before
		// the eye, among the arms and the gun of the player's own body as others see it, whose shadow then swept
		// over the hand with every breath of its stance. The whole gun takes one answer instead: whether the eye
		// stands in the sun, read from the map-wide map, which holds the world and nothing that moves.
  #if defined(USE_SHADOW_CASCADE)
		result = Sample(u_ShadowMap4, u_ShadowMvp4, u_ViewOrigin, TowardLight(u_ShadowMvp4));
  #else
		result = Sample(u_ShadowMap, u_ShadowMvp, u_ViewOrigin, TowardLight(u_ShadowMvp));
  #endif
	}
	else
	{

  #if defined(USE_SHADOW_CASCADE)
		float reach = Reach(u_ShadowMvp, pos);

		if (reach < MAP_EDGE)
		{
			result = Fade(Sample(u_ShadowMap, u_ShadowMvp, pos, normal), reach, u_ShadowMap2, u_ShadowMvp2, pos, normal);
		}
		else
		{
			reach = Reach(u_ShadowMvp2, pos);
			if (reach < MAP_EDGE)
			{
				result = Fade(Sample(u_ShadowMap2, u_ShadowMvp2, pos, normal), reach, u_ShadowMap3, u_ShadowMvp3, pos, normal);
			}
			else
			{
				reach = Reach(u_ShadowMvp3, pos);
				if (reach < MAP_EDGE)
					result = Fade(Sample(u_ShadowMap3, u_ShadowMvp3, pos, normal), reach, u_ShadowMap4, u_ShadowMvp4, pos, normal);
				else
					result = Sample(u_ShadowMap4, u_ShadowMvp4, pos, normal);
			}
		}
  #else
		result = Sample(u_ShadowMap, u_ShadowMvp, pos, normal);
  #endif
	}

#else

	vec4 shadowpos = u_ShadowMvp * biasPos;

	if ( depth >= 0.999 )
	{
		result = 1.0;
	}
	else
#if defined(USE_SHADOW_CASCADE)
	if (all(lessThan(abs(shadowpos.xyz), vec3(abs(shadowpos.w)))))
#endif
	{
		shadowpos.xyz = shadowpos.xyz * (0.5 / shadowpos.w) + vec3(0.5);
		result = PCF(u_ShadowMap, shadowpos.xy, shadowpos.z);
	}
#if defined(USE_SHADOW_CASCADE)
	else
	{
		shadowpos = u_ShadowMvp2 * biasPos;

		if (all(lessThan(abs(shadowpos.xyz), vec3(abs(shadowpos.w)))))
		{
			shadowpos.xyz = shadowpos.xyz * (0.5 / shadowpos.w) + vec3(0.5);
			result = PCF(u_ShadowMap2, shadowpos.xy, shadowpos.z);
		}
		else
		{
			shadowpos = u_ShadowMvp3 * biasPos;

			if (all(lessThan(abs(shadowpos.xyz), vec3(abs(shadowpos.w)))))
			{
				shadowpos.xyz = shadowpos.xyz * (0.5 / shadowpos.w) + vec3(0.5);
				result = PCF(u_ShadowMap3, shadowpos.xy, shadowpos.z);
			}
			else
			{
				shadowpos = u_ShadowMvp4 * biasPos;
				shadowpos.xyz = shadowpos.xyz * (0.5 / shadowpos.w) + vec3(0.5);
				result = PCF(u_ShadowMap4, shadowpos.xy, shadowpos.z);
			}
		}
	}
#endif

#endif

	gl_FragColor = vec4(vec3(result), 1.0);
}
