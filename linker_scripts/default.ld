# Parts taken from: https://github.com/syntacore/sc-bl/blob/master/common/scbl.ld

OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv", "elf32-littleriscv")
OUTPUT_ARCH(riscv)

ENTRY(_start)

STACK_PAD = 16;

# Use variables to allow configuring from the command line

# Size of RAM (in bytes)
__RAM_SIZE__ = DEFINED( __RAM_SIZE__ ) ? __RAM_SIZE__ : 4096K;

# Display pointer address
__DISPLAY_POINTER_ADDRESS__ = DEFINED( __DISPLAY_POINTER_ADDRESS__ ) ? __DISPLAY_POINTER_ADDRESS__ : __RAM_SIZE__ - 32 / 8;

# Address for the the top of stack
# Will start growing to lower addresses (as is RISC-V convention)
__STACK_TOP__ = DEFINED( __STACK_TOP__ ) ? __STACK_TOP__ : __DISPLAY_POINTER_ADDRESS__ - 32 / 8;

# Size of the stack in bytes
# Note: This doesn't implement any stack overflow checking.
#       This just ensures this amount of memory is reserved for the stack.
# Note: There is a 16 byte pad at the top of the stack, just in case
__STACK_SIZE__ = DEFINED( __STACK_SIZE__ ) ? __STACK_SIZE__ : 4K;

__VINPUT_ADDRESS__ = __RAM_SIZE__;
__BREAKPOINT_ADDRESS__ = __VINPUT_ADDRESS__ + 32 / 8;

MEMORY
{
  RAM (rwx) : ORIGIN = 0x0, LENGTH = __RAM_SIZE__

  DISPLAY_POINTER (rw) : ORIGIN = __DISPLAY_POINTER_ADDRESS__, LENGTH = 32 / 8
  VIRTUAL_INPUT (rw) : ORIGIN = __VINPUT_ADDRESS__, LENGTH = 32 / 8
  BREAKPOINT (rw) : ORIGIN = __BREAKPOINT_ADDRESS__, LENGTH = 32 / 8
}

SECTIONS
{
  . = ORIGIN(RAM);

  # The .init section is used for code that needs to be run before main (e.g. set the stack pointer)
  .init : {
    KEEP (*(SORT_NONE(.init)))
  } > RAM

  .text : {
    *(.text .text.*);
  } > RAM

  .rodata : {
    *(.srodata .srodata.*);
    *(.rodata .rodata.*);
    *(.rdata .rdata.*);
  } > RAM

  .data : {
    *(.data .data.*);
  } > RAM

  .sdata : {
    *(.sdata .sdata.*);
  } > RAM

  .sbss : {
    *(.sbss .sbss.*);
  } > RAM

  .bss : {
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

  .display_pointer __DISPLAY_POINTER_ADDRESS__ : {
    PROVIDE(__DISPLAY_POINTER_ADDRESS__ = .);
    KEEP (*(.display_pointer));
  } > DISPLAY_POINTER AT> RAM

  .virtual_input __VINPUT_ADDRESS__ : {
    PROVIDE(__VINPUT_ADDRESS__ = .);
    KEEP (*(.virtual_input));
  } > VIRTUAL_INPUT

  .breakpoint : {
    PROVIDE(__BREAKPOINT_ADDRESS__ = .);
    KEEP (*(.breakpoint));
  } > BREAKPOINT
}
