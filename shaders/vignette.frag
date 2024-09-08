
uniform vec2 resolution;

void main() {
    vec2 uv = gl_FragCoord.xy / resolution.xy;
    vec2 center = vec2(0.5, 0.5);
    
    // Adjust for aspect ratio
    vec2 aspectRatio = vec2(resolution.x / resolution.y, 1.0);
    vec2 adjustedUV = (uv - center) * aspectRatio + center;
    
    float dist = distance(adjustedUV, center);
    
	float vignette = 1.1 - pow(dist / 0.5, 2.0);
	vignette = clamp(vignette, 0.0, 1.0);

    gl_FragColor = vec4(vec3(vignette * 0.15), 1.0) + vec4(0, 0.0013, 0.0026, 0);
}

