#pragma once
#include <iostream>
class Vec3
{
public:
  Vec3(float x, float y, float z);
  Vec3(Vec3 const &v);
  Vec3();
  ~Vec3();

  // operators
  friend std::ostream &operator<<(std::ostream &os, Vec3 const &v);

  float x, y, z;
};