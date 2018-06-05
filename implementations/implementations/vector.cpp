#include "stdafx.h"
#include "vector.h"

// NOTE: All the if (size < capacity / 3) checks could probably be optimized
//      into modulos with respect to powers of two.  Though, this only affects 
//      operations that enact multiple size changes like 'Remove()'

/******************Constructor***************************/
template<typename T>
Vector<T>::Vector() {
	size = 0;
	capacity = 2;
	storage = new T[capacity];
    //storage = malloc(sizeof(T) * capacity);

    // TODO: Add an allocating overload Vector<T>(input_size)
    //          that initializes zeros with that range
}
template class Vector<int>;

template<typename T>
Vector<T>::~Vector() {
    delete[] storage;
}

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
        // Grow the vector's storage capacity.
        // NOTE: Inlined because we have to do the same operation for Insert anyway
        capacity = capacity * 2;
        T* new_storage = new T[capacity];
        
        // Copy the old values
        for (u32 i = 0; i < size; ++i)
            new_storage[i] = storage[i];
        
        // Cleanup
        delete[] storage;
        storage = new_storage;

		storage[size] = value;
	}
	size++;
}

template<typename T>
void Vector<T>::Insert(u32 index, T value) {
    if (index < 0 || index > size) {
        // TODO: Do an assertion here instead.
        fprintf(stderr, "Attempted to insert at invalid index.");
    }
    else 
    {
        size++;
        // If we've hit the vector's capacity, we have to grow while we insert.
        if (size == capacity)
        {
            capacity = capacity * 2;
		    T * new_storage = new T[capacity];
		    for (u32 i = 0; i < size + 1; ++i) {
			    if (i < index)
				    new_storage[i] = storage[i];
			    else if (i == index)
				    new_storage[i] = value;
			    else
				    new_storage[i] = storage[i - 1];
		    }
		    delete[] storage;
		    storage = new_storage;
        }
        else
        {
            // Iterate over the array backwards, shift everything right.
            // This method avoids temp values.
            for (u32 i = size; i > index; --i) {
                storage[i] = storage[i - 1];
            }
            // Overwrite the duplicate at storage[index], now at [index + 1]
            storage[index] = value;
        }
	}
}

template<typename T> 
T Vector<T>::Pop() {
    T val = storage[size - 1];
    // NULL assignment is unneccessary, just moving the size counter would be fine.
    storage[size - 1] = NULL;
	size--;
    // NOTE: Capacity shrinks in half if the number of actual stored items is
    //        less than 1/3rd capacity. Less performant but saves space.  
    if (size < (capacity / 3)) {
        capacity = capacity / 2;
        T * new_storage = new T[capacity];

        for (u32 i = 0; i < size; ++i)
            new_storage[i] = storage[i];

        delete[] storage;        
        storage = new_storage;
    }

	return val;
}

template<typename T>
T Vector<T>::Delete(u32 index) {
    if (index < 0 || index > size - 1) 
    {
        printf("ERROR: Attempted to delete from invalid index.");
        return NULL;
    }
    else 
    {
        T val = storage[index];
        size--;
        // Handle Shrinking Case
        if (size <= capacity / 3) 
        {
            T * new_storage = new T[capacity / 2];
            for (u32 i = 0; i < size; ++i) 
            {
                // Elements below i will be copied
                if (i < index)
                    new_storage[i] = storage[i];
                // Elements at or after i will be pulled down one.
                // We can do this because we shrunk size earlier, otherwise
                // we'd get an Array Index Out of Bounds error.
                else
                    new_storage[i] = storage[i + 1];

            }
            delete[] storage;
            storage = new_storage;
        }
        // Handle In-Place Case
        else 
        {
            // Shift everything left.
            for (u32 i = index; i < size; ++i) 
                storage[i] = storage[i + 1];
            storage[size] = NULL;
        }
        return val;
    }
}

// Remove all occurences of 'value' from Dynamic Array
// O(n) - Will copy down the next value in line but still iterate over the whole
//          array.  
template<typename T>
u32 Vector<T>::Remove(T value) {
    u32 num_removed = 0;
#if 1
    T* result = new T[capacity];

    u32 _new = 0;
    u32 _old = 0;
    while (_old < size) {
        if (storage[_old] != value) 
        {
            result[_new] = storage[_old];
            _new++;
        }
        _old++;
    }
    num_removed = _old - _new;
    size = size - num_removed;

    delete[] storage;
    storage = result;


#else    
    // TODO: In-place doesn't work.
    while (i < size) {
        if (storage[i] == value) {
            j = i + 1;
            while (j < size) {
                if (storage[j] != value) {
                    storage[i] = storage[j];
                    i++, j++;
                }
                else { // storage[j] == value
                    
                }
                total_removed++;
            }
        }
        else {
            i++;
        }

	}
    size -= total_removed;
    if (size < capacity / 3) {
        // TODO: Shrink
        // This is a tradeoff, we can shrink either way and get O(n) with extra space.
        // Or we can do this double loop and sometimes get O(n+n/2) aka O(n)
    }
#endif
    return num_removed;
}

// Linear Search:
//  return the first found index of value. if not found return -1
template<typename T>
int Vector<T>::Find(T value) {
	for (int i = 0; i < size; i++) {
		if (storage[i] == value) 
			return i;
	}
    // TODO: Assert Value Not Found
    fprintf(stderr, "Value not found in Array!\n");
    return -1;
}

template<>
int Vector<int>::BinarySearch(int value) {
    // WARN(6/4/18): I don't think this handles unsorted vectors.
    u32 max = size;
    u32 middle = max / 2;
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



#pragma region OLD - 5/30/17 (Non-template version?)
/*
//*****************Constructor***************************
Vector::Vector() {
    size = 0;
    capacity = 2;
    storage = new int[capacity]();

    // Write intial values to 0
    //for (int i = 0; i < capacity; i++)
    //	storage[i] = 0;
}

Vector::Vector(int initialSize) {
    size = 0;
    capacity = initialSize;
    storage = new int[capacity]();
}

//*********************Public*****************************
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
            * / 
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

int Vector::BinarySearch(int value) {
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

int Vector::BinarySearchR(int value) {
    return 0;
}

//********************Private*****************************
void Vector::Resize() {
    // TODO: Array only Grows, doesn't shrink
    capacity = capacity * 2;
    int * temp = new int[capacity];

    for (int i = 0; i < size; i++)
        temp[i] = storage[i];

    delete[] storage;
    storage = temp;
}
*/
#pragma endregion