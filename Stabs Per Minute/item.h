#pragma once

#include "animation.h"
#include <SFML/Graphics.hpp>

class Item
{
    public:
        Item(sf::Vector2f position, sf::Vector2f velocity, int type, int immunity);
        ~Item();
        ///Update functions
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);
        ///Information functions
        sf::Vector2f GetPosition() {return body.getPosition();}
        sf::Vector2f GetHalfSize() {return body.getSize() / 2.0f;}
        ///Physics functions
        int GetPlayerCollision(float deltaTime);
        void CheckWeaponCollision(float deltaTime);
        void CheckPlayerCollision(float deltaTime);
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
        ///Movement
        sf::Vector2f velocity;
        ///State
        int type;
        /**
        0 = Sword
        1 = Pistol
        */
        int immunity; ///To avoid collision when item has just been thrown
        /**
        -1 = None
        0 = Blue
        1 = Red
        */

    private:
};
