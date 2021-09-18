#pragma once

#include <SFML/Graphics.hpp>

class Spike
{
    public:
        ///Constructor functions
        Spike(sf::Vector2f position);
        ~Spike();

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
