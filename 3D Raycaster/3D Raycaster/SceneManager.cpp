#include "SceneManager.h"

Scene Scenes::currentMode = Scene::MainMenu;
int Scenes::level = 0;
bool Scenes::levelComplete[LEVELS_AMOUNT];

SceneManager::SceneManager() :
	m_window{ sf::VideoMode{ SCREEN_WIDTH, SCREEN_HEIGHT, 32U }, "Top Down" },
	m_exitGame{ false } //when true game will exit
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::run()
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

void SceneManager::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}

		// Check which scene you are in and do the processEvents() of that scene
		switch (Scenes::currentMode)
		{
		case Scene::None:
			break;

		case Scene::MainMenu:
			menu.processEvents(newEvent);
			break;

		case Scene::Game:
			game.processEvents(newEvent);
			break;
		}
	}
}

void SceneManager::update(sf::Time t_deltaTime)
{
	// Check which scene you are in and do the update() of that scene
	switch (Scenes::currentMode)
	{
	case Scene::None:
		break;

	case Scene::MainMenu:
		menu.update(t_deltaTime);
		break;

	case Scene::Game:
		game.update(t_deltaTime);
		break;
	}
}

void SceneManager::render()
{
	// Check which scene you are in and do the update() of that scene
	switch (Scenes::currentMode)
	{
	case Scene::None:
		break;

	case Scene::MainMenu:
		menu.render(m_window);
		break;

	case Scene::Game:
		game.render(m_window);
		break;
	}
}
