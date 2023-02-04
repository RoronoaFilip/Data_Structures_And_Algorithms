#include <algorithm>
#pragma once
template <typename T> int partition(T *arr, int start, int end) {
  int j = start;

  T pivot = arr[end];

  for (int i = start; i < end; i++) {
    if (arr[i] < pivot) {
      std::swap(arr[j++], arr[i]);
    }
  }

  std::swap(arr[j], arr[end]);

  return j;
}

template <typename T> int randomIndexPartition(T *arr, int start, int end) {
  srand(time(NULL));
  int random = start + rand() % (end - start);

  std::swap(arr[end], arr[random]);

  return partition(arr, start, end);
}

template <typename T> void quickSort(T *arr, int start, int end) {
  if (start < end) {

    int part = randomIndexPartition(arr, start, end);

    quickSort(arr, start, part - 1);
    quickSort(arr, part + 1, end);
  }
}