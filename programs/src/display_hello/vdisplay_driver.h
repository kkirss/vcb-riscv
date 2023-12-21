
const unsigned int WORD_SIZE = 32;

extern unsigned int __DISPLAY_POINTER_ADDRESS__;
const unsigned int FRAME_BUFFER_POINTER_ADDR = __DISPLAY_POINTER_ADDRESS__;

void configure_display(unsigned int x, unsigned int y, unsigned int color_depth);
unsigned int* allocate_frame_buffer();
void display_frame_buffer(unsigned int* frame_buffer);

void set_pixel_1b(unsigned int x, unsigned int y, unsigned int new_color, unsigned int* frame_buffer);
