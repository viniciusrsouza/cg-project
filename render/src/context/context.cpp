#include <context/context.h>
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

void Context::Render(uint8_t *buffer, int size)
{
  // clear buffer
  memset(buffer, 0, size);
  if (shader == nullptr)
    return;

  shader->Load(camera);

  vec4 *t_vertices = new vec4[num_vertices];

  for (int i = 0; i < num_vertices; i++)
  {
    t_vertices[i] = shader->Vertex(vertices[i]);
    // std::cout << "Vertex " << i << ": " << t_vertices[i] << std::endl;
  }
}