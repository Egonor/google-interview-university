#include "stdafx.h"
#include "queue.h"


#pragma region ListQueue
ListQueue::ListQueue() {
	// TODO: ?
}

ListQueue::ListQueue(int value) {
	q.PushBack(value);
}

/*
ListQueue::~ListQueue() {
	// TODO: Required or not?
}
*/

int ListQueue::Size() {
	return q.Size();
}

bool ListQueue::isEmpty() {
	//return size == 0;
	return q.isEmpty();
}

void ListQueue::Enqueue(int value){
	q.PushBack(value);
	//size++;
}

int ListQueue::Dequeue() {
	// Uses a temp value and two calls because PopFront() doesn't return a value.
	// LinkedList.PopFront() should probably be rewritten to return the popped value.
	if ( !isEmpty() ) {
		int temp = q.Front();
		q.PopFront();
		//size--;
		return temp;
	}
	else
		throw std::length_error("Cannot Dequeue() from an empty ListQueue");
}
#pragma endregion


#pragma region ArrayQueue
ArrayQueue::ArrayQueue() {
	size = 0;
	readCursor = 0;
	writeCursor = 0;
}

ArrayQueue::ArrayQueue(int value) {
	size = 0;
	readCursor = 0;
	writeCursor = 0;
	Enqueue(value);
}

/*
ArrayQueue::~ArrayQueue() {

}
*/

int ArrayQueue::Size() {
	return size;
}

bool ArrayQueue::isEmpty() {
	return size == 0;
}

bool ArrayQueue::isFull() {
	return size == bufferSize;
}

void ArrayQueue::Enqueue(int value) {
	// * Overwrites data rather than throwing an error
	//		- This is the simplest form of an ArrayQueue
	// * Uses a circular buffer to store queue

	buffer[writeCursor] = value;

	// If we've overwritten at readCursor, we have to increment
	// readCursor to the next (least recently added) value
	if (writeCursor == readCursor)
		readCursor = ((readCursor + 1) % bufferSize);

	// Wrap writeCursor if writing to end of buffer
	writeCursor = ((writeCursor + 1) % bufferSize);

	// TODO: This increases on the case where write wraps and read should still be 0 (off by +1)

	// We've enqueued more than our buffer can hold so...
	// we're overwriting/queue wrapping and size doesn't increase
	if (size < bufferSize)
		size++;
	
	/*
	// write to end case
	[1r, 2, 3, 4, w]
	enqueue(5);
	[1rw, 2, 3, 4, 5]
	just write++;

	// write to wrapped 0 case
	[1rw, 2, 3, 4, 5]
	enqueue(6);
	[6, 2rw, 3, 4, 5]
	read++ and write++;
	*/

}

int ArrayQueue::Dequeue() {
	int removed = buffer[readCursor];

	//if (removed == NULL) {
		// End of queue (figure out what to do that's not fail)
		// Queue can't hold zero values? set to -1, queue can't hold negative values...
	//}
	// Delete item as it has been read.
	buffer[readCursor] = -1;

	if (readCursor == (bufferSize - 1))
		readCursor = 0;
	else
		readCursor++;

	size--;
	return removed;
}

// * Just for testing purposes...
//		- Prints only positive list integers (if condition)
//		- Prints buffer start to finish (not read -> end queue order)
void ArrayQueue::Print() {
	printf("ArrayQueue [");
	for (int i = 0; i < bufferSize; i++) {
		if (buffer[i] >= -1)
			printf("%d, ", buffer[i]);
	}
	printf("]\n");
}
#pragma endregion
