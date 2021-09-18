#pragma once

#include <SFML/Graphics.hpp>

class Corpse
{
    public:
        Corpse(sf::Vector2f position, sf::Vector2f velocity, int colour);
        ~Corpse();
        ///Update functions
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);
        ///Information functions
        sf::Vector2f GetPosition() {return body.getPosition();}
        sf::Vector2f GetHalfSize() {return body.getSize() / 2.0f;}
        ///Physics functions
        float DistanceToBlock(int direction);
        /**
        0 = Below player
        1 = Above player
        2 = To the left of player
        3 = To the right of player
        */
        void CheckCollision(float deltaTime);

        ///Display
        sf::RectangleShape body;
        sf::RectangleShape sprite;
        Animation animation;
        int row;
        int column;
        bool faceRight;
        int colour;
        ///Movement
        sf::Vector2f velocity;
        ///State
        int state;
        /**
        0 = Lying on face
        1 = Lying on back
        2 = Skeleton lying on face
        3 = Skeleton lying on back
        */

    private:
};
