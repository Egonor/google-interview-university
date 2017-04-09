#pragma once


#ifndef VECTOR_H
#define VECTOR_H

#endif


class Vector {
private:
	int size;
	int capacity;						// Default vector capacity == 1024
	int * storage;						// Pointer to array

	void Resize();						// Double size of Vector

public:
	Vector();

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

};


