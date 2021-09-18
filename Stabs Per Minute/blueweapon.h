#pragma once

#include "weapon.h"

class BlueWeapon : public Weapon
{
    public:
        BlueWeapon() :
            Weapon()
        {
            faceRight = true;
        }

        ~BlueWeapon()
        {

        }

        ///Update functions
        void Update(float deltaTime);
        void DoAiming(float deltaTime);

    private:
};
