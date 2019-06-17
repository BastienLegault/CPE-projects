//==============================================================================
//! \file      vec4.h
//!
//! \author    David Odin <david.odin@forma3dev.fr>
//! \date      Created on 2009-08-01
///
//==============================================================================

#ifndef VEC4_H
#define VEC4_H

#include <cmath>

#include "vec3.h"

struct vec4
{
  float x, y, z, w;
  vec4(float x_, float y_, float z_, float w_): x(x_),y(y_),z(z_),w(w_) {}
  vec4(float x_, float y_, float z_) : x (x_), y (y_), z (z_), w (1.0f) {}
  vec4(float x_=0.0f) : x (x_), y (x_), z (x_), w (x_) {}
  vec4(vec2 v1, vec2 v2) : x (v1.x), y (v1.y), z (v2.x), w (v2.y) {}
  vec4(vec2 v, float z_, float w_) : x (v.x), y (v.y), z (z_), w (w_) {}
  vec4(float x_, vec2 v, float w_) : x (x_), y (v.x), z (v.y), w (w_) {}
  vec4(float x_, float y_, vec2 v) : x (x_), y (y_), z (v.x), w (v.y) {}
  vec4(vec3 v, float w_) : x (v.x), y (v.y), z (v.z), w (w_) {}
  vec4(float x_, vec3 v) : x (x_), y (v.x), z (v.y), w (v.z) {}

  vec4 operator+(const vec4&v)const{return vec4(x+v.x, y+v.y, z+v.z, w+v.w);}
  vec4 operator-(const vec4&v)const{return vec4(x-v.x, y-v.y, z-v.z, w-v.w);}
  vec4 operator-()const{return vec4(-x, -y, -z, -w);}
  vec4 operator*(const vec4&v)const{return vec4(x*v.x, y*v.y, z*v.z, w*v.w);}
  vec4 operator*(float f)const{return vec4(x*f,y*f,z*f,w*f);}
  vec4 operator/(float f)const{return vec4(x/f,y/f,z/f,w/f);}
  //  vec3& operator*=(float f){x*=f;y*=f;z*=f;return*this;}
  //  vec3& normalize (void){float l=std::sqrt(x*x+y*y+z*z);x/=l;y/=l;z/=l;return*this;}
  //  vec3& operator+=(const vec3&v){x+=v.x;y+=v.y;z+=v.z;return*this;}
  //  vec3& operator-=(const vec3&v){x-=v.x;y-=v.y;z-=v.z;return*this;}
  float dot(const vec4&v)const{return x*v.x+y*v.y+z*v.z+w*v.w;}
  float length(void)const{return std::sqrt(dot(*this));}
  void semi_normalize(){float f=xyz().length();x/=f;y/=f;z/=f;w/=f;}
  //
  vec2 xx()const{return vec2(x,x);}
  vec2 xy()const{return vec2(x,y);}
  vec2 xz()const{return vec2(x,z);}
  vec2 xw()const{return vec2(x,w);}
  vec2 yx()const{return vec2(y,x);}
  vec2 yy()const{return vec2(y,y);}
  vec2 yz()const{return vec2(y,z);}
  vec2 yw()const{return vec2(y,w);}
  vec2 zx()const{return vec2(z,x);}
  vec2 zy()const{return vec2(z,y);}
  vec2 zz()const{return vec2(z,z);}
  vec2 zw()const{return vec2(z,w);}
  vec2 wx()const{return vec2(w,x);}
  vec2 wy()const{return vec2(w,y);}
  vec2 wz()const{return vec2(w,z);}
  vec2 ww()const{return vec2(w,w);}
  vec3 xxx()const{return vec3(x,x,x);}
  vec3 xxy()const{return vec3(x,x,y);}
  vec3 xxz()const{return vec3(x,x,z);}
  vec3 xxw()const{return vec3(x,x,w);}
  vec3 xyx()const{return vec3(x,y,x);}
  vec3 xyy()const{return vec3(x,y,y);}
  vec3 xyz()const{return vec3(x,y,z);}
  vec3 xyw()const{return vec3(x,y,w);}
  vec3 xzx()const{return vec3(x,z,x);}
  vec3 xzy()const{return vec3(x,z,y);}
  vec3 xzz()const{return vec3(x,z,z);}
  vec3 xzw()const{return vec3(x,z,w);}
  vec3 xwx()const{return vec3(x,w,x);}
  vec3 xwy()const{return vec3(x,w,y);}
  vec3 xwz()const{return vec3(x,w,z);}
  vec3 xww()const{return vec3(x,w,w);}
  vec3 yxx()const{return vec3(y,x,x);}
  vec3 yxy()const{return vec3(y,x,y);}
  vec3 yxz()const{return vec3(y,x,z);}
  vec3 yxw()const{return vec3(y,x,w);}
  vec3 yyx()const{return vec3(y,y,x);}
  vec3 yyy()const{return vec3(y,y,y);}
  vec3 yyz()const{return vec3(y,y,z);}
  vec3 yyw()const{return vec3(y,y,w);}
  vec3 yzx()const{return vec3(y,z,x);}
  vec3 yzy()const{return vec3(y,z,y);}
  vec3 yzz()const{return vec3(y,z,z);}
  vec3 yzw()const{return vec3(y,z,w);}
  vec3 ywx()const{return vec3(y,w,x);}
  vec3 ywy()const{return vec3(y,w,y);}
  vec3 ywz()const{return vec3(y,w,z);}
  vec3 yww()const{return vec3(y,w,w);}
  vec3 zxx()const{return vec3(z,x,x);}
  vec3 zxy()const{return vec3(z,x,y);}
  vec3 zxz()const{return vec3(z,x,z);}
  vec3 zxw()const{return vec3(z,x,w);}
  vec3 zyx()const{return vec3(z,y,x);}
  vec3 zyy()const{return vec3(z,y,y);}
  vec3 zyz()const{return vec3(z,y,z);}
  vec3 zyw()const{return vec3(z,y,w);}
  vec3 zzx()const{return vec3(z,z,x);}
  vec3 zzy()const{return vec3(z,z,y);}
  vec3 zzz()const{return vec3(z,z,z);}
  vec3 zzw()const{return vec3(z,z,w);}
  vec3 zwx()const{return vec3(z,w,x);}
  vec3 zwy()const{return vec3(z,w,y);}
  vec3 zwz()const{return vec3(z,w,z);}
  vec3 zww()const{return vec3(z,w,w);}
  vec3 wxx()const{return vec3(w,x,x);}
  vec3 wxy()const{return vec3(w,x,y);}
  vec3 wxz()const{return vec3(w,x,z);}
  vec3 wxw()const{return vec3(w,x,w);}
  vec3 wyx()const{return vec3(w,y,x);}
  vec3 wyy()const{return vec3(w,y,y);}
  vec3 wyz()const{return vec3(w,y,z);}
  vec3 wyw()const{return vec3(w,y,w);}
  vec3 wzx()const{return vec3(w,z,x);}
  vec3 wzy()const{return vec3(w,z,y);}
  vec3 wzz()const{return vec3(w,z,z);}
  vec3 wzw()const{return vec3(w,z,w);}
  vec3 wwx()const{return vec3(w,w,x);}
  vec3 wwy()const{return vec3(w,w,y);}
  vec3 wwz()const{return vec3(w,w,z);}
  vec3 www()const{return vec3(w,w,w);}

  vec4 xxxx()const{return vec4(x,x,x,x);}
  vec4 xxxy()const{return vec4(x,x,x,y);}
  vec4 xxxz()const{return vec4(x,x,x,z);}
  vec4 xxxw()const{return vec4(x,x,x,w);}
  vec4 xxyx()const{return vec4(x,x,y,x);}
  vec4 xxyy()const{return vec4(x,x,y,y);}
  vec4 xxyz()const{return vec4(x,x,y,z);}
  vec4 xxyw()const{return vec4(x,x,y,w);}
  vec4 xxzx()const{return vec4(x,x,z,x);}
  vec4 xxzy()const{return vec4(x,x,z,y);}
  vec4 xxzz()const{return vec4(x,x,z,z);}
  vec4 xxzw()const{return vec4(x,x,z,w);}
  vec4 xxwx()const{return vec4(x,x,w,x);}
  vec4 xxwy()const{return vec4(x,x,w,y);}
  vec4 xxwz()const{return vec4(x,x,w,z);}
  vec4 xxww()const{return vec4(x,x,w,w);}
  vec4 xyxx()const{return vec4(x,y,x,x);}
  vec4 xyxy()const{return vec4(x,y,x,y);}
  vec4 xyxz()const{return vec4(x,y,x,z);}
  vec4 xyxw()const{return vec4(x,y,x,w);}
  vec4 xyyx()const{return vec4(x,y,y,x);}
  vec4 xyyy()const{return vec4(x,y,y,y);}
  vec4 xyyz()const{return vec4(x,y,y,z);}
  vec4 xyyw()const{return vec4(x,y,y,w);}
  vec4 xyzx()const{return vec4(x,y,z,x);}
  vec4 xyzy()const{return vec4(x,y,z,y);}
  vec4 xyzz()const{return vec4(x,y,z,z);}
  vec4 xyzw()const{return vec4(x,y,z,w);}
  vec4 xywx()const{return vec4(x,y,w,x);}
  vec4 xywy()const{return vec4(x,y,w,y);}
  vec4 xywz()const{return vec4(x,y,w,z);}
  vec4 xyww()const{return vec4(x,y,w,w);}
  vec4 xzxx()const{return vec4(x,z,x,x);}
  vec4 xzxy()const{return vec4(x,z,x,y);}
  vec4 xzxz()const{return vec4(x,z,x,z);}
  vec4 xzxw()const{return vec4(x,z,x,w);}
  vec4 xzyx()const{return vec4(x,z,y,x);}
  vec4 xzyy()const{return vec4(x,z,y,y);}
  vec4 xzyz()const{return vec4(x,z,y,z);}
  vec4 xzyw()const{return vec4(x,z,y,w);}
  vec4 xzzx()const{return vec4(x,z,z,x);}
  vec4 xzzy()const{return vec4(x,z,z,y);}
  vec4 xzzz()const{return vec4(x,z,z,z);}
  vec4 xzzw()const{return vec4(x,z,z,w);}
  vec4 xzwx()const{return vec4(x,z,w,x);}
  vec4 xzwy()const{return vec4(x,z,w,y);}
  vec4 xzwz()const{return vec4(x,z,w,z);}
  vec4 xzww()const{return vec4(x,z,w,w);}
  vec4 xwxx()const{return vec4(x,w,x,x);}
  vec4 xwxy()const{return vec4(x,w,x,y);}
  vec4 xwxz()const{return vec4(x,w,x,z);}
  vec4 xwxw()const{return vec4(x,w,x,w);}
  vec4 xwyx()const{return vec4(x,w,y,x);}
  vec4 xwyy()const{return vec4(x,w,y,y);}
  vec4 xwyz()const{return vec4(x,w,y,z);}
  vec4 xwyw()const{return vec4(x,w,y,w);}
  vec4 xwzx()const{return vec4(x,w,z,x);}
  vec4 xwzy()const{return vec4(x,w,z,y);}
  vec4 xwzz()const{return vec4(x,w,z,z);}
  vec4 xwzw()const{return vec4(x,w,z,w);}
  vec4 xwwx()const{return vec4(x,w,w,x);}
  vec4 xwwy()const{return vec4(x,w,w,y);}
  vec4 xwwz()const{return vec4(x,w,w,z);}
  vec4 xwww()const{return vec4(x,w,w,w);}

  vec4 yxxx()const{return vec4(y,x,x,x);}
  vec4 yxxy()const{return vec4(y,x,x,y);}
  vec4 yxxz()const{return vec4(y,x,x,z);}
  vec4 yxxw()const{return vec4(y,x,x,w);}
  vec4 yxyx()const{return vec4(y,x,y,x);}
  vec4 yxyy()const{return vec4(y,x,y,y);}
  vec4 yxyz()const{return vec4(y,x,y,z);}
  vec4 yxyw()const{return vec4(y,x,y,w);}
  vec4 yxzx()const{return vec4(y,x,z,x);}
  vec4 yxzy()const{return vec4(y,x,z,y);}
  vec4 yxzz()const{return vec4(y,x,z,z);}
  vec4 yxzw()const{return vec4(y,x,z,w);}
  vec4 yxwx()const{return vec4(y,x,w,x);}
  vec4 yxwy()const{return vec4(y,x,w,y);}
  vec4 yxwz()const{return vec4(y,x,w,z);}
  vec4 yxww()const{return vec4(y,x,w,w);}
  vec4 yyxx()const{return vec4(y,y,x,x);}
  vec4 yyxy()const{return vec4(y,y,x,y);}
  vec4 yyxz()const{return vec4(y,y,x,z);}
  vec4 yyxw()const{return vec4(y,y,x,w);}
  vec4 yyyx()const{return vec4(y,y,y,x);}
  vec4 yyyy()const{return vec4(y,y,y,y);}
  vec4 yyyz()const{return vec4(y,y,y,z);}
  vec4 yyyw()const{return vec4(y,y,y,w);}
  vec4 yyzx()const{return vec4(y,y,z,x);}
  vec4 yyzy()const{return vec4(y,y,z,y);}
  vec4 yyzz()const{return vec4(y,y,z,z);}
  vec4 yyzw()const{return vec4(y,y,z,w);}
  vec4 yywx()const{return vec4(y,y,w,x);}
  vec4 yywy()const{return vec4(y,y,w,y);}
  vec4 yywz()const{return vec4(y,y,w,z);}
  vec4 yyww()const{return vec4(y,y,w,w);}
  vec4 yzxx()const{return vec4(y,z,x,x);}
  vec4 yzxy()const{return vec4(y,z,x,y);}
  vec4 yzxz()const{return vec4(y,z,x,z);}
  vec4 yzxw()const{return vec4(y,z,x,w);}
  vec4 yzyx()const{return vec4(y,z,y,x);}
  vec4 yzyy()const{return vec4(y,z,y,y);}
  vec4 yzyz()const{return vec4(y,z,y,z);}
  vec4 yzyw()const{return vec4(y,z,y,w);}
  vec4 yzzx()const{return vec4(y,z,z,x);}
  vec4 yzzy()const{return vec4(y,z,z,y);}
  vec4 yzzz()const{return vec4(y,z,z,z);}
  vec4 yzzw()const{return vec4(y,z,z,w);}
  vec4 yzwx()const{return vec4(y,z,w,x);}
  vec4 yzwy()const{return vec4(y,z,w,y);}
  vec4 yzwz()const{return vec4(y,z,w,z);}
  vec4 yzww()const{return vec4(y,z,w,w);}
  vec4 ywxx()const{return vec4(y,w,x,x);}
  vec4 ywxy()const{return vec4(y,w,x,y);}
  vec4 ywxz()const{return vec4(y,w,x,z);}
  vec4 ywxw()const{return vec4(y,w,x,w);}
  vec4 ywyx()const{return vec4(y,w,y,x);}
  vec4 ywyy()const{return vec4(y,w,y,y);}
  vec4 ywyz()const{return vec4(y,w,y,z);}
  vec4 ywyw()const{return vec4(y,w,y,w);}
  vec4 ywzx()const{return vec4(y,w,z,x);}
  vec4 ywzy()const{return vec4(y,w,z,y);}
  vec4 ywzz()const{return vec4(y,w,z,z);}
  vec4 ywzw()const{return vec4(y,w,z,w);}
  vec4 ywwx()const{return vec4(y,w,w,x);}
  vec4 ywwy()const{return vec4(y,w,w,y);}
  vec4 ywwz()const{return vec4(y,w,w,z);}
  vec4 ywww()const{return vec4(y,w,w,w);}

  vec4 zxxx()const{return vec4(z,x,x,x);}
  vec4 zxxy()const{return vec4(z,x,x,y);}
  vec4 zxxz()const{return vec4(z,x,x,z);}
  vec4 zxxw()const{return vec4(z,x,x,w);}
  vec4 zxyx()const{return vec4(z,x,y,x);}
  vec4 zxyy()const{return vec4(z,x,y,y);}
  vec4 zxyz()const{return vec4(z,x,y,z);}
  vec4 zxyw()const{return vec4(z,x,y,w);}
  vec4 zxzx()const{return vec4(z,x,z,x);}
  vec4 zxzy()const{return vec4(z,x,z,y);}
  vec4 zxzz()const{return vec4(z,x,z,z);}
  vec4 zxzw()const{return vec4(z,x,z,w);}
  vec4 zxwx()const{return vec4(z,x,w,x);}
  vec4 zxwy()const{return vec4(z,x,w,y);}
  vec4 zxwz()const{return vec4(z,x,w,z);}
  vec4 zxww()const{return vec4(z,x,w,w);}
  vec4 zyxx()const{return vec4(z,y,x,x);}
  vec4 zyxy()const{return vec4(z,y,x,y);}
  vec4 zyxz()const{return vec4(z,y,x,z);}
  vec4 zyxw()const{return vec4(z,y,x,w);}
  vec4 zyyx()const{return vec4(z,y,y,x);}
  vec4 zyyy()const{return vec4(z,y,y,y);}
  vec4 zyyz()const{return vec4(z,y,y,z);}
  vec4 zyyw()const{return vec4(z,y,y,w);}
  vec4 zyzx()const{return vec4(z,y,z,x);}
  vec4 zyzy()const{return vec4(z,y,z,y);}
  vec4 zyzz()const{return vec4(z,y,z,z);}
  vec4 zyzw()const{return vec4(z,y,z,w);}
  vec4 zywx()const{return vec4(z,y,w,x);}
  vec4 zywy()const{return vec4(z,y,w,y);}
  vec4 zywz()const{return vec4(z,y,w,z);}
  vec4 zyww()const{return vec4(z,y,w,w);}
  vec4 zzxx()const{return vec4(z,z,x,x);}
  vec4 zzxy()const{return vec4(z,z,x,y);}
  vec4 zzxz()const{return vec4(z,z,x,z);}
  vec4 zzxw()const{return vec4(z,z,x,w);}
  vec4 zzyx()const{return vec4(z,z,y,x);}
  vec4 zzyy()const{return vec4(z,z,y,y);}
  vec4 zzyz()const{return vec4(z,z,y,z);}
  vec4 zzyw()const{return vec4(z,z,y,w);}
  vec4 zzzx()const{return vec4(z,z,z,x);}
  vec4 zzzy()const{return vec4(z,z,z,y);}
  vec4 zzzz()const{return vec4(z,z,z,z);}
  vec4 zzzw()const{return vec4(z,z,z,w);}
  vec4 zzwx()const{return vec4(z,z,w,x);}
  vec4 zzwy()const{return vec4(z,z,w,y);}
  vec4 zzwz()const{return vec4(z,z,w,z);}
  vec4 zzww()const{return vec4(z,z,w,w);}
  vec4 zwxx()const{return vec4(z,w,x,x);}
  vec4 zwxy()const{return vec4(z,w,x,y);}
  vec4 zwxz()const{return vec4(z,w,x,z);}
  vec4 zwxw()const{return vec4(z,w,x,w);}
  vec4 zwyx()const{return vec4(z,w,y,x);}
  vec4 zwyy()const{return vec4(z,w,y,y);}
  vec4 zwyz()const{return vec4(z,w,y,z);}
  vec4 zwyw()const{return vec4(z,w,y,w);}
  vec4 zwzx()const{return vec4(z,w,z,x);}
  vec4 zwzy()const{return vec4(z,w,z,y);}
  vec4 zwzz()const{return vec4(z,w,z,z);}
  vec4 zwzw()const{return vec4(z,w,z,w);}
  vec4 zwwx()const{return vec4(z,w,w,x);}
  vec4 zwwy()const{return vec4(z,w,w,y);}
  vec4 zwwz()const{return vec4(z,w,w,z);}
  vec4 zwww()const{return vec4(z,w,w,w);}

  vec4 wxxx()const{return vec4(w,x,x,x);}
  vec4 wxxy()const{return vec4(w,x,x,y);}
  vec4 wxxz()const{return vec4(w,x,x,z);}
  vec4 wxxw()const{return vec4(w,x,x,w);}
  vec4 wxyx()const{return vec4(w,x,y,x);}
  vec4 wxyy()const{return vec4(w,x,y,y);}
  vec4 wxyz()const{return vec4(w,x,y,z);}
  vec4 wxyw()const{return vec4(w,x,y,w);}
  vec4 wxzx()const{return vec4(w,x,z,x);}
  vec4 wxzy()const{return vec4(w,x,z,y);}
  vec4 wxzz()const{return vec4(w,x,z,z);}
  vec4 wxzw()const{return vec4(w,x,z,w);}
  vec4 wxwx()const{return vec4(w,x,w,x);}
  vec4 wxwy()const{return vec4(w,x,w,y);}
  vec4 wxwz()const{return vec4(w,x,w,z);}
  vec4 wxww()const{return vec4(w,x,w,w);}
  vec4 wyxx()const{return vec4(w,y,x,x);}
  vec4 wyxy()const{return vec4(w,y,x,y);}
  vec4 wyxz()const{return vec4(w,y,x,z);}
  vec4 wyxw()const{return vec4(w,y,x,w);}
  vec4 wyyx()const{return vec4(w,y,y,x);}
  vec4 wyyy()const{return vec4(w,y,y,y);}
  vec4 wyyz()const{return vec4(w,y,y,z);}
  vec4 wyyw()const{return vec4(w,y,y,w);}
  vec4 wyzx()const{return vec4(w,y,z,x);}
  vec4 wyzy()const{return vec4(w,y,z,y);}
  vec4 wyzz()const{return vec4(w,y,z,z);}
  vec4 wyzw()const{return vec4(w,y,z,w);}
  vec4 wywx()const{return vec4(w,y,w,x);}
  vec4 wywy()const{return vec4(w,y,w,y);}
  vec4 wywz()const{return vec4(w,y,w,z);}
  vec4 wyww()const{return vec4(w,y,w,w);}
  vec4 wzxx()const{return vec4(w,z,x,x);}
  vec4 wzxy()const{return vec4(w,z,x,y);}
  vec4 wzxz()const{return vec4(w,z,x,z);}
  vec4 wzxw()const{return vec4(w,z,x,w);}
  vec4 wzyx()const{return vec4(w,z,y,x);}
  vec4 wzyy()const{return vec4(w,z,y,y);}
  vec4 wzyz()const{return vec4(w,z,y,z);}
  vec4 wzyw()const{return vec4(w,z,y,w);}
  vec4 wzzx()const{return vec4(w,z,z,x);}
  vec4 wzzy()const{return vec4(w,z,z,y);}
  vec4 wzzz()const{return vec4(w,z,z,z);}
  vec4 wzzw()const{return vec4(w,z,z,w);}
  vec4 wzwx()const{return vec4(w,z,w,x);}
  vec4 wzwy()const{return vec4(w,z,w,y);}
  vec4 wzwz()const{return vec4(w,z,w,z);}
  vec4 wzww()const{return vec4(w,z,w,w);}
  vec4 wwxx()const{return vec4(w,w,x,x);}
  vec4 wwxy()const{return vec4(w,w,x,y);}
  vec4 wwxz()const{return vec4(w,w,x,z);}
  vec4 wwxw()const{return vec4(w,w,x,w);}
  vec4 wwyx()const{return vec4(w,w,y,x);}
  vec4 wwyy()const{return vec4(w,w,y,y);}
  vec4 wwyz()const{return vec4(w,w,y,z);}
  vec4 wwyw()const{return vec4(w,w,y,w);}
  vec4 wwzx()const{return vec4(w,w,z,x);}
  vec4 wwzy()const{return vec4(w,w,z,y);}
  vec4 wwzz()const{return vec4(w,w,z,z);}
  vec4 wwzw()const{return vec4(w,w,z,w);}
  vec4 wwwx()const{return vec4(w,w,w,x);}
  vec4 wwwy()const{return vec4(w,w,w,y);}
  vec4 wwwz()const{return vec4(w,w,w,z);}
  vec4 wwww()const{return vec4(w,w,w,w);}
};

//static inline vec3 operator*(float s, const vec3& v){vec3 r(v); r *= s; return r;}
static inline vec4 abs(const vec4& v){return vec4(fabsf(v.x),fabsf(v.y),fabsf(v.z),fabsf(v.w));}
#endif
