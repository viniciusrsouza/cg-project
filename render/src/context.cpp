#include <context.h>
#include <render.h>
#include <iostream>

Context::Context()
{
  vertices = nullptr;
  triangles = nullptr;
  camera = nullptr;
  shader = nullptr;
}

Context::~Context()
{
  if (vertices != nullptr)
    delete[] vertices;
  if (triangles != nullptr)
    delete[] triangles;

  if (camera != nullptr)
    delete camera;
  if (shader != nullptr)
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

void Context::Render(uint8_t *buffer, int w, int h)
{
  int size = w * h * 4;
  // clear buffer
  memset(buffer, 0, size);
  if (shader == nullptr)
    return;

  shader->Load(camera);

  vec3 *t_vertices = new vec3[num_vertices];

  for (int i = 0; i < num_vertices; i++)
    t_vertices[i] = shader->Vertex(vertices[i]);

  for (int i = 0; i < num_triangles * 3; i += 3)
  {
    int ai = triangles[i] - 1;
    int bi = triangles[i + 1] - 1;
    int ci = triangles[i + 2] - 1;
    vec3 a = t_vertices[ai];
    vec3 b = t_vertices[bi];
    vec3 c = t_vertices[ci];

    Scanline(a, b, c, buffer, w, h, *shader);
  }
}