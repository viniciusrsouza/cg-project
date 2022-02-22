#pragma once

#include <mathlib.h>
#include "camera.h"
#include "shader.h"

class Context
{
public:
  Context();
  ~Context();

  void Render(uint8_t *buffer, int size);

  void Load(vec3 *vertices, int num_vertices, int *triangles, int num_triangles);
  void SetCamera(Camera *c);
  void UseShader(Shader *s);

private:
  vec3 *vertices;
  int num_vertices;
  int *triangles;
  int num_triangles;
  Camera *camera;
  Shader *shader;
};