#pragma once
#include <iostream>

#include "vec3.h"

class mat3
{
public:
  mat3();
  mat3(const mat3 &m);
  mat3(const float *m);
  mat3(float m00, float m10, float m20,
       float m01, float m11, float m21,
       float m02, float m12, float m22);
  mat3(vec3 const &u, vec3 const &v, vec3 const &w);
  mat3(float mi);
  ~mat3();

  mat3 &operator=(const mat3 &m);
  mat3 &operator+=(const mat3 &m);
  mat3 &operator-=(const mat3 &m);
  mat3 &operator*=(const mat3 &m);
  mat3 &operator*=(float s);
  mat3 &operator/=(float s);

  mat3 operator+(const mat3 &m) const;
  mat3 operator-(const mat3 &m) const;
  mat3 operator*(const mat3 &m) const;
  mat3 operator*(float s) const;
  mat3 operator/(float s) const;

  vec3 operator*(const vec3 &v) const;

  inline float &operator()(int i, int j);
  inline float operator()(int i, int j) const;

  float *getPtr();
  const float *getPtr() const;

  void set(float m00, float m10, float m20,
           float m01, float m11, float m21,
           float m02, float m12, float m22);
  void set(const float *m);
  void set(const mat3 &m);
  void set(float mi);

  void identity();
  void transpose();
  void invert();

  float determinant() const;
  mat3 inverse() const;

  friend std::ostream &operator<<(std::ostream &os, const mat3 &m);

private:
  float m[9];
};