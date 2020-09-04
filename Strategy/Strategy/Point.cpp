#include "Point.h"
#include "Player.h"

//Point::Point() :
//	body(20.f), ownerID(0), id(-1), capital(-1), prevRevenue(-1), transactionTimes(0), price(-1), updatePopUpInfo(false), bankrupt(false), texture()
//{
//	body.setOrigin(body.getRadius(), body.getRadius());
//	body.setPosition(0, 0);
//	body.setFillColor(sf::Color::Red);
//}

Point::Point(float x, float y, std::wstring name, int id, sf::Texture& texture, sf::Font* font) :
	body(sf::Vector2f(40.f, 60.f)), name(name), ownerID(0), id(id), capital(-1), prevRevenue(-1), transactionTimes(0), price(-1), updatePopUpInfo(false), bankrupt(false), texture(texture), font(font), moveTime(0),
	text("", *font, 25)
{
	body.setOrigin(body.getSize().x / 2, body.getSize().y);
	body.setPosition(x, y - 30.f);
	//this->texture.setSmooth(true);
	body.setTexture(&this->texture);

	text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
	text.setPosition(body.getPosition().x, body.getPosition().y - body.getSize().y * 0.77f);
	//text.setCharacterSize(30);
	text.setFillColor(sf::Color::Black);
}

void Point::draw(sf::RenderWindow* window)
{
	if (!bankrupt)
	{
		window->draw(body);
		window->draw(text);
	}
}

bool Point::clicked(float mouseX, float mouseY)
{
	if (!bankrupt)
	{
		if (std::abs(body.getPosition().x - mouseX) <= body.getSize().x / 2 && mouseY >= body.getPosition().y - body.getSize().y && mouseY <= body.getPosition().y)
		{
			return true;
		}
	}
	return false;
}

void Point::purchased(Player* player)
{
	ownerID = player->getID();
	this->text.setString(std::to_string(ownerID));
	centerText(text, text.getPosition());
}


