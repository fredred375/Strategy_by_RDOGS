#include "MapState.h"

void MapState::initPoints()
{
	int shopIndex = 1;
	wchar_t blank = ' ';
	points.emplace_back(2509.34f, 3524.19f, std::to_wstring(shopIndex) + blank + L"Shallot 紅蔥餐館", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(2568.f, 4162.4f, std::to_wstring(shopIndex) + blank + L"三角冰冰品專賣店", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(2540.21f, 3770.33f, std::to_wstring(shopIndex) + blank + L"自由51", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(4902.29f, 1554.5f, std::to_wstring(shopIndex) + blank + L"有意樹桿咖啡", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(5036.92f, 1942.66f, std::to_wstring(shopIndex) + blank + L"老先覺麻辣窯燒鍋", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(2380.01f, 2969.f, std::to_wstring(shopIndex) + blank + L"龐德羅莎 台大店", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(2842.44f, 2277.09f, std::to_wstring(shopIndex) + blank + L"活大餐廳", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(2493.52f, 2178.04f, std::to_wstring(shopIndex) + blank + L"摩斯漢堡 小福店", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(2595.66f, 1980.8f, std::to_wstring(shopIndex) + blank + L"稍飽 燒肉廚房", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(2750.51f, 2048.18f, std::to_wstring(shopIndex) + blank + L"女九餐廳", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(2499.13f, 2624.16f, std::to_wstring(shopIndex) + blank + L"小木屋鬆餅 台大店", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1075.88f, 1630.78f, std::to_wstring(shopIndex) + blank + L"錢都 師大店", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1870.54f, 2357.52f, std::to_wstring(shopIndex) + blank + L"七里亭", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1769.02f, 2031.25f, std::to_wstring(shopIndex) + blank + L"小川西堂", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1755.71f, 2234.99f, std::to_wstring(shopIndex) + blank + L"楽坡 公館店", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1168.3f, 1718.29f, std::to_wstring(shopIndex) + blank + L"雞二拉麵 師大店", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(683.109f, 1114.78f, std::to_wstring(shopIndex) + blank + L"肉多多火鍋 古亭店", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(4126.8f, 1443.21f, std::to_wstring(shopIndex) + blank + L"草泥Cafe", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(3012.56f, 766.885f, std::to_wstring(shopIndex) + blank + L"瑞安豆漿大王", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(2733.74f, 1161.55f, std::to_wstring(shopIndex) + blank + L"馬祖麵館", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1893.7f, 2109.79f, std::to_wstring(shopIndex) + blank + L"好想吃冰 公館店", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1905.46f, 2001.53f, std::to_wstring(shopIndex) + blank + L"柒食貳", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1735.87f, 1454.57f, std::to_wstring(shopIndex) + blank + L"糊塗麵", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1990.09f, 2134.15f, std::to_wstring(shopIndex) + blank + L"台一牛奶大王", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1994.28f, 1961.45f, std::to_wstring(shopIndex) + blank + L"璞田PureTime", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(2032.46f, 1943.42f, std::to_wstring(shopIndex) + blank + L"鳳城燒臘粵菜", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(2105.63f, 1431.18f, std::to_wstring(shopIndex) + blank + L"莫宰羊 大安台大店", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1914.25f, 2437.37f, std::to_wstring(shopIndex) + blank + L"比薩幫", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(3883.12f, 1360.93f, std::to_wstring(shopIndex) + blank + L"漢堡王 敦南店", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(3145.61f, 858.561f, std::to_wstring(shopIndex) + blank + L"雷咖哩", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(3169.74f, 2832.82f, std::to_wstring(shopIndex) + blank + L"摩斯漢堡 台科大店", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(2972.79f, 3111.5f, std::to_wstring(shopIndex) + blank + L"台科大第三學餐", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(3386.39f, 2303.88f, std::to_wstring(shopIndex) + blank + L" " + L"Living One", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(3462.38f, 2359.56f, std::to_wstring(shopIndex) + blank + L"星巴克 長興門市", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(4232.01f, 1594.9f, std::to_wstring(shopIndex) + blank + L"黑熊愛跳舞", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(948.992f, 1348.13f, std::to_wstring(shopIndex) + blank + L"秘氏珈琲", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1719.72f, 1194.69f, std::to_wstring(shopIndex) + blank + L"初魚屋台", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1298.73f, 1539.51f, std::to_wstring(shopIndex) + blank + L"小木屋鬆餅 師大店", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1432.14f, 1347.37f, std::to_wstring(shopIndex) + blank + L"師園鹽酥雞", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1313.3f, 1215.98f, std::to_wstring(shopIndex) + blank + L"貳樓餐廳 師大店", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1393.98f, 1669.68f, std::to_wstring(shopIndex) + blank + L"龍泉深海鮮魚湯", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(2621.85f, 417.514f, std::to_wstring(shopIndex) + blank + L"2J CAFE", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1858.32f, 847.971f, std::to_wstring(shopIndex) + blank + L"青田七六", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(4245.77f, 2214.56f, std::to_wstring(shopIndex) + blank + L"富士咖哩", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(4680.56f, 1709.56f, std::to_wstring(shopIndex) + blank + L"佐藤咖哩", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(4492.44f, 1924.97f, std::to_wstring(shopIndex) + blank + L"豬頭天知高飯", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(3668.04f, 1265.11f, std::to_wstring(shopIndex) + blank + L"找餐。店", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(3123.47f, 1519.75f, std::to_wstring(shopIndex) + blank + L"補時", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(3444.61f, 1166.83f, std::to_wstring(shopIndex) + blank + L"營養師的光合廚房", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(3199.91f, 1640.91f, std::to_wstring(shopIndex) + blank + L"穰穰", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(3029.64f, 1088.54f, std::to_wstring(shopIndex) + blank + L"曬貓咖啡", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1468.51f, 1015.58f, std::to_wstring(shopIndex) + blank + L"艾炫咖啡", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(3141.32f, 1748.07f, std::to_wstring(shopIndex) + blank + L"蘇草salvia", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(2985.13f, 1611.41f, std::to_wstring(shopIndex) + blank + L"揪食堂 韓國餐館", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(2815.24f, 1742.25f, std::to_wstring(shopIndex) + blank + L"開房間桌遊餐館", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(4635.37f, 1934.3f, std::to_wstring(shopIndex) + L"鴨膳師當歸鴨肉麵線", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(4096.2f, 1282.3f, std::to_wstring(shopIndex) + blank + L"吳一無二法式甜點", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(3727.11f, 1092.02f, std::to_wstring(shopIndex) + blank + L"餘記麵館", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(2124.56f, 2801.34f, std::to_wstring(shopIndex) + blank + L"麥當勞 公館店", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(2013.7f, 2775.56f, std::to_wstring(shopIndex) + blank + L"鴉片粉圓", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(2242.89f, 3036.99f, std::to_wstring(shopIndex) + blank + L"墨洋拉麵", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(2267.7f, 2953.67f, std::to_wstring(shopIndex) + blank + L"茗香園冰室 公館店", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1873.57f, 2610.54f, std::to_wstring(shopIndex) + blank + L"炸手指", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1603.37f, 2460.32f, std::to_wstring(shopIndex) + blank + L"Mr. 雪腐 公館店", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(248.934f, 597.765f, std::to_wstring(shopIndex) + blank + L"酮伴咖啡", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1584.69f, 2850.09f, std::to_wstring(shopIndex) + blank + L"水源會館 公館店", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(531.113f, 1160.59f, std::to_wstring(shopIndex) + blank + L"夏慕尼鐵板燒", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1895.68f, 2762.99f, std::to_wstring(shopIndex) + blank + L"馬辣麻辣鴛鴦火鍋", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(2112.18f, 2878.95f, std::to_wstring(shopIndex) + blank + L"喫尤平價鐵板燒", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1790.37f, 3329.78f, std::to_wstring(shopIndex) + blank + L"尖蚪", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(2240.42f, 3107.65f, std::to_wstring(shopIndex) + blank + L"三媽臭臭鍋", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(2211.24f, 3063.88f, std::to_wstring(shopIndex) + blank + L"鍋in百元風味火鍋", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(2044.78f, 2926.24f, std::to_wstring(shopIndex) + blank + L"土司吐司 公館店", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1493.67f, 2404.84f, std::to_wstring(shopIndex) + blank + L"El Sabroso", shopIndex++, textures["locationMark"], &font);
	points.emplace_back(1959.78f, 2633.9f, std::to_wstring(shopIndex) + blank + L"星巴克 公館店", shopIndex++, textures["locationMark"], &font);
	//player->setPosition(&points.at(player->getID() - 1));

	// hi
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
			points[tagsShopIndex[i][j] - 1].setTag(i);
			points[tagsShopIndex[i][j] - 1].setTexture(textures["locationMark" + std::to_string(i + 1)]);
		}
	}

	// double tags
	points[12 - 1].setTexture(textures["locationMark2.9"]);
	points[16 - 1].setTexture(textures["locationMark2.8"]);
	points[21 - 1].setTexture(textures["locationMark1.10"]);
	points[24 - 1].setTexture(textures["locationMark1.10"]);
	points[61 - 1].setTexture(textures["locationMark4.8"]);
	points[71 - 1].setTexture(textures["locationMark4.9"]);
	points[72 - 1].setTexture(textures["locationMark4.9"]);
	points[60 - 1].setTexture(textures["locationMark4.10"]);

}

void MapState::initTextures()
{

	textures["background"].loadFromFile("Resources/Textures/darkmap(0821)(revised).png");
	textures["notification"].loadFromFile("Resources/Textures/UI/notification.png");
	textures["locationMark"].loadFromFile("Resources/Textures/location_mark.png");
	textures["locationMark1"].loadFromFile("Resources/Textures/location_mark_1.png");
	textures["locationMark2"].loadFromFile("Resources/Textures/location_mark_2.png");
	textures["locationMark3"].loadFromFile("Resources/Textures/location_mark_3.png");
	textures["locationMark4"].loadFromFile("Resources/Textures/location_mark_4.png");
	textures["locationMark5"].loadFromFile("Resources/Textures/location_mark_5.png");
	textures["locationMark6"].loadFromFile("Resources/Textures/location_mark_6.png");
	textures["locationMark7"].loadFromFile("Resources/Textures/location_mark_7.png");
	textures["locationMark8"].loadFromFile("Resources/Textures/location_mark_8.png");
	textures["locationMark9"].loadFromFile("Resources/Textures/location_mark_9.png");
	textures["locationMark10"].loadFromFile("Resources/Textures/location_mark_10.png");
	textures["locationMark11"].loadFromFile("Resources/Textures/location_mark_11.png");
	textures["locationMark12"].loadFromFile("Resources/Textures/location_mark_11.png");
	textures["locationMark1.10"].loadFromFile("Resources/Textures/location_mark_1_10.png");
	textures["locationMark2.8"].loadFromFile("Resources/Textures/location_mark_2_8.png");
	textures["locationMark2.9"].loadFromFile("Resources/Textures/location_mark_2_9.png");
	textures["locationMark4.8"].loadFromFile("Resources/Textures/location_mark_4_8.png");
	textures["locationMark4.9"].loadFromFile("Resources/Textures/location_mark_4_9.png");
	textures["locationMark4.10"].loadFromFile("Resources/Textures/location_mark_4_10.png");

	textures["player"].loadFromFile("Resources/Textures/player_icon/player.png");
	textures["team1"].loadFromFile("Resources/Textures/player_icon/team1.png");
	textures["team2"].loadFromFile("Resources/Textures/player_icon/team2.png");
	textures["team3"].loadFromFile("Resources/Textures/player_icon/team3.png");
	textures["team4"].loadFromFile("Resources/Textures/player_icon/team4.png");
	textures["team5"].loadFromFile("Resources/Textures/player_icon/team5.png");
	textures["team6"].loadFromFile("Resources/Textures/player_icon/team6.png");
	textures["team7"].loadFromFile("Resources/Textures/player_icon/team7.png");
	textures["team8"].loadFromFile("Resources/Textures/player_icon/team8.png");
	textures["team9"].loadFromFile("Resources/Textures/player_icon/team9.png");

}

void MapState::initMap()
{
	background.setTexture(&textures["background"]);
	background.setSize(sf::Vector2f(textures["background"].getSize()));
}

void MapState::initUI()
{
	popUpWindow = new PopUpWindow(player, &font, communicator);
	playerUI = new PlayerUI(player, &font);
	pointHoverUI = new PointHoverUI(&font);
	playerUI->setWindow(window);
	teamPopUp = new TeamPopUp(player, &font, communicator);
	teamPopUp->setWindow(window);
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
	for (auto team : teams)
	{
		if (team->getID() == this->playerID)
		{
			continue;
		}
		if (team->clicked(mouseData->mousePos.x, mouseData->mousePos.y))
		{
			if (mouseData->leftClicked)
			{
				teamPopUp->activated = true;
				teamPopUp->setTeam(team);
				teamPopUp->initDraw(view);
				pointHoverUI->activated = false;
				return;
			}
		}
	}
	for (auto& point : points)
	{
		if (point.clicked(mouseData->mousePos.x, mouseData->mousePos.y))
		{
			if (mouseData->leftClicked)
			{
				popUpWindow->activated = true;
				popUpWindow->setPoint(&point);
				popUpWindow->initDraw(view);
				pointHoverUI->activated = false;
			}
			else
			{
				if (!pointHoverUI->activated || pointHoverUI->getPoint() != &point)
				{
					pointHoverUI->activated = true;
					pointHoverUI->setPoint(&point);
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

MapState::MapState(sf::RenderWindow* window, std::stack<State*>* states, MouseData* mouseData, sf::Uint8 teamID, Communicator* communicator) :
	State(window, states, mouseData, communicator), player(nullptr), mapViewport(constants::PLAYER_UI_PORTION, 0.f, constants::MAP_PORTION, 1.f), playerID(teamID),
	playerUI(nullptr), UIViewport(0.f, 0.f, constants::PLAYER_UI_PORTION, 1.f), notifViewport(1 - 350.f / 1920.f, 0.f, 350.f / 1920.f, 1.f)
{

	font.loadFromFile("Resources/Fonts/NotoSansCJKtc-Regular.otf");
	initTextures();
	player = new Player(teamID, &this->textures["player"]);
	for (int i = 0; i < 8; i++)
	{
		if (i + 1 != teamID)
		{
			teams.push_back(new Player(i + 1, &(this->textures["team" + std::to_string(i + 1)])));
			//teams.at(i)->setColor(sf::Color::Green);
		}
		else
		{
			teams.push_back(player);
		}
		teams.back()->setPointList(&points);
	}
	initPoints();
	initMap();
	initUI();
	view = sf::View(sf::Vector2f(2150.f, 2900.f), sf::Vector2f(constants::MAPVIEW_WIDTH, constants::MAPVIEW_HEIGHT));
	view.setViewport(mapViewport);
	UIView = sf::View(sf::Vector2f(constants::UIVIEW_WIDTH / 2.f * -1.f, constants::UIVIEW_HEIGHT / 2.f), sf::Vector2f(constants::UIVIEW_WIDTH, constants::UIVIEW_HEIGHT));
	UIView.setViewport(UIViewport);
	notifView = sf::View(sf::Vector2f(350.f, 1080.f), sf::Vector2f(700.f, 2160.f));
	notifView.setViewport(notifViewport);
}

MapState::~MapState()
{
	delete popUpWindow;
}

void MapState::update(const float& dt)
{
	playerUI->update(mouseData, dt);
	if (!popUpWindow->activated && !teamPopUp->activated)
	{
		updateMouseInput();
		checkBoundaries();
	}
	else if(popUpWindow->activated)
	{
		popUpWindow->update(mouseData);
	}
	else if (teamPopUp->activated)
	{
		teamPopUp->update(mouseData);
	}
	handleRecieves();
	for (auto team : teams)
	{
		team->update(dt);
	}
	if (!notifications.empty())
	{
		for (auto notification : notifications)
		{
			notification->update(dt);
		}
		updateNotifList();
	}
	for (size_t i = 0; i < 75; ++i)
	{
		Point& point = this->points[i];
		if (point.getNonPurchasable())
		{
			point.updateText();
		}
	}
}

void MapState::handleRecieves()
{
	if (this->communicator->newReceives())
	{
		printf( "new receive!\n" );
		PacketProperties receivePacketProperties;
		sf::Packet receivePacket = this->communicator->fetch(receivePacketProperties);

		switch (receivePacketProperties.packetType)
		{
		
		case PacketType::BROADCAST:
		{
			printf("received server broadcast!\n");

			switch (receivePacketProperties.subType)
			{
			case SubType::BROADCAST_START:
			{
				printf("Game has started!");

				this->onBroadcastStart();
			}
			break;
			case SubType::BROADCAST_GAME_TIME:
			{
				printf("Synchronized game time!\n");

				sf::Uint32 currentGameTime;
				receivePacket >> currentGameTime;

				this->onBroadcastGameTime(currentGameTime);
			}
			break;

			case SubType::BROADCAST_BANKRUPT:
			{
				sf::Uint8 shopID;
				receivePacket >> shopID;

				printf("shop %d was bankrupted!\n", shopID);
				

				this->onBroadcastBankrupt(shopID);
			}
			break;

			case SubType::BROADCAST_TRANSACTION:
			{
				sf::Uint8 shopID, purchasingTeamID, sellingTeamID;
				sf::Uint32 price;
				receivePacket >> shopID >> purchasingTeamID >> sellingTeamID >> price;

				printf("a transaction broadcast!\n");

				this->onBroadcastTransaction(shopID, purchasingTeamID, sellingTeamID, price);
			}
			break;

			case SubType::BROADCAST_MOVE:
			{
				sf::Uint8 teamID, from, to;
				sf::Uint16 duration;
				receivePacket >> teamID >> from >> to >> duration;

				printf("a move broadcast!\n");

				this->onBroadcastMove(teamID, from, to, duration);
			}
			break;

			

			default:
				break;
			}
		}
		break;
		
		case PacketType::SEND:
		{
			printf("received server send!\n");
			switch (receivePacketProperties.subType)
			{
			case SubType::SEND_TAGS_COLLECTION_UPDATE:
			{
				printf("a tags collection update!\n");
				sf::Uint16 tagIndex;
				double bonus;
				bool lose;
				receivePacket >> tagIndex >> bonus >> lose;

				this->onTagsCollectionUpdate(static_cast<ShopTag>(tagIndex), bonus, lose);
			}
			break;
			case SubType::SEND_PRICE_UPDATE:
			{
				printf("a price update send!\n");
				sf::Int32 cap;
				receivePacket >> cap;

				this->onBroadcastPriceUpdate(cap);
			}
			break;

			case SubType::SEND_PLAYER_INFORMATION:
			{
				sf::Int32 cash;
				sf::Int32 cap;
				sf::Uint16 numShopsOwned;
				std::vector<sf::Uint8> ownedShopsID;
				sf::Uint8 visiting, prevVisiting, tempShopID;
				bool moving;
				sf::Uint16 duration;
				receivePacket >> cash >> cap >> numShopsOwned;
					
				for (size_t i = 0; i < numShopsOwned; i++)
				{
					receivePacket >> tempShopID;
					ownedShopsID.emplace_back(tempShopID);
				}
					
				receivePacket >> visiting >> prevVisiting >> moving >> duration;

				printf("a player information send!\n");

				this->onPlayerInformation(cash, cap, ownedShopsID, visiting, prevVisiting, moving, duration);
			}
			break;
			case SubType::SEND_MOVE:
			{
				sf::Uint8 teamID, from, to;
				sf::Uint16 duration;
				receivePacket >> teamID >> from >> to >> duration;

				printf("a move send!\n");
				//std::cout << teamID << " from " << from << " to " << to << " for " << duration << "\n";

				this->onBroadcastMove(teamID, from, to, duration);
			}
			break;
			case SubType::SEND_SELL:
			{
				sf::Uint8 shopID;
				sf::Uint8 purchasingTeamID;
				sf::Uint32 income;
				sf::Int32 cashBalance;
				sf::Int32 cap;

				printf("a sell send!\n");

				receivePacket >> shopID >> purchasingTeamID >> income >> cashBalance >> cap;
				
				this->onSell(shopID, purchasingTeamID, income, cashBalance, cap);
			}
			break;

			case SubType::SEND_REVENUE:
			{
				sf::Int32 amount, tempByShop;
				sf::Uint16 numShopsOwned;
				std::vector<sf::Int32> byShop;
				sf::Uint32 cashBalance;

				printf("a revenue send!\n");

				receivePacket >> amount >> numShopsOwned;

				for (size_t i = 0; i < numShopsOwned; i++)
				{
					receivePacket >> tempByShop;
					byShop.emplace_back(tempByShop);
				}

				receivePacket >> cashBalance;

				this->onRevenue(amount, byShop, cashBalance);
			}
			break;

			case SubType::SEND_BANKRUPT:
			{
				sf::Uint8 shopID;
				sf::Int32 cap;

				receivePacket >> shopID >> cap;

				this->onBankrupt(shopID, cap);
			}
			break;

			case SubType::SEND_ERROR:
			{
				std::array<sf::String, 5> lines;
				notifications.push_back(new Notification(&font, &textures["notification"]));
				notifications.back()->setPosition(sf::Vector2f(25.f, 2160.f - 420.f * notifications.size()));
				notifications.back()->setTitle(L"唉呦喂呀!");
				int i = 1;
				for (auto line : lines)
				{
					receivePacket >> line;
					notifications.back()->setString(i, line);
					i++;
				}
			}

			default:
				break;
			}
		}
		break;
		
		default:
			break;
		}
		
	}
}

void MapState::updateMouseInput()
{
	if (mouseData->leftClicked)
	{
		std::cout << mouseData->mousePos.x << "f, " << mouseData->mousePos.y << "f" << std::endl;
	}
	//zoom in & out
	if (mouseData->wheelTicks != 0)
	{
		if (mouseData->wheelTicks > 0)
		{
			//zoom in
			if (view.getSize().x > (float)constants::WINDOW_WIDTH_BIG / 2.f)
			{
				view.setSize(view.getSize() * constants::ZOOM_IN_SPEED);
				if (pointHoverUI->activated)
				{
					pointHoverUI->initDraw(view);
				}
			}
		}
		else
		{
			//zoom out
			view.setSize(view.getSize() * constants::ZOOM_OUT_SPEED);
			if (pointHoverUI->activated)
			{
				pointHoverUI->initDraw(view);
			}
		}
	}

	//view dragging
	if (mouseData->leftPressed && mouseData->moving)
	{
		if (mouseData->mousePressedPos.x > window->getSize().x * constants::PLAYER_UI_PORTION) //not in ui portion
		{
			const sf::Vector2f deltaPos = mouseData->oldMousePos - mouseData->mousePos;
			view.setCenter(view.getCenter() + deltaPos);
			mouseData->oldMousePosPixel = mouseData->mousePosPixel;
		}
	}
	checkPointsClicked();
}

void MapState::updateNotifList()
{
	if (!notifications.empty())
	{
		if (notifications.front()->getSpan() <= 0)
		{
			delete notifications.front();
			notifications.erase(notifications.begin());
			for (int i = 0; i < notifications.size(); i++)
			{
				notifications.at(i)->setPosition(sf::Vector2f(25.f, 2160.f - 420.f * (i + 1)));
			}
		}
	}
}

void MapState::render(sf::RenderWindow* window)
{
	if (!window)
	{
		window = this->window;
	}
	window->setView(UIView);
	playerUI->draw(window);//this function will call setView(boxView), thus changing the view of the window
	window->setView(view);
	window->draw(background);
	for (auto& point : points)
	{
		point.draw(window);
	}
	for (auto team : teams)
	{
		if(team != player)
			team->draw(window);
	}
	player->draw(window);
	if (pointHoverUI->activated)
	{
		pointHoverUI->draw(window);
	}
	if (popUpWindow->activated)
	{
		popUpWindow->draw(window);
	}
	if (teamPopUp->activated)
	{
		teamPopUp->draw(window);
		window->setView(view);
	}
	if (!notifications.empty())
	{
		window->setView(notifView);
		for (auto notification : notifications)
		{
			notification->draw(window);
		}
		window->setView(view);
	}
}

void MapState::resizeView(float aspectRatio)
{
	State::resizeView(aspectRatio * constants::MAP_PORTION);
	if (popUpWindow->activated)
	{
		popUpWindow->initDraw(view);
	}
}

void MapState::onBroadcastStart()
{
	notifications.push_back(new Notification(&font, &textures["notification"]));
	notifications.back()->setPosition(sf::Vector2f(25.f, 2160.f - 420.f * notifications.size()));
	notifications.back()->setTitle(L"致富之路已經開始!");
	notifications.back()->setString(1, L"遊戲開始囉!");
}

void MapState::onBroadcastGameTime(sf::Uint32 currentGameTime)
{
	playerUI->setTime(static_cast<float>(currentGameTime));
}

void MapState::onBroadcastBankrupt(sf::Uint8 shopID)
{
	notifications.push_back(new Notification(&font, &textures["notification"]));
	notifications.back()->setPosition(sf::Vector2f(25.f, 2160.f - 420.f * notifications.size()));
	notifications.back()->setTitle(L"破產!");
	notifications.back()->setString(1, (points.at(shopID - 1).getOwnerID() == 0 ? L"銀行擁有的" : L"第" + std::to_wstring(points.at(shopID - 1).getOwnerID()) + L"小隊擁有的"));
	notifications.back()->setString(2, points.at(shopID - 1).getName());
	notifications.back()->setString(3, L"倒閉了...");

	points.at(shopID - 1).bankrupt = true;
}

void MapState::onBroadcastTransaction(sf::Uint8 shopID, sf::Uint8 purchasingTeamID, sf::Uint8 sellingTeamID, sf::Uint32 price)
{
	notifications.push_back(new Notification(&font, &textures["notification"]));
	notifications.back()->setPosition(sf::Vector2f(25.f, 2160.f - 420.f * notifications.size()));
	notifications.back()->setTitle(L"成交!");
	notifications.back()->setString(1, L"第" + std::to_wstring(purchasingTeamID) + L"小隊");
	notifications.back()->setString(2, L"從" + (sellingTeamID == 0 ? L"銀行" : L"第" + std::to_wstring(sellingTeamID) + L"小隊") + L"手中");
	notifications.back()->setString(3, L"買下了");
	notifications.back()->setString(4, points.at(shopID - 1).getName());

	points.at(shopID - 1).setOwnerID(purchasingTeamID);
	points.at(shopID - 1).setNonPurchasable();
}

void MapState::onBroadcastMove(sf::Uint8 teamID, sf::Uint8 fromShopID, sf::Uint8 toShopID, sf::Uint16 duration)
{
	if (duration == 0)
	{
		teams.at(teamID - 1)->setPosition(&points.at(toShopID - 1));
	}
	else
	{
		teams.at(teamID - 1)->setPosition(&points.at(fromShopID - 1));
		teams.at(teamID - 1)->moveToPoint(&points.at(toShopID - 1), duration);
	}
}

void MapState::onBroadcastPriceUpdate(sf::Int32 cap)
{
	notifications.push_back(new Notification(&font, &textures["notification"]));
	notifications.back()->setPosition(sf::Vector2f(25.f, 2160.f - 420.f * notifications.size()));
	notifications.back()->setTitle(L"市場有些波動!");
	notifications.back()->setString(1, L"商家的售價與資本額變動了");
	notifications.back()->setString(2, L"你的商家總資本額現在是:");
	notifications.back()->setString(3, std::to_wstring(cap) + L"元");

}

void MapState::onTagsCollectionUpdate(ShopTag tag, double bonus, bool lose)
{
	std::wstring tagName;

	switch (tag)
	{
	case ShopTag::WENZHOU:
		tagName = L"溫州商圈";
		break;
	case ShopTag::SHIDA:
		tagName = L"師大商圈";
		break;
	case ShopTag::YIYIBA:
		tagName = L"118巷";
		break;
	case ShopTag::GONGGUAN:
		tagName = L"公館商圈";
		break;
	case ShopTag::FASTFOOD:
		tagName = L"速食店";
		break;
	case ShopTag::STARBUCKS:
		tagName = L"星巴克";
		break;
	case ShopTag::CURRY:
		tagName = L"咖哩店";
		break;
	case ShopTag::RAMEN:
		tagName = L"拉麵店";
		break;
	case ShopTag::HOTPOT:
		tagName = L"火鍋店";
		break;
	case ShopTag::ICE:
		tagName = L"冰店";
		break;
	case ShopTag::CHAMONIX:
		tagName = L"夏慕尼";
		break;
	case ShopTag::MALA:
		tagName = L"馬辣";
		break;
	case ShopTag::numShopTags:
		break;
	default:
		break;
	}

	if (!lose)
	{
		notifications.push_back(new Notification(&font, &textures["notification"]));
		notifications.back()->setPosition(sf::Vector2f(25.f, 2160.f - 420.f * notifications.size()));
		notifications.back()->setTitle(tagName + L" 蒐集成功!");
		notifications.back()->setString(1, L"你的營收金額將會乘以");
		notifications.back()->setString(2, std::to_wstring(bonus) + L"倍!");
	}

	else
	{
		notifications.push_back(new Notification(&font, &textures["notification"]));
		notifications.back()->setPosition(sf::Vector2f(25.f, 2160.f - 420.f * notifications.size()));
		notifications.back()->setTitle(L"你的" + tagName + L" 蒐集被破壞了...");
		notifications.back()->setString(1, L"你的營收金額將不再有加成");
	}
}

void MapState::onPlayerInformation(sf::Int32 cash, sf::Int32 cap, std::vector<sf::Uint8> owenedShopsID, sf::Uint8 visitingShopID, sf::Uint8 prevVisitingShopID, bool moving, sf::Uint16 moveDuration)
{
	if (moving)
	{
		player->setPosition(&points.at(prevVisitingShopID - 1));
		player->moveToPoint(&points.at(visitingShopID - 1), moveDuration);
	}
	else
	{
		player->setPosition(&points.at(visitingShopID - 1));
	}
	for (int i = 0; i < owenedShopsID.size(); i++)
	{
		int shopID = owenedShopsID.at(i);
		player->addProperty(&points.at(shopID - 1));
	}
	player->setCash(cash);
	player->setCap(cap);
}

void MapState::onSell(sf::Uint8 shopID, sf::Uint8 purchasingTeamID, sf::Uint32 income, sf::Int32 cashBalance, sf::Int32 cap)
{
	notifications.push_back(new Notification(&font, &textures["notification"]));
	notifications.back()->setPosition(sf::Vector2f(25.f, 2160.f - 420.f * notifications.size()));
	notifications.back()->setTitle(L"被買走了...");
	notifications.back()->setString(1, this->points.at(shopID - 1).getName() + L"已經被");
	notifications.back()->setString(2, L"第" + std::to_wstring(purchasingTeamID) + L"小隊買走了");
	notifications.back()->setString(3, L"不過至少你獲得了" + std::to_wstring(income) + L"元");

	player->removeProperty(shopID);
	player->setCash(cashBalance);
	player->setCap(cap);
}

void MapState::onRevenue(sf::Int32 amount, std::vector<sf::Int32> byShop, sf::Uint32 cashBalance)
{
	notifications.push_back(new Notification(&font, &textures["notification"]));
	notifications.back()->setPosition(sf::Vector2f(25.f, 2160.f - 420.f * notifications.size()));
	notifications.back()->setTitle(L"發放盈餘!");
	notifications.back()->setString(1, L"這季的盈餘發下來了");
	notifications.back()->setString(2, L"你共獲得");
	notifications.back()->setString(3, std::to_wstring(amount) + L"元");

	player->setCash(cashBalance);
	player->updateCashUI = true;
}

void MapState::onBankrupt(sf::Uint8 shopID, sf::Int32 cap)
{
	notifications.push_back(new Notification(&font, &textures["notification"]));
	notifications.back()->setPosition(sf::Vector2f(25.f, 2160.f - 420.f * notifications.size()));
	notifications.back()->setTitle(L"你的商家破產了...");
	notifications.back()->setString(1, this->points.at(shopID - 1).getName() + L"已經破產");
	notifications.back()->setString(2, L"你的商家總資本額現在是:");
	notifications.back()->setString(3, std::to_wstring(cap) + L"元");
	player->removeProperty(shopID);
	player->setCap(cap);
}
