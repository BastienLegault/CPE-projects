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
#include "ray_tracing/scene/scene_parameter.hpp"
#include "ray_tracing/scene/ray.hpp"
#include "ray_tracing/primitives/intersection_data.hpp"
#include "ray_tracing/scene/anti_aliasing_table.hpp"
#include <cmath>

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>  // openMP thread
#include <sys/time.h>

namespace cpe
{







#define SIZE 2000



double get_time() {

  struct timeval tv;

  gettimeofday(&tv, NULL);

  return (double) tv.tv_sec + tv.tv_usec*1e-6;

}




void render(image& im,scene_parameter const& scene)
{
    // **************************************************************************** //
    //
    // Current Algorithm:
    //
    // For all pixels of the image
    //    Generate ray from the camera toward in the direction of the current pixel
    //    Compute associated color (ray tracing algorithm)
    //    Set the color to the current pixel
    //
    // **************************************************************************** //

    camera const& cam = scene.get_camera();

    int const Nx = im.Nx();
    int const Ny = im.Ny();
    int const Nu = 5;
    int const Nv = 5;
    anti_aliasing_table aa(Nu);

    int kx, ky;
    double t, start, stop;
    int nb_threads = 5;
    // loop over all the pixels of the image
    start = get_time();
  //  #pragma omp parallel for num_threads(nb_threads) private(kx, ky)

    for(int kx=0 ; kx<Nx ; ++kx)
    {
        float const u = static_cast<float>(kx)/(Nx-1); // Norme de la position en x
        for(int ky=0 ; ky<Ny ; ++ky)
        {
            float const v = static_cast<float>(ky)/(Ny-1);// Norme de la position en y

            //init value = 0
            color c = (0.0f,0.0f,0.0f);
            for(int dx=0 ; dx<Nu ; ++dx)
            {
                for(int dy=0 ; dy<Nv ; ++dy)
                {
                    float const du = aa.displacement(dx)/(Nx-1); //Nx is the size in pixel in x direction
                    float const dv = aa.displacement(dy)/(Ny-1); //Ny is the size in pixel in y direction

                    float const w = aa.weight(dx,dy);

                    ray const r = ray_generator(cam,u+du,v+dv);
                    c += w*ray_trace(r,scene,0);

                    //value += w*F(u+du,v+dv); //F is a function of (u,v)
                }
            }

/*


            for(int ku=0 ; ku<Nu; ++ku)
            {
                float const du = static_cast<float>(ku)/(Nu-1); // Norme de la position en u
                for(int kv=0 ; kv<Nv ; ++kv)
                {
                    float const dv = static_cast<float>(kv)/(Nv-1);// Norme de la position en v
                    // generate ray and compute color
                    ray const r = ray_generator(cam,u+du,v+dv);
                    color const c = ray_trace(r,scene,0);

                }
            }*/
            //std::lock_guard<std::mutex> lck(mtx);
            im({kx,ky}) = c;
        }
    }
    stop=get_time();

    t=stop-start;

    printf("%d\t%f\n",nb_threads,t);


}


ray ray_generator(camera const& cam,float const u,float const v)
{
    // position of the sample on the screen in 3D
    vec3 const p_screen = screen_position(cam,u,v);

    // vector "camera center" to "screen position"
    vec3 const d = p_screen-cam.center();

    // compute the ray
    ray const r(cam.center(),d);

    return r;
}

color ray_trace(ray const& r,scene_parameter const& scene, int n)
{
    // ********************************************* //
    // ********************************************* //
    //
    // TO DO: Calculer la couleur associee a un rayon dans la scene 3D
    //
    // ********************************************* //
    // ********************************************* //
    //Le code suivant affecte la couleur de base de la premiere intersection trouvee
    //Ce code ne gere pas les reflections.

    if(n == 5)
        return color(0,0,0); //no intersection

    //float N = 5.0f;
    //r.n_aug();
    //int i = 0;
    //float coeff = 1/N;

    //ray r_ref = r;
    //vec3 u;

    intersection_data intersection; //current intersection
    int intersected_primitive = 0;  //current index of intersected primitive

    bool const is_intersection = compute_intersection(r,scene,intersection,intersected_primitive);
    if(is_intersection) //if the ray intersects a primitive
    {
        material const& mat = scene.get_material(intersected_primitive);
        color c = compute_illumination(mat,intersection,scene);

        //vec3 u = reflected(r.u(), intersection.normal);
        ray r1 = reflected(r, intersection.normal);
        ray r_ref(intersection.position,r1.u());
        r_ref.offset();
        color c_inter = ray_trace(r_ref,scene,n+1);
        //if(c_inter.r() != 0 && c_inter.g() != 0 && c_inter.b() != 0)
        color c_fin = (c_inter*mat.reflection() + c) / (1.0f + mat.reflection());
        return c_fin;

        /*for(i = 0; i<N; i++)
        {
            u = reflected(r_ref.u(), intersection.normal);
            ray r_ref(intersection.position,u);
            r_ref.offset();
            bool is_intersection_for = compute_intersection(r_ref,scene,intersection,intersected_primitive);
            if(!is_intersection_for)
                return c;
            material const& mat_inter = scene.get_material(intersected_primitive);
            color c_inter = compute_illumination(mat_inter,intersection,scene);
            c = (c_inter*(1.0f-coeff) + c) / (2.0f-coeff);
            coeff += 1/N;

        }
        return c;*/
    }
    else
        return color(0,0,0); //no intersection
}


bool compute_intersection(ray const& r,
                          scene_parameter const& scene,
                          intersection_data& intersection,
                          int& index_intersected_primitive)
{
    // ********************************************* //
    // ********************************************* //
    //
    // TO DO: Calculer l'intersection valide la plus proche
    //        Doit retourner vrai/faux si une intersection est trouvee ou non
    //        Doit mettre a jour intersection et index_intersected_primitive avec l'intersection la plus proche
    //
    // ********************************************* //
    // ********************************************* //

    //Le code suivant renvoie la premiere intersection valide que l'on trouve dans l'ordre de stockage du vecteur
    //Ce code est a modifier afin de trouver la 1ere intersection dans l'espace 3D le long du rayon.

    int const N_primitive = scene.size_primitive();

    bool found_intersection = false;
    int k = 0;

    intersection_data intersection_tmp;
    float t_tmp;

    while(k<N_primitive)
    {
        primitive_basic const & primitive = scene.get_primitive(k);
        bool is_intersection = primitive.intersect(r,intersection_tmp);
        if(is_intersection)
        {
            //std::cout<<intersection.relative<<std::endl;
            if(found_intersection == false || intersection_tmp.relative < t_tmp)
            {
                t_tmp = intersection_tmp.relative;
                intersection = intersection_tmp;
                found_intersection = true;
                index_intersected_primitive = k;
            }
        }

        ++k;
    }

    //std::cout<<k_tmp<<std::endl;

    return found_intersection;

    /*
    while(k<N_primitive && found_intersection==false)
    {
        primitive_basic const & primitive = scene.get_primitive(k);
        bool is_intersection = primitive.intersect(r,intersection);
        if(is_intersection)
            found_intersection = true;
        else
            ++k;
    }*/

}


bool is_in_shadow(vec3 const& p,vec3 const& p_light, scene_parameter const& scene)
{
    // ********************************************* //
    //
    // TO DO: Calculer si le point p est dans l'ombre de la lumiere situee en p_light
    //
    // ********************************************* //


    vec3 u = p_light - p;
    ray r(p,u);
    r.offset();
    int k = 0;
    int const N_primitive = scene.size_primitive();


    intersection_data intersection;

    while(k<N_primitive)
    {
        primitive_basic const & primitive = scene.get_primitive(k);
        bool is_intersection = primitive.intersect(r,intersection);
        if(is_intersection)
        {
            return true;
        }
        ++k;

    }

    return false;

}



color compute_illumination(material const& mat,intersection_data const& intersection,scene_parameter const& scene)
{
    // ********************************************* //
    //
    // TO DO: Mettre en place le calcul d'illumination correct
    //
    //   Pour toutes les lumieres
    //     Si point dans l'ombre
    //       Ajouter a couleur courante une faible part de la couleur du materiau
    //          ex. c += mat.color_object()/10.0f;
    //     Sinon
    //       Calculer illumination au point courant en fonction de la position
    //          de la lumiere et de la camera
    //       Ajouter a couleur courante la contribution suivante:
    //           puissance de la lumiere (L.power)
    //         X couleur de la lumiere (L.c)
    //         X valeur de l'illumination
    //
    // ********************************************* //

    color c;
    camera cam = scene.get_camera();
    //shading_parameter shading = mat.shading();


    vec3 const& p0 = intersection.position;

    int const N_light = scene.size_light();
    for(int k=0; k<N_light ; ++k)
    {
        light const& L = scene.get_light(k);
        bool const shadow = is_in_shadow(p0,L.p,scene);
        if(shadow==false)
        {
            color X = compute_shading(mat.shading(), mat.color_object(), p0, L.p, intersection.normal, cam.center());
            c += L.power * L.c * X;
        }
        else
            c += mat.color_object()/10.0f;

    }

    return c;


}

/*
color compute_shading(shading_parameter const& shading,
                      color const& input,
                      vec3 const& p,
                      vec3 const& p_light,
                      vec3 const& normal,
                      vec3 const& p_camera)

*/
}


