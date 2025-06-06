#include "LinkedList.h"

int main() {
       	LinkedList<int> list = {1, 2, 3, 4, 5};

        std::cout << "Initial list: ";
	list.print();

	list.insertFront(0);
	list.insertBack(6);

	std::cout << "After insertions: ";
	list.print();

	list.removeFront();
	list.removeBack();
	std::cout << "After removals: ";
	list.print();

	return 0;
}
