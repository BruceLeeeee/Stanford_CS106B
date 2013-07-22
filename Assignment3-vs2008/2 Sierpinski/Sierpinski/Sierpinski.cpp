/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gwindow.h"
#include <cmath>
using namespace std;

const double WIN_WIDTH = 800;
const double WIN_HEIGHT = 800;

void recDraw(GWindow &gw, GPoint &upperLeft, double edgeLen, int order) {
	if (order == 0) {
		GPoint p0(upperLeft.getX() + edgeLen / 2, upperLeft.getY());
		GPoint p1 = gw.drawPolarLine(p0, edgeLen, -120);
		GPoint p2 = gw.drawPolarLine(p1, edgeLen, 0);
		gw.drawPolarLine(p2, edgeLen, 120);
		return;
	}
	GPoint top(upperLeft.getX() + edgeLen / 4, upperLeft.getY());
	recDraw(gw, top, edgeLen / 2, order - 1);

	GPoint left(upperLeft.getX(), upperLeft.getY() + sqrt(3.0) / 2 * edgeLen / 2);
	recDraw(gw, left, edgeLen / 2, order - 1);

	GPoint right(upperLeft.getX() + edgeLen / 2, upperLeft.getY() + sqrt(3.0) / 2 * edgeLen / 2);
	recDraw(gw, right, edgeLen / 2, order - 1);
}

int main() {
    // [TODO: fill with your code]
	GWindow gw(WIN_WIDTH, WIN_HEIGHT);
	double edgeLen;
	int order;

	cout << "Edge length: ";
	cin >> edgeLen;
	cout << "Order = ";
	cin >> order;

	GPoint upperLeft((WIN_WIDTH - edgeLen) / 2, (WIN_HEIGHT - sqrt(3.0) / 2 * edgeLen) / 2);
	recDraw(gw, upperLeft, edgeLen, order);

    return 0;
}
