#pragma once

// Co-ordinates originate from top-left

const unsigned int WORD_SIZE = 32;

extern const unsigned int DISPLAY_WIDTH_PIXELS;
extern const unsigned int DISPLAY_HEIGHT_PIXELS;
extern const unsigned int DISPLAY_COLOR_DEPTH;

inline unsigned int __attribute__((used, section (".display_buffers"))) frame_buffer_a_start;

inline unsigned int __attribute__((used, section (".display_pointer"))) frame_buffer_pointer;

void display_frame_buffer(const unsigned int &frame_buffer_start);

void set_pixel_1b(unsigned int x, unsigned int y, unsigned int new_color, unsigned int &frame_buffer_start);
