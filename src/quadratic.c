#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "quadratic.h"

#define CHUNK_SIZE 10

/*
 * Specifically sorts an array created by the algorithm used by the
 * factor() function.
 */
void sort_factors(int * factors, int * sorted, int count) {
	int index = 0;

	for (int i = 0; i < count; i += 2) {
		*(sorted + index) = *(factors + i);
		index++;
	}

	int start;
	if (count % 2 == 1)
		/* if factored number was square */
		start = count - 2;
	else
		/* if factored number was not square */
		start = count - 1;

	for (int i = start; i > 0; i -= 2) {
		*(sorted + index) = *(factors + i);
		index++;
	}
}

/*
 * Returns the greatest common divisor of a and b. Uses the Euclidean
 * algorithm to calculate the greatest common divisor. Will return a
 * negative value if and only if a is negative.
 */
int gcd(int a, int b) {
	int divisor = abs(b == 0 ? a : gcd(b, a % b));
	return a < 0 ? -1 * divisor : divisor;
}  

/*
 * Factors an integer n. Returns a pointer to an array of the
 * factors. The value at the pointer is the number of factors, the
 * factors themselves start at the next index (starting with 1,
 * ending with n).
 */
int * factor(int n) {
	if (n == 0)
		return 0;
	n = abs(n);
	
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
			count++;
			*(factors + count) = i;
			if (i != n / i) {
				count++;
				*(factors + count) = n / i;
			}
		}
	}
	/* assign the first value to be the number of factors */
	*factors = count;
	
	/* sort the factors */
	int * sorted = malloc(sizeof(int) * (count + 1));
	*sorted = count;
	sort_factors(factors + 1, sorted + 1, count);

	return sorted;
}

/*
 * Finds two factors of q->a * q->c that add up to q->b. Returns a pointer
 * to an array that holds the two factors.
 */
int * get_working_factors(Quadratic * q) {
	int n = q->a * q->c;
	int * factors = factor(n);
	int * working = malloc(2 * sizeof(int));
	
	int len = *factors;
	
	if (q->b >= 0) {
		if (q->c > 0) {
			/* check using two positives */
			for (int i = 0; i < (len / 2) + 1; i++) {
				if (*(factors + 1 + i) + *(factors + len - i) == q->b) {
					*working = *(factors + 1 + i);
					*(working + 1) = *(factors + len - i);
					return working;
				}
			}
		}
		
		if (q->c < 0) {
			/* check using a positive and a smaller or equal negative */
			for (int i = 0; i < (len / 2) + 1; i++) {
				if ((-1 * *(factors + 1 + i)) + *(factors + len - i) == q->b) {
					*working = -1 * *(factors + 1 + i);
					*(working + 1) = *(factors + len - i);
					return working;
				}
			}
		}
	}

	else if (q->b < 0) {
		if (q->c > 0) {
			/* check using two negatives */
			for (int i = 0; i < (len / 2); i++) {
				if (*(factors + 1 + i) + *(factors + len - i) == q->b) {
					*working = *(factors + 1 + i);
					*(working + 1) = *(factors + len - i);
					return working;
				}
			}
		}
		
		if (q->c < 0) {
			/* check using a positive and a larger negative */
			for (int i = 0; i < (len / 2); i++) {
				if (*(factors + 1 + i) + (-1 * *(factors + len - i)) == q->b) {
					*working = *(factors + 1 + i);
					*(working + 1) = -1 * *(factors + len - i);
					return working;
				}
			}
		}
	}
	
	return NULL;
}

/*
 * Returns a pointer to an array of the coefficients of the factored
 * quadratic. The array is in the form [a, b, c, d, e], representing
 * a(bx + c)(dx + e).
 */
int * solve(Quadratic * q) {
	if (q->c == 0)
		return NULL;

	Quadratic * temp = malloc(sizeof(Quadratic));
	memcpy(temp, q, sizeof(Quadratic));

	int * solved = malloc(5 * sizeof(int));
	*solved = gcd(temp->a, gcd(temp->b, temp->c));

	temp->a /= *solved;
	temp->b /= *solved;
	temp->c /= *solved;

	if (!get_working_factors(temp))
		return NULL;
	int * working = get_working_factors(temp);

	int expanded[4] = {temp->a, *working, *(working + 1), temp->c};

	*(solved + 1) = gcd(expanded[0], expanded[1]);
	*(solved + 2) = gcd(expanded[2], expanded[3]);
	*(solved + 3) = expanded[0] / *(solved + 1);
	*(solved + 4) = expanded[1] / *(solved + 1);

	return solved;
}

/*
 * Returns the given Quadratic struct as a string in the form ax^2 +
 * bx + c.
 */
char * quadratic_to_string(Quadratic * q) {
	static char s[50];

	if (q->a != 1)
		sprintf(s, strcat(s, "%d"), q->a);
	strcat(s, "x^2");

	if (q->b > 0)
		strcat(s, " + ");
	else if (q->b < 0)
		strcat(s, " - ");
	if (q->b != 0) {
		if (q->b != 1)
			sprintf(s, strcat(s, "%d"), abs(q->b));
		strcat(s, "x");
	}

	if (q->c > 0)
		strcat(s, " + ");
	else if (q->c < 0)
		strcat(s, " - ");
	if (q->c != 0)
		sprintf(s, strcat(s, "%d"), abs(q->c));

	return s;
}

/* Returns the given factored quadratic in string form. */
char * factored_to_string(int * solved) {
	static char s[50];

	if (*solved != 1)
		sprintf(s, strcat(s, "%d"), *solved);

	for (int i = 0; i < 2; i++) {
		strcat(s, "(");

		if (*(solved + (2 * i) + 1) != 1)
			sprintf(s, strcat(s, "%d"), *(solved + (2 * i) + 1));
		strcat(s, "x");

		if (*(solved + (2 * i) + 2) > 0)
			strcat(s, " - ");
		else
			strcat(s, " + ");
		sprintf(s, strcat(s, "%d"), abs(*(solved + (2 * i) + 2)));
		strcat(s, ")");
	}

	return s;
}
