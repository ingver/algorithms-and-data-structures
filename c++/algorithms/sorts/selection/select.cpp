#include "../sorts.h"

void selection_sort(int* arr, int size)
{
	for (int i = 0; i < size; ++i) {
		int min_index = i;
		for (int j = i+1; j < size; ++j)
			if (arr[j] < arr[min_index])
				min_index = j;

		if (i != min_index) {
			int t = arr[min_index];
			arr[min_index] = arr[i];
			arr[i] = t;
		}
	}
}
