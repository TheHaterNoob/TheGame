#include "TrampaWorm.h"

TrampaWorm::TrampaWorm(const std::vector<sf::Texture>& textures, const sf::Vector2f& position, Player& player)
    : textureList(textures), currentFrameIndex(0), frameDuration(0.2f), timerCounter(0.0f), entityPosition(position), player(player)
{
    entitySprite.setTexture(textureList[currentFrameIndex]);
    entitySprite.setPosition(entityPosition);
}

void TrampaWorm::cargar(float deltaTime)
{

    const float WormCooldown = 25.0f;
    static float WormTimer = 0.0f;
    bool dañito = false;

    WormTimer += deltaTime;

    if (WormTimer >= WormCooldown)
    {
        currentFrameIndex = (currentFrameIndex + 1) % textureList.size();
        entitySprite.setTexture(textureList[currentFrameIndex]);
        WormTimer = 0.0f;



        if (currentFrameIndex >= 4 && currentFrameIndex <= 11)
        {
            sf::FloatRect trapBounds = entitySprite.getGlobalBounds();
            sf::FloatRect playerBounds = player.getGlobalBounds();


            if (player.life > 0) {
                if (trapBounds.intersects(playerBounds))
                {
                    if (!dañito) {

                        dañito = true;
                        player.receiveDamage(10);
                    }
                }
                else {
                    dañito = false;
                }
            }
        }


    }
}

void TrampaWorm::draw(sf::RenderWindow& window)
{
    window.draw(entitySprite);
}
