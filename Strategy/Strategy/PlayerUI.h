#pragma once
<<<<<<< HEAD
#include "Player.h"
=======
#include "InfoBox.h"
>>>>>>> socket
#include "centerText.h"
class PlayerUI
{
private:
	sf::RectangleShape body;
	sf::Font* font;
	sf::Text IDText;
	sf::Text posText;
	sf::Text cashText;
<<<<<<< HEAD
	Player* player;

	void updatePosText();
	void updateCashText();
public:
	PlayerUI(Player* player, sf::Font* font);
	void draw(sf::RenderWindow* window);
	void checkMouseData(MouseData* mouseData);
	void update(MouseData* mouseData);
=======
	sf::Text capText;
	Player* player;

	float time;
	sf::Text timeText;

	sf::Texture bodyTexture;

	sf::RenderWindow* window;

	InfoBox infoBox;

	void updatePosText();
	void updateCashText();
	void updateCapText();
	void updateTimeText();
public:
	PlayerUI(Player* player, sf::Font* font);
	void draw(sf::RenderWindow* window);
	void update(MouseData* mouseData, float dt);
	void setWindow(sf::RenderWindow* window);
	void setTime(int time) { this->time = time; }
>>>>>>> socket
};

