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

#pragma once

#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "primitive_basic.hpp"
#include "lib/3d/vec3.hpp"
#include "lib/3d/mat3.hpp"



namespace cpe
{

class triangle : public primitive_basic
{
public:
    triangle(vec3 const& position_param1,vec3 const& position_param2,
             vec3 const& position_param3);

    /** points of the triangle */
    vec3 const& position1() const;
    vec3 const& position2() const;
    vec3 const& position3() const;

    /** Normal of the triangle */
    vec3 const& normal() const;

    /** Intersection computation with a ray */
    bool intersect(ray const& ray_param,intersection_data& intersection) const override;



private:

    /** One point belonging to the plane */
    vec3 position1_data;
    vec3 position2_data;
    vec3 position3_data;
    /** Normal of the plane */
    vec3 normal_data;

};

}
#endif // TRIANGLE_HPP
