#include "stdafx.h"

#pragma once

#ifndef UNIONFIND_H
#define UNIONFIND_H


class UnionFind {
private:
    std::vector<int> parents;
    std::vector<int> size;
    int count;
    //std::vector<T> items;

public:
    //UnionFind() {};

    UnionFind(int n) {
        count = n;
        //parents.reserve(n);
        //size.reserve(n);
        for (int i = 0; i < n; ++i) {
            parents.push_back(i);
            size.push_back(1);
        }
    };

    ~UnionFind() {};

    int Count();

    bool Connected(int a, int b);
    //int Find(Item item);
    int Find(int item_index);
    void Union(int a, int b);
};

int UnionFind::Count() {
    return count;
}

/*
void UnionFind::AddItem(int parent, graph_edge value) {
    Item temp;
    temp.parent = parent;
    temp.value = value;
    temp.height = 1;
    items.push_back(temp);
}
*/


bool UnionFind::Connected(int a, int b) {
    return Find(a) == Find(b);
}

// returns the index of the requested value
int UnionFind::Find(int item_index) {
    if (item_index < 0 || item_index >= parents.size()) {
        printf("Error: attempted to access outside UnionFind's size.");
        return -1;
    }

    // Path Compression
    // Whenever you find, take the values below the root with you and
    //  attach them to the root.
    std::queue<int> to_compress;

    // while we're not at the root
    while (item_index != parents.at(item_index)) {
        // add item to lift to root
        to_compress.push(item_index);
        // go to parent of item
        item_index = parents.at(item_index);
    }

    // loop over items queued to life
    while (!to_compress.empty()) {
        int to_lift = to_compress.front();
        parents.at(to_lift) = item_index;
        size.at(to_lift) = 2;
        to_compress.pop();
    }

    return item_index;
}

void UnionFind::Union(int a, int b) {
    // Weighted Union
    // Connect smaller tree to larger tree, add the height of the lower tree
    // Find will compress the nodes over time (amortized)
    // Sets start at size 1 and ideally should never be greater than 2.
    int root_a = Find(a);
    int root_b = Find(b);
    if (root_a == root_b) return;

    if (size.at(root_a) < size.at(root_b)) {
        parents.at(root_a) = root_b;
        size.at(root_b) += size.at(root_a);
        // Size is bjorked but implemented as I first pseduocoded it...
        // then confirmed as correct by Sedgewick (Algorithms 4th Ed.)
        // To do heights we'd probably have to adjust at Find().
    }
    else {
        parents.at(root_b) = root_a;
        size.at(root_a) = 1 + root_b;
        size.at(root_a) += root_b;
    }
    count--;
}


#endif
