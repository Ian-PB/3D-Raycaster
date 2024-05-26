#include "Block.h"


void Block::spawn(int t_size, sf::Vector2f t_pos)
{
	position = t_pos;
	body.setPosition(position);
	sprite.setPosition(position);

	size = t_size;

	body.setSize({ size, size });
	body.setOrigin(size / 2, size / 2);

	sprite.setOrigin(size / 2, size / 2);
	sprite.setTextureRect(sf::IntRect{ 0, 0, t_size, t_size });
	sprite.setColor({ 25, 25, 25, 255 });


	active = true;
}
