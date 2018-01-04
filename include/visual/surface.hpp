/*
 * surface.hpp
 *
 *  Created on: Jan 4, 2018
 *      Author: nullifiedcat
 */

#pragma once

#include "colors.hpp"

namespace draw_api_surface
{

typedef unsigned long font_t;
typedef unsigned long texture_t;
typedef unsigned long color_t;

struct font_handle_t
{
    unsigned long font;
};

font_handle_t create_font(const char *path, float size);
void destroy_font(font_handle_t font);

bool ready();

void initialize();

void draw_rect(float x, float y, float w, float h, const colors::rgba_t &rgba);
void draw_rect_outlined(float x, float y, float w, float h, const colors::rgba_t &rgba,
                        float thickness);
void draw_line(float x, float y, float dx, float dy, const colors::rgba_t &rgba,
               float thickness);
void draw_circle(float x, float y, float radius, const colors::rgba_t &rgba,
                 float thickness, int steps);

// Both of these functions draw string with outline.
void draw_string(float x, float y, const char *string, font_handle_t &font,
                 const colors::rgba_t &rgba);
void draw_string_with_outline(float x, float y, const char *string,
                              font_handle_t &font, const colors::rgba_t &rgba,
                              const colors::rgba_t &rgba_outline, float thickness);

// Not implemented
void get_string_size(const char *string, font_handle_t &font, float *x,
                     float *y);

void draw_begin();
void draw_end();

}
