

#include "Player.h"   // include Player header file
#include <iostream>


// Default constructer
Player::Player()
{
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
		direction = Direction::Left;
		move(t_2D);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction = Direction::Right;
		move(t_2D);
	}
}

// Checks the mouse position and rotates the player to face that position
void Player::rotateToMouse(sf::Vector2f t_mousePos, bool t_2D)
{
	// Rotates the player to the mouse
	float angleD; // Degrees


	if (t_2D) // In 3D mode move camera when moving mouse side to side
	{
		sf::Vector2f line;

		line = t_mousePos - position;
		angleR = std::atan2f(line.y, line.x); // Find the angle of the line in radians
	}
	else
	{
		// Calculate the change in mouse position since the last frame
		sf::Vector2f deltaMousePos = t_mousePos - prevMousePos;
		prevMousePos = t_mousePos;


		// Check if the mouse is moving to the left or right
		if (deltaMousePos.x > 0)
		{
			angleR += 0.05f * (deltaMousePos.x / 10.0f);

			// Correct angle
			if (angleR > PI)
			{
				angleR = -PI;
			}
		}
		else if (deltaMousePos.x < 0)
		{
			angleR -= 0.05f * -(deltaMousePos.x / 10.0f);

			// Correct angle
			if (angleR < -PI)
			{
				angleR = PI;
			}
		}
	}



	// Set the rotations
	angleD = angleR * 180.0f / PI;     // Convert to degrees
	body.setRotation(angleD + 90.0f);  // Rotate the body
}

// Moves the player in the direction pressed
void Player::move(bool t_2D)
{
	sf::Vector2f movement = { 0.0f, 0.0f };

	if (t_2D)
	{
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
	}
	else // Move depending on the direction you're facing
	{
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

		case Direction::Left:
			movement.x = sin(angleR) * speed;
			movement.y = cos(angleR) * speed;
			break;

		case Direction::Right:
			movement.x = sin(angleR) * -speed;
			movement.y = cos(angleR) * -speed;
			break;
		}
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

