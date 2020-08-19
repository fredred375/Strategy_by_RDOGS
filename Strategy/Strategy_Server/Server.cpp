#include "Server.h"

void Server::update()
{
	this->updateEvent();
	
	this->communicator->update();
}

void Server::updateEvent()
{
	this->mouseData.reset();

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
			if (sfEvent.mouseButton.button == sf::Mouse::Left)
			{
				mouseData.oldMousePos = window.mapPixelToCoords(sf::Vector2i(sfEvent.mouseButton.x, sfEvent.mouseButton.y));
				mouseData.leftPressed = true;
			}
			break;

		case sf::Event::MouseButtonReleased:
			if (sfEvent.mouseButton.button == sf::Mouse::Left)
			{
				mouseData.leftPressed = false;
				mouseData.leftClicked = true;
			}
			break;

		case sf::Event::MouseMoved:
			mouseData.moving = true;
			mouseData.mousePos = window.mapPixelToCoords(sf::Vector2i(sfEvent.mouseMove.x, sfEvent.mouseMove.y));
			break;

		case sf::Event::MouseWheelMoved:
			mouseData.wheelTicks = sfEvent.mouseWheel.delta;
			break;
		}
	}
}

void Server::resizeView()
{
	float aspectRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
	view.setSize(view.getSize().y * aspectRatio, view.getSize().y);
}

void Server::render()
{
	this->window.clear();

	// TODO: render stuff here

	this->window.display();
}

Server::Server() :
	window(sf::VideoMode::getDesktopMode(), "Strategy Server by RDOGS", sf::Style::Default)
{
	this->communicator = new Communicator;
}

Server::~Server()
{
}

void Server::run()
{
	while (window.isOpen())
	{
		this->update();
		this->render();
	}
}
