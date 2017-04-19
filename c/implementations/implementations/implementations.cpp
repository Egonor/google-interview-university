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
	for (int i = 0; i < l->Size(); i++) {
		printf("%d, ", l->Access(i));
	}
	printf("\n");
}


int main()
{
	// LinkedList Tail Tests
	/**/
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
	LinkedList t2;
	t2.PushBack(1);
	PrintList(&t2);
	t.RemoveValue(1);
	PrintList(&t2);


	printf("\nSize of t = %d\n", t.Size());
	printf(t.isEmpty() ? "isEmpty()?: true\n" : "isEmpty()?: false\n");

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

//
//LinkedList l;
//
//printf("Size(): %d\n", l.Size());
//printf(l.isEmpty() ? "Empty: True\n" : "Empty: False\n");
//
//
//// TEST Revere()
//LinkedList r;
//
//r.PushBack(1);
///*
//r.PushBack(2);
//r.PushBack(3);
//r.PushBack(4);
//*/
//
//PrintList(&r);
//r.Reverse();
//PrintList(&r);
//
//
//// TEST Erase()				"remove all value == arg (int value)"
///*
//LinkedList e;
//e.PushBack(1);
//e.PushBack(2);
//e.PushBack(2);
//e.PushBack(3);
//e.PushBack(1);
//e.PushBack(3);
//e.PushBack(3);
//e.PushBack(1);
//
//PrintList(&e);
//e.Erase(1);
//PrintList(&e);
//*/
//
//// TEST RemoveValue()
///*
//LinkedList removeVal;
//
//for (int i = 1; i < 6; i++) {				// Setup Lists for Test [1, 2, 3, 4, 5]
//removeVal.PushBack(i);
//}
//PrintList(&removeVal);						// Print initial list
//
//removeVal.RemoveValue(10);					// Attempt (and fail) to remove 10 from list
//PrintList(&removeVal);
//
//removeVal.RemoveValue(1);					// Remove 1 from the list (first item)
//PrintList(&removeVal);
//
//removeVal.RemoveValue(3);					// Remove 3 from the list (middle item)
//PrintList(&removeVal);
//
//removeVal.RemoveValue(5);					// remove 5 from the list (end item)
//PrintList(&removeVal);
//*/
//
//// TEST PushFront()	
///*
//for (int pushfront = 5; pushfront >= 0; pushfront--){
//l.PushFront(i);
//}
//printf("PushFront(0): %d\n", l.Front());
//*/
//
//// TEST PushBack() & Insert
///*
//l.PushBack(1);
//l.PushBack(2);
//l.PushBack(4);
//l.Insert(1, 3);
//printf("%d %d %d %d\n", l.Access(0), l.Access(1), l.Access(2), l.Access(3));
//*/
//
//// TODO: Fix this shit, brain fried atm...
///* TEST PopFront()
//LinkedList front;
//for (int i = 1; i < 5; i++) {
//front.PushBack(i);
//}
//PrintList(&front);
//int toPopFront = front.Size() - 1;
//for (int i = 1; i < toPopFront; i++) {
//front.PopBack();
//}
//PrintList(&front);
//*/
//
///* TEST PopBack()
//LinkedList back;
//for (int i = 1; i < 5; i++) {
//back.PushBack(i);
//}
//PrintList(&back);
//int toPopBack = back.Size() - 1;
//for (int i = 1; i < toPopBack; i++) {
//back.PopBack();
//}
//PrintList(&back);
//*/
//
///*
//// TEST Front()
//printf("Front(): %d\n", l.Front());
//// TEST Back()
//printf("Back(): %d\n", l.Back());
//// Test AccessFromEnd()
//printf("AccEnd(3): %d\n", l.AccessFromEnd(3));
//*/
//
//
///* TEST isEmpty()
//printf(l.isEmpty() ? "true\n" : "false\n");
//l.PushFront(12);
//printf(l.isEmpty() ? "true\n" : "false\n");
//
//// TEST Size()
//printf("Size: %d\n", l.Size());
//*/
//
