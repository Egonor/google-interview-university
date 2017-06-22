#include "stdafx.h"
#include "vector.h"
#include "linkedlist.h"
#include "queue.h"
#include "dictionary.h"
#include "GenericVector.h"
#include "BinaryTree.h"
#include "bst.h"


int main()
{

#pragma region Binary Search Tree Tests
    /*
    BST tree;
        0
        5
       / \
       2  6
        \  \
        4   8
       /   / \
      3   7   9      

    // root
    BST_Add(&tree, 5);    
    BST_Add(&tree, 2);    // test right child only (delete 2)
    BST_Add(&tree, 4);    // test left child only (delete 4)
    BST_Add(&tree, 3);
    // for both children
    BST_Add(&tree, 6);
    BST_Add(&tree, 8);
    BST_Add(&tree, 7);
    BST_Add(&tree, 9);    // test both children (delete 8)

    PrintTree(&tree);
    DeleteFromTree(&tree, 2);   // test right child only (delete 2)
    PrintTree(&tree);
    DeleteFromTree(&tree, 4);   // test left child only (delete 4)
    PrintTree(&tree);
    DeleteFromTree(&tree, 8);
    PrintTree(&tree);   
    */


    BST root;
    BST_Add(&root, 5);
    BST_Print_LevelOrder(&root);
    
    /*
    BinaryTree<int> tree(5);// = new BinaryTree<int>(5);// = new BinaryTree<int>(1, NULL);
    tree.Add(1);
    tree.Add(3);
    tree.Add(6);
    tree.Add(7);
    tree.Add(9);
    */
#pragma endregion

#pragma region GenericVector (template) Tests
    /*
    // To WATCH use "storage, 10" (to display 10 array values){ <arrayname>, <#num values>
    Vector<int> vec;

    vec.Push(1234);
    vec.Push(2341);
    vec.Push(3412);
    vec.Push(4123);

    GenericVector<int> genVec;

    genVec.Push(1234);
    genVec.Push(999);
    genVec.Push(2);  // TODO: TEST
    genVec.Push(3);
    genVec.Push(4);
    */
#pragma endregion
            
#pragma region Binary Search Test
    /*
    // Setup sorted vector [0, ... 9]
    Vector bin;
    for (int i = 0; i < 10; ++i) {
        bin.Push(i);
    }

    printf("0 is at index: %d\n", bin.BinarySearch(0));
    printf("1 is at index: %d\n", bin.BinarySearch(1));
    printf("2 is at index: %d\n", bin.BinarySearch(2));
    printf("3 is at index: %d\n", bin.BinarySearch(3));
    printf("4 is at index: %d\n", bin.BinarySearch(4));
    printf("5 is at index: %d\n", bin.BinarySearch(5));
    printf("6 is at index: %d\n", bin.BinarySearch(6));
    printf("7 is at index: %d\n", bin.BinarySearch(7));
    printf("8 is at index: %d\n", bin.BinarySearch(8));
    printf("9 is at index: %d\n", bin.BinarySearch(9));

    printf("0 is at index: %d\n", bin.BinarySearchR(0, 0, bin.Size()));
    */

#pragma endregion

#pragma region Hash Tests
    /*
    // c++ hash 
	// hash<string> hash_fn;
	// size_t hash = hash_fn(s);	
	// printf("%d", hash);
	
	string temp = "Supposedly there are over one million words in the English Language. We trimmed some fat to take away really odd words and determiners. Then we grabbed the most popular words and built this word randomizer. Just keep clicking generate—chances are you won't find a repeat!";

	Dictionary d(16);

	d.Insert(" over", 69);
	
	printf("Inserting 'alpha' at hash: %d\n", d.Insert("alpha", 100));			// 11
	printf("Inserting 'beta' at hash: %d\n", d.Insert("beta", 200));			// 1
	
	printf("Does 'alpha' exist? %s\n", d.Exists("alpha") ? "true" : "false");	// true
	printf("Does charlie exist? %s\n", d.Exists("charlie") ? "true" : "false");	// false

	printf("Value of 'beta': %d\n", d.GetValue("beta"));							// 200
	printf("Value of 'gamma': %d\n", d.GetValue("gamma"));						// Error

	printf("Delete 'beta' @: %d\n", d.Delete("beta"));
	printf("Delete 'zulu' @: %d\n", d.Delete("zulu"));
	
	// Test Growth
	for (int i = 0; i < (25*5); i+=5) {
		string t = temp.substr(i, 5);
		printf("Inserting '%s' at hash: %d\n", t.c_str(), d.Insert(t, i));
	}
	d.Size();	
    */
#pragma endregion

#pragma region Queue Tests
	// ArrayQueue Tests
	/*
	ArrayQueue aq;
	
	// Test empty ArrayQueue
	aq.Print();
	printf("ArrayQueue.isEmpty(t): %s\n", aq.isEmpty() ? "True" : "False");
	printf("ArrayQueue.isFull(f): %s\n", aq.isFull() ? "True" : "False");

	// Test single item ArrayQueue
	aq.Enqueue(1);
	aq.Print();
	printf("ArrayQueue.isEmpty(f): %s\n", aq.isEmpty() ? "True" : "False");
	printf("ArrayQueue.isFull(f): %s\n", aq.isFull() ? "True" : "False");

	// Test full ArrayQueue
	aq.Enqueue(2);
	aq.Enqueue(3);
	aq.Enqueue(4);
	aq.Print();
	printf("ArrayQueue.isFull(t): %s\n", aq.isFull() ? "True" : "False");

	// Test overwriting full ArrayQueue
	aq.Enqueue(5);
	aq.Print();
	printf("ArrayQueue.isFull(t): %s\n", aq.isFull() ? "True" : "False");
		
	// Test removing items from ArrayQueue
	printf("Removed: %d\n", aq.Dequeue());

	aq.Print();
	printf("ArrayQueue.isEmpty(f): %s\n", aq.isEmpty() ? "True" : "False");
	printf("ArrayQueue.isFull(f): %s\n", aq.isFull() ? "True" : "False");

	printf("Removed: %d\n", aq.Dequeue());
	printf("Removed: %d\n", aq.Dequeue());
	printf("Removed: %d\n", aq.Dequeue());

	// Test emptied ArrayQueue
	aq.Print();
	printf("ArrayQueue.isEmpty(t): %s\n", aq.isEmpty() ? "True" : "False");
	printf("ArrayQueue.isFull(f): %s\n", aq.isFull() ? "True" : "False");
	*/
	

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
	
	printf("End...");
}