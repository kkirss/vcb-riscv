#include "vdisplay_driver.h"


void display_frame_buffer(const unsigned int &frame_buffer_start) {
    // Divide by 4 as VMEM address is in words
    frame_buffer_pointer = reinterpret_cast<unsigned int>(&frame_buffer_start) >> 2;
}

void set_pixel_1b(unsigned int x, unsigned int y, unsigned int new_color, unsigned int &frame_buffer_start) {
    // TODO: What if pixels don't align with word boundaries?
    // TODO: Ensure that display dimensions are multiples of word size

    // Calculate the sequential pixel number within the frame buffer
    const unsigned int sequential_pixel_number = x + (y * DISPLAY_WIDTH_PIXELS);

    // Calculate the word address within the frame buffer
    const unsigned int mem_word_address = sequential_pixel_number / WORD_SIZE;

    // Calculate the actual memory address to be accessed
    volatile unsigned int* pixel_word = reinterpret_cast<unsigned int*>(&frame_buffer_start) + mem_word_address;

    // Calculate the bit mask for the pixel
    const unsigned int mem_pixel_mask = 1 << (WORD_SIZE - (sequential_pixel_number % WORD_SIZE) - 1);

    // Set or clear the pixel based on new_color
    if (new_color == 1) {
        *pixel_word |= mem_pixel_mask;
    } else {
        *pixel_word &= ~mem_pixel_mask;
    }
}
