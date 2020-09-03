#pragma once
#include "Communicator.h"
#include "centerText.h"
class Player;
class InfoBox
{
private:
	sf::View boxView;

	sf::RenderWindow* window;

	const float lowerBound;
	float upperBound;

	sf::Font* font;

	std::vector<sf::RectangleShape> infoBody;
	std::vector<sf::Text> textBody;
	void checkUpperBound();
public:
	InfoBox(sf::Font* font);
	InfoBox(sf::Font* font, sf::View boxView, sf::FloatRect viewport);
	void draw(sf::RenderWindow* window);
	void updateInfo(Player* player);
	void update(MouseData* mouseData);
	void setWindow(sf::RenderWindow* window) { this->window = window; }
};

