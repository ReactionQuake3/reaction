// REACTION: temporal anti-aliasing (r_temporalAA): this frame, with no memory of edges, over a model's box on the screen,
// where the picture's depth lies within the model's. What moves is not blended; what stands in front of a model behind a
// wall, or far behind it, is the static world and stays blended.
uniform sampler2D u_ScreenImageMap;     // this frame
uniform sampler2D u_ScreenDepthMap;     // this frame's depth

uniform vec2  u_TemporalDepthRange;     // the model's nearest and farthest depth

varying vec2  var_TexCoords;

void main()
{
	float depth = texture2D(u_ScreenDepthMap, var_TexCoords).r;

	if (depth < u_TemporalDepthRange.x || depth > u_TemporalDepthRange.y)
		discard;

	gl_FragColor = vec4(texture2D(u_ScreenImageMap, var_TexCoords).rgb, 0.0);
}
