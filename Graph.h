//
// 12adi45@gmail.com
//
#ifndef GRAPH_H
#define GRAPH_H
#include "Node_V.h"
#include "Helpers.h"

namespace graph
{
    /**
    * Data structure representing a neighbor in an adjacency list.
    * Holds the destination vertex index, the edge weight, and a pointer
    * to the next neighbor in the linked list.
    */
    struct Neighbor
    {
        int dest;
        int weight;
        Neighbor* next; // מצביע על מי שהקודם הצביע עליו

        Neighbor(int dest, int weight, Neighbor* next = nullptr)
            : dest(dest), weight(weight), next(next) {}
    };

    /**
     * Class representing an undirected weighted graph.
     * The graph is implemented using adjacency lists for each vertex.
     */
    class Graph {
    public:
        const int num_vertices;
        Node_V** nodes; //מערך של קודקודים
        Neighbor** adjacency_list; // מערך של רשימת שכנויות
        /**
        * Constructor - creates a graph with the given number of vertices and no edges.
        */
        Graph(int num_vertices);
        /**
        * Destructor - releases memory used for vertices and adjacency lists.
        */
        ~Graph();
        /**
        * Adds a bidirectional edge between two vertices with an optional weight (default is 1).
        */
        void add_Edge(int from, int to, int weight = 1) const;
        /**
        * Removes a bidirectional edge between two vertices if it exists.
        */
        void remove_Edge(int from, int to) const;
        /**
        * Prints all the edges in the graph to the console, avoiding duplicates.
        */
        void print_graph() const;
        /**
        * Returns the number of vertices in the graph.
        */
        int getNumVertices() const {return num_vertices;}
    };
} // graph

#endif //GRAPH_H
