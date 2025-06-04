//
// 12adi45@gmail.com
//
#ifndef HELPERS_H
#define HELPERS_H
namespace graph
{
    /**
    * A generic utility function that deletes the current object and advances
    * the pointer to the next in a linked list structure.
    * Useful for safely iterating and deleting linked list elements.
    *
    * @tparam T The type of the node (e.g., Neighbor, PQNode, etc.)
    * @param current A reference to the pointer of the current node to delete
    */
    template<typename T>
   void deleteAndAdvance(T*& current) {
        if (current != nullptr) {
            T* to_delete = current;
            current = current->next;
            delete to_delete;
        }
    }
    /**
    * Utility function to check if a value is within a specified range (inclusive).
    *
    * @param value The value to check
    * @param min The lower bound of the range
    * @param max The upper bound of the range
    * @return true if value is within [min, max], false otherwise
    */
    inline bool isInBounds(int value, int min, int max) {
        return value >= min && value <= max;
    }
    /**
    * Constant representing "infinity", typically used in graph algorithms
    * like Dijkstra and Prim to initialize distances.
    */
    const int INF = 1000000000;

}
#endif //HELPERS_H
