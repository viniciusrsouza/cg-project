#pragma once
#include <iostream>

#include "mat3.h"
class vec3
{
public:
  vec3(float x, float y, float z);
  vec3(vec3 const &v);
  vec3();
  ~vec3();

  // operators
  vec3 &operator=(vec3 const &v);
  vec3 &operator+=(vec3 const &v);
  vec3 &operator-=(vec3 const &v);
  vec3 &operator*=(float s);
  vec3 &operator/=(float s);

  vec3 operator+(vec3 const &v) const;
  vec3 operator-(vec3 const &v) const;
  vec3 operator*(float s) const;
  vec3 operator/(float s) const;

  vec3 operator*=(mat3 const &m);
  vec3 operator*(mat3 const &m) const;

  vec3 cross(vec3 const &v) const;
  float dot(vec3 const &v) const;

  vec3 normalize() const;
  float length() const;
  float distance(vec3 const &v) const;

  void zero();

  friend std::ostream &operator<<(std::ostream &os, vec3 const &v);

  float x, y, z;
};