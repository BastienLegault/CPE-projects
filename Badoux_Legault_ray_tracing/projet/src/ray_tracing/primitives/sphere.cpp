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

#include "sphere.hpp"

#include "intersection_data.hpp"
#include "../scene/ray.hpp"
#include "lib/common/error_handling.hpp"

#include <cmath>

namespace cpe
{

sphere::sphere(vec3 const& center_param,float radius_param)
    :center_data(center_param),radius_data(radius_param)
{}

vec3 const& sphere::center() const
{
    return center_data;
}
float sphere::radius() const
{
    return radius_data;
}

bool sphere::intersect(ray const& ray_param,intersection_data& intersection) const
{

    vec3 const& u = ray_param.u();
    vec3 const& p0 = ray_param.p0();
    vec3 const& center = center_data;
    float const& r = radius_data;


    // ********************************************************** //
    // ********************************************************** //
    //  TO DO:
    //    Calcul d'intersection entre un rayon et une plan
    //
    // Variales:
    //  - Position initiale du rayon: ray_param.p0()
    //  - Vecteur directeur unitaire du rayon: u
    //  - Position du centre de la sphere: center_data
    //  - Rayon de la sphere: radius_data
    //
    // Aide de syntaxe:
    //  - Norme au carre d'un vecteur v: float norme=v.norm2();
    //             ou: float norme=v.dot(v);
    //
    // ********************************************************** //
    // ********************************************************** //

    vec3 const diff = p0 - center;

    float a = dot(u,u);
    float b = 2.0 * dot(diff,u);
    float c = dot(diff,diff) - r*r;

    //float const delta = 4*dot(u,u)*r*r;
    float const delta = b*b - 4.0*a*c;

    if(delta < 0)
        return false;


    if(delta == 0)
    {
        //float const t_inter = - sqrt(dot(diff,diff)) / sqrt(dot(u,u));
        //float const t_inter = - dot(u,diff) / dot(u,u);
        float const t_inter = - b / (2*a);

        vec3 const p_inter = p0 + t_inter*u;
        vec3 const n = p_inter - center;
        vec3 const n_inter = normalized(n);

        intersection.set(p_inter,n_inter,t_inter);

        return true;
    }


    if(delta > 0)
    {
     //   float const t1 = - (sqrt(dot(diff,diff)) + r) / sqrt(dot(u,u));
       // float const t2 = - (sqrt(dot(diff,diff)) - r) / sqrt(dot(u,u));


/*
        float const t1 = - (dot(u,diff) - sqrt(dot(u,u)) * r) / dot(u,u);
        float const t2 = - (dot(u,diff) + sqrt(dot(u,u)) * r) / dot(u,u);
        */
        float const t1 = - (b - sqrt(delta)) / (2*a);
        float const t2 = - (b + sqrt(delta)) / (2*a);



        float t_inter = t2;
        if(t_inter < 0)
            t_inter = t1;
        if (t_inter <0)
           return false;

        vec3 const p_inter = p0 + t_inter*u;
        vec3 const n = p_inter - center;
        vec3 const n_inter = normalized(n);

        intersection.set(p_inter,n_inter,t_inter);

        return true;
    }



}



}
