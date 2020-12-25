#version 330 core

// interpolated values from the vertex shaders (?!)
in vec2 UV; // (*?) what are "UV coordinates" ?"
out vec3 color;

// values that stay constant for the whole "mesh" []I suppose in other
    // cases this is called the "model" (?!)]
uniform sampler2D myTextureSampler; // still, "Sampler2D" is a strange name
    // for a dts

    // I like how simple it looks, but there seem to be too many
    // built-in things which the IDE does not help me with (?!)
void main() {
    // output color = color of the texture at the specified UV
    color = texture(myTextureSampler, UV).rgb;  // now, is $color the built-in
        // output or is it $gl_FragColor[] (?!)...
}

// (!?) author: "it also needs a sampler2D in order to know which texture to access; you" can access several textures in the same shader
    // "fragment shader needs UV coordinates"
    // "accessing a texture is done with texture(...), which gives back the RGBA vec4"
