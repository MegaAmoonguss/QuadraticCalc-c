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
	int * working = malloc(2 * sizeof(int));
	
	int len = *factors;
	
	if (q->b >= 0) {
		/* check using two positives */
		for (int i = 0; i < (len / 2) + 1; i++) {
			if (*(factors + 1 + i) + *(factors + len - i) == q->b) {
				*working = *(factors + 1 + i);
				*(working + 1) = *(factors + len - i);
				return working;
			}
		}
		
		/* check using a positive and a smaller or equal negative */
		for (int i = 0; i < (len / 2) + 1; i++) {
			if ((-1 * *(factors + 1 + i)) + *(factors + len - i) == q->b) {
				*working = -1 * *(factors + 1 + i);
				*(working + 1) = *(factors + len - i);
				return working;
			}
		}
	}
	
	if (q->b < 0) {
		/* check using two negatives */
		for (int i = 0; i < (len / 2); i++) {
			if (*(factors + 1 + i) + *(factors + len - i) == q->b) {
				*working = *(factors + 1 + i);
				*(working + 1) = *(factors + len - i);
				return working;
			}
		}
		
		/* check using a positive and a larger negative */
		for (int i = 0; i < (len / 2); i++) {
			if (*(factors + 1 + i) + (-1 * *(factors + len - i)) == q->b) {
				*working = *(factors + 1 + i);
				*(working + 1) = -1 * *(factors + len - i);
				return working;
			}
		}
	}
	
	return NULL;
}
