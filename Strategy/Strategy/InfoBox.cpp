#include "InfoBox.h"
#include "Player.h"
#include "Point.h"

void InfoBox::checkUpperBound()
{
	if (infoBody.back().getPosition().y - boxView.getSize().y / 2.f + constants::INFO_BOX_HEIGHT < lowerBound)
	{
		upperBound = lowerBound;
	}
	else
	{
		upperBound = infoBody.back().getPosition().y - boxView.getSize().y / 2.f + constants::INFO_BOX_HEIGHT + 10.f;
	}
}

InfoBox::InfoBox(sf::Font* font) :
	boxView(sf::Vector2f(-240.f, 857.5f), sf::Vector2f(400.f, 355.f)), window(nullptr), upperBound(857.5f), lowerBound(857.5f), font(font)
{
	boxView.setViewport(sf::FloatRect((480.f - 400.f) / 480.f * 0.25f * 0.5f, 680.f / 1080.f, 400.f / 480.f * 0.25f, 355.f / 1080.f));
	infoBody.emplace_back(sf::Vector2f(constants::INFO_BOX_WIDTH, constants::INFO_BOX_HEIGHT));
	infoBody.at(0).setPosition(-430.f, 690.f);
	infoBody.at(0).setFillColor(sf::Color::White);
	textBody.push_back(sf::Text(L"目前無持有店家", *font, 30));
	textBody.front().setFillColor(sf::Color(26, 115, 232));
	textBody.front().setStyle(sf::Text::Bold);
	centerTextRight(textBody.front(), -60.f, 707.f);
	checkUpperBound();
}

InfoBox::InfoBox(sf::Font* font, sf::View view, sf::FloatRect viewport) :
	boxView(view), window(nullptr), upperBound(view.getCenter().y), lowerBound(view.getCenter().y), font(font)
{
	boxView.setViewport(viewport);
	infoBody.emplace_back(sf::Vector2f(constants::INFO_BOX_WIDTH, constants::INFO_BOX_HEIGHT));
	infoBody.at(0).setPosition(-430.f, 690.f);
	infoBody.at(0).setFillColor(sf::Color::White);
	textBody.push_back(sf::Text(L"目前無持有店家", *font, 30));
	textBody.front().setFillColor(sf::Color(26, 115, 232));
	textBody.front().setStyle(sf::Text::Bold);
	centerTextRight(textBody.front(), -60.f, 707.f);
	checkUpperBound();
}

void InfoBox::draw(sf::RenderWindow* window)
{
	window->setView(boxView);
	for (const auto& info : infoBody)
	{
		window->draw(info);
	}
	for (const auto& text : textBody)
	{
		window->draw(text);
	}
}

void InfoBox::updateInfo(Player* player)
{
	infoBody.clear();
	textBody.clear();
	std::vector<Point*> list = player->getProperties();
	for (int i = 0; i < list.size(); i++)
	{
		infoBody.emplace_back(sf::Vector2f(constants::INFO_BOX_WIDTH, constants::INFO_BOX_HEIGHT));
		infoBody.at(i).setFillColor(sf::Color::White);
		textBody.emplace_back(list.at(i)->getName(), *font, 30);
		textBody.at(i).setFillColor(sf::Color(26, 115, 232));
		textBody.at(i).setStyle(sf::Text::Bold);
		if (i == 0)
		{
			infoBody.at(i).setPosition(-430.f, 690.f);
		}
		else
		{
			infoBody.at(i).setPosition(infoBody.at(i - 1).getPosition() + sf::Vector2f(0.f, 55.f));
		}
		centerTextRight(textBody.at(i), infoBody.at(i).getPosition() + sf::Vector2f(370.f, 17.f));
	}
	if (infoBody.empty())
	{
		infoBody.emplace_back(sf::Vector2f(constants::INFO_BOX_WIDTH, constants::INFO_BOX_HEIGHT));
		infoBody.at(0).setPosition(-430.f, 690.f);
		infoBody.at(0).setFillColor(sf::Color::White);
		textBody.push_back(sf::Text(L"目前無持有店家", *font, 30));
		textBody.front().setFillColor(sf::Color(26, 115, 232));
		textBody.front().setStyle(sf::Text::Bold);
		centerTextRight(textBody.front(), -60.f, 707.f);
	}
	checkUpperBound();
}

void InfoBox::update(MouseData* mouseData)
{
	if (this->window)
	{
		if (mouseData->mousePosPixel.x >= boxView.getViewport().left * window->getSize().x && mouseData->mousePosPixel.x <= (boxView.getViewport().left + boxView.getViewport().width) * window->getSize().x)
		{
			if (mouseData->mousePosPixel.y >= boxView.getViewport().top * window->getSize().y && mouseData->mousePosPixel.y <= (boxView.getViewport().top + boxView.getViewport().height) * window->getSize().y)
			{
				if (mouseData->leftPressed && mouseData->moving)
				{
					const float boxOldMouseY = window->mapPixelToCoords(mouseData->oldMousePosPixel, boxView).y;
					const float boxMouseY = window->mapPixelToCoords(mouseData->mousePosPixel, boxView).y;
					const float deltaY = boxOldMouseY - boxMouseY;
					boxView.setCenter(boxView.getCenter() + sf::Vector2f(0.f, deltaY));
					if (boxView.getCenter().y > upperBound)
					{
						boxView.setCenter(sf::Vector2f(boxView.getCenter().x, upperBound));
					}
					else if (boxView.getCenter().y < lowerBound)
					{
						boxView.setCenter(sf::Vector2f(boxView.getCenter().x, lowerBound));
					}
					mouseData->oldMousePosPixel = mouseData->mousePosPixel;
				}
			}
		}
	}
}
