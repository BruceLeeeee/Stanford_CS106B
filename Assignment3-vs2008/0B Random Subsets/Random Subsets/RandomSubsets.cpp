/*
 * File: RandomSubsets.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Subsets problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "set.h"
#include "random.h"
#include "console.h"
using namespace std;

/* Given a set of integers, returns a uniformly-random subset of that
 * set.
 */
Set<int> randomSubsetOf(Set<int>& s) {
	if (s.isEmpty())
		return s;
	Set<int> rest = s - s.first();
	Set<int> ans;

	if (randomChance(.5))
		ans += s.first();
	ans += randomSubsetOf(rest);
	return ans;
}

int main() {
    // [TODO: fill with your code]
	Set<int> s;
	s += 1, 2, 3, 4;
	Set<int> sub = randomSubsetOf(s);
	for (Set<int>::iterator itr = sub.begin(); itr != sub.end(); itr++)
		cout << *itr << endl;
    return 0;
}
