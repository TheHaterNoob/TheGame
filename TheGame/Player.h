#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include <cstdlib>

class Player {
public:
    bool isFacingLeft;
    int life;
    sf::RectangleShape lifeBar;
    bool tamuerto;


    Player(sf::Vector2f size) {
        player.setSize(size);
        isFacingLeft = false;
        setOriginAndScale();
        life = 100;

        lifeBar.setSize(sf::Vector2f(87, 6));
        lifeBar.setFillColor(sf::Color::Red);
        tamuerto = false;

    }

    void receiveDamage(int damage) {
        if (damage >= life) {
            life = 0;
        }
        else {
            life -= damage;
        }

        std::cerr << life << std::endl;

        if (life <= 0) {
            std::cout << "MUERTO" << std::endl;
            tamuerto = true;

        }

        float lifeBarWidth = static_cast<float>(life) / 100 * 87; 
        lifeBar.setSize(sf::Vector2f(lifeBarWidth, 6));
    }


    void drawTo(sf::RenderWindow& window, sf::View& camera) {

        sf::Texture barraTexture;
        if (!barraTexture.loadFromFile("barra124.png")) {
            std::cerr << "Error loading barra texture" << std::endl;
        }

        sf::Sprite barraSprite(barraTexture);

        sf::Vector2f cameraPosition = camera.getCenter();
        sf::Vector2f cameraSize = camera.getSize();

        float xPos = cameraPosition.x - (cameraSize.x / 2) + (cameraSize.x / 2) - 166;
        float yPos = cameraPosition.y + (cameraSize.y / 2) - 184;

        float xPos2 = cameraPosition.x - (cameraSize.x / 2) + (cameraSize.x / 2) - 197;
        float yPos2 = cameraPosition.y + (cameraSize.y / 2) - 199;

        lifeBar.setPosition(xPos, yPos);
        barraSprite.setPosition(xPos2, yPos2);

        window.draw(barraSprite);
        window.draw(player);
        window.draw(lifeBar);

        if (tamuerto) {

           

            sf::Texture muertoTexture;
            if (!muertoTexture.loadFromFile("hasmuerto2.png")) {
                std::cerr << "Error loading 'has muerto' texture" << std::endl;
            }
             sf::Sprite muertoSprite(muertoTexture);

            float xPos3 = cameraPosition.x - (cameraSize.x / 2) + (cameraSize.x / 2) - 160;
            float yPos3 = cameraPosition.y + (cameraSize.y / 2) - 190;

           
           muertoSprite.setPosition(xPos3, yPos3);

            window.draw(muertoSprite);
        }

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
