#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct node {
    string aNum;
    string rNum;
    node* next = nullptr;
};

char checkArabicOrRoman(string);
string convertArabicToRoman(string);
string convertRomanToArabic(string);
void createLinkedList(node*&);
void searchLinkedList(node*, string);
void sortLinkedList(node*&, string);
void printLinkedList(node*, ofstream&);

int main() {
    int choice1;
    string choice2;
    node* head = nullptr;
    createLinkedList(head);

    // Displays menu to console until user chooses to exit program
    do {
        cout << "Menu Choices\n\t1. Search\n\t2. Sort\n\t3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice1;

        if (choice1 == 3)
            break;
        else if (choice1 == 1) {
            cout << "Enter number to search: ";
            cin >> choice2;

            searchLinkedList(head, choice2);
        }
        else if (choice1 == 2) {
            cout << "\t1. Sort by Roman numeral\n\t2. Sort by Arabic numeral\n";
            cin >> choice2;
            // sortLinkedList(head, choice2);
        }
    } while (choice1);

    // Prints linked list to file at end of program
    ofstream outfile;
    outfile.open("numbers.txt");
    printLinkedList(head, outfile);

    return 0;
}

char checkArabicOrRoman(string str) {
    int aCount = 0, rCount = 0, invalid = 0;
    for (unsigned i = 0; i < str.length(); i++) {
        if (isdigit(str[i])) {
            if (str[i] != 0)
                aCount++;
            else
                invalid++;
        }
        else if (isalpha(str[i]) || ispunct(str[i])) {
            if (str[i] == 'I' || str[i] == 'V' || str[i] == 'X' || str[i] == 'L' || str[i] == 'C' || str[i] == 'D' || str[i] == 'M')
                rCount++;
            else
                invalid++; // all invalid alphabetical characters and punctuation characters
        }
    }
    if (rCount == 0 && invalid == 0)
        return 'a';
    else if (aCount == 0 && invalid == 0)
        return 'r';
    else
        return '\0';
}

string convertArabicToRoman(string str) {
    int aNum = stoi(str);
    string rNum;

    if (aNum / 1000 != 0) {
        while (aNum / 1000 >= 1) {
            rNum += 'M';
            aNum -= 1000;
        }
    }
    if (aNum / 500 != 0) {
        // special conversion case: 900 converts to CM
        if (aNum >= 900) {
            rNum += "CM";
            aNum -= 900;
        }
        else {
            rNum += 'D';
            aNum -= 500;
        }
    }
    if (aNum / 100 != 0) {
        // special conversion case: 400 converts to CD
        if (aNum >= 400) {
            rNum += "CD";
            aNum -= 400;
        }
        while (aNum / 100 >= 1) {
            rNum += 'C';
            aNum -= 100;
        }
    }
    if (aNum / 50 != 0) {
        // special conversion case: 90 converts to XC
        if (aNum >= 90) {
            rNum += "XC";
            aNum -= 90;
        }
        else {
            rNum += 'L';
            aNum -= 50;
        }
    }
    if (aNum / 10 != 0) {
        // special conversion case: 40 converts to XL
        if (aNum >= 40) {
            rNum += "XL";
            aNum -= 40;
        }
        while (aNum / 10 >= 1) {
            rNum += 'X';
            aNum -= 10;
        }
    }
    if (aNum / 5 != 0) {
        if (aNum >= 9) {
            // special conversion case: 9 converts to IX
            rNum += "IX";
            aNum -= 9;
        }
        else {
            rNum += 'V';
            aNum -= 5;
        }
    }
    if (aNum > 0) {
        if (aNum == 4) {
            // special conversion case: 4 converts to IV
            rNum += "IV";
            aNum -= 4;
        }
        else
            while (aNum-- > 0)
                rNum += 'I';
    }
    // Checks if converted numeral contains '0', invalid character (not in arabic numeral range)
    // if (to_string(aNum).find('0') != string::npos)
    //    return "                     \n";
    return rNum;
}

string convertRomanToArabic(string str) {
    int aNum = 0;
    for (unsigned i = 0; i < str.length(); i++) {
        if (i != str.length() - 1) {
            if (str[i] == 'I') {
                if (str[i + 1] == 'V' || str[i + 1] == 'X') // roman numeral segment is IV or IX
                    aNum--;
                else
                    aNum++;
            }
            else if (str[i] == 'V')
                aNum += 5;
            else if (str[i] == 'X') {
                if (str[i + 1] == 'L' || str[i + 1] == 'C') // roman numeral segment is XL or XC
                    aNum -= 10;
                else
                    aNum += 10;
            }
            else if (str[i] == 'L')
                aNum += 50;
            else if (str[i] == 'C') {
                if (str[i + 1] == 'D' || str[i + 1] == 'M') // roman numeral segment is CD or CM
                    aNum -= 100;
                else
                    aNum += 100;
            }
            else if (str[i] == 'D')
                aNum += 500;
            else if (str[i] == 'M')
                aNum += 1000;
        }
    }
    // Checks if converted numeral contains '0', invalid character (not in arabic numeral range)
    // if (to_string(aNum).find('0') != string::npos)
    //     return "                     \n";
    return to_string(aNum);
}

void createLinkedList(node*& head) {
    ifstream infile;
    string filename, line;
    node* ptr, * temp;

    cout << "Enter filename: ";
    cin >> filename;
    infile.open(filename);

    while (infile.good()) {
        // Takes input without whitespaces
        while (infile >> line) {
            // Only creates linked list node if input not empty
            if (checkArabicOrRoman(line) != '\0') {
                ptr = new node, temp = head;
                // Assigns value of node's Arabic and Roman numerals depending on file input, converts and assigns to corresponding node attribute
                if (checkArabicOrRoman(line) == 'a') {
                    ptr->aNum = line;
                    ptr->rNum = convertArabicToRoman(line);
                }
                else if (checkArabicOrRoman(line) == 'r') {
                    ptr->rNum = line;
                    ptr->aNum = convertRomanToArabic(line);
                }
                ptr->next = head;
                head = ptr;
            }
        }
    }
    infile.close();
}

void searchLinkedList(node* head, string val) {
    node* curr = head;
    cout << val << " ";
    do {
        if (curr->aNum == val || curr->rNum == val) {
            cout << "found\n";
            return; // once value found, returns to main function, disregarding rest of function
        }
        curr = curr->next; // moves onto next value to be compared
    } while (curr != nullptr);

    cout << "not found\n";
}

void sortLinkedList(node*& head, string choice) {
    bool flag = true;
    // curr points to node being compared to, ptr points to node used to compare with previous node
    node* curr = head, * ptr = head, * temp = nullptr;
    if (head == nullptr)
        return;

    // Continues to iterate until list fully sorted
    do {
        flag = false;
        temp = curr->next;
        while (curr->next != nullptr) {
            // Universal sorting algorithm to sort regardless if user chooses sort by Arabic or Roman
            if ((stoi(curr->aNum) > stoi(temp->aNum)) || (stoi(convertRomanToArabic(curr->rNum)) > stoi(convertRomanToArabic(temp->rNum)))) {
                curr->next = temp->next;
                temp->next = curr;
                if (curr == head) {
                    ptr = temp;
                    head = ptr;
                }
                else {
                    ptr->next = temp;
                    ptr = temp;
                }
                flag = true;
            }
            ptr = curr;
            curr = curr->next;
        }
    } while (flag);

    // Reset pointer to front of linked list and displays sorted list to console
    curr = head;
    while (curr != nullptr) {
        if (choice == "1")
            cout << curr->rNum << endl;
        else if (choice == "2")
            cout << curr->aNum << endl;
        curr = curr->next;
    }
}

void printLinkedList(node* curr, ofstream& outfile) {
    if (curr == nullptr)
        return;

    outfile << curr->rNum;
    for (unsigned i = 0; i < 17 - (curr->rNum).length(); i++)
        outfile << " ";
    outfile << curr->aNum;
    for (unsigned j = 0; j < 4 - (curr->aNum).length(); j++)
        outfile << " ";
    outfile << endl;

    // Stops calling once reaches end of linked list (when pointer is null)
    printLinkedList(curr->next, outfile);
}
