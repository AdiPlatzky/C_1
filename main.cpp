// main.cpp - נקודת הכניסה החדשה למערכת
#include <iostream>
#include <string>
#include "GraphVisualLizer.h"
#include "Graph.h"
#include "Algorithms.h"

void showWelcomeMessage() {
    std::cout << "======================================\n";
    std::cout << "   🎯 מערכת ויזואליזציה לגרפים   \n";
    std::cout << "======================================\n";
    std::cout << "מפותח על ידי: [השם שלך]\n";
    std::cout << "מבוסס על SFML עבור גרפיקה מתקדמת\n\n";
    std::cout << "הוראות שימוש:\n";
    std::cout << "- לחץ עם העכבר כדי להוסיף קודקודים\n";
    std::cout << "- בחר שני קודקודים כדי ליצור קשת\n";
    std::cout << "- השתמש בכפתורים כדי להריץ אלגוריתמים\n";
    std::cout << "- לחץ ESC כדי לצאת\n\n";
    std::cout << "פותח עם אהבה לאלגוריתמי גרפים! 💙\n";
    std::cout << "======================================\n\n";
}

void runConsoleDemo() {
    std::cout << "הדגמה קונסולית מהירה של האלגוריתמים:\n\n";

    using namespace graph;

    // יצירת גרף לדוגמה
    Graph g(5);

    // הוספת קשתות
    g.add_Edge(0, 1, 2);
    g.add_Edge(0, 2, 4);
    g.add_Edge(1, 2, 1);
    g.add_Edge(1, 3, 7);
    g.add_Edge(2, 4, 3);
    g.add_Edge(3, 4, 2);

    std::cout << "גרף לדוגמה נוצר עם 5 קודקודים:\n";
    g.print_graph();
    std::cout << "\n";

    // הרצת אלגוריתמים
    Algorithms algo;

    std::cout << "🔍 BFS Tree מקודקוד 0:\n";
    Graph bfs_tree = algo.bfs(g, g.nodes[0]);
    bfs_tree.print_graph();
    std::cout << "\n";

    std::cout << "🌊 DFS Tree מקודקוד 0:\n";
    Graph dfs_tree = algo.dfs(g, g.nodes[0]);
    dfs_tree.print_graph();
    std::cout << "\n";

    std::cout << "🌳 Prim MST:\n";
    Graph prim_tree = Algorithms::prim(g);
    prim_tree.print_graph();
    std::cout << "\n";

    std::cout << "🔧 Kruskal MST:\n";
    Graph kruskal_tree = Algorithms::kruskal(g);
    kruskal_tree.print_graph();
    std::cout << "\n";
}

int main(int argc, char* argv[]) {
    showWelcomeMessage();

    // בדיקה אם המשתמש רוצה רק הדגמה קונסולית
    bool showConsoleDemo = false;
    bool showGUI = true;

    // ניתוח ארגומנטים
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--console" || arg == "-c") {
            showConsoleDemo = true;
        } else if (arg == "--no-gui" || arg == "-ng") {
            showGUI = false;
        } else if (arg == "--help" || arg == "-h") {
            std::cout << "אפשרויות:\n";
            std::cout << "  --console, -c     הצג הדגמה קונסולית\n";
            std::cout << "  --no-gui, -ng     ללא ממשק גרפי\n";
            std::cout << "  --help, -h        הצג עזרה זו\n";
            return 0;
        }
    }

    if (showConsoleDemo) {
        runConsoleDemo();
    }

    if (showGUI) {
        try {
            std::cout << "מפעיל מערכת ויזואליזציה גרפית...\n";

            graph::GraphVisualizer visualizer;

            if (!visualizer.initialize()) {
                std::cerr << "❌ שגיאה: לא ניתן לאתחל את המערכת הגרפית\n";
                std::cerr << "ודא שמותקן SFML במערכת שלך\n";
                return -1;
            }

            std::cout << "✅ המערכת הגרפית הופעלה בהצלחה!\n";
            std::cout << "חלון הויזואליזציה נפתח...\n\n";

            // הרצת הלולאה הראשית
            visualizer.run();

        } catch (const std::exception& e) {
            std::cerr << "❌ שגיאה בהפעלת המערכת: " << e.what() << std::endl;
            return -1;
        }
    }

    std::cout << "\n🎉 תודה שהשתמשת במערכת הויזואליזציה!\n";
    std::cout << "המערכת נסגרה בהצלחה.\n";

    return 0;
}
// #include <iostream>
// #include "Graph.h"
// int main() {
//     using namespace graph;
//     try {
//         // יוצרים גרף עם 5 צמתים
//         Graph g(5);
//
//         // מוסיפים קשתות
//         g.add_Edge(0, 1);
//         g.add_Edge(0, 2);
//         g.add_Edge(1, 3);
//         g.add_Edge(2, 4);
//         g.add_Edge(3, 4);
//
//         std::cout << "befor the delete:" << std::endl;
//         g.print_graph();
//
//         // מוחקים קשת
//         g.remove_Edge(0, 1);
//
//         std::cout << "after the delete:" << std::endl;
//         g.print_graph();
//
//     } catch (const char* msg) {
//         std::cerr << "error: " << msg << std::endl;
//     }
//
//     return 0;
// }