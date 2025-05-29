//
// Created by 12adi on 25/05/2025.
//
#include "doctest.h"
#include "../Graph.h"

using namespace graph;

TEST_SUITE("Graph Advanced Tests"){

  TEST_CASE("build graph && vertices")
  {
    graph::Graph g(3);
    CHECK(g.getNumVertices() == 3);
    for (int i = 0; i < 3; i++)
    {
      CHECK(g.nodes[i]->get_id() == i);
      CHECK(g.adjacency_list[i] == nullptr);
    }
  }

  TEST_CASE("add edges && neighbors")
  {
    Graph g(3);
    g.add_Edge(0, 1, 5);
    g.add_Edge(1, 2, 7);

    // בדוק שהקשת נוספה בשני הכיווינם (גרף לא מכוון)
    CHECK(g.adjacency_list[0]->dest == 1);
    CHECK(g.adjacency_list[0]->weight == 5);

    CHECK(g.adjacency_list[1]->dest == 0); // תיקון: 1 מחובר ל-0, לא ל-2
    CHECK(g.adjacency_list[1]->weight == 5); // תיקון: הוזן לא 7

    // בדוק את הקשת השנייה
    bool found_2_to_1 = false;
    Neighbor* curr = g.adjacency_list[1];
    while(curr != nullptr) {
        if(curr->dest == 2 && curr->weight == 7) {
            found_2_to_1 = true;
            break;
        }
        curr = curr->next;
    }
    CHECK(found_2_to_1);

    CHECK(g.adjacency_list[2]->dest == 1);
    CHECK(g.adjacency_list[2]->weight == 7);
  }

  TEST_CASE("delete edges")
  {
    Graph g(2);
    g.add_Edge(0, 1, 10);

    // תיקון: remove_Edge במקום add_Edge
    g.remove_Edge(0, 1);

    CHECK(g.adjacency_list[0] == nullptr);
    CHECK(g.adjacency_list[1] == nullptr);
  }

  TEST_CASE("check error")
  {
    Graph g(2);
    CHECK_THROWS(g.add_Edge(-1, 1, 3));
    CHECK_THROWS(g.add_Edge(0, 2, 3));
    CHECK_THROWS(g.remove_Edge(1, 5));
  }

  TEST_CASE("Edge cases - Single vertex graph"){
    Graph g(1);
    CHECK(g.getNumVertices() == 1);
    CHECK(g.nodes[0]->get_id() == 0);
    CHECK(g.adjacency_list[0] == nullptr);

    CHECK_NOTHROW(g.print_graph());
  }

  TEST_CASE("Empty graph")
  {
    Graph g(0);
    CHECK(g.getNumVertices() == 0);
    // תיקון: גרף ריק לא אמור לזרוק חריגה בprint_graph
    CHECK_NOTHROW(g.print_graph());
  }

  TEST_CASE("Large graph creation")
  {
    Graph g(1000);
    CHECK(g.getNumVertices() == 1000);

    for (int i = 0; i < 1000; i++){
      CHECK(g.nodes[i]->get_id() == i);
      CHECK(g.adjacency_list[i] == nullptr);
    }
  }

  TEST_CASE("Add multiple edges between same vertices")
  {
    Graph g(3);
    g.add_Edge(0, 1, 10);
    CHECK(g.adjacency_list[0]->dest == 1);
    CHECK(g.adjacency_list[0]->weight == 10);

    g.add_Edge(0, 1, 20);

    int edge_count = 0;
    Neighbor* curr = g.adjacency_list[0];
    while (curr != nullptr){
      if (curr->dest == 1)
      {
        edge_count++;
      }
      curr = curr->next;
    }
    CHECK(edge_count == 2);
  }

  TEST_CASE("Self loops"){
    Graph g(3);
    g.add_Edge(0, 0, 5);

    CHECK(g.adjacency_list[0]->dest == 0);
    CHECK(g.adjacency_list[0]->weight == 5);

    int self_loop_count = 0;
    Neighbor* curr = g.adjacency_list[0];
    while (curr != nullptr){
      if (curr->dest == 0){
        self_loop_count++;
      }
      curr = curr->next;
    }
    CHECK(self_loop_count == 2); // self-loop מופיע פעמיים
  }

  TEST_CASE("Remove edge that doesn't exist")
  {
    Graph g(3);
    g.add_Edge(0, 1, 5);

    CHECK_THROWS_WITH(g.remove_Edge(0, 2), "Edge does not exist");
    CHECK_THROWS_WITH(g.remove_Edge(1, 2), "Edge does not exist");
  }

  TEST_CASE("Remove edge multiple times"){
    Graph g(3);
    g.add_Edge(0, 1, 5);

    CHECK_NOTHROW(g.remove_Edge(0, 1));
    CHECK_THROWS_WITH(g.remove_Edge(0, 1), "Edge does not exist");
  }

  TEST_CASE("All vertices connected to one vertex (star graph)")
  {
    Graph g(6);

    for (int i = 1; i < 6; i++) // תיקון: התחל מ-1, לא מ-0
    {
      g.add_Edge(0, i, i);
    }

    bool connected_to_0[6] = {false, false, false, false, false, false};
    Neighbor* curr = g.adjacency_list[0];
    while (curr != nullptr)
    {
      connected_to_0[curr->dest] = true;
      curr = curr->next;
    }

    int count = 0;
    for (int i = 1; i < 6; i++) // תיקון: בדוק רק 1-5
    {
      if(connected_to_0[i]){
        count++;
      }
      CHECK(connected_to_0[i]);
    }
    CHECK(count == 5);
    CHECK(connected_to_0[0] == false); // 0 לא מחובר לעצמו במקרה הזה
  }
}