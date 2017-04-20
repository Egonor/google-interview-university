// implementations.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "vector.h"
#include "linkedlist.h"
#include "queue.h"

// To WATCH use "storage, 10" (to display 10 array values){ <arrayname>, <#num values>

// Takes a pointer to a linked list because it calls
// destructor if given an actual list...
// Why it doesn't give it a copy, I don't understand...
// TODO: Look up Copy Constructor = may need to define copy's behavior for pass by value.
// https://stackoverflow.com/questions/21215409/does-c-pass-objects-by-value-or-reference
void PrintList(LinkedList *l) {
	printf("List[");
	for (int i = 0; i < l->Size(); i++) {
		printf("%d, ", l->Access(i));
	}
	printf("]\n");
}


int main()
{

#pragma region Queue Tests


	// ListQueue Tests
	/*
	ListQueue lQ;

	printf("\nlq.Size = %d\n", lQ.Size());
	printf(lQ.isEmpty() ? "lQ Empty\n" : "lq NOT Empty\n");

	lQ.Enqueue(1);
	lQ.Enqueue(2);
	lQ.Enqueue(3);
	lQ.Enqueue(4);
	printf("\nlq.Size = %d\n", lQ.Size());
	printf(lQ.isEmpty() ? "lQ Empty\n" : "lq NOT Empty\n");
	
	printf("Dequeued: %d\n", lQ.Dequeue());
	printf("Dequeued: %d\n", lQ.Dequeue());
	printf("Dequeued: %d\n", lQ.Dequeue());
	printf("Dequeued: %d\n", lQ.Dequeue());

	printf("\nlq.Size = %d\n", lQ.Size());
	printf(lQ.isEmpty() ? "lQ Empty\n" : "lq NOT Empty\n");
	*/

#pragma endregion

#pragma region LinkedList Tail Tests
	// TODO: Are all the TAIL pointer adjustments unneccesary because I don't understand pointers?
	/*
	printf("\n-----List 1-----\n");
	LinkedList t;
	printf(t.isEmpty() ? "isEmpty()?: true\n" : "isEmpty()?: false\n");
	t.PushBack(1);
	t.PushBack(2);
	t.PushBack(3);
	PrintList(&t);

	// Test Access
	printf("t[0] = %d...t[front] = %d\n", t.Access(0), t.Front());
	printf("t[1] = %d...t[end-1] = %d\n", t.Access(1), t.AccessFromEnd(1));
	printf("t[2] = %d...t[back ] = %d\n", t.Access(2), t.Back());

	printf("\nPushFront(0):\n");
	t.PushFront(0);
	printf("t[0] = %d\n", t.Front());

	PrintList(&t);
	printf("\nInsert(2, 3):\n");
	t.Insert(2, 99);

	PrintList(&t);

	printf("\nInsert(@end, 4):\n");
	t.Insert(t.Size() - 1, 4);
	PrintList(&t);

	printf("\nPopBack():\n");
	t.PopBack();
	PrintList(&t);
	
	// Test removing last value
	printf("\nRemoveValue(3):\n");
	t.RemoveValue(3);
	PrintList(&t);

	// Test updating tail when removing from list with one value
	printf("\n-----List 2-----\n");
	LinkedList t2 = LinkedList(1);
	PrintList(&t2);

	printf("\nPopFront():\n");
	t2.PopFront();
	PrintList(&t2);
	// List is empty, test tail adjustment with PushFront on empty list
	t2.PushFront(1);
	PrintList(&t2);

	t2.PushBack(1);
	PrintList(&t2);
	t2.RemoveValue(1);
	//t2.Erase(1);
	PrintList(&t2);

	t2.PushBack(1);
	t2.PushBack(2);
	t2.PushBack(3);
	PrintList(&t2);
	t2.Erase(3);
	PrintList(&t2);

	printf("\nSize of t = %d\n", t.Size());
	printf(t.isEmpty() ? "isEmpty()?: true\n" : "isEmpty()?: false\n");
	*/
#pragma endregion

#pragma region Vector Tests
	/*
	Vector v;
	
	v.Push(1);
	v.Push(2);
	v.Push(3);
	v.Push(4);
	v.Push(5);
	v.Push(6);
	v.Push(7);
	v.Push(8);
	v.Push(9);
	v.Push(5);
	v.Push(11);
	v.Push(12);
	v.Push(13);
	v.Push(5);

	printf("Searching through...\n");
	for (int i = 0; i < v.Size(); i++)
	{
		printf("%i ", v.Access(i));
	}

	// Should be v[4]
	int val = v.Find(69);
	if (val != NULL)
		printf("\n5 Found at v[%i]! ", v.Find(5));
	else
	{
		printf("\nVal not found");
	}

	/*
	// Add 10 random numbers to v
	srand(time(NULL));
	for (int i = 0; i < 10; i++) {
		v.Push(rand() % 3);
	}

	// Print Vector pre function
	printf("BEFORE:\n");
	for (int i = 0; i < v.Size(); i++)
	{
		printf("%i ", v.Access(i));
	}

	// TEST INSERT()
	//v.Insert(5, 9999);

	// TEST POP()
	//v.Pop();

	// TEST DELETE()
	//v.Delete(5)

	// TEST REMOVE()
	//v.Remove(2);
	
	// Print Vector post function
	printf("\nPOST:\n");
	for (int i = 0; i < v.Size(); i++)
	{
		printf("%i ", v.Access(i));
	}	
	*/

	/* TEST isEmpty()
	printf(v.isEmpty() ? "true\n" : "false\n");
	v.Push(32);
	printf(v.isEmpty() ? "true\n" : "false\n");
	*/
	
#pragma endregion
	
	printf(0);
}