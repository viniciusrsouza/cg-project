#include <vec3.h>

vec3::vec3(float x, float y, float z) : x(x), y(y), z(z)
{
}

vec3::vec3(vec3 const &v) : x(v.x), y(v.y), z(v.z)
{
}

vec3::vec3() : x(0), y(0), z(0)
{
}

vec3::~vec3()
{
}

// Operators

std::ostream &operator<<(std::ostream &os, vec3 const &v)
{
  os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}