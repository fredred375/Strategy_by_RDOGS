#pragma once

#include "Communicator.h"
#include "MouseData.h"

class Server
{
private:

	// components

	sf::RenderWindow window;

	sf::Event sfEvent;

	MouseData mouseData;

	Communicator* communicator;

	std::map<std::string, sf::Texture> textures;

	sf::View view;


	// methods

	void update();
	
	void updateEvent();

	void resizeView();

	void render();


public:

	// constructors/destructors
	
	Server();
	~Server();


	// methods

	void run();

};

