#include "header.h"
#include "particle.h"

Particle::Particle(sf::Vector2f position, sf::Vector2f startSize, int row, int column, bool faceRight) :
    animation(&texParticle, sf::Vector2u(4, 2), 0.0f)
{
    body.setSize(startSize);
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(position);
    body.setTexture(&texParticle);
    body.setFillColor(sf::Color(255, 255, 255, 200));
    this->row = row;
    this->column = column;
    this->faceRight = faceRight;
    this->finished = false;
}

Particle::~Particle()
{
    //dtor
}

///Update----------------------------------------------------------------------------------------------------
void Particle::Update(float deltaTime)
{
    ///Fade
    if (body.getSize().x > 0.0f && body.getSize().y > 0.0f)
    {
        body.setFillColor(sf::Color(255, 255, 255, body.getFillColor().a - deltaTime * 10.0f));
        body.setSize(sf::Vector2f(body.getSize().x - deltaTime * 10.0f, body.getSize().y - deltaTime * 10.0f));
        body.setOrigin(body.getSize() / 2.0f);
    }
    ///Fade finished, delete
    else
    {
        finished = true;
    }

    ///Update animation
    body.setTexture(&texParticle);
    animation.SetTexture(&texParticle);
    animation.Update(row, column, column, deltaTime, faceRight);
    body.setTextureRect(animation.uvRect);
}

///Draw----------------------------------------------------------------------------------------------------
void Particle::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}
