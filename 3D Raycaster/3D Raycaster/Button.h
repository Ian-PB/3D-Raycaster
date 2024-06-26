#pragma once

#include <SFML/Graphics.hpp>

class Button
{
public:

	Button();

	sf::RectangleShape getBody() { return body; }
	sf::Sprite getSprite() { return sprite; }

	void setup(sf::Vector2f t_pos, float t_width, float t_height, sf::Color t_color);

	bool checkForMouse(sf::Vector2f t_mousePos);

	void changeColor(sf::Color t_color);


private:

	sf::Sprite sprite;
	sf::Texture texture;

	sf::RectangleShape body;
	float width;
	float height;

	sf::Vector2f position;

	bool colliding = false;

	float scale = 1;

};