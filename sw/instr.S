
.globl _start
_start:
	// R-type
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
	// I-type
	addi t2, t3, 12
	xori t4, s0, 11
	ori a3, a4, 13
	andi s2, s3, 14
	slli x1, x2, 15
	srli x3,x4,16
	srai x6,x7,17
	slt x9, x10, 18
	sltu x26,x27, 19
	nop
	nop
	nop
	// I (Load) type
	lb x22, 12(x21)
	lh x21, 16(x20)
	lw x20, 20(x19)
	lbu x19, 24(x18)
	lhu x18, 28(x17)
	nop
	nop
	nop
	//  S type
	sb x17, 32(x16)
	sh x16, 36(x15)
	sw x15, 40(x14)
	nop
	nop
	nop
	// jal
	jal x2, jmp1
	jal x3, jmp2
	jal x4, jmp3
	nop
	nop
	nop
	// jalr
	jalr a0, 48(t1)
	jalr a1, 52(t2)
	jalr a2, 56(t3)


.align 5
jjr1:
	ret

.align 5
jjr2:
	ret

.align 5
jjr3:
	ret
	
.align 12

jmp1:
	nop
	
.align 12

jmp2: 
	nop

.align 12
jmp3:
	nop
	
	
