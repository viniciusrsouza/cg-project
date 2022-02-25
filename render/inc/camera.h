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

  vec3 ToView(vec3 const &v) const;
  vec3 ToPerspective(vec3 const &v) const;
  vec3 ToScreen(vec3 const &v) const;
  void SetSize(int w, int h);

  static Camera *FromFile(std::string const &filename);
  friend std::ostream &operator<<(std::ostream &os, Camera const &c);

private:
  void Init();

  mat3 transition_matrix;
  vec3 N;
  vec3 V;
  vec3 U;
  point C;
  const float d;
  const float hx;
  const float hy;
  const float dhx;
  const float dhy;
  int width;
  int height;
};