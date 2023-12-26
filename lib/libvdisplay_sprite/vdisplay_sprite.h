#pragma once

#include "sprite.h"
#include "vdisplay_driver.h"

template <IsSprite SpriteType>
static void draw_sprite(const unsigned int x_pos,
                        const unsigned int y_pos,
                        const SpriteType &sprite,
                        const DisplayConfig &display_config,
                        unsigned int *frame_buffer) {
    for (unsigned int y = 0; y < SpriteType::height; ++y) {
        for (unsigned int x = 0; x < SpriteType::width; ++x) {
            draw_pixel(
                x_pos + x, y_pos + y, sprite.pixels[y][x], display_config, frame_buffer);
        }
    }
}
