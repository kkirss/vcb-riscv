.section .init
.global _start
.type _start,@function

_start:
  # Start with no-op as VMEM address 0 is not accessible
  nop

  # Initialize stack pointer to __C_STACK_TOP (defined in the linker script)
	la sp, __C_STACK_TOP__

	# Initialize global pointer to __global_pointer$ (defined in the linker script)
  .option push
  .option norelax
	la gp, __global_pointer$
	.option pop

	# Call main() function
	jal main

	# Run in infinite loop after main() returns
	j idle

idle:
	j idle
