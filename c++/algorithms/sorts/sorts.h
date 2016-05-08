#ifndef CPP_SORTS_H
#define CPP_SORTS_H

#include <utility>

// =============================================================================
// bubble sort
// =============================================================================

// simple version for int array
void bubble_sort(int* arr, int size);


// template version
template <typename T>
void bubble_sort(T arr[], int arr_size)
{
	for (int i = 0; i < arr_size; ++i)
		for (int j = 0; j < arr_size - i - 1; ++j)
			if (arr[j+1] < arr[j])
				std::swap(arr[j], arr[j+1]);
}



// =============================================================================
// insertion sort
// =============================================================================

// simple array version
void insertion_sort(int* arr, int size);

// template version
template <typename T>
void insertion_sort(T arr[], int size)
{
	for (int i = 1; i < size; ++i) {
		int j;
		T key = arr[i];
		for (j = i-1; j >= 0 && arr[j] > key; --j) {
			arr[j+1] = arr[j];
		}
		arr[j+1] = key;
	}
}

// =============================================================================
// selection sort
// =============================================================================

// 
// simple array version
void selection_sort(int* arr, int size);

// template version
template <typename T>
void selection_sort(T* arr, int size)
{
	for (int i = 0; i < size; ++i) {
		int min_index = i;
		for (int j = i+1; j < size; ++j)
			if (arr[j] < arr[min_index])
				min_index = j;

		if (i != min_index)
			std::swap(arr[i], arr[min_index]);
	}
}

#endif
