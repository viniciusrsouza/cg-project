#pragma once

class Vec3
{
public:
  Vec3(float x, float y, float z);
  Vec3(Vec3 const &v);
  Vec3();
  ~Vec3();

  float x, y, z;
};