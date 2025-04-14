//
// Created by 12adi on 14/04/2025.
//

#include "UnionFind.h"

#include "Algorithms.h"

namespace graph {
    UnionFind::UnionFind(int num_vertices) {

    }

    void UnionFind::Create(int root) {
        if (root < 0) {

        }
        Graph new_tree(1);
        Node_V new_node(root);
        new_tree.add_Edge(int(nullptr), root, 0);
    }

    int UnionFind::Find(int node) {
        if (nodes[node] != node) {

        }
        if (nodes[node] != node) {
            nodes[node] = Find(nodes[node]);
        }
        return nodes[node];


    }

} // graph