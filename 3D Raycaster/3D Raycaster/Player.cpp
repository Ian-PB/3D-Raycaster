

#include "Player.h"   // include Player header file
#include <iostream>


// Default constructer
Player::Player()
{
	// Player Sprite
	if (!texture.loadFromFile("ASSETS\\IMAGES\\Player.png"))
	{
		std::cout << "problem loading Player" << std::endl;
	}

	texture.setSmooth(true);
	sprite.setTexture(texture);
	sprite.setScale(0.2, 0.2);
	sprite.setRotation((angleR * 180 / PI) - 90);


	direction = Direction::None;
}

// Check the direction you pressed in
void Player::checkDirection(bool t_2D)
{
	direction = Direction::None;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		direction = Direction::Up;
		move(t_2D);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		direction = Direction::Down;
		move(t_2D);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		// Rotate --
		angleR -= DEGREE_R * 2;

		// Correct angle
		if (angleR < -PI)
		{
			angleR = PI;
		}

		sprite.setRotation((angleR * 180 / PI) - 90);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		// Rotate ++
		angleR += DEGREE_R * 2;

		// Correct angle
		if (angleR > PI)
		{
			angleR = -PI;
		}

		sprite.setRotation((angleR * 180 / PI) - 90);
	}
}


// Moves the player in the direction pressed
void Player::move(bool t_2D)
{
	sf::Vector2f movement = { 0.0f, 0.0f };


	switch (direction)
	{
	case Direction::None:
		break;

	case Direction::Up:
		movement.x = cos(angleR) * speed;
		movement.y = sin(angleR) * speed;
		break;

	case Direction::Down:
		movement.x = cos(angleR) * -speed;
		movement.y = sin(angleR) * -speed;
		break;
	}

	position += movement;
	body.setPosition(position); // Change hitbox position
	sprite.setPosition(position); // Change hitbox position

	checkBoundries();
}


// Keeps the player within the bounds of the screen
void Player::checkBoundries()
{
	if (position.x < size / 2)
	{
		position.x = size / 2;
	}
	else if (position.x > SCREEN_WIDTH - (size / 2))
	{
		position.x = SCREEN_WIDTH - (size / 2);
	}

	if (position.y < size / 2)
	{
		position.y = size / 2;
	}
	else if (position.y > SCREEN_HEIGHT - (size / 2))
	{
		position.y = SCREEN_HEIGHT - (size / 2);
	}
}

// Sets up the enemy and needed assets for the enemy
void Player::setup(sf::Vector2f t_pos)
{
	position = t_pos;

	// Body
	body.setPosition(position);
	body.setFillColor(sf::Color::Blue);
	body.setSize({ size, size });
	body.setOrigin({ size / 2.0f, size / 2.0f });

	sprite.setPosition(position);
	sprite.setOrigin({ 150 / 2.0f, 150 / 2.0f });
}

