#pragma once

#include <SFML/Graphics.hpp>

class Block
{
public:
	Block();


	void spawn(int t_size, sf::Vector2f t_pos);
	sf::RectangleShape getBody() { return body; }

	bool active = false;

private:

	sf::RectangleShape body;
	float size;

	sf::Vector2f position;

};

