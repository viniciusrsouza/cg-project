#pragma once

#include <mathlib.h>
#include "shader.h"

void BeginScanline(int w, int h);
void EndScanline();
void Scanline(
    vec3 const &a,
    vec3 const &b,
    vec3 const &c,
    uint8_t *buffer,
    int w, int h,
    Shader const &shader);

// scanline auxilary functions
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
void Sorted(vec3 *vs);
void PaintPixel(vec3 const &a,
                vec3 const &b,
                vec3 const &c,
                uint8_t *buffer,
                int w, int h, int x, int y,
                Shader const &shader);