
/** TP 5ETI IMI- CPE Lyon - 2015-2016 */



#include "lib/common/error_handling.hpp"

#include "image/image.hpp"
#include "ray_tracing/scene/scene_parameter.hpp"
#include "ray_tracing/primitives/sphere.hpp"
#include "ray_tracing/primitives/plane.hpp"
#include "ray_tracing/primitives/triangle.hpp"
#include "ray_tracing/primitives/cylindre.hpp"


#include "ray_tracing/render_engine/render_engine.hpp"

#include <iostream>
#include <fstream>
#include <cmath>


using namespace cpe;

void test()
{
    std::cout<<"coucou"<<std::endl;
}


int main(int argc,char *argv[])
{

    std::cout<<"***********************"<<std::endl;
    std::cout<<"run "<<argv[0]<<" with "<<argc-1<<" parameters ... \n"<<std::endl;


    try
    {




        //create empty black image
        int const N_pixels = 500;
        image im(N_pixels);
        im.fill({0,0,0});

        //create a 3D scene for ray tracing
        //***********************************//

        scene_parameter scene;

        //setup camera (center, direction, up, distance to the screen,length of the screen)
        //camera devant
        scene.set_camera(camera({0,0,-2},{0,0,1},{0,1,0} , 2.0f,1.2f));
        //camera a droite
        //scene.set_camera(camera({-10,0,0},{1,0,0},{0,1,0} , 2.0f,1.2f));
        //camera derriere
        //scene.set_camera(camera({0,0,10},{0,0,-1},{0,1,0} , 2.0f,1.2f));
        //camera a gauche
        //scene.set_camera(camera({10,0,0},{-1,0,0},{0,1,0} , 2.0f,1.2f));


        //scene.set_camera(camera({0,-10.0,0.0},{0,1,0.0},{0,1,0} , 1.5f,1.2f));
        /*float camerax = 5 * cos(i*M_PI/16);
        float cameraz = 5 * sin(i*M_PI/16) + 2.5;
        float directionx = -cos(i * M_PI/16);
        float directionz = -sin(i * M_PI/16);
        scene.set_camera(camera({camerax,0,cameraz},{directionx,0,directionz},{0,1,0} , 2.0f,1.2f));*/



        shading_parameter shading;

        //add some 3d sphere (center,radius)
        scene.push_back(new sphere( {-0.5f,1.0f,2.0f} , 0.9f ),
                        material(color(0.5f,0.5f,1.0f),shading,0.5f));

        scene.push_back(new sphere( {1.0f,0.8f,1.0f} , 0.2f),
                        material(color(1.0f,0.0f,0.0f),shading,0.9f));

        scene.push_back(new sphere( {1.7f,-0.2f,5.0f} , 0.3f),
                        material(color(0.3f,1.0f,0.0f),shading,0.9f));

        //add some 3d triangle (position1,position2,position3,normal)
      /*  scene.push_back(new triangle( {1.7f,-0.2f,5.0f} , {1.0f,0.8f,1.0f} , {-0.5f,1.0f,2.0f} ),
                        material(color(0.0f,1.0f,0.0f),shading,0.9f));*/
     //   scene.push_back(new triangle( {1.7f,-0.2f,3.0f} , {1.0f,0.8f,3.0f} , {-0.5f,1.0f,3.0f}),
       //                 material(color(0.0f,1.0f,0.0f),shading,0.9f));



        scene.push_back(new cylindre( {-1.0f,-2.0f,5.0f} , {-1.0f,1.0f,5.0f} ,0.1f),
                        material(color(0.3f,1.0f,0.0f),shading,0.9f));



        scene.push_back(new triangle( {-0.5f,1.0f,3.0f} , {1.0f,0.8f,2.5f} , {1.7f,-0.2f,2.5f}),
                        material(color(1.0f,0.0f,1.0f),shading,0.9f));

        /*scene.push_back(new triangle( {0.0f,0.0f,2.0f} , {-0.5f,0.5f,1.0f} , {0.5f,-0.5f,1.0f}),
                        material(color(1.0f,0.0f,0.0f),shading,0.9f));*/

        /*scene.push_back(new triangle( {0.5f,1.0f,4.0f} , {0.0f,0.5f,5.0f} , {-0.5f,0.0f,4.0f}),
                        material(color(0.0f,0.0f,1.0f),shading,0.9f));*/

       /*scene.push_back(new triangle( {0.5f,1.0f,2.0f} , {0.0f,0.5f,1.0f} , {-0.5f,0.0f,2.0f}),
                        material(color(0.0f,0.0f,1.0f),shading,0.9f));*/




        //add some 3d plane (position,normal)
       scene.push_back(new plane( {150.0f,1.0f,0.0f} ,  {0.0f,-1.0f,0.0f}),
                       material(color(0.8f,0.8f,0.8f),shading,0.9f));



        //add a light
       scene.push_back(light( {15.0f,-10.0f,-10.0f} ));


        //Render the scene
        //***********************************//

        render(im,scene);


        im.save("image.ppm");



        /*if(i==0)
            im.save("image0.ppm");
        if(i==1)
            im.save("image1.ppm");
        if(i==2)
            im.save("image2.ppm");
        if(i==3)
            im.save("image3.ppm");
        if(i==4)
            im.save("image4.ppm");
        if(i==5)
            im.save("image5.ppm");
        if(i==6)
            im.save("image6.ppm");
        if(i==7)
            im.save("image7.ppm");
        if(i==8)
            im.save("image8.ppm");
        if(i==9)
            im.save("image9.ppm");
        if(i==10)
            im.save("image10.ppm");
        if(i==11)
            im.save("image11.ppm");
        if(i==12)
            im.save("image12.ppm");
        if(i==13)
            im.save("image13.ppm");
        if(i==14)
            im.save("image14.ppm");
        if(i==15)
            im.save("image15.ppm");
        if(i==16)
            im.save("image16.ppm");
        if(i==17)
            im.save("image17.ppm");
        if(i==18)
            im.save("image18.ppm");
        if(i==19)
            im.save("image19.ppm");
        if(i==20)
            im.save("image20.ppm");
        if(i==21)
            im.save("image21.ppm");
        if(i==22)
            im.save("image22.ppm");
        if(i==23)
            im.save("image23.ppm");
        if(i==24)
            im.save("image24.ppm");
        if(i==25)
            im.save("image25.ppm");
        if(i==26)
            im.save("image26.ppm");
        if(i==27)
            im.save("image27.ppm");
        if(i==28)
            im.save("image28.ppm");
        if(i==29)
            im.save("image29.ppm");
        if(i==30)
            im.save("image30.ppm");
        if(i==31)
            im.save("image31.ppm");*/







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
