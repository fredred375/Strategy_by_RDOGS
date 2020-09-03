#pragma once

#include "Communicator.h"
#include "GameEvent.h"
#include "MouseData.h"
#include "Shop.h"
#include "Team.h"

class Server
{
private:

	// Components

	Communicator* communicator;


	// Status

	GameMode mode;

	sf::Uint8 capPhase;

	sf::Uint8 revPhase;

	sf::Clock gameTime;

	sf::Clock backupTime;

	sf::Time startGameTime;


	// Data

	std::array<Shop*, numShops + 1> shops;

	std::array<Team*, numTeams + 1> teams;

	std::queue<std::vector<Shop*>> bankruptingShops;

	std::queue<GameEvent> events;

	bool startFromBackup;


	// Methods

	void initGameMode();

	void initData();

	void initEvents();

	void checkInitClient();

	void update();

	void handleRequests();

	void updateEvents();

	void checkBackup();

	void print(std::string cat, std::string message);


public:

	// constructors/destructors
	
	Server();

	~Server();


	// methods

	void run();

};

