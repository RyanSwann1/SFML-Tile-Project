#include "..\..\include\Managers\EntityManager.h"
#include "Entities\Entity.h"
#include "Entities\Player.h"
#include <functional>
#include <unordered_map>
#include <string>
#include <algorithm>

class EntityManager::EntityFactory
{
public:
	EntityFactory(SharedContext* sharedContext)
	{
		registerEntity<Player>("Player", sharedContext);
	}

	Entity* const createEntity(const std::string& name) const
	{
		auto cIter = m_entityFactory.find(name);
		if (cIter != m_entityFactory.cend())
		{
			return cIter->second();
		}
		return nullptr;
	}

	template <class T>
	bool registerEntity(const std::string& name, SharedContext* sharedContext)
	{
		if (m_entityFactory.find(name) == m_entityFactory.cend())
		{
			m_entityFactory.emplace(std::make_pair(name, [sharedContext]() -> Entity*
			{
				return new T(*sharedContext);
			}));
			return true;
		}
		return false;
	}

private:
	std::unordered_map<std::string, std::function<Entity*()>> m_entityFactory;
};

void EntityManager::addEntity(const std::string& name, const sf::Vector2f & pos)
{
	Entity* const entity = m_entityFactory->createEntity(name);
	if (entity)
	{
		entity->setPosition(pos.x, pos.y);
		entity->setID(m_entityCount);
		m_entities.emplace_back(m_entityCount, entity);
		++m_entityCount;
	}	
}

EntityManager::EntityManager(SharedContext* sharedContext)
	: m_entityFactory(new EntityFactory(sharedContext))
{
}

EntityManager::~EntityManager()
{
	delete m_entityFactory;
}

void EntityManager::addEntity(const std::string& name)
{
	Entity* entity = m_entityFactory->createEntity(name);
	if (entity)
	{
		entity->setID(m_entityCount);
		m_entities.emplace_back(m_entityCount, entity);
		++m_entityCount;
	}
}

void EntityManager::update(const float deltaTime)
{
	auto entitiesCopy = m_entities;
	for (auto &i : entitiesCopy)
	{
		i.second->update(deltaTime);
	}

}

void EntityManager::draw(sf::RenderWindow & window)
{
	for (const auto &i : m_entities)
	{
		i.second->draw(window);
	}
}

void EntityManager::purgeEntities()
{
	for (auto &i : m_entities)
	{
		delete i.second;
		i.second = nullptr;
	}
	m_entities.clear();
}

void EntityManager::removeEntity(const int ID)
{
	if (std::find(m_removals.cbegin(), m_removals.cend(), ID) == m_removals.cend())
	{
		m_removals.push_back(ID);
	}
}

void EntityManager::processRemovals()
{
	for (auto iter = m_removals.begin(); iter != m_removals.end();)
	{
		if (removeActiveEntity(*iter))
		{
			iter = m_removals.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

bool EntityManager::removeActiveEntity(const int ID)
{
	auto iter = std::find_if(m_entities.begin(), m_entities.end(), [ID](const std::pair<int, Entity*>& entity) {return entity.first == ID; });
	if (iter != m_entities.end())
	{
		delete iter->second;
		iter->second = nullptr;
		return true;
	}

	else 
	{
		return false;
	}
}
