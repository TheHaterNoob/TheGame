#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

class Platform {
public:
    Platform(const sf::Texture& texture, const sf::Vector2f& position) {
        sprite.setTexture(texture);
        sprite.setPosition(position);
       
    }

    sf::FloatRect getGlobalBounds() const {
        return sprite.getGlobalBounds();
    }

    void drawTo(sf::RenderWindow& window) const {
        window.draw(sprite);
    }
    sf::Vector2f getPosition() const {
        return sprite.getPosition();
    }

    void move(sf::Vector2f distance) {
        sprite.move(distance);
    }

    void setPosition(sf::Vector2f position) {
        sprite.setPosition(position);
    }

    


private:
    sf::Sprite sprite;

    

};