// implementations.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "vector.h"
#include "linkedlist.h"

// To WATCH use "storage, 10" (to display 10 array values){ <arrayname>, <#num values>

// Takes a pointer to a linked list because it calls
// destructor if given an actual list...
// Why it doesn't give it a copy, I don't understand...
// TODO: Look up Copy Constructor = may need to define copy's behavior for pass by value.
// https://stackoverflow.com/questions/21215409/does-c-pass-objects-by-value-or-reference
void PrintList(LinkedList *l) {
	printf("------------------------\n");
	for (int i = 0; i < l->Size(); i++) {
		printf("%d, ", l->Access(i));
	}
	printf("\n");
	printf("------------------------\n");
}


int main()
{
	LinkedList l;


	// TEST isEmpty()
	printf(l.isEmpty() ? "Empty: True\n" : "Empty: False\n");
	printf("Size(): %d\n", l.Size());

	/* TEST PushFront()	
	l.PushFront(6);
	l.PushFront(5);
	l.PushFront(4);
	l.PushFront(3);
	l.PushFront(2);
	l.PushFront(1);
	printf("PushFront(0): %d\n", l.Front());
	*/
	
	/* TEST PushBack() & Insert
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.Insert(1, 3);
	printf("%d %d %d %d\n", l.Access(0), l.Access(1), l.Access(2), l.Access(3));
	*/


	// TODO: Fix this shit, brain fried atm...
	// TEST PopFront()
	LinkedList front;
	for (int i = 1; i < 5; i++) {
		front.PushBack(i);
	}
	PrintList(&front);
	int toPopFront = front.Size() - 1;
	for (int i = 1; i < toPopFront; i++) {
		front.PopBack();
	}
	PrintList(&front);

	// TEST PopBack()
	LinkedList back;
	for (int i = 1; i < 5; i++) {
		back.PushBack(i);
	}
	PrintList(&back);
	int toPopBack = back.Size() - 1;
	for (int i = 1; i < toPopBack; i++) {
		back.PopBack();
	}
	PrintList(&back);

	/*
	// TEST Front()
	printf("Front(): %d\n", l.Front());
	// TEST Back()
	printf("Back(): %d\n", l.Back());
	// Test AccessFromEnd()
	printf("AccEnd(3): %d\n", l.AccessFromEnd(3));
	*/


	/* TEST isEmpty() 
	printf(l.isEmpty() ? "true\n" : "false\n");
	l.PushFront(12);
	printf(l.isEmpty() ? "true\n" : "false\n");

	// TEST Size()
	printf("Size: %d\n", l.Size());
	*/
	

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
	

	l.~LinkedList();
	printf(0);
}

