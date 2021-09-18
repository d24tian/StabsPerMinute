#pragma once

#include "animation.h"
#include <SFML/Graphics.hpp>

class HealthBar
{
    public:
        HealthBar();
        ~HealthBar();

        ///Update functions
        void Draw(sf::RenderWindow& window);
        ///Information functions
        sf::Vector2f GetPosition() {return body.getPosition();}
        sf::Vector2f GetHalfSize() {return body.getSize() / 2.0f;}
        ///Management functions
        void SetPosition(sf::Vector2f position)
        {
            body.setPosition(position);
            frame.setPosition(position);
            number.setPosition(sf::Vector2f(position.x, position.y + 32.0f));
        }

        ///Display
        sf::RectangleShape body;
        sf::RectangleShape frame;
        sf::Text number;
        Animation animation;
        ///State
        float pulseTimer;

    private:
};
