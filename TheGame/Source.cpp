#include <SFML/Graphics.hpp>

int main()
{
    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Platform Game");

    // Load player texture
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("player.png")) {
        // Error loading texture
        return -1;
    }

    // Create player sprite
    sf::Sprite player(playerTexture);
    player.setPosition(400, 300);

    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Move the player sprite with arrow keys
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.move(-1, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.move(1, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player.move(0, -1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player.move(0, 1);

        // Clear screen
        window.clear(sf::Color::Blue);

        // Draw game objects
        window.draw(player);

        // Update the window
        window.display();
    }

    return 0;
}