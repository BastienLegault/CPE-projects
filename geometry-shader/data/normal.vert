#version 330

in vec3 position;
in vec3 normal;

out vec3 v_position;
out vec3 v_normal;

uniform mat4 projection;
uniform mat4 modelview;

void main(void)
{
  gl_Position = projection * modelview * vec4(position, 1.0);
  v_position  = position;
  v_normal = normal;
}
