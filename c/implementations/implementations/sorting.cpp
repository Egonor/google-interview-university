#include "stdafx.h"
#include "sorting.h"


void Swap(std::vector<int> *v, int indexA, int indexB) {
    //int to_swap = (*storage)[index_to_swap];
    //(* storage)[parent_index] = (* storage)[index];
    //(* storage)[index] = to_swap;

    int temp = v->at(indexA);
    v->at(indexA) = v->at(indexB);
    v->at(indexB) = temp;
}


// O(n^2)? actually think it's O(n log n)
// *Can do a binary search (instead of pairwise swaps) to find insert location.
// ** Doesn't decrease O() because you'd still have to shift array on insert.
void InsertionSort(std::vector<int> * to_sort) {
    // For every value in the array...
    for (int forward = 1; forward < to_sort->size(); ++forward) {
        int backward = forward;
        // ...we need to check if it's less than it's left element.
        while (backward > 0 && to_sort->at(backward) < to_sort->at(backward - 1)) {
            Swap(to_sort, backward, backward - 1);
            // check the next left element
backward--;
        }
    }
}

// O(n^2)
void BubbleSort(std::vector<int> * to_sort) {
    for (int i = (int)to_sort->size() - 1; i > 0; --i) {
        for (int j = 0; j < i; ++j) {
            if (to_sort->at(j) > to_sort->at(j + 1))
                Swap(to_sort, j, j + 1);
        }
    }
}

// O(n^2)? actually think it's O(n log n)
void SelectionSort(std::vector<int> * to_sort) {
    for (int i = 0; i < to_sort->size(); ++i) {
        int smallest_index = i;
        for (int k = i + 1; k < to_sort->size(); ++k) {
            if (to_sort->at(k) < to_sort->at(smallest_index))
                smallest_index = k;
        }
        if (smallest_index != i) {
            Swap(to_sort, smallest_index, i);
        }
    }
}

int PartitionA(std::vector<int> *to_sort, int left, int right) {
    // Partitioning
    while (left != right) {
        while (to_sort->at(left) < to_sort->at(right) && left != right) {
            left++;
        }
        Swap(to_sort, left, right);
        while (to_sort->at(left) < to_sort->at(right) && left != right) {
            right--;
        }
        Swap(to_sort, left, right);
    }
    return left;
};

int PartitionB(std::vector<int> *to_sort, int left, int right) {
    int pivot = to_sort->at(left);

    while (left != right) {
        while (to_sort->at(right) > pivot && left != right) {
            right--;
        }
        to_sort->at(left) = to_sort->at(right);
        while (to_sort->at(left) < pivot && left != right) {
            left++;
        }
        to_sort->at(right) = to_sort->at(left);
    }
    to_sort->at(left) = pivot;
    return left;
}

int PartitionC(std::vector<int> *to_sort, int left, int right) {
    int pivot = to_sort->at(left);

    bool current_right = true;
    while (left != right) {
        if (current_right) {
            if (to_sort->at(right) < pivot) {
                to_sort->at(left) = to_sort->at(right);
                left++;
                current_right = false;
            }
            else
                right--;
        }
        else if (!current_right) {
            if (to_sort->at(left) > pivot) {
                to_sort->at(right) = to_sort->at(left);
                right--;
                current_right = true;
            }
            else
                left++;
        }
    }
    to_sort->at(left) = pivot; // left == right
    return left;
}


// Average = 0(n log n), Worst = O(n^2)
// Default min == 0, max == (vec->size() - 1)
void QuickSort(std::vector<int> *to_sort, int min, int max) {
    // TODO: Random Shuffle and setup QuickSort to just take an array as param.

    if (min < max) {
        int pivot_index = PartitionA(to_sort, min, max);
        //int pivot_index = PartitionB(to_sort, min, max);
        //int pivot_index = PartitionC(to_sort, min, max);
        QuickSort(to_sort, min, pivot_index - 1);
        QuickSort(to_sort, pivot_index + 1, max);
    }
}



void QuickSort(int *to_sort, int min, int max) {
    if (min < max) {
        // Partition
        int left = min;
        int right = max;

        int pivot = to_sort[left];

        bool current_right = true;
        while (left != right) {
            if (current_right) {
                if (to_sort[right] < pivot) {
                    to_sort[left] = to_sort[right];
                    left++;
                    current_right = false;
                }
                else
                    right--;
            }
            else if (!current_right) {
                if (to_sort[left] > pivot) {
                    to_sort[right] = to_sort[left];
                    right--;
                    current_right = true;
                }
                else
                    left++;
            }
        }

        to_sort[left] = pivot; // left == right

        QuickSort(to_sort, min, left - 1);
        QuickSort(to_sort, right + 1, max);
    }
}




// 0(n log n)
std::vector<int> Merge(std::vector<int> left, std::vector<int> right) {
    // Assuming two sorted arrays, merge them together

    std::vector<int> done;

    int l = 0;      // Two finger method, l tracks left array and r...
    int r = 0;      
    while (l < left.size() || r < right.size()) {
        if (l == left.size()) {
            done.push_back(right.at(r));
            r++;
        }
        else if (r == right.size()) {
            done.push_back(left.at(l));
            l++;
        }
        else if (left.at(l) < right.at(r)) {
            done.push_back(left.at(l));
            l++;
        }
        else {
            done.push_back(right.at(r));
            r++;
        }
    }
    return done;

}

// int arr[to_sort.size()];
// MSVC DOESN'T LIKE NON-CONSTANT ARRAY ARGUMENTS/SIZES
// const doesn't work because...constants aren't "constant" in c...
// they're just read-only.
// Probably has to do with array sizes being determined at compile-time.
// unless you allocate and free it yourself

// THE C++ STD documentation WORD SOUP IS FREAKING INSUFFERABLE
std::vector<int> MergeSort(std::vector<int> to_sort) {
    if (to_sort.size() >= 2) {
        std::vector<int>::const_iterator begin = to_sort.begin();
        std::vector<int>::const_iterator mid = to_sort.begin() + (to_sort.size() / 2);
        std::vector<int>::const_iterator last = to_sort.begin() + to_sort.size();

        // end == to_sort.size()

        std::vector<int> left_half(begin, mid);
        std::vector<int> right_half(mid, last);

        left_half = MergeSort(left_half);
        right_half = MergeSort(right_half);
        return Merge(left_half, right_half);
    }
    else {
        return to_sort;
    }
}


