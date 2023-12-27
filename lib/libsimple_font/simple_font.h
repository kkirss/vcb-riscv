#pragma once

#include "sprite.h"

namespace SimpleFont {
typedef Sprite<4, 5> SpriteType;

inline constexpr SpriteType D = {{{
    {1, 1, 1, 0},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 1, 1, 0},
}}};
inline constexpr SpriteType E = {{{
    {1, 1, 1, 1},
    {1, 0, 0, 0},
    {1, 1, 1, 0},
    {1, 0, 0, 0},
    {1, 1, 1, 1},
}}};
inline constexpr SpriteType H = {{{
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 1, 1, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
}}};
inline constexpr SpriteType I = {{{
    {1, 1, 1, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {1, 1, 1, 0},
}}};
inline constexpr SpriteType L = {{{
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 1, 1, 1},
}}};
inline constexpr SpriteType O = {{{
    {0, 1, 1, 0},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {0, 1, 1, 0},
}}};
inline constexpr SpriteType R = {{{
    {1, 1, 1, 0},
    {1, 0, 0, 1},
    {1, 1, 1, 0},
    {1, 0, 1, 0},
    {1, 0, 0, 1},
}}};
inline constexpr SpriteType W = {{{
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 1, 0, 1},
    {1, 1, 1, 1},
    {1, 0, 1, 0},
}}};
inline constexpr SpriteType SPACE = {{{
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
}}};
inline constexpr SpriteType EXCLAMATION_MARK = {{{
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 0},
    {0, 1, 0, 0},
}}};
}; // namespace SimpleFont
