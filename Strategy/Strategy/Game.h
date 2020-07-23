#pragma once
#include "MapState.h"
class Game
{
private:
	sf::RenderWindow window;
	sf::Event sfEvent;

	MouseData mouseData;

	std::stack<State*> states;

	void update();
	void updateEvent();
	void resizeView();
	void render();
public:
	Game();
	~Game();
	void run();
};

