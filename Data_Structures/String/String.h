//* My Implementation of String

#pragma once
#include <cstring>
#include <iostream>

class String {
  char *data;
  size_t size;

  //* Copy Function for dynamic Memory
  void copyFrom(const String &other);

  //* Delete all of the dynamic Memory
  void free();

public:
  //! ==========================================================
  //! Constructor, Destructor, (Move)Operator=, Copy/Move Constructor

  //* Default Constructor
  String();

  //* Constructor to set the String
  String(const char *newString);

  //* Copy Constructor
  String(const String &other);

  //* Operator=
  String &operator=(const String &other);

  //* Move Constructor
  String(String &&other);

  //* Move operator=
  String &operator=(String &&other);

  //* Destructor
  ~String();

  //
  //
  //! ===========================================================
  //* Operators
  String &operator+=(const String &other);
  String &operator+=(const char other);
  bool operator==(const String &other) const;
  bool operator!=(const String &other) const;
  bool operator<(const String &other) const;
  bool operator<=(const String &other) const;
  bool operator>(const String &other) const;
  bool operator>=(const String &other) const;
  friend std::istream &operator>>(std::istream &stream, String &myString);
  friend std::ostream &operator<<(std::ostream &stream,
                                  const String &myString);

  //! Care For Exceptions
  char operator[](const size_t index);
  //! Care For Exceptions
  const char operator[](const size_t index) const;

  //* Print the String
  void print() const;

  //
  //
  //! Getters and Setters ===============================================
  //* Get the Size of the String
  int getSize() const;

  //* Set a new String
  void setString(const String &other);

  //* Get a const Pointer to the String
  const char *getCharPointer() const;

  //* Get a const Pointer to the String
  //! A NEW POINTER
  char *getCharPointerNew() const;

  //
  //
  //! Other Functions ================================================

  //* Get a Substring from the String
  //! start and end are INDEXES!
  String substring(const size_t start, const size_t end) const;

  //* Check if String is empty
  bool isEmpty() const;

  //* Swap constents with Other
  void swap(String &other);

  //* Concatenate 2 Strings
  void concatenate(const String &other);

  //* Add a String to the End
  void push_back(const String &other);

  //* Add a Symbol to the End
  void push_back(const char add);

  //* Remove a Symbol from the End
  void pop_back();

  //* Clear and Reset the String
  void clear();
};

String operator+(const String &lhs, const String &rhs);