/*
void insertion_sort(int array[], const int length) {
	for(int i = 1; i < length; i++) {
		int j, current = array[i];
		for(j = i - 1; j >= 0 && array[j] > current; j--) {
			array[j + 1] = array[j];
		}
		array[j + 1] = current;
	}
}
*/

.text
.global _start
.extern printf

.func printArray
printArray:
	LDR x10, =arr
	LDR x11, =length
	LDR x11, [x11]		//length in x11
	LSL x11, x11, #3
	ADD x11, x10, x11
	LDR x12, =Stack
	MOV SP, x12
	SUB SP, SP, #16
	STR x25, [SP]
	STR x26,[SP, #8]	//store x26 in stack offset 8
	MOV x25, x10 		//move base array to x25
	MOV x26, x11		//move ending addr of array to x26
Loop:
	CMP x25, x26
	B.GE Done		//if curr item is last element, go to end
	LDR X0, =msg
	LDR X1, [x25]		//arr[i]
	BL printf
	ADD x25, x25, #8
	B Loop
Done:
	LDR X0, =endmsg
	BL printf			//print (newline character)
	LDR x25, [SP]
	LDR x26, [SP, #8]
	B End
.endfunc

Insertion_sort:
	LDR x10, =arr
	LDR x11, =length
	LDR x11,[x11]
	LSL x11, x11,#3
	ADD x11, x11, x10 	// last elm addr
	MOV x12, x10
Outer_loop:
	CMP x12, x11
	B.GE printArray
	ADD x12, x12, #8 	//next elm
	LDR x14, [x12]		// load next elm
	MOV x15, x12
Inner_loop:
	SUB x15, x15, #8
	CMP x15, x10
	B.LT Outer_loop
	LDR x13, [x15]
	CMP x13, x14
	B.LE Outer_loop
	STR x13, [x15, #8]
	STR x14, [x15]
	B Inner_loop
	
_start:
	B Insertion_sort
	
End:
	mov x0,#0
	mov w8, #93
	svc #0
.data
	arr:.dword 4, 5, 2, 1, 3, 6
	length: .dword 6
	msg: .ascii "%d \0"
	endmsg: .ascii "\n"
.bss
	.space 4096
Stack: .space 8

.end
