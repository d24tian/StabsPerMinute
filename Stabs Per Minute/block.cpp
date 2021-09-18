#include "header.h"
#include "block.h"

Block::Block(sf::Vector2f position) :
    animation(&texTiles, sf::Vector2u(8, 16), 0.0f)
{
    body.setSize(sf::Vector2f(32.0f, 32.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(position);
    body.setTexture(&texTiles);
}

Block::~Block()
{
    //dtor
}

///Update----------------------------------------------------------------------------------------------------
void Block::Update(float deltaTime)
{
    ///Update animation
    body.setTexture(&texTiles);
    animation.SetTexture(&texTiles);
    animation.Update(0, 0, 0, deltaTime, true);
    body.setTextureRect(animation.uvRect);
}

///Draw----------------------------------------------------------------------------------------------------
void Block::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}
