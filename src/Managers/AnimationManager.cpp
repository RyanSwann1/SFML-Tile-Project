#include "Managers\AnimationManager.h"
#include "Sprite\SpriteSheet.h"

AnimationManager::AnimationManager(const SharedContext& sharedContext)
	: m_sharedContext(sharedContext),
	m_currentAnimation(nullptr)
{

}

void AnimationManager::print()
{

}

void AnimationManager::loadInAnimations(const std::string & fileName)
{

}

void AnimationManager::update(const float deltaTime)
{
	if (m_currentAnimation)
	{
		m_currentAnimation->update(deltaTime);
	}
}

void AnimationManager::draw(sf::RenderWindow & window)
{
	if (m_currentAnimation)
	{
		m_currentAnimation->draw(window);
	}
}

void SpriteSheet::setDrawLocation()
{
	const int tileSize = WorldMap::getTileSize();
	if (m_currentAnimation)
	{
		sf::IntRect drawLocation = m_currentAnimation->getDrawLocation();

		((m_tileFlipped) ? -drawLocation.width : drawLocation.width); //Flip the tile 
		m_spriteSheet.setTextureRect(drawLocation);

		//if (m_tileFlipped)
		//{
		//	m_spriteSheet.setTextureRect(sf::IntRect(drawLocation.x * tileSize, drawLocation.y * tileSize, tileSize, tileSize));
		//}
		//else
		//{
		//	m_spriteSheet.setTextureRect(sf::IntRect(drawLocation.x * tileSize, drawLocation.y * tileSize, -tileSize, tileSize));
		//}
	}
}

void SpriteSheet::setAnimationType(const EntityState state, const Direction dir)
{
	auto cIter = m_animations.find(state);
	if (cIter != m_animations.cend())
	{
		if (m_currentAnimation)
		{
			m_currentAnimation->stop();
		}

		m_currentAnimation = &cIter->second;
	}
}

void SpriteSheet::loadInSpriteSheetDetails(const std::string & fileName)
{
	//Animations have already been loaded in
	if (!m_animations.empty())
	{
		return;
	}

	std::ifstream file(fileName);
	assert(file.is_open());

	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream keyStream(line);
		std::string type;
		sf::Vector2i drawLocationSize;
		int entityState = 0, startRow = 0, endRow = 0, column = 0, frameTime = 0, direction = 0, repeatable = 0;

		keyStream >> type;
		if (type == "Animation")
		{
			keyStream >> entityState >> startRow >> endRow >> column >> frameTime >> direction >> repeatable;
			////Add new animation
			//auto anim = findAnimation(static_cast<EntityState>(entityState));
			//if (anim)
			//{
			//	anim->emplace_back(std::make_pair(static_cast<Direction>(direction), Animation(startRow, endRow, column, frameTime, direction, repeatable)));
			//}
			//else
			//{
			//	m_animations[static_cast<EntityState>(entityState)].emplace_back(
			//		std::make_pair(static_cast<Direction>(direction), Animation(startRow, endRow, column, frameTime, direction, repeatable)));
			//}
		}
		if (type == "DrawLocationSize")
		{
			keyStream >> drawLocationSize.x >> drawLocationSize.y;
		}

		assert(m_animations.emplace(static_cast<EntityState>(entityState),
			Animation(startRow, endRow, column, frameTime, direction, repeatable, drawLocationSize, WorldMap::getTileSize())).second);
	}
}


void SpriteSheet::changeAnimationDirection(const Direction dir)
{
	switch (dir)
	{
	case (Direction::Right):
	{
		m_tileFlipped = false;
		break;
	}
	case (Direction::Left):
	{
		m_tileFlipped = true;
		break;
	}
	}
}
