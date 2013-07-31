/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
	// TODO: Fill this in!
	usedCount = 1;
	allocatedCount = 2;
	minHeap = new string[2];
	minHeap[0] = "dummy";
}

HeapPriorityQueue::~HeapPriorityQueue() {
	// TODO: Fill this in!
	delete[] minHeap;
}

int HeapPriorityQueue::size() {
	// TODO: Fill this in!
	
	return usedCount - 1;
}

bool HeapPriorityQueue::isEmpty() {
	// TODO: Fill this in!
	
	return usedCount == 1;
}

void HeapPriorityQueue::enlarge() {
	string *newArray = new string[allocatedCount * 2];
	for (int i = 0; i < usedCount; i++)
		newArray[i] = minHeap[i];
	delete[] minHeap;
	minHeap = newArray;
	allocatedCount *= 2;
}

void HeapPriorityQueue::swap(string &a, string &b) {
	string tmp;
	tmp = a;
	a = b;
	b = tmp;
}

void HeapPriorityQueue::bubbleUp(int index) {
	int parent = index / 2;
	if (parent == 0)
		return;
	if (minHeap[index] < minHeap[parent]) {
		swap(minHeap[index], minHeap[parent]);
		bubbleUp(parent);
	}
}

void HeapPriorityQueue::enqueue(string value) {
	// TODO: Fill this in!
	if (usedCount == allocatedCount)
		enlarge();
	minHeap[usedCount] = value;
	bubbleUp(usedCount);
	usedCount++;
}

string HeapPriorityQueue::peek() {
	// TODO: Fill this in!
	if (isEmpty())
		error("peek: pqueue is empty!");
	return minHeap[1];
}

void HeapPriorityQueue::bubbleDown(int index) {
	int left = index * 2;
	int right = index * 2 + 1;
	int minIndex = index;
	if (left < usedCount && minHeap[minIndex] > minHeap[left])
		minIndex = left;
	if (right < usedCount && minHeap[minIndex] > minHeap[right])
		minIndex = right;
	if (minIndex != index) {
		swap(minHeap[index], minHeap[minIndex]);
		bubbleDown(minIndex);
	}
}

string HeapPriorityQueue::dequeueMin() {
	// TODO: Fill this in!
	if (isEmpty())
		error("dequeue: pqueue is empty!");
	string min = minHeap[1];
	minHeap[1] = minHeap[usedCount - 1];
	usedCount--;
	bubbleDown(1);
	return min;
}

