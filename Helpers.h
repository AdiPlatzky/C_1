//
// Created by 12adi on 10/04/2025.
//

#ifndef HELPERS_H
#define HELPERS_H
namespace graph {
    template<typename T>
   void deleteAndAdvance(T*& current) {
        if (current != nullptr) {
            T* to_delete = current;
            current = current->next;
            delete to_delete;
        }
    }

    inline bool isInBounds(int value, int min, int max) {
        return value >= min && value <= max;
    }

    const int INF = 1000000000;


}
#endif //HELPERS_H
