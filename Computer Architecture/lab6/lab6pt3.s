/* Nicholas H Mohamed
 I pledge my honor that i have abided by the steven's honor pledge
problem 3
*/

.text
.global _start
.extern printf
	
_start:
		ADR X9, i
		LDR X9, [X9]
		ADR X1, holder
		LDR X1, [X1]
	
Loop:	CBZ X9, DONE
		ADD X1,X1, X9
		SUB X9, X9, #1
		B Loop
		
DONE:
		ADR X0, msg
		BL printf
	
		MOV X0, 0
		MOV W8, 93
		SVC #0
	
.data
	i: .quad 10
	holder: .quad 0
	msg: .ascii "%d\n\0"
	
.end
	