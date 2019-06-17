// trackball.cc

#include <iostream>
#include <algorithm>
#include <cmath>
#include "math/vec2.h"
#include "math/vec3.h"
#include "math/quaternion.h"
#include "trackball.h"

const float TRACKBALLSIZE = 0.8f;

/*
 * Ok, simulate a track-ball.  Project the points onto the virtual
 * trackball, then figure out the axis of rotation, which is the cross
 * product of P1 P2 and O P1 (O is the center of the ball, 0,0,0)
 * Note:  This is a deformed trackball-- is a trackball in the center,
 * but is deformed into a hyperbolic sheet of rotation away from the
 * center.  This particular function was chosen after trying out
 * several variations.
 *
 * It is assumed that the arguments to this routine are in the range
 * (-1.0 ... 1.0)
 */
quaternion trackball(const vec2 &p2, const vec2 &p1)
{
  vec3 a;           // Axis of rotation.
  float phi;        // How much to rotate about axis.
  vec3 p_1(p1.x, p1.y, quaternion::project_to_sphere(TRACKBALLSIZE, p1.x, p1.y));
  vec3 p_2(p2.x, p2.y, quaternion::project_to_sphere(TRACKBALLSIZE, p2.x, p2.y));
  float t;

  if (p1.x == p2.x && p1.y == p2.y)
    return quaternion();

  a = p_1.cross(p_2);
  // Figure out how much to rotate around that axis.
  t = (p_1 - p_2).length() / (2.0 * TRACKBALLSIZE);
  t = std::min(std::max(t, -1.0f), 1.0f); // just to be sure!
  phi = 2.0 * asin(t);

  return quaternion(a.normalize()* sin(phi / 2.0), cos(phi / 2.0));
}
