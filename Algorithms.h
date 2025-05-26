//
// Created by 12adi on 09/04/2025.
//

#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <string>

#include "Graph.h"

namespace graph
{
    struct Node {
        Node_V* node_v;
        int d_v;
        int f_v;
        Node_V* parent;
        std::string color;

        Node(Node_V* node_v, int d_v, Node_V* parent) : node_v(node_v), d_v(d_v), f_v(0), parent(parent), color("") {}
    };

class Algorithms {
    public:
    static Node** restart_Nodes(const Graph& graph, bool print_white);
    static void cleanup_Nodes(Node** nodes, int n);

    Graph bfs(const Graph& graph, Node_V* nodes);

    void DFS_visit(int source_id, const Graph & graph, Node ** node, Graph& dfs_tree);

    Graph dfs(const Graph& graph, Node_V* nodes);
    Graph dijkstra(const Graph& graph, Node_V* nodes);
    Graph prim(const Graph& graph);
    static Graph kruskal(const Graph& graph);
};

} // graph

#endif //ALGORITHMS_H
