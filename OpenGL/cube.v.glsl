//#version 330 core
attribute vec3 coord3d;
attribute vec3 v_color;
varying vec3 f_color;
uniform mat4 mvp;   // projection * view * model -> all combined into one matrix

void main() {
    gl_Position = mvp * vec4(coord3d, 1.0f);
    f_color = v_color;
}
