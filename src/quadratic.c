#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "quadratic.h"

#define CHUNK_SIZE 10

void print_quadratic(Quadratic * q) {
	printf("%dx^2 + %dx + %d\n", q->a, q->b, q->c);
}

int compare_int(const void* a, const void* b) {
    if( *(int*)a == *(int*)b ) return 0;
    return *(int*)a < *(int*)b ? -1 : 1;
}


int * factor(int n) {
	/* Factors an integer n. Returns a pointer to the factors. The value
	 * at the pointer is the number of factors, the factors themselves
	 * start at the next index (starting with 1, ending with n). */
	 
	if (n == 0)
		return 0;
	else if (n < 0)
		n *= -1;
	
	int * factors = malloc(CHUNK_SIZE * sizeof(int));
	int count = 0;
	int increases = 0;
	
	size_t size;
	for (int i = 1; i < ((int) sqrt(n)) + 1; i++) {
		/* increase size of factors array if needed */
		size = CHUNK_SIZE * sizeof(int) * (increases + 1);
		if (count >= (size / sizeof(int)) - 2) {
			factors = realloc(factors, size + (CHUNK_SIZE * sizeof(int)));
			increases++;
		}
		
		/* check if i is a factor */
		if (n % i == 0) {
			if (i == n / i) {
				*(factors + count + 1) = i;
				count++;
			}
			else {
				*(factors + count + 1) = i;
				*(factors + count + 2) = n / i;
				count += 2;
			}
		}
	}
	/* assign the first value to be the number of factors */
	*factors = count;
	
	/* sort the factors */
	qsort(factors + 1, count, sizeof(int), compare_int);
	
	return factors;
}

int * get_working_factors(Quadratic * q) {
	int n = q->a * q->c;
	int * factors = factor(n);
	
	/* check for working factors */
	int len = *factors;
	for (int i = 0; i < len; i++) {
		if (*(factors + 1 + i))
			printf("");
	}
	
	return 0;
}

int * solve(Quadratic * q) {
	return 0;
}
