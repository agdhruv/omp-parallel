#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX 1000000000

int a[MAX];

int main() {

	long n = MAX;

	long sum = 0;

	for (long i = 0; i < n; i++) {
		a[i] = 1;
	}

	double t1 = omp_get_wtime();

	// perform the sum
	for (long i = 0; i < n; i++) {
		sum += a[i];
	}

	double t2 = omp_get_wtime();

	printf("Sum: %d\n", sum);
	printf("Time: %f\n", t2-t1);
}