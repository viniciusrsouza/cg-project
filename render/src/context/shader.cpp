#include <context/shader.h>
#include <iostream>

Shader::Shader() {}
Shader::~Shader() {}

void Shader::Load(Camera *c)
{
  camera = c;
}

vec3 Shader::Vertex(vec3 const &in)
{
  return in;
}

vec3 Shader::Fragment()
{
  return vec3(1.0f, 1.0f, 1.0f);
}