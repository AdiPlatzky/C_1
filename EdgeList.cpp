//
// 12adi45@gmail.com
//

#include "EdgeList.h"

#include <cstdlib>
#include <stdlib.h>

namespace graph
{
    // בנאי - מאתחל מערך של קשתות בגודל התחלתי
    EdgeList::EdgeList(int initial_size) : capacity(initial_size), count(0)
    {
        data = new Edge[capacity];
    }

    // הורס את הרשימה - משחרר את הזיכרון הדינאמי שהוקצה
    EdgeList::~EdgeList() {
        delete[] data;
    }
    // פונקציה פנימית שמכפילה את גודל המערך כשאין מספיק מקום
    // מעתיקה את כל הקשתות למערך חדש
    void EdgeList::resize() {
        capacity *= 2;
        Edge* new_data = new Edge[capacity];
        for (int i = 0; i < count; i++) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
    }
    // מוסיף קשת חדשה לרשימה. אם אין מקום - מבצע הגדלה אוטומטית
    void EdgeList::add(const Edge &edge) {
        if (count == capacity) {
            resize();
        }
        data[count++] = edge;
    }

    // מחזיר את הקשת שבאינדקס המבוקש
    Edge EdgeList::get(int index) const {
        return data[index];
    }

    // מחזיר את מספר הקשתות שנמצאות כרגע ברשימה
    int EdgeList::size() const {
        return count;
    }

    // ממיין את רשימת הקשתות לפי המשקל מהקל לכבד
    // מממש מיון בועתי (Quick Sort) - פשוט אך לא יעיל כלכך
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