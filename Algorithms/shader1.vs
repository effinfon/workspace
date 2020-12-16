#version 120
attribute vec2 coord2d; // current vertex, input variable, declared in this ~ C code
void main(void) {
    gl_Position = vec4(coord2d, 0.0, 1.0);  // built-in output variable; resulting screen position
}
// vec4: x, y, z, w (w - homogeneous coordinates)
