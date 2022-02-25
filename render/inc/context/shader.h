#pragma once

#include <mathlib.h>
#include "camera.h"

class Shader
{
public:
  Shader();
  ~Shader();

  void Load(Camera *c);

  virtual vec3 Vertex(vec3 const &in);
  virtual vec3 Fragment();

  Camera *camera;
};