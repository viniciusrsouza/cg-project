#include <render.h>
#include <math.h>
#include <iostream>

scanline_config *cfg = nullptr;

light::light()
{
  pos = vec3(0.0f, 0.0f, 0.0f);
  rgb = vec3(1.0f, 1.0f, 1.0f);

  ka = 0.2f;
  iamb = vec3(1.0f, 1.0f, 1.0f);
  amb = iamb * ka;
}

scanline_config::scanline_config(int w, int h, uint8_t *buffer)
{
  this->zbuffer = (float *)malloc(sizeof(float) * w * h);
  memset(this->zbuffer, 0, sizeof(float) * w * h);

  this->l = light();

  this->w = w;
  this->h = h;
  this->buffer = buffer;
}

scanline_config::~scanline_config()
{
  free(this->zbuffer);
}

void BeginScanline(int w, int h, uint8_t *buffer)
{
  cfg = new scanline_config(w, h, buffer);
}
void EndScanline()
{
  delete cfg;
  cfg = nullptr;
}

void LoadTriangle(vec3 const &a, vec3 const &b, vec3 const &c)
{
  cfg->area = Triangle::Area(a, b, c);
  cfg->normal = Triangle::Normal(a, b, c);
}

void Scanline(vec3 const &_a,
              vec3 const &_b,
              vec3 const &_c)
{
  vec3 vs[3] = {_a, _b, _c};
  Sorted(vs);
  vec3 a = vs[0];
  vec3 b = vs[1];
  vec3 c = vs[2];

  if (b.y == c.y)
    PaintUpper(a, b, c);
  else if (a.y == b.y)
    PaintLower(a, b, c);
  else
  {
    float x = a.x + ((b.y - a.y) / (c.y - a.y)) * (c.x - a.x) + 0.5;
    x = floorf(x);
    float y = b.y;
    vec3 d = vec3(x, y, 0);

    PaintUpper(a, b, d);
    PaintLower(d, b, c);
  }
}

void PaintUpper(
    vec3 const &a,
    vec3 const &b,
    vec3 const &c)
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

  LoadTriangle(a, b, c);
  for (int y = a.y; y < b.y; y++)
  {
    for (int x = x_min; x < x_max; x++)
    {
      int i = (y * cfg->w + x) * 4;
      PaintPixel(a, b, c, x, y);
    }
    x_min += a_min;
    x_max += a_max;
  }
}

void PaintLower(
    vec3 const &a,
    vec3 const &b,
    vec3 const &c)
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

  LoadTriangle(a, b, c);
  for (int y = c.y; y > a.y - 1; y--)
  {
    for (int x = x_min; x < x_max; x++)
    {
      int i = (y * cfg->w + x) * 4;
      PaintPixel(a, b, c, x, y);
    }
    x_min -= a_min;
    x_max -= a_max;
  }
}

void Sorted(vec3 *vs)
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

void PaintPixel(vec3 const &a,
                vec3 const &b,
                vec3 const &c,
                int x, int y)
{
  int i = (y * cfg->w + x) * 4;

  vec3 p = Triangle::PointAt(a, b, c, x, y, cfg->area);
  if (cfg->zbuffer[y * cfg->w + x] > p.z)
    return;
  cfg->zbuffer[y * cfg->w + x] = p.z;

  vec3 color = GetColor(a, b, c, p);
  cfg->buffer[i + 0] = (uint8_t)(color.x * 255);
  cfg->buffer[i + 1] = (uint8_t)(color.y * 255);
  cfg->buffer[i + 2] = (uint8_t)(color.z * 255);
  cfg->buffer[i + 3] = 0xff;
}

vec3 GetColor(vec3 const &a,
              vec3 const &b,
              vec3 const &c,
              vec3 const &p)
{
  return cfg->l.amb;
}