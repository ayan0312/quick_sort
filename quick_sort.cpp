#include <stdio.h>
#include <stdlib.h> 
#include <stack>
#include <map>
#include <time.h>

#define RANDOM(L, R)	(L + rand() % ((R) - (L) + 1)) // gen a random integer in [L, R]

namespace utility {
	template<typename T>
	static inline void swap(T& x, T& y)
	{
		T _t(x);
		x = y;
		y = _t;
	}

	template<typename T>
	static void printlist(T& list, int count) {
		int i;
		for (i = 0; i < count; i++)
			printf("%d  ", list[i]);
		printf("\n");
	}
}

namespace algorithm {
	template<typename T>
	static int partition(T list[], int begin, int end) {
		int pivot_index = RANDOM(begin, end);
		T pivot = list[pivot_index];
		utility::swap(list[begin], list[pivot_index]);

		int left = begin + 1;
		int right = end;

		while (left <= right) {
			while ((left <= end) && (list[left] <= pivot))
				left++;
			while ((right >= begin) && (list[right] > pivot))
				right--;
			if (left < right)
				utility::swap(list[left], list[right]);
		}

		utility::swap(list[begin], list[right]);
		return right;
	}

	template<typename T>
	static int partition_single(T list[], int begin, int end) {
		int pivot_index = RANDOM(begin, end);
		T pivot = list[pivot_index];
		utility::swap(list[begin], list[pivot_index]);

		int mark = begin;

		for (int i = begin + 1; i <= end; i++) {
			if (list[i] < pivot) {
				mark++;
				utility::swap(list[i], list[mark]);
			}
		}

		utility::swap(list[begin], list[mark]);
		return mark;
	}

	template<typename T>
	static void quick_sort_recursion(T list[], int begin, int end, int (*func)(T[], int, int)) {
		if (begin >= end) return;
		int pivot_index = func(list, begin, end);
		quick_sort_recursion(list, begin, pivot_index - 1, func);
		quick_sort_recursion(list, pivot_index + 1, end, func);
	}

	template<typename T>
	static void quick_sort_stack(T list[], int begin, int end, int (*func)(T[], int, int)) {
		if (begin >= end) return;
		using namespace std;
		stack<map<int, int>> quickSortStack;
		map<int, int> rootParam;
		rootParam[0] = begin;
		rootParam[1] = end;
		quickSortStack.push(rootParam);

		while (!quickSortStack.empty()) {
			map<int, int> param = quickSortStack.top();
			quickSortStack.pop();

			int paramBegin = param.find(0)->second;
			int paramEnd = param.find(1)->second;
			int pivot_index = func(list, paramBegin, paramEnd);

			if (paramBegin < pivot_index - 1) {
				map<int, int> leftParam;
				leftParam[0] = paramBegin;
				leftParam[1] = pivot_index - 1;
				quickSortStack.push(leftParam);
			}

			if (paramEnd > pivot_index + 1) {
				map<int, int> rightParam;
				rightParam[0] = pivot_index + 1;
				rightParam[1] = paramEnd;
				quickSortStack.push(rightParam);
			}
		}
	}
}

int quick_sort_test()
{
	printf("quick sort for recursion testing:\n");

	const int MAX_ELEMENTS = 10;
	int list[MAX_ELEMENTS];

	int i = 0;
	srand((unsigned)time(NULL));

	for (i = 0; i < MAX_ELEMENTS; i++) {
		list[i] = rand() % 100;
	}

	printf("  double:\n");
	printf("    The list before sorting is:\n");
	utility::printlist(list, MAX_ELEMENTS);

	algorithm::quick_sort_recursion(list, 0, MAX_ELEMENTS - 1, algorithm::partition);

	printf("    The list after sorting using quicksort algorithm:\n");
	utility::printlist(list, MAX_ELEMENTS);

	for (i = 0; i < MAX_ELEMENTS; i++) {
		list[i] = rand() % 100;
	}

	printf("  single:\n");
	printf("    The list before sorting is:\n");
	utility::printlist(list, MAX_ELEMENTS);

	algorithm::quick_sort_recursion(list, 0, MAX_ELEMENTS - 1, algorithm::partition_single);

	printf("    The list after sorting using quicksort algorithm:\n");
	utility::printlist(list, MAX_ELEMENTS);

	printf("\n");
	printf("quick sort for stack testing:\n");

	for (i = 0; i < MAX_ELEMENTS; i++) {
		list[i] = rand() % 100;
	}

	printf("  double:\n");
	printf("    The list before sorting is:\n");
	utility::printlist(list, MAX_ELEMENTS);

	algorithm::quick_sort_stack(list, 0, MAX_ELEMENTS - 1, algorithm::partition);

	printf("    The list after sorting using quicksort algorithm:\n");
	utility::printlist(list, MAX_ELEMENTS);

	for (i = 0; i < MAX_ELEMENTS; i++) {
		list[i] = rand() % 100;
	}

	printf("  single:\n");
	printf("    The list before sorting is:\n");
	utility::printlist(list, MAX_ELEMENTS);

	algorithm::quick_sort_stack(list, 0, MAX_ELEMENTS - 1, algorithm::partition_single);

	printf("    The list after sorting using quicksort algorithm:\n");
	utility::printlist(list, MAX_ELEMENTS);

	return 0;
}

int main()
{
	quick_sort_test();
	system("pause");
	return 0;
}