#pragma once
#include "MouseData.h"
class Notification
{
	sf::Sprite body;
	sf::Text titleText;
	std::vector<sf::Text> textList;
	sf::Font* font;
	sf::Texture* texture;
	float span; //second
	const float faint; //second
public:
	Notification(sf::Font* font, sf::Texture* texture);
	void update(const float& dt);
	void draw(sf::RenderWindow* window);
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition() const { return body.getPosition(); }
	void setTitle(std::wstring string) { titleText.setString(string); }
	void setString(int line, std::wstring string);
	float getSpan() const { return span; }
};

