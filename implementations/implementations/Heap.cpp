#include "stdafx.h"
#include "Heap.h"

Heap::Heap(bool is_min_heap, const std::vector<int> *values) {

    min_heap = is_min_heap;

    for (int i = 0; i < values->size(); i++) {
        HeapItem temp;
        temp.value = values->at(i);
        temp.priority = temp.value;
        items.push_back(temp);
    }

    BuildHeap();
}
Heap::Heap(bool is_min_heap, const std::vector<int> *values, const std::vector<int> *priorities) {
    if (values->size() != priorities->size()) {
        printf("ERROR: Cannot create Heap! Number of VALUES and PRIORITES is different.");
    }
    else {
        for (int i = 0; i < values->size(); i++) {
            HeapItem temp;
            temp.value = values->at(i);
            temp.priority = priorities->at(i);
            items.push_back(temp);
        }

        BuildHeap();
    }
}

// When a new node is inserted, MAINTAIN the heap by raising the inserted node.
inline void Heap::SiftUp(int index)
{
    int parent = ParentIndex(index);
    // 1) While we're not at the root (no parent to search) // index > 1?
    while (index > 0 && (
        // 2) If in a min_heap, move up if parent is larger than node
        (min_heap && items.at(parent).priority > items.at(index).priority) ||
        // 3) Or if in a max_heap, move up if parent is smaller than node
        (!min_heap && items.at(parent).priority < items.at(index).priority)
        )
        )
    {
        // 4) If true, swap the values and repeat
        Swap(index, parent);    // Move value up.
        index = parent;
        parent = ParentIndex(parent);
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
        if ((min_heap && items.at(child).priority < items.at(index).priority) ||
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
    SiftUp((int)items.size() - 1);
}
void Heap::Insert(int value, int priority) {
    HeapItem temp;
    temp.value = value;
    temp.priority = priority;

    items.push_back(temp);
    SiftUp((int)items.size() - 1);
}

// Pops top item off Heap (lowest if min_heap) then maintains HEAP property.
int Heap::Extract() {
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
void Heap::Remove(int index) {
    if (index >= items.size()) {
        printf("ERROR: Attempted to remove index outside of Heap.");
        return;
    }

    if (min_heap)
        items.at(index).priority = INT_MIN;     // Subsitute for "-infinity"
    else
        items.at(index).priority = INT_MAX;     // Subsitute for "infinity"

    SiftUp(index);                              // Move "infinity" to top
    Extract();                                  // Pop "infinity" as garbage
}

std::vector<int> HeapSort(bool ascending, std::vector<int> *input_vector) {
    // NOTE: This implementation is HORRIBLE for complexity!
    //          - Not in-place
    //          - O(n) input + O(n log n) sifting + O(n) produce output vector
    Heap temp_heap(ascending, input_vector);
    return temp_heap.GetItems();
}