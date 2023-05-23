#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "menu.h"
#include "Player.h"
#include "Coin.h"
#include <sstream>

using namespace sf;
const float GRAVITY = 0.5f;
float velocity = 0.0f;
bool onPlatform = false;
bool una = true;
int pagenum = 1000;
void game() {
    sf::RenderWindow window(sf::VideoMode(1366, 768), "THE GAME", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);

    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(400.0f, 200.0f));

    std::vector<sf::Texture> walkingFrames;
    for (int i = 1; i <= 2; i++) {
        sf::Texture frame;
        if (!frame.loadFromFile("player" + std::to_string(i) + ".png")) {
            std::cerr << "Error cargando el frame " << i << std::endl;
        }
        else {
            walkingFrames.push_back(frame);
        }
    }

    if (walkingFrames.empty()) {
        // Lógica para manejar el caso de que no se hayan cargado los frames
    }

    sf::Clock animationTimer;
    float frameTime = 0.2f;

    Player player(sf::Vector2f(40.0f, 40.0f));
    player.setTexture(walkingFrames[0]);
    player.setPos(sf::Vector2f(683, 384));

    sf::Texture platformTexture;
    if (!platformTexture.loadFromFile("platform.png")) {
        // Lógica para manejar el error al cargar la textura
    }
    sf::Sprite platform(platformTexture);
    platform.setPosition(683, 484);
    int currentFrame = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::FloatRect playerBounds = player.getGlobalBounds();
        sf::FloatRect platformBounds = platform.getGlobalBounds();

        if (playerBounds.intersects(platformBounds)) {
            if (velocity > 0) {
                sf::Vector2f newPosition(player.getPosition().x, platform.getPosition().y - player.getGlobalBounds().height+20);
                player.setPos(newPosition);
                velocity = 0.0f;
                onPlatform = true;
            }
            else {
                sf::Vector2f newPosition(player.getPosition().x, platform.getPosition().y + platform.getGlobalBounds().height);
                player.setPos(newPosition);
                onPlatform = false;
            }
        }
        else {
            velocity += GRAVITY;
            player.move(sf::Vector2f(0, velocity));
            onPlatform = false;
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.setFacingLeft(true);
            player.move(sf::Vector2f(-1, 0));
            if (animationTimer.getElapsedTime().asSeconds() >= frameTime) {
                currentFrame = (currentFrame + 1) % walkingFrames.size();
                player.setTexture(walkingFrames[currentFrame]);
                
                animationTimer.restart();
            }
            }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player.setFacingLeft(false);
            player.move(sf::Vector2f(1, 0));
            if (animationTimer.getElapsedTime().asSeconds() >= frameTime) {
                currentFrame = (currentFrame + 1) % walkingFrames.size();
                player.setTexture(walkingFrames[currentFrame]);
                
                animationTimer.restart();
            }
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && onPlatform) {
            
            while (velocity >= -10.00f) {
                velocity = velocity - 1.00f;
            }
            player.move(sf::Vector2f(0, velocity));
            if (animationTimer.getElapsedTime().asSeconds() >= frameTime) {
                currentFrame = (currentFrame + 1) % walkingFrames.size();
                player.setTexture(walkingFrames[currentFrame]);
                animationTimer.restart();
            }
        }
        view.setCenter(player.getPosition().x, view.getCenter().y);
        if (una) {
            view.setCenter(player.getPosition().x, player.getPosition().y + 30);
            una = false;
        }
        window.clear(sf::Color::Blue);
        window.setView(view);
        window.draw(platform);
        player.drawTo(window);
        window.display();
    }
}
menu::menu(int width, int height) {
    font.loadFromFile("fuente3.ttf");

    mainmenu[0].setFont(font);
    mainmenu[0].setFillColor(Color{ 255, 255, 255 });
    mainmenu[0].setString("Play");
    mainmenu[0].setCharacterSize(120);
    mainmenu[0].setPosition(Vector2f(400, height / (4)));

    mainmenu[1].setFont(font);
    mainmenu[1].setFillColor(Color::Red);
    mainmenu[1].setString("Instrucciones");
    mainmenu[1].setCharacterSize(120);
    mainmenu[1].setPosition(Vector2f(400, height / (4) + 200));

    mainmenu[2].setFont(font);
    mainmenu[2].setFillColor(Color::Red);
    mainmenu[2].setString("Exit");
    mainmenu[2].setCharacterSize(120);
    mainmenu[2].setPosition(Vector2f(400, height / (4) + 400));

    selected = 0;

}

menu::~menu() {}

void menu::setSelected(int n) {
    selected = n;
}

void menu::draw(RenderWindow& window) {
    for (int i = 0; i < 3; i++)
    {
        window.draw(mainmenu[i]);
    }
}

void menu::MoveDown() {
    if (selected + 1 <= 3) {
        mainmenu[selected].setFillColor(Color::Red);
        selected++;
        if (selected == 3) {
            selected = 0;
        }
        mainmenu[selected].setFillColor(Color(255, 255, 255));
    }
}

void menu::MoveUp() {
    if (selected - 1 >= -1) {
        mainmenu[selected].setFillColor(Color::Red);
        selected--;
        if (selected == -1) {
            selected = 2;
        }
        mainmenu[selected].setFillColor(Color{ 255, 255, 255 });
    }
}
void menu1() {
    RenderWindow window(VideoMode(1920, 1080), "Game");
    menu menu(1920, 1080);
    Texture mainmenubg;
    mainmenubg.loadFromFile("hell.jpg");
    Sprite bg;
    bg.setTexture(mainmenubg);

    while (true) {
        if (pagenum == 1000) {
            while (window.isOpen()) {
                Event event;
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed) {
                        window.close();
                        break;
                    }
                    if (event.type == Event::KeyPressed) {
                        if (event.key.code == Keyboard::Up) {
                            menu.MoveUp();
                        }
                        if (event.key.code == Keyboard::Down) {
                            menu.MoveDown();
                        }
                        if (event.key.code == Keyboard::Return) {
                            if (menu.pressed() == 0) {
                                pagenum = 0;
                            }
                            if (menu.pressed() == 1) {
                                pagenum = 1;
                            }
                            if (menu.pressed() == 2) {
                                pagenum = -1;
                            }
                        }
                    }
                }
                window.clear();
                if (pagenum != 1000) {
                    break;
                }
                window.draw(bg);
                menu.draw(window);
                window.display();
            }
            if (pagenum == -1) {
                window.close();
                break;
            }
            if (pagenum == 0) {
                window.close();
                game();
                break;
            }
        }
    }
}

int main()
{
    menu1();
}