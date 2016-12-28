#pragma once

#include "SharedContext.h"
#include "Window\Window.h"
#include "Managers\StateManager.h"
#include "Managers\TextureManager.h"
#include "Managers\EntityManager.h"
#include "Map\WorldMap.h"
#include "Parser\GUIParser.h"
#include "Utilities.h"

class Game
{
public:
	Game();

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	const bool isRunning() const { return m_window.isRunning(); }
	void update();
	void draw();
	void lateUpdate();

private:
	Window m_window;
	StateManager m_stateManager;
	TextureManager m_textureManager;
	GUIParser m_guiParser;
	WorldMap m_worldMap;
	SharedContext m_sharedContext;
	EntityManager m_entityManager;
	const Utilities m_utilities;

	sf::Time m_time;
	sf::Clock m_clock;
};