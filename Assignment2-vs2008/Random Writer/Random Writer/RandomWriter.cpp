/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include "console.h"
#include <map>
#include "vector.h"
#include "random.h"
using namespace std;

const int textSize = 2000;

void openFile(ifstream &fin) {
	string filename;
	
	while (true) {
		cout << "Enter the source text: ";
		cin >> filename;
		fin.open(filename.c_str());
		if (fin.is_open())
			break;
		else fin.clear();
	}
}

void analyzeFile(map<string, Vector<char> > &stat) {
	ifstream fin;
	int order;
	char ch;
	string seed;

	openFile(fin);
	cout << "Enter the Markov order [1-10]: ";
	cin >> order;
	cout << "Processing file..." << endl;
	for (int i = 0; i < order; i++) {
		fin.get(ch);
		seed += ch;
	}
	while (fin.get(ch)) {
		if (stat.find(seed) != stat.end())
			stat[seed].push_back(ch);
		else {
			Vector<char> v;
			v.push_back(ch);
			stat[seed] = v;
		}
		seed = seed.substr(1, order - 1) + ch;
	}
}

string getInitSeed(map<string, Vector<char>> &stat) {
	string initSeed;
	int max = 0;

	map<string, Vector<char>>::iterator itr = stat.begin();
	while (itr != stat.end()) {
		if (itr->second.size() > max) {
			max = itr->second.size();
			initSeed = itr->first;
		}
		itr++;
	}
	return initSeed;
}

void randomWrite(map<string, Vector<char>> &stat) {
	string seed = getInitSeed(stat);
	char ch;
	int order = seed.length();

	for (int i = 0; i < textSize; i++) {
		if (stat.find(seed) == stat.end())
			break;
		Vector<char> v = stat[seed];
		int index = randomInteger(0, v.size() - 1);
		ch = v.get(index);
		cout << ch;
		seed = seed.substr(1, order - 1) + ch;
	}
}

int main() {
    // [TODO: fill with your code]
	map<string, Vector<char>> stat;
	analyzeFile(stat);
	randomWrite(stat);
    return 0;
}
