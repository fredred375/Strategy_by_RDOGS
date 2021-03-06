#pragma once

#include "Variables.h"

struct MouseData
{
	sf::Vector2f mousePos;
	sf::Vector2f oldMousePos;
	int wheelTicks;

	bool leftPressed;
	bool leftClicked; //this bool only triggers when and only when a full click is done. In other words, a press and a release.
	bool moving;

	MouseData() :
		wheelTicks(0),
		leftPressed(false),
		leftClicked(false),
		moving(false)
	{}

	void reset() //called every loop, reseting ephemeral data
	{
		wheelTicks = 0;
		leftClicked = false;
		moving = false;
	}
};
