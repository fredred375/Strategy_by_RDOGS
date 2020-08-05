#include "PopUpWindow.h"

void PopUpWindow::setString(const std::wstring& s)
{
	nameText.setString(s);
}

void PopUpWindow::setPoint(Point* point)
{
	this->point = point;
	nameText.setString(point->getName());
	priceText.setString(L"價格 : " + std::to_wstring(point->getPrice()));
	if (point->getOwner())
	{
		ownerText.setString(L"持有者 : 第" + std::to_wstring(point->getOwner()->getID()) + L"組");
		if (point->getOwner() == player)
		{
			purchaseText.setString(L"已持有");
		}
		else
		{
			purchaseText.setString(L"購買");
		}
	}
	else
	{
		ownerText.setString(L"持有者 : 無");
		purchaseText.setString(L"購買");
	}
	if (player->getPoint() == point && player->getArrived() && player->getCash() >= point->getPrice())
	{
		purchaseBody.setFillColor(sf::Color::White);
		canPurchase = true;
	}
	else
	{
		purchaseBody.setFillColor(sf::Color(128, 128, 128));
		canPurchase = false;
	}
}

void PopUpWindow::initDraw(const sf::View& view)
{
	windowBody.setSize(view.getSize() * 0.75f);
	windowBody.setPosition(view.getCenter() - windowBody.getSize() / 2.f);

	closeBody.setSize(windowBody.getSize() / 10.f);
	closeBody.setOrigin(closeBody.getSize() / 2.f);
	closeBody.setPosition(windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x, 0.f));

	purchaseBody.setSize(sf::Vector2f(windowBody.getSize().x / 4.f, windowBody.getSize().y / 6.f));
	purchaseBody.setOrigin(purchaseBody.getSize() / 2.f);
	purchaseBody.setPosition(windowBody.getPosition().x + windowBody.getSize().x / 2.f, windowBody.getPosition().y + windowBody.getSize().y / 10.f * 8.6f);

	nameText.setCharacterSize(windowBody.getSize().x / 10.f);
	centerText(nameText, windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x / 2.f, windowBody.getSize().y / 10.f));

	priceText.setCharacterSize(windowBody.getSize().x / 15.f);
	centerText(priceText, windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x / 2.f, windowBody.getSize().y / 10.f * 2.5f));

	ownerText.setCharacterSize(windowBody.getSize().x / 15.f);
	centerText(ownerText, windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x / 2.f, windowBody.getSize().y / 10.f * 3.5f));

	purchaseText.setCharacterSize(windowBody.getSize().x / 15.f);
	centerText(purchaseText, purchaseBody.getPosition());
}

void PopUpWindow::checkMouseData(MouseData* mouseData)
{
	checkCloseWindow(mouseData);
	if (canPurchase)
	{
		checkPurchase(mouseData);
	}
}

void PopUpWindow::update(MouseData* mouseData)
{
	if (player->getCash() >= point->getPrice())
	{
		if (player->getPoint() == point && player->getArrived())
		{
			if (!canPurchase)
			{
				purchaseBody.setFillColor(sf::Color::White);
			}
			canPurchase = true;
		}
		else
		{
			if (canPurchase)
			{
				purchaseBody.setFillColor(sf::Color(128, 128, 128));
			}
			canPurchase = false;
		}
	}
	else
	{
		if (canPurchase)
		{
			purchaseBody.setFillColor(sf::Color(128, 128, 128));
		}
		canPurchase = false;
	}
	checkMouseData(mouseData);
}

void PopUpWindow::checkCloseWindow(MouseData* mouseData)
{
	if (mouseData->leftClicked)
	{
		sf::Vector2f windowTopRight(windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x, 0.f));
		if (mouseData->mousePos.x <= windowTopRight.x + windowBody.getSize().x / 20.f && mouseData->mousePos.x >= windowTopRight.x - windowBody.getSize().x / 20.f)
		{
			if (mouseData->mousePos.y <= windowTopRight.y + windowBody.getSize().y / 20.f && mouseData->mousePos.y >= windowTopRight.y - windowBody.getSize().y / 20.f)
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
	if (mouseData->leftClicked)
	{
		sf::Vector2f buttonCenter = purchaseBody.getPosition();
		if (mouseData->mousePos.x <= buttonCenter.x + purchaseBody.getSize().x / 2.f && mouseData->mousePos.x >= buttonCenter.x - purchaseBody.getSize().x / 2.f)
		{
			if (mouseData->mousePos.y <= buttonCenter.y + purchaseBody.getSize().y / 2.f && mouseData->mousePos.y >= buttonCenter.y - purchaseBody.getSize().y / 2.f)
			{
				//purchased
				player->purchase(point);
				purchaseText.setString(L"已購入");
				purchaseBody.setFillColor(sf::Color(128, 128, 128));
				centerText(purchaseText, purchaseText.getPosition());
				ownerText.setString(L"持有者 : 第" + std::to_wstring(point->getOwner()->getID()) + L"組");
				centerText(ownerText, ownerText.getPosition());
			}
		}
	}
}

PopUpWindow::PopUpWindow(Player* player, sf::Font* font) :
	activated(false), font(font), player(player), point(nullptr), canPurchase(false)
{
	windowBody.setFillColor(sf::Color::Black);
	nameText.setFont(*font);
	priceText.setFont(*font);
	ownerText.setFont(*font);
	purchaseText.setFont(*font);
	purchaseText.setFillColor(sf::Color::Black);
}

void PopUpWindow::draw(sf::RenderWindow* window)
{

	window->draw(windowBody);
	window->draw(nameText);
	window->draw(priceText);
	window->draw(ownerText);
	window->draw(closeBody);
	window->draw(purchaseBody);
	window->draw(purchaseText);
}
