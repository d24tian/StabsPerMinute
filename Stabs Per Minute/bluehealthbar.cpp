#include "header.h"
#include "bluehealthbar.h"

///Pulse----------------------------------------------------------------------------------------------------
void BlueHealthBar::Pulse(float deltaTime)
{
    ///Do pulse--------------------------------------------------
    if (blue.health > 50)
    {
        if (pulseTimer >= 2.4f)
        {
            body.setSize(sf::Vector2f(64.0f * blue.health / 100.0f, 64.0f * blue.health / 100.0f));
            pulseTimer = 0.0f;
        }
        else if (pulseTimer >= 2.2f)
        {
            body.setSize(sf::Vector2f(body.getSize().x - (deltaTime * 64.0f), body.getSize().y - (deltaTime * 64.0f)));
        }
        else if (pulseTimer >= 2.0f)
        {
            body.setSize(sf::Vector2f(body.getSize().x + (deltaTime * 64.0f), body.getSize().y + (deltaTime * 64.0f)));
        }
        else
        {
            body.setSize(sf::Vector2f(64.0f * blue.health / 100.0f, 64.0f * blue.health / 100.0f));
        }
    }
    else if (blue.health > 20)
    {
        if (pulseTimer >= 1.4f)
        {
            body.setSize(sf::Vector2f(64.0f * blue.health / 100.0f, 64.0f * blue.health / 100.0f));
            pulseTimer = 0.0f;
        }
        else if (pulseTimer >= 1.2f)
        {
            body.setSize(sf::Vector2f(body.getSize().x - (deltaTime * 64.0f), body.getSize().y - (deltaTime * 64.0f)));
        }
        else if (pulseTimer >= 1.0f)
        {
            body.setSize(sf::Vector2f(body.getSize().x + (deltaTime * 64.0f), body.getSize().y + (deltaTime * 64.0f)));
        }
        else
        {
            body.setSize(sf::Vector2f(64.0f * blue.health / 100.0f, 64.0f * blue.health / 100.0f));
        }
    }
    else if (blue.health > 0)
    {
        if (pulseTimer >= 0.9f)
        {
            body.setSize(sf::Vector2f(64.0f * blue.health / 100.0f, 64.0f * blue.health / 100.0f));
            pulseTimer = 0.0f;
        }
        else if (pulseTimer >= 0.7f)
        {
            body.setSize(sf::Vector2f(body.getSize().x - (deltaTime * 64.0f), body.getSize().y - (deltaTime * 64.0f)));
        }
        else if (pulseTimer >= 0.5f)
        {
            body.setSize(sf::Vector2f(body.getSize().x + (deltaTime * 64.0f), body.getSize().y + (deltaTime * 64.0f)));
        }
        else
        {
            body.setSize(sf::Vector2f(64.0f * blue.health / 100.0f, 64.0f * blue.health / 100.0f));
        }
    }
    else
    {
        body.setSize(sf::Vector2f(0.0f, 0.0f));
        pulseTimer = 0.0f;
    }

    pulseTimer += deltaTime;
    body.setOrigin(body.getSize() / 2.0f);
}

///Update----------------------------------------------------------------------------------------------------
void BlueHealthBar::Update(float deltaTime)
{
    ///Do pulse--------------------------------------------------
    Pulse(deltaTime);

    ///Update animation--------------------------------------------------
    body.setTexture(&texHealthBar);
    frame.setTexture(&texHealthBar);
    animation.SetTexture(&texHealthBar);

    animation.Update(0, 1, 1, deltaTime, true);
    body.setTextureRect(animation.uvRect);

    animation.Update(0, 0, 0, deltaTime, true);
    frame.setTextureRect(animation.uvRect);

    ///Update text
    stringstream ns;
    ns << blue.health;
    string numberString = ns.str();
    number.setString(numberString);
    number.setOrigin(sf::Vector2f(number.getCharacterSize() * number.getString().getSize() / 2.0f, number.getCharacterSize() / 2.0f));
}
