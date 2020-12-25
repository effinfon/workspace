//#version 330 core
attribute vec3 coord3d;
attribute vec3 v_color;
varying vec3 f_color;
uniform mat4 m_transform;   // "model matrix"

void main() {
    gl_Position = m_transform * vec4(coord3d, 1.0f);
    f_color = v_color;
}
