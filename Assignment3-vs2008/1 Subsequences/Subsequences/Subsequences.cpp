/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence) {
	if (subsequence.empty())
		return true;
	for (int i = 0; i < text.size(); i++) {
		if (text[i] == subsequence[0] && isSubsequence(text.substr(i), subsequence.substr(1)))
			return true;
	}
	
	return false;
}

int main() {
    // [TODO: fill with your code]
	string text;
	string subsequence;

	cout << "text = ";
	cin >> text;
	cout << "subsequence = ";
	cin >> subsequence;
	cout << isSubsequence(text, subsequence) << endl;
    return 0;
}
