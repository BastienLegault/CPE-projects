//==============================================================================
//! \file      quaternion.h
//!
//! \author    David Odin <david.odin@forma3dev.fr>
//! \date      Created on 2009-08-01
///
//==============================================================================

#ifndef QUATERNION_H
#define QUATERNION_H

#include "vec4.h"
#include "matrix.h"

struct quaternion : vec4
{
  quaternion():vec4(0,0,0,1){}
  quaternion(const vec3 &a, float phi):vec4(a, phi){}
  quaternion(const float *m, vec3 &position);
  quaternion(const vec4 &a):vec4(a) {}
  quaternion(float x, float y, float z, float w):vec4(x,y,z,w){}

  void compute_w();
  void normalize();
  quaternion operator*(const quaternion &q) const;
  quaternion operator*(const vec3 &v) const;
  vec3 rotate(const vec3 &in) const;
  quaternion operator~() const{return quaternion(-x,-y,-z,w);}
  quaternion slerp(const quaternion &qb, float t) const;

  matrix  get_matrix() const;

  static float project_to_sphere (float r, float x, float y);
};
#endif
