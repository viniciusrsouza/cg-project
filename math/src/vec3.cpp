#include <vec3.h>
#include <math.h>

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
vec3 &vec3::operator=(vec3 const &v)
{
  set(v);
  return *this;
}

vec3 &vec3::operator+=(vec3 const &v)
{
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

vec3 &vec3::operator-=(vec3 const &v)
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}

vec3 &vec3::operator*=(float s)
{
  x *= s;
  y *= s;
  z *= s;
  return *this;
}

vec3 &vec3::operator/=(float s)
{
  x /= s;
  y /= s;
  z /= s;
  return *this;
}

vec3 vec3::operator*(float s) const
{
  return vec3(x * s, y * s, z * s);
}

vec3 vec3::operator/(float s) const
{
  return vec3(x / s, y / s, z / s);
}

vec3 vec3::operator-(vec3 const &v) const
{
  return vec3(x - v.x, y - v.y, z - v.z);
}

vec3 vec3::operator+(vec3 const &v) const
{
  return vec3(x + v.x, y + v.y, z + v.z);
}

std::ostream &operator<<(std::ostream &os, vec3 const &v)
{
  os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}

// vec3 functions
vec3 vec3::cross(vec3 const &v) const
{
  return vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

float vec3::dot(vec3 const &v) const
{
  return x * v.x + y * v.y + z * v.z;
}

vec3 vec3::normalize() const
{
  float l = length();
  return vec3(x / l, y / l, z / l);
}

float vec3::length() const
{
  return sqrt(x * x + y * y + z * z);
}

float vec3::distance(vec3 const &v) const
{
  return (*this - v).length();
}

vec3 vec3::project(vec3 const &v) const
{
  return v * (dot(v) / v.dot(v));
}

// Setters
void vec3::set(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

void vec3::set(vec3 const &v)
{
  this->x = v.x;
  this->y = v.y;
  this->z = v.z;
}

void vec3::set(float s)
{
  this->x = s;
  this->y = s;
  this->z = s;
}