/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "random.h"

using namespace std;

int main() {
	int conHeadCount = 0;
	int flipCount = 0;

	while (true) {
		if (randomChance(0.5)) {
			conHeadCount++;
			cout << "heads" << endl;
		} else {
			conHeadCount = 0;
			cout << "tails" << endl;
		}
		if (conHeadCount == 3)
			break;
		flipCount++;
	}
	cout << "It took " << flipCount << " to get 3 consecutive heads." << endl;
    // [TODO: fill in the code]
    return 0;
}
