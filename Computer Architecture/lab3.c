//I pledge my honor that I have abided by the stenes honor pledge 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 
float calc(float x){
	return 2.5*pow(x, 3.0) - 15.5*pow(x, 2.0) + 20*x + 15;
}

int main(int argc, char *argv[]) {
	// y = 2.5x3−15.5x2+ 20x + 15;
	if (argc < 3){
		printf("Enter two numbers for the bounds and the number of rectangles");
		return 1;
	}
	
	const float epsilon = 0.0001;
	float lowerBound = atoi(argv[1]); // upperbound 
	float upperBound = atoi(argv[2]); // lowerbound 
	if (lowerBound > upperBound){
		printf("Enter proper bounds");
		return 1;
	}
	int numRect = atoi(argv[3]); // number of rectangles 
	float deltaX = (upperBound - lowerBound) / numRect; // change in x
	float aproximation = 0;
	float guess = 1;
	float oldguess = 0;
	int cnt = 0;

	while (guess - oldguess > epsilon){
		deltaX = (upperBound - lowerBound) / numRect;
		
		for (float x = lowerBound; x < upperBound; x += deltaX){
			aproximation += deltaX * (calc((x + (deltaX + x)) / 2));
			printf("%f\n", aproximation);
		}
		if (cnt > 0){
			oldguess = guess;
		}
		printf("%d\n", numRect);
		guess = aproximation;
		numRect *=2;
		aproximation = 0;
		cnt ++;
	}
	
	return 0;
}

