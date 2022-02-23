#pragma once
#include <iostream>

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

  // vec3 functions
  vec3 cross(vec3 const &v) const;
  float dot(vec3 const &v) const;

  vec3 normalize() const;
  float length() const;
  float distance(vec3 const &v) const;
  vec3 project(vec3 const &v) const;

  void set(float x, float y, float z);
  void set(vec3 const &v);
  void set(float s);

  void zero();

  friend std::ostream &operator<<(std::ostream &os, vec3 const &v);

  float x, y, z;
};