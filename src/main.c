#include <stdio.h>
#include <stdlib.h>
#include "quadratic.h"

int main(int argc, char * argv[]) {
	if (argc != 4) {
		printf("Invalid number of arguments.\n");
		return -1;
	}
	
	Quadratic * q = malloc(sizeof(Quadratic));
	q->a = atoi(argv[1]);
	q->b = atoi(argv[2]);
	q->c = atoi(argv[3]);
	int * solved = solve(q);
	
	if (solved == NULL)
		printf("Not factorable.\n");
	else {
		printf("%s\n", quadratic_to_string(q));
		printf("%d(%dx + %d)(%dx + %d)\n", *solved, *(solved + 1), *(solved + 2), *(solved + 3), *(solved + 4));
	}
	
	return 0;
}
