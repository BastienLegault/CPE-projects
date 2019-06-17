#version 330

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

uniform mat4 projection;
uniform mat4 modelview;
uniform float beta;

in vec3 v_position[];
in vec3 v_normal[];
in vec2 v_tex_coords[];

out vec2 g_tex_coords;


void main(void)
{
/*
    vec4 n_moy = vec4(0.0,0.0,0.0,0.0);
    for (int j = 0; j < 3; j++)
    {
        n_moy += projection * modelview * (vec4(v_normal[j] , 0.0)/3.0);
    }

    if (n_moy.x > 0)
    {
        for (int i = 0; i < 3; i++)
        {
            g_tex_coords = v_tex_coords[i];
            gl_Position = projection * modelview * vec4(v_position[i], 1.0);
         // ou : gl_Position = gl_in[i].gl_Position;
            EmitVertex();
         }
     }

*/


// eclatement

vec3 n_moy = vec3(0.0,0.0,0.0);
for (int j = 0; j < 3; j++)
{
    n_moy += v_normal[j]/3.0;
}
for (int i = 0; i < 3; i++)
{
    g_tex_coords = v_tex_coords[i];
    gl_Position = projection * modelview * vec4(v_position[i]+beta *n_moy, 1.0);
 // ou : gl_Position = gl_in[i].gl_Position;
    EmitVertex();
 }



// doudou
/*
for (int i = 0; i < 3; i++)
{
    g_tex_coords = v_tex_coords[i];
    gl_Position = projection * modelview * (vec4(v_position[i], 1.0)+ beta*vec4(v_normal[i], 0.0));
 // ou : gl_Position = gl_in[i].gl_Position;
    EmitVertex();
 }

*/

     EndPrimitive();
}
