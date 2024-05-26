#include "Node.h"
#include <iostream>
#include <cmath>

Node::Node() {
	coef = 0.0;
	exp = 0;
}

Node::Node(double c, int e) {
	coef = c;
	exp = e;
}

std::ostream& operator<<(std::ostream& out, const Node* n) {
	if (n->getCoef() != 0 && n->getExp() != 0) {
		if (fabs(n->getCoef()) != 1)
			out << fabs(n->getCoef());
		out << "x";
		if (n->getExp() != 1)
			out << "^" << n->getExp();
	}
	else if (n->getExp() == 0)
		out << fabs(n->getCoef());
	return out;
}
