#pragma once

#include "player.h"

class Blue :
    public Player
{
    public:
        ///Constructor functions
        Blue(sf::Vector2f position) :
            Player(position)
        {
            this->faceRight = true;
            this->velocity.x = 1.0f;
        }

        ~Blue()
        {

        }

        ///Update functions
        void Update(float deltaTime);
        ///Management functions
        void Hurt(int damage);
        void Warp();

    private:
        ///Collision functions
        void CheckItemCollision(float deltaTime);
        void CheckWeaponCollision(float deltaTime);
        void CheckPlayerCollision(float deltaTime);
        ///State functions
        void DeadState(float deltaTime);
        void IdleState(float deltaTime);
        void WalkState(float deltaTime);
        void RunState(float deltaTime);
        void JumpState(float deltaTime);
        void CrouchState(float deltaTime);
        void SlideState(float deltaTime);
        void AttackState(float deltaTime);
        void ChargeState(float deltaTime);
        void FlecheState(float deltaTime);
        void SmashState(float deltaTime);
        void SurpriseState(float deltaTime);
        void ThrowState(float deltaTime);
        void StunnedState(float deltaTime);
        void HitState(float deltaTime);
        void WallState(float deltaTime);
};
