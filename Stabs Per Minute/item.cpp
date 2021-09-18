#include "header.h"
#include "item.h"

Item::Item(sf::Vector2f position, sf::Vector2f velocity, int type, int immunity) :
    animation(&texItems, sf::Vector2u(8, 8), 0.0f)
{
    ///Sword
    if (type == 1)
    {
        body.setSize(sf::Vector2f(32.0f, 4.0f));
    }
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(position);
    sprite.setSize(sf::Vector2f(32.0f, 32.0f));
    sprite.setOrigin(sprite.getSize() / 2.0f);
    sprite.setPosition(body.getPosition());
    sprite.setTexture(&texItems);
    this->row = 0;
    this->column = 0;
    this->faceRight = true;
    this->velocity.x = velocity.x;
    this->velocity.y = velocity.y;
    this->type = type;
    this->immunity = immunity;
}

Item::~Item()
{
    //dtor
}

///Get player collision----------------------------------------------------------------------------------------------------
int Item::GetPlayerCollision(float deltaTime)
{
    ///Blue collision
    sf::Vector2f otherPos = blue.GetPosition();
    sf::Vector2f otherHalfSize = blue.GetHalfSize();
    sf::Vector2f thisPos = GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();

    float deltaX = otherPos.x - thisPos.x;
    float deltaY = otherPos.y - thisPos.y;

    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if (intersectX < 0.0f && intersectY < 0.0f)
    {
        if (immunity == -1)
        {
            return 0;
        }
    }

    ///Red collision
    otherPos = red.GetPosition();
    otherHalfSize = red.GetHalfSize();
    thisPos = GetPosition();
    thisHalfSize = GetHalfSize();

    deltaX = otherPos.x - thisPos.x;
    deltaY = otherPos.y - thisPos.y;

    intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if (intersectX < 0.0f && intersectY < 0.0f)
    {
        if (immunity == -1)
        {
            return 1;
        }
    }

    ///No collision
    return -1;
}

///Weapon collision----------------------------------------------------------------------------------------------------
void Item::CheckWeaponCollision(float deltaTime)
{
    ///Item has velocity
    if (abs(velocity.x) > 98.1f || abs(velocity.y) > 98.1f)
    {
        ///Blue weapon collision
        sf::Vector2f otherPos;
        if (blueWeapon.faceRight)
        {
            otherPos = sf::Vector2f(blueWeapon.GetPosition().x + (blueWeapon.body.getSize().x / 2.0f), blueWeapon.GetPosition().y);
        }
        else
        {
            otherPos = sf::Vector2f(blueWeapon.GetPosition().x - (blueWeapon.body.getSize().x / 2.0f), blueWeapon.GetPosition().y);
        }
        sf::Vector2f otherHalfSize = blueWeapon.GetHalfSize();
        sf::Vector2f thisPos = GetPosition();
        sf::Vector2f thisHalfSize = GetHalfSize();

        float deltaX = otherPos.x - thisPos.x;
        float deltaY = otherPos.y - thisPos.y;

        float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
        float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

        if (intersectX < 0.0f && intersectY < 0.0f)
        {
            ///Fists
            if (blueWeapon.type == 0)
            {

            }
            ///Sword
            else if (blueWeapon.type == 1)
            {
                ///Head-on collision only
                if (faceRight && !blueWeapon.faceRight)
                {
                    velocity.x *= -0.1;
                    velocity.y *= 0.1;
                }
                else if (!faceRight && blueWeapon.faceRight)
                {
                    velocity.x *= -0.1;
                    velocity.y *= 0.1;
                }
            }
        }

        ///Red weapon collision
        if (redWeapon.faceRight)
        {
            otherPos = sf::Vector2f(redWeapon.GetPosition().x + (redWeapon.body.getSize().x / 2.0f), redWeapon.GetPosition().y);
        }
        else
        {
            otherPos = sf::Vector2f(redWeapon.GetPosition().x - (redWeapon.body.getSize().x / 2.0f), redWeapon.GetPosition().y);
        }
        otherHalfSize = redWeapon.GetHalfSize();
        thisPos = GetPosition();
        thisHalfSize = GetHalfSize();

        deltaX = otherPos.x - thisPos.x;
        deltaY = otherPos.y - thisPos.y;

        intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
        intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

        if (intersectX < 0.0f && intersectY < 0.0f)
        {
            ///Fists
            if (redWeapon.type == 0)
            {

            }
            ///Sword
            else if (redWeapon.type == 1)
            {
                ///Head-on collision only
                if (faceRight && !redWeapon.faceRight)
                {
                    velocity.x *= -0.1;
                    velocity.y *= 0.1;
                }
                else if (!faceRight && redWeapon.faceRight)
                {
                    velocity.x *= -0.1;
                    velocity.y *= 0.1;
                }
            }
        }
    }
}

///Player collision----------------------------------------------------------------------------------------------------
void Item::CheckPlayerCollision(float deltaTime)
{
    ///Item has velocity
    if (abs(velocity.x) > 98.1f || abs(velocity.y) > 98.1f)
    {
        ///Blue collision
        sf::Vector2f otherPos = blue.GetPosition();
        sf::Vector2f otherHalfSize = blue.GetHalfSize();
        sf::Vector2f thisPos = GetPosition();
        sf::Vector2f thisHalfSize = GetHalfSize();

        float deltaX = otherPos.x - thisPos.x;
        float deltaY = otherPos.y - thisPos.y;

        float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
        float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

        if (intersectX < 0.0f && intersectY < 0.0f)
        {
            if (immunity == -1)
            {
                velocity.x *= 0.98f;
                velocity.y *= 0.98f;
            }
        }
        else
        {
            ///Reset immunity
            if (immunity == 0)
            {
                immunity = -1;
            }
        }

        ///Red collision
        otherPos = red.GetPosition();
        otherHalfSize = red.GetHalfSize();
        thisPos = GetPosition();
        thisHalfSize = GetHalfSize();

        deltaX = otherPos.x - thisPos.x;
        deltaY = otherPos.y - thisPos.y;

        intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
        intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

        if (intersectX < 0.0f && intersectY < 0.0f)
        {
            if (immunity == -1)
            {
                velocity.x *= 0.98f;
            }
        }
        else
        {
            ///Reset immunity
            if (immunity == 1)
            {
                immunity = -1;
            }
        }
    }
}

///Distance to block----------------------------------------------------------------------------------------------------
float Item::DistanceToBlock(int direction)
{
    float distance = 999999.0f;
    sf::Vector2f blockPos;
    int location;

    float bodyHeight = 2.0f;

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
void Item::CheckCollision(float deltaTime)
{
    ///Block collision--------------------------------------------------
    ///Horizontal collision
    ///Left
    if (velocity.x < 0.0f)
    {
        if (DistanceToBlock(2) < abs(velocity.x) * deltaTime)
        {
            body.move(-DistanceToBlock(2), 0.0f);
            velocity.x *= -0.5f;
            immunity = -1;
        }
    }
    ///Right
    else if (velocity.x > 0.0f)
    {
        if (DistanceToBlock(3) < velocity.x * deltaTime)
        {
            body.move(DistanceToBlock(3), 0.0f);
            velocity.x *= -0.5f;
            immunity = -1;
        }
    }

    ///Vertical collision
    ///Ground
    if (DistanceToBlock(0) < velocity.y * deltaTime)
    {
        body.move(0.0f, DistanceToBlock(0));
        if (GetPlayerCollision(deltaTime) == -1)
        {
            velocity.y *= -0.5f;
        }
        else
        {
            velocity.y *= -0.1f;
        }
    }

    ///Ceiling
    if (DistanceToBlock(1) != 999999.0f)
    {
        if (-DistanceToBlock(1) > velocity.y * deltaTime)
        {
            ///Stop player from moving upwards
            body.move(0.0f, -DistanceToBlock(1));
            velocity.y *= -0.5f;
        }
    }

    ///Reverse after colliding with wall
    if (DistanceToBlock(2) <= 1.0f && velocity.x < 0.0f)
    {
        velocity.x *= -0.5f;
        immunity = -1;
    }

    if (DistanceToBlock(3) <= 1.0f && velocity.x > 0.0f)
    {
        velocity.x *= -0.5f;
        immunity = -1;
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
                    velocity.x *= -0.5f;
                    immunity = -1;
                }
                ///Right
                else if (deltaX < 0.0f)
                {
                    body.move(-intersectX, 0.0f);
                    velocity.x *= -0.5f;
                    immunity = -1;
                }
            }
            else
            {
                ///Top
                if (deltaY > 0.0f)
                {
                    body.move(0.0f, intersectY);
                    if (GetPlayerCollision(deltaTime) == -1)
                    {
                        velocity.y *= -0.5f;
                    }
                    else
                    {
                        velocity.y *= -0.1f;
                    }
                }
                ///Bottom
                else if (deltaY < 0.0f)
                {
                    body.move(0.0f, -intersectY);
                    velocity.y *= -0.5f;
                }
            }
        }
    }
}

///Update----------------------------------------------------------------------------------------------------
void Item::Update(float deltaTime)
{
    ///Do physics--------------------------------------------------
    ///Decrease horizontal movement speed
    if (DistanceToBlock(0) < 1.0f)
    {
        velocity.x *= 0.995f;
    }
    else
    {
        velocity.x *= 0.9999f;
    }

    ///Restrict maximum horizontal movement speed
    if (velocity.x > 490.5f)
    {
        velocity.x = 490.5f;
    }
    if (velocity.x < -490.5f)
    {
        velocity.x = -490.5f;
    }

    ///Set X velocity to 0 when small enough
    if (abs(velocity.x) < 0.1f)
    {
        velocity.x = 0.0f;
    }

    ///Add to and limit gravity
    if (velocity.y < 490.5f)
    {
        velocity.y += 858.375f * deltaTime;
    }
    else
    {
        velocity.y = 490.5f;
    }

    ///Do collision--------------------------------------------------
    if (immunity == -1)
    {
        CheckWeaponCollision(deltaTime);
    }
    CheckPlayerCollision(deltaTime);
    CheckCollision(deltaTime);

    ///Move--------------------------------------------------
    body.move(velocity * deltaTime);

    ///Update animation--------------------------------------------------
    sprite.setTexture(&texItems);
    animation.SetTexture(&texItems);

    ///Sword--------------------------------------------------
    if (type == 1)
    {
        row = 0;
        column = 0;
    }

    ///Determine direction--------------------------------------------------
    if (velocity.x > 0.0f)
    {
        faceRight = true;
    }
    else if (velocity.x < 0.0f)
    {
        faceRight = false;
    }

    ///Do rotation--------------------------------------------------
    if (faceRight)
    {
        sprite.setRotation(velocity.y / 10);
    }
    else
    {
        sprite.setRotation(-velocity.y / 10);
    }

    ///Apply animation--------------------------------------------------
    animation.Update(row, column, column, deltaTime, faceRight);
    sprite.setTextureRect(animation.uvRect);
    sprite.setPosition(body.getPosition());
}

///Draw----------------------------------------------------------------------------------------------------
void Item::Draw(sf::RenderWindow& window)
{
    sprite.move(0.0f, -16.0f);
    window.draw(sprite);
    body.setFillColor(sf::Color(255, 0, 0, 100));
    body.move(0.0f, -16.0f);
    //window.draw(body);
    body.move(0.0f, 16.0f);
}
