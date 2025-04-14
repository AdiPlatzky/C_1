//
// Created by 12adi on 09/04/2025.
//

#include "Algorithms.h"

#include <queue>

#include "Graph.h"
#include "Queue.h"

namespace graph
{
    int time_global;

    Node** Algorithms::restart_Nodes(const Graph& graph)
    {
        int n = graph.num_vertices;
        Node** nodes = new Node*[n];
        for (int i = 0; i < n; ++i) {
            nodes[i] = new Node(graph.nodes[i], INF, nullptr);
            nodes[i]->color = "white";
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

        Node** nodes = Algorithms::restart_Nodes(graph);

        int source_id = source->get_id();
        nodes[source_id]->d_v = 0;
        nodes[source_id]->color = "gray";

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
                if (nodes[v_id]->color == "white")
                {
                    nodes[v_id]->color = "gray";
                    nodes[v_id]->d_v = nodes[u_id]-> d_v+1;
                    nodes[v_id]->parent = u;
                    Q.enqueue(graph.nodes[v_id]);

                    bfs_tree.add_Edge(u_id, v_id);
                }
                neighbor = neighbor->next;
            }
            nodes[u_id]->color = "black";
        }

        Algorithms::cleanup_Nodes(nodes, n);
    }


    Graph Algorithms::dfs(const Graph &graph, Node_V* source) {
        int n = graph.num_vertices;
        Graph dfs_tree(n);

        Node** nodes = Algorithms::restart_Nodes(graph);

        time_global = 0;
        for (int i = 0; i < n; ++i)
            if (nodes[i]->color == "white")
                DFS_visit(i, graph, nodes, dfs_tree);

        cleanup_Nodes(nodes, n);
        return dfs_tree;
    }




    void Algorithms::DFS_visit(int u_id, const Graph &graph, Node **node, Graph& dfs_tree)
    {
        node[u_id]->color = "gray";
        node[u_id]->d_v = time_global++;

        Neighbor* neighbor = graph.adjacency_list[u_id];
        while (neighbor != nullptr) {
            int v_id = neighbor->dest;
            if (node[v_id]->color == "white") {
                node[v_id]->parent = graph.nodes[u_id];
                DFS_visit(v_id, graph, node, dfs_tree);

                // רק קשתות tree edges!
                dfs_tree.add_Edge(u_id, v_id);
            }
            neighbor = neighbor->next;
        }

        node[u_id]->color = "black";
        node[u_id]->f_v = time_global++;
    }






} // graph