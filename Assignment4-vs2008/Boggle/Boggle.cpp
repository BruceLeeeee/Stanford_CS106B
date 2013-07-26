/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include <string>
#include <cctype>
using namespace std;

typedef struct location location;

struct location {
	int x, y;
};

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
void giveInstructions();

/* Main program */

/* Ask the user for the board size and draw blank board
 * return broad size
 */	
int initBoard() {
	cout << "You can choose standard Boggle (4 x 4 grid)" << endl;
	cout << "or Big Boggle (5 x 5)." << endl;
	cout << "Would you like Big Boggle? (Y or N) ";
	char choice;
	cin >> choice;
	cout << endl;
	if (choice == 'Y') {
		drawBoard(5, 5);
		return 5;
	}
	else {
		drawBoard(4, 4);
		return 4;
	}
}

void pickCubeLettersByPlayer(Grid<char> &cubes) {
	cout << "Enter a " << cubes.nRows * cubes.nCols;
	cout << "-character string to identify which letters you want on the cubes." << endl;
	cout << "The first 4 letters are the cubes on the top row from left to right, the next ";
	cout << cubes.nRows << endl;
	cout << "letters are the second row, and so on." << endl;
	cout << "Enter the string: ";
	string str;
	while (true) {
		cin >> str;
		if (str.length() == cubes.nCols * cubes.nRows)
			break;
		else 
			cout << "String must include " << cubes.nRows * cubes.nCols;
			cout << " characters! Try again: ";
	}
	for (int i = 0; i < str.length(); i++)
		cubes[i / cubes.nRows][i % cubes.nCols] = str[i];
}

void copyArray(Vector<string> &cubeStrs, int gridSize) {
	if (gridSize == 4) {
		for (int i = 0; i < 16; i++)
			cubeStrs.push_back(STANDARD_CUBES[i]);
	} else {
		for (int i = 0; i < 25; i++)
			cubeStrs.push_back(BIG_BOGGLE_CUBES[i]);
	}
}

template <typename T>
void swap(T &a, T &b) {
	T tmp = a;
	a = b;
	b = tmp;
}

void shuffleCubes(Vector<string> &cubeStrs) {
	for (int i = 0; i < cubeStrs.size(); i++) {
		int r = randomInteger(i, cubeStrs.size() - 1);
		swap(cubeStrs[i], cubeStrs[r]);
	}
}

/* automatically pick cube letters
 */
void pickCubeLetters(Grid<char> &cubes) {
	Vector<string> cubeStrs;
	int gridSize = cubes.nRows;
	copyArray(cubeStrs, gridSize);
	shuffleCubes(cubeStrs);
	for (int i = 0; i < gridSize * gridSize; i++) {
		int r = randomInteger(0, 5);
		char letter = cubeStrs[i][r];
		cubes[i / gridSize][i % gridSize] = letter;
	}
}

void displayCubeLetters(Grid<char> &cubes) {
	for (int i = 0; i < cubes.nRows; i++)
		for (int j = 0; j < cubes.nCols; j++)
			labelCube(i, j, cubes[i][j]);
}

void setupCubes(Grid<char> &cubes, int gridSize) {
	cubes.resize(gridSize, gridSize);
	cout << "I'll give you a chance to set up the board to you specification, which makes it" << endl;
	cout << " easier to confirm your boggle program is working." << endl;
	cout << "Do you want to force the board configuration? (Y or N)";
	char choice;
	cin >> choice;
	if (choice == 'Y')
		pickCubeLettersByPlayer(cubes);
	else 
		pickCubeLetters(cubes);
	displayCubeLetters(cubes);
}

void setup(Grid<char> &cubes) {
	int gridSize = initBoard();
	setupCubes(cubes, gridSize);
}

bool outOfBound(int x, int y, int gridSize) {
	if (x < 0 || y < 0 || x >= gridSize || y >= gridSize)
		return true;
	return false;
}

/*
 * check whether a word exist starting at (x, y) given the visisted board constraint
 * if exist, the path would be stored in vector path
 */
bool hasWord(int x, int y, string &word, Grid<char> &cubes, bool visisted[5][5], Vector<location> &path) {
	if (word.empty())
		return true;
	if (cubes[x][y] != toupper(word[0]))
		return false;
	visisted[x][y] = true;
	int dir[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}};
	int flag = false;
	for (int i = 0; i < 8; i++) {
		string rest = word.substr(1);
		int xNext = x + dir[i][0];
		int yNext = y + dir[i][1];
		if (outOfBound(xNext, yNext, cubes.nRows))
			continue;
		if (visisted[xNext][yNext])
			continue;
	    visisted[x][y] = true;
		Vector<location> pathTmp;
		flag = hasWord(xNext, yNext, rest, cubes, visisted, pathTmp);
		visisted[x][y] = false;
		if (flag) {
			location loc;
			loc.x = x;
			loc.y = y;
			path.push_back(loc);
			path += pathTmp;
			break;
		}
	}
	
	return flag;
}

void highlightCubes(Vector<location> &path) {
	for (int i = 0; i < path.size(); i++)
		highlightCube(path[i].x, path[i].y, true);
	pause(100);
	for (int i = 0; i < path.size(); i++)
		highlightCube(path[i].x, path[i].y, false);
}

/*
 * check whether a word is on board, if true, highlight the word on board
 */
bool onBoard(string &word, Grid<char> &cubes) {
	bool visisted[5][5];
	Vector<location> path;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			visisted[i][j] = false;
	for (int i = 0; i < cubes.nRows; i++)
		for (int j = 0; j < cubes.nCols; j++)
			if (hasWord(i, j, word, cubes, visisted, path)) {
				highlightCubes(path);
				return true;
			}
	return false;
}

bool isLegal(Lexicon &english, Lexicon &wordFound, Grid<char> &cubes, string &word) {
	if (wordFound.contains(word)) {
		cout << "You've already guessed that!" << endl;
		return false;
	}
	if (!english.contains(word)) {
		cout << "That's not a word!" << endl;
		return false;
	}
	if (word.length() < 4) {
		cout << "I'm sorry, but we have our standards." << endl;
		cout << "That word doesn't meet the minimum word length." << endl;
		return false;
	}
	if (!onBoard(word, cubes)) {
		cout << "You can't make that word!" << endl;
		return false;
	}
	return true;
}

void playerTurn(Lexicon &english, Lexicon &wordFound, Grid<char> &cubes) {
	cout << "Ok, take all the time you want and find all the words you can! Signal that you\'";
	cout << "re finished by entering an empty line." << endl;
	cout << endl;
	string word;
	while (true) {
		cout << "Enter a word: ";
		cin >> word;
		if (word.empty())
			break;
		if (isLegal(english, wordFound, cubes, word)) {
			wordFound.add(word);
			recordWordForPlayer(word, HUMAN);
		}
	}
}

void play(Grid<char> &cubes) {
	Lexicon english("EnglishWords.dat");
	Lexicon wordFound;
	playerTurn(english, wordFound, cubes);
	//computerTurn(english, wordFound, cubes);
}

int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
	Grid<char> cubes;
    initGBoggle(gw);
    welcome();
    giveInstructions();
	setup(cubes);
	play(cubes);
    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

// [TODO: Fill in the rest of the code]
