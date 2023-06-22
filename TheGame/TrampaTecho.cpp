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
    bool da�oo = false;

    TechoTimer += deltaTime;

    if (TechoTimer >= TechoCooldown)
    {
        currentFrameIndex = (currentFrameIndex + 1) % textureList.size();
        entitySprite.setTexture(textureList[currentFrameIndex]);
        TechoTimer = 0.0f;


        if (currentFrameIndex >= 1 && currentFrameIndex <= 4)
        {
            sf::FloatRect trapBounds = entitySprite.getGlobalBounds();

            float xPadding = 14.0f; // Valor de ajuste para restar a los l�mites en x

            // Restar el valor de xPadding a los l�mites izquierdo y derecho
            trapBounds.left += xPadding;
            trapBounds.width -= 2 * xPadding;



            sf::FloatRect playerBounds = player.getGlobalBounds();

            if (player.life > 0) {
                if (trapBounds.intersects(playerBounds))
                {
                    if (!da�oo) {
                        da�oo = true;
                        player.receiveDamage(80);
                    }
                }
                else {
                    da�oo = false;
                }
            }
        }

    }
}

void TrampaTecho::draw(sf::RenderWindow& window)
{
    window.draw(entitySprite);
}


