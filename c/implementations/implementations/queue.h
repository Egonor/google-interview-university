#pragma once

#ifndef QUEUE_H
#define QUEUE_H

#endif

#include "linkedlist.h"


class ListQueue {
private:
	LinkedList q;
	//int size;					// Is this redundant?

public:
	ListQueue();
	ListQueue(int value);
	//~ListQueue();

	int Size();					// return size of queue
	bool isEmpty();				// return true if queue is empty

	void Enqueue(int value);	// Add value @ tail position
	int Dequeue();				// Remove and return last added value
	
};