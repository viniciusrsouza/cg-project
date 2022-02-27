#pragma once
#include "vec3.h"

namespace Triangle
{
  float Area(vec3 const &a, vec3 const &b, vec3 const &c);
  vec3 PointAt(
      vec3 const &a, vec3 const &b, vec3 const &c,
      float x, float y, float area);
  vec3 Normal(vec3 const &a, vec3 const &b, vec3 const &c);
}