#pragma once
//* My Implementation of Template Vector

#include <iostream>

template <typename T> class Vector {
	T* data;

	size_t size;
	size_t capacity;

	//* Delete[] dynamic memory
	void free();

	//* Copy from other
	void copyFrom(const Vector<T>& other);

	//* Resize the data
	void resize();

	//* Calculate the new Capacity
	size_t calculateCapacity(const size_t newCapacity);

public:
	//! ====================================
	//* Default Constructor
	Vector();

	//* A Contructor that initializes the Vector with the given Size
	Vector(size_t initialCapacity);

	//* Copy Constructor
	Vector(const Vector<T>& other);

	//* Operator=
	Vector<T>& operator=(const Vector<T>& other);

	//* Move Constructor
	Vector(Vector<T>&& other);

	//* Move Operator=
	Vector<T>& operator=(Vector<T>&& other);

	//* Destructor
	~Vector();
	//! ====================================

	//! Operators
	Vector<T>& operator+=(const T& other);

	//! Can Throw if Invalid Index
	T& operator[](const size_t index);

	//! Can Throw if Invalid Index
	const T& operator[](const size_t index) const;

	//! ====================================

	//! Other Functions

	//* Clear the Contents
	void clear();

	//* Add a Vector
	void pushBack(const T& add);

	//* Add a Vector with Move Semantics
	void pushBack(T&& add);

	//* Remove the last Element
	//! Return 0 if good, 2 if Empty
	size_t popBack();

	//* Insert an Element on the Position
	//! Return 0 if good, 1 if invalid Position
	size_t insert(const T& add, const size_t position);

	//* Insert an Element on the Position with Move Semantics
	//! Return 0 if good, 1 if invalid Position
	size_t insert(T&& add, const size_t position);

	//* Remove the Element on the Position
	//! Return 0 if good, 1 if invalid Position, 2 if Empty
	size_t remove(const size_t position);

	//* Remove the Element on the Position
	//! Return 0 if good, 1 if invalid Position, 2 if Empty
	size_t remove(const T& toRemove);

	//* Check if Vector is empty
	const size_t isEmpty() const;

	//* Returns the capacity
	const size_t maxSize() const;

	//* Get the Size
	const size_t getSize() const;

	//* Public Resize
	void resize(const size_t newCapacity);

	//* Swap the Contents with another Vector
	void swap(Vector<T>& other);
};

//* Delete[] dynamic memory
template <typename T> void Vector<T>::free() { delete[] data; }

//* Copy from other
template <typename T> void Vector<T>::copyFrom(const Vector& other) {
	size = other.size;
	capacity = other.capacity;

	data = new T[capacity];
	for (size_t i = 0; i < size; ++i) {
		data[i] = other.data[i];
	}
}

//* Resize the data
template <typename T> void Vector<T>::resize() {
	capacity *= 2;

	T* temp = new T[capacity];

	for (size_t i = 0; i < size; ++i) {
		temp[i] = data[i];
	}

	delete[] data;
	data = temp;
}

//! ====================================
//* Default Constructor
template <typename T> Vector<T>::Vector() : size(0), capacity(8) {
	data = new T[capacity];
}

//* A Contructor that initializes the Vector with the given Size
template <typename T>
Vector<T>::Vector(size_t initialCapacity) : size(0) {
	capacity = calculateCapacity(initialCapacity);

	data = new T[capacity];
}

//* Copy Constructor
template <typename T> Vector<T>::Vector(const Vector<T>& other) {
	copyFrom(other);
}

//* Operator=
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
	if (this != &other) {
		free();

		copyFrom(other);
	}

	return *this;
}

//* Move Constructor
template <typename T>
Vector<T>::Vector(Vector<T>&& other)
	: data(other.data), size(other.size), capacity(other.capacity) {
	other.size = 0;
	other.capacity = 8;
	other.data = new T[other.capacity];
}

//* Move Operator=
template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) {
	if (this != &other) {
		free();

		size = other.size;
		capacity = other.capacity;
		data = other.data;

		other.size = 0;
		other.capacity = 8;
		other.data = new T[other.capacity];
	}

	return *this;
}

//* Destructor
template <typename T> Vector<T>::~Vector() { free(); }
//! ====================================

//! Operators
template <typename T>
Vector<T>& Vector<T>::operator+=(const T& other) {
	pushBack(other);

	return *this;
}

template <typename T> T& Vector<T>::operator[](const size_t index) {
	if (index < 0 || index >= size) {
		throw "Invalid Index";
	}

	return data[index];
}

template <typename T>
const T& Vector<T>::operator[](const size_t index) const {
	if (index < 0 || index >= size) {
		throw "Invalid Index";
	}

	return data[index];
}

//! ====================================

//* Clear the Contents
template <typename T> void Vector<T>::clear() {
	free();

	capacity = 8;
	data = new T[capacity];
	size = 0;
}

//* Add an Element
template <typename T> void Vector<T>::pushBack(const T& add) {
	if (size >= capacity) {
		resize();
	}

	data[size++] = add;

	return;
}
//* Add an Element with Move Semantics
template <typename T> void Vector<T>::pushBack(T&& add) {
	if (size >= capacity) {
		resize();
	}

	data[size++] = add;

	return;
}

//* Remove the last Element
//! Return 0 if good, 2 if Empty
template <typename T> size_t Vector<T>::popBack() {
	if (isEmpty()) {
		return 2;
	}

	--size;

	return 0;
}

//* Insert an Element on the Position
//! Return 0 if good, 1 if invalid Position
template <typename T>
size_t Vector<T>::insert(const T& add, const size_t position) {
	if (position < 0 || position > size) {
		return 1;
	}
	if (size >= capacity) {
		resize();
	}

	for (size_t i = size; i > position; i--) {
		data[i] = data[i - 1];
	}

	data[position] = add;
	size++;

	return 0;
}

//* Insert an Element on the Position with Move Semantics
//! Return 0 if good, 1 if invalid Position
template <typename T>
size_t Vector<T>::insert(T&& add, const size_t position) {
	if (position < 0 || position > size) {
		return 1;
	}
	if (size >= capacity) {
		resize(size + 1);
	}

	for (size_t i = size; i > position; i--) {
		data[i] = data[i - 1];
	}

	data[position] = add;
	size++;

	return 0;
}

//* Remove the Element on the Position
//! Return 0 if good, 1 if invalid Position, 2 if Empty
template <typename T> size_t Vector<T>::remove(const size_t position) {
	if (position < 0 || position >= size) {
		return 1;
	}

	if (isEmpty()) {
		return 2;
	}

	for (size_t i = position; i < size - 1; i++) {
		data[i] = data[i + 1];
	}

	size--;

	return 0;
}
template <typename T> size_t Vector<T>::remove(const T& toRemove) {
	for (size_t i = 0; i < size; ++i) {
		if (data[i] == toRemove) {
			remove(i);
			return 1;
		}
	}

	return 0;
}

//* Check if Vector is empty
template <typename T> const size_t Vector<T>::isEmpty() const {
	return size == 0;
}

//* Returns the capacity
template <typename T> const size_t Vector<T>::maxSize() const {
	return capacity;
}

//* Get the Size
template <typename T> const size_t Vector<T>::getSize() const {
	return size;
}

template <typename T>
size_t Vector<T>::calculateCapacity(const size_t newCapacity) {
	size_t result = 8;

	while (result < newCapacity) {
		result *= 2;
	}

	return result;
}

//* Public Resize
template <typename T> void Vector<T>::resize(const size_t newCapacity) {
	capacity = calculateCapacity(newCapacity);

	T* temp = new T[capacity];

	for (size_t i = 0; i < (size < capacity) ? size : capacity; ++i) {
		temp[i] = data[i];
	}

	delete[] data;
	data = temp;

	size = newCapacity;
}

//* Swap the Contents with another Vector
template <typename T> void Vector<T>::swap(Vector<T>& other) {
	Vector<T> tempVector = std::move(*this);
	*this = std::move(other);
	other = std::move(tempVector);
}