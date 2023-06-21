#include "TrampaTecho.h"

TrampaTecho::TrampaTecho(const std::vector<sf::Texture>& textures, const sf::Vector2f& position, Player& player)
    : textureList(textures), currentFrameIndex(0), frameDuration(0.2f), timerCounter(0.0f), entityPosition(position), player(player)
{
    entitySprite.setTexture(textureList[currentFrameIndex]);
    entitySprite.setPosition(entityPosition);
}
void TrampaTecho::cargar(float deltaTime)
{

    const float TechoCooldown = 25.0f;
    static float TechoTimer = 0.0f;


    TechoTimer += deltaTime;

    if (TechoTimer >= TechoCooldown)
    {
        currentFrameIndex = (currentFrameIndex + 1) % textureList.size();
        entitySprite.setTexture(textureList[currentFrameIndex]);
        TechoTimer = 0.0f;


        if (currentFrameIndex >= 1 && currentFrameIndex <= 4)
        {
            sf::FloatRect trapBounds = entitySprite.getGlobalBounds();
            sf::FloatRect playerBounds = player.getGlobalBounds();

            if (trapBounds.intersects(playerBounds))
            {
                player.receiveDamage(80);
            }
        }

    }
}

void TrampaTecho::draw(sf::RenderWindow& window)
{
    window.draw(entitySprite);
}


