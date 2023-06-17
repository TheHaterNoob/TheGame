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
#include "Enemigo.h"
#include "Canon.h"
#include "TrampaWorm.h"

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
bool isAttacking2 = false;
const float ROLL_FRAME_SPEED = 2.0f;
const float ROLL_DISTANCE = 2.0f;

bool isAttacking = false;
bool isCrouching = false;
const Vector2f backgroundLimitTopLeft(720, 0);
const Vector2f backgroundLimitBottomRight(2130, 421);
int currentAttackFrame = 0;
int currentWalkingFrame = 0;
int currentDashFrame = 0;
bool isClimbing = false;
const float attackCooldown = 10.0f;
float attackTimer = 0.0f;
float pushDuration = 0.5f;    // Duration of the push in seconds
float pushTimer = 0.0f;       // Timer for push duration
float pushForce = 0.69f;     // Force to push the enemy
bool isPushing = false;
sf::Vector2f enemyPosition;
sf::Vector2f pushDirection;
bool canAttackA;
bool wasAKeyPressed = false;
bool canAttackS;
bool wasSKeyPressed = false;

bool canDash;
bool wasDashPressed = false;

bool isRolling = false;
int currentRollFrame = 0;
bool isPerformingAction = false;

int currentIdleFrame = 0;

bool isWalkingCrouched = false;
    RenderWindow window(VideoMode(1366, 768), "THE GAME", Style::Fullscreen);


std::vector<Platform> platforms;
sf::Vector2f normalize(const sf::Vector2f& vector)
{
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);

    if (length != 0.0f)
        return sf::Vector2f(vector.x / length, vector.y / length);
    else
        return vector;
}
void secondLevel()
{
   
   


    std::vector<sf::Texture> wormFrames(11);
    for (int i = 1; i <= 11; i++)
    {
        if (!wormFrames[i - 1].loadFromFile("worm" + std::to_string(i) + ".png"))
        {
            std::cerr << "Error loading second attack frame " << i << std::endl;
        }
    }

    TrampaWorm gusano1(wormFrames, sf::Vector2f(793, 467));
    TrampaWorm gusano2(wormFrames, sf::Vector2f(864, 467));
    TrampaWorm gusano3(wormFrames, sf::Vector2f(935, 467));
    TrampaWorm gusano4(wormFrames, sf::Vector2f(1006, 467));
 


    std::vector<sf::Texture> attackFrames2(6);
    for (int i = 1; i <= 6; i++)
    {
        if (!attackFrames2[i - 1].loadFromFile("2ataque_" + std::to_string(i) + ".png"))
        {
            std::cerr << "Error loading second attack frame " << i << std::endl;
        }
    }


    //LADDER
    sf::Texture woodTexture;
    if (!woodTexture.loadFromFile("escalar.png"))
    {
        std::cerr << "Error loading ladder texture" << std::endl;
    }

    Platform wood(woodTexture, Vector2f(855, 430));

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

    std::vector<Texture> idleEnemigo(4);
    for (int i = 1; i <= 4; i++)
    {
        if (!idleEnemigo[i - 1].loadFromFile("en_idle" + std::to_string(i) + ".png"))
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

    std::vector<sf::Texture> idleFrames(9);
    for (int i = 1; i <= 9; i++)
    {
        if (!idleFrames[i - 1].loadFromFile("idle" + std::to_string(i) + ".png"))
        {
            std::cerr << "Error loading idle frame " << i << std::endl;
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

    std::vector<sf::Texture> rollFrames(12);
    for (int i = 1; i <= 12; i++)
    {
        if (!rollFrames[i - 1].loadFromFile("roll" + std::to_string(i) + ".png"))
        {
            std::cerr << "Error loading roll frame " << i << std::endl;
        }
    }



    if (walkingFrames.empty())
    {
        // Logic to handle the case when no frames are loaded
    }
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);
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

    Enemigo enemigo(Vector2f(20.00f, 38.00f));
    enemigo.setTexture(idleEnemigo[0]);

    std::vector<Texture> escalandoFrames(1);
    if (!escalandoFrames[0].loadFromFile("escalando.png")) {
        std::cerr << "Error loading escalando frame" << std::endl;
    }

    Texture platformTexture;
    if (!platformTexture.loadFromFile("suelof.png"))
    {
        // Logic to handle the error when loading the platform texture
    }
    Platform platform(platformTexture, Vector2f(683, 484));


    Texture puertaTexture;
    if (!puertaTexture.loadFromFile("puerta.png"))
    {
        // Logic to handle the error when loading the platform texture
    }
    Sprite puerta(puertaTexture);
    puerta.setPosition(2250, 427);

    Texture signoTexture;
    if (!signoTexture.loadFromFile("letrero1.png"))
    {
        // Logic to handle the error when loading the platform texture
    }
    Sprite signo(signoTexture);
    signo.setPosition(570, 465);


    Texture lamparaTexture;
    if (!lamparaTexture.loadFromFile("lampara.png"))
    {
        //error
    }
    Sprite lampara(lamparaTexture);
    lampara.setPosition(900, 375);

    Sprite lampara2(lamparaTexture);
    lampara2.setPosition(1050, 375);

    Sprite lampara3(lamparaTexture);
    lampara3.setPosition(1200, 375);

    Sprite lampara4(lamparaTexture);
    lampara4.setPosition(1350, 375);

    Texture trampaTexture;
    if (!trampaTexture.loadFromFile("spikes.png"))
    {
        //error
    }
    Sprite trampa(trampaTexture);
    trampa.setPosition(1470, 478);

    Sprite trampa2(trampaTexture);
    trampa2.setPosition(1485, 478);

    Sprite trampa3(trampaTexture);
    trampa3.setPosition(1495, 478);

    Texture castleTexture;
    if (!castleTexture.loadFromFile("segundo.png"))
    {
        std::cerr << "Error loading castle texture" << std::endl;
    }

    Sprite castle(castleTexture);
    castle.setPosition(435, 260);

    sf::Sprite fondoDuplicadoSprite(castleTexture);
    fondoDuplicadoSprite.setPosition(1250, 260);


    platforms.push_back(Platform(platformTexture, Vector2f(509, 496)));
    platforms.push_back(Platform(platformTexture, Vector2f(580, 496)));
    platforms.push_back(Platform(platformTexture, Vector2f(651, 496)));
    platforms.push_back(Platform(platformTexture, Vector2f(722, 496)));
    platforms.push_back(Platform(platformTexture, Vector2f(793, 496)));
    platforms.push_back(Platform(platformTexture, Vector2f(864, 496)));
    platforms.push_back(Platform(platformTexture, Vector2f(935, 496)));
    platforms.push_back(Platform(platformTexture, Vector2f(1006, 496)));



    sf::Time deltaTime = clock1.restart();
 
    float dt = deltaTime.asSeconds();

    while (window.isOpen())
    {
       
        gusano1.cargar(dt);
        gusano2.cargar(dt);
        gusano3.cargar(dt);
        gusano4.cargar(dt);



        isPerformingAction = false;


        if (attackTimer > 0.0f)
        {
            attackTimer -= dt;
        }
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
            Vector2f vec(cube.getX() + 16, cube.getY() + 14);
            player.setPosition(vec);
        }
        else {
            Vector2f vec(cube.getX() + 4, cube.getY() + 14);
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
            Mvelocity += (GRAVITY - 0.23f);
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !isAttacking && !isCrouching && !isDashing)
        {
            isRolling = true;
            currentRollFrame = 0;
            float rollFrameTime = FRAME_TIME * ROLL_FRAME_SPEED;



        }


        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || !cubeBounds.intersects(wood.getGlobalBounds()))
        {
            isClimbing = false;
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
            bool isAKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
            if (isAKeyPressed && !wasAKeyPressed && !isAttacking && !isAttacking2 && attackTimer <= 0.0f && canAttackA)
            {
                isAttacking = true;
                attackTimer = attackCooldown;
                canAttackA = false;


            }
            wasAKeyPressed = isAKeyPressed;
            if (!isAKeyPressed)
            {
                canAttackA = true;


            }
            bool isSKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
            if (isSKeyPressed && !wasSKeyPressed && !isAttacking && !isAttacking2 && attackTimer <= 0.0f)
            {
                isAttacking2 = true;
                attackTimer = attackCooldown;
                canAttackS = false;


            }

            wasSKeyPressed = isSKeyPressed;
            if (!isSKeyPressed)
            {
                canAttackS = true;

            }

            if (Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right)) {

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

                currentIdleFrame = 0;
                animationTimer.restart();

                isPerformingAction = true;

            }
            if (Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left)) {
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
        bool isDashKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
        if (isDashKeyPressed && !wasDashPressed && !isDashing) {
            isDashing = true;
            dashTime = 0.0f;
            canDash = false;
        }
        wasDashPressed = isDashKeyPressed;
        if (!isDashKeyPressed)
        {
            canDash = true;
        }

        if (isRolling)
        {
            currentRollFrame++;
            if (currentRollFrame >= rollFrames.size())
            {
                // Se ha completado la animación de roll
                isRolling = false;
                // Restablecer el frame actual para otras animaciones si es necesario
                currentWalkingFrame = 0;
            }
            else
            {
                player.setTexture(rollFrames[currentRollFrame]);
            }
            animationTimer.restart();


            float rollMovement = ROLL_DISTANCE * dt;
            if (player.isFacingLeft)
            {
                cube.move(sf::Vector2f(-rollMovement, 0.0f));
            }
            else
            {
                cube.move(sf::Vector2f(rollMovement, 0.0f));
            }

            currentIdleFrame = 0;
            animationTimer.restart();

            isPerformingAction = true;
        }

        if (isAttacking2)
        {
            if (player.isFacingLeft)
            {
                veck = Vector2f(cube.getX() - 30, cube.getY() + 1);
            }
            else {
                veck = Vector2f(cube.getX() + 30, cube.getY() + 1);
            }
            if (currentAttackFrame < attackFrames2.size())
            {
                sf::Texture& attackFrame = attackFrames2[currentAttackFrame];
                player.setTexture(attackFrame);

                attack.setPosition(veck);
                currentAttackFrame++;
                if (attack.getGlobalBounds().intersects(bad.getGlobalBounds()))
                {
                    pushDirection = normalize(sf::Vector2f(bad.getPosition().x - cube.getPosition().x, bad.getPosition().y - cube.getPosition().y));

                    // Start pushing the enemy
                    isPushing = true;
                    pushTimer = 0.0f;
                    Mvelocity = 0.0f;
                }
                currentIdleFrame = 0;
                animationTimer.restart();

                isPerformingAction = true;
            }
            else
            {
                attack.setPosition(sf::Vector2f(-100.0f, -100.0f));
                isAttacking2 = false;
                currentAttackFrame = 0;

                currentIdleFrame = 0;
                animationTimer.restart();

                isPerformingAction = true;
            }
        }
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
                if (attack.getGlobalBounds().intersects(bad.getGlobalBounds()))
                {
                    pushDirection = normalize(sf::Vector2f(bad.getPosition().x - cube.getPosition().x, bad.getPosition().y - cube.getPosition().y));

                    // Start pushing the enemy
                    isPushing = true;
                    pushTimer = 0.0f;
                    Mvelocity = 0.0f;
                }

                currentIdleFrame = 0;
                animationTimer.restart();

                isPerformingAction = true;
            }
            else
            {
                attack.setPosition(sf::Vector2f(-100.0f, -100.0f));
                isAttacking = false;
                currentAttackFrame = 0;
            }
            currentIdleFrame = 0;
            animationTimer.restart();

            isPerformingAction = true;
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

        if (isPushing)
        {

            // Calculate the push distance based on elapsed time and push duration
            float pushDistance = pushForce * (1.0f - pushTimer / pushDuration);

            // Apply the push force to move the enemy
            sf::Vector2f pushVector = pushDirection * pushDistance;
            pushVector.y -= pushDistance * 3.0f;  // Adjust the vertical component of the push force

            bad.move(pushVector);

            // Update the push timer
            pushTimer += deltaTime.asSeconds();

            // Check if the push duration has ended
            if (pushTimer >= pushDuration)
            {
                // Stop pushing the enemy
                isPushing = false;
            }
            currentIdleFrame = 0;
            animationTimer.restart();

            isPerformingAction = true;
        }

        if (!isPerformingAction)
        {
            // Ejecutar la animación de idle
            if (animationTimer.getElapsedTime().asSeconds() >= FRAME_TIME)
            {
                if (currentIdleFrame >= idleFrames.size())
                {
                    currentIdleFrame = 0;
                }
                player.setTexture(idleFrames[currentIdleFrame]);
                currentIdleFrame++;
                animationTimer.restart();
            }
        }

        view.setCenter(cube.getX(), view.getCenter().y);
        if (una)
        {
            view.setCenter(cube.getX(), cube.getY());
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
        window.draw(fondoDuplicadoSprite);
     
        window.draw(castle);
     
       

        for (const auto& platform : platforms) {
            platform.drawTo(window);
        }

        player.drawTo(window);
        cube.draw(window);
        attack.draw(window);
        gusano1.draw(window);
        gusano2.draw(window);
        gusano3.draw(window);
        gusano4.draw(window);
        
        enemigo.drawTo(window);
        bad.draw(window);
        window.display();
    }
}

void game()
{

    std::vector<sf::Texture> canonTextures(7);
    for (int i = 1; i <= 7; i++)
    {
        if (!canonTextures[i - 1].loadFromFile("cañon" + std::to_string(i) + ".png"))
        {
            std::cerr << "Error loading canon texture " << i << std::endl;
        }
    }
    Canon canon(canonTextures, sf::Vector2f(1845, 447));

    //BASE DE ESCALERA
    sf::Texture escaleraTexture;
    if (!escaleraTexture.loadFromFile("escalera1.png"))
    {
        std::cerr << "Error loading escalera1 texture" << std::endl;
    }

    Platform escalera1(escaleraTexture, Vector2f(857, 430));




    std::vector<sf::Texture> attackFrames2(6);
    for (int i = 1; i <= 6; i++)
    {
        if (!attackFrames2[i - 1].loadFromFile("2ataque_" + std::to_string(i) + ".png"))
        {
            std::cerr << "Error loading second attack frame " << i << std::endl;
        }
    }


    //LADDER
    sf::Texture woodTexture;
    if (!woodTexture.loadFromFile("escalar.png"))
    {
        std::cerr << "Error loading ladder texture" << std::endl;
    }

    Platform wood(woodTexture, Vector2f(855, 430));

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

    std::vector<Texture> idleEnemigo(4);
    for (int i = 1; i <= 4; i++)
    {
        if (!idleEnemigo[i - 1].loadFromFile("en_idle" + std::to_string(i) + ".png"))
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

    std::vector<sf::Texture> idleFrames(9);
    for (int i = 1; i <= 9; i++)
    {
        if (!idleFrames[i - 1].loadFromFile("idle" + std::to_string(i) + ".png"))
        {
            std::cerr << "Error loading idle frame " << i << std::endl;
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

    std::vector<sf::Texture> rollFrames(12);
    for (int i = 1; i <= 12; i++)
    {
        if (!rollFrames[i - 1].loadFromFile("roll" + std::to_string(i) + ".png"))
        {
            std::cerr << "Error loading roll frame " << i << std::endl;
        }
    }

    

    if (walkingFrames.empty())
    {
        // Logic to handle the case when no frames are loaded
    }
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);
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

    Enemigo enemigo(Vector2f(20.00f, 38.00f));
    enemigo.setTexture(idleEnemigo[0]);
    
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


    Texture puertaTexture;
    if (!puertaTexture.loadFromFile("puerta.png"))
    {
        // Logic to handle the error when loading the platform texture
    }
    Sprite puerta(puertaTexture);
    puerta.setPosition(2250, 427);

    Texture signoTexture;
    if (!signoTexture.loadFromFile("letrero1.png"))
    {
        // Logic to handle the error when loading the platform texture
    }
    Sprite signo(signoTexture);
    signo.setPosition(570, 465);


    Texture lamparaTexture;
    if (!lamparaTexture.loadFromFile("lampara.png"))
    {
        //error
    }
    Sprite lampara(lamparaTexture);
    lampara.setPosition(900, 375);

    Sprite lampara2(lamparaTexture);
    lampara2.setPosition(1050, 375);

    Sprite lampara3(lamparaTexture);
    lampara3.setPosition(1200, 375);

    Sprite lampara4(lamparaTexture);
    lampara4.setPosition(1350, 375);

    Texture trampaTexture;
    if (!trampaTexture.loadFromFile("spikes.png"))
    {
        //error
    }
    Sprite trampa(trampaTexture);
    trampa.setPosition(1470, 478);

    Sprite trampa2(trampaTexture);
    trampa2.setPosition(1485, 478);

    Sprite trampa3(trampaTexture);
    trampa3.setPosition(1495, 478);

    Texture castleTexture;
    if (!castleTexture.loadFromFile("fondo.png"))
    {
        std::cerr << "Error loading castle texture" << std::endl;
    }

    Sprite castle(castleTexture);
    castle.setPosition(435, 260);

    sf::Sprite fondoDuplicadoSprite(castleTexture);
    fondoDuplicadoSprite.setPosition(1380, 260);



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
    platforms.push_back(Platform(platformTexture, Vector2f(1292, 430)));
    platforms.push_back(Platform(platformTexture, Vector2f(1379, 430)));

    platforms.push_back(Platform(platformTexture, Vector2f(1466, 496)));
    platforms.push_back(Platform(platformTexture, Vector2f(1553, 496)));
    platforms.push_back(Platform(platformTexture, Vector2f(1640, 496)));
    platforms.push_back(Platform(platformTexture, Vector2f(1727, 496)));
    platforms.push_back(Platform(platformTexture, Vector2f(1814, 496)));
    platforms.push_back(Platform(platformTexture, Vector2f(1901, 496)));
    platforms.push_back(Platform(platformTexture, Vector2f(1988, 496)));
    platforms.push_back(Platform(platformTexture, Vector2f(2075, 496)));
    platforms.push_back(Platform(platformTexture, Vector2f(2162, 496)));
    platforms.push_back(Platform(platformTexture, Vector2f(2249, 496)));

    sf::Time deltaTime = clock1.restart();
    platforms.push_back(escalera1);
    platforms.push_back(wood);
    float dt = deltaTime.asSeconds();

  
    // Update the attack cooldown timer


    


    while (window.isOpen())
    {
        canon.update(dt);
      

        isPerformingAction = false;


        if (attackTimer > 0.0f)
        {
            attackTimer -= dt;
        }
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
            Mvelocity += (GRAVITY-0.23f);
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !isAttacking && !isCrouching && !isDashing)
        {
            isRolling = true;
            currentRollFrame = 0;
            float rollFrameTime = FRAME_TIME * ROLL_FRAME_SPEED;


           
        }


        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || !cubeBounds.intersects(wood.getGlobalBounds()))
        {
            isClimbing = false;
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
            bool isAKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
                if (isAKeyPressed && !wasAKeyPressed  && !isAttacking && !isAttacking2 && attackTimer <= 0.0f && canAttackA)
                {
                    isAttacking = true;
                    attackTimer = attackCooldown;
                    canAttackA = false;

                   
                }
                wasAKeyPressed = isAKeyPressed;
                if (!isAKeyPressed)
                {
                    canAttackA = true;

                    
                }
                bool isSKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
                if (isSKeyPressed && !wasSKeyPressed && !isAttacking && !isAttacking2 && attackTimer <= 0.0f)
                {
                    isAttacking2 = true;
                    attackTimer = attackCooldown;
                    canAttackS = false;

                    
                }
                
                wasSKeyPressed = isSKeyPressed;
                if (!isSKeyPressed)
                {
                    canAttackS = true;
                   
                }

                if (Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right)) {

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

                    currentIdleFrame = 0;
                    animationTimer.restart();

                    isPerformingAction = true;

                }
                if (Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left)) {
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
        bool isDashKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
        if (isDashKeyPressed && !wasDashPressed && !isDashing) {
            isDashing = true;
            dashTime = 0.0f;
            canDash = false;
        }
        wasDashPressed = isDashKeyPressed;
        if (!isDashKeyPressed)
        {
            canDash = true;
        }

        if (isRolling)
        {
            currentRollFrame++;
            if (currentRollFrame >= rollFrames.size())
            {
                // Se ha completado la animación de roll
                isRolling = false;
                // Restablecer el frame actual para otras animaciones si es necesario
                currentWalkingFrame = 0;
            }
            else
            {
                player.setTexture(rollFrames[currentRollFrame]);
            }
            animationTimer.restart();


            float rollMovement = ROLL_DISTANCE * dt;
            if (player.isFacingLeft)
            {
                cube.move(sf::Vector2f(-rollMovement, 0.0f));
            }
            else
            {
                cube.move(sf::Vector2f(rollMovement, 0.0f));
            }

            currentIdleFrame = 0;
            animationTimer.restart();

            isPerformingAction = true;
        }

        if (isAttacking2)
        {
            if (player.isFacingLeft)
            {
                veck = Vector2f(cube.getX() - 30, cube.getY() + 1);
            }
            else {
                veck = Vector2f(cube.getX() + 30, cube.getY() + 1);
            }
            if (currentAttackFrame < attackFrames2.size())
            {
                sf::Texture& attackFrame = attackFrames2[currentAttackFrame];
                player.setTexture(attackFrame);

                attack.setPosition(veck);
                currentAttackFrame++;
                if (attack.getGlobalBounds().intersects(bad.getGlobalBounds()))
                {
                    pushDirection = normalize(sf::Vector2f(bad.getPosition().x - cube.getPosition().x, bad.getPosition().y - cube.getPosition().y));

                    // Start pushing the enemy
                    isPushing = true;
                    pushTimer = 0.0f;
                    Mvelocity = 0.0f;
                }
                currentIdleFrame = 0;
                animationTimer.restart();

                isPerformingAction = true;
            }
            else
            {
                attack.setPosition(sf::Vector2f(-100.0f, -100.0f));
                isAttacking2 = false;
                currentAttackFrame = 0;

                currentIdleFrame = 0;
                animationTimer.restart();

                isPerformingAction = true;
            }
        }
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
                if (attack.getGlobalBounds().intersects(bad.getGlobalBounds()))
                {
                    pushDirection = normalize(sf::Vector2f(bad.getPosition().x - cube.getPosition().x, bad.getPosition().y - cube.getPosition().y));

                    // Start pushing the enemy
                    isPushing = true;
                    pushTimer = 0.0f;
                    Mvelocity = 0.0f;
                }

                currentIdleFrame = 0;
                animationTimer.restart();

                isPerformingAction = true;
            }
            else
            {
                attack.setPosition(sf::Vector2f(-100.0f, -100.0f));
                isAttacking = false;
                currentAttackFrame = 0;
            }
            currentIdleFrame = 0;
            animationTimer.restart();

            isPerformingAction = true;
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

        if (isPushing)
        {

            // Calculate the push distance based on elapsed time and push duration
            float pushDistance = pushForce * (1.0f - pushTimer / pushDuration);

            // Apply the push force to move the enemy
            sf::Vector2f pushVector = pushDirection * pushDistance;
            pushVector.y -= pushDistance * 3.0f;  // Adjust the vertical component of the push force

            bad.move(pushVector);

            // Update the push timer
            pushTimer += deltaTime.asSeconds();

            // Check if the push duration has ended
            if (pushTimer >= pushDuration)
            {
                // Stop pushing the enemy
                isPushing = false;
            }
            currentIdleFrame = 0;
            animationTimer.restart();

            isPerformingAction = true;
        }

        if (!isPerformingAction)
        {
            // Ejecutar la animación de idle
            if (animationTimer.getElapsedTime().asSeconds() >= FRAME_TIME)
            {
                if (currentIdleFrame >= idleFrames.size())
                {
                    currentIdleFrame = 0;
                }
                player.setTexture(idleFrames[currentIdleFrame]);
                currentIdleFrame++;
                animationTimer.restart();
            }
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
            window.draw(fondoDuplicadoSprite);
            canon.draw(window);
            window.draw(castle);
            window.draw(puerta);
            window.draw(signo);
            window.draw(lampara);
            window.draw(lampara2);
            window.draw(lampara3);
            window.draw(lampara4);
            window.draw(trampa);
            window.draw(trampa2);
            window.draw(trampa3);
         
            for (const auto& platform : platforms) {
                platform.drawTo(window);
            }
            
            player.drawTo(window);
            cube.draw(window);
            attack.draw(window);
  
            escalera1.drawTo(window);
            wood.drawTo(window);
            enemigo.drawTo(window);
            bad.draw(window);
            window.display();
        }
    }


menu::menu(int width, int height)
{
    font.loadFromFile("fuente3.ttf");

    mainmenu[0].setFont(font);
    mainmenu[0].setFillColor(Color::White);
    mainmenu[0].setString("Primer Nivel");
    mainmenu[0].setCharacterSize(120);
    mainmenu[0].setPosition(Vector2f(400, height / 4));


    mainmenu[1].setFont(font);
    mainmenu[1].setFillColor(Color::Red);
    mainmenu[1].setString("Segundo Nivel");
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
            if (pagenum == 1)
            {
                secondLevel();
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
