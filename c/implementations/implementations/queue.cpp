#include "stdafx.h"
#include "queue.h"



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