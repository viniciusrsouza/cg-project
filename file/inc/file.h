#pragma once
#include <iostream>
#include <mathlib.h>

// Loads byu file used by the render algorithm
class File
{
public:
  File(std::string const &filename);
  ~File();
  bool Load();

  // operators
  friend std::ostream &operator<<(std::ostream &os, File const &f);

  std::string filename;

  int triangleCount;
  int vertexCount;

  Vec3 *vertices;
  int *indices;
};