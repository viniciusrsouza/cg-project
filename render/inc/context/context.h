#pragma once

#include <mathlib.h>

class Context
{
public:
  Context();
  ~Context();

  void Load(vec3 *vertices, int num_vertices, int *triangles, int num_triangles);

private:
  vec3 *vertices;
  int num_vertices;
  int *triangles;
  int num_triangles;
};