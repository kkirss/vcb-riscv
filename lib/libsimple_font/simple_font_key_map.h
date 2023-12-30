#pragma once

#include "vinput_key.h"

using namespace VInputKeys;

namespace SimpleFont {
struct SimpleFontKeyMap {
    Key key;
    const Sprite<SPRITE_WIDTH, SPRITE_HEIGHT> *sprite;
};

static constexpr array<SimpleFontKeyMap, 40> key_map = {{
    {Keys::A, &A},         {Keys::B, &B},         {Keys::C, &C},         {Keys::D, &D},
    {Keys::E, &E},         {Keys::F, &F},         {Keys::G, &G},         {Keys::H, &H},
    {Keys::I, &I},         {Keys::J, &J},         {Keys::K, &K},         {Keys::L, &L},
    {Keys::M, &M},         {Keys::N, &N},         {Keys::O, &O},         {Keys::P, &P},
    {Keys::Q, &Q},         {Keys::R, &R},         {Keys::S, &S},         {Keys::T, &T},
    {Keys::U, &U},         {Keys::V, &V},         {Keys::W, &W},         {Keys::X, &X},
    {Keys::Y, &Y},         {Keys::Z, &Z},         {Keys::_1, &_1},       {Keys::_2, &_2},
    {Keys::_3, &_3},       {Keys::_4, &_4},       {Keys::_5, &_5},       {Keys::_6, &_6},
    {Keys::_7, &_7},       {Keys::_8, &_8},       {Keys::_9, &_9},       {Keys::_0, &_0},
    {Keys::SPACE, &SPACE}, {Keys::MINUS, &MINUS}, {Keys::COMMA, &COMMA}, {Keys::PERIOD, &PERIOD},
}};

typedef array<const Sprite<SPRITE_WIDTH, SPRITE_HEIGHT> *, 102> Sprites;

static constexpr Sprites KEY_SPRITES = [] {
    Sprites key_sprites{};
    for (const auto [key, sprite] : key_map) {
        key_sprites[key] = sprite;
    }
    return key_sprites;
}();

static const SpriteType *get_key_sprite(const Key key) { return KEY_SPRITES[key]; }

} // namespace SimpleFont
