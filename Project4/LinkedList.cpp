#include "LinkedList.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

LinkedList::LinkedList() {
	head = nullptr;
	size = 0;
}

LinkedList::LinkedList(Node* h) {
	Node *curr = h, *ptr = nullptr, *last = nullptr;
	// If null pointer passed
	if (h == nullptr) {
		head = nullptr;
		size = 0;
		return;
	}
	while (curr != nullptr) {
		// If empty linked list, add new node to list
		if (last == nullptr) {
			head = new Node(curr->getCoef(), curr->getExp());
			head->setNext(nullptr);
			last = head;
			std::cout << "head: " << last << std::endl;
	    }
		else {
			// If current term contains same exponent, combine like terms
			if (curr->getExp() == last->getExp())
				last->setCoef(last->getCoef() + curr->getExp());
			else {
				ptr = new Node(curr->getCoef(), curr->getExp());
				last->setNext(ptr);
				last = ptr;
				last->setNext(nullptr);
			}
		}
		curr = curr->getNext();
		size++;
	}
}

LinkedList::~LinkedList() {
	Node* ptr = head, *ptrNext = nullptr;
	while (ptr != nullptr) {
		ptrNext = ptr->getNext();
		delete ptr;
		ptr = ptrNext;
	}
	head = nullptr;
}

void LinkedList::setHead(Node* h) {
	// Node pointer curr used to traverse new linked list, temp used to hold values, ptr used to traverse old linked list
	Node* curr = nullptr, *temp = nullptr, *ptr = nullptr;
	// Deleting memory formerly allocated
	delete head;
	head = nullptr;
	
	head = new Node(h->getCoef(), h->getExp());
	size = 1;

	curr = head;
	temp = h->getNext();
	while (temp != nullptr) {
		ptr = new Node(temp->getCoef(), temp->getExp());
		curr->setNext(ptr);
		curr = ptr;
		temp = temp->getNext();
		size++;
	}
}

const Node* LinkedList::operator[](int pos) const {
	Node* ptr = head;
	for (int i = 0; i < size; i++) {
		if (i == pos)
			return ptr;
		else
			ptr = ptr->getNext();
	}
	return nullptr;
}

std::ostream& operator<<(std::ostream& out, const LinkedList& list) {
	const Node* ptr = nullptr;
	for (int i = 0; i < list.size; i++) {
		ptr = list[i];
		if (ptr->getCoef() < 0) {
			if (i == 0)
				out << "-";
			else
				out << " - ";
		}
		else if (ptr->getCoef() > 0 && i != 0) {
			out << " + ";
		}
		out << ptr;
		ptr = ptr->getNext();
	}
	return out;
}

void LinkedList::operator+=(const Node* n) {
	Node* curr = new Node(n->getCoef(), n->getExp()), *last = head;
	curr->setNext(nullptr);
	if (head == nullptr)
		head = curr;
	else {
		while (last->getNext() != nullptr)
			last = last->getNext();
		last->setNext(curr);
	}
	size++;
}

void LinkedList::sortList() {
	Node *curr = nullptr, *ptr = nullptr, *temp = nullptr;

	for (int i = 0; i < size; ++i) {
		curr = ptr = head;
		while (curr->getNext() != nullptr) {
			if (curr->getExp() < curr->getNext()->getExp()) {
				temp = curr->getNext();
				curr->setNext(temp->getNext());
				temp->setNext(curr);

				if (curr == head)
					head = ptr = temp;
				else
					ptr->setNext(temp);
				curr = temp;
			}
			ptr = curr;
			curr = curr->getNext();
		}
	}
}
