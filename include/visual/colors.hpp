/*
 * colors.hpp
 *
 *  Created on: Jan 4, 2018
 *      Author: nullifiedcat
 */

#pragma once

#include <cstdint>

#include <Color.h>

namespace colors
{

struct rgba_t
{
    union {
        struct
        {
            float r, g, b, a;
        };
        float rgba[4];
    };

    constexpr rgba_t() : r(0.0f), g(0.0f), b(0.0f), a(0.0f){};
    constexpr rgba_t(float _r, float _g, float _b, float _a = 1.0f)
        : r(_r), g(_g), b(_b), a(_a){};

    constexpr operator bool() const
    {
        return r || g || b || a;
    }

    constexpr operator int() const = delete;

    operator float *()
    {
        return rgba;
    }

    constexpr operator const float *() const
    {
        return rgba;
    }

    constexpr rgba_t operator*(float value) const
    {
        return rgba_t(r * value, g * value, b * value, a * value);
    }

    constexpr operator unsigned() const
    {
        return unsigned(
                uint8_t(r * 255) << 24 |
                uint8_t(g * 255) << 16 |
                uint8_t(b * 255) << 8 |
                uint8_t(a * 255)
        );
    }

    operator Color() const
    {
        return Color(r * 255, g * 255, b * 255, a * 255);
    }
};

constexpr rgba_t rgba8(float r, float g, float b, float a)
{
    return rgba_t{ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f };
}

constexpr rgba_t transparent(const rgba_t &in, float multiplier = 0.5f)
{
    return rgba_t{ in.r, in.g, in.b, in.a * multiplier };
}

constexpr rgba_t white{ 1, 1, 1, 1 };
constexpr rgba_t black{ 0, 0, 0, 1 };

constexpr rgba_t pink = rgba8(255, 105, 180, 255);
constexpr rgba_t empty  = rgba8(0, 0, 0, 0);

constexpr rgba_t hsl(float h, float s, float v)
{
    if (s <= 0.0)
    { // < is bogus, just shuts up warnings
        return rgba_t{ v, v, v, 1.0f };
    }
    float hh = h;
    if (hh >= 360.0)
        hh = 0.0;
    hh /= 60.0;
    long i   = long(hh);
    float ff = hh - i;
    float p  = v * (1.0 - s);
    float q  = v * (1.0 - (s * ff));
    float t  = v * (1.0 - (s * (1.0 - ff)));

    switch (i)
    {
    case 0:
        return rgba_t{ v, t, p, 1.0f };
    case 1:
        return rgba_t{ q, v, p, 1.0f };
    case 2:
        return rgba_t{ p, v, t, 1.0f };
    case 3:
        return rgba_t{ p, q, v, 1.0f };
        break;
    case 4:
        return rgba_t{ t, p, v, 1.0f };
    case 5:
    default:
        return rgba_t{ v, p, q, 1.0f };
    }
}
constexpr rgba_t health(int hp, int max)
{
    float hf = float(hp) / float(max);
    if (hf > 1)
    {
        return colors::rgba8(64, 128, 255, 255);
    }
    return rgba_t{ (hf <= 0.5f ? 1.0f : 1.0f - 2.0f * (hf - 0.5f)),
                   (hf <= 0.5f ? (2.0f * hf) : 1.0f), 0.0f, 1.0f };
}

}
