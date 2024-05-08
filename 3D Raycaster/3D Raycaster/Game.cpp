/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game()
{
	setupFontAndText(); // load font 
	setupSprites();

	// Map
	drawMap();
	player.setup(spawnPos);

	setupObjects(); // load texture


	// Rays
	ray.setPrimitiveType(sf::Lines);
	light.setPrimitiveType(sf::TrianglesStrip);
	wallSegment.setPrimitiveType(sf::TrianglesStrip);
}




/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents(sf::Event t_event)
{
	if (sf::Event::KeyPressed == t_event.type) //user pressed a key
	{
		processKeys(t_event);
	}

	// Mouse
	if (sf::Event::MouseMoved == t_event.type)
	{
		processMouseMove(t_event);
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
		Scenes::currentMode = Scene::MainMenu;
	}

	if (sf::Keyboard::Q == t_event.key.code)
	{
		topDown = !topDown;
	}

	if (sf::Keyboard::E == t_event.key.code)
	{
		for (int i = 0; i < 64; i++)
		{
			if (doors[i].active)
			{
				doors[i].open();
			}
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	// Rays & 3D
	drawRays3D();
	makeLight();

	// Player
	if (player.alive)
	{
		player.checkDirection();
		player.rotateToMouse(mousePos);
	}

	// Collisions
	for (int i = 0; i < 64; i++)
	{
		// Walls collision
		if (walls[i].active)
		{
			// Blocks collision
			walls[i].collisionDetection(player);
		}

		// Invis walls collisions
		if (invisTops[i].active)
		{
			// Blocks collision
			invisTops[i].collisionDetection(player);
		}
		// Invis walls 3D collisions
		if (invis3Ds[i].active)
		{
			// Blocks collision
			invis3Ds[i].collisionDetection(player);
		}
		// Traps
		if (traps[i].active)
		{
			// Blocks collision
			traps[i].collisionDetection(player, spawnPos);
		}
		// Traps 3D
		if (traps3D[i].active)
		{
			// Blocks collision
			traps3D[i].collisionDetection(player, spawnPos);
		}
		// Door 2D
		if (doors[i].active)
		{
			// Blocks collision
			doors[i].collisionDetection(player);
			doors[i].interactCheck(player.getBody());
		}
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render(sf::RenderWindow& t_window)
{
	t_window.clear({ 180, 180, 180, 255 });
	

	// Check which mode
	if (topDown)
	{
		// Top down Walls / Objects
		for (int i = 0; i < 64; i++)
		{
			// Walls
			if (walls[i].active)
			{
				t_window.draw(walls[i].getBody());
			}
			// Invis 3D
			else if (invis3Ds[i].active)
			{
				t_window.draw(invis3Ds[i].getBody());
			}
			else if (traps[i].active)
			{
				t_window.draw(traps[i].getBody());
			}
			else if (doors[i].active)
			{
				for (int d = 0; d < 4; d++)
				{
					t_window.draw(doors[i].interactAreas[d]);
				}

				t_window.draw(doors[i].getBody());
			}

			// Rays
			//t_window.draw(ray); // Used for DeBug
			t_window.draw(light);
		}

		// Player
		t_window.draw(player.getBody());
	}

	else
	{

		// Floor 3D
		t_window.draw(floor);

		// Walls 3D
		t_window.draw(wallSegment);

		// Gadget that sorrounds 3D screen
		t_window.draw(gadgetSprite);
	}


	t_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
}

void Game::setupSprites()
{
	// Floor
	floor.setFillColor({ 200, 200, 200, 255 });
	floor.setSize({ SCREEN_WIDTH / 2 - 8, 160 });
	floor.setPosition(5, 160);

	// Gadget Sprite
	if (!gadgetTexture.loadFromFile("ASSETS\\IMAGES\\Gadget.png"))
	{
		std::cout << "problem loading Gadget" << std::endl;
	}

	gadgetSprite.setTexture(gadgetTexture);
	gadgetSprite.setScale(0.93, 1);
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupObjects()
{

}

void Game::drawMap()
{

	sf::Vector2f pos = { blockSize / 2.0f, blockSize / 2.0f };

	for (int i = 0; i < 64; i++)
	{
		if (pos.x >= SCREEN_WIDTH / 2.0f)
		{
			pos.y += blockSize;
			pos.x = blockSize / 2.0f;
		}

		// Check the grid slot
		if (map[i] == 1)
		{
			walls[i].spawn(blockSize, pos);
		}
		else if (map[i] == 2)
		{
			invisTops[i].spawn(blockSize, pos);
		}
		else if (map[i] == 3)
		{
			invis3Ds[i].spawn(blockSize, pos);
		}
		else if (map[i] == 4)
		{
			traps[i].spawn(blockSize, pos);
		}
		else if (map[i] == 5)
		{
			traps3D[i].spawn(blockSize, pos);
		}
		else if (map[i] == 6)
		{
			doors[i].spawn(blockSize, pos);
			doors[i].setup();
		}
		else if (map[i] == 9)
		{
			spawnPos = pos;
		}
		else // = 0
		{
			// Empty
			walls[i].active = false;
			invisTops[i].active = false;
			invis3Ds[i].active = false;
			traps[i].active = false;
			traps3D[i].active = false;
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
	sf::Color wallColorH;
	sf::Color wallColorV;



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
				wallColorH = WALL_COLOR;

				dof = 8; // Hit a wall
			}
			else if (mp > 0 && mp < mapX * mapY && map[mp] == 2)
			{
				hx = rayPos.x;
				hy = rayPos.y;
				distH = dist(player.getPos().x, player.getPos().y, hx, hy, rayAngle);

				// Color
				wallColorH = INVIS_COLOR;

				dof = 8; // Hit a wall
			}
			else if (mp > 0 && mp < mapX * mapY && map[mp] == 5)
			{
				hx = rayPos.x;
				hy = rayPos.y;
				distH = dist(player.getPos().x, player.getPos().y, hx, hy, rayAngle);

				// Color
				wallColorH = TRAP_COLOR;

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
				wallColorV = WALL_COLOR;

				dof = 8; // Hit a wall
			}
			else if (mp > 0 && mp < mapX * mapY && map[mp] == 2)
			{
				vx = rayPos.x;
				vy = rayPos.y;
				distV = dist(player.getPos().x, player.getPos().y, vx, vy, rayAngle);

				// Color
				wallColorV = INVIS_COLOR;

				dof = 8; // Hit a wall
			}
			else if (mp > 0 && mp < mapX * mapY && map[mp] == 5)
			{
				vx = rayPos.x;
				vy = rayPos.y;
				distV = dist(player.getPos().x, player.getPos().y, vx, vy, rayAngle);

				// Color
				wallColorV = TRAP_COLOR;

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

			wallColor = wallColorV;
			wallColor += SIDE_COLOR_CHANGE;
		}
		else if (distH < distV)
		{
			rayPos.x = hx;
			rayPos.y = hy;
			finalDistance = distH;

			wallColor = wallColorH;
		}



		// Draw ray
		ray.append(player.getPos());
		ray.append(rayPos);



		// Set Color
		ray[rayN].color = wallColor;
		rayN++;
		ray[rayN].color = wallColor;


		//----- Draw 3D Walls -----//
		// 
		// Fix fish eye effect
		float correctedAngle = player.getAngle() - rayAngle;

		finalDistance = finalDistance * cos(correctedAngle);

		float lineHeight = (blockSize * 320 / finalDistance);
		if (lineHeight > 320) // Cap the line's height at 320
		{
			lineHeight = 320;
		}

		float lineOffset = 160 - lineHeight / 2;


		sf::Vector2f tempVector;
		tempVector = { r * 8 + 5, lineOffset };
		wallSegment.append(tempVector);
		tempVector = { r * 8 + 5, lineHeight + lineOffset };
		wallSegment.append(tempVector);

		int wallN = r * 2;

		// Color Walls
		wallSegment[wallN].color = wallColor;
		wallN++;
		wallSegment[wallN].color = wallColor;




		rayAngle += DEGREE_R;
	}
}

void Game::makeLight()
{
	int mx, my, mp, dof;
	float r;
	float finalDistance = 0.0f;
	float xOffset = 0.0f, yOffset = 0.0f;
	float lightAngle = player.getAngle() - DEGREE_R * 32;
	sf::Vector2f lightEnd;

	light.clear();




	// Draw ray
	for (r = 0; r < 64; r++)
	{
		//----- Horizontal Line Check -----//
		dof = 0;

		float distH = 1000000;
		float hx = player.getPos().x;
		float hy = player.getPos().y;

		float aTan = -1 / tan(lightAngle);


		if (lightAngle < 0) // Looking up
		{
			lightEnd.y = (((int)player.getPos().y >> 6) << 6) - 0.0001f;
			lightEnd.x = (player.getPos().y - lightEnd.y) * aTan + player.getPos().x;
			yOffset = -64;
			xOffset = -yOffset * aTan;
		}

		if (lightAngle > 0) // Looking down
		{
			lightEnd.y = (((int)player.getPos().y >> 6) << 6) + 64;
			lightEnd.x = (player.getPos().y - lightEnd.y) * aTan + player.getPos().x;
			yOffset = 64;
			xOffset = -yOffset * aTan;
		}

		if (lightAngle == 0 || lightAngle == PI) // Looking straight left or right
		{
			lightEnd.x = player.getPos().x;
			lightEnd.y = player.getPos().y;

			dof = 8;
		}

		while (dof < 8)
		{
			mx = (int)(lightEnd.x) >> 6;
			my = (int)(lightEnd.y) >> 6;
			mp = my * mapX + mx;

			// Check what it hit
			if (mp > 0 && mp < mapX * mapY && map[mp] == 1)
			{
				hx = lightEnd.x;
				hy = lightEnd.y;
				distH = dist(player.getPos().x, player.getPos().y, hx, hy, lightAngle);


				dof = 8; // Hit a wall
			}
			else if (mp > 0 && mp < mapX * mapY && map[mp] == 3)
			{
				hx = lightEnd.x;
				hy = lightEnd.y;
				distH = dist(player.getPos().x, player.getPos().y, hx, hy, lightAngle);


				dof = 8; // Hit a wall
			}
			else if (mp > 0 && mp < mapX * mapY && map[mp] == 4)
			{
				hx = lightEnd.x;
				hy = lightEnd.y;
				distH = dist(player.getPos().x, player.getPos().y, hx, hy, lightAngle);


				dof = 8; // Hit a wall
			}
			else
			{
				lightEnd.x += xOffset;
				lightEnd.y += yOffset;

				dof += 1;
			}
		}




		//----- Vertical Line Check -----//
		dof = 0;

		float distV = 1000000;
		float vx = player.getPos().x;
		float vy = player.getPos().y;

		float nTan = -tan(lightAngle);


		if ((lightAngle >= P2 && lightAngle <= P3) || (lightAngle <= -P2 && lightAngle >= -P3)) // Looking left
		{
			lightEnd.x = (((int)player.getPos().x >> 6) << 6) - 0.0001f;
			lightEnd.y = (player.getPos().x - lightEnd.x) * nTan + player.getPos().y;
			xOffset = -64;
			yOffset = -xOffset * nTan;
		}

		if ((lightAngle <= P2 && lightAngle >= -P2) || (lightAngle >= P3 && lightAngle <= P3)) // Looking right
		{
			lightEnd.x = (((int)player.getPos().x >> 6) << 6) + 64;
			lightEnd.y = (player.getPos().x - lightEnd.x) * nTan + player.getPos().y;
			xOffset = 64;
			yOffset = -xOffset * nTan;
		}

		if (lightAngle == 0 || lightAngle == PI) // Looking straight up or down
		{
			lightEnd.x = player.getPos().x;
			lightEnd.y = player.getPos().y;

			dof = 8;
		}

		while (dof < 8)
		{
			mx = (int)(lightEnd.x) >> 6;
			my = (int)(lightEnd.y) >> 6;
			mp = my * mapX + mx;

			if (mp > 0 && mp < mapX * mapY && map[mp] == 1)
			{
				vx = lightEnd.x;
				vy = lightEnd.y;
				distV = dist(player.getPos().x, player.getPos().y, vx, vy, lightAngle);


				dof = 8; // Hit a wall
			}
			else if (mp > 0 && mp < mapX * mapY && map[mp] == 3)
			{
				vx = lightEnd.x;
				vy = lightEnd.y;
				distV = dist(player.getPos().x, player.getPos().y, vx, vy, lightAngle);


				dof = 8; // Hit a wall
			}
			else if (mp > 0 && mp < mapX * mapY && map[mp] == 4)
			{
				vx = lightEnd.x;
				vy = lightEnd.y;
				distV = dist(player.getPos().x, player.getPos().y, vx, vy, lightAngle);


				dof = 8; // Hit a wall
			}
			else
			{
				lightEnd.x += xOffset;
				lightEnd.y += yOffset;

				dof += 1;
			}
		}



		int lightN = r * 2;
		// Find the ray with the lowest distance
		if (distV < distH)
		{
			lightEnd.x = vx;
			lightEnd.y = vy;
			finalDistance = distV;
		}
		else if (distH < distV)
		{
			lightEnd.x = hx;
			lightEnd.y = hy;
			finalDistance = distH;
		}



		// Draw Light

		light.append(player.getPos());

		// Check if the current lenght is less than the light's lenght
		if (finalDistance < LIGHT_REACH)
		{
			light.append(lightEnd);
		}
		else
		{
			// Get light lenght
			lightEnd = pointOnALine(player.getPos(), lightEnd, lightAngle, LIGHT_REACH);
			light.append(lightEnd);
		}

		// Set Color
		light[lightN].color = LIGHT_COLOR;
		lightN++;
		light[lightN].color = LIGHT_COLOR;


		lightAngle += DEGREE_R;
	}
}


sf::Vector2f Game::pointOnALine(sf::Vector2f t_startPoint, sf::Vector2f t_endPoint, float t_angle, int t_distance)
{
	// Calculate the total length of the line
	float totalLength = dist(t_startPoint.x, t_startPoint.y, t_endPoint.x, t_endPoint.y, t_angle);

	// Calculate the ratio of the desired length to the total length of the line
	float ratio = t_distance / totalLength;

	// Calculate the coordinates of the point at the desired length along the line
	float newX = t_startPoint.x + ratio * (t_endPoint.x - t_startPoint.x);
	float newY = t_startPoint.y + ratio * (t_endPoint.y - t_startPoint.y);

	return { newX, newY };
}
