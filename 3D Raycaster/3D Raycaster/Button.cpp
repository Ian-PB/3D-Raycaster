#include "Button.h"
#include <iostream>


Button::Button()
{
	// Button Sprite
	if (!texture.loadFromFile("ASSETS\\IMAGES\\Button.png"))
	{
		std::cout << "problem loading Button" << std::endl;
	}

	texture.setSmooth(true);
	sprite.setTexture(texture);
}

void Button::setup(sf::Vector2f t_pos, float t_width, float t_height,  sf::Color t_color)
{
	// Get the dimensions
	width = t_width;
	height = t_height;


	body.setSize({ width, height });
	body.setFillColor(t_color);

	body.setOrigin({ width / 2, height / 2 });
	sprite.setOrigin({ width / 2, height / 2 });

	position = t_pos;
	body.setPosition(position);
	sprite.setPosition(position);
}

bool Button::checkForMouse(sf::Vector2f t_mousePos)
{
	// Check if the mouse is within the button on the x-axis
	if (t_mousePos.x >= position.x - ((width) / 2) && t_mousePos.x <= position.x + ((width) / 2))
	{
		// Check if the mouse is within the button on the y-axis
		if (t_mousePos.y <= position.y + (height / 2) && t_mousePos.y >= position.y - (height / 2))
		{
			// if colliding
			colliding = true;

			// Increase size
			if (body.getScale().x < 1.4f)
			{
				scale += 0.1f;
				body.setScale(scale, scale);
				sprite.setScale(scale, scale);
			}

			return colliding;
		}
		else
		{
			// Decrease size
			if (body.getScale().x > 1.0f)
			{
				scale -= 0.1f;
				body.setScale(scale, scale);
				sprite.setScale(scale, scale);
			}
		}
	}
	else
	{
		// Decrease size
		if (body.getScale().x > 1.0f)
		{
			scale -= 0.1f;
			body.setScale(scale, scale);
			sprite.setScale(scale, scale);
		}
	}

	// if not colliding 
	colliding = false;

	return colliding; // if not colliding
}

void Button::changeColor(sf::Color t_color)
{
	body.setFillColor(t_color);
}
