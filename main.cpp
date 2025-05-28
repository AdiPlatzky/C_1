// main.cpp - נקודת הכניסה למערכת הויזואליזציה
#include <iostream>
#include <string>

// בדיקה אם SFML זמין
#ifdef SFML_AVAILABLE
#include "GraphVisualizer.h"
#endif

#include "Graph.h"
#include "Algorithms.h"

void showWelcomeMessage() {
    std::cout << "======================================\n";
    std::cout << "   🎯 Graph Algorithms Visualizer   \n";
    std::cout << "======================================\n";
    std::cout << "Developed by: Your Name\n";
    std::cout << "Based on SFML for advanced graphics\n\n";

#ifdef SFML_AVAILABLE
    std::cout << "Instructions:\n";
    std::cout << "- Click with mouse to add nodes\n";
    std::cout << "- Select two nodes to create an edge\n";
    std::cout << "- Use buttons to run algorithms\n";
    std::cout << "- Press ESC to exit\n\n";
    std::cout << "Developed with love for graph algorithms! 💙\n";
#else
    std::cout << "SFML not available - running console demo only\n";
#endif
    std::cout << "======================================\n\n";
}

void runConsoleDemo() {
    std::cout << "Quick console demo of algorithms:\n\n";

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

    std::cout << "Sample graph created with 5 nodes:\n";
    g.print_graph();
    std::cout << "\n";

    // הרצת אלגוריתמים
    std::cout << "🔍 BFS Tree from node 0:\n";
    Graph bfs_tree = Algorithms::bfs(g, g.nodes[0]);
    bfs_tree.print_graph();
    std::cout << "\n";

    std::cout << "🌊 DFS Tree from node 0:\n";
    Graph dfs_tree = Algorithms::dfs(g, g.nodes[0]);
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
            std::cout << "Options:\n";
            std::cout << "  --console, -c     Show console demo\n";
            std::cout << "  --no-gui, -ng     No GUI\n";
            std::cout << "  --help, -h        Show this help\n";
            return 0;
        }
    }

    if (showConsoleDemo) {
        runConsoleDemo();
    }

#ifdef SFML_AVAILABLE
    if (showGUI) {
        try {
            std::cout << "Starting graphical visualization system...\n";

            graph::GraphVisualizer visualizer;

            if (!visualizer.initialize()) {
                std::cerr << "❌ Error: Could not initialize graphical system\n";
                std::cerr << "Make sure SFML is properly installed\n";
                return -1;
            }

            std::cout << "✅ Graphical system started successfully!\n";
            std::cout << "Visualization window opening...\n\n";

            // הרצת הלולאה הראשית
            visualizer.run();

        } catch (const std::exception& e) {
            std::cerr << "❌ Error starting system: " << e.what() << std::endl;
            return -1;
        }
    }
#else
    if (showGUI) {
        std::cout << "❌ GUI requested but SFML not available\n";
        std::cout << "Install SFML and recompile to use GUI mode\n";
        std::cout << "Running console demo instead:\n\n";
        runConsoleDemo();
    }
#endif

    std::cout << "\n🎉 Thanks for using the visualization system!\n";
    std::cout << "System closed successfully.\n";

    return 0;
}