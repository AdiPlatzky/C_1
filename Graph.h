// המייל שלי:
// 12adi45@gmail.com

#ifndef GRAPH_H
#define GRAPH_H
#include "Node_V.h"
#include "Helpers.h"

namespace graph {
    struct Neighbor {
        int dest;
        int weight;
        Neighbor* next; // מצביע על מי שהקודם הצביע עליו

        Neighbor(int dest, int weight, Neighbor* next = nullptr)
            : dest(dest), weight(weight), next(next) {}
    };

    class Graph {
    public:
        const int num_vertices;
        Node_V** nodes; //מערך של קודקודים
        Neighbor** adjacency_list; // מערך של רשימת שכנויות

        Graph(int num_vertices);
        ~Graph();

        void add_Edge(int from, int to, int weight = 1) const;
        void remove_Edge(int from, int to) const;
        void print_graph() const;
    };
} // graph

#endif //GRAPH_H
