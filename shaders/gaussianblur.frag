uniform sampler2D texture;
uniform vec2 resolution;
uniform vec2 direction;

void main() {
    vec2 uv = gl_FragCoord.xy / resolution.xy;
    vec4 color = vec4(0.0);
    vec2 off1 = vec2(1.411764705882353) * direction;
    vec2 off2 = vec2(3.2941176470588234) * direction;
    vec2 off3 = vec2(5.176470588235294) * direction;
    color += texture2D(texture, uv) * 0.1964825501511404;
    color += texture2D(texture, uv + (off1 / resolution)) * 0.2969069646728344;
    color += texture2D(texture, uv - (off1 / resolution)) * 0.2969069646728344;
    color += texture2D(texture, uv + (off2 / resolution)) * 0.09447039785044732;
    color += texture2D(texture, uv - (off2 / resolution)) * 0.09447039785044732;
    color += texture2D(texture, uv + (off3 / resolution)) * 0.010381362401148057;
    color += texture2D(texture, uv - (off3 / resolution)) * 0.010381362401148057;
    gl_FragColor = color;
}
