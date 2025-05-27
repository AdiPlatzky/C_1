//
// Created by 12adi on 09/04/2025.
//

#include "Queue.h"

namespace graph
{
    Queue::Queue(Node_In_Queue *head, Node_In_Queue *tail): head(head), tail(tail), size(0) {

    }
    Queue::~Queue() {
        Node_In_Queue* current = head;
        while (current != nullptr) {
            Node_In_Queue* next = current->next_n;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    void Queue::enqueue(Node_V *node)
    {
        Node_In_Queue *newNode = new Node_In_Queue(node);
        if (is_empty()) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next_n = newNode;
            newNode->prev_n = tail;
            tail = newNode;
        }
        size++;
    }

    Node_V *Queue::dequeue()
    {
        if (is_empty())
        {
            throw "Queue is empty";
        }
        Node_In_Queue* temp = head;
        Node_V *node = temp->original;
        head = head->next_n;

        if (head != nullptr)
        {
            head->prev_n = nullptr;
        }
        else
        {
            tail = nullptr;
        }
        delete temp;
        size--;
        return node;
    }

    bool Queue::is_empty()const {
        if (size == 0) {
            return true;
        }
        return false;
    }
} // graph