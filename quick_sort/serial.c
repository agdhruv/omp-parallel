#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 100000

void quicksort(int a[], int l, int r, int threads);
int partition(int a[], int l, int r);

int main() {

	int size = SIZE;
	
	int a[SIZE];

	for (int i = 0; i < size; i++) {
		a[i] = rand() % 20;
	}

	// request for two threads
	omp_set_num_threads(2);
	int threads;

	double t1 = omp_get_wtime();
	quicksort(a, 0, size - 1, threads);
	double t2 = omp_get_wtime();

	// check if the array is actually sorted
	int sorted = 1;
	for (int i = 0; i < size-1; ++i) {
		sorted &= (a[i] <= a[i+1]);
	}
	printf("\nSorted: %d\n", sorted);
	printf("\nTime: %f\n", t2-t1);

	return 0;
}

int partition(int a[], int l, int r) {
	int pivot = a[r];
	int pIndex = l;

	for (int i = l; i <= r - 1; i++) {
		if (a[i] <= pivot) {
			int temp = a[i];
			a[i] = a[pIndex];
			a[pIndex] = temp;
			pIndex++;
		}
	}

	int temp = a[r];
	a[r] = a[pIndex];
	a[pIndex] = temp;

	return pIndex;
}

void quicksort(int a[], int l, int r, int threads) {

	// base step for recursion
	if (l >= r) {
		return;
	}

	// do the main sorting
	int pIndex = partition(a, l, r);

	// Same thread sorting the two sub-arrays
	quicksort(a, l, pIndex - 1, 1);
	quicksort(a, pIndex + 1, r, 1);
}