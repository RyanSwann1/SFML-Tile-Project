#include "Entities\Entity.h"
#include "Map\WorldMap.h"
#include <math.h>
#include <fstream>
#include <sstream>
#include <assert.h>

Entity::Entity(const SharedContext & sharedContext, const std::string name)
	: m_sharedContext(sharedContext),
	m_spriteSheet(sharedContext),
	m_name(name)
{

}

void Entity::draw(sf::RenderWindow & window)
{
	m_spriteSheet.draw(window);
}

void Entity::update(const float deltaTime)
{
	applyGravity();
	applyFriction();

	const sf::Vector2f deltaPos = m_velocity * deltaTime;
	move(deltaPos.x, deltaPos.y);

	m_spriteSheet.update(deltaTime);
}

void Entity::moveDirection(const Direction newDir)
{
	if (m_currentDirection != newDir)
	{
		m_currentDirection = newDir;
	}
	switch (newDir)
	{
	case (Direction::Right) :
	{
		move(m_speed.x, 0);
		break;
	}
	case (Direction::Left) :
	{
		move(-m_speed.x, 0);
		break;
	}
	}
}

void Entity::move(const float x, const float y)
{
	m_oldPosition = m_position;
	m_position += sf::Vector2f(x, y);

	//Keep position within bounds of map
	const sf::Vector2f& mapSize = m_sharedContext.m_worldMap.getMapSize();
	if (m_position.x < mapSize.x)
	{
		m_position.x = 0;
	}

	else if (m_position.x > mapSize.x)
	{
		m_position.x = mapSize.x;
	}
}

void Entity::applyFriction()
{
	if (std::abs(m_velocity.x) > 0.0f)
	{
		//if((m_velocity.x > 0.0f) - m_friction.x)
		if (m_velocity.x > 0.0f)
		{
			m_velocity.x -= m_friction.x;
		}
		else
		{
			m_velocity.x += m_friction.x;
		}
	}
}

void Entity::loadInDetails(const std::string& fileName)
{
	std::ifstream file(fileName);
	assert(file.is_open());

	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream keyStream(line);

		std::string type;
		keyStream >> type;
		if ("SpriteSheet")
		{
			std::string spriteSheetLocation;
			keyStream >> spriteSheetLocation;
			Entity::getSpriteSheet().loadInSpriteSheetDetails(spriteSheetLocation);
		}
	}
}
