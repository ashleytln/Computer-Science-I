#include "LinkedList.cpp"
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
				// If term is not last term
				//if ((line.find(' ', i) != std::string::npos) && (line.find(' ', i) <= (i + 9))) {
				//}
				// Term contains coefficient other than 1
				if ((line.find('x', i) != std::string::npos) && (line.find('x', i) <= (i + 4))) {
					for (; i < line.find('x', i); i++) {
						coef += line[i];
					}
				}
				// Term contains exponent other than 0
				if ((line.find('^', i) != std::string::npos) && (line.find('^', i) <= (i + 1))) {
					i = line.find('^', i) + 1;
					if (line.find(' ', i) != std::string::npos) {
						for (; i < line.find(' ', i); i++) {
							exp += line[i];
						}
					}
					else {
						for (; i < line.length(); i++) {
							exp += line[i];
						}
					}
				}
				// Term contains zero exponent
				if (line.find('^', i) == std::string::npos) {
					for (; i < line.length(); i++) {
						coef += line[i];
					}
				}
				if (coef == "")
					coef = "1";
				if (exp == "")
					exp = "0";
				term = new Node(stod(coef), stoi(exp));
				term->setNext(nullptr);
				expression += term;
				coef = "", exp = "";
				if ((i + 1) <= (line.length() - 1)) {
					i++;
					if (line[i] == '-')
						coef += line[i];
					i += 2;
				}
				if (i >= line.length())
					break;
			}
			expression.sortList();
			double val = calculateExpression(stod(input), expression.getHead());
			cout << setprecision(3) << fixed;
			cout << expression << " = " << val << endl;
		}
	}
}
