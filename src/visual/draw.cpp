/*
 * draw.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: nullifiedcat
 */

#include "visual/draw.hpp"
#include "interfaces.hpp"
#include <cdll_int.h>

namespace draw
{

namespace fonts
{

draw_api::font_handle_t tf2build_large{};
draw_api::font_handle_t tf2build{};

}

int width{ 0 };
int height{ 0 };

void init()
{
    // TODO change it to font path
    fonts::tf2build = draw_api::create_font("TF2BUILD", 18);
    fonts::tf2build_large = draw_api::create_font("TF2BUILD", 30);
    I<IVEngineClient013>()->GetScreenSize(width, height);
}

}
