#include "stdafx.h"

#pragma once

#ifndef PRINTERS_H
#define PRINTERS_H

// https://stackoverflow.com/q/22482689

template <typename T>
void print_container(const T&);

template <typename T>
void print(const std::vector<T>& v) { print_container(v); }

template <typename T>
void print(const std::list<T>& l) { print_container(l); }

template <typename T>
void print(const T& e) { cout << e; }

template <typename T>
void print_container(const T& c) {
    cout << "[";
    bool isFirst = true;
    for (const auto& e : c) {
        if (isFirst) isFirst = false;
        else cout << ", ";
        print(e);
    }
    cout << "]\n";
}

/* My Implementation
void print_vec(std::vector<int> *to_print) {
    cout << "[";
    bool isFirst = true;
    for (int i = 0; i < to_print->size(); ++i) {
        printf("%i, ", to_print->at(i));
    }
    cout << "]\n";
}
*/

#endif