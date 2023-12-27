#pragma once

#include "sprite.h"
#include "vdisplay_driver.h"

template <DisplayConfig display_config, IsSprite SpriteType>
static void draw_sprite(const unsigned int x_pos,
                        const unsigned int y_pos,
                        const SpriteType &sprite,
                        FrameBuffer &frame_buffer) {
    for (unsigned int y = 0; y < SpriteType::height; ++y) {
        for (unsigned int x = 0; x < SpriteType::width; ++x) {
            draw_pixel<display_config>(x_pos + x, y_pos + y, sprite.pixels[y][x], frame_buffer);
        }
    }
}
