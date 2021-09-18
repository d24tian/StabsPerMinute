#include "header.h"
#include "corpse.h"

Corpse::Corpse(sf::Vector2f position, sf::Vector2f velocity, int colour) :
    animation(&texCorpseBlue, sf::Vector2u(4, 2), 0.0f)
{
    body.setSize(sf::Vector2f(16.0f, 32.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(position);
    sprite.setSize(sf::Vector2f(32.0f, 32.0f));
    sprite.setOrigin(sprite.getSize() / 2.0f);
    sprite.setPosition(body.getPosition());
    ///Blue
    if (colour == 0)
    {
        sprite.setTexture(&texCorpseBlue);
    }
    ///Red
    else
    {
        sprite.setTexture(&texCorpseRed);
    }
    this->colour = colour;
    this->row = 0;
    this->column = 0;
    ///Determine direction
    if (velocity.x > 0.0f)
    {
        this->faceRight = true;
    }
    else if (velocity.x < 0.0f)
    {
        this->faceRight = false;
    }
    this->velocity.x = velocity.x;
    this->velocity.y = velocity.y;
    this->state = 0;
}

Corpse::~Corpse()
{
    //dtor
}

///Distance to block----------------------------------------------------------------------------------------------------
float Corpse::DistanceToBlock(int direction)
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
void Corpse::CheckCollision(float deltaTime)
{
    ///Block collision--------------------------------------------------
    ///Horizontal collision
    ///Left
    if (velocity.x < 0.0f)
    {
        if (DistanceToBlock(2) < abs(velocity.x) * deltaTime)
        {
            body.move(-DistanceToBlock(2), 0.0f);
        }
    }
    ///Right
    else if (velocity.x > 0.0f)
    {
        if (DistanceToBlock(3) < velocity.x * deltaTime)
        {
            body.move(DistanceToBlock(3), 0.0f);
        }
    }

    ///Vertical collision
    ///Ground
    if (DistanceToBlock(0) <= velocity.y * deltaTime)
    {
        velocity.x *= 0.75f;
        velocity.y *= -0.5f;
        body.move(0.0f, DistanceToBlock(0));
    }

    ///Ceiling
    if (DistanceToBlock(1) != 999999.0f)
    {
        if (-DistanceToBlock(1) > velocity.y * deltaTime)
        {
            ///Stop player from moving upwards
            velocity.y *= -0.5f;
            body.move(0.0f, -DistanceToBlock(1));
        }
    }

    ///Reverse after colliding with wall
    if (DistanceToBlock(2) <= 1.0f && velocity.x < 0.0f)
    {
        velocity.x *= -0.5f;
    }

    if (DistanceToBlock(3) <= 1.0f && velocity.x > 0.0f)
    {
        velocity.x *= -0.5f;
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

///Update----------------------------------------------------------------------------------------------------
void Corpse::Update(float deltaTime)
{
    ///Do physics--------------------------------------------------
    ///Decrease horizontal movement speed
    velocity.x *= 0.998f;

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
    if (velocity.y < 245.25f)
    {
        velocity.y += 858.375f * deltaTime;
    }
    else
    {
        velocity.y = 245.25f;
    }

    ///Do collision--------------------------------------------------
    CheckCollision(deltaTime);

    ///Move--------------------------------------------------
    body.move(velocity * deltaTime);

    ///Release particles--------------------------------------------------
    if (DistanceToBlock(0) <= 16.0f && abs(velocity.x) >= 9.81f)
    {
        if (rand() % 10 < abs(velocity.x) / 100.0f)
        {
            int startSize = (rand() % 4) + 4;
            particles.push_back(Particle(sf::Vector2f(body.getPosition().x + float((rand() % int(body.getSize().x))) - (body.getSize().x / 2.0f), body.getPosition().y + (body.getSize().y / 2.0f) - 16.0f), sf::Vector2f(startSize, startSize), 0, rand() % 4, bool(rand() % 2)));
        }
    }

    ///Update animation--------------------------------------------------
    ///Blue
    if (colour == 0)
    {
        sprite.setTexture(&texCorpseBlue);
        animation.SetTexture(&texCorpseBlue);
    }
    ///Red
    else
    {
        sprite.setTexture(&texCorpseRed);
        animation.SetTexture(&texCorpseRed);
    }

    ///Lying on face--------------------------------------------------
    if (state == 0)
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

    animation.Update(row, column, column, deltaTime, faceRight);
    sprite.setTextureRect(animation.uvRect);
    sprite.setPosition(body.getPosition());
}

///Draw----------------------------------------------------------------------------------------------------
void Corpse::Draw(sf::RenderWindow& window)
{
    sprite.move(0.0f, -16.0f);
    window.draw(sprite);
}
