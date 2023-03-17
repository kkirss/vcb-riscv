OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv", "elf32-littleriscv")
OUTPUT_ARCH(riscv)

ENTRY(main)

MEMORY
{
  TEXT (rx) : ORIGIN = 0x0, LENGTH = 0x8000
  DATA (rwx) : ORIGIN = 0x8000, LENGTH = 0x8000
}

SECTIONS
{
    . = ORIGIN(TEXT);

    .text : {
        *(.text);
    } > TEXT

    . = ORIGIN(DATA);

    .rodata : {
        *(.srodata);
        *(.rodata);
        *(.rdata);
    } > DATA

    . = ALIGN(32 / 8);
    .data : {
        *(.sdata);
        *(.data);
    } > DATA

    . = ALIGN(32 / 8);
    .bss : {
        *(.sbss);
        *(.bss);
    } > DATA
}
