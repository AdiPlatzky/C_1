//
// 12adi45@gmail.com
//
#include "Graph.h"
#include <cstdio>  // במקום <iostream>

namespace graph
{
    Graph::Graph(int num_vertices): num_vertices(num_vertices)
    {
        nodes = new Node_V*[num_vertices];
        for (int i = 0; i < num_vertices; i++)
            nodes[i] = new Node_V(i);

        adjacency_list = new Neighbor*[num_vertices];
        for (int i = 0; i < num_vertices; i++)
            adjacency_list[i] = nullptr;
    }

    Graph::~Graph()
    {
        for (int i = 0; i < num_vertices; i++) {
            delete nodes[i];
            Neighbor* curr = adjacency_list[i];
            while (curr != nullptr) {
                deleteAndAdvance(curr);
            }
        }
        delete[] adjacency_list;
        delete[] nodes;
    }

    void Graph::add_Edge(int from, int to, int weight) const
    {
        if (from < 0 || from >= num_vertices || to < 0 || to >= num_vertices)
            throw "Invalid vertex index";

        adjacency_list[from] = new Neighbor(to, weight, adjacency_list[from]);
        adjacency_list[to] = new Neighbor(from, weight, adjacency_list[to]);
    }

    void Graph::remove_Edge(int from, int to) const
    {
        if (from < 0 || from >= num_vertices || to < 0 || to >= num_vertices)
            throw "Invalid vertex index";

        bool removed1 = false, removed2 = false;

        Neighbor* next_v = adjacency_list[from];
        Neighbor* prev = nullptr;
        while (next_v != nullptr)
        {
            if (next_v->dest == to)
            {
                if (prev == nullptr)
                    adjacency_list[from] = next_v->next;
                else
                    prev->next = next_v->next;

                delete next_v;
                removed1 = true;
                break;
            }
            prev = next_v;
            next_v = next_v->next;
        }

        Neighbor* revers_v = adjacency_list[to];
        Neighbor* revers_prev = nullptr;
        while (revers_v != nullptr)
        {
            if (revers_v->dest == from)
            {
                if (revers_prev == nullptr)
                    adjacency_list[to] = revers_v->next;
                else
                    revers_prev->next = revers_v->next;

                delete revers_v;
                removed2 = true;
                break;
            }
            revers_prev = revers_v;
            revers_v = revers_v->next;
        }

        if (!removed1 || !removed2)
            throw "Edge does not exist";
    }

    void Graph::print_graph() const
    {
        for (int i = 0; i < num_vertices; ++i)
        {
            Neighbor* temp_v = adjacency_list[i];
            while (temp_v != nullptr)
            {
                if (temp_v->dest > i)
                {
                    // במקום std::cout
                    printf("e{(%d,%d),%d}\n", i, temp_v->dest, temp_v->weight);
                }
                temp_v = temp_v->next;
            }
        }
    }
} // namespace graph
