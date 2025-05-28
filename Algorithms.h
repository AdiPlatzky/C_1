//
// 12adi45@gmail.com
//

#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <string>

#include "Graph.h"

namespace graph
{
    /**
     * A helper structure to store DFS/BFS-related metadata for each vertex.
     */
    struct Node {
        Node_V* node_v;
        int d_v;
        int f_v;
        Node_V* parent;
        std::string color;

        Node(Node_V* node_v, int d_v, Node_V* parent) : node_v(node_v), d_v(d_v), f_v(0), parent(parent), color("") {}
    };

class Algorithms {
    /**
    * Initializes auxiliary Node array for graph algorithms.
    * @param graph The graph to prepare.
    * @param print_white Whether to initialize color to "white" (default: true).
    * @return A dynamic array of Node* representing each vertex.
    */
    public:
    /**
    * Initializes auxiliary Node array for graph algorithms.
    * @param graph The graph to prepare.
    * @param print_white Whether to initialize color to "white" (default: true).
    * @return A dynamic array of Node* representing each vertex.
    */
    static Node** restart_Nodes(const Graph& graph, bool print_white);
    /**
     * Releases dynamically allocated array of Node*.
     * @param nodes Array of Node*.
     * @param n Number of vertices.
     */
    static void cleanup_Nodes(Node** nodes, int n);
    /**
     * Performs Breadth-First Search (BFS) starting from a source vertex.
     * @param graph The graph to search.
     * @param source Pointer to the starting vertex.
     * @return A BFS tree graph built from the traversal.
     */

    static Graph bfs(const Graph& graph, Node_V* nodes);
    /**
    * Internal helper function for DFS. Recursively explores vertices.
    * @param source_id ID of the current source vertex.
    * @param graph The graph.
    * @param node Array of traversal metadata.
    * @param dfs_tree The resulting DFS tree being built.
    */

    static void DFS_visit(int source_id, const Graph & graph, Node ** node, Graph& dfs_tree);
    /**
    * Performs Breadth-First Search (BFS) starting from a source vertex.
    * @param graph The graph to search.
    * @param source Pointer to the starting vertex.
    * @return A BFS tree graph built from the traversal.
    */
    static Graph dfs(const Graph& graph, Node_V* nodes);
    /**
    * Dijkstra's algorithm for shortest paths from a single source.
    * @param graph The graph.
    * @param source The source vertex.
    * @return A shortest-path tree graph.
    */
    static Graph dijkstra(const Graph& graph, Node_V* nodes);
    /**
    * Prim's algorithm to construct a Minimum Spanning Tree (MST).
    * @param graph The graph.
    * @return The MST graph built using Prim's method.
    */
    static Graph prim(const Graph& graph);
    /**
    * Kruskal's algorithm to construct a Minimum Spanning Tree (MST).
    * @param graph The graph.
    * @return The MST graph built using Kruskal's method.
    */
    static Graph kruskal(const Graph& graph);
};

} // graph

#endif //ALGORITHMS_H
