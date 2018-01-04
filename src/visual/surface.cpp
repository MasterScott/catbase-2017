/*
 * surface.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: nullifiedcat
 */

#include "interfaces.hpp"

#include <vgui/ISurface.h>
#include <visual/surface.hpp>

namespace draw_api_surface
{

font_handle_t create_font(const char *path, float size)
{
    font_handle_t result{};
    result.font = I<vgui::ISurface>()->CreateFont();
    I<vgui::ISurface>()->SetFontGlyphSet(result.font, "TF2_BUILD", size, 200, 0, 0, vgui::ISurface::FONTFLAG_OUTLINE, 0, 0);
    return result;
}

void destroy_font(font_handle_t font)
{
    return;
}

bool ready()
{
    return true;
}

void initialize()
{

}

void draw_rect(float x, float y, float w, float h, const colors::rgba_t &rgba)
{
    I<vgui::ISurface>()->DrawSetColor(rgba);
    I<vgui::ISurface>()->DrawFilledRect(x, y, x + w, y + h);
}

void draw_rect_outlined(float x, float y, float w, float h, const colors::rgba_t &rgba,
                        float thickness)
{
    I<vgui::ISurface>()->DrawSetColor(rgba);
    I<vgui::ISurface>()->DrawOutlinedRect(x, y, x + w, y + h);
}

void draw_line(float x, float y, float dx, float dy, const colors::rgba_t &rgba,
               float thickness)
{
    I<vgui::ISurface>()->DrawSetColor(rgba);
    I<vgui::ISurface>()->DrawLine(x, y, x + dx, y + dy);
}

void draw_circle(float x, float y, float radius, const colors::rgba_t &rgba,
                 float thickness, int steps)
{
    I<vgui::ISurface>()->DrawSetColor(rgba);
    I<vgui::ISurface>()->DrawOutlinedCircle(x, y, radius, steps);
}

void draw_string(float x, float y, const char *string, font_handle_t &font,
                 const colors::rgba_t &rgba)
{
    if (!string)
        return;

    wchar_t wstring[1024] = { 0 };

    swprintf(wstring, 1024, L"%s", string);

    I<vgui::ISurface>()->DrawSetTextPos(x, y);
    I<vgui::ISurface>()->DrawSetTextFont(font.font);
    I<vgui::ISurface>()->DrawSetTextColor(rgba);
    I<vgui::ISurface>()->DrawPrintText(wstring, wcslen(wstring));
}

void draw_string_with_outline(float x, float y, const char *string,
                              font_handle_t &font, const colors::rgba_t &rgba,
                              const colors::rgba_t &rgba_outline, float thickness)
{
    if (!string)
        return;

    wchar_t wstring[1024] = { 0 };

    swprintf(wstring, 1024, L"%s", string);

    I<vgui::ISurface>()->DrawSetTextPos(x, y);
    I<vgui::ISurface>()->DrawSetTextFont(font.font);
    I<vgui::ISurface>()->DrawSetTextColor(rgba);
    I<vgui::ISurface>()->DrawPrintText(wstring, wcslen(wstring));
}

void get_string_size(const char *string, font_handle_t &font, float *x,
                     float *y)
{
    return;
}

void draw_begin()
{
    return;
}

void draw_end()
{
    return;
}
}
