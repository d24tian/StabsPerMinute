#include "header.h"
#include "spike.h"

Spike::Spike(sf::Vector2f position) :
    animation(&texTiles, sf::Vector2u(8, 16), 0.0f)
{
    body.setSize(sf::Vector2f(32.0f, 32.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(position);
    body.setTexture(&texTiles);
}

Spike::~Spike()
{
    //dtor
}

///Update----------------------------------------------------------------------------------------------------
void Spike::Update(float deltaTime)
{
    ///Check collision with players
    ///Blue
    sf::Vector2f otherPos = sf::Vector2f(blue.GetPosition().x, blue.GetPosition().y - 16.0f);
    sf::Vector2f otherHalfSize = blue.GetHalfSize() / 2.0f;
    sf::Vector2f thisPos = GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();

    float deltaX = otherPos.x - thisPos.x;
    float deltaY = otherPos.y - thisPos.y;

    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if (intersectX < 0.0f && intersectY < 0.0f)
    {
        if (blue.state != -1)
        {
            blue.Hurt(50);
        }
    }

    ///Red
    otherPos = sf::Vector2f(red.GetPosition().x, red.GetPosition().y - 16.0f);
    otherHalfSize = red.GetHalfSize() / 2.0f;
    thisPos = GetPosition();
    thisHalfSize = GetHalfSize();

    deltaX = otherPos.x - thisPos.x;
    deltaY = otherPos.y - thisPos.y;

    intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if (intersectX < 0.0f && intersectY < 0.0f)
    {
        if (red.state != -1)
        {
            red.Hurt(50);
        }
    }

    ///Update animation
    body.setTexture(&texTiles);
    animation.SetTexture(&texTiles);
    animation.Update(3, 0, 0, deltaTime, true);
    body.setTextureRect(animation.uvRect);
}

///Draw----------------------------------------------------------------------------------------------------
void Spike::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}
