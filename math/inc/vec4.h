#pragma once
#include <iostream>

class vec4
{
public:
  vec4(float x, float y, float z, float w);
  vec4(vec4 const &v);
  vec4();
  ~vec4();

  // operators
  vec4 &operator=(vec4 const &v);
  vec4 &operator+=(vec4 const &v);
  vec4 &operator-=(vec4 const &v);
  vec4 &operator*=(float s);
  vec4 &operator/=(float s);

  vec4 operator+(vec4 const &v) const;
  vec4 operator-(vec4 const &v) const;
  vec4 operator*(float s) const;
  vec4 operator/(float s) const;

  // vec4 functions
  float dot(vec4 const &v) const;

  vec4 normalize() const;
  float length() const;
  float distance(vec4 const &v) const;
  vec4 project(vec4 const &v) const;

  void set(float x, float y, float z, float w);
  void set(vec4 const &v);
  void set(float s);

  void zero();

  friend std::ostream &operator<<(std::ostream &os, vec4 const &v);

  float x, y, z, w;
};