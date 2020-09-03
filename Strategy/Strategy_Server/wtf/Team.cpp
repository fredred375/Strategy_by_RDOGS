#include "Team.h"

Team::Team()
	: ID(0), cash(2000000), visitingShop(nullptr), previousVisitingShop(nullptr), movingTime(sf::Time::Zero), movingClock(sf::Clock()), status(TeamStatus::IDLE), capital(0)
{
}

Team::Team(sf::Uint8 ID, Shop* startingPoint)
	: ID(ID), cash(2000000), visitingShop(startingPoint), previousVisitingShop(nullptr), movingTime(sf::Time::Zero), movingClock(sf::Clock()), status(TeamStatus::IDLE), capital(0)
{
}

Team::Team(sf::Uint8 ID, std::vector<Shop*> shopsOwned, TeamStatus status, sf::Int32 cash, Shop* visitingShop, Shop* prevVisitingShop, sf::Time movingTime)
	: ID(ID), shopsOwned(shopsOwned), status(status), cash(cash), visitingShop(visitingShop), previousVisitingShop(prevVisitingShop), movingTime(movingTime), capital(0)
{
}

Team::~Team()
{
}

void Team::updateStatus()
{
	if (this->status == TeamStatus::MOVING)
	{
		if (this->movingClock.getElapsedTime() > this->movingTime) // reached destination
		{
			this->status = TeamStatus::IDLE;
			if (this->visitingShop->getOwnerID() == this->ID)
			{
				this->visitingShop->revisit();
			}
		}
	}
}

void Team::updateCapital(sf::Uint8 capPhase)
{
	this->capital = 0;
	for (auto shop : this->shopsOwned)
	{
		if (!shop->getBankrupt())
		{
			this->capital += shop->getCapital(capPhase);
		}
	}
}

sf::Int32 Team::purchase(Shop* shop, sf::Uint32 cost)
{
	this->cash -= cost;
	this->shopsOwned.push_back(shop);
	return this->cash;
}

sf::Int32 Team::sell(Shop* shop, sf::Uint32 cost)
{
	this->cash += cost;
	this->shopsOwned.erase(std::remove(this->shopsOwned.begin(), this->shopsOwned.end(), shop), this->shopsOwned.end());
	//shop->transaction(this->ID);
	return this->cash;
}

sf::Int32 Team::receiveRevenue(sf::Int32 amount)
{
	this->cash += amount;
	return this->cash;
}

sf::Time Team::move(Shop* destination)
{
	this->previousVisitingShop = this->visitingShop;
	this->visitingShop = destination;

	sf::Time movingTime = sf::seconds(this->previousVisitingShop->getMoveTime(this->visitingShop) * 60.f);

	this->movingTime = movingTime;
	this->movingClock.restart();
	this->status = TeamStatus::MOVING;

	return movingTime;
}

sf::Uint16 Team::getRemainingMoveTime()
{
	if (this->status == TeamStatus::IDLE)
	{
		return 0;
	}
	
	return static_cast<sf::Uint16>(this->movingTime.asSeconds() - this->movingClock.getElapsedTime().asSeconds());
}

sf::Uint32 Team::getRevenue(sf::Uint8 phase, std::vector<sf::Uint32>& byShop)
{
	// Calculates revenue

	sf::Uint32 total = 0;
	std::array<unsigned short, static_cast<int>(ShopTag::numShopTags)> tagsCount = { 0 };

	for (size_t i = 0; i < this->shopsOwned.size(); i++)
	{
		if (!this->shopsOwned[i]->getBankrupt())
		{
			byShop.emplace_back(this->shopsOwned[i]->getRevenue(phase));
			total += this->shopsOwned[i]->getRevenue(phase);

			std::list<ShopTag> tempTags = this->shopsOwned[i]->getTags();

			for (std::list<ShopTag>::iterator it = tempTags.begin(); it != tempTags.end(); ++it)
			{
				tagsCount[static_cast<int>(*it)]++;
			}
		}
		else
		{
			byShop.emplace_back(0);
		}
	}

	for (size_t i = 0; i < static_cast<int>(ShopTag::numShopTags); i++)
	{
		if (tagsCount[i] >= this->bonusThreshold[i])
		{
			total *= this->bonus[i];
		}
	}


	return static_cast<sf::Uint32>(total);
}

void Team::initFromBackup(TeamStatus status, sf::Int32 cash, std::vector<Shop*> shopsOwned, Shop* visitingShop, Shop* prevVisitingShop, sf::Time movingTime)
{
	this->status = status;
	this->cash = cash;
	this->shopsOwned = shopsOwned;
	this->visitingShop = visitingShop;
	this->previousVisitingShop = prevVisitingShop;
	this->movingTime = movingTime;
}


