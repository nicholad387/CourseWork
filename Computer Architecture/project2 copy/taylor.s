.text
.global _start
.extern printf


ith_Term:
	fmul D12, D12, d10
	fmul D13, D13, D16
	fdiv d8, D12, D13
	br lr

taylor:
	cmp X15, x11
	b.ge Exit
	bl ith_Term
	fadd d14, d14, d8
	fadd D16, D16, D17
	add X15, X15, 1
	b taylor
	
_start:
	ldr x1, =x
	ldr d10, [x1]	// holds x
	ldr x1, =num
	ldr x11, [x1]	// holds num
	
	fmov D12, 1	// numerator
	fmov D13, 1	// denomonator
	fmov d14, 1	// answer
	mov X15, 1	// i
	
	fmov D16, 1
	fmov D17, 1
	
	bl taylor

Exit:
	adr x0, msg
	fmov d0, d14
	bl printf
	mov x0, 0
	mov w8, 93
	svc 0
	
.data
	x: .double 5
	num: .dword 15
	
	msg: .ascii "Approximation: %f\n"
.end
