//
// Created by 12adi on 09/04/2025.
//

#ifndef QUEUE_H
#define QUEUE_H
#include "Graph.h"

namespace graph {
    struct Node_In_Queue
    {
        Node_V* original;
        Node_In_Queue* next_n;
        Node_In_Queue* prev_n;

        Node_In_Queue(Node_V* original, Node_In_Queue* next_n = nullptr, Node_In_Queue* prev_n)
        : original(original), next_n(next_n), prev_n(prev_n) {}
    };

class Queue {

    public:
    Node_In_Queue* head;
    Node_In_Queue* tail;
    int size;

    Queue(Node_In_Queue* head = nullptr, Node_In_Queue* tail = nullptr);
    ~Queue();

    void enqueue(Node_V* node);
    Node_V* dequeue();

    bool is_empty();

    bool is_empty() const;



};

} // graph

#endif //QUEUE_H
