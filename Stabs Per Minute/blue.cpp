#include "header.h"
#include "blue.h"

///Item collision----------------------------------------------------------------------------------------------------
void Blue::CheckItemCollision(float deltaTime)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i].immunity == -1)
        {
            sf::Vector2f otherPos = items[i].GetPosition();
            sf::Vector2f otherHalfSize = items[i].GetHalfSize();
            sf::Vector2f thisPos = GetPosition();
            sf::Vector2f thisHalfSize = GetHalfSize();

            float deltaX = otherPos.x - thisPos.x;
            float deltaY = otherPos.y - thisPos.y;

            float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
            float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

            if (intersectX < 0.0f && intersectY < 0.0f)
            {
                ///Crouch or slide
                if (state == 4 || state == 5)
                {
                    if (weapon == 0)
                    {
                        weapon = items[i].type;
                        items.erase(items.begin() + i);
                    }
                }
                ///Not crouch or slide
                else
                {
                    ///Item has velocity
                    if (abs(items[i].velocity.y) > 98.1f)
                    {
                        ///Sword
                        if (items[i].type == 1)
                        {
                            Hurt(50);
                        }
                    }
                }
            }
        }
    }
}

///Weapon collision----------------------------------------------------------------------------------------------------
void Blue::CheckWeaponCollision(float deltaTime)
{
    sf::Vector2f otherPos;
    if (redWeapon.faceRight)
    {
        otherPos = sf::Vector2f(redWeapon.GetPosition().x + (redWeapon.body.getSize().x / 2.0f), redWeapon.GetPosition().y);
    }
    else
    {
        otherPos = sf::Vector2f(redWeapon.GetPosition().x - (redWeapon.body.getSize().x / 2.0f), redWeapon.GetPosition().y);
    }
    sf::Vector2f otherHalfSize = redWeapon.GetHalfSize();
    sf::Vector2f thisPos = GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();

    float deltaX = otherPos.x - thisPos.x;
    float deltaY = otherPos.y - thisPos.y;

    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if (intersectX < 0.0f && intersectY < 0.0f)
    {
        if (graceTimer <= 0.0f)
        {
            ///Fists
            if (redWeapon.type == 0)
            {
                ///Thrust
                if (redWeapon.state == 2)
                {
                    ///Hit from back
                    if (faceRight == redWeapon.faceRight)
                    {
                        ///Fleche, smash, or surprise
                        if (red.state == 8 || red.state == 9 || red.state == 10)
                        {
                            Hurt(20);
                            hitDirection = 2;
                            if (redWeapon.faceRight)
                            {
                                velocity.x += 490.5f;
                            }
                            else
                            {
                                velocity.x = -490.5f;
                            }
                        }
                        ///Normal attack
                        else
                        {
                            Hurt(16);
                            hitDirection = 2;
                            if (redWeapon.faceRight)
                            {
                                velocity.x += 490.5f;
                            }
                            else
                            {
                                velocity.x = -490.5f;
                            }
                        }

                        ///Reset enemy velocity
                        if (red.state == 6 || red.state == 8 || red.state == 10)
                        {
                            red.velocity.x *= 0.5f;
                        }
                    }
                    ///Blocked
                    else if (GetWeaponCollision())
                    {
                        ///Collision on right
                        if (red.GetPosition().x > GetPosition().x)
                        {
                            body.move((intersectX - otherHalfSize.x) * 2.0f * deltaTime, 0.0f);
                            red.body.move(-(intersectX - otherHalfSize.x) * 2.0f * deltaTime, 0.0f);
                        }
                        ///Collision on left
                        else if (red.GetPosition().x < GetPosition().x)
                        {
                            body.move(-(intersectX - otherHalfSize.x) * 2.0f * deltaTime, 0.0f);
                            red.body.move((intersectX - otherHalfSize.x) * 2.0f * deltaTime, 0.0f);
                        }
                    }
                    ///Hit from front
                    else
                    {
                        ///Fleche, smash, or surprise
                        if (red.state == 8 || red.state == 9 || red.state == 10)
                        {
                            Hurt(16);
                            hitDirection = redWeapon.aim;
                            if (redWeapon.faceRight)
                            {
                                velocity.x = 490.5f;
                            }
                            else
                            {
                                velocity.x = -490.5f;
                            }
                        }
                        ///Normal attack
                        else
                        {
                            Hurt(10);
                            hitDirection = redWeapon.aim;
                            if (redWeapon.faceRight)
                            {
                                velocity.x = 490.5f;
                            }
                            else
                            {
                                velocity.x = -490.5f;
                            }
                        }

                        ///Reset enemy velocity
                        if (red.state == 6 || red.state == 8 || red.state == 10)
                        {
                            red.velocity.x *= 0.5f;
                        }
                    }
                }
            }
            ///Sword
            else if (redWeapon.type == 1)
            {
                ///Thrust
                if (redWeapon.state == 2)
                {
                    ///Hit from back
                    if (faceRight == redWeapon.faceRight)
                    {
                        ///Fleche, smash, or surprise
                        if (red.state == 8 || red.state == 9 || red.state == 10)
                        {
                            Hurt(80);
                            hitDirection = 2;
                            if (redWeapon.faceRight)
                            {
                                velocity.x = 490.5f;
                            }
                            else
                            {
                                velocity.x = -490.5f;
                            }
                        }
                        ///Normal attack
                        else
                        {
                            Hurt(60);
                            hitDirection = 2;
                            if (redWeapon.faceRight)
                            {
                                velocity.x = 490.5f;
                            }
                            else
                            {
                                velocity.x = -490.5f;
                            }
                        }

                        ///Reset enemy velocity
                        if (red.state == 6 || red.state == 8 || red.state == 10)
                        {
                            red.velocity.x *= 0.5f;
                        }
                    }
                    ///Blocked
                    else if (GetWeaponCollision() && weapon == 1 && blueWeapon.state != 0)
                    {
                        ///Collision on right
                        if (red.GetPosition().x > GetPosition().x)
                        {
                            body.move((intersectX - otherHalfSize.x) * 2.0f * deltaTime, 0.0f);
                            red.body.move(-(intersectX - otherHalfSize.x) * 2.0f * deltaTime, 0.0f);
                        }
                        ///Collision on left
                        else if (red.GetPosition().x < GetPosition().x)
                        {
                            body.move(-(intersectX - otherHalfSize.x) * 2.0f * deltaTime, 0.0f);
                            red.body.move((intersectX - otherHalfSize.x) * 2.0f * deltaTime, 0.0f);
                        }
                    }
                    ///Hit from front
                    else
                    {
                        ///Fleche, smash, or surprise
                        if (red.state == 8 || red.state == 9 || red.state == 10)
                        {
                            Hurt(60);
                            hitDirection = redWeapon.aim;
                            if (redWeapon.faceRight)
                            {
                                velocity.x = 490.5f;
                            }
                            else
                            {
                                velocity.x = -490.5f;
                            }
                        }
                        ///Normal attack
                        else
                        {
                            Hurt(40);
                            hitDirection = redWeapon.aim;
                            if (redWeapon.faceRight)
                            {
                                velocity.x = 490.5f;
                            }
                            else
                            {
                                velocity.x = -490.5f;
                            }
                        }

                        ///Reset enemy velocity
                        if (red.state == 6 || red.state == 8 || red.state == 10)
                        {
                            red.velocity.x *= 0.5f;
                        }
                    }
                }
                ///Active
                else if (redWeapon.state == 1)
                {
                    ///Check state
                    if (state != 3 && state != 4 && state != 5 && state != 6 && state != 7 && state != 8 && state != 9 && state != 10)
                    {
                        ///Hit from back
                        if (faceRight == redWeapon.faceRight)
                        {
                            if (deltaY < GetHalfSize().y / 4.0f * 3.0f)
                            {
                                ///Fleche, smash, or surprise
                                if (red.state == 8 || red.state == 9 || red.state == 10)
                                {
                                    Hurt(80);
                                    hitDirection = 2;
                                    if (redWeapon.faceRight)
                                    {
                                        velocity.x = 490.5f;
                                    }
                                    else
                                    {
                                        velocity.x = -490.5f;
                                    }

                                }
                                ///Normal attack
                                else
                                {
                                    Hurt(60);
                                    hitDirection = 2;
                                    if (redWeapon.faceRight)
                                    {
                                        velocity.x = 490.5f;
                                    }
                                    else
                                    {
                                        velocity.x = -490.5f;
                                    }
                                }
                            }
                        }
                        ///Blocked
                        else if (GetWeaponCollision() && weapon == 1)
                        {
                            ///Collision on right
                            if (red.GetPosition().x > GetPosition().x)
                            {
                                body.move((intersectX - otherHalfSize.x) * 2.0f * deltaTime, 0.0f);
                                red.body.move(-(intersectX - otherHalfSize.x) * 2.0f * deltaTime, 0.0f);
                            }
                            ///Collision on left
                            else if (red.GetPosition().x < GetPosition().x)
                            {
                                body.move(-(intersectX - otherHalfSize.x) * 2.0f * deltaTime, 0.0f);
                                red.body.move((intersectX - otherHalfSize.x) * 2.0f * deltaTime, 0.0f);
                            }
                        }
                        ///Hit from front
                        else
                        {
                            if (deltaY < GetHalfSize().y / 4.0f * 3.0f)
                            {
                                ///Fleche, smash, or surprise
                                if (red.state == 8 || red.state == 9 || red.state == 10)
                                {
                                    Hurt(60);
                                    hitDirection = redWeapon.aim;
                                    if (redWeapon.faceRight)
                                    {
                                        velocity.x = 490.5f;
                                    }
                                    else
                                    {
                                        velocity.x = -490.5f;
                                    }

                                }
                                ///Normal attack
                                else
                                {
                                    Hurt(40);
                                    hitDirection = redWeapon.aim;
                                    if (redWeapon.faceRight)
                                    {
                                        velocity.x = 490.5f;
                                    }
                                    else
                                    {
                                        velocity.x = -490.5f;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        else
        {

        }
    }
}

///Player collision----------------------------------------------------------------------------------------------------
void Blue::CheckPlayerCollision(float deltaTime)
{
    if (red.state != -1 && red.state != 5)
    {
        ///Player collision
        sf::Vector2f otherPos = red.GetPosition();
        sf::Vector2f otherHalfSize = red.GetHalfSize();
        sf::Vector2f thisPos = GetPosition();
        sf::Vector2f thisHalfSize = GetHalfSize();

        float deltaX = otherPos.x - thisPos.x;
        float deltaY = otherPos.y - thisPos.y;

        float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
        float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

        float crossX = abs(deltaX) - (otherHalfSize.x + 1.0f);// / 4.0f);
        float crossY = abs(deltaY) - (otherHalfSize.x + 1.0f);// / 4.0f);

        if (crossX < 0.0f && crossY < 0.0f)
        {
            ///Collision on right
            if (deltaX > 0.0f)
            {
                body.move(crossX / 2.0f, 0.0f);
                red.body.move(-crossX / 2.0f, 0.0f);
                canGoRight = false;
                canGoLeft = true;
            }
            ///Collision on left
            else if (deltaX < 0.0f)
            {
                body.move(-crossX / 2.0f, 0.0f);
                red.body.move(crossX / 2.0f, 0.0f);
                canGoLeft = false;
                canGoRight = true;
            }
        }
        else if (intersectX < 0.0f && intersectY < 0.0f)
        {
            ///Collision on right
            if (deltaX > 0.0f)
            {
                body.move(intersectX * 2.0f * deltaTime, 0.0f);
                red.body.move(-intersectX * 2.0f * deltaTime, 0.0f);
                canGoRight = false;
                canGoLeft = true;
            }
            ///Collision on left
            else if (deltaX < 0.0f)
            {
                body.move(-intersectX * 2.0f * deltaTime, 0.0f);
                red.body.move(intersectX * 2.0f * deltaTime, 0.0f);
                canGoLeft = false;
                canGoRight = true;
            }

            ///Below
            if (deltaY > 0.0f && velocity.y > 0.0f)
            {
                velocity.y = -sqrt(981.0f * jumpHeight / 8.0f);
                ///Left
                if (deltaX > 0.0f)
                {
                    red.velocity.x = 490.5;
                }
                ///Right
                else if (deltaX < 0.0f)
                {
                    red.velocity.x = -490.5;
                }
                red.state = 12;
            }
            ///Above
            else if (deltaY < 0.0f && red.velocity.y > 0.0f)
            {
                ///Left
                if (deltaX > 0.0f)
                {
                    velocity.x = -490.5;
                }
                ///Right
                else if (deltaX < 0.0f)
                {
                    velocity.x = 490.5;
                }
                state = 12;
            }
        }
        else
        {
            canGoLeft = true;
            canGoRight = true;
        }
    }
    else
    {
        canGoLeft = true;
        canGoRight = true;
    }
}

///Dead state----------------------------------------------------------------------------------------------------
void Blue::DeadState(float deltaTime)
{
    ///Do physics--------------------------------------------------
    velocity.x = 0.0f;
    velocity.y = 0.0f;

    ///Determine direction--------------------------------------------------
    faceRight = true;

    ///Set position--------------------------------------------------
    body.setPosition(red.GetPosition());

    ///Set body size to (0, 0)--------------------------------------------------
    body.setSize(sf::Vector2f(0.0f, 0.0f));

    ///Switch states--------------------------------------------------
    if (state == -1)
    {
        if (stateTimer > 3.0f)
        {
            body.setSize(sf::Vector2f(16.0f, 32.0f));
            ///Restart game
            if (area == 3)
            {
                area = 0;
                body.setPosition(sf::Vector2f(-64.0f, 128.0f));
                red.SetSize(sf::Vector2f(16.0f, 32.0f));
                red.SetPosition(sf::Vector2f(64.0f, 128.0f));
                red.health = 100;
                red.weapon = 1;
                red.stateTimer = 0.0f;
                red.velocity.x = -1.0f;
                red.state = 0;
                focus = -1;
            }
            else
            {
                Warp();
            }
            health = 100;
            weapon = 1;
            stateTimer = 0.0f;
            velocity.x = 1.0f;
            state = 0;
        }
        else
        {
            stateTimer += deltaTime;
        }
    }
}

///Idle state----------------------------------------------------------------------------------------------------
void Blue::IdleState(float deltaTime)
{
    ///Do physics--------------------------------------------------
    ///Decrease horizontal movement speed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !canGoLeft)
    {
        velocity.x *= 0.98f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !canGoRight)
    {
        velocity.x *= 0.98f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || velocity.y != 0.0f)
    {
        velocity.x *= 0.998f;
    }
    else
    {
        velocity.x *= 0.9f;
    }

    ///Restrict maximum horizontal movement speed
    if (velocity.x > 122.625f)
    {
        velocity.x = 122.625f;
    }
    if (velocity.x < -122.625f)
    {
        velocity.x = -122.625f;
    }

    ///Set X velocity to 0 when small enough
    if (abs(velocity.x) < 0.1f)
    {
        velocity.x = 0.0f;
    }

    ///Add to and limit gravity
    if (velocity.y < 490.5f)
    {
        velocity.y += 1716.75f * deltaTime;//9.81f;
    }
    else
    {
        velocity.y = 490.5f;
    }

    ///Detect input--------------------------------------------------
    ///Movement
    ///Left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        velocity.x -= speed / 2.0f;
    }

    ///Right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        velocity.x += speed / 2.0f;
    }

    ///Shift
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if (canJump)
            {
                velocity.y = -sqrt(981.0f * jumpHeight / 4.0f);
            }
            canJump = false;
        }
    }

    ///Attack
    ///Aim
    ///Both up and down pressed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        aim = 0;
    }
    ///Up
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        aim = -1;
    }
    ///Down
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        aim = 1;
    }
    ///Nothing is pressed
    else
    {
        aim = 0;
    }

    ///Ctrl
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && canAttack)
    {
        if (faceRight)
        {
            velocity.x = 490.5f;
        }
        else
        {
            velocity.x = -490.5f;
        }
    }

    ///Do collision--------------------------------------------------
    CheckItemCollision(deltaTime);
    CheckWeaponCollision(deltaTime);
    CheckPlayerCollision(deltaTime);
    CheckCollision(deltaTime);

    ///Move--------------------------------------------------
    body.move(velocity * deltaTime);

    ///Determine direction--------------------------------------------------
    if (abs(red.GetPosition().x - GetPosition().x) < 128.0f)
    {
        if (red.GetPosition().x > GetPosition().x && !red.faceRight && faceRight)
        {

        }
        else if (red.GetPosition().x < GetPosition().x && red.faceRight && !faceRight)
        {

        }
        else
        {
            if (velocity.x > 0.0f)
            {
                faceRight = true;
            }
            else if (velocity.x < 0.0f)
            {
                faceRight = false;
            }
        }
    }
    else
    {
        if (velocity.x > 0.0f)
        {
            faceRight = true;
        }
        else if (velocity.x < 0.0f)
        {
            faceRight = false;
        }
    }

    ///Switch states--------------------------------------------------
    if (state == 0)
    {
        ///Attack
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && canAttack)
        {
            attackPosition = body.getPosition().x;
            state = 6;
            canAttack = false;
        }
        ///Jump
        else if (velocity.y != 0.0f)
        {
            state = 3;
        }
        ///Crouch
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            state = 4;
        }
        ///Run
        else if (abs(red.GetPosition().x - GetPosition().x) > 128.0f && velocity.x != 0.0f)
        {
            state = 2;
        }
        else if (abs(red.GetPosition().x - GetPosition().x) < 128.0f && red.GetPosition().x > GetPosition().x && velocity.x != 0.0f)
        {
            if (red.faceRight || !faceRight)
            {
                state = 2;
            }
            ///Walk
            else if (abs(red.GetPosition().x - GetPosition().x) < 128.0f && velocity.x != 0.0f)
            {
                state = 1;
            }
        }
        else if (abs(red.GetPosition().x - GetPosition().x) < 128.0f && red.GetPosition().x < GetPosition().x && velocity.x != 0.0f)
        {
            if (!red.faceRight || faceRight)
            {
                state = 2;
            }
            ///Walk
            else if (abs(red.GetPosition().x - GetPosition().x) < 128.0f && velocity.x != 0.0f)
            {
                state = 1;
            }
        }
        ///Walk
        else if (abs(red.GetPosition().x - GetPosition().x) < 128.0f && velocity.x != 0.0f)
        {
            state = 1;
        }
    }
}

///Walk state----------------------------------------------------------------------------------------------------
void Blue::WalkState(float deltaTime)
{
    ///Do physics--------------------------------------------------
    ///Decrease horizontal movement speed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !canGoLeft)
    {
        velocity.x *= 0.98f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !canGoRight)
    {
        velocity.x *= 0.98f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || velocity.y != 0.0f)
    {
        velocity.x *= 0.998f;
    }
    else
    {
        velocity.x *= 0.9f;
    }

    ///Restrict maximum horizontal movement speed
    if (velocity.x > 122.625f)
    {
        velocity.x = 122.625f;
    }
    if (velocity.x < -122.625f)
    {
        velocity.x = -122.625f;
    }

    ///Set X velocity to 0 when small enough
    if (abs(velocity.x) < 0.1f)
    {
        velocity.x = 0.0f;
    }

    ///Add to and limit gravity
    if (velocity.y < 490.5f)
    {
        velocity.y += 1716.75f * deltaTime;//9.81f;
    }
    else
    {
        velocity.y = 490.5f;
    }

    ///Detect input--------------------------------------------------
    ///Movement
    ///Left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        velocity.x -= speed / 2.0f;
    }

    ///Right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        velocity.x += speed / 2.0f;
    }

    ///Shift
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if (canJump)
            {
                velocity.y = -sqrt(981.0f * jumpHeight / 4.0f);
            }
            canJump = false;
        }
    }

    ///Attack
    ///Aim
    ///Both up and down pressed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        aim = 0;
    }
    ///Up
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        aim = -1;
    }
    ///Down
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        aim = 1;
    }
    ///Nothing is pressed
    else
    {
        aim = 0;
    }

    ///Ctrl
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && canAttack)
    {
        if (faceRight)
        {
            velocity.x = 490.5f;
        }
        else
        {
            velocity.x = -490.5f;
        }
    }

    ///Do collision--------------------------------------------------
    CheckItemCollision(deltaTime);
    CheckWeaponCollision(deltaTime);
    CheckPlayerCollision(deltaTime);
    CheckCollision(deltaTime);

    ///Move--------------------------------------------------
    body.move(velocity * deltaTime);

    ///Determine direction--------------------------------------------------
    if (abs(red.GetPosition().x - GetPosition().x) < 128.0f)
    {
        if (red.GetPosition().x > GetPosition().x && !red.faceRight && faceRight)
        {

        }
        else if (red.GetPosition().x < GetPosition().x && red.faceRight && !faceRight)
        {

        }
        else
        {
            if (velocity.x > 0.0f)
            {
                faceRight = true;
            }
            else if (velocity.x < 0.0f)
            {
                faceRight = false;
            }
        }
    }
    else
    {
        if (velocity.x > 0.0f)
        {
            faceRight = true;
        }
        else if (velocity.x < 0.0f)
        {
            faceRight = false;
        }
    }

    ///Switch states--------------------------------------------------
    if (state == 1)
    {
        ///Attack
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && canAttack)
        {
            attackPosition = body.getPosition().x;
            state = 6;
            canAttack = false;
        }
        ///Jump
        else if (velocity.y != 0.0f)
        {
            state = 3;
        }
        ///Crouch
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            state = 4;
        }
        ///Run
        else if (red.state == -1) ///Enemy is dead
        {
            state = 2;
        }
        else if (abs(red.GetPosition().x - GetPosition().x) > 128.0f && velocity.x != 0.0f)
        {
            state = 2;
        }
        else if (abs(red.GetPosition().x - GetPosition().x) < 128.0f && red.GetPosition().x > GetPosition().x && velocity.x != 0.0f)
        {
            if (red.faceRight || !faceRight)
            {
                state = 2;
            }
        }
        else if (abs(red.GetPosition().x - GetPosition().x) < 128.0f && red.GetPosition().x < GetPosition().x && velocity.x != 0.0f)
        {
            if (!red.faceRight || faceRight)
            {
                state = 2;
            }
        }
        ///Idle
        else if (velocity.x == 0.0f)
        {
            state = 0;
        }
    }
}

///Run state----------------------------------------------------------------------------------------------------
void Blue::RunState(float deltaTime)
{
    ///Do physics--------------------------------------------------
    ///Decrease horizontal movement speed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !canGoLeft)
    {
        velocity.x *= 0.98f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !canGoRight)
    {
        velocity.x *= 0.98f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || velocity.y != 0.0f)
    {
        velocity.x *= 0.998f;
    }
    else
    {
        velocity.x *= 0.9f;
    }

    ///Restrict maximum horizontal movement speed
    if (velocity.x > 245.25f)
    {
        velocity.x = 245.25f;
    }
    if (velocity.x < -245.25f)
    {
        velocity.x = -245.25f;
    }

    ///Set X velocity to 0 when small enough
    if (abs(velocity.x) < 0.1f)
    {
        velocity.x = 0.0f;
    }

    ///Add to and limit gravity
    if (velocity.y < 490.5f)
    {
        velocity.y += 1716.75f * deltaTime;//9.81f;
    }
    else
    {
        velocity.y = 490.5f;
    }

    ///Detect input--------------------------------------------------
    ///Movement
    ///Left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        velocity.x -= speed;
    }

    ///Right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        velocity.x += speed;
    }

    ///Shift
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if (canJump)
            {
                velocity.y = -sqrt(981.0f * jumpHeight / 4.0f);
            }
            canJump = false;
        }
    }

    ///Attack
    ///Aim
    ///Both up and down pressed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        aim = 0;
    }
    ///Up
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        aim = -1;
    }
    ///Down
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        aim = 1;
    }
    ///Nothing is pressed
    else
    {
        aim = 0;
    }

    ///Do collision--------------------------------------------------
    CheckItemCollision(deltaTime);
    CheckWeaponCollision(deltaTime);
    CheckPlayerCollision(deltaTime);
    CheckCollision(deltaTime);

    ///Move--------------------------------------------------
    body.move(velocity * deltaTime);

    ///Determine direction--------------------------------------------------
    if (velocity.x > 0.0f)
    {
        faceRight = true;
    }
    else if (velocity.x < 0.0f)
    {
        faceRight = false;
    }

    ///Release particles--------------------------------------------------
    if (rand() % 10 < abs(velocity.x) / 100.0f)
    {
        int startSize = (rand() % 4) + 4;
        particles.push_back(Particle(sf::Vector2f(body.getPosition().x + float((rand() % int(body.getSize().x))) - (body.getSize().x / 2.0f), body.getPosition().y + (body.getSize().y / 2.0f) - 16.0f), sf::Vector2f(startSize, startSize), 0, rand() % 4, bool(rand() % 2)));
    }

    ///Switch states--------------------------------------------------
    if (state == 2)
    {
        ///Fleche
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && canAttack)
        {
            state = 7;
            canAttack = false;
        }
        ///Jump
        else if (velocity.y != 0.0f)
        {
            state = 3;
        }
        ///Slide
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            state = 5;
        }
        ///Idle
        else if (velocity.x == 0.0f)
        {
            state = 0;
        }
    }
}

///Jump state----------------------------------------------------------------------------------------------------
void Blue::JumpState(float deltaTime)
{
    ///Do physics--------------------------------------------------
    ///Decrease horizontal movement speed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !canGoLeft)
    {
        velocity.x *= 0.98f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !canGoRight)
    {
        velocity.x *= 0.98f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || velocity.y != 0.0f)
    {
        velocity.x *= 0.998f;
    }
    else
    {
        velocity.x *= 0.9f;
    }

    ///Restrict maximum horizontal movement speed
    if (velocity.x > 245.25f)
    {
        velocity.x = 245.25f;
    }
    if (velocity.x < -245.25f)
    {
        velocity.x = -245.25f;
    }

    ///Set X velocity to 0 when small enough
    if (abs(velocity.x) < 0.1f)
    {
        velocity.x = 0.0f;
    }

    ///Add to and limit gravity
    if (velocity.y < 490.5f)
    {
        velocity.y += 1716.75f * deltaTime;//9.81f;
    }
    else
    {
        velocity.y = 490.5f;
    }

    ///Detect input--------------------------------------------------
    ///Movement
    ///Left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        velocity.x -= speed;
    }

    ///Right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        velocity.x += speed;
    }

    ///Do collision--------------------------------------------------
    CheckItemCollision(deltaTime);
    CheckWeaponCollision(deltaTime);
    CheckPlayerCollision(deltaTime);
    CheckCollision(deltaTime);

    ///Move--------------------------------------------------
    body.move(velocity * deltaTime);

    ///Determine direction--------------------------------------------------
    if (velocity.x > 0.0f)
    {
        faceRight = true;
    }
    else if (velocity.x < 0.0f)
    {
        faceRight = false;
    }

    ///Switch states--------------------------------------------------
    if (state == 3)
    {
        ///Smash
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        {
            state = 7;
        }
        ///Stunned
        else if (DistanceToBlock(1) <= 1.0f)
        {
            ///Release particles
            for (int i = 0; i < (rand() % 4) + 12; i++)
            {
                int startSize = (rand() % 4) + 4;
                particles.push_back(Particle(sf::Vector2f(body.getPosition().x + float((rand() % int(body.getSize().x))) - (body.getSize().x / 2.0f), body.getPosition().y - (body.getSize().y / 2.0f)), sf::Vector2f(startSize, startSize), 0, rand() % 4, bool(rand() % 2)));
            }

            state = 12;
        }
        ///Wall, facing left
        else if (DistanceToBlock(2) <= 1.0f && velocity.y > 0.0f && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            faceRight = true;
            state = 14;
        }
        ///Wall, facing right
        else if (DistanceToBlock(3) <= 1.0f && velocity.y > 0.0f && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            faceRight = false;
            state = 14;
        }
        else if (DistanceToBlock(0) == 0.0f)
        {
            ///Release particles
            for (int i = 0; i < (rand() % 4) + 12; i++)
            {
                int startSize = (rand() % 4) + 4;
                particles.push_back(Particle(sf::Vector2f(body.getPosition().x + float((rand() % int(body.getSize().x))) - (body.getSize().x / 2.0f), body.getPosition().y + (body.getSize().y / 2.0f) - 16.0f), sf::Vector2f(startSize, startSize), 0, rand() % 4, bool(rand() % 2)));
            }

            ///Run
            if (velocity.x > 49.05f || velocity.x < -49.05f)
            {
                state = 2;
            }
            ///Idle
            else if (velocity.x < 49.05f && velocity.x > -49.05f)
            {
                state = 0;
            }
        }
    }
}

///Crouch state----------------------------------------------------------------------------------------------------
void Blue::CrouchState(float deltaTime)
{
    ///Do physics--------------------------------------------------
    ///Decrease horizontal movement speed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !canGoLeft)
    {
        velocity.x *= 0.98f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !canGoRight)
    {
        velocity.x *= 0.98f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || velocity.y != 0.0f)
    {
        velocity.x *= 0.998f;
    }
    else
    {
        velocity.x *= 0.9f;
    }

    ///Restrict maximum horizontal movement speed
    if (velocity.x > 122.625f)
    {
        velocity.x = 122.625f;
    }
    if (velocity.x < -122.625f)
    {
        velocity.x = -122.625f;
    }

    ///Set X velocity to 0 when small enough
    if (abs(velocity.x) < 0.1f)
    {
        velocity.x = 0.0f;
    }

    ///Add to and limit gravity
    if (velocity.y < 490.5f)
    {
        velocity.y += 1716.75f * deltaTime;//9.81f;
    }
    else
    {
        velocity.y = 490.5f;
    }

    ///Detect input--------------------------------------------------
    ///Movement
    ///Left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        velocity.x -= speed / 16.0f;
    }

    ///Right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        velocity.x += speed / 16.0f;
    }

    ///Do collision--------------------------------------------------
    CheckItemCollision(deltaTime);
    CheckWeaponCollision(deltaTime);
    CheckPlayerCollision(deltaTime);
    CheckCollision(deltaTime);

    ///Move--------------------------------------------------
    body.move(velocity * deltaTime);

    ///Determine direction--------------------------------------------------
    if (velocity.x > 0.0f)
    {
        faceRight = true;
    }
    else if (velocity.x < 0.0f)
    {
        faceRight = false;
    }

    ///Switch states--------------------------------------------------
    if (state == 4)
    {
        ///Surprise attack
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && canAttack)
        {
            canAttack = false;
            if (faceRight)
            {
                velocity.x = 245.25f;
                state = 10;
            }
            else
            {
                velocity.x = -245.25f;
                state = 10;
            }
        }
        ///Idle
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            state = 0;
        }
    }
}

///Slide state----------------------------------------------------------------------------------------------------
void Blue::SlideState(float deltaTime)
{
    ///Do physics--------------------------------------------------
    ///Decrease horizontal movement speed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !canGoLeft)
    {
        velocity.x *= 0.98f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !canGoRight)
    {
        velocity.x *= 0.98f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || velocity.y != 0.0f)
    {
        velocity.x *= 0.998f;
    }
    else
    {
        velocity.x *= 0.9f;
    }

    ///Restrict maximum horizontal movement speed
    if (velocity.x > 245.25f)
    {
        velocity.x = 245.25f;
    }
    if (velocity.x < -245.25f)
    {
        velocity.x = -245.25f;
    }

    ///Set X velocity to 0 when small enough
    if (abs(velocity.x) < 0.1f)
    {
        velocity.x = 0.0f;
    }

    ///Add to and limit gravity
    if (velocity.y < 490.5f)
    {
        velocity.y += 1716.75f * deltaTime;//9.81f;
    }
    else
    {
        velocity.y = 490.5f;
    }

    ///Detect input--------------------------------------------------
    ///Movement
    ///Left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        velocity.x -= speed / 16.0f;
    }

    ///Right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        velocity.x += speed / 16.0f;
    }

    ///Do collision--------------------------------------------------
    CheckItemCollision(deltaTime);
    CheckWeaponCollision(deltaTime);
    //CheckPlayerCollision(deltaTime);
    CheckCollision(deltaTime);

    ///Move--------------------------------------------------
    body.move(velocity * deltaTime);

    ///Determine direction--------------------------------------------------
    if (velocity.x > 0.0f)
    {
        faceRight = true;
    }
    else if (velocity.x < 0.0f)
    {
        faceRight = false;
    }

    ///Switch states--------------------------------------------------
    if (state == 5)
    {
        ///Surprise attack
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && canAttack)
        {
            canAttack = false;
            if (faceRight)
            {
                velocity.x = 245.25f;
                state = 10;
            }
            else
            {
                velocity.x = -245.25f;
                state = 10;
            }
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            ///Run
            if (velocity.x > 49.05f || velocity.x < -49.05f)
            {
                state = 2;
            }
            ///Idle
            else if (velocity.x < 49.05f && velocity.x > -49.05f)
            {
                state = 0;
            }
        }
    }
}

///Attack state----------------------------------------------------------------------------------------------------
void Blue::AttackState(float deltaTime)
{
    ///Do physics--------------------------------------------------
    ///Do horizontal movement
    if (faceRight)
    {
        velocity.x -= 490.5f * 4.0f * deltaTime;//9.81f;
    }
    else
    {
        velocity.x += 490.5f * 4.0f * deltaTime;//9.81f;
    }

    ///Set X velocity to 0 when small enough
    if (abs(velocity.x) < 0.1f)
    {
        velocity.x = 0.0f;
    }

    ///Add to and limit gravity
    if (velocity.y < 490.5f)
    {
        velocity.y += 1716.75f * deltaTime;//9.81f;
    }
    else
    {
        velocity.y = 490.5f;
    }

    ///Do collision--------------------------------------------------
    CheckItemCollision(deltaTime);
    CheckWeaponCollision(deltaTime);
    CheckPlayerCollision(deltaTime);
    CheckCollision(deltaTime);

    ///Move--------------------------------------------------
    body.move(velocity * deltaTime);

    ///Switch states--------------------------------------------------
    if (state == 6)
    {
        if (faceRight)
        {
            ///Idle
            if (velocity.x <= -245.25f || body.getPosition().x < attackPosition || stateTimer > 0.5f)
            {
                velocity.x = 0.0f;
                stateTimer = 0.0f;
                state = 0;
            }
            else
            {
                stateTimer += deltaTime;
            }
        }
        else
        {
            ///Idle
            if (velocity.x >= 245.25f || body.getPosition().x > attackPosition || stateTimer > 0.5f)
            {
                velocity.x = 0.0f;
                stateTimer = 0.0f;
                state = 0;
            }
            else
            {
                stateTimer += deltaTime;
            }
        }
    }
}

///Charge state----------------------------------------------------------------------------------------------------
void Blue::ChargeState(float deltaTime)
{
    ///Do physics--------------------------------------------------
    ///Decrease horizontal movement speed
    velocity.x *= 0.98f;

    ///Set X velocity to 0 when small enough
    if (abs(velocity.x) < 0.1f)
    {
        velocity.x = 0.0f;
    }

    ///Add to and limit gravity
    if (velocity.y < 490.5f)
    {
        velocity.y += 1716.75f * deltaTime;//9.81f;
    }
    else
    {
        velocity.y = 490.5f;
    }

    ///Detect input--------------------------------------------------
    ///Aim
    ///Both up and down pressed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        aim = 0;
    }
    ///Up
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        aim = -1;
    }
    ///Down
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        aim = 1;
    }
    ///Nothing is pressed
    else
    {
        aim = 0;
    }

    ///Do collision--------------------------------------------------
    CheckItemCollision(deltaTime);
    CheckWeaponCollision(deltaTime);
    CheckPlayerCollision(deltaTime);
    CheckCollision(deltaTime);

    ///Move--------------------------------------------------
    body.move(velocity * deltaTime);

    ///Switch states--------------------------------------------------
    if (state == 7)
    {
        ///Throw
        if (stateTimer > 0.3f)
        {
            ///Create item
            if (faceRight)
            {
                items.push_back(Item(GetPosition(), sf::Vector2f(490.5f, (aim * 490.5f) - 122.625f), weapon, 0));
            }
            else
            {
                items.push_back(Item(GetPosition(), sf::Vector2f(-490.5f, (aim * 490.5f) - 122.625f), weapon, 0));
            }
            stateTimer = 0.0f;
            state = 11;
            weapon = 0;
            canAttack = false;
        }
        else if (stateTimer > 0.2f)
        {
            ///Throw
            if (weapon != 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            {
                stateTimer += deltaTime;
            }
            ///Smash
            else if (velocity.y != 0.0f)
            {
                stateTimer = 0.0f;
                velocity.y = 245.25f;
                state = 9;
                canAttack = false;
            }
            ///Fleche
            else
            {
                stateTimer = 0.0f;
                if (faceRight)
                {
                    velocity.x = 490.5f;
                }
                else
                {
                    velocity.x = -490.5f;
                }
                state = 8;
                canAttack = false;
            }
        }
        else
        {
            stateTimer += deltaTime;
        }
    }
}

///Fleche state----------------------------------------------------------------------------------------------------
void Blue::FlecheState(float deltaTime)
{
    ///Do physics--------------------------------------------------
    ///Do horizontal movement
    if (faceRight)
    {
        velocity.x -= 981.0f * deltaTime;
    }
    else
    {
        velocity.x += 981.0f * deltaTime;
    }

    ///Set X velocity to 0 when small enough
    if (abs(velocity.x) < 0.1f)
    {
        velocity.x = 0.0f;
    }

    ///Add to and limit gravity
    if (velocity.y < 490.5f)
    {
        velocity.y += 1716.75f * deltaTime;//9.81f;
    }
    else
    {
        velocity.y = 490.5f;
    }

    ///Do collision--------------------------------------------------
    CheckItemCollision(deltaTime);
    CheckWeaponCollision(deltaTime);
    CheckPlayerCollision(deltaTime);
    CheckCollision(deltaTime);

    ///Move--------------------------------------------------
    body.move(velocity * deltaTime);

    ///Switch states--------------------------------------------------
    if (state == 8)
    {
        if (faceRight)
        {
            ///Idle
            if (velocity.x <= 49.05f || stateTimer > 0.6f)
            {
                velocity.x = 49.05f;
                stateTimer = 0.0f;
                state = 0;
            }
            else
            {
                stateTimer += deltaTime;
            }
        }
        else
        {
            ///Idle
            if (velocity.x >= -49.05f || stateTimer > 0.6f)
            {
                velocity.x = -49.05f;
                stateTimer = 0.0f;
                state = 0;
            }
            else
            {
                stateTimer += deltaTime;
            }
        }
    }
}

///Smash state----------------------------------------------------------------------------------------------------
void Blue::SmashState(float deltaTime)
{
    ///Do physics--------------------------------------------------
    ///Decrease horizontal movement speed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || velocity.y != 0.0f)
    {
        velocity.x *= 0.998f;
    }
    else
    {
        velocity.x *= 0.9f;
    }

    ///Restrict maximum horizontal movement speed
    if (velocity.x > 122.625f)
    {
        velocity.x = 122.625f;
    }
    if (velocity.x < -122.625f)
    {
        velocity.x = -122.625f;
    }

    ///Set X velocity to 0 when small enough
    if (abs(velocity.x) < 0.1f)
    {
        velocity.x = 0.0f;
    }

    ///Add to and limit gravity
    if (velocity.y < 490.5f)
    {
        velocity.y += 1716.75f * deltaTime;//9.81f;
    }
    else
    {
        velocity.y = 490.5f;
    }

    ///Set aim
    aim = -1;

    ///Do collision--------------------------------------------------
    CheckItemCollision(deltaTime);
    CheckWeaponCollision(deltaTime);
    CheckPlayerCollision(deltaTime);
    CheckCollision(deltaTime);

    ///Move--------------------------------------------------
    body.move(velocity * deltaTime);

    ///Switch states--------------------------------------------------
    if (state == 9)
    {
        if (DistanceToBlock(0) == 0.0f)
        {
            ///Release particles
            for (int i = 0; i < (rand() % 4) + 12; i++)
            {
                int startSize = (rand() % 4) + 4;
                particles.push_back(Particle(sf::Vector2f(body.getPosition().x + float((rand() % int(body.getSize().x))) - (body.getSize().x / 2.0f), body.getPosition().y + (body.getSize().y / 2.0f) - 16.0f), sf::Vector2f(startSize, startSize), 0, rand() % 4, bool(rand() % 2)));
            }

            ///Run
            if (velocity.x > 49.05f || velocity.x < -49.05f)
            {
                state = 2;
            }
            ///Idle
            else if (velocity.x < 49.05f && velocity.x > -49.05f)
            {
                state = 0;
            }
        }
    }
}

///Surprise attack state----------------------------------------------------------------------------------------------------
void Blue::SurpriseState(float deltaTime)
{
    ///Do physics--------------------------------------------------
    ///Do horizontal movement
    if (faceRight)
    {
        velocity.x -= 981.0f * deltaTime;
    }
    else
    {
        velocity.x += 981.0f * deltaTime;
    }

    ///Set X velocity to 0 when small enough
    if (abs(velocity.x) < 0.1f)
    {
        velocity.x = 0.0f;
    }

    ///Add to and limit gravity
    if (velocity.y < 490.5f)
    {
        velocity.y += 1716.75f * deltaTime;//9.81f;
    }
    else
    {
        velocity.y = 490.5f;
    }

    ///Do collision--------------------------------------------------
    CheckItemCollision(deltaTime);
    CheckWeaponCollision(deltaTime);
    CheckPlayerCollision(deltaTime);
    CheckCollision(deltaTime);

    ///Move--------------------------------------------------
    body.move(velocity * deltaTime);

    ///Switch states--------------------------------------------------
    if (state == 10)
    {
        if (faceRight)
        {
            ///Idle
            if (velocity.x <= 49.05f || stateTimer > 0.6f)
            {
                velocity.x = 49.05f;
                stateTimer = 0.0f;
                state = 0;
            }
            else
            {
                stateTimer += deltaTime;
            }
        }
        else
        {
            ///Idle
            if (velocity.x >= -49.05f || stateTimer > 0.6f)
            {
                velocity.x = -49.05f;
                stateTimer = 0.0f;
                state = 0;
            }
            else
            {
                stateTimer += deltaTime;
            }
        }
    }
}

///Throw state----------------------------------------------------------------------------------------------------
void Blue::ThrowState(float deltaTime)
{
    ///Do physics--------------------------------------------------
    ///Decrease horizontal movement speed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || velocity.y != 0.0f)
    {
        velocity.x *= 0.998f;
    }
    else
    {
        velocity.x *= 0.9f;
    }

    ///Restrict maximum horizontal movement speed
    if (velocity.x > 122.625f)
    {
        velocity.x = 122.625f;
    }
    if (velocity.x < -122.625f)
    {
        velocity.x = -122.625f;
    }

    ///Set X velocity to 0 when small enough
    if (abs(velocity.x) < 0.1f)
    {
        velocity.x = 0.0f;
    }

    ///Add to and limit gravity
    if (velocity.y < 490.5f)
    {
        velocity.y += 1716.75f * deltaTime;//9.81f;
    }
    else
    {
        velocity.y = 490.5f;
    }

    ///Do collision--------------------------------------------------
    CheckItemCollision(deltaTime);
    CheckWeaponCollision(deltaTime);
    CheckPlayerCollision(deltaTime);
    CheckCollision(deltaTime);

    ///Move--------------------------------------------------
    body.move(velocity * deltaTime);

    ///Switch states--------------------------------------------------
    if (state == 11)
    {
        ///Do timer
        if (stateTimer > 0.2f)
        {
            stateTimer = 0.0f;
            weapon = 0;
            ///Run
            if (velocity.x > 49.05f || velocity.x < -49.05f)
            {
                state = 2;
            }
            ///Idle
            else if (velocity.x < 49.05f && velocity.x > -49.05f)
            {
                state = 0;
            }
        }
        else
        {
            stateTimer += deltaTime;
        }
    }
}

///Stunned state----------------------------------------------------------------------------------------------------
void Blue::StunnedState(float deltaTime)
{
    ///Do physics--------------------------------------------------
    ///Decrease horizontal movement speed
    velocity.x *= 0.98f;

    ///Restrict maximum horizontal movement speed
    if (velocity.x > 122.625f)
    {
        velocity.x = 122.625f;
    }
    if (velocity.x < -122.625f)
    {
        velocity.x = -122.625f;
    }

    ///Set X velocity to 0 when small enough
    if (abs(velocity.x) < 0.1f)
    {
        velocity.x = 0.0f;
    }

    ///Add to and limit gravity
    if (velocity.y < 490.5f)
    {
        velocity.y += 1716.75f * deltaTime;//9.81f;
    }
    else
    {
        velocity.y = 490.5f;
    }

    ///Detect input--------------------------------------------------
    ///Movement
    ///Left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        velocity.x -= speed;
    }

    ///Right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        velocity.x += speed;
    }

    ///Do collision--------------------------------------------------
    CheckItemCollision(deltaTime);
    CheckWeaponCollision(deltaTime);
    CheckPlayerCollision(deltaTime);
    CheckCollision(deltaTime);

    ///Move--------------------------------------------------
    body.move(velocity * deltaTime);

    ///Switch states--------------------------------------------------
    if (state == 12)
    {
        ///Do timer
        if (stateTimer > 0.2f)
        {
            stateTimer = 0.0f;
            state = 0;
        }
        else
        {
            stateTimer += deltaTime;
        }
    }
}

///Hit state----------------------------------------------------------------------------------------------------
void Blue::HitState(float deltaTime)
{
    ///Do physics--------------------------------------------------
    ///Decrease horizontal movement speed
    velocity.x *= 0.98f;

    ///Restrict maximum horizontal movement speed
    if (velocity.x > 122.625f)
    {
        velocity.x = 122.625f;
    }
    if (velocity.x < -122.625f)
    {
        velocity.x = -122.625f;
    }

    ///Set X velocity to 0 when small enough
    if (abs(velocity.x) < 0.1f)
    {
        velocity.x = 0.0f;
    }

    ///Add to and limit gravity
    if (velocity.y < 490.5f)
    {
        velocity.y += 1716.75f * deltaTime;//9.81f;
    }
    else
    {
        velocity.y = 490.5f;
    }

    ///Do collision--------------------------------------------------
    CheckItemCollision(deltaTime);
    CheckWeaponCollision(deltaTime);
    CheckPlayerCollision(deltaTime);
    CheckCollision(deltaTime);

    ///Move--------------------------------------------------
    body.move(velocity * deltaTime);

    ///Switch states--------------------------------------------------
    if (state == 13)
    {
        ///Do timer
        if (stateTimer > 0.2f)
        {
            stateTimer = 0.0f;
            state = 0;
        }
        else
        {
            stateTimer += deltaTime;
        }
    }
}

///Wall state----------------------------------------------------------------------------------------------------
void Blue::WallState(float deltaTime)
{
    ///Do physics--------------------------------------------------
    ///Set x velocity to 0
    velocity.x = 0.0f;

    ///Decrease y velocity
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        velocity.y *= 0.98f;
    }
    else
    {
        velocity.y *= 0.9f;
    }

    ///Detect input--------------------------------------------------
    ///Movement
    ///Shift
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if (canJump)
            {
                velocity.y = -sqrt(981.0f * jumpHeight / 4.0f);

                if (faceRight)
                {
                    velocity.x = 49.05f;
                }
                else
                {
                    velocity.x = -49.05f;
                }
            }

            ///Release particles
            for (int i = 0; i < (rand() % 4) + 12; i++)
            {
                int startSize = (rand() % 4) + 4;
                if (faceRight)
                {
                    particles.push_back(Particle(sf::Vector2f(body.getPosition().x - (body.getSize().x / 2.0f), body.getPosition().y + float((rand() % int(body.getSize().y / 2.0f))) - (body.getSize().y / 4.0f) - 16.0f), sf::Vector2f(startSize, startSize), 0, rand() % 4, bool(rand() % 2)));
                }
                else
                {
                    particles.push_back(Particle(sf::Vector2f(body.getPosition().x + (body.getSize().x / 2.0f), body.getPosition().y + float((rand() % int(body.getSize().y / 2.0f))) - (body.getSize().y / 4.0f) - 16.0f), sf::Vector2f(startSize, startSize), 0, rand() % 4, bool(rand() % 2)));
                }
            }

            canJump = false;
        }
    }

    ///Down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        velocity.y += 981.0f * deltaTime;
    }

    ///Ctrl
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && canAttack)
    {
        if (faceRight)
        {
            velocity.x = 490.5f;
        }
        else
        {
            velocity.x = -490.5f;
        }
    }

    ///Set aim--------------------------------------------------
    aim = 0;

    ///Do collision--------------------------------------------------
    CheckItemCollision(deltaTime);
    CheckWeaponCollision(deltaTime);
    CheckPlayerCollision(deltaTime);
    CheckCollision(deltaTime);

    ///Move--------------------------------------------------
    body.move(velocity * deltaTime);

    ///Release particles--------------------------------------------------
    if (velocity.y >= 1.0f)
    {
        if (rand() % 10 < abs(velocity.y) / 100.0f)
        {
            int startSize = (rand() % 4) + 4;
            if (faceRight)
            {
                particles.push_back(Particle(sf::Vector2f(body.getPosition().x - 14.0f + float((rand() % 4) - 2), body.getPosition().y - 16.0f), sf::Vector2f(startSize, startSize), 0, rand() % 4, bool(rand() % 2)));
            }
            else
            {
                particles.push_back(Particle(sf::Vector2f(body.getPosition().x + 14.0f + float((rand() % 4) - 2), body.getPosition().y - 16.0f), sf::Vector2f(startSize, startSize), 0, rand() % 4, bool(rand() % 2)));
            }
        }
    }

    ///Switch states--------------------------------------------------
    if (state == 14)
    {
        ///Fleche
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && canAttack)
        {
            if (faceRight)
            {
                velocity.x = 490.5f;
            }
            else
            {
                velocity.x = -490.5f;
            }
            state = 8;
            canAttack = false;
        }
        ///Jump
        else if (velocity.y < 0.0f)
        {
            state = 3;
        }
        else if (faceRight && DistanceToBlock(2) >= 1.0f)
        {
            state = 3;
        }
        else if (!faceRight && DistanceToBlock(3) >= 1.0f)
        {
            state = 3;
        }
        ///Idle
        else if (DistanceToBlock(0) <= 1.0f)
        {
            state = 0;
        }
    }
}

///Update----------------------------------------------------------------------------------------------------
void Blue::Update(float deltaTime)
{
    ///Perform state machine--------------------------------------------------
    stateBefore = state;

    switch(state)
    {
        case -1:
            DeadState(deltaTime);
            break;
        case 0:
            IdleState(deltaTime);
            break;
        case 1:
            WalkState(deltaTime);
            break;
        case 2:
            RunState(deltaTime);
            break;
        case 3:
            JumpState(deltaTime);
            break;
        case 4:
            CrouchState(deltaTime);
            break;
        case 5:
            SlideState(deltaTime);
            break;
        case 6:
            AttackState(deltaTime);
            break;
        case 7:
            ChargeState(deltaTime);
            break;
        case 8:
            FlecheState(deltaTime);
            break;
        case 9:
            SmashState(deltaTime);
            break;
        case 10:
            SurpriseState(deltaTime);
            break;
        case 11:
            ThrowState(deltaTime);
            break;
        case 12:
            StunnedState(deltaTime);
            break;
        case 13:
            HitState(deltaTime);
            break;
        case 14:
            WallState(deltaTime);
            break;
    }

    ///Change variables--------------------------------------------------
    ///Check canJump
    if (DistanceToBlock(0) == 0.0f || state == 14)
    {
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            canJump = true;
        }
    }
    else
    {
        canJump = false;
    }

    ///Check canAttack
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    {
        canAttack = true;
    }

    ///Do grace timer
    if (graceTimer > 0.0f)
    {
        graceTimer -= deltaTime;
    }
    else
    {
        graceTimer = 0.0f;
    }

    ///Check boundaries--------------------------------------------------
    ///Check if player has fallen out of level
    if (body.getPosition().y > 382.0f && health > 0)
    {
        Hurt(9999);
    }

    ///Check if player is off-screen
    ///Focus on other player
    ///Check state
    if (state != -1)
    {
        if (focus == 1)
        {
            ///Check position
            if (body.getPosition().x >= viewPosition.x + (viewSize.x / 2.0f) + 64.0f)
            {
                Warp();
            }
        }
    }

    ///Update animation--------------------------------------------------
    sprite.setTexture(&texBlue);
    animation.SetTexture(&texBlue);
    UpdateAnimation(deltaTime);
}

///Hurt----------------------------------------------------------------------------------------------------
void Blue::Hurt(int damage)
{
    if (graceTimer <= 0.0f)
    {
        health -= damage;
        graceTimer = 0.5f;
        stateTimer = 0.0f;
        state = 13;
    }

    if (health <= 0)
    {
        health = 0;
        deathTimer = 0.0f;

        ///Hit from right, spawn a corpse flying to the left
        if (red.GetPosition().x > body.getPosition().x)
        {
            corpses.push_back(Corpse(body.getPosition(), sf::Vector2f((rand() % 123) - 245, (rand() % 123) - 368), 0));
        }
        ///Hit from left, spawn a corpse flying to the right
        else
        {
            corpses.push_back(Corpse(body.getPosition(), sf::Vector2f((rand() % 123) + 122, (rand() % 123) - 368), 0));
        }

        ///Spawn item
        if (weapon != 0)
        {
            ///Other player is to the right, send weapon flying to the left
            if (red.GetPosition().x > body.getPosition().x)
            {
                items.push_back(Item(body.getPosition(), sf::Vector2f((rand() % 123) - 245, (rand() % 123) - 368), weapon, 1));
            }
            ///Other player is to the left, send weapon flying to the right
            else if (red.GetPosition().x < body.getPosition().x)
            {
                items.push_back(Item(body.getPosition(), sf::Vector2f((rand() % 123) + 122, (rand() % 123) - 368), weapon, 1));
            }
        }

        ///Change focus
        if (red.state != -1)
        {
            focus = 1;
        }
        else
        {
            focus = -1;
        }

        state = -1;
    }
}

///Warp----------------------------------------------------------------------------------------------------
void Blue::Warp()
{
    ///Determine the size of current map
    sf::Vector2f mapSize;
    if (area == 0)
    {
        mapSize.x = 33.0f * 32.0f;
    }
    else
    {
        mapSize.x = 32.0f * 32.0f;
    }
    mapSize.y = 12.0f * 32.0f;

    ///Determine room center
    float roomCenter;
    if (area == 0)
    {
        roomCenter = 0.0f;
    }
    else
    {
        if (area > 0)
        {
            roomCenter = (area * 32.0f * 32.0f) + 16.0f;
        }
        else if (area < 0)
        {
            roomCenter = (area * 32.0f * 32.0f) - 16.0f;
        }
    }

    ///Set position
    ///Normal
    if (red.GetPosition().x > roomCenter - (mapSize.x / 2.0f) + (viewSize.x / 2.0f))
    {
        body.setPosition(FindSpawn(sf::Vector2f(red.GetPosition().x - 256.0f, red.GetPosition().y), 0));
        velocity.x = 1.0f;
    }
    ///Not enough room in front of opponent, set spawn behind
    else
    {
        body.setPosition(FindSpawn(sf::Vector2f(red.GetPosition().x + 256.0f, red.GetPosition().y), 1));
        velocity.x = -1.0f;
    }

    ///Release particles
    for (int i = 0; i < (rand() % 4) + 12; i++)
    {
        int startSize = (rand() % 4) + 4;
        particles.push_back(Particle(sf::Vector2f(body.getPosition().x + float((rand() % int(body.getSize().x))) - (body.getSize().x / 2.0f), body.getPosition().y + float((rand() % int(body.getSize().y))) - (body.getSize().y / 2.0f) - 16.0f), sf::Vector2f(startSize, startSize), 0, rand() % 2, bool(rand() % 2)));
    }
}
