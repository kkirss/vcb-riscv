#pragma once

#include "sprite.h"

namespace SimpleFont {
typedef Sprite<4, 5> SpriteType;

inline constexpr SpriteType A = {{{
    {0, 1, 1, 0},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 1, 1, 1},
    {1, 0, 0, 1},
}}};
inline constexpr SpriteType B = {{{
    {1, 1, 1, 0},
    {1, 0, 0, 1},
    {1, 1, 1, 0},
    {1, 0, 0, 1},
    {1, 1, 1, 0},
}}};
inline constexpr SpriteType C = {{{
    {0, 1, 1, 1},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {0, 1, 1, 1},
}}};
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
inline constexpr SpriteType F = {{{
    {1, 1, 1, 1},
    {1, 0, 0, 0},
    {1, 1, 1, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
}}};
inline constexpr SpriteType G = {{{
    {0, 1, 1, 1},
    {1, 0, 0, 0},
    {1, 0, 1, 1},
    {1, 0, 0, 1},
    {0, 1, 1, 0},
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
inline constexpr SpriteType J = {{{
    {1, 1, 1, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1},
    {0, 1, 1, 0},
}}};
inline constexpr SpriteType K = {{{
    {1, 0, 0, 1},
    {1, 0, 1, 0},
    {1, 1, 0, 0},
    {1, 0, 1, 0},
    {1, 0, 0, 1},
}}};
inline constexpr SpriteType L = {{{
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 1, 1, 1},
}}};
inline constexpr SpriteType M = {{{
    {1, 0, 1, 1},
    {1, 1, 1, 1},
    {1, 1, 0, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
}}};
inline constexpr SpriteType N = {{{
    {1, 0, 0, 1},
    {1, 1, 0, 1},
    {1, 0, 1, 1},
    {1, 0, 1, 1},
    {1, 0, 0, 1},
}}};
inline constexpr SpriteType O = {{{
    {0, 1, 1, 0},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {0, 1, 1, 0},
}}};
inline constexpr SpriteType P = {{{
    {1, 1, 1, 0},
    {1, 0, 0, 1},
    {1, 1, 1, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
}}};
inline constexpr SpriteType Q = {{{
    {0, 1, 1, 0},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 0, 1, 0},
    {0, 1, 0, 1},
}}};
inline constexpr SpriteType R = {{{
    {1, 1, 1, 0},
    {1, 0, 0, 1},
    {1, 1, 1, 0},
    {1, 0, 1, 0},
    {1, 0, 0, 1},
}}};
inline constexpr SpriteType S = {{{
    {0, 1, 1, 1},
    {1, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 1},
    {1, 1, 1, 0},
}}};
inline constexpr SpriteType T = {{{
    {1, 1, 1, 1},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
}}};
inline constexpr SpriteType U = {{{
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {0, 1, 1, 0},
}}};
inline constexpr SpriteType V = {{{
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 0, 1, 0},
    {1, 0, 1, 0},
    {0, 1, 0, 0},
}}};
inline constexpr SpriteType X = {{{
    {1, 0, 0, 1},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
}}};
inline constexpr SpriteType Y = {{{
    {1, 0, 0, 1},
    {1, 0, 1, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
}}};
inline constexpr SpriteType Z = {{{
    {1, 1, 1, 1},
    {0, 0, 1, 0},
    {0, 1, 0, 0},
    {1, 0, 0, 0},
    {1, 1, 1, 1},
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
