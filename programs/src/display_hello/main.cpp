#include "vdisplay_driver.h"

unsigned int CPU_V_0_1_DISPLAY_SIZE_X = 180;
unsigned int CPU_V_0_1_DISPLAY_SIZE_Y = 60;

void write_h_letter(unsigned int origin_x, unsigned int origin_y, unsigned int* frame_buffer) {
    set_pixel_1b(origin_x + 0, origin_x + 0, 1, frame_buffer);
    set_pixel_1b(origin_x + 0, origin_x + 1, 1, frame_buffer);
    set_pixel_1b(origin_x + 0, origin_x + 2, 1, frame_buffer);
    set_pixel_1b(origin_x + 0, origin_x + 3, 1, frame_buffer);
    set_pixel_1b(origin_x + 0, origin_x + 4, 1, frame_buffer);

    set_pixel_1b(origin_x + 1, origin_x + 2, 1, frame_buffer);

    set_pixel_1b(origin_x + 2, origin_x + 2, 1, frame_buffer);

    set_pixel_1b(origin_x + 3, origin_x + 0, 1, frame_buffer);
    set_pixel_1b(origin_x + 3, origin_x + 1, 1, frame_buffer);
    set_pixel_1b(origin_x + 3, origin_x + 2, 1, frame_buffer);
    set_pixel_1b(origin_x + 3, origin_x + 3, 1, frame_buffer);
    set_pixel_1b(origin_x + 3, origin_x + 4, 1, frame_buffer);
}

int main() {
    configure_display(CPU_V_0_1_DISPLAY_SIZE_X, CPU_V_0_1_DISPLAY_SIZE_Y, 1);
    unsigned int* frame_buffer_a = allocate_frame_buffer();
    display_frame_buffer(frame_buffer_a);
    set_pixel_1b(30, 30, 1, frame_buffer_a);
    // write_h_letter(1, 3, frame_buffer_a);
}
