#include <stdlib.h>
#include <string.h>

// simple int array version
void bubble_sort(int* arr, int size)
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
void sort_bubble(void* arr, int size, int count, int (*less)(void*, void*))
{
	int i, j;
	char* array = (char*) arr;
	for (i = 0; i < count; ++i)
		for (j = 0; j < count - i - 1; ++j)
			if (less(arr + size*(j+1), arr + size*j)) {
				swap(arr + size*j, arr + size*(j+1), size);
			}
}
