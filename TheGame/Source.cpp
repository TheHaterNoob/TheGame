#pragma once
#include <SFML/Graphics.hpp>
#include "menu.h"
#include "Player.h"
#include "Platform.h"

using namespace sf;

const float GRAVITY = 0.5f;
const float JUMP_HEIGHT = 2.0f;
const float FRAME_TIME = 0.2f;
int pagenum = 1000;
bool una = true;
float jump = 2.00f;
bool isDashing = false;
float dashTime = 0.0f;
const float dashDuration = 0.3f; 
const float dashDistance = 100.0f; 
const float dashSpeed = dashDistance / dashDuration;
float speed = 1.0f;
bool onPlatform = false;
float velocity = 0.0f;
sf::Clock clock1;

bool isAttacking = false;

int currentAttackFrame = 0;

void game()
{
    RenderWindow window(VideoMode(1366, 768), "THE GAME", Style::Fullscreen);
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);

    View view(Vector2f(0.0f, 0.0f), Vector2f(400.0f, 200.0f));

    std::vector<Texture> walkingFrames(2);
    for (int i = 1; i <= 2; i++)
    {
        if (!walkingFrames[i - 1].loadFromFile("player" + std::to_string(i) + ".png"))
        {
            std::cerr << "Error loading frame " << i << std::endl;
        }
    }

    std::vector<sf::Texture> attackFrames(4);
    for (int i = 1; i <= 4; i++)
    {
        if (!attackFrames[i - 1].loadFromFile("ataque1_" + std::to_string(i) + ".png"))
        {
            std::cerr << "Error loading attack frame " << i << std::endl;
        }
    }

    if (walkingFrames.empty())
    {
        // Logic to handle the case when no frames are loaded
    }

    Clock animationTimer;
    int currentFrame = 0;

    Player player(Vector2f(40.0f, 40.0f));
    player.setTexture(walkingFrames[0]);
    player.setPos(Vector2f(683, 384));

    Texture platformTexture;
    if (!platformTexture.loadFromFile("platform.png"))
    {
        // Logic to handle the error when loading the platform texture
    }
    Platform platform(platformTexture, Vector2f(683, 484));

    Texture castleTexture;
    if (!castleTexture.loadFromFile("fondo.png"))
    {
        std::cerr << "Error loading castle texture" << std::endl;
    }

    Sprite castle(castleTexture);
    castle.setPosition(435, 260);




    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        FloatRect playerBounds = player.getGlobalBounds();
        FloatRect platformBounds = platform.getGlobalBounds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && !isAttacking)
        {
            isAttacking = true;
            currentAttackFrame = 0;
        }

        if (isAttacking)
        {
            if (currentAttackFrame < attackFrames.size())
            {
                player.setTexture(attackFrames[currentAttackFrame]);
                currentAttackFrame++;
            }
            else
            {
                isAttacking = false;
            }
        }

        if (playerBounds.intersects(platformBounds))
        {
            if (velocity > 0)
            {
                Vector2f newPosition(player.getPosition().x, platform.getPosition().y - player.getGlobalBounds().height + 20);
                player.setPos(newPosition);
                velocity = 0.0f;
                onPlatform = true;
                
                jump = 2.0f;
            }
        }
        else
        {
            velocity += GRAVITY;
            player.move(Vector2f(0, velocity));
        }

        if (!isDashing) {
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                player.setFacingLeft(true);
                player.move(Vector2f(-speed, 0));
                if (animationTimer.getElapsedTime().asSeconds() >= FRAME_TIME) {
                    currentFrame = (currentFrame + 1) % walkingFrames.size();
                    player.setTexture(walkingFrames[currentFrame]);
                    animationTimer.restart();
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                player.setFacingLeft(false);
                player.move(Vector2f(speed, 0));
                if (animationTimer.getElapsedTime().asSeconds() >= FRAME_TIME) {
                    currentFrame = (currentFrame + 1) % walkingFrames.size();
                    player.setTexture(walkingFrames[currentFrame]);
                    animationTimer.restart();
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                if (onPlatform) {
                    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                        onPlatform = false;
                    }
                    velocity -= jump;
                    jump = jump - 0.2f;
                    if (jump < 0.0f) {
                        jump = 0.0f;
                        onPlatform = false;
                    }
                    player.move(sf::Vector2f(0, velocity));
                }
            }
        }
        sf::Time deltaTime = clock1.restart();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !isDashing) {
            isDashing = true;
            dashTime = 0.0f;
            
        }

        if (isDashing) {
            
            dashTime += deltaTime.asSeconds();
            
            if (dashTime <= dashDuration) {
                // Calculate the distance to move based on the elapsed time
                float distance = dashSpeed * deltaTime.asSeconds();

                if (player.isFacingLeft) {
                    player.move(sf::Vector2f(-distance, 0));
                }
                else {
                    player.move(sf::Vector2f(distance, 0));
                }
            }
            else {
                isDashing = false;
            }
            
        }
        else {
          
        }

            view.setCenter(player.getPosition().x, view.getCenter().y);
            if (una)
            {
                view.setCenter(player.getPosition().x, player.getPosition().y + 30);
                una = false;
            }

            window.clear(Color::Blue);
            window.setView(view);
            window.draw(castle);
            platform.drawTo(window);
            player.drawTo(window);
            window.display();
        }
    }


menu::menu(int width, int height)
{
    font.loadFromFile("fuente3.ttf");

    mainmenu[0].setFont(font);
    mainmenu[0].setFillColor(Color::White);
    mainmenu[0].setString("Play");
    mainmenu[0].setCharacterSize(120);
    mainmenu[0].setPosition(Vector2f(400, height / 4));

    mainmenu[1].setFont(font);
    mainmenu[1].setFillColor(Color::Red);
    mainmenu[1].setString("Instructions");
    mainmenu[1].setCharacterSize(120);
    mainmenu[1].setPosition(Vector2f(400, height / 4 + 200));

    mainmenu[2].setFont(font);
    mainmenu[2].setFillColor(Color::Red);
    mainmenu[2].setString("Exit");
    mainmenu[2].setCharacterSize(120);
    mainmenu[2].setPosition(Vector2f(400, height / 4 + 400));

    selected = 0;
}

menu::~menu() {}

void menu::setSelected(int n)
{
    selected = n;
}

void menu::draw(RenderWindow& window)
{
    for (int i = 0; i < 3; i++)
    {
        window.draw(mainmenu[i]);
    }
}

void menu::MoveDown()
{
    if (selected + 1 <= 3)
    {
        mainmenu[selected].setFillColor(Color::Red);
        selected++;
        if (selected == 3)
        {
            selected = 0;
        }
        mainmenu[selected].setFillColor(Color::White);
    }
}

void menu::MoveUp()
{
    if (selected - 1 >= -1)
    {
        mainmenu[selected].setFillColor(Color::Red);
        selected--;
        if (selected == -1)
        {
            selected = 2;
        }
        mainmenu[selected].setFillColor(Color::White);
    }
}

void menu1()
{
    RenderWindow window(VideoMode(1920, 1080), "Game");
    menu menu(1920, 1080);
    Texture mainmenubg;
    mainmenubg.loadFromFile("hell.jpg");
    Sprite bg;
    bg.setTexture(mainmenubg);

    while (true)
    {
        if (pagenum == 1000)
        {
            while (window.isOpen())
            {
                Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == Event::Closed)
                    {
                        window.close();
                        break;
                    }
                    if (event.type == Event::KeyPressed)
                    {
                        if (event.key.code == Keyboard::Up)
                        {
                            menu.MoveUp();
                        }
                        if (event.key.code == Keyboard::Down)
                        {
                            menu.MoveDown();
                        }
                        if (event.key.code == Keyboard::Return)
                        {
                            if (menu.pressed() == 0)
                            {
                                pagenum = 0;
                            }
                            if (menu.pressed() == 1)
                            {
                                pagenum = 1;
                            }
                            if (menu.pressed() == 2)
                            {
                                pagenum = -1;
                            }
                        }
                    }
                }
                window.clear();
                if (pagenum != 1000)
                {
                    break;
                }
                window.draw(bg);
                menu.draw(window);
                window.display();
            }
            if (pagenum == -1)
            {
                window.close();
                break;
            }
            if (pagenum == 0)
            {
                game();
                window.close();
                
                break;
            }
        }
    }
}

int main()
{
    menu1();
    return 0;
}
