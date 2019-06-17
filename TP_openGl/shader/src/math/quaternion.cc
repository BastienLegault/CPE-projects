//==============================================================================
//! \file      quaternion.cc
//!
//! \author    David Odin <david.odin@forma3dev.fr>
//! \date      Created on 2009-08-01
///
//==============================================================================

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include "quaternion.h"

// This function build a Quaternion from a 4x4 transposed matrix (in the collada order).
// the 3x3 upper left matrix is supposed to only hold a rotation (no skew or scale).
// the postion vec3 will be filled with the last column of the 4x4 matrix.
quaternion::quaternion(const float *m, vec3 &position)
{
  float t = 1 + m[0] + m[5] + m[10];

  if (t > 0.00000001)
  {
    float s = 2 * sqrt(t);
    x = (m[9] - m[6]) / s;
    y = (m[2] - m[8]) / s;
    z = (m[4] - m[1]) / s;
    w = 0.25 * s;
  }
  else
  {
    if (m[0] > m[5] && m[0] > m[10])
    { // Column 0: 
      float s  = 2 * sqrt(1.0 + m[0] - m[5] - m[10]);
      x = 0.25 * s;
      y = (m[4] + m[1] ) / s;
      z = (m[2] + m[8] ) / s;
      w = (m[9] - m[6] ) / s;
    }
    else if (m[5] > m[10])
    { // Column 1: 
      float s  = 2 * sqrt(1.0 + m[5] - m[0] - m[10]);
      x = (m[4] + m[1] ) / s;
      y = 0.25 * s;
      z = (m[9] + m[6]) / s;
      w = (m[2] - m[8]) / s;
    }
    else
    { // Column 2:
      float s  = 2 * sqrt(1.0 + m[10] - m[0] - m[5]);
      x = (m[2] + m[8]) / s;
      y = (m[9] + m[6]) / s;
      z = 0.25 * s;
      w = (m[4] - m[1] ) / s;
    }
  }
  position = vec3(m[3], m[7], m[11]);
}

quaternion quaternion::slerp(const quaternion &q, float t) const
{
  // Check for out-of range parameter and return edge points if so.
  if (t <= 0.0)
    return *this;

  if (t >= 1.0)
    return q;

  // Compute "cosine of angle between quaternions" using dot product.
  float cosOmega = dot(q);

  /* If negative dot, use -q1.  Two quaternions q and -q
     represent the same rotation, but may produce
     different slerp.  We chose q or -q to rotate using
     the acute angle. */
  float q1w = q.w;
  float q1x = q.x;
  float q1y = q.y;
  float q1z = q.z;

  if (cosOmega < 0.0f)
    {
      q1w = -q1w;
      q1x = -q1x;
      q1y = -q1y;
      q1z = -q1z;
      cosOmega = -cosOmega;
    }

  /* Compute interpolation fraction, checking for quaternions
     almost exactly the same */
  float k0, k1;

  if (cosOmega > 0.9999f)
    {
      /* Very close - just use linear interpolation,
         which will protect againt a divide by zero */

      k0 = 1.0f - t;
      k1 = t;
    }
  else
    {
      /* Compute the sin of the angle using the
         trig identity sin^2(omega) + cos^2(omega) = 1 */
      float sinOmega = sqrt(1.0f - (cosOmega * cosOmega));

      /* Compute the angle from its sin and cosine */
      float omega = atan2 (sinOmega, cosOmega);

      /* Compute inverse of denominator, so we only have
         to divide once */
      float oneOverSinOmega = 1.0f / sinOmega;

      /* Compute interpolation parameters */
      k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
      k1 = sin(t * omega) * oneOverSinOmega;
    }

  quaternion out;
  /* Interpolate and return new quaternion */
  out.w = (k0 * w) + (k1 * q1w);
  out.x = (k0 * x) + (k1 * q1x);
  out.y = (k0 * y) + (k1 * q1y);
  out.z = (k0 * z) + (k1 * q1z);
  return out;
}

void quaternion::compute_w()
{
  float t = 1.0f - x * x - y * y - z * z;

  if (t < 0.0f)
    w = 0.0f;
  else
    w = -sqrt(t);
}

void quaternion::normalize()
{
  /* compute magnitude of the quaternion */
  float mag = sqrt(x*x + y*y + z*z + w*w);

  /* check for bogus length, to protect against divide by zero */
  if (mag > 0.0f)
    {
      /* normalize it */
      float oneOverMag = 1.0f / mag;

      x *= oneOverMag;
      y *= oneOverMag;
      z *= oneOverMag;
      w *= oneOverMag;
    }
}

quaternion quaternion::operator *(const quaternion &q) const
{
  return quaternion(
   (x * q.w) + (w * q.x) + (y * q.z) - (z * q.y),
   (y * q.w) + (w * q.y) + (z * q.x) - (x * q.z),
   (z * q.w) + (w * q.z) + (x * q.y) - (y * q.x),
   (w * q.w) - (x * q.x) - (y * q.y) - (z * q.z)
  );
}

quaternion quaternion::operator*(const vec3 &v) const
{
  return quaternion(
     (w * v.x) + (y * v.z) - (z * v.y),
     (w * v.y) + (z * v.x) - (x * v.z),
     (w * v.z) + (x * v.y) - (y * v.x),
   - (x * v.x) - (y * v.y) - (z * v.z)
  );
}

vec3 quaternion::rotate(const vec3 &in) const
{
  return ((*this)* in * ~(*this)).xyz();
}


// Project an x,y pair onto a sphere of radius r OR a hyperbolic sheet
// if we are away from the center of the sphere.
float quaternion::project_to_sphere(float r, float x, float y)
{
  float d;

  d = sqrt(x*x + y*y);
  if (d < r * 0.70710678118654752440)
    return sqrt(r*r - d*d);
  else
    return r * r / d / 2.0;
}

matrix quaternion::get_matrix() const
{
  matrix mat;

  mat.m[0 * 4 + 0] = 1.0 - 2.0 * (y * y + z * z);
  mat.m[0 * 4 + 1] =       2.0 * (x * y - z * w);
  mat.m[0 * 4 + 2] =       2.0 * (z * x + y * w);

  mat.m[1 * 4 + 0] =       2.0 * (x * y + z * w);
  mat.m[1 * 4 + 1] = 1.0 - 2.0 * (z * z + x * x);
  mat.m[1 * 4 + 2] =       2.0 * (y * z - x * w);

  mat.m[2 * 4 + 0] =       2.0 * (z * x - y * w);
  mat.m[2 * 4 + 1] =       2.0 * (y * z + x * w);
  mat.m[2 * 4 + 2] = 1.0 - 2.0 * (y * y + x * x);

  return mat;
}

