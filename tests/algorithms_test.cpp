//
// Created by 12adi on 26/05/2025.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../Algorithms.h"

using namespace graph;
TEST_CASE("small connected graph") {
    Graph g(4);
    g.add_Edge(0,1);
    g.add_Edge(0,2);
    g.add_Edge(1,3);

    Algorithms algo;
    Graph bfs_tree = algo.bfs(g, g.nodes[0]);

    CHECK_NOTHROW(bfs_tree.print_graph());
}

TEST_CASE("DFS: disconnected graph") {
    Graph g(5);
    g.add_Edge(0,1);
    g.add_Edge(2,3);

    Algorithms algo;
    Graph dfs_tree = algo.bfs(g, g.nodes[0]);

    CHECK_NOTHROW(dfs_tree.print_graph());
}

TEST_CASE("Dijkstra: weighted graph with unreachable nodes") {
    Graph g(5);
    g.add_Edge(0,1,3);
    g.add_Edge(1,2,1);

    Algorithms algo;
    Graph dij_tree =algo.dijkstra(g, g.nodes[0]);

    CHECK_NOTHROW(dij_tree.print_graph());
}

TEST_CASE("Prim: complete graph with different wights") {
    Graph g(4);
    g.add_Edge(0,1,1);
    g.add_Edge(0,2,10);
    g.add_Edge(0, 3, 100);
    g.add_Edge(1, 2, 2);
    g.add_Edge(1, 3, 50);
    g.add_Edge(2, 3, 20);

    Algorithms algo;
    Graph prim_tree = algo.prim(g);

    CHECK_NOTHROW(prim_tree.print_graph());
}

TEST_CASE("Kurskal: minimal spanning tree creation") {
    Graph g(6);
    g.add_Edge(0, 1, 4);
    g.add_Edge(0, 2, 4);
    g.add_Edge(1, 2, 2);
    g.add_Edge(1, 0, 4);
    g.add_Edge(2, 3, 3);
    g.add_Edge(2, 5, 2);
    g.add_Edge(2, 4, 4);
    g.add_Edge(3, 4, 3);
    g.add_Edge(5, 4, 3);

    Graph kurskal_tree = Algorithms::kruskal(g);

    CHECK_NOTHROW(kurskal_tree.print_graph());
}