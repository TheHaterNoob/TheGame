#include "canon.h"

Canon::Canon(const std::vector<sf::Texture>& textures, const sf::Vector2f& position)
    : m_textures(textures), m_currentFrame(0), m_frameTime(0.2f), m_timer(0.0f), m_position(position)
{
    m_sprite.setTexture(m_textures[m_currentFrame]);
    m_sprite.setPosition(m_position);
}

void Canon::update(float deltaTime)
{
    const float CanonCooldown = 46.0f;
    static float CanonTimer = 0.0f; 

    CanonTimer += deltaTime;  
    if (CanonTimer >= CanonCooldown)
    {
        m_currentFrame = (m_currentFrame + 1) % m_textures.size();
        m_sprite.setTexture(m_textures[m_currentFrame]);
        CanonTimer = 0.0f;  
    }
}

void Canon::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}
