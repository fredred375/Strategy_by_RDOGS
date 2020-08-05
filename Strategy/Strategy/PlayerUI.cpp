#include "PlayerUI.h"

void PlayerUI::updatePosText()
{
	if (player->getArrived())
	{
		if (player->getPoint())
		{
			posText.setString(L"�Ҧb�a : " + player->getPoint()->getName());
			centerText(posText, -240.f, 120.f);
		}
	}
	else
	{
		posText.setString(L"���b�e��" + player->getPoint()->getName());
		centerText(posText, -240.f, 120.f);
	}
	player->updatePosUI = false;
}

void PlayerUI::updateCashText()
{
	cashText.setString(L"�� : " + std::to_wstring(player->getCash()));
	centerText(cashText, -240.f, 190.f);
	player->updateCashUI = false;
}

PlayerUI::PlayerUI(Player* player, sf::Font* font) :
	player(player), font(font), 
	IDText(L"��" + std::to_wstring(player->getID()) + L"��", *font, 50),
	posText(L"�Ҧb�a : �_�I", *font, 50),
	cashText(L"�� : " + std::to_wstring(player->getCash()), *font, 50)
{
	body.setSize(sf::Vector2f(480.f, 1000.f));
	body.setPosition(body.getSize().x * -1.f, 0.f);
	body.setFillColor(sf::Color::Blue);
	centerText(IDText, -240.f, 50.f);
	centerText(posText, -240.f, 120.f);
	centerText(cashText, -240.f, 190.f);
}

void PlayerUI::draw(sf::RenderWindow* window)
{
	window->draw(body);
	window->draw(IDText);
	window->draw(posText);
	window->draw(cashText);
}

void PlayerUI::update(MouseData* mouseData)
{
	if (player->updatePosUI)
	{
		updatePosText();
	}
	if (player->updateCashUI)
	{
		updateCashText();
	}
}

