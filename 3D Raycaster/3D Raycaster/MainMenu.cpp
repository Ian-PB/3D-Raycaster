#include "MainMenu.h"

MainMenu::MainMenu()
{
	for (int i = 0; i < LEVELS_AMOUNT; i++)
	{
		float xValue = 0.0f;
		float yValue = 0.0f;
		colliding[i] = false;

		if (i < LEVELS_AMOUNT / 2)
		{
			yValue = (SCREEN_HEIGHT / 4.0f) + 50;
		}
		else
		{
			yValue = ((SCREEN_HEIGHT / 4.0f) * 3) - 50;
		}

		xValue = (i * 2.0f) * 50 + 55;

		if (i >= LEVELS_AMOUNT / 2)
		{
			xValue -= 500; // The multiplied value * the added value in the first xValue equation
		}

		sf::Vector2f tempPos = { xValue, yValue };
		buttons[i].setup(tempPos, 75, 75, sf::Color::Red);
	}
}

void MainMenu::processEvents(sf::Event t_event)
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
	if (sf::Event::MouseButtonPressed == t_event.type)
	{
		processMouseDown(t_event);
	}
}

void MainMenu::update(sf::Time t_deltaTime)
{
	for (int i = 0; i < LEVELS_AMOUNT; i++)
	{
		// Check what the mouse is over
		colliding[i] = buttons[i].checkForMouse(mousePos);
	}

	for (int i = 0; i < LEVELS_AMOUNT; i++)
	{
		if (Scenes::levelComplete[i])
		{
			buttons[i].changeColor(sf::Color::Green);
		}
	}
}

void MainMenu::render(sf::RenderWindow& t_window)
{
	t_window.clear({ 180, 180, 180, 255 });

	for (int i = 0; i < LEVELS_AMOUNT; i++)
	{
		t_window.draw(buttons[i].getBody());
	}

	t_window.display();
}

void MainMenu::processMouseMove(sf::Event t_event)
{
	// Gets the position of the mouse
	mousePos.x = static_cast<float>(t_event.mouseMove.x);
	mousePos.y = static_cast<float>(t_event.mouseMove.y);
}

void MainMenu::processMouseDown(sf::Event t_event)
{
	for (int i = 0; i < LEVELS_AMOUNT; i++)
	{
		if (colliding[i])
		{
			switch (i)
			{
				// Start button
			case 0:
				std::cout << "Level 1 \n";
				Scenes::level = 1;
				Scenes::currentMode = Scene::Game;
				break;


			case 1:
				std::cout << "Level 2 \n";
				Scenes::level = 2;
				Scenes::currentMode = Scene::Game;
				break;


			case 2:
				std::cout << "Level 3 \n";
				Scenes::level = 3;
				Scenes::currentMode = Scene::Game;
				break;

			case 3:
				std::cout << "Level 4 \n";
				Scenes::level = 4;
				Scenes::currentMode = Scene::Game;
				break;

			case 4:
				std::cout << "Level 5 \n";
				Scenes::level = 5;
				Scenes::currentMode = Scene::Game;
				break;

			case 5:
				std::cout << "Level 6 \n";
				Scenes::level = 6;
				Scenes::currentMode = Scene::Game;
				break;

			case 6:
				std::cout << "Level 7 \n";
				Scenes::level = 7;
				Scenes::currentMode = Scene::Game;
				break;

			case 7:
				std::cout << "Level 8 \n";
				Scenes::level = 8;
				Scenes::currentMode = Scene::Game;
				break;

			case 8:
				std::cout << "Level 9 \n";
				Scenes::level = 9;
				Scenes::currentMode = Scene::Game;
				break;

			case 9:
				std::cout << "Level 10 \n";
				Scenes::level = 10;
				Scenes::currentMode = Scene::Game;
				break;
			}
		}
	}
}

void MainMenu::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		for (int i = 0; i < LEVELS_AMOUNT; i++)
		{
			std::cout << colliding[i] << std::endl;
		}
		std::cout << std::endl;
	}
}

void MainMenu::setupFontAndText()
{
}

void MainMenu::setupSprites()
{
}

void MainMenu::setupObjects()
{
}
