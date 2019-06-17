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
#include "triangle.hpp"

#include "intersection_data.hpp"
#include "../scene/ray.hpp"
#include "lib/common/error_handling.hpp"

#include <cmath>

namespace cpe
{

triangle::triangle(vec3 const& position1_param,vec3 const& position2_param,
                   vec3 const& position3_param)
    :position1_data(position1_param),position2_data(position2_param),position3_data(position3_param)

{
    vec3 v1 = position2_param - position1_param;
    vec3 v2 = position3_param - position1_param;
    normal_data = normalized(cross(v2,v1));
}


vec3 const& triangle::position1() const
{
    return position1_data;
}

vec3 const& triangle::position2() const
{
    return position2_data;
}

vec3 const& triangle::position3() const
{
    return position3_data;
}

vec3 const& triangle::normal() const
{
    return normal_data;
}


bool triangle::intersect(ray const& ray_param,intersection_data& intersection) const
{

    vec3 const& u = ray_param.u();
    vec3 const& n = normal_data;
    vec3 const& p0 = ray_param.p0(); //origine du rayon
    vec3 const& xp1 = position1_data;
    vec3 const& xp2 = position2_data;
    vec3 const& xp3 = position3_data;

    // ********************************************************** //
    // ********************************************************** //
    //  TO DO:
    //    Calcul d'intersection entre un rayon et un plan
    //
    // Variables:
    //  - Position initiale du rayon: ray_param.p0()
    //  - Vecteur directeur unitaire du rayon: u
    //  - Position d'un point du plan: position_data
    //  - Normale unitaire au plan: n
    //
    // Aide de syntaxe:
    //  - Calcul du produit scalaire <a,b>: dot(a,b);
    //  - Mise a jour de la donnee d'intersection:
    //                intersection.set(p_inter,n_inter,t_inter);
    //
    // ********************************************************** //
    // ********************************************************** //


    float pdt_u_n = dot(u,n);
    if(pdt_u_n == 0)
        return false;

    float t_inter = dot(xp1 - p0, n) / pdt_u_n; //distance entre p_inter et origine rayon
    vec3 const p_inter = p0 + t_inter*u;
    //const vec3 & p = ray_param(t_inter);
    vec3 const n_inter = n;


    if(t_inter>0)
    {
        /*vec3 AB = xp2 - xp1;
        vec3 BC = xp3 - xp2;
        vec3 CA = xp1 - xp3;

        vec3 vecteur1 = p - xp1;

        vec3 vecteur2 = p - xp2;

        vec3 vecteur3 = p - xp3;

       /* mat3 P(AB.x(),AB.y(),AB.z(),
               AC.x(),AC.y(),AC.z(),
               n.x(),n.y(),n.z());*/

        /*mat3 P(AB.x(),AC.x(),n.x(),
               AB.y(),AC.y(),n.y(),
               AB.z(),AC.z(),n.z());

        mat3 P_inv = inverted(P);

        vec3 AM = p_inter - xp1;

        vec3 AM_prime = P_inv * AM;

        if (AM_prime.x() >= 0 && AM_prime.x() <= 1 && AM_prime.y() >= 0 && AM_prime.y() <= 1 && AM_prime.x() + AM_prime.y() <=1)
        {
            intersection.set(p_inter,n_inter,t_inter);
            return true;
        }
        */
    /*    if(dot(normal_data, cross(AB,vecteur1)) >0 &&
           dot(normal_data, cross(BC,vecteur2)) >0 &&
           dot(normal_data, cross(CA,vecteur3)) >0 )
       */
        vec3 BA = xp1 - xp2;
        vec3 CB = xp2 - xp3;
        vec3 AC = xp3 - xp1;
        vec3 vec1 = p_inter - xp1;
        vec3 vec2 = p_inter - xp2;
        vec3 vec3 = p_inter - xp3;
        if (dot(normal_data, cross(BA, vec1)) >= 0 &&
            dot(normal_data, cross(CB, vec2)) >= 0 &&
            dot(normal_data, cross(AC, vec3)) >= 0)
        {
            intersection.set(p_inter,n_inter,t_inter);
            return true;
        }
    }
    return false;


}

}
