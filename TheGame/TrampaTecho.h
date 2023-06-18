#pragma once
#include <SFML/Graphics.hpp>

class TrampaTecho {
    int IndiceAnimacion;

public:
    TrampaTecho(const std::vector<sf::Texture>& textures, const sf::Vector2f& position);
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

};
