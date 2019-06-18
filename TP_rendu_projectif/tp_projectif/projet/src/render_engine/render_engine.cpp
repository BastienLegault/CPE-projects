/*
**    TP CPE Lyon
**    Copyright (C) 2015 Damien Rohmer
**
**    This program is free software: you can redistribute it and/or modify
**    it under the terms of the GNU General Public License as published by
**    the Free Software Foundation, either version 3 of the License, or
**    (at your option) any later version.
**
**   This program is distributed in the hope that it will be useful,
**    but WITHOUT ANY WARRANTY; without even the implied warranty of
**    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**    GNU General Public License for more details.
**
**    You should have received a copy of the GNU General Public License
**    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/



#include "render_engine.hpp"

#include "image/image.hpp"
#include "image/color.hpp"
#include "image/image_zbuffer.hpp"
#include "lib/3d/vec3.hpp"
#include "lib/3d/vec4.hpp"
#include "lib/3d/mat4.hpp"
#include "image/drawer.hpp"
#include "lib/mesh/mesh.hpp"
#include "lib/common/basic_functions.hpp"
#include "image/io/image_ppm.hpp"

#include <cmath>

namespace cpe
{

// convert the (x,y) coordinate of a vec3 in discrete pixel position in an image of size (Nx,Ny)
static ivec2 coordinates_to_pixel_index(vec3 const& coord,int const Nx,int const Ny)
{
    int const x = (coord.x()+1.0f)/2.0f * Nx;
    int const y = (coord.y()+1.0f)/2.0f * Ny;

    return ivec2(x,y);
}

//helper function converting a vec3 (x,y,z) into a color (r,g,b)
// (a mesh structure store a color as a vec3)
static color to_color(vec3 const& p)
{
    return color(p.x(),p.y(),p.z());
}


void render(image& im,image_zbuffer& zbuffer,
            vec3 const& p0,vec3 const& p1,vec3 const& p2,
            color const& c0,color const& c1,color const& c2,
            vec3 const& n0,vec3 const& n1,vec3 const& n2,
            mat4 const& model,mat4 const& view,mat4 const& projection
            )
{
    vec3 p0_proj,p1_proj,p2_proj;
    color c0_shading,c1_shading,c2_shading;



    //apply vertex shader on the 3 vertices
    vertex_shader(p0_proj,c0_shading , p0,c0,n0 , model,view,projection);
    vertex_shader(p1_proj,c1_shading , p1,c1,n1 , model,view,projection);
    vertex_shader(p2_proj,c2_shading , p2,c2,n2 , model,view,projection);

    //convert normalized coordinates to pixel coordinate
    ivec2 u0 = coordinates_to_pixel_index(p0_proj,im.Nx(),im.Ny());
    ivec2 u1 = coordinates_to_pixel_index(p1_proj,im.Nx(),im.Ny());
    ivec2 u2 = coordinates_to_pixel_index(p2_proj,im.Nx(),im.Ny());

    //draw triangle in the screen space
    draw_triangle(im,zbuffer,u0,u1,u2 , c0_shading,c1_shading,c2_shading ,
                  p0_proj.z(),p1_proj.z(),p2_proj.z() );
}






void render(image& im,image_zbuffer& zbuffer,mesh const& m,
            mat4 const& model,mat4 const& view,mat4 const& projection)
{
    /*************************************
    // TO DO
    /*************************************
    // Completez l'affichage d'un maillage
    //
    // Pour tous les triangles
    //   p0,p1,p2 <- coordonnees des sommets du triangle
    //   c0,c1,c2 <- couleurs des sommets du triangle (utilisez la fonction to_color pour convertir un vec3 vers la structure color)
    //   n0,n1,n2 <- normales des sommets du triangle
    //
    //   Affichage du triangle courant
    */

    image texture_dino = read_ppm("/fs03/share/users/mathieu.badoux/home/Tp_projection/tp_projectif/projet/data/dino.ppm");

    int u = texture_dino.Nx()-1;
    int v = texture_dino.Ny()-1;

    /*vec2 test(740.551f, 399.239f);
    std::cout<<m.texture_coord(4)<<std::endl;
    std::cout<<texture_dino(test)<<std::endl;*/

    int i = 0;
    for (i=0 ; i!=m.size_connectivity() ; i++)
    {
        const auto triangle = m.connectivity(i);
        vec3 p0 = m.vertex((triangle.u0()));
        vec3 p1 = m.vertex((triangle.u1()));
        vec3 p2 = m.vertex((triangle.u2()));

        /*vec3 c0_v = m.color((triangle.u0()));
        vec3 c1_v = m.color((triangle.u1()));
        vec3 c2_v = m.color((triangle.u2()));

        color c0 = to_color(c0_v);//(c0_v.x(),c0_v.y(),c0_v.z());
        color c1 = to_color(c1_v);//(c1_v.x(),c1_v.y(),c1_v.z());
        color c2 = to_color(c2_v);//(c2_v.x(),c2_v.y(),c2_v.z());*/


        vec2 ac0_v = m.texture_coord((triangle.u0()));
        vec2 ac1_v = m.texture_coord((triangle.u1()));
        vec2 ac2_v = m.texture_coord((triangle.u2()));


        std::cout<<ac0_v.x()*u<<std::endl;

        vec2 c0_v(ac0_v.x()*u,ac0_v.y()*v);
        vec2 c1_v(ac1_v.x()*u,ac1_v.y()*v);
        vec2 c2_v(ac2_v.x()*u,ac2_v.y()*v);

        //std::cout<<bc0_v<<std::endl;

        color c0(texture_dino(c0_v.x(),c0_v.y()));
        color c1(texture_dino(c1_v.x(),c1_v.y()));
        color c2(texture_dino(c2_v.x(),c2_v.y()));

        vec3 n0 = m.normal((triangle.u0()));
        vec3 n1 = m.normal((triangle.u1()));
        vec3 n2 = m.normal((triangle.u2()));

        render(im, zbuffer, p0, p1, p2, c0, c1, c2, n0, n1, n2, model, view, projection);
    }

    std::cout<<u<<std::endl;





    /*

    auto it_m = m.begin();
    auto it_m_end = m.end();

    for ( ; it_m != it_m_end ; ++ it_m )
    {
        const auto triangle = it_m -> connectivity ;

        vec3 p0 = m.vertex((triangle.u0()));
        vec3 p1 = m.vertex((triangle.u1()));
        vec3 p2 = m.vertex((triangle.u2()));

        color c0 = m.color((triangle.u0()));
        color c1 = m.color((triangle.u1()));
        color c2 = m.color((triangle.u2()));

        vec3 n0 = m.normal((triangle.u0()));
        vec3 n1 = m.normal((triangle.u1()));
        vec3 n2 = m.normal((triangle.u2()));

        render(im, zbuffer, p0, p1, p2, c0, c1, c2, n0, n1, n2, model, view, projection);

     }*/

}



void vertex_shader(vec3& p_proj,color& c_shading,
                   vec3 const& p,color const& c,vec3 const& n,
                   mat4 const& model, mat4 const& view,mat4 const& projection)
{
    /*************************************
    // TO DO
    /*************************************
    // Completez le vertex shader
    */
   // vec4 p_bis(p.x(),p.y(),p.z(),1.0f);
    p_proj=projection*view*model*p;    //a modifier

    vec3 src_lum(0.0f,0.0f,0.0f);
    vec3 Ul = normalized(src_lum-p);
    vec3 s = reflected(Ul,normalized(n));
    vec3 cam(0.0f,0.0f,0.0f);
    vec3 t = normalized(cam-p);

    float Ka = 0.2f;
    float Kd = 0.8f;
    float Ks = 0.6f;
    float es = 128.0f;

    float Ia = Ka;
    float Id = Kd * clamp(dot(n,Ul));
    float Is = Ks * pow(clamp(dot(s,t)),es);

    c_shading = (Ia + Id) * c + Is * (1.0f,1.0f,1.0f); //a modifier
}




}

