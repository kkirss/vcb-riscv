OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv", "elf32-littleriscv")
OUTPUT_ARCH(riscv)

ENTRY(_start)

STACK_SIZE = DEFINED( STACK_SIZE ) ? STACK_SIZE : 4K;

MEMORY
{
    /* 4096K bytes is max size of VMEM (20 bit address of 32-bit word -> 2^20 * (32/8) = 4096K) */
    RAM (rwx) : ORIGIN = 0x4, LENGTH = 4096K - 0x4
}

SEC_ALIGN = 32;

SECTIONS
{
    . = ORIGIN(RAM);

    .init :
    {
        KEEP (*(SORT_NONE(.init)))
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

    .stack ORIGIN(RAM) + LENGTH(RAM) - STACK_SIZE : {
        FILL(0);
        PROVIDE(__STACK_START__ = .);
        . += STACK_SIZE;
        PROVIDE(__C_STACK_TOP__ = .);
        PROVIDE(__STACK_END__ = .);
    } > RAM
}
