#include <utility> // for std::swap

template <typename T>
void qsort(T arr[], int size)
{
	if (size <= 1)
		return;

	T pivot = arr[0];
	// make partitions
	int swap_idx = 1;
	for (int i = 1; i < size; ++i)
		if (!(pivot < arr[i]))
			std::swap(arr[i], arr[swap_idx++]);

	std::swap(arr[0], arr[swap_idx-1]);

	// sorting left partition
	if (swap_idx != 1)
		qsort(arr, swap_idx-1);

	// sorting right partition
	if (swap_idx != size - 1)
		qsort(arr + swap_idx, size - swap_idx);
}
