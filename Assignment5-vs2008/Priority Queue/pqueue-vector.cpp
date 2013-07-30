/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	// TODO: Fill this in!
}

VectorPriorityQueue::~VectorPriorityQueue() {
	// TODO: Fill this in!
}

int VectorPriorityQueue::size() {
	// TODO: Fill this in!
	
	return pqueue.size();
}

bool VectorPriorityQueue::isEmpty() {
	// TODO: Fill this in!
	
	return pqueue.size() == 0;
}

void VectorPriorityQueue::enqueue(string value) {
	// TODO: Fill this in!
	pqueue.push_back(value);
}

//
int VectorPriorityQueue::findMin() {
	int minIndex = 0;
	string min = pqueue[0];
	for (int i = 1; i < pqueue.size(); i++)
		if (pqueue[i] < min) {
			min = pqueue[i];
			minIndex = i;
		}
	return minIndex;
}

string VectorPriorityQueue::peek() {
	// TODO: Fill this in!
	if (isEmpty())
		error("peek error: pqueue is empty");
	int index = findMin();
	return pqueue[index];
}

string VectorPriorityQueue::dequeueMin() {
	// TODO: Fill this in!
	if (isEmpty())
		error("dequeue error: pqueue is empty");
	int index = findMin();
	string min = pqueue[index];
	pqueue.remove(index);
	return min;
}

