/* Nicholas H Mohamed
 I pledge my honor that i have abided by the steven's honor pledge
problem 2
*/

.text
.global _start
.extern printf
	
_start:
	adr X9, a
	adr x10, b
	adr X11, c
	
	ldr x9,[x9]		//a
	ldr x10,[x10]	//b
	ldr x12, [x11]	//c
	
	ADD X9, X9, X10	//add a + b
	SUB X9, X9, #4	//sub a + b from 4
	CBZ X9, Else	//check if its 0
	
	MOV X12, #-12
	STR x12, [x11]
	ADR X0, msg
	LDR X1, [X11]
	BL printf
	
	MOV X0, #0
	MOV W8, #93
	SVC #0
	
Else:
	MOV X12, #13
	STR X12, [X11]
	ADR X0, msg
	LDR X1, [X11]
	BL printf

	MOV X0, 0
	MOV W8, 93
	SVC #0


.data
	a: .quad 2
	b: .quad 2
	c: .quad 4
	msg: .ascii "c = %d\n\0"
	
.end
	