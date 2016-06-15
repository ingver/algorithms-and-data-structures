#include <utility> // for std::swap

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

