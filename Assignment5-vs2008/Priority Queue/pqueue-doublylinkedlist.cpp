/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	// TODO: Fill this in!
	head = new node;
	dummy = head;
	head->prev = NULL;
	head->next = NULL;
	pqueueSize = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	// TODO: Fill this in!
	node *cur;
	cur = head;
	while (true) {
		if (head == NULL)
			break;
		head = head->next;
		delete cur;
		cur = head;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	// TODO: Fill this in!
	
	return pqueueSize;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	// TODO: Fill this in!
	
	return pqueueSize == 0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	// TODO: Fill this in!
	node *newbie = new node;
	newbie->value = value;
	newbie->prev = dummy;
	newbie->next = dummy->next;
	if (dummy->next != NULL)
		dummy->next->prev = newbie;
	dummy->next = newbie;
	pqueueSize++;
}

DoublyLinkedListPriorityQueue::node * DoublyLinkedListPriorityQueue::findMin(node *cur) {
	node *minP = cur;
	string min = cur->value;
	while (true) {
		if (cur == NULL)
			break;
		if (cur->value < min) {
			min = cur->value;
			minP = cur;
		}
		cur = cur->next;
	}
	return minP;
}

string DoublyLinkedListPriorityQueue::peek() {
	// TODO: Fill this in!
	if (isEmpty())
		error("peek: pqueue is empty!");
	node *minP = findMin(dummy->next);
	return minP->value;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	// TODO: Fill this in!
	if (isEmpty())
		error("peek: dequeue is empty!");
	node *cur = dummy->next;
	node *minP = findMin(cur);
	string min = minP->value;
	if (minP->next != NULL)
		minP->next->prev = minP->prev;
	minP->prev->next = minP->next;
	delete minP;
	pqueueSize--;

	return min;
}

