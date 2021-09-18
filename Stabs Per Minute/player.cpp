#include "header.h"
#include "player.h"

Player::Player(sf::Vector2f position) :
    animation(&texBlue, sf::Vector2u(8, 8), 0.0f)
{
    body.setSize(sf::Vector2f(16.0f, 32.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(position);
    sprite.setSize(sf::Vector2f(32.0f, 32.0f));
    sprite.setOrigin(sprite.getSize() / 2.0f);
    sprite.setPosition(body.getPosition());
    sprite.setTexture(&texBlue);
    this->row = 0;
    this->columnBegin = 0;
    this->columnEnd = 0;
    this->switchTime = 0.0f;
    this->faceRight = true;
    this->velocity.x = 0.0f;
    this->velocity.y = 0.0f;
    this->speed = 2.0f;
    this->jumpHeight = 981.0f * 0.75;
    this->canJump = true;
    this->state = 0;
    this->stateBefore = 0;
    this->weapon = 1;
    this->aim = 0;
    this->canAttack = true;
    this->attackPosition = body.getPosition().x;
    this->stateTimer = 0.0f;
    this->health = 100;
    this->graceTimer = 0.0f;
    this->deathTimer = 0.0f;
}

Player::~Player()
{
    //dtor
}

///Get weapon collision----------------------------------------------------------------------------------------------------
bool Player::GetWeaponCollision()
{
    sf::Vector2f blueWeaponPos;
    if (blueWeapon.faceRight)
    {
        blueWeaponPos = sf::Vector2f(blueWeapon.GetPosition().x + (blueWeapon.GetHalfSize().x), blueWeapon.GetPosition().y);
    }
    else
    {
        blueWeaponPos = sf::Vector2f(blueWeapon.GetPosition().x - (blueWeapon.GetHalfSize().x), blueWeapon.GetPosition().y);
    }
    sf::Vector2f blueWeaponHalfSize = blueWeapon.GetHalfSize();
    sf::Vector2f redWeaponPos;
    if (redWeapon.faceRight)
    {
        redWeaponPos = sf::Vector2f(redWeapon.GetPosition().x + (redWeapon.GetHalfSize().x), redWeapon.GetPosition().y);
    }
    else
    {
        redWeaponPos = sf::Vector2f(redWeapon.GetPosition().x - (redWeapon.GetHalfSize().x), redWeapon.GetPosition().y);
    }
    sf::Vector2f redWeaponHalfSize = redWeapon.GetHalfSize();

    float deltaX = redWeaponPos.x - blueWeaponPos.x;
    float deltaY = redWeaponPos.y - blueWeaponPos.y;

    float intersectX = abs(deltaX) - (redWeaponHalfSize.x + blueWeaponHalfSize.x);
    float intersectY = abs(deltaY) - (redWeaponHalfSize.y + blueWeaponHalfSize.y);

    if (intersectX < 0.0f && intersectY < 0.0f)
    {
        return true;
    }
    return false;
}

///Distance to block----------------------------------------------------------------------------------------------------
float Player::DistanceToBlock(int direction)
{
    float distance = 999999.0f;
    sf::Vector2f blockPos;
    int location;

    float bodyHeight = 16.0f;

    ///Below--------------------------------------------------
    if (direction == 0)
    {
        for (int i = 0; i < blocks.size(); i++)
        {
            blockPos = blocks[i].GetPosition();
            bool isBlock = false;

            if (blockPos.y - 16 >= body.getPosition().y + bodyHeight)
            {
                ///Left
                if (body.getPosition().x - 12 < blockPos.x + 16 && body.getPosition().x - 12 > blockPos.x - 16)
                {
                    isBlock = true;
                }
                ///Right
                if (body.getPosition().x + 12 > blockPos.x - 16 && body.getPosition().x + 12 < blockPos.x + 16)
                {
                    isBlock = true;
                }

                if (isBlock)
                {
                    if (blockPos.y - 16 - (body.getPosition().y + bodyHeight) < distance)
                    {
                        distance = blockPos.y - 16 - (body.getPosition().y + bodyHeight);
                        location = i;
                    }
                }
            }
        }
    }
    ///Above--------------------------------------------------
    else if (direction == 1)
    {
        for (int i = 0; i < blocks.size(); i++)
        {
            blockPos = blocks[i].GetPosition();
            bool isBlock = false;

            if (blockPos.y + 16 <= body.getPosition().y - bodyHeight)
            {
                ///Left
                if (body.getPosition().x - 12 < blockPos.x + 16 && body.getPosition().x - 12 > blockPos.x - 16)
                {
                    isBlock = true;
                }
                ///Right
                if (body.getPosition().x + 12 > blockPos.x - 16 && body.getPosition().x + 12 < blockPos.x + 16)
                {
                    isBlock = true;
                }

                if (isBlock)
                {
                    if ((body.getPosition().y - bodyHeight) - blockPos.y + 16 < distance)
                    {
                        distance = (body.getPosition().y - bodyHeight) - blockPos.y + 16;
                        location = i;
                    }
                }
            }
        }
    }
    ///Left--------------------------------------------------
    else if (direction == 2)
    {
        for (int i = 0; i < blocks.size(); i++)
        {
            blockPos = blocks[i].GetPosition();
            if (blockPos.x + 16 <= body.getPosition().x - 12 && blockPos.y - 16 < body.getPosition().y + bodyHeight && blockPos.y + 16 > body.getPosition().y - bodyHeight)
            {
                if ((body.getPosition().x - 12) - (blockPos.x + 16) < distance)
                {
                    distance = (body.getPosition().x - 12) - (blockPos.x + 16);
                    location = i;
                }
            }
        }
    }
    ///Right--------------------------------------------------
    else if (direction == 3)
    {
        for (int i = 0; i < blocks.size(); i++)
        {
            blockPos = blocks[i].GetPosition();
            if (blockPos.x - 16 >= body.getPosition().x + 12 && blockPos.y - 16 < body.getPosition().y + bodyHeight && blockPos.y + 16 > body.getPosition().y - bodyHeight)
            {
                if ((blockPos.x - 16) - (body.getPosition().x + 12) < distance)
                {
                    distance = (blockPos.x - 16) - (body.getPosition().x + 12);
                    location = i;
                }
            }
        }
    }

    ///Return distance--------------------------------------------------
    if (distance == 999999.0f)
    {
        return 999999.0f;
    }
    else
    {
        ///Below
        if (direction == 0)
        {
            return blocks[location].GetPosition().y - 16 - (body.getPosition().y + bodyHeight);
        }
        ///Above
        if (direction == 1)
        {
            return (body.getPosition().y - bodyHeight) - (blocks[location].GetPosition().y + 16);
        }
        ///Left
        if (direction == 2)
        {
            return (body.getPosition().x - 12) - (blocks[location].GetPosition().x + 16);
        }
        ///Right
        else if (direction == 3)
        {
            return (blocks[location].GetPosition().x - 16) - (body.getPosition().x + 12);
        }
    }
}

///Check collision----------------------------------------------------------------------------------------------------
void Player::CheckCollision(float deltaTime)
{
    ///Block collision--------------------------------------------------
    ///Horizontal collision
    ///Left
    if (velocity.x < 0.0f)
    {
        if (DistanceToBlock(2) < abs(velocity.x) * deltaTime)
        {
            velocity.x = 0.0f;
            body.move(-DistanceToBlock(2), 0.0f);
        }
    }
    ///Right
    else if (velocity.x > 0.0f)
    {
        if (DistanceToBlock(3) < velocity.x * deltaTime)
        {
            velocity.x = 0.0f;
            body.move(DistanceToBlock(3), 0.0f);
        }
    }

    ///Vertical collision
    ///Ground
    if (DistanceToBlock(0) < velocity.y * deltaTime)
    {
        velocity.y = 0.0f;
        body.move(0.0f, DistanceToBlock(0));
    }

    ///Ceiling
    if (DistanceToBlock(1) != 999999.0f)
    {
        if (-DistanceToBlock(1) > velocity.y * deltaTime)
        {
            ///Stop player from moving upwards
            velocity.y = 0.0f;
            body.move(0.0f, -DistanceToBlock(1));
        }
    }

    ///Set X velocity to 0 after colliding with wall
    if (DistanceToBlock(2) <= 1.0f && velocity.x < 0.0f)
    {
        velocity.x = 0.0f;
    }

    if (DistanceToBlock(3) <= 1.0f && velocity.x > 0.0f)
    {
        velocity.x = 0.0f;
    }

    ///Backup engines--------------------------------------------------
    for (int i = 0; i < blocks.size(); i++)
    {
        sf::Vector2f otherPos = blocks[i].GetPosition();
        sf::Vector2f otherHalfSize = blocks[i].GetHalfSize();
        sf::Vector2f thisPos = GetPosition();
        sf::Vector2f thisHalfSize = GetHalfSize();

        float deltaX = otherPos.x - thisPos.x;
        float deltaY = otherPos.y - thisPos.y;

        float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
        float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

        if (intersectX < 0.0f && intersectY < 0.0f)
        {
            if (intersectX > intersectY)
            {
                ///Left
                if (deltaX > 0.0f)
                {
                    body.move(intersectX, 0.0f);
                    velocity.x = 0.0f;
                }
                ///Right
                else if (deltaX < 0.0f)
                {
                    body.move(-intersectX, 0.0f);
                    velocity.x = 0.0f;
                }
            }
            else
            {
                ///Top
                if (deltaY > 0.0f)
                {
                    body.move(0.0f, intersectY);
                    velocity.y = 0.0f;
                }
                ///Bottom
                else if (deltaY < 0.0f)
                {
                    body.move(0.0f, -intersectY);
                    velocity.y = 0.0f;
                }
            }
        }
    }
}

///Find spawn----------------------------------------------------------------------------------------------------
sf::Vector2f Player::FindSpawn(sf::Vector2f position, int searchDirection)
{
    ///Check if there are any possible positions
    bool isPossible = false;
    for (int i = 0; i < blocks.size(); i++)
    {
        if (searchDirection == 0 && blocks[i].GetPosition().x < position.x)
        {
            isPossible = true;
        }
        else if (searchDirection == 1 && blocks[i].GetPosition().x > position.x)
        {
            isPossible = true;
        }
    }

    ///Blocks exist in specified direction
    if (isPossible)
    {
        ///Check for blank space
        bool isViable = true;
        for (int i = 0; i < blocks.size(); i++)
        {
            sf::Vector2f otherPos = blocks[i].GetPosition();
            sf::Vector2f otherHalfSize = blocks[i].GetHalfSize();
            sf::Vector2f thisHalfSize = GetHalfSize();

            float deltaX = otherPos.x - position.x;
            float deltaY = otherPos.y - position.y;

            float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
            float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

            if (intersectX < 0.0f && intersectY < 0.0f)
            {
                isViable = false;
            }
        }
        for (int i = 0; i < spikes.size(); i++)
        {
            sf::Vector2f otherPos = spikes[i].GetPosition();
            sf::Vector2f otherHalfSize = spikes[i].GetHalfSize();
            sf::Vector2f thisHalfSize = GetHalfSize();

            float deltaX = otherPos.x - position.x;
            float deltaY = otherPos.y - position.y;

            float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
            float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

            if (intersectX < 0.0f && intersectY < 0.0f)
            {
                isViable = false;
            }
        }

        ///Check for block underneath
        bool isBlock = false;
        for (int i = 0; i < blocks.size(); i++)
        {
            sf::Vector2f otherPos = blocks[i].GetPosition();
            sf::Vector2f otherHalfSize = blocks[i].GetHalfSize();
            sf::Vector2f thisHalfSize = GetHalfSize();

            float deltaX = otherPos.x - position.x;
            float deltaY = otherPos.y - (position.y + 32.0f);

            float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
            float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

            if (intersectX < 0.0f && intersectY < 0.0f)
            {
                isBlock = true;
                break;
            }
        }

        if (isViable && isBlock)
        {
            return position;
        }
        else
        {
            ///At bottom, move horizontally
            if (position.y > 11.0f * 32.0f)
            {
                if (searchDirection == 0)
                {
                    return FindSpawn(sf::Vector2f(position.x - 32.0f, 32.0f), searchDirection);
                }
                else if (searchDirection == 1)
                {
                    return FindSpawn(sf::Vector2f(position.x + 32.0f, 32.0f), searchDirection);
                }
            }
            ///Not reached bottom, move vertically
            else
            {
                return FindSpawn(sf::Vector2f(position.x, position.y + 32.0f), searchDirection);
            }
        }
    }
    ///No blocks in specified direction
    else
    {
        if (searchDirection == 0)
        {
            return FindSpawn(sf::Vector2f(position.x + 512.0f, 32.0f), 1);
        }
        else if (searchDirection == 1)
        {
            return FindSpawn(sf::Vector2f(position.x - 512.0f, 32.0f), 0);
        }
    }
}

///Update animation----------------------------------------------------------------------------------------------------
void Player::UpdateAnimation(float deltaTime)
{
    ///Idle--------------------------------------------------
    if (state == 0)
    {
        row = 0;
        ///Fists
        if (weapon == 0)
        {
            columnBegin = 0;
            columnEnd = 1;
        }
        ///Sword
        else if (weapon == 1)
        {
            columnBegin = 2;
            columnEnd = 3;
        }
        switchTime = 1.0f / 2.0f;
    }
    ///Walk--------------------------------------------------
    else if (state == 1)
    {
        row = 1;
        ///Fists
        if (weapon == 0)
        {
            columnBegin = 0;
            columnEnd = 1;
        }
        ///Sword
        else if (weapon == 1)
        {
            columnBegin = 2;
            columnEnd = 3;
        }
        switchTime = 1.0f / 4.0f;
    }
    ///Run--------------------------------------------------
    else if (state == 2)
    {
        row = 1;
        columnBegin = 4;
        columnEnd = 6;
        switchTime = 1.0f / 8.0f;
    }
    ///Jump--------------------------------------------------
    else if (state == 3)
    {
        row = 2;
        ///Going upwards
        if (velocity.y < 0.0f)
        {
            columnBegin = 0;
            columnEnd = 0;
        }
        ///Coming back down
        else if (velocity.y > 0.0f)
        {
            columnBegin = 1;
            columnEnd = 1;
        }
        switchTime = 0.0f;
    }
    ///Crouch--------------------------------------------------
    else if (state == 4)
    {
        row = 2;
        ///Stopped
        if (velocity.x == 0.0f)
        {
            columnBegin = 2;
            columnEnd = 2;
            switchTime = 0.0f;
        }
        ///Moving
        else if (velocity.x < 981.0f / 8.0f && velocity.x > -(981.0f / 8.0f))
        {
            columnBegin = 2;
            columnEnd = 3;
            switchTime = 1.0f / 4.0f;
        }
    }
    ///Slide--------------------------------------------------
    else if (state == 5)
    {
        row = 2;
        ///Stopped, or going too fast
        if (velocity.x == 0.0f || velocity.x > 981.0f / 8.0f || velocity.x < -(981.0f / 8.0f))
        {
            columnBegin = 4;
            columnEnd = 4;
            switchTime = 0.0f;
        }
        ///Going normal speed
        else if (velocity.x < 981.0f / 8.0f && velocity.x > -(981.0f / 8.0f))
        {
            columnBegin = 4;
            columnEnd = 5;
            switchTime = 1.0f / 4.0f;
        }
    }
    ///Attack--------------------------------------------------
    else if (state == 6)
    {
        row = 3;
        ///Fists
        if (weapon == 0)
        {
            if (faceRight)
            {
                if (velocity.x > 0.0f)
                {
                    columnBegin = 0;
                    columnEnd = 0;
                }
                else
                {
                    columnBegin = 1;
                    columnEnd = 1;
                }
            }
        }
        ///Sword
        else if (weapon == 1)
        {
            if (faceRight)
            {
                if (velocity.x > 0.0f)
                {
                    columnBegin = 2;
                    columnEnd = 2;
                }
                else
                {
                    columnBegin = 3;
                    columnEnd = 3;
                }
            }
            else
            {
                if (velocity.x < 0.0f)
                {
                    columnBegin = 2;
                    columnEnd = 2;
                }
                else
                {
                    columnBegin = 3;
                    columnEnd = 3;
                }
            }
        }
        switchTime = 0.0f;
    }
    ///Charge--------------------------------------------------
    else if (state == 7)
    {
        row = 4;
        columnBegin = 0;
        columnEnd = 0;
        switchTime = 0.0f;
    }
    ///Fleche--------------------------------------------------
    else if (state == 8)
    {
        row = 4;
        ///Fists
        if (weapon == 0)
        {
            columnBegin = 1;
            columnEnd = 1;
        }
        ///Sword
        else if (weapon == 1)
        {
            columnBegin = 2;
            columnEnd = 2;
        }
        switchTime = 0.0f;
    }
    ///Smash--------------------------------------------------
    else if (state == 9)
    {
        row = 4;
        ///Fists
        if (weapon == 0)
        {
            columnBegin = 1;
            columnEnd = 1;
        }
        ///Sword
        else if (weapon == 1)
        {
            columnBegin = 2;
            columnEnd = 2;
        }
        switchTime = 0.0f;
    }
    ///Surprise--------------------------------------------------
    else if (state == 10)
    {
        row = 4;
        ///Fists
        if (weapon == 0)
        {
            columnBegin = 3;
            columnEnd = 3;
        }
        ///Sword
        else if (weapon == 1)
        {
            columnBegin = 4;
            columnEnd = 4;
        }
        switchTime = 0.0f;
    }
    ///Throw--------------------------------------------------
    else if (state == 11)
    {
        row = 4;
        columnBegin = 5;
        columnEnd = 5;
        switchTime = 0.0f;
    }
    ///Stunned--------------------------------------------------
    else if (state == 12)
    {
        row = 5;
        if (velocity.y == 0.0f)
        {
            columnBegin = 0;
            columnEnd = 0;
        }
        else
        {
            columnBegin = 1;
            columnEnd = 1;
        }
        switchTime = 0.0f;
    }
    ///Hit--------------------------------------------------
    else if (state == 13)
    {
        row = 5;
        if (hitDirection == -1)
        {
            columnBegin = 2;
            columnEnd = 2;
        }
        else if (hitDirection == 0)
        {
            columnBegin = 3;
            columnEnd = 3;
        }
        else if (hitDirection == 1)
        {
            columnBegin = 4;
            columnEnd = 4;
        }
        switchTime = 0.0f;
    }
    ///Wall--------------------------------------------------
    else if (state == 14)
    {
        row = 2;
        columnBegin = 6;
        columnEnd = 6;
        switchTime = 0.0f;
    }

    ///Check for state switch--------------------------------------------------
    if (stateBefore != state)
    {
        switchTime = 0.0f;
    }
    animation.SetSwitchtime(switchTime);

    ///Set alpha--------------------------------------------------
    if (state == -1)
    {
        sprite.setFillColor(sf::Color(255, 255, 255, 0));
    }
    else if (graceTimer > 0.0f)
    {
        if ((int)(graceTimer * 10) % 2 == 0)
        {
            sprite.setFillColor(sf::Color(255, 255, 255, 128));
        }
        else
        {
            sprite.setFillColor(sf::Color(255, 255, 255, 255));
        }
    }
    else
    {
        sprite.setFillColor(sf::Color(255, 255, 255, 255));
    }

    ///Update--------------------------------------------------
    animation.Update(row, columnBegin, columnEnd, deltaTime, faceRight);
    sprite.setTextureRect(animation.uvRect);
    sprite.setPosition(body.getPosition());
}

///Draw----------------------------------------------------------------------------------------------------
void Player::Draw(sf::RenderWindow& window)
{
    sprite.move(0.0f, -16.0f);
    window.draw(sprite);
    body.setFillColor(sf::Color(255, 255, 0, 100));
    body.move(0.0f, -16.0f);
    //window.draw(body);
    body.move(0.0f, 16.0f);
}
