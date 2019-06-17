#version 330

uniform sampler2D texture_id;
uniform vec2      size;
uniform vec4      moyenne = vec4(0.5, 0.5, 0.5, 1.0);
uniform float     alpha;

in vec2 v_tex_coord;

out vec4 color;

void main(void)
{
    //Original
    //vec4 c = texture(texture_id, v_tex_coord);
    /*color  = mix(moyenne, c, alpha);*/

    //Noir et blanc
    /*float col = (c.x+ c.y + c.z)/3.0;
    color  = vec4(col, col, col, 1.0);*/

    //Sepia
    /*float red_sepia = (c.r * .393) + (c.g *.769) + (c.b * .189);
    float green_sepia = (c.r * .349) + (c.g *.686) + (c.b * .168);
    float blue_sepia = (c.r * .272) + (c.g *.534) + (c.b * .131);
    color = vec4(red_sepia,green_sepia,blue_sepia,1.0);*/

    //Saturation
    /*vec4 level_satur = vec4(alpha,alpha,alpha,0.0);
    color = c + level_satur;*/

    //Contraste
    /*color = c * alpha;*/

    //Seuillage (on peut faire plusieurs tranche)
    /*float col = (c.x+ c.y + c.z)/3.0;
    if (col < 0.5) {
            col = 0.0;
    }
    else{
           col = 1.0;
    }
    color  = vec4(col, col, col, 1.0);*/

    //flou
    /*vec2 offset = alpha * vec2(1.0,1.0)/size ;
    vec4 c = texture(texture_id,v_tex_coord + offset * vec2(-1.0,-1.0));
    c += texture(texture_id,v_tex_coord + offset * vec2(-1.0,0.0));
    c += texture(texture_id,v_tex_coord + offset * vec2(-1.0,1.0));
    c += texture(texture_id,v_tex_coord + offset * vec2(0.0,-1.0));
    c += texture(texture_id,v_tex_coord + offset * vec2(0.0,0.0));
    c += texture(texture_id,v_tex_coord + offset * vec2(0.0,1.0));
    c += texture(texture_id,v_tex_coord + offset * vec2(1.0,-1.0));
    c += texture(texture_id,v_tex_coord + offset * vec2(1.0,0.0));
    c += texture(texture_id,v_tex_coord + offset * vec2(1.0,1.0));
    color = c / 9.0;*/

    //Dilatation



}
