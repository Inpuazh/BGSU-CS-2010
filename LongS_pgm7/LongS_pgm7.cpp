//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Program: This program is a Snowman game where the player plays
//          against the computer to guess a secret word.
// Process: The computer will select a random word from a provided dictionary.
//          The player will be allowed up to 8 wrong guesses. The game will show
//          the correct guesses in the proper spot in the word. Whenever the player
//          guesses incorrectly, a part of the snowman will be displayed. Once 8
//          turns have been exhausted, the game is lost. If the player guesses
//          the word in 8 turns, the game is won.
//
// Class: CS2010
// Section: 1006
// Term: Fall 2023
// Author: Shane Long
//
// Reflection: This was a challenging assignment. However, I managed to put this together and I think it was a great
// final program to work on this semester. I had a lot of fun working this one out and it put everything I learned this
// semester to the the test. I think it runs completely correctly with what is outlined in the assignment.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cctype>


using namespace std;


const int MAX_WORDS = 100;
const int MAX_WORD_LENGTH = 25;    // Assumptions from documentation
const int MAX_WRONG_GUESSES = 8;

int loadDictionary(string dict[]) {
	
	fstream input;

	input.open("pgm7.txt");
	if (!input.is_open()) {
		cout << "Could not open the file. " << endl;  // if the file could not be found, exit program with code 1
		return 1;
	}

	int count = 0;
	while (count < MAX_WORDS && input >> dict[count]) { // counts the number of words
		count++;
	}

	input.close(); // closes the file
	return count;
}


void drawSnowman(int turn) {  // DRAWING THE ACTUAL SNOWMAN
	if (turn == 1) { // draw a hat
		cout << "     " << static_cast<char>(218) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(191) << endl;
		cout << "    " << static_cast<char>(196) << static_cast<char>(197) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(197) << static_cast<char>(196) << endl;
	}
	else if (turn == 2) { // draw snowman head
		cout << "     " << static_cast<char>(218) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(191) << endl;
		cout << "    " << static_cast<char>(196) << static_cast<char>(197) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(197) << static_cast<char>(196) << endl;
		cout << "     |* *|     " << endl;
		cout << "     | | |     " << endl;
		cout << "    " << static_cast<char>(218) << static_cast<char>(193) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(193) << static_cast<char>(191) << endl;
	}
	else if (turn == 3) { // draw snowman body
		cout << "     " << static_cast<char>(218) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(191) << endl;
		cout << "    " << static_cast<char>(196) << static_cast<char>(197) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(197) << static_cast<char>(196) << endl;
		cout << "     |* *|     " << endl;
		cout << "     | | |     " << endl;
		cout << "    " << static_cast<char>(218) << static_cast<char>(193) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(193) << static_cast<char>(191) << endl;
		cout << "    |     | " << endl;
		cout << "    |  @  | " << endl;
		cout << "    |     | " << endl;
		cout << "   " << static_cast<char>(218) << static_cast<char>(193) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(193) << static_cast<char>(191) << endl;
	}
	else if (turn == 4) { // draw the left arm
		cout << "     " << static_cast<char>(218) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(191) << endl;
		cout << "    " << static_cast<char>(196) << static_cast<char>(197) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(197) << static_cast<char>(196) << endl;
		cout << "     |* *|     " << endl;
		cout << "     | | |     " << endl;
		cout << "    " << static_cast<char>(218) << static_cast<char>(193) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(193) << static_cast<char>(191) << endl;
		cout << "   /|     | " << endl;
		cout << "  / |  @  | " << endl;
		cout << " /  |     | " << endl;
		cout << "   " << static_cast<char>(218) << static_cast<char>(193) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(193) << static_cast<char>(191) << endl;
	}
	else if (turn == 5) { // draw the right arm
		cout << "     " << static_cast<char>(218) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(191) << endl;
		cout << "    " << static_cast<char>(196) << static_cast<char>(197) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(197) << static_cast<char>(196) << endl;
		cout << "     |* *|     " << endl;
		cout << "     | | |     " << endl;
		cout << "    " << static_cast<char>(218) << static_cast<char>(193) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(193) << static_cast<char>(191) << endl;
		cout << "   /|     |\\" << endl;
		cout << "  / |  @  | \\" << endl;
		cout << " /  |     |  \\" << endl;
		cout << "   " << static_cast<char>(218) << static_cast<char>(193) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(193) << static_cast<char>(191) << endl;
	}
	else if (turn == 6) { // draw the snowman bottom
		cout << "     " << static_cast<char>(218) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(191) << endl;
		cout << "    " << static_cast<char>(196) << static_cast<char>(197) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(197) << static_cast<char>(196) << endl;
		cout << "     |* *|     " << endl;
		cout << "     | | |     " << endl;
		cout << "    " << static_cast<char>(218) << static_cast<char>(193) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(193) << static_cast<char>(191) << endl;
		cout << "   /|     |\\" << endl;
		cout << "  / |  @  | \\" << endl;
		cout << " /  |     |  \\" << endl;
		cout << "   " << static_cast<char>(218) << static_cast<char>(193) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(193) << static_cast<char>(191) << endl;
		cout << "   |       |   " << endl;
		cout << "   |   @   |   " << endl;
		cout << "   |       |   " << endl;
		cout << "   " << static_cast<char>(192) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(217) << endl;
	}
	else if (turn == 7) { // draw the left leg
		cout << "     " << static_cast<char>(218) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(191) << endl;
		cout << "    " << static_cast<char>(196) << static_cast<char>(197) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(197) << static_cast<char>(196) << endl;
		cout << "     |* *|     " << endl;
		cout << "     | | |     " << endl;
		cout << "    " << static_cast<char>(218) << static_cast<char>(193) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(193) << static_cast<char>(191) << endl;
		cout << "   /|     |\\" << endl;
		cout << "  / |  @  | \\" << endl;
		cout << " /  |     |  \\" << endl;
		cout << "   " << static_cast<char>(218) << static_cast<char>(193) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(193) << static_cast<char>(191) << endl;
		cout << "   |       |   " << endl;
		cout << "   |   @   |   " << endl;
		cout << "   |       |   " << endl;
		cout << "   " << static_cast<char>(192) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(217) << endl;
		cout << "     " << static_cast<char>(186) << endl;
		cout << "     " << static_cast<char>(188) << endl;
	}
	else if (turn == 8) { // draw the right leg
		cout << "     " << static_cast<char>(218) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(191) << endl;
		cout << "    " << static_cast<char>(196) << static_cast<char>(197) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(197) << static_cast<char>(196) << endl;
		cout << "     |* *|     " << endl;
		cout << "     | | |     " << endl;
		cout << "    " << static_cast<char>(218) << static_cast<char>(193) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(193) << static_cast<char>(191) << endl;
		cout << "   /|     |\\" << endl;
		cout << "  / |  @  | \\" << endl;
		cout << " /  |     |  \\" << endl;
		cout << "   " << static_cast<char>(218) << static_cast<char>(193) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(193) << static_cast<char>(191) << endl;
		cout << "   |       |   " << endl;
		cout << "   |   @   |   " << endl;
		cout << "   |       |   " << endl;
		cout << "   " << static_cast<char>(192) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(217) << endl;
		cout << "     " << static_cast<char>(186) << "   " << static_cast<char>(186) << endl;
		cout << "     " << static_cast<char>(188) << "   " << static_cast<char>(200) << endl;
	}
}


char getGuess() { // Allows the user to enter their guess
	char guess;

	cout << "Enter your guess: ";
	cin >> guess;

	guess = tolower(guess); // Convert any potential capital letters to lower case so that the game is case insensitive
	return guess;

	// FIXME - I've tried several different ways to validate the input so that only 1 character that is a alphabetical character is accepted.
	// No matter what I tried, it kept giving me an error telling me guess is not a char and must be a type.
}

int setSecretWord(char secret[], string dict[], int wordcount) { // randomly picks a word from the dictionary provided
	int randomIndex = rand() % wordcount;
	string randomWord = dict[randomIndex];
	int length = randomWord.length();

	//  Copy the random word to secret array

	for (int i = 0; i < length; i++) {
		secret[i] = randomWord[i];
	}

	return length;
}

void showStatus(char guesses[], int secretlen) {  // shows the current game status
	for (int i = 0; i < secretlen; i++) {
		if (guesses[i] == '_') {
			cout << " _ ";
		}
		else {
			cout << guesses[i] << " ";
		}
	}
	cout << endl;
}

void initGuess(char guesses[], int secretlen) {  // initialize each element of the char array of guessed letters
	for (int i = 0; i < secretlen; i++) {
		guesses[i] = '_';
	}

}

bool recordGuess(char secret[], char guesses[], char letter, int secretlen) { // places the guessed letters in their corresponding spots
	bool correctGuess = false;
	for (int i = 0; i < secretlen; i++) {
		if (secret[i] == letter) {
			guesses[i] = letter;
			correctGuess = true;
		}
	}
	
	return correctGuess;
}

bool isWin(char guesses[], int secretlen) { // determines if the player has won the game

	for (int i = 0; i < secretlen; i++) {
		if (guesses[i] == '_') {
			return false;
		}
	}
	return true;
}


void showSecret(char secret[], int secretlen) { // reveals the secret word
	for (int i = 0; i < secretlen; i++) {
		cout << secret[i];
	}
}

void bubbleSort(string dictionary[], int size) {  // sorts the dictionary so that each word is in alphabetical order.
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (dictionary[j] < dictionary[j + 1]) {
				swap(dictionary[j], dictionary[j + 1]);
			}
		}
	}
}



int main() {

	srand(static_cast<unsigned int>(time(0)));
	string dictionary[MAX_WORDS];
	int numWords = loadDictionary(dictionary);

	// Sorts the dictionary into alphabetical order
	bubbleSort(dictionary, numWords);

	char playAgain;

	do {
		
		// selects a word
		
		char secret[MAX_WORD_LENGTH];
		int secretlen = setSecretWord(secret, dictionary, numWords);

		char guessed[MAX_WORD_LENGTH];
		initGuess(guessed, secretlen);

		int wrongGuesses = 0;
		bool gameWon = false;

		do {
			// Status of current game
			showStatus(guessed, secretlen);

			// Gets a valid guess from the player
			char guess = getGuess();
			cout << endl;

			// Update guessed word and check if the player won
			if (recordGuess(secret, guessed, guess, secretlen)) {
				gameWon = isWin(guessed, secretlen);
			}
			else {
				wrongGuesses++;
				drawSnowman(wrongGuesses);
				cout << endl;
			}

		} while (!gameWon && wrongGuesses < MAX_WRONG_GUESSES);
		

		// Display W/L Status

		showStatus(guessed, secretlen);
		if (gameWon) {
			cout << "-------------------------" << endl;
			cout << "Congratulations! You win!" << endl;
			cout << "-------------------------" << endl;
			cout << endl;
		}
		else {
			cout << "The word was ";
			showSecret(secret, secretlen);
			cout << endl;
			cout << "--------------------" << endl;
			cout << "Game over. You lost." << endl;
			cout << "--------------------" << endl;
			cout << endl;
		}

		cout << "Play again? [Y = play again] ";
		cin >> playAgain;
	} while (playAgain == 'Y' || playAgain == 'y');
	return 0;
}