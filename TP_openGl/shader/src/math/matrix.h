//==============================================================================
//! \file      matrix.h
//!
//! \author    David Odin <david.odin@forma3dev.fr>
//! \date      Created on 2009-08-01
///
//==============================================================================

#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>

#include "vec3.h"
#include "vec4.h"

//! 4x4 standard matrix (4 columns: 0-3 == first column)
struct matrix
{
  float m[16];
  matrix();
  matrix(const float *f, bool transposed = false);
  void translate (const vec3 &trans);
  void scale (float factor);
  void scale (const vec3 &factor);
  void rotate(float angle, const vec3 &v);
  void set_frustum(float left, float right, float bottom, float top, float near, float far);
  void set_perspective(float fovy, float aspect, float near, float far);
  void set_ortho(float left, float right, float bottom, float top, float near, float far);
  void set_look_at(const vec3 &eye, const vec3 &center, const vec3 &up);
  vec3 transform (const vec3 &in);
  matrix operator*(const matrix &mat) const;
  vec4 get_nth_col(unsigned int n) const;
  vec4 get_nth_row(unsigned int n) const;
  matrix get_invert() const;
};
#endif
