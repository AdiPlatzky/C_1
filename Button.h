//
// Created by 12adi on 29/05/2025.
//

#ifndef BUTTON_H
#define BUTTON_H
#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;

public:
    Button(const std::string& label, sf::Vector2f position, sf::Vector2f size = {120, 40}) {
        font.loadFromFile("arial.ttf");

        shape.setSize(size);
        shape.setPosition(position);
        shape.setFillColor(sf::Color(180, 180, 180));

        text.setFont(font);
        text.setString(label);
        text.setCharacterSize(18);
        text.setFillColor(sf::Color::Black);
        text.setPosition(position.x + 10, position.y + 5);
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
        window.draw(text);
    }

    bool isClicked(sf::Vector2f mousePos) const {
        return shape.getGlobalBounds().contains(mousePos);
    }
};

#endif

#endif //
