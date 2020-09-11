#include "TeamPopUp.h"

void TeamPopUp::checkCloseWindow(MouseData* mouseData)
{
	if (mouseData->leftClicked)
	{
		if (mouseData->mousePos.x <= closeBody.getPosition().x + closeBody.getSize().x && mouseData->mousePos.x >= closeBody.getPosition().x)
		{
			if (mouseData->mousePos.y <= closeBody.getPosition().y + closeBody.getSize().y && mouseData->mousePos.y >= closeBody.getPosition().y)
			{
				//closed
				activated = false;
				team = nullptr;
			}
		}
	}
}

void TeamPopUp::updateText()
{
	if (team->getPoint())
	{
		destText.setString(team->getPoint()->getName());
	}
	else
	{
		destText.setString("-1");
	}
	centerTextRight(destText, windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x * 0.461f, windowBody.getSize().y * 0.34f));

	cashText.setString(std::to_wstring(team->getCash()));
	centerTextRight(cashText, windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x * 0.461f, windowBody.getSize().y * 0.515f));

	capitalText.setString(std::to_wstring(team->getCap()));
	centerTextRight(capitalText, windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x * 0.461f, windowBody.getSize().y * 0.695f));
}

TeamPopUp::TeamPopUp(Player* player, sf::Font* font, Communicator* communicator) :
	player(player), font(font), communicator(communicator), activated(false), team(nullptr), 
	infoBox(font, sf::View(sf::Vector2f(-240.f, 980.f), sf::Vector2f(400.f, 600.f)), sf::FloatRect(1270.f / 1920.f, 295.f / 1080.f, 400.f / 1920.f, 600.f / 1080.f)),
	nameText(L"第0組", *font, 60),
	destText(L"", *font, 36),
	cashText("0", *font, 36),
	capitalText(L"", *font, 36)
{
	nameText.setStyle(sf::Text::Bold);
	destText.setStyle(sf::Text::Bold);
	cashText.setStyle(sf::Text::Bold);
	capitalText.setStyle(sf::Text::Bold);
	destText.setFillColor(sf::Color(26, 115, 232));
	cashText.setFillColor(sf::Color(26, 115, 232));
	capitalText.setFillColor(sf::Color(26, 115, 232));
	if (windowTexture.loadFromFile("Resources/Textures/UI/teamPopUp.png"))
	{
		windowBody.setTexture(&windowTexture);
	}
	if (closeTexture.loadFromFile("Resources/Textures/UI/PopUpWindow/close.png"))
	{
		closeBody.setTexture(&closeTexture);
	}
}

void TeamPopUp::draw(sf::RenderWindow* window)
{
	window->draw(this->windowBody);
	window->draw(this->closeBody);
	window->draw(nameText);
	window->draw(destText);
	window->draw(cashText);
	window->draw(capitalText);
	infoBox.draw(window);
	//window->draw(allText)
}

void TeamPopUp::setTeam(Player* team)
{
	this->team = team;
	communicator->requestTeamInformation(team);
}

void TeamPopUp::initDraw(const sf::View& view)
{
	windowBody.setSize(view.getSize() * 0.75f);
	windowBody.setPosition(view.getCenter() - windowBody.getSize() / 2.f);

	closeBody.setSize(sf::Vector2f(windowBody.getSize().x * 30.f / 1080.f, windowBody.getSize().y * 30.f / 810.f));
	closeBody.setPosition(windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x * 1023.f / 1080.f, windowBody.getSize().y * 23.f / 810.f));

	nameText.setString(L"第" + std::to_wstring(team->getID()) + L"組");
	nameText.setCharacterSize(windowBody.getSize().x / 15.f);
	centerText(nameText, windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x * 285.f / 1080.f, windowBody.getSize().y * 125.f / 810.f));

	destText.setString(L"載入中");
	destText.setCharacterSize(windowBody.getSize().x / 32.f);
	centerTextRight(destText, windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x * 0.461f, windowBody.getSize().y * 0.34f));

	cashText.setString(L"載入中");
	cashText.setCharacterSize(windowBody.getSize().x / 25.f);
	centerTextRight(cashText, windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x * 0.461f, windowBody.getSize().y * 0.515f));

	capitalText.setString(L"載入中");
	capitalText.setCharacterSize(windowBody.getSize().x / 25.f);
	centerTextRight(capitalText, windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x * 0.461f, windowBody.getSize().y * 0.695f));

}

void TeamPopUp::checkMouseData(MouseData* mouseData)
{
	checkCloseWindow(mouseData);
}

void TeamPopUp::update(MouseData* mouseData)
{
	if (team->updateTeamUI)
	{
		infoBox.updateInfo(team);
		updateText();
		team->updateTeamUI = false;
	}
	checkMouseData(mouseData);
	infoBox.update(mouseData);
}

void TeamPopUp::setWindow(sf::RenderWindow* window)
{
	infoBox.setWindow(window);
}
