#ifndef NODE_H
#define NODE_H

#include <iostream>

class Node {
private:
	double coef;
	int exp;
	Node* next = nullptr;
public:
	// Default constructor
	Node();
	// Overloaded constructor
	Node(double, int);
	// Accessors
	double getCoef() const { return coef; }
	int getExp() const { return exp; }
	Node* getNext() const { return next; }
	// Mutators 
	void setCoef(double c) { coef = c; }
	void setExp(int e) { exp = e; }
	void setNext(Node* n) { next = n; }
	// Overloaded << operator
	friend std::ostream& operator<<(std::ostream&, const Node*);
};

#endif
