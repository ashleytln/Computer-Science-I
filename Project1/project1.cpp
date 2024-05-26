// Name: Ashley Nguyen
// NetID: atn210009

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int ARABIC_CHAR_FIELD = 4, ROMAN_CHAR_FIELD = 17;
const string database = "numbers.txt";
//your filestream for the database will connect to this variable

/*
* Function: checkArabicOrRoman
* Initial character validity check, determines what type of numeral what line of input in file contains
* Parameter:
*   string str: comes from line of input from ifstream object (infile)
* Returns:
*   char: 'a' - line contains arabic numeral, 'r' - line contains roman numeral, '\0' - line contains invalid character
*/
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

/*
* Function: convertArabicToRoman
* Converts arabic numeral to roman numeral.
* Divides and subtracts arabic values from variable aNum (stores value of parameter str converted to integer value)
* Adds corresponding roman numeral value as character/string to variable rNum
* Parameter:
*   string str: comes from line of input from ifstream object (infile)
* Returns:
*   string rNum - string containing roman numeral conversion
*/
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
    if (to_string(aNum).find('0') != string::npos)
        return "                     \n";
    else
        return rNum;
}

/*
* Function: convertRomanToArabic
* Converts roman numeral to arabic numeral.
* Checks if string parameter contains roman numeral character
* Adds/subtracts corresponding arabic numeral value to variable aNum
* Parameter:
*   string str: comes from line of input from ifstream object (infile)
* Returns:
*   string aNum - string containing arabic numeral conversion (if contains valid characters)
*       - involves extra characters for file formatting purposes
*/
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
    if (to_string(aNum).find('0') != string::npos)
        return "                     \n";
    else
        return str.substr(0, str.length() - ARABIC_CHAR_FIELD) + to_string(aNum);
}

int main() {
    /* ################  DO NOT MODIFY CODE IN THIS BLOCK ###################### */
    string temp;  //variable for database filename
    string batch; //variable for batch filename

    cout << "Enter File Name: ";
    cin >> temp;

    ifstream infile(temp, ios::binary);
    ofstream outfile(database, ios::binary);
    string line;
    if (infile)
        while (infile.good())
        {
            getline(infile, line);
            if (line != "")
                outfile << line << "\n";
        }

    infile.close();
    outfile.close();
    /* ################  DO NOT MODIFY CODE IN THIS BLOCK ###################### */
    long inputChars = 0;

    infile.open(temp, ios::binary);
    if (infile.good()) {
        while (getline(infile, line)) {
            /* Since infile differs from outfile by a single newline character at the end of the file,
               this was a working solution which prevents infile.tellg() from returning -1. */
            if (infile.eof())
                inputChars = inputChars + line.length() + 1;
            else
                inputChars = infile.tellg();
            infile.close();
            
            outfile.open(database, ios::in | ios::ate | ios::binary); // ios::in flag applied to prevent outfile from being truncated
            outfile.seekp(inputChars - ROMAN_CHAR_FIELD - ARABIC_CHAR_FIELD - 1, ios::beg);
            
            // If line of input contains arabic numeral, displays the converted roman numeral (if contains valid characters) to outfile
            if (checkArabicOrRoman(line) == 'a') {
                outfile << convertArabicToRoman(line);
            }
            // If line of input contains roman numeral, displays the converted arabic numeral (if contains valid characters) to outfile
            else if (checkArabicOrRoman(line) == 'r') {
                outfile << convertRomanToArabic(line);
            }
            // If line of input contains invalid characters via initial character check, clears individual line in outfile
            else
                outfile << "                     \n";
            outfile.close();

            infile.open(temp, ios::binary);
            infile.seekg(inputChars, ios::beg);
        }
        infile.close();
    }
    return 0;
}
