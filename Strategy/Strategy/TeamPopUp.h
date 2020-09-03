#pragma once
#include "InfoBox.h"
class TeamPopUp
{
	sf::RectangleShape windowBody;
	sf::RectangleShape closeBody;
	InfoBox infoBox;

	sf::Text nameText;
	sf::Text destText;
	sf::Text cashText;
	sf::Text capitalText;

	sf::Font* font;
	sf::Texture windowTexture;
	sf::Texture closeTexture;

	Communicator* communicator;

	Player* player;
	Player* team;

	void checkCloseWindow(MouseData* mouseData);
	void updateText();
public:
	bool activated;
	TeamPopUp(Player* player, sf::Font* font, Communicator* communicator);
	void draw(sf::RenderWindow* window);
	void setTeam(Player* team);
	void initDraw(const sf::View& view); //only called when this window is sure to be drawn
	void checkMouseData(MouseData* mouseData);
	void update(MouseData* mouseData);
	void setWindow(sf::RenderWindow* window);
};

