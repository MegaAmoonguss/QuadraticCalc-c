#include <stdio.h>
#include <stdlib.h>
#include "quadratic.h"

int main() {
	Quadratic * q = malloc(sizeof(Quadratic));
	q->a = 5;
	q->b = -5;
	q->c = -360;
	int * solved = solve(q);
	
	if (solved == NULL)
		printf("Not factorable.\n");
	else {
		print_quadratic(q);
		printf("%d(%dx + %d)(%dx + %d)\n", *solved, *(solved + 1), *(solved + 2), *(solved + 3), *(solved + 4));
	}
	
	return 0;
}
