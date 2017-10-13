#include "stdafx.h"
#include "graph.h"
#include "UnionFind.h"

// TODO: Adjacency Map? What about Incidence Matrix?
//       Definitely add to graphs notes.

// TODO: Adjacency Matrix

// TODO: DFS with adjacency list(iterative with stack)
// TODO: DFS with adjacency matrix(recursive)
// TODO: DFS with adjacency matrix(iterative with stack)
// TODO: BFS with adjacency matrix

// TODO: single-source shortest path (Dijkstra)
// TODO: DFS - based algorithms(see Aduni videos above) :
            // list strongly connected components
            // check for bipartite graph


bool GraphList::validate(int node) {
    if (node > 0 || node < nodes.size())
        return true;
    else {
        DEBUG_PRINT(("Attempted to access node %i outside of graph[0-%zu]\n", node, nodes.size()));
        return false;
        //throw std::out_of_range("Illegal graph access");
    }
}

// 0(n + e)
void GraphList::PrintGraph() {
#if _DEBUG
    for (int i = 0; i < nodes.size(); ++i) {        
        if (nodes.at(i).dfs_started != -1 && nodes.at(i).dfs_finished != -1) {
            printf("%i/%i ", nodes.at(i).dfs_started, nodes.at(i).dfs_finished);
        }

        printf("%c: ", nodes.at(i).name);        
        for (std::list<graph_edge>::iterator edge_index = nodes.at(i).edges.begin();
             edge_index != nodes.at(i).edges.end(); ++edge_index) {           
            //printf("->%c ", edge_index->dest_name);
            printf("->%c ", edge_index->dest_name);
        }

        printf("\n");
    }
#endif

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
    g.index = nodes.size();
    g.name = node_name;
    // TODO: Overload to allow simultaneous Edge input 
    //       e.g. AddNode('A', 'B', <weight>);
    nodes.push_back(g);
}

void GraphList::AddEdge(char node_from, char node_to, int weight) {
    // NOTE:    Currently we're obfuscating the node index:
    //          AddEdge('A', 'B', <weight>); instead of AddEdge(0, 1, <weight>);
    //          which adds to complexity to improve code readability.
    int index_from = GetIndex(node_from);
    int index_to = GetIndex(node_to);

    if (index_from < 0 || index_from >= nodes.size()) {
        printf("ERROR: Attempted to add edge to a node not in graph.\n");
    }
    else if (index_to < 0 || index_to >= nodes.size()) {
        printf("ERROR: Attempted to create edge to nonexistent node.\n");
    }
    else {
        // Scan through edge list of specified node to check for duplicates
        for (std::list<graph_edge>::iterator it = nodes.at(index_from).edges.begin(); 
                it != nodes.at(index_from).edges.end(); ++it) {
            if (it->index_to == index_to) {
                printf("Error: Edge %c->%c already found, cannot re-add.\n",
                         node_from, node_to);
                return;
            }
            /* NOTE: Does std::list<> use a tail pointer? 0(1)            
            
            Or is it 0(e) to add a new node to the list?            
                    
            If the Dupe Check is 0(e)...
            Can we operate on the last node checked to maintain 0(e)?

            if (last_edge && !dupe):
                point to new edge!
            */
        }

        // Add edge to graph
        graph_edge new_edge;
        new_edge.index_from = index_from;
        new_edge.index_to = index_to;
        new_edge.dest_name = nodes.at(index_to).name;
        new_edge.weight = weight;
        nodes.at(index_from).edges.push_back(new_edge);

        // NOTE: We can automatically calculate indegrees here when adding an edge.
        //       We'd have to remove/edit the calculation in TopoSort (as it assumes 0)
        //       but it puts the load on graph creation instead of the algorithm.
        // nodes.at(edge_to).indegree += 1;
        
        // In an undirected graph we need to store each edge twice.
        // NOTE: To save space, can use:::::: if (i < j) access as [j, i]
        if (directed != true) {
            graph_edge back_edge;
            back_edge.index_from = index_to;
            back_edge.index_to = index_from;
            back_edge.dest_name = nodes.at(index_from).name;
            back_edge.weight = weight;
            nodes.at(index_to).edges.push_back(back_edge);
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
    // Return type as int for indicies?
    // or graph_node* to provide a sorted list of graph_nodes? (exposes nodes)
}

std::vector<graph_edge> GraphList::MinimumSpanningTree() {
    // Kruskal
    std::vector<graph_edge> sorted_edges;
    
    // In an undirected graph this adds duplicate edges to the list: A->B & B->A
    // TODO: Find a more elegant solution?
    for (int i = 0; i < nodes.size(); ++i) {
        for (std::list<graph_edge>::iterator edge = nodes.at(i).edges.begin(); 
                edge != nodes.at(i).edges.end(); ++edge) {
            sorted_edges.push_back(*edge);
        }
    }

    std::sort(sorted_edges.begin(), sorted_edges.end(), WeightComparator);
    
    // Setup parent array 0(n)
    UnionFind parent_array(nodes.size());

// TODO: I hate this implementation.
//  Union-Find is only to check for cycles. Weighted/PathComp the UnionFind makes it
//      unable to store an actual spanning tree (eg. actual parent references)
//  And the way I'm storing and manipulating "graph_edge"s doesn't seem pure.
//      Each graph_edge needs to hold its FROM value which makes this algorithm
//      seem more suited for an adjacency matrix, but we still want it in 0(e)
    std::vector<graph_edge> spanning_tree;
    // Loop over sorted edges and Union edges not in the same set.
    for (int i = 0; i < sorted_edges.size(); ++i) {
        if (parent_array.Find(sorted_edges.at(i).index_from) != 
            parent_array.Find(sorted_edges.at(i).index_to)) {

            parent_array.Union(sorted_edges.at(i).index_from, 
                                sorted_edges.at(i).index_to);
            spanning_tree.push_back(sorted_edges.at(i));
        }
    }

    return spanning_tree;
}

void GraphList::BFS(int start_node_index) {
    printf("BFS: ");
    // Array of size(n) that has 0's if nodes hasn't been seen yet.
    std::vector<bool> seen;
    for (int i = 0; i < nodes.size(); ++i) {
        seen.push_back(false);
    }

    std::queue<int> node_queue;
    if (start_node_index < 0 || start_node_index >= nodes.size()) {
        printf("Error: Tried to start BFS at node not in graph.");
        return;
    }
    node_queue.push(start_node_index);
    seen.at(start_node_index) = true;

    while (!node_queue.empty()) {
        int node_index = node_queue.front();
        for (std::list<graph_edge>::iterator edge = nodes.at(node_index).edges.begin();
                edge != nodes.at(node_index).edges.end(); ++edge) {
            if (seen.at(edge->index_to) == false) {
                node_queue.push(edge->index_to);
                seen.at(edge->index_to) = true;
            }
        }
        printf("%c ", nodes.at(node_index).name);
        node_queue.pop();
    }
    printf("\n");
}

void GraphList::DFSr(int n, std::vector<bool>& seen, std::vector<graph_node*> *tree,
                     int* start_counter, int* finish_counter) {
    // BEGINNING
    //DEBUG_PRINT(("%c ", nodes.at(n).name));
    DEBUG_PRINT(("%c ", nodes.at(n).name));
    seen.at(n) = true;
    tree->push_back(&nodes.at(n));

    nodes.at(n).dfs_started = *start_counter;
    (*start_counter)++;
    // NOTE: There's some weird operator precedence with incrementing a
    //          dereferenced pointer (right->left)... ++*ptr ...would also work.

    // Add item to DFS_TREE stack.
    for (std::list<graph_edge>::iterator edge = nodes.at(n).edges.begin();
        edge != nodes.at(n).edges.end(); ++edge) {

        // MIDDLE - TREE EDGES
        // Creates a DFS_Tree in SEARCHED order        
        if (!seen.at(edge->index_to)) {
            DFSr(edge->index_to, seen, tree, start_counter, finish_counter);
        }
        // else {} - BACK EDGES
        // Else we've already seen the node (seen == true) then we've found a back edge.
        // But in an UNDIRECTED graph this will trigger on every node.
        // So we have to check if the node we CAME FROM is the parent of the current node.
        // Otherwise, it's a back edge.        
    }
    // END
    // FINISHING TIMES
    nodes.at(n).dfs_finished = *finish_counter;
    ++*finish_counter;
}

// Can do a topological sort by doing a post-order traversal of the DFS tree...
//      then reading it backward. OR just use the finishing times as indicies.
std::vector<graph_node*> GraphList::DFS(int start_node) {
    validate(start_node);

    DEBUG_PRINT(("__DFS__\n"));

    std::vector<bool> seen(nodes.size(), false);
    std::vector<graph_node*> dfs_tree;

    // TODO: Make this start at 1?
    int start_count = 0;
    int finish_count = 0;

    // in undirected IF NODE OF PARENT IS SAME AS TREE EDGE ITS NOT A BACK EDGE
    int components = 1;
    for (int i = 0; i < nodes.size(); ++i) {
        if (!seen.at(i)) {
            DEBUG_PRINT(("Component %i: ", components));
            DFSr(i, seen, &dfs_tree, &start_count, &finish_count);
            // Track Connected components.
            /*
            for (int i = 0; i < dfs_tree.size(); ++i) {
                if (dfs_tree.at(i) != NULL) {
                    printf("%c->%c", nodes.at(i).name, dfs_tree.at(i)->name);
                }
            }
            */
            components++;
            DEBUG_PRINT(("\n"));
        }

    }

    return dfs_tree;
}

// Overloaded DFS that runs DFS in a custom order (for Strongly connected components.)
std::vector<graph_node*> GraphList::DFS(int start_node, std::vector<graph_node*> *dfs_order) {
    // Resort to default method if input == NULL
    if (dfs_order == NULL) {
        DEBUG_PRINT(("ERROR: No custom DFS order provided, DFSing normally.\n"));
        return DFS(start_node);
    }
    else {
        std::vector<bool> seen(nodes.size(), false);
        std::vector<graph_node*> dfs_tree;

        int start_count = 0;
        int finish_count = 0;

        int components = 1;
        for (int i = 0; i < dfs_order->size(); ++i) {
            if (!seen.at(i)) {
                DEBUG_PRINT(("Component %i: ", components));
                // This a really confusing and could be implemented more clearly.
                DFSr(dfs_order->at(i)->index, seen, &dfs_tree, &start_count, &finish_count);
                components++;
                DEBUG_PRINT(("\n"));
            }
        }

        return dfs_tree;
    }    
}

// Strongly connected components (only in DIRECTED graphs)
// https://youtu.be/DiedsPsMKXc?list=PLFDnELG9dpVxQCxuD-9BSy2E7BWY3t5Sm&t=3118
// A Strongly Connect component is a group of nodes where EVERY node can connect
//  to every other node in the component.
//      0(e) 1) DFS - calculate finishing times for each node
//      0(e) 2) Reverse the edges in the graph
//      0(e) 3) Call DFS on the nodes in the reverse graph, in reverse order of the 
//          finishing times.
GraphList GraphList::MakeReverseGraph() {

    // Note: This hulabaloo is required because I don't have a copy constructor.
    std::vector<graph_node> reversed_nodes(nodes.size());
        
    // Copy Nodes & Edges
    for (int i = 0; i < nodes.size(); ++i) {
        reversed_nodes.at(i).name = nodes.at(i).name;
        reversed_nodes.at(i).index = nodes.at(i).index;
        reversed_nodes.at(i).indegree = nodes.at(i).indegree; // No longer true
        reversed_nodes.at(i).dfs_started = nodes.at(i).dfs_started; // backward?
        reversed_nodes.at(i).dfs_finished = nodes.at(i).dfs_finished;
        
        std::list<graph_edge>::iterator edge;
        for (edge = nodes.at(i).edges.begin();
                edge != nodes.at(i).edges.end(); ++edge) {
            
            //TODO: Edges are borked, need to figure out how to make them work
            graph_edge new_edge;
            new_edge.index_from = edge->index_to;
            new_edge.index_to = edge->index_from;
            new_edge.dest_name = GetName(edge->index_from);
            new_edge.weight = edge->weight;

            reversed_nodes.at(edge->index_to).edges.push_back(new_edge);
            //reversed.AddEdge(edge->dest_name, nodes.at(i).name, edge->weight);
            
            //nodes.at(i).edges.pop_front();
            
            // TODO: char is clunky, overload AddEdge with indicies.
            //       See AddEdge() note.
            
        }
    }

    GraphList reversed;
    reversed.directed = directed;
    reversed.nodes = reversed_nodes;

    return reversed;
}

void GraphList::StronglyConnectedComponents() {

    //  0(e) 1) DFS - calculate finishing times for each node
    std::vector<graph_node*> temp = DFS(0);

    //  0(e) 2) Reverse the edges in the graph
    GraphList r = MakeReverseGraph();
        
    DEBUG_PRINT(("\n__Strongly Connected Components__\n"));
    
    //  0(e) 3) Call DFS on the nodes in the reverse graph, in reverse order 
    //          of the finishing times.
    r.DFS(0, &temp);
               
    // NOTE: Ideally this runs independently with it's own DFS implementation,
    //  but we have to call it as r.DFS() because DFS affects nodes and we want it
    //  to run on the "r" Graphlist, not muck about with "g"'s nodes.
    //  MakeReverseGraph should probably be independent too, taking a GraphList
    //  as arguments and returning a reversed graph.
}