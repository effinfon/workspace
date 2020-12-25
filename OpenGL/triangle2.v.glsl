//#version 330 core
attribute vec2 coord2d;
attribute vec3 v_color;
varying vec3 f_color;

void main() {
    gl_Position = vec4(coord2d, 0.0f, 1.0f);
    f_color = v_color;
}
