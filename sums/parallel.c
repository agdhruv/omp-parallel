#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX 1000000000

int a[MAX];

int main() {

	omp_set_num_threads(4);

	long n = MAX;

	long sum = 0;

	for (long i = 0; i < n; i++) {
		a[i] = 1;
	}

	double t1 = omp_get_wtime();

	#pragma omp parallel
	{
		long t_sum = 0;

		long n_threads = (long)omp_get_num_threads();

		long id = (long)omp_get_thread_num();

		for (long i = id; i < n; i += n_threads) {
			t_sum += a[i];
		}

		#pragma omp critical
		{
			sum += t_sum;
		}
	}

	// #pragma omp parallel for reduction(+:sum)
	// for (long i = 0; i < n; i++) {
	// 	sum += a[i];
	// }

	double t2 = omp_get_wtime();

	printf("Sum: %d\n", sum);
	printf("Time: %f\n", t2-t1);
}