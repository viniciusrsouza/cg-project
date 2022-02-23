#pragma once
#include <iostream>

#include "vec4.h"

class mat4
{
public:
  mat4();
  mat4(const mat4 &m);
  mat4(const float *m);
  mat4(float m00, float m10, float m20, float m30,
       float m01, float m11, float m21, float m31,
       float m02, float m12, float m22, float m32,
       float m03, float m13, float m23, float m33);
  mat4(float mi);
  ~mat4();

  mat4 &operator=(const mat4 &m);
  mat4 &operator+=(const mat4 &m);
  mat4 &operator-=(const mat4 &m);
  mat4 &operator*=(const mat4 &m);
  mat4 &operator*=(float s);
  mat4 &operator/=(float s);

  mat4 operator+(const mat4 &m) const;
  mat4 operator-(const mat4 &m) const;
  mat4 operator*(const mat4 &m) const;
  mat4 operator*(float s) const;
  mat4 operator/(float s) const;

  vec4 operator*(const vec4 &v) const;

  inline float &operator()(int i, int j);
  inline float operator()(int i, int j) const;

  float *getPtr();
  const float *getPtr() const;

  void set(float m00, float m10, float m20, float m30,
           float m01, float m11, float m21, float m31,
           float m02, float m12, float m22, float m32,
           float m03, float m13, float m23, float m33);
  void set(const float *m);
  void set(const mat4 &m);
  void set(float mi);

  void identity();
  void transpose();
  void invert();

  float determinant() const;
  mat4 inverse() const;

  friend std::ostream &operator<<(std::ostream &os, const mat4 &m);

private:
  float m[16];
};