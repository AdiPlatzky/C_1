//
// Created by 12adi on 09/04/2025.
//

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include "Graph.h"
namespace graph {
    struct PQNode {
        Node_V* node;
        int d;
        Node_V* key_pai;
        PQNode* next;

        PQNode(Node_V* node, int d, Node_V* key_pai = nullptr) : node(node), d(d), key_pai(key_pai), next(nullptr) {}
    };

class PriorityQueue {
    PQNode* head;

public:
    PriorityQueue();
    ~PriorityQueue();

    void insert(Node_V* node_v, int priority, Node_V* parent_v);
    Node_V* extractMin();
    bool isEmpty() const;
};

} // graph

#endif //PRIORITYQUEUE_H
