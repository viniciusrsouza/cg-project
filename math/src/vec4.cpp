#include <vec4.h>
#include <math.h>

vec4::vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{
}

vec4::vec4(vec4 const &v) : x(v.x), y(v.y), z(v.z), w(v.w)
{
}

vec4::vec4(vec3 const &v, float w) : x(v.x), y(v.y), z(v.z), w(w)
{
}

vec4::vec4(float s) : x(s), y(s), z(s), w(s)
{
}

vec4::vec4() : x(0), y(0), z(0), w(0)
{
}

vec4::~vec4()
{
}

// Operators
vec4 &vec4::operator=(vec4 const &v)
{
  set(v);
  return *this;
}

vec4 &vec4::operator+=(vec4 const &v)
{
  x += v.x;
  y += v.y;
  z += v.z;
  w += v.w;
  return *this;
}

vec4 &vec4::operator-=(vec4 const &v)
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
  w -= v.w;
  return *this;
}

vec4 &vec4::operator*=(float s)
{
  x *= s;
  y *= s;
  z *= s;
  w *= s;
  return *this;
}

vec4 &vec4::operator/=(float s)
{
  x /= s;
  y /= s;
  z /= s;
  w /= s;
  return *this;
}

vec4 vec4::operator*(float s) const
{
  return vec4(x * s, y * s, z * s, w * s);
}

vec4 vec4::operator/(float s) const
{
  return vec4(x / s, y / s, z / s, w / s);
}

vec4 vec4::operator-(vec4 const &v) const
{
  return vec4(x - v.x, y - v.y, z - v.z, w - v.w);
}

vec4 vec4::operator+(vec4 const &v) const
{
  return vec4(x + v.x, y + v.y, z + v.z, w + v.w);
}

std::ostream &operator<<(std::ostream &os, vec4 const &v)
{
  os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
  return os;
}

// vec4 functions
float vec4::dot(vec4 const &v) const
{
  return x * v.x + y * v.y + z * v.z + w * v.w;
}

vec4 vec4::normalize() const
{
  float len = length();
  return vec4(x / len, y / len, z / len, w / len);
}

float vec4::length() const
{
  return sqrt(x * x + y * y + z * z + w * w);
}

float vec4::distance(vec4 const &v) const
{
  return (*this - v).length();
}

vec4 vec4::project(vec4 const &v) const
{
  return v * (dot(v) / v.dot(v));
}

// Setters
void vec4::set(float x, float y, float z, float w)
{
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

void vec4::set(vec4 const &v)
{
  this->x = v.x;
  this->y = v.y;
  this->z = v.z;
  this->w = v.w;
}

void vec4::set(float s)
{
  this->x = s;
  this->y = s;
  this->z = s;
  this->w = s;
}