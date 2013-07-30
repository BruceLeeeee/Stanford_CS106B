/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	// TODO: Fill this in!
	dummy = new node;
	dummy->next = NULL;
	head = dummy;
	count = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	// TODO: Fill this in!
	node *cur = head;
	while (true) {
		if (head == NULL)
			break;
		cur = head;
		head = head->next;
		delete cur;
	}
}

int LinkedListPriorityQueue::size() {
	// TODO: Fill this in!
	
	return count;
}

bool LinkedListPriorityQueue::isEmpty() {
	// TODO: Fill this in!
	
	return count == 0;
}

void LinkedListPriorityQueue::enqueue(string value) {
	// TODO: Fill this in!
	node *prev, *cur, *newbie;
	cur = dummy->next;
	prev = dummy;
	newbie = new node;
	newbie->value = value;
	newbie->next = NULL;	
	while (true) {
		if (cur == NULL)
			break;
		if (cur->value > value)
			break;
		prev = cur;
		cur = cur->next;
	}
	newbie->next = prev->next;
	prev->next = newbie;
	
	count++;
}

string LinkedListPriorityQueue::peek() {
	// TODO: Fill this in!
	if (isEmpty()) 
		error("peek: pqueue is empty!");
	return head->next->value;
}

string LinkedListPriorityQueue::dequeueMin() {
	// TODO: Fill this in!
	if (isEmpty()) 
		error("dequeue: pqueue is empty!");
	node *min = head->next;
	string value = min->value;
	dummy->next = dummy->next->next;
	delete min;
	count--;
	return value;
}

