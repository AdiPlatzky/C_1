//
// 12adi45@gmail.com
//

#include "UnionFind.h"
/* Union Find - מבנה נתונים לניהול קבוצות זרות (disjoint sets)
  * מאפשר לבדוק האם שני איברים שייכים לאותה הקבוצה
  * ולאחר מכן לאחד בין קבוצות נפרדות
  * שימושי מאוד באלגוריתמים על גרפים - במטלה זו השימוש במחלקה הנ"ל נעשה ב kurskal
  */
namespace graph
{
    // בנאי - מאתחל n קבוצות נפרדות שכל אחד כוללת איבר אחד
    UnionFind::UnionFind(int n)
    {
        parent = new int[n];              // מערך המכיל את הנציגים של כל איבר
        rank = new int[n];                // עומק מוערך של כל קבוצה (משמש לאיזון העצים)
        for (int i = 0; i < n; i++) {
            parent[i] = i;                // כל איבר הוא נציג של עצמו
            rank[i] = 0;                  // עומק התחלתי 0
        }
    }

   //  שחרור הזיכרון שהוקצה למערכים
    UnionFind:: ~UnionFind()
    {
        delete[] parent;
        delete[] rank;
    }

    // מחזירה את הנציג (השורש) של איבר כלשהו
    // מבצעת דחיסת נתיב לשיפור ביצועים עתידיים
    int UnionFind::Find(int x)
    {
        if (parent[x] != x) {
            parent[x] = Find(parent[x]);
        }
        return parent[x];
    }

    // מאחדת בין 2 קבוצות זרות לפי הדרגה

    void UnionFind::Union(int x, int y)
    {
        int xRoot = Find(x);
        int yRoot = Find(y);

        if (xRoot == yRoot) {
            return;          //כבר באותה קבוצה
        }
        if (rank[xRoot] < rank[yRoot]){
            parent[xRoot] = yRoot;
        }
        else if (rank[xRoot] > rank[yRoot]) {
            parent[yRoot] = xRoot;
        }
        else {
            parent[yRoot] = xRoot;
            rank[xRoot]++;
        }
    }

    // מחזירה האם שני איברים שייכים לאותה הקבוצה (כלומר יש להם את נציג זהה)
    bool UnionFind::Connected(int u, int v)
    {
        return Find(u) == Find(v);
    }
} // graph