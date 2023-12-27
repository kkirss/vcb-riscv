#pragma once

#include <array>
#include <type_traits>

using std::array;

template <unsigned int WIDTH, unsigned int HEIGHT>
struct Sprite {
    const array<array<unsigned int, WIDTH>, HEIGHT> pixels;
    static const unsigned int width = WIDTH;
    static const unsigned int height = HEIGHT;
};

template <typename T>
struct is_sprite : std::false_type {};

template <unsigned int WIDTH, unsigned int HEIGHT>
struct is_sprite<Sprite<WIDTH, HEIGHT>> : std::true_type {};

template <typename T>
concept IsSprite = is_sprite<T>::value;
