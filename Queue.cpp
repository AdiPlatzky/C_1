//
// 12adi45@gmail.com
//

#include "Queue.h"

namespace graph
{
    // בנאי שמאתחל תור ריק
    Queue::Queue(Node_In_Queue *head, Node_In_Queue *tail): head(head), tail(tail), size(0) {}

    //פעולת הרס – מנקה את כל האיברים מהתור ומשחררת את הזיכרון
    Queue::~Queue() {
        Node_In_Queue* current = head;
        while (current != nullptr) {
            Node_In_Queue* next = current->next_n;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    // הוספת איבר חדש לסוף התור
    void Queue::enqueue(Node_V *node)
    {
        Node_In_Queue *newNode = new Node_In_Queue(node);
        if (is_empty()) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next_n = newNode;
            newNode->prev_n = tail;
            tail = newNode;
        }
        size++;
    }

    // פעולת הוצאה - מוציאה את האיבר הראשון מהתור ומחזירה אותו
    //  אם התור ריק – נזרקת חריגה
    Node_V *Queue::dequeue()
    {
        if (is_empty())
        {
            throw "Queue is empty";
        }
        Node_In_Queue* temp = head;
        Node_V *node = temp->original;
        head = head->next_n;

        if (head != nullptr)
        {
            head->prev_n = nullptr;
        }
        else
        {
            tail = nullptr;
        }
        delete temp;
        size--;
        return node;
    }

    // מחזירה true אם אין אף איבר בתור
    bool Queue::is_empty()const {
        if (size == 0) {
            return true;
        }
        return false;
    }
} // graph