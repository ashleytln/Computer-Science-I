#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <iostream>

class LinkedList {
private:
	Node* head = nullptr;
	int size = 0;
//	deleteList();
public:
	// Default constructor
	LinkedList();
	// Overloaded constructor
	LinkedList(Node*);
	// Destructor
	~LinkedList();
	// Accessors
	Node* getHead() const { return head; }
	int getSize() const { return size; }
	// Mutators
	void setHead(Node*);
	void setSize(int s) { size = s; }
	// Overloaded [] operator
	const Node* operator[](int) const;
	// Overloaded << operator
	friend std::ostream& operator<<(std::ostream&, const LinkedList&);
	// Overloaded += operator
	void operator+=(const Node*);
	// Sort function
	void sortList();
};

#endif
