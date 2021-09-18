#pragma once

#include <SFML/Graphics.hpp>

class Target
{
    public:
        ///Constructor functions
        Target();
        ~Target();

        ///Update functions
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);

    private:
        sf::RectangleShape body;
        sf::RectangleShape pulse;
        sf::RectangleShape arrow;
        Animation animation;
        int column;
        int lastFocus;
        float arrowTimer;
        float arrowPosition;
};
