#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"

class TrampaWorm {
    int IndiceAnimacion;

public:
    TrampaWorm(const std::vector<sf::Texture>& textures, const sf::Vector2f& position, Player& player);
    void cargar(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    std::vector<sf::Texture> textureList;
    sf::Sprite entitySprite;
    unsigned int currentFrameIndex;
    float frameDuration;
    float timerCounter;
    sf::Vector2f entityPosition;
    sf::Time animationTimer;

    Player& player;


};
