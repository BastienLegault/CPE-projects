#version 330

in vec3 position;
in vec3 normal;
in vec2 tex_coord;

out vec2 v_tex_coords;
out vec3 v_position;
out vec3 v_normal;

uniform mat4 projection;
uniform mat4 modelview;

void main(void)
{
  gl_Position = projection * modelview * vec4(position, 1.0);
  v_tex_coords = tex_coord;
  v_position = position;
  v_normal = normal;
}
