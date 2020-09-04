#include "PointHoverUI.h"

PointHoverUI::PointHoverUI(sf::Font* font) :
	text("", *font, 1), activated(false), point(nullptr)
{
	body.setFillColor(sf::Color::Black);
}

void PointHoverUI::setPoint(Point* point)
{
	this->point = point;
	text.setString(point->getName());
}

void PointHoverUI::initDraw(sf::View view)
{
	body.setSize(view.getSize() / 10.f);
	body.setOrigin(body.getSize());
	body.setPosition(point->getPosition() - sf::Vector2f(0.f, point->getSize().y * 0.66f));
	text.setCharacterSize(body.getSize().x / 10.f);
	text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
	text.setPosition(body.getPosition() - body.getSize() / 2.f);
}

void PointHoverUI::draw(sf::RenderWindow* window)
{
	window->draw(body);
	window->draw(text);
}
