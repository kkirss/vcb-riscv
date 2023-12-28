#pragma once

#include "sprite.h"
#include "vdisplay_driver.h"

template <DisplayConfig display_config, unsigned int SPRITE_WIDTH, unsigned int SPRITE_HEIGHT>
static void draw_sprite(const unsigned int x_pos,
                        const unsigned int y_pos,
                        const Sprite<SPRITE_WIDTH, SPRITE_HEIGHT> &sprite,
                        FrameBuffer &frame_buffer) {
    for (unsigned int y = 0; y < SPRITE_HEIGHT; ++y) {
        for (unsigned int x = 0; x < SPRITE_WIDTH; ++x) {
            draw_pixel<display_config>(x_pos + x, y_pos + y, sprite.pixels[y][x], frame_buffer);
        }
    }
}
