#pragma once

template<typename T, unsigned int WIDTH, unsigned int HEIGHT>
struct Sprite {
    T pixels[HEIGHT][WIDTH];
    static const unsigned int width = WIDTH;
    static const unsigned int height = HEIGHT;
};
