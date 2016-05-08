#include "../sorts.h"

void bubble_sort(int* arr, int size)
{
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size - i - 1; ++j)
			if (arr[j+1] < arr[j]) {
				int t = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = t;
			}
}
