/*
 * draw.hpp
 *
 *  Created on: Jan 4, 2018
 *      Author: nullifiedcat
 */

#pragma once

#include "visual/surface.hpp"

#define draw_api draw_api_surface

namespace draw
{

namespace fonts
{

extern draw_api::font_handle_t tf2build_large;
extern draw_api::font_handle_t tf2build;

}

extern int width;
extern int height;

void init();

}
