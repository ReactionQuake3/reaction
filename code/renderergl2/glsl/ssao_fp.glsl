uniform sampler2D u_ScreenDepthMap;

uniform vec4   u_ViewInfo; // zfar / znear, zfar, 0.5 / tan(fov_x / 2), 0.5 / tan(fov_y / 2)

varying vec2   var_ScreenTex;

// REACTION: ambient occlusion rewritten. The stock pass took three samples a pixel and counted each as fully in
// front or not, which left dark dots that flickered along corners. This one takes sixteen on a spiral within a
// radius set in game units, weighs each by how far it stands in front of the surface's own plane, and ignores what
// stands far in front (another object, not a crease).
#define NUM_SAMPLES 16
#define RADIUS 24.0      // game units: a crease, not a room's corner (at 40 whole walls darkened toward their edges)
#define STRENGTH 1.0
#define FLOOR 0.55       // the baked light already shades the corners, so this never takes more than 45 %
// How steeply a sample must stand over the surface's plane, as seen from the pixel (the sine of that angle), to count:
// from 15 degrees, fully at 45. A wall meeting a floor stands at up to a right angle; a fold between two facets of
// the ground stands at its own few degrees and is no crease.
#define STEEP_FROM 0.26
#define STEEP_FULL 0.71

float getLinearDepth(sampler2D depthMap, const vec2 tex, const float zFarDivZNear)
{
	float sampleZDivW = texture2D(depthMap, tex).r;
	return 1.0 / mix(zFarDivZNear, 1.0, sampleZDivW);
}

#if defined(USE_REFLECT)
// REACTION: the screen's reflections. The same quad and depth read, compiled a third time (tr.reflectShader). For
// each pixel of a picture half the screen's size: where the surface in it would mirror the eye's line to, followed
// through the picture's own depths until it meets something, and that something's colour, taken from the picture
// just drawn. The next frame's surfaces lay it over the sky probe's reflection (lightall_fp.glsl), from a smaller
// copy the rougher they are. Where the line meets nothing in the picture (it leaves the screen, runs into the sky,
// comes back at the eye) the pixel holds nothing, and the probe shows.
uniform sampler2D u_ScreenImageMap;

#define STEPS 28            // looks along the line; each lies the same share further than the one before (growth), so near ones are fine
#define REFINE 5            // halvings between the last look in front of a surface and the first behind it
#define FIRST_STEP 0.02     // the first look, as a share of the pixel's own distance, plus one unit
#define REACH 2400.0        // game units the line is followed
#define THICK 12.0          // game units: how far behind a surface the line may be found and still count as having met it
#define EDGE 0.08           // of the screen: a reflection found this near its border fades out, as what lies past it is unknown
#define BRIGHTEST 8.0       // a reflected colour is held to this, so one pixel of the sun's glare cannot flood a blurred copy

float ViewDepth(vec2 at)
{
	return u_ViewInfo.y / mix(u_ViewInfo.x, 1.0, texture2D(u_ScreenDepthMap, at).r);
}

// a point's place before the eye (x right, y up, z its distance ahead), and back to the screen
vec3 Place(vec2 at, float depth)
{
	return vec3((at * 2.0 - 1.0) * depth * 0.5 / u_ViewInfo.zw, depth);
}

vec2 ScreenOf(vec3 place)
{
	return 0.5 + place.xy * u_ViewInfo.zw / place.z;
}

void main()
{
	// one pixel of this pass, across and up (taken before any branch, since it reads how values change across the screen)
	vec2 px = vec2(dFdx(var_ScreenTex.x), 0.0);
	vec2 py = vec2(0.0, dFdy(var_ScreenTex.y));
	float raw = texture2D(u_ScreenDepthMap, var_ScreenTex).r;

	gl_FragColor = vec4(0.0);

	// the sky reflects nothing, and the gun in the hand has its depth squeezed into the nearest part of the range
	if (raw >= 0.99999 || raw < WEAPON_DEPTH)
		return;

	float depth = u_ViewInfo.y / mix(u_ViewInfo.x, 1.0, raw);
	vec3 place = Place(var_ScreenTex, depth);

	// the surface's normal from its neighbours' places, each way from the side that lies nearer in depth (the other
	// side may belong to another surface)
	float left = ViewDepth(var_ScreenTex - px), right = ViewDepth(var_ScreenTex + px);
	float below = ViewDepth(var_ScreenTex - py), above = ViewDepth(var_ScreenTex + py);
	vec3 across = (abs(right - depth) < abs(depth - left)) ? Place(var_ScreenTex + px, right) - place : place - Place(var_ScreenTex - px, left);
	vec3 up = (abs(above - depth) < abs(depth - below)) ? Place(var_ScreenTex + py, above) - place : place - Place(var_ScreenTex - py, below);
	vec3 normal = normalize(cross(up, across));     // toward the eye: z runs away from it
	vec3 view = normalize(place);
	vec3 line = reflect(view, normal);

	float along = depth * FIRST_STEP + 1.0;
	float growth = pow(REACH / along, 1.0 / float(STEPS));
	float before = 0.0;
	float met = -1.0;

	for (int i = 0; i < STEPS; i++)
	{
		vec3 there = place + line * along;

		if (there.z <= 1.0)
			break;      // behind the eye

		vec2 at = ScreenOf(there);

		if (at.x < 0.0 || at.x > 1.0 || at.y < 0.0 || at.y > 1.0)
			break;      // off the screen

		float rawThere = texture2D(u_ScreenDepthMap, at).r;

		if (rawThere < 0.99999 && rawThere >= WEAPON_DEPTH)
		{
			float behind = there.z - u_ViewInfo.y / mix(u_ViewInfo.x, 1.0, rawThere);

			// behind what the picture shows there, by no more than the line ran in depth since the last look and
			// the surface's own thickness: further behind, the line is passing at the back of something in front
			if (behind > 0.0 && behind < abs(line.z) * (along - before) + THICK)
			{
				float front = before, back = along;

				for (int j = 0; j < REFINE; j++)
				{
					float middle = 0.5 * (front + back);
					vec3 point = place + line * middle;

					if (point.z > ViewDepth(ScreenOf(point)))
						back = middle;
					else
						front = middle;
				}

				met = back;
				break;
			}
		}

		before = along;
		along *= growth;
	}

	if (met < 0.0)
		return;

	vec2 found = ScreenOf(place + line * met);
	vec2 inside = smoothstep(vec2(0.0), vec2(EDGE), found) * (1.0 - smoothstep(vec2(1.0 - EDGE), vec2(1.0), found));
	float sure = inside.x * inside.y;

	// a line that comes back at the eye would show what stands behind it, which the picture does not hold
	sure *= 1.0 - smoothstep(0.3, 0.7, dot(line, -view));
	sure *= 1.0 - smoothstep(0.7 * REACH, REACH, met);

	// the colour times how sure it is, so that the smaller copies weigh each pixel by that
	gl_FragColor = vec4(min(texture2D(u_ScreenImageMap, found).rgb, vec3(BRIGHTEST)) * sure, sure);
}
#elif defined(USE_HAZE)
// REACTION: air. The same quad and depth read, compiled a second time (tr.hazeShader): what is far takes on a
// little of the sky's colour near the horizon, by how much air lies between it and the eye, so far buildings stand
// apart from near ones. Drawn over the picture before it is tone mapped; the sky itself is left alone.
uniform vec4   u_Color; // the air's colour; alpha: what a game unit of distance adds

void main()
{
	float sampleZDivW = texture2D(u_ScreenDepthMap, var_ScreenTex).r;
	float away = u_ViewInfo.y / mix(u_ViewInfo.x, 1.0, sampleZDivW);   // game units from the eye
	float amount = (sampleZDivW >= 0.99999) ? 0.0 : 1.0 - exp(-away * u_Color.a);

	gl_FragColor = vec4(u_Color.rgb, amount);
}
#else
// REACTION: the depth at half the screen's size with smaller copies of it (tr.depthSmallImage), which the samples
// read. From the full-size depth, the sixteen samples of a pixel near the eye lay up to 380 pixels from it, each
// pixel's turned its own way, so every one fetched a part of that large picture nothing else had just fetched, and
// the pass took about as long as drawing the world. A sample now reads the copy whose texels are an eighth to a
// sixteenth of its distance from the pixel, so neighbours' samples fall into the same few texels (McGuire, Mara
// and Luebke, "Scalable Ambient Obscurance", 2012).
uniform sampler2D u_ScreenImageMap;

#define FIRST_COPY_LOG2 3.0   // a sample under 16 pixels (two to this power, doubled) from its pixel reads the first copy, the half-size depth

void main()
{
	float zFarDivZNear = u_ViewInfo.x;
	float zFar = u_ViewInfo.y;
	float result = 1.0;

	float centre = getLinearDepth(u_ScreenDepthMap, var_ScreenTex, zFarDivZNear);
	float viewZ = centre * zFar;
	// one pixel of this pass, across and up (taken before any branch, since it reads how values change across the screen)
	vec2 px = vec2(dFdx(var_ScreenTex.x), 0.0);
	vec2 py = vec2(0.0, dFdy(var_ScreenTex.y));

	// not the sky, and not the gun in hand, whose depth is squeezed into the nearest part of the range
	if (centre < 0.999 && viewZ > 12.0)
	{
		// How the surface's depth changes across the screen: its plane. Taken from the block of 2 x 2 pixels this
		// pixel is drawn in (dFdx, dFdy), it spanned both faces wherever two meet, and this pass draws at a quarter
		// of the screen's size: along every corner some blocks got a plane that stood behind the next face and
		// went dark, others did not, a row of dark dashes that crawled along the corner with every move. Each
		// direction now takes the side that lies on this pixel's own face: a plane's window depth changes evenly
		// across the screen, so that is the side whose two depths run on evenly through this pixel.
		float here = texture2D(u_ScreenDepthMap, var_ScreenTex).r;
		float left = texture2D(u_ScreenDepthMap, var_ScreenTex - px).r;
		float right = texture2D(u_ScreenDepthMap, var_ScreenTex + px).r;
		float below = texture2D(u_ScreenDepthMap, var_ScreenTex - py).r;
		float above = texture2D(u_ScreenDepthMap, var_ScreenTex + py).r;
		vec2 slope;

		if (abs(texture2D(u_ScreenDepthMap, var_ScreenTex - 2.0 * px).r - 2.0 * left + here)
			< abs(texture2D(u_ScreenDepthMap, var_ScreenTex + 2.0 * px).r - 2.0 * right + here))
			slope.x = (centre - 1.0 / mix(zFarDivZNear, 1.0, left)) / px.x;
		else
			slope.x = (1.0 / mix(zFarDivZNear, 1.0, right) - centre) / px.x;

		if (abs(texture2D(u_ScreenDepthMap, var_ScreenTex - 2.0 * py).r - 2.0 * below + here)
			< abs(texture2D(u_ScreenDepthMap, var_ScreenTex + 2.0 * py).r - 2.0 * above + here))
			slope.y = (centre - 1.0 / mix(zFarDivZNear, 1.0, below)) / py.y;
		else
			slope.y = (1.0 / mix(zFarDivZNear, 1.0, above) - centre) / py.y;
		vec2 reach = min(RADIUS * u_ViewInfo.zw / viewZ, vec2(0.15));   // the radius in screen units at this depth
		// The pixel's place before the eye (x right, y up, z ahead, game units), and its surface's normal there from
		// two more points of the plane found above, turned toward the eye.
		vec3 place = vec3((var_ScreenTex * 2.0 - 1.0) * viewZ * 0.5 / u_ViewInfo.zw, viewZ);
		float acrossZ = viewZ + slope.x * px.x * zFar;
		float upZ = viewZ + slope.y * py.y * zFar;
		vec3 normal = normalize(cross(vec3(((var_ScreenTex + px) * 2.0 - 1.0) * acrossZ * 0.5 / u_ViewInfo.zw, acrossZ) - place,
			vec3(((var_ScreenTex + py) * 2.0 - 1.0) * upZ * 0.5 / u_ViewInfo.zw, upZ) - place));

		if (normal.z > 0.0)
			normal = -normal;

		// one turn of the spiral per pixel, from a pattern that repeats finely enough for the blur after this to even out
		float turn = 6.2831853 * fract(52.9829189 * fract(dot(gl_FragCoord.xy, vec2(0.06711056, 0.00583715))));
		float occlusion = 0.0;

		for (int i = 0; i < NUM_SAMPLES; i++)
		{
			float r = sqrt((float(i) + 0.5) / float(NUM_SAMPLES));
			float a = turn + float(i) * 2.3999632;
			vec2 offset = vec2(cos(a), sin(a)) * r * reach;
			// which copy: by the sample's distance from the pixel, in pixels of this pass
			float copy = clamp(floor(log2(length(offset / vec2(px.x, py.y)))) - FIRST_COPY_LOG2, 0.0, DEPTH_SMALL_COPIES);
			float there = 1.0 / mix(zFarDivZNear, 1.0, texture2DLod(u_ScreenImageMap, var_ScreenTex + offset, copy).r);
			// The sample's place, from the pixel's: how far off it is, and how high it stands over the surface's
			// plane, both in game units. The pass used to take the height along the view, within a radius measured
			// across the view: looking low over ground, that radius reached hundreds of units along the ground, and
			// a facet a few degrees steeper than its neighbour stood "in front" of it by more than a wall's corner
			// does. A dark band lay along every gentle fold of teamjungle's grass and moved with the view.
			float thereZ = there * zFar;
			vec3 to = vec3(((var_ScreenTex + offset) * 2.0 - 1.0) * thereZ * 0.5 / u_ViewInfo.zw, thereZ) - place;
			float away = length(to);
			float rise = dot(to, normal);

			occlusion += smoothstep(0.75, 8.0, rise) * smoothstep(STEEP_FROM, STEEP_FULL, rise / max(away, 0.001))
				* (1.0 - smoothstep(RADIUS, RADIUS * 2.0, away));
		}

		occlusion /= float(NUM_SAMPLES);

		// a surface seen nearly edge-on has no plane to trust
		occlusion *= 1.0 - smoothstep(4000.0, 9000.0, length(slope) * zFar);

		// fades out far away, where a pixel is wider than a crease
		occlusion *= 1.0 - smoothstep(1500.0, 3000.0, viewZ);

		result = clamp(1.0 - STRENGTH * occlusion, FLOOR, 1.0);
	}

	gl_FragColor = vec4(vec3(result), 1.0);
}
#endif
