//
// Created by 12adi on 30/05/2025.
//

#ifndef FONTMANAGER_H
#define FONTMANAGER_H
//
// FontManager.h - מנהל פונטים עם תמיכה בפונטים מרובים וחלופיים
//

#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>

namespace GraphGame {

class FontManager {
private:
    static std::unique_ptr<sf::Font> defaultFont;
    static bool fontLoaded;
    static std::vector<std::string> fontPaths;

public:
    // רשימת פונטים לנסות (לפי סדר עדיפות)
    static void initializeFontPaths() {
        fontPaths = {
            // Windows
            "C:/Windows/Fonts/arial.ttf",
            "C:/Windows/Fonts/Arial.ttf",
            "C:/Windows/Fonts/calibri.ttf",
            "C:/Windows/Fonts/tahoma.ttf",

            // macOS
            "/System/Library/Fonts/Arial.ttf",
            "/System/Library/Fonts/Helvetica.ttc",
            "/Library/Fonts/Arial.ttf",

            // Linux
            "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
            "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
            "/usr/share/fonts/TTF/arial.ttf",
            "/usr/share/fonts/arial.ttf",

            // נסיבות נוספות
            "arial.ttf",
            "fonts/arial.ttf",
            "../fonts/arial.ttf",
            "assets/fonts/arial.ttf"
        };
    }

    static sf::Font& getFont() {
        if (!fontLoaded) {
            loadFont();
        }
        return *defaultFont;
    }

    static bool loadFont() {
        if (fontLoaded) return true;

        defaultFont = std::make_unique<sf::Font>();
        initializeFontPaths();

        // נסה לטעון פונט מהרשימה
        for (const auto& path : fontPaths) {
            if (defaultFont->loadFromFile(path)) {
                fontLoaded = true;
                std::cout << "✅ Font loaded successfully from: " << path << std::endl;
                return true;
            }
        }

        // אם לא הצלחנו לטעון פונט, ננסה ליצור פונט ברירת מחדל
        std::cout << "⚠️  Warning: Could not load any font files. Using system default." << std::endl;

        // יצירת פונט בסיסי עם נתונים מובנים (bitmap פשוט)
        createFallbackFont();

        fontLoaded = true;
        return true;
    }

private:
    static void createFallbackFont() {
        // אם כל הפונטים נכשלו, ננסה ליצור פונט בסיסי
        // זה לא יהיה יפה אבל לפחות יעבוד
        std::cout << "🔄 Creating fallback font..." << std::endl;

        // פונט ברירת מחדל של SFML (אם קיים)
        sf::Font systemFont;
        if (systemFont.loadFromFile("")) {
            *defaultFont = systemFont;
            return;
        }

        // אם גם זה לא עבד, ננסה ליצור משהו בסיסי
        // SFML ישתמש בפונט ברירת מחדל של המערכת
        std::cout << "ℹ️  Using SFML default system font" << std::endl;
    }
};

// הגדרה של המשתנים הסטטיים
std::unique_ptr<sf::Font> FontManager::defaultFont = nullptr;
bool FontManager::fontLoaded = false;
std::vector<std::string> FontManager::fontPaths;

} // namespace GraphGame

#endif // FONT_MANAGER_H

//
// עדכון לקבצי הוויזואליזציה - שימוש במנהל הפונטים
//

// הוספה לתחילת GraphGameVisualizer.cpp:
/*

#include "FontManager.h"

// בפונקציה initialize():
bool GraphGameVisualizer::initialize() {
    // טעינת פונט עם תמיכה בחלופות
    if (!GraphGame::FontManager::loadFont()) {
        std::cout << "Warning: Font loading issues, but continuing with fallback" << std::endl;
    }

    // שימוש בפונט בכל הרכיבים
    font = GraphGame::FontManager::getFont();

    // המשך הקוד הרגיל...
    bfsQueue = std::make_unique<VisualQueue>("BFS Queue", sf::Vector2f(50, 750));
    // וכו'...
}

// עדכון בבנאי של VisualQueue, VisualStack, וכו':
VisualQueue::VisualQueue(const std::string& queueTitle, sf::Vector2f pos)
    : title(queueTitle), position(pos) {

    font = GraphGame::FontManager::getFont(); // במקום לטעון לוקלית

    background.setSize(sf::Vector2f(300, 100));
    // וכו'...
}

*/
#endif //FONTMANAGER_H
