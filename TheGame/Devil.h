#include "SFML/Graphics.hpp"
class Devil {
private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    float acceleration;

public:
    Devil(sf::Vector2f position, sf::Vector2f size, float acceleration)
        : acceleration(acceleration)
    {
        shape.setSize(size);
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Red);
    }

    void update(float deltaTime, sf::RenderWindow& window) {
        // Update velocity based on acceleration
        velocity.x -= acceleration * deltaTime;

        // Update position based on velocity
        shape.move(velocity * deltaTime);

        // Check if enemy hits the left side of the view
        if (shape.getPosition().x < 0) {
            shape.setPosition(0, shape.getPosition().y);
            velocity.x *= -1;  // Switch direction
        }

        // Check if enemy hits the right side of the view
        if (shape.getPosition().x + shape.getSize().x > window.getSize().x) {
            shape.setPosition(window.getSize().x - shape.getSize().x, shape.getPosition().y);
            velocity.x *= -1;  // Switch direction
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }
    void setTexture(const sf::Texture& texture) {
        shape.setTexture(&texture);
    }
    void setPos(sf::Vector2f newPos) {
        shape.setPosition(newPos);
    }
};


