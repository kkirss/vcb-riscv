#include "vdisplay_driver.h"

// Co-ordinates originate from top-left

unsigned int display_size_x;
unsigned int display_size_y;
unsigned int display_color_depth;

void configure_display(unsigned int x, unsigned int y, unsigned int color_depth) {
    display_size_x = x;
    display_size_y = y;
    display_color_depth = color_depth;
}

unsigned int* allocate_frame_buffer() {
    const unsigned int total_display_bits = display_size_x * display_size_y * display_color_depth;
    // unsigned int* frame_buffer = new unsigned int[total_display_bits / WORD_SIZE];
    // TODO: Use proper allocation here
    const unsigned int frame_buffer_address = FRAME_BUFFER_POINTER_ADDR + 8;
    unsigned int *frame_buffer = reinterpret_cast<unsigned int*>(frame_buffer_address);
    return frame_buffer;
}

void display_frame_buffer(unsigned int* frame_buffer) {
    volatile unsigned int *display_frame_buffer = reinterpret_cast<unsigned int*>(FRAME_BUFFER_POINTER_ADDR);
    *display_frame_buffer = (unsigned int) &frame_buffer;
}

// TODO: test
void set_pixel_1b(unsigned int x, unsigned int y, unsigned int new_color, unsigned int* frame_buffer) {
    const unsigned int frame_buffer_origin_address = (unsigned int) &frame_buffer;
    const unsigned int mem_bit_address = frame_buffer_origin_address * WORD_SIZE + x + y * display_size_x;

    const unsigned int mem_word_address = mem_bit_address / WORD_SIZE;
    volatile unsigned int *pixel_word = reinterpret_cast<unsigned int*>(mem_word_address);

    const unsigned int mem_pixel_mask = 1 << (mem_bit_address % WORD_SIZE);
    const unsigned int mem_pixel_set = *pixel_word & mem_pixel_mask;

    if (new_color == 0 && mem_pixel_set) {
        *pixel_word |= mem_pixel_mask;
    } else if (new_color == 0 && !mem_pixel_set) {
        *pixel_word &= ~mem_pixel_mask;
    }
}
