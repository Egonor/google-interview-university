#pragma once

#ifndef LINKEDLIST_H
#define LINKEDLIST_H


// Advantages of Linked Lists:
// 1) Inserting an value is O(1) IF you have a reference to previous node.
// 2) List can keep growing until memory runs out.


struct Node {
	int value;
	Node* next;
};


class LinkedList {
private:
	Node* head;
	Node* tail;
	int size;

public:
	LinkedList();
	LinkedList(int value);
	//LinkedList(int value, Node *next);
	~LinkedList();

	void PrintList();

	int Size();								// return number of data elements in list
	bool isEmpty();							// return true if list is empty

	int Access(int index);					// return value at nth node (0 based)
	int Front();							// return First value
	int Back();								// return Last value
	int AccessFromEnd(int n);				// return value from nth node (from back of list)

	void PushFront(int value);				// add value to front of list
	void PushBack(int value);				// add value to back of list
	void Insert(int index, int value);		// add value after give index of list

	void PopFront();						// remove value from Front (memory leaks?)
	void PopBack();							// remove value from Back ("")
	void RemoveValue(int value);			// remove FIRST value with == Value
	void Erase(int value);					// remove ALL values with Value

	void Reverse();							// reverse the list
};

#endif
