#include "vdisplay_driver.h"
#include "simple_font.h"

constexpr unsigned int DISPLAY_WIDTH_PIXELS = 192;
constexpr unsigned int DISPLAY_HEIGHT_PIXELS = 96;
constexpr unsigned int DISPLAY_COLOR_DEPTH = 1;

typedef Display<DISPLAY_WIDTH_PIXELS, DISPLAY_HEIGHT_PIXELS, DISPLAY_COLOR_DEPTH> display;

int main() {
    display_frame_buffer(display::frame_buffer_a);

    display::draw_sprite(1, 1, SimpleFont::H, display::frame_buffer_a);
    display::draw_sprite(1 + 5, 1, SimpleFont::I, display::frame_buffer_a);
}
