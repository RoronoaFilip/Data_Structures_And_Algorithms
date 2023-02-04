//* My Implementation of Vector

#pragma once
#include <iostream>

template <typename T>
class FilipVector {
  T *data;

  size_t size;
  size_t capacity;

  //* Delete[] dynamic memory
  void free();

  //* Copy from other
  void copyFrom(const FilipVector &other);

  //* Resize the data
  void resize();

  //* Swap to Ts with Pointers
  void swap(T *lhs, T *rhs);
  //* Swap to Ts with Reference
  void swap(T &lhs, T &rhs);

public:
  //! ====================================
  //* Default Constructor
  FilipVector();

  //* Copy Constructor
  FilipVector(const FilipVector &other);

  //* Operator=
  FilipVector &operator=(const FilipVector &other);

  //* Move Constructor
  FilipVector(FilipVector &&other);

  //* Move Operator=
  FilipVector &operator=(FilipVector &&other);

  //* Destructor
  ~FilipVector();
  //! ====================================

  //! Operators
  FilipVector<T> &operator+=(const T &other);
  T &operator[](const size_t index);
  const T &operator[](const size_t index) const;

  // friend std::istream &operator>>(std::istream &stream, FilipVector &myVector);
  // friend std::ostream &operator<<(std::ostream &stream, const FilipVector &myVector);

  //* Lexicographical operators
  int operator==(const FilipVector<T> &other) const;
  int operator!=(const FilipVector<T> &other) const;
  int operator<(const FilipVector<T> &other) const;
  int operator<=(const FilipVector<T> &other) const;
  int operator>(const FilipVector<T> &other) const;
  int operator>=(const FilipVector<T> &other) const;
  //! ====================================

  //! Other Functions

  //* Clear the Contents
  void clear();

  //* Add a Vector
  size_t push_back(const T &add);
  //* Add a Vector with Move Semantics
  size_t push_back(T &&add);

  //* Remove the last Element
  size_t pop_back();

  //* Insert an Element on the Position
  size_t insert(const T &add, const size_t position);
  //* Insert an Element on the Position with Move Semantics
  size_t insert(T &&add, const size_t position);

  //* Remove the Element on the Position
  size_t remove(const size_t position);

  //* Check if Vector is empty
  const size_t isEmpty() const;

  //* Returns the capacity
  const size_t max_size() const;

  //* Get the Size
  const size_t getSize() const;
};

//! More Operators
template <typename T>
FilipVector<T> operator+(const FilipVector<T> &lhs, const FilipVector<T> &rhs);

//* Delete[] dynamic memory
template <typename T>
void FilipVector<T>::free() {
  delete[] data;
}

//* Copy from other
template <typename T>
void FilipVector<T>::copyFrom(const FilipVector &other) {
  size = other.size;
  capacity = other.capacity;

  data = new T[capacity];
  for (size_t i = 0; i < size; ++i) {
    data[i] = other.data[i];
  }
}

//* Resize the data
template <typename T>
void FilipVector<T>::resize() {
  capacity *= 2;

  T *temp = new T[capacity];

  for (size_t i = 0; i < size; ++i) {
    temp[i] = data[i];
  }

  delete[] data;
  data = temp;
}

//* Swap to Ts with Pointers
template <typename T>
void FilipVector<T>::swap(T *lhs, T *rhs) {
  T *ptr = lhs;
  lhs = rhs;
  rhs = ptr;
}
//* Swap to Ts with Reference
template <typename T>
void FilipVector<T>::swap(T &lhs, T &rhs) {
  T ptr = lhs;
  lhs = rhs;
  rhs = ptr;
}

//! ====================================
//* Default Constructor
template <typename T>
FilipVector<T>::FilipVector() : size(0), capacity(8) {
  data = new T[capacity];
}

//* Copy Constructor
template <typename T>
FilipVector<T>::FilipVector(const FilipVector<T> &other) {
  copyFrom(other);
}

//* Operator=
template <typename T>
FilipVector<T> &FilipVector<T>::operator=(const FilipVector<T> &other) {
  if (this != &other) {
    free();
    copyFrom(other);
  }

  return *this;
}

//* Move Constructor
template <typename T>
FilipVector<T>::FilipVector(FilipVector &&other) : data(other.data), size(other.size), capacity(other.capacity) {}

//* Move Operator=
template <typename T>
FilipVector<T> &FilipVector<T>::operator=(FilipVector &&other) {
  if (this != &other) {
    free();
    size = other.size;
    capacity = other.capacity;

    data = other.data;
  }

  return *this;
}

//* Destructor
template <typename T>
FilipVector<T>::~FilipVector() {
  free();
}
//! ====================================

//! Operators
template <typename T>
FilipVector<T> &FilipVector<T>::operator+=(const T &other) {
  push_back(other);

  return *this;
}

template <typename T>
T &FilipVector<T>::operator[](const size_t index) {
  if (index + 1 <= size) {
    return data[index];
  }

  return data[0];
}

template <typename T>
const T &FilipVector<T>::operator[](const size_t index) const {
  if (index + 1 <= size) {
    return data[index];
  }

  return data[0];
}

// template <typename T>
// std::istream &operator>>(std::istream &stream, FilipVector<T> &myVector) {
//   FilipVector<T> temp;
//   stream >> temp;

//   myVector.push_back(temp);

//   return stream;
// }

// template <typename T>
// std::ostream &operator<<(std::ostream &stream, const FilipVector<T> &myVector) {
//   for (size_t i = 0; i < myVector.size; ++i) {
//     stream << myVector.data[i] << " ";
//   }

//   return stream;
// }

//* Lexicographical operators
//* -2 - first is smaller, 2 - second is smaller
//* -1 - first has word1 < word2, 1 - seconds has word1 < word2
template <typename T>
int FilipVector<T>::operator==(const FilipVector &other) const {
  if (size < other.size) {
    return -2;
  } else if (other.size < size) {
    return 2;
  }

  for (size_t i = 0; i < size; ++i) {
    if (data[i] != other.data[i]) {
      if (data[i] < other.data[i]) {
        return -1;
      } else {
        return 1;
      }
    }
  }

  return 0;
}

template <typename T>
int FilipVector<T>::operator!=(const FilipVector<T> &other) const {
  return (*this == other) != 0;
}
template <typename T>
int FilipVector<T>::operator<(const FilipVector<T> &other) const {
  return ((*this == other) == -1) ||
         ((*this == other) == -2);
}
template <typename T>
int FilipVector<T>::operator<=(const FilipVector<T> &other) const {
  return ((*this == other) == -1) ||
         ((*this == other) == -2) ||
         (*this == other) == 0;
}
template <typename T>
int FilipVector<T>::operator>(const FilipVector<T> &other) const {
  return ((*this == other) == 1) ||
         ((*this == other) == 2);
}
template <typename T>
int FilipVector<T>::operator>=(const FilipVector<T> &other) const {
  return ((*this == other) == 1) ||
         ((*this == other) == 2) ||
         (*this == other) == 0;
}

//! ====================================

//* Clear the Contents
template <typename T>
void FilipVector<T>::clear() {
  free();
  capacity = 8;
  T *temp = new T[capacity];
  data = temp;
  size = 0;
}

//* Add an Element
template <typename T>
size_t FilipVector<T>::push_back(const T &add) {
  if (size >= capacity) {
    resize();
  }

  data[size++] = add;

  return 1;
}
//* Add an Element with Move Semantics
template <typename T>
size_t FilipVector<T>::push_back(T &&add) {
  if (size >= capacity) {
    resize();
  }

  data[size++] = add;

  return 1;
}

//* Remove the last Element
template <typename T>
size_t FilipVector<T>::pop_back() {
  T temp;
  data[--size] = temp;

  return 1;
}

//* Insert an Element on the Position
template <typename T>
size_t FilipVector<T>::insert(const T &add, const size_t position) {
  if (position + 1 >= size) {
    return 0;
  }

  ++size;

  if (size >= capacity) {
    resize();
  }

  T *temp = new T[capacity];

  size_t dataIndex = 0;
  for (size_t i = 0; i < position; ++i) {
    temp[i] = data[dataIndex++];
  }

  temp[position] = add;

  for (size_t i = position + 1; i < size; ++i) {
    temp[i] = data[dataIndex++];
  }

  delete[] data;
  data = temp;

  return 1;
}

//* Insert an Element on the Position with Move Semantics
template <typename T>
size_t FilipVector<T>::insert(T &&add, const size_t position) {
  if (position + 1 >= size) {
    return 0;
  }

  ++size;

  if (size >= capacity) {
    resize();
  }

  T *temp = new T[capacity];

  size_t dataIndex = 0;
  for (size_t i = 0; i < position; ++i) {
    temp[i] = data[dataIndex++];
  }

  temp[position] = add;

  for (size_t i = position + 1; i < size; ++i) {
    temp[i] = data[dataIndex++];
  }

  delete[] data;
  data = temp;

  return 1;
}

//* Remove the Element on the Position
template <typename T>
size_t FilipVector<T>::remove(const size_t position) {
  if (position + 1 >= size) {
    return 0;
  }

  for (size_t i = position; i < size - 1; ++i) {
    swap(data[i], data[i + 1]);
  }

  pop_back();

  return 1;
}

//* Check if Vector is empty
template <typename T>
const size_t FilipVector<T>::isEmpty() const {
  return size == 0;
}

//* Returns the capacity
template <typename T>
const size_t FilipVector<T>::max_size() const {
  return capacity;
}

//* Get the Size
template <typename T>
const size_t FilipVector<T>::getSize() const {
  return size;
}