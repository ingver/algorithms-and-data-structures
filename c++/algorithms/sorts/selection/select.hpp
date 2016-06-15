#include <utility> // for std::swap

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
