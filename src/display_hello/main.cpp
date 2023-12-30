#include "simple_font.h"
#include "simple_font_key_map.h"
#include "vdisplay_driver.h"
#include "vdisplay_sprite.h"
#include "vinput_driver.h"

using namespace VInputKeys;

inline volatile unsigned int BREAKPOINT __attribute__((used, section(".breakpoint")));

constexpr unsigned int DISPLAY_WIDTH_PIXELS = 192;
constexpr unsigned int DISPLAY_HEIGHT_PIXELS = 96;
constexpr unsigned int DISPLAY_COLOR_DEPTH = 1;

constexpr DisplayConfig
    display_config(DISPLAY_WIDTH_PIXELS, DISPLAY_HEIGHT_PIXELS, DISPLAY_COLOR_DEPTH);

typedef DisplayBuffers<display_config> display_buffers;

constexpr unsigned int GRID_X = 1;
constexpr unsigned int GRID_Y = 1;
constexpr unsigned int GRID_PADDING_X = 1;
constexpr unsigned int GRID_PADDING_Y = 1;

constexpr unsigned int GRID_WIDTH =
    (display_config.width - GRID_X) / (SimpleFont::SPRITE_WIDTH + GRID_PADDING_X);
constexpr unsigned int GRID_HEIGHT =
    (display_config.height - GRID_Y) / (SimpleFont::SPRITE_HEIGHT + GRID_PADDING_Y);

SpriteGrid<GRID_WIDTH,
           GRID_HEIGHT,
           SimpleFont::SPRITE_WIDTH,
           SimpleFont::SPRITE_HEIGHT,
           GRID_X,
           GRID_Y,
           GRID_PADDING_X,
           GRID_PADDING_Y>
    sprite_grid;

constexpr array VCB_RISCV = {
    SimpleFont::V,
    SimpleFont::C,
    SimpleFont::B,
    SimpleFont::MINUS,
    SimpleFont::R,
    SimpleFont::I,
    SimpleFont::S,
    SimpleFont::C,
    SimpleFont::V,
};

void draw_vcb_riscv() {
    for (const auto &sprite : VCB_RISCV) {
        draw_sprite<display_config>(sprite_grid, sprite, display_buffers::a);
    }
}

void on_key_press(const Key key) {
    switch (key) {
    case Keys::BACKSPACE:
        decrement_cursor(sprite_grid);
        break;
    case Keys::ENTER:
    case Keys::KEYPAD_ENTER:
        move_cursor_new_line(sprite_grid);
        break;
    default:
        const SimpleFont::SpriteType *sprite = SimpleFont::get_key_sprite(key);

        if (sprite != nullptr) {
            draw_sprite<display_config>(sprite_grid, *sprite, display_buffers::a);
        }
    }
}

int main() {
    display_frame_buffer<display_config>(display_buffers::a);

    draw_vcb_riscv();
    move_cursor_new_line(sprite_grid);
    move_cursor_new_line(sprite_grid);

    Key last_key = Keys::NONE;

    while (true) {
        const Key pressed_key = read_virtual_input_key();

        if (pressed_key == last_key) {
            continue;
        }
        last_key = pressed_key;

        switch (pressed_key) {
        case Keys::ESCAPE:
            break;
        case Keys::NONE:
            continue;
        default:
            on_key_press(pressed_key);
        }
    }
}
