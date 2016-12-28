#pragma once

#include "SharedContext.h"
#include <list>
#include <vector>
#include <SFML\Graphics.hpp>
#include <unordered_map>
#include <string>

class Entity;
class EntityManager
{
public:
	EntityManager(SharedContext* sharedContext);
	~EntityManager();
	void addEntity(const std::string& name);
	void addEntity(const std::string& name, const sf::Vector2f& pos);

	void update(const float deltaTime);
	void draw(sf::RenderWindow& window);

	void purgeEntities();
	void removeEntity(const int ID);

private:
	class EntityFactory;
	const EntityFactory* const m_entityFactory;
	std::list<std::pair<int, Entity*>> m_entities;
	std::unordered_map<std::string, std::string> m_entityDetails;
	std::list<int> m_removals;
	int m_entityCount;

	void processRemovals();
	bool removeActiveEntity(const int ID);
};
