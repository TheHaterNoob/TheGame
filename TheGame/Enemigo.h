#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

class Enemigo {
public:
 
    Enemigo(sf::Vector2f size) {
        enemigo.setSize(size);
        setOriginAndScale();
    }

    void drawTo(sf::RenderWindow& window) {
        window.draw(enemigo);
    }

    void move(sf::Vector2f distance) {
        enemigo.move(distance);
    }

    void setPos(sf::Vector2f newPos) {
        enemigo.setPosition(newPos);
    }

    int getY() {
        return enemigo.getPosition().y;
    }

    int getX() {
        return enemigo.getPosition().x;
    }

    sf::Vector2f getSize() {
        return enemigo.getSize();
    }

    sf::Vector2f getPosition() {
        return enemigo.getPosition();
    }

    void setTexture(const sf::Texture& texture) {
        enemigo.setTexture(&texture);
        sf::FloatRect bounds = enemigo.getLocalBounds();
        enemigo.setOrigin(23, 20);
        
          
    }

    sf::FloatRect getGlobalBounds() {
        return enemigo.getGlobalBounds();
    }

    void setPosition(sf::Vector2f position) {
        enemigo.setPosition(position);
    }

    void setOrigin(sf::Vector2f origin) {
        enemigo.setOrigin(origin);
    }

    void setScale(sf::Vector2f scaleFactor) {
        enemigo.setScale(scaleFactor);
    }

    void setScale(float scaleX, float scaleY) {
       enemigo.setScale(scaleX, scaleY);
    }

private:
    void setOriginAndScale() {
        sf::FloatRect bounds = enemigo.getLocalBounds();
        enemigo.setOrigin(23, 20);
        
    }
    sf::RectangleShape enemigo;
};
