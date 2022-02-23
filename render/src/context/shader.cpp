#include <context/shader.h>
#include <iostream>

Shader::Shader() {}
Shader::~Shader() {}

void Shader::Load(mat4 const &view, mat4 const &perspective, mat4 const &screen)
{
  std::cout << "loaded" << std::endl;
  this->view = mat4(view);
  this->perspective = mat4(perspective);
  this->screen = mat4(screen);
}
vec4 Shader::Vertex(vec3 const &in)
{
  return vec4(in, 1.0f);
}

vec3 Shader::Fragment()
{
  return vec3(1.0f, 1.0f, 1.0f);
}