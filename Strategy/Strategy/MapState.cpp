#include "MapState.h"

void MapState::initPoints()
{
	font.loadFromFile("Resources/Fonts/NotoSansCJKtc-Regular.otf");
	points["總圖"] = Point(3074.63f, 1709.87f, L"總圖", 7000);
	points["運動場"] = Point(2170.36f, 1226.96f, L"運動場", 5000);
	points["管圖"] = Point(2407.59f, 2370.13f, L"管圖", 2000);
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

void MapState::initUI()
{
	popUpWindow = new PopUpWindow(&player, &font);
	playerUI = new PlayerUI(&player, &font);
	pointHoverUI = new PointHoverUI(&font);
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
		std::cout << mouseData->mousePos.x << "f, " << mouseData->mousePos.y << "f" << std::endl;
	}
	for (auto it = points.begin(); it != points.end(); it++)
	{
		if (it->second.clicked(mouseData->mousePos.x, mouseData->mousePos.y))
		{
			if (mouseData->leftClicked)
			{
				popUpWindow->activated = true;
				popUpWindow->setPoint(&it->second);
				popUpWindow->initDraw(view);
				pointHoverUI->activated = false;
			}
			else if (mouseData->rightClicked)
			{
				player.moveToPoint(&it->second);
			}
			else
			{
				if (!pointHoverUI->activated)
				{
					pointHoverUI->activated = true;
					pointHoverUI->setPoint(&it->second);
					pointHoverUI->initDraw(view);
				}
			}
			return;
		}
	}
	if (pointHoverUI->activated)
	{
		pointHoverUI->activated = false;
	}
}

MapState::MapState(sf::RenderWindow* window, std::stack<State*>* states, MouseData* mouseData) :
	State(window, states, mouseData), player(1), mapViewport(0.25f, 0.f, 0.75f, 1.f), playerUI(nullptr),
	UIViewport(0.f, 0.f, 0.25f, 1.f)
{
	initTextures();
	initPoints();
	initMap();
	initUI();
	view = sf::View(sf::Vector2f(2000.f, 2000.f), sf::Vector2f(1000.f, 1000.f));
	view.setViewport(mapViewport);
	UIView = sf::View(sf::Vector2f(-240.f, 500.f), sf::Vector2f(480.f, 1000.f));
	UIView.setViewport(UIViewport);
}

MapState::~MapState()
{
	delete popUpWindow;
}

void MapState::update(const float& dt)
{
	playerUI->update(mouseData);
	if (!popUpWindow->activated)
	{
		updateMouseInput();
		checkBoundaries();
	}
	else
	{
		popUpWindow->update(mouseData);
	}
	player.update(dt);
}

void MapState::updateMouseInput()
{
	//zoom in & out
	if (mouseData->wheelTicks != 0)
	{
		if (mouseData->wheelTicks > 0)
		{
			if (view.getSize().x > 1920.f)
			{
				view.setSize(view.getSize() * 0.95f);
			}
			//zoom in
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
		if (mouseData->mousePressedPos.x > window->getSize().x * 0.25f)
		{
			const sf::Vector2f deltaPos = mouseData->oldMousePos - mouseData->mousePos;
			view.setCenter(view.getCenter() + deltaPos);
		}
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
	window->setView(UIView);
	playerUI->draw(window);
	window->setView(view);
	window->draw(background);
	for (auto it = points.begin(); it != points.end(); it++)
	{
		it->second.draw(window);
	}
	player.draw(window);
	if (pointHoverUI->activated)
	{
		pointHoverUI->draw(window);
	}
	if (popUpWindow->activated)
	{
		popUpWindow->draw(window);
	}
}

void MapState::resizeView(float aspectRatio)
{
	State::resizeView(aspectRatio * 0.75f);
	if (popUpWindow->activated)
	{
		popUpWindow->initDraw(view);
	}
}
