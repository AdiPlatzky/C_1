//
// 12adi45@gmail.com
//

#include "PropertyQueue.h"
#include "Helpers.h"

namespace graph {
    // בנאי – אתחול ראש הרשימה כ-nullptr
    PropertyQueue::PropertyQueue() : head(nullptr) {}

    // פונקציית השמדה – שחרור כל הזיכרון שהוקצה
    PropertyQueue::~PropertyQueue()
    {
        while (head != nullptr) {
            deleteAndAdvance(head);
        }
    }

    // מוסיף קודקוד חדש לרשימה במקום המתאים לפי ערך העדיפות
    void PropertyQueue::insert(Node_V* node_v, int priority, Node_V* parent_v)
    {
        PQNode* newNode = new PQNode(node_v, priority, parent_v);

        // אם הרשימה ריקה או הקודקוד החדש צריך להיות בראש
        if (head == nullptr || newNode->d < head->d) {
            newNode->next = head;
            head = newNode;
            return;
        }

        // חיפוש המקום המתאים והכנסת הקודקוד באמצע
        PQNode* curr = head;
        while (curr->next != nullptr && curr->next->d <= newNode->d) {
            curr = curr->next;
        }

        newNode->next = curr->next;
        curr->next = newNode;
    }

    // מחזיר את הקודקוד עם העדיפות הנמוכה ביותר ומסיר אותו מהרשימה
    Node_V* PropertyQueue::extractMin()
    {
        if (head == nullptr)
            throw "priority queue is empty";

        Node_V* minD = head->node;
        deleteAndAdvance(head);
        return minD;
    }

    // בדיקה אם התור ריק
    bool PropertyQueue::isEmpty() const
    {
        return head == nullptr;
    }

    // מפחית את ערך העדיפות של קודקוד קיים בתור ומעדכן את מקומו
    void PropertyQueue::decreaseKey(Node_V* node_v, int new_priority, Node_V* newParent_v) {
        if (head == nullptr) return;
        PQNode* curr = head;
        PQNode* prev = nullptr;

        // חיפוש הקודקוד ברשימה
        while (curr != nullptr && curr->node != node_v) {
            prev = curr;
            curr = curr->next;
        }

        if (curr == nullptr) return; // לא נמצא

        if (new_priority >= curr->d) return; // אין הפחתה אמיתית

        // הסרת הקודקוד מהמקום הישן והכנסה מחדש
        if (prev == nullptr) {
            head = curr->next;
        }
        else {
            prev->next = curr->next;
        }
        delete curr;

        insert(node_v, new_priority, newParent_v);
    }

    // מחזיר אמת אם הקודקוד נמצא בתור
    bool PropertyQueue::contains(Node_V* node_v) {
        PQNode* curr = head;
        while (curr != nullptr) {
            if (curr->node == node_v) {
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    // מחזיר את ההורה של קודקוד מסוים אם נמצא בתור
    Node_V* PropertyQueue::getParent(Node_V* node_v)const {
        PQNode* curr = head;
        while (curr != nullptr) {
            if (curr->node == node_v) {
                return curr->key_pai;
            }
            curr = curr->next;
        }
        return nullptr;
    }
} // graph