#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string checkRowValidity(char*, char*, char*, int);
string checkColumnValidity(char*, char*, char*, int);
char checkSectorValidity(char*, char*, char*, int);
void displayPuzzleValidity(string, char*, char*, char*);

int main()
{
    // Dynamic memory allocation of array
    char* puzzle = new char[81];
    // Storing address of puzzle's first element, used to reset puzzle pointer after storing puzzle values in array
    char* ptr1 = puzzle, * ptr2 = nullptr;
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
                    *puzzle = line.at(j);
                    puzzle++;
                }
            }
        }
        // Resetting puzzle to point to beginning of array (where ptr1 is pointing to)
        puzzle = ptr1;
        displayPuzzleValidity(puzzleNum, puzzle, ptr1, ptr2);
    }
    infile.close();
    delete[] puzzle;
    puzzle = nullptr;

    return 0;
}

/*
* Function: checkRowValidity
* Validates whether row in Sudoku puzzle contains duplicates of a number by comparing every element with all subsequent elements in the row
* Parameter:
*   char *arr: pointer storing Sudoku puzzle
*   char *curr: points to current value being compared
*   char *next: points to next value in row
*   int count: represents row number of Sudoku puzzle
* Returns:
*   string: "v" - valid, meets all rules, contains spaces
*           "s" - solved, valid with no spaces
*           invalid - reason why column violates Sudoku rules
*/

string checkRowValidity(char* arr, char* curr, char* next, int count) {
    int hasSpace = 0;
    // Comparing 1st 7 elements (0-7) in row with every other element in row; 7th element only has 8th (last) element to compare with
    for (int i = 0 + (9 * count); i < 8 + (9 * count); i++) {
        curr = arr + i;
        for (int j = i + 1; j < 9 + (9 * count); j++) {
            next = arr + j;
            // If puzzle element is not a space and is a duplicate, function returns reason invalid
            if (*curr != ' ' && *curr == *next)
                return "row " + to_string(count + 1) + " has multiple " + *curr + "s";
            // Tracks if puzzle has space or not (indicating strictly validity; solved puzzles have no spaces)
            else if (*curr == ' ')
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
*   char *arr: pointer storing Sudoku puzzle
*   char *curr: points to current value being compared
*   char *next: points to next value in column
*   int count: represents column number of Sudoku puzzle
* Returns:
*   string: "v" - valid, meets all rules, contains spaces
*           "s" - solved, valid with no spaces
*           invalid - reason why column violates Sudoku rules
*/
string checkColumnValidity(char* arr, char* curr, char* next, int count) {
    int hasSpace = 0;
    // Comparing 1st 7 elements (0-7) in column with every other element in column; 7th element only has 8th (last) element to compare with
    for (int i = count; i < 8 * 9; i += 9) {
        curr = arr + i;
        for (int j = i + 9; j < 9 * 9; j += 9) {
            next = arr + j;
            // If puzzle element is not a space and is a duplicate, function returns reason invalid
            if (*curr != ' ' && *curr == *next)
                return "column " + to_string(count + 1) + " has multiple " + *curr + "s";
            // Tracks if puzzle has space or not (indicating strictly validity; solved puzzles have no spaces)
            else if (*curr == ' ')
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
*   char *arr: pointer storing Sudoku puzzle
*   char *curr: points to current value being compared
*   char *next: points to next value in column
*   int count: represents column number of Sudoku puzzle
* Returns:
*   char: "v" - valid, meets all rules, contains spaces
*         "s" - solved, valid with no spaces
*         invalid - duplicate number, reason why sector violates Sudoku rules
*/
char checkSectorValidity(char* arr, char* curr, char* next, int count) {
    int hasSpace = 0;
    // For upper 3 sectors
    if (count < 3) {
        // Comparing 1st 7 elements (0-7) in sector with every other element in sector; 7th element only has 8th (last) element to compare with
        for (int i = 0; i < 8; i++) {
            // Elements after 3rd sector element require specific arithmetic manipulation to point to correct array index
            if (i > 2) {
                if (i % 3 == 0)
                    curr = arr + (i * 3) + (3 * count);
                else
                    // (2 * (i % 3)) serves as offset from left end of subsequent sector.
                    // Offseting negatively from the next sector allows for easier calculation of sector's corresponding puzzle array index
                    curr = arr + (i * 3) + (3 * count) - (2 * (i % 3));
            }
            // If in first row of Sudoku puzzle (elements 0-2 of sector), curr position based on sector number
            else
                curr = arr + i + (3 * count);
            for (int j = i + 1; j < 9; j++) {
                if (j > 2) {
                    if (j % 3 == 0)
                        next = arr + (j * 3) + (3 * count);
                    else
                        next = arr + (j * 3) + (3 * count) - (2 * (j % 3));
                }
                else
                    next = arr + j + (3 * count);
                // If puzzle element is not a space and is a duplicate, function returns reason invalid
                if (*curr != ' ' && *curr == *next) {
                    if (count % 3 == 0)
                        return *curr;
                    else if (count == 1)
                        return *curr;
                    else
                        return *curr;
                }
                // Tracks if puzzle has space or not (indicating strictly validity; solved puzzles have no spaces)
                else if (*curr == ' ')
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
                    curr = arr + (i * 3) + (3 * count) + (9 * 2);
                else
                    curr = arr + (i * 3) + (3 * count) + (9 * 2) - (2 * (i % 3));
            }
            else
                curr = arr + i + (3 * count) + (9 * 2);

            for (int j = i + 1; j < 9; j++) {
                if (j > 2) {
                    if (j % 3 == 0)
                        next = arr + (j * 3) + (3 * count) + (9 * 2);
                    else
                        next = arr + (j * 3) + (3 * count) + (9 * 2) - (2 * (j % 3));
                }
                else
                    next = arr + j + (3 * count) + (9 * 2);
                if (*curr != ' ' && *curr == *next) {
                    if (count % 3 == 0)
                        return *curr;
                    else if (count % 3 == 1)
                        return *curr;
                    else
                        return *curr;
                }
                else if (*curr == ' ')
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
                    curr = arr + (i * 3) + (3 * count) + (9 * 4);
                else
                    curr = arr + (i * 3) + (3 * count) + (9 * 4) - (2 * (i % 3));
            }
            else
                curr = arr + i + (3 * count) + (9 * 4);
            for (int j = i + 1; j < 9; j++) {
                if (j > 2) {
                    if (j % 3 == 0)
                        next = arr + (j * 3) + (3 * count) + (9 * 4);
                    else
                        next = arr + (j * 3) + (3 * count) + (9 * 4) - (2 * (j % 3));
                }
                else
                    next = arr + j + (3 * count) + (9 * 4);
                if (*curr != ' ' && *curr == *next) {
                    if (count % 3 == 0) {
                        return *curr;
                    }
                    else if (count % 3 == 1)
                        return *curr;
                    else
                        return *curr;
                }
                else if (*curr == ' ')
                    hasSpace++;
            }
        }
    }
    // Returns valid if sector contains spaces and no duplicates; otherwise, sector is solved
    if (hasSpace > 0)
        return 'v';
    else
        return 's';
}

/*
* Function: displayPuzzleValidity
* Displays validity of Sudoku puzzle onto console as validity of individual rows/columsn/sectors is determined by smaller validity functions.
* If puzzle invalid (contains duplicate numbers, with or without spaces), displays reasons on individual lines.
* Otherwise, displays puzzle as valid (containing spaces) or solved (valid with no spaces).
* Parameter:
*   string pNum: corresponding Sudoku puzzle number
*   char *arr: pointer storing Sudoku puzzle
*   char *ptr1: passed as argument into validity functions to be used as pointer to current element in puzzle being compared
*   char *ptr2: passed as argument into validity functions to be used as pointer to subsequent element(s) in puzzle
* Returns:
*   void - displays validity of puzzle onto console
*/
void displayPuzzleValidity(string pNum, char* arr, char* ptr1, char* ptr2) {
    int invalidCount = 0, solvedCount = 0, num = 0;
    string rowValid, colValid, sectValid;
    // Validity is checked for each of the 9 rows, columns, and sectors (27 total)
    while (num < 9) {
        rowValid = checkRowValidity(arr, ptr1, ptr2, num);
        colValid = checkColumnValidity(arr, ptr1, ptr2, num);
        sectValid = checkSectorValidity(arr, ptr1, ptr2, num);
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
            // Displays reason invalid based on sector number containing duplicate (0 is upper left, 3 is left, etc)
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
