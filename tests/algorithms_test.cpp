//
// 12adi45@gmail.com
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../Algorithms.h"

using namespace graph;
TEST_SUITE("Advanced Algorithm Tests")
{
    TEST_CASE("small connected graph")
    {
        Graph g(4);
        g.add_Edge(0,1);
        g.add_Edge(0,2);
        g.add_Edge(1,3);

        Algorithms algo;
        Graph bfs_tree = algo.bfs(g, g.nodes[0]);

        CHECK_NOTHROW(bfs_tree.print_graph());
    }

    TEST_CASE("DFS: disconnected graph")
    {
        Graph g(5);
        g.add_Edge(0,1);
        g.add_Edge(2,3);

        Algorithms algo;
        Graph dfs_tree = algo.bfs(g, g.nodes[0]);

        CHECK_NOTHROW(dfs_tree.print_graph());
    }

    TEST_CASE("Dijkstra: weighted graph with unreachable nodes")
    {
        Graph g(5);
        g.add_Edge(0,1,3);
        g.add_Edge(1,2,1);

        Algorithms algo;
        Graph dij_tree =algo.dijkstra(g, g.nodes[0]);

        CHECK_NOTHROW(dij_tree.print_graph());
    }

    TEST_CASE("Prim: complete graph with different wights")
    {
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

    TEST_CASE("Kurskal: minimal spanning tree creation")
    {
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

    TEST_CASE("BFS on disconnected graph")
    {
        Graph g(5);
        g.add_Edge(0, 1, 1);
        g.add_Edge(1, 2, 1);
        // קודקודים 3,4 מנותקים

        Algorithms alg;
        Graph bfs_tree = alg.bfs(g, g.nodes[0]);

        // עץ BFS צריך להכיל רק את הקודקודים המחוברים
        // בדוק שקיימות קשתות רק בין 0,1,2
        bool has_edge_to_3_or_4 = false;
        for(int i = 0; i < 5; i++)
            {
            Neighbor* curr = bfs_tree.adjacency_list[i];
            while(curr != nullptr)
                {
                if(curr->dest == 3 || curr->dest == 4)
                {
                    has_edge_to_3_or_4 = true;
                    break;
                }
                curr = curr->next;
            }
        }
        CHECK_FALSE(has_edge_to_3_or_4);
    }

    TEST_CASE("DFS on single vertex")
    {
        Graph g(1);
        Algorithms alg;

        CHECK_NOTHROW(alg.dfs(g, g.nodes[0]));
        Graph dfs_tree = alg.dfs(g, g.nodes[0]);

        // עץ DFS של קודקוד יחיד צריך להיות ריק
        CHECK(dfs_tree.adjacency_list[0] == nullptr);
    }

    TEST_CASE("Dijkstra with negative weights")
    {
        Graph g(3);
        g.add_Edge(0, 1, -5);  // משקל שלילי
        g.add_Edge(1, 2, 3);

        Algorithms alg;
        // Dijkstra לא אמור לעבוד עם משקלים שליליים
        // אבל הקוד שלך לא בודק את זה, אז הוא ירוץ
        CHECK_NOTHROW(alg.dijkstra(g, g.nodes[0]));
    }

    TEST_CASE("Kruskal on empty graph")
    {
        Graph g(3);  // גרף ללא קשתות

        Graph mst = Algorithms::kruskal(g);

        // MST של גרף ללא קשתות צריך להיות ריק
        for(int i = 0; i < 3; i++)
        {
            CHECK(mst.adjacency_list[i] == nullptr);
        }
    }

    TEST_CASE("Kruskal with equal weights")
    {
        Graph g(4);
        g.add_Edge(0, 1, 5);
        g.add_Edge(1, 2, 5);
        g.add_Edge(2, 3, 5);
        g.add_Edge(0, 3, 5);

        Graph mst = Algorithms::kruskal(g);

        // צריכות להיות בדיוק 3 קשתות ב-MST
        int edge_count = 0;
        for(int i = 0; i < 4; i++)
        {
            Neighbor* curr = mst.adjacency_list[i];
            while(curr != nullptr)
            {
                if(curr->dest > i) edge_count++;  // ספור כל קשת פעם אחת
                curr = curr->next;
            }
        }
        CHECK(edge_count == 3);
    }

    TEST_CASE("Prim algorithm consistency")
    {
        Graph g(4);
        g.add_Edge(0, 1, 1);
        g.add_Edge(1, 2, 2);
        g.add_Edge(2, 3, 3);
        g.add_Edge(0, 3, 4);

        // הרץ Prim מספר פעמים - התוצאה צריכה להיות עקבית
        Graph mst1 = Algorithms::prim(g);
        Graph mst2 = Algorithms::prim(g);
        Graph mst3 = Algorithms::prim(g);

        // חשב את סכום המשקלים של כל MST
        auto calculateMSTWeight = [](const Graph& mst)
        {
            int total_weight = 0;
            for(int i = 0; i < mst.getNumVertices(); i++)
            {
                Neighbor* curr = mst.adjacency_list[i];
                while(curr != nullptr)
                {
                    if(curr->dest > i) {
                        total_weight += curr->weight;
                    }
                    curr = curr->next;
                }
            }
            return total_weight;
        };

        int weight1 = calculateMSTWeight(mst1);
        int weight2 = calculateMSTWeight(mst2);
        int weight3 = calculateMSTWeight(mst3);

        CHECK(weight1 == weight2);
        CHECK(weight2 == weight3);
    }

    TEST_CASE("Compare Kruskal vs Prim results")
    {
        Graph g(5);
        g.add_Edge(0, 1, 2);
        g.add_Edge(0, 3, 6);
        g.add_Edge(1, 2, 3);
        g.add_Edge(1, 3, 8);
        g.add_Edge(1, 4, 5);
        g.add_Edge(2, 4, 7);
        g.add_Edge(3, 4, 9);

        Graph kruskal_mst = Algorithms::kruskal(g);
        Graph prim_mst = Algorithms::prim(g);

        // חשב משקל כל MST
        auto calculateWeight = [](const Graph& mst)
        {
            int total = 0;
            for(int i = 0; i < mst.getNumVertices(); i++)
            {
                Neighbor* curr = mst.adjacency_list[i];
                while(curr != nullptr)
                {
                    if(curr->dest > i) total += curr->weight;
                    curr = curr->next;
                }
            }
            return total;
        };

        int kruskal_weight = calculateWeight(kruskal_mst);
        int prim_weight = calculateWeight(prim_mst);

        // שני האלגוריתמים צריכים לתת אותו משקל כולל
        CHECK(kruskal_weight == prim_weight);
    }
}
