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

  mat4 m = mat4(0.0f, 1.0f, 4.0f, -1.0f,
                9.0f, 2.0f, 7.0f, -3.0f,
                8.0f, -4.0f, 2.0f, 1.0f,
                3.0f, 0.0f, -2.0f, 0.0f);
  m.transpose();
  std::cout << "m = " << std::endl;
  std::cout << m << std::endl;

  float det = m.determinant();
  std::cout << "det = " << det << std::endl;
}