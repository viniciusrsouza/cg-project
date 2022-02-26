#pragma once

/**
 * @brief Entry point of wasm application.
 *
 * @param asset_path  path to byu file to be rendered.
 * @param camera_path path to file descipting camera.
 * @param buffer      path to output pixel buffer.
 * @param w           width of output buffer.
 * @param h           height of output buffer.
 */
int render(
    const char *asset_path,
    const float *camera_values,
    unsigned char *buffer,
    int w, int h);