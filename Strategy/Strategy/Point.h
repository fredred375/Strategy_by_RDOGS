#pragma once
#include "MouseData.h"
#include "centerText.h"

enum class ShopTag
{
	WENZHOU = 0,

	SHIDA = 1,

	YIYIBA = 2,

	GONGGUAN = 3,

	FASTFOOD = 4,

	STARBUCKS = 5,

	CURRY = 6,

	RAMEN = 7,

	HOTPOT = 8,

	ICE = 9,

	CHAMONIX = 10,

	MALA = 11,

	numShopTags
};

class Player;
class Point
{
private:
	sf::RectangleShape body;
	sf::Texture& texture;
	sf::Text text;
	sf::Font* font;
	std::wstring name;
	std::list<ShopTag> tag;
	//sf::Clock notPurchasableClock;
	int id;
	int ownerID;
	int capital;
	int price;
	int prevRevenue;
	int transactionTimes;
public:
	bool updatePopUpInfo;
	bool requestInfo;
	bool bankrupt;
	//Point();
	Point(float x, float y, std::wstring name, int id, sf::Texture& texture, sf::Font* font);
	std::wstring getName() const { return name; }
	void draw(sf::RenderWindow* window);
	bool clicked(float mouseX, float mouseY);
	int getOwnerID() const { return ownerID; }
	void setOwnerID(int ownerID) { 
		this->ownerID = ownerID;
		this->text.setString(std::to_string(ownerID));
		centerText(text, text.getPosition());
	}
	sf::Vector2f getPosition() const { return body.getPosition(); }
	int getID() const { return id; }
	int getPrice() const { return price; }
	void setPrice(int price) { this->price = price; }
	int getCapital() const{ return capital; }
	void setCapital(int capital) { this->capital = capital; }
	int getPrevRevenue() const { return prevRevenue; }
	void setPrevRevenue(int prevRevenue) { this->prevRevenue = prevRevenue; }
	int getTransactionTimes() const { return transactionTimes; }
	void setTransactionTimes(int transactionTimes) { this->transactionTimes = transactionTimes; }
	void purchased(Player* player);
	void setTag(int tag) { this->tag.push_back(static_cast<ShopTag>(tag)); };
	void setFont(sf::Font* font) {
		this->font = font; 
		text.setFont(*this->font);
	};
	void setTexture(sf::Texture& texture) { this->body.setTexture(&texture); };
};

