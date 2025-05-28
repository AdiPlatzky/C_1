// GraphVisualizer.h
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <map>
#include <string>
#include "Graph.h"
#include "Algorithms.h"

namespace graph {

// מחלקה לייצוג קודקוד ויזואלי
class VisualNode {
public:
    sf::Vector2f position;
    float radius;
    sf::Color color;
    sf::Color originalColor;
    int id;
    bool isSelected;
    bool isVisited;
    int distance;

    VisualNode(int nodeId, sf::Vector2f pos);
    void draw(sf::RenderWindow& window, sf::Font& font);
    bool contains(sf::Vector2f point) const;
    void setColor(sf::Color newColor);
    void resetColor();
    void highlight();
    void markVisited();
};

// מחלקה לייצוג קשת ויזואלית
class VisualEdge {
public:
    std::shared_ptr<VisualNode> from;
    std::shared_ptr<VisualNode> to;
    int weight;
    sf::Color color;
    sf::Color originalColor;
    bool isHighlighted;

    VisualEdge(std::shared_ptr<VisualNode> fromNode,
               std::shared_ptr<VisualNode> toNode,
               int edgeWeight);
    void draw(sf::RenderWindow& window, sf::Font& font);
    void highlight();
    void resetColor();
};

// מצבי עבודה של המערכת
enum class Mode {
    ADD_NODES,
    ADD_EDGES,
    SELECT_NODES,
    RUN_ALGORITHM
};

// סוגי אלגוריתמים
enum class AlgorithmType {
    NONE,
    BFS,
    DFS,
    DIJKSTRA,
    PRIM,
    KRUSKAL
};

// מחלקה ראשית למערכת הויזואליזציה
class GraphVisualizer {
private:
    sf::RenderWindow window;
    sf::Font font;

    // מבנה הגרף הויזואלי
    std::vector<std::shared_ptr<VisualNode>> visualNodes;
    std::vector<std::shared_ptr<VisualEdge>> visualEdges;

    // מצב המערכת
    Mode currentMode;
    AlgorithmType currentAlgorithm;
    bool isAnimating;

    // בחירות וקלט
    std::shared_ptr<VisualNode> selectedNode;
    std::shared_ptr<VisualNode> firstSelectedNode;
    sf::Vector2f mousePosition;

    // אלמנטי UI
    std::map<std::string, sf::RectangleShape> buttons;
    std::map<std::string, sf::Text> buttonTexts;
    sf::Text statusText;
    sf::Text infoText;

    // אנימציה
    sf::Clock animationClock;
    float animationSpeed;
    std::vector<int> animationQueue;
    size_t currentAnimationStep;

    // הגרף הלוגי (חיבור לקוד שלך)
    std::unique_ptr<Graph> logicalGraph;
    int nodeIdCounter;

public:
    GraphVisualizer();
    ~GraphVisualizer();

    bool initialize();
    void run();

private:
    // אתחול וטעינה
    bool loadFont();
    void setupUI();
    void createButton(const std::string& name,
                     sf::Vector2f position,
                     sf::Vector2f size,
                     const std::string& text,
                     sf::Color color = sf::Color::Blue);

    // לולאה ראשית
    void handleEvents();
    void update();
    void render();

    // טיפול באירועים
    void handleMouseClick(sf::Vector2f mousePos);
    void handleButtonClick(const std::string& buttonName);
    void handleKeyPress(sf::Keyboard::Key key);

    // ניהול קודקודים וקשתות
    void addNode(sf::Vector2f position);
    void addEdge(std::shared_ptr<VisualNode> from, std::shared_ptr<VisualNode> to);
    std::shared_ptr<VisualNode> findNodeAt(sf::Vector2f position);
    void clearGraph();

    // הרצת אלגוריתמים
    void runBFS(int startNodeId);
    void runDFS(int startNodeId);
    void runDijkstra(int startNodeId);
    void runPrim();
    void runKruskal();

    // אנימציה
    void startAnimation(const std::vector<int>& nodeSequence);
    void updateAnimation();
    void resetVisualization();

    // עדכון מצב המערכת
    void setMode(Mode newMode);
    void setAlgorithm(AlgorithmType algorithm);
    void updateStatus(const std::string& message);
    void updateInfo();

    // ציור
    void drawGraph();
    void drawUI();
    void drawNodes();
    void drawEdges();
    void drawButtons();
    void drawTexts();

    // עזרה וכלים
    void showHelp();
    sf::Color getNodeColor(bool visited, bool selected, bool highlighted);
    sf::Color getEdgeColor(bool highlighted);
    std::string modeToString(Mode mode);
    std::string algorithmToString(AlgorithmType algorithm);
};

} // namespace graph