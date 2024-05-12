#pragma once

#include <SFML/Graphics.hpp>
#include "Wall.h"


class Door : public Wall
{
public:
	Door();
	void setup();

	void interactCheck(sf::RectangleShape t_player);
	bool open();

	sf::RectangleShape interactAreas[4];

private:

	sf::Vector2f interactAreasPos[4];

	bool canInteract = false;
};

