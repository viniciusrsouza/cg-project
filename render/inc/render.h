#pragma once

#include <mathlib.h>
#include "shader.h"

void Scanline(
    vec3 const &a,
    vec3 const &b,
    vec3 const &c,
    uint8_t *buffer,
    int w, int h,
    Shader const &shader);