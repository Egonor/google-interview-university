#pragma once

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#endif

// Advantages of Linked Lists:
// 1) Inserting an item is O(1) IF you have a reference to previous node.
// 2) List can keep growing until memory runs out.


struct Node {
	int item;
	Node* next;
};


class LinkedList {
private:
	Node* head;
	int size;

public:
	LinkedList();
	//LinkedList(int item, Node *next);
	LinkedList(int item);
	~LinkedList();

	int Size();								// return number of data elements in list
	bool isEmpty();							// return true if list is empty

	int Access(int index);					// return item at nth node (0 based)
	int Front();							// return First item
	int Back();								// return Last item
	int AccessFromEnd(int n);				// return item from nth node (from back of list)

	void PushFront(int value);				// add item to front of list
	void PushBack(int value);				// add item to back of list
	void Insert(int index, int value);		// add item after give index of list

	void PopFront();						// remove item from Front (memory leaks?)
	void PopBack();							// remove item from Back ("")
	void RemoveValue(int value);			// remove FIRST item with == Value
	void Erase(int index);					// remove ALL items with Value

	void Reverse(int value);				// reverse the list

	//void InsertAfter(int newItem);

};
