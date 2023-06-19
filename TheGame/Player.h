#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include <cstdlib>

class Player {
public:
    bool isFacingLeft;
    int life;
    Player(sf::Vector2f size) {
        player.setSize(size);
        isFacingLeft = false;
        setOriginAndScale();
        life = 100;
    }

    void receiveDamage(int damage) {
        life -= damage;        
        std::cerr << life << std::endl;

        if (life <= 0) {
            std::cout << "MUERTO" << std::endl;
            
        }

    }

    void drawTo(sf::RenderWindow& window) {
        window.draw(player);

        
        sf::RectangleShape lifeBar(sf::Vector2f(60, 2)); 
        lifeBar.setPosition(player.getPosition().x - 27, player.getPosition().y - 30);



        lifeBar.setFillColor(sf::Color::Red); 
        lifeBar.setOutlineThickness(1);
        lifeBar.setOutlineColor(sf::Color::Black); 
        window.draw(lifeBar);
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

    int getX() {
        return player.getPosition().x;
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
        player.setOrigin(23, 20);
        if (isFacingLeft) {
            player.setScale(-std::abs(player.getScale().x), player.getScale().y);
        }
        else {
            player.setScale(std::abs(player.getScale().x), player.getScale().y);
        }
    }

    void setFacingLeft(bool facingLeft) {
        isFacingLeft = facingLeft;
        if (isFacingLeft) {
            player.setScale(-std::abs(player.getScale().x), player.getScale().y);
        }
        else {
            player.setScale(std::abs(player.getScale().x), player.getScale().y);
        }
    }

    sf::FloatRect getGlobalBounds() {
        sf::FloatRect bounds = player.getGlobalBounds();
        bounds.width -= 60;  
        return bounds;
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
        player.setOrigin(23, 20);
        if (isFacingLeft) {
            player.setScale(-std::abs(player.getScale().x), player.getScale().y);
        }
        else {
            player.setScale(std::abs(player.getScale().x), player.getScale().y);
        }
    }
    sf::RectangleShape player;

  

};
