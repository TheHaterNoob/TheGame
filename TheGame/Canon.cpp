#include "canon.h"

Canon::Canon(const std::vector<sf::Texture>& textures, const sf::Vector2f& position)
    : m_textures(textures), m_currentFrame(0), m_frameTime(0.2f), m_timer(0.0f), m_position(position)
{
    m_sprite.setTexture(m_textures[m_currentFrame]);
    m_sprite.setPosition(m_position);
}

void Canon::update(float deltaTime)
{
    m_timer += deltaTime;
    if (m_timer >= m_frameTime)
    {
        m_currentFrame = (m_currentFrame + 1) % m_textures.size();
        m_sprite.setTexture(m_textures[m_currentFrame]);
        m_timer = 0.0f;
    }
}




void Canon::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}
