//* A Data Structure that can store any Data or just point to nullptr

#pragma once
#include <exception>
#include <iostream>
template <typename T>
class Optional {
  T *data; //* Dynamic Memory

  void copyFrom(const Optional<T> &other);
  void free();

public:
  //* Default Constructor
  Optional();

  //* Constructor
  Optional(const T &obj);

  //* Copy Constructor
  Optional(const Optional<T> &other);

  //* Operator=
  Optional<T> operator=(const Optional<T> &other);

  //* Destructor
  ~Optional();

  //* Check if there is any data
  bool containsData() const;

  //* Get the Data
  const T &getData() const; //* Can throw an Exception for being Empty

  //* Change the Data
  void setData(const T &el);

  //* Clear the Data
  void clear();
};

template <typename T>
void Optional<T>::copyFrom(const Optional<T> &other) {
  if (other.containsData())
    data = new T(*other.data);
  else
    data = nullptr;
}

template <typename T>
void Optional<T>::free() {
  delete data;
}

template <typename T>
Optional<T>::Optional() : data(nullptr) {}

template <typename T>
Optional<T>::Optional(const T &obj) : data(nullptr) {
  setData(obj);
}

template <typename T>
Optional<T>::Optional(const Optional<T> &other) {
  copyFrom(other);
}

template <typename T>
Optional<T> Optional<T>::operator=(const Optional<T> &other) {
  if (this != &other) {
    free();
    copyFrom(other);
  }
  return *this;
}

//* Destructor
template <typename T>
Optional<T>::~Optional() {
  free();
}

template <typename T>
bool Optional<T>::containsData() const {
  return data != nullptr;
}

template <typename T>
const T &Optional<T>::getData() const {
  if (!containsData()) {
    throw std::logic_error("No data in Optional");
  }

  return *data;
}

template <typename T>
void Optional<T>::setData(const T &el) {
  delete data;
  data = new T(el); // copy const;
}

template <typename T>
void Optional<T>::clear() {
  free();
  data = nullptr;
}