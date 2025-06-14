//
// 12adi45@gmail.com
//

#include "Algorithms.h"
#include <ctime>

#include <queue>
#include "EdgeList.h"
#include "Graph.h"
#include "PropertyQueue.h"
#include "Queue.h"
#include "UnionFind.h"

namespace graph {
    int time_global;

    Node** Algorithms::restart_Nodes(const Graph& graph, bool print_white = true)
    {
        int n = graph.num_vertices;
        Node** nodes = new Node*[n];
        for (int i = 0; i < n; i++) {
            nodes[i] = new Node(graph.nodes[i], INF, nullptr);
            if (print_white)
                nodes[i]->setColor("white");
        }
        return nodes;
    }

    void Algorithms::cleanup_Nodes(Node** nodes, int n)
    {
        for (int i = 0; i < n; ++i)
            delete nodes[i];
        delete[] nodes;
    }

    Graph Algorithms::bfs(const Graph& graph, Node_V *source)
    {
        int n = graph.num_vertices;
        Graph bfs_tree(n);

        Node** nodes = restart_Nodes(graph);

        int source_id = source->get_id();
        nodes[source_id]->d_v = 0;
        nodes[source_id]->setColor( "gray");

        Queue Q;
        Q.enqueue(source);

        while (!Q.is_empty())
        {
            Node_V* u = Q.dequeue();
            int u_id = u->get_id();

            Neighbor* neighbor = graph.adjacency_list[u_id];
            while (neighbor != nullptr)
            {
                int v_id = neighbor->dest;
                if (strcmp(nodes[v_id]->color, "white") == 0)
                {
                    nodes[v_id]->setColor("gray");
                    nodes[v_id]->d_v = nodes[u_id]-> d_v+1;
                    nodes[v_id]->parent = u;
                    Q.enqueue(graph.nodes[v_id]);

                    bfs_tree.add_Edge(u_id, v_id);
                }
                neighbor = neighbor->next;
            }
            nodes[u_id]->setColor("black");
        }

        cleanup_Nodes(nodes, n);
        return bfs_tree;
    }


    Graph Algorithms::dfs(const Graph &graph, Node_V* source) {
        int n = graph.num_vertices;
        Graph dfs_tree(n);

        Node** nodes = restart_Nodes(graph);
        time_global = 0;

        int source_id = source->get_id();
        if (strcmp(nodes[source_id]->color, "white") == 0) {
            DFS_visit(source_id,graph,nodes,dfs_tree);
        }
        for (int i = 0; i < n; ++i)
            if (strcmp(nodes[i]->color, "white") == 0)
                DFS_visit(i, graph, nodes, dfs_tree);

        cleanup_Nodes(nodes, n);
        return dfs_tree;
    }


    void Algorithms::DFS_visit(int u_id, const Graph &graph, Node **node, Graph& dfs_tree)
    {
        node[u_id]->setColor("gray");
        node[u_id]->d_v = time_global++;

        Neighbor* neighbor = graph.adjacency_list[u_id];
        while (neighbor != nullptr) {
            int v_id = neighbor->dest;
            if (strcmp(node[v_id]->color, "white") == 0) {
                node[v_id]->parent = graph.nodes[u_id];
                DFS_visit(v_id, graph, node, dfs_tree);

                // רק קשתות tree edges!
                dfs_tree.add_Edge(u_id, v_id);
            }
            neighbor = neighbor->next;
        }

        node[u_id]->setColor("black");
        node[u_id]->f_v = time_global++;
    }

    Graph Algorithms::dijkstra(const Graph &graph, Node_V *node_s)
    {
        int n = graph.num_vertices;
        Graph dijkstra_tree(n);
        Node** nodes = restart_Nodes(graph, false);
        nodes[node_s->get_id()]->d_v = 0;

        PropertyQueue Q = PropertyQueue();

        for (int i = 0; i < n; i++) {
            Q.insert(graph.nodes[i], nodes[i]->d_v, nodes[i]->parent);
        }

        while (!Q.isEmpty()) {
            Node_V* u = Q.extractMin();
            int u_id = u->get_id();

            Neighbor* neighbor = graph.adjacency_list[u_id];
            while (neighbor != nullptr) {
                int v_id = neighbor->dest;
                int newWeight = nodes[u_id]->d_v + neighbor->weight;

                if (newWeight < nodes[v_id]->d_v) {
                    nodes[v_id]->d_v = newWeight;
                    nodes[v_id]->parent = u;

                    Q.decreaseKey(graph.nodes[v_id], newWeight, u);
                }
                neighbor = neighbor->next;
            }
        }

        for (int i = 0; i < n; i++) {
            Node_V* parent = nodes[i]->parent;
            if (parent != nullptr) {
                dijkstra_tree.add_Edge(parent->get_id(), i);
            }
        }
        cleanup_Nodes(nodes, n);
        return dijkstra_tree;
    }

    Graph Algorithms::kruskal(const Graph &graph)
    {
        int n = graph.num_vertices;
        Graph kruskal_tree(n);

        EdgeList edges; // איסוף של הצלעות
        for (int u = 0; u < n; u++) {
            Neighbor* neighbor = graph.adjacency_list[u];
            while (neighbor != nullptr) {
                int v = neighbor->dest;
                int weight = neighbor->weight;

                if (u < v) {
                    edges.add(Edge(u, v, weight)); // כדי למנוע כפילויות של צלעות!!
                }
                neighbor = neighbor->next;
            }
        }

        edges.sort(); // מיון הצלעות לפי משקל

        UnionFind unionFind(n); // לצור זיהוי רכיבי קשירות

        for (int i = 0; i < n; i++) { //נעבור על כל הצלעות לפי הסדר
            Edge e = edges.get(i);

            if (!unionFind.Connected(e.u, e.v)) {
                unionFind.Union(e.u, e.v);
                kruskal_tree.add_Edge(e.u, e.v, e.weight);
            }
        }
        return kruskal_tree;
    }
        // פה אני רוצה לבצע מיון של הצלעות בסדר עולה כך שם הקשת בעלת המקך הנמוך ביותר תהיה הראשונה
        //  *ואז אני רוצה ליצור גרף לתשובה שיכיל לבסוף את כל הקודקודים מהגרף המקורי אבל לא עם כל צלעות!
        //  *את הצלעות אני אוסיף לפי בדיקה שאעשה
        //  *אבל לפני הבדיקה אשים תחילה את הקשת בעלת המשקל הנמוך ביותר שמצאתייחד עם הקודקודים שלה כמובן
        //  *ולאחר מכן אעשה בדיקה - אם 2-1 מקודקודי הקשת הבאה בתור לא נמצאים בגרף החדש - נוסיף את הקשת
        //  *אחרת הקשת הזו תסגור לנו מעגל ולכן לא נוסיך אותה ונעבור לקשת הבאה בתור
        //  *לאחר שעברנו על כל הקשתות נחזיר את הגרך החדש שנוצר לנו :)

    Graph Algorithms::prim(const Graph &graph)
    {
        int n = graph.num_vertices;
        Graph prim_tree(n);

        srand(time(NULL));
        int s = rand() % n;

        //Node_V* u = graph.nodes[s];
        Node** nodes = restart_Nodes(graph);

        nodes[s]->d_v = 0;
        PropertyQueue Q;

        for (int i = 0; i < n; i++)
        {
          Q.insert(graph.nodes[i], nodes[i]->d_v, nullptr);
        }
        while (!Q.isEmpty())
        {
          Node_V* u = Q.extractMin();
          int u_id = u->get_id();

          nodes[u_id]->setColor("black");

          Neighbor* neighbor = graph.adjacency_list[u_id];
          while (neighbor != nullptr)
          {
            int v_id = neighbor->dest;
            int weight = neighbor->weight;

            if(strcmp(nodes[v_id]->color, "black") != 0 && weight < nodes[v_id]->d_v)
            {
              nodes[v_id]->d_v = weight;
              nodes[v_id]->parent = u;

              Q.decreaseKey(graph.nodes[v_id], weight, u);
            }
            neighbor = neighbor->next;
          }
        }
        for (int v = 0; v < n; v++)
        {
          Node_V* parent = nodes[v]->parent;
          if (parent != nullptr)
          {
            int u = parent->get_id();
            prim_tree.add_Edge(u, v, nodes[v]->d_v);
          }
        }
        cleanup_Nodes(nodes, n);
        return prim_tree;
    }

} // graph