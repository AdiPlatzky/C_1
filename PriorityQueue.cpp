//
// Created by 12adi on 09/04/2025.
//

#include "PriorityQueue.h"

#include <stdexcept>

#include "Helpers.h"

namespace graph {
    PriorityQueue::PriorityQueue() : head(nullptr) {}

    PriorityQueue::~PriorityQueue() {
        while (head != nullptr) {
            deleteAndAdvance(head);
        }
    }

    void PriorityQueue::insert(Node_V* node_v, int priority, Node_V* parent_v)
    {
        PQNode* newNode = new PQNode(node_v, priority, parent_v);
        if (head == nullptr || newNode->d < head->d) {
            newNode->next = head;
            head = newNode;
            return;
        }
        PQNode* curr = head;
        while (curr->next != nullptr && curr->next->d <= newNode->d) {
            curr = curr->next;
        }

        newNode->next = curr->next;
        curr->next = newNode;
    }

    Node_V* PriorityQueue::extractMin()
    {
        if (head == nullptr)
            throw "priority queue is empty";

        Node_V* minD = head->node;
        deleteAndAdvance(head);
        return minD;
    }

    bool PriorityQueue::isEmpty() const
    {
        return head == nullptr;
    }
} // graph