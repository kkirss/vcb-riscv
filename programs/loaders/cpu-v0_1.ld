OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv", "elf32-littleriscv")
OUTPUT_ARCH(riscv)

ENTRY(_start)

MEMORY
{
    /* 4096K bytes is max size of VMEM (20 bit address of 32-bit word -> 2^20 * (32/8) = 4096K) */
    RAM (rwx) : ORIGIN = 0x4, LENGTH = 4096K - 0x4
}

SEC_ALIGN = 32;

SECTIONS
{
    . = ORIGIN(RAM);

    .text : {
        *(.text);
    } > RAM

    .rodata ALIGN(SEC_ALIGN) : {
        *(.srodata);
        *(.rodata);
        *(.rdata);
    } > RAM

    .data ALIGN(SEC_ALIGN) : {
        *(.sdata);
        *(.data);
    } > RAM

    .bss ALIGN(SEC_ALIGN) : {
        *(.sbss);
        *(.bss);
    } > RAM
}
