//
// Created by 12adi on 26/05/2025.
//
// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../Node_V.h"

using namespace graph;

TEST_CASE("creat object && check ID") {
    Node_V node1(7);
    CHECK(node1.get_id() == 7);

    Node_V node2(-5);
    CHECK(node2.get_id() == -5);

    Node_V node3(0);
    CHECK(node3.get_id() == 0);
}
TEST_CASE("check const id") {
    Node_V node3(42);
    CHECK(node3.get_id() == 42);
}