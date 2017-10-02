#include "stdafx.h"

#pragma once

#ifndef UNIONFIND_H
#define UNIONFIND_H

template <typename T>
struct Item {
    int parent;
    T value;
    int height;
};

template <class T>
class UnionFind {
private:
    std::vector<typename Item> items;

public:
    template <class t>
    UnionFind(std::vector<T> input_vector) {
        for (int i = 0; i < input_vector.size(); ++i) {
            Item item;
            item.parent = i;
            item.value = input_vector.at(i);
            item.height = 1;
            items.push_back(item);
        }
    };

    ~UnionFind() {

    };


    int Find(typename Item item);
    void Union(typename Item a, typename Item b);
};


// returns the index of the requested value
template <typename T>
int UnionFind::Find(typename Item item) {
    std::vector<int> to_move;

    int current = item.parent;

    while (items.at(current).parent != current) {
        to_move.push_back(current);
        current = items.at(current).parent;
    }

    // Raising the parents to the top of the set improves
    // the amortized runtime to _____0(p log* n)_____
    for (int i = 0; i < to_move.size(); ++i) {
        items.at(to_move.at(i)).parent = current;
        items.at(to_move.at(i)).height = 2;
    }

    return current;
}

template <typename T>
void UnionFind::Union(Item a, Item b) {

}


#endif
