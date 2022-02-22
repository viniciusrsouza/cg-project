#include <file.h>
#include <fstream>

File::File(std::string const &filename) : filename(filename)
{
}

bool File::Load()
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
    std::cout << "Could not open file: " << filename << std::endl;
    return false;
  }

  std::string line;
  file >> vertexCount >> triangleCount;

  vertices = new Vec3[vertexCount];
  indices = new int[triangleCount * 3];

  for (int i = 0; i < vertexCount; i++)
  {
    file >> vertices[i].x >> vertices[i].y >> vertices[i].z;
  }

  for (int i = 0; i < triangleCount * 3; i++)
  {
    file >> indices[i];
  }

  file.close();
  return true;
}

std::ostream &operator<<(std::ostream &os, File const &f)
{
  os << "File: " << f.filename << std::endl;
  os << "vertexCount: " << f.vertexCount << std::endl;
  os << "triangleCount: " << f.triangleCount << std::endl;
  os << "vertices: " << std::endl;
  return os;
}