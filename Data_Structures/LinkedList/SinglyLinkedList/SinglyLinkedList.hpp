#pragma once
#include <iostream>

template <typename T>
class SinglyLinkedList {
public:
	struct Node {
		T data;
		Node* next;

		Node(const T& data, Node* next = nullptr) {
			this->data = data;
			this->next = next;
		}
	};

	Node* head;
	Node* tail;

	void copyFrom(const SinglyLinkedList<T>& other);
	void free();
public:
	SinglyLinkedList() {
		head = tail = nullptr;
	}
	SinglyLinkedList(const SinglyLinkedList<T>& other);
	SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>& other);
	~SinglyLinkedList();

	void pushFront(const T& el);
	void pushBack(const T& el);

	void popFront();

	void reverse();

	const T& front() const;
	const T& back() const;

	template <typename U>
	friend SinglyLinkedList<U> concat(SinglyLinkedList<U>& lhs, SinglyLinkedList<U>& rhs);

	void print() const;
};

template<typename T>
inline void SinglyLinkedList<T>::copyFrom(const SinglyLinkedList<T>& other) {
	Node* iter = other.head;

	while (iter != nullptr) {
		pushBack(iter->data);
		iter = iter->next;
	}

	return;
}

template<typename T>
inline void SinglyLinkedList<T>::free() {
	Node* iter = head;

	while (iter != nullptr) {
		Node* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	}

	head = tail = nullptr;
}

template<typename T>
inline SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other) {
	copyFrom(other);
}

template<typename T>
inline SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
inline SinglyLinkedList<T>::~SinglyLinkedList() {
	free();
}

template <typename T>
void SinglyLinkedList<T>::pushFront(const T& el) {
	Node* newNode = new Node(el);
	if (head == nullptr) {
		head = tail = newNode;
		return;
	}

	newNode->next = head;
	head = newNode;
	return;
}

template <typename T>
void SinglyLinkedList<T>::pushBack(const T& el) {
	Node* newNode = new Node(el);
	if (tail == nullptr) {
		head = tail = newNode;
		return;
	}

	tail->next = newNode;
	tail = newNode;
	return;
}

template <typename T>
void SinglyLinkedList<T>::popFront() {
	if (head == nullptr) {
		throw std::length_error("Empty list!");
	}

	if (head == tail) {
		delete head;
		head = tail = nullptr;
		return;
	}

	Node* temp = head;
	head = head->next;
	delete temp;
	return;
}

template<typename T>
inline void SinglyLinkedList<T>::reverse() {
	Node* curr = head;
	Node* prev = nullptr;

	while (curr != nullptr) {
		Node* temp = prev;
		prev = curr;
		curr = curr->next;

		prev->next = temp;
	}

	head = prev;
}

template<typename T>
const T& SinglyLinkedList<T>::front() const {
	if (head == nullptr) {
		throw std::length_error("Empty list!");
	}

	return head->data;
}

template<typename T>
const T& SinglyLinkedList<T>::back() const {
	if (tail == nullptr) {
		throw std::length_error("Empty list!");
	}

	return tail->data;
}

template<typename T>
inline void SinglyLinkedList<T>::print() const {
	Node* iter = head;

	while (iter != nullptr) {
		std::cout << iter->data << ' ';
		if (iter->next) {
			std::cout << "->" << ' ';
		}
		iter = iter->next;
	}
}

template<typename T>
inline SinglyLinkedList<T> concat(SinglyLinkedList<T>& lhs, SinglyLinkedList<T>& rhs) {
	SinglyLinkedList<T> result;

	if (lhs.head == nullptr) {
		result.head = rhs.head;
		result.tail = rhs.tail;
		return;
	} else if (rhs.head == nullptr) {
		result.head = lhs.head;
		result.tail = lhs.tail;
	} else {
		result.head = lhs.head;
		lhs->tail.next = rhs.head;
		result.tail = rhs.tail;
	}

	rhs.head = rhs.tail = lhs.head = lhs.tail = nullptr;

	return;
}