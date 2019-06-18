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

#include "mesh_parametric_cloth.hpp"

#include "../lib/common/error_handling.hpp"
#include <cmath>

namespace cpe
{
vec3 mesh_parametric_cloth::calc_force(float K,float L, int xu, int xv,int ku,int kv)
{
    vec3 u0 =  vertex(ku,kv)-vertex(xu,xv);
    float L10 = norm(u0);
    //std::cout<<L10<<std::endl;
    vec3 force = K * ( L - L10) * u0/L10;
    /*float Kw = 0.005f;
    vec3 vent = Kw * dot(normal(xu, xv), vec3{1.0f ,1.0f ,0.0f}) * normal(xu, xv);
    force = force + vent;*/
    return -force;
}

void mesh_parametric_cloth::update_force()
{

    int const Nu = size_u();
    int const Nv = size_v();
    int const N_total = Nu*Nv;
    ASSERT_CPE(static_cast<int>(force_data.size()) == Nu*Nv , "Error of size");


    //Gravity
    static vec3 const g (0.0f,0.0f,-9.81f);
    vec3 const g_normalized = g/N_total;


    /*static float const mu = 0.2f;
    static float K = 7.0f;*/


    std::vector<int> coord{0, 1, 0, -1, 1, 0, -1, 0,       -1, -1, -1, 1, 1, -1, 1, 1,       0, 2, 0, -2, 2, 0, -2, 0};
    std::vector<float> K{70.0f, 8.0f, 8.0f};//K{10.0f, 8.0f, 8.0f};
    std::vector<float> L{(1.0/(size_u()-1)), std::sqrt(2.0)/(size_u()-1),(2.0/(size_u()-1))};
    for(int ku=0 ; ku<Nu ; ++ku)
    {
        for(int kv=0 ; kv<Nv ; ++kv)
        {
            force(ku,kv) = g_normalized;
            for(int i=0; i<coord.size(); i+=2)
            {
                if(ku+coord[i]>=0 && ku+coord[i]<=Nu-1 && kv+coord[i+1]>=0 && kv+coord[i+1]<=Nv-1)
                {
                    force(ku,kv) += calc_force(K[i/8], L[i/8], ku, kv, ku+coord[i],kv+coord[i+1]);
                }
            }
        }
    }
    force(0,0) = vec3(0.,0.,0.);
    force(0,Nv-1) = vec3(0.,0.,0.);

    //*************************************************************//
    // TO DO, Calculer les forces s'appliquant sur chaque sommet
    //*************************************************************//
    //
    // ...
    //
    //
    //
    //*************************************************************//


}

void mesh_parametric_cloth::integration_step(float const dt)
{
    ASSERT_CPE(speed_data.size() == force_data.size(),"Incorrect size");
    ASSERT_CPE(static_cast<int>(speed_data.size()) == size_vertex(),"Incorrect size");


    int const Nu = size_u();
    int const Nv = size_v();
    //*************************************************************//
    // TO DO: Calculer l'integration numerique des positions au cours de l'intervalle de temps dt.
    //*************************************************************//
    //
    // ...
    //
    //
    //
    //*************************************************************//

    static float const mu = 0.2f;
   // static float K = 20.0f;
    static vec3 const g (0.0f,0.0f,-9.81f);

    for(int i = 0 ; i<Nu ; i++)
    {
        for(int j = 0 ; j<Nv ; j++)
        {

            /*if(vertex(i,j).z() < -1.1f && vertex(i,j).x() > -1.0/2.0f && vertex(i,j).x() < 1.5f &&
                    vertex(i,j).y() > -1.0f && vertex(i,j).y() < 1.0f)
            {
                force(i,j).z() = 0;
                speed(i,j).z() = 0;

            }*/

            speed(i,j) = (1 - mu*dt)*speed(i,j) + dt*(force(i,j)  );
            vertex(i,j) = vertex(i,j) + dt*speed(i,j);

            /*if(norm(vertex(i,j) - vec3{0.5f,0.05f,-1.1f}) < 0.198f)
            {
                vec3 normal_sphere = vertex(i,j) - vec3{0.5f,0.05f,-1.1f};

                speed(i, j) = speed(i, j) - dot(speed(i,j),normal_sphere) * normal_sphere;
                force(i, j) = force(i, j) - dot(force(i,j),normal_sphere) * normal_sphere;
                vertex(i,j) = vec3{0.5f,0.05f,-1.1f} + 0.198f*normal_sphere/norm(normal_sphere) *1.02;

                //on glisse sur la sphere

            }*/



        }
    }


    //security check (throw exception if divergence is detected)
    static float const LIMIT=30.0f;
    for(int ku=0 ; ku<Nu ; ++ku)
    {
        for(int kv=0 ; kv<Nv ; ++kv)
        {
            vec3 const& p = vertex(ku,kv);

            if( norm(p) > LIMIT )
            {
                throw exception_divergence("Divergence of the system",EXCEPTION_PARAMETERS_CPE);
            }
        }
    }

}

void mesh_parametric_cloth::set_plane_xy_unit(int const size_u_param,int const size_v_param)
{
    mesh_parametric::set_plane_xy_unit(size_u_param,size_v_param);

    int const N = size_u()*size_v();
    speed_data.resize(N);
    force_data.resize(N);
}

vec3 const& mesh_parametric_cloth::speed(int const ku,int const kv) const
{
    ASSERT_CPE(ku >= 0 , "Value ku ("+std::to_string(ku)+") should be >=0 ");
    ASSERT_CPE(ku < size_u() , "Value ku ("+std::to_string(ku)+") should be < size_u ("+std::to_string(size_u())+")");
    ASSERT_CPE(kv >= 0 , "Value kv ("+std::to_string(kv)+") should be >=0 ");
    ASSERT_CPE(kv < size_v() , "Value kv ("+std::to_string(kv)+") should be < size_v ("+std::to_string(size_v())+")");

    int const offset = ku + size_u()*kv;

    ASSERT_CPE(offset < static_cast<int>(speed_data.size()),"Internal error");

    return speed_data[offset];
}

vec3& mesh_parametric_cloth::speed(int const ku,int const kv)
{
    ASSERT_CPE(ku >= 0 , "Value ku ("+std::to_string(ku)+") should be >=0 ");
    ASSERT_CPE(ku < size_u() , "Value ku ("+std::to_string(ku)+") should be < size_u ("+std::to_string(size_u())+")");
    ASSERT_CPE(kv >= 0 , "Value kv ("+std::to_string(kv)+") should be >=0 ");
    ASSERT_CPE(kv < size_v() , "Value kv ("+std::to_string(kv)+") should be < size_v ("+std::to_string(size_v())+")");

    int const offset = ku + size_u()*kv;

    ASSERT_CPE(offset < static_cast<int>(speed_data.size()),"Internal error");

    return speed_data[offset];
}

vec3 const& mesh_parametric_cloth::force(int const ku,int const kv) const
{
    ASSERT_CPE(ku >= 0 , "Value ku ("+std::to_string(ku)+") should be >=0 ");
    ASSERT_CPE(ku < size_u() , "Value ku ("+std::to_string(ku)+") should be < size_u ("+std::to_string(size_u())+")");
    ASSERT_CPE(kv >= 0 , "Value kv ("+std::to_string(kv)+") should be >=0 ");
    ASSERT_CPE(kv < size_v() , "Value kv ("+std::to_string(kv)+") should be < size_v ("+std::to_string(size_v())+")");

    int const offset = ku + size_u()*kv;

    ASSERT_CPE(offset < static_cast<int>(force_data.size()),"Internal error");

    return force_data[offset];
}

vec3& mesh_parametric_cloth::force(int const ku,int const kv)
{
    ASSERT_CPE(ku >= 0 , "Value ku ("+std::to_string(ku)+") should be >=0 ");
    ASSERT_CPE(ku < size_u() , "Value ku ("+std::to_string(ku)+") should be < size_u ("+std::to_string(size_u())+")");
    ASSERT_CPE(kv >= 0 , "Value kv ("+std::to_string(kv)+") should be >=0 ");
    ASSERT_CPE(kv < size_v() , "Value kv ("+std::to_string(kv)+") should be < size_v ("+std::to_string(size_v())+")");

    int const offset = ku + size_u()*kv;

    ASSERT_CPE(offset < static_cast<int>(force_data.size()),"Internal error");

    return force_data[offset];
}


}
