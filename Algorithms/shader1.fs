#version 120
void main(void) {
    gl_FragColor[0] = 0.0;  // I suppose gl_FragColor is yet another
    gl_FragColor[1] = 0.0;  // built-in variable, but whether it's a
    gl_FragColor[2] = 1.0;  // [3] or [4] depends on RGB vs RGBA when
                            // initializing the OpenGL context
}
