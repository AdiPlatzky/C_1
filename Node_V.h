//
// 12adi45@gmail.com
//

#ifndef NODE_V_H
#define NODE_V_H

namespace graph
{
    /**
   * This class represents a vertex in a graph using a constant numeric identifier.
   * The identifier is immutable once the object is created.
   */
    class Node_V
    {
        public:
        const int id;
        /**
        * Constructor - creates a node with a given ID.
        * @param id the unique identifier for the vertex
        */
        Node_V(int id);
        /**
         * Returns the ID of the node.
         * @return the unique identifier of the vertex
         */
        int get_id() const;
    };
} // graph

#endif //NODE_V_H
