#include "Door.h"

Door::Door()
{
	body.setFillColor(sf::Color::Blue);

	

	// Set trigger hitbox
	for (int i = 0; i < 4; i++)
	{
		interactAreas[i].setOrigin({ 35, 35 });
		interactAreas[i].setSize({ 70, 70 });
		interactAreas[i].setFillColor(sf::Color::Transparent);
		interactAreas[i].setOutlineColor(sf::Color::Blue);
		interactAreas[i].setOutlineThickness(2);
	}
}

void Door::setup()
{
	for (int i = 0; i < 4; i++) // set default
	{
		interactAreasPos[i] = position;
	}
	interactAreasPos[0].y -= 50; // Up
	interactAreasPos[1].y += 50; // Down
	interactAreasPos[2].x -= 50; // Left
	interactAreasPos[3].x += 50; // Right

	for (int i = 0; i < 4; i++)
	{
		interactAreas[i].setPosition(interactAreasPos[i]);
	}
}

void Door::interactCheck(sf::RectangleShape t_player)
{
	for (int i = 0; i < 4; i++)
	{
		if (t_player.getGlobalBounds().intersects(interactAreas[i].getGlobalBounds()))
		{
			canInteract = true;

			break;
		}
		else
		{
			canInteract = false;
		}
	}
}

void Door::open()
{
	if (canInteract)
	{
		active = false;
	}
}