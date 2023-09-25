/*
* I pledge my honor that i have abided by the stevens honor pledge 
*/
#include "utils.h"
#include <stdlib.h>
#include <string.h>


/*
	You are free to use any data type you like in this file.
    However, other than the five functions declared in "utils.h",
    DO NOT create any other functions.
	
*/

int cmpr_int(void* a, void* b) {
	if (*(int *)a > *(int *)b){
		return 1;
	}else if (*(int *)a < *(int *)b) {
		return -1;
	}
	return 0;
}

int cmpr_float(void* a,void* b) {
	if (*(float *)a > *(float *)b) {
		return 1;
	}else if (*(float *)a < *(float *)b) {
		return -1;
	}
	return 0;
}

void print_int(void* obj) {
	int* val = (int*)obj;
	printf("%d", *val);
}

void print_float(void* obj) {
	float* val = (float*)obj;
	printf("%f", *val);
}


void* read_array(char* filename, char* format, size_t* len) {
	FILE* fp;
	void* arr;
	int n;
	
	fp = fopen(filename, "r"); // open the file in read mode
	
	// if the file cannot be opened, print an error message and exit with code 1
	if (fp == NULL) {
		fprintf(stderr, "File failed to open.\n");
		exit(1);
	}
	
	// get the number of elements in the file
	n = 0;
	while (fscanf(fp, format, &arr) == 1) {
		n++;
	}

	*len = n; // set the length of the array
	
	arr = malloc(n * sizeof(void*)); // allocate memory for the array
	fseek(fp, 0, SEEK_SET); // reset the file pointer to the beginning of the file
	
	// read in each element of the array from the file and store it in the array
	for (int i = 0; i < n; i++) {
		if (strcmp(format, "%d") == 0) {
			int* temp = malloc(sizeof(int));
			fscanf(fp, format, temp);
			*((int*) arr + i) = *temp;
			free(temp);  // free the memory allocated for temp
		} else if (strcmp(format, "%f") == 0) {
			float* temp = malloc(sizeof(float));
			fscanf(fp, format, temp);
			*((float*) arr + i) = *temp;
			free(temp);  // free the memory allocated for temp
		}
	}
	
	fclose(fp); // close the file
	return arr; // return a pointer to the array
}
