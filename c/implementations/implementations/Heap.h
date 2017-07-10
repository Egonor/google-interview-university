#include "stdafx.h"

#pragma once

#ifndef HEAP_H
#define HEAP_H

class Heap {
private:
    int size;
    int max_size;
    std::vector<int> *storage;

    int Parent(int index) {
        return index / 2;
    }

    int LeftChild(int index) {
        return (2 * index) + 1; // +1 is necessary for 0 based array
    }

    int RightChild(int index) {
        return (2 * index) + 2; 
    }

    void Swap(int indexA, int indexB) {
        //int to_swap = (*storage)[index_to_swap];
        //(* storage)[parent_index] = (* storage)[index];
        //(* storage)[index] = to_swap;
        
        int temp = storage->at(indexA);
        storage->at(indexA) = storage->at(indexB);
        storage->at(indexB) = temp;
    }    
       
    void SiftUp(int index) {
        while (index > 1 &&                                // while index is not root
            storage[index] > storage[Parent(index)]) {  // while index > parent
            Swap(index, Parent(index));                     // swap values at A[i] and A[Parent(i)]
            index = Parent(index);
        }
    }

    void SiftDown(int index) {
        // We're trying to find the max of index and it's two children.
        int max_index = index;                  // maintain the current max
        int left_index = LeftChild(index);
        if (left_index <= size &&               // left_index exists in heap
            storage->at(left_index) > storage->at(max_index)) { // left child is > current max
            max_index = left_index;             // set left child to current max
        }
        int right_index = RightChild(index);
        if (right_index <= size &&              // right_index exists in heap
            storage->at(right_index) > storage->at(max_index)) { // right child is > current max
            max_index = right_index;            // right child is new current max
        }
        if (index != max_index) {               // one of the children is >, not a max-heap
            Swap(index, max_index);             // move max to parent
            SiftDown(max_index);                // max_index now holds the swapped index
                                                // continue sifting down on the initial index
        }

    }

    void BuildHeap(std::vector<int> *input_array) {
        for (int i = ((int)input_array->size() - 1) / 2; i >= 0; i--) {
            SiftDown(i);
        }
    }

public:
    Heap() {
        storage = new std::vector<int>();
        size = (int)storage->size(); // size = 0;
        max_size = (int)storage->capacity();

        printf("size: %llu\n", storage->size());        // llu = u64
        printf("max_size: %llu\n", storage->capacity());
    };

    Heap(std::vector<int> *input_array) { //, int size) variable for safety?
        // converts an existing array to a heap "in place"
        // probably causes some wonky stuff to happen outside (NOT-SAFE)
        // Better to just copy values to a new heap as we "heapify"
        // Or make Heapify() non-reliant on class Heap's code.
        size = (int)input_array->size();
        max_size = (int)input_array->capacity();
        storage = input_array;
        BuildHeap(input_array);

        printf("size: %llu\n", storage->size());
        printf("max_size: %llu\n", storage->capacity());
    }
        
    ~Heap() { 
        delete storage;
    };

    int Heap::GetSize() {
        return size;
    }

    bool IsEmpty() {
        return size == 0;
    }

    int GetMax() {
        if (size == 0) {
            printf("ERROR: Heap is empty! Cannot read from empty Heap\n");
            return -1; // NOTE: error (storage[0] not set)
        }
        else
            return storage->at(0);
    }
    
    void Insert(int value) {
        if (size == max_size) {
            // ERROR - should never happen when using std::vector
            printf("ERROR: Heap is full! Cannot Insert into full Heap\n");
        }
        else {
            size++;
            // storage->push_back(value); Should work too.
            storage->at(size) = value;
            SiftUp(size);
        }
    }

    int ExtractMax() {
        // pseudocode
        if (size == 0) {
            printf("ERROR: Heap is empty! Cannot ExtractMax() from empty Heap\n");
            return -1;
        }
        else {
            int result = storage->at(0);            // save popped for later
            size--;
            storage->at(0) = storage->at(size); // pull up bottom rightmost value
            SiftDown(0);
            return result;
        }
    }

    void Remove(int index) {
        storage->at(index) = INT_MAX;           // Subsitute for "infinity"
        SiftUp(index);                          // Move "infinity" to top
        ExtractMax();                           // Pop "infinity" as garbage
    }
    
    std::vector<int>* Sort() {
        //BuildHeap(input_array);
        int heap_size = size;
        while (heap_size > 0) {
            Swap(0, heap_size);
            heap_size--;
            SiftDown(0);
        }
        return storage;
        // TODO: Leaves an invalid MaxHeap. Find a better way to terminate it
        //       Newly Inserted items will probably take O(log n + 1) time.
        //       ExtractMax() will pull smallest value: storage[0], then
        //       rebuild Heap because SiftDown() is recursive.
    }


};


// Not In-place
Heap* Sort(std::vector<int> *input_array) {
    Heap* sorted = new Heap();
    for (int i = 0; i < input_array->size(); ++i) {
        sorted->Insert(input_array->at(i));
    }
    return sorted;
}

std::vector<int>* HeapSort(std::vector<int> *input_array) {
    printf("ERROR: This function is broken, must access private functions");
    int heap_size = (int)input_array->size();
    while (heap_size > 0) {
        //Swap(0, heap_size;        ***NOT PUBLIC*** 
        heap_size--;
        //Heap::SiftDown(0);        ***NOT PUBLIC***
    }
    return input_array;
}

// NOTE: MIT 6.006's max_heapify is similar to SiftDown
#endif