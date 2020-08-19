#pragma once

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <tuple>

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"


// Server


#define numTeams 8
#define port 2000

const sf::Time selectorTimeout = sf::milliseconds(100); 