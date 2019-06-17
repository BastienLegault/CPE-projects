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

#ifndef CYLINDRE_HPP
#define CYLINDRE_HPP

#include "primitive_basic.hpp"
#include "lib/3d/vec3.hpp"

namespace cpe
{


class cylindre : public primitive_basic
{
public:
    cylindre(vec3 const& center1_param, vec3 const& center2_param, float radius_param);

    /** Center of one side */
    vec3 const& center1() const;
    /** Center of the other side */
    vec3 const& center2() const;
    /** Radius of the sphere */
    float radius() const;
    /** Height of the sphere */
    float height() const;
    /** axis of the cylindre */
    vec3 const& axis() const;

    /** Intersection computation with a ray */
    bool intersect(ray const& ray_param,intersection_data& intersection) const override;

private:

    /** Center of one side */
    vec3 center1_data;
    /** Center of the other side */
    vec3 center2_data;
    /** Radius of the sphere */
    float radius_data;
    /** Height of the sphere */
    float height_data;
    /** Axis of the cylindre */
    vec3 axis_data;

};

#endif // CYLINDRE_HPP



}




