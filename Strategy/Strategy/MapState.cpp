#include "MapState.h"

void MapState::initPoints()
{
	font.loadFromFile("Resources/Fonts/NotoSansTC-Regular.otf");
	points["總圖"] = Point(3074.63f, 1709.87f, L"總圖", &font);
	points["運動場"] = Point(2170.36, 1226.96, L"運動場", &font);
}

void MapState::initTextures()
{
	textures["background"].loadFromFile("Resources/Textures/map.jpg");
}

void MapState::initMap()
{
	background.setTexture(&textures["background"]);
	background.setSize(sf::Vector2f(textures["background"].getSize()));
}

void MapState::checkBoundaries()
{
	sf::Vector2f viewCenter = view.getCenter();
	float viewLeft = viewCenter.x - (view.getSize().x / 2.f);
	float viewRight = viewCenter.x + (view.getSize().x / 2.f);
	float viewTop = viewCenter.y - (view.getSize().y / 2.f);
	float viewDown = viewCenter.y + (view.getSize().y / 2.f);
	float backgroundLeft = background.getPosition().x;
	float backgroundRight = background.getPosition().x + background.getSize().x;
	float backgroundTop = background.getPosition().y;
	float backgroundDown = background.getPosition().y + background.getSize().y;
	float viewAdjustX = view.getCenter().x;
	float viewAdjustY = view.getCenter().y;
	if (view.getSize().x > background.getSize().x)
	{
		view.setSize(background.getSize().x, view.getSize().y / view.getSize().x * background.getSize().x);
	}
	else if (view.getSize().y > background.getSize().y)
	{
		view.setSize(view.getSize().x / view.getSize().y * background.getSize().y, background.getSize().y);
	}
	if (viewLeft < backgroundLeft)
	{
		viewAdjustX = backgroundLeft + (view.getSize().x / 2);
	}
	else if (viewRight > backgroundRight)
	{
		viewAdjustX = backgroundRight - (view.getSize().x / 2);
	}
	if (viewTop < backgroundTop)
	{
		viewAdjustY = backgroundTop + (view.getSize().y / 2);
	}
	else if (viewDown > backgroundDown)
	{
		viewAdjustY = backgroundDown - (view.getSize().y / 2);
	}
	view.setCenter(viewAdjustX, viewAdjustY);
}

void MapState::checkPointsClicked()
{
	if (mouseData->leftClicked)
	{
		std::cout << mouseData->mousePos.x << ", " << mouseData->mousePos.y << std::endl;
		for (auto it = points.begin(); it != points.end(); it++)
		{
			if (it->second.clicked(mouseData->mousePos.x, mouseData->mousePos.y))
			{
				std::cout << it->first << " is clicked" << std::endl;
				popUpKey = it->first;
				popUpWindowActivated = true;
				it->second.popUp(window);
			}
		}
	}
}

MapState::MapState(sf::RenderWindow* window, std::stack<State*>* states, MouseData* mouseData) :
	State(window, states, mouseData), popUpWindowActivated(false)
{
	initTextures();
	initPoints();
	initMap();
	view = sf::View(sf::Vector2f(2000.f, 2000.f), sf::Vector2f(1000.f, 1000.f));
}

MapState::~MapState()
{
}

void MapState::update()
{
	if (!popUpWindowActivated)
	{
		updateMouseInput();
		checkBoundaries();
	}
	else
	{
		points[popUpKey].update(mouseData, popUpWindowActivated);
	}
}

void MapState::updateMouseInput()
{
	//zoom in & out
	if (mouseData->wheelTicks != 0)
	{
		if (mouseData->wheelTicks > 0)
		{
			//zoom in
			view.setSize(view.getSize() * 0.95f);
		}
		else
		{
			//zoom out
			view.setSize(view.getSize() * 1.05f);
		}
	}

	//view dragging
	if (mouseData->leftPressed && mouseData->moving)
	{
		const sf::Vector2f deltaPos = mouseData->oldMousePos - mouseData->mousePos;
		view.setCenter(view.getCenter() + deltaPos);
	}

	//point clicking
	checkPointsClicked();
}

void MapState::render(sf::RenderWindow* window)
{
	if (!window)
	{
		window = this->window;
	}
	window->setView(view);
	window->draw(background);
	for (auto it = points.begin(); it != points.end(); it++)
	{
		it->second.draw(window);
	}
	if (popUpWindowActivated)
	{
		points[popUpKey].draw(window);
	}
}
