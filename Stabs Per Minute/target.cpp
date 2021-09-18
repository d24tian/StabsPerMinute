#include "header.h"
#include "target.h"

Target::Target() :
    animation(&texTarget, sf::Vector2u(3, 2), 0.0f)
{
    body.setSize(sf::Vector2f(64.0f, 64.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setTexture(&texTarget);
    pulse.setSize(sf::Vector2f(64.0f, 64.0f));
    pulse.setOrigin(pulse.getSize() / 2.0f);
    pulse.setTexture(&texTarget);
    arrow.setSize(sf::Vector2f(64.0f, 64.0f));
    arrow.setOrigin(pulse.getSize() / 2.0f);
    arrow.setTexture(&texTarget);
    this->column = 0;
    this->lastFocus = focus;
    this->arrowTimer = 0.0f;
    this->arrowPosition = 0.0f;
}

Target::~Target()
{
    //dtor
}

///Update----------------------------------------------------------------------------------------------------
void Target::Update(float deltaTime)
{
    ///Set position--------------------------------------------------
    body.setPosition(sf::Vector2f(viewPosition.x, viewPosition.y - 120.0f));
    pulse.setPosition(body.getPosition());
    if (focus == -1)
    {
        arrow.setPosition(body.getPosition());
    }
    else if (focus == 0)
    {
        arrow.setPosition(sf::Vector2f(body.getPosition().x + 64.0f, body.getPosition().y));
    }
    else if (focus == 1)
    {
        arrow.setPosition(sf::Vector2f(body.getPosition().x - 64.0f, body.getPosition().y));
    }

    ///Check focus change--------------------------------------------------
    if (focus != lastFocus)
    {
        pulse.setFillColor(sf::Color(255, 255, 255, 100));
        pulse.setSize(sf::Vector2f(64.0f, 64.0f));
        lastFocus = focus;
    }

    ///Do pulse--------------------------------------------------
    ///Pulse finished
    if (pulse.getFillColor().a <= 0)
    {
        pulse.setFillColor(sf::Color(255, 255, 255, 0));
        pulse.setSize(sf::Vector2f(64.0f, 64.0f));
        pulse.setOrigin(pulse.getSize() / 2.0f);
    }
    ///Pulse unfinished
    else
    {
        pulse.setFillColor(sf::Color(255, 255, 255, pulse.getFillColor().a - deltaTime * 100.0f));
        pulse.setSize(sf::Vector2f(pulse.getSize().x + deltaTime * 100.0f, pulse.getSize().y + deltaTime * 100.0f));
        pulse.setOrigin(pulse.getSize() / 2.0f);
    }

    ///Do arrow pulse
    if (focus == -1)
    {
        arrowTimer = 0.0f;
        arrowPosition = 0.0f;
    }
    else
    {
        if (arrowTimer < 0.5f)
        {
            arrowPosition += 98.1 * deltaTime;
            arrowTimer += deltaTime;
        }
        else if (arrowTimer < 1.0f)
        {
            arrowPosition -= 98.1 * deltaTime;
            arrowTimer += deltaTime;
        }
        else
        {
            arrowTimer = 0.0f;
        }
    }

    ///Move arrow
    if (focus == -1)
    {
        arrow.setPosition(body.getPosition());
    }
    else if (focus == 0)
    {
        arrow.setPosition(sf::Vector2f(body.getPosition().x + arrowPosition + 32.0f, body.getPosition().y));
    }
    else if (focus == 1)
    {
        arrow.setPosition(sf::Vector2f(body.getPosition().x - arrowPosition - 32.0f, body.getPosition().y));
    }

    ///Update animation--------------------------------------------------
    body.setTexture(&texTarget);
    pulse.setTexture(&texTarget);
    arrow.setTexture(&texTarget);
    animation.SetTexture(&texTarget);

    ///No focus
    if (focus == -1)
    {
        column = 0;
    }
    ///Focus on blue
    else if (focus == 0)
    {
        column = 1;
    }
    ///Focus on red
    else if (focus == 1)
    {
        column = 2;
    }

    animation.Update(0, column, column, deltaTime, true);
    body.setTextureRect(animation.uvRect);
    pulse.setTextureRect(animation.uvRect);

    animation.Update(1, column, column, 0.0f, true);
    arrow.setTextureRect(animation.uvRect);
}

///Draw----------------------------------------------------------------------------------------------------
void Target::Draw(sf::RenderWindow& window)
{
    window.draw(arrow);
    window.draw(body);
    window.draw(pulse);
}
