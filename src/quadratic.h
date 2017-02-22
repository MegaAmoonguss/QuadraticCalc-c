#ifndef QUADRATIC_H_
#define QUADRATIC_H_

typedef struct {
	int a;
	int b;
	int c;
} Quadratic;

void print_quadratic(Quadratic * q);
int gcd(int a, int b);
int * factor(int n);
int * get_working_factors(Quadratic * q);
int * solve(Quadratic * q);

#endif /* QUADRATIC_H_ */
