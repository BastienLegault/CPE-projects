#version 330

layout(triangles) in;
//a decommenter pour l'affichage des normales
//layout(line_strip, max_vertices = 6) out;
layout(triangle_strip, max_vertices = 3) out;

uniform mat4 projection;
uniform mat4 modelview;
//uniform float alpha;

in vec3 v_position[];
in vec3 v_normal[];

void main(void)
{
/*  for (int i = 0; i < 3; i++)
  {
    gl_Position = projection * modelview * vec4(v_position[i], 1.0);
    // ou : gl_Position = gl_in[i].gl_Position;
    EmitVertex();
  }
  EndPrimitive();
*/

//affichage normales
/*
    for (int i = 0 ; i < 3 ; i ++)
    {
    gl_Position = gl_in[i].gl_Position ;
    EmitVertex();
    gl_Position = projection * modelview * (vec4(v_position[i] , 1.0 ) + (vec4(alpha * v_normal[i] , 0.0 ))) ;
    EmitVertex() ;
    EndPrimitive() ;
    }
*/

  //EndPrimitive();
}
