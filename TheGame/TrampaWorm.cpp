#include "TrampaWorm.h"

TrampaWorm::TrampaWorm(const std::vector<sf::Texture>& textures, const sf::Vector2f& position)
    : textureList(textures), currentFrameIndex(0), frameDuration(0.2f), timerCounter(0.0f), entityPosition(position)
{
    entitySprite.setTexture(textureList[currentFrameIndex]);
    entitySprite.setPosition(entityPosition);
}

void TrampaWorm::cargar(float deltaTime)
{
    timerCounter += deltaTime;

    if (timerCounter >= frameDuration)
    {
        currentFrameIndex = (currentFrameIndex + 1) % textureList.size();
        entitySprite.setTexture(textureList[currentFrameIndex]);
        timerCounter = 0.0f;
    }
}

void TrampaWorm::draw(sf::RenderWindow& window)
{
    window.draw(entitySprite);
}
