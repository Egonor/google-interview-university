#include "stdafx.h"

#pragma once

#ifndef GenericVector_H
#define GenericVector_H

#endif

template <typename T>                   // T = int> Default type to int: use as GenericVector<> myV;
class GenericVector {
private:
    u32 size;
    u32 capacity;						// Default vector capacity == 1024
    T*  storage;	   					// Pointer to array

    void Resize();						// Double size of vector

public:
    GenericVector()
    {
        size = 0;
        capacity = 2;
        storage = new T[capacity]; 
    }

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

    int BinarySearch(int value);        // Binary search the GenericVector
    int BinarySearchR(int value, int min, int max);       // Binary search using recursion
                                                          // bool operator == (const Pair<T1, T2& Other) const {}
};

#include "GenericVector.h"


/*********************Public*****************************/
template<typename T>
u32 GenericVector<T>::Size() {
    return size;
}

template<typename T>
u32 GenericVector<T>::Capacity() {
    return capacity;
}

template<typename T>
bool GenericVector<T>::isEmpty() {
    if (size == 0)
        return true;
    else
        return false;
}

template<typename T>
u32 GenericVector<T>::Access(u32 index) {
    if (index <= size && index >= 0)
        return storage[index];
    else
        throw std::out_of_range("Tried to Access() invalid index.");
}

template<typename T>
void GenericVector<T>::Push(T value) {
    if (size < capacity)
        storage[size] = value;
    else {
        Resize();
        storage[size] = value;
    }
    size++;
}

template<typename T>
void GenericVector<T>::Insert(u32 index, T value) {
    // TODO: Handle index == 0 with Prepend() or in here
    if (index > 0) {
        if (size + 1 == capacity)
            Resize(); //TODO: Resize(1); for growth

        T * temp = new T[capacity];

        for (int i = 0; i < size + 1; i++) {
            if (i < index)
                temp[i] = storage[i];
            else if (i == index)
                temp[i] = value;
            else
                temp[i] = storage[i - 1];
        }

        size++;

        delete[] storage;
        storage = temp;
    }
}

template<typename T>
T GenericVector<T>::Pop() {
    // TODO: Resize by half if size <= cap / 2
    // Value still exists, the tracker for Size is just moved ahead of it.
    T val = storage[size];
    size--;
    return val;
}

template<typename T>
void GenericVector<T>::Delete(u32 index) {
    T * temp = new T[capacity];

    for (int i = 0; i < size - 1; i++) {
        if (i < index)
            temp[i] = storage[i];
        else if (i >= index)
            temp[i] = storage[i + 1];
    }
    size--;

    delete[] storage;
    storage = temp;
}

// Remove all occurences of 'value' from Dynamic Array
// Not O(n) AT ALL - Maybe O(n^2)?
template<typename T>
void GenericVector<T>::Remove(T value) {
    for (int i = 0; i < size; i++) {
        if (storage[i] == value) {
            Delete(i);
            i--;
            /* We need to i-- because our array shrinks as we work on it
            WITHOUT:
            i=0, v=[0, 2, 2, 1]	storage[0] != 2, no Delete(0)
            i=1, v=[0, 2, 2, 1]	storage[1] == 2, Delete(1)
            i=2, v=[0, 2, 1]	storage[2] != 1, no Delete(2)*****
            i=3, v=[0, 2, 1]	storage[3] != 2, no Delete(3)
            WITH:
            i=0, v=[0, 2, 2, 1]	storage[0] != 2, no Delete(0)
            i=1, v=[0, 2, 2, 1]	storage[1] == 2, Delete(1); i=0;
            i=1, v=[0, 2, 1]	storage[1] == 2, Delete(1); i=0;
            i=1, v=[0, 1]		storage[1] != 2, no Delete(1)
            */
        }
    }
}

// Linear Search array, return the first found index of value, if not found return -1
template<typename T>
u32 GenericVector<T>::Find(T value) {
    for (int i = 0; i < size; i++) {
        if (storage[i] == value)
            return i;
    }
    return -1;
}

// INT ONLY
template<>
int GenericVector<int>::BinarySearch(int value) {
    int max = size;
    int middle = max / 2;
    while ((middle >= 0) | (middle <= size))
    {
        if (value == storage[middle])
            return middle;
        else if (value > storage[middle]) {
            middle = ((max + middle) / 2);
        }
        else if (value < storage[middle]) {
            max = middle;
            middle = max / 2;
        }
    }
    printf("ERROR: Value not found in GenericVector!");
    return -1;

}

template<>
int GenericVector<int>::BinarySearchR(int value, int min, int max) {
    if (max < min)
        return -1; // value not in array

    int midpoint = ((max + min) / 2);

    if (storage[midpoint] < value)
        BinarySearchR(value, (midpoint + 1), max);
    else if (storage[midpoint] > value)
        BinarySearchR(value, min, midpoint - 1);
    else
        return midpoint;
}

/*********************Private*****************************/
template<typename T>
void GenericVector<T>::Resize() {
    // TODO: Array only Grows, doesn't shrink
    capacity = capacity * 2;
    T * temp = new T[capacity];

    for (int i = 0; i < size; i++)
        temp[i] = storage[i];

    delete[] storage;
    storage = temp;
}
