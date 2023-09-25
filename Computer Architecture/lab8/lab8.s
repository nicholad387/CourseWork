.text
.global _start

_start:
	ldr x8, =P
	ldr x9, [x8,#0]		//point x1
	ldr x10, [x8, #8]	//point y1
	
	ldr x8, =C
	ldr x11, [x8, #0]	//point x2
	ldr x12, [x8, #8]	//point y2
	
	ldr x8, =p3
	ldr x13, [x8]	// radius 
	mul x13, x13, x13	//radius squared
	
	sub x9, x9, x11 // x1 - x2
	mul x9, x9, x9	// point 1 squared
	
	sub x10, x10, x12	// y1 - y2
	mul x10, x10, x10	//point 2 squared 
	
	add x14, x9, x10	// point 1 + point 2
	
	cmp x13, x14
	b.gt YES
	
	adr x16, no
	b Done

YES:
	adr x16, yes
	b Done
	
Done:
	mov x0, #0
	mov w8, #93
	SVC #0

.data
	P: .quad 0, 0
	C: .quad 1, 2
	p3: .quad 2
	yes: .string "P is inside the circle."
	no: .string "P is outside the circle."
	.end
	
