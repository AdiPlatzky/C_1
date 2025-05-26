//
// Created by 12adi on 25/05/2025.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../Graph.h"

using namespace graph;

TEST_CASE("build graph && vertices")
{
    graph::Graph g(3);
    CHECK(g.num_vertices() == 3);
    for (int i = 0; i < 3; i++)
    {
      CHECK(g.nodes[i]->get_id() == i);
      CHECK(g.adjacency_list[i] == nullptr);
    }
}

TEST_CASE("add edges && neighbors")
{
  Graph g(3);
  g.add_Edge(0, 1,5);
  g.add_Edge(1, 2,7);

  CHECK(g.adjacency_list[0]->dest == 1);
  CHECK(g.adjacency_list[0]->weight == 5);

  CHECK(g.adjacency_list[1]->dest == 2);
  CHECK(g.adjacency_list[1]->weight == 7);

  CHECK(g.adjacency_list[2]->dest == 1);
}

TEST_CASE("delete edges")
{
  Graph g(2);
  g.add_Edge(0, 1,10);
  g.add_Edge(0, 1);

  CHECK(g.adjacency_list[0] == nullptr);
  CHECK(g.adjacency_list[1] == nullptr);
}

TEST_CASE("check error")
{
  Graph g(2);
  CHECK_THROWS(g.add_Edge(-1, 1,3));
  CHECK_THROWS(g.add_Edge(0, 2,3));
  CHECK_THROWS(g.remove_Edge(1, 5));
}
//    CHECK_NOTHROW(g.add_Edge(0, 1, 5));
//    CHECK_NOTHROW(g.add_Edge(2, 3, 7));
//
//    // בדיקה של חריגה עבור קודקודים לא חוקיים
//    CHECK_THROWS(g.add_Edge(-1, 3, 2));
//    CHECK_THROWS(g.add_Edge(4, 0, 1));  // מחוץ לתחום
//}
