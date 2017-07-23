#pragma once

#ifndef SORTING_H
#define SORTING_H

//template <typename T> T* BubbleSort(T *to_sort);

void InsertionSort(std::vector<int> * to_sort);
void BubbleSort(std::vector<int> * to_sort);
void SelectionSort(std::vector<int> * to_sort);










std::vector<int> * QuickSort(std::vector<int> * to_sort);
std::vector<int> Merge(std::vector<int> left, std::vector<int> right);
std::vector<int> MergeSort(std::vector<int> to_sort);



#endif
