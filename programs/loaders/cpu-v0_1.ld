OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv", "elf32-littleriscv")
ENTRY(main)

MEMORY
{
  TEXT (rx) : ORIGIN = 0x0, LENGTH = 0x8000
  DATA (rwx) : ORIGIN = 0x8000, LENGTH = 0x8000
}

SECTIONS
{
  .text :
  {
    . = ALIGN(32 / 8);
    *(.text)
  }> TEXT

  .data :
  {
    . = ALIGN(32 / 8);
    *(.data)
  }> DATA
}
