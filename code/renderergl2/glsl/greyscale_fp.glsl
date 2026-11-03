uniform sampler2D u_TextureMap;
uniform float     u_Greyscale;
// REACTION: brightness (r_gamma), as the display's gamma ramp applied it
uniform float     u_Gamma;
varying vec2      var_TexCoords;

// From Rec. 709-1 4.2 "Derivation of luminance signal"
const vec3 LUMA = vec3(0.2125, 0.7154, 0.0721);

void main() {
    vec4 color = texture2D(u_TextureMap, var_TexCoords);
    if (u_Greyscale > 0.0) {
        float y = dot(color.rgb, LUMA);
        color.rgb = mix(color.rgb, vec3(y), clamp(u_Greyscale, 0.0, 1.0));
    }
    if (u_Gamma != 1.0) {
        // the window clamps to 0..1 before the ramp, and pow is undefined below 0
        color.rgb = pow(clamp(color.rgb, 0.0, 1.0), vec3(1.0 / u_Gamma));
    }
    gl_FragColor = color;
}