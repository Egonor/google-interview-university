#include "stdafx.h"
#include "vector.h"


/******************Constructor***************************/
Vector::Vector() {
	size = 0;
	capacity = 2;
	storage = new int[capacity]();

	// Write intial values to 0
	//for (int i = 0; i < capacity; i++)
	//	storage[i] = 0;
}

/*********************Public*****************************/
int Vector::Size() {
	return size;
}

int Vector::Capacity() {
	return capacity;
}

bool Vector::isEmpty() {
	if (size == 0) 
		return true; 
	else 
		return false; 
}

int Vector::Access(int index) {
	if (index <= size && index >= 0)
		return storage[index];
	else
		throw std::out_of_range("Tried to Access() invalid index.");
}

void Vector::Push(int value) {
	if (size < capacity)
		storage[size] = value;
	else {
		Resize();
		storage[size] = value;
	}
	size++;
}

void Vector::Insert(int index, int value) {
	// TODO: Handle index == 0 with Prepend() or in here
	if (index > 0) {
		if (size + 1 == capacity)
			Resize();

		int * temp = new int[capacity];

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

int Vector::Pop() {
	// TODO: Resize by half if size <= cap / 2
	// Value still exists, the tracker for Size is just moved ahead of it.
	int val = storage[size];
	size--;
	return val;
}

void Vector::Delete(int index) {
	int * temp = new int[capacity];

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
void Vector::Remove(int value) {
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
int Vector::Find(int value) {
	for (int i = 0; i < size; i++) {
		if (storage[i] == value) 
			return i;
	}
	return -1;
}

/*********************Private*****************************/
void Vector::Resize() {
	// TODO: Array only Grows, doesn't shrink
	capacity = capacity * 2;
	int * temp = new int[capacity];

	for (int i = 0; i < size; i++)
		temp[i] = storage[i];

	delete [] storage;
	storage = temp;
}