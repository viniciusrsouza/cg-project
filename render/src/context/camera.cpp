#include <context/camera.h>
#include <fstream>
#include <sstream>

Camera::Camera() : N(vec3(0, 1, -1)), V(vec3(0, -1, -1)),
                   d(5), hx(2), hy(2),
                   C(point(0, -500, -500)),
                   dhx(d / hx), dhy(d / hy)
{
  Init();
}

Camera::Camera(vec3 const &N, vec3 const &V,
               point const &C,
               float d, float hx, float hy)
    : N(N), V(V), C(C),
      d(d), hx(hx), hy(hy),
      dhx(d / hx), dhy(d / hy)
{
  Init();
}

void Camera::Init()
{
  V = (V - V.project(N)).normalize();
  N = N.normalize();
  U = N.cross(V).normalize();
}

Camera::~Camera()
{
}

// Parser for camera.txt
inline vec3 *ParseVec3(std::string const &str)
{
  std::stringstream ss(str);
  vec3 *v = new vec3();
  ss >> v->x >> v->y >> v->z;
  return v;
}

inline float ParseFloat(std::string const &str)
{
  std::stringstream ss(str);
  float f;
  ss >> f;
  return f;
}

inline Camera *ParseFile(std::ifstream &file)
{
  std::string line;

  std::getline(file, line);
  vec3 *N = ParseVec3(line);

  std::getline(file, line);
  vec3 *V = ParseVec3(line);

  std::getline(file, line);
  float d = ParseFloat(line);

  std::getline(file, line);
  float hx = ParseFloat(line);

  std::getline(file, line);
  float hy = ParseFloat(line);

  std::getline(file, line);
  point *C = ParseVec3(line);

  return new Camera(*N, *V, *C, d, hx, hy);
}

Camera *Camera::FromFile(std::string const &filename)
{
  std::ifstream file(filename);

  if (!file.is_open())
  {
    std::cerr << "Failed to open file: " << filename << std::endl;
    return nullptr;
  }

  return ParseFile(file);
}

std::ostream &operator<<(std::ostream &os, Camera const &c)
{
  os << "Camera: " << std::endl;
  os << "N: " << c.N << std::endl;
  os << "V: " << c.V << std::endl;
  os << "C: " << c.C << std::endl;
  os << "d: " << c.d << std::endl;
  os << "hx: " << c.hx << std::endl;
  os << "hy: " << c.hy << std::endl;
  return os;
}