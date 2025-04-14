#include <iostream>

#include "Graph.h"


#include <iostream>
#include "Graph.h"
int main() {
    using namespace graph;
    try {
        // יוצרים גרף עם 5 צמתים
        Graph g(5);

        // מוסיפים קשתות
        g.add_Edge(0, 1);
        g.add_Edge(0, 2);
        g.add_Edge(1, 3);
        g.add_Edge(2, 4);
        g.add_Edge(3, 4);

        std::cout << "befor the delete:" << std::endl;
        g.print_graph();

        // מוחקים קשת
        g.remove_Edge(0, 1);

        std::cout << "after the delete:" << std::endl;
        g.print_graph();

    } catch (const char* msg) {
        std::cerr << "error: " << msg << std::endl;
    }

    return 0;
}