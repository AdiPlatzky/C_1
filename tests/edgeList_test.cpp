//
// Created by 12adi on 26/05/2025.
//
#include "doctest.h"
#include "../EdgeList.h"

using namespace graph;

TEST_CASE("") {
    EdgeList edges(2);
    CHECK(edges.size() == 0);

    edges.add(Edge(0,1,10));
    edges.add(Edge(1,2,20));
    CHECK(edges.size() == 2);

    edges.add(Edge(2,3,30));
    CHECK(edges.size() == 3);
    CHECK(edges.get(2).weight == 30);
}

TEST_CASE("check by index") {
    EdgeList edges;
    edges.add(Edge(3,4,5));
    edges.add(Edge(5,6,6));

    Edge e = edges.get(0);
    CHECK(e.u == 3);
    CHECK(e.v == 4);
    CHECK(e.weight == 5);

    CHECK(edges.get(1).v == 6);
}

TEST_CASE("sort by edge list") {
    EdgeList edges;
    edges.add(Edge(0,1,40));
    edges.add(Edge(1,2,10));
    edges.add(Edge(2,3,30));
    edges.add(Edge(3,4,20));

    edges.sort();

    CHECK(edges.get(0).weight == 10);
    CHECK(edges.get(1).weight == 20);
    CHECK(edges.get(2).weight == 30);
    CHECK(edges.get(3).weight == 40);
}
