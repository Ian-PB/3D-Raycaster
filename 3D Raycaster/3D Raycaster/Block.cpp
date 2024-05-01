#include "Block.h"

Block::Block()
{
	body.setFillColor(sf::Color::White);
}

void Block::spawn(int t_size, sf::Vector2f t_pos)
{
	position = t_pos;
	body.setPosition(position);

	size = t_size - 1;

	body.setSize({ size, size });
	body.setOrigin(size / 2, size / 2);

	active = true;
}
