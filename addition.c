#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM 1000000000

int a[NUM], b[NUM];

int main() {

	long n = NUM;

	for (long i = 0; i < n; i++) {
		a[i] = rand()%10;
		b[i] = rand()%10;
	}

	double t1 = omp_get_wtime();

	omp_set_num_threads(6);

	#pragma omp parallel for schedule(static)
		for (int i = 0; i < n; i++) {
			a[i] = a[i] + b[i];
		}

	double t2 = omp_get_wtime();

	printf("%f\n", t2-t1);

	return 0;
}