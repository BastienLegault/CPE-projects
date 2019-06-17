#version 330

in vec3 position;
in vec3 vitesse;

out vec3 v_position;

void main (void)
{
  v_position = position + vitesse / 100.0;
  gl_Position = vec4(position, 1.0);
}
