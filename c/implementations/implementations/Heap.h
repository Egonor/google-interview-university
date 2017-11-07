#include "stdafx.h"

#pragma once

#ifndef HEAP_H
#define HEAP_H

// Heaps are an array based data-structure that simulates a tree.
// They can be defined as Max Heaps (max value at root) or Min Heaps.

// HeapSort Complexity:
//  Time:   O(n log n) where log n == height of tree
//  Space:  O(1)

struct HeapItem {
    // We want to seperate an item's priority from it's index:
    //  1) What if there's duplicate priorities?
    //  2) What if our priority is very large? (i.e. INT_MAX/Infinity for Dijkstra)
    //      * We don't want to make a massive array because an item's priority
    //          should logically be == INT_MAX

    //  3) What if we have an input array without priority information?
    //      * Default to 0, if no priority is specified use the value as priority 
    //  TODO; Set priority when adding items based on bool min_heap
    
    unsigned int priority;
    int value;
};


class Heap {
private:
    bool min_heap = false;
    int heap_size; // Is this necessary?
    //int max_size;
    // Flag to convert max_heap functions to min_heap
    std::vector<HeapItem> items;

    inline int ParentIndex(int index)     { return std::floor(index - 1 / 2); }
    inline int LeftChildIndex(int index)  { return (2 * index) + 1; } // +1 for 0 based arrays
    inline int RightChildIndex(int index) { return (2 * index) + 2; }

    inline void Swap(int indexA, int indexB) {
        // Doesn't fix Heap, just swaps values
        HeapItem temp = items.at(indexA);
        items.at(indexA) = items.at(indexB);
        items.at(indexB) = temp;
    }    
       
    void SiftUp(int index);
    void SiftDown(int index);

    // This ignores leaf nodes? does it actually create HeapItems? Nah, TODO
    void BuildHeap(std::vector<int> *input_array) {
        for (int i = ((int)input_array->size() - 1) / 2; i >= 0; i--) {
            SiftDown(i);
        }
    }

public:
    Heap(bool is_min_heap) {
        min_heap = is_min_heap;
        heap_size = 0; // size = 0;
        items = std::vector<HeapItem>();

        //printf("size: %llu\n", storage->size());        // llu = u64        
    };
    Heap(bool is_min_heap, std::vector<int> *values);
    Heap(bool is_min_heap, std::vector<int> *values, std::vector<int> *priorities);

    ~Heap() {};

    int  GetSize()  { return heap_size; }
    bool IsEmpty()  { return heap_size == 0; }

    int GetMax() {
        if (heap_size == 0) {
            printf("ERROR: Heap is empty! Cannot read from empty Heap\n");
            return -1; // NOTE: error (storage[0] not set)
        }
        else
            return items.at(0).value;
    }
    
    void Insert(int value);                 // Insert with default priority
    void Insert(int value, int priority);   // Insert with set priority
    int Extract();                          // Pop Min/Max

    void Remove(int index) {
        items.at(index).priority = INT_MAX;     // Subsitute for "infinity"
        
        SiftUp(index);                          // Move "infinity" to top
        Extract();                              // Pop "infinity" as garbage
    }
    
    
    /*std::vector<int>* Sort() {
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
    }*/

};


/*
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
*/
#endif
Heap::Heap(bool is_min_heap, std::vector<int> *input_array) {
     min_heap = is_min_heap;
     //, int size) variable for safety?
     // converts an existing array to a heap "in place"
     // probably causes some wonky stuff to happen outside (NOT-SAFE)
     // Better to just copy values to a new heap as we "heapify"
     // Or make Heapify() non-reliant on class Heap's code.
     
     for (int i = (input_array->size() / 2) - 1; i > 0; --i) {
         SiftDown(i);
     }
     
     BuildHeap(input_array);

     printf("size: %llu\n", items.size());
     //printf("max_size: %llu\n", items.capacity());
}


// When a new node is inserted, MAINTAIN the heap by raising the inserted node.
inline void Heap::SiftUp(int index)
{   
    // 1) While we're not at the root (no parent to search) // index > 1?
    while (index > 0 && (
                // 2) If in a min_heap, check if node's parent is smaller than node
                (min_heap && items.at(ParentIndex(index)).priority < items.at(index).priority) ||
                // 3) Or if in a max_heap, check if node's parent is larger than node
                (!min_heap && items.at(ParentIndex(index)).priority > items.at(index).priority)
              )
          )
    {
        // 4) If true, swap the values and repeat
        Swap(index, ParentIndex(index));    // Move value up.
        index = ParentIndex(index);
    }
}

inline void Heap::SiftDown(int index) {
    // child holds the index of the value we're currently looking at
    int child;

    // while there is a left child
    for (; LeftChildIndex(index) < items.size(); index = child) {
        // set the target child to the left child
        child = LeftChildIndex(index);

        // if a right child exists as well
        if (child != items.size() - 1) {
            // pick the smaller child in min_heap and the larger child in max heap
            if ((min_heap && items.at(child + 1).priority < items.at(child).priority) ||
                (!min_heap && items.at(child + 1).priority > items.at(child).priority))
                child++;
        }


        // pick the smaller child in min_heap and the larger child in max heap
        if ((min_heap && items.at(child).priority) < items.at(index).priority ||
            (!min_heap && items.at(child).priority > items.at(index).priority))
            // swap the chosen child
            Swap(index, child);
        else
            break;
    }

    /*      SAVE ITEM TO LIMIT PROCESSING ON SWAP()s / ALTERNATE METHOD
    //      This doesn't use the swap function which is weird to me.
    // save the item to sift
    HeapItem temp = items.at(index);
    // child holds the index of the value we're currently looking at
    int child;

    // while there is a left child
    for (; LeftChildIndex(index) < items.size(); index = child) {
        // set the target child to the left child
        child = LeftChildIndex(index);

        // if a right child exists as well
        if (child != items.size() - 1) {
            // pick the smaller child in min_heap and the larger child in max heap00
            if ((min_heap && items.at(child + 1).priority < items.at(child).priority) ||
                (!min_heap && items.at(child + 1).priority > items.at(child).priority))
                child++;
        }

        // This doesn't use the swap function which is weird to me.

        // 
        if ((min_heap && items.at(child).priority) < temp.priority ||
            (!min_heap && items.at(child).priority > temp.priority))
            // lift up the child
            items.at(index) = items.at(child);
        else
            break;
    }
    items.at(index) = temp;
    */
}

void Heap::Insert(int value) {
    HeapItem temp;
    temp.value = value;
    temp.priority = value;

    items.push_back(temp);
    SiftUp(items.size() - 1);
}

void Heap::Insert(int value, int priority) {
    HeapItem temp;
    temp.value = value;
    temp.priority = priority;

    items.push_back(temp);
    //heap_size++;
    SiftUp(items.size() - 1);
}

// Pops top item off Heap (lowest if min_heap) then maintains HEAP property.
int Heap::Extract() {
    // Cannot extract from an empty Heap
    if (items.size() == 0) {
        printf("ERROR: Heap is empty! Cannot Extract() from empty Heap\n");
        return NULL;
    }
    else {
        int result = items.at(0).value;             // Save the top value for later
        items.at(0) = items.at(items.size() - 1);   // Pull up bottom rightmost value
        items.pop_back();                           // Remove duplicate last item
        SiftDown(0);                                // Move original last item down
        return result;
    }
}