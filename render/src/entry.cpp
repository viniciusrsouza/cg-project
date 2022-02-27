#include <entry.h>
#include <context.h>
#include <camera.h>

#include <filelib.h>
#include <mathlib.h>

int render(
    const char *asset_path,
    const float *camera_values,
    unsigned char *buffer,
    int w, int h)
{
  Context *ctx = new Context();
  File *file = new File(asset_path);
  if (!file->Load())
    return -1;

  vec3 N(camera_values[0], camera_values[1], camera_values[2]);
  vec3 V(camera_values[3], camera_values[4], camera_values[5]);
  float d = camera_values[6];
  float hx = camera_values[7];
  float hy = camera_values[8];
  vec3 C(camera_values[9], camera_values[10], camera_values[11]);
  Camera *c = new Camera(N, V, C, d, hx, hy);
  if (c == nullptr)
    return -2;

  c->SetSize(w, h);
  ctx->SetCamera(c);
  ctx->Load(file->vertices, file->vertexCount, file->indices, file->triangleCount);
  ctx->Render((uint8_t *)buffer, w, h);
  return 0;
}