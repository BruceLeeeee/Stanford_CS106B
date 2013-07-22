/*
 * File: KarelGoesHome.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Karel Goes Home
 * warmup problem for Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "console.h"
using namespace std;

/* Given a street number and avenue number, which are 1-indexed,
 * returns the number of paths Karel can take back home that only
 * moves left or down.
 */
int numPathsHome(int street, int avenue) {
	if (street == 0 || avenue == 0)
		return 0;
	if (street == 1 && avenue == 1)
		return 1;
	return numPathsHome(street - 1, avenue) + numPathsHome(street, avenue - 1);
}

int main() {
    // [TODO: fill with your code]
	int street, avenue;
	cout << "street = ";
	cin >> street;
	cout << "avenue = ";
	cin >> avenue;
	cout << numPathsHome(street, avenue) << endl;
    return 0;
}
