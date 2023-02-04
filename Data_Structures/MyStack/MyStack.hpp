//* A simple Data Structure that applies the rules first in last out

#include <iostream>

template <typename T>
class MyStack {
  T *data;

  int put;
  int capacity;

  int get;

private:
  void free();
  void copyFrom(const MyStack<T> &other);
  void resize();

public:
  MyStack();

  MyStack(const MyStack<T> &other);
  MyStack &operator=(const MyStack<T> &other);
  MyStack(MyStack<T> &&other);
  MyStack &operator=(MyStack<T> &&other);

  ~MyStack();

  void push(const T &other);
  void pop();
  bool isEmpty() const;
  T &top();
  const T &top() const;
};

template <typename T>
void MyStack<T>::free() {
  delete[] data;
}
template <typename T>
void MyStack<T>::copyFrom(const MyStack &other) {
  capacity = other.capacity;

  data = new T[capacity];
  for (size_t i = 0; i < put; ++i) {
    data[i] = other.data[i];
  }

  get = other.get;
  put = other.put;
}
template <typename T>
void MyStack<T>::resize() {
  capacity *= 2;

  T *temp = new T[capacity];
  for (size_t i = 0; i < put; ++i) {
    temp[i] = data[i];
  }
}

template <typename T>
MyStack<T>::MyStack() {
  put = 0;
  get = 0;

  capacity = 4;
  data = new T[capacity];
}

template <typename T>
MyStack<T>::MyStack(const MyStack<T> &other) {
  copyFrom(other);
}
template <typename T>
MyStack<T> &MyStack<T>::operator=(const MyStack<T> &other) {
  if (this != &other) {
    free();
    copyFrom(other);
  }

  return &this;
}

template <typename T>
MyStack<T>::MyStack(MyStack<T> &&other) : data(other.data), put(other.put),
                                          get(other.get), capacity(other.capacity) {}
template <typename T>
MyStack<T> &MyStack<T>::operator=(MyStack<T> &&other) {
  if (this != &other) {
    free();
    capacity = other.capacity;

    data = other.data;

    get = other.get;
    put = other.put;
  }

  return &this;
}

template <typename T>
MyStack<T>::~MyStack() {
  free();
}

template <typename T>
void MyStack<T>::push(const T &other) {
  if (put >= capacity) {
    resize();
  }

  get = put;
  data[put++] = other;
}

template <typename T>
void MyStack<T>::pop() {
  if (put == 0) {
    return;
  }

  --get;
  --put;
}

template <typename T>
bool MyStack<T>::isEmpty() const {
  return put == 0;
}

template <typename T>
const T &MyStack<T>::top() const {
  return data[get];
}
template <typename T>
T &MyStack<T>::top() {
  return data[get];
}