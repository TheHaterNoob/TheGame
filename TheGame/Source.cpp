#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1366, 768), "THE GAME");


    std::vector<sf::Texture> walkingFrames;
    for (int i = 1; i <= 2; i++) {
        sf::Texture frame;
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

    sf::Clock animationTimer;
    float frameTime = 0.4f;

    sf::Sprite player(walkingFrames[0]);
    player.setPosition(683, 384);

    sf::Texture platformTexture;
    if (!platformTexture.loadFromFile("platform.png")) {
        return -1;
    }
    sf::Sprite platform(platformTexture);
    platform.setPosition(683, 484);
    int currentFrame = 0;
    while (window.isOpen())
    {  
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (player.getGlobalBounds().intersects(platform.getGlobalBounds())) {
            
            player.setPosition(player.getPosition().x, platform.getPosition().y - player.getGlobalBounds().height);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.move(-0.4, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.move(0.4, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player.move(0, -0.4);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player.move(0, 0.4);
        if (animationTimer.getElapsedTime().asSeconds() >= frameTime) {
            currentFrame = (currentFrame + 1) % walkingFrames.size(); 
            player.setTexture(walkingFrames[currentFrame]);
            animationTimer.restart();
        }
        window.clear(sf::Color::Blue);
        window.draw(player);
        window.draw(platform);
        window.display();
    }

    return 0;
}