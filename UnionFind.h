//
// 12adi45@gmail.com
//

#ifndef UNIONFIND_H
#define UNIONFIND_H

namespace graph
{
    /**
    * @class UnionFind
    * @brief Implements the Union-Find (Disjoint Set Union) data structure.
    *
    * This structure supports efficient operations for:
    * - Finding the root representative of a set (`Find`)
    * - Merging two sets (`Union`)
    * - Checking if two elements belong to the same set (`Connected`)
    *
    * It uses path compression and union by rank for optimal performance.
    */
class UnionFind {
    int* parent; // מצביע לנציג הקבוצה
    int* rank; // עומק משוער של כל העץ
public:
    /**
    * @brief Constructor. Initializes `n` disjoint sets, one per node.
    * @param num_vertices Number of initial disjoint sets
    */
    UnionFind(int num_vertices);
    /**
    * @brief Destructor. Frees allocated memory.
    */
    ~UnionFind();
    /**
    * @brief Finds the representative of the set containing `v`.
    * Uses path compression for optimization.
    * @param v Element to search
    * @return Root of the set that `v` belongs to
    */
    int Find(int v);
    /**
     * @brief Merges the sets containing `u` and `v`.
     * Uses union by rank to keep tree flat.
     * @param u First element
     * @param v Second element
     */
    void Union(int u, int v);
    /**
     * @brief Checks whether `u` and `v` belong to the same set.
     * @param u First element
     * @param v Second element
     * @return `true` if both belong to the same set, otherwise `false`
     */
    bool Connected(int u, int v);
};

}
#endif //UNIONFIND_H
