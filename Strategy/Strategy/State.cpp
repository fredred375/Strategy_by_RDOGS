#include "State.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states, MouseData* mouseData) :
	window(window), states(states), mouseData(mouseData)
{
}

State::~State()
{
}

void State::resizeView(float aspectRatio)
{
	view.setSize(view.getSize().y * aspectRatio, view.getSize().y);
}

