//
// 12adi45@gmail.com
//

#ifndef EDGELIST_H
#define EDGELIST_H

#include "Graph.h"

namespace graph
{
    /**
     * Structure representing a graph edge with two vertices (u, v) and a weight.
     */
    struct Edge {
        int u, v, weight;
        /**
        * Constructor with default parameters.
        * @param u Source vertex.
        * @param v Destination vertex.
        * @param w Edge weight.
        */
        Edge(int u = 0, int v = 0, int w = 0)
        : u(u), v(v), weight(w) {}
    };
    /**
     * Class EdgeList - A dynamic array-based structure for storing graph edges.
     * Provides methods to add, retrieve, sort, and manage edges.
     */
class EdgeList {
    Edge* data;     /// Dynamic array of edges
    int capacity;   /// Total capacity of the array
    int count;      /// Current number of stored edges

    /**
    * Doubles the array capacity when full.
    * Internal method used by add().
    */
    void resize();

public:
    /**
     * Constructor - Initializes the edge list with a given initial capacity.
     * @param initial_size Starting size of the array (default: 16)
     */
    EdgeList(int initial_size = 16);
    /**
     * Destructor - Frees the dynamically allocated memory.
     */
    ~EdgeList();
    /**
    * Adds a new edge to the list.
    * Automatically resizes if needed.
    * @param edge The edge to be added.
    */
    void add(const Edge& edge);
    /**
     * Sorts the list of edges by weight in ascending order.
     */
    void sort();
    /**
    * Retrieves the edge at a given index.
    * @param index Position in the array.
    * @return The edge at the specified index.
    */
    Edge get(int index) const;
    /**
     * Returns the number of edges currently stored.
     * @return Number of edges.
     */
    int size() const;
};

} // graph

#endif //EDGELIST_H
