//==============================================================================
//! \file      matrix.cc
//!
//! \author    David Odin <david.odin@forma3dev.fr>
//! \date      Created on 2012-01-16
///
//==============================================================================

#include "matrix.h"

static matrix identity;
/******************************************************************************\
 * matrix::matrix                                                             *
\******************************************************************************/
matrix::matrix()
{
  m[ 0] = 1; m[ 1] = 0; m[ 2] = 0; m[ 3] = 0;
  m[ 4] = 0; m[ 5] = 1; m[ 6] = 0; m[ 7] = 0;
  m[ 8] = 0; m[ 9] = 0; m[10] = 1; m[11] = 0;
  m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}

/******************************************************************************\
 * matrix::matrix                                                             *
\******************************************************************************/
matrix::matrix(const float *f, bool transposed)
{
  if (transposed)
  {
    m[ 0] = f[ 0]; m[ 1] = f[ 4]; m[ 2] = f[ 8]; m[ 3] = f[12];
    m[ 4] = f[ 1]; m[ 5] = f[ 5]; m[ 6] = f[ 9]; m[ 7] = f[13];
    m[ 8] = f[ 2]; m[ 9] = f[ 6]; m[10] = f[10]; m[11] = f[14];
    m[12] = f[ 3]; m[13] = f[ 7]; m[14] = f[11]; m[15] = f[15];
  }
  else
  {
    m[ 0] = f[ 0]; m[ 1] = f[ 1]; m[ 2] = f[ 2]; m[ 3] = f[ 3];
    m[ 4] = f[ 4]; m[ 5] = f[ 5]; m[ 6] = f[ 6]; m[ 7] = f[ 7];
    m[ 8] = f[ 8]; m[ 9] = f[ 9]; m[10] = f[10]; m[11] = f[11];
    m[12] = f[12]; m[13] = f[13]; m[14] = f[14]; m[15] = f[15];
  }
}

/******************************************************************************\
 * matrix::translate                                                          *
\******************************************************************************/
void matrix::translate(const vec3 &trans)
{
  m[12] = m[0] * trans.x + m[4] * trans.y + m[8]  * trans.z + m[12];
  m[13] = m[1] * trans.x + m[5] * trans.y + m[9]  * trans.z + m[13];
  m[14] = m[2] * trans.x + m[6] * trans.y + m[10] * trans.z + m[14];
  m[15] = m[3] * trans.x + m[7] * trans.y + m[11] * trans.z + m[15];
}

/******************************************************************************\
 * matrix::scale                                                              *
\******************************************************************************/
void matrix::scale(const vec3 &factor)
{
   m[0] *= factor.x;   m[4] *= factor.y;   m[8]  *= factor.z;
   m[1] *= factor.x;   m[5] *= factor.y;   m[9]  *= factor.z;
   m[2] *= factor.x;   m[6] *= factor.y;   m[10] *= factor.z;
   m[3] *= factor.x;   m[7] *= factor.y;   m[11] *= factor.z;
}

/******************************************************************************\
 * matrix::scale                                                              *
\******************************************************************************/
void matrix::scale(float factor)
{
  scale(vec3(factor, factor, factor));
}

/******************************************************************************\
 * matrix::set_perspective                                                    *
\******************************************************************************/
void matrix::set_perspective(float fovy, float aspect, float near, float far)
{
  m[ 0] = 1.0f / tan(fovy * M_PI / 360.0f) / aspect;
  m[ 1] = 0.0f;
  m[ 2] = 0.0f;
  m[ 3] = 0.0f;

  m[ 4] = 0.0f;
  m[ 5] = 1.0f / tan(fovy * M_PI / 360.0f);
  m[ 6] = 0.0f;
  m[ 7] = 0.0f;

  m[ 8] = 0.0f;
  m[ 9] = 0.0f;
  m[10] = (far + near) / (near - far);
  m[11] = -1.0f;

  m[12] = 0.0f;
  m[13] = 0.0f;
  m[14] = 2.0f * far * near / (near - far);
  m[15] = 0.0f;
}

/******************************************************************************\
 * matrix::set_frustum                                                        *
\******************************************************************************/
void matrix::set_frustum(float left, float right, float bottom, float top, float near, float far)
{
  float A = (right+left) / (right-left);
  float B = (top+bottom) / (top-bottom);
  float C = - (far+near) / (far-near);
  float D = - 2.0f * far * near / (far - near);

  m[ 0] = 2.0f * near / (right - left);
  m[ 1] = 0.0f;
  m[ 2] = 0.0f;
  m[ 3] = 0.0f;

  m[ 4] = 0.0f;
  m[ 5] = 2.0f * near / (top - bottom);
  m[ 6] = 0.0f;
  m[ 7] = 0.0f;

  m[ 8] = A;
  m[ 9] = B;
  m[10] = C;
  m[11] = -1.0f;

  m[12] = 0.0f;
  m[13] = 0.0f;
  m[14] = D;
  m[15] = 0.0f;
}

/******************************************************************************\
 * matrix::set_ortho                                                          *
\******************************************************************************/
void matrix::set_ortho(float left, float right, float bottom, float top, float near, float far)
{
#define M(row,col)  m[col * 4 + row]
   M(0,0) = 2.0f / (right - left);
   M(0,1) = 0.0f;
   M(0,2) = 0.0f;
   M(0,3) = -(right + left) / (right - left);

   M(1,0) = 0.0f;
   M(1,1) = 2.0f / (top - bottom);
   M(1,2) = 0.0f;
   M(1,3) = -(top + bottom) / (top - bottom);

   M(2,0) = 0.0f;
   M(2,1) = 0.0f;
   M(2,2) = -2.0f / (far - near);
   M(2,3) = -(far + near) / (far - near);

   M(3,0) = 0.0f;
   M(3,1) = 0.0f;
   M(3,2) = 0.0f;
   M(3,3) = 1.0f;
#undef M
}

/******************************************************************************\
 * matrix::set_look_at                                                        *
\******************************************************************************/
void matrix::set_look_at(const vec3 &eye, const vec3 &center, const vec3 &up)
{
  vec3 f = (center - eye).normalize();
  vec3 my_up = up;
  vec3 s, u;

  my_up.normalize();
  s = f.cross(up);
  u = s.cross(f);

  matrix rotation;

  rotation.m[ 0] = s.x;
  rotation.m[ 1] = u.x;
  rotation.m[ 2] = -f.x;
  rotation.m[ 3] = 0.0f;

  rotation.m[ 4] = s.y;
  rotation.m[ 5] = u.y;
  rotation.m[ 6] = -f.y;
  rotation.m[ 7] = 0.0f;

  rotation.m[ 8] = s.z;
  rotation.m[ 9] = u.z;
  rotation.m[10] = -f.z;
  rotation.m[11] = 0.0f;

  rotation.m[12] = 0;
  rotation.m[13] = 0;
  rotation.m[14] = 0;
  rotation.m[15] = 1.0f;

  matrix translation;

  translation.m[ 0] = 1;
  translation.m[ 1] = 0;
  translation.m[ 2] = 0;
  translation.m[ 3] = 0.0f;

  translation.m[ 4] = 0;
  translation.m[ 5] = 1;
  translation.m[ 6] = 0;
  translation.m[ 7] = 0.0f;

  translation.m[ 8] = 0;
  translation.m[ 9] = 0;
  translation.m[10] = 1;
  translation.m[11] = 0.0f;

  translation.m[12] = -eye.x;
  translation.m[13] = -eye.y;
  translation.m[14] = -eye.z;
  translation.m[15] = 1.0f;

  *this = rotation * translation;
}

/******************************************************************************\
 * matrix::transform                                                          *
\******************************************************************************/
vec3 matrix::transform(const vec3 &in)
{
  return vec3(in.x * m[ 0] + in.y * m[ 4] + in.z * m[ 8] + m[12],
              in.x * m[ 1] + in.y * m[ 5] + in.z * m[ 9] + m[13],
              in.x * m[ 2] + in.y * m[ 6] + in.z * m[10] + m[14]);
}

/******************************************************************************\
 * matrix::operator*                                                          *
\******************************************************************************/
matrix matrix::operator*(const matrix &mat) const
{
  matrix result;
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
    {
      result.m[i * 4 + j] = 0.0f;
      for (int k = 0; k < 4; k++)
        result.m[i * 4 + j] += mat.m[i * 4 + k] * m[k * 4 + j];
    }
  return result;
}

/******************************************************************************\
 * matrix::rotate                                                             *
\******************************************************************************/
void matrix::rotate(float angle, const vec3 &v)
{
  float s = sin(angle * M_PI / 180.0);
  float c = cos(angle * M_PI / 180.0);
  bool optimized = false;
  float xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;
  matrix mat;

#define M(row,col)  mat.m[col*4+row]

  if (v.x == 0.0f && v.y == 0.0f && v.z == 0.0f)
    return;
  if (v.x == 0.0f)
  {
    if (v.y == 0.0f)
    {
      optimized = true  ;
      // Rotate only around z-axis.
      M(0,0) = c; M(1,1) = c;
      if (v.z < 0.0f) { M(0,1) = s; M(1,0) = -s; }
      else { M(0,1) = -s; M(1,0) = s; }
    }
    else if (v.z == 0.0f)
    {
      optimized = true;
      // Rotate only around y-axis.
      M(0,0) = c; M(2,2) = c;
      if (v.y < 0.0f) { M(0,2) = -s; M(2,0) = s; }
      else { M(0,2) = s; M(2,0) = -s; }
    }
  }
  else if (v.y == 0.0f && v.z == 0.0f)
  {
    optimized = true;
    // Rotate only around x-axis.
    M(1,1) = c; M(2,2) = c;
    if (v.x < 0.0f) { M(1,2) = s; M(2,1) = -s; }
    else { M(1,2) = -s; M(2,1) = s; }
  }

  if (!optimized)
  {
    float x = v.x / v.length();
    float y = v.y / v.length();
    float z = v.z / v.length();

    xx = x * x;
    yy = y * y;
    zz = z * z;
    xy = x * y;
    yz = y * z;
    zx = z * x;
    xs = x * s;
    ys = y * s;
    zs = z * s;
    one_c = 1.0f - c;

    /* We already hold the identity-matrix so we can skip some statements */
    M(0,0) = (one_c * xx) + c;
    M(0,1) = (one_c * xy) - zs;
    M(0,2) = (one_c * zx) + ys;
    /*    M(0,3) = 0.0F; */

    M(1,0) = (one_c * xy) + zs;
    M(1,1) = (one_c * yy) + c;
    M(1,2) = (one_c * yz) - xs;
    /*    M(1,3) = 0.0F; */

    M(2,0) = (one_c * zx) - ys;
    M(2,1) = (one_c * yz) + xs;
    M(2,2) = (one_c * zz) + c;
    /*    M(2,3) = 0.0F; */

    /*
       M(3,0) = 0.0F;
       M(3,1) = 0.0F;
       M(3,2) = 0.0F;
       M(3,3) = 1.0F;
       */
  }
#undef M

  *this = *this * mat;
}

/******************************************************************************\
 * matrix::get_nth_col                                                        *
\******************************************************************************/
vec4 matrix::get_nth_col(unsigned int n) const
{
  return vec4(m[4 * n + 0], m[4 * n + 1], m[4 * n + 2], m[4 * n + 3]);
}

/******************************************************************************\
 * matrix::get_nth_row                                                        *
\******************************************************************************/
vec4 matrix::get_nth_row(unsigned int n) const
{
  return vec4(m[0 + n], m[4 + n], m[8 + n], m[12 + n]);
}

matrix matrix::get_invert() const
{
  matrix invert;

  invert.m[ 0] =  m[ 5] * m[10] * m[15] - m[ 5] * m[11] * m[14] - m[ 9] * m[ 6] * m[15] + m[ 9] * m[ 7] * m[14] + m[13] * m[ 6] * m[11] - m[13] * m[ 7] * m[10];
  invert.m[ 1] = -m[ 1] * m[10] * m[15] + m[ 1] * m[11] * m[14] + m[ 9] * m[ 2] * m[15] - m[ 9] * m[ 3] * m[14] - m[13] * m[ 2] * m[11] + m[13] * m[ 3] * m[10];
  invert.m[ 2] =  m[ 1] * m[ 6] * m[15] - m[ 1] * m[ 7] * m[14] - m[ 5] * m[ 2] * m[15] + m[ 5] * m[ 3] * m[14] + m[13] * m[ 2] * m[ 7] - m[13] * m[ 3] * m[ 6];
  invert.m[ 3] = -m[ 1] * m[ 6] * m[11] + m[ 1] * m[ 7] * m[10] + m[ 5] * m[ 2] * m[11] - m[ 5] * m[ 3] * m[10] - m[ 9] * m[ 2] * m[ 7] + m[ 9] * m[ 3] * m[ 6];
  invert.m[ 4] = -m[ 4] * m[10] * m[15] + m[ 4] * m[11] * m[14] + m[ 8] * m[ 6] * m[15] - m[ 8] * m[ 7] * m[14] - m[12] * m[ 6] * m[11] + m[12] * m[ 7] * m[10];
  invert.m[ 5] =  m[ 0] * m[10] * m[15] - m[ 0] * m[11] * m[14] - m[ 8] * m[ 2] * m[15] + m[ 8] * m[ 3] * m[14] + m[12] * m[ 2] * m[11] - m[12] * m[ 3] * m[10];
  invert.m[ 6] = -m[ 0] * m[ 6] * m[15] + m[ 0] * m[ 7] * m[14] + m[ 4] * m[ 2] * m[15] - m[ 4] * m[ 3] * m[14] - m[12] * m[ 2] * m[ 7] + m[12] * m[ 3] * m[ 6];
  invert.m[ 7] =  m[ 0] * m[ 6] * m[11] - m[ 0] * m[ 7] * m[10] - m[ 4] * m[ 2] * m[11] + m[ 4] * m[ 3] * m[10] + m[ 8] * m[ 2] * m[ 7] - m[ 8] * m[ 3] * m[ 6];
  invert.m[ 8] =  m[ 4] * m[ 9] * m[15] - m[ 4] * m[11] * m[13] - m[ 8] * m[ 5] * m[15] + m[ 8] * m[ 7] * m[13] + m[12] * m[ 5] * m[11] - m[12] * m[ 7] * m[ 9];
  invert.m[ 9] = -m[ 0] * m[ 9] * m[15] + m[ 0] * m[11] * m[13] + m[ 8] * m[ 1] * m[15] - m[ 8] * m[ 3] * m[13] - m[12] * m[ 1] * m[11] + m[12] * m[ 3] * m[ 9];
  invert.m[10] =  m[ 0] * m[ 5] * m[15] - m[ 0] * m[ 7] * m[13] - m[ 4] * m[ 1] * m[15] + m[ 4] * m[ 3] * m[13] + m[12] * m[ 1] * m[ 7] - m[12] * m[ 3] * m[ 5];
  invert.m[11] = -m[ 0] * m[ 5] * m[11] + m[ 0] * m[ 7] * m[ 9] + m[ 4] * m[ 1] * m[11] - m[ 4] * m[ 3] * m[ 9] - m[ 8] * m[ 1] * m[ 7] + m[ 8] * m[ 3] * m[ 5];
  invert.m[12] = -m[ 4] * m[ 9] * m[14] + m[ 4] * m[10] * m[13] + m[ 8] * m[ 5] * m[14] - m[ 8] * m[ 6] * m[13] - m[12] * m[ 5] * m[10] + m[12] * m[ 6] * m[ 9];
  invert.m[13] =  m[ 0] * m[ 9] * m[14] - m[ 0] * m[10] * m[13] - m[ 8] * m[ 1] * m[14] + m[ 8] * m[ 2] * m[13] + m[12] * m[ 1] * m[10] - m[12] * m[ 2] * m[ 9];
  invert.m[14] = -m[ 0] * m[ 5] * m[14] + m[ 0] * m[ 6] * m[13] + m[ 4] * m[ 1] * m[14] - m[ 4] * m[ 2] * m[13] - m[12] * m[ 1] * m[ 6] + m[12] * m[ 2] * m[ 5];
  invert.m[15] =  m[ 0] * m[ 5] * m[10] - m[ 0] * m[ 6] * m[ 9] - m[ 4] * m[ 1] * m[10] + m[ 4] * m[ 2] * m[ 9] + m[ 8] * m[ 1] * m[ 6] - m[ 8] * m[ 2] * m[ 5];

  float det = m[0] * invert.m[0] + m[1] * invert.m[4] + m[2] * invert.m[8] + m[3] * invert.m[12];

  det = 1.0 / det;

  for (int i = 0; i < 16; i++)
    invert.m[i] *= det;

  return invert;
}
