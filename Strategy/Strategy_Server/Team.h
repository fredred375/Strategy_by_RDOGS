#pragma once

#include "Variables.h"
#include "Shop.h"

enum class TeamStatus
{
	IDLE,

	MOVING,
};


class Team
{
private:

	// Properties

	sf::Uint8 ID;

	std::vector<Shop*> shopsOwned;


	// Status

	TeamStatus status;

	sf::Int32 cash;

	sf::Int32 capital;

	Shop* visitingShop, * previousVisitingShop;

	sf::Time movingTime;

	sf::Clock movingClock;

	int numShopsBankrupted = 0;

	std::array<sf::Uint16, static_cast<int>(ShopTag::numShopTags)> numTagsCollected;


	// Data

	const std::array<unsigned short, static_cast<int>(ShopTag::numShopTags)> bonusThreshold = { 5, 4, 3, 3, 2, 2, 3, 2, 3, 3, 1, 1 };

	const std::array<double, static_cast<int>(ShopTag::numShopTags)> bonus = { 1.3f, 1.2f, 1.1f, 1.1f, 1.3f, 1.3f, 1.4f, 1.3f, 1.4f, 1.4f, 1.3f, 1.2f };



public:

	
	// Constructors / Destructors

	Team();

	Team(sf::Uint8 ID, Shop* startingPoint);

	Team(sf::Uint8 ID, std::vector<Shop*> shopsOwned, TeamStatus status, sf::Int32 cash, Shop* visitingShop, Shop* prevVisitingShop, sf::Time movingTime); // from backup

	~Team();


	// Methods

	void updateStatus();

	void updateCapital(sf::Uint8 capPhase);

	sf::Int32 purchase(Shop* shop, sf::Uint32 cost, std::vector<sf::Uint16>& bonusActivated); // returns remaining cash

	sf::Int32 sell(Shop* shop, sf::Uint32 cost, std::vector<sf::Uint16>& bonusDeactivated); // returns remaining cash

	sf::Int32 receiveRevenue(sf::Int32 amount);

	sf::Time move(Shop* destination); // returns moving time


	// Queries

	sf::Int32 getCash() { return this->cash; };

	sf::Int32 getCapital() { return this->capital; };

	TeamStatus getStatus() { return this->status; };

	sf::Uint16 getNumShopsOwned() { return this->shopsOwned.size(); };

	std::vector<Shop*>& getShopsOwned() { return this->shopsOwned; };

	Shop* getPrevPosition() { return this->previousVisitingShop; };

	Shop* getPosition() { return this->visitingShop; };

	sf::Uint16 getRemainingMoveTime();

	sf::Uint32 getRevenue(sf::Uint8 phase, std::vector<sf::Uint32>& byShop);

	void initFromBackup(TeamStatus status, sf::Int32 cash, std::vector<Shop*> shopsOwned, Shop* visitingShop, Shop* prevVisitingShop, sf::Time movingTime);

	int getNumShopsBankrupted() { return this->numShopsBankrupted; };

	void shopBankrupted(Shop* shop, std::vector<sf::Uint16>& bonusDeactivated);

	double getBonus(sf::Uint16 tag) { return this->bonus.at(tag); };
};

