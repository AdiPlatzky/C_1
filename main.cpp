// 12adi45@gmail.com

#include <cstdio>
#include "Graph.h"
#include "Algorithms.h"

using namespace graph;

int main() {
    printf("=== Final Project: Algorithm Tree - Adi Platzky ===\n");

    try {
        Graph g(5); //makes tree with 5 vertices - without edges currently

        // now I am adding edges to the tree - the edges are have two sides
        g.add_Edge(0, 1, 1);
        g.add_Edge(0, 2, 2);
        g.add_Edge(1, 3, 3);
        g.add_Edge(2, 4, 4);
        g.add_Edge(3, 4, 5);

        printf("\nInitial Graph:\n");
        g.print_graph();

        g.remove_Edge(0, 1);
        printf("\nAfter removing edge 0-1:\n");
        g.print_graph();

        Node_V* start = g.nodes[0];

        printf("\n--- BFS Tree ---\n");
        Graph bfs_tree = Algorithms::bfs(g, start);
        bfs_tree.print_graph();

        printf("\n--- DFS Tree ---\n");
        Graph dfs_tree = Algorithms::dfs(g, start);
        dfs_tree.print_graph();

        printf("\n--- Dijkstra Distances ---\n");
        Algorithms::dijkstra(g, start);

        printf("\n--- Prim MST ---\n");
        Graph prim_tree = Algorithms::prim(g);
        prim_tree.print_graph();

        printf("\n--- Kruskal MST ---\n");
        Graph kruskal_tree = Algorithms::kruskal(g);
        kruskal_tree.print_graph();

    } catch (const char* msg) {
        printf("Error occurred: %s\n", msg);
    }

    return 0;
}
