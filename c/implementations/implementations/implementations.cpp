// implementations.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "vector.h"
#include "linkedlist.h"

// To DEBUG use "storage, 10" (to display 10 array values) "<arrayname>, <#num values>"


int main()
{
	LinkedList l;


	// TEST isEmpty()
	printf(l.isEmpty() ? "Empty: True\n" : "Empty: False\n");
	printf("Size(): %d\n", l.Size());

	// TEST PushFront()
	l.PushFront(6);
	l.PushFront(5);
	l.PushFront(4);
	l.PushFront(3);
	l.PushFront(2);
	l.PushFront(1);

	// Test Access()
	printf("Item 1: %d\n", l.Access(0));
	printf("Item 2: %d\n", l.Access(1));
	printf("Item 3: %d\n", l.Access(2));
	printf("Item 4: %d\n", l.Access(3));
	printf("Item 5: %d\n", l.Access(4));
	printf("Item 6: %d\n", l.Access(5));

	// TEST Front()
	printf("Front(): %d\n", l.Front());
	// TEST Back()
	printf("Back(): %d\n", l.Back());

	// TEST isEmpty() (After filling)
	printf("Empty(): %s", l.isEmpty() ? "True\n" : "False\n");
	// TEST Size()
	printf("Size(): %d\n", l.Size());




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
	printf(NULL);
}

