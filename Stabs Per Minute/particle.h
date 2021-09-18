#pragma once

#include <SFML/Graphics.hpp>

class Particle
{
    public:
        ///Constructor functions
        Particle(sf::Vector2f position, sf::Vector2f startSize, int row, int column, bool faceRight);
        ~Particle();

        ///Update functions
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);

        ///State
        bool finished;

    private:
        ///Display
        sf::RectangleShape body;
        Animation animation;
        int row;
        int column;
        bool faceRight;
};
