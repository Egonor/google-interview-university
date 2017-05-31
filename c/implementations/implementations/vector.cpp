#include "stdafx.h"
#include "vector.h"


/******************Constructor***************************/
template<typename T>
Vector<T>::Vector() {
	size = 0;
	capacity = 2;
	storage = new T[capacity];

	// Write intial values to 0
    // *** THIS WOULD NEED TO BE ADDED TO RESIZE TOO
	//for (int i = 0; i < capacity; i++)
	//	storage[i] = T();
}
template class Vector<int>;

/*********************Public*****************************/
template<typename T>
u32 Vector<T>::Size() {
	return size;
}

template<typename T>
u32 Vector<T>::Capacity() {
	return capacity;
}

template<typename T>
bool Vector<T>::isEmpty() {
	if (size == 0) 
		return true; 
	else 
		return false; 
}

template<typename T>
u32 Vector<T>::Access(u32 index) {
	if (index <= size && index >= 0)
		return storage[index];
	else
		throw std::out_of_range("Tried to Access() invalid index.");
}

template<typename T>
void Vector<T>::Push(T value) {
	if (size < capacity)
		storage[size] = value;
	else {
		Resize();
		storage[size] = value;
	}
	size++;
}

template<typename T>
void Vector<T>::Insert(u32 index, T value) {
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
T Vector<T>::Pop() {
	// TODO: Resize by half if size <= cap / 2
	// Value still exists, the tracker for Size is just moved ahead of it.
	T val = storage[size];
	size--;
	return val;
}

template<typename T>
void Vector<T>::Delete(u32 index) {
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
void Vector<T>::Remove(T value) {
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
u32 Vector<T>::Find(T value) {
	for (int i = 0; i < size; i++) {
		if (storage[i] == value) 
			return i;
	}
	return -1;
}

// INT ONLY
template<>
int Vector<int>::BinarySearch(int value) {
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
    printf("ERROR: Value not found in vector!");
    return -1;
    
}

template<>
int Vector<int>::BinarySearchR(int value, int min, int max) {
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
void Vector<T>::Resize() {
	// TODO: Array only Grows, doesn't shrink
	capacity = capacity * 2;
	T * temp = new T[capacity];

	for (int i = 0; i < size; i++)
		temp[i] = storage[i];

	delete [] storage;
	storage = temp;
}