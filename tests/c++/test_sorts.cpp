#include <algorithm>
#include <iostream>
#include <cassert>
#include <cfloat>
#include <cstdlib>
#include <ctime>
#include "../../c++/algorithms/sorts/sorts.h"

int main()
{
	srand(time(NULL));

	const int size = 100;
	int iarr[size];
	double darr[size];

	std::cout << "TESTING SORTS...\n\n";

	for (auto& x: iarr)
		x = rand();
	std::cout << "Testing bubble sort for int array... ";
	bubble_sort(iarr, size);
	assert(std::is_sorted(iarr, iarr+size));
	std::cout << "sorted\n";

	for (auto& x: darr)
		x = (double)rand() / DBL_MAX;
	std::cout << "Testing bubble sort for double array... ";
	bubble_sort(darr, size);
	assert(std::is_sorted(darr, darr+size));
	std::cout << "sorted\n";

	for (auto& x: iarr)
		x = rand();
	std::cout << "Testing insertion sort for int array... ";
	insertion_sort(iarr, size);
	assert(std::is_sorted(iarr, iarr+size));
	std::cout << "sorted\n";

	for (auto& x: darr)
		x = (double)rand() / DBL_MAX;
	std::cout << "Testing insertion sort for double array... ";
	insertion_sort(darr, size);
	assert(std::is_sorted(darr, darr+size));
	std::cout << "sorted\n";

	for (auto& x: iarr)
		x = rand();
	std::cout << "Testing selection sort for int array... ";
	selection_sort(iarr, size);
	assert(std::is_sorted(iarr, iarr+size));
	std::cout << "sorted\n";

	for (auto& x: darr)
		x = (double)rand() / DBL_MAX;
	std::cout << "Testing selection sort for double array... ";
	selection_sort(darr, size);
	assert(std::is_sorted(darr, darr+size));
	std::cout << "sorted\n";

	return 0;
}
