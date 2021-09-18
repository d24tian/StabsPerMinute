/**

Hey there! Please take a look at the readme file for controls and explainations of game mechanics!

WARNING: the code that follows will make you cry;
         a safety pig has been provided below for your benefit
                         _
 _._ _..._ .-',     _.._(`))
'-. `     '  /-._.-'    ',/
   )         \            '.
  / _    _    |             \
 |  a    a    /              |
 \   .-.                     ;
  '-('' ).-'       ,'       ;
     '-;           |      .'
        \           \    /
        | 7  .__  _.-\   \
        | |  |  ``/  /`  /
       /,_|  |   /,_/   /
          /,_/      '`-'
*/

#include "header.h"

///Vectors
vector<Block> blocks;
vector<Corpse> corpses;
vector<Decoration> decorations;
vector<Item> items;
vector<Particle> particles;
vector<Spike> spikes;

///Audio manager
AudioManager audioManager;

///Classes
Blue blue(sf::Vector2f(-64.0f, 128.0f));
Red red(sf::Vector2f(64.0f, 128.0f));
BlueWeapon blueWeapon;
RedWeapon redWeapon;
BlueHealthBar blueHealthBar;
RedHealthBar redHealthBar;
Target target;

///Resources
sf::Texture texBlue;
sf::Texture texCorpseBlue;
sf::Texture texCorpseRed;
sf::Texture texHealthBar;
sf::Texture texHurtBorder;
sf::Texture texItems;
sf::Texture texOverlay;
sf::Texture texParticle;
sf::Texture texRed;
sf::Texture texTarget;
sf::Texture texTiles;
sf::Texture texWeapons;

sf::Font fntPressStart2P;

///Global variables
bool isPaused = false;

int gameState = 0;
float loadTimer = 3.0f;
int level = 0;
int area = 0;
int focus = -1;

std::string requestedMusic = "";
std::string currentMusic = "";

static const float VIEW_HEIGHT = 320.0f;
sf::Vector2f viewPosition;
sf::Vector2f viewSize;

float timeElapsed = 0.0f;

///Manage view size
void ResizeView(sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
    ///Load textures
    texBlue.loadFromFile("sprites/texBlue.png");
    texCorpseBlue.loadFromFile("sprites/texCorpseBlue.png");
    texCorpseRed.loadFromFile("sprites/texCorpseRed.png");
    texHealthBar.loadFromFile("sprites/texHealthBar.png");
    texHurtBorder.loadFromFile("sprites/texHurtBorder.png");
    texItems.loadFromFile("sprites/texItems.png");
    texOverlay.loadFromFile("sprites/texOverlay.png");
    texParticle.loadFromFile("sprites/texParticle.png");
    texRed.loadFromFile("sprites/texRed.png");
    texTarget.loadFromFile("sprites/texTarget.png");
    texTiles.loadFromFile("sprites/texTiles.png");
    texWeapons.loadFromFile("sprites/texWeapons.png");

    ///Load fonts
    fntPressStart2P.loadFromFile("fonts/fntPressStart2P.ttf");

    ///Create window
    sf::RenderWindow window(sf::VideoMode(960.0f, 640.0f), "Stabs per Minute", sf::Style::Close | sf::Style::Titlebar);

    ///Create view
    sf::View view(sf::Vector2f(0.0f, window.getSize().y / 4.0f - 16.0f), sf::Vector2f(480.0f, 320.0f));
    ResizeView(window, view);
    viewPosition.x = 0.0f;
    viewPosition.y = window.getSize().y / 4.0f - 16.0f;
    viewSize = view.getSize();

    ///Create audio manager
    audioManager.LoadAudio();
    audioManager.Add("audio/nothing.wav", false);
    audioManager.Add("audio/overworld.wav", true);
    audioManager.SetCurrent(0);

    ///Create overlay
    sf::RectangleShape overlay;
    overlay.setSize(view.getSize());
    overlay.setTexture(&texOverlay);
    overlay.setOrigin(overlay.getSize() / 2.0f);
    overlay.setFillColor(sf::Color(255, 255, 255, 100));

    ///Start deltaTime
    float deltaTime = 0.0f;
    sf::Clock clock;

    ///Main window loop
    while (window.isOpen())
    {
        ///Event switch
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                ResizeView(window, view);
                break;
            case sf::Event::GainedFocus:
                audioManager.GetCurrent()->play();
                deltaTime = clock.restart().asSeconds();
                isPaused = false;
                break;
            case sf::Event::LostFocus:
                audioManager.GetCurrent()->pause();
                isPaused = true;
                break;
            }
        }

        ///Paused--------------------------------------------------
        if (isPaused)
        {
            ///Add pause text?
        }
        ///Not paused--------------------------------------------------
        else
        {
            ///Restart deltaTime at beginning of frame--------------------------------------------------
            deltaTime = clock.restart().asSeconds();

            ///Manage music--------------------------------------------------
            ///Make sure that if the requested music is already playing as the current music, then we do not restart the music
            if (requestedMusic != currentMusic)
            {
                ///Stop the previous track
                if (audioManager.GetCurrent()->getStatus() == sf::SoundSource::Playing)
                {
                    audioManager.GetCurrent()->stop();
                }

                ///Set the new track
                if (requestedMusic == "")
                {
                    audioManager.SetCurrent(0);
                }
                else if (requestedMusic == "overworld")
                {
                    audioManager.SetCurrent(1);
                }
                ///Play the new track
                audioManager.GetCurrent()->play();
                currentMusic = requestedMusic;
            }

            ///Menu--------------------------------------------------
            if (gameState == 0)
            {
                StartLevel(level);
                gameState = 1;

                window.clear(sf::Color(64, 64, 96));

                ///Set view center
                viewPosition.x = 0.0f;
                viewPosition.y = window.getSize().y / 4.0f - 16.0f;

                ///Draw all objects

                window.display();
            }
            ///Game--------------------------------------------------
            else if (gameState == 1)
            {
                ///Refresh window--------------------------------------------------
                window.clear(sf::Color(64, 64, 96));

                ///Update players--------------------------------------------------
                blue.Update(deltaTime);
                red.Update(deltaTime);
                blueWeapon.Update(deltaTime);
                redWeapon.Update(deltaTime);

                ///Check victory--------------------------------------------------
                if (area == 3)
                {
                    if (red.state != -1)
                    {
                        red.Hurt(100);
                    }
                    red.stateTimer = 0.0f;
                    focus = 0;
                }
                else if (area == -3)
                {
                    if (blue.state != -1)
                    {
                        blue.Hurt(100);
                    }
                    blue.stateTimer = 0.0f;
                    focus = 1;
                }

                ///Make sure player does not go above level--------------------------------------------------
                if (blue.GetPosition().y < 0.0f)
                {
                    blue.SetPosition(sf::Vector2f(blue.GetPosition().x, 0.0f));
                }
                if (red.GetPosition().y < 0.0f)
                {
                    red.SetPosition(sf::Vector2f(red.GetPosition().x, 0.0f));
                }

                ///Set view--------------------------------------------------
                ///Horizontal
                ///Determine the size of current map
                sf::Vector2f mapSize;
                if (area == 0)
                {
                    mapSize.x = 33.0f * 32.0f;
                }
                else
                {
                    mapSize.x = 32.0f * 32.0f;
                }
                mapSize.y = 12.0f * 32.0f;

                ///Determine room center
                float roomCenter;
                if (area == 0)
                {
                    roomCenter = 0.0f;
                }
                else
                {
                    if (area > 0)
                    {
                        roomCenter = (area * 32.0f * 32.0f) + 16.0f;
                    }
                    else if (area < 0)
                    {
                        roomCenter = (area * 32.0f * 32.0f) - 16.0f;
                    }
                }

                ///No focus--------------------------------------------------
                if (focus == -1)
                {
                    ///Determine player average position
                    sf::Vector2f playerAverage = (blue.GetPosition() + red.GetPosition()) / 2.0f;

                    ///Prevent unfocused players from leaving
                    if (blue.GetPosition().x < roomCenter - mapSize.x / 2.0f)
                    {
                        blue.SetPosition(sf::Vector2f(roomCenter - mapSize.x / 2.0f, blue.GetPosition().y));
                    }
                    else if (blue.GetPosition().x > roomCenter + mapSize.x / 2.0f)
                    {
                        blue.SetPosition(sf::Vector2f(roomCenter + mapSize.x / 2.0f, blue.GetPosition().y));
                    }

                    if (red.GetPosition().x < roomCenter - mapSize.x / 2.0f)
                    {
                        red.SetPosition(sf::Vector2f(roomCenter - mapSize.x / 2.0f, red.GetPosition().y));
                    }
                    else if (red.GetPosition().x > roomCenter + mapSize.x / 2.0f)
                    {
                        red.SetPosition(sf::Vector2f(roomCenter + mapSize.x / 2.0f, red.GetPosition().y));
                    }

                    ///IDK, MAYBE KEEP MAYBE REMOVE LATER?
                    ///Change area
                    if (area != 0)
                    {
                        if (playerAverage.x > roomCenter + mapSize.x / 2.0f)
                        {
                            area++;
                        }
                        else if (playerAverage.x < roomCenter - mapSize.x / 2.0f)
                        {
                            area--;
                        }
                    }

                    ///The view is out of bounds
                    ///Too far right, need to move to the left
                    if (roomCenter + (mapSize.x / 2.0f) - (view.getSize().x / 2.0f) < min(playerAverage.x, viewPosition.x))
                    {
                        viewPosition.x -= abs(viewPosition.x - (roomCenter + (mapSize.x / 2.0f) - (view.getSize().x / 2.0f) - 2.0f)) * 10.0f * deltaTime;
                    }
                    ///Too far left, need to move to the right
                    else if (roomCenter - (mapSize.x / 2.0f) + (view.getSize().x / 2.0f) > max(playerAverage.x, viewPosition.x))
                    {
                        viewPosition.x += abs(viewPosition.x - (roomCenter - (mapSize.x / 2.0f) + (view.getSize().x / 2.0f) + 2.0f)) * 10.0f * deltaTime;
                    }
                    else
                    {
                        ///The view needs to move to the left
                        if (max(playerAverage.x, roomCenter - (mapSize.x / 2.0f) + (view.getSize().x / 2.0f)) < viewPosition.x)
                        {
                            ///Check for out of bounds
                            if (roomCenter - (mapSize.x / 2.0f) + (view.getSize().x / 2.0f) < playerAverage.x)
                            {
                                viewPosition.x -= abs(viewPosition.x - playerAverage.x) * 10.0f * deltaTime;
                            }
                            else
                            {
                                viewPosition.x -= abs(viewPosition.x - (roomCenter - (mapSize.x / 2.0f) + (view.getSize().x / 2.0f))) * 10.0f * deltaTime;
                            }
                        }
                        ///The view needs to move to the right
                        else if (min(playerAverage.x, roomCenter + (mapSize.x / 2.0f) - (view.getSize().x / 2.0f)) > viewPosition.x)
                        {
                            ///Check for out of bounds
                            if (roomCenter + (mapSize.x / 2.0f) - (view.getSize().x / 2.0f) > playerAverage.x)
                            {
                                viewPosition.x += abs(viewPosition.x - playerAverage.x) * 10.0f * deltaTime;
                            }
                            else
                            {
                                viewPosition.x += abs(viewPosition.x - (roomCenter + (mapSize.x / 2.0f) - (view.getSize().x / 2.0f))) * 10.0f * deltaTime;
                            }
                        }
                    }

                    ///Vertical
                    ///The view needs to move up
                    if (max(playerAverage.y - 48.0f, (view.getSize().y / 2.0f) - 16.0f) < viewPosition.y)
                    {
                        ///Not out of bounds
                        if (viewPosition.y > (view.getSize().y / 2.0f) - 16.0f)
                        {
                            viewPosition.y -= abs(viewPosition.y - max(playerAverage.y - 48.0f, (view.getSize().y / 2.0f) - 16.0f)) * 2.0f * deltaTime;
                        }
                        ///Out of bounds
                        else
                        {
                            viewPosition.y = (view.getSize().y / 2.0f) - 16.0f;
                        }
                    }
                    ///The view needs to move down
                    else if (min(playerAverage.y - 48.0f, mapSize.y - (view.getSize().y / 2.0f) - 16.0f) > viewPosition.y)
                    {
                        ///Not out of bounds
                        if (viewPosition.y < mapSize.y - (view.getSize().y / 2.0f) - 16.0f)
                        {
                            viewPosition.y += abs(viewPosition.y - min(playerAverage.y - 48.0f, mapSize.y - (view.getSize().y / 2.0f) - 16.0f)) * 2.0f * deltaTime;
                        }
                        ///Out of bounds
                        else
                        {
                            viewPosition.y = mapSize.y - (view.getSize().y / 2.0f) - 16.0f;
                        }
                    }
                }
                ///Focus on blue--------------------------------------------------
                else if (focus == 0)
                {
                    ///Prevent unfocused player from leaving
                    if (red.GetPosition().x < roomCenter - mapSize.x / 2.0f)
                    {
                        red.SetPosition(sf::Vector2f(roomCenter - mapSize.x / 2.0f, red.GetPosition().y));
                    }
                    else if (red.GetPosition().x > roomCenter + mapSize.x / 2.0f)
                    {
                        red.SetPosition(sf::Vector2f(roomCenter + mapSize.x / 2.0f, red.GetPosition().y));
                    }

                    ///Change area
                    if (blue.GetPosition().x > roomCenter + mapSize.x / 2.0f)
                    {
                        area++;
                        if (red.state != -1)
                        {
                            red.Warp();
                        }
                    }
                    ///Prevent movement in opposite direction
                    else if (blue.GetPosition().x < roomCenter - mapSize.x / 2.0f)
                    {
                        blue.SetPosition(sf::Vector2f(roomCenter - mapSize.x / 2.0f, blue.GetPosition().y));
                    }

                    ///The view is out of bounds
                    ///Too far right, need to move to the left
                    if (roomCenter + (mapSize.x / 2.0f) - (view.getSize().x / 2.0f) < min(blue.GetPosition().x + 96.0f, viewPosition.x))
                    {
                        viewPosition.x -= abs(viewPosition.x - (roomCenter + (mapSize.x / 2.0f) - (view.getSize().x / 2.0f) - 4.0f)) * 10.0f * deltaTime;
                    }
                    ///Too far left, need to move to the right
                    else if (roomCenter - (mapSize.x / 2.0f) + (view.getSize().x / 2.0f) > max(blue.GetPosition().x + 96.0f, viewPosition.x))
                    {
                        viewPosition.x += abs(viewPosition.x - (roomCenter - (mapSize.x / 2.0f) + (view.getSize().x / 2.0f) + 4.0f)) * 10.0f * deltaTime;
                    }
                    else
                    {
                        ///The view needs to move to the left
                        if (max(blue.GetPosition().x + 96.0f, roomCenter - (mapSize.x / 2.0f) + (view.getSize().x / 2.0f)) < viewPosition.x)
                        {
                            ///Check for out of bounds
                            if (roomCenter - (mapSize.x / 2.0f) + (view.getSize().x / 2.0f) < blue.GetPosition().x + 96.0f)
                            {
                                viewPosition.x -= abs(viewPosition.x - (blue.GetPosition().x + 96.0f)) * 10.0f * deltaTime;
                            }
                            else
                            {
                                viewPosition.x -= abs(viewPosition.x - (roomCenter - (mapSize.x / 2.0f) + (view.getSize().x / 2.0f))) * 10.0f * deltaTime;
                            }
                        }
                        ///The view needs to move to the right
                        else if (min(blue.GetPosition().x + 96.0f, roomCenter + (mapSize.x / 2.0f) - (view.getSize().x / 2.0f)) > viewPosition.x)
                        {
                            ///Check for out of bounds
                            if (roomCenter + (mapSize.x / 2.0f) - (view.getSize().x / 2.0f) > blue.GetPosition().x + 96.0f)
                            {
                                viewPosition.x += abs(viewPosition.x - (blue.GetPosition().x + 96.0f)) * 10.0f * deltaTime;
                            }
                            else
                            {
                                viewPosition.x += abs(viewPosition.x - (roomCenter + (mapSize.x / 2.0f) - (view.getSize().x / 2.0f))) * 10.0f * deltaTime;
                            }
                        }
                    }

                    ///Vertical
                    ///The view needs to move up
                    if (max(blue.GetPosition().y - 48.0f, (view.getSize().y / 2.0f) - 16.0f) < viewPosition.y)
                    {
                        ///Not out of bounds
                        if (viewPosition.y > (view.getSize().y / 2.0f) - 16.0f)
                        {
                            viewPosition.y -= abs(viewPosition.y - max(blue.GetPosition().y - 48.0f, (view.getSize().y / 2.0f) - 16.0f)) * 2.0f * deltaTime;
                        }
                        ///Out of bounds
                        else
                        {
                            viewPosition.y = (view.getSize().y / 2.0f) - 16.0f;
                        }
                    }
                    ///The view needs to move down
                    else if (min(blue.GetPosition().y - 48.0f, mapSize.y - (view.getSize().y / 2.0f) - 16.0f) > viewPosition.y)
                    {
                        ///Not out of bounds
                        if (viewPosition.y < mapSize.y - (view.getSize().y / 2.0f) - 16.0f)
                        {
                            viewPosition.y += abs(viewPosition.y - min(blue.GetPosition().y - 48.0f, mapSize.y - (view.getSize().y / 2.0f) - 16.0f)) * 2.0f * deltaTime;
                        }
                        ///Out of bounds
                        else
                        {
                            viewPosition.y = mapSize.y - (view.getSize().y / 2.0f) - 16.0f;
                        }
                    }
                }
                ///Focus on red--------------------------------------------------
                else if (focus == 1)
                {
                    ///Prevent unfocused player from leaving
                    if (blue.GetPosition().x < roomCenter - mapSize.x / 2.0f)
                    {
                        blue.SetPosition(sf::Vector2f(roomCenter - mapSize.x / 2.0f, blue.GetPosition().y));
                    }
                    else if (blue.GetPosition().x > roomCenter + mapSize.x / 2.0f)
                    {
                        blue.SetPosition(sf::Vector2f(roomCenter + mapSize.x / 2.0f, blue.GetPosition().y));
                    }

                    ///Change area
                    if (red.GetPosition().x < roomCenter - mapSize.x / 2.0f)
                    {
                        area--;
                        if (blue.state != -1)
                        {
                            blue.Warp();
                        }
                    }
                    ///Prevent movement in opposite direction
                    else if (red.GetPosition().x > roomCenter + mapSize.x / 2.0f)
                    {
                        red.SetPosition(sf::Vector2f(roomCenter + mapSize.x / 2.0f, red.GetPosition().y));
                    }

                    ///The view is out of bounds
                    ///Too far right, need to move to the left
                    if (roomCenter + (mapSize.x / 2.0f) - (view.getSize().x / 2.0f) < min(red.GetPosition().x - 96.0f, viewPosition.x))
                    {
                        viewPosition.x -= abs(viewPosition.x - (roomCenter + (mapSize.x / 2.0f) - (view.getSize().x / 2.0f) - 4.0f)) * 10.0f * deltaTime;
                    }
                    ///Too far left, need to move to the right
                    else if (roomCenter - (mapSize.x / 2.0f) + (view.getSize().x / 2.0f) > max(red.GetPosition().x - 96.0f, viewPosition.x))
                    {
                        viewPosition.x += abs(viewPosition.x - (roomCenter - (mapSize.x / 2.0f) + (view.getSize().x / 2.0f) + 4.0f)) * 10.0f * deltaTime;
                    }
                    else
                    {
                        ///The view needs to move to the left
                        if (max(red.GetPosition().x - 96.0f, roomCenter - (mapSize.x / 2.0f) + (view.getSize().x / 2.0f)) < viewPosition.x)
                        {
                            ///Check for out of bounds
                            if (roomCenter - (mapSize.x / 2.0f) + (view.getSize().x / 2.0f) < red.GetPosition().x - 96.0f)
                            {
                                viewPosition.x -= abs(viewPosition.x - (red.GetPosition().x - 96.0f)) * 10.0f * deltaTime;
                            }
                            else
                            {
                                viewPosition.x -= abs(viewPosition.x - (roomCenter - (mapSize.x / 2.0f) + (view.getSize().x / 2.0f))) * 10.0f * deltaTime;
                            }
                        }
                        ///The view needs to move to the right
                        else if (min(red.GetPosition().x - 96.0f, roomCenter + (mapSize.x / 2.0f) - (view.getSize().x / 2.0f)) > viewPosition.x)
                        {
                            ///Check for out of bounds
                            if (roomCenter + (mapSize.x / 2.0f) - (view.getSize().x / 2.0f) > red.GetPosition().x - 96.0f)
                            {
                                viewPosition.x += abs(viewPosition.x - (red.GetPosition().x - 96.0f)) * 10.0f * deltaTime;
                            }
                            else
                            {
                                viewPosition.x += abs(viewPosition.x - (roomCenter + (mapSize.x / 2.0f) - (view.getSize().x / 2.0f))) * 10.0f * deltaTime;
                            }
                        }
                    }

                    ///Vertical
                    ///The view needs to move up
                    if (max(red.GetPosition().y - 48.0f, (view.getSize().y / 2.0f) - 16.0f) < viewPosition.y)
                    {
                        ///Not out of bounds
                        if (viewPosition.y > (view.getSize().y / 2.0f) - 16.0f)
                        {
                            viewPosition.y -= abs(viewPosition.y - max(red.GetPosition().y - 48.0f, (view.getSize().y / 2.0f) - 16.0f)) * 2.0f * deltaTime;
                        }
                        ///Out of bounds
                        else
                        {
                            viewPosition.y = (view.getSize().y / 2.0f) - 16.0f;
                        }
                    }
                    ///The view needs to move down
                    else if (min(red.GetPosition().y - 48.0f, mapSize.y - (view.getSize().y / 2.0f) - 16.0f) > viewPosition.y)
                    {
                        ///Not out of bounds
                        if (viewPosition.y < mapSize.y - (view.getSize().y / 2.0f) - 16.0f)
                        {
                            viewPosition.y += abs(viewPosition.y - min(red.GetPosition().y - 48.0f, mapSize.y - (view.getSize().y / 2.0f) - 16.0f)) * 2.0f * deltaTime;
                        }
                        ///Out of bounds
                        else
                        {
                            viewPosition.y = mapSize.y - (view.getSize().y / 2.0f) - 16.0f;
                        }
                    }
                }

                ResizeView(window, view);
                view.setCenter(viewPosition);
                window.setView(view);

                ///Draw all objects
                for (int i = 0; i < blocks.size(); i++)
                {
                    blocks[i].Update(deltaTime);
                    blocks[i].Draw(window);
                }

                for (int i = 0; i < decorations.size(); i++)
                {
                    decorations[i].Update(deltaTime);
                    decorations[i].Draw(window);
                }

                for (int i = 0; i < spikes.size(); i++)
                {
                    spikes[i].Update(deltaTime);
                    spikes[i].Draw(window);
                }

                for (int i = 0; i < corpses.size(); i++)
                {
                    corpses[i].Update(deltaTime);
                    corpses[i].Draw(window);

                    if (corpses[i].GetPosition().x < roomCenter - mapSize.x / 2.0f || corpses[i].GetPosition().x > roomCenter + mapSize.x / 2.0f)
                    {
                        corpses.erase(corpses.begin() + i);
                    }
                }

                for (int i = 0; i < items.size(); i++)
                {
                    items[i].Update(deltaTime);
                    items[i].Draw(window);

                    if (items[i].GetPosition().x < roomCenter - mapSize.x / 2.0f || items[i].GetPosition().x > roomCenter + mapSize.x / 2.0f)
                    {
                        items.erase(items.begin() + i);
                    }
                }

                ///Draw players
                blue.Draw(window);
                red.Draw(window);
                blueWeapon.Draw(window);
                redWeapon.Draw(window);

                ///Draw particles
                for (int i = 0; i < particles.size(); i++)
                {
                    particles[i].Update(deltaTime);
                    particles[i].Draw(window);
                    if (particles[i].finished)
                    {
                        particles.erase(particles.begin() + i);
                    }
                }

                ///Update and draw overlay
                overlay.setPosition(view.getCenter());
                window.draw(overlay);

                ///Update and draw UI
                blueHealthBar.Update(deltaTime);
                redHealthBar.Update(deltaTime);
                blueHealthBar.SetPosition(sf::Vector2f(view.getCenter().x - 180.0f, view.getCenter().y + 100.0f));
                redHealthBar.SetPosition(sf::Vector2f(view.getCenter().x + 180.0f, view.getCenter().y + 100.0f));
                blueHealthBar.Draw(window);
                redHealthBar.Draw(window);
                target.Update(deltaTime);
                target.Draw(window);

                window.display();

                ///Output deltaTime and timeElapsed
                timeElapsed += deltaTime;
                cout << "deltaTime: " << setw(8) << deltaTime << setw(14) << "timeElapsed: " << setw(7) << timeElapsed << endl;
            }
        }
    }

    return 0; ///LOL NO
}
