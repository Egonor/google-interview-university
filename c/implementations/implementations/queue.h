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

class ArrayQueue {
private:
	const static int bufferSize = 4;	// Uses to set initial buffer size
	int buffer[bufferSize];				// (changing size isn't implemented)
	int size;
	int readCursor = 0;
	int writeCursor = 0;

public:

	ArrayQueue();
	ArrayQueue(int value);
	//~ArrayQueue();

	int Size();
	bool isEmpty();
	bool isFull();
	
	void Enqueue(int value);
	int Dequeue();
};