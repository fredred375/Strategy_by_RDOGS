#pragma once

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <math.h>
#include <queue>
#include <sstream>
#include <stdlib.h>
#include <stack>
#include <string>
#include <tuple>
#include <vector>

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"


// Server


#define numTeams 8
#define numShops 75
#define numRevPhases 5
#define numCapPhases 4
#define port 2000


const sf::Time selectorTimeout = sf::milliseconds(250); 

const sf::Time purchaseCD = sf::seconds(90);

const sf::Time backUpTimeGap = sf::seconds(60);

enum class GameMode
{
	Debug,

	Test,

	Release,
};