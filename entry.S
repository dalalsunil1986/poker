.section .text
.globl _start
_start:
	la sp,__stack_top
	#enable interrupts
	li a0, 8
	csrrs zero, mstatus, a0
	#mtvec
	la a0, handler
	csrw mtvec, a0
	la a0, (1 << 11)
	csrrs zero, mie, a0
	li a0, 0
	call main
	wfi	
.align 4
handler:
	csrr a0, mcause
	#clear MEIP
	#li a1, (1 << 11)
	#csrrc zero, mip, a1
	#clear MSIE
	#csrrc zero, mie, a1
	call test
	#csrr a2, mepc
	#3add a2, a2, 4
	#3csrw mepc, a2
	mret
	
