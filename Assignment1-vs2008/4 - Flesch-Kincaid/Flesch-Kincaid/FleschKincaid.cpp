/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include "console.h"
#include "tokenscanner.h"

using namespace std;

const double C0 = -15.59;
const double C1 = 0.39;
const double C2 = 11.8;

void openFile(ifstream& fin) {
	string filename;

	while (true) {
		cout << "Enter input file name:";
		cin >> filename;
		fin.open(filename.c_str());
		if (fin.fail()) {
			cout << "Cannot open file!";
			fin.clear();
		}
		else break;
	}
}

bool isWord(string& token) {
	if (token[0] >= 'a' && token[0] <= 'z' ||
		token[0] >= 'A' && token[0] <= 'Z')
		return true;
	return false;
}

bool isVowel(char ch) {
	if (ch == 'a' || ch == 'A') return true;
	if (ch == 'e' || ch == 'E') return true;
	if (ch == 'i' || ch == 'I') return true;
	if (ch == 'o' || ch == 'O') return true;
	if (ch == 'u' || ch == 'U') return true;
	if (ch == 'y' || ch == 'Y') return true;
	return false;
}

int countSyllable(string& token) {
	int count = 0;

	for (int i = 0; i < token.length(); i++) {
		if (isVowel(token[i])) {
			if (i != 0 && isVowel(token[i - 1]))
				continue;
			if (i == token.length() - 1 && (token[i] == 'e' || token[i] == 'E'))
				continue;
			count++;
		}
	}
	if (count == 0)
		return 1;
	return count;
}

bool isEndOfSentence(string& token) {
	if (token.length() != 1)
		return false;
	if (token[0] == '.' || token[0] == '!' || token[0] == '?')
		return true;
	return false;
}

double eval(int wordNum, int syllableNum, int sentenceNum) {
	return C0 + C1 * ((double)wordNum / sentenceNum) + C2 * ((double)syllableNum / wordNum);
}
int main() {
    // [TODO: fill in the code]
	ifstream fin;
	TokenScanner scanner;
	int wordCount = 0;
	int syllableCount = 0;
	int sentenceCount = 0;

	openFile(fin);
	scanner.setInput(fin);
	scanner.ignoreWhitespace();
	scanner.addWordCharacters("'");
	while (scanner.hasMoreTokens()) {
		string token = scanner.nextToken();
		//cout << "Token: [" << token << "]" << endl;
		if (isWord(token)) {
			wordCount++;
			syllableCount += countSyllable(token);

		} else if (isEndOfSentence(token)) {
			sentenceCount++;
		}
	}
	if (wordCount == 0)
		wordCount = 1;
	if (sentenceCount == 0)
		sentenceCount = 1;
	cout << "Words: " << wordCount << endl;
	cout << "Syllables: " << syllableCount << endl;
	cout << "Sentences: " << sentenceCount << endl;
	cout << "Grade level: " << eval(wordCount, syllableCount, sentenceCount) << endl;
    return 0;
}
