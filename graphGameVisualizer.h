//
// Created by 12adi on 29/05/2025.
//

#ifndef RAPHGAMEVISUALIZER_H
#define RAPHGAMEVISUALIZER_H

#endif //RAPHGAMEVISUALIZER_H
//
// GraphGameVisualizer.h - מערכת ויזואליזציה משחקית לאלגוריתמי גרפים
// מותאמת לילדים ונוער - הצגה אטרקטיבית וחוויתית של אלגוריתמים
//

#ifndef GRAPH_GAME_VISUALIZER_H
#define GRAPH_GAME_VISUALIZER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <memory>
#include <chrono>

// הכללת המחלקות שלך
#include "Graph.h"
#include "Algorithms.h"
#include "Node_V.h"
#include "PropertyQueue.h"
#include "Queue.h"
#include "UnionFind.h"
#include "EdgeList.h"

namespace GraphGame {

// מבנה לאחסון מיקום ויזואלי של קודקוד
struct VisualNode {
    int id;
    sf::Vector2f position;
    sf::Color color;
    std::string label;
    int distance;  // למרחק ב-BFS/Dijkstra
    graph::Node_V* parent;  // להורה באלגוריתמים
    bool visited;
    float animationScale;
    sf::Clock animationClock;

    VisualNode() : id(-1), color(sf::Color::White), label(""),
                   distance(999999), parent(nullptr), visited(false),
                   animationScale(1.0f) {}

    VisualNode(int nodeId, sf::Vector2f pos) :
        id(nodeId), position(pos), color(sf::Color::Cyan),
        label(std::to_string(nodeId)), distance(999999),
        parent(nullptr), visited(false), animationScale(1.0f) {}
};

// מבנה לאחסון קשת ויזואלית
struct VisualEdge {
    int from, to;
    int weight;
    sf::Color color;
    bool highlighted;
    bool inMST;  // לאלגוריתמי MST
    float animationProgress;

    VisualEdge(int f, int t, int w = 1) :
        from(f), to(t), weight(w), color(sf::Color::White),
        highlighted(false), inMST(false), animationProgress(0.0f) {}
};

// סוגי אלגוריתמים
enum class AlgorithmType {
    BFS,
    DFS,
    DIJKSTRA,
    PRIM,
    KRUSKAL,
    NONE
};

// שלבי האלגוריתמים
enum class AlgorithmStep {
    INIT,
    PROCESSING,
    COMPLETED,
    STEP_BY_STEP
};

// תור ויזואלי למבני נתונים
class VisualQueue {
private:
    std::vector<int> items;
    sf::RectangleShape background;
    sf::Font font;
    std::string title;
    sf::Vector2f position;

public:
    VisualQueue(const std::string& queueTitle, sf::Vector2f pos);
    void push(int nodeId);
    int pop();
    bool empty() const { return items.empty(); }
    void clear();
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f pos) { position = pos; }
    size_t size() const { return items.size(); }
};

// ערימה ויזואלית ל-DFS
class VisualStack {
private:
    std::vector<int> items;
    sf::RectangleShape background;
    sf::Font font;
    std::string title;
    sf::Vector2f position;

public:
    VisualStack(const std::string& stackTitle, sf::Vector2f pos);
    void push(int nodeId);
    int pop();
    bool empty() const { return items.empty(); }
    void clear();
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f pos) { position = pos; }
    size_t size() const { return items.size(); }
};

// תור עדיפויות ויזואלי
class VisualPriorityQueue {
private:
    std::vector<std::pair<int, int>> items; // (priority, nodeId)
    sf::RectangleShape background;
    sf::Font font;
    std::string title;
    sf::Vector2f position;

public:
    VisualPriorityQueue(const std::string& pqTitle, sf::Vector2f pos);
    void push(int nodeId, int priority);
    int pop();
    bool empty() const { return items.empty(); }
    void clear();
    void draw(sf::RenderWindow& window);
    void decreaseKey(int nodeId, int newPriority);
    void setPosition(sf::Vector2f pos) { position = pos; }
};

// לוח מידע אלגוריתם
class AlgorithmInfoPanel {
private:
    sf::RectangleShape background;
    sf::Font font;
    sf::Text titleText;
    sf::Text descriptionText;
    sf::Text stepText;
    sf::Text complexityText;
    sf::Vector2f position;
    AlgorithmType currentAlgorithm;

public:
    AlgorithmInfoPanel(sf::Vector2f pos);
    void setAlgorithm(AlgorithmType algo);
    void setStep(const std::string& step);
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f pos) { position = pos; }
};

// המערכת הראשית של המשחק
class GraphGameVisualizer {
private:
    // SFML Components
    sf::RenderWindow window;
    sf::Font font;
    sf::Clock clock;
    sf::Clock animationClock;

    // Graph data
    std::unique_ptr<graph::Graph> gameGraph;
    std::vector<VisualNode> visualNodes;
    std::vector<VisualEdge> visualEdges;

    // UI Components
    std::unique_ptr<VisualQueue> bfsQueue;
    std::unique_ptr<VisualStack> dfsStack;
    std::unique_ptr<VisualPriorityQueue> priorityQueue;
    std::unique_ptr<AlgorithmInfoPanel> infoPanel;

    // Game state
    AlgorithmType currentAlgorithm;
    AlgorithmStep currentStep;
    bool isAnimating;
    bool stepByStepMode;
    int currentAnimationNode;
    int sourceNode;

    // Algorithm results
    std::unique_ptr<graph::Graph> algorithmResult;

    // UI Buttons
    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;
    std::vector<std::string> buttonLabels;

    // Colors for different states
    static const sf::Color COLOR_UNVISITED;
    static const sf::Color COLOR_VISITING;
    static const sf::Color COLOR_VISITED;
    static const sf::Color COLOR_SOURCE;
    static const sf::Color COLOR_PATH;
    static const sf::Color COLOR_MST_EDGE;
    static const sf::Color COLOR_CURRENT_EDGE;

public:
    GraphGameVisualizer();
    ~GraphGameVisualizer();

    // Main game loop
    bool initialize();
    void run();
    void cleanup();

    // Graph creation and management
    void createSampleGraph();
    void createRandomGraph(int numNodes);
    void addVisualNode(int id, sf::Vector2f position);
    void addVisualEdge(int from, int to, int weight = 1);
    void clearGraph();

    // Algorithm execution
    void runBFS(int startNode);
    void runDFS(int startNode);
    void runDijkstra(int startNode);
    void runPrim();
    void runKruskal();
    void resetAlgorithmVisualization();

    // Step-by-step execution
    void nextStep();
    void previousStep();
    void toggleStepByStepMode();

    // Event handling
    void handleEvents();
    void handleMouseClick(sf::Vector2i mousePos);
    void handleKeyPress(sf::Keyboard::Key key);

    // Rendering
    void render();
    void renderGraph();
    void renderNodes();
    void renderEdges();
    void renderUI();
    void renderButtons();
    void renderInstructions();

    // Animations
    void updateAnimations();
    void animateNode(int nodeId, sf::Color newColor);
    void animateEdge(int from, int to, sf::Color newColor);
    void highlightPath(const std::vector<int>& path);

    // Utility functions
    sf::Vector2f getNodePosition(int nodeId);
    int getNodeAtPosition(sf::Vector2i position);
    void generateCircularLayout();
    void generateRandomLayout();

    // Educational features
    void showAlgorithmExplanation(AlgorithmType algo);
    void displayComplexityInfo(AlgorithmType algo);
    void showStepExplanation(const std::string& explanation);
};

// פונקציות עזר גלובליות
namespace Utils {
    sf::Color interpolateColor(sf::Color from, sf::Color to, float t);
    std::string algorithmToString(AlgorithmType algo);
    std::string getAlgorithmDescription(AlgorithmType algo);
    std::string getComplexityInfo(AlgorithmType algo);
    sf::Vector2f polarToCartesian(float radius, float angle, sf::Vector2f center);
}

} // namespace GraphGame

#endif // GRAPH_GAME_VISUALIZER_H