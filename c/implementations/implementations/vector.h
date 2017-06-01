#pragma once

#ifndef VECTOR_H
#define VECTOR_H

#endif

template <typename T>                   // T = int> Default type to int: use as Vector<> myV;
class Vector {
private:
	u32 size;
	u32 capacity;						// Default vector capacity == 1024
    T*  storage;	   					// Pointer to array

	void Resize();						// Double size of Vector

public:
    Vector();// : size(0), capacity(2), storage(NULL) { storage = new T[capacity]; }

	u32 Size();							// return Size of Mutable Array
	u32 Capacity();						// return Capacity of Mutable Array
	bool isEmpty();						// Checker whether size >= 0

	u32 Access(u32 index);				// return the value at a given index

	void Push(T value);		    		// add value onto back of Mutable Array
	void Insert(u32 index, T value);	// add value at index in Mutable Array, shift other values right
	//void Prepend(int);				// add item at 0

	T Pop();							// remove value from back of Mutable Array
	void Delete(u32 index);				// remove value at index in Mutable Array, shift other values left
	void Remove(T value);				// remove any indexes containing value

	u32 Find(T value);			    	// return first index of value	

    int BinarySearch(int value);        // Binary search the vector
    int BinarySearchR(int value, int min, int max);       // Binary search using recursion
    // bool operator == (const Pair<T1, T2& Other) const {}
};


