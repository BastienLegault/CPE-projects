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

#include "cylindre.hpp"

#include "intersection_data.hpp"
#include "../scene/ray.hpp"
#include "lib/common/error_handling.hpp"

#include <cmath>

namespace cpe
{

cylindre::cylindre(vec3 const& center1_param,vec3 const& center2_param, float radius_param)
    :center1_data(center1_param),center2_data(center2_param),radius_data(radius_param)
{
    axis_data = center2_data - center1_data;
    height_data = norm(axis_data);
}

vec3 const& cylindre::center1() const
{
    return center1_data;
}
vec3 const& cylindre::center2() const
{
    return center2_data;
}
float cylindre::radius() const
{
    return radius_data;
}
float cylindre::height() const
{
    return height_data;
}
vec3 const& cylindre::axis() const
{
    return axis_data;
}



bool cylindre::intersect(ray const& ray_param,intersection_data& intersection) const
{

    vec3 const& u = ray_param.u();
    vec3 const& p0 = ray_param.p0();
    vec3 center1 = center2_data;
    vec3 center2 = center1_data;
    if (center1_data.y()<=center2_data.y())
    {
        center1 = center1_data;
        center2 = center2_data;
    }


    float const& r = radius_data;
    float const& h = height_data;
    vec3 const& axis = axis_data;


    // ********************************************************** //
    // ********************************************************** //
    //  TO DO:
    //    Calcul d'intersection entre un rayon et un cylindre
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

/*
    float pdt_a_n = dot(u,axis);
    if(pdt_a_n == 0)
        return false;//pas return false, ça signifie que le rayon est parallèe au cylindre, donc possible intersect avec les deux bases
                     //a modif
*/
    float A = (u.x()*u.x()) + (u.z()*u.z());
    float B = 2*((p0.x()-center1.x())*u.x() + (p0.z()-center1.z())*u.z());
    float C = (p0.x()-center1.x())*(p0.x()-center1.x()) + (p0.z()-center1.z())*(p0.z()-center1.z()) - r;

    float delta = B*B - 4*A*C;

    if(delta < 0)
        return false;

    if(delta==0)
    {
        float const t_inter = - B / (2*A);


        //vec3 const p_inter = ray_param(t_inter);
        vec3 const p_inter = p0 + t_inter*u;
        if ( p_inter.y()>=center1.y() && p_inter.y()<=center2.y())
        {

            vec3 const n = p_inter - vec3(center1.x(),p_inter.y(),center1.z());
            vec3 const n_inter = normalized(n);

            intersection.set(p_inter,n_inter,t_inter);

            return true;
        }

    }

    if(delta > 0)
    {
        float const t1 = - (B - sqrt(delta)) / (2*A);
        float const t2 = - (B + sqrt(delta)) / (2*A);



        float t_inter = t2;
        if(t_inter < 0)
            t_inter = t1;
        if (t_inter <0)
           return false;

        vec3 const p_inter = p0 + t_inter*u;
        if ( p_inter.y()>=center1.y() && p_inter.y()<=center2.y())
        {
            //std::cout<<p_inter.y()<<std::endl;

            vec3 const n = p_inter - vec3(center1.x(),p_inter.y(),center1.z());
            vec3 const n_inter = normalized(n);

            intersection.set(p_inter,n_inter,t_inter);

            return true;
        }
        //vec3 const p_inter = ray_param(t_inter);

    }

    return false;



}



}
