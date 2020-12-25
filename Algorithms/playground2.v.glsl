#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;

struct DirectionalLight{
    vec3 direction;
    vec3 color;
    vec3 ambient;
};

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform DirectionalLight dLight;

out vec2 iUv;
out vec3 iPosition;
out vec3 iNormal;
out vec3 lightDir;

void main()
{
    iUv = uv;
    iPosition = vec3(viewMatrix * modelMatrix * vec4(position,1));
    iNormal = normal;
    lightDir = vec3(normalize(viewMatrix * vec4(dLight.direction, 0)));

    gl_Position =  projectionMatrix * viewMatrix * modelMatrix * vec4(position,1);
}
