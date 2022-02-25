#include <shader.h>
#include <iostream>

Shader::Shader() {}
Shader::~Shader() {}

void Shader::Load(Camera *c)
{
  camera = c;
}

vec3 Shader::Vertex(vec3 const &in) const
{
  return in;
}

vec3 Shader::Fragment() const
{
  return vec3(0xff, 0xff, 0xff);
}