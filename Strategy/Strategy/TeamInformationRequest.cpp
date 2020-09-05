#include "TeamInformationRequest.h"

TeamInformationRequest::TeamInformationRequest(sf::Uint32 requestID, sf::Uint8 teamID, Player* team) :
	team(team)
{
	PacketProperties properties(requestID, PacketType::REQUEST, SubType::REQUEST_TEAM_INFORMATION);

	this->sendProperties = properties;

	this->sendPacket << properties << teamID;
}

TeamInformationRequest::~TeamInformationRequest()
{
	printf("team info request terminated: ");

	//*(this->communicatorStatus) = CommunicatorStatus::FAILED;

	Request::~Request();
}

void TeamInformationRequest::update()
{
	Request::update();
	if (this->status == RequestStatus::RESPONDED)
	{
		sf::Uint8 teamID;
		sf::Int32 cash;
		sf::Int32 capital;
		sf::Uint16 numShopsOwned;
		std::vector<sf::Uint8> ownedShopsID;
		sf::Uint8 visitingShopID, tempShopID;
	
	
		switch (receiveProperties.requestValidity)
		{
		case RequestValidity::VALID:
			this->receivePacket >> teamID >> cash >> capital >> numShopsOwned;
			for (size_t i = 0; i < numShopsOwned; i++)
			{
				receivePacket >> tempShopID;
				ownedShopsID.emplace_back(tempShopID);
			}
			this->receivePacket >> visitingShopID;
			team->setCash(cash);
			team->setCap(capital);
			team->setProperties(ownedShopsID);
			team->setDest(visitingShopID);
			break;
		default:
			break;
		}

		team->updateTeamUI = true;
	}

	else if (this->status == RequestStatus::TIMEOUT)
	{
		team->setCash(-1);
		team->setCap(-1);
		team->setDest(-1);
	}
}
