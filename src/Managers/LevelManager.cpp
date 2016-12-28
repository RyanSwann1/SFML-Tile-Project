#include "Managers/LevelManager.h"
#include "Managers\EntityManager.h"
#include "Map\WorldMap.h"
#include <algorithm>

LevelManager::LevelManager(const SharedContext& sharedContext)
	: m_sharedContext(sharedContext),
	m_levelParser(sharedContext)
{
	
}

LevelManager::~LevelManager()
{
	purgeCurrentLevel();
}

void LevelManager::changeLevel(const std::string& newLevelName)
{	
	auto cIter = std::find_if(m_levelNames.cbegin(), m_levelNames.cend(), [newLevelName](const std::pair<std::string, std::string>& name) {return name.first == newLevelName; });
	if (cIter != m_levelNames.cend())
	{
		purgeCurrentLevel();
		m_levelParser.parseLevel(cIter->second);
	}
}

void LevelManager::update(const float deltaTime)
{
	m_sharedContext.m_worldMap.update(deltaTime);
	m_sharedContext.m_entityManager.update(deltaTime);
}

void LevelManager::draw(sf::RenderWindow & window)
{
	m_sharedContext.m_worldMap.draw(window);
	m_sharedContext.m_entityManager.draw(window);
}

void LevelManager::purgeCurrentLevel()
{
	m_sharedContext.m_worldMap.purgeTileLayers();
	m_sharedContext.m_entityManager.purgeEntities();
}

