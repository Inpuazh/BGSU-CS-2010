#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <iomanip>
using namespace std;

int main()
{

    // Initialization

    ifstream inFS;
    ofstream outFS;

    string isbn;
    char isbnChar;
    int i;
    int checksum;
    int sum;
    char c = 0;


    // Program

    cout << " ISBN" << setw(30) << setfill(' ') << "Is Valid?" << endl;
    cout << setw(45) << setfill('-') << "" << setfill(' ') << endl;  // prints out a header

    inFS.open("ISBNs.csv"); // opens the input file stream
    if (!inFS.is_open()) {
        cout << "-e: could not open file \"ISBNs.csv\"" << endl;
        return 1;  // If the file cannot be opened, exit with return code 1
    }

    outFS.open("ISBN_Out.csv"); // opens the output file stream
    if (!outFS.is_open()) {
        cout << "-e: could not open file \"ISBN_Out.csv\"" << endl;
        return 1; // If the file cannot be opened, do not write to the file
    }

    outFS << " ISBN" << setw(30) << setfill(' ') << "Is Valid?" << endl;
    outFS << setw(45) << setfill('-') << "" << setfill(' ') << endl;  // prints out a header for the Output file

    inFS >> isbn;
    while (!inFS.fail()) {
        cout << isbn.substr(0, 3) << "-" << isbn.substr(3, 2) << "-" << isbn.substr(5, 2) << "-" << isbn.substr(7, 5) << "-" << isbn.substr(12, 1) << "         ";
        isbnChar = isbn[12];
        isbnChar = isbnChar - '0';
        sum = 0; // sets sum equal to 0 before the for loop runs, so that any previous values are cleared

        for (i = 0; i != isbn.size() - 1; ++i) {   // Runs the calculation for each digit of the IBSN, excluding the 13th digit
            c = isbn[i]; // sets the actual value of the digit at index i
            c = c - '0'; // changes to an integer

            if (i % 2 == 0) {
                c = c * 1;
                // cout << "DIGIT " << i+1 << ":" << static_cast<int>(c) << endl; // for debugging
            }
            else if (i % 2 == 1) {
                c = c * 3;
                // cout << "DIGIT " << i+1 << ":" << static_cast<int>(c) << endl; // for debugging
            }

            sum = sum + c; // increments sum by the value determined by the above conditional

        }

        // cout << "sum: " << sum << endl; // for debugging

        sum = sum % 10;
        // cout << "% 10: " << sum << endl; // for debugging
        if (sum == 0) {
            checksum = 0;
            // cout << "chs: " << checksum << endl; // for debugging
        }
        else if (sum != 0) {
            sum = 10 - sum;
            checksum = sum;
            // cout << "chs: " << checksum << endl; // for debugging
        }

        if (checksum == isbnChar) {
            cout << "Yes" << endl;
            outFS << isbn.substr(0, 3) << "-" << isbn.substr(3, 2) << "-" << isbn.substr(5, 2) << "-" << isbn.substr(7, 5) << "-" << isbn.substr(12, 1) << "           Yes" << endl;
        }
        else {
            cout << "No " << endl;
        }

        inFS >> isbn; // inputs the next line in the input file stream and restarts the loop
    }
    if (!inFS.eof()) {
        cout << "-e -inp: Input error before reaching end of file." << endl;
    }

    inFS.close();  // Closes the file stream
    outFS.close(); // Closes the output file stream

    return 0;
}
