#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#define SIZE 1000000

void merge(int a[], int l, int m, int r);
void mergesort_serial(int a[], int l, int r);
void mergesort_parallel_omp(int a[], int l, int r, int threads);

int main() {

	int a[SIZE];

	int num_threads;

	int size = SIZE;

	omp_set_num_threads(2);

	// get num_threads
	#pragma omp parallel
	{
		#pragma omp master
		{
			num_threads = omp_get_num_threads();
		}
	}

	for (int i = 0; i < SIZE; i++) {
		a[i] = rand() % SIZE;
	}

	double startTime = omp_get_wtime();

	mergesort_parallel_omp(a, 0, size - 1, num_threads);

	double endTime = omp_get_wtime();

	int sorted = 1;
	for (int i = 0; i < size-1; ++i) {
		sorted &= (a[i] <= a[i+1]);
	}
	printf("\nSorted: %d\n", sorted);
	printf("\nTime taken: %f\n\n", endTime - startTime);
}


void merge(int a[], int l, int m, int r) {

    int n1 = m - l + 1;
    int n2 =  r - m;
 	
 	// create temporary arrays
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
    	L[i] = a[l + i];
    }

    for (int j = 0; j < n2; j++) {
        R[j] = a[m + 1 + j];
    }
 
    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            a[k] = L[i];
            i++;
        }

        else {
            a[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }

}

void mergesort_serial(int a[], int l, int r) {

	if (l < r) {
		int m = l + (r-l)/2;

		mergesort_serial(a, l, m);
		mergesort_serial(a, m+1, r);
		merge(a, l, m, r);
	}

}

void mergesort_parallel_omp(int a[], int l, int r, int threads) {
    
    int m = l + (r-l)/2;

    if (threads == 1) {
    	mergesort_serial(a, l, r);
    }

    else if (threads > 1) {
    	#pragma omp parallel sections
        {
			#pragma omp section
			mergesort_parallel_omp(a, l, m, threads/2);
			#pragma omp section
			mergesort_parallel_omp(a, m+1, r, threads - threads/2);
        }

        merge(a, l, m, r);
    }
}