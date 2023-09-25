.text
.global _start
.extern printf

.func calc_dist
calc_dist:				// (x_1 - x_2)^2 + (y_1 - y_2)^2
	fsub d1, d1, d3
	fsub d2, d2, d4
	fmul d1, d1, d1
	fmul d2, d2, d2
	fadd d1, d1, d2
	br lr
.endfunc
	
_start:
	ldr x0, =N
	ldr x5, [x0]	// N
	
	ldr x6, =x
	ldr x7, =y
	fsub d9, d9, d9
	fmov d8, 31
	
	mov x10, 0	// L1 iterator 
	mov x11, -1		// x11 - 14 hold indexes 
	mov x12, -1
	
	mov x13, 0
	mov x14, 0
L1:
	cmp x5, x10
	b.le Done
	ldr d17, [x6]
	ldr d18, [x7]
	mov x15, x10	//L2 iterator
	add x15, x15, 1
	mov x16, #8		// offset 
	
	L2:
		cmp x5, x15
		b.le InnerStop
		
		ldr d3, [x6,x16]
		ldr d4, [x7, x16]
		
		fmov d1, d17
		fmov d2, d18
		bl calc_dist
		fcmp d1, d8
		b.ge validMax
		
		fmov d8, d1 
		mov x11, x10
		mov x12, x15
		
validMax:
	fcmp d1, d9
	b.le validMin
	
	fmov d9, d1
	mov x13, x10
	mov x14, x15
	
validMin:
	add x15, x15, 1
	add x16, x16, 8
	
	b L2
	
InnerStop:
	add x6, x6, 8	// fix address 
	add x7, x7, 8
	add x10, x10, 1
	
	b L1
Done:
	
	ldr x0, =msg
	mov x1, x11
	mov x2, x12
	mov x3, x13
	mov x4, x14
	bl printf
	
	mov x0, 0
	mov w8, 93
	svc 0
	
	.data
N:
	.dword 8
x:
	.double 0.0, 0.4140, 1.4949, 5.0014, 6.5163, 3.9303, 8.4813, 2.6505
y:
	.double 0.0, 3.9862, 6.1488, 1.047, 4.6102, 1.4057, 5.0371, 4.1196
msg:
	.asciz "Shortest distance between (%d, %d) and Largest between (%d, %d)\n "
	
.end
