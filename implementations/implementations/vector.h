#pragma once

#ifndef VECTOR_H
#define VECTOR_H

// WARN: Untested if inserting an invalid type works. Compiler handles?
//       i.e. vec is type Vector<int>, called vec.Insert(bool);

template <typename T>                   // T = int> Default type to int: use as Vector<> myV;
class Vector {
private:
	u32 size;
	u32 capacity;						// Default vector capacity == 1024
    T*  storage;	   					// Pointer to array
    
public:
    Vector();// : size(0), capacity(2), storage(NULL) { storage = new T[capacity]; }
    ~Vector();

	u32 Size();							// return Size of Mutable Array
	u32 Capacity();						// return Capacity of Mutable Array
	bool isEmpty();						// Checker whether size >= 0

	u32 Access(u32 index);				// return the value at a given index

	void Push(T value);		    		// add value onto back of Mutable Array
	void Insert(u32 index, T value);	// add value at index in Mutable Array, shift other values right
	//void Prepend(int);				// add item at 0

	T Pop();							// remove value from back of Mutable Array
	T Delete(u32 index);				// remove value at index in Mutable Array, shift other values left (returns value deleted or NULL) 
	u32 Remove(T value);				// remove any indexes containing value (returns count removed)

	int Find(T value);			    	// return first index of value	

    int BinarySearch(int value);        // Binary search the vector
    int BinarySearchR(int value, int min, int max);       // Binary search using recursion
    // bool operator == (const Pair<T1, T2& Other) const {}
};


#pragma region OLD - 5/30/17
/* 
// Replaced with TWO implementations:
        1) GenericVector (Inclusion Model)
        2) vector.h & vector.cpp

class Vector {
private:
int size;
int capacity;						// Default vector capacity == 1024
int * storage;						// Pointer to array

void Resize();						// Double size of Vector

public:
Vector();
Vector(int initialSize);			// initialize a vector with a starting size

int Size();							// return Size of Mutable Array
int Capacity();						// return Capacity of Mutable Array
bool isEmpty();						// Checker whether size >= 0

int Access(int index);				// return the value at a given index

void Push(int value);				// add value onto back of Mutable Array
void Insert(int index, int value);	// add value at index in Mutable Array, shift other values right
//void Prepend(int);				// add item at 0

int Pop();							// remove value from back of Mutable Array
void Delete(int index);				// remove value at index in Mutable Array, shift other values left
void Remove(int value);				// remove any indexes containing value

int Find(int value);				// return first index of value
// 5/17/17
// should be u32?  vector[u32] doesn't work so would have to rewrite
int BinarySearch(int value);        // Binary search the vector
int BinarySearchR(int value);       // Binary search using recursion
};
*/
#pragma endregion


#endif