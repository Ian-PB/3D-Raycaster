#include "Trap.h"

Trap::Trap()
{
	body.setFillColor(sf::Color::Red);
}

void Trap::collisionDetection(Player& t_player, sf::Vector2f t_spawnPos)
{
	if (t_player.getBody().getGlobalBounds().intersects(body.getGlobalBounds()))
	{
		t_player.setPos(t_spawnPos);
	}
}

