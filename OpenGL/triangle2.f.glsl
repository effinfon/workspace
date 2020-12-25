//#version 330 core
uniform float fade;
varying vec3 f_color;

void main() {
  gl_FragColor = vec4(f_color.r, f_color.g, f_color.b, fade);
}
