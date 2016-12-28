#pragma once

#include "Parser\LevelParser.h"
#include "SharedContext.h"
#include <unordered_map>
#include <string>
#include <SFML\Graphics.hpp>
#include <array>

class LevelManager
{
public:
	LevelManager(const SharedContext& sharedContext);
	~LevelManager();

	void changeLevel(const std::string& newLevelName);

	void update(const float deltaTime);
	void draw(sf::RenderWindow& window);

private:
	LevelParser m_levelParser;
	SharedContext m_sharedContext;
	const std::array<std::pair<std::string, std::string>, static_cast<size_t>(1)> m_levelNames{ std::make_pair("Level1", "Map1.tmx") };
	
	void purgeCurrentLevel();
};