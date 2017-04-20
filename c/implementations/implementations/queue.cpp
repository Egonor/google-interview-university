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


ArrayQueue::ArrayQueue() {

}

ArrayQueue::ArrayQueue(int value) {

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
	return size == 4;
}

void ArrayQueue::Enqueue(int value) {
	// * Overwrites data rather than throwing an error
	//		- This is the simplest form of an ArrayQueue
	// * Uses a circular buffer to store queue

	buffer[writeCursor] = value;
	// wrap if writing to end of array
	if (writeCursor == (size - 1))
		writeCursor = 0;
	else
		writeCursor++;
}

int ArrayQueue::Dequeue() {
	int removed = buffer[readCursor];
	if (removed == NULL) {
		// End of queue (figure out what to do that's not fail)
		// Queue can't hold zero values? set to -1, queue can't hold negative values...
	}
	// Delete item as it has been read.
	buffer[readCursor] = NULL;

	// TODO: These don't maintain the read/write order, they just dumbly wrap.
	if (readCursor == (size - 1))
		readCursor = 0;
	else
		readCursor++;

	return removed;
}