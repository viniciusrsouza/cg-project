#include <mat4.h>
#include <mat3.h>

// inline implementations
inline void _multiply_4_4(const float *m1, const float *m2, mat4 *dest)
{
  float result[16];
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      result[i * 4 + j] = 0;
      for (int k = 0; k < 4; k++)
      {
        result[i * 4 + j] += m1[i * 4 + k] * m2[k * 4 + j];
      }
    }
  }
  dest->set(result);
}

inline float _determinant_4_4(const float *m)
{
  std::cout << "determinant" << std::endl;
  std::cout << "first submatrix" << std::endl;
  mat3 sm1 = mat3(m[5], m[6], m[7],
                  m[9], m[10], m[11],
                  m[13], m[14], m[15]);
  std::cout << "second submatrix" << std::endl;
  mat3 sm2 = mat3(m[4], m[6], m[7],
                  m[8], m[10], m[11],
                  m[12], m[14], m[15]);
  std::cout << "third submatrix" << std::endl;
  mat3 sm3 = mat3(m[4], m[5], m[7],
                  m[8], m[9], m[11],
                  m[12], m[13], m[15]);
  std::cout << "fourth submatrix" << std::endl;
  mat3 sm4 = mat3(m[4], m[5], m[6],
                  m[8], m[9], m[10],
                  m[12], m[13], m[14]);
  std::cout << "multiplying" << std::endl;
  return m[0] * sm1.determinant() -
         m[1] * sm2.determinant() +
         m[2] * sm3.determinant() -
         m[3] * sm4.determinant();
}

inline void _invert(mat4 *m1)
{
  float r[16];
  float *m = m1->getPtr();
  float det = _determinant_4_4(m1->getPtr());
  if (det == 0)
    return;
  det = 1.0f / det;
  r[0] = det * (m[4] * m[8] - m[5] * m[7]);
  r[1] = det * (m[2] * m[7] - m[1] * m[8]);
  r[2] = det * (m[1] * m[5] - m[2] * m[4]);
  r[3] = det * (m[5] * m[6] - m[3] * m[8]);
  r[4] = det * (m[0] * m[8] - m[2] * m[6]);
  r[5] = det * (m[2] * m[3] - m[0] * m[5]);
  r[6] = det * (m[3] * m[7] - m[4] * m[6]);
  r[7] = det * (m[1] * m[6] - m[0] * m[7]);
  r[8] = det * (m[0] * m[4] - m[1] * m[3]);
  r[9] = det * (m[3] * m[7] - m[5] * m[6]);
  r[10] = det * (m[1] * m[6] - m[2] * m[7]);
  r[11] = det * (m[2] * m[5] - m[0] * m[4]);
  r[12] = det * (m[3] * m[6] - m[4] * m[5]);
  r[13] = det * (m[2] * m[7] - m[1] * m[6]);
  r[14] = det * (m[0] * m[5] - m[3] * m[4]);
  r[15] = det * (m[1] * m[4] - m[0] * m[3]);
  m1->set(r);
}

// Matrix constructors
mat4::mat4()
{
  set(0, 0, 0, 0,
      0, 0, 0, 0,
      0, 0, 0, 0,
      0, 0, 0, 0);
}

mat4::mat4(const mat4 &m)
{
  set((float *)m.m);
}

mat4::mat4(const float *m)
{
  set(m);
}

mat4::mat4(float mi)
{
  set(mi);
}

mat4::mat4(float m00, float m10, float m20, float m30,
           float m01, float m11, float m21, float m31,
           float m02, float m12, float m22, float m32,
           float m03, float m13, float m23, float m33)
{
  set(m00, m10, m20, m30,
      m01, m11, m21, m31,
      m02, m12, m22, m32,
      m03, m13, m23, m33);
}

mat4::~mat4()
{
}

// Matrix operators

std::ostream &operator<<(std::ostream &os, const mat4 &m)
{
  os << "|" << m.m[0] << " " << m.m[1] << " " << m.m[2] << " " << m.m[3] << "|" << std::endl;
  os << "|" << m.m[4] << " " << m.m[5] << " " << m.m[6] << " " << m.m[7] << "|" << std::endl;
  os << "|" << m.m[8] << " " << m.m[9] << " " << m.m[10] << " " << m.m[11] << "|" << std::endl;
  os << "|" << m.m[12] << " " << m.m[13] << " " << m.m[14] << " " << m.m[15] << "|" << std::endl;
  return os;
}

inline float &mat4::operator()(int i, int j)
{
  return m[i * 4 + j];
}

inline float mat4::operator()(int i, int j) const
{
  return m[i * 4 + j];
}

mat4 &mat4::operator=(const mat4 &m)
{
  set(m);
  return *this;
}

mat4 &mat4::operator+=(const mat4 &m)
{
  for (int i = 0; i < 16; i++)
    this->m[i] += m.m[i];
  return *this;
}

mat4 &mat4::operator-=(const mat4 &m)
{
  for (int i = 0; i < 16; i++)
    this->m[i] -= m.m[i];
  return *this;
}

mat4 &mat4::operator*=(const mat4 &m)
{
  _multiply_4_4(this->m, m.getPtr(), this);
  return *this;
}

mat4 &mat4::operator*=(float s)
{
  for (int i = 0; i < 16; i++)
    this->m[i] *= s;
  return *this;
}

mat4 &mat4::operator/=(float s)
{
  for (int i = 0; i < 16; i++)
    this->m[i] /= s;
  return *this;
}

mat4 mat4::operator+(const mat4 &m) const
{
  mat4 r;
  for (int i = 0; i < 16; i++)
    r.m[i] = this->m[i] + m.m[i];
  return r;
}

mat4 mat4::operator-(const mat4 &m) const
{
  mat4 r;
  for (int i = 0; i < 16; i++)
    r.m[i] = this->m[i] - m.m[i];
  return r;
}

mat4 mat4::operator*(const mat4 &m) const
{
  mat4 r;
  _multiply_4_4(this->m, m.getPtr(), &r);
  return r;
}

mat4 mat4::operator*(float s) const
{
  mat4 r;
  for (int i = 0; i < 16; i++)
    r.m[i] = this->m[i] * s;
  return r;
}

mat4 mat4::operator/(float s) const
{
  mat4 r;
  for (int i = 0; i < 16; i++)
    r.m[i] = this->m[i] / s;
  return r;
}

vec4 mat4::operator*(const vec4 &v) const
{
  float x = v.x * m[0] + v.y * m[4] + v.z * m[8] + v.w * m[12];
  float y = v.x * m[1] + v.y * m[5] + v.z * m[9] + v.w * m[13];
  float z = v.x * m[2] + v.y * m[6] + v.z * m[10] + v.w * m[14];
  float w = v.x * m[3] + v.y * m[7] + v.z * m[11] + v.w * m[15];
  return vec4(x, y, z, w);
}

float *mat4::getPtr()
{
  return m;
}

const float *mat4::getPtr() const
{
  return m;
}

// Matrix functions
void mat4::identity()
{
  set(1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1);
}

void mat4::transpose()
{
  float t[16];
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      t[i * 4 + j] = m[j * 4 + i];
  set(t);
}

void mat4::invert()
{
  _invert(this);
}

float mat4::determinant() const
{
  return _determinant_4_4(m);
}

mat4 mat4::inverse() const
{
  mat4 r(m);
  _invert(&r);
  return r;
}

// Matrix setters
void mat4::set(float m00, float m10, float m20, float m30,
               float m01, float m11, float m21, float m31,
               float m02, float m12, float m22, float m32,
               float m03, float m13, float m23, float m33)
{
  m[0] = m00;
  m[1] = m01;
  m[2] = m02;
  m[3] = m03;
  m[4] = m10;
  m[5] = m11;
  m[6] = m12;
  m[7] = m13;
  m[8] = m20;
  m[9] = m21;
  m[10] = m22;
  m[11] = m23;
  m[12] = m30;
  m[13] = m31;
  m[14] = m32;
  m[15] = m33;
}

void mat4::set(const float *m)
{
  memcpy(this->m, m, sizeof(float) * 16);
}

void mat4::set(const mat4 &m)
{
  memcpy(this->m, m.m, sizeof(float) * 16);
}

void mat4::set(float mi)
{
  memset(m, 0, sizeof(float) * 16);
  m[0] = mi;
  m[5] = mi;
  m[10] = mi;
  m[15] = mi;
}