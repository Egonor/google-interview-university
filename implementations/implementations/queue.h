#pragma once

#ifndef QUEUE_H
#define QUEUE_H

#include "linkedlist.h"

class ListQueue {
private:
	LinkedList q;
	//int size;							// redundant? Can use LinkedList.Size()

public:
	ListQueue();
	ListQueue(int value);
	//~ListQueue();

	int Size();							// return size of queue
	bool isEmpty();						// return true if queue is empty

	void Enqueue(int value);			// Add value @ tail position
	int Dequeue();						// Remove and return last added value	
};

class ArrayQueue {
private:
	const static int bufferSize = 256;	// Uses to set initial buffer size
	int buffer[bufferSize];				// (changing size isn't implemented)
	int size;
	int readCursor;
	int writeCursor;

public:

	ArrayQueue();
	ArrayQueue(int value);
	//~ArrayQueue();

	int Size();							// return size of queue
	bool isEmpty();						// return true if queue is empty
	bool isFull();						// return true if queue is full
										// (not useful w/ overwriting circular buffer)	
	void Enqueue(int value);			// Add an item at the back of queue
	int Dequeue();						// Pop and return item from front of queue

	void Print();
};

#endif