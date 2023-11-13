/*
* Program: Grade Analyzer
* 
* Process: Analyze a class's scores over three different chapters and compute various values.
* Input: records.txt file that contains 3 scores, one for each chapter.
* Results: Return a formatted output of the scores, the scores as percentages and the letter grade, along with the average grade, highest grade, lowest grade, and ABC rate of the class.
*
* Class: CS2010
* Section: 1006
*
* Term: Fall 2023
* Author: Shane Long
*
* Reflection: IThis program went well. There were no major issues I ran into while working on this program, other than one minor issue. One issue I ran into was during the input loop.
* I ended up using two loops which cause the input to get messed up, however I couldn't figure out why for a while until someone pointed it out to me. After that, everything
* was extremely straight forward. The out put looks basically exactly the same as the smaple output in the assignment, so I think this works out well.
*
*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

void readRosterAndComputeTotal(double ch1[], double ch2[], double ch3[], double totalGrades[], int SIZE_CLASS) { // Step 3 - read data from input, store grade for each student for each chapter, and compute the total and store that total in another array.

    ifstream inFS; // initializes the file stream

    inFS.open("roster.txt"); // opens the file
    if (inFS.is_open()) {  // if the file is open, runs the rest of the function

        for (int i = 0; i < SIZE_CLASS; ++i) {

            inFS >> ch1[i] >> ch2[i] >> ch3[i];  // Reads and inputs all numbers from the file into each array

            // cout << ch1[i] << " " << ch2[i] << " " << ch3[i] << endl;            // for debugging
        }
        for (int i = 0; i < SIZE_CLASS; ++i) {

            totalGrades[i] = (ch1[i] + ch2[i] + ch3[i]); // Sums each amount of points scored and adds that value to the current array index

        }

    }
    else { // If the file could not be opened
        cout << "-e: could not open file." << endl;

    }

    inFS.close(); // closes the file

}

void printRoster(double ch1[], double ch2[], double ch3[], double totalGrades[], int SIZE_CLASS) { // Step 4 - display all the data stored in the four arrays as well the student number.

    // Print out a header
    cout << "The original roster:" << endl;
    cout << "Student #" << setw(10) << setfill(' ') << "Ch01" << setw(10) << setfill(' ') << "Ch02" << setw(10) << setfill(' ') << "Ch03"
        << setw(11) << setfill(' ') << "Total" << endl;
    cout << setw(80) << setfill('-') << "" << setfill(' ') << endl;

    // Prints out each score for each student
    for (int i = 0; i < SIZE_CLASS; ++i) {
        
        // Student #'s 1-9 formatted as 01-09 to align the output
        cout << setw(2) << setfill('0') << fixed << i + 1 << setw(18) << setfill(' ') << right << setprecision(2) << ch1[i] << setw(10) << setfill(' ') << ch2[i] << setw(10) << setfill(' ') << ch3[i]
            << setw(10) << setfill(' ') << totalGrades[i] << endl;
       
    }

}

void convertToPercentage(double ch1[], double ch2[], double ch3[], double totalGrades[], int SIZE_CLASS) { // Step 6 - convert all grades to percentage.

    for (int i = 0; i < SIZE_CLASS; ++i) {
        ch1[i] = (ch1[i] / 15) * 100;  
        ch2[i] = (ch2[i] / 15) * 100;  // Divides full scores by actual scores, then multiplies by 100 to turn to percentage 
        ch3[i] = (ch3[i] / 20) * 100;

        totalGrades[i] = (totalGrades[i] / 50) * 100;
    }

}

void printConvertedRosterWithLetterGrade(double ch1[], double ch2[], double ch3[], double totalGrades[], int SIZE_CLASS) { // Step 7 - display the converted grades in percentage, as well as the letter grade

    char letterGrade;

    // prints out a header
    cout << "The converted roster with letter grade:" << endl;
    cout << "Student #" << setw(11) << setfill(' ') << "Ch01" << setw(13) << setfill(' ') << "Ch02" << setw(13) << setfill(' ') << "Ch03"
        << setw(13) << setfill(' ') << "Total" << setw(18) << setfill(' ') << "Letter Grade" << endl;
    cout << setw(80) << setfill('-') << "" << setfill(' ') << endl;

    
    for (int i = 0; i < SIZE_CLASS; ++i) {

        // Logic for determining letter grade
        if (totalGrades[i] >= 92) {
            letterGrade = 'A';
        }
        else if (totalGrades[i] >= 82) {
            letterGrade = 'B';
        }
        else if (totalGrades[i] >= 72) {
            letterGrade = 'C';
        }
        else if (totalGrades[i] >= 62) {
            letterGrade = 'D';
        }
        else {
            letterGrade = 'F';
        }

        // Output
        cout << setw(2) << setfill('0') << fixed << i + 1 << setw(19) << setfill(' ') << right << setprecision(2) << ch1[i] << " % " << setw(10) << setfill(' ') << ch2[i] << " % " << setw(10)
            << setfill(' ') << ch3[i] << " % " << setw(10) << setfill(' ') << totalGrades[i] << " % " << setw(3) << setfill(' ') << letterGrade << endl;

    }

}

double computeAvgGrade(double totalGrades[], int SIZE_CLASS) { // Step 9  - compute and return the average total score.

    double avgGrade = 0;

    for (int i = 0; i < SIZE_CLASS; ++i) {

        avgGrade = avgGrade + totalGrades[i]; // adds up all grades

    }

    return (avgGrade / SIZE_CLASS); // returns average

}

double findHighestScore(double totalGrades[], int SIZE_CLASS) { // Step 10  - find and return the highest total score.

    double highestScore = 0;

    for (int i = 0; i < SIZE_CLASS; ++i) {

        if (totalGrades[i] > highestScore) { // If the score is higher than the highest score, set that score as the highest
            highestScore = totalGrades[i];
        }
    }

    return highestScore;

}

double findLowestScore(double totalGrades[], int SIZE_CLASS) { // Step 11 - find and return the lowest total score.

    double lowestScore = 1000;

    for (int i = 0; i < SIZE_CLASS; ++i) {

        if (totalGrades[i] < lowestScore) { // If the score is lower than the lowest score, set that score as the lowest
            lowestScore = totalGrades[i];
        }

    }

    return lowestScore;
}

double computeABCRate(double totalGrades[], int SIZE_CLASS) { // Step 12 - compute and return the ABC rate of the class

    double abcRate = 0;

    for (int i = 0; i < SIZE_CLASS; ++i) {

        if (totalGrades[i] >= 72) { // If the score is 72 or higher, add one to abcRate

            ++abcRate;

        }

    }

    return (abcRate / SIZE_CLASS) * 100; // Returns abcRate / class size

}



int main() {  // MAIN FUNCTION
    
    const int SIZE_CLASS = 21;

    // step 1 - Declare three arrays to hold the grades of chapter 01, chapter 02, and chapter 03
    double ch1[SIZE_CLASS];
    double ch2[SIZE_CLASS];
    double ch3[SIZE_CLASS];

    //step 2 - Declare a new array to hold the total of the grades of chapter 01, 02, and 03 for each student
    double totalGrades[SIZE_CLASS];


    // step 3 - read data from input, store grade for each student for each chapter, and compute the total and store that total in another array.
    readRosterAndComputeTotal(ch1, ch2, ch3, totalGrades, SIZE_CLASS);

    
    // step 4 - display all the data stored in the four arrays as well the student number.
    printRoster(ch1, ch2, ch3, totalGrades, SIZE_CLASS);


    // step 5 - Print a line of “*” followed by an empty line.
    cout << setw(80) << setfill('*') << "" << setfill(' ') << endl << endl;


    // step 6 - convert all grades to percentage.
    convertToPercentage(ch1, ch2, ch3, totalGrades, SIZE_CLASS);


    // step 7 - display the converted grades in percentage, as well as the letter grade
    printConvertedRosterWithLetterGrade(ch1, ch2, ch3, totalGrades, SIZE_CLASS);


    // step 8 - Print a line of “*” followed by an empty line.
    cout << setw(80) << setfill('*') << "" << setfill(' ') << endl << endl;


    // step 9 - compute and return the average total score.
    cout << "The average total score of the class is: " << computeAvgGrade(totalGrades, SIZE_CLASS) << "%" << endl; // computes the average score for the class


    // step 10 - find and return the highest total score.
    cout << "The highest score is: " << findHighestScore(totalGrades, SIZE_CLASS) << "%" << endl;


    // step 11 - find and return the lowest total score.
    cout << "The lowest score is: " << findLowestScore(totalGrades, SIZE_CLASS) << "%" << endl;

    
    //step 12 - compute and return the ABC rate of the class
    cout << "The ABC rate of the class is: " << computeABCRate(totalGrades, SIZE_CLASS) << "%" << endl;

    return 0;
}

