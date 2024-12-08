#include <iostream>
#include <fstream>
#include <string>
#include <memory>

using namespace std;

// Function prototypes
string checkRowValidity(shared_ptr<char[]>, shared_ptr<char[]>, int);
string checkColumnValidity(shared_ptr<char[]>, shared_ptr<char[]>, int);
char checkSectorValidity(shared_ptr<char[]>, shared_ptr<char[]>, int);
void displayPuzzleValidity(string, shared_ptr<char[]>, shared_ptr<char[]>);

// Driver program involving user input and file input parsing
int main() {
    // Dynamic memory allocation of array using smart pointers
    shared_ptr<char[]> puzzleptr(new char[81]);
    shared_ptr<char[]> nextptr = puzzleptr;
    ifstream infile;
    string filename, puzzleNum, line;

    cout << "Enter filename: ";
    cin >> filename;
    infile.open(filename);
    while (infile.good() && !infile.eof()) {
        // If first line being read is not empty, is puzzle number 
        getline(infile, line);
        if (!line.empty()) {
            puzzleNum = line;
            // For next 9 lines in file, store in array (sudoku puzzle)
            for (int i = 0; i < 9; i++) {
                getline(infile, line);
                for (int j = 0; j < 9; j++) {
                    *(puzzleptr.get() + (i * 9) + j) = line.at(j);
                }
            }
        }
        displayPuzzleValidity(puzzleNum, puzzleptr, nextptr);
    }
    infile.close();
    puzzleptr = nullptr;
    nextptr = nullptr;

    return 0;
}

/*
* Function: checkRowValidity
* Validates whether row in Sudoku puzzle contains duplicates of a number by comparing every element with all subsequent elements in the row
* Parameter:
*   shared_ptr<char[]> curr: points to current value being compared in row
*   shared_ptr<char[]> next: points to next value in row
*   int count: represents row number of Sudoku puzzle
* Returns:
*   string: "v" - valid, meets all rules, contains spaces
*           "s" - solved, valid with no spaces
*           invalid - reason why column violates Sudoku rules
*/

string checkRowValidity(shared_ptr<char[]> curr, shared_ptr<char[]> next, int count) {
    int hasSpace = 0;
    // Comparing 1st 7 elements (0-7) in row with every other element in row; 7th element only has 8th (last) element to compare with
    for (int i = 0 + (9 * count); i < 8 + (9 * count); i++) {
        for (int j = i + 1; j < 9 + (9 * count); j++) {
            // If puzzle element is not a space and is a duplicate, function returns reason invalid
            if (*(curr.get() + i) != ' ' && *(curr.get() + i) == *(next.get() + j))
                return "row " + to_string(count + 1) + " has multiple " + *(curr.get() + i) +"s";
            // Tracks if puzzle has space or not (indicating strictly validity; solved puzzles have no spaces)
            else if (*(curr.get() + i) == ' ')
                hasSpace++;
        }
    }
    // Returns valid if sector contains spaces and no duplicates; otherwise, sector is solved
    if (hasSpace > 0)
        return "v";
    else
        return "s";
}

/*
* Function: checkColumnValidity
* Validates whether column in Sudoku puzzle contains duplicates of a number by comparing every element with all subsequent elements in the column
* Parameter:
*   shared_ptr<char[]> curr: points to current value being compared in column
*   shared_ptr<char[]> next: points to next value in column
*   int count: represents column number of Sudoku puzzle
* Returns:
*   string: "v" - valid, meets all rules, contains spaces
*           "s" - solved, valid with no spaces
*           invalid - reason why column violates Sudoku rules
*/
string checkColumnValidity(shared_ptr<char[]> curr, shared_ptr<char[]> next, int count) {
    int hasSpace = 0;
    // Comparing 1st 7 elements (0-7) in column with every other element in column; 7th element only has 8th (last) element to compare with
    for (int i = count; i < 8 * 9; i += 9) {
        for (int j = i + 9; j < 9 * 9; j += 9) {
            // If puzzle element is not a space and is a duplicate, function returns reason invalid
            if (*(curr.get() + i) != ' ' && *(curr.get() + i) == *(next.get() + j))
                return "column " + to_string(count + 1) + " has multiple " + *(curr.get() + i) + "s";
            // Tracks if puzzle has space or not (indicating strictly validity; solved puzzles have no spaces)
            else if (*(curr.get() + i) == ' ')
                hasSpace++;
        }
    }
    // Returns valid if sector contains spaces and no duplicates; otherwise, sector is solved
    if (hasSpace > 0)
        return "v";
    else
        return "s";
}

/*
* Function: checkSectorValidity
* Validates whether sector in Sudoku puzzle contains duplicates of a number by comparing every element with all subsequent elements in the sector
* Parameter:
*   shared_ptr<char[]> curr: points to current value being compared
*   shared_ptr<char[]> next: points to next value in row
*   int count: represents row number of Sudoku puzzle
* Returns:
*   string: "v" - valid, meets all rules, contains spaces
*         "s" - solved, valid with no spaces
*         invalid - duplicate number, reason why sector violates Sudoku rules
*/
string checkSectorValidity(shared_ptr<char[]> curr, shared_ptr<char[]> next, int count) {
    // Created variables to store offset for curr and next pointers for easier offset notation and to increase program readability
    int hasSpace = 0, offsetI, offsetJ;
    // For upper 3 sectors
    if (count < 3) {
        // Comparing 1st 7 elements (0-7) in sector with every other element in sector; 7th element only has 8th (last) element to compare with
        for (int i = 0; i < 8; i++) {
            // Elements after 3rd sector element require specific arithmetic manipulation to point to correct array index
            if (i > 2) {
                if (i % 3 == 0)
                    offsetI = (i * 3) + (3 * count);
                else
                    // (2 * (i % 3)) serves as offset from left end of subsequent sector.
                    // Offseting negatively from the next sector allows for easier calculation of sector's corresponding puzzle array index
                    offsetI = (i * 3) + (3 * count) - (2 * (i % 3));
            }
            // If in first row of Sudoku puzzle (elements 0-2 of sector), curr position based on sector number
            else
                offsetI = i + (3 * count);
            for (int j = i + 1; j < 9; j++) {
                if (j > 2) {
                    if (j % 3 == 0)
                        offsetJ = (j * 3) + (3 * count);
                    else
                        offsetJ = (j * 3) + (3 * count) - (2 * (j % 3));
                }
                else
                    offsetJ = j + (3 * count);
                // If puzzle element is not a space and is a duplicate, function returns reason invalid
                if (*(curr.get() + offsetI) != ' ' && *(curr.get() + offsetI) == *(next.get() + offsetJ)) {
                    if (count % 3 == 0)
                        return *(curr.get() + offsetI);
                    else if (count == 1)
                        return *(curr.get() + offsetI);
                    else
                        return *(curr.get() + offsetI);
                }
                // Tracks if puzzle has space or not (indicating strictly validity; solved puzzles have no spaces)
                else if (*(curr.get() + offsetI) == ' ')
                    hasSpace++;
            }
        }
    }
    // For middle 3 sectors
    else if (count < 6) {
        for (int i = 0; i < 8; i++) {
            // Elements after 3rd sector element require specific arithmetic manipulation to point to correct array index
            if (i > 2) {
                if (i % 3 == 0)
                    // Add 18 to offset (point pointer to element 2 rows from 3rd element of 1st sector)
                    offsetI = (i * 3) + (3 * count) + (9 * 2);
                else
                    offsetI = (i * 3) + (3 * count) + (9 * 2) - (2 * (i % 3));
            }
            else
                offsetI = i + (3 * count) + (9 * 2);

            for (int j = i + 1; j < 9; j++) {
                if (j > 2) {
                    if (j % 3 == 0)
                        offsetJ = (j * 3) + (3 * count) + (9 * 2);
                    else
                        offsetJ = (j * 3) + (3 * count) + (9 * 2) - (2 * (j % 3));
                }
                else
                    offsetJ = j + (3 * count) + (9 * 2);
                if (*(curr.get() + offsetI) != ' ' && *(curr.get() + offsetI) == *(next.get() + offsetJ)) {
                    if (count % 3 == 0)
                        return *(curr.get() + offsetI);
                    else if (count % 3 == 1)
                        return *(curr.get() + offsetI);
                    else
                        return *(curr.get() + offsetI);
                }
                else if (*(curr.get() + offsetI) == ' ')
                    hasSpace++;
            }
        }
    }
    // For last 3 sectors
    else {
        for (int i = 0; i < 8; i++) {
            if (i > 2) {
                if (i % 3 == 0)
                    // Add 36 to offset (pointing pointer to element 4 rows from 3rd element of 1st sector)
                    offsetI = (i * 3) + (3 * count) + (9 * 4);
                else
                    offsetI = (i * 3) + (3 * count) + (9 * 4) - (2 * (i % 3));
            }
            else
                offsetI = i + (3 * count) + (9 * 4);
            for (int j = i + 1; j < 9; j++) {
                if (j > 2) {
                    if (j % 3 == 0)
                        offsetJ = (j * 3) + (3 * count) + (9 * 4);
                    else
                        offsetJ = (j * 3) + (3 * count) + (9 * 4) - (2 * (j % 3));
                }
                else
                    offsetJ = j + (3 * count) + (9 * 4);
                if (*(curr.get() + offsetI) != ' ' && *(curr.get() + offsetI) == *(next.get() + offsetJ)) {
                    if (count % 3 == 0) {
                        return *(curr.get() + offsetI);
                    }
                    else if (count % 3 == 1)
                        return *(curr.get() + offsetI);
                    else
                        return *(curr.get() + offsetI);
                }
                else if (*(curr.get() + offsetI) == ' ')
                    hasSpace++;
            }
        }
    }
    // Returns valid if sector contains spaces and no duplicates; otherwise, sector is solved
    if (hasSpace > 0)
        return "v";
    else
        return "s";
}

/*
* Function: displayPuzzleValidity
* Displays validity of Sudoku puzzle onto console as validity of individual rows/columsn/sectors is determined by smaller validity functions.
* If puzzle invalid, displays reasons on individual lines. If valid or solved, displays only once.
* Parameter:
*   string pNum: corresponding Sudoku puzzle number
*   char *ptr1: passed as argument into validity functions to be used as pointer to current element in puzzle being compared
*   char *ptr2: passed as argument into validity functions to be used as pointer to subsequent element(s) in puzzle
* Returns:
*   void - displays validity of puzzle onto console
*/
void displayPuzzleValidity(string pNum, shared_ptr<char[]> ptr1, shared_ptr<char[]> ptr2) {
    int invalidCount = 0, solvedCount = 0, num = 0;
    string rowValid, colValid, sectValid;
    // Validity is checked for each of the 9 rows, columns, and sectors (27 total)
    while (num < 9) {
        rowValid = checkRowValidity(ptr1, ptr2, num);
        colValid = checkColumnValidity(ptr1, ptr2, num);
        sectValid = checkSectorValidity(ptr1, ptr2, num);
        // Displays reason for invalidity each time one occurs
        if (rowValid != "v" && rowValid != "s") {
            cout << pNum << "\t" << "invalid" << "\t" << rowValid << endl;
            invalidCount++;
        }
        if (colValid != "v" && colValid != "s") {
            cout << pNum << "\t" << "invalid" << "\t" << colValid << endl;
            invalidCount++;
        }
        if (sectValid != "v" && sectValid != "s") {
            // Experienced continuous output error, resulting in a workaround
            if (num == 0)
                cout << pNum << "\t" << "invalid" << "\t" << "upper left has multiple " << sectValid << "s" << endl;
            else if (num == 1)
                cout << pNum << "\t" << "invalid" << "\t" << "upper middle has multiple " << sectValid << "s" << endl;
            else if (num == 2)
                cout << pNum << "\t" << "invalid" << "\t" << "upper right has multiple " << sectValid << "s" << endl;
            else if (num == 3)
                cout << pNum << "\t" << "invalid" << "\t" << "left has multiple " << sectValid << "s" << endl;
            else if (num == 4)
                cout << pNum << "\t" << "invalid" << "\t" << "middle has multiple " << sectValid << "s" << endl;
            else if (num == 5)
                cout << pNum << "\t" << "invalid" << "\t" << "right has multiple " << sectValid << "s" << endl;
            else if (num == 6)
                cout << pNum << "\t" << "invalid" << "\t" << "lower left has multiple " << sectValid << "s" << endl;
            else if (num == 7)
                cout << pNum << "\t" << "invalid" << "\t" << "lower middle has multiple " << sectValid << "s" << endl;
            else if (num == 8)
                cout << pNum << "\t" << "invalid" << "\t" << "lower right has multiple " << sectValid << "s" << endl;
            invalidCount++;
        }
        // Tracks number of rows/columns/sectors without any spaces; excluded indicates only valid
        if (rowValid == "s")
            solvedCount++;
        if (colValid == "s")
            solvedCount++;
        if (sectValid == "s")
            solvedCount++;
        // If all 9 rows, columns, and sectors are valid and contain no spaces, puzzle is solved; otherwise, valid
        if (num == 8) {
            if (solvedCount == 3 * 9)
                cout << pNum << "\t" << "solved" << endl;
            else if (invalidCount == 0)
                cout << pNum << "\t" << "valid" << endl;
        }
        num++;
    }
}
