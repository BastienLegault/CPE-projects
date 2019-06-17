#version 330

uniform sampler2D tex;

in vec2 v_tex_coords;
in vec3 v_position;
in vec3 v_normal;
out vec4 color;
void main(void)
{
  //color = vec4(1.0, 0.0, 0.0, 1.0);
   // color = vec4 ( mod ( gl_FragCoord.xy / 30.0 , vec2 (1.0 ,1.0)) , 0.0 , 1.0);
    /*if((int(floor(gl_FragCoord.x/30)) % 2 == 0 && int(floor(gl_FragCoord.y/30)) % 2 == 0 ) ||
       (int(floor(gl_FragCoord.x/30)) % 2 == 1 && int(floor(gl_FragCoord.y/30)) % 2 == 1))
        color = vec4(0.2, 0.2, 0.2, 1.0);
    else
        color = vec4(0.7, 0.7, 0.7, 1.0);*/

    color = vec4 ( abs ( v_position + v_normal) / 17.0 , 1.0);


}

