#pragma once

#include <mathlib.h>

class Shader
{
public:
  Shader();
  ~Shader();

  void Load(mat4 const &view, mat4 const &perspective, mat4 const &screen);

  virtual vec4 Vertex(vec3 const &in);
  virtual vec3 Fragment();

  mat4 view;
  mat4 perspective;
  mat4 screen;
};