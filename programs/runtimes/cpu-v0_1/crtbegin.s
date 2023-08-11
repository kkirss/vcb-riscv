# Copied from https:#github.com/ChrisShakkour/RV32I-MAF-project/blob/main/scripts/crt0/crt0.S

.section .init
.global _start
.type _start,@function

# init stack pointer to 4M - 16
# jump to call_main_handler
_start:
	li sp, 0x3FFFF0
	j call_main_handler

# jump to main program
# (argc = argv = 0)
call_main_handler:
	li x10, 0
	li x11, 0
	jal main
	j end_of_main_handler

# stuck at, indicator of end of execution.
idle:
	j idle

# move main function status/return value from a0 to saved register s0.
end_of_main_handler:
	mv s0, a0
	j idle
