//#version 330 core
varying vec2 f_texcoord;
uniform sampler2D mytexture;

void main() {
    vec2 flipped_texcoord = vec2(f_texcoord.x, 1.0f - f_texcoord.y);
    gl_FragColor = texture2D(mytexture, flipped_texcoord);
}
