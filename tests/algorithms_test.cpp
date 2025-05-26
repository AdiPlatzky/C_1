//
// Created by 12adi on 26/05/2025.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../Algorithms.h"

TEST_CASE("kurskal") {
    graph::Graph g(4);
    g.add_Edge(0,1,1);
    g.add_Edge(1,2,2);
    g.add_Edge(2,3,3);
    g.add_Edge(3,0,4);

    graph::Graph mst = graph::Algorithms::kruskal(g);
    CHECK(mst.num_vertices == 4);
}