#include <stdio.h>
#include <omp.h>

static long num_steps = 100000000;
double step;

int main() {

	double x, pi, sum = 0.0;

	step = 1.0/(double) num_steps;

	double t1 = omp_get_wtime();

	for (int i = 0; i < num_steps; i++) {
		x = (i + 0.5) * step;
		sum = sum + 4.0/(1.0 + x*x);
	}

	double t2 = omp_get_wtime();

	pi = step * sum;

	printf("%f\n", t2-t1);

	printf("%f\n", pi);
}