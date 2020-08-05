#include "centerText.h"

void centerText(sf::Text& text, float x, float y)
{
	text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
	text.setPosition(x, y);
}

void centerText(sf::Text& text, sf::Vector2f pos)
{
	text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
	text.setPosition(pos);
}
