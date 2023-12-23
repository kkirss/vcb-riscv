#include "vdisplay_driver.h"

const unsigned int DISPLAY_WIDTH_PIXELS = 192;
const unsigned int DISPLAY_HEIGHT_PIXELS = 96;
const unsigned int DISPLAY_COLOR_DEPTH = 1;

void write_h_letter(unsigned int origin_x, unsigned int origin_y, unsigned int &frame_buffer_start) {
    set_pixel_1b(origin_x + 0, origin_y + 0, 1, frame_buffer_start);
    set_pixel_1b(origin_x + 3, origin_y + 0, 1, frame_buffer_start);

    set_pixel_1b(origin_x + 0, origin_y + 1, 1, frame_buffer_start);
    set_pixel_1b(origin_x + 3, origin_y + 1, 1, frame_buffer_start);

    set_pixel_1b(origin_x + 0, origin_y + 2, 1, frame_buffer_start);
    set_pixel_1b(origin_x + 1, origin_y + 2, 1, frame_buffer_start);
    set_pixel_1b(origin_x + 2, origin_y + 2, 1, frame_buffer_start);
    set_pixel_1b(origin_x + 3, origin_y + 2, 1, frame_buffer_start);

    set_pixel_1b(origin_x + 0, origin_y + 3, 1, frame_buffer_start);
    set_pixel_1b(origin_x + 3, origin_y + 3, 1, frame_buffer_start);

    set_pixel_1b(origin_x + 0, origin_y + 4, 1, frame_buffer_start);
    set_pixel_1b(origin_x + 3, origin_y + 4, 1, frame_buffer_start);
}

void write_i_letter(unsigned int origin_x, unsigned int origin_y, unsigned int &frame_buffer_start) {
    set_pixel_1b(origin_x + 0, origin_y + 0, 1, frame_buffer_start);
    set_pixel_1b(origin_x + 1, origin_y + 0, 1, frame_buffer_start);
    set_pixel_1b(origin_x + 2, origin_y + 0, 1, frame_buffer_start);

    set_pixel_1b(origin_x + 1, origin_y + 1, 1, frame_buffer_start);

    set_pixel_1b(origin_x + 1, origin_y + 2, 1, frame_buffer_start);

    set_pixel_1b(origin_x + 1, origin_y + 3, 1, frame_buffer_start);

    set_pixel_1b(origin_x + 0, origin_y + 4, 1, frame_buffer_start);
    set_pixel_1b(origin_x + 1, origin_y + 4, 1, frame_buffer_start);
    set_pixel_1b(origin_x + 2, origin_y + 4, 1, frame_buffer_start);
}

int main() {
    display_frame_buffer(frame_buffer_a_start);

    write_h_letter(1, 1, frame_buffer_a_start);
    write_i_letter(1 + 5, 1, frame_buffer_a_start);
}
