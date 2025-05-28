//
// 12adi45@gmail.com
//

#include "Node_V.h"

namespace graph
{
    //בנאי - מאחסן את המזהה במשתנה הקבוע של המחלקה
    Node_V::Node_V(int id): id(id) {}

    // מחזיר את המזהה של הקודקוד
    int Node_V::get_id() const {
        return id;
    }
} // graph
