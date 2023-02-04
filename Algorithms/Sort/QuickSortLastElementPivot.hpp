#pragma once
template <typename T> int partition(T* arr, int start, int end) {
	int  j = start - 1;

	T pivot = arr[end];

	for (int i = start; i < end; i++) {
		if (arr[i] < pivot) {
			std::swap(arr[++j], arr[i]);
		}
	}

	std::swap(arr[j + 1], arr[end]);

	return (j + 1);
}

template <typename T> void QuickSortLastElementPivot(T* arr, int start, int end) {
	if (start < end) {

		int part = partition(arr, start, end);

		QuickSortLastElementPivot(arr, start, part - 1);
		QuickSortLastElementPivot(arr, part + 1, end);
	}
}