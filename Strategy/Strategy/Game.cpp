#include "Game.h"


void Game::update()
{
	updateEvent();
	dt = clock.restart().asSeconds();
	if (dt > 1.f / constants::FRAMERATE_LOW)
	{
		dt = 1.f / constants::FRAMERATE_LOW;
	}
	if (!states.empty())
	{
		states.top()->update(dt);
	}
	else
	{
		window.close();
	}
	this->communicator->update();
}

void Game::updateEvent()
{
	mouseData.reset();

	while (window.pollEvent(sfEvent))
	{
		switch (sfEvent.type)
		{
		default:
			break;
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::Resized:
			resizeView();
			break;
		case sf::Event::MouseButtonPressed:
			if (sfEvent.mouseButton.button == sf::Mouse::Left || sfEvent.mouseButton.button == sf::Mouse::Right)
			{
				mouseData.oldMousePosPixel = sf::Vector2i(sfEvent.mouseButton.x, sfEvent.mouseButton.y);
				mouseData.oldMousePos = window.mapPixelToCoords(mouseData.oldMousePosPixel);
				if (!mouseData.leftPressed)
				{
					mouseData.mousePressedPos = sf::Vector2i(sfEvent.mouseButton.x, sfEvent.mouseButton.y);
				}
				if (sfEvent.mouseButton.button == sf::Mouse::Left)
				{
					mouseData.leftPressed = true;
				}
				else if(sfEvent.mouseButton.button == sf::Mouse::Right)
				{
					mouseData.rightPressed = true;
				}
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (sfEvent.mouseButton.button == sf::Mouse::Left)
			{
				mouseData.leftPressed = false;
				mouseData.leftClicked = true;
			}
			else if (sfEvent.mouseButton.button == sf::Mouse::Right)
			{
				mouseData.rightPressed = false;
				mouseData.rightClicked = true;
			}
			break;
		case sf::Event::MouseMoved:
			mouseData.moving = true;
			mouseData.mousePosPixel = sf::Vector2i(sfEvent.mouseMove.x, sfEvent.mouseMove.y);
			mouseData.mousePos = window.mapPixelToCoords(mouseData.mousePosPixel);

			break;
		case sf::Event::MouseWheelMoved:
			mouseData.wheelTicks = sfEvent.mouseWheel.delta;
			break;
		}
	}
}

void Game::resizeView()
{
	sf::Vector2u windowSize = window.getSize();
	if (windowSize.x < constants::WINDOW_WIDTH_SMALL)
	{
		windowSize.x = constants::WINDOW_WIDTH_SMALL;
	}
	if (windowSize.y < constants::WINDOW_HEIGHT_SMALL)
	{
		windowSize.y = constants::WINDOW_HEIGHT_SMALL;
	}
	window.setSize(windowSize);
	if (!states.empty())
	{
		float aspectRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
		states.top()->resizeView(aspectRatio);
	}
}

void Game::render()
{
	window.clear();
	if (!states.empty())
	{
		states.top()->render();
	}
	window.display();
}

Game::Game(sf::Uint8 teamID, std::string ip)
	:
	window(sf::VideoMode::getFullscreenModes().front(), "Strategy by RDOGS", sf::Style::Close | sf::Style::Titlebar), dt(0.f)
{

	sf::Image icon;
	icon.loadFromFile("Resources/Textures/RDOGE.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	this->communicator = new Communicator(ip, teamID);
	states.push(new MapState(&window, &states, &mouseData, teamID, communicator));

}

Game::~Game()
{
	while (!states.empty())
	{
		delete states.top();
		states.pop();
	}
}

void Game::run()
{
	while (window.isOpen())
	{
		update();
		render();
	}
}
