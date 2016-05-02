#include <utility> // std::swap

// simple version for int array
void bubble_sort(int* arr, int arr_size)
{
	for (int i = 0; i < arr_size; ++i)
		for (int j = 0; j < arr_size - i - 1; ++j)
			if (arr[j+1] < arr[j]) {
				int t = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = t;
			}
}

// template version
template <typename T>
void bubble_sort(T* arr, int arr_size)
{
	for (int i = 0; i < arr_size; ++i)
		for (int j = 0; j < arr_size - i - 1; ++j)
			if (arr[j+1] < arr[j])
				std::swap(arr[j], arr[j+1]);
}
