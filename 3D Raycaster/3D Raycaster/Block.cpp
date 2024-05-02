#include "Block.h"

Block::Block()
{
	body.setFillColor(sf::Color::Black);
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

void Block::collisionDetection(Player& t_player)
{

	if (t_player.getBody().getGlobalBounds().intersects(body.getGlobalBounds()))
	{
		t_player.setPos(safePos);
	}
	else
	{
		safePos = t_player.getPos();
	}
}
