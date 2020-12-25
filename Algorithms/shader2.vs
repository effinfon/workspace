#version 330 core

// (*?) author: "the vertex shader is simple too;
    // just have to pass the UVs to the fragment shader"

    // (*!?) indeed, the concept of "position modelspace" seems necessary
        // and have thought of it before, since everything gets to be mapped
        // to that [-1.0 .. +1.0] 2Dim space in the end
layout(location = 0) in vec3 vertexPosition_modelspace; // (*?)
layout(location = 1) in vec2 vertexUV;  // (*?)

    // author: "output data; will be interpolated for each fragment" (*?)
out vec2 UV;

uniform mat4 MVP;   // (*?)

void main() {
        // built-in output $gl_Position of the vertex, in "clip space" is "MVP * position"
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

        // UV of the vertex; no "special space" for this one
    UV = vertexUV;
}
