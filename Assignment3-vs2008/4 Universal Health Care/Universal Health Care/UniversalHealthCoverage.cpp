/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

bool coveredAll(Set<string>& cities,
				Vector< Set<string> >& result) {
	Set<string> coveredCities;
	for (int i = 0; i < result.size(); i++)
		coveredCities += result[i];
	if (cities == coveredCities)
		return true;
	return false;
}

bool recCheck(Set<string>& cities,
			  int p,
			  Vector< Set<string> >& locations,
			  int numHospitals,
			  Vector< Set<string> >& result) {
	if (coveredAll(cities, result))
		return true;
	if (numHospitals <= 0 || p >= locations.size())
		return false;
	
	Set<string> hospital = locations[p];
	//Vector<Set<string>> rest(locations.begin() + p, locations.end());
	result.push_back(hospital);
	if (recCheck(cities, p + 1, locations, numHospitals - 1, result))
		return true;
	result.remove(result.size() - 1);
	if (recCheck(cities, p + 1, locations, numHospitals, result))
		return true;

	return false;
}

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
							   Vector< Set<string> >& result) {
	if (recCheck(cities, 0, locations, numHospitals, result))
		return true;
	else 
		return false;
}

void output(Vector<Set<string>>& result) {
	for (int i = 0; i < result.size(); i++) {
		Set<string>::iterator itr = result[i].begin();
		cout << "{\"" << *itr << "\"";
		itr++;
		for (; itr != result[i].end(); itr++)
			cout << ", " << "\"" << *itr << "\"";
		cout << "}" << endl;
	}
}

int main() {
    /* TODO: Add testing code here! */
	Set<string> cities;
	cities += "A", "B", "C", "D", "E", "F";
	Vector<Set<string>> locations;
	Vector< Set<string> > result;

	Set<string> hospital0;
	hospital0 += "A", "B", "C";
	locations.push_back(hospital0);
	Set<string> hospital1;
	hospital1 += "A", "C", "D";
	locations.push_back(hospital1);
	Set<string> hospital2;
	hospital2 += "B", "F";
	locations.push_back(hospital2);
	Set<string> hospital3;
	hospital3 += "C", "E", "F";
	locations.push_back(hospital3);
	if (canOfferUniversalCoverage(cities, locations, 3, result)) {
		cout << "Yes!" << endl;
		output(result);
	} else {
		cout << "No!" << endl;
	}
    return 0;
}
