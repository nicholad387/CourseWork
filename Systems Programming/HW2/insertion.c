/*
* 
* I pledge my honor that i have abided by the stevens honor pledge 
*/

#include "insertion.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

/*
	We emphasize this: because this is a generic implementation, in insertion.c you must not use if-else to
	discriminate different data types in your code. Your code must be able to deal with any data type possible.
	Therefore, we limit the usage of the following primitive types:
	- int or size_t: only allowed as loop iterators;
	- char or u_int8_t: can be used as you wish;
	- Types that are used in the declarations of iSort() and iPrint(): feel free to use them for their _original_
      purpose;
	- All other types are not allowed to appear in insertion.c: no exceptions, no matter if you actually used
	  them, or what purpose it is. Once it appears, you will receive 30% reduction of the homework.

	You are free to create helper functions only in insertion.c; you must declare and implement them in the
    .c file instead of the header files. Do not change any of the header files.
	
*/


/* help to create the insertion sort alrgorthum from https://www.geeksforgeeks.org/insertion-sort/ */

/* the biult in function "memcpy" i found from https://www.tutorialspoint.com/c_standard_library/c_function_memcpy.htm */

void iSort(void* base, size_t nel, size_t width, int (*compare)(void*,void*)) {
	char *arrBytes = (char *)base; // Cast the void pointer to a char pointer 
	char *key = (char *)malloc(width);	// Allocate memory for a temporary key variable to store the value being compared
	int i, j; // just for itorators 
	
	for (i = 1; i < (int)nel; i++) {
		memcpy(key, arrBytes + i * width, width); // Copy the value being compared into the key variable
		j = i - 1;
		
		// Shift all elements that are greater than the key to the right
		while (j >= 0 && compare(arrBytes + j * width, key) > 0) {
			memcpy(arrBytes + (j + 1) * width, arrBytes + j * width, width);
			j--;
		}
		
		memcpy(arrBytes + (j + 1) * width, key, width); // Insert the key into its correct position in the sorted subarray
	}
	
	free(key); // Free the temporary key variable
}


void iPrint(void* base, size_t nel, size_t width, void (*print)(void*)) {
	char *arrBytes = (char *)base;
	// Loop through each element of the array
	for (size_t i = 0; i < nel; i++) {
		// Call the type-specific print function on the element at the current index
		print(arrBytes + i * width);
		printf("\n");
	}
}
