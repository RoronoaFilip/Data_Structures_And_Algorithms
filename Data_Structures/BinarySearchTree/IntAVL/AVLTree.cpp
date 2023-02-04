#pragma once
#include "AVLTree.h"


void AVLTree::free() {
	freeRec(root);
}

void AVLTree::freeRec(Node* root) {
	if (root == nullptr) {
		return;
	}

	freeRec(root->left);
	freeRec(root->right);

	delete root;
}

void AVLTree::copyFrom(const AVLTree& other) {
	copyFromRec(other.root, root);
}

void AVLTree::copyFromRec(const Node* other, Node*& root) {
	if (other == nullptr) {
		return;
	}

	root = new Node(other->data);

	copyFromRec(other->left, root->left);
	copyFromRec(other->right, root->right);
}

bool AVLTree::containsRec(const Node* root, const int n)  const {
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

AVLTree::Node* AVLTree::findMin(Node* start) const {
	Node* iter = start;
	while (iter->left != nullptr) {
		iter = iter->left;
	}

	return iter;
}

AVLTree::Node* AVLTree::findMax(Node* start) const {
	Node* iter = start;
	while (iter->right != nullptr) {
		iter = iter->right;
	}

	return iter;
}

size_t AVLTree::getDepth(Node* root) {
	if (root == nullptr) {
		return 0;
	}

	return root->depth;
}

void AVLTree::fixDepth(Node* root) {
	int leftChildHeight = getHeight(root->left);
	int rightChildHeight = getHeight(root->right);
	root->depth = leftChildHeight < rightChildHeight ? rightChildHeight + 1: leftChildHeight + 1;
}

int AVLTree::calculateBalanceFactor(Node* root) {
	return getDepth(root->right) - getDepth(root->left);
}

AVLTree::Node* AVLTree::rotateRight(Node* root) {
	Node* temp = root->left;
	root->left = temp->right;
	temp->right = root;

	fixDepth(root);
	fixDepth(temp);

	return temp;
}

AVLTree::Node* AVLTree::rotateLeft(Node* root) {
	Node* temp = root->right;
	root->right = temp->left;
	temp->left = root;

	fixDepth(root);
	fixDepth(temp);

	return temp;
}

AVLTree::Node* AVLTree::balance(Node* root) {
	fixDepth(root);
	if (calculateBalanceFactor(root) == -2) {
		if (calculateBalanceFactor(root->left) > 0)
			root->left = rotateLeft(root->left);
		return rotateRight(root);
	} else if (calculateBalanceFactor(root) == 2) {
		if (calculateBalanceFactor(root->right) < 0)
			root->right = rotateRight(root->right);
		return rotateLeft(root);
	}

	return root;
}

AVLTree::Node* AVLTree::removeRec(AVLTree::Node* root, const int n) {
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

	return balance(root);
}

size_t AVLTree::getHeight(Node* root) {
	if (root == nullptr) {
		return 0;
	}

	return std::max(getHeight(root->left), getHeight(root->right)) + 1;
}

void AVLTree::createTreeRec(const std::vector<int>& v, int start, int end, AVLTree::Node*& root) {
	if (start > end) {
		root = nullptr;
		return;
	}

	int mid = (start + end) / 2;
	root = new Node(v[mid]);

	createTreeRec(v, start, mid - 1, root->left);
	createTreeRec(v, mid + 1, end, root->right);
}

void AVLTree::inOrder(AVLTree::Node* current) const {
	if (current == nullptr) {
		return;
	}
	inOrder(current->left);
	std::cout << current->data << " ";
	inOrder(current->right);
}

AVLTree::AVLTree(const std::vector<int>& v) {
	if (!std::is_sorted(v.begin(), v.end())) {
		throw std::logic_error("Array should be sorted!");
	}
	createTreeRec(v, 0, v.size() - 1, root);
}

AVLTree::AVLTree(const AVLTree& other) {
	copyFrom(other);
}

AVLTree& AVLTree::operator=(const AVLTree& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

AVLTree::~AVLTree() {
	free();
}

bool AVLTree::isEmpty() const
{
	return root == nullptr;
}

AVLTree::Node* AVLTree::InsertRec(AVLTree::Node* root, const int n) {
	if (root == nullptr) {
		return new Node(n);
	}

	if (n < root->data) {
		root->left = InsertRec(root->left, n);
	} else {
		root->right = InsertRec(root->right, n);
	}

	return balance(root);
}

bool AVLTree::contains(const int n) const {
	return containsRec(root, n);
}

void AVLTree::insert(const int n) {
	root = InsertRec(root, n);
}

void AVLTree::remove(const int n) {
	root = removeRec(root, n);
}

void AVLTree::printInOrder()  const {
	inOrder(root);
}

size_t AVLTree::getHeight()
{
	return getHeight(root);
}