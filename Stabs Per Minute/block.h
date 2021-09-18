#pragma once

#include <SFML/Graphics.hpp>

class Block
{
    public:
        ///Constructor functions
        Block(sf::Vector2f position);
        ~Block();

        ///Update functions
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);
        ///Information functions
        sf::Vector2f GetPosition() {return body.getPosition();}
        sf::Vector2f GetHalfSize() {return body.getSize() / 2.0f;}

    private:
        sf::RectangleShape body;
        Animation animation;
};
