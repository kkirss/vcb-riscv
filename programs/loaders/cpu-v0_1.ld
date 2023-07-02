OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv", "elf32-littleriscv")
OUTPUT_ARCH(riscv)

ENTRY(_start)

MEMORY
{
  NOP_START (r) : ORIGIN = 0x0, LENGTH = 0x4
  TEXT (rx) : ORIGIN = 0x4, LENGTH = (0x100000 - 0x4)
  DISPLAY_ADDR (rw) : ORIGIN = 0x100000, LENGTH = 0x4
  DATA (rwx) : ORIGIN = (0x100000 + 0x4), LENGTH = 0x100000
}

SECTIONS
{
    . = ORIGIN(NOP_START);

    .nop_start : {
        LONG(0x0);
    } > NOP_START

    . = ORIGIN(TEXT);

    .text : {
        *(.text);
    } > TEXT

    . = ORIGIN(DISPLAY_ADDR);

    .display_addr : {
        LONG(0x0);
    } > DISPLAY_ADDR

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
