#include <vec3.h>

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z)
{
}

Vec3::Vec3(Vec3 const &v) : x(v.x), y(v.y), z(v.z)
{
}

Vec3::Vec3() : x(0), y(0), z(0)
{
}

Vec3::~Vec3()
{
}