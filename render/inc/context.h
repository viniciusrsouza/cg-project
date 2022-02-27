#pragma once

#include <mathlib.h>
#include "camera.h"

class Context
{
public:
  Context();
  ~Context();

  void Render(uint8_t *buffer, int w, int h);

  void Load(vec3 *vertices, int num_vertices, int *triangles, int num_triangles);
  void SetCamera(Camera *c);
  vec3 TransformVertex(vec3 const &in) const;

private:
  vec3 *vertices;
  int num_vertices;
  int *triangles;
  int num_triangles;
  Camera *camera;
};