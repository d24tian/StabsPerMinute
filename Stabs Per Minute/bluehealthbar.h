#pragma once

#include "healthbar.h"

class BlueHealthBar : public HealthBar
{
    public:
        BlueHealthBar() :
            HealthBar()
        {

        }

        ~BlueHealthBar()
        {

        }

        ///Update functions
        void Pulse(float deltaTime);
        void Update(float deltaTime);

    private:
};
