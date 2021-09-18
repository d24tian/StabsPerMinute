#pragma once

#include "weapon.h"

class RedWeapon : public Weapon
{
    public:
        RedWeapon() :
            Weapon()
        {
            faceRight = false;
        }

        ~RedWeapon()
        {

        }

        ///Update functions
        void Update(float deltaTime);
        void DoAiming(float deltaTime);

    private:
};
