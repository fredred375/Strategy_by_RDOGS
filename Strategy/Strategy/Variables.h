#pragma once

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <stack>
#include <tuple>
#include <map>

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"


// Client

#define numTeams 8
#define port 2000

const sf::Time requestTimeout = sf::milliseconds(2000); 


enum class CommunicatorStatus
{
	NA,

	CONNECTED,

	REQUESTED,

	FAILED,

	DISCONNECTED
};