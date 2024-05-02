

#include "Player.h"   // include Player header file
#include <iostream>


// Default constructer
Player::Player()
{
	direction = Direction::None;
}

// Check the direction you pressed in
void Player::checkDirection()
{
	direction = Direction::None;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		direction = Direction::Up;
		move();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		direction = Direction::Down;
		move();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction = Direction::Left;
		move();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction = Direction::Right;
		move();
	}
}

// Checks the mouse position and rotates the player to face that position
void Player::rotateToMouse(sf::Vector2f t_mousePos)
{
	// Rotates the player to the mouse
	float angleD; // Degrees
	sf::Vector2f line;

	line = t_mousePos - position;
	angleR = std::atan2f(line.y, line.x); // Find the angle of the line in radians


	angleD = angleR * 180.0f / PI;     // Convert to degrees
	body.setRotation(angleR + 90.0f);  // Rotate the body

	previousXPos = line.x;
}

// Moves the player in the direction pressed
void Player::move()
{
	sf::Vector2f movement = { 0.0f, 0.0f };

	switch (direction)
	{
	case Direction::None:
		break;

	case Direction::Up:
		movement.y = -speed;
		break;

	case Direction::Down:
		movement.y = speed;
		break;

	case Direction::Left:
		movement.x = -speed;
		break;

	case Direction::Right:
		movement.x = speed;
		break;
	}
	position += movement;
	body.setPosition(position); // Change hitbox position

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
}

