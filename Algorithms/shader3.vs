#version 330 core
layout (location = 0) in vec2 position;
//layout (location = 1) in vec3 color;
//layout (location = 2) in vec10 random_attribute;  // now this, why am I forced to split it into vec of up to dimension 4 (*?) -> GPU design ?
// what about the EBO ? I guess that is "back-ground handled" and is not seen in the shader (*?); and what if it were, what if I could change the EBO from a shader ?

void main() {
//    vec3 temporary = position * color;
//    gl_Position = vec4(temporary, 1.0f);
    gl_Position = vec4(position, 0.0f, 1.0f);
}
