//#version 330 core
attribute vec2 coord2d; // location = 0, as "in order of appearance" ?

void main(void) {
    gl_Position = vec4(coord2d, 0.0f, 1.0f);
}
