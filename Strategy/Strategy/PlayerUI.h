#pragma once
#include "Player.h"
#include "centerText.h"
class PlayerUI
{
private:
	sf::RectangleShape body;
	sf::Font* font;
	sf::Text IDText;
	sf::Text posText;
	sf::Text cashText;
	Player* player;

	void updatePosText();
	void updateCashText();
public:
	PlayerUI(Player* player, sf::Font* font);
	void draw(sf::RenderWindow* window);
	void checkMouseData(MouseData* mouseData);
	void update(MouseData* mouseData);
};

