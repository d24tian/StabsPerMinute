#pragma once

#include "animation.h"
#include <SFML/Graphics.hpp>

class Weapon
{
    public:
        Weapon();
        ~Weapon();

        ///Update functions
        void UpdateAnimation(float deltaTime);
        void Draw(sf::RenderWindow& window);
        ///Information functions
        sf::Vector2f GetPosition() {return body.getPosition();}
        sf::Vector2f GetHalfSize() {return body.getSize() / 2.0f;}
        ///Management functions
        void SetPosition(sf::Vector2f position) {body.setPosition(position);}
        void SetRow(int index) {row = index;}
        void SetColumn (int index) {column = index;}
        ///Physics functions
        float DistanceToBlock(int direction);

        ///Display
        sf::RectangleShape body;
        sf::RectangleShape sprite;
        Animation animation;
        int row;
        int column;
        bool faceRight;
        ///State
        int type;
        /**
        0 = Fists
        1 = Sword
        */
        int aim;
        /**
        -1 = Up
        0 = Middle
        1 = Down
        */
        int state;
        /**
        0 = Inactive
        1 = Active
        2 = Thrust
        */
        bool statePrevious; ///??????????

    private:
};
