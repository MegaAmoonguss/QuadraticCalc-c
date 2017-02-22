#ifndef QUADRATIC_H_
#define QUADRATIC_H_

typedef struct {
	int a;
	int b;
	int c;
} Quadratic;

void print_quadratic(Quadratic * q);
int * factor(int n);
int * get_working_factors(Quadratic * q);

#endif
