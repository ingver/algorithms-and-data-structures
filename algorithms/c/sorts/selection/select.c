#include <stdlib.h>
#include <string.h>

// simple int array version
void selection_sort_int(int* arr, int size)
{
	if (arr == NULL)
		return;

	int i, j, min_index;
	for (i = 0; i < size; ++i) {
		min_index = i;
		for (j = i+1; j < size; ++j)
			if (arr[j] < arr[min_index])
				min_index = j;
		if (i != min_index) {
			int t = arr[min_index];
			arr[min_index] = arr[i];
			arr[i] = t;
		}
	}
}

// generalized swap
void swap(void* a, void* b, int size)
{
	if (a == NULL || b == NULL || size <= 0)
		return;

	char* t = (char*) malloc(size);
	memcpy(t, a, size);
	memcpy(a, b, size);
	memcpy(b, t, size);
	free(t);
}

// generalized version
void selection_sort(void* arr, int size, int count, int (*cmp)(void*, void*))
{
// macro to get easier element of an array
#define elem(idx) (arr + size*(idx))

	if (arr == NULL || size <= 0 || cmp == NULL)
		return;

	int i, j, min_index;
	for (i = 0; i < count; ++i) {
		min_index = i;
		for (j = i+1; j < count; ++j)
			if (cmp(elem(j), elem(min_index)))
				min_index = j;
		if (i != min_index)
			swap(elem(i), elem(min_index), size);
	}

#undef elem
}

// example of compare function
int less(void* a, void* b)
{
	if(a == NULL || b == NULL) {
		return 0;
	}
	double* ia = (double*) a;
	double* ib = (double*) b;

	return *ia < *ib;
}
