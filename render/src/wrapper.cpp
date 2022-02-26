#include <wrapper.h>
#include <entry.h>
#include <iostream>

unsigned char *c_render(
    const char *asset_path,
    const float *camera_values,
    int w, int h)
{
  unsigned char *buffer = new unsigned char[w * h * 4];
  render(asset_path, camera_values, buffer, w, h);
  return buffer;
}

unsigned char *dbg(const char *asset_path,
                   const float *camera_values,
                   int w, int h)
{
  unsigned char *buffer = new unsigned char[w * h * 4];
  return buffer;
}