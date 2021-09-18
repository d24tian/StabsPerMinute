#pragma once

#include <SFML/Graphics.hpp>

class Decoration
{
    public:
        ///Constructor functions
        Decoration(sf::Vector2f position, int type);
        ~Decoration();

        ///Update functions
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);

    private:
        sf::RectangleShape body;
        Animation animation;
        unsigned int row;
        unsigned int columnBegin;
        unsigned int columnEnd;
        int type;
        /**
        0 = Ground
        1 = Ground platform
        2 = Ceiling platform
        */
};
