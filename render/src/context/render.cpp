#include <context/render.h>
#include <math.h>
#include <iostream>

void PaintUpper(
    vec3 const &a,
    vec3 const &b,
    vec3 const &c,
    uint8_t *buffer,
    int w, int h,
    Shader const &shader);
void PaintLower(
    vec3 const &a,
    vec3 const &b,
    vec3 const &c,
    uint8_t *buffer,
    int w, int h,
    Shader const &shader);

void sorted(vec3 *vs);

void Scanline(vec3 const &_a,
              vec3 const &_b,
              vec3 const &_c,
              uint8_t *buffer,
              int w, int h,
              Shader const &shader)
{
  vec3 vs[3] = {_a, _b, _c};
  sorted(vs);
  vec3 a = vs[0];
  vec3 b = vs[1];
  vec3 c = vs[2];

  if (b.y == c.y)
    PaintUpper(a, b, c, buffer, w, h, shader);
  else if (a.y == b.y)
    PaintLower(a, b, c, buffer, w, h, shader);
  else
  {
    float x = a.x + ((b.y - a.y) / (c.y - a.y)) * (c.x - a.x) + 0.5;
    x = floorf(x);
    float y = b.y;
    vec3 d = vec3(x, y, 0);

    PaintUpper(a, b, d, buffer, w, h, shader);
    PaintLower(d, b, c, buffer, w, h, shader);
  }
}

void PaintUpper(
    vec3 const &a,
    vec3 const &b,
    vec3 const &c,
    uint8_t *buffer,
    int w, int h,
    Shader const &shader)
{
  float a_min, a_max;
  if (b.x < c.x)
  {
    a_min = (b.y - a.y) == 0 ? 0 : (b.x - a.x) / (b.y - a.y);
    a_max = (c.y - a.y) == 0 ? 0 : (c.x - a.x) / (c.y - a.y);
  }
  else
  {
    a_min = (c.y - a.y) == 0 ? 0 : (c.x - a.x) / (c.y - a.y);
    a_max = (b.y - a.y) == 0 ? 0 : (b.x - a.x) / (b.y - a.y);
  }

  float x_min = a.x;
  float x_max = a.x;

  for (int y = a.y; y < b.y; y++)
  {
    for (int x = x_min; x < x_max; x++)
    {
      int i = (y * w + x) * 3;
      vec3 color = shader.Fragment();
      buffer[i] = 0xff;
      buffer[i + 1] = 0xff;
      buffer[i + 2] = 0xff;
    }
    x_min += a_min;
    x_max += a_max;
  }
}
void PaintLower(
    vec3 const &a,
    vec3 const &b,
    vec3 const &c,
    uint8_t *buffer,
    int w, int h,
    Shader const &shader)
{
  float a_min, a_max;
  if (a.x < b.x)
  {
    a_min = (c.y - a.y) == 0 ? 0 : (c.x - a.x) / (c.y - a.y);
    a_max = (c.y - b.y) == 0 ? 0 : (c.x - b.x) / (c.y - b.y);
  }
  else
  {
    a_min = (c.y - b.y) == 0 ? 0 : (c.x - b.x) / (c.y - b.y);
    a_max = (c.y - a.y) == 0 ? 0 : (c.x - a.x) / (c.y - a.y);
  }

  float x_min = c.x;
  float x_max = c.x;

  for (int y = c.y; y > a.y - 1; y--)
  {
    for (int x = x_min; x < x_max; x++)
    {
      int i = (y * w + x) * 3;
      vec3 color = shader.Fragment();
      buffer[i] = 0xff;
      buffer[i + 1] = 0xff;
      buffer[i + 2] = 0xff;
    }
    x_min -= a_min;
    x_max -= a_max;
  }
}

void sorted(vec3 *vs)
{
  if (vs[0].y > vs[2].y)
  {
    vec3 tmp = vs[0];
    vs[0] = vs[2];
    vs[2] = tmp;
  }
  if (vs[0].y > vs[1].y)
  {
    vec3 tmp = vs[0];
    vs[0] = vs[1];
    vs[1] = tmp;
  }
  if (vs[1].y > vs[2].y)
  {
    vec3 tmp = vs[1];
    vs[1] = vs[2];
    vs[2] = tmp;
  }
}