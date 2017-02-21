#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "quadratic.h"

int main() {
	int num = 15;
	
	clock_t begin = clock();
	int * factors = factor(num);
	clock_t end = clock();
	
	printf("%d\n", *factors);
	for (int i = 0; i < *factors; i++)
		printf("%d ", *(factors + 1 + i));
	printf("\nTime: %f\n\n", (double)(end-begin) / CLOCKS_PER_SEC);
	
	Quadratic * q = malloc(sizeof(Quadratic));
	q->a = 5;
	q->b = -5;
	q->c = -360;
	print_quadratic(q);
	
	return 0;
}
