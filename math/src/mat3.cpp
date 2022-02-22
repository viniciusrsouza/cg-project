#include <mat3.h>

// inline implementations
inline void _multiply(const float *m1, const float *m2, mat3 *dest)
{
  float result[9];
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      result[i * 3 + j] = 0;
      for (int k = 0; k < 3; k++)
      {
        result[i * 3 + j] += m1[i * 3 + k] * m2[k * 3 + j];
      }
    }
  }
  dest->set(result);
}

inline float _determinant(const float *m1)
{
  return m1[0] * (m1[4] * m1[8] - m1[5] * m1[7]) -
         m1[1] * (m1[3] * m1[8] - m1[5] * m1[6]) +
         m1[2] * (m1[3] * m1[7] - m1[4] * m1[6]);
}

inline void _invert(mat3 *m1)
{
  float r[9];
  float *m = m1->getPtr();
  float det = _determinant(m1->getPtr());
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
  m1->set(r);
}

// Matrix constructors
mat3::mat3()
{
  set(0, 0, 0,
      0, 0, 0,
      0, 0, 0);
}

mat3::mat3(const mat3 &m)
{
  set((float *)m.m);
}

mat3::mat3(const float *m)
{
  set(m);
}

mat3::mat3(float mi)
{
  set(mi);
}

mat3::mat3(float m00, float m10, float m20,
           float m01, float m11, float m21,
           float m02, float m12, float m22)
{
  set(m00, m10, m20,
      m01, m11, m21,
      m02, m12, m22);
}

mat3::~mat3()
{
}

// Matrix operators

std::ostream &operator<<(std::ostream &os, const mat3 &m)
{
  os << "|" << m.m[0] << " " << m.m[1] << " " << m.m[2] << "|" << std::endl;
  os << "|" << m.m[3] << " " << m.m[4] << " " << m.m[5] << "|" << std::endl;
  os << "|" << m.m[6] << " " << m.m[7] << " " << m.m[8] << "|" << std::endl;
  return os;
}

float &mat3::operator()(int i, int j)
{
  return m[i * 3 + j];
}

float mat3::operator()(int i, int j) const
{
  return m[i * 3 + j];
}

mat3 &mat3::operator=(const mat3 &m)
{
  set(m);
  return *this;
}

mat3 &mat3::operator+=(const mat3 &m)
{
  for (int i = 0; i < 9; i++)
    this->m[i] += m.m[i];
  return *this;
}

mat3 &mat3::operator-=(const mat3 &m)
{
  for (int i = 0; i < 9; i++)
    this->m[i] -= m.m[i];
  return *this;
}

mat3 &mat3::operator*=(const mat3 &m)
{
  _multiply(this->m, m.getPtr(), this);
  return *this;
}

mat3 &mat3::operator*=(float s)
{
  for (int i = 0; i < 9; i++)
    this->m[i] *= s;
  return *this;
}

mat3 &mat3::operator/=(float s)
{
  for (int i = 0; i < 9; i++)
    this->m[i] /= s;
  return *this;
}

mat3 mat3::operator+(const mat3 &m) const
{
  mat3 r;
  for (int i = 0; i < 9; i++)
    r.m[i] = this->m[i] + m.m[i];
  return r;
}

mat3 mat3::operator-(const mat3 &m) const
{
  mat3 r;
  for (int i = 0; i < 9; i++)
    r.m[i] = this->m[i] - m.m[i];
  return r;
}

mat3 mat3::operator*(const mat3 &m) const
{
  mat3 r;
  _multiply(this->m, m.getPtr(), &r);
  return r;
}

mat3 mat3::operator*(float s) const
{
  mat3 r;
  for (int i = 0; i < 9; i++)
    r.m[i] = this->m[i] * s;
  return r;
}

mat3 mat3::operator/(float s) const
{
  mat3 r;
  for (int i = 0; i < 9; i++)
    r.m[i] = this->m[i] / s;
  return r;
}

float *mat3::getPtr()
{
  return m;
}

const float *mat3::getPtr() const
{
  return m;
}

// Matrix functions
void mat3::identity()
{
  set(1, 0, 0,
      0, 1, 0,
      0, 0, 1);
}

void mat3::transpose()
{
  float t[9];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      t[i * 3 + j] = m[j * 3 + i];
  set(t);
}

void mat3::invert()
{
  _invert(this);
}

float mat3::determinant() const
{
  return _determinant(m);
}

mat3 mat3::inverse() const
{
  mat3 r(m);
  _invert(&r);
  return r;
}

// Matrix setters
void mat3::set(float m00, float m10, float m20,
               float m01, float m11, float m21,
               float m02, float m12, float m22)
{
  m[0] = m00;
  m[1] = m01;
  m[2] = m02;
  m[3] = m10;
  m[4] = m11;
  m[5] = m12;
  m[6] = m20;
  m[7] = m21;
  m[8] = m22;
}

void mat3::set(const float *m)
{
  memcpy(this->m, m, sizeof(float) * 9);
}

void mat3::set(const mat3 &m)
{
  memcpy(this->m, m.m, sizeof(float) * 9);
}

void mat3::set(float mi)
{
  memset(m, 0, sizeof(float) * 9);
  m[0] = mi;
  m[4] = mi;
  m[8] = mi;
}