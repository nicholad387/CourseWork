/*
binarySearch(arr, x, low, high)
			repeat till low = high
					mid = (low + high)/2
						if (x == arr[mid])
						return mid
						
						else if (x > arr[mid]) // x is on the right side
								low = mid + 1
								
						else                  // x is on the left side
								high = mid - 1
*/
.text
.global _start
.extern printf


BINARY_SEARCH:
	SUB X9, X11, 1 // high
	MOV X13, #0 
	LOOP:
		CMP X13, X9
		B.GT print_not_found 
		ADD x14, X9, X13 // add Low and high
		LSR x14, x14, #1 // dividing by 2
		LSL x15, x14, 3 // multiply by 8
		LDR x16, [X10, x15] //  arr[mid]
		CMP X18, x16
		B.EQ print_found 
		CMP X18, x16
		B.GT greater 
		B less 
greater:
	ADD X13, x14, 1 // low = mid + 1
	B LOOP
less:
	SUB X9, x14, 1 // high = mid - 1
	B LOOP
	
print_not_found:
	LDR X0, =not_found
	BL printf
	B Exit
	
print_found:
	LDR X0, =found
	MOV X1, x14
	BL printf
	B Exit

_start:
	LDR X1,=target
	LDR X0,=s_format
	BL scanf
	LDR X10,=arr
	LDR X11, =length
	LDR X18, =target 
	LDR X18, [X18, #0] 
	LDR X11, [X11, #0] 
	B BINARY_SEARCH 
	
Exit:
	MOV X0,0
	MOV W8,93
	SVC 0
	
.data
	arr: .dword 0,1,2,3,4,5,6,7,8,9
	length:.dword 10
	target:.dword 0
	
	s_format: .asciz "%d"
	
	not_found: .asciz "Not in the array. \n\0"
	found: .asciz "At the index: %d\n\0"
	.end

