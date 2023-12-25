# Parts taken from: https://github.com/syntacore/sc-bl/blob/master/common/scbl.ld

OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv", "elf32-littleriscv")
OUTPUT_ARCH(riscv)

ENTRY(_start)

WORD_SIZE = 4;
SEC_ALIGN = 32;
STACK_PAD = 16;

# Use variables to allow configuring from the command line

# Size of RAM (in bytes)
__RAM_SIZE__ = DEFINED( __RAM_SIZE__ ) ? __RAM_SIZE__ : 4096K;

# Display pointer address
__DISPLAY_POINTER_ADDRESS__ = DEFINED( __DISPLAY_POINTER_ADDRESS__ ) ? __DISPLAY_POINTER_ADDRESS__ : __RAM_SIZE__ - WORD_SIZE;

# Address for the the top of stack
# Will start growing to lower addresses (as is RISC-V convention)
__STACK_TOP__ = DEFINED( __STACK_TOP__ ) ? __STACK_TOP__ : __DISPLAY_POINTER_ADDRESS__ - WORD_SIZE;

# Size of the stack in bytes
# Note: This doesn't implement any stack overflow checking.
#       This just ensures this amount of memory is reserved for the stack.
# Note: There is a 16 byte pad at the top of the stack, just in case
__STACK_SIZE__ = DEFINED( __STACK_SIZE__ ) ? __STACK_SIZE__ : 4K;

MEMORY
{
    RAM (rwx) : ORIGIN = 0x0, LENGTH = __RAM_SIZE__
    DISPLAY_POINTER (rw) : ORIGIN = __DISPLAY_POINTER_ADDRESS__, LENGTH = WORD_SIZE
}

SECTIONS
{
    . = ORIGIN(RAM);

    # The .init section is used for code that needs to be run before main (e.g. set the stack pointer)
    .text.init : {
        KEEP (*(SORT_NONE(.text.init)))
    } > RAM

    .text : {
        *(.text .text.*);
    } > RAM

    .rodata ALIGN(SEC_ALIGN) : {
        *(.srodata .srodata.*);
        *(.rodata .rodata.*);
        *(.rdata .rdata.*);
    } > RAM

    .data ALIGN(SEC_ALIGN) : {
        *(.data .data.*);
    } > RAM

    .sdata ALIGN(SEC_ALIGN) : {
        *(.sdata .sdata.*);
    } > RAM

    .sbss ALIGN(SEC_ALIGN) : {
        *(.sbss .sbss.*);
    } > RAM

    .bss ALIGN(SEC_ALIGN) : {
        *(.bss .bss.*);
    } > RAM

    .stack __STACK_TOP__ - __STACK_SIZE__ : {
        FILL(0);
        PROVIDE(__STACK_START__ = .);
        . += (__STACK_SIZE__ - STACK_PAD);
        PROVIDE(__C_STACK_TOP__ = .);
        PROVIDE(__STACK_END__ = .);
        . += STACK_PAD;
    } > RAM

    .display_pointer : {
        PROVIDE(__DISPLAY_POINTER_ADDRESS__ = .);
        KEEP (*(.display_pointer));
    } > DISPLAY_POINTER AT> RAM

    _end = .;
}
