// main.cpp - נקודת הכניסה המעודכנת למערכת הויזואליזציה המשחקית
#include <iostream>
#include <string>

// בדיקה אם SFML זמין
#ifdef SFML_AVAILABLE
#include "GraphGameVisualizer.h"
#endif

#include "Graph.h"
#include "Algorithms.h"

void showWelcomeMessage() {
    std::cout << "======================================\n";
    std::cout << "   🎯 Graph Algorithms Game System   \n";
    std::cout << "     מערכת לימוד אלגוריתמי גרפים      \n";
    std::cout << "======================================\n";
    std::cout << "Developed by: Your Name\n";
    std::cout << "Educational game system for learning graph algorithms\n\n";

#ifdef SFML_AVAILABLE
    std::cout << "🎮 GAME MODE AVAILABLE!\n";
    std::cout << "Features:\n";
    std::cout << "• Interactive graph visualization\n";
    std::cout << "• Step-by-step algorithm execution\n";
    std::cout << "• Educational animations and explanations\n";
    std::cout << "• BFS, DFS, Dijkstra, Prim, and Kruskal algorithms\n";
    std::cout << "• Kid-friendly interface with colors and animations\n\n";

    std::cout << "Controls:\n";
    std::cout << "• Click nodes to select source vertex\n";
    std::cout << "• Use number keys 1-5 to run algorithms\n";
    std::cout << "• Press SPACE for next step in step-by-step mode\n";
    std::cout << "• Press 'S' to toggle step-by-step/automatic mode\n";
    std::cout << "• Press 'R' to reset visualization\n";
    std::cout << "• Click buttons for easy access\n\n";
#else
    std::cout << "SFML not available - running console demo only\n";
    std::cout << "To enable the game mode, install SFML and recompile\n";
#endif
    std::cout << "======================================\n\n";
}

void runConsoleDemo() {
    std::cout << "🔍 Console Demo - Testing Algorithm Implementations:\n\n";

    using namespace graph;

    // יצירת גרף לדוגמה
    Graph g(6);

    // הוספת קשתות עם משקלים
    g.add_Edge(0, 1, 4);
    g.add_Edge(0, 2, 2);
    g.add_Edge(1, 2, 1);
    g.add_Edge(1, 3, 5);
    g.add_Edge(2, 3, 8);
    g.add_Edge(2, 4, 10);
    g.add_Edge(3, 4, 2);
    g.add_Edge(3, 5, 6);
    g.add_Edge(4, 5, 3);

    std::cout << "📊 Sample graph created with 6 nodes and weighted edges:\n";
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

    std::cout << "📏 Dijkstra shortest paths from node 0:\n";
    Graph dijkstra_tree = Algorithms::dijkstra(g, g.nodes[0]);
    dijkstra_tree.print_graph();
    std::cout << "\n";

    std::cout << "🌳 Prim MST:\n";
    Graph prim_tree = Algorithms::prim(g);
    prim_tree.print_graph();
    std::cout << "\n";

    std::cout << "🔧 Kruskal MST:\n";
    Graph kruskal_tree = Algorithms::kruskal(g);
    kruskal_tree.print_graph();
    std::cout << "\n";

    std::cout << "✅ All algorithms completed successfully!\n";
    std::cout << "💡 Tip: Run with SFML to see the interactive game version!\n\n";
}

int main(int argc, char* argv[]) {
    showWelcomeMessage();

    // ניתוח ארגומנטים
    bool showConsoleDemo = false;
    bool showGUI = true;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--console" || arg == "-c") {
            showConsoleDemo = true;
        } else if (arg == "--no-gui" || arg == "-ng") {
            showGUI = false;
        } else if (arg == "--help" || arg == "-h") {
            std::cout << "🎯 Graph Algorithms Game System - Help\n\n";
            std::cout << "Options:\n";
            std::cout << "  --console, -c     Show console demo\n";
            std::cout << "  --no-gui, -ng     No GUI (console only)\n";
            std::cout << "  --help, -h        Show this help\n\n";
            std::cout << "Examples:\n";
            std::cout << "  " << argv[0] << "                    # Run game mode (if SFML available)\n";
            std::cout << "  " << argv[0] << " --console          # Show console demo + game\n";
            std::cout << "  " << argv[0] << " --no-gui           # Console demo only\n\n";
            return 0;
        }
    }

    if (showConsoleDemo) {
        runConsoleDemo();
    }

#ifdef SFML_AVAILABLE
    if (showGUI) {
        try {
            std::cout << "🎮 Starting Graph Algorithms Game System...\n";

            GraphGame::GraphGameVisualizer gameVisualizer;

            if (!gameVisualizer.initialize()) {
                std::cerr << "❌ Error: Could not initialize game system\n";
                std::cerr << "Make sure SFML is properly installed and fonts are available\n";
                return -1;
            }

            std::cout << "✅ Game system initialized successfully!\n";
            std::cout << "🎯 Opening interactive visualization window...\n\n";

            std::cout << "🎓 EDUCATIONAL FEATURES:\n";
            std::cout << "• Watch algorithms work step-by-step\n";
            std::cout << "• See data structures (queues, stacks) in action\n";
            std::cout << "• Learn time and space complexity\n";
            std::cout << "• Experiment with different graphs\n";
            std::cout << "• Perfect for students and visual learners!\n\n";

            // הרצת הלולאה הראשית של המשחק
            gameVisualizer.run();

        } catch (const std::exception& e) {
            std::cerr << "❌ Error starting game system: " << e.what() << std::endl;
            std::cerr << "💡 Try running with --console flag for demo mode\n";
            return -1;
        }
    }
#else
    if (showGUI) {
        std::cout << "❌ GUI requested but SFML not available\n";
        std::cout << "📚 Install SFML and recompile to use interactive game mode\n";
        std::cout << "🖥️  Running console demo instead:\n\n";
        runConsoleDemo();
    }
#endif

    std::cout << "\n🎉 Thank you for using the Graph Algorithms Game System!\n";
    std::cout << "🎓 Keep learning and exploring algorithms!\n";
    std::cout << "System closed successfully.\n";

    return 0;
}