.section .init
.global _start
.type _start,@function

_start:
    # Initialize stack pointer to __C_STACK_TOP (defined in the linker script)
	la sp, __C_STACK_TOP__
	# Call main() function
	jal main
	# Run in infinite loop after main() returns
	j idle

idle:
	j idle
