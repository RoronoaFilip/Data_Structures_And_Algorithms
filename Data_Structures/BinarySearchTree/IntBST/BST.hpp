#pragma once
#include <iostream>
#include <vector>

class BST {
public:
	struct Node {
		int data;
		Node* left;
		Node* right;

		Node(const int data, Node* left = nullptr, Node* right = nullptr) : data(data), left(left), right(right) {}
	};

private:
	Node* root = nullptr;

	void free();
	void freeRec(Node* root);

	void copyFrom(const BST& other);
	void copyFromRec(const Node* other, Node*& root);

	bool containsRec(const Node* root, const int n) const;
	Node* removeRec(Node* root, const int n);
	Node* InsertRec(Node* root, const int n);

	size_t getHeight(Node* root);

	Node* findMin(Node* start) const;
	Node* findMax(Node* start) const;

	void createTreeRec(const std::vector<int>& v, int start, int end, Node*& root);

	void inOrder(Node* current) const;
public:
	BST() = default;
	BST(const std::vector<int>& v);

	BST(const BST& other);
	BST& operator= (const BST& other);
	~BST();

	bool isEmpty() const;
	bool contains(const int n) const;
	void insert(const int n);
	void remove(const int n);
	void printInOrder() const;

	size_t getHeight();
};

void BST::free() {
	freeRec(root);
}

void BST::freeRec(Node* root) {
	if (root == nullptr) {
		return;
	}

	freeRec(root->left);
	freeRec(root->right);

	delete root;
}

void BST::copyFrom(const BST& other) {
	copyFromRec(other.root, root);
}

void BST::copyFromRec(const Node* other, Node*& root) {
	if (other == nullptr) {
		return;
	}

	root = new Node(other->data);

	copyFromRec(other->left, root->left);
	copyFromRec(other->right, root->right);
}

bool BST::containsRec(const Node* root, const int n)  const {
	if (root == nullptr) {
		return false;
	}

	if (root->data == n) {
		return true;
	}

	if (n > root->data) {
		return containsRec(root->right, n);
	}

	return containsRec(root->left, n);

}

BST::Node* BST::findMin(Node* start) const {
	Node* iter = start;
	while (iter->left != nullptr) {
		iter = iter->left;
	}

	return iter;
}

BST::Node* BST::findMax(Node* start) const {
	Node* iter = start;
	while (iter->right != nullptr) {
		iter = iter->right;
	}

	return iter;
}

BST::Node* BST::removeRec(BST::Node* root, const int n) {
	if (root == nullptr) {
		return root;
	}

	if (n < root->data) {
		root->left = removeRec(root->left, n);
	} else if (n > root->data) {
		root->right = removeRec(root->right, n);
	} else {

		if (root->left == nullptr) {
			Node* toReturn = root->right;
			delete root;
			return toReturn;
		} else if (root->right == nullptr) {
			Node* toReturn = root->left;
			delete root;
			return toReturn;
		}

		Node* minOnTheRight = findMin(root->right);

		root->data = minOnTheRight->data;

		root->right = removeRec(root->right, minOnTheRight->data);

	}

	return root;
}

size_t BST::getHeight(Node* root) {
	if (root == nullptr) {
		return 0;
	}

	return std::max(getHeight(root->left), getHeight(root->right)) + 1;
}

void BST::createTreeRec(const std::vector<int>& v, int start, int end, BST::Node*& root) {
	if (start > end) {
		root = nullptr;
		return;
	}

	int mid = (start + end) / 2;
	root = new Node(v[mid]);
	createTreeRec(v, start, mid - 1, root->left);
	createTreeRec(v, mid + 1, end, root->right);
}

void BST::inOrder(BST::Node* current) const {
	if (current == nullptr) {
		return;
	}
	inOrder(current->left);
	std::cout << current->data << " ";
	inOrder(current->right);
}

BST::BST(const std::vector<int>& v) {
	if (!std::is_sorted(v.begin(), v.end())) {
		throw std::logic_error("Array should be sorted!");
	}
	createTreeRec(v, 0, v.size() - 1, root);
}

BST::BST(const BST& other) {
	copyFrom(other);
}

BST& BST::operator=(const BST& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

BST::~BST() {
	free();
}

bool BST::isEmpty() const
{
	return root == nullptr;
}

BST::Node* BST::InsertRec(BST::Node* root, const int n) {

	if (root == nullptr) {
		return new Node(n);

	}

	if (n <= root->data) {
		root->left = InsertRec(root->left, n);
	} else if (n > root->data) {
		root->right = InsertRec(root->right, n);
	}

	return root;
}

bool BST::contains(const int n) const {
	return containsRec(root, n);
}

void BST::insert(const int n) {
	root = InsertRec(root, n);
}

void BST::remove(const int n) {
	root = removeRec(root, n);
}

void BST::printInOrder()  const {
	inOrder(root);
}

size_t BST::getHeight()
{
	return getHeight(root);
}
