#version 330

uniform sampler2D tex;

in vec2 g_tex_coords;
in vec3 v_position;
in vec3 v_normal;
out vec4 color;
void main(void)
{
  color = texture(tex, g_tex_coords);
}

