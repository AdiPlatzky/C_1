//
// Created by 12adi on 22/05/2025.
//

#include "EdgeList.h"

namespace graph
{
    EdgeList::EdgeList(int initial_size) : capacity(initial_size), count(0)
    {
        data = new Edge[capacity];
    }

    EdgeList::~EdgeList() {
        delete[] data;
    }

    void EdgeList::resize() {
        capacity *= 2;
        Edge* new_data = new Edge[capacity];
        for (int i = 0; i < count; i++) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
    }

    void EdgeList::add(const Edge &edge) {
        if (count == capacity) {
            resize();
        }
        data[count++] = edge;
    }

    Edge EdgeList::get(int index) const {
        return data[index];
    }

    int EdgeList::size() const {
        return count;
    }

    void EdgeList::sort() {
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (data[j].weight > data[j + 1].weight) {
                    Edge temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }






} // graph