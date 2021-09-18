#pragma once

#include "healthbar.h"

class RedHealthBar : public HealthBar
{
    public:
        RedHealthBar() :
            HealthBar()
        {

        }

        ~RedHealthBar()
        {

        }

        ///Update functions
        void Pulse(float deltaTime);
        void Update(float deltaTime);

    private:
};

