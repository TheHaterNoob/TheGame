#pragma once
#include <SFML/Graphics.hpp>
class AttackCube{
public:
    AttackCube(sf::Vector2f size) {
        shape.setSize(size);
        shape.setFillColor(sf::Color(0, 255, 0, 10));
    }

    void setPosition(sf::Vector2f position) {
        shape.setPosition(position);
    }

    void setColor(sf::Color color) {
        shape.setFillColor(color);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }
    int getY() {
        return shape.getPosition().y;
    }
    int getX() {
        return shape.getPosition().x;
    }
    sf::FloatRect  getGlobalBounds() {
        return shape.getGlobalBounds();
    }
    void move(sf::Vector2f distance) {
        shape.move(distance);
    }
    sf::Vector2f getPosition() {
       
        return shape.getPosition();
    }
    void setSize(sf::Vector2f xd) {
        shape.setSize(xd);
    }
    
private:
    sf::RectangleShape shape;
};

