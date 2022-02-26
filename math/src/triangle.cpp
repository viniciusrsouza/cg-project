#include <triangle.h>

#include <math.h>

vec3 Triangle::PointAt(vec3 const &a, vec3 const &b, vec3 const &c, float x, float y, float area)
{
  vec3 a0 = vec3(a.x, a.y, 0.0f);
  vec3 b0 = vec3(b.x, b.y, 0.0f);
  vec3 c0 = vec3(c.x, c.y, 0.0f);
  vec3 p0 = vec3(x, y, 0.0f);
  // barycentric coordinates
  float wa = Area(b0, c0, p0) / area;
  float wb = Area(c0, a0, p0) / area;
  float wc = Area(a0, b0, p0) / area;

  // interpolated point
  return a * wa + b * wb + c * wc;
}

// Heron's formula
float Triangle::Area(vec3 const &a, vec3 const &b, vec3 const &c)
{
  float ab = a.distance(b);
  float ac = a.distance(c);
  float bc = b.distance(c);

  float s = (ab + ac + bc) / 2.0f;
  return sqrt(s * (s - ab) * (s - ac) * (s - bc));
}