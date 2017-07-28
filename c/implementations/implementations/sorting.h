#pragma once

#ifndef SORTING_H
#define SORTING_H

void InsertionSort(std::vector<int> * to_sort);
void BubbleSort(std::vector<int> * to_sort);
void SelectionSort(std::vector<int> * to_sort);

void QuickSort(std::vector<int> *to_sort, int min, int max);
void QuickSort(int *to_sort, int min, int max);

std::vector<int> MergeSort(std::vector<int> to_sort);



#endif
