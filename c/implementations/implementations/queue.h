#pragma once

#ifndef QUEUE_H
#define QUEUE_H

#endif

#include "linkedlist.h"


class ListQueue {
private:
	LinkedList q;
	int size;

public:
	ListQueue();
	ListQueue(int item);
	~ListQueue();

	bool isEmpty();				// return true if queue is empty

	void Enqueue(int value);	// Add value @ tail position
	int Dequeue();				// Remove and return last added value
	
};