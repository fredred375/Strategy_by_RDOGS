#include "PopUpWindow.h"

void PopUpWindow::setPosition(sf::Vector2f pos)
{
	windowBody.setPosition(pos);
	text.setPosition(pos + windowBody.getSize() / 2.f);
}

void PopUpWindow::setString(const std::wstring& s)
{
	text.setString(s);
}

void PopUpWindow::setPoint(const Point& point)
{
	text.setString(point.getName());
}

void PopUpWindow::initDraw(sf::RenderWindow* window)
{
	sf::View view = window->getView();
	windowBody.setSize(view.getSize() * 0.75f);
	windowBody.setPosition(view.getCenter() - windowBody.getSize() / 2.f);
	text.setCharacterSize(windowBody.getSize().x / 10.f);
	text.setOrigin(sf::Vector2f(text.getLocalBounds().width, text.getLocalBounds().height) / 2.f);
	text.setPosition(view.getCenter());
	closeBody.setSize(windowBody.getSize() / 10.f);
	closeBody.setOrigin(closeBody.getSize() / 2.f);
	closeBody.setPosition(windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x, 0.f));
}

void PopUpWindow::checkMouseData(MouseData* mouseData)
{
	checkCloseWindow(mouseData);
}

void PopUpWindow::update(MouseData* mouseData)
{
	checkMouseData(mouseData);
}

void PopUpWindow::checkCloseWindow(MouseData* mouseData)
{
	if (mouseData->leftClicked)
	{
		sf::Vector2f windowTopRight(windowBody.getPosition() + sf::Vector2f(windowBody.getSize().x, 0.f));
		if (mouseData->mousePos.x <= windowTopRight.x + windowBody.getSize().x / 10.f && mouseData->mousePos.x >= windowTopRight.x - windowBody.getSize().x / 10.f)
		{
			if (mouseData->mousePos.y <= windowTopRight.y + windowBody.getSize().y / 10.f && mouseData->mousePos.y >= windowTopRight.y - windowBody.getSize().y / 10.f)
			{
				//closed
				activated = false;
			}
		}
	}
}

PopUpWindow::PopUpWindow() :
	activated(false)
{
	windowBody.setFillColor(sf::Color::Black);
	text.setString("Test");
}

PopUpWindow::PopUpWindow(sf::Font* font) :
	activated(false)
{
	windowBody.setFillColor(sf::Color::Black);
	text = sf::Text("Test", *font, 1);
}

void PopUpWindow::draw(sf::RenderWindow* window)
{

	window->draw(windowBody);
	window->draw(text);
	window->draw(closeBody);
}
