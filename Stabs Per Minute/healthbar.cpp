#include "header.h"
#include "healthbar.h"

HealthBar::HealthBar() :
    animation(&texHealthBar, sf::Vector2u(4, 1), 0.0f)
{
    body.setSize(sf::Vector2f(64.0f, 64.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setTexture(&texHealthBar);
    frame.setSize(sf::Vector2f(64.0f, 64.0f));
    frame.setOrigin(frame.getSize() / 2.0f);
    frame.setTexture(&texHealthBar);
    number.setFont(fntPressStart2P);
    number.setCharacterSize(12);
    number.setFillColor(sf::Color::White);
    number.setOutlineThickness(2.0f);
    number.setOutlineColor(sf::Color::Black);
    this->pulseTimer = 0.0f;
}

HealthBar::~HealthBar()
{
    //dtor
}

///Draw----------------------------------------------------------------------------------------------------
void HealthBar::Draw(sf::RenderWindow& window)
{
    window.draw(frame);
    window.draw(body);
    window.draw(number);
}
