/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ SCREEN_WIDTH, SCREEN_HEIGHT, 32U }, "Top Down" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupObjects(); // load texture

	// Map
	drawMap();

	// Rays
	ray.setPrimitiveType(sf::Lines);
	wallSegment.setPrimitiveType(sf::TrianglesStrip);
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}

		// Mouse
		if (sf::Event::MouseMoved == newEvent.type)
		{
			processMouseMove(newEvent);
		}
	}
}

// Gets the mouse position on the screen
void Game::processMouseMove(sf::Event t_event)
{
	// Gets the position of the mouse
	mousePos.x = static_cast<float>(t_event.mouseMove.x);
	mousePos.y = static_cast<float>(t_event.mouseMove.y);
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	// Rays & 3D
	drawRays3D();

	// Player
	player.checkDirection();
	player.rotateToMouse(mousePos);

	for (int i = 0; i < 64; i++)
	{
		if (blocks[i].active)
		{
			// Blocks collision
			blocks[i].collisionDetection(player);
		}
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear({ 180, 180, 180, 255 });
	
	// Player
	m_window.draw(player.getBody());

	for (int i = 0; i < 64; i++)
	{
		if (blocks[i].active)
		{
			// Blocks
			m_window.draw(blocks[i].getBody());
		}

		// Rays
		m_window.draw(ray);
		m_window.draw(wallSegment);
	}

	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupObjects()
{
	player.setup({ SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 2.0f });
}

void Game::drawMap()
{

	sf::Vector2f pos = { blockSize / 2.0f, blockSize / 2.0f };

	for (int i = 0; i < 64; i++)
	{
		if (pos.x >= SCREEN_WIDTH / 2)
		{
			pos.y += blockSize;
			pos.x = blockSize / 2.0f;
		}

		// Check the grid slot
		if (map[i] == 1)
		{
			blocks[i].spawn(blockSize, pos);
		}

		pos.x += blockSize;
	}
}

void Game::drawRays3D()
{
	int mx, my, mp, dof;
	float r;
	float finalDistance = 0.0f;
	float xOffset = 0.0f, yOffset = 0.0f;
	sf::Vector2f rayPos;

	ray.clear();
	wallSegment.clear();

	float rayAngle = player.getAngle() - DEGREE_R * 32;

	sf::Color wallColor;



	// Draw ray
	for (r = 0; r < 64; r++)
	{
	    //----- Horizontal Line Check -----//
		dof = 0;

		float distH = 1000000;
		float hx = player.getPos().x;
		float hy = player.getPos().y;

		float aTan = -1 / tan(rayAngle);


		if (rayAngle < 0) // Looking up
		{
			rayPos.y = (((int)player.getPos().y >> 6) << 6) - 0.0001f;
			rayPos.x = (player.getPos().y - rayPos.y) * aTan + player.getPos().x;
			yOffset = -64;
			xOffset = -yOffset * aTan;
		}

		if (rayAngle > 0) // Looking down
		{
			rayPos.y = (((int)player.getPos().y >> 6) << 6) + 64;
			rayPos.x = (player.getPos().y - rayPos.y) * aTan + player.getPos().x;
			yOffset = 64;
			xOffset = -yOffset * aTan;
		}

		if (rayAngle == 0 || rayAngle == PI) // Looking straight left or right
		{
			rayPos.x = player.getPos().x;
			rayPos.y = player.getPos().y;

			dof = 8;
		}

		while (dof < 8)
		{
			mx = (int)(rayPos.x) >> 6;
			my = (int)(rayPos.y) >> 6;
			mp = my * mapX + mx;

			// Check what it hit
			if (mp > 0 && mp < mapX * mapY && map[mp] == 1)
			{
				hx = rayPos.x;
				hy = rayPos.y;
				distH = dist(player.getPos().x, player.getPos().y, hx, hy, rayAngle);

				// Color
				wallColor = WALL_COLOR;

				dof = 8; // Hit a wall
			}
			else if (mp > 0 && mp < mapX * mapY && map[mp] == 2)
			{
				hx = rayPos.x;
				hy = rayPos.y;
				distH = dist(player.getPos().x, player.getPos().y, hx, hy, rayAngle);

				// Color
				wallColor = INVIS_COLOR;

				dof = 8; // Hit a wall
			}
			else
			{
				rayPos.x += xOffset;
				rayPos.y += yOffset;

				dof += 1;
			}
		}




		//----- Vertical Line Check -----//
		dof = 0;

		float distV = 1000000;
		float vx = player.getPos().x;
		float vy = player.getPos().y;

		float nTan = -tan(rayAngle);




		if ((rayAngle >= P2 && rayAngle <= P3) || (rayAngle <= -P2 && rayAngle >= -P3)) // Looking left
		{
			rayPos.x = (((int)player.getPos().x >> 6) << 6) - 0.0001f;
			rayPos.y = (player.getPos().x - rayPos.x) * nTan + player.getPos().y;
			xOffset = -64;
			yOffset = -xOffset * nTan;
		}

		if ((rayAngle <= P2 && rayAngle >= -P2) || (rayAngle >= P3 && rayAngle <= P3)) // Looking right
		{
			rayPos.x = (((int)player.getPos().x >> 6) << 6) + 64;
			rayPos.y = (player.getPos().x - rayPos.x) * nTan + player.getPos().y;
			xOffset = 64;
			yOffset = -xOffset * nTan;
		}

		if (rayAngle == 0 || rayAngle == PI) // Looking straight up or down
		{
			rayPos.x = player.getPos().x;
			rayPos.y = player.getPos().y;

			dof = 8;
		}

		while (dof < 8)
		{
			mx = (int)(rayPos.x) >> 6;
			my = (int)(rayPos.y) >> 6;
			mp = my * mapX + mx;

			if (mp > 0 && mp < mapX * mapY && map[mp] == 1)
			{
				vx = rayPos.x;
				vy = rayPos.y;
				distV = dist(player.getPos().x, player.getPos().y, vx, vy, rayAngle);

				// Color
				wallColor = WALL_COLOR;

				dof = 8; // Hit a wall
			}
			else if (mp > 0 && mp < mapX * mapY && map[mp] == 2)
			{
				vx = rayPos.x;
				vy = rayPos.y;
				distV = dist(player.getPos().x, player.getPos().y, vx, vy, rayAngle);

				// Color
				wallColor = INVIS_COLOR;

				dof = 8; // Hit a wall
			}
			else
			{
				rayPos.x += xOffset;
				rayPos.y += yOffset;

				dof += 1;
			}
		}
		


		int rayN = r * 2;
		// Find the ray with the lowest distance
		if (distV < distH)
		{
			rayPos.x = vx;
			rayPos.y = vy;
			finalDistance = distV;

			wallColor += SIDE_COLOR_CHANGE;
		}
		else if (distH < distV)
		{
			rayPos.x = hx;
			rayPos.y = hy;
			finalDistance = distH;
		}

		// Draw ray
		ray.append(player.getPos());
		ray.append(rayPos);

		// Set Color
		ray[rayN].color = wallColor;
		rayN++;
		ray[rayN].color = wallColor;


		//----- Draw 3D Walls -----//
		
		// Fix fish eye effect
		float correctedAngle = player.getAngle() - rayAngle;

		finalDistance = finalDistance * cos(correctedAngle);

		float lineHeight = (blockSize * 320 / finalDistance);
		if (lineHeight > 320) // Cap the line's height at 320
		{
			lineHeight = 320;
		}

		float lineOffset = 160 - lineHeight / 2;

		// Draw wall
		sf::Vector2f tempVector;
		tempVector = { r * 8 + 530, lineOffset };
		wallSegment.append(tempVector);
		tempVector = { r * 8 + 530, lineHeight + lineOffset };
		wallSegment.append(tempVector);

		int wallN = r * 2;
		
		// Color
		wallSegment[wallN].color = wallColor;
		wallN++;
		wallSegment[wallN].color = wallColor;


		rayAngle += DEGREE_R;
	}
}
