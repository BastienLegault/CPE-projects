//==============================================================================
//! \file      vec2.h
//!
//! \author    David Odin <david.odin@forma3dev.fr>
//! \date      Created on 2009-08-01
///
//==============================================================================

#ifndef VEC2_H
#define VEC2_H

#include <cmath>

struct vec2
{
  float x, y;
  vec2(float x_, float y_): x(x_),y(y_) {}
  vec2(float x_ = 0.0f) : x(x_), y(x_) {}

  vec2 operator+(const vec2&v)const{return vec2(x+v.x, y+v.y);}
  vec2 operator-(const vec2&v)const{return vec2(x-v.x, y-v.y);}
  vec2 operator*(const vec2&v)const{return vec2(x*v.x, y*v.y);}
  vec2 operator/(const vec2&v)const{return vec2(x/v.x, y/v.y);}

  vec2 operator+=(const vec2&v){x+=v.x;y+=v.y;return*this;}
  vec2 operator-=(const vec2&v){x-=v.x;y-=v.y;return*this;}
  vec2 operator*=(const vec2&v){x*=v.x;y*=v.y;return*this;}
  vec2 operator/=(const vec2&v){x/=v.x;y/=v.y;return*this;}

  vec2 operator*(float f)const{return vec2(x*f,y*f);}
  vec2 operator/(float f)const{return vec2(x/f,y/f);}
  vec2 operator*=(float f){x*=f;y*=f;return*this;}
  vec2 operator/=(float f){x/=f;y/=f;return*this;}

  float dot (const vec2&v)const{return x*v.x+y*v.y;}
  float length()const{return std::sqrt(dot(*this));}
  vec2 normalize(){float l=length(); x/=l;y/=l;return*this;}
  //
  vec2 xx()const{return vec2(x,x);}
  vec2 xy()const{return vec2(x,y);}
  vec2 yx()const{return vec2(y,x);}
  vec2 yy()const{return vec2(y,y);}
  //
  float s()const{return x;}
  float t()const{return y;}
  vec2 ss()const{return vec2(x,x);}
  vec2 st()const{return vec2(x,y);}
  vec2 ts()const{return vec2(y,x);}
  vec2 tt()const{return vec2(y,y);}
  //
  float r()const{return x;}
  float g()const{return y;}
  vec2 rr()const{return vec2(x,x);}
  vec2 rg()const{return vec2(x,y);}
  vec2 gr()const{return vec2(y,x);}
  vec2 gg()const{return vec2(y,y);}
};

static inline vec2 operator*(float s, const vec2& v){vec2 r(v); r *= s; return r;}
static inline vec2 abs(const vec2& v){return vec2(fabsf(v.x),fabsf(v.y));}
#endif
