/*
* Program: ISBN Validation
* Process: Read a list of ISBN values from a file, and determine if the number is valid by calculating the checksum.
* 
*
* Results: Display the list of ISBN values in the terminal and whether or not they are valid, then output all valid numbers only to an output file.
*
* Class: CS2010
* Section: 1006
*
* Term: Fall 2023
* Author: Shane Long
*
* Reflection: I spent many hours putting together this program. It took me a while on step two of the assignment, where we had to create the for loop to iterate over the string.
* Eventually, with a little bit of guidance, I was able to figure it out and the rest of the program went smoothly. There was a lot of trial and error and debugging to make sure
* the program ran correctly. One thing I was unsure about, however, is when I double checked all my work by looking up the ISBN numbers online, I kept getting invalid numbers even
* though the program proved they were valid and I proved them valid by hand. I chalked it up to being that maybe the numbers just simply don't exist yet and were made up for the
* purpose of the assignment, but I still can't help but second guess if I made any mistakes. That being said, I do feel confident in my work.
* 
* Note: The assignment has an error, where step 4 and the output details below step 4 are conflicting. One says that the output on the terminal and the output in the file should be
* exactly the same, whereas the other wants the output file to only include valid entries. This code only includes valid entries in the output file, but to include the invalid entries
* line 121 can be uncommented.
* 
* 
* 
*
*/
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <iomanip>
using namespace std;

int main()
{
 
    // Initialization

    ifstream inFS;  //  input file stream
    ofstream outFS; // output file stream

    string isbn;
    char isbnChar;
    int i;
    int checksum;
    int sum;
    char digit = 0;


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
        return 1; // If the file cannot be opened, exit with return code 1
    }


    outFS << " ISBN" << setw(30) << setfill(' ') << "Is Valid?" << endl;
    outFS << setw(45) << setfill('-') << "" << setfill(' ') << endl;  // prints out a header for the Output file


    inFS >> isbn;

    while (!inFS.fail()) {
        cout << isbn.substr(0, 3) << "-" << isbn.substr(3, 2) << "-" << isbn.substr(5, 2) << "-" << isbn.substr(7, 5) << "-" << isbn.substr(12, 1) << "         ";
        isbnChar = isbn[12];
        isbnChar = isbnChar - '0';
        sum = 0; // sets sum equal to 0 before the for loop runs, so that any previous values are cleared

        for (i = 0; i != isbn.size()-1; ++i) {   // Runs the calculation for each digit of the IBSN, excluding the 13th digit
            digit = isbn[i]; // sets the actual value of the digit at index i
            digit = digit - '0'; // changes to an integer

            if (i % 2 == 0) {
                digit = digit * 1;
                // cout << "DIGIT " << i+1 << ":" << static_cast<int>(c) << endl; // for debugging
            }
            else if (i % 2 == 1) {
                digit = digit * 3;
                // cout << "DIGIT " << i+1 << ":" << static_cast<int>(c) << endl; // for debugging
            }

            sum = sum + digit; // increments sum by the value determined by the above conditional
            
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
            
            // Uncoment the line below to include invalid entries in the output file so that the terminal output and files are exactly the same, see note in header.
            
            // outFS << isbn.substr(0, 3) << "-" << isbn.substr(3, 2) << "-" << isbn.substr(5, 2) << "-" << isbn.substr(7, 5) << "-" << isbn.substr(12, 1) << "            No" << endl;
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
