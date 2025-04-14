//
// Created by 12adi on 14/04/2025.
//

#ifndef UNIONFIND_H
#define UNIONFIND_H
#include "Graph.h"

namespace graph {

class UnionFind {
    public:
    int* parent;
    int* rank;
    int* size;

    UnionFind(int num_vertices);
    ~UnionFind();

    void Create(int s);
    int Find(int v);
    void Union(int u, int v);
    bool Connected(int u, int v);
};

} // graph


#endif //UNIONFIND_H
