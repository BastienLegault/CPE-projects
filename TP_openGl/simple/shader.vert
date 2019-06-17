#version 330 core

in vec3 position;
in vec3 color;

out vec3 ver_color; // inutilisée pour l'instant

void main(void)
{
  gl_Position = vec4(position, 1.0);
  ver_color = color;
}
