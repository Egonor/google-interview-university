#include "stdafx.h"
#pragma once

#ifndef GRAPH_H
#define GRAPH_H

struct graph_edge {    
    int index_to;
    char dest_name;
    int weight = 0;

};
static bool WeightComparator(const graph_edge& e1, const graph_edge& e2) {
    return e1.weight < e2.weight;
}

struct graph_node {
    char name;              // Additional data for actual operations.
    //std::string name;
    int indegree = 0;
    std::list<graph_edge> edges;   // Essentially a pointer to other nodes by index.
                            // In an undirected graph, these will be duplicated
                            //  in the nodes vector.
};


class GraphList {
private:
    std::vector<graph_node> nodes;
    

public:
    // Graphs are assumed directed unless specified otherwise.
    // This property causes AddEdge to duplicate between two nodes: A->B, B->A
    bool directed = true;

    void PrintGraph();              // 0(n + e)
    char GetName(int node_index);   // 0(1)
    int GetIndex(char name);        // 0(n)

    void AddNode(char name);        // 0(n) amortized (for resizing vector?)
    
    // 0(e) (does duplicate checking increase the complexity?)
    void AddEdge(char node_from, char node_to, int weight);


    std::vector<char> GraphList::TopologicalSort();
    void GraphList::MinimumSpanningTree();
};



/* TODO: Adjacency Matrix
class GraphMatrix {
private:
    struct graph_node_m {
        char name;

        std::vector<int> columns;
    };

    std::vector<graph_node_m> rows;

public:
    void AddNode(char name);
    void AddEdge(int from_node, int to_node);

};

void GraphMatrix::AddNode(char name) {
graph_node_m node;
node.name = name;
// TODO: Check for duplicates?
rows.push_back(node);

}

void GraphMatrix::AddEdge(int from_node, int to_node) {
rows.at(from_node).columns.at(to_node) = 1;
}
*/

























#endif