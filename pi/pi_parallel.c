#include <stdio.h>
#include <omp.h>

static long num_steps = 100000000;
double step;

void main() {

	double pi, sum = 0.0;

	step = 1.0/(double) num_steps;

	omp_set_num_threads(4);

	double t1 = omp_get_wtime();

	#pragma omp parallel
	{	
		long ID = (long)omp_get_thread_num();
		long num_of_threads = (long)omp_get_num_threads();

		double x, t_sum = 0.0;

		for (int i = ID; i < num_steps; i += num_of_threads) {
			x = (i + 0.5) * step;
			t_sum = t_sum + 4.0/(1.0 + x*x);
		}

		#pragma omp critical
		{
			sum += t_sum;
		}
	}

	// #pragma omp parallel for reduction(+:sum)
	// 	for (int i = 0; i < num_steps; i++) {
	// 		double x = (i + 0.5) * step;
	// 		sum += 4.0/(1.0 + x*x);
	// 	}

	double t2 = omp_get_wtime();

	printf("%f\n", t2-t1);

	pi = step * sum;

	printf("%f\n", pi);
}