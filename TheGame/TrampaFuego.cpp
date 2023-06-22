#include "TrampaFuego.h"

TrampaFuego::TrampaFuego(const std::vector<sf::Texture>& textures, const sf::Vector2f& position, Player& player)
    : listaTexturas(textures), indiceFrameActual(0), duracionFrame(0.2f), contadorTimer(0.0f), posicionEntidad(position), jugador(player)
{
    spriteEntidad.setTexture(listaTexturas[indiceFrameActual]);
    spriteEntidad.setPosition(posicionEntidad);
}
void TrampaFuego::actualizar(float deltaTime)
{

    const float FuegoCooldown = 25.0f;
    static float FuegoTimer = 0.0f;


    FuegoTimer += deltaTime;

    if (FuegoTimer >= FuegoCooldown)
    {
        indiceFrameActual = (indiceFrameActual + 1) % listaTexturas.size();
       spriteEntidad.setTexture(listaTexturas[indiceFrameActual]);
        FuegoTimer = 0.0f;

            sf::FloatRect trapBounds = spriteEntidad.getGlobalBounds();
            sf::FloatRect playerBounds = jugador.getGlobalBounds();

            if (trapBounds.intersects(playerBounds))
            {
                jugador.receiveDamage(34);
            }
        

    }
}

void TrampaFuego::draw(sf::RenderWindow& window)
{
    window.draw(spriteEntidad);
}


