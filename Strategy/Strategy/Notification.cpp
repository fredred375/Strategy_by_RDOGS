#include "Notification.h"
#include "centerText.h"

Notification::Notification(sf::Font* font, sf::Texture* texture) : body(*texture), font(font), texture(texture), textList(4 , sf::Text(L"", *font, 36)), span(10.f), faint(2.5f), titleText(L"", *font, 48)
{
	titleText.setStyle(sf::Text::Bold);
}

void Notification::update(const float& dt)
{
	if (span > 0)
	{
		span -= dt;
		if(span < faint)
		{
			body.setColor(sf::Color(255, 255, 255, 255 * span / faint));
			titleText.setFillColor(sf::Color(255, 255, 255, 255 * span / faint));
			for (auto& text : textList)
			{
				text.setFillColor(sf::Color(255, 255, 255, 255 * span / faint));
			}
		}
	}
}

void Notification::draw(sf::RenderWindow* window)
{
	window->draw(body);
	window->draw(titleText);
	for (const auto& text : textList)
	{
		window->draw(text);
	}
}

void Notification::setPosition(sf::Vector2f pos)
{
	body.setPosition(pos);
	titleText.setPosition(pos.x + 75.f, pos.y + 55.f);
	for (int i = 0; i < textList.size(); i++)
	{
		centerTextLeft(textList.at(i), pos.x + 75.f, pos.y + 150.f + i * 54.f);
	}
}

void Notification::setString(int line, std::wstring string)
{
	if(line > 0 && line <= textList.size())
	{ 
		textList.at(line - 1).setString(string); 
	}
	else
	{
		std::cout << "Notification setString exception : requested line out of bounds\n";
	}
}
