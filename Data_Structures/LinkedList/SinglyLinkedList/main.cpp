#include <iostream>
#include "SinglyLinkedList.hpp"
using namespace std;

int main() {
	SinglyLinkedList<int> list;

	srand(time(0));
	for (int i = 0; i < 5; ++i) {
		list.pushBack(rand() % 100);
	}

	list.print();
	list.reverse();
	cout << endl;
	list.print();
}
