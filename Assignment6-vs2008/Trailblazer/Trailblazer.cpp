/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "random.h"
using namespace std;

#define P 1e-6

void initSP(Loc &start,
		  Grid<Loc> &parent,
		  Grid<Color> &cellColor,
		  Grid<double> &dist,
		  Grid<double>& world) {
	parent.resize(world.nRows, world.nCols);
	cellColor.resize(world.nRows, world.nCols);
	dist.resize(world.nRows, world.nCols);
	for (int i = 0; i < world.nRows; i++)
		for (int j = 0; j < world.nCols; j++)
			cellColor[i][j] = GRAY;
	dist[start.row][start.col] = 0;
}

bool isOutOfBounds(int rNext, int cNext, int row, int col) {
	if (rNext < 0 || rNext >= row)
		return true;
	if (cNext < 0 || cNext >= col)
		return true;
	return false;
}

void reverse(Vector<Loc> &path) {
	Vector<Loc> result;
	for (int i = path.size() - 1; i >= 0; i--)
		result.push_back(path[i]);
	path = result;
}

void getPath(Loc start,
             Loc end,
			 Vector<Loc> &path, 
			 Grid<Loc> &parent) {
	Loc loc = end;
	path.push_back(loc);
	while (true) {
		loc = parent[loc.row][loc.col];
		path.push_back(loc);
		if (loc == start)
			break;
	}
	reverse(path);
}

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
Vector<Loc>
shortestPath(Loc start,
             Loc end,
             Grid<double>& world,
             double costFn(Loc from, Loc to, Grid<double>& world),
			 double heuristic(Loc start, Loc end, Grid<double>& world)) {
	// TODO: Fill this in!
	//error("shortestPath is not implemented yet.");
	Grid<Loc> parent;
	Grid<Color> cellColor;
	Grid<double> dist;
	int dir[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
	Vector<Loc> path;
	TrailblazerPQueue<Loc> pqueue;
	initSP(start, parent, cellColor, dist, world);
	cellColor[start.row][start.col] = YELLOW;
	colorCell(world, start, YELLOW);
	parent[start.row][start.col] = start;
	pqueue.enqueue(start, heuristic(start, end, world));
	while (!pqueue.isEmpty()) {
		Loc curr = pqueue.dequeueMin();
		cellColor[curr.row][curr.col] = GREEN;
		colorCell(world, curr, GREEN);
		if (curr == end)
			break;
		for (int i = 0; i < 8; i++) {
			int rNext = curr.row + dir[i][0];
			int cNext = curr.col + dir[i][1];
			if (isOutOfBounds(rNext, cNext, world.nRows, world.nCols))
				continue;
			Loc next;
			next.row = rNext;
			next.col = cNext;
			double L = costFn(curr, next, world);
			if (cellColor[rNext][cNext] == GRAY) {
				cellColor[rNext][cNext] = YELLOW;
				colorCell(world, next, YELLOW);
				dist[rNext][cNext] = dist[curr.row][curr.col] + L;
				parent[rNext][cNext] = curr;
				pqueue.enqueue(next, dist[rNext][cNext] + heuristic(next, end, world));
			} else if (cellColor[rNext][cNext] == YELLOW &&
					dist[rNext][cNext] - (dist[curr.row][curr.col] + L) > P) {
				dist[rNext][cNext] = dist[curr.row][curr.col] + L;
				parent[rNext][cNext] = curr;
				pqueue.decreaseKey(next, dist[rNext][cNext] + heuristic(next, end, world));
			}
		}
	}
	getPath(start, end, path, parent);
    return path;
}

void initMST (int numRows, int numCols, Vector<int> &parent, TrailblazerPQueue<Edge> &pqueue) {
	int dir[2][2] = {{-1, 0}, {0, 1}};
	for (int i = 0; i < numRows; i++)
		for (int j = 0; j < numCols; j++) {
			int node = i * numCols + j;
			parent[node] = node;
		}
	
	for (int i = 0; i < numRows; i++)
		for (int j = 0; j < numCols; j++)
			for (int k = 0; k < 2; k++) {
				int rNext = i + dir[k][0];
				int cNext = j + dir[k][1];
				if (isOutOfBounds(rNext, cNext, numRows, numCols))
					continue;
				Edge edge;
				Loc loc1;
				Loc loc2;
				loc1.row = i;
				loc1.col = j;
				loc2.row = rNext;
				loc2.col = cNext;
				edge.start = loc1;
				edge.end = loc2;
				double len = randomReal(0, 1);
				pqueue.enqueue(edge, len);
			}

}

// use disjoint-set data structure with Path Compression
int find(int node, Vector<int> &parent) {
	if (parent[node] == node)
		return node;
	else {
		int root = find(parent[node], parent);
		parent[node] = root;
		return root;
	}
}

Set<Edge> createMaze(int numRows, int numCols) {
	// TODO: Fill this in!
	//error("createMaze is not implemented yet.");
	Set<Edge> mst;
	Vector<int> parent(numRows * numCols);
	TrailblazerPQueue<Edge> pqueue;
	int clusterCount = numRows * numCols;
	initMST(numRows, numCols, parent, pqueue);
	while (!pqueue.isEmpty()) {
		Edge edge = pqueue.dequeueMin();
		Loc loc1 = edge.start;
		Loc loc2 = edge.end;
		int node1 = loc1.row * numCols + loc1.col;
		int node2 = loc2.row * numCols + loc2.col;
		int node1Root = find(node1, parent);
		int node2Root = find(node2, parent);
		if (node1Root == node2Root)
			continue;
		mst.add(edge);
		parent[node1Root] = node2Root;
		clusterCount--;
		if (clusterCount == 1)
			break;
	}
    return mst;
}
