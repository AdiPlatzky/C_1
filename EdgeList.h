//
// Created by 12adi on 22/05/2025.
//

#ifndef EDGELIST_H
#define EDGELIST_H

#include "Graph.h"

namespace graph
{

    struct Edge {
        int u, v, weight;

        Edge(int u = 0, int v = 0, int w = 0)
        : u(u), v(v), weight(w) {}
    };

class EdgeList {
    Edge* data;
    int capacity;
    int count;

    void resize();

public:
    EdgeList(int initial_size = 16);
    ~EdgeList();

    void add(const Edge& edge);
    void sort();
    Edge get(int index) const;
    int size() const;
};

} // graph

#endif //EDGELIST_H
