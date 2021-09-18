#include "header.h"
#include "weapon.h"

Weapon::Weapon() :
    animation(&texWeapons, sf::Vector2u(4, 8), 0.0f)
{
    sprite.setSize(sf::Vector2f(64.0f, 32.0f));
    sprite.setPosition(body.getPosition());
    sprite.setTexture(&texWeapons);
    this->row = 0;
    this->column = 0;
    this->faceRight = true;
    this->type = 0;
    this->aim = 0;
    this->state = 1;
    this->statePrevious = 1; ///??????????
}

Weapon::~Weapon()
{
    //dtor
}

///Distance to block----------------------------------------------------------------------------------------------------
float Weapon::DistanceToBlock(int direction)
{
    float distance = 999999.0f;
    sf::Vector2f blockPos;
    int location;

    float bodyWidth = body.getSize().x;
    float bodyHeight = body.getSize().y;

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
                if (body.getPosition().x - bodyWidth < blockPos.x + 16 && body.getPosition().x - bodyWidth > blockPos.x - 16)
                {
                    isBlock = true;
                }
                ///Right
                if (body.getPosition().x + bodyWidth > blockPos.x - 16 && body.getPosition().x + bodyWidth < blockPos.x + 16)
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
                if (body.getPosition().x - bodyWidth < blockPos.x + 16 && body.getPosition().x - bodyWidth > blockPos.x - 16)
                {
                    isBlock = true;
                }
                ///Right
                if (body.getPosition().x + bodyWidth > blockPos.x - 16 && body.getPosition().x + bodyWidth < blockPos.x + 16)
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
            if (blockPos.x + 16 <= body.getPosition().x - bodyWidth && blockPos.y - 16 < body.getPosition().y + bodyHeight && blockPos.y + 16 > body.getPosition().y - bodyHeight)
            {
                if ((body.getPosition().x - bodyWidth) - (blockPos.x + 16) < distance)
                {
                    distance = (body.getPosition().x - bodyWidth) - (blockPos.x + 16);
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
            if (blockPos.x - 16 >= body.getPosition().x + bodyWidth && blockPos.y - 16 < body.getPosition().y + bodyHeight && blockPos.y + 16 > body.getPosition().y - bodyHeight)
            {
                if ((blockPos.x - 16) - (body.getPosition().x + bodyWidth) < distance)
                {
                    distance = (blockPos.x - 16) - (body.getPosition().x + bodyWidth);
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
            return (body.getPosition().x - bodyWidth) - (blocks[location].GetPosition().x + 16);
        }
        ///Right
        else if (direction == 3)
        {
            return (blocks[location].GetPosition().x - 16) - (body.getPosition().x + bodyWidth);
        }
    }
}

///Update animation----------------------------------------------------------------------------------------------------
void Weapon::UpdateAnimation(float deltaTime)
{
    sprite.setTexture(&texWeapons);
    animation.SetTexture(&texWeapons);

    ///Do texture--------------------------------------------------
    ///Inactive
    if (state == 0)
    {
        ///Fists
        if (type == 0)
        {
            sprite.setFillColor(sf::Color(255, 255, 255, 0));
        }
        ///Sword
        else if (type == 1)
        {
            sprite.setFillColor(sf::Color(255, 255, 255, 255));
            row = 2;
            column = 0;
        }
    }
    ///Active
    else if (state == 1)
    {
        sprite.setFillColor(sf::Color(255, 255, 255, 255));
        ///Fists
        if (type == 0)
        {
            row = 0;
            column = 0;
        }
        ///Sword
        else if (type == 1)
        {
            row = 1;
            column = 0;
        }
    }
    ///Thrusting
    else if (state == 2)
    {
        sprite.setFillColor(sf::Color(255, 255, 255, 255));
        ///Fists
        if (type == 0)
        {
            row = 0;
            if (aim == -1)
            {
                column = 2;
            }
            else if (aim == 0)
            {
                column = 1;
            }
            else if (aim == 1)
            {
                column = 3;
            }
        }
        ///Sword
        else if (type == 1)
        {
            row = 1;
            if (aim == -1)
            {
                column = 2;
            }
            else if (aim == 0)
            {
                column = 1;
            }
            else if (aim == 1)
            {
                column = 3;
            }
        }
    }

    ///Set alpha--------------------------------------------------
    if (state == -1)
    {
        sprite.setFillColor(sf::Color(255, 255, 255, 0));
    }

    ///Update--------------------------------------------------
    animation.Update(row, column, column, deltaTime, faceRight);
    sprite.setTextureRect(animation.uvRect);
    sprite.setPosition(body.getPosition());
}

void Weapon::Draw(sf::RenderWindow& window)
{
    ///Set positions
    sprite.move(0.0f, -16.0f);
    window.draw(sprite);
    body.setFillColor(sf::Color(0, 255, 255, 100));
    body.move(0.0f, -16.0f);
    //window.draw(body);
    body.move(0.0f, 16.0f);
}
