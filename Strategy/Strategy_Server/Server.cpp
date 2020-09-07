#include "Server.h"

sf::Packet& operator <<(sf::Packet& packet, const PacketProperties& t);

sf::Packet& operator >>(sf::Packet& packet, PacketProperties& t);


std::vector<std::string> _csv(std::string s)
{
	std::vector<std::string> arr;
	std::istringstream delim(s);
	std::string token;
	int c = 0;
	while (getline(delim, token, ','))        
	{
		arr.push_back(token);                
		c++;                                           
	}
	return  arr;
}

void Server::initGameMode()
{
	char choice;


	printf("d for debug, t for testing, r for release:");

	std::cin >> choice;

	switch (choice)
	{
	case 'd':
		this->mode = GameMode::Debug;
		break;

	case 't':
		this->mode = GameMode::Test;
		printf("start from backup? y / n");

		std::cin >> choice;

		this->startFromBackup = (choice == 'y');
		break;

	case 'r':
		this->mode = GameMode::Release;
		printf("start from backup? y / n");

		std::cin >> choice;

		this->startFromBackup = (choice == 'y');
		break;

	default:
		this->mode = GameMode::Release;
		printf("start from backup? y / n");

		std::cin >> choice;

		this->startFromBackup = (choice == 'y');
		break;
	}

	
}

void Server::initData()
{
	std::array<std::ifstream*, numCapPhases> ifsCap;
	std::array<std::ifstream*, numRevPhases> ifsRev;
	std::ifstream* ifsMoveTime;

	std::string path = "Spreadsheets\\";
	std::string line;
	std::vector<std::string> tokens;

	std::array<sf::Uint32, numCapPhases> caps, prices;
	std::array<sf::Uint32, numRevPhases> revs;
	std::array<double, numShops + 1> moveTimes;

	for (size_t j = 0; j < numCapPhases; j++)
	{
		std::string fileCap = "cap" + std::to_string(j + 1) + ".csv";
		

		ifsCap[j] = new std::ifstream(path + fileCap, std::ios::in);
		

		if (!*ifsCap[j])
		{
			std::cout << "Can't open file \"" << path + fileCap << "\"...\n";
			exit(4);
		}

		// discard index row
		std::getline(*(ifsCap[j]), line);
		
	}

	for (size_t j = 0; j < numRevPhases; j++)
	{
		std::string fileRev = "rev" + std::to_string(j + 1) + ".csv";

		ifsRev[j] = new std::ifstream(path + fileRev, std::ios::in);

		if (!*ifsRev[j])
		{
			std::cout << "Can't open file \"" << path + fileRev << "\"...\n";
			exit(4);
		}

		// discard index row
		std::getline(*(ifsRev[j]), line);
	}

		

	ifsMoveTime = new std::ifstream(path + "move_time.csv", std::ios::in);
	if (!*ifsMoveTime)
	{
		std::cout << "Can't open file \"" << path + "move_time.csv" << "\"...\n";
		//exit(4);
	}

	this->print("SRVR", "Files opened successfully!");

	std::getline(*ifsMoveTime, line);

	for (size_t i = 1; i <= numShops; i++)
	{
		for (size_t j = 0; j < numCapPhases; j++)
		{
			std::getline(*(ifsCap[j]), line);

			tokens = _csv(line);
			caps[j] = atoi(tokens[1].c_str());
			prices[j] = atoi(tokens[2].c_str());
		}

		for (size_t j = 0; j < numRevPhases; j++)
		{
			std::getline(*(ifsRev[j]), line);

			tokens = _csv(line);
			revs[j] = atoi(tokens[1].c_str());
		}

		std::getline(*ifsMoveTime, line);

		tokens = _csv(line);

		for (size_t j = 1; j <= numShops; j++)
		{
			moveTimes[j] = atof(tokens[j].c_str());
		}

		shops[i] = new Shop(i, caps, prices, revs, moveTimes);
	}

	this->bankruptingShops.push({ shops[25], shops[47] });
	this->bankruptingShops.push({ shops[13], shops[23], shops[52], shops[73] });
	this->bankruptingShops.push({ shops[30], shops[50], shops[72] });
	this->bankruptingShops.push({ shops[14], shops[20], shops[33], shops[36], shops[41] });
	this->bankruptingShops.push({ shops[63], shops[65] });
	this->bankruptingShops.push({ shops[4], shops[58] });

	std::vector<std::vector<sf::Uint8>> tagsShopIndex = 
	{
		{ 13, 14, 15, 21, 22, 24, 25, 26, 28 },
		{ 12, 16, 38, 39, 40, 41, 52         },
		{ 48, 50, 53, 54, 55                 },
		{ 60, 61, 63, 69, 71, 72, 73         },
		{  8, 29, 31, 59                     },
		{ 34, 75                             },
		{ 30, 44, 45                         },
		{ 16, 61                             },
		{  5, 12, 17, 27, 71, 72             },
		{  2, 21, 24, 60, 64                 },
		{ 67                                 },
		{ 68                                 }
	};

	for (size_t i = 0; i < tagsShopIndex.size(); i++)
	{
		for (size_t j = 0; j < tagsShopIndex[i].size(); j++)
		{
			this->shops[tagsShopIndex[i][j]]->addTag(static_cast<ShopTag>(i));
		}
	}

	std::vector<sf::Uint8> startingPointIndices = { 0, 61, 71, 69, 59, 73, 68, 60, 63 };

	for (size_t i = 1; i < teams.size(); i++)
	{
		teams[i] = new Team(i, shops[startingPointIndices[i]]);
	}

	if (this->startFromBackup)
	{
		std::string backupFolderPath = "Backup\\";

		for (size_t i = 1; i <= numTeams; i++)
		{
			Team* team = this->teams[i];

			std::string buffer;
			std::vector<std::string> tokens;

			std::ifstream file(backupFolderPath + std::to_string(i) + ".txt");


			// backup format
			
			/*
			--------------
			team 1
			status:
			0
			cash:
			2000000
			visiting shop:
			'
			prevVisitingShop:
			0
			shops owned:

			moving time:
			0
			--------------
			*/
			
			
			Shop* visitingShop, * prevVisitingShop;
			std::vector<Shop*> shopsOwned;
			sf::Time movingTime;

			std::getline(file, buffer);
			std::getline(file, buffer);
			std::getline(file, buffer);
			TeamStatus status = static_cast<TeamStatus>(atoi(buffer.c_str()));

			std::getline(file, buffer);
			std::getline(file, buffer);
			sf::Uint32 cash = atoi(buffer.c_str());

			std::getline(file, buffer);
			std::getline(file, buffer);
			visitingShop = this->shops.at(atoi(buffer.c_str()));

			std::getline(file, buffer);
			std::getline(file, buffer);
			prevVisitingShop = this->shops.at(atoi(buffer.c_str()));
			
			std::getline(file, buffer);
			std::getline(file, buffer);
			tokens = _csv(buffer);
			for (auto token : tokens)
			{
				shopsOwned.push_back(this->shops.at(atoi(buffer.c_str())));
			}

			std::getline(file, buffer);
			std::getline(file, buffer);
			movingTime = sf::seconds(atoi(buffer.c_str()));

			team->initFromBackup(status, cash, shopsOwned, visitingShop, prevVisitingShop, movingTime);
		}

		for (auto shop : shops)
		{
			if (shop == nullptr) continue;

			std::string buffer;

			std::ifstream file(backupFolderPath + "shop" + std::to_string(static_cast<int>(shop->getID())) + ".txt");

			// foramt
			/*
			--------------------
			shop 4
			owner:
			0
			bankrupted:
			0
			transcation times:
			0
			--------------------
			*/

			std::getline(file, buffer);
			std::getline(file, buffer);
			std::getline(file, buffer);


		}
	}
}

void Server::initEvents()
{
	int startingTime = 1;
	if (this->mode != GameMode::Debug)
	{
		printf("Game start in (secs):");
		std::cin >> startingTime;
	}

	this->events.emplace(startingTime / 60, startingTime % 60, GameEventType::START);

	switch (this->mode)
	{
	case GameMode::Debug:
	{
		this->events.emplace(0, 0, GameEventType::SYNCHRONIZE);
		this->events.emplace(0, 35, GameEventType::REVENUE);
		this->events.emplace(1, 30, GameEventType::BANKRUPT);
		this->events.emplace(2, 30, GameEventType::NEXT_CAP_PHASE);
		this->events.emplace(3, 0, GameEventType::NEXT_REV_PHASE);
		this->events.emplace(3, 30, GameEventType::REVENUE);
		this->events.emplace(3, 30, GameEventType::FINISH);
	}
	break;

	case GameMode::Test:
	{
		this->events.emplace(0, 0, GameEventType::SYNCHRONIZE);
		this->events.emplace(1, 0, GameEventType::SYNCHRONIZE);
		this->events.emplace(2, 0, GameEventType::SYNCHRONIZE);
		this->events.emplace(3, 0, GameEventType::SYNCHRONIZE);
		this->events.emplace(4, 0, GameEventType::SYNCHRONIZE);
		this->events.emplace(5, 0, GameEventType::SYNCHRONIZE);

	}
	break;

	case GameMode::Release:
	{
		this->events.emplace(0, 0, GameEventType::SYNCHRONIZE);
		//this->events.emplace(1, 0, GameEventType::REVENUE);
		this->events.emplace(1, 0, GameEventType::SYNCHRONIZE);
		this->events.emplace(2, 0, GameEventType::SYNCHRONIZE);

		this->events.emplace(2, 0, GameEventType::PRINT_LEADER);
		this->events.emplace(3, 0, GameEventType::SYNCHRONIZE);
		this->events.emplace(4, 0, GameEventType::SYNCHRONIZE);
		this->events.emplace(5, 0, GameEventType::SYNCHRONIZE);
		this->events.emplace(5, 0, GameEventType::BANKRUPT);
		this->events.emplace(8, 0, GameEventType::REVENUE);
		this->events.emplace(10, 0, GameEventType::NEXT_REV_PHASE);
		this->events.emplace(10, 0, GameEventType::PRINT_LEADER);
		this->events.emplace(15, 0, GameEventType::BANKRUPT);
		this->events.emplace(15, 0, GameEventType::SYNCHRONIZE);
		this->events.emplace(18, 0, GameEventType::REVENUE);
		this->events.emplace(20, 0, GameEventType::NEXT_CAP_PHASE);
		this->events.emplace(20, 0, GameEventType::PRINT_LEADER);
		this->events.emplace(28, 0, GameEventType::REVENUE);
		this->events.emplace(30, 0, GameEventType::SYNCHRONIZE);
		this->events.emplace(30, 0, GameEventType::PRINT_LEADER);
		this->events.emplace(35, 0, GameEventType::BANKRUPT);
		this->events.emplace(40, 0, GameEventType::REVENUE);
		this->events.emplace(40, 0, GameEventType::NEXT_REV_PHASE);
		this->events.emplace(40, 0, GameEventType::PRINT_LEADER);
		this->events.emplace(45, 0, GameEventType::NEXT_CAP_PHASE);
		this->events.emplace(45, 0, GameEventType::SYNCHRONIZE);
		this->events.emplace(50, 0, GameEventType::REVENUE);
		this->events.emplace(50, 0, GameEventType::PRINT_LEADER);
		this->events.emplace(55, 0, GameEventType::BANKRUPT);
		this->events.emplace(60, 0, GameEventType::REVENUE);
		this->events.emplace(60, 0, GameEventType::NEXT_REV_PHASE);
		this->events.emplace(60, 0, GameEventType::PRINT_LEADER);
		this->events.emplace(60, 0, GameEventType::SYNCHRONIZE);
		this->events.emplace(65, 0, GameEventType::NEXT_CAP_PHASE);
		this->events.emplace(70, 0, GameEventType::REVENUE);
		this->events.emplace(70, 0, GameEventType::PRINT_LEADER);
		this->events.emplace(75, 0, GameEventType::BANKRUPT);
		this->events.emplace(75, 0, GameEventType::SYNCHRONIZE);
		this->events.emplace(80, 0, GameEventType::REVENUE);
		this->events.emplace(80, 0, GameEventType::NEXT_REV_PHASE);
		this->events.emplace(80, 0, GameEventType::PRINT_LEADER);
		this->events.emplace(85, 0, GameEventType::BANKRUPT);
		this->events.emplace(90, 0, GameEventType::REVENUE);
		this->events.emplace(90, 0, GameEventType::PRINT_LEADER);
	}
	break;

	default:
		break;
	}

	
}

void Server::checkInitClient()
{
	for (size_t i = 1; i <= numTeams; i++)
	{
		if (this->communicator->clientUninitialized[i])
		{
			this->print("SEND", "Team " + std::to_string(i) + " is uninitialized, initailizing...");

			this->communicator->clientUninitialized[i] = false;
			Team* team = this->teams[i];
			sf::Uint16 numShopsOwned = team->getNumShopsOwned();
			sf::Packet sendPacket;
			sendPacket
				<< PacketProperties(this->communicator->getCurrentSendID(), PacketType::SEND, SubType::SEND_PLAYER_INFORMATION)
				<< team->getCash()
				<< team->getCapital()
				<< numShopsOwned;
			for (size_t j = 0; j < numShopsOwned; j++)
			{
				sendPacket << team->getShopsOwned()[j]->getID();
			}

			sendPacket
				<< team->getPosition()
				<< team->getPrevPosition()
				<< (team->getStatus() == TeamStatus::MOVING)
				<< team->getRemainingMoveTime();

			this->communicator->send(i, sendPacket);

			for (size_t j = 1; (j <= numTeams /*&& j != i*/); j++)
			{
				sf::Packet sendPacket_2;
				if (this->teams[j]->getStatus() == TeamStatus::IDLE)
				{
					sendPacket_2
						<< PacketProperties(this->communicator->getCurrentSendID(), PacketType::SEND, SubType::SEND_MOVE)
						<< static_cast<sf::Uint8>(j)
						<< (this->teams[j] == nullptr ? sf::Uint8(0) : this->teams[j]->getPosition()->getID())
						<< this->teams[j]->getPosition()->getID()
						<< 0;
				}
				else
				{
					sendPacket_2
						<< PacketProperties(this->communicator->getCurrentSendID(), PacketType::SEND, SubType::SEND_MOVE)
						<< static_cast<sf::Uint8>(j)
						<< this->teams[j]->getPrevPosition()->getID()
						<< this->teams[j]->getPosition()->getID()
						<< this->teams[j]->getRemainingMoveTime();
				}

				this->communicator->send(i, sendPacket_2);
			}
		}
	}
}

void Server::update()
{
	this->communicator->update();

	for (size_t i = 1; i < this->teams.size(); i++)
	{
		this->teams[i]->updateStatus();
	}

	this->checkInitClient();

	this->checkBackup();

	this->handleRequests();

	this->updateEvents();
}

void Server::handleRequests()
{
	for (size_t i = 1; i <= numTeams; i++)
	{
		if (this->communicator->newRequest(i))
		{
			sf::Packet receivePacket;
			std::vector<sf::Packet> sendPackets, broadcastPackets;
			std::vector<sf::Uint8> sendTeams;

			//bool broadcast = false;

			sendPackets.emplace_back();
			sendTeams.emplace_back(i);

			PacketProperties receivePacketProperties;

			this->communicator->fetch(i, receivePacket);
			receivePacket >> receivePacketProperties;

			switch (receivePacketProperties.subType)
			{
			case SubType::REQUEST_SHOP_INFORMATION:
			{
				sf::Uint8 shopID;
				receivePacket >> shopID;

				if (shopID <= 0 || shopID > numShops) // invalid ID
				{
					sendPackets.back()
						<< PacketProperties(receivePacketProperties.ID, PacketType::RESPONSE, SubType::RESPONSE_SHOP_INFORMATION, RequestValidity::INVALID_SHOP_ID);

					this->print("RSPN", "Denied an invalid SHOP_INFORMATION request from team " + std::to_string(i) + ": INVALID_SHOP_ID");
				}

				else // valid
				{
					Shop* shop = this->shops.at(shopID);
					sendPackets.back()
						<< PacketProperties(receivePacketProperties.ID, PacketType::RESPONSE, SubType::RESPONSE_SHOP_INFORMATION, RequestValidity::VALID)
						<< shop->getID()
						<< shop->getOwnerID()
						<< shop->getCapital(this->capPhase)
						<< shop->getPrice(this->capPhase)
						<< shop->getPrevRevenue()
						<< shop->getTransactionTimes()
						<< static_cast<sf::Uint16>((this->shops[this->teams.at(i)->getPosition()->getID()]->getMoveTime(shop)) * 60);

					this->print("RSPN", "Responded an SHOP_INFORMATION request from team " + std::to_string(i));
				}
			}
			break;

			case SubType::REQUEST_SHOP_PURCHASE:
			{
				sf::Uint8 shopID;

				receivePacket >> shopID;

				Shop* requestedShop = this->shops[shopID];

				if (teams[i]->getStatus() == TeamStatus::MOVING) // not on site
				{
					sendPackets.back() 
						<< PacketProperties(receivePacketProperties.ID, PacketType::RESPONSE, SubType::RESPONSE_SHOP_PURCHASE, RequestValidity::NOT_ON_SITE) 
						<< shopID;

					sendTeams.emplace_back(i);
					sendPackets.emplace_back();
					sendPackets.back()
						<< PacketProperties(this->communicator->getCurrentSendID(), PacketType::SEND, SubType::SEND_ERROR)
						<< sf::String(L"還不能買店家啦，")
						<< sf::String(L"你還沒到達定位喔!")
						<< sf::String(L"")
						<< sf::String(L"")
						<< sf::String(L"");

					this->print("RSPN", "Denied an invalid SHOP_PURCHASE request from team " + std::to_string(i) + ": NOT_ON_SITE");
				}

				else if (i == requestedShop->getOwnerID())
				{
					sendPackets.back()
						<< PacketProperties(receivePacketProperties.ID, PacketType::RESPONSE, SubType::RESPONSE_SHOP_PURCHASE, RequestValidity::ALREADY_OWNED);
					this->print("RSPN", "Denied an invalid SHOP_PURCHASE request from team " + std::to_string(i) + ": ALREADY_OWNED");
				}

				else if (requestedShop->purchasable())
				{
					sf::Uint32 price = requestedShop->getPrice(this->capPhase);
					if (this->teams[i]->getCash() >= price) // valid
					{
						std::vector<sf::Uint16> bonusActivated, bonusDeactivated;

						sendPackets.back()
							<< PacketProperties(receivePacketProperties.ID, PacketType::RESPONSE, SubType::RESPONSE_SHOP_PURCHASE, RequestValidity::VALID) 
							<< shopID 
							<< requestedShop->getOwnerID() // 0 for none
							<< price 
							<< this->teams[i]->purchase(requestedShop, price, bonusActivated);
						this->teams[i]->updateCapital(this->capPhase);
						sendPackets.back()
							<< this->teams[i]->getCapital();

						for (auto bonus : bonusActivated)
						{
							sendTeams.emplace_back(i);
							sendPackets.emplace_back();
							
							sendPackets.back()
								<< PacketProperties(receivePacketProperties.ID, PacketType::SEND, SubType::SEND_TAGS_COLLECTION_UPDATE)
								<< bonus
								<< teams[1]->getBonus(bonus)
								<< false;
						}


						if (requestedShop->getOwnerID()) //  buy from another team
						{
							sendTeams.emplace_back(requestedShop->getOwnerID());
							sendPackets.emplace_back();
							sendPackets.back()
								<< PacketProperties(this->communicator->getCurrentSendID(), PacketType::SEND, SubType::SEND_SELL)
								<< shopID
								<< static_cast<sf::Uint8>(i)
								<< price
								<< this->teams[requestedShop->getOwnerID()]->sell(requestedShop, price, bonusDeactivated);
							this->teams[requestedShop->getOwnerID()]->updateCapital(this->capPhase);
							sendPackets.back()
								<< this->teams[requestedShop->getOwnerID()]->getCapital();

							for (auto bonus : bonusDeactivated)
							{
								sendTeams.emplace_back(requestedShop->getOwnerID());
								sendPackets.emplace_back();

								sendPackets.back()
									<< PacketProperties(receivePacketProperties.ID, PacketType::SEND, SubType::SEND_TAGS_COLLECTION_UPDATE)
									<< bonus
									<< teams[1]->getBonus(bonus)
									<< true;
							}
						}

						broadcastPackets.emplace_back();
						broadcastPackets.back()
							<< PacketProperties(this->communicator->getCurrentBroadcastID(), PacketType::BROADCAST, SubType::BROADCAST_TRANSACTION)
							<< shopID
							<< static_cast<sf::Uint8>(i)
							<< this->shops[shopID]->getOwnerID()
							<< price;

						this->print("BROD", "Broadcasted a purchase");

						this->shops[shopID]->transaction(i);

						this->print("RSPN", "Responded an SHOP_PURCHASE request from team " + std::to_string(i));
						//this->print("GAME", "Team " + std::to_string(i) + " bought shop " + std::to_string(shopID) + " for " + std::to_string(price));

					}

					else // insufficient cash
					{
						
						sendPackets.back()
							<< PacketProperties(receivePacketProperties.ID, PacketType::RESPONSE, SubType::RESPONSE_SHOP_PURCHASE, RequestValidity::INSUFFICIENT_CASH)
							<< shopID 
							<< price - this->teams[i]->getCash(); // shortage
						this->print("RSPN", "Denied an invalid SHOP_PURCHASE request from team " + std::to_string(i) + ": INSUFFICIENT_CASH");

						sendTeams.emplace_back(i);
						sendPackets.emplace_back();
						sendPackets.back()
							<< PacketProperties(this->communicator->getCurrentSendID(), PacketType::SEND, SubType::SEND_ERROR)
							<< sf::String(L"你的錢不夠，沒辦法買這家店...")
							<< sf::String(L"再存" + std::to_wstring(price - this->teams[i]->getCash()) + L"元")
							<< sf::String(L"就可以啦!")
							<< sf::String(L"")
							<< sf::String(L"");
					}
				}

				else // frequent purchase
				{
				    sendPackets.back()
						<< PacketProperties(receivePacketProperties.ID, PacketType::RESPONSE, SubType::RESPONSE_SHOP_PURCHASE, RequestValidity::FREQUENT_PURCHASE) 
						<< shopID;
					this->print("RSPN", "Responded an invalid SHOP_PURCHASE request from team " + std::to_string(i) + ": FREQUENT_PURCHASE");
					
					sendTeams.emplace_back(i);
					sendPackets.emplace_back();
					sendPackets.back()
						<< PacketProperties(this->communicator->getCurrentSendID(), PacketType::SEND, SubType::SEND_ERROR)
						<< sf::String(L"這家店才剛被買下來")
						<< sf::String(L"或被店主造訪過，")
						<< sf::String(L"等等再來吧!")
						<< sf::String(L"")
						<< sf::String(L"");
				}
			}
			break;

			case SubType::REQUEST_MOVE:
			{
				if (this->teams[i]->getStatus() == TeamStatus::MOVING) // moving
				{
					sendPackets.back()
						<< PacketProperties(receivePacketProperties.ID, PacketType::RESPONSE, SubType::RESPONSE_MOVE, RequestValidity::MOVING);
					this->print("RSPN", "Denied an invalid MOVE request from team " + std::to_string(i) + ": MOVING");
				}

				else // valid
				{
					sf::Uint8 shopID;

					receivePacket >> shopID;

					Shop* requestedShop = this->shops[shopID];
					sf::Uint16 duration = (this->teams[i]->move(requestedShop)).asSeconds();

					sendPackets.back()
						<< PacketProperties(receivePacketProperties.ID, PacketType::RESPONSE, SubType::RESPONSE_MOVE, RequestValidity::VALID)
						<< shopID 
						<< duration;

					broadcastPackets.emplace_back();
					broadcastPackets.back()
						<< PacketProperties(this->communicator->getCurrentBroadcastID(), PacketType::BROADCAST, SubType::BROADCAST_MOVE)
						<< static_cast<sf::Uint8>(i)
						<< this->teams[i]->getPrevPosition()->getID()
						<< this->teams[i]->getPosition()->getID()
						<< duration;

					this->print("RSPN", "Responded an MOVE request from team " + std::to_string(i));
					//this->print("GAME", "Team " + std::to_string(i) + " is moving to shop " + )
				}
			}
			break;

			case SubType::REQUEST_TEAM_INFORMATION:
			{
				sf::Uint8 teamID;

				receivePacket >> teamID;

				Team* requestedTeam = this->teams[teamID];
				std::vector<Shop*> shopsOwned = requestedTeam->getShopsOwned();

				sendPackets.back()
					<< PacketProperties(receivePacketProperties.ID, PacketType::RESPONSE, SubType::RESPONSE_TEAM_INFORMATION, RequestValidity::VALID)
					<< teamID
					<< requestedTeam->getCash()
					<< requestedTeam->getCapital()
					<< static_cast<sf::Uint16>(shopsOwned.size() - requestedTeam->getNumShopsBankrupted());

				for (auto shop : shopsOwned)
				{
					if (!shop->getBankrupt())
					{
						sendPackets.back()
							<< shop->getID();
					}
				}
				
				sendPackets.back()
					<< requestedTeam->getPosition()->getID();
					/*<< requestedTeam->getPrevPosition()->getID()
					<< (requestedTeam->getStatus() == TeamStatus::MOVING)
					<< requestedTeam->getRemainingMoveTime();*/
			}
			break;

			default:
				break;
			}

			for (size_t j = 0; j < sendPackets.size(); j++)
			{
				this->communicator->send(sendTeams[j], sendPackets[j]);
			}
			
			for (auto broadcastPacket : broadcastPackets)
			{
				this->communicator->broadcast(broadcastPacket);
			}
		}
	}
}

void Server::updateEvents()
{

	if (!this->events.empty() && (this->gameTime.getElapsedTime().asSeconds() >= this->events.front().getTime().asSeconds())) // event due
	{
		switch (this->events.front().getType())
		{
		case GameEventType::START:
		{
			this->print("EVNT", "Game has started!");
			this->gameTime.restart();

			sf::Packet broadcastPacket;
			broadcastPacket
				<< PacketProperties(this->communicator->getCurrentBroadcastID(), PacketType::BROADCAST, SubType::BROADCAST_START);
			this->communicator->broadcast(broadcastPacket);
		}
		break;

		case GameEventType::SYNCHRONIZE:
		{
			this->print("EVNT", "Synchronizes with clients!");

			sf::Packet broadcastPacket;
			broadcastPacket
				<< PacketProperties(this->communicator->getCurrentBroadcastID(), PacketType::BROADCAST, SubType::BROADCAST_GAME_TIME)
				<< static_cast<sf::Uint32>(this->gameTime.getElapsedTime().asSeconds());

			this->communicator->broadcast(broadcastPacket);
		}
		break;

		case GameEventType::REVENUE:
		{
			this->print("EVNT", "Announces revenue!");
			this->print("EVNT", "According to revenue version " + std::to_string(this->revPhase + 1));

			// Send

			std::vector<sf::Uint32> tempByShop;

			for (auto shop : shops)
			{
				if (shop != nullptr)
				{
					shop->setPrevRevunue(shop->getRevenue(this->revPhase));
				}
			}

			for (size_t i = 1; i <= numTeams; i++)
			{
				sf::Packet sendPacket;
				sf::Int32 amount = this->teams[i]->getRevenue(this->revPhase, tempByShop);
				sendPacket
					<< PacketProperties(this->communicator->getCurrentSendID(), PacketType::SEND, SubType::SEND_REVENUE)
					<< amount
					<< this->teams[i]->getNumShopsOwned();
				for (size_t j = 0; j < this->teams[i]->getNumShopsOwned(); j++)
					sendPacket << tempByShop[j];
				sendPacket
					<< this->teams[i]->receiveRevenue(amount);

				this->communicator->send(i, sendPacket);

				this->print("EVNT", "Team " + std::to_string(i) + " receives $" + std::to_string(amount) + " of revenue!");
			}
		}
		break;

		case GameEventType::BANKRUPT:
		{
			std::vector<Shop*> shops = this->bankruptingShops.front();
			this->bankruptingShops.pop();
			
			for (size_t i = 0; i < shops.size(); i++)
			{
				Shop* shop = shops.at(i);
				shop->bankrupt();

				sf::Uint8 shopID = shop->getID();
				sf::Packet broadcastingPacket, sendPacket;

				// Broadcast
				broadcastingPacket
					<< PacketProperties(this->communicator->getCurrentBroadcastID(), PacketType::BROADCAST, SubType::BROADCAST_BANKRUPT)
					<< shopID;

				this->communicator->broadcast(broadcastingPacket);

				// Send

				if (shop->getOwnerID() != 0) // owned
				{
					std::vector<sf::Uint16> bonusDeactivated;
					teams[shop->getOwnerID()]->shopBankrupted(shop, bonusDeactivated);
					teams[shops[i]->getOwnerID()]->updateCapital(this->capPhase);
					sendPacket
						<< PacketProperties(this->communicator->getCurrentSendID(), PacketType::SEND, SubType::SEND_BANKRUPT)
						<< shopID
						<< teams[shop->getOwnerID()]->getCapital();

					this->communicator->send(shop->getOwnerID(), sendPacket);

					for (auto bonus : bonusDeactivated)
					{
						sf::Packet sendPacket;
						sendPacket
							<< PacketProperties(this->communicator->getCurrentSendID(), PacketType::SEND, SubType::SEND_TAGS_COLLECTION_UPDATE)
							<< bonus
							<< teams[1]->getBonus(bonus)
							<< true;
					}
				}
			}
		}
		break;

		case GameEventType::NEXT_CAP_PHASE:
		{
			this->capPhase++;

			for (size_t i = 1; i <= numTeams; i++)
			{
				this->teams[i]->updateCapital(this->capPhase);
				sf::Packet sendPacket;
				sendPacket
					<< PacketProperties(this->communicator->getCurrentSendID(), PacketType::SEND, SubType::SEND_PRICE_UPDATE)
					<< this->teams[i]->getCapital();
			}
		}
		break;

		case GameEventType::NEXT_REV_PHASE:
		{
			this->revPhase++;
		}
		break;

		case GameEventType::PRINT_LEADER:
		{
			for (size_t i = 1; i <= numTeams; i++)
			{
				int asset = 0;

				asset += this->teams[i]->getCash();
				asset += this->teams[i]->getCapital();

				this->print("LDER", "Team " + std::to_string(i) + " now has $" + std::to_string(asset) + " worth of asset!");
			}
		}	

		default:
			break;
		}
		//GameEvent currentEvent = this->events.front();
		this->events.pop();
	}
}

void Server::checkBackup()
{
	if (this->backupTime.getElapsedTime() >= backUpTimeGap)
	{
		this->print("SRVR", "Data has been backed up!");
		this->backupTime.restart();

		std::string backupFolderPath = "Backup\\";

		std::ofstream file(backupFolderPath + "server.txt");

		file
			<< "server\n"

			<< "time:\n"

			<< this->gameTime.getElapsedTime().asSeconds();

		file.close();

		for (size_t i = 1; i <= numTeams; ++i)
		{
			Team* team = this->teams[i];
			std::ofstream file(backupFolderPath + std::to_string(i) + ".txt");

			file 
				<< "team " << std::to_string(i)
				
				<< "\nstatus:\n" << static_cast<int>(team->getStatus())

				<< "\ncash:\n" << team->getCash()
				
				<< "\nvisiting shop:\n" << team->getPosition()->getID()

				<< "\nprevVisitingShop:\n" << ((team->getPrevPosition() == nullptr) ? ("0") : std::to_string((team->getPrevPosition()->getID())))

				<< "\nshops owned:\n";

			for (auto shop : team->getShopsOwned())
			{
				file << static_cast<int>(shop->getID()) << ",";
			}

			file 
				<< "\nmoving time:\n" << team->getRemainingMoveTime();

			file.close();
		}

		for (auto shop : shops)
		{
			if (shop == nullptr)
			{
				continue;
			}

			std::ofstream file(backupFolderPath + "shop" + std::to_string(static_cast<int>(shop->getID())) + ".txt");

			file
				<< "shop " << std::to_string(static_cast<int>(shop->getID()))

				<< "\nowner:\n" << static_cast<int>(shop->getOwnerID())

				<< "\nbankrupted:\n" << shop->getBankrupt()

				<< "\ntranscation times:\n" << shop->getTransactionTimes();

			file.close();
		}

	}
}

void Server::print(std::string cat, std::string message)
{
	short seconds = static_cast<short>(this->gameTime.getElapsedTime().asSeconds());
	short minutes = seconds / 60;
	seconds %= 60;

	std::string secondStr, minuteStr;

	secondStr = (seconds < 10 ? "0" + std::to_string(seconds) : std::to_string(seconds));
	minuteStr = (minutes < 10 ? "0" + std::to_string(minutes) : std::to_string(minutes));

	printf("[");
	printf("%s:%s", minuteStr.c_str(), secondStr.c_str());
	printf("]\t[");
	printf(cat.c_str());
	printf("]\t");
	printf(message.c_str());
	printf("\n");
}

Server::Server() :
	revPhase(0), capPhase(0)
{
	this->initGameMode();

	this->initEvents();

	this->communicator = new Communicator(this->gameTime);

	this->initData();
}

Server::~Server()
{
}

void Server::run()
{
	while (true)
	{
		this->update();
	}
}
