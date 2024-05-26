#include "Wall.h"

Wall::Wall()
{
	// Floor Sprite
	if (!texture.loadFromFile("ASSETS\\IMAGES\\Floor.png"))
	{
		std::cout << "problem loading Floor" << std::endl;
	}
	texture.setRepeated(true);
	texture.setSmooth(true);
	sprite.setTexture(texture);

	body.setFillColor(sf::Color::Black);
}

void Wall::collisionDetection(Player& t_player)
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