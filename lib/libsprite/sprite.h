#pragma once

#include <array>
#include <type_traits>

using std::array;

template <typename PIXEL_T, unsigned int WIDTH, unsigned int HEIGHT>
struct Sprite {
    const array<array<PIXEL_T, WIDTH>, HEIGHT> pixels;
    static const unsigned int width = WIDTH;
    static const unsigned int height = HEIGHT;
};

template <typename T>
struct is_sprite : std::false_type {};

template <typename PIXEL_T, unsigned int WIDTH, unsigned int HEIGHT>
struct is_sprite<Sprite<PIXEL_T, WIDTH, HEIGHT>> : std::true_type {};

template <typename T>
concept IsSprite = is_sprite<T>::value;
