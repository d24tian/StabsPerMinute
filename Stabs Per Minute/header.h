#pragma once

#include "animation.h"
#include "audiomanager.h"
#include "block.h"
#include "blue.h"
#include "bluehealthbar.h"
#include "blueweapon.h"
#include "corpse.h"
#include "decoration.h"
#include "healthbar.h"
#include "item.h"
#include "particle.h"
#include "player.h"
#include "red.h"
#include "redhealthbar.h"
#include "redweapon.h"
#include "spike.h"
#include "target.h"
#include "weapon.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

struct blockPoint
{
    int index;
	int x;
	int y;
	int type;
};

///Game functions
void StartLevel(int index);

///Global audio manager
extern AudioManager audioManager;

///Global classes
extern Blue blue;
extern Red red;
extern BlueWeapon blueWeapon;
extern RedWeapon redWeapon;

///Global vectors
extern vector<Block> blocks;
extern vector<Corpse> corpses;
extern vector<Decoration> decorations;
extern vector<Item> items;
extern vector<Particle> particles;
extern vector<Spike> spikes;

///Global resources
extern sf::Texture texBlue;
extern sf::Texture texCorpseBlue;
extern sf::Texture texCorpseRed;
extern sf::Texture texHealthBar;
extern sf::Texture texHurtBorder;
extern sf::Texture texItems;
extern sf::Texture texOverlay;
extern sf::Texture texParticle;
extern sf::Texture texRed;
extern sf::Texture texTarget;
extern sf::Texture texTiles;
extern sf::Texture texWeapons;

extern sf::Font fntPressStart2P;

///Global variables
extern bool isPaused;
extern int gameState;
extern float loadTimer;
extern int level;
extern int area;
extern int focus;
extern std::string requestedMusic;
extern std::string currentMusic;
extern sf::Vector2f viewPosition;
extern sf::Vector2f viewSize;

extern float timeElapsed;
