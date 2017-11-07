#include "stdafx.h"
#pragma once

#ifndef GRAPH_H
#define GRAPH_H


// Used to return Parent Tree & Distances
struct ShortestPath {
    int source;
    std::vector<int> distances;
    std::vector<int> parents;
};


struct graph_edge {    
    char dest_name;     // Just for readability
    int index_from;     // NOTE: This is only used for Kruskal to do Find()
    int index_to;
    int weight = 0;    
};
// For std::priority_queue to make a min_heap
// std::priority_queue<int, std::vector<int>, comparator> min_heap;
struct comparator {
    bool operator()(const std::pair<int, int> i, const std::pair<int, int> j) {
        return i.second > j.second;
    }
};

inline bool WeightComparator(const graph_edge& e1, const graph_edge& e2) {
    return e1.weight < e2.weight;
}

struct graph_node {
    int index;          //
    char name;          // Additional data for actual operations.
    //std::string name;
    
    int indegree = 0;    
    int dfs_started = -1;
    int dfs_finished = -1;

    // Essentially a pointer to other nodes by index.
    // In an undirected graph, these will be duplicated
    //  in the nodes vector.
    std::list<graph_edge> edges;   
};
/*
static bool StartedComparator(const graph_node& n1, const graph_node& n2) {
    return n1.dfs_started < n2.dfs_started;
}*/

inline bool FinishedComparator(const graph_node& n1, const graph_node& n2) {
    return n1.dfs_finished > n2.dfs_finished;
}

class GraphList {
private:
    std::vector<graph_node> nodes;
    
    bool validate(int node);
    void DFSr(int n, std::vector<bool>& seen_array, std::vector<graph_node*> *tree,
                int* start_counter, int* finish_counter);

public:
    // Graphs are assumed directed unless specified otherwise.
    // This property causes AddEdge to duplicate between two nodes: A->B, B->A
    bool directed = true;

    void PrintGraph();              // 0(n + e)
    char GetName(int node_index);   // 0(1)
    int GetIndex(char name);        // 0(n)

    void AddNode(char name);        // 0(n) amortized (for resizing vector?)
    //void AddNode(graph_node g);
    
    // 0(e) (does duplicate checking increase the complexity?)
    void AddEdge(char node_from, char node_to, int weight);


    std::vector<char> GraphList::TopologicalSort();
    std::vector<graph_edge> GraphList::MinimumSpanningTree();

    void BFS(int start_node);
    std::vector<graph_node*> DFS(int start_node);
    // Overloaded DFS for searching with an input order (Strongly Connected Components.)
    std::vector<graph_node*> DFS(int start_node, std::vector<graph_node*> *dfs_order);

    // Strongly Connected Components
    GraphList MakeReverseGraph();
    void StronglyConnectedComponents();

    // Returns a Shortest Path Tree (with indexes to parents)
    void Scan(int node_index, std::vector<int>& distances, std::vector<int>& parents);
    ShortestPath Dijkstra(int source_node);
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