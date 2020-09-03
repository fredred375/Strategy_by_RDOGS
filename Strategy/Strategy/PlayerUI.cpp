#include "PlayerUI.h"

void PlayerUI::updatePosText()
{
	if (player->getArrived())
	{
		if (player->getPoint())
		{
<<<<<<< HEAD
			posText.setString(L"所在地 : " + player->getPoint()->getName());
			centerText(posText, -240.f, 120.f);
=======
			posText.setString(player->getPoint()->getName());
			centerTextRight(posText, -50.f, 330.f);
>>>>>>> socket
		}
	}
	else
	{
<<<<<<< HEAD
		posText.setString(L"正在前往" + player->getPoint()->getName());
		centerText(posText, -240.f, 120.f);
=======
		posText.setString(player->getPoint()->getName());
		centerTextRight(posText, -50.f, 330.f);
>>>>>>> socket
	}
	player->updatePosUI = false;
}

void PlayerUI::updateCashText()
{
<<<<<<< HEAD
	cashText.setString(L"錢 : " + std::to_wstring(player->getCash()));
	centerText(cashText, -240.f, 190.f);
	player->updateCashUI = false;
}

PlayerUI::PlayerUI(Player* player, sf::Font* font) :
	player(player), font(font), 
	IDText(L"第" + std::to_wstring(player->getID()) + L"組", *font, 50),
	posText(L"所在地 : 起點", *font, 50),
	cashText(L"錢 : " + std::to_wstring(player->getCash()), *font, 50)
{
	body.setSize(sf::Vector2f(480.f, 1000.f));
	body.setPosition(body.getSize().x * -1.f, 0.f);
	body.setFillColor(sf::Color::Blue);
	centerText(IDText, -240.f, 50.f);
	centerText(posText, -240.f, 120.f);
	centerText(cashText, -240.f, 190.f);
=======
	cashText.setString(std::to_wstring(player->getCash()));
	centerTextRight(cashText, -50.f, 412.f);
	player->updateCashUI = false;
}

void PlayerUI::updateCapText()
{
	capText.setString(std::to_wstring(player->getCap()));
	centerTextRight(capText, -50.f, 500.f);
	player->updateCapUI = false;
}

void PlayerUI::updateTimeText()
{
	int time = static_cast<int>(this->time);
	int hour = static_cast<int>(time / 3600);
	int minute = static_cast<int>((time - hour * 3600) / 60);
	int second = static_cast<int>(time - hour * 3600 - minute * 60);
	std::string text;
	if (hour >= 10)
	{
		text = std::to_string(hour) + ":";
	}
	else if (hour >= 0)
	{
		text = "0" + std::to_string(hour) + ":";
	}
	if (minute >= 10)
	{
		text += (std::to_string(minute) + ":");
	}
	else if (minute >= 0)
	{
		text += ("0" + std::to_string(minute) + ":");
	}
	if (second >= 10)
	{
		text += std::to_string(second);
	}
	else if(second >= 0)
	{
		text += ("0" + std::to_string(second));
	}
	timeText.setString(text);
}

PlayerUI::PlayerUI(Player* player, sf::Font* font) :
	player(player), font(font), window(nullptr),
	IDText(L"第" + std::to_wstring(player->getID()) + L"組", *font, 60),
	posText(L"起點", *font, 30),
	cashText(std::to_wstring(player->getCash()), *font, 30),
	capText(std::to_wstring(player->getCap()), *font, 30),
	infoBox(font), timeText("00:00:00", *font, 80), time(0)
{
	body.setSize(sf::Vector2f(480.f, 1000.f));
	body.setPosition(body.getSize().x * -1.f, 0.f);
	if (bodyTexture.loadFromFile("Resources/Textures/UI/PlayerUI/PlayerUI.png"))
	{
		body.setTexture(&bodyTexture);
	}
	else
	{
		std::cout << "Failed to load texture : PlayerUI.png" << std::endl;
	}
	IDText.setStyle(sf::Text::Bold);
	centerText(IDText, -240.f, 240.f);
	posText.setFillColor(sf::Color(26, 115, 232));
	posText.setStyle(sf::Text::Bold);
	centerTextRight(posText, -50.f, 330.f);
	cashText.setFillColor(sf::Color(26, 115, 232));
	cashText.setStyle(sf::Text::Bold);
	centerTextRight(cashText, -50.f, 412.f);
	capText.setFillColor(sf::Color(26, 115, 232));
	capText.setStyle(sf::Text::Bold);
	centerTextRight(capText, -50.f, 500.f);
	timeText.setFillColor(sf::Color::White);
	timeText.setStyle(sf::Text::Bold);
	centerText(timeText, -240.f, 85.f);
>>>>>>> socket
}

void PlayerUI::draw(sf::RenderWindow* window)
{
	window->draw(body);
	window->draw(IDText);
	window->draw(posText);
	window->draw(cashText);
<<<<<<< HEAD
}

void PlayerUI::update(MouseData* mouseData)
{
=======
	window->draw(capText);
	window->draw(timeText);
	infoBox.draw(window);
}

void PlayerUI::update(MouseData* mouseData, float dt)
{
	time += dt;
>>>>>>> socket
	if (player->updatePosUI)
	{
		updatePosText();
	}
	if (player->updateCashUI)
	{
		updateCashText();
	}
<<<<<<< HEAD
=======
	if (player->updateCapUI)
	{
		updateCapText();
	}
	if (player->updateInfoBox)
	{
		infoBox.updateInfo(player);
	}

	updateTimeText();

	infoBox.update(mouseData);
}

void PlayerUI::setWindow(sf::RenderWindow* window)
{
	this->window = window;
	infoBox.setWindow(window);
>>>>>>> socket
}

