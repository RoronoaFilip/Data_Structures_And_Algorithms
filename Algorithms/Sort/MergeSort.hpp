template <typename T>
void merge(T *arr1, T *arr2, size_t size1, size_t size2) {
  T *temp = new T[size1 + size2];

  size_t arr1Index = 0;
  size_t arr2Index = 0;
  size_t tempIndex = 0;

  while (arr1Index < size1 && arr2Index < size2) {
    if (arr1[arr1Index] < arr2[arr2Index]) {
      temp[tempIndex++] = arr1[arr1Index++];
    } else {
      temp[tempIndex++] = arr2[arr2Index++];
    }
  }

  while (arr1Index < size1) {
    temp[tempIndex++] = arr1[arr1Index++];
  }

  while (arr2Index < size2) {
    temp[tempIndex++] = arr2[arr2Index++];
  }

  for (size_t i = 0; i < size1 + size2; ++i) {
    arr1[i] = temp[i];
  }

  delete[] temp;
}

template <typename T>
void mergeSort(T *arr, size_t size) {
  if (size <= 1) {
    return;
  }

  size_t mid = size / 2;

  mergeSort(arr, mid);
  mergeSort(arr + mid, size - mid);

  merge(arr, arr + mid, mid, size - mid);
}