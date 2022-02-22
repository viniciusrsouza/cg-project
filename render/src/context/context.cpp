#include <context/context.h>

Context::Context()
{
}

Context::~Context()
{
  delete[] vertices;
  delete[] triangles;
  delete camera;
  delete shader;
}

void Context::Load(vec3 *vertices, int num_vertices, int *triangles, int num_triangles)
{
  this->vertices = vertices;
  this->num_vertices = num_vertices;
  this->triangles = triangles;
  this->num_triangles = num_triangles;
}

void Context::SetCamera(Camera *c)
{
  camera = c;
}

void Context::UseShader(Shader *s)
{
  shader = s;
}

void Context::Render(uint8_t *buffer, int size)
{
  // clear buffer
  memset(buffer, 0, size);
}