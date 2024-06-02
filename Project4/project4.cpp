#include "LinkedList.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

double calculateExpression(double input, Node* head) {
	Node* ptr = head;
	double val = 0;
	while (ptr != nullptr) {
		val += ptr->getCoef() * pow(input, ptr->getExp());
		ptr = ptr->getNext();
	}
	return val;
}

int main() {
	ifstream infile;
	string filename, line, input, coef, exp;
    double val;
    
	Node* term = nullptr;
	unsigned i = 0;

	cout << "Enter filename: ";
	cin >> filename;

	infile.open(filename);
	if (infile.good()) {
		while (getline(infile, line)) {
			LinkedList expression;
			input = "", coef = "", exp = "";
			// Store value inside parentheses for later calculation
			for (i = 2; i < line.find(')'); i++)
				input += line[i];
			// Traverse to expression
			i += 4;
			while (i < line.length()) {
				// Term contains coefficient other than 1
				if ((line.find('x', i) != std::string::npos) && (line.find('x', i) <= (i + 4))) {
					for (; i < line.find('x', i); i++) {
						coef += line[i];
					}
				}
				// Term contains exponent other than 0 or 1
				if ((line.find('^', i) != std::string::npos) && (line.find('^', i) <= (i + 1))) {
					i = static_cast<int>(line.find('^', i)) + 1;
					// Term is not at end of expression
					if (line.find(' ', i) != std::string::npos) {
						for (; i < line.find(' ', i); i++) {
							exp += line[i];
						}
					}
					// Term is at end of expression (anything after '^' is exponent)
					else {
						for (; i < line.length(); i++) {
							exp += line[i];
						}
					}
				}
				// Term is a constant (non-zero coefficient, zero exponent)
				else if (line.find('^', i) == std::string::npos && line.find('x', i) == std::string::npos) {
					for (; i < line.length(); i++) {
						coef += line[i];
					}
					exp = "0";
				}
				// Term coefficient is empty
				if (coef == "")
				    coef += "1";
				// Term exponent is empty
				if (exp == "")
				    exp += "1";
				// Create term node to add to expression linked list
				term = new Node(stod(coef), stoi(exp));
				term->setNext(nullptr);
				// Add node term to expression linked list
				expression += term;
				// Reset coefficient and exponent variables
				coef = "", exp = "";
				// If current index not past end of line
				if (i <= (line.length() - 1)) {
					i++;
					// If index past end of line, stop reading
					if (i >= line.length())
					    break;
					// If current element is '-', make coefficient negative 
					if (line[i] == '-')
						coef += "-";
					// Traverse to next term in expression
					i += 2;
				}
			}
			// Sort expression linked list based on exponent (standard form)
			expression.sortList();
			val = calculateExpression(stod(input), expression.getHead());
			cout << setprecision(3) << fixed;
			cout << expression << " = " << val << endl;
		}
	}
}
