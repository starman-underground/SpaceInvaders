uniform sampler2D texture;
uniform vec2 resolution;
uniform float strength;

void main() {
    vec2 uv = gl_FragCoord.xy / resolution.xy;
    vec2 center = vec2(0.5, 0.5);
    vec2 dir = center - uv;
    
    vec4 color = vec4(0.0);
    for (int i = 0; i < 1000; i++) {
        float scale = 1.0 - strength * (float(i) / 1000.0);
        color += texture2D(texture, uv + dir * scale);
    }
    color /= 1000.0;
    
    gl_FragColor = color;
}
