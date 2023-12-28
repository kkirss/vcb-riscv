#include "simple_font.h"
#include "vdisplay_driver.h"
#include "vdisplay_sprite.h"

inline volatile unsigned int BREAKPOINT __attribute__((used, section(".breakpoint")));

constexpr unsigned int DISPLAY_WIDTH_PIXELS = 192;
constexpr unsigned int DISPLAY_HEIGHT_PIXELS = 96;
constexpr unsigned int DISPLAY_COLOR_DEPTH = 1;

constexpr DisplayConfig
    display_config(DISPLAY_WIDTH_PIXELS, DISPLAY_HEIGHT_PIXELS, DISPLAY_COLOR_DEPTH);

typedef DisplayBuffers<display_config> display_buffers;

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
    display_frame_buffer<display_config>(display_buffers::a);

    unsigned int x = 1;
    for (const auto &sprite : HELLO_WORLD) {
        draw_sprite<display_config>(x, 1, sprite, display_buffers::a);
        x += SimpleFont::SpriteType::width + 1;
    }
}
