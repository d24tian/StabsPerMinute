#include "header.h"
#include "decoration.h"

Decoration::Decoration(sf::Vector2f position, int type) :
    animation(&texTiles, sf::Vector2u(8, 16), 0.0f)
{
    body.setPosition(position);
    body.setSize(sf::Vector2f(32.0f, 32.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setTexture(&texTiles);
    this->row = 0;
    this->columnBegin = 0;
    this->columnEnd = 0;
    this->type = type;
}

Decoration::~Decoration()
{
    //dtor
}

void Decoration::Update(float deltaTime)
{
    ///Update animations
    body.setTexture(&texTiles);
    animation.SetTexture(&texTiles);
    ///Ground
    if (type == 0)
    {
        row = 2;
        columnBegin = 0;
        columnEnd = 0;
    }
    ///Ceiling platform
    else if (type == 1)
    {
        row = 2;
        columnBegin = 1;
        columnEnd = 1;
    }
    ///Pillar shaft
    else if (type == 2)
    {
        row = 2;
        columnBegin = 2;
        columnEnd = 2;
    }
    ///Pillar base
    else if (type == 3)
    {
        row = 2;
        columnBegin = 3;
        columnEnd = 3;
    }
    ///Pillar top
    else if (type == 4)
    {
        row = 2;
        columnBegin = 4;
        columnEnd = 4;
    }
    animation.Update(row, columnBegin, columnEnd, deltaTime, true);
    body.setTextureRect(animation.uvRect);
}

void Decoration::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}
