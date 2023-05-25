#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

class Player  {
public:
    bool isFacingLeft;
    Player(sf::Vector2f size) {
        player.setSize(size);
        isFacingLeft = false;
        setOriginAndScale();
    }

    void drawTo(sf::RenderWindow& window) {
        window.draw(player);
    }

    void move(sf::Vector2f distance) {
        player.move(distance);
    }

    void setPos(sf::Vector2f newPos) {
        player.setPosition(newPos);
    }

    int getY() {
        return player.getPosition().y;
    }
    sf::Vector2f getSize() {
        return player.getSize();
    }

    sf::Vector2f getPosition() {
        return player.getPosition();
    }
    void setTexture(const sf::Texture& texture) {
        player.setTexture(&texture);
        sf::FloatRect bounds = player.getLocalBounds();
        player.setOrigin(bounds.width / 2, bounds.height /2);
        if (isFacingLeft) {
            sf::Vector2f scale = player.getScale();
            player.setScale(-std::abs(scale.x), scale.y);
        }
        else {
            player.setScale(std::abs(player.getScale().x), player.getScale().y);
        }
    }
    void setFacingLeft(bool facingLeft) {
            isFacingLeft = facingLeft;
    }
    sf::FloatRect  getGlobalBounds() {
        return player.getGlobalBounds();
    }
    void setPosition(sf::Vector2f position) {
        player.setPosition(position);
    }
    void setOrigin(sf::Vector2f origin) {
        player.setOrigin(origin);
    }
    void setScale(sf::Vector2f scaleFactor) {
        player.setScale(scaleFactor);
    }
    void setScale(float scaleX, float scaleY) {
        player.setScale(scaleX, scaleY);
    }



private:
    void setOriginAndScale() {
        sf::FloatRect bounds = player.getLocalBounds();
        player.setOrigin(bounds.width / 2, bounds.height / 2);
        if (isFacingLeft) {
            player.setScale(-std::abs(player.getScale().x), player.getScale().y);
        }
        else {
            player.setScale(std::abs(player.getScale().x), player.getScale().y);
        }
    }
    sf::RectangleShape player;
    
};
