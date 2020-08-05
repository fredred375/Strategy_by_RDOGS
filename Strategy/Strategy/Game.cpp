#include "Game.h"


void Game::update()
{
	updateEvent();
	dt = clock.restart().asSeconds();
	if (dt > 1.f / 20.f)
	{
		dt = 1.f / 20.f;
	}
	if (!states.empty())
	{
		states.top()->update(dt);
	}
	else
	{
		window.close();
	}
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
				mouseData.oldMousePos = window.mapPixelToCoords(sf::Vector2i(sfEvent.mouseButton.x, sfEvent.mouseButton.y));
				if (!mouseData.leftPressed)
				{
					mouseData.mousePressedPos = sf::Vector2i(sfEvent.mouseButton.x, sfEvent.mouseButton.y);
				}
				if (sfEvent.mouseButton.button == sf::Mouse::Left)
				{
					mouseData.leftPressed = true;
				}
				else
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
			mouseData.mousePos = window.mapPixelToCoords(sf::Vector2i(sfEvent.mouseMove.x, sfEvent.mouseMove.y));
			mouseData.mousePosPixel = sf::Vector2i(sfEvent.mouseMove.x, sfEvent.mouseMove.y);

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
	if (windowSize.x < 800)
	{
		windowSize.x = 800;
	}
	if (windowSize.y < 600)
	{
		windowSize.y = 600;
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

Game::Game() :
	window(sf::VideoMode::getDesktopMode(), "Strategy by RDOGS", sf::Style::Default), dt(0.f)
{
	sf::Image icon;
	icon.loadFromFile("Resources/Textures/RDOGE.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);

	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect("127.0.0.1 ", 53000);
	if (status != sf::Socket::Done)
	{
		printf("connection failed\n");
	}
	else
	{
		printf("connection successed!\n");
	}



	states.push(new MapState(&window, &states, &mouseData));
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
