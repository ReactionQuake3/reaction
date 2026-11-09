// REACTION: temporal anti-aliasing (r_temporalAA). The static world's geometry is drawn a fraction of a pixel off, a
// different one each frame (VPF_TEMPORALJITTER), while textures read as if it were not (RB_SetTemporalJitter). At the
// world's geometry edges the frames are blended, moved to where this frame sees them, so a ledge thinner than a pixel is
// averaged over the offsets instead of showing or vanishing with every small move. Everywhere else this frame alone is
// the picture: inside a surface mipmapping has filtered it already, and blending would only soften it as the view moves.
uniform sampler2D u_ScreenImageMap;     // this frame
uniform sampler2D u_TextureMap;         // the frames blended so far; alpha: how lately each pixel saw an edge
uniform sampler2D u_ScreenDepthMap;     // this frame's depth

uniform mat4  u_ReprojectionMatrix;     // this frame's clip space to the last frame's
uniform vec2  u_InvTexRes;              // one pixel
uniform float u_TemporalBlend;          // this frame's share on an edge; 1 starts over

varying vec2  var_TexCoords;

// WEAPON_DEPTH comes from the renderer (DEPTHHACK_RANGE): the view weapon is drawn in depths from 0 to it.

// A depth step across a pixel of this much marks an edge (window depth, 0 to 1). Inside any plane the step is about zero;
// with r_znear 4 this sees a step of about 4.5 units at 3000 units. 0.2 to 2 millionths popped the same at urban's walkway.
const float EDGE_DEPTH_STEP = 2.0e-6;
// What a frame keeps of an edge seen before, so that a ledge caught in one of the eight offsets counts through the others.
const float EDGE_MEMORY = 0.85;
// An edge seen lately counts in full down to EDGE_FULL of its memory, and not at all from EDGE_FORGOTTEN.
const float EDGE_FULL = 0.25;
const float EDGE_FORGOTTEN = 0.05;
// While the picture moves this many pixels a frame or more, this frame's share rises to MOTION_BLEND.
const float MOTION_PIXELS = 8.0;
const float MOTION_BLEND = 0.25;
// The history is held within this many standard deviations of the neighbourhood's mean.
const float SPREAD = 1.25;

// A surface's window depth changes linearly across the screen, also at a grazing angle, so its second difference across
// a pixel is about zero inside a surface and large where the pixel sees a geometry edge or a thin ledge.
float depthStep(float centre)
{
	vec2 x = vec2(u_InvTexRes.x, 0.0);
	vec2 y = vec2(0.0, u_InvTexRes.y);
	vec2 d1 = u_InvTexRes;
	vec2 d2 = vec2(u_InvTexRes.x, -u_InvTexRes.y);
	float across = abs(texture2D(u_ScreenDepthMap, var_TexCoords - x).r + texture2D(u_ScreenDepthMap, var_TexCoords + x).r - 2.0 * centre);
	float along = abs(texture2D(u_ScreenDepthMap, var_TexCoords - y).r + texture2D(u_ScreenDepthMap, var_TexCoords + y).r - 2.0 * centre);
	float diagonal1 = abs(texture2D(u_ScreenDepthMap, var_TexCoords - d1).r + texture2D(u_ScreenDepthMap, var_TexCoords + d1).r - 2.0 * centre);
	float diagonal2 = abs(texture2D(u_ScreenDepthMap, var_TexCoords - d2).r + texture2D(u_ScreenDepthMap, var_TexCoords + d2).r - 2.0 * centre);

	return max(max(across, along), max(diagonal1, diagonal2));
}

// The history between pixels. Bilinear reads blur a little more with every frame the view moves; Catmull-Rom, here
// from five bilinear reads, keeps it sharp.
vec3 historyAt(vec2 uv)
{
	vec2 position = uv / u_InvTexRes;
	vec2 centre = floor(position - 0.5) + 0.5;
	vec2 f = position - centre;
	vec2 w0 = f * (-0.5 + f * (1.0 - 0.5 * f));
	vec2 w1 = 1.0 + f * f * (-2.5 + 1.5 * f);
	vec2 w2 = f * (0.5 + f * (2.0 - 1.5 * f));
	vec2 w3 = f * f * (-0.5 + 0.5 * f);
	vec2 w12 = w1 + w2;
	vec2 t0 = (centre - 1.0) * u_InvTexRes;
	vec2 t3 = (centre + 2.0) * u_InvTexRes;
	vec2 t12 = (centre + w2 / w12) * u_InvTexRes;
	vec3 sum = texture2D(u_TextureMap, vec2(t12.x, t0.y)).rgb * (w12.x * w0.y)
	         + texture2D(u_TextureMap, vec2(t0.x, t12.y)).rgb * (w0.x * w12.y)
	         + texture2D(u_TextureMap, t12).rgb * (w12.x * w12.y)
	         + texture2D(u_TextureMap, vec2(t3.x, t12.y)).rgb * (w3.x * w12.y)
	         + texture2D(u_TextureMap, vec2(t12.x, t3.y)).rgb * (w12.x * w3.y);
	float total = w12.x * w0.y + w0.x * w12.y + w12.x * w12.y + w3.x * w12.y + w12.x * w3.y;

	return max(sum / total, vec3(0.0));
}

void main()
{
	vec3 current = texture2D(u_ScreenImageMap, var_TexCoords).rgb;
	float depth = texture2D(u_ScreenDepthMap, var_TexCoords).r;
	vec2 previous = var_TexCoords;
	float blend = u_TemporalBlend;
	float edge;
	vec3 low, high, sum, squares, mean, spread;
	vec4 clip;
	int x, y;

	// the view weapon moves with the eye and is no part of the static world
	if (depth < WEAPON_DEPTH)
	{
		gl_FragColor = vec4(current, 0.0);
		return;
	}

	clip = u_ReprojectionMatrix * vec4(var_TexCoords * 2.0 - 1.0, depth * 2.0 - 1.0, 1.0);
	if (clip.w <= 0.0)
		blend = 1.0;
	else
		previous = clip.xy / clip.w * 0.5 + 0.5;

	if (previous.x < 0.0 || previous.y < 0.0 || previous.x > 1.0 || previous.y > 1.0)
		blend = 1.0;

	// only where this pixel saw an edge lately; when starting over, the history is not read: it may be undefined
	edge = depthStep(depth) >= EDGE_DEPTH_STEP ? 1.0 : 0.0;
	if (blend < 1.0)
		edge = max(edge, texture2D(u_TextureMap, previous).a * EDGE_MEMORY);

	blend = max(blend, mix(blend, MOTION_BLEND, clamp(length((previous - var_TexCoords) / u_InvTexRes) / MOTION_PIXELS, 0.0, 1.0)));
	blend = mix(1.0, blend, smoothstep(EDGE_FORGOTTEN, EDGE_FULL, edge));
	if (blend >= 1.0)
	{
		gl_FragColor = vec4(current, edge);
		return;
	}

	// the colours this frame shows around the pixel: what the blended frames may still show here
	low = current;
	high = current;
	sum = current;
	squares = current * current;
	for (y = -1; y <= 1; y++)
	{
		for (x = -1; x <= 1; x++)
		{
			if (x != 0 || y != 0)
			{
				vec3 neighbour = texture2D(u_ScreenImageMap, var_TexCoords + vec2(float(x), float(y)) * u_InvTexRes).rgb;
				low = min(low, neighbour);
				high = max(high, neighbour);
				sum += neighbour;
				squares += neighbour * neighbour;
			}
		}
	}
	mean = sum / 9.0;
	spread = sqrt(max(squares / 9.0 - mean * mean, vec3(0.0))) * SPREAD;
	low = max(low, mean - spread);
	high = min(high, mean + spread);

	gl_FragColor = vec4(mix(clamp(historyAt(previous), low, high), current, blend), edge);
}
