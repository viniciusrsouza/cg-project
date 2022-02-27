#pragma once

#include <mathlib.h>

/**
 * @brief initializes scanline config object
 *
 * @param w buffer width
 * @param h buffer height
 * @param buffer pixel buffer to render to
 */
void BeginScanline(int w, int h, uint8_t *buffer);

/**
 * @brief cleans up scanline config object
 */
void EndScanline();

/**
 * @brief Renders a triangle using scanline conversion
 * algorithm
 *
 * @param a triangle a vertex
 * @param b triangle b vertex
 * @param c triangle c vertex
 */
void Scanline(
    vec3 const &a,
    vec3 const &b,
    vec3 const &c);

struct light
{
    light();

    vec3 pos;
    vec3 rgb;

    // ambient
    float ka;
    vec3 iamb;
    vec3 amb;
};

struct scanline_config
{
    scanline_config(int w, int h, uint8_t *buffer);
    ~scanline_config();

    light l;
    vec3 normal;
    float area;
    float *zbuffer;
    int w;
    int h;
    uint8_t *buffer;
};

// scanline auxilary functions
/**
 * @brief Paints the upper part of the triangle.
 *
 * @param a sub-triangle a vertex
 * @param b sub-triangle b vertex
 * @param c sub-triangle c vertex
 */
void PaintUpper(
    vec3 const &a,
    vec3 const &b,
    vec3 const &c);

/**
 * @brief Paints the lower part of the triangle.
 *
 * @param a sub-triangle a vertex
 * @param b sub-triangle b vertex
 * @param c sub-triangle c vertex
 * @param buffer pixel buffer
 * @param w pixel buffer width
 * @param h pixel buffer height
 */
void PaintLower(
    vec3 const &a,
    vec3 const &b,
    vec3 const &c);

/**
 * @brief sorts a list of 3 vec3s by y
 *
 * @param vs
 */
void Sorted(vec3 *vs);

/**
 * @brief paints a pixel at x,y
 *
 * @param a vertex a of the triangle
 * @param b vertex b of the triangle
 * @param c vertex c of the triangle
 * @param x x position of the pixel
 * @param y y position of the pixel
 */
void PaintPixel(vec3 const &a,
                vec3 const &b,
                vec3 const &c,
                int x, int y);

/**
 * @brief Get rgb vector of a pixel at p.
 *
 * @param a
 * @param b
 * @param c
 * @param p
 * @return vec3
 */
vec3 GetColor(vec3 const &a,
              vec3 const &b,
              vec3 const &c,
              vec3 const &p);