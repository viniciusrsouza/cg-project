#pragma once

#include <mathlib.h>
#include <iostream>

// for readability only.
typedef vec3 point;

class Camera
{
public:
  Camera();
  Camera(vec3 const &N,
         vec3 const &V,
         point const &C,
         float d, float hx, float hy);
  ~Camera();

  static Camera *FromFile(std::string const &filename);

  friend std::ostream &operator<<(std::ostream &os, Camera const &c);

private:
  vec3 N;
  vec3 V;
  point C;
  float d;
  float hx;
  float hy;
};