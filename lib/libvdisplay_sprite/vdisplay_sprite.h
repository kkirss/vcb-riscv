#pragma once

#include "sprite.h"
#include "vdisplay_driver.h"

template<IsDisplay DisplayType, IsSprite SpriteType>
static void draw_sprite(const unsigned int x_pos, const unsigned int y_pos, const SpriteType& sprite, unsigned int *frame_buffer) {
    for (unsigned int y = 0; y < SpriteType::height; ++y) {
        for (unsigned int x = 0; x < SpriteType::width; ++x) {
            DisplayType::set_pixel_1b(x_pos + x, y_pos + y, sprite.pixels[y][x], frame_buffer);
        }
    }
}
