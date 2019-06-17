//==============================================================================
//! \file      vec3.h
//!
//! \author    David Odin <david.odin@forma3dev.fr>
//! \date      Created on 2009-08-01
///
//==============================================================================

#ifndef VEC3_H
#define VEC3_H

#include <cmath>

#include "vec2.h"

struct vec3
{
  float x, y, z;
  vec3 (float x_, float y_, float z_): x(x_),y(y_),z(z_) {}
  vec3 (float x_ = 0.0f) : x (x_), y (x_), z (x_) {}
  vec3 (vec2 v, float z_) : x (v.x), y (v.y), z (z_) {}
  vec3 (float x_, vec2 v) : x (x_), y (v.x), z (v.y) {}
  vec3 operator+(const vec3&v)const{return vec3(x+v.x, y+v.y, z+v.z);}
  vec3 operator-(const vec3&v)const{return vec3(x-v.x, y-v.y, z-v.z);}
  vec3 operator*(const vec3&v)const{return vec3(x*v.x, y*v.y, z*v.z);}
  vec3 operator/(const vec3&v)const{return vec3(x/v.x, y/v.y, z/v.z);}

  vec3& operator+=(const vec3&v){x+=v.x;y+=v.y;z+=v.z;return*this;}
  vec3& operator-=(const vec3&v){x-=v.x;y-=v.y;z-=v.z;return*this;}
  vec3& operator*=(const vec3&v){x*=v.x;y*=v.y;z*=v.z;return*this;}
  vec3& operator/=(const vec3&v){x/=v.x;y/=v.y;z/=v.z;return*this;}

  vec3 operator-(void)const{return vec3(-x,-y,-z);}
  vec3 operator*(float f)const{return vec3(x*f,y*f,z*f);}
  vec3 operator/(float f)const{return vec3(x/f,y/f,z/f);}

  vec3& operator*=(float f){x*=f;y*=f;z*=f;return*this;}
  vec3& operator/=(float f){x/=f;y/=f;z/=f;return*this;}

  float dot (const vec3&v)const{return x*v.x+y*v.y+z*v.z;}
  //float length (void)const{if (dot(*this)<0.001)return 1;return std::sqrt(dot(*this));}
  float length (void)const{return std::sqrt(dot(*this));}
  vec3& normalize (void){float l=length();x/=l;y/=l;z/=l;return*this;}
  //vec3& normalize (void){float l=length();if(l<0.001f){*this=vec3(0,0,0);return*this;}x/=l;y/=l;z/=l;return*this;}

  vec3 cross(const vec3&v)const{return vec3(y*v.z-z*v.y,z*v.x-x*v.z,x*v.y-y*v.x);}
  vec3 operator^(const vec3&v)const{return vec3(y*v.z-z*v.y,z*v.x-x*v.z,x*v.y-y*v.x);}
  //
  vec2 xx()const{return vec2(x,x);}
  vec2 xy()const{return vec2(x,y);}
  vec2 xz()const{return vec2(x,z);}
  vec2 yx()const{return vec2(y,x);}
  vec2 yy()const{return vec2(y,y);}
  vec2 yz()const{return vec2(y,z);}
  vec2 zx()const{return vec2(z,x);}
  vec2 zy()const{return vec2(z,y);}
  vec2 zz()const{return vec2(z,z);}
  vec3 xxx()const{return vec3(x,x,x);}
  vec3 xxy()const{return vec3(x,x,y);}
  vec3 xxz()const{return vec3(x,x,z);}
  vec3 xyx()const{return vec3(x,y,x);}
  vec3 xyy()const{return vec3(x,y,y);}
  vec3 xyz()const{return vec3(x,y,z);}
  vec3 xzx()const{return vec3(x,z,x);}
  vec3 xzy()const{return vec3(x,z,y);}
  vec3 xzz()const{return vec3(x,z,z);}
  vec3 yxx()const{return vec3(y,x,x);}
  vec3 yxy()const{return vec3(y,x,y);}
  vec3 yxz()const{return vec3(y,x,z);}
  vec3 yyx()const{return vec3(y,y,x);}
  vec3 yyy()const{return vec3(y,y,y);}
  vec3 yyz()const{return vec3(y,y,z);}
  vec3 yzx()const{return vec3(y,z,x);}
  vec3 yzy()const{return vec3(y,z,y);}
  vec3 yzz()const{return vec3(y,z,z);}
  vec3 zxx()const{return vec3(z,x,x);}
  vec3 zxy()const{return vec3(z,x,y);}
  vec3 zxz()const{return vec3(z,x,z);}
  vec3 zyx()const{return vec3(z,y,x);}
  vec3 zyy()const{return vec3(z,y,y);}
  vec3 zyz()const{return vec3(z,y,z);}
  vec3 zzx()const{return vec3(z,z,x);}
  vec3 zzy()const{return vec3(z,z,y);}
  vec3 zzz()const{return vec3(z,z,z);}
  //
  float r()const{return x;}
  float g()const{return y;}
  float b()const{return z;}
  vec2 rr()const{return vec2(x,x);}
  vec2 rg()const{return vec2(x,y);}
  vec2 rb()const{return vec2(x,z);}
  vec2 gr()const{return vec2(y,x);}
  vec2 gg()const{return vec2(y,y);}
  vec2 gb()const{return vec2(y,z);}
  vec2 br()const{return vec2(z,x);}
  vec2 bg()const{return vec2(z,y);}
  vec2 bb()const{return vec2(z,z);}
  vec3 rrr()const{return vec3(x,x,x);}
  vec3 rrg()const{return vec3(x,x,y);}
  vec3 rrb()const{return vec3(x,x,z);}
  vec3 rgr()const{return vec3(x,y,x);}
  vec3 rgg()const{return vec3(x,y,y);}
  vec3 rgb()const{return vec3(x,y,z);}
  vec3 rbr()const{return vec3(x,z,x);}
  vec3 rbg()const{return vec3(x,z,y);}
  vec3 rbb()const{return vec3(x,z,z);}
  vec3 grr()const{return vec3(y,x,x);}
  vec3 grg()const{return vec3(y,x,y);}
  vec3 grb()const{return vec3(y,x,z);}
  vec3 ggr()const{return vec3(y,y,x);}
  vec3 ggg()const{return vec3(y,y,y);}
  vec3 ggb()const{return vec3(y,y,z);}
  vec3 gbr()const{return vec3(y,z,x);}
  vec3 gbg()const{return vec3(y,z,y);}
  vec3 gbb()const{return vec3(y,z,z);}
  vec3 brr()const{return vec3(z,x,x);}
  vec3 brg()const{return vec3(z,x,y);}
  vec3 brb()const{return vec3(z,x,z);}
  vec3 bgr()const{return vec3(z,y,x);}
  vec3 bgg()const{return vec3(z,y,y);}
  vec3 bgb()const{return vec3(z,y,z);}
  vec3 bbr()const{return vec3(z,z,x);}
  vec3 bbg()const{return vec3(z,z,y);}
  vec3 bbb()const{return vec3(z,z,z);}
  //
  float s()const{return x;}
  float t()const{return y;}
  float p()const{return z;}
  vec2 ss()const{return vec2(x,x);}
  vec2 st()const{return vec2(x,y);}
  vec2 sp()const{return vec2(x,z);}
  vec2 ts()const{return vec2(y,x);}
  vec2 tt()const{return vec2(y,y);}
  vec2 tp()const{return vec2(y,z);}
  vec2 ps()const{return vec2(z,x);}
  vec2 pt()const{return vec2(z,y);}
  vec2 pp()const{return vec2(z,z);}
  vec3 sss()const{return vec3(x,x,x);}
  vec3 sst()const{return vec3(x,x,y);}
  vec3 ssp()const{return vec3(x,x,z);}
  vec3 sts()const{return vec3(x,y,x);}
  vec3 stt()const{return vec3(x,y,y);}
  vec3 stp()const{return vec3(x,y,z);}
  vec3 sps()const{return vec3(x,z,x);}
  vec3 spt()const{return vec3(x,z,y);}
  vec3 spp()const{return vec3(x,z,z);}
  vec3 tss()const{return vec3(y,x,x);}
  vec3 tst()const{return vec3(y,x,y);}
  vec3 tsp()const{return vec3(y,x,z);}
  vec3 tts()const{return vec3(y,y,x);}
  vec3 ttt()const{return vec3(y,y,y);}
  vec3 ttp()const{return vec3(y,y,z);}
  vec3 tps()const{return vec3(y,z,x);}
  vec3 tpt()const{return vec3(y,z,y);}
  vec3 tpp()const{return vec3(y,z,z);}
  vec3 pss()const{return vec3(z,x,x);}
  vec3 pst()const{return vec3(z,x,y);}
  vec3 psp()const{return vec3(z,x,z);}
  vec3 pts()const{return vec3(z,y,x);}
  vec3 ptt()const{return vec3(z,y,y);}
  vec3 ptp()const{return vec3(z,y,z);}
  vec3 pps()const{return vec3(z,z,x);}
  vec3 ppt()const{return vec3(z,z,y);}
  vec3 ppp()const{return vec3(z,z,z);}
};

static inline vec3 operator*(float s, const vec3& v){vec3 r(v); r *= s; return r;}
static inline vec3 abs(const vec3& v){return vec3(fabsf(v.x),fabsf(v.y),fabsf(v.z));}

#endif
