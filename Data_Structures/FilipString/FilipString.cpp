//* My Implementation of String

#include "FilipString.h"
#include <cstring>
#include <iostream>

#pragma warning(disable : 4996)

//* Copy Function for dynamic Memory
void FilipString::copyFrom(const FilipString &other) {
  size = other.size;
  data = new char[size + 1];

  strcpy(data, other.data);
}

//* Delete all of the dynamic Memory
void FilipString::free() { delete[] data; }

//! public:

//! ==========================================================
//! Constructor, Destructor, Operator=, Copy Constructor

//* Default Constructor
FilipString::FilipString() {
  data = new char[1];
  data[0] = '\0';
  size = 0;
}

//* Constructor to set the String
FilipString::FilipString(const char *newString) {
  size = strlen(newString);
  data = new char[size + 1];
  strcpy(data, newString);
}

//* Copy Constructor - create a new Object of type FilipString
FilipString::FilipString(const FilipString &other) { copyFrom(other); }

//* Operator= - Modify an EXISTING Object of type FilipString
FilipString &FilipString::operator=(const FilipString &other) {
  if (this != &other) {
    free();
    copyFrom(other);
  }
  return *this;
}

//* Move Constructor
FilipString::FilipString(FilipString &&other) {
  data = other.data;
  other.data = nullptr;

  size = other.size;
}

//* Move operator=
FilipString &FilipString::operator=(FilipString &&other) {
  if (this != &other) {
    free();
    data = other.data;
    other.data = nullptr;

    size = other.size;
  }

  return *this;
}

//*Destructor - delete[] dynamic Memory
FilipString::~FilipString() { free(); }

//! ===========================================================

void FilipString::print() const { std::cout << data << std::endl; }

//! Getters and Setters ===============================================

//* Get the Size of the String
int FilipString::getSize() const { return size; }

//* Get a const Pointer to the String
const char *FilipString::getCharPointer() const { return data; }

//* Get a const Pointer to the String
//! A NEW POINTER
char *FilipString::getCharPointerNew() const {
  char *temp = new char[size + 1];

  strcpy(temp, data);

  return temp;
}

//* Set a new String
void FilipString::setString(const FilipString &other) {
  if (this == &other || strcmp(data, other.data) == 0) {
    return;
  }

  free();
  size = strlen(other.data);
  data = new char[size + 1];
  strcpy(data, other.data);
}

//! Other Functions ================================================

//* Get a Substring from the String - a new char Array
FilipString FilipString::substring(const size_t start, const size_t end) const {
  size_t newStringSize = end - start + 1;

  FilipString newString;
  delete[] newString.data;

  newString.data = new char[newStringSize + 1];
  newString.size = newStringSize;

  size_t newStringIndex = 0;

  for (size_t i = start; i <= end; ++i) {
    newString.data[newStringIndex++] = data[i];
  }

  newString.data[newStringIndex] = '\0';

  return newString;
}

//* Check if String is empty
bool FilipString::isEmpty() const { return (size == 0); }

//* Swap constents with Other
void FilipString::swap(FilipString &other) {
  FilipString temp = std::move(*this);
  *this = std::move(other);
  other = std::move(temp);
}

//* Concatenate 2 Strings
void FilipString::concatenate(const FilipString &other) {
  char *temp = new char[getSize() + other.getSize() + 1];
  strcpy(temp, data);
  strcat(temp, other.data);

  delete[] data;
  data = temp;
  size += other.getSize();
}

//* Add a String to the End
void FilipString::push_back(const FilipString &other) { concatenate(other); }

//* Add a Symbol to the End
void FilipString::push_back(const char other) {
  char *temp = new char[size + 2];

  strcpy(temp, data);

  temp[size++] = other;
  temp[size] = '\0';

  free();
  data = temp;
}

//* Remove a Symbol from the End
void FilipString::pop_back() {
  if (size - 1 <= 0) {
    data[0] = '\0';
    return;
  }

  --size;

  char *temp = new char[size + 1];

  int tempIndex = 0;
  for (int i = 0; i < size - 1; ++i) {
    temp[tempIndex++] = data[i];
  }

  temp[tempIndex] = '\0';

  free();
  data = temp;
}

//* Clear and Reset the String
void FilipString::clear() {
  if (size != 0) {
    free();
    data = new char[1];
    data[0] = '\0';
    size = 0;
  }

  return;
}

//* Operator==
FilipString &FilipString::operator+=(const FilipString &other) {
  concatenate(other);

  return *this;
}

FilipString &FilipString::operator+=(const char other) {
  push_back(other);

  return *this;
}

bool FilipString::operator==(const FilipString &other) const {
  return (strcmp(data, other.data) == 0);
}

//* Operator!=
bool FilipString::operator!=(const FilipString &other) const {
  return strcmp(data, other.data) != 0;
}

//* Operator<
bool FilipString::operator<(const FilipString &other) const {
  return strcmp(data, other.data) == -1;
}

//* Operator<=
bool FilipString::operator<=(const FilipString &other) const {
  return *this == other || *this < other;
}

//* Operator<
bool FilipString::operator>(const FilipString &other) const {
  return strcmp(data, other.data) == 1;
}

//* Operator>=
bool FilipString::operator>=(const FilipString &other) const {
  return *this == other || *this > other;
}

//* Operator>>
std::istream &operator>>(std::istream &stream, FilipString &myString) {
  char input[1024];
  stream.getline(input, 1024, '\n');
  myString.push_back(input);

  return stream;
}

//* Operator<<
std::ostream &operator<<(std::ostream &stream, const FilipString &myString) {
  stream << myString.data;

  return stream;
}

//* Operator[]
//! Care For Exceptions
char FilipString::operator[](const size_t index) {
  if (index >= size) {
    throw false;
  }

  return data[index];
}
//* Operator[]
//! Care For Exceptions
const char FilipString::operator[](const size_t index) const {
  if (index >= size) {
    return '~';
  }

  return data[index];
}

FilipString operator+(const FilipString &lhs, const FilipString &rhs) {
  FilipString temp(lhs);
  temp += rhs;

  return temp;
}