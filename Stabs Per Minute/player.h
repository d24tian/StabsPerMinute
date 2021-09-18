#pragma once

#include "animation.h"
#include <SFML/Graphics.hpp>

class Player
{
    public:
        ///Constructor functions
        Player(sf::Vector2f position);
        ~Player();

        ///Update functions
        void UpdateAnimation(float deltaTime);
        void Draw(sf::RenderWindow& window);
        ///Information functions
        sf::Vector2f GetPosition() {return body.getPosition();}
        sf::Vector2f GetHalfSize() {return body.getSize() / 2.0f;}
        bool GetWeaponCollision();
        ///Management functions
        void SetRow(int index) {row = index;}
        void SetColumn (int indexBegin, int indexEnd) {columnBegin = indexBegin; columnEnd = indexEnd;}
        void SetSize(sf::Vector2f size) {body.setSize(size);}
        void SetVelocity(float x, float y)
        {
            velocity.x = x;
            velocity.y = y;
        }
        void MoveBody(sf::Vector2f move) {body.move(move);}
        void MoveSprite(sf::Vector2f move) {sprite.move(move);}
        void SetPosition(sf::Vector2f position) {body.setPosition(position);}
        void SetSpritePosition(sf::Vector2f position) {sprite.setPosition(position);}
        void Reset();
        ///Physics functions
        float DistanceToBlock(int direction);
        /**
        0 = Below player
        1 = Above player
        2 = To the left of player
        3 = To the right of player
        */
        void CheckCollision(float deltaTime);
        sf::Vector2f FindSpawn(sf::Vector2f position, int index);

        ///Display
        sf::RectangleShape body;
        sf::RectangleShape sprite;
        Animation animation;
        int row;
        int columnBegin;
        int columnEnd;
        float switchTime;
        bool faceRight;
        ///Movement
        sf::Vector2f velocity;
        float speed;
        float jumpHeight;
        ///State
        bool canJump;
        bool canGoLeft;
        bool canGoRight;
        int state;
        /**
        -2 = PLEASE DELETE ME
        -1 = Dead
        0 = Idle/Guard
        1 = Walk
        2 = Run
        3 = Jump
        4 = Crouch
        5 = Slide
        6 = Attack
        7 = Charge
        8 = Fleche
        9 = Smash
        10 = Surprise
        11 = Throw
        12 = Stunned
        13 = Hit
        14 = Stagger
        15 = Wall
        */
        int stateBefore;
        int weapon;
        /**
        0 = Fists/nothing
        1 = Sword
        */
        int aim;
        /**
        -1 = Up
        0 = Middle
        1 = Down
        */
        int hitDirection;
        /**
        -1 = Up
        0 = Middle
        1 = Down
        2 = Back
        */
        bool canAttack;
        float attackPosition;
        float stateTimer;
        int health;
        float graceTimer;
        float deathTimer;
        int stateSwitchImmunity;

    private:
};
