#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

class Block
{
public:
	Block();


	void spawn(int t_size, sf::Vector2f t_pos);
	sf::RectangleShape getBody() { return body; }

	bool active = false;

protected: // Can be used in the inherited class

	sf::RectangleShape body;
	float size;

	sf::Vector2f position;

private:

};

