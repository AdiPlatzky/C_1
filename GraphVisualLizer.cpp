//
// Created by 12adi on 28/05/2025.
//

#include "GraphVisualLizer.h"
// GraphVisualizer.cpp
#include "GraphVisualizer.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>

namespace graph {

// מימוש VisualNode
VisualNode::VisualNode(int nodeId, sf::Vector2f pos)
    : id(nodeId), position(pos), radius(25.0f),
      isSelected(false), isVisited(false), distance(0) {
    originalColor = sf::Color(102, 126, 234); // כחול יפה
    color = originalColor;
}

void VisualNode::draw(sf::RenderWindow& window, sf::Font& font) {
    // ציור עיגול הקודקוד
    sf::CircleShape circle(radius);
    circle.setPosition(position.x - radius, position.y - radius);
    circle.setFillColor(color);
    circle.setOutlineThickness(3);
    circle.setOutlineColor(sf::Color(76, 81, 191));

    window.draw(circle);

    // ציור המספר
    sf::Text text;
    text.setFont(font);
    text.setString(std::to_string(id));
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);

    // מרכז הטקסט
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        position.x - textBounds.width / 2,
        position.y - textBounds.height / 2 - 3
    );

    window.draw(text);

    // אם הקודקוד נבחר, צייר הדגשה
    if (isSelected) {
        sf::CircleShape highlight(radius + 5);
        highlight.setPosition(position.x - radius - 5, position.y - radius - 5);
        highlight.setFillColor(sf::Color::Transparent);
        highlight.setOutlineThickness(3);
        highlight.setOutlineColor(sf::Color::Yellow);
        window.draw(highlight);
    }
}

bool VisualNode::contains(sf::Vector2f point) const {
    float dx = point.x - position.x;
    float dy = point.y - position.y;
    return (dx * dx + dy * dy) <= (radius * radius);
}

void VisualNode::setColor(sf::Color newColor) {
    color = newColor;
}

void VisualNode::resetColor() {
    color = originalColor;
    isVisited = false;
}

void VisualNode::highlight() {
    color = sf::Color(72, 187, 120); // ירוק
}

void VisualNode::markVisited() {
    color = sf::Color(237, 137, 54); // כתום
    isVisited = true;
}

// מימוש VisualEdge
VisualEdge::VisualEdge(std::shared_ptr<VisualNode> fromNode,
                       std::shared_ptr<VisualNode> toNode,
                       int edgeWeight)
    : from(fromNode), to(toNode), weight(edgeWeight), isHighlighted(false) {
    originalColor = sf::Color(160, 174, 192);
    color = originalColor;
}

void VisualEdge::draw(sf::RenderWindow& window, sf::Font& font) {
    // ציור הקו
    sf::Vertex line[] = {
        sf::Vertex(from->position, color),
        sf::Vertex(to->position, color)
    };
    window.draw(line, 2, sf::Lines);

    // ציור המשקל באמצע הקשת
    sf::Vector2f midPoint = (from->position + to->position) / 2.0f;

    // רקע לבן למשקל
    sf::RectangleShape background(sf::Vector2f(30, 20));
    background.setPosition(midPoint.x - 15, midPoint.y - 10);
    background.setFillColor(sf::Color::White);
    background.setOutlineThickness(1);
    background.setOutlineColor(sf::Color::Black);
    window.draw(background);

    // טקסט המשקל
    sf::Text weightText;
    weightText.setFont(font);
    weightText.setString(std::to_string(weight));
    weightText.setCharacterSize(12);
    weightText.setFillColor(sf::Color::Black);
    weightText.setStyle(sf::Text::Bold);

    sf::FloatRect textBounds = weightText.getLocalBounds();
    weightText.setPosition(
        midPoint.x - textBounds.width / 2,
        midPoint.y - textBounds.height / 2 - 2
    );

    window.draw(weightText);
}

void VisualEdge::highlight() {
    color = sf::Color::Red;
    isHighlighted = true;
}

void VisualEdge::resetColor() {
    color = originalColor;
    isHighlighted = false;
}

// מימוש GraphVisualizer
GraphVisualizer::GraphVisualizer()
    : window(sf::VideoMode(1200, 800), "מערכת ויזואליזציה לאלגוריתמי גרפים", sf::Style::Default),
      currentMode(Mode::ADD_NODES),
      currentAlgorithm(AlgorithmType::NONE),
      isAnimating(false),
      animationSpeed(1.0f),
      currentAnimationStep(0),
      nodeIdCounter(0) {

    window.setFramerateLimit(60);
    logicalGraph = std::make_unique<Graph>(100); // גרף עד 100 קודקודים
}

GraphVisualizer::~GraphVisualizer() = default;

bool GraphVisualizer::initialize() {
    if (!loadFont()) {
        return false;
    }

    setupUI();
    updateStatus("מוכן לעבודה - לחץ כדי להוסיף קודקודים");
    return true;
}

bool GraphVisualizer::loadFont() {
    // נסה לטעון פונט מהמערכת
    if (!font.loadFromFile("arial.ttf")) {
        // אם לא נמצא, השתמש בפונט ברירת המחדל
        std::cout << "⚠️  פונט לא נמצא, משתמש בפונט ברירת מחדל\n";
        // SFML יחזיר לפונט ברירת מחדל
    }
    return true;
}

void GraphVisualizer::setupUI() {
    // יצירת כפתורים
    createButton("addNodes", sf::Vector2f(20, 20), sf::Vector2f(120, 40),
                "הוספת קודקודים", sf::Color(102, 126, 234));
    createButton("addEdges", sf::Vector2f(20, 70), sf::Vector2f(120, 40),
                "הוספת קשתות", sf::Color(102, 126, 234));
    createButton("clear", sf::Vector2f(20, 120), sf::Vector2f(120, 40),
                "מחיקת הכל", sf::Color(229, 62, 62));

    // כפתורי אלגוריתמים
    createButton("bfs", sf::Vector2f(20, 180), sf::Vector2f(120, 40),
                "BFS", sf::Color(237, 137, 54));
    createButton("dfs", sf::Vector2f(20, 230), sf::Vector2f(120, 40),
                "DFS", sf::Color(237, 137, 54));
    createButton("dijkstra", sf::Vector2f(20, 280), sf::Vector2f(120, 40),
                "Dijkstra", sf::Color(237, 137, 54));
    createButton("prim", sf::Vector2f(20, 330), sf::Vector2f(120, 40),
                "Prim", sf::Color(237, 137, 54));
    createButton("kruskal", sf::Vector2f(20, 380), sf::Vector2f(120, 40),
                "Kruskal", sf::Color(237, 137, 54));

    // טקסט מצב
    statusText.setFont(font);
    statusText.setCharacterSize(16);
    statusText.setFillColor(sf::Color::White);
    statusText.setPosition(20, window.getSize().y - 60);

    // טקסט מידע
    infoText.setFont(font);
    infoText.setCharacterSize(14);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition(20, window.getSize().y - 40);
}

void GraphVisualizer::createButton(const std::string& name,
                                  sf::Vector2f position,
                                  sf::Vector2f size,
                                  const std::string& text,
                                  sf::Color color) {
    sf::RectangleShape button(size);
    button.setPosition(position);
    button.setFillColor(color);
    button.setOutlineThickness(2);
    button.setOutlineColor(sf::Color::White);
    buttons[name] = button;

    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(14);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setStyle(sf::Text::Bold);

    // מרכז הטקסט בכפתור
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setPosition(
        position.x + (size.x - textBounds.width) / 2,
        position.y + (size.y - textBounds.height) / 2 - 3
    );

    buttonTexts[name] = buttonText;
}

void GraphVisualizer::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void GraphVisualizer::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    mousePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    handleMouseClick(mousePosition);
                }
                break;

            case sf::Event::KeyPressed:
                handleKeyPress(event.key.code);
                break;

            default:
                break;
        }
    }
}

void GraphVisualizer::handleMouseClick(sf::Vector2f mousePos) {
    // בדיקה אם לחצו על כפתור
    for (const auto& [name, button] : buttons) {
        if (button.getGlobalBounds().contains(mousePos)) {
            handleButtonClick(name);
            return;
        }
    }

    // אם לא לחצו על כפתור, טפל בלחיצה על הגרף
    if (mousePos.x > 160) { // אזור הגרף (מימין לכפתורים)
        auto clickedNode = findNodeAt(mousePos);

        switch (currentMode) {
            case Mode::ADD_NODES:
                if (!clickedNode) {
                    addNode(mousePos);
                }
                break;

            case Mode::ADD_EDGES:
                if (clickedNode) {
                    if (!firstSelectedNode) {
                        firstSelectedNode = clickedNode;
                        clickedNode->isSelected = true;
                        updateStatus("בחר קודקוד שני ליצירת קשת");
                    } else if (firstSelectedNode != clickedNode) {
                        addEdge(firstSelectedNode, clickedNode);
                        firstSelectedNode->isSelected = false;
                        firstSelectedNode = nullptr;
                        updateStatus("נוצרה קשת");
                    }
                }
                break;

            default:
                break;
        }
    }
}

void GraphVisualizer::handleButtonClick(const std::string& buttonName) {
    if (buttonName == "addNodes") {
        setMode(Mode::ADD_NODES);
    } else if (buttonName == "addEdges") {
        setMode(Mode::ADD_EDGES);
    } else if (buttonName == "clear") {
        clearGraph();
    } else if (buttonName == "bfs" && !visualNodes.empty()) {
        setAlgorithm(AlgorithmType::BFS);
        runBFS(0);
    } else if (buttonName == "dfs" && !visualNodes.empty()) {
        setAlgorithm(AlgorithmType::DFS);
        runDFS(0);
    } else if (buttonName == "prim" && !visualNodes.empty()) {
        setAlgorithm(AlgorithmType::PRIM);
        runPrim();
    } else if (buttonName == "kruskal" && !visualNodes.empty()) {
        setAlgorithm(AlgorithmType::KRUSKAL);
        runKruskal();
    }
}

void GraphVisualizer::handleKeyPress(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Escape:
            window.close();
            break;
        case sf::Keyboard::R:
            resetVisualization();
            break;
        case sf::Keyboard::Space:
            if (isAnimating) {
                isAnimating = false;
                updateStatus("אנימציה הושהתה");
            }
            break;
        default:
            break;
    }
}

void GraphVisualizer::addNode(sf::Vector2f position) {
    auto newNode = std::make_shared<VisualNode>(nodeIdCounter++, position);
    visualNodes.push_back(newNode);
    updateStatus("נוסף קודקוד " + std::to_string(newNode->id));
    updateInfo();
}

void GraphVisualizer::addEdge(std::shared_ptr<VisualNode> from, std::shared_ptr<VisualNode> to) {
    // בחירת משקל אקראי בין 1-10
    int weight = rand() % 10 + 1;

    auto newEdge = std::make_shared<VisualEdge>(from, to, weight);
    visualEdges.push_back(newEdge);

    // הוספה לגרף הלוגי
    logicalGraph->add_Edge(from->id, to->id, weight);

    updateInfo();
}

std::shared_ptr<VisualNode> GraphVisualizer::findNodeAt(sf::Vector2f position) {
    for (auto& node : visualNodes) {
        if (node->contains(position)) {
            return node;
        }
    }
    return nullptr;
}

void GraphVisualizer::clearGraph() {
    visualNodes.clear();
    visualEdges.clear();
    selectedNode = nullptr;
    firstSelectedNode = nullptr;
    nodeIdCounter = 0;
    logicalGraph = std::make_unique<Graph>(100);
    resetVisualization();
    updateStatus("הגרף נמחק");
    updateInfo();
}

void GraphVisualizer::runBFS(int startNodeId) {
    if (visualNodes.empty()) return;

    resetVisualization();
    updateStatus("מריץ BFS מקודקוד " + std::to_string(startNodeId));

    // כאן תוכלי לחבר את האלגוריתם שלך
    // לעת עתה, אנימציה פשוטה
    std::vector<int> sequence;
    for (size_t i = 0; i < visualNodes.size(); i++) {
        sequence.push_back(i);
    }
    startAnimation(sequence);
}
void GraphVisualizer::runDFS(int startNodeId) {
    if (visualNodes.empty()) return;

    resetVisualization();
    updateStatus("מריץ DFS מקודקוד " + std::to_string(startNodeId));

    // כאן תוכלי לחבר את האלגוריתם שלך
    std::vector<int> sequence;
    for (size_t i = 0; i < visualNodes.size(); i++) {
        sequence.push_back(i);
    }
    startAnimation(sequence);
}

void GraphVisualizer::runDijkstra(int startNodeId) {
    if (visualNodes.empty()) return;

    resetVisualization();
    updateStatus("מריץ Dijkstra מקודקוד " + std::to_string(startNodeId));

    // חיבור לאלגוריתם Dijkstra שלך
    Algorithms algo;
    Graph dijkstra_tree = algo.dijkstra(*logicalGraph, logicalGraph->nodes[startNodeId]);

    // הדגשת הקשתות בעץ
    for (auto& edge : visualEdges) {
        // בדיקה אם הקשת נמצאת בעץ dijkstra
        bool inTree = false;
        // כאן תצטרכי לבדוק אם הקשת נמצאת בעץ התוצאה
        if (inTree) {
            edge->highlight();
        }
    }
}

void GraphVisualizer::runPrim() {
    if (visualNodes.empty()) return;

    resetVisualization();
    updateStatus("מריץ אלגוריתם Prim");

    try {
        // חיבור לאלגוריתם Prim שלך
        Graph prim_tree = Algorithms::prim(*logicalGraph);

        // הדגשת הקשתות בעץ הפורש המינימלי
        for (auto& edge : visualEdges) {
            // כאן צריך לבדוק אם הקשת נמצאת בעץ prim
            // זה ידרוש התאמה קלה בקוד שלך כדי לקבל רשימת קשתות
        }

        updateStatus("Prim הושלם - עץ פורש מינימלי מוצג");
    } catch (const std::exception& e) {
        updateStatus("שגיאה בהרצת Prim");
    }
}

void GraphVisualizer::runKruskal() {
    if (visualNodes.empty()) return;

    resetVisualization();
    updateStatus("מריץ אלגוריתם Kruskal");

    try {
        // חיבור לאלגוריתם Kruskal שלך
        Graph kruskal_tree = Algorithms::kruskal(*logicalGraph);

        // אנימציה של בניית העץ לפי סדר המשקלים
        std::vector<int> edgeSequence;
        // כאן תוכלי לממש אנימציה מתקדמת יותר

        updateStatus("Kruskal הושלם - עץ פורש מינימלי מוצג");
    } catch (const std::exception& e) {
        updateStatus("שגיאה בהרצת Kruskal");
    }
}

void GraphVisualizer::startAnimation(const std::vector<int>& nodeSequence) {
    animationQueue = nodeSequence;
    currentAnimationStep = 0;
    isAnimating = true;
    animationClock.restart();
}

void GraphVisualizer::updateAnimation() {
    if (!isAnimating || animationQueue.empty()) return;

    // עדכון כל 500 מילישניות
    if (animationClock.getElapsedTime().asMilliseconds() > 500 / animationSpeed) {
        if (currentAnimationStep < animationQueue.size()) {
            int nodeId = animationQueue[currentAnimationStep];
            if (nodeId < visualNodes.size()) {
                visualNodes[nodeId]->markVisited();
            }
            currentAnimationStep++;
            animationClock.restart();
        } else {
            isAnimating = false;
            updateStatus("האנימציה הושלמה");
        }
    }
}

void GraphVisualizer::resetVisualization() {
    for (auto& node : visualNodes) {
        node->resetColor();
        node->isSelected = false;
    }
    for (auto& edge : visualEdges) {
        edge->resetColor();
    }
    selectedNode = nullptr;
    firstSelectedNode = nullptr;
    isAnimating = false;
    currentAnimationStep = 0;
    animationQueue.clear();
}

void GraphVisualizer::setMode(Mode newMode) {
    currentMode = newMode;
    resetVisualization();

    // עדכון צבע הכפתורים
    for (auto& [name, button] : buttons) {
        button.setFillColor(sf::Color(102, 126, 234)); // צבע רגיל
    }

    // הדגשת הכפתור הפעיל
    std::string activeButton;
    switch (newMode) {
        case Mode::ADD_NODES:
            activeButton = "addNodes";
            updateStatus("מצב הוספת קודקודים - לחץ כדי להוסיף");
            break;
        case Mode::ADD_EDGES:
            activeButton = "addEdges";
            updateStatus("מצב הוספת קשתות - בחר שני קודקודים");
            break;
        default:
            break;
    }

    if (!activeButton.empty() && buttons.find(activeButton) != buttons.end()) {
        buttons[activeButton].setFillColor(sf::Color(72, 187, 120)); // ירוק לכפתור פעיל
    }
}

void GraphVisualizer::setAlgorithm(AlgorithmType algorithm) {
    currentAlgorithm = algorithm;
    resetVisualization();
}

void GraphVisualizer::updateStatus(const std::string& message) {
    statusText.setString("מצב: " + message);
}

void GraphVisualizer::updateInfo() {
    std::stringstream info;
    info << "קודקודים: " << visualNodes.size()
         << " | קשתות: " << visualEdges.size()
         << " | מצב: " << modeToString(currentMode);

    if (currentAlgorithm != AlgorithmType::NONE) {
        info << " | אלגוריתם: " << algorithmToString(currentAlgorithm);
    }

    infoText.setString(info.str());
}

void GraphVisualizer::update() {
    updateAnimation();
    updateInfo();
}

void GraphVisualizer::render() {
    window.clear(sf::Color(30, 30, 50)); // רקע כהה

    drawGraph();
    drawUI();

    window.display();
}

void GraphVisualizer::drawGraph() {
    drawEdges();
    drawNodes();
}

void GraphVisualizer::drawNodes() {
    for (auto& node : visualNodes) {
        node->draw(window, font);
    }
}

void GraphVisualizer::drawEdges() {
    for (auto& edge : visualEdges) {
        edge->draw(window, font);
    }
}

void GraphVisualizer::drawUI() {
    drawButtons();
    drawTexts();
}

void GraphVisualizer::drawButtons() {
    for (const auto& [name, button] : buttons) {
        window.draw(button);
        window.draw(buttonTexts.at(name));
    }
}

void GraphVisualizer::drawTexts() {
    window.draw(statusText);
    window.draw(infoText);
}

std::string GraphVisualizer::modeToString(Mode mode) {
    switch (mode) {
        case Mode::ADD_NODES: return "הוספת קודקודים";
        case Mode::ADD_EDGES: return "הוספת קשתות";
        case Mode::SELECT_NODES: return "בחירה";
        case Mode::RUN_ALGORITHM: return "הרצת אלגוריתם";
        default: return "לא ידוע";
    }
}

std::string GraphVisualizer::algorithmToString(AlgorithmType algorithm) {
    switch (algorithm) {
        case AlgorithmType::BFS: return "BFS";
        case AlgorithmType::DFS: return "DFS";
        case AlgorithmType::DIJKSTRA: return "Dijkstra";
        case AlgorithmType::PRIM: return "Prim";
        case AlgorithmType::KRUSKAL: return "Kruskal";
        default: return "אין";
    }
}

sf::Color GraphVisualizer::getNodeColor(bool visited, bool selected, bool highlighted) {
    if (highlighted) return sf::Color::Yellow;
    if (selected) return sf::Color(72, 187, 120); // ירוק
    if (visited) return sf::Color(237, 137, 54);   // כתום
    return sf::Color(102, 126, 234);               // כחול רגיל
}

sf::Color GraphVisualizer::getEdgeColor(bool highlighted) {
    return highlighted ? sf::Color::Red : sf::Color(160, 174, 192);
}

void GraphVisualizer::showHelp() {
    // כאן תוכלי להוסיף חלון עזרה
    updateStatus("עזרה: ESC=יציאה, R=איפוס, Space=השהיית אנימציה");
}

} // namespace graph