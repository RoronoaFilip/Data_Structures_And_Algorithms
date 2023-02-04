#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

class AVLTree {
public:
	struct Node {
		int data;
		int depth;
		Node* left;
		Node* right;

		Node(const int data, Node* left = nullptr, Node* right = nullptr) : data(data), depth(1), left(left), right(right) {}
	};

private:
	Node* root = nullptr;

	void free();
	void freeRec(Node* root);

	void copyFrom(const AVLTree& other);
	void copyFromRec(const Node* other, Node*& root);

	bool containsRec(const Node* root, const int n) const;
	Node* removeRec(Node* root, const int n);
	Node* InsertRec(Node* root, const int n);

	size_t getHeight(Node* root);

	Node* findMin(Node* start) const;
	Node* findMax(Node* start) const;

	size_t getDepth(Node* root);
	void fixDepth(Node* root);
	int calculateBalanceFactor(Node* root);

	Node* rotateRight(Node* root);
	Node* rotateLeft(Node* root);

	Node* balance(Node* root);

	void createTreeRec(const std::vector<int>& v, int start, int end, Node*& root);

	void inOrder(Node* current) const;
public:
	AVLTree() = default;
	AVLTree(const std::vector<int>& v);

	AVLTree(const AVLTree& other);
	AVLTree& operator= (const AVLTree& other);
	~AVLTree();

	bool isEmpty() const;
	bool contains(const int n) const;
	void insert(const int n);
	void remove(const int n);
	void printInOrder() const;

	size_t getHeight();
};