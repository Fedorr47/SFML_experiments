#include "stdafx.h"

#include "Game/CustomLogic.h"

CustomLogic::CustomLogic()
{
}

void CustomLogic::Render(sf::RenderWindow& InWindow)
{
	sf::CircleShape circle(10);
	circle.setFillColor(sf::Color::Green);
	circle.setPosition(10, 20);
	InWindow.draw(circle);
}