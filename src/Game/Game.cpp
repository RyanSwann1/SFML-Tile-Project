#include "Game\Game.h"

Game::Game() 
	: m_window("Platformer!", sf::Vector2i(500, 350)),
	m_stateManager(m_sharedContext),
	m_worldMap(m_sharedContext),
	m_sharedContext(m_stateManager, m_textureManager, m_worldMap, m_entityManager, m_utilities),
	m_entityManager(&m_sharedContext)
{
	m_stateManager.switchTo(StateType::Game);
}

void Game::update()
{
	m_window.update();
	m_stateManager.update(m_time.asSeconds());
}

void Game::draw()
{
	m_window.beginDraw();
	m_stateManager.draw(m_window.getWindow());
	m_window.endDraw();
}

void Game::lateUpdate()
{
	m_time = m_clock.restart();
}
