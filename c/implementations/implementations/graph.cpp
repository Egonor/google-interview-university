#include "stdafx.h"
#include "graph.h"
#include "UnionFind.h"

// TODO: Adjacency Map? What about Incidence Matrix?
//       Definitely add to graphs notes.

// TODO: Adjacency Matrix

// TODO: DFS with adjacency list(recursive)
// TODO: DFS with adjacency list(iterative with stack)
// TODO: DFS with adjacency matrix(recursive)
// TODO: DFS with adjacency matrix(iterative with stack)
// TODO: BFS with adjacency list
// TODO: BFS with adjacency matrix

// TODO: single-source shortest path (Dijkstra)
// TODO: minimum spanning tree (Kruskul > Prim)
// TODO: DFS - based algorithms(see Aduni videos above) :
            // check for cycle(needed for topological sort, since we'll check for cycle before starting)
            // count connected components in a graph
            // list strongly connected components
            // check for bipartite graph

// 0(n + e)
void GraphList::PrintGraph() {
    for (int i = 0; i < nodes.size(); ++i) {
        printf("%c: ", nodes.at(i).name);
        for (std::list<graph_edge>::iterator edge_index = nodes.at(i).edges.begin();
             edge_index != nodes.at(i).edges.end(); ++edge_index) {           
            //printf("->%c ", edge_index->dest_name);
            DEBUG_PRINT(("->%c ", edge_index->dest_name));
        }
        printf("\n");
    }
}

// 0(1)
char GraphList::GetName(int node_index) {
    // Get by index?
    return nodes.at(node_index).name;
}

// 0(n)
int GraphList::GetIndex(char node_name) {
    for (int i = 0; i <= this->nodes.size(); ++i) {
        if (this->nodes.at(i).name == node_name) {
            // node found, return current node[i]
            return i;
        }
    }
    // node not found, 
    printf("ERROR: Attempted to get index of node not in graph!\n");
    return -1;
}

// Graph setup
void GraphList::AddNode(char node_name) {
    graph_node g;
    g.name = node_name;
    // TODO: At some point included edge input into newly added nodes?
    //      By default, Nodes have zero edges attached to them.
    //g.edges = edges_to_add;
    nodes.push_back(g);
}

void GraphList::AddEdge(char node_from, char node_to, int weight) {
    // NOTE: Obfuscating the node index (i.e. AddEdge('A', 'B', <weight>)
    //          instead of AddEdge(0, 1, <weight>)... adds to complexity.
    int node_index = GetIndex(node_from);
    int edge_to = GetIndex(node_to);

    if (node_index < 0 || node_index >= nodes.size()) {
        printf("ERROR: Attempted to add edge to a node not in graph.\n");
    }
    else if (edge_to < 0 || edge_to >= nodes.size()) {
        printf("ERROR: Attempted to create edge to nonexistent node.\n");
    }
    else {

        // Scan through edge list of specified node to check for duplicates
        for (std::list<graph_edge>::iterator it = nodes.at(node_index).edges.begin(); 
                it != nodes.at(node_index).edges.end(); ++it) {
            if (it->index_to == edge_to) {
                printf("Error: Edge already found, cannot re-add.\n");
                return;
            }
            /* NOTE: Does std::list<> use a tail pointer?  Is it 0(1) to
            // add a new node to the list or is it 0(e) to check for duplicates?

            // Can we operate on the last node here to reduce complexity?
            if (it == nodes.at(node_index).edges.end()) {
                nodes.at(node_index).edges.push_back(edge_to);
            } */
        }

        // Add edge to graph
        graph_edge new_edge;
        new_edge.index_to = edge_to;
        new_edge.dest_name = GetName(edge_to);  // Complexity increase
        new_edge.weight = weight;
        nodes.at(node_index).edges.push_back(new_edge);

        // NOTE: We can automatically calculate indegrees here when adding an edge.
        //       We'd have to remove/edit the calculation int TopoSort (as it assumes 0)
        //       but it puts the load on graph creation instead of the algorithm.
        // nodes.at(edge_to).indegree += 1;
        
        // In an undirected graph we need to store each edge twice.
        // NOTE: To save space, can use:::::: if (i < j) access as [j, i]
        if (directed != true) {
            graph_edge back_edge;
            back_edge.index_to = node_index;
            back_edge.dest_name = GetName(node_index);
            back_edge.weight = weight;
            nodes.at(edge_to).edges.push_back(back_edge);
            // nodes.at(node_index).indegree += 1;
        }

    }
}

std::vector<char> GraphList::TopologicalSort() {
    // ************************************************************************** 
    // 1) Collect indegrees of graph by looping over every edge and increasing
    //      indegree on its target node by one.
    // 2) Loop over indegrees to add zero-indegrees to a queue
    // 3) Loop over queue to remove nodes in Topo-order
    // 3b) As they're removed, scan the node's edges to decrease indegrees
    // 3c) If the decreased indegree is now zero, add to the queue 
    // **************************************************************************
    printf("Topological Sort: ");
    // Output list for usage
    std::vector<char> sorted;

    // Calculate indegrees of Graph: 0(n + e)
    for (int node_index = 0; node_index < nodes.size(); ++node_index) {
        for (std::list<graph_edge>::iterator edge_index = nodes.at(node_index).edges.begin();
            edge_index != nodes.at(node_index).edges.end();
            ++edge_index) {
            // If an edge connection exists in the edge list, that means
            // we increase the indegree of the pointed to node.
            nodes.at(edge_index->index_to).indegree += 1;
            //nodes.at(*edge_index).indegree += 1;
        }
    }

    std::queue<graph_node> zero_indegrees;
    // Push initial indegree(0) nodes onto the queue
    for (int n = 0; n < nodes.size(); ++n) {
        if (nodes.at(n).indegree == 0)
            zero_indegrees.push(nodes.at(n));
    }

    if (zero_indegrees.empty()) {
        printf("ERROR: There is a cycle in the graph.\n");
    }

    // Handle Queue: 0(n + e)
    while (!zero_indegrees.empty()) {
        // Loop over the edges in a known indegree(0) node.
        graph_node front = zero_indegrees.front();

        for (std::list<graph_edge>::iterator edge_index = front.edges.begin();
            edge_index != front.edges.end();
            ++edge_index) {
            // For each indegree(0) node subtract an indegree because...
            // we're essentially deleting the front of the queue and the nodes
            // it points to will then have one less indegree
            nodes.at(edge_index->index_to).indegree -= 1;

            // If the nodes updated indegree is now 0, we want to add it to the
            // queue so we can progress further through the graph.
            if (nodes.at(edge_index->index_to).indegree == 0) {
                zero_indegrees.push(nodes.at(edge_index->index_to));
            }
        }
        printf("%c ", front.name);
        //DEBUG_PRINT(("%c", front.name));

        // Control how Sorted nodes are provided here...
        // We only need to print them so nothing complicated
        sorted.push_back(front.name);
        zero_indegrees.pop();
    }

    printf("\n");
    return sorted;
}


// Kruskal
void GraphList::MinimumSpanningTree() {
    std::list<graph_edge> sorted_edges;
    
    // In an undirected graph this adds duplicate edges to the list
    // TODO: Find a more elegant solution
    for (int i = 0; i < nodes.size(); ++i) {
        for (std::list<graph_edge>::iterator edge = nodes.at(i).edges.begin(); 
            edge != nodes.at(i).edges.end(); ++edge) {
            sorted_edges.push_back(*edge);
        }
    }

    sorted_edges.sort(WeightComparator);

    

    // Setup parent array 0(n)
    UnionFind parent_array;
    for (int i = 0; i < nodes.size(); ++i) {
        parent_array
    }


    for (int i = 0; i < sorted_edges.size(); ++i) {

    }



}