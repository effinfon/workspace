#version 330 core
layout (location = 0) out vec4 color;
// how can I link more data to this ? from what I understand, this gets its input directly from
// the vertex shader, but what if the vertex shader has multiple outputs and the fragment shdaer
// also gets some more data from the VBO (?!)

uniform vec3 dominatingColor;

void main() {
//    color = vec4(1.0f, 0.7f, 0.29f, 1.0f);
    color = vec4(dominatingColor, 1.0f);
}
