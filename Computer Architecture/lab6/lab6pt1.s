/* Nicholas H Mohamed
 I pledge my honor that i have abided by the steven's honor pledge
problem 1
*/

.text
.global _start
.extern printf
	
_start:
	adr X9, i
	adr x10, g
	adr X11, f
	
	ldr x9,[x9]
	ldr x10,[x10]
	
	sub X9, X9, #4
	CBZ X9, Else //if equal 0
	
	sub x10, x10, #24 
	str x10 , [x11]
	adr x0, msg
	ldr x1, [x11]
	BL printf
	
	MOV X0, #0
	MOV W8, #93
	SVC #0
	
Else:
	adds x10, x10, #12
	str x10 ,[x11]
	adr x0, msg
	ldr x1, [x11]
	BL printf
	
	MOV X0, 0
	MOV W8, 93
	SVC #0


.data
	i: .quad 4
	g: .quad 4
	f: .quad 4
	msg: .ascii "f = %d\n\0"
	
.end
	