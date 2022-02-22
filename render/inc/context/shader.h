#pragma once

#include <mathlib.h>

class Shader
{
public:
  Shader();
  ~Shader();

  virtual void Vertex(vec3 in);
  virtual vec3 Fragment();
};