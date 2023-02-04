#pragma once

template <class T> int binarySearch(const T *arr, int len, const T &searched) {
  int leftIndex = 0;
  int rightIndex = len - 1;

  while (leftIndex <= rightIndex) {

    int midIndex = leftIndex / 2 + rightIndex / 2;

    if (arr[midIndex] == searched) {
      return midIndex;
    }

    if (arr[midIndex] > searched) {
      rightIndex = midIndex - 1;
    } else {
      leftIndex = midIndex + 1;
    }
  }

  //! Position where searched Element must be placed
  return -(leftIndex + 1);
}