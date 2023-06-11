#pragma once
#include <SFML/Graphics.hpp>

class Canon {
    int currentAnimationIndex;



public:
    Canon(const std::vector<sf::Texture>& textures, const sf::Vector2f& position);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

    

private:
    std::vector<sf::Texture> m_textures;
    sf::Sprite m_sprite;
    unsigned int m_currentFrame;
    float m_frameTime;
    float m_timer;
    sf::Vector2f m_position;
    sf::Time m_animationTimer;

};
