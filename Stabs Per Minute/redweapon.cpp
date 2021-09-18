#include "header.h"
#include "redweapon.h"

///Do aiming----------------------------------------------------------------------------------------------------
void RedWeapon::DoAiming(float deltaTime)
{
    ///Up
    if (red.aim == -1)
    {
        if (faceRight)
        {
            if (sprite.getRotation() < 360.0f && sprite.getRotation() >= 315.0f)
            {
                sprite.rotate(-abs(sprite.getRotation() - 315.0f) * 5.0f * deltaTime);
            }
            else if (sprite.getRotation() <= 45.0f && sprite.getRotation() >= 0.0f)
            {
                sprite.rotate(-abs(sprite.getRotation() + 45.0f) * 5.0f * deltaTime);
            }
            else
            {
                sprite.setRotation(315.0f);
            }
        }
        else
        {
            if (sprite.getRotation() >= 315.0f && sprite.getRotation() <= 360.0f)
            {
                sprite.rotate(abs((360.0f - sprite.getRotation()) + 45.0f) * 5.0f * deltaTime);
            }
            else if (sprite.getRotation() < 45.0f && sprite.getRotation() >= 0.0f)
            {
                sprite.rotate(abs(45.0f - sprite.getRotation()) * 5.0f * deltaTime);
            }
            else
            {
                sprite.setRotation(45.0f);
            }
        }
    }
    ///Middle
    else if (red.aim == 0)
    {
        if (sprite.getRotation() >= 315.0f)
        {
            sprite.rotate(abs(360.0f - sprite.getRotation()) * 5.0f * deltaTime);
        }
        else if (sprite.getRotation() <= 45.0f)
        {
            sprite.rotate(-abs(sprite.getRotation()) * 5.0f * deltaTime);
        }
        else
        {
            sprite.setRotation(0.0f);
        }
    }
    ///Down
    else if (red.aim == 1)
    {
        if (faceRight)
        {
            if (sprite.getRotation() >= 315.0f && sprite.getRotation() <= 360.0f)
            {
                sprite.rotate(abs((360.0f - sprite.getRotation()) + 45.0f) * 5.0f * deltaTime);
            }
            else if (sprite.getRotation() < 45.0f && sprite.getRotation() >= 0.0f)
            {
                sprite.rotate(abs(45.0f - sprite.getRotation()) * 5.0f * deltaTime);
            }
            else
            {
                sprite.setRotation(45.0f);
            }
        }
        else
        {
            if (sprite.getRotation() < 360.0f && sprite.getRotation() >= 315.0f)
            {
                sprite.rotate(-abs(sprite.getRotation() - 315.0f) * 5.0f * deltaTime);
            }
            else if (sprite.getRotation() <= 45.0f && sprite.getRotation() >= 0.0f)
            {
                sprite.rotate(-abs(sprite.getRotation() + 45.0f) * 5.0f * deltaTime);
            }
            else
            {
                sprite.setRotation(315.0f);
            }
        }
    }
}

///Update----------------------------------------------------------------------------------------------------
void RedWeapon::Update(float deltaTime)
{
    ///Switch states--------------------------------------------------
    ///Player state
    switch (red.state)
    {
        ///Dead
        case -1:
            state = -1;
            aim = 0;
            break;
        ///Idle
        case 0:
            state = 1;
            aim = red.aim;
            break;
        ///Walk
        case 1:
            state = 1;
            aim = red.aim;
            break;
        ///Run
        case 2:
            state = 0;
            aim = red.aim;
            break;
        ///Jump
        case 3:
            state = 0;
            aim = 0;
            break;
        ///Crouch
        case 4:
            state = 0;
            aim = 0;
            break;
        ///Slide
        case 5:
            state = 0;
            aim = 0;
            break;
        ///Attack
        case 6:
            if (red.faceRight)
            {
                if (red.velocity.x > 0.0f)
                {
                    state = 2;
                }
                else
                {
                    state = 1;
                }
            }
            else
            {
                if (red.velocity.x < 0.0f)
                {
                    state = 2;
                }
                else
                {
                    state = 1;
                }
            }
            break;
        ///Charge
        case 7:
            state = 0;
            break;
        ///Fleche
        case 8:
            state = 2;
            break;
        ///Smash
        case 9:
            state = 2;
            break;
        ///Surprise
        case 10:
            state = 2;
            break;
        ///Throw
        case 11:
            state = 0;
            break;
        ///Stunned
        case 12:
            state = 0;
            break;
        ///Hit
        case 13:
            state = 0;
            break;
        ///Stagger
        case 14:
            state = 0;
            break;
    }

    ///Weapons state
    switch(red.weapon)
    {
        ///Fist
        case 0:
            type = 0;
            ///Dead
            if (state == -1)
            {
                body.setSize(sf::Vector2f(0.0f, 0.0f));
            }
            ///Thrusting
            else if (state == 2)
            {
                body.setSize(sf::Vector2f(16.0f, 8.0f));
            }
            ///Not thrusting
            else
            {
                body.setSize(sf::Vector2f(8.0f, 8.0f));
            }
            body.setOrigin(sf::Vector2f(0.0f, body.getSize().y / 2.0f));
            break;
        ///Sword
        case 1:
            type = 1;
            ///Dead
            if (state == -1)
            {
                body.setSize(sf::Vector2f(0.0f, 0.0f));
            }
            ///Thrusting
            else if (state == 2)
            {
                body.setSize(sf::Vector2f(40.0f, 8.0f));
            }
            ///Not thrusting
            else
            {
                ///Aim
                ///Up
                if (aim == -1)
                {
                    body.setSize(sf::Vector2f(18.0f, 8.0f));
                }
                ///Middle
                else if (aim == 0)
                {
                    body.setSize(sf::Vector2f(24.0f, 8.0f));
                }
                ///Down
                else if (aim == 1)
                {
                    body.setSize(sf::Vector2f(18.0f, 8.0f));
                }
            }
            body.setOrigin(sf::Vector2f(0.0f, body.getSize().y / 2.0f));
            break;
    }

    if (faceRight)
    {
        ///Up
        if (aim == -1)
        {
            body.setPosition(sf::Vector2f(red.GetPosition().x + 4.0f, red.GetPosition().y));
        }
        ///Middle
        else if (aim == 0)
        {
            body.setPosition(sf::Vector2f(red.GetPosition().x + 4.0f, red.GetPosition().y + 8.0f));
        }
        ///Down
        else if (aim == 1)
        {
            body.setPosition(sf::Vector2f(red.GetPosition().x + 4.0f, red.GetPosition().y + 16.0f));
        }
        body.setRotation(0.0f);
    }
    else
    {
        ///Up
        if (aim == -1)
        {
            body.setPosition(sf::Vector2f(red.GetPosition().x - 4.0f, red.GetPosition().y));
        }
        ///Middle
        else if (aim == 0)
        {
            body.setPosition(sf::Vector2f(red.GetPosition().x - 4.0f, red.GetPosition().y + 8.0f));
        }
        ///Down
        else if (aim == 1)
        {
            body.setPosition(sf::Vector2f(red.GetPosition().x - 4.0f, red.GetPosition().y + 16.0f));
        }
        body.setRotation(180.0f);
    }

    ///Update animations--------------------------------------------------
    ///Face right
    if (red.faceRight)
    {
        faceRight = true;
        sprite.setOrigin(sf::Vector2f(0.0f, sprite.getSize().y / 2.0f));
    }
    ///Face left
    else
    {
        faceRight = false;
        sprite.setOrigin(sf::Vector2f(sprite.getSize().x, sprite.getSize().y / 2.0f));
    }
    UpdateAnimation(deltaTime);

    ///Set body position based on player texture--------------------------------------------------
    switch (red.animation.row)
    {
        case 0:
            switch (red.animation.column)
            {
                ///Idle
                case 0:
                case 1:
                case 2:
                case 3:
                    if (faceRight)
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x + 6.0f, red.GetPosition().y + 4.0f));
                    }
                    else
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x - 6.0f, red.GetPosition().y + 4.0f));
                    }
                    DoAiming(deltaTime);
                    break;
            }
            break;
        case 1:
            switch (red.animation.column)
            {
                ///Walk
                case 0:
                case 1:
                case 2:
                case 3:
                    if (faceRight)
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x + 6.0f, red.GetPosition().y + 4.0f));
                    }
                    else
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x - 6.0f, red.GetPosition().y + 4.0f));
                    }
                    DoAiming(deltaTime);
                    break;
                ///Run
                case 4:
                    if (faceRight)
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x + 4.0f, red.GetPosition().y + 4.0f));
                        sprite.setRotation(-75.0f);
                    }
                    else
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x - 4.0f, red.GetPosition().y + 4.0f));
                        sprite.setRotation(75.0f);
                    }
                    break;
                case 5:
                    if (faceRight)
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x + 4.0f, red.GetPosition().y + 6.0f));
                        sprite.setRotation(-65.0f);
                    }
                    else
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x - 4.0f, red.GetPosition().y + 6.0f));
                        sprite.setRotation(65.0f);
                    }
                    break;
                case 6:
                    if (faceRight)
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x + 4.0f, red.GetPosition().y + 6.0f));
                        sprite.setRotation(-60.0f);
                    }
                    else
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x - 4.0f, red.GetPosition().y + 6.0f));
                        sprite.setRotation(60.0f);
                    }
                    break;
            }
            break;
        case 2:
            switch (red.animation.column)
            {
                ///Jump
                case 0:
                    if (faceRight)
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x + 8.0f, red.GetPosition().y + 4.0f));
                        sprite.setRotation(-75.0f);
                    }
                    else
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x - 8.0f, red.GetPosition().y + 4.0f));
                        sprite.setRotation(75.0f);
                    }
                    break;
                case 1:
                    if (faceRight)
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x + 10.0f, red.GetPosition().y + 8.0f));
                        sprite.setRotation(-50.0f);
                    }
                    else
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x - 10.0f, red.GetPosition().y + 8.0f));
                        sprite.setRotation(50.0f);
                    }
                    break;
                ///Crouch
                case 2:
                    if (faceRight)
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x + 6.0f, red.GetPosition().y + 12.0f));
                        sprite.setRotation(5.0f);
                    }
                    else
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x - 6.0f, red.GetPosition().y + 12.0f));
                        sprite.setRotation(-5.0f);
                    }
                    break;
                case 3:
                    if (faceRight)
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x + 4.0f, red.GetPosition().y + 12.0f));
                        sprite.setRotation(5.0f);
                    }
                    else
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x - 4.0f, red.GetPosition().y + 12.0f));
                        sprite.setRotation(-5.0f);
                    }
                    break;
                ///Slide
                case 4:
                    if (faceRight)
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x - 0.0f, red.GetPosition().y + 16.0f));
                        sprite.setRotation(175.0f);
                    }
                    else
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x + 0.0f, red.GetPosition().y + 16.0f));
                        sprite.setRotation(-175.0f);
                    }
                    break;
                case 5:
                    if (faceRight)
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x - 2.0f, red.GetPosition().y + 16.0f));
                        sprite.setRotation(175.0f);
                    }
                    else
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x + 2.0f, red.GetPosition().y + 16.0f));
                        sprite.setRotation(-175.0f);
                    }
                    break;
            }
            break;
        case 3:
            switch (red.animation.column)
            {
                ///Attack
                case 0:
                case 1:
                case 2:
                case 3:
                    if (faceRight)
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x + 6.0f, red.GetPosition().y + 4.0f));
                    }
                    else
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x - 6.0f, red.GetPosition().y + 4.0f));
                    }
                    sprite.setRotation(0.0f);
                    break;
            }
            break;
        case 4:
            switch (red.animation.column)
            {
                ///Charge
                case 0:
                    if (faceRight)
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x - 10.0f, red.GetPosition().y + 4.0f));
                        sprite.setRotation(202.5f);
                    }
                    else
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x + 10.0f, red.GetPosition().y + 4.0f));
                        sprite.setRotation(-202.5f);
                    }
                    break;
                ///Fleche/Smash
                case 1:
                case 2:
                    if (faceRight)
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x + 6.0f, red.GetPosition().y + 4.0f));
                    }
                    else
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x - 6.0f, red.GetPosition().y + 4.0f));
                    }
                    sprite.setRotation(0.0f);
                    break;
                ///Surprise attack
                case 3:
                case 4:
                    if (faceRight)
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x + 6.0f, red.GetPosition().y + 4.0f));
                    }
                    else
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x - 6.0f, red.GetPosition().y + 4.0f));
                    }
                    sprite.setRotation(0.0f);
                    break;
                ///Throw
                case 5:
                    if (faceRight)
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x + 6.0f, red.GetPosition().y + 4.0f));
                    }
                    else
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x - 6.0f, red.GetPosition().y + 4.0f));
                    }
                    sprite.setRotation(0.0f);
                    break;
            }
            break;
        case 5:
            switch (red.animation.column)
            {
                ///Stunned
                case 0:
                case 1:
                    if (faceRight)
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x + 8.0f, red.GetPosition().y + 10.0f));
                        sprite.setRotation(-45.5f);
                    }
                    else
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x - 8.0f, red.GetPosition().y + 10.0f));
                        sprite.setRotation(45.5f);
                    }
                    break;
                ///Hit
                case 2:
                case 3:
                    if (faceRight)
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x + 8.0f, red.GetPosition().y + 6.0f));
                        sprite.setRotation(-70.5f);
                    }
                    else
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x - 8.0f, red.GetPosition().y + 6.0f));
                        sprite.setRotation(70.5f);
                    }
                    break;
                case 4:
                    if (faceRight)
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x + 8.0f, red.GetPosition().y + 8.0f));
                        sprite.setRotation(-70.5f);
                    }
                    else
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x - 8.0f, red.GetPosition().y + 8.0f));
                        sprite.setRotation(70.5f);
                    }
                    break;
            }
            break;
        case 6:
            switch (red.animation.column)
            {
                ///Stagger
                case 0:
                    if (faceRight)
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x + 8.0f, red.GetPosition().y + 10.0f));
                        sprite.setRotation(-45.5f);
                    }
                    else
                    {
                        sprite.setPosition(sf::Vector2f(red.GetPosition().x - 8.0f, red.GetPosition().y + 10.0f));
                        sprite.setRotation(45.5f);
                    }
                    break;
            }
            break;
    }
}
