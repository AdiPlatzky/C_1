//
// 12adi45@gmail.com
//
#include "doctest.h"
#include "../Graph.h"
#include "../Algorithms.h"
#include "../Queue.h"

using namespace graph;

TEST_SUITE("Memory Management Tests")
{
    TEST_CASE("Graph destruction with many edges")
    {
        {
            Graph g(100);

            // הוסף הרבה קשתות
            for(int i = 0; i < 99; i++) {
                g.add_Edge(i, i + 1, i);
            }

            // הוסף קשתות אקראיות
            for(int i = 0; i < 50; i++) {
                g.add_Edge(i, (i + 50) % 100, i * 2);
            }

            // מחק חלק מהקשתות
            for(int i = 0; i < 25; i++) {
                try {
                    g.remove_Edge(i, i + 1);
                } catch(...) {
                    // אם הקשת לא קיימת, זה בסדר
                }
            }
        }
        // כאן הdestructor צריך לנקות הכל

        CHECK(true);  // אם הגענו לכאן, לא היה crash
    }

    TEST_CASE("Algorithm trees cleanup")
    {
        Graph g(50);

        // בנה גרף מחובר
        for(int i = 0; i < 49; i++) {
            g.add_Edge(i, i + 1, i + 1);
        }

        Algorithms alg;

        // הרץ כל האלגוריתמים
        {
            Graph bfs_tree = alg.bfs(g, g.nodes[0]);
            Graph dfs_tree = alg.dfs(g, g.nodes[0]);
            Graph dijkstra_tree = alg.dijkstra(g, g.nodes[0]);
            Graph prim_tree = Algorithms::prim(g);
            Graph kruskal_tree = Algorithms::kruskal(g);

            // כל העצים יושמדו כאן
        }

        CHECK(true);  // בדיקה שלא היה crash
    }

    TEST_CASE("Queue stress test") {
        Queue q;
        Node_V *nodes[1000];
        for (int i = 0; i < 1000; i++) {
            nodes[i] = new Node_V(i);
            q.enqueue(nodes[i]);
        }

        for (int i = 0; i < 1000; i++) {
            Node_V *extracted = q.dequeue();
            CHECK(extracted->get_id() == i);
        }

        for(Node_V* node : nodes) {
            delete node;
        }
        CHECK(true);
    }

}
