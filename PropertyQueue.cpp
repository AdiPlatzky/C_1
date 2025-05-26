//
// Created by 12adi on 09/04/2025.
//

#include "PropertyQueue.h"
#include <stdexcept>
#include "Helpers.h"

namespace graph {
    PropertyQueue::PropertyQueue() : head(nullptr) {}

    PropertyQueue::~PropertyQueue() {
        while (head != nullptr) {
            deleteAndAdvance(head);
        }
    }

    void PropertyQueue::insert(Node_V* node_v, int priority, Node_V* parent_v)
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

    Node_V* PropertyQueue::extractMin()
    {
        if (head == nullptr)
            throw "priority queue is empty";

        Node_V* minD = head->node;
        deleteAndAdvance(head);
        return minD;
    }

    bool PropertyQueue::isEmpty() const
    {
        return head == nullptr;
    }

    void PropertyQueue::decreaseKey(Node_V* node_v, int new_priority, Node_V* newParent_v) {
        if (head == nullptr) return;
        PQNode* curr = head;
        PQNode* prev = nullptr;

        while (curr != nullptr && curr->node != node_v) {
            prev = curr;
            curr = curr->next;
        }

        if (curr == nullptr) return;

        if (new_priority >= curr->d) return;;

        if (prev == nullptr) {
            head = curr->next;
        }
        else {
            prev->next = curr->next;
        }
        delete curr;

        insert(node_v, new_priority, newParent_v);
    }

    bool PropertyQueue::contains(Node_V* node_v) {
        PQNode* curr = head;
        while (curr != nullptr) {
            if (curr->node == node_v) {
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    Node_V* PropertyQueue::getParent(Node_V* node_v)const {
        PQNode* curr = head;
        while (curr != nullptr) {
            if (curr->node == node_v) {
                return curr->key_pai;
            }
            curr = curr->next;
        }
        return nullptr;
    }
} // graph