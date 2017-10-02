#include "stdafx.h"

#pragma once

#ifndef UNIONFIND_H
#define UNIONFIND_H

struct Item {
    int parent;
    char value;
    int height;
};

class UnionFind {
private:
    std::vector<Item> items;

public:
    UnionFind() {};
    ~UnionFind() {};

    UnionFind(std::vector<char> input_vector) {
        for (int i = 0; i < input_vector.size(); ++i) {
            Item item;
            item.parent = i;
            item.value = input_vector.at(i);
            item.height = 1;
            items.push_back(item);
        }
    };

    void AddItem(int parent, char value);

    int Find(Item item);
    void Union(int a, int b);
};

void UnionFind::AddItem(int parent, char value) {
    Item temp;
    temp.parent = parent;
    temp.value = value;
    temp.height = 1;
    items.push_back(temp);
}


// returns the index of the requested value
int UnionFind::Find(Item item) {
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

void UnionFind::Union(int a, int b) {
    Item A = items.at(a);
    Item B = items.at(b);
}


#endif
