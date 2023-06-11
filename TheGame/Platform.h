#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

class Platform {
public:
    Platform(sf::Texture& texture, const sf::Vector2f& position) {
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

private:
    sf::Sprite sprite;

    

};