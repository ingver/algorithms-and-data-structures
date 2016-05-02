#include <stdlib.h>
#include <string.h>

// simple int array version
void bubble_sort_int(int* arr, int size)
{
	int i, j;
	for (i = 0; i < size; ++i)
		for (j = 0; j < size - i - 1; ++j)
			if (arr[j+1] < arr[j]) {
				int t = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = t;
			}
}

// generalized swap
void swap(void* a, void* b, int size)
{
	char* t = (char*) malloc(size);
	memcpy(t, a, size);
	memcpy(a, b, size);
	memcpy(b, t, size);
}

// generalized version
void bubble_sort(void* arr, int size, int count, int (*cmp)(void*, void*))
{
// macro to get easier element of an array
#define elem(idx) (arr + size*(idx))

	if (arr == NULL || size <= 0 || cmp == NULL)
		return;

	int i, j;
	for (i = 0; i < count; ++i)
		for (j = 0; j < count - i - 1; ++j)
			if (cmp(arr + size*(j+1), arr + size*j)) {
				swap(arr + size*j, arr + size*(j+1), size);
			}

#undef elem
}
