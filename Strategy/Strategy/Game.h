#pragma once
#include "MapState.h"
#include "Communicator.h"
class Game
{
private:
	sf::RenderWindow window;
	sf::Event sfEvent;

	MouseData mouseData;
	Communicator* communicator;

	sf::Clock clock;
	float dt;

	

	sf::Clock clock;
	float dt;

	std::stack<State*> states;

	void update();
	void updateEvent();
	void resizeView();
	void render();
public:
	Game(sf::Uint8 teamID, std::string ip);
	~Game();
	void run();
};

