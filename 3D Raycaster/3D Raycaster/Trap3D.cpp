#include "Trap3D.h"

Trap3D::Trap3D()
{
	body.setFillColor(sf::Color::Red);
}

void Trap3D::collisionDetection(Player& t_player, sf::Vector2f t_spawnPos)
{
	if (t_player.getBody().getGlobalBounds().intersects(body.getGlobalBounds()))
	{
		t_player.setPos(t_spawnPos);
	}
}
