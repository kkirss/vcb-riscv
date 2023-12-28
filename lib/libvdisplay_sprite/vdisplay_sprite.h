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

#define SpriteGridTemplTypes                                                                       \
    unsigned int GRID_WIDTH, unsigned int GRID_HEIGHT, unsigned int SPRITE_WIDTH,                  \
        unsigned int SPRITE_HEIGHT, unsigned int X, unsigned int Y, unsigned int PADDING_X,        \
        unsigned int PADDING_Y

#define SpriteGridT                                                                                \
    SpriteGrid<GRID_WIDTH, GRID_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT, X, Y, PADDING_X, PADDING_Y>

template <SpriteGridTemplTypes>
struct SpriteGrid {
    static constexpr unsigned int grid_width = GRID_WIDTH;
    static constexpr unsigned int grid_height = GRID_HEIGHT;

    static constexpr unsigned int sprite_width = SPRITE_WIDTH;
    static constexpr unsigned int sprite_height = SPRITE_HEIGHT;

    static constexpr unsigned int x = X;
    static constexpr unsigned int y = Y;

    static constexpr unsigned int padding_x = PADDING_X;
    static constexpr unsigned int padding_y = PADDING_Y;

    unsigned int cursor_x = 0;
    unsigned int cursor_y = 0;

    const unsigned int grid_size = grid_width * grid_height;

    [[nodiscard]] unsigned int cursor_display_x() const {
        return x + cursor_x * (sprite_width + padding_x);
    }
    [[nodiscard]] unsigned int cursor_display_y() const {
        return y + cursor_y * (sprite_height + padding_y);
    }
};

template <SpriteGridTemplTypes>
void increment_cursor(SpriteGridT &sprite_grid) {
    if (sprite_grid.cursor_x < sprite_grid.grid_width - 1) {
        ++sprite_grid.cursor_x;
        return;
    }
    if (sprite_grid.cursor_y < sprite_grid.grid_height - 1) {
        sprite_grid.cursor_x = 0;
        ++sprite_grid.cursor_y;
    }
}

template <SpriteGridTemplTypes>
void decrement_cursor(SpriteGridT &sprite_grid) {
    if (sprite_grid.cursor_x > 0) {
        --sprite_grid.cursor_x;
        return;
    }
    if (sprite_grid.cursor_y > 0) {
        sprite_grid.cursor_x = sprite_grid.grid_width - 1;
        --sprite_grid.cursor_y;
    }
}

template <DisplayConfig display_config, SpriteGridTemplTypes>
static void draw_sprite(SpriteGridT &sprite_grid,
                        const Sprite<SPRITE_WIDTH, SPRITE_HEIGHT> &sprite,
                        FrameBuffer &frame_buffer) {
    unsigned int x_pos = sprite_grid.cursor_display_x();
    unsigned int y_pos = sprite_grid.cursor_display_y();
    draw_sprite<display_config>(x_pos, y_pos, sprite, frame_buffer);
    increment_cursor(sprite_grid);
}
