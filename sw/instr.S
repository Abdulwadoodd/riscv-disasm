
.globl _start
_start:
	add t2, t3, x1
	sub a0, a1, a2
	xor t4, s0, s1
	or a3, a4, s3
	and s2, s3, s4
	sll x1, x2, x3
	srl x3,x4,x5
	sra x6,x7,x8
	slt x9, x10, x11
	sltu x26,x27, x28
	nop
	nop
	nop
	
	addi t2, t3, 12
	xori t4, s0, 11
	ori a3, a4, 13
	andi s2, s3, 14
	slli x1, x2, 15
	srli x3,x4,16
	srai x6,x7,17
	slt x9, x10, 18
	sltu x26,x27, 19
	
	
