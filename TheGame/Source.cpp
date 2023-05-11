#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
const float GRAVITY = 0.5f;

float velocity = 0.0f;

int main()
{
    RenderWindow window(VideoMode(1366, 768), "THE GAME");
    window.setFramerateLimit(60);
    View view(Vector2f(0.0f,0.0f),Vector2f(400.0f,200.0f ));
    
    std::vector<sf::Texture> walkingFrames;
    for (int i = 1; i <= 2; i++) {
        Texture frame;
        if (!frame.loadFromFile("player" + std::to_string(i) + ".png")) {
     
            std::cerr << "Error loading frame " << i << std::endl;
        }
        else {
            walkingFrames.push_back(frame);
        }
    }

    if (walkingFrames.empty()) {
        return -1;
    }

    Clock animationTimer;
    float frameTime = 0.4f;

    Sprite player(walkingFrames[0]);
    player.setPosition(683, 384);

    Texture platformTexture;
    if (!platformTexture.loadFromFile("platform.png")) {
        return -1;
    }
    Sprite platform(platformTexture);
    platform.setPosition(683, 484);
    int currentFrame = 0;
    while (window.isOpen())
    {  
        Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == Event::Closed)
                window.close();
        }
        
        if (player.getGlobalBounds().intersects(platform.getGlobalBounds())) {
            player.setPosition(player.getPosition().x, platform.getPosition().y - player.getGlobalBounds().height);
            velocity = 0.0f;
        }
        else {
            velocity += GRAVITY;
            player.move(0, velocity);
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {


            player.move(-0.4, 0);
            if (animationTimer.getElapsedTime().asSeconds() >= frameTime) {
                currentFrame = (currentFrame + 1) % walkingFrames.size();
                player.setTexture(walkingFrames[currentFrame]);
                animationTimer.restart();
            }
        }
        if (sf::Keyboard::isKeyPressed(Keyboard::Right)) {
            player.move(0.4, 0);
            if (animationTimer.getElapsedTime().asSeconds() >= frameTime) {
                currentFrame = (currentFrame + 1) % walkingFrames.size();
                player.setTexture(walkingFrames[currentFrame]);
                animationTimer.restart();
            }
        }
        if (sf::Keyboard::isKeyPressed(Keyboard::Up) && player.getGlobalBounds().intersects(platform.getGlobalBounds())) {
            velocity = -10.0f;
            player.move(0, velocity);
            if (animationTimer.getElapsedTime().asSeconds() >= frameTime) {
                currentFrame = (currentFrame + 1) % walkingFrames.size();
                player.setTexture(walkingFrames[currentFrame]);
                animationTimer.restart();
            }
        }
        view.setCenter(player.getPosition().x, player.getPosition().y);
        
        window.clear(Color::Blue);
        window.setView(view);
        window.draw(platform);
        window.draw(player);
       
        
        window.display();
    }
    return 0;
}