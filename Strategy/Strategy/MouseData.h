#pragma once
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Network.hpp"
#include <Windows.h>
#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <cmath>
struct MouseData
{
	sf::Vector2f mousePos;
	sf::Vector2f oldMousePos;
	sf::Vector2i mousePosPixel;
	sf::Vector2i mousePressedPos;
	int wheelTicks;

	bool leftPressed;
	bool leftClicked; //this bool only triggers when and only when a full click is done. In other words, a press and a release.
	bool rightPressed;
	bool rightClicked;
	bool moving;

	MouseData() :
		wheelTicks(0),
		leftPressed(false),
		leftClicked(false),
		rightPressed(false),
		rightClicked(false),
		moving(false)
	{}

	void reset() //called every loop, reseting ephemeral data
	{
		wheelTicks = 0;
		leftClicked = false;
		rightClicked = false;
		moving = false;
	}
};

