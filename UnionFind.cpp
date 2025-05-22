//
// Created by 12adi on 14/04/2025.
//

#include "UnionFind.h"

#include "Algorithms.h"

namespace graph
{
    UnionFind::UnionFind(int n)
    {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    UnionFind:: ~UnionFind()
    {
        delete[] parent;
        delete[] rank;
    }

    int UnionFind::Find(int x)
    {
        if (parent[x] != x) {
            parent[x] = Find(parent[x]);
        }
        return parent[x];
    }

    void UnionFind::Union(int x, int y)
    {
        int xRoot = Find(x);
        int yRoot = Find(y);

        if (xRoot == yRoot) {
            return;
        }
        if (rank[xRoot] < rank[yRoot]){
            parent[xRoot] = yRoot;
        }
        else if (rank[xRoot] > rank[yRoot]) {
            parent[yRoot] = xRoot;
        }
        else {
            parent[yRoot] = xRoot;
            rank[xRoot]++;
        }
    }

    bool UnionFind::Connected(int u, int v)
    {
        return Find(u) == Find(v);
    }
} // graph