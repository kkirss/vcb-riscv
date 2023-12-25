#include "simple_font.h"
#include "vdisplay_driver.h"
#include "vdisplay_sprite.h"

constexpr unsigned int DISPLAY_WIDTH_PIXELS = 192;
constexpr unsigned int DISPLAY_HEIGHT_PIXELS = 96;
constexpr unsigned int DISPLAY_COLOR_DEPTH = 1;

typedef Display<DISPLAY_WIDTH_PIXELS, DISPLAY_HEIGHT_PIXELS, DISPLAY_COLOR_DEPTH> display;

constexpr SimpleFont::SpriteType HELLO_WORLD[] = {
    SimpleFont::H,
    SimpleFont::E,
    SimpleFont::L,
    SimpleFont::L,
    SimpleFont::O,
    SimpleFont::SPACE,
    SimpleFont::W,
    SimpleFont::O,
    SimpleFont::R,
    SimpleFont::L,
    SimpleFont::D,
    SimpleFont::EXCLAMATION_MARK,
};

int main() {
    display_frame_buffer(display::frame_buffer_a);

    unsigned int x = 0;
    for (const auto &sprite : HELLO_WORLD) {
        draw_sprite<display>(x, 0, sprite, display::frame_buffer_a);
        x += SimpleFont::SpriteType::width + 1;
    }
}
