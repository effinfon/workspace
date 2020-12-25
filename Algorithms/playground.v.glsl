#version 430 core

layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 color;

//layout (location = 2) out vec4 out_var;
//out vec3 out_color;

//uniform vec3 dominatingColor;

void main() {
/*
    position[0] *= 0.7f;
    if(position[0] < 0.5f) position[0] = 0.9f;
*/
    gl_Position = vec4(position, 1.0f);
//    out_color = color;
//    out_color = dominatingColor;

//    out_var = vec4(position, 1.0f) * vec4(color, 1.0f);
}
