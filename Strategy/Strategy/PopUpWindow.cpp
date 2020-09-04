#include "PopUpWindow.h"


void PopUpWindow::setPoint(Point* point)
{
	this->point = point;
	tagNum = point->getTag().size();
	communicator->requestShopInformation(point);
}

void PopUpWindow::initDraw(const sf::View& view)
{
	//displays as no owner
	ownershipBody.setTextureRect(sf::IntRect(0, 0, ownershipTexture.getSize().x / 9, ownershipTexture.getSize().y));

	windowBody.setSize(view.getSize() * 0.75f);
	windowBody.setPosition(view.getCenter() - windowBody.getSize() / 2.f);

	closeBody.setSize(sf::Vector2f(windowBody.getSize().x * 30.f / 1080.f, windowBody.getSize().y * 30.f / 810.f));
	closeBody.setPosition(windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x * 1023.f / 1080.f, windowBody.getSize().y * 23.f / 810.f));

	ownershipBody.setTextureRect(sf::IntRect(0, 0, ownershipTexture.getSize().x / 9, ownershipTexture.getSize().y));
	ownershipBody.setSize(sf::Vector2f(windowBody.getSize().x * 0.367f, windowBody.getSize().y * 0.23f));
	ownershipBody.setPosition(windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x * 0.106f, windowBody.getSize().y / 10.f * 7.f));

	purchaseBody.setSize(sf::Vector2f(windowBody.getSize().x * 0.2037f, windowBody.getSize().y * 0.232f));
	purchaseBody.setPosition(windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x * 0.7638f, windowBody.getSize().y * 0.706f));

	moveBody.setSize(sf::Vector2f(windowBody.getSize().x * 0.2037f, windowBody.getSize().y * 0.232f));
	moveBody.setPosition(windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x * 0.5278f, windowBody.getSize().y * 0.706f));

	nameText.setString(point->getName());
	nameText.setCharacterSize(windowBody.getSize().x / 18.f);
	centerText(nameText, windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x / 10.f * 2.8f, windowBody.getSize().y / 10.f * 1.2f));

	priceText.setString(L"更い");
	priceText.setCharacterSize(windowBody.getSize().x / 25.f);
	centerTextRight(priceText, windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x * 0.44f, windowBody.getSize().y / 10.f * 5.88f));

	capitalText.setString(L"更い");
	capitalText.setCharacterSize(windowBody.getSize().x / 25.f);
	centerTextRight(capitalText, windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x * 0.44f, windowBody.getSize().y * 0.276f));

	prevRevenueText.setString(L"更い");
	prevRevenueText.setCharacterSize(windowBody.getSize().x / 25.f);
	centerTextRight(prevRevenueText, windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x * 0.44f, windowBody.getSize().y * 0.380f));
	
	transactionText.setString(L"更い");
	transactionText.setCharacterSize(windowBody.getSize().x / 25.f);
	centerTextRight(transactionText, windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x * 0.44f, windowBody.getSize().y * 0.485f));

	moveText.setString(L"更い");
	moveText.setCharacterSize(windowBody.getSize().x / 25.f);
	centerTextRight(moveText, windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x * 0.94f, windowBody.getSize().y / 10.f * 5.88f));

	for (int i = 0; i < tagNum; i++)
	{
		switch (point->getTag().at(i))
		{
		case ShopTag::WENZHOU:
			tagsText.at(i).setString(L"放");
			break;
		case ShopTag::SHIDA:
			tagsText.at(i).setString(L"畍");
			break;
		case ShopTag::YIYIBA:
			tagsText.at(i).setString(L"118");
			break;
		case ShopTag::GONGGUAN:
			tagsText.at(i).setString(L"そ繻");
			break;
		case ShopTag::FASTFOOD:
			tagsText.at(i).setString(L"硉");
			break;
		case ShopTag::STARBUCKS:
			tagsText.at(i).setString(L"琍ぺ");
			break;
		case ShopTag::CURRY:
			tagsText.at(i).setString(L"〡");
			break;
		case ShopTag::RAMEN:
			tagsText.at(i).setString(L"┰难");
			break;
		case ShopTag::HOTPOT:
			tagsText.at(i).setString(L"羚");
			break;
		case ShopTag::ICE:
			tagsText.at(i).setString(L"┍");
			break;
		case ShopTag::CHAMONIX:
			tagsText.at(i).setString(L"甃紏ェ");
			break;
		case ShopTag::MALA:
			tagsText.at(i).setString(L"皑欢");
			break;
		}
		tagsText.at(i).setCharacterSize(windowBody.getSize().x / 60.f);
		centerText(tagsText.at(i), windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x * 0.69f, windowBody.getSize().y * (0.3016f + 80.f / 810.f * i)));
	}

	if (tagNum == 0)
	{
		tagNum = 1;
		tagsText.front().setString(L"礚");
	}

	for (int i = 0; i < tagNum; i++)
	{
		tagsBody.at(i).setSize(sf::Vector2f(windowBody.getSize().x * 0.0926f, windowBody.getSize().y * 0.068f));
		tagsBody.at(i).setPosition(windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x * 0.6574f, windowBody.getSize().y * (0.2716f + 80.f / 810.f * i)));
	}
}

void PopUpWindow::checkMouseData(MouseData* mouseData)
{
	checkCloseWindow(mouseData);
	if (canPurchase)
	{
		checkPurchase(mouseData);
	}
	if (player->getArrived() && player->getPoint() != point)
	{
		checkMove(mouseData);
	}
}

void PopUpWindow::update(MouseData* mouseData)
{
	if (point->requestInfo)
	{
		communicator->requestShopInformation(point);
		point->requestInfo = false;
	}

	updateOwnership();

	updatePurchaseButton();

	updateMoveButton();

	updateText();

	checkMouseData(mouseData);
}

void PopUpWindow::checkCloseWindow(MouseData* mouseData)
{
	if (mouseData->leftClicked)
	{
		if (mouseData->mousePos.x <= closeBody.getPosition().x + closeBody.getSize().x && mouseData->mousePos.x >= closeBody.getPosition().x)
		{
			if (mouseData->mousePos.y <= closeBody.getPosition().y + closeBody.getSize().y && mouseData->mousePos.y >= closeBody.getPosition().y)
			{
				//closed
				activated = false;
				point = nullptr;
			}
		}
	}
}

void PopUpWindow::checkPurchase(MouseData* mouseData)
{
	if (mouseData->leftClicked && !player->disablePurchase)
	{
		if (mouseData->mousePos.x <= purchaseBody.getPosition().x + purchaseBody.getSize().x && mouseData->mousePos.x >= purchaseBody.getPosition().x)
		{
			if (mouseData->mousePos.y <= purchaseBody.getPosition().y + purchaseBody.getSize().y && mouseData->mousePos.y >= purchaseBody.getPosition().y)
			{
				//purchased
				communicator->requestPurchase(player, point);
				purchaseBody.setTextureRect(sf::IntRect(0, 0, purchaseTexture.getSize().x / 2, purchaseTexture.getSize().y));
				canPurchase = false;
				player->disablePurchase = true;
			}
		}
	}
}

void PopUpWindow::checkMove(MouseData* mouseData)
{
	if (mouseData->leftClicked && !player->disableMove)
	{
		if (mouseData->mousePos.x <= moveBody.getPosition().x + moveBody.getSize().x && mouseData->mousePos.x >= moveBody.getPosition().x)
		{
			if (mouseData->mousePos.y <= moveBody.getPosition().y + moveBody.getSize().y && mouseData->mousePos.y >= moveBody.getPosition().y)
			{
				//move
				communicator->requestMove(player, point);
				moveBody.setTextureRect(sf::IntRect(0, 0, moveTexture.getSize().x / 2, moveTexture.getSize().y));
				player->disableMove = true;
			}
		}
	}
}

void PopUpWindow::updateOwnership()
{
	int ownerID = point->getOwnerID();
	if (ownerID < 1 || ownerID > 8)
	{
		ownerID = 0;
	}
	sf::IntRect uvRect(ownershipTexture.getSize().x / 9 * ownerID, 0, ownershipTexture.getSize().x / 9, ownershipTexture.getSize().y);
	ownershipBody.setTextureRect(uvRect);
}

void PopUpWindow::updatePurchaseButton()
{
	if (!player->disablePurchase)
	{
		if (canPurchase)
		{
			if (!(player->getArrived() && player->getPoint() == this->point))
			{
				canPurchase = false;
				purchaseBody.setTextureRect(sf::IntRect(static_cast<int>(canPurchase) * purchaseTexture.getSize().x / 2, 0, purchaseTexture.getSize().x / 2, purchaseTexture.getSize().y));
			}
		}
		else if (point->getOwnerID() != this->player->getID())
		{
			if (player->getArrived() && player->getPoint() == this->point)
			{
				canPurchase = true;
				purchaseBody.setTextureRect(sf::IntRect(static_cast<int>(canPurchase) * purchaseTexture.getSize().x / 2, 0, purchaseTexture.getSize().x / 2, purchaseTexture.getSize().y));
			}
		}
	}
}

void PopUpWindow::updateMoveButton()
{
	if (!player->disableMove)
	{
		if (player->getArrived() && player->getPoint() != point)
		{
			moveBody.setTextureRect(sf::IntRect(moveTexture.getSize().x / 2, 0, moveTexture.getSize().x / 2, moveTexture.getSize().y));
		}
		else
		{
			moveBody.setTextureRect(sf::IntRect(0, 0, moveTexture.getSize().x / 2, moveTexture.getSize().y));
		}
	}
}

void PopUpWindow::updateText()
{
	if (point->updatePopUpInfo)
	{
		capitalText.setString(std::to_string(point->getCapital()));
		centerTextRight(capitalText, windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x * 0.44f, windowBody.getSize().y * 0.2874f));

		prevRevenueText.setString(std::to_string(point->getPrevRevenue()));
		centerTextRight(prevRevenueText, windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x * 0.44f, windowBody.getSize().y * 0.3862f));

		transactionText.setString(std::to_string(point->getTransactionTimes()));
		centerTextRight(transactionText, windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x * 0.44f, windowBody.getSize().y * 0.4850f));

		priceText.setString(std::to_string(point->getPrice()));
		centerTextRight(priceText, windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x * 0.44f, windowBody.getSize().y * 0.5837f));
		

		moveText.setString(std::to_wstring(point->moveTime) + L"");
		centerTextRight(moveText, windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x * 0.94f, windowBody.getSize().y / 10.f * 5.88f));

		updateOwnership();
		point->updatePopUpInfo = false;
	}
}

PopUpWindow::PopUpWindow(Player* player, sf::Font* font, Communicator* communicator) :
	activated(false), font(font), player(player), point(nullptr), canPurchase(false), communicator(communicator), tagsBody(2, sf::RectangleShape()), tagsText(2, sf::Text()), tagNum(0)
{
	nameText.setFont(*font);
	nameText.setStyle(sf::Text::Bold);
	priceText.setFont(*font);
	priceText.setFillColor(sf::Color(26, 115, 232));
	priceText.setStyle(sf::Text::Bold);
	capitalText.setFont(*font);
	capitalText.setFillColor(sf::Color(26, 115, 232));
	capitalText.setStyle(sf::Text::Bold);
	prevRevenueText.setFont(*font);
	prevRevenueText.setFillColor(sf::Color(26, 115, 232));
	prevRevenueText.setStyle(sf::Text::Bold);
	transactionText.setFont(*font);
	transactionText.setFillColor(sf::Color(26, 115, 232));
	transactionText.setStyle(sf::Text::Bold);
	moveText.setFont(*font);
	moveText.setFillColor(sf::Color(26, 115, 232));
	moveText.setStyle(sf::Text::Bold);
	for (auto& tagText : tagsText)
	{
		tagText.setFont(*font);
	}

	if (windowTexture.loadFromFile("Resources/Textures/UI/PopUpWindow/windowBody.png"))
	{
		windowBody.setTexture(&windowTexture);
	}
	else
	{
		std::cout << "Failed to load texture : PopUpWindow.png" << std::endl;
	}
	if (ownershipTexture.loadFromFile("Resources/Textures/UI/PopUpWindow/checkmarkbox.png"))
	{
		ownershipBody.setTexture(&ownershipTexture);
		ownershipBody.setTextureRect(sf::IntRect(0, 0, ownershipTexture.getSize().x / 9, ownershipTexture.getSize().y));
	}
	if (purchaseTexture.loadFromFile("Resources/Textures/UI/PopUpWindow/purchaseButton.png"))
	{
		purchaseBody.setTexture(&purchaseTexture);
		purchaseBody.setTextureRect(sf::IntRect(static_cast<int>(canPurchase) * purchaseTexture.getSize().x / 2, 0, purchaseTexture.getSize().x / 2, purchaseTexture.getSize().y));
	}
	if (moveTexture.loadFromFile("Resources/Textures/UI/PopUpWindow/moveButton.png"))
	{
		moveBody.setTexture(&moveTexture);
		moveBody.setTextureRect(sf::IntRect(0, 0, moveTexture.getSize().x / 2, moveTexture.getSize().y));
	}
	if (closeTexture.loadFromFile("Resources/Textures/UI/PopUpWindow/close.png"))
	{
		closeBody.setTexture(&closeTexture);
	}
	if (tagTexture.loadFromFile("Resources/Textures/UI/PopUpWindow/tag.png"))
	{
		for (auto& tagBody : tagsBody)
		{
			tagBody.setTexture(&tagTexture);
		}
	}
}

void PopUpWindow::draw(sf::RenderWindow* window)
{

	window->draw(windowBody);
	window->draw(nameText);
	window->draw(priceText);
	window->draw(closeBody);
	window->draw(purchaseBody);
	window->draw(moveBody);
	window->draw(ownershipBody);
	window->draw(capitalText);
	window->draw(transactionText);
	window->draw(prevRevenueText);
	window->draw(moveText);
	for (int i = 0; i < tagNum; i++)
	{
		window->draw(tagsBody.at(i));
		window->draw(tagsText.at(i));
	}
}
