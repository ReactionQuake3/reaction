uniform sampler2D u_DiffuseMap;

uniform int       u_AlphaTest;

#if defined(USE_TEMPORAL_JITTER)
uniform vec2      u_TemporalJitter;     // REACTION: pixels the static world is drawn off (RB_SetTemporalJitter)
#endif

varying vec2      var_DiffuseTex;

varying vec4      var_Color;


void main()
{
#if defined(USE_TEMPORAL_JITTER)
	// the texture as if the view were not offset; an alpha-tested edge is geometry and keeps the offset
	float textureShift = (u_AlphaTest == 0) ? 1.0 : 0.0;
	vec4 color  = texture2D(u_DiffuseMap, var_DiffuseTex + (dFdx(var_DiffuseTex) * u_TemporalJitter.x + dFdy(var_DiffuseTex) * u_TemporalJitter.y) * textureShift);
#else
	vec4 color  = texture2D(u_DiffuseMap, var_DiffuseTex);
#endif

	float alpha = color.a * var_Color.a;
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
	
	gl_FragColor.rgb = color.rgb * var_Color.rgb;
	gl_FragColor.a = alpha;
}
