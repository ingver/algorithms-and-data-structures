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

	std::cout << "TESTING SORTS...\n\n";

	for (auto& x: iarr)
		x = rand();
	std::cout << "Testing bubble sort... ";
	bubble_sort(iarr, size);
	assert(std::is_sorted(iarr, iarr+size));
	std::cout << "sorted\n";

	for (auto& x: iarr)
		x = rand();
	std::cout << "Testing insertion sort... ";
	insertion_sort(iarr, size);
	assert(std::is_sorted(iarr, iarr+size));
	std::cout << "sorted\n";

	for (auto& x: iarr)
		x = rand();
	std::cout << "Testing selection sort... ";
	selection_sort(iarr, size);
	assert(std::is_sorted(iarr, iarr+size));
	std::cout << "sorted\n";

	for (auto& x: iarr)
		x = rand();
	std::cout << "Testing quick sort... ";
	qsort(iarr, size);
	assert(std::is_sorted(iarr, iarr+size));
	std::cout << "sorted\n";

	return 0;
}
