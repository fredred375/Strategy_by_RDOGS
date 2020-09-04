#pragma once
#include "centerText.h"
#include "Communicator.h"
class PopUpWindow
{
private:
	sf::RectangleShape windowBody;
	sf::RectangleShape closeBody;
	sf::RectangleShape ownershipBody;

	sf::RectangleShape purchaseBody;
	sf::RectangleShape moveBody;

	std::vector<sf::RectangleShape> tagsBody;
	std::vector<sf::Text> tagsText;
	int tagNum;


	sf::Font* font;
	sf::Texture windowTexture;
	sf::Texture ownershipTexture;
	sf::Texture closeTexture;
	sf::Texture purchaseTexture;
	sf::Texture moveTexture;
	sf::Texture tagTexture;
	sf::Text nameText;
	sf::Text priceText;
	sf::Text transactionText;
	sf::Text capitalText;
	sf::Text prevRevenueText;
	sf::Text moveText;
	Communicator* communicator;
	Point* point;
	Player* player;
	bool canPurchase;
	void checkCloseWindow(MouseData* mouseData);
	void checkPurchase(MouseData* mouseData);
	void checkMove(MouseData* mouseData);
	void updateOwnership();
	void updatePurchaseButton();
	void updateMoveButton();
	void updateText();
public:
	bool activated;
	PopUpWindow(Player* player, sf::Font* font, Communicator* communicator);
	void draw(sf::RenderWindow* window);
	void setPoint(Point* point);
	void initDraw(const sf::View& view); //only called when this window is sure to be drawn
	void checkMouseData(MouseData* mouseData);
	void update(MouseData* mouseData);
};

