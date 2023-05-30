#pragma once
#include <SFML/Graphics.hpp>
#include "menu.h"
#include "Player.h"
#include "Platform.h"
#include "Cube.h"
#include "AttackCube.h"
#include "Enemy.h"
#include <SFML/System/Vector2.hpp>
#include <cmath>



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
float Mvelocity = 0.0f;
sf::Clock clock1;

bool isAttacking = false;
bool isCrouching = false;
const Vector2f backgroundLimitTopLeft(720, 0);
const Vector2f backgroundLimitBottomRight(995, 421);
int currentAttackFrame = 0;
int currentWalkingFrame = 0;
int currentDashFrame = 0;
bool isClimbing = false;


std::vector<Platform> platforms;
sf::Vector2f normalize(const sf::Vector2f& vector)
{
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);

    if (length != 0.0f)
        return sf::Vector2f(vector.x / length, vector.y / length);
    else
        return vector;
}

void game()
{

    
    //BASE DE ESCALERA
    sf::Texture escaleraTexture;
    if (!escaleraTexture.loadFromFile("escalera1.png"))
    {
        std::cerr << "Error loading escalera1 texture" << std::endl;
    }

    Platform escalera1(escaleraTexture, Vector2f(857, 430));


    //LADDER
    sf::Texture woodTexture;
    if (!woodTexture.loadFromFile("escalar.png"))
    {
        std::cerr << "Error loading ladder texture" << std::endl;
    }

    Platform wood(woodTexture, Vector2f(855, 430));


    RenderWindow window(VideoMode(1366, 768), "THE GAME", Style::Fullscreen);
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);



    View view(Vector2f(0.0f, 0.0f), Vector2f(400.0f, 200.0f));

    sf::Texture agacharseTexture;
    if (!agacharseTexture.loadFromFile("agacharse.png"))
    {
        std::cerr << "Error loading agacharse texture" << std::endl;
    }

    std::vector<Texture> walkingFrames(4);
    for (int i = 1; i <= 4; i++)
    {
        if (!walkingFrames[i - 1].loadFromFile("player" + std::to_string(i) + ".png"))
        {
            std::cerr << "Error loading frame " << i << std::endl;
        }
    }

    std::vector<Texture> dashFrames(2);
    for (int i = 1; i <= 2; i++)
    {
        if (!dashFrames[i - 1].loadFromFile("dash" + std::to_string(i) + ".png"))
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


    Cube cube(Vector2f(20.00f, 38.00f));
    cube.setPosition(Vector2f(680, 420));
    cube.setColor(sf::Color(255, 0, 0, 60));

    AttackCube attack(Vector2f(20.00f, 38.00f));
    attack.setColor(sf::Color(0, 255, 0, 60));
    

    Enemy bad(Vector2f(20.00f, 38.00f));
    bad.setColor(sf::Color(0, 0, 255, 60));
    bad.setPosition(Vector2f(700, 420));

    Player player(Vector2f(100.0f, 45.0f));
    player.setTexture(walkingFrames[0]);
    
    std::vector<Texture> escalandoFrames(1);
    if (!escalandoFrames[0].loadFromFile("escalando.png")) {
        std::cerr << "Error loading escalando frame" << std::endl;
    }

    Texture platformTexture;
    if (!platformTexture.loadFromFile("suelo1.png"))
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


    platforms.push_back(Platform(platformTexture, Vector2f(509, 496)));
    platforms.push_back(Platform(platformTexture, Vector2f(596, 496)));
    platforms.push_back(Platform(platformTexture, Vector2f(683, 496)));
    platforms.push_back(Platform(platformTexture, Vector2f(770, 496)));
 
    //PLATAFORMA AEREA
    platforms.push_back(Platform(platformTexture, Vector2f(857, 430)));
    platforms.push_back(Platform(platformTexture, Vector2f(944, 430)));
    platforms.push_back(Platform(platformTexture, Vector2f(1031, 430)));
    platforms.push_back(Platform(platformTexture, Vector2f(1118, 430)));
    platforms.push_back(Platform(platformTexture, Vector2f(1205, 430)));

    sf::Time deltaTime = clock1.restart();
    platforms.push_back(escalera1);
    platforms.push_back(wood);
    
    while (window.isOpen())
    {
        int escalandoFrame = 0;
        float climbSpeed = -1.0f;



        if (isClimbing) {
            if (escalandoFrame < escalandoFrames.size()) {
                sf::Texture& escalandoFrameTexture = escalandoFrames[escalandoFrame];
                player.setTexture(escalandoFrameTexture);
                escalandoFrame++;
            }
            else {
                escalandoFrame = 0;
            }
        }
        else {
            // Resto del código para manejar la animación de caminata, etc.
        }

        if (isClimbing) {
            float distance = climbSpeed * deltaTime.asSeconds();
            cube.move(sf::Vector2f(0, -distance)); // Mueve al personaje hacia arriba
        }


        if (isClimbing) {
            player.setTexture(escalandoFrames[0]);
        }
        if (player.isFacingLeft)
        {
            Vector2f vec(cube.getX()+16, cube.getY() + 14);
            player.setPosition(vec);
        }
        else {
            Vector2f vec(cube.getX()+4 , cube.getY() + 14);
            player.setPosition(vec);
        }
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        FloatRect cubeBounds = cube.getGlobalBounds();
        FloatRect malitoBounds = bad.getGlobalBounds();
        bool onAnyPlatform = false;

        Vector2f veck;
        if (isAttacking)
        {
            if (player.isFacingLeft)
            {
                veck = Vector2f(cube.getX() - 30, cube.getY() + 0);
            }
            else {
                veck = Vector2f(cube.getX() + 30, cube.getY() + 0);
            }
            if (currentAttackFrame < attackFrames.size())
            {
                sf::Texture& attackFrame = attackFrames[currentAttackFrame];
                player.setTexture(attackFrame);

                attack.setPosition(veck);
                currentAttackFrame++;
                if (attack.getGlobalBounds().intersects(malitoBounds))
                {
                    // Calculate the direction from the attack cube to the bad cube
                    Vector2f direction = bad.getPosition() - attack.getPosition();
                    direction = normalize(direction);

                    // Push the bad cube away in the direction of the attack
                    float pushForce = 50.0f;
                    float pushUpForce = 20.0f;
                    bad.move(direction * pushForce);
                    bad.move(Vector2f(0.0f, -pushUpForce));
                }
            }
            else
            {
                attack.setPosition(sf::Vector2f(-100.0f, -100.0f));
                isAttacking = false;
                currentAttackFrame = 0;
            }
        }


       for (const auto& platform : platforms) {
            FloatRect platformBounds = platform.getGlobalBounds();

            if (cubeBounds.intersects(platformBounds)) {
                if (velocity > 0) {
                    Vector2f newPosition(cube.getX(), platform.getPosition().y - cube.getGlobalBounds().height);
                    cube.setPosition(newPosition);
                    velocity = 0.0f;
                    onPlatform = true;
                    onAnyPlatform = true;
                    jump = 2.0f;
                    break; // Se encontró una plataforma, no es necesario seguir verificando las demás
                }
            }

        }
        for (const auto& platform : platforms)
        {
            FloatRect platformBounds = platform.getGlobalBounds();
            if (malitoBounds.intersects(platformBounds)) {
                if (Mvelocity > 0) {
                    Vector2f newPosition(bad.getX(), platform.getPosition().y - bad.getGlobalBounds().height);
                    bad.setPosition(newPosition);
                    Mvelocity = 0.0f;
                    break; // Se encontró una plataforma, no es necesario seguir verificando las demás
                }
            }
        }

        if (!onAnyPlatform) {
            velocity += GRAVITY;
            Mvelocity += GRAVITY;
            cube.move(Vector2f(0, velocity));
           bad.move(Vector2f(0, Mvelocity));
        }

        

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (cubeBounds.intersects(wood.getGlobalBounds()))
            {
                isClimbing = true;
                cube.move(sf::Vector2f(0, -speed)); // Mueve al personaje hacia arriba
            }
        }

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || !cubeBounds.intersects(wood.getGlobalBounds()))
        {
            isClimbing = false;
        }

        if (!isClimbing)
        {
            // Resto del código para mover al personaje, detectar colisiones, etc.
        }

        if (cubeBounds.intersects(wood.getGlobalBounds())) {
            if (player.isFacingLeft) {
                cube.move(Vector2f(speed, 0)); // Revertir el movimiento hacia la izquierda
            }
            else {
                cube.move(Vector2f(-speed, 0)); // Revertir el movimiento hacia la derecha
            }
        }

        if (!isDashing) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && !isAttacking)
            {
                isAttacking = true;
              
            }
            if (Keyboard::isKeyPressed(Keyboard::Left)&& !Keyboard::isKeyPressed(Keyboard::Right)) {

                player.setFacingLeft(true);
                cube.move(Vector2f(-speed, 0));


                if (animationTimer.getElapsedTime().asSeconds() >= FRAME_TIME) {
                    currentWalkingFrame = (currentWalkingFrame + 1) % walkingFrames.size();
                    player.setTexture(walkingFrames[currentWalkingFrame]);
                    animationTimer.restart();
                }
                
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !isAttacking)
            {
                isCrouching = true;
                // Cambiar la textura del personaje al sprite de agacharse
                player.setTexture(agacharseTexture);
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)&& !Keyboard::isKeyPressed(Keyboard::Left)) {
                player.setFacingLeft(false);
                cube.move(Vector2f(speed, 0));
                if (animationTimer.getElapsedTime().asSeconds() >= FRAME_TIME) {
                    currentWalkingFrame = (currentWalkingFrame + 1) % walkingFrames.size();
                    player.setTexture(walkingFrames[currentWalkingFrame]);
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
                    cube.move(sf::Vector2f(0, velocity));
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
                if (animationTimer.getElapsedTime().asSeconds() >= FRAME_TIME) {
                    currentDashFrame = (currentDashFrame + 1) % dashFrames.size();
                    player.setTexture(dashFrames[currentDashFrame]);
                    animationTimer.restart();
                }
                if (player.isFacingLeft) {
                    cube.move(sf::Vector2f(-distance, 0));
                }
                else {
                    cube.move(sf::Vector2f(distance, 0));
                }
            }
            else {
                isDashing = false;
                player.setTexture(walkingFrames[currentWalkingFrame]);
            }
            
        }
        else {
          
        }

            view.setCenter(cube.getX(), view.getCenter().y);
            if (una)
            {
                view.setCenter(cube.getX(), cube.getY() );
                una = false;
            }

            // Después de actualizar la posición del personaje principal:
            sf::Vector2f viewCenter = view.getCenter();

            // Asegurarse de que la vista no se salga de los límites del fondo
            if (viewCenter.x < backgroundLimitTopLeft.x)
                viewCenter.x = backgroundLimitTopLeft.x;
            else if (viewCenter.x > backgroundLimitBottomRight.x)
                viewCenter.x = backgroundLimitBottomRight.x;

            if (viewCenter.y < backgroundLimitTopLeft.y)
                viewCenter.y = backgroundLimitTopLeft.y;
            else if (viewCenter.y > backgroundLimitBottomRight.y)
                viewCenter.y = backgroundLimitBottomRight.y;

            view.setCenter(viewCenter);


            
            window.clear(Color::Blue);
            window.setView(view);
            
            window.draw(castle);
            
            for (const auto& platform : platforms) {
                platform.drawTo(window);
            }
            
            player.drawTo(window);
            cube.draw(window);
            attack.draw(window);

            escalera1.drawTo(window);
            wood.drawTo(window);
            bad.draw(window);
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
