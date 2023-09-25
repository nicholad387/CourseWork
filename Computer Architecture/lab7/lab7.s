.text
.global _start
.extern printf

FUNC:
	SUB SP, SP, #32		// make space 
	STUR LR, [SP] 		// save return address 
	STUR X1, [SP, #8]
	STUR X6, [SP,#16]
	STUR X7, [SP, #24]
	CMP X6, #0		// check if n == 0
	B.EQ DONE
	
	LSL X8, X6, #3		// shift 
	SUB X6, X6, #1		// n - 1
	LDR X9, [X1, X8]	// load elm
	CMP X9, X7
	B.GT L1		// check if its bigger
	BL FUNC
	
	LDR LR, [SP]
	ADD SP, SP, #32		//pop stack
	BR LR		// return 
	
L1:
	MOV X7, X9 // move bigger elm into X7
	BL FUNC
	LDR LR, [SP]
	ADD SP, SP, #32	//pop stack
	BR LR	//return 
	
DONE:
	LDR LR, [SP]
	ADD SP,SP, #32	//pop stack
	BR LR		//return 

EXIT:		//end program 
	mov x0, #0
	mov w8, #93
	SVC #0
	
_start:
	ADR X1, arr
	adr X6, leng
	LDR X6, [X6] 
	SUB X6, X6, #1 
	ldr X7, [X1,#0] 
	bl FUNC
	adr X0, msg
	MOV X1, X7 
	bl printf 
	b EXIT
	
.data
	arr: .quad 1, 9, 6, 3
	leng: .quad 4
	msg: .ascii "Max = %d\n\0"
	.end
	
	
