//
// 12adi45@gmail.com
//

#ifndef QUEUE_H
#define QUEUE_H
#include "Graph.h"

namespace graph
{
    /**
    * @struct Node_In_Queue
    * @brief A node in the doubly-linked list used to implement the Queue.
    */
    struct Node_In_Queue
    {
        Node_V* original;               ///< Pointer to the original node stored.
        Node_In_Queue* next_n;         ///< Pointer to the next node in the queue.
        Node_In_Queue* prev_n;         ///< Pointer to the previous node in the queue.

        Node_In_Queue(Node_V* original, Node_In_Queue* next_n = nullptr, Node_In_Queue* prev_n = nullptr)
        : original(original), next_n(next_n), prev_n(prev_n) {}
    };

    /**
    * @class Queue
    * @brief Implements a FIFO (First-In-First-Out) queue using a doubly-linked list.
    *        This structure is used in BFS traversal.
    */
class Queue {
    public:
    Node_In_Queue* head;  ///< Pointer to the front of the queue.
    Node_In_Queue* tail;    ///< Pointer to the back of the queue.
    int size;               ///< Tracks the number of elements in the queue.

    /**
    * @brief Constructor initializing an empty queue.
    */
    Queue(Node_In_Queue* head = nullptr, Node_In_Queue* tail = nullptr);
    /**
     * @brief Destructor that releases all dynamically allocated nodes.
     */
    ~Queue();
    /**
     * @brief Adds a node to the end of the queue.
     * @param node Pointer to the node to enqueue.
     */
    void enqueue(Node_V* node);
    /**
    * @brief Removes and returns the front node from the queue.
    * @return Pointer to the dequeued node.
    * @throws If the queue is empty.
    */
    Node_V* dequeue();
    /**
     * @brief Checks if the queue is empty.
     * @return True if the queue is empty, otherwise false.
     */
    bool is_empty() const;
};

}

#endif //QUEUE_H
