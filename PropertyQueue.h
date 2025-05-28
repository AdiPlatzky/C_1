//
// 12adi45@gmail.com
//
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include "Graph.h"
/**
 * A simple priority queue implemented using a singly linked list.
 * This queue is used in graph algorithms such as Dijkstra and Prim.
 * Each element in the queue holds:
 * - A graph node (`Node_V*`)
 * - A priority value (`int d`) representing distance or weight
 * - A parent pointer (`Node_V* key_pai`) used for backtracking the tree
 */
namespace graph {
    class PropertyQueue {
        /**
        * Internal structure representing a single item in the priority queue.
        * Each item maintains:
        * - `node`: the vertex this entry represents
        * - `d`: the priority (e.g., distance value)
        * - `key_pai`: the parent node in the graph traversal
        * - `next`: pointer to the next item in the queue
        */
        struct PQNode {
            Node_V *node;
            int d;
            Node_V *key_pai;
            PQNode *next;

            PQNode(Node_V *node, int d, Node_V *key_pai = nullptr)
                : node(node), d(d), key_pai(key_pai), next(nullptr) {
            }
        };

        PQNode *head; // Pointer to the first item in the list (lowest priority)


    public:
        PropertyQueue(); // Constructor
        ~PropertyQueue(); // Destructor
        /**
        * Inserts a new node into the queue at the correct position
        * based on its priority value.
        *
        * @param node_v     The node to insert.
        * @param priority   The priority of the node (lower = higher priority).
        * @param parent_v   The parent of the node in the graph traversal.
        */
        void insert(Node_V *node_v, int priority, Node_V *parent_v);

        /**
        * Removes and returns the node with the minimum priority value.
        *
        * @return Node with the lowest priority.
        * @throws If the queue is empty.
        */
        Node_V *extractMin();
        /**
        * Checks whether the queue is empty.
        *
        * @return True if empty, false otherwise.
        */
        bool isEmpty() const;
        /**
        * Decreases the priority value of a given node in the queue.
        *
        * @param node_v        The node to update.
        * @param new_priority  The new lower priority value.
        * @param parent_v      The updated parent of the node.
        */
        void decreaseKey(Node_V *node_v, int new_priority, Node_V *parent_v);
        /**
        * Checks whether the given node exists in the queue.
        *
        * @param node_v Node to check.
        * @return True if the node exists, false otherwise.
        */
        bool contains(Node_V *node_v);
        /**
        * Returns the parent of the given node in the queue (if exists).
        *
        * @param node_v Node to look up.
        * @return Parent node or nullptr if not found.
        */
        Node_V *getParent(Node_V *node_v) const;
    };
} // graph

#endif
