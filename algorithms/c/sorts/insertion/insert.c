#include <stdlib.h>
#include <string.h>

// simple int array version
void insertion_sort_int(int* arr, int size)
{
	if (arr == NULL)
		return;

	int i;
	for (i = 1; i < size; ++i) {
		int key = arr[i], j;
		for (j = i-1; j >= 0 && arr[j] > key; --j) {
			arr[j+1] = arr[j];
		}
		arr[j+1] = key;
	}
}

// generalized version
void insertion_sort(void* arr, int size, int count, int (*less)(void*, void*))
{
	if (arr == NULL || size <= 0 || less == NULL)
		return;

	int i, j;
	char* array = (char*) arr;
	char* key = (char*) malloc(size);
	for (i = 1; i < count; ++i) {
		memcpy(key, arr + size*i, size);
		for (j = i-1; j >= 0 && less(key, arr + size*j); --j) {
			memcpy(arr + size*(j+1), arr + size*j, size);
		}
		memcpy(arr + size*(j+1), key, size);
	}
}
