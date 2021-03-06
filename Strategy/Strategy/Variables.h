#pragma once

#include <iostream>
#include <utility>
#include <array>
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

#define numTeams 9
#define port 2000

//sf::Uint8 teamIDGlobal = 0;

const sf::Time requestTimeout = sf::milliseconds(5000); 
const sf::Time nonPurchasableTime = sf::seconds(120);

enum class CommunicatorStatus
{
	NA,

	CONNECTED,

	REQUESTED,

	FAILED,

	DISCONNECTED
};