# Parts taken from: https://github.com/syntacore/sc-bl/blob/master/common/scbl.ld

OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv", "elf32-littleriscv")
OUTPUT_ARCH(riscv)

ENTRY(rvtest_entry_point)

# Use variables to allow configuring from the command line

# Size of RAM (in bytes)
RAM_SIZE = DEFINED( RAM_SIZE ) ? RAM_SIZE : 4096K;

# Address for the the top of stack
# Will start growing to lower addresses (as is RISC-V convention)
STACK_TOP = DEFINED( STACK_TOP ) ? STACK_TOP : ORIGIN(RAM) + LENGTH(RAM);

# Size of the stack in bytes
# Note: This doesn't implement any stack overflow checking.
#       This just ensures this amount of memory is reserved for the stack.
# Note: There is a 16 byte pad at the top of the stack, just in case
STACK_SIZE = DEFINED( STACK_SIZE ) ? STACK_SIZE : 4K;

SEC_ALIGN = 32;
STACK_PAD = 16;

MEMORY
{
    RAM (rwx) : ORIGIN = 0x0, LENGTH = RAM_SIZE
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

    .stack STACK_TOP - STACK_SIZE : {
        FILL(0);
        PROVIDE(__STACK_START__ = .);
        . += (STACK_SIZE - STACK_PAD);
        PROVIDE(__C_STACK_TOP__ = .);
        PROVIDE(__STACK_END__ = .);
        . += STACK_PAD;
    } > RAM

    _end = .;
}
