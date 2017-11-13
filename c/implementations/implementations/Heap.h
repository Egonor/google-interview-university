#include "stdafx.h"
#pragma once

#ifndef HEAP_H
#define HEAP_H

// TODO: Allow changing values/priorities.

// Heaps are an array based data-structure that simulates a tree.
// They can be defined as Max Heaps (max value at root) or Min Heaps.

// HeapSort Complexity:
//  Time:   O(n log n) where log n == height of tree
//  Space:  O(1) 

struct HeapItem {
    // We want to seperate an item's priority from it's index:
    //  1) What if there's duplicate priorities?
    //      (A) Nothing happens during comparisons, we only use < and >.
    //  2) What if we have an input array without priority information?
    //      (A) We duplicate the value and use it as the priority.
    //          It's not space efficient but it simplifies SiftUp/SiftDown
    //      (*) We also can't do an in-place BuildHeap() with seperate priorities
    //          because we have to copy EVERY value's priority (see BuildHeap())
    
    int priority;
    int value;
};


class Heap {
private:
    bool min_heap = false;

    // Flag to convert max_heap functions to min_heap
    std::vector<HeapItem> items;

    inline void Swap(int indexA, int indexB) {
        HeapItem temp = items.at(indexA);
        items.at(indexA) = items.at(indexB);
        items.at(indexB) = temp;
    }    

    inline int ParentIndex(int index) { return (int)std::floor((index - 1) / 2); }
    inline int LeftChildIndex(int index)  { return (2 * index) + 1; } // +1 for 0 based arrays
    inline int RightChildIndex(int index) { return (2 * index) + 2; }
       
    inline void SiftUp(int index);
    inline void SiftDown(int index);

    void BuildHeap() {
        // We cannot BuildHeap in place with priorities.
        // NOTE: This ignores leaf nodes because they are already "Sifted Down".
        for (int i = ((int)items.size() - 1) / 2; i >= 0; i--) {
            SiftDown(i);
        }
    }

public:
    // Constructor: Empty Heap
    Heap(bool is_min_heap) {
        min_heap = is_min_heap;
        items = std::vector<HeapItem>();

        //printf("size: %llu\n", storage->size());        // llu = u64        
    };
    Heap(bool is_min_heap, const std::vector<int> *values);    
    Heap(bool is_min_heap, const std::vector<int> *values, 
                           const std::vector<int> *priorities);
    ~Heap() {};

    int  GetSize()  { return (int)items.size(); }
    bool IsEmpty()  { return items.size() == 0; }
    int  GetTop() {
        if (items.size() == 0) {
            printf("ERROR: Heap is empty! Cannot read from empty Heap\n");
            return -1; // NOTE: This won't actually Error out.
        }
        else
            return items.at(0).value;
    }    
    std::vector<int> GetItems() {
        std::vector<int> result;
        for (int i = 0; i < items.size(); i++) {
            result.push_back(items.at(i).value);
        }
        return result;
    }

    void Insert(int value);                 // Insert with default priority
    void Insert(int value, int priority);   // Insert with set priority
    int Extract();                          // Pop Min/Max
    void Remove(int index);
};

#endif