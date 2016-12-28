#include "Entities\Character.h"
#include "Utilities.h"
#include <math.h>
#include <fstream>
#include <sstream>
#include <assert.h>

Character::Character(const SharedContext & sharedContext, const std::string name)
	: Entity(sharedContext, name)
{
	loadInDetails(sharedContext.m_utilities.getEntityDetails(Entity::getName()));
}

void Character::update(const float deltaTime)
{
	Entity::update(deltaTime);

	if (std::abs(Entity::getVelocity().x > 0.1f))
	{
		setState(EntityState::Walking);
	}
	else
	{
		setState(EntityState::Idling);
	}

	determineAnimationType();
}

void Character::determineAnimationType()
{
	//Hacky way of flipping a tile
	if (Entity::getCurrentDirection() == Direction::Left)
	{
		Entity::getSpriteSheet().flipTile(true);
	}
	else if (Entity::getCurrentDirection() == Direction::Right)
	{
		Entity::getSpriteSheet().flipTile(false);
	}

	SpriteSheet& spriteSheet = Entity::getSpriteSheet();
	const Direction dir = Entity::getCurrentDirection();

	switch (m_state)
	{
	case (EntityState::Idling) :
	{
		spriteSheet.setAnimationType(m_state, dir);
		break;
	}
	case (EntityState::Walking) :
	{
		spriteSheet.setAnimationType(m_state, dir);
		break;
	}
	case (EntityState::Hurt) :
	{
		if (!spriteSheet.getCurrentAnimation().isFinished())
		{
			spriteSheet.setAnimationType(EntityState::Idling, dir);
		}
		break;
	}
	}
}

void Character::setState(const EntityState state)
{
	if (m_state != EntityState::Dead)
	{
		m_state = state;
	}
}

void Character::loadInDetails(const std::string & fileName)
{
	Entity::loadInDetails(fileName);
	//std::ifstream file(fileName);
	//assert(file.is_open());

	//std::string line;
	//while (std::getline(file, line))
	//{
	//	std::stringstream keyStream(line);
	//	std::string type;
	//	keyStream >> type;
	//	if (type == "SpriteSheetDetails")
	//	{
	//		std::string spriteSheetLocation;
	//		keyStream >> spriteSheetLocation;
	//		Entity::getSpriteSheet().loadInSpriteSheetDetails(spriteSheetLocation);
	//	}
	//}
}