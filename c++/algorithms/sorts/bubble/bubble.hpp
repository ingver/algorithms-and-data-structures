#include <utility> // for std::swap

template <typename T>
void bubble_sort(T arr[], int arr_size)
{
	for (int i = 0; i < arr_size; ++i)
		for (int j = 0; j < arr_size - i - 1; ++j)
			if (arr[j+1] < arr[j])
				std::swap(arr[j], arr[j+1]);
}
