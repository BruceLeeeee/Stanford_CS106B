/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "lexicon.h"
#include "queue.h"
#include "vector.h"
#include "console.h"
using namespace std;

//return a string vector as the shortest ladder, if found
//return an empty vector, if not found
Vector<string> bfs(string &startingWord, string &endingWord) {
	Lexicon english("EnglishWords.dat");
	Lexicon wordUsed;
	Queue<Vector<string>> queue;
	Vector<string> ladder;

	ladder.push_back(startingWord);
	queue.enqueue(ladder);
	while (!queue.isEmpty()) {
		Vector<string> front = queue.dequeue();
		if (front.get(front.size() - 1) == endingWord)
			return front;
		string current = front.get(front.size() - 1);
		for (int i = 0; i < current.size(); i++)
			for (char j = 'a'; j <= 'z'; j++) 
				if (current[i] != j){
					string next = current;
					next[i] = j;
					if (!english.contains(next))
						continue;
					if (wordUsed.contains(next))
						continue;
					wordUsed.add(next);
					Vector<string> nextLadder = front;
					nextLadder.push_back(next);
					queue.enqueue(nextLadder);
				}
	}

	Vector<string> empty;
	return empty;
}

void printLadder(Vector<string> &ladder) {
	if (ladder.size() == 0) {
		cout << "No word ladder could be found." << endl << endl;
		return;
	}
	cout << "Ladder found: ";
	for (int i = 0; i < ladder.size(); i++)
		if (i != ladder.size() - 1)
			cout << ladder.get(i) << " -> ";
		else 
			cout << ladder.get(i) << endl << endl;
}

int main() {
    // [TODO: fill with your code]
	while (true) {
		string startingWord;
		string endingWord;
		cout << "Enter the starting word (or nothing to quit): ";
		cin >> startingWord;
		if (startingWord.empty())
			break;
		cout << "Enter the ending word: ";
		cin >> endingWord;
		cout << "Searching..." << endl;
		Vector<string> ladder = bfs(startingWord, endingWord);
		printLadder(ladder);
	}
    return 0;
}
