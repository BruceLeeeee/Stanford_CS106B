/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include "console.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);

/* Main program */

int main() {
    // [TODO: fill in the code]
	cout << intToString(-34324) << endl;
	cout << intToString(49232323) << endl;
	cout << intToString(0) << endl;
	cout << stringToInt("39942343") << endl;
    return 0;
}

string intToString(int n) {
	if (n / 10 == 0) {
		char ch = abs(n) + '0';
		if (n < 0)
			return string() + '-' + ch;
		else 
			return string() + ch;
	} else {
		char ch = abs(n) % 10 + '0';
		return intToString(n / 10) + ch;
	}
}

int stringToInt(string str) {
	if (str.length() == 1) 
		return str[0] - '0';
	else if (str.length() == 2) {
		if (str[0] == '-')
			return -1 *  stringToInt(string() + str[1]);
		else 
			return str[1] - '0' + (str[0] - '0') * 10;
	} else {
		if (str[0] != '-')
			return stringToInt(str.substr(0, str.length() - 1)) * 10 + (str[str.length() - 1] - '0');
		else 
			return stringToInt(str.substr(0, str.length() - 1)) * 10 - (str[str.length() - 1] - '0');
	}
}