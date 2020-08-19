#pragma once
#include "Point.h"
#include "Communicator.h"

class State
{
protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, sf::Texture> textures;
	sf::View view;
	MouseData* mouseData;
	Communicator* communicator;
	virtual void updateMouseInput() = 0;
public:
	State(sf::RenderWindow* window, std::stack<State*>* states, MouseData* mouseData, Communicator* communicator);
	virtual ~State();
	virtual void update() = 0;
	virtual void render(sf::RenderWindow* window = nullptr) = 0;
	void resizeView(float aspectRatio);
};

