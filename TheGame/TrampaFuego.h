#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class TrampaFuego {
    int INDICE;

public:
    TrampaFuego(const std::vector<sf::Texture>& textures, const sf::Vector2f& position, Player& player);
    void actualizar(float deltaTime);
    void draw(sf::RenderWindow& window);


private:
    std::vector<sf::Texture> listaTexturas;
    sf::Sprite spriteEntidad;
    unsigned int indiceFrameActual;
    float duracionFrame;
    float contadorTimer;
    sf::Vector2f posicionEntidad;
    sf::Time temporizadorAnimacion;
    Player& jugador;

};
