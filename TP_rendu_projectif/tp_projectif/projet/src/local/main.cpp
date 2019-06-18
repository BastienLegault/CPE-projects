
/** TP 5ETI IMI- CPE Lyon - 2015-2016 */



#include "lib/common/error_handling.hpp"

#include "discrete/bresenham.hpp"
#include "discrete/line_discrete.hpp"
#include "discrete/line_interpolation_parameter.hpp"
#include "image/image.hpp"
#include "image/drawer.hpp"
#include "discrete/triangle_scanline.hpp"
#include "image/image_zbuffer.hpp"
#include "lib/mesh/mesh.hpp"
#include "lib/mesh/mesh_io.hpp"
#include "render_engine/render_engine.hpp"
#include "lib/3d/mat4.hpp"
#include "lib/3d/mat3.hpp"
#include "lib/3d/vec4.hpp"
#include "image/texture.hpp"

#include <iostream>
#include <fstream>
#include <cmath>



using namespace cpe;

int main(int argc,char *argv[])
{

    std::cout<<"***********************"<<std::endl;
    std::cout<<"run "<<argv[0]<<" with "<<argc-1<<" parameters ... \n"<<std::endl;


    try
    {
  /*      int const Nx = 40;
        int const Ny = 25;

        image im(Nx,Ny);
        //std::cout << im(91, 10) << std::endl;
        im.fill({1.0f,1.0f,1.0f});*/
/*
        im(20,10) = color(1.0f,1.0f,0.0f);
        im(21,10) = color(1.0f,0.0f,0.0f);

        for(int k=0;k<20;++k)
            im(10+k,5) = color(k/20.0f,0.0f,1.0f-k/20.0f);

        for(int k=0;k<20;++k)
            im(10,5+k) = color(k/20.0f,k/20.0f,k/20.0f);

        line_discrete line ; // création d’une ligne discrète
        line . push_back ( ivec2 (4 , 5)); // ajout d’une position
        line . push_back ({5 , 6}); // autre méthode d’ajout
        const ivec2 p (6 , 7);
        line . push_back ( p ); // autre méthode d’ajout
        std :: cout << line << std :: endl ; // affichage du contenu de la ligne

        // première méthode de parcours de la ligne
        for ( int k = 0; k < line . size (); k ++)
        std :: cout << line [ k ] << " ␣ " ;
        std :: cout << std :: endl ;
        // deuxième méthode de parcours de la ligne
        for ( const ivec2 & p : line )
        std :: cout << p << " ␣ " ;
        std :: cout << std :: endl ;
  */

 /*       //refaire avec des lignes plus grandes et pas juste diag et ligne droite
        const ivec2 p0(20,12);
        const ivec2 p1(30,17);
        const ivec2 p2(25,22);
        const ivec2 p3(15,22);
        const ivec2 p4(10,17);
        const ivec2 p5(10,7);
        const ivec2 p6(15,2);
        const ivec2 p7(25,2);
        const ivec2 p8(30,7);
        const color c = color(1.0f,0.0f,0.0f);
        draw_line(im,p0,p1,c);
        draw_line(im,p0,p2,c);
        draw_line(im,p0,p3,c);
        draw_line(im,p0,p4,c);
        draw_line(im,p0,p5,c);
        draw_line(im,p0,p6,c);
        draw_line(im,p0,p7,c);
        draw_line(im,p0,p8,c);
*/
        /*const ivec2 p0(5,10);
        const ivec2 p1(35,20);
        const color c0 = color(1.0f,0.0f,0.0f);
        const color c1 = color(0.0f,1.0f,0.0f);
        draw_line(im,p0,p1,c0,c1);*/

        /*const ivec2 p0(5,5);
        const ivec2 p1(35,15);
        const ivec2 p2(22,21);
        const color c = color(1.0f,0.0f,0.0f);
        draw_triangle_wireframe(im,p0,p1,p2,c);*/

       /* draw_triangle_wireframe(im , {15 ,12} ,{2 ,17} ,{6 ,3} , {0 ,0 ,0});
        auto scanline = triangle_scanline_factory({15 ,12} ,{2 ,17} ,{6 ,3}, 0.0f ,1.0f ,2.0f);
        std :: cout << scanline << std :: endl ;*/

        /*draw_triangle_wireframe(im , {15 ,12} ,{2 ,17} ,{6 ,3} , {0 ,0 ,0});
        auto scanline = triangle_scanline_factory({15 ,12} ,{2 ,17} ,{6 ,3} ,color (1 ,0 ,0) , color (0 ,1 ,0) , color (0 ,0 ,1));
        std::cout << scanline << std::endl ;*/

        /*const ivec2 p0(5,5);
        const ivec2 p1(35,15);
        const ivec2 p2(22,21);
        const color c0 = color(1.0f,0.0f,0.0f);
        const color c1 = color(0.0f,1.0f,0.0f);
        const color c2 = color(0.0f,0.0f,1.0f);
        draw_triangle(im,p0,p1,p2,c0,c1,c2);*/


     /*   image_zbuffer zbuffer(Nx,Ny);

        const ivec2 p0_1(35,35);
        const ivec2 p1_1(5,15);
        const ivec2 p2_1(28,2);
        const color c0_1 = color(1.0f,1.0f,0.0f);
        const color c1_1 = color(1.0f,1.0f,0.0f);
        const color c2_1 = color(1.0f,1.0f,0.0f);
        float z0_1 = 0.5f;
        float z1_1 = 0.4f;
        float z2_1 = 0.4f;


        draw_triangle(im,zbuffer,p0_1,p1_1,p2_1,c0_1,c1_1,c2_1,z0_1,z1_1,z2_1);

        image_zbuffer zbuffer(Nx,Ny);
        const ivec2 p0(5,5);
        const ivec2 p1(35,15);
        const ivec2 p2(22,21);
        const color c0 = color(1.0f,0.0f,0.0f);
        const color c1 = color(0.0f,1.0f,0.0f);
        const color c2 = color(0.0f,0.0f,1.0f);
        float z0 = 0.8f;
        float z1 = -0.5f;
        float z2 = 0.88f;

        draw_line(im,p0,p1,c0,c1,zbuffer,z0,z1);
        draw_triangle(im,zbuffer,p0,p1,p2,c0,c1,c2,z0,z1,z2);

*/
        image im(1000,1000);
        //std::cout << im(91, 10) << std::endl;
        im.fill({1.0f,1.0f,1.0f});
        image_zbuffer zbuffer(1000,1000);
        /*const vec3 p0(5.0f,4.0f,-15.0f);
        const vec3 p1(-4.0f,-5.0f,-18.0f);
        const vec3 p2(-2.0f,3.0f,-10.5f);
        const color c0 = color(1.0f,0.0f,0.0f);
        const color c1 = color(1.0f,0.0f,0.0f);
        const color c2 = color(1.0f,0.0f,0.0f);
        const vec3 n0(-1.0f,-1.0f,-1.0f);
        const vec3 n1(0.5f,0.5f,0.5f);
        const vec3 n2(1.0f,1.0f,1.0f);
        mat4 model ; // identité

        /*mat4 model(1.0f,0.0f,0.0f,0.0f,
                   0.0f,1.0f,0.0f,5.0f,
                   0.0f,0.0f,1.0f,-5.0f,
                   0.0f,0.0f,0.0f,1.0f); // matrice de translation
        float angle = M_PI /3.0f;
        mat4 model(cos(angle),-sin(angle),0.0f,0.0f,
                   sin(angle),cos(angle), 0.0f,0.0f,
                   0.0f,      0.0f,       1.0f,0.0f,
                   0.0f,      0.0f,       0.0f,1.0f); // matrice de translation selon zs

        mat4 view ;// identité
        mat4 projection ;
        // matrice de projection angle de vue de 60 degres ,
        // image de taille carree ,
        // sommets visibles entre z =0.1 et z =20.
        projection.set_projection_perspective(60* M_PI /180.0f ,1.0f ,0.1f ,20.0f );
        std::cout<<projection<<std::endl;
        render(im,zbuffer,p0,p1,p2,c0,c1,c2,n0,n1,n2,model,view,projection);
        im.save("mon_image.ppm");

        */









        // chargement du fichier
        mesh m = load_mesh_file("/fs03/share/users/mathieu.badoux/home/Tp_projection/tp_projectif/projet/data/dino.obj");
        // applique po te n ti el l em e nt une rotation , translation
        //(scaling possible egalement )
        m.transform_apply_rotation({0 ,1 ,0}, - M_PI /4.0f );
        m.transform_apply_translation({0 ,0 , -1.5f });
        m.fill_color({1 ,1 ,1}); // applique la couleur blanche a
        //l’ensemble des sommets
        m.fill_normal();
        // calcul automatique des normales


        mat4 model ; // identité
        /*float angle = M_PI /3.0f;
        mat4 model(1.0f,0.0f,        0.0f,       0.0f,
                   0.0f, cos(angle), -sin(angle),0.0f,
                   0.0f, sin(angle), cos(angle), 0.0f,
                   0.0f, 0.0f,       0.0f,       1.0f); // matrice de translation selon x*/
        mat4 view ;// identité
        mat4 projection ;
        // matrice de projection angle de vue de 60 degres ,
        // image de taille carree ,
        // sommets visibles entre z =0.1 et z =20.
        projection.set_projection_perspective(60* M_PI /180.0f ,1.0f ,0.1f ,20.0f );
        render(im,zbuffer,m,model,view,projection);


        im.save("mon_image.ppm");

        std::cout<<"oui"<<std::endl;


    }
    catch(cpe::exception_cpe const& e)
    {


        std::cout<<"**********************************"<<std::endl;
        std::cout<<"**********************************"<<std::endl;
        std::cout<<"Exception found"<<std::endl;
        std::cout<<e.info()<<std::endl;
        std::cout<<"\nSaving backtrace in file backtrace_log.txt"<<std::endl;
        std::cout<<"**********************************"<<std::endl;
        std::cout<<"**********************************"<<std::endl;


        std::ofstream back_file("backtrace_log.txt");
        back_file<<e.info()<<std::endl;
        back_file<<e.info_backtrace();
        back_file.close();

        exit(1);
    }


    std::cout<<"Exit Main"<<std::endl;

    return 0;
}
